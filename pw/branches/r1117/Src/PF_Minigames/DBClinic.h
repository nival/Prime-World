#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;

namespace NDb
{
struct AnimGraphCreator;
struct BaseUIMaterial;
struct DBSceneObject;
struct Sound2D;
struct UIObjectOvertips;

enum EBonusType
{
	BONUSTYPE_BROOM = 0,
	BONUSTYPE_COMFORTABLEPILLOW = 1,
	BONUSTYPE_BOOKLET = 2,
	BONUSTYPE_COMFORTABLETABLE = 3,
	BONUSTYPE_BELL = 4,
	BONUSTYPE_FOOTPATHS = 5,
	BONUSTYPE_WHIP = 6,
	BONUSTYPE_VELVETGLOVES = 7,
	BONUSTYPE_ADVENCEDENTRACE = 8,
	BONUSTYPE_CANDY = 9,
	BONUSTYPE_TALISMAN = 10,
	BONUSTYPE_TOYBOX = 11,
	BONUSTYPE_SPEEDBOOTS = 12,
	BONUSTYPE_COMFORTABLECARPET = 13,
	BONUSTYPE_SUPERCLEANER = 14,
	BONUSTYPE_BOOTCOVERS = 15,
	BONUSTYPE_BESTCLINIC = 16,
	BONUSTYPE_STAR = 17,
};

const char *EnumToString( const EBonusType value );
const EBonusType StringToEnum_EBonusType( const char* value );

template <>
struct KnownEnum< EBonusType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 18 };
	static const char *ToString( const EBonusType value ) { return EnumToString( value ); }
	static const EBonusType ToEnum( const char* value ) { return StringToEnum_EBonusType( value ); }
	static const EBonusType ToEnum( const string& value ) { return StringToEnum_EBonusType( value.c_str() ); }
	static const int SizeOf() { return 18; }
};

enum EClinicSounds
{
	CLINICSOUNDS_STARTLEVEL = 0,
	CLINICSOUNDS_LEVELWINWITHMEDAL = 1,
	CLINICSOUNDS_LEVELWINWITHOUTMEDAL = 2,
	CLINICSOUNDS_CREEPWISHMELEE = 3,
	CLINICSOUNDS_CREEPWISHRANGED = 4,
	CLINICSOUNDS_CREEPWISHSIEGE = 5,
	CLINICSOUNDS_CREEPWISHDESIREDMELEE = 6,
	CLINICSOUNDS_CREEPWISHDESIREDRANGED = 7,
	CLINICSOUNDS_CREEPWISHDESIREDSIEGE = 8,
	CLINICSOUNDS_CREEPBECOMELAZY = 9,
	CLINICSOUNDS_CREEPLOOSEWISH = 10,
	CLINICSOUNDS_USETABLE = 11,
	CLINICSOUNDS_USEWASHTAB = 12,
	CLINICSOUNDS_USEBAD = 13,
	CLINICSOUNDS_USEPLAYGROUND = 14,
	CLINICSOUNDS_CREEPFRIENDSHIP = 15,
	CLINICSOUNDS_CREEPBAR25 = 16,
	CLINICSOUNDS_CREEPBAR50 = 17,
	CLINICSOUNDS_CREEPWAKEUP = 18,
	CLINICSOUNDS_PLACEBECOMEDIRTY = 19,
	CLINICSOUNDS_BUY = 20,
};

const char *EnumToString( const EClinicSounds value );
const EClinicSounds StringToEnum_EClinicSounds( const char* value );

template <>
struct KnownEnum< EClinicSounds >
{
	enum { isKnown = 1 };
	enum { sizeOf = 21 };
	static const char *ToString( const EClinicSounds value ) { return EnumToString( value ); }
	static const EClinicSounds ToEnum( const char* value ) { return StringToEnum_EClinicSounds( value ); }
	static const EClinicSounds ToEnum( const string& value ) { return StringToEnum_EClinicSounds( value.c_str() ); }
	static const int SizeOf() { return 21; }
};

