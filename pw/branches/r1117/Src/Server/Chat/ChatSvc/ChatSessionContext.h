#pragma once
#include <ChatSvc/ChatChannelContext.h>

namespace chat
{
  class SessionContext : public Context, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( SessionContext, Context, BaseObjectMT );

  public:
    typedef map<chat::ChannelName, StrongMT<ChannelContext> > ChannelsT;
    typedef map<chat::CustomId, StrongMT<UserContext> > UsersByGlobalIdT;
    typedef map<chat::UserId, StrongMT<UserContext> > UsersT;

  public:
    SessionContext (chat::SessionId const & _sidGlobal, chat::CustomId const & _sidLocal = chat::DEFAULT_CUSTOM_ID);
    ~SessionContext ();

    void Poll();

  public:
    chat::CustomId const & sidGlobal() const { return sidGlobal_; }
    chat::SessionId const & sidLocal() const { return sidLocal_; }
    int addChannel(ChannelContext * _chnlctx);
    ChannelContext * findChannel(chat::ChannelName const & _chnlname) const;

    int registerUser(UserContext * _userctx);
    int unregisterUser(chat::UserId const & _userid);
    UserContext * findUserByGlobalId(chat::CustomId const & _useridGlobal) const;
    UserContext * findUser(chat::UserId const & _userid) const;

    ChannelsT const & channels() const { return channels_; }

    bool close();

  private:
    chat::SessionId sidLocal_;
    chat::CustomId sidGlobal_;

    ChannelsT channels_;
    UsersByGlobalIdT  usersByGlobalId_;
    UsersT  users_;
  };

} //namespace chat
