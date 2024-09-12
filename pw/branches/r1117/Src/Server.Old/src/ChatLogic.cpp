/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "TypeProxy.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ClientThread.h"
#include "../../System/basic.h"
#include "../../System/nlist.h"
#include "../../System/nstring.h"
#include "../../System/nvector.h"
using namespace nstl;
#include "../../System/StrProc.h"
#include "../../System/ScopedArray.h"
#include "ServerApp.h"
#include "ListenerThread.h"
#include "ChatLogic.h"
#include "LCAuthenticateSimple.h"
#include "LCStartQuickGame.h"
#include "LCChatLeaveChannel.h"
#include "ChatLogic.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ChatLogic::~ChatLogic()
{
}

ChatLogic::ChatLogic()
:m_nLeaveChannelTimeLeft(0), m_nLeaveChannelTimePrev(time(NULL))
{
}

void ChatLogic::perform()
{
  const int nChatNotifyIntervalSec = 5;
  m_nLeaveChannelTimeLeft += time(NULL) - m_nLeaveChannelTimePrev;
  m_nLeaveChannelTimePrev = time(NULL);
  if(m_nLeaveChannelTimeLeft > nChatNotifyIntervalSec)
  {
    m_nLeaveChannelTimeLeft = 0;

    //perform once per sometime
    notifyLeaveChannel();
  }
}


void ChatLogic::notifyLeaveChannel()
{
  int nRes;
  nstl::wstring sReq(L"SELECT `user_id`, `channel_id` FROM `chat_channel_kicks` WHERE `sended` = FALSE;");
  SQLStream  sResult;
  nRes = DatabaseThread::Get()->performDBRequest(sReq, &sResult);
  if(nRes != 0)
  {
    return;
  }

  unsigned int nCommandsNum = 0;
  sResult >> nCommandsNum;

  unsigned int nColsNum = 0;
  sResult >> nColsNum;
  NI_ASSERT(nColsNum == 2, "Expected 2");
  unsigned int nI;
  for(nI = 0; nI < nCommandsNum; nI++)
  {
    int                 nUser_id;
    sResult >> nUser_id;
    int                 nChan_id;
    sResult >> nChan_id;
    LCChatLeaveChannel *pCmd     = new LCChatLeaveChannel(nChan_id, LCChatLeaveChannel::LR_UNKNOWN);
    ClientThread       *pClient = DatabaseThread::Get()->GetClientById(nUser_id);
    if(pClient != NULL)
    {
      CommandHolder hLeaveChan(pCmd);
      pClient->Send(hLeaveChan);
      const int nCommandBufferSize = 300;
      ScopedArray<wchar_t> pBuff(new wchar_t[nCommandBufferSize]);
      swprintf(&pBuff[0], nCommandBufferSize - 1, L"DELETE FROM `chat_channel_kicks` WHERE (`user_id` = %d) AND (`channel_id` = %d);",
               nUser_id, nChan_id);
      DatabaseThread::Get()->performDBRequest(nstl::wstring(&pBuff[0]), NULL);
    }

  }
}

