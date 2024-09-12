/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef SERVERLOGIC_H_
#define SERVERLOGIC_H_

#include "TypeProxy.h"
#include <time.h>
#include "../../System/basic.h"
#include "ServerThread.h"
#include "../../Net/TSList.h"
#include "../../System/Ring.h"
#include "../../System/Singleton.h"
#include "../../System/nstring.h"
#include "mysql.h"
#include "SQLStream.h"
#include "DatabaseThread.h"
#include "QuickPlayLogic.h"
#include "ChatLogic.h"


class ServerLogic: public Singleton<ServerLogic>
{
public:
  struct LoginQueueEntry
  {
    CommandHolder loginCommand;
    time_t        nTimeEntered; 
    ClientThread *pClient;
    LoginQueueEntry(CommandHolder cmd, time_t t, ClientThread *p): loginCommand(cmd), nTimeEntered(t), pClient(p) {}
  };
  typedef nstl::vector<LoginQueueEntry> LoginQueue;

  ServerLogic();
  virtual ~ServerLogic();

  //perform logic calls besides user serving
  void logicPerform();

  //quick play logic
  QuickPlayLogic    m_quickPlay;  

  ChatLogic         m_chat; 

  LoginQueue        m_loginQueue;

  void logicAuth();
  void authProcessDelayed();
  void authIssueDisc();

  bool onCommandRecieved(ClientThread *pClient, CommandHolder &holder);

  bool onClientDestroy(ClientThread *pClient);

  //perform quick play logic
  void logicRemoveDeadClients();

  //stop of server logic
  void logicKickAllClients();

  //on-connect logic
  void logicAddNewClients();

  void loadSQLLogic(char const *path);
  void loadSQLScriptFile(char const *path);
};


#endif /* SERVERLOGIC_H_ */
