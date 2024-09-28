#pragma once
#include <GameChatController/IGameChatController.h>
#include <ChatSvc/RChatManagementIface.auto.h>
#include <rpc/IfaceRequester.h>
#include <rpc/LocalEntityFactory.h>
#include <GameChatController/GameChatContext.h>

namespace gamechat
{
  class GameChatController : public IGameChatController, 
                             public rpc::IfaceRequesterCallback<chat::RIChatManagement>, 
                             public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_3(GameChatController, IGameChatController, IfaceRequesterCallback<chat::RIChatManagement>, BaseObjectMT);

  public:
    GameChatController( rpc::GateKeeper * _gk );
    ~GameChatController();

  public:
    virtual bool isopen() const;
    virtual void step();

    //  IGameChatController
    virtual int OpenGameChat( GameSessionId const & _gameid, vector<wstring> const & _channelNames, IOpenGameChatCallback * _cb );
    virtual int CloseGameChat( GameSessionId const & _gameid );
    virtual int AddToChannel( GameSessionId const & _gameid, wstring const & _channelName, chat::UserId const & _userid, const bool channelMuted );
    virtual int KickFromChannel( GameSessionId const & _gameid, wstring const & _channelName, chat::UserId const & _userid );

  protected:
    void onChangeState(rpc::IfaceRequesterState::Enum st, StrongMT<rpc::IfaceRequester<chat::RIChatManagement> > const & ifacereq);

  private:
    StrongMT<GameChatContext> findContext(GameSessionId const & _gameid) const;

  private:
    StrongMT<rpc::IfaceRequester<chat::RIChatManagement> > chatManagementIface_;
    ScopedPtr<rpc::LocalEntityFactory> rpcFactory_;

    typedef map<GameSessionId, StrongMT<GameChatContext> > GameChatContextsT;
    GameChatContextsT gamechats_;

    StrongMT<NLogg::BasicTextFileDumper> fileDumper_;
  };
}
