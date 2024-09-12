/////////////////////////////////////////////////////////////////////
//  Written by Phillip Sitbon
//  Copyright 2003
//
//  Win32/Semaphore.h
//    - Resource counting mechanism
//
/////////////////////////////////////////////////////////////////////
#ifndef _Semaphore_Win32_
#define _Semaphore_Win32_

#include "Win32.h"

#define SEM_VALUE_MAX ((int) ((~0u) >> 1))

class Semaphore
{
  HANDLE S;
  void operator=(const Semaphore &){}
  Semaphore(const Semaphore &){}

  public:
  Semaphore( int init = 0 )
  { S = CreateSemaphore(0,init,SEM_VALUE_MAX,0); }

  virtual ~Semaphore()
  { CloseHandle(S); }

  void Wait() const
  { WaitForSingleObject((HANDLE)S,INFINITE); }

  int Wait_Try() const
  { return ((WaitForSingleObject((HANDLE)S,INFINITE)==WAIT_OBJECT_0)?0:EAGAIN); }

  int Post() const
  { return (ReleaseSemaphore((HANDLE)S,1,0)?0:ERANGE); }

  int Value() const
  { LONG V = -1; ReleaseSemaphore((HANDLE)S,0,&V); return V; }

  void Reset( int init = 0 )
  {
    CloseHandle(S);
    S = CreateSemaphore(0,init,SEM_VALUE_MAX,0);
  }
};

#endif // !_Semaphore_Win32_
