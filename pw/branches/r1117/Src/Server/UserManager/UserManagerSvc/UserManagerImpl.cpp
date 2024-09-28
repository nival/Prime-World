#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/UserManagerImpl.h"
#include "UserManagerSvc/UserManagerCfg.h"
#include "ServerAppBase/PerfCounters.h"


NI_DEFINE_REFCOUNT(UserManager::UserManagerImpl);

namespace UserManager
{
  namespace Instrumentation
  {
    NDebug::DebugVar<int> activeUsers("ActiveUsers", "UserManager");
  }

  UserManagerImpl::UserManagerImpl( rpc::IfaceRequester<Relay::RIBalancer> * _relayBalancerIface, Transport::IPerfCounters * _perfCounters ) :
  idCounter_(0),
  relayBalancerIface_(_relayBalancerIface),
  perfCounters( _perfCounters )
  {
  }

  UserManagerImpl::~UserManagerImpl()
  {
  }

  bool UserManagerImpl::AddUser(Cluster::TUserId _userId, string const & _sessionKey, Transport::TServiceId const & _sessionPath, wstring const & _username)
  {
    //FIXME: This function IS NOT CALLED from anywhere
    UserEnvInfo envinfo(_userId, _sessionKey, _sessionPath, _username, Cluster::INVALID_GAME_ID, false);
    int rc = registerUser_(envinfo);
    if (0 == rc)
    {
      LOG_M(UMLOG).Trace("User added(u=%d sk=%s)", _userId, _sessionKey);
    }
    else
    {
      LOG_W(UMLOG).Trace("User already exists(u=%d sk=%s)", _userId, _sessionKey);
    }
    return (rc >= 0);
  }

  bool UserManagerImpl::RemoveUser(Cluster::TUserId _userId)
  {
    bool result = (unregisterUser_(_userId) == 0);

    if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
        locked->AutoPerfCounterRate( "users_out_usrmgr", 1 );

    return result;
  }

  UserSessionInfo UserManagerImpl::FindUserSession(string const & _sessionKey, bool _partialReconnect)
  {
    LOG_M(UMLOG).Trace("%s (sessionKey=%s partialReconnect=%d)", __FUNCTION__, _sessionKey.c_str(), _partialReconnect);

    if (!_partialReconnect)
    {
      SessionKey2UserT::iterator it = userShadows_.find(_sessionKey);
      if (it != userShadows_.end())
      {
        StrongMT<UserContext> ctx = it->second;
        LOG_M(UMLOG).Trace("User shadow is found(u=%d sessionKey=%s)", ctx->userid(), ctx->sessionKey().c_str());

        userShadows_.erase(it);
        return UserSessionInfo(ctx->userid(), ctx->sessionPath(), _partialReconnect);
      }
    }
    else
    {
      SessionKey2UserT::iterator it = users4PartialReconnect_.find(_sessionKey);
      if (it != users4PartialReconnect_.end())
      {
        StrongMT<UserContext> ctx = it->second;
        LOG_M(UMLOG).Trace("User for partial reconnect is found(u=%d sessionKey=%s)", ctx->userid(), ctx->sessionKey().c_str());
        return UserSessionInfo(ctx->userid(), ctx->sessionPath(), _partialReconnect);
      }
    }

    return UserSessionInfo();
  }

  void UserManagerImpl::Step()
  {
    NHPTimer::FTime currtime = NHPTimer::GetScalarTime();

    //  process user shadows
    {
      NHPTimer::FTime userShadowLifetime = Cfg::GetUserShadowLifetime();
      UserContextListT::iterator it = userShadowsByTime_.begin();
      while(it != userShadowsByTime_.end() && currtime - (*it)->shadowTime() >= userShadowLifetime)
      {
        StrongMT<UserContext> ctx = *it;
        LOG_M(UMLOG).Trace("Remove user shadow(u=%d sessionKey=%s)", ctx->userid(), ctx->sessionKey().c_str());
        userShadows_.erase(ctx->sessionKey());
        it = userShadowsByTime_.erase(it);
        ctx = 0;
      }
    }

    //  process timeout for user environment preparation
    {
      NHPTimer::FTime allocateRelayCallbackTimeout = Cfg::GetAllocateRelayCallbackTimeout();
      PrepareUserEnvCtxListT::iterator it = preUserEnvCtx4Timeout_.begin();
      while(it != preUserEnvCtx4Timeout_.end() && currtime - (*it)->timemark() >= allocateRelayCallbackTimeout)
      {
        StrongMT<PrepareUserEnvCtx> ctx = *it;
        if (!ctx->isclosed())
        {
          LOG_W(UMLOG).Trace("Relay allocation callback timeout(u=%d sessionKey=%s)", ctx->userid(), ctx->sessionKey().c_str());
          ctx->Complete(UserManager::Result::RELAY_ALLOCATION_FAILED);
        }
        it = preUserEnvCtx4Timeout_.erase(it);
      }
    }
  }

