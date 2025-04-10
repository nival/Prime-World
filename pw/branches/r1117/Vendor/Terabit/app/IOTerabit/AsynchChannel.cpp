/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  @file AsynchChannel.cpp
**   
**  @author Alexander Libman <libman@terabit.com.au>
**  
**********************************************************************/

#include "IOTerabit/AsynchChannel.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/Protocol.h"

#include "ace/OS_NS_sys_socket.h"

namespace Terabit {


// ***************************************************************
//  AsynchChannelList 
// ***************************************************************
AsynchChannelList::AsynchChannelList ()
: Double_List_T <AsynchChannel> ()
{
}

AsynchChannelList::~AsynchChannelList ()
{
    ACE_ASSERT (this->empty());
}

bool 
AsynchChannelList::insert_channel (AsynchChannel *channel)
{
    //ACE_ASSERT (channel->get_link ()->is_free());
    
    ACE_ASSERT (channel->LinkD_T<AsynchChannel>::is_free());
    
    iterator itr = this->push_front (channel);
    channel->itr_ = itr;
    return true;
}

bool 
AsynchChannelList::remove_channel (AsynchChannel *channel)
{
    iterator itr = channel->itr_;
    ACE_ASSERT (*itr == channel);
    
    AsynchChannel  *ret = this->remove (itr);
    ACE_ASSERT (ret == channel);
    
    channel->itr_ = iterator ();
    return true;
}
// *************************************************************
// AsynchChannel::Info
// ************************************************************
AsynchChannel::Info::Info (unsigned int id)
: id_               (id)
, total_snd_        (0)    
, total_rcv_        (0)  
, total_w_          (0)  
, total_r_          (0) 
, state_            (AsynchChannel::ST_INIT)
, err_flags_        (AsynchChannel::ERR_NONE)
, error_            (0)
, io_flags_         (0)
, cb_flags_         (0)
, mode_flags_       (AsynchChannel::MODE_AUTO_READ)
, read_size_        (AsynchChannel::DEFAULT_READ_SIZE)
, timer_id_         (-1)
, last_op_time_     (ACE_Time_Value::zero)
, remote_addr_      ()
, local_addr_       ()
{
}

void
AsynchChannel::Info::reset ()
{
    // we never change id_ 
    total_snd_        = 0;    
    total_rcv_        = 0;  
    total_w_          = 0;  
    total_r_          = 0; 
    state_            = AsynchChannel::ST_INIT;
    err_flags_        = AsynchChannel::ERR_NONE;
    error_            = 0;
    io_flags_         = 0;
    cb_flags_         = 0;
    mode_flags_       = AsynchChannel::MODE_AUTO_READ;
    read_size_        = AsynchChannel::DEFAULT_READ_SIZE;
    timer_id_         = -1;
    last_op_time_     = ACE_Time_Value::zero;
    remote_addr_      = ACE_INET_Addr ();
    local_addr_       = ACE_INET_Addr ();
}

void
AsynchChannel::Info::print (const ACE_TCHAR *txt)
{
    if (!txt)
    {
        txt ="";
    }

    ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s channel id=(%c)%d Snd=%Q(%Q) Rcv=%Q(%Q) Pending=%04x\n"),
              txt,
              ACE_BIT_ENABLED (this->mode_flags_, MODE_SERVER) ? 'S' : 'C',
              (int) id_,
              (ACE_INT64)this->total_snd_,
              (ACE_INT64)this->total_w_,
              (ACE_INT64)this->total_rcv_,
              (ACE_INT64)this->total_r_,
              (int) this->io_flags_));
}

// ***************************************************************
//  AsynchChannel 
// ***************************************************************

AsynchChannel::AsynchChannel (unsigned int id)
: RefCount     ()
, TRB_Handler  ()
//, link_        ()
, itr_         ()
, manager_     (0)
, info_        (id)
, self_        (0)
, protocol_    (0)
, rd_mb_       (info_.read_size_)
, wr_mq_       (0)
, mb_cache_    (0, //   initial_cache_size,
                MessageBlockFactory_T<ACE_NULL_SYNCH>::DEF_MSG_SIZE,   // msg size
                MessageBlockFactory_T<ACE_NULL_SYNCH>::DEF_CACHE_SIZE, // limit
                0)
{
}

AsynchChannel::AsynchChannel (unsigned int id, unsigned int mb_cache_limit)
: RefCount     ()
, TRB_Handler  ()
//, link_        ()
, itr_         ()
, manager_     (0)
, info_        (id)
, self_        (0)
, protocol_    (0)
, rd_mb_       (info_.read_size_)
, wr_mq_       (0)
, mb_cache_    (0, //   initial_cache_size,
                MessageBlockFactory_T<ACE_NULL_SYNCH>::DEF_MSG_SIZE,   // msg size
                mb_cache_limit, // limit
                0)
{
}

