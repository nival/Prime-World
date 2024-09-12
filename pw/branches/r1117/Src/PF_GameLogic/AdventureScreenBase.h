#pragma once

#include "Core/WorldBase.h"
#include "Core/GameTypes.h"
#include "Client/AdventureScreenBaseClient.h"
#include "PlayerData.h"

#include "PF_Core/World.h"

#include "IAdventureScreen.h"

namespace NWorld
{
  class PFWorld;
  class PFBaseUnit;
  class PFPlayer;
}

namespace NCore
{
  class ITransceiver;
}

namespace NGameX
{

class Minimap;
class ObjectsInfo2dLogic;

class AdventureScreenBase : public NMainLoop::AdventureScreenBaseClient, public IAdventureScreen
{
  NI_DECLARE_REFCOUNT_CLASS_2( AdventureScreenBase, NMainLoop::AdventureScreenBaseClient, IAdventureScreen );

public:
  AdventureScreenBase();
  ~AdventureScreenBase()
  {
  }

  virtual bool Init( UI::User * uiUser );
  virtual bool InitAdventuresBase( NCore::MapStartInfo const& info, NCore::ITransceiver *_pTransceiver, int myPlayerId, bool isSpectator = false );
  virtual NWorld::PFWorld* GetWorld() = 0;
  virtual PlayerDataManager *GetPlayerDataMan() const = 0;
  virtual Minimap* GetMinimap() const = 0;
  virtual ObjectsInfo2dLogic* GetObjInfo2d() const = 0;
  virtual void SetActiveChat(bool isActiveChat) = 0;
  virtual NWorld::PFBaseUnit *GetMainUnit() = 0;
  virtual NWorld::PFPlayer const *GetPlayer() const = 0;
  
  virtual void SetTimeScale(float timescale) = 0;
  virtual void OnTimeScaleChanged(float timescale) = 0;

  bool IsInReplayMode() const;
  
  void CloseScreen();

protected:
  NCore::MapStartInfo    startInfo;

  Weak<NCore::ITransceiver> pTransceiver;
  int playerId;
private:
};
} // namespace NGameX
