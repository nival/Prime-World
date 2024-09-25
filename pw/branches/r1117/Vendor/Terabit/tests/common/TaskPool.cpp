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
 *  @file Task_Pool.cpp
 *
 *  Task_Pool.cpp
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"
#include "TaskPool.h"

#if defined (ACE_HAS_THREADS) 

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------

TaskPool::TaskPool (TestCfg & cfg)
: cfg_        (cfg)
, lock_       ()
, sem_main_   (0)
, sem_work_   (0)
, flg_stop_   (0)
, thr_seq_num_(0)
{
}

TaskPool::~TaskPool() 
{ 
  ACE_ASSERT(this->thr_count() == 0);
}

int
TaskPool::start (void)
{
  u_int num_threads  = this->cfg_.threads ();

  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                      monitor,
                      this->lock_,
                      -1);

    if (this->create_demultiplexor() == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("(%t) %p.\n"),
                         ACE_TEXT ("unable to create demultiplexor")),
                        -1);

    if (this->activate (THR_NEW_LWP, num_threads) == -1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("(%t) %p.\n"),
                         ACE_TEXT ("unable to activate thread pool")),
                        -1);
  }

  for (; num_threads > 0; num_threads--)
    this->wait_signal();
    
  return 0;
}


int
TaskPool::stop ()
{
  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                      monitor,
                      this->lock_,
                      -1);

    this->flg_stop_ = 1;

    if (thr_count () == 0)
      return 0;


    this->enable_event_loop();

    this->end_event_loop ();
  }

  if (this->wait () == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("(%t) %p.\n"),
                ACE_TEXT ("unable to stop thread pool")));

  return 0;
}

int
TaskPool::stop_and_free ()
{
  int rc = this->stop();

  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                      monitor,
                      this->lock_,
                      -1);

    this->delete_demultiplexor ();
  }
  return rc;
}


int
TaskPool::enable_event_loop (void)
{
  int num_threads = this->thr_count ();

  for (; num_threads > 0; num_threads--)
    {
      this->sem_work_.release (1);
    }

  return 0;
}

int
TaskPool::signal_main (void)
{
  this->sem_main_.release (1);
  return 0;
}
  
int
TaskPool::wait_signal (void)
{
  this->sem_main_.acquire ();
  return 0;
}

int
TaskPool::svc (void)
{
  u_int thr_num = 0;
  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                      monitor,
                      this->lock_,
                      -1);

    thr_num = this->thr_seq_num_;
    ++this->thr_seq_num_;

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) %d TaskPool started\n"), thr_num));

    disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);

    // signal that we started and are ready
    this->signal_main();
  }

  // wait enable command to run event loop
  this->sem_work_.acquire ();

  this->run_event_loop (thr_num);

  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX,
                      monitor,
                      this->lock_,
                      -1);
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) %d TaskPool finished\n"), thr_num));
  }
  return 0;
}


#endif // ACE_HAS_THREADS 