AsynchChannel::~AsynchChannel (void)
{
}

void
AsynchChannel::get_info(Info & info)
{
    info = this->info_;
}

void
AsynchChannel::addresses (const ACE_Addr & remote,
                          const ACE_Addr & local)
{
    this->info_.remote_addr_ = remote;
    this->info_.local_addr_  = local;
}

void 
AsynchChannel::set_manager (ChannelManager * manager)
{
    ACE_ASSERT (this->info_.state_ == ST_INIT);
    this->manager_ = manager;
    this->proactor (manager->get_task ().get_proactor (0));
}

ACE_Message_Block *
AsynchChannel::alloc_msg (size_t length)
{
    return this->mb_cache_.alloc_msg (length);
}

ACE_Message_Block *
AsynchChannel::alloc_msg (size_t length, unsigned long long tag)
{
    return this->mb_cache_.alloc_msg (length, tag);
}

void
AsynchChannel::free_msg (ACE_Message_Block * mb)
{
    this->mb_cache_.free_msg (mb);
}

void
AsynchChannel::reset ()
{
    ACE_ASSERT (!this->self_);
    ACE_ASSERT (!this->protocol_);
    ACE_ASSERT (this->wr_mq_ == 0);
    
    //ACE_ASSERT (this->link_.is_free ());
    ACE_ASSERT (LinkD_T<AsynchChannel>::is_free ());
    
    RefCount::set (0);
   
    this->info_.reset ();
    this->rd_mb_.reset ();
    this->reset_impl ();
}

void
AsynchChannel::free ()
{
    //{
    //    RefCountGuard guard (*this);
    //    ACE_ASSERT (this->info_.state_ == ST_CLOSED);
    //    ACE_ASSERT (this->manager_ != 0);
    //}
    this->manager_->free_channel (this);
}

int
AsynchChannel::open(ACE_HANDLE  handle,
                    bool        flg_server)
{
    RefCountPtr tmp (this);
    RefCountGuard guard (*this);
    if (flg_server)
    {
        ACE_SET_BITS (this->info_.mode_flags_, MODE_SERVER);
    }
    else
    {
        ACE_CLR_BITS (this->info_.mode_flags_, MODE_SERVER);
    }

    if (this->info_.state_ == ST_CLOSED)
    {
        ACE_OS::closesocket (handle);
        return -1;
    }

    ACE_ASSERT (this->info_.state_ == ST_INIT);
    if (this->open_impl (handle, flg_server) != 0)
    {
        this->close_impl ();
        this->info_.state_ = ST_CLOSED;
        return -1;
    }

    this->self_.swap (tmp);
    this->info_.state_ = ST_ACTIVE;
    return 0;
}

int
AsynchChannel::activate_protocol(Protocol   *protocol,
                                 const char *data,
                                 size_t      datalen)
{
    RefCountPtr tmp (0);

    RefCountGuard guard (*this);

    ACE_ASSERT (this->protocol_ == 0);
    this->protocol_ = protocol;

    if (this->info_.state_ == ST_ACTIVE)
    {
        MessageBlockFactory * mbf = protocol->get_message_block_factory ();
        if (mbf == 0)
        {
            mbf = this->manager_->get_message_block_factory ();
        }

        this->mb_cache_.set_parent (mbf);
 
        int rc = -1;
        ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_OPEN | FLG_CALLBACK_READ);
        {
            RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
            try
            {
                rc = this->protocol_->on_channel_opened (this) ;
                if (rc >= 0  && this->is_server () && datalen != 0)
                {
                    rc = this->protocol_->on_read_completed (this,
                                                             data,
                                                             datalen);
                }
            }
            catch (...)
            {
                rc = -1;
                ACE_ERROR((LM_ERROR,
                    ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::on_channel_opened()\n"),
                    this->is_server () ? 'S' : 'C',
                    this->get_id () ));
            }
        }
        if (rc < 0)
        {
            this->initiate_close (ERR_PROTOCOL, 0);
        }
        else
        {
            if (this->is_server ())
            {
                ACE_ASSERT ((size_t) rc <= datalen);
                if ((size_t)rc < datalen && data != 0)
                {
                    this->rd_mb_.copy (data + rc,  datalen - rc);
                }
            }
            start_read_internal ();
        }
        ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_OPEN | FLG_CALLBACK_READ);
    } 
    
    if (check_closure (true, guard) == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
    return 0;
}

