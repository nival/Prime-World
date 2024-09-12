#include "StdAfx.h"
#include "IgnoreListController.h"

#include "IgnoreListStorage.h"

#include "AdventureFlashInterface.h"
#include "FlashFSCommands.h"
#include "ui/FlashContainer2.h"
#include "Client/GameChatClient/IGameChatClient.h"

#include "DBStats.h"

#include "PFWorld.h"
#include "PFPlayer.h"

#include "PlayerInfoHelper.hpp"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////

Strong<IPlayerIdMapper> PlayerIdMapper::Create(const NCore::TPlayersStartInfo& playerStartInfos)
{
  class Impl
    : public IPlayerIdMapper
    , public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2(Impl, IPlayerIdMapper, BaseObjectST);
  public:
    explicit Impl(const NCore::TPlayersStartInfo& playerStartInfos)
      : playerStartInfos(playerStartInfos)
      , nicknameDummy()
    {

    }

    virtual TPlayerId GetPlayerId(const TUserId userId) const
    {
      const NCore::PlayerStartInfo* const psi = PlayerInfoHelper::FindPlayerInfoByUserId(playerStartInfos, userId);

      if (!psi)
        return -1;

      return psi->playerID;
    }

    virtual TUserId GetUserId(const TPlayerId playerId) const
    {
      const NCore::PlayerStartInfo* const psi = PlayerInfoHelper::FindPlayerInfoByPlayerId(playerStartInfos, playerId);

      if (!psi)
        return 0ULL;

      return psi->userID;
    }

    virtual const TUserNickname& GetUserNicknameByPlayerId(const TPlayerId playerId) const
    {
      const NCore::PlayerStartInfo* const psi = PlayerInfoHelper::FindPlayerInfoByPlayerId(playerStartInfos, playerId);

      if (!psi)
        return nicknameDummy;

      return psi->nickname;
    }
  private:
    Impl() {}

    const NCore::TPlayersStartInfo playerStartInfos;
    const TUserNickname nicknameDummy;
  };

  Impl* const p = new Impl(playerStartInfos);

  return p;
}

//////////////////////////////////////////////////////////////////////////

IgnoreListController::IgnoreListController(const CreateStruct& cs)
  : ignoreListStorage(cs.ignoreListStorage)
  , playerIdMapper(cs.playerIdMapper)
  , flashInterface(cs.flashInterface)
  , uiData(cs.uiData)
{
  DoInit(cs.flashContainer);
}

void IgnoreListController::OnUserAddedToIgnoreList(const TUserId auid)
{
  if (!flashInterface)
    return;

  flashInterface->IgnoreUser(GetPlayerIdByUserId(auid));
}

void IgnoreListController::OnUserRemovedFromIgnoreList(const TUserId auid)
{
  if (!flashInterface)
    return;

  flashInterface->RemoveIgnore(GetPlayerIdByUserId(auid));
}

bool IgnoreListController::IsIgnored(const TUserId auid) const
{
  if (!ignoreListStorage)
    return false;

  return ignoreListStorage->ContainsUser(auid);
}

void IgnoreListController::InvalidateFlashInterface()
{
  if (!flashInterface)
    return;

  const IgnoreList::TUserSet& ignoredUsers = ignoreListStorage->GetIgnoredUsers();

  IgnoreList::TUserSet::const_iterator it = ignoredUsers.begin();
  IgnoreList::TUserSet::const_iterator it_end = ignoredUsers.end();
  for (; it != it_end; ++it)
  {
    flashInterface->IgnoreUser(GetPlayerIdByUserId(*it));
  }
}

void IgnoreListController::OnFastReconnect(IgnoreListStorage *_ignoreListStorage)
{
  ignoreListStorage = _ignoreListStorage;

  if (ignoreListStorage)
    ignoreListStorage->AddListener(this);
}

void IgnoreListController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  if (!ignoreListStorage)
    return;

  const TPlayerId playerId = NStr::ToInt(args);
  const TUserId userId = GetUserIdByPlayerId(playerId);

  if (userId == 0U)
    return;

  switch (ConvertToFSCommand(listenerID))
  {
  case IgnoreUser:
    DevTrace("IgnoreList: Ignore #%llu", userId);
    ignoreListStorage->AddUserNickname(userId, GetUserNicknameByPlayerId(playerId));
    ignoreListStorage->AddUser(userId);
    break;
  case RemoveIgnoreFromUser:
    DevTrace("IgnoreList: Forgive #%llu", userId);
    ignoreListStorage->RemoveUser(userId);
    break;
  }
}

NGameX::TPlayerId IgnoreListController::GetPlayerIdByUserId(const TUserId userId) const
{
  if (!playerIdMapper)
    return -1;
  if (userId == 0ULL)
    return -1;

  return playerIdMapper->GetPlayerId(userId);
}

NGameX::TUserId IgnoreListController::GetUserIdByPlayerId(const TPlayerId playerId) const
{
  if (!playerIdMapper)
    return 0ULL;
  if (playerId < 0)
    return 0ULL;

  return playerIdMapper->GetUserId(playerId);
}

const TUserNickname& IgnoreListController::GetUserNicknameByPlayerId(const TPlayerId playerId) const
{
  static const TUserNickname l_dummy;

  if (!playerIdMapper)
    return l_dummy;
  if (playerId < 0)
    return l_dummy;

  return playerIdMapper->GetUserNicknameByPlayerId(playerId);
}

void IgnoreListController::DoInit(UI::FlashContainer2* const flashContainer)
{
  using namespace FlashFSCommands;

  if (!ignoreListStorage)
    return;

  ignoreListStorage->AddListener(this);

  flashContainer->AddFSListner(ConvertToString(IgnoreUser), this);
  flashContainer->AddFSListner(ConvertToString(RemoveIgnoreFromUser), this);
}

}

NI_DEFINE_REFCOUNT(NGameX::IPlayerIdMapper)
NI_DEFINE_REFCOUNT(NGameX::IgnoreListController)
