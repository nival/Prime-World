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
 *  @file PConnection.cpp
 *
 *  PConnection.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================

#include "test_config.h"


#include "PConnection.h"
#include "ace/INET_Addr.h"

// ***************************************************************
//  PConnection - base class for all Read/Write Asynch handlers
// ***************************************************************

PConnection::PConnection (void)
  : lock_      (),
    manager_   (0),
    index_     (-1),
    protocol_  (0),
    ref_cnt_r_ (0),
    ref_cnt_w_ (0),
    total_snd_ (0),
    total_rcv_ (0),
    total_w_   (0),
    total_r_   (0),
    last_op_time_ (ACE_OS::gettimeofday ()),
    timeout_      (ACE_Time_Value::zero),
    buf_       ()
{
}

PConnection::~PConnection (void)
{
  ;
}



void
PConnection::set_manager(PConnectionManager * manager, int index)
{
  //ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);
  
  this->manager_ = manager;
  this->index_ = index;
}

void 
PConnection::set_protocol (PConnectionProtocol * protocol)
{
  //ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->lock_);
  
  this->protocol_ = protocol;
}
  
int 
PConnection::is_safe_to_delete (void)
{
  return !this->has_pending_io();
}

void 
PConnection::check (void)
{
  if (this->timeout_ == ACE_Time_Value::zero)
    return;

  ACE_Time_Value diff_time = ACE_OS::gettimeofday () - this->last_op_time_;

  if (diff_time < this->timeout_)
    return;

  this->cancel();
}

int
PConnection::initiate_read_stream (void)
{
  if (this->get_ref_cnt_r() != 0)
    return 0;
    
 
  // Inititiate read
  if (this->start_asynch_read(Buffer_Info (buf_),
                              sizeof(buf_)) == -1)
    {
      this->cancel();
      return -1;
    }

  this->ref_cnt_r_++;
  this->total_r_++;
  return 0;
}

int
PConnection::initiate_write_stream (const char *data,
                                    int         nbytes)
{
  if (this->get_ref_cnt_w() != 0)
    return 0;

  if (nbytes == 0)
    {
      this->cancel ();
      ACE_ERROR_RETURN((LM_ERROR,
          ACE_TEXT ("(%t) %s PConnection: attempt write 0 bytes\n"),
          this->get_name()),
          -1);
    }

  if (this->start_asynch_write (Buffer_Info (const_cast<char *>(data)),
                                nbytes) == 0)
    {
      this->ref_cnt_w_++;
      this->total_w_++;
      return 0;
    }

  this->cancel ();
  return -1;
}

void
PConnection::open (ACE_HANDLE handle, ACE_Message_Block &)
{
  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->on_open (handle);

    if (this->protocol_ != 0)
      this->protocol_->on_start();

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_connection(this);
}

void
PConnection::addresses (const ACE_Addr& peer, const ACE_Addr& local)
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
  return;
}

void
PConnection::handle_read_stream (const TRB_Asynch_Read_Stream::Result &result)
{
  this->trace_read_completion (result);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->update_last_time();

    this->ref_cnt_r_--;

    int              error = result.error();
    size_t      xfer_bytes = result.bytes_transferred ();

    this->total_rcv_ += xfer_bytes;

    if (error == 0 && this->protocol_ != 0) 
      {
        char *buf = result.get_buffer ();
        this->protocol_->on_read_finished (buf,
                                           xfer_bytes, 
                                           error);
      }
    else
      {
        this->cancel ();
      }
     
    if (!this->is_safe_to_delete ())
      return;
  }
  this->manager()->destroy_connection (this);
}

void
PConnection::handle_write_stream (const TRB_Asynch_Write_Stream::Result &result)
{
  this->trace_write_completion (result);

  {
    ACE_GUARD (ACE_SYNCH_MUTEX, monitor, this->mutex ());

    this->update_last_time();

    this->ref_cnt_w_--;

    int              error = result.error();
    size_t      xfer_bytes = result.bytes_transferred ();
    size_t       req_bytes = result.bytes_to_write ();

    this->total_snd_ += xfer_bytes;

    if (error == 0 && this->protocol_ != 0) 
      {
        char *buf = result.get_buffer ();
        if (xfer_bytes < req_bytes) // Process partial write
          {
            this->initiate_write_stream (buf + xfer_bytes, 
                                         req_bytes - xfer_bytes);
          }
        else  
          {
            this->protocol_->on_write_finished (buf,
                                                xfer_bytes,
                                                error);
          }
      }
    else
      {
        this->cancel ();
      }

    if (!is_safe_to_delete())
      return;
  }
  this->manager()->destroy_connection(this);
}


