#pragma once
#include <ChatTypes.h>
#include <ChatSvc/ChatChannelHistory.h>
#include <ChatSvc/ChatContext.h>
#include <ChatSvc/ChatCensorCheckOp.h>
#include <list>

namespace chat
{
  class ChannelHistory;

  class ChannelContext : public Context, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( ChannelContext, Context, BaseObjectMT );

    static StrongMT<UserContext> const NULL_USER_CTX;

  public:
    typedef map<UserId, StrongMT<UserContext> > UsersT;

  public:
    ChannelContext();
    ChannelContext( SessionId _sid, ChannelName const & _chnlname, CustomId _ctmid, int _msgHistorySize, censorship::ICensorClient * _censor, bool const _ignoreUserMute );
    ~ChannelContext();

    void Poll();

  public:
    CustomId customid() const { return ctmid_; }
    SessionId sid() const { return sid_; }
    ChannelName const & chnlname() const { return chnlname_; }

    int userJoin(UserContext * _uctx);
    int userLeave(UserId const & _userid);
    UserContext * findUser(UserId const & _userid) const;

    void addMsg2History( UserContext * _userctx, const timer::DecodedTime & _time, const wstring & _srcText, const wstring & _filtrdText );
    ChannelHistory::HistoryT const & msgHistory() const;

    UsersT const & users() const { return users_; }
    unsigned int userCount() const { return users_.size(); }

    bool close();

    bool messageCensorCheck( UserContext * _userctx, timer::DecodedTime _msgtime, const wstring & _text );
    void sendMsg( UserContext * _userctx, timer::DecodedTime _msgtime, const wstring & _srcText, const wstring & _filtrdText );

    bool ignoreUserMute() const { return ignoreUserMute_; }

  private:
    typedef std::list<StrongMT<CensorCheckOp> > CensorOpQueue;
    SessionId sid_;
    CustomId ctmid_;
    ChannelName chnlname_;

    UsersT users_;
    StrongMT<ChannelHistory> msgHistory_;
    CensorOpQueue censorOps_;
    StrongMT<censorship::ICensorClient> censor_;

    const bool ignoreUserMute_;
  };

}
