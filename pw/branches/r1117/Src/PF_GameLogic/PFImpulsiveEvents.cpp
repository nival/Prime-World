#include "stdafx.h"

#include "PFImpulsiveEvents.h"
#include "PFHero.h"
#include "PFAbilityData.h"
#include "PFEaselPlayer.h"
#include "PFAIWorld.h"
#include "PFImpulsiveBuffs.h"
#include "PFWorldNatureMap.h"
#include "PFTalent.h"

namespace NWorld
{

  namespace
  {

    //////////////////////////////////////////////////////////////////////////
    struct EnemyFinder
    {
      inline static int Count( PFBaseUnit* pUnit, float maxDistance, NDb::ESpellTarget unitTypes, bool treatNeutralAsHostile )
      {
        NI_ASSERT( pUnit && pUnit->GetWorld() && pUnit->GetWorld()->GetAIWorld(), "Invalid unit!" );

        EnemyFinder finder;
        
        int factions = pUnit->GetOppositeFactionFlags();
        if( treatNeutralAsHostile )
          factions |= NDb::FACTION_NEUTRAL;
        else
          factions &= ~NDb::FACTION_NEUTRAL;

        int types = unitTypes; 
        types &= ~( NDb::SPELLTARGET_ALLY | NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_SELF | NDb::SPELLTARGET_LAND);
        types |= NDb::SPELLTARGET_FLYING; // always count flying targets
        
        pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange(pUnit->GetPosition(), maxDistance, finder, UnitMaskingPredicate( factions, types ) );
        
        return finder.count;
      }
      // ~~~
      inline void operator ()(PFBaseUnit &unit) { if( !unit.IsDead() ) ++count; }
    private:
      EnemyFinder() : count(0) {}
      int count;
    };
    
    inline int NormalizeTargetFlags(NDb::ESpellTarget targets)
    {
      int flags = targets;
      flags &= ~( NDb::SPELLTARGET_ALLY | NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_LAND );
      flags |= NDb::SPELLTARGET_FLYING; // always count flying targets
      return flags;
    }

    template<typename T>
    struct VectorCollector
    {
      vector<T const*> objects;
      void operator () ( T const& arg ) { objects.push_back( &arg ); }
    };
    
    struct Counter
    {
      mutable int count;
      explicit Counter() : count(0) {}
      void operator () ( ... ) const { ++count; }
    };

    class UnitSelector
    {
      bool acceptSelf;
      CPtr<PFBaseUnit> pSelf;
      UnitMaskingPredicate predicate;
    public:
      UnitSelector(int factionMask, int unitTypeMask, PFBaseUnit * pSelf, bool acceptSelf)
        : predicate( factionMask, unitTypeMask, pSelf )
        , pSelf(pSelf)
        , acceptSelf(acceptSelf)
      {
      }

      bool operator () ( PFLogicObject const& unit ) const
      {
        if( !predicate(unit) || unit.IsDead() )
          return false;

        if( !acceptSelf && &unit == pSelf )
          return false;

        if( unit.IsHero() )
        {
          // exclude clones from selection
          const PFBaseHero* pHero = dynamic_cast<const PFBaseHero*>(&unit);
          if( pHero && pHero->IsClone() )
            return false;
        }

        return true;
      }
    };

    class UnitCollector
    {
    public:
      static void Collect( CPtr<PFBaseUnit> const& pUnit, float range, NDb::ESpellTarget targets, NDb::EFactionFlags factions, bool acceptSelf, vector<CPtr<PFBaseUnit> >* pResult)
      {
        NI_VERIFY( pUnit && pUnit->GetWorld() && pUnit->GetWorld()->GetAIWorld(), "Invalid hero!", return );
        NI_VERIFY( pResult, "Invalid argument!", return; )
        
        int factionFlags = pUnit->GetFactionMask(factions);
        int typeFlags    = NormalizeTargetFlags(targets); 
        
        UnitCollector collector(pUnit, acceptSelf);
        pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange(pUnit->GetPosition(), range, collector, UnitMaskingPredicate( factionFlags, typeFlags, pUnit ) );

        pResult->swap(collector.units);
      }

