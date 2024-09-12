#include "stdafx.h"
#include "System/Thread.h"
#include "System/ThreadPool.h"

#if defined( NV_WIN_PLATFORM )

namespace threading
{
  class TPThread : public Thread
  {
  public:
    TPThread(IThreadMngr* thm, IJobScheduler* jscheduler, HANDLE hEvent);
    ~TPThread();

  public:
    void Stop();
    void WakeUp();

  protected:
    unsigned Work();

  private:
    volatile bool stop_;
    HANDLE hEvent_;
    IJobScheduler* js_;
    IThreadMngr* thm_;
  };

  TPThread::TPThread(IThreadMngr* thm, IJobScheduler* jscheduler, HANDLE hEvent)
    :stop_(false),
    hEvent_(hEvent),
    js_(jscheduler),
    thm_(thm)
  {
  }

  TPThread::~TPThread()
  {
  }

  void TPThread::Stop()
  {
    stop_ = true;
    ::SetEvent(hEvent_);
  }

  void TPThread::WakeUp()
  {
    ::SetEvent(hEvent_);
  }

  unsigned TPThread::Work()
  {
    while(!stop_)
    {
      DWORD dw = ::WaitForSingleObject(hEvent_, INFINITE);
      if (WAIT_OBJECT_0 == dw)
      {
        if (!stop_)
        {
          while(ITPJob* j = js_->getJob())
          {
            j->Execute();
          }

          thm_->freeThread(this);
        }
      }
      else
        stop_ = true;
    }

    return 0;
  }

  //////////////////////////////////////////////////////////////////////////
  //  ThreadPool
  ThreadPool::ThreadPool()
    :hWaitJobsEvt_(INVALID_HANDLE_VALUE),
    state_(State::INIT)
  {
    hWaitJobsEvt_ = ::CreateEvent(NULL, FALSE, FALSE, NULL);
  }

  ThreadPool::~ThreadPool()
  {
    if (INVALID_HANDLE_VALUE != hWaitJobsEvt_)
    {
      ::CloseHandle(hWaitJobsEvt_);
      hWaitJobsEvt_ = INVALID_HANDLE_VALUE;
    }
  }

  int ThreadPool::Open(unsigned int n)
  {
    if (state_ != State::INIT)
      return -1;

    for (unsigned int i = 0; i < n; ++i)
    {
      HANDLE hEvt = ::CreateEvent(NULL, FALSE, FALSE, NULL);
      TPThread* th = new TPThread(this, this, hEvt);
      threads_.push_back(th);
      freethreads_.push_back(th);
    }

    for (Threads::iterator it = threads_.begin(); it != threads_.end(); ++it)
      (*it)->Resume();

    state_ = State::OPENED;
    return 0;
  }

  void ThreadPool::Close()
  {
    for (Threads::iterator it = threads_.begin(); it != threads_.end(); ++it)
      (*it)->Stop();

    for (Threads::iterator it = threads_.begin(); it != threads_.end(); ++it)
      (*it)->Wait();

    for (Threads::iterator it = threads_.begin(); it != threads_.end(); ++it)
      delete (*it);

    state_ = State::CLOSED;
  }

  int ThreadPool::WaitJobs()
  {
    MutexLock lock(threadsMux_);
    if (freethreads_.size() == threads_.size())
      return 0; //  нет работы

    ::WaitForSingleObject(hWaitJobsEvt_, INFINITE);
    return 0;
  }

  int ThreadPool::pushJob(ITPJob* j)
  {
    ::ResetEvent(hWaitJobsEvt_);

    MutexLock lock(jqueueMux_);
    jqueue_.push_back(j);
    TPThread* th = allocThread();
    if (th)
      th->WakeUp();

    return 0;
  }

  ITPJob* ThreadPool::getJob()
  {
    MutexLock lock(jqueueMux_);
    if (jqueue_.size())
    {
      ITPJob* j = jqueue_.front();
      jqueue_.pop_front();
      return j;
    }

    return 0;
  }

