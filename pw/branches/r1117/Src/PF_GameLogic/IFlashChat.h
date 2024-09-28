#pragma once

namespace NDb   { enum EChatChannel;}

namespace NGameX
{
  _interface IFlashChat : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IFlashChat, IBaseInterfaceST );

    virtual void AddChannel(NDb::EChatChannel channel,  const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel) = 0;
    virtual void AddChannelShortCut(NDb::EChatChannel channel, const wstring & shortcut) = 0;
    virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message) = 0;
    virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message, const int playerId) = 0;
    virtual void SetDefaultChannel(NDb::EChatChannel channelID) = 0;
    virtual void SetChatVisible(bool visible) = 0;
    virtual void SetChatOff(bool isChatOff) = 0;
    virtual void SetPlayerIcon(const int playerId, const string& path) = 0;
    virtual void SetPlayerHeroId(const int playerId, const int heroId, const int teamId) = 0;
    virtual void IgnoreUser(const int playerId) = 0;
    virtual void RemoveIgnore(const int playerId) = 0;
  };

  _interface IFlashSmartChat : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IFlashSmartChat, IBaseInterfaceST );

    virtual void SmartChatActivate() = 0;
    virtual void SmartChatActivateCategory(const unsigned id) = 0;
    virtual void SmartChatDeactivate() = 0;
    virtual void SmartChatBeginUpdate() = 0;
    virtual void SmartChatEndUpdate() = 0;
    virtual void SmartChatBeginCategory(const unsigned id, const string& key, const wstring& name) = 0;
    virtual void SmartChatEndCategory() = 0;
    virtual void SmartChatAddMessage(const unsigned id, const string& key, const wstring& text) = 0;
    virtual void SmartChatAddCancel(const unsigned id, const string& key) = 0;
  };
}


