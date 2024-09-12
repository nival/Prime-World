/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "TypeProxy.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ClientThread.h"
#include "ServerApp.h"

#include "ListenerThread.h"

ListenerThread::~ListenerThread()
{
  m_bWantExit = true;
#ifdef NI_PLATF_LINUX
  //discard any data OS going to deliver to us, still attempting to deliver all leftovers
  shutdown(m_ListenSocket, SHUT_RD);
  close(m_ListenSocket);
#else
  closesocket(m_ListenSocket);
#endif
  Join(m_threadHandle);
}

void ListenerThread::ThreadMain()
{
  NiSocket fd;
  struct sockaddr_in sa;
  socklen_t n;

  m_ListenSocket = socket(PF_INET, SOCK_STREAM, 0);

  if(m_ListenSocket != -1)
  {
    memset(&sa, 0, sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(m_pars.m_nListenPort);

    if(bind(m_ListenSocket, (struct sockaddr *) &sa, sizeof(sa)) != -1)
    {
      if(SOCKET_ERROR != listen(m_ListenSocket, SOMAXCONN - 1))
      {
        while(true)
        {
          n = sizeof(sa);
          if((fd = accept(m_ListenSocket, (struct sockaddr *) &sa, &n)) != SOCKET_ERROR)
          {
            NI_SERVER_LOG(("Connection from %s. Socket assigned: %d \n", inet_ntoa(sa.sin_addr), *((int *)&fd)));
            ClientThread *pClient = new ClientThread(fd);
            *m_clientsToAdd.GetBack() = pClient;
            m_clientsToAdd.PushBack();
            pClient->Run();
            NI_SERVER_LOG_L2(("Client thread started.\n"));
          }
          else
          {
            if(!m_bWantExit)
            {
              NI_SERVER_LOG(("Failed to accept: %d\n", errno));
            }
          }
          if(m_bWantExit)
          {
            break;
          }
        }
      }
      else
      {
        NI_SERVER_LOG(("Failed to listen port %d with error: %d\n", m_pars.m_nListenPort, errno));
      }
    }
    else
    {
      NI_SERVER_LOG(("Fail to bind to port %d", m_pars.m_nListenPort));
    }
  }
}

/*void ListenerThread::operate(S fd)
{
  char c;
  bool finished;
  std::string cmd, answer;

  finished = false;

  write(fd, answer.c_str(), answer.size());

  while(!finished)
  {
    cmd = answer = "";

    while(!finished) {
      finished = read(fd, &c, 1) != 1;

      if(c == '\n') break; else
        if(c != '\r') cmd += c;
    }

    if(!finished && !cmd.empty())
    {
      if(cmd == "info")
      {
        answer = "First Socket SERVER :)";
      }
      else if(cmd == "version")
      {
        answer = "version 1.0";
      }

      else if(cmd == "quit")
      {
        shutdown(fd, 2);
        close(fd);
        finished = true;
      }

      else
      {

      }

    }

    if(!finished && !answer.empty())
    {
      answer += "\n";
      write(fd, answer.c_str(), answer.size());
    }
  }

  exit(0);
} */

