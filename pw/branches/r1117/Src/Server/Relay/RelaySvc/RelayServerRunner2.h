#pragma once

#include "ServerAppBase/ServerRunner.h"
#include "RelayServer2.h"

namespace Coordinator
{
  class RelayBalancer;
}

namespace Relay
{

class RelayServerRunner2 : public Transport::IServerRunner, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( RelayServerRunner2, BaseObjectMT );

public:
  RelayServerRunner2();
  ~RelayServerRunner2();

  virtual void StartInstance( const Transport::ServiceParams & _params );
  virtual void StopInstance( const Transport::TServiceId& serviceId );
  virtual void SoftStopInstance(Transport::TServiceId const & _svcid);
  virtual Coordinator::TServiceRole const & GetRole() const { return svcrole; }

private:
  typedef map<Transport::TServiceId, StrongMT<threading::JobThread> > TServerInstances;
  TServerInstances instances;

  Coordinator::TServiceRole svcrole;
};

} //namespace Relay
