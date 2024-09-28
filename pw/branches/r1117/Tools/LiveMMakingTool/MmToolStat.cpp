#include "stdafx.h"

#include "MmToolStat.h"
#include "Db/DBServer.auto.h"
#include "system/SafeTextFormatStl.h"
#include "Server/LobbySocial/SocialLobbyConfig.h"
#include <direct.h>
#include <json/writer.h>


namespace mm_test
{

Statistics::Statistics( MmData * _mmData, const StatisticsSettings & _statSett ) :
mmData( _mmData ), settings( _statSett ),
totalGames( 0 ),
mixedNoobGames( 0 ),
filteredOutRequestsNumber( 0 ),
timeoutRatingHisto( new nutils::DataHistogram( 50 ) ),
avgForceDelta( new nutils::DataHistogram( nutils::EasyVector<double>( -50, -15, -10, -5, -3, 0, 3, 5, 10, 15, 50 ) ) )
{
  for ( int i = 0; i < 2; ++i ) {
    totalMembers[i] = 0;
    totalLadies[i] = 0;
    avgWait[i] = 0;
    avgRemovedWait[i] = 0;
    totalGameMembers[i] = 0;
    totalRemoved[i] = 0;
    avgTeamRating[i] = 0;

    nutils::EasyVector<double> heroRatingScale( 500, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2200, 2500, 3000 );
    heroRatingHisto[i] =            new nutils::DataHistogram( heroRatingScale );
    heroRatingCanceledHisto[i] =    new nutils::DataHistogram( heroRatingScale );

    nutils::EasyVector<double> plrRatingScale( 500, 1300, 1500, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000 );
    playerRatingHisto[i] =          new nutils::DataHistogram( plrRatingScale );
    playerRatingCanceledHisto[i] =  new nutils::DataHistogram( plrRatingScale );

    forceHisto[i] = new nutils::DataHistogram( nutils::EasyVector<double>( 90, 110, 120, 130, 140, 150, 160, 170, 200 ) );
  }

  heroRatingByHourHisto = new nutils::DataHistogram2D( 
    nutils::EasyVector<double>( 0, 4, 8, 12, 14, 16, 20, 24 ),
    nutils::EasyVector<double>( 500, 1300, 1500, 1600, 1800, 1900, 2000, 3000 ) );

  ratingSpanByHeroRating = new nutils::DataHistogram2D( 
    nutils::EasyVector<double>( 50, 100, 150, 200, 300, 500, 2000 ),
    nutils::EasyVector<double>( 500, 1300, 1500, 1600, 1800, 1900, 2000, 3000 ) );

  const float forceStep = 10.0f;
  for ( float f = 100.0f; f <= 180.0f; f += forceStep ) {
    avgForceDeltaByForce.push_back( SAvgForceDeltaByForce( f, f + forceStep ) );
  }

  waitTimeByRating = new WaitTimeByRating( 1100, 2200, 20 );
  socialLobbyconfig = socialLobby::CreateConfigFromStatics();
}




void Statistics::ProcessAddRequest( const Timestamp & ts, mmaking::TRequestUId reqId, const mmaking::SRequestCommonData & commonData, const vector<mmaking::SRequestMember> & members, timer::Time wait )
{
  NI_PROFILE_FUNCTION;

  CheckForMinTimestamp( ts );

  int tidx = lobby::ETeam::Index( commonData.team );

  Strong<SStatRequestData> data = new SStatRequestData( ts, reqId, commonData, wait, members );

  requestsLogRaw.push_back( data );

  AddActiveRequest( data );

  for ( int i = 0; i < members.size(); ++i )
  {
    const mmaking::SRequestMember & memb = members[i];

    mmaking::TUserId id = memb.mmId;
    ++totalMembers[tidx];

    std::pair<TMmIdSet::iterator, bool> insertResult = uniqueUserIds[tidx].insert( id );
    if ( insertResult.second )
    { //New mmid
      ////////////
    }

    if ( memb.sex == lobby::ESex::Female ) {
      ++totalLadies[tidx];
      uniqueLadies[tidx].insert( id );
    }

    RegisterHeroId( memb.heroId );
    CountHeroUsage( commonData.team, memb.heroId );
  }

  FilterRequestsOnAdd( data );
}



void Statistics::ProcessRemoveRequest( const Timestamp & ts, mmaking::TRequestUId reqId, bool timedOut )
{
  CheckForMinTimestamp( ts );

  removedLog.push_back( reqId );

  Strong<SStatRequestData> data = FindActRequestByReqId( reqId );
  if ( !data )
    return;

  FilterRequestsOnCancel( ts, data );

  int tidx = lobby::ETeam::Index( data->cmn.team );

  totalRemoved[tidx] += data->members.size();
  timer::Time wait = TimeDiff( ts, data->ts );

  avgRemovedWait[tidx] += data->members.size() * wait;

  for ( int i = 0; i < data->members.size(); ++i )
  {
    const mmaking::SRequestMember & memb = data->members[i];

    GetThatHistosByRating( memb.heroRating, memb.basket ).removedWait[tidx]->AddValue( wait );
    totalHistograms.removedWait[tidx]->AddValue( wait );
    /*
    if ( !data->cmn.readyToManoeuvre ) {
      GetThatHistosByRating( memb.heroRating, memb.basket ).removedWaitNoManoeuvres[tidx]->AddValue( wait );
      totalHistograms.removedWaitNoManoeuvres[tidx]->AddValue( wait );
    }
    */
    if ( timedOut ) {
      timeoutRatingHisto->AddValue( memb.heroRating );
    }
  }

  RemoveActiveRequest( data );
}

void AvgRRTimeReplyToJson(const TAvgRRTimes& avgTimes, Json::Value& modeTimes)
{
  TAvgRRTimes::const_iterator it_mode = avgTimes.begin();
  for( ; it_mode != avgTimes.end(); ++it_mode )
    modeTimes[ NI_STRFMT( "%d", it_mode->first ) ] = Json::Value(it_mode->second);
}

void AvgModeTimeReplyToJson(const TModeAvgTimes& avgTimes, Json::Value& jsonAvgTimes)
{
  TModeAvgTimes::const_iterator it_mode = avgTimes.begin();
  for( ; it_mode != avgTimes.end(); ++it_mode )
  {
    Json::Value javgTimes ( Json::objectValue );
    AvgRRTimeReplyToJson((*it_mode).second, javgTimes);
    jsonAvgTimes[NI_STRFMT( "%d", it_mode->first )] = javgTimes;
  }
}

void AvgTimeReplyToJson( const TBasketAvgTimes& avgTimes, Json::Value& jsonAvgTimes )
{
  TBasketAvgTimes::const_iterator it_basket = avgTimes.begin();
  for( ; it_basket != avgTimes.end(); ++it_basket )
  {
    Json::Value javgTimes ( Json::objectValue );
    AvgModeTimeReplyToJson(it_basket->second, javgTimes);
    jsonAvgTimes[(it_basket->first).c_str()] = javgTimes;
  }
}


void Statistics::ProcessGame( const Timestamp & ts, const mmaking::SGame & game )
{
  CheckForMinTimestamp( ts );

  ++totalGames;

  const bool pve = mmData->map->mapType == NDb::MAPTYPE_COOPERATIVE;
  TBasketAvgTimes avgTimesPerMode;
  GatherMmStatisticsByMode( mmData->map, lastGameWaitTimesByMode, lastGameGatheredByMode, socialLobbyconfig, timer::Now(), game );
  GetServerStatusEx( lastGameWaitTimesByMode, lastGameGatheredByMode, socialLobbyconfig, timer::Now(), avgTimesPerMode);
  Json::Value JsonMmStatistics(Json::objectValue);
  AvgTimeReplyToJson(avgTimesPerMode, JsonMmStatistics);

  mmaking::GameEstimFun estim( mmData->teamSize, mmData->db, game.basket, game.manoeuvresFaction, pve );

  bool dataIsOk = true;

  int total = 0, noobs = 0, leavers = 0;
  int winsMin = 0, winsMax = 0;
  int minRank = 0, maxRank = 0;
  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    int tidx = lobby::ETeam::Index( party.common.team );

    totalGameMembers[tidx] += party.members.size();
    avgWait[tidx] += party.waitTime * party.members.size();

    int maxHeroRating = 0, loseStreakRatingComp = 0;
    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      maxHeroRating = Max( maxHeroRating, party.members[mi].heroRating );
      loseStreakRatingComp += mmaking::MmRequest::LoseStreakRatingCompensation( mmData->db, party.members[mi].loseStreak );
    }
    loseStreakRatingComp /= party.members.size();


