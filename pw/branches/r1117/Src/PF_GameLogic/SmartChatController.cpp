#include "stdafx.h"
#include "SmartChatController.h"
#include "DBStats.h"
#include "DBSmartChat.h"
#include "NivalInput/Binds.h"
#include "NivalInput/ControlsSet.h"
#include "NivalInput/InputCommandInstance.h"
#include "IFlashChat.h"
#include "UI/FlashContainer2.h"
#include "FlashFSCommands.h"
#include "BindsController.h"
#include "Client/GameChatClient/IGameChatClient.h"

#include "PFPlayer.h"
#include "AdventureScreen.h"
#include "MarkersController.h"
#include "SmartChatAntiSpam.h"

//#define SMART_CHAT_OWN_CANCEL

NI_DEFINE_REFCOUNT(NGameX::IFlashSmartChat)
NI_DEFINE_REFCOUNT(NGameX::ISmartChatCallback)
NI_DEFINE_REFCOUNT(NGameX::ISmartChatAntiSpam)
NI_DEFINE_REFCOUNT(NGameX::SmartChatController)

namespace
{
  const nstl::string smartChatTechnicalBindSection("$smart_chat_tech_section");
  const nstl::string smartChatTechnicalCommand("$smart_chat_tech_command");
  const nstl::string smartChatNA("[n/a]");
  const nstl::string smartChatPlus("+");

  const nstl::wstring smartChatMessagePrefix = L"smartchat://";

  static inline bool IsSmartChatMessage(const nstl::wstring& s)
  {
    return (s.find(smartChatMessagePrefix) == 0);
  }

  static inline bool TryExplodeSmartChatMesssage(nstl::wstring& s)
  {
    const size_t index = s.find(smartChatMessagePrefix);

    if (index == nstl::wstring::npos)
      return false;

    s.erase(0, smartChatMessagePrefix.length());

    return true;
  }

  static inline nstl::wstring MakeSmartChatMessage(const nstl::wstring& s)
  {
    if (IsSmartChatMessage(s))
      return s;

    return (smartChatMessagePrefix + s);
  }
}

namespace NGameX
{
  namespace SmartChat
  {
    namespace Private
    {
      typedef nstl::vector<CategoryPtr> CategoryVector;
      typedef nstl::vector<MessagePtr> MessageVector;

      static inline GroupPtr GetGroup(const CategoryPtr& p) { return GroupPtr(p); }
      static inline GroupPtr GetGroup(const ConfigurationPtr& p) { return GroupPtr(p); }

      static inline bool IsGroupEmpty(const GroupPtr& p)
      {
        if (!IsValid(p))
          return true;

        return
          p->categories.empty() &&
          p->messages.empty();
      }

      static inline bool IsGroupEmpty(const CategoryPtr& p) { return IsGroupEmpty(GetGroup(p)); }
      static inline bool IsGroupEmpty(const ConfigurationPtr& p) { return IsGroupEmpty(GetGroup(p)); }

      struct UpdateGuard : public NonCopyable
      {
        explicit UpdateGuard(IFlashSmartChat* const flashChat)
          : flashChat(flashChat)
        {
          flashChat->SmartChatBeginUpdate();
        }
        ~UpdateGuard()
        {
          flashChat->SmartChatEndUpdate();
        }
      private:
        UpdateGuard();

        IFlashSmartChat* const flashChat;
      };

      typedef nstl::string BindSection;
      typedef nstl::vector<BindSection> BindSectionStack;

      struct BindSectionGuard : public NonCopyable
      {
        BindSectionGuard(Input::Binds* const binds, const BindSection& section, BindSectionStack& stack)
          : binds(binds)
          , stack(stack)
        {
          stack.push_back(section);

          Apply();
        }
        ~BindSectionGuard()
        {
          DeactivateTop();

          stack.pop_back();

          Apply();
        }
      private:
        BindSectionGuard();

