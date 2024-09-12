#include "UserManagerAgent/stdafx.h"
#include "UserManagerAgent/UserManagerAgent.h"
#include "UserManagerSvc/UserManagerNaming.h"

NI_DEFINE_REFCOUNT(UserManager::UserManagerAgent);

namespace UserManager
{
  UserManagerAgent::UserManagerAgent( rpc::GateKeeper * _gk, Coordinator::ServerIdT const & _srvid )
    :srvid_(_srvid)
  {
    registerLogChannel(_srvid);

    userPublisherIfaceReq_ = new rpc::IfaceRequester<UserManager::RIUserNotificationPublisher>;
    int rc = userPublisherIfaceReq_->init(_gk, UserManager::ServiceClass, UserManager::UserPublisherRpcIface, 
      &GetSystemLog(), UMALOG, this);
    if (rc < 0)
    {
      LOG_A(UMALOG).Trace("Can't init rpc iface requester(node=%s iface=%s)", 
        UserManager::ServiceClass.c_str(), UserManager::UserPublisherRpcIface);
    }
  }

  UserManagerAgent::~UserManagerAgent()
  {
  }

  void UserManagerAgent::Step()
  {
    userPublisherIfaceReq_->step();
  }

  void UserManagerAgent::OnUserLoggedIn(UserInfo const & _uinfo)
  {
    LOG_M(UMALOG).Trace("%s(u=%d n=%s)", __FUNCTION__, _uinfo.userid_, _uinfo.username_.c_str());

    bool res = false;
    {
      threading::MutexLock lock(muxUsersInfo_);
      res = usersInfo_.insert(nstl::make_pair(_uinfo.userid_, _uinfo)).second;
    }

    if (res)
    {
      for (SubscribersT::const_iterator cit = subscribers_.begin(); cit != subscribers_.end(); ++cit)
      {
        (*cit)->OnUserLoggedIn(_uinfo);
      }
    }
    else
    {
      LOG_E(UMALOG).Trace("%s. User already exists(u=%d n=%s)", __FUNCTION__, _uinfo.userid_, _uinfo.username_.c_str());
    }
  }

  void UserManagerAgent::OnUserLoggedOut(UserInfo const & _uinfo)
  {
    LOG_M(UMALOG).Trace("%s(u=%d n=%s)", __FUNCTION__, _uinfo.userid_, _uinfo.username_.c_str());

    bool res = false;
    {
      threading::MutexLock lock(muxUsersInfo_);
      UsersInfoT::iterator it = usersInfo_.find(_uinfo.userid_);
      res = (it != usersInfo_.end());
      if (res)
        usersInfo_.erase(it);
    }

    if (res)
    {
      for (SubscribersT::const_iterator cit = subscribers_.begin(); cit != subscribers_.end(); ++cit)
      {
        (*cit)->OnUserLoggedOut(_uinfo);
      }
    }
    else
    {
      LOG_W(UMALOG).Trace("%s. User not found(u=%d n=%s)", __FUNCTION__, _uinfo.userid_, _uinfo.username_.c_str());
    }
  }

  void UserManagerAgent::onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<RIUserNotificationPublisher> > const & ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == st)
    {
      ifacereq->iface()->RegisterSubscriber(this, this, &UserManagerAgent::OnRegisterSubscriberReturn);
    }
  }

  void UserManagerAgent::OnRegisterSubscriberReturn(UserManager::SubscriberIdT result)
  {
    result;
  }

  bool UserManagerAgent::FindUserName(Cluster::TUserId const & _userid, nstl::wstring & _username)
  {
    threading::MutexLock lock(muxUsersInfo_);
    UsersInfoT::iterator it = usersInfo_.find(_userid);
    if (it != usersInfo_.end())
    {
      _username = it->second.username_;
      return true;
    }

    return false;
  }

  bool UserManagerAgent::RegisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber)
  {
    if (subscribers_.end() != subscribers_.find(_subscriber))
      return false;

    subscribers_.push_back(_subscriber);
    return true;
  }

  void UserManagerAgent::UnregisterSubscriber(StrongMT<IUserManagerAgentSubscriber> const & _subscriber)
  {
    SubscribersT::iterator it = subscribers_.find(_subscriber);
    if (subscribers_.end() == it)
      return;

    subscribers_.erase(it);
  }

  void UserManagerAgent::registerLogChannel(Coordinator::ServerIdT const & _srvid)
  {
    //  create log filename postfix
    nstl::string logFilePostfix = UMALOG;
    logFilePostfix += "_";
    logFilePostfix += NStr::StrFmt("%d", (int)_srvid);

    fileDumper = NLogg::BasicTextFileDumper::New( 0, logFilePostfix.c_str() );

    StrongMT<NLogg::CDumper> stdoutDumper = GetSystemLog().FindDumperByName("stdout");
    if (stdoutDumper)
      GetSystemLog().AddChannel( UMALOG, fileDumper, stdoutDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
    else
      GetSystemLog().AddChannel( UMALOG, fileDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
  }
}