void
PConnection::trace_read_completion (const TRB_Asynch_Read_Stream::Result &result)
{
    int loglevel = this->config().loglevel ();

    size_t xfer_bytes = result.bytes_transferred();

    if (loglevel == 0)
    {
        LogLocker log_lock;

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) **** %s=%d handle_read_stream() ****\n"),
            this->get_name(),
            this->index()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_to_read = %d\n"),
            result.bytes_to_read ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("handle = %d\n"),
            result.handle ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_transfered = %d\n"),
            xfer_bytes));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("error = %d\n"),
            result.error ()));

        trace_buffers (result.get_buffer_info (), xfer_bytes, true);

    }
    else if (result.error () != 0 )
    {
        LogLocker log_lock;

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_OS::last_error (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
            ACE_TEXT ("(%t) %s=%d READ %p\n"),
            this->get_name (),
            this->index (),
            ACE_TEXT ("ERROR"));
    }
    else if (loglevel == 1)
    {
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) %s=%d read_bytes=%d OK\n"),
            this->get_name (),
            this->index (),
            xfer_bytes));
    }

    return;

}
void
PConnection::trace_write_completion (const TRB_Asynch_Write_Stream::Result &result)
{
    int loglevel = this->config().loglevel ();

    size_t xfer_bytes = result.bytes_transferred();

    if (loglevel == 0)
    {
        LogLocker log_lock;

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) **** %s=%d handle_write_stream() ****\n"),
            this->get_name(),
            this->index()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_to_write = %d\n"),
            result.bytes_to_write ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("handle = %d\n"),
            result.handle ()));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("bytes_transfered = %d\n"),
            xfer_bytes));

        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("error = %d\n"),
            result.error ()));

        trace_buffers (result.get_buffer_info (), xfer_bytes, false);

    }
    else if (result.error () != 0 )
    {
        LogLocker log_lock;

        ACE_Log_Msg::instance ()->errnum (result.error ());
        ACE_OS::last_error (result.error ());
        ACE_Log_Msg::instance ()->log (LM_ERROR,
            ACE_TEXT ("(%t) %s=%d WRITE %p\n"),
            this->get_name (),
            this->index (),
            ACE_TEXT ("ERROR"));
    }
    else if (loglevel == 1)
    {
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%t) %s=%d write_bytes=%d OK\n"),
            this->get_name (),
            this->index (),
            xfer_bytes));
    }
}

void
PConnection::trace_buffers(const Buffer_Info& buf_info,
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
          ACE_TEXT ("message_block [%d] length=%d:\n"), i, (int)len));

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
          ACE_TEXT ("iov[%d] length=%d:\n"), i, (int)len));

        ACE_HEX_DUMP ((LM_DEBUG, ptr, len));
      }
    }
  else // simple  buffer
    {
      char *ptr = buf_info.get_buffer ();
      ACE_DEBUG ((LM_DEBUG,
          ACE_TEXT ("buffer length=%d:\n"), (int)xfer_bytes));

      ACE_HEX_DUMP ((LM_DEBUG, ptr, xfer_bytes));
    }
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("**** end of buffers ****************\n")));
}
// *************************************************************
//  PConnectionManager  - container and object manager
//  for PConnection
// *************************************************************

PConnectionManager::PConnectionManager (ProactorTask &    task,
                                  PConnectionFactory & factory,
                                  const ACE_TCHAR * name)
  : lock_         (),
    task_         (task),
    factory_      (factory),
    name_         (name),
    total_snd_    (0),
    total_rcv_    (0),
    total_w_      (0),
    total_r_      (0),
    flg_cancel_   (0),
    num_connections_ (0),
    peak_connections_(0),
    timeout_      (ACE_Time_Value::zero),
    timer_id_     (-1)
{
  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
     this->list_connections_[i] = 0;
}

PConnectionManager::~PConnectionManager (void)
{
  //ACE_ASSERT(this->num_connections_ == 0);

  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      this->destroy_connection (i);
    }
}

