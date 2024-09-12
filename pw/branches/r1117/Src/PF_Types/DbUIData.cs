//#include "DBResources.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBTalent;
using Sound.DBSound;
using UI.DBUI;
using PF_GameLogic.DBSmartChat;
using PF_GameLogic.DBResources;

namespace PF_GameLogic.DBStats
{
  public enum EVisualStyle
  {
    Always,
    Changed,
    DontShow,
  }
   
  public enum EFormatType
  {
    Integer,
    OneDigit,
    TwoDigits,
    Percent,
    OneDigitPercent,
  }

  public enum EPathMarker
  {
      Green,
      Red
  }
  [Custom("Social")]
  public enum EChatChannel
  {
    Global,
    MyTeam,
    BothTeams,
    System,
    Achievments,
    Private,
    Tambur,
    Guild,
    LookingForGroupe,
    Administration,
    SmartChat,
  }

  [Custom("Social")]
  public enum BasicResourceType
  {
    None,
    Gold,
    Silver,
    Crystal,
    RedCrystal,
    Resource1,
    Resource2,
    Resource3,
    Population,
    ClanWarPoints,
    PlayerWarPoints,
    Shard,
  }

  [Custom("Social")]
  public enum EResourceType
  {
    Silver,
    Crystal,
    Resource1,
    Resource2,
    Resource3,
    RedCrystal,
    Shard,
  }

  [Custom("Social")]
  public enum EClanWarsResourceType
  {
    ClanRating,
    PlayerRating
  }

  //дописывайте только в конец. тк дубликат этого енама есть во флеше. 
  //дописывание в конец безопасно. иначе нужно перескопировать Enum во флеш
  public enum EErrorMessageType
  {
    NotEnoughPrimeToBuy,
    NotEnoughManaForAbility,
    AbilityOnCooldown,
    WrongTarget,
    InvulnerableTarget,

	  FlagpoleProtectedByTower,
	  FlagpoleProtectedByNext,
	  FlagpoleTooFar,
	  FlagpoleCurrentlyRising,

    MinigameBusy,
    MinigameProtectedByTowers,
   
    WaitingForTarget,
    OutOfInventory,
    MinigameNotReady,
    MinigameDisabled,
    NotEnoughLifeForAbility,
    PingRestricted,
    SmartChatRestricted,

    ReplayEnded,
  }

  [Custom("Social")]
  public enum GuildShopCategoryType
  {
    ClanBufs,
    PlayerBufs,
    SkinsAndFlags,
    ProductionBonus,
    Talents,
  }

  [Custom("Social")]
  public class ChatChannelDescription
  {
    public TextRef channelName;
    public Color channelColor;

    public TextRef castleChannelName;
    public Color castleChannelColor;

    public bool showChannelName;
    public bool showPlayerName;

    [Description("иконка для таба канала фракции А, если пустая, то таб не появится")]
    public string chatChannelIconA;

    [Description("иконка для таба канала фракции B, если пустая, то таб не появится")]
    public string chatChannelIconB;

    [Description("Если false, то приходящее сообщение не будет вызывать мигание таба")]
    public bool showBlinkOnMessage = true;

    [Description( "shortcuts for channel" )]
    public List<TextRef> shortcuts = new List<TextRef>();

		[Description("Флаг для чистки сообщений, если мы выходим из канала")]
		public bool clearMessagesOnLeave = true;

		[Description("Флаг для спама этого канала в глобал")]
		public bool spamInGlobalChannel = true;

		[Description("Флаг для появления кулдауна на спам в этот канал")]
		public bool cooldownOnSpam = false;
  }

  public class ResourceDescription
  {
    [Description( "tooltip for resource. NOTE: should not contain value tags Dohkt" )]
    public TextRef resourceTooltipFreeze;

    [Description("tooltip for resource. NOTE: should not contain value tags Adornians")]
    public TextRef resourceTooltipBurn;
    
