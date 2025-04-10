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

//============================================================================
//
// = LIBRARY
//    tests
//
// = FILENAME
//    TSSL_Test.cpp
//
// = DESCRIPTION
//    This program illustrates how the <ACE_TP_Reactor> can be used to
//    implement an application that does various  operations.
//    usage: TSSL_Test
//           -n number threads in the TP_Reactor thread pool
//           -d duplex mode 1 (full-duplex) vs. 0 (half-duplex)
//           -p port to listen(Server)/connect(Client)
//           -h host to connect (Client mode)
//           -s number of sender's instances ( Client mode)
//           -b run client and server (both modes ) at the same time
//           -v log level
//              0 - log all messages
//              1 - log only errors and unusual cases
//           -i time to run in seconds
//           -u show this message
//
//     The main differences between Thread_Pool_Reactor_Test.cpp and
//     this test are:
//
//     1. Thread_Pool_Reactor_Test.cpp tests only handle_input()
//     events on the server, whereas this one tests both handle_input() and
//     handle_output() on both server and client, i.e., the receiver
//     and sender are completely event-driven.
//
//     2. The receiver and sender in this test can work in full duplex
//     mode, i.e., input and ouput events are processed independently.
//     Half-duplex mode (request-reply) is also supported.
//
//     This test is therefore a bit more stressful than the
//     Thread_Pool_Reactor.cpp for the ACE_TP_Reactor since same
//     thread pool is shared between client and server.
//
//     This test is a "twin" of the Proactor_Test.cpp, so it can help for
//     developers to provide independent of Reactor/Proactor solutions.
//
// = AUTHOR
//      Alexander Libman <libman@terabit.com.au>
//
//============================================================================

#include "test_config.h"

#if defined(ACE_HAS_THREADS)

#include "TSSL_Test.h"

#include "ace/Signal.h"
#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"
#include "ace/streams.h"

#include "ace/Reactor.h"
#include "ace/TP_Reactor.h"

ACE_RCSID(TPReactor, TPReactor_Test, "TPReactor_Test.cpp,v 1.27 2000/03/07 17:15:56 schmidt Exp")

static TestCfg cfg;

static char data[] =
  "GET / HTTP/1.1\r\n"
  "Accept: */*\r\n"
  "Accept-Language: C++\r\n"
  "Accept-Encoding: gzip, deflate\r\n"
  "User-Agent: TPReactor_Test/1.0 (non-compatible)\r\n"
  "Connection: Keep-Alive\r\n"
  "\r\n" ;


// *************************************************************

Acceptor::Acceptor (TP_ReactorTask & task)
  : ACE_Acceptor<Receiver,ACE_SSL_SOCK_ACCEPTOR> ((ACE_Reactor *) 0),
    task_     (task),
    connections_ (0),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
     this->list_connections_[i] =0;
}

Acceptor::~Acceptor (void)
{
  this->reactor (0);
  stop ();
}

int
Acceptor::stop (void)
{
  // this method can be called only after reactor event loop id done
  // in all threads

  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] !=0)
        this->list_connections_[i]->close();
    
      //delete this->list_connections_[i];
      //this->list_connections_[i] =0;
    }
  return 0;
} 

int
Acceptor::cancel_all(void)
{
  // this method can be called only after reactor event loop id done
  // in all threads

  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] !=0)
        this->list_connections_[i]->flg_cancel_ =1;
    }

  return 0;
}


void
Acceptor::on_new_receiver (Receiver &rcvr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
  this->connections_++;
  this->list_connections_[ rcvr.index_] = & rcvr;
  ACE_DEBUG ((LM_DEBUG,
              "Receiver::CTOR connections_=%d\n",
              this->connections_));
}