    Strong<SStatRequestData> data;
    for ( int mi = 0; mi < party.members.size(); ++mi )
    {
      const mmaking::SRequestMember & memb = party.members[mi];

      if ( !memb.mmId ) {
        //Defence against add/cancel/game requests in wrong log order
        dataIsOk = false;
        continue;
      }

      const mmaking::SHeroDescription * heroDesc = mmData->heroes->FindDescr( memb.heroId );
      if ( !heroDesc ) {
        dataIsOk = false;
        continue;
      }

      winsMin = total ? Min( winsMin, memb.totalWins ) : memb.totalWins;
      winsMax = total ? Max( winsMax, memb.totalWins ) : memb.totalWins;

      if ( memb.basket == mmaking::EBasket::Newbie )
        ++noobs;

      if ( memb.basket == mmaking::EBasket::Leaver )
        ++leavers;


      //int r = ( game.basket == mmaking::EBasket::Guard ) ? memb.guardRating : memb.playerRating;
      //if ( memb.basket == mmaking::EBasket::Normal )
      //  r += mmaking::MmRequest::LoseStreakRatingCompensation( mmData->db, memb.loseStreak );
      int r = maxHeroRating + loseStreakRatingComp;

      r = Clamp( r, mmData->db->ratingScale.low, mmData->db->ratingScale.high );

      int f = memb.force;
      //if ( memb.basket == mmaking::EBasket::Normal )
      //  f += mmaking::MmRequest::LoseStreakForceCompensation( mmData->db, memb.loseStreak );

      RegisterHeroId( memb.heroId ); //Log can be played from random point
      estim.Count( party.common.team, memb.sex, FindHeroId( memb.heroId ), memb.basket, r, f, heroDesc->classEfficiency, party.waitTime, memb.loseStreak, false );

      if ( !data )
        data = FindActRequestByMmId( memb.mmId );

      ++total;
    }

    int partyRank = ( noobs == party.members.size() ) ? 0 : mmData->ranks->FindRank( maxHeroRating )->index;
    minRank = i ? Min( minRank, partyRank ) : partyRank;
    maxRank = i ? Max( maxRank, partyRank ) : partyRank;

    if ( data )
      FilterRequestsOnGame( ts, data );

    if ( data )
      RemoveActiveRequest( data );
  }

  if ( !dataIsOk )
    return;

  if ( noobs && ( noobs < total ) )
    ++mixedNoobGames;

  EvalForceDeltas( game );
  CollectForceRelations( game );

  mmaking::SGameEstimDetails details;
  estim.Get( details, 0 );

  for ( int i = 0; i < 2; ++i ) {
    heroClassEfficiencyTeamData[estim.ClassEfficiencies()[i]] += 1;
    heroClassLog.push_back( estim.ClassEfficiencies()[i] );
  }

  for ( int i = 0; i < 2; ++i )
    avgTeamRating[i] += details.teamRating[i];
  
  std::string sJsonMmStatistics;
  Json::StyledWriter writer;
  sJsonMmStatistics = writer.write( JsonMmStatistics );
  MessageTrace( "Average time in Json %s", sJsonMmStatistics);

  DebugTrace( "Game estim fun: %02d:%02d:%02d value %g / %g", ts.time.hour, ts.time.minute, ts.time.sec, details.sumValue, details.maxValue );
  DebugTrace( "Game estim fun: %g / %g / %g / %g / %g / %g / %g", 
    details.sexTerm,
    details.genderPairsDeltaTerm,
    details.heroesTerm,
    details.ratingSpanTerm,
    details.ratingPatternDeltaTerm,
    /*details.forceSpanTerm*/0.0f,
    /*details.forcePatternDeltaTerm*/0.0f );
  DebugTrace( "Game estim fun: %g / %g / %g",
    details.heroClassesOptimumTerm,
    details.heroClassesDifferTerm,
    /*details.loseStreakCorrectionTerm*/0.0f );

  UpdateGameHistograms( totalHistograms, game, details );
  for ( int rr = minRank; rr <= maxRank; ++rr )
    UpdateGameHistograms( GetThatHistos( rr ), game, details );

  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    int tidx = lobby::ETeam::Index( party.common.team );

    totalGameMembers[tidx] += party.members.size();
    avgWait[tidx] += party.waitTime * party.members.size();

    int maxHeroRating = 0, loseStreakRatingComp = 0;
    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      maxHeroRating = Max( maxHeroRating, party.members[mi].heroRating );
      loseStreakRatingComp += mmaking::MmRequest::LoseStreakRatingCompensation( mmData->db, party.members[mi].loseStreak );
    }
    loseStreakRatingComp /= party.members.size();

    int effRating = maxHeroRating + loseStreakRatingComp;
    effRating = Clamp( effRating, mmData->db->ratingScale.low, mmData->db->ratingScale.high );
    ratingSpanByHeroRating->AddValue( details.ratingSpan, effRating, party.members.size() );

    for ( int mi = 0; mi < party.members.size(); ++mi )
      waitTimeByRating->Add( effRating, party.waitTime );
  }

  gamesLog.push_back( new GameLogEntry( ts, game ) );
}



