//#include "DBHeroRanks.cs"
//#include "DBTalent.cs"
//#include "DbAchievements.cs"
//#include "DbAbility.cs"
//#include "DbUIData.cs"
//#include "DbHero.cs"
//#include "DBTalent.cs"
//#include "DBAdvMap.cs"


using System;
using System.Collections.Generic;
using libdb.DB;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBHeroRanks;
using System.ComponentModel;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBAdvMap;

namespace PF_GameLogic.DBGuild
{
  [Custom("DBServer", "Social")]
  public enum EStatBufToggle
  {
    AtGameStart = 1 << 0,
    By36Level = 1 << 1,
  }

  [Flags]
  [Custom("DBServer", "Social")]
  public enum ESessionType
  {
    UsualBattle = 1 << 0,
    GuildBattle = 1 << 1,
    All = UsualBattle | GuildBattle,
  }

  [Flags]
  [Custom("DBServer", "Social")]
  public enum EBuildingProductionCycle
  {
    First = 1 << 0,
    Second = 1 << 1,
    Third = 1 << 2,
    Fourth = 1 << 3,
    All = First | Second | Third | Fourth,
  }

  [Flags]
  [Custom("DBServer", "Social")]
  public enum EGameType
  {
    PvP = 1 << 0,
    CTE = 1 << 1,
    PvE = 1 << 2,
    MidOnly = 1 << 3,
    All = PvP | CTE | PvE | MidOnly,
  }

  [Custom( "DBServer", "Social" )]
  public class TargetHeroes : DBResource
  {
    public List<DBPtr<Hero>> heroes;
  }

  [Custom( "DBServer", "Social" )]
  public class GameProps 
  {
    [Custom("DBServer", "Social")]
    [Description("Список карт и режимов игры")]
    public List<DBPtr<AdvMapDescription>> maps;

    [Description( "Session type" )]
    [Custom( "DBServer", "Social" )]
    public ESessionType sessionType = ESessionType.All;
  }

  [Custom( "DBServer", "Social" )]
  public class ValueProps
  {
    [Description( "Значение, которое прибавляется (чтобы было +2 надо сюда вписать 2)" )]
    public float additiveValue = 0.0f;
    [Description( "Процентное значение, которое прибавляется (чтобы прибавить 15%, надо сюда вписать 0.15" )]
    public float multiplicativeValue = 0.0f;
  }

  [Custom("DBServer", "Social")]
  [NonTerminal]
  public class GuildShopItemBonus : DBResource
  {
      [Description("Тултип для баффа")]
      public TextRef propertyTooltip = new TextRef();
  }

  
  [Custom( "DBServer", "Social" )]
  public class HeroBonusBase : GuildShopItemBonus
  {
    public List<DBPtr<Hero>> heroes;
  }

  [Custom( "DBServer", "Social" )]
  public class SessionBonus : HeroBonusBase
  {
    public GameProps gameSettings;
  }

  [Custom("DBServer", "Social")]
  public class GuildWarEventPass : SessionBonus
  {
    [NoCode, Browsable(false)]
    public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom( "DBServer", "Social" )]
  public class SessionValueBonus : SessionBonus
  {
    public ValueProps modifiers;
  }

  [Custom("DBServer", "Social")]
  public class HeroExperienceBonus : SessionValueBonus
  {
      [NoCode, Browsable(false)]
      public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom("DBServer", "Social")]
  public class SessionResourceBonus : SessionValueBonus
  {
    public EResourceType resource;
  }

  [Custom("DBServer", "Social")]
  [NoCode]
  public class SessionTalentsBonus : SessionValueBonus
  {
      [NoCode, Browsable(false)]
      public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom("DBServer", "Social")]
  [NoCode]
  public class ClanPointsBonus : SessionValueBonus
  {
      [NoCode, Browsable(false)]
      public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom( "DBServer", "Social" )]
  [NoCode]
  public class PlayerPointsBonus : SessionValueBonus
  {
    [NoCode, Browsable( false )]
    public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom( "DBServer", "Social" )]
  public class StatBonus
  {
    [Description("Увеличиваемый стат (Will, Strength..)")]
    public EStat statType;
    public ValueProps modifiers;
  }

  [Custom("DBServer", "Social")]
  public class StatChangeBonus : SessionBonus
  {
    [Description("Список возможных статов для бафа")]
    public List<StatBonus> statBonuses;
    [Description("Список характеристик, которые не работают друг с другом")]
    public List<EStat> excludedBufs;
    [Description("Тип действия (при старте игры или к 36 уровню)")]
    public EStatBufToggle toggle;
  }

  [Custom("DBServer", "Social")]
  public class HeroEnergyBonus : SessionValueBonus
  {
      [NoCode, Browsable(false)]
      public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom("DBServer", "Social")]
  public class SiegePointsBonus : SessionValueBonus
  {
      [NoCode, Browsable(false)]
      public int fakeFieldForCastle; //заливаю это по просьбе Ильи Михайлова, ибо разбираться с DBCodeGen некогда, но клятвенно обещаем разобраться
  }

  [Custom("DBServer", "Social")]
  public class GuildBuff : DBResource
  {
    [Description("ID бафа")]
    public string persistentId = null;
    [Description("Список расходников, с которыми одновременно не работает")]
    public List<DBPtr<GuildBuff>> doNotWorkWith;
    [Description("Если true, то по выходу из клана бонус у игрока пропадает")]
    public bool isGuildBonus;
    [Description("Приоритет для списка расходников (вес эффекта) - какой из них остается работать")]
    public int priority;
    [Description("Длительность")]
    public int duration;
    [Description("Количество игр, в течение которых активен баф")]
    public int numGames;
    [Description("Тултип для свойства - тот что будет показываться не в магазине, а при наведении на иконку баффа")]
    public TextRef propertyTooltip = new TextRef();
    public List<DBPtr<GuildShopItemBonus>> bonuses;
  }

  [UseTypeName("GUILDBUFFS")]
  [Custom("DBServer", "Social")]
  public class GuildBuffsCollection : DBResource
  {
    public List<DBPtr<GuildBuff>> buffs;
  }


}