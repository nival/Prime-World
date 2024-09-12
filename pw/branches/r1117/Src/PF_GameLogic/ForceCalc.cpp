#include "stdafx.h"
#include "ForceCalc.h"
#include "PFMaleHero.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "PFTalent.h"
#include "DBTalent.h"
#include "HeroSpawn.h"

namespace NWorld
{

namespace Force
{

  // Calculation of force by talent set and persistent stats
  float CalculateForce(const NCore::PlayerInfo&  playerInfo,
    bool usePlayerInfoTalentSet,
    const PFResourcesCollection* pResourceCollection,
    const NDb::AdvMapDescription* advMapDescription) 
  {
    NI_ASSERT(pResourceCollection, "Force::Calculate: pResourceCollection is NULL");

    const NDb::SessionLogicRoot* pRoot = NDb::SessionRoot::GetRoot()->logicRoot; 
    NI_ASSERT(pRoot, "Force::Calculate: AI Logic Root is NULL");

    NDb::Ptr<NDb::HeroesDB> pHeroes = pRoot->heroes;

    const NDb::Hero * dbHero = NWorld::FindHero( pHeroes, advMapDescription, playerInfo.heroId );
    NI_VERIFY( dbHero, NStr::StrFmt( "Invalid hero id '0x%0X' assigned to player!", playerInfo.heroId ), return 0 );


    PFTalentsSet::SetInfo info;
    float force = PFTalentsSet::PreloadTalentsSetAndCalcForce( pRoot->aiLogic, 
      dbHero, usePlayerInfoTalentSet, pResourceCollection,
      playerInfo, info);
    PFBaseMaleHero::TPersistentStats persistentStats;
    PFBaseMaleHero::FillPersistentStats( playerInfo, persistentStats );
    PFBaseMaleHero::ModifyForceByStats( persistentStats, pRoot->aiLogic, force );

    return force;
  }

  float CalculateForce(const NWorld::PFBaseMaleHero* pHero) 
  {
    const NDb::SessionLogicRoot* pRoot = NDb::SessionRoot::GetRoot()->logicRoot; 
    NI_ASSERT(pRoot, "Force::Calculate: AI Logic Root is NULL");

    NWorld::PFTalentsSet*  talentSet = pHero->GetTalentsSet();

    TalentsForceCalculator calculator(pRoot->aiLogic);
    talentSet->CalculateForce(calculator);
    
    float force = calculator.GetResult();
    force += pRoot->aiLogic->forceParameters->baseHeroForce;
    PFBaseMaleHero::ModifyForceByStats( pHero->GetPersistentStats(), pRoot->aiLogic, force );

    return force;
  }

  // Calculation of force compensation budget
  float CalcHeroStatsBonusBudget( PFBaseMaleHero const* pHero, int level )
  {
    if ( !IsValid( pHero ) )
      return 0.0f;

    NDb::Ptr<NDb::ForceParameters> const& dbForceParams = pHero->GetWorld()->GetAIWorld()->GetAIParameters().forceParameters;
    NI_DATA_VERIFY( !dbForceParams.IsEmpty(), "forceParameters is empty", return 0.0f );

    // count total devpoints for level
    int devpointsPerLevel = 0;
    for ( int slot = 0; slot < PFTalentsSet::SLOTS_COUNT; ++slot )
    {
      PFTalent const* talent = pHero->GetTalent( level, slot );
      if ( talent )
      {
        devpointsPerLevel += talent->GetDevPoints();
      }
    }
    NI_ASSERT( devpointsPerLevel > 0, "Zero devpoints per level" );

    const float percent = dbForceParams->talentLevelBonusPercent[level] / devpointsPerLevel * 0.01f;

    return CalcStatsTotalBonusBudget( pHero->GetForce(), dbForceParams ) * percent;
  }

