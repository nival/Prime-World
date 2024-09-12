#pragma once

//#include <IOTerabit/ProtocolFactory_T.h>
#include <IOTerabit/ChannelConnector.h>
#include "System/nhash_fun.h"
#include "Network/TransportAddress.h"
#include "BackendContext.h"
#include <map>
#include <list>
#include "SvcAddressResolver.h"

namespace Relay
{

class BackendConnector;

class SvcConnectionManager : protected Terabit::ChannelConnector
{
public:

  class ICallback
  {
  public:
    virtual Transport::TServiceId const & svcid() const = 0;
    virtual void* act() const = 0;
    virtual void callback(int err, BackendContextWeakPtr wpctx) = 0;
  };

  typedef std::list<ICallback*> CallbackQueueT;

private:
  struct cbqueue_t
  {
    volatile ICallback* current_;
    CallbackQueueT  queue_;

    cbqueue_t() : current_(0) {}
  };

  typedef std::map<Transport::TServiceId, cbqueue_t> Svc2CallbacksT;

public:
  SvcConnectionManager (Terabit::IOThreadPool &     task,
    Terabit::ProtocolFactory &  protocol_factory, 
    Terabit::ChannelManager &   manager,
    ISvcAddressResolver* resolver);
  ~SvcConnectionManager();

public:
  bool IsKnownService(Transport::TServiceId const & svcid);
  int Connect(ICallback* cb, BackendContextWeakPtr & wpbc);
  /// вызывается когда соединение успешно установлено
  void OnConnectionCompleted(ICallback* pcb, BackendContextWeakPtr wpctx);

private:
  //  Terabit::ChannelConnector interface
  virtual int on_connect_completed(const TRB_Asynch_Connect::Result &result);

  //  internal interface
  int Connect_(ICallback* pcb);

private:

  typedef std::list<BackendContextWeakPtr> BackendCtxsT;
  typedef std::map<Transport::TServiceId, BackendCtxsT>  Services2CtxT;
  Services2CtxT  services_;
  ACE_Thread_Mutex  servicesMutex_;
  Svc2CallbacksT svc2cb_;

  ISvcAddressResolver*  resolver_;

  Terabit::IOThreadPool &    task_;
  Terabit::ProtocolFactory & protocol_factory_;
  Terabit::ChannelManager &  manager_;
};

}
