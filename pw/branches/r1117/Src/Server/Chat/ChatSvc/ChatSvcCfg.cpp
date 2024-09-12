#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatSvcCfg.h"

namespace chat
{
  static unsigned int s_channelHistorSize = 10;
  REGISTER_VAR( "chat_channel_history_size", s_channelHistorSize, STORAGE_GLOBAL);

  static unsigned int s_censorCheck = 1;
  REGISTER_VAR( "chat_censor_check", s_censorCheck, STORAGE_GLOBAL);

  unsigned int Cfg::GetChannelHistorySize()
  {
    return s_channelHistorSize;
  }

  unsigned int Cfg::GetCensorCheck()
  {
    return s_censorCheck;
  }
}
