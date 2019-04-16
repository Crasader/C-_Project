
#ifndef  __BRXJ_MESSAGEHEAD_H__
#define __BRXJ_MESSAGEHEAD_H__

#include <memory.h>
#include "HNNetExport.h"
#pragma pack(1)
namespace BRXJ
{

	enum COMMOND
	{
		//��Ϸ��Ϣ
		GAME_KIND_ID								= 1,
		GAME_NAME_ID							= 11100600,				 // ���� ID
		PLAY_COUNT								= 180,						// ��Ϸ����


		//��Ϸ�ڲ������汾��
		DEV_HIGH_VERSION						= 2,							// �ڲ������߰汾��(ÿ����һ��LOW_VERSIONG+1)
		DEV_LOW_VERSION						= 0,							// �ڲ������Ͱ汾��

		//ׯ������
		BANKER_INDEX								= 0,							//ׯ������
		SHUN_MEN_INDEX						= 1,							//˳������
		DUI_MEN_INDEX							= 2,							//��������
		DAO_MEN_INDEX							= 3,							//��������
		MAX_INDEX									= 3,							//�������

		//��Ϸ��
		MAX_NOTE_COUNT						= 3,							//�����ע����
		USER_HAND_CARD_COUNT			= 2,							//�û����е���
		GAME_XIPAI_COUNT						= 72,							//һ��ϴ�ƴ���
		GAME_SAVE_COUNT						= 72,							//����·�Ӱ���

		//��ϢID
		ASS_XIA_ZHU_FINISH						= 32,							//��ע����
		ASS_NO_XIA_ZHU							= 33,							//��ֹ��ע
		ASS_SEND_CARD_FINISH				= 34,							//���ƽ���
		ASS_SHOW_CARD							= 35,							//��ʾ���ƽ��
		ASS_NEW_TURN							= 36,							//��ʼ��һ��

		S_C_IS_SUPER_USER						= 78,							//�����û���Ϣ
		C_S_SUPER_SET								= 79,							//��������
		S_C_SUPER_SET_RESULT					= 80,							//�������ý��

		C_S_APPLY_ZHUANG						= 90,							//��������ׯ
		S_C_APPLY_ZHUANG_RESULT			= 91,							//��������ׯ���
		C_S_XIA_ZHU									= 92,							//�����ע
		S_C_XIA_ZHU_RESULT					= 93,							//�����ע���

		S_C_NO_NT_WAITE						= 100,						//֪ͨ��ׯ�ȴ�
		S_C_NOTICE_XIA_ZHU					= 101,						//֪ͨ��ע��Ϣ
		S_C_SEND_CARD							= 102,						//������Ϣ
		S_C_NO_XIAZHU							= 103,						//��ֹ��ע
		S_C_SHOW_WINAREA					= 104,						//��ʾ�н�������Ϣ
		S_C_GAME_END							= 105,						//��Ϸ����
		S2C_TIP_EXIT_MSG						= 106,						//ǿ���˳�
		// ��Ϸ״̬����
		GS_WAIT_SETGAME						= 0,							// ��ׯ�ȴ�
		GS_WAIT_AGREE							= 1,							// �ȴ�ͬ������
		GS_NOTE_STATE							= 20,							// ��ע״̬
		GS_SEND_CARD							= 21,							// ����״̬
		GS_SHOW_WIN								= 22,							// ��ʾ�н�����
		GS_WAIT_NEXT								= 23							// �ȴ���һ�̿�ʼ

	};



	struct	TGameLuzi
	{
		int		iShangMen;
		int		iTianMen;
		int		iXiaMen;
		TGameLuzi()
		{
			memset(this, 0, sizeof(TGameLuzi));
		}
	};
	/*--------------------------------------------------------------------------*/
	//��Ϸ״����̬��
	struct TGameStationBase
	{
		BYTE			byZhuangList[PLAY_COUNT];					 //��ׯ�б�	
		int				iXiaZhuTime;											 // ��עʱ��					
		int				iKaiPaiTime;     										 // ����ʱ��    
		int				iFreeTime;												 // ����ʱ��	
		int				iShowWinTime;										 // ��ʾ�н�ʱ��
		int				iRemaindTime;										 // �׶�ʣ��ʱ��
																					 
		int				iNtStation;												 //ׯ��λ��
		int				iNtPlayCount;											 //ׯ����ׯ����
		LLONG		i64NtMoney;											 //ׯ�ҽ��
		LLONG		i64NtWinMoney;									 //ׯ����Ӯ���
																					 
		LLONG		i64UserWin;											 //������Ӯ
		LLONG		i64MyMoney;										 //���˽���� -�ӷ���˷��͹�ȥ
																					 