        void Apply()
        {
          if (stack.empty())
            binds->SetCurrentConfigSection(0);
          else
            binds->SetCurrentConfigSection(stack.back().c_str());
        }

        void DeactivateTop()
        {
          if (stack.empty())
            ;
          else
            binds->DeactivateSection(stack.back().c_str());
        }

        Input::Binds* const binds;
        BindSectionStack& stack;
      };

      struct BindTool : public NonCopyable
      {
        BindTool()
        {

        }

        bool RecoverBind(Input::ICommandInstance* const command, Input::Binds* const binds)
        {
          controlIds.clear();
          controlNames.clear();

          keys.clear();

          if (!command)
            return false;
          if (!binds)
            return false;

          Input::ICommandInstanceImplementation* const impl = static_cast<Input::ICommandInstanceImplementation*>(command);
          Input::TControlsSet& controlSets = impl->AccessControlsSet();

          const int bindCount = controlSets.size();

          NI_VERIFY(bindCount > 0, NStr::StrFmt("SmartChat command \"%s\" is not bound at all!", command->Name().c_str()), return false);
          NI_VERIFY(bindCount < 2, NStr::StrFmt("SmartChat command \"%s\" has multiple binds!", command->Name().c_str()), return false);

          controlSets.front()->GetControls(controlIds);
          controlNames.resize(controlIds.size());

          for (int i = 0, count = controlIds.size(); i < count; ++i)
          {
            controlNames[i] = binds->HwInput()->ControlName(controlIds[i]);
          }

          keys = NStr::Join(controlNames.begin(), controlNames.end(), smartChatPlus);

          return true;
        }

        bool Rebind(Input::ICommandInstance* const command, Input::Binds* const binds) const
        {
          if (!command)
            return false;
          if (!binds)
            return false;

          if (controlNames.empty())
            return false;

          Input::ICommandInstanceImplementation* const impl = static_cast<Input::ICommandInstanceImplementation*>(command);
          Input::TControlsSet& controlSets = impl->AccessControlsSet();

          controlSets.clear();

          Input::ICommandInstance* const boundCommand = binds->DefineCommand(command->Name().c_str(), false, controlNames);

          NI_VERIFY(boundCommand == command, NStr::StrFmt("SmartChat rebound command \"%s\" does not match it's original!", command->Name().c_str()), return false);

          return true;
        }

        nstl::vector<int> controlIds;
        nstl::vector<nstl::string> controlNames;

        nstl::string keys;
      };

      struct Builder : public NonCopyable
      {
        struct Item
        {
          Model::ItemId id;
          nstl::string sid;
        };

        enum
        {
          itemIdBufferLength = 32
        };

        Builder(IFlashSmartChat* const flashChat, ISmartChatCallback* const callback, Input::BindsContainer* const dispatcher)
          : flashChat(flashChat)
          , callback(callback)
          , binds(Input::BindsManager::Instance()->GetBinds())
          , dispatcher(dispatcher)
          , itemId(0)
        {
          // hacky
          itemIdHead = itemIdBuffer;
          itemIdTail = itemIdBuffer + sprintf_s(itemIdBuffer, "__smart_chat_");
        }

        void Build(ConfigurationPtr configuration)
        {
          if (IsGroupEmpty(configuration))
          {
            DebugTrace("SmartChat: empty configuration");
            return;
          }

          DoBuild(configuration);

          #pragma REMINDER("Get rid of this hack")
          // HACK: удаление команды безусловно "дергает" UpdateAllCommandsSupersets()
          // некоторые ControlsSet'ы были уничтожены в процессе ребинда
          // необходимо обеспечить консистентность ссылок
          binds->DeleteCommand(smartChatTechnicalCommand.c_str());
        }
      private:
        void DoBuild(ConfigurationPtr configuration)
        {
          PrepareCancelAction(configuration->cancelCommandId);

          const UpdateGuard updateGuard(flashChat);

          {
            Item item;

            OnItem(item);

            RegisterCategory(item, item);

            const BindSectionGuard bindSectionGuard(binds, item.sid, bindSectionStack);

            OnGroup(GetGroup(configuration), item, item);
          }
        }

