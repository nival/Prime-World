//#include "../Types/UI.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBConsumable;
using PF_GameLogic.DBUnit;
using Render.DBRender;
using Render.DBRenderResources;
using Scene.DBScene;
using Scene.DBSceneBase;
using UI.DBUI;

namespace PF_Minigames.DBEasel
{
  /// <summary>
  /// Common color data types
  /// </summary>
  public enum EColor
  {
    black,
    blue,
    green,
    red,
    white,
    cyan,
    yellow,
    magenta,
    any
  }

  public enum EEaselRoundStatus
  {
    Uninitialized,
    Incomplete,
    Won,
    Failed,
    Canceled,
    CanceledBySession,
  }

  public enum WonGameMedal
  {
    None, 
    Silver,
    Gold,
  }

  public enum WonGameHearts
  {
    Level,
    SilverMedal,
    GoldMedal,
    GoldOverSilverMedal,
  }

  public enum EFallingObject
  {
    coin,
  }

  /// <summary>
  /// Common cursor data types
  /// </summary>
  public enum ECursor
  {
    aim,
    paintblast,
  }

  public class DBPoint
  {
    public int xCoord = 0;
    public int yCoord = 0;
    public int zCoord = 0;
  }

  public enum EChainsStatisticsType
  {
    first_visible_chain,
    all_visible_balls,
    all_chains,
  }

  public class EChainStatistics
  {
    [EnumArray(typeof(EColor))]
    public List<int> colorBallsNum; //numBalls;
    public int       allBallsNum;   //allBalls;
  }

  public class EPlatformGeneratorStatistics
  {
    public EColor lastColor;
    public int lastColorRepeatNum = 0;
  }

  public class EPlatformGeneratorParams
  {
    [MinMaxSize(0, 10)]
    public int maxRepeatColorNum;
  }

  public class ChainGate
  {
    public bool valid = false;
    public int startChainId = 0;
    public int endChainId = 0;
  }

  public class BulletStatistics
  {
    public bool drillerGatePassed;
    public ChainGate drillerGate;
    public int gatesPassed = 0;
  }

  public class ELuxorStatistics
  {
    public int remainDistanceForFirstChain;
    public int remainDistanceForFirstChainPercent;
    [EnumArray(typeof(EChainsStatisticsType))]
    public List<EChainStatistics> chainStatistics;
    public EPlatformGeneratorStatistics generatorStatistics;

    public BulletStatistics bulletStats;

    [EnumArray(typeof(EColor))]
    [Description("Weights of colors based on sum of ratios : COLOR_BALL_PATH/PATH_LENGTH ")]
    public List<float> colorWeights;
  }

  public class EPaintStatistics
  {
    [EnumArray(typeof(EColor))]
    public List<int> remainColorCapacity;

    // all used colors for single paint
    public List<EColor> allPaintColors;

    public int remainColorsToPaint;
    public int remainPaintCapacity;
  }

  public class DBLuxorPlatformGeneratorParams
  {
    [MinMaxSize(0, 100)]
    [Description("0 - begin of path, 100 - end of path[OBSOLETE]")]
    public int firstChainInfluenceStart = 0;

    [MinMaxSize(0, 100)]
    [Description("0 - begin of path, 100 - end of path [OBSOLETE]")]
    public int firstChainInfluenceEnd = 100;

    public float colorWeightsPower = 4.0f;
    public float colorWeightsMultiplier = 0.95f;
    public float lowActChance = 0.95f;
  }

  /// <summary>
  /// Luxor part data types
  /// </summary>
  public class DBLuxBall : DBResource
  {
    public EColor ballColor = EColor.black;
    public DBLuxBall() { }
  }

  /// <summary>
  /// Paint part data types
  /// </summary>
  public class DBPainterPoint : DBResource
  {
    [FieldCategory("PainterPoint")]
    [Description("Point data for painter operations")]

    public DBPoint pointCoords;

    public int pointCapacity = 1;
    public EColor pointColor = EColor.black;
  }

  public class DBFragment
  {
    [FieldCategory("Painter fragment")]

    public EColor fragmentColor = EColor.black;
    public List<DBPtr<DBPainterPoint>> fragmentPoints = new List<DBPtr<DBPainterPoint>>();

    public int paintFragmentId;

    /// fragment render data
    [FieldCategory("Painter render parameters")]
    public DBPtr<Material> completeEffectMaterial;

  }

