#pragma once
#include <ChatTypes.h>
#include <ChatSvc/ChatContext.h>

namespace chat
{
  class IChatClientCallback;
  class ChannelContext;
  class SessionContext;

  class UserContext : public Context, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( UserContext, Context, BaseObjectMT );

  public:
    typedef vector< StrongMT<ChannelContext> > ChannelsT;

  public:
    UserContext();
    UserContext(CustomId const & _useridGlobal, UserId const & _useridLocal, SessionContext * _sid);
    ~UserContext();

  public:
    CustomId const useridGlobal() const { return useridGlobal_; }
    UserId const & useridLocal() const { return useridLocal_; }
    void nickname(NickName const & _nickname) { nickname_ = _nickname; }
    NickName const & nickname() const { return nickname_; }
    void callback( IChatClientCallback * _cb ) { cb_ = _cb; }
    IChatClientCallback * callback() const { return cb_; }
    SessionContext * sessionctx() const { return sessionctx_; }

    int channel2join( ChannelContext * _chnlctx, const bool _channelMuted );
    ChannelsT const & channels2join() const { return channels_; }

    bool close();

    bool IsChannelMuted(ChannelContext* _chnlctx) const
    {
      if (channelsMuted_.empty())
        return false;

      return ContainsChannel(channelsMuted_, _chnlctx);
    }

  private:
    static bool ContainsChannel(const ChannelsT& _channels, ChannelContext* _chnlctx);

    CustomId useridGlobal_;
    UserId useridLocal_;
    StrongMT<SessionContext> sessionctx_;
    CustomId sidGlobal_;
    SessionId sidLocal_;
    NickName nickname_;
    StrongMT<IChatClientCallback> cb_;

    ChannelsT channels_;
    ChannelsT channelsMuted_;
  };
}