  SubscriberIdT UserManagerImpl::RegisterSubscriber(IUserNotificationSubscriber* _s)
  {
    ++idCounter_;
    StrongMT<RIUserNotificationSubscriber> s = 
      StrongMT<RIUserNotificationSubscriber>(static_cast<RIUserNotificationSubscriber*>(_s));

    bool res = subscribers_.insert(make_pair(idCounter_, s)).second;
    if (!res)
    {
      LOG_E(UMLOG).Trace("Can't register subscriber: such id already exist(id=%d)", idCounter_);
    }

    return idCounter_;
  }

  void UserManagerImpl::UnregisterSubscriber(SubscriberIdT _id, IUserNotificationSubscriber* _s)
  {
  }

  void UserManagerImpl::publishUser_(StrongMT<UserContext> const & uctx)
  {
    for(SubscribersT::const_iterator it = subscribers_.begin(); 
      it != subscribers_.end(); ++it)
    {
      StrongMT<RIUserNotificationSubscriber> s = it->second.iface_;
      UserInfo ui(uctx->userid(), uctx->username());
      s->OnUserLoggedIn(ui);
    }
  }

  void UserManagerImpl::unpublishUser_(StrongMT<UserContext> const & uctx)
  {
    for(SubscribersT::const_iterator it = subscribers_.begin(); 
      it != subscribers_.end(); ++it)
    {
      StrongMT<RIUserNotificationSubscriber> s = it->second.iface_;
      UserInfo ui(uctx->userid(), uctx->username());
      s->OnUserLoggedOut(ui);
    }
  }

  Result::Enum UserManagerImpl::PrepareUserEnv(UserManager::UserEnvInfo const & _uei, UserManager::IPrepareUserEnvCallback* _cb)
  {
    LOG_M(UMLOG).Trace("%s(u=%d sessionKey=%s sessionPath=%s partialReconnect=%d)", 
      __FUNCTION__, _uei.userid_, _uei.sessionKey_.c_str(), _uei.sessionPath_.c_str(), _uei.partialReconnect_);

    if (_uei.partialReconnect_ && !Cfg::GetPartialReconnectSupport())
    {
      LOG_E(UMLOG).Trace("%s : partial reconnect is not supported(u=%d sessionKey=%s)", 
        __FUNCTION__, _uei.userid_, _uei.sessionKey_.c_str());

      return Result::PARTIAL_RECONNECT_NOT_SUPPORTED;
    }

    UserContextsT::iterator it = users_.find(_uei.userid_);
    if (it != users_.end())
    {
      StrongMT<UserContext> const & uctx = it->second;
      if (!_uei.partialReconnect_)
      {
        LOG_E(UMLOG).Trace("%s : user already registered(u=%d currentSessionKey=%s newSessionKey=%s)", 
          __FUNCTION__, _uei.userid_, uctx->sessionKey().c_str(), _uei.sessionKey_.c_str());
        return Result::USER_ALREADY_REGISTERED;
      }
      else
      {
        //  remove user context from partial reconnect list if user has no more retries
        if (0 == uctx->decPartialReconnectRetriesCount())
        {
          LOG_M(UMLOG).Trace("%s : user removed from partial reconnect(u=%d currentSessionKey=%s newSessionKey=%s)", 
            __FUNCTION__, _uei.userid_, uctx->sessionKey().c_str(), _uei.sessionKey_.c_str());

          users4PartialReconnect_.erase(uctx->sessionKey());
        }
      }
    }

    if (!relayBalancerIface_->isopen())
    {
      LOG_E(UMLOG).Trace("%s : no relay balancer(u=%d sessionKey=%s)", __FUNCTION__, _uei.userid_, _uei.sessionKey_.c_str());
      return Result::NO_RELAY_BALANCER;
    }

    StrongMT<PrepareUserEnvCtx> puectx = new PrepareUserEnvCtx(_uei, nival_cast<RIPrepareUserEnvCallback>(_cb), this, this, PartialReconnectSettings());

    if (prepUserEnvCtxs_.insert(pair<Cluster::TUserId, StrongMT<PrepareUserEnvCtx> >(_uei.userid_, puectx)).second)
    {
      relayBalancerIface_->iface()->AllocateRelay( puectx->gameid(), puectx->userid(), Transport::GetServicePath(puectx->sessionPath()), 
        (_uei.partialReconnect_ ? Coordinator::SecondarySvcRole : Coordinator::PrimarySvcRole), 
        puectx->userid(), RemotePtr<Relay::RIBalancerCallback>(puectx.Get()), 
        puectx.Get(), &PrepareUserEnvCtx::OnRelayAllocateReturn, puectx->userid(), Cfg::GetAllocateRelayReturnTimeout() );

      if ( StrongMT<Transport::IPerfCounters> locked = perfCounters.Lock() )
          locked->AutoPerfCounterRate( "users_inc_usrmgr", 1 );

      return Result::IN_PROGRESS;
    }
    else
    {
      LOG_E(UMLOG).Trace("%s : request for such user already registered(u=%d sessionKey=%s)",
        __FUNCTION__, _uei.userid_, _uei.sessionKey_.c_str());
      return Result::REQUEST_FOR_SUCH_USER_ALREADY_REGISTERED;
    }
  }

