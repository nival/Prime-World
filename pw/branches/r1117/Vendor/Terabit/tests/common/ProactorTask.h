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
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef PROACTOR_TASK_H
#define PROACTOR_TASK_H

#include "TaskPool.h"
#include "TProactor/Proactor.h"
#include <vector>



class ProactorTask : public TaskPool
{
public:
  ProactorTask (TestCfg & cfg);
  virtual ~ProactorTask();

 
  TRB_Proactor * get_proactor(u_int idx);

protected:
  virtual int create_demultiplexor(void);
  virtual int delete_demultiplexor(void);
  virtual int run_event_loop(u_int thr_num);
  virtual int end_event_loop(void);

private:
  TRB_Proactor * create_proactor (u_int idx); 

  typedef std::vector<TRB_Proactor *> ProactorVector;
  
  ProactorVector proactor_vect_;
};


#endif  /* PROACTOR_TASK_H*/

