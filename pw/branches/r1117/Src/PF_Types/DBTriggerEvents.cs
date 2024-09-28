using System;
using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBAnimations;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBConsumable;
using Terrain.DBTerrain;

namespace PF_GameLogic.DBAbility
{

  [Flags]
  public enum ETriggerAbilitiesAbilitiesFlags
  {
    None = 0,

    BaseAttack = 1 << EAbilityTypeId.BaseAttack,
    Ability0 = 1 << EAbilityTypeId.Ability0,
    Ability1 = 1 << EAbilityTypeId.Ability1,
    Ability2 = 1 << EAbilityTypeId.Ability2,
    Ability3 = 1 << EAbilityTypeId.Ability3,
    Ability4 = 1 << EAbilityTypeId.Ability4,
    Consumable = 1 << EAbilityTypeId.Consumable,
    Talent = 1 << EAbilityTypeId.Talent,
    Special = 1 << EAbilityTypeId.Special,
    All = BaseAttack | Ability0 | Ability1 | Ability2 | Ability3 | Ability4 | Consumable | Talent | Special,

    OnlyClassTalent = Talent | 0x08000000,

    FromList = 0x10000000,

    FromAlly = 0x20000000,
    FromEnemy = 0x40000000,
  }

  public enum EAbilityCostMode
  {
    Energy = 0,
    Life   = 1,
    Any    = 2,
    Custom = 3
  }

  public class TriggerAbilitiesFilter
  {
    public ETriggerAbilitiesAbilitiesFlags flags = ETriggerAbilitiesAbilitiesFlags.All | ETriggerAbilitiesAbilitiesFlags.FromAlly | ETriggerAbilitiesAbilitiesFlags.FromEnemy;
    public bool onlySingleTarget = false;
    [Description("Реагировать на абилки с указанным режимом стоимости. Для автоатаки не проверяется.")]
    public EAbilityCostMode abilityCostMode = EAbilityCostMode.Energy;
    public List<DBPtr<Ability>> abilitiesList = new List<DBPtr<Ability>>();
    public bool exceptThis = false;
    [Description( "Условие (pMisc=фильтруемая абилка) " )]
    public ExecutableBoolString abilityCondition = new ExecutableBoolString( "true" );
  }
  
  [Flags]
  public enum UnitDieKillersFlags
  {
    KilledByMe       = 1 << 0,
    KilledByAllies   = 1 << 1,
    KilledByEnemy    = 1 << 2,
    KilledByMySummons= 1 << 3,
    KilledByAll = KilledByMe | KilledByAllies | KilledByEnemy,
  }

  [Flags]
  public enum ETriggerEventCheckSender
  {
    None = 0,

    MatchTarget = 1 << 0,
    ObjectFilter = 1 << 1,
  }

