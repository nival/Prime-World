#include "stdafx.h"
#include "EaselScreenLobby.h"

#include "../Core/CoreFSM.h"
#include "../Client/ScreenCommands.h"

#include "Minigames.h"

#include "MinigameCameraController.h"

#include "EaselMinigame.h"
#include "EaselScreenLogicLobby.h"

NI_DEFINE_REFCOUNT(PF_Minigames::EaselScreenLobby)

namespace PF_Minigames
{

REGISTER_SCREEN(EaselScreenLobby)  // PF_Minigames

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLobby::EaselScreenLobby() :
maxLevel(1)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLobby::~EaselScreenLobby()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLobby::AssociateWithMinigames( Minigames & minigames )
{
	NI_VERIFY( !IsValid( GetMinigames() ) , "Easel screen can be associated only once", return );
  SetMinigames( &minigames );

  EaselMinigame *_client = GetMinigames()->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY(IsValid(_client),"Missing EaselMinigame object", return);

  localEasel = _client->GetLocalEasel();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLobby::Init( UI::User * uiUser )
{
  if( !IsValid( GetMinigames() ) )
  {
    return false;
  }

	// create and init ui logic
	logic = new EaselScreenLogicLobby;

  //Some crazy pointers exchange...
  SetLogic( logic );
  SetLobbyLogic( logic );
  logic->SetUser( uiUser );

  MinigameLobbyScreen::Init( uiUser ); //Very tight call order!

  logic->Init( GetMinigames(), maxLevel + 1 );
  logic->LoadScreenLayout("Minigame02Lobby");
  logic->InitLayout();
  logic->UpdateBoostsImages();

  // change camera
  lastCamera = GetMinigames()->GetCameraController()->GetCameraParams();
  
  if( IsValid( localEasel ) )
  {
    const NDb::ViewCamera& camera =  localEasel->GetData()->commonParams->camera;
    GetMinigames()->GetCameraController()->ChangeCamera(camera);
    GetMinigames()->GetCameraController()->ApplyResolutionModifcators();
    GetMinigames()->GetCameraController()->SetTarget(localEasel->GetPlacement());
  }

	return true;
}

void EaselScreenLobby::SetMaxLevel( int _maxLevel ) 
{  
  maxLevel = _maxLevel;
  if(IsValid(logic))
    logic->SetMaxLevel(_maxLevel+1);
}

void EaselScreenLobby::UpdateLobby()
{
  if(IsValid(logic))
  {
    logic->UpdateLobby();
    logic->UpdateBoostsImages();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLobby::OnBeforeClose()
{
  NI_VERIFY( IsValid( GetMinigames()), "EaselScreen: associated minigames is already dead", return true );

//  GetMinigames()->GetCameraController()->ChangeCamera(lastCamera);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLobby::OnBecameFront()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLobby::OnNewFront(IScreenBase * pNewFrontScreen)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLobby::ProcessEaselEvent( const Input::Event & message )
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLobby::ProcessUIEvent( const Input::Event & message )
{
  if( MinigameLobbyScreen::ProcessUIEvent( message ) )
    return true;

	// process inputs for easel minigame
	if( ProcessEaselEvent( message ) )
		return true;

	return false;
}

}
