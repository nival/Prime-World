#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatUserContext.h"
#include "ChatSvc/ChatClientIface.h"
#include "ChatSvc/ChatChannelContext.h"
#include "ChatSvc/ChatSessionContext.h"

NI_DEFINE_REFCOUNT(chat::UserContext);

namespace chat
{
  UserContext::UserContext()
    :useridGlobal_(DEFAULT_CUSTOM_ID),
    useridLocal_(INVALID_USER_ID),
    sidLocal_(INVALID_SESSION_ID),
    sidGlobal_(DEFAULT_CUSTOM_ID)
  {
  }

  UserContext::UserContext( CustomId const & _useridGlobal, UserId const & _useridLocal, SessionContext * _sessionctx ) :
  useridGlobal_(_useridGlobal),
  useridLocal_(_useridLocal),
  sessionctx_(_sessionctx)
  {
    sidLocal_ = sessionctx_->sidLocal();
    sidGlobal_ = sessionctx_->sidGlobal();
  }

  UserContext::~UserContext()
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d useridL=%d sidG=%016x sidL=%d)", 
      __FUNCTION__, useridGlobal_, useridLocal_, sidGlobal_, sidLocal_);
  }

  int UserContext::channel2join( ChannelContext * _chnlctx, const bool _channelMuted )
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d useridL=%d sidG=%016x sidL=%d chnlname=%s)", 
      __FUNCTION__, useridGlobal_, useridLocal_, sidGlobal_, sidLocal_, _chnlctx->chnlname().c_str());

    if (Context::isclosed())
    {
      LOG_E(CHATLOG).Trace("%s: user context already CLOSED(useridG=%d useridL=%d sidG=%016x sidL=%d chnlname=%s)", 
        __FUNCTION__, useridGlobal_, useridLocal_, sidGlobal_, sidLocal_, _chnlctx->chnlname().c_str());
      return -1;
    }

    bool registered = false;

    {
      if (ContainsChannel(channels_, _chnlctx))
      {
        LOG_E(CHATLOG).Trace("%s: channel already register to join(useridG=%d useridL=%d sidG=%016x sidL=%d chnlname=%s)", 
          __FUNCTION__, useridGlobal_, useridLocal_, _chnlctx->customid(), _chnlctx->sid(), _chnlctx->chnlname().c_str());
      }
      else
      {
        channels_.push_back(_chnlctx);

        registered = true;
      }
    }

    if (_channelMuted)
    {
      if (ContainsChannel(channelsMuted_, _chnlctx))
      {
        LOG_E(CHATLOG).Trace("%s: channel already muted(useridG=%d useridL=%d sidG=%016x sidL=%d chnlname=%s)", 
          __FUNCTION__, useridGlobal_, useridLocal_, _chnlctx->customid(), _chnlctx->sid(), _chnlctx->chnlname().c_str());
      }
      else
      {
        channelsMuted_.push_back(_chnlctx);
      }
    }

    return (registered ? 0 : -1);
  }

  bool UserContext::close()
  {
    LOG_M(CHATLOG).Trace("%s(useridG=%d useridL=%d sidG=%016x sidL=%d)", 
      __FUNCTION__, useridGlobal_, useridLocal_, sidGlobal_, sidLocal_);

    bool res = Context::close();
    if (res)
    {
      channels_.clear();
      channelsMuted_.clear();
      sessionctx_ = 0;
    }
    else
    {
      LOG_M(CHATLOG).Trace("%s: context already CLOSED(useridG=%d useridL=%d sidG=%016x sidL=%d)", 
        __FUNCTION__, useridGlobal_, useridLocal_, sidGlobal_, sidLocal_);
    }

    return res;
  }

  bool UserContext::ContainsChannel(const ChannelsT& _channels, ChannelContext* _chnlctx)
  {
    ChannelsT::const_iterator it = _channels.begin();
    ChannelsT::const_iterator it_end = _channels.end();
    for (; it != it_end; ++it)
    {
      ChannelsT::const_reference ctx = *it;

      if (ctx->sid() != _chnlctx->sid())
        continue;
      if (ctx->chnlname() != _chnlctx->chnlname())
        continue;

      return true;
    }

    return false;
  }
}
