//#include "DBAnimations.cs"
//#include "DBStats.cs"
//#include "DBGameLogic.cs"
//#include "DBSummonApplicator.cs"
//#include "DBGlyph.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBAnimations;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBConsumable;
using PF_GameLogic.DBDayNight;
using Scene.DBScene;
using Scene.DBSceneBase;

namespace PF_GameLogic.DBAbility
{
  public enum EUnitFlagType
  {
    ForbidMove = 0,
    ForbidSelectTarget,
    ForbidAttack,
    Forbid_Ability1,
    Forbid_Ability2,
    Forbid_Ability3,
    Forbid_Ability4,
    ForbidTakeDamage,
    ForbidAutotargetMe,
    ForbidUseConsumables, 
    ForbidUseTalents,
    Invisible,
    CanSeeInvisible,
    Stun,
    ForbidLifeRestore,
    ForbidEnergyRestore,
    IgnoreInvisible,
    ForbidMoveSpecial,
    ForbidDeath,
    ForbidInteract,
    Flying,
    ForbidAutoAttack,
    ForbidPick,
    ForbidPlayerControl,
    CanTurnWhileForbidMove,
    Freeze,
    IgnorePush,
    ForbidInvisibility,
    InMinigame,
    LiveAfterDeath,
    ForbidRewards
  };

  [Flags]
  public enum EUnitFlag
  {
    ForbidMove             = (1 << EUnitFlagType.ForbidMove),
    ForbidSelectTarget     = (1 << EUnitFlagType.ForbidSelectTarget),
    ForbidAttack           = (1 << EUnitFlagType.ForbidAttack),
    Forbid_Ability1        = (1 << EUnitFlagType.Forbid_Ability1),
    Forbid_Ability2        = (1 << EUnitFlagType.Forbid_Ability2),
    Forbid_Ability3        = (1 << EUnitFlagType.Forbid_Ability3),
    Forbid_Ability4        = (1 << EUnitFlagType.Forbid_Ability4),
    ForbidTakeDamage       = (1 << EUnitFlagType.ForbidTakeDamage),
    ForbidAutotargetMe     = (1 << EUnitFlagType.ForbidAutotargetMe),
    ForbidUseConsumables   = (1 << EUnitFlagType.ForbidUseConsumables),
    ForbidUseTalents       = (1 << EUnitFlagType.ForbidUseTalents),
    Isolated               = ForbidMove | ForbidSelectTarget | ForbidAttack | Forbid_Ability1 | Forbid_Ability2 | Forbid_Ability3 |
                             Forbid_Ability4 | ForbidTakeDamage | ForbidAutotargetMe | ForbidUseConsumables | ForbidUseTalents,
    Invisible              = (1 << EUnitFlagType.Invisible),
    CanSeeInvisible        = (1 << EUnitFlagType.CanSeeInvisible),
    Stun                   = (1 << EUnitFlagType.Stun),
    ForbidLifeRestore      = (1 << EUnitFlagType.ForbidLifeRestore),
    ForbidEnergyRestore    = (1 << EUnitFlagType.ForbidEnergyRestore),
    IgnoreInvisible        = (1 << EUnitFlagType.IgnoreInvisible),
    ForbidMoveSpecial      = (1 << EUnitFlagType.ForbidMoveSpecial),
    ForbidDeath            = (1 << EUnitFlagType.ForbidDeath),
    ForbidInteract         = (1 << EUnitFlagType.ForbidInteract),
    Flying                 = (1 << EUnitFlagType.Flying),
    ForbidAutoAttack       = (1 << EUnitFlagType.ForbidAutoAttack),
    ForbidPick             = (1 << EUnitFlagType.ForbidPick),
    ForbidPlayerControl    = (1 << EUnitFlagType.ForbidPlayerControl),
    CanTurnWhileForbidMove = (1 << EUnitFlagType.CanTurnWhileForbidMove),
    Freeze                 = (1 << EUnitFlagType.Freeze),
    IgnorePush             = (1 << EUnitFlagType.IgnorePush),
    ForbidInvisibility     = (1 << EUnitFlagType.ForbidInvisibility),
    InMinigame             = (1 << EUnitFlagType.InMinigame),
    LiveAfterDeath         = (1 << EUnitFlagType.LiveAfterDeath),
    ForbidRewards          = (1 << EUnitFlagType.ForbidRewards),
  };

  public enum EBaseUnitEvent
  {
    Move = 0,
    CastMagic,
    UseConsumable,
    UseTalent,
    Attack,
    ForbidMove,
    ForbidAttack,
    ForbidCast,
    ForcedMove,
    DispatchApplied,
    DispatchEvaded,
    Damage,
    Isolate,
    ApplicatorStep,
    ApplicatorApplied,
    Death,
    AssignTarget,
    LastHit,
    ForbidAutoAttack,
    Pickup,
    Resurrect,
    AbilityStart,
    ChannelingCanceled,
    CancelInvisibility,
    Unsummon,
    ConsumableObtained,
    UsePortal,
    WantMoveTo,
    OutgoingDamage,
    DispatchMissed,
    HeroKillOrAssist,
    MinigameStarted,
    MinigameExit,
    MinigameLevelStarted,
    MinigameLevelWon,
    MinigameLevelFailed,
  };

  [Flags]
  public enum EBaseUnitEventFlags
  {
    Zero              = 0,
    Move              = 1 << EBaseUnitEvent.Move,
    CastMagic         = 1 << EBaseUnitEvent.CastMagic,
    UseConsumable     = 1 << EBaseUnitEvent.UseConsumable,
    UseTalent         = 1 << EBaseUnitEvent.UseTalent,
    Attack            = 1 << EBaseUnitEvent.Attack,
    ForbidMove        = 1 << EBaseUnitEvent.ForbidMove,
    ForbidAttack      = 1 << EBaseUnitEvent.ForbidAttack,
    ForbidCast        = 1 << EBaseUnitEvent.ForbidCast,
    ForcedMove        = 1 << EBaseUnitEvent.ForcedMove,
    DispatchApplied   = 1 << EBaseUnitEvent.DispatchApplied,
    DispatchEvaded    = 1 << EBaseUnitEvent.DispatchEvaded,
    Damage            = 1 << EBaseUnitEvent.Damage,
    Isolate           = 1 << EBaseUnitEvent.Isolate,
    ApplicatorStep    = 1 << EBaseUnitEvent.ApplicatorStep,
    ApplicatorApplied = 1 << EBaseUnitEvent.ApplicatorApplied,
    Death             = 1 << EBaseUnitEvent.Death,
    AssignTarget      = 1 << EBaseUnitEvent.AssignTarget,
    LastHit           = 1 << EBaseUnitEvent.LastHit,
    ForbidAutoAttack  = 1 << EBaseUnitEvent.ForbidAutoAttack,
    Pickup            = 1 << EBaseUnitEvent.Pickup,
    Resurrect         = 1 << EBaseUnitEvent.Resurrect,
    AbilityStart      = 1 << EBaseUnitEvent.AbilityStart,
    ChannelingCanceled = 1 << EBaseUnitEvent.ChannelingCanceled,
    CancelInvisibility = 1 << EBaseUnitEvent.CancelInvisibility,
    Unsummon          = 1 << EBaseUnitEvent.Unsummon,
    UsePortal         = 1 << EBaseUnitEvent.UsePortal,
    DispatchMissed      = 1 << EBaseUnitEvent.DispatchMissed,
    HeroKillOrAssist = 1 << EBaseUnitEvent.HeroKillOrAssist,
  };

  public enum EApplicatorDamageType
  {
    Material = 0,
    Energy,
    Mana,
    Pure,
    Native,
  }