void 
PConnectionManager::print_statistic(void)
{
  //Print statistic
  ACE_TCHAR bufs [256];
  ACE_TCHAR bufr [256];

  ACE_OS::sprintf (bufs, ACE_TEXT ("%lu(%lu)"),
                   this->get_total_snd (),
                   this->get_total_w ());

  ACE_OS::sprintf (bufr, ACE_TEXT ("%lu(%lu)"),
                   this->get_total_rcv (),
                   this->get_total_r ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s total bytes(operations): snd=%s rcv=%s\n"),
              this->get_name(),
              bufs,
              bufr));
}

int
PConnectionManager::is_safe_to_delete (void)
{
  ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_,0);

  return (this->num_connections_ == 0 && this->timer_id_ == -1);
}


void
PConnectionManager::cancel (void)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  this->flg_cancel_ = 1;

  this->cancel_timer ();

  // Propagate cancel to all connections
  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] != 0)
        {
            ACE_GUARD (ACE_SYNCH_MUTEX, monitor, list_connections_[i]->mutex());
            this->list_connections_[i]->cancel ();
        }
    }

  return;
}

void
PConnectionManager::check (void)
{
  //ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  // Propagate cancel to all connections
  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] != 0)
        {
            ACE_GUARD (ACE_SYNCH_MUTEX, monitor, list_connections_[i]->mutex());
            this->list_connections_[i]->check ();
        }
    }

  return;
}

void
PConnectionManager::cancel_timer (void)
{
  if (this->timer_id_ != -1)
    {
      int rc = this->task().get_proactor(0)->cancel_timer (this->timer_id_);

      if (rc != 0)
        this->timer_id_ = -1;
    }
}

void
PConnectionManager::start_timer (void) 
{
    if (this->should_finish())
      {
        if (this->is_safe_to_delete())
          this->task().signal_main();

        return;
      }

    if (this->timer_id_ != -1 ||
        this->timeout_ == ACE_Time_Value::zero)
      return;

    ACE_Time_Value abs_time = this->timeout_;

    this->timer_id_ = this->task().get_proactor(0)->schedule_timer (*this,
                                                               0,
                                                               abs_time);
}

void
PConnectionManager::handle_time_out ( const ACE_Time_Value & /* tv */,
                                   const void *   /* pArg */)
{
    ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

    //ACE_DEBUG((LM_DEBUG,
    //              ACE_TEXT ("(%t) %s handle timeout\n"),
    //              this->get_name ()));

    
    this->check();
    
    this->timer_id_ = -1;

    this->start_timer ();
}

void
PConnectionManager::set_timeout (const ACE_Time_Value & timeout)
{
    ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

    this->timeout_ = timeout;

    this->start_timer ();
}

PConnection *
PConnectionManager::create_connection (void)
{
  ACE_GUARD_RETURN (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_, 0);

  if (this->num_connections_ >= MAX_CONNECTIONS || 
      this->flg_cancel_ != 0)
    return 0;

  PConnection * connection = 0;

  for (u_int i = 0; i < MAX_CONNECTIONS; ++i)
    {
      if (this->list_connections_[i] != 0)
        continue;

      connection = this->factory_.create_connection(*this);

      if (connection == 0)
        break;

      this->list_connections_[i] = connection;
      this->num_connections_++;

      if (this->num_connections_ > this->peak_connections_)
        this->peak_connections_ = this->num_connections_;

      connection->set_manager (this,i);
      connection->set_timeout (this->timeout_);

      ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s=%d NEW %s=%d\n"),
              this->get_name(),
              this->num_connections_,
              connection->get_name(),
              i));

      PConnectionProtocol * protocol = 
        this->factory_.create_protocol (connection);

      connection->set_protocol (protocol);

      break;
    }

  return connection;
}

void
PConnectionManager::destroy_connection(PConnection * connection)
{
  if (!connection)
    return;

  u_int i = connection->index();

  ACE_ASSERT(connection->manager() == this);
  ACE_ASSERT(i < MAX_CONNECTIONS);
  ACE_ASSERT(connection == this->list_connections_[i]);

  this->destroy_connection (i);
}
  


