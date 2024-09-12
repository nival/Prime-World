#include "stdafx.h"
#include "RLobbyAccounting.auto.h"

DEFINE_RE_FACTORY( Lobby, RLobbyAccounting );

namespace rpc
{

template<>
void RegisterRemoteFactory(Lobby::RLobbyAccounting* factory)
{
  &factory_Lobby_RLobbyAccounting;
}

} // rpc

NI_DEFINE_REFCOUNT( Lobby::RLobbyAccounting )
