// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Scene/DBSceneBase.h"
#include "DBConsumable.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Consumable );
REGISTER_DBRESOURCE( ConsumablesShop );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EConsumableOrigin value )
{
	switch( value )
	{
		case CONSUMABLEORIGIN_DEFAULT:
			return "Default";
		case CONSUMABLEORIGIN_SHOP:
			return "Shop";
		case CONSUMABLEORIGIN_MINIGAME:
			return "Minigame";
		case CONSUMABLEORIGIN_PICKUPABLE:
			return "Pickupable";
		case CONSUMABLEORIGIN_APPLICATOR:
			return "Applicator";
		case CONSUMABLEORIGIN_SCRIPT:
			return "Script";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EConsumableOrigin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EConsumableOrigin StringToEnum_EConsumableOrigin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EConsumableOrigin)(NStr::ToInt( value ));
	if ( strcmp( value, "Default" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_DEFAULT" ) == 0 )
		return CONSUMABLEORIGIN_DEFAULT;
	if ( strcmp( value, "Shop" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_SHOP" ) == 0 )
		return CONSUMABLEORIGIN_SHOP;
	if ( strcmp( value, "Minigame" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_MINIGAME" ) == 0 )
		return CONSUMABLEORIGIN_MINIGAME;
	if ( strcmp( value, "Pickupable" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_PICKUPABLE" ) == 0 )
		return CONSUMABLEORIGIN_PICKUPABLE;
	if ( strcmp( value, "Applicator" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_APPLICATOR" ) == 0 )
		return CONSUMABLEORIGIN_APPLICATOR;
	if ( strcmp( value, "Script" ) == 0 || strcmp( value, "CONSUMABLEORIGIN_SCRIPT" ) == 0 )
		return CONSUMABLEORIGIN_SCRIPT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EConsumableOrigin", value ) );
	return CONSUMABLEORIGIN_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Consumable::Consumable() :
		naftaCost( 0 )
	, maxQuantity( 1 )
	, isPotion( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Consumable::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Ability*)this );
	saver.Add( 2, &naftaCost );
	saver.Add( 3, &maxQuantity );
	saver.Add( 4, &gameObject );
	saver.Add( 5, &isPotion );
	saver.Add( 6, &persistentId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Consumable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Consumable* parentPtr = (Consumable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Consumable::SerializeSelf( IXmlSaver &saver )
{
	Ability::SerializeSelf( saver );
	saver.Add( "naftaCost", &naftaCost );
	saver.Add( "maxQuantity", &maxQuantity );
	saver.Add( "gameObject", &gameObject );
	saver.Add( "isPotion", &isPotion );
	saver.Add( "persistentId", &persistentId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Consumable::Assign( const Consumable& _consumable )
{
	naftaCost = _consumable.naftaCost;
	maxQuantity = _consumable.maxQuantity;
	gameObject = _consumable.gameObject;
	isPotion = _consumable.isPotion;
	persistentId = _consumable.persistentId;
	name = _consumable.name;
	description = _consumable.description;
	compiledDescriptionA = _consumable.compiledDescriptionA;
	compiledDescriptionB = _consumable.compiledDescriptionB;
	shortDescription = _consumable.shortDescription;
	commonDescription = _consumable.commonDescription;
	castLimitations = _consumable.castLimitations;
	image = _consumable.image;
	imageSecondState = _consumable.imageSecondState;
	aoeType = _consumable.aoeType;
	aoeSize = _consumable.aoeSize;
	aoeMaterial = _consumable.aoeMaterial;
	aoeHeight = _consumable.aoeHeight;
	useRangeMaterial = _consumable.useRangeMaterial;
	aoePassabilityCheckMode = _consumable.aoePassabilityCheckMode;
	aoeDisplayOnMinimap = _consumable.aoeDisplayOnMinimap;
	type = _consumable.type;
	cooldownTime = _consumable.cooldownTime;
	cooldownTimeSecondState = _consumable.cooldownTimeSecondState;
	manaCost = _consumable.manaCost;
	activeCustomTrigger = _consumable.activeCustomTrigger;
	useRange = _consumable.useRange;
	minUseRangeCorrection = _consumable.minUseRangeCorrection;
	castAllowRange = _consumable.castAllowRange;
	allowChase = _consumable.allowChase;
	constants = _consumable.constants;
	conditionFormulas = _consumable.conditionFormulas;
	isUnitFreeAfterCast = _consumable.isUnitFreeAfterCast;
	flags = _consumable.flags;
	targetType = _consumable.targetType;
	requireLineOfSight = _consumable.requireLineOfSight;
	passiveApplicators = _consumable.passiveApplicators;
	autoTargetSelector = _consumable.autoTargetSelector;
	microAI = _consumable.microAI;
	node = _consumable.node;
	marker = _consumable.marker;
	warFogRemoveTime = _consumable.warFogRemoveTime;
	warFogRemoveRadius = _consumable.warFogRemoveRadius;
	alternativeTargets = _consumable.alternativeTargets;
	dispatch = _consumable.dispatch;
	applicators = _consumable.applicators;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsumablesShop::ConsumablesShop() :
		interactionRadius( 10.0f )
	, secretShop( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumablesShop::operator&( IBinSaver &saver )
{
	saver.Add( 2, &items );
	saver.Add( 3, &interactionRadius );
	saver.Add( 4, &secretShop );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumablesShop::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConsumablesShop* parentPtr = (ConsumablesShop*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsumablesShop::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "items", &items );
	saver.Add( "interactionRadius", &interactionRadius );
	saver.Add( "secretShop", &secretShop );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsumablesShop::Assign( const ConsumablesShop& _consumablesShop )
{
	items = _consumablesShop.items;
	interactionRadius = _consumablesShop.interactionRadius;
	secretShop = _consumablesShop.secretShop;
}
}; // namespace NDb
