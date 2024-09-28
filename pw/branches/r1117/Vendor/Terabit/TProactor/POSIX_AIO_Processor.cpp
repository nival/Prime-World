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
// $Id: $

#include "TProactor/POSIX_AIO_Processor.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "TProactor/POSIX_AIO_Config.h"
#include "TProactor/POSIX_AIO_Dispatcher.h"
#include "TProactor/POSIX_AIO_Provider.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/*
 *******************************************************************
 * TRB_POSIX_AIO_Processor
 *******************************************************************
 */
TRB_POSIX_AIO_Processor::TRB_POSIX_AIO_Processor
  (TRB_POSIX_AIO_Dispatcher & completion_dispatcher,
   const TRB_POSIX_AIO_Config & config)
: config_                (config)
, completion_dispatcher_ (completion_dispatcher)
, provider_              (0)
, supported_operations_  (config.processor_op_mask())
{
    this->provider_ = config.create_provider();
}
 
TRB_POSIX_AIO_Processor::~TRB_POSIX_AIO_Processor (void)
{
    delete provider_;
    this->provider_ = 0;
}

bool
TRB_POSIX_AIO_Processor::is_emulation () const
{
    return (config_.provider_class() == 
        TRB_POSIX_AIO_Config::PVC_EMULATION);
}
    
int
TRB_POSIX_AIO_Processor::get_supported_operations_mask () const
{
    return (this->supported_operations_ &
            this->provider()->get_supported_operations_mask ());
}  

int
TRB_POSIX_AIO_Processor::init (void)
{
    if (this->provider() == 0)
    {
        return -1;
    }

    if (this->provider()->init () != 0)
    { 
        return -1;
    }
    return 0;
}

int
TRB_POSIX_AIO_Processor::fini (void)
{
    if (this->provider() != 0)
    {
        this->provider()->fini ();
    }
    return 0;
}

int
TRB_POSIX_AIO_Processor::register_handle (ACE_HANDLE handle, 
                     const void *completion_key,
                     int operations)
{
    return this->provider()->register_handle (handle,
                                              completion_key,
                                              operations);
}


int
TRB_POSIX_AIO_Processor::unregister_handle (ACE_HANDLE handle)
{
    return this->provider()->unregister_handle (handle);
}

int
TRB_POSIX_AIO_Processor::start_aio (TRB_POSIX_Asynch_Result * result)
{
    TRB_POSIX_Asynch_Result_Queue  completed_queue;

    int rc = this->provider()->start_aio (result, completed_queue);

    this->completion_dispatcher().add_completions (completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_Processor::cancel_aio (ACE_HANDLE handle)
{
    TRB_POSIX_Asynch_Result_Queue  completed_queue;

    int rc = this->provider()->cancel_aio (handle, completed_queue);

    this->completion_dispatcher().add_completions (completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_Processor::cancel_aio (TRB_Handler * handler)
{
    TRB_POSIX_Asynch_Result_Queue  completed_queue;

    int rc = this->provider()->cancel_aio (handler, completed_queue);

    this->completion_dispatcher().add_completions (completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_Processor::cancel_all ()
{
    TRB_POSIX_Asynch_Result_Queue  completed_queue;

    int rc = this->provider()->cancel_all (completed_queue);

    this->completion_dispatcher().add_completions (completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_Processor::get_completed_aio (ACE_Time_Value * wait_time,
               TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    // do not lock it now
    // it is up to the provider to lock as required
    Guard_Monitor leader_guard (leader_monitor(), false);
    return this->provider()->get_completed_aio (wait_time,
                                               leader_guard, 
                                               completed_queue);
}

bool
TRB_POSIX_AIO_Processor::is_dedicated () const
{
    return false;
}
 
int
TRB_POSIX_AIO_Processor::start (void)
{
    return 0;
}

int
TRB_POSIX_AIO_Processor::stop (void)
{
    return 0;
}

int
TRB_POSIX_AIO_Processor::interrupt (void)
{
    return this->provider()->interrupt ();
}


/*
 *******************************************************************
 * TRB_POSIX_AIO_Dedicated_Processor
 *******************************************************************
 */
TRB_POSIX_AIO_Dedicated_Processor::TRB_POSIX_AIO_Dedicated_Processor
(TRB_POSIX_AIO_Dispatcher & completion_dispatcher,
   const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Processor  (completion_dispatcher, config)
, ACE_Task_Base (&completion_dispatcher.thread_manager())
, task_monitor_ ()
, flg_stop_     (false)
{
}

TRB_POSIX_AIO_Dedicated_Processor::~TRB_POSIX_AIO_Dedicated_Processor ()
{
}

bool
TRB_POSIX_AIO_Dedicated_Processor::is_dedicated () const
{
    return true;
}

int 
TRB_POSIX_AIO_Dedicated_Processor::start ()
{
    if (this->activate (THR_NEW_LWP | THR_JOINABLE, 1) != 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("%N:%l:%p\n"),
            ACE_LIB_TEXT ("TRB_POSIX_AIO_Dedicated_Processor::start failed")),
            -1);
    }
    return 0;
}

int 
TRB_POSIX_AIO_Dedicated_Processor::stop ()
{
    {
        Guard_Monitor  guard (task_monitor_, true);
        this->flg_stop_ = true;
    }
    this->provider ()->interrupt ();

    if (ACE_Task_Base::wait () != 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("%N:%l:%p\n"),
            ACE_LIB_TEXT ("TRB_POSIX_AIO_Dedicated_Processor::stop failed")),
            -1);
    }
    return 0;
}

int 
TRB_POSIX_AIO_Dedicated_Processor::interrupt ()
{
    // Can not bee called
    ACE_ASSERT(0);

    this->completion_dispatcher().wakeup();
    return 0;
}

int
TRB_POSIX_AIO_Dedicated_Processor::get_completed_aio 
    (ACE_Time_Value * wait_time,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG(wait_time);

    this->provider()->finish_aio_completions (completed_queue);
    return 0;
}

int
TRB_POSIX_AIO_Dedicated_Processor::svc ()
{
    ACE_DEBUG ((LM_DEBUG, 
        ACE_TEXT("(%t) TRB_POSIX_AIO_Dedicated_Processor::svc enter\n")));

    // We are leader forever
    Guard_Monitor leader_guard (this->leader_monitor (), true);

    TRB_POSIX_Asynch_Result_Queue completed_queue;

    bool flgExit = false;

    while (!flgExit)
    {
        bool rc = this->provider ()->begin_aio_wait (0,
                                                     leader_guard, 
                                                     completed_queue);

        if (!completed_queue.empty ())
        {
            // we have completed AIOs
            // really asynchronous provider 
            this->completion_dispatcher ().add_main_completions (completed_queue);
        }
        else if (rc)
        {
            // we ready descriptors in provider exec_list_
            // emulation provider
            this->completion_dispatcher ().wakeup ();
        }

        {
            Guard_Monitor task_guard (this->task_monitor_);
            flgExit |= this->flg_stop_;
        }
    }

    ACE_DEBUG ((LM_DEBUG, 
        ACE_TEXT("(%t) TRB_POSIX_AIO_Dedicated_Processor::svc leave\n")));
    return 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
