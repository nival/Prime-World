#include "stdafx.h"
#include "RISessionHybridLink.auto.h"

DEFINE_RE_FACTORY( lobby, RISessionHybridLink );

namespace rpc
{

template<>
void RegisterRemoteFactory(lobby::RISessionHybridLink* factory)
{
  &factory_lobby_RISessionHybridLink;
}

} // rpc

NI_DEFINE_REFCOUNT( lobby::RISessionHybridLink )
