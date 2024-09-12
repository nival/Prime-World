#include "stdafx.h"
#include "RISocialLobbyNotify.auto.h"

DEFINE_RE_FACTORY( socialLobby, RINotify );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RINotify* factory)
{
  &factory_socialLobby_RINotify;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RINotify )
