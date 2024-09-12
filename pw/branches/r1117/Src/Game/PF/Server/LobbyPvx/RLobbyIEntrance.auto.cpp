#include "stdafx.h"
#include "RLobbyIEntrance.auto.h"

DEFINE_RE_FACTORY( lobby, RIEntrance );

namespace rpc
{

template<>
void RegisterRemoteFactory(lobby::RIEntrance* factory)
{
  &factory_lobby_RIEntrance;
}

} // rpc

NI_DEFINE_REFCOUNT( lobby::RIEntrance )
