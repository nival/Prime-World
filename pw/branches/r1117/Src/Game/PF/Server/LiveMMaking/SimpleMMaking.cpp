#include "stdafx.h"
#include "SimpleMMaking.h"
#include "MMakingLog.h"
#include "MMakingDraftGame.h"
#include "Server/TourneyCfg/TourneyCfg.h"
#include "Db/DBServer.auto.h"


namespace mmaking
{

SimpleMMaking::SimpleMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
BaseMMaking( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
m_requestsCounter( 0 ),
m_now( 0 ),
m_enableAlgoStartRotation( true )
{
}



void SimpleMMaking::Poll()
{
  BaseMMaking::Poll();

  PullReloadedConfig();

  m_loger->Poll( m_now );
}



void SimpleMMaking::AddGroupRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime, IMMakingLogicCallback * _callback )
{
  NI_VERIFY( !_members.empty(), "", return );

  StrongMT<MmRequest> req = new MmRequest( m_settings, _requestUId, m_now - _waitTime, _commonData );
  if ( !req->Init( _members, m_heroes, m_ranks, m_locales, m_locations, m_loger ) ) {
    if ( _callback ) _callback->MmResultAddRequest( _requestUId, false );
    return;
  }

  std::pair<TRequestMap::iterator, bool> insResult = m_requests.insert( TRequestMap::value_type( _requestUId, req ) );
  if ( !insResult.second ) {
    if ( _callback ) _callback->MmResultAddRequest( _requestUId, false );
    NI_ALWAYS_ASSERT( NI_STRFMT( "Duplicate request id %d", _requestUId ) );
    StrongMT<MmRequest> oldReq = insResult.first->second;
    m_loger->Log( ELogLevel::Critical, "Duplicate request id %d (user ids %d, existing user ids %d)", req->RequestId(), req->FormatAllMmIds().c_str(), oldReq->FormatAllMmIds().c_str() );
    return;
  }

  ++m_requestsCounter;

  m_loger->Log( ELogLevel::Normal, "Request added: id %d, %s", _requestUId, req->FormatAll().c_str() );

  if ( _callback ) _callback->MmResultAddRequest( _requestUId, true );
}



void SimpleMMaking::RemoveRequest( TRequestUId _requestUId, IMMakingLogicCallback * _callback )
{
  m_loger->Log( ELogLevel::Normal, "Removing request: %d", _requestUId );

  TRequestMap::iterator it = m_requests.find( _requestUId );
  NI_VERIFY( it != m_requests.end(), NI_STRFMT( "Unknown reqId %d", _requestUId ), return );

  m_requests.erase( it );

  if ( _callback ) _callback->MmResultAddRequest( _requestUId, true );
}



void SimpleMMaking::GetLineStatistics( unsigned & team1, unsigned & team2 )
{
  team1 = team2 = 0;
  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end(); ++it )
    switch ( it->second->CommonData().team )
    {
      case lobby::ETeam::Team1:
        ++team1;
        break;

      case lobby::ETeam::Team2:
        ++team2;
        break;

      default:
        ;
    }
}









bool SingleplayerMMaking::PopGame( SGame & result )
{
  if ( m_requests.empty() )
    return false;

  TRequestMap::iterator it = m_requests.begin();
  StrongMT<MmRequest> req = it->second;

  m_requests.erase( it );


  MMakingDraftGame draft;
  draft.Init( m_teamSize, EBasket::Undefined, m_heroes );

  lobby::ETeam::Enum faction = lobby::ETeam::None;
  draft.AddMembers( req, faction );

  if ( m_mapType == NDb::MAPTYPE_TRAINING )
    draft.AddBots( m_settings->trainingFemaleBotsCount );

  draft.ProduceResult( result, m_mapType, m_mapId, m_now );

  LogGame( ELogLevel::Normal, result, "Game ready: " );

  return true;
}









bool CompStompMMaking::PopGame( SGame & result )
{
  lobby::ETeam::Enum searchTeams[2] = { lobby::ETeam::Team1, lobby::ETeam::Team2 };

  for ( int i = 0; i < 2; ++i )
    if ( RetrieveGameForTeam( result, searchTeams[i] ) )
      return true;

  return false;
}



bool CompStompMMaking::RetrieveGameForTeam( SGame & result, lobby::ETeam::Enum searchTeam )
{
  if ( m_enableAlgoStartRotation )
  {
    for ( int rot = 0; rot < Min( (int)m_requests.size(), m_teamSize ); ++rot )
      if ( RetrieveGameForTeam( result, searchTeam, rot ) )
        return true;
  }
  else
    return RetrieveGameForTeam( result, searchTeam, 0 );

  return false;
}



