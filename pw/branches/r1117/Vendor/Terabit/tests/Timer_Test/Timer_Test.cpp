/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// ============================================================================
/**
 *  @file P_Test.cpp
 *
 *  P_Test.cpp
 *
 *  This program illustrates how the ACE_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "Cfg.h"
#include "ProactorTask.h"
#include <list>
//#include "ace/Countdown_Time.h"
static TestCfg cfg;


// *************************************************************
//   TimerHanlder 
// *************************************************************

class TimerHandler : public TRB_Handler
{
public:
    TimerHandler  (ProactorTask & task, int index)
    : lock_     ()
    , cond_     (lock_)
    , task_     (task)
    , index_    (index)
    , timeout_  (0,0)
    , timer_id_ (-1)
    , flg_stop_ (false)
    {;}

    virtual ~TimerHandler (void) 
    {
        stop ();
        wait ();
        ACE_GUARD (ACE_SYNCH_MUTEX, mon, lock_);
        ACE_ASSERT (timer_id_ == -1);
    }


public:

    int   stop ();
    int   wait ();

    long  start_timer (long seconds);

    // virtual from ACE_Handler
    void handle_time_out (const ACE_Time_Value & tv,
                          const void * pArg );
   
   
private:
    long  start_timer_i (long seconds, void * pArg);

    ACE_SYNCH_MUTEX           lock_;
    ACE_SYNCH_CONDITION       cond_;

    ProactorTask &            task_;
    int                       index_;
    ACE_Time_Value            timeout_;
    long                      timer_id_;
    bool                      flg_stop_;
};

int
TimerHandler::stop()
{
   ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, mon, lock_, -1);
   this->flg_stop_ = true;

   if (this->timer_id_ != -1)
   {
       int rc = task_.get_proactor(0)->cancel_timer (this->timer_id_);

       ACE_DEBUG((LM_DEBUG,
           ACE_TEXT ("(%t) handler=%d cancel: timerId=%Ld rc=%d\n"),
            this->index_,
            this->timer_id_,
            rc));

       if (rc != 0)
       {
           this->timer_id_ = -1;
           cond_.signal ();
       }
   }

   return 0;
}

int
TimerHandler::wait()
{
   ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, mon, lock_, -1);

   while (this->timer_id_ != -1)
   {
       cond_.wait ();
   }
   return 0;
}

void
TimerHandler::handle_time_out (const ACE_Time_Value & tv,
                               const void * pArg )
{
    do_delay (cfg.delay());
    
    ACE_GUARD (ACE_SYNCH_MUTEX, mon, lock_);
    
    ACE_DEBUG((LM_DEBUG,
        ACE_TEXT ("(%t) handler=%d handle_time_out: timerId=%Ld arg=%@ tv=(%Ld,%Ld)\n"),
        this->index_,
        this->timer_id_,
        pArg,
        tv.sec(),
        tv.usec()));


    this->timer_id_ = -1;

    char * nextArg = (char *) pArg;

    ++nextArg;

    start_timer_i (this->timeout_.sec(), nextArg );
}

long
TimerHandler::start_timer (long seconds)
{
   ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, mon, lock_, -1);
   return start_timer_i (seconds, 0);
}

long  
TimerHandler::start_timer_i (long seconds, void * pArg) 
{
    if (timer_id_ != -1 )
    {
        return -1;
    }

    if (flg_stop_)
    {
        cond_.signal ();
        return -1;
    }
    
    this->timeout_.set (seconds, 0);
    
    this->timer_id_ = task_.get_proactor(0)->schedule_timer (*this,
                                                        pArg,
                                                        timeout_);
    ACE_DEBUG((LM_DEBUG,
        ACE_TEXT ("(%t) handler=%d start: timerId=%Ld arg=%@\n"),
               this->index_,
               this->timer_id_,
               pArg));

    return timer_id_;
}

int
run_main (int argc, ACE_TCHAR *argv[])
{
    int rc = 0;

    ProactorTask task1(cfg);

    std::list<TimerHandler *>  th_list;
    std::list<TimerHandler *>::iterator it1;
    std::list<TimerHandler *>::iterator it2;

    size_t num_timers  = cfg.connections ();

    for (size_t i= 0; i< num_timers; ++i)
    {
        th_list.push_back ( new TimerHandler(task1, i));
    }


    
    ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
    ACE_Time_Value time_end = ACE_OS::gettimeofday ();
    ACE_Time_Value time_run;

    if (task1.start () == 0)
    {
        it1 = th_list.begin();
        it2 = th_list.end ();

        for (; it1 !=it2; ++it1)
        {
            (*it1)->start_timer (cfg.timeout());
        }

        time_begin = ACE_OS::gettimeofday ();

        task1.enable_event_loop();
          
        ACE_Time_Value  sleep_time (cfg.seconds());
           
        while (sleep_time != ACE_Time_Value::zero)
        {
              ACE_Countdown_Time countdown ( & sleep_time );

              ACE_OS::sleep (sleep_time );
        }


        if (cfg.seconds () == 0)
        {
              // comment this later
              char c;
              cout << "Press any key to stop=>" << flush;
              cin.clear ();
              cin >> c;
        }


        //TestProactor * p = ACE_static_cast(TestProactor*,task1.get_proactor(0));
        //
        ////suspend timer thread 
        //p->timer_thread_manager().suspend_all (); 
        //// suspend event loop threads 
        //task1.suspend ();      

        //// sleep some time
        //ACE_OS::sleep (10 );

        //// resume suspended threads
        //task1.resume ();
        //p->timer_thread_manager().resume_all();
    }

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) Stop Timers\n")));
    it1 = th_list.begin();
    it2 = th_list.end ();
    for (; it1 !=it2; ++it1)
    {
        (*it1)->stop ();
    }

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) Wait Timers\n")));
    it1 = th_list.begin();
    it2 = th_list.end ();
    for (; it1 !=it2; ++it1)
    {
        (*it1)->wait ();
    }

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) Destroy Timers\n")));
    it1 = th_list.begin();
    it2 = th_list.end ();
    for (; it1 !=it2; ++it1)
    {
        delete (*it1);
        *it1 = 0;
    }
  
    time_end = ACE_OS::gettimeofday ();
    time_run = time_end - time_begin;


    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

    task1.stop ();
 
    return rc;
}

// *************************************************************
//   Configuration helpers
// *************************************************************

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("Timer_Test"));


  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

  int rc = run_main (argc, argv);

  ACE_END_TEST;

  return rc;
}

