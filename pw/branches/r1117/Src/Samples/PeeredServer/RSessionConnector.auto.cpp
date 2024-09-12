#include "stdafx.h"
#include "RSessionConnector.auto.h"

static rpc::SimpleRemoteEntityFactory<Peered::RSessionConnector> factory_Peered_RSessionConnector;

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RSessionConnector* factory)
{
  &factory_Peered_RSessionConnector;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RSessionConnector )
