//#include "DbAchievements.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBStats;

namespace PF_GameLogic.DBTalent
{
  [IndexField("caption")]
  public class AchievmentCondition
  {
    public DBPtr<AchievBase> achiev;
    [IntMin(1)]
    public int minRank = 1;
  }

  [Custom( "DBServer", "Social") ]
  public enum ETalentRarity
  {
    Class,
    ordinary,
    good,
    excellent,
    magnificent,
    exclusive,
    outstanding
  }

  [Flags]
  [Custom( "DBServer" ) ]
  public enum ETalentRollGroup
  {
    PvP      = 1 << 0,
    Training = 1 << 1,
    CTE      = 1 << 2,
    PvE      = 1 << 3,
    Castle   = 1 << 4,
    MidOnly  = 1 << 5,
    All = PvP | Training | CTE | PvE | Castle | MidOnly,
  }

  [NoCode, Custom( "Social" ), IndexField( "stat" ), Browsable( false )]
  public class TalentStats
  {
    public EStat stat = EStat.Life;
    public List<float> values;
    public string addValueName = string.Empty;
  }

  [TypeId(0xF690AC0)]
  [UseTypeName("TALENT")]
  [DBVersion(1)]
  public class Talent : Ability
  {
    [FieldCategory("TURs")]
    [Description("Level of talent (TUR)")]
    [IntMin(0)]
    [Custom( "Social" )]
    public int minLevel = 0;

    [FieldCategory("TURs")]
    [Description("Development points to add on talent activate")]
    [IntMin(1)]
    [Custom( "Social" )]
    public int devPoints = 1;

    [Custom( "Social" )]
    public float budget = 0;

    [FieldCategory("TURs")]
    [Description("Conditions to determinate then talent can be activated (AND)")]
    public List<AchievmentCondition> activationConditions = new List<AchievmentCondition>();

    [FieldCategory("Logic")]
    [Description("Cost of activation")]
    [Custom("Social")]
    public int naftaCost = 0;

    [FieldCategory("Logic")]
    [Description("Prerequisite talents.")]
    [Custom( "Social" )]
    public List<DBPtr<Talent>> prerequisiteTalents = new List<DBPtr<Talent>>();

    [Description( "Conflicting(alternative) talents." )]
    [NoCode, Custom( "Social" )]
    public List<DBPtr<Talent>> conflictingTalents = new List<DBPtr<Talent>>();

    [FieldCategory("UI")]
    [Description("Rarity of talent")]
    [Custom( "DBServer", "Social" )]
    public ETalentRarity rarity = ETalentRarity.ordinary;

    [Description("Talent name to formulas")]
    [Custom( "DBServer", "Social" )]
    public string persistentId = "";


    [Description("Talent vendor cost")]
    [Custom("DBServer")]
    public int vendorCost = 0;

    [Description( "Talent roll group" )]
    [Custom( "DBServer", "Social" )]
    public ETalentRollGroup talentRollGroups = ETalentRollGroup.All;

    [Description( "Ask index to play. 0 - not set, 1 - A1, etc.." )]
    public int askId = 0;

    [Description( "Flag for indication of gender talents" )]
    [Custom( "Social" )]
    public bool isGenderTalent = false;

    [Description( "We should have this talent already bought on start?" )]
    [Custom( "Social" )]
    public bool isTakenOnStart = false;

    [Description("Is super puper talent ? 0_o")]
    [Custom("Social")]
    public bool isUltimateTalent = false;

    [Description( "Describes talent upgrade. 0 means basic talent, 1- first basic talent upgrade etc" )]
    [Custom( "Social" )]
    public int upgradeLevel = 0;

    [Description("Stores information about ConsumptionBonusConstant and ConsumptionBounsPercent needed for Consumption")]
    [Custom("Social")]
    public ConsumptionBonus consumptionBonus = new ConsumptionBonus();

    [NoCode, Custom( "Social" ), Browsable( false )]
    public List<TalentStats> talentStats;

    [Description( "Variative stats depending on current hero max base stats NUM_TASK" )]
    [NoCode, Custom( "Social" ), Browsable( false )]
    public List<TalentStats> variativeMaxTalentStats;

    [Description( "Variative stats depending on current hero min base stats NUM_TASK" )]
    [NoCode, Custom( "Social" ), Browsable( false )]
    public List<TalentStats> variativeMinTalentStats;

    [NoCode, Custom( "Social" ), Browsable( false )]
    public float forceBonus;
  }

  [Custom("Social")]
  public class ConsumptionBonus
  {
    public int constant = 0;
    public int percent = 0;
  }

  //FIXME: These values are completely UNSUED in code. The only meaningfull thing is their count!
  [Custom( "Social" )]
  public enum ETalentSlot
  {
    id0 = 0,
    id1,
    id2,
    id3,
    id4,
    id5,
  }

  [Custom( "Social" )]
  public enum ETalentLevel
  {
    id0 = 0,
    id1,
    id2,
    id3,
    id4,
    id5,
  }

  [Custom( "Social" )]
  public enum ETalentSlotStatus
  {
    normal,
    locked,
    unavailable,
  }

  [Custom( "Social" )]
  public enum ETalents
  {
    points_per_level = 4,
  }

  [DBVersion(0)]
  [Custom( "Social" )]
  public class TalentSlot
  {
    [Description("Can't use an talents in this slot, if not 'normal'!")]
    public ETalentSlotStatus status = ETalentSlotStatus.normal;

    [Description("Talent, used in this slot!")]
    public DBPtr<Talent> talent;

    [IntMinMax(1, 10)]
    public int refineRate = 1;

    [Description("Priority for bots")]
    public int aIPriority = 0;
  }

  [DBVersion(0)]
  [Custom( "Social" )]
  public class TalentsLevel
  {
    [EnumArray(typeof(ETalentSlot))]
    public List<TalentSlot> talents = new List<TalentSlot>();
  }

  [TypeId(0xF691300)]
  [UseTypeName("TALENTSET")]
  [Custom( "Social" )]
  public class TalentsSet : DBResource
  {
    [EnumArray(typeof(ETalentLevel))]
    public List<TalentsLevel> levels = new List<TalentsLevel>();
  }

  [TypeId(0xE79C6BC0)]
  [UseTypeName( "TALKIT" )]
  [Custom( "Social" )]
  [IndexField("caption")]
  public class TalentKit : DBResource
  {
    [NoCode]
    public string caption = string.Empty;

    [Custom( "Social" )]
    public TextRef name = new TextRef();

    [Custom( "Social" )]
    public DBPtr<Talent> special;

    public int kitCapacity; 

    [Custom( "Social" )]
    [Description("Список талантов в этом наборе (сете)")]
    public List<DBPtr<Talent>> talents = new List<DBPtr<Talent>>();
  }

  [TypeId( 0xE79C6BC1 )]
  [UseTypeName( "TALPACK" )]
  [IndexField( "id" )]
  [Custom( "Social" )]
  public class TalentPack : DBResource
  {
    [Description("Имя (строковой айдишник) пака, чтобы можно было спросить через формулы. Паки должны иметь уникальные id.")]
    public string id = string.Empty;
    [Custom( "Social" )]
    public TextRef name = new TextRef();
    [Custom( "Social" )]
    public string iconStyle = string.Empty;
    [Custom("Social")]
    public DBPtr<Render.DBRenderResources.Texture> icon;
    [Custom("Social")]
    public bool isRedPack = false;

    [Custom( "Social" )]
    [Description( "Список талантов в этом паке (edition-е)" )]
    public List<DBPtr<Talent>> talents = new List<DBPtr<Talent>>();
  }

}