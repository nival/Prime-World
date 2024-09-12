#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatChannelContext.h"
#include "ChatSvc/ChatUserContext.h"
#include "ChatSvc/ChatChannelHistory.h"
#include "ChatSvc/ChatClientIfaceCallback.h"

NI_DEFINE_REFCOUNT(chat::ChannelContext);

namespace chat
{
  StrongMT<UserContext> const ChannelContext::NULL_USER_CTX;

  ChannelContext::ChannelContext( SessionId _sid, ChannelName const & _chnlname, CustomId _ctmid, int _msgHistorySize, censorship::ICensorClient * _censor, bool const _ignoreUserMute ) :
  sid_(_sid),
  chnlname_(_chnlname),
  ctmid_(_ctmid),
  censor_(_censor),
  ignoreUserMute_(_ignoreUserMute)
  {
    msgHistory_.Set(new ChannelHistory(_msgHistorySize));
  }

  ChannelContext::~ChannelContext()
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d chnlname=%s)", __FUNCTION__, sid_, chnlname_.c_str());
  }


  void ChannelContext::Poll()
  {
    while ( !censorOps_.empty() )
    {
      StrongMT<CensorCheckOp> op = censorOps_.front();
      if ( !op->Finished() )
        break;

      censorOps_.pop_front();

      sendMsg( op->user(), op->MsgTime(), op->SrcText(), op->FilteredText() );
    }
  }


  int ChannelContext::userJoin( UserContext * _uctx)
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d useridL=%d sidL=%d chnlname=%s)", 
      __FUNCTION__, _uctx->useridGlobal(), _uctx->useridLocal(), sid_, chnlname_.c_str());

    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: channel context already CLOSED(useridG=%d useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _uctx->useridGlobal(), _uctx->useridLocal(), sid_, chnlname_.c_str());
      return -1;
    }

    if (!users_.insert(make_pair(_uctx->useridLocal(), _uctx)).second)
    {
      LOG_E(CHATLOG).Trace("%s: user already registered in channel(useridG=%d useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _uctx->useridGlobal(), _uctx->useridLocal(), sid_, chnlname_.c_str());
      return -1;
    }

    return 0;
  }

  int ChannelContext::userLeave(UserId const & _userid)
  {
    LOG_M(CHATLOG).Trace("%s(useridL=%d sidL=%d chnlname=%s)", 
      __FUNCTION__, _userid, sid_, chnlname_.c_str());

    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: channel context already CLOSED(useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _userid, sid_, chnlname_.c_str());
      return -1;
    }

    UsersT::iterator it = users_.find(_userid);
    if (users_.end() == it)
    {
      LOG_E(CHATLOG).Trace("%s: user NOT FOUND(useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _userid, sid_, chnlname_.c_str());
      return -1;
    }

    users_.erase(it);
    return 0;
  }

  bool ChannelContext::close()
  {
    LOG_M(CHATLOG).Trace("%s(sidL=%d chnlname=%s)", __FUNCTION__, sid_, chnlname_.c_str());

    bool res = Context::close();
    if (res)
    {
      msgHistory_->clear();
      censorOps_.clear();
      users_.clear();
    }
    else
    {
      LOG_W(CHATLOG).Trace("%s: context already CLOSED(sidL=%d chnlname=%s)", __FUNCTION__, sid_, chnlname_.c_str());
    }
    return res;
  }

  void ChannelContext::addMsg2History( UserContext * _userctx, const timer::DecodedTime & _time, const wstring & _srcText, const wstring & _filtrdText )
  {
    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: channel context already CLOSED(userG=%d useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _userctx->useridGlobal(), _userctx->useridLocal(), sid_, chnlname_.c_str());
      return;
    }

    msgHistory_->addMessage( HistoryMsg( _userctx, _time, _srcText, _filtrdText ) );
  }

  ChannelHistory::HistoryT const & ChannelContext::msgHistory() const
  {
    return msgHistory_->history();
  }

  UserContext * ChannelContext::findUser(UserId const & _userid) const
  {
    UsersT::const_iterator uit = users_.find(_userid);
    if (users_.end() == uit)
      return 0;

    return uit->second;
  }

  bool ChannelContext::messageCensorCheck( UserContext * _userctx, timer::DecodedTime _msgtime, const wstring & _text )
  {
    StrongMT<CensorCheckOp> ccop = new CensorCheckOp( this, _userctx, _msgtime, _text );

    censorship::TRequestId reqid = censor_->Check( 0, ccop.Get(), _text );
    if (0 == reqid)
    {
      LOG_E(CHATLOG).Trace("%s: censor check FAILED (userG=%d useridL=%d sidL=%d chnlname=%s)", 
        __FUNCTION__, _userctx->useridGlobal(), _userctx->useridLocal(), sid_, chnlname_.c_str());
      return false;
    }

    censorOps_.push_back( ccop );
    return true;
  }

  void ChannelContext::sendMsg( UserContext * _userctx, timer::DecodedTime _msgtime, const wstring & _srcText, const wstring & _filtrdText )
  {
    addMsg2History(_userctx, _msgtime, _srcText, _filtrdText );

    for(ChannelContext::UsersT::const_iterator it = users_.begin(); it != users_.end(); ++it)
    {
      StrongMT<UserContext> const ictx = it->second;
      ictx->callback()->OnNewMessage( sid(), chnlname(), _userctx->nickname(), _userctx->useridGlobal(), _srcText, _filtrdText );
    }
  }
}
