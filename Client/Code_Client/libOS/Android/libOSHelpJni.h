
#pragma once


/************************************************************************/


/*
	Ҫ���Զ����������ͻ���App
*/
extern void requestRestartAppJni();


/************************************************************************/

/*
	��ʼ���ͻ���ͳ�Ʒ������߰�
*/
extern void initAnalyticsJni(const std::string& appid);
/*
	�ͻ���ͳ�Ʒ������߰����趨���ΨһID����������key
*/
extern void initAnalyticsUserIDJni(const std::string userid);
/*

*/
extern void analyticsLogEventJni(const std::string& event);

extern void analyticsLogEventJni(const std::string& event, const std::map<std::string, std::string>& dictionary, bool timed);

extern void analyticsLogEndTimeEventJni(const std::string& event);

/************************************************************************/


extern void weChatOpenJni();

extern void weChatShareFriendsJni(const std::string& shareContent);
	
extern void weChatShareFriendsJni(const std::string& shareImgPath,const std::string& shareContent);
	
	
extern void weChatSharePersonJni(const std::string& shareContent);
	
extern void weChatSharePersonJni(const std::string& shareImgPath,const std::string& shareContent);
extern void playMovieJni(const std::string filename, int needSkip /*= true*/);

extern void stopMovieJni();

extern void fbAttentionJni();

extern int getSecondsFromGMTJni();