  [Flags]
  public enum EDamageMode
  {
    Zero              = 0,
    ApplyLifeDrains   = 1,
    ApplyEnergyDrains = 2,
    DontAttackBack    = 4,
    CouldBeCritical   = 8,
  }

  public enum EHealTarget
  {
    Health = 0,
    Energy = 1,
  }

  public enum EApplicatorApplyTarget
  {
    ApplicatorTarget = 0,
    AbilityOwner,
    PrevApplicatorTarget,
    PrevApplicatorReceiver,
    Hier1UpApplicatorTarget,
    Hier2UpApplicatorTarget,
    Hier3UpApplicatorTarget,
    AbilityTarget,
    ApplicatorSelectedTarget,
    CastPosition,
    CastMasterPosition,
  }

  [Flags]
  public enum EBuffBehavior
  {
    Zero                  = 0,
    StopOnDisable         = (1 << 0),
    RemoveChildren        = (1 << 1),
    DontShowInBar         = (1 << 2),
    DontStopOnDeath       = (1 << 3),
    EnabledOnSenderDeath  = (1 << 4),
    DontRemoveEffect      = (1 << 5),
    ApplyToDead           = (1 << 6),
    DontStopOnSenderDeath = (1 << 7)
  }

  public enum EParentNotification
  {
    NA = -1,
    Start = 0,
    Stop,
    Done,
    Cancel,
  }

  [Flags]
  public enum EParentNotificationFlags
  {
    Zero   = 0,
    Start  = (1 << EParentNotification.Start),
    Stop   = (1 << EParentNotification.Stop),
    Done   = (1 << EParentNotification.Done),
    Cancel = (1 << EParentNotification.Cancel),
  }

  [Flags]
  public enum EBehaviourChangeFlags
  {
    Zero = 0,
    DummyBehaviour = 1,
    ChangeFaction = 2,
    PrimarySummon = 4,
    ChangePermanently = 8,
    ChangeType2Summon = 16,
    DisableBehaviour = 32,
  }

  public enum EUnitCreationPlace
  {
    DirectToTarget = 0,
    AtTarget,
    AtCreator,
  }

  public enum EScaleCalculationMode
  {
    ScaleIsCount = 0,
    ScaleIsTime,
    ScaleIsVPar,
  }

  [Flags]
  public enum EWaitForSpellBehaviour
  {
    Zero                           = 0,
    StopWhenSpellFinished          = 1 << 0,
    UpdateParentTarget             = 1 << 1,
    DontApplyEffectOnFirstTarget   = 1 << 2,
  }

  public enum EKickAwayBehaviour
  {
    KickFromSender,
    KickFromHier1UpTarget,
    KickFromHier1UpTargetMoveDirection,
  }

  public enum EStopBehaviour
  {
    StopByTime,
    StopByChild,
    StopByAllChilds,
  }

  public enum EDispellPriority
  {
    NonDispellable = -1,
    Low    = 0,
    Medium = 1,
    High   = 2,
  }

  [Flags]
  public enum EDamageFilter
  {
    Zero     = 0,
    Melee    = (1 << 0),
    Ranged   = (1 << 1),
    Material = (1 << 2),
    Energy   = (1 << 3),
    Pure     = (1 << 4),
    All      = Melee | Ranged | Material | Energy | Pure,
  }

  public enum EAttackTargetEvadeAction
  {
    AttackAgain,
    StopAsComplete,
    StopAsFailed,
  }

  public enum EAbilityTypeId
  {
    BaseAttack,
    Ability0,
    Ability1,
    Ability2,
    Ability3,
    Ability4,
    Consumable,
    Talent,
    TalentFromList,
    ImpulsiveBuff,
    Special,
    Portal,
  }
  
  [Flags]
  public enum EAbilityIdFlags
  {
    Specific    = 0,
    BaseAttack  = (1 << EAbilityTypeId.BaseAttack),
    Ability1    = (1 << EAbilityTypeId.Ability1),
    Ability2    = (1 << EAbilityTypeId.Ability2),
    Ability3    = (1 << EAbilityTypeId.Ability3),
    Ability4    = (1 << EAbilityTypeId.Ability4),
    Consumables = (1 << EAbilityTypeId.Consumable),
    Talents     = (1 << EAbilityTypeId.Talent),
    Portal      = (1 << EAbilityTypeId.Portal),
    All = BaseAttack | Ability1 | Ability2 | Ability3 | Ability4 | Consumables | Talents | Portal,
  }

  public enum EAbilityModMode
  {
    naftacost,
    manacost,
    cooldown,
    scale,
    duration,
    state,
  }

  public enum EStatConstraint
  {
    None,
    UpperLimit,
    LowerLimit,
  }

  [NoCode]
  public enum ECustomApplyType
  {
    None = 0,
    Maximize = 1,
    Minimize = 2,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Custom("Social")]
  public class Modifier
  {
    [Description("Stat to be modified")]
    public EStat stat;

    [Description("Value to be modified")]
    public string variable;

    [Description("Value to be added to stat [Formula update: every step]")]
    public ExecutableFloatString addValue = new ExecutableFloatString("0.0f");

    [Description("Value to be multiplied on stat [Formula update: every step]")]
    public ExecutableFloatString multValue = new ExecutableFloatString("1.0f");

