#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBStats.h"

struct IXmlSaver;
// forward declarations for factories
namespace NWorld
{
	class ImpulsiveEvent;
	class ImpulsiveBuffsManager;
}; //namespace NWorld

namespace NDb
{
struct Ability;
struct BuyServicesContainer;
struct ImpulsiveEvent;

enum ECompareOperator
{
	COMPAREOPERATOR_EQUAL = 0,
	COMPAREOPERATOR_GREATER = 1,
	COMPAREOPERATOR_GREATEROREQUAL = 2,
	COMPAREOPERATOR_LESS = 3,
	COMPAREOPERATOR_LESSOREQUAL = 4,
};

const char *EnumToString( const ECompareOperator value );
const ECompareOperator StringToEnum_ECompareOperator( const char* value );

template <>
struct KnownEnum< ECompareOperator >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const ECompareOperator value ) { return EnumToString( value ); }
	static const ECompareOperator ToEnum( const char* value ) { return StringToEnum_ECompareOperator( value ); }
	static const ECompareOperator ToEnum( const string& value ) { return StringToEnum_ECompareOperator( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EEventsCombineMove
{
	EVENTSCOMBINEMOVE_AND = 0,
	EVENTSCOMBINEMOVE_OR = 1,
	EVENTSCOMBINEMOVE_XOR = 2,
};

const char *EnumToString( const EEventsCombineMove value );
const EEventsCombineMove StringToEnum_EEventsCombineMove( const char* value );

template <>
struct KnownEnum< EEventsCombineMove >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEventsCombineMove value ) { return EnumToString( value ); }
	static const EEventsCombineMove ToEnum( const char* value ) { return StringToEnum_EEventsCombineMove( value ); }
	static const EEventsCombineMove ToEnum( const string& value ) { return StringToEnum_EEventsCombineMove( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ELevelCheckType
{
	LEVELCHECKTYPE_EXACT = 0,
	LEVELCHECKTYPE_AVGOFSELFTEAM = 1,
	LEVELCHECKTYPE_AVGOFOPPOSITETEAM = 2,
};

const char *EnumToString( const ELevelCheckType value );
const ELevelCheckType StringToEnum_ELevelCheckType( const char* value );

template <>
struct KnownEnum< ELevelCheckType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ELevelCheckType value ) { return EnumToString( value ); }
	static const ELevelCheckType ToEnum( const char* value ) { return StringToEnum_ELevelCheckType( value ); }
	static const ELevelCheckType ToEnum( const string& value ) { return StringToEnum_ELevelCheckType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ERangeType
{
	RANGETYPE_EXACTVALUE = 0,
	RANGETYPE_ATTACKRANGE = 1,
};

const char *EnumToString( const ERangeType value );
const ERangeType StringToEnum_ERangeType( const char* value );

template <>
struct KnownEnum< ERangeType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ERangeType value ) { return EnumToString( value ); }
	static const ERangeType ToEnum( const char* value ) { return StringToEnum_ERangeType( value ); }
	static const ERangeType ToEnum( const string& value ) { return StringToEnum_ERangeType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ImpulseBuffClass
{
	IMPULSEBUFFCLASS_CLASS_BUFFTOWER = 0,
	IMPULSEBUFFCLASS_CLASS_BUFFHERO = 1,
};

const char *EnumToString( const ImpulseBuffClass value );
const ImpulseBuffClass StringToEnum_ImpulseBuffClass( const char* value );

template <>
struct KnownEnum< ImpulseBuffClass >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ImpulseBuffClass value ) { return EnumToString( value ); }
	static const ImpulseBuffClass ToEnum( const char* value ) { return StringToEnum_ImpulseBuffClass( value ); }
	static const ImpulseBuffClass ToEnum( const string& value ) { return StringToEnum_ImpulseBuffClass( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ImpulsiveEventType
{
	IMPULSIVEEVENTTYPE_HEROEVENT = 0,
	IMPULSIVEEVENTTYPE_TOWEREVENT = 1,
};

const char *EnumToString( const ImpulsiveEventType value );
const ImpulsiveEventType StringToEnum_ImpulsiveEventType( const char* value );

template <>
struct KnownEnum< ImpulsiveEventType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ImpulsiveEventType value ) { return EnumToString( value ); }
	static const ImpulsiveEventType ToEnum( const char* value ) { return StringToEnum_ImpulsiveEventType( value ); }
	static const ImpulsiveEventType ToEnum( const string& value ) { return StringToEnum_ImpulsiveEventType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct AccessCost
{
public:
	int impulsesPoints;
	int gamesLimit;

	AccessCost();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AccessInfo
{
public:
	int level;
	int points;

	AccessInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ImpulsiveBuff
{
public:
	Ptr< Ability > buff;
	vector< Ptr< ImpulsiveEvent > > events;
	AccessInfo accessInfo;
	string caption;
	bool canBeOfferedToDead;
	float offerTime;
	float cooldown;
	string cooldownGroup;
	float priority;
	ImpulseBuffClass buffClass;
	bool isSimple;
	bool oncePerTeam;

	ImpulsiveBuff();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct NegativeEffectCondition
{
public:
	int minCount;
	EDispellPriority priority;

	NegativeEffectCondition();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UnitCountingWeights
{
public:
	string setName;
	vector< int > weights;

	UnitCountingWeights();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ImpulsiveEvent : public DbResource
{
public:
	bool suggestTarget;
	ImpulsiveEventType eventType;

	ImpulsiveEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ImpulsiveEvent& operator = ( const ImpulsiveEvent &_impulsiveEvent ) { Assign( _impulsiveEvent ); return *this; }
	ImpulsiveEvent( const ImpulsiveEvent &_impulsiveEvent ) { Assign( _impulsiveEvent ); }
	virtual void Assign( const ImpulsiveEvent &_impulsiveEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ImpulsiveEvent * pOther = dynamic_cast< const ImpulsiveEvent * > ( _pResource );
		if ( pOther ) ImpulsiveEvent::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtComplexEvent : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtComplexEvent );
public:
	enum { typeId = 0x2C6C4B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtComplexEvent::typeId; }
	EEventsCombineMove combineMode;
	vector< Ptr< ImpulsiveEvent > > events;

	EvtComplexEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtComplexEvent& operator = ( const EvtComplexEvent &_evtComplexEvent ) { Assign( _evtComplexEvent ); return *this; }
	EvtComplexEvent( const EvtComplexEvent &_evtComplexEvent ) { Assign( _evtComplexEvent ); }
	virtual void Assign( const EvtComplexEvent &_evtComplexEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtComplexEvent * pOther = dynamic_cast< const EvtComplexEvent * > ( _pResource );
		if ( pOther ) EvtComplexEvent::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtCondition : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtCondition );
public:
	enum { typeId = 0x4977E4C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtCondition::typeId; }
	ExecutableBoolString condition;

	EvtCondition();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtCondition& operator = ( const EvtCondition &_evtCondition ) { Assign( _evtCondition ); return *this; }
	EvtCondition( const EvtCondition &_evtCondition ) { Assign( _evtCondition ); }
	virtual void Assign( const EvtCondition &_evtCondition );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtCondition * pOther = dynamic_cast< const EvtCondition * > ( _pResource );
		if ( pOther ) EvtCondition::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtDead : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtDead );
public:
	enum { typeId = 0x2C6C8440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtDead::typeId; }

	EvtDead();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtDead& operator = ( const EvtDead &_evtDead ) { Assign( _evtDead ); return *this; }
	EvtDead( const EvtDead &_evtDead ) { Assign( _evtDead ); }
	virtual void Assign( const EvtDead &_evtDead );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtDead * pOther = dynamic_cast< const EvtDead * > ( _pResource );
		if ( pOther ) EvtDead::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtEnemyDanger : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtEnemyDanger );
public:
	enum { typeId = 0x0F664C02 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtEnemyDanger::typeId; }
	int count;
	float distance;
	ESpellTarget unitTypes;
	bool treatNeutralAsHostile;

	EvtEnemyDanger();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtEnemyDanger& operator = ( const EvtEnemyDanger &_evtEnemyDanger ) { Assign( _evtEnemyDanger ); return *this; }
	EvtEnemyDanger( const EvtEnemyDanger &_evtEnemyDanger ) { Assign( _evtEnemyDanger ); }
	virtual void Assign( const EvtEnemyDanger &_evtEnemyDanger );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtEnemyDanger * pOther = dynamic_cast< const EvtEnemyDanger * > ( _pResource );
		if ( pOther ) EvtEnemyDanger::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtEnemyFlees : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtEnemyFlees );
public:
	enum { typeId = 0x2C72D3C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtEnemyFlees::typeId; }
	float health;
	ECompareOperator operation;
	float fleeTime;
	float cowardDetectRange;
	float cowardChaseRange;

	EvtEnemyFlees();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtEnemyFlees& operator = ( const EvtEnemyFlees &_evtEnemyFlees ) { Assign( _evtEnemyFlees ); return *this; }
	EvtEnemyFlees( const EvtEnemyFlees &_evtEnemyFlees ) { Assign( _evtEnemyFlees ); }
	virtual void Assign( const EvtEnemyFlees &_evtEnemyFlees );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtEnemyFlees * pOther = dynamic_cast< const EvtEnemyFlees * > ( _pResource );
		if ( pOther ) EvtEnemyFlees::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtEnteringBattleLine : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtEnteringBattleLine );
public:
	enum { typeId = 0x2C72D3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtEnteringBattleLine::typeId; }
	float battleRange;
	int fightingAllies;
	float roadRange;

	EvtEnteringBattleLine();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtEnteringBattleLine& operator = ( const EvtEnteringBattleLine &_evtEnteringBattleLine ) { Assign( _evtEnteringBattleLine ); return *this; }
	EvtEnteringBattleLine( const EvtEnteringBattleLine &_evtEnteringBattleLine ) { Assign( _evtEnteringBattleLine ); }
	virtual void Assign( const EvtEnteringBattleLine &_evtEnteringBattleLine );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtEnteringBattleLine * pOther = dynamic_cast< const EvtEnteringBattleLine * > ( _pResource );
		if ( pOther ) EvtEnteringBattleLine::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtHeroTotalNaftaCondition : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtHeroTotalNaftaCondition );
public:
	enum { typeId = 0x2C6C4C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtHeroTotalNaftaCondition::typeId; }
	ELevelCheckType type;
	ECompareOperator operation;
	int totalNafta;

	EvtHeroTotalNaftaCondition();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtHeroTotalNaftaCondition& operator = ( const EvtHeroTotalNaftaCondition &_evtHeroTotalNaftaCondition ) { Assign( _evtHeroTotalNaftaCondition ); return *this; }
	EvtHeroTotalNaftaCondition( const EvtHeroTotalNaftaCondition &_evtHeroTotalNaftaCondition ) { Assign( _evtHeroTotalNaftaCondition ); }
	virtual void Assign( const EvtHeroTotalNaftaCondition &_evtHeroTotalNaftaCondition );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtHeroTotalNaftaCondition * pOther = dynamic_cast< const EvtHeroTotalNaftaCondition * > ( _pResource );
		if ( pOther ) EvtHeroTotalNaftaCondition::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtInMinigame : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtInMinigame );
public:
	enum { typeId = 0x2B78EBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtInMinigame::typeId; }

	EvtInMinigame();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtInMinigame& operator = ( const EvtInMinigame &_evtInMinigame ) { Assign( _evtInMinigame ); return *this; }
	EvtInMinigame( const EvtInMinigame &_evtInMinigame ) { Assign( _evtInMinigame ); }
	virtual void Assign( const EvtInMinigame &_evtInMinigame );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtInMinigame * pOther = dynamic_cast< const EvtInMinigame * > ( _pResource );
		if ( pOther ) EvtInMinigame::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtInverseEvent : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtInverseEvent );
public:
	enum { typeId = 0x2C6C4C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtInverseEvent::typeId; }
	Ptr< ImpulsiveEvent > evt;

	EvtInverseEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtInverseEvent& operator = ( const EvtInverseEvent &_evtInverseEvent ) { Assign( _evtInverseEvent ); return *this; }
	EvtInverseEvent( const EvtInverseEvent &_evtInverseEvent ) { Assign( _evtInverseEvent ); }
	virtual void Assign( const EvtInverseEvent &_evtInverseEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtInverseEvent * pOther = dynamic_cast< const EvtInverseEvent * > ( _pResource );
		if ( pOther ) EvtInverseEvent::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtMinEnergy : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtMinEnergy );
public:
	enum { typeId = 0x0F664C01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtMinEnergy::typeId; }
	float minEnergy;

	EvtMinEnergy();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtMinEnergy& operator = ( const EvtMinEnergy &_evtMinEnergy ) { Assign( _evtMinEnergy ); return *this; }
	EvtMinEnergy( const EvtMinEnergy &_evtMinEnergy ) { Assign( _evtMinEnergy ); }
	virtual void Assign( const EvtMinEnergy &_evtMinEnergy );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtMinEnergy * pOther = dynamic_cast< const EvtMinEnergy * > ( _pResource );
		if ( pOther ) EvtMinEnergy::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtMinHealth : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtMinHealth );
public:
	enum { typeId = 0x0F664C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtMinHealth::typeId; }
	float minHealth;

	EvtMinHealth();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtMinHealth& operator = ( const EvtMinHealth &_evtMinHealth ) { Assign( _evtMinHealth ); return *this; }
	EvtMinHealth( const EvtMinHealth &_evtMinHealth ) { Assign( _evtMinHealth ); }
	virtual void Assign( const EvtMinHealth &_evtMinHealth );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtMinHealth * pOther = dynamic_cast< const EvtMinHealth * > ( _pResource );
		if ( pOther ) EvtMinHealth::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtNegativeEffects : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtNegativeEffects );
public:
	enum { typeId = 0x2C6C1C80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtNegativeEffects::typeId; }
	int minTotalEffects;
	vector< NegativeEffectCondition > priorityConditions;

	EvtNegativeEffects();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtNegativeEffects& operator = ( const EvtNegativeEffects &_evtNegativeEffects ) { Assign( _evtNegativeEffects ); return *this; }
	EvtNegativeEffects( const EvtNegativeEffects &_evtNegativeEffects ) { Assign( _evtNegativeEffects ); }
	virtual void Assign( const EvtNegativeEffects &_evtNegativeEffects );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtNegativeEffects * pOther = dynamic_cast< const EvtNegativeEffects * > ( _pResource );
		if ( pOther ) EvtNegativeEffects::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtPriestessGainMaxLevel : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtPriestessGainMaxLevel );
public:
	enum { typeId = 0x2C6C83C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtPriestessGainMaxLevel::typeId; }

	EvtPriestessGainMaxLevel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtPriestessGainMaxLevel& operator = ( const EvtPriestessGainMaxLevel &_evtPriestessGainMaxLevel ) { Assign( _evtPriestessGainMaxLevel ); return *this; }
	EvtPriestessGainMaxLevel( const EvtPriestessGainMaxLevel &_evtPriestessGainMaxLevel ) { Assign( _evtPriestessGainMaxLevel ); }
	virtual void Assign( const EvtPriestessGainMaxLevel &_evtPriestessGainMaxLevel );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtPriestessGainMaxLevel * pOther = dynamic_cast< const EvtPriestessGainMaxLevel * > ( _pResource );
		if ( pOther ) EvtPriestessGainMaxLevel::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtSpellLowMana : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtSpellLowMana );
public:
	enum { typeId = 0x0F665B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtSpellLowMana::typeId; }

	EvtSpellLowMana();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtSpellLowMana& operator = ( const EvtSpellLowMana &_evtSpellLowMana ) { Assign( _evtSpellLowMana ); return *this; }
	EvtSpellLowMana( const EvtSpellLowMana &_evtSpellLowMana ) { Assign( _evtSpellLowMana ); }
	virtual void Assign( const EvtSpellLowMana &_evtSpellLowMana );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtSpellLowMana * pOther = dynamic_cast< const EvtSpellLowMana * > ( _pResource );
		if ( pOther ) EvtSpellLowMana::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtTargetInRange : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtTargetInRange );
public:
	enum { typeId = 0x2C6CAAC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtTargetInRange::typeId; }
	float range;
	ERangeType rangeType;

	EvtTargetInRange();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtTargetInRange& operator = ( const EvtTargetInRange &_evtTargetInRange ) { Assign( _evtTargetInRange ); return *this; }
	EvtTargetInRange( const EvtTargetInRange &_evtTargetInRange ) { Assign( _evtTargetInRange ); }
	virtual void Assign( const EvtTargetInRange &_evtTargetInRange );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtTargetInRange * pOther = dynamic_cast< const EvtTargetInRange * > ( _pResource );
		if ( pOther ) EvtTargetInRange::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtUnitsInRange : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtUnitsInRange );
public:
	enum { typeId = 0x2C6C4BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtUnitsInRange::typeId; }
	float range;
	ERangeType rangeType;
	EFactionFlags factions;
	ESpellTarget unitTypes;
	int minCount;
	int maxCount;
	bool acceptSelf;
	string countingSet;

	EvtUnitsInRange();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtUnitsInRange& operator = ( const EvtUnitsInRange &_evtUnitsInRange ) { Assign( _evtUnitsInRange ); return *this; }
	EvtUnitsInRange( const EvtUnitsInRange &_evtUnitsInRange ) { Assign( _evtUnitsInRange ); }
	virtual void Assign( const EvtUnitsInRange &_evtUnitsInRange );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtUnitsInRange * pOther = dynamic_cast< const EvtUnitsInRange * > ( _pResource );
		if ( pOther ) EvtUnitsInRange::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtUnitsInRangeWithProperHealth : public EvtUnitsInRange
{
	DBRESOURCE_METHODS( EvtUnitsInRangeWithProperHealth );
public:
	enum { typeId = 0x2C6C5C80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtUnitsInRangeWithProperHealth::typeId; }
	float health;
	ECompareOperator operation;

	EvtUnitsInRangeWithProperHealth();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtUnitsInRangeWithProperHealth& operator = ( const EvtUnitsInRangeWithProperHealth &_evtUnitsInRangeWithProperHealth ) { Assign( _evtUnitsInRangeWithProperHealth ); return *this; }
	EvtUnitsInRangeWithProperHealth( const EvtUnitsInRangeWithProperHealth &_evtUnitsInRangeWithProperHealth ) { Assign( _evtUnitsInRangeWithProperHealth ); }
	virtual void Assign( const EvtUnitsInRangeWithProperHealth &_evtUnitsInRangeWithProperHealth );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtUnitsInRangeWithProperHealth * pOther = dynamic_cast< const EvtUnitsInRangeWithProperHealth * > ( _pResource );
		if ( pOther ) EvtUnitsInRangeWithProperHealth::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct EvtUsedImpulsiveBuff : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtUsedImpulsiveBuff );
public:
	enum { typeId = 0x2C6C5C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtUsedImpulsiveBuff::typeId; }
	int buffIndex;
	bool usedByAlly;
	bool acceptSelf;
	float range;
	ERangeType rangeType;

	EvtUsedImpulsiveBuff();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtUsedImpulsiveBuff& operator = ( const EvtUsedImpulsiveBuff &_evtUsedImpulsiveBuff ) { Assign( _evtUsedImpulsiveBuff ); return *this; }
	EvtUsedImpulsiveBuff( const EvtUsedImpulsiveBuff &_evtUsedImpulsiveBuff ) { Assign( _evtUsedImpulsiveBuff ); }
	virtual void Assign( const EvtUsedImpulsiveBuff &_evtUsedImpulsiveBuff );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtUsedImpulsiveBuff * pOther = dynamic_cast< const EvtUsedImpulsiveBuff * > ( _pResource );
		if ( pOther ) EvtUsedImpulsiveBuff::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

struct ImpulsiveBuffsContainer : public DbResource
{
	DBRESOURCE_METHODS( ImpulsiveBuffsContainer );
public:
	enum { typeId = 0x0F664BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ImpulsiveBuffsContainer::typeId; }
	Ptr< BuyServicesContainer > servicesCosts;
	vector< ImpulsiveBuff > buffs;
	vector< AccessCost > accessLevelsCosts;
	float globalCooldown;
	float buffUseEventLifeTime;
	float priestessEventsLifeTime;
	vector< UnitCountingWeights > unitCountingParams;

