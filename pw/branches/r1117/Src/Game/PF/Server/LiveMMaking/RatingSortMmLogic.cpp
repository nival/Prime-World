#include "stdafx.h"
#include "RatingSortMmLogic.h"
#include "RatingSortMmWorker.h"
#include "Db/DBServer.auto.h"
#include "MMakingLog.h"
#include "MMakingUniStat.h"
#include "LiveMMakingConfigVars.h"
#include "RankTable.h"
#include "MmQueueIterator.h"
#include "System/InlineProfiler.h"


namespace mmaking
{

struct RatingSortMmLogic::SampleContext
{
  int           pop;
  int           teamPop[2];
  ELongWaitMode::Enum longWaitMode;
  int           minRating, maxRating;
  timer::Time   maxWaitTime;

  SampleContext() :
  pop( 0 ),
  longWaitMode( ELongWaitMode::None ),
  minRating( 0 ), maxRating( 0 ),
  maxWaitTime( 0 )
  {
    teamPop[0] = teamPop[1] = 0;
  }
};


struct RatingSortMmLogic::PresampleKey
{
  int               distance;
  StrongMT<MmRequest> request;
  timer::Time       effectiveWaitTime;
  bool              pingIsGood;
  bool              mandatory;

  PresampleKey( int dist, MmRequest * req, timer::Time _wait, bool _pingIsGood, bool _mandatory = false ) :
  distance( dist ), request( req ),
  effectiveWaitTime( _wait ),
  pingIsGood( _pingIsGood ),
  mandatory( _mandatory )
  {}

