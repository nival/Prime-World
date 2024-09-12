using System;
using System.Collections.Generic;
using libdb.DB;
using PF_Types.SocialClient;
using PF_GameLogic.DBStats;
using System.ComponentModel;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBTalent;
using SocialTypes.DBTypes;
using PF_GameLogic.DBAdvMap;

namespace SocialTypes.Quests
{
  [NonTerminal]
  public class QuestAction : DBResource
  {
      [Description("При выборе All - действие выполняется для всех без исключений, выбор какой-то одной из фракций или только одного из полов - означает ограничения выполнения действия только для игрока с данным полом/фракцией. Если выбрано оба пола или обе фракции - значит по этим характеристикам нет ограничений, равнозначно не выбору этих значений вовсе.")]
      public GenderFractionFilter genderFractionFilter = GenderFractionFilter.All;
  }

  [NonTerminal]
  public class ClientQuestAction : QuestAction
  {
  }

  [Flags]
  public enum GenderFractionFilter
  {
    All = 0,
    Male = 0x1,
    Female = 0x2,
    A = 0x4,
    B = 0x8,
  }

  [NonTerminal]
  public class QuestCondition : DBResource
  {
  }

  public enum FinsihSessionResult
  {
    DontCare,
    Win,
    Lose,
  }

    public enum OpenWindowConditionType
    {
        Academy,
        CastleMain
    }

  public class OpenWindowCondition : QuestCondition
  {
      public OpenWindowConditionType windowName = OpenWindowConditionType.Academy;
  }

  public class CloseAllWindowCondition : QuestCondition
  {
  }

  public class FinishSessionCondition : QuestCondition
  {
    [Description("Результат по возвращению")]
    public FinsihSessionResult result = FinsihSessionResult.DontCare;
    [Description( "Список карт, любую из которых надо завершить. Пустой список - любая карта" )]
    public List<DBPtr<AdvMapDescription>> maps;
  }

  public enum SendRequestPhase
  {
    ClientAccepted,
    ServerAccepted,
  }

  public enum SendRequestName
  {
      accept_friend,
      accept_quest,
      add_all_talents,
      add_dodges,
      add_friend,
      add_friend_to_favorites,
      add_ignore,
      add_quest,
      add_statistic,
      add_talent,
      add_to_pocket,
      boost_buildingproduction,
      building_move,
      building_place,
      building_remove,
      building_upgrade,
      buy_cycle,
      buy_hero,
      buy_hero_gold,
      buy_premium_account,
      buy_premium_account_GM,
      buy_special_hero,
      change_fraction,
      change_last_login,
      change_map,
      change_nickname,
      change_pa_end,
      check_pending_quests,
      check_talent,
      clear_item_soulbound,
      clear_soulbound,
      collect_production_results,
      collect_talent,
      complete_quest,
      decline_friend,
      decrease_energy,
      expansion,
      finish_production,
      force_complete_objective,
      get_prices,
      give_experience,
      give_fame,
      give_rating,
      give_resource,
      give_stat_points,
      hire_hero,
      increase_building_lvl,
      increase_stat,
      invite_friend,
      item_move_inv2ts,
      item_move_ts2inv,
      item_move_ts2ts,
      item_remove_new_status,
      item_set_actbar_idx,
      keepalive,
      mark_event_viewed,
      merge_talents,
      mm_accept,
      mm_add,
      mm_cancel,
      mm_leave,
      move_from_pocket,
      move_perl_into_building,
      move_to_pocket,
      notify_session_ended,
      only_guard,
      party_accept,
      party_decline,
      party_disband,
      party_go,
      party_hero,
      party_invite,
      party_kick,
      place_friend_to_building,
      place_hero_to_building,
      remove_friend,
      remove_friend_from_building,
      remove_friend_from_favorites,
      remove_hero_from_building,
      remove_ignore,
      remove_perl_from_building,
      remove_talents,
      reset_counters,
      reset_new_talents,
      reset_stat_points,
      return_friend,
      search_friend,
      set_guard,
      set_new_status,
      skip_objective,
      start_building_production,
      stop_building_production,
      try_complete_objective,
      upgrade_talent,
  }