        void OnGroup(GroupPtr group, const Item& item, const Item& parentItem)
        {
          {
            CategoryVector::const_iterator it = group->categories.begin();
            CategoryVector::const_iterator it_end = group->categories.end();
            for (; it != it_end; ++it)
            {
              CategoryVector::const_reference category = *it;

              if (!IsValid(category))
                continue;

              OnCategory(category, item);
            }
          }

          {
            MessageVector::const_iterator it = group->messages.begin();
            MessageVector::const_iterator it_end = group->messages.end();
            for (; it != it_end; ++it)
            {
              MessageVector::const_reference message = *it;

              if (!IsValid(message))
                continue;

              OnMessage(message);
            }
          }

          OnCancel();
        }

        void OnCategory(CategoryPtr category, const Item& parentItem)
        {
          Item item;

          OnItem(item);

          RegisterCategory(item, parentItem);
          RegisterCategoryHandler(item, category);

          const nstl::string keys(ProcessCommand(category->commandId) ? GetKeys() : smartChatNA);

          const BindSectionGuard bindSectionGuard(binds, item.sid, bindSectionStack);

          flashChat->SmartChatBeginCategory(item.id, keys, category->name.GetText());

          OnGroup(GetGroup(category), item, parentItem);

          flashChat->SmartChatEndCategory();
        }

        void OnMessage(MessagePtr message)
        {
          Item item;

          OnItem(item);

          RegisterMessage(item, message);
          RegisterMessageHandler(item, message);

          const nstl::string keys(ProcessCommand(message->commandId) ? GetKeys() : smartChatNA);

          flashChat->SmartChatAddMessage(item.id, keys, message->text.GetText());
        }

        void OnCancel()
        {
          Item item;

          OnItem(item);

          RegisterCancel(item);

          flashChat->SmartChatAddCancel(item.id, cancelKeys);
        }

        void OnItem(Item& item)
        {
          NStr::ItoA(itemId, itemIdTail, itemIdBufferLength - (itemIdTail - itemIdHead) - 1);

          item.id = itemId;
          item.sid.assign(itemIdHead);

          ++itemId;
        }

        void RegisterCategory(const Item& item, const Item& parentItem)
        {
          const Model::Category category = { item.sid, parentItem.id };

          callback->SmartChatRegisterCategory(item.id, category);
        }

        void RegisterMessage(const Item& item, const MessagePtr& dbMessage)
        {
          const Model::Message message = { NStr::ToUnicode(dbMessage->commandId), dbMessage };

          callback->SmartChatRegisterMessage(item.id, message);
        }

        void RegisterCancel(const Item& item)
        {
          callback->SmartChatRegisterCancel(item.id);
        }

        void RegisterCategoryHandler(const Item& item, const CategoryPtr& dbCategory)
        {
          dispatcher->AddActivationHandler(dbCategory->commandId.c_str(), &ISmartChatCallback::SmartChatHandleCategoryCommand, item.id);
        }

        void RegisterMessageHandler(const Item& item, const MessagePtr& dbMessage)
        {
          dispatcher->AddActivationHandler(dbMessage->commandId.c_str(), &ISmartChatCallback::SmartChatHandleMessageCommand, item.id);
        }

        bool ProcessCommand(const nstl::string& commandId)
        {
          Input::ICommandInstance* const command = binds->FindCommand(commandId.c_str());

          NI_VERIFY(!!command, NStr::StrFmt("SmartChat command \"%s\" not found!", commandId.c_str()), return false);

          if (!bindTool.RecoverBind(command, binds))
            return false;
          if (!bindTool.Rebind(command, binds))
            return false;

          return true;
        }

