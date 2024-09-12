#include "stdafx.h"

#include "Scripts/lua.hpp"

#include "Core/CoreFSM.h"
#include "Core/GameTypes.h"

#include "Client/ScreenCommands.h"

#include "Scene/Scene.h"
#include "Scene/CameraControllersContainer.h"

#include "MinigameCameraController.h"
#include "MinigameLobbyScreenLogic.h"
#include "MinigameLobbyScreen.h"
#include "Minigames.h"
#include "MinigamesMain.h"

#include "MinigameCommands.h"

static float minigameCameraMoveMaxWaitTime = 5.0f;
REGISTER_DEV_VAR("MinigamesCameraMoveMaxWaitTime", minigameCameraMoveMaxWaitTime, STORAGE_NONE);

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( MinigameLobbyScreenLogic, MinigameScreenLogic )
END_LUA_TYPEINFO( MinigameLobbyScreenLogic )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameLobbyScreenLogic::MinigameLobbyScreenLogic() :
cameraPositionSave( VNULL3 ),
waitForCameraMovement( 0 )
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameLobbyScreenLogic::InitScene( PF_Minigames::Minigames* _minigames )
{
  NI_ASSERT(!waitForCameraMovement, "MinigameLobbyScreenLogic: previous close screen operation doesn't complete yet")

  waitForCameraMovement = 0;
  minigames = _minigames;

  CPtr<NScene::IScene> scene = minigames->GetNativeMain()->GetScene();
  CPtr<NScene::ICamera> camera = scene->GetCamera();

  camera->GetPosition( &saveCameraParams );

  cameraPositionSave = saveCameraParams.vAnchor;
  cameraFOVSave = camera->GetFOV();

  cameraController = new PF_Minigames::MinigameCameraController();

  scene->GetCameraControllers()->AddCameraController( cameraController );
  minigames->SetCameraController( cameraController );

  cameraController->ChangeCamera( minigames->GetNativeMain()->GetCommonDBData()->cameraOptions );
  cameraController->EnableInterpolation( minigames->GetNativeMain()->GetCommonDBData()->smoothCamera );
  cameraController->ApplyResolutionModifcators();
	cameraController->SetTarget( minigames->GetPlacement());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameLobbyScreenLogic::OnBecameFront()
{
  minigames->GetCameraController()->ChangeCamera( minigames->GetNativeMain()->GetCommonDBData()->cameraOptions );
  minigames->GetCameraController()->ApplyResolutionModifcators();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameLobbyScreenLogic::ExitLobby()
{
  NI_ASSERT( screen->State() == ELobbyScreenState::Normal, "" );
  NI_ASSERT( !waitForCameraMovement, "MinigameLobbyScreenLogic: previous close screen operation doesn't complete yet" )
  NI_ASSERT( IsValid( screen ), "Screen not set" );

  screen->SetState( ELobbyScreenState::Exiting );

  NScene::IScene * scene = minigames->GetNativeMain()->GetScene();
  NScene::ICamera * camera = scene->GetCamera();

  if (camera)
    camera->SetFOV(cameraFOVSave);

  if ( cameraController )
  {
    cameraController->ChangeCamera( saveCameraParams );
    cameraController->SetTarget( CVec3( 0, 0, 0 ) );
    cameraController->LockTarget( true );
  }

  waitForCameraMovement = max( minigameCameraMoveMaxWaitTime, 0.0001f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameLobbyScreenLogic::Step( float deltaTime )
{
  if ( screen->State() != ELobbyScreenState::Exiting )
    return;
  NI_ASSERT( waitForCameraMovement > 0, "Lobby exit sequence internal error" );

  waitForCameraMovement -= deltaTime;

  if ( cameraController )
    if ( waitForCameraMovement > 0 )
      if( !cameraController->IsCameraInWantedPosition() )
        return;

  NI_ASSERT( waitForCameraMovement > 0, "Minigame camera timedout!" );

  if ( cameraController )
    cameraController->LockTarget( false );

  cameraController = 0;

  DebugTrace( "Starting leaving minigame..." ); //NUM_TASK debugging

  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( screen ) );

  minigames->ForceLeaveMinigame();

  waitForCameraMovement = 0.0f;

  screen->SetState( ELobbyScreenState::Finished );
}

} //namespace PF_Minigames