  public class SendRequestCondition : QuestCondition
  {
    [Description("Имя запроса")]
    public SendRequestName name = SendRequestName.expansion;
    [Description("Фаза исполнения запроса")]
    public SendRequestPhase phase = SendRequestPhase.ClientAccepted;
  }

  public class ModelDataCondition : QuestCondition
  {
    [Multiline]
    public string code = string.Empty;
    [Description("Условия, по выполнению любого из которых происходит проверка кода")]
    public List<DBPtr<QuestCondition>> triggers;
  }

  public class RepeatableCondition : QuestCondition
  {
      [Description("Условие, по которому вызываются действия пока квест активен")]
      public DBPtr<QuestCondition> trigger;
      [Description("Набор действий, выполняемый после срабатывания триггера")]
      public List<DBPtr<ClientQuestAction>> actions;
  }

  public enum StatisticEventType
  {
    SESSION_FINISH,
    SESSION_RESOURCE,
    SESSION_TALENT,
    BATH_START,
    BATH_FINISH,
    PRODUCTION_START,
    PRODUCTION_FINISH,
    TALENT_START,
    TALENT_FINISH,
    TALENT_UNSOULBOUND,
    TALENT_SOULBOUND,
    TALENT_UPGRADE,
    TALENTS_REMOVE,
    FREE_SKIP,
    DAILY_COMPLETE,
    PRODUCTION_SKIP,
    HERO_LEVEL,
    HERO_RATING ,
    HERO_FORCE,
    BUILDING_LEVEL,
    TALENT_REFORGE,
    GUILD_SESSION_FINISH,
    BUILDING_BOOST,
    RED_PERL_BUY,
    TALENT_REFORGE_UPGRADE
  }

  public class StatisticEventConditionItem
  {
    public StatisticEventType eventType = StatisticEventType.PRODUCTION_FINISH;
    [Description( "Regex уточняющий действие" )]
    public string description; 
  }

  public class StatisticEventCondition : QuestCondition
  {
    [Description("Список эвентов, каждый из которых может привести к комплиту условия")]
    public List<StatisticEventConditionItem> events;
    [Description( "Если true condition возвращает 1, иначе - value из эвента" )]
    public bool countOnly = false;
  }

  public class Objective
  {
    public DBPtr<QuestCondition> condition;
    [Description( "Накапливать ли value в процессе проверки условия. Те если стоит True, то при повторном вычислении условия value увеличится, пока не достигнет значения в objective" )]
    public bool incremental = false;

    [Description("показывать ли прогресс выполнения обжектива. Пример: 1/13")]
    public bool showProgress = true;
    public int value = 1;

    [Description("Таймаут в минутах на изменение Value обжектива (актуально для накопительных условий)")]
    public int timeOutInMinutes = 0;

    public DBPtr<ModelDataCondition> autoCompleteCondition;
    public bool showInUI = true;

    [Description("текст обжектива")]
    public TextRef Text;

    public List<DBPtr<QuestAction>> skip;
    [Description( "Стоимость пропуска обжектива. 0, если обжектив нельзя пропустить" )]
    public ResourcesTable skipPrice;

    [Description("Повторяемое действие пока квест активен")]
    public DBPtr<RepeatableCondition> repeatableCondition;

    [Description("текст на кнопке быстроклика")]
    public TextRef InstantText;
    public List<DBPtr<ClientQuestAction>> instant;

    [Description( "Дейсвтия, которые выполнятся при выполнении данного обжектива" )]
    public List<DBPtr<QuestAction>> completeActions;

    [Description("Если мы послали try_complete_objective, а он не закомплитился, то вернем эту ошибку")]
    public int errorCode;

  }

