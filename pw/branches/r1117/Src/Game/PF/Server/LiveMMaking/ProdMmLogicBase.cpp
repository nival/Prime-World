#include "stdafx.h"
#include "ProdMmLogicBase.h"
#include "MMakingLog.h"
#include "MMakingGameRequest.h"
#include "MMakingUniStat.h"
#include "Db/DBServer.auto.h"
#include "System/InlineProfiler.h"
#include "HeroesTable.h"
#include "MmQueueIterator.h"


namespace mmaking
{


StrongMT<mmaking::IHeroesTable> ProdLogicBase::FillHeroesTable( MMConfig * _cfg, const NDb::HeroesDB * dbHeroes )
{
  vector<string> disabled;
  NStr::SplitString( _cfg->disabledHeroes, &disabled, ' ' );

  vector<string> disabledBotSkins;
  NStr::SplitString( _cfg->disabledBotSkins, &disabledBotSkins, ' ' );

  StrongMT<mmaking::HeroesTable> heroes = new mmaking::HeroesTable;

  for ( int i = 0; i < dbHeroes->heroes.size(); ++i )
  {
    NDb::Ptr<NDb::Hero> dbHero = dbHeroes->heroes[i];
    NI_VERIFY( dbHero, "Null hero in data", continue );

    if ( !dbHero->legal )
      continue;

    if ( disabled.find( dbHero->id ) != disabled.end() )
      continue;

    SHeroDescription descr;
    descr.id = dbHero->id;
    descr.sex = ( dbHero->gender == NDb::GENDER_FEMALE ) ? lobby::ESex::Female : lobby::ESex::Male;

    switch ( dbHero->heroRace ) {
      case NDb::HERORACES_A:  descr.faction = lobby::ETeam::Team1; break;
      case NDb::HERORACES_B:  descr.faction = lobby::ETeam::Team2; break;
    }

    switch ( dbHero->botRollMode )
    {
      case NDb::BOTROLLMODE_ENABLED:          descr.botCanBe = descr.botCanBeAnEnemy = true; break;
      case NDb::BOTROLLMODE_DISABLEDASENEMY:  descr.botCanBe = true; descr.botCanBeAnEnemy = false; break;
      default:
      case NDb::BOTROLLMODE_DISABLED:         descr.botCanBe = descr.botCanBeAnEnemy = false; 
    }

    NI_VERIFY( dbHero->classEfficiency.size() == HeroClassesNumber + 1, "", continue );
    for ( int i = 1; i < dbHero->classEfficiency.size(); ++i )
      descr.classEfficiency.classes[i - 1] = (int)( 100.0f * dbHero->classEfficiency[i] + 0.5f );

    for ( int j = 0; j < dbHero->heroSkins.size(); ++j )
    {
      NI_VERIFY( dbHero->heroSkins[j], "", continue );
      const NDb::HeroSkin * skin = dbHero->heroSkins[j];
      if ( !skin->legal || !skin->botRoll )
        continue;

      if ( disabledBotSkins.find( skin->persistentId ) != disabledBotSkins.end() )
        continue;

      SHeroSkinDescription skinDescr;
      skinDescr.id = skin->persistentId;
      switch ( skin->heroRace ) {
        case NDb::HERORACES_A:  skinDescr.faction = lobby::ETeam::Team1; break;
        case NDb::HERORACES_B:  skinDescr.faction = lobby::ETeam::Team2; break;
      }

      if ( descr.faction != lobby::ETeam::None )
        NI_VERIFY( descr.faction == skinDescr.faction, NI_STRFMT( "Wrong hero skin faction. skin=%s", skin->persistentId ), continue );

      descr.botSkins.push_back( skinDescr );
    }

    heroes->Add( descr );
  }

  //второй прогон, чтобы заполнить списки с shortId антогонистов 
  for ( int i = 0; i < dbHeroes->heroes.size(); ++i )
  {
    NDb::Ptr<NDb::Hero> dbHero = dbHeroes->heroes[i];
    NI_VERIFY( dbHero, "Null hero in data", continue );
    
    if ( !dbHero->legal )
      continue;
    
    if ( disabled.find( dbHero->id ) != disabled.end() )
      continue;

    SHeroDescription* desc = heroes->FindDescr(dbHero->id);
    if (!desc)
      continue;

    for ( vector<string>::const_iterator it = dbHero->mmakingAntagonists.begin(); 
      it != dbHero->mmakingAntagonists.end(); ++it )
    {
      const SHeroDescription* antogonistDesc = heroes->FindDescr(*it);
      if (!antogonistDesc)
        continue;

      desc->antagonists.push_back( antogonistDesc->shortId );
    }
  }

  return heroes.Get();
}





class ProdLogicThreadJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( ProdLogicThreadJob, threading::IThreadJob, BaseObjectMT );

public:
  ProdLogicThreadJob( ProdLogicBase * l, unsigned _sleepMs ) :
  logic( l ),
  sleepMs( _sleepMs )
  {}

