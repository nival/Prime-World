#pragma once
#include "ChatTypes.h"
#include "Types.h"

namespace gamechat
{
  _interface IOpenGameChatCallback : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IOpenGameChatCallback, IBaseInterfaceMT );

    virtual void OnOpenSessionChat(gamechat::GameSessionId const & _gameid, int _rc) = 0;
  };

  _interface IGameChatController : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IGameChatController, IBaseInterfaceMT );

    virtual int OpenGameChat( GameSessionId const & _gameid, vector<chat::ChannelName> const & _channelNames, IOpenGameChatCallback * _cb ) = 0;
    virtual int CloseGameChat(GameSessionId const & _gameid) = 0;
    virtual int AddToChannel(GameSessionId const & _gameid, chat::ChannelName const & _channelName, chat::UserId const & _userId, const bool channelMuted) = 0;
    virtual int KickFromChannel(GameSessionId const & _gameid, chat::ChannelName const & _channelName, chat::UserId const & _userId) = 0;
  };
}
