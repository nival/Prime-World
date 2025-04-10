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

#include "TProactor/POSIX_AIO_STD_Provider.h"

#if defined (ACE_HAS_AIO_CALLS)

#include "ace/Log_Msg.h"
#include "ace/ACE.h"

//#include "ace/Addr.h"
//#include "ace/OS_NS_sys_socket.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX AIO  STD Provider
 *****************************************************************
 */
TRB_POSIX_AIO_STD_Provider::~TRB_POSIX_AIO_STD_Provider ()
{
}

TRB_POSIX_AIO_STD_Provider::TRB_POSIX_AIO_STD_Provider
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Provider (config)
, mon_provider_    ()
, started_queue_   ()
, wait_queue_      ()
, deferred_queue_  ()
{
}

int
TRB_POSIX_AIO_STD_Provider::get_supported_operations_mask () const
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
TRB_POSIX_AIO_STD_Provider::register_handle (ACE_HANDLE handle,
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
TRB_POSIX_AIO_STD_Provider::unregister_handle (ACE_HANDLE handle)
{
    ACE_UNUSED_ARG (handle);
    return 0;
}


// *************************************************************
//
// *************************************************************
int
TRB_POSIX_AIO_STD_Provider::finish_aio_completions
     (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);
    return 0;
}

bool
TRB_POSIX_AIO_STD_Provider::begin_aio_wait
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    this->get_completed_aio (wait_time, leader_guard, completed_queue);
    return false;
}

int
TRB_POSIX_AIO_STD_Provider::start_deferred_queue
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

int
TRB_POSIX_AIO_STD_Provider::check_wait_queue
    (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result * result;
    int num_completed = 0;

    while ((result = wait_queue_.pop_front()) !=0)
    {
        bool flg_done = this->test_result_status(result);
        if (flg_done)
        {
            ++num_completed;
            completed_queue.push_back(result);
            if (start_deferred_queue(completed_queue) < 0)
            {
                ++num_completed;
            }
            break;
        }
        this->started_queue_.push_front(result);
    }

    return num_completed;
}

// *************************************************************
//   Cancel AIO
//    return
//     1  nothing to cancel ot all is sone
//     0  cancel initiated
//    -1  errors
// *************************************************************

int
TRB_POSIX_AIO_STD_Provider::cancel_all
    (TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    {
        Guard_Monitor guard (this->mon_provider_);
        this->cancel_deferred_queue (0, completed_queue);
        this->cancel_active_queue (0, this->wait_queue_, completed_queue);
        this->cancel_active_queue (0, this->started_queue_, completed_queue);
    }
    this->interrupt();
    return 0;
}

int
TRB_POSIX_AIO_STD_Provider::cancel_aio
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    {
        Guard_Monitor guard (this->mon_provider_);
        this->cancel_deferred_queue (handler, completed_queue);
        this->cancel_active_queue (handler, this->wait_queue_, completed_queue);
        this->cancel_active_queue (handler, this->started_queue_, completed_queue);
    }
    this->interrupt();
    return 0;
}

int
TRB_POSIX_AIO_STD_Provider::cancel_aio
    (TRB_POSIX_Asynch_Result * result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);
    {
        struct aiocb * aiocb_ptr = result->get_aiocb (); 
        Guard_Monitor guard (this->mon_provider_);
        ::aio_cancel (aiocb_ptr->aio_fildes, 0);
    }
    this->interrupt();
    return 0;
}

int
TRB_POSIX_AIO_STD_Provider::cancel_aio
    (ACE_HANDLE handle,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);
    {
        Guard_Monitor guard (this->mon_provider_);
        ::aio_cancel (handle, 0);
    }
    this->interrupt();
    return 0;
}

bool
TRB_POSIX_AIO_STD_Provider::cancel_active_queue
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & active_queue,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);
    TRB_POSIX_Asynch_Result_Queue::iterator it1 = active_queue.begin();
    TRB_POSIX_Asynch_Result_Queue::iterator it2 = active_queue.end();

    for (; it1 != it2 ; ++it1)
    {
        TRB_POSIX_Asynch_Result * result = (*it1);
        if (handler == 0 ||
            handler == result->get_original_result ().get_handler ())
        {
            struct aiocb * aiocb_ptr = result->get_aiocb (); 
            ::aio_cancel (aiocb_ptr->aio_fildes, 0);
        }
    }
    return false;
}