AsynchChannel::State
AsynchChannel::close (bool flg_callback)
{
    RefCountPtr tmp (0);
    RefCountGuard guard (*this);
    this->initiate_close (0, 0);
    AsynchChannel::State rc = this->check_closure (flg_callback, guard);
    if (rc == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
    return rc;
}
  

AsynchChannel::State
AsynchChannel::initiate_close (int err_flags, u_long error)
{
    switch (this->info_.state_)
    {
    case ST_CLOSED:  
        return this->info_.state_;      // already closed
    case ST_CANCEL: 
        return this->info_.state_;      // already in cancel
    case ST_INIT:   
        this->info_.state_ = ST_CLOSED;
        return this->info_.state_;
    case ST_ACTIVE:  
        break;
    }

    // move to ST_CANCEL state
    this->info_.state_ = ST_CANCEL;       // set state
    this->info_.err_flags_ |= err_flags;  // add error flags
                                          // reason for CANCEL

    if (this->info_.error_ == 0)          // do not override 
    {                                     // the original error
        this->info_.error_ = error;       // set only the first error
    }

    //// consider post completion
    //// this trick allow to avoid recursive callback
    //// inside close 
    //if (ACE_BIT_DISABLED (this->info_.io_flags_, FLG_PENDING_MASK) &&
    //    ACE_BIT_DISABLED (this->info_.cb_flags_, FLG_CALLBACK_MASK))
    //{
    //    ACE_SET_BITS (this->info_.mode_flags_, MODE_AUTO_READ);
    //    this->rd_mb_.reset ();
    //    if (this->start_read_impl (this->rd_mb_, 
    //                               this->rd_mb_.space()) == 0)
    //    {
    //        // This will force read completion
    //        ACE_SET_BITS (this->info_.io_flags_, FLG_PENDING_READ);
    //    }
    //    else // TODO REMOVE LATER
    //    {
    //        ACE_ASSERT(0); 
    //    }
    //}

    this->close_impl ();
    this->cancel_timer_internal ();

    this->free_msg (this->wr_mq_);
    this->wr_mq_ = 0;

    int loglevel = this->manager_->get_log_level ();
    if (loglevel < 2)
    {
        ACE_ERROR((LM_DEBUG,
            ACE_TEXT ("(%t)%T %s: wr_mq_=0 (ch=%d)\n"),
            __FUNCTION__,
            this->get_id () ));
    }

    return this->info_.state_;
}

AsynchChannel::State
AsynchChannel::check_closure (bool flg_callback, RefCountGuard& guard)
{
    switch (this->info_.state_)
    {
    case ST_INIT:
    case ST_ACTIVE:
    case ST_CLOSED:
         return this->info_.state_;

    case ST_CANCEL:
        if (ACE_BIT_ENABLED (this->info_.io_flags_, FLG_PENDING_MASK) ||
            ACE_BIT_ENABLED (this->info_.cb_flags_, FLG_CALLBACK_MASK) ||
            this->has_specific_events ())
        {
            return this->info_.state_;
        }
        break;

    default:
        ACE_ASSERT (0);  // should never be
    }

    ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_CLOSE);

    ACE_ASSERT (this->wr_mq_ == 0);

    Protocol *tmp = this->protocol_;
    this->protocol_ = 0;
    if (tmp != 0 && flg_callback)
    {
        RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
        try
        {
            tmp->on_channel_closed (this);
        }
        catch (...)
        {
            ACE_ERROR((LM_ERROR,
                ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::on_channel_closed()\n"),
                      this->is_server () ? 'S' : 'C',
                      this->get_id () ));
        }

    }

    this->mb_cache_.clear ();
    this->mb_cache_.set_parent (0);

    this->info_.state_ = ST_CLOSED;
    ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_CLOSE);
    
    return this->info_.state_;
}

void 
AsynchChannel::check_activity (void)
{
    RefCountPtr tmp (0);

    RefCountGuard guard (*this);

    if (this->info_.state_ != ST_ACTIVE ||
        ACE_BIT_ENABLED (this->info_.cb_flags_, FLG_CALLBACK_MASK))
    {
        return;
    }

    int rc = -1;

    ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_CHECK);
    if (this->protocol_ != 0)
    {
        RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
         
        try
        {
            rc  = this->protocol_->check_activity (this, 
                                                   this->info_.last_op_time_ );
        }
        catch (...)
        {
            ACE_ERROR((LM_ERROR,
                ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::check_activity()\n"),
                    this->is_server () ? 'S' : 'C',
                    this->get_id () ));
        }
    }
    
    if (rc < 0)
    {
        this->initiate_close (ERR_TIMEOUT, 0);
    }
    else
    {
        start_read_internal ();
    }

    ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_CHECK);
    
    if (this->check_closure (true, guard) == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
}