void Statistics::RecoverGameForce( mmaking::SGame & recovered, const mmaking::SGame & game ) const
{
  recovered = game;
  for ( int pi = 0; pi < recovered.humans.size(); ++pi )
  {
    mmaking::SGameParty & pty = recovered.humans[pi];
    for ( int mi = 0; mi < pty.members.size(); ++mi )
    {
      mmaking::SRequestMember & member = pty.members[mi];

      TActiveRequestsByMmId::const_iterator it = activeRequestsByMmId.find( member.mmId );
      if ( it == activeRequestsByMmId.end() ) {
        WarningTrace( "Recovering game force: mmid %d not found!", member.mmId );
        member.mmId = 0;
        pty.requestUId = 0;
        continue;
      }

      Strong<SStatRequestData> data = it->second;

      mmaking::SRequestMember * reqMemb = 0;
      for ( int i = 0; i < data->members.size(); ++i )
        if ( data->members[i].mmId == member.mmId ) {
          reqMemb = &data->members[i];
          break;
        }
      NI_VERIFY( reqMemb, "Mmid not found!", continue );

      member.heroRating = reqMemb->heroRating;
      member.guardRating = reqMemb->guardRating;
      member.playerRating = reqMemb->playerRating;
      member.force = reqMemb->force;
    }
  }
}



void Statistics::EnumActiveRequests( IStatisticsEnumerator * callback ) const
{
  for ( TActiveRequests::const_iterator it = activeRequestsByReqId.begin(); it != activeRequestsByReqId.end(); ++it )
    callback->EnumRequest( it->second );
}



template <class TKey> 
inline Strong<nutils::DataHistogram> GetWaitHystoFromMap( std::map<TKey, Strong<nutils::DataHistogram>> & map, const TKey & key, const std::vector<double> & histoScale )
{
  std::map<TKey, Strong<nutils::DataHistogram>>::iterator it = map.find( key );
  if ( it != map.end() )
    return it->second;

  Strong<nutils::DataHistogram> newhisto = new nutils::DataHistogram( histoScale );

  std::pair<std::map<TKey, Strong<nutils::DataHistogram>>::iterator, bool> result = map.insert( std::pair<TKey, Strong<nutils::DataHistogram>>( key, newhisto ) );
  NI_ASSERT( result.second, "" );
  return result.first->second;
}



void Statistics::UpdateGameHistograms( SPerGameHistograms & histos, const mmaking::SGame & game, const mmaking::SGameEstimDetails & details )
{
  histos.estimFun->AddValue( details.maxValue );
  histos.ratingSpan->AddValue( details.ratingSpan );
  histos.ratingPatternDelta->AddValue( details.ratingPatternDelta );
  histos.ratingTeamAvgDelta->AddValue( details.ratingTeamAvgDelta );

  histos.waitTimeAvg->AddValue( details.waitTimeAvg );

  int winMin = 0, winMax = 0, total = 0;
  float totalForces[2] = { 0, 0 };
  float minForce = 0, maxForce = 0;
  float minPveForce = 0, maxPveForce = 0;
  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    const int tidx = lobby::ETeam::Index( party.common.team );

    Strong<nutils::DataHistogram> waitTotalHisto = histos.wait[tidx];
    Strong<nutils::DataHistogram> waitTotalSergeHisto = histos.waitSerge[tidx];

    Strong<nutils::DataHistogram2D> waitByPartySizeHisto = histos.waitByPartySize[tidx];

    float partyForce = 0;
    for ( int mi = 0; mi < party.members.size(); ++mi )
    {
      const mmaking::SRequestMember & memb = party.members[mi];
      if ( !memb.mmId )
        continue;

      partyForce += memb.force;
      minForce = total ? Min( minForce, memb.force ) : memb.force;
      maxForce = total ? Max( maxForce, memb.force ) : memb.force;
      totalForces[lobby::ETeam::Index(party.common.team)] += memb.force;

      Strong<nutils::DataHistogram> waitByHeroHisto = GetWaitHystoFromMap( histos.waitByHero[tidx], memb.heroId, histos.stdWaitScale );

      //party.common.readyToManoeuvre
      waitTotalHisto->AddValue( party.waitTime );
      waitTotalSergeHisto->AddValue( party.waitTime );
      waitByPartySizeHisto->AddValue( party.members.size(), party.waitTime );

      waitByHeroHisto->AddValue( party.waitTime );

      histos.wins->AddValue( memb.totalWins );

      winMin = total ? Min( winMin, memb.totalWins ) : memb.totalWins;
      winMax = total ? Max( winMax, memb.totalWins ) : memb.totalWins;

      ++total;
    }

    partyForce /= party.members.size();
    partyForce = Clamp( partyForce, (float)mmData->db->forceScale.low, (float)mmData->db->forceScale.high );

    minPveForce = i ? Min( minPveForce, partyForce ) : partyForce;
    maxPveForce = i ? Max( maxPveForce, partyForce ) : partyForce;
  }

  float avgForceDelta = fabs( totalForces[1] - totalForces[0] ) / ( total * 0.5f );

  if ( mmData->map->mapType == NDb::MAPTYPE_COOPERATIVE )
    histos.forceSpan->AddValue( maxPveForce - minPveForce );
  else
    histos.forceSpan->AddValue( maxForce - minForce );

  histos.avgForceDelta->AddValue( avgForceDelta );

  int winSpan = winMax - winMin;
  histos.winsSpan->AddValue( winSpan );
}


SPerGameHistograms & Statistics::GetThatHistos( int rank )
{
  return rankedHistograms[rank];
}



