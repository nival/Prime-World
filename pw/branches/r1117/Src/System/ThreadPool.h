#pragma once

#include "TPJobIntf.h"

namespace threading
{
  class TPThread;

  class IJobScheduler
  {
  public:
    virtual ITPJob* getJob() = 0;
  };

  class IThreadMngr
  {
  public:
    virtual TPThread* allocThread() = 0;
    virtual void freeThread(TPThread* th) = 0;
  };

  class ThreadPool : public IJobScheduler, public IThreadMngr
  {
    typedef list<TPThread*> Threads;
    typedef list<ITPJob*> JobQueue;

    struct State
    {
      enum
      {
        INIT,
        OPENED,
        CLOSED
      };
    };

  public:
    ThreadPool();
    ~ThreadPool();

  public:
    int Open(unsigned int n);
    bool IsOpened() const;
    void Close();
    int WaitJobs();
    int pushJob(ITPJob* j);

  protected:
    ITPJob* getJob();

//#if defined( NV_WIN_PLATFORM )

  private:

    TPThread* allocThread();
    void freeThread(TPThread* th);

//#endif

  private:
    Threads threads_;
    Threads freethreads_;
    threading::Mutex threadsMux_;
    JobQueue jqueue_;
    threading::Mutex jqueueMux_;

#if defined( NV_WIN_PLATFORM )

    HANDLE hWaitJobsEvt_;

#elif defined( NV_LINUX_PLATFORM )

	threading::Semaphore m_wait_jobs;
	threading::Semaphore m_job_finished;
	volatile long m_active_jobs_counter;

#endif

    int state_;

  };

  inline bool ThreadPool::IsOpened() const
  {
    return (state_ == State::OPENED);
  }
}

