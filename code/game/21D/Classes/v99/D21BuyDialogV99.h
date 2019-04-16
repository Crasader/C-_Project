#ifndef __D21BuyDialogV99_h__
#define __D21BuyDialogV99_h__

#include "HNNetExport.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "UI/HNDialogBase.h"

using namespace cocostudio;
using namespace ui;
USING_NS_CC;

namespace D21
{
	class BuyDialogV99 : public HNDialogBase
	{
	public:
		/**
		* create a buy dialog.
		* @param parent parent node.
		* @param max allow buy max. 
		* @param min allow buy min.
		* @param plan default buy.
		* @param total user account.
		*/
		static BuyDialogV99* create(cocos2d::Node* parent, LLONG max, LLONG min, LLONG plan, LLONG total, BYTE deskStation);
		bool init(cocos2d::Node* parent, LLONG max, LLONG min, LLONG plan, LLONG total, BYTE deskStation);
	protected:
		void sliderChangedCallback(cocos2d::Ref* pRef, ui::Slider::EventType eventType);
		void submitCallback(cocos2d::Ref*, ui::Widget::TouchEventType);
		bool onTouchBegan(Touch *touch, Event *unused_event);

	private:
		BuyDialogV99():_max(0), _min(0), _plan(0), _total(0) {}
		virtual ~BuyDialogV99() {}
		void sendMoneyPlan();
		void resetLayout();
		void sendStandUp();
	private:
		LLONG _max;
		LLONG _min;
		LLONG _plan;
		LLONG _total;
		BYTE _deskStation;

		Widget* _widget;
		Slider* _slider;

		TextAtlas* _allMoney;
		Button* _btnMax;
		Button* _btnMin;
		Button* _btnOk;
		Button* _btnCancle;
		TextAtlas* _planTextAtlas;
	};
}

#endif //__D21BuyDialogV99_h__