bool CompStompMMaking::RetrieveGameForTeam( SGame & result, lobby::ETeam::Enum searchTeam, int algoStartRotation )
{
  if ( m_requests.empty() )
    return false;

  MMakingDraftGame draft;
  draft.Init( m_teamSize, EBasket::Undefined, m_heroes );

  std::vector<TRequestMap::iterator> toRemove;
  toRemove.reserve( m_teamSize );

  timer::Time latestRequest = -1;

  for ( TRequestMap::iterator it = GetRotatedRequestsBegin( algoStartRotation ); it != m_requests.end(); ++it )
  {
    StrongMT<MmRequest> req = it->second;

    if ( req->CommonData().team != searchTeam )
      continue;

    if ( !draft.GameSize() )
      latestRequest = req->StartTime();
    else
      latestRequest = Max( latestRequest, req->StartTime() );

    NI_ASSERT( draft.TeamSize( searchTeam ) < m_teamSize, "" );
    draft.AddMembers( req );

    toRemove.push_back( it );

    if ( draft.TeamSize( searchTeam ) == m_teamSize ) //polna korobochka
    {
      FinishGame( result, draft, toRemove );
      return true;
    }
  }

  if ( ( draft.TeamSize( searchTeam ) > 0 ) && ( draft.TeamSize( searchTeam ) <= m_teamSize ) )
  {
    NI_ASSERT( latestRequest >= 0, "" );
    timer::Time delta = m_now - latestRequest;
    NI_ASSERT( delta >= 0, "" );
    if ( delta > m_waitThreshold )
    {
      FinishGame( result, draft, toRemove );
      return true;
    }
  }

  return false;
}


void CompStompMMaking::FinishGame( SGame & result, MMakingDraftGame & draft, const std::vector<TRequestMap::iterator> & toRemove )
{
  draft.AddBots();

  draft.ProduceResult( result, NDb::MAPTYPE_TRAINING, m_mapId, m_now );

  LogGame( ELogLevel::Normal, result, "Game ready: " );

  for ( size_t i = 0; i < toRemove.size(); ++i )
    m_requests.erase( toRemove[i] );
}

bool StubMMaking::PopGame( SGame & result )
{
  lobby::ETeam::Enum teams[3] = { lobby::ETeam::None, lobby::ETeam::Team1, lobby::ETeam::Team2 };

  if ( m_mapType == NDb::MAPTYPE_COOPERATIVE )
  {
    for ( int i = 1; i < 3; ++i )
      if ( PopGameImpl( result, teams[i] ) )
        return true;
    return false;
  }

  if ( m_manoeuvresWaitThreshold || tourney::Enabled() )
  {
    for ( int i = 0; i < 3; ++i )
      if ( PopGameImpl( result, teams[i] ) )
        return true;
  }
  else
    return PopGameImpl( result, lobby::ETeam::None );

  return false;
}



bool StubMMaking::PopGameImpl( SGame & result, lobby::ETeam::Enum currentFaction )
{
  if ( m_enableAlgoStartRotation )
  {
    for ( int rot = 0; rot < Min( (int)m_requests.size(), m_teamSize ); ++rot )
      if ( PopGameImpl( result, currentFaction, rot ) )
        return true;
  }
  else
    return PopGameImpl( result, currentFaction, 0 );

  return false;
}



bool StubMMaking::PopGameImpl( SGame & result, lobby::ETeam::Enum currentFaction, int algoStartRotation )
{
  if ( m_requests.empty() )
    return false;

  const bool coop = m_mapType == NDb::MAPTYPE_COOPERATIVE;

  MMakingDraftGame draft;
  draft.Init( m_teamSize, EBasket::Undefined, m_heroes );

  std::vector<TRequestMap::iterator> toRemove;
  toRemove.reserve( m_teamSize * 2 );

  for ( TRequestMap::iterator it = GetRotatedRequestsBegin( algoStartRotation ); it != m_requests.end(); ++it )
  {
    StrongMT<MmRequest> req = it->second;

    timer::Time userWait = m_now - req->StartTime();
    if ( userWait < m_config->mockMinimumUserWait )
      continue;

    else if ( currentFaction != lobby::ETeam::None ) //manoeuvre
    {

      if ( req->CommonData().team != currentFaction )
        continue;

      if ( draft.TeamSize( lobby::ETeam::Team1 ) < m_teamSize ) {
        draft.AddMembers( req, coop ? lobby::ETeam::None : lobby::ETeam::Team1 );
        toRemove.push_back( it );
      }
      else if ( draft.TeamSize( lobby::ETeam::Team2 ) < m_teamSize ) {
        draft.AddMembers( req, coop ? lobby::ETeam::None : lobby::ETeam::Team2 );
        toRemove.push_back( it );
      }
    }
    else
    {
      if ( draft.CanGoToTeam( req->CommonData().team, req->Size() ) )
      {
        draft.AddMembers( req );
        toRemove.push_back( it );
      }
    }

    bool gameOk = false;
    if ( coop )
      gameOk = ( draft.TeamSize( lobby::ETeam::Team1 ) == m_teamSize ) || ( draft.TeamSize( lobby::ETeam::Team2 ) == m_teamSize );
    else
      gameOk = ( draft.TeamSize( lobby::ETeam::Team1 ) == m_teamSize ) && ( draft.TeamSize( lobby::ETeam::Team2 ) == m_teamSize );

    if ( gameOk )
    {
      for ( size_t i = 0; i < toRemove.size(); ++i )
        m_requests.erase( toRemove[i] );

      draft.AddBots();
      draft.ProduceResult( result, m_mapType, m_mapId, m_now );

      LogGame( ELogLevel::Normal, result, "Game ready: " );
      return true;
    }
  }

  return false;
}

} //namespace mmaking