  public class Reward
  {
    [Description( "Текст кнопки с данным выбором" )]
    public TextRef caption;
    [Description( "Список действий по этому выбору" )]
    public List<DBPtr<QuestAction>> actions;
  }

  [IndexField( "caption" ), NonTerminal]
  public class DialogBase : DBResource
  {
    [NoCode]
    public string caption;
  }

  public class CastleDialog : DialogBase
  {
    public List<Phrase> phrasesA;
    public List<Phrase> phrasesB;
    public TextRef locationNameA;
    public TextRef locationNameB;
    [Description("location image for Docts quest")]
    public DBPtr<Render.DBRenderResources.Texture> locationImageA;
    [Description("location image for Adornians quest")]
    public DBPtr<Render.DBRenderResources.Texture> locationImageB;
  }

  [IndexField( "sctiptName" )]
  public class Caption : DialogBase
  {
    public string sctiptName;
    [Description( "Время реплики. Работает только для terminate = Time или TimeAndKey. Если -1 - совпадает с длительностью скрипта" )]
    public float duration = -1.0f;
    [Description( "Событие по которому можно закончить реплику" )]
    public PhraseTerminateEvent terminate = PhraseTerminateEvent.TimeAndKey;
  }

  #region talent quest

  public class DynamicQuestForTalents : DBResource   //root
  {
    [Description( "Таланты, для которых не выдем квесты" )]
    public List<DBPtr<Talent>> ForbadeTalents;

    [Description( "Цены для рарностей" )]
    public List<DynamicQuestForTalentsPrice> PricesMap;
    [Description( "Перегрузка цен для талантов" )]
    public List<DynamicQuestForTalentsOverridenPrice> OverridenPricesMap;

    [Description( "Сложности для рарностей" )]
    public List<DynamicQuestForTalentsDifficulty> DifficultiesMap;
    [Description( "Перегрузка сложностей для талантов" )]
    public List<DynamicQuestForTalentsOverridenDifficulty> OverridenDifficultiesMap;

    [Description( "Группы квестов" )]
    public List<DQuestForTalentsGroup> QuestsGroups;
  }

  [IndexField( "ETalentRarity" )]
  public class DynamicQuestForTalentsPrice
  {
    [Description( "Рарность для этой стоимости" )]
    public ETalentRarity ETalentRarity;

    [Description( "Цена в ресурсах" )]
    public ResourcesTable Resources;
  }

  [IndexField( "Talent" )]
  public class DynamicQuestForTalentsOverridenPrice
  {
    [Description( "Талант" )]
    public DBPtr<Talent> Talent;

    [Description( "Цена в ресурсах" )]
    public ResourcesTable Resources;
  }

  [IndexField( "ETalentRarity" )]
  public class DynamicQuestForTalentsDifficulty
  {
    [Description( "Рарность для этой сложности" )]
    public ETalentRarity ETalentRarity;

    [Description( "Сложность" )]
    public int Difficulty;
  }

  [IndexField( "Talent" )]
  public class DynamicQuestForTalentsOverridenDifficulty
  {
    [Description( "Талант" )]
    public DBPtr<Talent> Talent;

    [Description( "Сложность" )]
    public int Difficulty;
  }

  [IndexField( "Difficulty" )]
  public class DQuestForTalentsGroup
  {
    [Description( "Сложность" )]
    public int Difficulty;
    [Description( "Сами квесты" )]
    public List<DBPtr<DQuestForTalent>> Quests;
  }

  [IndexField( "Title" )]
  public class DQuestForTalent : DBResource
  {
    [Description("Заголовок квеста")]
    public TextRef Title;
    [Description("Что надо сделать")]
    public TextRef Description;
    [Description("Длительность квеста (в секундах), стартует в тот момент, как добавили его")]
    public int Duration;
    [Description("Ccылка на картинку")]
    public TextRef NPCPortret;
    [Description("Логика нужных действий")]
    public List<DBDynamicObjective> DynamicObjectives;
    [Description("Награды")]
    public List<DBDynamicAward> DynamicAwards;
  }

