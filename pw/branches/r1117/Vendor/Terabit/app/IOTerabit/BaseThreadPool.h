/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  = AUTHOR
**   Alexander Libman <libman@terabit.com.au>
**
**
**********************************************************************/
#ifndef TERABIT_BASETHREADPOOL_H
#define TERABIT_BASETHREADPOOL_H

#include "IOTerabit/IOTERABIT_Export.h"

#include "ace/Task.h"
#include "ace/Synch.h"
#include "ace/SString.h"
#include "TProactor/Monitor_T.h"


namespace Terabit {

class LogGuard
{
public:
  LogGuard () { ACE_LOG_MSG->acquire (); }
  virtual ~LogGuard () { ACE_LOG_MSG->release (); }
};



// *************************************************************
//  BaseThreadPool is ACE_Task resposible for :
//  1. creation and deletion of
//     Proactor and Proactor thread pool
//  2. running Proactor event loop
// *************************************************************

/**
 * @class BaseThreadPool
 *
 */
class IOTERABIT_Export BaseThreadPool : public ACE_Task_Base
{
public:
    typedef ACE_SYNCH_MUTEX            Mutex;
    typedef ACE_SYNCH_CONDITION        Condition;
    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;

    enum State
    {
        ST_INIT      = 0x0000,   // BEFORE OPEN
        ST_SUSPENDED = 0x0001,   // OPERATIONAL - SUSPENDED
        ST_ACTIVE    = 0x0002,   // OPERATIONAL - ACTIVE
        ST_CANCEL    = 0x0004,   // IN CANCEL
        ST_CLOSED    = 0x0008    // CLOSED
    };


    BaseThreadPool (const ACE_TCHAR *name);
    virtual ~BaseThreadPool();


    const ACE_TCHAR *get_name () const;

    static int  disable_signal (int sigmin, int sigmax);


    int start (int num_threads);
    int stop  (void);


    // override ACE_Task_Base
    virtual int resume ();
    virtual int suspend ();
    virtual int svc (void);

protected:

    virtual int enable_event_loop (void) = 0;
    virtual int disable_event_loop(void)=0;
    virtual int run_event_loop(u_int thr_num)=0;

    Monitor & get_monitor () { return this->monitor_; }
    State     get_state () const  { return this->state_; }

private:
    Monitor     monitor_;
    ACE_TString name_;
    State       state_;
    int         num_threads_;
    int         active_threads_ ;
};

inline const ACE_TCHAR *
BaseThreadPool::get_name () const
{
    return this->name_.c_str ();
}

}  //namespace Terabit 

#endif  /* TERABIT_BASETHREADPOOL_H*/

