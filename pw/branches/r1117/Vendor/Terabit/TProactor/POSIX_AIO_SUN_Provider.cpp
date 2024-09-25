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

#include "TProactor/POSIX_AIO_SUN_Provider.h"

#if defined(ACE_HAS_AIO_CALLS) && defined(sun)

#include "ace/OS_NS_sys_socket.h"
#include "ace/Log_Msg.h"
#include "ace/ACE.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX AIO  SUN Provider
 *****************************************************************
 */
TRB_POSIX_AIO_SUN_Provider::~TRB_POSIX_AIO_SUN_Provider ()
{
    this->fini ();
}

TRB_POSIX_AIO_SUN_Provider::TRB_POSIX_AIO_SUN_Provider 
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Provider (config)
, mon_provider_    ()
, started_queue_   ()
, deferred_queue_  ()
, interrupter_     (false)  // blocking read side
, interrupt_result_(interrupter_)
{
    //this->init ();
}  

int
TRB_POSIX_AIO_SUN_Provider::get_supported_operations_mask () const
{
  return (TRB_Asynch_Result::OP_READ_STREAM 
         |TRB_Asynch_Result::OP_WRITE_STREAM 
         |TRB_Asynch_Result::OP_READ_FILE 
         |TRB_Asynch_Result::OP_WRITE_FILE);
         
}  

// *************************************************************
//
// *************************************************************
int 
TRB_POSIX_AIO_SUN_Provider::register_handle (ACE_HANDLE handle,
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

    return 0;
}

int 
TRB_POSIX_AIO_SUN_Provider::unregister_handle (ACE_HANDLE handle)
{
    ACE_UNUSED_ARG(handle);
    return 0;
}

int 
TRB_POSIX_AIO_SUN_Provider::init ()
{
    Guard_Monitor guard (this->mon_provider_);
    int rc = this->start_aio_impl (&this->interrupt_result_);
    if (rc <= 0)
    {
        int error = ACE_OS::last_error(); 
        ACE_ERROR((LM_ERROR,
            ACE_TEXT("TRB_POSIX_AIO_SUN_Provider::init:")
            ACE_TEXT(" unable to start aio error=%d\n"),
            error));
        return -1;

    }
    return 0;
}

int 
TRB_POSIX_AIO_SUN_Provider::fini ()
{
    this->interrupt();
    TRB_POSIX_Asynch_Result_Queue completed_queue;
    this->cancel_all (completed_queue);
    return 0;
}

int 
TRB_POSIX_AIO_SUN_Provider::interrupt ()
{
    this->interrupter_.notify();
    return 0;
}

// *************************************************************
//
// *************************************************************
int 
TRB_POSIX_AIO_SUN_Provider::finish_aio_completions 
     (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);
    return 0;
}

bool 
TRB_POSIX_AIO_SUN_Provider::begin_aio_wait 
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    this->get_completed_aio (wait_time, leader_guard, completed_queue);
    return false;
}

// *************************************************************
//   Cancel AIO
//    return  
//     1  nothing to cancel ot all is done
//     0  cancelled
//    -1  errors
// *************************************************************
int
TRB_POSIX_AIO_SUN_Provider::cancel_result
    (TRB_POSIX_Asynch_Result * result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    /// Cancel pending AIO request

    struct aiocb * aiocb_ptr = result->get_aiocb (); 

    int rc = ::aiocancel (&aiocb_ptr->aio_resultp);
  
    // Check the return value and translate into enumeration values
  
    // ****** from Sun man pages *********************
    // Upon successful completion, 
    // aiocancel() returns 0 and the requested operation is cancelled.
    // The application will not receive the SIGIO completion signal 
    // for an asynchronous operation that is successfully cancelled.

    if (rc == 0)       // OK, canceled and dequeued
    {
        result->set_completion (0, ECANCELED);
        completed_queue.push_back(result);
        return 0;
    }
    
    int err = errno;
   
    switch ( errno )   // ****** from Sun man pages *********************
    {
    case EINVAL :                 // Thee are not any outstanding 
                                  // requests to cancel
    case EACCES :                 // The parameter resultp does not 
                                  // correspond to any outstanding 
                                  // asynchronous operation,
                                  // although there is at least 
                                  // one currently outstanding.
        result->set_completion (0, ECANCELED);
        completed_queue.push_back(result);
        return 0;
         


    case EFAULT:                    // resultp points to an address 
                                    // outside the address space 
                                    // of the requesting  process.
    default:
        break;
    }
    ACE_ERROR((LM_ERROR, "(%t) Result not cancelled errno=%d\n", err));
    return -1;
}


