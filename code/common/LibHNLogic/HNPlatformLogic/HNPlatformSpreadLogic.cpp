﻿//Copyright (c) 2012—2015 Beijing TianRuiDiAn Network Technology Co,Ltd. All rights reserved

#include "HNPlatformSpreadLogic.h"
#include "HNPlatformSpreadManager.h"
#include "HNNetExport.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#define JSON_RESOVE(obj, key) (obj.HasMember(key) && !obj[key].IsNull())

using namespace cocos2d::network;

namespace HN
{
	HNSpreadLogic::HNSpreadLogic()
	:_delegate(nullptr)
	{
	}

	HNSpreadLogic::~HNSpreadLogic()
	{
	}

	void HNSpreadLogic::init(Delegate* delegate)
	{
		_delegate = delegate;
	}

	//void HNSpreadLogic::test(HttpClient* client, HttpResponse* response)
	//{
	//	if (response->isSucceed())
	//	{
	//		std::vector<char> *buffer = response->getResponseData();
	//		std::string resp(buffer->begin(),buffer->end());
	//		rapidjson::Document doc;
	//		doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
	//		if(!doc.IsObject())
	//		{
	//			_delegate->onSpreadInfo(true, false, GBKToUtf8("数据格式不对"));
	//			return ;
	//		}
	//		int status = -1;
	//		if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
	//		if(400 == status)
	//		{
	//			//_delegate->onSpreadInfo(true, false, doc["message"].GetString());
	//			_delegate->onSpreadInfo(true, false, doc["message"].GetString());
	//		}
	//		else if (200 == status)
	//		{
	//			SpreaderInfo info;
	//			if(JSON_RESOVE(doc, "TuiguangUrl")) info.spreadUrl = doc["TuiguangUrl"].GetString();
	//			rapidjson::Value &dataArray = doc["list"];
	//			if (dataArray.IsArray())
	//			{
	//				for (int i = 0; i < dataArray.Size(); i++)
	//				{
	//					const rapidjson::Value& content = dataArray[i];
	//					if(JSON_RESOVE(content, "UserID")) info.userId = content["UserID"].GetInt();
	//					if(JSON_RESOVE(content, "TrueName")) info.reallName = content["TrueName"].GetString();
	//					if(JSON_RESOVE(content, "ApplyTime")) info.applyTime = content["ApplyTime"].GetString();
	//					if(JSON_RESOVE(content, "Phone")) info.phoneNum = content["Phone"].GetString();
	//					if(JSON_RESOVE(content, "Address")) info.address = content["Address"].GetString();
	//					if(JSON_RESOVE(content, "BankName")) info.bankName = content["BankName"].GetString();
	//					if(JSON_RESOVE(content, "BankNo")) info.bankNum = content["BankNo"].GetString();
	//					if(JSON_RESOVE(content, "IDCardNo")) info.personNum = content["IDCardNo"].GetString();
	//					if(JSON_RESOVE(content, "MoneyCount")) info.spreadIncom = content["MoneyCount"].GetInt64();
	//					if(JSON_RESOVE(content, "Remark")) info.failedInfo = content["Remark"].GetString();
	//					if (JSON_RESOVE(content, "IDCardImgUrlMain")) info.IDCardImgUrlMain = content["IDCardImgUrlMain"].GetString();
	//					if (JSON_RESOVE(content, "IDCardImgUrlOther")) info.IDCardImgUrlOther = content["IDCardImgUrlOther"].GetString();
	//					int spreaderStatus = 0;
	//					if (JSON_RESOVE(content, "CheckState")) spreaderStatus = content["CheckState"].GetInt();
	//					if(0 == spreaderStatus || 1 == spreaderStatus)
	//						info.applyStatus = SPREADER_STATUS_ING;
	//					else if (2 == spreaderStatus)
	//						info.applyStatus = SPREADER_STATUS_SUCCESS;
	//					else if (3 == spreaderStatus)
	//						info.applyStatus = SPREADER_STATUS_FAILED;
	//					HNSpreadManager::getInstance()->setSpreadInfo(info);
	//					break;
	//				}
	//			}
	//			_delegate->onSpreadInfo(true,  true, GBKToUtf8("成功"));
	//		}
	//		else
	//		{
	//			_delegate->onSpreadInfo(true, false, GBKToUtf8("不明错误"));
	//		}
	//	}
	//	else
	//	{
	//		_delegate->onSpreadInfo(false, false, GBKToUtf8("连接网络错误"));
	//	}
	//}

	// 请求推广员信息
	void HNSpreadLogic::requestSpreadInfo(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());

		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
			if (response->isSucceed())
			{
				std::vector<char> *buffer = response->getResponseData();
				std::string resp(buffer->begin(),buffer->end());

				log("recv>%s", resp.c_str());

				rapidjson::Document doc;
				doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
                if(!doc.IsObject())
                {
                    _delegate->onSpreadInfo(true, false, GBKToUtf8("数据格式不对"));
                    return ;
                }
				int status = -1;
				if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
				if(400 == status)
				{
					SpreaderInfo info;
					HNSpreadManager::getInstance()->setSpreadInfo(info);
					_delegate->onSpreadInfo(true, false, doc["message"].GetString());
				}
				else if (200 == status)
				{
					SpreaderInfo info;
					if(JSON_RESOVE(doc, "TuiguangUrl")) info.spreadUrl = doc["TuiguangUrl"].GetString();

					rapidjson::Value &dataArray = doc["list"];
					if (dataArray.IsArray())
					{
						for (int i = 0; i < dataArray.Size(); i++)
						{
							const rapidjson::Value& content = dataArray[i];
							if(JSON_RESOVE(content, "UserID")) info.userId = content["UserID"].GetInt();
							if(JSON_RESOVE(content, "TrueName")) info.reallName = content["TrueName"].GetString();
							if(JSON_RESOVE(content, "ApplyTime")) info.applyTime = content["ApplyTime"].GetString();
							if(JSON_RESOVE(content, "Phone")) info.phoneNum = content["Phone"].GetString();
							if(JSON_RESOVE(content, "Address")) info.address = content["Address"].GetString();
							if(JSON_RESOVE(content, "BankName")) info.bankName = content["BankName"].GetString();
							if(JSON_RESOVE(content, "BankNo")) info.bankNum = content["BankNo"].GetString();
							if(JSON_RESOVE(content, "IDCardNo")) info.personNum = content["IDCardNo"].GetString();
							if(JSON_RESOVE(content, "MoneyCount")) info.spreadIncom = content["MoneyCount"].GetInt64();
							if(JSON_RESOVE(content, "Remark")) info.failedInfo = content["Remark"].GetString();
							if (JSON_RESOVE(content, "IDCardImgUrlMain")) info.IDCardImgUrlMain = content["IDCardImgUrlMain"].GetString();
							if (JSON_RESOVE(content, "IDCardImgUrlOther")) info.IDCardImgUrlOther = content["IDCardImgUrlOther"].GetString();
							int spreaderStatus = 0;
							if (JSON_RESOVE(content, "CheckState")) spreaderStatus = content["CheckState"].GetInt();
							if(0 == spreaderStatus || 1 == spreaderStatus)
								info.applyStatus = SPREADER_STATUS_ING;
							else if (2 == spreaderStatus)
								info.applyStatus = SPREADER_STATUS_SUCCESS;
							else if (3 == spreaderStatus)
								info.applyStatus = SPREADER_STATUS_FAILED;
							HNSpreadManager::getInstance()->setSpreadInfo(info);
							break;
						}
					}
					_delegate->onSpreadInfo(true,  true, GBKToUtf8("成功"));
				}
				else
				{
					_delegate->onSpreadInfo(true, false, GBKToUtf8("不明错误"));
				}
			}
			else
			{
				_delegate->onSpreadInfo(false, false, GBKToUtf8("连接网络错误"));
			}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	// 申请推广员
	void HNSpreadLogic::requestBeSpreader(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
		if (response->isSucceed())
		{
		std::vector<char> *buffer = response->getResponseData();
		std::string resp(buffer->begin(),buffer->end());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
		if (!doc.IsObject())
		{
		_delegate->onBeSpreader(false, GBKToUtf8("数据格式不对"));
		return;
		}
		int status = -1;
		if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
		if(202 == status || 201 == status)
		{
		std::string msg = "";
		if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
		_delegate->onBeSpreader(true, msg);
		}
		else
		{
		_delegate->onBeSpreader(false, GBKToUtf8("数据异常错误"));
		}
		}
		else
		{
		_delegate->onBeSpreader(false, GBKToUtf8("连接网络错误"));
		}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	//推广员结算界面信息
	void HNSpreadLogic::requestSpreadBillLayerInfo(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
		spread_layerInfo info;
		if (response->isSucceed())
		{
		std::vector<char> *buffer = response->getResponseData();
		std::string resp(buffer->begin(),buffer->end());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
		if (!doc.IsObject())
		{
		_delegate->onGetBillLayerInfo(false, info, GBKToUtf8("数据格式不对"));
		return;
		}
		int status = -1;
		if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();

		if(JSON_RESOVE(doc, "TrueName")) info.trueName = doc["TrueName"].GetString();
		if(JSON_RESOVE(doc, "TgMoney")) info.spreadIncome = doc["TgMoney"].GetInt64();
		if(JSON_RESOVE(doc, "UserName")) info.userName = doc["UserName"].GetString();
		if(JSON_RESOVE(doc, "MinClearingMoney")) info.minMoney = doc["MinClearingMoney"].GetInt64();
		if(206 == status)
		{
		_delegate->onGetBillLayerInfo(true,  info, "");
		}
		else
		{
		_delegate->onGetBillLayerInfo(false, info, GBKToUtf8("没有获取到数据"));
		}
		}
		else
		{
		_delegate->onGetBillLayerInfo(false, info, GBKToUtf8("连接网络错误"));
		}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	//推广员结账提现
	void HNSpreadLogic::requestSpreaderBill(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
		if (response->isSucceed())
		{
		std::vector<char> *buffer = response->getResponseData();
		std::string resp(buffer->begin(),buffer->end());
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
		if (!doc.IsObject())
		{
		_delegate->onGetMoney(false, GBKToUtf8("数据格式不对"));
		return;
		}
		int status = -1;
		std::string msg = "";
		if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
		if(207 == status)
		{
		if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
		_delegate->onGetMoney(true, msg);
		}
		else if(405 == status || 406 == status || 407 == status || 408 == status)
		{
		if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
		_delegate->onGetMoney(false, msg);
		}
		else
		{
		_delegate->onGetMoney(false, GBKToUtf8("连接异常错误"));
		}
		}
		else
		{
		_delegate->onGetMoney(false, GBKToUtf8("连接网络错误"));
		}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	// 获取被推广玩家充值列表
	void HNSpreadLogic::requestSpreadedPayList(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
			vecSpreadPayList vecInfo;
			vecInfo.clear();
			if (response->isSucceed())
			{
				std::vector<char> *buffer = response->getResponseData();
				std::string resp(buffer->begin(),buffer->end());
				rapidjson::Document doc;
				doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
				if (!doc.IsObject())
				{
					_delegate->onSpreadedPayList(false, vecInfo, GBKToUtf8("数据格式不对"));
					return;
				}
				int status = -1;
				if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
				if(401 == status)
				{
					std::string msg = GBKToUtf8("没有充值数据");
					if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
					_delegate->onSpreadedPayList(false, vecInfo, msg);
				}
				else if (205 == status)
				{
					rapidjson::Value &dataArray = doc["list"];
					if (dataArray.IsArray())
					{
						for (int i = 0; i < dataArray.Size(); i++)
						{
							const rapidjson::Value& content = dataArray[i];
							Spread_PayInfo info;
							if(JSON_RESOVE(content, "PayUserID")) info.PayUserID = content["PayUserID"].GetInt();
							if(JSON_RESOVE(content, "PayMoney")) info.PayMoney = content["PayMoney"].GetInt64();
							if(JSON_RESOVE(content, "GetMoney")) info.GetMoney = content["GetMoney"].GetInt64();
							if(JSON_RESOVE(content, "PayType")) info.PayType = content["PayType"].GetString();
							if(JSON_RESOVE(content, "AddTime")) info.AddTime = content["AddTime"].GetString();
							if(JSON_RESOVE(content, "UserName")) info.UserName = content["UserName"].GetString();
							vecInfo.push_back(info);
						}
					}
					_delegate->onSpreadedPayList(true, vecInfo, "");
				}
			}
			else
			{
				_delegate->onSpreadedPayList(false, vecInfo, GBKToUtf8("连接网络错误"));
			}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	// 获取推广列表
	void HNSpreadLogic::requestSpreadedList(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
			vecSpreadList vecInfo;
			vecInfo.clear();
			if (response->isSucceed())
			{
				std::vector<char> *buffer = response->getResponseData();
				std::string resp(buffer->begin(),buffer->end());
				rapidjson::Document doc;
				doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
				if (!doc.IsObject())
				{
					_delegate->onSpreadedList(false, vecInfo, GBKToUtf8("数据格式不对"));
					return;
				}
				int status = -1;
				if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
				if(401 == status)
				{
					std::string msg = GBKToUtf8("没有充值数据");
					if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
					_delegate->onSpreadedList(false, vecInfo, msg);
				}
				else if (203 == status)
				{
					rapidjson::Value &dataArray = doc["list"];
					if (dataArray.IsArray())
					{
						for (int i = 0; i < dataArray.Size(); i++)
						{
							const rapidjson::Value& content = dataArray[i];
							SpreadedUserInfo info;
							if(JSON_RESOVE(content, "UserID")) info.UserID = content["UserID"].GetInt();
							if(JSON_RESOVE(content, "GameTimeCount")) info.GameTimeCount = content["UserID"].GetInt();
							if(JSON_RESOVE(content, "GetMoney")) info.GetMoney = content["GetMoney"].GetInt64();
							if(JSON_RESOVE(content, "IsRegAward")) info.IsRegAward = content["IsRegAward"].GetInt64();
							if(JSON_RESOVE(content, "UserName")) info.UserName = content["UserName"].GetString();
							if(JSON_RESOVE(content, "IsClearing")) info.BillStatus = content["IsClearing"].GetBool();
							if(JSON_RESOVE(content, "FinishPercent")) info.FinishPercent = content["FinishPercent"].GetString();
							vecInfo.push_back(info);
						}
					}
					_delegate->onSpreadedList(true, vecInfo, "");
				}
				else
				{
					_delegate->onSpreadedList(false, vecInfo, GBKToUtf8("其他错误，待会儿再试试"));
				}
			}
			else
			{
				//test
				for(int i=0; i<10; i++)
				{
					SpreadedUserInfo info;
					info.UserName = "sfsfdf";
					vecInfo.push_back(info);
				}
				_delegate->onSpreadedList(true, vecInfo, "");
				//_delegate->onSpreadedList(false, vecInfo, GBKToUtf8("连接网络错误"));
			}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	//单个玩家有效推广结算请求
	void HNSpreadLogic::requestSingleSpreadedUserBill(std::string url, std::string data/* = ""*/)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(url.c_str());
		request->setRequestType(HttpRequest::Type::POST);
		if (!data.empty()) request->setRequestData(data.c_str(), data.length());
		request->setResponseCallback([&](HttpClient* client, HttpResponse* response)
		{
			if (response->isSucceed())
			{
				std::vector<char> *buffer = response->getResponseData();
				std::string resp(buffer->begin(),buffer->end());
				rapidjson::Document doc;
				doc.Parse<rapidjson::kParseDefaultFlags>(resp.c_str());
				if (!doc.IsObject())
				{
					_delegate->onSingleSpreadedUserBillResult(false, GBKToUtf8("数据格式不对"));
					return;
				}
				int status = -1;
				std::string msg = "";
				if(JSON_RESOVE(doc, "status")) status = doc["status"].GetInt();
				if(204 == status)
				{
					if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
					_delegate->onSingleSpreadedUserBillResult(true, msg);
				}
				else if(402 == status || 403 == status || 404 == status)
				{
					if(JSON_RESOVE(doc, "message")) msg = doc["message"].GetString();
					_delegate->onSingleSpreadedUserBillResult(false, msg);
				}
				else
				{
					_delegate->onSingleSpreadedUserBillResult(false, GBKToUtf8("连接异常错误"));
				}
			}
			else
			{
				_delegate->onSingleSpreadedUserBillResult(false, GBKToUtf8("连接网络错误"));
			}
		});
		HttpClient::getInstance()->setTimeoutForConnect(3);
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}
}
