using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using Foundation.DBSystem;
using PF_GameLogic.DBUnit;

namespace PF_GameLogic.DBStats
{
  public enum EAchievementType
  {
      FirstBlood,
      DoubleKill,
      MassKill,
      Duel,
      Chase,
      Avenge,
      Dominate,
      Vendetta,
      CeremonialKill,
      KillingSpree,
      DoubleAssist,
      MassAssist,
      Saviour,
      MasterControl,
      AssistingSpree,
      BorderGuard,
      FirstAssault,
      DemolishingSpree,
      TowerDeny,
      ClearWay,
      BaseStrike,
      Vandalism,
      WarLord,
      CleanUpCreeps,
      DragonSlayer,
      KittySlayer,
      Legend,
      ForestHunter,

      Ascension,
      SliverRite,
      GoldRite,
      FirstMinigameComplete,
      SessionDuration,
      BossSlayer,
      
      InvalidAchivement,
  }

  [NonTerminal]
  [TypeId(0x8D7C7280)]
  [UseTypeName("FAKE")]
  [FactoryBase("Create", "NWorld::PFWorld")]
  public class FakeObj : DBResource
	{

	}

	[NonTerminal]
  [TypeId(0x4D72CBC2)]
  [UseTypeName("ACHIEV")]
  [FactoryBase("Create", "NWorld::PFAchievBase", "NWorld::PFWorld* world")]
  public class AchievBase : DBResource
  {
    public EAchievementType achievType = EAchievementType.InvalidAchivement;

    [Description( "Achievement name" )]
    public TextRef name;

    [Description( "Amount of score per one achievement" )]
    public int perAchievementScore = 0;
    [Description( "Maximum achievement scores" )]
    public int limit = 0;
    [Description( "Score multiplier (for linear achievements)" )]
    public float multiplier = 1.0f;

    [Description( "Tooltip text for final statistics" )]
    public TextRef tooltip;

    [Description( "Priority for final stat order" )]
    public int priority = 0;

    [Description( "Icon image" )]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [Description( "UI Event" )]
    public DBPtr<UIEvent> evUI;

    [Description( "Сколько прайма дадут за этот подвиг" )]
    public float naftaAward = 0.0f;

  }