int
TRB_POSIX_AIO_SUN_Provider::cancel_all
    (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    Guard_Monitor guard (this->mon_provider_);
    this->cancel_deferred_queue (0, 0, true, completed_queue);
    this->cancel_active_queue (0, 0, true, completed_queue);
    return 0;
}

int
TRB_POSIX_AIO_SUN_Provider::cancel_aio
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    Guard_Monitor guard (this->mon_provider_);
    this->cancel_deferred_queue (handler, 0, false, completed_queue);
    this->cancel_active_queue (handler, 0, false, completed_queue);
    return 0;
}

int
TRB_POSIX_AIO_SUN_Provider::cancel_aio 
    (TRB_POSIX_Asynch_Result * result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_HANDLE handle = result->get_aiocb ()->aio_fildes;
    return this->cancel_aio (handle, completed_queue);
}

int
TRB_POSIX_AIO_SUN_Provider::cancel_aio 
    (ACE_HANDLE handle,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    Guard_Monitor guard (this->mon_provider_);
    this->cancel_deferred_queue (0,handle, false, completed_queue);
    this->cancel_active_queue (0, handle, false, completed_queue);
    return 0;
}

bool
TRB_POSIX_AIO_SUN_Provider::cancel_active_queue
    (TRB_Handler * handler,
     ACE_HANDLE    handle,
     bool          flg_all,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_Queue tmp_queue;
    TRB_POSIX_Asynch_Result * result;

    while((result = started_queue_.pop_front()) !=0)
    {
        if (flg_all ||
            handler == result->get_original_result ().get_handler() ||
            handle == result->get_aiocb ()->aio_fildes)
        {
            if (cancel_result (result, completed_queue) == 0)
            {
                continue;
            }
        }
        tmp_queue.push_front (result);
    }
    this->started_queue_.splice (tmp_queue);
    return  !completed_queue.empty();
}

bool
TRB_POSIX_AIO_SUN_Provider::cancel_deferred_queue
    (TRB_Handler * handler,
     ACE_HANDLE    handle,
     bool          flg_all,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_Queue tmp_queue;
    TRB_POSIX_Asynch_Result * result;

    while((result = deferred_queue_.pop_front()) !=0)
    {
        if (flg_all ||
            handler == result->get_original_result ().get_handler() ||
            handle == result->get_aiocb ()->aio_fildes)
        {
            result->set_completion (0, ECANCELED);
            completed_queue.push_back (result);
        }
        else
        {
            tmp_queue.push_back (result);
        }
    }
    this->deferred_queue_.splice (tmp_queue);
    return  !completed_queue.empty();
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
TRB_POSIX_AIO_SUN_Provider::start_aio 
    (TRB_POSIX_Asynch_Result *result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);

    Guard_Monitor guard (this->mon_provider_);
    int rc = this->start_aio_impl (result);

    if (rc < 0)   // < 0   not started
        return -1;

    if (rc == 0)  // == 0  deferred
    {
        this->deferred_queue_.push_back (result);
        return 0;
    }

    //  > 0  started
    this->started_queue_.push_back (result);

    return 0;
}

int 
TRB_POSIX_AIO_SUN_Provider::start_aio_impl 
    (TRB_POSIX_Asynch_Result *result)
{
    result->build_aiocb ();

    struct aiocb * aiocb_ptr = result->get_aiocb (); 
    // ****** from Sun man pages *********************
    // Upon completion of the operation both aio_return and aio_errno
    // are set to reflect the result of the operation.
    // AIO_INPROGRESS is not a value used by the system
    // so the client may detect a change in state
    // by initializing aio_return to this value.
    int rc = 0;        

    //
    // temporary while register_handle will be changed
    //
    ACE::clr_flags (aiocb_ptr->aio_fildes, ACE_NONBLOCK);


    int op_code = result->get_original_result ().op_code ();
    
    switch (op_code)
    {
    case TRB_Asynch_Result::OP_READ_STREAM:  
    case TRB_Asynch_Result::OP_READ_FILE:
        aiocb_ptr->aio_resultp.aio_return = AIO_INPROGRESS;
        aiocb_ptr->aio_resultp.aio_errno  = EINPROGRESS;
        rc =::aioread (aiocb_ptr->aio_fildes,
                     (char *) aiocb_ptr->aio_buf,
                     aiocb_ptr->aio_nbytes,
                     aiocb_ptr->aio_offset,
                     SEEK_SET,
                     &aiocb_ptr->aio_resultp);
        break;


    case TRB_Asynch_Result::OP_WRITE_STREAM:  
    case TRB_Asynch_Result::OP_WRITE_FILE:
        aiocb_ptr->aio_resultp.aio_return = AIO_INPROGRESS;
        aiocb_ptr->aio_resultp.aio_errno  = EINPROGRESS;
        rc = ::aiowrite (aiocb_ptr->aio_fildes,
                       (char *) aiocb_ptr->aio_buf,
                       aiocb_ptr->aio_nbytes,
                       aiocb_ptr->aio_offset,
                       SEEK_SET,
                       &aiocb_ptr->aio_resultp);
        break;

    case TRB_Asynch_Result::OP_READ_DGRAM:
    case TRB_Asynch_Result::OP_WRITE_DGRAM:
    case TRB_Asynch_Result::OP_ACCEPT:
    case TRB_Asynch_Result::OP_CONNECT:
        result->set_completion (0, ENOTSUP);
        return -1;
    default:
        ACE_ASSERT (0);
        result->set_completion (0, ENOTSUP);
        return -1;
    }

    // lock access to the interest list
        
    if (rc == 0)  //  success on start
    {
        return 1;
    }

    int error = ACE_OS::last_error(); 
    ACE_ERROR((LM_ERROR, "(%t) start failed errno=%d\n", error));
    switch (error)
    {
    case EAGAIN:
    case ENOMEM:  //Ok, it will be deferred AIO
        return 0;
    }

    result->set_completion (0, error);
    return -1;
}