    [Description("image for resource Dohkt")]
    public DBPtr<Render.DBRenderResources.Texture> imageFreeze;
    [Description("image for resource Adornians")]
    public DBPtr<Render.DBRenderResources.Texture> imageBurn;

  }

  public class ErrorMessageDescription
  {
    public TextRef textMessage;
    public bool shouldPlaySound = false;
    public float lifeTime = 1.0f;
  }

  public class AnnouncementDescription
  {
    public TextRef textMessage;
    public float lifeTime = 3.0f;
  }

  public class AttackType
  {
    public TextRef statName, phisicalAttackName, energyAttackName, pureAttackName;
  }

  public class StatParams
  {
    public TextRef      name;
    public EVisualStyle visualStyle;
    public EFormatType  format;
    public float        defValue;
  }

  public class CombatStatuses
  {
    public TextRef replaySpeed;
    public TextRef replayPause;
  };

  [DBVersion(1)]
  public class PWSoundEvents
  {
    [Description("Unit selection sound")]
    public DBFMODEventDesc selection;

    [Description("Target select cancelation sound")]
    public DBFMODEventDesc targetCancelled;

    [Description("Target selection sound")]
    public DBFMODEventDesc targetSelected;

    [Description("Minimap signal sound")]
    public DBFMODEventDesc minimapSignal;

    [Description("Chat marker sound")]
    public DBFMODEventDesc chatMarker;
  };
     

  public class ImpulsiveBuffsParams
  {
      public float minLifeTime;
      public float maxLifeTime;
      public float normalBlendTime;
      public float fastBlendTime;
      public float cancelDelay;
  };

  public class StringTextRefPair
  {
    public string key = string.Empty;
    public TextRef text;
  }


  public class GameUIData
  {
    public TextRef gamePauseMessage;
    public TextRef gameResumeMessage;    
  };

  public class PathMarkerColor
  {
      public HDRColor mul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
      public HDRColor add = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
  }

  [Custom("Social")]
  public class CharStatTooltips
  {
      [FieldCategory("Tooltips for base stats (used in CharStat window)")]
      [EnumArray(typeof(EStat))]
      public List<TextRef> baseStatTooltips = new List<TextRef>();

      [FieldCategory("Tooltips for derivative stats (used in CharStat window)")]
      [EnumArray(typeof(EDerivativeStat))]
      public List<TextRef> derivativeStatTooltips = new List<TextRef>();

      [NoCode]
      [FieldCategory("Tooltips for base stats (used in HeroesBuilding window)")]
      [EnumArray(typeof(EStat))]
      public List<TextRef> heroesBuildingStatTooltips = new List<TextRef>();
  }
  
  public class TipOfTheDay
  {
    public TextRef tipText;
  }
  
  [DBVersion( 0 )]
  public class DamageBloodMaskParams
  {
    [Description( "alpha curve of blood mask right after hit" )]
    public AnimatedFloat alphaCurve = new AnimatedFloat( 0.0f );

    [Description( "alpha level of image when health is low" )]
    public float lowHealthAlpha = 0.2f;

    [Description( "alpha level of image when hero is near death" )]
    public float nearDeathAlpha = 0.4f;

    [Description( "level of health when hero's health is low" )]
    public float lowHealthLevel = 0.33f;

    [Description( "level of health when hero is near death" )]
    public float nearDeathLevel = 0.16f;

    [Description("Color saturation on lowHealthLevel [0..1]")]
    public float lowHealthSaturation = 0.5f;

    [Description("Color saturation on nearDeathLevel [0..1]")]
    public float nearDeathSaturation = 0.2f;

    [Description("Color saturation on death [0..1]")]
    public float afterDeathSaturation = 0.0f;

    [Description("Color saturation on lose [0..1]")]
    public float afterLoseSaturation = 0.3f;

    [Description("Speed of saturation changing in game process (values / sec)")]
    public float saturationChangeSpeed = 1.0f / 3;