bool
TRB_POSIX_AIO_STD_Provider::cancel_deferred_queue
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_Queue tmp_queue;
    TRB_POSIX_Asynch_Result * result;

    while((result = deferred_queue_.pop_front()) !=0)
    {
        if (handler == 0 ||
            handler == result->get_original_result ().get_handler ())
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

int
TRB_POSIX_AIO_STD_Provider::start_aio_impl
    (TRB_POSIX_Asynch_Result *result)
{
    result->build_aiocb ();
    struct aiocb * aiocb_ptr = result->get_aiocb (); 

    //
    // temporary while register_handle will be changed
    //
    ACE::clr_flags (aiocb_ptr->aio_fildes, ACE_NONBLOCK);

    int rc = 0;
    switch (result->get_original_result ().op_code ())
    {
    case TRB_Asynch_Result::OP_READ_STREAM:
    case TRB_Asynch_Result::OP_READ_FILE:
        rc = ::aio_read(aiocb_ptr);
        break;

    case TRB_Asynch_Result::OP_WRITE_STREAM:
    case TRB_Asynch_Result::OP_WRITE_FILE:
        rc = ::aio_write (aiocb_ptr);
        break;

    case TRB_Asynch_Result::OP_READ_DGRAM:
    case TRB_Asynch_Result::OP_ACCEPT:
    case TRB_Asynch_Result::OP_WRITE_DGRAM:
    case TRB_Asynch_Result::OP_CONNECT:
        result->set_completion (0, EINVAL);
        return -1;

    default:
        ACE_ASSERT (0);
        result->set_completion (0, ENOTSUP);
        return -1;
    }

    // lock access to the interest list

    if (rc >= 0)  //  success on start
    {
        return 1;
    }

    int error = ACE_OS::last_error();

    switch (error)
    {
    case EAGAIN:
    case ENOMEM:  //Ok, it will be deferred AIO
        return 0;
    }

    result->set_completion (0, error);
    return -1;
}

bool
TRB_POSIX_AIO_STD_Provider::test_result_status (TRB_POSIX_Asynch_Result *result)
{
    struct aiocb * aiocb_ptr = result->get_aiocb (); 
    // Get the error status of the aio_ operation.
    // aio_error can be called many times
    // while operation status is EINPROGRESS

    int val_aio_error = ::aio_error (aiocb_ptr);

    if (val_aio_error == EINPROGRESS)
        return false;  // not completed

    // aio_return can be called only once
    // it tells OS that result is dequed from OS AIO queue

    ssize_t val_aio_return = ::aio_return (aiocb_ptr);

    result->set_completion (val_aio_return, val_aio_error);

    return true; // completed and marked
}

/**
 *****************************************************************
 *  POSIX AIO  AIOCB Provider
 *****************************************************************
 */
TRB_POSIX_AIO_AIOCB_Provider::~TRB_POSIX_AIO_AIOCB_Provider ()
{
    fini ();
}

TRB_POSIX_AIO_AIOCB_Provider::TRB_POSIX_AIO_AIOCB_Provider
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_STD_Provider (config)
, need_interrupt_  (false)
, interrupter_     (false)  // blocking read side
, interrupt_result_(interrupter_)
{
    init ();
}

int
TRB_POSIX_AIO_AIOCB_Provider::init ()
{
    Guard_Monitor guard (this->mon_provider_);

    struct aiocb * aiocb_ptr = this->interrupt_result_.get_aiocb (); 
    aiocb_ptr->aio_sigevent.sigev_notify = SIGEV_NONE;

    this->check_interrupter_result ();
    return 0;
}

int
TRB_POSIX_AIO_AIOCB_Provider::fini ()
{
    this->interrupt();
    TRB_POSIX_Asynch_Result_Queue completed_queue;
    this->cancel_all (completed_queue);
    return 0;
}

int
TRB_POSIX_AIO_AIOCB_Provider::interrupt ()
{
    this->interrupter_.notify();
    return 0;
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
TRB_POSIX_AIO_AIOCB_Provider::start_aio
    (TRB_POSIX_Asynch_Result *result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);

    struct aiocb * aiocb_ptr = result->get_aiocb (); 

    aiocb_ptr->aio_sigevent.sigev_notify = SIGEV_NONE;

    int rc = this->start_aio_impl (result);

    if (rc < 0)   // not started
        return -1;

    if (rc == 0)  // deferred
    {
        Guard_Monitor guard (this->mon_provider_);
        this->deferred_queue_.push_back (result);
        return 0;
    }

    //  started
    {
        Guard_Monitor guard (this->mon_provider_);
        this->started_queue_.push_back (result);
        if (!this->need_interrupt_)
        {
            return 0;
        }

        // request set was updated and
        // we have to interrupt, so reset interrupt flag
        this->need_interrupt_ = false;
    }
    this->interrupt ();
    return 0;
}
// *****************************************************************
//
// *****************************************************************
int
TRB_POSIX_AIO_AIOCB_Provider::get_completed_aio
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    int count = 0;
    {
        Guard_Monitor guard (this->mon_provider_);
        this->check_interrupter_result();

        if (this->check_wait_queue(completed_queue) > 0)
            return 0;

        count = this->build_wait_queue ();

        this->need_interrupt_ = true;
    }

    {
        // only one thread can take leadership
        Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

        this->wait_for_aio(wait_time, count);
    }

    {
        Guard_Monitor guard (this->mon_provider_);
        this->check_interrupter_result();
        this->check_wait_queue(completed_queue);
    }

    return 0;
}

