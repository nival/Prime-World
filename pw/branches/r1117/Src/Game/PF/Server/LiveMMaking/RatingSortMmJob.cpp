#include "stdafx.h"
#include "RatingSortMmJob.h"


namespace mmaking
{

NI_ENUM_BEGIN_STD( ERatingSortBpType );
  NI_ENUM_ITEM( Normal );
  NI_ENUM_ITEM( LongWait );
  NI_ENUM_ITEM( FullParties );
NI_ENUM_END_STD;



NI_ENUM_BEGIN_STD( ELongWaitMode );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Normal );
  NI_ENUM_ITEM( TooLong );
NI_ENUM_END_STD;



RatingSortSampleSlot::RatingSortSampleSlot( MmRequest * _req, int _wait, bool _mandatory, EBasket::Enum _gameBasket, const NDb::MapMMakingSettings * _sett ) :
req( _req ), waitTimeSec( _wait ),
mandatory( _mandatory ),
size( _req->Size() )
{
  NI_ASSERT( _req->Size() <= MaxConstTeamSz, "" );
  NI_VERIFY( _req->Size(), "", return );

  const int effRating = _req->EffectiveRating( _sett );
  const int effForce = _req->EffectiveForce( _sett );

  for ( int i = 0; i < _req->Size(); ++i )
  {
    const SRequestMemberEx & m = _req->Member( i );

    lobby::ESex::Enum sex = ( m.sex == m.heroSex ) ? m.sex : lobby::ESex::Undefined;
    memb[i] = SMember( sex, m.shortHeroId, m.basket, effRating, effForce, m.loseStreak, m.heroClassEff );
  }
}



void RatingSortDraft::PushBack( int teamIndex, const RatingSortSampleSlot & slot )
{
  lineup[teamIndex].push_back( slot.req );
  lobby::ETeam::Enum faction = lobby::ETeam::Index( teamIndex );
  for ( int i = 0; i < slot.size; ++i ) {
    const RatingSortSampleSlot::SMember & m = slot.memb[i];
    fun.Count( faction, m.sex, m.heroid, m.basket, m.rating, m.force, m.heroClassEff, slot.waitTimeSec, m.loseStreak, slot.mandatory );
  }
}



void RatingSortDraft::PopBack( int teamIndex, const RatingSortSampleSlot & slot )
{
  lineup[teamIndex].pop_back();
  lobby::ETeam::Enum faction = lobby::ETeam::Index( teamIndex );
  for ( int i = slot.size - 1; i >= 0; --i ) {
    const RatingSortSampleSlot::SMember & m = slot.memb[i];
    fun.Uncount( faction, m.sex, m.heroid, m.basket, m.rating, m.force, m.heroClassEff, slot.waitTimeSec, m.loseStreak, slot.mandatory );
  }
}



void RatingSortDraft::CheckOut()
{
  SGameEstimDetails details;
  fun.Get( details, ( longWaitMode == ELongWaitMode::None ) ? 0 : 1 );

  if ( !details.valid )
    return;

#ifdef MATCHMAKING_DEBUG_ESTIM_FUNC
  efMaxValue.Add( details.maxValue );
  efSumValue.Add( details.sumValue );
  efForceSpanTerm.Add( details.forceSpanTerm );
  efHeroClassesTerm.Add( details.heroClassesOptimumTerm );
  efSexTerm.Add( details.sexTerm );
#endif //MATCHMAKING_DEBUG_ESTIM_FUNC

  if ( details.maxValue > 1.0f )
    if ( longWaitMode != ELongWaitMode::TooLong )
      return;

  const float value = details.maxValue + 0.1 * details.sumValue;
  if ( !updates || ( value < minValue ) )
  {
    ++updates;
    minValue = value;
    minValueDetails = details;
    bestLineup[0] = lineup[0];
    bestLineup[1] = lineup[1];
  }
}




void RatingSortJob::Do()
{
  NI_PROFILE_FUNCTION;

  timer::Time start = timer::Now();

  if ( manoeuvresFaction != lobby::ETeam::None )
    iterations = RatingSortFSAlgorithm::FullSweepHomo( sample, draft, teamSize );
  else if ( basePoint.pveFaction != lobby::ETeam::None )
    iterations = RatingSortFSAlgorithm::FullSweepSingleSide( sample, draft, teamSize );
  else
    iterations = RatingSortFSAlgorithm::FullSweepHetero( sample, draft, teamSize );

  timeWasted = timer::Now() - start;

  //Hack just to count iterations in profiler
  //Counting every iteration consumes too mush CPU and RAM
  for ( unsigned i = 0; i < iterations / 1000; ++i ) {
    NI_PROFILE_HEAVY_BLOCK( "1k iterations" );
  }

#ifdef MATCHMAKING_DEBUG_ESTIM_FUNC
  if ( !draft.updates )
    if ( ( basePoint.force >= 140 ) && ( basePoint.force <= 150 ) )
      if ( basePoint.sidesLocale[0] == 1 && basePoint.sidesLocale[1] == 1 )
        if ( sample.Size( lobby::ETeam::Team1 ) + sample.Size( lobby::ETeam::Team2 ) >= 15 )
        {
          DebugTrace( "No valid games. base_force=%d", basePoint.force );
          for ( int tidx = 0; tidx < 2; ++tidx )
            for ( int i = 0; i < sample.Size( lobby::ETeam::Index( tidx ) ); ++i )
            {
              const RatingSortSampleSlot & slot = sample.GetSlot( lobby::ETeam::Index( tidx ), i );
              DebugTrace( "Slot %d: wait=%d, %s", i, slot.waitTimeSec, slot.req->FormatAll() );
            }
          DebugTrace( "Estim fun max val     : %s", draft.efMaxValue.ToString() );
          DebugTrace( "Estim fun sum val     : %s", draft.efSumValue.ToString() );
          DebugTrace( "Estim fun force span  : %s", draft.efForceSpanTerm.ToString() );
          DebugTrace( "Estim fun hero classes: %s", draft.efHeroClassesTerm.ToString() );
          DebugTrace( "Estim fun sex val     : %s", draft.efSexTerm.ToString() );
        }
#endif //MATCHMAKING_DEBUG_ESTIM_FUNC

  if ( basePoint.type == ERatingSortBpType::FullParties )
    if ( !draft.updates )
      DebugTrace( "Full party game rejected!" );
}

} //namespace mmaking
