#include "StdAfx.h"
#include "ChatController.h"
#include "IFlashChat.h"
#include "FlashFSCommands.h"
#include "ui/FlashContainer2.h"
#include "DBStats.h"
#include "IgnoreListController.h"
#include "FlashFSCommands.h"
#include "Tools/Censor/CensorDll.h"
#include "IChatMessageHook.h"
#include <cwctype>

// IMPORT: NWorld::FindHero
#include "HeroSpawn.h"

namespace
{
  static bool g_chatVisible = true;
  REGISTER_DEV_VAR( "chat_visible", g_chatVisible, STORAGE_NONE );

  static bool g_useBadWordsFilter = true;
  REGISTER_VAR( "use_badwords_filter", g_useBadWordsFilter, STORAGE_USER );

  // NUM_TASK
  //static bool g_receiveRegularChatMessages = true;
  //REGISTER_VAR( "receive_regular_chat_messages", g_receiveRegularChatMessages, STORAGE_USER );
  
  static bool g_sessionChatOff = false;
  REGISTER_VAR( "session_chat_off", g_sessionChatOff, STORAGE_USER );

  DEV_VAR_STATIC bool g_chatMuted = false;
  DEV_VAR_STATIC bool g_chatLeaverMuted = false;
  DEV_VAR_STATIC bool g_chatLeaverPartyMuted = false;

  REGISTER_DEV_VAR("chat_muted", g_chatMuted, STORAGE_NONE);
  REGISTER_DEV_VAR("chat_leaver_muted", g_chatLeaverMuted, STORAGE_NONE);
  REGISTER_DEV_VAR("chat_leaver_party_muted", g_chatLeaverPartyMuted, STORAGE_NONE);
}

namespace
{
  bool isLower(wchar_t ch)
 {
    return (bool)std::iswlower(ch);
 }

  bool isUpperString(const wstring& s )
  {
    wstring::const_iterator cit = find_if(s.begin(), s.end(), isLower);
    if(cit !=s.end())
      return false;
    else
      return true;
  }

  NDb::EChatChannel ChannelTypeToChannel(const gamechat::ChannelType::Enum channelType)
  {
    switch (channelType)
    {
    case gamechat::ChannelType::Global:
      return NDb::CHATCHANNEL_GLOBAL;
    case gamechat::ChannelType::MyTeam:
      return NDb::CHATCHANNEL_MYTEAM;
    case gamechat::ChannelType::Session:
      return NDb::CHATCHANNEL_BOTHTEAMS;
    case gamechat::ChannelType::SmartChat:
      return NDb::CHATCHANNEL_SMARTCHAT;
    default:
      NI_ALWAYS_ASSERT("Invalid chat channel type!");
      return NDb::CHATCHANNEL_MYTEAM;
    }
  }

  gamechat::ChannelType::Enum ChannelToChannelType(const NDb::EChatChannel channel)
  {
    switch (channel)
    {
    case NDb::CHATCHANNEL_GLOBAL:
      return gamechat::ChannelType::Global;
    case NDb::CHATCHANNEL_MYTEAM:
      return gamechat::ChannelType::MyTeam;
    case NDb::CHATCHANNEL_BOTHTEAMS:
      return gamechat::ChannelType::Session;
    case NDb::CHATCHANNEL_SMARTCHAT:
      return gamechat::ChannelType::SmartChat;
    default:
      NI_ALWAYS_ASSERT("Invalid chat channel!");
      return gamechat::ChannelType::Invalid;
    }
  }
}


