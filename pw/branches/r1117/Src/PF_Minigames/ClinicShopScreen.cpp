#include "stdafx.h"

#include "Core/CoreFSM.h"
#include "Client/ScreenCommands.h"

#include "Clinic.h"
#include "ClinicShopScreen.h"
#include "Minigames.h"
#include "MinigameCameraController.h"
#include "MinigamesMain.h"

namespace PF_Minigames
{
REGISTER_SCREEN(ClinicShopScreen);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicShopScreen::ClinicShopScreen()
{
  eventsUI.AddActivationHandler( "minigame_escape", &ClinicShopScreen::MsgOnEscapeKey );

  eventsScene.AddSystemHandler( "win_mouse_move", &ClinicShopScreen::MsgOnMousemove );
  eventsScene.AddSystemHandler( "win_left_button_down", &ClinicShopScreen::MsgOnLMouseDown );
  eventsScene.AddSystemHandler( "win_mouse_wheel_down", &ClinicShopScreen::MsgOnMouseWheel );
  eventsScene.AddSystemHandler( "win_mouse_wheel_up", &ClinicShopScreen::MsgOnMouseWheel );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicShopScreen::~ClinicShopScreen()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicShopScreen::Set(Minigames * _minigames)
{
	minigames = _minigames;
  clinic = _minigames->GetNativeMinigame<PF_Minigames::Clinic>( "Clinic" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::Init( UI::User * uiUser )
{
  logic = new UI::ClinicShopScreenLogic;
	NI_VERIFY(IsValid(logic), "", return false);
  SetLogic(logic);
  logic->SetUser( uiUser );
  logic->LoadScreenLayout("ClinicShop");
	logic->InitScene(minigames);
  logic->InitLayout();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::ProcessUIEvent(const Input::Event & event)
{
  if(MinigameScreen::ProcessUIEvent( event ))
    return true;

  //TODO: move this to ProcessSceneEvent when it's time
	if ( IsValid( minigames->GetCameraController() ) )
	{
		if ( minigames->GetCameraController()->ProcessEvent( event ) )
			return true;
	}

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::ProcessSceneEvent (const Input::Event & event )
{
  return MinigameScreen::ProcessSceneEvent( event );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::MsgOnMousemove( const Input::SSysParams & sysParams )
{
  NI_VERIFY(IsValid(logic), "", return false);
  return logic->OnMouseMove( CVec2( sysParams.GetMouseX(), sysParams.GetMouseY() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::MsgOnLMouseDown( const Input::SSysParams & sysParams )
{
	NI_VERIFY(IsValid(logic), "", return false);
	return logic->OnLeftClick( CVec2( sysParams.GetMouseX(), sysParams.GetMouseY() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::MsgOnMouseWheel( const Input::SSysParams & sysParams )
{
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicShopScreen::MsgOnEscapeKey()
{
  NI_VERIFY(IsValid(logic), "", return false);
  logic->OnEscapeKey();
  return true;
}


} // namespace PF_Minigames

NI_DEFINE_REFCOUNT(PF_Minigames::ClinicShopScreen)

