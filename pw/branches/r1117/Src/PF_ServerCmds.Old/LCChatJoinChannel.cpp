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
#include "LCChatJoinChannel.h"

REG_COMMAND_CPP(LCChatJoinChannel);


nstl::wstring LCChatJoinChannel::serializeSQL(void)
{
  const int nCommandBufferSize = 300;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
  if(m_nChannelId != INVALID_ID_NUMBER)
  {
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"INSERT INTO `chat_cu_list` (`channel_id`, `user_id`)"
      L"VALUES (%d, %d)", m_nChannelId, m_nClientID);
  }
  else
  {
    NI_ASSERT(L"" != m_sChanName, "Channel name cannot be empty.");
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"CALL LCChatJoinChannel(\"%s\", %d)", m_sChanName.c_str(), m_nClientID);
  }
  return nstl::wstring(&pBuff[0]);
}

void LCChatJoinChannel::serialize(void)
{
  LobbyCommand::serialize();
  GetRequestStream() << m_nChannelId;
  GetRequestStream() << m_sChanName;
}

void LCChatJoinChannel::deserialize(ClientThread const *pClient)
{
  LobbyCommand::deserialize(pClient);
  GetRequestStream() >> m_nChannelId;
  GetRequestStream() >> m_sChanName;

  m_nClientID = pClient->GetAccoundId();
  //verify we join this channel

}

bool isCanJoinChannel(class ClientThread const *)
{
  return true;
}

