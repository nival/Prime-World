//#include "..\Types\Render.cs"
//#include "..\Types\UI.cs"
//#include "..\Types\RenderResources.cs"
//#include "..\PF_Types\DBHero.cs"
//#include "..\PF_Types\DbHeroesList.cs"
//#include "..\PF_Types\SocialClient\DBSocialHeroes.cs"
//#include "..\PF_Types\DBAbility.cs"
//#include "..\PF_Types\DBServerPvPRoll.cs"
//#include "..\PF_Types\DbUIData.cs"
//#include "..\PF_Types\DbMinimap.cs"
//#include "..\PF_Types\DBAdvMap.cs"
//#include "..\PF_Types\DBMapList.cs"
//#include "..\PF_Types\DBGuild.cs"
//#include "..\PF_Types\DBSmartChat.cs"
//#include "..\PF_Types\DBResources.cs"

using System.Collections.Generic;
using System.ComponentModel;
using PF_GameLogic.DBHeroRanks;
using PF_GameLogic.DBUnit;
using SocialTypes.RerollShop;
using libdb.DB;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBHeroesList;
using PF_GameLogic.DBServer;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBTalent;
using PF_Types.SocialClient;
using Render.DBRenderResources;
using SocialTypes.Quests;
using SocialTypes.Guild;
using SocialTypes.ClanWars;
using UI.DBUI;
using PF_GameLogic.DBAdvMap;
using PF_GameLogic.DbMapList;
using PF_GameLogic.DBGuild;
using PF_GameLogic.DBResources;

namespace SocialTypes.DBTypes
{
  public class DefaultMap
  {
    [Description( "Группа карт по умолчанию для режима" )]
    public DBPtr<DBAdvMapDescGroup> group;
    [Description( "Карта по умолчанию для режима" )]
    public DBPtr<AdvMapDescription> map;
    [Description( "Доступна ли она по умолчанию" )]
    public bool enabled;
  }

  [UseTypeName( "ADMPDSCRGR" )]
  public class DBAdvMapDescGroup : DBResource
  {
    [Description( "Список карт и режимов игры" )]
    public List<DBPtr<AdvMapDescription>> maps;
  }

  public class FreeSkipsEventBuildings
  {
    public DBPtr<Constructon> talentProductionBuilding;
    public DBPtr<Constructon> crystalProductionBuilding;

  }

  public class RarityToLevelAndPrice
  {
    public List<int> levelToPrice;
  }

  public class RarityToPointsAndLevel
  {
    [Description("Соотношение количество очков улучшения с уровнем таланта (в порядке возрастания)")]
    public List<int> levelToPoints;
    [Description("Лимит очков, выше которого нельзя улучшить талант")]
    public int refinePointsCap;
  }

  public class BathPriceToHeroLevel
  {
    public int currentLevel;
    public float silver;
  }

  /*
  public class RarityToUnsoulboundPrice
  {
    [Description("Соответствие уровня таланта и цены отвязки (задавать строго в порядке возрастания уровня)")]
    public List<TalentLevelToUnsoulboundPrice> levelToPrice;
  }
  
  public class TalentLevelToUnsoulboundPrice 
  {
    public int level;
    public ResourcesTable price;
  }*/

  public class TalentLevelToUnsoulboundPrice
  {
    public int level;
    public int price;
  }

  public class GoldLampRollSettings
  {
    public int lastPayDate = 0;
    public DBPtr<RollContainer> container;
  }

  public class Credits : DBResource
  {
    public TextRef text;
    public string backImage;
    [Description( "Время за которое должны пролететь титры" )]
    public float duration;
  }

  [IndexField( "name" )]
  public class UIText
  {
    public string name;
    public TextRef text;
  }

  public class UITexts : DBResource
  {
    public List<UIText> items = new List<UIText>();
  }

  [IndexField( "stars" )]
  public class ReforgeRerollPrice
  {
    [Description("количество звезд (уровень заточки) таланта (начиная с 1)")]
    public int stars;
    [Description( "цена, если роллим из всех сетов" )]
    public ResourcesTable priceWithoutSetFilter;
    [Description( "цена, если роллим из конкретного сета" )]
    public ResourcesTable priceWithSetFilter;
  }

