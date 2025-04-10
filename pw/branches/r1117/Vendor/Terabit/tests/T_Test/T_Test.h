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
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef ACE_TESTS_TP_REACTOR_TEST_H
#define ACE_TESTS_TP_REACTOR_TEST_H

#include "ace/OS.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Stream.h"
#include "ace/Acceptor.h"
#include "ace/Connector.h"
#include "ace/Svc_Handler.h"
#include "ace/Synch.h"


#include "Cfg.h"
#include "TP_ReactorTask.h"

// *************************************************************
//   Receiver and Acceptor
// *************************************************************
// forward declaration
class Acceptor;

class Receiver : public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
  friend class Acceptor;
public:

  Receiver (Acceptor * acceptor=0, int index=-1);

  ~Receiver (void);

  long get_total_snd (void) { return this->total_snd_; }
  long get_total_rcv (void) { return this->total_rcv_; }
  long get_total_w   (void) { return this->total_w_; }
  long get_total_r   (void) { return this->total_r_; }


  int should_finish (void) const { return flg_cancel_ != 0;}


  // virtual from ACE_Svc_Handler<>
  virtual int open (void * pVoid);

  // virtual from ACE_Event_Handler
  virtual int handle_input (ACE_HANDLE h);
  virtual int handle_output (ACE_HANDLE h);
  virtual int handle_close (ACE_HANDLE h , ACE_Reactor_Mask mask);

private:
  //int  terminate_io (ACE_Reactor_Mask mask);
  int  initiate_io (ACE_Reactor_Mask mask);
  int  check_destroy (void);

  Acceptor * acceptor_;
  size_t index_;
  int  flg_mask_;

  ACE_Recursive_Thread_Mutex mutex_;
  ACE_Message_Queue<ACE_NULL_SYNCH> mqn_;

  long total_snd_;
  long total_rcv_;
  long total_w_;
  long total_r_;
  int  flg_cancel_;
  int  in_count_;
  int  out_count_;
};

// *************************************************************

class Acceptor : public ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR>
{
 friend class Receiver;
public:
  size_t get_number_connections (void) { return connections_; }
  long get_total_snd (void) { return this->total_snd_; }
  long get_total_rcv (void) { return this->total_rcv_; }
  long get_total_w   (void) { return this->total_w_; }
  long get_total_r   (void) { return this->total_r_; }

  int should_finish (void) const { return flg_cancel_ != 0;}
  

  Acceptor (TP_ReactorTask & task);
  virtual ~Acceptor (void);

  int start (const ACE_INET_Addr & addr);
  int stop (void);
  int cancel_all();


  TP_ReactorTask & task () { return task_;}


  //  virtual from ACE_Acceptor<Receiver,ACE_SOCK_ACCEPTOR>
  virtual int make_svc_handler (Receiver * & sh);

private:

  TP_ReactorTask &  task_;

  ACE_Recursive_Thread_Mutex mutex_;

  size_t connections_;
  Receiver *list_connections_[MAX_CONNECTIONS];
  long total_snd_;
  long total_rcv_;
  long total_w_;
  long total_r_;
  int  flg_cancel_;

  void on_new_receiver (Receiver & rcvr);
  void on_delete_receiver (Receiver & rcvr);
};


// *******************************************
//   Sender
// *******************************************

class Connector;

class Sender : public ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>
{
  friend class Connector;

public:
  Sender (Connector * connector=0, int index=-1);

  ~Sender (void);

  long get_total_snd (void) { return this->total_snd_; }
  long get_total_rcv (void) { return this->total_rcv_; }
  long get_total_w   (void) { return this->total_w_; }
  long get_total_r   (void) { return this->total_r_; }

  int should_finish (void) const { return flg_cancel_ != 0;}

  // virtual from ACE_Svc_Handler<>
  virtual int open (void * pVoid);

  // virtual from ACE_Event_Handler
  virtual int handle_input (ACE_HANDLE h);
  virtual int handle_output (ACE_HANDLE h);
  virtual int handle_close (ACE_HANDLE h , ACE_Reactor_Mask mask);

private:
  //int  terminate_io (ACE_Reactor_Mask mask);
  int  initiate_io (ACE_Reactor_Mask mask);

  int  fill_queue (void);
  int  check_destroy (void);

  Connector * connector_;
  size_t  index_;
  int  flg_mask_;

  ACE_Recursive_Thread_Mutex mutex_;
  ACE_Message_Queue<ACE_NULL_SYNCH> mqn_;

  long total_snd_;
  long total_rcv_;
  long total_w_;
  long total_r_;
  int  flg_cancel_;
  int  in_count_;
  int  out_count_;
};

// *************************************************************

class Connector: public ACE_Connector<Sender,ACE_SOCK_CONNECTOR>
{
  friend class Sender;
public:
  long get_number_connections (void) { return connections_; }
  long get_total_snd (void) { return this->total_snd_; }
  long get_total_rcv (void) { return this->total_rcv_; }
  long get_total_w   (void) { return this->total_w_; }
  long get_total_r   (void) { return this->total_r_; }


  Connector (TP_ReactorTask & task);
  
  virtual ~Connector ();

  int  stop ();
  int  start (const ACE_INET_Addr & addr , int num);
  int  cancel_all();

  TP_ReactorTask & task () { return task_;}

  //  virtual from ACE_Connector<>
  virtual int make_svc_handler (Sender * & sh);

private:

  TP_ReactorTask &  task_;

  ACE_Recursive_Thread_Mutex mutex_;
  size_t  connections_;
  Sender * list_connections_ [MAX_CONNECTIONS];
  long total_snd_;
  long total_rcv_;
  long total_w_;
  long total_r_;
  int  flg_cancel_;

  void on_new_sender (Sender & sndr);
  void on_delete_sender (Sender & sndr);
};


#endif /* ACE_TESTS_TP_REACTOR_TEST_H */
