#include "stdafx.h"
#include "RISocialLobby.auto.h"

DEFINE_RE_FACTORY( socialLobby, RISocialInterface );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RISocialInterface* factory)
{
  &factory_socialLobby_RISocialInterface;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RISocialInterface )
DEFINE_RE_FACTORY( socialLobby, RIPvxInterface );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RIPvxInterface* factory)
{
  &factory_socialLobby_RIPvxInterface;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RIPvxInterface )
DEFINE_RE_FACTORY( socialLobby, RIDevSocLobby );

namespace rpc
{

template<>
void RegisterRemoteFactory(socialLobby::RIDevSocLobby* factory)
{
  &factory_socialLobby_RIDevSocLobby;
}

} // rpc

NI_DEFINE_REFCOUNT( socialLobby::RIDevSocLobby )
