using System;
using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBAnimations;
using PF_GameLogic.DBGameLogic;
using Foundation.DBSystem;
using Terrain.DBTerrain;

namespace PF_GameLogic.DBAbility
{

  public enum SummonType
  {
    Primary,
    Secondary,
    Pet,
    Clone
  }

  public enum SummonPlaceMode
  {
    ByApplicator,
    ByTargetSelector,
    ByBehaviour
  }

  public enum SummonSource
  {
    ByApplicator,
    TargetClone
  }

  [Flags]
  public enum ESummonFlags
  {
    None                  = 0,
    Essential             = 1 << 0,
    AlphaSummon           = 1 << 1,
    NoHealthPriority      = 1 << 2,
    CopyLevelAndStats     = 1 << 3,
    TurnByMasterDirection = 1 << 4,
    NoSummonAnimation     = 1 << 5,
    UseGlowEffect         = 1 << 6,
    NoCollision           = 1 << 7,
    LikeHero              = 1 << 8,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF730BC0)]
  [NonTerminal]
  [UseTypeName("SBEH")]
  [FactoryBase("Create", "NWorld::PFSummonBehaviourDataBase")]
  [IndexField("comment")]
  public class SummonBehaviourBase : DBResource
  {
    [NoCode]
    public string comment = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(3)]
  [TypeId(0xF730BC1)]
  [FactoryImpl("Create", "NWorld::PFSummonBehaviourDataCommon", "PFApplSummon.h")]
  public class SummonBehaviourCommon : SummonBehaviourBase
  {
    [Description("Group of summoned units to insert")]
    public SummonType summonType = SummonType.Primary;

    [Description( "Макс кол-во суммонов типа summonType" )]
    public ExecutableIntString maxCount = new ExecutableIntString("1");

    [Description( "Макс кол-во суммонов типа указанного в аппликаторе. Должно быть не больше maxCount. Если 0, то не учитывать." )]
    public ExecutableIntString maxThisCount = new ExecutableIntString( "0" );

    [Description("Override targeting params")]
    public DBPtr<UnitTargetingParameters> targetingParams;

    [FieldCategory( "Ranges" )]
    [Description( "Радиус в пределах которого саммон будет стараться находится в обычном состоянии." )]
    public ExecutableFloatString lashRange = new ExecutableFloatString( "0.0" );

    [FieldCategory( "Ranges" )]
    [Description( "Радиус за пределами которого команда move воспринимается саммоном как приказ к немедленному движению и игнорированию всех целей" )]
    public float responseRange = 0.0f;

    [Description( "Время в течении которого саммон бежит в указанную точку игнорируя цели." )]
    public float responseTime = 0.0f;
  }

  public class SummonBehaviourCommonParams
  {
    [Description("Override targeting params")]
    public DBPtr<UnitTargetingParameters> targetingParams;

    [FieldCategory("Ranges")]
    [Description("Радиус в пределах которого саммон будет стараться находится в обычном состоянии.")]
    public ExecutableFloatString lashRange = new ExecutableFloatString("0.0");

    [FieldCategory("Ranges")]
    [Description("Радиус за пределами которого команда move воспринимается саммоном как приказ к немедленному движению и игнорированию всех целей")]
    public float responseRange = 0.0f;

    [Description("Время в течении которого саммон бежит в указанную точку игнорируя цели.")]
    public float responseTime = 0.0f;
  }

  [TypeId(0x15D32040)]
  [FactoryImpl("Create", "NWorld::PFSummonBehaviourDataAdvanced", "PFAdvancedSummon.h")]
  public class SummonBehaviourAdvanced : SummonBehaviourCommon
  {
    [Description("Параметры режима охраны")]
    public SummonBehaviourCommonParams guardBehaviourParams;
    [Description("Параметры режима преследования")]
    public SummonBehaviourCommonParams chaseBehaviourParams;
  }

  [TypeId(0x15D320C1)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplAdvancedSummonSetTarget", "PFAdvancedSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SetAdvancedSummonTargetApplicator : BaseApplicator
  {
  }

  public class SpawnStats
  {
    public ExecutableFloatString life = new ExecutableFloatString("-1.0");
    public ExecutableFloatString energy = new ExecutableFloatString("-1.0");
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(5)]
  [TypeId(0xF730BC3)]
  [UseTypeName("APLR")]
  [FactoryImpl("Create", "NWorld::PFApplSummon", "PFApplSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
  public class SummonApplicator : BaseApplicator
  {
    [Description("Какого крипа призываем — из списка или клона цели")]
    public SummonSource summonSource = SummonSource.ByApplicator;

    [Description("[ByApplicator] Units array that will be created (one of them)")]
    public List<DBPtr<Summoned>> summonedUnits = new List<DBPtr<Summoned>>();
    
    [Description("[ByApplicator] Unit that will be created (index in array)")]
    public ExecutableIntString summonedUnitIndex = new ExecutableIntString("0");

    [Description("How many units will be summoned")]
    public ExecutableIntString summonedUnitsCount = new ExecutableIntString("1");

    [Description("Summoned unit behaviour")]
    public DBPtr<SummonBehaviourBase> behaviour;

    [Description("Summoned unit creation place")]
    public DBPtr<SingleTargetSelector> placeSelector;

    [Description("Summoned unit creation place source")]
    public SummonPlaceMode placeMode = SummonPlaceMode.ByBehaviour;
    
    [Description("Maximum life time of summoned unit")]
    public ExecutableFloatString lifeTime = new ExecutableFloatString("0.0f");

    [Description("List of applicators that will be applied to summoned unit")]
    public List<DBPtr<BaseApplicator>> applicators = new List<DBPtr<BaseApplicator>>();

    [Description("Флаги (Является ли суммон 'важным', является ли альфа-суммоном)")]
    public ESummonFlags flags = 0;
  
    [Description("Life and energy at spawn time")]
    public SpawnStats spawnStats = new SpawnStats();

    [Description("Additional damage's multiplier")]
    public ExecutableFloatString takeModDmg = new ExecutableFloatString("1.0f");

    [Description("Flags to specify targets of the takeModDmg")]
    public ESpellTarget takeTypeUnit = ESpellTarget.All | ESpellTarget.VulnerableTargetsOnly;

    [Description("Открывать ли варфог вокруг этого юнита")]
    public bool openWarFog = true;

    [Description("Критерий по которому сортируются существующие суммоны для ансуммона лишних (с меньшими значениями). Если не используется, то оставить 0. Здесь: sender - тот кто суммонит, receiver - суммон из перебираемых")]
    public ExecutableFloatString unsummonSortCriterion = new ExecutableFloatString("0.0f");

    [Description( "Имя группы суммонов к которой приписать" )]
    public string summonGroupName;

  }


} //namespace PF_GameLogic.DBAbility