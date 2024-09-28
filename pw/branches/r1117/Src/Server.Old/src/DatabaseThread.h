/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef DATABASETHREAD_H_
#define DATABASETHREAD_H_

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
#include "ClientThread.h"

class DatabaseThread: public ServerThread, public Singleton<DatabaseThread>
{
public:
  struct Params
  {
    nstl::string       m_sDBServerAddr; //server address we are connecting to
    int                m_nDBServerPort;
    nstl::string       m_sDBServerLogin;
    nstl::string       m_sDBServerPassw;
    nstl::string       m_sSQLLogicPath;
    Params()
    {
      m_sSQLLogicPath = nstl::string("../ServerData/SQLProcs/");
    }
  };

  DatabaseThread(Params &pars);
  virtual ~DatabaseThread();
  void WaitForGraciousTerminate();
  ClientThread * GetClientById(int nAccId);

  //do DB work, reply can be NULL, in this case DB reply is ignored
  int  performDBRequest(nstl::wstring const &request, SQLStream *reply) {return performDBRequest(request.c_str(), reply);}
  int  performDBRequest(wchar_t const *request, SQLStream *reply);
  int  performDBRequest(char const *pUTF8Request, unsigned int nRequestSize, SQLStream *reply);

protected:
  Params m_pars;
  MYSQL *m_pConnection;
  //CTSList
  void ThreadMain(void);
  bool   m_bWantExit;

  void setWantExit() {m_bWantExit = true;}

  //perform logic calls besides user serving
  void logicPerform();
};


#endif /* DATABASETHREAD_H_ */
