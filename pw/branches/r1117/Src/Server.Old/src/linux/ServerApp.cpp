/*
* ServerApp.cpp
*
*  Created on: 14.10.2008
*      Author: earnol
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include "../ServerApp.h"
#include "../ListenerThread.h"
#include "../DatabaseThread.h"

void ServerApp::sighandler(int signum)
{
  waitpid(0, 0, WNOHANG);
}

void ServerApp::sigtermhandler(int signum)
{
  if(SIGTERM == signum)
  {
    ServerApp::Get()->m_wantTerminate.Post();
  }
}


void ServerApp::daemonize()
{
  int pid;
  struct sigaction sa;

  printf("Server starting... ");
  pid = fork();

  switch(pid)
  {
    case 0:
    {
      setsid();
      chdir("/");

      close(0);
      close(1);
      close(2);

      memset(&sa, 0, sizeof(sa));
      sa.sa_handler = &sighandler;
      sigaction(SIGCHLD, &sa, 0);
      memset(&sa, 0, sizeof(sa));
      sa.sa_handler = &sigtermhandler;
      sigaction(SIGTERM, &sa, 0);

      openlog("tcp_daemon", 0, LOG_USER);
    }
    case -1:
    {
      printf("fork() error\n");
      break;
    }

    default:
    {
      printf("ok. PID = %d\n", pid);
      exit(0);
      break;
    }
  }
}

void ServerApp::Run()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = &sigtermhandler;
  sigaction(SIGTERM, &sa, 0);

  printf("Performing demonization ...\n");
  //daemonize();

  ListenerThread::Params listenrPars;
  listenrPars.m_nListenPort = (m_nArgCount > 1)? atol(m_cppArgs[1]): 1024;
  ListenerThread::Init(listenrPars);
  ListenerThread *pListener = ListenerThread::Get();
  printf("Starting Listener thread ...\n");
  pListener->Run();

  DatabaseThread::Params dbPars;
  dbPars.m_nDBServerPort  = 3306;
  dbPars.m_sDBServerAddr  = "10.0.0.39";
  dbPars.m_sDBServerLogin = "PFLobby";
  dbPars.m_sDBServerPassw = "pflobbypflobby";
  printf("Starting database thread ...\n");
  DatabaseThread::Init(dbPars);
  DatabaseThread::Get()->Run();

  m_wantTerminate.Wait();

  DatabaseThread::Term();
  ListenerThread::Term();

  closelog();
}
