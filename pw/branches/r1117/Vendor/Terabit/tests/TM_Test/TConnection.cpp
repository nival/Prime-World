#include "TConnectionManager.h"
#include "TP_ReactorTask.h"

#include "ace/Auto_IncDec_T.h"

template class ACE_Auto_IncDec<int>;
typedef ACE_Auto_IncDec<int> IntGuard;


// ***********************************************************
//   TConnection
// ***********************************************************

TConnection::TConnection ()
: mtx_           ()
, factory_       (0)
, mgr_           (0)
, index_         ((size_t)-1)
, reactor_mask_  (ACE_Event_Handler::NULL_MASK)
, ready_mask_    (ACE_Event_Handler::NULL_MASK)
, total_snd_     (0)
, total_rcv_     (0)
, total_w_       (0)
, total_r_       (0)
, flg_stop_      (false)
, last_op_time_  (ACE_OS::gettimeofday ())
, timeout_       (ACE_Time_Value::zero)
, mq_recv_       ((size_t) -1, (size_t) -1)
, mq_send_       ((size_t) -1, (size_t) -1)
, in_count_      (0)
, out_count_     (0)
{
}

TConnection::~TConnection ()
{
    ACE_ASSERT (mgr_ == 0);
}

TP_ReactorTask &
TConnection::task (void) const 
{
    return this->manager()->task();
}

TestCfg &
TConnection::config (void) const 
{
    return this->task().config();
}

void
TConnection::setup (TConnectionFactory * factory,
                    TConnectionManager * mgr,
                    int index)
{
  //ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);
  this->factory_ = factory;
  this->mgr_     = mgr;
  this->index_   = index;
}

ACE_Message_Block *
TConnection::alloc_msg ()
{
  ACE_GUARD_RETURN (TMutex, guard, mtx_, 0);

  ACE_Time_Value tv = ACE_Time_Value::zero;

  ACE_Message_Block * mb = 0;

  if (this->getq(mb, &tv) >= 0)
  {
      mb->reset();
      return mb;
  }

  if (ACE_OS::last_error () != EWOULDBLOCK)
    return mb;

  u_int blksize = this->config().r_blksize();

  ACE_NEW_NORETURN (mb, ACE_Message_Block (blksize));

  return mb;
}

void
TConnection::free_msg (ACE_Message_Block * mb)
{
  ACE_GUARD (TMutex, guard, mtx_);
  if (mb == 0)
    return;

  ACE_Time_Value tv = ACE_Time_Value::zero;

  if(this->putq (mb, &tv) >= 0)
    return;

  ACE_Message_Block::release(mb);
  return;
}

int
TConnection::initiate_io (ACE_Reactor_Mask mask)
{
    if (this->should_stop())
    {
        mask |= ( ACE_Event_Handler::READ_MASK
                | ACE_Event_Handler::WRITE_MASK );
    }

    if (ACE_BIT_CMP_MASK (reactor_mask_, mask, mask))
    {
        return 0;
    }

    //if (this->reactor()->schedule_wakeup  (this, mask) == -1)
    if (this->reactor()->register_handler  (this, mask) == -1)
    {
        return -1;
    }

    //ACE_CLR_BITS (ready_mask_,   mask);
    ACE_SET_BITS (reactor_mask_, mask);
    return 0;
}


ACE_Reactor_Mask 
TConnection::get_request_mask () 
{
    ACE_Reactor_Mask mask  = ACE_Event_Handler::NULL_MASK;

    if (!mq_recv_.is_empty ())
    {
        mask |= ACE_Event_Handler::READ_MASK;
    }

    if (!mq_send_.is_empty ())
    {
        mask |= ACE_Event_Handler::WRITE_MASK;
    }
        
    return mask;
}
    

int 
TConnection::stop ()
{
    {
        ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);
        this->flg_stop_ = true;
        this->peer().close_reader ();
        this->peer().close_writer ();
    }

    return 0;
}

void 
TConnection::check (void)
{
  if (this->timeout_ == ACE_Time_Value::zero)
    return;

  ACE_Time_Value diff_time = ACE_OS::gettimeofday () - this->last_op_time_;

  if (diff_time < this->timeout_)
    return;

  this->stop();
}

int
TConnection::open (void *)
{
    ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

    ACE_ASSERT (this->mgr_ != 0);

    reactor_mask_ = ACE_Event_Handler::NULL_MASK ;
    ready_mask_   = ACE_Event_Handler::NULL_MASK;

    ACE_Reactor * reactor = this->task().tp_reactor();
    this->reactor (reactor);

    int rc = 0;
    {
        TReverseMutex  anti_mtx_(mtx_);
        ACE_GUARD_RETURN (TReverseMutex, guard, anti_mtx_, -1);
        rc = this->on_open ();
    }

    if (rc < 0)
    {
        return -1;
    }

    ACE_Reactor_Mask  request_mask = get_request_mask ();
    
    rc = initiate_io (request_mask);
    return rc;
}

