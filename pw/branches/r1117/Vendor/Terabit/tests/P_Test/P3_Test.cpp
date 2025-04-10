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
 *  @file P3_Test.cpp
 *
 *  P3_Test.cpp
 *
 *  This program illustrates how the TRB_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "Cfg.h"
#include "PSession.h"

#include "ace/INET_Addr.h"
//#include "ace/Countdown_Time.h"


#include "Asynch_RW.h"

static TestCfg cfg;

static ACE_TCHAR complete_message[] =
  ACE_TEXT ("GET / HTTP/1.1\r\n")
  ACE_TEXT ("Accept: */*\r\n")
  ACE_TEXT ("Accept-Language: C++\r\n")
  ACE_TEXT ("Accept-Encoding: gzip, deflate\r\n")
  ACE_TEXT ("User-Agent: P3_Test /1.0 (non-compatible)\r\n")
  ACE_TEXT ("Connection: Keep-Alive\r\n")
  ACE_TEXT ("\r\n");


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_Acceptor<PSession>;
template class TRB_Asynch_Connector<PSession>;
template class TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;
template class TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_Acceptor<PSession>
#pragma instantiate TRB_Asynch_Connector<PSession>
#pragma instantiate TRB_Asynch_RW<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>
#pragma instantiate TRB_Asynch_RW_Stream<TRB_Asynch_Read_Stream,TRB_Asynch_Write_Stream>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


ProactorTask * pBackTask = 0;

// *************************************************************
//   Receiver 
// *************************************************************

class Receiver : public PSession
{
public:
  Receiver  (void);
  ~Receiver (void);

  // Virtual from PSession
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("Receiver");
    }

  virtual void  cancel ();
  
  virtual int   is_safe_to_delete (void) const;

  /// This is called after the new connection has been accepted.
  virtual void open (ACE_HANDLE handle,
                     ACE_Message_Block &message_block);

  /**
   * @name AIO callback handling
   *
   * These methods are called by the framework
   */
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

  /// This is called when message delivered
  virtual void handle_user_operation(const TRB_Asynch_User_Result& result);

private:
  int initiate_read_stream  (void);
  int initiate_write_stream (ACE_Message_Block &mb);
  int initiate_post_message (ACE_Message_Block &mb);
 

  Asynch_RW_Stream  stream_;
  int               ref_cnt_m_;   // Number of currently outstanding Messages
};

// ***************************************************
Receiver::Receiver ()
  : PSession   (), 
    ref_cnt_m_ (0)
{
}

Receiver::~Receiver (void)
{
}

void
Receiver::cancel ()
{
  ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex());

  this->stream_.cancel_and_close();
}

int 
Receiver::is_safe_to_delete (void) const
{
  return (ref_cnt_m_ == 0 && this->has_pending_io() == 0);
}

void
Receiver::open (ACE_HANDLE handle, ACE_Message_Block &)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    if (this->stream_.open (*this, 
                        handle,
                        0, // completion key,
                        this->task().get_proactor(this->index()),
                        1) == -1)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%t) %s %p\n"),
                  this->get_name(),
                  ACE_TEXT ("TRB_Asynch_RW_Stream::open")));

    else
      this->initiate_read_stream ();

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

int
Receiver::initiate_read_stream (void)
{
  ACE_Message_Block *mb = 0;

  if (this->get_ref_cnt_r() != 0)
     return 0;


  u_int blksize = this->config().r_blksize();
  u_int winsize = this->config().w_size();

  // flow control
  if ((u_long)(this->total_rcv_ - this->total_snd_) > winsize)
    return 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (blksize+1),
                  -1);

  // Inititiate read
  if (this->stream_.read (*mb, blksize) == -1)
    {
      mb->release ();
      this->stream_.cancel_and_close();
      return -1;
    }

  this->ref_cnt_r_++;
  this->total_r_++;
  return 0;
}

