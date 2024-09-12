// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "DBImpulsiveBuffs.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_DBRESOURCE( ImpulsiveEvent );
REGISTER_DBRESOURCE( EvtComplexEvent );
REGISTER_DBRESOURCE( EvtCondition );
REGISTER_DBRESOURCE( EvtDead );
REGISTER_DBRESOURCE( EvtEnemyDanger );
REGISTER_DBRESOURCE( EvtEnemyFlees );
REGISTER_DBRESOURCE( EvtEnteringBattleLine );
REGISTER_DBRESOURCE( EvtHeroTotalNaftaCondition );
REGISTER_DBRESOURCE( EvtInMinigame );
REGISTER_DBRESOURCE( EvtInverseEvent );
REGISTER_DBRESOURCE( EvtMinEnergy );
REGISTER_DBRESOURCE( EvtMinHealth );
REGISTER_DBRESOURCE( EvtNegativeEffects );
REGISTER_DBRESOURCE( EvtPriestessGainMaxLevel );
REGISTER_DBRESOURCE( EvtSpellLowMana );
REGISTER_DBRESOURCE( EvtTargetInRange );
REGISTER_DBRESOURCE( EvtUnitsInRange );
REGISTER_DBRESOURCE( EvtUnitsInRangeWithProperHealth );
REGISTER_DBRESOURCE( EvtUsedImpulsiveBuff );
REGISTER_DBRESOURCE( ImpulsiveBuffsContainer );
REGISTER_DBRESOURCE( EvtAttackedByUnits );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef SERVER_DB
#include "PFImpulsiveEvents.h"
#endif // #ifndef SERVER_DB

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ECompareOperator value )
{
	switch( value )
	{
		case COMPAREOPERATOR_EQUAL:
			return "Equal";
		case COMPAREOPERATOR_GREATER:
			return "Greater";
		case COMPAREOPERATOR_GREATEROREQUAL:
			return "GreaterOrEqual";
		case COMPAREOPERATOR_LESS:
			return "Less";
		case COMPAREOPERATOR_LESSOREQUAL:
			return "LessOrEqual";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ECompareOperator", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECompareOperator StringToEnum_ECompareOperator( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECompareOperator)(NStr::ToInt( value ));
	if ( strcmp( value, "Equal" ) == 0 || strcmp( value, "COMPAREOPERATOR_EQUAL" ) == 0 )
		return COMPAREOPERATOR_EQUAL;
	if ( strcmp( value, "Greater" ) == 0 || strcmp( value, "COMPAREOPERATOR_GREATER" ) == 0 )
		return COMPAREOPERATOR_GREATER;
	if ( strcmp( value, "GreaterOrEqual" ) == 0 || strcmp( value, "COMPAREOPERATOR_GREATEROREQUAL" ) == 0 )
		return COMPAREOPERATOR_GREATEROREQUAL;
	if ( strcmp( value, "Less" ) == 0 || strcmp( value, "COMPAREOPERATOR_LESS" ) == 0 )
		return COMPAREOPERATOR_LESS;
	if ( strcmp( value, "LessOrEqual" ) == 0 || strcmp( value, "COMPAREOPERATOR_LESSOREQUAL" ) == 0 )
		return COMPAREOPERATOR_LESSOREQUAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECompareOperator", value ) );
	return COMPAREOPERATOR_EQUAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEventsCombineMove value )
{
	switch( value )
	{
		case EVENTSCOMBINEMOVE_AND:
			return "AND";
		case EVENTSCOMBINEMOVE_OR:
			return "OR";
		case EVENTSCOMBINEMOVE_XOR:
			return "XOR";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEventsCombineMove", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEventsCombineMove StringToEnum_EEventsCombineMove( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEventsCombineMove)(NStr::ToInt( value ));
	if ( strcmp( value, "AND" ) == 0 || strcmp( value, "EVENTSCOMBINEMOVE_AND" ) == 0 )
		return EVENTSCOMBINEMOVE_AND;
	if ( strcmp( value, "OR" ) == 0 || strcmp( value, "EVENTSCOMBINEMOVE_OR" ) == 0 )
		return EVENTSCOMBINEMOVE_OR;
	if ( strcmp( value, "XOR" ) == 0 || strcmp( value, "EVENTSCOMBINEMOVE_XOR" ) == 0 )
		return EVENTSCOMBINEMOVE_XOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEventsCombineMove", value ) );
	return EVENTSCOMBINEMOVE_AND;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ELevelCheckType value )
{
	switch( value )
	{
		case LEVELCHECKTYPE_EXACT:
			return "Exact";
		case LEVELCHECKTYPE_AVGOFSELFTEAM:
			return "AvgOfSelfTeam";
		case LEVELCHECKTYPE_AVGOFOPPOSITETEAM:
			return "AvgOfOppositeTeam";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ELevelCheckType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ELevelCheckType StringToEnum_ELevelCheckType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ELevelCheckType)(NStr::ToInt( value ));
	if ( strcmp( value, "Exact" ) == 0 || strcmp( value, "LEVELCHECKTYPE_EXACT" ) == 0 )
		return LEVELCHECKTYPE_EXACT;
	if ( strcmp( value, "AvgOfSelfTeam" ) == 0 || strcmp( value, "LEVELCHECKTYPE_AVGOFSELFTEAM" ) == 0 )
		return LEVELCHECKTYPE_AVGOFSELFTEAM;
	if ( strcmp( value, "AvgOfOppositeTeam" ) == 0 || strcmp( value, "LEVELCHECKTYPE_AVGOFOPPOSITETEAM" ) == 0 )
		return LEVELCHECKTYPE_AVGOFOPPOSITETEAM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ELevelCheckType", value ) );
	return LEVELCHECKTYPE_EXACT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ERangeType value )
{
	switch( value )
	{
		case RANGETYPE_EXACTVALUE:
			return "ExactValue";
		case RANGETYPE_ATTACKRANGE:
			return "AttackRange";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ERangeType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ERangeType StringToEnum_ERangeType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ERangeType)(NStr::ToInt( value ));
	if ( strcmp( value, "ExactValue" ) == 0 || strcmp( value, "RANGETYPE_EXACTVALUE" ) == 0 )
		return RANGETYPE_EXACTVALUE;
	if ( strcmp( value, "AttackRange" ) == 0 || strcmp( value, "RANGETYPE_ATTACKRANGE" ) == 0 )
		return RANGETYPE_ATTACKRANGE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ERangeType", value ) );
	return RANGETYPE_EXACTVALUE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ImpulseBuffClass value )
{
	switch( value )
	{
		case IMPULSEBUFFCLASS_CLASS_BUFFTOWER:
			return "Class_BuffTower";
		case IMPULSEBUFFCLASS_CLASS_BUFFHERO:
			return "Class_BuffHero";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ImpulseBuffClass", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ImpulseBuffClass StringToEnum_ImpulseBuffClass( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ImpulseBuffClass)(NStr::ToInt( value ));
	if ( strcmp( value, "Class_BuffTower" ) == 0 || strcmp( value, "IMPULSEBUFFCLASS_CLASS_BUFFTOWER" ) == 0 )
		return IMPULSEBUFFCLASS_CLASS_BUFFTOWER;
	if ( strcmp( value, "Class_BuffHero" ) == 0 || strcmp( value, "IMPULSEBUFFCLASS_CLASS_BUFFHERO" ) == 0 )
		return IMPULSEBUFFCLASS_CLASS_BUFFHERO;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ImpulseBuffClass", value ) );
	return IMPULSEBUFFCLASS_CLASS_BUFFTOWER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ImpulsiveEventType value )
{
	switch( value )
	{
		case IMPULSIVEEVENTTYPE_HEROEVENT:
			return "HeroEvent";
		case IMPULSIVEEVENTTYPE_TOWEREVENT:
			return "TowerEvent";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ImpulsiveEventType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ImpulsiveEventType StringToEnum_ImpulsiveEventType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ImpulsiveEventType)(NStr::ToInt( value ));
	if ( strcmp( value, "HeroEvent" ) == 0 || strcmp( value, "IMPULSIVEEVENTTYPE_HEROEVENT" ) == 0 )
		return IMPULSIVEEVENTTYPE_HEROEVENT;
	if ( strcmp( value, "TowerEvent" ) == 0 || strcmp( value, "IMPULSIVEEVENTTYPE_TOWEREVENT" ) == 0 )
		return IMPULSIVEEVENTTYPE_TOWEREVENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ImpulsiveEventType", value ) );
	return IMPULSIVEEVENTTYPE_HEROEVENT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AccessCost::AccessCost() :
		impulsesPoints( 0 )
	, gamesLimit( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AccessCost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &impulsesPoints );
	saver.Add( 3, &gamesLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AccessCost::operator&( IXmlSaver &saver )
{
	saver.Add( "impulsesPoints", &impulsesPoints );
	saver.Add( "gamesLimit", &gamesLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AccessInfo::AccessInfo() :
		level( 0 )
	, points( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AccessInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &level );
	saver.Add( 3, &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AccessInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "level", &level );
	saver.Add( "points", &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImpulsiveBuff::ImpulsiveBuff() :
		canBeOfferedToDead( false )
	, offerTime( 0.0f )
	, cooldown( 10.0f )
	, cooldownGroup( "A" )
	, priority( 0.3f )
	, buffClass( IMPULSEBUFFCLASS_CLASS_BUFFHERO )
	, isSimple( true )
	, oncePerTeam( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuff::operator&( IBinSaver &saver )
{
	saver.Add( 2, &buff );
	saver.Add( 3, &events );
	saver.Add( 4, &accessInfo );
	saver.Add( 5, &caption );
	saver.Add( 6, &canBeOfferedToDead );
	saver.Add( 7, &offerTime );
	saver.Add( 8, &cooldown );
	saver.Add( 9, &cooldownGroup );
	saver.Add( 10, &priority );
	saver.Add( 11, &buffClass );
	saver.Add( 12, &isSimple );
	saver.Add( 13, &oncePerTeam );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuff::operator&( IXmlSaver &saver )
{
	saver.Add( "buff", &buff );
	saver.Add( "events", &events );
	saver.Add( "accessInfo", &accessInfo );
	saver.Add( "caption", &caption );
	saver.Add( "canBeOfferedToDead", &canBeOfferedToDead );
	saver.Add( "offerTime", &offerTime );
	saver.Add( "cooldown", &cooldown );
	saver.Add( "cooldownGroup", &cooldownGroup );
	saver.Add( "priority", &priority );
	saver.Add( "buffClass", &buffClass );
	saver.Add( "isSimple", &isSimple );
	saver.Add( "oncePerTeam", &oncePerTeam );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NegativeEffectCondition::NegativeEffectCondition() :
		minCount( 1 )
	, priority( DISPELLPRIORITY_NONDISPELLABLE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NegativeEffectCondition::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minCount );
	saver.Add( 3, &priority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NegativeEffectCondition::operator&( IXmlSaver &saver )
{
	saver.Add( "minCount", &minCount );
	saver.Add( "priority", &priority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitCountingWeights::UnitCountingWeights()
{
	weights.resize( 22, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCountingWeights::operator&( IBinSaver &saver )
{
	saver.Add( 2, &setName );
	saver.Add( 3, &weights );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitCountingWeights::operator&( IXmlSaver &saver )
{
	saver.Add( "setName", &setName );
	weights.resize( 22 );
	saver.Add( "weights", &weights );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImpulsiveEvent::ImpulsiveEvent() :
		suggestTarget( false )
	, eventType( IMPULSIVEEVENTTYPE_HEROEVENT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveEvent::operator&( IBinSaver &saver )
{
	saver.Add( 2, &suggestTarget );
	saver.Add( 3, &eventType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ImpulsiveEvent* parentPtr = (ImpulsiveEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveEvent::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "suggestTarget", &suggestTarget );
	saver.Add( "eventType", &eventType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveEvent::Assign( const ImpulsiveEvent& _impulsiveEvent )
{
	suggestTarget = _impulsiveEvent.suggestTarget;
	eventType = _impulsiveEvent.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* ImpulsiveEvent::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return ( NWorld::ImpulsiveEvent* )(0);
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtComplexEvent::EvtComplexEvent() :
		combineMode( EVENTSCOMBINEMOVE_AND )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtComplexEvent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &combineMode );
	saver.Add( 3, &events );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtComplexEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtComplexEvent* parentPtr = (EvtComplexEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtComplexEvent::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "combineMode", &combineMode );
	saver.Add( "events", &events );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtComplexEvent::Assign( const EvtComplexEvent& _evtComplexEvent )
{
	combineMode = _evtComplexEvent.combineMode;
	events = _evtComplexEvent.events;
	suggestTarget = _evtComplexEvent.suggestTarget;
	eventType = _evtComplexEvent.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtComplexEvent::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtComplexEvent( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtCondition::EvtCondition()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtCondition::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &condition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtCondition::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtCondition* parentPtr = (EvtCondition*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtCondition::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "condition", &condition );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtCondition::Assign( const EvtCondition& _evtCondition )
{
	condition = _evtCondition.condition;
	suggestTarget = _evtCondition.suggestTarget;
	eventType = _evtCondition.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtCondition::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtCondition( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtDead::EvtDead()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtDead::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtDead::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtDead* parentPtr = (EvtDead*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtDead::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtDead::Assign( const EvtDead& _evtDead )
{
	suggestTarget = _evtDead.suggestTarget;
	eventType = _evtDead.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtDead::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtDead( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtEnemyDanger::EvtEnemyDanger() :
		count( 1 )
	, distance( 150.0f )
	, unitTypes( ESpellTarget( SPELLTARGET_HEROFEMALE | SPELLTARGET_HEROMALE ) )
	, treatNeutralAsHostile( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnemyDanger::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &count );
	saver.Add( 3, &distance );
	saver.Add( 4, &unitTypes );
	saver.Add( 5, &treatNeutralAsHostile );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnemyDanger::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtEnemyDanger* parentPtr = (EvtEnemyDanger*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnemyDanger::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "count", &count );
	saver.Add( "distance", &distance );
	saver.Add( "unitTypes", &unitTypes );
	saver.Add( "treatNeutralAsHostile", &treatNeutralAsHostile );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnemyDanger::Assign( const EvtEnemyDanger& _evtEnemyDanger )
{
	count = _evtEnemyDanger.count;
	distance = _evtEnemyDanger.distance;
	unitTypes = _evtEnemyDanger.unitTypes;
	treatNeutralAsHostile = _evtEnemyDanger.treatNeutralAsHostile;
	suggestTarget = _evtEnemyDanger.suggestTarget;
	eventType = _evtEnemyDanger.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtEnemyDanger::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtEnemyDanger( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtEnemyFlees::EvtEnemyFlees() :
		health( 10.0f )
	, operation( COMPAREOPERATOR_LESS )
	, fleeTime( 10.0f )
	, cowardDetectRange( 20.0f )
	, cowardChaseRange( 20.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnemyFlees::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &health );
	saver.Add( 3, &operation );
	saver.Add( 4, &fleeTime );
	saver.Add( 5, &cowardDetectRange );
	saver.Add( 6, &cowardChaseRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnemyFlees::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtEnemyFlees* parentPtr = (EvtEnemyFlees*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnemyFlees::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "health", &health );
	saver.Add( "operation", &operation );
	saver.Add( "fleeTime", &fleeTime );
	saver.Add( "cowardDetectRange", &cowardDetectRange );
	saver.Add( "cowardChaseRange", &cowardChaseRange );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnemyFlees::Assign( const EvtEnemyFlees& _evtEnemyFlees )
{
	health = _evtEnemyFlees.health;
	operation = _evtEnemyFlees.operation;
	fleeTime = _evtEnemyFlees.fleeTime;
	cowardDetectRange = _evtEnemyFlees.cowardDetectRange;
	cowardChaseRange = _evtEnemyFlees.cowardChaseRange;
	suggestTarget = _evtEnemyFlees.suggestTarget;
	eventType = _evtEnemyFlees.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtEnemyFlees::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtEnemyFlees( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtEnteringBattleLine::EvtEnteringBattleLine() :
		battleRange( 100.0f )
	, fightingAllies( 1 )
	, roadRange( 15.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnteringBattleLine::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &battleRange );
	saver.Add( 3, &fightingAllies );
	saver.Add( 4, &roadRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtEnteringBattleLine::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtEnteringBattleLine* parentPtr = (EvtEnteringBattleLine*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnteringBattleLine::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "battleRange", &battleRange );
	saver.Add( "fightingAllies", &fightingAllies );
	saver.Add( "roadRange", &roadRange );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtEnteringBattleLine::Assign( const EvtEnteringBattleLine& _evtEnteringBattleLine )
{
	battleRange = _evtEnteringBattleLine.battleRange;
	fightingAllies = _evtEnteringBattleLine.fightingAllies;
	roadRange = _evtEnteringBattleLine.roadRange;
	suggestTarget = _evtEnteringBattleLine.suggestTarget;
	eventType = _evtEnteringBattleLine.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtEnteringBattleLine::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtEnteringBattleLine( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtHeroTotalNaftaCondition::EvtHeroTotalNaftaCondition() :
		type( LEVELCHECKTYPE_EXACT )
	, operation( COMPAREOPERATOR_EQUAL )
	, totalNafta( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtHeroTotalNaftaCondition::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &operation );
	saver.Add( 4, &totalNafta );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtHeroTotalNaftaCondition::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtHeroTotalNaftaCondition* parentPtr = (EvtHeroTotalNaftaCondition*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtHeroTotalNaftaCondition::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "operation", &operation );
	saver.Add( "totalNafta", &totalNafta );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtHeroTotalNaftaCondition::Assign( const EvtHeroTotalNaftaCondition& _evtHeroTotalNaftaCondition )
{
	type = _evtHeroTotalNaftaCondition.type;
	operation = _evtHeroTotalNaftaCondition.operation;
	totalNafta = _evtHeroTotalNaftaCondition.totalNafta;
	suggestTarget = _evtHeroTotalNaftaCondition.suggestTarget;
	eventType = _evtHeroTotalNaftaCondition.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtHeroTotalNaftaCondition::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtHeroTotalNaftaCondition( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtInMinigame::EvtInMinigame()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtInMinigame::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtInMinigame::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtInMinigame* parentPtr = (EvtInMinigame*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtInMinigame::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtInMinigame::Assign( const EvtInMinigame& _evtInMinigame )
{
	suggestTarget = _evtInMinigame.suggestTarget;
	eventType = _evtInMinigame.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtInMinigame::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtInMinigame( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtInverseEvent::EvtInverseEvent()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtInverseEvent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &evt );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtInverseEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtInverseEvent* parentPtr = (EvtInverseEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtInverseEvent::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "evt", &evt );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtInverseEvent::Assign( const EvtInverseEvent& _evtInverseEvent )
{
	evt = _evtInverseEvent.evt;
	suggestTarget = _evtInverseEvent.suggestTarget;
	eventType = _evtInverseEvent.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtInverseEvent::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtInverseEvent( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtMinEnergy::EvtMinEnergy() :
		minEnergy( 0.2f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtMinEnergy::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &minEnergy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtMinEnergy::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtMinEnergy* parentPtr = (EvtMinEnergy*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtMinEnergy::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "minEnergy", &minEnergy );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtMinEnergy::Assign( const EvtMinEnergy& _evtMinEnergy )
{
	minEnergy = _evtMinEnergy.minEnergy;
	suggestTarget = _evtMinEnergy.suggestTarget;
	eventType = _evtMinEnergy.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtMinEnergy::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtMinEnergy( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtMinHealth::EvtMinHealth() :
		minHealth( 0.2f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtMinHealth::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &minHealth );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtMinHealth::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtMinHealth* parentPtr = (EvtMinHealth*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtMinHealth::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "minHealth", &minHealth );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtMinHealth::Assign( const EvtMinHealth& _evtMinHealth )
{
	minHealth = _evtMinHealth.minHealth;
	suggestTarget = _evtMinHealth.suggestTarget;
	eventType = _evtMinHealth.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtMinHealth::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtMinHealth( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtNegativeEffects::EvtNegativeEffects() :
		minTotalEffects( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtNegativeEffects::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &minTotalEffects );
	saver.Add( 3, &priorityConditions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtNegativeEffects::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtNegativeEffects* parentPtr = (EvtNegativeEffects*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtNegativeEffects::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "minTotalEffects", &minTotalEffects );
	saver.Add( "priorityConditions", &priorityConditions );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtNegativeEffects::Assign( const EvtNegativeEffects& _evtNegativeEffects )
{
	minTotalEffects = _evtNegativeEffects.minTotalEffects;
	priorityConditions = _evtNegativeEffects.priorityConditions;
	suggestTarget = _evtNegativeEffects.suggestTarget;
	eventType = _evtNegativeEffects.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtNegativeEffects::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtNegativeEffects( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtPriestessGainMaxLevel::EvtPriestessGainMaxLevel()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtPriestessGainMaxLevel::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtPriestessGainMaxLevel::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtPriestessGainMaxLevel* parentPtr = (EvtPriestessGainMaxLevel*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtPriestessGainMaxLevel::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtPriestessGainMaxLevel::Assign( const EvtPriestessGainMaxLevel& _evtPriestessGainMaxLevel )
{
	suggestTarget = _evtPriestessGainMaxLevel.suggestTarget;
	eventType = _evtPriestessGainMaxLevel.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtPriestessGainMaxLevel::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtPriestessGainMaxLevel( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtSpellLowMana::EvtSpellLowMana()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtSpellLowMana::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtSpellLowMana::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtSpellLowMana* parentPtr = (EvtSpellLowMana*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtSpellLowMana::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtSpellLowMana::Assign( const EvtSpellLowMana& _evtSpellLowMana )
{
	suggestTarget = _evtSpellLowMana.suggestTarget;
	eventType = _evtSpellLowMana.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtSpellLowMana::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtSpellLowMana( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtTargetInRange::EvtTargetInRange() :
		range( 0.0f )
	, rangeType( RANGETYPE_EXACTVALUE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtTargetInRange::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &rangeType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtTargetInRange::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtTargetInRange* parentPtr = (EvtTargetInRange*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtTargetInRange::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "rangeType", &rangeType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtTargetInRange::Assign( const EvtTargetInRange& _evtTargetInRange )
{
	range = _evtTargetInRange.range;
	rangeType = _evtTargetInRange.rangeType;
	suggestTarget = _evtTargetInRange.suggestTarget;
	eventType = _evtTargetInRange.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtTargetInRange::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtTargetInRange( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtUnitsInRange::EvtUnitsInRange() :
		range( 0.0f )
	, rangeType( RANGETYPE_EXACTVALUE )
	, factions( EFactionFlags( 0 ) )
	, unitTypes( ESpellTarget( 0 ) )
	, minCount( 0 )
	, maxCount( 1000 )
	, acceptSelf( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUnitsInRange::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &rangeType );
	saver.Add( 4, &factions );
	saver.Add( 5, &unitTypes );
	saver.Add( 6, &minCount );
	saver.Add( 7, &maxCount );
	saver.Add( 8, &acceptSelf );
	saver.Add( 9, &countingSet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUnitsInRange::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtUnitsInRange* parentPtr = (EvtUnitsInRange*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUnitsInRange::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "rangeType", &rangeType );
	saver.Add( "factions", &factions );
	saver.Add( "unitTypes", &unitTypes );
	saver.Add( "minCount", &minCount );
	saver.Add( "maxCount", &maxCount );
	saver.Add( "acceptSelf", &acceptSelf );
	saver.Add( "countingSet", &countingSet );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUnitsInRange::Assign( const EvtUnitsInRange& _evtUnitsInRange )
{
	range = _evtUnitsInRange.range;
	rangeType = _evtUnitsInRange.rangeType;
	factions = _evtUnitsInRange.factions;
	unitTypes = _evtUnitsInRange.unitTypes;
	minCount = _evtUnitsInRange.minCount;
	maxCount = _evtUnitsInRange.maxCount;
	acceptSelf = _evtUnitsInRange.acceptSelf;
	countingSet = _evtUnitsInRange.countingSet;
	suggestTarget = _evtUnitsInRange.suggestTarget;
	eventType = _evtUnitsInRange.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtUnitsInRange::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtUnitsInRange( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtUnitsInRangeWithProperHealth::EvtUnitsInRangeWithProperHealth() :
		health( 0.0f )
	, operation( COMPAREOPERATOR_EQUAL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUnitsInRangeWithProperHealth::operator&( IBinSaver &saver )
{
	saver.Add( 1, (EvtUnitsInRange*)this );
	saver.Add( 2, &health );
	saver.Add( 3, &operation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUnitsInRangeWithProperHealth::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtUnitsInRangeWithProperHealth* parentPtr = (EvtUnitsInRangeWithProperHealth*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUnitsInRangeWithProperHealth::SerializeSelf( IXmlSaver &saver )
{
	EvtUnitsInRange::SerializeSelf( saver );
	saver.Add( "health", &health );
	saver.Add( "operation", &operation );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUnitsInRangeWithProperHealth::Assign( const EvtUnitsInRangeWithProperHealth& _evtUnitsInRangeWithProperHealth )
{
	health = _evtUnitsInRangeWithProperHealth.health;
	operation = _evtUnitsInRangeWithProperHealth.operation;
	range = _evtUnitsInRangeWithProperHealth.range;
	rangeType = _evtUnitsInRangeWithProperHealth.rangeType;
	factions = _evtUnitsInRangeWithProperHealth.factions;
	unitTypes = _evtUnitsInRangeWithProperHealth.unitTypes;
	minCount = _evtUnitsInRangeWithProperHealth.minCount;
	maxCount = _evtUnitsInRangeWithProperHealth.maxCount;
	acceptSelf = _evtUnitsInRangeWithProperHealth.acceptSelf;
	countingSet = _evtUnitsInRangeWithProperHealth.countingSet;
	suggestTarget = _evtUnitsInRangeWithProperHealth.suggestTarget;
	eventType = _evtUnitsInRangeWithProperHealth.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtUnitsInRangeWithProperHealth::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtUnitsInRangeWithProperHealth( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtUsedImpulsiveBuff::EvtUsedImpulsiveBuff() :
		buffIndex( -1 )
	, usedByAlly( false )
	, acceptSelf( false )
	, range( 0.0f )
	, rangeType( RANGETYPE_EXACTVALUE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUsedImpulsiveBuff::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &buffIndex );
	saver.Add( 3, &usedByAlly );
	saver.Add( 4, &acceptSelf );
	saver.Add( 5, &range );
	saver.Add( 6, &rangeType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtUsedImpulsiveBuff::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtUsedImpulsiveBuff* parentPtr = (EvtUsedImpulsiveBuff*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUsedImpulsiveBuff::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "buffIndex", &buffIndex );
	saver.Add( "usedByAlly", &usedByAlly );
	saver.Add( "acceptSelf", &acceptSelf );
	saver.Add( "range", &range );
	saver.Add( "rangeType", &rangeType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtUsedImpulsiveBuff::Assign( const EvtUsedImpulsiveBuff& _evtUsedImpulsiveBuff )
{
	buffIndex = _evtUsedImpulsiveBuff.buffIndex;
	usedByAlly = _evtUsedImpulsiveBuff.usedByAlly;
	acceptSelf = _evtUsedImpulsiveBuff.acceptSelf;
	range = _evtUsedImpulsiveBuff.range;
	rangeType = _evtUsedImpulsiveBuff.rangeType;
	suggestTarget = _evtUsedImpulsiveBuff.suggestTarget;
	eventType = _evtUsedImpulsiveBuff.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtUsedImpulsiveBuff::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtUsedImpulsiveBuff( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImpulsiveBuffsContainer::ImpulsiveBuffsContainer() :
		globalCooldown( 0.0f )
	, buffUseEventLifeTime( 15.0f )
	, priestessEventsLifeTime( 15.0f )
{
	buffs.resize( 11 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &servicesCosts );
	saver.Add( 3, &buffs );
	saver.Add( 4, &accessLevelsCosts );
	saver.Add( 5, &globalCooldown );
	saver.Add( 6, &buffUseEventLifeTime );
	saver.Add( 7, &priestessEventsLifeTime );
	saver.Add( 8, &unitCountingParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ImpulsiveBuffsContainer* parentPtr = (ImpulsiveBuffsContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveBuffsContainer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "servicesCosts", &servicesCosts );
	buffs.resize( 11 );
	saver.Add( "buffs", &buffs );
	saver.Add( "accessLevelsCosts", &accessLevelsCosts );
	saver.Add( "globalCooldown", &globalCooldown );
	saver.Add( "buffUseEventLifeTime", &buffUseEventLifeTime );
	saver.Add( "priestessEventsLifeTime", &priestessEventsLifeTime );
	saver.Add( "unitCountingParams", &unitCountingParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImpulsiveBuffsContainer::Assign( const ImpulsiveBuffsContainer& _impulsiveBuffsContainer )
{
	servicesCosts = _impulsiveBuffsContainer.servicesCosts;
	buffs = _impulsiveBuffsContainer.buffs;
	accessLevelsCosts = _impulsiveBuffsContainer.accessLevelsCosts;
	globalCooldown = _impulsiveBuffsContainer.globalCooldown;
	buffUseEventLifeTime = _impulsiveBuffsContainer.buffUseEventLifeTime;
	priestessEventsLifeTime = _impulsiveBuffsContainer.priestessEventsLifeTime;
	unitCountingParams = _impulsiveBuffsContainer.unitCountingParams;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EvtAttackedByUnits::EvtAttackedByUnits() :
		range( 0.0f )
	, rangeType( RANGETYPE_EXACTVALUE )
	, attackedFactions( EFactionFlags( 0 ) )
	, attackedTypes( ESpellTarget( 0 ) )
	, attackedAcceptSelf( true )
	, attackersFactions( EFactionFlags( 0 ) )
	, attackersTypes( ESpellTarget( 0 ) )
	, attackersAcceptSelf( true )
	, minAttackersCount( 0 )
	, maxAttackersCount( 1000 )
	, suggestVictim( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtAttackedByUnits::operator&( IBinSaver &saver )
{
	saver.Add( 1, (ImpulsiveEvent*)this );
	saver.Add( 2, &range );
	saver.Add( 3, &rangeType );
	saver.Add( 4, &attackedFactions );
	saver.Add( 5, &attackedTypes );
	saver.Add( 6, &attackedAcceptSelf );
	saver.Add( 7, &attackersFactions );
	saver.Add( 8, &attackersTypes );
	saver.Add( 9, &attackersAcceptSelf );
	saver.Add( 10, &minAttackersCount );
	saver.Add( 11, &maxAttackersCount );
	saver.Add( 12, &suggestVictim );
	saver.Add( 13, &countingSet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EvtAttackedByUnits::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			EvtAttackedByUnits* parentPtr = (EvtAttackedByUnits*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtAttackedByUnits::SerializeSelf( IXmlSaver &saver )
{
	ImpulsiveEvent::SerializeSelf( saver );
	saver.Add( "range", &range );
	saver.Add( "rangeType", &rangeType );
	saver.Add( "attackedFactions", &attackedFactions );
	saver.Add( "attackedTypes", &attackedTypes );
	saver.Add( "attackedAcceptSelf", &attackedAcceptSelf );
	saver.Add( "attackersFactions", &attackersFactions );
	saver.Add( "attackersTypes", &attackersTypes );
	saver.Add( "attackersAcceptSelf", &attackersAcceptSelf );
	saver.Add( "minAttackersCount", &minAttackersCount );
	saver.Add( "maxAttackersCount", &maxAttackersCount );
	saver.Add( "suggestVictim", &suggestVictim );
	saver.Add( "countingSet", &countingSet );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EvtAttackedByUnits::Assign( const EvtAttackedByUnits& _evtAttackedByUnits )
{
	range = _evtAttackedByUnits.range;
	rangeType = _evtAttackedByUnits.rangeType;
	attackedFactions = _evtAttackedByUnits.attackedFactions;
	attackedTypes = _evtAttackedByUnits.attackedTypes;
	attackedAcceptSelf = _evtAttackedByUnits.attackedAcceptSelf;
	attackersFactions = _evtAttackedByUnits.attackersFactions;
	attackersTypes = _evtAttackedByUnits.attackersTypes;
	attackersAcceptSelf = _evtAttackedByUnits.attackersAcceptSelf;
	minAttackersCount = _evtAttackedByUnits.minAttackersCount;
	maxAttackersCount = _evtAttackedByUnits.maxAttackersCount;
	suggestVictim = _evtAttackedByUnits.suggestVictim;
	countingSet = _evtAttackedByUnits.countingSet;
	suggestTarget = _evtAttackedByUnits.suggestTarget;
	eventType = _evtAttackedByUnits.eventType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SERVER_DB
NWorld::ImpulsiveEvent* EvtAttackedByUnits::Create( class NWorld::ImpulsiveBuffsManager* _buffsManager ) const
{
	return new NWorld::EvtAttackedByUnits( *this, _buffsManager );
}
#endif // #ifndef SERVER_DB
}; // namespace NDb