      void operator ()(PFBaseUnit& unit) 
      {
        if( unit.IsDead() )
          return;

        if( !acceptSelf && unit.IsHero() && &unit == pSelf )
          return;

        units.push_back(&unit);
      }
    private:
      UnitCollector(CPtr<PFBaseUnit> const& pSelf, bool acceptSelf) : pSelf(pSelf), acceptSelf(acceptSelf) {}
      
      bool acceptSelf;
      CPtr<PFBaseUnit> pSelf;
      vector<CPtr<PFBaseUnit> > units;
    };
    
    class StatusesToDispellFinder : public NonCopyable
    {
      int         factionFlags;
      vector<int> dispellable;
    public:
      StatusesToDispellFinder( int factionFlags )
        : factionFlags(factionFlags)
        , dispellable( NDb::KnownEnum<NDb::EDispellPriority>::sizeOf, 0)
      {
      }

      void operator()(CObj<PFBaseApplicator> const& pAppl) 
      {
        // Check that it is status
        if (pAppl->GetTypeId() != PFApplStatus::typeId)
          return;

        // Faction check
        if ( (factionFlags & (1 << pAppl->GetAbilityOwner()->GetFaction())) == 0)
          return;

        // Cast to status
        PFApplStatus *pStatus                 = static_cast<PFApplStatus*>(pAppl.GetPtr());
        NDb::EDispellPriority dispellPriority = pStatus->GetDB().dispellPriority;
        
        ++dispellable[ dispellPriority - NDb::DISPELLPRIORITY_NONDISPELLABLE ];
      }

      static void Find(CPtr<PFBaseUnit> const& pTarget, vector<int>* pOutput)
      {
        if( NULL != pOutput )
        {
          StatusesToDispellFinder finder( pTarget->GetOppositeFactionFlags() );
          pTarget->ForAllAppliedApplicators(finder);
          pOutput->swap( finder.dispellable );
          return;
        }
      }
    };

    float CalculateAvgHeroTotalNaftaEarned( CPtr<PFWorld> const& pWorld, NDb::EFaction faction)
    {
      int heroes  = 0; 
      float totalNaftaEarned = 0;
      for( int i = 0, count = IsValid(pWorld) ? pWorld->GetPlayersCount() : 0; i < count; ++i )
      {
        PFPlayer const* pPlayer = pWorld->GetPlayer(i);
        PFBaseHero const* pHero = pPlayer ? pPlayer->GetHero() : NULL;

        if( pHero && faction == pHero->GetFaction() )
          totalNaftaEarned += pHero->GetTotalNaftaEarned(), ++heroes;
      }

      return 0 < heroes ? totalNaftaEarned / heroes : 0;
    }

  } // unnamed namespace

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  EvtMinHealth::EvtMinHealth(NDb::EvtMinHealth const& dbDesc, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbDesc, _buffsManager)
    , minHealth(dbDesc.minHealth)
  {
  }

  bool EvtMinHealth::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    return !pUnit->IsDead() && (pUnit->GetHealthPercent() <= minHealth);
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  EvtMinEnergy::EvtMinEnergy(NDb::EvtMinEnergy const& dbDesc, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbDesc, _buffsManager)
    , minEnergy(dbDesc.minEnergy)
  {
  }

  bool EvtMinEnergy::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    return !pUnit->IsDead() && (pUnit->GetManaPercent() <= minEnergy);
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  EvtEnemyDanger::EvtEnemyDanger(NDb::EvtEnemyDanger const& dbDesc, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbDesc, _buffsManager)
    , count(dbDesc.count)
    , distance(dbDesc.distance)
    , unitTypes(dbDesc.unitTypes)
    , treatNeutralAsHostile(dbDesc.treatNeutralAsHostile)
  {
  }