  ~ProdLogicThreadJob()
  {
    logic = NULL;
  }

  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    StrongMT<Loger> loger = logic->GetLoger();

    if ( loger )
      loger->Log( ELogLevel::Critical, "Matchmaking thread started..." );

    while( true )
    {
      if ( !isRunning )
        break;

      threading::Sleep( sleepMs );

      logic->ParallelPoll( isRunning );
    }

    if ( loger )
      loger->Log( ELogLevel::Critical, "Matchmaking thread stopped..." );
  }

private:
  ProdLogicBase *   logic;
  unsigned          sleepMs;
};




ProdLogicBase::ProdLogicBase( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
BaseMMaking( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
m_externalTime( 0 ),
m_now( 0 ),
m_requestAdded( 0 ), m_requestServed( 0 ),
m_lineLength1( 0 ), m_lineLength2( 0 ),
m_dataChanged( false ),
m_lastSmartDump( 0 ), m_lastFullDump( 0 ),
m_lastRequestsAdded( 0 ), m_lastRequestsServed( 0 )
{
  if ( _logSuffix )
    m_queueCsvDumper = new Loger( ( string( _logSuffix ) + ".csv" ).c_str(), "" );
  else
    m_queueCsvDumper = new Loger( _logSuffix, "" );
  m_queueCsvDumper->EnableTimestampLogging( false );
  m_queueCsvDumper->EnableDebugOutput( false );

  m_jsonLogger = new Loger( _logSuffix ? ( ( string( _logSuffix ) + ".json" ).c_str() ) : 0, "" );
  m_jsonLogger->SetLogLevel( (ELogLevel::Enum)_cfg->logLevel );
  m_jsonLogger->EnableTimestampLogging( false );
  m_jsonLogger->EnableDebugOutput( false );

  m_uniStats = new UniStatLoger( _logSuffix );
}



ProdLogicBase::~ProdLogicBase()
{
  //We have to kill thread first, then all ze fields
  StopParallelThread();
}


void ProdLogicBase::StopParallelThread()
{
  if (m_thread) 
  {
    m_thread->AsyncStop();
    m_thread->Wait(1000);
  }

  m_thread = 0;
}

void ProdLogicBase::LaunchParallelThread()
{
  m_thread = new threading::JobThread( new ProdLogicThreadJob( this, m_config->sleepMs), "Matchmaking" );
}



void ProdLogicBase::SetTime( timer::Time _simulationTime )
{
  threading::MutexLock lock( m_incomingMutex );
  m_externalTime = _simulationTime;
}



void ProdLogicBase::AddGroupRequest( TRequestUId _requestUId, const SRequestCommonData & _commonData, const vector<SRequestMember> & _members, timer::Time _waitTime, IMMakingLogicCallback * _callback )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_VERIFY( !_members.empty(), "", return );
  NI_ASSERT( ( _commonData.team == lobby::ETeam::Team1 ) || ( _commonData.team == lobby::ETeam::Team2 ), "" );

  //HACK: Мы передаем waitTime вместо startTime; В PickUpNewRequests() будет вычислено 'startTime'
  StrongMT<MmRequest> req = new MmRequest( m_settings, _requestUId, 0, _commonData );
  if ( !req->Init( _members, m_heroes, m_ranks, m_locales, m_locations, m_loger ) ) {
    if ( _callback ) _callback->MmResultAddRequest( _requestUId, false );
    return;
  }

  string dump = req->FormatAll();
  string dumpJson = req->FormatAllJson();
  {
    threading::MutexLock lock( m_incomingMutex );
    m_incoming.push_back( SIncomingRequest<TRequestUId, MmRequest>( _requestUId, req, _callback ) );
    req->SetStartTime( m_now - _waitTime );
    req = 0; //'req' is under parallel thread's control
    ++m_requestAdded;
  }

  m_loger->Log( ELogLevel::Normal, "Request queued: id %d (wait %.1f), %s", _requestUId, _waitTime, dump.c_str() );

  string jsonTime;
  FormatTimeToJson( jsonTime );
  m_jsonLogger->Log( ELogLevel::Normal, "{ \"RequestQueued\": { \"time\": %s, \"id\": %d, \"wait\": %.1f, %s } }", jsonTime.c_str(), _requestUId, _waitTime, dumpJson.c_str() );
}



void ProdLogicBase::RemoveRequest( TRequestUId _requestUId, IMMakingLogicCallback * _callback )
{
  m_loger->Log( ELogLevel::Verbose, "Removing request: %d", _requestUId );

  threading::MutexLock lock( m_incomingMutex );
  m_incoming.push_back(  SIncomingRequest<TRequestUId, MmRequest>( _requestUId, 0, _callback ) );
}



bool ProdLogicBase::PopGame( SGame & _result )
{
  {
    threading::MutexLock lock( m_outcomeMutex );
    if ( m_outcome.empty() )
      return false;
    _result.Swap( m_outcome.front() );
    m_outcome.pop_front();
  }

  LogGame( ELogLevel::Verbose, _result, "Game popped: " );

  return true;
}



void ProdLogicBase::AddGameForReconnect( lobby::TGameId _gameId, const SGame & _gameData, IMMakingLogicCallback * _callback )
{
  StrongMT<GameRequest> gameReq = new GameRequest( _gameId );

  if ( !gameReq->Init( m_settings, m_teamSize, _gameData, m_heroes, m_ranks, m_locales, m_locations, m_loger ) ) {
    if ( _callback ) _callback->MmResultAddReconnectGame( _gameId, false );
    return;
  }

  {
    threading::MutexLock lock( m_incomingMutex );
    m_icomingGameRequests.push_back( SIncomingRequest<lobby::TGameId, GameRequest>( _gameId, gameReq, _callback ) );
    gameReq->SetStartTime( m_now );
    gameReq = 0;
    ++m_requestAdded;
  }

  string tmp;
  FormatGame( tmp, _gameData );

  m_loger->Log( ELogLevel::Normal, "Game request queued: id %d, %s", _gameId, tmp.c_str() );
}



void ProdLogicBase::RemoveGame( lobby::TGameId _gameId, IMMakingLogicCallback * _callback )
{
  m_loger->Log( ELogLevel::Verbose, "Removing game request: %d", _gameId );

  threading::MutexLock lock( m_incomingMutex );
  m_icomingGameRequests.push_back( SIncomingRequest<lobby::TGameId, GameRequest>( _gameId, 0, _callback ) );
}



bool ProdLogicBase::PopReconnectSlot( SReconnectSlot & _slot )
{
  {
    threading::MutexLock lock( m_outcomeMutex );
    if ( m_gameRequestsResults.empty() )
      return false;
    _slot = m_gameRequestsResults.front();
    m_gameRequestsResults.pop_front();
  }

  m_loger->Log( ELogLevel::Normal, "Reconnect pair popped %d %d", _slot.gameId, _slot.userRequestId );
  return true;
}



string ProdLogicBase::GetDebugStatus()
{
  threading::MutexLock lock( m_debugStatusMutex );
  return m_debugStatus;
}



void ProdLogicBase::GetLineStatistics( unsigned & team1, unsigned & team2 )
{
  threading::MutexLock lock( m_outcomeMutex );
  team1 = m_lineLength1;
  team2 = m_lineLength2;
}



void ProdLogicBase::PickUpNewRequests()
{
  NI_PROFILE_FUNCTION;

  while ( !m_incoming.empty() )
  {
    TIncomingRequests::iterator it = m_incoming.begin();

    TRequestUId reqId = it->reqId;
    StrongMT<MmRequest> newReq = it->req;
    StrongMT<IMMakingLogicCallback> callback = it->cb.Lock();

    if ( newReq.Valid() )
      PickUpNewRequest( newReq, callback );
    else
      RemoveRemovedRequest( reqId, callback );

    it = m_incoming.erase( it );
  }
}



void ProdLogicBase::PickUpNewRequest( MmRequest * newReq, IMMakingLogicCallback * callback )
{
  std::pair< TRequestMap::iterator, bool > resultByReqId =
      m_requests.insert( TRequestMap::value_type( newReq->RequestId(), newReq ) );
  if ( !resultByReqId.second )
  {
    if ( callback ) callback->MmResultAddRequest( newReq->RequestId(), false );

    StrongMT<MmRequest> oldReq = resultByReqId.first->second;
    m_loger->Log( ELogLevel::Critical, "Duplicate request id %d (new user ids %s, existing user ids %s)", newReq->RequestId(),
                newReq->FormatAllMmIds().c_str(), oldReq->FormatAllMmIds().c_str() );
    NI_ALWAYS_ASSERT( "Duplicate request id" );
    return;
  }

  if ( callback ) callback->MmResultAddRequest( newReq->RequestId(), true );
  m_loger->Log( ELogLevel::Verbose, "Request added: id %d, userIds %s", newReq->RequestId(), newReq->FormatAllMmIds().c_str() );

  OnRequestAdded( newReq );

  m_dataChanged = true;
}



void ProdLogicBase::RemoveRemovedRequest( TRequestUId requestId, IMMakingLogicCallback * callback )
{
  if ( !DeleteRequest( requestId ) ) {
    if ( callback )
      callback->MmResultRemoveRequest( requestId, false );
    return;
  }

  if ( callback )
    callback->MmResultRemoveRequest( requestId, true );
  m_loger->Log( ELogLevel::Normal, "Request removed: %d", requestId );

  string jsonTime;
  FormatTimeToJson( jsonTime );
  m_jsonLogger->Log( ELogLevel::Normal, "{ \"RequestRemoved\": { \"time\": %s, \"id\": %d } }", jsonTime.c_str(), requestId );
}



void ProdLogicBase::PickUpNewGameRequests()
{
  NI_PROFILE_FUNCTION;

  while ( !m_icomingGameRequests.empty() )
  {
    TIncomingGameRequests::iterator it = m_icomingGameRequests.begin();

    lobby::TGameId gameId = it->reqId;
    StrongMT<GameRequest> newGReq = it->req;
    StrongMT<IMMakingLogicCallback> callback = it->cb.Lock();

    if ( newGReq )
      PickUpNewGameRequest( newGReq, callback );
    else
      RemoveRemovedGameRequest( gameId, callback );

    it = m_icomingGameRequests.erase( it );
  }
}



void ProdLogicBase::PickUpNewGameRequest( GameRequest * newReq, IMMakingLogicCallback * callback )
{
  std::pair< TGameRequestMap::iterator, bool > insertResult =
      m_gameRequests.insert( TGameRequestMap::value_type( newReq->GameId(), newReq ) );
  if ( !insertResult.second )
  {
    if ( callback ) callback->MmResultAddReconnectGame( newReq->GameId(), false );

    StrongMT<GameRequest> oldGReq = insertResult.first->second;
    m_loger->Log( ELogLevel::Critical, "Duplicate game request id %d", newReq->GameId() );
    NI_ALWAYS_ASSERT( "Duplicate game request id" );
    return;
  }

  if ( callback ) callback->MmResultAddReconnectGame( newReq->GameId(), true );
  m_loger->Log( ELogLevel::Verbose, "Game request added: id %d", newReq->GameId() );

  m_dataChanged = true;
}



void ProdLogicBase::RemoveRemovedGameRequest( lobby::TGameId gameId, IMMakingLogicCallback * callback )
{
  TGameRequestMap::iterator it = m_gameRequests.find( gameId );
  if( it == m_gameRequests.end() ) {
    m_loger->Log( ELogLevel::Critical, "Unknown game request to remove: %d", gameId );
    if ( callback ) callback->MmResultRemoveReconnectGame( gameId, false );
    return;
  }
  m_gameRequests.erase( it );

  if ( callback ) callback->MmResultRemoveReconnectGame( gameId, true );
  m_loger->Log( ELogLevel::Normal, "Game request removed: %d", gameId );

  m_dataChanged = true;
}



int ProdLogicBase::GatherRevisionsInfo( TClientRevisions & revisions )
{
  NI_PROFILE_FUNCTION;

  revisions.clear();
  {
    for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end() ; ++it )
    {
      MmRequest * req = it->second;
      int rev = req->CommonData().clientRevision;
      revisions[rev] += req->Size();
    }
  }

  int mostPopularCount = 0;
  int mostPopularRev = 0;
  for ( TClientRevisions::iterator it = revisions.begin(); it != revisions.end(); ++it )
  {
    const int rev = it->first, count = it->second;
    if ( count > mostPopularCount )
    {
      mostPopularCount = count;
      mostPopularRev = rev;
    }
  }

  return mostPopularRev;
}



