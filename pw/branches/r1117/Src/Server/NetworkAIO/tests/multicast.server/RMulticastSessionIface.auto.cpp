#include "stdafx.h"
#include "RMulticastSessionIface.auto.h"

static rpc::SimpleRemoteEntityFactory<MulticastTest::RIMulticastSession> factory_MulticastTest_RIMulticastSession;

namespace rpc
{

template<>
void RegisterRemoteFactory(MulticastTest::RIMulticastSession* factory)
{
  &factory_MulticastTest_RIMulticastSession;
}

} // rpc

NI_DEFINE_REFCOUNT( MulticastTest::RIMulticastSession )
