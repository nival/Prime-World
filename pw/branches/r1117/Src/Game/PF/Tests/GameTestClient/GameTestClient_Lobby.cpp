#include "stdafx.h"
#include "GameTestClient_Lobby.h"
#include "HybridServer/Peered.h"
#include "HybridServer/RPeered.auto.h"

namespace gtc
{

Client_Lobby::Client_Lobby( const TestClientBaseParams & _params ) :
Client_GS( _params )
{
}



Client_Lobby::~Client_Lobby()
{
  if ( lobbyClient )
    lobbyClient->CleanUpRpcCyclicLinks();
  lobbyClient = 0;
}



StepResult Client_Lobby::MainStep()
{
  NI_PROFILE_FUNCTION;

  StepResult result = Client_GS::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  stepLobbyClient();

  switch ( stage_ )
  {
    default:
      return StepResult( false, true );

    case Stage::LOGIN_FINISHED:
      return StepResult( true, startLobbyClient() != Result::FAIL );

    case Stage::LOBBY_ENTERING:
      return StepResult( true, Result::FAIL != waitLobbyClient() );
  } //case ends
}



int Client_Lobby::startLobbyClient()
{
  NI_PROFILE_FUNCTION;
  lobbyClient = new lobby::ClientBase( transport_->GetUserId(), true );


  lobbyClient->Start( gateKeeper_, transport_->GetSessionPath() );

  stage_ = Stage::LOBBY_ENTERING;
  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int Client_Lobby::waitLobbyClient()
{
  NI_PROFILE_FUNCTION;

  if ( lobbyClient->Status() == lobby::EClientStatus::InGameSession )
  {
    StartGame( lobbyClient->GameServer() );
  }
  else if ( lobbyClient->Status() == lobby::EClientStatus::Error )
    lastresult_ = Result::FAIL;
  else
    lastresult_ = Result::IN_PROGRESS;
  
  return lastresult_;
}



void Client_Lobby::stepLobbyClient()
{
  NI_PROFILE_FUNCTION;

  if ( lobbyClient )
    lobbyClient->Poll();
}

} //namespace gtc

NI_DEFINE_REFCOUNT( gtc::Client_Lobby );
