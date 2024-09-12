using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using Terrain.DBTerrain;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_GameLogic.DBStats
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ETerrainType
  {
    Plains,
    Swamp,
    Desert,
    Rock,
    Water,
    Road,
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "TRTI" )]
  public class PFTerrainTypeInfo : TerrainTypeInfo
  {
    public ETerrainType eType;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum EPlayerID
	{
		None,
		Player_1,
		Player_2,
		Player_3,
		Player_4,
		Player_5,
		Player_6,
		Player_7,
		Player_8,
    Player_9,
    Player_10,
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Custom("DBServer")]
	public enum EFaction
	{
		Neutral,
		Freeze, 
		Burn,
	}

  [Flags]
  public enum EFactionFlags
  {
    FactionFreeze = 1,
    FactionBurn   = (1 << 1),
    Neutral       = (1 << 2),
    Self          = (1 << 3),
    Opposite      = (1 << 4),
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ERoute
  {
    Top,
    Center,
    Bottom,
    Tree,
    Unassigned,
  }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum EStatOwner
	{
		None,
		Creature,
		EnemyCreature,
		EnemyHero,
		Hero,
		Player,
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Custom( "DBServer", "Social" )]
  public enum EStat
	{
    // New stats from design
    Life,             // old Health
    Energy,           // old Mana
    Range,            // old AttackRange
    MoveSpeed,
    AttackSpeed,
    CriticalChance,
    CriticalMultiplier,
    LifeDrain,
    EnergyDrain,
    Evasion,
    LifeRegeneration, // old HealthRegenSpeed
    LifeRegenerationAbsolute,
    EnergyRegeneration, // old ManaRegenSpeed
    EnergyRegenerationAbsolute,
    VisibilityRange,
   
    //new stats
    Strength,
    Intellect,
    Dexterity,
    BaseAttack,
    Stamina,
    Will,
    VirtualStat,
    CritChanceBonus,
    EnergyDamageDecrease,
    MaterialDamageDecrease,
    MissChance,
    Level,

    NaftaForKill,
    NaftaForAssist,
    NaftaSpecForKill,
    TeamNaftaForKill,
    TeamNaftaForPresence,
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [Custom( "Social" )]
  public enum  EDerivativeStat
  {
    LifeRegenTotal,
    EnergyRegenTotal,
    DamageMin,
    DamageMax,
    DexterityDamageMult,
    MoveSpeedMpS,
    CritChance,
    AttacksPerSecond,
    BodyDefence,
    SpiritDefence,
    PenetrationFromAttackSpeed,
    PenetrationFromDexterity,
    PenetrationTotal
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class StatUpgrade
  {
    public int level = 0;
    public float increment = 0.0f;
  }

  public class StatEnhancer
  {
    public EStat statId = EStat.Life;
    public float statAddModifier = 0.0f;
    public float statMullModifier = 1.0f;
    public float incrementAddModifier = 0.0f;
    public float incrementMullModifier = 1.0f;
  }

  public class StatsEnhancersContainer : DBResource
  {
    public List<StatEnhancer> statsEnhancers = new List<StatEnhancer>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(1)]
  [IndexField("statId")]
  [Custom( "Social" )]
  public class UnitStat
  {
    [Description("Stat base value")]
    public ExecutableFloatString value = new ExecutableFloatString("0.0f");

    [Description("Stat increment per level")]
    public ExecutableFloatString increment = new ExecutableFloatString("0.0f");

    [Description("Stat Id")]
    public EStat statId = EStat.Life;

    [Description("Special way to specify non-linear increment. Field increment ignored when this field is used")]
    public List<StatUpgrade> levelUpgrades = new List<StatUpgrade>();

    [NoCode, Browsable( false )]
    public float calcValue;
    [NoCode, Browsable( false )]
    public float calcIncrement;
  }
    
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF626440)]
  [UseTypeName("STCN")]
  [Custom( "Social" )]
  public class StatsContainer : DBResource
  {
    public List<UnitStat> stats = new List<UnitStat>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "DSTCN" )]
  [Custom( "Social" )]
  public class DerivativeStatsContainer : DBResource
  {
    [EnumArray( typeof( EDerivativeStat ) )]
    public List<ExecutableFloatString> derivativeStats = new List<ExecutableFloatString>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [IndexField( "stat" )]
  [Custom("Social")]
  public class StatBudget
  {
    public EStat stat = EStat.Life;
    public float budget = 0;
    [Description("Растёт ли стат от мощи")]
    public bool upgradesWithForce = false;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "STBUD" )]
  [Custom("Social")]
  public class StatsBudgetContainer : DBResource
  {
    public List<StatBudget> stats = new List<StatBudget>();
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
