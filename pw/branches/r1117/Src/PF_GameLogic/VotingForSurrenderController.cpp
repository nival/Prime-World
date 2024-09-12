#include "stdafx.h"
#include "VotingForSurrenderController.h"
#include "AdventureScreen.h"

namespace NGameX
{

static const char szStartVotingFlashCommand[] = "VoteForSurrender";
static const char szMakeDecisionFlashCommand[] = "SurrenderVote"; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VotingForSurrenderController::VotingForSurrenderController(  const CPtr<VotingForSurrenderLogic> &pVFS, NDb::Ptr<NDb::VotingForSurrender> pDb, UI::FlashContainer2 * flashWnd, const char* className ) :
  FlashInterface( flashWnd, className ),
  pVFS(pVFS), pDb(pDb)
{
  flashWnd->AddFSListner( szStartVotingFlashCommand, this );
  flashWnd->AddFSListner( szMakeDecisionFlashCommand, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  if( strcmp(listenerID, szStartVotingFlashCommand) == 0 )
  {
    StartVoting();
  }
  else if( strcmp(listenerID, szMakeDecisionFlashCommand) == 0 )
  {
    int value;
    sscanf_s( args, "%d", &value );  
    MakeDecision(value);
  }
  else
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Unknown flash command: %s", listenerID) );
    return;     
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderController::Update( float timeDelta )
{ 
  if( !IsValid(pVFS) )
    return;

  const VotingForSurrenderLogic::State &newState = pVFS->GetCurrState();
  
  if( curUIState == newState )
    return; 
    
  if( curUIState.IsVotingInProgress() != newState.IsVotingInProgress() )
  {
    if( newState.IsVotingInProgress() )
    {
      if( NGameX::AdventureScreen *pAdv = NGameX::AdventureScreen::Instance() )
      {  
        const bool curPlayerAlreadyVoted =
          newState.result.find(pAdv->GetPlayer()->GetPlayerID()) != newState.result.end();      
        
        CallMethod( "ShowVoteWindow", pDb->votingDuration, curPlayerAlreadyVoted );  
      }
    }
    else
      CallMethod( "HideVoteWindow" );
  }
      
  if( newState.IsVotingInProgress() && curUIState.result != newState.result )
  {
    VotingForSurrenderLogic::Statistics stat;
    
    pVFS->CalcStatistics( newState, stat );     
    CallMethod( "SetSurrenderVoteStatus", stat.votesForSurrender, stat.votesForFight, stat.playersCount );
  }

  curUIState = newState;     
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderController::StartVoting()
{
  if( NGameX::AdventureScreen *pAdv = NGameX::AdventureScreen::Instance() )
    pAdv->SendGameCommand( NWorld::AIWorldFacets::VotingForSurrenderStartCommandCreate(pAdv->GetPlayer()), true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderController::MakeDecision( bool vote )
{
  if( NGameX::AdventureScreen *pAdv = NGameX::AdventureScreen::Instance() )
    pAdv->SendGameCommand( NWorld::AIWorldFacets::VotingForSurrenderMakeDecisionCommandCreate(pAdv->GetPlayer(), vote), true );
}

}