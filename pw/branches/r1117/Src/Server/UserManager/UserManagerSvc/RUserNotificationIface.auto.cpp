#include "stdafx.h"
#include "RUserNotificationIface.auto.h"

DEFINE_RE_FACTORY( UserManager, RIUserNotificationSubscriber );

namespace rpc
{

template<>
void RegisterRemoteFactory(UserManager::RIUserNotificationSubscriber* factory)
{
  &factory_UserManager_RIUserNotificationSubscriber;
}

} // rpc

NI_DEFINE_REFCOUNT( UserManager::RIUserNotificationSubscriber )
DEFINE_RE_FACTORY( UserManager, RIUserNotificationPublisher );

namespace rpc
{

template<>
void RegisterRemoteFactory(UserManager::RIUserNotificationPublisher* factory)
{
  &factory_UserManager_RIUserNotificationPublisher;
}

} // rpc

NI_DEFINE_REFCOUNT( UserManager::RIUserNotificationPublisher )