int
Receiver::initiate_write_stream (ACE_Message_Block &mb)
{
  size_t nbytes = mb.length ();

  if (nbytes == 0)
    {
      mb.release ();
      this->stream_.cancel_and_close();

      ACE_ERROR_RETURN((LM_ERROR,
         ACE_TEXT ("(%t) %s TRB_Asynch_Write_Stream::write 0 bytes\n"),
         this->get_name()),
         -1);
    }

  if (this->stream_.write (mb, nbytes) == -1)
    {
      mb.release ();
      this->stream_.cancel_and_close();
      return -1;
    }

  this->ref_cnt_w_++;
  this->total_w_++;
  return 0;
}

int
Receiver::initiate_post_message (ACE_Message_Block &mb)
{
  if (this->stream_.should_finish())
    {
      mb.release ();
      return 0;
    }

  TRB_Asynch_User_Result result (this, 
                                 ACE_INVALID_HANDLE, // handle
                                 mb,   
                                 0,  // bytes requested
                                 0,  // offset low
                                 0,  // offset high
                                 (const void*) this->index (),
                                 0,  // completion key
                                 0,  // priority
                                 0); // signal_number
  if (pBackTask->get_proactor(0)->post_completion (result) < 0 )
    {
       mb.release ();
       this->stream_.cancel_and_close();
       ACE_ERROR_RETURN((LM_ERROR,
                       ACE_TEXT ("(%t) %s=%d attempt POST failed\n"),
                       this->get_name (),
                       this->index ()),
                       -1);
    }

  this->ref_cnt_m_++;
  return 0;
}

void
Receiver::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
  this->trace_read_completion (result);

  // emulate long callback
  do_delay (cfg.delay());  // delay milliseconds

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex () );

    this->ref_cnt_r_--;

    ACE_Message_Block & mb = result.message_block ();

    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->initiate_post_message(mb);

        this->initiate_read_stream ();
      }
    else
    {
      mb.release ();
    }

    if (result.error () != 0)
      this->stream_.cancel_and_close ();

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

void
Receiver::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
  this->trace_write_completion (result);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->ref_cnt_w_--;

    ACE_Message_Block & mb = result.message_block ();
    mb.release ();

    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->initiate_read_stream ();
      }
    else
      this->stream_.cancel_and_close ();

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

void
Receiver::handle_user_operation(const TRB_Asynch_User_Result& result)
{
  ACE_Message_Block *mb =result.get_message_block_ptr ();

  ACE_ASSERT (mb != 0);
  ACE_ASSERT (this->index() == (int) result.act ());

  do_delay (this->config().delay());  // delay milliseconds

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);

    if (this->config().loglevel () == 0)
      {
        LogLocker log_lock;


        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_user_operation() ****\n"),
                    this->get_name(),
                    this->index()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("length"),
                    mb->length()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("act"),
                    (int) result.act()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %s\n"),
                    ACE_TEXT ("message_block"),
                    mb->rd_ptr ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("**** end of message ****************\n")));
      }

    this->initiate_write_stream (*mb);
    
    this->ref_cnt_m_--;

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}


// *******************************************
//   Sender
// *******************************************
class Sender : public PSession
{
public:
  Sender  (void);
  ~Sender (void);

  // Virtual from PSession
  virtual const ACE_TCHAR * get_name (void) const 
    {
       return ACE_TEXT("Sender");
    }

  virtual void  cancel ();
  
  virtual int   is_safe_to_delete (void) const;

  /// This is called after the new connection has been accepted.
  virtual void open (ACE_HANDLE handle,
                     ACE_Message_Block &message_block);

  /**
   * @name AIO callback handling
   *
   * These methods are called by the framework
   */
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);


private:
  int initiate_read_stream (void);
  int initiate_write_stream (void);

  Asynch_RW_Stream  stream_;
};

// ************************************************

Sender::Sender ()
  : PSession   ()
{
}

Sender::~Sender (void)
{
}

void
Sender::cancel ()
{
  ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());
  this->stream_.cancel_and_close();
}

