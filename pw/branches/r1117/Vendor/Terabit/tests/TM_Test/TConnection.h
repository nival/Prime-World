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

#ifndef TCONNECTION_H
#define TCONNECTION_H

#include "ace/INET_Addr.h"
#include "ace/Svc_Handler.h"
#include "ace/Synch.h"
#include "ace/SOCK_Stream.h"

//#include "ace/Atomic_Op_T.h"

#include "ace/OS_NS_sys_time.h"
#include "ace/OS_NS_string.h"

class TConnectionManager;
class TP_ReactorTask;
class TestCfg;
class TConnectionFactory;

class TConnection :
    public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:
    friend class TConnectionManager;
    
    typedef ACE_SYNCH_MUTEX TMutex;
    typedef ACE_Reverse_Lock<TMutex> TReverseMutex;
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> BaseClass;

    TConnection ();
    virtual ~TConnection ();

    long get_total_snd (void) { return this->total_snd_; }
    long get_total_rcv (void) { return this->total_rcv_; }
    long get_total_w   (void) { return this->total_w_; }
    long get_total_r   (void) { return this->total_r_; }
  
    TConnectionFactory *  factory (void) const { return factory_;}
    TConnectionManager *  manager (void) const { return mgr_;}
    int                   index   (void) const { return index_; }
    TP_ReactorTask &      task    (void) const;
    TestCfg &             config  (void) const;

    bool should_stop (void) const { return flg_stop_ ;}
    int  stop ();

    // virtual from ACE_Svc_Handler<>
    virtual int open (void * pVoid);

    // virtual from ACE_Event_Handler
    virtual int handle_input (ACE_HANDLE h);
    virtual int handle_output (ACE_HANDLE h);
    virtual int handle_close (ACE_HANDLE h , ACE_Reactor_Mask mask);

    // this should be pure virtual
    // get connection name
    virtual const ACE_TCHAR * get_name (void) const
    {
        return ""; 
    }

    virtual int  on_open () 
    {
        return -1;
    }

    virtual int on_read_finished (ACE_Message_Block & mb,
                                  int error,
                                  int xfer_bytes)
    {
        return -1;
    }

    virtual int on_write_finished (ACE_Message_Block & mb,
                                   int error)
    {
        return -1;
    }

    int start_read  (ACE_Message_Block & mb);
    int start_write (ACE_Message_Block & mb);


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
  
    void check ();

protected:
    ACE_Message_Block *  alloc_msg (void);
    void free_msg (ACE_Message_Block * mb);

private:

    void  setup (TConnectionFactory * factory,
                 TConnectionManager *  mgr,
                 int index);


    int  initiate_io (ACE_Reactor_Mask mask);
    ACE_Reactor_Mask  get_request_mask ();

    bool process_events ();
    int  do_read      ();
    int  do_write     ();


    void  trace_read  (ACE_Message_Block & mb,
                       int  req_bytes,
                       int  xfer_bytes,
                       int  error);

    void  trace_write (ACE_Message_Block & mb,
                       int  req_bytes,
                       int  xfer_bytes,
                       int  error);


    TMutex                mtx_;
    TConnectionFactory *  factory_;
    TConnectionManager *  mgr_;
    size_t                index_;
    int                   reactor_mask_;  // currently registered mask
    int                   ready_mask_;    // currently ready events

    long                  total_snd_;
    long                  total_rcv_;
    long                  total_w_;
    long                  total_r_;
    volatile bool         flg_stop_;
    ACE_Time_Value        last_op_time_;  // time of last activity
    ACE_Time_Value        timeout_;       // timeout value (0 means infinite)


    ACE_Message_Queue<ACE_NULL_SYNCH> mq_recv_;
    ACE_Message_Queue<ACE_NULL_SYNCH> mq_send_;
    //ACE_Message_Queue<ACE_NULL_SYNCH> * free_mq_;

    int                   in_count_;
    int                   out_count_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------

class TConnectionFactory 
{
public:
  virtual TConnection *  create_connection ()= 0;
  virtual void destroy_connection (TConnection * connection)=0;
};

template <class CON>
class  TConnectionFactory_T : public TConnectionFactory
{
public:
  virtual TConnection *  create_connection ()
  {
      TConnection * con = 0;
      ACE_NEW_RETURN (con, CON, 0);
      return con;
  }

  virtual void destroy_connection (TConnection * connection)
  {
      delete connection;
  }
};

#endif /* TCONNECTION_H */
