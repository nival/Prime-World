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


#include "TProactor/POSIX_AIO_FD_Info.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "TProactor/POSIX_AIO_Config.h"
//#include "ace/OS_NS_poll.h"
//#include "ace/OS_NS_sys_socket.h"
//#include "ace/Flag_Manip.h"
//#include "ace/ACE.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *
 *
 *****************************************************************
 */
TRB_POSIX_AIO_FD_Repository::TRB_POSIX_AIO_FD_Repository
    (const TRB_POSIX_AIO_Config & config)
: config_    (config)
, num_files_ (0)
, num_slots_ (0)
, array_mon_ (0)
, array_info_(0)
{
    this->open (0,0);
}


TRB_POSIX_AIO_FD_Repository::~TRB_POSIX_AIO_FD_Repository()
{
    this->close ();
}

void
TRB_POSIX_AIO_FD_Repository::close ()
{
    for (size_t i = 0; i < this->num_files_; ++i)
    {
        delete this->array_info_[i];
        this->array_info_ [i] = 0;
    }

    delete [] this->array_info_;
    this->array_info_ = 0;

    delete [] this->array_mon_;
    this->array_mon_  = 0;

    num_slots_ = 0;
    num_files_ = 0;

}

int
TRB_POSIX_AIO_FD_Repository::open(size_t num_files, size_t num_slots)
{
    //this->close ();
    ACE_ASSERT (num_slots_ == 0 && num_files_ == 0 && array_info_== 0);

    size_t max_num_files = this->config_.max_handles();

    ACE_ASSERT ((int)max_num_files > 0);

    if (num_files == 0 || num_files > max_num_files)
    {
        num_files = max_num_files;
    }

    if (num_slots == 0  || num_slots > num_files)
    {
        num_slots = num_files;
    }

    if (num_slots > 1024)
    {
        num_slots = 1024; // why 1024 - should constant
    }

    this->num_files_ = num_files;
    this->num_slots_ = num_slots;

    ACE_NEW_RETURN (this->array_mon_,
                    Monitor[num_slots_],
                   -1);

    ACE_NEW_RETURN (this->array_info_,
                    TRB_POSIX_AIO_FD_Info *[num_files_],
                   -1);

    for (size_t i = 0; i < num_files_; ++i)
    {
        this->array_info_ [i] = 0;
    }
    return 0;
}

/**
 *****************************************************************
 *
 *
 *****************************************************************
 */
TRB_POSIX_AIO_FD_Repository::FD_Guard::FD_Guard(TRB_POSIX_AIO_FD_Repository & rep,
                                                ACE_HANDLE handle,
                                                bool flgCreate)
: Guard_Monitor (rep.array_mon_ [handle % rep.num_slots_], true)
, fd_info_      (0)
{
    this->acquire ();

    if (handle < 0 &&  (size_t) handle >=  rep.num_files_)
    {
        return;
    }

    fd_info_ = rep.array_info_[handle];

    if (this->fd_info_ != 0)
    {
        return;
    }

    if (flgCreate)
    {
        ACE_NEW_NORETURN (this->fd_info_, TRB_POSIX_AIO_FD_Info (handle));
        rep.array_info_[handle] = this->fd_info_;
    }
}


/**
 *****************************************************************
 *
 *
 *****************************************************************
 */
TRB_POSIX_AIO_FD_Info::TRB_POSIX_AIO_FD_Info (int fd)
: fd_            (fd)
, link_interest_ ()
, link_execute_  ()
, read_op_list_  ()
, write_op_list_ ()
, ready_mask_    (0)
, active_mask_   (0)
, flags_         (0)
, num_waiters_   (0)
{
}

TRB_POSIX_AIO_FD_Info::~TRB_POSIX_AIO_FD_Info (void)
{
}

