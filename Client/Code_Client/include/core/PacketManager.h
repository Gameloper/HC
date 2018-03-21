#pragma once

namespace google{namespace protobuf{class Message;}}

#include "Singleton.h"
#include "cocos2d.h"
#include "ThreadSocket.h"
#include <map>
#include <set>
#include <string>

class PacketBase;
class PacketFactoryBase;

class PacketHandler
{
public:
	enum Handler_Type
	{
		Default_Handler,
		Scripty_Handler,
		Double_Handler,
	};
	virtual void onReceivePacket(const int opcode, const ::google::protobuf::Message* packet){};
	virtual void onReceivePacket(const int opcode, const std::string& str){};
	virtual void onSendPacketFailed(const int opcode) = 0;
	virtual void onReceivePacketFailed() {};
	virtual void onConnectFailed(std::string ip, int port) = 0;
	virtual void onTimeout(const int opcode) = 0;
	virtual void onPacketError(const int opcode) = 0;
	virtual Handler_Type getHandleType(void) {return Default_Handler;};
};

class PacketManagerListener
{
public:
	virtual void onConnection(void){}			//����ʱ
	virtual void onConnectionError(void){}		//��һ������ʧ��ʱ
	virtual void onReConnection(void){}			//����ʱ
	virtual void onReConnectionError(void){}	//����ʧ��ʱ������N�����Ӻ�
	virtual void onConnectionSuccess(void){}	//���ӳɹ�ʱ
	virtual void onDisConnection(void){}

	virtual void onLogin(void){}				//��½ʱ
	virtual void onLoginError(void){}			//��һ�ε�½ʧ��ʱ
	virtual void onReLogin(void){}				//�ص�½ʱ
	virtual void onReLoginError(void){}			//�ص�½ʧ��ʱ������N�ε�½��
	virtual void onLoginSuccuss(void){}			//��½�ɹ�ʱ
	
	virtual void onPreSend(int opcode, ::google::protobuf::Message*, bool needWaiting=true){}
	virtual void onPreSend(int opcode, char* buff, int length, bool needWaiting = true){}
	virtual void onPostSend(int opcode, ::google::protobuf::Message*, bool needWaiting=true, int targetOpcode = 0){}
	virtual void onPostSend(int opcode, char* buff, int length, bool needWaiting = true){}

	virtual void onBoardcastPacketToHandler( int id, const ::google::protobuf::Message* msg, const std::string& msgStr=0){}
	virtual void onBoardcastConnectionFailed(std::string ip, int port){}
	virtual void onBoardcastSendFailed(int opcode){}
	virtual void onBoardcastReceiveFailed(){}
	virtual void onBoardcastReceiveTimeout(int opcode){}
	virtual void onBoardcastPacketError(int opcode, const std::string &errmsg){}

};
class PacketScriptHandler : public cocos2d::CCObject, public PacketHandler 
{
public:
	PacketScriptHandler(int opcode, int nHandler);
	virtual ~PacketScriptHandler();

	virtual void onConnection(void){}			//����ʱ
	virtual void onConnectionError(void){}		//��һ������ʧ��ʱ
	virtual void onReConnection(void){}			//����ʱ
	virtual void onReConnectionError(void){}	//����ʧ��ʱ������N�����Ӻ�
	virtual void onConnectionSuccess(void){}	//���ӳɹ�ʱ
	virtual void onDisConnection(void){}

	virtual void onLogin(void){}				//��½ʱ
	virtual void onLoginError(void){}			//��һ�ε�½ʧ��ʱ
	virtual void onReLogin(void){}				//�ص�½ʱ
	virtual void onReLoginError(void){}			//�ص�½ʧ��ʱ������N�ε�½��
	virtual void onLoginSuccuss(void){}			//��½�ɹ�ʱ


	virtual void onReceivePacket(const int opcode, const ::google::protobuf::Message* packet);;
	virtual void onReceivePacket(const int opcode, const std::string& str);;
	virtual void onSendPacketFailed(const int opcode);
	virtual void onConnectFailed(std::string ip, int port);
	virtual void onTimeout(const int opcode);
	virtual void onPacketError(const int opcode);
	virtual Handler_Type getHandleType(void) {return Scripty_Handler;};

