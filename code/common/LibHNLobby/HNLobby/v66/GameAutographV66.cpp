﻿#include "GameAutographV66.h"
#include "PlatformResV66.h"
#include "HNLobby/FontConfig.h"
#include "HNLobby/PlatformDefine.h"
#include "HNLobby/GamePrompt.h"
#include "HNLobby/PlatformConfig.h"
#include "HNLobby/PersionalCenter/GameUserDataLayer.h"
#include <string>
//#include "ui/UIEditBox/UIEditBox.h"

static char* BACKGROUND = "v66/set_bank/set/qianming/qianmin.png";   //输入背景框
static char* BUTTON_OK = "v66/button/green/bg.png";
static char* BUTTON_TITLE = "v66/button/green/4.png";

#define WINSIZE Director::getInstance()->getWinSize()

AutoGraphV66::AutoGraphV66()
{
}
AutoGraphV66::~AutoGraphV66()
{
	PlatformLogic()->removeEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_ACCEPT);
	PlatformLogic()->removeEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_NOTACCEPT);
}

bool AutoGraphV66::init()
{
	if (!HNLayer::init())
	{
		return false;
	}

	MSG_GP_R_LogonResult& LogonResult = PlatformLogic()->loginResult;

	auto bg = Sprite::create(BACKGROUND);

	_editName = cocos2d::ui::EditBox::create(bg->getContentSize(), BACKGROUND);
	_editName->setFont(DEFAULT_FONT, 36);
	_editName->setPosition(Point(bg->getContentSize().width* 0.5f, bg->getContentSize().height *0.5f - 60));
	_editName->setFontColor(Color3B::WHITE);
	_editName->setPlaceholderFontName(DEFAULT_FONT);
	_editName->setPlaceholderFontColor(Color4B::WHITE);
	_editName->setPlaceholderFontSize(36);
	_editName->setPlaceHolder(ForceGBKToUtf8(LogonResult.szSignDescr));
	_editName->setMaxLength(15);
	_editName->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
	_editName->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
	_editName->setDelegate(this);
	this->addChild(_editName);


	_ok = AUIButton::create(BUTTON_OK, BUTTON_OK);
	_ok->setTitle(BUTTON_TITLE);
	_ok->setTitleOffset(Vec2(-4, 4));
	_ok->setPosition(Vec2(_editName->getPositionX(), _editName->getPositionY() - _editName->getContentSize().height * 0.5f - _ok->getContentSize().height*0.6 - 10));
	_ok->addTouchEventListener(CC_CALLBACK_2(AutoGraphV66::buttonCallBack, this));
	this->addChild(_ok);

	PlatformLogic()->addEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_ACCEPT, HN_SOCKET_CALLBACK(AutoGraphV66::modifyOKSelector, this));
	PlatformLogic()->addEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_NOTACCEPT, HN_SOCKET_CALLBACK(AutoGraphV66::modifyNoSelector, this));
	PlatformLogic()->addEventSelector(MDM_GP_USERINFO, ASS_GP_USERINFO_NOTACCEPT_BADWORD, HN_SOCKET_CALLBACK(AutoGraphV66::modifyFailureSelector, this));

	return true;
}

void AutoGraphV66::textFieldEvent(Ref *pSender, TextField::EventType type)
{


}

bool AutoGraphV66::modifyOKSelector(HNSocketMessage* socketMessage)
{

	//CCAssert(sizeof (MSG_GP_UserInfo) == socketMessage->objectSize, "MSG_GP_R_BindMobile is error.");
	//if (socketMessage->objectSize != sizeof(MSG_GP_UserInfo)) return true;
	//MSG_GP_UserInfo* pData = (MSG_GP_UserInfo*)socketMessage->object;
	//strcpy(PlatformLogic()->getInstance()->loginResult.szSignDescr, GBKToUtf8(_editName->getText()));


	strcpy(PlatformLogic()->getInstance()->loginResult.szSignDescr, Utf8ToGB(_editName->getText()));

	GamePromptLayer::create()->showPrompt(GBKToUtf8("修改签名成功！"));
	//_editName->setPlaceHolder(GBKToUtf8(PlatformLogic()->loginResult.szSignDescr));
	return false;
}

bool AutoGraphV66::modifyNoSelector(HNSocketMessage* socketMessage)
{
	//CCAssert(sizeof (MSG_GP_UserInfo) == socketMessage->objectSize, "MSG_GP_R_BindMobile is error.");
	//if (socketMessage->objectSize != sizeof(MSG_GP_UserInfo)) return true;
	GamePromptLayer::create()->showPrompt(GBKToUtf8("修改签名失败!"));
	return false;
}

bool AutoGraphV66::modifyFailureSelector(HNSocketMessage* socketMessage)
{
	GamePromptLayer::create()->showPrompt(GetText("Sign_Default"));
	return true;
}

void AutoGraphV66::buttonCallBack(Ref*pShender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		HNAudioEngine::getInstance()->playEffect(GAME_SOUND_BUTTON);
		if (strcmp(_editName->getText(),PlatformLogic()->loginResult.szSignDescr) == 0)
		{
			GamePromptLayer::create()->showPrompt(GBKToUtf8("内容相同请重新输入！！！"));
			return;
		}
		MSG_GP_UserInfo logonResult;
		memset(&logonResult, 0, sizeof(logonResult));

		logonResult.dwUserID = PlatformLogic()->loginResult.dwUserID;
		logonResult.i64Bank = PlatformLogic()->loginResult.i64Bank;
		logonResult.i64Money = PlatformLogic()->loginResult.i64Money;
		//strcpy(logonResult.szSignDescr, Utf8ToGB(_editName->getText()));
		strcpy(logonResult.szSignDescr, Utf8ToGB(_editName->getText()));
		strcpy(logonResult.szMD5Pass, PlatformLogic()->loginResult.szMD5Pass);
		PlatformLogic()->sendData(MDM_GP_USERINFO, ASS_GP_USERINFO_UPDATE_BASE, &logonResult, sizeof(logonResult));
		return;
	}
}
