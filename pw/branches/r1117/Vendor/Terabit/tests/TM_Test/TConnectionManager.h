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

#ifndef TCONNECTIONMANAGER_H
#define TCONNECTIONMANAGER_H

#include "TConnection.h"
#include "Cfg.h"

#include "ace/OS_NS_string.h"
#include "ace/OS_NS_stdio.h"

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class TConnectionManager : public ACE_Event_Handler
{
  friend class TConnection;
  typedef ACE_SYNCH_RECURSIVE_MUTEX TMutex;

public:
  int    get_number_connections (void) const { return this->num_connections_; }
  int    get_peak_connections (void) const { return this->peak_connections_; }

  // Sessions statistic
  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long   get_total_w   (void) const { return this->total_w_; }
  long   get_total_r   (void) const { return this->total_r_; }

  const ACE_TCHAR * get_name (void) const { return this->name_.c_str();}

  TMutex  & mutex (void)  {return this->mtx_;}

  TP_ReactorTask &  task (void) const { return task_;}
  TestCfg & config (void) const;

  

  int    should_stop (void) const { return this->flg_stop_;}
  int    stop ();
  int    wait ();

  int    is_safe_to_delete (void);


  
  TConnectionManager (TP_ReactorTask &  task, 
                      const ACE_TCHAR * name);

  virtual ~TConnectionManager  (void);

  void set_timeout (const ACE_Time_Value & timeout);

  const ACE_Time_Value& get_timeout (void) const
  {
    return this->timeout_;
  }

  // virtual from ACE_Event_Handler
  int handle_timeout (const ACE_Time_Value & /* tv */,
                      const void *   /* pArg */);

  void print_statistic(void);

  TConnection * create_connection  (TConnectionFactory & factory);
  
private:

  void          destroy_connection (TConnection * connection);
  // evictor pattern
  void check  (void);

  void cancel_timer (void);
  void start_timer (void);

  TMutex                mtx_;
  ACE_Thread_Semaphore  sem_;

  TP_ReactorTask &      task_;
  ACE_TString           name_;

  size_t           total_snd_;  // Total bytes successfully sent
  size_t           total_rcv_;  // Total bytes successfully received
  long             total_w_;    // Number of performed write operations
  long             total_r_;    // Number of performed read operations
        
  bool             flg_stop_; // Request to cancel

  u_int            num_connections_;
  u_int            peak_connections_;
  TConnection *    list_connections_[MAX_CONNECTIONS];
  ACE_Time_Value   timeout_;
  long             timer_id_;
};






#endif /* TCONNECTIONMANAGER_H */
