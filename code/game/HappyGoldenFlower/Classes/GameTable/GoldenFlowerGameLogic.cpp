#include "GoldenFlowerGameLogic.h"
#include <stdlib.h>

namespace goldenflower
{
#define ARRAY_COUNT(_array)	(sizeof(_array) / sizeof(_array[0]))

	//�˿˶���
	static BYTE	s_CardData[FULL_COUNT] =
	{
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� 2 - A
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� 2 - A
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� 2 - A
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� 2 - A
	};

	GameLogic::GameLogic()
	{
	}

	GameLogic::~GameLogic()
	{
	}

	//�����˿�
	void GameLogic::randCard(BYTE cbCardBuffer[], BYTE cbBufferCount)
	{
		//����׼��
		BYTE cbCardData[ARRAY_COUNT(s_CardData)] = {0};

		//�����˿�
		BYTE cbRandCount = 0, cbPosition = 0;
		do
		{
			cbPosition = rand()%(cbBufferCount-cbRandCount);
			cbCardBuffer[cbRandCount++] = cbCardData[cbPosition];
			cbCardData[cbPosition] = cbCardData[cbBufferCount - cbRandCount];
		} while (cbRandCount < cbBufferCount);
	}

	//��ȡ����
	BYTE GameLogic::getCardType(BYTE cbCardData[], BYTE cbCardCount)
	{
		//����У��
		assert(cbCardCount == MAX_CENTERCOUNT);
		if(cbCardCount != MAX_CENTERCOUNT) return 0;

		//��������
		bool cbSameColor = true, bLineCard = true;
		BYTE cbFirstColor = getCardColor(cbCardData[0]);
		BYTE cbFirstValue = getCardLogicValue(cbCardData[0]);

		//���η���
		for (BYTE i = 1; i < cbCardCount; i++)
		{
			//���ݷ���
			if (getCardColor(cbCardData[i]) != cbFirstColor) cbSameColor = false;
			if (cbFirstValue!=(getCardLogicValue(cbCardData[i])+i)) bLineCard = false;

			//�����ж�
			if ((cbSameColor == false) && (bLineCard == false)) break;
		}

		//��Сͬ��˳
		if((bLineCard == false)&&(cbFirstValue == 14))
		{
			BYTE i=1;
			for( i = 1; i < cbCardCount; i++)
			{
				BYTE cbLogicValue = getCardLogicValue(cbCardData[i]);
				if ((cbFirstValue != (cbLogicValue+i+8))) break;
			}
			if (i == cbCardCount)
			{
				bLineCard = true;
			}
		}

		//�ʼ�ͬ��˳
		if (cbSameColor && bLineCard && (getCardLogicValue(cbCardData[1]) == 13 )) 
			return CT_KING_TONG_HUA_SHUN;

		//˳������
		if (!cbSameColor && bLineCard) 
			return CT_SHUN_ZI;

		//ͬ������
		if (cbSameColor && !bLineCard) 
			return CT_TONG_HUA;

		//ͬ��˳����
		if (cbSameColor && bLineCard)
			return CT_TONG_HUA_SHUN;

		//�˿˷���
		CardAnalyseResult AnalyseResult;
		analysebCardData(cbCardData, cbCardCount, AnalyseResult);

		//�����ж�
		if (AnalyseResult.cbFourCount == 1) 
			return CT_TIE_ZHI;
		if (AnalyseResult.cbLONGCount == 2) 
			return CT_TWO_LONG;
		if ((AnalyseResult.cbLONGCount == 1) && (AnalyseResult.cbThreeCount == 1))
			return CT_HU_LU;
		if ((AnalyseResult.cbThreeCount == 1) && (AnalyseResult.cbLONGCount == 0))
			return CT_THREE_TIAO;
		if ((AnalyseResult.cbLONGCount == 1) && (AnalyseResult.cbSignedCount == 3)) 
			return CT_ONE_LONG;

		return CT_SINGLE;
	}

