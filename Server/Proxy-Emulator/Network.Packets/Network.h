// Network.h

#include "pb\up.pb.h"
#include "Packets\Up_UpMsg.h"
#include "Packets\Up_Login.h"
#include "Packets\Up_SdkLogin.h"
#include "Packets\Up_SystemSettingChange.h"

#include "Packets\Up_ActivityBigpackageInfo.h"
#include "Packets\Up_ActivityBigpackageReset.h"
#include "Packets\Up_ActivityBigpackageRewardInfo.h"
#include "Packets\Up_ActivityInfo.h"
#include "Packets\Up_ActivityLottoInfo.h"
#include "Packets\Up_ActivityLottoReward.h"
#include "Packets\Up_AskActivityInfo.h"
#include "Packets\Up_AskDailyLogin.h"
#include "Packets\Up_AskMagicsoul.h"
#include "Packets\Up_BuySkillStrenPoint.h"
#include "Packets\Up_BuyVitality.h"
#include "Packets\Up_CdkeyGift.h"
#include "Packets\Up_ChangeServer.h"
#include "Packets\Up_ChangeTaskStatus.h"
#include "Packets\Up_Charge.h"
#include "Packets\Up_Chat.h"
#include "Packets\Up_ConsumeItem.h"
#include "Packets\Up_ContinuePay.h"
#include "Packets\Up_DotInfo.h"
#include "Packets\Up_EnterActStage.h"
#include "Packets\Up_EnterStage.h"
#include "Packets\Up_EquipSynthesis.h"
#include "Packets\Up_EveryDayHappy.h"
#include "Packets\Up_Excavate.h"
#include "Packets\Up_ExitStage.h"
#include "Packets\Up_FbAttention.h"
#include "Packets\Up_FragmentCompose.h"
#include "Packets\Up_GetMaillist.h"
#include "Packets\Up_GetSvrTime.h"
#include "Packets\Up_GetVipGift.h"
#include "Packets\Up_GmCmd.h"
#include "Packets\Up_Guild.h"
#include "Packets\Up_HeroEquipUpgrade.h"
#include "Packets\Up_HeroEvolve.h"
#include "Packets\Up_HeroUpgrade.h"
#include "Packets\Up_JobRewards.h"
#include "Packets\Up_Ladder.h"
#include "Packets\Up_Midas.h"
#include "Packets\Up_OpenShop.h"
#include "Packets\Up_PushNotify.h"
#include "Packets\Up_QueryActStage.h"
#include "Packets\Up_QueryData.h"
#include "Packets\Up_QueryRanklist.h"
#include "Packets\Up_QueryReplay.h"
#include "Packets\Up_QuerySplitData.h"
#include "Packets\Up_QuerySplitReturn.h"
#include "Packets\Up_ReadMail.h"
#include "Packets\Up_RechargeRebate.h"
#include "Packets\Up_ReportBattle.h"
#include "Packets\Up_RequestGuildLog.h"
#include "Packets\Up_RequestUpgradeArousalLevel.h"
#include "Packets\Up_RequestUserinfo.h"
#include "Packets\Up_RequireArousal.h"
#include "Packets\Up_RequireRewards.h"
#include "Packets\Up_ResetElite.h"
#include "Packets\Up_SellItem.h"
#include "Packets\Up_SetAvatar.h"
#include "Packets\Up_SetName.h"
#include "Packets\Up_ShopConsume.h"
#include "Packets\Up_ShopRefresh.h"
#include "Packets\Up_SkillLevelup.h"
#include "Packets\Up_SplitHero.h"
#include "Packets\Up_String.h"
#include "Packets\Up_SuspendReport.h"
#include "Packets\Up_SweepStage.h"
#include "Packets\Up_SyncSkillStren.h"
#include "Packets\Up_SyncVitality.h"
#include "Packets\Up_TavernDraw.h"
#include "Packets\Up_Tbc.h"
#include "Packets\Up_TriggerJob.h"
#include "Packets\Up_TriggerTask.h"
#include "Packets\Up_Tutorial.h"
#include "Packets\Up_WearEquip.h"
#include "Packets\Up_Worldcup.h"

#include <iostream>
#pragma once

#define ARRAY_LENGTH(array) (sizeof(array)*sizeof((array)[0]))

using namespace System;
using namespace System::Collections::Generic;

namespace Network {
	namespace Packets {

		public ref class Class1
		{
		public:
			static List<Up_UpMsg^>^ ParseDownMsg(array<Byte>^ data)
			{
				int dataLen = data->Length;
				pin_ptr<unsigned char> data_pin = &data[0];
				unsigned char* data_ptr = data_pin;
				/*char* data_ptr = new char[74]{
					'\x08', '\x00', '\x10', '\x01', '\x1A', '\x33', '\x08', '\x00', '\x12', '\x0B', '\x77', '\x69', '\x6E', '\x33', '\x32', '\x5F', '\x61', '\x64', '\x6D', '\x69', '\x6E', '\x1A', '\x20', '\x34', '\x37', '\x62', '\x32', '\x36', '\x30', '\x37', '\x62', '\x39', '\x34', '\x31', '\x61', '\x37', '\x61', '\x62', '\x63', '\x35', '\x61', '\x63', '\x34', '\x65', '\x32', '\x30', '\x38', '\x30', '\x65', '\x38', '\x31', '\x36', '\x31', '\x32', '\x33', '\x20', '\x00', '\xB2', '\x02', '\x0E', '\x0A', '\x0A', '\x33', '\x33', '\x33', '\x33', '\x33', '\x33', '\x33', '\x33', '\x33', '\x33', '\x10', '\x00'
				};*/
				up::up_msg* msg = new up::up_msg();

				msg->ParseFromArray(data_ptr, dataLen);

				List<Up_UpMsg^>^ messages = gcnew List<Up_UpMsg^>(2);

				Up_UpMsg^ up_msg = gcnew Up_UpMsg(msg);
				messages->Add(up_msg);

				if (msg->has__login())
				{
					Up_Login^ login = gcnew Up_Login(&msg->_login());
					messages->Add(login);
				}

				if (msg->has__sdk_login())
				{
					Up_SdkLogin^ sdkLogin = gcnew Up_SdkLogin(&msg->_sdk_login());
					messages->Add(sdkLogin);
				}

				if (msg->has__system_setting())
				{
					Up_SystemSetting^ systemSetting = gcnew Up_SystemSetting(&msg->_system_setting());
					messages->Add(systemSetting);
				}

				if(msg->has__enter_stage())
				{
					Up_EnterStage^ enterStage = gcnew Up_EnterStage(&msg->_enter_stage());
					messages->Add(enterStage);
				}

				return messages;
			}
		};
	}
}