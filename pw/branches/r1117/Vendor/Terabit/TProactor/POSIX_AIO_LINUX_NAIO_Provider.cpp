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

#include "TProactor/POSIX_AIO_LINUX_NAIO_Provider.h"

#if defined(ACE_HAS_AIO_CALLS) && defined (ACE_HAS_LINUX_LIBAIO) && defined(linux)

//#include "ace/OS_NS_sys_socket.h"
#include "ace/Log_Msg.h"
#include "ace/ACE.h"



ACE_BEGIN_VERSIONED_NAMESPACE_DECL
/**
 *****************************************************************
 *  TRB_POSIX_AIO_Provider::Notification_File
 *****************************************************************
 */
TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::Notification_File ()
: handle_   (ACE_INVALID_HANDLE)
, buffer_   ()
, iocb_     ()
{
    ACE_OS::memset (this->buffer_, 0, sizeof (buffer_));
    ACE_OS::memset (&this->iocb_, 0, sizeof (iocb_));
}

TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::~Notification_File ()
{
    this->close ();
}

int 
TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::close ()
{
    if (this->handle_ != ACE_INVALID_HANDLE) 
    {
        ACE_OS::close (this->handle_);
        this->handle_ = ACE_INVALID_HANDLE;
    }
    return 0;
}

int 
TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::open ()
{
    if (this->handle_ != ACE_INVALID_HANDLE)
        return 0;  // already open

    this->handle_ = ACE_OS::open("LINUX_NAIO_Notifier",
                                  O_RDWR | O_CREAT);

    if (this->handle_ == ACE_INVALID_HANDLE)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) ACE_POSIX_AIO_LINUX_Provider:: %p\n"),
            ACE_LIB_TEXT ("<Notification_File::open> failed")),
            -1);
    }

    return 0;
}


int 
TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::notify (io_context_t context)
{
    io_prep_pwrite (&this->iocb_,
                    this->handle_,
                    this->buffer_,
                    sizeof(this->buffer_),
                    0);

    iocb_.data = this;
    struct iocb * iocb_ptr = &this->iocb_;

    int rc = io_submit (context, 1, &iocb_ptr);
    if (rc <= 0)
    {
        return -1;
    }

    return 0;
}

bool 
TRB_POSIX_AIO_LINUX_NAIO_Provider::Notification_File::check(struct io_event& event)
{
    return (event.data == this) ? true : false;
}


/**
 *****************************************************************
 *  POSIX AIO  LINUX_NAIO Provider
 *****************************************************************
 */
TRB_POSIX_AIO_LINUX_NAIO_Provider::~TRB_POSIX_AIO_LINUX_NAIO_Provider ()
{
    this->fini ();
}

