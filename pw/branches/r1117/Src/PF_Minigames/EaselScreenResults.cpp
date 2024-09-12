#include "stdafx.h"
#include "EaselScreenResults.h"

#include "../Core/CoreFSM.h"
#include "../Client/ScreenCommands.h"

#include "Minigames.h"

#include "MinigameCameraController.h"

//#include "Easel.h"
#include "EaselMinigame.h"
#include "EaselScreenLogicResults.h"

NI_DEFINE_REFCOUNT(PF_Minigames::EaselScreenResults)

namespace PF_Minigames
{

REGISTER_SCREEN(EaselScreenResults)  // PF_Minigames

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenResults::EaselScreenResults()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenResults::~EaselScreenResults()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenResults::AssociateWithMinigames(Minigames& minigames)
{
  NI_VERIFY( !IsValid( associatedMinigames ) , "EaselScreenResults: Easel screen can be associated only once", return );
	associatedMinigames = &minigames;

  CPtr<EaselMinigame> _client = associatedMinigames->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY(IsValid(_client),"Missing EaselMinigame object", return);

  localEasel = _client->GetLocalEasel();
}

#pragma region IScreenBase 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenResults::Init( UI::User * uiUser )
{
  if( !IsValid( associatedMinigames ) )
    return false;

	// create and init ui logic
	logic = new EaselScreenLogicResults;
  logic->SetUser( uiUser );

  NI_VERIFY(IsValid(logic), "EaselScreenResults: Easel lobby screen creation failed", return false);

  SetLogic(logic);

  logic->Init( associatedMinigames );	
  logic->LoadScreenLayout("Minigame02Results");

  // change camera
  lastCamera = associatedMinigames->GetCameraController()->GetCameraParams();

  if( IsValid( localEasel ) )
  {
    const NDb::ViewCamera& camera =  localEasel->GetData()->commonParams->camera;
    associatedMinigames->GetCameraController()->ChangeCamera(camera);
    associatedMinigames->GetCameraController()->ApplyResolutionModifcators();
  }

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenResults::OnBeforeClose()
{
  NI_VERIFY( IsValid( associatedMinigames), "EaselScreenResults: associated minigames is already dead", return true );

  associatedMinigames->GetCameraController()->ChangeCamera(lastCamera);

	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenResults::OnNewFront(IScreenBase * pNewFrontScreen)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenResults::ProcessEaselEvent( const Input::Event & message )
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenResults::ProcessUIEvent( const Input::Event & message )
{
  if(MinigameScreen::ProcessUIEvent( message ))
    return true;

	// process inputs for easel minigame
	if( ProcessEaselEvent( message ) )
		return true;

	return false;
}

#pragma endregion IScreenBase interface implementation

}
