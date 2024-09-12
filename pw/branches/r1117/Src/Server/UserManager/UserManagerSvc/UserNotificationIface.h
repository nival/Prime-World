#pragma once
#include "UserInfo.h"

namespace UserManager
{
  typedef unsigned int SubscriberIdT;

  REMOTE class IUserNotificationSubscriber : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IUserNotificationSubscriber, rpc::IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnUserLoggedIn(UserInfo const & _uinfo) = 0;
    REMOTE virtual void OnUserLoggedOut(UserInfo const & _uinfo) = 0;
  };

  REMOTE class IUserNotificationPublisher : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IUserNotificationPublisher, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual SubscriberIdT RegisterSubscriber(NI_LPTR IUserNotificationSubscriber* _s) = 0;
    REMOTE virtual void UnregisterSubscriber(SubscriberIdT _id, NI_LPTR IUserNotificationSubscriber* _s) = 0;
  };
}
