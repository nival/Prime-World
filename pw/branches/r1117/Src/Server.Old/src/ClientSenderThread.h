/*
 * ClientSenderThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef CLIENTSENDERTHREAD_H_
#define CLIENTSENDERTHREAD_H_

#include "TypeProxy.h"
#include "ServerThread.h"
#include "LobbyCommand.h"
#include "../System/Ring.h"

class ClientSenderThread: public ServerThread
{
  static const int             m_nDefaultSendBufferSize = 1024;
  int                          m_nSendBufferSize;
  NiSocket                     m_socket;
  UINT8                       *m_pBuff;
  CTSList<CommandHolder>       m_sendList;
  Semaphore                    m_semaphore;
  unsigned int                 &m_nAccountId;
  bool                         m_bInWork;
  protected:
  void ThreadMain(void);
  bool process(void);
public:
  void Send(CommandHolder &pHolder);
  void SetPacketSize(int nSize);
  ClientSenderThread(NiSocket &sock, unsigned int &accountId);
  virtual ~ClientSenderThread();
};


#endif /* CLIENTSENDERTHREAD_H_ */
