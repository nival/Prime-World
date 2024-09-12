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
#include "LCStartQuickGame.h"

REG_COMMAND_CPP(LCStartQuickGame);

#ifdef NI_PLATF_WIN
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

void LCStartQuickGame::serializeReply(void)
{
  LobbyCommand::serializeReply();
  m_replyCmd << clients.size();
  for(int nI = 0; nI < clients.size(); nI++)
  {
    m_replyCmd << clients[nI].team;
    m_replyCmd << clients[nI].clientIP;
    m_replyCmd << clients[nI].accountID;
    m_replyCmd << clients[nI].gameID;
  }
}

void LCStartQuickGame::deserializeReply(void)
{
  LobbyCommand::deserializeReply();
  //do not try before received completely
  int nInfos;
  m_replyCmd >> nInfos;
  for(int nI = 0; nI < nInfos; nI++)
  {
    ClientInfo info;
    m_replyCmd >> info.team;
    m_replyCmd >> info.clientIP;
    m_replyCmd >> info.accountID;
    m_replyCmd >> info.gameID;
    clients.push_back(info);
  }
}



#ifdef NI_PLATF_WIN
#pragma warning(pop)
#endif
