using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBStats;

namespace PF_GameLogic.DBImpulsiveBuffs
{
  public enum EEventsCombineMove
  {
    AND,
    OR,
    XOR
  }

  [TypeId(0x2C6C4B00)]
  [FactoryImpl("Create", "NWorld::EvtComplexEvent", "PFImpulsiveEvents.h")]
  public class EvtComplexEvent : ImpulsiveEvent
  {
    public EEventsCombineMove combineMode = EEventsCombineMove.AND;
    public List<DBPtr<ImpulsiveEvent>> events = new List<DBPtr<ImpulsiveEvent>>();
  }

  [TypeId(0x2C6C4C00)]
  [FactoryImpl("Create", "NWorld::EvtInverseEvent", "PFImpulsiveEvents.h")]
  public class EvtInverseEvent : ImpulsiveEvent
  {
    public DBPtr<ImpulsiveEvent> evt;
  }
  
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  [TypeId(0xF664C00)]
  [FactoryImpl("Create", "NWorld::EvtMinHealth", "PFImpulsiveEvents.h")]
  public class EvtMinHealth : ImpulsiveEvent
  {
    public float minHealth = 0.2f;
  }

  [TypeId(0xF664C01)]
  [FactoryImpl("Create", "NWorld::EvtMinEnergy", "PFImpulsiveEvents.h")]
  public class EvtMinEnergy : ImpulsiveEvent
  {
    public float minEnergy = 0.2f;
  }

  [TypeId(0xF664C02)]
  [FactoryImpl("Create", "NWorld::EvtEnemyDanger", "PFImpulsiveEvents.h")]
  public class EvtEnemyDanger : ImpulsiveEvent
  {
    public int count = 1;
    public float distance = 150.0f;
    public ESpellTarget unitTypes = ESpellTarget.HeroMale | ESpellTarget.HeroFemale;
    public bool treatNeutralAsHostile = true;
  }

  [TypeId(0xF665B80)]
  [FactoryImpl("Create", "NWorld::EvtSpellLowMana", "PFImpulsiveEvents.h")]
  public class EvtSpellLowMana : ImpulsiveEvent
  {
  }

  public class NegativeEffectCondition
  {
    public int minCount = 1;
    public PF_GameLogic.DBAbility.EDispellPriority priority = PF_GameLogic.DBAbility.EDispellPriority.NonDispellable;
  }

  [TypeId(0x2C6C1C80)]
  [FactoryImpl("Create", "NWorld::EvtNegativeEffects", "PFImpulsiveEvents.h")]
  public class EvtNegativeEffects : ImpulsiveEvent
  {
    public int minTotalEffects = 1;
    public List<NegativeEffectCondition> priorityConditions = new List<NegativeEffectCondition>();
  }

  public enum ERangeType
  {
    ExactValue,
    AttackRange,
  }

  [TypeId(0x2C6C4BC0)]
  [FactoryImpl("Create", "NWorld::EvtUnitsInRange", "PFImpulsiveEvents.h")]
  public class EvtUnitsInRange : ImpulsiveEvent
  {
    public float range            = 0f;
    public ERangeType rangeType   = ERangeType.ExactValue;
    public EFactionFlags factions = 0;
    public ESpellTarget unitTypes = 0;
    public int minCount           = 0;
    public int maxCount           = 1000; 
    public bool acceptSelf        = true;
    public string countingSet     = "";
  }

  public enum ELevelCheckType
  {
    Exact,
    AvgOfSelfTeam,
    AvgOfOppositeTeam,
  }

  public enum ECompareOperator
  {
    Equal,
    Greater,
    GreaterOrEqual,
    Less, 
    LessOrEqual
  }

  [TypeId(0x2C6C4C40)]
  [FactoryImpl("Create", "NWorld::EvtHeroTotalNaftaCondition", "PFImpulsiveEvents.h")]
  public class EvtHeroTotalNaftaCondition : ImpulsiveEvent
  {
    public ELevelCheckType type = ELevelCheckType.Exact;
    public ECompareOperator operation = ECompareOperator.Equal;
    public int totalNafta = 0;
  }

