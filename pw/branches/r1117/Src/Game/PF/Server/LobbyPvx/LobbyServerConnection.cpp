#include "stdafx.h"
#include "LobbyServerConnection.h"
#include "LobbyGameSession.h"
#include "LobbyCustomGame.h"
#include "LobbyServerNode.h"
#include "LobbyConfig.h"
#include "Client/LobbyPvx/RLobbyClientInterface.auto.h"
#include "LobbyLog.h"


namespace lobby
{

ServerConnection::ServerConnection( IConfigProvider * _cfg, ServerNode * _server, Transport::TClientId _clientId ) :
config( _cfg ),
status( EConnectionStatus::New ),
server( _server ),
clientId( _clientId ),
clientRevision( 0 )
{
}



void ServerConnection::JustConnected( StrongMT<rpc::Node> const & _node )
{
  NI_ASSERT( status == EConnectionStatus::New, "" );
  status = EConnectionStatus::New;
  NI_VERIFY( !user, "", user = 0 );
}



void ServerConnection::Established( RILobbyUser * _user, int _clientRevision )
{
  NI_ASSERT( status == EConnectionStatus::New, "" );
  NI_ASSERT( !user, "" );
  user = _user;
  clientRevision = _clientRevision;
  status = EConnectionStatus::Established;
}



void ServerConnection::Disconnected( NHPTimer::FTime now )
{
  user = 0;
  clientRevision = 0;
}



void ServerConnection::SetCustomGame( CustomGame * _game )
{
  game = _game;
}



StrongMT<CustomGame> ServerConnection::GetCustomGame()
{
  return game.Lock();
}



void ServerConnection::SetDeveloperSex( int /*ESex::Enum*/ _sex )
{
  if ( !config->Cfg()->enableDevMode )
    return;

  NI_VERIFY( ( _sex == lobby::ESex::Male ) || ( _sex == lobby::ESex::Female ), "", return )
  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return;
  }
  NI_VERIFY( user, "", return );

  userInfo.zzimaSex = (ESex::Enum)_sex;
}



void ServerConnection::RequestGamesList()
{
  if ( !config->Cfg()->enableDevMode )
    return;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return;
  }

  NI_VERIFY( user, "", return );

  StrongMT<ServerNode> locked  = server.Lock();
  NI_VERIFY( locked, "", return );

  int cnt = 32;

  for ( ServerNode::TCustomGames::const_iterator it = locked->CustomGames().begin(); ( it != locked->CustomGames().end() ) && ( cnt > 0 ); ++it, --cnt )
  {
    const SGameParameters & params = it->second->Params();

    SDevGameInfo info;
    info.gameId = it->first;
    info.name = params.name.c_str();
    info.mapId = params.mapId;
    info.playersCount = it->second->Players().size();
    info.maxPlayers = params.slotsCount;

    user->AddGameInfo( info );
  }

  for ( ServerNode::TGames::const_iterator it = locked->Games().begin(); ( it != locked->Games().end() ) && ( cnt > 0 ); ++it, --cnt )
  {
    const SGameParameters & params = it->second->Params();

    SDevGameInfo info;
    info.gameId = it->first;
    info.name = params.name.c_str();
    info.mapId = params.mapId;
    info.playersCount = params.slotsCount;
    info.maxPlayers = params.slotsCount;

    user->AddGameInfo( info );
  }
}



EOperationResult::Enum ServerConnection::JoinGame( int gameId )
{
  if ( !config->Cfg()->enableDevMode )
    return EOperationResult::RestrictedAccess;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return EOperationResult::RestrictedAccess;
  }

  StrongMT<ServerNode> locked  = server.Lock();
  NI_VERIFY( locked, "", return EOperationResult::InternalError );

  StrongMT<CustomGame> game;

  if ( gameId )
  {
    ServerNode::TCustomGames::const_iterator it = locked->CustomGames().find( gameId );
    NI_VERIFY( it != locked->CustomGames().end(), "Unknown game", return EOperationResult::GameNotFound );
    game = it->second;
  }
  else
  {
    //Let's find first custom lobby game with free slot
    for ( ServerNode::TCustomGames::const_iterator it = locked->CustomGames().begin(); it != locked->CustomGames().end(); ++it )
    {
      StrongMT<CustomGame> g = it->second;
      if ( g->State() == ECustomGameState::Lobby )
        if ( g->Players().size() < g->Params().slotsCount )
        {
          game = g;
          break;
        }
    }
    if ( !game )
      return EOperationResult::GameNotFound;
  }

  return game->AddPlayerToCustomLobby( this );
}