int
TRB_POSIX_AIO_FD_Info::open(int mask,
                            FD_Guard &  guard)
{
    ACE_UNUSED_ARG (mask);
    FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::ACQUIRE);

    if (ACE_BIT_ENABLED (flags_, IN_CANCEL))
    {
        return -1;
    }

    while (ACE_BIT_ENABLED (flags_, IN_EXEC))
    {
        ++num_waiters_;
        guard.wait();
        --num_waiters_;
        // we have to wait for execution
        // otherwise we can execute I/O on new fd
        // that can be assigned to this number
    }

    if (ACE_BIT_ENABLED (flags_, IN_CANCEL))
    {
        return -1;
    }

    ACE_CLR_BITS (flags_, CANCEL);
    ACE_SET_BITS (flags_, OPEN_READ | OPEN_WRITE);

    // assume that descriptor is ready to read and write
    // for edge-triggered providers
    // so Linux epoll will behave as select ()
    ACE_SET_BITS (ready_mask_, READ | WRITE);
    this->active_mask_ = 0;

    return 0;
}


int
TRB_POSIX_AIO_FD_Info::start_read (TRB_POSIX_Asynch_Result * result,
                                   FD_Guard &  guard,
                                   TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::ACQUIRE);

    // check if FD_Info open for operation
    if (ACE_BIT_DISABLED(flags_, OPEN_READ))
    {
        result->set_completion (0, ECANCELED);
        return -1;
    }

    // queue the operation
    bool flgFirst = read_op_list_.empty ();
    read_op_list_.push_back (result);

    if (!flgFirst)
    {
        return 0; // started, i.e. queued
    }

    // this operation is first in the queue
    // try may be in can be executed
    int  rc = this->execute (guard, completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_FD_Info::start_write (TRB_POSIX_Asynch_Result * result,
                                   FD_Guard &  guard,
                                   TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::ACQUIRE);

    // check if FD_Info open for operation
    if (ACE_BIT_DISABLED(flags_, OPEN_WRITE))
    {
        result->set_completion (0, ECANCELED);
        return -1;
    }

    // queue the operation
    bool flgFirst = write_op_list_.empty ();
    write_op_list_.push_back (result);

    if (!flgFirst)
    {
        return 0; // started, i.e. queued
    }

    // this operation is first in the queue
    // try may be in can be executed
    int  rc = this->execute (guard, completed_queue);

    return rc;
}

int
TRB_POSIX_AIO_FD_Info::cancel_handler(FD_Guard &  guard,
                                TRB_Handler * handler,
                              TRB_POSIX_Asynch_Result_Queue & canceled_queue)
{
    FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::ACQUIRE);

    bool found = false;

    TRB_POSIX_Asynch_Result_List::iterator it1 = read_op_list_.begin();
    TRB_POSIX_Asynch_Result_List::iterator it2 = read_op_list_.end();

    for (; it1 != it2  && !found; ++it1)
    {
        if (handler ==  (*it1)->get_original_result ().get_handler ())
        {
            found = true;
        }
    }

    it1 = write_op_list_.begin();
    it2 = write_op_list_.end();

    for (; it1 != it2  && !found; ++it1)
    {
        if (handler ==  (*it1)->get_original_result ().get_handler ())
        {
            found = true;
        }
    }

    if (found)
    {
        return this->cancel (guard, canceled_queue);
    }

    return -1;
}


int
TRB_POSIX_AIO_FD_Info::cancel(FD_Guard &  guard,
                              TRB_POSIX_Asynch_Result_Queue & canceled_queue)
{
    FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::ACQUIRE);

    // check if already canceled
    //if (ACE_BIT_ENABLED(flags_, CANCEL))
    //{
    //    return 1;
    //}

    ACE_SET_BITS (flags_, CANCEL | IN_CANCEL);
    ACE_CLR_BITS (flags_, OPEN_READ | OPEN_WRITE);

    while (ACE_BIT_ENABLED (flags_, IN_EXEC))
    {
        ++num_waiters_;
        guard.wait();
        --num_waiters_;
        // we have to wait for execution
        // otherwise we can execute I/O on new fd
        // that can be assigned to this number
    }

    this->cancel_list (read_op_list_, canceled_queue);
    this->cancel_list (write_op_list_, canceled_queue);

    //if (num_waiters_ != 0)
    //{
    //    guard.broadcast();
    //}
    ACE_CLR_BITS (flags_, IN_CANCEL);
    this->active_mask_ = 0;

    return 0;
}