  bool operator < ( const PresampleKey & other ) const {
    if ( request->RequestId() == other.request->RequestId() )
      return false;
    if ( distance < other.distance ) return true;
    if ( distance > other.distance ) return false;
    return request->RequestId() < other.request->RequestId();
  }
};








RatingSortMmLogic::RatingSortMmLogic( const NDb::MapMMakingSettings * _settings, MMConfig * _cfg, IHeroesTable * _heroes, int _teamSize, NDb::EMapType _mapType, const char * _mapId, const char * _logSuffix ) :
ProdLogicBase( _settings, _cfg, _heroes, _teamSize, _mapType, _mapId, _logSuffix ),
m_workersNumber( (size_t)m_config->threads ),
m_simulationMode( false ),
m_nextBasePointIdx( 0 ),
m_proPlayerModeEndTime( -1 ), m_proPlayerModeStartTime( -1 ),
m_random( GetTickCount() ),
m_debugGameId( 1 )
{
  SetupBasePoints( m_workersNumber );

  //m_loger->EnableDebugOutput( false );

  m_statistics = new RatingSortStatistics( m_uniStats );
  m_worker = new RatingSortWorker( m_workersNumber );
}



RatingSortMmLogic::~RatingSortMmLogic()
{
  m_worker = 0;

  if ( m_thread ) {
    m_thread->AsyncStop();
    bool finished = m_thread->Wait( 10000 );
    NI_ASSERT( finished, "" );
    m_thread = 0;
  }
}


inline void SetupLinearScale( vector<int> & points, const NDb::MMakingScale & scale )
{
  points.reserve( 1 + ( scale.high - scale.low ) / scale.step );

  for ( int x = scale.low; x <= scale.high; x += scale.step )
    points.push_back( x );
}



void RatingSortMmLogic::SetupBasePoints( unsigned threadNumber )
{
  vector<int> R, F;
  SetupLinearScale( R, m_settings->ratingScale );
  SetupLinearScale( F, m_settings->forceScale );
  NI_VERIFY( !R.empty() && !F.empty(), "", return );

  NI_ASSERT( m_settings->proRatingThreshold <= m_settings->ratingScale.high, "'proRatingThreshold' should fit in rating base points range!" );

  typedef std::list<RatingSortBasePoint> BasePointsList;

  string bpDebug;
  BasePointsList srcPoints;
  for ( int fi = 0; fi < F.size(); ++fi )
    {
      for ( int ri = 0; ri < R.size(); ++ri )
      {
        srcPoints.push_back( RatingSortBasePoint( GeolocationConstraints(), ERatingSortBpType::Normal, EBasket::Undefined, (int)R[ri], (int)F[fi] ) );
        bpDebug += NI_STRFMT( "[r%d f%d] ", R[ri], F[fi] );
      }
    }
  m_loger->Log( ELogLevel::Normal, "Base points: %s", bpDebug.c_str() );

  BasePointsList shuffledPoints;
  ShuffleBasePoints( shuffledPoints, srcPoints, threadNumber );

  m_basePoints.clear();
  m_basePoints.reserve( shuffledPoints.size() );

  int newbiesCounterOffset = 0;
  int normalCounterOffset = 0;

  for ( BasePointsList::const_iterator it = shuffledPoints.begin(); it != shuffledPoints.end(); ++it )
    for ( TGeoIndex locale1 = m_locales.BeginIdx(); locale1 < m_locales.EndIdx(); ++locale1 )
      for ( TGeoIndex locale2 = m_locales.BeginIdx(); locale2 < m_locales.EndIdx(); ++locale2 )
      {
        GeolocationConstraints geo;
        if ( !CheckAndSetupLocalePair( geo, locale1, locale2 ) )
          continue;

        for ( TGeoIndex location = m_locations.BeginIdx(); location < m_locations.EndIdx(); ++location )
        {
          geo.location = location;

          if ( m_mapType != NDb::MAPTYPE_COOPERATIVE )
            m_basePoints.push_back( RatingSortBasePoint( geo, ERatingSortBpType::Normal, EBasket::Newbie, 0, 0, m_settings->noobBasePointsRepeatFactor, newbiesCounterOffset++ ) );

          m_basePoints.push_back( RatingSortBasePoint( geo, ERatingSortBpType::Normal, EBasket::Normal, it->rating, it->force, m_settings->normalBasePointsRepeatFactor, normalCounterOffset++ ) );
        }
      }

  for ( TGeoIndex locale1 = m_locales.BeginIdx(); locale1 < m_locales.EndIdx(); ++locale1 )
    for ( TGeoIndex locale2 = m_locales.BeginIdx(); locale2 < m_locales.EndIdx(); ++locale2 )
    {
      GeolocationConstraints geo;
      if ( !CheckAndSetupLocalePair( geo, locale1, locale2 ) )
        continue;

      m_basePoints.push_back( RatingSortBasePoint( geo, ERatingSortBpType::LongWait, EBasket::Undefined, 0, 0 ) );
      m_basePoints.push_back( RatingSortBasePoint( geo, ERatingSortBpType::FullParties, EBasket::Undefined, 0, 0 ) );
    }

  if ( m_mapType == NDb::MAPTYPE_COOPERATIVE )
  {
    size_t sz = m_basePoints.size();
    m_basePoints.reserve( sz * 2 );
    for( size_t i = 0; i < sz; ++i )
    {
      m_basePoints[i].pveFaction = lobby::ETeam::Team1;

      m_basePoints.push_back( m_basePoints[i] );
      m_basePoints.back().pveFaction = lobby::ETeam::Team2;
    }
  }
}



void RatingSortMmLogic::ShuffleBasePoints( BasePointsList & dest, BasePointsList & src, unsigned historyLength )
{
  NI_VERIFY( !src.empty(), "", return );

  const float ratingRange = m_settings->ratingScale.high - m_settings->ratingScale.low;
  const float forceRange = m_settings->forceScale.high - m_settings->forceScale.low;

  dest.push_back( src.front() );

  BasePointsList lastPoints;
  lastPoints.push_back( src.front() );

  src.pop_front();

  while ( !src.empty() )
  {
    //We are looking for point distanced the most from points in 'lastPoints'
    BasePointsList::iterator bestPoint;
    float bestPointDist = -1;

    for ( BasePointsList::iterator i = src.begin(); i != src.end(); ++i )
    {
      float nearestDist = -1.0f;
      for ( BasePointsList::iterator j = lastPoints.begin(); j != lastPoints.end(); ++j )
      {
        float deltaR = ( ratingRange > 1e-3 ) ? ( ( j->rating - i->rating ) / ratingRange ) : 0;
        float deltaF = ( forceRange > 1e-3 ) ? ( ( j->force - i->force ) / forceRange ) : 0;
        float dist = sqrt( sqr( deltaR ) + sqr( deltaF ) );
        if ( ( nearestDist < 0 ) || ( dist < nearestDist ) )
          nearestDist = dist;
      }
      NI_ASSERT( nearestDist >= 0, "" );

      if ( ( bestPointDist < 0 ) || ( nearestDist > bestPointDist ) )
      {
        bestPoint = i;
        bestPointDist = nearestDist;
      }
    }

    NI_ASSERT( bestPointDist >= 0, "" );
    dest.push_back( *bestPoint );
    lastPoints.push_back( *bestPoint );

    src.erase( bestPoint );

    while ( lastPoints.size() > historyLength )
      lastPoints.pop_front();
  }
}



StrongMT<RatingSortJob> RatingSortMmLogic::CookDataForAJob( const RatingSortBasePoint & basePoint, int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  TPresample presample;
  SampleContext sampleCtx;

  if ( m_mapType == NDb::MAPTYPE_COOPERATIVE )
  {
    NI_ASSERT( basePoint.pveFaction != lobby::ETeam::None, "" );
    NI_ASSERT( ( basePoint.basket == EBasket::Normal ) || ( basePoint.type == ERatingSortBpType::LongWait ) || ( basePoint.type == ERatingSortBpType::FullParties ), "" );
  }

  if ( basePoint.type == ERatingSortBpType::Normal )
  {
    if ( basePoint.basket == EBasket::Normal || basePoint.basket == EBasket::Leaver )
      PresampleByBasePoints( presample, sampleCtx, basePoint, mostPopularRevision, 0 );
    else // ( basePoint.basket == EBasket::Newbie )
      PresampleNewbies( presample, sampleCtx, basePoint, mostPopularRevision );
  }
  else if ( basePoint.type == ERatingSortBpType::LongWait )
    PresampleLongWait( presample, sampleCtx, basePoint, mostPopularRevision );
  else if ( basePoint.type == ERatingSortBpType::FullParties )
  {
    PresampleFullParties( presample, sampleCtx, basePoint, mostPopularRevision );
    if ( m_mapType == NDb::MAPTYPE_COOPERATIVE )
    {
      if ( StrongMT<RatingSortJob> job = CheckFullPartyPveGames( presample, basePoint, sampleCtx ) )
        return job;
    }
    else
    {
      if ( StrongMT<RatingSortJob> job = CheckFullPartyPvpGames( presample, basePoint, sampleCtx ) )
        return job;
    }
    return 0;
  }
  else
    NI_ALWAYS_ASSERT("");

  //Optimization: Idle matchmaking consuming too much CPU
  if ( !sampleCtx.pop )
    return 0;

  if ( m_config->manoeuvresEnabled && ( m_mapType != NDb::MAPTYPE_COOPERATIVE ) )
    for ( int tidx = 0; tidx < 2; ++tidx ) {
      NI_PROFILE_BLOCK( "Manoeuvres" );
      const int minPop =  m_settings->manoeuvresMinPopulation;
      const int maxPop = m_settings->manoeuvresMaxPopulation;
      int other_tidx = tidx ? 0 : 1;
      if ( ( sampleCtx.teamPop[tidx] >= minPop ) && ( sampleCtx.teamPop[other_tidx] < maxPop ) )
      {
        lobby::ETeam::Enum manoeuvresFaction = lobby::ETeam::Index( tidx );
        StrongMT<RatingSortJob> job = new RatingSortJob( basePoint, manoeuvresFaction, m_settings, m_teamSize );

        if ( SampleSample( job->Sample(), presample, basePoint, manoeuvresFaction, sampleCtx ) )
        {
          job->Draft().longWaitMode = sampleCtx.longWaitMode;
          return job;
        }
      }
    }

  NI_PROFILE_BLOCK( "Normal" );

  StrongMT<RatingSortJob> job = new RatingSortJob( basePoint, lobby::ETeam::None, m_settings, m_teamSize );

  if ( SampleSample( job->Sample(), presample, basePoint, lobby::ETeam::None, sampleCtx ) )
  {
    job->Draft().longWaitMode = sampleCtx.longWaitMode;
    return job;
  }

  return 0;
}



RatingSortBasePoint RatingSortMmLogic::GetNextBasePoint()
{
  for ( int limit = 0; ; ++limit )
  {
    RatingSortBasePoint & bp = m_basePoints[m_nextBasePointIdx];

    if ( limit > 10000 )
    {
      CriticalTrace( "Infinite base point loop" );
      return bp;
    }

    ++m_nextBasePointIdx;

    if ( m_nextBasePointIdx >= m_basePoints.size() ) {
      m_nextBasePointIdx = 0;
      if ( m_config->debugLogging )
        DebugTrace( "Base points cycle (%d) passed, sim time %.1f", m_basePoints.size(), m_now );

      m_statistics->OnBpCycleStart( m_now );
    }

    const int counter = bp.counter;
    bp.counter = ( counter + 1 ) % bp.frequency;

    if ( counter )
      continue;

    if ( !m_config->international )
      if ( bp.sidesLocale[0] != bp.sidesLocale[1] )
        continue;

//    if ( m_proPlayerModeEndTime >= 0 )
//      if ( bp.rating >= m_settings->highRatingThreshold && bp.rating < m_settings->proRatingThreshold )
//        continue;

    return bp;
  }
}



void RatingSortMmLogic::CheckForProPlayers( int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  bool havePros = false;

  for ( TRequestMap::iterator it = m_requests.begin(); it != m_requests.end() ; ++it )
  {
    StrongMT<MmRequest> req = it->second;
    
    if ( mostPopularRevision && mostPopularRevision !=-1)
      if ( req->CommonData().clientRevision != mostPopularRevision )
        continue;

    if ( req->EffectiveRating( 0 ) >= m_settings->proRatingThreshold ) {
      havePros = true;
      break;
    }
  }

  if ( havePros )
  {
    if ( m_proPlayerModeEndTime < 0 ) {
      m_loger->Log( ELogLevel::Normal, "Pro player mode: enabled" );
      m_proPlayerModeStartTime = m_now;
    }

    m_proPlayerModeEndTime = m_now + m_settings->highRatingCooldown;
    return;
  }

  if ( ( m_proPlayerModeEndTime >= 0 ) && ( m_now > m_proPlayerModeEndTime ) )
  {
    m_proPlayerModeEndTime = -1;

    NI_ASSERT( m_proPlayerModeStartTime >= 0, "" );
    timer::Time modeTime = m_now - m_proPlayerModeStartTime;
    m_proPlayerModeStartTime = 0;
    m_statistics->OnProModeEnd( modeTime );

    m_loger->Log( ELogLevel::Normal, "Pro player mode: disabled (%.1f)", modeTime );
  }
}



bool RatingSortMmLogic::CookData( Jobs & jobs, int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  //Cut down idle CPU consumption
  if ( m_requests.empty() )
    return false;

  jobs.reserve( m_workersNumber );

  //In live mode, we want to load all processing threads at maximum
  //In simulation mode, this cuts down performance on sparse data
  size_t basePointCounter = m_basePoints.size();
  if ( m_simulationMode )
    basePointCounter = Min( m_workersNumber * 2, m_basePoints.size() );

  while ( ( jobs.size() < m_workersNumber ) && ( basePointCounter > 0 ) )
  {
    RatingSortBasePoint point = GetNextBasePoint();
    --basePointCounter;

    if ( StrongMT<RatingSortJob> job = CookDataForAJob( point, mostPopularRevision ) )
    {
      m_statistics->OnSample();
      RatingSortFSAlgorithm::PreprocessSample( job->Sample() );
      jobs.push_back( job );
    }
  }

  return !jobs.empty();
}



void RatingSortMmLogic::RunIteration( int mostPopularRevision, volatile bool & isRunning )
{
  NI_PROFILE_FUNCTION_MEM;

  ClearInUse();

  CheckForProPlayers( mostPopularRevision );

  NI_VERIFY( !m_basePoints.empty(), "No base points!", return );
  NI_VERIFY( m_nextBasePointIdx >= 0 && m_nextBasePointIdx < m_basePoints.size(), "Wrong base point index", return );

  Jobs jobs;
  CookData( jobs, mostPopularRevision );

  if ( jobs.empty() )
    return; //Not enough data
  NI_ASSERT( jobs.size() <= m_workersNumber, "" );

  DoTheJob( jobs, isRunning );

  ProcessResults( jobs );
}



void RatingSortMmLogic::OnSmartDump()
{
  timer::Time currentlyInProMode = ( m_proPlayerModeStartTime >= 0 ) ? ( m_now - m_proPlayerModeStartTime ) : 0;

  m_statistics->Dump( m_loger, m_now, currentlyInProMode );
}



void RatingSortMmLogic::DoTheJob( Jobs & jobs, volatile bool & isRunning )
{
  NI_ASSERT( m_worker, "" );
  m_worker->Start();

  for ( size_t i = 0; i < jobs.size(); ++i )
    m_worker->AddJob( jobs[i] );

  {
    NI_PROFILE_BLOCK( "Waiting jobs" );
    for ( int i = 0; ; ++i )
      if ( m_worker->WaitAll( 1000 ) )
        break;
      else if ( !isRunning ) {
        MessageTrace( "Shutdown was requested." );
        return;
      }
      else if ( i > 20 ) {
        NI_ALWAYS_ASSERT( "Jobs timed out! Resetting worker..." );
        m_worker = new RatingSortWorker( m_workersNumber );
        return;
      }
  }
}



void RatingSortMmLogic::SortJobResults( Jobs & jobs )
{
  NI_PROFILE_FUNCTION;

  for ( size_t i = 0; i < jobs.size(); ++i )
    for ( size_t j = i + 1; j < jobs.size(); ++j )
    {
      if ( !jobs[j]->Draft().updates )
        continue;
      if ( jobs[i]->Draft().updates )
        if ( jobs[i]->Draft().minValue < jobs[j]->Draft().minValue )
          continue;
      std::swap( jobs[i], jobs[j] );
    }
}



void RatingSortMmLogic::ProcessResults( Jobs & jobs )
{
  NI_PROFILE_FUNCTION;

  SortJobResults( jobs );

  for ( size_t i = 0; i < jobs.size(); ++i )
  {
    RatingSortJob * job = jobs[i];
    RatingSortDraft & draft = job->Draft();

    if ( !draft.updates ) {
      continue;
    }

    if ( IsRequestsInUse( job ) ) {
      if ( m_config->debugLogging ){
        DbgReportRejectedGame( job, "parallel" );
      }
      continue;
    }
    MarkRequestsInUse( job );

    CreateGameFromJob( job );
  }
}



bool RatingSortMmLogic::IsRequestsInUse( RatingSortJob * job ) const
{
  NI_PROFILE_HEAVY_FUNCTION;

  RatingSortDraft & draft = job->Draft();

  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < draft.bestLineup[t].size(); ++i )
      if ( draft.bestLineup[t][i]->InUse() )
        return true;
  return false;
}



