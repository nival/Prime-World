#include "stdafx.h"
#include "RMulticastClientIface.auto.h"

static rpc::SimpleRemoteEntityFactory<MulticastTest::RIMulticastClient> factory_MulticastTest_RIMulticastClient;

namespace rpc
{

template<>
void RegisterRemoteFactory(MulticastTest::RIMulticastClient* factory)
{
  &factory_MulticastTest_RIMulticastClient;
}

} // rpc

NI_DEFINE_REFCOUNT( MulticastTest::RIMulticastClient )