	ImpulsiveBuffsContainer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ImpulsiveBuffsContainer& operator = ( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer ) { Assign( _impulsiveBuffsContainer ); return *this; }
	ImpulsiveBuffsContainer( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer ) { Assign( _impulsiveBuffsContainer ); }
	virtual void Assign( const ImpulsiveBuffsContainer &_impulsiveBuffsContainer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ImpulsiveBuffsContainer * pOther = dynamic_cast< const ImpulsiveBuffsContainer * > ( _pResource );
		if ( pOther ) ImpulsiveBuffsContainer::Assign( *pOther );
	}
};

struct EvtAttackedByUnits : public ImpulsiveEvent
{
	DBRESOURCE_METHODS( EvtAttackedByUnits );
public:
	enum { typeId = 0x2C6C5381 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EvtAttackedByUnits::typeId; }
	float range;
	ERangeType rangeType;
	EFactionFlags attackedFactions;
	ESpellTarget attackedTypes;
	bool attackedAcceptSelf;
	EFactionFlags attackersFactions;
	ESpellTarget attackersTypes;
	bool attackersAcceptSelf;
	int minAttackersCount;
	int maxAttackersCount;
	bool suggestVictim;
	string countingSet;

	EvtAttackedByUnits();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EvtAttackedByUnits& operator = ( const EvtAttackedByUnits &_evtAttackedByUnits ) { Assign( _evtAttackedByUnits ); return *this; }
	EvtAttackedByUnits( const EvtAttackedByUnits &_evtAttackedByUnits ) { Assign( _evtAttackedByUnits ); }
	virtual void Assign( const EvtAttackedByUnits &_evtAttackedByUnits );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EvtAttackedByUnits * pOther = dynamic_cast< const EvtAttackedByUnits * > ( _pResource );
		if ( pOther ) EvtAttackedByUnits::Assign( *pOther );
	}

#ifndef SERVER_DB
	virtual NWorld::ImpulsiveEvent* Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const;
#endif // #ifndef SERVER_DB
};

}; // namespace NDb
