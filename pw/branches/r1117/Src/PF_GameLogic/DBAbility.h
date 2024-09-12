#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAnimations.h"
#include "../PF_GameLogic/DBDayNight.h"
#include "../PF_GameLogic/DBStats.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;
// forward declarations for factories
namespace NWorld
{
	class PFBaseApplicator;
	class PFApplCreatePars;
	class PFTargetSelector;
	class PFWorld;
	class PFMicroAI;
	class PFMicroAICreateParams;
	class PFAbilityData;
	class CastLimitationsCheckParams;
	class PFDispatch;
	class PFDispatchCreateParams;
	class PFEventProcessorBase;
	class PFSummonBehaviourDataBase;
}; //namespace NWorld

namespace NDb
{
struct Ability;
struct AlternativeActivity;
struct AlternativeTarget;
struct AnimSet;
struct AOEMaterial;
struct ApplicatorsList;
struct BaseApplicator;
struct BaseAttack;
struct BuffApplicator;
struct CastLimitation;
struct ConditionFormula;
struct Consumable;
struct DBSceneObject;
struct DelegateDamageApplicator;
struct Dispatch;
struct EffectBase;
struct EventProcessorBase;
struct Glyph;
struct LightningEffect;
struct MicroAI;
struct MultipleTargetSelector;
struct ProgramApplicator;
struct SingleTargetSelector;
struct Spell;
struct SummonBehaviourBase;
struct Summoned;
struct TargetSelector;
struct Texture;
struct UIEvent;
struct Unit;
struct UnitConstant;
struct UnitConstantsContainer;
struct UnitTargetingParameters;

enum EAbility
{
	ABILITY_ID_STATS = 0,
	ABILITY_ID_1 = 1,
	ABILITY_ID_2 = 2,
	ABILITY_ID_3 = 3,
	ABILITY_ID_4 = 4,
};

const char *EnumToString( const EAbility value );
const EAbility StringToEnum_EAbility( const char* value );

template <>
struct KnownEnum< EAbility >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EAbility value ) { return EnumToString( value ); }
	static const EAbility ToEnum( const char* value ) { return StringToEnum_EAbility( value ); }
	static const EAbility ToEnum( const string& value ) { return StringToEnum_EAbility( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EAbilityAOEVisual
{
	ABILITYAOEVISUAL_NONE = 0,
	ABILITYAOEVISUAL_DISK = 1,
	ABILITYAOEVISUAL_CONE = 2,
	ABILITYAOEVISUAL_CORRIDOR = 3,
	ABILITYAOEVISUAL_CORRIDORMAX = 4,
	ABILITYAOEVISUAL_UNATTACHEDSECTOR = 5,
	ABILITYAOEVISUAL_WALL = 6,
	ABILITYAOEVISUAL_ATTACHEDSECTOR = 7,
};

const char *EnumToString( const EAbilityAOEVisual value );
const EAbilityAOEVisual StringToEnum_EAbilityAOEVisual( const char* value );

template <>
struct KnownEnum< EAbilityAOEVisual >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const EAbilityAOEVisual value ) { return EnumToString( value ); }
	static const EAbilityAOEVisual ToEnum( const char* value ) { return StringToEnum_EAbilityAOEVisual( value ); }
	static const EAbilityAOEVisual ToEnum( const string& value ) { return StringToEnum_EAbilityAOEVisual( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum EAbilityCostMode
{
	ABILITYCOSTMODE_ENERGY = 0,
	ABILITYCOSTMODE_LIFE = 1,
	ABILITYCOSTMODE_ANY = 2,
	ABILITYCOSTMODE_CUSTOM = 3,
};

const char *EnumToString( const EAbilityCostMode value );
const EAbilityCostMode StringToEnum_EAbilityCostMode( const char* value );

template <>
struct KnownEnum< EAbilityCostMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EAbilityCostMode value ) { return EnumToString( value ); }
	static const EAbilityCostMode ToEnum( const char* value ) { return StringToEnum_EAbilityCostMode( value ); }
	static const EAbilityCostMode ToEnum( const string& value ) { return StringToEnum_EAbilityCostMode( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EAbilityFlags
{
	ABILITYFLAGS_FOCUSONTARGET = 1,
	ABILITYFLAGS_MOMENTARY = 2,
	ABILITYFLAGS_APPLYTODEAD = 4,
	ABILITYFLAGS_MIRROREDBYCLONE = 8,
	ABILITYFLAGS_STAYINVISIBLE = 16,
	ABILITYFLAGS_CHANNELINGCREATE = 32,
	ABILITYFLAGS_CANUSEOUTOFRANGE = 64,
	ABILITYFLAGS_DONTOPENWARFOG = 128,
	ABILITYFLAGS_INSTACAST = 256,
	ABILITYFLAGS_MOVING = 512,
	ABILITYFLAGS_USEATTACKTARGET = 1024,
	ABILITYFLAGS_WAITFORCHANNELING = 2048,
	ABILITYFLAGS_FOCUSINSTANTLY = 4096,
	ABILITYFLAGS_MINIMAPTARGETMUSTBEALTERNATIVE = 8192,
	ABILITYFLAGS_SPENDLIFEINSTEADENERGY = 16384,
	ABILITYFLAGS_SELFCASTING = 32768,
	ABILITYFLAGS_FORCEDONOTSTOPUNIT = 65536,
};

const char *EnumToString( const EAbilityFlags value );
const EAbilityFlags StringToEnum_EAbilityFlags( const char* value );

template <>
struct KnownEnum< EAbilityFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 17 };
	static const char *ToString( const EAbilityFlags value ) { return EnumToString( value ); }
	static const EAbilityFlags ToEnum( const char* value ) { return StringToEnum_EAbilityFlags( value ); }
	static const EAbilityFlags ToEnum( const string& value ) { return StringToEnum_EAbilityFlags( value.c_str() ); }
	static const int SizeOf() { return 17; }
};

enum EAbilityIdFlags
{
	ABILITYIDFLAGS_SPECIFIC = 0,
	ABILITYIDFLAGS_BASEATTACK = 1,
	ABILITYIDFLAGS_ABILITY1 = 4,
	ABILITYIDFLAGS_ABILITY2 = 8,
	ABILITYIDFLAGS_ABILITY3 = 16,
	ABILITYIDFLAGS_ABILITY4 = 32,
	ABILITYIDFLAGS_CONSUMABLES = 64,
	ABILITYIDFLAGS_TALENTS = 128,
	ABILITYIDFLAGS_PORTAL = 2048,
	ABILITYIDFLAGS_ALL = 2301,
};

const char *EnumToString( const EAbilityIdFlags value );
const EAbilityIdFlags StringToEnum_EAbilityIdFlags( const char* value );

template <>
struct KnownEnum< EAbilityIdFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 10 };
	static const char *ToString( const EAbilityIdFlags value ) { return EnumToString( value ); }
	static const EAbilityIdFlags ToEnum( const char* value ) { return StringToEnum_EAbilityIdFlags( value ); }
	static const EAbilityIdFlags ToEnum( const string& value ) { return StringToEnum_EAbilityIdFlags( value.c_str() ); }
	static const int SizeOf() { return 10; }
};

enum EAbilityModMode
{
	ABILITYMODMODE_NAFTACOST = 0,
	ABILITYMODMODE_MANACOST = 1,
	ABILITYMODMODE_COOLDOWN = 2,
	ABILITYMODMODE_SCALE = 3,
	ABILITYMODMODE_DURATION = 4,
	ABILITYMODMODE_STATE = 5,
};

const char *EnumToString( const EAbilityModMode value );
const EAbilityModMode StringToEnum_EAbilityModMode( const char* value );