    [Description("Speed of saturation changing after loose (values / sec)")]
    public float saturationChangeSpeedAfterLose = 1.0f / 9;
  }

  public class BattleStartAnnouncementParams
  {
    [Description("image for elfs")]
    public DBPtr<Render.DBRenderResources.Texture> imageBurn;

    [Description("image for humans")]
    public DBPtr<Render.DBRenderResources.Texture> imageFreeze;

    [Description("announcement text")]
    public TextRef announcementText;

    [Description( "Sound on battle start (soldiers first spawn)" )]
    public DBFMODEventDesc battleStartSound;
  }

  public class VictoryDefeatImages
  {
    [Description("Defeat: image for elfs ")]
    public DBPtr<Render.DBRenderResources.Texture> DefeatBurn;

    [Description("Defeat: image for humans")]
    public DBPtr<Render.DBRenderResources.Texture> DefeatFreeze;

    [Description("Victory: image for elfs")]
    public DBPtr<Render.DBRenderResources.Texture> VictoryBurn;

    [Description("Victory: image for humans")]
    public DBPtr<Render.DBRenderResources.Texture> VictoryFreeze;
  }

  [Custom("Social")]
  [UseTypeName("MAPMODDESC")]
  public class AdvMapModeDescription : DBResource
  {
    [Description("иконка модификатора")]
    public DBPtr<Render.DBRenderResources.Texture> icon;

    [Description("Тултип модификатора")]
    public TextRef tooltip = new TextRef();
  }

  [Custom("Social")]
  [IndexField("bindKey")]
  public class HotkeyBind
  {
    //TODO подумать как добавлять дуальные бинды. например "Окно талантов = T"
    //фактически это два бинда на нажатие/отжатие одной кнопки

    [Description("Название бинда. показывается в настройках")]
    public TextRef name = new TextRef();

    [Description("ключ бинда. Например cmd_attack")]
    public string bindKey = string.Empty;

    [Description("ключ зависимого бинда бинда. Будет записываться вместе с оновным. Например cmd_attack")]
    public string dependentBindKey = string.Empty;

    [Description("фактор бинда. например bind camera_forward +1.0 'W' и bind camera_forward -1.0 'DOWN'")]
    public float bindFactor = 0.0f;

    [Description("Вспомогательный ли это бинд. Нужен чтобы уметь вводить просто ALT для селфкаста. Подразумевает только 1 клавишу (но любую)")]
    public bool isHelperKey = false;

    [Description("Тултип бинда")]
    public TextRef tooltip = new TextRef();

    [Description("категория бинда")]
    public DBPtr<BindCategory> category;
  }
  

  [Custom("Social")]
  [UseTypeName("BINDCATEGORY")]
  public class BindCategory: DBResource
  {
    [Description("Индекс категории. Обозначает порядок в окне настроек")]
    public int index;

    [Description("Название категории")]
    public TextRef name = new TextRef();
  }

  [Custom("Social")]
  public class Binds
  {
    [Description("список видимых биндов для пользователя")]
    public List<HotkeyBind> bindList = new List<HotkeyBind>();
  }


  public class MapModeCustomDescriptions
  {
    public DBPtr<AdvMapModeDescription> maneuvers;
    public DBPtr<AdvMapModeDescription> guardBattle;
		public DBPtr<AdvMapModeDescription> guildBattle;
    [Description("описание иконки договорных боев")]
    public DBPtr<AdvMapModeDescription> customBattle;
  }

  public class IgnoreListParams
  {
    [Description("out of ignore place")]
    public TextRef outOfIgnorePlace;
  }

  public class MarkerSettings
  {
    public float duration = 10.0f;
    public float otherMarkersCheckRange = 100.0f;
  }

  [Custom("Social")]
  public class ForceColor
  {
    public int force;
    public Color color;
    public DBPtr<UIFontStyle> style;
  }
  
