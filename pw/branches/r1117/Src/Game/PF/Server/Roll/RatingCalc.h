#pragma once

#include "Core/GameTypes.h"
#include "Server/Roll/EloRating.h"


namespace NDb
{
  struct RollSettings;
  struct AdvMapDescription;
  struct ModeRollSettings;
}

namespace roll
{

class RatingDeltaCalculator
{
public:
  RatingDeltaCalculator( const NDb::RollSettings * _settings, const NDb::AdvMapDescription * _map ) :
  settings( _settings ),
  map( _map )
  {}

  void AddPlayer( lobby::ETeam::Enum _faction, EloRating::PlayerId _playerId, float _rating, int _partyId );
  bool Calculate( lobby::ETeam::Enum _winnner );
  bool GetDelta( EloRating::PlayerId _uid, float & _delta, bool _modified ) const;

private:
  EloRating::Calculator calc;
  NDb::Ptr<NDb::RollSettings> settings;
  NDb::Ptr<NDb::AdvMapDescription> map;

  float FindDeltaModifier( float _delta, float _rating ) const;
};

} //namespace roll
