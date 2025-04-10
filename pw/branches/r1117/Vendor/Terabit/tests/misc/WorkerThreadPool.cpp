#include "WorkerThreadPool.h"

WorkerThreadPool::WorkerThreadPool (size_t low_mark, 
                                    size_t high_mark)
: ACE_Task_Base   ()
, task_mutex_     ()
, task_condition_ (task_mutex_)
, handler_        ()
, queue_          (low_mark, high_mark)
, state_          (ST_INIT)
, num_threads_    (0)
, active_threads_ (0)
{
}

WorkerThreadPool::~WorkerThreadPool()
{
    stopAndWait ();
    ACE_ASSERT ( state_ == ST_STOPPED);
}


bool
WorkerThreadPool::putq (Job *job)
{
    return queue_.put (obj);
}


 bool
WorkerThreadPool::start (int num_threads, const HANDLER & runHandler)
{
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);

        if (num_threads == 0)
        {
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) WorkerThreadPool::start - invalid parameter\n")));
            return false;
        }

        switch (state_)
        {
        case ST_INIT:
        case ST_STOPPED:
            break;
        default:
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) WorkerThreadPool::start - already started or requested to stop\n")));
            return false;
        }

        state_ = ST_ACTIVE;
        handler_ = runHandler;

    }
    
    queue_.activate (Queue::READABLE);
    
    // activate "numThreads" 
    if (this->activate (THR_NEW_LWP| THR_JOINABLE, num_threads) < 0)
    {
        ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%t) WorkerThreadPool::start - unable to activate\n")));

        this->stopAndWait ();
        return false;
    }
    
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);
        while (num_threads_ != num_threads)
        {
            task_condition_.wait();
        }
    }
    queue_.activate (Queue::WRITABLE);
    return true;
}


inline bool
WorkerThreadPool <OBJECT, HANDLER, CONTAINER>::stop ()
{
    queue_.deactivate (Queue::READABLE | Queue::WRITABLE);

    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);

        switch (state_)
        {
        case ST_INIT:     state_ = ST_STOPPED; return true;
        case ST_STOPPED:  return true;
        case ST_CANCEL:   break;
        case ST_ACTIVE:   break;
        default:          break;
        }
        
        state_ = ST_CANCEL;
    }

    return true;
}


inline bool
WorkerThreadPool <OBJECT, HANDLER, CONTAINER>::stopAndWait ()
{
    this->stop ();

    int rc = this->wait ();
    if (rc < 0)
    {
        ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%t) ThreadPool_t::stop - unable to deactivate\n")));
        return false;
    }

    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);
        num_threads_ = 0;
        state_ = ST_STOPPED;
    }
        
    return true;
}



inline bool
WorkerThreadPool <OBJECT, HANDLER, CONTAINER>::purgeQueue  (const HANDLER & purgeHandler)
{
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);
        if (state_ != ST_STOPPED)
            return false;
    }

    OBJECT  msg;

    while (queue_.pop(msg))
    {
        try
        {
            purgeHandler(msg);
        }
        catch (std::exception & e )
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) WorkerThreadPool::purgeQueue() caught exception: %s\n"),
                e.what()));
        }
        catch (...)
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) WorkerThreadPool::purgeQueue() caught unknown exception\n")));
        }
    }
    return true;
}


inline int
WorkerThreadPool <OBJECT, HANDLER, CONTAINER>::svc ()
{
    int  thrNum = 0;
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, -1);

        thrNum  = active_threads_ = ++num_threads_;
        task_condition_.signal ();
        ACE_ERROR ((LM_INFO, 
            ACE_TEXT ("(%t) WorkerThreadPool::svc() thread=%d started\n"),
            thrNum));
    }

    OBJECT msg;

    while (queue_.get(msg))
    {
        try
        {
            handler_(msg);
        }
        catch (std::exception & e )
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) WorkerThreadPool::svc() thread=%d caught exception: %s\n"),
                thrNum,
                e.what()));
        }
        catch (...)
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) WorkerThreadPool::svc() thread=%d caught unknown exception\n"),
                thrNum));
        }
    }

    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, -1);
        --active_threads_;
        ACE_ERROR ((LM_INFO, 
            ACE_TEXT ("(%t) WorkerThreadPool::svc() thread=%d finished\n"),
            thrNum));
    }

    return 0;
}

#endif // THREAD_POOL_T 