  public class DBListFragments
  {
    [FieldCategory("FragmentsList")]
    public List<DBFragment> listFragments = new List<DBFragment>();
  }

  [DBVersion(4)]
  public class DBPainterFragment : DBResource
  {
    [FieldCategory("Painter fragment resource")]
    public DBListFragments painterFragment;

    [FieldCategory("Painter render parameters")]
    public DBPtr<PaintMaterial> paintMaterial;
  }

  /// <summary>
  /// Sound Data Resource
  /// </summary>
  public enum EEaselSoundType
  {
    ballfired,                   //  easel_drop_shot
    ballhit,                     //  easel_hit
    ballmiss,                    //  easel_miss
    ballcolorchanged,            //  easel_platform_drops_swap
    ballexploded,                //  easel_drop_explosion

    ballhit_color_match,         //  easel_hit_color_match
    ballhit_color_missmatch,     //  easel_hit_color_missmatch

    game_win,                    //  easel_level_win
    game_loose,                  //  easel_level_loose

    boost_brighten_click,        //  easel_boost_brightening_click
    boost_freeze_click,          //  easel_boost_freeze_click
    boost_inspire_click,         //  easel_boost_inspiration_click
    boost_joker_click,           //  easel_boost_joker_click
    boost_paintblast_click,      //  easel_boost_paintblast_click
    boost_paintblast_explosion,  //  easel_boost_paintblast_explosion
    boost_speedball_click,       //  easel_boost_speedball_click
    boost_speedball_fired,       //  easel_boost_speedball_fired 

    explosion_combo_2x,          //  easel_combo_2x
    explosion_combo_3x,          //  easel_combo_3x
    explosion_combo_4x,          //  easel_combo_4x
    explosion_combo_5x,          //  easel_combo_5x

    paint_flow,                  //  easel_paint_flow

    chains_moving,               //  easel_drop_movement
    drop_sliding_low,            //  easel_drop_slide_low
    drop_sliding_high,           //  easel_drop_slide_high

    level_scroll_start,          //  easel_level_scroll_start
    level_scroll_end,            //  easel_level_scroll_end

    chain_near_exit,             //  easel_chain_near_exit
    chain_near_exit_zz,          //  easel_chain_near_exit_zz
    chain_reached_end,           //  easel_chain_reach_end
    chain_destroyed,             //  easel_chain_destroyed
    chain_merged,                //  easel_chain_merged

    result_gold_medal,           //  easel_result_gold
    result_silver_medal,         //  easel_result_silver

    scorpion_start,              //  easel_scorpion_start

    new_boost_obtained,          //  easel_new_boost_obtained

    ball_in_tunnel,              //  easel_ball_in_tunnel
    ball_out_tunnel,             //  easel_ball_out_tunnel
    tunnel_appeared,             //  easel_tunnel_appeared
    
    //speed_ball_fired,            //  easel_speedball_fired  // !!! dup of boost_speedball_fired !!!
    coin_catched,                //  easel_coin_catched

    boost_sorter_click,          //  easel_boost_sorter_fired
  }

  // Pavel <GnoM> Cherniavski: one data, based on FMod Sound subsystem
  /// <summary>
  /// Sound Event Data Resource
  /// </summary>
  [DBVersion(1)]
  public class DBEaselSound 
  {
    public string eventName = string.Empty;
    //public bool   isLooped  = false; 
  }

  /// <summary>
  /// Sounds container data Resource
  /// </summary>
  public class DBEaselSoundsData : DBResource
  {
    [FieldCategory("Easel sounds data")]
    [EnumArray(typeof(EEaselSoundType))]
    public List<DBEaselSound> sounds = new List<DBEaselSound>();
  }
  
  public class DBEaselFlowEffectGroup
  {
    [Description("group distance interval starts from previous interval and ends by this value")]
    public float intervalEndDistance = 0.0f;
    public DBPtr<BasicEffectStandalone> flowEffect;
  }

  public enum DBEaselDropState
  {
    Idle,
    Move, 
    Dead,
    MoveUnderground,
    JumpIn
}


  /// <summary>
  /// Ball view data resource
  /// </summary>
  public class DBEaselBallsView
  {
    [EnumArray(typeof(EColor))]
    public List<DBPtr<DBSceneObject>> colorBalls;