  [TypeId(0x2C6C5381)]
  [FactoryImpl("Create", "NWorld::EvtAttackedByUnits", "PFImpulsiveEvents.h")]
  public class EvtAttackedByUnits : ImpulsiveEvent
  {
    public float range          = 0.0f;
    public ERangeType rangeType = ERangeType.ExactValue;

    // attacked
    public EFactionFlags attackedFactions = 0;
    public ESpellTarget  attackedTypes = 0;
    public bool          attackedAcceptSelf = true;
    
    // attackers
    public EFactionFlags attackersFactions = 0;
    public ESpellTarget attackersTypes = 0;
    public bool attackersAcceptSelf = true;
    public int minAttackersCount = 0;
    public int maxAttackersCount = 1000;

    // for target suggestion
    public bool suggestVictim = true;

    public string countingSet = "";
  }

  [TypeId(0x2C6C5C40)]
  [FactoryImpl("Create", "NWorld::EvtUsedImpulsiveBuff", "PFImpulsiveEvents.h")]
  public class EvtUsedImpulsiveBuff : ImpulsiveEvent
  {
    public int   buffIndex      = -1;
    public bool  usedByAlly     = false;
    public bool  acceptSelf     = false;
    public float range          = 0;
    public ERangeType rangeType = ERangeType.ExactValue;
  }

  [TypeId(0x2C6C5C80)]
  [FactoryImpl("Create", "NWorld::EvtUnitsInRangeWithProperHealth", "PFImpulsiveEvents.h")]
  public class EvtUnitsInRangeWithProperHealth : EvtUnitsInRange
  {
    public float health = 0;
    public ECompareOperator operation = ECompareOperator.Equal;
  }
  
  [TypeId(0x2C6C83C1)]
  [FactoryImpl("Create", "NWorld::EvtPriestessGainMaxLevel", "PFImpulsiveEvents.h")]
  public class EvtPriestessGainMaxLevel : ImpulsiveEvent
  {
  }

  [TypeId(0x2C6C8440)]
  [FactoryImpl("Create", "NWorld::EvtDead", "PFImpulsiveEvents.h")]
  public class EvtDead : ImpulsiveEvent
  {
  }


  [TypeId(0x2B78EBC0)]
  [FactoryImpl("Create", "NWorld::EvtInMinigame", "PFImpulsiveEvents.h")]
  public class EvtInMinigame : ImpulsiveEvent
  {
  }

  [TypeId(0x2C6CAAC0)]
  [FactoryImpl("Create", "NWorld::EvtTargetInRange", "PFImpulsiveEvents.h")]
  public class EvtTargetInRange : ImpulsiveEvent
  {
    public float range          = 0.0f;
    public ERangeType rangeType = ERangeType.ExactValue;
  }

  [TypeId(0x2C72D3C0)]
  [FactoryImpl("Create", "NWorld::EvtEnteringBattleLine", "PFImpulsiveEvents.h")]
  public class EvtEnteringBattleLine : ImpulsiveEvent
  {
    [Description("Distance from hero to battle")]
    public float battleRange  = 100.0f;

    [Description("Minimum allies count to treat their fight as battle")]
    public int   fightingAllies = 1;

    [Description("Distance from road line to heroes to treat they are at road")]
    public float roadRange = 15.0f;
  }

  [TypeId(0x2C72D3C1)]
  [FactoryImpl("Create", "NWorld::EvtEnemyFlees", "PFImpulsiveEvents.h")]
  public class EvtEnemyFlees : ImpulsiveEvent
  {
    [FloatMinMax(0, 100)]
    public float health               = 10.0f;
    public ECompareOperator operation = ECompareOperator.Less;

    public float fleeTime             = 10.0f;

    public float cowardDetectRange    = 20.0f;
    public float cowardChaseRange     = 20.0f;
  }

  [TypeId( 0x4977E4C0 )]
  [FactoryImpl( "Create", "NWorld::EvtCondition", "PFImpulsiveEvents.h" )]
  public class EvtCondition : ImpulsiveEvent
  {
    public ExecutableBoolString condition = new ExecutableBoolString( "true" );
  }
}