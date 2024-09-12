#include "stdafx.h"
#include "AdventureScreen.h"
#include "FinalScreen.h"

#include "../Core/CoreFSM.h"
#include "../Core/MessagesInGame.h"
#include "../Core/MessagesLogin.h"
#include "../Client/ScreenCommands.h"

namespace NGameX
{

FinalScreen::~FinalScreen()
{
}


bool FinalScreen::Init( UI::User * uiUser )
{
  pLogic = new UI::FinalScreenLogic;
  SetLogic( pLogic );
  pLogic->SetUser( uiUser );
  pLogic->SetOwner(this);
  pLogic->LoadScreenLayout("FinalScreen");

  SubscribeUpdates();

  if ( loserFaction != -1 )
    ShowFinalMessage( NCore::GameShowWonMessage( loserFaction ) );

  // brute force set FSM to idle state
  //NCore::GetGlobalGameFSM()->PushMessageToCore( NCore::SetIdleState::NewSetIdleState() ); //@todo ?
  return true;
}

void FinalScreen::SubscribeUpdates()
{
  DefaultScreenBase::SubscribeUpdates();

  Subscribe( &FinalScreen::ShowFinalMessage );
}

void FinalScreen::ShowFinalMessage( const NCore::GameShowWonMessage& message )
{
  if (AdventureScreen const *pScreen = AdventureScreen::Instance())
  {    
    if (NWorld::PFBaseHero const *pHero = pScreen->GetHero())
    {
      if (pHero->GetFaction() == message.loserFaction )
      {
        pLogic->SetWinLoseText(L"[@todo Oleg]Вы проиграли!");
      }
      else
      {
        pLogic->SetWinLoseText(L"[@todo Oleg]Вы победили!");
      }
    }
  }
}

void FinalScreen::CloseScreen()
{
  NCore::GetGlobalGameFSM()->PushMessageToCore( NCore::GameFinishedMessage::NewGameFinishedMessage() );
  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( this ) );
}

} // End of namespace NGameX

namespace
{
  // You should NOT use this class anywhere in your code
  struct __FinalScreenMsgHandler
  {
    static NGameX::FinalScreen *screen;

    static void CreateFinalScreen( const NCore::GameStateWonState& message )
    {
      screen =  new NGameX::FinalScreen();
      NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand(screen) );
    }

    static void CreateFinalScreenWithResults( const NCore::GameShowWonMessage& message )
    {
      screen =  new NGameX::FinalScreen( message.loserFaction );
      NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand(screen) );
    }

    static void ExitFinalState( const NCore::InIdleState & message)
    {
      NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand(screen) );
    }

    __FinalScreenMsgHandler()
    {
      static Updater::Functor<NCore::GameShowWonMessage> functor3( &CreateFinalScreenWithResults );
      NCore::GetGlobalGameFSM()->RegisterFromCore( NCore::GameShowWonMessage::typeId, &functor3 );

      static Updater::Functor<NCore::GameStateWonState> functor( &CreateFinalScreen );
      NCore::GetGlobalGameFSM()->RegisterFromCore( NCore::GameStateWonState::typeId, &functor );

      static Updater::Functor<NCore::InIdleState> functor2( &ExitFinalState );
      NCore::GetGlobalGameFSM()->RegisterFromCore( NCore::InIdleState::typeId, &functor2 );

    }
  } __handler;
  NGameX::FinalScreen *__FinalScreenMsgHandler::screen = NULL;
}
