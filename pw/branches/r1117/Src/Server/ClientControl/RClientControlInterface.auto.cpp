#include "stdafx.h"
#include "RClientControlInterface.auto.h"

DEFINE_RE_FACTORY( clientCtl, RIInterface );

namespace rpc
{

template<>
void RegisterRemoteFactory(clientCtl::RIInterface* factory)
{
  &factory_clientCtl_RIInterface;
}

} // rpc

NI_DEFINE_REFCOUNT( clientCtl::RIInterface )
