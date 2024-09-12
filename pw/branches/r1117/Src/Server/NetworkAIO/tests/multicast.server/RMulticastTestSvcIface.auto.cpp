#include "stdafx.h"
#include "RMulticastTestSvcIface.auto.h"

static rpc::SimpleRemoteEntityFactory<MulticastTest::RIMulticastSvc> factory_MulticastTest_RIMulticastSvc;

namespace rpc
{

template<>
void RegisterRemoteFactory(MulticastTest::RIMulticastSvc* factory)
{
  &factory_MulticastTest_RIMulticastSvc;
}

} // rpc

NI_DEFINE_REFCOUNT( MulticastTest::RIMulticastSvc )