void
Acceptor::on_delete_receiver (Receiver &rcvr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  this->connections_--;

  this->total_snd_ += rcvr.get_total_snd ();
  this->total_rcv_ += rcvr.get_total_rcv ();
  this->total_w_   += rcvr.get_total_w ();
  this->total_r_   += rcvr.get_total_r ();

  if (rcvr.index_ < MAX_CONNECTIONS
      && this->list_connections_[rcvr.index_] == &rcvr)
    this->list_connections_[rcvr.index_] = 0;

  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf ( bufs , ACE_TEXT ("%ld(%ld)"),
                    rcvr.get_total_snd (),
                    rcvr.get_total_w () );

  ACE_OS::sprintf ( bufr , ACE_TEXT ("%ld(%ld)"),
                    rcvr.get_total_rcv (),
                    rcvr.get_total_r ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Receiver::~DTOR index=%d snd=%s rcv=%s connections_=%d\n"),
              rcvr.index_,
              bufs,
              bufr,
              this->connections_));
}

int
Acceptor::start (const ACE_INET_Addr &addr)
{
  if (ACE_Acceptor<Receiver,ACE_SSL_SOCK_ACCEPTOR>
      ::open (addr,
              this->task().tp_reactor(),
              ACE_NONBLOCK) < 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "Acceptor::start () - open failed"),
                       -1);
  return 0;
}

int
Acceptor::make_svc_handler (Receiver *&sh)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  if (connections_ >= MAX_CONNECTIONS)
    return -1;

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    if (this->list_connections_ [i] == 0)
      {
        ACE_NEW_RETURN (sh,
                        Receiver (this , i),
                        -1);
        return 0;
      }
  return -1;
}

// *************************************************************

Receiver::Receiver (Acceptor * acceptor, int index)
  : acceptor_ (acceptor),
    index_ (index),
    flg_mask_ (ACE_Event_Handler::NULL_MASK),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  if (acceptor_ != 0)
    acceptor_->on_new_receiver (*this);
}


Receiver::~Receiver (void)
{
  this->reactor (0);
  if (acceptor_ != 0)
    acceptor_->on_delete_receiver (*this);

  this->index_ = 0;

  for (; ;)
    {
      ACE_Time_Value tv = ACE_Time_Value::zero;
      ACE_Message_Block *mb = 0;

      if (this->mqn_.dequeue_head (mb, &tv) < 0)
        break;

      ACE_Message_Block::release (mb);
    }
}

int
Receiver::check_destroy (void)
{
  if (flg_mask_ == ACE_Event_Handler::NULL_MASK)
    return -1;

  return 0;
}

int
Receiver::open (void *)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  ACE_Reactor * TPReactor = this->acceptor_->task().tp_reactor();
  
  this->reactor (TPReactor);

  flg_mask_ = ACE_Event_Handler::NULL_MASK ;

  if (TPReactor->register_handler (this, flg_mask_) == -1)
    return -1;

  initiate_io (ACE_Event_Handler::READ_MASK);

  return check_destroy ();
}

int
Receiver::initiate_io (ACE_Reactor_Mask mask)
{
  if (this->should_finish())
    return -1;

  if (ACE_BIT_ENABLED (flg_mask_, mask))
    return 0;

  if (this->reactor()->schedule_wakeup  (this, mask) == -1)
    return -1;

  ACE_SET_BITS (flg_mask_, mask);
  return 0;
}

int
Receiver::terminate_io (ACE_Reactor_Mask mask)
{
  if (ACE_BIT_DISABLED (flg_mask_, mask))
    return 0;

  if (this->reactor()->cancel_wakeup (this, mask) == -1)
    return -1;

  ACE_CLR_BITS (flg_mask_, mask);
  return 0;
}

int
Receiver::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
  ACE_Reactor * TPReactor = this->reactor();
  
  if (TPReactor != 0)
    TPReactor->remove_handler (this,
                               ACE_Event_Handler::ALL_EVENTS_MASK |
                               ACE_Event_Handler::DONT_CALL);  // Don't call handle_close
  this->reactor (0);
  this->destroy ();
  return 0;
}

