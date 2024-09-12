#include "stdafx.h"
#include "Server/Db/DBServer.auto.h"
#include "LobbyCustomGame.h"
#include "LobbyServerConnection.h"
#include "LobbyConfig.h"
#include "Client/LobbyPvx/RLobbyClientInterface.auto.h"
#include "Server/LiveMMaking/IMMakingLogic.h" //To get to 'IHeroesTable'
#include "LobbyLog.h"


namespace lobby
{

CustomGame::CustomGame( IConfigProvider * _cfg, TGameId _id, const SGameParameters & _params, mmaking::IHeroesTable * _heroes, int _autostartPlayers ) :
config( _cfg ),
id( _id ),
params( _params ),
state( ECustomGameState::Lobby ),
heroes( _heroes ),
autostartPlayers( _autostartPlayers ),
eliseevHackForPve( false )
{
  NDb::Ptr<NDb::AdvMapDescription> advMapDesc =  NDb::Get<NDb::AdvMapDescription>( NDb::DBID( params.mapId ) );
  if ( advMapDesc )
  {
    eliseevHackForPve = ( advMapDesc->mapType == NDb::MAPTYPE_COOPERATIVE ) || 
      ( advMapDesc->mapType == NDb::MAPTYPE_SERIES );
  }

  if ( eliseevHackForPve )
  {
    if ( params.slotsCount > params.maxPlayersPerTeam )
    {
      params.slotsCount = params.maxPlayersPerTeam;
      LOBBY_LOG_DBG( "Slots count in custom game %016x adjusted to %d", id, params.slotsCount );
    }
  }
}



CustomGame::~CustomGame()
{
}



void CustomGame::Poll( timer::Time now )
{
}



int CustomGame::FindPlayer( ServerConnection * player )
{
  for ( int i = 0; i < players.size(); ++i )
    if ( players[i].player == player )
      return i;
  return -1;
}



int CustomGame::AddPlayerInternal( ServerConnection * player, ETeam::Enum team, const char * heroId )
{
  player->SetCustomGame( this );

  //TODO: original_team
  players.push_back( CustomGameMember( player, SPlayerGameContext( EPlayerType::Human, team, team, heroId ) ) );

  return players.size() - 1;
}



void CustomGame::RemovePlayer( ServerConnection * _player )
{
  NI_PROFILE_FUNCTION;

  int index = FindPlayer( _player );
  NI_VERIFY( index >= 0, "Removing unknown player!", return );

  LOBBY_LOG_MSG( "Player %d leaves custom game %016x", _player->ClientId(), id );

  CustomGameMember member = players[index];
  players.erase( players.begin() + index );

  if ( players.empty() )
  {
    LOBBY_LOG_MSG( "Last user left from custom game %016x", id );
    ChangeState( ECustomGameState::Empty );
  }
  else
  {
    BroadcastPlayerLeaveCustom( _player->ClientId() );
    DropReadinessAndBroadcast();
  }

  _player->SetCustomGame( 0 );
  _player->ForgetRemoteUser();
}



EOperationResult::Enum CustomGame::SetupCustom( ServerConnection * firstPlayer )
{
  return AddPlayerToCustomLobby( firstPlayer );
}



EOperationResult::Enum CustomGame::AddPlayerToCustomLobby( ServerConnection * player )
{
  if ( state != ECustomGameState::Lobby )
    return EOperationResult::GameStarted;

  if ( players.size() >= params.slotsCount )
    return EOperationResult::NoFreeSlot;

  if ( player->GetCustomGame() )
    return EOperationResult::AlreadyInGame;

  if ( players.empty() )
    params.name = NStr::StrFmtW( L"%s's game", player->UserInfo().nickname.c_str() );

  for ( int i = 0; i < players.size(); ++i )
    if ( players[i].player->ClientRevision() != player->ClientRevision() )
      return EOperationResult::RevisionDiffers;

  //Find out gameplay params BEFORE adding player
  string heroId;
  ETeam::Enum teamId = ETeam::None;
  int teamSizes[2] = { 0, 0 };
  for ( int i = 0; i < players.size(); ++i )
    ++teamSizes[ ( players[i].context.team == ETeam::Team1 ) ? 0 : 1 ];
  FindOutNewPlayerInfo( heroId, teamId, teamSizes );

  int index = AddPlayerInternal( player, teamId, heroId.c_str() );

  if ( player->RemoteUser() )
    player->RemoteUser()->JoinCustomSession( params );

  //Lets tell everybody in custom game lobby about new player
  SGameMember memb( players[index].player->UserInfo(), players[index].context );
  for ( int i = 0; i < players.size(); ++i )
    if ( players[i].player->RemoteUser() )
      players[i].player->RemoteUser()->AddCustomGameMember( memb );    

  //Lets tell new player abount other team members
  if ( player->RemoteUser() )
    for ( int i = 0; i < players.size(); ++i )
      if ( players[i].player != player )
      {
        SGameMember memb( players[i].player->UserInfo(), players[i].context );
        player->RemoteUser()->AddCustomGameMember( memb );
      }

  if ( ( config->Cfg()->customAutoStartPlayers > 0 ) && ( players.size() >= config->Cfg()->customAutoStartPlayers ) )
  {
    LOBBY_LOG_MSG( "Custom game %016x AUTO-started with player %i", id, player->ClientId() );

    StartGame();
  }
  else if ( ( autostartPlayers > 0 ) && ( players.size() >= autostartPlayers ) ) {
    LOBBY_LOG_MSG( "Custom game %016x AUTO-started with player %i", id, player->ClientId() );

    StartGame();
  }

  return EOperationResult::Ok;
}



void CustomGame::ChangeCustomGameSettings( ServerConnection * player, ETeam::Enum team, ETeam::Enum faction,  const string & heroId )
{
  if ( state != ECustomGameState::Lobby )
    return;

  int index = FindPlayer( player );
  NI_VERIFY( index >= 0, "", return );

  const bool factionIsOk = ( faction == ETeam::Team1 ) || ( faction == ETeam::Team2 );
  bool factionChanged = factionIsOk && ( players[index].context.original_team != faction );

  const bool teamIsOk = ( team == ETeam::Team1 ) || ( team == ETeam::Team2 );
  bool teamChanged = teamIsOk && ( players[index].context.team != team );

  //Let's check hero id
  bool heroValid = !heroId.empty() && ( heroes->Find( heroId ) != 0 );
  bool heroChanged = false;

  if ( !heroValid && !heroId.empty() )
    LOBBY_LOG_MSG( "Illegal hero id '%s' request skipped", heroId.c_str() );

  if ( heroValid && ( players[index].context.hero != heroId.c_str() ) )
  {
    heroChanged = true;
    players[index].context.hero = heroId.c_str();
  }

  if ( teamChanged )
    players[index].context.team = team;

  if ( factionChanged )
    players[index].context.original_team = faction;

  if ( heroChanged || teamChanged || factionChanged )
    BroadcastPlayerSettings( index );

  //TODO: faction is not affect eliseevHackForPve

  if ( eliseevHackForPve && teamChanged )
  { // hack for cooperative game: move all players to same team
      for( int i = 0; i < players.size(); ++i )
      {
        if ( players[i].context.team == team )
          continue;
        players[i].context.team = team;
        BroadcastPlayerSettings( i );
      }
  }

  DropReadinessAndBroadcast();
}



void CustomGame::SetDeveloperParty(ServerConnection * player, int party)
{
  if ( state != ECustomGameState::Lobby )
    return;

  int index = FindPlayer( player );
  NI_VERIFY( index >= 0, "", return );

  const uint partyId = (party > 0) ? (party) : (0U);
  const bool partyChanged = (players[index].partyId != partyId);

  if (!partyChanged)
    return;

  players[index].partyId = partyId;

  LOBBY_LOG_MSG("+++ SET PARTY: #%d (%d) -> %u", index, players[index].player->ClientId(), partyId);

  DropReadinessAndBroadcast();
}



void CustomGame::SetPlayerReady( ServerConnection * player, EGameMemberReadiness::Enum readiness )
{
  if ( state != ECustomGameState::Lobby )
    return;

  int index = FindPlayer( player );
  NI_VERIFY( index >= 0, "", return );

  const EGameMemberReadiness::Enum old = players[index].customLobbyReadiness;

  const bool oldReady = ( old == EGameMemberReadiness::Ready ) || ( old == EGameMemberReadiness::ReadyForAnything );
  const bool newReady = ( readiness == EGameMemberReadiness::Ready ) || ( readiness == EGameMemberReadiness::ReadyForAnything );

  if ( oldReady && newReady )
    return;
  if ( !oldReady && !newReady )
    return;

  players[index].customLobbyReadiness = readiness;
  BroadcastCustomReadiness( player->ClientId(), newReady );

  //params.manoeuvresFaction = players[index].context.original_team;

  for( int i = 0; i < players.size(); ++i )
    if ( players[i].customLobbyReadiness == EGameMemberReadiness::NotReady )
      return;

  //Everything IS ready, let's start

  LOBBY_LOG_MSG( "Custom game %016x started with player %i", id, player->ClientId() );

  StartGame();
}



void CustomGame::FindOutNewPlayerInfo( string & heroId, ETeam::Enum & teamId, int teamSizes[2] ) 
{
  NI_STATIC_ASSERT( ETeam::Team1 == 0 && ETeam::Team2 == 1, Wrong_team_id );

  if ( eliseevHackForPve )
  {
    teamId = ( teamSizes[1] > teamSizes[0] ) ? ETeam::Team2 : ETeam::Team1;
  }
  else 
  {
    teamId = ( teamSizes[1] <= teamSizes[0] ) ? ETeam::Team2 : ETeam::Team1;
  }

  NI_DATA_VERIFY( heroes->MaxShortId() > 0, "", return );

  mmaking::THeroShortId hid = 1 + ( teamSizes[ teamId ] % heroes->MaxShortId() );
  heroId = heroes->Find( hid );

  ++teamSizes[ teamId ];
}



void CustomGame::ComplementWithLegacyAi( TGameLineUp & _lineup )
{
  int teamSizes[2] = { 0, 0 };
  for ( int i = 0; i < _lineup.size(); ++i )
    ++teamSizes[ ( _lineup[i].context.team == ETeam::Team1 ) ? 0 : 1 ];

  int aiPlayers = params.slotsCount - _lineup.size();

  for ( int i = 0; i < aiPlayers; ++i )
  {
    _lineup.push_back();
    SGameMember & memb = _lineup.back();
    memb.context.playerType = EPlayerType::Computer;
    FindOutNewPlayerInfo( memb.context.hero, memb.context.team, teamSizes );
  }
}



void CustomGame::BalanceCustomGame()
{
  int teamSizes[2] = { 0, 0 };
  for ( int i = 0; i < players.size(); ++i )
    ++teamSizes[ ( players[i].context.team == ETeam::Team1 ) ? 0 : 1 ];

  NI_ASSERT( teamSizes[0] + teamSizes[1] <= params.slotsCount, "Too many players in games" );

  int hardMoveToTeam1 = Max( teamSizes[1] - params.maxPlayersPerTeam, 0 );
  int hardMoveToTeam2 = Max( teamSizes[0] - params.maxPlayersPerTeam, 0 );

  if ( eliseevHackForPve )
  {
    int activeTeam = teamSizes[0] >= teamSizes[1] ? 0 : 1;
    hardMoveToTeam1 = ( activeTeam == 0 ) ? teamSizes[1] : 0;
    hardMoveToTeam2 = ( activeTeam == 1 ) ? teamSizes[0] : 0;
  }

  if ( hardMoveToTeam1 > 0 || hardMoveToTeam2 > 0 )
  {
    for ( int i = players.size() - 1; 0 <= i; --i )
    {
      ETeam::Enum team = players[i].context.team;

      if( ( team == ETeam::Team1 ) && ( hardMoveToTeam2 > 0 ) )
      {
        players[i].context.team = ETeam::Team2;
        --hardMoveToTeam2;
      }

      if( ( team == ETeam::Team2 ) && ( hardMoveToTeam1 > 0 ) )
      {
        players[i].context.team = ETeam::Team1;
        --hardMoveToTeam1;
      }
    }
  }
}



void CustomGame::StartGame()
{
  LOBBY_LOG_MSG( "Starting custom game %016x", id );

  BalanceCustomGame();

  ChangeState( ECustomGameState::Starting );

  //ServeGameServer( HostServer::Cfg::GetSvcPath().c_str() );
}



void CustomGame::BroadcastPlayerSettings( size_t playerIndex )
{
  NI_VERIFY( playerIndex < (size_t)players.size(), "", return );
  const SPlayerGameContext & prm = players[playerIndex].context;
  for ( int j = 0; j < players.size(); ++j )
  {
    NI_VERIFY( players[j].player->RemoteUser(), "", continue );
    players[j].player->RemoteUser()->UpdateCustomGameMember( players[playerIndex].player->ClientId(), prm );
  }
}



void CustomGame::BroadcastPlayerLeaveCustom( Transport::TClientId playerClientId )
{
  for ( int i = 0; i < players.size(); ++i )
  {
    NI_VERIFY( players[i].player->RemoteUser(), "", continue );
    players[i].player->RemoteUser()->RemoveCustomGameMember( playerClientId );
  }
}



void CustomGame::BroadcastCustomReadiness( Transport::TClientId playerClientId, bool isReady )
{
  for ( int i = 0; i < players.size(); ++i )
  {
    NI_VERIFY( players[i].player->RemoteUser(), "", continue );
    players[i].player->RemoteUser()->UpdateCustomGameMemberReadiness( playerClientId, isReady );
  }
}



void CustomGame::DropReadinessAndBroadcast()
{
  NI_ASSERT( state == ECustomGameState::Lobby, "" );

  for( int i = 0; i < players.size(); ++i )
  {
    if ( players[i].customLobbyReadiness == EGameMemberReadiness::ReadyForAnything )
      continue;
    if ( players[i].customLobbyReadiness == EGameMemberReadiness::NotReady )
      continue;

    players[i].customLobbyReadiness = EGameMemberReadiness::NotReady;
    BroadcastCustomReadiness( players[i].player->ClientId(), false );
  }
}



void CustomGame::SetupGameStartInfo( vector<Peered::ClientInfo> & _gameServerData, TGameLineUp & _lineup )
{
#pragma warning(push)
#pragma warning(disable:4201)
  union PartyKey
  {
    struct
    {
      uint party : 24;
      char team : 8;
    };

    uint key;
  };
#pragma warning(pop)

  NI_ASSERT( state == ECustomGameState::Starting, "" );

  _gameServerData.clear();
  _gameServerData.resize( players.size() );

  _lineup.clear();
  _lineup.resize( players.size() );

  typedef vector<uint> PartyList;

  PartyList parties;

  for( int i = 0; i < players.size(); ++i )
  {
    const CustomGameMember& member = players[i];

    _gameServerData[i].clientId = member.player->ClientId();

    _lineup[i].user = member.player->UserInfo();
    _lineup[i].context = member.context;

    const bool teamOK = (member.context.team == ETeam::Team1) || (member.context.team == ETeam::Team2);
    const bool partyOK = (member.partyId != 0U);

    if (!teamOK || !partyOK)
      continue;

    PartyKey pk;

    pk.party = member.partyId;
    pk.team = member.context.team;

    PartyList::const_iterator it = parties.find(pk.key);

    if (it == parties.end())
    {
      const uint partyId = static_cast<uint>(parties.size()) + 1U;

      _gameServerData[i].info.partyId = partyId;
      _gameServerData[i].info.partyLeader = true;

      parties.push_back(pk.key);

      LOBBY_LOG_MSG( "+++ PARTY: %08X -> %u", pk.key, partyId );
    }
    else
    {
      const uint partyId = static_cast<uint>(distance<PartyList::const_iterator>(parties.begin(), it)) + 1U;

      _gameServerData[i].info.partyId = partyId;

      LOBBY_LOG_MSG( "+++ PARTY: %08X -> %u", pk.key, partyId );
    }
  }

  ComplementWithLegacyAi( _lineup );
}

} //namespace lobby