int 
Sender::is_safe_to_delete (void) const
{
  return !this->has_pending_io();
}


void
Sender::open (ACE_HANDLE handle, ACE_Message_Block &)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    if (this->stream_.open (*this, 
                        handle,
                        0, // completion key,
                        this->task().get_proactor(this->index()),
                        1) == -1)

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("(%t) %s %p\n"),
                  this->get_name(),
                  ACE_TEXT ("TRB_Asynch_RW_Stream::open")));

    else
      {
        this->initiate_read_stream ();

        u_int blksize = this->config().s_blksize();
        u_int winsize = this->config().w_size();

        int num = 1+(winsize/blksize);

        for (; num > 0; --num)
          this->initiate_write_stream ();
      }

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

int
Sender::initiate_write_stream (void)
{
  u_int blksize = this->config().s_blksize();
  u_int limit   = this->config().xfer_limit();
  u_int winsize = this->config().w_size();

  if (limit != 0 && this->total_snd_ >= limit)
    return 0;

  u_long delta = this->total_snd_- this->total_rcv_;

  if (delta > winsize)
    return 0;
  
  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (blksize+1),
                  -1);

  mb->rd_ptr(mb->base());
  mb->wr_ptr(mb->base() + blksize);

  ACE_OS::strncpy(mb->rd_ptr(), complete_message, blksize);

  *mb->wr_ptr() = '\0'; 
    
  if (this->stream_.write (*mb, mb->length ()) == -1)
    {
      mb->release ();
      this->stream_.cancel_and_close();
      return -1;
    }

  this->ref_cnt_w_++;
  this->total_w_++;
  return 0;
}

int
Sender::initiate_read_stream (void)
{
  u_int blksize = this->config().r_blksize();
  u_int limit   = this->config().xfer_limit();

  if (limit != 0 && this->total_rcv_ >= limit)
    return 0;

  if (this->get_ref_cnt_r() != 0 )
    return 0;

  ACE_Message_Block *mb = 0;
  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (blksize+1),
                  -1);

  // Inititiate read
  if (this->stream_.read (*mb, mb->size () - 1) == -1)
    {
      mb->release ();
      this->stream_.cancel_and_close();
      return -1;
    }

  this->ref_cnt_r_++;
  this->total_r_++;
  return 0;
}

void
Sender::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
  this->trace_write_completion (result);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->ref_cnt_w_--;

    ACE_Message_Block & mb = result.message_block ();
    mb.release ();

    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->initiate_write_stream ();
        this->initiate_read_stream();
      }
    else
      this->stream_.cancel_and_close ();


    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

void
Sender::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
  this->trace_read_completion (result);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->ref_cnt_r_--;

    ACE_Message_Block & mb = result.message_block ();

    mb.release ();

    if (result.error () == 0 && result.bytes_transferred () > 0)
      {
        this->initiate_read_stream ();
        this->initiate_write_stream ();
      }
    else
      this->stream_.cancel_and_close ();

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_session(this);
}

class RecvFactory : public PSessionFactory
{
public:
  virtual PSession*  create_session(PSessionManager & /*manager*/)
    {
      PSession * p = 0;
      ACE_NEW_RETURN (p, Receiver, 0);
      return p;
    }
};

class SendFactory : public PSessionFactory
{
public:
  virtual PSession*  create_session(PSessionManager & /*manager*/)
    {
      PSession * p = 0;
      ACE_NEW_RETURN (p, Sender, 0);
      return p;
    }
};

// *************************************************************
//   Configuration helpers
// *************************************************************

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("P3_Test"));


  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