// *****************************************************************
//
// *****************************************************************
int 
TRB_POSIX_AIO_SUN_Provider::get_completed_aio 
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{

    TRB_POSIX_Asynch_Result * posix_result = 0;
    aio_result_t *            aio_result = 0;
    {
        // only one thread can take leadership
        Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

        timeval timeout ;
        timeval * ptime = 0;
  
        if (wait_time != 0) 
        {
            timeout = wait_time->operator timeval();
            ptime = &timeout;
        }
  
        aio_result = ::aiowait (ptime);
    }

    if (aio_result == 0 ||
        reinterpret_cast<long> (aio_result) == -1 )
    {
        return -1;
    }

    {
        Guard_Monitor guard (this->mon_provider_);
        if (this->check_interrupter_result (aio_result))
        {
            return 0;
        }

        posix_result = this->find_completed_result (aio_result);
        if (posix_result != 0)
        {
            completed_queue.push_back(posix_result);
        }
        this->start_deferred_queue (completed_queue);
    }
    return 0;
}

int
TRB_POSIX_AIO_SUN_Provider::start_deferred_queue 
    (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    int num_started = 0;
    TRB_POSIX_Asynch_Result * result;

    while((result = deferred_queue_.pop_front()) !=0)
    {
        int rc = this->start_aio_impl (result);
        if (rc < 0)  // unable to start
        {
            completed_queue.push_back(result);
            return -1;  // we have completions
        }

        if (rc == 0) // still have to try later
        {
            this->deferred_queue_.push_front(result);
            break;
        }
        ++num_started;
        this->started_queue_.push_front(result);
    }
    return num_started;
}


TRB_POSIX_Asynch_Result *
TRB_POSIX_AIO_SUN_Provider::find_completed_result (aio_result_t *aio_result)
{
    TRB_POSIX_Asynch_Result_Queue tmp_queue;
    TRB_POSIX_Asynch_Result * result;

    while ((result = started_queue_.pop_front()) !=0)
    {
        struct aiocb * aiocb_ptr = result->get_aiocb (); 
        if (&aiocb_ptr->aio_resultp == aio_result)
        {
            int  val_aio_error = aiocb_ptr->aio_resultp.aio_errno;
            ssize_t val_aio_return = aiocb_ptr->aio_resultp.aio_return;

            ACE_ASSERT (val_aio_return != AIO_INPROGRESS);

            result->set_completion (val_aio_return, val_aio_error);
            break;
        }
        tmp_queue.push_back(result);
    }
    this->started_queue_.splice (tmp_queue);
    if (result == 0)
    {
         ACE_ERROR((LM_ERROR,"(%t) result not found!!!\n"));
    }
    return result;
}

bool
TRB_POSIX_AIO_SUN_Provider::check_interrupter_result 
    (aio_result_t *result)
{
    struct aiocb * aiocb_ptr = 
      this->interrupt_result_.get_aiocb (); 

    if (result == &aiocb_ptr->aio_resultp)
    {
        int rc = this->start_aio_impl (&this->interrupt_result_);
        if (rc <= 0)
        {
            int error = ACE_OS::last_error(); 
            ACE_ERROR((LM_ERROR,
                ACE_TEXT("TRB_POSIX_AIO_SUN_Provider::check_interrupter_result:")
                ACE_TEXT(" unable to start aio error=%d"),
                error));

        }
        return true;
    }
    
    return false;
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
