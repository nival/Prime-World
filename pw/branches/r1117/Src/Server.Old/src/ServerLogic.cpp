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
#include "ServerLogic.h"
#include "LCAuthenticateSimple.h"
#include "LCStartQuickGame.h"
#include "LCDisconnect.h"
#include "ServerLogic.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ServerLogic::~ServerLogic()
{
}

ServerLogic::ServerLogic()
: m_quickPlay(), m_chat()
{
}


bool ServerLogic::onClientDestroy(ClientThread *pClient)
{
  ScopedArray<wchar_t> pBuf(new wchar_t[200]);
  swprintf(&pBuf[0], 199, L"CALL on_user_disconnect(%d);", pClient->GetAccoundId());
  DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);

  //remove all clients entries from login queue
  LoginQueue::iterator b = m_loginQueue.begin();
  LoginQueue::iterator e = m_loginQueue.end();
  for(; b != e; )
  {
    if(b->pClient == pClient)
    {
      LoginQueue::iterator td = b;
      b++;
      bool bWantBreak = false;
      if(b == e)
        bWantBreak = true;
      m_loginQueue.erase(td);
      e = m_loginQueue.end();
      if(bWantBreak)
        break;
      continue;
    }
    b++;
  }

  return true;
}

bool ServerLogic::onCommandRecieved(ClientThread *pClient, CommandHolder &holder)
{
  bool bRet = true;
  if(holder->GetCommandNumber() == 0)
  {
    LCAuthenticateSimple *p;
    if((p = LCAuthenticateSimple::DynamicCast(holder)) != NULL)
    {
      pClient->SetPacketSize(p->GetPacketSize());
      if(p->GetAccountId() <= 0)
      {
        CommandHolder pDisc(new LCDisconnect(LCDisconnect::DR_INVALID_LOGIN));
        pClient->Send(pDisc);
        pClient->Disconnect();
      }
      else
      {
        //verify we are alone
        ScopedArray<wchar_t> pBuf(new wchar_t[200]);
        swprintf(&pBuf[0], 199, L"SELECT `user_id` FROM `user_accounts` WHERE (`user_id` = %d) AND (`online` = TRUE);", p->GetAccountId());
        SQLStream reply;
        DatabaseThread::Get()->performDBRequest(&pBuf[0], &reply);
        unsigned int nNum;
        reply >> nNum;
        if(nNum == 0)
        {
          pClient->SetAccoundId(p->GetAccountId());
        }
        else
        {
          //register kick
          swprintf(&pBuf[0], 199, L"INSERT INTO `user_kicks` (`user_id`) VALUES (%d);", p->GetAccountId());
          DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);
          //put user on_hold
          LoginQueueEntry e(holder, time(NULL), pClient);
          m_loginQueue.push_back(e);
          bRet = false;
        }
      }
    }
  }
  return bRet;
}

void ServerLogic::authProcessDelayed()
{
  const int nMaxTimeout = 60;

  ScopedArray<wchar_t> pBuf(new wchar_t[200]);
  LoginQueue::iterator b = m_loginQueue.begin();
  LoginQueue::iterator e = m_loginQueue.end();
  for(; b != e; )
  {
    NI_ASSERT(LCAuthenticateSimple::DynamicCast(b->loginCommand) != NULL, " Only login commands can be in queue.");
    // fast cast
    LCAuthenticateSimple *p = (LCAuthenticateSimple *)b->loginCommand.operator ->();

    //check login queue and validate kicks
    swprintf(&pBuf[0], 199, L"SELECT `user_id` FROM `user_kicks` WHERE `user_id` = %d;", p->GetAccountId());
    SQLStream reply;
    DatabaseThread::Get()->performDBRequest(&pBuf[0], &reply);
    unsigned int nNum;
    reply >> nNum;
    if(nNum == 0 || (nMaxTimeout < (time(NULL) - b->nTimeEntered)))
    {
      if(nNum != 0)
      {
        swprintf(&pBuf[0], 199, L"DELETE FROM `user_kicks` WHERE `user_id` = %d LIMIT 1;", p->GetAccountId());
        DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);
        swprintf(&pBuf[0], 199, L"CALL on_user_disconnect(%d);", p->GetAccountId());
        DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);
      }
      //kick disappeared: safe to login
      b->pClient->SetAccoundId(p->GetAccountId());
      b->pClient->Send(b->loginCommand);
      LoginQueue::iterator td = b;
      b++;
      bool bWantBreak = false;
      if(b == e)
        bWantBreak = true;
      m_loginQueue.erase(td);
      e = m_loginQueue.end();
      if(bWantBreak)
        break;
      continue;
    }
    b++;
  }
}