		LLONG		i64UserMaxNote;									 //��������ע��
		LLONG		i64ShangZhuangLimit;							 // ��ׯ��Ҫ�����ٽ��	
		LLONG		i64ChouMaValues[6];								 //6������ֵ

		LLONG     i64RemainBetNum;									 //ʣ�������ע��
		TGameLuzi	tGameLuzi[GAME_SAVE_COUNT];		 //·����Ϣ


		TGameStationBase()
		{
			memset(this, 0, sizeof(TGameStationBase));
			memset(byZhuangList, 255, sizeof(byZhuangList));
		}
	};

	/*--------------------------------------------------------------------------*/
	//��Ϸ��ע״̬��
	struct TGameStationBase_Note
	{
		BYTE			byZhuangList[PLAY_COUNT];							//��ׯ�б�	
		int				iXiaZhuTime;													// ��עʱ��					
		int				iKaiPaiTime;     												// ����ʱ��    
		int				iFreeTime;														// ����ʱ��	
		int				iShowWinTime;												// ��ʾ�н�ʱ��
		int				iRemaindTime;												// �׶�ʣ��ʱ��

		int				iNtStation;														//ׯ��λ��
		int				iNtPlayCount;													//ׯ����ׯ����
		LLONG		i64NtMoney;													//ׯ�ҽ��
		LLONG		i64NtWinMoney;											//ׯ����Ӯ���

		LLONG		i64UserWin;													//������Ӯ
		LLONG		i64MyMoney;												//���˽���� -�ӷ���˷��͹�ȥ

		LLONG		i64UserMaxNote;											//��������ע��
		LLONG		i64ShangZhuangLimit;									// ��ׯ��Ҫ�����ٽ��	
		LLONG		i64ChouMaValues[6];										//6������ֵ

		LLONG		i64QuYuZhuTrue[MAX_NOTE_COUNT];			//��ʵ��ҵ���עֵ
		LLONG		i64QuYuZhu[MAX_NOTE_COUNT];					// ����ÿ�������µ�ע��
		LLONG     i64UserXiaZhu[MAX_NOTE_COUNT];				//�����ע���	

		LLONG     i64RemainBetNum;											//ʣ�������ע��
		TGameLuzi	tGameLuzi[GAME_SAVE_COUNT];				//·����Ϣ


		TGameStationBase_Note()
		{
			memset(this, 0, sizeof(TGameStationBase_Note));
			memset(byZhuangList, 255, sizeof(byZhuangList));
		}
	};
	/*--------------------------------------------------------------------------*/
	//��Ϸ����״̬��
	struct TGameStationBase_SendCard
	{
		BYTE		byZhuangList[PLAY_COUNT];								//��ׯ�б�	
		BYTE		byUserCard[4][2];												//������				
		BYTE		byCardCount[4];												//������
		int			iCardShape[4];													//���͵���
		int			iXiaZhuTime;														// ��עʱ��					
		int			iKaiPaiTime;     													// ����ʱ��    
		int			iFreeTime;															// ����ʱ��	
		int			iShowWinTime;													// ��ʾ�н�ʱ��
		int			iRemaindTime;													// �׶�ʣ��ʱ��

		int				iNtStation;														//ׯ��λ��
		int				iNtPlayCount;													//ׯ����ׯ����
		LLONG		i64NtMoney;													//ׯ�ҽ��
		LLONG		i64NtWinMoney;											//ׯ����Ӯ���

		LLONG		i64UserWin;													//������Ӯ
		LLONG		i64MyMoney;												//���˽���� -�ӷ���˷��͹�ȥ

		LLONG		i64UserMaxNote;											//��������ע��
		LLONG		i64ShangZhuangLimit;									// ��ׯ��Ҫ�����ٽ��	
		LLONG		i64ChouMaValues[6];										//6������ֵ

		LLONG		i64QuYuZhuTrue[MAX_NOTE_COUNT];			//��ʵ��ҵ���עֵ
		LLONG		i64QuYuZhu[MAX_NOTE_COUNT];					// ����ÿ�������µ�ע��
		LLONG     i64UserXiaZhu[MAX_NOTE_COUNT];				//�����ע���	

		LLONG     i64RemainBetNum;											//ʣ�������ע��

		TGameLuzi	tGameLuzi[GAME_SAVE_COUNT];				//·����Ϣ


