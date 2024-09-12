#include "stdafx.h"

#include "SingleMinigame.h"

#include "Minigames.h"
#include "MinigameCameraController.h"

#include "../Scene/DiAnGrUtils.h"

#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/PFMinigamePlace.h"
#include "../PF_GameLogic/PFClientMinigamePlace.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleMinigame::SingleMinigame() :
visualState(NDb::MINIGAMEVISUALSTATE_NONE),
clientType(NDb::MINIGAMECLIENTTYPE_ANY),
placementApplyType(NDb::CHANGESAPPLYTYPE_DONOTAPPLY)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleMinigame::SingleMinigame(NDb::MinigameClientType _clientType) :
visualState(NDb::MINIGAMEVISUALSTATE_NONE),
clientType(_clientType),
placementApplyType(NDb::CHANGESAPPLYTYPE_DONOTAPPLY)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::ChangeVisualState(NDb::MinigameVisualState _state)
{
  if ( !IsValid( GetMinigamePlace() ) )
    return;

  NDb::Ptr<NDb::MinigameVisualStateChange> stateChange = GetMinigamePlace()->ChangeVisualState(_state, GetClientType());

  if(IsValid(stateChange))
  {
    SetVisualStateChangeCamera(*stateChange);
    SetVisualStateChangePosition(*stateChange);
  }

  OnChangeVisualState( GetVisualState(), _state);
  visualState = _state;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SingleMinigame::InitMinigames( Minigames * _minigames, NScene::IScene * _scene )
{
  MinigameBase::InitMinigames( _minigames, _scene );
  return OnInit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::Update( float deltaTime, bool gameOnPause )
{
  if ( gameOnPause )
    return;

  UpdateCamera();
  UpdatePlacement();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::SessionFinished( bool victory )
{
  if ( IsValid( GetMinigames() ) && IsValid( GetMinigames()->GetWorldSessionInterface() ) )
    GetMinigames()->GetWorldSessionInterface()->OnLeaveMinigameCmd();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::Eject()
{
  NI_ALWAYS_ASSERT("Eject() not implemented!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::UpdateCamera()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::UpdatePlacement()
{
  if(placementApplyType ==  NDb::CHANGESAPPLYTYPE_DONOTAPPLY || placementApplyType == NDb::CHANGESAPPLYTYPE_APPLYDEFAULT)
  {
    return;
  }

  NI_VERIFY(IsValid( GetMinigames() ), "", return);
  NI_VERIFY(IsValid( GetMinigamePlace() ), "", return);

  Placement newPlacement = GetMinigamePlace()->GetMinigamePlacement();

  if( memcmp(&newPlacement, &currentPlacement, sizeof(Placement)) == 0)
  {
    return;
  }

  CPtr<MinigameCameraController> cameraController = GetMinigames()->GetCameraController();
  if ( IsValid( cameraController ) )
  {
    cameraController->SetTarget( newPlacement );
  }

  OnPlacementChanged(currentPlacement, newPlacement);
  currentPlacement = newPlacement;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::SetVisualStateChangeCamera(const NDb::MinigameVisualStateChange& _stateChangeParams)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SingleMinigame::SetVisualStateChangePosition(const NDb::MinigameVisualStateChange& _stateChangeParams)
{
  placementApplyType = _stateChangeParams.changePlacement;

  UpdatePlacement();
}

} //namespace PF_Minigames
