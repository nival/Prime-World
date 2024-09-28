#pragma once
#include "Chat/ChatTypes.h"

namespace gamechat
{
  namespace ChannelType
  {
    enum Enum
    {
      Invalid = -1,
      Global,
      MyTeam,
      Session,
      SmartChat,
    };
  };

  struct ChatMessage
  {
    enum MessageType
    {
      Predefined,
      Whisper,
    };

    MessageType messageType;
    chat::NickName nickname;
    wstring message;
    wstring filteredMessage;
    ChannelType::Enum channel;
    chat::CustomId userId;

    ChatMessage()
      : messageType(ChatMessage::Predefined)
      , channel(ChannelType::Invalid)
      , userId(chat::DEFAULT_CUSTOM_ID)
    {
    }
  };

  class IClient : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1(IClient, IBaseInterfaceMT);

  public:
    virtual void Step() = 0;

    virtual void SendMsg(wstring const & _message, gamechat::ChannelType::Enum const _channelType) = 0;
    virtual void GetNewMessages(vector<ChatMessage> & _messages) = 0;
    virtual void Shutdown() = 0;

    virtual chat::UserId GetUserId() const = 0;
    virtual chat::CustomId GetGameUserId() const = 0;
  };
} //namespace gamechat