void ServerLogic::authIssueDisc()
{
  ScopedArray<wchar_t> pBuf(new wchar_t[200]);
  swprintf(&pBuf[0], 199, L"SELECT `user_id` FROM `user_kicks`;");
  SQLStream reply;
  DatabaseThread::Get()->performDBRequest(&pBuf[0], &reply);
  unsigned int nNum;
  reply >> nNum;
  if(nNum == 0)
  {
    //no pending disconnects
    return;
  }
  unsigned int nCols;
  reply >> nCols;
  NI_ASSERT(nCols == 1, "Only one column is expected.");
  for(unsigned int nI = 0; nI < nNum; nI++)
  {
    unsigned int nClinetId;
    reply >> nClinetId;
    ClientThread *pClient = NULL;
    if(NULL != (pClient = DatabaseThread::Get()->GetClientById(nClinetId)))
    {
      swprintf(&pBuf[0], 199, L"DELETE FROM `user_kicks` WHERE `user_id` = %d LIMIT 1;", nClinetId);
      DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);
      CommandHolder pDisc(new LCDisconnect(LCDisconnect::DR_OTHER_USER_LOGGED));
      pClient->Send(pDisc);
      pClient->Disconnect();
    }
  }
}

void ServerLogic::logicAuth()
{
  authIssueDisc();
  authProcessDelayed();
}

void ServerLogic::logicPerform()
{
  //add new clients
  logicAddNewClients();

  //kill disconnected clients
  logicRemoveDeadClients();

  logicAuth();

  //perform quick play related tasks
  m_quickPlay.perform();

  //perform chat related tasks
  m_chat.perform();
}

void ServerLogic::logicRemoveDeadClients()
{
  //now iterate with clients
  ClientThread *const pClientLast = ServerApp::Get()->m_recieveClients.last();
  for (ClientThread *pClient = ServerApp::Get()->m_recieveClients.first(); pClient != pClientLast;)
  {
    //remove disconnected client
    if(!pClient->IsConnected())
    {
      ClientThread *pClientToDel = pClient;
      pClient = ClientThread::Ring::next(pClient);
      delete pClientToDel;
      continue;
    }
    //next
    pClient = ClientThread::Ring::next(pClient);
  }
}

void ServerLogic::logicAddNewClients()
{
  while(!ListenerThread::Get()->GetClientsList().IsEmpty())
  {
    ClientThread *pClient = *ListenerThread::Get()->GetClientsList().GetFront();
    ListenerThread::Get()->GetClientsList().PopFront();
    //save client
    ServerApp::Get()->m_recieveClients.addLast(pClient);
  }
}

void ServerLogic::logicKickAllClients()
{
  //add and then kick
  logicAddNewClients();

  //now iterate with clients
  ClientThread *const pClientLast = ServerApp::Get()->m_recieveClients.last();
  for (ClientThread *pClient = ServerApp::Get()->m_recieveClients.first(); pClient != pClientLast;)
  {
    //remove client
    ClientThread *pClientToDel = pClient;
    pClient = ClientThread::Ring::next(pClient);
    delete pClientToDel;
    continue;
  }
}


#ifdef NI_PLATF_WIN
  #pragma warning(push)
  #pragma warning(disable: 4996)
#endif
void ServerLogic::loadSQLScriptFile(char const * cpPath)
{
  unsigned long  nFileSize;
  FILE *fp = fopen(cpPath, "rb");
  if(fp == NULL)
    return;
#ifndef NI_PLATF_WIN
  struct stat fileStats;
  if(stat(cpPath, &fileStats) == 0)
#else
  struct __stat64 fileStats;
  if(_stat64(cpPath, &fileStats) == 0)
#endif
  {
     nFileSize = fileStats.st_size;
  }
  NI_VERIFY(nFileSize > 0, "File size is zero.", fclose(fp); return;);
  ScopedArray<char> pBuff(new char[nFileSize + 1]);
  pBuff[nFileSize] = '\0';

  fread(&pBuff[0], sizeof(char), nFileSize, fp);
  fclose(fp);
  //execute
  DatabaseThread::Get()->performDBRequest(&pBuff[0], nFileSize, NULL);
}
#ifdef NI_PLATF_WIN
  #pragma warning(pop)
#endif

void ServerLogic::loadSQLLogic(char const * cpPath)
{
  nstl::string filePath;
  filePath = cpPath;
  loadSQLScriptFile(nstl::string(filePath + "account.sql").c_str());
  loadSQLScriptFile(nstl::string(filePath + "chat.sql").c_str());
  loadSQLScriptFile(nstl::string(filePath + "quickplay.sql").c_str());
}

