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

/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    POSIX_AIO_Dispatcher.h
 *
 *  $Id: $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TPROACTOR_POSIX_AIO_DISPATCHER_H 
#define TPROACTOR_POSIX_AIO_DISPATCHER_H 

#include "TProactor/POSIX_Asynch_IO.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "ace/Thread_Manager.h"
#include <vector>

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

//Forward declaration
class TRB_POSIX_AIO_Processor;
class TRB_POSIX_AIO_Config;

/**
 * @class TRB_POSIX_AIO_Dispatcher
 *
 * @brief POSIX implementation .
 */
class TPROACTOR_Export TRB_POSIX_AIO_Dispatcher
{
    // friend class TRB_POSIX_AIO_Processor;

public:
    typedef ACE_SYNCH_MUTEX            Mutex;
    typedef ACE_SYNCH_CONDITION        Condition;
    typedef Monitor_T<Mutex,Condition> Monitor;
    typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
    typedef Guard_Monitor::Save_Guard  Save_Guard;


    /// Constructor.
    TRB_POSIX_AIO_Dispatcher (const TRB_POSIX_AIO_Config & config1,
                              const TRB_POSIX_AIO_Config & config2);


    /// Virtual destructor.
    virtual ~TRB_POSIX_AIO_Dispatcher (void);

    void add_completions (TRB_POSIX_Asynch_Result_Queue & completed_queue);

    void add_completion (TRB_POSIX_Asynch_Result *result);

    void add_main_completions (TRB_POSIX_Asynch_Result_Queue & completed_queue);

    void add_main_completion (TRB_POSIX_Asynch_Result *result);

    void wakeup ();
    
    
    int  handle_events (ACE_Time_Value * wait_time);

    int  add_processor (TRB_POSIX_AIO_Processor * processor);
    
    int  close ();
  
    ACE_Thread_Manager & thread_manager();

private:
    int   handle_events_d (ACE_Time_Value * wait_time);
    int   handle_events_s (ACE_Time_Value * wait_time);

    void  poll_dedicated_processors (TRB_POSIX_Asynch_Result_Queue& tmp_queue);

    int   process_completion_queue (TRB_POSIX_Asynch_Result_Queue& tmp_queue);

    int   clear_main_queue (Guard_Monitor & guard);

    int   process_main_queue (Guard_Monitor & guard);
    
    void  interrupt_shared_processor ();



    const TRB_POSIX_AIO_Config &    config1_ ;
    const TRB_POSIX_AIO_Config &    config2_ ;

    /// Thread manager for AIO_Dedicated_Processor's threads
    ACE_Thread_Manager              thr_manager_;

    Monitor                         completion_monitor_;
    TRB_POSIX_Asynch_Result_Queue   main_completion_queue_;

    // can be only one
    TRB_POSIX_AIO_Processor *       shared_processor_;

    typedef std::vector<TRB_POSIX_AIO_Processor *> ProcessorVector;
    ProcessorVector                 dedicated_processors_;

    int                             num_waiting_threads_;
};

inline ACE_Thread_Manager &
TRB_POSIX_AIO_Dispatcher::thread_manager ()
{
    return this->thr_manager_;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#endif //TPROACTOR_POSIX_AIO_DISPATCHER_H 


