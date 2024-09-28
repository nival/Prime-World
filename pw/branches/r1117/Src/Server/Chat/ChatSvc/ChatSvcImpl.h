#pragma once
#include "ChatSvc/ChatManagementIface.h"
#include "ChatSvc/ChatClientIface.h"
#include "Server/Censorship/ICensorClient.h"

namespace chat
{
  class UserContext;
  class SessionContext;

  class ChatSvcImpl : public IChatManagement, public IChatClient, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3(ChatSvcImpl, IChatManagement, IChatClient, BaseObjectMT);

  public:
    ChatSvcImpl();
    ~ChatSvcImpl();

  public:
    void Step();

  public:
    //  IChatManagement
    virtual void OpenSession(SessionInfo const & _si, IOpenSessionCallback* _cb);
    virtual void CloseSession(SessionId _sid);
    virtual void OpenChannel(ChannelInfo const & _chinfo, SessionId _sid, CustomId _ctmid, IOpenChannelCallback* _cb);
    virtual void CloseChannel(ChannelId _chnlid, SessionId _sid);
    virtual Result::Enum AddUser2Channel(CustomId _useridGlobal, SessionId _sid, bool channelMuted, ChannelName const & _chnlname);
    virtual Result::Enum RemoveUser(CustomId _useridGlobal, SessionId _sid, ChannelName const & _chnlname);

    //  IChatClient
    virtual int RegisterUser(CustomId _sidGlobal, CustomId _useridGlobal, NickName const & _nickname, IChatClientCallback* _cb);
    virtual void UnregisterUser(SessionId _sid, UserId _useridLocal);
    virtual void SendMsg(SessionId _sid, ChannelName const & _chnlname, UserId _from, wstring const & _msg);

    void UnregisterUser(CustomId const & _useridGlobal);

  private:
    void unregisterUser_(UserContext * _uctx);

  private:
    SessionId autoincsid_;
    UserId autouserid_;

    typedef map<SessionId, StrongMT<SessionContext> > SessionsT;
    SessionsT sessions_;
    typedef map<CustomId, StrongMT<SessionContext> > SessionsByGlobalIdT;
    SessionsByGlobalIdT sessionsByGlobalId_;
    typedef map<CustomId, StrongMT<UserContext> > UsersByGlobalIdT;
    UsersByGlobalIdT usersByGlobalId_;

    StrongMT<censorship::ICensorClient> censor_;
  };
}