int
Receiver::handle_input (ACE_HANDLE h)
{
//  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  if (this->should_finish())
    return -1;

  u_int r_blksize = cfg.r_blksize(); 
  u_int w_size = cfg.w_size();
  int loglevel = cfg.loglevel();

  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (r_blksize+1),
                  -1);

  int err = 0;
  ssize_t res = this->peer ().recv (mb->rd_ptr (),r_blksize);

  this->total_r_++;

  if (res >= 0)
    {
      mb->wr_ptr (res);
      this->total_rcv_ += res;
    }
  else
    {
      err = errno ;
      if (err == EWOULDBLOCK)
        {
          err=0;
          res=0;
          ACE_Message_Block::release (mb);
          ACE_DEBUG((LM_DEBUG,"Receiver - EWOULDBLOCK???\n"));
          return check_destroy();
        }
    }

  mb->wr_ptr ()[0] = '\0';


  if (loglevel == 0 || res <= 0 || err != 0)
    {
      LogLocker log_lock;

      ACE_DEBUG ((LM_DEBUG, "(%t)**** Receiver::handle_input () SessionId=%d****\n", index_));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_to_read", BUFSIZ));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "handle", h));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_transferred", res));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "error", err));
      ACE_DEBUG ((LM_DEBUG, "%s = %s\n", "message_block", mb->rd_ptr ()));
      ACE_DEBUG ((LM_DEBUG, "**** end of message ****************\n"));
    }


  if (err !=0  || res <= 0)
    {
      ACE_Message_Block::release (mb);
      return -1;
    }

  ACE_Time_Value tv = ACE_Time_Value::zero;

  int qcount = this->mqn_.enqueue_tail (mb, & tv);

  if (qcount < 0)  // failed to putq
    {
      ACE_Message_Block::release (mb);
      ACE_DEBUG((LM_DEBUG,"Receiver - putq overflow\n"));
      return -1 ;
    }

  do_delay(cfg.delay());  // 

  int rc = 0;

  if ((u_long)(this->total_rcv_-this->total_snd_) > w_size &&
       qcount > 0)
    rc = this->terminate_io (ACE_Event_Handler::READ_MASK);
  else
    rc = this->initiate_io (ACE_Event_Handler::READ_MASK);

  if (rc == -1)
    return -1;

  //initiate write
  if (qcount > 0 &&
      this->initiate_io (ACE_Event_Handler::WRITE_MASK) != 0)
    return -1;

  return check_destroy ();
}

int
Receiver::handle_output (ACE_HANDLE h)
{
//  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  ACE_Time_Value tv = ACE_Time_Value::zero;
  ACE_Message_Block *mb = 0;

  int     err = 0;
  ssize_t res = 0;
  int     bytes = 0;

  int loglevel = cfg.loglevel();
  u_int w_size = cfg.w_size ();


  if (this->should_finish())
    return -1;

  int  qcount = 0;

  for (;;)
   {
      mb = 0;
      qcount = this->mqn_.dequeue_head (mb , & tv);

      if (mb == 0)
        break;

      bytes = mb->length ();
      res = this->peer ().send (mb->rd_ptr (), bytes);

      this->total_w_++;

      if (res < 0)
        {
          err = errno ;
          if (err == EWOULDBLOCK)
            {
              qcount = this->mqn_.enqueue_head (mb, & tv);
              mb = 0;
              err = 0;
              res = 0;
              break;
            } 
        }     
      else
        this->total_snd_ += res;


      if (loglevel == 0 || res <= 0 || err!= 0)
        {
          LogLocker log_lock;

          ACE_DEBUG ((LM_DEBUG, "(%t)**** Receiver::handle_output () SessionId=%d****\n", index_));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_to_write", bytes));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "handle", h));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_transferred", res));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "error", err));
          ACE_DEBUG ((LM_DEBUG, "%s = %s\n", "message_block", mb->rd_ptr ()));
          ACE_DEBUG ((LM_DEBUG, "**** end of message ****************\n"));
        }

       ACE_Message_Block::release (mb);
    }


  if (err != 0  || res < 0)
    return -1;

  if (qcount <= 0)  // no more message blocks in queue
    {
      if (this->terminate_io (ACE_Event_Handler::WRITE_MASK) != 0)
        return -1;
    }

  if ( qcount <= 0 ||
      (u_long)(this->total_rcv_-this->total_snd_) <= w_size)
    {
      if (this->initiate_io (ACE_Event_Handler::READ_MASK) != 0)
        return -1;
    }

  return check_destroy ();
}

// *************************************************************