  int UserManagerImpl::registerUser_(UserEnvInfo const & _uei)
  {
    int rc = -1;
    StrongMT<UserContext> ctx = new UserContext(_uei.userid_, _uei.sessionKey_, _uei.sessionPath_, _uei.username_, 
      Cfg::GetPartialReconnectSupport(), Cfg::GetPartialReconnectRetries(), Cfg::GetPartialReconnectRetryTimeout());
    if (users_.insert(pair<Cluster::TUserId, StrongMT<UserContext> >(_uei.userid_, ctx)).second)
    {
      Instrumentation::activeUsers.AddValue(1);
      publishUser_(ctx);
      rc = 0;
    }
    return rc;
  }

  int UserManagerImpl::unregisterUser_(Cluster::TUserId const & _userId)
  {
    UserContextsT::iterator it = users_.find(_userId);
    if (it != users_.end())
    {
      StrongMT<UserContext> ctx = it->second;

      if (Cfg::GetUserShadowLifetime() > 0)
      {
        ctx->shadowTime(NHPTimer::GetScalarTime());
        userShadows_[ctx->sessionKey()] = ctx;
        userShadowsByTime_.push_back(ctx);

        LOG_M(UMLOG).Trace("User shadow is registered(u=%d sessionKey=%s to=%d)", 
          _userId, ctx->sessionKey().c_str(), Cfg::GetUserShadowLifetime());
      }
      users4PartialReconnect_.erase(ctx->sessionKey());
      unpublishUser_(ctx);
      users_.erase(it);

      Instrumentation::activeUsers.DecValue(1);

      LOG_M(UMLOG).Trace("User removed(u=%d sessionKey=%s)", _userId, ctx->sessionKey().c_str());
      return 0;
    }

    LOG_E(UMLOG).Trace("User is NOT found(u=%d)", _userId);
    return -1;
  }

  int UserManagerImpl::RegisterUser(UserEnvInfo const & _uei)
  {
    LOG_M(UMLOG).Trace("%s(u=%d sessionKey=%s)", __FUNCTION__, _uei.userid_, _uei.sessionKey_.c_str());
    return registerUser_(_uei);
  }

  bool UserManagerImpl::IsUserRegistered(Cluster::TUserId const & _userId)
  {
    return (users_.find(_userId) != users_.end());
  }

  int UserManagerImpl::UnregisterUser(Cluster::TUserId const & _userId)
  {
    LOG_M(UMLOG).Trace("%s(u=%d)", __FUNCTION__, _userId);

    return unregisterUser_(_userId);
  }

  void UserManagerImpl::OnRelayAllocationInProgress(StrongMT<PrepareUserEnvCtx> const & ctx)
  {
    if (Cfg::GetAllocateRelayCallbackTimeout())
    {
      ctx->timemark(NHPTimer::GetScalarTime());
      preUserEnvCtx4Timeout_.push_back(ctx);
    }
  }

  void UserManagerImpl::OnPrepareUserEnvCompleted(int _rc, StrongMT<PrepareUserEnvCtx> const & _ctx)
  {
    LOG_M(UMLOG).Trace("User environment preparation completed(u=%d rc=%d)", _ctx->userid(), _rc);
    prepUserEnvCtxs_.erase(_ctx->userid());
  }

  bool UserManagerImpl::OnUserLeave(Cluster::TUserId _userId, Transport::TServiceId const & _svcid, Coordinator::TServiceRole const & _svcrole)
  {
    LOG_M(UMLOG).Trace("%s(u=%d svcid=%s svcrole=%s)", __FUNCTION__, _userId, _svcid.c_str(), _svcrole.c_str());

    if (Coordinator::SecondarySvcRole != _svcrole)
      return false;

    UserContextsT::const_iterator cit = users_.find(_userId);
    if (users_.end() == cit)
    {
      LOG_W(UMLOG).Trace("%s. User not found(u=%d svcid=%s svcrole=%s)", __FUNCTION__, _userId, _svcid.c_str(), _svcrole.c_str());
      return false;
    }

    StrongMT<UserContext> ctx = cit->second;
    users4PartialReconnect_[ctx->sessionKey()] = ctx;

    LOG_M(UMLOG).Trace("User for partial reconnect is registered(u=%d sessionKey=%s)", _userId, ctx->sessionKey().c_str());
    return true;
  }
}
