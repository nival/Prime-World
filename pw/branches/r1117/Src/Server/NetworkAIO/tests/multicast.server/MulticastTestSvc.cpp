#include "stdafx.h"
#include "MulticastTestSvc.h"
#include "MulticastTestNaming.h"
#include "LMulticastSessionIface.auto.h"

namespace MulticastTest
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Service::Service( Transport::ITransportSystem * transport, const Transport::TServiceId& serviceId)
    :Network::GateKeeperService(transport, serviceId)
  {
    impl = new MulticastTestImpl(gateKeeper, transport);
    RegisterObject<IMulticastSvc>(impl.Get(), MulticastTest::ServiceIfaceId);

    rpcFactory->RegisterAttach<IMulticastSession, LIMulticastSession>();
  }

  Service::~Service()
  {
    if ( impl )
      gateKeeper->GetGate().UnregisterObject( impl );
  }

  void Service::Step()
  {
    impl->Step();
  }
}
