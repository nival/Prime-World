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
#include "QuickPlayLogic.h"
#include "LCAuthenticateSimple.h"
#include "LCStartQuickGame.h"
#include "LCChatLeaveChannel.h"
#include "QuickPlayLogic.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QuickPlayLogic::~QuickPlayLogic()
{
}

QuickPlayLogic::QuickPlayLogic()
: m_nQuickPlayTimeLeft(0), m_nQuickPlayTimePrev(time(NULL))
{
}

void QuickPlayLogic::perform()
{
  const int nQuickIntervalSec = 10;
  m_nQuickPlayTimeLeft += time(NULL) - m_nQuickPlayTimePrev;
  m_nQuickPlayTimePrev = time(NULL);
  if(m_nQuickPlayTimeLeft > nQuickIntervalSec)
  {
    m_nQuickPlayTimeLeft = 0;
    //perform once per sometime
    formQuickGames();
    notifyQuickGamesClients();
  }
}

bool QuickPlayLogic::formQuickGames()
{
  int nRes;
  nRes = DatabaseThread::Get()->performDBRequest(nstl::wstring(L"CALL gathergame();"), NULL);
  return nRes == 0;
}

void QuickPlayLogic::notifyQuickGamesClients()
{
  int nRes;
  nstl::wstring sReq(L"SELECT qp_gathered_game.gg_id, qp_gu_list.sended, qp_gu_list.user_id, \
                      user_accounts.lastip FROM `qp_gathered_game` LEFT JOIN `qp_gu_list` ON \
                      qp_gu_list.gg_id = qp_gathered_game.gg_id LEFT JOIN `user_accounts` ON user_accounts.user_id = qp_gu_list.user_id WHERE qp_gathered_game.start_flag = 'Y';");
  SQLStream  sResult;
  nRes = DatabaseThread::Get()->performDBRequest(sReq, &sResult);
  if(nRes != 0)
  {
    return;
  }

  //gather all commands we can theoretically send
  nstl::vector<CommandHolder> commandsList;

  //parse stream
  nstl::vector<LCStartQuickGame::ClientInfo> ciList;
  nstl::vector<bool>                         bWasSentList;
  unsigned int nCommandsNum = 0;
  sResult >> nCommandsNum;

  unsigned int nColsNum = 0;
  sResult >> nColsNum;
  NI_ASSERT(nColsNum == 4, "Expected 4");
  int nI, nJ, nStartJ;
  for(nI = 0; nI < (int)nCommandsNum; nI++)
  {
    LCStartQuickGame::ClientInfo ci;
    sResult >> ci.gameID;
    nstl::wstring temp_str;
    sResult >> temp_str;
    bool bWasSent = temp_str == L"Y";
    bWasSentList.push_back(bWasSent);
    sResult >> ci.accountID  ;
    sResult >> ci.clientIP   ;
    ciList.push_back(ci);
  }
  //build commands
  unsigned int nCurrGame = 0;
  for(nI = 0; nI < (int)nCommandsNum; nI++)
  {
    LCStartQuickGame * pCmd = new LCStartQuickGame();
    NI_ASSERT(nCurrGame <= ciList[nI].gameID, "Wrong order of goatherd games list");
    if(nCurrGame < ciList[nI].gameID)
    {
      nCurrGame = ciList[nI].gameID;
      nStartJ = nI;
    }
    nJ = nStartJ;
    while(nJ < ciList.size() && nCurrGame == ciList[nJ].gameID)
    {
      pCmd->clients.push_back(ciList[nJ]);
      nJ++;
    }
    commandsList.push_back(CommandHolder(pCmd));
  }

  //now for each clientInfo search through corresponding clients and notify
  for(nI = 0; nI < (int)nCommandsNum; nI++)
  {
    ClientThread * pClient = DatabaseThread::Get()->GetClientById(ciList[nI].accountID);
    if(pClient != NULL && !bWasSentList[nI])
    {
      pClient->Send(commandsList[nI]);
      //UPDATE list_gu SET `sended` = 'N' WHERE (`user_id` = 1981103) AND (`gg_id` = 1)
      ScopedArray<wchar_t> pBuff(new wchar_t[300]);
      swprintf(&pBuff[0], 299, L"UPDATE qp_gu_list SET `sended` = 'Y' WHERE (`user_id` = %d) AND (`gg_id` = %d);", ciList[nI].accountID, ciList[nI].gameID);
      DatabaseThread::Get()->performDBRequest(&pBuff[0], NULL);
    }
  }
}
