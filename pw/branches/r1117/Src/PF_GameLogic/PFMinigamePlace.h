#pragma once

#ifndef VISUAL_CUTTED

#include "PFBuildings.h"
#include "DBMinigamesTypes.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
  class Minigames;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{
  class PFClientMinigamePlace;
}

namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseHero;
class PFEaselPlayer;

class PFMinigamePlace : public PFBuilding
{
	WORLD_OBJECT_METHODS_WITH_CLIENT(0x9D62D3C0, PFMinigamePlace, NGameX::PFClientMinigamePlace )

public:
	PFMinigamePlace(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);
  virtual ~PFMinigamePlace();

  bool IsAvailable();

  void OnPlayerEnter();
  void OnPlayerLeave();

  float GetPlaceRadiusPow2() const { return radiusPow2; }

  void SetEaselPlayer( PFEaselPlayer * _easelPlayer ) { easelPlayer = _easelPlayer; }
  PFEaselPlayer * CurrentEaselPlayer() const { return IsValid( easelPlayer ) ? easelPlayer : 0; }

  const Placement& GetMinigamePlacement() const;

  const NDb::Ptr<NDb::MinigamePlace>& GetMinigamePlaceDB() const { return minigamePlaceDB; }

  const string & MinigameId() const { return minigameId; }

  // returns invalid ptr if there is no visual state change params
  NDb::Ptr<NDb::MinigameVisualStateChange> ChangeVisualState(NDb::MinigameVisualState _state, NDb::MinigameClientType _clientType);
	virtual void Reset();
  virtual CObj<PFAbilityInstance> Use( PFBaseUnit* pUser );
  virtual bool CanBeUsedBy( PFBaseHero const* pHero ) const;
  virtual float GetUseRange( PFBaseUnit* pUser ) const { return 0.0f; }
protected:
  PFMinigamePlace() { type = NDb::UNITTYPE_MINIGAMEPLACE; }
  
  virtual bool Step(float dtInSeconds);

  NScene::AnimatedPlacement animatedPlacement;

  ZDATA_(PFBuilding);
  float radiusPow2;
  float scale;
  CPtr<PFEaselPlayer> easelPlayer;
  Placement basePlacement;
	string minigameId;
  ZNOCRC
  NDb::MinigameVisualState visualState;
  NDb::Ptr<NDb::MinigamePlace> minigamePlaceDB;
  NDb::ChangesApplyType placementApplyType;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBuilding*)this); f.Add(2,&radiusPow2); f.Add(3,&scale); f.Add(4,&easelPlayer); f.Add(5,&basePlacement); f.Add(6,&minigameId);  if(!f.IsChecksum()){ f.Add(7,&visualState); f.Add(8,&minigamePlaceDB); f.Add(9,&placementApplyType);  } return 0; }


private:

  void ChangePositionForVisualState(const NDb::MinigameVisualStateChange& _stateChangeParams);

  // returns invalid ptr if there is no visual state change params
  NDb::Ptr<NDb::MinigameVisualStateChange> GetVisualStateChangeParams(NDb::MinigameVisualState fromState
    , NDb::MinigameVisualState toState, NDb::MinigameClientType _clientType);
};

} // namespace NWorld

#endif