Connector::Connector (TP_ReactorTask & task)
  : ACE_Connector<Sender,ACE_SSL_SOCK_CONNECTOR> ((ACE_Reactor *) 0),
    task_     (task),
    connections_ (0),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
     this->list_connections_[i] = 0;
}

Connector::~Connector (void)
{
  this->reactor (0);
  stop ();
}

int
Connector::cancel_all(void)
{
  // this method can be called only after reactor event loop id done
  // in all threads

  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] !=0)
        this->list_connections_[i]->flg_cancel_ =1;
    }

  return 0;
}

int
Connector::stop ()
{
  // this method can be called only
  // after reactor event loop id done
  // in all threads

  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    {
    if (this->list_connections_[i] !=0)
        this->list_connections_[i]->close();
    
      //delete this->list_connections_[i];
      //this->list_connections_[i] =0;   
  }

  return 0;
}

void
Connector::on_new_sender (Sender & sndr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);
  this->connections_++;
  this->list_connections_[sndr.index_] = &sndr;
  ACE_DEBUG ((LM_DEBUG,
              "Sender::CTOR connections_=%d\n",
              this->connections_));
}

void
Connector::on_delete_sender (Sender & sndr)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  this->connections_--;
  this->total_snd_ += sndr.get_total_snd();
  this->total_rcv_ += sndr.get_total_rcv();
  this->total_w_   += sndr.get_total_w();
  this->total_r_   += sndr.get_total_r();

  if (sndr.index_ < MAX_CONNECTIONS
      && this->list_connections_[sndr.index_] == &sndr)
    this->list_connections_[sndr.index_] = 0;

  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf ( bufs , ACE_TEXT ("%ld(%ld)"),
                    sndr.get_total_snd(),
                    sndr.get_total_w() );

  ACE_OS::sprintf ( bufr , ACE_TEXT ("%ld(%ld)"),
                    sndr.get_total_rcv(),
                    sndr.get_total_r() );

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("Sender::~DTOR index=%d snd=%s rcv=%s connections_=%d\n"),
              sndr.index_,
              bufs,
              bufr,
              this->connections_));

}

int
Connector::start (const ACE_INET_Addr & addr, int num)
{

  if (ACE_Connector<Sender,ACE_SSL_SOCK_CONNECTOR>
      ::open (this->task().tp_reactor(),
              ACE_NONBLOCK) < 0)
    ACE_ERROR_RETURN
      ((LM_ERROR,
        "%p\n",
        "Connector::start () - open failed"),
       0);

  int rc = 0;

  ACE_Synch_Options opt(ACE_Synch_Options::USE_REACTOR,
                        ACE_Time_Value::zero);   //  (seconds,0));

  for (rc = 0 ; rc < num ; rc++)
    {
      Sender * sender = 0;

      if (ACE_Connector<Sender,ACE_SSL_SOCK_CONNECTOR>
          ::connect (sender,
                     addr) <0)
                     //opt) < 0)
        {
          if ( ACE_OS::last_error() == EWOULDBLOCK)
            continue;

          ACE_ERROR_RETURN
            ((LM_ERROR,
              "%p\n",
              "Connector::start () - connect failed"),
              rc);
        }
    }

  return rc;
}

int
Connector::make_svc_handler (Sender * & sh)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (this->mutex_);

  if (connections_ >= MAX_CONNECTIONS)
    return -1;

  for (size_t i = 0; i < MAX_CONNECTIONS; ++i)
    if (this->list_connections_ [i] == 0)
      {
        ACE_NEW_RETURN (sh,
                        Sender (this , i),
                        -1);
        return 0;
      }

  return -1;
}

// *************************************************************

Sender::Sender (Connector* connector, int index)
  : connector_ (connector),
    index_ (index),
    flg_mask_ (ACE_Event_Handler::NULL_MASK),
    total_snd_(0),
    total_rcv_(0),
    total_w_  (0),
    total_r_  (0),
    flg_cancel_(0)
{
  if (connector_ != 0)
    connector_->on_new_sender (*this);

}


