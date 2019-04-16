#include "HNSocketLogic.h"
#include "HNSocketThread.h"
#include "HNSocketMessageDelegate.h"
#include "HNSocketProtocolData.h"
#include "HNNetProtocol/HNProtocolExport.h"
#include "HNCommon/HNLog.h"
#include "HNCommon/HNCommonMarco.h"

#include "base/CCMap.h"

namespace HN {
HNSocketLogic::HNSocketLogic(ISocketMessageDelegate* delegate, const std::string& tag) : _delegate(delegate) {
    _socketThread = new HNSocketThread(this);
    _socketThread->setTag(tag);
    _selectorQueue = new HNSocketMessageSelectorHandler();
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule(schedule_selector(HNSocketLogic::socketDataDispatch), this, 0.0f, true);
}

HNSocketLogic::~HNSocketLogic(void) {
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule(schedule_selector(HNSocketLogic::socketDataDispatch), this);

    HN_SAFE_DELETE(_selectorQueue);

    HN_SAFE_DELETE(_socketThread);
}

bool HNSocketLogic::init() 
{
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_CONNECT, "������Ϣ����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_GET_CONTEST_ROOMID, "�������䣬�û�˫���б�ʱ���������Ҫ�����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_GET_TIMINGMATCH_TIME, "��ʱ��");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_NOTIFY_PAY, "֧����Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_REGISTER, "ע���û�");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_LOGON, "ƽ̨��½");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_LIST, "��Ϸ�б�");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_MESSAGE, "ϵͳ��Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_USER_MONEY, "����Ϸ�н������в��� ���򷢰� ID");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_BIND_MOBILE, "���ֻ�����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SET_LOGO, "�����û�ͷ���ֶ�");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_USERINFO, "����û����Ϲ���");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SMS, "�ֻ�������֤���ȡ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_LOGONUSERS, "ͳ�Ƶ�¼����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_BANK, "������Ϣ����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_PAIHANGBANG, "���а���Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SIGN, "ǩ����Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_ONLINE_AWARD, "���߽������");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_IMEI, "���ٵ�¼");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_PROP, "������Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_IMEI_Bind, "������¼���˺�");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_GetInviteCode, "��ȡ������");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SetInviteCode, "����������");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_GetGameTypeID, "��ȡ��ϷID");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_GetBanBenConfig, "��ȡ�汾��Ϣ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SetTiYanMa, "������");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_TRANS_SUCCESS_TIP, "ת�˳ɹ�����ʾ");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_TUIGUANG_SHENQING, "�ƹ��û�����");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SET_TUIGUANG_USER, "�����ƹ��û�");
	DEFINE_MDM_GP_TYPE_MAP(MDM_GP_SELECT_TUIGUANG_USER, "�ƹ��û������ѯ");


	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_CONNECT, "������Ϣ����");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_LOGON, "��½��Ϸ����");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_USER_LIST, "��¼�ɹ��󷵻ظ�����Ϣ�Լ��÷��������Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_USER_ACTION, "�û�����������������������ߵȶ����Ը�ֵΪ����־");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_ROOM, "������Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_MONEY, "������Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_QUEUE_MSG, "�Ŷ���Ϣ(����)");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GR_MANAGE, "����");
	//DEFINE_MDM_GR_TYPE_MAP(MDM_GR_PROP, "�������Ϸ�е�����ص���Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GM_GAME_FRAME, "�����Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GM_MESSAGE, "��Ϣ��Ϣ");
	DEFINE_MDM_GR_TYPE_MAP(MDM_GM_GAME_NOTIFY, "��Ϸ��Ϣ");



    return true;
}

void HNSocketLogic::resetData() {
    _selectorQueue->clear();
}

bool HNSocketLogic::openWithIp(const CHAR* ip, INT port) {
    return _socketThread->openWithIp(ip, port);
}

bool HNSocketLogic::openWithHost(const CHAR* host, INT port) {
    return _socketThread->openWithHost(host, port);
}

bool HNSocketLogic::close() {
    resetData();
    return _socketThread->close();
}

bool HNSocketLogic::connected() const {
    return _socketThread->connected();
}

INT HNSocketLogic::send(UINT MainID, UINT AssistantID, UINT CheckCode, void* object, INT objectSize) 
{
	HNLog::logInfoCn(StringUtils::format("Sender:[%s],MainID:%d,AssistantID:%d,CheckCode:%d", _socketThread->getTag().c_str(), MainID, AssistantID, CheckCode));

    HNSocketProtocolData protocolData;
    protocolData.createPackage(MainID, AssistantID, CheckCode, object, objectSize);
    return _socketThread->send(protocolData.getPackage(), protocolData.getPackageSize());
}

void HNSocketLogic::addEventSelector(UINT MainID, UINT AssistantID, SEL_SocketMessage selector)
{
    CCAssert(nullptr != selector, "selector is nullptr");
    if (nullptr != selector)
	{
		HNLog::logInfoCn(StringUtils::format("Selector:[%s],MainID:%d,AssistantID:%d,Fun[%s]", _socketThread->getTag().c_str(), MainID, AssistantID, typeid(selector).name()));

        CHAR messageKey[16] = {0};
        sprintf(messageKey, SELECTER_KEY_FORMAT, MainID, AssistantID);
        _selectorQueue->addSelector(messageKey, selector);
    }
}

void HNSocketLogic::addEventSelector(std::string strKey, SEL_SocketMessage selector)
{
	CCAssert(nullptr != selector, "selector is nullptr");
	if (nullptr != selector)
	{
		HNLog::logInfoCn(StringUtils::format("Selector:[%s],Key:%s,Fun[%s]", _socketThread->getTag().c_str(), strKey.c_str(), typeid(selector).name()));

		
		_selectorQueue->addSelector(strKey, selector);
	}
}

void HNSocketLogic::removeEventSelector(UINT MainID, UINT AssistantID) {
    CHAR messageKey[16] = {0};
    sprintf(messageKey, SELECTER_KEY_FORMAT, MainID, AssistantID);
    _selectorQueue->removeSelector(messageKey);
}

void HNSocketLogic::heartBeat(UINT MainID, UINT AssistantID, UINT CheckCode) {
    HNSocketProtocolData protocolData;
    protocolData.createPackage(MainID, AssistantID, CheckCode);
    int ret = _socketThread->send(protocolData.getPackage(), protocolData.getPackageSize());
    if (ret >= 0) {
        //HNLOG_WARNING("%s >> heartBeat", _socketThread->getTag().c_str());
    }
}

void HNSocketLogic::onReadComplete() {
    Director::getInstance()->getScheduler()->resumeTarget(this);
}
    
void HNSocketLogic::onHearBeat(){
    _delegate->onHearBeat();
}

void HNSocketLogic::printfMessageInfo(HNSocketMessage* socketMessage)
{
	HNLog::logInfo("Receiver[%s]->Key:%s", _socketThread->getTag().c_str(), socketMessage->strKey.c_str());
	if (_socketThread->getTag() == "platform")
	{
		HNLog::logInfo("%s", m_mdmGP_MessageInfo[socketMessage->messageHead.bMainID].c_str());
	}
	else if (_socketThread->getTag() == "game")
	{
		HNLog::logInfo("%s", m_mdmGR_MessageInfo[socketMessage->messageHead.bMainID].c_str());
	}
	else
	{
		HNLog::logInfo("δ֪�׽����߳�����!");
	}



}

void HNSocketLogic::socketDataDispatch(float dt) {
    _socketThread->transform([this](HNSocketMessage* socketMessage) {
        assert(nullptr != _delegate);
        switch (socketMessage->socketStatus) {
        case SocketStatus_UNKNOW:
            HNLog::logInfo("SocketStatus_UNKNOW");
            break;

        case SocketStatus_CONNECT:
            HNLog::logInfo("SocketStatus_CONNECT");
            break;

        case SocketStatus_OUTTIME:
            HNLog::logInfo("SocketStatus_OUTTIME");
            _delegate->onConnected(false, SocketStatus_OUTTIME);
            break;

        case SocketStatus_STCCESS:
            HNLog::logInfo("SocketStatus_STCCESS");
                
            break;

        case SocketStatus_RECV:
		{
			//printfMessageInfo(socketMessage);
            bool ret = _selectorQueue->executeSelector(socketMessage->strKey, socketMessage);
			
            if (ret) 
			{
				HNLog::logInfo("Receiver[%s]->executeSelector->Key:%s", _socketThread->getTag().c_str(),socketMessage->strKey.c_str());
			}
			else
			{
				HNLog::logInfo("Receiver[%s]->onSocketMessage->Key:%s", _socketThread->getTag().c_str(), socketMessage->strKey.c_str());
				_delegate->onSocketMessage(socketMessage);
			}
        }
        break;

        case SocketStatus_DISCONNECT:

			//qiuyx net
            _selectorQueue->clear();
            _delegate->onDisConnect();
            break;

        case SocketStatus_ERROR:
            _selectorQueue->clear();
            _delegate->onConnected(false, SocketStatus_ERROR);
            break;

        default:
            break;
        }
    });
    Director::getInstance()->getScheduler()->pauseTarget(this);
}

void HNSocketLogic::addPlatformHearBeatCount() {
    if(_socketThread->connected()){
        _socketThread->platformHeartBeatCount++;
    }   
}

void HNSocketLogic::addGameHearBeatCount() {
        if(_socketThread->connected()){
            _socketThread->gameHeartBeatCount++;
        }
}

int HNSocketLogic::getPlatformHeartBeatCount() {
            if(_socketThread->connected()){
    return _socketThread->platformHeartBeatCount;
            }
    return 0;
}

int HNSocketLogic::getGameHeartBeatCount() {
                if(_socketThread->connected()){
    return _socketThread->gameHeartBeatCount;
                }
    return 0;
}

void HNSocketLogic::resumePlatformHearBeatCount() {
                    if(_socketThread->connected()){
    _socketThread->platformHeartBeatCount = 0;
                    }
}

void HNSocketLogic::resumeGameHearBeatCount() {
                    if(_socketThread->connected()){
    _socketThread->gameHeartBeatCount = 0;
                    }
}
}
