#include "stdafx.h"
#include "LiveMMakingSvc.h"
#include "RILiveMMaking.auto.h"
#include "RILiveMMakingClient.auto.h"
#include "Server/LobbySocial/SocialLobbyMaps.h"
#include "RatingSortMmLogic.h"
#include "RankMatchmaking.h"
#include "HeroesTable.h"
#include "SimpleMMaking.h"
#include "Db/DBServer.auto.h"
#include "LiveMMakingConfigVars.h"
#include "Server/TourneyCfg/TourneyCfg.h"
#include "System/InlineProfiler.h"



namespace mmaking
{

LiveMMaking::LiveMMaking( const Transport::TServiceId & _serviceId ) :
serviceId( _serviceId ),
producePvpStatusInfo( false )
{
}



LiveMMaking::~LiveMMaking()
{
}



StrongMT<IMMakingLogic> LiveMMaking::StartLogic( const NDb::AdvMapDescription * mapDesc )
{
  StrongMT<MMConfig> config = CreateConfigFromStatics();

  StrongMT<IHeroesTable> heroes = LoadHeroes( config );
  if ( !heroes )
    return 0;

  NI_VERIFY( mapDesc->matchmakingSettings, "", return 0 );

  const NDb::EMapType mapType = mapDesc->mapType;
  const string mapId = mapDesc->GetDBID().GetFormatted();
  const int teamSize = mapDesc->teamSize;
  

  switch ( mapType )
  {
    default:
      ErrorTrace( "Wrong live mmaking map type %d!", (int)mapType );
      return 0;

    case NDb::MAPTYPE_PVP:
    case NDb::MAPTYPE_CTE:
    case NDb::MAPTYPE_COOPERATIVE:
      if ( config->mockMatchmaking || mapDesc->matchmakingSettings->mock || tourney::Enabled() )
      {
        StrongMT<StubMMaking> testMm = new StubMMaking( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "testmm" );
        if ( tourney::Enabled() || mapDesc->matchmakingSettings->isTournamentMap)
          testMm->EnableAlgoStartRotation( false );
        producePvpStatusInfo = true;
        return testMm.Get();
      }
      else if ( mapDesc->matchmakingSettings->useRanking )
      {
        StrongMT<RankMMakingLogic> liveMM = new RankMMakingLogic( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "livemmaking" );
        liveMM->LaunchParallelThread();
        producePvpStatusInfo = true;
        return liveMM.Get();
      }
      else
      {
        StrongMT<RatingSortMmLogic> liveMM = new RatingSortMmLogic( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "livemmaking" );
        liveMM->LaunchParallelThread();
        producePvpStatusInfo = true;
        return liveMM.Get();
      }

    case NDb::MAPTYPE_TRAINING:
      return new SingleplayerMMaking( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "mmtrain" );

    case NDb::MAPTYPE_TUTORIAL:
      return new SingleplayerMMaking( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "mmtut" );

    case NDb::MAPTYPE_SERIES:
      return new SingleplayerMMaking( mapDesc->matchmakingSettings, config, heroes, teamSize, mapType, mapId.c_str(), "single" );
  }
}




#pragma warning( disable : 4996)

StrongMT<IHeroesTable> LiveMMaking::LoadHeroes( MMConfig * _cfg )
{
  NDb::Ptr<NDb::HeroesDB> heroes = NDb::SessionRoot::GetRoot()->logicRoot->heroes;
  NI_VERIFY( heroes, "", return 0 );
  return ProdLogicBase::FillHeroesTable( _cfg, heroes );
}



NDb::Ptr<NDb::AdvMapDescription> LiveMMaking::FindMap( const string & _mapId )
{
  Strong<socialLobby::IMaps> maps = socialLobby::LoadMaps();

  for ( size_t i = 0; i < maps->Size(); ++i )
    if ( maps->GetMapId( i ) == _mapId )
      return maps->GetMap( i );

  return 0;
}



void LiveMMaking::SetupLogic( const string & _mapId, ILiveMMakingClient * _client )
{
  MessageTrace( "Map assigment requested. map=%s, svcid='%s'", _mapId, serviceId.c_str() );

  NI_VERIFY( _client, "", return );

  NDb::Ptr<NDb::AdvMapDescription> dbmap = FindMap( _mapId );
  if ( dbmap )
  {
    logic = StartLogic( dbmap );
    if ( logic )
    {
      MessageTrace( "Map successfully loaded into MM logic. map=%s", _mapId, serviceId.c_str() );
      client = _client;
      map = _mapId;

      _client->MmLogicSetupResult( serviceId, true );
      return;
    }
  }

  ErrorTrace( "Failed to load map into MM logic. map=%s", _mapId, serviceId.c_str() );
  _client->MmLogicSetupResult( serviceId, false );
}



void LiveMMaking::AddMmRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime )
{
  NI_VERIFY( logic, "Logic is not started yet", return );
  logic->AddGroupRequest( _requestUId, _commonData, _members, _waitTime, this );
}



