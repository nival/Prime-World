#pragma once
#include "Chat/ChatSvc/RChatClientIface.auto.h"
#include <RPC/IfaceRequester.h>
#include <RPC/LocalEntityFactory.h>
#include "IGameChatClient.h"


namespace gamechat
{
  struct ChannelContext : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ChannelContext, BaseObjectST );

    chat::SessionId sid_;
    chat::ChannelName chnlname_;
    ChannelType::Enum type_;

    ChannelContext()
      :sid_(chat::INVALID_SESSION_ID),
      type_(ChannelType::Invalid)
    {}

    ChannelContext(chat::SessionId _sid, chat::ChannelName const & _chnlname)
      :sid_(_sid),
      chnlname_(_chnlname),
      type_(ChannelType::Invalid)
    {}

  };
  typedef Strong<ChannelContext> ChannelContextPtr;

  class Client : public gamechat::IClient, public chat::IChatClientCallback, public rpc::IfaceRequesterCallback<chat::RIChatClient>, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_4(Client, gamechat::IClient, chat::IChatClientCallback, rpc::IfaceRequesterCallback<chat::RIChatClient>, BaseObjectMT);

  public:
    Client(chat::CustomId const & _gameid, chat::CustomId const & _gameUserid, chat::NickName const & _nickname, rpc::GateKeeperClient * _gk);
    virtual ~Client();

  public:
    //  IClient
    void Step();
    void SendMsg(wstring const & message, gamechat::ChannelType::Enum const channelType);
    void GetNewMessages( vector<ChatMessage> & _messages );

    virtual void Shutdown();

    virtual chat::UserId GetUserId() const { return chatUserid_; }
    virtual chat::CustomId GetGameUserId() const { return gameUserid_; }

    //  getters
    chat::UserId const & chatUserid() const;
    chat::CustomId const & gameUserid() const;
    chat::NickName const & nickname() const;

  private:
    //IChatClientCallback
    virtual void OnRegisterUser(chat::SessionId _sid, chat::UserId _chatUserId, int _rc);
    virtual void OnJoinChannel(chat::SessionId _sid, chat::ChannelName const & _chnlname);
    virtual void OnNewMessage(chat::SessionId _sid, const chat::ChannelName &_chnlname, const chat::NickName &_nickname, chat::CustomId _useridGlobal, const wstring &_sourceMsg, const wstring &_fiteredMsg);

    void onChangeState(rpc::IfaceRequesterState::Enum _st, StrongMT<rpc::IfaceRequester<chat::RIChatClient>> const & _ifacereq);

    void OnRegisterUserReturn(int _rc, chat::CustomId _gameUserid, rpc::CallStatus _rpcsts);

  private:
    Client();

    ChannelType::Enum GetChannelType(chat::ChannelName const & _chnlname) const;

    chat::CustomId gameid_;
    chat::CustomId gameUserid_;
    chat::SessionId sid_;
    chat::UserId chatUserid_;
    chat::NickName nickname_;
    vector<ChatMessage> messages_;


    StrongMT<rpc::IfaceRequester<chat::RIChatClient>> chatiface_;
    ScopedPtr<rpc::LocalEntityFactory> rpcFactory_;
    typedef vector<ChannelContextPtr> ChannelsT;
    ChannelsT channels_;
    typedef map<chat::ChannelName, ChannelType::Enum> ChannelName2TypeT;

    ChannelName2TypeT channelName2Type_;
  };

  inline
  chat::UserId const & Client::gameUserid() const
  {
    return gameUserid_;
  }

  inline
  chat::UserId const & Client::chatUserid() const
  {
    return chatUserid_;
  }

  inline
  chat::NickName const & Client::nickname() const
  {
    return nickname_;
  }

}
