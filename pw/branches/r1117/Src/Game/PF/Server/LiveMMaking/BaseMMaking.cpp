#include "stdafx.h"
#include "BaseMMaking.h"
#include "RankTable.h"
#include "MMakingLog.h"
#include "System/InlineProfiler.h"
#include "Db/DBServer.auto.h"


namespace mmaking
{

NDb::Ptr<NDb::MapList> BaseMMaking::GetMapListResource()
{
  return NDb::SessionRoot::GetRoot()->logicRoot->mapList;
}



BaseMMaking::BaseMMaking( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
m_settings( _settings ),
m_config( _cfg ),
m_heroes( _heroes ),
m_teamSize( _teamSize ),
m_mapType( _mapType ),
m_mapId( _mapId ),
m_locales( m_config->localeTable, m_config->donorLocale, m_config->isolatedLocales ),
m_locations( m_config->geolocationTable, "", "" ),
m_enableRandomQueueIterator(m_config->enableRandomQueueIterator)
{
  string logHeader = NI_STRFMT( "Team size: %d; Map: %s", m_teamSize, m_mapId.c_str() );

  m_loger = new Loger( _logSuffix, logHeader.c_str() );
  m_loger->SetLogLevel( (ELogLevel::Enum)m_config->logLevel );

  StrongMT<RankTable> ranks = new RankTable;
  ranks->Init( _settings );
  m_ranks = ranks;
}



void BaseMMaking::Poll()
{
}



void BaseMMaking::OnConfigReload( MMConfig * _cfg, IHeroesTable * _heroes )
{
  threading::MutexLock lock( m_configReloadMutex );
  
  if ( _cfg )
    m_reloadedConfig = _cfg;

  if ( _heroes )
    m_reloadedHeroes = _heroes;
}



void BaseMMaking::AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData, IMMakingLogicCallback * _callback )
{
  if ( _callback )
    _callback->MmResultAddReconnectGame( _gameId, false );
}



void BaseMMaking::RemoveGame( lobby::TGameId _gameId, IMMakingLogicCallback * _callback )
{
  if ( _callback )
    _callback->MmResultRemoveReconnectGame( _gameId, false );
}



bool BaseMMaking::CheckRequestMmIds( const TRequestMap & _requests, MmRequest * _req ) const
{
  for ( int i = 0; i < _req->Size(); ++i )
  {
    const int mmId = _req->Member( i ).mmId;
    if ( _requests.find( mmId ) != _requests.end() )
    {
      ErrorTrace( "Duplicate request with mm id %d", mmId );
      m_loger->Log( ELogLevel::Critical, "Duplicate request with mm id %d", mmId );
      return false;
    }
  }
  return true;
}



void BaseMMaking::FormatGame( string & _buffer, const SGame & _game )
{
  NI_PROFILE_FUNCTION;

  float hratings[2] = { 0, 0 };
  float pratings[2] = { 0, 0 };
  float forces[2] = { 0, 0 };
  int count[2] = { 0, 0 };

  vector<vector<string> > lines;

  lines.push_back( vector<string>() );
  vector<string> & item = lines.back();
  item.push_back( "Team" );
  item.push_back( "Faction" );
  item.push_back( "UserId" );
  item.push_back( "ReqId" );
  item.push_back( "Sex" );
  item.push_back( "Hero" );
  item.push_back( "Basket" );
  item.push_back( "PRating" );
  item.push_back( "HRating" );
  item.push_back( "Force" );
  item.push_back( "Wait" );
  item.push_back( "Loses" );
  item.push_back( "Wins" );
  item.push_back( "Fame" );
  item.push_back( "Loc" );
  item.push_back( "Pings" );

  for ( int tidx = 0; tidx < 2; ++tidx )
  {
    for ( int i = 0; i < _game.humans.size(); ++i )
    {
      const SGameParty & party = _game.humans[i];
      if ( tidx != lobby::ETeam::Index( party.common.team ) )
        continue;
  
      count[tidx] += party.members.size();
      float prevForce = forces[tidx];
      for ( int j = 0; j < party.members.size(); ++j )
      {
        const SRequestMember & memb = party.members[j];
        hratings[tidx] += memb.heroRating;
        pratings[tidx] += memb.playerRating;
        forces[tidx] += memb.force;
        lines.push_back( vector<string>() );
        vector<string> & item = lines.back();
        item.reserve( 10 );
        item.push_back( NI_STRFMT( "%s", lobby::ETeam::ToString( party.common.team ) ) );
        item.push_back( NI_STRFMT( "%s", lobby::ETeam::ToString( memb.original_team) ) );
        item.push_back( NI_STRFMT( "%d", memb.mmId ) );
        item.push_back( NI_STRFMT( "%d", party.requestUId ) );
        item.push_back( NI_STRFMT( "%s", lobby::ESex::ToString( memb.sex ) ) );
        item.push_back( NI_STRFMT( "%s", memb.heroId.c_str() ) );
        item.push_back( NI_STRFMT( "%s", mmaking::EBasket::ToString( memb.basket ) ) );
        item.push_back( NI_STRFMT( "%.1f", memb.playerRating ) );
        item.push_back( NI_STRFMT( "%.1f", memb.heroRating ) );
        item.push_back( NI_STRFMT( "%.1f", memb.force ) );
        item.push_back( NI_STRFMT( "%.1f", party.waitTime ) );
        item.push_back( NI_STRFMT( "%d", memb.loseStreak ) );
        item.push_back( NI_STRFMT( "%d", memb.totalWins ) );
        item.push_back( NI_STRFMT( "%d", memb.fameLevel ) );
        item.push_back( NI_STRFMT( "%s", memb.geoInfo.locale ) );
        item.push_back( NI_STRFMT( "%s", memb.geoInfo.FmtPings() ) );
      }
      
      if (m_settings->useRanking && party.members.size() >1)
      {
        float maxForce =0; 
        for ( int j = 0; j < party.members.size(); ++j )
        {
          const SRequestMember & memb = party.members[j];
          if (memb.force > maxForce)
            maxForce = memb.force;
        }
        forces[tidx] = prevForce + maxForce * party.members.size();
      }


    }

    for ( int i = 0; i < _game.bots.size(); ++i )
    {
      if ( tidx != lobby::ETeam::Index( _game.bots[i].team ) )
        continue;
      lines.push_back( vector<string>() );
      vector<string> & item = lines.back();
      item.reserve( 4 );
      item.push_back( NI_STRFMT( "%s", lobby::ETeam::ToString( _game.bots[i].team ) ) );
      item.push_back( "Bot" );
      item.push_back( NI_STRFMT( "%s", _game.bots[i].heroSkin.c_str() ) );
      item.push_back( string() );
      item.push_back( NI_STRFMT( "%s", _game.bots[i].heroId.c_str() ) );
    }
  }

  //And now some pretty formatting...
  vector<int> maxLens;
  for ( int lnIdx = 0; lnIdx < lines.size(); ++lnIdx ) {
    const vector<string> & line = lines[lnIdx];
    for ( int wordIdx = 0; wordIdx < line.size(); ++wordIdx ) {
      if ( line.size() > maxLens.size() )
        maxLens.resize( line.size(), 0 );

      int total = 0;
      for ( int i = 0; i < line.size(); ++i ) {
        int len = line[i].length() + 1;
        maxLens[i] = Max( maxLens[i], len );
        total += len;
      }
    }
  }

  _buffer += NI_STRFMT( "Type %s, map '%s', basket %s\n", NDb::EnumToString( _game.mapType ), _game.mapId.c_str(), mmaking::EBasket::ToString( _game.basket ) );

  for ( int t = 0; t < 2; ++t )
  {
    float avgf = 0, avghr = 0, avgpr = 0;
    if ( count[t] ) {
      avgf = forces[t] / count[t];
      avghr = hratings[t] / count[t];
      avgpr = pratings[t] / count[t];
    }
    _buffer += NI_STRFMT( "%s: Hero Rating %.1f, Player Rating %.1f, Force %.1f\n", lobby::ETeam::ToString( lobby::ETeam::Index( t ) ), avghr, avgpr, avgf );
  }

  for ( int lnIdx = 0; lnIdx < lines.size(); ++lnIdx )
  {
    const vector<string> & line = lines[lnIdx];
    NI_VERIFY( line.size() <= maxLens.size(), "", continue );
    for ( int wordIdx = 0; wordIdx < maxLens.size(); ++wordIdx )
      _buffer += NI_STRFMT( "%-*s", maxLens[wordIdx], ( wordIdx < line.size() ) ? line[wordIdx].c_str() : "" );
    _buffer += "\n";
  }
}



void BaseMMaking::LogGame( ELogLevel::Enum _lvl, const SGame & _game, const char * _prefix )
{
  NI_PROFILE_FUNCTION;

  string buf;
  buf.reserve( 512 );
  buf = _prefix;

  FormatGame( buf, _game );

  m_loger->Log( _lvl, buf.c_str() );
}



void BaseMMaking::PullReloadedConfig()
{
  threading::MutexLock lock( m_configReloadMutex );

  if ( m_reloadedConfig )
  {
    m_config = m_reloadedConfig;
    m_reloadedConfig = 0;
  }

  if ( m_reloadedHeroes )
  {
    m_heroes = m_reloadedHeroes;
    m_reloadedHeroes = 0;
  }
}

} //namespace mmaking