bool
TRB_POSIX_AIO_AIOCB_Provider::check_interrupter_result ()
{
    if (!test_result_status (&this->interrupt_result_))
    {
        return true; // not finished yet, wait
    }

    int rc = this->start_aio_impl (&this->interrupt_result_);
    if (rc <= 0)
    {
        int error = ACE_OS::last_error();
        ACE_ERROR((LM_ERROR,
            ACE_TEXT("TRB_POSIX_AIO_AIOCB_Provider::check_interrupter_result:")
            ACE_TEXT(" unable to start aio error=%d"),
            error));

        return false;
    }

    return true; // started wait
}

bool
TRB_POSIX_AIO_AIOCB_Provider::wait_for_aio (ACE_Time_Value * wait_time,
                                          int count)
{
    int rc = 0;
    if (wait_time == 0) //  wait indefinetely
    {
        rc = ::aio_suspend (this->aiocb_array_,
                            count,
                            0);
    }
    else
    {
        // Block on <aio_suspend> for <milli_seconds>
        timespec timeout = wait_time->operator timespec_t();

        rc = ::aio_suspend (this->aiocb_array_,
                            count,
                            &timeout);
    }

    // Check for errors
    if (rc == -1)
    {
        switch (errno)
        {
        case ETIME :   // Timeout
            break;
        case EAGAIN :   // Timeout
            break;
        case EINTR :    // Interrupted call
            break;

        default:
            ACE_ERROR((LM_ERROR,
                ACE_LIB_TEXT ("%N:%l:(%P | %t)::%p\n"),
                ACE_LIB_TEXT ("TRB_POSIX_AIO_AIOCB_Provider::wait")
                ACE_LIB_TEXT (" <aio_suspend> failed\n")));
            break;
        } //switch
        return true;

    } //if
    return false;
}

int
TRB_POSIX_AIO_AIOCB_Provider::build_wait_queue ()
{
    int i=0;
    aiocb_array_[i++] = this->interrupt_result_.get_aiocb ();

    TRB_POSIX_Asynch_Result * result;

    while((result = started_queue_.pop_front()) !=0)
    {
        aiocb_array_[i++] = result->get_aiocb();
        wait_queue_.push_front(result);
    }
    return i;
}

#if !defined(__Lynx__) && !defined (__FreeBSD__)

/**
 *****************************************************************
 *  POSIX AIO  CB Provider
 *****************************************************************
 */
void TRB_POSIX_AIO_CB_Provider::aio_completion_func (sigval_t cb_data)
{
  TRB_POSIX_AIO_CB_Provider * impl =
      static_cast<TRB_POSIX_AIO_CB_Provider *> (cb_data.sival_ptr);
  if ( impl != 0 )
      impl->interrupt();
}

#if defined (ACE_HAS_SIG_C_FUNC)
extern "C" void
TRB_POSIX_AIO_CB_Provider_aio_completion (sigval_t cb_data)
{
    TRB_POSIX_AIO_CB_Provider::aio_completion_func (cb_data);
}
#endif /* ACE_HAS_SIG_C_FUNC */

TRB_POSIX_AIO_CB_Provider::~TRB_POSIX_AIO_CB_Provider ()
{
    fini ();
}