void
AsynchChannel::handle_time_out (const ACE_Time_Value&  interval,
                                const void            *arg)
{
    ACE_UNUSED_ARG (interval);
    RefCountPtr tmp (0);

    RefCountGuard guard (*this);

    this->info_.timer_id_ = -1;
    ACE_CLR_BITS (this->info_.io_flags_, FLG_PENDING_TIMER);
    ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_TIMER);

    int rc = -1;
    if (this->info_.state_ == ST_ACTIVE &&
        this->protocol_ != 0)
    {
        RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
        
        try
        {
            rc = this->protocol_->on_timeout (this, arg);
        }
        catch (...)
        {
            ACE_ERROR((LM_ERROR,
                ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::::on_timeout()()\n"),
                    this->is_server () ? 'S' : 'C',
                    this->get_id () ));
        }
    }
    
    if (rc < 0)
    {
        this->initiate_close (ERR_TIMEOUT, 0);
    }
    else
    {
        start_read_internal ();
    }

    ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_TIMER);
    
    if (this->check_closure (true, guard) == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
}

int  
AsynchChannel::cancel_timer ()
{
    RefCountGuard guard (*this);
    return this->cancel_timer_internal();
}

int  
AsynchChannel::cancel_timer_internal ()
{
    if (ACE_BIT_DISABLED(this->info_.io_flags_, FLG_PENDING_TIMER))
    {
        return 0;
    }

    TRB_Proactor * proactor = this->proactor ();
    int rc = proactor->cancel_timer (this->info_.timer_id_);
    if (rc != 0)   // 1  success cancellation, 0 timer was not found
    {
        ACE_CLR_BITS (this->info_.io_flags_, FLG_PENDING_TIMER);
        this->info_.timer_id_ = -1;
        return 0;
    }

    // will get timer calback later
    return -1;
}

long  
AsynchChannel::start_timer  (const ACE_Time_Value&  interval,
                             const void            *act)
{
    RefCountGuard guard (*this);

    if (this->info_.state_ != ST_ACTIVE)
    {
        return -1;
    }

    if (ACE_BIT_ENABLED(this->info_.io_flags_, FLG_PENDING_TIMER))
    {
        return -1;
    }

    
    TRB_Proactor * proactor = this->proactor ();
    
    this->info_.timer_id_ = proactor->schedule_timer (*this, 
                                                      act,
                                                      interval);

    if (this->info_.timer_id_ != -1)
    {
        ACE_SET_BITS (this->info_.io_flags_, FLG_PENDING_TIMER);
    }

    return this->info_.timer_id_;
}

int
AsynchChannel::start_write (const iovec *iov, int iov_cnt)
{
    ACE_ASSERT(iov != 0 && iov_cnt > 0);

    RefCountGuard guard (*this);

    if (this->info_.state_ != ST_ACTIVE)
    {
        return -1;
    }

    if (!this->build_write_chain (iov, iov_cnt))
    {
        this->initiate_close (ERR_ALLOC, 0);
        return -1;
    }

    if (ACE_BIT_ENABLED(this->info_.io_flags_, FLG_PENDING_WRITE))
    {
        // pending write
        return 0;
    }
    size_t length = 0;
    ACE_Message_Block *first = this->get_write_chain (length);
    return this->start_write_internal (*first, length);
}

int
AsynchChannel::start_write (const char *data, size_t datalen)
{
    iovec iov;
    iov.iov_base = (char *) data;
    iov.iov_len  = datalen;
    return this->start_write (&iov, 1);
}

int
AsynchChannel::start_write (ACE_Message_Block& mb)
{
    RefCountGuard guard (*this);
    int loglevel = this->manager_->get_log_level ();

    if (this->info_.state_ != ST_ACTIVE)
    {
        if (loglevel < 2)
        {
          ACE_ERROR((LM_INFO,
            ACE_TEXT ("(%t)%T %s. Channel is NOT ACTIVE already(ch=%d st=%d sz=%d)\n"),
            __FUNCTION__,
            this->get_id (),
            this->info_.state_,
            mb.length()));
        }

        this->free_msg (&mb);
        return -1;
    }

    unsigned int qlen = 0;
    unsigned int qlen_in_bytes = 0;
    ACE_Message_Block *last = this->get_last_wr_mb (qlen, qlen_in_bytes);
    if (last != 0)
    {
        // enqueue message block
        last->cont (&mb);
        if (loglevel < 2)
        {
            ACE_ERROR((LM_DEBUG,
                ACE_TEXT ("(%t)%T ENqueue mb(ch=%d sz=%d qlen=%d)\n"),
                this->get_id (),
                mb.length(),
                qlen));
        }
        return 0;
    }

    // here we are if last is 0 
    if (ACE_BIT_ENABLED(this->info_.io_flags_, FLG_PENDING_WRITE))
    {
        // pending write, enqueue message block
        this->wr_mq_ = &mb;
        if (loglevel < 2)
        {
            ACE_ERROR((LM_DEBUG,
                ACE_TEXT ("(%t)%T new out queue(ch=%d sz=%d)\n"),
                this->get_id (),
                mb.length()));
        }
        return 0;
    }
   
    size_t length = mb.total_length ();
    return this->start_write_internal (mb, length);
}

