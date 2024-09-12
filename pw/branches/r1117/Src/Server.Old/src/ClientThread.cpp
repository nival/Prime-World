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

#include "CommandFactory.h"
#include "LobbyCommand.h"
#include "DatabaseThread.h"
#include "ServerLogic.h"
#include "ClientThread.h"


ClientThread::ClientThread(NiSocket &sock): m_socket(sock), m_pPacketer(new LobbyPacket(m_nDefaultRecieveBufferSize)), m_nAccountId(0)
{
  m_senderThread = new ClientSenderThread(sock, m_nAccountId);
}

void ClientThread::SetPacketSize(int nSize)
{
  m_senderThread->SetPacketSize(nSize);
  //just relay, since it is recommendation for sender only
}


ClientThread::~ClientThread()
{
  // Remove from the ring if we are here
  if (m_clientPart.isLinked())
  {
    Ring::remove(this);
  }

  ServerLogic::Get()->onClientDestroy(this);

  NI_SERVER_LOG_L2(("ClientID: %d disconnected.\n", m_nAccountId));

  delete m_senderThread;

#ifdef NI_PLATF_LINUX
    //discard any data OS going to deliver to us, still attempting to deliver all leftovers
    shutdown(m_socket, 0);
    close(m_socket);
  #else
    closesocket(m_socket);
  #endif

  //thread should exit es soon as socket is closed
  Join(m_threadHandle);
  //and invalidate
  m_threadHandle = (Thread<void>::Handle)-1;
}

//return true if continue needed
bool ClientThread::process()
{
  LobbyPacket::PacketInfo  packet;
  bool bOk = m_pPacketer->ReceiveLobbyCommandPacket(m_socket, packet);
  if(!bOk)
  {
    return false;
  }

  //look in our commands queue for this command
  CommandHolder *pHolder = NULL;
  int            nI      = 0;
  bool           bCommandFound = false;
  while((pHolder = m_recievingList.GetFront(nI)) != NULL)
  {
    NI_ASSERT((*pHolder)->getStatus() == LobbyCommand::CS_RECEIVING, "Wronmg command status.");
    if((*pHolder)->GetCommandNumber() == packet.m_nCommandNumber)
    {
      NI_SERVER_LOG_L2(("Long command recieved (cnt.) cmd name: %s clientID: %d cmdNum: %d \n", (*pHolder)->GetCmdClassName(), m_nAccountId, (*pHolder)->GetCommandNumber()));
      NI_ASSERT(packet.m_nCommandSize == -1, "Should be initted by this point.");
      //write data to this command
      (*pHolder)->GetRequestStream().Write(packet.m_pDataStream->GetBuffer(), packet.m_pDataStream->GetSize());
      bCommandFound = true;
      if((*pHolder)->requestSize() == (*pHolder)->getTotalRequestSize())
      {
        NI_SERVER_LOG_L2(("Long command recieved end cmd name: %s clientID: %d cmdNum: %d \n", (*pHolder)->GetCmdClassName(), m_nAccountId, (*pHolder)->GetCommandNumber()));

        //well command is received completely: Deserialize it!
        (*pHolder)->GetRequestStream().Seek(0, SEEKORIGIN_BEGIN);
        (*pHolder)->deserialize(this);

        (*pHolder)->SetStatus(LobbyCommand::CS_RECEIVED);
      }
      break;
    }
  }
  //create new command
  if(!bCommandFound)
  {
    NI_ASSERT(packet.m_bFirstPacket, "Here we should encounter only first packet.");
    CommandFactory* pFacCommand = CommandFactory::CreateInstance(packet.m_nCommandType);
    //it's safe since we expect only lobby command here
    LobbyCommand* pCommand = (LobbyCommand *) pFacCommand;

    pCommand->SetStatus(LobbyCommand::CS_RECEIVING);

    CommandHolder pHolder(pCommand); //create hosted pointer

    //write data
    pCommand->GetRequestStream().Write(packet.m_pDataStream->GetBuffer(), packet.m_pDataStream->GetSize());
    pCommand->SetCommandNumber(packet.m_nCommandNumber);
    pCommand->SetRequestSize(packet.m_nCommandSize);
    pCommand->SetReceivedFromClient();
    pCommand->SetReply();

    NI_SERVER_LOG_L2(("New command recieved start cmd name: %s clientID: %d cmdNum: %d \n", pCommand->GetCmdClassName(), m_nAccountId, pCommand->GetCommandNumber()));

    if(pCommand->requestSize() == pCommand->getTotalRequestSize())
    {
      pCommand->SetStatus(LobbyCommand::CS_RECEIVED);
      //well command is received completely: Deserialize it!
      pCommand->GetRequestStream().Seek(0, SEEKORIGIN_BEGIN);
      NI_SERVER_LOG_L2(("Command received end cmd name: %s clientID: %d cmdNum: %d \n", pCommand->GetCmdClassName(), m_nAccountId, pCommand->GetCommandNumber()));
      pCommand->deserialize(this);
    }
    //put to storage
    *m_recievingList.GetBack() = pHolder;
    //increase list
    m_recievingList.PushBack();
  }
  //extort all received commands
  while((pHolder = m_recievingList.GetFront(nI)) != NULL)
  {
    if((*pHolder)->getStatus() == LobbyCommand::CS_RECEIVED)
    {
      //store reference locally
      CommandHolder pCmd = *pHolder;
      //take it
      m_recievingList.PopFront(nI);
      *m_recievedList.GetBack() = pCmd;
      m_recievedList.PushBack();
    }
  }
  return true;
}