        const nstl::string& GetKeys() const
        {
          return bindTool.keys;
        }

        void PrepareCancelAction(const nstl::string& commandId)
        {
          dispatcher->AddActivationHandler(commandId.c_str(), &ISmartChatCallback::SmartChatHandleCancelCommand);

          const BindSectionGuard bindSectionGuard(binds, smartChatTechnicalBindSection, bindSectionStack);

          cancelKeys = (ProcessCommand(commandId) ? GetKeys() : smartChatNA);
        }

        IFlashSmartChat* const flashChat;
        ISmartChatCallback* const callback;

        Input::Binds* const binds;
        Input::BindsContainer* const dispatcher;

        BindSectionStack bindSectionStack;
        BindTool bindTool;

        nstl::string cancelKeys;

        Model::ItemId itemId;

        char itemIdBuffer[itemIdBufferLength];

        char* itemIdHead;
        char* itemIdTail;
      };
    }
  }
}

namespace NGameX
{

  SmartChatController::SmartChatController(gamechat::IClient* chatClient)
    : chatClient(chatClient)
    , enabled(false)
    , active(false)
    , gameLoading(false)
    , activeCategory(0)
  {
    {
      using namespace NDb;

      const Ptr<DBUIData> uiData(Get<DBUIData>(DBID("UI/Content/_.UIDT.xdb")));

      if (!IsValid(uiData))
      {
        DebugTrace("SmartChat: UI data is inaccessible");
        return;
      }

      if (!IsValid(uiData->smartChat))
      {
        DebugTrace("SmartChat: configuration not defined");
        return;
      }

      configuration = uiData->smartChat;
    }

    enabled = true;
  }

  SmartChatController::~SmartChatController()
  {

  }

  void SmartChatController::EnableCategory(const SmartChat::Model::ItemId categoryId)
  {
    SmartChat::Model::Categories::const_iterator it = categories.find(categoryId);

    if (it == categories.end())
      return;

    const SmartChat::Model::Category& category = it->second;

    ActivateBindSection(category.bindSection);
  }

  void SmartChatController::DisableCategory(const SmartChat::Model::ItemId categoryId)
  {
    SmartChat::Model::Categories::const_iterator it = categories.find(categoryId);

    if (it == categories.end())
      return;

    const SmartChat::Model::Category& category = it->second;

    DeactivateBindSection(category.bindSection);
  }

  bool SmartChatController::ProcessUIEvent(const Input::Event& event)
  {
    if (!active)
      return false;

    return handlers.ProcessEvent(event, this);
  }

  void SmartChatController::AddSmartChatUI(UI::FlashContainer2* const flashContainer, IFlashSmartChat* const flashSmartChat)
  {
    if (!flashContainer)
      return;
    if (!flashSmartChat)
      return;

    flashChatController = flashSmartChat;

    if (!IsOperational())
      return;

    flashContainer->AddFSListner(ConvertToString(FlashFSCommands::ActivateSmartChat), this);
    flashContainer->AddFSListner(ConvertToString(FlashFSCommands::ActivateSmartChatCategory), this);
    flashContainer->AddFSListner(ConvertToString(FlashFSCommands::DeactivateSmartChat), this);
    flashContainer->AddFSListner(ConvertToString(FlashFSCommands::ClickSmartChatItem), this);

    SmartChat::Private::Builder(flashSmartChat, this, &handlers).Build(configuration);

    DebugTrace("SmartChat: ready");
  }

  bool SmartChatController::SmartChatHandleCategoryCommand(const SmartChat::Model::ItemId& id)
  {
    if (!IsActive())
      return false;

    GoToCategory(id);

    return true;
  }

  bool SmartChatController::SmartChatHandleMessageCommand(const SmartChat::Model::ItemId& id)
  {
    if (!IsActive())
      return false;

    if (Use())
      SendMessage(id);

    Close();

    return true;
  }