void RatingSortMmLogic::MarkRequestsInUse( RatingSortJob * job )
{
  NI_PROFILE_HEAVY_FUNCTION;

  RatingSortDraft & draft = job->Draft();

  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < draft.bestLineup[t].size(); ++i )
      draft.bestLineup[t][i]->Use( true );
}



void RatingSortMmLogic::MarkRequestsInUse( RatingSortFSAlgorithm::Sample & sample )
{
  NI_PROFILE_HEAVY_FUNCTION;

  for ( int t = 0; t < 2; ++t ) {
    lobby::ETeam::Enum tm = lobby::ETeam::Index( t );
    for ( int i = 0; i < sample.Size( tm ); ++i ) {
      MmRequest * req = sample.GetSlot( tm, i ).req;
      req->Use( true );
    }
  }
}



void RatingSortMmLogic::CreateGameFromJob( RatingSortJob * job )
{
  NI_PROFILE_FUNCTION;

  RatingSortDraft & draft = job->Draft();
  const mmaking::SGameEstimDetails & det = draft.minValueDetails;

  if ( m_config->debugLogging )
    DebugTrace( "Game completed, sim time: %.1f", m_now );

  unsigned debugGameId = m_debugGameId++;

  if ( false /*draft.minValueDetails.maxValue > 1.0f*/ ) //DEBUG code
  {
    DumpJobSample( job, debugGameId );
    FullDump( debugGameId );
  }

  //We need extensive info on resulting line-ups
  m_loger->Log( ELogLevel::Normal, "Game details, I: bp type %s, rating %d, force %d, dbg_id=%u, estim value: %.3f, avg wait: %d, manoeuvres: %s",
    ERatingSortBpType::ToString( job->BasePoint().type ),
    job->BasePoint().rating, job->BasePoint().force,
    debugGameId,
    draft.minValue, det.waitTimeAvg,
    ( job->ManoeuvresFaction() == lobby::ETeam::None ) ? "no" : "yes" );

  m_loger->Log( ELogLevel::Normal, "Game details, II: sample: %d + %d, long wait: %s, iterations done: %d (%.1f ms)",
    job->Sample().Size( lobby::ETeam::Team1 ), job->Sample().Size( lobby::ETeam::Team2 ), 
    ELongWaitMode::ToString( job->Draft().longWaitMode ),
    job->Iterations(), job->TimeWasted() * 1e3 );

  m_loger->Log( ELogLevel::Normal, "Game details, deltas: ratingSpan=%d, ratingPatternDelta=%d, ratingTeamAvgDelta=%d, forceSpan=%d, genderPairs=%d, loseStrCorrctn=%d",
    det.ratingSpan, det.ratingPatternDelta, det.ratingTeamAvgDelta, det.forceSpan, det.genderPairsDelta, 0/*det.loseStreakCorrectionLevel*/ );

  m_loger->Log( ELogLevel::Normal, "Game details, terms: ratingSpan=%.3f, ratingPatternDelta=%.3f, ratingTeamAvgDelta=%.3f, forceSpan=%.3f, "
    "sex=%.3f, genderPairs=%.3f, heroes=%.3f, heroClassOpt=%.3f, heroClassDiff=%.3f, loseStrCorrctn=%.2f",
    det.ratingSpanTerm, det.ratingPatternDeltaTerm, det.ratingTeamAvgDeltaTerm, det.forceSpanTerm,
    det.sexTerm, det.genderPairsDeltaTerm, det.heroesTerm, det.heroClassesOptimumTerm, det.heroClassesDifferTerm, 0.0f/*det.loseStreakCorrectionTerm*/ );

  const GeolocationConstraints & dbgGeo = job->BasePoint();
  m_loger->Log( ELogLevel::Normal, "Game details, international: locales=[%s%s, %s%s], location=%s", 
    m_locales.Find( dbgGeo.sidesLocale[0] ), dbgGeo.multipleLocales ? ( dbgGeo.donorSide ? "(recipient)" : "(donor)" ) : "",
    m_locales.Find( dbgGeo.sidesLocale[1] ), dbgGeo.multipleLocales ? ( dbgGeo.donorSide ? "(donor)" : "(recipient)" ) : "",
    m_locations.Find( dbgGeo.location ) );

  OutputGame( draft, job->BasePoint().basket, job->ManoeuvresFaction(), job->BasePoint().type );

  m_statistics->OnGame( job->BasePoint().type, job->Draft().longWaitMode, job->ManoeuvresFaction() );
}



