#include "stdafx.h"
#include "RatingSortMmStat.h"
#include "MMakingUniStat.h"
#include "MMakingLog.h"


namespace mmaking
{

void RatingSortStatistics::OnBpCycleStart( timer::Time _now )
{
  timer::Time cycleDuration = _now - ( lastBasePointCycleStartTime ? lastBasePointCycleStartTime : _now );
  lastBasePointCycleStartTime = _now;

  uniStats->AddStat( "BasePointCycle", cycleDuration * 1e3 );
}



void RatingSortStatistics::OnGame( ERatingSortBpType::Enum _bpType, ELongWaitMode::Enum _longWaitMode, lobby::ETeam::Enum _manoeuvresFaction )
{
  uniStats->AddStat( "Game", 0 );

  if ( _bpType == ERatingSortBpType::LongWait )
    uniStats->AddStat( "GameLongWait", 0 );
  else if ( _bpType == ERatingSortBpType::FullParties )
    uniStats->AddStat( "GameFullParty", 0 );
  if ( _longWaitMode == ELongWaitMode::TooLong )
    uniStats->AddStat( "GameWaitTooLong", 0 );
  if ( _manoeuvresFaction != lobby::ETeam::None )
    uniStats->AddStat( "GameManoeuvres", 0 );

  ++gamesDone;

  if ( _bpType == ERatingSortBpType::LongWait )
    ++longWaitGames;
  else if ( _bpType == ERatingSortBpType::FullParties )
    ++fullPartyGames;

  if ( _longWaitMode == ELongWaitMode::TooLong )
    ++waitTooLongGames;

  if ( _manoeuvresFaction != lobby::ETeam::None )
    ++manoeuvresGames;
}



void RatingSortStatistics::Dump( Loger * loger, timer::Time _now, timer::Time _currentlyInProMode )
{
  timer::Time proModeTime = timeInProMode + _currentlyInProMode;

  loger->Log( ELogLevel::Normal, "Tech info: %d games done, %d manoeuvres, %d long wait games, %d wait too long games, %u full party games",
    gamesDone, manoeuvresGames,
    longWaitGames, waitTooLongGames,
    fullPartyGames );

  loger->Log( ELogLevel::Normal, "Tech info: %d samples made, %.1f sec in pro mode(%d%%)",
    samplesMade,
    proModeTime, (int)( 1e2f * proModeTime / _now ) );
}

} //namespace mmaking
