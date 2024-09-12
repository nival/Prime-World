// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Scene/DBScene.h"
#include "../UI/DBUI.h"
#include "../Render/DBRender.h"
#include "../Sound/DBSound.h"
#include "../Render/DBRenderResources.h"
#include "DBClinic.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( DBMinigame_Clinic );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBonusType value )
{
	switch( value )
	{
		case BONUSTYPE_BROOM:
			return "Broom";
		case BONUSTYPE_COMFORTABLEPILLOW:
			return "ComfortablePillow";
		case BONUSTYPE_BOOKLET:
			return "Booklet";
		case BONUSTYPE_COMFORTABLETABLE:
			return "ComfortableTable";
		case BONUSTYPE_BELL:
			return "Bell";
		case BONUSTYPE_FOOTPATHS:
			return "Footpaths";
		case BONUSTYPE_WHIP:
			return "Whip";
		case BONUSTYPE_VELVETGLOVES:
			return "VelvetGloves";
		case BONUSTYPE_ADVENCEDENTRACE:
			return "AdvencedEntrace";
		case BONUSTYPE_CANDY:
			return "Candy";
		case BONUSTYPE_TALISMAN:
			return "Talisman";
		case BONUSTYPE_TOYBOX:
			return "ToyBox";
		case BONUSTYPE_SPEEDBOOTS:
			return "SpeedBoots";
		case BONUSTYPE_COMFORTABLECARPET:
			return "ComfortableCarpet";
		case BONUSTYPE_SUPERCLEANER:
			return "SuperCleaner";
		case BONUSTYPE_BOOTCOVERS:
			return "BootCovers";
		case BONUSTYPE_BESTCLINIC:
			return "BestClinic";
		case BONUSTYPE_STAR:
			return "Star";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBonusType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBonusType StringToEnum_EBonusType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBonusType)(NStr::ToInt( value ));
	if ( strcmp( value, "Broom" ) == 0 || strcmp( value, "BONUSTYPE_BROOM" ) == 0 )
		return BONUSTYPE_BROOM;
	if ( strcmp( value, "ComfortablePillow" ) == 0 || strcmp( value, "BONUSTYPE_COMFORTABLEPILLOW" ) == 0 )
		return BONUSTYPE_COMFORTABLEPILLOW;
	if ( strcmp( value, "Booklet" ) == 0 || strcmp( value, "BONUSTYPE_BOOKLET" ) == 0 )
		return BONUSTYPE_BOOKLET;
	if ( strcmp( value, "ComfortableTable" ) == 0 || strcmp( value, "BONUSTYPE_COMFORTABLETABLE" ) == 0 )
		return BONUSTYPE_COMFORTABLETABLE;
	if ( strcmp( value, "Bell" ) == 0 || strcmp( value, "BONUSTYPE_BELL" ) == 0 )
		return BONUSTYPE_BELL;
	if ( strcmp( value, "Footpaths" ) == 0 || strcmp( value, "BONUSTYPE_FOOTPATHS" ) == 0 )
		return BONUSTYPE_FOOTPATHS;
	if ( strcmp( value, "Whip" ) == 0 || strcmp( value, "BONUSTYPE_WHIP" ) == 0 )
		return BONUSTYPE_WHIP;
	if ( strcmp( value, "VelvetGloves" ) == 0 || strcmp( value, "BONUSTYPE_VELVETGLOVES" ) == 0 )
		return BONUSTYPE_VELVETGLOVES;
	if ( strcmp( value, "AdvencedEntrace" ) == 0 || strcmp( value, "BONUSTYPE_ADVENCEDENTRACE" ) == 0 )
		return BONUSTYPE_ADVENCEDENTRACE;
	if ( strcmp( value, "Candy" ) == 0 || strcmp( value, "BONUSTYPE_CANDY" ) == 0 )
		return BONUSTYPE_CANDY;
	if ( strcmp( value, "Talisman" ) == 0 || strcmp( value, "BONUSTYPE_TALISMAN" ) == 0 )
		return BONUSTYPE_TALISMAN;
	if ( strcmp( value, "ToyBox" ) == 0 || strcmp( value, "BONUSTYPE_TOYBOX" ) == 0 )
		return BONUSTYPE_TOYBOX;
	if ( strcmp( value, "SpeedBoots" ) == 0 || strcmp( value, "BONUSTYPE_SPEEDBOOTS" ) == 0 )
		return BONUSTYPE_SPEEDBOOTS;
	if ( strcmp( value, "ComfortableCarpet" ) == 0 || strcmp( value, "BONUSTYPE_COMFORTABLECARPET" ) == 0 )
		return BONUSTYPE_COMFORTABLECARPET;
	if ( strcmp( value, "SuperCleaner" ) == 0 || strcmp( value, "BONUSTYPE_SUPERCLEANER" ) == 0 )
		return BONUSTYPE_SUPERCLEANER;
	if ( strcmp( value, "BootCovers" ) == 0 || strcmp( value, "BONUSTYPE_BOOTCOVERS" ) == 0 )
		return BONUSTYPE_BOOTCOVERS;
	if ( strcmp( value, "BestClinic" ) == 0 || strcmp( value, "BONUSTYPE_BESTCLINIC" ) == 0 )
		return BONUSTYPE_BESTCLINIC;
	if ( strcmp( value, "Star" ) == 0 || strcmp( value, "BONUSTYPE_STAR" ) == 0 )
		return BONUSTYPE_STAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBonusType", value ) );
	return BONUSTYPE_BROOM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EClinicSounds value )
{
	switch( value )
	{
		case CLINICSOUNDS_STARTLEVEL:
			return "StartLevel";
		case CLINICSOUNDS_LEVELWINWITHMEDAL:
			return "LevelWinWithMedal";
		case CLINICSOUNDS_LEVELWINWITHOUTMEDAL:
			return "LevelWinWithoutMedal";
		case CLINICSOUNDS_CREEPWISHMELEE:
			return "CreepWishMelee";
		case CLINICSOUNDS_CREEPWISHRANGED:
			return "CreepWishRanged";
		case CLINICSOUNDS_CREEPWISHSIEGE:
			return "CreepWishSiege";
		case CLINICSOUNDS_CREEPWISHDESIREDMELEE:
			return "CreepWishDesiredMelee";
		case CLINICSOUNDS_CREEPWISHDESIREDRANGED:
			return "CreepWishDesiredRanged";
		case CLINICSOUNDS_CREEPWISHDESIREDSIEGE:
			return "CreepWishDesiredSiege";
		case CLINICSOUNDS_CREEPBECOMELAZY:
			return "CreepBecomeLazy";
		case CLINICSOUNDS_CREEPLOOSEWISH:
			return "CreepLooseWish";
		case CLINICSOUNDS_USETABLE:
			return "UseTable";
		case CLINICSOUNDS_USEWASHTAB:
			return "UseWashtab";
		case CLINICSOUNDS_USEBAD:
			return "UseBad";
		case CLINICSOUNDS_USEPLAYGROUND:
			return "UsePlayground";
		case CLINICSOUNDS_CREEPFRIENDSHIP:
			return "CreepFriendship";
		case CLINICSOUNDS_CREEPBAR25:
			return "CreepBar25";
		case CLINICSOUNDS_CREEPBAR50:
			return "CreepBar50";
		case CLINICSOUNDS_CREEPWAKEUP:
			return "CreepWakeup";
		case CLINICSOUNDS_PLACEBECOMEDIRTY:
			return "PlaceBecomeDirty";
		case CLINICSOUNDS_BUY:
			return "Buy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EClinicSounds", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EClinicSounds StringToEnum_EClinicSounds( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EClinicSounds)(NStr::ToInt( value ));
	if ( strcmp( value, "StartLevel" ) == 0 || strcmp( value, "CLINICSOUNDS_STARTLEVEL" ) == 0 )
		return CLINICSOUNDS_STARTLEVEL;
	if ( strcmp( value, "LevelWinWithMedal" ) == 0 || strcmp( value, "CLINICSOUNDS_LEVELWINWITHMEDAL" ) == 0 )
		return CLINICSOUNDS_LEVELWINWITHMEDAL;
	if ( strcmp( value, "LevelWinWithoutMedal" ) == 0 || strcmp( value, "CLINICSOUNDS_LEVELWINWITHOUTMEDAL" ) == 0 )
		return CLINICSOUNDS_LEVELWINWITHOUTMEDAL;
	if ( strcmp( value, "CreepWishMelee" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHMELEE" ) == 0 )
		return CLINICSOUNDS_CREEPWISHMELEE;
	if ( strcmp( value, "CreepWishRanged" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHRANGED" ) == 0 )
		return CLINICSOUNDS_CREEPWISHRANGED;
	if ( strcmp( value, "CreepWishSiege" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHSIEGE" ) == 0 )
		return CLINICSOUNDS_CREEPWISHSIEGE;
	if ( strcmp( value, "CreepWishDesiredMelee" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHDESIREDMELEE" ) == 0 )
		return CLINICSOUNDS_CREEPWISHDESIREDMELEE;
	if ( strcmp( value, "CreepWishDesiredRanged" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHDESIREDRANGED" ) == 0 )
		return CLINICSOUNDS_CREEPWISHDESIREDRANGED;
	if ( strcmp( value, "CreepWishDesiredSiege" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWISHDESIREDSIEGE" ) == 0 )
		return CLINICSOUNDS_CREEPWISHDESIREDSIEGE;
	if ( strcmp( value, "CreepBecomeLazy" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPBECOMELAZY" ) == 0 )
		return CLINICSOUNDS_CREEPBECOMELAZY;
	if ( strcmp( value, "CreepLooseWish" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPLOOSEWISH" ) == 0 )
		return CLINICSOUNDS_CREEPLOOSEWISH;
	if ( strcmp( value, "UseTable" ) == 0 || strcmp( value, "CLINICSOUNDS_USETABLE" ) == 0 )
		return CLINICSOUNDS_USETABLE;
	if ( strcmp( value, "UseWashtab" ) == 0 || strcmp( value, "CLINICSOUNDS_USEWASHTAB" ) == 0 )
		return CLINICSOUNDS_USEWASHTAB;
	if ( strcmp( value, "UseBad" ) == 0 || strcmp( value, "CLINICSOUNDS_USEBAD" ) == 0 )
		return CLINICSOUNDS_USEBAD;
	if ( strcmp( value, "UsePlayground" ) == 0 || strcmp( value, "CLINICSOUNDS_USEPLAYGROUND" ) == 0 )
		return CLINICSOUNDS_USEPLAYGROUND;
	if ( strcmp( value, "CreepFriendship" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPFRIENDSHIP" ) == 0 )
		return CLINICSOUNDS_CREEPFRIENDSHIP;
	if ( strcmp( value, "CreepBar25" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPBAR25" ) == 0 )
		return CLINICSOUNDS_CREEPBAR25;
	if ( strcmp( value, "CreepBar50" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPBAR50" ) == 0 )
		return CLINICSOUNDS_CREEPBAR50;
	if ( strcmp( value, "CreepWakeup" ) == 0 || strcmp( value, "CLINICSOUNDS_CREEPWAKEUP" ) == 0 )
		return CLINICSOUNDS_CREEPWAKEUP;
	if ( strcmp( value, "PlaceBecomeDirty" ) == 0 || strcmp( value, "CLINICSOUNDS_PLACEBECOMEDIRTY" ) == 0 )
		return CLINICSOUNDS_PLACEBECOMEDIRTY;
	if ( strcmp( value, "Buy" ) == 0 || strcmp( value, "CLINICSOUNDS_BUY" ) == 0 )
		return CLINICSOUNDS_BUY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EClinicSounds", value ) );
	return CLINICSOUNDS_STARTLEVEL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ECreepState value )
{
	switch( value )
	{
		case CREEPSTATE_WORKING:
			return "Working";
		case CREEPSTATE_SLEEPING:
			return "Sleeping";
		case CREEPSTATE_NEEDWASH:
			return "NeedWash";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ECreepState", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECreepState StringToEnum_ECreepState( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECreepState)(NStr::ToInt( value ));
	if ( strcmp( value, "Working" ) == 0 || strcmp( value, "CREEPSTATE_WORKING" ) == 0 )
		return CREEPSTATE_WORKING;
	if ( strcmp( value, "Sleeping" ) == 0 || strcmp( value, "CREEPSTATE_SLEEPING" ) == 0 )
		return CREEPSTATE_SLEEPING;
	if ( strcmp( value, "NeedWash" ) == 0 || strcmp( value, "CREEPSTATE_NEEDWASH" ) == 0 )
		return CREEPSTATE_NEEDWASH;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECreepState", value ) );
	return CREEPSTATE_WORKING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ECreepWish value )
{
	switch( value )
	{
		case CREEPWISH_NONE:
			return "None";
		case CREEPWISH_SLEEP:
			return "Sleep";
		case CREEPWISH_WASH:
			return "Wash";
		case CREEPWISH_EAT:
			return "Eat";
		case CREEPWISH_PLAY:
			return "Play";
		case CREEPWISH_CARPET:
			return "Carpet";
		case CREEPWISH_ANY:
			return "Any";
		case CREEPWISH_EXIT:
			return "Exit";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ECreepWish", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECreepWish StringToEnum_ECreepWish( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECreepWish)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "CREEPWISH_NONE" ) == 0 )
		return CREEPWISH_NONE;
	if ( strcmp( value, "Sleep" ) == 0 || strcmp( value, "CREEPWISH_SLEEP" ) == 0 )
		return CREEPWISH_SLEEP;
	if ( strcmp( value, "Wash" ) == 0 || strcmp( value, "CREEPWISH_WASH" ) == 0 )
		return CREEPWISH_WASH;
	if ( strcmp( value, "Eat" ) == 0 || strcmp( value, "CREEPWISH_EAT" ) == 0 )
		return CREEPWISH_EAT;
	if ( strcmp( value, "Play" ) == 0 || strcmp( value, "CREEPWISH_PLAY" ) == 0 )
		return CREEPWISH_PLAY;
	if ( strcmp( value, "Carpet" ) == 0 || strcmp( value, "CREEPWISH_CARPET" ) == 0 )
		return CREEPWISH_CARPET;
	if ( strcmp( value, "Any" ) == 0 || strcmp( value, "CREEPWISH_ANY" ) == 0 )
		return CREEPWISH_ANY;
	if ( strcmp( value, "Exit" ) == 0 || strcmp( value, "CREEPWISH_EXIT" ) == 0 )
		return CREEPWISH_EXIT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECreepWish", value ) );
	return CREEPWISH_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPlaceType value )
{
	switch( value )
	{
		case PLACETYPE_NONE:
			return "None";
		case PLACETYPE_TABLE:
			return "Table";
		case PLACETYPE_BAD:
			return "Bad";
		case PLACETYPE_WASHTAB:
			return "Washtab";
		case PLACETYPE_GAMEPLACE:
			return "GamePlace";
		case PLACETYPE_CREEPPLACE:
			return "CreepPlace";
		case PLACETYPE_ENTRANCE:
			return "Entrance";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPlaceType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPlaceType StringToEnum_EPlaceType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPlaceType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "PLACETYPE_NONE" ) == 0 )
		return PLACETYPE_NONE;
	if ( strcmp( value, "Table" ) == 0 || strcmp( value, "PLACETYPE_TABLE" ) == 0 )
		return PLACETYPE_TABLE;
	if ( strcmp( value, "Bad" ) == 0 || strcmp( value, "PLACETYPE_BAD" ) == 0 )
		return PLACETYPE_BAD;
	if ( strcmp( value, "Washtab" ) == 0 || strcmp( value, "PLACETYPE_WASHTAB" ) == 0 )
		return PLACETYPE_WASHTAB;
	if ( strcmp( value, "GamePlace" ) == 0 || strcmp( value, "PLACETYPE_GAMEPLACE" ) == 0 )
		return PLACETYPE_GAMEPLACE;
	if ( strcmp( value, "CreepPlace" ) == 0 || strcmp( value, "PLACETYPE_CREEPPLACE" ) == 0 )
		return PLACETYPE_CREEPPLACE;
	if ( strcmp( value, "Entrance" ) == 0 || strcmp( value, "PLACETYPE_ENTRANCE" ) == 0 )
		return PLACETYPE_ENTRANCE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPlaceType", value ) );
	return PLACETYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BonusDesc::BonusDesc() :
		cooldown( 0.0f )
	, duration( 20.0f )
	, accessibility( -1 )
	, cost( 100 )
	, useCost( 10 )
	, value( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BonusDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &description );
	saver.Add( 3, &name );
	saver.Add( 4, &position );
	saver.Add( 5, &cooldown );
	saver.Add( 6, &duration );
	saver.Add( 7, &accessibility );
	saver.Add( 8, &cost );
	saver.Add( 9, &useCost );
	saver.Add( 10, &value );
	saver.Add( 11, &sceneObject );
	saver.Add( 12, &overtip );
	saver.Add( 13, &iconMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BonusDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "description", &description );
	saver.Add( "name", &name );
	saver.Add( "position", &position );
	saver.Add( "cooldown", &cooldown );
	saver.Add( "duration", &duration );
	saver.Add( "accessibility", &accessibility );
	saver.Add( "cost", &cost );
	saver.Add( "useCost", &useCost );
	saver.Add( "value", &value );
	saver.Add( "sceneObject", &sceneObject );
	saver.Add( "overtip", &overtip );
	saver.Add( "iconMaterial", &iconMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepBehaviourDesc::CreepBehaviourDesc() :
		timeBeforeSearchFriend( 0.0f )
	, friendshipBonus( 0.02f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepBehaviourDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &timeBeforeSearchFriend );
	saver.Add( 3, &friendshipBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepBehaviourDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "timeBeforeSearchFriend", &timeBeforeSearchFriend );
	saver.Add( "friendshipBonus", &friendshipBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepPlaceDesc::CreepPlaceDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepPlaceDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &position );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepPlaceDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "position", &position );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepsDesc::CreepsDesc() :
		goldMedalValue( 0.75f )
	, silverMedalValue( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepsDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sceneObjectMelee );
	saver.Add( 3, &sceneObjectRange );
	saver.Add( 4, &sceneObjectSiege );
	saver.Add( 5, &imageMeleeMaterial );
	saver.Add( 6, &imageRangeMaterial );
	saver.Add( 7, &imageSiegeMaterial );
	saver.Add( 8, &overtip );
	saver.Add( 9, &goldMedalValue );
	saver.Add( 10, &silverMedalValue );
	saver.Add( 11, &creepPlaces );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepsDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "sceneObjectMelee", &sceneObjectMelee );
	saver.Add( "sceneObjectRange", &sceneObjectRange );
	saver.Add( "sceneObjectSiege", &sceneObjectSiege );
	saver.Add( "imageMeleeMaterial", &imageMeleeMaterial );
	saver.Add( "imageRangeMaterial", &imageRangeMaterial );
	saver.Add( "imageSiegeMaterial", &imageSiegeMaterial );
	saver.Add( "overtip", &overtip );
	saver.Add( "goldMedalValue", &goldMedalValue );
	saver.Add( "silverMedalValue", &silverMedalValue );
	saver.Add( "creepPlaces", &creepPlaces );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DecorationDesc::DecorationDesc()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecorationDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &position );
	saver.Add( 3, &sceneObject );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecorationDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "position", &position );
	saver.Add( "sceneObject", &sceneObject );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IntOffsets::IntOffsets() :
		pxBefore( 0 )
	, pxAfter( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IntOffsets::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pxBefore );
	saver.Add( 3, &pxAfter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IntOffsets::operator&( IXmlSaver &saver )
{
	saver.Add( "pxBefore", &pxBefore );
	saver.Add( "pxAfter", &pxAfter );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LevelDesc::LevelDesc() :
		expToOpen( 0 )
	, levelFinishBonus( 100.0f )
	, creepTraindedBonus( 100.0f )
	, levelFinishMoney( 100 )
	, creepMedalMoney( 5 )
	, duration( 3.0f )
	, numberOfMelee( 1 )
	, numberOfRange( 1 )
	, numberOfSiege( 1 )
	, casualWishGeneration( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &expToOpen );
	saver.Add( 3, &levelFinishBonus );
	saver.Add( 4, &creepTraindedBonus );
	saver.Add( 5, &levelFinishMoney );
	saver.Add( 6, &creepMedalMoney );
	saver.Add( 7, &duration );
	saver.Add( 8, &name );
	saver.Add( 9, &description );
	saver.Add( 10, &numberOfMelee );
	saver.Add( 11, &numberOfRange );
	saver.Add( 12, &numberOfSiege );
	saver.Add( 13, &casualWishGeneration );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LevelDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "expToOpen", &expToOpen );
	saver.Add( "levelFinishBonus", &levelFinishBonus );
	saver.Add( "creepTraindedBonus", &creepTraindedBonus );
	saver.Add( "levelFinishMoney", &levelFinishMoney );
	saver.Add( "creepMedalMoney", &creepMedalMoney );
	saver.Add( "duration", &duration );
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "numberOfMelee", &numberOfMelee );
	saver.Add( "numberOfRange", &numberOfRange );
	saver.Add( "numberOfSiege", &numberOfSiege );
	saver.Add( "casualWishGeneration", &casualWishGeneration );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameUIStylesDesc::MinigameUIStylesDesc() :
		creepsAppearPause( 0.0f )
	, creepAppearTime( 0.0f )
	, creepMedalAppearTime( 0.0f )
	, medalAppearPause( 0.0f )
	, medalAppearTime( 0.0f )
	, naftaAnimationSpeed( 0.0f )
{
	creepWishMaterials.resize( 8 );
	creepStateMaterials.resize( 3 );
	creepFriendshipMaterials.resize( 5 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigameUIStylesDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &creepWishMaterials );
	saver.Add( 3, &creepStateMaterials );
	saver.Add( 4, &creepFriendshipMaterials );
	saver.Add( 5, &creepsAppearPause );
	saver.Add( 6, &creepAppearTime );
	saver.Add( 7, &creepMedalAppearTime );
	saver.Add( 8, &medalAppearPause );
	saver.Add( 9, &medalAppearTime );
	saver.Add( 10, &naftaAnimationSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigameUIStylesDesc::operator&( IXmlSaver &saver )
{
	creepWishMaterials.resize( 8 );
	saver.Add( "creepWishMaterials", &creepWishMaterials );
	creepStateMaterials.resize( 3 );
	saver.Add( "creepStateMaterials", &creepStateMaterials );
	creepFriendshipMaterials.resize( 5 );
	saver.Add( "creepFriendshipMaterials", &creepFriendshipMaterials );
	saver.Add( "creepsAppearPause", &creepsAppearPause );
	saver.Add( "creepAppearTime", &creepAppearTime );
	saver.Add( "creepMedalAppearTime", &creepMedalAppearTime );
	saver.Add( "medalAppearPause", &medalAppearPause );
	saver.Add( "medalAppearTime", &medalAppearTime );
	saver.Add( "naftaAnimationSpeed", &naftaAnimationSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NeighbourhoodDesc::NeighbourhoodDesc() :
		first( 0 )
	, second( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NeighbourhoodDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &first );
	saver.Add( 3, &second );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NeighbourhoodDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "first", &first );
	saver.Add( "second", &second );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlaceDesc::PlaceDesc() :
		placeType( PLACETYPE_BAD )
	, accessibility( -1 )
	, cost( 250 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlaceDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &placeType );
	saver.Add( 3, &position );
	saver.Add( 4, &sceneObject );
	saver.Add( 5, &sceneObjectDirty50 );
	saver.Add( 6, &overtip );
	saver.Add( 7, &accessibility );
	saver.Add( 8, &cost );
	saver.Add( 9, &name );
	saver.Add( 10, &description );
	saver.Add( 11, &iconMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlaceDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "placeType", &placeType );
	saver.Add( "position", &position );
	saver.Add( "sceneObject", &sceneObject );
	saver.Add( "sceneObjectDirty50", &sceneObjectDirty50 );
	saver.Add( "overtip", &overtip );
	saver.Add( "accessibility", &accessibility );
	saver.Add( "cost", &cost );
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "iconMaterial", &iconMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PlayerDesc::PlayerDesc() :
		velocity( 2.0f )
	, scaleFactor( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayerDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startPosition );
	saver.Add( 3, &velocity );
	saver.Add( 4, &scaleFactor );
	saver.Add( 5, &animationGraph );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PlayerDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "startPosition", &startPosition );
	saver.Add( "velocity", &velocity );
	saver.Add( "scaleFactor", &scaleFactor );
	saver.Add( "animationGraph", &animationGraph );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Preselection::Preselection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Preselection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &colorNotBought );
	saver.Add( 3, &colorNotBoughtUnavailable );
	saver.Add( 4, &colorNotBoughtPreselect );
	saver.Add( 5, &colorPreselect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Preselection::operator&( IXmlSaver &saver )
{
	saver.Add( "colorNotBought", &colorNotBought );
	saver.Add( "colorNotBoughtUnavailable", &colorNotBoughtUnavailable );
	saver.Add( "colorNotBoughtPreselect", &colorNotBoughtPreselect );
	saver.Add( "colorPreselect", &colorPreselect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TrainingBonuses::TrainingBonuses()
{
	statLifeBar50.resize( 32, float() );
	statLifeBar59.resize( 32, float() );
	statLifeBar69.resize( 32, float() );
	statLifeBar79.resize( 32, float() );
	statLifeBar89.resize( 32, float() );
	statLifeBar100.resize( 32, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TrainingBonuses::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statLifeBar50 );
	saver.Add( 3, &statLifeBar59 );
	saver.Add( 4, &statLifeBar69 );
	saver.Add( 5, &statLifeBar79 );
	saver.Add( 6, &statLifeBar89 );
	saver.Add( 7, &statLifeBar100 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TrainingBonuses::operator&( IXmlSaver &saver )
{
	statLifeBar50.resize( 32 );
	saver.Add( "statLifeBar50", &statLifeBar50 );
	statLifeBar59.resize( 32 );
	saver.Add( "statLifeBar59", &statLifeBar59 );
	statLifeBar69.resize( 32 );
	saver.Add( "statLifeBar69", &statLifeBar69 );
	statLifeBar79.resize( 32 );
	saver.Add( "statLifeBar79", &statLifeBar79 );
	statLifeBar89.resize( 32 );
	saver.Add( "statLifeBar89", &statLifeBar89 );
	statLifeBar100.resize( 32 );
	saver.Add( "statLifeBar100", &statLifeBar100 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBMinigame_Clinic::DBMinigame_Clinic() :
		soilPersentMelee( 15.0f )
	, soilPersentRange( 15.0f )
	, soilPersentSiege( 35.0f )
	, clickBonusClickCount( 10 )
	, clickBonusValue( 0.02f )
	, heartsBonus( 0.5f )
	, minTimeBetweenCreeps( 2.0f )
	, maxTimeBetweenCreeps( 5.0f )
	, minThinkTime( 3.0f )
	, maxThinkTime( 5.0f )
	, waitTime( 30.0f )
	, fallAsleepTime( 3.0f )
	, wakeupTime( 3.0f )
	, workTime( 5.0f )
	, workBonus( 0.1f )
	, failBonus( 0.1f )
	, level1_BarValue( 40.0f )
	, level3_phase1Min( 8.0f )
	, level3_phase1Max( 12.0f )
	, level4_washProbTimes( 2.0f )
	, level5_fallAsleepTime( 2.0f )
	, level6_soilAtStart( 90.0f )
	, level8_timeReduction( 2.0f )
	, level8_bonusReduction( 50.0f )
	, level9_washProb( 80.0f )
	, level10_playProbTimes( 2.0f )
	, level11_soilIncrease( 200.0f )
	, level12_soilIncrease( 150.0f )
	, level12_bonusReduction( 70.0f )
	, level12_waitDecrease( 2.0f )
{
	sounds.resize( 21 );
	bonusSounds.resize( 18 );
	bonuses.resize( 18 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinigame_Clinic::operator&( IBinSaver &saver )
{
	saver.Add( 2, &title );
	saver.Add( 3, &cameraOptions );
	saver.Add( 4, &sounds );
	saver.Add( 5, &bonusSounds );
	saver.Add( 6, &preselection );
	saver.Add( 7, &player );
	saver.Add( 8, &bonuses );
	saver.Add( 9, &places );
	saver.Add( 10, &sceneObjectDirty100 );
	saver.Add( 11, &neighbourhood );
	saver.Add( 12, &levels );
	saver.Add( 13, &decorations );
	saver.Add( 14, &creepsDesc );
	saver.Add( 15, &creepBehaviourDesc );
	saver.Add( 16, &trainingBonuses );
	saver.Add( 17, &soilPersentMelee );
	saver.Add( 18, &soilPersentRange );
	saver.Add( 19, &soilPersentSiege );
	saver.Add( 20, &clickBonusClickCount );
	saver.Add( 21, &clickBonusValue );
	saver.Add( 22, &heartsBonus );
	saver.Add( 23, &minTimeBetweenCreeps );
	saver.Add( 24, &maxTimeBetweenCreeps );
	saver.Add( 25, &minThinkTime );
	saver.Add( 26, &maxThinkTime );
	saver.Add( 27, &waitTime );
	saver.Add( 28, &fallAsleepTime );
	saver.Add( 29, &wakeupTime );
	saver.Add( 30, &workTime );
	saver.Add( 31, &workBonus );
	saver.Add( 32, &failBonus );
	saver.Add( 33, &level1_BarValue );
	saver.Add( 34, &level3_phase1Min );
	saver.Add( 35, &level3_phase1Max );
	saver.Add( 36, &level4_washProbTimes );
	saver.Add( 37, &level5_fallAsleepTime );
	saver.Add( 38, &level6_soilAtStart );
	saver.Add( 39, &level8_timeReduction );
	saver.Add( 40, &level8_bonusReduction );
	saver.Add( 41, &level9_washProb );
	saver.Add( 42, &level10_playProbTimes );
	saver.Add( 43, &level11_soilIncrease );
	saver.Add( 44, &level12_soilIncrease );
	saver.Add( 45, &level12_bonusReduction );
	saver.Add( 46, &level12_waitDecrease );
	saver.Add( 47, &uiStyles );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinigame_Clinic::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBMinigame_Clinic* parentPtr = (DBMinigame_Clinic*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinigame_Clinic::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "title", &title );
	saver.Add( "cameraOptions", &cameraOptions );
	sounds.resize( 21 );
	saver.Add( "sounds", &sounds );
	bonusSounds.resize( 18 );
	saver.Add( "bonusSounds", &bonusSounds );
	saver.Add( "preselection", &preselection );
	saver.Add( "player", &player );
	bonuses.resize( 18 );
	saver.Add( "bonuses", &bonuses );
	saver.Add( "places", &places );
	saver.Add( "sceneObjectDirty100", &sceneObjectDirty100 );
	saver.Add( "neighbourhood", &neighbourhood );
	saver.Add( "levels", &levels );
	saver.Add( "decorations", &decorations );
	saver.Add( "creepsDesc", &creepsDesc );
	saver.Add( "creepBehaviourDesc", &creepBehaviourDesc );
	saver.Add( "trainingBonuses", &trainingBonuses );
	saver.Add( "soilPersentMelee", &soilPersentMelee );
	saver.Add( "soilPersentRange", &soilPersentRange );
	saver.Add( "soilPersentSiege", &soilPersentSiege );
	saver.Add( "clickBonusClickCount", &clickBonusClickCount );
	saver.Add( "clickBonusValue", &clickBonusValue );
	saver.Add( "heartsBonus", &heartsBonus );
	saver.Add( "minTimeBetweenCreeps", &minTimeBetweenCreeps );
	saver.Add( "maxTimeBetweenCreeps", &maxTimeBetweenCreeps );
	saver.Add( "minThinkTime", &minThinkTime );
	saver.Add( "maxThinkTime", &maxThinkTime );
	saver.Add( "waitTime", &waitTime );
	saver.Add( "fallAsleepTime", &fallAsleepTime );
	saver.Add( "wakeupTime", &wakeupTime );
	saver.Add( "workTime", &workTime );
	saver.Add( "workBonus", &workBonus );
	saver.Add( "failBonus", &failBonus );
	saver.Add( "level1_BarValue", &level1_BarValue );
	saver.Add( "level3_phase1Min", &level3_phase1Min );
	saver.Add( "level3_phase1Max", &level3_phase1Max );
	saver.Add( "level4_washProbTimes", &level4_washProbTimes );
	saver.Add( "level5_fallAsleepTime", &level5_fallAsleepTime );
	saver.Add( "level6_soilAtStart", &level6_soilAtStart );
	saver.Add( "level8_timeReduction", &level8_timeReduction );
	saver.Add( "level8_bonusReduction", &level8_bonusReduction );
	saver.Add( "level9_washProb", &level9_washProb );
	saver.Add( "level10_playProbTimes", &level10_playProbTimes );
	saver.Add( "level11_soilIncrease", &level11_soilIncrease );
	saver.Add( "level12_soilIncrease", &level12_soilIncrease );
	saver.Add( "level12_bonusReduction", &level12_bonusReduction );
	saver.Add( "level12_waitDecrease", &level12_waitDecrease );
	saver.Add( "uiStyles", &uiStyles );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinigame_Clinic::Assign( const DBMinigame_Clinic& _dBMinigame_Clinic )
{
	title = _dBMinigame_Clinic.title;
	cameraOptions.name = _dBMinigame_Clinic.cameraOptions.name;
	cameraOptions.anchor = _dBMinigame_Clinic.cameraOptions.anchor;
	cameraOptions.yaw = _dBMinigame_Clinic.cameraOptions.yaw;
	cameraOptions.pitch = _dBMinigame_Clinic.cameraOptions.pitch;
	cameraOptions.roll = _dBMinigame_Clinic.cameraOptions.roll;
	cameraOptions.rod = _dBMinigame_Clinic.cameraOptions.rod;
	cameraOptions.fov = _dBMinigame_Clinic.cameraOptions.fov;
	cameraOptions.environment = _dBMinigame_Clinic.cameraOptions.environment;
	sounds = _dBMinigame_Clinic.sounds;
	bonusSounds = _dBMinigame_Clinic.bonusSounds;
	preselection.colorNotBought = _dBMinigame_Clinic.preselection.colorNotBought;
	preselection.colorNotBoughtUnavailable = _dBMinigame_Clinic.preselection.colorNotBoughtUnavailable;
	preselection.colorNotBoughtPreselect = _dBMinigame_Clinic.preselection.colorNotBoughtPreselect;
	preselection.colorPreselect = _dBMinigame_Clinic.preselection.colorPreselect;
	player.startPosition = _dBMinigame_Clinic.player.startPosition;
	player.velocity = _dBMinigame_Clinic.player.velocity;
	player.scaleFactor = _dBMinigame_Clinic.player.scaleFactor;
	player.animationGraph = _dBMinigame_Clinic.player.animationGraph;
	bonuses = _dBMinigame_Clinic.bonuses;
	places = _dBMinigame_Clinic.places;
	sceneObjectDirty100 = _dBMinigame_Clinic.sceneObjectDirty100;
	neighbourhood = _dBMinigame_Clinic.neighbourhood;
	levels = _dBMinigame_Clinic.levels;
	decorations = _dBMinigame_Clinic.decorations;
	creepsDesc.sceneObjectMelee = _dBMinigame_Clinic.creepsDesc.sceneObjectMelee;
	creepsDesc.sceneObjectRange = _dBMinigame_Clinic.creepsDesc.sceneObjectRange;
	creepsDesc.sceneObjectSiege = _dBMinigame_Clinic.creepsDesc.sceneObjectSiege;
	creepsDesc.imageMeleeMaterial = _dBMinigame_Clinic.creepsDesc.imageMeleeMaterial;
	creepsDesc.imageRangeMaterial = _dBMinigame_Clinic.creepsDesc.imageRangeMaterial;
	creepsDesc.imageSiegeMaterial = _dBMinigame_Clinic.creepsDesc.imageSiegeMaterial;
	creepsDesc.overtip = _dBMinigame_Clinic.creepsDesc.overtip;
	creepsDesc.goldMedalValue = _dBMinigame_Clinic.creepsDesc.goldMedalValue;
	creepsDesc.silverMedalValue = _dBMinigame_Clinic.creepsDesc.silverMedalValue;
	creepsDesc.creepPlaces = _dBMinigame_Clinic.creepsDesc.creepPlaces;
	creepBehaviourDesc.timeBeforeSearchFriend = _dBMinigame_Clinic.creepBehaviourDesc.timeBeforeSearchFriend;
	creepBehaviourDesc.friendshipBonus = _dBMinigame_Clinic.creepBehaviourDesc.friendshipBonus;
	trainingBonuses.statLifeBar50 = _dBMinigame_Clinic.trainingBonuses.statLifeBar50;
	trainingBonuses.statLifeBar59 = _dBMinigame_Clinic.trainingBonuses.statLifeBar59;
	trainingBonuses.statLifeBar69 = _dBMinigame_Clinic.trainingBonuses.statLifeBar69;
	trainingBonuses.statLifeBar79 = _dBMinigame_Clinic.trainingBonuses.statLifeBar79;
	trainingBonuses.statLifeBar89 = _dBMinigame_Clinic.trainingBonuses.statLifeBar89;
	trainingBonuses.statLifeBar100 = _dBMinigame_Clinic.trainingBonuses.statLifeBar100;
	soilPersentMelee = _dBMinigame_Clinic.soilPersentMelee;
	soilPersentRange = _dBMinigame_Clinic.soilPersentRange;
	soilPersentSiege = _dBMinigame_Clinic.soilPersentSiege;
	clickBonusClickCount = _dBMinigame_Clinic.clickBonusClickCount;
	clickBonusValue = _dBMinigame_Clinic.clickBonusValue;
	heartsBonus = _dBMinigame_Clinic.heartsBonus;
	minTimeBetweenCreeps = _dBMinigame_Clinic.minTimeBetweenCreeps;
	maxTimeBetweenCreeps = _dBMinigame_Clinic.maxTimeBetweenCreeps;
	minThinkTime = _dBMinigame_Clinic.minThinkTime;
	maxThinkTime = _dBMinigame_Clinic.maxThinkTime;
	waitTime = _dBMinigame_Clinic.waitTime;
	fallAsleepTime = _dBMinigame_Clinic.fallAsleepTime;
	wakeupTime = _dBMinigame_Clinic.wakeupTime;
	workTime = _dBMinigame_Clinic.workTime;
	workBonus = _dBMinigame_Clinic.workBonus;
	failBonus = _dBMinigame_Clinic.failBonus;
	level1_BarValue = _dBMinigame_Clinic.level1_BarValue;
	level3_phase1Min = _dBMinigame_Clinic.level3_phase1Min;
	level3_phase1Max = _dBMinigame_Clinic.level3_phase1Max;
	level4_washProbTimes = _dBMinigame_Clinic.level4_washProbTimes;
	level5_fallAsleepTime = _dBMinigame_Clinic.level5_fallAsleepTime;
	level6_soilAtStart = _dBMinigame_Clinic.level6_soilAtStart;
	level8_timeReduction = _dBMinigame_Clinic.level8_timeReduction;
	level8_bonusReduction = _dBMinigame_Clinic.level8_bonusReduction;
	level9_washProb = _dBMinigame_Clinic.level9_washProb;
	level10_playProbTimes = _dBMinigame_Clinic.level10_playProbTimes;
	level11_soilIncrease = _dBMinigame_Clinic.level11_soilIncrease;
	level12_soilIncrease = _dBMinigame_Clinic.level12_soilIncrease;
	level12_bonusReduction = _dBMinigame_Clinic.level12_bonusReduction;
	level12_waitDecrease = _dBMinigame_Clinic.level12_waitDecrease;
	uiStyles.creepWishMaterials = _dBMinigame_Clinic.uiStyles.creepWishMaterials;
	uiStyles.creepStateMaterials = _dBMinigame_Clinic.uiStyles.creepStateMaterials;
	uiStyles.creepFriendshipMaterials = _dBMinigame_Clinic.uiStyles.creepFriendshipMaterials;
	uiStyles.creepsAppearPause = _dBMinigame_Clinic.uiStyles.creepsAppearPause;
	uiStyles.creepAppearTime = _dBMinigame_Clinic.uiStyles.creepAppearTime;
	uiStyles.creepMedalAppearTime = _dBMinigame_Clinic.uiStyles.creepMedalAppearTime;
	uiStyles.medalAppearPause = _dBMinigame_Clinic.uiStyles.medalAppearPause;
	uiStyles.medalAppearTime = _dBMinigame_Clinic.uiStyles.medalAppearTime;
	uiStyles.naftaAnimationSpeed = _dBMinigame_Clinic.uiStyles.naftaAnimationSpeed;
}
}; // namespace NDb