  [Custom("Social")]
  [IndexField("name")]
  public class CountryFlag
  {
    public string id;
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> icon;
    [Description("Название флага")]
    public TextRef name = new TextRef();
    [Description("Аббревиатура страны (2 буквы)")]
    [Custom("DBServer", "Social")]
    public string countryCode = "";
    public TextRef tooltip = new TextRef();
  }

  [Custom("Social")]
  [IndexField("name")]
  public class CustomFlag : DBResource
  {
      public string id;
      [Description("Иконка")]
      public DBPtr<Render.DBRenderResources.Texture> icon;
      [Description( "Большая иконка (85*85) (в SeasonReardWnd)" )]
      public DBPtr<Render.DBRenderResources.Texture> bigIcon;
      [Description("Название флага")]
      public TextRef name = new TextRef();
      public TextRef tooltip = new TextRef();
      public int Price = 0;
  }

  [IndexField( "name" )]
  [Custom("Social")]
  public class GuildShopTab
  {
    public GuildShopCategoryType category;
    [Description("Название категории")]
    public TextRef name = new TextRef();
    public TextRef tooltip = new TextRef();
  }

  [Custom("Social")]
  public class ForceToColorTable
  {
    public List<ForceColor> forceColors = new List<ForceColor>();
  }

  public class DialogsSettings
  {
    public float defaultPhraseDuration = 30.0f;

    [Description("Длительность тишины после фразы")]
    public float defaultSilenceDuration = 0.0f;

    public float FadeInOutPercentage = 0.4f;
  }

  public class PremiumVisualInfo
  {
    [Description("дописка к тултипу таланта полученному благодаря премиуму")]
    public TextRef premiumTooltipAddition;
  }

  public class Locale
  {
      public string locale;
      public TextRef tooltip;
      public DBPtr<Render.DBRenderResources.Texture> localeImage;
  }

  [Custom("Social")]
  public class ReportType
  {
      public TextRef name;
      public int id;
  }

  [Custom("Social")]
  [Description("флаги для ботов")]
  public class BotDefaultFlags
  {
      public CountryFlag adornianDefaultFlag;
      public CountryFlag doctDefaultFlag;
  }


  public class AbuseSettings
  {
    [Description("Длительность ограничения (кулдаун) (сек)")]
    public float cooldownTime = 15.0f;

    [Description("Разрешённое кол-во действий за промежуток времени в обычном режиме")]
    public int maxUsagesPerPeriod = 6;

    [Description("Промежуток в обычном режиме(сек)")]
    public float period = 3.0f;

    [Description("Разрешённое кол-во действий за промежуток времени в режиме ограничения")]
    public int maxUsagesPerRestrictedPeriod = 1;

    [Description("Промежуток в режиме ограничения (сек)")]
    public float restrictedPeriod = 3.0f;

    [Description("Обновлять таймер режима ограничения")]
    public bool refreshRestrictedPeriod = true;

  }

  [DBVersion(1)]
  public class PingAbuseSettings : AbuseSettings
  {

  }

  [DBVersion(1)]
  public class SmartChatAbuseSettings : AbuseSettings
  {

  }

  [UseTypeName( "UIDT" )]
  [DBVersion( 12 )]

  public class DBUIData : DBResource
  {
    [FieldCategory( "Unit info params" )]
    [EnumArray( typeof( EStat ) )]
    public List<StatParams> elements = new List<StatParams>();
    [FieldCategory( "Unit info params" )]

    [Description( "Combat screen status texts" )]
    public CombatStatuses combatStatuses;

    [Description( "Session UI sound events" )]
    public PWSoundEvents soundEvents;

    public AttackType attackType;

    [FieldCategory( "Impulsive buffs" )]
    public ImpulsiveBuffsParams impulsiveBuffsParams;

    [FieldCategory( "Preselection" )]
    [Description( "Color multiplier for preselection" )]
    public HDRColor colorPreselect = new HDRColor( 1.2F, 1.2F, 1.2F, 1.0F );