void
PConnectionManager::destroy_connection(int index)
{
  ACE_GUARD (ACE_SYNCH_RECURSIVE_MUTEX, monitor, this->lock_);

  ACE_ASSERT(ACE_static_cast(u_int,index) < MAX_CONNECTIONS);

  PConnection * connection = this->list_connections_[index];

  if (!connection)
    return;
  
  this->total_snd_ += connection->get_total_snd();
  this->total_rcv_ += connection->get_total_rcv();
  this->total_w_   += connection->get_total_w();
  this->total_r_   += connection->get_total_r();

  this->factory_.destroy_protocol (connection->protocol ());
  connection->set_protocol (0);

  this->num_connections_--;
  this->list_connections_[index] = 0;


  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) %s=%d: DEL %s=%d S=%d(%d+%d) R=%d(%d+%d)\n"),
              this->get_name(),
              this->num_connections_,
              connection->get_name(),
              index,
              connection->get_total_snd(),
              connection->get_total_w(),
              connection->get_ref_cnt_w(),
              connection->get_total_rcv(),
              connection->get_total_r(),
              connection->get_ref_cnt_r()));

  connection->set_manager (0,-1);

  this->factory_.destroy_connection (connection) ;

  if (this->is_safe_to_delete())
    this->task().signal_main();
}

// *************************************************************
//  Acceptor
// *************************************************************
Acceptor::Acceptor  (PConnectionManager & manager)
: manager_        (manager)
{
}

Acceptor::~Acceptor (void)
{
}

int
Acceptor::start(const ACE_Addr & addr)
{
  int num_initial_accepts = 20; //5;
  
  int rc = this->open(addr,
                    0,   //size_t bytes_to_read = 0,
                    1,   //int pass_addresses = 0,
                    ACE_DEFAULT_BACKLOG, //int backlog ,
                    1,   //int reuse_addr = 1,
                    manager().task().get_proactor(0), // TRB_Proactor *proactor = 0,
                    1,   //int validate_new_connection = 0,
                    1,   //int reissue_accept = 1,
                    num_initial_accepts);
  
  return rc;
}



int
Acceptor::validate_connection(const TRB_Asynch_Accept::Result&  result,
                              const ACE_Addr& /*remote*/,
                              const ACE_Addr& /*local*/)
{
  int rc = 0;

  if (!result.success())
    {
      ACE_Errno_Guard g (errno);

      ACE_Log_Msg::instance ()->errnum (result.error ());
      ACE_OS::last_error (result.error ());

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) Acceptor: error=%d %p\n"),
                  (int) result.error(),
                  ACE_TEXT ("accept failed")));

      rc = -1;
    }
   return rc;
}

bool
Acceptor::is_safe_to_delete (void) const
{ 
  return (this->get_pending_count() == 0);
}

PConnection *
Acceptor::make_handler (void)
{
  return this->manager ().create_connection ();
}

// *************************************************************
//  Connector
// *************************************************************
Connector::Connector (PConnectionManager & manager)
: manager_        (manager)
{
}

Connector::~Connector (void)
{
}

bool
Connector::is_safe_to_delete (void) const
{ 
  return (this->get_pending_count() == 0);
}

int
Connector::start (const ACE_Addr& addr, u_int num)
{
  if (num > MAX_CONNECTIONS)
    num = MAX_CONNECTIONS;

  u_int rc = 0;

  if (this->open (1,  // int pass_addresses = 0,
                  manager().task().get_proactor(0), //TRB_Proactor *proactor = 0,
                  1    // int validate_new_connection = 0 );
                 )!= 0)
  {
     ACE_ERROR ((LM_ERROR,
                 ACE_TEXT ("(%t) Connector %p\n"),
                 ACE_TEXT ("open failed")));
     return rc;
  }

  for (; rc < num;  ++rc )
    {
      if (this->connect (addr, 
                         ACE_Addr::sap_any,
                         1 ,
                         (const void *) rc) != 0)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("(%t) Connector %p\n"),
                      ACE_TEXT ("connect start failed"))); 
          break;
        }
    }
  return (u_int) rc;
}


int
Connector::validate_connection(const TRB_Asynch_Connect::Result&  result,
                               const ACE_Addr& /*remote*/,
                               const ACE_Addr& /*local*/)
{
  int rc = 0;
  if (!result.success())
    {

      ACE_Errno_Guard g (errno);

      ACE_Log_Msg::instance ()->errnum (result.error ());
      ACE_OS::last_error (result.error ());

      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("(%t) Connector: error=%d %p\n"),
                  (int) result.error(),
                  ACE_TEXT ("connect failed")));

      rc = -1;

    }
  return rc;
}


PConnection *
Connector::make_handler (void)
{
  return this->manager ().create_connection ();
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class TRB_Asynch_Acceptor2<PConnection>;
template class TRB_Asynch_Connector2<PConnection>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate TRB_Asynch_Acceptor2<PConnection>
#pragma instantiate TRB_Asynch_Connector2<PConnection>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


