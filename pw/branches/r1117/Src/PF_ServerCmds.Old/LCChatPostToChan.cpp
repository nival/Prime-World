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
#include "LCChatPostToChan.h"

REG_COMMAND_CPP(LCChatPostToChan);

                                              
nstl::wstring LCChatPostToChan::serializeSQL(void)
{
  const int nCommandBufferSize = 900;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);

  NI_ASSERT(m_nChannelId != INVALID_ID_NUMBER, "Wrong id for channel");
  NI_ASSERT(m_nUserId    != INVALID_ID_NUMBER, "Wrong id for user");
  swprintf(&pBuff[0], nCommandBufferSize - 1, 
    L"INSERT INTO `chat_chat` (`channel_id`, `user_id`, `text`) VALUES (%d, %d, \"%s\");", m_nChannelId, m_nUserId, m_sText.c_str());
  return nstl::wstring(&pBuff[0]);
}

void LCChatPostToChan::deserialize(ClientThread const *pClient) 
{
  LobbyCommand::deserialize(pClient); 
  GetRequestStream() >> m_nChannelId;
  ReadStringFromStream(GetRequestStream(), m_sText);

  m_nUserId = pClient->GetAccoundId();
}

void LCChatPostToChan::serialize(void) 
{
  LobbyCommand::serialize(); 
  GetRequestStream() << m_nChannelId; 
  WriteStringToStream(GetRequestStream(), m_sText);
}