int
AsynchChannel::start_write (ACE_Message_Block& mb, 
                            unsigned int& qlen, unsigned int& qlen_in_bytes)
{
  RefCountGuard guard (*this);
  int loglevel = this->manager_->get_log_level ();

  if (this->info_.state_ != ST_ACTIVE)
  {
    if (loglevel < 2)
    {
      ACE_ERROR((LM_INFO,
        ACE_TEXT ("(%t)%T %s. Channel is NOT ACTIVE already(ch=%d st=%d sz=%d)\n"),
        __FUNCTION__,
        this->get_id (),
        this->info_.state_,
        mb.length()));
    }

    this->free_msg (&mb);
    return -1;
  }

  size_t mb_total_length = mb.total_length ();
  ACE_Message_Block *last = this->get_last_wr_mb (qlen, qlen_in_bytes);
  if (last != 0)
  {
    // enqueue message block
    last->cont (&mb);
    ++qlen;
    qlen_in_bytes += mb_total_length;

    if (loglevel < 2)
    {
      ACE_ERROR((LM_DEBUG,
        ACE_TEXT ("(%t)%T ENqueue mb(ch=%d sz=%d qlen=%d)\n"),
        this->get_id (),
        mb.length(),
        qlen));
    }
    return 0;
  }

  // here we are if last is 0 
  if (ACE_BIT_ENABLED(this->info_.io_flags_, FLG_PENDING_WRITE))
  {
    // pending write, enqueue message block
    this->wr_mq_ = &mb;
    qlen = 1;
    qlen_in_bytes = mb_total_length;

    if (loglevel < 2)
    {
      ACE_ERROR((LM_DEBUG,
        ACE_TEXT ("(%t)%T new out queue(ch=%d sz=%d)\n"),
        this->get_id (),
        mb.length()));
    }
    return 0;
  }

  qlen = 0;
  qlen_in_bytes = 0;
  return this->start_write_internal (mb, mb_total_length);
}

int
AsynchChannel::start_write_internal (ACE_Message_Block& mb, size_t length)
{
    ACE_ASSERT (ACE_BIT_DISABLED (this->info_.io_flags_, FLG_PENDING_WRITE));

    if (this->info_.state_ != ST_ACTIVE)
    {
        this->free_msg (&mb);
        return -1;
    }

    int loglevel = this->manager_->get_log_level ();
    if (loglevel < 2)
    {
        ACE_ERROR((LM_DEBUG,
            ACE_TEXT ("(%t)%T %s(ch=%d sz=%d)\n"),
            __FUNCTION__,
            this->get_id (),
            length));
    }

    int rc = this->start_write_impl (mb, length);
        
    if (rc == -1)
    {
        this->free_msg (&mb);
        this->initiate_close (ERR_WRITE, 0);
        return -1;
    }

    ++this->info_.total_w_;
    ACE_SET_BITS (this->info_.io_flags_, FLG_PENDING_WRITE);

    return 0;
}

int
AsynchChannel::enable_write_notifications ()
{
    RefCountGuard guard (*this);
    ACE_SET_BITS (this->info_.mode_flags_, MODE_NOTIFY_WRITE);
    return 0;
}

int
AsynchChannel::disable_write_notifications ()
{
    RefCountGuard guard (*this);
    ACE_CLR_BITS (this->info_.mode_flags_, MODE_NOTIFY_WRITE);
    return 0;
}

int
AsynchChannel::disable_read ()
{
    RefCountGuard guard (*this);
    ACE_CLR_BITS (this->info_.mode_flags_, MODE_AUTO_READ);
    return 0;
}

int
AsynchChannel::enable_read ()
{
    RefCountGuard guard (*this);

    ACE_SET_BITS (this->info_.mode_flags_, MODE_AUTO_READ);

    if (ACE_BIT_ENABLED (this->info_.cb_flags_, FLG_CALLBACK_MASK))
    {
        return 0; // already started or will be started later
    }

    return this->start_read_internal ();
}