	//for lua
	int getRecPacketBufferLength(){return mPktBuffer.length();}
	std::string  getRecPacketBuffer(){return mPktBuffer;}

private:

	int mRecOpcode;
	std::string mPktBuffer;

	int mScriptFunHandler;
};

//Ҫ���½�� opcode=1 ��½�ر� opcode=2
//���͵İ������û�д���ر���opcode��Ĭ�ϻذ�opcodeΪ���Ͱ�opcode+1
//�������з��Ͱ�opcodeȡ�������ذ�ȡż��
class PacketManager : public Singleton<PacketManager>, SocketListener 
{
public:
	PacketManager(void);
	~PacketManager(void);
	static PacketManager* getInstance();

	enum
	{
		DEFAULT_BUFFER_LENGTH = 131072,//128k
	};
	enum PM_STATE
	{
		PM_UnInit,
		PM_Init,
		PM_Connecting,
		PM_ConnectError,
		PM_ReConnecting,
		PM_ReConnectError,
		PM_Connected,
		PM_ReConnected,
	};
	void init(const std::string& configFile);
	void init(const std::string& ip, int port);
	void update(float dt);
	void disconnect();
	void reconnect();

	void login(const char* buff, unsigned int length);
	void relogin();
	bool registerPacketHandler(int opcode,PacketHandler*);
	bool registerPacketSendListener(PacketManagerListener*);
	void removePacketSendListener(PacketManagerListener*);

	int nameToOpcode(const std::string& name);
	void removePacketHandler(int opcode, PacketHandler* packethandler);
	void removePacketHandler(PacketHandler* packethandler);
	
	void sendPakcet(int opcode, ::google::protobuf::Message*, bool needWaiting=true, int targetOpcode = 0);
	void sendPakcet(int opcode, char* buff, int length, bool needWaiting = true);

	
	void _checkReceivePacket();
	bool _registerPacketFactory(int opcode, const std::string& packetName,  PacketFactoryBase*);
	bool _buildDefaultMessage(int opcode, ::google::protobuf::Message*);
	::google::protobuf::Message* _getDefaultMessage(int opcode);

	void _boardcastPacketToHandler( int id, const ::google::protobuf::Message* msg, const std::string& msgStr=0);
	void _boardcastConnectionFailed(std::string ip, int port);
	void _boardcastSendFailed(int opcode);
	void _boardcastReceiveFailed();
	void _boardcastReceiveTimeout(int opcode);
	void _boardcastPacketError(int opcode, const std::string &errmsg);
	PM_STATE getPmState(){return mPMState;}
	void setPmState(PM_STATE state);
	
	void onReceivePacket(void* buffer, int size);
	//void onReceivePacket(unsigned int opcode, const std::string& msgStr);
	void onReceiveFailed(void);
	void onSendFailed(unsigned int opcode);
	void onConnectionFailed(std::string ip, unsigned int port);
	void onConnectionSuccess(std::string ip, unsigned int port);

	void setPacketOpcodeWaitReason(int opcode,int tartgetOpcode=0);

	int getPacketWaitOpcode(int opcode);
private:
	friend class ThreadSocket;
	PacketBase* createPacket(int opcode);

	typedef std::map<int, PacketFactoryBase*> PACKET_FACTORY_MAP;
	PACKET_FACTORY_MAP mFactories;

	typedef std::map<int,std::set<PacketHandler*> > PACKET_HANDLER_MAP;
	PACKET_HANDLER_MAP mHandlers;

	typedef std::set<PacketManagerListener*> PacketManagerListenerList;
	PacketManagerListenerList mPacketManagerListenerList;

	typedef std::map<int,int> PACKET_WAIT_OPCODE_MAP;
	PACKET_WAIT_OPCODE_MAP mWaitReason;

	typedef std::map<std::string, int> NAME_TO_OPCODE_MAP;
	NAME_TO_OPCODE_MAP mNameToOpcode;

	typedef std::map<int, ::google::protobuf::Message*> DEFAULT_MESSAGE_MAP;
	DEFAULT_MESSAGE_MAP mDefaultMessageMap;

	//bool isReLogin;
	bool needReConnect;

	PM_STATE mPMState;

	float mLoginTimer;
	unsigned int mReconnectCount;
	unsigned int mReloginCount;
};
