#pragma once

#include "DBImpulsiveBuffs.h"
#include "PFImpulsiveBuffs.h"

namespace NWorld
{

  class EvtComplexEvent : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtComplexEvent );
    EvtComplexEvent() {}

    NDb::EEventsCombineMove combineMode;
    vector<CObj<ImpulsiveEvent> > events;
  public:
    EvtComplexEvent(NDb::EvtComplexEvent const&, ImpulsiveBuffsManager * _buffsManager); 
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
    virtual void Step( const float dt);
  };

  //////////////////////////////////////////////////////////////////////////
  class EvtInverseEvent : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtInverseEvent );
    EvtInverseEvent() {}

    CObj<ImpulsiveEvent> event;
  public:
    EvtInverseEvent(NDb::EvtInverseEvent const&, ImpulsiveBuffsManager * _buffsManager); 
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
    virtual void Step( const float dt);
  };
  
  //////////////////////////////////////////////////////////////////////////
  class EvtMinHealth : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtMinHealth );
    EvtMinHealth() : minHealth () {}

  public:
    EvtMinHealth(NDb::EvtMinHealth const& dbDesc, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  private:
    const float minHealth;
  };

  //////////////////////////////////////////////////////////////////////////
  class EvtMinEnergy : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtMinEnergy );
    EvtMinEnergy() : minEnergy() {}

  public:
    EvtMinEnergy(NDb::EvtMinEnergy const& dbDesc, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  private:
    const float minEnergy;
  };

  //////////////////////////////////////////////////////////////////////////
  class EvtEnemyDanger : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtEnemyDanger );
    EvtEnemyDanger() : count(), distance(), unitTypes(), treatNeutralAsHostile() {}

  public:
    EvtEnemyDanger(NDb::EvtEnemyDanger const& dbDesc, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  private:
    const int count;
    const float distance;
    const NDb::ESpellTarget unitTypes;
    const bool treatNeutralAsHostile;
  };

  class EvtSpellLowMana : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtSpellLowMana );
    EvtSpellLowMana() {}

  public:
    EvtSpellLowMana(NDb::EvtSpellLowMana const& dbDesc, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtNegativeEffects : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtNegativeEffects );
    EvtNegativeEffects() {}

    int                                  minTotalEffects;
    vector<NDb::NegativeEffectCondition> priorityConditions;
  public:
    EvtNegativeEffects(NDb::EvtNegativeEffects const& db, ImpulsiveBuffsManager * _buffsManager); 
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };
  
  class EvtUnitsInRange : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtUnitsInRange );
    EvtUnitsInRange() {}

    NDb::EFactionFlags factions;
    NDb::ESpellTarget types;
    NDb::ERangeType rangeType;
    float range;
    int minCount;
    int maxCount;
    bool acceptSelf;
    vector<int> countingWeights;
  public:
    EvtUnitsInRange(NDb::EvtUnitsInRange const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtAttackedByUnits : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtAttackedByUnits );
    EvtAttackedByUnits() {}

    float range;
    NDb::ERangeType rangeType;
    NDb::EFactionFlags attackedFactions;
    NDb::ESpellTarget attackedTypes;
    bool attackedAcceptSelf;
    NDb::EFactionFlags attackersFactions;
    NDb::ESpellTarget attackersTypes;
    bool attackersAcceptSelf;
    int minAttackersCount;
    int maxAttackersCount;
    bool suggestVictim;
    vector<int> countingWeights;
  public:
    EvtAttackedByUnits(NDb::EvtAttackedByUnits const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtHeroTotalNaftaCondition : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtHeroTotalNaftaCondition );
    EvtHeroTotalNaftaCondition() {}

    int totalNafta;
    NDb::ELevelCheckType type;
    NDb::ECompareOperator operation;
  public:
    EvtHeroTotalNaftaCondition(NDb::EvtHeroTotalNaftaCondition const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtUsedImpulsiveBuff : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtUsedImpulsiveBuff );
    EvtUsedImpulsiveBuff() {}

    int   buffIndex;
    bool  usedByAlly;
    bool  acceptSelf;
    float range;
    NDb::ERangeType rangeType;
  public:
    EvtUsedImpulsiveBuff(NDb::EvtUsedImpulsiveBuff const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtUnitsInRangeWithProperHealth : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtUnitsInRangeWithProperHealth );
    EvtUnitsInRangeWithProperHealth() {}

    NDb::EFactionFlags factions;
    NDb::ESpellTarget types;
    float range;
    int minCount;
    int maxCount;
    bool acceptSelf;

    float health;
    NDb::ECompareOperator operation;
  public:
    EvtUnitsInRangeWithProperHealth(NDb::EvtUnitsInRangeWithProperHealth const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };
   
  class EvtPriestessGainMaxLevel : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtPriestessGainMaxLevel );
    EvtPriestessGainMaxLevel() {}

  public:
    EvtPriestessGainMaxLevel(NDb::EvtPriestessGainMaxLevel const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtDead : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtDead );
    EvtDead() {}

  public:
    EvtDead(NDb::EvtDead const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtInMinigame : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtInMinigame );
    EvtInMinigame() {}

  public:
    EvtInMinigame(NDb::EvtInMinigame const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtTargetInRange : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtTargetInRange );
    EvtTargetInRange() {}

    float range;
    NDb::ERangeType rangeType;
  public:
    EvtTargetInRange(NDb::EvtTargetInRange const& dbEvt, ImpulsiveBuffsManager * _buffsManager);
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtEnteringBattleLine : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtEnteringBattleLine );
    EvtEnteringBattleLine() {}

    // data params
    float battleRange;
    int   fightingAllies;
    float roadRange;

    // internal params
    mutable bool isAtBase;
  public:
    EvtEnteringBattleLine(NDb::EvtEnteringBattleLine const& dbEvt, ImpulsiveBuffsManager * _buffsManager); 
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
  };

  class EvtEnemyFlees : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtEnemyFlees );
    EvtEnemyFlees() {}

    // data params
    NDb::ECompareOperator operation;
    float                 health;
    float                 fleeTime;

    float                 cowardDetectRange;    
    float                 cowardChaseRange;

    
    // internal params
    struct CowardData
    {
      float            timeRan;
      CVec3            lastPos;
      CPtr<PFBaseHero> pCoward;

      CowardData() : timeRan( 0.0f ) {}
    };
    
    mutable CPtr<PFBaseHero>   pOwner;
    mutable vector<CowardData> cowards;
  public:
    EvtEnemyFlees(NDb::EvtEnemyFlees const& dbEvt, ImpulsiveBuffsManager * _buffsManager); 
    virtual bool IsEnabled(PFBaseHero* pUnit, Target& suggestedTarget )const;
    virtual void Step( const float dt );
  };

  class EvtCondition : public ImpulsiveEvent, public CObjectBase, public NonCopyable
  {
    OBJECT_BASIC_METHODS( EvtCondition );
    EvtCondition() : pCondition() {}

    const ExecutableBoolString * pCondition;
  public:
    EvtCondition( const NDb::EvtCondition& dbEvt, ImpulsiveBuffsManager * _buffsManager );
    virtual bool IsEnabled( PFBaseHero* pUnit, Target& suggestedTarget ) const;
    virtual void Step( const float dt ) {}
  };


} //namespace NWorld
