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
 *  @file P2_Test.cpp
 *
 *
 *  This program illustrates how the TRB_Proactor can be used to
 *  implement an application that does various asynchronous
 *  operations.
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"
#include "P2_Test.h"
//#include "ace/Countdown_Time.h"



static TestCfg  cfg;


// *************************************************************
//  Bridge
// *************************************************************
Bridge::Bridge   (Acceptor & acceptor, int index)
  : lock_        (),
    acceptor_    (acceptor),
    index_       (index),
//    ref_cnt_     (0),   // Number of currently outstanding I/O requests
    flg_cancel_  (0),
    queue_r2s_   (),
    queue_s2r_   (),
    receiver_    (0),
    sender_      (0)
{
  this->acceptor_.on_new_bridge(this);
}

Bridge::~Bridge (void)
{
  this->close ();

  ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);
  this->acceptor_.on_delete_bridge(this);

  this->acceptor_.on_delete_session (this->sender_);
  delete this->sender_;
  this->sender_ = 0;

  this->acceptor_.on_delete_session (this->receiver_);
  delete this->receiver_;
  this->receiver_ = 0;

  this->index_ = -1;
}

  
long 
Bridge::check_ref (void)
{
   long cnt = 0; //this->ref_cnt_ ;

   if (this->sender_ != 0)
     cnt += this->sender_->get_ref_cnt ();

   if (this->receiver_ != 0)
     cnt += this->receiver_->get_ref_cnt ();

   return cnt;
}

long
Bridge::try_destroy (void)
{
  long ret = this->check_ref ();

  ACE_ASSERT (ret == 0);
  delete this;

  return ret;
}

long
Bridge::cancel ()
{
  ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, 1);

  this->flg_cancel_ = 1;

  if (this->sender_)
    this->sender_->cancel ();

  if (this->receiver_)
    this->receiver_->cancel ();

  return check_ref ();
}

long
Bridge::close ()
{
  ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, 1);

  if (this->sender_)
    this->sender_->close ();
  
  if (this->receiver_)
    this->receiver_->close ();

  return check_ref ();
}


int
Bridge::on_accept(void)
{
  int rc = -1;

  {
    ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, -1);

    ACE_ASSERT (this->receiver_ == 0);

    ACE_NEW_NORETURN (this->receiver_, Receiver (this));


    if (this->receiver_ != 0)
      {
        this->acceptor().on_new_session (this->receiver_);

        ACE_NEW_NORETURN (this->sender_, Sender (this));

        if (this->sender_ != 0)
          {
            this->acceptor().on_new_session (this->sender_);

            const ACE_Addr & addr = this->acceptor().addr_connect();

            rc = this->sender_->connect(addr);
            
          }
      }

      if (this->check_ref () != 0)
        return rc;
  }

  this->try_destroy ();
  return rc;
}


int
Bridge::putq (ACE_Message_Block & mb, int qtype)
{
  ACE_Time_Value tv = ACE_Time_Value::zero;

  int qcount = -1;

  const ACE_TCHAR * err_txt = ACE_LIB_TEXT("??????");

  switch (qtype)
    {
    case Q_R2S:
      qcount = this->queue_r2s_.enqueue_tail ( &mb, &tv);
      err_txt = ACE_LIB_TEXT("Q_R2S Rcv-->Snd");
      break;

    case Q_S2R: 
      qcount = this->queue_s2r_.enqueue_tail ( &mb, &tv);
      err_txt = ACE_LIB_TEXT("Q_S2R Rcv<--Snd");
      break;

    default:
      ACE_ASSERT (0);
      break;
    }

  if (qcount < 0)
    {
      mb.release ();
      ACE_ERROR_RETURN 
        ((LM_ERROR,
          ACE_LIB_TEXT("(%t) Put queue failed: %s\n"),
          err_txt), 
          -1);
    }

  return qcount;
}

ACE_Message_Block *
Bridge::getq (int qtype)
{
  ACE_Time_Value tv = ACE_Time_Value::zero;

  ACE_Message_Block * mb = 0;

  int qcount = -1;

  switch (qtype)
    {
    case Q_R2S:
      qcount = this->queue_r2s_.dequeue_head (mb, &tv);
      break;

    case Q_S2R: 
      qcount = this->queue_s2r_.dequeue_head (mb, &tv);
      break;

    default:
      ACE_ASSERT (0);
      break;
    }

  return mb;
}

int
Bridge::qcount(int qtype)
{
  int qcount = -1;

  switch (qtype)
    {
    case Q_R2S:
      qcount = this->queue_r2s_.message_count ();
      break;

    case Q_S2R: 
      qcount = this->queue_s2r_.message_count ();;
      break;

    default:
      ACE_ASSERT (0);
      break;
    }

  return qcount;
}


