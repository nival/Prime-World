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

// ============================================================================
/**
 *  @file Session.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"
#include "P2_Test.h"

// *************************************************************
//   Session
// *************************************************************
Session::Session (Bridge * bridge)
  : bridge_   (bridge),
    rs_       (),
    ws_       (),
    handle_   (ACE_INVALID_HANDLE),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    ref_cnt_w_(0),
    ref_cnt_r_(0),
    flags_    (0)
{
  ACE_ASSERT (this->bridge_ != 0);
}

Session::~Session (void)
{
  this->close ();
}

void
Session::close ()
{
  if (this->handle_ != ACE_INVALID_HANDLE)
    ACE_OS::closesocket (this->handle_);

  this->handle_= ACE_INVALID_HANDLE;
}

void
Session::cancel ()
{
  this->ws_.cancel ();
  this->rs_.cancel ();

#if defined(ACE_WIN32)
  this->close();
#endif

  return;
}

int
Session::index (void) const
{
  return this->bridge ()->index ();
}

int
Session::is_open(void) const
{
  return ((this->flags_ & SSN_OPEN) != 0);
}

void
Session::addresses (const ACE_Addr& peer, const ACE_Addr& local)
{
  ACE_TCHAR str_peer [256];
  ACE_TCHAR str_local[256];

  TRB_Sock_Addr::to_string (peer, str_peer, sizeof (str_peer)/sizeof (ACE_TCHAR));
  TRB_Sock_Addr::to_string (local, str_local, sizeof (str_local)/sizeof (ACE_TCHAR));
  
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s=%d Remote=%s Local=%s\n"),
              this->get_name(),
              this->index(),
              str_peer,
              str_local));

}

void
Session::open (ACE_HANDLE handle, ACE_Message_Block & mb)
{
  ACE_UNUSED_ARG(mb);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->bridge_->mutex());

    this->open_streams (handle);
    
    if (bridge_->check_ref () != 0)
      return;
  }

  this->bridge_->try_destroy ();
}

int
Session::open_streams (ACE_HANDLE handle)
{
    this->handle_ = handle;

    if (this->handle_ == ACE_INVALID_HANDLE)
      return -1;
    
    TRB_Proactor * proactor = this->bridge ()->acceptor ().proactor();

    if (this->ws_.open (*this, 
                        this->handle_,
                        0, // completion key,
                        proactor) == -1)

      ACE_ERROR_RETURN ((LM_ERROR,
                  ACE_TEXT ("(%t) %s=%d %p\n"),
                  this->get_name(),
                  this->index(),
                  ACE_TEXT (" TRB_Asynch_Write_Stream::open")),
                  -1);

    if (this->rs_.open (*this, 
                        this->handle_,
                        0, // completion key,
                        proactor) == -1)

      ACE_ERROR_RETURN ((LM_ERROR,
                  ACE_TEXT ("(%t) %s=%d %p\n"),
                  this->get_name(),
                  this->index(),
                  ACE_TEXT (" TRB_Asynch_Read_Stream::open")),
                  -1);

    this->flags_ |= SSN_OPEN;

    return this->on_open();
}

int
Session::initiate_read_stream (void)
{
  if (this->bridge_->should_finish() ||
      (this->flags_ & SSN_RCV_CLOSED) ||
      this->handle_ == ACE_INVALID_HANDLE)
    return -1;


  ACE_Message_Block *mb = 0;

  size_t r_blksize = this->bridge_->acceptor().task().config().r_blksize();
  int loglevel = this->bridge_->acceptor().task().config().loglevel ();
  
  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (r_blksize+1),
                  -1);

  if (loglevel <= 1)
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d Initiate READ %u bytes\n"),
                    this->get_name (),
                    this->index (),
                    (u_int) r_blksize ));
      }
  // Inititiate read
  if (this->rs_.read (*mb, r_blksize) == -1)
    {
      mb->release ();
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT ("(%t) %s=%d attempt read failed\n"),
                        this->get_name(),
                        this->index()),
                        -1);
    }

  this->ref_cnt_r_++; 
  this->total_r_++;
  return 0;
}

int
Session::initiate_write_stream (ACE_Message_Block &mb, size_t nbytes)
{
  int loglevel = this->bridge_->acceptor().task().config().loglevel ();

  int mb_type = mb.msg_type ();


  if (this->bridge_->should_finish() ||
      (this->flags_ & SSN_SND_CLOSED) ||
      this->handle_ == ACE_INVALID_HANDLE)
    {
      mb.release ();
      return -1;
    }

  if (nbytes == 0 || 
      mb_type == ACE_Message_Block::MB_HANGUP ||
      mb_type == ACE_Message_Block::MB_ERROR)
    {

      ACE_OS::shutdown (this->handle_, ACE_SHUTDOWN_WRITE);
      this->flags_ |= SSN_SND_CLOSED;
      mb.release ();
      return -1;

      //this->cancel ();

      //ACE_ERROR_RETURN((LM_ERROR,
      //                  ACE_TEXT ("(%t) %s=%d attempt write 0 bytes\n"),
      //                  this->get_name(),
      //                  this->index()),
      //                  -1);
    }

  if (loglevel <= 1)
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d Initiate WRITE %u bytes\n"),
                    this->get_name (),
                    this->index (),
                    (u_int) nbytes ));
      }

  if (this->ws_.write (mb, nbytes) == -1)
    {
      mb.release ();
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT ("(%t) %s=%d attempt write failed\n"),
                        this->get_name(),
                        this->index()),
                        -1);
    }

  this->ref_cnt_w_++;
  this->total_w_++;
  return 0;
}

void
Session::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->bridge_->mutex());

    int loglevel = this->bridge_->acceptor().task().config().loglevel ();

    --this->ref_cnt_r_;

    ACE_Message_Block & mb = result.message_block ();

    // Reset pointers.
    mb.rd_ptr ()[result.bytes_transferred ()] = '\0';

    if (loglevel == 0)
      {
        LogLocker log_lock;

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_read_stream() ****\n"),
                    this->get_name(),
                    this->index()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("bytes_to_read"),
                    result.bytes_to_read ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("handle"),
                    result.handle ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("bytes_transfered"),
                    result.bytes_transferred ()));
/*
-------------------------------------------
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %@\n"),
                    ACE_TEXT ("act"),
                    result.act ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("success"),
                    result.success ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %@\n"),
                    ACE_TEXT ("completion_key"),
                    result.completion_key ()));

-------------------------------------------
*/

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("error"),
                    result.error ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %s\n"),
                    ACE_TEXT ("message_block"),
                    mb.rd_ptr ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (result.error () != 0)
      {
        LogLocker log_lock;

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d ERROR %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       ACE_TEXT ("read"));
      }
    else if ( loglevel ==1 )
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d read=%d bytes ok\n"),
                    this->get_name (),
                    this->index (),
                    result.bytes_transferred ()));
      }


    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->total_rcv_ += result.bytes_transferred ();

      }
    else
      {
        this->flags_ |= SSN_RCV_CLOSED;

        mb.msg_type (ACE_Message_Block::MB_HANGUP);
        mb.wr_ptr (mb.rd_ptr());
      }

    this->on_data_received (mb);

    if (bridge_->check_ref () != 0)
      return;
  }

  this->bridge_->try_destroy ();
}