Sender::~Sender (void)
{
  this->reactor (0);
  if (connector_ != 0)
    connector_->on_delete_sender (*this);

  this->index_ = 0;

  for (; ;)
    {
      ACE_Time_Value tv = ACE_Time_Value::zero;
      ACE_Message_Block *mb = 0;

      if (this->mqn_.dequeue_head (mb, &tv) < 0)
        break;

      ACE_Message_Block::release (mb);
    }
}

int
Sender::check_destroy (void)
{
  if (flg_mask_ == ACE_Event_Handler::NULL_MASK)
    return -1;

  return 0;
}

int Sender::open (void *)
{
  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  ACE_Reactor * TPReactor = this->connector_->task().tp_reactor();

  this->reactor (TPReactor);

  flg_mask_ = ACE_Event_Handler::NULL_MASK ;

  if (TPReactor->register_handler (this,flg_mask_) == -1)
    return -1;

  if (this->fill_queue () < 0)
    return -1;

  this->initiate_io (ACE_Event_Handler::WRITE_MASK);
  //this->initiate_io (ACE_Event_Handler::READ_MASK);

  return check_destroy ();
}

int
Sender::fill_queue (void)
{
  int cur_count = mqn_.message_count();

  u_int w_size = cfg.w_size();
  u_int s_blksize = cfg.s_blksize();

  int max_count = 1+ w_size/s_blksize;

  if (cur_count >= max_count)
    return max_count;
    
  for (; cur_count < max_count ; ++cur_count)
    {
      ACE_Message_Block *mb = 0;


      ACE_NEW_RETURN (mb,
                    ACE_Message_Block (s_blksize+1),
                    -1);

      mb->rd_ptr(mb->base());
      mb->wr_ptr(mb->base()+s_blksize);

      ACE_OS::strncpy(mb->rd_ptr(), data, s_blksize);
      *mb->wr_ptr() = '\0'; 


      ACE_Time_Value tv = ACE_Time_Value::zero;

      int qcount = this->mqn_.enqueue_tail (mb, & tv);

      if (qcount < 0)
        {
          ACE_Message_Block::release (mb);
          break;
        }
    }

 return cur_count;
}

int
Sender::initiate_io (ACE_Reactor_Mask mask)
{
  if (this->should_finish())
    return -1;

  if (ACE_BIT_ENABLED (flg_mask_, mask))
    return 0;

  if (this->reactor()->schedule_wakeup (this, mask) == -1)
    return -1;

  ACE_SET_BITS (flg_mask_, mask);
  return 0;
}

int
Sender::terminate_io (ACE_Reactor_Mask mask)
{
  if (ACE_BIT_DISABLED (flg_mask_, mask))
    return 0;

  if (this->reactor()->cancel_wakeup (this, mask) == -1)
    return -1;

  ACE_CLR_BITS (flg_mask_, mask);
  return 0;
}

int
Sender::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
  ACE_Reactor * TPReactor = this->reactor();

  if (TPReactor != 0)
    TPReactor->remove_handler (this,
                               ACE_Event_Handler::ALL_EVENTS_MASK |
                               ACE_Event_Handler::DONT_CALL);  // Don't call handle_close
  this->reactor (0);
  this->destroy ();
  return 0;
}

int
Sender::handle_input (ACE_HANDLE h)
{
//  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  if (this->should_finish())
    return -1;

  u_int r_blksize = cfg.r_blksize(); 
  u_int w_size = cfg.w_size(); 
  int loglevel = cfg.loglevel();

  ACE_Message_Block *mb = 0;

  ACE_NEW_RETURN (mb,
                  ACE_Message_Block (r_blksize+1),
                  -1);


  int     err = 0;
  ssize_t res = this->peer ().recv (mb->rd_ptr (),
                                    r_blksize);
  this->total_r_++;

  if (res >= 0)
    {
      mb->wr_ptr (res);
      this->total_rcv_ += res;
    }
  else
    {
      err = errno ;
      if (err == EWOULDBLOCK)
       {
         err=0;
         res=0;
         ACE_DEBUG((LM_DEBUG,"Sender::handle_input EWOULDBLOCK ???\n")); 
         return check_destroy ();
       }
    }

  mb->wr_ptr ()[0] = '\0';

  if (loglevel == 0 || res <= 0 || err!= 0)
    {
      LogLocker log_lock;

      ACE_DEBUG ((LM_DEBUG, "(%t)**** Sender::handle_input () SessionId=%d****\n", index_));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_to_read", BUFSIZ));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "handle", h));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_transferred", res));
      ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "error", err));
      ACE_DEBUG ((LM_DEBUG, "%s = %s\n", "message_block", mb->rd_ptr ()));
      ACE_DEBUG ((LM_DEBUG, "**** end of message ****************\n"));
    }

  ACE_Message_Block::release (mb);


  if (err !=0  || res <= 0)
    return -1;

  int count = fill_queue ();
  if (count < 0)
    return -1;

  int rc = 0;

  rc = this->initiate_io (ACE_Event_Handler::READ_MASK);
  if (rc < 0)
     return -1;

  if ((u_long)(this->total_snd_ - this->total_rcv_ ) > w_size ) 
    rc = this->terminate_io (ACE_Event_Handler::WRITE_MASK);
  else
    rc = this->initiate_io (ACE_Event_Handler::WRITE_MASK);

  if (rc < 0)
    return -1;
  
  return check_destroy ();
}

