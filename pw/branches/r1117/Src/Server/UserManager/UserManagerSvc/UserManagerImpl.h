#pragma once
#include "UserManagerSvc/UserManagerIface.h"
#include "UserManagerSvc/IUserRegister.h"
#include "UserManagerSvc/UserNotificationIface.h"
#include "UserManagerSvc/RUserNotificationIface.auto.h"
#include "UserManagerSvc/UserContext.h"
#include "UserManagerSvc/PrepareUserEnvCtx.h"
#include "UserManagerSvc/IPrepareUserEnvNotify.h"
#include <RPC/IfaceRequester.h>
#include <RelayBalancer/RRelayBalancerIface.auto.h>
#include <map>
#include <list>
#include "nhash_map.h"


namespace Transport
{
  class IPerfCounters;
}


namespace UserManager
{
  class UserManagerImpl : public IUserManager, 
                          public IUserRegister,
                          public IUserNotificationPublisher,
                          public IPrepareUserEnvNotify,
                          public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_5(UserManagerImpl, IUserManager, IUserRegister, IUserNotificationPublisher, IPrepareUserEnvNotify, BaseObjectMT);

    typedef nstl::hash_map<Cluster::TUserId, StrongMT<UserContext> > UserContextsT;
    typedef nstl::hash_map<Cluster::TUserId, StrongMT<PrepareUserEnvCtx> > PrepUserEnvCtxsT;
    typedef std::list<StrongMT<PrepareUserEnvCtx> > PrepareUserEnvCtxListT;
    typedef std::map<string, StrongMT<UserContext> > SessionKey2UserT;
    typedef list<StrongMT<UserContext> > UserContextListT;

  public:
    UserManagerImpl( rpc::IfaceRequester<Relay::RIBalancer> * _relayBalancerIface, Transport::IPerfCounters * _perfCounters );
    ~UserManagerImpl();

  public:
    void Step();

    //  IUserManager
    bool AddUser(Cluster::TUserId _userId, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username);
    bool RemoveUser(Cluster::TUserId _userId);
    bool OnUserLeave(Cluster::TUserId _userId, Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole);
    UserSessionInfo FindUserSession(string const & _sessionKey, bool _partialReconnect);
    Result::Enum PrepareUserEnv(UserManager::UserEnvInfo const & _uei, UserManager::IPrepareUserEnvCallback* _cb);

    //  IUserNotificationPublisher
    SubscriberIdT RegisterSubscriber(IUserNotificationSubscriber* _s);
    void UnregisterSubscriber(SubscriberIdT _id, IUserNotificationSubscriber* _s);

    //  IUserRegister
    int RegisterUser(UserEnvInfo const & _uei);
    bool IsUserRegistered(Cluster::TUserId const & _userId);
    int UnregisterUser(Cluster::TUserId const & _userId);

    //  IPrepareUserEnvNotify
    void OnRelayAllocationInProgress(StrongMT<PrepareUserEnvCtx> const & ctx);
    void OnPrepareUserEnvCompleted(int rc, StrongMT<PrepareUserEnvCtx> const & ctx);

  private:
    void publishUser_(StrongMT<UserContext> const & uctx);
    void unpublishUser_(StrongMT<UserContext> const & uctx);

    int registerUser_(UserEnvInfo const & _uei);
    int unregisterUser_(Cluster::TUserId const & _userId);

  private:
    UserContextsT users_;
    PrepUserEnvCtxsT prepUserEnvCtxs_;
    PrepareUserEnvCtxListT preUserEnvCtx4Timeout_;
    SessionKey2UserT userShadows_;
    SessionKey2UserT users4PartialReconnect_;
    UserContextListT userShadowsByTime_;

    SubscriberIdT idCounter_;

    struct UserSubscriberContext
    {
      UserSubscriberContext()
      {
      }

      UserSubscriberContext(StrongMT<RIUserNotificationSubscriber> const & _iface)
        :iface_(_iface)
      {}

      StrongMT<RIUserNotificationSubscriber> iface_;
    };

    typedef nstl::map<SubscriberIdT, UserSubscriberContext> SubscribersT;
    SubscribersT subscribers_;

    StrongMT<rpc::IfaceRequester<Relay::RIBalancer> > relayBalancerIface_;

    WeakMT<Transport::IPerfCounters> perfCounters;
  };
}
