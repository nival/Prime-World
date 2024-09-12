/////////////////////////////////////////////////////////////////////
//  Written by Phillip Sitbon
//  Copyright 2003
//
//  Win32/Thread.h
//    - Windows thread
//
//  - From CreateThread Platform SDK Documentation:
//
//  "A thread that uses functions from the static C run-time 
//    libraries should use the beginthread and endthread C run-time
//    functions for thread management rather than CreateThread and
//    ExitThread. Failure to do so results in small memory leaks
//    when ExitThread is called. Note that this is not a problem
//    with the C run-time in a DLL."
//
//  With regards to this, I have decided to use the CreateThread
//  API, unless you define _CRT_ in which case there are two
//  possibilities:
//
//    1. Define _USE_BEGINTHREAD: Uses _beginthread/_endthread
//        (said to be *unreliable* in the SDK docs)
//
//    2. Don't - Uses _beginthreaded/_endthreadex
//
//  A note about _endthread:
//
//    It will call CloseHandle() on exit, and if it was already
//    closed then you will get an exception. To prevent this, I
//    removed the CloseHandle() functionality - this means that
//    a Join() WILL wait on a Detach()'ed thread.
//
/////////////////////////////////////////////////////////////////////
#ifndef _Thread_Win32_
#define _Thread_Win32_


#include "Win32.h"
#include "Semaphore.h"
#include "Mutex.h"

#define _CRT_

#ifdef _CRT_
# include <process.h>
# ifdef _USE_BEGINTHREAD
#   define THREAD_CALL                __cdecl
#   define THREAD_HANDLE              uintptr_t
#   define THREAD_RET_T               void
#   define CREATE_THREAD_FAILED       (-1L)
#   define CREATE_THREAD_ERROR        (errno)
#   define CREATE_THREAD(_S,_F,_P, _ID)    ((Handle)_beginthread((void (__cdecl *)(void *))_F,_S,(void *)_P))
#   define EXIT_THREAD                _endthread()
#   define CLOSE_HANDLE(x)            1
#   define THREAD_RETURN(x)           return
# else
#   define THREAD_CALL                WINAPI
#   define THREAD_HANDLE              HANDLE
#   define THREAD_RET_T               UINT
#   define CREATE_THREAD_FAILED       (0L)
#   define CREATE_THREAD_ERROR        (errno)
#   define CREATE_THREAD(_S,_F,_P, _ID)    ((Handle)_beginthreadex(0,_S,(UINT (WINAPI *)(void *))_F,(void *)_P,0,(unsigned int *)_ID))
#   define EXIT_THREAD                _endthreadex(0)
#   define CLOSE_HANDLE(x)            CloseHandle(x)
#   define THREAD_RETURN(x)           return(x)
# endif
#else
# define THREAD_CALL                WINAPI
# define THREAD_HANDLE              HANDLE
# define THREAD_RET_T               DWORD
# define CREATE_THREAD_FAILED       (0L)
# define CREATE_THREAD_ERROR        GetLastError()
# define CREATE_THREAD(_S,_F,_P, _ID)    ((Handle)CreateThread(0,_S,reinterpret_cast<DWORD (WINAPI *)(void *)>(_F),(void *)_P,0,(LPDWORD)_ID))
# define EXIT_THREAD                ExitThread(0)
# define CLOSE_HANDLE(x)            CloseHandle(x)
# define THREAD_RETURN(x)           return(x)
#endif

#define InvalidHandle 0