int
Sender::handle_output (ACE_HANDLE h)
{
//  ACE_Guard<ACE_Recursive_Thread_Mutex> locker (mutex_);

  ACE_Time_Value tv = ACE_Time_Value::zero;
  ACE_Message_Block *mb = 0;

  int     err=0;
  ssize_t res=0;
  int     bytes=0;

  int loglevel = cfg.loglevel();
  u_int w_size = cfg.w_size(); 

  if (this->should_finish())
    return -1;

  int rc = initiate_io (ACE_Event_Handler::READ_MASK);
  if (rc == -1)
     return -1;

  int  qcount = this->fill_queue();
  if (qcount < 0 )
    return -1;

  int flg_term = 1;

  for (qcount=0 ; ;++qcount)
    {
      mb = 0;

      this->mqn_.dequeue_head (mb, &tv);

      if (mb == 0) 
        break;

      bytes = mb->length ();
      res = this->peer ().send (mb->rd_ptr (), bytes);

      this->total_w_++;

      if (res < 0)
        {
          err = errno ;
          if (err == EWOULDBLOCK)
            {
              this->mqn_.enqueue_head (mb, & tv);
              mb = 0;
              err = 0;
              res = 0;
              flg_term = 0;
              break;
            } 
        }     
      else
        this->total_snd_ += res;

      if (loglevel == 0 || res <= 0 || err!= 0)
        {
          LogLocker log_lock;

          ACE_DEBUG ((LM_DEBUG, "(%t)**** Sender::handle_output () SessionId=%d****\n", index_));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_to_write", bytes));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "handle", h));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "bytes_transferred", res));
          ACE_DEBUG ((LM_DEBUG, "%s = %d\n", "error", err));
          ACE_DEBUG ((LM_DEBUG, "%s = %s\n", "message_block", mb->rd_ptr ()));
          ACE_DEBUG ((LM_DEBUG, "**** end of message ****************\n"));
        }

      ACE_Message_Block::release (mb);
    
      if (err != 0  || res < 0)
        return -1;

      if ((u_long)(this->total_snd_ - this->total_rcv_ ) > w_size )  
        {
          flg_term = 1;
          break;
        }
    }

  if (flg_term)
    rc = terminate_io (ACE_Event_Handler::WRITE_MASK);
  else
   rc = initiate_io (ACE_Event_Handler::WRITE_MASK);
  
  if (rc == -1)
    return -1;

  return check_destroy ();
}