  [IndexField( "rarity" )]
  public class ReforgeTalentPrice
  {
    public ETalentRarity rarity;
    [Description( "цены за реролл (сортировка по stars; как минимум должна быть определена цена для 1 stars; если не смогли найти цену для конкретного stars, будет взята ближайшая с меньшем stars цена)" )]
    public List<ReforgeRerollPrice> rerollPrices;
    [Description( "цена за апгрейд" )]
    public ResourcesTable upgradePrice;
    public int talentsToUpgrade = 1;
  }

  public class ContextBuyResourceTabel
  {
    public ContextBuyResource Resource1;
    public ContextBuyResource Resource2;
    public ContextBuyResource Resource3;
    public ContextBuyResource Silver;
    public ContextBuyResource Perl;
  }
  
  public class ContextBuyResource 
  {
    public bool isPack;
    public int resourceCount;
    public float goldPrice;
  }

  #region Old Seasons Types
  /// <summary>
  /// Сезон
  /// 
  /// TODO: плохое название (хорошее - Season)
  /// </summary>
  [IndexField( "persistentId" )]
  public class SeasonSettings
  {
    [Description("Идентификатор сезона")]
    public string persistentId;
    [Description("Имя сезона")]
    public TextRef nameSeason;
    [Description("Настройки лиг в сезонах")]
    public List<LeagueInfo> ParamLeagues;
    [Description("Время начала сезона в Unix TimeStamp")]
    public int startTime;
    [Description("Время окончания сезона в Unix TimeStamp")]
    public int stopTime;
  }

  /// <summary>
  /// настройки лиги для конкретноего сезона
  /// 
  /// TODO: плохое название (хорошее - SeasonLeagueSettings)
  /// </summary>
  [IndexField( "leagueId" )]
  public class LeagueInfo
  {
    [Description( "Минимальный рейтинг, начиная с которого начинается лига" )]
    public int minRating;
    [Description( "Минимальное место в таблице рейтинга для героя пятой лиги, начиная с которого рамка должна отображаться" )]
    public int minLeaderPlace;
    [Description( "Индекс лиги из SeasonLeagues" )]
    public int leagueId;  // TODO: id! (проверить, что юзается реально id)
  }

  /// <summary>
  /// Лига
  /// 
  /// TODO: плохое название (хорошее - League)
  /// </summary>
  [IndexField( "nameLeague" )]
  public class SeasonLeagueSettings
  {
    [Description("Идентификатор лиги")]
    public int leagueId;

    [Description("Индекс для получения данных во флеше ( начинать от 2 )")]
    public int flashDataIndex;  // TODO: переименовать в borderFlashIndex

    [Description( "Индекс индекв фрейма с коронкой во флэше" )]
    public int crownFlashIndex;

    [Description("Важность лиги при её отображении")]
    public int quality;
    
    [Description( "Имя лиги" )]
    public TextRef nameLeague;
  }

  #endregion

