/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef LISTENERTHREAD_H_
#define LISTENERTHREAD_H_

#include "TypeProxy.h"
#include "ServerThread.h"
#include "../../Net/TSList.h"
#include "../../System/Ring.h"
#include "../../System/Singleton.h"

class ListenerThread: public ServerThread, public Singleton<ListenerThread>
{
public:
  struct Params
  {
    int       m_nListenPort; //port we are listening
  };
  typedef CTSList<ClientThread *> ClientsList;

  ListenerThread(Params &pars): m_pars(pars), m_bWantExit(false) {}
  virtual ~ListenerThread();
  ClientsList &GetClientsList() {return m_clientsToAdd;}
  void        SetWantExit() {m_bWantExit = true;}
protected:
  Params    m_pars;
  bool      m_bWantExit; 
  NiSocket  m_ListenSocket;
  void ThreadMain(void);
private:
  ClientsList m_clientsToAdd;

};


#endif /* LISTENERTHREAD_H_ */