void ProdLogicBase::GatherCcuInfo()
{
  NI_PROFILE_FUNCTION;

  unsigned count[2] = { 0, 0 };
  unsigned newb[2] = { 0, 0 };
  unsigned leavers[2] = { 0, 0 };
  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end(); ++it ) {
    StrongMT<MmRequest> req = it->second;
    int tidx = lobby::ETeam::Index( req->CommonData().team );
    ++count[tidx];
    if ( req->Basket() == EBasket::Newbie )
      ++newb[tidx];
    if ( req->Basket() == EBasket::Leaver )
      ++leavers[tidx];

  }

  m_uniStats->AddStat( "TotalRequests", m_requests.size() );
  m_uniStats->AddStat( "Team1Requests", count[0] );
  m_uniStats->AddStat( "Team2Requests", count[1] );
  m_uniStats->AddStat( "Newbies1", newb[0] );
  m_uniStats->AddStat( "Newbies2", newb[1] );
  m_uniStats->AddStat( "Leavers1", leavers[0] );
  m_uniStats->AddStat( "Leavers2", leavers[1] );


  threading::MutexLock lock( m_outcomeMutex );
  m_lineLength1 = count[0];
  m_lineLength2 = count[1];
}



void ProdLogicBase::ClearInUse()
{
  NI_PROFILE_FUNCTION;

  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end() ; ++it )
    it->second->Use( false );
}