  float CalcStatsTotalBonusBudget( const float force, NDb::Ptr<NDb::ForceParameters> const& dbForceParams )
  {
    NI_DATA_VERIFY( !dbForceParams.IsEmpty(), "forceParameters is empty", return 0.0f );

    float statsBonusBudget = dbForceParams->defaultStatBonus;
    if ( force > dbForceParams->defaultBaseForce )
    {
      statsBonusBudget += ( force - dbForceParams->defaultBaseForce ) * dbForceParams->statBonusByForce;
    }
    return statsBonusBudget;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void CalcHeroAbilityCostFactor( PFBaseMaleHero const* pHero, float& manaCostMod, float& lifeCostMod )
  {
    if ( !IsValid( pHero ) )
      return;

    NDb::Ptr<NDb::ForceParameters> const& dbForceParams = pHero->GetWorld()->GetAIWorld()->GetAIParameters().forceParameters;
    NI_DATA_VERIFY( !dbForceParams.IsEmpty(), "forceParameters is empty", return );

    const float forceDiff = pHero->GetForce() - dbForceParams->defaultBaseForce;
    if ( forceDiff <= 0.0f )
    {
      manaCostMod = 1.0f;
      lifeCostMod = 1.0f;
      return;
    }

    const float coreEnergy = pHero->GetCoreEnergy();
    const float coreLife   = pHero->GetCoreLife();

    const float acquiredBudgetPercent = pHero->GetTalentsAcquiredBudgetPercent();
    const PFStatContainer* statCont = pHero->GetStatContainer();

    const float statShiftFactor = forceDiff * dbForceParams->statBonusByForce * acquiredBudgetPercent / statCont->GetTotalIncrementBudget();
    const float energyShift = statCont->GetStatIncrement( NDb::STAT_ENERGY ) * statShiftFactor;
    const float lifeShift   = statCont->GetStatIncrement( NDb::STAT_LIFE )   * statShiftFactor;
    
    if ( coreEnergy - energyShift > EPS_VALUE )
      manaCostMod = coreEnergy / ( coreEnergy - energyShift );
    else
      manaCostMod = 1.0f;

    if ( coreLife - lifeShift > EPS_VALUE )
      lifeCostMod = coreLife / ( coreLife - lifeShift );
    else
      lifeCostMod = 1.0f;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TalentsForceCalculator::TalentsForceCalculator( const NDb::AILogicParameters* aiParams )
    : pAIParams(aiParams)
    , force(0.0f)
  {}

  void TalentsForceCalculator::operator()( NDb::Ptr<NDb::Talent> const& pDBTalent, int level, const PFTalentsSet::SlotInfo& slot )
  {
    float budget = pDBTalent->budget;
    NDb::Ptr<NDb::ForceParameters> pForceParams = pAIParams->forceParameters;
    if (budget < 0)
      budget = PFTalent::CalcBudget(pAIParams, slot.refineRate, level, pDBTalent->rarity);
    
    if ( pDBTalent->rarity != NDb::TALENTRARITY_CLASS )
    {
      budget /= 1.0f + pForceParams->talentLevelForceModifiers[level] * 0.01f;
    }
    else
    {
      budget /= 1.0f + pForceParams->classTalentLevelForceModifiers[level] * 0.01f;
    }
    
    force += budget + pForceParams->talentRarityForceSummand[pDBTalent->rarity];
  }

  float TalentsForceCalculator::GetResult()
  {
    return force;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  MapStatsCoeffCalculator::MapStatsCoeffCalculator( NDb::Ptr<NDb::ForceParameters> const& _forceParameters, float _forceOfMap, bool _humanPlayersOnly )
    : forceParameters( _forceParameters )
    , heroesCount(0)
    , forceOfMap(_forceOfMap)
    , humanPlayersOnly(_humanPlayersOnly)
  {
    findMinimum = _forceParameters->teamForceCalcMethod == NDb::TEAMFORCECALCMETHOD_MINIMUM;
    force = findMinimum ? MAX_FLOAT : 0.0f;
  }

  void MapStatsCoeffCalculator::operator()(PFBaseHero const& hero)
  {
    if ( humanPlayersOnly && ( !hero.GetPlayer() || hero.GetPlayer()->IsBot() ) )
      return;

    ++heroesCount;

    float heroForce = hero.GetForce( false );

    if(heroForce > forceParameters->maxHeroForce)
      heroForce = forceParameters->maxHeroForce;

    // Don't count persistent stats in hero force
    if ( !findMinimum )
    {
      force += heroForce;
    }
    else if ( hero.GetForce() < force )
    {
      force = heroForce;
    }
  }

  float MapStatsCoeffCalculator::GetForce()
  {
    return findMinimum ? force : force / heroesCount;
  }

  float MapStatsCoeffCalculator::GetResult()
  {
    if ( GetForce() < forceOfMap )
      return 1.0;

    return 1.0f + ( GetForce() / forceOfMap - 1.0f ) * forceParameters->mapHabitantsStatsMultiplier;
  }
}
}