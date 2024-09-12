#pragma once

#include "../UI/FSCommandListner.h"
#include "../UI/FlashInterface.h"
#include "Client/GameChatClient/IGameChatClient.h"
#include "BindsController.h"
#include "PFUIEvent.h"
#include "PrecompiledTooltips.h"
#include "PlayerBehaviourTracking.h"

namespace UI     { class FlashContainer2; }
namespace Chat   { class ChatClient;      }
namespace NDb    { struct DBUIData;       }

namespace NGameX 
{
  _interface IFlashChat;
  _interface IUIEventHandler;
  _interface IPlayerIdMapper;
  class IgnoreListController;
  class IgnoreListStorage;
}
namespace EPlayerBehaviourEvent
{
  enum Enum;
}

namespace gamechat
{
  class IClient;
}


namespace NGameX
{

class ChatUiController;

class AsyncMessagesFilter : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1(AsyncMessagesFilter, BaseObjectST);
public:
  AsyncMessagesFilter(ChatUiController* controller) : pChatController(controller) {}

  int FilterMessage(const gamechat::ChatMessage& msg);
  void ProcessMessages();

private:
  struct FilteredMessageData
  {
    FilteredMessageData() : filtered(false) {}
    FilteredMessageData(const gamechat::ChatMessage& msg) : filtered(false), message(msg) {}
    gamechat::ChatMessage message;
    bool filtered;
  };

  ChatUiController*               pChatController;
  map< int, FilteredMessageData > toFilter;
  list<int>                       toFilterIdxOrder;
};

class IChatMessageHook;

class ChatUiController : public BaseObjectST, public UI::IFSCommandListner//,  public IChatUiInterface
{
  NI_DECLARE_REFCOUNT_CLASS_2( ChatUiController, BaseObjectST, UI::IFSCommandListner );//, UI::IFSCommandListner,  );
public:
  ChatUiController( gamechat::IClient * _chatClient );
  void OnFastReconnect( gamechat::IClient * _chatClient, IgnoreListStorage *_ignoreStorage );
  gamechat::IClient * GetClientPtr() const { return chatClient; }
  void SetIgnoreListController(  IgnoreListController* ilc );
  IgnoreListController* GetIgnoreListController() { return ignoreListController; }
  void SetPlayerIdMapper(IPlayerIdMapper* pim);

  const vector<gamechat::ChatMessage>& GetChatMessages(){return allMessages;}

  void AddChatUI( UI::FlashContainer2* _flashContainer, IFlashChat * _flashChat, const bool muted, const bool leaver, const bool leaverParty);
  void Update();

  void AddChatMessage(const wstring & msg, NDb::EChatChannel channel);

  void SetBindsController(BindsController* _bindsController){bindsController = _bindsController;};
  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  bool IsActive() const { return active; }

  void AddMessageHook(NGameX::IChatMessageHook* const hook);
  void RemoveMessageHook(NGameX::IChatMessageHook* const hook);

  void LoadPlayerIcons(const NDb::AdvMapDescription* const mapDesc, const nstl::vector<NCore::PlayerStartInfo>& playerStartInfos) const;

  void Reset();

  void NotifyChatMuted(const NWorld::PFPlayer* const player);

private:
  typedef nstl::list<Strong<NGameX::IChatMessageHook>> MessageHooks;
  
  typedef int TPlayerId;
  typedef unsigned long long TUserId;

  typedef CObj<PFUIEvent> UIEventPtr;


  void DispatchMuteEvent(const UIEventPtr& event);
  void AddMessageFromSign(const PFUISignMessageToChat* const sign, const NDb::EMessage messageId);
  void AddAutoMuteCondion(const int playerId, const EPlayerBehaviourEvent::Enum );

  void AddMessageToChatOutput( const wstring & message, NDb::EChatChannel channel, const wstring & playerName, const TUserId userId );
  void AddChannel(NGameX::IFlashChat * _flashChat, NDb::EChatChannel channel, bool canWrite2Channel);

  bool HookMessageReceived(gamechat::ChatMessage& message) const;

  void SetPlayerIcon(const int playerId, const nstl::string& path) const;
  void SetPlayerHeroId(const int playerId, const int heroId, const int teamId) const;

  TPlayerId GetPlayerIdByUserId(const TUserId userId) const;

  Strong<IPlayerIdMapper> playerIdMapper;
  Strong<IgnoreListController> ignoreListController;
  StrongMT<gamechat::IClient> chatClient;
  Weak<BindsController> bindsController;
  //nstl::list<Weak<UI::FlashContainer2>> flashContainers;
  nstl::list<Weak<IFlashChat>> flashChats;


  NDb::Ptr<NDb::DBUIData>     uiData;
  NDb::Ptr<NDb::AILogicParameters>     aiLogicParams;
  bool isChatVisible;
  vector<gamechat::ChatMessage> allMessages;

  CObj<NGameX::PFUIEvent> evAdminMuted;
  CObj<NGameX::PFUIEvent> evAdminMutedNotify;
  CObj<NGameX::PFUIEvent> evLeaverMuted;
  CObj<NGameX::PFUIEvent> evLeaverPartyMuted;

  Strong<AsyncMessagesFilter> asyncFilter;

  bool isMuted;
  bool isLeaver;
  bool isLeaverParty;

  bool active;
  bool chatOffSendedToFlash;

  MessageHooks messageHooks;

  friend AsyncMessagesFilter;
};

}
