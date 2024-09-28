#include "stdafx.h"
#include "EaselScreensManager.h"

#include "../Client/ScreenCommands.h"

#include "EaselScreenLogic.h"
#include "EaselScreen.h"
#include "EaselScreenLobby.h"

#include "EaselScreenResults.h"
#include "EaselFailScreen.h"

#include "Easel.h"
#include "EaselMinigame.h"

#include "../UI/Root.h"

namespace PF_Minigames
{


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenManager::EaselScreenManager() :
initailized( false )
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenManager::~EaselScreenManager()
{
  initailized = false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLogic * EaselScreenManager::GetMainScreenLogic()
{
  return IsValid( easelScreen ) ? easelScreen->GetLogic() : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLogicLobby * EaselScreenManager::GetLobbyScreenLogic()
{
  return IsValid( lobbyScreen ) ? lobbyScreen->GetLogic() : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLogicResults * EaselScreenManager::GetResultsScreenLogic()
{
  return IsValid( resultsScreen ) ? resultsScreen->GetLogic() : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselFailScreenLogic * EaselScreenManager::GetFailureScreenLogic()
{
  return IsValid( failureScreen ) ? failureScreen->GetLogic() : 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenManager::Init( EaselMinigame * _minigame )
{
  if ( initailized )
    return true;

  minigame = _minigame;

  initailized = true;
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::Uninit()
{
  if( initailized )
    return;

  initailized = false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PushEaselScreen()
{
  if( !initailized )
    return;

  //Weak<EaselScreen> easelScreen = new EaselScreen();
  easelScreen = new EaselScreen;
  easelScreen->AssociateWithMinigames( *(minigame->GetMinigames() ) ); // setting minigames association

  // add screen to screens stack
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( easelScreen ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PopEaselScreen()
{
  if( IsValid( easelScreen ) )
    PopScreen( easelScreen );
  easelScreen = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PopLobbyScreen()
{
  if( IsValid( lobbyScreen ) )
    PopScreen( lobbyScreen );
  lobbyScreen = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PopFailureScreen()
{
  if ( IsValid( failureScreen ) )
    PopScreen( failureScreen );
  failureScreen = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PopResultsScreen()
{
  if ( IsValid( resultsScreen ) )
    PopScreen( resultsScreen );
  resultsScreen = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLobby * EaselScreenManager::CreateLobbyScreen()
{
  NI_ASSERT( !IsValid( lobbyScreen ), "" );
  NI_ASSERT( IsValid( minigame ), "" );

  lobbyScreen = new EaselScreenLobby;
  lobbyScreen->AssociateWithMinigames( *minigame->GetMinigames() );

  PushScreen( lobbyScreen );

  return lobbyScreen;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::CreateResultsScreen()
{
  NI_ASSERT( !IsValid( resultsScreen ), "" );
  NI_ASSERT( IsValid( minigame ), "" );

  resultsScreen = new EaselScreenResults;
  resultsScreen->AssociateWithMinigames( *minigame->GetMinigames() );

  PushScreen( resultsScreen );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::CreateFailureScreen()
{
  NI_ASSERT( !IsValid( failureScreen ), "" );
  NI_ASSERT( IsValid( minigame ), "" );

  failureScreen = new EaselFailScreen;
  failureScreen->AssociateWithMinigames( *minigame->GetMinigames() );

  PushScreen( failureScreen );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PushScreen(NMainLoop::IScreenBase *_pScreen)
{
  NScreenCommands::PushCommand(NScreenCommands::CreatePushScreenCommand(_pScreen));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenManager::PopScreen(NMainLoop::IScreenBase *_pScreen)
{
  NScreenCommands::PushCommand(NScreenCommands::CreatePopScreenCommand(_pScreen));
}

} //namespace PF_Minigames