bool ProdLogicBase::CheckAndSetupLocalePair( GeolocationConstraints & geo, TGeoIndex locale1, TGeoIndex locale2 )
{
  geo.sidesLocale[0] = locale1;
  geo.sidesLocale[1] = locale2;

  if ( locale1 == locale2 )
    return true;

  if ( !m_config->international )
    return false;

  if ( m_locales.Isolated( locale1 ) || m_locales.Isolated( locale2 ) )
    return false;

  if ( m_locales.IsDonor( locale1 ) && !m_locales.IsDonor( locale2 ) )
  {
    geo.multipleLocales = true;
    geo.donorSide = 0;
    geo.recipientSide = 1;
  }
  else if ( !m_locales.IsDonor( locale1 ) && m_locales.IsDonor( locale2 ) )
  {
    geo.multipleLocales = true;
    geo.donorSide = 1;
    geo.recipientSide = 0;
  }
  else
    return false;

  return true;
}



bool ProdLogicBase::CheckHeroesLimit( const THeroCounter & heroCounter, const MmRequest * req, EBasket::Enum basket ) const
{
  NI_PROFILE_FUNCTION;

  int limit = 0;
  switch ( basket )
  {
    case EBasket::Newbie:
      limit = m_settings->identicalNoobHeroesSampleLimit;
      break;

    case EBasket::Leaver:
      limit = m_settings->identicalHeroesSampleLimit;
      break;

    default:
    case EBasket::Normal:
      limit = m_settings->identicalHeroesSampleLimit;
      break;
  }

  // подсчитываем количество одинаковых героев в пати из запроса
  THeroCounter partyHeroesCounter;
  for ( int i = 0; i < req->Size(); ++i )
    partyHeroesCounter[req->Member( i ).shortHeroId] += 1;

  // теперь проверим можно ли добавить всю пати в семпл 
  for ( THeroCounter::const_iterator it = partyHeroesCounter.begin(); it != partyHeroesCounter.end(); ++it )
  {
    THeroShortId heroId = it->first;
    int countInParty = it->second;

    if ( countInParty > limit )
        return false;

    THeroCounter::const_iterator check = heroCounter.find( heroId );
    if ( check != heroCounter.end() )
      if ( check->second + countInParty > limit )
        return false;
  }

  return true;
}



