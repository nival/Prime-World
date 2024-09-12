//#include "Effect.cs"
//#include "DbSignsEventsSystem.cs"
//#include "DBExecString.cs"
//#include "DBUnit.cs"
//#include "DBApplicators.cs"
//#include "DBTargetSelectors.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBStats;
using Render.DBRender;

namespace PF_GameLogic.DBAbility
{
  public enum ETeamID
  {
    A,
    B
  }

  [Custom( "Social" )]
  public enum EUnitType
  {
    Invalid = -1,
    HeroMale = 0,
    HeroFemale,
    Summon,
    Creep,
    SiegeCreep,
    NeutralCreep,
    Tower,
    Building,
    MainBuilding,
    Shop,
    Tree,
    Pet,
    Pickupable,
    MinigamePlace,
    DeadBody,
    SimpleObject,
    DummyUnit,
    Flagpole,
    NeutralChampion,
    NeutralBoss,
    FactionChampion,
  }

  public enum EDispatchType
  {
    Immediate = 0,
    Linear,
    ByTime,
  };

  public enum EDispatchFlyMode
  {
    Parabolic = 0,
    Linear,
    FixedHeight,
  };

  public enum EApplyEffectOrientation
  {
    Default = 0,
    Random,
    Motion,
    LogicalDirection,
  };

  public enum EAbility
  {
    ID_Stats,
    ID_1,
    ID_2,
    ID_3,
    ID_4,
  }

  public enum EAbilityType
  {
    Simple,
    Active,
    MultiActive,
    Passive,
    Autocastable,
    Switchable,
    Channelling,
  }

  [Flags]
  public enum EAbilityFlags
  {
    FocusOnTarget          = (1 << 0),
    Momentary              = (1 << 1),
    ApplyToDead            = (1 << 2),
    MirroredByClone        = (1 << 3),
    StayInvisible          = (1 << 4),
    ChannelingCreate       = (1 << 5),
    CanUseOutOfRange       = (1 << 6),
    DontOpenWarFog         = (1 << 7),
    InstaCast              = (1 << 8),
    Moving                 = (1 << 9),
    UseAttackTarget        = (1 << 10),
    WaitForChanneling      = (1 << 11),
    FocusInstantly         = (1 << 12),
    MinimapTargetMustBeAlternative = (1 << 13),
    SpendLifeInsteadEnergy = (1 << 14),
    SelfCasting            = (1 << 15),
    ForceDoNotStopUnit     = (1 << 16),
  }

  [Flags]
  public enum ESpellTarget
  {
    HeroMale = (1 << EUnitType.HeroMale),
    HeroFemale = (1 << EUnitType.HeroFemale),
    Summon = (1 << EUnitType.Summon),
    Creep = (1 << EUnitType.Creep),
    SiegeCreep = (1 << EUnitType.SiegeCreep),
    NeutralCreep = (1 << EUnitType.NeutralCreep),
    Tower = (1 << EUnitType.Tower),
    MainBuilding = (1 << EUnitType.MainBuilding),
    Building = (1 << EUnitType.Building),
    Shop = (1 << EUnitType.Shop),
    Tree = (1 << EUnitType.Tree),
    Pickupable = (1 << EUnitType.Pickupable),
    MinigamePlaces = (1 << EUnitType.MinigamePlace),
    DeadBodies = (1 << EUnitType.DeadBody),
    DummyUnit = (1 << EUnitType.DummyUnit),
    Flagpole = (1 << EUnitType.Flagpole),
    NeutralChampion = (1 << EUnitType.NeutralChampion),
    NeutralBoss = (1 << EUnitType.NeutralBoss),
    FactionChampion = (1 << EUnitType.FactionChampion),
    AllNeutrals = NeutralCreep | NeutralChampion | NeutralBoss,
    All = HeroMale | HeroFemale | Summon | Creep | SiegeCreep | AllNeutrals | Tower | MainBuilding | Building | MinigamePlaces | DummyUnit | Flagpole | FactionChampion,
    AllWoBuildings = HeroMale | HeroFemale | Summon | Creep | SiegeCreep | AllNeutrals | DummyUnit | FactionChampion,
    Flying = 0x00400000,
    LineOfSight = 0x00200000,
    VulnerableTargetsOnly = 0x00800000,
    Land = 0x01000000,
    Neutral = 0x02000000,
    AffectMounted = 0x04000000,
    VisibleTargetsOnly = 0x08000000,
    Ally = 0x10000000,
    Enemy = 0x20000000,
    Self = 0x40000000,
    AllEnemies = All | Enemy,
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EAbilityAOEVisual
  {
    None,
    Disk,
    Cone,
    Corridor,
    CorridorMax,
    UnattachedSector,
    Wall,
    AttachedSector,
  };

