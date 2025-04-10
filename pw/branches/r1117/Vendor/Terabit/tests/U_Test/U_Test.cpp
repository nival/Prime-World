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
 *  @file U_Test.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "Cfg.h"
#include "U_Test.h"

#include "ace/SOCK_Dgram.h"
//#include "ace/Countdown_Time.h"

static TestCfg cfg;

static char complete_message[] =
  "GET / HTTP/1.1\r\n"
  "Accept: */*\r\n"
  "Accept-Language: C++\r\n"
  "Accept-Encoding: gzip, deflate\r\n"
  "User-Agent: U_Test /1.0 (non-compatible)\r\n"
  "Connection: Keep-Alive\r\n"
  "\r\n";

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
DSession::print_address (const ACE_Addr& addr)
{
    ACE_TCHAR str_addr[256];
    TRB_Sock_Addr::to_string (addr, 
                              str_addr, 
                              sizeof (str_addr)/sizeof (ACE_TCHAR));

    ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s=%d Addr=%s\n"),
              this->get_name (),
              this->index (),
              str_addr));
}


int
DSession::open (const ACE_Addr & local,
                const ACE_Addr & remote)
{
  {
    ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, -1);
    
    
    this->print_address (local);
    this->print_address (remote);
     

    ACE_SOCK_Dgram dgram;

    if (dgram.open(local, 
                   local.get_type (),
                   0,
                   1) == -1)
    {
      ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("(%t) %s=%d open error 1\n"),
              this->get_name (),
              this->index ()));
    }
    else if (this->stream_.open (*this, 
                                dgram.get_handle(),
                                0, // completion key,
                                this->owner_.task().get_proactor(this->index()),
                                1) == -1)
    {
      ACE_ERROR((LM_ERROR,
              ACE_TEXT ("(%t) %s=%d open error 2\n"),
              this->get_name (),
              this->index ()));
    }
    else
    {
      this->on_open(local, remote);
    }
    
    if (this->io_count_r_ != 0 || 
        this->io_count_w_ != 0 ||
        this->post_count_ != 0 )
      return 0;
  }
  delete this;
  return -1;
}

int
DSession::post_message (void)
{
  ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, monitor, this->lock_, -1 );

  if (this->get_pending_r_() == 0 &&
      this->get_pending_w_() == 0)
      return 0;  // too late


  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (80),
                  -1);

  char str[80];

  int len = ACE_OS::snprintf(str, 
                             sizeof(str),
                             "Message to %s=%d", 
                             this->get_name (),
                             this->index ());


  mb->rd_ptr(mb->base());
  mb->wr_ptr(mb->base() + len);
  ACE_OS::strcpy(mb->rd_ptr(), str);

  TRB_Asynch_User_Result result (this, 
                                 ACE_INVALID_HANDLE, // handle
                                 *mb,   
                                 0,  // bytes requested
                                 0,  // offset low
                                 0,  // offset high
                                 (const void*) this->index (),
                                 0,  // completion key
                                 0,  // priority
                                 0); // signal_number
  if (this->owner_.task().get_proactor(0)->post_completion (result) < 0)
    {
       mb->release ();
       ACE_ERROR_RETURN((LM_ERROR,
                       ACE_TEXT ("(%t) %s=%d attempt POST failed\n"),
                       this->get_name(),
                       this->index()),
                       -1);
    }

  this->post_count_ ++;
  return 0;
}
  
