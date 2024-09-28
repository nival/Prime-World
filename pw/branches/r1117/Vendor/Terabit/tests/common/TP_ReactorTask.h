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
//
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef ACE_TP_REACTOR_TASK_H
#define ACE_TP_REACTOR_TASK_H

#include "TaskPool.h"

#if defined (ACE_HAS_THREADS) 

#include "ace/Reactor.h"
#include "ace/TP_Reactor.h"



class TP_ReactorTask : public TaskPool
{
public:
  TP_ReactorTask (TestCfg & cfg);
  virtual ~TP_ReactorTask();

 
  ACE_Reactor * tp_reactor(void) { return this->tp_reactor_;}

protected:
  virtual int create_demultiplexor(void);
  virtual int delete_demultiplexor(void);
  virtual int run_event_loop(u_int thr_num);
  virtual int end_event_loop(void);


  ACE_Reactor * tp_reactor_;
};


#endif  // (ACE_HAS_THREADS) 

#endif  /*ACE_TP_REACTOR_H*/

