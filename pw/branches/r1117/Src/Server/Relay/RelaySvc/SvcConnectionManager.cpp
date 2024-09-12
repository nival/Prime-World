#pragma warning( disable : 4996)
#include "stdafx.h"
#include "IOTerabit/ChannelManager.h"
#include "IOTerabit/Protocol.h"
#include "TransportMessagesHeaders.h"
#include "BaseChannel.h"
#include "SvcConnectionManager.h"
#include "RelayServer2Cfg.h"

using namespace Terabit;
using namespace Transport;

namespace Relay
{

SvcConnectionManager::SvcConnectionManager(IOThreadPool &     task,
                                          ProtocolFactory &  protocol_factory,
                                          ChannelManager &   manager,
                                          ISvcAddressResolver* resolver)
  :ChannelConnector(task, protocol_factory, manager),
  task_(task),
  protocol_factory_(protocol_factory),
  manager_(manager),
  resolver_(resolver)
{
}

SvcConnectionManager::~SvcConnectionManager()
{
}

int SvcConnectionManager::Connect(ICallback* pcb, BackendContextWeakPtr & wpbc)
{
  ACE_Guard<ACE_Thread_Mutex>  lock(servicesMutex_);

  int rc = -1;
  TServiceId const & svcid = pcb->svcid();
  Services2CtxT::iterator sit = services_.find(svcid);
  if (services_.end() != sit)
  {
    BackendCtxsT* backendCtxs = &(sit->second);
    if (backendCtxs->size())
    {
      for(BackendCtxsT::iterator it = backendCtxs->begin(); it != backendCtxs->end() && rc < 0; )
      {
        BackendContextSP spbc = (*it).strong();
        if (!spbc.null() && !spbc->isclosed())
        {
          if (0 == RelayServer2Cfg::GetChannelsPerBackendConnection() || 
              spbc->UnicastPipeCount() <= RelayServer2Cfg::GetChannelsPerBackendConnection())
          {
            ACE_ERROR((LM_INFO, ACE_TEXT("%s: backend connection found(svc=%s svctx=%d svcpipes=%d svcpipesMax=%d svctxCount=%d)"), 
              __FUNCTION__, svcid.c_str(), spbc->id(), spbc->UnicastPipeCount(), 
              RelayServer2Cfg::GetChannelsPerBackendConnection(), backendCtxs->size()));

            wpbc = spbc;
            rc = 1;
          }

          ++it;
        }
        else
        {
          it = backendCtxs->erase(it);

          if (!spbc.null())
            ACE_ERROR((LM_INFO, ACE_TEXT("%s: remove backend context(svc=%s svctx=%d svcpipes=%d svcpipesMax=%d svctxCount=%d)"), 
              __FUNCTION__, svcid.c_str(), spbc->id(), spbc->UnicastPipeCount(), 
              RelayServer2Cfg::GetChannelsPerBackendConnection(), backendCtxs->size()));
          else
            ACE_ERROR((LM_INFO, ACE_TEXT("%s: remove backend context(svc=%s svcpipesMax=%d svctxCount=%d)"), 
              __FUNCTION__, svcid.c_str(), RelayServer2Cfg::GetChannelsPerBackendConnection(), backendCtxs->size()));
        }
      }
    }
  }
  else
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("%s. Connection to service NOT found(svc=%s)"), 
      __FUNCTION__, svcid.c_str()));
  }

  if (rc < 0)
  {
    cbqueue_t* cbq = &(svc2cb_[svcid]);
    if (!cbq->current_)
    {
      rc = Connect_(pcb);
    }
    else
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s. Connect to service ENqueued(svc=%s pcb=%d)"), 
        __FUNCTION__, svcid.c_str(), pcb));

      cbq->queue_.push_back(pcb);
      rc = 0;
    }
  }

  return rc;
}

bool SvcConnectionManager::IsKnownService(Transport::TServiceId const & svcid)
{
  TRB_Sock_Addr saddr;
  return resolver_->ResolveSvcAddress(svcid, saddr);
}

int SvcConnectionManager::Connect_(ICallback* pcb)
{
  int rc = -1;
  TServiceId const & svcid = pcb->svcid();
  TRB_Sock_Addr saddr;
  if (resolver_->ResolveSvcAddress(svcid, saddr))
  {
    char svcIpAddrString[64] = "\0";
    saddr.to_string(&svcIpAddrString[0], sizeof(svcIpAddrString)-1);

    cbqueue_t* cbq = &(svc2cb_[svcid]);
    cbq->current_ = pcb;  // выставляем не после if(0==rc) 
                          // т.к. к тому моменту операция уже может завершиться

    rc = ChannelConnector::start(saddr, pcb);
    if (0 == rc)
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("Connect to service started(svc=%s ip=%s)"), 
                 svcid.c_str(), svcIpAddrString));
    }
    else
    {
      ACE_ERROR((LM_ERROR, ACE_TEXT("%s. Connect to service FAILED(svc=%s ip=%s)"), 
                 __FUNCTION__, svcid.c_str(), svcIpAddrString));
      cbq->current_ = 0;
    }
  }
  else
  {
    ACE_ERROR((LM_INFO, ACE_TEXT("Can't resolve service address(svc=%s pcb=%d)"), 
              svcid.c_str(), pcb));
  }

  return rc;
}