TRB_POSIX_AIO_LINUX_NAIO_Provider::TRB_POSIX_AIO_LINUX_NAIO_Provider 
    (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Provider (config)
, context_        (0)
, events_         ()
, max_num_events_ (sizeof(events_)/sizeof(events_[0]))
, num_remain_     (0)
, cur_index_      (0)
, interrupter_    ()
, repository_     (config)
{
    this->init ();
}  

// *************************************************************
//        POSIX AIO Provider Interface
// *************************************************************
int
TRB_POSIX_AIO_LINUX_NAIO_Provider::init ()
{
    if (this->context_ != 0)
        return 0;  // OK , all is done

    int rc = io_setup (ACE_AIO_MAX_SIZE, &context_);

    if (rc != 0)
    {
        this->context_ = 0;
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) ACE_POSIX_AIO_LINUX_Provider::init %p\n"),
            ACE_LIB_TEXT ("<io_setup> failed")),
            -1);
    }

    if (this->interrupter_.open () != 0)
        return -1;

    if (this->register_handle(interrupter_.handle (), 
                              0,
                              TRB_Asynch_Result::OP_WRITE_FILE) != 0)

    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) ACE_POSIX_AIO_LINUX_Provider::init %p\n"),
            ACE_LIB_TEXT ("<register_handle> failed")),
            -1);
    }
    return 0;
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::fini ()
{
    this->interrupter_.close();

    if (this->context_ != 0)
    {
        io_destroy (this->context_);
        this->context_ = 0;
    }
    return 0;
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::interrupt ()
{
    // Interrupt has dual purpose
    // a) to interrupt provider to start new operation
    //    or update wait state. This provider does not
    //    need to be interrupted
    // b) interrupt  is required for shared processors
    //    to interrupt waiting in provider. This allows
    //    to return control to the Dispatcher to process
    //    completion queue. For dedicated processors
    //    interrupt is required only to stop .
    // There is no way to interrupt io_getevents
    // We should wait till IO_CMD_POLL will be supported
    // or try to send a signal.
    // In any case we assume that provider will used
    // with dedicated processor for now
    return this->interrupter_.notify (this->context_);  
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::get_supported_operations_mask () const
{
    return (TRB_Asynch_Result::OP_READ_FILE 
           |TRB_Asynch_Result::OP_WRITE_FILE);
       
}  
int 
TRB_POSIX_AIO_LINUX_NAIO_Provider::register_handle (ACE_HANDLE handle,
                                         const void *completion_key,
                                         int operations)
{
    ACE_UNUSED_ARG (completion_key);

    if (!ACE_BIT_CMP_MASK(this->get_supported_operations_mask(),
                          operations, 
                          operations))
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
TRB_POSIX_AIO_LINUX_NAIO_Provider::unregister_handle (ACE_HANDLE handle)
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
TRB_POSIX_AIO_LINUX_NAIO_Provider::cancel_all
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
TRB_POSIX_AIO_LINUX_NAIO_Provider::cancel_aio
    (TRB_Handler * handler,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    size_t num_files = this->repository_.size ();

    for ( size_t i = 0 ; i <  num_files; ++i)
    {
        FD_Guard guard(this->repository_, i, false);

        TRB_POSIX_AIO_FD_Info * info = guard.get_fd_info ();
        if (info == 0)
        {
            continue;
        }

        this->cancel_queue (handler, info->get_read_list(), completed_queue);
        this->cancel_queue (handler, info->get_write_list(), completed_queue);
    }
    return 0;
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::cancel_aio 
    (TRB_POSIX_Asynch_Result * result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    return this->cancel_aio (result->get_original_result ().handle (),
                             completed_queue);
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::cancel_aio 
    (ACE_HANDLE handle,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    FD_Guard guard(this->repository_, handle, false);

    TRB_POSIX_AIO_FD_Info * info = guard.get_fd_info ();
    if (info == 0)
    {
        return 1;
    }

    this->cancel_queue (0, info->get_read_list(), completed_queue);
    this->cancel_queue (0, info->get_write_list(), completed_queue);

    return 0;
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::cancel_queue(
                            TRB_Handler * handler,
                            TRB_POSIX_Asynch_Result_List & pending_list,
                            TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_List  tmp_list;
    struct io_event event;

    for (;;)
    {
        TRB_POSIX_Asynch_Result * result = pending_list.pop_front ();
        if (result == 0)
            break;

        int rc = -1 ; // not cancelled

        if (handler == 0 ||
            result->get_original_result ().get_handler () == handler)
        {

            struct iocb *iocb_ptr = result->get_iocb ();
            rc = io_cancel (this->context_, iocb_ptr, &event);
            // check errno
        }

        if (rc == 0) // cancelled
        {
            result->set_completion (event.res, event.res2);
            completed_queue.push_back (result);  // cancelled
        }
        else
        {
            tmp_list.push_front (result);  // still pending
        }
    }
    pending_list.splice (tmp_list);  // put back pending results
    return 0;
}

// *****************************************************************
//  Start AIO
//  Return code :
//    1 - operation finished and added to completion list
//    0 - started
//   -1 - was not started
// *****************************************************************

int 
TRB_POSIX_AIO_LINUX_NAIO_Provider::start_aio 
    (TRB_POSIX_Asynch_Result *result,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    ACE_UNUSED_ARG (completed_queue);

    TRB_Asynch_Result&  original = result->get_original_result ();
    struct iocb        *iocb_ptr = result->get_iocb ();

    int  op_code = original.op_code ();
    char *buffer = 0;
    ACE_Message_Block *msg = original.get_message_block_ptr ();
    TRB_POSIX_Asynch_Result_List *list = 0;

    TRB_POSIX_AIO_FD_Info * info;
    ACE_HANDLE handle = original.handle ();

    // do not create new FD_Info (third argument is false)
    FD_Guard guard (this->repository_, handle, false);

    info = guard.get_fd_info ();
    if (info == 0)
    {
        result->set_completion (0, EINVAL);
        return -1;
    }


    // special case for CONNECT
    // when we include support for IO_CMP_POLL_WAIT
    //
    //if (op_code == TRB_Asynch_Result::OP_CONNECT)
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

    switch (op_code)
    {
    case TRB_Asynch_Result::OP_READ_FILE:
        buffer = msg ? msg->wr_ptr() : 0;
        if (buffer == 0)
        {
            result->set_completion (0, EINVAL);
            return -1;
        }

        // check if FD_Info open for operation
        if (!info->is_open_for_read ())
        {
            result->set_completion (0, ECANCELED);
            return -1;
        }

        list = &info->get_read_list ();

        io_prep_pread (iocb_ptr,
                       handle,
                       buffer,
                       original.bytes_requested (),
                       original.offset ());
        break;

    case TRB_Asynch_Result::OP_WRITE_FILE:
        buffer = msg ? msg->rd_ptr() : 0;
        if (buffer == 0)
        {
            result->set_completion (0, EINVAL);
            return -1;
        }

        // check if FD_Info open for operation
        if (!info->is_open_for_write ())
        {
            result->set_completion (0, ECANCELED);
            return -1;
        }

        list = &info->get_write_list ();

        io_prep_pwrite (iocb_ptr,
                        handle,
                        buffer,
                        original.bytes_requested (),
                        original.offset ());
        break;

    default:
        result->set_completion (0, ENOTSUP);
        return -1;
    }

    iocb_ptr->data = result;
    int rc = io_submit (this->context_, 1, &iocb_ptr);
    if (rc <= 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) ACE_POSIX_AIO_LINUX_Provider::init %p\n"),
            ACE_LIB_TEXT ("<io_submit> failed")),
            -1);
        result->set_completion (0, errno);
        return -1;
    }


    list->push_back (result);
    return 0;
}

// *************************************************************
//   Get Completed AIO
// *************************************************************
int
TRB_POSIX_AIO_LINUX_NAIO_Provider::get_completed_aio 
    (ACE_Time_Value * wait_time,
     Guard_Monitor &  leader_guard,
     TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    struct io_event event;

    {
        // only one thread can take leadership
        Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

        if (find_next_event(event) != 0)
        {
            if (this->wait_for_events (wait_time) !=0)
                return -1;

            if (find_next_event(event) != 0)
                return -1;
        }
    }

    if (!this->interrupter_.check(event))
    {
        this->process_event (event, completed_queue);
    }
    return 0;
}


int
TRB_POSIX_AIO_LINUX_NAIO_Provider::find_next_event (struct io_event& event)
{ 
    if (this->cur_index_ < this->num_remain_)
    {
        // consume event, i.e. copy POD data
        event = this->events_ [this->cur_index_];
        ++this->cur_index_;
        return 0;
    }
    return -1;
}

int
TRB_POSIX_AIO_LINUX_NAIO_Provider::wait_for_events (ACE_Time_Value *wait_time)
{
    timespec timeout = {0,0} ;
    timespec * ptime = 0;

    if (wait_time != 0) 
    {
        timeout = wait_time->operator timespec();
        ptime = &timeout;
    }


    this->cur_index_ = 0;

    this->num_remain_ = io_getevents (this->context_,
                                      1,
                                      this->max_num_events_,
                                      this->events_,
                                      ptime);

    if (this->num_remain_ < 0)
    {
        this->num_remain_ = 0;
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT ("(%t) io_getevents error=%d %p\n"),
            (int) ACE_OS::last_error(),
            ACE_LIB_TEXT ("text")),
            -1);
    }

    return 0;
}

void
TRB_POSIX_AIO_LINUX_NAIO_Provider::process_event (struct io_event& event,
                          TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result * result =
        (TRB_POSIX_Asynch_Result *) event.data;

    // Remove this ASSERT later, this is just for testing
    struct iocb *iocb_ptr = result->get_iocb ();

    ACE_ASSERT (result == iocb_ptr->data);

    TRB_Asynch_Result & original = result->get_original_result ();

    ACE_HANDLE handle = original.handle ();
    TRB_POSIX_AIO_FD_Info * info;

    {
        // do not create new FD_Info (third argument is false)
        FD_Guard guard (this->repository_, handle, false);

        info = guard.get_fd_info ();
        if (info == 0)
        {
            ACE_ASSERT(0);
            return;
        }

        int   op_code = original.op_code ();
        TRB_POSIX_Asynch_Result_List *list = 0;
        switch (op_code)
        {
        case TRB_Asynch_Result::OP_READ_FILE:
            list = &info->get_read_list ();
            break;

        case TRB_Asynch_Result::OP_WRITE_FILE:
            list = &info->get_write_list ();
            break;

        default:
            ACE_ASSERT(0);
            return;
        }

        TRB_POSIX_Asynch_Result *ret = list->remove (result);
        ACE_ASSERT (ret == result);
    }

    u_long  nbytes = event.res;
    u_long  err    = event.res2;
    result->set_completion (nbytes, err);
    completed_queue.push_back (result);
}

// *************************************************************
//   begin_aio_wait
//   wait for ready FD  and  enqueue FD_Info for execution
// *************************************************************
bool  
TRB_POSIX_AIO_LINUX_NAIO_Provider::begin_aio_wait 
      (ACE_Time_Value * wait_time,
       Guard_Monitor &  leader_guard,
       TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    this->get_completed_aio (wait_time, leader_guard, completed_queue);
    return false;
}
// *************************************************************
//
// *************************************************************
int  
TRB_POSIX_AIO_LINUX_NAIO_Provider::finish_aio_completions (
                    TRB_POSIX_Asynch_Result_Queue & completed_queue)

{
    ACE_UNUSED_ARG (completed_queue);
    return 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* defined(ACE_HAS_AIO_CALLS) && defined (ACE_HAS_LINUX_LIBAIO) && defined(linux) */