int 
Bridge::on_data_received (ACE_Message_Block * mb, int qtype)
{
  if (mb != 0)
    {
      int rc = this->putq (*mb, qtype);
      if (rc < 0)
        return -1;
    }

  return this->check_flow (qtype);
}

int 
Bridge::on_data_sent (ACE_Message_Block * mb, int qtype)
{
  //int mb_type = ACE_Message_Block::MB_DATA;

  ACE_Message_Block::release (mb);

  return this->check_flow (qtype);
}

int Bridge::check_flow (int qtype)
{
  Session *  from = 0;
  Session *  to = 0;

  switch (qtype)
    {
    case Q_R2S:  //  got data from R in Q_R2S  to S
      from = this->receiver_;
      to   = this->sender_;
      break;

    case Q_S2R:  //  got  data from S in Q_S2R to R
      from = this->sender_;
      to   = this->receiver_;
      break;

    default:
      ACE_ASSERT (0);
      return -1;
    }

  ACE_Message_Block * mb = 0;

  if (to != 0 && to->is_open()) // && to->get_ref_cnt_w () == 0)
    {
      mb = this->getq (qtype);

      if (mb != 0)
        to->initiate_write_stream (*mb, mb->length ());
    }

  if (from != 0 && from->is_open() && from->get_ref_cnt_r () == 0)
    {
      //size_t delta = from->get_total_rcv ();

      //if (to != 0)
      //  delta -= to->get_total_snd ();

      //if (delta < w_size)

      int qcount = this->qcount(qtype);

      u_int r_blksize = this->acceptor().task().config().r_blksize ();
      u_int w_size = this->acceptor().task().config().w_size ();
  
      if (qcount == 0 || (u_int)qcount*r_blksize < w_size)
        from->initiate_read_stream ();
    }

  return 0;
}

// *************************************************************
// Acceptor
// *************************************************************
Acceptor::Acceptor (ProactorTask & task)
  : task_        (task),
    lock_        (),
    addr_listen_ (),
    addr_connect_(),
    bridges_     (0),
    total_snd_   (0),
    total_rcv_   (0),
    total_w_     (0),
    total_r_     (0),
    flg_cancel_  (0)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
     this->list_bridges_ [i] = 0;
}

Acceptor::~Acceptor (void)
{
  this->stop ();

}

int
Acceptor::start(const ACE_Addr & addr_listen,
                const ACE_Addr & addr_connect)
{
  this->addr_listen_  = addr_listen;
  this->addr_connect_ = addr_connect;


  return this->open(this->addr_listen_,
                    0,   //size_t bytes_to_read = 0,
                    1,   //int pass_addresses = 0,
                    ACE_DEFAULT_BACKLOG, //int backlog ,
                    1,   //int reuse_addr = 1,
                    this->task_.get_proactor(0), // TRB_Proactor *proactor = 0,
                    1,   //int validate_new_connection = 0,
                    1,   //int reissue_accept = 1,
                    5 ); //int number_of_initial_accepts = -1);
}

void
Acceptor::cancel_all (void)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->flg_cancel_ = 1;

  this->reissue_accept(0);  // stop future accepts
  this->cancel ();


  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_bridges_[i] != 0)
        this->list_bridges_[i]->cancel ();
    }
  return;
}

void
Acceptor::stop (void)
{
  // This method can be called only after proactor event loop is done
  // in all threads.

  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      delete this->list_bridges_[i];
      this->list_bridges_[i] = 0;
    }
}

void
Acceptor::on_new_bridge (Bridge * bridge)
{
  if (bridge)
    {
      u_int i = bridge->index (); 

      ACE_ASSERT(i < MAX_CONNECTIONS);
      ACE_ASSERT(this->list_bridges_[i] == 0);

      this->list_bridges_[i] = bridge;
      ++this->bridges_;
    }
}

void
Acceptor::on_delete_bridge (Bridge * bridge)
{
  if (bridge)
    {
      u_int i = bridge->index (); 

      ACE_ASSERT(i < MAX_CONNECTIONS);
      ACE_ASSERT(this->list_bridges_[i] == bridge);

      this->list_bridges_[i] = 0;
      --this->bridges_;
    }

 if (this->bridges_ == 0)
    this->task().signal_main();

}

void
Acceptor::on_new_session (Session * session)
{
  if (!session)
    return;

  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) NEW %s=%d total=%d.\n"),
              session->get_name (),
              session->index (),
              this->bridges_));
}