void SvcConnectionManager::OnConnectionCompleted(ICallback* pcb, BackendContextWeakPtr wpctx)
{
  ACE_Guard<ACE_Thread_Mutex>  lock(servicesMutex_);

  Transport::TServiceId const & svcid = pcb->svcid();
  Svc2CallbacksT::iterator it = svc2cb_.find(svcid);
  cbqueue_t* cbq = 0;
  if (it != svc2cb_.end())
  {
    cbq = &(it->second);
    ACE_ASSERT(pcb == cbq->current_);
  }
  else
  {
    ACE_ERROR((LM_CRITICAL, ACE_TEXT("%s: can't find service callback(svc=%s pcb=%d)"), 
      __FUNCTION__, svcid.c_str(), pcb));
  }

  BackendContextSP spctx = wpctx.strong();
  if (!spctx.null())
  {
    bool newconnection = true;
    BackendCtxsT* ctxs = &(services_[svcid]);
    for(BackendCtxsT::iterator it = ctxs->begin(); it != ctxs->end(); ++it)
    {
      BackendContextWP const & wpbc = *it;
      BackendContextSP const & spbc = wpbc.strong();
      if (!spbc.null() && spbc == spctx)
      {
        newconnection = false;
        break;
      }
    }

    if (newconnection)
    {
      ACE_ERROR((LM_INFO, ACE_TEXT("%s: new backend connection registered(svc=%s svctx=%d svcpipes=%d svcpipesMax=%d svctxCount=%d)"), 
        __FUNCTION__, svcid.c_str(), spctx->id(), spctx->UnicastPipeCount(), RelayServer2Cfg::GetChannelsPerBackendConnection(), ctxs->size()));

      ctxs->push_front(wpctx);
    }

    //  notify other callbacks
    if (cbq)
    {
      for(CallbackQueueT::iterator qit=cbq->queue_.begin();
        qit != cbq->queue_.end();
        ++qit)
      {
        (*qit)->callback(0, wpctx);
      }
      cbq->queue_.clear();
      cbq->current_ = 0;
    }
  }
  else
  {
    ACE_ERROR((LM_WARNING, ACE_TEXT("%s: backend context already null(svc=%s pcb=%d)"), 
      __FUNCTION__, svcid.c_str(), pcb));
  }
}

int SvcConnectionManager::on_connect_completed(const TRB_Asynch_Connect::Result &result)
{
  //
  //  copy/paste of ChannelConnector::on_connect_completed() because we can't call it
  //
  {
    bool  success = result.success ();
    const void * act = result.act ();

    const ACE_Addr& local_addr  = result.local_address ();
    const ACE_Addr& remote_addr = result.remote_address ();

    int rc = this->protocol_factory_.validate_connection (success,
      remote_addr,
      local_addr,
      act);
    if (!success || rc != 0)  // accept/connect failure
    {                         // or factory rejected to process
      //  <-- changes here : begin -->
      ICallback* cb = const_cast<ICallback*>(reinterpret_cast<ICallback const *>(result.act()));

      ACE_TCHAR str_peer [256];
      ACE_TCHAR str_local[256];
      TRB_Sock_Addr::to_string (remote_addr, str_peer, sizeof (str_peer)/sizeof (ACE_TCHAR));
      TRB_Sock_Addr::to_string (local_addr, str_local, sizeof (str_local)/sizeof (ACE_TCHAR));
      Transport::TServiceId svcid = cb->svcid();

      ACE_DEBUG ((LM_WARNING,
        ACE_TEXT ("Connect to service FAILED(svcid=%s err=%d remote=%s local=%s"),
        svcid.c_str(),
        result.error(),
        str_peer,
        str_local));

      cb->callback(result.error(), BackendContextWeakPtr());  //  <-- cb deleted here
      cb = 0;

      {
        ACE_Guard<ACE_Thread_Mutex>  lock(servicesMutex_);
        Svc2CallbacksT::iterator it = svc2cb_.find(svcid);
        if (it != svc2cb_.end())
        {
          //  notify other callbacks
          cbqueue_t* cbq = &(it->second);
          for(CallbackQueueT::iterator qit=cbq->queue_.begin();
            qit != cbq->queue_.end();
            ++qit)
          {
            (*qit)->callback(result.error(), BackendContextWeakPtr());
          }

          cbq->queue_.clear();
          cbq->current_ = 0;
        }
      }
      //  <-- changes here : end -->

      return -1;            // new connection
    }


    AsynchChannelPtr  channel = this->manager_.allocate_channel ();
    if (!channel)
    {
      return -1;
    }

    channel->addresses (remote_addr, local_addr);
    if (this->get_log_level () < 2)
    {
      ACE_TCHAR str_peer [256];
      ACE_TCHAR str_local[256];

      TRB_Sock_Addr::to_string (remote_addr, str_peer, sizeof (str_peer)/sizeof (ACE_TCHAR));
      TRB_Sock_Addr::to_string (local_addr, str_local, sizeof (str_local)/sizeof (ACE_TCHAR));

      ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("CONNECTED channel id=(C)%d remote=%s local=%s"),
        channel->get_id (),
        str_peer,
        str_local));
    }


    ACE_HANDLE handle = result.connect_handle ();
    rc = channel->open (handle, false);
    if (rc < 0)
    {
      return 0;  // open failed, but handle ownership must be taken
    }

    // ownership of handle is taken
    Protocol *protocol = protocol_factory_.create_protocol (act);

    if (!protocol)
    {
      channel->close ();
      return 0;
    }

    const ACE_Message_Block *mb   = result.get_message_block_ptr ();
    int                      len  = result.bytes_transferred ();
    const char              *data = mb ? mb->base () : 0;

    //  <-- changes here : begin -->
    (static_cast<BaseChannel*>(channel.get()))->activate_protocol (protocol, data, len);
    //  <-- changes here : end -->

    return 0;
  }
}

}
