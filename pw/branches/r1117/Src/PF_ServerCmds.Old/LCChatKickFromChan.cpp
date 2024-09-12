/*
 * LCRegisterQuickGame.cpp
 *
 *  Created on: 01.11.2008
 *      Author: earnol
 */


#include "../Server/src/TypeProxy.h"
#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LoggerStream.h"
#include "../System/SystemLog.h"
#include <ctype.h>
#include <typeinfo>
#include <math.h>
#include "../System/ScopedArray.h"
#include "../System/basic.h"
#include "../System/nalgoritm.h"
#include "../Server/src/ClientThread.h"
#include "LCChatKickFromChan.h"

REG_COMMAND_CPP(LCChatKickFromChan);

                                              
nstl::wstring LCChatKickFromChan::serializeSQL(void)
{
  if(m_nKickerId != INVALID_ID_NUMBER && m_nVictimId != INVALID_ID_NUMBER && m_nChannelId != INVALID_ID_NUMBER)
  {
    const int nCommandBufferSize = 300;
    ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"DELETE FROM `chat_cu_list` WHERE (`channel_id` = %d) AND (`user_id` = %d);"
      L"INSERT INTO `chat_channel_kicks` (`user_id`, `channel_id`) VALUES (%d, %d );", m_nChannelId, m_nVictimId, m_nVictimId, m_nChannelId);
    return nstl::wstring(&pBuff[0]);
  }
  else
  {
    return nstl::wstring(L"");
  }
}

void LCChatKickFromChan::serialize(void) 
{
  LobbyCommand::serialize(); 
  GetRequestStream() << m_nKickerId; 
  GetRequestStream() << m_nVictimId; 
  GetRequestStream() << m_nChannelId; 
}

void LCChatKickFromChan::deserialize(ClientThread const *pClient) 
{
  LobbyCommand::deserialize(pClient); 

  GetRequestStream() >> m_nKickerId; 
  GetRequestStream() >> m_nVictimId; 
  GetRequestStream() >> m_nChannelId; 
}
