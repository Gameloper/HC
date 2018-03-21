
#include <string>

#include <jni.h>
#include <android/log.h>
#include "jni/JniHelper.h"
#include "com4loves.h"

#define  CLASS_NAME "com/nuclear/dota/LastLoginHelp"

#define  LOG_TAG    "LastLoginHelp.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

    //�ͻ����������ͬ��������id
    void com4loves::updateServerInfo(int serverID, const std::string& playerName, int playerID, int lvl, int vipLvl, int coin1, int coin2, bool pushSvr){
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "updateServerInfo",  "(ILjava/lang/String;IIIIIZ)V")) {
			
			//LOGD("com4loves::updateServerInfo:%d,%s,%d,%d,%d,%d,%d,%d", serverID, playerName.c_str(), playerID, lvl, vipLvl, coin1, coin2, pushSvr);
			jstring stringArg1 = t.env->NewStringUTF(playerName.c_str());

			t.env->CallStaticVoidMethod(t.classID, t.methodID, serverID, stringArg1, playerID, lvl, vipLvl, coin1, coin2, pushSvr);
			
			t.env->DeleteLocalRef(stringArg1);
			t.env->DeleteLocalRef(t.classID);			
		}
    }
    
   //ˢ����Ϸ��������Ϣ�������л��û������÷������б�
    void com4loves::refreshServerInfo(const std::string& gameid, const std::string& puid, bool getSvr){
		JniMethodInfo t;

		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "refreshServerInfo","(Ljava/lang/String;Ljava/lang/String;Z)V")) {
			//LOGD("com4loves::refreshServerInfo:%s,%s,%d", gameid.c_str(), puid.c_str(), getSvr);
			jstring stringArg1 = t.env->NewStringUTF(gameid.c_str());
			jstring stringArg2 = t.env->NewStringUTF(puid.c_str());
			
			t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, getSvr);
			
			t.env->DeleteLocalRef(stringArg1);
			t.env->DeleteLocalRef(stringArg2);
			t.env->DeleteLocalRef(t.classID);
			return;
		}
		return;
    }
    //����˺ŷ������ϼ�¼����Ϸ����������
    int com4loves::getServerInfoCount(){
		JniMethodInfo t;
		
		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getServerInfoCount", "()I")) {
			
			jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			return ret;
		}
		return 0;
    }
    //����˳�����˺ŷ������ϵ�n����Ϸ�������ķ�����ID
    int com4loves::getServerUserByIndex(int index){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getServerUserByIndex", "(I)I")) {
			
			jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, index);
			t.env->DeleteLocalRef(t.classID);
			
			return ret;
		}
		return 0;
    }