    [EnumArray(typeof(DBEaselDropState))]
    public List<string> switchToAnimation;

    [EnumArray(typeof(DBEaselDropState))]
    public List<float> animationsBaseSpeed;

    [EnumArray(typeof(DBEaselDropState))]
    public List<float> animationsSpeedModifier;

    public DBPtr<BasicEffectStandalone> paintBlastBall;
    public DBPtr<BasicEffectStandalone> paintBlastBallFlying;
    public DBPtr<DBSceneObject> jokerBall;

    public float shadowRotation = 0;
    public float shadowOpacityChangeSpeed = 1;    // opacity/sec
  }

  /// <summary>
  /// Cursor view data resource
  /// </summary>
  public class DBEaselCursorView
  {
    [EnumArray(typeof(ECursor))]
    public List<DBPtr<BasicEffectStandalone>> cursors;
  }

  public class PaintFragmentFillParams
  {
    public float paintFillStartTime = 1.1f;

    public float fillInterval = 1.0f;

    public float completeFadeIn = 1.0f;

    public float completeEffectFadeIn = 1.0f;
    public float completeEffectFadeOut = 2.0f;
  }

  public enum EComboType
  {
    none = 0,
    x2,
    x3,
    x4,
    x6,
    x8,
    x9,
    x16,
    plus3,
    plus10,
    plus20,
    godlike,
  }

  public class ExplosionParams
  {
    [Description("Minimal value of rotation angle of explosion effect between two calls in degrees")]
    public float minRotationAngle = 90;

    public Vec3 maxScale = new Vec3(1, 1, 1);
    public Vec3 minScale = new Vec3(1, 1, 1);
  }

  /// <summary>
  /// Effects view data resource
  /// </summary>
  [DBVersion( 3 )]
  public class DBEaselEffectView
  {
    public DBPtr<BasicEffectStandalone> paintblastExplosion;
    public DBPtr<BasicEffectStandalone> freezeEffect;
    public DBPtr<BasicEffectAttached> coinPickUp;
    public DBPtr<BasicEffectStandalone> gameStartEffect;
    public DBPtr<BasicEffectStandalone> gameWonEffect;
    public DBPtr<BasicEffectStandalone> sortEffect;

    public DBPtr<BasicEffectStandalone> ballExplosion;
    public ExplosionParams explosionParams;

    [Description("there is no flow effect if distance for paint flow is less than this value")]
    public float flowIntervalsStartDistance = 0.0f;
    [Description("Base scale for flow effects")]
    public float flowScale = 10.0f;

    public PaintFragmentFillParams fillParams;

    [Description("flow effects groups by distance intervals that they should fly by")]
    public List<DBEaselFlowEffectGroup> flowGroups;
    public DBPtr<BasicEffectStandalone> flowTouchEffect;

    public DBPtr<BasicEffectStandalone> pathfinderHead;
    public DBPtr<BasicEffectStandalone> pathfinderTail;

    public float pathfinderVelocity = 1000000.0f;
    public float pathfinderInterval = 10.0f;
  }

  /// <summary>
  /// platform parameters
  /// </summary>
  public class DBEaselPlatfrom
  {
    public DBPtr<DBSceneObject> platformObject;
    public DBPtr<DBSceneObject> triplePlatformObject;

    public DBPtr<LightningEffect> laser;
    public DBPtr<LightningEffect> laser2;
    public DBPtr<BasicEffectStandalone> laserPointer;
    public DBPtr<BasicEffectAttached> laserSource;
  }

  public class TunnelParams
  {
    public DBPtr<DBSceneObject> tunnel;
    public int startPointOffset = 250;
    public int endPointOffset = 100;
  }

  public class Magnet
  {
    public DBPtr<BasicEffectStandalone> magnetHighlight;
    public DBPtr<BasicEffectStandalone> magnetPreselect;
    public DBPtr<BasicEffectStandalone> magnet;
  }

  public class Coin
  {
    [MinMaxSize(0, 100)]
    public int fallingPercentage = 5;
    public float catchRadius = 1.0f;
    public float gravity = 10.0f;
    public float jumpSpeed = 10.0f;
    public float zLift = 3.0f;
  }

  public class BallVelocities
  {
    [Description("Bullet velocity")]
    public float bulletVelocity = 150000.0f;

    [Description("Bullet velocity with Palette (Laser Pointer) Bidon")]
    public float bulletPointerVelocity = 1500000.0f;