SPerGameHistograms & Statistics::GetThatHistosByRating( int rating, mmaking::EBasket::Enum basket )
{
  int rank = ( basket == mmaking::EBasket::Newbie ) ? 0 : mmData->ranks->FindRank( rating )->index;
  return GetThatHistos( rank );
}



void Statistics::OutputBasketHistos( const SPerGameHistograms & histos, const string & rangeTitle, TReport & report ) const
{
  OutputHistogram( histos.estimFun, "estim_fun", rangeTitle, rangeTitle, "Значение оценочной функции", 2, report );
  OutputHistogram( histos.ratingSpan, "rating_span", rangeTitle, rangeTitle, "Разброс рейтинга игроков, макс-мин", 0, report );
  OutputHistogram( histos.ratingPatternDelta, "rating_pattern_delta", rangeTitle, rangeTitle, "Разница сортированного рейтинга", 0, report );
  OutputHistogram( histos.ratingTeamAvgDelta, "rating_team_avg_delta", rangeTitle, rangeTitle, "Разброс среднего рейтинга игроков обеих команд", 0, report );
  OutputHistogram( histos.forceSpan, "force_span", rangeTitle, rangeTitle, "Разброс форса игроков, макс-мин", 0, report );
  OutputHistogram( histos.avgForceDelta, "avg_force_delta", rangeTitle, rangeTitle, "Разница среднего форса команд", 0, report );

  OutputHistogram( histos.waitTimeAvg, "wait_game_avg", rangeTitle, rangeTitle, "Среднее геометрическое времени ожидания", 0, report );

  for ( int ti = 0; ti < 2; ++ti ) {
    const char * fact = ti ? "B" : "A";

    histos.waitByPartySize[ti]->DumpFreq( NI_STRFMT( "wait%d_by_party", ti + 1 ), rangeTitle );

    {
      nutils::DataHistogram::THistogramsPack histoPack;
      for ( std::map<string, Strong<nutils::DataHistogram>>::const_iterator it = histos.waitByHero[ti].begin(); it != histos.waitByHero[ti].end(); ++it ) {
        string id = NI_STRFMT( "wait%d_hero_%s", ti + 1, it->first );
        string descr = NI_STRFMT( "Время ожидания, фракция %s, герой %s", fact, it->first );
        ReportHistogram( it->second, id, rangeTitle, descr, 0, report );
        histoPack.push_back( pair<string, Strong<nutils::DataHistogram>>( it->first, it->second ) );
      }
      nutils::DataHistogram::WritePackAsCsv( histoPack, NI_STRFMT( "wait%d_by_hero", ti + 1 ), rangeTitle );
    }

    {
      string id = NI_STRFMT( "wait%d_removed", ti + 1 );
      string descr = NI_STRFMT( "Время ожидания перед отменой, фракция %s", fact );
      OutputHistogram( histos.removedWait[ti], id, rangeTitle, rangeTitle, descr, 0, report );
    }

    {
      string id = NI_STRFMT( "wait%d_removed_no_man", ti + 1 );
      string descr = NI_STRFMT( "Время ожидания перед отменой, фракция %s, с отключенными маневрами", fact );
      OutputHistogram( histos.removedWaitNoManoeuvres[ti], id, rangeTitle, rangeTitle, descr, 0, report );
    }

    {
      string id = NI_STRFMT( "wait%d", ti + 1 );
      string descr = NI_STRFMT( "Время ожидания, фракция %s", fact );
      OutputHistogram( histos.wait[ti], id, rangeTitle, rangeTitle, descr, 0, report );
    }

    {
      string id = NI_STRFMT( "wait%d_serge", ti + 1 );
      string descr = NI_STRFMT( "Время ожидания, фракция %s", fact );
      OutputHistogram( histos.waitSerge[ti], id, rangeTitle, rangeTitle, descr, 0, report );
    }
  }

  OutputHistogram( histos.wins, "wins", rangeTitle, rangeTitle, "Общее количество побед", 0, report );
  OutputHistogram( histos.winsSpan, "wins_span", rangeTitle, rangeTitle, "Разброс количество побед в игре", 0, report );
}



void Statistics::ReportHistogram( const nutils::DataHistogram * histo, const string & id, const string & reportSection, const string & descr, int precision, TReport & report ) const
{
  nutils::DataHistogram::SInfo info = histo->Info();
  report.push_back( ReportItem( info, id, reportSection, descr ) );
}



void Statistics::OutputHistogram( const nutils::DataHistogram * histo, const string & id, const string & reportSection, const string & subfolder, const string & descr, int precision, TReport & report ) const
{
  ReportHistogram( histo, id, reportSection, descr, precision, report );
  histo->Output( subfolder, id, settings.imgWidth, settings.imgHeight, precision );
}



static std::string Flt2Csv( double f )
{
  char buf[128]="";
  _gcvt( f, 6, buf );
  for ( int j = 0; buf[j]; ++j )
    if ( buf[j] == '.' )
      buf[j] = ',';
  return buf;
}



void Statistics::WriteReport( const TReport & report )
{
  FILE * f = fopen( "results/report.csv", "wt" );
  if ( !f )
    return;

  fprintf( f, "Id;Suffix;Min;Average;Max;Count;Description\n" );

  for ( TReport::const_iterator it = report.begin(); it != report.end(); ++it )
  {
    const ReportItem & item = *it;

    fprintf( f, "%s;%s;%s;%s;%s;%d;%s\n", item.id.c_str(), item.section.c_str(),
      Flt2Csv(item.info.minVal).c_str(), Flt2Csv(item.info.average).c_str(), Flt2Csv(item.info.maxVal).c_str(),
      item.info.count, item.descr.c_str() );
  }

  fclose( f );
}



void Statistics::WriteRatingForce() const
{
  FILE * f = fopen( "results/rating_force.csv", "wt" );
  if ( !f )
    return;

  fprintf( f, "Rating;Force\n" );

  for ( RatingForceData::const_iterator it = ratingForceData.begin(); it != ratingForceData.end(); ++it ) {
    const RatingForce & item = *it;
    fprintf( f, "%d;%s\n", item.rating, Flt2Csv( item.force ).c_str() );
  }

  fclose( f );
}



inline const char * HeroClassName( int classIdx ) {
  return NDb::KnownEnum<NDb::MMakingHeroClassEnum>::ToString( (NDb::MMakingHeroClassEnum)( classIdx ) );
}