#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Svc_Tuple<Sender>;
template class ACE_Map_Manager<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Entry<int, ACE_Svc_Tuple<Sender> * >;
template class ACE_Map_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Reverse_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Map_Iterator_Base<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >;
template class ACE_Connector<Sender,ACE_SSL_SOCK_CONNECTOR>;
template class ACE_Acceptor<Receiver,ACE_SSL_SOCK_ACCEPTOR>;
template class ACE_Svc_Handler<ACE_SSL_SOCK_STREAM,ACE_MT_SYNCH>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Svc_Tuple<Sender>
#pragma instantiate ACE_Map_Manager<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Entry<int, ACE_Svc_Tuple<Sender> * >
#pragma instantiate ACE_Map_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Reverse_Iterator<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Map_Iterator_Base<int, ACE_Svc_Tuple<Sender> *, ACE_RW_Thread_Mutex >
#pragma instantiate ACE_Connector<Sender,ACE_SSL_SOCK_CONNECTOR>
#pragma instantiate ACE_Acceptor<Receiver,ACE_SSL_SOCK_ACCEPTOR>
#pragma instantiate ACE_Svc_Handler<ACE_SSL_SOCK_STREAM,ACE_MT_SYNCH>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

#endif /* ACE_HAS_THREADS */

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_START_TEST (ACE_TEXT ("TSSL_Test"));

#if defined(ACE_HAS_THREADS)
  if (cfg.parse_args (argc, argv) < 0)
    return -1;

  disable_signal (ACE_SIGRTMIN, ACE_SIGRTMAX);
  disable_signal (SIGPIPE, SIGPIPE);
  disable_signal (SIGIO, SIGIO);

  ACE_SSL_Context *context = ACE_SSL_Context::instance ();
  // Note - the next two strings are naked on purpose... the arguments to
  // the ACE_SSL_Context methods are const char *, not ACE_TCHAR *.
  context->certificate ("dummy.pem", SSL_FILETYPE_PEM);
  context->private_key ("key.pem", SSL_FILETYPE_PEM);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("FD_SETSIZE=%d ACE_FDSETSIZE=%d\n"),
              FD_SETSIZE,
              ACE_FD_SETSIZE));

  ACE_DEBUG ((LM_DEBUG,
             "s_blksize=%u r_blksize=%u win_size=%u\n",
              cfg.s_blksize(),
              cfg.r_blksize(),
              cfg.w_size()));


  int rc = 0;

  TP_ReactorTask    task1(cfg);
  Acceptor  acceptor(task1);
  Connector connector(task1);



  ACE_Time_Value time_begin = ACE_OS::gettimeofday ();
  ACE_Time_Value time_end = ACE_OS::gettimeofday ();
  ACE_Time_Value time_run;

  if (task1.start () == 0)
    {
      task1.enable_event_loop();
      time_begin = ACE_OS::gettimeofday ();
    
    if (cfg.both() != 0 || cfg.connections () == 0) // Acceptor
        {
          if (acceptor.start (ACE_INET_Addr (cfg.listen_port())) == 0)
            rc = 1;
        }
      
      if (cfg.both() != 0 || cfg.connections () > 0) // Connector
        {
          ACE_INET_Addr addr;

          addr.set (cfg.connect_port(), cfg.connect_host());

          rc += connector.start (addr, cfg.connections ());
        }

      if (rc > 0)
        {
          ACE_Time_Value  sleep_time (cfg.seconds());
           
          while ( sleep_time != ACE_Time_Value::zero)
            {
              ACE_Countdown_Time countdown ( & sleep_time );

              ACE_OS::sleep (sleep_time );
            }

          if (cfg.seconds() == 0)
            {
              // comment this later
              char c;
              cout << "Press any key to stop=>" << flush;
              cin.clear ();
              cin >> c;
            }
        }
    }

  u_int  num_ssn_s = connector.get_number_connections ();
  u_int  num_ssn_r = acceptor.get_number_connections ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) Stop Thread Pool Task\n")));

  task1.stop ();
 

  // As Proactor event loop now is inactive it is safe to destroy all
  // Senders
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Connector/Senders: connections_=%d\n"),
              num_ssn_s));
  connector.stop ();

  // As Proactor event loop now is inactive it is safe to destroy all
  // Receivers
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t)******** Stop Acceptor/Receivers:connections_=%d\n"),
              num_ssn_r));
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
              ACE_TEXT ("Connector/Senders  total bytes: snd=%s rcv=%s\n"),
              bufs,
              bufr));

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





#else /* ACE_HAS_THREADS */
   ACE_UNUSED_ARG( argc );
   ACE_UNUSED_ARG( argv );
#endif /* ACE_HAS_THREADS */

  ACE_END_TEST;

  return 0;
}
