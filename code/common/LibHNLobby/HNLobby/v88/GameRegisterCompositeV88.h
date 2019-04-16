﻿#ifndef GameRegisterCompositeV88_h
#define GameRegisterCompositeV88_h

#include "HNNetExport.h"
//#include "HNUIExport.h"
//#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UICheckBox.h"
#include "../pattern/factory/gameRegister/IGameRegister.h"
#include "UI/HNEditBox.h"
#include "UI/Base/AUIButton.h"

//USING_NS_CC;

using namespace cocostudio;
using namespace ui;
using namespace HN;

class GameRegisterCompositeV88 : public IGameRegister, public ui::EditBoxDelegate {
public:
    CREATE_FUNC(GameRegisterCompositeV88);

public:
    GameRegisterCompositeV88();
    virtual ~GameRegisterCompositeV88();

    virtual bool init() override;

private:
    struct REGIST_NODE {
        CheckBox*	manCheckBox;
        CheckBox*	womanCheckBox;
        HNEditBox*	accountEdit;
//        HNEditBox*	nickEdit;
        HNEditBox*	passwordEdit;
        HNEditBox*	pwCheckEdit;
        HNEditBox*  inviteCodeEdit;
        AUIButton*		registerBtn;
        Button*		backBtn;
        Node*		node;
    } _regist_node;

    std::string	_userName;
    std::string	_userPassword;
    std::string _visiblePassword;

    BYTE				_gender;

    virtual void initRegisterUI() override;

private:
    void closeClickCallback(Ref* pSender, Widget::TouchEventType type);
    void registerClickCallback(Ref* pSender, Widget::TouchEventType type);
    void resetClickCallBack(Ref* pSender, Widget::TouchEventType type);
    // 复选框回调函数
    void checkBoxCallback(Ref* pSender,CheckBox::EventType type);
    //协议
    void AgreeClickCallBack(Ref* pSender, Widget::TouchEventType type);


    virtual void editBoxReturn(ui::EditBox* editBox)override {};

    void editBoxEditingDidEnd(ui::EditBox* editBox) override;
    void editBoxTextChanged(ui::EditBox* editBox, const std::string& text) override;

};

#endif /* GameRegisterCompositeV88_h */