namespace NGameX
{
ChatUiController::ChatUiController( gamechat::IClient * _chatClient )
  : chatClient(_chatClient)
  , isChatVisible(true)
  , isMuted(false)
  , isLeaver(false)
  , isLeaverParty(false)
  , active(false)
{
  uiData = NDb::Get<NDb::DBUIData>( NDb::DBID( "UI/Content/_.UIDT.xdb" ) );
  aiLogicParams = NDb::Get<NDb::AILogicParameters>( NDb::DBID( "GameLogic/AILogic.AILP") );
  
  const NDb::Ptr<NDb::UIEventsCustom> uiEvents(NDb::SessionRoot::GetRoot()->visualRoot->uiEvents);

  if (IsValid(uiEvents))
  {
    if (IsValid(uiEvents->evAdminMuted))
      evAdminMuted = new NGameX::PFUIEvent(uiEvents->evAdminMuted, NULL);
    if (IsValid(uiEvents->evAdminMutedNotify))
      evAdminMutedNotify = new NGameX::PFUIEvent(uiEvents->evAdminMutedNotify, NULL);
    if (IsValid(uiEvents->evLeaverMuted))
      evLeaverMuted = new NGameX::PFUIEvent(uiEvents->evLeaverMuted, NULL);
    if (IsValid(uiEvents->evLeaverPartyMuted))
      evLeaverPartyMuted = new NGameX::PFUIEvent(uiEvents->evLeaverPartyMuted, NULL);
  }

  asyncFilter = new AsyncMessagesFilter(this);
}

void ChatUiController::OnFastReconnect( gamechat::IClient * _chatClient, IgnoreListStorage * _ignoreStorage )
{
  chatClient = _chatClient;

  if (ignoreListController)
    ignoreListController->OnFastReconnect(_ignoreStorage);
}

void ChatUiController::AddChatUI( UI::FlashContainer2* _flashContainer, IFlashChat * _flashChat, const bool muted, const bool leaver, const bool leaverParty )
{
  using namespace FlashFSCommands;

  if (!_flashContainer || !_flashChat || !IsValid(uiData))
    return;

  _flashContainer->AddFSListner(ConvertToString(FlashFSCommands::SendMessage), this);
  _flashContainer->AddFSListner(ConvertToString(FlashFSCommands::ActivateChatInput), this);

  AddChannel(_flashChat, NDb::CHATCHANNEL_SYSTEM, false);
  AddChannel(_flashChat, NDb::CHATCHANNEL_ACHIEVMENTS, false);
  AddChannel(_flashChat, NDb::CHATCHANNEL_BOTHTEAMS, true);
  AddChannel(_flashChat, NDb::CHATCHANNEL_MYTEAM, true);
  AddChannel(_flashChat, NDb::CHATCHANNEL_SMARTCHAT, false);

  _flashChat->SetDefaultChannel(NDb::CHATCHANNEL_MYTEAM);
  chatOffSendedToFlash = g_sessionChatOff;
  _flashChat->SetChatOff(g_sessionChatOff);

  isMuted = muted;
  isLeaver = leaver;
  isLeaverParty = leaverParty;

  flashChats.push_back(_flashChat);
}


void ChatUiController::AddChannel( NGameX::IFlashChat * _flashChat, NDb::EChatChannel channel, bool canWrite2Channel )
{
  const NDb::ChatChannelDescription & channelDesc = uiData->chatChannelDescriptions[channel];
  // virtual void AddChannel(NDb::EChatChannel channel,  const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel) = 0;
  _flashChat->AddChannel(channel, channelDesc.channelName.GetText(), channelDesc.channelColor.Dummy, channelDesc.showChannelName, channelDesc.showPlayerName, canWrite2Channel)  ;

  for (int i = 0; i<channelDesc.shortcuts.size();i++)
  {
    const wstring & shorcut = channelDesc.shortcuts[i].GetText();
    if (!canWrite2Channel || shorcut.length()<=0)
      continue;

    //  virtual void AddChannelShortCut(NDb::EChatChannel channel, const char * shortcut) = 0;
    _flashChat->AddChannelShortCut(channel, shorcut.c_str());
  }
}

void ChatUiController::Update()
{
  if (chatClient && ignoreListController)
  {
    typedef vector<gamechat::ChatMessage> TChatMessages;

    TChatMessages newMessages;

    chatClient->Step();
    chatClient->GetNewMessages(newMessages);

    allMessages.insert(allMessages.end(), newMessages.begin(), newMessages.end());

    TChatMessages::iterator it = newMessages.begin();
    TChatMessages::iterator it_end = newMessages.end();
    nstl::map<TUserId, int> uMessCount;
    for (; it != it_end; ++it)
    {
      TChatMessages::reference chatMessage = *it;

      // TODO: ?
      if (chatMessage.messageType != gamechat::ChatMessage::Predefined)
        continue;

      const bool isRegularChatMessage =
        (chatMessage.channel == gamechat::ChannelType::MyTeam) ||
        (chatMessage.channel == gamechat::ChannelType::Session); 
        
        nstl::map<TUserId, int>::const_iterator cit = uMessCount.find(chatMessage.userId);
        if(cit!= uMessCount.end())
          uMessCount[chatMessage.userId] +=1; 
        else
          uMessCount[chatMessage.userId] =1; 

      if (isRegularChatMessage)
      {
        if (chatMessage.message.size() >=aiLogicParams->behaviourTrackerParams->autoMuteMessageLength)
        {
          PlayerBehaviourTracking::DispatchEvent(chatMessage.userId, EPlayerBehaviourEvent::AutoMuteMessageLength);
        }
        if (isUpperString(chatMessage.message))
        {
          PlayerBehaviourTracking::DispatchEvent(chatMessage.userId, EPlayerBehaviourEvent::CapsMeessage);
        }
        if(uMessCount[chatMessage.userId]>=aiLogicParams->behaviourTrackerParams->autoMuteMinMessage)
        {
          PlayerBehaviourTracking::DispatchEvent(chatMessage.userId, EPlayerBehaviourEvent::AutoMuteMessage);
        }  
      

      if ( g_sessionChatOff)
      {
        // NUM_TASK свои сообщения всё же должны получать
        if (chatMessage.userId != chatClient->GetGameUserId())
          continue;
      }
    }

      const bool proceed = HookMessageReceived(chatMessage);

      if (!proceed)
        continue;

      const bool canIgnore = (chatMessage.channel != gamechat::ChannelType::SmartChat);

      if (canIgnore && ignoreListController->IsIgnored(chatMessage.userId))
        continue;

      const bool needFilter = (chatMessage.channel != gamechat::ChannelType::SmartChat);

    

      if (needFilter && g_useBadWordsFilter)
      {
        asyncFilter->FilterMessage(chatMessage);
        
      }
      else{
        AddMessageToChatOutput(chatMessage.message, ChannelTypeToChannel(chatMessage.channel), chatMessage.nickname, chatMessage.userId);
      }
    }

    if (g_useBadWordsFilter)
      asyncFilter->ProcessMessages();
  }

  if (isChatVisible != g_chatVisible)
  {
    isChatVisible = g_chatVisible;
    
    for (nstl::list<Weak<IFlashChat>>::iterator i = flashChats.begin(); i!=flashChats.end(); i++)
    {
      IFlashChat * flashChat = *i;

      if (flashChat)
        flashChat->SetChatVisible(isChatVisible);
    }
  }

    if (chatOffSendedToFlash != g_sessionChatOff)
    {
      chatOffSendedToFlash = g_sessionChatOff;

      for (nstl::list<Weak<IFlashChat>>::iterator i = flashChats.begin(); i!=flashChats.end(); i++)
      {
        IFlashChat * flashChat = *i;

        if (flashChat)
        {
          flashChat->SetChatOff(g_sessionChatOff);
        }
      }
    }
}

void ChatUiController::AddMessageToChatOutput( const wstring & message, NDb::EChatChannel channel, const wstring & playerName, const TUserId userId )
{
  const int playerId = GetPlayerIdByUserId(userId);

  for (nstl::list<Weak<IFlashChat>>::iterator i = flashChats.begin(); i!=flashChats.end(); i++)
  {
    IFlashChat * flashChat = *i;

    if (flashChat)
      flashChat->AddMessage(channel, playerName, message, playerId);
  }
}

void ChatUiController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  switch (FlashFSCommands::ConvertToFSCommand(listenerID))
  {
  case FlashFSCommands::ActivateChatInput:
    {

      if (!bindsController)
        break;

      int isChatActivated;
      sscanf_s(args,"%d", &isChatActivated);

      bindsController->SetEnabled(BindsController::Chat,!isChatActivated);

      active = !!isChatActivated;

      break;
    }
  case FlashFSCommands::SendMessage:
    {
      const wchar_t* const p0 = argsW;
      const wchar_t* const p1 = wcschr(p0, L' ') + 1;

      int channelID;

      swscanf_s(p0, L"%d", &channelID);

      wstring message(p1);

      NStr::TrimBoth(message);

      if (message.empty())
        return;

      if (isMuted || g_chatMuted)
      {
        DispatchMuteEvent(evAdminMuted);
        return;
      }

      const NDb::EChatChannel channel = static_cast<NDb::EChatChannel>(channelID);

      if (channel == NDb::CHATCHANNEL_BOTHTEAMS)
      {
        if (isLeaver || g_chatLeaverMuted)
        {
          DispatchMuteEvent(evLeaverMuted);
          return;
        }

        if (isLeaverParty || g_chatLeaverPartyMuted)
        {
          DispatchMuteEvent(evLeaverPartyMuted);
          return;
        }
      }

      if (!g_sessionChatOff)
      {
        if (!chatClient)
        {
          //Send message to myself directly
          AddMessageToChatOutput(message, channel, L"Very Local User", 0ULL);
        }
        else
        {
          chatClient->SendMsg(message, ChannelToChannelType(channel));
        }
      }

      break;
    }
  }
}

