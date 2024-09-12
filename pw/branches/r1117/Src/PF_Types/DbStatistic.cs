using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;

namespace PF_GameLogic.DBStats
{
  public enum EHeroTitle
  {
    BestKiller,     //Убийца героев 
    BestAssister,   //Лучший напарник 
    TopCreepKills,  //Истребитель / Истребительница 
    TopTowerKills,  //Разрушитель 
    LeastDeaths,    //Неистребимый / Неистребимая 
    TopNafta,       //Добытчик / Добытчица 
    Painter_mg2,    //Художник / Художница 
    Dedicated_mg2,  //Целеустремленный / Целеустремленная 
    Merciless,      //Безжалостный/ Безжалостная 
    Wanderer,       //Странник/ Странница 
    Teleporter,     //Мерцающий / Мерцающая 
    Stay_at_home,   //Домосед  / Домоседка 
    TopConsumableUser, //Жаждущий / Жаждущая 
		LeastConsumableUser, //Стойкий / Стойкая 
    Ascetic,        //Аскет 
    TopKillStreaker,//Необоримый 
    Shinigami,      //Жнец жизней
    Adventurer,     //Искатель приключений 
    TopTowerDenier,   //Принципиальный 
    TopNeutralKiller, //Охотник / Охотница 
    TopCeremonialKiller, //Жрец / Жрица 
    TopOneHeroKiller, //Дерзкий 
    Avenger,        //Мститель 
		LastHitToMainBuilding,//Хваткий / Хваткая
    TopIdleTime,    //Статуя 
    Huntsman,       //Ловчий
    DragonSlayer,   //Драконоборец 
    Legend,         //Живая легенда 
    Kamikaze,       //Камикадзе
    Novice,          //Все впереди
    BossSlayer      //Убийца босса
  }

  public enum EScoreType
  {
      HeroKillCount, // - Убийства героев (количество убийств вражеских героев)
      DeathCount,    // - Смерти (количество смертей)  
      AssistCount,   //- Поддержки (количество поддержек)
      Score,         //- Очки (количество набранных очков)   
      TotalNafta,    //- Собрано нафты (количество собранной нафты)   
      AchievmentCount,//- Подвиги (количество совершенных подвигов)
      TowersDestroyed,//- Разрушено башен (количество разрушенных башен)  
      TowersDenied,   //- Отказано башен (количество отказанных башен)
      FlagsRaised,    //- Поднято флагов (количество поднятых флагов)
      FlagsDestroyed, //- Уничтожено флагов (количество уничтоженных флагов)
      MinigameLevelsWon, //- Выиграно уровней мини игры (количество выигранных уровней мини игры)
      CreepsKilled,   //- Убито солдат (количество убийств вражеских солдат)
      NeutralCreepsCount, //- Убито монстров (количество убийств нейтральных монстров)
      TimeInDeath,    //- Время, проведенное в смерти (количество времени (в секундах), проведенного в смерти)
      HeleadAmount,   //- Вылечено Здоровья (количество вылеченного за сессию своего Здоровья)  
      SexHelp,        //- Помощь противоположному полу (количество раз, когда был оказана помощь героям противоположного пола с помощью Gender-талантов)
      DamageDealed,   //- Нанесенный урон (общее количество нанесенного урона)  
      DamageRecieved, //- Полученный урон (общее количество полученного урона)
      DanageHeroDealed, // - Нанесеный урон по героям
      DanageHeroRecieved, // - Полученный урон от героев
      MeterialDamageDealed,   //- Нанесенный материальный урон (количество нанесенного материального урона)
      MeterialDamageRecieved, //- Нанесенный материальный урон (количество нанесенного материального урона)
      EnergyDamageDealed,     //- Нанесенный энергетический урон (количество нанесенного энергетического урона)
      EnergyDamageRecieved    //- Полученный энергетический урон (количество полученного энергетического урона)
  }


  public class ScoreDescription
  {
      [Description("score name")]
      public TextRef name;

      [Description("score icon")]
      public DBPtr<Render.DBRenderResources.Texture> icon;

      [Description("output priority")]
      public int outputPriority = 0;
  };

  public class HeroTitle
  {
    public TextRef maleName;
    public TextRef femaleName;

    [Description("Tooltip for final statistics")]
    public TextRef tooltip;

    [Description("Icon image")]
    public DBPtr<Render.DBRenderResources.Texture> image;

    public float score;
  }

  //==========================================================================================================================
  [UseTypeName("StatisticData")]
  public class DBStatisticData : DBResource
  {
    public TextRef winnersTeamStr = new TextRef();
    public TextRef losersTeamStr = new TextRef();
    public TextRef levelFormatStr = new TextRef();
    public TextRef favoritesFeatsStr = new TextRef();
    public TextRef timeUnderBlessingStr = new TextRef();
    public TextRef totalHeartsStr = new TextRef();
    public TextRef heartsFromMenAndMinigamesStr = new TextRef();
    public TextRef goldAndSilverFromMinigameStr = new TextRef();
    public TextRef killingAssistantsStr = new TextRef();
  }

  //==========================================================================================================================
  public class PFUIGameLogicRoot : DBResource
  {
    public DBPtr<DBStatisticData> statisticData;
  }

  public class FactionScoringTable : DBResource
  {
    // scoring
    public int loose = 10;
    public int win   = 30;
    [Description( "Base score for tower destruction" )]
    public float towerDestroyedBase = 1.0f;
    [Description( "Tower level multiplier for scoring" )]
    public float towerDestroyedLevelMul = 1.0f;
    public int bossKill = 1;
    public int topKills = 5;
    public int topAssists = 5;

    // restrictions
    public int maxBossKillScore = 5;
  }

  public class RestrictedScoring
  {
    public int score;
    public int maxScore;
  }

  public class DiscreteScoring : RestrictedScoring
  {
    public int count;
  }

  public class HeroScoringTable : DBResource
  {
    public int heroOfTheDay = 5;
    public int towerKill = 2;
    public RestrictedScoring heroKill;
    public RestrictedScoring bossKill;
    public RestrictedScoring goldMedals;
    public RestrictedScoring silverMedals;
    public RestrictedScoring buildingDestroy;
    public DiscreteScoring flagRaise;
    public DiscreteScoring flagDrop;
  }

  [TypeId(0xA06693C0)]
  [UseTypeName("SCTB")]
  public class ScoringTable : DBResource
  {
    public DBPtr<FactionScoringTable> faction;
    public DBPtr<HeroScoringTable> hero;

    [Description("All game achievements")]
    public List<DBPtr<AchievBase>> achievementsList;

    [Description("Hero titles")]
    [EnumArray(typeof(EHeroTitle))]
    public List<HeroTitle> heroTitles;

    [Description("List score descriptions")]
    [EnumArray(typeof(EScoreType))]
    public List<ScoreDescription> scoreDescriptions;

    [Description("Abilities whose teleports are counted by Teleporter title")]
    public List<DBPtr<Ability>> teleporterAbilities;
  }
}
