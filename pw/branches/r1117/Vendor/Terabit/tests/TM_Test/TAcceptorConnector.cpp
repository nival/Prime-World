// ============================================================================
/**
 *  @file TAcceptorConnector.cpp
 *
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================


#include "TAcceptorConnector.h"
#include "TConnectionManager.h"
#include "TP_ReactorTask.h"


// *************************************************************
//  TAcceptConnectHelper
// *************************************************************
TAcceptConnectHelper::TAcceptConnectHelper (TConnectionFactory & con_factory,
                                          TConnectionManager & manager)
: mtx_            ()
, sem_            (0)
, con_factory_    (con_factory)
, manager_        (manager)
, flg_closed_     (false)
, flg_stop_       (false)
{
}

TAcceptConnectHelper::~TAcceptConnectHelper()
{
}

TP_ReactorTask & 
TAcceptConnectHelper::task (void)   const   
{
    return manager().task();
}

int
TAcceptConnectHelper::is_safe_to_delete (void)
{ 
  ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),0);

  return (this->flg_closed_);
}

int
TAcceptConnectHelper::wait (void)
{
    while (!is_safe_to_delete())
    {
        this->sem_.acquire ();
    }
    return 0;
}

int
TAcceptConnectHelper::stop(void)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),-1);

    flg_stop_ = true;

    ACE_Reactor * reactor = task ().reactor();
    if (reactor == 0)
    {
        sem_.release ();
        return 0;
    }
    return do_stop ();
}



TConnection *
TAcceptConnectHelper::create_handler (void)
{
   if (should_stop())
   {
       return 0;
   }
   return manager_.create_connection (con_factory_);
}
 

// *************************************************************
//  Acceptor
// *************************************************************
TAcceptor::TAcceptor(TConnectionFactory & con_factory,
                   TConnectionManager & manager)
: TAcceptConnectHelper (con_factory, manager)
{
}

TAcceptor::~TAcceptor (void)
{
}

int
TAcceptor::start(const ACE_INET_Addr & addr)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),-1);

    if (this->should_stop ())
    {
        return -1;
    }

    int rc = BaseClass2::open 
             (addr,
              this->task().tp_reactor(),
              ACE_NONBLOCK);
    
    if (rc < 0)
    {
        ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n",
                       "Acceptor::start () - open failed"),
                       -1);
    }
    return 0;
}


int
TAcceptor::handle_close (ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    {
        ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),-1);
        this->flg_closed_ = true;
    }
    this->sem_.release (1);
    return BaseClass2::handle_close (handle, mask);
}

int
TAcceptor::do_stop(void)
{
    BaseClass2::close ();
    this->reactor (0);
    return 0;
}




int 
TAcceptor::make_svc_handler (TConnection * & sh)
{
    sh = this->create_handler ();

    if (sh == 0)
    {
        return -1;
    }
    return 0;
}

// *************************************************************
//  Connector
// *************************************************************
TConnector::TConnector(TConnectionFactory & con_factory,
                     TConnectionManager & manager)
: TAcceptConnectHelper (con_factory, manager)
{
}

TConnector::~TConnector (void)
{
}

int
TConnector::start (const ACE_INET_Addr& addr, int num)
{
    ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),-1);

    if (this->should_stop ())
    {
        return -1;
    }
    int rc = BaseClass2::open (this->task().tp_reactor(),
                               ACE_NONBLOCK);
    
    if (rc < 0)
    {   
        ACE_ERROR_RETURN
            ((LM_ERROR,
              "%p\n",
              "Connector::start () - open failed"),
              -1);
    }

 
    ACE_Synch_Options opt(ACE_Synch_Options::USE_REACTOR,
                        ACE_Time_Value::zero);   //  (seconds,0));

    for (rc = 0 ; rc < num ; rc++)
    {
        TConnection * sender = 0;

        if (BaseClass2::connect (sender,
                     addr,
                     opt) < 0)
        {
          if ( ACE_OS::last_error() == EWOULDBLOCK)
            continue;

          ACE_ERROR_RETURN
            ((LM_ERROR,
              "%p\n",
              "Connector::start () - connect failed"),
              -1);
        }
    }

    return rc;
}

int
TConnector::handle_close (ACE_HANDLE handle, ACE_Reactor_Mask mask)

{
    {
        ACE_GUARD_RETURN (TMutex, monitor, this->mutex(),-1);
        this->flg_closed_ = true;
    }
    this->sem_.release (1);
    return BaseClass2::handle_close (handle, mask);
}

int
TConnector::do_stop(void)
{
    BaseClass2::close ();
    this->reactor (0);
    return 0;
}


int 
TConnector::make_svc_handler (TConnection * & sh)
{
    sh = this->create_handler ();

    if (sh == 0)
    {
        return -1;
    }
    return 0;
}

// **********************************************************************

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Acceptor<TConnection,ACE_SOCK_ACCEPTOR>;
template class ACE_Connector<TConnection,ACE_SOCK_CONNECTOR>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Acceptor<TConnection,ACE_SOCK_ACCEPTOR>
#pragma instantiate ACE_Connector<TConnection,ACE_SOCK_CONNECTOR>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

// **********************************************************************


