#include "GameChatController/stdafx.h"
#include "GameChatController/GameChatController.h"
#include <ChatSvc/ChatSvcNaming.h>
#include <chatsvc/LChatManagementIface.auto.h>

namespace gamechat
{
  static float s_connect2chatRetryTimeout = 10.0f;
  REGISTER_VAR( "chatctrl_connect_to_chat_retry_timeout", s_connect2chatRetryTimeout, STORAGE_NONE );

  GameChatController::GameChatController( rpc::GateKeeper * _gk )
  {
    fileDumper_ = NLogg::BasicTextFileDumper::New( 0, CHATCTRLLOG );

    if ( StrongMT<NLogg::CDumper> stdoutDumper = GetSystemLog().FindDumperByName( "stdout" ) )
      GetSystemLog().AddChannel( CHATCTRLLOG, fileDumper_, stdoutDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
    else
      GetSystemLog().AddChannel( CHATCTRLLOG, fileDumper_, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );

    chatManagementIface_ = new rpc::IfaceRequester<chat::RIChatManagement>;
    chatManagementIface_->init( _gk, chat::ServiceClass, chat::ServiceRpcIface, &GetSystemLog(), 0, this, s_connect2chatRetryTimeout);

    Reset( rpcFactory_, new rpc::LocalEntityFactory( _gk->GetGate() ) );
    rpcFactory_->RegisterAttach<chat::IOpenSessionCallback, chat::LIOpenSessionCallback>();
    rpcFactory_->RegisterAttach<chat::IOpenChannelCallback, chat::LIOpenChannelCallback>();
  }

  GameChatController::~GameChatController()
  {
  }

  bool GameChatController::isopen() const
  {
    return chatManagementIface_->isopen();
  }

  void GameChatController::step()
  {
    chatManagementIface_->step();
  }

  int GameChatController::OpenGameChat( GameSessionId const & _gameid, vector<wstring> const & _channelNames, IOpenGameChatCallback * _cb )
  {
    LOG_M(CHATCTRLLOG).Trace("%s (gameid=%016x)", __FUNCTION__, _gameid);

    if (!chatManagementIface_->isopen())
    {
      LOG_W(CHATCTRLLOG).Trace("Chat management iface is CLOSED");
      return -1;
    }

    StrongMT<GameChatContext> ctx(new GameChatContext(_gameid, _cb));
    if (!gamechats_.insert(make_pair(_gameid, ctx)).second)
    {
      LOG_E(CHATCTRLLOG).Trace("%s : game chat with the same id already exits(gameid=%016x)", __FUNCTION__, _gameid);
      return -1;
    }

    chat::SessionInfo si(_gameid);
    si.channels_.push_back(chat::ChannelInfo(gamechat::channels::Session));
    si.channels_.push_back(chat::ChannelInfo(gamechat::channels::Team1));
    si.channels_.push_back(chat::ChannelInfo(gamechat::channels::Team2));
    si.channels_.push_back(chat::ChannelInfo(gamechat::channels::Team1_SmartChat, true));
    si.channels_.push_back(chat::ChannelInfo(gamechat::channels::Team2_SmartChat, true));

    chatManagementIface_->iface()->OpenSession(si, ctx.Get());

    return 0;
  }

  int GameChatController::CloseGameChat( GameSessionId const & _gameid )
  {
    LOG_M(CHATCTRLLOG).Trace("%s (gameid=%016x)", __FUNCTION__, _gameid);

    if (!chatManagementIface_->isopen())
    {
      LOG_W(CHATCTRLLOG).Trace("Chat management iface is CLOSED");
      return -1;
    }

    StrongMT<GameChatContext> const & ctx = findContext(_gameid);
    if (!ctx)
    {
      LOG_E(CHATCTRLLOG).Trace("%s : game chat NOT found(gameid=%016x)", __FUNCTION__, _gameid);
      return -1;
    }

    chatManagementIface_->iface()->CloseSession(ctx->sid());
    return 0;
  }

  int GameChatController::AddToChannel( GameSessionId const & _gameid, wstring const & _channelName, chat::UserId const & _userid, const bool channelMuted )
  {
    LOG_M(CHATCTRLLOG).Trace("%s (gameid=%016x u=%d chnlname=%s muted=%d)", __FUNCTION__, _gameid, _userid, _channelName, (int)channelMuted);

    if (!chatManagementIface_->isopen())
    {
      LOG_W(CHATCTRLLOG).Trace("Chat management iface is CLOSED");
      return -1;
    }

    StrongMT<GameChatContext> const & ctx = findContext(_gameid);
    if (!ctx)
    {
      LOG_E(CHATCTRLLOG).Trace("%s : game chat NOT found(gameid=%016x)", __FUNCTION__, _gameid);
      return -1;
    }

    chatManagementIface_->iface()->AddUser2Channel(_userid, ctx->sid(), channelMuted, _channelName, ctx.Get(), &GameChatContext::OnAddUser2Channel, _gameid);
    return 0;
  }

  int GameChatController::KickFromChannel( GameSessionId const & _gameid, wstring const & _channelName, chat::UserId const & _userid )
  {
    LOG_M(CHATCTRLLOG).Trace("%s (gameid=%016x u=%d chnlname=%s)", __FUNCTION__, _gameid, _userid, _channelName);
    return -1;
  }

  void GameChatController::onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<chat::RIChatManagement> > const & _ifacereq)
  {
    return;
  }

  StrongMT<GameChatContext> GameChatController::findContext(GameSessionId const & _gameid) const
  {
    GameChatContextsT::const_iterator it = gamechats_.find(_gameid);
    if (gamechats_.end() == it)
    {
      return StrongMT<GameChatContext>();
    }

    return it->second;
  }

}