void LiveMMaking::RemoveMmRequest( TRequestUId _requestUId )
{
  NI_VERIFY( logic, "Logic is not started yet", return );
  logic->RemoveRequest( _requestUId, this );
}



void LiveMMaking::AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData )
{
  NI_VERIFY( logic, "Logic is not started yet", return );
  logic->AddGameForReconnect( _gameId, _gameData, this );
}



void LiveMMaking::RemoveGame( lobby::TGameId _gameId )
{
  NI_VERIFY( logic, "Logic is not started yet", return );
  logic->RemoveGame( _gameId, this );
}



void LiveMMaking::MmResultAddRequest( TRequestUId _requestUId, bool _ok )
{
  NI_VERIFY( client, "Cleint is not connected yet", return );
  client->MmResultAddRequest( _requestUId, _ok );
}



void LiveMMaking::MmResultRemoveRequest( TRequestUId _requestUId, bool _ok )
{
  NI_VERIFY( client, "Cleint is not connected yet", return );
  client->MmResultRemoveRequest( _requestUId, _ok );
}



void LiveMMaking::MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok )
{
  NI_VERIFY( client, "Cleint is not connected yet", return );
  client->MmResultAddReconnectGame( _gameId, _ok );
}



void LiveMMaking::MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok )
{
  NI_VERIFY( client, "Cleint is not connected yet", return );
  client->MmResultRemoveReconnectGame( _gameId, _ok );
}



void LiveMMaking::Poll()
{
  NI_PROFILE_FUNCTION;

  timer::Time now = timer::Now();

  if ( !logic || !client )
    return;

  logic->SetTime( now );
  logic->Poll();

  {    
    SGame game;
    if ( logic->PopGame( game ) )
      client->GameMatchmaked( game );
  }

  {
    SReconnectSlot slot;
    if ( logic->PopReconnectSlot( slot ) )
      client->GameMatchmakedForReconnect( slot );
  }

  UpdatePvPStat( now );
}



void LiveMMaking::OnConfigReload()
{
  if ( !logic )
    return;

  StrongMT<MMConfig> reloadedConfig = CreateConfigFromStatics();

  StrongMT<IHeroesTable> heroes = LoadHeroes( reloadedConfig );
  if ( !heroes )
    return;

  logic->OnConfigReload( reloadedConfig, heroes );
}



void LiveMMaking::UpdatePvPStat( timer::Time _now )
{
  if ( !producePvpStatusInfo )
    return;

  if ( _now < nextPvpStatus )
    return;
  nextPvpStatus = _now + 1.0;

  client->MmDebugStatus( logic->GetDebugStatus().c_str() );

  unsigned t1=0, t2=0;
  logic->GetLineStatistics( t1, t2 );
}

} //namespace mmaking