EOperationResult::Enum ServerConnection::ReconnectToCustomGame( int gameId, /*ETeam::Enum*/ int team, const string & heroId )
{
  if ( !config->Cfg()->enableDevMode )
    return EOperationResult::RestrictedAccess;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return EOperationResult::RestrictedAccess;
  }

  StrongMT<ServerNode> locked  = server.Lock();
  NI_VERIFY( locked, "", return EOperationResult::InternalError );

  ServerNode::TGames::const_iterator it = locked->Games().find( gameId );
  if( it == locked->Games().end() ) {
    LOBBY_LOG_ERR( "Unknown game" );
    return EOperationResult::GameNotFound;
  }
  StrongMT<GameSession> game = it->second;

  return game->ReconnectToCustomGame( this );
}



EOperationResult::Enum ServerConnection::CreateCustomGame( int maxPlayers, int maxPlayersPerTeam, const string & mapId, int autostartPlayers )
{
  if ( !config->Cfg()->enableDevMode )
    return EOperationResult::RestrictedAccess;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return EOperationResult::RestrictedAccess;
  }

  StrongMT<ServerNode> locked  = server.Lock();
  NI_VERIFY( locked, "", return EOperationResult::InternalError );

  SGameParameters params;
  params.gameType = EGameType::Custom;
  params.name = L"";
  params.mapId = mapId;
  params.slotsCount = Min( maxPlayers, maxPlayersPerTeam * 2 );
  params.maxPlayersPerTeam = maxPlayersPerTeam;
  params.randomSeed = locked->GetGameRandom();
  params.manoeuvresFaction = lobby::ETeam::None;

  StrongMT<CustomGame> game = locked->CreateCustomGame( params, autostartPlayers );
  NI_VERIFY( game, "Custom game was NOT created", return EOperationResult::InternalError );

  EOperationResult::Enum result = game->SetupCustom( this );

  if ( result == EOperationResult::Ok )
    locked->InsertCustomGame( game );

  return result;
}



EOperationResult::Enum ServerConnection::SpectateCustomGame( int gameId )
{
  if ( !config->Cfg()->enableDevMode )
    return EOperationResult::RestrictedAccess;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return EOperationResult::RestrictedAccess;
  }

  StrongMT<ServerNode> locked  = server.Lock();
  NI_VERIFY( locked, "", return EOperationResult::InternalError );

  ServerNode::TGames::const_iterator it = locked->Games().find( gameId );
  if( it == locked->Games().end() ) {
    LOBBY_LOG_ERR( "Unknown game" );
    return EOperationResult::GameNotFound;
  }
  StrongMT<GameSession> game = it->second;

  return game->SpectateCustomGame( this );
}



void ServerConnection::ChangeCustomGameSettings( /*ETeam::Enum*/ int team, /*ETeam::Enum*/ int faction, const string & heroId )
{
  if ( !config->Cfg()->enableDevMode )
    return;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return;
  }

  if ( StrongMT<CustomGame> lgame = game.Lock() )
    lgame->ChangeCustomGameSettings( this, (ETeam::Enum)team, (ETeam::Enum)faction, heroId );
}



void ServerConnection::SetDeveloperParty(int party)
{
  if ( !config->Cfg()->enableDevMode )
    return;

  if ( status != EConnectionStatus::Established )
  {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return;
  }

  if ( StrongMT<CustomGame> lgame = game.Lock() )
    lgame->SetDeveloperParty( this, party );
}



void ServerConnection::SetReady( /*EGameMemberReadiness::Enum*/ int readiness )
{
  if ( !config->Cfg()->enableDevMode )
    return;

  if ( status != EConnectionStatus::Established ) {
    LOBBY_LOG_ERR( "Wrong connection state" );
    return;
  }


  if ( StrongMT<CustomGame> lgame = game.Lock() )
    lgame->SetPlayerReady( this, (EGameMemberReadiness::Enum)readiness );
}



EOperationResult::Enum ServerConnection::JoinSocialGame()
{
  StrongMT<ServerNode> locked = server.Lock();
  if ( locked )
    return locked->JoinSocialGame( this );
  //TODO: Remove this 'ServerConnection', disconnect from lobby
  return EOperationResult::InternalError;
}

} //namespace lobby