int
DSession::initiate_read (int prot_type)
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
                          prot_type) == -1)
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

    ACE_Message_Block *mb = result.message_block ();

    size_t xfer_bytes = result.bytes_transferred();
    char * last  = mb->wr_ptr();
    char * first = last - xfer_bytes; 

    u_long error = result.error ();


    if (loglevel == 0)
      {
        LogLocker log_lock;

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_read_dgram() ****\n"),
                    this->get_name(),
                    this->index()));
        
        this->print_address (result.remote_address());

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
                    error));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("message_block:\n")));

        ACE_HEX_DUMP ((LM_DEBUG, first, xfer_bytes));


        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (error != 0)
      {
        LogLocker log_lock;

        this->print_address (result.remote_address());

        ACE_OS::last_error (error);
        ACE_Log_Msg::instance ()->errnum (error);
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d READ ERROR=%d %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       error,
                                       ACE_TEXT (":"));
      }
    else if (loglevel == 1)
      {
         LogLocker log_lock;
         this->print_address (result.remote_address());

         ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d READ=%d bytes ok\n"),
                    this->get_name (),
                    this->index (),
                    result.bytes_transferred ()));
      }


    do_delay (cfg.delay());  // delay milliseconds

    if (error == 0 && result.bytes_transferred () > 0)
      {
        this->total_rcv_ += result.bytes_transferred ();

      }
    else
      {
        mb->msg_type (ACE_Message_Block::MB_HANGUP);
        mb->wr_ptr (mb->rd_ptr());
      }

      this->on_data_received (*mb, 
                              result.remote_address());

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

    ACE_Message_Block *mb = result.message_block ();
    size_t xfer_bytes = result.bytes_transferred();
    char * last  = mb->rd_ptr();
    char * first = last - xfer_bytes; 

    u_long error = result.error ();

    const ACE_Addr  & addr = result.remote_address ();

    if (cfg.loglevel () == 0)
      {
        LogLocker log_lock;

        //mb.rd_ptr () [0] = '\0';
        mb->rd_ptr (mb->rd_ptr () - result.bytes_transferred ());

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_write_dgram() ****\n"),
                    this->get_name(),
                    this->index()));

        this->print_address (addr);
        
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
                    error));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("message_block:\n")));

        ACE_HEX_DUMP ((LM_DEBUG, first, xfer_bytes));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("**** end of message ****************\n")));
      }
    else if (error != 0)
      {
        LogLocker log_lock;

        this->print_address (addr);

        ACE_OS::last_error (error);
        ACE_Log_Msg::instance ()->errnum (error);
        ACE_Log_Msg::instance ()->log (LM_ERROR,
                                       ACE_TEXT ("(%t) %s=%d WRITE ERROR=%d %p\n"),
                                       this->get_name (),
                                       this->index (),
                                       error,
                                       ACE_TEXT (":"));
      }
    else if (loglevel == 1)
      {
         LogLocker log_lock;
         this->print_address (addr);
         
         ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) %s=%d WRITE=%d bytes ok\n"),
                    this->get_name (),
                    this->index (),
                    result.bytes_transferred ()));
      }

    if (error == 0 && result.bytes_transferred () > 0)
      {
        this->total_snd_ += result.bytes_transferred ();
      }
    else
      {
        mb->msg_type (ACE_Message_Block::MB_ERROR);
        mb->wr_ptr (mb->rd_ptr());
      }

    this->on_data_sent (*mb, addr);
    
 
    if (this->io_count_r_ != 0 || 
        this->io_count_w_ != 0 ||
        this->post_count_ != 0 )
      return;
  }
  delete this;
}

void
DSession::handle_user_operation(const TRB_Asynch_User_Result& result)
{
  ACE_Message_Block *mb =result.get_message_block_ptr ();

  ACE_ASSERT (mb != 0);
  ACE_ASSERT (this->index() == (int) result.act ());

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);

    this->post_count_--;

      {
        LogLocker log_lock;


        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("(%t) **** %s=%d handle_message() ****\n"),
                    this->get_name(),
                    this->index()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("length"),
                    mb->length()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %d\n"),
                    ACE_TEXT ("act"),
                    (int) result.act ()));

        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("%s = %s\n"),
                    ACE_TEXT ("message_block"),
                    mb->rd_ptr ()));
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("**** end of message ****************\n")));
      }

    mb->release();
  
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
  : DSession (owner, index, ACE_TEXT("Receiver"))
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

  if (this->initiate_write (mb, remote) != 0)
    return -1;

  return 0;
}

int
Receiver::on_data_sent(ACE_Message_Block & mb,
                       const ACE_Addr & remote)
{
  ACE_UNUSED_ARG(remote);

  int nbytes = mb.length ();

  mb.release();

  if ( nbytes > 0 && this->io_count_r_ == 0)
    this->initiate_read(remote.get_type ());

  return 0;
}

// *********************************************************
//   Sender
// *********************************************************

Sender::Sender (DOwner & owner, int index)
  : DSession (owner, index, ACE_TEXT("Sender"))
{
}

Sender::~Sender (void)
{
}



int
Sender::on_open (const ACE_Addr & local,
                 const ACE_Addr & remote)
{
   ACE_UNUSED_ARG(local);
   ACE_Message_Block *mb = 0;

   ACE_NEW_RETURN (mb,
                  ACE_Message_Block (cfg.s_blksize()+1),
                  -1);

   mb->rd_ptr(mb->base());
   mb->wr_ptr(mb->base() + cfg.s_blksize());
   
   ACE_OS::strncpy(mb->rd_ptr(), complete_message,cfg.s_blksize());
   *mb->wr_ptr() = '\0'; 
 
 
   return this->on_data_sent(*mb, remote);
}

int
Sender::on_data_received(ACE_Message_Block & mb,
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

  if (this->io_count_w_ == 0)
    {
      mb.rd_ptr(mb.base());
      mb.wr_ptr(mb.base() + nbytes);

      this->initiate_write(mb, remote);
    }

  return 0;
}