  bool EvtEnemyDanger::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    return !pUnit->IsDead() && ( count <= EnemyFinder::Count(pUnit, distance, unitTypes, treatNeutralAsHostile) );
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  EvtSpellLowMana::EvtSpellLowMana(NDb::EvtSpellLowMana const& dbDesc, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbDesc, _buffsManager)
  {
  }
  
  bool EvtSpellLowMana::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    CDynamicCast<PFBaseHero> pHero(pUnit);
    if( NULL == pHero )
    {
      NI_ALWAYS_ASSERT("HeroOnly impulsive event assigned for non-hero buff!");
      return false;
    }

    if ( pHero->GetGlobalPreparedness() < 1.0f )
      return false;
    
    float energy = pHero->GetMana();

    const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
    const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

    for ( int i = 0; i < levels; i++ )
    {
      for ( int j = 0; j < slots; j++ )
      {
        PFTalent* pTalent = pHero->GetTalent( i, j );
        if ( pTalent && pTalent->IsActivated() && pTalent->IsActive() )
        {
          if ( pTalent->GetPreparedness() < 1.0f )
          {
            continue; // ability is on cooldown
          }

          if ( pTalent->GetManaCost() > energy )
          {
            return true;
          }
        }
      }
    }

    return false;
  }
  
  EvtNegativeEffects::EvtNegativeEffects(NDb::EvtNegativeEffects const& db, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(db, _buffsManager)
    , minTotalEffects(db.minTotalEffects)
    , priorityConditions(db.priorityConditions)
  {
  }

  bool EvtNegativeEffects::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    CDynamicCast<PFBaseHero> pHero(pUnit);
    if( NULL == pHero )
    {
      NI_ALWAYS_ASSERT("HeroOnly impulsive event assigned for non-hero buff!");
      return false;
    }

    vector<int> dispellable;
    StatusesToDispellFinder::Find( pHero.GetPtr(), &dispellable);
    
    bool enabled = false;
    int  total   = 0;
    for(int i = 1, count = dispellable.size(); i < count; ++i)
    {
      for(vector<NDb::NegativeEffectCondition>::const_iterator it = priorityConditions.begin(), 
          end = priorityConditions.end(); it != end; ++it)
      {
        if( 0 < it->minCount && NDb::DISPELLPRIORITY_NONDISPELLABLE != it->priority && 
            it->priority == static_cast<NDb::EDispellPriority>(i + NDb::DISPELLPRIORITY_NONDISPELLABLE) )
          enabled |= it->minCount <= dispellable[i];
      }

      total += dispellable[i];
    }

    enabled |= minTotalEffects <= total;

    return enabled;
  }

  EvtComplexEvent::EvtComplexEvent(NDb::EvtComplexEvent const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , combineMode(dbEvt.combineMode)
  {
    for( vector<NDb::Ptr<NDb::ImpulsiveEvent>>::const_iterator it = dbEvt.events.begin(), end = dbEvt.events.end(); it != end; ++it )
      if( *it )
        events.push_back( (*it)->Create(buffsManager) );
  }

  bool EvtComplexEvent::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget)const
  {
    vector<CObj<ImpulsiveEvent> >::const_iterator const begin = events.begin();
    vector<CObj<ImpulsiveEvent> >::const_iterator const end   = events.end();
    
    bool result = false;
    for( vector<CObj<ImpulsiveEvent> >::const_iterator it = begin; it != end; ++it )
    {
      bool enabled = (*it) && (*it)->IsEnabled(pUnit, suggestedTarget);
      if( begin == it )
        result = enabled;
      else
      {
        switch(combineMode)
        {
        case NDb::EVENTSCOMBINEMOVE_AND:
          if( !enabled || !result )
            return false;
          break;
        case NDb::EVENTSCOMBINEMOVE_OR: 
          if( result || enabled)
            return true;
          break;
        case NDb::EVENTSCOMBINEMOVE_XOR:
          result ^= enabled;
          break;
        }
      }
    }

    return result;
  }

  void EvtComplexEvent::Step( const float dt)
  {
    vector<CObj<ImpulsiveEvent> >::const_iterator const begin = events.begin();
    vector<CObj<ImpulsiveEvent> >::const_iterator const end   = events.end();

    for( vector<CObj<ImpulsiveEvent> >::const_iterator it = begin; it != end; ++it )
      if( (*it) )
        (*it)->Step( dt );
  }
  
  EvtInverseEvent::EvtInverseEvent(NDb::EvtInverseEvent const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , event( dbEvt.evt ? dbEvt.evt->Create(buffsManager) : NULL )
  {
  }

  bool EvtInverseEvent::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget)const
  {
    return event ? !event->IsEnabled(pUnit, suggestedTarget) : false;
  }

  void EvtInverseEvent::Step( const float dt)
  {
    if( event )
      event->Step( dt );
  }
  
  EvtUnitsInRange::EvtUnitsInRange(NDb::EvtUnitsInRange const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , types(dbEvt.unitTypes)
    , factions(dbEvt.factions)
    , minCount(dbEvt.minCount)
    , maxCount(dbEvt.maxCount)
    , range(dbEvt.range)
    , rangeType(dbEvt.rangeType)
    , acceptSelf(dbEvt.acceptSelf)
    , countingWeights(buffsManager->GetCountingWeights(dbEvt.countingSet))
  {
  }

  bool EvtUnitsInRange::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/) const
  {
    VectorCollector<PFBaseUnit> collector;
    pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange(pUnit->GetPosition(), 
      NDb::RANGETYPE_EXACTVALUE == rangeType ? range : pUnit->GetAttackRange(), collector, 
      UnitSelector( pUnit->GetFactionMask(factions), NormalizeTargetFlags(types), pUnit, acceptSelf) );
    
    int count = 0;
    for(vector<PFBaseUnit const*>::const_iterator it = collector.objects.begin(), end = collector.objects.end(); 
      it != end; ++it )
    {
      if( NULL == *it )
        continue;

      NDb::EUnitType const unitType = (*it)->GetUnitType();
      if( NDb::UNITTYPE_INVALID != unitType )
        count += countingWeights[unitType];
    }

    return minCount <= count && count <= maxCount;
  }

  
  EvtAttackedByUnits::EvtAttackedByUnits(NDb::EvtAttackedByUnits const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , range(dbEvt.range)
    , rangeType(dbEvt.rangeType)
    , attackedFactions(dbEvt.attackedFactions)
    , attackedTypes(dbEvt.attackedTypes)
    , attackedAcceptSelf(dbEvt.attackedAcceptSelf)
    , attackersFactions(dbEvt.attackersFactions)
    , attackersTypes(dbEvt.attackersTypes)
    , attackersAcceptSelf(dbEvt.attackersAcceptSelf)
    , minAttackersCount(dbEvt.minAttackersCount)
    , maxAttackersCount(dbEvt.maxAttackersCount)
    , suggestVictim(dbEvt.suggestVictim)
    , countingWeights(buffsManager->GetCountingWeights(dbEvt.countingSet))
  {
  }

  bool EvtAttackedByUnits::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget)const
  {
    vector<CPtr<PFBaseUnit> > preys;
    UnitCollector::Collect( pUnit, NDb::RANGETYPE_EXACTVALUE == rangeType ? range : pUnit->GetAttackRange() + range, attackedTypes, attackedFactions, attackedAcceptSelf, &preys);
    
    for( vector<CPtr<PFBaseUnit> >::const_iterator it = preys.begin(), end = preys.end(); it != end; ++it)
    {
      VectorCollector<PFBaseUnit> collector;
      (*it)->ForAllAttackers( UnitSelector( pUnit->GetFactionMask(attackersFactions), NormalizeTargetFlags(attackersTypes), pUnit, attackersAcceptSelf), collector );
      
      int count = 0;
      for(vector<PFBaseUnit const*>::const_iterator attackers_it = collector.objects.begin(), 
        attackers_end = collector.objects.end(); attackers_it != attackers_end; ++attackers_it )
      {
        if( NULL == *attackers_it )
          continue;

        NDb::EUnitType const unitType = (*attackers_it)->GetUnitType();
        if( NDb::UNITTYPE_INVALID != unitType )
          count += countingWeights[unitType];
      }

      if( minAttackersCount <= count && count <= maxAttackersCount)
      {
        if( suggestTarget )
        {
          CPtr<PFBaseUnit> pTarget = suggestVictim ? *it :
            CPtr<PFBaseUnit>( collector.objects.empty() ? NULL : const_cast<PFBaseUnit*>( collector.objects.front() ));
          suggestedTarget.SetUnit(pTarget);
        }

        return true;
      }
    }
    
    return false;
  }

  bool PerformCompare( float l, float r, NDb::ECompareOperator operation)
  {
    switch( operation )
    {
    case NDb::COMPAREOPERATOR_EQUAL:
      return l == r;
    case NDb::COMPAREOPERATOR_GREATER:
      return l <  r;
    case NDb::COMPAREOPERATOR_GREATEROREQUAL:
      return l <= r;
    case NDb::COMPAREOPERATOR_LESS:
      return r <  l;
    case NDb::COMPAREOPERATOR_LESSOREQUAL:
      return r <= l;
    }
    
    NI_ALWAYS_ASSERT("Invalid operation requested!");
    return false;
  }
   
  EvtHeroTotalNaftaCondition::EvtHeroTotalNaftaCondition( NDb::EvtHeroTotalNaftaCondition const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , totalNafta(dbEvt.totalNafta)
    , type(dbEvt.type)
    , operation(dbEvt.operation)
  {
  }

  bool EvtHeroTotalNaftaCondition::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    CDynamicCast<PFBaseHero> pHero(pUnit);
    if( NULL == pHero )
    {
      NI_ALWAYS_ASSERT("HeroOnly impulsive event assigned for non-hero buff!");
      return false;
    }

    float const heroTotalNaftaEarned = pHero->GetTotalNaftaEarned();
    float const value     = NDb::LEVELCHECKTYPE_EXACT == type ? totalNafta :
      CalculateAvgHeroTotalNaftaEarned( pHero->GetWorld(), NDb::LEVELCHECKTYPE_AVGOFSELFTEAM == type ? pHero->GetFaction() : pHero->GetOppositeFaction() );

    return PerformCompare(value, heroTotalNaftaEarned, operation);
  }

  EvtUsedImpulsiveBuff::EvtUsedImpulsiveBuff(NDb::EvtUsedImpulsiveBuff const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , buffIndex(dbEvt.buffIndex)
    , usedByAlly(dbEvt.usedByAlly)
    , acceptSelf(dbEvt.acceptSelf)
    , range( dbEvt.range )
    , rangeType(dbEvt.rangeType)
  {
  }

  bool EvtUsedImpulsiveBuff::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    VectorCollector<PFBaseHero> collector;
    pUnit->GetWorld()->GetAIWorld()->ForAllHeroes(collector, 
      usedByAlly ? pUnit->GetFaction() : pUnit->GetOppositeFaction(), 
      (NDb::ESpellTarget)(NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_AFFECTMOUNTED) );
    
    CVec3 const pos          = pUnit->GetPosition();
    const float rangeSquared = pow(NDb::RANGETYPE_EXACTVALUE == rangeType ? range : pUnit->GetAttackRange(), 2);
    for( vector<PFBaseHero const*>::iterator it = collector.objects.begin(), 
      end = collector.objects.end(); it != end; ++it )
    {
      if( NULL == *it )
        continue;

      if( pUnit == *it && !acceptSelf )
        continue;

      if( rangeSquared < fabs2( (*it)->GetPosition() - pos ) )
        continue;

      if(IsValid(buffsManager) && buffsManager->IsBuffUsed( buffIndex ) )
        return true;
    }

    return false;
  }

  EvtUnitsInRangeWithProperHealth::EvtUnitsInRangeWithProperHealth(NDb::EvtUnitsInRangeWithProperHealth const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , factions(dbEvt.factions)
    , types(dbEvt.unitTypes)
    , range(dbEvt.range)
    , minCount(dbEvt.minCount)
    , maxCount(dbEvt.maxCount)
    , acceptSelf(dbEvt.acceptSelf)
    , health(dbEvt.health)
    , operation(dbEvt.operation)
  {
  }

  bool EvtUnitsInRangeWithProperHealth::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget)const
  {
    VectorCollector<PFBaseUnit> collector;
    pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange(pUnit->GetPosition(), range, collector, 
      UnitSelector( pUnit->GetFactionMask(factions), NormalizeTargetFlags(types), pUnit, acceptSelf) );
    
    int count = 0;
    for( vector<PFBaseUnit const*>::const_iterator it = collector.objects.begin(), 
      end = collector.objects.end(); it != end; ++it )
    {
      if( *it && PerformCompare(health, (*it)->GetHealthPercent(), operation) )
        ++count;
    }

    if( minCount <= count && count <= maxCount )
    {
      if( suggestTarget )
        suggestedTarget = Target( CPtr<PFBaseUnit>(const_cast<PFBaseUnit*>( collector.objects.front() ) ) );  

      return true;
    }
    
    return false;
  } 
  
 
  EvtPriestessGainMaxLevel::EvtPriestessGainMaxLevel(NDb::EvtPriestessGainMaxLevel const& dbEvt,ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
  {
  }

  bool EvtPriestessGainMaxLevel::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget)const
  { 
    VectorCollector<PFBaseHero> collector;
    pUnit->GetWorld()->GetAIWorld()->ForAllHeroes(collector, pUnit->GetFaction(), 
      (NDb::ESpellTarget)( NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_AFFECTMOUNTED) );
    
    const float lifeTime = IsValid(buffsManager)? buffsManager->GetPriestessEventsLifeTime(): 0;
    const int maxLevel = pUnit->GetWorld()->GetAIWorld()->GetMaxHeroLevel();

    for( vector<PFBaseHero const*>::const_iterator it = collector.objects.begin(), end = collector.objects.end();
      it != end; ++it )
    {
      if( *it && maxLevel == (*it)->GetNaftaLevel() && (*it)->GetTimeSinceLevelUp() <= lifeTime )
      {
        if( suggestTarget )
          suggestedTarget.SetUnit(CPtr<PFBaseUnit>(const_cast<PFBaseHero*>( *it ) ) );
        return true;
      }
    }
    
    return false;
  }

  EvtDead::EvtDead(NDb::EvtDead const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
  {
  }

  bool EvtDead::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    return pUnit->IsDead() && !pUnit->IsResurrecting();
  }

  EvtInMinigame::EvtInMinigame(NDb::EvtInMinigame const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
  {
  }

  bool EvtInMinigame::IsEnabled(PFBaseHero* pUnit, Target& /*suggestedTarget*/)const
  {
    PFEaselPlayer* easelPlayer = dynamic_cast<PFEaselPlayer*>( pUnit );

    if ( easelPlayer )
    {
      return easelPlayer->IsIsolated();
    }

    return false;
  }

  EvtTargetInRange::EvtTargetInRange(NDb::EvtTargetInRange const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , range( dbEvt.range )
  {
  }

  bool EvtTargetInRange::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const
  {
    if( NULL == pUnit )
      return false;

    CVec3 targetPos = VNULL3;
    if( suggestedTarget.IsObject() )
    {
      CPtr<PFLogicObject> const& pObject = suggestedTarget.GetObject();
      if( !IsValid( pObject ) )
        return false;

      targetPos = pObject->GetPosition();
    }
    else
    if( suggestedTarget.IsPosition() )
      targetPos = suggestedTarget.GetPosition();
    else
    {
      NI_ALWAYS_ASSERT("Invalid target!");
      return false;
    }

    return fabs( pUnit->GetPosition() - targetPos ) <= (NDb::RANGETYPE_EXACTVALUE == rangeType ? range : pUnit->GetAttackRange());
  }

  EvtEnteringBattleLine::EvtEnteringBattleLine(NDb::EvtEnteringBattleLine const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , battleRange( dbEvt.battleRange )
    , fightingAllies( dbEvt.fightingAllies )
    , roadRange( dbEvt.roadRange )
    , isAtBase( false )
  {
  }

  bool EvtEnteringBattleLine::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const
  {
    CDynamicCast<PFBaseHero> pHero(pUnit);
    if( NULL == pHero )
    {
      NI_ALWAYS_ASSERT("HeroOnly impulsive event assigned for non-hero buff!");
      return false;
    }
      
    PFWorld const* pWorld = pHero->GetWorld();
    CVec3 const pos       = pHero->GetPosition();
    if( pWorld->GetNatureMap()->IsAtBase( pos.x, pos.y ) )
    {
      isAtBase = true;
      return false;
    }
    
    if( !isAtBase )
      return false;
    
    isAtBase = false;

    // we`ve just left the base
    // 1. check our line
    float distance = 0.0f;
    NDb::ERoute const road = pHero->GetNearestRoute(&distance);
    
    if( roadRange < distance || NDb::ROUTE_UNASSIGNED == road )
      return false;

    // 2. find and count battles 
    int battles = 0;

    VectorCollector<PFBaseUnit> heroesCollector;
    pWorld->GetAIWorld()->ForAllHeroes( heroesCollector, pHero->GetFaction() );

    for( vector<PFBaseUnit const*>::const_iterator heroes_it = heroesCollector.objects.begin(), 
      heroes_end = heroesCollector.objects.end(); heroes_it != heroes_end; ++heroes_it )
    {
      if ( !(*heroes_it)->IsTrueHero() )
        continue;

      PFBaseHero const* pAlly = static_cast<PFBaseHero const*>( *heroes_it );

      if( NULL == pAlly )
      {
        NI_ALWAYS_ASSERT("Logic problem!");
        continue;
      }

      if( pAlly == pHero )
        continue;
      
      if( road != pHero->GetNearestRoute(&distance) || roadRange < distance )
        continue;

      // now we found ally hero at line
      // 1. check if he is fighting
      // 1a. if his target is hero
      CPtr<PFBaseUnit> pTarget = pAlly->GetCurrentTarget();
      if( IsUnitValid(pTarget) && pTarget->IsHero() )
      {
        // check range
        if( battleRange < fabs2( pos - pAlly->GetPosition() ) || 
            battleRange < fabs2( pos - pTarget->GetPosition() ) )
        {
          ++battles;
          continue;
        }
      }

      // 1b. if ally is attacked  by enemy hero 
      VectorCollector<PFBaseUnit> collector;
      pAlly->ForAllAttackers( UnitSelector( pAlly->GetOppositeFactionFlags(), 
        NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_AFFECTMOUNTED, NULL, false), collector );
       
      if( collector.objects.empty() )
        continue;
      
      bool enemyInRange = false;
      for( vector<PFBaseUnit const*>::const_iterator it = collector.objects.begin(), end = collector.objects.end(); 
           !enemyInRange && it != end; ++it)
      {
        if( battleRange < fabs2( pos - (*it)->GetPosition() ) )
        {
          enemyInRange = true;
          break;
        }
      }

      if( enemyInRange || battleRange < fabs2( pos - pAlly->GetPosition() )  )
      {
        ++battles;
        continue;
      }
    }

    return fightingAllies <= battles;
  }

  EvtEnemyFlees::EvtEnemyFlees(NDb::EvtEnemyFlees const& dbEvt, ImpulsiveBuffsManager * _buffsManager)
    : ImpulsiveEvent(dbEvt, _buffsManager)
    , operation( dbEvt.operation )
    , health( dbEvt.health * 0.01f )
    , fleeTime( dbEvt.fleeTime )
    , cowardDetectRange( dbEvt.cowardDetectRange )
    , cowardChaseRange( dbEvt.cowardChaseRange )
  {
  }

  bool EvtEnemyFlees::IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const
  {    
    CDynamicCast<PFBaseHero> pHero(pUnit);
    if( NULL == pHero )
    {
      NI_ALWAYS_ASSERT("HeroOnly impulsive event assigned for non-hero buff!");
      return false;
    }
    
    if( pOwner != pHero )
    {
      cowards.clear();
      pOwner = pHero;
      return false;
    }
    
    for( vector<CowardData>::const_iterator it = cowards.begin(), end = cowards.end(); it != end; ++it )
      if( IsUnitValid( it->pCoward ) && fleeTime <= it->timeRan )
        return true;

    return false;
  }

  void EvtEnemyFlees::Step( const float dt )
  {
    if( !IsUnitValid(pOwner) )
    {
      cowards.clear();
      return;
    }

    // 1. check current cowards
    for( vector<CowardData>::iterator it = cowards.begin(); it != cowards.end(); )
    {
      // coward died
      if( !IsUnitValid( it->pCoward ) )
      {
        it = cowards.erase(it);
        continue;
      }

      // coward fleed
      CVec3 const cowardPos = it->pCoward->GetPosition();
      const float distance2 = fabs2( pOwner->GetPosition() - cowardPos );
      if( pow( cowardChaseRange, 2 ) < distance2 )
      {
        it = cowards.erase(it);
        continue;
      }
      
      if( cowardPos != it->lastPos )
        it->timeRan += dt;

      ++it;
    }
    
    // 2. find new cowards
    VectorCollector<PFBaseUnit> collector;
    pOwner->GetWorld()->GetAIWorld()->ForAllUnitsInRange( pOwner->GetPosition(), cowardDetectRange, collector, 
      UnitSelector( pOwner->GetOppositeFactionFlags(), NDb::SPELLTARGET_ENEMY | NDb::SPELLTARGET_AFFECTMOUNTED | NDb::SPELLTARGET_HEROMALE | NDb::SPELLTARGET_HEROFEMALE, NULL, false ) );
    
    for( vector<PFBaseUnit const*>::const_iterator it = collector.objects.begin(), end = collector.objects.end(); 
      it != end; ++it)
    {
      CDynamicCast<PFBaseHero> pHero( *it );
      if( NULL == pHero )
      {
        NI_ALWAYS_ASSERT("Logic problem");
        continue;
      }
      
      // check if we know about this coward!
      bool found = false;
      for( vector<CowardData>::iterator known_it = cowards.begin(), known_end = cowards.end(); 
        !found && known_it != known_end; ++known_it )
        if( known_it->pCoward == pHero )
          found = true;

      if( found )
        continue;
  
      if( PerformCompare(health, pHero->GetHealthPercent(), operation) )
      {
        cowards.push_back();
        cowards.back().pCoward = pHero;
        cowards.back().lastPos = pHero->GetPosition();
      }

    }
  }
 
  EvtCondition::EvtCondition( const NDb::EvtCondition& dbEvt, ImpulsiveBuffsManager * _buffsManager  ) :
  ImpulsiveEvent(dbEvt, _buffsManager),
  pCondition( &dbEvt.condition )
  {
  }

  bool EvtCondition::IsEnabled( PFBaseHero* pUnit, Target& /*suggestedTarget*/ ) const
  {
    return (*pCondition)( pUnit, pUnit, 0 );
  }
 
} //namespace NWorld
