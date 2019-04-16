﻿#ifndef __THIRTEENZHANG_CardSprite_V88_H__
#define __THIRTEENZHANG_CardSprite_V88_H__

//#include "cocos2d.h"
//#include "HNNetExport.h"
#include "UI/Base/HNSprite.h"
#include "HNBaseType.h"
#include <string>
//USING_NS_CC;

/*
 0x00 // Back image
 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,	// Diamond	2 3 4 5 6 7 8 9 10 J Q K A
 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,	// Club		2 - A
 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,	// Heart	2 - A
 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,	// Spade	2 - A
 0x4E,0x4F //small king, big king
 */

namespace ThirteenZhang
{
    class CardSpriteV88 : public Sprite
    {
    public:
        static CardSpriteV88* create(BYTE cardValue);
        
    public:
        virtual bool initWithCardValue(BYTE cardValue);
        
    public:
        void setValue(BYTE cardValue);
        BYTE getValue() const;
        
        // set the color card to gray. Works only for the back-card 0x00
        void setGray(bool gray);
        
    public:
        static std::string getCardTextureFileName(BYTE cardValue);
        
    protected:
        CardSpriteV88();
        virtual ~CardSpriteV88();
        
    private:
        BYTE _cardValue;	
    };
}



#endif // !__THIRTEENZHANG_CardSpriteV88_H__
