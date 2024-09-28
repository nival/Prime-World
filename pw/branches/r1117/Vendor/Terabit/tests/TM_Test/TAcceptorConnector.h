// ============================================================================
//
// = LIBRARY
//    
//
// = FILENAME
//    TAcceptorConnector.h
//
// = DESCRIPTION
//
// = AUTHOR
//    Alexander Libman 
//
// ============================================================================
#ifndef TACCEPTOR_CONNECTOR_H
#define TACCEPTOR_CONNECTOR_H

#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Connector.h"
#include "ace/Acceptor.h"
#include "ace/Connector.h"

#include "TConnection.h"

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class TAcceptConnectHelper 
{
public:
    typedef ACE_SYNCH_RECURSIVE_MUTEX TMutex;

    bool   should_stop (void) const  { return flg_stop_;}

    int    stop ();
    int    is_safe_to_delete (void);
    int    wait ();

    TConnectionFactory & connection_factory (void) const { return this->con_factory_; }
    TConnectionManager & manager (void) const { return manager_; }

    TP_ReactorTask & task (void)   const;

  
    TMutex  & mutex (void) { return mtx_;}

protected:
    TAcceptConnectHelper (TConnectionFactory & con_factory,
                          TConnectionManager & manager);

    virtual ~TAcceptConnectHelper (void);


    TConnection * create_handler ();
    virtual int do_stop()=0;

    TMutex                mtx_;
    ACE_Thread_Semaphore  sem_;

    TConnectionFactory & con_factory_;
    TConnectionManager & manager_;
    bool                 flg_closed_;
    bool                 flg_stop_;
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class TAcceptor :  
  public TAcceptConnectHelper,
  public ACE_Acceptor<TConnection,ACE_SOCK_ACCEPTOR>
{
  typedef TAcceptConnectHelper BaseClass1;
  typedef ACE_Acceptor<TConnection,ACE_SOCK_ACCEPTOR> BaseClass2;

public:
  TAcceptor (TConnectionFactory & con_factory,
            TConnectionManager & manager);

  virtual ~TAcceptor (void);

  int    start(const ACE_INET_Addr & addr);
    
  //  virtual from ACE_Acceptor<>
  virtual int make_svc_handler (TConnection * & sh);

  virtual int handle_close (ACE_HANDLE h, ACE_Reactor_Mask mask);
  
  virtual int do_stop (void);
};

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
class TConnector : 
  public  TAcceptConnectHelper,
  public  ACE_Connector<TConnection,ACE_SOCK_CONNECTOR>
{
  typedef TAcceptConnectHelper BaseClass1;
  typedef ACE_Connector<TConnection,ACE_SOCK_CONNECTOR> BaseClass2;
public:
  TConnector (TConnectionFactory & con_factory,
              TConnectionManager & manager);

  virtual ~TConnector (void);

  int start (const ACE_INET_Addr &addr, int num);

 
  virtual int handle_close (ACE_HANDLE h, ACE_Reactor_Mask mask);
  
  virtual int do_stop (void);

  //  virtual from ACE_Connector<>
  virtual int make_svc_handler (TConnection * & sh);

};



#endif /* TACCEPTOR_CONNECTOR_H */
