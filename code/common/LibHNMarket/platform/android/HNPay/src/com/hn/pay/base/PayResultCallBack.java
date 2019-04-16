package com.hn.pay.base;

public abstract interface PayResultCallBack {
	public enum PAY_SDK {
		UNKNOW,
		ALIPAY,
		WECHAT,
		YEEPAY,
		UNIONPAY
	}

	public abstract void onPayResult(PAY_SDK sdk, int status);
}
