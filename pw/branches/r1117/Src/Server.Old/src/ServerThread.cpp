/*
 * ServerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "TypeProxy.h"
#include "ServerThread.h"

ServerThread::~ServerThread()
{
}

void ServerThread::Stop()
{
  Kill(m_threadHandle);
}

