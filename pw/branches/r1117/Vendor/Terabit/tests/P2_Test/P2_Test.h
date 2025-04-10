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
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef ACE_TESTS_P2_TEST_H
#define ACE_TESTS_P2_TEST_H

#include "ace/INET_Addr.h"
#include "TProactor/Asynch_Acceptor.h"
#include "TProactor/Asynch_Connector.h"

#include "ProactorTask.h"


// *************************************************************
//
// *************************************************************

class Acceptor;
class Connector;
class Bridge;
class Receiver;
class Sender;

// *************************************************************
//   Session
// *************************************************************

class Session : public TRB_Service_Handler_T<ACE_Addr>
{
  friend class Bridge;

public:
  Session   (Bridge * bridge);
  ~Session  (void);

  virtual const ACE_TCHAR * get_name (void) const =0;
  virtual int on_open          (void) = 0;
  virtual int on_data_received (ACE_Message_Block & mb) = 0;
  virtual int on_data_sent     (ACE_Message_Block & mb) = 0;
  
  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }

  long get_total_w (void) const { return this->total_w_; }
  long get_total_r (void) const { return this->total_r_; }

  int get_ref_cnt_w (void) const { return this->ref_cnt_w_; }
  int get_ref_cnt_r (void) const { return this->ref_cnt_r_; }
  int get_ref_cnt   (void) const 
    { 
      return (this->ref_cnt_w_ +this->ref_cnt_r_);
    }






  // This is called to pass the new connection's addresses.
  virtual void addresses (const ACE_Addr& peer,
                          const ACE_Addr& local);

  /// This is called after the new connection has been accepted.
  virtual void open (ACE_HANDLE handle,
                     ACE_Message_Block &message_block);

  Bridge * bridge (void) const { return bridge_;}


  int  index  (void) const;
  void cancel (void);
  void close  (void);
  int  is_open(void) const;

protected:
  /// This is called when asynchronous <read> operation from the
  /// socket completes.
  virtual void handle_read_stream (const TRB_Asynch_Read_Stream::Result &result);

  /// This is called when an asynchronous <write> to the socket
  /// completes.
  virtual void handle_write_stream (const TRB_Asynch_Write_Stream::Result &result);

  int open_streams (ACE_HANDLE handle);
  int initiate_read_stream (void);
  int initiate_write_stream (ACE_Message_Block &mb, size_t nbytes);


//private:

  enum 
    {
      SSN_OPEN   = 0x0001,
      SSN_RCV_CLOSED = 0x0002,
      SSN_SND_CLOSED = 0x0004
    };

  Bridge * bridge_;

  TRB_Asynch_Read_Stream rs_;
  TRB_Asynch_Write_Stream ws_;
  ACE_HANDLE handle_;

  size_t total_snd_;         // Number of bytes successfully sent
  size_t total_rcv_;         // Number of bytes successfully received
  long total_w_;             // Number of finished write operations
  long total_r_;             // Number of finished read operations
  int  ref_cnt_w_;           // Number of pending write operations
  int  ref_cnt_r_;           // Number of pending read operations

  int  flags_;
};

// *************************************************************
//   Receiver
// *************************************************************

class Receiver : public Session
{
  //friend class Bridge;

public:
  Receiver  (Bridge * bridge = 0);
  ~Receiver (void);

  virtual const ACE_TCHAR * get_name (void) const;

  virtual int on_open          (void);
  virtual int on_data_received (ACE_Message_Block & mb);
  virtual int on_data_sent     (ACE_Message_Block & mb);
};
// *************************************************************
//  Sender
// *************************************************************

class Sender : public Session
{
  //friend class Connector;
public:

  Sender  (Bridge * bridge = 0);
  ~Sender (void);

  virtual const ACE_TCHAR * get_name (void) const;

  virtual int on_open          (void);
  virtual int on_data_received (ACE_Message_Block & mb);
  virtual int on_data_sent     (ACE_Message_Block & mb);

