#include "stdafx.h"
#include "EaselFailScreen.h"

#include "../Core/CoreFSM.h"
#include "../Client/ScreenCommands.h"

#include "Minigames.h"

#include "MinigameCameraController.h"

#include "Easel.h"
#include "EaselMinigame.h"
#include "EaselFailScreenLogic.h"


NI_DEFINE_REFCOUNT(PF_Minigames::EaselFailScreen)

namespace PF_Minigames
{
  
REGISTER_SCREEN(EaselFailScreen)  // PF_Minigames
//////////////////////////////////////////////////////////////////////////
//
// class EaselFailScreen implementation
//
//////////////////////////////////////////////////////////////////////////
EaselFailScreen::EaselFailScreen() 
: MinigameScreen()
{

}

EaselFailScreen::~EaselFailScreen()
{

}

void EaselFailScreen::AssociateWithMinigames(Minigames& minigames)
{
  NI_VERIFY( !IsValid( associatedMinigames ) , "EaselFailScreen: Easel screen can be associated only once", return );
  associatedMinigames = &minigames;

  CPtr<EaselMinigame> _client = associatedMinigames->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY(IsValid(_client),"Missing EaselMinigame object", return);

  localEasel = _client->GetLocalEasel();
}

bool EaselFailScreen::Init(UI::User * uiUser)
{
  if( !IsValid(associatedMinigames) )
  {
    return false;
  }

  // create and init ui logic
  logic = new EaselFailScreenLogic;
  logic->SetUser(uiUser);

  NI_VERIFY(IsValid(logic), "EaselFailScreen: Easel fail lobby screen creation failed", return false);

  SetLogic(logic);

  logic->Init( associatedMinigames );	
  logic->LoadScreenLayout("Minigame02Fail"); //????
  logic->InitLayout();

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

bool EaselFailScreen::OnBeforeClose()
{
  NI_VERIFY( IsValid( associatedMinigames), "EaselFailScreen: associated minigames is already dead", return true );

  associatedMinigames->GetCameraController()->ChangeCamera(lastCamera);

  return true;
}

void EaselFailScreen::OnBecameFront()
{
  
}

void EaselFailScreen::OnNewFront(IScreenBase * pNewFrontScreen)
{

}

bool EaselFailScreen::ProcessUIEvent( const Input::Event & message )
{
  if( MinigameScreen::ProcessUIEvent( message ) )
    return true;

  return false;
}

}