    [Description("Bullet velocity in chain")]
    public float ballInChainVelocity = 10000.0f;
  }

  /// <summary>
  /// Common GameData resource
  /// </summary>
  [DBVersion(1)]
  public class DBEaselCommon : DBResource
  {
    [EnumArray(typeof(EColor))]
    public List<HDRColor> colors;

    public DBPtr<AnimGraphCreator> priestessAnimGraph;

    public ViewCamera camera;

    //public DBPtr<DBSceneObject> aimCursorObject;
    public DBEaselCursorView aimCursors;

    public DBEaselPlatfrom platform;

    public Placement luxorPlacement;

    public DBEaselBallsView balls;

    public DBEaselEffectView effects;

    public TunnelParams tunnels;
        
    [EnumArray(typeof(EFallingObject))]
    public List<DBPtr<DBSceneObject>> fallingObjects;
    public DBLuxorPlatformGeneratorParams platformGeneratorParams;

    public DBPtr<DBSceneObject> startPipe;
    public DBPtr<DBSceneObject> endWell;

    public Magnet magnetEffects;

    public DBPtr<BasicEffectAttached> alchemistPot;

    public DBPtr<BasicEffectStandalone> glueEffect;

    public int chainTravelTime = 60000;

    public Coin coin;

    public BallVelocities ballVelocities;

    public float waitForResultScreen = 4;

    public AnimatedPlacement priestessDefaultPlacement;

    public float ballFireInterval = 0.2F;

    [Description("Number of ticks ( 100 msec ) before ball explodes after insertion")]
    public int explosionCountdown = 3;
  }

  /// <summary>
  /// Game Statistics resource
  /// </summary>
  /// 
  public enum EPriestessLevel
  {
    level_0,
    level_1,
    level_2,
    level_3,
    level_4,
    level_5,
    level_6,
    level_7,
    level_8,
    level_9,
    level_10,
    level_11,
    level_12,
    level_13,
    level_14,
    level_15,
  }

  public enum EPaintType
  {
    type_0,
    type_1, 
    type_2,
    type_3,
    type_4
  }

  [DBVersion(2)]
  public class DBPriestessLevelStats : DBResource
  {
    public EPriestessLevel level;

    public int pictureEndNafta = 0;
		public int ballExplosionNafta = 0;
		
		public int chainKillNafta = 0;
    public int paintFragmentFinishedNafta = 0;
    public int fastCompletePerSecondNafta = 0;

		public int naftaRequired = 0;

    public float goldMedalTime = 100;
    public float silverMedalTime = 150;

		public int goldMedalNafta   = 0;
		public int silverMedalNafta = 0;

    [FieldCategory("How much nafta will be returned to priestess on level fail. [0, 1]")]
    [FloatMinMax(0, 1)]
    public float failNaftaReturnMultiplier = 0.66f;
  }

  [DBVersion(1)]
  public class DBPriestessStats : DBResource
  {
    [FieldCategory("Easel statistics params")]
    [EnumArray(typeof(EPriestessLevel))]
    public List<DBPtr<DBPriestessLevelStats>> stats = new List<DBPtr<DBPriestessLevelStats>>();

    public int comboNafta = 10;
    public int coinNafta = 10;

    [IntMin(0)]
    public int heartsForLevelsStartsFrom = 5;

    [EnumArray(typeof(WonGameHearts))]
    public List<float> wonGameHearts;
  }

  /// <summary>
  /// Easel Boosts data
  /// </summary>

  /// <summary>
  /// boosts types enumeration
  /// </summary>
  public enum EBoostType
  {
    Unknown,
    PaintBlast,
    Freeze,
    Joker,
    Inspiration,
    Brightening,
    Sorter,
    Magnet,
    Alchemist,
  }

  /// <summary>
  /// boosts types enumeration
  /// </summary>
  public enum EBoostUsage
  {
    Unknown,       // not defined (must fire an error)
    InGame,        // can be used directly in-game
    AtExit,        // boost is available only when chain is at exit
  }

  /// <summary>
  /// boosts category
  /// </summary>
  public enum EBoostsCategory
  {
    Easy,
    Medium,
    Hard,
  }

  /// <summary>
  /// ` boost base data type
  /// </summary>
  public class DBBoost 
  {
    [FieldCategory("Boost base parameters")]
    public string name        = "Unknown";