void ChatUiController::AddChatMessage( const wstring & msg, NDb::EChatChannel channel)
{
  AddMessageToChatOutput(msg, channel, wstring(), 0ULL);
}

void ChatUiController::SetIgnoreListController(IgnoreListController* ilc)
{
  ignoreListController = ilc;
}

void ChatUiController::SetPlayerIdMapper(IPlayerIdMapper* pim)
{
  playerIdMapper = pim;
}

int AsyncMessagesFilter::FilterMessage(const gamechat::ChatMessage& msg)
{
  int id = CensorFilter::FilterAsync(msg.message.c_str());
  toFilterIdxOrder.push_back(id);
  toFilter.insert( make_pair(id, FilteredMessageData(msg)) );
  return id;
}

void AsyncMessagesFilter::ProcessMessages()
{
  int id;
  wchar_t str[8192];  
  while(CensorFilter::GetFilteredAsync(id, str, 8192))
  {
    toFilter[id].message.message = str;
    toFilter[id].filtered = true;
  }

  while (!toFilterIdxOrder.empty())
  {
    int id = toFilterIdxOrder.front();
    FilteredMessageData& res = toFilter[id];
    if ( res.filtered )
    {
      pChatController->AddMessageToChatOutput(res.message.message, ChannelTypeToChannel(res.message.channel), res.message.nickname, res.message.userId);
      toFilterIdxOrder.pop_front();
      toFilter.erase(id);
    }
    else
      
      break;
  }
}