TRB_POSIX_AIO_CB_Provider::TRB_POSIX_AIO_CB_Provider
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_STD_Provider (config)
, sema_ ((unsigned int) 0)
{
    init ();
}

int
TRB_POSIX_AIO_CB_Provider::init ()
{
    return 0;
}

int
TRB_POSIX_AIO_CB_Provider::fini ()
{
    this->interrupt();
    TRB_POSIX_Asynch_Result_Queue completed_queue;
    this->cancel_all (completed_queue);
    return 0;
}

int
TRB_POSIX_AIO_CB_Provider::interrupt ()
{
    return this->sema_.release();
}
// *****************************************************************
//  Start AIO
//  On return result state contains:
//    STARTED       - "AIO started", i.e. handle is in select mask
//    DEFFERED      - is never returned for this provider
//    START_ERROR   - IO unable to start, i.e. invalid handle
//    RESULT_READY  - IO started and completed immediately
//  Return code :
//    1 - operation finished and added to completion list
//    0 - started
//   -1 - was not started
// *****************************************************************

int
TRB_POSIX_AIO_CB_Provider::start_aio
    (TRB_POSIX_Asynch_Result *result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
  ACE_UNUSED_ARG (completed_queue);

  struct aiocb * aiocb_ptr = result->get_aiocb (); 

  // setup OS notification methods for this aio
  // @@ TODO: This gets the completion method back to this proactor to
  // find the completed aiocb. It would be so much better to not only get
  // the proactor, but the aiocb as well.
#if defined(__sgi)
    aiocb_ptr->aio_sigevent.sigev_notify = SIGEV_CALLBACK;
    aiocb_ptr->aio_sigevent.sigev_func   = aio_completion_func ;
#else
    aiocb_ptr->aio_sigevent.sigev_notify = SIGEV_THREAD;
#  if defined (ACE_HAS_SIG_C_FUNC)
    aiocb_ptr->aio_sigevent.sigev_notify_function =
        TRB_POSIX_AIO_CB_Provider_aio_completion;
#  else
    aiocb_ptr->aio_sigevent.sigev_notify_function = aio_completion_func;
#  endif /* ACE_HAS_SIG_C_FUNC */
    aiocb_ptr->aio_sigevent.sigev_notify_attributes = 0;
#endif /* __sgi */

    aiocb_ptr->aio_sigevent.sigev_value.sival_ptr = this ;

    int rc = this->start_aio_impl (result);

    if (rc < 0)   // not started
        return -1;

    if (rc == 0)  // deferred
    {
        Guard_Monitor guard (this->mon_provider_);
        this->deferred_queue_.push_back (result);
        return 0;
    }

    //  started
    {
        Guard_Monitor guard (this->mon_provider_);
        this->wait_queue_.push_back (result);
    }
    return 0;
}
// *****************************************************************
//
// *****************************************************************
int
TRB_POSIX_AIO_CB_Provider::get_completed_aio
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (leader_guard);

    {
        Guard_Monitor guard (this->mon_provider_);
        if (this->check_wait_queue(completed_queue) >0)
            return 0;

        this->wait_queue_.splice(this->started_queue_);
    }

    this->wait_for_aio (wait_time);

    {
        Guard_Monitor guard (this->mon_provider_);
        this->check_wait_queue(completed_queue);
    }

    return 0;
}


bool
TRB_POSIX_AIO_CB_Provider::wait_for_aio (ACE_Time_Value * wait_time)
{
    int rc = 0;
    if (wait_time == 0) //  wait indefinetely
    {
        rc = this->sema_.acquire();
    }
    else
    {
        // Wait for <milli_seconds> amount of time.
        ACE_Time_Value abs_time = ACE_OS::gettimeofday ()
                                + (*wait_time);

        rc = this->sema_.acquire(abs_time);
    }

    // Check for errors
    if (rc == -1)
    {
        switch (errno)
        {
        case ETIME :   // Timeout
            break;
        case EAGAIN :   // Timeout
            break;
        case EINTR :    // Interrupted call
            break;

        default:
            ACE_ERROR((LM_ERROR,
                ACE_LIB_TEXT ("%N:%l:(%P | %t)::%p\n"),
                ACE_LIB_TEXT ("TRB_POSIX_AIO_CB_Provider::wait")
                ACE_LIB_TEXT ("semaphore acquire failed\n")));
            break;
        } //switch
        return true;

    } //if
    return false;
}

#endif /* !defined(__Lynx__) && !defined (__FreeBSD__)*/


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