    [IntMin(0)]
    public int    accesslevel = 0;
    [IntMin(0)]
    public int    cooldown    = 0;
    [IntMin(0)]
    public int    price       = 0;
  }

  /// <summary>
  /// PaintBlast boost
  /// </summary>
  public class DBPaintBlastBoost
  {
    public DBBoost boostBase;

    [IntMin(0)]
    public int radius = 0;
  }

  /// <summary>
  /// Freeze boost
  /// </summary>
  public class DBFreezeBoost
  {
    public DBBoost boostBase;

    [IntMin(0)]
    public int seconds = 0;
  }

  public class DBAlchemistBoost
  {
    public DBBoost boostBase;

    [IntMin(0)]
    public int alchemistDuration = 0;

    public int additionalPaint = 0;
    public float paintMult = 1.0f;
  }

  /// <summary>
  /// Joker boost
  /// </summary>
  public class DBJokerBoost 
  {
    public DBBoost boostBase;
  }

  /// <summary>
  /// Brightening boost
  /// </summary>
  public class DBBrighteningBoost
  {
    public DBBoost boostBase;

    [IntMin(0)]
    public int ballsnum = 0;
  }

  /// <summary>
  /// Brightening boost
  /// </summary>
  public class DBSorterBoost
  {
    public DBBoost boostBase;
  }

  /// <summary>
  /// Magnet boost
  /// </summary>
  public class DBMagnetBoost
  {
    public DBBoost boostBase;

    [IntMin(0)]
    public int searchSeconds;
    [IntMin(0)]
    public int radiusR1;
    [IntMin(0)]
    public int radiusR2;
    [IntMin(0)]
    public int numBallToEat;
  }

  /// <summary>
  /// boost random generator template class
  /// </summary>
  public class DBBoostTemplate
  {
    public EBoostUsage     boostUsage    = EBoostUsage.Unknown;
    public EBoostsCategory boostCategory = EBoostsCategory.Easy;
  }

  /// <summary>
  /// complete boosts set class
  /// </summary>
  [DBVersion(4)]
  public class DBBoostList
  {
    [FieldCategory("Reroll streak")]
    [IntMin(1)]
    public int rerollOnWinStreak  = 1;
    [IntMin(1)]
    public int rerollOnFailStreak = 3;

    [FieldCategory("Slots by level")]
    [EnumArray(typeof(EPriestessLevel))]
    public List<EBoostsCategory> slots = new List<EBoostsCategory>();

    [FieldCategory("Re-roll by Level")]
    [EnumArray(typeof(EPriestessLevel))]
    public List<bool> canReroll = new List<bool>();

    [FieldCategory("Boosts usage templates")]
    [EnumArray(typeof(EBoostType))]
    public List<DBBoostTemplate> boostsTemplate = new List<DBBoostTemplate>();

    [FieldCategory("Boosts tooltips")]
    [EnumArray(typeof(EBoostType))]
    public List<TextRef> boostsTooltips = new List<TextRef>();

    [FieldCategory("Slots pricing")]
    [EnumArray(typeof(EBoostsCategory))]
    public List<int> slotsPrices = new List<int>();

    [FieldCategory("Regenerate pricing")]
    [EnumArray(typeof(EBoostsCategory))]
    public List<int> regenPrices = new List<int>();

    [FieldCategory("Boosts UI images")]
    [EnumArray(typeof(EBoostType))]
    public List<DBPtr<UITexture>> images;

    [FieldCategory("Complete boosts set")]
    public DBPaintBlastBoost  paintblast;
    public DBFreezeBoost      freeze;
    public DBJokerBoost       joker;
    public DBSorterBoost      sorter;
    public DBMagnetBoost      magnet;
    public DBAlchemistBoost   alchemist;
  }

  //////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Easel artifact's data
  /// </summary>

  /// <summary>
  /// artifact's storage area
  /// </summary>
  [DBVersion(1)]
  public class DBEaselArtifacts
  {
    [FieldCategory("Easel artifacts parameters")]
    public List<DBPtr<Consumable>> artifact;

    [FieldCategory("Easel scrolls")]
    public List<DBPtr<SingleStateObject>> scroll;
  }   

  //////////////////////////////////////////////////////////////////////////

  /// <summary>
  /// Easel splines data minieditor's data (subject to change)
  /// </summary>
  /// 

