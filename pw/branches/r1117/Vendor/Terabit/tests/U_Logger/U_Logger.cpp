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
 *  @file U_Logger.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "Cfg.h"
#include "U_Logger.h"

#include "ace/SOCK_Dgram.h"

static TestCfg cfg;



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_RW<TRB_Asynch_Read_Dgram,TRB_Asynch_Write_Dgram>;
template class TRB_Asynch_RW_Dgram<TRB_Asynch_Read_Dgram,TRB_Asynch_Write_Dgram>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_RW<TRB_Asynch_Read_Dgram,TRB_Asynch_Write_Dgram>
#pragma instantiate TRB_Asynch_RW_Dgram<TRB_Asynch_Read_Dgram,TRB_Asynch_Write_Dgram>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */



// *************************************************************
//   
// *************************************************************
DSession::DSession (DOwner & owner, int index, const ACE_TCHAR * name)
  : name_     (name),
    owner_    (owner),
    index_    (index),
    io_count_r_ (0),
    io_count_w_ (0),
    post_count_ (0),
    total_snd_  (0),
    total_rcv_  (0),
    total_w_    (0),
    total_r_    (0)
{
  this->owner_.on_new_session (*this);
}

DSession::~DSession (void)
{
  this->owner_.on_delete_session (*this);

  this->close();
  this->index_ = -1;
}

void
DSession::cancel ()
{
  ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);

  this->stream_.cancel_and_close();
}

void
DSession::close ()
{
  ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);
  this->stream_.close();
}

void
DSession::print_address (const ACE_Addr& addr, const ACE_TCHAR * txt)
{

    ACE_TCHAR str_addr[256];
    TRB_Sock_Addr::to_string (addr, 
                              str_addr, 
                              sizeof (str_addr)/sizeof (ACE_TCHAR));

  
    ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s=%d %s=%s\n"),
              this->get_name (),
              this->index (),
              txt,
              str_addr));
  
  return;
}


int
DSession::open (const ACE_Addr & local,
                const ACE_Addr & remote)
{
  {
    ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, -1);

    ACE_SOCK_Dgram dgram;

    if (dgram.open(local) == -1)
      ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("(%t) %s=%d open error 1\n"),
              this->get_name (),
              this->index ()));

    else if (this->stream_.open (*this, 
                                dgram.get_handle(),
                                0, // completion key,
                                this->owner_.task().get_proactor(this->index()),
                                1) == -1)
      ACE_ERROR((LM_ERROR,
              ACE_TEXT ("(%t) %s=%d open error 2\n"),
              this->get_name (),
              this->index ()));
    else
      this->on_open(local, remote);

    if (this->io_count_r_ != 0 || 
        this->io_count_w_ != 0 ||
        this->post_count_ != 0 )
      return 0;
  }
  delete this;
  return -1;
}

  
int
DSession::initiate_read (int addr_type)
{
  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (cfg.r_blksize()+1),
                  -1);

  if (cfg.loglevel() <= 1)
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d Initiate READ %u bytes\n"),
                    this->get_name (),
                    this->index (),
                    (u_int) cfg.r_blksize()));
      }


  size_t nbytes = cfg.r_blksize();

  // Inititiate read
  if (this->stream_.recv (*mb,
                          nbytes,
                          0,
                          addr_type) == -1)
    {
      mb->release ();
      this->stream_.cancel_and_close();

      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT ("(%t) %s=%d attempt READ failed\n"),
                        this->get_name(),
                        this->index()),
                        -1);
    }

  this->io_count_r_++;
  this->total_r_++;
  return 0;
}

int
DSession::initiate_write (ACE_Message_Block &mb,
                          const ACE_Addr & addr)
{

  size_t nbytes = mb.length();

  if (cfg.loglevel() <= 1)
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d Initiate WRITE %u bytes\n"),
                    this->get_name (),
                    this->index (),
                    nbytes));
      }

  if (nbytes == 0)
    {
      mb.release ();
      this->stream_.cancel_and_close();
      return -1;
    }

  if (this->stream_.send(mb,
                         nbytes,
                         0, 
                         addr) == -1)
    {
      mb.release ();
      this->stream_.cancel_and_close();

      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT ("(%t) %s=%d attempt WRITE failed\n"),
                        this->get_name(),
                        this->index()),
                        -1);
    }

  this->io_count_w_++;
  this->total_w_++;
  return 0;
}