  [Flags]
  public enum EDispatchFlags
  {
    Upgradable = 1 << 0,
    Evadable   = 1 << 1,
    Aggressive = 1 << 2,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // SPELL & ABILITIES
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0678C00)]
  [UseTypeName("DSCH")]
  [FactoryBase("Create", "NWorld::PFDispatch", "NWorld::PFDispatchCreateParams const &cp")]
  [NonTerminal]
  public class Dispatch : DBResource
  {
    [Description("Effect that will be played in the position of dispatch (used by Linear and ByTime types)")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<EffectBase>> dispatchEffect = new List<DBPtr<EffectBase>>();

    [Description("Effect that will be played on the target of the dispatch")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<EffectBase>> applyEffect = new List<DBPtr<EffectBase>>();

    public EApplyEffectOrientation applyEffectOrientation = EApplyEffectOrientation.Default;

    [Description("Number of points for discreet randomization of apply effect orientation (0 = continuos random)")]
    public int applyEffectRandomAnglePoints = 0;

    [Description("If false dispatch will remain after apply. Someone else should kill it eventually.")]
    public bool dieAfterApply = true;

    [Description("Skip CanApplyDispatch check")]
    public bool alwaysApply = false;

    [Description("Ignore target visibility dispatch check for applyEffect. False is default")]
    public bool applyEffectIgnoreVisibility = false;

    [Description("Dispatch flags")]
    public EDispatchFlags flags = 0;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0678C01)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchImmediate", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchImmediate : Dispatch
  {
    [Description("Apply dispatch instantly. Use with caution!")]
    public bool instantApply = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA067A400)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchContinuous", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchContinuous : Dispatch
  {
    [Description("List of persistent applicators that will live along with the dispatch itself")]
    public List<DBPtr<BaseApplicator>> persistentApplicators = new List<DBPtr<BaseApplicator>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0678C02)]
  [UseTypeName("DSCH")]
  [DBVersion(1)]
  [FactoryImpl("Create", "NWorld::PFDispatchByTime", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchByTime : DispatchContinuous
  {
    [Description("Life time of dispatch (in seconds). If negative dispatch dies upon all persistent applicators death.")]
    public ExecutableFloatString lifeTime = new ExecutableFloatString("0.0f");

    [Description("Cancel dispatch on sender's death")]
    public bool cancelOnSenderDeath = true;
  }

  public enum EDispatchAiming
  {
    Straight,
    Homing,
    Pursue,
  }

  [TypeId(0x8D85DC80)]
  [DBVersion(0)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchCursor", "PFDispatchCursor.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchCursor : DispatchContinuous
  {
    [Description("Speed of bullet (in meters/second).")]
    public ExecutableFloatString speed = new ExecutableFloatString("0.0f");

    [Description("Max speed of bullet (in meters/second).")]
    public ExecutableFloatString maxSpeed = new ExecutableFloatString("0.0f");

    [Description("Name of locator (on owner object) dispatch will depart from. If empty, AABB center will be used.")]
    public string fromLocator = "Attack";

    [Description("Высота над террейном")]
    public float height = 0;

    [Description("Время жизни")]
    public ExecutableFloatString lifeTime = new ExecutableFloatString("10.0f");

    [Description("Частота обновления положения курсора в step'ах (1-каждый step, 2-каждый второй step и тд)")]
    public int cursorUpdateFrequency = 5;

    [Description("Расстояние на которое диспатч может удалиться от посылающего")]
    public float linkRange = 0;

    [Description("Эффект-молния который появится между диспатчем и посылающим, когда диспатч удалится на расстояние linkRange")]
    public DBPtr<LightningEffect> linkEffect;

    [Description("AOE-материал для отображения макс. радиуса полёта")]
    public DBPtr<AOEMaterial> maxRangeMaterial;

    [Description("Размер диспатча для отображения maxRangeMaterial")]
    public float size = 0;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0678C03)]
  [DBVersion(0)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchUniformLinearMove", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchLinear : DispatchContinuous
  {
    [Description("Affects chances to lose target if it moves during flight")]
    public EDispatchAiming aiming = EDispatchAiming.Straight;

    [Description("Maximum deviation angle from straight line of fire in degrees (if aiming = Straight)")]
    public float maxDeviation = 180;

    [Description("Speed of bullet (in meters/second).")]
    public float speed = 0;

    [Description("Dispatch effect will use from-locator orientation (otherwise it will use position only).")]
    public bool locatorOrient = true;

    [Description("Name of locator (on owner object) dispatch will depart from. If empty, AABB center will be used.")]
    public string fromLocator = "Attack";

    [Description("Name of locator (on target object) dispatch will arrive to. If empty, AABB center will be used.")]
    public string toLocator = "Body";

    [Description("Высота над toLocator или террейном")]
    public float height = 0;

    [HideEnumValues("FixedHeight")]
    [Description("Trajectory calculation method dispatch starts flying with (may be changed according to environment conditions).")]
    public EDispatchFlyMode flyMode = EDispatchFlyMode.Parabolic;

    [Description("Maximum distance dispatch can travel (negative for unlimited motion).")]
    public float maxDistance = -1.0f;

    [Description("Trajectory height on minimal distance.")]
    public float minRise = 0.0f;

    [Description("Trajectory height on maximal distance.")]
    public float maxRise = 0.0f;

    [Description("Kill dispatch effect upon arrival. If false someone else is responsible for this.")]
    public bool killEffect = true;

    [Description("Time to suspend dispatch before sending it fly")]
    public float suspendTime = 0.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class LightningLink
  {
    [Description("Lightning effect for visualization.")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<LightningEffect>> effect = new List<DBPtr<LightningEffect>>();
  }

  [TypeId(0xA067BBC0)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchWithLink", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchLinearWithLink : DispatchLinear
  {
    public List<LightningLink> links;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA073CA80)]
  [UseTypeName("DSCH")]
  [FactoryImpl("Create", "NWorld::PFDispatchRockmanMace", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
  public class DispatchRockmanMace : DispatchLinearWithLink
  {
    [Description("Minimal distance to send dispatch")]
    public float minDistance = 0.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C5C0B00)]
  [DBVersion(1)]
  [UseTypeName("SPLL")]
  public class Spell : DBResource
  {
    [FieldCategory("Dispatch")]
    public DBPtr<Dispatch> dispatch;

    [FieldCategory("Applicators")]
    [Description("List of applicators that will be applied to the target of the spell. Exceptions: applicators with applyMode = Passive & OnSender")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [IndexField("name")]
  [Custom( "Social" )]
  public class UnitConstant : DBResource
  {
    public string name = string.Empty;
    public ExecutableFloatString var = new ExecutableFloatString("0.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF64AC40)]
  [UseTypeName("UCCN")]
  [Custom( "Social" )]
  public class UnitConstantsContainer : DBResource
  {
    public List<DBPtr<UnitConstant>> vars = new List<DBPtr<UnitConstant>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("MCAI")]
  [FactoryBase("Create", "NWorld::PFMicroAI", "NWorld::PFMicroAICreateParams const &cp")]
  public class MicroAI : DBResource
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("MCAI")]
  [FactoryImpl("Create", "NWorld::PFBasicMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
  public class BasicMicroAI : MicroAI
  {
    [Description("Формула для активации абилки; true = активировать")]
    public ExecutableBoolString condition = new ExecutableBoolString("false");

    [Description("Кастовать только если юнит ничего не делает")]
    public bool castWhenIdle = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("MCAI")]
  [FactoryImpl("Create", "NWorld::PFTargetSelectorMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
  public class TargetSelectorMicroAI : BasicMicroAI
  {
    public DBPtr<SingleTargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("MCAI")]
  [FactoryImpl("Create", "NWorld::PFMultipleTargetSelectorMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
  public class MultipleTargetSelectorMicroAI : BasicMicroAI
  {
    [Description("TargetSelector для поиска целей")]
    public DBPtr<MultipleTargetSelector> targetSelector;

    [Description("Дополнительное условие, на найденные цели")]
    public ExecutableBoolString unitFilter = new ExecutableBoolString("true");

    [Description("Минимальное количество целей для каста абилки. Установить 0 если надо кастовать только когда цели не найдены.")]
    [IntMin(0)]
    public int minTargetCount = 1;

    [Description("Минимальный вес каждой цели")]
    public float minTargetWeight = 0.0f;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("ABCL")]
  [FactoryBase("Check", "NWorld::PFAbilityData", "NWorld::CastLimitationsCheckParams const &cp", ReturnType = "const NWorld::PFAbilityData*")]
  public class CastLimitation : DBResource
  {
    [Description("Error description UI event")]
    public DBPtr<UIEvent> uiEvent;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E71CB80)]
  [UseTypeName("ABCL")]
  [FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckTargetLimitation")]
  public class TargetCastLimitation : CastLimitation
  {
    [Description("Target selector to check target presence")]
    public DBPtr<TargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E71CB81)]
  [UseTypeName("ABCL")]
  [FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckConditionLimitation")]
  public class ConditionCastLimitation : CastLimitation
  {
    [Description("Condition to check validity of cast")]
    public ExecutableBoolString condition = new ExecutableBoolString("true");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E71CB82)]
  [UseTypeName("ABCL")]
  [FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckDispellLimitation")]
  public class DispellCastLimitation : CastLimitation
  {
  }

  [TypeId(0x5BB4ABC0)]
  [UseTypeName("ABCL")]
  [FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckPositionLimitation")]
  public class PositionCastLimitation : CastLimitation
  {
    [Description("Condition to check validity of cast")]
    public ExecutableBooleanString condition = new ExecutableBooleanString("false");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("ALTT")]
  public class AlternativeTarget : DBResource
  {
    public DBPtr<SingleTargetSelector> targetSelector;

    [Description("Alternative target index. Applicators can access it via GetAlternativeTargetIndex()")]
    public int index = 0;

    [Description("Update ability target with alternative one if found")]
    public bool updateTarget = true;

    [Description("Search such targets only if requested from minimap")]
    public bool fromMinimap = false;

    [Description( "Activity that will be used if alternative target found" )]
    public DBPtr<AlternativeActivity> alternativeActivity;
  }

  [UseTypeName("ACTV")]
  public class AlternativeActivity : DBResource
  {
    public ExecutableFloatString useRange = new ExecutableFloatString( "0.0f" );

    public EAbilityFlags flags = 0;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C5C0B01)]
  [IndexField("caption")]
  [DBVersion(7)]
  [UseTypeName("ABLT")]
  public class Ability : Spell
  {
    [NoCode]
    [FieldCategory("Description")]
    [Description("Caption of ability")]
    [Custom( "Social" )]
    public string caption = string.Empty;

    [FieldCategory("Description")]
    [Description("Name of ability/artifact/glyph")]
    [Custom( "Social" )]
    public TextRef name = new TextRef();

    [FieldCategory("Description")]
    [Description("Description of ability/artifact/glyph")]
    [Custom("Social")]
    public TextRef description = new TextRef();

    [Browsable(false)]
    [FieldCategory("Description")]
    [Description("Description of ability/artifact/glyph")]
    [Custom( "Social" )]
    public TextRef compiledDescriptionA = new TextRef();

    [Browsable(false)]
    [FieldCategory("Description")]
    [Description("Description of ability/artifact/glyph")]
    [Custom( "Social" )]
    public TextRef compiledDescriptionB = new TextRef();

    [FieldCategory("Description")]
    [Description("Short description of ability/artifact/glyph")]
    public TextRef shortDescription = new TextRef();

    [Description("Common description part that can be substituted as $(commonDescription)")]
    public TextRef commonDescription = new TextRef();

    [FieldCategory("Description")]
    [Description("List of possible cast limitations")]
    public List<DBPtr<CastLimitation>> castLimitations = new List<DBPtr<CastLimitation>>();

    [FieldCategory("UI")]
    [Description("UI texture that will be shown in action bar (and status bar)")]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [FieldCategory("UI")]
    [Description("UI texture that will be shown in action bar (and status bar) when ability is switched off.")]
    public DBPtr<Render.DBRenderResources.Texture> imageSecondState;

    [FieldCategory("UI")]
    [Description("Target zone visual shape.")]
    public EAbilityAOEVisual aoeType = EAbilityAOEVisual.None;

    [FieldCategory("UI")]
    [Description("Target zone size, interpreted differently. For DISK - radius in meters. For CONE - half of the angle in degrees. For CORRIDOR - the width in meters.")]
    public ExecutableFloatString aoeSize = new ExecutableFloatString("0.0f");

    [FieldCategory("UI")]
    [Description("Target zone material.")]
    public DBPtr<AOEMaterial> aoeMaterial;

    [FieldCategory("UI")]
    [Description("Target zone height.")]
    public float aoeHeight = 0.0f;

    [FieldCategory("UI")]
    [Description("Target zone range material")]
    public DBPtr<AOEMaterial> useRangeMaterial;

    [FieldCategory("UI")]
    [Description("Target zone passability check mode for corridor AOE. 0 (zero) means no check.")]
    public ETraceMode aoePassabilityCheckMode = 0;

    [FieldCategory("UI")]
    [Description("Отображать ли радиус действия на мини-карте")]
    public bool aoeDisplayOnMinimap = false;

    [FieldCategory("Logic")]
    [Description("Type of ability. Don't use Autocastable.")]
    [Custom( "Social" )]
    public EAbilityType type = EAbilityType.Passive;

    [FieldCategory("Logic")]
    [Description("Cooldown time of ability. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]")]
    [Custom("Social")]
    public ExecutableFloatString cooldownTime = new ExecutableFloatString("0.0f");

    [FieldCategory("Logic")]
    [Description("Cooldown time of ability for a second state. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]")]
    public ExecutableFloatString cooldownTimeSecondState = new ExecutableFloatString("0.0f");

    [FieldCategory("Logic")]
    [Description("Mana cost of ability. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]")]
    [Custom("Social")]
    public ExecutableFloatString manaCost = new ExecutableFloatString("0.0f");

    [FieldCategory("Logic")]
    [Description("for TriggerAbilitiesFilter")]
    public bool activeCustomTrigger = true;

    [FieldCategory("Logic")]
    [Description("Using range of ability (in meters)")]
    public ExecutableFloatString useRange = new ExecutableFloatString("0.0f");

    [FieldCategory("Logic")]
    [Description("min range to witch ability range is stretched when its less than minUseRangeCorrection(in meters)")]
    public float minUseRangeCorrection = 0.0f;

    [Description( "Расстояние до цели на котором абилка сработает (случай ченнелинга). Если <= 0, то будет считаться по умолчанию (см. настройку channelingAbilityRangeMultiplier)" )]
    public ExecutableFloatString castAllowRange = new ExecutableFloatString( "0.0f" );

    [Description( "Allow or disallow chasing ability's target (currently attack ability only)" )]
    public ExecutableBoolString allowChase = new ExecutableBoolString( "true" );

    [FieldCategory("Logic")]
    [Custom( "Social" )]
    public DBPtr<UnitConstantsContainer> constants;

    [FieldCategory("Logic")]
    [Custom("Social")]
    public List<DBPtr<ConditionFormula>> conditionFormulas = new List<DBPtr<ConditionFormula>>();

    [FieldCategory("Logic")]
    [Description("If true then unit can do anything after workTime, if false then after program(applicators) end")]
    public bool isUnitFreeAfterCast = true;

    [FieldCategory("Logic")]
    [Custom("Social")]
    public EAbilityFlags flags = EAbilityFlags.FocusOnTarget;

    [FieldCategory("Targets")]
    [Description("Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender.")]
    [Custom("Social")]
    public ESpellTarget targetType = ESpellTarget.All | ESpellTarget.VisibleTargetsOnly;

    [FieldCategory("Targets")]
    [Description("Describes if direct line of side is needed to target unit")]
    public bool requireLineOfSight = true;

    [FieldCategory("Applicators")]
    [Custom( "Social" )]
    [Description("List of applicators that will be applied to the owner of the spell then attach it to owner.")]
    public List<DBPtr<BaseApplicator>> passiveApplicators = new List<DBPtr<BaseApplicator>>();

    [FieldCategory("Targets")]
    [Description("Target selector использующийся для выбора дефолтовой цели")]
    public DBPtr<SingleTargetSelector> autoTargetSelector;

    [FieldCategory("Targets")]
    [Description("Микро ИИ данной абилки. Используется в крипах или в ИИ-героях")]
    public DBPtr<MicroAI> microAI;

    [FieldCategory("Animations")]
    public string node = "";

    [FieldCategory("Animations")]
    public string marker = "";

    [FieldCategory("WarFog")]
    [Description("Defines time for removing WarFog around attacker after dispatch delivery to target (seconds).")]
    public float warFogRemoveTime = 0.0f;

    [FieldCategory("WarFog")]
    [Description("Defines radius for removing WarFog around attacker after dispatch delivery to target (meters).")]
    public float warFogRemoveRadius = 0.0f;

    public List<DBPtr<AlternativeTarget>> alternativeTargets;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C5CCAC0)]
  [UseTypeName("ATCK")]
  public class BaseAttack : Ability
  {
    [Description("Считать автоатаку милишной")]
    public bool isMelee = false;
  }
}
