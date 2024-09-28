
#ifndef __MTWORKERLITE_H__
#define __MTWORKERLITE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include this stuff for multi platform threads
//#include "mtintrin.h"
#include "mtworker.h"

class MTWorkerLite
{
public:
  typedef void (*UserFuncPtr)(void *);

	enum /*AffinityPolicy*/ {
		AFFINITY_AUTO,
		AFFINITY_ORDERED,
		AFFINITY_HT_ORDERED
	};

	MTWorkerLite();
	MTWorkerLite(UserFuncPtr pFunc, void ** pUserData, int numThreads = 0, int affinityPolicy = 0);
	~MTWorkerLite();
	
	void Init(UserFuncPtr pFunc, void ** pUserData, int numThreads = 0, int affinityPolicy = 0);

	void ExecuteJob(void ** pUserData = NULL);

	void SetJobFunction(UserFuncPtr pFunc);

  int GetThreadCount() const { return m_numThreads; }

  static int GetCPUCount();

protected:
  enum
  {
    SEM_OPEN   = 0,
    SEM_CLOSED = 1
  };

	struct ThreadData
  {
		pthread_t threadID; // Thread ID
    int       threadNumber; // 

    // Semaphores and counters
    int  volatile * pBegSem;
    int  volatile * pEndSem;
    long volatile * pTasks2BeDone;
    long volatile * pNotReady2Start;
    int  volatile * pQuit;

		UserFuncPtr pUserFunc;
		void*       pUserData;
	};

	volatile long m_tasks2BeDone;
	volatile long m_notReady2Start;
  volatile int  m_begSem;
  volatile int  m_endSem;
  volatile int  m_quit;

	int         m_numThreads;
	ThreadData *m_pData;

	static void* ThreadEntry(void *pArg);
	static void DummyJob(void *pArg);
};


#endif	// __MTWORKERLITE_H__