void ChatUiController::AddMessageHook(NGameX::IChatMessageHook* const hook)
{
  if (!hook)
    return;

  const Strong<NGameX::IChatMessageHook> ptr(hook);

  if (nstl::find(messageHooks.begin(), messageHooks.end(), ptr) != messageHooks.end())
    return;

  messageHooks.push_back(ptr);
}

void ChatUiController::RemoveMessageHook(NGameX::IChatMessageHook* const hook)
{
  if (!hook)
    return;

  const Strong<NGameX::IChatMessageHook> ptr(hook);

  messageHooks.remove(ptr);
}

bool ChatUiController::HookMessageReceived(gamechat::ChatMessage& message) const
{
  MessageHooks::const_iterator it = messageHooks.begin();
  MessageHooks::const_iterator it_end = messageHooks.end();
  for (; it != it_end; ++it)
  {
    if (!(*it)->MessageReceived(message))
      return false;
  }

  return true;
}

void ChatUiController::LoadPlayerIcons(const NDb::AdvMapDescription* const mapDesc, const nstl::vector<NCore::PlayerStartInfo>& playerStartInfos) const
{
  const NDb::Ptr<NDb::HeroesDB> heroes(NDb::SessionRoot::GetRoot()->logicRoot->heroes);

  typedef vector<NCore::PlayerStartInfo> PSIVector;

  PSIVector::const_iterator it = playerStartInfos.begin();
  PSIVector::const_iterator it_end = playerStartInfos.end();
  for (; it != it_end; ++it)
  {
    PSIVector::const_reference psi = *it;

    const NDb::BaseHero* const dbHero = NWorld::FindHero(heroes, mapDesc, psi.playerInfo.heroId);
    if (!dbHero)
      continue;

    switch (psi.teamID)
    {
    case NCore::ETeam::Team1:
      if (dbHero->minimapIconA)
        SetPlayerIcon(psi.playerID, dbHero->minimapIconA->textureFileName);
      break;
    case NCore::ETeam::Team2:
      if (dbHero->minimapIconB)
        SetPlayerIcon(psi.playerID, dbHero->minimapIconB->textureFileName);
      break;
    }

    SetPlayerHeroId(psi.playerID, psi.userID, psi.teamID);
  }
}

