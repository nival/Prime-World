/////////////////////////////////////////////////////////////////////
//  Written by Phillip Sitbon
//  Copyright 2003
//
//  Posix/Thread.h
//    - Posix thread
//
/////////////////////////////////////////////////////////////////////

#ifndef _Thread_Posix_
#define _Thread_Posix_

#include "Semaphore.h"
#include "Mutex.h"

#include <pthread.h>

#define InvalidHandle 0

template
<
  typename Thread_T
>
class Thread
{
  private:
    struct Instance;

  public:
    typedef Thread_T              & Thread_R;
    typedef const Thread_T        & Thread_C_R;

    typedef pthread_t Handle;
    typedef void ( *Handler)( Thread_R );


  protected:
    Thread() {}

    virtual ~Thread() {}

    virtual void ThreadMain( Thread_R ) = 0;

    static void Exit()
      { pthread_exit(0); }

    static void TestCancel()
      { pthread_testcancel(); }

    static Handle Self()
      { return (Handle)pthread_self(); }

  public:

    static int Create(
      const Handler       & Function,
      Thread_C_R            Param,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,
      const bool          & CancelAsync     = false
    )
    {
      M_Create().Lock();
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      if ( CreateDetached )
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

      if ( StackSize )
        pthread_attr_setstacksize(&attr, StackSize);

      Instance I(Param, 0, Function, CancelEnable, CancelAsync);

      int R = pthread_create((pthread_t *)H, &attr, ThreadMainHandler, (void *)&I);
      pthread_attr_destroy(&attr);

      if ( !R ) S_Create().Wait();
      else if ( H ) *H = InvalidHandle;

      M_Create().Unlock();
      return errno;
    }

    int Create(
      Thread_C_R            Param,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,
      const bool          & CancelAsync     = false
    ) const
    {
      M_Create().Lock();
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      if ( CreateDetached )
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

      if ( StackSize )
        pthread_attr_setstacksize(&attr,StackSize);

      Instance I(Param,const_cast<Thread *>(this),0,CancelEnable,CancelAsync);

      int R = pthread_create((pthread_t *)H,&attr,ThreadMainHandler,(void *)&I);
      pthread_attr_destroy(&attr);

      if ( !R ) S_Create().Wait();
      else if ( H ) *H = InvalidHandle;

      M_Create().Unlock();
      return errno;
    }

    static int Join( Handle H )
      { return pthread_join(H,0); }

    static int Kill( Handle H )
      { return pthread_cancel(H); }

    static int Detach( Handle H )
      { return pthread_detach(H); }

  private:

    static const Mutex &M_Create()      { static Mutex M; return M; }
    static const Semaphore &S_Create()  { static Semaphore S; return S; }

    static void *ThreadMainHandler( Instance *Param )
    {
      Instance  I(*Param);
      Thread_T  Data(I.Data);
      S_Create().Post();

      if ( I.Flags & 1 /*CancelEnable*/ )
      {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);

        if ( I.Flags & 2 /*CancelAsync*/ )
          pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
        else
          pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
      }
      else
      {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
      }

      if ( I.Owner )
        I.Owner->ThreadMain(Data);
      else
        I.pFN(Data);

      return 0;
    }

    struct Instance
    {
      Instance( Thread_C_R P, Thread<Thread_T> *const &O, const Thread<Thread_T>::Handler &pH = 0, const bool &CE=false, const bool &CA=false )
        : pFN(pH), Data(P), Owner(O), Flags(0) { if ( CE ) Flags|=1; if ( CA ) Flags|=2; }

      Thread_C_R                        Data;
      Thread<Thread_T>                * Owner;
      Handler                           pFN;
      unsigned char                     Flags;
    };
};

/////////////////////////////////////////////////////////////////////
//  Explicit specialization, no thread parameters
//

template <> class Thread<void>
{
  private:
    struct Instance;

  public:
    typedef pthread_t Handle;
    typedef void ( *Handler)();

  protected:
    Thread<void>() {}
    virtual ~Thread<void>() {}

    virtual void ThreadMain() = 0;

    static void Exit()
      { pthread_exit(0); }

    static void TestCancel()
      { pthread_testcancel(); }

    static Handle Self()
      { return (Handle)pthread_self(); }

  public:

    static int Create(
      const Handler       & Function,
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,
      const bool          & CancelAsync     = false
    )
    {
      M_Create().Lock();
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      if ( CreateDetached )
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

      if ( StackSize )
        pthread_attr_setstacksize(&attr,StackSize);

      Instance I(0, Function, CancelEnable, CancelAsync);

      int R = pthread_create((pthread_t *)H, &attr, (void*(*)(void*))ThreadMainHandler, (void *)&I);
      pthread_attr_destroy(&attr);

      if ( !R ) S_Create().Wait();
      else if ( H ) *H = InvalidHandle;

      M_Create().Unlock();
      return errno;
    }

    int Create(
      Handle  * const     & H               = 0,
      const bool          & CreateDetached  = false,
      const unsigned int  & StackSize       = 0,
      const bool          & CancelEnable    = false,
      const bool          & CancelAsync     = false
    ) const
    {
      M_Create().Lock();
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      if ( CreateDetached )
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

      if ( StackSize )
        pthread_attr_setstacksize(&attr,StackSize);

      Instance I(const_cast<Thread *>(this),0,CancelEnable,CancelAsync);

      int R = pthread_create((pthread_t *)H,&attr, (void*(*)(void*))ThreadMainHandler,(void *)&I);
      pthread_attr_destroy(&attr);

      if ( !R ) S_Create().Wait();
      else if ( H ) *H = InvalidHandle;

      M_Create().Unlock();
      return errno;
    }

    static int Join( Handle H )
      { return pthread_join(H,0); }

    static int Kill( Handle H )
      { return pthread_cancel(H); }

    static int Detach( Handle H )
      { return pthread_detach(H); }

  private:

    static const Mutex &M_Create()      { static Mutex M; return M; }
    static const Semaphore &S_Create()  { static Semaphore S; return S; }

    static void *ThreadMainHandler( Instance *Param )
    {
      Instance  I(*Param);
      S_Create().Post();

      if ( I.Flags & 1 /*CancelEnable*/ )
      {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);

        if ( I.Flags & 2 /*CancelAsync*/ )
          pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
        else
          pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
      }
      else
      {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
      }

      if ( I.Owner )
        I.Owner->ThreadMain();
      else
        I.pFN();

      return 0;
    }

    struct Instance
    {
      Instance( Thread<void> *const &O, const Thread<void>::Handler &pH = 0, const bool &CE=false, const bool &CA=false )
        : pFN(pH), Owner(O), Flags(0) { if ( CE ) Flags|=1; if ( CA ) Flags|=2; }

      Thread<void>::Handler             pFN;
      Thread<void>                *     Owner;
      unsigned char                     Flags;
    };
};

#endif // !_Thread_Posix_
