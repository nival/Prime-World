// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBStats.h"
#include "../Render/DBRenderResources.h"
#include "DBTalent.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Talent );
REGISTER_DBRESOURCE( TalentKit );
REGISTER_DBRESOURCE( TalentPack );
REGISTER_DBRESOURCE( TalentsSet );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentLevel value )
{
	switch( value )
	{
		case TALENTLEVEL_ID0:
			return "id0";
		case TALENTLEVEL_ID1:
			return "id1";
		case TALENTLEVEL_ID2:
			return "id2";
		case TALENTLEVEL_ID3:
			return "id3";
		case TALENTLEVEL_ID4:
			return "id4";
		case TALENTLEVEL_ID5:
			return "id5";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalentLevel", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentLevel StringToEnum_ETalentLevel( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentLevel)(NStr::ToInt( value ));
	if ( strcmp( value, "id0" ) == 0 || strcmp( value, "TALENTLEVEL_ID0" ) == 0 )
		return TALENTLEVEL_ID0;
	if ( strcmp( value, "id1" ) == 0 || strcmp( value, "TALENTLEVEL_ID1" ) == 0 )
		return TALENTLEVEL_ID1;
	if ( strcmp( value, "id2" ) == 0 || strcmp( value, "TALENTLEVEL_ID2" ) == 0 )
		return TALENTLEVEL_ID2;
	if ( strcmp( value, "id3" ) == 0 || strcmp( value, "TALENTLEVEL_ID3" ) == 0 )
		return TALENTLEVEL_ID3;
	if ( strcmp( value, "id4" ) == 0 || strcmp( value, "TALENTLEVEL_ID4" ) == 0 )
		return TALENTLEVEL_ID4;
	if ( strcmp( value, "id5" ) == 0 || strcmp( value, "TALENTLEVEL_ID5" ) == 0 )
		return TALENTLEVEL_ID5;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentLevel", value ) );
	return TALENTLEVEL_ID0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentRarity value )
{
	switch( value )
	{
		case TALENTRARITY_CLASS:
			return "Class";
		case TALENTRARITY_ORDINARY:
			return "ordinary";
		case TALENTRARITY_GOOD:
			return "good";
		case TALENTRARITY_EXCELLENT:
			return "excellent";
		case TALENTRARITY_MAGNIFICENT:
			return "magnificent";
		case TALENTRARITY_EXCLUSIVE:
			return "exclusive";
		case TALENTRARITY_OUTSTANDING:
			return "outstanding";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalentRarity", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentRarity StringToEnum_ETalentRarity( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentRarity)(NStr::ToInt( value ));
	if ( strcmp( value, "Class" ) == 0 || strcmp( value, "TALENTRARITY_CLASS" ) == 0 )
		return TALENTRARITY_CLASS;
	if ( strcmp( value, "ordinary" ) == 0 || strcmp( value, "TALENTRARITY_ORDINARY" ) == 0 )
		return TALENTRARITY_ORDINARY;
	if ( strcmp( value, "good" ) == 0 || strcmp( value, "TALENTRARITY_GOOD" ) == 0 )
		return TALENTRARITY_GOOD;
	if ( strcmp( value, "excellent" ) == 0 || strcmp( value, "TALENTRARITY_EXCELLENT" ) == 0 )
		return TALENTRARITY_EXCELLENT;
	if ( strcmp( value, "magnificent" ) == 0 || strcmp( value, "TALENTRARITY_MAGNIFICENT" ) == 0 )
		return TALENTRARITY_MAGNIFICENT;
	if ( strcmp( value, "exclusive" ) == 0 || strcmp( value, "TALENTRARITY_EXCLUSIVE" ) == 0 )
		return TALENTRARITY_EXCLUSIVE;
	if ( strcmp( value, "outstanding" ) == 0 || strcmp( value, "TALENTRARITY_OUTSTANDING" ) == 0 )
		return TALENTRARITY_OUTSTANDING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentRarity", value ) );
	return TALENTRARITY_CLASS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentRollGroup value )
{
	switch( value )
	{
		case TALENTROLLGROUP_PVP:
			return "PvP";
		case TALENTROLLGROUP_TRAINING:
			return "Training";
		case TALENTROLLGROUP_CTE:
			return "CTE";
		case TALENTROLLGROUP_PVE:
			return "PvE";
		case TALENTROLLGROUP_CASTLE:
			return "Castle";
		case TALENTROLLGROUP_MIDONLY:
			return "MidOnly";
		case TALENTROLLGROUP_ALL:
			return "All";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentRollGroup StringToEnum_ETalentRollGroup( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentRollGroup)(NStr::ToInt( value ));
	if ( strcmp( value, "PvP" ) == 0 || strcmp( value, "TALENTROLLGROUP_PVP" ) == 0 )
		return TALENTROLLGROUP_PVP;
	if ( strcmp( value, "Training" ) == 0 || strcmp( value, "TALENTROLLGROUP_TRAINING" ) == 0 )
		return TALENTROLLGROUP_TRAINING;
	if ( strcmp( value, "CTE" ) == 0 || strcmp( value, "TALENTROLLGROUP_CTE" ) == 0 )
		return TALENTROLLGROUP_CTE;
	if ( strcmp( value, "PvE" ) == 0 || strcmp( value, "TALENTROLLGROUP_PVE" ) == 0 )
		return TALENTROLLGROUP_PVE;
	if ( strcmp( value, "Castle" ) == 0 || strcmp( value, "TALENTROLLGROUP_CASTLE" ) == 0 )
		return TALENTROLLGROUP_CASTLE;
	if ( strcmp( value, "MidOnly" ) == 0 || strcmp( value, "TALENTROLLGROUP_MIDONLY" ) == 0 )
		return TALENTROLLGROUP_MIDONLY;
	if ( strcmp( value, "All" ) == 0 || strcmp( value, "TALENTROLLGROUP_ALL" ) == 0 )
		return TALENTROLLGROUP_ALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentRollGroup", value ) );
	return TALENTROLLGROUP_PVP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalents value )
{
	switch( value )
	{
		case TALENTS_POINTS_PER_LEVEL:
			return "points_per_level";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalents", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalents StringToEnum_ETalents( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalents)(NStr::ToInt( value ));
	if ( strcmp( value, "points_per_level" ) == 0 || strcmp( value, "TALENTS_POINTS_PER_LEVEL" ) == 0 )
		return TALENTS_POINTS_PER_LEVEL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalents", value ) );
	return TALENTS_POINTS_PER_LEVEL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentSlot value )
{
	switch( value )
	{
		case TALENTSLOT_ID0:
			return "id0";
		case TALENTSLOT_ID1:
			return "id1";
		case TALENTSLOT_ID2:
			return "id2";
		case TALENTSLOT_ID3:
			return "id3";
		case TALENTSLOT_ID4:
			return "id4";
		case TALENTSLOT_ID5:
			return "id5";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalentSlot", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentSlot StringToEnum_ETalentSlot( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentSlot)(NStr::ToInt( value ));
	if ( strcmp( value, "id0" ) == 0 || strcmp( value, "TALENTSLOT_ID0" ) == 0 )
		return TALENTSLOT_ID0;
	if ( strcmp( value, "id1" ) == 0 || strcmp( value, "TALENTSLOT_ID1" ) == 0 )
		return TALENTSLOT_ID1;
	if ( strcmp( value, "id2" ) == 0 || strcmp( value, "TALENTSLOT_ID2" ) == 0 )
		return TALENTSLOT_ID2;
	if ( strcmp( value, "id3" ) == 0 || strcmp( value, "TALENTSLOT_ID3" ) == 0 )
		return TALENTSLOT_ID3;
	if ( strcmp( value, "id4" ) == 0 || strcmp( value, "TALENTSLOT_ID4" ) == 0 )
		return TALENTSLOT_ID4;
	if ( strcmp( value, "id5" ) == 0 || strcmp( value, "TALENTSLOT_ID5" ) == 0 )
		return TALENTSLOT_ID5;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentSlot", value ) );
	return TALENTSLOT_ID0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETalentSlotStatus value )
{
	switch( value )
	{
		case TALENTSLOTSTATUS_NORMAL:
			return "normal";
		case TALENTSLOTSTATUS_LOCKED:
			return "locked";
		case TALENTSLOTSTATUS_UNAVAILABLE:
			return "unavailable";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETalentSlotStatus", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETalentSlotStatus StringToEnum_ETalentSlotStatus( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETalentSlotStatus)(NStr::ToInt( value ));
	if ( strcmp( value, "normal" ) == 0 || strcmp( value, "TALENTSLOTSTATUS_NORMAL" ) == 0 )
		return TALENTSLOTSTATUS_NORMAL;
	if ( strcmp( value, "locked" ) == 0 || strcmp( value, "TALENTSLOTSTATUS_LOCKED" ) == 0 )
		return TALENTSLOTSTATUS_LOCKED;
	if ( strcmp( value, "unavailable" ) == 0 || strcmp( value, "TALENTSLOTSTATUS_UNAVAILABLE" ) == 0 )
		return TALENTSLOTSTATUS_UNAVAILABLE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETalentSlotStatus", value ) );
	return TALENTSLOTSTATUS_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievmentCondition::AchievmentCondition() :
		minRank( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievmentCondition::operator&( IBinSaver &saver )
{
	saver.Add( 2, &achiev );
	saver.Add( 3, &minRank );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievmentCondition::operator&( IXmlSaver &saver )
{
	saver.Add( "achiev", &achiev );
	saver.Add( "minRank", &minRank );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsumptionBonus::ConsumptionBonus() :
		constant( 0 )
	, percent( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumptionBonus::operator&( IBinSaver &saver )
{
	saver.Add( 2, &constant );
	saver.Add( 3, &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumptionBonus::operator&( IXmlSaver &saver )
{
	saver.Add( "constant", &constant );
	saver.Add( "percent", &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentSlot::TalentSlot() :
		status( TALENTSLOTSTATUS_NORMAL )
	, refineRate( 1 )
	, aIPriority( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentSlot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &status );
	saver.Add( 3, &talent );
	saver.Add( 4, &refineRate );
	saver.Add( 5, &aIPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentSlot::operator&( IXmlSaver &saver )
{
	saver.Add( "status", &status );
	saver.Add( "talent", &talent );
	saver.Add( "refineRate", &refineRate );
	saver.Add( "aIPriority", &aIPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentsLevel::TalentsLevel()
{
	talents.resize( 6 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentsLevel::operator&( IBinSaver &saver )
{
	saver.Add( 2, &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentsLevel::operator&( IXmlSaver &saver )
{
	talents.resize( 6 );
	saver.Add( "talents", &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Talent::Talent() :
		minLevel( 0 )
	, devPoints( 1 )
	, budget( 0.0f )
	, naftaCost( 0 )
	, rarity( TALENTRARITY_ORDINARY )
	, vendorCost( 0 )
	, talentRollGroups( TALENTROLLGROUP_ALL )
	, askId( 0 )
	, isGenderTalent( false )
	, isTakenOnStart( false )
	, isUltimateTalent( false )
	, upgradeLevel( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Talent::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Ability*)this );
	saver.Add( 2, &minLevel );
	saver.Add( 3, &devPoints );
	saver.Add( 4, &budget );
	saver.Add( 5, &activationConditions );
	saver.Add( 6, &naftaCost );
	saver.Add( 7, &prerequisiteTalents );
	saver.Add( 8, &rarity );
	saver.Add( 9, &persistentId );
	saver.Add( 10, &vendorCost );
	saver.Add( 11, &talentRollGroups );
	saver.Add( 12, &askId );
	saver.Add( 13, &isGenderTalent );
	saver.Add( 14, &isTakenOnStart );
	saver.Add( 15, &isUltimateTalent );
	saver.Add( 16, &upgradeLevel );
	saver.Add( 17, &consumptionBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Talent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Talent* parentPtr = (Talent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Talent::SerializeSelf( IXmlSaver &saver )
{
	Ability::SerializeSelf( saver );
	saver.Add( "minLevel", &minLevel );
	saver.Add( "devPoints", &devPoints );
	saver.Add( "budget", &budget );
	saver.Add( "activationConditions", &activationConditions );
	saver.Add( "naftaCost", &naftaCost );
	saver.Add( "prerequisiteTalents", &prerequisiteTalents );
	saver.Add( "rarity", &rarity );
	saver.Add( "persistentId", &persistentId );
	saver.Add( "vendorCost", &vendorCost );
	saver.Add( "talentRollGroups", &talentRollGroups );
	saver.Add( "askId", &askId );
	saver.Add( "isGenderTalent", &isGenderTalent );
	saver.Add( "isTakenOnStart", &isTakenOnStart );
	saver.Add( "isUltimateTalent", &isUltimateTalent );
	saver.Add( "upgradeLevel", &upgradeLevel );
	saver.Add( "consumptionBonus", &consumptionBonus );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Talent::Assign( const Talent& _talent )
{
	minLevel = _talent.minLevel;
	devPoints = _talent.devPoints;
	budget = _talent.budget;
	activationConditions = _talent.activationConditions;
	naftaCost = _talent.naftaCost;
	prerequisiteTalents = _talent.prerequisiteTalents;
	rarity = _talent.rarity;
	persistentId = _talent.persistentId;
	vendorCost = _talent.vendorCost;
	talentRollGroups = _talent.talentRollGroups;
	askId = _talent.askId;
	isGenderTalent = _talent.isGenderTalent;
	isTakenOnStart = _talent.isTakenOnStart;
	isUltimateTalent = _talent.isUltimateTalent;
	upgradeLevel = _talent.upgradeLevel;
	consumptionBonus.constant = _talent.consumptionBonus.constant;
	consumptionBonus.percent = _talent.consumptionBonus.percent;
	name = _talent.name;
	description = _talent.description;
	compiledDescriptionA = _talent.compiledDescriptionA;
	compiledDescriptionB = _talent.compiledDescriptionB;
	shortDescription = _talent.shortDescription;
	commonDescription = _talent.commonDescription;
	castLimitations = _talent.castLimitations;
	image = _talent.image;
	imageSecondState = _talent.imageSecondState;
	aoeType = _talent.aoeType;
	aoeSize = _talent.aoeSize;
	aoeMaterial = _talent.aoeMaterial;
	aoeHeight = _talent.aoeHeight;
	useRangeMaterial = _talent.useRangeMaterial;
	aoePassabilityCheckMode = _talent.aoePassabilityCheckMode;
	aoeDisplayOnMinimap = _talent.aoeDisplayOnMinimap;
	type = _talent.type;
	cooldownTime = _talent.cooldownTime;
	cooldownTimeSecondState = _talent.cooldownTimeSecondState;
	manaCost = _talent.manaCost;
	activeCustomTrigger = _talent.activeCustomTrigger;
	useRange = _talent.useRange;
	minUseRangeCorrection = _talent.minUseRangeCorrection;
	castAllowRange = _talent.castAllowRange;
	allowChase = _talent.allowChase;
	constants = _talent.constants;
	conditionFormulas = _talent.conditionFormulas;
	isUnitFreeAfterCast = _talent.isUnitFreeAfterCast;
	flags = _talent.flags;
	targetType = _talent.targetType;
	requireLineOfSight = _talent.requireLineOfSight;
	passiveApplicators = _talent.passiveApplicators;
	autoTargetSelector = _talent.autoTargetSelector;
	microAI = _talent.microAI;
	node = _talent.node;
	marker = _talent.marker;
	warFogRemoveTime = _talent.warFogRemoveTime;
	warFogRemoveRadius = _talent.warFogRemoveRadius;
	alternativeTargets = _talent.alternativeTargets;
	dispatch = _talent.dispatch;
	applicators = _talent.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentKit::TalentKit() :
		kitCapacity( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentKit::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &special );
	saver.Add( 4, &kitCapacity );
	saver.Add( 5, &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentKit::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentKit* parentPtr = (TalentKit*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentKit::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "special", &special );
	saver.Add( "kitCapacity", &kitCapacity );
	saver.Add( "talents", &talents );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentKit::Assign( const TalentKit& _talentKit )
{
	name = _talentKit.name;
	special = _talentKit.special;
	kitCapacity = _talentKit.kitCapacity;
	talents = _talentKit.talents;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentPack::TalentPack() :
		isRedPack( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentPack::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &name );
	saver.Add( 4, &iconStyle );
	saver.Add( 5, &icon );
	saver.Add( 6, &isRedPack );
	saver.Add( 7, &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentPack::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentPack* parentPtr = (TalentPack*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentPack::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "name", &name );
	saver.Add( "iconStyle", &iconStyle );
	saver.Add( "icon", &icon );
	saver.Add( "isRedPack", &isRedPack );
	saver.Add( "talents", &talents );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentPack::Assign( const TalentPack& _talentPack )
{
	id = _talentPack.id;
	name = _talentPack.name;
	iconStyle = _talentPack.iconStyle;
	icon = _talentPack.icon;
	isRedPack = _talentPack.isRedPack;
	talents = _talentPack.talents;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentsSet::TalentsSet()
{
	levels.resize( 6 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentsSet::operator&( IBinSaver &saver )
{
	saver.Add( 2, &levels );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentsSet::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentsSet* parentPtr = (TalentsSet*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentsSet::SerializeSelf( IXmlSaver &saver )
{
	levels.resize( 6 );
	saver.Add( "levels", &levels );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentsSet::Assign( const TalentsSet& _talentsSet )
{
	levels = _talentsSet.levels;
}
}; // namespace NDb
