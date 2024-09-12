
#ifndef __MTWORKER_H
#define __MTWORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RTOSDef.hxx"
#include "RTExpImp.hxx"

#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT	0x0400
#endif
#include <windows.h>

typedef HANDLE	pthread_t;
typedef HANDLE	pthread_cond_t;
typedef HANDLE	pthread_mutex_t;
typedef void	pthread_mutexattr_t;
typedef void	pthread_condattr_t;
typedef void	pthread_attr_t;


// POSIX thread implementation
inline int pthread_create(pthread_t *t, pthread_attr_t *, void *(*pfn)(void *), void *a) {
	return (*t = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pfn, a, 0, NULL)) == NULL;
}

// POSIX mutex lightweight implementation
inline int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *) {
	return (*m = ::CreateMutex(NULL, FALSE, NULL)) == NULL;
}

inline int pthread_mutex_destroy(pthread_mutex_t *m) {
	return ::CloseHandle(*m) != 0;
}

inline int pthread_mutex_lock(pthread_mutex_t *m) {
	//printf("   [%u] wait to lock mutex %p\n", GetCurrentThreadId(), *m); fflush(stdout);
	DWORD r = ::WaitForSingleObject(*m, INFINITE);	assert(r != WAIT_FAILED);
	//printf("   [%u] mutex %p locked\n", GetCurrentThreadId(), *m); fflush(stdout);
	return r == WAIT_FAILED;
}

inline int pthread_mutex_unlock(pthread_mutex_t *m) {
	int r = ::ReleaseMutex(*m);
	//printf("   [%u] mutex %p unlocked\n", GetCurrentThreadId(), *m); fflush(stdout);
	return r == 0;
}

// POSIX condition variable lightweight implementation
inline int pthread_cond_init(pthread_cond_t *c, pthread_condattr_t *attr) {
	return (*c = ::CreateEvent(NULL, attr != NULL, FALSE, NULL)) == NULL;
}

inline int pthread_cond_destroy(pthread_cond_t *c) {
	return ::CloseHandle(*c) != 0;
}

inline int pthread_cond_signal(pthread_cond_t *c) {
	//printf("cs [%u] event %p signaled\n", GetCurrentThreadId(), *c); fflush(stdout);
	int r = ::SetEvent(*c);	assert(r);
	return r == 0;
}

inline int pthread_cond_broadcast(pthread_cond_t *c) {
	//printf("cb [%u] event %p signaled\n", GetCurrentThreadId(), *c); fflush(stdout);
	int r = ::PulseEvent(*c);	assert(r);
#ifndef NDEBUG
	::Sleep(1);
#endif
	return r == 0;
}

//#if !(_WIN32_WINNT >= 0x0400)
extern "C" WINBASEAPI DWORD WINAPI SignalObjectAndWait(HANDLE, HANDLE, DWORD, BOOL);
//#endif

inline int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m) {
	//printf("cw [%u] mutex %p unlocked\n", GetCurrentThreadId(), *m); fflush(stdout);
	//printf("cw [%u] waiting for event %p\n", GetCurrentThreadId(), *c); fflush(stdout);
	DWORD r = SignalObjectAndWait(*m, *c, INFINITE, FALSE);	assert(r != 0xFFFFFFFF);
	//::ReleaseMutex(*m);
	//::WaitForSingleObject(*c, INFINITE);	// wait for signal (event)
	//printf("cw [%u] event %p signaled\n", GetCurrentThreadId(), *c); fflush(stdout);

	//printf("cw [%u] wait to lock mutex %p\n", GetCurrentThreadId(), *m); fflush(stdout);
	::WaitForSingleObject(*m, INFINITE);	// lock mutex
	//printf("cw [%u] mutex %p locked\n", GetCurrentThreadId(), *m); fflush(stdout);
	
	return r != 0xFFFFFFFF;
}

#else
// Linux
#include <pthread.h>
#include <unistd.h>
#endif

class MTWorker
{
protected:

	static void *threadEntry(void *);
	
	struct TPARAM {
		pthread_t thread_id;

		int 		*p1, *p2;	// predicate
		pthread_mutex_t	*m1, *m2;	// mutex
		pthread_cond_t	*c1, *c2;	// condition

		void *(*pUserFunc)(void *);
		void *pUserParam;

		int *pCancel;
	};

	int	m_isInitialized;
	int	m_tasksLeft,
		m_currentJob,
		m_cancelJobs;
	pthread_cond_t	m_cond1,  m_cond2;
	pthread_mutex_t	m_mutex1, m_mutex2;

	TPARAM *m_tparam;
	int m_threads;

public:
	enum /*AffinityPolicy*/ {
		AFFINITY_AUTO,
		AFFINITY_ORDERED,
		AFFINITY_HT_ORDERED
	};

	
public:

	RTSCLIBENTRY MTWorker();
	RTSCLIBENTRY MTWorker(void *(*)(void *), void *, int = 0, int = 0);
	RTSCLIBENTRY ~MTWorker();

	RTSCLIBENTRY static int GetCPUCount();
	
	RTSCLIBENTRY int Init(void *(*)(void *), void *, int = 0, int = 0);

	RTSCLIBENTRY int ExecuteJob(void * = NULL);

	RTSCLIBENTRY int SetJobFunction(void *(*)(void *));

	RTSCLIBENTRY int GetThreadCount() const;
};


#endif	// __MTWORKER_H

