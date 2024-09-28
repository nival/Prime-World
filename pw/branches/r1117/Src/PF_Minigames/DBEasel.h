#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Scene/DBScene.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;

namespace NDb
{
struct AnimGraphCreator;
struct BasicEffectAttached;
struct BasicEffectStandalone;
struct Consumable;
struct DBEaselChains;
struct DBEaselCommon;
struct DBEaselGame;
struct DBEaselPath;
struct DBEaselSoundsData;
struct DBEaselSpline;
struct DBPainterFragment;
struct DBPainterPoint;
struct DBPriestessLevelStats;
struct DBPriestessStats;
struct DBSceneObject;
struct LightningEffect;
struct Material;
struct PaintMaterial;
struct SingleStateObject;
struct UITexture;

enum DBEaselDropState
{
	DBEASELDROPSTATE_IDLE = 0,
	DBEASELDROPSTATE_MOVE = 1,
	DBEASELDROPSTATE_DEAD = 2,
	DBEASELDROPSTATE_MOVEUNDERGROUND = 3,
	DBEASELDROPSTATE_JUMPIN = 4,
};

const char *EnumToString( const DBEaselDropState value );
const DBEaselDropState StringToEnum_DBEaselDropState( const char* value );

template <>
struct KnownEnum< DBEaselDropState >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const DBEaselDropState value ) { return EnumToString( value ); }
	static const DBEaselDropState ToEnum( const char* value ) { return StringToEnum_DBEaselDropState( value ); }
	static const DBEaselDropState ToEnum( const string& value ) { return StringToEnum_DBEaselDropState( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EBoostsCategory
{
	BOOSTSCATEGORY_EASY = 0,
	BOOSTSCATEGORY_MEDIUM = 1,
	BOOSTSCATEGORY_HARD = 2,
};

const char *EnumToString( const EBoostsCategory value );
const EBoostsCategory StringToEnum_EBoostsCategory( const char* value );

template <>
struct KnownEnum< EBoostsCategory >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EBoostsCategory value ) { return EnumToString( value ); }
	static const EBoostsCategory ToEnum( const char* value ) { return StringToEnum_EBoostsCategory( value ); }
	static const EBoostsCategory ToEnum( const string& value ) { return StringToEnum_EBoostsCategory( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EBoostType
{
	BOOSTTYPE_UNKNOWN = 0,
	BOOSTTYPE_PAINTBLAST = 1,
	BOOSTTYPE_FREEZE = 2,
	BOOSTTYPE_JOKER = 3,
	BOOSTTYPE_INSPIRATION = 4,
	BOOSTTYPE_BRIGHTENING = 5,
	BOOSTTYPE_SORTER = 6,
	BOOSTTYPE_MAGNET = 7,
	BOOSTTYPE_ALCHEMIST = 8,
};

const char *EnumToString( const EBoostType value );
const EBoostType StringToEnum_EBoostType( const char* value );

template <>
struct KnownEnum< EBoostType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 9 };
	static const char *ToString( const EBoostType value ) { return EnumToString( value ); }
	static const EBoostType ToEnum( const char* value ) { return StringToEnum_EBoostType( value ); }
	static const EBoostType ToEnum( const string& value ) { return StringToEnum_EBoostType( value.c_str() ); }
	static const int SizeOf() { return 9; }
};

enum EBoostUsage
{
	BOOSTUSAGE_UNKNOWN = 0,
	BOOSTUSAGE_INGAME = 1,
	BOOSTUSAGE_ATEXIT = 2,
};

const char *EnumToString( const EBoostUsage value );
const EBoostUsage StringToEnum_EBoostUsage( const char* value );

template <>
struct KnownEnum< EBoostUsage >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EBoostUsage value ) { return EnumToString( value ); }
	static const EBoostUsage ToEnum( const char* value ) { return StringToEnum_EBoostUsage( value ); }
	static const EBoostUsage ToEnum( const string& value ) { return StringToEnum_EBoostUsage( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EChainsStatisticsType
{
	CHAINSSTATISTICSTYPE_FIRST_VISIBLE_CHAIN = 0,
	CHAINSSTATISTICSTYPE_ALL_VISIBLE_BALLS = 1,
	CHAINSSTATISTICSTYPE_ALL_CHAINS = 2,
};

const char *EnumToString( const EChainsStatisticsType value );
const EChainsStatisticsType StringToEnum_EChainsStatisticsType( const char* value );

template <>
struct KnownEnum< EChainsStatisticsType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EChainsStatisticsType value ) { return EnumToString( value ); }
	static const EChainsStatisticsType ToEnum( const char* value ) { return StringToEnum_EChainsStatisticsType( value ); }
	static const EChainsStatisticsType ToEnum( const string& value ) { return StringToEnum_EChainsStatisticsType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EColor
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_RED = 3,
	COLOR_WHITE = 4,
	COLOR_CYAN = 5,
	COLOR_YELLOW = 6,
	COLOR_MAGENTA = 7,
	COLOR_ANY = 8,
};

const char *EnumToString( const EColor value );
const EColor StringToEnum_EColor( const char* value );

template <>
struct KnownEnum< EColor >
{
	enum { isKnown = 1 };
	enum { sizeOf = 9 };
	static const char *ToString( const EColor value ) { return EnumToString( value ); }
	static const EColor ToEnum( const char* value ) { return StringToEnum_EColor( value ); }
	static const EColor ToEnum( const string& value ) { return StringToEnum_EColor( value.c_str() ); }
	static const int SizeOf() { return 9; }
};

enum EComboType
{
	COMBOTYPE_NONE = 0,
	COMBOTYPE_X2 = 1,
	COMBOTYPE_X3 = 2,
	COMBOTYPE_X4 = 3,
	COMBOTYPE_X6 = 4,
	COMBOTYPE_X8 = 5,
	COMBOTYPE_X9 = 6,
	COMBOTYPE_X16 = 7,
	COMBOTYPE_PLUS3 = 8,
	COMBOTYPE_PLUS10 = 9,
	COMBOTYPE_PLUS20 = 10,
	COMBOTYPE_GODLIKE = 11,
};

const char *EnumToString( const EComboType value );
const EComboType StringToEnum_EComboType( const char* value );

template <>
struct KnownEnum< EComboType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 12 };
	static const char *ToString( const EComboType value ) { return EnumToString( value ); }
	static const EComboType ToEnum( const char* value ) { return StringToEnum_EComboType( value ); }
	static const EComboType ToEnum( const string& value ) { return StringToEnum_EComboType( value.c_str() ); }
	static const int SizeOf() { return 12; }
};