  [NonTerminal]
  [TypeId(0x4D732480)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievRuler", "PFAchievement.h")]
  public class AchievRuler : AchievBase
  {
    [Description("Start ruler value")]
    public int start = 2;
    [Description("Ruler step")]
    public int step = 1;
    [Description("Reset values on hero death?")]
    public bool breakOnDeath = true;
  }

  [TypeId(0x4D72CBC3)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievFirstBlood", "PFAchievement.h")]
  public class AchievFirstBlood : AchievBase
  {
  }

  [TypeId(0x4D732B00)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDoubleKill", "PFAchievement.h")]
  public class AchievDoubleKill : AchievBase
  {
    public int timeLimit = 8;
  }

  [TypeId(0x4D732B40)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievMassKill", "PFAchievement.h")]
  public class AchievMassKill : AchievBase
  {
    public int timeLimit = 8;
    public int cnt       = 4;
  }

  [TypeId(0x4D732B41)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDuel", "PFAchievement.h")]
  public class AchievDuel : AchievBase
  {
    [Description("For achievement killer must have life less than this percent")]
    public int maxRestLifePercent = 10;
    [Description("or during duel killer's life was below this percent")]
    public int minLifePercent = 5;
    [Description("Duel duration")]
    public int timeLimit = 30;
  }

  [TypeId(0x4D732B42)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievChase", "PFAchievement.h")]
  public class AchievChase : AchievBase
  {
    public float distanceMult = 0.25f;
    [Description("Chase duration")]
    public int timeLimit = 30;
  }

  [TypeId(0x4D732B43)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievAvenge", "PFAchievement.h")]
  public class AchievAvenge : AchievBase
  {
    public int timeLimit = 15;
    public float distanceLimit = 50.0f;
  }

  [TypeId(0x4D732B45)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDominate", "PFAchievement.h")]
  public class AchievDominate : AchievBase
  {
    [Description("This value must be equal to start value Dominate-ruller")]
    public int minKillsForDominate = 3;
  }

  [TypeId(0x4D732B46)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievVendetta", "PFAchievement.h")]
  public class AchievVendetta : AchievBase
  {
    [Description("This value must be equal to start value Dominate-ruller")]
    public int minKillsForDominate = 3;
  }

  [TypeId(0x4D732280)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievCeremonialKill", "PFAchievement.h")]
  public class AchievCeremonialKill : AchievBase
  {
  }

  [TypeId(0x4D732A80)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievKillingSpree", "PFAchievement.h")]
  public class AchievKillingSpree : AchievRuler
  {
  }

  [TypeId(0x4D732B47)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDoubleAssist", "PFAchievement.h")]
  public class AchievDoubleAssist : AchievBase
  {
    public int timeLimit = 8;
  }

  [TypeId(0x4D732B48)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievMassAssist", "PFAchievement.h")]
  public class AchievMassAssist : AchievBase
  {
    public int timeLimit = 8;
    public int cnt       = 4;
  }

  [DBVersion(0)]
  [TypeId(0x4D732B49)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievSaviour", "PFAchievement.h")]
  public class AchievSaviour : AchievBase
  {
    public int minLifePercent = 50;
    public int damageDealedPeriod = 5;
    public DBPtr<DBAbility.ApplicatorsList> applicatorTypes;
    public DBPtr<DBAbility.ApplicatorsList> exactApplicators;
    public int cooldownPeriod = 60;

    [Description( "Количество секунд, сколько должен прожить герой, после использования на нем спасательной абилки" )]
    public float timeToLive = 5.0f;

    [Description( "Количество секунд, сколько герой должен не получать дамаг по истечении времени timeToLive-timeToNoDamage" )]
    public float timeToNoDamage = 2.0f;

  }

  [TypeId(0x4D732B4A)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievMasterControl", "PFAchievement.h")]
  public class AchievMasterControl : AchievRuler
  {
  }

  [TypeId(0x4D732B4A)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievAssistingSpree", "PFAchievement.h")]
  public class AchievAssistingSpree : AchievRuler
  {
  }

  [TypeId(0x4D732B4B)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievBorderGuard", "PFAchievement.h")]
  public class AchievBorderGuard : AchievBase
  {
    public int byTowerLifePercent = 50;
    public int timePeriod = 30;
  }

  [TypeId(0x4D732B4C)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievFirstAssault", "PFAchievement.h")]
  public class AchievFirstAssault : AchievBase
  {
  }

  [TypeId(0x4D732B4D)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDemolishingSpree", "PFAchievement.h")]
  public class AchievDemolishingSpree : AchievRuler
  {
  }

  [TypeId(0x4D731440)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievTowerDeny", "PFAchievement.h")]
  public class AchievTowerDeny : AchievBase
  {
  }

  [TypeId(0x4D72CBC4)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievClearWay", "PFAchievement.h")]
  public class AchievClearWay : AchievBase
  {
    public int minClearWayTowers = 3;
  }

  [TypeId(0x4D732281)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievBaseStrike", "PFAchievement.h")]
  public class AchievBaseStrike : AchievBase
  {
    public int minBarracks = 2;
  }

  [TypeId(0x4D732B4E)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievVandalism", "PFAchievement.h")]
  public class AchievVandalism : AchievRuler
  {
  }

  [TypeId(0x4D7324C0)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievWarLord", "PFAchievement.h")]
  public class AchievWarLord : AchievRuler
  {
  }

  [TypeId(0x4D732B4F)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievCleanUpCreeps", "PFAchievement.h")]
  public class AchievCleanUpCreeps : AchievBase
  {
    public int minCreepsKilled = 30;
    public int timePeriod = 5;
  }

  [TypeId(0x4D732B50)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievDragonSlayer", "PFAchievement.h")]
  public class AchievDragonSlayer : AchievBase
  {
    [Description("Драконы. Подвиг даётся за любого из них")]
    public List<DBPtr<Creature>> dragons = new List<DBPtr<Creature>>();
  }

  [TypeId( 0x37B1DC00 )]
  [UseTypeName( "ACHIEV" )]
  [FactoryImpl( "Create", "NWorld::PFAchievKittySlayer", "PFAchievement.h" )]
  public class AchievKittySlayer : AchievBase
  {
    [Description( "Киски. Подвиг даётся за любого из них" )]
    public List<DBPtr<Creature>> kitties = new List<DBPtr<Creature>>();
  }

  [TypeId(0x4D732B51)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievLegend", "PFAchievement.h")]
  public class AchievLegend : AchievBase
  {
      [Description("NeutralBosses. Подвиг даётся за любого из них")]
      public List<DBPtr<Creature>> creatures = new List<DBPtr<Creature>>();

  }

  [TypeId(0x4D732B52)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievForestHunter", "PFAchievement.h")]
  public class AchievForestHunter : AchievRuler
  {
  }

  // priestess achievements
  [NonTerminal]
  [TypeId(0x4D739B00)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievStreak", "PFAchievement.h")]
  public class AchievStreak : AchievBase
  {
    [Description("Start streak value")]
    public int start = 3;
  }

  [TypeId(0x4D738C00)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievAscension", "PFAchievement.h")]
  public class AchievAscension : AchievStreak
  {
  }

  [TypeId(0x4D738C01)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievNecklaceOfGlory", "PFAchievement.h")]
  public class AchievNecklaceOfGlory : AchievStreak
  {
  }

  [TypeId(0x4D738C02)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievGoldRite", "PFAchievement.h")]
  public class AchievGoldRite : AchievStreak
  {
  }

  [TypeId(0x4D738C03)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievCraftWoman", "PFAchievement.h")]
  public class AchievCraftWoman : AchievBase
  {
    public float heartsCnt = 5.0f;
  }

  [TypeId(0x4D738C04)]
  [UseTypeName("ACHIEV")]
  [FactoryImpl("Create", "NWorld::PFAchievFirstMinigameComplete", "PFAchievement.h")]
  public class AchievFirstMinigameComplete : AchievBase
  {
  }

  [TypeId( 0xE79BD3C0 )]
  [UseTypeName( "ACHIEV" )]
  [FactoryImpl( "Create", "NWorld::PFAchievSessionDuration", "PFAchievement.h" )]
  public class AchievSessionDuration : AchievBase
  {
    [Description("Минимальная длительность сессии для подвига (минуты)")]
    public float minTime = 0.0f;

    [Description("Максимальная длительность сессии для подвига (минуты)")]
    public float maxTime = 0.0f;

    [Description( "Подвиг только для победивших" )]
    public bool winners = true;

    [Description( "Подвиг только для проигравших" )]
    public bool loosers = false;
  }

  public enum EBossSlayerAchievMode
  {
    OnlyForKiller,
    ForKillerAndAssister,
    ForAllTeammates
  }

  public class AchievBossSlayerData
  {
    public DBPtr<Creature> boss;

    [Description( "Achievement name" )]
    public TextRef name;

    [Description( "Amount of score per one achievement" )]
    public int perAchievementScore = 0;
    [Description( "Maximum achievement scores" )]
    public int limit = 0;
    
    [Description( "Tooltip text for final statistics" )]
    public TextRef tooltip;

    [Description( "Icon image" )]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [Description( "UI Event" )]
    public DBPtr<UIEvent> evUI;

    public EBossSlayerAchievMode mode = EBossSlayerAchievMode.OnlyForKiller;
  }

  [TypeId( 0xB19BF480 )]
  [UseTypeName( "ACHIEV" )]
  [FactoryImpl( "Create", "NWorld::PFAchievBossSlayer", "PFAchievement.h" )]
  public class AchievBossSlayer : AchievBase
  {
    [Description( "Юниты за убийство которых дается ачивка" )]
    public List<AchievBossSlayerData> creatures = new List<AchievBossSlayerData>();

  }
}
