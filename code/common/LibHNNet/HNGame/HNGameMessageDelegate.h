﻿#ifndef __HN_GameMessageDelegate_H__
#define __HN_GameMessageDelegate_H__

#include "HNBaseType.h"
#include "HNNetProtocol/HNProtocolExport.h"
#include <vector>

namespace HN
{
	
	class IGameMessageDelegate	: public IGameMatchMessageDelegate
								, public IGameChartMessageDelegate
								, public IUserActionMessageDelegate
	{
	public:
		virtual ~IGameMessageDelegate() {}
		// 网络断开
		virtual void onDisConnect() {}
		// 用户同意消息
		virtual void onUserAgreeMessage(MSG_GR_R_UserAgree* agree) = 0;
		// 游戏开始消息
		virtual void onGameStartMessage(BYTE bDeskNO) = 0;
		// 结算消息
		virtual void onGamePointMessage(void * object, INT objectSize) = 0;
		// 游戏结束消息
		virtual void onGameEndMessage(BYTE bDeskNO) = 0;
		// 游戏信息消息
		virtual void onGameInfoMessage(MSG_GM_S_GameInfo* pGameInfo) = 0;
		// 游戏状态消息
		virtual void onGameStationMessage(void* object, INT objectSize) = 0;
		// 游戏消息
		virtual bool onGameMessage(NetMessageHead* messageHead, void* object, INT objectSize) = 0;
	};
}

#endif	//__HN_GameMessageDelegate_H__