//  ACE_DEBUG ((LM_DEBUG,
//              ACE_TEXT ("FD_SETSIZE=%d ACE_FDSETSIZE=%d\n"),
//              FD_SETSIZE,
//              ACE_FD_SETSIZE));

  ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


  {
  int rc = 0;

  TestCfg  cfg2(cfg);
  cfg2.set_proactor_type( ACE_TEXT("Y")); // dummy

  ProactorTask    task1(cfg);
  ProactorTask    task2(cfg2);

  RecvFactory r_factory;
  SendFactory s_factory;

  PSessionManager r_manager (task1, r_factory,"R_Manager");
  PSessionManager s_manager (task1, s_factory,"S_Manager");

  Acceptor  acceptor  (r_manager);
  Connector connector (s_manager);

  TRB_Sock_Addr listen_addr;
  TRB_Sock_Addr connect_addr;
  cfg.get_addresses (listen_addr, connect_addr);

  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task2.start() == 0 && task1.start () == 0)
    {
      ACE_Time_Value timeout (cfg.timeout(), 0);
      r_manager.set_timeout (timeout);
      s_manager.set_timeout (timeout);

      pBackTask = &task2;

      if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
        {
          // Simplify, initial read with zero size
          if (acceptor.start (listen_addr.get_ace_addr ()) == 0)
            rc = 1;
        }

      if (cfg.both() != 0 || cfg.connections () > 0) // Connector
        {
          rc += connector.start (connect_addr.get_ace_addr (),
                                 cfg.connections ());
        }

      time_begin = ACE_OS::gettimeofday ();

      if (rc > 0)
        {
          task2.enable_event_loop();
          task1.enable_event_loop();
          
          ACE_Time_Value  sleep_time (cfg.seconds());
           
          while ( sleep_time != ACE_Time_Value::zero)
            {
              ACE_Countdown_Time countdown ( & sleep_time );

              ACE_OS::sleep (sleep_time );
            }


          if (cfg.seconds () == 0)
            {
              // comment this later
              char c;
              cout << "Press any key to stop=>" << flush;
              cin.clear ();
              cin >> c;
            }
        }
    }


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Cancel Connector: PendingOP=%d Senders=%d\n"),
              connector.get_ref_cnt(),  // number_pending_connects
              s_manager.get_number_connections ()
            ));
 
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Cancel Acceptor: PendingOP=%d Receivers=%d\n"),
              acceptor.get_ref_cnt(),  // number_pending_accepts
              r_manager.get_number_connections ()
            ));

  // Cancel all pending AIO on
  // Connector, Acceptor, all Senders, all Receivers
  connector.cancel ();
  acceptor.cancel  ();
  s_manager.cancel ();
  r_manager.cancel ();
   
  pBackTask = 0;

  while ( !connector.is_safe_to_delete () ||
          !acceptor.is_safe_to_delete  () ||
          !s_manager.is_safe_to_delete () ||
          !r_manager.is_safe_to_delete () 
        )
    {
        task1.wait_signal ();
    }

  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task2.stop ();
  task1.stop ();
 

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Stop Connector: PendingOP=%d Senders=%d\n"),
              connector.get_ref_cnt (), // number_pending_connects
              s_manager.get_number_connections ()
            ));
 
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) *** Stop Acceptor: PendingOP=%d Receivers=%d\n"),
              acceptor.get_ref_cnt (),  //number_pending_accepts
              r_manager.get_number_connections ()
            ));


  //Print statistic
  s_manager.print_statistic ();
  r_manager.print_statistic ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Threads = %d BlkSize=%d\n"),
              cfg.threads(),
              cfg.blksize()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Sessions: Max=%d  S=%d R=%d \n"),
              cfg.connections (),
              s_manager.get_peak_connections (),
              r_manager.get_peak_connections ()));


  float  fsec = (float)(time_run.msec()/1000);
  double fspeed = ((float) s_manager.get_total_snd()
                  +(float) s_manager.get_total_rcv()
                  +(float) r_manager.get_total_snd()
                  +(float) r_manager.get_total_rcv()
                  );

  if ( fsec > 0.1 )
    fspeed /= fsec; 

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective run time = %f sec\n"),
              fsec));


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Effective bytes/sec = %f\n"),
              fspeed));

 }

  ACE_END_TEST;

  return 0;
}