    [Description("This modifier is applied to top")]
    public bool topModifier = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF724340)]
  [UseTypeName("APLS")]
  public class ApplicatorsList : DBResource
  {
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();
    public List<DBPtr<ApplicatorsList>> applicatorLists = new List<DBPtr<ApplicatorsList>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B00)]
  [DBVersion(0)]
  [UseTypeName("APLR")]
  [IndexField("caption")]
  [FactoryBase("Create", "NWorld::PFBaseApplicator", "NWorld::PFApplCreatePars const &cp")]
  [NonTerminal]

  public class BaseApplicator : DBResource
  {
    [Description("Enables/disables applicator. [Formula update: every step]")]
    [Custom( "Social" )]
    public ExecutableBoolString enabled = new ExecutableBoolString("true");

    [Description("Specifies the target for applying the applicator. Basically it is the target of the applicator, but you can select different target")]
    public EApplicatorApplyTarget applyTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Name of applicator to access from formulas")]
    public string formulaName = "";
    
    [NoCode]
    [Custom( "Social" )]
    public string caption = string.Empty;

    [Description("Number of logging event")]
    public int LoggingEvent = -1;

    [Description("PersistentId of a talent providing this applicator")]
    public string providerName = string.Empty;
  }

  [TypeId(0xE794DC40)]
  [UseTypeName( "ADBIC" )]
  [FactoryImpl( "Create", "NWorld::PFBaseApplicator", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class ApplicatorNameOverrider : BaseApplicator
  {
    public DBPtr<BaseApplicator> applicator;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B01)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDamage", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DamageApplicator : BaseApplicator
  {
    [Description("Damage to be dealt to target [Formula update: once]")]
    public ExecutableFloatString damage = new ExecutableFloatString("0.0");

    [Description("Damage type. Material/Energy - damage, Mana - mana-burn")]
    public EApplicatorDamageType damageType = EApplicatorDamageType.Material;

    [Description("ApplyDrains - apply life & energy drain, DontAttackBack - target willn't attack back if idle")]
    public EDamageMode damageMode = EDamageMode.Zero;

    [Description("Cancel owner's invisibility")]
    public bool cancelInvisibility = false;

    [Description("UI Event")]
    public DBPtr<UIEvent> uiEvent;

    [Description("Limiter time for applicator [if -1.0 then don't check it]")]
    public float timeLimiter = -1.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0617B80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplHeal", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class HealApplicator : BaseApplicator
  {
    [Description("Amount to be added")]
    public ExecutableFloatString amount = new ExecutableFloatString("0.0");

    [Description("Health - add amount to health; Energy - add amount to energy")]
    public EHealTarget healTarget = EHealTarget.Health;

    [Description("UI Event")]
    public DBPtr<UIEvent> uiEvent;

    [Description( "Не применять модификаторы при хиле юнита, отличного от кастера" )]
    public bool ignoreHealingMods = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EKillMode
  {
    None = 0,
    DontShowDeath,
    InstantRemove,
    Unsummon
  }

  [DBVersion(1)]
  [TypeId(0x9E678B02)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplKill", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class KillApplicator : BaseApplicator
  {
    [Description("Kill flag: Don't show death animation, Instant remove on death")]
    public EKillMode flag = EKillMode.None;
    [Description("Do not reward killer")]
    public bool dontGiveRewards = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB75FB81)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAbilityEnd", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AbilityEndApplicator : BaseApplicator
  {
    [Description("Cancel ability applicators applied to sender")]
    public bool cancelApplicators = true;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E67C380)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplTeleport", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class TeleportApplicator : BaseApplicator
  {
    [Description("Target to teleport to")]
    public EApplicatorApplyTarget teleportTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Maximal teleport distance (if 0 or less - teleport distance is not limited)")]
    public ExecutableFloatString maxDistance = new ExecutableFloatString("0.0f");

    [Description("Effect of disappearing. Played on the place where teleporting unit was standing.")]
    public DBPtr<EffectBase> disappearEffect;

    [Description("Effect of appearing. Played on the place where teleporting unit standing after teleport.")]
    public DBPtr<EffectBase> appearEffect;

    [Description("When true, this applicator will free place for teleporting unit by pushing other units avay.")]
    public bool pushUnits = false;

    [Description("Notify inbound dispatches")]
    public bool notifyInboundDispatches = true;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E67DB00)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDispell", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DispellApplicator : BaseApplicator
  {
    [Description("Maximal amount of effects to be dispelled at once")]
    public ExecutableIntString maxEffectsToDispell = new ExecutableIntString("1");

    [Description("Цели по которым диспеллить (опционально)")]
    public DBPtr<TargetSelector> targets;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E678B02)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAttackTarget", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AttackTargetApplicator : BuffApplicator
  {
    [Description("Target to attack")]
    public EApplicatorApplyTarget attackTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Number attacks")]
    public int attackCount = -1;

    [Description("What to do when attack is evaded")]
    public EAttackTargetEvadeAction evadeAction = EAttackTargetEvadeAction.StopAsFailed;

    [Description( "Allow attack invisible (concealed by warfog too) targets" )]
    public bool ignoreVisibility = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E67ACC1)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplWaitForSpell", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class WaitForSpellApplicator : BuffApplicator
  {
    [Description("Spell target")]
    public EApplicatorApplyTarget spellTarget;

    [Description("Spell to send")]
    public DBPtr<Spell> spell;

    [Description("Behaviour description")]
    public EWaitForSpellBehaviour behaviour = EWaitForSpellBehaviour.Zero;

    [Description("Dispatch will hit found target and stop")]
    public DBPtr<SingleTargetSelector> firstTargetToHit;

    [Description("Source of dispatch. Applytarget by default.")]
    public DBPtr<SingleTargetSelector> dispatchSource;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B02)]
  [UseTypeName("APLR")]
  [NonTerminal]
  public class BuffApplicator : BaseApplicator
  {
    [Description("StopOnDisable - buff will be dropped when become disabled (in normal state it could be enabled again)")]
    public EBuffBehavior behaviorFlags = EBuffBehavior.Zero;

    [Description("Life time of buff (in seconds); specify -1 as infinity")]
    public ExecutableFloatString lifeTime = new ExecutableFloatString("-1.0");

    [Description("Visual effect of buff")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<EffectBase>> effect = new List<DBPtr<EffectBase>>();

    [Description("Проверка на запуск аппликатора (не путать с enabled!)")]
    public ExecutableBoolString startCondition = new ExecutableBoolString("true");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum EUpdateDurationFlags
  {
    None               = 0,
    CheckByFormulaName = (1 << 0),
    SetDuration        = (1 << 1),
  }

  [TypeId(0x2B82CC80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAddApplicatorDuration", "PFApplBuff.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AddApplicatorDuration : BaseApplicator
  {
    public ExecutableFloatString durationToAdd = new ExecutableFloatString("-1.0");
    public List<DBPtr<BuffApplicator>> applicators;
    public EUpdateDurationFlags flags = 0;
    public string nameToCheck;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B03)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplStatMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class StatModApplicator : BuffApplicator
  {
    [FieldCategory("StatModifier")]
    public Modifier modifier;

    [Description("Don't update modifier")]
    public bool dontUpdate = false;

    [Description("Name for resolving constants while merging statuses in UI, must be same as constant name used in modifier and tooltip")]
    public string statModName = "";

    [Description( "Calculated value (baseValue * multValue + addValue) becomes a constraint" )]
    public EStatConstraint constraint = EStatConstraint.None;

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E688C00)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplPermanentStatMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  [Custom( "Social" )]
  public class PermanentStatModApplicator : BaseApplicator
  {
    [NoCode]
    public ECustomApplyType customApplyType = ECustomApplyType.None;

    [FieldCategory("StatModifier")]
    public Modifier modifier;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EUseMode
  {
    ListAsRule,
    ListAsException,
  }

  [TypeId(0xF6BCC40)]
  [UseTypeName("APLR")]
  [DBVersion(1)]
  [FactoryImpl("Create", "NWorld::PFApplAbilityMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AbilityModApplicator : BuffApplicator
  {
    [FieldCategory("Ability Modification")]
    [Description("Value to be added to stat [Formula update: every step]")]
    public ExecutableFloatString addValue = new ExecutableFloatString("0.0f");

    [FieldCategory("Ability Modification")]
    [Description("Value to be multiplied on stat [Formula update: every step]")]
    public ExecutableFloatString multValue = new ExecutableFloatString("1.0f");

    [FieldCategory("Ability Modification")]
    public EAbilityIdFlags targetAbilities = EAbilityIdFlags.All;

    [FieldCategory("Ability Modification")]
    public EAbilityModMode mode = EAbilityModMode.naftacost;

    [FieldCategory("Ability Modification")]
    [Description("Ability to modify (used only if targetAbilities == Specific)")]
    public DBPtr<Ability> specificAbility;

    [FieldCategory("Ability Modification")]
    [Description("Список улучшаемых талантов/предметов")]
    public List<DBPtr<Ability>> talents = new List<DBPtr<Ability>>();

    [FieldCategory("Ability Modification")]
    [Description("Режим работы со списком")]
    public EUseMode useListAs = EUseMode.ListAsException;
  }

  [Flags]
  public enum EAbilityUpgradeMode
  {
    None                = 0,
    DontUseOriginal     = 1,
    UseAbilityMana      = 2,
    UseAbilityCooldown  = 4,
    UseGlyph            = 8,
    ChangeIcon          = 16,
    ApplyOncePerCast    = 32,
    ApplyOncePerCastPerTarget = 64,
  }
  
  [DBVersion(2)]
  [TypeId(0xF6C0C40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAbilityUpgrade", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AbilityUpgradeApplicator : BuffApplicator
  {
    [FieldCategory("Ability Modification")]
    [Description("Extended upgrade properties")]
    public EAbilityUpgradeMode flags = EAbilityUpgradeMode.None;

    [FieldCategory("Ability Modification")]
    [Description("Ability to upgrade (use only with BaseAttack or Ability1 - Ability4)")]
    public EAbilityTypeId targetAbility = EAbilityTypeId.BaseAttack;

    [FieldCategory("Ability Modification")]
    [Description("Applicators to attach")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();
    
    [FieldCategory("Ability Modification")]
    [Description("Persistent applicators to attach")]
    public List<DBPtr<BaseApplicator>> persistentApplicators = new List<DBPtr<BaseApplicator>>();

    [FieldCategory("Ability Modification")]
    [Description("Upgrades counter (0 if infinite)")]
    public ExecutableIntString applyCount = new ExecutableIntString("0");

    [FieldCategory("Ability Modification")]
    [Description("Список улучшаемых талантов")]
    public List<DBPtr<Ability>> talents = new List<DBPtr<Ability>>();

    [FieldCategory("Ability Modification")]
    [Description("Режим работы со списком")]
    public EUseMode useListAs = EUseMode.ListAsRule;
  }

  [DBVersion(0)]
  [TypeId(0x15DC6040)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplTechAbilityUpgrade", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AbilityUpgradeTechApplicator : BaseApplicator
  {
    [HideInOutliner]
    public int abilityObjectId = 0;
    [HideInOutliner]
    public int abilityLastUseStep = 0;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E678AC0)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChangeBaseAttack", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChangeBaseAttackApplicator : BuffApplicator
  {
    [Description("This attack ability replaces attack ability of the unit")]
    public DBPtr<BaseAttack> attackAbility;

    public bool applyPassivePart = true;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E678B04)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplWatch", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class WatchApplicator : BuffApplicator
  {
    [Description("Event will be send to the parent when dispatch from ability owner is applied to watched unit")]
    public EParentNotification onSenderDispatchApply = EParentNotification.NA;
    [Description("Event will be send to the parent when dispatch from ability owner is evaded by watched unit")]
    public EParentNotification onSenderDispatchEvade = EParentNotification.NA;
    [Description("Event will be send to parent on watched unit death")]
    public EParentNotification onUnitDeath = EParentNotification.NA;
    [Description("Event will be send to parent when this applicator finishes and watched unit is still alive")]
    public EParentNotification onFinish = EParentNotification.NA;
    [Description("Event will be send to the parent when dispatch from ability owner is missed by watched unit")]
    public EParentNotification onSenderDispatchMiss = EParentNotification.NA;

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EAuraVisualType
  {
    None,
    Ally,
    Enemy,
  }

  [DBVersion(1)]
  [TypeId(0x9E5C0B04)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAura", "PFApplAura.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AuraApplicator : BuffApplicator
  {
    [Description("Targets selector")]
    public DBPtr<TargetSelector> targetSelector;

    [FieldCategory("Aura")]
    [Description("Affecting range (in meters)")]
    public ExecutableFloatString range = new ExecutableFloatString("0.0f");

    [FieldCategory("Aura")]
    [Description("Flags to specify targets of the aura. The same as targetType field in Spell")]
    public ESpellTarget targets = ESpellTarget.All | ESpellTarget.VulnerableTargetsOnly;

    [FieldCategory("Aura")]
    [Description("Тип ауры: дружественная или враждебная. Используется для визуального эффекта на кастующего.")]
    public EAuraVisualType type = EAuraVisualType.None;

    [FieldCategory("Applicators")]
    [Description("List of aura applicators")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF622B41)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDropTree", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DropTreeApplicator : BaseApplicator
  {
  // public float range = 5.0f;
  }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB76AA41)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplRaiseFlag", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class RaiseFlagApplicator : ChannellingApplicator
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E677240)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSpell", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  [DBVersion(1)]
  public class SpellApplicator : BaseApplicator
  {
    [Description("Targets selector")]
    public DBPtr<TargetSelector> targetSelector;

    [Description("Target to spell (works only if no target selector used)")]
    public EApplicatorApplyTarget spellTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Spell that will be applied to the targets")]
    public DBPtr<Spell> spell;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0BFD)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSpellProbability", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SpellProbabilityApplicator : BaseApplicator
  {
    [Description("Probability of a spell (within 0..100 interval)")]
    public ExecutableFloatString probability = new ExecutableFloatString("100.0");

    [Description("Spell that will be applied to the target in the case of passing probability check")]
    public DBPtr<Spell> spell;

    [Description("Spell that will be applied to the target in the case of failing probability check")]
    public DBPtr<Spell> spellIfFailed;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x0E674B40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSpellSwitch", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SpellSwitchApplicator : BaseApplicator
  {
    [Description("Index of default(active) spell")]
    public ExecutableIntString activeSpellIndex = new ExecutableIntString("0");

    [Description("Don't use spell dispatches, apply instantly")]
    public bool dontUseDispatches = false;

    [Description("Spell list to select active spell from.")]
    public List<DBPtr<Spell> > spells = new List<DBPtr<Spell> > ();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B08)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSpellPeriodically", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SpellPeriodicallyApplicator : BuffApplicator
  {
    [Description("Period of time (in sec)")]
    public ExecutableFloatString period = new ExecutableFloatString("0.0f");

    [Description("Start offset before first strike (in sec)")]
    public ExecutableFloatString startOffset = new ExecutableFloatString("0.0f");

    [Description("The mode of scale calculation")]
    public EScaleCalculationMode scaleMode = EScaleCalculationMode.ScaleIsCount;

    [Description("Targets selector")]
    public DBPtr<TargetSelector> targetSelector;

    [Description("Spell that will be cast on the target of applicator every 'period' of time")]
    public DBPtr<Spell> spell;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E6CF400)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSpellPeriodicallyVisual", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SpellPeriodicallyVisualApplicator : SpellPeriodicallyApplicator
  {
    [Description("Period of time (in sec)")]
    public ExecutableFloatString attackTimeOffset = new ExecutableFloatString("0.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x0E676B40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplNaftaTransfer", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class NaftaTransferApplicator : BaseApplicator
  {
    [Description("Nafta is transfered from receiver of this applicator to this target")]
    public EApplicatorApplyTarget naftaTransferTarget = EApplicatorApplyTarget.AbilityOwner;

    [Description("Amount of nafta to be taken from receiver")]
    public ExecutableFloatString amount = new ExecutableFloatString("0.0f");

    [Description("Multiplier of nafta to be transfered")]
    public ExecutableFloatString multiplier = new ExecutableFloatString("1.0f");
    [Description("Bonus nafta to be transfered")]
    public ExecutableFloatString addition = new ExecutableFloatString("0.0f");

    [Description("UI Event")]
    public DBPtr<UIEvent> uiEvent;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(0)]
  [TypeId(0x0E676B42)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplModifyTerrain", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ModifyTerrainApplicator : BaseApplicator
  {
    [Description("Time of modification")]
    public ExecutableFloatString durationTime = new ExecutableFloatString("5.0f");

    [Description("Faction")]
    public ExecutableIntString faction       = new ExecutableIntString("0");
    
    [Description("Modification radius")]
    public ExecutableFloatString modifRadius = new ExecutableFloatString("1.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x0E676B80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplMoveTo", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class MoveToApplicator : BuffApplicator
  {
    [Description("Destination we going to move.")]
    public ExecutableFloatString moveRange = new ExecutableFloatString("1.0f");

    [Description("(isMoveDirect mode only!) Movement speed in MPs")]
    public ExecutableFloatString moveSpeed = new ExecutableFloatString("0.0f");

    [Description("Movement target")]
    public EApplicatorApplyTarget moveTarget;

    [Description("Offset off target (negative_Y is pointing towards target)")]
    public Vec2 offset = new Vec2(0.0f, 0.0f);

    [Description("Should we move trough obstacles?")]
    public ExecutableBoolString isMoveDirect = new ExecutableBoolString("true");

    [Description( "(isMoveDirect mode only!) should free place for unit by pushing other units avay?" )]
    public bool pushUnits = false;

    [Description("Don't move, just rotate to target")]
    public bool justRotate = false;

    [Description("Not stackable MoveTo applicator")]
    public bool isNotStackable = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum EGhostMoveMode
  {
    IgnoreDynamic   = 1,
    IgnoreBuildings = 2,
    IgnoreStatic    = 4,
  }

  [TypeId(0xB74F480)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplGhostMove", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class GhostMoveApplicator : BuffApplicator
  {
    [FieldCategory("Mode")]
      [Description("Dynamic - collide with moving units, Buildings - collide with buildings, Static - collide with static objects")]
    public EGhostMoveMode collisionFlags = 0;

    [Description("When true, this applicator will free place for unit by pushing other units away - after stopping applicator.")]
    public bool pushUnits = true;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(1)]
  [TypeId(0x9E5C0B06)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplFlags", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class FlagsApplicator : BuffApplicator
  {
    [FieldCategory("Flags")]
    [Description("Specify different flags to be set")]
    public EUnitFlag flag = 0; 

    [Description("Talents to forbid")]
    public List<DBPtr<Ability>> talents = new List<DBPtr<Ability>>();

    [Description( "Consumables to forbid" )]
    public List<DBPtr<Ability>> consumables = new List<DBPtr<Ability>>();

    [Description( "Режим работы со списком (talents only)" )]
    public EUseMode useListAs = EUseMode.ListAsRule;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EChannelingType
  {
    Streaming,
    Creation,
  }

  [DBVersion(1)]
  [TypeId(0x9E67B280)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChannelling", "PFApplChannelling.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChannellingApplicator : BuffApplicator
  {
    [Description("Targets selector")]
    public DBPtr<TargetSelector> targetSelector;

    [Description("Type of channeling. In case of Creation don't forget to setup DontTakeMana flag for Ability")]
    public EChannelingType channelingType = EChannelingType.Streaming;

    [Description("List of applicators that will be applied to caster of channelling")]
    public List<DBPtr<BaseApplicator>> applicatorsOnSelf = new List<DBPtr<BaseApplicator>>();

    [Description("Spell that will be cast on the targets of applicator at start")]
    public DBPtr<Spell> startSpell;

    [Description("Spell that will be cast on the targets of applicator every 'period' of time")]
    public DBPtr<Spell> periodicalSpell;

    [Description("Spell that will be cast on the targets of applicator at stop")]
    public DBPtr<Spell> stopSpell;

    [Description("Spell that will be cast on the targets of applicator on cancel")]
    public DBPtr<Spell> cancelSpell;

    [Description("Period of time (in sec)")]
    public float period = 0.0f;

    [Description("Flags that specify channelling interruption events")]
    public EBaseUnitEventFlags interruptEvents = EBaseUnitEventFlags.Zero;

    [Description("When 'true' channelling will be cancelled when interrupted and cancelSpell will be applied instead of stopSpell")]
    public bool cancelOnInterrupt = false;

    [Description("On interrupt all start spell effects will be removed")]
    public bool removeStartSpellEffectOnInterrupt = false;

    [Description("When channelling is interrupted it's scale will be calculated using this formula")]
    public ExecutableFloatString scaleWhenInterrupted = new ExecutableFloatString("1.0f");

    [Description( "Should cancelSpell will be applied on disable instead of stopSpell?" )]
    public bool cancelOnDisable = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B07)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplOnDamage", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class OnDamageApplicator : BuffApplicator
  {
    [Description("Flags that allow control over type of damage that produces spell")]
    public EDamageFilter filterFlags = EDamageFilter.All;

    [FieldCategory("OnDamage")]
    [Description("A spell that will be cast on sender of incoming damage")]
    public DBPtr<Spell> spell;

    [FieldCategory("OnDamage")]
    [Description("A spell that will be cast on sender of incoming damage")]
    public EApplicatorApplyTarget spellTarget;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(4)]
  [TypeId(0x9E677A81)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplCreepBehaviourChange", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class CreepBehaviourChangeApplicator : BuffApplicator
  {
    [Description("Flags")]
    public EBehaviourChangeFlags behaviourChangeFlags = EBehaviourChangeFlags.ChangeFaction;

    [Description("List of applicators that will be applied to changed unit")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();

    [Description("Имя группы суммонов к которой приписать")]
    public string summonGroupName;

    [Description( "Summoned unit behaviour" )]
    public DBPtr<SummonBehaviourBase> behaviour;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B09)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplTaunt", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class TauntApplicator : BuffApplicator
  {
    [Description("Target to taunt on")]
    public EApplicatorApplyTarget tauntTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Receiver's target can't be changed by autotargeting")]
    public bool strongTarget = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E79AD18)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplRefreshCooldown", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class RefreshCooldownApplicator : BaseApplicator
  {
    [Description("Задает способности героя, которым следует сбросить кулдаун")]
    public EAbilityIdFlags flags = EAbilityIdFlags.All;

    [Description("Нужно ли сбрасывать кулдаун у данной способности")]
    public bool refreshThis = false;

    [Description("На сколько сбросить кулдаун, в секундах (если <= 0, то полностью). Процент (точнее сотые), если стоит флаг reductByPercent")]
    public ExecutableFloatString reductionAmount = new ExecutableFloatString("-1.0f");

    [Description("Список улучшаемых талантов")]
    public List<DBPtr<Ability>> talents = new List<DBPtr<Ability>>();

    [Description("Режим работы со списком")]
    public EUseMode useListAs = EUseMode.ListAsRule;

    [Description("Разрешить увеличивать кулдаун (указывая отрицательный reductionAmount)")]
    public bool allowCdIncrease = false;

    [Description("Сбросить кулдаун на процент вместо секунд")]
    public bool reduceByPercent = false;
  }
   

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // http://SITE - No more XP
  //[TypeId(0xF721440)]
  //[UseTypeName("APLR")]
  //[FactoryImpl("Create", "NWorld::PFApplAddExp", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  //public class AddExpApplicator : BaseApplicator
  //{
  //  [Description("Experience to be added to the target hero (must be more then 0)")]
  //  [FloatMin(0.0f)]
  //  public ExecutableFloatString experience = new ExecutableFloatString("1.0f");
  //}
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B0A)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDamageReflect", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DamageReflectApplicator : BuffApplicator
  {
    [FieldCategory("Damage reflection")]
    public float amountInPersent = 0.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B0B)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplKickAway", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class KickAwayApplicator : BaseApplicator
  {
    [FieldCategory("KickAway")]
    public float distance = 10.0f;
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[TypeId(0x1E726440)]
	[UseTypeName("APLR")]
	[FactoryImpl("Create", "NWorld::PFApplShift", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
	public class ShiftApplicator : BaseApplicator
	{
    [Description("Target to shift to")]
    public EApplicatorApplyTarget shiftTarget = EApplicatorApplyTarget.ApplicatorTarget;

		[Description("Targets selector")]
		public DBPtr<SingleTargetSelector> targetSelector;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EThrowType
  {
      Throw,
      Jump,
      Flip,
  };

  [DBVersion(5)]
  [TypeId(0x1E729C40)]
	[UseTypeName("APLR")]
	[FactoryImpl("Create", "NWorld::PFApplThrow", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
	public class ThrowApplicator : BaseApplicator
  {
    [Description("Разновидность полёта")]
    public EThrowType flightType = EThrowType.Throw;

    [Description("Объекты, через которые мы можем перепрыгивать")]
    public EGhostMoveMode collisionFlags = EGhostMoveMode.IgnoreDynamic;

    [Description("Выбор цели полёта")]
		public DBPtr<SingleTargetSelector> targetSelector;

	  [Description("Режим самонаведения на движущийся юнит-цель")]
	  public bool trackTargetUnit = false;

    [Description("Spell выполняемый до начала работы аппликатора")]
    public DBPtr<Spell> startSpell;

    [Description("Spell выполняемый после окончания работы аппликатора")]
    public DBPtr<Spell> stopSpell;

	  [Description("Горизонтальная скорость полёта юнита (м/с)")]
	  public ExecutableFloatString moveSpeed = new ExecutableFloatString("1.0");

    [Description("Время полёта юнита в случае Flip")]
    public ExecutableFloatString flipTime = new ExecutableFloatString("1.0");

    [Description( "Максимальная высота полёта юнита" )]
    public float maxHeight = 0.0f;

    [Description( "Растояние на котором высота равняется maxHeight" )]
    public float maxDistance = 0.0f;

    [Description( "Форма траектории полёта юнита (нормируется по maxHeight)" )]
    public AnimatedFloat trajectory = new AnimatedFloat( 1.0f );

    [Description( "Угол наклона на траектории полета (0 - для вычисления по касательной к траектории)" )]
    public AnimatedFloat angle = new AnimatedFloat( 0.0f );

    [Description("Время, через которое юнит начнёт перемещение после начала спела (случай Jump)")]
    public float takeOffTime = 0.0f;

    [Description("Время до приземления, когда пора проигрывать финальную анимацию (случай Jump)")]
    public float landTime = 0.0f;

    [Description("Согласовывать ли Surface Speed анимации с АГ (случай Jump)")]
    public bool surfaceSpeedFromAG = true;

    [Description("Эффект полёта юнита (зацикленная нода) (случай Jump)")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<EffectBase>> flyEffect = new List<DBPtr<EffectBase>>();

    [Description("StopOnDisable - buff will be dropped when become disabled (in normal state it could be enabled again)")]
    public EBuffBehavior behaviorFlags = EBuffBehavior.Zero;

    [Description("Запрещать ли поворот SceneObject'а получателя на время действия аппликатора")]
    public bool lockRotation = false;

    [Description("Выбор цели для экстренной остановки")]
    public DBPtr<SingleTargetSelector> firstTargetToHit;
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[TypeId( 0x2B789AC0 )]
	[UseTypeName( "APLR" )]
	[FactoryImpl( "Create", "NWorld::PFApplFly", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class FlyApplicator : BuffApplicator
	{
		[Description( "Высота полёта" )]
		public float flightHeight = 3.0f;

    [Description("Время взлёта")]
    public float startTime = 1.0f;

    [Description("Время приземления")]
    public float stopTime = 1.0f;

    [Description("Длительность анимации приземления")]
    public float animatedStopTime = 1.0f;

    [Description("Объекты, через которые мы можем перелетать")]
		public EGhostMoveMode collisionFlags = EGhostMoveMode.IgnoreDynamic | EGhostMoveMode.IgnoreBuildings | EGhostMoveMode.IgnoreStatic;

    [Description("Расталкивать ли юнитов при приземлении")]
    public bool push = false;

    [Description("Spell выполняемый до начала работы аппликатора")]
    public DBPtr<Spell> startSpell;

    [Description("Spell выполняемый после окончания работы аппликатора")]
    public DBPtr<Spell> stopSpell;

    [Description("Замены анимаций")]
    public List<AnimStateChanger> replaceAnimations;

    [Description("Радиус, в рамках которого будет исправляться позиция приземления после полёта")]
    public float radiusFixObstacle = 30.0f;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[TypeId( 0xF61F480 )]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAttract", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AttractApplicator : BaseApplicator
  {
    [FieldCategory("Attract")]
    public float distance = 10.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B0C)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDealedDamageConverter", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DealedDamageConverterApplicator : BaseApplicator
  {
    [FieldCategory("DealedDamageConverter")]

    [Description("Dealed damage will be multiplied on this value")]
    public float scale = 1.0f;

    [Description("Applicators that dealed damage will be gathered within this time frame")]
    public float deltaTime = 3.0f;

    [Description("Type of healing: life or energy")]
    public EHealTarget type = EHealTarget.Health;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E5C0B0D)]
  [DBVersion(2)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChainLightning", "PFApplChainLightning.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChainLightningApplicator : BaseApplicator
  {    
    [FieldCategory("ChainLightning")]
    public ExecutableIntString numJumps = new ExecutableIntString("1");
    public DBPtr<Spell> spell;
    public float onJumpSpellScale = 1.0f;
    public float betweenJumpsTimeInterval = 0.0f;
    public ExecutableFloatString range = new ExecutableFloatString("0.0");

    [Description("Flags that specify targets of this spell.")]
    public ESpellTarget targetFilter = ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly;

    [Description("Индекс эффекта из списка")]
    public ExecutableIntString effectIndex = new ExecutableIntString( "0" );

    [Description("Списов эффектов (LightningEffect или EffectList с молниями)")]
    public List<DBPtr<EffectBase>> effects = new List<DBPtr<EffectBase>>();

    [Description("Перескакивать на новую цель, если текущая уклонилась")]
    public ExecutableBoolString jumpOnEvade = new ExecutableBoolString( "true" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [IndexField("applicator")]
  public class ApplicatorToExecute
  {
    public DBPtr<BaseApplicator> applicator;
    [Description("Через сколько секунд переключимся на следующий аппликатор в списке. -1 — механизм не задействован")]
    public ExecutableFloatString delay = new ExecutableFloatString("-1.0");
    [Description("Дополнительное условие переключения на следующий аппликатор в списке")]
    public ExecutableBoolString continueCondition = new ExecutableBoolString("false");
    [Description("Дополнительное условие останова программы")]
    public ExecutableBoolString stopCondition = new ExecutableBoolString("false");
    public EParentNotificationFlags continueEvents = EParentNotificationFlags.Stop;
    public EParentNotificationFlags stopEvents     = EParentNotificationFlags.Zero;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E676A80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplProgram", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ProgramApplicator : BuffApplicator
  {
    [Description("Applicators to be applied sequentially (one after another)")]
    public List<ApplicatorToExecute> applicators = new List<ApplicatorToExecute>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB76BC40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplForAllTargets", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ForAllTargetsApplicator : BuffApplicator
  {
    [Description("Таргет селектор, для выбора целей")]
    public DBPtr<MultipleTargetSelector> targets;

    [Description("Программа, которая применяется к каждой цели")]
    public DBPtr<ProgramApplicator> program;

    [Description("Когда наложить программу на следующую цель")]
    public EParentNotificationFlags continueEvents;

    [Description("Когда прервать аппликатор")]
    public EParentNotificationFlags stopEvents;

    [Description( "Если во время действия апликатора над многими целями следующая цель стала не валидной, то пропустить ее" )]
    public bool skipTargetIfInvalid = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C67DB40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplMovementControl", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class MovementControlApplicator : BuffApplicator
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum EStatusFlags
  {
    None                 = 0,
    UpdateLifetime       = 1 << 0,
    IsDebuff             = 1 << 1,
    StopSameConflicted   = 1 << 2,
    AlwaysMerge          = 1 << 3,
    ShowSingle           = 1 << 4,
    StopAllConflicted    = 1 << 5,
    IsBuff               = 1 << 6,
  }

  public enum EStackingRule
  {
    Unstackable,
    PartiallyStackable,
    FullyStackable,
  }

  [DBVersion(2)]
  [TypeId(0x9E688BC0)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplStatus", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class StatusApplicator : BuffApplicator
  {
    [Description("Name of status")]
    public TextRef name = new TextRef();

    [Description("Description of status")]
    public TextRef description = new TextRef();

    [Description("UI texture that will be shown in status bar")]
    public DBPtr<Render.DBRenderResources.Texture> image; 

    [Description("Count of stacking of status with the same one")]
    public int stackCount = 0;

    [Description("How status stacks with the same status from other unit")]
    public EStackingRule stackableAcrossUnits = EStackingRule.Unstackable;

    [Description("When nonstackable statuses collide, status with highest power survives")]
    public int power = 0;

    [Description("The higher dispell priority is, the earlier effect will be dispelled")]
    public EDispellPriority dispellPriority = EDispellPriority.Medium;

    [Description("Поведение статус-аппликатора. Остановиться по времени, остановиться, когда ребенок остановиться, остановиться после остановки всех детей.")]
    public EStopBehaviour stopBehaviour = EStopBehaviour.StopByTime;

    [Description("List of applicators that will be applied to changed unit")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();

    [Description("List of unstackable applicators")]
    public DBPtr<ApplicatorsList> unstackableWith;

    [Description("Custom stack counter")]
    public ExecutableIntString customCounter = new ExecutableIntString("0");

    [Description("Custom progress")]
    public ExecutableFloatString customProgress = new ExecutableFloatString( "-1.0" );

    [Description("UI status icon position")]
    public int statusPosition = 0;

    public EStatusFlags flags = EStatusFlags.None;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C68AC00)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChangeAnimSet", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChangeAnimSetApplicator : BuffApplicator
  {
    public DBPtr<AnimSet> animSet;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C68AC01)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChangeAnimation", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChangeAnimationApplicator : BuffApplicator
  {
    public EAnimStates animState;
    public string animation = "";
    public string marker = "";
    public bool upper = false;
    public bool affectAllSets = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // http://SITE - No more XP
  //[TypeId(0x2C6C4C81)]
  //[UseTypeName("APLR")]
  //[FactoryImpl("Create", "NWorld::PFLevelUpApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  //public class LevelUpApplicator : BaseApplicator
  //{
  //  public bool keepLevelProgress = true;
  //}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C6C83C2)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFUIMessageApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class UIMessageApplicator : BaseApplicator
  {
    [Description("Сообщение со значением. Включать значение value так: <value=value>.")]
    public TextRef message = new TextRef();

    [Description("Значение")]
    public ExecutableFloatString value = new ExecutableFloatString( "-1.0" );

    [Description("UI событие")]
    public DBPtr<UIEvent> uiEvent;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C6C8442)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFResurrectApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ResurrectApplicator : BaseApplicator
  {
    [FloatMinMax(0, 100)]
    public float healthPercent = 100;

    [FloatMinMax(0, 100)]
    public float energyPercent = 100;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Flags]
  public enum ECloneFlags
  {
    None              = 0,
    GhostMove         = 1 << 0,
    DoLevelUp         = 1 << 1,
    MirrorOwnerSpells = 1 << 2,
    UseAbilityAI      = 1 << 3,
    PlaySummonEffect  = 1 << 4,
    MakeSlave         = 1 << 5,
    CopyStats         = 1 << 6,
    DummyBehaviour    = 1 << 7,
    InitTalents       = 1 << 8,
  };

  [DBVersion(0)]
  [TypeId(0x9E724380)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplCloneHero", "PFApplSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class CloneHeroApplicator : BaseApplicator
  {
    [Description("Список аппликаторов, который ляжет на копию")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();

    [Description("Life time of buff (in seconds); specify -1 as infinity")]
    public ExecutableFloatString lifeTime = new ExecutableFloatString("-1.0");

    [Description("Максимальное расстояние, на котором клон следует за хозяином; <= 0 - не переопределять")]
    public ExecutableFloatString followRange = new ExecutableFloatString("-1.0");

    [Description("Дополнительнае настройки")]
    public ECloneFlags flags = ECloneFlags.DoLevelUp | ECloneFlags.GhostMove | ECloneFlags.PlaySummonEffect;

    [Description("(вариант MakeSlave) Целеуказание клона")]
    public DBPtr<UnitTargetingParameters> targetingParams;

    [Description("(вариант MakeSlave) Максимум склонированных героев; -1 - предел не меняется")]
    public ExecutableIntString maxCount = new ExecutableIntString("1");

    [Description( "Имя группы суммонов к которой приписать" )]
    public string summonGroupName;

    [Description("Life and energy at spawn time")]
    public SpawnStats spawnStats = new SpawnStats();

    [Description("Additional damage's multiplier")]
    public ExecutableFloatString takeModDmg = new ExecutableFloatString("1.0f");

    [Description("Flags to specify targets of the takeModDmg")]
    public ESpellTarget takeTypeUnit = ESpellTarget.All | ESpellTarget.VulnerableTargetsOnly;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB724A40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplInvisibility", "PfApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class InvisibilityApplicator : BuffApplicator
  {
    [Description("Время ухода в невидимость")]
      public ExecutableFloatString fadeIn = new ExecutableFloatString("0.0");

    [Description("Заклинание, которое будет закастовано в момент, когда юнит становится невидимым.")]
    public DBPtr<Spell> onBecomeInvisible;

    [Description("Игнорировать событие отмены невидимости")]
    public bool ignoreCancel = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [NonTerminal]
  [FactoryBase("Create", "NWorld::PFEventProcessorBase", "NWorld::PFWorld* world")]
  [IndexField("caption")]
  public class EventProcessorBase : DBResource
  {
    public EApplicatorApplyTarget applyTarget = EApplicatorApplyTarget.ApplicatorTarget;
    public DBPtr<Spell> spell;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF722380)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFTriggerApplicator", "PFTriggerApplicator.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class TriggerApplicator : BuffApplicator
  {
    public ExecutableIntString actionsCount = new ExecutableIntString("0");

    public DBPtr<EventProcessorBase> processor;

    public bool useAbilityCooldown = false;
    public bool useAbilityOwnerMana = false;

    [Description("Проигрывать указанный в таланте аск героя при срабатывании.")]
    public bool playAck = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2B82CC00)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFAbsorbShieldApplicator", "PFTriggerApplicator.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AbsorbShieldApplicator : BuffApplicator
  {
    public ExecutableFloatString damageToAbsorb = new ExecutableFloatString("0.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF739C40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplTargetsCounter", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class TargetsCounterApplicator : BuffApplicator
  {
    public DBPtr<TargetSelector> targetSelector;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF73BB40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplEye", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class EyeApplicator : BuffApplicator
  {
    public ExecutableFloatString visRange = new ExecutableFloatString("1.0f");

    [Description("Какой фракции открыть туман")]
    public EFactionFlags flags = EFactionFlags.Self;

    [Description("Target to open warfog at")]
    public EApplicatorApplyTarget eyeTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Cancel hiding beyond obstacles")]
    public bool cancelObstacles = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF73BB40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplValue", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ValueApplicator : BuffApplicator
  {
    public ExecutableFloatString value = new ExecutableFloatString("0.0f");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xA0757340)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplLockTiles", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class LockTilesApplicator : BuffApplicator
  {
    [Description("Mask to lock tile map")]
    public ObjectLockMask lockMask;

    [Description("Relative 2D object bounds to lock map")]
    public FloatRect collision;

    [Description("Push applicator sender out of locked tiles")]
    public bool pushCaster = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE7764C40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFAddNaftaApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class AddNaftaApplicator : BaseApplicator
  {
    [Description("Nafta to be added to the target unit (negative to remove)")]
    public ExecutableFloatString nafta = new ExecutableFloatString("1.0f");

		[Description("Designates whether the source is impulse buff or not")]
		public bool isFromImpulseBuff = false;
	}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE7777B80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplMount", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class MountApplicator : BuffApplicator
  {
    [Description("Target to mount to")]
    public EApplicatorApplyTarget mountTarget = EApplicatorApplyTarget.ApplicatorTarget;

    [Description("Hero can issue commands to his mount")]
    public bool controlMount = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(0)]
  [IndexField("applicator")]
  public class ApplicatorToProxy
  {
      [Description("Applicator to execute")]
      public DBPtr<BaseApplicator> applicator;

      [Description("Names of variables which values should be retrieved and stored")]
      public List<string> variableNames;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE778BC80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplVariableProxy", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class VariableProxyApplicator : BaseApplicator
  {
      [Description("List of applicators to execute and retrieve variable value from")]
      public List<ApplicatorToProxy> applicators = new List<ApplicatorToProxy>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE778BC81)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplMarker", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class MarkerApplicator : BuffApplicator
  {
    [Description("Прибавка к текущему значению")]
    public ExecutableFloatString addValue = new ExecutableFloatString("1.0");
    [Description("Множитель текущего значения")]
    public ExecutableFloatString multValue = new ExecutableFloatString("1.0");
  }

  [Flags]
  public enum EBounceFlags
  {
    BounceNextTargetOnLoss = 1 << 0,
    RenewTargetOnStart     = 1 << 1,
    StartFromOwner         = 1 << 2,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE7792380)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplBounce", "PFApplBounce.h", CreateFunction = "NWorld::CreateApplicator<>")]
  [DBVersion(0)]
  public class BounceApplicator : BuffApplicator
  {
      [Description("Target to select for next bounce")]
      public DBPtr<SingleTargetSelector> target;

      [Description("Spell to send")]
      public DBPtr<Spell> spell;

      [Description("Number of targets to bounce between. Less or equal 0 means no limits")]
      public ExecutableIntString targetsNumber = new ExecutableIntString("1");

      [Description("Delay before next bounce")]
      public ExecutableFloatString bounceDelay = new ExecutableFloatString("0.0");

      [Description("Target from which bouncing starts")]
      public EApplicatorApplyTarget startTarget = EApplicatorApplyTarget.ApplicatorTarget;

      [Description("Flags specific for Bounce applicator")]
      public EBounceFlags flags = 0;

      [EnumArray( typeof( ETeamID ) )]
      public List<DBPtr<EffectBase>> cancelEffect = new List<DBPtr<EffectBase>>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE77AF500)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplCreateGlyph", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class CreateGlyphApplicator : BaseApplicator
  {
      [Description("Glyph to create")]
      public DBPtr<Glyph> glyph;

      [Description( "Distance from parent's position" )]
      public float distance = -1.0f;

      [Description( "Angle from parent's direction or from [1,0] direction on map (ccw,deg)" )]
      public float angle = -1.0f;

      [Description( "Radius for free place searching" )]
      public float radius = -1.0f;

      [Description( "Angle is relative to the parent's direction" )]
      public bool angleIsRelative = false;

      [Description("Absolute position instead distance, angle and radius parameters")]
      public Vec2 absolutePosition = new Vec2(0.0f, 0.0f);

      [Description("Script name to assign")]
      public string scriptName = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE77B4C80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplVictory", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class VictoryApplicator : BaseApplicator
  {
    [Description( "Destroy losers' main building" )]
    public bool destroyMainBuilding = false;

    [Description("Wins a faction opposite to the applicator sender's faction")]
    public bool oppositeFaction = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x22CC6D80)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplChangeHeroState", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class ChangeHeroStateApplicator : BuffApplicator
  {
      // Nothing here for now. It just changes hero state to second state, when enabled.
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2B7B8C40)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSceneObjectChange", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SceneObjectChangeApplicator : BuffApplicator
  {
    [Description("List of scene objects")]
    public List<DBPtr<DBSceneObject>> sceneObjects = new List<DBPtr<DBSceneObject>>();
    
    [Description("Index to select scene object from the list")]
    public ExecutableIntString sceneObjectIndex = new ExecutableIntString("0");
  }

  [Flags]
  public enum EDelegateDamageFlags
  {
    AllowDrains = 1,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE7873440)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDelegateDamage", "PFApplDelegateDamage.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DelegateDamageApplicator : BuffApplicator
  {
    [Description("Damage to delegate; use 'appl.vDamage' to access incoming damage")]
    public ExecutableFloatString damageToDelegate = new ExecutableFloatString("0.0f");

    [Description("Damage to apply on receiver; use 'appl.vDamage' to access incoming damage")]
    public ExecutableFloatString damageToApply = new ExecutableFloatString("0.0f");

    [Description("Total damage that can be delegated")]
    public ExecutableFloatString totalDamage = new ExecutableFloatString("0.0f");

    public EDelegateDamageFlags flags = 0;

    [Description("Total damage is infinite (ignores totalDamage formula)")]
    public bool infiniteTotalDamage = false;

    [Description("Delegated damage ignores defence")]
    public bool ignoreDefences = false;

    [Description("Delegated damage won't trigger aggro whether DontAttackBack flag is set for original damage or not")]
    public bool forceDontAttackBack = false;

    [Description("Targets to delegate damage to")]
    public DBPtr<TargetSelector> delegateTargets;

    [Description("Condition to stop after damage processing")]
    public ExecutableBoolString stopCondition = new ExecutableBoolString( "false" );
  }

  [TypeId( 0xE7958BC0 )]
  [UseTypeName( "APLR" )]
  [FactoryImpl( "Create", "NWorld::PFApplChangeState", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class ChangeStateApplicator : BaseApplicator
  {
    public string newStateName = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x9A9CA341 )]
  [UseTypeName( "APLR" )]
  [FactoryImpl( "Create", "NWorld::PFApplScaleControl", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class ScaleControlApplicator : BuffApplicator
  {
    [Description( "Желаемый масштаб цели. Текущий масштаб будет подтягиваться к желаемому" )]
    public ExecutableFloatString desiredScale = new ExecutableFloatString( "1.0f" );

    [Description( "Скорость изменения масштаба, % в секунду" )]
    public ExecutableFloatString changeSpeed = new ExecutableFloatString( "10.0f" );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xE79B9C00)]
  [UseTypeName( "APLR" )]
  [FactoryImpl( "Create", "NWorld::PFApplGiveConsumable", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class GiveConsumable : BaseApplicator
  {
    public DBPtr<Consumable> consumable;
    public ExecutableIntString amount = new ExecutableIntString("1");
  }

  [TypeId(0xE7A4F3C0)]
  [UseTypeName( "APLR" )]
  [FactoryImpl( "Create", "NWorld::PFApplPickupChanneling", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class PickupChannelingApplicator : ChannellingApplicator
  {
  }

  [Flags]
  public enum EFXFlags
  {
    ApplyFXToAux = 1,
  }

  [TypeId(0xE7A6C480)]
  [UseTypeName( "APLR" )]
  [FactoryImpl( "Create", "NWorld::PFApplFX", "PFApplFx.h", CreateFunction = "NWorld::CreateApplicator<>" )]
  public class FXApplicator : BuffApplicator
  {
    [Description("Дополнительная цель для эффекта. Например начало молнии.")]
    public DBPtr<SingleTargetSelector> auxillaryTarget;

    public EFXFlags flags = 0;
  }

  [TypeId(0x15C7A800)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplInvalidAbilityTarget", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class InvalidAbilityTargetApplicator : BuffApplicator
  {
  }

  [TypeId(0x15CBF300)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplDayNightTransition", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class DayNightTransitionApplicator : BaseApplicator
  {
    public EDayNightState desiredState = EDayNightState.Night;
    [FloatMinMax(0.0f, 1.0f)]
    public float desiredStateFraction = 0.0f;
  }

  [TypeId(0x15CBF400)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSetTimescale", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SetTimescaleApplicator : BaseApplicator
  {
      //[FloatMinMax(0.5f, 1.5f)]
      public float desiredTimescale = 1.0f;
  }
}
