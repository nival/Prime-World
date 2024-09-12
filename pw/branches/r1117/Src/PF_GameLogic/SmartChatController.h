#pragma once

#include "../libdb/Db.h"
#include "UI/FSCommandListner.h"
#include "NivalInput/BindsContainer.h"
#include "IChatMessageHook.h"

namespace Input
{
  class Binds;
}

namespace NDb
{
  struct SmartChatGroup;
  struct SmartChatMessage;
  struct SmartChatCategory;
  struct SmartChatConfiguration;
}

namespace NGameX
{
  _interface IFlashSmartChat;
  _interface ISmartChatCallback;
  _interface ISmartChatAntiSpam;

  class BindsController;
  class GenericAbuseController;

  namespace SmartChat
  {
    typedef NDb::Ptr<NDb::SmartChatGroup> GroupPtr;
    typedef NDb::Ptr<NDb::SmartChatMessage> MessagePtr;
    typedef NDb::Ptr<NDb::SmartChatCategory> CategoryPtr;
    typedef NDb::Ptr<NDb::SmartChatConfiguration> ConfigurationPtr;

    namespace Model
    {
      namespace ItemType
      {
        enum Enum
        {
          Undefined,
          Category,
          Message,
          Cancel,
        };
      }

      typedef unsigned ItemId;

      struct Category
      {
        nstl::string bindSection;
        ItemId parentCategoryId;
      };

      struct Message
      {
        nstl::wstring commandId;
        MessagePtr dbMessage;
      };

      typedef nstl::map<ItemId, Category> Categories;
      typedef nstl::map<ItemId, Message> Messages;

      typedef nstl::map<ItemId, ItemType::Enum> ItemIdToItemTypeMap;

      typedef nstl::hash_map<nstl::wstring, MessagePtr> CommandIdToMessageMap;
    }
  }

  _interface ISmartChatCallback : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1(ISmartChatCallback, IBaseInterfaceST);

    virtual bool SmartChatHandleCategoryCommand(const SmartChat::Model::ItemId& id) = 0;
    virtual bool SmartChatHandleMessageCommand(const SmartChat::Model::ItemId& id) = 0;
    virtual bool SmartChatHandleCancelCommand() = 0;

    virtual void SmartChatRegisterCategory(const SmartChat::Model::ItemId& id, const SmartChat::Model::Category& category) = 0;
    virtual void SmartChatRegisterMessage(const SmartChat::Model::ItemId& id, const SmartChat::Model::Message& message) = 0;
    virtual void SmartChatRegisterCancel(const SmartChat::Model::ItemId& id) = 0;
  };

  class SmartChatController
    : public BaseObjectST
    , public ISmartChatCallback
    , public UI::IFSCommandListner
    , public NGameX::IChatMessageHook
  {
    NI_DECLARE_REFCOUNT_CLASS_4(SmartChatController, BaseObjectST, ISmartChatCallback, UI::IFSCommandListner, NGameX::IChatMessageHook);
  public:
    explicit SmartChatController(gamechat::IClient* chatClient);
    virtual ~SmartChatController();

    void OnFastReconnect(gamechat::IClient * _chatClient);

    void OnStartLoading() { gameLoading = true; }
    void OnFinishLoading() { gameLoading = false; }

    bool ProcessUIEvent(const Input::Event& event);

    void AddSmartChatUI(UI::FlashContainer2* const flashContainer, IFlashSmartChat* const flashSmartChat);

    void SetAntiSpam(ISmartChatAntiSpam* const value) { antiSpam = value; }
    void SetBindsController(BindsController* const value) { bindsController = value; }

    bool IsActive() const;

    void Reset();
  protected:
    // ISmartChatCallback
    virtual bool SmartChatHandleCategoryCommand(const SmartChat::Model::ItemId& id);
    virtual bool SmartChatHandleMessageCommand(const SmartChat::Model::ItemId& id);
    virtual bool SmartChatHandleCancelCommand();

    virtual void SmartChatRegisterCategory(const SmartChat::Model::ItemId& id, const SmartChat::Model::Category& category);
    virtual void SmartChatRegisterMessage(const SmartChat::Model::ItemId& id, const SmartChat::Model::Message& message);
    virtual void SmartChatRegisterCancel(const SmartChat::Model::ItemId& id);

    // UI::IFSCommandListener
    virtual void OnFSCommand(UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW);

    // NGameX::IChatMessageHook
    virtual bool MessageReceived(gamechat::ChatMessage& message);
  private:
    bool IsOperational() const;

    void EnableCategory(const SmartChat::Model::ItemId categoryId);
    void DisableCategory(const SmartChat::Model::ItemId categoryId);

    void ActivateBindSection(const nstl::string& section);
    void DeactivateBindSection(const nstl::string& section);

    void OnDeactivate();
    void OnActivate();
    void OnActivateCategory(const SmartChat::Model::ItemId id);
    void OnClickItem(const SmartChat::Model::ItemId itemId);

    void GoToCategory(const SmartChat::Model::ItemId id);
    void GoToParentCategory(const SmartChat::Model::ItemId id);
    void SendMessage(const SmartChat::Model::ItemId id);
    void Close();

    bool Use() const;

    // TODO: import chat::CustomId
    typedef unsigned long long ChatUserId;

    void AddMarker(const ChatUserId userId);

    StrongMT<gamechat::IClient> chatClient;

    Weak<ISmartChatAntiSpam> antiSpam;
    Weak<BindsController> bindsController;
    Weak<IFlashSmartChat> flashChatController;

    SmartChat::ConfigurationPtr configuration;

    SmartChat::Model::Categories categories;
    SmartChat::Model::Messages messages;

    SmartChat::Model::ItemIdToItemTypeMap itemTypes;

    SmartChat::Model::CommandIdToMessageMap dbMessagesByCommandId;

    bool enabled;
    bool active;

    bool gameLoading;

    SmartChat::Model::ItemId activeCategory;

    Input::BindsContainer handlers;
  };
}