void
Acceptor::on_delete_session (Session * session)
{
  if (!session)
    return;

  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->total_snd_ += session->get_total_snd();
  this->total_rcv_ += session->get_total_rcv();
  this->total_w_   += session->get_total_w();
  this->total_r_   += session->get_total_r();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) DEL %s=%d S=%d(%d) R=%d(%d) total=%d\n"),
              session->get_name (),
              session->index (),
              session->get_total_snd(),
              session->get_total_w(),
              session->get_total_rcv(),
              session->get_total_r(),
              this->bridges_));
}

int
Acceptor::should_reissue_accept (void)
{
  return (this->flg_cancel_ == 0) ? 1 : 0;
}


int
Acceptor::validate_connection (const TRB_Asynch_Accept::Result & /*result*/,
                               const ACE_Addr & /*remote_addr*/,
                               const ACE_Addr & /*local_addr*/)
{
   return 0;
} 


Receiver *
Acceptor::make_handler (void)
{
  Bridge * bridge = 0;
  {
    ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_, 0);

    if (this->bridges_ >= MAX_CONNECTIONS || this->flg_cancel_ !=0 )
      return 0;

    u_int  i = 0;

    for ( i = 0; i < MAX_CONNECTIONS; ++i)
      {
        if (this->list_bridges_[i] == 0)
          {
            ACE_NEW_RETURN (bridge,
                            Bridge(*this,i),
                            0);
            break;
          }
      }

    if (bridge == 0)
      return 0;
  }

  if (bridge->on_accept () != 0)
    return 0;

  Receiver * rcvr = bridge->receiver ();

  ACE_ASSERT (rcvr != 0);
  
  return rcvr;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("P2_Test"));

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

  ProactorTask  task1(cfg);
  Acceptor  acceptor(task1);

  TRB_Sock_Addr listen_addr;
  TRB_Sock_Addr connect_addr;
  cfg.get_addresses (listen_addr, connect_addr);

  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task1.start () == 0)
    {
      // Simplify, initial read with zero size
      if (acceptor.start (listen_addr.get_ace_addr (),
                          connect_addr.get_ace_addr ()) == 0)
        rc = 1;
        
      time_begin = ACE_OS::gettimeofday ();

      if (rc > 0)
        {
          task1.enable_event_loop ();
          ACE_Time_Value  sleep_time (cfg.seconds());
           
          while ( sleep_time != ACE_Time_Value::zero)
            {
              ACE_Countdown_Time countdown ( & sleep_time );
          
               ACE_OS::sleep (sleep_time );
            }

          
          if (cfg.seconds () == 0)
            {
              char c;
              cout << "Press any key to stop=>" << flush;
              cin.clear ();
              cin >> c;
            }

        }
    }

  u_int  num_ssn = acceptor.get_number_bridges ();

  //Cancel all pending AIO on Acceptor And Receivers
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******* Cancel Acceptor: Bridges=%d\n"),
              num_ssn
            ));
  acceptor.cancel_all ();
   

  while ( acceptor.get_number_bridges () > 0 )
    {
        task1.wait_signal ();
    }

  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;

  u_long snd_bytes = acceptor.get_total_snd();
  u_long rcv_bytes = acceptor.get_total_rcv();
  u_long snd_op = acceptor.get_total_w();
  u_long rcv_op = acceptor.get_total_r();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task1.stop ();
 



  // As Proactor event loop now is inactive it is safe to destroy all
  // Receivers
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Acceptor/Receivers:Bridges_=%d\n"),
              acceptor.get_number_bridges ()));
  acceptor.stop ();

  //Print statistic
  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                   snd_bytes,
                   snd_op);

  ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                   rcv_bytes,
                   rcv_op);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Total bytes: snd=%s rcv=%s\n"),
              bufs,
              bufr));


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Threads = %d BlkSize=%d\n"),
              cfg.threads(),
              cfg.blksize()));

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Sessions = %d (%d) \n"),
              rc-1,
              cfg.connections ()));


  float  fsec = (float)(time_run.msec()/1000);
  double fspeed = ((float) snd_bytes
                  +(float) rcv_bytes
                  );

  if ( fsec > 0.1 )
    fspeed /= fsec; 

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Effective run time = %f sec\n"),
              fsec));


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Effective bytes/sec = %f\n"),
              fspeed));


  } // ProactorTask

  ACE_END_TEST;

  return 0;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_Acceptor<Receiver>;
template class TRB_Asynch_Connector<Sender>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_Acceptor<Receiver>
#pragma instantiate TRB_Asynch_Connector<Sender>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */




