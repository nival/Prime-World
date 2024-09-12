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
#include "LCChatGetChanProp.h"

REG_COMMAND_CPP(LCChatGetChanProp);
//__declspec( dllexport ) bool gTestBool = true;

nstl::wstring LCChatGetChanProp::serializeSQL(void)
{
  const int nCommandBufferSize = 300;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
  if(m_nChannelId == INVALID_ID_NUMBER)
  {
    NI_VERIFY(m_sChannelName != L"", "Channel name could not be empty if channel ID not provided too.", return nstl::wstring(L""););
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"SELECT `channel_id`, `channel_name`, `owner_id`, `is_clan`, `is_public`, `is_game`, `is_whisper` FROM `chat_channels` WHERE `channel_name` = %s", m_sChannelName.c_str());
  }
  else
  {
    NI_ASSERT(m_nChannelId > 0, "ChannelId is not invalid, but still not valid. Investigation needed.");
    swprintf(&pBuff[0], nCommandBufferSize - 1, L"SELECT `channel_id`, `channel_name`, `owner_id`, `is_clan`, `is_public`, `is_game`, `is_whisper` FROM `chat_channels` WHERE `channel_id` = %d", m_nChannelId);
  }
  return nstl::wstring(&pBuff[0]);
}

void LCChatGetChanProp::serialize(void)
{
  LobbyCommand::serialize();
  GetRequestStream() << m_nChannelId;
  WriteStringToStream(GetRequestStream(), m_sChannelName);
}

void LCChatGetChanProp::deserialize(ClientThread const *pClient)
{
  LobbyCommand::deserialize(pClient);
  GetRequestStream() >> m_nChannelId;
  ReadStringFromStream(GetRequestStream(), m_sChannelName);
}

void LCChatGetChanProp::serializeReply(void)
{
  LobbyCommand::serializeReply();
  GetReplyStream() << m_nChannelId;
  WriteStringToStream(GetReplyStream(), m_sChannelName);
  GetReplyStream() << m_nOwnerId;
  unsigned int nFlags = 0;
  nFlags |= int(m_bIsPublic ) << CP_PUBLIC;
  nFlags |= int(m_bIsSecret ) << CP_SECRET;
  nFlags |= int(m_bIsClan   ) << CP_CLAN;
  nFlags |= int(m_bIsGame   ) << CP_GAME;
  nFlags |= int(m_bIsWhisper) << CP_WHISPER;
  GetReplyStream() << nFlags;
}

void LCChatGetChanProp::deserializeReply()
{
  LobbyCommand::deserializeReply();
  GetReplyStream() >> m_nChannelId;
  ReadStringFromStream(GetReplyStream(), m_sChannelName);
  GetReplyStream() >> m_nOwnerId;
  unsigned int nFlags = 0;
  GetReplyStream() >> nFlags;
  m_bIsPublic  = (nFlags && (1UL << CP_PUBLIC )) != 0;
  m_bIsSecret  = (nFlags && (1UL << CP_SECRET )) != 0;
  m_bIsClan    = (nFlags && (1UL << CP_CLAN   )) != 0;
  m_bIsGame    = (nFlags && (1UL << CP_GAME   )) != 0;
  m_bIsWhisper = (nFlags && (1UL << CP_WHISPER)) != 0;
}

void LCChatGetChanProp::deserializeSQL(SQLStream &str)
{
  LobbyCommand::deserializeSQL(str);

  //check for result
  if(str.GetSize() == 0)
    return;
  //we expect one one value
  unsigned int nVal;
  //rows
  str >> nVal;
  NI_ASSERT(nVal <= 1, "Investigate if not so.");
  if(nVal != 1)
    return;
  //cols
  str >> nVal;
  if(nVal != 7)
    return;
  str >> m_nChannelId   ;
  str >> m_sChannelName ;
  str >> m_nOwnerId     ;
  str >> m_bIsPublic    ;
  str >> m_bIsSecret    ;
  str >> m_bIsClan      ;
  str >> m_bIsGame      ;
  str >> m_bIsWhisper   ;
}
