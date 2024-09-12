//#include "DBGameLogic.cs"
//#include "DBCameraSettings.cs"
//#include "DbUIData.cs"
//#include "DbMMaking.cs"
//#include "AdvMapCreep.cs"
//#include "DbStatistic.cs"
//#include "..\Types\VotingForSurrender.cs"
//#include "DBDayNight.cs"

using libdb.DB;
using Render.DBRender;
using PF_GameLogic.DBStats;
using System.ComponentModel;
using Foundation.DBSystem;
using Scene.DBSceneBase;
using PF_GameLogic.DBUnit;
using Sound.DBSound;
using System;
using Render.DBRenderResources;
using System.Collections.Generic;
using PF_GameLogic.DBServer;
using PF_Core.DBEffect;
using UI.DBVotingForSurrender;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBDayNight;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_GameLogic.DBAdvMap
{
  [UseTypeName("HNP")]
  public class HeroNaftaParams : DBResource
  {
    public ExecutableFloatString naftaForKill = new ExecutableFloatString("0.0f");
    public ExecutableFloatString naftaForAssist = new ExecutableFloatString("0.0f");
    public ExecutableFloatString naftaSpecForKill = new ExecutableFloatString("0.0f");
    public ExecutableFloatString teamNaftaForPresence = new ExecutableFloatString("0.0f");
  }

  [DBVersion(1)]
  public class PrimeSettings
  {
    [Description( "Give prime salary to dead heroes" )]
    public bool giveWorldPrimeToDead = true;

    [Description( "World prime receiving after-resurrect delay" )]
    public float giveWorldPrimeRessurectDelay = 0.0f;

    [Description( "Amount of prime, divide with all players in team at start of game" )]
    public int startPrimePerTeam = 1500;

    [Description( "Amount of given to all heroes prime in second" )]
    public int giveWorldPrimeAmount = 2;

    [Description( "NaftaSpecForKill multipliers depending on hero group size" )]
    public List<float> multipliers = new List<float>();

    [Description( "Heroes' NaftaForKill override. Leave -1 if not used." )]
    public float naftaForKill = -1.0f;

    [Description("Heroes' NaftaForAssist override. Leave -1 if not used.")]
    public float naftaForAssist = -1.0f;

    [Description("Heroes' NaftaSpecForKill override. Leave -1 if not used.")]
    public float naftaSpecForKill = -1.0f;

    [Description("Heroes' TeamNaftaForPresence override. Leave -1 if not used.")]
    public float teamNaftaForPresence = -1.0f;

    [Description( "NaftaSpecForKill modifiers for level difference of hero and killed neutral creep")]
    public DBPtr<KillExperienceModifier> neutralKillExperienceModifier;

    public DBPtr<HeroNaftaParams> heroNaftaParams;

    public float awardSpecRange = 32.0f;
    public float awardTeamRange = 25.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class AdvMapObject
  {
    public DBPtr<GameObject> gameObject;

    [Description( "Offset from node" )]
    public Placement2 offset;

    [Description( "Owner player" )]
    public EPlayerID player = EPlayerID.None;

    [Description("Whether this object should lock map or not")]
    public bool lockMap = true;

    [Description( "Name for searching object in script" )]
    public string scriptName;

    [Description( "Name for searching object in script" )]
    public string scriptGroupName;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class ScriptArea
  {
    public string name;
    public Vec2 position;
    public float radius = 10.0f;
    public PF_GameLogic.DBAbility.ESpellTarget targetType = PF_GameLogic.DBAbility.ESpellTarget.All;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [IndexField( "key" )]
  public class ResourceDesc
  {
    public string key;
    public DBPtr<DBResource> resource;
  }

  [TypeId(0xEF91FBC0)]
  [UseTypeName("DICT")]
  public class DictionaryPreloadingResources : DBResource
  {
    public List<ResourceDesc> resources = new List<ResourceDesc>();
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class LoadingBackgroundImages
  {
    [Description("бэк лоадинг скрина")]
    public DBPtr<Render.DBRenderResources.Texture> back;

    [Description("логотип. будет выставлен по центру")]
    public DBPtr<Render.DBRenderResources.Texture> logo;
  }

  public class StatisticBackgoundImages
  {
    [Description("бэк текущей статистики. Во время боя")]
    public DBPtr<Render.DBRenderResources.Texture> normal;

    [Description("бэк текущей статистики. Победа")]
    public DBPtr<Render.DBRenderResources.Texture> win;

    [Description("бэк текущей статистики. Поражение")]
    public DBPtr<Render.DBRenderResources.Texture> loose;
  }

  [Custom("Social")]
  public class FWODVisualInfo : DBResource
  {
    [Description("Иконка первого вина для сессии большая")]
    public DBPtr<Render.DBRenderResources.Texture> icon;

    [Description("Иконка первого вина. Мелкая для замка")]
    public DBPtr<Render.DBRenderResources.Texture> iconSmall;

    [Description("тултип в замке")]
    public TextRef tooltip;

    [Description("тултип")]
    public TextRef sessionTooltip;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("ADMP")]
  [DBVersion(1)]
  public class AdvMap : DBResource
  {
    public DBPtr<AdventureCameraSettings> cameraSettings;

    public DBPtr<MinimapImages> minimapImages;

    public List<AdvMapObject> objects = new List<AdvMapObject>();

    public DBPtr<Terrain.DBTerrain.Terrain> terrain;
    public DBPtr<Sound.DBSound.SoundEnvironment> soundEnvironment;
    public DBPtr<LightEnvironment> lightEnvironment;
    public DBPtr<LightEnvironment> nightLightEnvironment;

    public BakedLighting bakedLighting;

    public List<PointLightInfo> pointLights = new List<PointLightInfo>();

    public List<ScriptArea> scriptAreas = new List<ScriptArea>();

    [FieldCategory("Objects height layer")]
    [DstFile("objectheight")]
    public string ObjectsLayerFileName = String.Empty;

    [DstFile("watermap")]
    public string waterMapFileName = string.Empty;

    [Description("Настройки звуков окружения на игровой карте с помощью текстуры.")]
    public SoundAmbienceMap ambienceMap;

    [Description("Map settings")]
    public DBPtr<AdvMapSettings> mapSettings;

    [Description( "Override full-screen post effect" )]
    public DBPtr<PostFXParams> postEffect;

    public DayNightSettings dayNightSettings;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0x146B6280 )]
  [UseTypeName( "WTRZ" )]
  [DBVersion( 0 )]
  public class AdvMapWaterZone : GameObject
  {
    public FlatSplineDesc area = new FlatSplineDesc();
  }

  [TypeId(0xEF924380)]
  [UseTypeName("CSPL")]
  public class AdvMapCameraSpline : GameObject
  {
    public List<Spline3DControlPointDesc> points;
    public int hight = 5;
    public bool SmoothStart = false;
    public float StartTime = 1.0f;
    public bool SmoothEnd = false;
    public float EndTime = 1.0f;
  }

  public class TriggerMarkerBinding
  {
      public string TriggerPoint = string.Empty;
      public List<string> MarkerPoints = new List<string>();
  }

  public class ScriptPolygonAreaPolygon
  {
    public string name = string.Empty;
    [NoCode]
    public Color color = new Color( 0, 192, 0, 0 );
    public List<int> indexes = new List<int>();
  }

  [TypeId( 0x9A9B7C40 )]
  [UseTypeName( "SPOL" )]
  public class ScriptPolygonArea : GameObject
  {
    public List<Vec2> points = new List<Vec2>();
    public List<ScriptPolygonAreaPolygon> polygons = new List<ScriptPolygonAreaPolygon>();
  }

  [Custom( "Social" )]
  public class AdvMapPlayerData
  {
    public DBPtr<Hero> hero;
    [Description( "Computer player nickname (use hero name if empty)" )]
    public TextRef nickname = new TextRef();
  }


  public class AdvMapHeroesOverrideData : DBResource
  {
    [Custom( "Social" )]
    [Description("Own hero - effective only in single player game")]
    public AdvMapPlayerData ownHero = new AdvMapPlayerData();

    [Description("Allies heroes")]
    public List<AdvMapPlayerData> allies;

    [Description("Enemies heroes")]
    public List<AdvMapPlayerData> enemies;
  }

  [Custom( "Social" )]
  public class AdvMapHeroesOverride : DBResource
  {
    [Description("Heroes override data for single player male")]
    public DBPtr<AdvMapHeroesOverrideData> singlePlayerMale;

    [Description("Heroes override data for single player female")]
    public DBPtr<AdvMapHeroesOverrideData> singlePlayerFemale;

    [Description( "Перемешать героев между игроками каждой из команд" )]
    public bool shuffleHeroesInTeam = false;
  }

  public class CreepAnnounce
  {
    public DBPtr<BaseCreepSpawner> spawner;
    public List<DBPtr<AdvMapCreep>> creeps = new List<DBPtr<AdvMapCreep>>();
  }

  public class CreepAnnounceList : DBResource
  {
    public List<CreepAnnounce> list = new List<CreepAnnounce>();
  }

  public class GlyphManagerParams : DBResource
  {
    [Description( "Кастомные параметры спавна глифов" )]
    public GlyphSettings settings = new GlyphSettings();

    [Description( "Кастомный список глифов" )]
    public DBPtr<GlyphsDB> glyphs = null;
  }


  [UseTypeName("ADMPSTTN")]
  public class AdvMapSettings : DBResource
  {
    [Description("Faction Creeps first spawn delay in seconds")]
    public int battleStartDelay = 10;

    [Description( "Towers vulnerability delay in seconds" )]
    public int towersVulnerabilityDelay = 0;

    [Description( "Custom battle start announcement icons and text" )]
    public BattleStartAnnouncementParams customBattleStartAnnouncement;

    public bool useCustomBattleStartAnnouncement = false;

    [Description("Show all heroes on loading screen")]
    public bool showAllHeroes = true;

    [Description("Force of the map")]
    public float force = 125.0f;

    [Custom("Social")]
    [Description("Минимальная необходимая мощь чтобы пойти героем на карту")]
    public float minRequiredHeroForce = 0;

    [Custom("Social")]
    [Description("Максимальная необходимая мощь чтобы пойти героем на карту")]
    public float maxRequiredHeroForce = 10000;

    [Custom("Social", "DBServer")]
    [Description("Включает возможность ухода в бой только группу из 5 человек")]
    public bool fullPartyOnly = false;

    [Description("Dictionary of preloading resources")]
    public DBPtr<DictionaryPreloadingResources> dictionary;

    [Description("Prime income settings")]
    public PrimeSettings primeSettings;

    [Description("Dialogs for the map")]
    public DBPtr<DialogsCollection> dialogsCollection;

    [Description("Hints for the map")]
    public DBPtr<HintsCollection> hintsCollection;

    [Description("Quests for the map")]
    public DBPtr<SessionQuestsCollection> questsCollection;

    [Description("Multiplier to the map force for training mode")]
    public float trainingForceCoeff = 1.0f;

    [Description("Script file to run after map loading")]
    public string scriptFileName = string.Empty;

    [Description("Overridden params")]
    public DBPtr<PF_GameLogic.DBGameLogic.HeroRespawnParams> heroRespawnParams;

    [Description("Binding of ScriptArea's Trigger and Marker points")]
    public List<TriggerMarkerBinding> triggerMarkerBinding = new List<TriggerMarkerBinding>();

    [Description("Neutral creeps in spawners whose killing to be announced")]
    public DBPtr<CreepAnnounceList> creepAnnounceList;
    
    [Description("Настройки голосования о сдаче. Если не указаны, то используются умолчания заданные для всех карт")]
    public DBPtr<VotingForSurrenderPerMission> votingForSurrender;

    [Description( "Overridden overtip settings" )]
    public DBPtr<AdventureTooltipParams> overrideTooltipParams;

    [Description( "Overridden minimap settings" )]
    public DBPtr<DBMinimap> overrideMinimapParams;

    [Description( "Overridden portal spell" )]
    public DBPtr<PF_GameLogic.DBTalent.Talent> overridePortalTalent;

    [Description( "Настройки спавна глифов. Если не указаны, то используются умолчания заданные для всех карт" )]
    public DBPtr<GlyphManagerParams> overrideGlyphSettings;

    [Description( "Настройки ботов. Если не указаны, то используются умолчания заданные для всех карт" )]
    public DBPtr<BotsSettings> overrideBotsSettings;

    [Description( "Show announcements in UI" )]
    public bool enableAnnouncements = true;

    [Description( "Enable portal standard hero talent" )]
    public bool enablePortalTalent = true;

    [Description( "Enable 'win game'  etc. script functions in multiplayer game" )]
    public bool enableAllScriptFunctions = false;

    [Description( "Enable/disable statistics logging" )]
    public bool enableStatistics = true;

    [Description( "If >= 0 - override creepLevelCap from AILogicParameters" )]
    public int creepLevelCap = -1;

    [Description( "При скольки героях одного клана на поднятых флагах рисуется эмблема клана" )]
    public int emblemHeroNeeds = 3;
  }

  [Custom("DBServer", "Social")]
  public enum EMapType
  {
    None,
    PvP,
    CTE,
    Training,
    Tutorial,
    Series,
    Cooperative
  }
    [Custom("Social")]
    public enum PartyMode
    {
        NotAllowed,
        OnlyAllies,
        AlliesAndEnemies
    }

  [UseTypeName("GSSTTN")]
  [Custom("DBServer")]
  public class GameSvcSettings : DBResource
  {
    [Description("AFK massage timer (sec). Counts after last player's command. 0 = disable.")]
    public int afkMessageTimer = 0;

    [Description("AFK disconnect timer (sec). Counts after last player's command. 0 = disable.")]
    public int afkDisconnectTimer = 0;

    [Description("Predefined timescale (0.1-10.0). Will be applied even if changing timescale is disabled on server.")]
    public float timeScale = 1.0f;
  }


  [UseTypeName("ADMPDSCR")]
  [IndexField("title")]
  public class AdvMapDescription : DBResource
  {
    [FieldCategory("Map title")]
    [Description("Имя карты")]
    [Custom( "Social" )]
    public TextRef title = new TextRef();
    

    [Description("Картики на экране загрузки. Логотип и Бэк")]
    public LoadingBackgroundImages loadingBackgroundImages;

    [Description("Картики текущей статистики. Показывается когда нету одной из комманд. Пока используется в кооперативе")]
    public StatisticBackgoundImages statisticBackgroundImages;
        
    [Description("Описание модификатора. Родная земля/Форпост итд")]
    public DBPtr<AdvMapModeDescription> modeVisualDescription;

    [Description("Иконка карты для отображения")]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [Custom("DBServer", "Social")]
    [FieldCategory( "MapType" )]
    [Description( "Тип карты, важно серверу. На основе этого поле выбирается алгоритм матчмейкинга: PVP, PVE, single-player etc" )]
    public EMapType mapType = EMapType.PvP;

    [Custom("Social")]
    [Description("Карта для режима Практики")]
    public DBPtr<AdvMapDescription> mapWithBots;

    [Custom("Social")]
    [Description("Настройки для группы. NotAllowed - нельзя группой, OnlyAllies - только с напарниками, AlliesAndEnemies - напарники и соперники (ДБ)")]
    public PartyMode PartyMode = PartyMode.AlliesAndEnemies;

    [Custom("Social")]
    [Description("Надо ли запрашивать accept на нахождение игры. По умолчанию - отключено")]
    public bool acceptNeeded = false;

    [Custom( "Social" )]
    [FieldCategory("Map description")]
    [Description("тултип для карты")]
    public TextRef description = new TextRef();

    public DBPtr<AdvMap> map;

    [Description("Optional heroes override data")]
    [Custom( "Social" )]
    public DBPtr<AdvMapHeroesOverride> heroesOverride;

    [Description("Настройки матчмейкинга, специфичные для карты; Если не указаны, то на этой карте включится тестовый матчмейкинг!")]
    [Custom("DBServer", "Social")]
    public DBPtr<MapMMakingSettings> matchmakingSettings;

    [Description("Число игроков за одну сторону, например, 5")]
    [Custom("DBServer", "Social")]
    public int teamSize = 5;

    [Description("необходимое количество игроков для карты. Нужно для кооператива. по дефолту -1")]
    [Custom("DBServer", "Social")]
    public int minTeamSize = -1;


    [Description("максимальный размер неполной парти на карте. если оставить -1 будет совпадать с максимальным количеством игроков за одну сторону")]
    [Custom("DBServer", "Social")]
    public int maxUncompleteTeamSize = -1;

    [Description("Допустим ли такой режим/карта на боевом сервере")]
    [Custom("DBServer")]
    public bool productionMode = false;

    [Custom("DBServer", "Social")]
    [Description("Map settings")]
    public DBPtr<AdvMapSettings> mapSettings;

    [Description("Roll settings")]
    [Custom( "DBServer", "Social" )]
    public DBPtr<ModeRollSettings> rollSettings;

    [Description( "Guard Mode roll settings" )]
    [Custom( "DBServer", "Social" )]
    public DBPtr<ModeRollSettings> guardRollSettings;

    [Description("Scoring table (leave empty to use default scoring)")]
    public DBPtr<ScoringTable> scoringTable;

    [Description( "Вес победы. Те кол-во очков победы, которое дается за победу. Например для Форпоста=0.5, для Пограничья=1.0" )]
    [Custom( "Social" )]
    public float victoryPoint = 1.0f;

    [Description( "Группа для первого выигрыша за день. Если бонус не положен - пустая строка. Чтобы был бонус один для нескольких карт (например драговальд и пограничье), строка должна совпадать" )]
    [Custom( "Social" )]
    public string FWODGroup;

    [Description("Информация для отображение FWOD в сессии и замке. Устанавливается на карту")]
    [Custom("Social")]
    public DBPtr<FWODVisualInfo> FirstWinVisualInfo;

    [Description( "Можно ли использовать на этой карте скины героев" )]
    [Custom("Social")]
    public bool canUseSkins = true;

    [Description( "Доступны ли ботам скины на этой карте" )]
    [Custom("Social")]
    public bool botsUseSkins = false;

    [Description("Количество игроков с одной стороны из одного клана, чтобы  бой получил статус клановый")]
    [Custom("DBServer")]
    public int minimalGuildFightTeam = 3;

    [Description("Map-specific game server settings")]
    [Custom("DBServer")]
    public DBPtr<GameSvcSettings> gameSvcSettings;

    [Description("Тайм-аут для фичи Играть в том же составе. Если 0, опция блокируется.")]
    [Custom("DBServer")]
    public int playSameTeamTimeOut = 30;

    [Description("Доступна ли карта для игры ливерам (True-доступна,False-недоступна)")]
    [Custom("Social")]
    public bool AvailableForLeavers = true;

    [Description("Будут ли даваться очки дезертира за покинутую игру на этой карте  (True-будут,False-небудут)")]
    [Custom("Social")]
    public bool PlusPointForLeave = false;

    [Description("Будут ли сниматься очки дезертира за сыгранную игру до конца на этой карте (True-будут,False-небудут)")]
    [Custom("Social")]
    public bool MinusPointsPerFullGame = false;
  }
}
