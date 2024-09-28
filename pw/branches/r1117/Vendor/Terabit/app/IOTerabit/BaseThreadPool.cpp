/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file Task_Pool.cpp
**   
**  Task_Pool.cpp
**  
**  @author Alexander Libman <libman@terabit.com.au>
**  
**
**********************************************************************/

#include "IOTerabit/BaseThreadPool.h"


namespace Terabit {

//-----------------------------------------------------
// Function to remove signals from the signal mask.
//-----------------------------------------------------
int 
BaseThreadPool::disable_signal (int sigmin, int sigmax)
{
#ifndef ACE_WIN32

    sigset_t signal_set;
    if (sigemptyset (&signal_set) == - 1)
    {
        ACE_ERROR ((LM_ERROR,
        ACE_TEXT ("Error: (%P|%t):%p\n"),
        ACE_TEXT ("sigemptyset failed")));
    }

    for (int i = sigmin; i <= sigmax; i++)
    {
        sigaddset (&signal_set, i);

        //  Put the <signal_set>.
        if (ACE_OS::pthread_sigmask (SIG_BLOCK, &signal_set, 0) != 0)
        {
            ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("Error: (%P|%t):%p\n"),
            ACE_TEXT ("pthread_sigmask failed")));
        }
    }
#else
    ACE_UNUSED_ARG (sigmin);
    ACE_UNUSED_ARG (sigmax);
#endif /* ACE_WIN32 */

  return 0;
}
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------

BaseThreadPool::BaseThreadPool (const ACE_TCHAR *name)
: monitor_        ()
, name_           (name)
, state_          (ST_INIT)
, num_threads_    (0)
, active_threads_ (0)
{
}

BaseThreadPool::~BaseThreadPool() 
{ 
    ACE_ASSERT(this->state_ == ST_CLOSED || 
               this->state_ == ST_INIT);
}

int
BaseThreadPool::start (int num_threads)
{
    {
        Guard_Monitor guard (monitor_);
        switch (state_)
        {
        case ST_INIT:     
        case ST_CLOSED:  
            break;
        case ST_SUSPENDED:
        case ST_ACTIVE:   
        case ST_CANCEL:   
        default:
            return -1;
        }

        this->state_ = ST_SUSPENDED;

        this->num_threads_    = num_threads;
        this->active_threads_ = 0;

        if (this->activate (THR_NEW_LWP, this->num_threads_) == -1)
        {
            this->state_ = ST_CLOSED;

            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_TEXT ("(%t) %s ThreadPool::start :")
                ACE_TEXT ("unable to activate thread pool"),
                this->name_.c_str ()),
                -1);
        }

        while (this->active_threads_  != this->num_threads_)
        {
            guard.wait ();
        }
    }

    return this->resume ();
}

int
BaseThreadPool::resume ()
{
    Guard_Monitor guard (monitor_);
    switch (state_)
    {
    case ST_ACTIVE:
        return 0;
    case ST_SUSPENDED:
        break;
    default:
        return -1;
    }
    this->enable_event_loop ();
    this->state_ = ST_ACTIVE;
    guard.broadcast ();
    return 0;
}

int
BaseThreadPool::suspend ()
{
    Guard_Monitor guard (monitor_);
    switch (state_)
    {
    case ST_SUSPENDED:
        return 0;
    case ST_ACTIVE:
        break;
    default:
        return -1;
    }
    this->state_ = ST_SUSPENDED;
    this->disable_event_loop ();
    guard.broadcast ();
    return 0;
}

int
BaseThreadPool::stop ()
{
    {
        Guard_Monitor guard (monitor_);
        switch (state_)
        {
        case ST_INIT:     
        case ST_CLOSED:  
        case ST_CANCEL:   
            return 0;
        case ST_SUSPENDED:
            this->state_ = ST_CANCEL; 
            break;
        case ST_ACTIVE:   
            this->state_ = ST_CANCEL; 
            this->disable_event_loop ();
            break;
        default:
            ACE_ASSERT (0);
            return -1;
        }
     
        guard.broadcast ();
    }

    if (this->wait () == -1)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_TEXT ("(%t) %s ThreadPool::stop : ")
            ACE_TEXT ("unable to stop thread pool"),
            this->name_.c_str ()),
            -1);
    }

    {
        Guard_Monitor guard (monitor_);
        this->state_ = ST_CLOSED;
    }
    return 0;
}

int
BaseThreadPool::svc (void)
{
    Guard_Monitor guard (monitor_);
    int thr_num = ++this->active_threads_;

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) %s thread=%d started\n"), 
        this->name_.c_str (),
        thr_num));

    disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
    guard.broadcast ();

    bool flg_exit = false;

    while (!flg_exit)
    {
        switch (state_)
        {
        case ST_CANCEL:
            flg_exit = true;
            break;

        case ST_SUSPENDED:
            guard.wait();
            break;

        case ST_ACTIVE:
            {
                Save_Guard anti_guard(guard, Save_Guard::RELEASE);
                this->run_event_loop (thr_num);
            }
            break;

        default:
            ACE_ASSERT (0);  // should never be
        }
    }

    --this->active_threads_;

    ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%t) %s thread=%d finished\n"), 
        this->name_.c_str (),
        thr_num));

    return 0;
}

}  //namespace Terabit 


