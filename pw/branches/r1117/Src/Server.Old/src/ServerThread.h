/*
 * ServerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include "TypeProxy.h"
#include "../../Net/TSList.h"
#include <typeinfo>
#include "../../System/Basic.h"
#include "../../System/Ring.h"

class ServerThread: protected Thread<void>
{
public:
  void Run(void)
  {
    Create(&m_threadHandle, false, 16 * 2048);
  }
protected:
  ServerThread::Handle m_threadHandle;
  bool                 m_bConnected;

public:
  bool IsConnected() {return m_bConnected;}
  void Disconnect()  {m_bConnected = false;}
  void Stop();
  ServerThread(): m_bConnected(true) {}
  virtual ~ServerThread();
};


#endif /* SERVERTHREAD_H_*/