void ProdLogicBase::CountHeroes( THeroCounter & heroCounter, const MmRequest * req, const IHeroesTable* heroes )
{
  NI_PROFILE_HEAVY_FUNCTION;

  for ( int i = 0; i < req->Size(); ++i )
  {
    const SRequestMemberEx& reqMember = req->Member(i);
    const SHeroDescription* reqMemberDesc = heroes->FindDescr(reqMember.shortHeroId);

    /* при добавлении новых героев в собирающуюся команду будем подсчитывать и антогонистов,
     * чтобы при следующей попытке добавить в  команду героя, который в скипке антогонистов 
     * у кого-то из тех, кто уже добавлен, она (попытка) фейлилась 
     */
    for (vector<THeroShortId>::const_iterator it = reqMemberDesc->antagonists.begin(); 
      it != reqMemberDesc->antagonists.end(); ++it )
    {
      //int  antogonistShortId = m_heroes->FindDescr( *it )->shortId;
      heroCounter[ *it /*antogonistShortId*/ ] += 1;
    }
    heroCounter[reqMember.shortHeroId] += 1;
  }
}



void ProdLogicBase::PushResultingGame( const MMakingDraftGame & draft, EDebugGameType::Enum debugGameType )
{
  NI_PROFILE_FUNCTION;

  SGame game;
  draft.ProduceResult( game, m_mapType, m_mapId, m_now );
  game.debugGameType = debugGameType;

  m_requestServed += draft.GameSize();

  LogGame( ELogLevel::Normal, game, "Pushing game: " );
  LogGameJson( ELogLevel::Normal, game );
  {
    threading::MutexLock lock( m_outcomeMutex );
    m_outcome.push_back( SGame() );
    m_outcome.back().Swap( game );
  }
}



