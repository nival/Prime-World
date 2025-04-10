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
//
// = LIBRARY
//    
//
// = FILENAME
//    PConnection.h
//
// = DESCRIPTION
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================
#ifndef PCONNECTION_H
#define PCONNECTION_H

#include "ProactorTask.h"

#include "TProactor/Asynch_Acceptor2.h"
#include "TProactor/Asynch_Connector2.h"
#include "ace/SString.h"


//----------------------------------------------------------
#include "ace/Version.h"

#if ((ACE_MAJOR_VERSION == 5) && (ACE_MINOR_VERSION ==3))

#include "ace/OS.h"

#else // Assume ACE 5.4.x

#include "ace/OS_NS_sys_time.h"

#endif // ((ACE_MAJOR_VERSION == 5) && (ACE_MINOR_VERSION ==3))
//----------------------------------------------------------

class PConnection;
class PConnectionProtocol;
class PConnectionManager;
class PConnectionFactory;

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class PConnectionManager : public TRB_Handler
{
  friend class PConnection;

public:
  int    get_number_connections (void) const { return this->num_connections_; }
  int    get_peak_connections (void) const { return this->peak_connections_; }

  // Sessions statistic
  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long   get_total_w   (void) const { return this->total_w_; }
  long   get_total_r   (void) const { return this->total_r_; }

  const ACE_TCHAR * get_name (void) const { return this->name_.c_str();}

  ACE_SYNCH_RECURSIVE_MUTEX  & mutex(void) { return this->lock_;}

  ProactorTask & task (void) { return task_;}

  PConnectionFactory & factory (void) { return factory_;}


  int    should_finish (void) const { return this->flg_cancel_;}
  int    is_safe_to_delete (void);
 
  // cancel method propagates cancel command to all 
  // active connections and prevents creation of new connections
  void   cancel (void);


  PConnection * create_connection (void);
  void       destroy_connection (PConnection * connection);
  void       destroy_connection (int index);

  PConnectionManager (ProactorTask &    task, 
                   PConnectionFactory & factory,
                   const ACE_TCHAR * name);

  virtual ~PConnectionManager  (void);

  void set_timeout (const ACE_Time_Value & timeout);

  const ACE_Time_Value& get_timeout (void) const
    {
      return this->timeout_;
    }

  // virtual from TRB_Handler
  void handle_time_out (const ACE_Time_Value & /* tv */,
                        const void *   /* pArg */);

  void print_statistic(void);

protected:
  // evictor pattern
  void check  (void);

  void cancel_timer (void);
  void start_timer (void);

  ACE_SYNCH_RECURSIVE_MUTEX lock_;
  ProactorTask &            task_;
  PConnectionFactory &         factory_;
  ACE_TString               name_;


  size_t total_snd_;  // Total bytes successfully sent
  size_t total_rcv_;  // Total bytes successfully received
  long   total_w_;    // Number of performed write operations
  long   total_r_;    // Number of performed read operations

  int    flg_cancel_; // Request to cancel

private:
  u_int                     num_connections_;
  u_int                     peak_connections_;
  PConnection *             list_connections_[MAX_CONNECTIONS];
  ACE_Time_Value            timeout_;
  long                      timer_id_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class PConnection : public  TRB_Service_Handler_T<ACE_Addr>
{
  friend class PConnectionManager;

public:

  typedef TRB_Asynch_Result::Buffer_Info Buffer_Info;

  PConnection  (void);
  ~PConnection (void);

  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long   get_total_w   (void) const { return this->total_w_; }
  long   get_total_r   (void) const { return this->total_r_; }
  int    get_ref_cnt_w (void) const { return this->ref_cnt_w_; }
  int    get_ref_cnt_r (void) const { return this->ref_cnt_r_; }


  ACE_SYNCH_MUTEX & mutex (void) { return this->lock_;}

  int    index (void) const { return this->index_; }

  PConnectionManager *  manager (void) const { return this->manager_; }

  PConnectionProtocol * protocol(void) const { return this->protocol_; }

  ProactorTask &  task (void) const { return this->manager()->task();}

  TestCfg & config (void) const { return this->task().config(); }


  int    has_pending_io (void) const
    { 
      return (get_ref_cnt_r() != 0 || get_ref_cnt_w() != 0);
    }

  void update_last_time (void)
    {
      this->last_op_time_  = ACE_OS::gettimeofday ();
    }

  void set_timeout (const ACE_Time_Value & timeout)
    {
      this->timeout_ = timeout;
    }

  const ACE_Time_Value& get_timeout (void) const
    {
      return this->timeout_;
    }
  
  int initiate_read_stream  (void);
  int initiate_write_stream (const char *data,
                             int nbytes);
  

  // this should be pure virtual
  // get connection name
  virtual const ACE_TCHAR * get_name (void) const
    { throw 0;}

  // this method is called when we have to force
  // cancellation of all outstanding requests 
  virtual void  cancel () 
    { throw 0;}

  virtual int start_asynch_read (const Buffer_Info& buf_info, size_t bytes)
    { throw 0;}
    
  virtual int start_asynch_write (const Buffer_Info& mb, size_t bytes)
    { throw 0;}


  virtual void on_open (ACE_HANDLE handle)
    { throw 0;}

  // this method is periodically called by PConnectionManager
  // when timeout is expired
  virtual void  check ();

  virtual int  is_safe_to_delete (void);


  /**
   * @name AIO callback handling
   *
   * These methods are called by the framework
   */

  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  /// virtual from TRB_Handler
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  /// virtual from TRB_Handler
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

  
  /// This is called to pass the new connection's addresses.
  /// virtual from ACE_Servce_Handler
  virtual void addresses (const ACE_Addr & peer,
                          const ACE_Addr & local);

  /// This is called after the new connection has been established
  /// virtual from ACE_Servce_Handler
  virtual void open (ACE_HANDLE handle, ACE_Message_Block & mb);

  ACE_Message_Block *  alloc_msg (void);
  void free_msg (ACE_Message_Block * mb);

protected:


  void trace_read_completion  (const TRB_Asynch_Read_Stream::Result &result);
  void trace_write_completion (const TRB_Asynch_Write_Stream::Result &result);
  void trace_buffers(const Buffer_Info& buf_info,
                     size_t xfer_bytes,
                     bool   flg_read);


  void set_manager  (PConnectionManager * manager, int index);
  void set_protocol (PConnectionProtocol * protocol);


  
  ACE_SYNCH_MUTEX lock_;

  PConnectionManager * manager_;
  int    index_;

  PConnectionProtocol * protocol_;


  int    ref_cnt_r_;         // Number of currently outstanding Read requests
  int    ref_cnt_w_;         // Number of currently outstanding Write requests
  size_t total_snd_;         // Total bytes successfully sent
  size_t total_rcv_;         // Total bytes successfully received
  long   total_w_;           // Number of performed write operations
  long   total_r_;           // Number of performed read operations
  ACE_Time_Value    last_op_time_;  // time of last activity
  ACE_Time_Value    timeout_;       // timeout value (0 means infinite)

  char  buf_ [4096];

};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class PConnectionProtocol
{
  friend class PConnection;

public:
  PConnection * get_connection(void) const {return connection_;}

  int read (void)
    {
      return (connection_) ? connection_->initiate_read_stream() : -1;
    }

  int write (const char *data, int length)
    {
      return (connection_) 
        ? connection_->initiate_write_stream (data, length)
        : -1;
    }
  
  PConnectionProtocol (PConnection * connection)
    : connection_(connection) 
    {;}

  virtual ~PConnectionProtocol (void)
    {;}
  

private:
  virtual void on_start ()=0;

  virtual void on_read_finished (const char *data,
                                 size_t bytes_transferred,
                                 int  error) = 0;

  virtual void on_write_finished (const char *data,
                                 size_t bytes_transferred,
                                 int  error) = 0;

  
  PConnection * connection_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class PConnectionFactory 
{
public:
  virtual PConnection*  create_connection(PConnectionManager & manager)=0;

  virtual PConnectionProtocol * create_protocol(PConnection * connection) =0;

  virtual void destroy_connection  (PConnection * connection) { delete connection;}
  virtual void destroy_protocol (PConnectionProtocol * protocol) { delete protocol;}
};


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class Acceptor :  public TRB_Asynch_Acceptor2<PConnection>
{
public:
  Acceptor (PConnectionManager & manager);
  virtual ~Acceptor (void);


  bool    is_safe_to_delete (void) const;


  PConnectionManager & manager (void)  { return this->manager_; }
  const PConnectionManager & manager (void) const  { return this->manager_; }

  ProactorTask & task (void)        { return manager().task();}

  
  int    start(const ACE_Addr & addr);


    

  virtual PConnection * make_handler (void);

  virtual int  validate_connection(const TRB_Asynch_Accept::Result&  result,
                           const ACE_Addr& remote,
                           const ACE_Addr& local );


protected:
  PConnectionManager & manager_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class Connector : public TRB_Asynch_Connector2<PConnection>
{
public:
  Connector (PConnectionManager & manager);
  virtual ~Connector (void);

  bool    is_safe_to_delete (void) const;

  PConnectionManager & manager (void)  { return this->manager_; }
  const PConnectionManager & manager (void) const  { return this->manager_; }

  ProactorTask & task (void)        { return manager().task();}


  int    start (const ACE_Addr &addr, u_int num);

  

  virtual PConnection * make_handler (void);

  virtual int validate_connection(const TRB_Asynch_Connect::Result&  result,
                           const ACE_Addr& remote,
                           const ACE_Addr& local );

protected:
  PConnectionManager & manager_;
};

#endif //PCONNECTION_H