template <typename Thread_T> class Thread
{
  private:
    typedef struct Instance;

  public:
    typedef typename Thread_T              & Thread_R;
    typedef const typename Thread_T        & Thread_C_R;

    typedef THREAD_HANDLE Handle;
    typedef void (* Handler)( typename Thread_R );

  protected:
    Thread() {}

    virtual void ThreadMain( Thread_R ) = 0;

    static void Exit()
      { EXIT_THREAD; }

    static void TestCancel()
      { Sleep(0); }

    static Handle Self()
    {
      //Handle Hnd = InvalidHandle;
      //DuplicateHandle(GetCurrentProcess(),GetCurrentThread(),GetCurrentProcess(),(LPHANDLE)&Hnd,NULL,0,NULL);
      //return Hnd;

      // only a pseudo-handle!
      return (Handle)GetCurrentThread();
    }

  public:

    static int Create(
      const Handler       & Function,
      Thread_C_R            Param,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,   // UNUSED
      const bool          & CancelAsync     = false    // UNUSED
    )
    {
      M_Create().Lock();

      Instance I(Param,0,Function);
      unsigned int ID; 
      Handle Hnd(CREATE_THREAD(StackSize,ThreadMainHandler,&I, &ID));

      if ( Hnd == CREATE_THREAD_FAILED )
      {
        if ( H ) *H = InvalidHandle;
        M_Create().Unlock();
        return CREATE_THREAD_ERROR;
      }

      if ( H ) *H = Hnd;

      S_Create().Wait();
      M_Create().Unlock();

      if ( CreateDetached ) CLOSE_HANDLE(Hnd);
      return 0;
    }

    int Create(
      Thread_C_R            Param,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,   // UNUSED
      const bool          & CancelAsync     = false    // UNUSED
    ) const
    {
      M_Create().Lock();

      Instance I(Param,const_cast<Thread *>(this));
			unsigned int ID;

      Handle Hnd(CREATE_THREAD(StackSize,ThreadMainHandler,&I, &ID));

      if ( Hnd == CREATE_THREAD_FAILED )
      {
        if ( H ) *H = InvalidHandle;
        M_Create().Unlock();
        return CREATE_THREAD_ERROR;
      }

      if ( H ) *H = Hnd;

      S_Create().Wait();
      M_Create().Unlock();

      if ( CreateDetached ) CLOSE_HANDLE(Hnd);
      return 0;
    }

    static int Join( const Handle &H )
    {
      DWORD R = WaitForSingleObject((HANDLE)H,INFINITE);

      if ( (R == WAIT_OBJECT_0) || (R == WAIT_ABANDONED) )
      {
        CLOSE_HANDLE(H);
        return 0;
      }

      if ( R == WAIT_TIMEOUT ) return EAGAIN;
      return EINVAL;
    }

    static int Kill( const Handle &H )
      { return TerminateThread((HANDLE)H,0) ? 0 : EINVAL; }

    static int Detach( const Handle &H )
      { return (CLOSE_HANDLE(H)?0:EINVAL); }

  private:

    static const Mutex &M_Create()      { static Mutex M; return M; }
    static const Semaphore &S_Create()  { static Semaphore S; return S; }

    static THREAD_RET_T THREAD_CALL ThreadMainHandler( Instance *Param )
    {
      Instance  I(*Param);
      Thread_T  Data(I.Data);
      S_Create().Post();

      if ( I.Owner )
        I.Owner->ThreadMain(Data);
      else
        I.pFN(Data);

      Exit();
      THREAD_RETURN(0);
    }

    struct Instance
    {
      Instance( Thread_C_R P, Thread<Thread_T> *const &O, const typename Thread<Thread_T>::Handler &pH = 0 )
        : pFN(pH), Data(P), Owner(O) {}

      typename Thread<Thread_T>::Thread_C_R          Data;
      typename Thread<Thread_T>                    * Owner;
      typename Thread<Thread_T>::Handler             pFN;
    };
};

/////////////////////////////////////////////////////////////////////
//  Explicit Specialization of void
//
template <> class Thread<void>
{
  private:
    typedef struct Instance;

  public:
    typedef THREAD_HANDLE Handle;
    typedef void ( *Handler)();

  protected:
    Thread<void>() {}

    virtual void ThreadMain() = 0;

    static void Exit()
      { EXIT_THREAD; }

    static void TestCancel()
      { Sleep(0); }

    static Handle Self()
      { return (Handle)GetCurrentThread(); }

  public:

    static int Create(
      const Handler       & Function,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,   // UNUSED
      const bool          & CancelAsync     = false    // UNUSED
    )
    {
      NI_USE_PARAM(CancelAsync);
      NI_USE_PARAM(CancelEnable);
			unsigned int ID;
      Handle Hnd(CREATE_THREAD(StackSize,ThreadMainHandler_S,Function, &ID));

      if ( Hnd == CREATE_THREAD_FAILED )
      {
        if ( H ) *H = InvalidHandle;
        return CREATE_THREAD_ERROR;
      }

      if ( H ) *H = Hnd;
      if ( CreateDetached ) CLOSE_HANDLE(Hnd);
      return 0;
    }

    int Create(
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,   // UNUSED
      const bool          & CancelAsync     = false,   // UNUSED
      unsigned int *const & ThreadID        = NULL
    ) const
    {
      NI_USE_PARAM(CancelAsync);
      NI_USE_PARAM(CancelEnable);
			unsigned int ID;
      Handle Hnd(CREATE_THREAD(StackSize,ThreadMainHandler,this, &ID));

      if ( Hnd == CREATE_THREAD_FAILED )
      {
        if ( H ) *H = InvalidHandle;
        return CREATE_THREAD_ERROR;
      }

      if ( H ) *H = Hnd;
			if ( ThreadID ) *ThreadID = ID; 
      if ( CreateDetached ) CLOSE_HANDLE(Hnd);
      return 0;
    }

    static int Join( const Handle &H )
    {
      DWORD R = WaitForSingleObject((HANDLE)H,INFINITE);

      if ( (R == WAIT_OBJECT_0) || (R == WAIT_ABANDONED) )
      {
        CLOSE_HANDLE(H);
        return 0;
      }

      if ( R == WAIT_TIMEOUT ) return EAGAIN;
      return EINVAL;
    }

    static int Kill( const Handle &H )
      { return TerminateThread((HANDLE)H,0) ? 0 : EINVAL; }

    static int Detach( const Handle &H )
      { return (CLOSE_HANDLE(H)?0:EINVAL); }

  private:

    static THREAD_RET_T THREAD_CALL ThreadMainHandler( Thread<void> *Param )
    {
      Param->ThreadMain();
      Exit();
      THREAD_RETURN(0);
    }

    static THREAD_RET_T THREAD_CALL ThreadMainHandler_S( void *p )
    {
			Handler Param = (Handler)p;

      Param();
      Exit();
      THREAD_RETURN(0);
    }
};

#endif // !_Thread_Win32_
