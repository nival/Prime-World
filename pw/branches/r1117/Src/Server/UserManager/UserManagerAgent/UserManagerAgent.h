#pragma once
#include "UserManager/UserManagerSvc/UserNotificationIface.h"
#include "UserManager/UserManagerSvc/RUserNotificationIface.auto.h"
#include "UserManager/UserManagerAgent/IUserManagerAgent.h"
#include <RPC/IfaceRequester.h>
#include "System/nhash_map.h"

namespace UserManager
{
  class UserManagerAgent : public IUserManagerAgent,
                          public IUserNotificationSubscriber,
                          public rpc::IfaceRequesterCallback<RIUserNotificationPublisher>,
                          public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_4(UserManagerAgent, IUserManagerAgent, IUserNotificationSubscriber, rpc::IfaceRequesterCallback<RIUserNotificationPublisher>, BaseObjectMT);

    typedef nstl::hash_map<Cluster::TUserId, UserInfo> UsersInfoT;

  public:
    UserManagerAgent( rpc::GateKeeper * _gk, Coordinator::ServerIdT const & _srvid);
    ~UserManagerAgent();

  public:
    void Step();

    //  IUserManagerAgent
    bool FindUserName(Cluster::TUserId const & _userid, nstl::wstring & _username);
    bool RegisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber);
    void UnregisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber);

  protected:
    //  IUserNotificationSubscriber
    void OnUserLoggedIn(UserInfo const & _uinfo);
    void OnUserLoggedOut(UserInfo const & _uinfo);

  private:
    //  IfaceRequesterCallback<RIUserNotificationPublisher>
    void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<RIUserNotificationPublisher> > const & ifacereq);
    void OnRegisterSubscriberReturn(UserManager::SubscriberIdT result);

    void registerLogChannel(Coordinator::ServerIdT const & _srvid);

  private:
    typedef StrongMT<rpc::IfaceRequester<UserManager::RIUserNotificationPublisher> > UserPublisherIfaceReqT;
    UserPublisherIfaceReqT userPublisherIfaceReq_;

    UsersInfoT usersInfo_;
    threading::Mutex muxUsersInfo_;

    typedef vector<StrongMT<IUserManagerAgentSubscriber> > SubscribersT;
    SubscribersT subscribers_;

    StrongMT<NLogg::BasicTextFileDumper> fileDumper;
    Coordinator::ServerIdT srvid_;
  };
}