void ClientThread::ThreadMain()
{
  NI_ASSERT(m_senderThread != NULL, "Sender thread already exists?");
  //start sender
  m_senderThread->Run();

  //enter the loop
  while(process())  {;}

  //finish up
  m_bConnected   = false;
}

void ClientThread::SetAccoundId(int nId)
{
  m_nAccountId = nId;
  if(m_nAccountId < 1)
  {
    //invalid authentication
    return;
  }

  //notify BD about new ID
  struct sockaddr_in sa;
  socklen_t          saSize = sizeof(sa);
  int nError = getpeername(m_socket, (struct sockaddr *) &sa, &saSize);
  if(nError == SOCKET_ERROR)
  {
    NI_ALWAYS_ASSERT("Need to look closer, when this happens.");
    return;
  }

  NI_SERVER_LOG_L2(("Successful login from %s. clientID: %d \n", inet_ntoa(sa.sin_addr), m_nAccountId));

  //unsigned long nIPAddr = ntohl(sa.sin_addr.s_addr);
  char *cpAddr = inet_ntoa(sa.sin_addr);
  nstl::wstring sAddr = LobbyCommand::Utf8ToUnc16(cpAddr);
  ScopedArray<wchar_t> pBuf(new wchar_t[200]);
  //UPDATE user_accounts SET `lastip` = INET_ATON('10.0.0.12') WHERE `user_id` = '1981103';
  swprintf(&pBuf[0], 199, L"UPDATE user_accounts SET `lastip` = INET_ATON('%s'), `online` = TRUE WHERE `user_id` = %d;", sAddr.c_str(), m_nAccountId);
  DatabaseThread::Get()->performDBRequest(&pBuf[0], NULL);
}

CommandHolder ClientThread::GetNextCommand()
{
  if(m_recievedList.IsEmpty())
  {
    return CommandHolder(NULL);
  }
  CommandHolder pHolder;
  CommandHolder *pp, *pDesPointer;
  int nI = 0;
  int nIdx = 0;
  LobbyCommand::Priority prio = LobbyCommand::CP_LOW;
  pDesPointer = m_recievedList.GetFront();
  while((pp = m_recievedList.GetFront(nI)) != NULL)
  {
    if((*pp)->getPriority() > prio)
    {
      pDesPointer = pp;
      prio        = (*pp)->getPriority();
      nIdx        = nI;
      if(prio == LobbyCommand::CP_HIGH)
      {
        break;
      }
    }
    nI += 1;
  }
  //regardless of result we remove from client: remove ownership
  pHolder = *pDesPointer;
  m_recievedList.PopFront(nIdx);

  return pHolder;
}

