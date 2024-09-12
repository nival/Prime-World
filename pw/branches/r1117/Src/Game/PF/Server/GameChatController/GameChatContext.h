#pragma once
#include <ChatSvc/ChatManagementIface.h>
#include <GameChatController/IGameChatController.h>

namespace gamechat
{
  class GameChatContext : public chat::IOpenSessionCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( GameChatContext, chat::IOpenSessionCallback, BaseObjectMT );

  public:
    GameChatContext();
    GameChatContext(gamechat::GameSessionId const & _gameid, IOpenGameChatCallback * _cb);
    ~GameChatContext();

  public:
    gamechat::GameSessionId const & gameid() const;
    chat::SessionId const &sid() const;

    //  chat::IOpenSessionCallback
    void OnOpenSession(chat::Result::Enum _rc, chat::SessionId _sid);

    //  IChatManagement::AddUser2Channel callback
    void OnAddUser2Channel(chat::Result::Enum _rc, GameSessionId _gameid, rpc::CallStatus _rpcsts);

  private:
    gamechat::GameSessionId gameid_;
    chat::SessionId sid_;
    WeakMT<gamechat::IOpenGameChatCallback> cb_;
  };

  inline
  gamechat::GameSessionId const & GameChatContext::gameid() const
  {
    return gameid_;
  }

  inline
  chat::SessionId const & GameChatContext::sid() const
  {
    return sid_;
  }
}
