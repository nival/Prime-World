#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatSessionContext.h"
#include "ChatSvc/ChatUserContext.h"

NI_DEFINE_REFCOUNT(chat::SessionContext);

namespace chat
{
  SessionContext::SessionContext (chat::SessionId const & _sidLocal, chat::CustomId const & _sidGlobal)
    :sidLocal_(_sidLocal),
    sidGlobal_(_sidGlobal)
  {
  }



  SessionContext::~SessionContext ()
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x sidL=%d)", __FUNCTION__, sidGlobal_, sidLocal_);
  }



  void SessionContext::Poll()
  {
    for( ChannelsT::const_iterator it = channels_.begin(); it != channels_.end(); ++it )
    {
      ChannelContext * ch = it->second;
      ch->Poll();
    }
  }
  
  

  int SessionContext::addChannel(ChannelContext * _chnlctx)
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x sidL=%d chnlname=%s)", __FUNCTION__, sidGlobal_, sidLocal_, _chnlctx->chnlname().c_str());

    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: session context already CLOSED(sidG=%016x sidL=%d chnlname=%s)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _chnlctx->chnlname().c_str());
      return -1;
    }

    if (!channels_.insert(make_pair(_chnlctx->chnlname(), _chnlctx)).second)
    {
      LOG_E(CHATLOG).Trace("%s: channel already exists(sidG=%016x sidL=%d chnlname=%s)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _chnlctx->chnlname().c_str());
      return -1;
    }

    return 0;
  }


  ChannelContext * SessionContext::findChannel(chat::ChannelName const & _chnlname) const
  {
    ChannelsT::const_iterator it = channels_.find(_chnlname);
    if ( it == channels_.end() )
      return 0;

    return it->second;
  }



  int SessionContext::registerUser(UserContext * _userctx)
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x sidL=%d useridG=%d useridL=%d)", 
      __FUNCTION__, sidGlobal_, sidLocal_, _userctx->useridGlobal(), _userctx->useridLocal());

    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: session context already CLOSED(sidG=%016x sidL=%d useridG=%d useridL=%d)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _userctx->useridGlobal(), _userctx->useridLocal());
      return -1;
    }

    if (!usersByGlobalId_.insert(make_pair(_userctx->useridGlobal(), _userctx)).second)
    {
      LOG_E(CHATLOG).Trace("%s: user with the same global id already registered(sidG=%016x sid=%d useridG=%d useridL=%d)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _userctx->useridGlobal(), _userctx->useridLocal());
      return -1;
    }

    if (!users_.insert(make_pair(_userctx->useridLocal(), _userctx)).second)
    {
      LOG_E(CHATLOG).Trace("%s: user with the same local id already registered(sidG=%016x sid=%d useridG=%d useridL=%d)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _userctx->useridGlobal(), _userctx->useridLocal());

      usersByGlobalId_.erase(_userctx->useridGlobal());
      return -1;
    }

    return 0;
  }

  int SessionContext::unregisterUser(chat::UserId const & _userid)
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x sidL=%d useridL=%d)", 
      __FUNCTION__, sidGlobal_, sidLocal_, _userid);

    UsersT::iterator it = users_.find(_userid);
    if (users_.end() == it)
    {
      LOG_E(CHATLOG).Trace("%s: user NOT FOUND(sidG=%016x sidL=%d useridL=%d)", 
        __FUNCTION__, sidGlobal_, sidLocal_, _userid);
      return -1;
    }

    StrongMT<UserContext> uctx = it->second;
    users_.erase(it);

    UsersByGlobalIdT::iterator uit = usersByGlobalId_.find(uctx->useridGlobal());
    if (usersByGlobalId_.end() == uit)
    {
      LOG_E(CHATLOG).Trace("%s: user NOT FOUND(sidG=%016x sidL=%d useridG=%016x useridL=%d)", 
        __FUNCTION__, sidGlobal_, sidLocal_, uctx->useridGlobal(), _userid);
      return -1;
    }

    usersByGlobalId_.erase(uit);

    return 0;
  }

  UserContext * SessionContext::findUserByGlobalId(chat::CustomId const & _useridGlobal) const
  {
    UsersByGlobalIdT::const_iterator it = usersByGlobalId_.find(_useridGlobal);
    if ( it == usersByGlobalId_.end() )
      return 0;

    return it->second;
  }

  UserContext * SessionContext::findUser(chat::UserId const & _userid) const
  {
    UsersT::const_iterator it = users_.find(_userid);
    if ( it == users_.end() )
      return 0;

    return it->second;
  }

  bool SessionContext::close()
  {
    LOG_M(CHATLOG).Trace("%s(sidG=%016x sidL=%d)", __FUNCTION__, sidGlobal_, sidLocal_);

    bool res = Context::close();
    if (res)
    {
      //  release users and channels if all channels closed(i.e. have no joined users)

      SessionContext::ChannelsT::const_iterator cit = channels_.begin();
      for(; cit != channels_.end(); ++cit)
      {
        StrongMT<ChannelContext> cctx = cit->second;
        if (!cctx->isclosed())
          break;
      }
      if (channels_.end() == cit)
      {
        LOG_M(CHATLOG).Trace("%s: all channels closed(sidG=%016x sidL=%d)", __FUNCTION__, sidGlobal_, sidLocal_);

        channels_.clear();
        for(UsersT::const_iterator uit = users_.begin(); uit != users_.end(); ++uit)
        {
          StrongMT<UserContext> uctx = uit->second;
          uctx->close();
        }

        users_.clear();
        usersByGlobalId_.clear();
      }
    }
    else
    {
      LOG_W(CHATLOG).Trace("%s: context already CLOSED(sidG=%016x sidL=%d)", __FUNCTION__, sidGlobal_, sidLocal_);
    }

    return res;
  }
}