enum ECreepState
{
	CREEPSTATE_WORKING = 0,
	CREEPSTATE_SLEEPING = 1,
	CREEPSTATE_NEEDWASH = 2,
};

const char *EnumToString( const ECreepState value );
const ECreepState StringToEnum_ECreepState( const char* value );

template <>
struct KnownEnum< ECreepState >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ECreepState value ) { return EnumToString( value ); }
	static const ECreepState ToEnum( const char* value ) { return StringToEnum_ECreepState( value ); }
	static const ECreepState ToEnum( const string& value ) { return StringToEnum_ECreepState( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ECreepWish
{
	CREEPWISH_NONE = 0,
	CREEPWISH_SLEEP = 1,
	CREEPWISH_WASH = 2,
	CREEPWISH_EAT = 3,
	CREEPWISH_PLAY = 4,
	CREEPWISH_CARPET = 5,
	CREEPWISH_ANY = 6,
	CREEPWISH_EXIT = 7,
};

const char *EnumToString( const ECreepWish value );
const ECreepWish StringToEnum_ECreepWish( const char* value );

template <>
struct KnownEnum< ECreepWish >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const ECreepWish value ) { return EnumToString( value ); }
	static const ECreepWish ToEnum( const char* value ) { return StringToEnum_ECreepWish( value ); }
	static const ECreepWish ToEnum( const string& value ) { return StringToEnum_ECreepWish( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum EPlaceType
{
	PLACETYPE_NONE = 0,
	PLACETYPE_TABLE = 1,
	PLACETYPE_BAD = 2,
	PLACETYPE_WASHTAB = 3,
	PLACETYPE_GAMEPLACE = 4,
	PLACETYPE_CREEPPLACE = 5,
	PLACETYPE_ENTRANCE = 6,
};

const char *EnumToString( const EPlaceType value );
const EPlaceType StringToEnum_EPlaceType( const char* value );

template <>
struct KnownEnum< EPlaceType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EPlaceType value ) { return EnumToString( value ); }
	static const EPlaceType ToEnum( const char* value ) { return StringToEnum_EPlaceType( value ); }
	static const EPlaceType ToEnum( const string& value ) { return StringToEnum_EPlaceType( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

struct BonusDesc
{
public:
	CTextRef description;
	CTextRef name;
	CVec3 position;
	float cooldown;
	float duration;
	int accessibility;
	int cost;
	int useCost;
	float value;
	Ptr< DBSceneObject > sceneObject;
	Ptr< UIObjectOvertips > overtip;
	Ptr< BaseUIMaterial > iconMaterial;

	BonusDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreepBehaviourDesc
{
public:
	float timeBeforeSearchFriend;
	float friendshipBonus;

	CreepBehaviourDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreepPlaceDesc
{
public:
	CVec3 position;

	CreepPlaceDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreepsDesc
{
public:
	Ptr< DBSceneObject > sceneObjectMelee;
	Ptr< DBSceneObject > sceneObjectRange;
	Ptr< DBSceneObject > sceneObjectSiege;
	Ptr< BaseUIMaterial > imageMeleeMaterial;
	Ptr< BaseUIMaterial > imageRangeMaterial;
	Ptr< BaseUIMaterial > imageSiegeMaterial;
	Ptr< UIObjectOvertips > overtip;
	float goldMedalValue;
	float silverMedalValue;
	vector< CreepPlaceDesc > creepPlaces;

	CreepsDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DecorationDesc
{
public:
	CVec3 position;
	Ptr< DBSceneObject > sceneObject;

	DecorationDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct IntOffsets
{
public:
	int pxBefore;
	int pxAfter;

	IntOffsets();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LevelDesc
{
public:
	int expToOpen;
	float levelFinishBonus;
	float creepTraindedBonus;
	int levelFinishMoney;
	int creepMedalMoney;
	float duration;
	CTextRef name;
	CTextRef description;
	int numberOfMelee;
	int numberOfRange;
	int numberOfSiege;
	bool casualWishGeneration;

	LevelDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MinigameUIStylesDesc
{
public:
	vector< Ptr< BaseUIMaterial > > creepWishMaterials;
	vector< Ptr< BaseUIMaterial > > creepStateMaterials;
	vector< Ptr< BaseUIMaterial > > creepFriendshipMaterials;
	float creepsAppearPause;
	float creepAppearTime;
	float creepMedalAppearTime;
	float medalAppearPause;
	float medalAppearTime;
	float naftaAnimationSpeed;

	MinigameUIStylesDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct NeighbourhoodDesc
{
public:
	int first;
	int second;

	NeighbourhoodDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PlaceDesc
{
public:
	EPlaceType placeType;
	CVec3 position;
	Ptr< DBSceneObject > sceneObject;
	Ptr< DBSceneObject > sceneObjectDirty50;
	Ptr< UIObjectOvertips > overtip;
	int accessibility;
	int cost;
	CTextRef name;
	CTextRef description;
	Ptr< BaseUIMaterial > iconMaterial;

	PlaceDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PlayerDesc
{
public:
	CVec3 startPosition;
	float velocity;
	float scaleFactor;
	Ptr< AnimGraphCreator > animationGraph;

	PlayerDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Preselection
{
public:
	Render::HDRColor colorNotBought;
	Render::HDRColor colorNotBoughtUnavailable;
	Render::HDRColor colorNotBoughtPreselect;
	Render::HDRColor colorPreselect;

	Preselection();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TrainingBonuses
{
public:
	vector< float > statLifeBar50;
	vector< float > statLifeBar59;
	vector< float > statLifeBar69;
	vector< float > statLifeBar79;
	vector< float > statLifeBar89;
	vector< float > statLifeBar100;

	TrainingBonuses();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBMinigame_Clinic : public DbResource
{
	DBRESOURCE_METHODS( DBMinigame_Clinic );
public:
	CTextRef title;
	ViewCamera cameraOptions;
	vector< Ptr< Sound2D > > sounds;
	vector< Ptr< Sound2D > > bonusSounds;
	Preselection preselection;
	PlayerDesc player;
	vector< BonusDesc > bonuses;
	vector< PlaceDesc > places;
	Ptr< DBSceneObject > sceneObjectDirty100;
	vector< NeighbourhoodDesc > neighbourhood;
	vector< LevelDesc > levels;
	vector< DecorationDesc > decorations;
	CreepsDesc creepsDesc;
	CreepBehaviourDesc creepBehaviourDesc;
	TrainingBonuses trainingBonuses;
	float soilPersentMelee;
	float soilPersentRange;
	float soilPersentSiege;
	int clickBonusClickCount;
	float clickBonusValue;
	float heartsBonus;
	float minTimeBetweenCreeps;
	float maxTimeBetweenCreeps;
	float minThinkTime;
	float maxThinkTime;
	float waitTime;
	float fallAsleepTime;
	float wakeupTime;
	float workTime;
	float workBonus;
	float failBonus;
	float level1_BarValue;
	float level3_phase1Min;
	float level3_phase1Max;
	float level4_washProbTimes;
	float level5_fallAsleepTime;
	float level6_soilAtStart;
	float level8_timeReduction;
	float level8_bonusReduction;
	float level9_washProb;
	float level10_playProbTimes;
	float level11_soilIncrease;
	float level12_soilIncrease;
	float level12_bonusReduction;
	float level12_waitDecrease;
	MinigameUIStylesDesc uiStyles;

	DBMinigame_Clinic();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBMinigame_Clinic& operator = ( const DBMinigame_Clinic &_dBMinigame_Clinic ) { Assign( _dBMinigame_Clinic ); return *this; }
	DBMinigame_Clinic( const DBMinigame_Clinic &_dBMinigame_Clinic ) { Assign( _dBMinigame_Clinic ); }
	virtual void Assign( const DBMinigame_Clinic &_dBMinigame_Clinic );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBMinigame_Clinic * pOther = dynamic_cast< const DBMinigame_Clinic * > ( _pResource );
		if ( pOther ) DBMinigame_Clinic::Assign( *pOther );
	}
};

}; // namespace NDb