template <>
struct KnownEnum< EAbilityModMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EAbilityModMode value ) { return EnumToString( value ); }
	static const EAbilityModMode ToEnum( const char* value ) { return StringToEnum_EAbilityModMode( value ); }
	static const EAbilityModMode ToEnum( const string& value ) { return StringToEnum_EAbilityModMode( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EAbilityType
{
	ABILITYTYPE_SIMPLE = 0,
	ABILITYTYPE_ACTIVE = 1,
	ABILITYTYPE_MULTIACTIVE = 2,
	ABILITYTYPE_PASSIVE = 3,
	ABILITYTYPE_AUTOCASTABLE = 4,
	ABILITYTYPE_SWITCHABLE = 5,
	ABILITYTYPE_CHANNELLING = 6,
};

const char *EnumToString( const EAbilityType value );
const EAbilityType StringToEnum_EAbilityType( const char* value );

template <>
struct KnownEnum< EAbilityType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EAbilityType value ) { return EnumToString( value ); }
	static const EAbilityType ToEnum( const char* value ) { return StringToEnum_EAbilityType( value ); }
	static const EAbilityType ToEnum( const string& value ) { return StringToEnum_EAbilityType( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EAbilityTypeId
{
	ABILITYTYPEID_BASEATTACK = 0,
	ABILITYTYPEID_ABILITY0 = 1,
	ABILITYTYPEID_ABILITY1 = 2,
	ABILITYTYPEID_ABILITY2 = 3,
	ABILITYTYPEID_ABILITY3 = 4,
	ABILITYTYPEID_ABILITY4 = 5,
	ABILITYTYPEID_CONSUMABLE = 6,
	ABILITYTYPEID_TALENT = 7,
	ABILITYTYPEID_TALENTFROMLIST = 8,
	ABILITYTYPEID_IMPULSIVEBUFF = 9,
	ABILITYTYPEID_SPECIAL = 10,
	ABILITYTYPEID_PORTAL = 11,
};

const char *EnumToString( const EAbilityTypeId value );
const EAbilityTypeId StringToEnum_EAbilityTypeId( const char* value );

template <>
struct KnownEnum< EAbilityTypeId >
{
	enum { isKnown = 1 };
	enum { sizeOf = 12 };
	static const char *ToString( const EAbilityTypeId value ) { return EnumToString( value ); }
	static const EAbilityTypeId ToEnum( const char* value ) { return StringToEnum_EAbilityTypeId( value ); }
	static const EAbilityTypeId ToEnum( const string& value ) { return StringToEnum_EAbilityTypeId( value.c_str() ); }
	static const int SizeOf() { return 12; }
};

enum EAbilityUpgradeMode
{
	ABILITYUPGRADEMODE_NONE = 0,
	ABILITYUPGRADEMODE_DONTUSEORIGINAL = 1,
	ABILITYUPGRADEMODE_USEABILITYMANA = 2,
	ABILITYUPGRADEMODE_USEABILITYCOOLDOWN = 4,
	ABILITYUPGRADEMODE_USEGLYPH = 8,
	ABILITYUPGRADEMODE_CHANGEICON = 16,
	ABILITYUPGRADEMODE_APPLYONCEPERCAST = 32,
	ABILITYUPGRADEMODE_APPLYONCEPERCASTPERTARGET = 64,
};

const char *EnumToString( const EAbilityUpgradeMode value );
const EAbilityUpgradeMode StringToEnum_EAbilityUpgradeMode( const char* value );

template <>
struct KnownEnum< EAbilityUpgradeMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const EAbilityUpgradeMode value ) { return EnumToString( value ); }
	static const EAbilityUpgradeMode ToEnum( const char* value ) { return StringToEnum_EAbilityUpgradeMode( value ); }
	static const EAbilityUpgradeMode ToEnum( const string& value ) { return StringToEnum_EAbilityUpgradeMode( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum EApplicatorAppliedMode
{
	APPLICATORAPPLIEDMODE_DEFAULT = 0,
	APPLICATORAPPLIEDMODE_CANCEL = 1,
	APPLICATORAPPLIEDMODE_SETNEWLIFETIME = 2,
};

const char *EnumToString( const EApplicatorAppliedMode value );
const EApplicatorAppliedMode StringToEnum_EApplicatorAppliedMode( const char* value );

template <>
struct KnownEnum< EApplicatorAppliedMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EApplicatorAppliedMode value ) { return EnumToString( value ); }
	static const EApplicatorAppliedMode ToEnum( const char* value ) { return StringToEnum_EApplicatorAppliedMode( value ); }
	static const EApplicatorAppliedMode ToEnum( const string& value ) { return StringToEnum_EApplicatorAppliedMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EApplicatorApplyTarget
{
	APPLICATORAPPLYTARGET_APPLICATORTARGET = 0,
	APPLICATORAPPLYTARGET_ABILITYOWNER = 1,
	APPLICATORAPPLYTARGET_PREVAPPLICATORTARGET = 2,
	APPLICATORAPPLYTARGET_PREVAPPLICATORRECEIVER = 3,
	APPLICATORAPPLYTARGET_HIER1UPAPPLICATORTARGET = 4,
	APPLICATORAPPLYTARGET_HIER2UPAPPLICATORTARGET = 5,
	APPLICATORAPPLYTARGET_HIER3UPAPPLICATORTARGET = 6,
	APPLICATORAPPLYTARGET_ABILITYTARGET = 7,
	APPLICATORAPPLYTARGET_APPLICATORSELECTEDTARGET = 8,
	APPLICATORAPPLYTARGET_CASTPOSITION = 9,
	APPLICATORAPPLYTARGET_CASTMASTERPOSITION = 10,
};

const char *EnumToString( const EApplicatorApplyTarget value );
const EApplicatorApplyTarget StringToEnum_EApplicatorApplyTarget( const char* value );

template <>
struct KnownEnum< EApplicatorApplyTarget >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EApplicatorApplyTarget value ) { return EnumToString( value ); }
	static const EApplicatorApplyTarget ToEnum( const char* value ) { return StringToEnum_EApplicatorApplyTarget( value ); }
	static const EApplicatorApplyTarget ToEnum( const string& value ) { return StringToEnum_EApplicatorApplyTarget( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum EApplicatorDamageType
{
	APPLICATORDAMAGETYPE_MATERIAL = 0,
	APPLICATORDAMAGETYPE_ENERGY = 1,
	APPLICATORDAMAGETYPE_MANA = 2,
	APPLICATORDAMAGETYPE_PURE = 3,
	APPLICATORDAMAGETYPE_NATIVE = 4,
};

const char *EnumToString( const EApplicatorDamageType value );
const EApplicatorDamageType StringToEnum_EApplicatorDamageType( const char* value );

template <>
struct KnownEnum< EApplicatorDamageType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EApplicatorDamageType value ) { return EnumToString( value ); }
	static const EApplicatorDamageType ToEnum( const char* value ) { return StringToEnum_EApplicatorDamageType( value ); }
	static const EApplicatorDamageType ToEnum( const string& value ) { return StringToEnum_EApplicatorDamageType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EApplyEffectOrientation
{
	APPLYEFFECTORIENTATION_DEFAULT = 0,
	APPLYEFFECTORIENTATION_RANDOM = 1,
	APPLYEFFECTORIENTATION_MOTION = 2,
	APPLYEFFECTORIENTATION_LOGICALDIRECTION = 3,
};

const char *EnumToString( const EApplyEffectOrientation value );
const EApplyEffectOrientation StringToEnum_EApplyEffectOrientation( const char* value );

template <>
struct KnownEnum< EApplyEffectOrientation >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EApplyEffectOrientation value ) { return EnumToString( value ); }
	static const EApplyEffectOrientation ToEnum( const char* value ) { return StringToEnum_EApplyEffectOrientation( value ); }
	static const EApplyEffectOrientation ToEnum( const string& value ) { return StringToEnum_EApplyEffectOrientation( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EAttackersType
{
	ATTACKERSTYPE_TARGETERS = 0,
	ATTACKERSTYPE_DAMAGEDEALERS = 1,
};

const char *EnumToString( const EAttackersType value );
const EAttackersType StringToEnum_EAttackersType( const char* value );

template <>
struct KnownEnum< EAttackersType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EAttackersType value ) { return EnumToString( value ); }
	static const EAttackersType ToEnum( const char* value ) { return StringToEnum_EAttackersType( value ); }
	static const EAttackersType ToEnum( const string& value ) { return StringToEnum_EAttackersType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EAttackTargetEvadeAction
{
	ATTACKTARGETEVADEACTION_ATTACKAGAIN = 0,
	ATTACKTARGETEVADEACTION_STOPASCOMPLETE = 1,
	ATTACKTARGETEVADEACTION_STOPASFAILED = 2,
};

const char *EnumToString( const EAttackTargetEvadeAction value );
const EAttackTargetEvadeAction StringToEnum_EAttackTargetEvadeAction( const char* value );

template <>
struct KnownEnum< EAttackTargetEvadeAction >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAttackTargetEvadeAction value ) { return EnumToString( value ); }
	static const EAttackTargetEvadeAction ToEnum( const char* value ) { return StringToEnum_EAttackTargetEvadeAction( value ); }
	static const EAttackTargetEvadeAction ToEnum( const string& value ) { return StringToEnum_EAttackTargetEvadeAction( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EAuraVisualType
{
	AURAVISUALTYPE_NONE = 0,
	AURAVISUALTYPE_ALLY = 1,
	AURAVISUALTYPE_ENEMY = 2,
};

const char *EnumToString( const EAuraVisualType value );
const EAuraVisualType StringToEnum_EAuraVisualType( const char* value );

template <>
struct KnownEnum< EAuraVisualType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAuraVisualType value ) { return EnumToString( value ); }
	static const EAuraVisualType ToEnum( const char* value ) { return StringToEnum_EAuraVisualType( value ); }
	static const EAuraVisualType ToEnum( const string& value ) { return StringToEnum_EAuraVisualType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EBaseUnitEvent
{
	BASEUNITEVENT_MOVE = 0,
	BASEUNITEVENT_CASTMAGIC = 1,
	BASEUNITEVENT_USECONSUMABLE = 2,
	BASEUNITEVENT_USETALENT = 3,
	BASEUNITEVENT_ATTACK = 4,
	BASEUNITEVENT_FORBIDMOVE = 5,
	BASEUNITEVENT_FORBIDATTACK = 6,
	BASEUNITEVENT_FORBIDCAST = 7,
	BASEUNITEVENT_FORCEDMOVE = 8,
	BASEUNITEVENT_DISPATCHAPPLIED = 9,
	BASEUNITEVENT_DISPATCHEVADED = 10,
	BASEUNITEVENT_DAMAGE = 11,
	BASEUNITEVENT_ISOLATE = 12,
	BASEUNITEVENT_APPLICATORSTEP = 13,
	BASEUNITEVENT_APPLICATORAPPLIED = 14,
	BASEUNITEVENT_DEATH = 15,
	BASEUNITEVENT_ASSIGNTARGET = 16,
	BASEUNITEVENT_LASTHIT = 17,
	BASEUNITEVENT_FORBIDAUTOATTACK = 18,
	BASEUNITEVENT_PICKUP = 19,
	BASEUNITEVENT_RESURRECT = 20,
	BASEUNITEVENT_ABILITYSTART = 21,
	BASEUNITEVENT_CHANNELINGCANCELED = 22,
	BASEUNITEVENT_CANCELINVISIBILITY = 23,
	BASEUNITEVENT_UNSUMMON = 24,
	BASEUNITEVENT_CONSUMABLEOBTAINED = 25,
	BASEUNITEVENT_USEPORTAL = 26,
	BASEUNITEVENT_WANTMOVETO = 27,
	BASEUNITEVENT_OUTGOINGDAMAGE = 28,
	BASEUNITEVENT_DISPATCHMISSED = 29,
	BASEUNITEVENT_HEROKILLORASSIST = 30,
	BASEUNITEVENT_MINIGAMESTARTED = 31,
	BASEUNITEVENT_MINIGAMEEXIT = 32,
	BASEUNITEVENT_MINIGAMELEVELSTARTED = 33,
	BASEUNITEVENT_MINIGAMELEVELWON = 34,
	BASEUNITEVENT_MINIGAMELEVELFAILED = 35,
};

const char *EnumToString( const EBaseUnitEvent value );
const EBaseUnitEvent StringToEnum_EBaseUnitEvent( const char* value );

template <>
struct KnownEnum< EBaseUnitEvent >
{
	enum { isKnown = 1 };
	enum { sizeOf = 36 };
	static const char *ToString( const EBaseUnitEvent value ) { return EnumToString( value ); }
	static const EBaseUnitEvent ToEnum( const char* value ) { return StringToEnum_EBaseUnitEvent( value ); }
	static const EBaseUnitEvent ToEnum( const string& value ) { return StringToEnum_EBaseUnitEvent( value.c_str() ); }
	static const int SizeOf() { return 36; }
};

enum EBaseUnitEventFlags
{
	BASEUNITEVENTFLAGS_ZERO = 0,
	BASEUNITEVENTFLAGS_MOVE = 1,
	BASEUNITEVENTFLAGS_CASTMAGIC = 2,
	BASEUNITEVENTFLAGS_USECONSUMABLE = 4,
	BASEUNITEVENTFLAGS_USETALENT = 8,
	BASEUNITEVENTFLAGS_ATTACK = 16,
	BASEUNITEVENTFLAGS_FORBIDMOVE = 32,
	BASEUNITEVENTFLAGS_FORBIDATTACK = 64,
	BASEUNITEVENTFLAGS_FORBIDCAST = 128,
	BASEUNITEVENTFLAGS_FORCEDMOVE = 256,
	BASEUNITEVENTFLAGS_DISPATCHAPPLIED = 512,
	BASEUNITEVENTFLAGS_DISPATCHEVADED = 1024,
	BASEUNITEVENTFLAGS_DAMAGE = 2048,
	BASEUNITEVENTFLAGS_ISOLATE = 4096,
	BASEUNITEVENTFLAGS_APPLICATORSTEP = 8192,
	BASEUNITEVENTFLAGS_APPLICATORAPPLIED = 16384,
	BASEUNITEVENTFLAGS_DEATH = 32768,
	BASEUNITEVENTFLAGS_ASSIGNTARGET = 65536,
	BASEUNITEVENTFLAGS_LASTHIT = 131072,
	BASEUNITEVENTFLAGS_FORBIDAUTOATTACK = 262144,
	BASEUNITEVENTFLAGS_PICKUP = 524288,
	BASEUNITEVENTFLAGS_RESURRECT = 1048576,
	BASEUNITEVENTFLAGS_ABILITYSTART = 2097152,
	BASEUNITEVENTFLAGS_CHANNELINGCANCELED = 4194304,
	BASEUNITEVENTFLAGS_CANCELINVISIBILITY = 8388608,
	BASEUNITEVENTFLAGS_UNSUMMON = 16777216,
	BASEUNITEVENTFLAGS_USEPORTAL = 67108864,
	BASEUNITEVENTFLAGS_DISPATCHMISSED = 536870912,
	BASEUNITEVENTFLAGS_HEROKILLORASSIST = 1073741824,
};

const char *EnumToString( const EBaseUnitEventFlags value );
const EBaseUnitEventFlags StringToEnum_EBaseUnitEventFlags( const char* value );

template <>
struct KnownEnum< EBaseUnitEventFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 29 };
	static const char *ToString( const EBaseUnitEventFlags value ) { return EnumToString( value ); }
	static const EBaseUnitEventFlags ToEnum( const char* value ) { return StringToEnum_EBaseUnitEventFlags( value ); }
	static const EBaseUnitEventFlags ToEnum( const string& value ) { return StringToEnum_EBaseUnitEventFlags( value.c_str() ); }
	static const int SizeOf() { return 29; }
};

enum EBehaviourChangeFlags
{
	BEHAVIOURCHANGEFLAGS_ZERO = 0,
	BEHAVIOURCHANGEFLAGS_DUMMYBEHAVIOUR = 1,
	BEHAVIOURCHANGEFLAGS_CHANGEFACTION = 2,
	BEHAVIOURCHANGEFLAGS_PRIMARYSUMMON = 4,
	BEHAVIOURCHANGEFLAGS_CHANGEPERMANENTLY = 8,
	BEHAVIOURCHANGEFLAGS_CHANGETYPE2SUMMON = 16,
	BEHAVIOURCHANGEFLAGS_DISABLEBEHAVIOUR = 32,
};

const char *EnumToString( const EBehaviourChangeFlags value );
const EBehaviourChangeFlags StringToEnum_EBehaviourChangeFlags( const char* value );

template <>
struct KnownEnum< EBehaviourChangeFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EBehaviourChangeFlags value ) { return EnumToString( value ); }
	static const EBehaviourChangeFlags ToEnum( const char* value ) { return StringToEnum_EBehaviourChangeFlags( value ); }
	static const EBehaviourChangeFlags ToEnum( const string& value ) { return StringToEnum_EBehaviourChangeFlags( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EBetweenUnitsMode
{
	BETWEENUNITSMODE_ALLPAIRS = 0,
	BETWEENUNITSMODE_CHAIN = 1,
};

const char *EnumToString( const EBetweenUnitsMode value );
const EBetweenUnitsMode StringToEnum_EBetweenUnitsMode( const char* value );

template <>
struct KnownEnum< EBetweenUnitsMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EBetweenUnitsMode value ) { return EnumToString( value ); }
	static const EBetweenUnitsMode ToEnum( const char* value ) { return StringToEnum_EBetweenUnitsMode( value ); }
	static const EBetweenUnitsMode ToEnum( const string& value ) { return StringToEnum_EBetweenUnitsMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EBounceFlags
{
	BOUNCEFLAGS_BOUNCENEXTTARGETONLOSS = 1,
	BOUNCEFLAGS_RENEWTARGETONSTART = 2,
	BOUNCEFLAGS_STARTFROMOWNER = 4,
};

const char *EnumToString( const EBounceFlags value );
const EBounceFlags StringToEnum_EBounceFlags( const char* value );

template <>
struct KnownEnum< EBounceFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EBounceFlags value ) { return EnumToString( value ); }
	static const EBounceFlags ToEnum( const char* value ) { return StringToEnum_EBounceFlags( value ); }
	static const EBounceFlags ToEnum( const string& value ) { return StringToEnum_EBounceFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EBuffBehavior
{
	BUFFBEHAVIOR_ZERO = 0,
	BUFFBEHAVIOR_STOPONDISABLE = 1,
	BUFFBEHAVIOR_REMOVECHILDREN = 2,
	BUFFBEHAVIOR_DONTSHOWINBAR = 4,
	BUFFBEHAVIOR_DONTSTOPONDEATH = 8,
	BUFFBEHAVIOR_ENABLEDONSENDERDEATH = 16,
	BUFFBEHAVIOR_DONTREMOVEEFFECT = 32,
	BUFFBEHAVIOR_APPLYTODEAD = 64,
	BUFFBEHAVIOR_DONTSTOPONSENDERDEATH = 128,
};

const char *EnumToString( const EBuffBehavior value );
const EBuffBehavior StringToEnum_EBuffBehavior( const char* value );

template <>
struct KnownEnum< EBuffBehavior >
{
	enum { isKnown = 1 };
	enum { sizeOf = 9 };
	static const char *ToString( const EBuffBehavior value ) { return EnumToString( value ); }
	static const EBuffBehavior ToEnum( const char* value ) { return StringToEnum_EBuffBehavior( value ); }
	static const EBuffBehavior ToEnum( const string& value ) { return StringToEnum_EBuffBehavior( value.c_str() ); }
	static const int SizeOf() { return 9; }
};

enum EChannelingType
{
	CHANNELINGTYPE_STREAMING = 0,
	CHANNELINGTYPE_CREATION = 1,
};

const char *EnumToString( const EChannelingType value );
const EChannelingType StringToEnum_EChannelingType( const char* value );

template <>
struct KnownEnum< EChannelingType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EChannelingType value ) { return EnumToString( value ); }
	static const EChannelingType ToEnum( const char* value ) { return StringToEnum_EChannelingType( value ); }
	static const EChannelingType ToEnum( const string& value ) { return StringToEnum_EChannelingType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ECloneFlags
{
	CLONEFLAGS_NONE = 0,
	CLONEFLAGS_GHOSTMOVE = 1,
	CLONEFLAGS_DOLEVELUP = 2,
	CLONEFLAGS_MIRROROWNERSPELLS = 4,
	CLONEFLAGS_USEABILITYAI = 8,
	CLONEFLAGS_PLAYSUMMONEFFECT = 16,
	CLONEFLAGS_MAKESLAVE = 32,
	CLONEFLAGS_COPYSTATS = 64,
	CLONEFLAGS_DUMMYBEHAVIOUR = 128,
	CLONEFLAGS_INITTALENTS = 256,
};

const char *EnumToString( const ECloneFlags value );
const ECloneFlags StringToEnum_ECloneFlags( const char* value );

template <>
struct KnownEnum< ECloneFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 10 };
	static const char *ToString( const ECloneFlags value ) { return EnumToString( value ); }
	static const ECloneFlags ToEnum( const char* value ) { return StringToEnum_ECloneFlags( value ); }
	static const ECloneFlags ToEnum( const string& value ) { return StringToEnum_ECloneFlags( value.c_str() ); }
	static const int SizeOf() { return 10; }
};

enum EConsumableOriginFlags
{
	CONSUMABLEORIGINFLAGS_SHOP = 2,
	CONSUMABLEORIGINFLAGS_MINIGAME = 4,
	CONSUMABLEORIGINFLAGS_PICKUPABLE = 8,
	CONSUMABLEORIGINFLAGS_APPLICATOR = 16,
	CONSUMABLEORIGINFLAGS_SCRIPT = 32,
};

const char *EnumToString( const EConsumableOriginFlags value );
const EConsumableOriginFlags StringToEnum_EConsumableOriginFlags( const char* value );

template <>
struct KnownEnum< EConsumableOriginFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EConsumableOriginFlags value ) { return EnumToString( value ); }
	static const EConsumableOriginFlags ToEnum( const char* value ) { return StringToEnum_EConsumableOriginFlags( value ); }
	static const EConsumableOriginFlags ToEnum( const string& value ) { return StringToEnum_EConsumableOriginFlags( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EDamageFilter
{
	DAMAGEFILTER_ZERO = 0,
	DAMAGEFILTER_MELEE = 1,
	DAMAGEFILTER_RANGED = 2,
	DAMAGEFILTER_MATERIAL = 4,
	DAMAGEFILTER_ENERGY = 8,
	DAMAGEFILTER_PURE = 16,
	DAMAGEFILTER_ALL = 31,
};

const char *EnumToString( const EDamageFilter value );
const EDamageFilter StringToEnum_EDamageFilter( const char* value );

template <>
struct KnownEnum< EDamageFilter >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EDamageFilter value ) { return EnumToString( value ); }
	static const EDamageFilter ToEnum( const char* value ) { return StringToEnum_EDamageFilter( value ); }
	static const EDamageFilter ToEnum( const string& value ) { return StringToEnum_EDamageFilter( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EDamageMode
{
	DAMAGEMODE_ZERO = 0,
	DAMAGEMODE_APPLYLIFEDRAINS = 1,
	DAMAGEMODE_APPLYENERGYDRAINS = 2,
	DAMAGEMODE_DONTATTACKBACK = 4,
	DAMAGEMODE_COULDBECRITICAL = 8,
};

const char *EnumToString( const EDamageMode value );
const EDamageMode StringToEnum_EDamageMode( const char* value );

template <>
struct KnownEnum< EDamageMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EDamageMode value ) { return EnumToString( value ); }
	static const EDamageMode ToEnum( const char* value ) { return StringToEnum_EDamageMode( value ); }
	static const EDamageMode ToEnum( const string& value ) { return StringToEnum_EDamageMode( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EDelegateDamageFlags
{
	DELEGATEDAMAGEFLAGS_ALLOWDRAINS = 1,
};

const char *EnumToString( const EDelegateDamageFlags value );
const EDelegateDamageFlags StringToEnum_EDelegateDamageFlags( const char* value );

template <>
struct KnownEnum< EDelegateDamageFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const EDelegateDamageFlags value ) { return EnumToString( value ); }
	static const EDelegateDamageFlags ToEnum( const char* value ) { return StringToEnum_EDelegateDamageFlags( value ); }
	static const EDelegateDamageFlags ToEnum( const string& value ) { return StringToEnum_EDelegateDamageFlags( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

enum EDispatchAiming
{
	DISPATCHAIMING_STRAIGHT = 0,
	DISPATCHAIMING_HOMING = 1,
	DISPATCHAIMING_PURSUE = 2,
};

const char *EnumToString( const EDispatchAiming value );
const EDispatchAiming StringToEnum_EDispatchAiming( const char* value );

template <>
struct KnownEnum< EDispatchAiming >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EDispatchAiming value ) { return EnumToString( value ); }
	static const EDispatchAiming ToEnum( const char* value ) { return StringToEnum_EDispatchAiming( value ); }
	static const EDispatchAiming ToEnum( const string& value ) { return StringToEnum_EDispatchAiming( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EDispatchFlags
{
	DISPATCHFLAGS_UPGRADABLE = 1,
	DISPATCHFLAGS_EVADABLE = 2,
	DISPATCHFLAGS_AGGRESSIVE = 4,
};

const char *EnumToString( const EDispatchFlags value );
const EDispatchFlags StringToEnum_EDispatchFlags( const char* value );

template <>
struct KnownEnum< EDispatchFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EDispatchFlags value ) { return EnumToString( value ); }
	static const EDispatchFlags ToEnum( const char* value ) { return StringToEnum_EDispatchFlags( value ); }
	static const EDispatchFlags ToEnum( const string& value ) { return StringToEnum_EDispatchFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EDispatchFlyMode
{
	DISPATCHFLYMODE_PARABOLIC = 0,
	DISPATCHFLYMODE_LINEAR = 1,
	DISPATCHFLYMODE_FIXEDHEIGHT = 2,
};

const char *EnumToString( const EDispatchFlyMode value );
const EDispatchFlyMode StringToEnum_EDispatchFlyMode( const char* value );

template <>
struct KnownEnum< EDispatchFlyMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EDispatchFlyMode value ) { return EnumToString( value ); }
	static const EDispatchFlyMode ToEnum( const char* value ) { return StringToEnum_EDispatchFlyMode( value ); }
	static const EDispatchFlyMode ToEnum( const string& value ) { return StringToEnum_EDispatchFlyMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EDispatchType
{
	DISPATCHTYPE_IMMEDIATE = 0,
	DISPATCHTYPE_LINEAR = 1,
	DISPATCHTYPE_BYTIME = 2,
};

const char *EnumToString( const EDispatchType value );
const EDispatchType StringToEnum_EDispatchType( const char* value );

template <>
struct KnownEnum< EDispatchType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EDispatchType value ) { return EnumToString( value ); }
	static const EDispatchType ToEnum( const char* value ) { return StringToEnum_EDispatchType( value ); }
	static const EDispatchType ToEnum( const string& value ) { return StringToEnum_EDispatchType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EDispellPriority
{
	DISPELLPRIORITY_NONDISPELLABLE = -1,
	DISPELLPRIORITY_LOW = 0,
	DISPELLPRIORITY_MEDIUM = 1,
	DISPELLPRIORITY_HIGH = 2,
};

const char *EnumToString( const EDispellPriority value );
const EDispellPriority StringToEnum_EDispellPriority( const char* value );

template <>
struct KnownEnum< EDispellPriority >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EDispellPriority value ) { return EnumToString( value ); }
	static const EDispellPriority ToEnum( const char* value ) { return StringToEnum_EDispellPriority( value ); }
	static const EDispellPriority ToEnum( const string& value ) { return StringToEnum_EDispellPriority( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EFXFlags
{
	FXFLAGS_APPLYFXTOAUX = 1,
};

const char *EnumToString( const EFXFlags value );
const EFXFlags StringToEnum_EFXFlags( const char* value );

template <>
struct KnownEnum< EFXFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const EFXFlags value ) { return EnumToString( value ); }
	static const EFXFlags ToEnum( const char* value ) { return StringToEnum_EFXFlags( value ); }
	static const EFXFlags ToEnum( const string& value ) { return StringToEnum_EFXFlags( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

enum EGhostMoveMode
{
	GHOSTMOVEMODE_IGNOREDYNAMIC = 1,
	GHOSTMOVEMODE_IGNOREBUILDINGS = 2,
	GHOSTMOVEMODE_IGNORESTATIC = 4,
};

const char *EnumToString( const EGhostMoveMode value );
const EGhostMoveMode StringToEnum_EGhostMoveMode( const char* value );

template <>
struct KnownEnum< EGhostMoveMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EGhostMoveMode value ) { return EnumToString( value ); }
	static const EGhostMoveMode ToEnum( const char* value ) { return StringToEnum_EGhostMoveMode( value ); }
	static const EGhostMoveMode ToEnum( const string& value ) { return StringToEnum_EGhostMoveMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EHealTarget
{
	HEALTARGET_HEALTH = 0,
	HEALTARGET_ENERGY = 1,
};

const char *EnumToString( const EHealTarget value );
const EHealTarget StringToEnum_EHealTarget( const char* value );

template <>
struct KnownEnum< EHealTarget >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EHealTarget value ) { return EnumToString( value ); }
	static const EHealTarget ToEnum( const char* value ) { return StringToEnum_EHealTarget( value ); }
	static const EHealTarget ToEnum( const string& value ) { return StringToEnum_EHealTarget( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EKickAwayBehaviour
{
	KICKAWAYBEHAVIOUR_KICKFROMSENDER = 0,
	KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGET = 1,
	KICKAWAYBEHAVIOUR_KICKFROMHIER1UPTARGETMOVEDIRECTION = 2,
};

const char *EnumToString( const EKickAwayBehaviour value );
const EKickAwayBehaviour StringToEnum_EKickAwayBehaviour( const char* value );

template <>
struct KnownEnum< EKickAwayBehaviour >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EKickAwayBehaviour value ) { return EnumToString( value ); }
	static const EKickAwayBehaviour ToEnum( const char* value ) { return StringToEnum_EKickAwayBehaviour( value ); }
	static const EKickAwayBehaviour ToEnum( const string& value ) { return StringToEnum_EKickAwayBehaviour( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EKillMode
{
	KILLMODE_NONE = 0,
	KILLMODE_DONTSHOWDEATH = 1,
	KILLMODE_INSTANTREMOVE = 2,
	KILLMODE_UNSUMMON = 3,
};

const char *EnumToString( const EKillMode value );
const EKillMode StringToEnum_EKillMode( const char* value );

template <>
struct KnownEnum< EKillMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EKillMode value ) { return EnumToString( value ); }
	static const EKillMode ToEnum( const char* value ) { return StringToEnum_EKillMode( value ); }
	static const EKillMode ToEnum( const string& value ) { return StringToEnum_EKillMode( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EParentNotification
{
	PARENTNOTIFICATION_NA = -1,
	PARENTNOTIFICATION_START = 0,
	PARENTNOTIFICATION_STOP = 1,
	PARENTNOTIFICATION_DONE = 2,
	PARENTNOTIFICATION_CANCEL = 3,
};

const char *EnumToString( const EParentNotification value );
const EParentNotification StringToEnum_EParentNotification( const char* value );

template <>
struct KnownEnum< EParentNotification >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EParentNotification value ) { return EnumToString( value ); }
	static const EParentNotification ToEnum( const char* value ) { return StringToEnum_EParentNotification( value ); }
	static const EParentNotification ToEnum( const string& value ) { return StringToEnum_EParentNotification( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EParentNotificationFlags
{
	PARENTNOTIFICATIONFLAGS_ZERO = 0,
	PARENTNOTIFICATIONFLAGS_START = 1,
	PARENTNOTIFICATIONFLAGS_STOP = 2,
	PARENTNOTIFICATIONFLAGS_DONE = 4,
	PARENTNOTIFICATIONFLAGS_CANCEL = 8,
};

const char *EnumToString( const EParentNotificationFlags value );
const EParentNotificationFlags StringToEnum_EParentNotificationFlags( const char* value );

template <>
struct KnownEnum< EParentNotificationFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EParentNotificationFlags value ) { return EnumToString( value ); }
	static const EParentNotificationFlags ToEnum( const char* value ) { return StringToEnum_EParentNotificationFlags( value ); }
	static const EParentNotificationFlags ToEnum( const string& value ) { return StringToEnum_EParentNotificationFlags( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EPointTargetSelectorMode
{
	POINTTARGETSELECTORMODE_TOOWNER = 0,
	POINTTARGETSELECTORMODE_TOTARGET = 1,
	POINTTARGETSELECTORMODE_RANGEFROMOWNER = 2,
	POINTTARGETSELECTORMODE_RANGEFROMTARGET = 3,
	POINTTARGETSELECTORMODE_INTERPOLATION = 4,
	POINTTARGETSELECTORMODE_OFFSETFROMOWNER = 5,
	POINTTARGETSELECTORMODE_RANGEFROMTARGETTOREQUESTER = 6,
	POINTTARGETSELECTORMODE_OFFSETFROMTARGET = 7,
	POINTTARGETSELECTORMODE_RANDOMPOINT = 8,
	POINTTARGETSELECTORMODE_RANDOMDIRECTION = 9,
	POINTTARGETSELECTORMODE_RANGEFROMTARGETTOABILITY = 10,
};

const char *EnumToString( const EPointTargetSelectorMode value );
const EPointTargetSelectorMode StringToEnum_EPointTargetSelectorMode( const char* value );

template <>
struct KnownEnum< EPointTargetSelectorMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const EPointTargetSelectorMode value ) { return EnumToString( value ); }
	static const EPointTargetSelectorMode ToEnum( const char* value ) { return StringToEnum_EPointTargetSelectorMode( value ); }
	static const EPointTargetSelectorMode ToEnum( const string& value ) { return StringToEnum_EPointTargetSelectorMode( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

enum EScaleCalculationMode
{
	SCALECALCULATIONMODE_SCALEISCOUNT = 0,
	SCALECALCULATIONMODE_SCALEISTIME = 1,
	SCALECALCULATIONMODE_SCALEISVPAR = 2,
};

const char *EnumToString( const EScaleCalculationMode value );
const EScaleCalculationMode StringToEnum_EScaleCalculationMode( const char* value );

template <>
struct KnownEnum< EScaleCalculationMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EScaleCalculationMode value ) { return EnumToString( value ); }
	static const EScaleCalculationMode ToEnum( const char* value ) { return StringToEnum_EScaleCalculationMode( value ); }
	static const EScaleCalculationMode ToEnum( const string& value ) { return StringToEnum_EScaleCalculationMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ESortingOrder
{
	SORTINGORDER_INCREASING = 0,
	SORTINGORDER_DECREASING = 1,
};

const char *EnumToString( const ESortingOrder value );
const ESortingOrder StringToEnum_ESortingOrder( const char* value );

template <>
struct KnownEnum< ESortingOrder >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ESortingOrder value ) { return EnumToString( value ); }
	static const ESortingOrder ToEnum( const char* value ) { return StringToEnum_ESortingOrder( value ); }
	static const ESortingOrder ToEnum( const string& value ) { return StringToEnum_ESortingOrder( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ESpellTarget
{
	SPELLTARGET_HEROMALE = 1,
	SPELLTARGET_HEROFEMALE = 2,
	SPELLTARGET_SUMMON = 4,
	SPELLTARGET_CREEP = 8,
	SPELLTARGET_SIEGECREEP = 16,
	SPELLTARGET_NEUTRALCREEP = 32,
	SPELLTARGET_TOWER = 64,
	SPELLTARGET_MAINBUILDING = 256,
	SPELLTARGET_BUILDING = 128,
	SPELLTARGET_SHOP = 512,
	SPELLTARGET_TREE = 1024,
	SPELLTARGET_PICKUPABLE = 4096,
	SPELLTARGET_MINIGAMEPLACES = 8192,
	SPELLTARGET_DEADBODIES = 16384,
	SPELLTARGET_DUMMYUNIT = 65536,
	SPELLTARGET_FLAGPOLE = 131072,
	SPELLTARGET_NEUTRALCHAMPION = 262144,
	SPELLTARGET_NEUTRALBOSS = 524288,
	SPELLTARGET_FACTIONCHAMPION = 1048576,
	SPELLTARGET_ALLNEUTRALS = 786464,
	SPELLTARGET_ALL = 2040319,
	SPELLTARGET_ALLWOBUILDINGS = 1900607,
	SPELLTARGET_FLYING = 4194304,
	SPELLTARGET_LINEOFSIGHT = 2097152,
	SPELLTARGET_VULNERABLETARGETSONLY = 8388608,
	SPELLTARGET_LAND = 16777216,
	SPELLTARGET_NEUTRAL = 33554432,
	SPELLTARGET_AFFECTMOUNTED = 67108864,
	SPELLTARGET_VISIBLETARGETSONLY = 134217728,
	SPELLTARGET_ALLY = 268435456,
	SPELLTARGET_ENEMY = 536870912,
	SPELLTARGET_SELF = 1073741824,
	SPELLTARGET_ALLENEMIES = 538911231,
};

const char *EnumToString( const ESpellTarget value );
const ESpellTarget StringToEnum_ESpellTarget( const char* value );

template <>
struct KnownEnum< ESpellTarget >
{
	enum { isKnown = 1 };
	enum { sizeOf = 33 };
	static const char *ToString( const ESpellTarget value ) { return EnumToString( value ); }
	static const ESpellTarget ToEnum( const char* value ) { return StringToEnum_ESpellTarget( value ); }
	static const ESpellTarget ToEnum( const string& value ) { return StringToEnum_ESpellTarget( value.c_str() ); }
	static const int SizeOf() { return 33; }
};

enum EStackingRule
{
	STACKINGRULE_UNSTACKABLE = 0,
	STACKINGRULE_PARTIALLYSTACKABLE = 1,
	STACKINGRULE_FULLYSTACKABLE = 2,
};

const char *EnumToString( const EStackingRule value );
const EStackingRule StringToEnum_EStackingRule( const char* value );

template <>
struct KnownEnum< EStackingRule >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EStackingRule value ) { return EnumToString( value ); }
	static const EStackingRule ToEnum( const char* value ) { return StringToEnum_EStackingRule( value ); }
	static const EStackingRule ToEnum( const string& value ) { return StringToEnum_EStackingRule( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EStatConstraint
{
	STATCONSTRAINT_NONE = 0,
	STATCONSTRAINT_UPPERLIMIT = 1,
	STATCONSTRAINT_LOWERLIMIT = 2,
};

const char *EnumToString( const EStatConstraint value );
const EStatConstraint StringToEnum_EStatConstraint( const char* value );

template <>
struct KnownEnum< EStatConstraint >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EStatConstraint value ) { return EnumToString( value ); }
	static const EStatConstraint ToEnum( const char* value ) { return StringToEnum_EStatConstraint( value ); }
	static const EStatConstraint ToEnum( const string& value ) { return StringToEnum_EStatConstraint( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EStatusFlags
{
	STATUSFLAGS_NONE = 0,
	STATUSFLAGS_UPDATELIFETIME = 1,
	STATUSFLAGS_ISDEBUFF = 2,
	STATUSFLAGS_STOPSAMECONFLICTED = 4,
	STATUSFLAGS_ALWAYSMERGE = 8,
	STATUSFLAGS_SHOWSINGLE = 16,
	STATUSFLAGS_STOPALLCONFLICTED = 32,
	STATUSFLAGS_ISBUFF = 64,
};

const char *EnumToString( const EStatusFlags value );
const EStatusFlags StringToEnum_EStatusFlags( const char* value );

template <>
struct KnownEnum< EStatusFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const EStatusFlags value ) { return EnumToString( value ); }
	static const EStatusFlags ToEnum( const char* value ) { return StringToEnum_EStatusFlags( value ); }
	static const EStatusFlags ToEnum( const string& value ) { return StringToEnum_EStatusFlags( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum EStopBehaviour
{
	STOPBEHAVIOUR_STOPBYTIME = 0,
	STOPBEHAVIOUR_STOPBYCHILD = 1,
	STOPBEHAVIOUR_STOPBYALLCHILDS = 2,
};

const char *EnumToString( const EStopBehaviour value );
const EStopBehaviour StringToEnum_EStopBehaviour( const char* value );

template <>
struct KnownEnum< EStopBehaviour >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EStopBehaviour value ) { return EnumToString( value ); }
	static const EStopBehaviour ToEnum( const char* value ) { return StringToEnum_EStopBehaviour( value ); }
	static const EStopBehaviour ToEnum( const string& value ) { return StringToEnum_EStopBehaviour( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ESummonFlags
{
	SUMMONFLAGS_NONE = 0,
	SUMMONFLAGS_ESSENTIAL = 1,
	SUMMONFLAGS_ALPHASUMMON = 2,
	SUMMONFLAGS_NOHEALTHPRIORITY = 4,
	SUMMONFLAGS_COPYLEVELANDSTATS = 8,
	SUMMONFLAGS_TURNBYMASTERDIRECTION = 16,
	SUMMONFLAGS_NOSUMMONANIMATION = 32,
	SUMMONFLAGS_USEGLOWEFFECT = 64,
	SUMMONFLAGS_NOCOLLISION = 128,
	SUMMONFLAGS_LIKEHERO = 256,
};

const char *EnumToString( const ESummonFlags value );
const ESummonFlags StringToEnum_ESummonFlags( const char* value );

template <>
struct KnownEnum< ESummonFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 10 };
	static const char *ToString( const ESummonFlags value ) { return EnumToString( value ); }
	static const ESummonFlags ToEnum( const char* value ) { return StringToEnum_ESummonFlags( value ); }
	static const ESummonFlags ToEnum( const string& value ) { return StringToEnum_ESummonFlags( value.c_str() ); }
	static const int SizeOf() { return 10; }
};

enum ETargetSelectorFlags
{
	TARGETSELECTORFLAGS_ZERO = 0,
	TARGETSELECTORFLAGS_IGNOREORIGINALTARGET = 1,
	TARGETSELECTORFLAGS_DEADALLOWED = 2,
};

const char *EnumToString( const ETargetSelectorFlags value );
const ETargetSelectorFlags StringToEnum_ETargetSelectorFlags( const char* value );

template <>
struct KnownEnum< ETargetSelectorFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETargetSelectorFlags value ) { return EnumToString( value ); }
	static const ETargetSelectorFlags ToEnum( const char* value ) { return StringToEnum_ETargetSelectorFlags( value ); }
	static const ETargetSelectorFlags ToEnum( const string& value ) { return StringToEnum_ETargetSelectorFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETargetSelectorMode
{
	TARGETSELECTORMODE_NORMAL = 0,
	TARGETSELECTORMODE_CAPTURETARGETS = 1,
	TARGETSELECTORMODE_SENDONCE = 2,
};

const char *EnumToString( const ETargetSelectorMode value );
const ETargetSelectorMode StringToEnum_ETargetSelectorMode( const char* value );

template <>
struct KnownEnum< ETargetSelectorMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETargetSelectorMode value ) { return EnumToString( value ); }
	static const ETargetSelectorMode ToEnum( const char* value ) { return StringToEnum_ETargetSelectorMode( value ); }
	static const ETargetSelectorMode ToEnum( const string& value ) { return StringToEnum_ETargetSelectorMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETargetSelectorPoint
{
	TARGETSELECTORPOINT_ABILITYOWNER = 0,
	TARGETSELECTORPOINT_CURRENTPOSITION = 1,
	TARGETSELECTORPOINT_PREVIOUSPOSITION = 2,
	TARGETSELECTORPOINT_OWNERDIRECTION = 3,
};

const char *EnumToString( const ETargetSelectorPoint value );
const ETargetSelectorPoint StringToEnum_ETargetSelectorPoint( const char* value );

template <>
struct KnownEnum< ETargetSelectorPoint >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const ETargetSelectorPoint value ) { return EnumToString( value ); }
	static const ETargetSelectorPoint ToEnum( const char* value ) { return StringToEnum_ETargetSelectorPoint( value ); }
	static const ETargetSelectorPoint ToEnum( const string& value ) { return StringToEnum_ETargetSelectorPoint( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum ETeamID
{
	TEAMID_A = 0,
	TEAMID_B = 1,
};

const char *EnumToString( const ETeamID value );
const ETeamID StringToEnum_ETeamID( const char* value );

template <>
struct KnownEnum< ETeamID >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ETeamID value ) { return EnumToString( value ); }
	static const ETeamID ToEnum( const char* value ) { return StringToEnum_ETeamID( value ); }
	static const ETeamID ToEnum( const string& value ) { return StringToEnum_ETeamID( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EThrowType
{
	THROWTYPE_THROW = 0,
	THROWTYPE_JUMP = 1,
	THROWTYPE_FLIP = 2,
};

const char *EnumToString( const EThrowType value );
const EThrowType StringToEnum_EThrowType( const char* value );

template <>
struct KnownEnum< EThrowType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EThrowType value ) { return EnumToString( value ); }
	static const EThrowType ToEnum( const char* value ) { return StringToEnum_EThrowType( value ); }
	static const EThrowType ToEnum( const string& value ) { return StringToEnum_EThrowType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETraceMode
{
	TRACEMODE_DYNAMIC = 1,
	TRACEMODE_STATIC = 2,
	TRACEMODE_BUILDING = 4,
};

const char *EnumToString( const ETraceMode value );
const ETraceMode StringToEnum_ETraceMode( const char* value );

template <>
struct KnownEnum< ETraceMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETraceMode value ) { return EnumToString( value ); }
	static const ETraceMode ToEnum( const char* value ) { return StringToEnum_ETraceMode( value ); }
	static const ETraceMode ToEnum( const string& value ) { return StringToEnum_ETraceMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETriggerAbilitiesAbilitiesFlags
{
	TRIGGERABILITIESABILITIESFLAGS_NONE = 0,
	TRIGGERABILITIESABILITIESFLAGS_BASEATTACK = 1,
	TRIGGERABILITIESABILITIESFLAGS_ABILITY0 = 2,
	TRIGGERABILITIESABILITIESFLAGS_ABILITY1 = 4,
	TRIGGERABILITIESABILITIESFLAGS_ABILITY2 = 8,
	TRIGGERABILITIESABILITIESFLAGS_ABILITY3 = 16,
	TRIGGERABILITIESABILITIESFLAGS_ABILITY4 = 32,
	TRIGGERABILITIESABILITIESFLAGS_CONSUMABLE = 64,
	TRIGGERABILITIESABILITIESFLAGS_TALENT = 128,
	TRIGGERABILITIESABILITIESFLAGS_SPECIAL = 1024,
	TRIGGERABILITIESABILITIESFLAGS_ALL = 1279,
	TRIGGERABILITIESABILITIESFLAGS_ONLYCLASSTALENT = 134217856,
	TRIGGERABILITIESABILITIESFLAGS_FROMLIST = 268435456,
	TRIGGERABILITIESABILITIESFLAGS_FROMALLY = 536870912,
	TRIGGERABILITIESABILITIESFLAGS_FROMENEMY = 1073741824,
};

const char *EnumToString( const ETriggerAbilitiesAbilitiesFlags value );
const ETriggerAbilitiesAbilitiesFlags StringToEnum_ETriggerAbilitiesAbilitiesFlags( const char* value );

template <>
struct KnownEnum< ETriggerAbilitiesAbilitiesFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 15 };
	static const char *ToString( const ETriggerAbilitiesAbilitiesFlags value ) { return EnumToString( value ); }
	static const ETriggerAbilitiesAbilitiesFlags ToEnum( const char* value ) { return StringToEnum_ETriggerAbilitiesAbilitiesFlags( value ); }
	static const ETriggerAbilitiesAbilitiesFlags ToEnum( const string& value ) { return StringToEnum_ETriggerAbilitiesAbilitiesFlags( value.c_str() ); }
	static const int SizeOf() { return 15; }
};

enum ETriggerEventCheckSender
{
	TRIGGEREVENTCHECKSENDER_NONE = 0,
	TRIGGEREVENTCHECKSENDER_MATCHTARGET = 1,
	TRIGGEREVENTCHECKSENDER_OBJECTFILTER = 2,
};

const char *EnumToString( const ETriggerEventCheckSender value );
const ETriggerEventCheckSender StringToEnum_ETriggerEventCheckSender( const char* value );

template <>
struct KnownEnum< ETriggerEventCheckSender >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETriggerEventCheckSender value ) { return EnumToString( value ); }
	static const ETriggerEventCheckSender ToEnum( const char* value ) { return StringToEnum_ETriggerEventCheckSender( value ); }
	static const ETriggerEventCheckSender ToEnum( const string& value ) { return StringToEnum_ETriggerEventCheckSender( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ETriggerEventFlags
{
	TRIGGEREVENTFLAGS_NONE = 0,
	TRIGGEREVENTFLAGS_ONLYFIRSTFROMABILITY = 1,
	TRIGGEREVENTFLAGS_ONCEPERSTEP = 2,
};

const char *EnumToString( const ETriggerEventFlags value );
const ETriggerEventFlags StringToEnum_ETriggerEventFlags( const char* value );

template <>
struct KnownEnum< ETriggerEventFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETriggerEventFlags value ) { return EnumToString( value ); }
	static const ETriggerEventFlags ToEnum( const char* value ) { return StringToEnum_ETriggerEventFlags( value ); }
	static const ETriggerEventFlags ToEnum( const string& value ) { return StringToEnum_ETriggerEventFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUnitCreationPlace
{
	UNITCREATIONPLACE_DIRECTTOTARGET = 0,
	UNITCREATIONPLACE_ATTARGET = 1,
	UNITCREATIONPLACE_ATCREATOR = 2,
};

const char *EnumToString( const EUnitCreationPlace value );
const EUnitCreationPlace StringToEnum_EUnitCreationPlace( const char* value );

template <>
struct KnownEnum< EUnitCreationPlace >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUnitCreationPlace value ) { return EnumToString( value ); }
	static const EUnitCreationPlace ToEnum( const char* value ) { return StringToEnum_EUnitCreationPlace( value ); }
	static const EUnitCreationPlace ToEnum( const string& value ) { return StringToEnum_EUnitCreationPlace( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUnitFlag
{
	UNITFLAG_FORBIDMOVE = 1,
	UNITFLAG_FORBIDSELECTTARGET = 2,
	UNITFLAG_FORBIDATTACK = 4,
	UNITFLAG_FORBID_ABILITY1 = 8,
	UNITFLAG_FORBID_ABILITY2 = 16,
	UNITFLAG_FORBID_ABILITY3 = 32,
	UNITFLAG_FORBID_ABILITY4 = 64,
	UNITFLAG_FORBIDTAKEDAMAGE = 128,
	UNITFLAG_FORBIDAUTOTARGETME = 256,
	UNITFLAG_FORBIDUSECONSUMABLES = 512,
	UNITFLAG_FORBIDUSETALENTS = 1024,
	UNITFLAG_ISOLATED = 2047,
	UNITFLAG_INVISIBLE = 2048,
	UNITFLAG_CANSEEINVISIBLE = 4096,
	UNITFLAG_STUN = 8192,
	UNITFLAG_FORBIDLIFERESTORE = 16384,
	UNITFLAG_FORBIDENERGYRESTORE = 32768,
	UNITFLAG_IGNOREINVISIBLE = 65536,
	UNITFLAG_FORBIDMOVESPECIAL = 131072,
	UNITFLAG_FORBIDDEATH = 262144,
	UNITFLAG_FORBIDINTERACT = 524288,
	UNITFLAG_FLYING = 1048576,
	UNITFLAG_FORBIDAUTOATTACK = 2097152,
	UNITFLAG_FORBIDPICK = 4194304,
	UNITFLAG_FORBIDPLAYERCONTROL = 8388608,
	UNITFLAG_CANTURNWHILEFORBIDMOVE = 16777216,
	UNITFLAG_FREEZE = 33554432,
	UNITFLAG_IGNOREPUSH = 67108864,
	UNITFLAG_FORBIDINVISIBILITY = 134217728,
	UNITFLAG_INMINIGAME = 268435456,
	UNITFLAG_LIVEAFTERDEATH = 536870912,
	UNITFLAG_FORBIDREWARDS = 1073741824,
};

const char *EnumToString( const EUnitFlag value );
const EUnitFlag StringToEnum_EUnitFlag( const char* value );

template <>
struct KnownEnum< EUnitFlag >
{
	enum { isKnown = 1 };
	enum { sizeOf = 32 };
	static const char *ToString( const EUnitFlag value ) { return EnumToString( value ); }
	static const EUnitFlag ToEnum( const char* value ) { return StringToEnum_EUnitFlag( value ); }
	static const EUnitFlag ToEnum( const string& value ) { return StringToEnum_EUnitFlag( value.c_str() ); }
	static const int SizeOf() { return 32; }
};

enum EUnitFlagType
{
	UNITFLAGTYPE_FORBIDMOVE = 0,
	UNITFLAGTYPE_FORBIDSELECTTARGET = 1,
	UNITFLAGTYPE_FORBIDATTACK = 2,
	UNITFLAGTYPE_FORBID_ABILITY1 = 3,
	UNITFLAGTYPE_FORBID_ABILITY2 = 4,
	UNITFLAGTYPE_FORBID_ABILITY3 = 5,
	UNITFLAGTYPE_FORBID_ABILITY4 = 6,
	UNITFLAGTYPE_FORBIDTAKEDAMAGE = 7,
	UNITFLAGTYPE_FORBIDAUTOTARGETME = 8,
	UNITFLAGTYPE_FORBIDUSECONSUMABLES = 9,
	UNITFLAGTYPE_FORBIDUSETALENTS = 10,
	UNITFLAGTYPE_INVISIBLE = 11,
	UNITFLAGTYPE_CANSEEINVISIBLE = 12,
	UNITFLAGTYPE_STUN = 13,
	UNITFLAGTYPE_FORBIDLIFERESTORE = 14,
	UNITFLAGTYPE_FORBIDENERGYRESTORE = 15,
	UNITFLAGTYPE_IGNOREINVISIBLE = 16,
	UNITFLAGTYPE_FORBIDMOVESPECIAL = 17,
	UNITFLAGTYPE_FORBIDDEATH = 18,
	UNITFLAGTYPE_FORBIDINTERACT = 19,
	UNITFLAGTYPE_FLYING = 20,
	UNITFLAGTYPE_FORBIDAUTOATTACK = 21,
	UNITFLAGTYPE_FORBIDPICK = 22,
	UNITFLAGTYPE_FORBIDPLAYERCONTROL = 23,
	UNITFLAGTYPE_CANTURNWHILEFORBIDMOVE = 24,
	UNITFLAGTYPE_FREEZE = 25,
	UNITFLAGTYPE_IGNOREPUSH = 26,
	UNITFLAGTYPE_FORBIDINVISIBILITY = 27,
	UNITFLAGTYPE_INMINIGAME = 28,
	UNITFLAGTYPE_LIVEAFTERDEATH = 29,
	UNITFLAGTYPE_FORBIDREWARDS = 30,
};

const char *EnumToString( const EUnitFlagType value );
const EUnitFlagType StringToEnum_EUnitFlagType( const char* value );

template <>
struct KnownEnum< EUnitFlagType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 31 };
	static const char *ToString( const EUnitFlagType value ) { return EnumToString( value ); }
	static const EUnitFlagType ToEnum( const char* value ) { return StringToEnum_EUnitFlagType( value ); }
	static const EUnitFlagType ToEnum( const string& value ) { return StringToEnum_EUnitFlagType( value.c_str() ); }
	static const int SizeOf() { return 31; }
};

enum EUnitRelation
{
	UNITRELATION_MASTER = 0,
	UNITRELATION_TARGET = 1,
	UNITRELATION_ALPHASUMMON = 2,
	UNITRELATION_MOUNT = 3,
};

const char *EnumToString( const EUnitRelation value );
const EUnitRelation StringToEnum_EUnitRelation( const char* value );

template <>
struct KnownEnum< EUnitRelation >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EUnitRelation value ) { return EnumToString( value ); }
	static const EUnitRelation ToEnum( const char* value ) { return StringToEnum_EUnitRelation( value ); }
	static const EUnitRelation ToEnum( const string& value ) { return StringToEnum_EUnitRelation( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EUnitType
{
	UNITTYPE_INVALID = -1,
	UNITTYPE_HEROMALE = 0,
	UNITTYPE_HEROFEMALE = 1,
	UNITTYPE_SUMMON = 2,
	UNITTYPE_CREEP = 3,
	UNITTYPE_SIEGECREEP = 4,
	UNITTYPE_NEUTRALCREEP = 5,
	UNITTYPE_TOWER = 6,
	UNITTYPE_BUILDING = 7,
	UNITTYPE_MAINBUILDING = 8,
	UNITTYPE_SHOP = 9,
	UNITTYPE_TREE = 10,
	UNITTYPE_PET = 11,
	UNITTYPE_PICKUPABLE = 12,
	UNITTYPE_MINIGAMEPLACE = 13,
	UNITTYPE_DEADBODY = 14,
	UNITTYPE_SIMPLEOBJECT = 15,
	UNITTYPE_DUMMYUNIT = 16,
	UNITTYPE_FLAGPOLE = 17,
	UNITTYPE_NEUTRALCHAMPION = 18,
	UNITTYPE_NEUTRALBOSS = 19,
	UNITTYPE_FACTIONCHAMPION = 20,
};

const char *EnumToString( const EUnitType value );
const EUnitType StringToEnum_EUnitType( const char* value );

template <>
struct KnownEnum< EUnitType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 22 };
	static const char *ToString( const EUnitType value ) { return EnumToString( value ); }
	static const EUnitType ToEnum( const char* value ) { return StringToEnum_EUnitType( value ); }
	static const EUnitType ToEnum( const string& value ) { return StringToEnum_EUnitType( value.c_str() ); }
	static const int SizeOf() { return 22; }
};

enum EUpdateDurationFlags
{
	UPDATEDURATIONFLAGS_NONE = 0,
	UPDATEDURATIONFLAGS_CHECKBYFORMULANAME = 1,
	UPDATEDURATIONFLAGS_SETDURATION = 2,
};

const char *EnumToString( const EUpdateDurationFlags value );
const EUpdateDurationFlags StringToEnum_EUpdateDurationFlags( const char* value );

template <>
struct KnownEnum< EUpdateDurationFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUpdateDurationFlags value ) { return EnumToString( value ); }
	static const EUpdateDurationFlags ToEnum( const char* value ) { return StringToEnum_EUpdateDurationFlags( value ); }
	static const EUpdateDurationFlags ToEnum( const string& value ) { return StringToEnum_EUpdateDurationFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EUseMode
{
	USEMODE_LISTASRULE = 0,
	USEMODE_LISTASEXCEPTION = 1,
};

const char *EnumToString( const EUseMode value );
const EUseMode StringToEnum_EUseMode( const char* value );

template <>
struct KnownEnum< EUseMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EUseMode value ) { return EnumToString( value ); }
	static const EUseMode ToEnum( const char* value ) { return StringToEnum_EUseMode( value ); }
	static const EUseMode ToEnum( const string& value ) { return StringToEnum_EUseMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EWaitForSpellBehaviour
{
	WAITFORSPELLBEHAVIOUR_ZERO = 0,
	WAITFORSPELLBEHAVIOUR_STOPWHENSPELLFINISHED = 1,
	WAITFORSPELLBEHAVIOUR_UPDATEPARENTTARGET = 2,
	WAITFORSPELLBEHAVIOUR_DONTAPPLYEFFECTONFIRSTTARGET = 4,
};

const char *EnumToString( const EWaitForSpellBehaviour value );
const EWaitForSpellBehaviour StringToEnum_EWaitForSpellBehaviour( const char* value );

template <>
struct KnownEnum< EWaitForSpellBehaviour >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EWaitForSpellBehaviour value ) { return EnumToString( value ); }
	static const EWaitForSpellBehaviour ToEnum( const char* value ) { return StringToEnum_EWaitForSpellBehaviour( value ); }
	static const EWaitForSpellBehaviour ToEnum( const string& value ) { return StringToEnum_EWaitForSpellBehaviour( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum SummonPlaceMode
{
	SUMMONPLACEMODE_BYAPPLICATOR = 0,
	SUMMONPLACEMODE_BYTARGETSELECTOR = 1,
	SUMMONPLACEMODE_BYBEHAVIOUR = 2,
};

const char *EnumToString( const SummonPlaceMode value );
const SummonPlaceMode StringToEnum_SummonPlaceMode( const char* value );

template <>
struct KnownEnum< SummonPlaceMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const SummonPlaceMode value ) { return EnumToString( value ); }
	static const SummonPlaceMode ToEnum( const char* value ) { return StringToEnum_SummonPlaceMode( value ); }
	static const SummonPlaceMode ToEnum( const string& value ) { return StringToEnum_SummonPlaceMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum SummonSource
{
	SUMMONSOURCE_BYAPPLICATOR = 0,
	SUMMONSOURCE_TARGETCLONE = 1,
};

const char *EnumToString( const SummonSource value );
const SummonSource StringToEnum_SummonSource( const char* value );

template <>
struct KnownEnum< SummonSource >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const SummonSource value ) { return EnumToString( value ); }
	static const SummonSource ToEnum( const char* value ) { return StringToEnum_SummonSource( value ); }
	static const SummonSource ToEnum( const string& value ) { return StringToEnum_SummonSource( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum SummonType
{
	SUMMONTYPE_PRIMARY = 0,
	SUMMONTYPE_SECONDARY = 1,
	SUMMONTYPE_PET = 2,
	SUMMONTYPE_CLONE = 3,
};

const char *EnumToString( const SummonType value );
const SummonType StringToEnum_SummonType( const char* value );

template <>
struct KnownEnum< SummonType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const SummonType value ) { return EnumToString( value ); }
	static const SummonType ToEnum( const char* value ) { return StringToEnum_SummonType( value ); }
	static const SummonType ToEnum( const string& value ) { return StringToEnum_SummonType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum SummonTypeFlags
{
	SUMMONTYPEFLAGS_PRIMARY = 1,
	SUMMONTYPEFLAGS_SECONDARY = 2,
	SUMMONTYPEFLAGS_PET = 4,
	SUMMONTYPEFLAGS_CLONE = 8,
};

const char *EnumToString( const SummonTypeFlags value );
const SummonTypeFlags StringToEnum_SummonTypeFlags( const char* value );

template <>
struct KnownEnum< SummonTypeFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const SummonTypeFlags value ) { return EnumToString( value ); }
	static const SummonTypeFlags ToEnum( const char* value ) { return StringToEnum_SummonTypeFlags( value ); }
	static const SummonTypeFlags ToEnum( const string& value ) { return StringToEnum_SummonTypeFlags( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum TargetToLandMode
{
	TARGETTOLANDMODE_FIRST = 0,
	TARGETTOLANDMODE_NEAREST = 1,
	TARGETTOLANDMODE_CENTER = 2,
	TARGETTOLANDMODE_CENTERTARGET = 3,
};

const char *EnumToString( const TargetToLandMode value );
const TargetToLandMode StringToEnum_TargetToLandMode( const char* value );

template <>
struct KnownEnum< TargetToLandMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const TargetToLandMode value ) { return EnumToString( value ); }
	static const TargetToLandMode ToEnum( const char* value ) { return StringToEnum_TargetToLandMode( value ); }
	static const TargetToLandMode ToEnum( const string& value ) { return StringToEnum_TargetToLandMode( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum UnitDieKillersFlags
{
	UNITDIEKILLERSFLAGS_KILLEDBYME = 1,
	UNITDIEKILLERSFLAGS_KILLEDBYALLIES = 2,
	UNITDIEKILLERSFLAGS_KILLEDBYENEMY = 4,
	UNITDIEKILLERSFLAGS_KILLEDBYMYSUMMONS = 8,
	UNITDIEKILLERSFLAGS_KILLEDBYALL = 7,
};

const char *EnumToString( const UnitDieKillersFlags value );
const UnitDieKillersFlags StringToEnum_UnitDieKillersFlags( const char* value );

template <>
struct KnownEnum< UnitDieKillersFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const UnitDieKillersFlags value ) { return EnumToString( value ); }
	static const UnitDieKillersFlags ToEnum( const char* value ) { return StringToEnum_UnitDieKillersFlags( value ); }
	static const UnitDieKillersFlags ToEnum( const string& value ) { return StringToEnum_UnitDieKillersFlags( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

struct ApplicatorToProxy
{
public:
	Ptr< BaseApplicator > applicator;
	vector< string > variableNames;

	ApplicatorToProxy();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ApplicatorToExecute
{
public:
	Ptr< BaseApplicator > applicator;
	ExecutableFloatString delay;
	ExecutableBoolString continueCondition;
	ExecutableBoolString stopCondition;
	EParentNotificationFlags continueEvents;
	EParentNotificationFlags stopEvents;

	ApplicatorToExecute();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LightningLink
{
public:
	vector< Ptr< LightningEffect > > effect;

	LightningLink();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Modifier
{
public:
	EStat stat;
	string variable;
	ExecutableFloatString addValue;
	ExecutableFloatString multValue;
	bool topModifier;

	Modifier();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SpawnStats
{
public:
	ExecutableFloatString life;
	ExecutableFloatString energy;

	SpawnStats();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SummonBehaviourCommonParams
{
public:
	Ptr< UnitTargetingParameters > targetingParams;
	ExecutableFloatString lashRange;
	float responseRange;
	float responseTime;

	SummonBehaviourCommonParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TriggerAbilitiesFilter
{
public:
	ETriggerAbilitiesAbilitiesFlags flags;
	bool onlySingleTarget;
	EAbilityCostMode abilityCostMode;
	vector< Ptr< Ability > > abilitiesList;
	bool exceptThis;
	ExecutableBoolString abilityCondition;

	TriggerAbilitiesFilter();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Spell : public DbResource
{
	DBRESOURCE_METHODS( Spell );
public:
	enum { typeId = 0x2C5C0B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Spell::typeId; }
	Ptr< Dispatch > dispatch;
	vector< Ptr< BaseApplicator > > applicators;

	Spell();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Spell& operator = ( const Spell &_spell ) { Assign( _spell ); return *this; }
	Spell( const Spell &_spell ) { Assign( _spell ); }
	virtual void Assign( const Spell &_spell );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Spell * pOther = dynamic_cast< const Spell * > ( _pResource );
		if ( pOther ) Spell::Assign( *pOther );
	}
};

struct BaseApplicator : public DbResource
{
public:
	enum { typeId = 0x9E5C0B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BaseApplicator::typeId; }
	ExecutableBoolString enabled;
	EApplicatorApplyTarget applyTarget;
	string formulaName;
	int LoggingEvent;
	string providerName;

	BaseApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BaseApplicator& operator = ( const BaseApplicator &_baseApplicator ) { Assign( _baseApplicator ); return *this; }
	BaseApplicator( const BaseApplicator &_baseApplicator ) { Assign( _baseApplicator ); }
	virtual void Assign( const BaseApplicator &_baseApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BaseApplicator * pOther = dynamic_cast< const BaseApplicator * > ( _pResource );
		if ( pOther ) BaseApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct BuffApplicator : public BaseApplicator
{
public:
	enum { typeId = 0x9E5C0B02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BuffApplicator::typeId; }
	EBuffBehavior behaviorFlags;
	ExecutableFloatString lifeTime;
	vector< Ptr< EffectBase > > effect;
	ExecutableBoolString startCondition;

	BuffApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BuffApplicator& operator = ( const BuffApplicator &_buffApplicator ) { Assign( _buffApplicator ); return *this; }
	BuffApplicator( const BuffApplicator &_buffApplicator ) { Assign( _buffApplicator ); }
	virtual void Assign( const BuffApplicator &_buffApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BuffApplicator * pOther = dynamic_cast< const BuffApplicator * > ( _pResource );
		if ( pOther ) BuffApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AbilityUpgradeApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( AbilityUpgradeApplicator );
public:
	enum { typeId = 0x0F6C0C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AbilityUpgradeApplicator::typeId; }
	EAbilityUpgradeMode flags;
	EAbilityTypeId targetAbility;
	vector< Ptr< BaseApplicator > > applicators;
	vector< Ptr< BaseApplicator > > persistentApplicators;
	ExecutableIntString applyCount;
	vector< Ptr< Ability > > talents;
	EUseMode useListAs;

	AbilityUpgradeApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AbilityUpgradeApplicator& operator = ( const AbilityUpgradeApplicator &_abilityUpgradeApplicator ) { Assign( _abilityUpgradeApplicator ); return *this; }
	AbilityUpgradeApplicator( const AbilityUpgradeApplicator &_abilityUpgradeApplicator ) { Assign( _abilityUpgradeApplicator ); }
	virtual void Assign( const AbilityUpgradeApplicator &_abilityUpgradeApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AbilityUpgradeApplicator * pOther = dynamic_cast< const AbilityUpgradeApplicator * > ( _pResource );
		if ( pOther ) AbilityUpgradeApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AbilityUpgradeTechApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( AbilityUpgradeTechApplicator );
public:
	enum { typeId = 0x15DC6040 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AbilityUpgradeTechApplicator::typeId; }
	int abilityObjectId;
	int abilityLastUseStep;

	AbilityUpgradeTechApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AbilityUpgradeTechApplicator& operator = ( const AbilityUpgradeTechApplicator &_abilityUpgradeTechApplicator ) { Assign( _abilityUpgradeTechApplicator ); return *this; }
	AbilityUpgradeTechApplicator( const AbilityUpgradeTechApplicator &_abilityUpgradeTechApplicator ) { Assign( _abilityUpgradeTechApplicator ); }
	virtual void Assign( const AbilityUpgradeTechApplicator &_abilityUpgradeTechApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AbilityUpgradeTechApplicator * pOther = dynamic_cast< const AbilityUpgradeTechApplicator * > ( _pResource );
		if ( pOther ) AbilityUpgradeTechApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AbsorbShieldApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( AbsorbShieldApplicator );
public:
	enum { typeId = 0x2B82CC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AbsorbShieldApplicator::typeId; }
	ExecutableFloatString damageToAbsorb;

	AbsorbShieldApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AbsorbShieldApplicator& operator = ( const AbsorbShieldApplicator &_absorbShieldApplicator ) { Assign( _absorbShieldApplicator ); return *this; }
	AbsorbShieldApplicator( const AbsorbShieldApplicator &_absorbShieldApplicator ) { Assign( _absorbShieldApplicator ); }
	virtual void Assign( const AbsorbShieldApplicator &_absorbShieldApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AbsorbShieldApplicator * pOther = dynamic_cast< const AbsorbShieldApplicator * > ( _pResource );
		if ( pOther ) AbsorbShieldApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AddApplicatorDuration : public BaseApplicator
{
	DBRESOURCE_METHODS( AddApplicatorDuration );
public:
	enum { typeId = 0x2B82CC80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AddApplicatorDuration::typeId; }
	ExecutableFloatString durationToAdd;
	vector< Ptr< BuffApplicator > > applicators;
	EUpdateDurationFlags flags;
	string nameToCheck;

	AddApplicatorDuration();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AddApplicatorDuration& operator = ( const AddApplicatorDuration &_addApplicatorDuration ) { Assign( _addApplicatorDuration ); return *this; }
	AddApplicatorDuration( const AddApplicatorDuration &_addApplicatorDuration ) { Assign( _addApplicatorDuration ); }
	virtual void Assign( const AddApplicatorDuration &_addApplicatorDuration );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AddApplicatorDuration * pOther = dynamic_cast< const AddApplicatorDuration * > ( _pResource );
		if ( pOther ) AddApplicatorDuration::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AddNaftaApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( AddNaftaApplicator );
public:
	enum { typeId = 0xE7764C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AddNaftaApplicator::typeId; }
	ExecutableFloatString nafta;
	bool isFromImpulseBuff;

	AddNaftaApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AddNaftaApplicator& operator = ( const AddNaftaApplicator &_addNaftaApplicator ) { Assign( _addNaftaApplicator ); return *this; }
	AddNaftaApplicator( const AddNaftaApplicator &_addNaftaApplicator ) { Assign( _addNaftaApplicator ); }
	virtual void Assign( const AddNaftaApplicator &_addNaftaApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AddNaftaApplicator * pOther = dynamic_cast< const AddNaftaApplicator * > ( _pResource );
		if ( pOther ) AddNaftaApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AlternativeActivity : public DbResource
{
	DBRESOURCE_METHODS( AlternativeActivity );
public:
	ExecutableFloatString useRange;
	EAbilityFlags flags;

	AlternativeActivity();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AlternativeActivity& operator = ( const AlternativeActivity &_alternativeActivity ) { Assign( _alternativeActivity ); return *this; }
	AlternativeActivity( const AlternativeActivity &_alternativeActivity ) { Assign( _alternativeActivity ); }
	virtual void Assign( const AlternativeActivity &_alternativeActivity );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AlternativeActivity * pOther = dynamic_cast< const AlternativeActivity * > ( _pResource );
		if ( pOther ) AlternativeActivity::Assign( *pOther );
	}
};

struct AlternativeTarget : public DbResource
{
	DBRESOURCE_METHODS( AlternativeTarget );
public:
	Ptr< SingleTargetSelector > targetSelector;
	int index;
	bool updateTarget;
	bool fromMinimap;
	Ptr< AlternativeActivity > alternativeActivity;

	AlternativeTarget();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AlternativeTarget& operator = ( const AlternativeTarget &_alternativeTarget ) { Assign( _alternativeTarget ); return *this; }
	AlternativeTarget( const AlternativeTarget &_alternativeTarget ) { Assign( _alternativeTarget ); }
	virtual void Assign( const AlternativeTarget &_alternativeTarget );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AlternativeTarget * pOther = dynamic_cast< const AlternativeTarget * > ( _pResource );
		if ( pOther ) AlternativeTarget::Assign( *pOther );
	}
};

struct ApplicatorNameOverrider : public BaseApplicator
{
	DBRESOURCE_METHODS( ApplicatorNameOverrider );
public:
	enum { typeId = 0xE794DC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ApplicatorNameOverrider::typeId; }
	Ptr< BaseApplicator > applicator;

	ApplicatorNameOverrider();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ApplicatorNameOverrider& operator = ( const ApplicatorNameOverrider &_applicatorNameOverrider ) { Assign( _applicatorNameOverrider ); return *this; }
	ApplicatorNameOverrider( const ApplicatorNameOverrider &_applicatorNameOverrider ) { Assign( _applicatorNameOverrider ); }
	virtual void Assign( const ApplicatorNameOverrider &_applicatorNameOverrider );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ApplicatorNameOverrider * pOther = dynamic_cast< const ApplicatorNameOverrider * > ( _pResource );
		if ( pOther ) ApplicatorNameOverrider::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct TargetSelector : public DbResource
{
	DBRESOURCE_METHODS( TargetSelector );
public:
	enum { typeId = 0x9E676B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TargetSelector::typeId; }

	TargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TargetSelector& operator = ( const TargetSelector &_targetSelector ) { Assign( _targetSelector ); return *this; }
	TargetSelector( const TargetSelector &_targetSelector ) { Assign( _targetSelector ); }
	virtual void Assign( const TargetSelector &_targetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TargetSelector * pOther = dynamic_cast< const TargetSelector * > ( _pResource );
		if ( pOther ) TargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ApplicatorsList : public DbResource
{
	DBRESOURCE_METHODS( ApplicatorsList );
public:
	enum { typeId = 0x0F724340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ApplicatorsList::typeId; }
	vector< Ptr< BaseApplicator > > applicators;
	vector< Ptr< ApplicatorsList > > applicatorLists;

	ApplicatorsList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ApplicatorsList& operator = ( const ApplicatorsList &_applicatorsList ) { Assign( _applicatorsList ); return *this; }
	ApplicatorsList( const ApplicatorsList &_applicatorsList ) { Assign( _applicatorsList ); }
	virtual void Assign( const ApplicatorsList &_applicatorsList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ApplicatorsList * pOther = dynamic_cast< const ApplicatorsList * > ( _pResource );
		if ( pOther ) ApplicatorsList::Assign( *pOther );
	}
};

struct MultipleTargetSelector : public TargetSelector
{
	DBRESOURCE_METHODS( MultipleTargetSelector );
public:
	enum { typeId = 0x9E6C82C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MultipleTargetSelector::typeId; }
	ETargetSelectorMode mode;
	ETargetSelectorFlags flags;

	MultipleTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MultipleTargetSelector& operator = ( const MultipleTargetSelector &_multipleTargetSelector ) { Assign( _multipleTargetSelector ); return *this; }
	MultipleTargetSelector( const MultipleTargetSelector &_multipleTargetSelector ) { Assign( _multipleTargetSelector ); }
	virtual void Assign( const MultipleTargetSelector &_multipleTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MultipleTargetSelector * pOther = dynamic_cast< const MultipleTargetSelector * > ( _pResource );
		if ( pOther ) MultipleTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct MultipleTargetSelectorFiltered : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( MultipleTargetSelectorFiltered );
public:
	enum { typeId = 0x9E7192C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MultipleTargetSelectorFiltered::typeId; }
	ESpellTarget targetFilter;

	MultipleTargetSelectorFiltered();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MultipleTargetSelectorFiltered& operator = ( const MultipleTargetSelectorFiltered &_multipleTargetSelectorFiltered ) { Assign( _multipleTargetSelectorFiltered ); return *this; }
	MultipleTargetSelectorFiltered( const MultipleTargetSelectorFiltered &_multipleTargetSelectorFiltered ) { Assign( _multipleTargetSelectorFiltered ); }
	virtual void Assign( const MultipleTargetSelectorFiltered &_multipleTargetSelectorFiltered );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MultipleTargetSelectorFiltered * pOther = dynamic_cast< const MultipleTargetSelectorFiltered * > ( _pResource );
		if ( pOther ) MultipleTargetSelectorFiltered::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct AttackTargetApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( AttackTargetApplicator );
public:
	enum { typeId = 0x9E678B02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AttackTargetApplicator::typeId; }
	EApplicatorApplyTarget attackTarget;
	int attackCount;
	EAttackTargetEvadeAction evadeAction;
	bool ignoreVisibility;

	AttackTargetApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AttackTargetApplicator& operator = ( const AttackTargetApplicator &_attackTargetApplicator ) { Assign( _attackTargetApplicator ); return *this; }
	AttackTargetApplicator( const AttackTargetApplicator &_attackTargetApplicator ) { Assign( _attackTargetApplicator ); }
	virtual void Assign( const AttackTargetApplicator &_attackTargetApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AttackTargetApplicator * pOther = dynamic_cast< const AttackTargetApplicator * > ( _pResource );
		if ( pOther ) AttackTargetApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AttractApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( AttractApplicator );
public:
	enum { typeId = 0x0F61F480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AttractApplicator::typeId; }
	float distance;

	AttractApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AttractApplicator& operator = ( const AttractApplicator &_attractApplicator ) { Assign( _attractApplicator ); return *this; }
	AttractApplicator( const AttractApplicator &_attractApplicator ) { Assign( _attractApplicator ); }
	virtual void Assign( const AttractApplicator &_attractApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AttractApplicator * pOther = dynamic_cast< const AttractApplicator * > ( _pResource );
		if ( pOther ) AttractApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AuraApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( AuraApplicator );
public:
	enum { typeId = 0x9E5C0B04 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AuraApplicator::typeId; }
	Ptr< TargetSelector > targetSelector;
	ExecutableFloatString range;
	ESpellTarget targets;
	EAuraVisualType type;
	vector< Ptr< BaseApplicator > > applicators;

	AuraApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AuraApplicator& operator = ( const AuraApplicator &_auraApplicator ) { Assign( _auraApplicator ); return *this; }
	AuraApplicator( const AuraApplicator &_auraApplicator ) { Assign( _auraApplicator ); }
	virtual void Assign( const AuraApplicator &_auraApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AuraApplicator * pOther = dynamic_cast< const AuraApplicator * > ( _pResource );
		if ( pOther ) AuraApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AbilityEndApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( AbilityEndApplicator );
public:
	enum { typeId = 0x0B75FB81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AbilityEndApplicator::typeId; }
	bool cancelApplicators;

	AbilityEndApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AbilityEndApplicator& operator = ( const AbilityEndApplicator &_abilityEndApplicator ) { Assign( _abilityEndApplicator ); return *this; }
	AbilityEndApplicator( const AbilityEndApplicator &_abilityEndApplicator ) { Assign( _abilityEndApplicator ); }
	virtual void Assign( const AbilityEndApplicator &_abilityEndApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AbilityEndApplicator * pOther = dynamic_cast< const AbilityEndApplicator * > ( _pResource );
		if ( pOther ) AbilityEndApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct Ability : public Spell
{
	DBRESOURCE_METHODS( Ability );
public:
	enum { typeId = 0x2C5C0B01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Ability::typeId; }
	CTextRef name;
	CTextRef description;
	CTextRef compiledDescriptionA;
	CTextRef compiledDescriptionB;
	CTextRef shortDescription;
	CTextRef commonDescription;
	vector< Ptr< CastLimitation > > castLimitations;
	Ptr< Texture > image;
	Ptr< Texture > imageSecondState;
	EAbilityAOEVisual aoeType;
	ExecutableFloatString aoeSize;
	Ptr< AOEMaterial > aoeMaterial;
	float aoeHeight;
	Ptr< AOEMaterial > useRangeMaterial;
	ETraceMode aoePassabilityCheckMode;
	bool aoeDisplayOnMinimap;
	EAbilityType type;
	ExecutableFloatString cooldownTime;
	ExecutableFloatString cooldownTimeSecondState;
	ExecutableFloatString manaCost;
	bool activeCustomTrigger;
	ExecutableFloatString useRange;
	float minUseRangeCorrection;
	ExecutableFloatString castAllowRange;
	ExecutableBoolString allowChase;
	Ptr< UnitConstantsContainer > constants;
	vector< Ptr< ConditionFormula > > conditionFormulas;
	bool isUnitFreeAfterCast;
	EAbilityFlags flags;
	ESpellTarget targetType;
	bool requireLineOfSight;
	vector< Ptr< BaseApplicator > > passiveApplicators;
	Ptr< SingleTargetSelector > autoTargetSelector;
	Ptr< MicroAI > microAI;
	string node;
	string marker;
	float warFogRemoveTime;
	float warFogRemoveRadius;
	vector< Ptr< AlternativeTarget > > alternativeTargets;

	Ability();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Ability& operator = ( const Ability &_ability ) { Assign( _ability ); return *this; }
	Ability( const Ability &_ability ) { Assign( _ability ); }
	virtual void Assign( const Ability &_ability );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Ability * pOther = dynamic_cast< const Ability * > ( _pResource );
		if ( pOther ) Ability::Assign( *pOther );
	}
};

struct MicroAI : public DbResource
{
	DBRESOURCE_METHODS( MicroAI );
public:

	MicroAI();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MicroAI& operator = ( const MicroAI &_microAI ) { Assign( _microAI ); return *this; }
	MicroAI( const MicroAI &_microAI ) { Assign( _microAI ); }
	virtual void Assign( const MicroAI &_microAI );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MicroAI * pOther = dynamic_cast< const MicroAI * > ( _pResource );
		if ( pOther ) MicroAI::Assign( *pOther );
	}

	virtual NWorld::PFMicroAI* Create( NWorld::PFMicroAICreateParams const &cp ) const;
};

struct BetweenUnitsTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( BetweenUnitsTargetSelector );
public:
	enum { typeId = 0x9A9CE3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BetweenUnitsTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableIntString maxTargets;
	EBetweenUnitsMode pairMode;
	ExecutableFloatString minDistBetweenTargets;

	BetweenUnitsTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BetweenUnitsTargetSelector& operator = ( const BetweenUnitsTargetSelector &_betweenUnitsTargetSelector ) { Assign( _betweenUnitsTargetSelector ); return *this; }
	BetweenUnitsTargetSelector( const BetweenUnitsTargetSelector &_betweenUnitsTargetSelector ) { Assign( _betweenUnitsTargetSelector ); }
	virtual void Assign( const BetweenUnitsTargetSelector &_betweenUnitsTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BetweenUnitsTargetSelector * pOther = dynamic_cast< const BetweenUnitsTargetSelector * > ( _pResource );
		if ( pOther ) BetweenUnitsTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct BounceApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( BounceApplicator );
public:
	enum { typeId = 0xE7792380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BounceApplicator::typeId; }
	Ptr< SingleTargetSelector > target;
	Ptr< Spell > spell;
	ExecutableIntString targetsNumber;
	ExecutableFloatString bounceDelay;
	EApplicatorApplyTarget startTarget;
	EBounceFlags flags;
	vector< Ptr< EffectBase > > cancelEffect;

	BounceApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BounceApplicator& operator = ( const BounceApplicator &_bounceApplicator ) { Assign( _bounceApplicator ); return *this; }
	BounceApplicator( const BounceApplicator &_bounceApplicator ) { Assign( _bounceApplicator ); }
	virtual void Assign( const BounceApplicator &_bounceApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BounceApplicator * pOther = dynamic_cast< const BounceApplicator * > ( _pResource );
		if ( pOther ) BounceApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AbilityModApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( AbilityModApplicator );
public:
	enum { typeId = 0x0F6BCC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AbilityModApplicator::typeId; }
	ExecutableFloatString addValue;
	ExecutableFloatString multValue;
	EAbilityIdFlags targetAbilities;
	EAbilityModMode mode;
	Ptr< Ability > specificAbility;
	vector< Ptr< Ability > > talents;
	EUseMode useListAs;

	AbilityModApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AbilityModApplicator& operator = ( const AbilityModApplicator &_abilityModApplicator ) { Assign( _abilityModApplicator ); return *this; }
	AbilityModApplicator( const AbilityModApplicator &_abilityModApplicator ) { Assign( _abilityModApplicator ); }
	virtual void Assign( const AbilityModApplicator &_abilityModApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AbilityModApplicator * pOther = dynamic_cast< const AbilityModApplicator * > ( _pResource );
		if ( pOther ) AbilityModApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct CapsuleTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( CapsuleTargetSelector );
public:
	enum { typeId = 0x9E6CBAC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CapsuleTargetSelector::typeId; }
	ETargetSelectorPoint segmentBegin;
	ETargetSelectorPoint segmentEnd;
	Ptr< SingleTargetSelector > segmentEndTargetSelector;
	ExecutableFloatString range;
	ExecutableFloatString rangeFromOwner;
	bool cutoffFirstSegment;
	float segmentDirectionOffset;

	CapsuleTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CapsuleTargetSelector& operator = ( const CapsuleTargetSelector &_capsuleTargetSelector ) { Assign( _capsuleTargetSelector ); return *this; }
	CapsuleTargetSelector( const CapsuleTargetSelector &_capsuleTargetSelector ) { Assign( _capsuleTargetSelector ); }
	virtual void Assign( const CapsuleTargetSelector &_capsuleTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CapsuleTargetSelector * pOther = dynamic_cast< const CapsuleTargetSelector * > ( _pResource );
		if ( pOther ) CapsuleTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct CastLimitation : public DbResource
{
	DBRESOURCE_METHODS( CastLimitation );
public:
	Ptr< UIEvent > uiEvent;

	CastLimitation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CastLimitation& operator = ( const CastLimitation &_castLimitation ) { Assign( _castLimitation ); return *this; }
	CastLimitation( const CastLimitation &_castLimitation ) { Assign( _castLimitation ); }
	virtual void Assign( const CastLimitation &_castLimitation );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CastLimitation * pOther = dynamic_cast< const CastLimitation * > ( _pResource );
		if ( pOther ) CastLimitation::Assign( *pOther );
	}

	virtual const NWorld::PFAbilityData* Check( NWorld::CastLimitationsCheckParams const &cp ) const;
};

struct ChainLightningApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ChainLightningApplicator );
public:
	enum { typeId = 0x9E5C0B0D };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChainLightningApplicator::typeId; }
	ExecutableIntString numJumps;
	Ptr< Spell > spell;
	float onJumpSpellScale;
	float betweenJumpsTimeInterval;
	ExecutableFloatString range;
	ESpellTarget targetFilter;
	ExecutableIntString effectIndex;
	vector< Ptr< EffectBase > > effects;
	ExecutableBoolString jumpOnEvade;

	ChainLightningApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChainLightningApplicator& operator = ( const ChainLightningApplicator &_chainLightningApplicator ) { Assign( _chainLightningApplicator ); return *this; }
	ChainLightningApplicator( const ChainLightningApplicator &_chainLightningApplicator ) { Assign( _chainLightningApplicator ); }
	virtual void Assign( const ChainLightningApplicator &_chainLightningApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChainLightningApplicator * pOther = dynamic_cast< const ChainLightningApplicator * > ( _pResource );
		if ( pOther ) ChainLightningApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChangeAnimationApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ChangeAnimationApplicator );
public:
	enum { typeId = 0x2C68AC01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeAnimationApplicator::typeId; }
	EAnimStates animState;
	string animation;
	string marker;
	bool upper;
	bool affectAllSets;

	ChangeAnimationApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeAnimationApplicator& operator = ( const ChangeAnimationApplicator &_changeAnimationApplicator ) { Assign( _changeAnimationApplicator ); return *this; }
	ChangeAnimationApplicator( const ChangeAnimationApplicator &_changeAnimationApplicator ) { Assign( _changeAnimationApplicator ); }
	virtual void Assign( const ChangeAnimationApplicator &_changeAnimationApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeAnimationApplicator * pOther = dynamic_cast< const ChangeAnimationApplicator * > ( _pResource );
		if ( pOther ) ChangeAnimationApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChangeAnimSetApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ChangeAnimSetApplicator );
public:
	enum { typeId = 0x2C68AC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeAnimSetApplicator::typeId; }
	Ptr< AnimSet > animSet;

	ChangeAnimSetApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeAnimSetApplicator& operator = ( const ChangeAnimSetApplicator &_changeAnimSetApplicator ) { Assign( _changeAnimSetApplicator ); return *this; }
	ChangeAnimSetApplicator( const ChangeAnimSetApplicator &_changeAnimSetApplicator ) { Assign( _changeAnimSetApplicator ); }
	virtual void Assign( const ChangeAnimSetApplicator &_changeAnimSetApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeAnimSetApplicator * pOther = dynamic_cast< const ChangeAnimSetApplicator * > ( _pResource );
		if ( pOther ) ChangeAnimSetApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChangeBaseAttackApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ChangeBaseAttackApplicator );
public:
	enum { typeId = 0x9E678AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeBaseAttackApplicator::typeId; }
	Ptr< BaseAttack > attackAbility;
	bool applyPassivePart;

	ChangeBaseAttackApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeBaseAttackApplicator& operator = ( const ChangeBaseAttackApplicator &_changeBaseAttackApplicator ) { Assign( _changeBaseAttackApplicator ); return *this; }
	ChangeBaseAttackApplicator( const ChangeBaseAttackApplicator &_changeBaseAttackApplicator ) { Assign( _changeBaseAttackApplicator ); }
	virtual void Assign( const ChangeBaseAttackApplicator &_changeBaseAttackApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeBaseAttackApplicator * pOther = dynamic_cast< const ChangeBaseAttackApplicator * > ( _pResource );
		if ( pOther ) ChangeBaseAttackApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChangeHeroStateApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ChangeHeroStateApplicator );
public:
	enum { typeId = 0x22CC6D80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeHeroStateApplicator::typeId; }

	ChangeHeroStateApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeHeroStateApplicator& operator = ( const ChangeHeroStateApplicator &_changeHeroStateApplicator ) { Assign( _changeHeroStateApplicator ); return *this; }
	ChangeHeroStateApplicator( const ChangeHeroStateApplicator &_changeHeroStateApplicator ) { Assign( _changeHeroStateApplicator ); }
	virtual void Assign( const ChangeHeroStateApplicator &_changeHeroStateApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeHeroStateApplicator * pOther = dynamic_cast< const ChangeHeroStateApplicator * > ( _pResource );
		if ( pOther ) ChangeHeroStateApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChangeStateApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ChangeStateApplicator );
public:
	enum { typeId = 0xE7958BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeStateApplicator::typeId; }
	string newStateName;

	ChangeStateApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeStateApplicator& operator = ( const ChangeStateApplicator &_changeStateApplicator ) { Assign( _changeStateApplicator ); return *this; }
	ChangeStateApplicator( const ChangeStateApplicator &_changeStateApplicator ) { Assign( _changeStateApplicator ); }
	virtual void Assign( const ChangeStateApplicator &_changeStateApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeStateApplicator * pOther = dynamic_cast< const ChangeStateApplicator * > ( _pResource );
		if ( pOther ) ChangeStateApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ChannellingApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ChannellingApplicator );
public:
	enum { typeId = 0x9E67B280 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChannellingApplicator::typeId; }
	Ptr< TargetSelector > targetSelector;
	EChannelingType channelingType;
	vector< Ptr< BaseApplicator > > applicatorsOnSelf;
	Ptr< Spell > startSpell;
	Ptr< Spell > periodicalSpell;
	Ptr< Spell > stopSpell;
	Ptr< Spell > cancelSpell;
	float period;
	EBaseUnitEventFlags interruptEvents;
	bool cancelOnInterrupt;
	bool removeStartSpellEffectOnInterrupt;
	ExecutableFloatString scaleWhenInterrupted;
	bool cancelOnDisable;

	ChannellingApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChannellingApplicator& operator = ( const ChannellingApplicator &_channellingApplicator ) { Assign( _channellingApplicator ); return *this; }
	ChannellingApplicator( const ChannellingApplicator &_channellingApplicator ) { Assign( _channellingApplicator ); }
	virtual void Assign( const ChannellingApplicator &_channellingApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChannellingApplicator * pOther = dynamic_cast< const ChannellingApplicator * > ( _pResource );
		if ( pOther ) ChannellingApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct CheckConditionTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( CheckConditionTargetSelector );
public:
	enum { typeId = 0x9A9C5C42 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CheckConditionTargetSelector::typeId; }
	Ptr< TargetSelector > targetSelector;
	ExecutableBoolString condition;
	ExecutableIntString minTargetsNumber;

	CheckConditionTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CheckConditionTargetSelector& operator = ( const CheckConditionTargetSelector &_checkConditionTargetSelector ) { Assign( _checkConditionTargetSelector ); return *this; }
	CheckConditionTargetSelector( const CheckConditionTargetSelector &_checkConditionTargetSelector ) { Assign( _checkConditionTargetSelector ); }
	virtual void Assign( const CheckConditionTargetSelector &_checkConditionTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CheckConditionTargetSelector * pOther = dynamic_cast< const CheckConditionTargetSelector * > ( _pResource );
		if ( pOther ) CheckConditionTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct CloneHeroApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( CloneHeroApplicator );
public:
	enum { typeId = 0x9E724380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CloneHeroApplicator::typeId; }
	vector< Ptr< BaseApplicator > > applicators;
	ExecutableFloatString lifeTime;
	ExecutableFloatString followRange;
	ECloneFlags flags;
	Ptr< UnitTargetingParameters > targetingParams;
	ExecutableIntString maxCount;
	string summonGroupName;
	SpawnStats spawnStats;
	ExecutableFloatString takeModDmg;
	ESpellTarget takeTypeUnit;

	CloneHeroApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CloneHeroApplicator& operator = ( const CloneHeroApplicator &_cloneHeroApplicator ) { Assign( _cloneHeroApplicator ); return *this; }
	CloneHeroApplicator( const CloneHeroApplicator &_cloneHeroApplicator ) { Assign( _cloneHeroApplicator ); }
	virtual void Assign( const CloneHeroApplicator &_cloneHeroApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CloneHeroApplicator * pOther = dynamic_cast< const CloneHeroApplicator * > ( _pResource );
		if ( pOther ) CloneHeroApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SingleTargetSelector : public TargetSelector
{
	DBRESOURCE_METHODS( SingleTargetSelector );
public:
	enum { typeId = 0x9E6C82C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SingleTargetSelector::typeId; }

	SingleTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SingleTargetSelector& operator = ( const SingleTargetSelector &_singleTargetSelector ) { Assign( _singleTargetSelector ); return *this; }
	SingleTargetSelector( const SingleTargetSelector &_singleTargetSelector ) { Assign( _singleTargetSelector ); }
	virtual void Assign( const SingleTargetSelector &_singleTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SingleTargetSelector * pOther = dynamic_cast< const SingleTargetSelector * > ( _pResource );
		if ( pOther ) SingleTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ConditionCastLimitation : public CastLimitation
{
	DBRESOURCE_METHODS( ConditionCastLimitation );
public:
	enum { typeId = 0x9E71CB81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ConditionCastLimitation::typeId; }
	ExecutableBoolString condition;

	ConditionCastLimitation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConditionCastLimitation& operator = ( const ConditionCastLimitation &_conditionCastLimitation ) { Assign( _conditionCastLimitation ); return *this; }
	ConditionCastLimitation( const ConditionCastLimitation &_conditionCastLimitation ) { Assign( _conditionCastLimitation ); }
	virtual void Assign( const ConditionCastLimitation &_conditionCastLimitation );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConditionCastLimitation * pOther = dynamic_cast< const ConditionCastLimitation * > ( _pResource );
		if ( pOther ) ConditionCastLimitation::Assign( *pOther );
	}

	virtual const NWorld::PFAbilityData* Check( NWorld::CastLimitationsCheckParams const &cp ) const;
};

struct ConditionFormula : public DbResource
{
	DBRESOURCE_METHODS( ConditionFormula );
public:
	string name;
	ExecutableBoolString condition;

	ConditionFormula();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConditionFormula& operator = ( const ConditionFormula &_conditionFormula ) { Assign( _conditionFormula ); return *this; }
	ConditionFormula( const ConditionFormula &_conditionFormula ) { Assign( _conditionFormula ); }
	virtual void Assign( const ConditionFormula &_conditionFormula );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConditionFormula * pOther = dynamic_cast< const ConditionFormula * > ( _pResource );
		if ( pOther ) ConditionFormula::Assign( *pOther );
	}
};

struct ConditionTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( ConditionTargetSelector );
public:
	enum { typeId = 0x2B7BB4C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ConditionTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableBoolString condition;

	ConditionTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConditionTargetSelector& operator = ( const ConditionTargetSelector &_conditionTargetSelector ) { Assign( _conditionTargetSelector ); return *this; }
	ConditionTargetSelector( const ConditionTargetSelector &_conditionTargetSelector ) { Assign( _conditionTargetSelector ); }
	virtual void Assign( const ConditionTargetSelector &_conditionTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConditionTargetSelector * pOther = dynamic_cast< const ConditionTargetSelector * > ( _pResource );
		if ( pOther ) ConditionTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ConvertTargetToLand : public SingleTargetSelector
{
	DBRESOURCE_METHODS( ConvertTargetToLand );
public:
	enum { typeId = 0x9E71EBC1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ConvertTargetToLand::typeId; }
	TargetToLandMode aggregateMode;
	Ptr< TargetSelector > targetSelector;

	ConvertTargetToLand();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConvertTargetToLand& operator = ( const ConvertTargetToLand &_convertTargetToLand ) { Assign( _convertTargetToLand ); return *this; }
	ConvertTargetToLand( const ConvertTargetToLand &_convertTargetToLand ) { Assign( _convertTargetToLand ); }
	virtual void Assign( const ConvertTargetToLand &_convertTargetToLand );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConvertTargetToLand * pOther = dynamic_cast< const ConvertTargetToLand * > ( _pResource );
		if ( pOther ) ConvertTargetToLand::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct CountingTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( CountingTargetSelector );
public:
	enum { typeId = 0xE776A5C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CountingTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableIntString targetsNumber;
	bool heroesFirst;
	bool enableSorting;
	ExecutableFloatString sortingValue;
	ESortingOrder order;

	CountingTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CountingTargetSelector& operator = ( const CountingTargetSelector &_countingTargetSelector ) { Assign( _countingTargetSelector ); return *this; }
	CountingTargetSelector( const CountingTargetSelector &_countingTargetSelector ) { Assign( _countingTargetSelector ); }
	virtual void Assign( const CountingTargetSelector &_countingTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CountingTargetSelector * pOther = dynamic_cast< const CountingTargetSelector * > ( _pResource );
		if ( pOther ) CountingTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct CreateGlyphApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( CreateGlyphApplicator );
public:
	enum { typeId = 0xE77AF500 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CreateGlyphApplicator::typeId; }
	Ptr< Glyph > glyph;
	float distance;
	float angle;
	float radius;
	bool angleIsRelative;
	CVec2 absolutePosition;
	string scriptName;

	CreateGlyphApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CreateGlyphApplicator& operator = ( const CreateGlyphApplicator &_createGlyphApplicator ) { Assign( _createGlyphApplicator ); return *this; }
	CreateGlyphApplicator( const CreateGlyphApplicator &_createGlyphApplicator ) { Assign( _createGlyphApplicator ); }
	virtual void Assign( const CreateGlyphApplicator &_createGlyphApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CreateGlyphApplicator * pOther = dynamic_cast< const CreateGlyphApplicator * > ( _pResource );
		if ( pOther ) CreateGlyphApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct CreepBehaviourChangeApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( CreepBehaviourChangeApplicator );
public:
	enum { typeId = 0x9E677A81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CreepBehaviourChangeApplicator::typeId; }
	EBehaviourChangeFlags behaviourChangeFlags;
	vector< Ptr< BaseApplicator > > applicators;
	string summonGroupName;
	Ptr< SummonBehaviourBase > behaviour;

	CreepBehaviourChangeApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CreepBehaviourChangeApplicator& operator = ( const CreepBehaviourChangeApplicator &_creepBehaviourChangeApplicator ) { Assign( _creepBehaviourChangeApplicator ); return *this; }
	CreepBehaviourChangeApplicator( const CreepBehaviourChangeApplicator &_creepBehaviourChangeApplicator ) { Assign( _creepBehaviourChangeApplicator ); }
	virtual void Assign( const CreepBehaviourChangeApplicator &_creepBehaviourChangeApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CreepBehaviourChangeApplicator * pOther = dynamic_cast< const CreepBehaviourChangeApplicator * > ( _pResource );
		if ( pOther ) CreepBehaviourChangeApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DamageApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( DamageApplicator );
public:
	enum { typeId = 0x9E5C0B01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DamageApplicator::typeId; }
	ExecutableFloatString damage;
	EApplicatorDamageType damageType;
	EDamageMode damageMode;
	bool cancelInvisibility;
	Ptr< UIEvent > uiEvent;
	float timeLimiter;

	DamageApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DamageApplicator& operator = ( const DamageApplicator &_damageApplicator ) { Assign( _damageApplicator ); return *this; }
	DamageApplicator( const DamageApplicator &_damageApplicator ) { Assign( _damageApplicator ); }
	virtual void Assign( const DamageApplicator &_damageApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DamageApplicator * pOther = dynamic_cast< const DamageApplicator * > ( _pResource );
		if ( pOther ) DamageApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DamageReflectApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( DamageReflectApplicator );
public:
	enum { typeId = 0x9E5C0B0A };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DamageReflectApplicator::typeId; }
	float amountInPersent;

	DamageReflectApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DamageReflectApplicator& operator = ( const DamageReflectApplicator &_damageReflectApplicator ) { Assign( _damageReflectApplicator ); return *this; }
	DamageReflectApplicator( const DamageReflectApplicator &_damageReflectApplicator ) { Assign( _damageReflectApplicator ); }
	virtual void Assign( const DamageReflectApplicator &_damageReflectApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DamageReflectApplicator * pOther = dynamic_cast< const DamageReflectApplicator * > ( _pResource );
		if ( pOther ) DamageReflectApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DamagingLinksTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( DamagingLinksTargetSelector );
public:
	enum { typeId = 0x9A9C5CD0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DamagingLinksTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > linkEndsSelector;
	Ptr< MultipleTargetSelector > linkTargetsSelector;
	ExecutableFloatString moveRange;
	ExecutableFloatString minRangeFromLinkEnds;
	ExecutableFloatString maxRangeFromLinkEnds;

	DamagingLinksTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DamagingLinksTargetSelector& operator = ( const DamagingLinksTargetSelector &_damagingLinksTargetSelector ) { Assign( _damagingLinksTargetSelector ); return *this; }
	DamagingLinksTargetSelector( const DamagingLinksTargetSelector &_damagingLinksTargetSelector ) { Assign( _damagingLinksTargetSelector ); }
	virtual void Assign( const DamagingLinksTargetSelector &_damagingLinksTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DamagingLinksTargetSelector * pOther = dynamic_cast< const DamagingLinksTargetSelector * > ( _pResource );
		if ( pOther ) DamagingLinksTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct DayNightTransitionApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( DayNightTransitionApplicator );
public:
	enum { typeId = 0x15CBF300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DayNightTransitionApplicator::typeId; }
	EDayNightState desiredState;
	float desiredStateFraction;

	DayNightTransitionApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DayNightTransitionApplicator& operator = ( const DayNightTransitionApplicator &_dayNightTransitionApplicator ) { Assign( _dayNightTransitionApplicator ); return *this; }
	DayNightTransitionApplicator( const DayNightTransitionApplicator &_dayNightTransitionApplicator ) { Assign( _dayNightTransitionApplicator ); }
	virtual void Assign( const DayNightTransitionApplicator &_dayNightTransitionApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DayNightTransitionApplicator * pOther = dynamic_cast< const DayNightTransitionApplicator * > ( _pResource );
		if ( pOther ) DayNightTransitionApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DealedDamageConverterApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( DealedDamageConverterApplicator );
public:
	enum { typeId = 0x9E5C0B0C };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DealedDamageConverterApplicator::typeId; }
	float scale;
	float deltaTime;
	EHealTarget type;

	DealedDamageConverterApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DealedDamageConverterApplicator& operator = ( const DealedDamageConverterApplicator &_dealedDamageConverterApplicator ) { Assign( _dealedDamageConverterApplicator ); return *this; }
	DealedDamageConverterApplicator( const DealedDamageConverterApplicator &_dealedDamageConverterApplicator ) { Assign( _dealedDamageConverterApplicator ); }
	virtual void Assign( const DealedDamageConverterApplicator &_dealedDamageConverterApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DealedDamageConverterApplicator * pOther = dynamic_cast< const DealedDamageConverterApplicator * > ( _pResource );
		if ( pOther ) DealedDamageConverterApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DefaultFormulas : public DbResource
{
	DBRESOURCE_METHODS( DefaultFormulas );
public:
	enum { typeId = 0x0F664BC9 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DefaultFormulas::typeId; }
	vector< ExecutableFloatString > floatFormulas;
	vector< ExecutableBoolString > boolFormulas;
	vector< ExecutableIntString > intFormulas;

	DefaultFormulas();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DefaultFormulas& operator = ( const DefaultFormulas &_defaultFormulas ) { Assign( _defaultFormulas ); return *this; }
	DefaultFormulas( const DefaultFormulas &_defaultFormulas ) { Assign( _defaultFormulas ); }
	virtual void Assign( const DefaultFormulas &_defaultFormulas );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DefaultFormulas * pOther = dynamic_cast< const DefaultFormulas * > ( _pResource );
		if ( pOther ) DefaultFormulas::Assign( *pOther );
	}
};

struct DelayTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( DelayTargetSelector );
public:
	enum { typeId = 0x9A9C5C41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DelayTargetSelector::typeId; }
	Ptr< TargetSelector > targetSelector;
	ExecutableFloatString delay;

	DelayTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DelayTargetSelector& operator = ( const DelayTargetSelector &_delayTargetSelector ) { Assign( _delayTargetSelector ); return *this; }
	DelayTargetSelector( const DelayTargetSelector &_delayTargetSelector ) { Assign( _delayTargetSelector ); }
	virtual void Assign( const DelayTargetSelector &_delayTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DelayTargetSelector * pOther = dynamic_cast< const DelayTargetSelector * > ( _pResource );
		if ( pOther ) DelayTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct DelegateDamageApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( DelegateDamageApplicator );
public:
	enum { typeId = 0xE7873440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DelegateDamageApplicator::typeId; }
	ExecutableFloatString damageToDelegate;
	ExecutableFloatString damageToApply;
	ExecutableFloatString totalDamage;
	EDelegateDamageFlags flags;
	bool infiniteTotalDamage;
	bool ignoreDefences;
	bool forceDontAttackBack;
	Ptr< TargetSelector > delegateTargets;
	ExecutableBoolString stopCondition;

	DelegateDamageApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DelegateDamageApplicator& operator = ( const DelegateDamageApplicator &_delegateDamageApplicator ) { Assign( _delegateDamageApplicator ); return *this; }
	DelegateDamageApplicator( const DelegateDamageApplicator &_delegateDamageApplicator ) { Assign( _delegateDamageApplicator ); }
	virtual void Assign( const DelegateDamageApplicator &_delegateDamageApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DelegateDamageApplicator * pOther = dynamic_cast< const DelegateDamageApplicator * > ( _pResource );
		if ( pOther ) DelegateDamageApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct Dispatch : public DbResource
{
public:
	enum { typeId = 0xA0678C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Dispatch::typeId; }
	vector< Ptr< EffectBase > > dispatchEffect;
	vector< Ptr< EffectBase > > applyEffect;
	EApplyEffectOrientation applyEffectOrientation;
	int applyEffectRandomAnglePoints;
	bool dieAfterApply;
	bool alwaysApply;
	bool applyEffectIgnoreVisibility;
	EDispatchFlags flags;

	Dispatch();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Dispatch& operator = ( const Dispatch &_dispatch ) { Assign( _dispatch ); return *this; }
	Dispatch( const Dispatch &_dispatch ) { Assign( _dispatch ); }
	virtual void Assign( const Dispatch &_dispatch );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Dispatch * pOther = dynamic_cast< const Dispatch * > ( _pResource );
		if ( pOther ) Dispatch::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchContinuous : public Dispatch
{
	DBRESOURCE_METHODS( DispatchContinuous );
public:
	enum { typeId = 0xA067A400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchContinuous::typeId; }
	vector< Ptr< BaseApplicator > > persistentApplicators;

	DispatchContinuous();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchContinuous& operator = ( const DispatchContinuous &_dispatchContinuous ) { Assign( _dispatchContinuous ); return *this; }
	DispatchContinuous( const DispatchContinuous &_dispatchContinuous ) { Assign( _dispatchContinuous ); }
	virtual void Assign( const DispatchContinuous &_dispatchContinuous );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchContinuous * pOther = dynamic_cast< const DispatchContinuous * > ( _pResource );
		if ( pOther ) DispatchContinuous::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchByTime : public DispatchContinuous
{
	DBRESOURCE_METHODS( DispatchByTime );
public:
	enum { typeId = 0xA0678C02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchByTime::typeId; }
	ExecutableFloatString lifeTime;
	bool cancelOnSenderDeath;

	DispatchByTime();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchByTime& operator = ( const DispatchByTime &_dispatchByTime ) { Assign( _dispatchByTime ); return *this; }
	DispatchByTime( const DispatchByTime &_dispatchByTime ) { Assign( _dispatchByTime ); }
	virtual void Assign( const DispatchByTime &_dispatchByTime );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchByTime * pOther = dynamic_cast< const DispatchByTime * > ( _pResource );
		if ( pOther ) DispatchByTime::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchCursor : public DispatchContinuous
{
	DBRESOURCE_METHODS( DispatchCursor );
public:
	enum { typeId = 0x8D85DC80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchCursor::typeId; }
	ExecutableFloatString speed;
	ExecutableFloatString maxSpeed;
	string fromLocator;
	float height;
	ExecutableFloatString lifeTime;
	int cursorUpdateFrequency;
	float linkRange;
	Ptr< LightningEffect > linkEffect;
	Ptr< AOEMaterial > maxRangeMaterial;
	float size;

	DispatchCursor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchCursor& operator = ( const DispatchCursor &_dispatchCursor ) { Assign( _dispatchCursor ); return *this; }
	DispatchCursor( const DispatchCursor &_dispatchCursor ) { Assign( _dispatchCursor ); }
	virtual void Assign( const DispatchCursor &_dispatchCursor );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchCursor * pOther = dynamic_cast< const DispatchCursor * > ( _pResource );
		if ( pOther ) DispatchCursor::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchImmediate : public Dispatch
{
	DBRESOURCE_METHODS( DispatchImmediate );
public:
	enum { typeId = 0xA0678C01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchImmediate::typeId; }
	bool instantApply;

	DispatchImmediate();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchImmediate& operator = ( const DispatchImmediate &_dispatchImmediate ) { Assign( _dispatchImmediate ); return *this; }
	DispatchImmediate( const DispatchImmediate &_dispatchImmediate ) { Assign( _dispatchImmediate ); }
	virtual void Assign( const DispatchImmediate &_dispatchImmediate );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchImmediate * pOther = dynamic_cast< const DispatchImmediate * > ( _pResource );
		if ( pOther ) DispatchImmediate::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchLinear : public DispatchContinuous
{
	DBRESOURCE_METHODS( DispatchLinear );
public:
	enum { typeId = 0xA0678C03 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchLinear::typeId; }
	EDispatchAiming aiming;
	float maxDeviation;
	float speed;
	bool locatorOrient;
	string fromLocator;
	string toLocator;
	float height;
	EDispatchFlyMode flyMode;
	float maxDistance;
	float minRise;
	float maxRise;
	bool killEffect;
	float suspendTime;

	DispatchLinear();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchLinear& operator = ( const DispatchLinear &_dispatchLinear ) { Assign( _dispatchLinear ); return *this; }
	DispatchLinear( const DispatchLinear &_dispatchLinear ) { Assign( _dispatchLinear ); }
	virtual void Assign( const DispatchLinear &_dispatchLinear );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchLinear * pOther = dynamic_cast< const DispatchLinear * > ( _pResource );
		if ( pOther ) DispatchLinear::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchLinearWithLink : public DispatchLinear
{
	DBRESOURCE_METHODS( DispatchLinearWithLink );
public:
	enum { typeId = 0xA067BBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchLinearWithLink::typeId; }
	vector< LightningLink > links;

	DispatchLinearWithLink();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchLinearWithLink& operator = ( const DispatchLinearWithLink &_dispatchLinearWithLink ) { Assign( _dispatchLinearWithLink ); return *this; }
	DispatchLinearWithLink( const DispatchLinearWithLink &_dispatchLinearWithLink ) { Assign( _dispatchLinearWithLink ); }
	virtual void Assign( const DispatchLinearWithLink &_dispatchLinearWithLink );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchLinearWithLink * pOther = dynamic_cast< const DispatchLinearWithLink * > ( _pResource );
		if ( pOther ) DispatchLinearWithLink::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispatchRockmanMace : public DispatchLinearWithLink
{
	DBRESOURCE_METHODS( DispatchRockmanMace );
public:
	enum { typeId = 0xA073CA80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispatchRockmanMace::typeId; }
	float minDistance;

	DispatchRockmanMace();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispatchRockmanMace& operator = ( const DispatchRockmanMace &_dispatchRockmanMace ) { Assign( _dispatchRockmanMace ); return *this; }
	DispatchRockmanMace( const DispatchRockmanMace &_dispatchRockmanMace ) { Assign( _dispatchRockmanMace ); }
	virtual void Assign( const DispatchRockmanMace &_dispatchRockmanMace );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispatchRockmanMace * pOther = dynamic_cast< const DispatchRockmanMace * > ( _pResource );
		if ( pOther ) DispatchRockmanMace::Assign( *pOther );
	}

	virtual NWorld::PFDispatch* Create( NWorld::PFDispatchCreateParams const &cp ) const;
};

struct DispellApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( DispellApplicator );
public:
	enum { typeId = 0x9E67DB00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispellApplicator::typeId; }
	ExecutableIntString maxEffectsToDispell;
	Ptr< TargetSelector > targets;

	DispellApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispellApplicator& operator = ( const DispellApplicator &_dispellApplicator ) { Assign( _dispellApplicator ); return *this; }
	DispellApplicator( const DispellApplicator &_dispellApplicator ) { Assign( _dispellApplicator ); }
	virtual void Assign( const DispellApplicator &_dispellApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispellApplicator * pOther = dynamic_cast< const DispellApplicator * > ( _pResource );
		if ( pOther ) DispellApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct DispellCastLimitation : public CastLimitation
{
	DBRESOURCE_METHODS( DispellCastLimitation );
public:
	enum { typeId = 0x9E71CB82 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DispellCastLimitation::typeId; }

	DispellCastLimitation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DispellCastLimitation& operator = ( const DispellCastLimitation &_dispellCastLimitation ) { Assign( _dispellCastLimitation ); return *this; }
	DispellCastLimitation( const DispellCastLimitation &_dispellCastLimitation ) { Assign( _dispellCastLimitation ); }
	virtual void Assign( const DispellCastLimitation &_dispellCastLimitation );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DispellCastLimitation * pOther = dynamic_cast< const DispellCastLimitation * > ( _pResource );
		if ( pOther ) DispellCastLimitation::Assign( *pOther );
	}

	virtual const NWorld::PFAbilityData* Check( NWorld::CastLimitationsCheckParams const &cp ) const;
};

struct DropTreeApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( DropTreeApplicator );
public:
	enum { typeId = 0x0F622B41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DropTreeApplicator::typeId; }

	DropTreeApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DropTreeApplicator& operator = ( const DropTreeApplicator &_dropTreeApplicator ) { Assign( _dropTreeApplicator ); return *this; }
	DropTreeApplicator( const DropTreeApplicator &_dropTreeApplicator ) { Assign( _dropTreeApplicator ); }
	virtual void Assign( const DropTreeApplicator &_dropTreeApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DropTreeApplicator * pOther = dynamic_cast< const DropTreeApplicator * > ( _pResource );
		if ( pOther ) DropTreeApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct EventProcessorBase : public DbResource
{
public:
	EApplicatorApplyTarget applyTarget;
	Ptr< Spell > spell;

	EventProcessorBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorBase& operator = ( const EventProcessorBase &_eventProcessorBase ) { Assign( _eventProcessorBase ); return *this; }
	EventProcessorBase( const EventProcessorBase &_eventProcessorBase ) { Assign( _eventProcessorBase ); }
	virtual void Assign( const EventProcessorBase &_eventProcessorBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorBase * pOther = dynamic_cast< const EventProcessorBase * > ( _pResource );
		if ( pOther ) EventProcessorBase::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorApplicatorApplied : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorApplicatorApplied );
public:
	enum { typeId = 0x0F72C2C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorApplicatorApplied::typeId; }
	ETriggerAbilitiesAbilitiesFlags filter;
	Ptr< ApplicatorsList > applicatorTypesList;
	Ptr< ApplicatorsList > applicatorsList;
	EApplicatorAppliedMode mode;
	ExecutableFloatString newLifetime;
	EApplicatorApplyTarget senderMatchTarget;
	ETriggerEventCheckSender checkSender;

	EventProcessorApplicatorApplied();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorApplicatorApplied& operator = ( const EventProcessorApplicatorApplied &_eventProcessorApplicatorApplied ) { Assign( _eventProcessorApplicatorApplied ); return *this; }
	EventProcessorApplicatorApplied( const EventProcessorApplicatorApplied &_eventProcessorApplicatorApplied ) { Assign( _eventProcessorApplicatorApplied ); }
	virtual void Assign( const EventProcessorApplicatorApplied &_eventProcessorApplicatorApplied );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorApplicatorApplied * pOther = dynamic_cast< const EventProcessorApplicatorApplied * > ( _pResource );
		if ( pOther ) EventProcessorApplicatorApplied::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorAbilityManacostTransformer : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorAbilityManacostTransformer );
public:
	enum { typeId = 0x0F729C41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorAbilityManacostTransformer::typeId; }
	TriggerAbilitiesFilter filter;

	EventProcessorAbilityManacostTransformer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorAbilityManacostTransformer& operator = ( const EventProcessorAbilityManacostTransformer &_eventProcessorAbilityManacostTransformer ) { Assign( _eventProcessorAbilityManacostTransformer ); return *this; }
	EventProcessorAbilityManacostTransformer( const EventProcessorAbilityManacostTransformer &_eventProcessorAbilityManacostTransformer ) { Assign( _eventProcessorAbilityManacostTransformer ); }
	virtual void Assign( const EventProcessorAbilityManacostTransformer &_eventProcessorAbilityManacostTransformer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorAbilityManacostTransformer * pOther = dynamic_cast< const EventProcessorAbilityManacostTransformer * > ( _pResource );
		if ( pOther ) EventProcessorAbilityManacostTransformer::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorCancelDispatch : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorCancelDispatch );
public:
	enum { typeId = 0x0F728300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorCancelDispatch::typeId; }
	TriggerAbilitiesFilter filter;
	EApplicatorApplyTarget senderMatchTarget;
	ETriggerEventCheckSender checkSender;

	EventProcessorCancelDispatch();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorCancelDispatch& operator = ( const EventProcessorCancelDispatch &_eventProcessorCancelDispatch ) { Assign( _eventProcessorCancelDispatch ); return *this; }
	EventProcessorCancelDispatch( const EventProcessorCancelDispatch &_eventProcessorCancelDispatch ) { Assign( _eventProcessorCancelDispatch ); }
	virtual void Assign( const EventProcessorCancelDispatch &_eventProcessorCancelDispatch );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorCancelDispatch * pOther = dynamic_cast< const EventProcessorCancelDispatch * > ( _pResource );
		if ( pOther ) EventProcessorCancelDispatch::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorCondition : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorCondition );
public:
	enum { typeId = 0x0F724340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorCondition::typeId; }
	EBaseUnitEventFlags events;
	ExecutableBoolString condition;
	bool onlyParent;

	EventProcessorCondition();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorCondition& operator = ( const EventProcessorCondition &_eventProcessorCondition ) { Assign( _eventProcessorCondition ); return *this; }
	EventProcessorCondition( const EventProcessorCondition &_eventProcessorCondition ) { Assign( _eventProcessorCondition ); }
	virtual void Assign( const EventProcessorCondition &_eventProcessorCondition );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorCondition * pOther = dynamic_cast< const EventProcessorCondition * > ( _pResource );
		if ( pOther ) EventProcessorCondition::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorDamageTransformer : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorDamageTransformer );
public:
	enum { typeId = 0x0F729C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorDamageTransformer::typeId; }
	EDamageFilter damageTypeFilter;
	TriggerAbilitiesFilter abilityFilter;
	ExecutableFloatString add;
	ExecutableFloatString mul;
	EApplicatorApplyTarget senderMatchTarget;
	bool matchTargetInverted;
	bool treatDelegatedByDelegator;
	ESpellTarget objectFilter;
	ETriggerEventCheckSender checkSender;
	ETriggerEventFlags flags;

	EventProcessorDamageTransformer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorDamageTransformer& operator = ( const EventProcessorDamageTransformer &_eventProcessorDamageTransformer ) { Assign( _eventProcessorDamageTransformer ); return *this; }
	EventProcessorDamageTransformer( const EventProcessorDamageTransformer &_eventProcessorDamageTransformer ) { Assign( _eventProcessorDamageTransformer ); }
	virtual void Assign( const EventProcessorDamageTransformer &_eventProcessorDamageTransformer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorDamageTransformer * pOther = dynamic_cast< const EventProcessorDamageTransformer * > ( _pResource );
		if ( pOther ) EventProcessorDamageTransformer::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorGroup : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorGroup );
public:
	enum { typeId = 0x0F7563C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorGroup::typeId; }
	vector< Ptr< EventProcessorBase > > processors;

	EventProcessorGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorGroup& operator = ( const EventProcessorGroup &_eventProcessorGroup ) { Assign( _eventProcessorGroup ); return *this; }
	EventProcessorGroup( const EventProcessorGroup &_eventProcessorGroup ) { Assign( _eventProcessorGroup ); }
	virtual void Assign( const EventProcessorGroup &_eventProcessorGroup );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorGroup * pOther = dynamic_cast< const EventProcessorGroup * > ( _pResource );
		if ( pOther ) EventProcessorGroup::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorIncomingDamage : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorIncomingDamage );
public:
	enum { typeId = 0xE78A3CC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorIncomingDamage::typeId; }
	Ptr< DelegateDamageApplicator > damageDelegate;
	EApplicatorApplyTarget damageDelegateOwner;

	EventProcessorIncomingDamage();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorIncomingDamage& operator = ( const EventProcessorIncomingDamage &_eventProcessorIncomingDamage ) { Assign( _eventProcessorIncomingDamage ); return *this; }
	EventProcessorIncomingDamage( const EventProcessorIncomingDamage &_eventProcessorIncomingDamage ) { Assign( _eventProcessorIncomingDamage ); }
	virtual void Assign( const EventProcessorIncomingDamage &_eventProcessorIncomingDamage );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorIncomingDamage * pOther = dynamic_cast< const EventProcessorIncomingDamage * > ( _pResource );
		if ( pOther ) EventProcessorIncomingDamage::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorLastHit : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorLastHit );
public:
	enum { typeId = 0xE7768540 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorLastHit::typeId; }

	EventProcessorLastHit();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorLastHit& operator = ( const EventProcessorLastHit &_eventProcessorLastHit ) { Assign( _eventProcessorLastHit ); return *this; }
	EventProcessorLastHit( const EventProcessorLastHit &_eventProcessorLastHit ) { Assign( _eventProcessorLastHit ); }
	virtual void Assign( const EventProcessorLastHit &_eventProcessorLastHit );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorLastHit * pOther = dynamic_cast< const EventProcessorLastHit * > ( _pResource );
		if ( pOther ) EventProcessorLastHit::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorOnConsumableObtained : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorOnConsumableObtained );
public:
	enum { typeId = 0xE79B9C01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorOnConsumableObtained::typeId; }
	Ptr< Consumable > consumable;
	EConsumableOriginFlags origin;

	EventProcessorOnConsumableObtained();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorOnConsumableObtained& operator = ( const EventProcessorOnConsumableObtained &_eventProcessorOnConsumableObtained ) { Assign( _eventProcessorOnConsumableObtained ); return *this; }
	EventProcessorOnConsumableObtained( const EventProcessorOnConsumableObtained &_eventProcessorOnConsumableObtained ) { Assign( _eventProcessorOnConsumableObtained ); }
	virtual void Assign( const EventProcessorOnConsumableObtained &_eventProcessorOnConsumableObtained );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorOnConsumableObtained * pOther = dynamic_cast< const EventProcessorOnConsumableObtained * > ( _pResource );
		if ( pOther ) EventProcessorOnConsumableObtained::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorOnDeath : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorOnDeath );
public:
	enum { typeId = 0x0F72CB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorOnDeath::typeId; }
	ExecutableFloatString castSpellDelay;
	EApplicatorApplyTarget senderMatchTarget;
	ESpellTarget objectFilter;
	ETriggerEventCheckSender checkSender;

	EventProcessorOnDeath();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorOnDeath& operator = ( const EventProcessorOnDeath &_eventProcessorOnDeath ) { Assign( _eventProcessorOnDeath ); return *this; }
	EventProcessorOnDeath( const EventProcessorOnDeath &_eventProcessorOnDeath ) { Assign( _eventProcessorOnDeath ); }
	virtual void Assign( const EventProcessorOnDeath &_eventProcessorOnDeath );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorOnDeath * pOther = dynamic_cast< const EventProcessorOnDeath * > ( _pResource );
		if ( pOther ) EventProcessorOnDeath::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorOnTarget : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorOnTarget );
public:
	enum { typeId = 0x0F72CB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorOnTarget::typeId; }
	Ptr< TargetSelector > targetSelector;
	ExecutableFloatString minTargets;

	EventProcessorOnTarget();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorOnTarget& operator = ( const EventProcessorOnTarget &_eventProcessorOnTarget ) { Assign( _eventProcessorOnTarget ); return *this; }
	EventProcessorOnTarget( const EventProcessorOnTarget &_eventProcessorOnTarget ) { Assign( _eventProcessorOnTarget ); }
	virtual void Assign( const EventProcessorOnTarget &_eventProcessorOnTarget );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorOnTarget * pOther = dynamic_cast< const EventProcessorOnTarget * > ( _pResource );
		if ( pOther ) EventProcessorOnTarget::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorOnUseAbilityForceStrike : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorOnUseAbilityForceStrike );
public:
	enum { typeId = 0x0F741400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorOnUseAbilityForceStrike::typeId; }
	TriggerAbilitiesFilter filter;
	string applicatorName;

	EventProcessorOnUseAbilityForceStrike();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorOnUseAbilityForceStrike& operator = ( const EventProcessorOnUseAbilityForceStrike &_eventProcessorOnUseAbilityForceStrike ) { Assign( _eventProcessorOnUseAbilityForceStrike ); return *this; }
	EventProcessorOnUseAbilityForceStrike( const EventProcessorOnUseAbilityForceStrike &_eventProcessorOnUseAbilityForceStrike ) { Assign( _eventProcessorOnUseAbilityForceStrike ); }
	virtual void Assign( const EventProcessorOnUseAbilityForceStrike &_eventProcessorOnUseAbilityForceStrike );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorOnUseAbilityForceStrike * pOther = dynamic_cast< const EventProcessorOnUseAbilityForceStrike * > ( _pResource );
		if ( pOther ) EventProcessorOnUseAbilityForceStrike::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorOutgoingDamage : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorOutgoingDamage );
public:
	enum { typeId = 0xE7A69380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorOutgoingDamage::typeId; }
	EDamageFilter damageTypeFilter;
	TriggerAbilitiesFilter abilityFilter;
	ExecutableFloatString modifiedDamage;

	EventProcessorOutgoingDamage();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorOutgoingDamage& operator = ( const EventProcessorOutgoingDamage &_eventProcessorOutgoingDamage ) { Assign( _eventProcessorOutgoingDamage ); return *this; }
	EventProcessorOutgoingDamage( const EventProcessorOutgoingDamage &_eventProcessorOutgoingDamage ) { Assign( _eventProcessorOutgoingDamage ); }
	virtual void Assign( const EventProcessorOutgoingDamage &_eventProcessorOutgoingDamage );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorOutgoingDamage * pOther = dynamic_cast< const EventProcessorOutgoingDamage * > ( _pResource );
		if ( pOther ) EventProcessorOutgoingDamage::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorPickupGlyph : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorPickupGlyph );
public:
	enum { typeId = 0x37A78C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorPickupGlyph::typeId; }
	TriggerAbilitiesFilter filter;

	EventProcessorPickupGlyph();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorPickupGlyph& operator = ( const EventProcessorPickupGlyph &_eventProcessorPickupGlyph ) { Assign( _eventProcessorPickupGlyph ); return *this; }
	EventProcessorPickupGlyph( const EventProcessorPickupGlyph &_eventProcessorPickupGlyph ) { Assign( _eventProcessorPickupGlyph ); }
	virtual void Assign( const EventProcessorPickupGlyph &_eventProcessorPickupGlyph );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorPickupGlyph * pOther = dynamic_cast< const EventProcessorPickupGlyph * > ( _pResource );
		if ( pOther ) EventProcessorPickupGlyph::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EventProcessorUnitDieNearMe : public EventProcessorBase
{
	DBRESOURCE_METHODS( EventProcessorUnitDieNearMe );
public:
	enum { typeId = 0x0F72CB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EventProcessorUnitDieNearMe::typeId; }
	ExecutableFloatString range;
	ESpellTarget targets;
	UnitDieKillersFlags killerFlags;
	EApplicatorApplyTarget senderMatchTarget;
	ETriggerEventCheckSender checkSender;

	EventProcessorUnitDieNearMe();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EventProcessorUnitDieNearMe& operator = ( const EventProcessorUnitDieNearMe &_eventProcessorUnitDieNearMe ) { Assign( _eventProcessorUnitDieNearMe ); return *this; }
	EventProcessorUnitDieNearMe( const EventProcessorUnitDieNearMe &_eventProcessorUnitDieNearMe ) { Assign( _eventProcessorUnitDieNearMe ); }
	virtual void Assign( const EventProcessorUnitDieNearMe &_eventProcessorUnitDieNearMe );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EventProcessorUnitDieNearMe * pOther = dynamic_cast< const EventProcessorUnitDieNearMe * > ( _pResource );
		if ( pOther ) EventProcessorUnitDieNearMe::Assign( *pOther );
	}

	virtual NWorld::PFEventProcessorBase* Create( NWorld::PFWorld* world ) const;
};

struct EyeApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( EyeApplicator );
public:
	enum { typeId = 0x0F73BB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EyeApplicator::typeId; }
	ExecutableFloatString visRange;
	EFactionFlags flags;
	EApplicatorApplyTarget eyeTarget;
	bool cancelObstacles;

	EyeApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EyeApplicator& operator = ( const EyeApplicator &_eyeApplicator ) { Assign( _eyeApplicator ); return *this; }
	EyeApplicator( const EyeApplicator &_eyeApplicator ) { Assign( _eyeApplicator ); }
	virtual void Assign( const EyeApplicator &_eyeApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EyeApplicator * pOther = dynamic_cast< const EyeApplicator * > ( _pResource );
		if ( pOther ) EyeApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct FilterTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( FilterTargetSelector );
public:
	enum { typeId = 0x0F738B02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FilterTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	vector< Ptr< Unit > > suitableUnits;

	FilterTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FilterTargetSelector& operator = ( const FilterTargetSelector &_filterTargetSelector ) { Assign( _filterTargetSelector ); return *this; }
	FilterTargetSelector( const FilterTargetSelector &_filterTargetSelector ) { Assign( _filterTargetSelector ); }
	virtual void Assign( const FilterTargetSelector &_filterTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FilterTargetSelector * pOther = dynamic_cast< const FilterTargetSelector * > ( _pResource );
		if ( pOther ) FilterTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct FirstTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( FirstTargetSelector );
public:
	enum { typeId = 0x0F738B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FirstTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	bool nearestTarget;

	FirstTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FirstTargetSelector& operator = ( const FirstTargetSelector &_firstTargetSelector ) { Assign( _firstTargetSelector ); return *this; }
	FirstTargetSelector( const FirstTargetSelector &_firstTargetSelector ) { Assign( _firstTargetSelector ); }
	virtual void Assign( const FirstTargetSelector &_firstTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FirstTargetSelector * pOther = dynamic_cast< const FirstTargetSelector * > ( _pResource );
		if ( pOther ) FirstTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct FixToCenterTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( FixToCenterTargetSelector );
public:
	enum { typeId = 0xEF9752C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FixToCenterTargetSelector::typeId; }
	Ptr< SingleTargetSelector > targetSelector;
	string nameScriptArea;

	FixToCenterTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FixToCenterTargetSelector& operator = ( const FixToCenterTargetSelector &_fixToCenterTargetSelector ) { Assign( _fixToCenterTargetSelector ); return *this; }
	FixToCenterTargetSelector( const FixToCenterTargetSelector &_fixToCenterTargetSelector ) { Assign( _fixToCenterTargetSelector ); }
	virtual void Assign( const FixToCenterTargetSelector &_fixToCenterTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FixToCenterTargetSelector * pOther = dynamic_cast< const FixToCenterTargetSelector * > ( _pResource );
		if ( pOther ) FixToCenterTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct FlagsApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( FlagsApplicator );
public:
	enum { typeId = 0x9E5C0B06 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FlagsApplicator::typeId; }
	EUnitFlag flag;
	vector< Ptr< Ability > > talents;
	vector< Ptr< Ability > > consumables;
	EUseMode useListAs;

	FlagsApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FlagsApplicator& operator = ( const FlagsApplicator &_flagsApplicator ) { Assign( _flagsApplicator ); return *this; }
	FlagsApplicator( const FlagsApplicator &_flagsApplicator ) { Assign( _flagsApplicator ); }
	virtual void Assign( const FlagsApplicator &_flagsApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FlagsApplicator * pOther = dynamic_cast< const FlagsApplicator * > ( _pResource );
		if ( pOther ) FlagsApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct FlyApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( FlyApplicator );
public:
	enum { typeId = 0x2B789AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FlyApplicator::typeId; }
	float flightHeight;
	float startTime;
	float stopTime;
	float animatedStopTime;
	EGhostMoveMode collisionFlags;
	bool push;
	Ptr< Spell > startSpell;
	Ptr< Spell > stopSpell;
	vector< AnimStateChanger > replaceAnimations;
	float radiusFixObstacle;

	FlyApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FlyApplicator& operator = ( const FlyApplicator &_flyApplicator ) { Assign( _flyApplicator ); return *this; }
	FlyApplicator( const FlyApplicator &_flyApplicator ) { Assign( _flyApplicator ); }
	virtual void Assign( const FlyApplicator &_flyApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FlyApplicator * pOther = dynamic_cast< const FlyApplicator * > ( _pResource );
		if ( pOther ) FlyApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ForAllTargetsApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ForAllTargetsApplicator );
public:
	enum { typeId = 0x0B76BC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ForAllTargetsApplicator::typeId; }
	Ptr< MultipleTargetSelector > targets;
	Ptr< ProgramApplicator > program;
	EParentNotificationFlags continueEvents;
	EParentNotificationFlags stopEvents;
	bool skipTargetIfInvalid;

	ForAllTargetsApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ForAllTargetsApplicator& operator = ( const ForAllTargetsApplicator &_forAllTargetsApplicator ) { Assign( _forAllTargetsApplicator ); return *this; }
	ForAllTargetsApplicator( const ForAllTargetsApplicator &_forAllTargetsApplicator ) { Assign( _forAllTargetsApplicator ); }
	virtual void Assign( const ForAllTargetsApplicator &_forAllTargetsApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ForAllTargetsApplicator * pOther = dynamic_cast< const ForAllTargetsApplicator * > ( _pResource );
		if ( pOther ) ForAllTargetsApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct FountainTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( FountainTargetSelector );
public:
	enum { typeId = 0x0B720B42 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FountainTargetSelector::typeId; }

	FountainTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FountainTargetSelector& operator = ( const FountainTargetSelector &_fountainTargetSelector ) { Assign( _fountainTargetSelector ); return *this; }
	FountainTargetSelector( const FountainTargetSelector &_fountainTargetSelector ) { Assign( _fountainTargetSelector ); }
	virtual void Assign( const FountainTargetSelector &_fountainTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FountainTargetSelector * pOther = dynamic_cast< const FountainTargetSelector * > ( _pResource );
		if ( pOther ) FountainTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct FXApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( FXApplicator );
public:
	enum { typeId = 0xE7A6C480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FXApplicator::typeId; }
	Ptr< SingleTargetSelector > auxillaryTarget;
	EFXFlags flags;

	FXApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FXApplicator& operator = ( const FXApplicator &_fXApplicator ) { Assign( _fXApplicator ); return *this; }
	FXApplicator( const FXApplicator &_fXApplicator ) { Assign( _fXApplicator ); }
	virtual void Assign( const FXApplicator &_fXApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FXApplicator * pOther = dynamic_cast< const FXApplicator * > ( _pResource );
		if ( pOther ) FXApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct GhostMoveApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( GhostMoveApplicator );
public:
	enum { typeId = 0x0B74F480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GhostMoveApplicator::typeId; }
	EGhostMoveMode collisionFlags;
	bool pushUnits;

	GhostMoveApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GhostMoveApplicator& operator = ( const GhostMoveApplicator &_ghostMoveApplicator ) { Assign( _ghostMoveApplicator ); return *this; }
	GhostMoveApplicator( const GhostMoveApplicator &_ghostMoveApplicator ) { Assign( _ghostMoveApplicator ); }
	virtual void Assign( const GhostMoveApplicator &_ghostMoveApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GhostMoveApplicator * pOther = dynamic_cast< const GhostMoveApplicator * > ( _pResource );
		if ( pOther ) GhostMoveApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct GiveConsumable : public BaseApplicator
{
	DBRESOURCE_METHODS( GiveConsumable );
public:
	enum { typeId = 0xE79B9C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GiveConsumable::typeId; }
	Ptr< Consumable > consumable;
	ExecutableIntString amount;

	GiveConsumable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GiveConsumable& operator = ( const GiveConsumable &_giveConsumable ) { Assign( _giveConsumable ); return *this; }
	GiveConsumable( const GiveConsumable &_giveConsumable ) { Assign( _giveConsumable ); }
	virtual void Assign( const GiveConsumable &_giveConsumable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GiveConsumable * pOther = dynamic_cast< const GiveConsumable * > ( _pResource );
		if ( pOther ) GiveConsumable::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct HealApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( HealApplicator );
public:
	enum { typeId = 0xA0617B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HealApplicator::typeId; }
	ExecutableFloatString amount;
	EHealTarget healTarget;
	Ptr< UIEvent > uiEvent;
	bool ignoreHealingMods;

	HealApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HealApplicator& operator = ( const HealApplicator &_healApplicator ) { Assign( _healApplicator ); return *this; }
	HealApplicator( const HealApplicator &_healApplicator ) { Assign( _healApplicator ); }
	virtual void Assign( const HealApplicator &_healApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HealApplicator * pOther = dynamic_cast< const HealApplicator * > ( _pResource );
		if ( pOther ) HealApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct HeroEnumerator : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( HeroEnumerator );
public:
	enum { typeId = 0x9E67AB00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HeroEnumerator::typeId; }

	HeroEnumerator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroEnumerator& operator = ( const HeroEnumerator &_heroEnumerator ) { Assign( _heroEnumerator ); return *this; }
	HeroEnumerator( const HeroEnumerator &_heroEnumerator ) { Assign( _heroEnumerator ); }
	virtual void Assign( const HeroEnumerator &_heroEnumerator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroEnumerator * pOther = dynamic_cast< const HeroEnumerator * > ( _pResource );
		if ( pOther ) HeroEnumerator::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct HighlanderA1TargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( HighlanderA1TargetSelector );
public:
	enum { typeId = 0x0B76C240 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HighlanderA1TargetSelector::typeId; }
	ExecutableFloatString range;
	ExecutableFloatString targetCount;

	HighlanderA1TargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HighlanderA1TargetSelector& operator = ( const HighlanderA1TargetSelector &_highlanderA1TargetSelector ) { Assign( _highlanderA1TargetSelector ); return *this; }
	HighlanderA1TargetSelector( const HighlanderA1TargetSelector &_highlanderA1TargetSelector ) { Assign( _highlanderA1TargetSelector ); }
	virtual void Assign( const HighlanderA1TargetSelector &_highlanderA1TargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HighlanderA1TargetSelector * pOther = dynamic_cast< const HighlanderA1TargetSelector * > ( _pResource );
		if ( pOther ) HighlanderA1TargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct InvalidAbilityTargetApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( InvalidAbilityTargetApplicator );
public:
	enum { typeId = 0x15C7A800 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)InvalidAbilityTargetApplicator::typeId; }

	InvalidAbilityTargetApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	InvalidAbilityTargetApplicator& operator = ( const InvalidAbilityTargetApplicator &_invalidAbilityTargetApplicator ) { Assign( _invalidAbilityTargetApplicator ); return *this; }
	InvalidAbilityTargetApplicator( const InvalidAbilityTargetApplicator &_invalidAbilityTargetApplicator ) { Assign( _invalidAbilityTargetApplicator ); }
	virtual void Assign( const InvalidAbilityTargetApplicator &_invalidAbilityTargetApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const InvalidAbilityTargetApplicator * pOther = dynamic_cast< const InvalidAbilityTargetApplicator * > ( _pResource );
		if ( pOther ) InvalidAbilityTargetApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct InvisibilityApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( InvisibilityApplicator );
public:
	enum { typeId = 0x0B724A40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)InvisibilityApplicator::typeId; }
	ExecutableFloatString fadeIn;
	Ptr< Spell > onBecomeInvisible;
	bool ignoreCancel;

	InvisibilityApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	InvisibilityApplicator& operator = ( const InvisibilityApplicator &_invisibilityApplicator ) { Assign( _invisibilityApplicator ); return *this; }
	InvisibilityApplicator( const InvisibilityApplicator &_invisibilityApplicator ) { Assign( _invisibilityApplicator ); }
	virtual void Assign( const InvisibilityApplicator &_invisibilityApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const InvisibilityApplicator * pOther = dynamic_cast< const InvisibilityApplicator * > ( _pResource );
		if ( pOther ) InvisibilityApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct KickAwayApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( KickAwayApplicator );
public:
	enum { typeId = 0x9E5C0B0B };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)KickAwayApplicator::typeId; }
	float distance;

	KickAwayApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	KickAwayApplicator& operator = ( const KickAwayApplicator &_kickAwayApplicator ) { Assign( _kickAwayApplicator ); return *this; }
	KickAwayApplicator( const KickAwayApplicator &_kickAwayApplicator ) { Assign( _kickAwayApplicator ); }
	virtual void Assign( const KickAwayApplicator &_kickAwayApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const KickAwayApplicator * pOther = dynamic_cast< const KickAwayApplicator * > ( _pResource );
		if ( pOther ) KickAwayApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct KillApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( KillApplicator );
public:
	enum { typeId = 0x9E678B02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)KillApplicator::typeId; }
	EKillMode flag;
	bool dontGiveRewards;

	KillApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	KillApplicator& operator = ( const KillApplicator &_killApplicator ) { Assign( _killApplicator ); return *this; }
	KillApplicator( const KillApplicator &_killApplicator ) { Assign( _killApplicator ); }
	virtual void Assign( const KillApplicator &_killApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const KillApplicator * pOther = dynamic_cast< const KillApplicator * > ( _pResource );
		if ( pOther ) KillApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ListOfTargetSelectors : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( ListOfTargetSelectors );
public:
	enum { typeId = 0x0F738B01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ListOfTargetSelectors::typeId; }
	vector< Ptr< TargetSelector > > targetSelectors;

	ListOfTargetSelectors();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ListOfTargetSelectors& operator = ( const ListOfTargetSelectors &_listOfTargetSelectors ) { Assign( _listOfTargetSelectors ); return *this; }
	ListOfTargetSelectors( const ListOfTargetSelectors &_listOfTargetSelectors ) { Assign( _listOfTargetSelectors ); }
	virtual void Assign( const ListOfTargetSelectors &_listOfTargetSelectors );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ListOfTargetSelectors * pOther = dynamic_cast< const ListOfTargetSelectors * > ( _pResource );
		if ( pOther ) ListOfTargetSelectors::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct LockTilesApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( LockTilesApplicator );
public:
	enum { typeId = 0xA0757340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)LockTilesApplicator::typeId; }
	ObjectLockMask lockMask;
	CTRect<float> collision;
	bool pushCaster;

	LockTilesApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LockTilesApplicator& operator = ( const LockTilesApplicator &_lockTilesApplicator ) { Assign( _lockTilesApplicator ); return *this; }
	LockTilesApplicator( const LockTilesApplicator &_lockTilesApplicator ) { Assign( _lockTilesApplicator ); }
	virtual void Assign( const LockTilesApplicator &_lockTilesApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LockTilesApplicator * pOther = dynamic_cast< const LockTilesApplicator * > ( _pResource );
		if ( pOther ) LockTilesApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct MainBuildingTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( MainBuildingTargetSelector );
public:
	enum { typeId = 0x0B720B41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MainBuildingTargetSelector::typeId; }

	MainBuildingTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MainBuildingTargetSelector& operator = ( const MainBuildingTargetSelector &_mainBuildingTargetSelector ) { Assign( _mainBuildingTargetSelector ); return *this; }
	MainBuildingTargetSelector( const MainBuildingTargetSelector &_mainBuildingTargetSelector ) { Assign( _mainBuildingTargetSelector ); }
	virtual void Assign( const MainBuildingTargetSelector &_mainBuildingTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MainBuildingTargetSelector * pOther = dynamic_cast< const MainBuildingTargetSelector * > ( _pResource );
		if ( pOther ) MainBuildingTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct MarkerApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( MarkerApplicator );
public:
	enum { typeId = 0xE778BC81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MarkerApplicator::typeId; }
	ExecutableFloatString addValue;
	ExecutableFloatString multValue;

	MarkerApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MarkerApplicator& operator = ( const MarkerApplicator &_markerApplicator ) { Assign( _markerApplicator ); return *this; }
	MarkerApplicator( const MarkerApplicator &_markerApplicator ) { Assign( _markerApplicator ); }
	virtual void Assign( const MarkerApplicator &_markerApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MarkerApplicator * pOther = dynamic_cast< const MarkerApplicator * > ( _pResource );
		if ( pOther ) MarkerApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct MaximizingTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( MaximizingTargetSelector );
public:
	enum { typeId = 0x9A9C5C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MaximizingTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableFloatString range;
	ExecutableFloatString searchRange;
	ESpellTarget searchFilter;
	ExecutableIntString minTargetsNumber;

	MaximizingTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MaximizingTargetSelector& operator = ( const MaximizingTargetSelector &_maximizingTargetSelector ) { Assign( _maximizingTargetSelector ); return *this; }
	MaximizingTargetSelector( const MaximizingTargetSelector &_maximizingTargetSelector ) { Assign( _maximizingTargetSelector ); }
	virtual void Assign( const MaximizingTargetSelector &_maximizingTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MaximizingTargetSelector * pOther = dynamic_cast< const MaximizingTargetSelector * > ( _pResource );
		if ( pOther ) MaximizingTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct BasicMicroAI : public MicroAI
{
	DBRESOURCE_METHODS( BasicMicroAI );
public:
	ExecutableBoolString condition;
	bool castWhenIdle;

	BasicMicroAI();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicMicroAI& operator = ( const BasicMicroAI &_basicMicroAI ) { Assign( _basicMicroAI ); return *this; }
	BasicMicroAI( const BasicMicroAI &_basicMicroAI ) { Assign( _basicMicroAI ); }
	virtual void Assign( const BasicMicroAI &_basicMicroAI );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicMicroAI * pOther = dynamic_cast< const BasicMicroAI * > ( _pResource );
		if ( pOther ) BasicMicroAI::Assign( *pOther );
	}

	virtual NWorld::PFMicroAI* Create( NWorld::PFMicroAICreateParams const &cp ) const;
};

struct ModifyTerrainApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ModifyTerrainApplicator );
public:
	enum { typeId = 0x0E676B42 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ModifyTerrainApplicator::typeId; }
	ExecutableFloatString durationTime;
	ExecutableIntString faction;
	ExecutableFloatString modifRadius;

	ModifyTerrainApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ModifyTerrainApplicator& operator = ( const ModifyTerrainApplicator &_modifyTerrainApplicator ) { Assign( _modifyTerrainApplicator ); return *this; }
	ModifyTerrainApplicator( const ModifyTerrainApplicator &_modifyTerrainApplicator ) { Assign( _modifyTerrainApplicator ); }
	virtual void Assign( const ModifyTerrainApplicator &_modifyTerrainApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ModifyTerrainApplicator * pOther = dynamic_cast< const ModifyTerrainApplicator * > ( _pResource );
		if ( pOther ) ModifyTerrainApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct MountApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( MountApplicator );
public:
	enum { typeId = 0xE7777B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MountApplicator::typeId; }
	EApplicatorApplyTarget mountTarget;
	bool controlMount;

	MountApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MountApplicator& operator = ( const MountApplicator &_mountApplicator ) { Assign( _mountApplicator ); return *this; }
	MountApplicator( const MountApplicator &_mountApplicator ) { Assign( _mountApplicator ); }
	virtual void Assign( const MountApplicator &_mountApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MountApplicator * pOther = dynamic_cast< const MountApplicator * > ( _pResource );
		if ( pOther ) MountApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct MovementControlApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( MovementControlApplicator );
public:
	enum { typeId = 0x2C67DB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MovementControlApplicator::typeId; }

	MovementControlApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MovementControlApplicator& operator = ( const MovementControlApplicator &_movementControlApplicator ) { Assign( _movementControlApplicator ); return *this; }
	MovementControlApplicator( const MovementControlApplicator &_movementControlApplicator ) { Assign( _movementControlApplicator ); }
	virtual void Assign( const MovementControlApplicator &_movementControlApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MovementControlApplicator * pOther = dynamic_cast< const MovementControlApplicator * > ( _pResource );
		if ( pOther ) MovementControlApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct MoveToApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( MoveToApplicator );
public:
	enum { typeId = 0x0E676B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MoveToApplicator::typeId; }
	ExecutableFloatString moveRange;
	ExecutableFloatString moveSpeed;
	EApplicatorApplyTarget moveTarget;
	CVec2 offset;
	ExecutableBoolString isMoveDirect;
	bool pushUnits;
	bool justRotate;
	bool isNotStackable;

	MoveToApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MoveToApplicator& operator = ( const MoveToApplicator &_moveToApplicator ) { Assign( _moveToApplicator ); return *this; }
	MoveToApplicator( const MoveToApplicator &_moveToApplicator ) { Assign( _moveToApplicator ); }
	virtual void Assign( const MoveToApplicator &_moveToApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MoveToApplicator * pOther = dynamic_cast< const MoveToApplicator * > ( _pResource );
		if ( pOther ) MoveToApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ApplicatorRecipientsTargetSelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( ApplicatorRecipientsTargetSelector );
public:
	enum { typeId = 0xE7832C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ApplicatorRecipientsTargetSelector::typeId; }
	Ptr< BaseApplicator > applicator;

	ApplicatorRecipientsTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ApplicatorRecipientsTargetSelector& operator = ( const ApplicatorRecipientsTargetSelector &_applicatorRecipientsTargetSelector ) { Assign( _applicatorRecipientsTargetSelector ); return *this; }
	ApplicatorRecipientsTargetSelector( const ApplicatorRecipientsTargetSelector &_applicatorRecipientsTargetSelector ) { Assign( _applicatorRecipientsTargetSelector ); }
	virtual void Assign( const ApplicatorRecipientsTargetSelector &_applicatorRecipientsTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ApplicatorRecipientsTargetSelector * pOther = dynamic_cast< const ApplicatorRecipientsTargetSelector * > ( _pResource );
		if ( pOther ) ApplicatorRecipientsTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct AreaTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( AreaTargetSelector );
public:
	enum { typeId = 0x9E676B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AreaTargetSelector::typeId; }
	ExecutableFloatString range;
	CVec2 absolutePosition;
	Ptr< SingleTargetSelector > targetSelector;

	AreaTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AreaTargetSelector& operator = ( const AreaTargetSelector &_areaTargetSelector ) { Assign( _areaTargetSelector ); return *this; }
	AreaTargetSelector( const AreaTargetSelector &_areaTargetSelector ) { Assign( _areaTargetSelector ); }
	virtual void Assign( const AreaTargetSelector &_areaTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AreaTargetSelector * pOther = dynamic_cast< const AreaTargetSelector * > ( _pResource );
		if ( pOther ) AreaTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct MultipleTargetSelectorMicroAI : public BasicMicroAI
{
	DBRESOURCE_METHODS( MultipleTargetSelectorMicroAI );
public:
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableBoolString unitFilter;
	int minTargetCount;
	float minTargetWeight;

	MultipleTargetSelectorMicroAI();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MultipleTargetSelectorMicroAI& operator = ( const MultipleTargetSelectorMicroAI &_multipleTargetSelectorMicroAI ) { Assign( _multipleTargetSelectorMicroAI ); return *this; }
	MultipleTargetSelectorMicroAI( const MultipleTargetSelectorMicroAI &_multipleTargetSelectorMicroAI ) { Assign( _multipleTargetSelectorMicroAI ); }
	virtual void Assign( const MultipleTargetSelectorMicroAI &_multipleTargetSelectorMicroAI );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MultipleTargetSelectorMicroAI * pOther = dynamic_cast< const MultipleTargetSelectorMicroAI * > ( _pResource );
		if ( pOther ) MultipleTargetSelectorMicroAI::Assign( *pOther );
	}

	virtual NWorld::PFMicroAI* Create( NWorld::PFMicroAICreateParams const &cp ) const;
};

struct NaftaTransferApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( NaftaTransferApplicator );
public:
	enum { typeId = 0x0E676B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NaftaTransferApplicator::typeId; }
	EApplicatorApplyTarget naftaTransferTarget;
	ExecutableFloatString amount;
	ExecutableFloatString multiplier;
	ExecutableFloatString addition;
	Ptr< UIEvent > uiEvent;

	NaftaTransferApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NaftaTransferApplicator& operator = ( const NaftaTransferApplicator &_naftaTransferApplicator ) { Assign( _naftaTransferApplicator ); return *this; }
	NaftaTransferApplicator( const NaftaTransferApplicator &_naftaTransferApplicator ) { Assign( _naftaTransferApplicator ); }
	virtual void Assign( const NaftaTransferApplicator &_naftaTransferApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NaftaTransferApplicator * pOther = dynamic_cast< const NaftaTransferApplicator * > ( _pResource );
		if ( pOther ) NaftaTransferApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct NearestInAreaTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( NearestInAreaTargetSelector );
public:
	enum { typeId = 0x9E67EC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NearestInAreaTargetSelector::typeId; }
	ExecutableFloatString range;

	NearestInAreaTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NearestInAreaTargetSelector& operator = ( const NearestInAreaTargetSelector &_nearestInAreaTargetSelector ) { Assign( _nearestInAreaTargetSelector ); return *this; }
	NearestInAreaTargetSelector( const NearestInAreaTargetSelector &_nearestInAreaTargetSelector ) { Assign( _nearestInAreaTargetSelector ); }
	virtual void Assign( const NearestInAreaTargetSelector &_nearestInAreaTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NearestInAreaTargetSelector * pOther = dynamic_cast< const NearestInAreaTargetSelector * > ( _pResource );
		if ( pOther ) NearestInAreaTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct NearestTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( NearestTargetSelector );
public:
	enum { typeId = 0x9E6C8340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NearestTargetSelector::typeId; }
	Ptr< TargetSelector > targetSelector;

	NearestTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NearestTargetSelector& operator = ( const NearestTargetSelector &_nearestTargetSelector ) { Assign( _nearestTargetSelector ); return *this; }
	NearestTargetSelector( const NearestTargetSelector &_nearestTargetSelector ) { Assign( _nearestTargetSelector ); }
	virtual void Assign( const NearestTargetSelector &_nearestTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NearestTargetSelector * pOther = dynamic_cast< const NearestTargetSelector * > ( _pResource );
		if ( pOther ) NearestTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct NotTargetOfSameAbilitySelector : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( NotTargetOfSameAbilitySelector );
public:
	enum { typeId = 0x9A9C6C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NotTargetOfSameAbilitySelector::typeId; }
	Ptr< TargetSelector > targetSelector;
	Ptr< TargetSelector > abilityCastersSelector;
	ExecutableFloatString minDistBetweenTargets;

	NotTargetOfSameAbilitySelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NotTargetOfSameAbilitySelector& operator = ( const NotTargetOfSameAbilitySelector &_notTargetOfSameAbilitySelector ) { Assign( _notTargetOfSameAbilitySelector ); return *this; }
	NotTargetOfSameAbilitySelector( const NotTargetOfSameAbilitySelector &_notTargetOfSameAbilitySelector ) { Assign( _notTargetOfSameAbilitySelector ); }
	virtual void Assign( const NotTargetOfSameAbilitySelector &_notTargetOfSameAbilitySelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NotTargetOfSameAbilitySelector * pOther = dynamic_cast< const NotTargetOfSameAbilitySelector * > ( _pResource );
		if ( pOther ) NotTargetOfSameAbilitySelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct OnDamageApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( OnDamageApplicator );
public:
	enum { typeId = 0x9E5C0B07 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)OnDamageApplicator::typeId; }
	EDamageFilter filterFlags;
	Ptr< Spell > spell;
	EApplicatorApplyTarget spellTarget;

	OnDamageApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	OnDamageApplicator& operator = ( const OnDamageApplicator &_onDamageApplicator ) { Assign( _onDamageApplicator ); return *this; }
	OnDamageApplicator( const OnDamageApplicator &_onDamageApplicator ) { Assign( _onDamageApplicator ); }
	virtual void Assign( const OnDamageApplicator &_onDamageApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const OnDamageApplicator * pOther = dynamic_cast< const OnDamageApplicator * > ( _pResource );
		if ( pOther ) OnDamageApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct PermanentStatModApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( PermanentStatModApplicator );
public:
	enum { typeId = 0x9E688C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PermanentStatModApplicator::typeId; }
	Modifier modifier;

	PermanentStatModApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PermanentStatModApplicator& operator = ( const PermanentStatModApplicator &_permanentStatModApplicator ) { Assign( _permanentStatModApplicator ); return *this; }
	PermanentStatModApplicator( const PermanentStatModApplicator &_permanentStatModApplicator ) { Assign( _permanentStatModApplicator ); }
	virtual void Assign( const PermanentStatModApplicator &_permanentStatModApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PermanentStatModApplicator * pOther = dynamic_cast< const PermanentStatModApplicator * > ( _pResource );
		if ( pOther ) PermanentStatModApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct PickupChannelingApplicator : public ChannellingApplicator
{
	DBRESOURCE_METHODS( PickupChannelingApplicator );
public:
	enum { typeId = 0xE7A4F3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PickupChannelingApplicator::typeId; }

	PickupChannelingApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PickupChannelingApplicator& operator = ( const PickupChannelingApplicator &_pickupChannelingApplicator ) { Assign( _pickupChannelingApplicator ); return *this; }
	PickupChannelingApplicator( const PickupChannelingApplicator &_pickupChannelingApplicator ) { Assign( _pickupChannelingApplicator ); }
	virtual void Assign( const PickupChannelingApplicator &_pickupChannelingApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PickupChannelingApplicator * pOther = dynamic_cast< const PickupChannelingApplicator * > ( _pResource );
		if ( pOther ) PickupChannelingApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct PointTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( PointTargetSelector );
public:
	enum { typeId = 0x1E728BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PointTargetSelector::typeId; }
	Ptr< SingleTargetSelector > targetSelector;
	EPointTargetSelectorMode mode;
	ExecutableFloatString range;
	CVec2 offset;
	ETraceMode traceMode;
	bool checkMinRange;
	bool paralleledTarget;

	PointTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PointTargetSelector& operator = ( const PointTargetSelector &_pointTargetSelector ) { Assign( _pointTargetSelector ); return *this; }
	PointTargetSelector( const PointTargetSelector &_pointTargetSelector ) { Assign( _pointTargetSelector ); }
	virtual void Assign( const PointTargetSelector &_pointTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PointTargetSelector * pOther = dynamic_cast< const PointTargetSelector * > ( _pResource );
		if ( pOther ) PointTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct PositionCastLimitation : public CastLimitation
{
	DBRESOURCE_METHODS( PositionCastLimitation );
public:
	enum { typeId = 0x5BB4ABC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PositionCastLimitation::typeId; }
	ExecutableBooleanString condition;

	PositionCastLimitation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PositionCastLimitation& operator = ( const PositionCastLimitation &_positionCastLimitation ) { Assign( _positionCastLimitation ); return *this; }
	PositionCastLimitation( const PositionCastLimitation &_positionCastLimitation ) { Assign( _positionCastLimitation ); }
	virtual void Assign( const PositionCastLimitation &_positionCastLimitation );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PositionCastLimitation * pOther = dynamic_cast< const PositionCastLimitation * > ( _pResource );
		if ( pOther ) PositionCastLimitation::Assign( *pOther );
	}

	virtual const NWorld::PFAbilityData* Check( NWorld::CastLimitationsCheckParams const &cp ) const;
};

struct ProgramApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ProgramApplicator );
public:
	enum { typeId = 0x9E676A80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ProgramApplicator::typeId; }
	vector< ApplicatorToExecute > applicators;

	ProgramApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ProgramApplicator& operator = ( const ProgramApplicator &_programApplicator ) { Assign( _programApplicator ); return *this; }
	ProgramApplicator( const ProgramApplicator &_programApplicator ) { Assign( _programApplicator ); }
	virtual void Assign( const ProgramApplicator &_programApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ProgramApplicator * pOther = dynamic_cast< const ProgramApplicator * > ( _pResource );
		if ( pOther ) ProgramApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct RaiseFlagApplicator : public ChannellingApplicator
{
	DBRESOURCE_METHODS( RaiseFlagApplicator );
public:
	enum { typeId = 0x0B76AA41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)RaiseFlagApplicator::typeId; }

	RaiseFlagApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RaiseFlagApplicator& operator = ( const RaiseFlagApplicator &_raiseFlagApplicator ) { Assign( _raiseFlagApplicator ); return *this; }
	RaiseFlagApplicator( const RaiseFlagApplicator &_raiseFlagApplicator ) { Assign( _raiseFlagApplicator ); }
	virtual void Assign( const RaiseFlagApplicator &_raiseFlagApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RaiseFlagApplicator * pOther = dynamic_cast< const RaiseFlagApplicator * > ( _pResource );
		if ( pOther ) RaiseFlagApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct RefreshCooldownApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( RefreshCooldownApplicator );
public:
	enum { typeId = 0x9E79AD18 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)RefreshCooldownApplicator::typeId; }
	EAbilityIdFlags flags;
	bool refreshThis;
	ExecutableFloatString reductionAmount;
	vector< Ptr< Ability > > talents;
	EUseMode useListAs;
	bool allowCdIncrease;
	bool reduceByPercent;

	RefreshCooldownApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RefreshCooldownApplicator& operator = ( const RefreshCooldownApplicator &_refreshCooldownApplicator ) { Assign( _refreshCooldownApplicator ); return *this; }
	RefreshCooldownApplicator( const RefreshCooldownApplicator &_refreshCooldownApplicator ) { Assign( _refreshCooldownApplicator ); }
	virtual void Assign( const RefreshCooldownApplicator &_refreshCooldownApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RefreshCooldownApplicator * pOther = dynamic_cast< const RefreshCooldownApplicator * > ( _pResource );
		if ( pOther ) RefreshCooldownApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct RelativeUnitTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( RelativeUnitTargetSelector );
public:
	enum { typeId = 0x9E6C8400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)RelativeUnitTargetSelector::typeId; }
	EUnitRelation relation;

	RelativeUnitTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RelativeUnitTargetSelector& operator = ( const RelativeUnitTargetSelector &_relativeUnitTargetSelector ) { Assign( _relativeUnitTargetSelector ); return *this; }
	RelativeUnitTargetSelector( const RelativeUnitTargetSelector &_relativeUnitTargetSelector ) { Assign( _relativeUnitTargetSelector ); }
	virtual void Assign( const RelativeUnitTargetSelector &_relativeUnitTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RelativeUnitTargetSelector * pOther = dynamic_cast< const RelativeUnitTargetSelector * > ( _pResource );
		if ( pOther ) RelativeUnitTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ResurrectApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ResurrectApplicator );
public:
	enum { typeId = 0x2C6C8442 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ResurrectApplicator::typeId; }
	float healthPercent;
	float energyPercent;

	ResurrectApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ResurrectApplicator& operator = ( const ResurrectApplicator &_resurrectApplicator ) { Assign( _resurrectApplicator ); return *this; }
	ResurrectApplicator( const ResurrectApplicator &_resurrectApplicator ) { Assign( _resurrectApplicator ); }
	virtual void Assign( const ResurrectApplicator &_resurrectApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ResurrectApplicator * pOther = dynamic_cast< const ResurrectApplicator * > ( _pResource );
		if ( pOther ) ResurrectApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ScaleControlApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ScaleControlApplicator );
public:
	enum { typeId = 0x9A9CA341 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScaleControlApplicator::typeId; }
	ExecutableFloatString desiredScale;
	ExecutableFloatString changeSpeed;

	ScaleControlApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScaleControlApplicator& operator = ( const ScaleControlApplicator &_scaleControlApplicator ) { Assign( _scaleControlApplicator ); return *this; }
	ScaleControlApplicator( const ScaleControlApplicator &_scaleControlApplicator ) { Assign( _scaleControlApplicator ); }
	virtual void Assign( const ScaleControlApplicator &_scaleControlApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScaleControlApplicator * pOther = dynamic_cast< const ScaleControlApplicator * > ( _pResource );
		if ( pOther ) ScaleControlApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SceneObjectChangeApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( SceneObjectChangeApplicator );
public:
	enum { typeId = 0x2B7B8C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SceneObjectChangeApplicator::typeId; }
	vector< Ptr< DBSceneObject > > sceneObjects;
	ExecutableIntString sceneObjectIndex;

	SceneObjectChangeApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SceneObjectChangeApplicator& operator = ( const SceneObjectChangeApplicator &_sceneObjectChangeApplicator ) { Assign( _sceneObjectChangeApplicator ); return *this; }
	SceneObjectChangeApplicator( const SceneObjectChangeApplicator &_sceneObjectChangeApplicator ) { Assign( _sceneObjectChangeApplicator ); }
	virtual void Assign( const SceneObjectChangeApplicator &_sceneObjectChangeApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SceneObjectChangeApplicator * pOther = dynamic_cast< const SceneObjectChangeApplicator * > ( _pResource );
		if ( pOther ) SceneObjectChangeApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SectorTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( SectorTargetSelector );
public:
	enum { typeId = 0x9E6C8A40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SectorTargetSelector::typeId; }
	ETargetSelectorPoint segmentBegin;
	ETargetSelectorPoint segmentEnd;
	ExecutableFloatString range;
	float angle;
	bool centerIsSegmentEnd;
	float segmentDirectionOffset;

	SectorTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SectorTargetSelector& operator = ( const SectorTargetSelector &_sectorTargetSelector ) { Assign( _sectorTargetSelector ); return *this; }
	SectorTargetSelector( const SectorTargetSelector &_sectorTargetSelector ) { Assign( _sectorTargetSelector ); }
	virtual void Assign( const SectorTargetSelector &_sectorTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SectorTargetSelector * pOther = dynamic_cast< const SectorTargetSelector * > ( _pResource );
		if ( pOther ) SectorTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct SelectApplicatorTarget : public SingleTargetSelector
{
	DBRESOURCE_METHODS( SelectApplicatorTarget );
public:
	enum { typeId = 0xE77B1C80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SelectApplicatorTarget::typeId; }
	EApplicatorApplyTarget selectTarget;
	string applicatorName;
	int applicatorIndex;
	EApplicatorApplyTarget namedApplicatorTarget;

	SelectApplicatorTarget();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SelectApplicatorTarget& operator = ( const SelectApplicatorTarget &_selectApplicatorTarget ) { Assign( _selectApplicatorTarget ); return *this; }
	SelectApplicatorTarget( const SelectApplicatorTarget &_selectApplicatorTarget ) { Assign( _selectApplicatorTarget ); }
	virtual void Assign( const SelectApplicatorTarget &_selectApplicatorTarget );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SelectApplicatorTarget * pOther = dynamic_cast< const SelectApplicatorTarget * > ( _pResource );
		if ( pOther ) SelectApplicatorTarget::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct SetAdvancedSummonTargetApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SetAdvancedSummonTargetApplicator );
public:
	enum { typeId = 0x15D320C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SetAdvancedSummonTargetApplicator::typeId; }

	SetAdvancedSummonTargetApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SetAdvancedSummonTargetApplicator& operator = ( const SetAdvancedSummonTargetApplicator &_setAdvancedSummonTargetApplicator ) { Assign( _setAdvancedSummonTargetApplicator ); return *this; }
	SetAdvancedSummonTargetApplicator( const SetAdvancedSummonTargetApplicator &_setAdvancedSummonTargetApplicator ) { Assign( _setAdvancedSummonTargetApplicator ); }
	virtual void Assign( const SetAdvancedSummonTargetApplicator &_setAdvancedSummonTargetApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SetAdvancedSummonTargetApplicator * pOther = dynamic_cast< const SetAdvancedSummonTargetApplicator * > ( _pResource );
		if ( pOther ) SetAdvancedSummonTargetApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SetTimescaleApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SetTimescaleApplicator );
public:
	enum { typeId = 0x15CBF400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SetTimescaleApplicator::typeId; }
	float desiredTimescale;

	SetTimescaleApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SetTimescaleApplicator& operator = ( const SetTimescaleApplicator &_setTimescaleApplicator ) { Assign( _setTimescaleApplicator ); return *this; }
	SetTimescaleApplicator( const SetTimescaleApplicator &_setTimescaleApplicator ) { Assign( _setTimescaleApplicator ); }
	virtual void Assign( const SetTimescaleApplicator &_setTimescaleApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SetTimescaleApplicator * pOther = dynamic_cast< const SetTimescaleApplicator * > ( _pResource );
		if ( pOther ) SetTimescaleApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ShiftApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ShiftApplicator );
public:
	enum { typeId = 0x1E726440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ShiftApplicator::typeId; }
	EApplicatorApplyTarget shiftTarget;
	Ptr< SingleTargetSelector > targetSelector;

	ShiftApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ShiftApplicator& operator = ( const ShiftApplicator &_shiftApplicator ) { Assign( _shiftApplicator ); return *this; }
	ShiftApplicator( const ShiftApplicator &_shiftApplicator ) { Assign( _shiftApplicator ); }
	virtual void Assign( const ShiftApplicator &_shiftApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ShiftApplicator * pOther = dynamic_cast< const ShiftApplicator * > ( _pResource );
		if ( pOther ) ShiftApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ShopTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( ShopTargetSelector );
public:
	enum { typeId = 0x0F756BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ShopTargetSelector::typeId; }
	bool secret;

	ShopTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ShopTargetSelector& operator = ( const ShopTargetSelector &_shopTargetSelector ) { Assign( _shopTargetSelector ); return *this; }
	ShopTargetSelector( const ShopTargetSelector &_shopTargetSelector ) { Assign( _shopTargetSelector ); }
	virtual void Assign( const ShopTargetSelector &_shopTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ShopTargetSelector * pOther = dynamic_cast< const ShopTargetSelector * > ( _pResource );
		if ( pOther ) ShopTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ComparingTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( ComparingTargetSelector );
public:
	enum { typeId = 0xE776B440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ComparingTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;
	ExecutableFloatString referenceValue;
	ExecutableFloatString valueToCompare;

	ComparingTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ComparingTargetSelector& operator = ( const ComparingTargetSelector &_comparingTargetSelector ) { Assign( _comparingTargetSelector ); return *this; }
	ComparingTargetSelector( const ComparingTargetSelector &_comparingTargetSelector ) { Assign( _comparingTargetSelector ); }
	virtual void Assign( const ComparingTargetSelector &_comparingTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ComparingTargetSelector * pOther = dynamic_cast< const ComparingTargetSelector * > ( _pResource );
		if ( pOther ) ComparingTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct BaseAttack : public Ability
{
	DBRESOURCE_METHODS( BaseAttack );
public:
	enum { typeId = 0x2C5CCAC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BaseAttack::typeId; }
	bool isMelee;

	BaseAttack();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BaseAttack& operator = ( const BaseAttack &_baseAttack ) { Assign( _baseAttack ); return *this; }
	BaseAttack( const BaseAttack &_baseAttack ) { Assign( _baseAttack ); }
	virtual void Assign( const BaseAttack &_baseAttack );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BaseAttack * pOther = dynamic_cast< const BaseAttack * > ( _pResource );
		if ( pOther ) BaseAttack::Assign( *pOther );
	}
};

struct SpellApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SpellApplicator );
public:
	enum { typeId = 0x9E677240 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpellApplicator::typeId; }
	Ptr< TargetSelector > targetSelector;
	EApplicatorApplyTarget spellTarget;
	Ptr< Spell > spell;

	SpellApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpellApplicator& operator = ( const SpellApplicator &_spellApplicator ) { Assign( _spellApplicator ); return *this; }
	SpellApplicator( const SpellApplicator &_spellApplicator ) { Assign( _spellApplicator ); }
	virtual void Assign( const SpellApplicator &_spellApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpellApplicator * pOther = dynamic_cast< const SpellApplicator * > ( _pResource );
		if ( pOther ) SpellApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SpellPeriodicallyApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( SpellPeriodicallyApplicator );
public:
	enum { typeId = 0x9E5C0B08 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpellPeriodicallyApplicator::typeId; }
	ExecutableFloatString period;
	ExecutableFloatString startOffset;
	EScaleCalculationMode scaleMode;
	Ptr< TargetSelector > targetSelector;
	Ptr< Spell > spell;

	SpellPeriodicallyApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpellPeriodicallyApplicator& operator = ( const SpellPeriodicallyApplicator &_spellPeriodicallyApplicator ) { Assign( _spellPeriodicallyApplicator ); return *this; }
	SpellPeriodicallyApplicator( const SpellPeriodicallyApplicator &_spellPeriodicallyApplicator ) { Assign( _spellPeriodicallyApplicator ); }
	virtual void Assign( const SpellPeriodicallyApplicator &_spellPeriodicallyApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpellPeriodicallyApplicator * pOther = dynamic_cast< const SpellPeriodicallyApplicator * > ( _pResource );
		if ( pOther ) SpellPeriodicallyApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SpellPeriodicallyVisualApplicator : public SpellPeriodicallyApplicator
{
	DBRESOURCE_METHODS( SpellPeriodicallyVisualApplicator );
public:
	enum { typeId = 0x9E6CF400 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpellPeriodicallyVisualApplicator::typeId; }
	ExecutableFloatString attackTimeOffset;

	SpellPeriodicallyVisualApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpellPeriodicallyVisualApplicator& operator = ( const SpellPeriodicallyVisualApplicator &_spellPeriodicallyVisualApplicator ) { Assign( _spellPeriodicallyVisualApplicator ); return *this; }
	SpellPeriodicallyVisualApplicator( const SpellPeriodicallyVisualApplicator &_spellPeriodicallyVisualApplicator ) { Assign( _spellPeriodicallyVisualApplicator ); }
	virtual void Assign( const SpellPeriodicallyVisualApplicator &_spellPeriodicallyVisualApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpellPeriodicallyVisualApplicator * pOther = dynamic_cast< const SpellPeriodicallyVisualApplicator * > ( _pResource );
		if ( pOther ) SpellPeriodicallyVisualApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SpellProbabilityApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SpellProbabilityApplicator );
public:
	enum { typeId = 0x9E5C0BFD };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpellProbabilityApplicator::typeId; }
	ExecutableFloatString probability;
	Ptr< Spell > spell;
	Ptr< Spell > spellIfFailed;

	SpellProbabilityApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpellProbabilityApplicator& operator = ( const SpellProbabilityApplicator &_spellProbabilityApplicator ) { Assign( _spellProbabilityApplicator ); return *this; }
	SpellProbabilityApplicator( const SpellProbabilityApplicator &_spellProbabilityApplicator ) { Assign( _spellProbabilityApplicator ); }
	virtual void Assign( const SpellProbabilityApplicator &_spellProbabilityApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpellProbabilityApplicator * pOther = dynamic_cast< const SpellProbabilityApplicator * > ( _pResource );
		if ( pOther ) SpellProbabilityApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SpellSwitchApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SpellSwitchApplicator );
public:
	enum { typeId = 0x0E674B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpellSwitchApplicator::typeId; }
	ExecutableIntString activeSpellIndex;
	bool dontUseDispatches;
	vector< Ptr< Spell > > spells;

	SpellSwitchApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpellSwitchApplicator& operator = ( const SpellSwitchApplicator &_spellSwitchApplicator ) { Assign( _spellSwitchApplicator ); return *this; }
	SpellSwitchApplicator( const SpellSwitchApplicator &_spellSwitchApplicator ) { Assign( _spellSwitchApplicator ); }
	virtual void Assign( const SpellSwitchApplicator &_spellSwitchApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpellSwitchApplicator * pOther = dynamic_cast< const SpellSwitchApplicator * > ( _pResource );
		if ( pOther ) SpellSwitchApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct StatModApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( StatModApplicator );
public:
	enum { typeId = 0x9E5C0B03 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)StatModApplicator::typeId; }
	Modifier modifier;
	bool dontUpdate;
	string statModName;
	EStatConstraint constraint;

	StatModApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatModApplicator& operator = ( const StatModApplicator &_statModApplicator ) { Assign( _statModApplicator ); return *this; }
	StatModApplicator( const StatModApplicator &_statModApplicator ) { Assign( _statModApplicator ); }
	virtual void Assign( const StatModApplicator &_statModApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatModApplicator * pOther = dynamic_cast< const StatModApplicator * > ( _pResource );
		if ( pOther ) StatModApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct StatusApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( StatusApplicator );
public:
	enum { typeId = 0x9E688BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)StatusApplicator::typeId; }
	CTextRef name;
	CTextRef description;
	Ptr< Texture > image;
	int stackCount;
	EStackingRule stackableAcrossUnits;
	int power;
	EDispellPriority dispellPriority;
	EStopBehaviour stopBehaviour;
	vector< Ptr< BaseApplicator > > applicators;
	Ptr< ApplicatorsList > unstackableWith;
	ExecutableIntString customCounter;
	ExecutableFloatString customProgress;
	int statusPosition;
	EStatusFlags flags;

	StatusApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StatusApplicator& operator = ( const StatusApplicator &_statusApplicator ) { Assign( _statusApplicator ); return *this; }
	StatusApplicator( const StatusApplicator &_statusApplicator ) { Assign( _statusApplicator ); }
	virtual void Assign( const StatusApplicator &_statusApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StatusApplicator * pOther = dynamic_cast< const StatusApplicator * > ( _pResource );
		if ( pOther ) StatusApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SummonApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( SummonApplicator );
public:
	enum { typeId = 0x0F730BC3 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SummonApplicator::typeId; }
	SummonSource summonSource;
	vector< Ptr< Summoned > > summonedUnits;
	ExecutableIntString summonedUnitIndex;
	ExecutableIntString summonedUnitsCount;
	Ptr< SummonBehaviourBase > behaviour;
	Ptr< SingleTargetSelector > placeSelector;
	SummonPlaceMode placeMode;
	ExecutableFloatString lifeTime;
	vector< Ptr< BaseApplicator > > applicators;
	ESummonFlags flags;
	SpawnStats spawnStats;
	ExecutableFloatString takeModDmg;
	ESpellTarget takeTypeUnit;
	bool openWarFog;
	ExecutableFloatString unsummonSortCriterion;
	string summonGroupName;

	SummonApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SummonApplicator& operator = ( const SummonApplicator &_summonApplicator ) { Assign( _summonApplicator ); return *this; }
	SummonApplicator( const SummonApplicator &_summonApplicator ) { Assign( _summonApplicator ); }
	virtual void Assign( const SummonApplicator &_summonApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SummonApplicator * pOther = dynamic_cast< const SummonApplicator * > ( _pResource );
		if ( pOther ) SummonApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct SummonBehaviourBase : public DbResource
{
public:
	enum { typeId = 0x0F730BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SummonBehaviourBase::typeId; }

	SummonBehaviourBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SummonBehaviourBase& operator = ( const SummonBehaviourBase &_summonBehaviourBase ) { Assign( _summonBehaviourBase ); return *this; }
	SummonBehaviourBase( const SummonBehaviourBase &_summonBehaviourBase ) { Assign( _summonBehaviourBase ); }
	virtual void Assign( const SummonBehaviourBase &_summonBehaviourBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SummonBehaviourBase * pOther = dynamic_cast< const SummonBehaviourBase * > ( _pResource );
		if ( pOther ) SummonBehaviourBase::Assign( *pOther );
	}

	virtual NWorld::PFSummonBehaviourDataBase* Create() const;
};

struct SummonBehaviourCommon : public SummonBehaviourBase
{
	DBRESOURCE_METHODS( SummonBehaviourCommon );
public:
	enum { typeId = 0x0F730BC1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SummonBehaviourCommon::typeId; }
	SummonType summonType;
	ExecutableIntString maxCount;
	ExecutableIntString maxThisCount;
	Ptr< UnitTargetingParameters > targetingParams;
	ExecutableFloatString lashRange;
	float responseRange;
	float responseTime;

	SummonBehaviourCommon();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SummonBehaviourCommon& operator = ( const SummonBehaviourCommon &_summonBehaviourCommon ) { Assign( _summonBehaviourCommon ); return *this; }
	SummonBehaviourCommon( const SummonBehaviourCommon &_summonBehaviourCommon ) { Assign( _summonBehaviourCommon ); }
	virtual void Assign( const SummonBehaviourCommon &_summonBehaviourCommon );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SummonBehaviourCommon * pOther = dynamic_cast< const SummonBehaviourCommon * > ( _pResource );
		if ( pOther ) SummonBehaviourCommon::Assign( *pOther );
	}

	virtual NWorld::PFSummonBehaviourDataBase* Create() const;
};

struct SummonBehaviourAdvanced : public SummonBehaviourCommon
{
	DBRESOURCE_METHODS( SummonBehaviourAdvanced );
public:
	enum { typeId = 0x15D32040 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SummonBehaviourAdvanced::typeId; }
	SummonBehaviourCommonParams guardBehaviourParams;
	SummonBehaviourCommonParams chaseBehaviourParams;

	SummonBehaviourAdvanced();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SummonBehaviourAdvanced& operator = ( const SummonBehaviourAdvanced &_summonBehaviourAdvanced ) { Assign( _summonBehaviourAdvanced ); return *this; }
	SummonBehaviourAdvanced( const SummonBehaviourAdvanced &_summonBehaviourAdvanced ) { Assign( _summonBehaviourAdvanced ); }
	virtual void Assign( const SummonBehaviourAdvanced &_summonBehaviourAdvanced );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SummonBehaviourAdvanced * pOther = dynamic_cast< const SummonBehaviourAdvanced * > ( _pResource );
		if ( pOther ) SummonBehaviourAdvanced::Assign( *pOther );
	}

	virtual NWorld::PFSummonBehaviourDataBase* Create() const;
};

struct SummonEnumerator : public MultipleTargetSelector
{
	DBRESOURCE_METHODS( SummonEnumerator );
public:
	enum { typeId = 0x9E677280 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SummonEnumerator::typeId; }
	SummonTypeFlags summonTypes;

	SummonEnumerator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SummonEnumerator& operator = ( const SummonEnumerator &_summonEnumerator ) { Assign( _summonEnumerator ); return *this; }
	SummonEnumerator( const SummonEnumerator &_summonEnumerator ) { Assign( _summonEnumerator ); }
	virtual void Assign( const SummonEnumerator &_summonEnumerator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SummonEnumerator * pOther = dynamic_cast< const SummonEnumerator * > ( _pResource );
		if ( pOther ) SummonEnumerator::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct TargetCastLimitation : public CastLimitation
{
	DBRESOURCE_METHODS( TargetCastLimitation );
public:
	enum { typeId = 0x9E71CB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TargetCastLimitation::typeId; }
	Ptr< TargetSelector > targetSelector;

	TargetCastLimitation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TargetCastLimitation& operator = ( const TargetCastLimitation &_targetCastLimitation ) { Assign( _targetCastLimitation ); return *this; }
	TargetCastLimitation( const TargetCastLimitation &_targetCastLimitation ) { Assign( _targetCastLimitation ); }
	virtual void Assign( const TargetCastLimitation &_targetCastLimitation );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TargetCastLimitation * pOther = dynamic_cast< const TargetCastLimitation * > ( _pResource );
		if ( pOther ) TargetCastLimitation::Assign( *pOther );
	}

	virtual const NWorld::PFAbilityData* Check( NWorld::CastLimitationsCheckParams const &cp ) const;
};

struct TargetsCounterApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( TargetsCounterApplicator );
public:
	enum { typeId = 0x0F739C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TargetsCounterApplicator::typeId; }
	Ptr< TargetSelector > targetSelector;

	TargetsCounterApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TargetsCounterApplicator& operator = ( const TargetsCounterApplicator &_targetsCounterApplicator ) { Assign( _targetsCounterApplicator ); return *this; }
	TargetsCounterApplicator( const TargetsCounterApplicator &_targetsCounterApplicator ) { Assign( _targetsCounterApplicator ); }
	virtual void Assign( const TargetsCounterApplicator &_targetsCounterApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TargetsCounterApplicator * pOther = dynamic_cast< const TargetsCounterApplicator * > ( _pResource );
		if ( pOther ) TargetsCounterApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct AttackersTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( AttackersTargetSelector );
public:
	enum { typeId = 0x9A9D43C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AttackersTargetSelector::typeId; }
	EAttackersType type;
	ExecutableFloatString damageDealTime;
	Ptr< SingleTargetSelector > targetSelector;

	AttackersTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AttackersTargetSelector& operator = ( const AttackersTargetSelector &_attackersTargetSelector ) { Assign( _attackersTargetSelector ); return *this; }
	AttackersTargetSelector( const AttackersTargetSelector &_attackersTargetSelector ) { Assign( _attackersTargetSelector ); }
	virtual void Assign( const AttackersTargetSelector &_attackersTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AttackersTargetSelector * pOther = dynamic_cast< const AttackersTargetSelector * > ( _pResource );
		if ( pOther ) AttackersTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct TargetSelectorMicroAI : public BasicMicroAI
{
	DBRESOURCE_METHODS( TargetSelectorMicroAI );
public:
	Ptr< SingleTargetSelector > targetSelector;

	TargetSelectorMicroAI();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TargetSelectorMicroAI& operator = ( const TargetSelectorMicroAI &_targetSelectorMicroAI ) { Assign( _targetSelectorMicroAI ); return *this; }
	TargetSelectorMicroAI( const TargetSelectorMicroAI &_targetSelectorMicroAI ) { Assign( _targetSelectorMicroAI ); }
	virtual void Assign( const TargetSelectorMicroAI &_targetSelectorMicroAI );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TargetSelectorMicroAI * pOther = dynamic_cast< const TargetSelectorMicroAI * > ( _pResource );
		if ( pOther ) TargetSelectorMicroAI::Assign( *pOther );
	}

	virtual NWorld::PFMicroAI* Create( NWorld::PFMicroAICreateParams const &cp ) const;
};

struct TauntApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( TauntApplicator );
public:
	enum { typeId = 0x9E5C0B09 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TauntApplicator::typeId; }
	EApplicatorApplyTarget tauntTarget;
	bool strongTarget;

	TauntApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TauntApplicator& operator = ( const TauntApplicator &_tauntApplicator ) { Assign( _tauntApplicator ); return *this; }
	TauntApplicator( const TauntApplicator &_tauntApplicator ) { Assign( _tauntApplicator ); }
	virtual void Assign( const TauntApplicator &_tauntApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TauntApplicator * pOther = dynamic_cast< const TauntApplicator * > ( _pResource );
		if ( pOther ) TauntApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct TeleportApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( TeleportApplicator );
public:
	enum { typeId = 0x9E67C380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TeleportApplicator::typeId; }
	EApplicatorApplyTarget teleportTarget;
	ExecutableFloatString maxDistance;
	Ptr< EffectBase > disappearEffect;
	Ptr< EffectBase > appearEffect;
	bool pushUnits;
	bool notifyInboundDispatches;

	TeleportApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TeleportApplicator& operator = ( const TeleportApplicator &_teleportApplicator ) { Assign( _teleportApplicator ); return *this; }
	TeleportApplicator( const TeleportApplicator &_teleportApplicator ) { Assign( _teleportApplicator ); }
	virtual void Assign( const TeleportApplicator &_teleportApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TeleportApplicator * pOther = dynamic_cast< const TeleportApplicator * > ( _pResource );
		if ( pOther ) TeleportApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct ThrowApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( ThrowApplicator );
public:
	enum { typeId = 0x1E729C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ThrowApplicator::typeId; }
	EThrowType flightType;
	EGhostMoveMode collisionFlags;
	Ptr< SingleTargetSelector > targetSelector;
	bool trackTargetUnit;
	Ptr< Spell > startSpell;
	Ptr< Spell > stopSpell;
	ExecutableFloatString moveSpeed;
	ExecutableFloatString flipTime;
	float maxHeight;
	float maxDistance;
	Animated<float, NDb::AnimatedAlgorithms::Linear> trajectory;
	Animated<float, NDb::AnimatedAlgorithms::Linear> angle;
	float takeOffTime;
	float landTime;
	bool surfaceSpeedFromAG;
	vector< Ptr< EffectBase > > flyEffect;
	EBuffBehavior behaviorFlags;
	bool lockRotation;
	Ptr< SingleTargetSelector > firstTargetToHit;

	ThrowApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ThrowApplicator& operator = ( const ThrowApplicator &_throwApplicator ) { Assign( _throwApplicator ); return *this; }
	ThrowApplicator( const ThrowApplicator &_throwApplicator ) { Assign( _throwApplicator ); }
	virtual void Assign( const ThrowApplicator &_throwApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ThrowApplicator * pOther = dynamic_cast< const ThrowApplicator * > ( _pResource );
		if ( pOther ) ThrowApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct TriggerApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( TriggerApplicator );
public:
	enum { typeId = 0x0F722380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TriggerApplicator::typeId; }
	ExecutableIntString actionsCount;
	Ptr< EventProcessorBase > processor;
	bool useAbilityCooldown;
	bool useAbilityOwnerMana;
	bool playAck;

	TriggerApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TriggerApplicator& operator = ( const TriggerApplicator &_triggerApplicator ) { Assign( _triggerApplicator ); return *this; }
	TriggerApplicator( const TriggerApplicator &_triggerApplicator ) { Assign( _triggerApplicator ); }
	virtual void Assign( const TriggerApplicator &_triggerApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TriggerApplicator * pOther = dynamic_cast< const TriggerApplicator * > ( _pResource );
		if ( pOther ) TriggerApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct UIMessageApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( UIMessageApplicator );
public:
	enum { typeId = 0x2C6C83C2 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIMessageApplicator::typeId; }
	CTextRef message;
	ExecutableFloatString value;
	Ptr< UIEvent > uiEvent;

	UIMessageApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIMessageApplicator& operator = ( const UIMessageApplicator &_uIMessageApplicator ) { Assign( _uIMessageApplicator ); return *this; }
	UIMessageApplicator( const UIMessageApplicator &_uIMessageApplicator ) { Assign( _uIMessageApplicator ); }
	virtual void Assign( const UIMessageApplicator &_uIMessageApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIMessageApplicator * pOther = dynamic_cast< const UIMessageApplicator * > ( _pResource );
		if ( pOther ) UIMessageApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct UnitConstant : public DbResource
{
	DBRESOURCE_METHODS( UnitConstant );
public:
	string name;
	ExecutableFloatString var;

	UnitConstant();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitConstant& operator = ( const UnitConstant &_unitConstant ) { Assign( _unitConstant ); return *this; }
	UnitConstant( const UnitConstant &_unitConstant ) { Assign( _unitConstant ); }
	virtual void Assign( const UnitConstant &_unitConstant );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitConstant * pOther = dynamic_cast< const UnitConstant * > ( _pResource );
		if ( pOther ) UnitConstant::Assign( *pOther );
	}
};

struct UnitConstantsContainer : public DbResource
{
	DBRESOURCE_METHODS( UnitConstantsContainer );
public:
	enum { typeId = 0x0F64AC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UnitConstantsContainer::typeId; }
	vector< Ptr< UnitConstant > > vars;

	UnitConstantsContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitConstantsContainer& operator = ( const UnitConstantsContainer &_unitConstantsContainer ) { Assign( _unitConstantsContainer ); return *this; }
	UnitConstantsContainer( const UnitConstantsContainer &_unitConstantsContainer ) { Assign( _unitConstantsContainer ); }
	virtual void Assign( const UnitConstantsContainer &_unitConstantsContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitConstantsContainer * pOther = dynamic_cast< const UnitConstantsContainer * > ( _pResource );
		if ( pOther ) UnitConstantsContainer::Assign( *pOther );
	}
};

struct UnitEnumerator : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( UnitEnumerator );
public:
	enum { typeId = 0x9E677300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UnitEnumerator::typeId; }

	UnitEnumerator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitEnumerator& operator = ( const UnitEnumerator &_unitEnumerator ) { Assign( _unitEnumerator ); return *this; }
	UnitEnumerator( const UnitEnumerator &_unitEnumerator ) { Assign( _unitEnumerator ); }
	virtual void Assign( const UnitEnumerator &_unitEnumerator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitEnumerator * pOther = dynamic_cast< const UnitEnumerator * > ( _pResource );
		if ( pOther ) UnitEnumerator::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct UnitPlaceCorrector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( UnitPlaceCorrector );
public:
	enum { typeId = 0x9E71DB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UnitPlaceCorrector::typeId; }
	Ptr< SingleTargetSelector > targetSelector;
	bool checkByRangeToRequester;
	bool nativeTerrainOnly;
	float radius;
	ETraceMode passabilityCheckMode;
	bool checkLineOfSight;

	UnitPlaceCorrector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitPlaceCorrector& operator = ( const UnitPlaceCorrector &_unitPlaceCorrector ) { Assign( _unitPlaceCorrector ); return *this; }
	UnitPlaceCorrector( const UnitPlaceCorrector &_unitPlaceCorrector ) { Assign( _unitPlaceCorrector ); }
	virtual void Assign( const UnitPlaceCorrector &_unitPlaceCorrector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitPlaceCorrector * pOther = dynamic_cast< const UnitPlaceCorrector * > ( _pResource );
		if ( pOther ) UnitPlaceCorrector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct UnitShiftTarget : public SingleTargetSelector
{
	DBRESOURCE_METHODS( UnitShiftTarget );
public:
	enum { typeId = 0x1E728BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UnitShiftTarget::typeId; }
	ExecutableFloatString distance;

	UnitShiftTarget();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitShiftTarget& operator = ( const UnitShiftTarget &_unitShiftTarget ) { Assign( _unitShiftTarget ); return *this; }
	UnitShiftTarget( const UnitShiftTarget &_unitShiftTarget ) { Assign( _unitShiftTarget ); }
	virtual void Assign( const UnitShiftTarget &_unitShiftTarget );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitShiftTarget * pOther = dynamic_cast< const UnitShiftTarget * > ( _pResource );
		if ( pOther ) UnitShiftTarget::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct ValueApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( ValueApplicator );
public:
	enum { typeId = 0x0F73BB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ValueApplicator::typeId; }
	ExecutableFloatString value;

	ValueApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ValueApplicator& operator = ( const ValueApplicator &_valueApplicator ) { Assign( _valueApplicator ); return *this; }
	ValueApplicator( const ValueApplicator &_valueApplicator ) { Assign( _valueApplicator ); }
	virtual void Assign( const ValueApplicator &_valueApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ValueApplicator * pOther = dynamic_cast< const ValueApplicator * > ( _pResource );
		if ( pOther ) ValueApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct VariableProxyApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( VariableProxyApplicator );
public:
	enum { typeId = 0xE778BC80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)VariableProxyApplicator::typeId; }
	vector< ApplicatorToProxy > applicators;

	VariableProxyApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	VariableProxyApplicator& operator = ( const VariableProxyApplicator &_variableProxyApplicator ) { Assign( _variableProxyApplicator ); return *this; }
	VariableProxyApplicator( const VariableProxyApplicator &_variableProxyApplicator ) { Assign( _variableProxyApplicator ); }
	virtual void Assign( const VariableProxyApplicator &_variableProxyApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const VariableProxyApplicator * pOther = dynamic_cast< const VariableProxyApplicator * > ( _pResource );
		if ( pOther ) VariableProxyApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct VictoryApplicator : public BaseApplicator
{
	DBRESOURCE_METHODS( VictoryApplicator );
public:
	enum { typeId = 0xE77B4C80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)VictoryApplicator::typeId; }
	bool destroyMainBuilding;
	bool oppositeFaction;

	VictoryApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	VictoryApplicator& operator = ( const VictoryApplicator &_victoryApplicator ) { Assign( _victoryApplicator ); return *this; }
	VictoryApplicator( const VictoryApplicator &_victoryApplicator ) { Assign( _victoryApplicator ); }
	virtual void Assign( const VictoryApplicator &_victoryApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const VictoryApplicator * pOther = dynamic_cast< const VictoryApplicator * > ( _pResource );
		if ( pOther ) VictoryApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct WaitForSpellApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( WaitForSpellApplicator );
public:
	enum { typeId = 0x9E67ACC1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WaitForSpellApplicator::typeId; }
	EApplicatorApplyTarget spellTarget;
	Ptr< Spell > spell;
	EWaitForSpellBehaviour behaviour;
	Ptr< SingleTargetSelector > firstTargetToHit;
	Ptr< SingleTargetSelector > dispatchSource;

	WaitForSpellApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WaitForSpellApplicator& operator = ( const WaitForSpellApplicator &_waitForSpellApplicator ) { Assign( _waitForSpellApplicator ); return *this; }
	WaitForSpellApplicator( const WaitForSpellApplicator &_waitForSpellApplicator ) { Assign( _waitForSpellApplicator ); }
	virtual void Assign( const WaitForSpellApplicator &_waitForSpellApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WaitForSpellApplicator * pOther = dynamic_cast< const WaitForSpellApplicator * > ( _pResource );
		if ( pOther ) WaitForSpellApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct WallTargetSelector : public MultipleTargetSelectorFiltered
{
	DBRESOURCE_METHODS( WallTargetSelector );
public:
	enum { typeId = 0xE79C9480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WallTargetSelector::typeId; }
	Ptr< SingleTargetSelector > origin;
	Ptr< SingleTargetSelector > direction;
	ExecutableFloatString length;
	ExecutableFloatString width;

	WallTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WallTargetSelector& operator = ( const WallTargetSelector &_wallTargetSelector ) { Assign( _wallTargetSelector ); return *this; }
	WallTargetSelector( const WallTargetSelector &_wallTargetSelector ) { Assign( _wallTargetSelector ); }
	virtual void Assign( const WallTargetSelector &_wallTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WallTargetSelector * pOther = dynamic_cast< const WallTargetSelector * > ( _pResource );
		if ( pOther ) WallTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

struct WatchApplicator : public BuffApplicator
{
	DBRESOURCE_METHODS( WatchApplicator );
public:
	enum { typeId = 0x9E678B04 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WatchApplicator::typeId; }
	EParentNotification onSenderDispatchApply;
	EParentNotification onSenderDispatchEvade;
	EParentNotification onUnitDeath;
	EParentNotification onFinish;
	EParentNotification onSenderDispatchMiss;

	WatchApplicator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WatchApplicator& operator = ( const WatchApplicator &_watchApplicator ) { Assign( _watchApplicator ); return *this; }
	WatchApplicator( const WatchApplicator &_watchApplicator ) { Assign( _watchApplicator ); }
	virtual void Assign( const WatchApplicator &_watchApplicator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WatchApplicator * pOther = dynamic_cast< const WatchApplicator * > ( _pResource );
		if ( pOther ) WatchApplicator::Assign( *pOther );
	}

	virtual NWorld::PFBaseApplicator* Create( NWorld::PFApplCreatePars const &cp ) const;
};

struct WeightTargetSelector : public SingleTargetSelector
{
	DBRESOURCE_METHODS( WeightTargetSelector );
public:
	enum { typeId = 0x2282AB00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WeightTargetSelector::typeId; }
	Ptr< MultipleTargetSelector > targetSelector;

	WeightTargetSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WeightTargetSelector& operator = ( const WeightTargetSelector &_weightTargetSelector ) { Assign( _weightTargetSelector ); return *this; }
	WeightTargetSelector( const WeightTargetSelector &_weightTargetSelector ) { Assign( _weightTargetSelector ); }
	virtual void Assign( const WeightTargetSelector &_weightTargetSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WeightTargetSelector * pOther = dynamic_cast< const WeightTargetSelector * > ( _pResource );
		if ( pOther ) WeightTargetSelector::Assign( *pOther );
	}

	virtual NWorld::PFTargetSelector* Create( NWorld::PFWorld* world ) const;
};

}; // namespace NDb
