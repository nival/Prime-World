#include "stdafx.h"
#include "RPeered.auto.h"

DEFINE_RE_FACTORY( Peered, RIGameClient );

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RIGameClient* factory)
{
  &factory_Peered_RIGameClient;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RIGameClient )
DEFINE_RE_FACTORY( Peered, RIGameClientReconnect );

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RIGameClientReconnect* factory)
{
  &factory_Peered_RIGameClientReconnect;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RIGameClientReconnect )
DEFINE_RE_FACTORY( Peered, RIGameServer );

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RIGameServer* factory)
{
  &factory_Peered_RIGameServer;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RIGameServer )
DEFINE_RE_FACTORY( Peered, RIGameServerInternal );

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RIGameServerInternal* factory)
{
  &factory_Peered_RIGameServerInternal;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RIGameServerInternal )
DEFINE_RE_FACTORY( Peered, RIGameServerReconnect );

namespace rpc
{

template<>
void RegisterRemoteFactory(Peered::RIGameServerReconnect* factory)
{
  &factory_Peered_RIGameServerReconnect;
}

} // rpc

NI_DEFINE_REFCOUNT( Peered::RIGameServerReconnect )