int
TRB_POSIX_AIO_FD_Info::cancel_list (TRB_POSIX_Asynch_Result_List & pending_list,
                                    TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    TRB_POSIX_Asynch_Result_List::iterator it1 = pending_list.begin();
    TRB_POSIX_Asynch_Result_List::iterator it2 = pending_list.end();

    for (; it1 != it2; ++it1)
    {
         (*it1)->set_completion (0, ECANCELED);
    }

    completed_queue.splice (pending_list);
    return 0;
}

int
TRB_POSIX_AIO_FD_Info::execute (FD_Guard &  guard,
                                TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    FD_Guard::Save_Guard saver(guard,  FD_Guard::Save_Guard::ACQUIRE);

    if (ACE_BIT_ENABLED(flags_, IN_EXEC))
    {
        return 0;
    }

    ACE_SET_BITS (flags_, IN_EXEC);

    bool flg_read ;
    bool flg_write;

    do
    {
        flg_read = execute_read_list (guard, completed_queue);
        flg_write = execute_write_list (guard, completed_queue);

    } while (flg_read || flg_write);

    int rc = 0;
    int interest = get_interest ();

    if ((interest & ~this->active_mask_) != 0)
    {
        // interest has been changed
        // combain old and new interest in rc
        // byte 0 : new interest
        // byte 1 : old interest
        rc = (this->active_mask_ << 8) | interest;

        // assume in advance that interest is declared
        this->active_mask_ |= interest;
    }

    ACE_CLR_BITS (flags_, IN_EXEC);

    if (num_waiters_ != 0)
    {
        guard.broadcast();
    }

    return rc; //  0 or  rc > 0 new and old interest
}

bool
TRB_POSIX_AIO_FD_Info::execute_read_list (FD_Guard &  guard,
                                          TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    if (ACE_BIT_DISABLED (flags_, OPEN_READ))
    {
        cancel_list (read_op_list_, completed_queue);
        return false;
    }

    while (ACE_BIT_ENABLED (ready_mask_, READ))
    {
        TRB_POSIX_Asynch_Result * result = read_op_list_.pop_front ();
        if (result == 0)
        {
            break;
        }

        ACE_CLR_BITS (ready_mask_, READ);

        int rc;

        {
           FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::RELEASE);

           rc = result->execute ();
        }

        if (rc != 0) // finished
        {
            ACE_SET_BITS (ready_mask_, READ);  // restore readyness

            completed_queue.push_back (result);
            return  true;
        }
        
        // here is operation is not finished and guard is locked
        // put operation back in the list and
        // check again for readyness, may be installed by other thread

        read_op_list_.push_front (result);
    }

    return false; 
 }

bool
TRB_POSIX_AIO_FD_Info::execute_write_list(FD_Guard &  guard,
                                          TRB_POSIX_Asynch_Result_Queue & completed_queue)
{
    if (ACE_BIT_DISABLED (flags_, OPEN_WRITE))
    {
        cancel_list (write_op_list_, completed_queue);
        return false;
    }

    while (ACE_BIT_ENABLED (ready_mask_, WRITE))
    {
        TRB_POSIX_Asynch_Result * result = write_op_list_.pop_front ();
        if (result == 0)
        {
            break;
        }

        ACE_CLR_BITS (ready_mask_, WRITE);

        int rc;

        {
           FD_Guard::Save_Guard saver(guard, FD_Guard::Save_Guard::RELEASE);

           rc = result->execute ();
        }

        if (rc != 0) // finished
        {
            ACE_SET_BITS (ready_mask_, WRITE);  // restore readyness

            completed_queue.push_back (result);
            return true;
        }
        
        // here is operation is not finished and guard is locked
        // put operation back in the list and
        // check again for readyness, may be installed by other thread
        
        write_op_list_.push_front (result);
    }

    return false; 
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
