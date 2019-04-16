﻿//
//  RedPacketMyUserInfo.cpp
//  MixProject_VIP
//
//  Created by 黄百超 on 04/08/2017.
//
//

#include "RedPacketMyUserInfo.h"
#include "HNLobby/v88/PlatformResV88.h"
#include "HNCommon/HNConverCode.h"
#include "HNPlatform/HNPlatformLogic.h"
#include "Tool/Tools.h"

namespace RedPacket {
    
    RedPacketMyUserInfo::RedPacketMyUserInfo() {
        
    }
    
    RedPacketMyUserInfo::~RedPacketMyUserInfo() {
        
    }
    
    bool RedPacketMyUserInfo::init() {
        if (!Layer::init()) {
            return false;
        }
        
        this->setContentSize(WIN_SIZE);
        this->setIgnoreAnchorPointForPosition(false);
        
        resetData();
        createUI();
        
        return true;
    }
    
    void RedPacketMyUserInfo::openAddToParent(Button *parent, cocos2d::Vec2 pos) {
        if (parent) {
            this->setPosition(pos);
            parent->addChild(this);
//            if (m_userName) {
//                m_userName->setString(ForceGBKToUtf8(PlatformLogic()->getInstance()->loginResult.nickName));
//            }
        }
    }
    
    void RedPacketMyUserInfo::closeLayer() {
        this->removeFromParent();
    }
    
    void RedPacketMyUserInfo::updateMyNameAndMoney(std::string name, LLONG money) {
        if (m_userName) {
            m_userName->setString(ForceGBKToUtf8(name.c_str()));
        }
        if (m_userMoney) {
            m_userMoney->setString(Tools::addComma(money));
        }
    }
    
    void RedPacketMyUserInfo::resetData() {
        m_bg = nullptr;
        m_userName = nullptr;
        m_userMoney = nullptr;
    }
    
    void RedPacketMyUserInfo::createUI() {
        m_bg = ImageView::create("v88/fahongbao/8.png");
        if (m_bg) {
            m_bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            m_bg->setPosition(WIN_SIZE/2);
            m_bg->setTouchEnabled(true);
            addChild(m_bg);
            //
            m_userName = Text::create("", FONT_TTF_MSYH, 22);
            if (m_userName) {
                m_userName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
                m_userName->setPosition(Vec2(m_bg->getContentSize().width*0.2f, m_bg->getContentSize().height*0.7f));
                m_userName->setColor(Color3B(72, 72, 72));
                m_bg->addChild(m_userName);
            }
            m_userMoney = Text::create("0", FONT_TTF_FZCY, 22);
            if (m_userMoney) {
                m_userMoney->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
                m_userMoney->setPosition(Vec2(m_bg->getContentSize().width*0.2f, m_bg->getContentSize().height*0.3f));
                m_userMoney->setColor(Color3B(250, 157, 59));
                m_bg->addChild(m_userMoney);
            }
            
        }
    }

    
}
