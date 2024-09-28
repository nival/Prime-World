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
// $Id:  $

#include "TProactor/POSIX_AIO_Emulation_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

//#include "ace/OS_NS_sys_socket.h"
#include "ace/Log_Msg.h"
#include "ace/ACE.h"



ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX AIO  Emulation Provider
 *****************************************************************
 */
TRB_POSIX_AIO_Emulation_Provider::~TRB_POSIX_AIO_Emulation_Provider ()
{
}

TRB_POSIX_AIO_Emulation_Provider::TRB_POSIX_AIO_Emulation_Provider 
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Provider (config)
, repository_            (config)
, exec_list_             ()
, exec_monitor_          ()
{
    
}  

// *************************************************************
//        POSIX AIO Provider Interface
// *************************************************************
int
TRB_POSIX_AIO_Emulation_Provider::get_supported_operations_mask () const
{
  return (TRB_Asynch_Result::OP_READ_STREAM 
         |TRB_Asynch_Result::OP_WRITE_STREAM 
         |TRB_Asynch_Result::OP_READ_FILE 
         |TRB_Asynch_Result::OP_WRITE_FILE
         |TRB_Asynch_Result::OP_READ_DGRAM 
         |TRB_Asynch_Result::OP_WRITE_DGRAM 
         |TRB_Asynch_Result::OP_ACCEPT 
         |TRB_Asynch_Result::OP_CONNECT);
         
}  
int 
TRB_POSIX_AIO_Emulation_Provider::register_handle (ACE_HANDLE handle,
                                         const void *completion_key,
                                         int operations)
{
    ACE_UNUSED_ARG (completion_key);
    
    if (!ACE_BIT_CMP_MASK(this->get_supported_operations_mask(),
                          operations, operations))
      {
        return -1;
      }

    if (handle == ACE_INVALID_HANDLE)
     {
        return -1;
     }

    ACE::set_flags (handle, ACE_NONBLOCK);

    // lock FD_Info access for execution 
    FD_Guard fd_guard (this->repository_, handle, true);

    TRB_POSIX_AIO_FD_Info * info = fd_guard.get_fd_info ();
    if (info == 0)
    {
        return -1;
    }

    int rc = info->open (TRB_POSIX_AIO_FD_Info::OPEN_READ | 
                         TRB_POSIX_AIO_FD_Info::OPEN_WRITE, 
                         fd_guard);

    return rc;
}

int 
TRB_POSIX_AIO_Emulation_Provider::unregister_handle (ACE_HANDLE handle)
{
    ACE_UNUSED_ARG(handle);
    return 0;
}

// *************************************************************
//   Cancel AIO
//    return  
//     1  nothing to cancel ot all is sone
//     0  cancel initiated
//    -1  errors
// *************************************************************

int
TRB_POSIX_AIO_Emulation_Provider::cancel_all
    (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    size_t num_files = this->repository_.size ();

    for ( size_t i = 0 ; i <  num_files; ++i)
    {
        this->cancel_aio (i, completed_queue);
    }
    return 0;
}

int
TRB_POSIX_AIO_Emulation_Provider::cancel_aio
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    size_t num_files = this->repository_.size ();

    for ( size_t i = 0 ; i <  num_files; ++i)
    {
        TRB_POSIX_AIO_FD_Info * info;
        {
            FD_Guard guard(this->repository_, i, false);

            info = guard.get_fd_info ();
            if (info == 0 ||
                info->cancel_handler (guard, 
                                      handler, 
                                      completed_queue) != 0)
            {
                continue;
            }
        }
        this->clear_interest (info);
    }
    return 0;
}

int
TRB_POSIX_AIO_Emulation_Provider::cancel_aio 
    (TRB_POSIX_Asynch_Result * result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_HANDLE handle = result->get_original_result ().handle ();
    return this->cancel_aio (handle,completed_queue);
}

int
TRB_POSIX_AIO_Emulation_Provider::cancel_aio 
    (ACE_HANDLE handle,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    int rc;
    TRB_POSIX_AIO_FD_Info * info;
    
    {
        FD_Guard guard(this->repository_, handle, false);

        info = guard.get_fd_info ();
        if (info == 0)
        {
            return 1;
        }

        rc = info->cancel (guard, completed_queue);
    }
    this->clear_interest (info);
    return rc;
}

// *****************************************************************
//  Start AIO
//  On return result state contains:
//  Return code :
//    1 - operation finished and added to completion list
//    0 - started
//   -1 - was not started
// *****************************************************************