	//�����˿�
	BYTE GameLogic::getSameCard(const BYTE bCardData[],const BYTE bMaxCard[],BYTE bCardCount,BYTE bMaxCardCount,BYTE bResultData[])
	{
		if(bCardData[0] == 0 || bMaxCard[0]==0)return 0;
		BYTE bTempCount = 0;
		for (BYTE i = 0; i < bCardCount; i++)
		{
			for (BYTE j = 0; j < bMaxCardCount; j++)
			{
				if (bCardData[i] == bMaxCard[j]) bResultData[bTempCount++] = bMaxCard[j];
			}
		}
		return bTempCount;
	}

	//�������
	BYTE GameLogic::fiveFromSeven(BYTE cbHandCardData[],BYTE cbHandCardCount,BYTE cbCenterCardData[],BYTE cbCenterCardCount,BYTE cbLastCardData[],BYTE cbLastCardCount)
	{
		//��ʱ����
		BYTE cbTempCardData[MAX_COUNT + MAX_CENTERCOUNT],cbTempLastCardData[5];
		memset(cbTempCardData, 0x0, sizeof(cbTempCardData));
		memset(cbTempLastCardData, 0x0, sizeof(cbTempLastCardData));

		//��������
		memcpy(cbTempCardData, cbHandCardData, sizeof(BYTE)*MAX_COUNT);
		memcpy(&cbTempCardData[2], cbCenterCardData, sizeof(BYTE)*MAX_CENTERCOUNT);

		//�����˿�
		sortCard(cbTempCardData, ARRAY_COUNT(cbTempCardData));

		memcpy(cbLastCardData,cbTempCardData,sizeof(BYTE)*MAX_CENTERCOUNT);
		BYTE cbCardKind = getCardType(cbLastCardData, sizeof(BYTE)*MAX_CENTERCOUNT);
		BYTE cbTempCardKind = 0;

		//����㷨
		for (int i=0;i<3;i++)
		{
			for (int j= i+1;j<4;j++)
			{
				for (int k = j+1;k<5;k++)
				{
					for (int l =k+1;l<6;l++)
					{
						for (int m=l+1;m<7;m++)
						{
							//��ȡ����
							cbTempLastCardData[0]=cbTempCardData[i];
							cbTempLastCardData[1]=cbTempCardData[j];
							cbTempLastCardData[2]=cbTempCardData[k];
							cbTempLastCardData[3]=cbTempCardData[l];
							cbTempLastCardData[4]=cbTempCardData[m];

							//��ȡ����
							cbTempCardKind = getCardType(cbTempLastCardData,ARRAY_COUNT(cbTempLastCardData));

							//���ʹ�С
							if(compareCard(cbTempLastCardData,cbLastCardData,ARRAY_COUNT(cbTempLastCardData))==2)
							{
								cbCardKind = cbTempCardKind;
								memcpy(cbLastCardData,cbTempLastCardData,sizeof(BYTE) * ARRAY_COUNT(cbTempLastCardData));
							}
						}
					}
				}
			}
		}

		return cbCardKind;
	}

