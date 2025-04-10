#ifndef THREAD_POOL_T_H
#define THREAD_POOL_T_H

#if defined (_MSC_VER)
#pragma once
#endif

#include <exception>

#include "ace/Task_T.h"
#include "Producer_Consumer_Queue_T.h"


template < class OBJECT >
class Activator_T 
{
public:
    bool operator () (OBJECT & obj) const
    {
        return obj.call ();
    }
};

/**
 *  @class  Thread_Pool_T
 *  @author Alexander Libman 
 *
 */
template < class OBJECT , 
           class HANDLER = Activator_T <OBJECT> ,
           class CONTAINER = std::list<OBJECT> >
class Thread_Pool_T : public ACE_Task_Base
{
public:

    typedef Producer_Consumer_Queue_T <OBJECT, CONTAINER> Queue;
    typedef ACE_SYNCH_MUTEX Mutex;
    typedef ACE_SYNCH_CONDITION Condition;

    Thread_Pool_T (size_t low_mark  = Queue::DEFAULT_LOW_MARK, 
                  size_t high_mark = Queue::DEFAULT_HIGH_MARK);

    virtual ~Thread_Pool_T();

    const Queue & getQueue () const { return queue_; }
    Queue & getQueue () { return queue_; }

    bool  putq (const OBJECT & obj);

    virtual int svc (void);

    bool start (int num_threads, const HANDLER & runHandler);
    bool stop  ();
    bool stopAndWait  ();
    bool purgeQueue   (const HANDLER & purgeHandler);


private:

    enum
    {
        RUNNING  = 1,
        STOPPING = 2,
        STOPPED  = 3
    };

    Mutex     task_mutex_;
    Condition task_condition_;

    HANDLER handler_;
    Queue   queue_;

    volatile int  state_;
    int     num_threads_;
    int     active_threads_;
};

template < class OBJECT, class HANDLER, class CONTAINER >
inline 
Thread_Pool_T <OBJECT,HANDLER, CONTAINER>::Thread_Pool_T (size_t low_mark, 
                                                        size_t high_mark)
: ACE_Task_Base   ()
, task_mutex_     ()
, task_condition_ (task_mutex_)
, handler_        ()
, queue_          (low_mark, high_mark)
, state_          (STOPPED)
, num_threads_    (0)
, active_threads_ (0)
{
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline 
Thread_Pool_T <OBJECT,HANDLER,CONTAINER>::~Thread_Pool_T()
{
    stopAndWait ();
    ACE_ASSERT ( state_ == STOPPED);
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline bool
Thread_Pool_T <OBJECT,HANDLER,CONTAINER>::putq (const OBJECT & obj)
{
    return queue_.put (obj);
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline bool
Thread_Pool_T <OBJECT,HANDLER,CONTAINER>::start (int num_threads, const HANDLER & runHandler)
{
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);

        if (num_threads == 0)
        {
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) Thread_Pool_T::start - invalid parameter\n")));
            return false;
        }

        if (state_ != STOPPED) 
        {
            ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) Thread_Pool_T::start - already started or requested to stop\n")));
            return false;
        }

        state_ = RUNNING;
        handler_ = runHandler;

    }
    
    queue_.activate (Queue::READABLE | Queue::WRITABLE);
    
    // activate "numThreads" 
    if (this->activate (THR_NEW_LWP| THR_JOINABLE, num_threads) < 0)
    {
        state_ = STOPPED;

        ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%t) Thread_Pool_T::start - unable to activate\n")));
        return false;
    }
    
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);
        while (num_threads_ != num_threads)
        {
            task_condition_.wait();
        }
    }

    return true;
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline bool
Thread_Pool_T <OBJECT, HANDLER, CONTAINER>::stop ()
{
    queue_.deactivate (Queue::READABLE | Queue::WRITABLE);

    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);

        switch (state_)
        {
        case STOPPED:  return true;
        case STOPPING: break;
        case RUNNING:  break;
        default:       break;
        }
        
        state_ = STOPPING;
    }

    return true;
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline bool
Thread_Pool_T <OBJECT, HANDLER, CONTAINER>::stopAndWait ()
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
        state_ = STOPPED;
    }
        
    return true;
}


template < class OBJECT, class HANDLER, class CONTAINER >
inline bool
Thread_Pool_T <OBJECT, HANDLER, CONTAINER>::purgeQueue  (const HANDLER & purgeHandler)
{
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, false);
        if (state_ != STOPPED)
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
                ACE_TEXT ("(%t) Thread_Pool_T::purgeQueue() caught exception: %s\n"),
                e.what()));
        }
        catch (...)
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) Thread_Pool_T::purgeQueue() caught unknown exception\n")));
        }
    }
    return true;
}

template < class OBJECT, class HANDLER, class CONTAINER >
inline int
Thread_Pool_T <OBJECT, HANDLER, CONTAINER>::svc ()
{
    int  thrNum = 0;
    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, -1);

        thrNum  = active_threads_ = ++num_threads_;
        task_condition_.signal ();
        ACE_ERROR ((LM_INFO, 
            ACE_TEXT ("(%t) Thread_Pool_T::svc() thread=%d started\n"),
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
                ACE_TEXT ("(%t) Thread_Pool_T::svc() thread=%d caught exception: %s\n"),
                thrNum,
                e.what()));
        }
        catch (...)
        {
            ACE_ERROR ((LM_ERROR, 
                ACE_TEXT ("(%t) Thread_Pool_T::svc() thread=%d caught unknown exception\n"),
                thrNum));
        }
    }

    {
        ACE_GUARD_RETURN (Mutex, guard, task_mutex_, -1);
        --active_threads_;
        ACE_ERROR ((LM_INFO, 
            ACE_TEXT ("(%t) Thread_Pool_T::svc() thread=%d finished\n"),
            thrNum));
    }

    return 0;
}

#endif // THREAD_POOL_T 