int
AsynchChannel::set_duplex_mode(bool full_duplex)
{
    RefCountGuard guard (*this);
    if (full_duplex)
    {
        ACE_CLR_BITS (this->info_.mode_flags_, MODE_HALF_DUPLEX);
    }
    else
    {
        ACE_SET_BITS (this->info_.mode_flags_, MODE_HALF_DUPLEX);
    }
    return this->start_read_internal ();
}
    

int
AsynchChannel::start_read_internal ()
{
    if (this->info_.state_ != ST_ACTIVE)
    {
        return -1;
    }

    if (ACE_BIT_DISABLED (this->info_.mode_flags_, MODE_AUTO_READ))
    {
        return 0;
    }

    if (ACE_BIT_ENABLED (this->info_.io_flags_, FLG_PENDING_READ))
    {
        return 0;
    }

    if (ACE_BIT_ENABLED (this->info_.mode_flags_, MODE_HALF_DUPLEX))
    {
        if (ACE_BIT_ENABLED (this->info_.io_flags_, FLG_PENDING_WRITE) ||
            this->wr_mq_ != 0)
        {
            return 0;
        }
    }
 

    this->rd_mb_.crunch ();
    if (this->rd_mb_.size () < this->info_.read_size_)
    {
        if (this->rd_mb_.size (this->info_.read_size_) != 0)
        {
            this->initiate_close (ERR_ALLOC, 0);
            return -1;
        }
    }

    if (this->start_read_impl (this->rd_mb_, 
                               this->rd_mb_.space()) == -1)
    {
        this->initiate_close (ERR_READ, 0);
        return -1;
    }

    ++this->info_.total_r_;
    ACE_SET_BITS (this->info_.io_flags_, FLG_PENDING_READ);
    return 0;
}

void
AsynchChannel::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
    this->trace_read_completion (result);

    RefCountPtr tmp(0);
    ACE_Message_Block & mb = result.message_block ();
    int              error = result.error();
    size_t      xfer_bytes = result.bytes_transferred ();

    RefCountGuard guard (*this);

    ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_READ);
 
    this->update_last_time();
    this->info_.total_rcv_ += xfer_bytes;

    if (error != 0)
    {
        this->initiate_close (ERR_READ, error);
    }
    else if (xfer_bytes == 0)
    {
        this->initiate_close (ERR_EOF, 0);
    }
    else if (this->info_.state_ == ST_ACTIVE)
    {
        int rc = -1;
        if (this->protocol_ != 0)
        {
            RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
            try
            {
                rc = this->protocol_->on_read_completed (this,
                                                         mb.rd_ptr(), 
                                                         mb.length());
            }
            catch (...)
            {
                ACE_ERROR((LM_ERROR,
                    ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::::on_read_completed()()\n"),
                        this->is_server () ? 'S' : 'C',
                        this->get_id () ));
            }
        }
        if (rc < 0)
        {
            this->initiate_close (ERR_PROTOCOL, 0);
        }
        else
        {
            ACE_ASSERT ((size_t) rc <= mb.length());
            mb.rd_ptr (rc);
        }
    }

    ACE_CLR_BITS (this->info_.io_flags_, FLG_PENDING_READ);

    start_read_internal ();
    
    ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_READ);

    if (this->check_closure (true, guard) == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
}

void
AsynchChannel::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
    this->trace_write_completion (result);

    RefCountPtr tmp(0);

    ACE_Message_Block  *mb = result.get_message_block_ptr ();
    int                 error = result.error();
    size_t              xfer_bytes = result.bytes_transferred ();
    size_t              req_bytes = result.bytes_to_write ();

    RefCountGuard guard (*this);

    this->update_last_time();

    ACE_CLR_BITS (this->info_.io_flags_, FLG_PENDING_WRITE);
    ACE_SET_BITS (this->info_.cb_flags_, FLG_CALLBACK_WRITE);
        
    this->info_.total_snd_ += xfer_bytes;

    if (error != 0)
    {
        this->free_msg (mb);
        this->initiate_close (ERR_WRITE, error);
    }
    else if (xfer_bytes < req_bytes)      // Process partial write
    {
        while (mb->length() == 0)
        {
          ACE_Message_Block *tmp= mb;
          mb = mb->cont ();
          tmp->cont (0);
          free_msg (tmp);
          ACE_ASSERT (mb != 0);
        }
        this->start_write_internal (*mb,   // continue write
                                    req_bytes - xfer_bytes );  
    }
    else // success
    {
        this->free_msg (mb);
        ACE_Message_Block *first = this->get_write_chain (req_bytes);
        if (first != 0)                   //  Process ouput queue
        {
            this->start_write_internal (*first, // continue write
                                        req_bytes);
        }
        else if (this->info_.state_ == ST_ACTIVE  &&
                 ACE_BIT_ENABLED (this->info_.mode_flags_, MODE_NOTIFY_WRITE) &&
                 this->protocol_ != 0)
        {
            int rc = -1;
            RefCountSaveGuard anti_guard (guard, RefCountSaveGuard::RELEASE);
            try
            {
                rc = this->protocol_->on_write_completed (this);
            }
            catch (...)
            {
                ACE_ERROR((LM_ERROR,
                    ACE_TEXT ("(%t) channel id=(%c)%d : exception in Protocol::::on_write_completed()()\n"),
                        this->is_server () ? 'S' : 'C',
                        this->get_id () ));
            }

            if (rc < 0)
            {
                this->initiate_close (ERR_PROTOCOL, 0);
            }
        }
    }

    start_read_internal ();
   
    ACE_CLR_BITS (this->info_.cb_flags_, FLG_CALLBACK_WRITE);

    if (this->check_closure (true, guard) == ST_CLOSED)
    {
        tmp.swap (this->self_);    
    }
}