int
TConnection::handle_close (ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    {
        
        ACE_ASSERT (in_count_ == 0);
        ACE_ASSERT (out_count_ == 0);

        ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

        ACE_CLR_BITS(reactor_mask_, mask);

        if (reactor_mask_ != ACE_Event_Handler::NULL_MASK)
        {
            return 0;
        }

        // Remove from reactor  and close peer
        BaseClass::shutdown ();
        this->reactor (0);
    }

    if (this->mgr_ != 0)
    {
        mgr_->destroy_connection (this);
        return 0;
    }

    // this->destroy ();
    // return 0;
    return BaseClass::handle_close (handle, mask);
}

int
TConnection::handle_input (ACE_HANDLE h)
{
   
    ACE_ASSERT (in_count_ == 0);
    ACE_ASSERT (out_count_ == 0);
    IntGuard g(in_count_);
  
    ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

    ready_mask_ |= ACE_Event_Handler::READ_MASK;

    if (!process_events ())
    {
        return -1;
    }

    ACE_Reactor_Mask  request_mask = get_request_mask ();
    
    if (initiate_io (request_mask) < 0)
    {
        return -1;
    }

    if (ACE_BIT_ENABLED(request_mask, ACE_Event_Handler::READ_MASK))
    {
        return 0;
    }
    
    return -1;
}

int
TConnection::handle_output (ACE_HANDLE h)
{

    ACE_ASSERT (in_count_ == 0);
    ACE_ASSERT (out_count_ == 0);
    IntGuard g(out_count_);

    ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

    ready_mask_ |= ACE_Event_Handler::WRITE_MASK;

    if (!process_events ())
    {
        return -1;
    }

    ACE_Reactor_Mask  request_mask = get_request_mask ();
    
    if (initiate_io (request_mask) < 0)
    {
        return -1;
    }

    if (ACE_BIT_ENABLED(request_mask, ACE_Event_Handler::WRITE_MASK))
    {
        return 0;
    }
    
    return -1;
}


bool
TConnection::process_events ( )
{
    bool flg_continue = false;

    do
    {
        if (should_stop())
        {
            return false;
        }

        flg_continue = false;
        ACE_Reactor_Mask  request_mask = get_request_mask ();
        
        if (ACE_BIT_ENABLED(request_mask, ACE_Event_Handler::READ_MASK) && 
            ACE_BIT_ENABLED(ready_mask_, ACE_Event_Handler::READ_MASK) )
        {
            flg_continue = true;
            if (do_read () < 0)
            {
                return false;
            }
        }

        if (ACE_BIT_ENABLED(request_mask,ACE_Event_Handler::WRITE_MASK) && 
            ACE_BIT_ENABLED(ready_mask_,ACE_Event_Handler::WRITE_MASK) )
        {
            flg_continue = true;
            if (do_write()< 0)
            {
                return false;
            }
        }

    }while (flg_continue);

    return true;
}

int 
TConnection::do_read ()
{
    ACE_Time_Value tv = ACE_Time_Value::zero;
    ACE_Message_Block * mb = 0;

    this->mq_recv_.dequeue_head(mb, &tv);
    if (mb == 0)
    {
        return -1;
    }

    int xfer_bytes = 0;
    int req_bytes = mb->space();
    int error = 0;

    int rc = this->peer ().recv (mb->wr_ptr(), req_bytes);

    if (rc >= 0)
    {
        xfer_bytes = rc;
        mb->wr_ptr (rc);
    }
    else
    {
        error = ACE_OS::last_error ();
        if (error == EWOULDBLOCK)
        {
            this->mq_recv_.enqueue_head (mb, &tv);
            ACE_CLR_BITS (ready_mask_ ,ACE_Event_Handler::READ_MASK);
            return 0;
        }
    }

    ++total_r_;
    total_rcv_ += xfer_bytes;

    trace_read (*mb, req_bytes, xfer_bytes, error);

    if (rc < 0)
    {
        return -1;
    }
    
    //if (rc >= 0)
    {
        TReverseMutex  anti_mtx_(mtx_);
        ACE_GUARD_RETURN (TReverseMutex, guard, anti_mtx_, -1);
        rc = on_read_finished (*mb, error, xfer_bytes);
    }

    if (rc < 0 || xfer_bytes == 0)
    {
        return -1;
    }
    return 1;
}

