/*
* ServerApp.cpp
*
*  Created on: 14.10.2008
*      Author: earnol
*/

#include <conio.h>
#include <stdio.h>
#include <locale>
#include <tchar.h>
#include "ServerApp.h"
#include "ListenerThread.h"
#include "DatabaseThread.h"
#include "tclap/CmdLine.h"

void ServerApp::Run()
{
  WSADATA wsaData;
  int wsaret = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if(wsaret != 0)
  {
    return;
  }
  if(LOBYTE(wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) 
  {
      WSACleanup( );
      return; 
  }

  ListenerThread::Params listenrPars;
  listenrPars.m_nListenPort = 1024;
  DatabaseThread::Params dbPars;
  dbPars.m_nDBServerPort  = 3306;
  dbPars.m_sDBServerAddr  = "10.0.0.39";
  dbPars.m_sDBServerLogin = "PFLobby";
  dbPars.m_sDBServerPassw = "pflobbypflobby";

  // process command line arguments
  try
  {
    TCLAP::CmdLine cmd("This is the Primal Forces game server application.", ' ', "0.1");

    // server address
    TCLAP::ValueArg<std::string> serverAddrArg("d", "dbServer", "Specifies database server lobby server should connect to.",
      false, dbPars.m_sDBServerAddr.c_str(), "server_addr", cmd);

    // server port
    TCLAP::ValueArg<int> serverPortArg(_T("p"), _T("dbPort"), _T("Specifies database server lobby server should connect to. ")
      _T("Default value is 3306."),
      false, dbPars.m_nDBServerPort, _T("db_port"), cmd);

    // server login
    TCLAP::ValueArg<std::string> serverLoginArg("l", "login", "Specifies login lobby server should use to connect to database server.",
      false, dbPars.m_sDBServerLogin.c_str(), "db_login", cmd);

    // server password
    TCLAP::ValueArg<std::string> serverPasswordArg(_T("s"), _T("password"), _T("Specifies password lobby server should use to connect to database server."),
      false, dbPars.m_sDBServerPassw.c_str(), _T("db_password"), cmd);

    cmd.parse(m_nArgCount, m_cppArgs);

    //store back
    dbPars.m_sDBServerAddr  = serverAddrArg.getValue().c_str();
    dbPars.m_nDBServerPort  = serverPortArg.getValue();
    dbPars.m_sDBServerLogin = serverLoginArg.getValue().c_str();
    dbPars.m_sDBServerPassw = serverPasswordArg.getValue().c_str();

  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
  catch (char const* e)
  {
    std::cerr << "error: " << e << endl;
  }
  catch (std::string& e)
  {
    std::cerr << "error: " << e << endl;
  }

  ListenerThread::Init(listenrPars);
  ListenerThread *pListener = ListenerThread::Get();
  printf("Starting Listener thread ...\n");
  pListener->Run();

  printf("Starting database thread ...\n");
  DatabaseThread::Init(dbPars);
  DatabaseThread::Get()->Run();

  //no demonization under windows

  printf("Press any key to close server...\n");
  fflush(stdout);
  if(_getch())
  {}

  DatabaseThread::Term();
  ListenerThread::Term();
  WSACleanup();
}