void
AsynchChannel::trace_read_completion (const TRB_Asynch_Read_Stream::Result &result)
{
    int loglevel = this->manager_->get_log_level ();
    
    size_t xfer_bytes = result.bytes_transferred();
    u_long error      = result.error ();

    if (loglevel == 0)
    {
        LogGuard log_lock;

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)%T **** channel id=(%c)%d handle_read_stream() ****\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_to_read = %d\n"),
            (int) result.bytes_to_read ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("handle = %d\n"),
            (int) result.handle ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_transfered = %d\n"),
            (int) xfer_bytes));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("error = %d\n"),
            (int) error));

        trace_buffers (result.get_buffer_info (), xfer_bytes, true);
    }
    else if (error != 0 )
    {
        LogGuard log_lock;

        ACE_Log_Msg::instance ()->errnum (error);
        ACE_OS::last_error (error);
        ACE_Log_Msg::instance ()->log (LM_ERROR,
            ACE_TEXT ("(%t)%T channel id=(%c)%d error=%d %p\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id (),
            (int) error,
            ACE_TEXT ("Read Error"));
    }
    else if (loglevel == 1)
    {
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)%T channel read OK(id=(%c)%d bytes=%d)\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id (),
            (int) xfer_bytes));
    }
}

void
AsynchChannel::trace_write_completion (const TRB_Asynch_Write_Stream::Result &result)
{
    int loglevel = this->manager_->get_log_level ();

    size_t xfer_bytes = result.bytes_transferred();
    u_long error      = result.error ();

    if (loglevel == 0)
    {
        LogGuard log_lock;

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)%T **** channel id=(%c)%d handle_write_stream() ****\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_to_write = %d\n"),
            (int) result.bytes_to_write ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("handle = %d\n"),
            (int) result.handle ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_transfered = %d\n"),
            (int) xfer_bytes));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("error = %d\n"),
            (int) error));

        trace_buffers (result.get_buffer_info (), xfer_bytes, false);
    }
    else if (error != 0 )
    {
        LogGuard log_lock;
        int error = (int) result.error ();

        ACE_Log_Msg::instance ()->errnum (error);
        ACE_OS::last_error (error);
        ACE_Log_Msg::instance ()->log (LM_ERROR,
            ACE_TEXT ("(%t)%T channel id=(%c)%d error=%d %p\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id (),
            (int) error,
            ACE_TEXT ("Write Error"));
    }
    else if (loglevel == 1)
    {
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)%T channel write OK(id=(%c)%d bytes=%d)\n"),
            this->is_server () ? 'S' : 'C',
            this->get_id (),
            (int) xfer_bytes));
    }
}

