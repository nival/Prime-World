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
#include "LCAuthenticateSimple.h"

REG_COMMAND_CPP(LCAuthenticateSimple);

#ifdef NI_PLATF_WIN
#pragma warning(push)
#pragma warning(disable: 4996)
#endif
nstl::wstring LCAuthenticateSimple::serializeSQL(void)
{
  nstl::wstring sRet(L"SELECT `user_id` FROM `user_accounts` WHERE (`login` = \"");
  sRet += m_sLogin + L"\") AND (`password` = \"" + m_sPassword + L"\")";
  return sRet;
}

void LCAuthenticateSimple::serialize(void)
{
  LobbyCommand::serialize();
  m_requestCmd << m_sLogin;
  m_requestCmd << m_sPassword;
  m_requestCmd << m_nPacketSize;
}

void LCAuthenticateSimple::deserialize(class ClientThread const *p)
{
  LobbyCommand::deserialize(p);
  m_requestCmd >> m_sLogin   ;
  m_requestCmd >> m_sPassword;
  m_requestCmd >> m_nPacketSize;
  //logick
  m_nPacketSize = min(m_nPacketSize, 10*1024);
}

void LCAuthenticateSimple::serializeReply(void)
{
  LobbyCommand::serializeReply();
  m_replyCmd.Write(&m_nAccountId, sizeof(m_nAccountId));
}

void LCAuthenticateSimple::deserializeReply(void)
{
  LobbyCommand::deserializeReply();
  m_replyCmd.Read(&m_nAccountId, sizeof(m_nAccountId));
}

void LCAuthenticateSimple::deserializeSQL(SQLStream &str)
{
  LobbyCommand::deserializeSQL(str);

  //check for result
  if(str.GetSize() == 0)
    return;
  //we expect one one value
  unsigned int nVal;
  //rows
  str >> nVal;
  if(nVal != 1)
    return;
  //cols
  str >> nVal;
  if(nVal != 1)
    return;
  str >> m_nAccountId;
}

#ifdef NI_PLATF_WIN
#pragma warning(pop)
#endif