  // типы, определяющие динамический квест, изначально были нагло скопрованы из ModelData
  // такое решение из-за возможного желания полностью перенести создание квестов для талантов в gm tool
  public class DBDynamicAward
  {
    public DynamicQuestAwardType AwardType;
    public string TextData;  // для награды в кастомной валите это поле задает ее id 
    //public string CustomCurrencyId; // id кастомной валюты (для кастомной валюты)
    public int Value;                           // Числовое значение (для ресурсов, опыта и т.д)
    public int PersistentId;                    // crc32 для талантов, героев, зданий, скинов..
    public DynamicQuestAwardConditionType AwardConditionType =  DynamicQuestAwardConditionType.AfterWin; //условия получения награды
  }

  public enum DynamicQuestAwardType
  {
    PremiumAcc = 0,
    Gold = 1,
    Resource1 = 2,
    Resource2 = 3,
    Resource3 = 4,
    Silver = 5,
    Perl = 6,
    RedPerl = 7,
    Talent = 8,
    RandomTalent = 9,
    Construction = 10,
    Experience = 11,
    Lamp = 12,
    CustomFlag = 13,
    Hero = 14,
    Skin = 15,
    FractionChange = 16,
    NicknameChange = 17,
    HeroExperience = 18,
    HeroStatsReset = 19,
    AllHeroStatsReset = 20,
    Quest = 21,
    RandomHero = 22,
    RandomSkin = 23,
    RandomTalentFromPool = 24,
    AlreadyCompletedQuest = 25,
    UpgradeHeroTalentsEvent = 26,
    GuildLogoChange,
    GuildExperience,
    Shard = 29,
    CustomCurrency = 30,
  }

  public class DynamicQuestLampAward
  {
    public string DbId;
    public int Bonus;
    public int Transactions;
    public int Duration;
  }

  public class DynamicQuestUpgradeHeroTalentsAward
  {
    public int usesLeft;
  }

  public enum DynamicQuestAwardConditionType
  {
        AfterWin = 0,
        AfterMiss = 1,  //будет отвечать за выдачу данной награды, если игрок пропустил квест
  }

  [IndexField( "QuestCheckType" )]
  [Description( "Нужно выбрать определённый condition в зависимости от QuestCheckType" )]
  public class DBDynamicObjective
  {
    public DBDynamicQuestCheckType QuestCheckType;
    public bool ShowProgress;
    public TextRef Description;
    public TextRef ButtonDescription;

    // Условия выполнения квеста
    public DBSessionCondition SessionCondition;
    public DBInstantCondition InstantCondition;
    public DBMDCondition ModelDataCondition;
  }  

  public enum DBDynamicQuestCheckType
  {
    SessionResult = 0,// Учитываем внутрисессионную статистику
    SessionInfo,      // Просто победа в режиме определённым или любым героем
    Instant,          // Сдать ресурсы
    ModelData,        // Проверка зданий, декораций, героев, скинов... Пока не используется.
  }

  public class DBSessionCondition
  {
    public List<int> PickedHeroes;        // Герой, которым надо выиграть бой (для сессионных квестов)
    public List<string> GameTypes;        // Тип игры, в который надо сходить (PvP, PvE..)
    public string CollectingType;               // Тип стата, который нужно набрать (kills, assists..)
    public int TotalValue;                      // Кол-во, которое надо набрать
    public int IncrementPerBattle;              // Максимальный прирост за одну битву
    public DBSessionCheckType SessionCheckType;   // Учитывать результаты только при победе или при победе/поражении
    public bool IsGuildGame;                    // Победить в гильдийском сражении
    public int PlayerPartySize = 1;             // Минимальный размер своей группы, которым нужно победить-----
    public bool IsPlayerPartySizeStrongCond;    // Строгое условие на размер своей группы
    public int EnemyPartySize = 1;              // Минимальный размер группы соперников, которую надо победить
    public bool IsEnemyPartySizeStrongCond;     // Строгое условие на размер группы соперников
  }

