#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include "mtworkerlite.h"

namespace
{

template <typename T>
void SpinUntilZero(T volatile &val)
{
  while (val != 0)
  {}
}

template <typename T>
int SpinUntilZeroAndCount(T volatile &val)
{
  int count = 0;
  while (val != 0)
    count++;
  return count;
}

template <typename T>
void SpinUntilZeroWithSleep(T volatile &val)
{
  while (val != 0)
  {
    //Sleep(0);
  }
}

template <typename T>
int SpinUntilZeroWithSleepAndCount(T volatile &val)
{
  int count = 0;
  while (val != 0)
  {
    //Sleep(0);
    count++;
  }
  return count;
}

}

MTWorkerLite::MTWorkerLite() : m_pData(NULL)
{
}

MTWorkerLite::MTWorkerLite(UserFuncPtr pFunc, void ** pUserData, int numThreads, int affinityPolicy)
{
	Init(pFunc, pUserData, numThreads, affinityPolicy);
}

void MTWorkerLite::Init(UserFuncPtr pFunc, void ** pUserData, int numThreads, int affinityPolicy)
{
  int numCPUs = GetCPUCount();
  if (numThreads == 0)
    m_numThreads = numCPUs;
  else
    m_numThreads = numThreads;

	m_tasks2BeDone   = 0;
  m_notReady2Start = m_numThreads - 1; // Count threads (except main one), which are not ready to start next job
  m_begSem = SEM_CLOSED;
  m_endSem = SEM_OPEN;
  m_quit   = SEM_CLOSED;

	m_pData = new ThreadData[m_numThreads];
	
	for (int i = 0; i < m_numThreads; i++)
	{
		m_pData[i].pUserFunc = pFunc;
		m_pData[i].pUserData = pUserData ? pUserData[i] : NULL;

    m_pData[i].threadNumber = i;
    m_pData[i].pBegSem = &m_begSem;
    m_pData[i].pEndSem = &m_endSem;
    m_pData[i].pTasks2BeDone = &m_tasks2BeDone;
    m_pData[i].pNotReady2Start = &m_notReady2Start;
    m_pData[i].pQuit   = &m_quit;

    if (i > 0)
		{
			int res = pthread_create(&m_pData[i].threadID, NULL, ThreadEntry, &m_pData[i]);
			NI_ASSERT( res == 0, "Cannot create thread" );
		  //assert(res == 0);
		}
		else	// main process thread
		{
#ifdef _WIN32 
			m_pData[i].threadID = GetCurrentThread();
#endif	// _WIN32
		}

#ifdef _WIN32
		int affinityMask = 0;
		switch(affinityPolicy)
		{
		case AFFINITY_AUTO:
			/* do nothing */
			break;
		case AFFINITY_ORDERED:
			affinityMask = 1 << (i % numCPUs);
			break;
		case AFFINITY_HT_ORDERED:
			{
        int procNdx = i % numCPUs;
				int p = (procNdx & 1) * (numCPUs >> 1);
				p += (procNdx >> 1);
				affinityMask = 1 << p;
			}
			break;
		}

		if (affinityMask)
		{
			DWORD_PTR ret = SetThreadAffinityMask(m_pData[i].threadID, DWORD_PTR(affinityMask));
			NI_ASSERT( ret == 0, "Cannot create thread" );
      //assert(ret != 0);
		}
#endif	// _WIN32
	}	// for(int n=0;n < threads;n++)
}

MTWorkerLite::~MTWorkerLite()
{
  m_quit = 0;
  if (m_pData != NULL) // Was ever inited?
  {
    SetJobFunction(&DummyJob);
	  ExecuteJob();

	  delete [] m_pData;
  }
}

void MTWorkerLite::SetJobFunction(UserFuncPtr pFunc)
{
	for(int i=0; i < m_numThreads; i++)
		m_pData[i].pUserFunc = pFunc;
}

void MTWorkerLite::ExecuteJob(void ** pUserData)
{
	if (pUserData)
	{
		for(int i = 0; i < m_numThreads; i++)
			m_pData[i].pUserData = pUserData[i];
	}

  if (m_numThreads > 1)
  {
    m_tasks2BeDone = m_numThreads - 1;
    // Wiat all threads to be ready to start
    SpinUntilZero(m_notReady2Start);
    // Start all threads
    m_endSem = SEM_CLOSED; // Close the end, so nobody will be able to loop twice
    _asm mfence; //WriteBarrier(); 
    m_begSem = SEM_OPEN;   // Start all threads!

    // Call user function
    m_pData[0].pUserFunc(m_pData[0].pUserData);
    
    // Spin until we got all the job done
    SpinUntilZero(m_tasks2BeDone);
    // Open end semaphor to finish the cycle
    m_begSem = SEM_CLOSED;
    _asm mfence; //WriteBarrier(); 
    m_endSem = SEM_OPEN;
  }
  else
  {
    // Just do my job =)
    m_pData[0].pUserFunc(m_pData[0].pUserData);
  }
}

void MTWorkerLite::DummyJob(void*)
{
  // Well, its dummy job. Just do nothing!
}

void* MTWorkerLite::ThreadEntry(void *pArg)
{
	ThreadData * const pThread = (ThreadData*)pArg;

	// shift stack beginnings for each thread to avoid L2 thrashing
	//void*	threadStackGap = _alloca(pThread->threadNumber*(2*4096+256));

  do 
	{
    // Ready to start
    InterlockedDecrement(pThread->pNotReady2Start);
    // Spin until we've got a job
    SpinUntilZeroWithSleep(*pThread->pBegSem);
    // Not ready to start
    InterlockedIncrement(pThread->pNotReady2Start);

    // Call user function
    pThread->pUserFunc(pThread->pUserData);

    // Job done!
    InterlockedDecrement(pThread->pTasks2BeDone);

    // Quit if need to
    if (*pThread->pQuit == SEM_OPEN)
      return NULL;

    // Spin until we finish all the stuff in main thread
    SpinUntilZeroWithSleep(*pThread->pEndSem);
	} while (1);
	
	return NULL;
}

int MTWorkerLite::GetCPUCount()
{
#ifdef _SC_NPROCESSORS_CONF		// Linux
	return (int)sysconf(_SC_NPROCESSORS_CONF);
#else
	SYSTEM_INFO si;
	::GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
#endif
}

#if 0
int s_log[400];
volatile long s_index = 0;

struct JobData
{
  int   threadIndex;
  float data;
};

void myJob(void *pData)
{
	JobData *pJob = (JobData*)pData;
  long index = InterlockedIncrement(&s_index);
  s_log[index-1] = pJob->threadIndex;
  
  printf("Job %d\n", pJob->threadIndex);
  /*
  pJob->data -= float(int(pJob->data));
  int count = int((pJob->data + 0.2f) * 5000000.0f);
  float f = 0.0f;
  for (int i = 0; i < count; i++)
  {
    f += sinf(float(i));
  }
  pJob->data = f; */
}


int main(int, char **)
{
  int const NUM_THREADS = 4;
  JobData *pData[NUM_THREADS];
  JobData jobData[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++)
  {
    pData[i] = jobData + i;
    jobData[i].threadIndex = i;
    jobData[i].data        = (float)i / NUM_THREADS;
  }

  MTWorkerLite worker(myJob, (void**)pData, NUM_THREADS, MTWorkerLite::AFFINITY_ORDERED);

	for(int n=0;n < 10;n++)
	{
		worker.ExecuteJob();
	}
  
  exit(0);
  
  printf("Execution log:\n");
	for(int n=0;n < s_index;n++)
    printf("%ld\n", s_log[n]);


  return 0;
}


#endif