void Statistics::WriteHeroClassStats() const
{
  if ( heroClassLog.empty() )
    return;

  double m[mmaking::HeroClassesNumber], mi[mmaking::HeroClassesNumber], ma[mmaking::HeroClassesNumber];
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i ) {
    m[i] = 0;
    mi[i] = 1e6;
    ma[i] = -1e6;
  }
  
  for ( HeroClassLog::const_iterator it = heroClassLog.begin(); it != heroClassLog.end(); ++it )
    for ( int i = 0; i < mmaking::HeroClassesNumber; ++i ) {
      double v = it->classes[i] * 1e-2;
      m[i] += v;
      mi[i] = Min( mi[i], v );
      ma[i] = Max( ma[i], v );
    }

  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    m[i] /= heroClassLog.size();

  double sigma[mmaking::HeroClassesNumber];
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    sigma[i] = 0;

  for ( HeroClassLog::const_iterator it = heroClassLog.begin(); it != heroClassLog.end(); ++it )
    for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
      sigma[i] += sqr( it->classes[i] * 1e-2 - m[i] );

  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    sigma[i] = sqrt( sigma[i] / heroClassLog.size() );


  FILE * f = fopen( "results/hero_classes_dispersion.csv", "wt" );
  if ( !f )
    return;

  fprintf( f, "Class;Min;Avg;Max;Sigma\n" );
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    fprintf( f, "%s;%s;%s;%s;%s\n", HeroClassName( i ), Flt2Csv( mi[i] ).c_str(), Flt2Csv( m[i] ).c_str(), Flt2Csv( ma[i] ).c_str(), Flt2Csv( sigma[i] ).c_str() );
  fclose( f );
}



void Statistics::WriteHeroClassesTeam() const
{
  FILE * f = fopen( "results/hero_classes.csv", "wt" );
  if ( !f )
    return;

  fprintf( f, "Freq" );
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    fprintf( f, ";%s", HeroClassName( i ) );
  fprintf( f, "\n" );

  for (HeroClassEfficiencyTeamData::const_iterator it = heroClassEfficiencyTeamData.begin(); it != heroClassEfficiencyTeamData.end(); ++it ) {
    fprintf( f, "%d", it->second );
    for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
      fprintf( f, ";%s", Flt2Csv( it->first.classes[i] * 1e-2f ).c_str() );
    fprintf( f, "\n" );
  }

  fclose( f );
}



void Statistics::WriteForceRelations() const
{
  FILE * f = fopen( "results/force_relations.csv", "wt" );
  if ( !f )
    return;

  fprintf( f, "Mine;Enemy min;Enemy avg;Enemy max\n" );

  for ( EnemyForceRelation::const_iterator it = enemyForceRelation.begin(); it != enemyForceRelation.end(); ++it )
    fprintf( f, "%s;%s;%s;%s\n", Flt2Csv(it->mine).c_str(), Flt2Csv(it->enemyMin).c_str(), Flt2Csv(it->enemyAvg).c_str(), Flt2Csv(it->enemyMax).c_str() );

  fclose( f );
}



void Statistics::CheckForMinTimestamp( const Timestamp & ts )
{
  if ( !minimalTimestamp.IsValid() || ( TimeDiff( ts, minimalTimestamp ) < 0 ) )
    minimalTimestamp = ts;
}



void Statistics::BuildLocationTable( TLocationIndexTable & locTable, const mmaking::SGeoInfo & geo )
{
  for ( int i = 0; i < geo.pings.size(); ++i ) {
    string l = geo.pings[i].clusterId;
    NStr::ToLower( &l );
    locTable.insert( l );
  }
}



void Statistics::WriteLocationsHeaderToFile( FILE * f, const TLocationIndexTable & locTable )
{
  for ( TLocationIndexTable::const_iterator it = locTable.begin(); it != locTable.end(); ++it ) {
    string id = "Ping_" + *it;
    fprintf( f, "%s%s", ( it == locTable.begin() ) ? "" : ";", id.c_str() );
  }
}



void Statistics::WriteLocationsToFile( FILE * f, const TLocationIndexTable & locTable, const mmaking::SGeoInfo & geo )
{
  for ( TLocationIndexTable::const_iterator it = locTable.begin(); it != locTable.end(); ++it ) {

    int ping = -1;
    for ( int i = 0; i < geo.pings.size(); ++i )
      if ( !stricmp( geo.pings[i].clusterId.c_str(), it->c_str() ) ) {
        ping = geo.pings[i].ping;
        break;
      }
    fprintf( f, "%s%d", ( it == locTable.begin() ) ? "" : ";", ping );
  }
}




void Statistics::WriteRequestCsvHeader( FILE * f, unsigned fields, const TLocationIndexTable & locTable ) const
{
  fprintf( f,
    "Year;Month;Day;Hour;Minute;Second;"
    "ScalarTime;"
    "UserId;ReqId;PartySize;" );

  if ( fields & ECsvFields::GameId )
    fprintf( f, "GameId;GameType;" );

  if ( fields & ECsvFields::Canceled )
    fprintf( f, "Canceled;" );

  if ( fields & ECsvFields::Wait )
    fprintf( f, "Wait;" );

  fprintf( f, "Adornia;Basket;Male;Hero;"
    "GuardRating;PlayerRating;HeroRating;Force;"
    "Locale;" );

  WriteLocationsHeaderToFile( f, locTable );
  fprintf( f, "\n" );
}



void Statistics::WriteRequestToCsv( FILE * f, const SCsvFields & fields, const Timestamp & ts, const mmaking::SRequestCommonData & cmn, const mmaking::SRequestMember & data, const TLocationIndexTable & locTable ) const
{
  fprintf( f, "%d; %d; %d; %d; %d; %d; ", ts.date.year, ts.date.mon, ts.date.day, ts.time.hour, ts.time.minute, ts.time.sec );

  timer::Time timedelta = TimeDiff( ts, minimalTimestamp );
  fprintf( f, " %s;", Flt2Csv( timedelta ).c_str() );

  fprintf( f, "%d; %d; %u; ", data.mmId, fields.reqId, fields.partySize );

  if ( fields.fields & ECsvFields::GameId )
    fprintf( f, "%d; %s; ", fields.gameId, mmaking::EDebugGameType::ToString( fields.dbgGameType ) );

  if ( fields.fields & ECsvFields::Canceled )
    fprintf( f, "%d; ", fields.canceled ? 1 : 0 );

  if ( fields.fields & ECsvFields::Wait )
    fprintf( f, "%s; ", Flt2Csv( fields.wait ).c_str() );

  fprintf( f, "%d; %s; %d; %s; ",
    lobby::ETeam::Index( cmn.team ),
    mmaking::EBasket::ToString( data.basket ),
    data.sex == lobby::ESex::Male ? 1 : 0,
    data.heroId.c_str() );

  fprintf( f, "%d; %d; %d; %d; ",
    data.guardRating,
    data.playerRating,
    data.heroRating,
    (int)( data.force * 10.0 ) );

  fprintf( f, "%s; ", data.geoInfo.locale.c_str()  );

  WriteLocationsToFile( f, locTable, data.geoInfo );

  fprintf( f, "\n" );
}