void
DSession::handle_read_dgram (const TRB_Asynch_Read_Dgram::Result &result)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_ );

    this->io_count_r_--;

    int loglevel = cfg.loglevel();

    ACE_Message_Block * mb = result.message_block ();

    const ACE_Addr& peerAddr = result.remote_address ();
    
    // Reset pointers.
    mb->rd_ptr ()[result.bytes_transferred ()] = '\0';

    if (loglevel == 0)
      {
        LogLocker log_lock;

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_read_dgram() ****\n"),
                    this->get_name(),
                    this->index()));
        
        this->print_address (peerAddr,ACE_TEXT("From"));

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

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("error"),
                    result.error ()));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("message_block:\n")));

      ACE_HEX_DUMP ((LM_DEBUG, mb->rd_ptr (), mb->length() ));
      //result.bytes_transferred ());

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (result.error () != 0)
      {
        LogLocker log_lock;

        this->print_address (peerAddr,ACE_TEXT("From"));

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d ERROR %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       ACE_TEXT ("READ"));
      }
    else if ( loglevel ==1 )
      {
         LogLocker log_lock;
         this->print_address (peerAddr,ACE_TEXT("From"));

         ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d READ=%d bytes ok\n"),
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
        mb->msg_type (ACE_Message_Block::MB_HANGUP);
        mb->wr_ptr (mb->rd_ptr());
      }

    this->on_data_received (*mb, peerAddr);

    if (this->io_count_r_ != 0 || 
        this->io_count_w_ != 0 ||
        this->post_count_ != 0 )
      return;
  }
  delete this;
}

void
DSession::handle_write_dgram(const TRB_Asynch_Write_Dgram::Result &result)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);

    this->io_count_w_--;

    int loglevel = cfg.loglevel();

    const ACE_Addr & peerAddr = result.remote_address ();

    

    ACE_Message_Block * mb = result.message_block ();

    if (cfg.loglevel () == 0)
      {
        LogLocker log_lock;

        //mb.rd_ptr () [0] = '\0';
        mb->rd_ptr (mb->rd_ptr () - result.bytes_transferred ());

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_write_dgram() ****\n"),
                    this->get_name(),
                    this->index()));

        this->print_address (peerAddr,ACE_TEXT("To"));

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

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("error"),
                    result.error ()));
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("message_block:\n")));

      ACE_HEX_DUMP ((LM_DEBUG, mb->rd_ptr (), result.bytes_transferred () ));

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (result.error () != 0)
      {
        LogLocker log_lock;

        this->print_address (peerAddr,ACE_TEXT("To"));

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d ERROR %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       ACE_TEXT ("WRITE"));
      }
    else if ( loglevel ==1 )
      {
         LogLocker log_lock;
         this->print_address (peerAddr,ACE_TEXT("To"));

         ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d WRITE=%d bytes ok\n"),
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
        mb->msg_type (ACE_Message_Block::MB_ERROR);
        mb->wr_ptr (mb->rd_ptr());
      }

    this->on_data_sent (*mb, peerAddr);

 
    if (this->io_count_r_ != 0 || 
        this->io_count_w_ != 0 ||
        this->post_count_ != 0 )
      return;
  }
  delete this;
}

// *********************************************************
//   Receiver
// *********************************************************

Receiver::Receiver (DOwner & owner, int index)
  : DSession (owner, index, ACE_TEXT("RCVR"))
{
}

Receiver::~Receiver (void)
{
}


int
Receiver::on_open (const ACE_Addr & local,
                   const ACE_Addr & remote)
{
   //ACE_UNUSED_ARG(local);
   ACE_UNUSED_ARG(remote);

   return this->initiate_read(local.get_type ());
}

int
Receiver::on_data_received(ACE_Message_Block & mb,
                           const ACE_Addr & remote)
{
  int nbytes = mb.length ();

  if (nbytes == 0)
    {
      mb.release();
      return 0;
    }

  if (this->io_count_r_ == 0)
    this->initiate_read(remote.get_type ());

  return 0;
}

int
Receiver::on_data_sent(ACE_Message_Block & mb,
                       const ACE_Addr & remote)
{
  ACE_UNUSED_ARG(remote);

  int nbytes = mb.length ();

  mb.release();

  

  return 0;
}


