#include "stdafx.h"
#include "GameChatClient.h"
#include <Chat/ChatSvc/ChatSvcNaming.h>
#include <Chat/ChatSvc/LChatClientIfaceCallback.auto.h>
#include <Chat/ChatSvc/RChatClientIfaceCallback.auto.h>
#include "Game/PF/Server/GameChatController/Types.h"
//#include "PF_GameLogic/DBStats.h"
#include <locale>

static unsigned int g_gamechatConnectRetryTimeout = 60;
REGISTER_VAR("gamechat_connect_retry_timeout", g_gamechatConnectRetryTimeout, STORAGE_NONE );

NI_DEFINE_REFCOUNT(gamechat::IClient);
NI_DEFINE_REFCOUNT(gamechat::Client);

namespace gamechat
{
  Client::Client(chat::CustomId const & _gameid, chat::CustomId const & _gameUserid, chat::NickName const & _nickname, rpc::GateKeeperClient * _gk)
    :gameid_(_gameid),
    gameUserid_(_gameUserid),
    sid_(chat::INVALID_SESSION_ID),
    chatUserid_(chat::INVALID_USER_ID),
    nickname_(_nickname),
    chatiface_(new rpc::IfaceRequester<chat::RIChatClient>())
  {
    Reset( rpcFactory_, new rpc::LocalEntityFactory( _gk->GetGate() ) );
    rpcFactory_->RegisterAttach<chat::IChatClientCallback, chat::LIChatClientCallback>();

    chatiface_->init( _gk, chat::ServiceClass, chat::ClientRpcIface, &::GetSystemLog(), 0, this, g_gamechatConnectRetryTimeout);

    channelName2Type_[gamechat::channels::Session] = ChannelType::Session;
    channelName2Type_[gamechat::channels::Team1] = ChannelType::MyTeam;
    channelName2Type_[gamechat::channels::Team2] = ChannelType::MyTeam;
    channelName2Type_[gamechat::channels::Team1_SmartChat] = ChannelType::SmartChat;
    channelName2Type_[gamechat::channels::Team2_SmartChat] = ChannelType::SmartChat;
 
  }

  Client::~Client()
  {
    Shutdown();
  }

  void Client::Shutdown()
  {
    // Разрываем кольцо NUM_TASK
    if ( chatiface_ )
      chatiface_->close();
    chatiface_ = 0;
  }


  void Client::Step()
  {
    if (chatiface_)
      chatiface_->step();
  }

  void Client::SendMsg(wstring const & message, gamechat::ChannelType::Enum const channelType)
  {
    MessageTrace("%s(msg=%s chnltype=%d)", __FUNCTION__, message.c_str(), (int)channelType);

    if (chatiface_ && chatiface_->isopen())
    {
      ChannelsT::const_iterator it = channels_.begin();
      for(; it != channels_.end(); ++it)
      {
        ChannelContextPtr const & ctx = *it;
        if (channelType == ctx->type_)
        {
          chatiface_->iface()->SendMsg(ctx->sid_, ctx->chnlname_, chatUserid_, message);
          break;
        }
      }
      if (channels_.end() == it)
      {
        MessageTrace("%s: channel NOT FOUND(chnltype=%d)", __FUNCTION__, (int)channelType);
      }
    }
  }

  void Client::GetNewMessages( vector<ChatMessage> & _messages )
  {
    _messages.insert( _messages.end(), messages_.begin(), messages_.end() );
    messages_.clear();
  }

  void Client::OnRegisterUser(chat::SessionId _sid, chat::UserId _chatUserId, int _rc)
  {
    MessageTrace("%s(sidL=%d chatUserid=%d rc=%d)", __FUNCTION__, _sid, _chatUserId, _rc);

    if (_rc < 0)
    {
      LOG_E(0).Trace("%s: registration FAILED(rc=%d)", __FUNCTION__, _rc);
      sid_ = chat::INVALID_SESSION_ID;
      chatUserid_ = chat::INVALID_USER_ID;
    }
    else
    {
      sid_ = _sid;
      chatUserid_ = _chatUserId;
    }
  }

  void Client::OnJoinChannel(chat::SessionId _sid, chat::ChannelName const & _chnlname)
  {
    MessageTrace("%s(sid=%d chnlname=%s)", __FUNCTION__, _sid, _chnlname.c_str());

    ChannelContextPtr const ctx(new ChannelContext(_sid, _chnlname));

    ctx->type_ = GetChannelType(_chnlname);

    if (ctx->type_ == ChannelType::Invalid)
    {
      LOG_E(0).Trace("%s: invalid channel type(sid=%d chnlname=%s)", __FUNCTION__, _sid, _chnlname.c_str());
      return;
    }

    ChannelsT::iterator it = channels_.begin();
    for(; it != channels_.end(); ++it)
    {
      ChannelContextPtr const & ictx = *it;
      if (ictx->type_ == ctx->type_)
      {
        LOG_E(0).Trace("%s: channel with the same type already exists(sid=%d chnlname=%s type=%d )", 
          __FUNCTION__, _sid, _chnlname.c_str(), int(ctx->type_));
        break;
      }
    }
    if (channels_.end() == it)
    {
      MessageTrace("%s: channel registered successfully(sid=%d chnlname=%s chnltype=%d)", 
        __FUNCTION__, _sid, _chnlname.c_str(), int(ctx->type_));
      channels_.push_back(ctx);
    }
  }
  
  bool isLower(wchar_t ch)
  {
    return islower(ch,std::locale(""));
  }


  bool isUpperString(const wstring& s )
  {
    wstring::const_iterator cit = find_if(s.begin(), s.end(), isLower);
    if(cit !=s.end())
      return false;
    else
      return true;
  }


  void Client::OnNewMessage(chat::SessionId _sid, const chat::ChannelName &_chnlname, const chat::NickName &_nickname, chat::CustomId _useridGlobal, const wstring &_sourceMsg, const wstring &_fiteredMsg)
  {
    MessageTrace("%s(sid=%d chnlname=%s nickname=%s msg=%s)", __FUNCTION__, _sid, _chnlname, _nickname, _sourceMsg, _fiteredMsg);

    ChatMessage& msg = messages_.push_back();
    msg.message = _sourceMsg;
    msg.filteredMessage = _fiteredMsg;
    msg.channel = GetChannelType(_chnlname);
    msg.nickname = _nickname;
    msg.messageType = ChatMessage::Predefined;
    msg.userId = _useridGlobal;

  }

  void Client::onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<chat::RIChatClient>> const & _ifacereq)
  {
    if (rpc::IfaceRequesterState::OPENED == _st)
    {
      MessageTrace("Chat client iface OPENED");
      chatiface_->iface()->RegisterUser(gameid_, gameUserid_, nickname_, this, this, &Client::OnRegisterUserReturn, gameUserid_);
    }
    else
    if (rpc::IfaceRequesterState::CLOSED == _st)
    {
      MessageTrace("Chat client iface CLOSED");
    }
  }

  void Client::OnRegisterUserReturn(int _rc, chat::CustomId _gameUserid, rpc::CallStatus _rpcsts)
  {
    MessageTrace("%s(rc=%d userid=%d rpcsts=%d)", __FUNCTION__, _rc, _gameUserid, (int)_rpcsts);
  }

  ChannelType::Enum Client::GetChannelType(chat::ChannelName const & _chnlname) const
  {
    ChannelName2TypeT::const_iterator it = channelName2Type_.find(_chnlname);

    if (it == channelName2Type_.end())
      return ChannelType::Invalid;

    return it->second;
  }

}
