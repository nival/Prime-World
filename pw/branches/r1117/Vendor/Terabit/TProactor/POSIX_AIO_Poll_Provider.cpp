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

#include "TProactor/POSIX_AIO_Poll_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "ace/Log_Msg.h"
//#include "ace/Addr.h"
//#include "ace/ACE.h"


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX Poll-based Wait Strategy
 *
 *****************************************************************
 */
TRB_POSIX_AIO_Poll_Provider::~TRB_POSIX_AIO_Poll_Provider()
{
    fini ();
}

TRB_POSIX_AIO_Poll_Provider::TRB_POSIX_AIO_Poll_Provider 
  (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Emulation_Provider (config)
, mon_interest_   ()
, list_interest_  ()
, max_num_events_ (0)
, num_requested_  (0)
, num_remain_     (0)
, cur_index_      (0)
, poll_fds_       (0)
, need_interrupt_ (false)
, interrupter_    (true)  // non blocking read side
{
    init ();
}

int 
TRB_POSIX_AIO_Poll_Provider::init ()
{
    if (this->poll_fds_ == 0)
    {
        this->max_num_events_ = this->max_files ();
        ACE_NEW_RETURN (this->poll_fds_,
                        pollfd[this->max_num_events_],
                        -1);
    }

    return 0;
}

int 
TRB_POSIX_AIO_Poll_Provider::fini ()
{
    delete [] this->poll_fds_;
    this->poll_fds_ = 0;
    return 0;
}

int
TRB_POSIX_AIO_Poll_Provider::interrupt ()
{
    return this->interrupter_.notify();
}
// *****************************************************************
//  Declare interest
//  Return code :
//    1 - leader was interrupted
//    0 - OK, we do not have to interrupt leader
//   -1 - errors
// *****************************************************************
int
TRB_POSIX_AIO_Poll_Provider::declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                               int interest,
                                               int remain_mask)
{
    ACE_UNUSED_ARG (remain_mask);
    ACE_UNUSED_ARG (interest);
    {
        // lock access to the interest list
        Guard_Monitor guard_interest (this->mon_interest_);
        
        bool flgFree = info->get_link_interest()->is_free ();

        if (flgFree)
        {
            this->list_interest_.push_back (info);
        }
        
        if (!this->need_interrupt_)
        {
            return 0;
        }

        // request set was updated and
        // we have to interrupt, so reset interrupt flag 
        need_interrupt_ = false;
    }

    this->interrupt ();
    return 1;
}

int
TRB_POSIX_AIO_Poll_Provider::clear_interest (TRB_POSIX_AIO_FD_Info * info)
{
    ACE_UNUSED_ARG (info);
    return 0;
}

int
TRB_POSIX_AIO_Poll_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}

int
TRB_POSIX_AIO_Poll_Provider::get_ready_fd (ACE_Time_Value * wait_time,
                                           Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    if (fd != ACE_INVALID_HANDLE)
    {
        return fd;
    }

    fd = this->wait_for_ready_fd (wait_time);
    if (fd <= 0)
    {
        return ACE_INVALID_HANDLE;
    }

    fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}


ACE_HANDLE
TRB_POSIX_AIO_Poll_Provider::find_next_ready_fd (int & ready_mask,
                                                 int & remain_mask)
{

    while (this->num_remain_ > 0 && this->cur_index_ < this->num_requested_)
    {
        struct pollfd * pfd = & this->poll_fds_ [this->cur_index_];

        ++this->cur_index_;

        ready_mask = 0;

        // do not report invalid fd, 
        // just remove it later
        if (ACE_BIT_ENABLED(pfd->revents, POLLNVAL))
        {
            continue;
        }

  
        if (ACE_BIT_ENABLED(pfd->revents, (POLLIN|POLLHUP|POLLERR|POLLNVAL)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
        }

        if (ACE_BIT_ENABLED(pfd->revents, (POLLOUT|POLLHUP|POLLERR|POLLNVAL)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
        }

        if (ready_mask == 0)
        {
            continue;
        }

        --this->num_remain_;
        remain_mask = 0;

        if (ACE_BIT_ENABLED(pfd->events, POLLIN))
        {
            ACE_SET_BITS (remain_mask, TRB_POSIX_AIO_FD_Info::READ);
        }
        
        if (ACE_BIT_ENABLED(pfd->events, POLLOUT))
        {
            ACE_SET_BITS (remain_mask, TRB_POSIX_AIO_FD_Info::WRITE);
        }

        // do not report notification pipe 
        if (this->interrupter_.read_handle () == pfd->fd)
        {
            remain_mask = 0;
            this->interrupter_.read ();
            continue;
        }

        
        remain_mask &= ~ready_mask;
        return pfd->fd;
    }

    return ACE_INVALID_HANDLE;
}



int
TRB_POSIX_AIO_Poll_Provider::wait_for_ready_fd (ACE_Time_Value * wait_time)
{
    ACE_TRACE ("TRB_POSIX_AIO_Poll_Provider::wait_for_ready_fd");

    TRB_POSIX_AIO_FD_Info  * fd_info = 0;

    this->num_requested_ = 0;
    this->cur_index_ = 0;
    {
        // lock access to the interest list
        Guard_Monitor guard_interest (this->mon_interest_);

        FD_Info_Interest_List::iterator it1 = this->list_interest_.begin();
        FD_Info_Interest_List::iterator it2 = this->list_interest_.end();

        while(this->num_requested_ < this->max_num_events_ && 
              it1 != it2)
        {
            fd_info = *it1;
            ACE_HANDLE fd = fd_info->get_handle();

            // This will lock-unlock fd guard mutex
            int interest = this->get_interest(fd);
            int events = 0;

            if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::READ))
            {
               events |= POLLIN;
            }

            if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::WRITE))
            {
               events |= POLLOUT;
            }

            if (events == 0)
            {
                // this will remove an item from the list 
                // and advance the iterator
                it1.remove();
            }
            else
            {
                this->poll_fds_[num_requested_].fd = fd;
                this->poll_fds_[num_requested_].events = events;
                this->poll_fds_[num_requested_].revents = 0;

                ++this->num_requested_ ;
                ++it1;
            }
        }

        this->need_interrupt_ = true;
    }

    // insert notification pipe fd into wait list
    if (this->num_requested_ < this->max_num_events_ )
    {
        this->poll_fds_[num_requested_].fd = this->interrupter_.read_handle();
        this->poll_fds_[num_requested_].events = POLLIN;
        this->poll_fds_[num_requested_].revents = 0;
        ++this->num_requested_ ;
    }

    long timeout = -1L;
  
    if (wait_time != 0 )
    {
         timeout =  ACE_static_cast (long, wait_time->msec ());
    }
  
    this->num_remain_ = ::poll (this->poll_fds_, 
                                this->num_requested_, 
                                ACE_static_cast(int, timeout));

    if (this->num_remain_ < 0)
    {
        return this->num_remain_ = 0;
    }

    return this->num_remain_;
}


ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */

