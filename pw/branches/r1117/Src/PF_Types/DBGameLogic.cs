//#include "../Types/Render.cs"
//#include "DBTalent.cs"
//#include "DBConsumable.cs"
//#include "DBUnit.cs"
//#include "DBAbility.cs"
//#include "DBHeroRanks.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using PF_GameLogic.DBAdvMap;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBConsumable;
using Scene.DBSceneBase;
using PF_GameLogic.DBHeroRanks;

namespace PF_GameLogic.DBGameLogic
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "UNTP" )]
  [DBVersion( 3 )]
  public class UnitTargetingParameters : DBResource
  {
    [FieldCategory( "Targeting by type" )]
    [Description( "Table of target types weights" )]
    [EnumArray( typeof( EUnitType ) )]
    public List<float> unitTargetWeight = new List<float>();

    [FieldCategory( "Targeting by type" )]
    [Description( "Multiplier for the common weights table" )]
    public float unitTypeTableWeight = 0.0f;

    [FieldCategory( "Targeting by range" )]
    [FloatMinMax( 0.0f, 1.0f )]
    public float weightMaximumRangePersent = 0.0f;

    [FieldCategory( "Targeting by range" )]
    public float rangeWeight = 0.0f;

    [FieldCategory( "Targeting attackers" )]
    public float attackerMeWeight = 0.5f;

    [FieldCategory( "Targeting attackers" )]
    [Description( "Table of weights of allied hero attackers" )]
    [EnumArray( typeof( EUnitType ) )]
    public List<float> attackerHeroWeight = new List<float>();

    [FieldCategory( "Targeting attackers" )]
    [Description( "Multiplier for allied hero attackers weights table" )]
    public float attackerHeroTableWeight = 1.0f;

    [Description( "Weight of summon whose master attacks allied hero. This weight applies instead of unitTargetWeight and attackerHeroWeight. Leave 0 in a case where such logics is not required." )]
    public float attackerHeroSummonWeight = 0.0f;

    [FieldCategory( "Targeting towers" )]
    public float attackerTowerWeight = 8f;

    [FieldCategory( "Targeting attackers" )]
    public float attackerMasterWeight = 2f;

    [FieldCategory( "Targeting attackers" )]
    public float attackerAllyWeight = 0.2f;

    [FieldCategory( "Targeting common" )]
    [Description( "Current target weights table" )]
    [EnumArray( typeof( EUnitType ) )]
    public List<float> currentTargetWeight = new List<float>();

    [Description( "Multiplier for current target weights table" )]
    public float currentTargetTableWeight = 1.0f;

    [FieldCategory( "Targeting common" )]
    public float targetRevisionTime = 7.0f;

    [FieldCategory( "Targeting common" )]
    public float healthWeight = 0.3f;

    [FieldCategory( "Targeting master" )]
    public float masterTargetWeight = 0f;

    [FieldCategory( "Targeting common" )]
    [Description( "Weight of target, attacked by talent. Added to total weight." )]
    public float talentAttackWeight = 0.0f;

    [FieldCategory( "Targeting common" )]
    [Description( "Weight of target, attacked by autoattack. Added to total weight." )]
    public float autoAttackWeight = 0.0f;

    [FieldCategory( "Targeting common" )]
    [Description( "Weight of target, attacked out of aggroRange" )]
    public float OutOfAggroWeight = 0.0f;

    [FieldCategory( "Targeting common" )]
    [Description( "Weight of target if at least one ally within screamRange has the same target" )]
    public float allyTargetWeight = 0.0f;

    [Description("Вес агрессивного нейтрала")]
    public float aggressiveNeutralWeight = 0.0f;

    [Description( "Вес агрессивного нейтрала который бьёт союзного героя. Предыдущий вес в этом случае не применяется" )]
    public float aggressiveNeutralAttackingHeroWeight = 0.0f;

    [FieldCategory( "Targeting common" )]
    [Description( "Custom weight (formula)" )]
    public ExecutableFloatString customWeight = new ExecutableFloatString( "0.0f" );

    [FieldCategory( "Targeting common" )]
    [Description( "Max time in seconds from attack, which may pass and it will be still considered in target weight calculation. -1 means no time check." )]
    public float maxTimeFromAttack = -1.0f;

    [FieldCategory( "Ranges" )]
    public float targetingRange = 15.0f;

    [FieldCategory( "Ranges" )]
    public float chaseRange = 30.0f;

    [FieldCategory( "Ranges" )]
    public float aggroRange = -1.0f;

    [Description( "Unit ignores targets attacked by friendly units same as this one" )]
    public bool ignoreSiblingTarget = false;

    [Description( "Is the unit is a stationary summon. Don't check ranges to master." )]
    public bool isStationarySummon = false;

    [Description( "Don't select target that damages the unit and ignore force assigning of targets. Select targets only by weights." )]
    public bool onlyAutoTargeting = false;

    [FieldCategory( "Targeting common" )]
    [Description( "Weight of target hero that attacks allied hero." )]
    public float attackerNearbyHeroWeight = 0.0f;

    [FieldCategory( "Ranges" )]
    public float nearbyRange = 0.0f;

    [FieldCategory("Targeting common")]
    [Description("Long Suspend Timeout(in seconds)")]
    public float longSuspendTimeout = 0.3f;

    [FieldCategory("Targeting common")]
    [Description("Sort Suspend Timeout(in seconds)")]
    public float sortSuspendTimeout = 0.0f;

  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "UNLP" )]
  [DBVersion( 2 )]
  public class UnitLogicParameters : DBResource
  {
    [FieldCategory( "Logic" )]
    [DescriptionAttribute( "Default stats values" )]
    [Custom( "Social" )]
    public DBPtr<StatsContainer> defaultStats;

    //////////////////////////////////////////////////////////////////////////
    [FieldCategory( "Logic" )]
    [DescriptionAttribute( "Targeting parameters" )]
    public DBPtr<UnitTargetingParameters> targetingPars;

    ////////////////////////////////////////////////////////////////  
    [FieldCategory( "Ranges" )]
    public float screamRange = 20.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "UNDP" )]
  [DBVersion( 0 )]
  public class UnitDeathParameters : DBResource
  {
    ///////////////////////////////////////////////////////////////
    [FieldCategory( "Corpses" )]
    [DescriptionAttribute( "Time offset in seconds then need to start put fall throught terrain after unit death" )]
    public float fallOffset = 4.5f;

    [FieldCategory( "Corpses" )]
    [DescriptionAttribute( "Speed of dead unit fall throught terrain (m/s)" )]
    public float fallSpeed = 0.5f;

    [FieldCategory( "Corpses" )]
    [DescriptionAttribute( "Time offset in seconds then need to remove unit from world after death" )]
    public float deathTime = 5.0f;

    [FieldCategory( "Corpses" )]
    [DescriptionAttribute( "Time offset in seconds then need to remove unit from world after unsummon" )]
    public float unsummonTime = 0.5f;

    [FieldCategory( "Corpses" )]
    [Description( "Time offset in seconds after logical death of the unit before visibility will be removed" )]
    public float observeOffset = 5.0f;

    [FieldCategory( "Corpses" )]
    [DescriptionAttribute( "Time offset in seconds then need play unit die effect after diying animation ends" )]
    public float effectOffset = 0.5f;

    [FieldCategory( "Dead Effect" )]
    public DBPtr<EffectBase> effect;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "UNTL" )]
  [Custom( "Social" )]
  public class UnitsLogicParameters : DBResource
  {
    [EnumArray( typeof( EUnitType ) )]
    public List<DBPtr<UnitLogicParameters>> unitParameters = new List<DBPtr<UnitLogicParameters>>();
  }
  [Custom( "Social" )]
  public enum EGender
  {
    Male,
    Female
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ETeamColorID
  {
    Team,
    Hero1,
    Hero2,
    Hero3,
    Hero4,
    Hero5
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion( 1 )]
  public class TeamColors
  {
    [EnumArray( typeof( ETeamColorID ) )]
    public List<HDRColor> teamColors = new List<HDRColor>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "TCS" )]
  [DBVersion( 1 )]
  public class TeamsColoringScheme : DBResource
  {
    public TeamColors teamA = new TeamColors();
    public TeamColors teamB = new TeamColors();
  }

  public enum EGlyphSpawnMode
  {
    RandomWeight,
    Ordered
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion( 0 )]
  public class GlyphSettings
  {
    public float minNormalSpawnDelay      = 50.0f;
    public float maxNormalSpawnDelay      = 150.0f;

    public float minAfterPickupSpawnDelay = 50.0f;
    public float maxAfterPickupSpawnDelay = 240.0f;

    public float spawnAttemptDelayDecrease = 50.0f;

    [Description( "Максимальное количество глифов на карте (во всех спавнерах)" )]
    public int maxInstances = 2;

    public EGlyphSpawnMode spawnMode = EGlyphSpawnMode.RandomWeight;
  }

  public class TurretParams
  {
    [Description( "Turret turn speed (angles per second)" )]
    public float turretAngleSpeed = 100.0f;

    [Description( "Turret acceleration (angles per squared second)" )]
    public float turretAngleAcceleration = 25.0f;

    [FloatMinMax( 0, 360 )]
    [Description( "Turret rotation tolerance (angles)" )]
    public float turretRotaionTolerance = 5.0f;

    public float turretLastAngleResetDelay = 2.0f;
  }


  public class HeroStatisticsParams
  {
    //for now 3 mins. 03.12.2010 - from now 1 min.
    public float timeSlicePeriod = 60;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class CreepsLevelUpInfo
  {
    public float interval  = 300.0f;
    public int increment = 1;
  }

  public class CreatureHappyStateParams
  {
    [Description( "Процент ''счастливых'' крипов: [0..1]" )]
    public float happyCreaturesPercent = 0.5f;

    [Description( "Сколько секунд крип должен отдыхать от ''счастья''" )]
    public float minRestTime = 0.5f;

    [Description( "Раз в сколько секунд проверяем процент ''счастливых'' крипов" )]
    public float happyCheckTick = 1.0f;
  }

  public class ExpoModeParams
  {
    public DBPtr<StatsEnhancersContainer> statsEnhancers;
    public float minHeroLife = 0.0f;
    public ExecutableFloatString damageModifier = new ExecutableFloatString( "1.0f" );
  }

  public class AbilityAndDamageScalingParams
  {
    public float abilityScaleStatLeft = 50.0f;
    public float abilityScaleStatRight = 160.0f;
    public float abilityScaleLifeLeft = 600.0f;
    public float abilityScaleLifeRight = 3350.0f;
    public float abilityScaleEnergyLeft = 600.0f;
    public float abilityScaleEnergyRight = 3350.0f;
    public float damageScaleStatLeft = 50.0f;
    public float damageScaleStatRight = 223.0f;
    public float damageScaleLifeLeft = 600.0f;
    public float damageScaleLifeRight = 4683.0f;
    public float damageScaleEnergyLeft = 600.0f;
    public float damageScaleEnergyRight = 4683.0f;
  }

  public enum TeamForceCalcMethod
  {
    Minimum,
    Average,
  }

  [Custom( "Social" )]
  [DBVersion( 2 )]
  public class ForceParameters : DBResource
  {
    [Description( "Таблица модификаторов ТУРа неклассовых талантов для вычисления Мощи" )]
    [EnumArray( typeof( ETalentLevel ) )]
    public List<float> talentLevelForceModifiers = new List<float>();

    [Description( "Таблица модификаторов РАРов для вычисления Мощи" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<float> talentRarityForceModifiers  = new List<float>();

    [Description("Таблица добавляемых значений РАРов для вычисления Мощи")]
    [EnumArray(typeof(ETalentRarity))]
    public List<float> talentRarityForceSummand = new List<float>();

    [Description( "Таблица модификаторов ТУРа классовых талантов для вычисления Мощи" )]
    [EnumArray( typeof( ETalentLevel ) )]
    public List<float> classTalentLevelForceModifiers = new List<float>();

    [Description( "% увеличения бюджета за звезду" )]
    public float talentForceBonusPerStar = 5.0f;

    [Description("% увеличения бюджета за звезду для классовых талантов")]
    public float classTalentForceBonusPerStar = 5.0f;

    [Description( "% от общего Суммарного бонуса" )]
    [EnumArray( typeof( ETalentLevel ) )]
    public List<float> talentLevelBonusPercent = new List<float>();

    [Description( "Базовая мощь героя" )]
    public float baseHeroForce = 0.0f;

    [Description( "Стандартная мощь для обобщённого героя" )]
    public float defaultBaseForce = 100.0f;

    [Description( "Мощь от единицы мастерства" )]
    public float masteryPointForce = 1.0f;

    [Description( "Бонус от мощи к статам" )]
    public float statBonusByForce = 1.27f;

    [Description( "Дефолтовый бонус к статам" )]
    public float defaultStatBonus = 252.0f;

    [Description( "Способ вычисления мощи команды героев" )]
    public TeamForceCalcMethod teamForceCalcMethod = TeamForceCalcMethod.Minimum;

    [Description( "Множитель на отношение мощи команды героев к мощи карты" )]
    public float mapHabitantsStatsMultiplier = 0.55f;

    [Description( "Множитель на отношение мощи ботов к мощи карты" )]
    public float trainingBotsStatsMultiplier = 0.6f;

    [Description( "Коэфицент для регулировки влияния бюджета на мощь" )]
    public float talentForceModifier = 1.1f;

    [Description( "Для Series карт. Множитель на отношение мощи героя к мощи карты" )]
    public float seriesMapHabitantsStatsMultiplier = 0.7f;

    [Description("Ограничение на мощь команды")]
    public float maxHeroForce = 0.0f;
  }

  public class OvertimeRespawnParams
  {
    [Description( "Session overtime (in minutes), after which hero respawn time will increase" )]
    public float overtime = 25.0f;

    [Description( "Hero respawn delay for each minute of overtime (in seconds)" )]
    public float respawnDelayForOvertime = 1.5f;
  }


  [Custom( "Social" )]
  public class DBLevelToExperience : DBResource
  {
    public List<int> Levels;
  }

  [Custom( "Social" )]
  public class DBRatingToFame : DBResource
  {
    public List<DBFameRatingPair> Ratings;
  }

  [Custom( "Social" )]
  public class DBFameRatingPair
  {
    public int fameLevel;
    public int rating;
  }

  public class KillTimeIntervals
  {
    public float creepKillInterval = 0.5f;
    public float buildingKillInterval = 2.0f;
    public float heroKillerDeadInterval = 5.0f;
    public float heroKillDamageInterval = 10.0f;
  }

  [IndexField( "caption" )]
  public class TalentGroup
  {
    [NoCode]
    public string caption = string.Empty;
    public TextRef name = new TextRef();
    public TextRef description = new TextRef();
    public float cooldown = 15.0f;
    public List<DBPtr<Talent>> talents = new List<DBPtr<Talent>>();
  }

  [UseTypeName( "TGRP" )]
  public class TalentGroupList : DBResource
  {
    public List<TalentGroup> groups = new List<TalentGroup>();
  }

  [IndexField( "caption" )]
  public class ConsumableGroup
  {
    [NoCode]
    public string caption = string.Empty;
    public TextRef name = new TextRef();
    public TextRef description = new TextRef();
    public float cooldown = 1.0f;
    public List<DBPtr<Consumable>> consumables = new List<DBPtr<Consumable>>();
  }

  [UseTypeName( "CGRP" )]
  public class ConsumableGroupList : DBResource
  {
    public List<ConsumableGroup> groups = new List<ConsumableGroup>();
  }

  [Custom( "Social" )]
  [UseTypeName( "TKLIST" )]
  public class TalentKitList : DBResource
  {
    public List<DBPtr<TalentKit>> kits = new List<DBPtr<TalentKit>>();
  }
  [Custom( "Social" )]
  [UseTypeName( "TPKLIST" )]
  public class TalentPackList : DBResource
  {
    public List<DBPtr<TalentPack>> packs = new List<DBPtr<TalentPack>>();
  }

  public class CommonSummonParameters
  {
    public float primarySummonEscortDistance = 4.5f;
    public float secondarySummonEscortDistance = 7.0f;
    public float petEscortDistance = 2.5f;
  }

  [UseTypeName( "HRESP" )]
  public class HeroRespawnParams : DBResource
  {
    [Description( "Множитель для формулы задержки времени воскрешения (умножается на уровень героя)" )]
    public float heroRespawnDelayMultiplier = 5.0f;

    [Description( "Минимальное время возрождения героя. Значение level * heroRespawnDelayMultiplier * reviveTimeScale  не может быть меньше указанного в heroMinRespawnTime" )]
    public float heroMinRespawnTime = 6.0f;

    [Description( "Базовое время возрождение к которому будут добавлятся все остальные модификаторы" )]
    public float heroBaseRespawnTime = 5.0f;

    public OvertimeRespawnParams overtimeRespawnParams = new OvertimeRespawnParams();
  }

  [UseTypeName("BTP")]
  [DBVersion(1)]
  public class BehaviourTrackerParams : DBResource
  {
    [Description("Время (сек) ожидания после начала игры")]
    public int idleTime = 2 * 60;

    [Description("Игрок получает 'зону риска', если в течение этого времени (сек) он не принимал участия в игре")]
    public int goodActionTimeout = 3 * 60;

    [Description("Игрок получает 'зону риска', если в течение этого времени (сек) он, находясь в зуме, не передал ни одного свитка союзнику")]
    public int goodZumaActionTimeout = 5 * 60;

    [Description("Игрок получает 'зону риска' и считается фидером, если его герой умер указанное количество раз в течение @feederDeathTime")]
    public int feederDeathCount = 3;

    [Description("Игрок получает 'зону риска' и считается фидером, если его герой умер @feederDeathCount раз в течение указанного времени (сек)")]
    public int feederDeathTime = 4 * 60;

    [Description("Поведение игрока считается действительно неспортивным, если он собрал столько (или больше) жалоб о неспортивном поведении от союзников")]
    public int badBehaviourComplaintsThreshold = 2;

    [Description("Количество репорта по причине оскорбления, после которых по окончанию сессии будем наказываеть мьютом")]
    public int insultComplaintsThreshold = 2;
    
    [Description("Общее количество сообщений в чате от игрока мы планируем наказывать игрока мьютом, которых по окончанию сессии будем наказываеть мьютом")]
    public int autoMuteMinMessage = 0;

    [Description("Общее количество сообщений в чате за время AutoMuteTimeLimit, после которых мы считаем сообщения спамом")]
    public int autoMuteMessagePerTime = 3;

    [Description("Время, за которое мы проверяем количество сообщений AutoMuteMessagePerTime")]
    public int autoMuteTimeLimit = 10;

    [Description("Длина сообщения, выше которой сообщение считается плохим и учитывается системой автомьюта")]
    public int autoMuteMessageLength = 50;

  }

  [UseTypeName( "AILP" )]
  [DBVersion( 9 )]
  public class AILogicParameters : DBResource
  {
    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Misc" )]
    [EnumArray( typeof( EFaction ) )]
    public List<TextRef> teamsNames = new List<TextRef>();

    [FieldCategory( "Misc" )]
    [Description( "Game object, used for chests with artifact" )]
    public DBPtr<SingleStateObject> chestGameObject;

    [FieldCategory( "Misc" )]
    [Custom("Social")]
    public List<DBPtr<ConditionFormula>> conditionFormulas = new List<DBPtr<ConditionFormula>>();

    [FieldCategory( "Misc" )]
    [Custom( "Social" )]
    public DBPtr<UnitConstantsContainer> globalConstants;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public DBPtr<HeroRespawnParams> heroRespawnParams;

    [Description( "Время на проигрывание анимации воскрешения. Используется в формуле вычисления задержки respawnDelay = level * heroRespawnDelayMultiplier * reviveTimeScale - heroAdvanceRespawnTime" )]
    public float heroAdvanceRespawnTime = 1.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float baseRedeemCost = 100.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float redeemCostPerLevel = 10.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float redeemCostrecalculateTime = 3.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float followRange = 4.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float pickupItemRange = 2.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Heroes" )]
    public float killAwardPartyMultiplier = 1.0f;

    [FieldCategory( "Heroes" )]
    public float maxTrueSightRange = 15.0f;

    [Description( "Range to target check for channeling applicator uses this multiplier" )]
    public float channelingAbilityRangeMultiplier = 1.2f;
    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Logic" )]
    public float heroScreamDelay = 3.0f;

    [FieldCategory( "Logic" )]
    [DescriptionAttribute( "Global cooldown time for all abilities" )]
    public float globalCooldownTime = 1.0f;

    [FieldCategory( "Corpses" )]
    [Description( "Life time in seconds of skeleton (for moving unit only)" )]
    public float skeletonLifeTime = 10.0f;

    [FieldCategory( "Logic" )]
    public GlyphSettings glyphSettings = new GlyphSettings();

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Statistics" )]
    [Description( "Within this time assist actions will be accounted while evaluating assistants" )]
    public float assistAccountTime = 30.0f;

    [Description( "Time intervals settings for kills counting" )]
    public KillTimeIntervals killTimeIntervals = new KillTimeIntervals();

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Creeps" )]
    public int creepsWavesDelay = 30;

    [FieldCategory( "Creeps" )]
    public int creepLevelCap = 30;

    [FieldCategory( "Creeps" )]
    public CreepsLevelUpInfo creepsLevelUpInfo;

    [FieldCategory( "Creeps" )]
    [EnumArray( typeof( EStat ) )]
    public List<float> quarterDestroyStatsMultipliers = new List<float>();

    [FieldCategory( "Creeps" )]
    [Description( "Время, по исченеии которого крип телепортируется на спавнер, если он застрял где-то" )]
    public float movingTimerBlock = 3.0f;

    [FieldCategory( "Units" )]
    public CreatureHappyStateParams creatureHappyStateParams;

    public CommonSummonParameters commonSummonParameters;

    [FieldCategory( "Units" )]
    [Description( "Unit rotation speed (degrees per second) " )]
    public float rotationSpeed = 1000;

    [FieldCategory( "Units" )]
    [Description( "Unit vertical rotation speed (degrees per second) " )]
    public float rotationSpeedZ = 100;

    public TurretParams towerTurretParams = new TurretParams();

    [EnumArray( typeof( ETeamID ) )]
    public List<TurretParams> mainBuildingTurretParams = new List<TurretParams>();

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Expand Nature" )]
    public int expandNatureSegmentRation = 1;

    [FieldCategory( "Expand Nature" )]
    public float expandNatureGlyphsLifeTime = 30.0f;

    [FieldCategory( "Expand Nature" )]
    public float expandNatureGlyphsVisibilityRadius = 10.0f;

    [FieldCategory( "Expand Nature" )]
    public DBPtr<GameObject> expandNatureGlyphGameObject;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Buildings deny" )]
    public DBPtr<Ability> buildingsDenyAbility;

    [FieldCategory( "Buildings deny" )]
    public float buildingsDenyMinHealth;

    [FieldCategory( "Buildings deny" )]
    [Description( "Penalty of experience, given from tower if denied (in percents)" )]
    public float buildingsDenyExperiencePenalty = 0.5f;

    [FieldCategory( "Buildings deny" )]
    [Description( "Penalty of nafta, given from tower if denied (in percents)" )]
    public float buildingsDenyNaftaPenalty = 0.0f;

    [FieldCategory( "Buildings deny" )]
    [Description( "Penalty of nafta, given from tower if denied (in percents)" )]
    public float buildingsDenyNaftaSpecPenalty = 0.0f;

    [FieldCategory( "Buildings deny" )]
    [Description( "Penalty of team nafta, given from tower if denied (in percents)" )]
    public float buildingsDenyTeamNaftaPenalty = 0.5f;

    [FieldCategory( "Buildings" )]
    public DBPtr<Ability> buildingsAbilityA;

    [FieldCategory( "Buildings" )]
    public DBPtr<Ability> buildingsAbilityB;

    [FieldCategory( "Buildings" )]
    public float buildingsMinHealthExplosionPercent = 80;

    [FieldCategory( "Buildings" )]
    public float buildingsFragEffectProbability = 0.2f;

    [FieldCategory( "Buildings" )]
    [Description( "Raise a flag ability" )]
    public DBPtr<Ability> raiseFlagAbility;

    [FieldCategory( "Talents" )]
    [Description( "Max range from shop, then male hero can to activate talents" )]
    public float talentsBuyRange = 15.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Talents" )]
    public DBPtr<TalentsSet> defaultTalentsSet;

    //////////////////////////////////////////////////////////////////////////
    [FieldCategory( "Talents" )]
    [Custom( "Social" )]
    public float talentBaseStatBudget = 480.0f;

    //////////////////////////////////////////////////////////////////////////
    [FieldCategory( "Talents" )]
    [Description( "Базовая стоимость от уровня" )]
    [Custom("Social")]
    [EnumArray( typeof( ETalentLevel ) )]
    public List<int> talentNaftaCostByLevel = new List<int>();

    //////////////////////////////////////////////////////////////////////////
    [FieldCategory( "Talents" )]
    [Description( "Ценность таланта при выдаче" )]
    [Custom( "DBServer" )]
    [EnumArray( typeof( ETalentRarity ) )]
    public List<int> talentVendorCostByRarity = new List<int>();


    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Interface" )]
    [Description( "Time for pause in seconds" )]
    public float pauseSeconds = 300.0f;

    ////////////////////////////////////////////////////////////////
    [FieldCategory( "Derivate Stats" )]
    [Custom( "Social" )]
    public DBPtr<DerivativeStatsContainer> derivativeStats;

    public DBPtr<StatsBudgetContainer> statsBudget;
    [Custom( "Social" )]
    public DBPtr<ForceParameters> forceParameters;

    public DBPtr<TalentGroupList> talentGroups;

    public DBPtr<ConsumableGroupList> consumableGroups;

    [Custom( "Social" )]
    public DBPtr<TalentKitList> talentKits;
    [Custom( "Social" )]
    public DBPtr<TalentPackList> talentPacks;

    ////////////////////////////////////////////////////////////////
    [Description( "Energy damage reduction formula" )]
    public ExecutableFloatString energyDamageReduction = new ExecutableFloatString( "0.0" );
    [Description( "Physical damage reduction formula" )]
    public ExecutableFloatString physicalDamageReduction = new ExecutableFloatString( "0.0" );

    ////////////////////////////////////////////////////////////////
    public HeroStatisticsParams heroStatisticsParams;

    public ExpoModeParams expoModeParams = new ExpoModeParams();

    public AbilityAndDamageScalingParams abilityAndDamageScalingParams = new AbilityAndDamageScalingParams();

    [Description( "таблица показывающая скольо нужно экспы герою чтобы достичь левела в замке" )]
    public DBPtr<DBLevelToExperience> levelToExperienceTable;

    public DBPtr<BotsSettings> botsSettings;

    [FieldCategory( "WarFog" )]
    [Description( "Defines default time for removing WarFog around attacker after dispatch delivery to target (seconds)." )]
    public float warFogRemoveTime = 0.4f;

    [FieldCategory( "WarFog" )]
    [Description( "Defines default radius for removing WarFog around attacker after dispatch delivery to target (meters)." )]
    public float warFogRemoveRadius = 4.0f;

    [FieldCategory( "MaxCreepsCount" )]
    [Description( "Defines a maximum number of creeps that can be on map at the same time." )]
    public int maxCreepsCount = 256;


    public DBPtr<Talent> portal;
    
    [Custom( "DBServer", "Social" )]
    public DBPtr<HeroRanks> heroRanks;

    [Description( "При скольки героях одного клана на поднятых флагах рисуется эмблема клана" )]
    public int baseEmblemHeroNeeds = 3;

    public DBPtr<BehaviourTrackerParams> behaviourTrackerParams;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [FactoryBase( "Construct", "PF_Minigames::IMinigamesMain" )]
  public class MinigamesBasic : DBResource
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName( "CHLP" )]
  public class ChatLogicParameters : DBResource
  {
    [Description( "Time after that the chat message will begin to disappear." )]
    public int timeBeforeDisappearing;

    [Description( "The duration of chat message disappearing time." )]
    public int disappearingTime;

    [Description( "Chat background opacity WITHOUT mouse over. Minimal opacity = 0.0, maximal opacity = 1.0" )]
    public float backgroundOpacityPermanent;

    [Description( "Chat background opacity WITH mouse over. Minimal opacity = 0.0, maximal opacity = 1.0" )]
    public float backgroundOpacityMotion;

    [Description( "UI channel text style" )]
    public string channelStyle;

    [Description( "UI nickname text style" )]
    public string nicknameStyle;

    [Description( "UI message text style" )]
    public string messageStyle;
  }

  [Custom( "DBServer" )]
  public enum BillingServicesStart
  {
    //TODO: сделать нумерацию сервисов ImpulseBuffs/GeneralServices с использованием BillingServicesStart
    Impulses = 100, //Unused
    Generic = 1000, //Unused
    Rewards = 2000,
  }

  public enum ImpulseBuffs
  {
    Buff_Healing,
    Buff_GetMana,
    Buff_Cleanising,
    Buff_Rising,
    Buff_Invulnerability,
    Buff_Blast,
    Buff_Speed,
    Buff_Help,
    Buff_Gratitude1,
    Buff_Gratitude2,
    Buff_Resurrection,
  }

  public enum GeneralServices
  {
    ZZBoost,
  }

  [Custom( "DBServer" )]
  public enum ZZRewards
  {
    Victory,
  }

  [Custom( "DBServer" )]
  public class BuyServiceCost
  {
    [DescriptionAttribute( "Cost of service in zzgold." )]
    public int goldCost = 1;
  }

  [TypeId( 0xF994BC9 )]
  [DBVersion( 2 )]
  [UseTypeName( "CIBC" )]
  [Custom( "DBServer" )]
  public class BuyServicesContainer : DBResource
  {
    [EnumArray( typeof( GeneralServices ) )]
    public List<BuyServiceCost> services;

    [EnumArray( typeof( ImpulseBuffs ) )]
    public List<BuyServiceCost> buffs;

    [EnumArray( typeof( ZZRewards ) )]
    public List<BuyServiceCost> rewards;
  }

  [UseTypeName( "BOTS" )]
  public class BotsSettings : DBResource
  {
    [Description( "Если % маны опуститься ниже, то используем поушен" )]
    public float manaUsePotionThreshold = 0.5f;
    [Description( "Если % жизни опуститься ниже, то используем поушен" )]
    public float healthUsePotionThreshold = 0.5f;
    [Description( "Наименьшее количество денег с которым бот пойдет в магазин" )]
    public int minShoppingMoney = 100;

    [Description( "Максимальное кол-во бутылочек жизни, которое может купить бот" )]
    public int maxHealthPotion = 2;
    [Description( "Максимальное кол-во бутылочек маны, которое может купить бот" )]
    public int maxManaPotion = 1;
    [Description( "Список героев, которым не покупать бутылки маны" )]
    public List<DBPtr<Hero>> doNotBuyMana;

    [Description( "Время в секундах после которого боты расходятся по лайнам" )]
    public int timeToGo = 45;

    [Description( "Боты ходят только по миду" )]
    public bool midOnly = false;

    [Description( "Enable/disable AI for bots" )]
    public bool enableBotsAI = true;

    [Description( "Время в секундах после которого боты будут телепортиться" )]
    public int timeToTeleport = 180;

    [Description( "Life fraction value to retreat to base" )]
    public float healthFractionToRetreatToBase = 0.1f;
    [Description( "Life absolute value to retreat to base" )]
    public float healthToRetreatToBase = 60.0f;
    [Description( "Distance along road to run away from attacking tower" )]
    public float escapeTowerDistance = 20.0f;
    [Description("Life fraction value to move back to front")]
    public float healthFractionToMoveToFront = 0.8f;

    [Description( "Distance to follow unit regardless to attacking units" )]
    public float forcedFollowRange = 20.0f;
  }

}