void RatingSortMmLogic::DumpJobSample( RatingSortJob * job, unsigned debugGameId )
{
  m_queueCsvDumper->Log( ELogLevel::Normal, "Job sample dump. dbg_id=%u", debugGameId );
  WriteFullDumpHat();

  const RatingSortFSAlgorithm::Sample & sample = job->Sample();

  for ( int i = 0; i < 2; ++i )
    for ( int j = 0; j < sample.Size( lobby::ETeam::Index( i ) ); ++j )
    {
      const RatingSortSampleSlot & slot = sample.GetSlot( lobby::ETeam::Index( i ), j );

      WriteFullDumpRequest( slot.req );
    }
}



inline float PolyLerp( float x, const vector<NDb::LerpDataItem> & data )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_VERIFY( !data.empty(), "", return 0 );

  const float eps = 1e-3f;

  if ( x < data.front().x + eps )
    return data.front().y;

  if ( x > data.back().x - eps )
    return data.back().y;

  for ( int i = 0; i + 1 < data.size(); ++i ) {
    const float x0 = data[i].x, x1 = data[i + 1].x;
    NI_VERIFY( x0 + eps < x1, "", return data[0].y );
    if ( ( x > x0 - eps ) && ( x < x1 + eps ) ) {
      const float t = ( x - x0 ) / ( x1 - x0 );
      return data[i].y * ( 1.0f - t ) + data[i].y * t;
    }
  }

  NI_ALWAYS_ASSERT( "" );
  return data[0].y;
}



