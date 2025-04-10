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

#include "TProactor/POSIX_AIO_Select_Provider.h"

#if defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)

#include "ace/Log_Msg.h"
//#include "ace/Addr.h"
//#include "ace/ACE.h"

#ifndef ACE_FD_SET_TYPE
#define ACE_FD_SET_TYPE  fd_set
#endif

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 *****************************************************************
 *  POSIX Select-based Wait Strategy
 *
 *****************************************************************
 */
TRB_POSIX_AIO_Select_Provider::~TRB_POSIX_AIO_Select_Provider()
{
    fini ();
}

TRB_POSIX_AIO_Select_Provider::TRB_POSIX_AIO_Select_Provider 
  (const TRB_POSIX_AIO_Config & config)
: TRB_POSIX_AIO_Emulation_Provider (config)
, mon_interest_   ()  
, hcur_           (0)
, hmax_           (0)
, num_bits_ready_ (0)
, request_set_    ()
, ready_set_      ()
, need_interrupt_ (false)
, interrupter_    (true)  // non blocking read side
{
    init ();
}

int 
TRB_POSIX_AIO_Select_Provider::init ()
{
    // lock access to the request set
    Guard_Monitor guard_interest (this->mon_interest_);
    int rc = this->declare_interest_i (this->interrupter_.read_handle(),
                                       TRB_POSIX_AIO_FD_Info::READ);               
    
    return rc;
}

int 
TRB_POSIX_AIO_Select_Provider::fini ()
{
    return 0;
}

int
TRB_POSIX_AIO_Select_Provider::interrupt ()
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
TRB_POSIX_AIO_Select_Provider::declare_interest (TRB_POSIX_AIO_FD_Info * info,
                                                 int interest,
                                                 int remain_mask)
{
    ACE_UNUSED_ARG (remain_mask);

    ACE_HANDLE fd = info->get_handle();

    bool flgUpdate;

    {
        // lock access to the request set
        Guard_Monitor guard_interest (this->mon_interest_);

        flgUpdate = this->declare_interest_i (fd, interest);

        if (!this->need_interrupt_ || !flgUpdate)
        {
            return 0;
        }

        // request set was updated and
        // we have to interrupt, so reset interrupt flag 
        this->need_interrupt_ = false;
    }

    this->interrupt ();
    return 1;
}


int
TRB_POSIX_AIO_Select_Provider::clear_interest (TRB_POSIX_AIO_FD_Info * info)
{
    ACE_HANDLE fd = info->get_handle();

    // lock access to the request set
    Guard_Monitor guard_interest (this->mon_interest_);
    this->clear_interest_i (fd, 
                            TRB_POSIX_AIO_FD_Info::WRITE |
                            TRB_POSIX_AIO_FD_Info::READ );
    return 0;
}


// *****************************************************************
//
// *****************************************************************
bool
TRB_POSIX_AIO_Select_Provider::declare_interest_i (ACE_HANDLE handle,
                                                   int interest)
{
    bool flgUpdate = false;

    if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::READ))
    {
        if (this->request_set_.rd_mask_.is_set (handle) == 0)
        {
            this->request_set_.rd_mask_.set_bit (handle);
            flgUpdate = true;
        }
    }

    if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::WRITE))
    {
        if (this->request_set_.wr_mask_.is_set (handle) == 0)
        {
            this->request_set_.wr_mask_.set_bit (handle);
            flgUpdate = true;
        }
    }
    return flgUpdate;
}

int
TRB_POSIX_AIO_Select_Provider::clear_interest_i (ACE_HANDLE handle,
                                               int interest)
{
    int remain_mask = 0;

    if (this->request_set_.rd_mask_.is_set (handle) != 0)
    {
        if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::READ))
        {
            this->request_set_.rd_mask_.clr_bit (handle);
        }
        else 
        {
            remain_mask |= TRB_POSIX_AIO_FD_Info::READ;
        }
    }

    if (this->request_set_.wr_mask_.is_set (handle) != 0)
    {
        if (ACE_BIT_ENABLED (interest, TRB_POSIX_AIO_FD_Info::WRITE))
        {
            this->request_set_.wr_mask_.clr_bit (handle);
        }
        else 
        {
            remain_mask |= TRB_POSIX_AIO_FD_Info::WRITE;
        }
    }
    return remain_mask;
}