		TGameStationBase_SendCard()
		{
			memset(this, 0, sizeof(TGameStationBase_SendCard));
			memset(byZhuangList, 255, sizeof(byZhuangList));
		}
	};
	/*--------------------------------------------------------------------------*/
	//��Ϸ��ʾ�н�����״̬��
	struct TGameStationBase_ShowWin
	{
		BYTE		byZhuangList[PLAY_COUNT];							//��ׯ�б�	
		BYTE		byUserCard[4][2];											//������				
		BYTE		byCardCount[4];											//������
		int			iCardShape[4];												//���͵���
		int			iCompareResult[4];										//�н�����
		int			iXiaZhuTime;													// ��עʱ��					
		int			iKaiPaiTime;     												// ����ʱ��    
		int			iFreeTime;														// ����ʱ��	
		int			iShowWinTime;												// ��ʾ�н�ʱ��
		int			iRemaindTime;												// �׶�ʣ��ʱ��

		int				iNtStation;													//ׯ��λ��
		int				iNtPlayCount;												//ׯ����ׯ����
		LLONG		i64NtMoney;												//ׯ�ҽ��
		LLONG		i64NtWinMoney;										//ׯ����Ӯ���

		LLONG		i64UserWin;												//������Ӯ
		LLONG		i64MyMoney;											//���˽���� -�ӷ���˷��͹�ȥ

		LLONG		i64UserMaxNote;										 //��������ע��
		LLONG		i64ShangZhuangLimit;								 // ��ׯ��Ҫ�����ٽ��	
		LLONG		i64ChouMaValues[6];									 //6������ֵ

		LLONG		i64QuYuZhuTrue[MAX_NOTE_COUNT];		 //��ʵ��ҵ���עֵ
		LLONG		i64QuYuZhu[MAX_NOTE_COUNT];				 // ����ÿ�������µ�ע��
		LLONG     i64UserXiaZhu[MAX_NOTE_COUNT];			 //�����ע���	
																						 
		LLONG     i64RemainBetNum;										 //ʣ�������ע��
		TGameLuzi	tGameLuzi[GAME_SAVE_COUNT];			 //·����Ϣ


		TGameStationBase_ShowWin()
		{
			memset(this, 0, sizeof(TGameStationBase_ShowWin));
			memset(byZhuangList, 255, sizeof(byZhuangList));
		}
	};
	/*--------------------------------------------------------------------*/
	struct	C_S_UserNote
	{
		BYTE	byDeskStation;
		int		iChouMaType;												//��������
		int		iNoteArea;														//��ע����
		C_S_UserNote()
		{
			byDeskStation = -1;
			iChouMaType = -1;
			iNoteArea = -1;

		}
	};
	/*--------------------------------------------------------------------*/
	struct	C_S_UserNoteResult
	{
		int				iArea;
		LLONG		i64Money;
		LLONG		i64ZhongZhu;												// ���ѵ�ǰ��ע��
		LLONG		i64QuYuZhuTrue[MAX_NOTE_COUNT];			//��ʵ��ҵ���עֵ
		LLONG		i64QuYuZhu[MAX_NOTE_COUNT];					// ����ÿ�������µ�ע��
		LLONG     i64UserXiaZhuData[MAX_NOTE_COUNT];		//�����ע���

		LLONG     i64RemainBetNum;        //ʣ�������ע��
		C_S_UserNoteResult()
		{
			memset(this, 0, sizeof(C_S_UserNoteResult));
		}
	};
	/*--------------------------------------------------------------------*/
	struct	S_C_GameResult
	{
		BYTE			byZhuangList[PLAY_COUNT];							//��ׯ�б�
		LLONG		i64NtScore;													//ׯ�ҵ÷�
		LLONG		i64UserScore;												//�мҵ÷�

		LLONG		i64NtWin;														//ׯ����Ӯ�ɼ�
		LLONG		i64NtMoney;													//ׯ�ҵĽ������

		LLONG		i64UserWin;													//�����Ӯ
		LLONG		i64UserMoney;												//�������Ľ��

		TGameLuzi	tGameLuzi[GAME_SAVE_COUNT];				//·����Ϣ	
		S_C_GameResult()
		{
			memset(this, 0, sizeof(S_C_GameResult));
		}
	};
	/*--------------------------------------------------------------------*/
	//��ׯ�ȴ���Ϣ
	struct	S_C_NoNtStation
	{
		int			iNowNtStation;										///��ǰׯ�ҵ�λ��
		int			iNtPlayCount;											//ׯ����ׯ����
		LLONG		i64NtMoney;										//ׯ�ҽ��
		LLONG		i64NtWinMoney;								//ׯ����Ӯ���
		S_C_NoNtStation()
		{
			iNowNtStation = -1;										//��ǰׯ�ҵ�λ��
			iNtPlayCount = 0;											//ׯ����ׯ����
			i64NtMoney = 0;											//ׯ�ҽ��
			i64NtWinMoney = 0;										//ׯ����Ӯ���
		}
	};
	/*--------------------------------------------------------------------------*/
	///��Ϸ��ʼ��Ϣ
	struct S_C_BeginData
	{
		BYTE			byZhuangList[PLAY_COUNT];				//��ׯ�б�

