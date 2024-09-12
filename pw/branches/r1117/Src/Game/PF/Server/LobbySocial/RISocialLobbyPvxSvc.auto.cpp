#include "stdafx.h"
#include "RISocialLobbyPvxSvc.auto.h"

DEFINE_RE_FACTORY( socialLobby, RIPvxSvc );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RIPvxSvc* factory)
{
  &factory_socialLobby_RIPvxSvc;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RIPvxSvc )