void
AsynchChannel::trace_buffers(const Buffer_Info& buf_info,
                             size_t xfer_bytes,
                             bool   flg_read)
{
  int   iovcnt = buf_info.get_iov_count ();
  if (iovcnt < 0)   // ACE_Message_Block
    {
      ACE_Message_Block * mb = buf_info.get_message_block_ptr();

      for (int i=0; 
            xfer_bytes != 0 && mb != 0 ;
            mb = mb->cont (), ++i)
      {
        char * ptr = flg_read ? mb->wr_ptr () : mb->rd_ptr ();
        size_t len = flg_read ? mb->length () : (ptr - mb->base ());
        if (len > xfer_bytes)
            len = xfer_bytes;

        ptr -= len;
        xfer_bytes -=len;

        ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("buffer is message_block[%d] transferred=%d:\n"), i, (int)len));

        ACE_HEX_DUMP ((LM_DEBUG, ptr, len));
      }
    }
  else if (iovcnt > 0) // iovec 
    {
      iovec *iov = buf_info.get_iov ();
      for (int i=0; xfer_bytes != 0 && i < iovcnt; ++i)
      {
        char * ptr = (char*) iov[i].iov_base;
        size_t len = iov[i].iov_len;
        if (len > xfer_bytes)
            len = xfer_bytes;

        ptr -= len;
        xfer_bytes -=len;

        ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("buffer is iov[%d] transferred=%d:\n"), i, (int)len));

        ACE_HEX_DUMP ((LM_DEBUG, ptr, len));
      }
    }
  else // simple  buffer
    {
      char *ptr = buf_info.get_buffer ();
      ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("buffer is raw transferred=%d:\n"), (int)xfer_bytes));

      ACE_HEX_DUMP ((LM_DEBUG, ptr, xfer_bytes));
    }
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("**** end of buffers ****************\n")));
}

// ************************************************************
//  helper private functions
// ************************************************************

ACE_Message_Block *
AsynchChannel::get_write_chain(size_t& length)
{
    ACE_Message_Block *ret  = this->wr_mq_;
    ACE_Message_Block *cur = ret;
    ACE_Message_Block *prev = 0;

    int loglevel = this->manager_->get_log_level ();

    length = 0;
    
    int num_max = ACE_IOV_MAX;
    //if (num_max > 64)
    //{
    //   num_max = 64;
    //}
  
    for (int i = 0; i < num_max; ++i)
    {
        if (cur == 0)
        {
            this->wr_mq_ = 0;
            if (loglevel < 2)
            {
                ACE_ERROR((LM_DEBUG,
                  ACE_TEXT ("(%t)%T %s: wr_mq_=0 (ch=%d num=%d len=%d)\n"),
                  __FUNCTION__,
                  this->get_id (),
                  i,
                  length));
            }
            return ret;
        }
        prev = cur;
        length += prev->length ();
        cur = cur->cont ();
    }

    this->wr_mq_ = cur;

    if (loglevel < 2)
    {
        ACE_ERROR((LM_DEBUG,
            ACE_TEXT ("(%t)%T %s: wr_mq_=cur (ch=%d num=%d len=%d)\n"),
            __FUNCTION__,
            this->get_id (),
            num_max,
            length));
    }

    prev->cont (0);
    return ret;
}

bool
AsynchChannel::build_write_chain (const iovec *iov, int iov_cnt)
{
    ACE_ASSERT(iov != 0 && iov_cnt > 0);

    int         i = 0;
    const char *data    = (const char *) iov[i].iov_base;
    size_t      datalen = iov[i].iov_len;

    unsigned int qlen = 0;
    unsigned int qlen_in_bytes = 0;
    ACE_Message_Block *mb  = this->get_last_wr_mb (qlen, qlen_in_bytes);
    ACE_Message_Block *tmp = 0; 

    if (mb == 0 ||
        ACE_BIT_ENABLED (mb->flags (),
                         MessageBlockFactory::FLG_MB_SHARED))
    {
        tmp = this->alloc_msg(DEFAULT_WRITE_SIZE);
        if (tmp == 0)
        {
            return false;
        }

        if (mb == 0)
        {
            this->wr_mq_ = tmp;
        }
        else
        {
            mb->cont (tmp);
        }
        mb = tmp;
    }

    while (1)
    {
        size_t space = mb->space ();

        if (space >= datalen)
        {
            mb->copy (data, datalen);
            if (++i >= iov_cnt)
            {
                break;
            }
            data =  (const char *) iov[i].iov_base;
            datalen = iov[i].iov_len;
        }
        else
        {
            mb->copy (data, space);
            data    += space;
            datalen -= space;

            tmp = this->alloc_msg(DEFAULT_WRITE_SIZE);
            if (tmp == 0)
            {
                return false;
            }

            mb->cont (tmp);
            mb = tmp;
        }
    }
    return true;
}
    
ACE_Message_Block *
AsynchChannel::get_last_wr_mb (unsigned int& qlen, unsigned int& qlen_in_bytes)
{
    qlen = 0;
    qlen_in_bytes = 0;
    ACE_Message_Block *last = this->wr_mq_;
    if (last != 0)
    {
        qlen = 1;
        qlen_in_bytes = last->length();

        while (last->cont () != 0)
        {
            last = last->cont ();
            ++qlen;
            qlen_in_bytes += last->length();
        }
    }
    return last;
}

}  //namespace Terabit 