  bool SmartChatController::SmartChatHandleCancelCommand()
  {
    if (!IsActive())
      return false;

#ifdef SMART_CHAT_OWN_CANCEL
#if 0
    if (activeCategory == 0)
      Close();
    else
      GoToParentCategory(activeCategory);
#else
    Close();
#endif
#endif // SMART_CHAT_CANCEL

    return true;
  }

  void SmartChatController::SmartChatRegisterCategory(const SmartChat::Model::ItemId& id, const SmartChat::Model::Category& category)
  {
    itemTypes[id] = SmartChat::Model::ItemType::Category;

    categories[id] = category;
  }

  void SmartChatController::SmartChatRegisterMessage(const SmartChat::Model::ItemId& id, const SmartChat::Model::Message& message)
  {
    itemTypes[id] = SmartChat::Model::ItemType::Message;

    messages[id] = message;

    dbMessagesByCommandId[message.commandId] = message.dbMessage;
  }

  void SmartChatController::SmartChatRegisterCancel(const SmartChat::Model::ItemId& id)
  {
    itemTypes[id] = SmartChat::Model::ItemType::Cancel;
  }

  void SmartChatController::OnFSCommand(UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW)
  {
    switch (FlashFSCommands::ConvertToFSCommand(listenerID))
    {
    case FlashFSCommands::ActivateSmartChat:
      {
        NI_VERIFY(IsOperational(), "SmartChat is not operational!", break);

        OnActivate();
      }
      break;
    case FlashFSCommands::ActivateSmartChatCategory:
      {
        NI_VERIFY(IsActive(), "SmartChat is inactive!", break);

        unsigned category;

        sscanf_s(args, "%u", &category);

        OnActivateCategory(category);
      }
      break;
    case FlashFSCommands::DeactivateSmartChat:
      {
        NI_VERIFY(IsOperational(), "SmartChat is not operational!", break);

        OnDeactivate();
      }
      break;
    case FlashFSCommands::ClickSmartChatItem:
      {
        NI_VERIFY(IsOperational(), "SmartChat is not operational!", break);

        unsigned id;

        sscanf_s(args, "%u", &id);

        // item id was not set
        if (id == 0xFFFFFFFF)
        {
          WarningTrace("SmartChat: clicked on item with invalid id!");
          break;
        }

        OnClickItem(id);
      }
      break;
    default:
      break;
    }
  }

  bool SmartChatController::IsOperational() const
  {
    if (!IsValid(flashChatController))
      return false;
    if (!enabled)
      return false;

    return true;
  }

  bool SmartChatController::IsActive() const
  {
    if (!IsOperational())
      return false;

    return active;
  }

  void SmartChatController::OnDeactivate()
  {
    if (!active)
      return;

    if (IsValid(bindsController))
      bindsController->SetEnabled(BindsController::Chat, true);

    DeactivateBindSection(smartChatTechnicalBindSection);
    DisableCategory(activeCategory);

    active = false;
    activeCategory = 0;
  }

  void SmartChatController::OnActivate()
  {
    if (active)
      return;

    if (IsValid(bindsController))
      bindsController->SetEnabled(BindsController::Chat, false);

    ActivateBindSection(smartChatTechnicalBindSection);

    active = true;
  }

  void SmartChatController::OnActivateCategory(const SmartChat::Model::ItemId id)
  {
    DisableCategory(activeCategory);

    activeCategory = id;

    EnableCategory(activeCategory);
  }