void ChatUiController::SetPlayerIcon(const int playerId, const nstl::string& path) const
{
  typedef nstl::list<Weak<IFlashChat>> FlashChatList;

  FlashChatList::const_iterator it = flashChats.begin();
  FlashChatList::const_iterator it_end = flashChats.end();
  for (; it != it_end; ++it)
  {
    FlashChatList::const_reference flashChat = *it;

    if (!IsValid(flashChat))
      continue;

    flashChat->SetPlayerIcon(playerId, path);
  }
}

void ChatUiController::SetPlayerHeroId(const int playerId, const int heroId, const int teamId) const
{
  typedef nstl::list<Weak<IFlashChat>> FlashChatList;

  FlashChatList::const_iterator it = flashChats.begin();
  FlashChatList::const_iterator it_end = flashChats.end();
  for (; it != it_end; ++it)
  {
    FlashChatList::const_reference flashChat = *it;

    if (!IsValid(flashChat))
      continue;

    flashChat->SetPlayerHeroId(playerId, heroId, teamId);
  }
}

void ChatUiController::Reset()
{
  active = false;
}

ChatUiController::TPlayerId ChatUiController::GetPlayerIdByUserId(const TUserId userId) const
{
  if (!playerIdMapper)
    return -1;
  if (userId == 0ULL)
    return -1;

  return playerIdMapper->GetPlayerId(userId);
}

void ChatUiController::DispatchMuteEvent(const UIEventPtr& event)
{
  typedef vector<CObj<PFUISign>> UISignList;

  if (!IsValid(event))
    return;

  const PFUIEventData& eventData = event->GetEventData();
  const UISignList& signs = eventData.signs;

  UISignList::const_iterator it = signs.begin();
  UISignList::const_iterator it_end = signs.end();
  for (; it != it_end; ++it)
  {
    UISignList::const_reference sign = *it;

    if (!IsValid(sign))
      continue;

    if (sign->signType != NDb::SIGN_SEND_MESSAGE_TO_CHAT)
      continue;

    const CDynamicCast<PFUISignMessageToChat> actualSign(sign);

    if (!IsValid(actualSign))
      continue;

    AddMessageFromSign(actualSign, event->GetCurMessageID());
  }
}

void ChatUiController::AddMessageFromSign(const PFUISignMessageToChat* const sign, const NDb::EMessage messageId)
{
  if (!sign)
    return;

  // check for known enum
  {
    if (messageId < 0)
      return;
    if (messageId >= NDb::KnownEnum<NDb::EMessage>::SizeOf())
      return;
  }

  wstring message;

  PrecompiledTooltip tooltip;

  tooltip.Parse(sign->messages[messageId]);
  tooltip.MakeText(message);

  AddChatMessage(message, sign->GetChannel());
}

void ChatUiController::NotifyChatMuted(const NWorld::PFPlayer* const player)
{
  typedef vector<CObj<PFUISign>> UISignList;

  if (!IsValid(evAdminMutedNotify))
    return;

  const PFUIEventData& eventData = evAdminMutedNotify->GetEventData();
  const UISignList& signs = eventData.signs;

  UISignList::const_iterator it = signs.begin();
  UISignList::const_iterator it_end = signs.end();
  for (; it != it_end; ++it)
  {
    UISignList::const_reference sign = *it;

    if (!IsValid(sign))
      continue;

    if (sign->signType != NDb::SIGN_SEND_MESSAGE_TO_CHAT)
      continue;

    const CDynamicCast<PFUISignMessageToChat> actualSign(sign);

    if (!IsValid(actualSign))
      continue;

    const NDb::EMessage messageId = evAdminMutedNotify->GetCurMessageID();

    // check for known enum
    {
      if (messageId < 0)
        continue;
      if (messageId >= NDb::KnownEnum<NDb::EMessage>::SizeOf())
        continue;
    }

    wstring message;

    PrecompiledTooltip tooltip;

    tooltip.Parse(actualSign->messages[messageId]);
    tooltip.ResolveVariants(player);
    tooltip.MakeText(message);

    AddChatMessage(message, actualSign->GetChannel());
  }
}

}

NI_DEFINE_REFCOUNT(NGameX::IFlashChat)
NI_DEFINE_REFCOUNT(NGameX::IChatMessageHook)
NI_DEFINE_REFCOUNT(NGameX::ChatUiController)