void Statistics::WriteRequestsLog() const
{
  DebugTrace( "Writing ALL requests..." );

  FILE * f = fopen( "results/all_requests.csv", "wt" );
  if ( !f )
    return;

  TLocationIndexTable locTable;
  for ( TRequestsLog::const_iterator it = requestsLogRaw.begin(); it != requestsLogRaw.end(); ++it )
  {
    Strong<SStatRequestData> data = *it;
    for ( int i = 0; i < data->members.size(); ++i ) {
      const mmaking::SRequestMember & m = data->members[i];
      BuildLocationTable( locTable, m.geoInfo );
    }
  }

  WriteRequestCsvHeader( f, ECsvFields::Wait, locTable );

  for ( TRequestsLog::const_iterator it = requestsLogRaw.begin(); it != requestsLogRaw.end(); ++it )
  {
    Strong<SStatRequestData> data = *it;

    for ( int i = 0; i < data->members.size(); ++i )
    {
      const mmaking::SRequestMember & m = data->members[i];

      SCsvFields flds;
      flds.fields = ECsvFields::Wait;
      flds.reqId = data->reqId;
      flds.wait = data->wait;
      flds.partySize = data->members.size();

      WriteRequestToCsv( f, flds, data->ts, data->cmn, m, locTable );
    }
  }

  fclose( f );
}



void Statistics::WriteFilteredRequestsLog() const
{
  DebugTrace( "Writing filtered requests..." );
  DebugTrace( "%d requests was filtered out, %d left", filteredOutRequestsNumber, filteredRequestsLog.size() );

  FILE * f = fopen( "results/filtered_requests.csv", "wt" );
  if ( !f )
    return;

  TLocationIndexTable locTable;
  for ( TFilteredRequests::const_iterator it = filteredRequestsLog.begin(); it != filteredRequestsLog.end(); ++it )
    BuildLocationTable( locTable, (*it)->data.geoInfo );

  WriteRequestCsvHeader( f, ECsvFields::Canceled, locTable );

  for ( TFilteredRequests::const_iterator it = filteredRequestsLog.begin(); it != filteredRequestsLog.end(); ++it )
  {
    Strong<ReqFilterItem> item = *it;

    SCsvFields flds;
    flds.fields = ECsvFields::Canceled;
    flds.reqId = item->reqId;
    flds.canceled = item->cancelled;
    flds.partySize = 1;

    WriteRequestToCsv( f, flds, item->ts, item->cmn, item->data, locTable );
  }

  fclose( f );
}



void Statistics::WriteGamesLog() const
{
  DebugTrace( "Writing all games (%d)...", gamesLog.size() );

  FILE * f = fopen( "results/all_games.csv", "wt" );
  if ( !f )
    return;

  TLocationIndexTable locTable;
  for ( TGamesLog::const_iterator it = gamesLog.begin(); it != gamesLog.end(); ++it )
  {
    GameLogEntry * game = *it;
    for ( int pi = 0; pi < game->Data().humans.size(); ++pi ) {
      const mmaking::SGameParty & pty = game->Data().humans[pi];
      for ( int mi = 0; mi < pty.members.size(); ++mi )
        BuildLocationTable( locTable, pty.members[mi].geoInfo );
    }
  }

  WriteRequestCsvHeader( f, ECsvFields::GameId | ECsvFields::Wait, locTable );

  int gameIdx = 0;
  mmaking::TRequestUId fakeReqId = 1;
  for ( TGamesLog::const_iterator it = gamesLog.begin(); it != gamesLog.end(); ++it )
  {
    GameLogEntry * game = *it;

    for ( int pi = 0; pi < game->Data().humans.size(); ++pi )
    {
      const mmaking::SGameParty & pty = game->Data().humans[pi];
      for ( int mi = 0; mi < pty.members.size(); ++mi )
      {
        const mmaking::SRequestMember & m = pty.members[mi];

        SCsvFields flds;
        flds.fields = ECsvFields::GameId | ECsvFields::Wait;
        flds.reqId = fakeReqId;
        flds.gameId = gameIdx;
        flds.dbgGameType = game->Data().debugGameType;
        flds.wait = pty.waitTime;
        flds.partySize = pty.members.size();

        WriteRequestToCsv( f, flds, game->Ts(), pty.common, m, locTable );
      }

      ++fakeReqId;
    }

    ++gameIdx;
  }

  fclose( f );
}



void Statistics::Postprocess()
{
  for ( int i = 0; i < 2; ++i )
  {
    if ( totalGameMembers[i] ) {
      avgWait[i] /= (timer::Time)totalGameMembers[i];
      avgTeamRating[i] /= (unsigned long long)totalGameMembers[i];
    }

    if ( totalRemoved[i] )
      avgRemovedWait[i] /= (timer::Time)totalRemoved[i];
  }

  for ( TFilteredRequests::const_iterator it = filteredRequestsLog.begin(); it != filteredRequestsLog.end(); ++it )
  {
    Strong<ReqFilterItem> item = *it;

    int tidx = lobby::ETeam::Index( item->cmn.team);

    heroRatingHisto[tidx]->AddValue( item->data.heroRating );
    playerRatingHisto[tidx]->AddValue( item->data.playerRating );

    if ( item->cancelled ) {
      heroRatingCanceledHisto[tidx]->AddValue( item->data.heroRating );
      playerRatingCanceledHisto[tidx]->AddValue( item->data.playerRating );
    }

    forceHisto[tidx]->AddValue( item->data.force );
    ratingForceData.push_back( RatingForce( item->data.heroRating, item->data.force ) );

    heroRatingByHourHisto->AddValue( item->ts.time.hour, item->data.heroRating );
  }
}



