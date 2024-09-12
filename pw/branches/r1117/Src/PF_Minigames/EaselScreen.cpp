#include "stdafx.h"
#include "EaselScreen.h"

#include "../Core/CoreFSM.h"
#include "../Client/ScreenCommands.h"

#include "Minigames.h"

#include "MinigameCameraController.h"

//#include "Easel.h"

#include "EaselMinigame.h"
#include "EaselScreenLogic.h"

#include "EaselDef.h"

NI_DEFINE_REFCOUNT(PF_Minigames::EaselScreen)

namespace PF_Minigames
{

REGISTER_SCREEN(EaselScreen)  // PF_Minigames

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreen::EaselScreen()
: MinigameScreen()
, fIsLMBAllowed(true)
, fIsRMBAllowed(true)
{
  eventsScene.AddSystemHandler( "win_mouse_move", &EaselScreen::MsgOnMouseMove );
  eventsScene.AddSystemHandler( "win_left_button_down", &EaselScreen::MsgOnLMouseDown );
  eventsScene.AddSystemHandler( "win_right_button_down", &EaselScreen::MsgOnRMouseDown );
  eventsScene.AddSystemHandler( "win_left_button_dblclk", &EaselScreen::MsgOnLDoubleclick );

  eventsUI.AddActivationHandler( "easel_skip_movie", &EaselScreen::MsgOnSkipMovie );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreen::~EaselScreen()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::AssociateWithMinigames(Minigames& minigames)
{
	NI_VERIFY( !IsValid( associatedMinigames ) , "Easel screen can be associated only once", return );
	associatedMinigames = &minigames;

  easelMinigame = associatedMinigames->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY( IsValid( easelMinigame ),"Missing EaselMinigame object", return );

	localEasel = easelMinigame->GetLocalEasel();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreen::Init( UI::User * uiUser )
{
  if( !IsValid( associatedMinigames ) )
    return false;

  if( IsValid( localEasel ) )
  {
    const NDb::ViewCamera& camera =  localEasel->GetData()->commonParams->camera;
    associatedMinigames->GetCameraController()->ChangeCamera(camera);
    associatedMinigames->GetCameraController()->ApplyResolutionModifcators();
  }

  // change camera
  lastCamera = associatedMinigames->GetCameraController()->GetCameraParams();

  if( !IsValid(logic))
  {
    logic = new EaselScreenLogic;
    NI_VERIFY( IsValid(logic), "Easel screen creation failed", return false);
  }

  SetLogic( logic );
  logic->SetUser( uiUser );

  logic->LoadScreenLayout("EaselScreen");
  logic->Init( associatedMinigames, this );
  logic->InitBoosts();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreen::OnBeforeClose()
{
  NI_VERIFY( IsValid( associatedMinigames), "EaselScreen: associated minigames is already dead", return true );

  associatedMinigames->GetCameraController()->ChangeCamera(lastCamera);

	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::Step( bool bAppActive )
{
  if ( IsValid(logic)  )
    logic->ProcessStep();

  MinigameScreen::Step(bAppActive);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::OnMouseMove( const UI::Point & point )
{
  if ( IsValid( localEasel ) )
    localEasel->ProcessMouseMove( CVec2( point.x, point.y ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::OnLMouseDown()
{
  // smart pointers to easel minigame and input handler should be valid
  if( !fIsLMBAllowed )
    return;

  if ( IsValid( localEasel ) )
    localEasel->ProcessMouseEvent( EEaselMouseEvents::LeftButton );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::OnRMouseDown()
{
  if( !fIsRMBAllowed )
    return;

  if ( IsValid( localEasel ) )
    localEasel->ProcessMouseEvent( EEaselMouseEvents::RightButton );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreen::OnSkipMovie()
{
  if ( IsValid( easelMinigame ) )
    easelMinigame->OnKeyboardEventLocal( EEaselKeyboardEvents::SkipMovie );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreen::MsgOnMouseMove( const Input::SSysParams & params )
{
  OnMouseMove( UI::Point( params.GetMouseX(), params.GetMouseY() ) );
  return false;
}

} //namespace PF_Minigames
