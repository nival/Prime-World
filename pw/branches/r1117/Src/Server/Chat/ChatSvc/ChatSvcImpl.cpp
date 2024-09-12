#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatSvcImpl.h"
#include "ChatSvc/ChatUserContext.h"
#include "ChatSvc/ChatSessionContext.h"
#include "ChatSvc/ChatSvcCfg.h"

namespace chat
{
  ChatSvcImpl::ChatSvcImpl()
    :autoincsid_(0),
    autouserid_(0)
  {
    censor_ = censorship::CreateClient();
  }

  ChatSvcImpl::~ChatSvcImpl()
  {
  }

  void ChatSvcImpl::Step()
  {
    if (Cfg::GetCensorCheck())
      censor_->Poll();

    for ( SessionsT::iterator it = sessions_.begin(); it != sessions_.end(); ++it )
    {
      SessionContext * sess = it->second;
      sess->Poll();
    }
  }

  void ChatSvcImpl::OpenSession(SessionInfo const & _si, IOpenSessionCallback* _cb)
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x)", __FUNCTION__, _si.sidGlobal_);
    if (!_cb)
    {
      LOG_E(CHATLOG).Trace("%s: callback is NULL(sidG=%016x)", __FUNCTION__, _si.sidGlobal_);
      return;
    }

    SessionId sidLocal = ++autoincsid_;
    StrongMT<SessionContext> ctx(new SessionContext(sidLocal, _si.sidGlobal_));
    pair<SessionsByGlobalIdT::iterator, bool> res = sessionsByGlobalId_.insert(make_pair(_si.sidGlobal_, ctx));
    if (!res.second)
    {
      LOG_E(CHATLOG).Trace("%s: session already registered with the same global id(sidG=%016x sidL=%d)", 
        __FUNCTION__, _si.sidGlobal_, res.first->second->sidLocal() );
      --autoincsid_;
      _cb->OnOpenSession(Result::ALREADY_EXISTS, INVALID_SESSION_ID);
      return;
    }

    for(ChannelInfosT::const_iterator it = _si.channels_.begin(); it != _si.channels_.end(); ++it)
    {
      StrongMT<ChannelContext> chnlctx(new ChannelContext(sidLocal, it->name_, _si.sidGlobal_, Cfg::GetChannelHistorySize(), censor_, it->ignoreUserMute_));
      ctx->addChannel(chnlctx);
    }

    if (!sessions_.insert(make_pair(sidLocal, ctx)).second)
    {
      LOG_E(CHATLOG).Trace("%s: session already registered with the same local id(sidL=%d sidG=%016x)", 
        __FUNCTION__, sidLocal, ctx->sidGlobal());

      --autoincsid_;
      sessionsByGlobalId_.erase(res.first);
      _cb->OnOpenSession(Result::ALREADY_EXISTS, INVALID_SESSION_ID);
      return;
    }

    _cb->OnOpenSession(Result::SUCCESS, ctx->sidLocal());
    return;
  }

  void ChatSvcImpl::CloseSession(SessionId _sid)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d)", __FUNCTION__, _sid);

    SessionsT::iterator it = sessions_.find(_sid);
    if (it == sessions_.end())
    {
      LOG_E(CHATLOG).Trace("%s: session NOT FOUND(sidL=%d)", __FUNCTION__, _sid);
      return;
    }

    StrongMT<SessionContext> const & sctx = it->second;
    if (sctx->close())
    {
      SessionContext::ChannelsT const & chnls = sctx->channels();
      SessionContext::ChannelsT::const_iterator cit = chnls.begin();
      for(; cit != chnls.end(); ++cit)
      {
        StrongMT<ChannelContext> cctx = cit->second;
        if (!cctx->isclosed())
          break;
      }
      if (chnls.end() == cit)
      {
        //  all channels closed -> close session
        sessions_.erase(it);
        sessionsByGlobalId_.erase(sctx->sidGlobal());
      }
    }
    else
    {
      LOG_E(CHATLOG).Trace("%s: session already CLOSED(sidG=%016x sidL=%d)", __FUNCTION__, sctx->sidGlobal(), _sid);
    }
  }

  void ChatSvcImpl::OpenChannel(ChannelInfo const & _chinfo, SessionId _sid, CustomId _ctmid, IOpenChannelCallback* _cb)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d ctmid=%016x)", __FUNCTION__, _sid, _ctmid);
  }

  void ChatSvcImpl::CloseChannel(ChannelId _chnlid, SessionId _sid)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d chnlid=%d)", __FUNCTION__, _sid, _chnlid);
  }

  Result::Enum ChatSvcImpl::AddUser2Channel(CustomId _useridGlobal, SessionId _sid, bool channelMuted, ChannelName const & _chnlname)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d useridG=%d chnlname=%s muted=%d)", __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str(), (int)channelMuted);

    SessionsT::iterator it = sessions_.find(_sid);
    if (it == sessions_.end())
    {
      LOG_E(CHATLOG).Trace("%s: session NOT FOUND(sidL=%d useridG=%d chnlname=%s)", __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str());
      return Result::FAIL;
    }

    StrongMT<SessionContext> sctx = it->second;
    StrongMT<ChannelContext> chnlctx = sctx->findChannel(_chnlname);
    if (!chnlctx)
    {
      LOG_E(CHATLOG).Trace("%s: channel NOT FOUND(sidL=%d useridG=%d chnlname=%s)", __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str());
      return Result::FAIL;
    }

    StrongMT<UserContext> uctx = sctx->findUserByGlobalId(_useridGlobal);
    if (!uctx)
    {
      uctx.Set(new UserContext(_useridGlobal, ++autouserid_, sctx));
      if (sctx->registerUser(uctx) < 0)
      {
        LOG_E(CHATLOG).Trace("%s: can't register user in session(sidL=%d useridG=%d chnlname=%s)", 
          __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str());
        return Result::FAIL;
      }
    }

    if (uctx->channel2join(chnlctx, channelMuted) < 0)
    {
      LOG_E(CHATLOG).Trace("%s: can't add channel for user(sidL=%d useridG=%d chnlname=%s)", __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str());
      return Result::FAIL;
    }

    return Result::SUCCESS;
  }

  Result::Enum ChatSvcImpl::RemoveUser(CustomId _useridGlobal, SessionId _sid, ChannelName const & _chnlname)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d useridG=%d chnlname=%s)", __FUNCTION__, _sid, _useridGlobal, _chnlname.c_str());
    return Result::FAIL;
  }

  int ChatSvcImpl::RegisterUser(CustomId _sidGlobal, CustomId _useridGlobal, NickName const & _nickname, IChatClientCallback* _cb)
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x useridG=%d nickname=%s)", __FUNCTION__, _sidGlobal, _useridGlobal, _nickname.c_str());

    if (!_cb)
    {
      LOG_E(CHATLOG).Trace("%s: client callback is NULL(sidG=%016x useridG=%d nickname=%s)", 
        __FUNCTION__, _sidGlobal, _useridGlobal, _nickname.c_str());
      return -1;
    }

    SessionsByGlobalIdT::const_iterator sit = sessionsByGlobalId_.find(_sidGlobal);
    if (sessionsByGlobalId_.end() == sit)
    {
      LOG_E(CHATLOG).Trace("%s: session NOT FOUND(sidG=%016x useridG=%d nickname=%s)", 
        __FUNCTION__, _sidGlobal, _useridGlobal, _nickname.c_str());
      return -1;
    }

    StrongMT<SessionContext> sctx = sit->second;
    StrongMT<UserContext> uctx = sctx->findUserByGlobalId(_useridGlobal);
    if (!uctx)
    {
      LOG_E(CHATLOG).Trace("%s: user NOT FOUND(sidG=%016x sidL=%d useridG=%d nickname=%s)", 
        __FUNCTION__, _sidGlobal, sctx->sidLocal(), _useridGlobal, _nickname.c_str());
      return -1;
    }

    uctx->nickname(_nickname);
    uctx->callback(_cb);
    uctx->callback()->OnRegisterUser(sctx->sidLocal(), uctx->useridLocal(), 0);

    usersByGlobalId_[_useridGlobal] = uctx;

    //  join channels
    UserContext::ChannelsT const & chnls2join = uctx->channels2join();
    for(UserContext::ChannelsT::const_iterator it = chnls2join.begin(); it != chnls2join.end(); ++it)
    {
      StrongMT<ChannelContext> chnlctx = *it;
      chnlctx->userJoin(uctx);
      uctx->callback()->OnJoinChannel(chnlctx->sid(), chnlctx->chnlname());
    }

    //  send channel history to user
    for(UserContext::ChannelsT::const_iterator it = chnls2join.begin(); it != chnls2join.end(); ++it)
    {
      StrongMT<ChannelContext> chnlctx = *it;
      const ChannelHistory::HistoryT & history = chnlctx->msgHistory();
      for(ChannelHistory::HistoryT::const_iterator hit=history.begin();
        hit != history.end(); ++hit)
      {
        uctx->callback()->OnNewMessage( chnlctx->sid(), chnlctx->chnlname(), 
          hit->userctx->nickname(), hit->userctx->useridGlobal(), hit->sourceText, hit->filteredText );
      }
    }

    return 0;
  }

  void ChatSvcImpl::UnregisterUser(SessionId _sidLocal, UserId _useridLocal)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d useridL=%d)", __FUNCTION__, _sidLocal, _useridLocal);

    SessionsT::const_iterator cit = sessions_.find(_sidLocal);
    if (sessions_.end() != cit)
    {
      StrongMT<SessionContext> sctx = cit->second;
      StrongMT<UserContext> uctx = sctx->findUser(_useridLocal);
      if (uctx)
      {
        unregisterUser_(uctx);
      }
      else
      {
        LOG_W(CHATLOG).Trace("%s: user NOT FOUND(sidL=%d useridL=%d)", __FUNCTION__, _sidLocal, _useridLocal);
      }
    }
    else
    {
      LOG_W(CHATLOG).Trace("%s: session NOT FOUND(sidL=%d useridL=%d)", __FUNCTION__, _sidLocal, _useridLocal);
    }
  }

  void ChatSvcImpl::UnregisterUser(CustomId const & _useridGlobal)
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d)", __FUNCTION__, _useridGlobal);
    UsersByGlobalIdT::iterator it = usersByGlobalId_.find(_useridGlobal);
    if (usersByGlobalId_.end() == it)
    {
      LOG_W(CHATLOG).Trace("%s: user NOT FOUND(useridG=%d)", __FUNCTION__, _useridGlobal);
      return;
    }

    StrongMT<UserContext> uctx = it->second;
    unregisterUser_(uctx);
  }

  void ChatSvcImpl::unregisterUser_(UserContext * _uctx)
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d useridL=%d)", __FUNCTION__, _uctx->useridGlobal(), _uctx->useridLocal());

    if (_uctx->isclosed())
    {
      LOG_M(CHATLOG).Trace("%s: user context already CLOSED(useridG=%d useridL=%d)", 
        __FUNCTION__, _uctx->useridGlobal(), _uctx->useridLocal());
      return;
    }

    //  leave channels
    UserContext::ChannelsT const & chnls = _uctx->channels2join();
    for(UserContext::ChannelsT::const_iterator cit = chnls.begin();
      cit != chnls.end(); ++cit)
    {
      StrongMT<ChannelContext> cctx = *cit;
      cctx->userLeave(_uctx->useridLocal());
    }

    usersByGlobalId_.erase(_uctx->useridGlobal());

    StrongMT<SessionContext> sctx = _uctx->sessionctx();
    if (sctx->isclosed())
    {
      sctx->unregisterUser(_uctx->useridLocal());

      int count = 0;
      for(UserContext::ChannelsT::const_iterator cit = chnls.begin();
        cit != chnls.end(); ++cit)
      {
        StrongMT<ChannelContext> cctx = *cit;
        if (!cctx->userCount())
        {
          //  no users joined to this channel
          cctx->close();
          ++count;
        }
      }
      if (count == chnls.size())
      {
        LOG_M(CHATLOG).Trace("%s: all channels CLOSED -> remove session (sidGlobal=%016x sidLocal=%d useridG=%d useridL=%d)", 
          __FUNCTION__, sctx->sidGlobal(), sctx->sidLocal(), _uctx->useridGlobal(), _uctx->useridLocal());

        //  all channels closed
        sessions_.erase(sctx->sidLocal());
        sessionsByGlobalId_.erase(sctx->sidGlobal());
      }

      _uctx->close();
    }
  }

  void ChatSvcImpl::SendMsg(SessionId _sid, ChannelName const & _chnlname, UserId _from, wstring const & _msg)
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d chnlname=%s useridL=%d msg=%s)", __FUNCTION__, _sid, _chnlname.c_str(), _from, _msg.c_str());

    SessionsT::const_iterator sit = sessions_.find(_sid);
    if (sessions_.end() == sit)
    {
      LOG_E(CHATLOG).Trace("%s: session NOT FOUND(useridL=%d sidL=%d chnlname=%s)", __FUNCTION__, _from, _sid, _chnlname.c_str());
      return;
    }

    StrongMT<SessionContext> sctx = sit->second;
    StrongMT<ChannelContext> cctx = sctx->findChannel( _chnlname );
    if (!cctx)
    {
      LOG_E(CHATLOG).Trace("%s: channel NOT FOUND(useridL=%d sidL=%d chnlname=%s)", __FUNCTION__, _from, _sid, _chnlname.c_str());
      return;
    }

    StrongMT<UserContext> uctx = sctx->findUser( _from );
    if (!uctx)
    {
      LOG_E(CHATLOG).Trace("%s: user NOT FOUND(useridL=%d sidL=%d chnlname=%s)", __FUNCTION__, _from, _sid, _chnlname.c_str());
      return;
    }

    if (!cctx->ignoreUserMute() && uctx->IsChannelMuted(cctx))
    {
      LOG_W(CHATLOG).Trace("%s: msg from muted user(useridL=%d sidL=%d chnlname=%s)", __FUNCTION__, _from, _sid, _chnlname.c_str());
      return;
    }

    timer::DecodedTime msgtime;
    UtcDecodedTime(msgtime);

    if (Cfg::GetCensorCheck())
      if ( cctx->messageCensorCheck( uctx, msgtime, _msg ) )
        return;

    cctx->sendMsg( uctx, msgtime, _msg, _msg );
  }
}