  /// This is called after the new connection has been established.
  virtual void handle_connect (const TRB_Asynch_Connect::Result &result);


  int connect(const ACE_Addr & addr);
  
protected:

  void parse_address (const TRB_Asynch_Connect::Result &result);

  TRB_Asynch_Connect asynch_connect_;
};

// *************************************************************
// Bridge
// *************************************************************

class Bridge 
{
  friend class Session;
  friend class Sender;
  
public: 

  enum
  {
    Q_R2S = 0,  // queue Receiver->Sender
    Q_S2R = 1   // queue Sender->Receiver
  };


  Bridge  (Acceptor & acceptor, int index);
  ~Bridge (void);

  ACE_SYNCH_MUTEX & mutex (void)   { return lock_;}
  Acceptor & acceptor (void) const { return acceptor_;}
  int index (void) const           { return index_;}
  int should_finish (void) const   { return flg_cancel_ ;}


  int putq (ACE_Message_Block & mb, int qtype);
  ACE_Message_Block * getq (int qtype);
  int qcount (int qtype);

  long cancel (void);
  long close  (void);

  int  on_data_received (ACE_Message_Block * mb, int qtype);
  int  on_data_sent     (ACE_Message_Block * mb, int qtype);

  int  on_accept(void);

  //long add_ref  (void); 
  //long dec_ref  (void); 

  Sender *   sender   (void) const {return this->sender_;}
  Receiver * receiver (void) const {return this->receiver_;}

protected:

  long check_ref(void);
  long try_destroy (void);
  int  check_flow  (int qtype);
  

  ACE_SYNCH_MUTEX lock_;
  Acceptor & acceptor_;
  int  index_;
  //int  ref_cnt_;       // Number of currently outstanding I/O requests
  int  flg_cancel_;

  ACE_Message_Queue<ACE_NULL_SYNCH>  queue_r2s_;
  ACE_Message_Queue<ACE_NULL_SYNCH>  queue_s2r_;

  Receiver * receiver_ ;
  Sender   * sender_ ;
};

// *************************************************************
// 
// *************************************************************


class Acceptor : public TRB_Asynch_Acceptor<Receiver>
{
  //friend class Bridge;

public:
  int get_number_bridges (void) const { return this->bridges_; }
  size_t get_total_snd (void) const { return this->total_snd_; }
  size_t get_total_rcv (void) const { return this->total_rcv_; }
  long get_total_w   (void) const { return this->total_w_; }
  long get_total_r   (void) const { return this->total_r_; }

  const ACE_Addr & addr_listen (void) const { return this->addr_listen_; }
  const ACE_Addr & addr_connect(void) const { return this->addr_connect_; }
  
  ProactorTask & task (void) const { return task_;}

  int should_finish (void) const   { return flg_cancel_ ;}


  Acceptor (ProactorTask &task);
  virtual ~Acceptor (void);

  int  start(const ACE_Addr & addr_listen,
             const ACE_Addr & addr_connect);
  void stop (void);
  void cancel_all (void);

  // Virtual from TRB_Asynch_Acceptor
  Receiver * make_handler (void);
  int validate_connection (const TRB_Asynch_Accept::Result & result,
                           const ACE_Addr & remote_addr,
                           const ACE_Addr & local_addr);

  int should_reissue_accept (void);

  void on_new_session    (Session * session);
  void on_delete_session (Session * session);
  void on_new_bridge     (Bridge  * bridge);
  void on_delete_bridge  (Bridge  * bridge);
  
private:

  ProactorTask & task_;
  ACE_SYNCH_RECURSIVE_MUTEX lock_;

  TRB_Sock_Addr addr_listen_;
  TRB_Sock_Addr addr_connect_;


  u_int bridges_;
  Bridge * list_bridges_[MAX_CONNECTIONS];

  size_t total_snd_;
  size_t total_rcv_;
  long total_w_;
  long total_r_;

  int  flg_cancel_;
};

#endif  /*ACE_TESTS_P2_TEST_H*/
