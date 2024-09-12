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
#include "LCRegisterQuickGame.h"

REG_COMMAND_CPP(LCRegisterForQuickGame);

                                              
nstl::wstring LCRegisterForQuickGame::serializeSQL(void)
{
  if(m_nAccountId >= 1)
  {
    nstl::wstring sDel(L"DELETE FROM `qp_queue` WHERE `user_id` = ");
    nstl::wstring sRet(L"; INSERT INTO `qp_queue` (`user_id`) VALUES (");
    wchar_t accID[30];
    //itoa does not exists under GCC
    int_itoa((int)m_nAccountId, accID, 10);
    sDel += accID;
    sRet  = sDel + sRet;
    sRet += accID;
    sRet += L");";
    return sRet;
  }
  else
  {
    return nstl::wstring(L"");
  }
}

void LCRegisterForQuickGame::deserialize(ClientThread const *pClient) 
{
  LobbyCommand::deserialize(pClient); 
  GetRequestStream() >> m_nAccountId;
  if(pClient->GetAccoundId() != m_nAccountId)
  {
    //correct wrong client
    m_nAccountId = pClient->GetAccoundId();
    //and note cheater
  }

}
