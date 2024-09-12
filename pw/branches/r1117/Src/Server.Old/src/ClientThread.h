/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef CLIENTTHREAD_H_
#define CLIENTTHREAD_H_

#include "TypeProxy.h"
#include "ServerThread.h"
#include "LobbyCommand.h"
#include "../System/Ring.h"
#include "../System/ScopedPtr.h"
#include "LobbyPacket.h"
#include "ClientSenderThread.h"

class ClientThread: public ServerThread
{

  NiSocket                m_socket;
  static const int        m_nDefaultRecieveBufferSize = 2048; 
  ScopedPtr<LobbyPacket>  m_pPacketer;

  unsigned int            m_nAccountId;    
  protected:
  void ThreadMain(void);
  bool process(void); 
  ClientSenderThread          *m_senderThread;
  CTSList<CommandHolder>       m_recievedList; 
  CTSList<CommandHolder>       m_recievingList; 

public:
  seDECLARE_RING(ClientThread, m_clientPart, Ring);

  void Send(CommandHolder &pHolder)  {m_senderThread->Send(pHolder);}
  CommandHolder GetNextCommand(); 

  //this function can be called from DB thread ONLY!
  void SetAccoundId(int nId);
  void SetPacketSize(int nId);
  int  GetAccoundId() const    {return m_nAccountId;} 

  ClientThread(NiSocket &sock);
  virtual ~ClientThread();
};


#endif /* CLIENTTHREAD_H_ */
