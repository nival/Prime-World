//#include "DBHeroRanks.cs"
//#include "DBTalent.cs"
//#include "DbAchievements.cs"
//#include "DbAbility.cs"
//#include "DbHero.cs"
//#include "DbUIData.cs"

using System.Collections.Generic;
using libdb.DB;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBHeroRanks;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBStats;
using System.ComponentModel;


namespace PF_GameLogic.DBServer
{
  public enum TalentUpgradeEntityType
  {
    Rune,
    Catalyst
  }

  [UseTypeName("TALUGRDENT")]
  [DBVersion(1)]
  [IndexField("persistentId")]
  public class TalentUpgradeEntity : DBResource
  {
    [Description("ID")]
    [Custom("DBServer", "Social")]
    public string persistentId = null;

    [NoCode]
    [Custom("Social")]
    public TextRef description = new TextRef();

    [NoCode]
    [Custom("Social")]
    public TextRef tooltip = new TextRef();

    [NoCode]
    [Custom("Social")]
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> icon;

    [Description("Тип: улучшатель или катализатор")]
    [Custom("DBServer", "Social")]
    public TalentUpgradeEntityType type;

    [Description("Максимальное кол-во звезд до которого может апнуть")]
    [Custom("DBServer", "Social")]
    public int talentLevelLimit;

    [Description("Шанс срабатывания")]
    [Custom("DBServer", "Social")]
    public int probability;
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  public class RollItemProbability
  {
    [Description("Вес итема для ролла из контейнера - probability всех итемов складываются перед опробыванием вероятности. В лутбоксах -1 гарантирует выдачу итема.")]
    public float probability = 0;
    public DBPtr<RollItem> item;
  }

  [Custom( "DBServer", "Social" )]
  [NonTerminal]
  public class RollItem : DBResource
  {
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class TalentRollItem : RollItem
  {
    public DBPtr<Talent> talent;
  }

  [Custom( "DBServer", "Social" )]
  public enum ClanWarsRollItemType
  {
    ClanRating,
    PlayerRating
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  [UseTypeName("CWROLLITEM")]
  public class ClanWarsRollItem : RollItem
  {
    public ClanWarsRollItemType type;
    public float count;
  }