void
Session::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->bridge_->mutex());

    int loglevel = this->bridge_->acceptor().task().config().loglevel ();

    --this->ref_cnt_w_;

    ACE_Message_Block & mb = result.message_block ();

    if (loglevel == 0)
      {
        LogLocker log_lock;

        //mb.rd_ptr () [0] = '\0';
        mb.rd_ptr (mb.rd_ptr () - result.bytes_transferred ());

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_write_stream() ****\n"),
                    this->get_name(),
                    this->index()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("bytes_to_write"),
                    result.bytes_to_write ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("handle"),
                    result.handle ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("bytes_transfered"),
                    result.bytes_transferred ()));
/*
-------------------------------------------
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %@\n"),
                    ACE_TEXT ("act"),
                    result.act ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("success"),
                    result.success ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %@\n"),
                    ACE_TEXT ("completion_key"),
                    result.completion_key ()));
-------------------------------------------
*/
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("error"),
                    result.error ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %s\n"),
                    ACE_TEXT ("message_block"),
                    mb.rd_ptr ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (result.error () != 0)
      {
        LogLocker log_lock;

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d ERROR %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       ACE_TEXT ("write"));
      }
    else if ( loglevel ==1 )
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d write=%d bytes ok\n"),
                    this->get_name (),
                    this->index (),
                    result.bytes_transferred ()));
      }


    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->total_snd_ += result.bytes_transferred ();
      }
    else
      {
        mb.msg_type (ACE_Message_Block::MB_ERROR);
        mb.wr_ptr (mb.rd_ptr());
      }

    this->on_data_sent (mb);

    if (bridge_->check_ref () != 0)
      return;
  }

  this->bridge_->try_destroy ();
}


// *********************************************************
//   Receiver
// *********************************************************

