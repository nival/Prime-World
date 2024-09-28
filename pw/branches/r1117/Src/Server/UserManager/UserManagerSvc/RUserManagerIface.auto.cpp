#include "stdafx.h"
#include "RUserManagerIface.auto.h"

DEFINE_RE_FACTORY( UserManager, RIPrepareUserEnvCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(UserManager::RIPrepareUserEnvCallback* factory)
{
  &factory_UserManager_RIPrepareUserEnvCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( UserManager::RIPrepareUserEnvCallback )
DEFINE_RE_FACTORY( UserManager, RIUserManager );

namespace rpc
{

template<>
void RegisterRemoteFactory(UserManager::RIUserManager* factory)
{
  &factory_UserManager_RIUserManager;
}

} // rpc

NI_DEFINE_REFCOUNT( UserManager::RIUserManager )