bool RatingSortMmLogic::FilterPresampleByRating( float & squareDiff, const RatingSortBasePoint & basePoint, MmRequest * req, float timeFactor, SampleContext & sampleCtx )
{
  NI_PROFILE_FUNCTION;

  if ( m_mapType == NDb::MAPTYPE_COOPERATIVE )
    return true;

  int effRating = req->EffectiveRating( m_settings );

  if ( ( m_proPlayerModeEndTime >= 0 ) && ( sampleCtx.longWaitMode != ELongWaitMode::TooLong ) )
  {
    if ( effRating >= m_settings->highRatingThreshold )
      if ( basePoint.rating < m_settings->highRatingThreshold )
        return false;
    if ( effRating < m_settings->highRatingThreshold )
      if ( basePoint.rating >= m_settings->highRatingThreshold )
        return false;
  }

  const float ratingDiff = abs( effRating - basePoint.rating );

  float diffHigh = PolyLerp( basePoint.rating, m_settings->ratingScale.diffHigh );
  float diffLow = PolyLerp( basePoint.rating, m_settings->ratingScale.diffLow );

  const float ratingDiffLimit = Lerp( diffLow, diffHigh, timeFactor );

  if ( sampleCtx.longWaitMode != ELongWaitMode::TooLong )
  {
    const float clampedRatingDiffLimit = Clamp( ratingDiffLimit, diffLow, diffHigh );
    if ( ratingDiff > clampedRatingDiffLimit )
      return false;
  }

  squareDiff += sqr( ratingDiff / ratingDiffLimit );
  return true;
}



bool RatingSortMmLogic::FilterPresampleByForce( float & squareDiff, const RatingSortBasePoint & basePoint, MmRequest * req, float timeFactor, SampleContext & sampleCtx )
{
  NI_PROFILE_FUNCTION;

  if ( m_mapType != NDb::MAPTYPE_COOPERATIVE )
    return true;

  int effForce = req->EffectiveForce( m_settings );
  //effForce += req->LoseStreakForceCompensation() / req->Size();

  const float forceDiff = abs( effForce - basePoint.force );

  float diffHigh = PolyLerp( effForce, m_settings->forceScale.diffHigh );
  float diffLow = PolyLerp( effForce, m_settings->forceScale.diffLow );

  const float forceDiffLimit = Lerp( diffLow, diffHigh, timeFactor );

  if ( sampleCtx.longWaitMode != ELongWaitMode::TooLong )
  {
    const float clampedForceDiffLimit = Clamp( forceDiffLimit, diffLow, diffHigh );
    if ( forceDiff > clampedForceDiffLimit )
      return false;
  }

  squareDiff += sqr( forceDiff / forceDiffLimit );
  return true;
}



bool RatingSortMmLogic::FilterPresampleByPartySize( const RatingSortBasePoint & basePoint, MmRequest * req, timer::Time waitTime )
{
  NI_PROFILE_HEAVY_FUNCTION;

  NI_ASSERT( basePoint.basket == EBasket::Normal, "" );

  if ( req->Size() != m_teamSize )
    return true;

  return ( waitTime > m_settings->fullPartyVsRandomTimeThreshold );
}



bool RatingSortMmLogic::FilterPresampleByPveFaction( const RatingSortBasePoint & basePoint, MmRequest * req )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( basePoint.pveFaction == lobby::ETeam::None )
    return true;

  return req->CommonData().team == basePoint.pveFaction;
}



void RatingSortMmLogic::PresampleByBasePoints( TPresample & presample, SampleContext & sampleCtx, const RatingSortBasePoint & basePoint, int mostPopularRevision, MmRequest * _ignoreReq )
{
  NI_PROFILE_FUNCTION;

  //TODO: Limit active requests number

  EBasket::Enum filterBasket = ( m_mapType == NDb::MAPTYPE_COOPERATIVE ) ? EBasket::Undefined : EBasket::Normal;

  const TGeoIndex primaryLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.recipientSide] : basePoint.sidesLocale[0];
  const TGeoIndex donorLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.donorSide] : 0;
  TGeoindexVector sidesLoc; sidesLoc.push_back(primaryLoc);

  for ( QueueIterator it( m_requests, mostPopularRevision, filterBasket, sidesLoc, donorLoc, basePoint.location, m_now, QueueIterator::F_RatingSortMode, m_settings, m_config, m_locales, false ); ; )
  {
    QueueIteratorCtx itCtx;
    StrongMT<MmRequest> req = it.NextRequest( itCtx );
    if ( !req )
      break;

    if ( req == _ignoreReq )
      continue;

    if ( !FilterPresampleByPveFaction( basePoint, req ) )
      continue;

    if ( !FilterPresampleByPartySize( basePoint, req, itCtx.waitTime ) )
      continue;

    float presampleOrder = 0;

    const float timeFactor = (float)( itCtx.waitTime / m_settings->ratingDiffGrowTime );

    float squareDist = 0;
    if ( !FilterPresampleByRating( squareDist, basePoint, req, timeFactor, sampleCtx ) )
      continue;
    if ( !FilterPresampleByForce( squareDist, basePoint, req, timeFactor, sampleCtx ) )
      continue;
    presampleOrder = sqrtf( squareDist );

    presample.insert( PresampleKey( (int)( presampleOrder * 1e4 ), req, itCtx.waitTime, itCtx.pingIsGood ) );

    UpdateSampleContext( sampleCtx, req, itCtx.waitTime );
  }
}



