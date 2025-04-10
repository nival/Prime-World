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

#include "TProactor/POSIX_AIO_Event_Poll_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)
#if defined (ACE_HAS_LINUX_EPOLL)


#include "ace/Log_Msg.h"
//#include "ace/Addr.h"
//#include "ace/ACE.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  Linux  Event Poll  Provider
 *
 *****************************************************************
 */
TRB_POSIX_AIO_Event_Poll_Provider::~TRB_POSIX_AIO_Event_Poll_Provider()
{
    fini ();
}

TRB_POSIX_AIO_Event_Poll_Provider::TRB_POSIX_AIO_Event_Poll_Provider
  (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Emulation_Provider (config)
, max_num_events_ (POLL_MAX_EVENTS)
, num_remain_     (0)
, cur_index_      (0)
, fd_poller_      (ACE_INVALID_HANDLE)
, interrupter_    (true)  // non blocking read side
{
    init ();
}

int
TRB_POSIX_AIO_Event_Poll_Provider::init ()
{
    if (this->fd_poller_ != ACE_INVALID_HANDLE)
    {
        return 0;
    }

    int max_files = this->max_files ();
    this->fd_poller_ =  ::epoll_create(max_files);

    if (this->fd_poller_ == ACE_INVALID_HANDLE)
    {
        return -1;
    }

    return this->declare_interest_i (this->interrupter_.read_handle ());
}

int
TRB_POSIX_AIO_Event_Poll_Provider::fini ()
{
    if (this->fd_poller_ != ACE_INVALID_HANDLE)
    {
        ACE_OS::close (this->fd_poller_);
    }

    this->fd_poller_ = ACE_INVALID_HANDLE;
    return 0;
}

int
TRB_POSIX_AIO_Event_Poll_Provider::interrupt ()
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
TRB_POSIX_AIO_Event_Poll_Provider::declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                                     int interest,
                                                     int remain_mask)
{
    ACE_UNUSED_ARG (interest);
    if (remain_mask != 0)
    {
        return 0;
    }
    int fd = info->get_handle();
    return declare_interest_i (fd);

}

int
TRB_POSIX_AIO_Event_Poll_Provider::clear_interest (TRB_POSIX_AIO_FD_Info * info)
{
    int fd = info->get_handle();
    return this->clear_interest_i (fd);
}

// *****************************************************************
//
// *****************************************************************
int
TRB_POSIX_AIO_Event_Poll_Provider::declare_interest_i (int fd)
{
    struct epoll_event ep;

    ep.events = (EPOLLIN | EPOLLOUT | EPOLLET);
    ep.data.ptr = 0;
    ep.data.fd = fd;

    int op = EPOLL_CTL_ADD;


    // Change the events associated with the given file descriptor.
    int rc = ::epoll_ctl (this->fd_poller_,
                          op,
                          fd,
                          &ep);

    if (rc < 0)
    {
        switch (errno)
        {
        case EEXIST:  // already declared
        case EPERM:   // descriptor is not pollable
            break;   
        default:
            ACE_ERROR_RETURN ((LM_ERROR,
                ACE_LIB_TEXT("(%t) TRB_POSIX_AIO_Event_Poll_Strategy::declare_interest : %p\n"),
                ACE_LIB_TEXT("epoll_ctl failed")),
                -1);
        }
    }
    return 0;
}

int
TRB_POSIX_AIO_Event_Poll_Provider::clear_interest_i (int fd)
{

    struct epoll_event ep;

    ep.events = (EPOLLIN |EPOLLOUT | EPOLLET);
    ep.data.ptr = 0;
    ep.data.fd = fd;

    int op = EPOLL_CTL_DEL;

    // Change the events associated with the given file descriptor.
    int rc = ::epoll_ctl (this->fd_poller_,
                          op,
                          fd,
                          &ep);

    if (rc < 0)
    {
        switch (errno)
        {
        case ENOENT:  // already removed, it is OK
        case EPERM:   // does not support
        case EBADF:   // invalid fd (ignore for cancell_all)
            break;

        default:
          ACE_ERROR_RETURN ((LM_ERROR,
            ACE_LIB_TEXT("(%t) TRB_POSIX_AIO_Event_Poll_Strategy::clear_interest : %p\n"),
            ACE_LIB_TEXT("epoll_ctl failed")),
            -1);
        }
    }
    return 0;
}

int
TRB_POSIX_AIO_Event_Poll_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);

    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}

int
TRB_POSIX_AIO_Event_Poll_Provider::get_ready_fd (ACE_Time_Value * wait_time,
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
TRB_POSIX_AIO_Event_Poll_Provider::find_next_ready_fd (int & ready_mask,
                                                       int & remain_mask)
{
    while (this->cur_index_ < this->num_remain_)
    {
        int index = cur_index_;

        ++this->cur_index_;

        struct epoll_event * pfd = & this->events_ [index];

        ready_mask = 0;

        if (ACE_BIT_ENABLED(pfd->events, (EPOLLIN | EPOLLHUP | EPOLLERR)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
        }

        if (ACE_BIT_ENABLED(pfd->events, (EPOLLOUT | EPOLLHUP | EPOLLERR)))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
        }

        ACE_ASSERT (ready_mask != 0);

        // do not report notification pipe
        if (this->interrupter_.read_handle () == pfd->data.fd)
        {
            this->interrupter_.read ();
            continue;
        }

        remain_mask = TRB_POSIX_AIO_FD_Info::READ
                    | TRB_POSIX_AIO_FD_Info::WRITE;




        return pfd->data.fd;


        //TRB_POSIX_AIO_FD_Info * fd_info =
        //    this->update_fd_info(fd, ready_mask, remain_mask);
        //
        //if (fd_info == 0)
        //{
        //    //this->clear_interest(fd);
        //    continue;
        //}
        //
        //if (ready_mask != 0)
        //{
        //    return pfd->fd;
        //}
    }

    return ACE_INVALID_HANDLE;
}



int
TRB_POSIX_AIO_Event_Poll_Provider::wait_for_ready_fd (ACE_Time_Value * wait_time)
{
    ACE_TRACE ("TRB_POSIX_AIO_Event_Poll_Provider::wait_for_ready_fd");


    long timeout = -1L;

    if (wait_time != 0 )
    {
        timeout =  ACE_static_cast (long, wait_time->msec ());
    }

    // Poll for events
    this->num_remain_ = ::epoll_wait (this->fd_poller_,
                                      this->events_,
                                      this->max_num_events_,
                                      timeout);


    this->cur_index_ = 0;

    if (this->num_remain_ < 0)
    {
        return this->num_remain_ = 0;
    }

    return this->num_remain_;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_LINUX_EPOLL */
#endif /* ACE_HAS_AIO_CALLS */
