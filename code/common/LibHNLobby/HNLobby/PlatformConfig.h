﻿#ifndef PlatformConfig_h__
#define PlatformConfig_h__

#include "HNNetExport.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

class PlatformConfig {
public:
    enum ACCOUNT_TYPE {
        UNKNOWN = 0,
        GUEST,
        NORMAL
    };
    
    struct FunctionConfig{
        //银行
        bool isOpenBankFunc;
        //商店
        bool isOpenRechargeFunc;
        //排行榜
        bool isOpenRankFunc;
        //验证码
        bool isOpenVertifyCodeFunc;
        //  帮助界面-帮助界面与审核挂钩，帮助界面开关为true，则表明这个版本是iOS审核版本，需要做相关屏蔽
        bool isOpenHelpFunc;
		//新春活动
		bool isOpenYearFunc;
        //推广福利
        bool isPopularize;
		//是否是IOS授信版本
		bool isIosSpapicVersion;

    }funcConfig;
    
    // APP授权码
    CC_SYNTHESIZE(std::string, _appKey, AppKey);
    // APP类型id
    CC_SYNTHESIZE_PASS_BY_REF(int, _appId, AppId);
    // plist下载地址
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _downloadPlistUrl, DownloadPlistUrl);
    CC_SYNTHESIZE(bool, fullClose, FullClose);
public:
    static PlatformConfig* getInstance();

    void setGameLogo(const std::string& logoGame);
    std::string getGameLogo() const;

    void setSplashLogo(const std::string& splashLogo);
    std::string getSplashLogo() const;

    void setGameDesignSize(Size designSize);
    Size getGameDesignSize() const;

    void setPlatformDesignSize(Size designSize);
    Size getPlatformDesignSize() const;

    void setAccountType(ACCOUNT_TYPE type);
    ACCOUNT_TYPE getAccountType() const;

    void setDownloadName(const std::string& name);
    std::string getDownloadName();

    void setVersionKey(const std::string& key);
    std::string getVersionKey();

    //设置是否支持苹果内购, 这个方法必须在addProducts()前调用
    void setSupportIAP(bool supportIAP);
    bool getSupportIAP() const;

    // 获取推广员地址
    std::string getPromoterUrl();

    // 获取商品列表地址
    std::string getGoodsListUrl(const std::string& platForm_Type);

    // 获取苹果内购后台验证地址
    std::string getPayCallbackUrl_iOS();

    // 获取订单信息接口地址
    std::string getOrderUrl();

    // 获取兑换奖品地址
    std::string getPrizeUrl();

    //获取平台类型
    int getPlatformType();

    void setUIVersion(std::string version);
    std::string getUIVersion();

	void setGoldDisplayRate(std::string strRate);
	float getGoldDisplayRate();
	float getGoldDisplayMultiple();
private:
    PlatformConfig();
    ~PlatformConfig();

    // 生成完整路径
    std::string buildHttp(const std::string& url, const std::string& path);
    std::string buildHttps(const std::string& url, const std::string& path);

private:
    std::string		_gameLogo;
    std::string		_splashLogo;
    Size			_gameDesignSize;
    Size			_platformDesignSize;
    ACCOUNT_TYPE	_accountType;
    std::string     _downloadName;
    std::string     _versionKey;
    bool			_supportIAP;
    //UI版本号
    std::string m_UIVersion;
	float			_fGoldDisplayRate;
	float			_fGoldDisplayMultiple;
};

#endif // PlatformConfig_h__
