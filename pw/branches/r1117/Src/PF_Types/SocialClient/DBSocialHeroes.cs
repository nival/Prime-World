//#include "DBSocialResources.cs"

using System;
using System.Collections.Generic;
using libdb.DB;
using System.ComponentModel;
using Render.DBRenderResources;
using PF_GameLogic.DBTalent;


namespace PF_Types.SocialClient
{
  [Custom("Social", "DBServer")]
  [Flags]
  [NoCode]
  public enum HeroClassEnum
  {
    None = 0x0,
    Protector = 0x1,
    Vanguard = 0x2,
    Executioner = 0x4,
    Fighter = 0x8,
    Support = 0x10
  }

  [Custom( "Social" )]
  [NoCode]
  public class EnduranceRegenTime
  {
    [Description( "Уровень героя ( начинается с 0 )" )]
    public int level = 0;
    [Description( "Скорость в секундах восстановления до MaxEndurance" )]
    public int enduranceRegenTime = 86400;
  }


  [Custom("Social")]
  [NoCode]
  public class HeroStatsTable : DBResource
  {
    [Description( "Максимальное кол-во бодрости" )]
    public int MaxEndurance = 100;

    [Description( "Табличка соответствия скорости восстановления бодрости и левела героя" )]
    public List<EnduranceRegenTime> EnduranceRegen;
  }

  [Custom("Social")]
  [NoCode]
  public class HeroClassStatBonus
  {
    public List<HeroClassStatPair> Bonuses;
  }

  [Custom("Social")]
  [NoCode]
  public class HeroClassStatPair
  {
    public HeroClassEnum Class;
    public int Bonus;
  }
  [NoCode]
  [Custom("Social")]
  public class HeroFameIncrement : DBResource
  {
    public List<int> FameIncrement;
  }

  [NoCode]
  [Custom( "Social" )]
  public class BonusTalents
  {
    [Description( "Таланты за этот уровень героя" )]
    public List<DBPtr<Talent>> Talents;
  }

  [NoCode]
  [Custom( "Social" )]
  public class BonusTalentsForLevel : DBResource
  {
    [Description( "Уровни героя" )]
    public List<BonusTalents> Levels;
  }

  [Custom("Social")]
  [NoCode]
  public enum EBarColor
  {
      None = 0,
      Red,
      Green,
      Yellow,
      Blue ,
  }
  [NoCode]
  [Custom("Social")]
  public class CharacterBar
  {
      [Description("Цвет")]
      public EBarColor BarColor = EBarColor.None;
      [Description("Количество кадров")]
      public int Count = 0;
  }  
  [NoCode]
  [Custom("Social")]
  public class CharacterBarSettings
  {
      [Description("Атака")]
      public CharacterBar Attak;
      [Description("Защита")]
      public CharacterBar Defence;
      [Description("Таланты")]
      public CharacterBar Talents;
      [Description("Сложность")]
      public CharacterBar Complexity;

  }

  [NoCode]
  [Custom("Social")]
  public class LobbyHeroData
  {
    [Description( "Path to sound, played on hero click in Doct castle. Relative path from Resources/Sound/, without file extension." )]
    public string heroAskSoundA;

    [Description( "Path to sound, played on hero click in Adornian castle. Relative path from Resources/Sound/, without file extension." )]
    public string heroAskSoundB;

    [Description("Hero UI render for first faction")]
    public DBPtr<Texture> heroRenderA;
    [Description("Hero UI description for first faction")]
    public TextRef heroDescriptionA = new TextRef();
    [Description( "Hero UI biography for first faction" )]
    public TextRef heroBiographyA = new TextRef();

    [Description("Hero UI render for second faction")]
    public DBPtr<Texture> heroRenderB;
    [Description("Hero UI description for second faction")]
    public TextRef heroDescriptionB = new TextRef();
    [Description( "Hero UI biography for second faction" )]
    public TextRef heroBiographyB = new TextRef();

    [Description("Is hero availabe by default. Using for male players.")]
    public bool IsHeroHiredByDefaultMale = false;
    [Description("Is hero availabe by default. Using for female players.")]
    public bool IsHeroHiredByDefaultFemale = false;
    
    [Description("Hero stats for Social client.")]
    public DBPtr<HeroStatsTable> Stats;
    
    [Description("Hero classes")]
    public HeroClassEnum Classes;
    [Description("Hero employment cost. Using for male players.")]
    public ResourcesTable CostMale;
    [Description("Hero employment cost. Using for female players.")]
    public ResourcesTable CostFemale;
    [Description("Production cycle resources delta")]
    public ResourcesTable ProductionResultIncrement;
    [Description("Lord's level required for hero employment. Using for female players.")]
    public int LevelRequireFemale;
    [Description("Lord's level required for hero employment. Using for male players.")]
    public int LevelRequireMale;
    [Description("Used for TalentSet versioning")]
    [Browsable(false)]
    public int Version;
    [Description("Fame increment for hero levels. First level using for employment case.")]
    public DBPtr<HeroFameIncrement> FameIncrement;
    [Description("heroId's required for current hero employment.")]
    public List<string> RequiredHeroes;

    [Description( "Список талантов, которые даются за достижение нового уровня героя" )]
    public DBPtr<BonusTalentsForLevel> BonusTalentsForLevel;

   [Description("Настройки характеристик героя (атака, защита, таланты, сложность) ")]
   public CharacterBarSettings CharacterBarSettings;


  }
}