  TPThread* ThreadPool::allocThread()
  {
    MutexLock lock(threadsMux_);
    if (freethreads_.size())
    {
      TPThread* th = freethreads_.front();
      freethreads_.pop_front();
      return th;
    }
    return 0;
  }

  void ThreadPool::freeThread(TPThread* th)
  {
    MutexLock lock(jqueueMux_);
    if (jqueue_.size())
      th->WakeUp();
    else
    {
      MutexLock lock(threadsMux_);
      freethreads_.push_front(th);
      if (freethreads_.size() == threads_.size())
        ::SetEvent(hWaitJobsEvt_);
    }
  }
}

#elif defined( NV_LINUX_PLATFORM )

	#include "interlocked.h"

	namespace threading {

		class TPThread: public Thread
		{
		public:

			TPThread( IJobScheduler *jscheduler, Semaphore &wjs, Semaphore &jfs):
				m_stop( false ),
				m_js( jscheduler ),
				m_wait_jobs_semaphore( wjs ),
				m_job_finished_semaphore( jfs )
			{}

		public:

			void Stop()
			{
				m_stop = true;
				m_wait_jobs_semaphore.Signal();
			}

		protected:

			virtual unsigned Work();

		private:

			volatile bool m_stop;
			IJobScheduler * m_js;
			Semaphore & m_wait_jobs_semaphore;
			Semaphore & m_job_finished_semaphore;

		};

		unsigned TPThread::Work()
		{
			while( false == m_stop ) {

				m_wait_jobs_semaphore.Wait();
				if ( false == m_stop ) {

					ITPJob *j = m_js->getJob();
					if ( j ) {

						j->Execute();
						m_job_finished_semaphore.Signal();

					}

				}

			}

			return 0;
		}

		ThreadPool::ThreadPool(): state_( State::INIT ), m_active_jobs_counter( 0 )
		{}

		ThreadPool::~ThreadPool()
		{}

		int ThreadPool::Open( unsigned int n )
		{
			if ( state_ != State::INIT )
				return -1;

			while ( n-- ) {

				TPThread *th = new TPThread( this, m_wait_jobs, m_job_finished );
				threads_.push_back( th );

			}

			for ( Threads::iterator it = threads_.begin(); threads_.end() != it; ++it )
				(*it)->Resume();

			state_ = State::OPENED;

			return 0;
		}

		void ThreadPool::Close()
		{
			if ( State::OPENED == state_ ) {

				for ( Threads::iterator it = threads_.begin(); threads_.end() != it; ++it )
					(*it)->Stop();

				for ( Threads::iterator it = threads_.begin(); threads_.end() != it; ++it)
					(*it)->Wait();

				for ( Threads::iterator it = threads_.begin(); threads_.end() != it; ++it)
					delete (*it);

				state_ = State::CLOSED;

			}
		}

		int ThreadPool::WaitJobs()
		{
			while ( m_active_jobs_counter ) {

				m_job_finished.Wait();
				nival::interlocked_decrement( m_active_jobs_counter );

			}

			return 0;
		}

		int ThreadPool::pushJob( ITPJob *j )
		{
			MutexLock lock( jqueueMux_ );
			jqueue_.push_back( j );

			nival::interlocked_increment( m_active_jobs_counter );
			m_wait_jobs.Signal();

			return 0;
		}

		ITPJob* ThreadPool::getJob()
		{
			MutexLock lock( jqueueMux_ );

			if ( jqueue_.empty() )
				return NULL;

			ITPJob *j = jqueue_.front();
			jqueue_.pop_front();

			return j;
		}
    
    TPThread* ThreadPool::allocThread()
    {
      MutexLock lock(threadsMux_);
      if (freethreads_.size())
      {
        TPThread* th = freethreads_.front();
        freethreads_.pop_front();
        return th;
      }
      return 0;
    }

    void ThreadPool::freeThread(TPThread* th)
    {
      MutexLock lock(threadsMux_);
      freethreads_.push_front(th);
        /*
        if (freethreads_.size() == threads_.size())
          ::SetEvent(hWaitJobsEvt_);
        */
    }

	}

#endif