		int				iGameCount;										//��ǰ�Ѿ������˼���
		int				iGameBeen;										//��ǰ����
		int				iNowNtStation;									//��ǰׯ�ҵ�λ��
		int				iNtPlayCount;										//ׯ����ׯ����
		LLONG		i64NtMoney;										//ׯ�ҽ��
		LLONG		i64NtWinMoney;								//ׯ����Ӯ���
		LLONG		i64UserMoney;									//�������Ľ������

		LLONG		i64PerMaxNotes;								// ���������ע��ע
		LLONG     i64RemainBetNum;								//ʣ�������ע��
		S_C_BeginData()
		{
			memset(this, 0, sizeof(S_C_BeginData));
			iNowNtStation = -1;
			memset(byZhuangList, 255, sizeof(byZhuangList));
		}
	};
	/*---------------------------------------------------------------*/
	//�������ݰ�
	struct S_C_SendCard
	{
		int		iKaiPaiTime;					//����ʱ��
		BYTE	byUserCard[4][2];
		BYTE	byCardCount[4];
		int		iCardShape[4];				//���͵���
		S_C_SendCard()
		{
			memset(this, 0, sizeof(S_C_SendCard));
		}
	};
	/*---------------------------------------------------------------*/
	//�������ݰ�
	struct S_C_NoXiaZhu
	{
		bool	bCanXiaZhu;					//�Ƿ������ע
		S_C_NoXiaZhu()
		{
			memset(this, 0, sizeof(S_C_NoXiaZhu));
		}
	};
	/*--------------------------------------------------------------------------*/
	//�н��������ݰ�
	struct S_C_ShowWinAreas
	{
		int		iCompareResult[4];		//�н�����
		S_C_ShowWinAreas()
		{
			memset(this, 0, sizeof(S_C_ShowWinAreas));
		}
	};
	/*--------------------------------------------------------------------------*/
	//������ׯ���ݰ�
	struct C_S_ApplyShangZhuang
	{
		bool	bShangZhuang;
		C_S_ApplyShangZhuang()
		{
			memset(this, 0, sizeof(C_S_ApplyShangZhuang));
		}
	};
	/*--------------------------------------------------------------------------*/
	//������ׯ���ݰ�
	struct S_C_ApplyZhuangResult
	{
		bool			bXiaZhuang;										//�Ƿ�ׯ��������ׯ
		BYTE			bIsSuccess;										//������ׯ�Ƿ�ɹ���0�ɹ���1����ׯ���б�2��Ҳ���)
		BYTE			byDeskStation;									//��������
		BYTE			byZhuangList[PLAY_COUNT];
		int				iNowNtStation;									//ׯ��λ��
		int				iZhuangBaShu;									//ׯ�Ұ���
		LLONG		i64NtMoney;										//��ҽ������
		LLONG		i64NtWin;											//��ǰׯ��Ӯ�Ľ�� 

		S_C_ApplyZhuangResult()
		{
			memset(byZhuangList, 255, sizeof(byZhuangList));
			iNowNtStation = -1;
			iZhuangBaShu = 0;
			i64NtMoney = 0;
			i64NtWin = 0;
			bXiaZhuang = false;
			bIsSuccess = 255;
			byDeskStation = 255;
		}
	};
	/*------------------------------------------------------------------------------*/
	/// ֪ͨ�ͻ����Ƿ�Ϊ�����ͻ���״̬��Ϣ�ṹ
	struct S_C_IsSuperUser
	{
		BYTE byDeskStation;      /**< ���λ�� */
		bool bEnable;           /**< �Ƿ�ͨ */
		S_C_IsSuperUser()
		{
			memset(this, 0, sizeof(S_C_IsSuperUser));
		}
	};
	/*------------------------------------------------------------------------------*/
	struct SuperUserSetData
	{
		bool	bSetSuccese;		//�Ƿ����óɹ���
		int		iSetResult[4];

		SuperUserSetData()
		{
			memset(this, 0, sizeof(SuperUserSetData));
		}
	};

	struct tag_s2c_tip_exit
	{
		BYTE	bIsExit;
		LLONG	i64Money;
		tag_s2c_tip_exit()
		{
			bIsExit = 255;
			i64Money = 0;
		}
	};
	/*--------------------------------------------------------------------------*/

}
#pragma pack()
#endif