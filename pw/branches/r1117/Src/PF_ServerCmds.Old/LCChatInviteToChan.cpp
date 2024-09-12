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
#include "LCChatInviteToChan.h"

REG_COMMAND_CPP(LCChatInviteToChan);


nstl::wstring LCChatInviteToChan::serializeSQL(void)
{
  const int nCommandBufferSize = 300;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
  if(m_nChannelId == INVALID_ID_NUMBER)
  {
	NI_VERIFY(m_sChannelName != L"", "Channel name could not be empty if channel ID not provided too.", return nstl::wstring(L""););
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"CALL chatInviteByName(\"%s\", %d, %d)", m_sChannelName.c_str(), m_nRecipientId, m_nChannelId);
  }
  else
  {
    NI_ASSERT(m_nChannelId > 0, "ChannelId is not invalid, but still not valid. Investigation needed.");
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"insert into `chat_channel_invites` (`sender_id`, `recipient_id`, `channel_id`) VALUES (%d, %d, %d)", m_nSenderId, m_nRecipientId, m_nChannelId);
  }
  return nstl::wstring(&pBuff[0]);
}

void LCChatInviteToChan::serialize(void)
{
  LobbyCommand::serialize();
  GetRequestStream() << m_nChannelId;
  WriteStringToStream(GetRequestStream(), m_sChannelName);
  GetRequestStream() << m_nSenderId;
  GetRequestStream() << m_nRecipientId;
}

void LCChatInviteToChan::deserialize(ClientThread const *pClient)
{
  LobbyCommand::deserialize(pClient);
  GetRequestStream() >> m_nChannelId;
  ReadStringFromStream(GetRequestStream(), m_sChannelName);
  GetRequestStream() >> m_nSenderId;
  GetRequestStream() >> m_nRecipientId;
}