int
TRB_POSIX_AIO_Select_Provider::poll_ready_fd (Guard_Monitor &  leader_guard,
                                           int & ready_mask,
                                           int & remain_mask)
{
    // only one thread can take leadership
    Save_Guard lock_leader (leader_guard, Save_Guard::ACQUIRE);
    
    ACE_HANDLE fd = find_next_ready_fd (ready_mask, remain_mask);
    return fd;
}
int
TRB_POSIX_AIO_Select_Provider::get_ready_fd (ACE_Time_Value * wait_time,
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
TRB_POSIX_AIO_Select_Provider::find_next_ready_fd (int & ready_mask,
                                                   int & remain_mask)
{
    while (num_bits_ready_ > 0 && this->hcur_ < this->hmax_)
    {
        int fd = this->hcur_++;

        ready_mask = 0;

        if (this->ready_set_.rd_mask_.is_set (fd))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::READ);
            --this->num_bits_ready_;
        }

        if (this->ready_set_.wr_mask_.is_set (fd))
        {
            ACE_SET_BITS (ready_mask, TRB_POSIX_AIO_FD_Info::WRITE);
            --this->num_bits_ready_;
        }

        if (ready_mask == 0)
        {
            continue;
        }


        // do not report notification pipe 
        if (this->interrupter_.read_handle () == fd)
        {
            this->interrupter_.read ();
            continue;
        }

        
        // lock access to the request set
        Guard_Monitor guard_interest (this->mon_interest_);
        this->need_interrupt_ = false;
        remain_mask = this->clear_interest_i (fd, ready_mask);

        return  fd;

        //ACE_DEBUG ((LM_DEBUG, "(%t) fd=%d mask=%d\n", fd, ready_mask));
        //if (this->update_fd_info(fd, ready_mask, remain_mask) != 0)
        //{
        //    return fd;
        //}
    }

    return ACE_INVALID_HANDLE;
}



int
TRB_POSIX_AIO_Select_Provider::wait_for_ready_fd (ACE_Time_Value * wait_time)
{
    ACE_TRACE ("TRB_POSIX_AIO_Select_Provider::wait_for_ready_fd");

    {
        // lock access to the request set
        Guard_Monitor guard_interest (this->mon_interest_);
      
        this->ready_set_ = this->request_set_;
        this->need_interrupt_ = true;
    }
  
    ACE_HANDLE hr = this->ready_set_.rd_mask_.max_set();
    ACE_HANDLE hw = this->ready_set_.wr_mask_.max_set();
  
    this->hcur_ = 0;
    this->hmax_ = (hr > hw) ? hr : hw;

    if (this->hmax_ < 0)
    {
    //     ACE_DEBUG ((LM_DEBUG,"**** hmax = %d\n", this->hmax_));

        this->hmax_ = 0;
        return 0; 
    }

    this->hmax_++;

    // I'd like to use ACE_OS::select(),
    // but it re-issued select in case of EINTR.
    // We can use EINTR as signal to stop select. 

    timeval tv;
    timeval *timep =0;

    if (wait_time != 0)
    {
        tv = * wait_time;
        timep = &tv;
    }

    //
    //  ACE_ERROR((LM_ERROR,"(%t) Before select hmax=%d\n",this->hmax_));
    //
    //  this->ready_set_.rd_mask_.dump();
    //  this->ready_set_.wr_mask_.dump();
    //  this->ready_set_.ex_mask_.dump();
  
    this->num_bits_ready_= 
        ::select ((int)this->hmax_,
                  (ACE_FD_SET_TYPE *) this->ready_set_.rd_mask_,
                  (ACE_FD_SET_TYPE *) this->ready_set_.wr_mask_,
                  (ACE_FD_SET_TYPE *) 0,
                   timep);

    //
    //  int save_err =errno;
    //
    //  ACE_ERROR((LM_ERROR,"(%t) After select rc=%d hmax=%d errno=%d %s\n",
    //             rc, 
    //             this->hmax_,
    //              rc >= 0 ? 0 : save_err , 
    //              rc >= 0 ? "no error" : ACE_OS::strerror(save_err)));
    //
    //  this->ready_set_.rd_mask_.dump();
    //  this->ready_set_.wr_mask_.dump();
    //  this->ready_set_.ex_mask_.dump();
    //
    //  errno=save_err;
    //

    if (this->num_bits_ready_ > 0)
    {
        return this->num_bits_ready_;
    }

    this->hmax_ = 0;

    if (this->num_bits_ready_ == 0)
    {
        return 0;
    }
    
    this->num_bits_ready_ = 0;

    switch (errno)
    {
    case EINTR :    // Interrupted call
        return -1;

    case EBADF :  
        //  TODO: some descriptors are invalid.
        //  Reason: user closed file with pending AIO!
        //  Action: check all results for valid descriptors.
        //  If descriptor is invalid, complete AIO
        //  with ECANCELED/EABORTED

        //this->ready_set_ = this->request_set_;
          
        //for ( int i=0; i < this->hmax_; ++i)
        //{
        //    this->ready_set_.rd_mask_.set_bit(i);
        //    this->ready_set_.wr_mask_.set_bit(i);
        //}
      
        return -1;

    default:
        break;
    }
    
    return -1;
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_AIO_CALLS */
