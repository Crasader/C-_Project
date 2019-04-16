#include "D21BuyDialog.h"
//#include "D21UpgradeMessage.h"

namespace D21
{
	BuyDialog* BuyDialog::create(Node* parent, LLONG max, LLONG min, LLONG plan, LLONG total, BYTE deskStation)
	{
		BuyDialog* dialog = new BuyDialog();
		if(dialog->init(parent, max, min, plan, total, deskStation))
		{
			dialog->ignoreAnchorPointForPosition(false);
			dialog->autorelease();
			return dialog;
		}
		else
		{
			CC_SAFE_DELETE(dialog);
			return nullptr;
		}
	}

	bool BuyDialog::init(Node* parent, LLONG max, LLONG min, LLONG plan, LLONG total, BYTE deskStation)
	{
		if(!HNDialogBase::init(parent))
		{
			return false;
		}

		auto distpatch = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(BuyDialog::onTouchBegan,this);
		listener->setSwallowTouches(true);
		distpatch->addEventListenerWithSceneGraphPriority(listener,this);

		_max = max;
		_min = min;
		_plan = plan > total ? total : plan;
		_total = total;
		_deskStation = deskStation;

		//_widget = GUIReader::getInstance()->widgetFromJsonFile("dzpoker/buydialog/buydialog.json");
		_widget = GUIReader::getInstance()->widgetFromJsonFile("");

		locateMid(_widget);
		this->addChild(_widget);

		resetLayout();

		return true;
	}

	bool BuyDialog::onTouchBegan(Touch *touch, Event *unused_event)
	{
		return false;
	}

	void  BuyDialog::sliderChangedCallback(Ref* pRef,ui::Slider::EventType eventType)
	{
		if(eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			LLONG min = _min;
			LLONG max = _total > _max ? _max : _total;
			int percent = _slider->getPercent();
			_plan = min + LLONG(percent / 100.0 * (max - min));
			char str[50] = {0};
			sprintf(str,"%lld",_plan);
			_planTextAtlas->setString(str);
		}
	}

	void BuyDialog::sendMoneyPlan()
	{
		//TSubMoney cmd;
		//cmd.bDeskStation = _deskStation;
		//cmd.nMoney[_deskStation] = _plan;
		//RoomLogic()->sendData(MDM_GM_GAME_NOTIFY,ASS_SUB_MONEY, (CHAR*)&cmd, sizeof(cmd));
	}

	void BuyDialog::sendStandUp()
	{
		RoomLogic()->sendData(MDM_GR_USER_ACTION, ASS_GR_USER_UP);
	}

	void  BuyDialog::submitCallback(Ref* pSender, Widget::TouchEventType type)
	{
		if (ui::Widget::TouchEventType::ENDED != type)
		{
			return ;
		}
		auto btn = (ui::Button*)pSender;
		if (btn == _btnMax)				//ֱ�Ӱ����Я��
		{
			if (_total >= _max)
			{
				_plan = _max;
				sendMoneyPlan();
				hide();
			}
		}
		else if (btn == _btnMin)		//ֱ�Ӱ���СЯ��
		{
			if (_total >= _min)
			{
				_plan = _min;
				sendMoneyPlan();
				hide();
			}

		}
		else if (btn == _btnOk)			//�ύ��ť
		{
			sendMoneyPlan();
			hide();
		}
		else if (btn == _btnCancle)		//ȡ��
		{
			sendStandUp();
			hide();
		}
	}


	void BuyDialog::resetLayout()
	{
		LLONG min = _min;
		LLONG max = _total > _max ? _max : _total;
		char str[50] = {0};

		_allMoney = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(_widget, "currentmoney"));

		_slider = dynamic_cast<Slider*>(Helper::seekWidgetByName(_widget, "slider"));
		_slider->addEventListener(CC_CALLBACK_2(BuyDialog::sliderChangedCallback,this));

		_btnMax = dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "max"));
		_btnMax->addTouchEventListener(CC_CALLBACK_2(BuyDialog::submitCallback,this));
		sprintf(str,"%lld", max);
		_btnMax->setTitleText(str);

		_btnMin = dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "min"));
		_btnMin->addTouchEventListener(CC_CALLBACK_2(BuyDialog::submitCallback,this));
		sprintf(str,"%lld",min);
		_btnMin->setTitleText(str);

		_btnOk = dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "ok"));
		_btnOk->addTouchEventListener(CC_CALLBACK_2(BuyDialog::submitCallback,this));

		_btnCancle = dynamic_cast<Button*>(Helper::seekWidgetByName(_widget, "cancel"));
		_btnCancle->addTouchEventListener(CC_CALLBACK_2(BuyDialog::submitCallback,this));

		_planTextAtlas = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(_widget, "money"));


		sprintf(str,"%lld",_total);
		_allMoney->setString(str);

		sprintf(str,"%lld",min);
		_planTextAtlas->setString(str);

		_slider->setPercent((_plan - min) * 1.0f / (max - min));
	}
}