  [Flags]
  public enum ETriggerEventFlags
  {
    None = 0,
    OnlyFirstFromAbility = 1 << 0,
    OncePerStep          = 1 << 1,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  [TypeId(0xF724340)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorCondition", "PFTriggerApplicator.h")]
  public class EventProcessorCondition : EventProcessorBase
  {
    public EBaseUnitEventFlags events = EBaseUnitEventFlags.Zero;
    public ExecutableBoolString condition = new ExecutableBoolString("false");

    [Description( "true - триггириться только от абилки, в которой лежит, false - от всех, подходящих по условию" )] 
    public bool onlyParent = false;
  }

  [TypeId(0xF728300)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorCancelDispatch", "PFTriggerApplicator.h")]
  public class EventProcessorCancelDispatch : EventProcessorBase
  {
    public TriggerAbilitiesFilter filter;

    [Description("Сравнить посылающего диспатч с целью аппликатора")]
    public EApplicatorApplyTarget senderMatchTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Дополнительные проверки посылающего событие")]
    public ETriggerEventCheckSender checkSender = 0;
  }

  [TypeId( 0x37A78C40 )]
  [UseTypeName( "EVNT" )]
  [FactoryImpl( "Create", "NWorld::PFEventProcessorPickupGlyph", "PFTriggerApplicator.h" )]
  public class EventProcessorPickupGlyph : EventProcessorBase
  {
    public TriggerAbilitiesFilter filter;
  }

  [TypeId(0xF729C40)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorDamageTransformer", "PFTriggerApplicator.h")]
  public class EventProcessorDamageTransformer : EventProcessorBase
  {
    public EDamageFilter damageTypeFilter = EDamageFilter.All;
    public TriggerAbilitiesFilter abilityFilter;
    public ExecutableFloatString add = new ExecutableFloatString("0.0f");
    public ExecutableFloatString mul = new ExecutableFloatString("1.0f");

    [Description("Сравнить посылающего событие с целью аппликатора")]
    public EApplicatorApplyTarget senderMatchTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description( "Invert sender vs target comparison results" )]
    public bool matchTargetInverted = false;

    [Description( "Считать делегированный урон как от делегирующего" )]
    public bool treatDelegatedByDelegator = false;

    [Description("Фильтр по типу объекта, посылающего событие")]
    public ESpellTarget objectFilter = ESpellTarget.All;

    [Description("Дополнительные проверки посылающего событие")]
    public ETriggerEventCheckSender checkSender = 0;

    [Description("Доплнительные Флаги: OnlyFirstFromAbility - обработать только первый урон из посланных абилкой за степ")]
    public ETriggerEventFlags flags = 0;
  }

  [TypeId(0xE78A3CC0)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorIncomingDamage", "PFTriggerApplicator.h")]
  public class EventProcessorIncomingDamage : EventProcessorBase
  {
    [Description("Делегированный указанным аппликатором урон можно получить из отдельной переменной")]
    public DBPtr<DelegateDamageApplicator> damageDelegate;

    [Description("Кто делегирует урон")]
    public EApplicatorApplyTarget damageDelegateOwner = EApplicatorApplyTarget.ApplicatorTarget;
  }

  [TypeId(0xF729C41)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorAbilityManacostTransformer", "PFTriggerApplicator.h")]
  public class EventProcessorAbilityManacostTransformer : EventProcessorBase
  {
    public TriggerAbilitiesFilter filter;
  }

  public enum EApplicatorAppliedMode
  {
    Default = 0,
    Cancel = 1,
    SetNewLifetime,
  }
  
  [TypeId(0xF72C2C1)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorApplicatorApplied", "PFTriggerApplicator.h")]
  public class EventProcessorApplicatorApplied : EventProcessorBase
  {
    public ETriggerAbilitiesAbilitiesFlags filter;
    [Description("Типы аппликаторов для сравнения")]
    public DBPtr<ApplicatorsList> applicatorTypesList;
    [Description("Конкретные аппликаторы для сравнения")]
    public DBPtr<ApplicatorsList> applicatorsList;

    public EApplicatorAppliedMode mode = EApplicatorAppliedMode.Default;

    [Description("Новая длительность накладываемого аппликатора. Оргинальную можно получить через appl.vLifetime")]
    public ExecutableFloatString newLifetime = new ExecutableFloatString( "-1.0" );

    [Description("Сравнить посылающего с целью аппликатора")]
    public EApplicatorApplyTarget senderMatchTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Дополнительные проверки посылающего событие")]
    public ETriggerEventCheckSender checkSender = 0;
  }

  [TypeId(0xF72CB40)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorOnDeath", "PFTriggerApplicator.h")]
  public class EventProcessorOnDeath: EventProcessorBase
  {
    [Description("Delay after death before apply spell")]
    public ExecutableFloatString castSpellDelay = new ExecutableFloatString("0.0f");

    [Description("Сравнить киллера с целью аппликатора")]
    public EApplicatorApplyTarget senderMatchTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Фильтр по типу объекта, посылающего событие")]
    public ESpellTarget objectFilter = ESpellTarget.All;

    [Description("Дополнительные проверки посылающего событие")]
    public ETriggerEventCheckSender checkSender = 0;
  }

  [TypeId(0xF72CB40)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorOnTarget", "PFTriggerApplicator.h")]
  public class EventProcessorOnTarget : EventProcessorBase
  {
    public DBPtr<TargetSelector> targetSelector;
    public ExecutableFloatString minTargets = new ExecutableFloatString("1.0f");
  }

  [TypeId(0xF72CB40)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorUnitDieNearMe", "PFTriggerApplicator.h")]
  public class EventProcessorUnitDieNearMe : EventProcessorBase
  {
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");
    public ESpellTarget targets = ESpellTarget.All | ESpellTarget.Enemy | ESpellTarget.Ally;
    public UnitDieKillersFlags killerFlags = UnitDieKillersFlags.KilledByAll;

    [Description("Сравнить убитого с целью аппликатора")]
    public EApplicatorApplyTarget senderMatchTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Дополнительные проверки посылающего событие")]
    public ETriggerEventCheckSender checkSender = 0;
  }

  [TypeId(0xF7563C0)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorGroup", "PFTriggerApplicator.h")]
  public class EventProcessorGroup: EventProcessorBase
  {
    public List<DBPtr<EventProcessorBase>> processors;
  }

  // Specially for witchdoctor A1 (crow eye)
  [TypeId(0xF741400)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorOnUseAbilityForceStrike", "PFTriggerApplicator.h")]
  public class EventProcessorOnUseAbilityForceStrike: EventProcessorBase
  {
    [Description("Abilities to process")]
    public TriggerAbilitiesFilter filter;
    [Description("formulaName of SpellPeriodicallyVisual applicator to control (must be placed in the same dispatch!)")]
    public String applicatorName = "";
  }

  [TypeId(0xE7768540)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorLastHit", "PFTriggerApplicator.h")]
  public class EventProcessorLastHit : EventProcessorBase
  {
  }

  [Flags]
  public enum EConsumableOriginFlags
  {
    Shop       = 1 << EConsumableOrigin.Shop,
    Minigame   = 1 << EConsumableOrigin.Minigame,
    Pickupable = 1 << EConsumableOrigin.Pickupable,
    Applicator = 1 << EConsumableOrigin.Applicator,
    Script     = 1 << EConsumableOrigin.Script,
  }

  [TypeId(0xE79B9C01)]
  [UseTypeName("EVNT")]
  [FactoryImpl("Create", "NWorld::PFEventProcessorOnConsumableObtained", "PFTriggerApplicator.h")]
  public class EventProcessorOnConsumableObtained : EventProcessorBase
  {
    [Description("Консумабл на получение которого реагировать. Оставить пустым если надо реагировать на любой.")]
    public DBPtr<Consumable> consumable;
    [Description("На какое происхождение консумабла реагировать")]
    public EConsumableOriginFlags origin = 0;
  }

  [TypeId( 0xE7A69380 )]
  [UseTypeName( "EVNT" )]
  [FactoryImpl( "Create", "NWorld::PFEventProcessorOutgoingDamage", "PFTriggerApplicator.h" )]
  public class EventProcessorOutgoingDamage : EventProcessorBase
  {
    public EDamageFilter damageTypeFilter = EDamageFilter.All;
    public TriggerAbilitiesFilter abilityFilter;

    [Description("Выходной урон. Доступ к урону на входе через appl.vDamage")]
    public ExecutableFloatString modifiedDamage = new ExecutableFloatString( "0.0f" );
  }
}

