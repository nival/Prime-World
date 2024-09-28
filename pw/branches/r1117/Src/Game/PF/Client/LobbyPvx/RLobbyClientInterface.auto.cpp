#include "stdafx.h"
#include "RLobbyClientInterface.auto.h"

DEFINE_RE_FACTORY( lobby, RILobbyUser );

namespace rpc
{

template<>
void RegisterRemoteFactory(lobby::RILobbyUser* factory)
{
  &factory_lobby_RILobbyUser;
}

} // rpc

NI_DEFINE_REFCOUNT( lobby::RILobbyUser )