	//�������
	bool GameLogic::selectMaxUser(BYTE bCardData[GAME_PLAYER][MAX_CENTERCOUNT],UserWinList &EndResult,const INT lAddScore[])
	{
		//��������
		memset(&EndResult, 0x0, sizeof(EndResult));

		//First����
		WORD wWinnerID;
		BYTE i = 0;
		for (i = 0; i < GAME_PLAYER; i++)
		{
			if(bCardData[i][0] != 0)
			{
				wWinnerID = i;
				break;
			}
		}

		//����ȫ��
		if(i == GAME_PLAYER)return false;

		//��������û�
		WORD wTemp = wWinnerID;
		for(WORD i=1;i<GAME_PLAYER;i++)
		{
			WORD j=(i+wTemp)%GAME_PLAYER;
			if(bCardData[j][0]==0)continue;
			if(compareCard(bCardData[j],bCardData[wWinnerID],MAX_CENTERCOUNT)>1)
			{
				wWinnerID=j;
			}
		}

		//������ͬ����
		EndResult.wWinerList[EndResult.bSameCount++] = wWinnerID;
		for(WORD i=0;i<GAME_PLAYER;i++)
		{
			if(i==wWinnerID || bCardData[i][0]==0)continue;
			if(compareCard(bCardData[i],bCardData[wWinnerID],MAX_CENTERCOUNT)==false)
			{
				EndResult.wWinerList[EndResult.bSameCount++] = i;
			}
		}

		//��С����
		if(EndResult.bSameCount>1 && lAddScore!=NULL)
		{
			int iSameCount=(int)EndResult.bSameCount;
			while((iSameCount--)>0)
			{
				INT lTempSocre = lAddScore[EndResult.wWinerList[iSameCount]];
				for(int i=iSameCount-1;i>=0;i--)
				{
					assert(lAddScore[EndResult.wWinerList[i]]>0);
					if(lTempSocre < lAddScore[EndResult.wWinerList[i]])
					{
						lTempSocre = lAddScore[EndResult.wWinerList[i]];
						WORD wTemp = EndResult.wWinerList[iSameCount];
						EndResult.wWinerList[iSameCount] = EndResult.wWinerList[i];
						EndResult.wWinerList[i] = wTemp;
					}
				}
			}
		}

		return true;
	}

