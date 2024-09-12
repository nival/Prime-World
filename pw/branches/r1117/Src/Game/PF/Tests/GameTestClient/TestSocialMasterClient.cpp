#include "stdafx.h"
#include "TestSocialMasterClient.h"
#include "TestSocialClient.h"
#include "TestSocialTransportRpc.h"
#include "TestSocialTransportHttp.h"
#include "System/InlineProfiler.h"
#include "GTCLog.h"


namespace GtcSocial
{

SocialMasterClient::SocialMasterClient( Network::INetworkDriver * _driver, TransportLayer::TransportModule * _sptm,
                            const string & _loginaddr, const string & _user, const string & _pswd,
                            int _clientsCount, const SSocialConfig & _socConfig, unsigned _firstUdpPort, unsigned _udpPortSearchRange ) :
GameTestClient2::ClientBase( 0, _driver, _sptm, 100, _loginaddr, _user, _pswd, "", _firstUdpPort, _udpPortSearchRange ),
clientsCount( _clientsCount ), socConfig( _socConfig ),
nextClientSpawn( timer::Now() ),
teamSwitch( lobby::ETeam::Team1 ),
spawningPartyCounter( 0 ),
rnd( GetTickCount() ),
currentUIdRangeIndex( 0 ),
userIdRangeRequested( false ),
nextSessionContextId( 1 ),
nextServerStatusRequest( 0 )
{
}



int SocialMasterClient::Poll()
{
  int rc = ClientBase::Step();

  if ( rc != GameTestClient2::Result::NO_SUCH_STAGE )
    return rc;

  if ( socTransport )
    socTransport->Poll();
  if ( devSocLobby )
    devSocLobby->step();

  switch( stage() )
  {
    case ESocialTestState::Start:
      MessageTrace( "Starting social test transport...." );
      if ( socConfig.gatewayUrl.empty() )
        socTransport = new TestSocialTransportRpc( getGateKeeper() );
      else
        socTransport = new HttpTransport( socConfig );
      setStage( ESocialTestState::WaitingSocTransport, 30 );
      break;

    case ESocialTestState::WaitingSocTransport:
      NI_ASSERT( socTransport, "" );
      if ( socTransport->IsReady() ) {
        MessageTrace( "Social test transport ready, acquiring dev-interface..." );
        devSocLobby = new rpc::IfaceRequester<socialLobby::RIDevSocLobby>;
        devSocLobby->init( getGateKeeper().Get(), socialLobby::serviceIds::Service, socialLobby::serviceIds::DevEntrance );
        setStage( ESocialTestState::WaitingDevSLPtr, 30.0 );
      }
      break;

    case ESocialTestState::WaitingDevSLPtr:
      NI_ASSERT( devSocLobby, "" );
      if ( devSocLobby->isopen() ) {
        MessageTrace( "Got dev social lobby pointer, ready to spam!" );
        setStage( ESocialTestState::Working );
      }
      break;

    case ESocialTestState::Working:
      if ( !socTransport->IsReady() || !devSocLobby->isopen() ) {
        ErrorTrace( "Lost connection to lobby!" );
        setLastResult( GameTestClient2::Result::FAIL );
        exit( true );
        break;
      }
      PollSocClients();
      SpawnClients();
      PollServerStatus();
      break;

    default:
      break;
  }

  setLastResult( rc );
  return rc;
}



void SocialMasterClient::PollSocClients()
{
  for ( TSocClients::iterator it = clients.begin(); it != clients.end(); )
  {
    SocialClient * cl = *it;

    cl->Poll();

    for ( SocialClient::StatesTiming::const_iterator logIt = cl->StatesTimingLog().begin(); logIt != cl->StatesTimingLog().end(); ++logIt ) {
      StateTimingSlot & slot = statesTimingStatistics[logIt->state];
      slot.total.Count( logIt->timing );
      slot.last.Count( logIt->timing );
    }
    cl->ClearStatesTimingLog();

    if ( ESocClSt::Terminal( cl->State() ) ) {
      MessageTrace( "Social client removed: userId u%lld, state %s", cl->Request().uid, ESocClSt::ToString( cl->State() ) );

      if ( cl->State() == ESocClSt::Finished )
        ++counters.succeeded;
      else if ( cl->State() == ESocClSt::Failed )
        ++counters.failed;
      else if ( cl->State() == ESocClSt::TimedOut )
        ++counters.timedOut;

      RecycleRequest( cl->Request() );
      it = clients.erase( it );
    }
    else
    {
      if ( cl->State() == ESocClSt::PreparedToGame )
        readyForPvX.push_back( cl );

      ++it;
    }
  }
}



StrongMT<SocialClient> SocialMasterClient::PopToPvx()
{
  if ( readyForPvX.empty() )
    return 0;

  StrongMT<SocialClient> result = readyForPvX.front();
  readyForPvX.pop_front();
  return result;
}



void SocialMasterClient::DumpStatistics()
{
  int totalServed = counters.succeeded + counters.failed + counters.timedOut;
  double succPerc = totalServed ? ( 100.0 * (float)counters.succeeded / (float)totalServed ) : 0.0;
  LOG_M( GameTestClient::StatusChannel ).Trace( "Social clients: %u spawned, %u succeeded (%.2f%%), %u failed, %u timed out", counters.totalSpawned, counters.succeeded, succPerc, counters.failed, counters.timedOut );
}



void SocialMasterClient::DumpStates()
{
  map<ESocClSt::Enum, int> histo;
  for ( TSocClients::iterator it = clients.begin(); it != clients.end(); ++it )
    histo[(*it)->State()]++;

  LOG_M( GameTestClient::StatusChannel ).Trace( "Social clients states:" );
  for ( map<ESocClSt::Enum, int>::iterator it = histo.begin(); it != histo.end(); ++it )
    LOG_M( GameTestClient::StatusChannel ).Trace( "%s: %d", ESocClSt::ToString( it->first ), (int)it->second );
}



void SocialMasterClient::DumpStatesStatistics()
{
  LOG_M( GameTestClient::StatusChannel ).Trace( "Social clients states  statistics:" );

  for ( StatesTimingStatistics::iterator it = statesTimingStatistics.begin(); it != statesTimingStatistics.end(); ++it ) {
    LOG_M( GameTestClient::StatusChannel ).Trace( "%s: total %i, last %i", ESocClSt::ToString( it->first ), it->second.total, it->second.last );
    it->second.last.Reset();
  }
}



void SocialMasterClient::AppendStatesDebugText( string & _dest )
{
  int totalServed = counters.succeeded + counters.failed + counters.timedOut;
  double succPerc = totalServed ? ( 100.0 * (float)counters.succeeded / (float)totalServed ) : 0.0;

  _dest += NI_STRFMT( ", success: %.2f%% (%u out of %u)", succPerc, counters.succeeded, totalServed );
}



void SocialMasterClient::SpawnClients()
{
  timer::Time t = timer::Now();

  while ( true ) {
    if ( clients.size() >= clientsCount )
      break;
    if ( t <= nextClientSpawn )
      break;

    if ( !SpawnClient() )
      break;
  }
}



bool SocialMasterClient::SpawnClient()
{
  socialLobby::SMatchmakingRequest req;

  if ( !GetNewClientData( req ) )
    return false;

  clients.push_back( new SocialClient( socConfig, socTransport, req ) );

  MessageTrace( "Social client created: uid u%lld, userId pu%d, partyId p%d, map %s, faction %s, hero '%s', sex %s", req.uid, req.userIdPvx, req.partyId,
                            req.map,
                            lobby::ETeam::ToString( req.faction ), req.heroId.c_str(), lobby::ESex::ToString( req.zzimaSex ) );

  nextClientSpawn += 1.0 / socConfig.spawnRate;
  ++counters.totalSpawned;
  return true;
}



bool SocialMasterClient::GetNewClientData( socialLobby::SMatchmakingRequest & data )
{
  if ( !spawningParty ) {
    spawningParty = GetNewParty();
    spawningPartyCounter = 0;
  }

  if ( !spawningParty )
    return false;

  if ( !spawningParty->ready )
  {
    int ready = 0;
    for ( int i = 0; i < spawningParty->members.size(); ++i )
    {
      socialLobby::SMatchmakingRequest & memb = spawningParty->members[i];
      if ( !memb.uid )
      {
        socialLobby::TUId uid = GetNextUid();
        if ( !uid )
          return false;
        SetupUid( memb, uid );
      }
      ++ready;
    }

    if ( ready < spawningParty->members.size() )
      return false;

    if ( spawningParty->members.size() > 1 ) {
      vector<socialLobby::TUId> partyLineup;
      partyLineup.reserve( spawningParty->members.size() );
      for ( int i = 0; i < spawningParty->members.size(); ++i )
        partyLineup.push_back( spawningParty->members[i].userIdPvx );
      for ( int i = 0; i < spawningParty->members.size(); ++i )
        spawningParty->members[i].partyLineup = partyLineup;
    }

    spawningParty->ready = true;
  }

  NI_VERIFY( spawningPartyCounter < spawningParty->members.size(), "", spawningParty = 0; return false );

  data = spawningParty->members[spawningPartyCounter];
  ++spawningPartyCounter;

  if ( spawningPartyCounter >= spawningParty->members.size() )
    spawningParty = 0;

  return true;
}


//template <class T>
//inline const T & Roll

Strong<SocialMasterClient::SSpawnedParty> SocialMasterClient::GetNewParty()
{
  if ( !requestsRecycle.empty() )
  {
    Strong<SSpawnedParty> party = requestsRecycle.front();
    requestsRecycle.pop_front();
    return party;
  }

  int partySize = 1;
  if ( rnd.Roll( socConfig.partyFrequency ) )
    partySize = rnd.Next( socConfig.minPartySize, socConfig.maxPartySize );

  socialLobby::TPartyId partyId = 0;
  if ( partySize > 1 )
  {
    partyId = (socialLobby::TPartyId)GetNextUid();
    if ( !partyId )
      return 0;
  }

  Strong<SSpawnedParty> party = new SSpawnedParty;

  lobby::ETeam::Enum faction = teamSwitch;
  teamSwitch = lobby::ETeam::Invert( teamSwitch );

  party->members.resize( partySize );
  for ( int i = 0; i < partySize; ++i )
  {
    static const char * heroTable[] = { 
      "rockman",
      "mowgly",
      "ratcatcher",
      "witchdoctor",
      "highlander",
      "frogenglut",
      "faceless",
      "prince",
      "healer",
      "firefox",
      "assassin",
      "marine",
      "naga",
      "night",
      "warlord" };
    static const int heroesCount = sizeof( heroTable ) / sizeof(char *);

    socialLobby::SMatchmakingRequest & req = party->members[i];

    req.map = socConfig.map;
    req.faction = faction;
    req.heroId = heroTable[ rnd.Next( heroesCount ) ];
    req.zzimaSex = rnd.Roll( 80.f ) ? lobby::ESex::Male : lobby::ESex::Female;

    int basketRoll = rnd.Next( 0, 100 );
    if ( basketRoll < 10 ) {
      req.basket = mmaking::EBasket::Newbie;
      req.playerRating = rnd.Next( 1000, 1300 );
      req.heroRating = rnd.Next( 1000, 1300 );
      req.force = rnd.NextF( 100.0f, 120.0f );
      req.fameLevel = rnd.Next( 1, 10 );
      req.totalWins = rnd.Next( 1, 10 );
    }
    else //if ( basketRoll < 80 ) {
    {
      req.basket = mmaking::EBasket::Normal;
      req.playerRating = rnd.Next( 1200, 2100 );
      req.heroRating = rnd.Next( 1200, 2100 );
      req.force = rnd.NextF( 115.0f, 149.9f );
      req.fameLevel = rnd.Next( 5, 31 );
      req.totalWins = rnd.Next( 10, 500 );
    }
    /*else
    {
      req.basket = mmaking::EBasket::Guard;
      req.playerRating = rnd.Next( 1400, 2100 );
      req.guardRating = req.playerRating + rnd.Next( -200, +200 );
      req.heroRating = rnd.Next( 1400, 2100 );
      req.force = rnd.NextF( 150.0f, 170.0f );
      req.fameLevel = rnd.Next( 20, 31 );
      req.totalWins = rnd.Next( 100, 1000 );
    }*/

    req.clientRevision = 101;
    req.geoInfo.locale = rnd.RollFromContainer( socConfig.botLocales );
    for ( int i = 0; i < socConfig.botLocations.size(); ++i )
      req.geoInfo.pings.push_back( mmaking::SLocationPing( socConfig.botLocations[i].c_str(), rnd.Next( 20, 200 ) ) );
    req.partyId = partyId;
    // req.partyLineup and user id related fields will be filled later...
  }

  return party;
}



void SocialMasterClient::RecycleRequest( const socialLobby::SMatchmakingRequest & req )
{
  if ( !req.partyId || req.partyLineup.empty() )
  {
    NI_ASSERT( !req.partyId && req.partyLineup.empty(), "" );
    requestsRecycle.push_back( new SSpawnedParty( req ) );
    return;
  }

  const socialLobby::TPartyId key = req.partyId;
  Strong<SRecycledParty> party;
  TPartyRecycle::iterator it = partyRecycleCollector.find( key );
  if ( it != partyRecycleCollector.end() )
  {
    party = it->second;
    NI_ASSERT( !party->members.empty(), "" );
    NI_VERIFY( party->members[0].partyId == req.partyId, "", return );
    party->members.push_back( req );
    party->lastUpdate = timer::Now();
  }
  else
  {
    party = new SRecycledParty( req );
    partyRecycleCollector[ key ] = party;
  }

  if ( party->members.size() == party->size )
  {
    partyRecycleCollector.erase( key );

    Strong<SSpawnedParty> newParty = new SSpawnedParty;
    newParty->members = party->members;
    for ( int i = 0; i < newParty->members.size(); ++i )
      CleanupUid( newParty->members[i] );
    requestsRecycle.push_back( newParty );
  }
}



socialLobby::TUId SocialMasterClient::GetNextUid()
{
  socialLobby::TUId range = uidRange.to - uidRange.from;

  if ( currentUIdRangeIndex >= range )
  {
    if ( !userIdRangeRequested )
      if ( devSocLobby && devSocLobby->isopen() ) {
        MessageTrace( "Acquiring another user id range (%d) from server...", clientsCount );
        devSocLobby->iface()->AcquireUIdRange( clientsCount, this, &SocialMasterClient::OnUIdRangeArrival );
        userIdRangeRequested = true;
      }
    return 0;
  }

  return uidRange.from + currentUIdRangeIndex++;
}




void SocialMasterClient::SetupUid( socialLobby::SMatchmakingRequest & data, socialLobby::TUId uid )
{
  data.uid = uid;
  data.userIdPvx = 100500 + uid;
  data.login = NStr::StrFmt( "user%lld", uid );
  data.nickname = NStr::StrFmtW( L"Player %lld", uid );
  data.sessionContextId = NStr::StrFmt( "mmid_%lld_%d", uid, nextSessionContextId++ );
}



void SocialMasterClient::CleanupUid( socialLobby::SMatchmakingRequest & data )
{
  data.uid = 0;
  data.userIdPvx = 0;
  data.login.clear();;
  data.nickname.clear();
  data.sessionContextId.clear();
  data.partyLineup.clear();
}



void SocialMasterClient::OnUIdRangeArrival( socialLobby::SDevUidRange range )
{
  MessageTrace( "Arrived userId range [%lld, %lld]", range.from, range.to );

  NI_ASSERT( range.to > range.from, "Arrived wrong userId range" );

  uidRange = range;
  currentUIdRangeIndex = 0;
  userIdRangeRequested = false;
}



void SocialMasterClient::PollServerStatus()
{
  timer::Time t = timer::Now();

  if ( t < nextServerStatusRequest )
    return;
  nextServerStatusRequest = t + 3.0;

  socTransport->RequestServerStatus( this );
}



void SocialMasterClient::OnServerStatus( const socialLobby::SServerStatus & status )
{
  MessageTrace( "Got server_status: %.1f / %.1f / %.1f\n%s", status.acceptTimeout, status.averageMmTime, status.reconnectTimeout, status.pvpMmDebugStatus );
}

} // namespace GtcSocial