int 
TConnection::do_write ()
{
    ACE_Time_Value tv = ACE_Time_Value::zero;
    ACE_Message_Block * mb = 0;

    this->mq_send_.dequeue_head(mb, &tv);
    if (mb == 0)
    {
        return -1;
    }

    int xfer_bytes = 0;
    int error = 0;
    int req_bytes = mb->length();

    int rc = this->peer ().send (mb->rd_ptr(), req_bytes);
   
    if (rc >= 0)
    {
        xfer_bytes += rc;
        mb->rd_ptr (rc);
    }
    else
    {
        error = ACE_OS::last_error ();
        if (error == EWOULDBLOCK)
        {
            this->mq_send_.enqueue_head (mb, &tv);
            ACE_CLR_BITS (ready_mask_ ,ACE_Event_Handler::WRITE_MASK);
            return 0;
        }
    }

    ++total_w_;
    total_snd_ += xfer_bytes;

    trace_write (*mb, req_bytes, xfer_bytes, error);
    
    if (rc < 0)
    {
        return -1;
    }

    //if (rc >= 0)
    {
        if (mb->length () != 0)
        {
            this->mq_send_.enqueue_head (mb, &tv);
            ACE_CLR_BITS (ready_mask_ ,ACE_Event_Handler::WRITE_MASK);
            return 0;
        }

        TReverseMutex  anti_mtx_(mtx_);
        ACE_GUARD_RETURN (TReverseMutex, guard, anti_mtx_, -1);
        rc = on_write_finished (*mb,error);
    }

    if (rc < 0)
    {
        return -1;
    }

    return 1;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
int 
TConnection::start_read (ACE_Message_Block & mb)
{
    ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

    ACE_Time_Value tv = ACE_Time_Value::zero;
    int rc = this->mq_recv_.enqueue_tail (&mb, &tv);
    if (rc < 0)
    {
        return -1;
    }
    return 0;
}

int 
TConnection::start_write (ACE_Message_Block & mb)
{
    ACE_GUARD_RETURN (TMutex, guard, mtx_, -1);

    ACE_Time_Value tv = ACE_Time_Value::zero;
    int rc = this->mq_send_.enqueue_tail (&mb, &tv);
    if (rc < 0)
    {
        return -1;
    }
    return 0;
}

//--------------------------------------------------------------------
// Tracing
//--------------------------------------------------------------------
void
TConnection::trace_read (ACE_Message_Block & mb,
                      int  req_bytes,
                      int  xfer_bytes,
                      int  error)
{                             
  int loglevel = this->config().loglevel ();

  if (loglevel == 0)
  {
      LogLocker log_lock;

      if (xfer_bytes < 0)
      {
          xfer_bytes = 0;
      }

      char * last  = mb.wr_ptr();
      char * first = last - xfer_bytes; 

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) **** %s=%d read finished ****\n"),
                  this->get_name(),
                  this->index()));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("bytes_to_read = %d\n"),
                  req_bytes));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("handle = %d\n"),
                  this->get_handle()));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("bytes_transfered = %d\n"),
                  xfer_bytes));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("error = %d\n"),
                  error));
    
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("message_block:\n")));

      ACE_HEX_DUMP ((LM_DEBUG, first, xfer_bytes));


      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("**** end of message ****************\n")));
  }
  else if (error != 0 )
  {
      LogLocker log_lock;

      ACE_Log_Msg::instance ()->errnum (error);
      ACE_Log_Msg::instance ()->log (LM_ERROR,
                                     ACE_TEXT ("(%t) %s=%d READ %p\n"),
                                     this->get_name (),
                                     this->index (),
                                     ACE_TEXT ("ERROR"));
  }
  else if ( loglevel ==1 )
  {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) %s=%d read=%d bytes OK\n"),
                  this->get_name (),
                  this->index (),
                  xfer_bytes));
  }

  return;
}

void
TConnection::trace_write (ACE_Message_Block & mb,
                       int  req_bytes,
                       int  xfer_bytes,
                       int  error)
{                             
  int loglevel = this->config().loglevel ();

  if (loglevel == 0)
  {
      LogLocker log_lock;

      if (xfer_bytes < 0)
      {
          xfer_bytes = 0;
      }

      char * last  = mb.rd_ptr();
      char * first = last - xfer_bytes; 

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) **** %s=%d write finished ****\n"),
                  this->get_name(),
                  this->index()));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("bytes_to_write = %d\n"),
                  req_bytes));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("handle = %d\n"),
                  this->get_handle()));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("bytes_transfered = %d\n"),
                  xfer_bytes));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("error = %d\n"),
                  error));
    
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("message_block:\n")));

      ACE_HEX_DUMP ((LM_DEBUG, first, xfer_bytes));


      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("**** end of message ****************\n")));
  }
  else if (error != 0 )
  {
      LogLocker log_lock;

      ACE_Log_Msg::instance ()->errnum (error);
      ACE_Log_Msg::instance ()->log (LM_ERROR,
                                     ACE_TEXT ("(%t) %s=%d WRITE %p\n"),
                                     this->get_name (),
                                     this->index (),
                                     ACE_TEXT ("ERROR"));
  }
  else if ( loglevel ==1 )
  {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) %s=%d write=%d bytes OK\n"),
                  this->get_name (),
                  this->index (),
                  xfer_bytes));
  }

  return;
}

