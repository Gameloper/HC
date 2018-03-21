package com.taobao.sdk.youai;

import org.json.JSONException;
import org.json.JSONObject;

import android.text.TextUtils;

/**
 * �����װ�ˡ�access_token������expires_in����"refresh_token"��
 *���ṩ�����ǵĹ�����
 * @author luopeng (luopeng@staff.sina.com.cn)
 */
public class Oauth2AccessToken {
	private String mAccessToken = "";
	private String mRefreshToken = "";
	private long mExpiresTime = 0;

//	private String mOauth_verifier = "";
//	protected String[] responseStr = null;
//	protected SecretKeySpec mSecretKeySpec;
	/**
	 * Oauth2AccessToken �Ĺ��캯��
	 */
	public Oauth2AccessToken() {
	}
	/**
	 * ���ݷ��������ص�responsetext����Oauth2AccessToken �Ĺ��캯����
	 * �˷����Ὣresponsetext��ġ�access_token������expires_in����"refresh_token"��������
	 * @param responsetext ���������ص�responsetext
	 */
	public Oauth2AccessToken(String responsetext) {
		if (responsetext != null) {
			if (responsetext.indexOf("{") >= 0) {
				try {
					JSONObject json = new JSONObject(responsetext);
					setToken(json.optString("access_token"));
					setExpiresIn(json.optString("expires_in"));
					setRefreshToken(json.optString("refresh_token"));
				} catch (JSONException e) {
					
				}
			}
		}
	}
	/**
	 * Oauth2AccessToken�Ĺ��캯��������accessToken ��expires_in ����Oauth2AccessTokenʵ��
	 * @param accessToken  ��������
	 * @param expires_in ��Ч�ڣ���λ�����룻�����ӷ�������ȡ��expires_inʱ���ã���ʾ���볬����֤ʱ�仹�ж�����
	 */
	public Oauth2AccessToken(String accessToken, String expires_in) {
		mAccessToken = accessToken;
		mExpiresTime = System.currentTimeMillis() + Long.parseLong(expires_in)*1000;
	}
	/**
	 *  AccessToken�Ƿ���Ч,���accessTokenΪ�ջ���expiresTime���ڣ�����false�����򷵻�true
	 *  @return ���accessTokenΪ�ջ���expiresTime���ڣ�����false�����򷵻�true
	 */
	public boolean isSessionValid() {
		return (!TextUtils.isEmpty(mAccessToken) && (mExpiresTime == 0 || (System
				.currentTimeMillis() < mExpiresTime)));
	}
	/**
	 * ��ȡaccessToken
	 */
	public String getToken() {
		return this.mAccessToken;
	}
	/**
     * ��ȡrefreshToken
     */
	public String getRefreshToken() {
		return mRefreshToken;
	}
	/**
	 * ����refreshToken
	 * @param mRefreshToken
	 */
	public void setRefreshToken(String mRefreshToken) {
		this.mRefreshToken = mRefreshToken;
	}
	/**
	 * ��ȡ��ʱʱ�䣬��λ: ���룬��ʾ�Ӹ�������ʱ��1970��01��01��00ʱ00��00���������ڵ��� ������
	 */
	public long getExpiresTime() {
		return mExpiresTime;
	}

	/**
	 * ���ù���ʱ�䳤��ֵ�������ӷ�������ȡ������ʱʹ�ô˷���
	 *            
	 */
	public void setExpiresIn(String expiresIn) {
		if (expiresIn != null && !expiresIn.equals("0")) {
			setExpiresTime(System.currentTimeMillis() + Long.parseLong(expiresIn) * 1000);
		}
	}

	/**
	 * ���ù���ʱ�̵� ʱ��ֵ
	 * @param mExpiresTime ��λ�����룬��ʾ�Ӹ�������ʱ��1970��01��01��00ʱ00��00���������ڵ��� ������
	 *            
	 */
	public void setExpiresTime(long mExpiresTime) {
		this.mExpiresTime = mExpiresTime;
	}
	/**
	 * ����accessToken
	 * @param mToken
	 */
	public void setToken(String mToken) {
		this.mAccessToken = mToken;
	}
//	/**
//	 * ���ü�����
//	 * @param verifier
//	 */
//	public void setVerifier(String verifier) {
//		mOauth_verifier = verifier;
//	}
//	/**
//	 * ��ȡ������
//	 * @return
//	 */
//	public String getVerifier() {
//		return mOauth_verifier;
//	}
//	
//	public String getParameter(String parameter) {
//		String value = null;
//		for (String str : responseStr) {
//			if (str.startsWith(parameter + '=')) {
//				value = str.split("=")[1].trim();
//				break;
//			}
//		}
//		return value;
//	}

//	protected void setSecretKeySpec(SecretKeySpec secretKeySpec) {
//		this.mSecretKeySpec = secretKeySpec;
//	}
//
//	protected SecretKeySpec getSecretKeySpec() {
//		return mSecretKeySpec;
//	}
}