int 
TRB_POSIX_AIO_Emulation_Provider::start_aio 
    (TRB_POSIX_Asynch_Result *result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    int rc;
    
    TRB_Asynch_Result & original = result->get_original_result ();

    //// special case for CONNECT
    //if (original.op_code () == TRB_Asynch_Result::OP_CONNECT)
    //{
    //    TRB_POSIX_Asynch_Connect_Result * connect_result =  
    //        static_cast<TRB_POSIX_Asynch_Connect_Result*> (result);
    //        
    //    rc = connect_result->start ();
    //    
    //    if (rc < 0)
    //       return rc;   
    //        
    //    if (rc > 0)
    //      {
    //        completed_queue.push_back (result);
    //        return 1;
    //      }
    //}

    TRB_POSIX_AIO_FD_Info * info;
    ACE_HANDLE handle = original.handle ();
    {
        FD_Guard guard (this->repository_, handle, false);

        info = guard.get_fd_info ();
        if (info == 0)
        {
            result->set_completion (0, EINVAL);
            return -1;
        }
        // call start_read or start_write with locked mutex
        // on return we have mask to declare interest.
        // mutex still is locked on return , but it may be temporary
        // unlocked-locked during FD_Info::start_read/start_write
        if (original.is_read_family())
        {
            rc = info->start_read(result, guard, completed_queue);
        }
        else if (original.is_write_family())
        {
            rc = info->start_write(result, guard, completed_queue);
        }
        else
        {
            result->set_completion (0, EINVAL);
            return -1;
        }
    }

    if (rc > 0)
    {
        this->declare_interest(info, rc & 0xFF, rc >> 8);
        rc = 0;
    }

    return rc;
}

// *************************************************************
//   Get Completed AIO in 2 steps
//   1) wait for ready FD and 
//   2) execute
// *************************************************************
int
TRB_POSIX_AIO_Emulation_Provider::get_completed_aio 
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    int  ready_mask = 0;
    int  remain_mask = 0;
    
    int fd = this->get_ready_fd (wait_time, 
                                 leader_guard,
                                 ready_mask,
                                 remain_mask);

    if (fd == ACE_INVALID_HANDLE)
    {
        return -1;
    }

    
    int rc;
    TRB_POSIX_AIO_FD_Info * info;

    {
        // lock FD_Info access 
        // do not create FD_Info if there is no such element
        FD_Guard fd_guard (this->repository_, fd, false);

        info = fd_guard.get_fd_info ();
        if (info == 0)
        {
            return -1;
        }

        info->update_ready_mask (ready_mask);
        info->set_active_mask (remain_mask);
    
        // execute immeadiately 
        rc = info->execute (fd_guard, completed_queue);
    }

    if (rc > 0)
    {
        this->declare_interest(info, rc & 0xFF, rc >> 8);
    }

    return rc;
}

// *************************************************************
//   begin_aio_wait
//   1) wait for ready FD  and 
//   2) enqueue FD_Info for execution later
// *************************************************************
bool  
TRB_POSIX_AIO_Emulation_Provider::begin_aio_wait 
      (ACE_Time_Value * wait_time,
       Guard_Monitor &  leader_guard,
       TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);

    int  ready_mask = 0;
    int  remain_mask = 0;
    
    int fd = this->get_ready_fd (wait_time, 
                                 leader_guard,
                                 ready_mask,
                                 remain_mask);

    if (fd == ACE_INVALID_HANDLE)
    {
        return false;
    }

    TRB_POSIX_AIO_FD_Info * info;
    {
        // lock FD_Info access 
        // do not create FD_Info if there is no such element
        FD_Guard fd_guard (this->repository_, fd, false);

        info = fd_guard.get_fd_info ();
        if (info == 0)
        {
            return false;
        }
        info->update_ready_mask (ready_mask);
        info->set_active_mask (remain_mask);
    }
    
    {  
        Guard_Monitor exec_guard (this->exec_monitor_);

        if (info->get_link_execute ()->is_free ())
        {
            this->exec_list_.push_back (info);
            return true;
        }
    }

    return false;
}

// *************************************************************
// finish_aio_completions
// 1) execute operations from exec_list_ 
//    (they have FD's ready for read/write)
// *************************************************************
int  
TRB_POSIX_AIO_Emulation_Provider::finish_aio_completions (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    for(;;)
    {
        TRB_POSIX_AIO_FD_Info * info;
        {
            Guard_Monitor  exec_guard (exec_monitor_, true);
            info = this->exec_list_.pop_front ();
        }
  
        if (info == 0)
        {
            break;
        }
        this->execute(info, completed_queue);
    }
    return 0;
}

// *************************************************************
//  get interest mask for given handle
// *************************************************************
int 
TRB_POSIX_AIO_Emulation_Provider::get_interest(ACE_HANDLE handle)
{
    // lock FD_Info access 
    // do not create FD_Info if there is no such element
    FD_Guard fd_guard (this->repository_, handle, false);

    TRB_POSIX_AIO_FD_Info * info = fd_guard.get_fd_info ();
    if (info != 0)
    {
        return info->get_interest ();
    }
    return 0;
}

// *************************************************************
//   execute operations for given FD and 
//   add finished operations to the completion list
// *************************************************************
int
TRB_POSIX_AIO_Emulation_Provider::execute 
    (TRB_POSIX_AIO_FD_Info * info,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    if (info == 0)
    {
        return -1;
    }

    int rc;
    int fd = info->get_handle ();
    // lock FD_Info access 
    // do not create FD_Info if there is no such element
    {
        FD_Guard fd_guard (this->repository_, fd, false);

        ACE_ASSERT (info == fd_guard.get_fd_info ());
    
        rc = info->execute (fd_guard, completed_queue);
    }

    if (rc > 0)
    {
        this->declare_interest(info, rc & 0xFF, rc >> 8);
    }

    return rc;
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