bool ProdLogicBase::DeleteRequest( TRequestUId requestId )
{
  TRequestMap::iterator it = m_requests.find( requestId );
  NI_VERIFY( it != m_requests.end(), NI_STRFMT( "Unknown request to remove: %d", requestId ), return false );

  StrongMT<MmRequest> req = it->second;
  OnRequestDeletion( req );

  m_requests.erase( it );

  m_dataChanged = true;

  return true;
}



void ProdLogicBase::ParallelPoll( volatile bool & isRunning )
{
  NI_PROFILE_FUNCTION;

  PullReloadedConfig();

  unsigned requestAdded = 0;
  {
    threading::MutexLock lock( m_incomingMutex );
    m_now = m_externalTime;

    m_loger->Poll( m_now );
    m_jsonLogger->Poll( m_now );
    m_queueCsvDumper->Poll( m_now );

    PickUpNewRequests();
    PickUpNewGameRequests();
    requestAdded = m_requestAdded;
  }

  GatherCcuInfo();

  TClientRevisions clRev;
  int mostPopularRev = m_config->checkRevision ? GatherRevisionsInfo( clRev ) : -1;

  m_uniStats->Poll( m_now );

  SmartDump( requestAdded, clRev );
  FullDump();

  RunIteration( mostPopularRev, isRunning );
}



void ProdLogicBase::WriteFullDumpHat()
{
  m_queueCsvDumper->Log( ELogLevel::Normal, "UserId;ReqId;Wait;Faction;Maneuvers;Client Rev;Basket;Hero;Sex;Player rating;Hero rating;Force;Lord level;Lose streak;Wins;Locale;Pings");
}



void ProdLogicBase::WriteFullDumpRequest( MmRequest * req )
{
  const timer::Time wait = m_now - req->StartTime();
  for ( int i = 0; i < req->Size(); ++i ) {
    const mmaking::SRequestMemberEx & m = req->Member( i );
    m_queueCsvDumper->Log( ELogLevel::Normal, "%d;%d;%d;%s;%d;%s;%s;%s;%d;%d;%d;%d;%d;%d;%s;%s",
      m.mmId,
      req->RequestId(),
      (int)wait,
      lobby::ETeam::ToString( req->CommonData().team ),
      req->CommonData().clientRevision,
      mmaking::EBasket::ToString( m.basket ),
      m.heroId.c_str(),
      lobby::ESex::ToString( m.sex ),
      m.playerRating,
      m.heroRating,
      (int)( m.force * 10.0f ),
      m.fameLevel,
      m.loseStreak,
      m.totalWins,
      m.geoInfo.locale.c_str(),
      m.geoInfo.FmtPings().c_str()
      );
  }
}



