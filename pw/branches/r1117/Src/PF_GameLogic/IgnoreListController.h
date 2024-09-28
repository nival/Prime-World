#pragma once
#include "IgnoreListStorage.h"
#include "../UI/FSCommandListner.h"
#include "Core/GameTypes.h"

namespace UI            
{ 
  class FlashContainer2; 
}

namespace NGameX
{
  _interface IFlashChat;
  class IgnoreListStorage;
}

namespace Chat
{
  class ChatClient;
}

namespace NDb
{
  struct DBUIData;
}

namespace gamechat
{
  class IClient;
}



namespace NGameX
{

typedef int TPlayerId;

// TODO: ?
_interface IPlayerIdMapper : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1(IPlayerIdMapper, IBaseInterfaceST);
public:
  virtual TPlayerId GetPlayerId(const TUserId userId) const = 0;
  virtual TUserId GetUserId(const TPlayerId playerId) const = 0;

  virtual const TUserNickname& GetUserNicknameByPlayerId(const TPlayerId playerId) const = 0;
};

class PlayerIdMapper
{
public:
  static Strong<IPlayerIdMapper> Create(const NCore::TPlayersStartInfo& playerStartInfos);
};

class IgnoreListController: public IIgnoreListListener, public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_3( IgnoreListController, IIgnoreListListener, UI::IFSCommandListner, BaseObjectST );
public:
  struct CreateStruct
  {
    UI::FlashContainer2*        flashContainer;
    Strong<IFlashChat>          flashInterface;
    Strong<IgnoreListStorage>   ignoreListStorage;
    Strong<IPlayerIdMapper>     playerIdMapper;
    NDb::Ptr<NDb::DBUIData>     uiData;
  };

  explicit IgnoreListController(const CreateStruct& cs);

  void InvalidateFlashInterface();
  bool IsIgnored(const TUserId auid) const;
  void OnFastReconnect(IgnoreListStorage *_ignoreListStorage);

  // IIgnoreListListener
  virtual void OnUserAddedToIgnoreList(const TUserId auid);
  virtual void OnUserRemovedFromIgnoreList(const TUserId auid);

  // UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:

  void DoInit(UI::FlashContainer2* const flashContainer);

  TPlayerId GetPlayerIdByUserId(const TUserId userId) const;
  TUserId GetUserIdByPlayerId(const TPlayerId playerId) const;

  const TUserNickname& GetUserNicknameByPlayerId(const TPlayerId playerId) const;

  Weak<IgnoreListStorage>     ignoreListStorage;
  Strong<IPlayerIdMapper>     playerIdMapper;
  Strong<IFlashChat>          flashInterface;
  NDb::Ptr<NDb::DBUIData>     uiData;

};
}