enum ECursor
{
	CURSOR_AIM = 0,
	CURSOR_PAINTBLAST = 1,
};

const char *EnumToString( const ECursor value );
const ECursor StringToEnum_ECursor( const char* value );

template <>
struct KnownEnum< ECursor >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ECursor value ) { return EnumToString( value ); }
	static const ECursor ToEnum( const char* value ) { return StringToEnum_ECursor( value ); }
	static const ECursor ToEnum( const string& value ) { return StringToEnum_ECursor( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EDifficultyLevel
{
	DIFFICULTYLEVEL_UNKNOWN = 0,
	DIFFICULTYLEVEL_EASY = 1,
	DIFFICULTYLEVEL_MEDIUM = 2,
	DIFFICULTYLEVEL_HARD = 3,
	DIFFICULTYLEVEL_IMPOSSIBLE = 4,
};

const char *EnumToString( const EDifficultyLevel value );
const EDifficultyLevel StringToEnum_EDifficultyLevel( const char* value );

template <>
struct KnownEnum< EDifficultyLevel >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EDifficultyLevel value ) { return EnumToString( value ); }
	static const EDifficultyLevel ToEnum( const char* value ) { return StringToEnum_EDifficultyLevel( value ); }
	static const EDifficultyLevel ToEnum( const string& value ) { return StringToEnum_EDifficultyLevel( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EEaselRoundStatus
{
	EASELROUNDSTATUS_UNINITIALIZED = 0,
	EASELROUNDSTATUS_INCOMPLETE = 1,
	EASELROUNDSTATUS_WON = 2,
	EASELROUNDSTATUS_FAILED = 3,
	EASELROUNDSTATUS_CANCELED = 4,
	EASELROUNDSTATUS_CANCELEDBYSESSION = 5,
};

const char *EnumToString( const EEaselRoundStatus value );
const EEaselRoundStatus StringToEnum_EEaselRoundStatus( const char* value );

template <>
struct KnownEnum< EEaselRoundStatus >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EEaselRoundStatus value ) { return EnumToString( value ); }
	static const EEaselRoundStatus ToEnum( const char* value ) { return StringToEnum_EEaselRoundStatus( value ); }
	static const EEaselRoundStatus ToEnum( const string& value ) { return StringToEnum_EEaselRoundStatus( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EEaselSoundType
{
	EASELSOUNDTYPE_BALLFIRED = 0,
	EASELSOUNDTYPE_BALLHIT = 1,
	EASELSOUNDTYPE_BALLMISS = 2,
	EASELSOUNDTYPE_BALLCOLORCHANGED = 3,
	EASELSOUNDTYPE_BALLEXPLODED = 4,
	EASELSOUNDTYPE_BALLHIT_COLOR_MATCH = 5,
	EASELSOUNDTYPE_BALLHIT_COLOR_MISSMATCH = 6,
	EASELSOUNDTYPE_GAME_WIN = 7,
	EASELSOUNDTYPE_GAME_LOOSE = 8,
	EASELSOUNDTYPE_BOOST_BRIGHTEN_CLICK = 9,
	EASELSOUNDTYPE_BOOST_FREEZE_CLICK = 10,
	EASELSOUNDTYPE_BOOST_INSPIRE_CLICK = 11,
	EASELSOUNDTYPE_BOOST_JOKER_CLICK = 12,
	EASELSOUNDTYPE_BOOST_PAINTBLAST_CLICK = 13,
	EASELSOUNDTYPE_BOOST_PAINTBLAST_EXPLOSION = 14,
	EASELSOUNDTYPE_BOOST_SPEEDBALL_CLICK = 15,
	EASELSOUNDTYPE_BOOST_SPEEDBALL_FIRED = 16,
	EASELSOUNDTYPE_EXPLOSION_COMBO_2X = 17,
	EASELSOUNDTYPE_EXPLOSION_COMBO_3X = 18,
	EASELSOUNDTYPE_EXPLOSION_COMBO_4X = 19,
	EASELSOUNDTYPE_EXPLOSION_COMBO_5X = 20,
	EASELSOUNDTYPE_PAINT_FLOW = 21,
	EASELSOUNDTYPE_CHAINS_MOVING = 22,
	EASELSOUNDTYPE_DROP_SLIDING_LOW = 23,
	EASELSOUNDTYPE_DROP_SLIDING_HIGH = 24,
	EASELSOUNDTYPE_LEVEL_SCROLL_START = 25,
	EASELSOUNDTYPE_LEVEL_SCROLL_END = 26,
	EASELSOUNDTYPE_CHAIN_NEAR_EXIT = 27,
	EASELSOUNDTYPE_CHAIN_NEAR_EXIT_ZZ = 28,
	EASELSOUNDTYPE_CHAIN_REACHED_END = 29,
	EASELSOUNDTYPE_CHAIN_DESTROYED = 30,
	EASELSOUNDTYPE_CHAIN_MERGED = 31,
	EASELSOUNDTYPE_RESULT_GOLD_MEDAL = 32,
	EASELSOUNDTYPE_RESULT_SILVER_MEDAL = 33,
	EASELSOUNDTYPE_SCORPION_START = 34,
	EASELSOUNDTYPE_NEW_BOOST_OBTAINED = 35,
	EASELSOUNDTYPE_BALL_IN_TUNNEL = 36,
	EASELSOUNDTYPE_BALL_OUT_TUNNEL = 37,
	EASELSOUNDTYPE_TUNNEL_APPEARED = 38,
	EASELSOUNDTYPE_COIN_CATCHED = 39,
	EASELSOUNDTYPE_BOOST_SORTER_CLICK = 40,
};

const char *EnumToString( const EEaselSoundType value );
const EEaselSoundType StringToEnum_EEaselSoundType( const char* value );

template <>
struct KnownEnum< EEaselSoundType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 41 };
	static const char *ToString( const EEaselSoundType value ) { return EnumToString( value ); }
	static const EEaselSoundType ToEnum( const char* value ) { return StringToEnum_EEaselSoundType( value ); }
	static const EEaselSoundType ToEnum( const string& value ) { return StringToEnum_EEaselSoundType( value.c_str() ); }
	static const int SizeOf() { return 41; }
};

enum EFallingObject
{
	FALLINGOBJECT_COIN = 0,
};

const char *EnumToString( const EFallingObject value );
const EFallingObject StringToEnum_EFallingObject( const char* value );

template <>
struct KnownEnum< EFallingObject >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const EFallingObject value ) { return EnumToString( value ); }
	static const EFallingObject ToEnum( const char* value ) { return StringToEnum_EFallingObject( value ); }
	static const EFallingObject ToEnum( const string& value ) { return StringToEnum_EFallingObject( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

enum EPaintType
{
	PAINTTYPE_TYPE_0 = 0,
	PAINTTYPE_TYPE_1 = 1,
	PAINTTYPE_TYPE_2 = 2,
	PAINTTYPE_TYPE_3 = 3,
	PAINTTYPE_TYPE_4 = 4,
};

const char *EnumToString( const EPaintType value );
const EPaintType StringToEnum_EPaintType( const char* value );

template <>
struct KnownEnum< EPaintType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EPaintType value ) { return EnumToString( value ); }
	static const EPaintType ToEnum( const char* value ) { return StringToEnum_EPaintType( value ); }
	static const EPaintType ToEnum( const string& value ) { return StringToEnum_EPaintType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EPriestessLevel
{
	PRIESTESSLEVEL_LEVEL_0 = 0,
	PRIESTESSLEVEL_LEVEL_1 = 1,
	PRIESTESSLEVEL_LEVEL_2 = 2,
	PRIESTESSLEVEL_LEVEL_3 = 3,
	PRIESTESSLEVEL_LEVEL_4 = 4,
	PRIESTESSLEVEL_LEVEL_5 = 5,
	PRIESTESSLEVEL_LEVEL_6 = 6,
	PRIESTESSLEVEL_LEVEL_7 = 7,
	PRIESTESSLEVEL_LEVEL_8 = 8,
	PRIESTESSLEVEL_LEVEL_9 = 9,
	PRIESTESSLEVEL_LEVEL_10 = 10,
	PRIESTESSLEVEL_LEVEL_11 = 11,
	PRIESTESSLEVEL_LEVEL_12 = 12,
	PRIESTESSLEVEL_LEVEL_13 = 13,
	PRIESTESSLEVEL_LEVEL_14 = 14,
	PRIESTESSLEVEL_LEVEL_15 = 15,
};

const char *EnumToString( const EPriestessLevel value );
const EPriestessLevel StringToEnum_EPriestessLevel( const char* value );

template <>
struct KnownEnum< EPriestessLevel >
{
	enum { isKnown = 1 };
	enum { sizeOf = 16 };
	static const char *ToString( const EPriestessLevel value ) { return EnumToString( value ); }
	static const EPriestessLevel ToEnum( const char* value ) { return StringToEnum_EPriestessLevel( value ); }
	static const EPriestessLevel ToEnum( const string& value ) { return StringToEnum_EPriestessLevel( value.c_str() ); }
	static const int SizeOf() { return 16; }
};

enum WonGameHearts
{
	WONGAMEHEARTS_LEVEL = 0,
	WONGAMEHEARTS_SILVERMEDAL = 1,
	WONGAMEHEARTS_GOLDMEDAL = 2,
	WONGAMEHEARTS_GOLDOVERSILVERMEDAL = 3,
};

const char *EnumToString( const WonGameHearts value );
const WonGameHearts StringToEnum_WonGameHearts( const char* value );

template <>
struct KnownEnum< WonGameHearts >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const WonGameHearts value ) { return EnumToString( value ); }
	static const WonGameHearts ToEnum( const char* value ) { return StringToEnum_WonGameHearts( value ); }
	static const WonGameHearts ToEnum( const string& value ) { return StringToEnum_WonGameHearts( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum WonGameMedal
{
	WONGAMEMEDAL_NONE = 0,
	WONGAMEMEDAL_SILVER = 1,
	WONGAMEMEDAL_GOLD = 2,
};

const char *EnumToString( const WonGameMedal value );
const WonGameMedal StringToEnum_WonGameMedal( const char* value );

template <>
struct KnownEnum< WonGameMedal >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const WonGameMedal value ) { return EnumToString( value ); }
	static const WonGameMedal ToEnum( const char* value ) { return StringToEnum_WonGameMedal( value ); }
	static const WonGameMedal ToEnum( const string& value ) { return StringToEnum_WonGameMedal( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct BallVelocities
{
public:
	float bulletVelocity;
	float bulletPointerVelocity;
	float ballInChainVelocity;

	BallVelocities();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ChainGate
{
public:
	bool valid;
	int startChainId;
	int endChainId;

	ChainGate();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct BulletStatistics
{
public:
	bool drillerGatePassed;
	ChainGate drillerGate;
	int gatesPassed;

	BulletStatistics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Coin
{
public:
	int fallingPercentage;
	float catchRadius;
	float gravity;
	float jumpSpeed;
	float zLift;

	Coin();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBBoost
{
public:
	string name;
	int accesslevel;
	int cooldown;
	int price;

	DBBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBBoard
{
public:
	int width;
	int height;

	DBBoard();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBAlchemistBoost
{
public:
	DBBoost boostBase;
	int alchemistDuration;
	int additionalPaint;
	float paintMult;

	DBAlchemistBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBBoostTemplate
{
public:
	EBoostUsage boostUsage;
	EBoostsCategory boostCategory;

	DBBoostTemplate();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBFreezeBoost
{
public:
	DBBoost boostBase;
	int seconds;

	DBFreezeBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBBrighteningBoost
{
public:
	DBBoost boostBase;
	int ballsnum;

	DBBrighteningBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselArtifacts
{
public:
	vector< Ptr< Consumable > > artifact;
	vector< Ptr< SingleStateObject > > scroll;

	DBEaselArtifacts();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselBallsView
{
public:
	vector< Ptr< DBSceneObject > > colorBalls;
	vector< string > switchToAnimation;
	vector< float > animationsBaseSpeed;
	vector< float > animationsSpeedModifier;
	Ptr< BasicEffectStandalone > paintBlastBall;
	Ptr< BasicEffectStandalone > paintBlastBallFlying;
	Ptr< DBSceneObject > jokerBall;
	float shadowRotation;
	float shadowOpacityChangeSpeed;

	DBEaselBallsView();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselBidonEffectDesc
{
public:
	float speedClockCooldownCoefficient;
	float speedClockPriceCoefficient;
	float glueSpeedReductionCoefficient;
	float glueAppearancePercentageDistance;

	DBEaselBidonEffectDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselBoostsTutorialDesc
{
public:
	int changeBallsSecondsFromMovieEnd;
	int changeBallsCounts;

	DBEaselBoostsTutorialDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselCursorView
{
public:
	vector< Ptr< BasicEffectStandalone > > cursors;

	DBEaselCursorView();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselFlowEffectGroup
{
public:
	float intervalEndDistance;
	Ptr< BasicEffectStandalone > flowEffect;

	DBEaselFlowEffectGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ExplosionParams
{
public:
	float minRotationAngle;
	CVec3 maxScale;
	CVec3 minScale;

	ExplosionParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselLevel
{
public:
	EDifficultyLevel difficulty;
	EDifficultyLevel additionalDifficulty;

	DBEaselLevel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselPlatfrom
{
public:
	Ptr< DBSceneObject > platformObject;
	Ptr< DBSceneObject > triplePlatformObject;
	Ptr< LightningEffect > laser;
	Ptr< LightningEffect > laser2;
	Ptr< BasicEffectStandalone > laserPointer;
	Ptr< BasicEffectAttached > laserSource;

	DBEaselPlatfrom();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselSound
{
public:
	string eventName;

	DBEaselSound();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBFragment
{
public:
	EColor fragmentColor;
	vector< Ptr< DBPainterPoint > > fragmentPoints;
	int paintFragmentId;
	Ptr< Material > completeEffectMaterial;

	DBFragment();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBJokerBoost
{
public:
	DBBoost boostBase;

	DBJokerBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBMagnetBoost
{
public:
	DBBoost boostBase;
	int searchSeconds;
	int radiusR1;
	int radiusR2;
	int numBallToEat;

	DBMagnetBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBListFragments
{
public:
	vector< DBFragment > listFragments;

	DBListFragments();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBLogicPoint
{
public:
	int x;
	int y;

	DBLogicPoint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBLuxorPlatformGeneratorParams
{
public:
	int firstChainInfluenceStart;
	int firstChainInfluenceEnd;
	float colorWeightsPower;
	float colorWeightsMultiplier;
	float lowActChance;

	DBLuxorPlatformGeneratorParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBPaintBlastBoost
{
public:
	DBBoost boostBase;
	int radius;

	DBPaintBlastBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBPicture
{
public:
	string picturefile;
	string picturename;
	vector< Ptr< DBPainterFragment > > pictureparams;

	DBPicture();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSorterBoost
{
public:
	DBBoost boostBase;

	DBSorterBoost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBPaint
{
public:
	vector< DBPicture > picture;
	Ptr< DBSceneObject > paintQuad;

	DBPaint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBPoint
{
public:
	int xCoord;
	int yCoord;
	int zCoord;

	DBPoint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBBoostList
{
public:
	int rerollOnWinStreak;
	int rerollOnFailStreak;
	vector< EBoostsCategory > slots;
	vector< bool > canReroll;
	vector< DBBoostTemplate > boostsTemplate;
	vector< CTextRef > boostsTooltips;
	vector< int > slotsPrices;
	vector< int > regenPrices;
	vector< Ptr< UITexture > > images;
	DBPaintBlastBoost paintblast;
	DBFreezeBoost freeze;
	DBJokerBoost joker;
	DBSorterBoost sorter;
	DBMagnetBoost magnet;
	DBAlchemistBoost alchemist;

	DBBoostList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSpeedMarker
{
public:
	int position;
	int speedmultiplier;
	int speedconstant;

	DBSpeedMarker();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSplinePoints
{
public:
	vector< DBLogicPoint > point;

	DBSplinePoints();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSplineSpeedMarkers
{
public:
	vector< DBSpeedMarker > speedmarker;

	DBSplineSpeedMarkers();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSpline
{
public:
	int degree;
	int cpnum;
	DBSplinePoints points;

	DBSpline();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSplineStartEndPoint
{
public:
	AnimatedPlacement placement;

	DBSplineStartEndPoint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBTunnel
{
public:
	int begin;
	int end;

	DBTunnel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSplineTunnels
{
public:
	vector< DBTunnel > tunnel;

	DBSplineTunnels();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBSplineData
{
public:
	int splinelenght;
	DBSplineTunnels tunnels;
	DBSplineSpeedMarkers speedmarkers;
	DBSplineStartEndPoint startPoint;
	DBSplineStartEndPoint endPoint;
	CVec2 atExitPoint;
	vector< Ptr< DBEaselChains > > chainparams;

	DBSplineData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EChainStatistics
{
public:
	vector< int > colorBallsNum;
	int allBallsNum;

	EChainStatistics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EPlatformGeneratorStatistics
{
public:
	EColor lastColor;
	int lastColorRepeatNum;

	EPlatformGeneratorStatistics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EPaintStatistics
{
public:
	vector< int > remainColorCapacity;
	vector< EColor > allPaintColors;
	int remainColorsToPaint;
	int remainPaintCapacity;

	EPaintStatistics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EPlatformGeneratorParams
{
public:
	int maxRepeatColorNum;

	EPlatformGeneratorParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ELuxorStatistics
{
public:
	int remainDistanceForFirstChain;
	int remainDistanceForFirstChainPercent;
	vector< EChainStatistics > chainStatistics;
	EPlatformGeneratorStatistics generatorStatistics;
	BulletStatistics bulletStats;
	vector< float > colorWeights;

	ELuxorStatistics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PaintFragmentFillParams
{
public:
	float paintFillStartTime;
	float fillInterval;
	float completeFadeIn;
	float completeEffectFadeIn;
	float completeEffectFadeOut;

	PaintFragmentFillParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Magnet
{
public:
	Ptr< BasicEffectStandalone > magnetHighlight;
	Ptr< BasicEffectStandalone > magnetPreselect;
	Ptr< BasicEffectStandalone > magnet;

	Magnet();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselEffectView
{
public:
	Ptr< BasicEffectStandalone > paintblastExplosion;
	Ptr< BasicEffectStandalone > freezeEffect;
	Ptr< BasicEffectAttached > coinPickUp;
	Ptr< BasicEffectStandalone > gameStartEffect;
	Ptr< BasicEffectStandalone > gameWonEffect;
	Ptr< BasicEffectStandalone > sortEffect;
	Ptr< BasicEffectStandalone > ballExplosion;
	ExplosionParams explosionParams;
	float flowIntervalsStartDistance;
	float flowScale;
	PaintFragmentFillParams fillParams;
	vector< DBEaselFlowEffectGroup > flowGroups;
	Ptr< BasicEffectStandalone > flowTouchEffect;
	Ptr< BasicEffectStandalone > pathfinderHead;
	Ptr< BasicEffectStandalone > pathfinderTail;
	float pathfinderVelocity;
	float pathfinderInterval;

	DBEaselEffectView();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TunnelParams
{
public:
	Ptr< DBSceneObject > tunnel;
	int startPointOffset;
	int endPointOffset;

	TunnelParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBEaselChains : public DbResource
{
	DBRESOURCE_METHODS( DBEaselChains );
public:
	int numBallsInChain;
	int minSameColorChain;
	int maxSameColorChain;
	int speedMultiplier;
	int firstChainDelay;
	int nextChainDelay;
	int colorsDistortionPercentage;

	DBEaselChains();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselChains& operator = ( const DBEaselChains &_dBEaselChains ) { Assign( _dBEaselChains ); return *this; }
	DBEaselChains( const DBEaselChains &_dBEaselChains ) { Assign( _dBEaselChains ); }
	virtual void Assign( const DBEaselChains &_dBEaselChains );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselChains * pOther = dynamic_cast< const DBEaselChains * > ( _pResource );
		if ( pOther ) DBEaselChains::Assign( *pOther );
	}
};

struct DBEaselCommon : public DbResource
{
	DBRESOURCE_METHODS( DBEaselCommon );
public:
	vector< Render::HDRColor > colors;
	Ptr< AnimGraphCreator > priestessAnimGraph;
	ViewCamera camera;
	DBEaselCursorView aimCursors;
	DBEaselPlatfrom platform;
	CPlacement luxorPlacement;
	DBEaselBallsView balls;
	DBEaselEffectView effects;
	TunnelParams tunnels;
	vector< Ptr< DBSceneObject > > fallingObjects;
	DBLuxorPlatformGeneratorParams platformGeneratorParams;
	Ptr< DBSceneObject > startPipe;
	Ptr< DBSceneObject > endWell;
	Magnet magnetEffects;
	Ptr< BasicEffectAttached > alchemistPot;
	Ptr< BasicEffectStandalone > glueEffect;
	int chainTravelTime;
	Coin coin;
	BallVelocities ballVelocities;
	float waitForResultScreen;
	AnimatedPlacement priestessDefaultPlacement;
	float ballFireInterval;
	int explosionCountdown;

	DBEaselCommon();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselCommon& operator = ( const DBEaselCommon &_dBEaselCommon ) { Assign( _dBEaselCommon ); return *this; }
	DBEaselCommon( const DBEaselCommon &_dBEaselCommon ) { Assign( _dBEaselCommon ); }
	virtual void Assign( const DBEaselCommon &_dBEaselCommon );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselCommon * pOther = dynamic_cast< const DBEaselCommon * > ( _pResource );
		if ( pOther ) DBEaselCommon::Assign( *pOther );
	}
};

struct DBEaselData : public DbResource
{
	DBRESOURCE_METHODS( DBEaselData );
public:
	CTextRef title;
	int startPointOffset;
	int killChainAfterOffset;
	Ptr< DBEaselGame > game;
	Ptr< DBEaselCommon > commonParams;
	Ptr< DBEaselSoundsData > soundData;
	Ptr< DBPriestessStats > priestessStats;
	DBBoostList gameboosts;
	DBEaselBidonEffectDesc bidonEffectDesc;
	DBEaselBoostsTutorialDesc boostsTutorialDesc;
	DBEaselArtifacts artifacts;

	DBEaselData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselData& operator = ( const DBEaselData &_dBEaselData ) { Assign( _dBEaselData ); return *this; }
	DBEaselData( const DBEaselData &_dBEaselData ) { Assign( _dBEaselData ); }
	virtual void Assign( const DBEaselData &_dBEaselData );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselData * pOther = dynamic_cast< const DBEaselData * > ( _pResource );
		if ( pOther ) DBEaselData::Assign( *pOther );
	}
};

struct DBEaselGame : public DbResource
{
	DBRESOURCE_METHODS( DBEaselGame );
public:
	vector< DBEaselLevel > levels;
	vector< Ptr< DBEaselSpline > > trajectories;
	int firstLevelForceTrajectory;
	Ptr< DBEaselChains > designerChainParams;
	DBPaint paint;
	vector< int > availabilityTable;
	float failureExperienceFactor;

	DBEaselGame();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselGame& operator = ( const DBEaselGame &_dBEaselGame ) { Assign( _dBEaselGame ); return *this; }
	DBEaselGame( const DBEaselGame &_dBEaselGame ) { Assign( _dBEaselGame ); }
	virtual void Assign( const DBEaselGame &_dBEaselGame );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselGame * pOther = dynamic_cast< const DBEaselGame * > ( _pResource );
		if ( pOther ) DBEaselGame::Assign( *pOther );
	}
};

struct DBEaselPath : public DbResource
{
	DBRESOURCE_METHODS( DBEaselPath );
public:
	DBSpline spline;
	DBSplineData splineData;

	DBEaselPath();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselPath& operator = ( const DBEaselPath &_dBEaselPath ) { Assign( _dBEaselPath ); return *this; }
	DBEaselPath( const DBEaselPath &_dBEaselPath ) { Assign( _dBEaselPath ); }
	virtual void Assign( const DBEaselPath &_dBEaselPath );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselPath * pOther = dynamic_cast< const DBEaselPath * > ( _pResource );
		if ( pOther ) DBEaselPath::Assign( *pOther );
	}
};

struct DBEaselSoundsData : public DbResource
{
	DBRESOURCE_METHODS( DBEaselSoundsData );
public:
	vector< DBEaselSound > sounds;

	DBEaselSoundsData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselSoundsData& operator = ( const DBEaselSoundsData &_dBEaselSoundsData ) { Assign( _dBEaselSoundsData ); return *this; }
	DBEaselSoundsData( const DBEaselSoundsData &_dBEaselSoundsData ) { Assign( _dBEaselSoundsData ); }
	virtual void Assign( const DBEaselSoundsData &_dBEaselSoundsData );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselSoundsData * pOther = dynamic_cast< const DBEaselSoundsData * > ( _pResource );
		if ( pOther ) DBEaselSoundsData::Assign( *pOther );
	}
};

struct DBEaselSpline : public DbResource
{
	DBRESOURCE_METHODS( DBEaselSpline );
public:
	AnimatedPlacement priestessPosition;
	bool overridePristessPosition;
	float colorWeightsPower;
	float colorWeightsMultiplier;
	bool overrideColorWeightsParams;
	EDifficultyLevel difficulty;
	DBBoard board;
	vector< Ptr< DBEaselPath > > path;

	DBEaselSpline();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBEaselSpline& operator = ( const DBEaselSpline &_dBEaselSpline ) { Assign( _dBEaselSpline ); return *this; }
	DBEaselSpline( const DBEaselSpline &_dBEaselSpline ) { Assign( _dBEaselSpline ); }
	virtual void Assign( const DBEaselSpline &_dBEaselSpline );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBEaselSpline * pOther = dynamic_cast< const DBEaselSpline * > ( _pResource );
		if ( pOther ) DBEaselSpline::Assign( *pOther );
	}
};

struct DBLuxBall : public DbResource
{
	DBRESOURCE_METHODS( DBLuxBall );
public:
	EColor ballColor;

	DBLuxBall();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBLuxBall& operator = ( const DBLuxBall &_dBLuxBall ) { Assign( _dBLuxBall ); return *this; }
	DBLuxBall( const DBLuxBall &_dBLuxBall ) { Assign( _dBLuxBall ); }
	virtual void Assign( const DBLuxBall &_dBLuxBall );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBLuxBall * pOther = dynamic_cast< const DBLuxBall * > ( _pResource );
		if ( pOther ) DBLuxBall::Assign( *pOther );
	}
};

struct DBPainterFragment : public DbResource
{
	DBRESOURCE_METHODS( DBPainterFragment );
public:
	DBListFragments painterFragment;
	Ptr< PaintMaterial > paintMaterial;

	DBPainterFragment();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBPainterFragment& operator = ( const DBPainterFragment &_dBPainterFragment ) { Assign( _dBPainterFragment ); return *this; }
	DBPainterFragment( const DBPainterFragment &_dBPainterFragment ) { Assign( _dBPainterFragment ); }
	virtual void Assign( const DBPainterFragment &_dBPainterFragment );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBPainterFragment * pOther = dynamic_cast< const DBPainterFragment * > ( _pResource );
		if ( pOther ) DBPainterFragment::Assign( *pOther );
	}
};

struct DBPainterPoint : public DbResource
{
	DBRESOURCE_METHODS( DBPainterPoint );
public:
	DBPoint pointCoords;
	int pointCapacity;
	EColor pointColor;

	DBPainterPoint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBPainterPoint& operator = ( const DBPainterPoint &_dBPainterPoint ) { Assign( _dBPainterPoint ); return *this; }
	DBPainterPoint( const DBPainterPoint &_dBPainterPoint ) { Assign( _dBPainterPoint ); }
	virtual void Assign( const DBPainterPoint &_dBPainterPoint );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBPainterPoint * pOther = dynamic_cast< const DBPainterPoint * > ( _pResource );
		if ( pOther ) DBPainterPoint::Assign( *pOther );
	}
};

struct DBPriestessLevelStats : public DbResource
{
	DBRESOURCE_METHODS( DBPriestessLevelStats );
public:
	EPriestessLevel level;
	int pictureEndNafta;
	int ballExplosionNafta;
	int chainKillNafta;
	int paintFragmentFinishedNafta;
	int fastCompletePerSecondNafta;
	int naftaRequired;
	float goldMedalTime;
	float silverMedalTime;
	int goldMedalNafta;
	int silverMedalNafta;
	float failNaftaReturnMultiplier;

	DBPriestessLevelStats();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBPriestessLevelStats& operator = ( const DBPriestessLevelStats &_dBPriestessLevelStats ) { Assign( _dBPriestessLevelStats ); return *this; }
	DBPriestessLevelStats( const DBPriestessLevelStats &_dBPriestessLevelStats ) { Assign( _dBPriestessLevelStats ); }
	virtual void Assign( const DBPriestessLevelStats &_dBPriestessLevelStats );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBPriestessLevelStats * pOther = dynamic_cast< const DBPriestessLevelStats * > ( _pResource );
		if ( pOther ) DBPriestessLevelStats::Assign( *pOther );
	}
};

struct DBPriestessStats : public DbResource
{
	DBRESOURCE_METHODS( DBPriestessStats );
public:
	vector< Ptr< DBPriestessLevelStats > > stats;
	int comboNafta;
	int coinNafta;
	int heartsForLevelsStartsFrom;
	vector< float > wonGameHearts;

	DBPriestessStats();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBPriestessStats& operator = ( const DBPriestessStats &_dBPriestessStats ) { Assign( _dBPriestessStats ); return *this; }
	DBPriestessStats( const DBPriestessStats &_dBPriestessStats ) { Assign( _dBPriestessStats ); }
	virtual void Assign( const DBPriestessStats &_dBPriestessStats );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBPriestessStats * pOther = dynamic_cast< const DBPriestessStats * > ( _pResource );
		if ( pOther ) DBPriestessStats::Assign( *pOther );
	}
};

}; // namespace NDb
