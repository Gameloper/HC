#pragma once
#include "inifile.h"
#include "Singleton.h"
#include "TableReader.h"
#include <map>

class VaribleManager : public ConfigFile, public Singleton<VaribleManager>
{
public:
	VaribleManager(){ reload(); };
	~VaribleManager();
	void reload(){ load("txt/Varible.txt"); }
	static VaribleManager* getInstance();
private:

};

class PlatformRoleItem
{
public:
	unsigned int	id;//�������
	std::string		name;//ƽ̨����
	unsigned int	attentionStatus;//��ע΢�ſ���
	std::string		loadingFrameSeversConnection;//������������ʾ��ƽ̨����
	std::string		rechargeMaxLimit;//�׳巭�����
	unsigned int	bbsOpenStatus;//bbs����״̬
	std::string		showFeedBack;//������Ϣ��תҳ�����
	unsigned int	webkitOpenStatus;//webkit����ҳ�濪��״̬
	std::string		aboutSetting;//����ҳ������
	std::string excludedAboutIds;//�ų����Ĺ���ҳ����Ŀid, ���id�ö��ŷָ�����ʽ�磺"1,2,3" 
	std::string excludedAnnoucementIds;//�ų����Ĺ���ҳ����Ŀid ���id�ö��ŷָ�����ʽ�磺"1,2,3" 
	unsigned int	isUsePrivateBigVersionUpdate;
	unsigned int	isUseSDKBBS;
	std::string		openBBSUrl;
	std::string		loadinScenceMsg;
	unsigned int	exit2platlogout;
	unsigned int    shareSwitch;//΢�ŷ�����
private:
	void readline(std::stringstream& _stream)
	{
		_stream
			>> id
			>> name
			>> attentionStatus
			>> loadingFrameSeversConnection
			>> rechargeMaxLimit
			>> bbsOpenStatus
			>> showFeedBack
			>> webkitOpenStatus
			>> aboutSetting
			>> excludedAboutIds
			>> excludedAnnoucementIds
			>> isUsePrivateBigVersionUpdate
			>> isUseSDKBBS
			>> openBBSUrl
			>> loadinScenceMsg
			>> exit2platlogout
			>> shareSwitch;
	}
	friend class PlatformRoleTableManager;
};
class PlatformRoleTableManager
	: public TableReader
	, public Singleton<PlatformRoleTableManager>
{
public:

	PlatformRoleTableManager()
	{
		init("txt/PlatformRoleConfig.txt");
	}

	typedef std::map<unsigned int, PlatformRoleItem* > PlatformRoleList;

	void init(const std::string& filename);
	const PlatformRoleItem * getPlatformRoleByID(unsigned int id);
	const PlatformRoleItem * getPlatformRoleByName(std::string name);

	inline unsigned int getTotalNum() { return mPlatformRoleList.size(); };

	static PlatformRoleTableManager* getInstance();

private:
	virtual void readline(std::stringstream& _stream);
	PlatformRoleList mPlatformRoleList;
};