  public enum EDifficultyLevel
  {
    Unknown,
    Easy,
    Medium,
    Hard,
    Impossible,
  }

  /// <summary>
  /// Game board structure
  /// </summary>
  public class DBBoard
  {
    [FieldCategory("Game board parameters")]
    [IntMinMax(0, 10000)]
    public int width = 10000;
    [IntMinMax(0, 10000)]
    public int height = 10000;
  }

  /// <summary>
  /// point structure
  /// </summary>
  public class DBLogicPoint
  {
    [IntMinMax(0, 10000)]
    public int x = 0;
    [IntMinMax(0, 10000)]
    public int y = 0;
  }

  /// <summary>
  /// Spline control points structure
  /// </summary>
  public class DBSplinePoints
  {
    [FieldCategory("Spline control points")]
    public List<DBLogicPoint> point = new List<DBLogicPoint>();
  }

  /// <summary>
  /// Spline structure
  /// </summary>
  public class DBSpline
  {
    [FieldCategory("Spline parameters")]
    [IntMinMax(0, 10)]
    public int degree = 3;
    [IntMinMax(0, 100)]
    public int cpnum = 0;          // number of spline control points

    public DBSplinePoints points;  // spline control points
  }

  /// <summary>
  /// Spline tunnel
  /// </summary>
  public class DBTunnel
  {
    [FieldCategory("Tunnel")]
    [IntMin(0)]
    public int begin = 0;
    [IntMin(0)]
    public int end = 0;
  }

  /// <summary>
  /// Spline tunnels data
  /// </summary>
  public class DBSplineTunnels
  {
    [FieldCategory("Spline tunnels")]
    public List<DBTunnel> tunnel = new List<DBTunnel>();
  }

  /// <summary>
  /// Spline speed marker
  /// </summary>
  public class DBSpeedMarker
  {
    [FieldCategory("SpeedMarker")]
    [IntMin(0)]
    public int position = 0;   // marker position on spline
    [IntMinMax(0, 100)]
    public int speedmultiplier = 0;
    [IntMinMax(0, 1000)]
    public int speedconstant = 0;
  }

  /// <summary>
  /// Spline speed markers data
  /// </summary>
  public class DBSplineSpeedMarkers
  {
    [FieldCategory("Spline speed markers")]
    public List<DBSpeedMarker> speedmarker = new List<DBSpeedMarker>();
  }

  /// <summary>
  /// Spline start/end point params
  /// </summary>
  public class DBSplineStartEndPoint
  {
    public AnimatedPlacement placement;
  }

  //public class DBAtExitPoint
  //{
  //  public Vec2 placement = new Vec2();

  //  public DBAtExitPoint()
  //  {
  //    placement.x = 0.0f;
  //    placement.y = 15.0f;
  //  }
  //}

  /// <summary>
  /// Spline data parameters
  /// </summary>
  public class DBSplineData
  {
    [IntMin(0)]
    public int splinelenght = 0;

    // tunnels data
    public DBSplineTunnels tunnels;

    // speed markers
    public DBSplineSpeedMarkers speedmarkers;

    // start/end points
    public DBSplineStartEndPoint startPoint;
    public DBSplineStartEndPoint endPoint;

    // at exit button points offset
    public Vec2 atExitPoint = new Vec2(0.0f,15.0f);
    //public DBAtExitPoint atExitPoint;

    // chain parameters
    [EnumArray(typeof(EPriestessLevel))]
    public List<DBPtr<DBEaselChains>> chainparams;
  }

  /// <summary>
  /// Easel path data
  /// </summary>
  public class DBEaselPath : DBResource
  {
    [FieldCategory("Spline")]
    public DBSpline spline;

    [FieldCategory("Spline data")]
    public DBSplineData splineData;
  }

  /// <summary>
  /// Easel spline resource
  /// </summary>
  public class DBEaselSpline : DBResource
  {
    public AnimatedPlacement priestessPosition;
    public bool overridePristessPosition = false;

    // for platform generator
    public float colorWeightsPower;
    public float colorWeightsMultiplier;
    public bool overrideColorWeightsParams = false;

    public EDifficultyLevel difficulty = EDifficultyLevel.Unknown;

    [FieldCategory("Board")]
    public DBBoard board;

    [FieldCategory("Paths")]
    public List<DBPtr<DBEaselPath>> path;
  }