int
Sender::on_data_sent(ACE_Message_Block & mb,
                     const ACE_Addr & remote)
{
  int nbytes = mb.length ();

  if (nbytes == 0)
    {
      mb.release();
      return 0;
    }
  
  if (this->io_count_r_ == 0)
    this->initiate_read(remote.get_type());

  
  if (this->io_count_w_ == 0)
    {
      mb.rd_ptr(mb.base());
      mb.wr_ptr(mb.base() + nbytes);

      this->initiate_write(mb, remote);
    }
  
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
DOwner::post_all (void)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->flg_cancel_ = 1;

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] != 0)
        this->list_connections_[i]->post_message();
    }
  return;
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
              ACE_TEXT ("(%t) DEL %s=%d S=%d(%d+%d) R=%d(%d+%d) total=%d\n"),
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
DOwner::start_sender(int index, const ACE_Addr& remote)
{
  ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_, 0);

  if (this->connections_ >= MAX_CONNECTIONS || flg_cancel_ != 0)
    return -1;

    

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_ [i] == 0)
        {
          ACE_NEW_RETURN (this->list_connections_[i],
                          Sender (*this, i),
                          -1);

          // this will create any address of given type
          TRB_Sock_Addr local;
          cfg.get_binding_address (local, index);
          
          this->list_connections_[i]->open(local.get_ace_addr (),
                                           remote);

          return 0;
        }
    }

  ACE_ASSERT(0);
  return -1;
}

int
DOwner::start_receiver(const ACE_Addr & listen)
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

          // this will create any address of given type
          TRB_Sock_Addr remote (listen.get_type ());
          this->list_connections_[i]->open(listen,
                                           remote.get_ace_addr ());
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
    ACE_START_TEST (ACE_TEXT ("U_Test"));


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
        DOwner      connector(task1);

        TRB_Sock_Addr listen_addr;
        TRB_Sock_Addr connect_addr;
        cfg.get_addresses (listen_addr, connect_addr);

        ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
        ACE_Time_Value time_end = ACE_OS::gettimeofday ();
        ACE_Time_Value time_run;

        if (task1.start () == 0)
        {
            if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
            {
                // Simplify, initial read with zero size
                if (acceptor.start_receiver(listen_addr.get_ace_addr()) == 0)
                    rc = 1;
            }

            if (cfg.both() != 0 || cfg.connections () > 0) // Connector
            {
                for (u_int i=0; i < cfg.connections (); ++i, ++rc)
                {
                    if (connector.start_sender (i, connect_addr.get_ace_addr()) != 0)
                        break;
                }
            }

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

                        switch (tolower(c[0]))
                        {
                        case 'p':
                            connector.post_all ();
                            acceptor.post_all ();
                            continue;
                        default:
                            break;
                        }
                        break;
                    }
                }
            }
        }

        u_int  num_ssn_s = connector.get_number_connections ();
        u_int  num_ssn_r = acceptor.get_number_connections ();

        // Cancel all pending AIO on Connector and Senders
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)******* Cancel Senders: connections_=%d\n"),
            connector.get_number_connections ()));
        connector.cancel_all ();

        //Cancel all pending AIO on Acceptor And Receivers
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)******* Cancel Receivers:connections_=%d\n"),
            acceptor.get_number_connections ()
            ));
        acceptor.cancel_all ();


        while (connector.get_number_connections () > 0 ||
               acceptor.get_number_connections () > 0 )
        {
            task1.wait_signal ();
        }


        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

        task1.stop ();


        // As Proactor event loop now is inactive it is safe to destroy all
        // Senders
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)******** Stop Senders: connections_=%d\n"),
            connector.get_number_connections ()));
        connector.stop ();

        // As Proactor event loop now is inactive it is safe to destroy all
        // Receivers
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t)******** Stop Receivers:connections_=%d\n"),
            acceptor.get_number_connections ()));
        acceptor.stop ();

        time_end = ACE_OS::gettimeofday ();
        time_run = time_end - time_begin;

        u_long snd_bytes_s = connector.get_total_snd();
        u_long rcv_bytes_s = connector.get_total_rcv();
        u_long snd_op_s = connector.get_total_w();
        u_long rcv_op_s = connector.get_total_r();

        u_long snd_bytes_r = acceptor.get_total_snd();
        u_long rcv_bytes_r = acceptor.get_total_rcv();
        u_long snd_op_r = acceptor.get_total_w();
        u_long rcv_op_r = acceptor.get_total_r();

        //Print statistic
        ACE_TCHAR bufs [256];
        ACE_TCHAR bufr [256];

        ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
            snd_bytes_s,
            snd_op_s);

        ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
            rcv_bytes_s,
            rcv_op_s);

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("Senders  total bytes: snd=%s rcv=%s\n"),
            bufs,
            bufr));

        ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
            snd_bytes_r,
            snd_op_r);

        ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
            rcv_bytes_r,
            rcv_op_r);

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("Receivers total bytes: snd=%s rcv=%s\n"),
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
        double fspeed = ((float) snd_bytes_s
            +(float) snd_bytes_r
            +(float) rcv_bytes_s
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


