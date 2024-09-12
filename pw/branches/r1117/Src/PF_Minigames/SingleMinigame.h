#pragma once

#include "MinigameBase.h"
#include "../PF_GameLogic/DBMinigamesTypes.h"
#include "../Scene/DBScene.h"
#include "../Scene/AnimatedPlacement.h"

namespace NScene
{
  _interface IScene;
}

namespace PF_Minigames
{

class Minigames;

// class provides common functionality for minigames like state, camera and position changing, scene and minigames bindings, etc 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SingleMinigame : public MinigameBase
{
public:
  SingleMinigame();
  virtual ~SingleMinigame() {}

  bool InitMinigames( Minigames * _minigames, NScene::IScene * _scene );

  NDb::MinigameVisualState    GetVisualState() const  { return visualState; }
  NDb::MinigameClientType     GetClientType() const   { return clientType; }

  const CPtr<NWorld::PFMinigamePlace>&  GetMinigamePlace() const  { return place; }

protected:
  SingleMinigame( NDb::MinigameClientType _clientType );
  void ChangeVisualState(NDb::MinigameVisualState _state);

  void SetMinigamePlace( NWorld::PFMinigamePlace * _place ) { place =_place; }

  //ISingleMinigame
  virtual void Update( float deltaTime, bool gameOnPause );
  virtual void SessionFinished( bool victory );
  virtual void Eject();

  //own methods
  virtual bool OnInit() { return true; }
  virtual void OnChangeVisualState( NDb::MinigameVisualState _oldState, NDb::MinigameVisualState _newState ) {}
  virtual void OnPlacementChanged( const Placement & _oldPlacement, const Placement & _newPlacement ) {}


private:
  void SetVisualStateChangeCamera(const NDb::MinigameVisualStateChange& _stateChangeParams);
  void SetVisualStateChangePosition(const NDb::MinigameVisualStateChange& _stateChangeParams);

  void UpdateCamera();
  void UpdatePlacement();

  NDb::MinigameVisualState visualState;
  NDb::MinigameClientType clientType;

  CPtr<NWorld::PFMinigamePlace> place;

  NDb::ChangesApplyType placementApplyType;
  Placement currentPlacement;
};



} // PF_Minigames