void Statistics::Output() const
{
  TReport report;

  _mkdir( "results" );
  _mkdir( "total" );

  report.push_back( ReportItem( nutils::DataHistogram::SInfo( mixedNoobGames, 0, 0, 0 ), "mixed_noob_games", "", "Количество смешанных нубоигр" ) );

  for ( int i = 0; i < 2; ++i ) {
    string idx = NI_STRFMT( "%d", i + 1 );
    OutputHistogram( heroRatingHisto[i], "rating" + idx, "", "results", "Рейтинг героя игроков фракции " + idx, 0, report );
    OutputHistogram( heroRatingCanceledHisto[i], "canceled_rating" + idx, "", "results", "Рейтинг героя игроков фракции " + idx + "(отмененные запросы)", 0, report );
    OutputHistogram( playerRatingHisto[i], "player_rating" + idx, "", "results", "Рейтинг аккаунта игроков фракции " + idx, 0, report );
    OutputHistogram( playerRatingCanceledHisto[i], "canceled_player_rating" + idx, "", "results", "Рейтинг аккаунта игроков фракции " + idx + "(отмененные запросы)", 0, report );
    OutputHistogram( forceHisto[i], "force" + idx, "", "results", "Форс игроков фракции " + idx, 0, report );
  }

  heroRatingByHourHisto->DumpFreq( "rating_by_hour", "results" );
  ratingSpanByHeroRating->DumpFreq( "rating_span_by_rating", "results" );

  OutputHistogram( avgForceDelta, "avg_force_abs_delta", "", "results", "Разница форса команд", 0, report );
  for ( AvgForceDeltaByForce::const_iterator it = avgForceDeltaByForce.begin(); it != avgForceDeltaByForce.end(); ++it ) {
    string id = NI_STRFMT( "avg_force_abs_delta_%d", (int)it->force0 );
    string descr = NI_STRFMT( "Разница форса команд: f=%d...%d", (int)it->force0, (int)it->force1 );
    OutputHistogram( it->histo, id, "", "results", descr, 0, report );
  }

  OutputHistogram( timeoutRatingHisto, "timed_out_rating", "", "results", "Рейтинг игроков, не дождавшихся ММ", 0, report );

  OutputBasketHistos( totalHistograms, "total", report );
  for( std::map<int, SPerGameHistograms>::const_iterator it = rankedHistograms.begin(); it != rankedHistograms.end(); ++it )
  {
    int rank = it->first;
    const mmaking::RankDescription * rankDescr = mmData->ranks->FindRankByIndex( rank );
    string id = NI_STRFMT( "rank%02d_%s", rank, rankDescr->name );
    _mkdir( id.c_str() );
    OutputBasketHistos( it->second, id.c_str(), report );
  }

  MessageTrace( "Total users: %d vs %d", totalMembers[0], totalMembers[1] );
  MessageTrace( "Unique users: %d vs %d", uniqueUserIds[0].size(), uniqueUserIds[1].size() );
  if ( totalMembers[0] && totalMembers[1] )
    MessageTrace( "Total ladies percent: %d%% vs %d%%", 100 * totalLadies[0] / totalMembers[0], 100 * totalLadies[1] / totalMembers[1] );
  if ( uniqueUserIds[0].size() && uniqueUserIds[1].size() ) 
    MessageTrace( "Unique ladies percent: %d%% vs %d%%", 100 * uniqueLadies[0].size() / uniqueUserIds[0].size(), 100 * uniqueLadies[1].size() / uniqueUserIds[1].size() );
  MessageTrace( "Removed requests: %d vs %d", totalRemoved[0], totalRemoved[1] );
  MessageTrace( "Games total: %d", totalGames );
  MessageTrace( "Avg wait time: %.1f vs %.1f", avgWait[0], avgWait[1] );
  MessageTrace( "Avg removed wait time: %.1f vs %.1f", avgRemovedWait[0], avgRemovedWait[1] );
  MessageTrace( "Avg rating: %u vs %u", avgTeamRating[0], avgTeamRating[1] );
  MessageTrace( "Team1 hero usage: %i", HeroUsageToString( usedHeroes[0] ) );
  MessageTrace( "Team2 hero usage: %i", HeroUsageToString( usedHeroes[1] ) );

  MessageTrace( "Hero class team data: %d pcs", heroClassEfficiencyTeamData.size() );

  WriteReport( report );
  waitTimeByRating->Write( "results/wait_by_rating.csv" );

  WriteRatingForce();

  WriteHeroClassStats();
  WriteHeroClassesTeam();
  WriteForceRelations();
  WriteRequestsLog();
  WriteFilteredRequestsLog();
  WriteGamesLog();
}



void Statistics::RegisterHeroId( const string & heroid )
{
  THeroUsage::iterator it = heroIds.find( heroid );
  if ( it != heroIds.end() )
    return;

  int id = heroIds.size() + 1;
  heroIds[heroid] = id;
}



void Statistics::CountHeroUsage( lobby::ETeam::Enum team, const string & heroid )
{
  int tidx = lobby::ETeam::Index( team );
  usedHeroes[tidx][heroid] += 1;
}



int Statistics::FindHeroId( const string & heroid ) const
{
  THeroUsage::const_iterator it = heroIds.find( heroid );
  NI_VERIFY( it != heroIds.end(), NI_STRFMT( "Unknown hero '%s'", heroid ), return 0 );
  return it->second;
}



string Statistics::HeroUsageToString( const THeroUsage & usage )
{
  map<int, string> preformat;
  for ( THeroUsage::const_iterator it = usage.begin(); it != usage.end(); ++it )
    preformat[-it->second] = it->first;
  return NI_STRFMT( "%i", preformat );
}



void Statistics::EvalForceDeltas( const mmaking::SGame & game )
{
  float forces[2] = { 0.0f, 0.0f };
  int count[2] = { 0, 0 };

  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    int tidx = lobby::ETeam::Index( party.common.team );

    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      const mmaking::SRequestMember & memb = party.members[mi];

      if ( !memb.mmId )
        return;

      forces[tidx] += memb.force;
      ++count[tidx];
    }
  }

  if ( count[0] != count[1] )
    return;
  if ( !count[0] || !count[1] )
    return;

  forces[0] /= count[0];
  forces[1] /= count[1];

  const float deltaForce = forces[1] - forces[0];
  avgForceDelta->AddValue( deltaForce );

  float avgF = 0.5f * (forces[0] + forces[1] );

  for ( AvgForceDeltaByForce::iterator it = avgForceDeltaByForce.begin(); it != avgForceDeltaByForce.end(); ++it )
    if ( ( it->force0 < avgF ) && ( avgF < it->force1 ) )
      it->histo->AddValue( deltaForce );
}