void RatingSortMmLogic::PresampleNewbies( TPresample & presample, SampleContext & sampleCtx, const RatingSortBasePoint & basePoint, int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  const float probWaitTimeWindow = m_settings->waitVsProbability.endingWaitTime - m_settings->waitVsProbability.startingWaitTime;
  const int probWeightWindow = m_settings->waitVsProbability.endingProbabilityWeight - m_settings->waitVsProbability.startingProbabilityWeight;

  const TGeoIndex primaryLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.recipientSide] : basePoint.sidesLocale[0];
  const TGeoIndex donorLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.donorSide] : 0;
  TGeoindexVector sidesLoc; sidesLoc.push_back(primaryLoc);
  for ( QueueIterator it( m_requests, mostPopularRevision, EBasket::Undefined, sidesLoc, donorLoc, basePoint.location, m_now, QueueIterator::F_RatingSortMode, m_settings, m_config, m_locales, false ); ; )
  {
    QueueIteratorCtx itCtx;
    StrongMT<MmRequest> req = it.NextRequest( itCtx );
    if ( !req )
      break;

    if ( req->Basket() == EBasket::Newbie || req->Basket() == EBasket::Leaver )
    {
      const float t = Clamp( (float)( ( itCtx.waitTime - m_settings->waitVsProbability.startingWaitTime ) / probWaitTimeWindow ), 0.0f, 1.0f );
      const int weight = m_settings->waitVsProbability.startingProbabilityWeight + (int)( 0.5f + t * probWeightWindow );
      const int roll = m_random.Next( weight );

      presample.insert( PresampleKey( -roll, req, itCtx.waitTime, itCtx.pingIsGood ) );

      UpdateSampleContext( sampleCtx, req, itCtx.waitTime );
    }
    else if ( req->Basket() == EBasket::Normal )
    {
      //FIXME: We ignore wait time of 'normal' players
      int r = req->EffectiveRating( 0 );

      if ( r > m_settings->noobGamesMaxNormalRating )
        continue;

      presample.insert( PresampleKey( r, req, itCtx.waitTime, itCtx.pingIsGood ) );

      //We do not want to count Normals
      //UpdateSampleContext( sampleCtx, req, itCtx.waitTime );
    }
  }
}



void RatingSortMmLogic::PresampleLongWait( TPresample & presample, SampleContext & sampleCtx,  const RatingSortBasePoint & basePoint, int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  struct PreselectSlot : public QueueIteratorCtx
  {
    StrongMT<MmRequest> req;
    PreselectSlot() {}
    PreselectSlot( const QueueIteratorCtx & _ctx, MmRequest * _req ) :
    QueueIteratorCtx( _ctx ), req( _req )
    {}
  };  

  typedef std::list<PreselectSlot> ReqList;

  ReqList softlist, hardlist;

  EBasket::Enum filterBasket = ( m_mapType == NDb::MAPTYPE_COOPERATIVE ) ? EBasket::Undefined : EBasket::Normal;

  const TGeoIndex primaryLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.recipientSide] : basePoint.sidesLocale[0];
  const TGeoIndex donorLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.donorSide] : 0;
  TGeoindexVector sidesLoc; sidesLoc.push_back(primaryLoc);
  for ( QueueIterator it( m_requests, mostPopularRevision, filterBasket, sidesLoc, donorLoc, basePoint.location, m_now, QueueIterator::F_RatingSortMode, m_settings, m_config, m_locales, false ); ; )
  {
    QueueIteratorCtx itCtx;
    StrongMT<MmRequest> req = it.NextRequest( itCtx );
    if ( !req )
      break;

    if ( !FilterPresampleByPveFaction( basePoint, req ) )
      continue;

    if ( itCtx.waitTime < m_settings->waitTimeSoftLimit )
      continue;

    if ( itCtx.waitTime >= m_settings->waitTimeHardLimit )
      hardlist.push_back( PreselectSlot( itCtx, req ) );
    else
      softlist.push_back( PreselectSlot( itCtx, req ) );
  }

  if ( softlist.empty() && hardlist.empty() )
    return;

  if ( !softlist.empty() )
    m_uniStats->AddStat( "LongWaitSoftLimitRequests", softlist.size() );

  if ( !hardlist.empty() )
    m_uniStats->AddStat( "LongWaitHardLimitRequests", softlist.size() );

  PreselectSlot lucky;
  if ( !hardlist.empty() )
  {
    lucky = m_random.RollFromContainer( hardlist );
    sampleCtx.longWaitMode = ELongWaitMode::TooLong;
  }
  else
  {
    lucky = m_random.RollFromContainer( softlist );
    sampleCtx.longWaitMode = ELongWaitMode::Normal;
  }
  NI_VERIFY( lucky.req, "", return );

  presample.insert( PresampleKey( -1000, lucky.req, lucky.waitTime, lucky.pingIsGood, true ) );
  UpdateSampleContext( sampleCtx, lucky.req, lucky.waitTime );

  RatingSortBasePoint tmpBasePoint(
    (const GeolocationConstraints &)basePoint,
    ERatingSortBpType::Normal, EBasket::Normal,
    0, lucky.req->EffectiveForce( m_settings ) );

  tmpBasePoint.rating = lucky.req->EffectiveRating( m_settings );

  tmpBasePoint.pveFaction = basePoint.pveFaction;

  PresampleByBasePoints( presample, sampleCtx, tmpBasePoint, mostPopularRevision, lucky.req );

  m_uniStats->AddStat( "LongWaitPresampleTotal", sampleCtx.pop );
}



void RatingSortMmLogic::PresampleFullParties( TPresample & presample, SampleContext & sampleCtx, const RatingSortBasePoint & basePoint, int mostPopularRevision )
{
  NI_PROFILE_FUNCTION;

  EBasket::Enum filterBasket = ( m_mapType == NDb::MAPTYPE_COOPERATIVE ) ? EBasket::Undefined : EBasket::Normal;

  const TGeoIndex primaryLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.recipientSide] : basePoint.sidesLocale[0];
  const TGeoIndex donorLoc = basePoint.multipleLocales ? basePoint.sidesLocale[basePoint.donorSide] : 0;
  TGeoindexVector sidesLoc; sidesLoc.push_back(primaryLoc);
  for ( QueueIterator it( m_requests, mostPopularRevision, filterBasket, sidesLoc, donorLoc, basePoint.location, m_now, QueueIterator::F_RatingSortMode, m_settings, m_config, m_locales, false ); ; )
  {
    QueueIteratorCtx itCtx;
    StrongMT<MmRequest> req = it.NextRequest( itCtx );
    if ( !req )
      break;

    if ( req->Size() < m_teamSize )
      continue;

    const int key = -req->EffectiveRating( false );
    presample.insert( PresampleKey( key, req, itCtx.waitTime, itCtx.pingIsGood ) );

    UpdateSampleContext( sampleCtx, req, itCtx.waitTime );
  }

  m_uniStats->AddStat( "FullPartyPresample", presample.size() );
}



