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
 *  @file    POSIX_AIO_SUN_Provider.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_SUN_PROVIDER_H 
#define TRB_POSIX_AIO_SUN_PROVIDER_H 

#include "TProactor/POSIX_AIO_Provider.h"

#if defined(ACE_HAS_AIO_CALLS) && defined(sun)
#include /**/ <sys/types.h>
#include /**/ <sys/asynch.h>    // Sun native aio calls

#include "TProactor/POSIX_AIO_Config.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


/**
 *
 * @class TRB_POSIX_AIO_SUN_Provider
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_SUN_Provider :
    public TRB_POSIX_AIO_Provider
{
public:
    TRB_POSIX_AIO_SUN_Provider (const TRB_POSIX_AIO_Config & config);
    virtual ~TRB_POSIX_AIO_SUN_Provider();

    virtual int  init ();
    virtual int  fini ();
    virtual int  interrupt ();

    virtual int  get_supported_operations_mask () const;

    virtual int register_handle (ACE_HANDLE  handle,
                                 const void *completion_key,
                                 int         operations);

    virtual int  unregister_handle (ACE_HANDLE handle);


    virtual bool begin_aio_wait (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  finish_aio_completions (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  get_completed_aio (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  start_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (TRB_POSIX_Asynch_Result * result,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (ACE_HANDLE handle,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_aio (TRB_Handler * handler,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  cancel_all (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

protected:
    int   start_aio_impl (TRB_POSIX_Asynch_Result * result);

    bool  check_interrupter_result (aio_result_t * result);

    TRB_POSIX_Asynch_Result * find_completed_result 
                                   (aio_result_t * result);


    // return  > 0  number of started deferred operations
    //           0  no started operations
    //         < 0  some completions due start errors 
    int   start_deferred_queue (
                TRB_POSIX_Asynch_Result_Queue & completed_queue);

    int   cancel_result (TRB_POSIX_Asynch_Result * result,
                         TRB_POSIX_Asynch_Result_Queue & completed_queue);

    bool  cancel_deferred_queue (TRB_Handler * handler,
                                 ACE_HANDLE    handle,
                                 bool          flg_all,
                TRB_POSIX_Asynch_Result_Queue & completed_queue);

    bool  cancel_active_queue (TRB_Handler * handler,
                               ACE_HANDLE    handle,
                               bool          flg_all,
                TRB_POSIX_Asynch_Result_Queue & completed_queue);


protected:
    Monitor                       mon_provider_;
    TRB_POSIX_Asynch_Result_Queue started_queue_;
    TRB_POSIX_Asynch_Result_Queue deferred_queue_;
    Notification_Pipe             interrupter_;
    Notification_Result           interrupt_result_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
#endif //TRB_POSIX_AIO_SUN_PROVIDER_H 
