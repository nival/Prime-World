#include "stdafx.h"

#include "Core/CoreFSM.h"
#include "Client/ScreenCommands.h"

#include "UI/DBUI.h"
#include "MinigameLobbyScreen.h"

namespace PF_Minigames
{


MinigameLobbyScreen::MinigameLobbyScreen() :
state( ELobbyScreenState::Starting )
{
}



MinigameLobbyScreen::~MinigameLobbyScreen()
{
}



bool MinigameLobbyScreen::Init( UI::User * uiUser )
{
  lobbyLogic->SetUser( uiUser );
  lobbyLogic->SetScreen( this );

	lobbyLogic->InitScene( minigames );

  state = ELobbyScreenState::Normal;
  return true;
}



bool MinigameLobbyScreen::ProcessUIEvent( const Input::Event & event )
{
  //HACK: block all binds for adventure screen
  //if ( event.Type() == Input::EEventType::Activation )
  //  return true;

  return MinigameScreen::ProcessUIEvent( event );
}



void MinigameLobbyScreen::OnBecameFront()
{
  NI_VERIFY( lobbyLogic, "", return );

  lobbyLogic->OnBecameFront();
}


} // namespace PF_Minigames

NI_DEFINE_REFCOUNT(PF_Minigames::MinigameLobbyScreen)
