#pragma once

#include "ServerAppBase/ServerRunner.h"

namespace MulticastTest
{
  class Service;

  class ServiceRunner : public Transport::IServerRunner, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ServiceRunner, BaseObjectMT )

  public:
    ServiceRunner();

    //IServerRunner
    virtual void StartInstance( const Transport::TServiceId& serviceId, Transport::ITransportSystem* _transport, 
      Network::INetworkDriver* _netdrv, Coordinator::ICoordinatorClient* _coordClient );
    virtual void StopInstance( const Transport::TServiceId& serviceId );
    virtual void SetOptions( const set<string>& options );

  private:
    vector<Transport::TServiceId>  interfaces;
    StrongMT<MulticastTest::Service> svc_;
  };

}
