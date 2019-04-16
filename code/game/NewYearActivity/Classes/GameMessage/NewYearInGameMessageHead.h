#pragma  once
#include <memory.h>
//#include "HNNetExport.h"
#include "HNBaseType.h"
#include "NSAnimationTool.h"

namespace NewYearActivityInGame
{

enum{
	S2C_SHOW_NIANSHOU_MSG = 150,				//���޳���
	S2C_DRIVE_NIANSHOU_RESULT = 151,			//�����޻�ý��
	S2C_MATCH_GAIN_BANGER_MSG = 152,			//�Ծֻ�ñ���

	C2S_DRIVE_NIANSHOUR_REQUEST = 190,			//����������
};
    
    const static int NianShouZOrder = 99999;
    const static Vec2 NianShouButtonPosition = Vec2(1080, 250);

//����������
struct GanNianShouRequest
{
	int		nUserID;			//���id
	BYTE	bPropType;			//��������0~2
	BYTE	bSceneType;			//ʹ������0~1
	GanNianShouRequest()
	{
		::memset(this, 0, sizeof(GanNianShouRequest));
	}
};

//�����޽��֪ͨ
struct GanNianShouRlt
{
	int				nUserID;			//��ұ��
	long long			nRewardMoney;		//�����޻�õĽ������
	GanNianShouRlt()
	{
		::memset(this, 0, sizeof(GanNianShouRlt));
	}
};

//�Ծֻ�ñ�����֪ͨ //ÿ��һ������
struct MatchFireCrackerRlt
{
	int				nUserID;			//��ұ��
	MatchFireCrackerRlt()
	{
		::memset(this, 0, sizeof(MatchFireCrackerRlt));
	}
};

}
