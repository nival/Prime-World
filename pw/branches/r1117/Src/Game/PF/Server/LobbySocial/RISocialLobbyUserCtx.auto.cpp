#include "stdafx.h"
#include "RISocialLobbyUserCtx.auto.h"

DEFINE_RE_FACTORY( socialLobby, RIUserContext );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RIUserContext* factory)
{
  &factory_socialLobby_RIUserContext;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RIUserContext )
