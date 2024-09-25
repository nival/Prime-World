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
 *  @file    POSIX_AIO_Emulation_Provider.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================

#ifndef TRB_POSIX_AIO_EMULATION_PROVIDER_H 
#define TRB_POSIX_AIO_EMULATION_PROVIDER_H 

#include "TProactor/POSIX_AIO_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *
 * @class TRB_POSIX_AIO_Emulation_Provider
 *
 */

class TPROACTOR_Export TRB_POSIX_AIO_Emulation_Provider 
    : public TRB_POSIX_AIO_Provider 
{
public:

    TRB_POSIX_AIO_Emulation_Provider (const TRB_POSIX_AIO_Config & config);
    virtual ~TRB_POSIX_AIO_Emulation_Provider();

    virtual int  init () = 0;
    virtual int  fini () = 0;
    virtual int  interrupt () = 0;

    virtual int  get_supported_operations_mask () const;

    virtual int register_handle (ACE_HANDLE  handle,
                               const void *completion_key,
                               int         operations);

    virtual int  unregister_handle (ACE_HANDLE handle);

    
    virtual int  get_completed_aio (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual bool begin_aio_wait (ACE_Time_Value * wait_time,
                    Guard_Monitor &  leader_guard,
                    TRB_POSIX_Asynch_Result_Queue & completed_queue);

    virtual int  finish_aio_completions (
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


    int  max_files ()  const;

protected:
    int  get_interest(ACE_HANDLE handle);
    // Emulation Provider addtional Interface
    virtual int declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                  int interest,
                                  int remain_mask) = 0;

    virtual int clear_interest   (TRB_POSIX_AIO_FD_Info * info) = 0;

    virtual int get_ready_fd (ACE_Time_Value  *wait_time,
                              Guard_Monitor &  leader_guard,
                              int & ready_mask,
                              int & remain_mask) = 0;

    virtual int poll_ready_fd (Guard_Monitor &  leader_guard,
                              int & ready_mask,
                              int & remain_mask) = 0;


    //
private:
    int  execute (TRB_POSIX_AIO_FD_Info * fd_info,
                  TRB_POSIX_Asynch_Result_Queue & completed_queue);



    TRB_POSIX_AIO_FD_Repository repository_;
    FD_Info_Exec_List           exec_list_;
    Monitor                     exec_monitor_;
};

inline int
TRB_POSIX_AIO_Emulation_Provider::max_files () const
{
    return this->repository_.max_files ();
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

#endif //TRB_POSIX_AIO_EMULATION_PROVIDER_H 
