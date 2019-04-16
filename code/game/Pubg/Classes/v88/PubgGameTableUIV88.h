﻿
#ifndef PubgGameTableUIV88_h
#define PubgGameTableUIV88_h

#include <string>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "Pubg/Classes/GameTable/PubgGameTableUICallback.h"
//#include "UI/Base/AUIButton.h"
//#include "../../TTNN/Classes/v88/BRNNClockV88.h"
#include "Pubg/Classes/GameTable/PubgGameTableLogic.h"
//#include "TigerGuessSizeV88.h"
#include "PubgSettlementV88.h"
//#include "TigerMaryTableUIV88.h"
#include "HNLobby/GameNotice.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocostudio;
using namespace ui;

namespace Pubg {

	class GameTableLogic;
    
	class GameTableUIV88 : public GameTableUICallback {

        struct Root_UI {
            ImageView*  bg;
            ImageView*  poolBg;
            Text*       poolText;
            Node*       middleNode;
            Node*       topNode;
            Node*       bottomNode;
            Button*     startBtn;
            Button*     autoBtn;
            Button*     cancelBtn;
            Button*     maxNote;
            Button*     maxLine;
            Button*     nineLine;
            Button*     addNote;
            Button*     addLine;
            Button*     subLine;
            Text*       myName;
			Text*       myID;
            Text*       myMoney;
            Text*       score;
            Text*       jackpot;
            Text*       addLineCount;
            Text*       addNoteCount;
            Node*       freeTurn;       // 免费次数界面
            Layout*     panelBg;
            ImageView*  bigMirror;//大瞄准镜
            ImageView*  smallMirror;//小瞄准镜
            ImageView*  bigKillModeBg;//大逃杀模式背景
            ImageView*  bigKillNumBg;//大逃杀击杀人数统计背景
            Text*       bigKillNum;//大逃杀击杀人数
            Root_UI() {
                bg = nullptr;
                poolBg = nullptr;
                poolText = nullptr;
                middleNode = nullptr;
                topNode = nullptr;
                bottomNode = nullptr;
                startBtn = nullptr;
                autoBtn = nullptr;
                cancelBtn = nullptr;
                maxNote = nullptr;
                maxLine = nullptr;
                nineLine = nullptr;
                addNote = nullptr;
                addLine = nullptr;
                subLine = nullptr;
                myName = nullptr;
                myMoney = nullptr;
                score = nullptr;
                jackpot = nullptr;
                addLineCount = nullptr;
                addNoteCount = nullptr;
                freeTurn = nullptr;
                panelBg = nullptr;
                bigMirror = nullptr;
                smallMirror = nullptr;
                bigKillModeBg = nullptr;
                bigKillNumBg = nullptr;
                bigKillNum = nullptr;
            }
            
            void EnableButtons(bool flag)
            {
                if (maxNote != nullptr)
                {
                    maxNote->setTouchEnabled(flag);
                    maxNote->setBright(flag);
                }

                if (addNote != nullptr)
                {
                    addNote->setTouchEnabled(flag);
                    addNote->setBright(flag);
                }

                if (addLine != nullptr)
                {
                    addLine->setTouchEnabled(flag);
                    addLine->setBright(flag);
                }

                if (subLine != nullptr)
                {
                    subLine->setTouchEnabled(flag);
                    subLine->setBright(flag);
                }

                if (maxNote != nullptr)
                {
                    startBtn->setTouchEnabled(flag);
                    startBtn->setBright(flag);
                }
            }
        } _root;
        
        bool m_bAuto;
        bool m_bHasCashIn;
        bool m_bGameFinished;       // 游戏已完成
        bool m_bAnimationFinished;  // 动画已播放完
        long long m_i64WinMoney;    // 当前奖励
        
        bool    m_autoRotation;         //自己转动图标
        int     m_autoRotationTime;     //自己转动图标计算的时间
        
        bool m_bAirDrop;
        bool m_bFirstMod;  //普通模式
        bool m_bFinalMode;  //大逃杀模式
        bool m_bFinishFinalMode; //结束大逃杀
        int  m_bFinalModelNum; //大逃杀摇奖次数
	public:
		GameTableLogic*			_GameTableLogic;

		//////////////////////////////////////////////////////////////////////////
	public:
		GameTableUIV88();
		~GameTableUIV88();
		static HNGameUIBase* create(BYTE bDeskIndex, bool bAutoCreate);

		bool init(BYTE bDeskIndex, bool bAutoCreate);

		virtual bool onTouchBegan(Touch* touch, Event* event) override;
		virtual void onEnter() override;
		virtual void onExit() override;

		virtual void onExitTransitionDidStart() override;
        
        //
        //消息同步
        virtual void leaveTheGame() override;
        //玩家坐下
        virtual void userSitDown(MSG_GR_R_UserSit * userSit, UserInfoStruct* user) override;
        //玩家站起
        virtual void userUp(MSG_GR_R_UserSit * userSit, UserInfoStruct* user) override;
        //添加用户
        virtual void addUser(BYTE seatNo, bool bMe) override;