  //////////////////////////////////////////////////////////////////////////

  public class DBEaselChains : DBResource
  {
    [MinMaxSize(3, 100)]
    public int numBallsInChain = 20;

    [MinMaxSize(0, 100)]
    public int minSameColorChain = 3;

    [MinMaxSize(1, 100)]
    public int maxSameColorChain = 8;

    [MinMaxSize(0, 200)]
    public int speedMultiplier = 100;

    public int firstChainDelay = 0;
    public int nextChainDelay  = 10000;

    [MinMaxSize(0, 100)]
    [Description("0 - maximum random, 100 - minimum")]
    public int colorsDistortionPercentage = 100;
  }

  public class DBPicture
  {
    public string picturefile;
    public string picturename;

    [EnumArray(typeof(EPriestessLevel))]
    public List<DBPtr<DBPainterFragment>> pictureparams;
  }

  public class DBPaint
  {
    public List<DBPicture> picture;
    public DBPtr<DBSceneObject> paintQuad;
  }

  public class DBEaselLevel
  {
    public EDifficultyLevel difficulty = EDifficultyLevel.Unknown;
    public EDifficultyLevel additionalDifficulty = EDifficultyLevel.Unknown;
  }

  public class DBEaselGame : DBResource
  {
    [EnumArray(typeof(EPriestessLevel))]
    public List<DBEaselLevel> levels = new List<DBEaselLevel>();

    public List<DBPtr<DBEaselSpline>> trajectories;

    [Description("Forces trajectory for first level for first time. -1 turns off trajectory force")]
    public int firstLevelForceTrajectory = 5;

    // designer test data
    public DBPtr<DBEaselChains> designerChainParams;
                
    public DBPaint paint;

    [EnumArray( typeof( EPaintType ) )]
    [Description( "С какого уровня миниигры открывается новый свиток" )]
    public List<int> availabilityTable = new List<int>();

    public float failureExperienceFactor = 0.3f;
  }

	/// <summary>
	/// Describes how bidons impact the minigame Easel
	/// </summary>
	public class DBEaselBidonEffectDesc
	{
		[Description( "Multiplier coefficient for a Cooldown" )]
		public float speedClockCooldownCoefficient = 1.0f;
    
		[Description( "Multiplier coefficient for a Price" )]
		public float speedClockPriceCoefficient = 1.0f;

    [Description( "Multiplier coefficient for a glue speed reduction" )]
    public float glueSpeedReductionCoefficient = 0.7f;

    [Description( "Percentage distance for a glue spot appearance (from the starting point)")]
    public float glueAppearancePercentageDistance = 0.7f;
	}


  /// <summary>
	/// Describes some parameters of Easel boosts tutorial
	/// </summary>
	public class DBEaselBoostsTutorialDesc
  {
    [Description("Describes how many seconds should passed after StartMovie end to fire change balls tutorial")]
    public int changeBallsSecondsFromMovieEnd = 5;

    [Description("Describes how many balls changes required to cancel tutorial about the color change")]
    public int changeBallsCounts = 2;
  }

  /// <summary>
  /// Easel data root
  /// </summary>
  [DBVersion(2)]
  public class DBEaselData : DBResource
  {
    [FieldCategory("Minigame Name")]
    public TextRef title;

    [FieldCategory("Generated chain will be placed on the spline from this offset")]
    public int startPointOffset = -400;

    [FieldCategory("Chain will be killed after end + offset")]
    public int killChainAfterOffset = 400;

    public DBPtr<DBEaselGame> game;

    [FieldCategory("Painter params")]
    public DBPtr<DBEaselCommon> commonParams;

    [FieldCategory("Sound params")]
    public DBPtr<DBEaselSoundsData> soundData;

    [FieldCategory("Stats params")]
    public DBPtr<DBPriestessStats> priestessStats;

    [FieldCategory("Boosts parameters")]
    public DBBoostList gameboosts;

		[Description( "Describes how Bidons affect the Easel MiniGame" )]
		public DBEaselBidonEffectDesc bidonEffectDesc;

    [Description("Describes some boosts tutorial parameters")]
    public DBEaselBoostsTutorialDesc boostsTutorialDesc;

    //[FieldCategory("Artifacts")]
    public DBEaselArtifacts artifacts;

    public DBEaselData() { }
  }
}