    /// <summary>
  /// Using for marks data to export in social(castle) game part.
  /// </summary>
  [UseTypeName( "ROOT" )]
  public class SocialRoot : DBResource
  {
    public DBPtr<CommonConstructionsSettings> CommonConstructionsSettings;
    [Description( "Список зданий замка" )]
    public List<DBPtr<Constructon>> Constructions;
    [Description( "Список героев замка" )]
    public DBPtr<HeroesDB> Heroes;
    [Description( "Список талантов замка" )]
    public List<DBPtr<Talent>> Talents;
    [Description( "Таблица перевода количества fame в уровень лорда" )]
    public DBPtr<DBLevelToFame> LevelToFameTable;
    [Description( "Таблица сколько дают ресурсов за достижение определенного уровня" )]
    public LevelToResources LevelToResources;
    [Description( "Количество статпоинтов, дающихся за уровень" )]
    public DBPtr<DBStatpointsToLevel> StatpointsToLevelTable;
    [Description( "Таблица перевода количества опыта в уровень героя" )]
    public DBPtr<DBLevelToExperience> LevelToExperienceTable;
    [Description( "Таблица зависимости количества очков рейтинга новых героев от уровня фейма" )]
    public DBPtr<DBRatingToFame> HeroRatingToFameLevel;
    [Description( "Таблица уровней системы чести" )]
    public HonorLevelTable HonorLevelTable;
    public DBPtr<StatsBudgetContainer> StatsBudgetContainer;
    public DBPtr<UIRoot> UIRoot;
    public DBPtr<DBUIData> DBUIData;
    [Description( "Таблица ролла для сессии" )]
    public DBPtr<RollSettings> SessionRollSettings;
    [Description( "Класификация героев" )]
    public DBPtr<HeroClassInfoTable> HeroClassesTable;
    [Description( "Список сопоставления номера ошибки соцсервера с текстом для пользователя" )]
    public DBPtr<ErrorMessagesTable> ErrorsTextsTable;
    public DBPtr<AILogicParameters> AIGameLogic;
    public DBPtr<UnitsLogicParameters> UnitLogicParameters;
    [Description( "Карта замка" )]
    public DBPtr<DBMap> Map;
    [Description( "Цены на продажу талантов" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<ResourcesTable> TalentsSellPrice;
    
    //[Description( "Цены на unsoulbound" )]
    //[EnumArray( typeof( ETalentRarity ) )]
    //public List<ResourcesTable> GoldTalentsUnsoulboundPrice;
    
    [Description("Цены на unsoulbound")]
    //[EnumArray(typeof(ETalentRarity))]
    //public List<RarityToUnsoulboundPrice> TalentsUnsoulboundPriceByLevel;
    public List<TalentLevelToUnsoulboundPrice> TalentsUnsoulboundPriceByLevel;
    
    [Description("Рар до которого таланты не привязываются к герою включительно")]
    public ETalentRarity RaritiesWithoutSoulbound;
    [EnumArray(typeof(ConstructionTab))]
    public List<ConstructionTabDesc> ConstructionTabDescs;
    [EnumArray(typeof(HeroClassEnum))]
    public List<ConstructionTabDesc> HeroesTabDescs;
    [Description( "Параметры ускорений циклов за деньги" )]
    public DBPtr<GoldPriceCycleTable> GoldPriceCycleTable;
    [Description( "Начальные параметры гостя" )]
    public DBPtr<MDInitParams> GuestInitParams;
    [Description( "Начальные параметры игрока" )]
    public DBPtr<MDInitParams> PlayerInitParams;
    [Description( "Начальные лимиты игрока" )]
    public DBPtr<ResourceAndInventoryLimits> ResourceAndInventoryLimits;
    [Description( "Начальные лимиты гостя" )]
    public DBPtr<ResourceAndInventoryLimits> GuestResourceAndInventoryLimits;
    [Description( "Первоначальные, сразу построенные домики" )]
    public List<BuildedConstruction> BuildedConstructions;
    [Description( "Табличка процентов на ролл талантов в кузнице" )]
    public DBPtr<DBRollTalentPercents> RollTalentForTransmutationBuilding;
    [Description("Табличка процентов на ролл талантов в кузнице с активным премиумом")]
    public DBPtr<DBRollTalentPercents> RollTalentPremiumForTransmutationBuilding;
    [Description( "Полный список линеек квестов" )]
    public List<DBPtr<QuestLine>> Quests;
    [Description( "Список одиночных квестов" )]
    public List<DBPtr<Quest>> SingleQuests;
    [Description( "Стартовый квест" )]
    public DBPtr<Quest> StartQuest;
    [Description( "Квесты, которые выдаются при смене фракции" )]
    public DBPtr<Quest> StartQuestsForFractionChange;
    [Description( "Коэффициент сброса статов героя" )]
    public ResourcesCoefTable ResetStatsPriceCoef;
    [Description( "Максимально допустимое количество отсутствующих талантов для старта матчмейкинга" )]
    public int MaxEmptyTalents;
    [Description( "Кат сцена пролета камеры. Показывается, например, при первом входе в социальный клиент." )]
    public DBPtr<CastleCutscene> SceneObservationCameraFlyCutScene;
    [Description( "Список дефолтовых карт для каждого режима/слота на экране ворот" )]
    [EnumArray( typeof( MapType ) )]
    public List<DefaultMap> DefaultMaps;
    [Description( "Список групп карт" )]
    public List<DBPtr<DBAdvMapDescGroup>> GroupMaps;
    [Description( "Список доступных для замка карт" )]
    public DBPtr<MapList> AviableMaps;
    [Description( "Количество дополнительного опыта для купленных героев от домиков FirstBuy" )]
    public int FirstBuyHeroExpBonus;

    [Description( "Описание акций" )]
    public MarketingEvents MarketingEvents;

    [Description( "Таблица зависимости уровня таланта от его рарности и количества вложенных в него points. Увеличивая максимальный уровень, не забудь увеличить в Tools/Scripts/FillCompiledTooltips.cs в MAX_REFINE_RATE!" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<RarityToPointsAndLevel> TalentLevelToPointsAndRarity;
    [Description( "Таблица зависимости цены таланта от его рарности и уровня" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<RarityToLevelAndPrice> TalentMergePriceToLevelAndRarity;
    [Description( "Зависимость количества points который дает талант при его поглощении от его рарности" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<int> TalentConsumptionPointsToRarity;
    [Description( "Зависимость стоимости восстановления единцы энергии от уровня героя" )]
    public List<BathPriceToHeroLevel> BathPriceToHeroLevel;

    [Description( "инфа по левелапам гильдии" )]
    public DBPtr<GuildLevels> GuildLevels;

    [Description( "Зависимости для вероятностей выпадания лампы от даты последнего платежа" )]
    public List<GoldLampRollSettings> LampEventsSettings = new List<GoldLampRollSettings>();

    public FreeSkipsEventBuildings freeSkipsEventBuildings;
    public DBPtr<Texture> RandomHeroIcon;
    public DBPtr<Credits> Credits;
    public DBPtr<GuildVisibleBonusesCount> GuildVisibleBonusesCount;
    [Description( "Иконки, которые должны появиться в замке" )]
    public List<DBPtr<Texture>> AdditionalTextures = new List<DBPtr<Texture>>();

    [Description( "Квест, при существовании которого у нас не снимается заставка" )]
    public List<DBPtr<Quest>> QuestsThatDontHideScreenBlocker;

    [Description( "Стоимость перековки разных рарностей талантов" )]
    public List<ReforgeTalentPrice> ReforgeTalentPrices;

    [Description( "Текстовые ресурсы для соц. клиента. Используются в UI и локализуются." )]
    public List<DBPtr<UITexts>> UITexts;

    [Description("Изменение рейтинга неактивных игроков")]
    public DBPtr<RatingDecreaseByTime> RatingDecreaseByTime;

    [Description( "Рейтинг сюзерена к уровню магазина" )] 
    public List<GuildSuzerenLevel> GuildShopLevelToSuzerenExperience;

    [Description("Ассортимент для кланового магазина")]
    public List<DBPtr<GuildShopItem>> GuildShopItems;

    [Description("Гильдийские бафы")]
    //public List<DBPtr<GuildBuf>> GuildBuffs;
    public DBPtr<GuildBuffsCollection> GuildBuffsCollection;

    [Description("Список интервалов рейтингов")]
    public List<int> GuildRatingRanges;

    [Description("Данные для клановых войн")]
    public ClanWarsData ClanWarsData;

    [Description("Данные для поиска подходящих кланов игроками")]
    public GuildRecruitment GuildRecruitment;

    [Description("Кол-во ресурсов, которое покупается за 1 золотой")]
    public ContextBuyResourceTabel resourcesToGoldPrice;

    [Description("Настройки магазина с рероллом")]
    public RerollShopSettings RerollShop;

    [Description("Настройки сезонов")]
    public List<SeasonSettings> Seasons;

    [Description("Настройки лиг")]
    public List<SeasonLeagueSettings> SeasonLeagues;

    [Description("Квесты для талантов")]
    public DBPtr<DynamicQuestForTalents> DynamicQuestForTalents;

    public DBPtr<TalentsCollectionSettings> talentsCollectionSettings;

    [Description("Валюты событий")]
    public DBPtr<CurrencyDescriptionList> currencies;

    [Description( "Список лутбоксов замка" )]
    public List<DBPtr<Lootbox>> Lootboxes;

    [Description("Список сущностей апгрейда талантов замка")]
    public List<DBPtr<TalentUpgradeEntity>> TalentUpgradeEntities;
  }
}