  [Custom( "DBServer", "Social" )]
  public enum ResourceRollConstraint
  {
    Silver,
    Resource1, 
    Resource2,
    Resource3,
    Pearl,
    RedPearl,
    Shard,
    CustomCurrency
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  public class RollLevelInfo
  {
    public int level = 0;
    public int count = 0;
    public int deviation = 0;
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class ResourceRollItem : RollItem
  {
    public ResourceRollConstraint type;
    public string customCurrencyId;
    public List<RollLevelInfo> itemsFromLord;
    public List<RollLevelInfo> itemsFromHero;
    public List<RollLevelInfo> itemsFromRank;
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class RarityTalentListRollItem : RollItem
  {
    public ETalentRarity rarity;
  }

  [DBVersion( 0 )]
  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLCONT" )]
  public class RollContainer : RollItem
  {
    [Description( "Стоимость контейнера в зависимости от звания (по умолчанию берётся из defaultRollContainerCostByRank общих настроек ролла)" )]
    public DBPtr<RollContainerCostByRank> costByRank;
    public string name = "";
    public List<RollItemProbability> items;
    public int multiplicator = 1;
  }

  [UseTypeName( "ROLLITEM" )]
  public class MarketingEventRollItem : RollItem
  {
    [Custom( "DBServer", "Social" )]
    public string persistentId;

    [NoCode]
    [Custom( "Social" )]
    public DBPtr<BaseMarketingEvent> marketingEvent;

    [NoCode]
    [Custom("Social")]
    public int count;

    public DBPtr<Render.DBRenderResources.Texture> image;
    public TextRef tooltip;
  }

  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class NothingRollItem : RollItem
  {
    public int dummy = 0;
  }

  [Custom( "DBServer", "Social" )]
  public class TalentUpgradeProbability
  {
    [Description( "вероятность" )]
    public float probability = 0f;
    [Description( "очки заточки (опыт) (по ним считается уровень заточки)" )]
    public int points = 0;
  }

  [Custom( "DBServer", "Social" )]
  public class TalentUpgradeProbabilityTable : DBResource
  {
    [Description( "" )]
    public List<TalentUpgradeProbability> upgrades;
  }

  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class TalentUpgradeRollItem : RollItem
  {
    [Description("вероятности очков заточек")]
    public DBPtr<TalentUpgradeProbabilityTable> upgradeTable;
    [Description("итем, из которого должен наролиться ТАЛАНТ")]
    public DBPtr<RollItem> talentItem;
  }

  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class HeroRollItem : RollItem
  {
    public DBPtr<Hero> hero;
  }

  [Custom( "DBServer", "Social" )]
  [UseTypeName( "ROLLITEM" )]
  public class SkinRollItem : RollItem
  {
    public DBPtr<HeroSkin> skin;
  }

  [Custom("DBServer", "Social")]
  [UseTypeName("ROLLITEM")]
  public class FlagRollItem : RollItem
  {
    public DBPtr<CustomFlag> flag;
  }

  [Custom("DBServer", "Social")]
  [UseTypeName("ROLLITEM")]
  public class PremiumAccRollItem : RollItem
  {
    [Description("Сколько дней золотого века выдать в лутбоксе")]
    public int days;
  }

  [Custom("DBServer", "Social")]
  [UseTypeName("ROLLITEM")]
  public class GoldRollItem : RollItem
  {
    [Description("Сколько золота выдать в лутбоксе")]
    public int count;
  }

  [Custom("DBServer", "Social")]
  [UseTypeName("ROLLITEM")]
  public class TalentUpgradeEntityRollItem : RollItem
  {
    public DBPtr<TalentUpgradeEntity> entity;
  }

  [Custom( "DBServer" )]
  public class PointsToContainers
  {
    [Description("Кол-во спец очков")]
    public int specialPoints;
    [Description("Сколько контейнеров давать за указанные очки")]
    public int containers;
  }

  [Custom( "DBServer" )]
  [UseTypeName("CONTSPEC")]
  public class ContainersBySpecialPoints : DBResource
  {
    public List<PointsToContainers> items = new List<PointsToContainers>();
  }

  [DBVersion(0)]
  [Custom( "DBServer" )]
  [UseTypeName("MODEROLL")]
  public class ModeRollSettings : DBResource
  {
    [Description("Scores cap")]
    public int scoresCap = 90;

    [Description("Explicitly roll specified number of containers if player wins")]
    public int containersOnWin = 0;

    [Description("Explicitly roll specified number of containers on player's first win of the day by player`s rank")]
    public DBPtr<RollContainerCountByRank> containersOnFWOD;

    [Description("Дополнительное кол-во контейнеров за спец очки")]
    public DBPtr<ContainersBySpecialPoints> containersBySpecialPoints;

    [Description("Allowed talent groups for roll")]
    public ETalentRollGroup allowedRollGroups = ETalentRollGroup.All;

    [Description("Default roll containers")]
    public List<DBPtr<RollContainer>> containers;

    [Description("Roll containers for premium roll")]
    public List<DBPtr<RollContainer>> premiumContainers;

    [Description( "Roll containers for additional premium roll" )]
    public List<DBPtr<RollContainer>> additionalPremiumContainers;

    [Description("Default container, rolled always")]
    public DBPtr<RollContainer> defaultContainer;

    [Description( "event awards (доп награда, включаемая из конфигов)" )]
    public List<DBPtr<RollContainer>> eventContainers;

    [Description( "premium event awards (доп награда для ЗВ, включаемая из конфигов)" )]
    public List<DBPtr<RollContainer>> premiumEventContainers;

    [Description("Hero endurance loss for session")]
    [Custom( "Social" )]
    public int enduranceGain = 40;

    [Description( "Endurance coeff (applied if hero is tired or enduranceDisableRollBoost is TRUE)" )]
    public float enduranceCoeff = 0.33f;
    public float enduranceFameCoeff = 0.33f;
    public float enduranceExperienceCoeff = 0.33f;
    public float enduranceResourcesCoeff = 0.33f;    
    [Description( "Коэффициент награжденения игрока - матерого ливера" ) ] 
    public float leaversAwardsCoeff = 0.3f;

    [Description("Reliability increment if player wins a match")]
    public int reliabilityOnFinishWin = 3;
    [Description( "Reliability increment if player loses a match" )]
    public int reliabilityOnFinishLose = 5;
    [Description("Reliability match period (duration, in seconds)")]
    public int reliabilityOnFinishPeriod = 1800;
    [Description("Reliability increment for period")]
    public int reliabilityOnFinishPerPeriod = 1;
    [Description( "Reliability increment if player leaves a match" )]
    public int reliabilityOnLeave = -3;
    [Description("Reliability leave penalty afk period (duration, in seconds)")]
    public int reliabilityOnLeavePeriod = 300;
    [Description("Reliability leave penalty")]
    public int reliabilityOnLeavePerPeriod = -1;

    [Description("Plain score multiplicator")]
    public int talentsMultiplicator = 1;
    [Description("Flag for disabling roll boost (if TRUE and hero is NOT tired enduranceCoeff if NOT applied for overall items set)")]
    public bool enduranceDisableRollBoost = true;
    [Description("heroLevel/Fame curve")]
    public List<RollLevelInfo> famePerSession;

    [Description("Fame coeff, applied if player loses a match")]
    public float fameLoseCoeff = 0.33f;
    [Description("Experience coeff, applied if player loses a match")]
    public float experienceLoseCoeff = 0.33f;
    [Description("Resources coeff, applied if player loses a match")]
    public float resourcesLoseCoeff = 1;

    [Description("heroLevel/Experience curve")]
    public List<RollLevelInfo> experiencePerSession;

    [Description( "Dodge points penalty if player leaves a guard match" )]
    public int dodgePointsOnLeave = 1;

    [Description("Rating change will be multiplied by this parameter")]
    public float ratingChangeMultiplier = 1.0f;

    [Description("Минимальная длительность сессии (сек). Если меньше, то награждение пропускается. По умолчанию выкл (0).")]
    public int minSessionDuration = 0;

    [Description("Roll additional talent (from additional premium containers) for premium awarding")]
    public int applyPremiumTalent = 0;

    [Description( "First win of the day rewards" )]
    public DBPtr<RollContainer> FWODRewardContainer;

    [Custom( "Social" )]
    [Description("Mode name")]
    public string modeName;

    [Description("Version for ModeRollSettings. Change for reset users' context")]
    public int version;

    [Description("Если игрок ливнул/дисконнектнулся, а его команда выиграла, то ему засчитывается победа.")]
    public bool teamWinDisconnectedWin = false;

    [Description("Clan Wars Economic settings")]
    public DBPtr<ClanWarsSettings> clanWarsSettings;

    [Description("Минимальный размер партии, начиная с которой начисляется бонус.")]
    public int fullPartySize = 4;


  }

  [Custom( "DBServer" )]
  public class RatingModifier
  {
    [Description( "Нижнее значение рейтинга героя" )]
    public int minValue = 0;
    [Description( "Верхнее значение рейтинга героя" )]
    public int maxValue = 0;
    [Description( "Множитель в случае победы" )]
    public float winModifier = 0;
    [Description( "Множитель в случае поражения" )]
    public float looseModifier = 0;
  }

  [Custom("DBServer")]
  public class FullPartyRatingModifier
  {
      [Description("Нижнее значение рейтинга героя")]
      public int minRating = 0;
      [Description("Бонусный рейтинг")]
      public float ratingBonus = 0;
  }

  [UseTypeName("RCCS")]
  [Custom( "DBServer" )]
  public class RollContainerCostByRank : DBResource
  {
    public List<float> costs;
  }

  [UseTypeName("RCCT")]
  [Custom("DBServer")]
  public class RollContainerCountByRank : DBResource
  {
    public List<int> counts;
  }

  [Custom( "DBServer" )]
  public class SingleRollSettings
  {
    [Description( "Контейнер для ролла" )]
    public DBPtr<RollContainer> rollContainer;

    [Description( "Allowed talent groups for roll" )]
    public ETalentRollGroup allowedRollGroups = ETalentRollGroup.All;

    [Description("Версия. Увеличить если изменилась ссылка на контейнер.")]
    public int version = 0;
  }

  [Custom("DBServer")]
  public class BaseModifierFromQuantity
  {
    public float quantity;
    public float percent;
  }

  [UseTypeName("CWST")]
  [Custom("DBServer")]
  public class ClanWarsSettings : DBResource
  {
    [Description("Базовое значение")]
    public float basePoints = 10;
    [Description("Модификатор от количества игроков одного клана в команде.")]
    public List<BaseModifierFromQuantity> partyClanMembersModifier = new List<BaseModifierFromQuantity>();
    [Description("Модификатор от количества игроков в противоположной команде.")]
    public List<BaseModifierFromQuantity> foeCountsModifier = new List<BaseModifierFromQuantity>();
    [Description("Значение полученное за рейтинг побежденного врага, в виде: номер ранка( из HeroRanks) - множитель")]
    public List<float> defeatedFoeRankModifier = new List<float>();
    [Description("Очки клана. % сбора очков со своих мемберов.")]
    public float clanPoints = .3f;
    [Description("Базовое значение после применения модификаторов умножается на нормализованные по капу очки игрока набранные в сесиии.")]
    public bool normalizeBySessionScores = true;
    [Description("Модификатор клановых очков игрока за золотой век.")]
    public float premiumAccountModifier = 2f;
  }

  [DBVersion(0)]
  [UseTypeName("ROLL")]
  [Custom( "DBServer", "Social" )]
  public class RollSettings : DBResource
  {
    [Description("Used in social part only!")]
    public DBPtr<ModeRollSettings> pvp;

    [Description("Стоимость ролл-контейнера от звания героя по умолчанию")]
    public DBPtr<RollContainerCostByRank> defaultRollContainerCostByRank;

    [Description("Настройки для ролла для первой победы за день в тренировке")]
    public DBPtr<ModeRollSettings> trainingFWODSettings;

    [Description("Модификаторы рейтинговой награды от рейтинга героя")]
    public List<RatingModifier> ratingModifiers = new List<RatingModifier>();

    [Description("Бонусный рейтинг для фуллки от рейтинга героя")]
    public List<FullPartyRatingModifier> fullPartyRatingModifiers = new List<FullPartyRatingModifier>();

    [Description("Контейнер для ролла кузницы (!сейчас отключено, настраивать надо в Social.ROOT!)")]
    public SingleRollSettings forgeRollSettings;

    [Description("Ссылка на гильдийские уровни")]
    public DBPtr<GuildLevels> guildLevels;

    [Description("Minimum hero's level, required for exclusive (orange) talents roll")]
    public int requiredLevelForExclusiveTalents = 21;

    [Description( "Minimum hero's rating, required for exclusive (orange) talents roll" )]
    public int requiredRatingForExclusiveTalents = 1600;

    [Description("Clan Wars Economic settings")]
    public DBPtr<ClanWarsSettings> clanWarsSettings;

  }

  [Custom( "DBServer", "Social" )]
  [NonTerminal]
  [NameMapValue]
  public class GuildBonus : DBResource
  {
    public TextRef tooltip;
  }

  [Custom( "DBServer", "Social" )]
  public class GuildLevel
  {
    [Description( "requiredExp*GuildLevels.requiredExpMultiplier = суммарное количество ресурсов, необходимое для прокачки клана до уровня. В последний уровень не вписывать больше, чем 9 223 372 036 854 775 807 / Множитель" )]
    public long requiredExp = 0;
    public TextRef title;
    public TextRef tooltip;

    public List<DBPtr<GuildBonus>> Bonuses;
  }

  [Custom( "DBServer", "Social" )]
  [UseTypeName( "GUILDLEVELS" )]
  public class GuildLevels : DBResource
  {
    [Description( "Множитель для представления requiredExp в рассчетах. Если уровень гильдии требует 10 опыта и множитель 10^5, то будет считаться что требуется 10*10^5 = 10^6 опыта" )]
    public int requiredExpMultiplier = 100000;
    public List<GuildLevel> levels;
  }

  [Custom( "DBServer", "Social" )]
  [NoCode]
  [UseTypeName( "GUILDBONUS" )]
  public class AdditionHeroExpBonus : GuildBonus
  {
    [Description("Дополнительный процент опыта герою за бой.  Доступен для namemap'а")]
    [NameMapValue]
    public int percent = 0;
  }

  [Custom( "DBServer", "Social" )]
  [NoCode]
  [UseTypeName( "GUILDBONUS" )]
  public class GuildResourceBonus : GuildBonus
  {
    [NameMapValue]
    [Description( "Кол-во гильдийского ресурса за бой. Доступен для namemap'а")]
    public int resource = 0;
  }

  [Custom( "DBServer", "Social" )]
  [NoCode]
  [UseTypeName( "GUILDBONUS" )]
  public class RandomTalentBonus : GuildBonus
  {
    [Description( "Настройки для одиночного ролла" )]
    public SingleRollSettings singleRollSettings = new SingleRollSettings();
  }

  //маркерный класс для выдачи ивентов
  [Custom("DBServer", "Social")]
  [NoCode]
  public class BaseMarketingEvent : DBResource
  {
  }

}