void RatingSortMmLogic::UpdateSampleContext( SampleContext & ctx, MmRequest * req, timer::Time waitTime )
{
  const int tidx = lobby::ETeam::Index( req->CommonData().team );

  const int r = req->EffectiveRating( m_settings );
  if ( !ctx.pop )
  {
    ctx.minRating = ctx.maxRating = r;
    ctx.maxWaitTime = waitTime;
  }
  else
  {
    ctx.minRating = Min( ctx.minRating, r );
    ctx.maxRating = Max( ctx.maxRating, r );
    ctx.maxWaitTime = Max( ctx.maxWaitTime, waitTime );
  }

  ctx.pop += req->Size();
  ctx.teamPop[tidx] += req->Size();
}



bool RatingSortMmLogic::SampleSample( RatingSortFSAlgorithm::Sample & sample, const TPresample & presample, const RatingSortBasePoint & basePoint, lobby::ETeam::Enum manvrsFaction, SampleContext & sampleCtx )
{
  NI_PROFILE_FUNCTION;

  const bool manoeuvres = ( manvrsFaction != lobby::ETeam::None );
  const bool pve = ( basePoint.pveFaction != lobby::ETeam::None );

  int fullsweepLimit = m_settings->fullSweepSubsetLimit;
  if ( pve )
    fullsweepLimit = m_settings->fullSweepSubsetLimitPve;
  else if ( manoeuvres )
    fullsweepLimit = m_settings->manoeuvresFullSweepSubset;

  sample.Reserve( fullsweepLimit );

  unsigned goodPingEntries = 0;

  THeroCounter heroCounter[2];
  for ( TPresample::const_iterator it = presample.begin(); it != presample.end(); ++it )
  {
    NI_PROFILE_HEAVY_BLOCK( "Iteration" );

    if ( manoeuvres || pve )
    {
      if ( sample.Size( lobby::ETeam::Team1 ) >= fullsweepLimit )
        break;
    }
    else
    {
      if ( ( sample.Size( lobby::ETeam::Team1 ) >= fullsweepLimit ) && ( sample.Size( lobby::ETeam::Team2 ) >= fullsweepLimit ) )
        break;
    }

    const bool pingIsGood = it->pingIsGood;
    StrongMT<MmRequest> req = it->request;
    const timer::Time waitTime = it->effectiveWaitTime;
    const bool mandatory = it->mandatory;

    const lobby::ETeam::Enum faction = req->CommonData().team;

     if ( sample.Size( faction ) >= fullsweepLimit )
        continue; //FIXME: In manvrs and PVE we can already break cycle

    const int tidx = lobby::ETeam::Index( faction );

    if ( !CheckHeroesLimit( heroCounter[tidx], req, basePoint.basket ) )
      continue;

    CountHeroes( heroCounter[tidx], req, m_heroes );

    //In manoeuvres, we always sample to Team1
    const lobby::ETeam::Enum pushFaction = ( manoeuvres || pve ) ? lobby::ETeam::Team1 : faction;

    sample.Push( pushFaction, RatingSortSampleSlot( req, waitTime, mandatory, basePoint.basket, m_settings ) );

    if ( pingIsGood )
      ++goodPingEntries;
  }

  if ( !goodPingEntries )
    return false;

  if ( m_config->debugLogging )
    DebugTrace( "Sample: base rating %d, base force %d, sim time: %.1f, total requests %d, presample %d + %d, sample %d + %d",
          basePoint.rating, basePoint.force, m_now, m_requests.size(),
          sampleCtx.teamPop[0], sampleCtx.teamPop[1],
          sample.Size( lobby::ETeam::Team1 ), sample.Size( lobby::ETeam::Team2 ) );

  bool enoughData = false;
  if ( manoeuvres )
    enoughData = ( sample.Length( lobby::ETeam::Team1 ) >= m_teamSize * 2 );
  else if ( pve )
    enoughData = ( sample.Length( lobby::ETeam::Team1 ) >= m_teamSize );
  else
    enoughData = ( ( sample.Length( lobby::ETeam::Team1 ) >= m_teamSize ) && ( sample.Length( lobby::ETeam::Team2 ) >= m_teamSize ) );

  return enoughData;
}



StrongMT<RatingSortJob> RatingSortMmLogic::CheckFullPartyPvpGames( const TPresample & presample, const RatingSortBasePoint & basePoint, SampleContext & sampleCtx )
{
  NI_PROFILE_FUNCTION;

  if ( presample.size() < 2 )
    return 0;

  const int limit = 10;

  StrongMT<MmRequest> bestReq[2];
  int minDiff = 0;

  int limit0 = limit;
  for ( TPresample::const_iterator it0 = presample.begin(); ( it0 != presample.end() ) && limit0; ++it0 )
  {
    StrongMT<MmRequest> req0 = it0->request;
    const timer::Time wait0 = it0->effectiveWaitTime;
    const int rating0 = req0->EffectiveRating( m_settings );

    TPresample::const_iterator it1 = it0;
    ++it1;
    int limit1 = limit0 - 1;

    for ( ; ( it1 != presample.end() ) && limit1; ++it1 )
    {
      StrongMT<MmRequest> req1 = it1->request;
      const timer::Time wait1 = it1->effectiveWaitTime;
      const int rating1 = req1->EffectiveRating( m_settings );

      timer::Time effectiveWait = 0.5 * ( wait0 + wait1 );
      const float timeFactor = Clamp( (float)( effectiveWait / m_settings->ratingDiffGrowTime ), 0.0f, 1.0f );

      const int ratingDiff = abs( rating0 - rating1 );
      const int ratingDiffLimit = (int)( Lerp( (float)m_settings->fullPartyGameRatingDiffMin, (float)m_settings->fullPartyGameRatingDiffMax, timeFactor ) );

      if ( ratingDiff < ratingDiffLimit )
        if ( ( ratingDiff < minDiff ) || !bestReq[0] || !bestReq[1] )
        {
          minDiff = ratingDiff;
          bestReq[0] = req0;
          bestReq[1] = req1;
        }

      --limit1;
    }
    --limit0;
  }

  if ( !bestReq[0] || !bestReq[1] )
    return 0;

  bool manvrs = ( bestReq[0]->CommonData().team == bestReq[1]->CommonData().team );
  lobby::ETeam::Enum manvrsFaction = manvrs ? bestReq[0]->CommonData().team : lobby::ETeam::None;

  StrongMT<RatingSortJob> job = new RatingSortJob( basePoint, manvrsFaction, m_settings, m_teamSize );

  for ( int i = 0; i < 2; ++i )
  {
    lobby::ETeam::Enum pushTeam = manvrs ? lobby::ETeam::Team1 : bestReq[i]->CommonData().team;
    int wait = m_settings->estimFunDecreaseTimeEnd; //Hacked wait time
    job->Sample().Push( pushTeam, RatingSortSampleSlot( bestReq[i], wait, false, basePoint.basket, m_settings ) );
  }

  return job;
}



