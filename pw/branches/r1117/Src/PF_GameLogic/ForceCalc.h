#pragma once

#include "PFMaleHero.h"
#include "PFTalent.h"

namespace NWorld
{

class PFBaseHero;
class PFBaseMaleHero;

namespace Force
{

  float CalcHeroStatsBonusBudget( PFBaseMaleHero const* pHero, int level );
  float CalcStatsTotalBonusBudget( const float force, NDb::Ptr<NDb::ForceParameters> const& dbForceParams );
  void CalcHeroAbilityCostFactor( PFBaseMaleHero const* pHero, float& manaCostMod, float& lifeCostMod );

  struct TalentsForceCalculator : public ITalentCalculator, public NonCopyable
  {
    TalentsForceCalculator( const NDb::AILogicParameters* aiParams );

    virtual void operator()( NDb::Ptr<NDb::Talent> const& pDBTalent, int level, const PFTalentsSet::SlotInfo& slot );
    float GetResult();

  private:
    const NDb::AILogicParameters* pAIParams;
    float force;
  };

  // Calculate coeff to map habitants' stats
  struct MapStatsCoeffCalculator : public NonCopyable
  {
    MapStatsCoeffCalculator( NDb::Ptr<NDb::ForceParameters> const& _forceParameters, float _forceOfMap, bool _humanPlayersOnly );

    void operator()(PFBaseHero const& hero);
    float GetForce();
    float GetResult();

  private:
    float force;
    float forceOfMap;
    bool findMinimum;
    int heroesCount;
    bool humanPlayersOnly;
    NDb::Ptr<NDb::ForceParameters> const& forceParameters;
  };


  float CalculateForce(const NWorld::PFBaseMaleHero* pHero);
  float CalculateForce(const NCore::PlayerInfo&  playerInfo,
                  bool usePlayerInfoTalentSet,
                  const PFResourcesCollection* pResourceCollection,
                  const NDb::AdvMapDescription* advMapDescription);
}
}