void ProdLogicBase::FullDump( unsigned debugGameId )
{
  NI_PROFILE_FUNCTION;

  if ( !m_config->fullDumpLimit )
    return;

  if ( !debugGameId && ( m_now < m_lastFullDump + m_config->fullDumpPeriod ) )
    return;

  m_lastFullDump = m_now;

  m_queueCsvDumper->Log( ELogLevel::Normal, "Full queue dump. simulation_time=%.1f, dbg_id=%u", m_now, debugGameId );
  WriteFullDumpHat();

  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end() ; ++it )
    WriteFullDumpRequest( it->second );
}


struct SMmLineStats
{
  int           people;
  int           parties;
  int           ladies;
  int           gents;
  int           leaver;
  int           normal;

  timer::Time   wait;

  const static int MaxPaties = 5;
  int           partyHysto[MaxPaties];

  SMmLineStats() :
  people(0), parties(0), ladies(0), gents(0), wait(0), leaver(0), normal(0) 
  {
    for ( int j = 0; j < MaxPaties; ++j )
      partyHysto[j] = 0;
  }

  SMmLineStats( MmRequest * req, timer::Time now ) :
  people( req->Size() ),
  parties( 1 ),
  ladies( req->Ladies() ),
  gents( req->Gentlemen() ),
  wait( now - req->StartTime() ),
  leaver(0), normal(0)
  {
    for ( int j = 0; j < MaxPaties; ++j )
      partyHysto[j] = ( j == ( req->Size() - 1 ) ) ? 1 : 0;
    
    switch (req->Basket())
    {
    case EBasket::Leaver:
      leaver += req->Size();
      break;
    default:
      normal += req->Size();
    }  
  }

  void operator += ( const SMmLineStats & other ) {
    people += other.people;
    parties += other.parties;
    ladies += other.ladies;
    gents += other.gents;
    wait += other.wait;
    leaver += other.leaver;
    normal += other.normal;

    for ( int j = 0; j < MaxPaties; ++j )
      partyHysto[j] += other.partyHysto[j];
  }

  string Str() {
    string s;
    timer::Time avgWait = parties ? ( wait /= parties ) : 0;
    s = NI_STRFMT( "%d total, %d leaver, %d other basket,  %d males, %d females, %.1f avg wait, parties: ( ", ladies + gents, leaver, normal, gents, ladies, avgWait );
    for ( int j = 0; j < SMmLineStats::MaxPaties; ++j )
      s += NI_STRFMT( "%s%d:%d", ( j ? ", " : "" ), j + 1, partyHysto[j] );
    s += " )";
    return s;
  }
};


void ProdLogicBase::SmartDump( unsigned requestAdded, const TClientRevisions & clientRevisions )
{
  NI_PROFILE_FUNCTION;

  if ( !m_dataChanged || ( m_config->smartDumpTime <= 0 ) )
    return;
  if ( m_now < m_lastSmartDump + m_config->smartDumpTime )
    return;

  timer::Time dt = m_now - m_lastSmartDump;
  m_lastSmartDump = m_now;
  m_dataChanged = false;

  unsigned addedDelta = requestAdded - m_lastRequestsAdded;
  unsigned servedDelta = m_requestServed - m_lastRequestsServed;
  m_lastRequestsAdded = requestAdded;
  m_lastRequestsServed = m_requestServed;

  m_uniStats->AddStat( "NewRequests", addedDelta );

  SMmLineStats byTeam[2];
  std::map<int, SMmLineStats> byTeamByRank[2];
  

  for( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end(); ++it )
  {
    MmRequest * req = it->second;

    int teamIdx = lobby::ETeam::Index( req->CommonData().team );

    SMmLineStats st( req, m_now );
    byTeam[teamIdx] += st;

    byTeamByRank[teamIdx][req->RankIndex()] += st;
    
  }

  string debugMsg, msg;
  debugMsg.reserve( 512 );
  msg.reserve( 256 );

  msg = NI_STRFMT( "%u requests total (%d + %d), %u was added (%.1f per sec), %u was served (%.1f per sec)",
    (unsigned)m_requests.size(), byTeam[0].parties, byTeam[1].parties,
    addedDelta, addedDelta / dt, servedDelta, servedDelta / dt );
  m_loger->Log( ELogLevel::Normal, "Line statistics brief: %s", msg.c_str() );
  debugMsg += msg;
  debugMsg += "\n";
  msg.clear();

  for ( int ti = 0; ti < 2; ++ti )
  {
    m_loger->Log( ELogLevel::Normal, "Line statistics: Team%d Total: %s", ti + 1, byTeam[ti].Str().c_str() );
    debugMsg += msg;
    debugMsg += "\n";
    msg.clear();
  }

  for ( int ri = 0; ri < m_ranks->RanksNumber(); ++ri )
  {
    for ( int ti = 0; ti < 2; ++ti )
    {
      const RankDescription * rank = m_ranks->FindRankByIndex( ri );
      m_loger->Log( ELogLevel::Normal, "Line statistics: Team%d, %s: %s", ti + 1, rank->name.c_str(), byTeamByRank[ti][rank->index].Str().c_str() );
      debugMsg += msg;
      debugMsg += "\n";
      msg.clear();
    }
  }

  if ( clientRevisions.size() > 1 )
  {
    string revList;
    for ( TClientRevisions::const_iterator it = clientRevisions.begin(); it != clientRevisions.end(); ++it ) {
      if ( !revList.empty() ) revList += ", ";
      revList += NI_STRFMT( "%d (%d requests)", (int)it->first, (int)it->second ); }
    msg += NI_STRFMT( "Attention! Multiple client revisions in line: %s", revList.c_str() );
    m_loger->Log( ELogLevel::Normal, "%s", msg.c_str() );
    debugMsg += msg;
    debugMsg += "\n";
    msg.clear();
  }

  {
    threading::MutexLock lock( m_debugStatusMutex );
    m_debugStatus = debugMsg;
  }

  OnSmartDump();
}



