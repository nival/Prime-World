#include "stdafx.h"
#include "RLobbyIServerInstance.auto.h"

DEFINE_RE_FACTORY( lobby, RIServerInstance );

namespace rpc
{

template<>
void RegisterRemoteFactory(lobby::RIServerInstance* factory)
{
  &factory_lobby_RIServerInstance;
}

} // rpc

NI_DEFINE_REFCOUNT( lobby::RIServerInstance )
