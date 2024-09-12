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
#include "LCChatSetChanProp.h"

REG_COMMAND_CPP(LCChatSetChanProp);

                                              
nstl::wstring LCChatSetChanProp::serializeSQL(void)
{
  const int nCommandBufferSize = 900;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
  NI_ASSERT(m_nChannelId != INVALID_ID_NUMBER, "Channel ID could not be INVALID_ID_NUMBER.");
  swprintf(&pBuff[0], nCommandBufferSize - 1,
    L"UPDATE `chat_channels` SET `channel_name` = \"%s\", `owner_id` = %d, `is_clan` = %s, `is_public` = %s, `is_game` = %s, `is_whisper` = %s WHERE `channel_id` = %d;",
    m_sChannelName.c_str(), m_nOwnerId, BoolToStr(m_bIsClan),
    BoolToStr(m_bIsPublic), BoolToStr(m_bIsGame), BoolToStr(m_bIsWhisper), m_nChannelId);
    
  return nstl::wstring(&pBuff[0]);
}

void LCChatSetChanProp::serialize(void)
{
  LobbyCommand::serialize(); 
  GetRequestStream() << m_nChannelId; 
  WriteStringToStream(GetRequestStream(), m_sChannelName);
  GetRequestStream() << m_nOwnerId;
  unsigned int nFlags = 0;
  nFlags |= int(m_bIsPublic ) << LCChatGetChanProp::CP_PUBLIC;
  nFlags |= int(m_bIsSecret ) << LCChatGetChanProp::CP_SECRET;
  nFlags |= int(m_bIsClan   ) << LCChatGetChanProp::CP_CLAN;
  nFlags |= int(m_bIsGame   ) << LCChatGetChanProp::CP_GAME;
  nFlags |= int(m_bIsWhisper) << LCChatGetChanProp::CP_WHISPER;
  GetRequestStream() << nFlags;
}

void LCChatSetChanProp::deserialize(ClientThread const *pClient) 
{
  LobbyCommand::deserialize(pClient); 
  GetRequestStream() >> m_nChannelId; 
  ReadStringFromStream(GetRequestStream(), m_sChannelName);
  GetRequestStream() >> m_nOwnerId;

  unsigned int nFlags = 0;
  GetRequestStream() >> nFlags;
  m_bIsPublic  = (nFlags && (1UL << LCChatGetChanProp::CP_PUBLIC )) != 0;
  m_bIsSecret  = (nFlags && (1UL << LCChatGetChanProp::CP_SECRET )) != 0;
  m_bIsClan    = (nFlags && (1UL << LCChatGetChanProp::CP_CLAN   )) != 0;
  m_bIsGame    = (nFlags && (1UL << LCChatGetChanProp::CP_GAME   )) != 0;
  m_bIsWhisper = (nFlags && (1UL << LCChatGetChanProp::CP_WHISPER)) != 0;
}
