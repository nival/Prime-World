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
#include "LobbyPacket.h"
#include "ClientSenderThread.h"


ClientSenderThread::ClientSenderThread(NiSocket &sock, unsigned int &accountId):
  m_nSendBufferSize(m_nDefaultSendBufferSize)
, m_socket(sock)
, m_pBuff(NULL)
, m_sendList()
, m_semaphore(0) //0 commands initially in queue
, m_nAccountId(accountId)
, m_bInWork(false)
{
  m_pBuff = (UINT8 *)::malloc(m_nSendBufferSize + 1);
  NI_VERIFY(m_pBuff != NULL, "No memory", ;);
}

ClientSenderThread::~ClientSenderThread()
{
  //send all messages to client
  while(!m_sendList.IsEmpty())
  {
#ifdef NI_PLATF_LINUX
    sched_yield();
#else
    Sleep(1);
#endif
  }
  //signal to stop
  m_bConnected = false;
  m_semaphore.Post();

  //wait to finish and invalidate
  Join(m_threadHandle);
  m_threadHandle = (Thread<void>::Handle)-1;
  //free memory and have sending queue to die itself
  free(m_pBuff);
}

bool ClientSenderThread::process()
{
  //basically if we are to terminate during wait ==> fuck the wait and terminate
  if(!m_bConnected)
    return false;

  NI_ASSERT(!m_sendList.IsEmpty(), "Should not be empty at this point!");
  //find cmd with highest priority
  CommandHolder *pHolder = m_sendList.GetFront(0);
  CommandHolder *pSelectedHolder = pHolder;
  int nI = 1, nSelectedIdx = 0;
  do
  {
    pHolder = m_sendList.GetFront(nI);
    if(pHolder != NULL && (int)(*pHolder)->getPriority() > (int)(*pSelectedHolder)->getPriority())
    {
      pSelectedHolder = pHolder;
      nSelectedIdx    = nI;
    }
    nI++;
  } while (pHolder != NULL);

  int  nPrevStreamPos = (*pSelectedHolder)->GetReplyStream().GetPosition(); ((void)nPrevStreamPos);
  bool bOk = LobbyPacket::SendLobbyCommandPacket(m_socket, *pSelectedHolder, (*pSelectedHolder)->GetReplyStream(), m_pBuff, m_nSendBufferSize);

  //Sleep(1); //this code is to test command interleaving
  //we have sending messages
  if(!bOk)
  {
    printf("Sending error in file: %s error: %d", __FILE__, errno);
    return false;
  }
  NI_SERVER_LOG_L2(("Command: % s send to clientID: %d from %d - %d\n", (*pSelectedHolder)->GetCmdClassName(), m_nAccountId, nPrevStreamPos, (*pSelectedHolder)->GetReplyStream().GetPosition() - 1));


  //check if we have send everything or not?
  if((*pSelectedHolder)->GetReplyStream().GetPosition()  == (*pSelectedHolder)->GetReplyStream().GetSize())
  {
    //remove from list
    m_sendList.PopFront(nSelectedIdx);
  }
  else
  {
    (*pSelectedHolder)->SetStatus(LobbyCommand::CS_SENDING);

    //if we have not send command completely we have to post again!
    m_semaphore.Post();
  }
  return true;
}

void ClientSenderThread::SetPacketSize(int nSize)
{
  if(nSize != m_nSendBufferSize)
  {
    NI_ASSERT(m_bInWork == false, "Needs to be investigated if true.");
    //wait synchrony
    while(m_bInWork)
    {
  #ifdef NI_PLATF_LINUX
      sched_yield();
  #else
      Sleep(1);
  #endif
    }
    m_nSendBufferSize = nSize;
    m_pBuff = (UINT8 *)::realloc(m_pBuff, m_nSendBufferSize);
  }
}

void ClientSenderThread::ThreadMain()
{
  int nSendBuffer = 2048;
  int nError            ;
  nError = setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char *)&nSendBuffer, sizeof(nSendBuffer));
  NI_ASSERT(nError == 0, "Failure to set socket option.");

  while(true)
  {
    //wait for at least one message to send
    m_semaphore.Wait();
    m_bInWork = true;
    if(!process())
    {
      m_bInWork = false;
      break;
    }
    m_bInWork = false;
  }

  m_bConnected   = false;
}

void ClientSenderThread::Send(CommandHolder &pHolder)
{
  NI_ASSERT(pHolder->GetReplyStream().GetSize() == 0, "Reply stream should be empty at this point");
  //propagate ID
  if(pHolder->m_nCommandID == -1)
  {
    pHolder->setCommandID();
  }
  pHolder->SetReceivedFromServer();
  //say command to prepare for sending
  pHolder->serializeReply();
  //rewind stream
  pHolder->GetReplyStream().Seek(0, SEEKORIGIN_BEGIN);
  //Well push it and signal semaphore
  *m_sendList.GetBack() = pHolder;
  m_sendList.PushBack();

  //signal
  m_semaphore.Post();

}