// *************************************************************
//   Session Owner
// *************************************************************

DOwner::DOwner (ProactorTask & task)
  : task_     (task),
    connections_ (0),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
     this->list_connections_[i] = 0;
}

DOwner::~DOwner (void)
{
  this->stop ();
}


void
DOwner::cancel_all (void)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->flg_cancel_ = 1;

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] != 0)
        this->list_connections_[i]->cancel ();
    }
  return;
}

void
DOwner::stop (void)
{
  // This method can be called only after proactor event loop is done
  // in all threads.

  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      delete this->list_connections_[i];
      this->list_connections_[i] = 0;
    }
}

void
DOwner::on_new_session (DSession & session)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->connections_++;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) NEW %s=%d total=%d.\n"),
              session.get_name (),
              session.index (),
              this->get_number_connections ()));
}

void
DOwner::on_delete_session (DSession & session)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->connections_--;

  this->total_snd_ += session.get_total_snd();
  this->total_rcv_ += session.get_total_rcv();
  this->total_w_   += session.get_total_w();
  this->total_r_   += session.get_total_r();

  int index = session.index();

  if (index >= 0
      && (u_int) index < MAX_CONNECTIONS
      && this->list_connections_[index] == &session)
    this->list_connections_[index] = 0;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) DEL %s=%d S=%d(%d-%d) R=%d(%d-%d) total=%d\n"),
              session.get_name (),
              session.index (),
              session.get_total_snd(),
              session.get_total_w(),
              session.get_pending_w_(),
              session.get_total_rcv(),
              session.get_total_r(),
              session.get_pending_r_(),
              this->connections_));

  if (this->connections_ == 0)
    this->task().signal_main();

}


int
DOwner::start_receiver(const ACE_Addr & local)
{
  ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_, 0);

  if (this->connections_ >= MAX_CONNECTIONS || flg_cancel_ != 0)
    return -1;

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_ [i] == 0)
        {
          ACE_NEW_RETURN (this->list_connections_[i],
                          Receiver (*this, i),
                          -1);

          this->list_connections_[i]->open(local,ACE_Addr::sap_any);
          
          return 0;
        }
    }

  ACE_ASSERT(0);
  return -1;
}


// *************************************************************
//   Configuration helpers
// *************************************************************

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("U_Logger"));


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

  ProactorTask    task1(cfg);
  DOwner      acceptor(task1);
  
  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  TRB_Sock_Addr listenAddr ;
  cfg.get_listen_address (listenAddr);
  
  if (task1.start () == 0)
    {
        if (acceptor.start_receiver(listenAddr.get_ace_addr ()) == 0)
            rc = 1;
    
      time_begin = ACE_OS::gettimeofday ();

      if (rc > 0)
        {
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
              char c[80];

              for (;;)
                {
                  cout << "Press any key to stop=>" << flush;

                  cin.clear ();
                  cin.getline(c, 80);

                  //switch (tolower(c[0]))
                  //{
                  //default:
                  //  break;
                  //}
                  break;
                }

            }
        }
    }


  u_int  num_ssn_r = acceptor.get_number_connections ();


  
  //Cancel all pending AIO on Acceptor And Receivers
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******* Cancel Acceptor/Receivers:connections_=%d\n"),
              acceptor.get_number_connections ()
            ));
  acceptor.cancel_all ();
   

  while ( acceptor.get_number_connections () > 0 )
    {
        task1.wait_signal ();
    }


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task1.stop ();
 

  // As Proactor event loop now is inactive it is safe to destroy all
  // Receivers
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Acceptor/Receivers:connections_=%d\n"),
              acceptor.get_number_connections ()));
  acceptor.stop ();

  time_end = ACE_OS::gettimeofday ();
  time_run = time_end - time_begin;


  u_long snd_bytes_r = acceptor.get_total_snd();
  u_long rcv_bytes_r = acceptor.get_total_rcv();
  u_long snd_op_r = acceptor.get_total_w();
  u_long rcv_op_r = acceptor.get_total_r();

  //Print statistic
  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];


  ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                   snd_bytes_r,
                   snd_op_r);

  ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                   rcv_bytes_r,
                   rcv_op_r);
  
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Acceptor/Receivers total bytes: snd=%s rcv=%s\n"),
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
  double fspeed = ((float) snd_bytes_r
                  +(float) rcv_bytes_r
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