void ProdLogicBase::FormatGameJson( string & _buffer, const SGame & _game )
{
  NI_PROFILE_FUNCTION;

  string jsonTime;
  FormatTimeToJson( jsonTime );
  _buffer = NI_STRFMT( "{ \"PushingGame\": { \"time\": %s, \"map_type\": %d, \"map\": \"%s\", \"basket\": %d, \"members\": [ ", jsonTime.c_str(), (int)_game.mapType, _game.mapId.c_str(), (int)_game.basket );

  vector<vector<string>> lines[2];

  bool first = true;
  for ( int i = 0; i < _game.humans.size(); ++i )
  {
    const SGameParty & party = _game.humans[i];

    for ( int j = 0; j < party.members.size(); ++j )
    {
      const SRequestMember & memb = party.members[j];

      if ( !first )
        _buffer += ", ";

      _buffer += "{";
      _buffer += NI_STRFMT( "\"userId\": %d, \"reqId\": %d, \"team\": %d, \"sex\": %d, \"hero\": \"%s\", \"basket\": %d, \"gRating\": %d, \"pRating\": %d, \"hRating\": %d, ", 
                              memb.mmId, party.requestUId, (int)party.common.team, (int)memb.sex, memb.heroId.c_str(), (int)memb.basket, memb.guardRating, memb.playerRating, memb.heroRating );
      _buffer += NI_STRFMT( "\"force\": %.1f, \"wait\": %.1f, \"loses\": %d, \"wins\": %d, \"fame\": %d, \"loc\": \"%s\", ", 
                              memb.force, party.waitTime, memb.loseStreak, memb.totalWins, memb.fameLevel, memb.geoInfo.locale );

      _buffer += "\"pings\":";
      MmRequest::FormatPingsIntoJson( _buffer, memb.geoInfo );

      _buffer += "}";

      first = false;
    }
  }
  _buffer += " ] } }";
}



void ProdLogicBase::LogGameJson( ELogLevel::Enum _lvl, const SGame & _game )
{
  NI_PROFILE_FUNCTION;

  string buf;
  buf.reserve( 4096 );

  FormatGameJson( buf, _game );

  m_jsonLogger->Log( _lvl, buf.c_str() );
}



void ProdLogicBase::FormatTimeToJson( string & buffer )
{
  timer::DecodedTime now;
  timer::UtcDecodedTime( now );

  char buf[128];
  sprintf_s( buf, "{\"day\":%u, \"mon\":%u, \"hour\":%u, \"min\":%u, \"sec\":%u, \"scalar\":%.1f}",
    (unsigned)now.wDay, (unsigned)now.wMonth, (unsigned)now.wHour, (unsigned)now.wMinute, (unsigned)now.wSecond, m_now );

  buffer = buf;
}



void ProdLogicBase::DebugEnumerateRequests( IDbgRequestsEnumerator * enumerator )
{
  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end() ; ++it )
    enumerator->EnumRequest( it->second );
}

} //namespace mmaking
