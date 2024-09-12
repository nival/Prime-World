#include "stdafx.h"
#include "SocialLobbyPvxServices.h"
#include "ISocialLobbyPvxSvc.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyPinnedLocations.h"
#include "Server/LiveMMaking/MMakingRequest.h"
#include "SocialLobbyLog.h"



namespace socialLobby
{

PvxSubcluster::PvxSubcluster( const string & _clusterId, const PvxClusterSettings & _settings, const Transport::TServiceId & _settingsSrcSvcId ) :
id( _clusterId ),
settings( _settings ),
settingsSrcSvcId( _settingsSrcSvcId )
{
  specialSet.clear();
  specialSet.insert( _settings.specialList.begin(), _settings.specialList.end() );
}



void PvxSubcluster::UpdateSettings( const PvxClusterSettings & _settings, const Transport::TServiceId & _srcSvcId )
{
  if ( !settingsSrcSvcId.empty() )
    if ( stricmp( settingsSrcSvcId.c_str(), _srcSvcId.c_str() ) > 0 )
    {
      SOCLOBBY_LOG_MSG( "PVX subcluster settings was NOT updated. cluster=%s, prev_svcid=%s, new_svcid=%s", id, settingsSrcSvcId.c_str(), _srcSvcId.c_str() );
      return;
    }

  SOCLOBBY_LOG_MSG( "Updating PVX subcluster settings. cluster=%s, prev_svcid=%s, new_svcid=%s, capacity=%u, mode=%s, spec_list=%s", id, settingsSrcSvcId.c_str(), _srcSvcId.c_str(), _settings.capacity, EPvxLobbyInstanceMode::ToString( _settings.specialMode ), _settings.specialList );

  settings = _settings;
  settingsSrcSvcId = _srcSvcId;

  specialSet.clear();
  specialSet.insert( _settings.specialList.begin(), _settings.specialList.end() );
}



PvxServiceSlot * PvxSubcluster::FindService( const Transport::TServiceId & _svcId ) const
{
  for ( TServices::const_iterator it = services.begin(); it != services.end(); ++it )
    if ( (*it)->SvcId() == _svcId )
      return *it;
  return 0;
}



void PvxSubcluster::AddService( IPvxSvc * _pvx, const Transport::TServiceId & _svcId )
{
  Strong<PvxServiceSlot> slot = new PvxServiceSlot( _svcId, _pvx );
  services.push_back( slot );
}



PvxServiceSlot * PvxSubcluster::Allocate( unsigned _loadIncrement )
{
  NI_VERIFY( !services.empty(), "", return 0 );

  Strong<PvxServiceSlot> best = *services.begin();

  {
    PvxSubcluster::TServices::iterator it = services.begin();
    ++it;
    for ( ; it != services.end(); ++it )
    {
      Strong<PvxServiceSlot> slot = *it;
      if ( slot->Load() < best->Load() )
        best = slot;
    }
  }

  SOCLOBBY_LOG_MSG( "Allocated PVX service. cluster=%s, svcid=%s, load=%u(+%u)", id, best->SvcId().c_str(), best->Load(), _loadIncrement );
  best->IncrementLoad( _loadIncrement );
  return best.Get();
}



unsigned PvxSubcluster::CountTotalLoad() const
{
  unsigned total = 0;
  for ( TServices::const_iterator it = services.begin(); it != services.end(); ++it )
    total += (*it)->Load();
  return total;
}



bool PvxSubcluster::Poll( timer::Time _now, const SConfig * _cfg )
{
  for ( TServices::iterator it = services.begin(); it != services.end(); )
  {
    Strong<PvxServiceSlot> slot = *it;
    if ( !slot->Poll( _now, _cfg, id ) )
    {
      if ( slot->SvcId() == settingsSrcSvcId )
        settingsSrcSvcId.clear();
      it = services.erase( it );
      continue;
    }
    ++it;
  }

  bool ok = !services.empty();

  if ( !ok )
    SOCLOBBY_LOG_ERR( "Lost connection to all PVX services in cluster! cluster=%s", id );

  return ok;
}







PvxServices::PvxServices( Config * _cfg ) :
config( _cfg )
{
  pinnedLocations = new PinnedLocations( _cfg->pinnedLocations, _cfg->pinnedLocationsPriority );
}



void PvxServices::ReloadConfig()
{
  pinnedLocations = new PinnedLocations( config->pinnedLocations, config->pinnedLocationsPriority );
}



void PvxServices::Add( IPvxSvc * _pvx, const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings & _settings )
{
  SOCLOBBY_LOG_MSG( "Got PVX instance. ptr=0x%d, cluster=%s, svcid=%s, capacity=%u, mode=%s, spec_list=%s", (void*)_pvx, _clusterId, _svcId.c_str(), _settings.capacity, EPvxLobbyInstanceMode::ToString( _settings.specialMode ), _settings.specialList );

  PvxSubcluster * subcluster = FindOrAllocSubcluster( _clusterId, _settings, _svcId );

  if ( PvxServiceSlot * pvxSvc = subcluster->FindService( _svcId ) )
  {
    SOCLOBBY_LOG_WRN( "Replacing previous PVX instance. cluster=%s, svcid=%s", _clusterId, _svcId.c_str() );
    pvxSvc->UpdateRemotePtr( _pvx );
    return;
  }

  subcluster->AddService( _pvx, _svcId );
}



void PvxServices::UpdateSettings( const string & _clusterId, const Transport::TServiceId & _svcId, const PvxClusterSettings & _settings )
{
  SOCLOBBY_LOG_MSG( "New PVX instance settings. cluster=%s, svcid=%s, capacity=%u, mode=%s, spec_list=%s", _clusterId, _svcId.c_str(), _settings.capacity, EPvxLobbyInstanceMode::ToString( _settings.specialMode ), _settings.specialList );

  PvxSubcluster * subcluster = FindSubcluster( _clusterId );
  if ( !subcluster )
  {
    SOCLOBBY_LOG_WRN( "PVX subcluster not found. cluster=%s, svcid=%s", _clusterId, _svcId.c_str() );
    return;
  }

  if ( !subcluster->FindService( _svcId ) )
  {
    SOCLOBBY_LOG_WRN( "PVX service not found. cluster=%s, svcid=%s", _clusterId, _svcId.c_str() );
    return;
  }

  subcluster->UpdateSettings( _settings, _svcId );
}



void PvxServices::LoadNotify( const string & _clusterId, const Transport::TServiceId & _svcId, unsigned _load )
{
  SOCLOBBY_LOG_MSG( "PVX instance load notify. cluster=%s, svcid=%s, load=%u", _clusterId, _svcId.c_str(), _load );

  PvxServiceSlot * subcluster = Find( _clusterId, _svcId );
  if ( !subcluster )
    return;

  SOCLOBBY_LOG_DBG( "PVX instance load updated. cluster=%s, svcid=%s, load=%u, prev_load=%u", _clusterId, _svcId.c_str(), _load, subcluster->Load() );
  subcluster->UpdateLoad( _load );
}



Strong<IPvxSvcWrapper> PvxServices::Allocate( const string & _clusterId, unsigned _loadIncrement )
{
  PvxSubcluster * subcluster = FindSubcluster( _clusterId );
  if ( !subcluster )
  {
    subcluster = GetLeastLoaded();
    if ( subcluster )
      SOCLOBBY_LOG_ERR( "No PVX services with requested location! Returning first available. cluster=%s, result=%s", _clusterId, subcluster->Id() );
  }

  if ( !subcluster )
  {
    SOCLOBBY_LOG_ERR( "No PVX services! cluster=%s", _clusterId );
    return 0;
  }

  return subcluster->Allocate( _loadIncrement );
}



PvxSubcluster * PvxServices::FindSubcluster( const string & _clusterId ) const
{
  for ( TClusters::const_iterator it = clusters.begin(); it != clusters.end(); ++it )
    if ( !stricmp( (*it)->Id().c_str(), _clusterId.c_str() ) )
      return *it;

  return 0;
}



PvxSubcluster * PvxServices::FindOrAllocSubcluster( const string & _clusterId, const PvxClusterSettings & _settings, const Transport::TServiceId & _settingsSrcSvcId )
{
  for ( TClusters::iterator it = clusters.begin(); it != clusters.end(); ++it )
    if ( !stricmp( (*it)->Id().c_str(), _clusterId.c_str() ) )
    {
      Strong<PvxSubcluster> cluster = *it;
      cluster->UpdateSettings( _settings, _settingsSrcSvcId );
      return cluster;
    }

  SOCLOBBY_LOG_MSG( "New PVX cluster. cluster=%s, capacity=%u, mode=%s, spec_list=%s", _clusterId, _settings.capacity, EPvxLobbyInstanceMode::ToString( _settings.specialMode ), _settings.specialList );

  clusters.push_back( new PvxSubcluster( _clusterId, _settings, _settingsSrcSvcId ) );
  return clusters.back();
}



PvxServiceSlot * PvxServices::Find( const string & _clusterId, const Transport::TServiceId & _svcId ) const
{
  if ( const PvxSubcluster * subcluster = FindSubcluster( _clusterId ) )
  {
    if ( PvxServiceSlot * pvxSvc = subcluster->FindService( _svcId ) )
      return pvxSvc;
  }

  SOCLOBBY_LOG_ERR( "PVX instance not found. cluster=%s, svcid=%s", _clusterId, _svcId.c_str() );
  return 0;
}



PvxSubcluster * PvxServices::GetLeastLoaded()
{
  float bestLoad = 0;
  Strong<PvxSubcluster> bestSubcluster;
  for ( TClusters::iterator it = clusters.begin(); it != clusters.end(); ++it )
  {
    Strong<PvxSubcluster> subcluster = *it;

    if ( !subcluster->Capacity() )
      continue;

    float load = (float)subcluster->CountTotalLoad() / (float)subcluster->Capacity();

    if ( !bestSubcluster || ( load < bestLoad ) )
    {
      bestLoad = load;
      bestSubcluster = subcluster;
    }
  }

  return bestSubcluster;
}



struct PvxServices::ClusterPingQuality
{
  int     count;
  float   sum, avg;
  float   minQ, maxQ;
  void Add( float q ) {
    minQ = count ? Min( minQ, q ) : q;
    maxQ = count ? Max( maxQ, q ) : q;
    count += 1;
    sum += q;
    avg = sum / count;
  }
  ClusterPingQuality() : sum( 0 ), count( 0 ), avg( 0 ), minQ( 0 ), maxQ( 0 ) {}
};



void PvxServices::CountMmRequestMemberPings( TClusterCounter & counter, const mmaking::SRequestMember & memb )
{
  if ( memb.geoInfo.pings.empty() )
    return;

  int minPing = 0, maxPing = 0;
  bool first = true;

  for ( int k = 0; k < memb.geoInfo.pings.size(); ++k )
    if ( FindSubcluster( memb.geoInfo.pings[k].clusterId ) )
    {
      const int p = memb.geoInfo.pings[k].ping;
      minPing = first ? p : Min( minPing, p );
      maxPing = first ? p : Max( maxPing, p );
      first = false;
    }

  for ( int k = 0; k < memb.geoInfo.pings.size(); ++k )
    if ( FindSubcluster( memb.geoInfo.pings[k].clusterId ) )
    {
      const int p = memb.geoInfo.pings[k].ping;
      const float q = mmaking::MmRequest::CalculateRelativePingQuality( p, minPing, maxPing, config->pingScaleThreshold, config->pingScaleFactor );

      string clid = memb.geoInfo.pings[k].clusterId;
      NStr::ToLower( &clid );

      counter[clid].Add( q );
    }
}



inline float RelativeLoadBias( float relativeLoad )
{
  const float Threshold = 0.75f;
  const float Bias = 0.5f;

  if ( relativeLoad < Threshold )
    return 0;
  if ( relativeLoad > 1.0f )
    return Bias;
  return ( relativeLoad - Threshold ) / ( 1.0f - Threshold ) * Bias;
}



string PvxServices::DetermineClusterForGame( const mmaking::SGame & _game )
{
  if ( clusters.empty() )
    return "";

  string pinnedCluster = CheckForPinnedCluster( _game );
  if ( !pinnedCluster.empty() )
  {
    NStr::ToLower( &pinnedCluster );
    return pinnedCluster;
  }

  string forcedCluster = CheckForForcedDevCluster( _game );
  if ( !forcedCluster.empty() )
  {
    NStr::ToLower( &forcedCluster );
    return forcedCluster;
  }

  TClusterCounter counter;

  for ( int i = 0; i < _game.humans.size(); ++i )
    for ( int mi = 0; mi < _game.humans[i].members.size(); ++mi )
      CountMmRequestMemberPings( counter, _game.humans[i].members[mi] );

  string locDataDump;
  for ( TClusterCounter::const_iterator it = counter.begin(); it != counter.end(); ++it )
    locDataDump += NI_STRFMT( "%s%s:%.2f*%d", ( it == counter.begin() ? "" : " " ), it->first, it->second.avg, it->second.count );
  SOCLOBBY_LOG_DBG( "Finding best pvx service. game_pings=[%s]", locDataDump );

  for ( int mode = 0; mode < 2; ++mode )
  {
    string best;
    float bestPingFactor = 0;
    for ( TClusterCounter::const_iterator it = counter.begin(); it != counter.end(); ++it )
    {
      const string & clid = it->first;
      PvxSubcluster * subcluster = FindSubcluster( clid );
      if ( !subcluster )
        continue;

      if ( !subcluster->Capacity() )
        continue;

      const ClusterPingQuality & locData = it->second;

      unsigned totalLoad = subcluster->CountTotalLoad();
      float relativeLoad = (float)totalLoad / (float)subcluster->Capacity();

      if ( mode == 0 )
      {
        if ( relativeLoad >= 1.0f )
          continue;

        float pingFactor = locData.avg + RelativeLoadBias( relativeLoad );

        if ( best.empty() || ( pingFactor < bestPingFactor ) ) {
          best = clid;
          bestPingFactor = pingFactor;
        }
      }
      else // if ( mode == 1 )
      {
        if ( best.empty() || ( relativeLoad < bestPingFactor ) ) {
          best = clid;
          bestPingFactor = relativeLoad;
        }
      }
    }

    if ( !best.empty() )
    {
      if ( mode == 0 )
        SOCLOBBY_LOG_MSG( "Found best cluster. cluster=%s, ping_factor=%.2f", best, bestPingFactor );
      else
        SOCLOBBY_LOG_WRN( "All listed subclusters are overloaded. Using least-loaded from list. cluster=%s", best );
      return best;
    }
  }

  if ( Strong<PvxSubcluster> subcluster = GetLeastLoaded() )
  {
    SOCLOBBY_LOG_ERR( "Could not find appropriate pvx service. Using least loaded available. cluster=%s", subcluster->Id() );
    return subcluster->Id();
  }

  return "";
}



string PvxServices::CheckForPinnedCluster( const mmaking::SGame & _game )
{
  const PinnedLocations::TMapping & mapping = pinnedLocations->Mapping();

  std::map<std::string, int> counter;
  for ( int i = 0; i < _game.humans.size(); ++i )
    for ( int mi = 0; mi < _game.humans[i].members.size(); ++mi )
    {
      const std::string loc = _game.humans[i].members[mi].geoInfo.location.c_str();

      PinnedLocations::TMapping::const_iterator it = mapping.find( loc );
      if ( it == mapping.end() )
        continue;
      const std::string & clusterId = it->second;
    
      counter[clusterId] += 1;
    }

  if ( counter.empty() )
    return "";

  SOCLOBBY_LOG_DBG( "Pinned locations in game: data=%s", counter );

  string mostPopularClust;
  int maxPop = 0;

  const PinnedLocations::TPriorityData & priority = pinnedLocations->Priority();

  for ( std::map<std::string, int>::const_iterator it = counter.begin(); it != counter.end(); ++it )
  {
    const std::string & clusterId = it->first;
    int cnt = it->second;

    PinnedLocations::TPriorityData::const_iterator itPrio = priority.find( clusterId );
    if ( itPrio != priority.end() )
      cnt += itPrio->second;

    if ( cnt > maxPop )
    {
      maxPop = cnt;
      mostPopularClust = clusterId.c_str();
    }
  }
  NI_VERIFY( !mostPopularClust.empty() && maxPop, "", return "" );

  if ( maxPop < config->pinnedLocationsThreshold )
  {
    SOCLOBBY_LOG_DBG( "Pinned location threshold is not passed. cluster=%s, counter=%d, threshold=%d", mostPopularClust, maxPop, config->pinnedLocationsThreshold );
    return "";
  }

  PvxSubcluster * subcluster = FindSubcluster( mostPopularClust );
  if ( !subcluster )
  {
    SOCLOBBY_LOG_WRN( "Pinned location cluster is not available. cluster=%s", mostPopularClust );
    return "";
  }

  const unsigned totalLoad = subcluster->CountTotalLoad(), cap = subcluster->Capacity();
  if ( totalLoad >= cap )
  {
    SOCLOBBY_LOG_WRN( "Pinned location cluster is overloaded. cluster=%s, load=%u, capacity=%u", mostPopularClust, totalLoad, cap );
    return "";
  }

  SOCLOBBY_LOG_MSG( "Using pinned location. cluster=%s, counter=%d, load=%u, capacity=%u", mostPopularClust, maxPop, totalLoad, cap );
  return mostPopularClust;
}



void PvxServices::Poll( timer::Time _now )
{
  for ( TClusters::iterator it = clusters.begin(); it != clusters.end(); )
  {
    Strong<PvxSubcluster> subcluster = *it;

    if ( subcluster->Poll( _now, config ) )
      ++it;
    else
      it = clusters.erase( it );
  }
}



string PvxServices::CheckForForcedDevCluster( const mmaking::SGame & _game )
{
  for ( TClusters::iterator it = clusters.begin(); it != clusters.end(); ++it )
  {
    Strong<PvxSubcluster> subcluster = *it;
    if ( subcluster->SpecialMode() == EPvxLobbyInstanceMode::Normal )
      continue;

    int special = 0, total = 0;
    for ( int i = 0; i < _game.humans.size(); ++i )
      for ( int mi = 0; mi < _game.humans[i].members.size(); ++mi )
      {
        ++total;
        if ( subcluster->IsInSpecialList( _game.humans[i].members[mi].mmId ) )
          ++special;
      }

    if ( subcluster->SpecialMode() == EPvxLobbyInstanceMode::ForcePartial )
    {
      if ( !special )
        continue;
    }
    else if ( subcluster->SpecialMode() == EPvxLobbyInstanceMode::ForceFullGames )
    {
      if ( special < total )
        continue;
    }

    SOCLOBBY_LOG_MSG( "Forcing game to cluster. cluster=%s, mode=%d, load=%u, capacity=%u", subcluster->Id(), (int)subcluster->SpecialMode(), 
      subcluster->CountTotalLoad(), subcluster->Capacity() );

    return subcluster->Id();
  }

  return "";
}



bool PvxServiceSlot::Poll( timer::Time _now, const SConfig * _cfg, const string & _dbgClusterId )
{
  const rpc::Status st = remote->GetStatus();
  if ( st == rpc::Connected )
  {
    if ( connectionLostTimeout >= 0 ) {
      SOCLOBBY_LOG_MSG( "Connection to PVX service restored. cluster=%s, svcid=%s", _dbgClusterId, svcId.c_str() );
      connectionLostTimeout = -1;
    }
    return true;
  }

  if ( connectionLostTimeout < 0 ) {
    SOCLOBBY_LOG_ERR( "Lost connection to PVX service! cluster=%s, svcid=%s", _dbgClusterId, svcId.c_str() );
    connectionLostTimeout = _now + _cfg->pvxDisconnectTimeout;
    return true;
  }

  if ( _now > connectionLostTimeout ) {
    SOCLOBBY_LOG_ERR( "No connection to PVX service. Removing it. cluster=%s, svcid=%s", _dbgClusterId, svcId.c_str() );
    return false;
  }

  return true;
}

} //namespace socialLobby
