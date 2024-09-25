#ifndef WORKERTHREADPOOL_H
#define WORKERTHREADPOOL_H

#if defined (_MSC_VER)
#pragma once
#endif

#include <exception>

#include "ace/Task_T.h"
#include "Producer_Consumer_Queue_T.h"
#include "Single_List_T.h"




class Job : public LinkS_T <Job>
{
public:
    virtual  int execute () = 0;
    virtual  int cancel () = 0;
};


/**
 *  @class  WorkerThreadPool
 *  @author Alexander Libman 
 *
 */
class WorkerThreadPool : public ACE_Task_Base
{
public:
    typedef ACE_SYNCH_MUTEX Mutex;
    typedef ACE_SYNCH_CONDITION Condition;

    typedef Single_Queue_T <Job>   JobQueue;
    typedef Producer_Consumer_Queue_T <Job *, JobQueue >  ActiveJobQueue;

    
    WorkerThreadPool (size_t low_mark  = Queue::DEFAULT_LOW_MARK, 
                      size_t high_mark = Queue::DEFAULT_HIGH_MARK);

    virtual ~WorkerThreadPool();

    const JobQueue & get_job_queue () const { return queue_; }
    JobQueue & get_job_queue () { return queue_; }

    bool  putq (Job *job);
    
    virtual int svc (void);

    bool start (int num_threads);
    bool stop  ();
    bool stopAndWait  ();
    bool purgeQueue   ();


private:

    enum State
    {
        ST_INIT    = 0x0001,
        ST_ACTIVE  = 0x0002,
        ST_CANCEL  = 0x0004,
        ST_STOPPED = 0x0008
    };

    Mutex     task_mutex_;
    Condition task_condition_;

    ActiveJobQueue   active_queue_;
    JobQueue         free_queue_;

    volatile int  state_;
    int     num_threads_;
    int     active_threads_;
};


#endif // WORKERTHREADPOOL_T 

