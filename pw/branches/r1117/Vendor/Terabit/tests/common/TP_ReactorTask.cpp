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
 *  @file TP_ReactorTask.cpp
 *
 *  TP_ReactorTask.cpp
 *
 *  This program illustrates how the ACE_TP_Reactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "TP_ReactorTask.h"

#if defined (ACE_HAS_THREADS) 

// *****************************************************************
//
// *****************************************************************

TP_ReactorTask::TP_ReactorTask (TestCfg & cfg)
  : TaskPool (cfg),
    tp_reactor_ (0)
{
}

TP_ReactorTask::~TP_ReactorTask (void)
{
  this->stop_and_free();
}

int
TP_ReactorTask::run_event_loop(u_int thr_num)
{
  int rc = -1;

  if (this->tp_reactor_ == 0)
    return rc;

  while (tp_reactor_->reactor_event_loop_done () == 0)
    {
      rc = this->tp_reactor_->run_reactor_event_loop ();
    }
  
  return rc;
}

int
TP_ReactorTask::end_event_loop(void)
{
  int rc = -1;

  ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) Calling End TP_Reactor event loop\n")));

  if (this->tp_reactor_ != 0)
    rc = this->tp_reactor_->end_reactor_event_loop ();

  return rc;
}


int
TP_ReactorTask::create_demultiplexor(void)
{
  ACE_ASSERT (this->tp_reactor_ == 0);

  ACE_TP_Reactor * pImpl = 0;

  ACE_NEW_RETURN (pImpl,ACE_TP_Reactor, -1);

  ACE_NEW_RETURN (tp_reactor_,
                   ACE_Reactor (pImpl ,1),
                   -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Create TP_Reactor\n")));

  // ACE_Reactor::instance (this->my_reactor_);

  this->reactor (tp_reactor_);

  return 0;
}



int
TP_ReactorTask::delete_demultiplexor (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Delete TP_Reactor\n")));

  // ACE_Reactor::instance ((ACE_Reactor *) 0);
  delete this->tp_reactor_;
  this->tp_reactor_ = 0;
  this->reactor (0);

  return 0;
}


#endif // ACE_HAS_THREADS 
