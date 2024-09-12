#include "stdafx.h"

#include "Core/CoreFSM.h"
#include "Client/ScreenCommands.h"

#include "Clinic.h"
#include "ClinicScreen.h"
#include "Minigames.h"
#include "MinigameCameraController.h"
#include "MinigamesMain.h"

namespace PF_Minigames
{
REGISTER_SCREEN(ClinicScreen);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicScreen::ClinicScreen() : levelID(0)
{
  eventsScene.AddSystemHandler( "win_mouse_move", &ClinicScreen::MsgOnMouseMove );
  eventsScene.AddSystemHandler( "win_left_button_down", &ClinicScreen::MsgOnLMouseDown );
  eventsScene.AddSystemHandler( "win_right_button_down", &ClinicScreen::MsgOnRMouseDown );

  eventsUI.AddActivationHandler( "minigame_escape", &ClinicScreen::MsgOnEscapeKey );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicScreen::~ClinicScreen()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreen::Set(Minigames * _minigames, int _levelID)
{
	minigames = _minigames;
	levelID = _levelID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::Init( UI::User * uiUser )
{
  logic = new UI::ClinicScreenLogic;
	NI_VERIFY(IsValid(logic), "", return false);
  SetLogic(logic);
  logic->SetUser( uiUser );
  logic->LoadScreenLayout("MinigameClinicScreen");
	logic->InitScene(minigames, levelID);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::ProcessUIEvent( const Input::Event & message )
{
	NI_VERIFY(logic, "", return false);

  if ( logic->ProcessMessage( message ) )
    return true;

  if ( eventsUI.ProcessEvent( message, this ) )
		return true;

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::ProcessSceneEvent( const Input::Event & message )
{
	NI_VERIFY(logic, "", return false);

	if (IsValid( minigames->GetCameraController()))
		if ( minigames->GetCameraController()->ProcessEvent( message ) )
			return true;

  return MinigameScreen::ProcessSceneEvent( message );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::GetCursor( string * id, const UI::Point & screenCoords ) const
{
  return MinigameScreen::GetCursor( id, screenCoords );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreen::Step( bool bAppActive )
{
  MinigameScreen::Step( bAppActive );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::MsgOnMouseMove( const Input::SSysParams & sysParams )
{
	NI_VERIFY(logic,"", return false);

  logic->SetCursorPos( CVec2( sysParams.GetMouseX(), sysParams.GetMouseY() ) );
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::MsgOnLMouseDown( const Input::SSysParams & )
{
	NI_VERIFY(logic,"", return false);

	logic->OnLeftClick();
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::MsgOnRMouseDown( const Input::SSysParams & )
{
  NI_VERIFY(logic,"", return false);

  logic->OnRightClick();
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreen::MsgOnEscapeKey()
{
  NI_VERIFY(logic, "", return false);
  logic->OnEscapeKey();
  return true;
}


} // namespace PF_Minigames

NI_DEFINE_REFCOUNT(PF_Minigames::ClinicScreen)