Receiver::Receiver (Bridge * bridge)
  : Session (bridge)
{
}

Receiver::~Receiver (void)
{
  if (this->get_ref_cnt () != 0)
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("(%t) %s=%d deleted with pending ")
                ACE_TEXT ("W=%d R=%d\n"),
                this->get_name (),
                this->index (),
                this->get_ref_cnt_w (),
                this->get_ref_cnt_r ()));

  this->close();
}

const ACE_TCHAR *
Receiver::get_name (void) const
{
  return ACE_TEXT("RCVR");
}

int
Receiver::on_open (void)
{
  //int num = 1+(w_size/r_blksize);
  //for (; num > 0; --num)

  //this->initiate_read_stream ();
  //return 0;

  //this->bridge ()->on_data_sent (&mb, Bridge::Q_S2R);

  this->bridge ()->on_data_received (0, Bridge::Q_R2S);

  return 0;
}

int
Receiver::on_data_received(ACE_Message_Block & mb)
{
  return this->bridge ()->on_data_received (&mb, Bridge::Q_R2S);
}

int
Receiver::on_data_sent(ACE_Message_Block & mb)
{
  return this->bridge ()->on_data_sent (&mb, Bridge::Q_S2R);
}

// *********************************************************
//   Sender
// *********************************************************

Sender::Sender (Bridge * bridge)
  : Session (bridge)
{
  ;
}

Sender::~Sender (void)
{
  if (this->get_ref_cnt () != 0)
    ACE_ERROR ((LM_WARNING,
                ACE_TEXT ("(%t) %s=%d deleted with pending ")
                ACE_TEXT ("W=%d R=%d\n"),
                this->get_name (),
                this->index (),
                this->get_ref_cnt_w (),
                this->get_ref_cnt_r ()));

  this->close();
}

const ACE_TCHAR *
Sender::get_name (void) const
{
  return ACE_TEXT("SNDR");
}

int
Sender::on_open (void)
{
  //int num = 1+(w_size/r_blksize);
  //for (; num > 0; --num)
  //this->initiate_read_stream ();

  this->bridge ()->on_data_received (0, Bridge::Q_S2R);
  this->bridge ()->on_data_sent (0, Bridge::Q_R2S);

  return 0;
}

int
Sender::on_data_received(ACE_Message_Block & mb)
{
  return this->bridge ()->on_data_received (&mb, Bridge::Q_S2R);
}

int
Sender::on_data_sent(ACE_Message_Block & mb)
{
  return this->bridge ()->on_data_sent (&mb, Bridge::Q_R2S);
}

int
Sender::connect(const ACE_Addr & addr)
{
  ACE_ASSERT(this->handle_ == ACE_INVALID_HANDLE);

  TRB_Proactor * proactor = this->bridge ()->acceptor ().proactor();

  if (this->bridge_->should_finish ())
    return -1;

  if (this->asynch_connect_.open (*this,  // handler 
                                  ACE_INVALID_HANDLE,  //handle
                                  0,  // completion key
                                  proactor) == -1)
  
      ACE_ERROR_RETURN 
        ((LM_ERROR,
          ACE_TEXT ("(%t) %s=%d %p\n"),
          this->get_name(),
          this->index(),
          ACE_TEXT (" TRB_Asynch_Connect::open")),
          -1);



  if (this->asynch_connect_.connect 
                    (ACE_INVALID_HANDLE,
                     addr,                        // remote sap
                     ACE_Addr::sap_any,           // local sap
                     1,                           // reuse addr 
                     0) != 0)                     // act
      ACE_ERROR_RETURN 
        ((LM_ERROR,
          ACE_TEXT ("(%t) %s=%d %p\n"),
          this->get_name(),
          this->index(),
          ACE_TEXT (" TRB_Asynch_Connect::open")),
          -1);

  ++this->ref_cnt_w_;

  return 0;
}


void 
Sender::handle_connect (const TRB_Asynch_Connect::Result &result)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->bridge_->mutex());

    --this->ref_cnt_w_;

    ACE_HANDLE handle = result.connect_handle();

    if (handle != ACE_INVALID_HANDLE)
      {
        ACE::clr_flags (handle, ACE_NONBLOCK);

        this->parse_address(result);
      }

    this->open_streams(handle);

    if (this->bridge_->check_ref () != 0)
      return;
  }

  this->bridge_->try_destroy ();
}

void
Sender::parse_address (const TRB_Asynch_Connect::Result &result)
{
    const ACE_Addr& remote_address = result.remote_address ();
    const ACE_Addr& local_address = result.local_address ();
    this->addresses(remote_address, local_address);
}



