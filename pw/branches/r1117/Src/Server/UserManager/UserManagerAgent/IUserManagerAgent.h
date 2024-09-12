#pragma once

#include <UserManager/UserManagerSvc/UserInfo.h>

namespace UserManager
{
  class IUserManagerAgentSubscriber : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IUserManagerAgentSubscriber, IBaseInterfaceMT );

  public:
    virtual void OnUserLoggedIn(UserInfo const & _uinfo) = 0;
    virtual void OnUserLoggedOut(UserInfo const & _uinfo) = 0;
  };

  class IUserManagerAgent : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IUserManagerAgent, IBaseInterfaceMT );

  public:
    virtual bool FindUserName(Cluster::TUserId const & _userid, nstl::wstring & _username) = 0;

    virtual bool RegisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber) = 0;
    virtual void UnregisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber) = 0;
  };
}