        //
        //
        virtual void dealGameState(struct_s2c_game_state* msg) override;
        //
        virtual void dealGameBaseInfo(struct_s2c_base_info* msg) override;
        //
        virtual void dealGameBegin(struct_s2c_game_begin* msg) override;
        //
        virtual void dealGameFinish(struct_s2c_game_finish* msg) override;
        //提醒退出
        virtual void onGameTipExit(tag_s2c_tip_exit* msg) override;
        virtual void dealGameFreeCount(struct_s2c_free_count * msg) override;
        
        virtual void dealGameFinalMode(struct_s2c_finalmode_result *msg)override;
        //
        void setNick(char* nick);
        //
		void updatePlayerInfo();
        
        virtual void closeLoadingCallBack() override;
        

		//数据
	public:
        long long           m_i64TipMoney;
//        int                 m_GameStatus;
		PubgSettlementV88*    _gameSettlement;
        unsigned int        m_audioEffectID;
        
//        Node*               root;
        Text*               m_TextTip;
        
		long long		    i64Reward;		//当局奖金
		long long		    i64MyMoney;		//背包金币

		int 				nOpenLotteryType[LOTTERY_COUNT_Pubg];			//服务端发送的15个图标
        int                 nOpenLotteryTypeColRow[LOTTERY_COLUMN_COUNT][4];


        vector<Layout*>             m_vPanelTurnArea;
        vector<vector<ImageView*>>  m_vTurnIcon;
        vector<Vec2>                m_vTurnIconPos;
        vector<int>                 m_vTurnUnitCount;           //转多少个icon单元
        int                         m_nHasTurnUnitCount;        //已经转的单元
        float                       m_fTurnUnitTime;            //每个单元时间
        
        ImageView*              m_vAllLines[LINE_COUNT];        //九条线
        int                     m_currentMaxLine;               //当前压的最大的线
        int                     lineResultNumData[LINE_COUNT];  //每条线的中奖水果，-1是不中奖
        int                     nOpenLinePrizeType[LINE_COUNT];         //每条线的奖品类型：倍率、免费次数、奖池比率
        int                     nOpenLineCount[LINE_COUNT];             //每条线连格的个数：2、3、4、5连     *N
        int                     nOpenLineRate[LINE_COUNT];              //每条线的得奖倍率（or免费次数or奖池比率） 倍数
        
        //基础信息同步
//        long long i64MyMoney;
        long long i64NoteUnit;                      //加注单位
        long long i64NoteMin;                       //每条线最少压注值
        long long i64NoteMax;                       //每条线最大压注值
        long long i64Jackpot;                       //当前奖池
        long long m_currentNoteValue;               //当前押注值
        
        
        
        int nGunsignPositionSmall;  //小瞄准镜
        int nGunsignPositionBig;    //大瞄准镜
        
        int nkillCount; //大逃杀总共击杀人数
        
    private:
        void initData();
        void resetUINewGame();
        void resetData();
        
		//侧边栏
		void createToolBarUI();
		//大厅底节点
		void createRootLayer();
        //create turn
        void loadTurn();
        //create settlement layer
        void createGameSettlementLayer();

		tag_s2c_tip_exit*	tipMsg;
		void tipCallback();
		void updateTip(float dt);

	private:
		//按钮回调
		void addLineBtnCallBack(Ref* pSender, Widget::TouchEventType type);     //加线回调
        void subLineBtnCallBack(Ref* pSender, Widget::TouchEventType type);     //
		void maxLineBtnCallBack(Ref* pSender, Widget::TouchEventType type);     //满线回调
        void nineLineBtnCallBack(Ref* pSender, Widget::TouchEventType type);
        
        void addNoteBtnCallBack(Ref* pSender, Widget::TouchEventType type);     //加注回调
		void maxNoteBtnCallBack(Ref* pSender, Widget::TouchEventType type);     //满注回调
        
        void autoBtnCallBack(Ref* pSender, Widget::TouchEventType type);        //自动回调
        void startBtnCallBack(Ref* pSender, Widget::TouchEventType type);       //开始回调

        void turnUpdate(float dt);
        void setTurnIcomPosition(vector<Vec2> &vIconPos, Size parentSize,int index);
        void setTurnUnitCount(vector<int> &vTurnUnitCount, vector<int> vCurBeginIcon, vector<int> vCurEndIcon, int nRoundMinNum);
        void checkTurnIsSuccess();
        void transformOpenLotteryType();
        void randomColumnDatasAndCalcTurnCount();
        void updateOpenLinesEffect();
        void updateSettlementLayer();
        void addLineLogic();
        void maxLineLogic();
        void updateSelectLines();
        void hideAllLines();
        virtual void updateMyMoney(long long money) override;
        
        void addNoteLogic();
        void maxNoteLogic();
        void updateSelectNotes();
        
        void updateJackpot();
        virtual void update(float dt) override;
        void updateMyRealWinMoney(long long money);
        
        void startCallFakeRotate();//点击开始虚假转动调用函数
        void turnUpdateEx(float dt);//点击开始虚假的转动 定时器
        
        void bigKillModeShow(bool show);
        void smallMirrorMove(int idx);
        void BigMirrorMove(int idx);
        void airDropFunc(); //空投
        void bigKillModeFunc();//大逃杀模式开启
        void bigKillPeople();//大逃杀击杀人物;
        
    private:
        long long i64WinJackpot;
        
        void showJackpot();
        
    private:
        vector<ImageView*> _resultImg;
        
        void cleanResults();
    };
}

#endif // __BRNN_GameTable_BRNNTableUI_h__