﻿#ifndef __D21PokerCardV99_h__
#define __D21PokerCardV99_h__

#include "HNNetExport.h"
#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;

/*
0x00 // Back image
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,	// Diamond	A 2 3 4 5 6 7 8 9 10 J Q K
0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,	// Club		A - K
0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,	// Heart	A - K
0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,	// Spade	A - K
0x4E,0x4F //small king, big king
*/
namespace D21
{
	class PokerCardV99 : public Sprite
	{
	public:
		static PokerCardV99* create(BYTE cardValue);
		virtual bool initWithCardValue(BYTE cardValue);

		// 设置牌值 
		void setCardValue(BYTE cardValue);

		// 获取牌值 
		BYTE getCardValue();
		
		// 通过牌值获取相应的图片
		string getCardTextureFileName(BYTE cardValue);

		void playSend(Vec2 endPos, BYTE bValue);
		void FaMingPai(Point pos);
		void FaAnPai(Point pos);
		void FlipPoke();
		void ChangePoke();

		void setEndCallback(std::function<void()> callback);

		std::function<void(void)> _callback;
	protected:
		PokerCardV99();
		~PokerCardV99();
	private:
		BYTE _Value;
	};
}

#endif //__D21PokerCardV99_h__
