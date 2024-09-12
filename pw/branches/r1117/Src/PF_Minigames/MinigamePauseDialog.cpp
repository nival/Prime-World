#include "stdafx.h"
#include "MinigamePauseDialog.h"
#include "../Client/MessageScreen.h"
#include "MinigameBase.h"

#include "../Client/ScreenCommands.h"


namespace PF_Minigames
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePauseDialog::PopUp()
{
  Strong<NMainLoop::MessageScreen> screen = new NMainLoop::MessageScreen();
  screen->Configure(this, "MinigamePauseScreen");

  NScreenCommands::PushCommand(NScreenCommands::CreatePushScreenCommand(screen));
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePauseDialog::OnYesButton()
{
  if(IsValid(game))
    game->InitiatePause(false);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamePauseDialog::OnNoButton()
{
  if(IsValid(logic))
  {
    game->InitiatePause(false);
    logic->ExitGame();
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MinigamePauseDialog::OnEscapeKey()
{
  //Same behaivior as Yes button
  MinigamePauseDialog::OnYesButton();
  return true;
}


}; //namespace PF_Minigames

using namespace PF_Minigames;
NI_DEFINE_REFCOUNT( MinigamePauseDialog );