void Statistics::CollectForceRelations( const mmaking::SGame & game )
{
  EnemyForceRelationItem forceRel[2] = { 
    EnemyForceRelationItem( 0, 0, 1e6, -1e6 ),
    EnemyForceRelationItem( 0, 0, 1e6, -1e6 )
  };

  int count[2] = { 0, 0 };

  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    int tidx = lobby::ETeam::Index( party.common.team );

    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      const mmaking::SRequestMember & memb = party.members[mi];

      if ( !memb.mmId )
        return;

      forceRel[tidx].enemyAvg += memb.force;
      forceRel[tidx].enemyMin = Min( forceRel[tidx].enemyMin, memb.force );
      forceRel[tidx].enemyMax = Max( forceRel[tidx].enemyMax, memb.force );
      count[tidx] += 1;
    }
  }

  for ( int i = 0; i < 2; ++i )
    if ( count[i] )
      forceRel[i].enemyAvg /= (float)count[i];

  for ( int i = 0; i < game.humans.size(); ++i )
  {
    const mmaking::SGameParty & party = game.humans[i];
    int enemy_tidx = lobby::ETeam::Index( lobby::ETeam::Invert( party.common.team ) );

    for ( int mi = 0; mi < party.members.size(); ++mi ) {
      const mmaking::SRequestMember & memb = party.members[mi];
      if ( !memb.mmId )
        return;

      EnemyForceRelationItem item( forceRel[enemy_tidx] );
      item.mine = memb.force;

      enemyForceRelation.push_back( item );
    }
  }
}



void Statistics::AddActiveRequest( SStatRequestData * data )
{
  mmaking::TRequestUId reqId = data->reqId;
  Strong<SStatRequestData> & byReqId = activeRequestsByReqId[reqId];
  if ( byReqId.Valid() )
    WarningTrace( "Duplicate reqId %d", reqId );
  byReqId = data;

  for ( int i = 0; i < data->members.size(); ++i ) {
    mmaking::TUserId mmid = data->members[i].mmId;
    Strong<SStatRequestData> & byMmId = activeRequestsByMmId[mmid];
    if ( byMmId.Valid() )
      WarningTrace( "Duplicate mmid %d", mmid );
    byMmId = data;
  }
}



void Statistics::RemoveActiveRequest( SStatRequestData * data )
{
  activeRequestsByReqId.erase( data->reqId );

  for ( int i = 0; i < data->members.size(); ++i )
    activeRequestsByMmId.erase( data->members[i].mmId );
}



Strong<SStatRequestData> Statistics::FindActRequestByReqId( mmaking::TRequestUId reqId )
{
  TActiveRequests::iterator it = activeRequestsByReqId.find( reqId );
  if ( it != activeRequestsByReqId.end() )
    return it->second;
  WarningTrace( "Unknown requestId %d", reqId );
  return 0;
}



Strong<SStatRequestData> Statistics::FindActRequestByMmId( mmaking::TUserId mmId )
{
  TActiveRequests::iterator it = activeRequestsByMmId.find( mmId );
  if ( it != activeRequestsByMmId.end() )
    return it->second;
  //FIXME: Log parser DOES NOT split resulting game into parties (there is not such info in the log).
  //But source AddRequest is parseed WITH parties
  //WarningTrace( "Unknown mmId %d", mmId );
  return 0;
}



void Statistics::FilterRequestsOnAdd( SStatRequestData * data )
{
  for ( int i = 0; i < data->members.size(); ++i )
  {
    const mmaking::SRequestMember & m = data->members[i];
    Strong<ReqFilterItem> & slot = requestsFilter[m.mmId];
    if ( slot )
    {
      timer::Time delta = TimeDiff( data->ts, slot->lastActivity );
      if ( delta < 600.0 )
      {
        slot->lastActivity = data->ts;
        slot->cancelled = false;
        ++filteredOutRequestsNumber;
        continue;
      }
    }

    slot = new ReqFilterItem( data->ts, data->reqId, m, data->cmn );
    filteredRequestsLog.push_back( slot );
  }
}



void Statistics::FilterRequestsOnCancel( const Timestamp & ts, SStatRequestData * data )
{
  for ( int i = 0; i < data->members.size(); ++i )
  {
    TRequestFilterById::iterator it = requestsFilter.find( data->members[i].mmId );
    if ( it == requestsFilter.end() )
      continue;

    Strong<ReqFilterItem> item = it->second;
    item->lastActivity = ts;
    item->cancelled = true;
  }
}



void Statistics::FilterRequestsOnGame( const Timestamp & ts, SStatRequestData * data )
{
  for ( int i = 0; i < data->members.size(); ++i )
  {
    TRequestFilterById::iterator it = requestsFilter.find( data->members[i].mmId );
    if ( it == requestsFilter.end() )
      continue;

    Strong<ReqFilterItem> item = it->second;
    item->lastActivity = ts;
    item->cancelled = false;
  }
}



void WaitTimeByRating::Add( int r, float wait )
{
  int index = ( ( r - minR ) * data.size() ) / ( maxR - minR );
  index = Clamp( index, 0, (int)data.size() - 1 );
  data[index].Add( wait );
}



void WaitTimeByRating::Write( const char * filename )
{
  FILE * f = fopen( filename, "wt" );
  if ( !f )
    return;

  fprintf( f, "Rating;WaitMin;WaitAvg;WaitMax;Count\n" );

  for ( size_t i = 0; i < data.size(); ++i ) {
    int r0 = minR + ( ( maxR - minR ) * i ) / data.size();
    int r1 = minR + ( ( maxR - minR ) * ( i + 1 ) ) / data.size();
    fprintf( f, "[%d...%d];%s;%s;%s;%d\n",
      r0, r1,
      Flt2Csv( data[i].minVal ).c_str(),
      Flt2Csv( data[i].avg ).c_str(),
      Flt2Csv( data[i].maxVal ).c_str(),
      data[i].count );
  }

  fclose( f );
}

} //namespace mm_test

namespace mmaking {

bool operator < ( const mmaking::SHeroClassEfficiency & l, const mmaking::SHeroClassEfficiency & r )
{
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    if ( l.classes[i] < r.classes[i] )
      return true;
    else if ( l.classes[i] > r.classes[i] )
      return false;

  return false;
}



bool operator == ( const mmaking::SHeroClassEfficiency & l, const mmaking::SHeroClassEfficiency & r )
{
  for ( int i = 0; i < mmaking::HeroClassesNumber; ++i )
    if ( l.classes[i] != r.classes[i] )
      return false;
  return true;
}

} //namespace mmaking