StrongMT<RatingSortJob> RatingSortMmLogic::CheckFullPartyPveGames( const TPresample & presample, const RatingSortBasePoint & basePoint, SampleContext & sampleCtx )
{
  NI_PROFILE_FUNCTION;

  if ( presample.size() < 1 )
    return 0;

  StrongMT<MmRequest> bestReq;
  timer::Time maxWaitTime = 0;

  for ( TPresample::const_iterator it = presample.begin(); it != presample.end(); ++it )
  {
    StrongMT<MmRequest> req = it->request;
    const timer::Time wait = it->effectiveWaitTime;

    if ( !bestReq || ( wait > maxWaitTime ) )
    {
      bestReq = req;
      maxWaitTime = wait;
    }
  }

  if ( !bestReq )
    return 0;

  StrongMT<RatingSortJob> job = new RatingSortJob( basePoint, lobby::ETeam::None, m_settings, m_teamSize );

  int wait = m_settings->estimFunDecreaseTimeEnd; //Hacked wait time
  job->Sample().Push( lobby::ETeam::Team1, RatingSortSampleSlot( bestReq, wait, false, basePoint.basket, m_settings ) );
  return job;
}



void RatingSortMmLogic::OutputGame( RatingSortDraft & draft, EBasket::Enum basket, lobby::ETeam::Enum manoeuvresFaction, ERatingSortBpType::Enum basePointType )
{
  NI_PROFILE_FUNCTION;

  MMakingDraftGame game;
  game.Init( m_teamSize, basket, m_heroes );

  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < draft.bestLineup[t].size(); ++i ) {
      lobby::ETeam::Enum faction = lobby::ETeam::Index( t );
      lobby::ETeam::Enum factionOverride = ( manoeuvresFaction == lobby::ETeam::None ) ? lobby::ETeam::None : faction;
      game.AddMembers( draft.bestLineup[t][i], factionOverride );
    }

  game.AssignAutoHeroes();
  game.Check( m_mapType );

  mmaking::EDebugGameType::Enum dbgGameType = mmaking::EDebugGameType::Normal;
  if ( basePointType == ERatingSortBpType::LongWait )
    dbgGameType = mmaking::EDebugGameType::LongWait;
  else if ( basePointType == ERatingSortBpType::FullParties )
    dbgGameType = mmaking::EDebugGameType::FullParty;

  PushResultingGame( game, dbgGameType );

  for ( int t = 0; t < 2; ++t )  {
    for ( int i = 0; i < draft.bestLineup[t].size(); ++i ) {
      StrongMT<MmRequest> req = draft.bestLineup[t][i];
      DeleteRequest( req->RequestId() );
    }
    draft.bestLineup[t].clear(); //Raw pointrs no longer valid
  }
}



void RatingSortMmLogic::DbgReportRejectedGame( RatingSortJob * job, const char * reason )
{
  NI_PROFILE_FUNCTION;

  const RatingSortBasePoint & basePoint = job->BasePoint();
  const RatingSortFSAlgorithm::Sample & sample = job->Sample();
  const RatingSortDraft & draft = job->Draft();

  if ( !m_config->debugLogging )
    return;

  const mmaking::SGameEstimDetails & det = draft.minValueDetails;

  DebugTrace( "Game rejected: Reason '%s', Base rating %d, base force %d, estim value: %.3f, avg wait: %d sec, sim time: %.1f",
    reason, basePoint.rating, basePoint.force, draft.minValue, det.waitTimeAvg, m_now );

  DebugTrace( "Game rejected, deltas: ratingSpan=%d, ratingPatternDelta=%d, ratingTeamAvgDelta=%d, forceSpan=%d, genderPairs=%d",
    det.ratingSpan, det.ratingPatternDelta, det.ratingTeamAvgDelta, det.forceSpan, det.genderPairsDelta );
  DebugTrace( "Game rejected, terms: ratingSpan=%.3f, ratingPatternDelta=%.3f, ratingTeamAvgDelta=%.3f forceSpan=%.3f, "
    "sex=%.3f, genderPairs=%.3f, heroes=%.3f, heroClassOpt=%.3f, heroClassDiff=%.3f",
    det.ratingSpanTerm, det.ratingPatternDeltaTerm, det.ratingTeamAvgDeltaTerm, det.forceSpanTerm, 
    det.sexTerm, det.genderPairsDeltaTerm, det.heroesTerm, det.heroClassesOptimumTerm, det.heroClassesDifferTerm );

  for ( int t = 0; t < 2; ++t )
    for ( int i = 0; i < draft.bestLineup[t].size(); ++i ) {
      MmRequest * req = draft.bestLineup[t][i];
      DebugTrace( "    %s", req->FormatAll() );
    }

  DebugTrace( "Source sample dump:" );
  DebugTrace( "ReqId;Faction;Sex;HeroId;GRating;PRating;Force;Wait" );
  for ( int t = 0; t < 2; ++t ) {
    lobby::ETeam::Enum team = lobby::ETeam::Index( t );
    for ( int i = 0; i < sample.Size( team ); ++i ) {
      const RatingSortSampleSlot & slot = sample.GetSlot( team, i );

      int wait = m_now - slot.req->StartTime();
      for ( int j = 0; j < slot.req->Size(); ++j ) {
        const SRequestMemberEx & m = slot.req->Member( j );
        DebugTrace( "%d;%s;%s;%s;%d;%d;%d;%d", slot.req->RequestId(), t?"B":"A", m.sex==lobby::ESex::Female?"F":"M", m.heroId, m.guardRating, m.playerRating, m.force, wait );
      }
    }
  }
}

} //namespace mmaking
