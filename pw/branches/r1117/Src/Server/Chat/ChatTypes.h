#pragma once

#include "Network/TransportTypes.h"

//Nice namespace names uh?

namespace Chat
{
  typedef long long TSessionId;

  static const Transport::TServiceId serviceId = "chat";
}

namespace chat
{
  typedef unsigned int ChannelGroupId;
  const ChannelGroupId INVALID_CHNL_GROUP_ID = (ChannelGroupId)-1;

  typedef unsigned long long CustomId;
  const CustomId DEFAULT_CUSTOM_ID = 0;

  typedef unsigned long long SessionId;
  const SessionId INVALID_SESSION_ID = (SessionId)-1;

  typedef unsigned long long ChannelId;
  const ChannelId INVALID_CHANNEL_ID = (ChannelId)-1;

  typedef wstring ChannelName;

  typedef unsigned long long UserId;
  const UserId INVALID_USER_ID = (UserId)-1;

  typedef wstring NickName;
  typedef wstring MessageText;

  class Channel;
  typedef StrongMT<Channel> ChannelPtr;
  class ChannelGroup;
  typedef StrongMT<ChannelGroup> ChannelGroupPtr;


  struct ChatChannelInfo
  {
    enum EChannelType
    {
      T_AUTO,
      T_CUSTOM,
      T_WHISPER,
    };
//    ZDATA
    Chat::TSessionId id;
    wstring name;
    Chat::TSessionId gameId;
    EChannelType channelType;
//    ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&name); f.Add(4,&gameId); f.Add(5,&channelType); return 0; }
    ChatChannelInfo() : id(-1), gameId( -1 ), channelType( T_CUSTOM ) {}
    ChatChannelInfo( Chat::TSessionId _id, wstring _name );
  };
}