  void SmartChatController::OnClickItem(const SmartChat::Model::ItemId itemId)
  {
    struct Local
    {
      static SmartChat::Model::ItemType::Enum GetItemType(const SmartChat::Model::ItemIdToItemTypeMap& itemTypes, const SmartChat::Model::ItemId itemId)
      {
        SmartChat::Model::ItemIdToItemTypeMap::const_iterator it = itemTypes.find(itemId);

        if (it == itemTypes.end())
          return SmartChat::Model::ItemType::Undefined;

        return it->second;
      }
    };

    const SmartChat::Model::ItemType::Enum itemType = Local::GetItemType(itemTypes, itemId);

    switch (itemType)
    {
    case SmartChat::Model::ItemType::Category:
      SmartChatHandleCategoryCommand(itemId);
      break;
    case SmartChat::Model::ItemType::Message:
      SmartChatHandleMessageCommand(itemId);
      break;
    case SmartChat::Model::ItemType::Cancel:
      SmartChatHandleCancelCommand();
      break;
    default:
      ErrorTrace("SmartChat: click on invalid item! (%u)", itemId);
      Close();
      break;
    }
  }

  void SmartChatController::ActivateBindSection(const nstl::string& section)
  {
    if (Input::Binds* const binds = Input::BindsManager::Instance()->GetBinds())
      binds->ActivateSection(section.c_str());
  }

  void SmartChatController::DeactivateBindSection(const nstl::string& section)
  {
    if (Input::Binds* const binds = Input::BindsManager::Instance()->GetBinds())
      binds->DeactivateSection(section.c_str());
  }

  void SmartChatController::GoToCategory(const SmartChat::Model::ItemId id)
  {
    SmartChat::Model::Categories::const_iterator it = categories.find(id);

    if (it == categories.end())
      return;

    flashChatController->SmartChatActivateCategory(id);
  }

  void SmartChatController::GoToParentCategory(const SmartChat::Model::ItemId id)
  {
    SmartChat::Model::Categories::const_iterator it = categories.find(id);

    if (it == categories.end())
      return;

    const SmartChat::Model::Category& category = it->second;

    flashChatController->SmartChatActivateCategory(category.parentCategoryId);
  }

  void SmartChatController::SendMessage(const SmartChat::Model::ItemId id)
  {
    SmartChat::Model::Messages::const_iterator it = messages.find(id);

    if (it == messages.end())
      return;

    const SmartChat::Model::Message& message = it->second;

    if (IsValid(chatClient))
    {
      const nstl::wstring payload(MakeSmartChatMessage(message.commandId));

      chatClient->SendMsg(payload, gamechat::ChannelType::SmartChat);
    }
  }

  void SmartChatController::Close()
  {
    flashChatController->SmartChatDeactivate();
  }

  bool SmartChatController::MessageReceived(gamechat::ChatMessage& message)
  {
    if (message.channel == gamechat::ChannelType::SmartChat)
    {
      if (!TryExplodeSmartChatMesssage(message.message))
        return false;
      if (!IsOperational())
        return false;

      SmartChat::Model::CommandIdToMessageMap::const_iterator it = dbMessagesByCommandId.find(message.message);

      if (it == dbMessagesByCommandId.end())
        return false;

      SmartChat::MessagePtr dbMessage = it->second;

      message.message = dbMessage->text.GetText();

      if (!gameLoading && dbMessage->showMarker)
        AddMarker(message.userId);
    }

    return true;
  }

  void SmartChatController::OnFastReconnect(gamechat::IClient * _chatClient)
  {
    chatClient = _chatClient;
  }

  void SmartChatController::AddMarker(const ChatUserId userId)
  {
    // TODO: better way?
    if (AdventureScreen* const advScreen = AdventureScreen::Instance())
    {
      if (NWorld::PFPlayer* const player = advScreen->GetWorld()->GetPlayerByUID(userId))
      {
        if (NWorld::PFBaseHero* const hero = player->GetHero())
        {
          if (hero->IsDead())
            return;

          advScreen->GetMarkersController()->AddChatMarker(hero);
        }
      }
    }
  }

  void SmartChatController::Reset()
  {
    OnDeactivate();
  }

  bool SmartChatController::Use() const
  {
    if (!IsValid(antiSpam))
      return true;

    return antiSpam->UseSmartChat();
  }

}