    [FieldCategory( "Preselection" )]
    [Description( "Color for selection outline (allies)" )]
    public HDRColor outlineAllyColor = new HDRColor( 1.0F, 1.0F, 0.0F, 1.0F );

    [FieldCategory( "Preselection" )]
    [Description( "Color for selection outline (hostiles)" )]
    public HDRColor outlineHostileColor = new HDRColor( 1.0F, 0.0F, 0.0F, 1.0F );

    [FieldCategory( "Preselection" )]
    [Description( "Color for selection outline (neutrals)" )]
    public HDRColor outlineSelfColor = new HDRColor( 1.0F, 0.0F, 0.0F, 1.0F );

    [FieldCategory( "Preselection" )]
    [Description( "Selection outline thickness, in meters" )]
    public float outlineThickness = 0.1f;

    [FieldCategory( "Data for adventure screen: pause messages." )]
    public GameUIData gameUIData;

    [FieldCategory( "Path markers" )]
    [EnumArray( typeof( EPathMarker ) )]
    public List<PathMarkerColor> pathMarkerColor = new List<PathMarkerColor>();

    [FieldCategory( "Talents text fields" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<TextRef> rarityValue = new List<TextRef>();

    [Description( "params for blood mask logic when hero is damaged" )]
    public DamageBloodMaskParams bloodMaskParams;


    [Description( "Error messages descriptions" )]
    [EnumArray( typeof( EErrorMessageType ) )]
    public List<ErrorMessageDescription> errorMessageDescriptions = new List<ErrorMessageDescription>();

    [Description( "Tooltips for char stat" )]
    [Custom( "Social" )]
    public CharStatTooltips charStatTooltips;

    [Description( "Minimap settings" )]
    public DBPtr<DBMinimap> minimap;

    [Description( "Minimal value of tooltip down scale factor" )]
    public float tooltipDownScaleLimit = 0.5f;

    [Description( "params for battle start delay announcement" )]
    public BattleStartAnnouncementParams battleStartAnnouncementParams;

    [Description( "Size of scrolling fields in pixels relative standard ui resolution" )]
    public float mouseScrollingFieldSize = 20;

    [Description( "Visual description for chat channels" )]
    [EnumArray( typeof( EChatChannel ) )]
    [Custom( "Social" )]
    public List<ChatChannelDescription> chatChannelDescriptions = new List<ChatChannelDescription>();

    [FieldCategory("Preselection")]
    [Description("Color for administrator messages in Lobby chat ")]
    [Custom( "Social" )]
    public HDRColor adminMessageColor = new HDRColor(1.0F, 0.0F, 0.0F, 1.0F);

    [Description( "resources visual description" )]
    [EnumArray( typeof( EResourceType ) )]
    public List<ResourceDescription> resourcesDescriptions = new List<ResourceDescription>();

    [Description("ClanWars resources visual description")]
    [EnumArray(typeof(EClanWarsResourceType))]
    public List<ResourceDescription> clanWarsResourcesDescriptions = new List<ResourceDescription>();

    public VictoryDefeatImages victoryDefeatImages;

    [Description("text recources for ignore list")]
    public IgnoreListParams ignoreListParams;

    public MarkerSettings markerSettings;

    [Description("Цветовая дифференциация мощи героев")]
    [Custom( "Social" )]
    public ForceToColorTable forceColors;

    public DialogsSettings dialogsSettings;

    [Description("Настройки ограничений на пинг")]
    public PingAbuseSettings pingAbuseSettings;

    [Description("Цвет для затемнения экрана при блокировании UI")]
    public HDRColor blockSaturationColor = new HDRColor(1.0F, 1.0F, 1.0F, 1.0F);

    [Description("описание кастомных модификаторов. Гвардейцы/Маневры итд")]
    public MapModeCustomDescriptions mapModeCustomDescriptions = new MapModeCustomDescriptions();

    [Description("список статусов загрузки")]
    public List<StringTextRefPair> loadingScreenStatuses = new List<StringTextRefPair>();

    [Description("информация по отображению премиума")]
    public PremiumVisualInfo premiumVisualInfo = new PremiumVisualInfo();

    [Description("список локалей для игроков")]
    public List<Locale> locales = new List<Locale>();

    public List<TipOfTheDay> tips = new List<TipOfTheDay>();

    [Description("список типов жалоб")]
    [Custom("Social")]
    public List<ReportType> reportTypes = new List<ReportType>();

    [Custom("Social")]
    [Description("визуальное описание биндов для настроек")]
    public Binds binds = new Binds();

    [Custom("Social")]
    [Description("список флагов стран")]
    public List<CountryFlag> countryFlags = new List<CountryFlag>();

    [Custom("Social")]
    [Description("флаги для ботов")]
    public BotDefaultFlags botFlags = new BotDefaultFlags();

    [Custom("Social")]
    [Description("список платных флагов")]
    public List<DBPtr<CustomFlag>> customFlags;

    [Custom("Social")]
    [Description("список флагов админов")]
    public List<DBPtr<CustomFlag>> adminFlags;

    [Custom( "Social" )]
    [Description("Вкладки гильдийского магазина")]
    public List<GuildShopTab> guildShopTabs;

    [Description("Смарт-чат")]
    public DBPtr<SmartChatConfiguration> smartChat;

    [Description("Настройки анти-спама для смарт-чата")]
    public SmartChatAbuseSettings smartChatAbuseSettings;

    [Description("Количество союзников, с которыми игрок играл в предыдущем бою, отображаемых в панели 'Недавние игроки' ")]
    public int RecentPlayers = 20;

    [Description("Описание кастомной валюты")]
    public DBPtr<CurrencyDescriptionList> currencies;
  }

  public enum EAdventureTooltipStretchMode { None, Dynamic, Static }

  [DBVersion(1)]
  public class AdventureTooltipSettings : DBResource
  {
    [Description("Show text description in tooltip")]
    public bool     showDesc = true;

    [Description("Stretch tooltip bars to fit unit AABB")]
    public EAdventureTooltipStretchMode stretch = EAdventureTooltipStretchMode.None;

    [Description("State of the tooltip layout")]
    public string uiState = "tooltip_layout";

    [Description("State of the tooltip layout in short mode; May be empty")]
    public string uiStateShort = "";

    [Description("Tooltip text")]
    public TextRef text;
  };

  public class UnitOvertipSettings
  {
    [Description("Overtip settings for ally units; The default ones")]
    public DBPtr<AdventureTooltipSettings> ally;

    [Description("Overtip settings for enemy units; If not set, then 'ally' settings will be used")]
    public DBPtr<AdventureTooltipSettings> enemy;

    [Description("Overtip settings for neutral units; If not set, then 'ally' settings will be used")]
    public DBPtr<AdventureTooltipSettings> neutral;

    [Description("Overtip settings for invulnerable ally units; If not set, then 'ally' settings will be used")]
    public DBPtr<AdventureTooltipSettings> invulnerableAlly;

    [Description("Overtip settings for invulnerable enemy units; If not set, then 'enemy' settings will be used")]
    public DBPtr<AdventureTooltipSettings> invulnerableEnemy;

    public DBPtr<AdventureTooltipSettings> localHero;
    public DBPtr<AdventureTooltipSettings> localHeroSlave;
    public DBPtr<AdventureTooltipSettings> invulnerableLocalHero;
    public DBPtr<AdventureTooltipSettings> invulnerableLocalHeroSlave;
  }

  [DBVersion(9395)]
  [UseTypeName("UITP")]
  public class AdventureTooltipParams : DBResource
  {
    [Description("Per unit type tooltip settings")]
    [EnumArray(typeof(EUnitType))]
    public List<UnitOvertipSettings> units;

    public TextRef locatorName;
  };

  public class TeamInfTooltipSettings
  {
    public TextRef heroTooltip;
  }

  [UseTypeName("UITI")]
  public class UITeamInfoParams : DBResource
  {
    [FieldCategory("Team info tooltip")]
    public TeamInfTooltipSettings tooltipSettings = new TeamInfTooltipSettings();
  }

  [Custom( "Social" )]
  public class Actor : DBResource
  {
    public TextRef name;
    public DBPtr<Render.DBRenderResources.Texture> icon;
    [NoCode]
    [Description( "Описание персонажа для локализаторов" )]
    public string description;
  }

  [Custom( "Social" )]
  public enum PhraseTerminateEvent
  {
    PressKey,
    Time,
    TimeAndKey,
  }

  [Custom("Social")]
  public enum PortretOrientation
  {
    Left,
    Right
  }

  [Custom( "Social" )]
  [IndexField( "caption" )]
  public class Phrase
  {
    [Description( "Говорящий" )]
    public DBPtr<Actor> actorMale;
    [Description( "Говорящий" )]
    public DBPtr<Actor> actorFemale;
    [Description( "Текст реплики" )]
    public TextRef textMale;
    [Description( "Текст реплики" )]
    public TextRef textFemale;
    [Description( "Цвет текста textMale" )]
    public Color colorTextMale = new Color( 0xF9, 0xD8, 0x7A, 0xFF );
    [Description( "Цвет текста textFemale" )]
    public Color colorTextFemale = new Color( 0xF9, 0xD8, 0x7A, 0xFF );
    [Description( "Звук реплики.")]
    public DBFMODEventDesc soundMale;
    [Description( "Звук реплики." )]
    public DBFMODEventDesc soundFemale;
    [Description( "Звук реплики. Указывается как путь относительно Resources/Sound без расширения" )]
    public string socialSoundMale;
    [Description( "Звук реплики Указывается как путь относительно Resources/Sound без расширения" )]
    public string socialSoundFemale;
    [Description( "Время реплики. Работает только для terminate = Time или TimeAndKey. Если -1 - совпадает с длительностью звука" )]
    public float duration = -1.0f;
    [Description( "Символьное имя для ссылок из скриптов (сессия). В замке поле не используется" )]
    public string scriptName;
    [Description( "Событие по которому можно закончить реплику" )]
    public PhraseTerminateEvent terminate = PhraseTerminateEvent.Time;
    [Description("Ориентация портрета в реплике, используется в замке")]
    public PortretOrientation orientation = PortretOrientation.Left;
    [NoCode]
    public string caption;
    [Description("Коллекция картинок для отображения в диалоговом окне")]
    public List<HintImage> hintImages = new List<HintImage>();
  }

  [Custom( "Social" )]
  [IndexField( "caption" )]
  public class Dialog : DBResource
  {
    [NoCode]
    public string caption;
    [Description( "Символьное имя для ссылок из скриптов (сессия). В замке поле не используется" )]
    public string id;
    public TextRef title;
    public List<Phrase> phrasesA;
    public List<Phrase> phrasesB;
  }

  [UseTypeName( "DIALOGS" )]
  public class DialogsCollection : DBResource
  {
    public List<DBPtr<Dialog>> dialogs = new List<DBPtr<Dialog>>();
  }

  [IndexField( "id" )]
  public class Hint
  {
    public string id;
    public TextRef text;
  }

  [UseTypeName( "HINTS" )]
  public class HintsCollection : DBResource
  {
    public List<Hint> hints = new List<Hint>();
  }

  [IndexField("id")]
  public class HintImage : Hint 
  {
    [Description("Картинка диалога")]
    public DBPtr<Render.DBRenderResources.Texture> image;
  }

  [IndexField( "id" )]
  public class SessionQuest
  {
      public string id;
      public TextRef text;
      public int counter = 0;
      public bool primary = false;
  }

  [UseTypeName( "QUESTS" )]
  public class SessionQuestsCollection : DBResource
  {
      public List<SessionQuest> quests = new List<SessionQuest>();
  }

}