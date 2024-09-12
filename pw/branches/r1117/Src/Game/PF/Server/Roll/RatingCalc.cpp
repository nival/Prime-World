#include "stdafx.h"
#include "RatingCalc.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "EloRating.h"
#include "Db/DBServer.auto.h"

namespace roll
{

class FullPartyBonus : public EloRating::IPartyRatingBonusCallback, public NonCopyable
{
public:
  FullPartyBonus( const NDb::RollSettings * _settings, int _minFullPartySize ) :
  settings( _settings ),
  minFullPartySize( _minFullPartySize )
  {}

private:
  NDb::Ptr<NDb::RollSettings> settings;
  const int minFullPartySize;

  virtual int PartyRatingBonus( float _partyRating, int _partySize );
};






void RatingDeltaCalculator::AddPlayer( lobby::ETeam::Enum _faction, EloRating::PlayerId _playerId, float _rating, int _partyId )
{
  calc.AddPlayer( _faction, _playerId, _rating, _partyId );
}



bool RatingDeltaCalculator::Calculate( lobby::ETeam::Enum _winnner )
{
  const int minFullPartySize = ( map->matchmakingSettings && map->matchmakingSettings->useRanking && map->rollSettings ) ? ( map->rollSettings->fullPartySize ) : 0;

  FullPartyBonus bonus( settings, minFullPartySize );
  return calc.Calculate( _winnner, &bonus, map );
}



bool RatingDeltaCalculator::GetDelta( EloRating::PlayerId _uid, float & _delta, bool _modified ) const
{
  float rating = 0;
  if ( !calc.GetChange( _uid, _delta, rating ) )
    return false;

  if ( map->rollSettings )
    _delta *= map->rollSettings->ratingChangeMultiplier;

  if ( _modified )
    _delta *= FindDeltaModifier( _delta, rating );

  return true;
}



float RatingDeltaCalculator::FindDeltaModifier( float _delta, float _rating ) const
{
  for ( int i = 0; i < settings->ratingModifiers.size(); i++ )
  {
    const NDb::RatingModifier & modifier = settings->ratingModifiers[i];
    if ( modifier.minValue <= _rating && _rating <= modifier.maxValue )
    {
      if ( _delta >= 0 )
        return modifier.winModifier;
      else
        return modifier.looseModifier;
    }
  }

  return 1.0f;
}



int FullPartyBonus::PartyRatingBonus( float _partyRating, int _partySize )
{
  if ( !minFullPartySize )
    return 0;

  if ( _partySize < minFullPartySize )
    return 0;

  for ( int i = settings->fullPartyRatingModifiers.size() - 1; i >= 0 ; --i )
    if ( _partyRating >= settings->fullPartyRatingModifiers[i].minRating )
      return settings->fullPartyRatingModifiers[i].ratingBonus;
  return 0;
}

} //namespace roll
