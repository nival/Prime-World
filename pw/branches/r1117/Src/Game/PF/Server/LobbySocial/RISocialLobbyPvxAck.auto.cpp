#include "stdafx.h"
#include "RISocialLobbyPvxAck.auto.h"

DEFINE_RE_FACTORY( socialLobby, RIPvxAcknowledge );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RIPvxAcknowledge* factory)
{
  &factory_socialLobby_RIPvxAcknowledge;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RIPvxAcknowledge )