  public enum DBSessionCheckType
  {
    WinOnly = 0,
    WinAndLoss = 1,
    Loss = 2,
  }

  public class DBInstantCondition
  {
    public CastleResources ResourceType;
    public string CustomCurrencyId;
    public string TotalValue;
  }

  public class DBMDCondition
  {
    public DBModelDataConditionType TypeToCollect;
    public List<string> PersistentIds;
    public int TotalValue;
    public long LastEventId;
  }

  public enum CastleResources
  {
    Resource1,
    Resource2,
    Resource3,
    Resource1_Rare,
    Resource2_Rare,
    Resource3_Rare,
    Perl,
    RedPerl,
    Silver,
    Gold,
    Population,
    CWPoints_Clan,
    CWPoints_Player,
    TalentsToPay,
    Shard,
    Custom,
  }

  public enum DBModelDataConditionType
  {
    CastleLogin = 0, 
    HeroLevel,
    HeroLevelUp,
    HeroRating,
    HeroRatingUp,
    HeroForce,
    HeroForceUp,
    BuildingLevel,
    CollectResources,
    ForgeTalent,
    MakeReforges,
    CollectCWPointsGuildFight,
  }

  #endregion

  #region talents collection

  public class TalentsCollectionSettings : DBResource
  {
    public List<TaletnsGrouping> grouping;
  }

  [IndexField( "title" )]
  public class TaletnsGrouping
  {
    public TextRef title;
    public List<TalentsColumn> columns;
  }

  [IndexField( "title" )]
  public class TalentsColumn
  {
    public TextRef title;
    public DBPtr<Render.DBRenderResources.Texture> icon;
    public bool isEventColumn;
    public int rowsPerLine;
    public List<TalentsRow> rows;
  }

  [IndexField( "title" )]
  public class TalentsRow
  {
    public TextRef title;
    public List<TalentItem> items;
  }

  [IndexField( "talent" )]
  public class TalentItem
  {
    public DBPtr<Talent> talent;
  }

  #endregion

  [IndexField( "id" )]
  public class Quest : DBResource
  {
    public string persistentId;
    
    [Description("заголовок квеста")]
    public TextRef Title;

    [Description("квест может быть выдан только один раз")]
    public bool oneTime = true;

    [Description("что надо сделать")]
    public TextRef Description;
    
    public List<DBPtr<DialogBase>> initialDialog;
    public List<DBPtr<DialogBase>> finalDialog;
    public List<Objective> objectives;

    [Description( "Список наград, которые выдаются всегда" )]
    public List<DBPtr<QuestAction>> rewards;

    [Description( "Варианты ответов на финальный диалог со списком действий" )]
    public List<Reward> answers;

    [Description( "влияет ли квест на изменение отображения линейки (пример 1 из 2)" )]
    public bool participateInQuestLine = true;

    [Description("окно квеста сразу открывается при его появлении")]
    public bool autoOpen = false;

    [Description("Какие квесты нужно закомплитить что бы получить доступ к этому квесту")]
    public List<DBPtr<Quest>> prerequisiteQuests;

    [Description("Необходимый уровень замка (минимальный) для выдачи квеста")]
    public int lordLevelRequirement = 1;

    [Description("флаг автоматического открытия окна квестовых наград")]
    public bool autoOpenReward = false;

    [Description("Показывается ли в интерфейсе")]
    public bool isVisible = true;

    [Description("persistentId квеста, на который меняется текущий квест, при смене фракции. Если менять не надо - оставить пустым.")]
    public string alternativeQuestId;
  }

  [IndexField( "caption" )]
  public class QuestLine : DBResource
  {
    public string caption;

    [Description("имя линейки")]
    public TextRef LineName;

    [Description( "Говорящий" )]
    public DBPtr<Actor> actor;
    public List<DBPtr<Quest>> quests;
  }
}