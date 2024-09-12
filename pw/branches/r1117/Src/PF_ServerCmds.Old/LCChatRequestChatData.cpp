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
#include "LCChatRequestChatData.h"

REG_COMMAND_CPP(LCChatRequestChatData);

                                              
nstl::wstring LCChatRequestChatData::serializeSQL(void)
{
  const int nCommandBufferSize = 300;
  ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);

  NI_ASSERT(m_nUserID    != INVALID_ID_NUMBER, "Wrong id for user");
  if(m_bUseTimeStamp)
  {
    swprintf(&pBuff[0], nCommandBufferSize - 1, 
        L"SELECT `chat_id`, `channel_id`, `user_id`, UNIX_TIMESTAMP(`time`), `text` FROM `chat_chat` WHERE `time` BETWEEN FROM_UNIXTIME(%u) AND NOW();",
      m_nTimeStampFrom);
  }
  else
  {
    swprintf(&pBuff[0], nCommandBufferSize - 1, 
#ifndef NI_PLATF_LINUX
      L"SELECT `chat_id`, `channel_id`, `user_id`, UNIX_TIMESTAMP(`time`), `text` FROM `chat_chat` WHERE `chat_id` >= %I64d;",
#else
      L"SELECT `chat_id`, `channel_id`, `user_id`, UNIX_TIMESTAMP(`time`), `text` FROM `chat_chat` WHERE `chat_id` >= %lld;",
#endif
      m_nChatIDFrom);
  }
  return nstl::wstring(&pBuff[0]);
}


void LCChatRequestChatData::deserializeSQL(SQLStream &str)
{
  LobbyCommand::deserializeSQL(str);

  //check for result
  if(str.GetSize() == 0)
    return;
  //we expect one one value
  int nVal;
  //rows
  str >> nVal;
  if(nVal < 1)
    return;
  int nRowsNum = nVal;
  //cols
  str >> nVal;
  if(nVal != 5)
    return;
  int nI;
  for(nI = 0; nI < nRowsNum; nI++)
  {
    ChatInfoElem elem;
    str >> elem.nChatId    ;
    str >> elem.nChannelId ;
    str >> elem.nUserId    ;
    str >> elem.nTimeStamp ;
    str >> elem.sText      ; 

    m_chatInfo.push_back(elem);
  }
}


void LCChatRequestChatData::serializeReply(void) 
{
  LobbyCommand::serializeReply();
  MemoryStream &str = GetReplyStream();
  str << m_chatInfo.size();
  for(int nI = 0; nI < m_chatInfo.size(); nI++)
  {
    str << m_chatInfo[nI].nChatId;
    str << m_chatInfo[nI].nChannelId;    //channel it was said into
    str << m_chatInfo[nI].nUserId;       //one who said it
    str << m_chatInfo[nI].nTimeStamp;    //when it was said
    WriteStringToStream(str, m_chatInfo[nI].sText); 
  }
}
void LCChatRequestChatData::deserializeReply(void) 
{
  LobbyCommand::deserializeReply();
  int nInfos;
  MemoryStream &str = GetReplyStream();
  str >> nInfos;
  for(int nI = 0; nI < nInfos; nI++)
  {
    ChatInfoElem elem;
    str >> elem.nChatId;
    str >> elem.nChannelId;    //channel it was said into
    str >> elem.nUserId;       //one who said it
    str >> elem.nTimeStamp;    //when it was said
    m_chatInfo.push_back(elem);
  }
}

void LCChatRequestChatData::serialize(void)
{
  LobbyCommand::serialize(); 
  GetRequestStream() << m_nChatIDFrom; 
  GetRequestStream() << m_nTimeStampFrom;
  GetRequestStream() << m_bUseTimeStamp;
}

void LCChatRequestChatData::deserialize(ClientThread const *pClient) 
{
  LobbyCommand::deserialize(pClient); 
  GetRequestStream() >> m_nChatIDFrom;
  GetRequestStream() >> m_nTimeStampFrom;
  GetRequestStream() >> m_bUseTimeStamp;

  m_nUserID = pClient->GetAccoundId();
}