	//�����˿�
	void GameLogic::sortCard(BYTE cbCardData[], BYTE cbCardCount)
	{
		//ת����ֵ
		BYTE cbLogicValue[FULL_COUNT];
		for (BYTE i=0;i<cbCardCount;i++)
		{
			cbLogicValue[i] = getCardLogicValue(cbCardData[i]);	
		}

		//�������
		bool bSorted = true;
		BYTE cbTempData,bLast=cbCardCount-1;
		do
		{
			bSorted=true;
			for (BYTE i=0;i<bLast;i++)
			{
				if ((cbLogicValue[i]<cbLogicValue[i+1])||
					((cbLogicValue[i]==cbLogicValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
				{
					//����λ��
					cbTempData=cbCardData[i];
					cbCardData[i]=cbCardData[i+1];
					cbCardData[i+1]=cbTempData;
					cbTempData=cbLogicValue[i];
					cbLogicValue[i]=cbLogicValue[i+1];
					cbLogicValue[i+1]=cbTempData;
					bSorted = false;
				}	
			}
			bLast--;
		} while(bSorted==false);

		return;
	}

	//�߼���ֵ
	BYTE GameLogic::getCardLogicValue(BYTE cbCardData)
	{
		//�˿�����
		BYTE bCardColor = getCardColor(cbCardData);
		BYTE bCardValue = getCardValue(cbCardData);

		//ת����ֵ
		return (bCardValue == 1) ? (bCardValue + 13) : bCardValue;
	}

	//�Ա��˿�
	BYTE GameLogic::compareCard(BYTE cbFirstData[], BYTE cbNextData[], BYTE cbCardCount)
	{
		//��ȡ����
		BYTE cbNextType = getCardType(cbNextData,cbCardCount);
		BYTE cbFirstType = getCardType(cbFirstData,cbCardCount);

		//�����ж�
		//��
		if(cbFirstType > cbNextType)
			return 2;

		//С
		if(cbFirstType < cbNextType)
			return 1;

		//������
		switch(cbFirstType)
		{
		case CT_SINGLE:			//����
			{
				//�Ա���ֵ
				BYTE i=0;
				for (i=0;i<cbCardCount;i++)
				{
					BYTE cbNextValue = getCardLogicValue(cbNextData[i]);
					BYTE cbFirstValue = getCardLogicValue(cbFirstData[i]);

					//��
					if(cbFirstValue > cbNextValue)
						return 2;
					//С
					else if(cbFirstValue <cbNextValue)
						return 1;
					//��
					else
						continue;
				}
				//ƽ
				if (i == cbCardCount)
					return 0;
				assert(false);
			}
		case CT_ONE_LONG:		//����
		case CT_TWO_LONG:		//����
		case CT_THREE_TIAO:		//����
		case CT_TIE_ZHI:		//��֧
		case CT_HU_LU:			//��«
			{
				//�����˿�
				CardAnalyseResult AnalyseResultNext;
				CardAnalyseResult AnalyseResultFirst;
				analysebCardData(cbNextData,cbCardCount,AnalyseResultNext);
				analysebCardData(cbFirstData,cbCardCount,AnalyseResultFirst);

				//������ֵ
				if (AnalyseResultFirst.cbFourCount>0)
				{
					BYTE cbNextValue=AnalyseResultNext.cbFourLogicVolue[0];
					BYTE cbFirstValue=AnalyseResultFirst.cbFourLogicVolue[0];

					//�Ƚ�����
					if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;

					//�Ƚϵ���
					assert(AnalyseResultFirst.cbSignedCount==1 && AnalyseResultNext.cbSignedCount==1);
					cbFirstValue = AnalyseResultFirst.cbSignedLogicVolue[0];
					cbNextValue = AnalyseResultNext.cbSignedLogicVolue[0];
					if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;
					else return 0;
				}

				//������ֵ
				if (AnalyseResultFirst.cbThreeCount>0)
				{
					BYTE cbNextValue=AnalyseResultNext.cbThreeLogicVolue[0];
					BYTE cbFirstValue=AnalyseResultFirst.cbThreeLogicVolue[0];

					//�Ƚ�����
					if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;

					//��«����
					if(CT_HU_LU == cbFirstType)
					{
						//�Ƚ϶���
						assert(AnalyseResultFirst.cbLONGCount==1 && AnalyseResultNext.cbLONGCount==1);
						cbFirstValue = AnalyseResultFirst.cbLONGLogicVolue[0];
						cbNextValue = AnalyseResultNext.cbLONGLogicVolue[0];
						if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;
						else return 0;
					}
					else //��������
					{
						//�Ƚϵ���
						assert(AnalyseResultFirst.cbSignedCount==2 && AnalyseResultNext.cbSignedCount==2);

						//ɢ����ֵ
						BYTE i=0;
						for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
						{
							BYTE cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
							BYTE cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
							//��
							if(cbFirstValue > cbNextValue)
								return 2;
							//С
							else if(cbFirstValue <cbNextValue)
								return 1;
							//��
							else continue;
						}
						if( i == AnalyseResultFirst.cbSignedCount)
							return 0;
						assert(false);
					}
				}

				//������ֵ
				BYTE i=0;
				for ( i=0;i<AnalyseResultFirst.cbLONGCount;i++)
				{
					BYTE cbNextValue=AnalyseResultNext.cbLONGLogicVolue[i];
					BYTE cbFirstValue=AnalyseResultFirst.cbLONGLogicVolue[i];
					//��
					if(cbFirstValue > cbNextValue)
						return 2;
					//С
					else if(cbFirstValue <cbNextValue)
						return 1;
					//ƽ
					else
						continue;
				}

				//�Ƚϵ���
				assert( i == AnalyseResultFirst.cbLONGCount);
				{
					assert(AnalyseResultFirst.cbSignedCount==AnalyseResultNext.cbSignedCount
						&& AnalyseResultNext.cbSignedCount>0);
					//ɢ����ֵ
					for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
					{
						BYTE cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
						BYTE cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
						//��
						if(cbFirstValue > cbNextValue)
							return 2;
						//С
						else if(cbFirstValue <cbNextValue)
							return 1;
						//��
						else continue;
					}
					//ƽ
					if( i == AnalyseResultFirst.cbSignedCount)
						return 0;
				}
				break;
			}
		case CT_SHUN_ZI:		//˳��
		case CT_TONG_HUA_SHUN:	//ͬ��˳
			{
				//��ֵ�ж�
				BYTE cbNextValue = getCardLogicValue(cbNextData[0]);
				BYTE cbFirstValue = getCardLogicValue(cbFirstData[0]);

				bool bFirstmin= (cbFirstValue ==(getCardLogicValue(cbFirstData[1])+9));
				bool bNextmin= (cbNextValue ==(getCardLogicValue(cbNextData[1])+9));

				//��С˳��
				if ((bFirstmin==true)&&(bNextmin == false))
				{
					return 1;
				}

				//��С˳��
				else if ((bFirstmin==false)&&(bNextmin == true))
				{
					return 2;
				}

				//��ͬ˳��
				else
				{
					//ƽ
					if(cbFirstValue == cbNextValue)return 0;		
					return (cbFirstValue > cbNextValue)?2:1;			
				}
			}
		case CT_TONG_HUA:		//ͬ��
			{	
				BYTE i = 0;
				//ɢ����ֵ
				for (i = 0; i < cbCardCount; i++)
				{
					BYTE cbNextValue=getCardLogicValue(cbNextData[i]);
					BYTE cbFirstValue=getCardLogicValue(cbFirstData[i]);
					if(cbFirstValue == cbNextValue)continue;
					return (cbFirstValue > cbNextValue)?2:1;
				}
				//ƽ
				if( i == cbCardCount) return 0;
			}
		}

		return  0;
	}

	//�����˿�
	void GameLogic::analysebCardData(const BYTE cbCardData[], BYTE cbCardCount, CardAnalyseResult & AnalyseResult)
	{
		//���ý��
		memset(&AnalyseResult, 0x0, sizeof(AnalyseResult));

		//�˿˷���
		for (BYTE i=0;i<cbCardCount;i++)
		{
			//��������
			BYTE cbSameCount=1;
			BYTE cbSameCardData[4]={cbCardData[i],0,0,0};
			BYTE cbLogicValue=getCardLogicValue(cbCardData[i]);

			//��ȡͬ��
			for (int j=i+1;j<cbCardCount;j++)
			{
				//�߼��Ա�
				if (getCardLogicValue(cbCardData[j])!=cbLogicValue) break;

				//�����˿�
				cbSameCardData[cbSameCount++]=cbCardData[j];
			}

			//������
			switch (cbSameCount)
			{
			case 1:		//����
				{
					AnalyseResult.cbSignedLogicVolue[AnalyseResult.cbSignedCount]=cbLogicValue;
					memcpy(&AnalyseResult.cbSignedCardData[(AnalyseResult.cbSignedCount++)*cbSameCount],cbSameCardData,cbSameCount);
					break;
				}
			case 2:		//����
				{
					AnalyseResult.cbLONGLogicVolue[AnalyseResult.cbLONGCount]=cbLogicValue;
					memcpy(&AnalyseResult.cbLONGCardData[(AnalyseResult.cbLONGCount++)*cbSameCount],cbSameCardData,cbSameCount);
					break;
				}
			case 3:		//����
				{
					AnalyseResult.cbThreeLogicVolue[AnalyseResult.cbThreeCount]=cbLogicValue;
					memcpy(&AnalyseResult.cbThreeCardData[(AnalyseResult.cbThreeCount++)*cbSameCount],cbSameCardData,cbSameCount);
					break;
				}
			case 4:		//����
				{
					AnalyseResult.cbFourLogicVolue[AnalyseResult.cbFourCount]=cbLogicValue;
					memcpy(&AnalyseResult.cbFourCardData[(AnalyseResult.cbFourCount++)*cbSameCount],cbSameCardData,cbSameCount);
					break;
				}
			}

			//���õ���
			i+=cbSameCount-1;
		}

		return;
	}
}


//////////////////////////////////////////////////////////////////////////
