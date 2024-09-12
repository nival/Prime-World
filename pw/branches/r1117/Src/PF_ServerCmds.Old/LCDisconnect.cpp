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
#include <stdio.h>
#include "../System/basic.h"
#include "../System/nalgoritm.h"
#include "LCDisconnect.h"

REG_COMMAND_CPP(LCDisconnect);

#ifdef NI_PLATF_WIN
#pragma warning(push)
#pragma warning(disable: 4996)
#endif


void LCDisconnect::serializeReply(void)
{
  LobbyCommand::serializeReply();
  m_replyCmd << m_nReason;
  m_data.serialize(m_replyCmd);
}

void LCDisconnect::deserializeReply(void)
{
  LobbyCommand::deserializeReply();
  m_replyCmd >> m_nReason;
  m_data.deserialize(m_replyCmd);
}

#ifdef NI_PLATF_WIN
#pragma warning(pop)
#endif
