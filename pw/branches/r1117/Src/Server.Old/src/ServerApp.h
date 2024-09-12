/*
 * ServerApp.h
 *
 *  Created on: 15.10.2008
 *      Author: earnol
 */

#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#include "TypeProxy.h"
#include "ServerThread.h"
#include "../../Net/TSList.h"
#include "../../System/Ring.h"
#include "../../System/Singleton.h"
#include "ClientThread.h"

class ServerApp: public Singleton<ServerApp>
{
  int    m_nArgCount;
  char **m_cppArgs;

public:
  ClientThread::Ring m_recieveClients;

  ServerApp (int argc, char **argv)
  {
    m_nArgCount = argc;
    m_cppArgs = argv;
    m_recieveClients.reset();
  }
  void Run();
#ifdef NI_PLATF_LINUX
private:
  Semaphore m_wantTerminate;
  void daemonize();
  static void sighandler(int signum);
  static void sigtermhandler(int signum);
#endif
};

#endif /* SERVERAPP_H_ */
