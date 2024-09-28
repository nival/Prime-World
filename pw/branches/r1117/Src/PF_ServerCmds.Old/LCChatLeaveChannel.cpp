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
#include "../System/basic.h"
#include "../System/nalgoritm.h"
#include "../Server/src/ClientThread.h"
#include "LCChatLeaveChannel.h"

REG_COMMAND_CPP(LCChatLeaveChannel);

void LCChatLeaveChannel::serializeReply(void)
{
  LobbyCommand::serializeReply();

  m_replyCmd << m_nChannelId;
  m_replyCmd << m_nLeaveReason;
}

void LCChatLeaveChannel::deserializeReply(void)
{
  LobbyCommand::deserializeReply();

  //do not try before received completely
  m_replyCmd    >> m_nChannelId;
  m_replyCmd    >> m_nLeaveReason;
}


