// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../Scene/DBSceneBase.h"
#include "../PF_GameLogic/DBTalent.h"
#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/DBHeroRanks.h"
#include "../PF_GameLogic/DBConsumable.h"
#include "../PF_Core/DBEffect.h"
#include "DBGameLogic.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AILogicParameters );
REGISTER_DBRESOURCE( BehaviourTrackerParams );
REGISTER_DBRESOURCE( BotsSettings );
REGISTER_DBRESOURCE( BuyServicesContainer );
REGISTER_DBRESOURCE( ChatLogicParameters );
REGISTER_DBRESOURCE( ConsumableGroupList );
REGISTER_DBRESOURCE( DBGameMenu );
REGISTER_DBRESOURCE( DBLevelToExperience );
REGISTER_DBRESOURCE( DBRatingToFame );
REGISTER_DBRESOURCE( ForceParameters );
REGISTER_DBRESOURCE( HeroRespawnParams );
REGISTER_DBRESOURCE( MinigamesBasic );
REGISTER_DBRESOURCE( TalentGroupList );
REGISTER_DBRESOURCE( TalentKitList );
REGISTER_DBRESOURCE( TalentPackList );
REGISTER_DBRESOURCE( TeamsColoringScheme );
REGISTER_DBRESOURCE( UnitDeathParameters );
REGISTER_DBRESOURCE( UnitLogicParameters );
REGISTER_DBRESOURCE( UnitsLogicParameters );
REGISTER_DBRESOURCE( UnitTargetingParameters );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BillingServicesStart value )
{
	switch( value )
	{
		case BILLINGSERVICESSTART_IMPULSES:
			return "Impulses";
		case BILLINGSERVICESSTART_GENERIC:
			return "Generic";
		case BILLINGSERVICESSTART_REWARDS:
			return "Rewards";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BillingServicesStart", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BillingServicesStart StringToEnum_BillingServicesStart( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BillingServicesStart)(NStr::ToInt( value ));
	if ( strcmp( value, "Impulses" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_IMPULSES" ) == 0 )
		return BILLINGSERVICESSTART_IMPULSES;
	if ( strcmp( value, "Generic" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_GENERIC" ) == 0 )
		return BILLINGSERVICESSTART_GENERIC;
	if ( strcmp( value, "Rewards" ) == 0 || strcmp( value, "BILLINGSERVICESSTART_REWARDS" ) == 0 )
		return BILLINGSERVICESSTART_REWARDS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BillingServicesStart", value ) );
	return BILLINGSERVICESSTART_IMPULSES;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGender value )
{
	switch( value )
	{
		case GENDER_MALE:
			return "Male";
		case GENDER_FEMALE:
			return "Female";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EGender", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGender StringToEnum_EGender( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGender)(NStr::ToInt( value ));
	if ( strcmp( value, "Male" ) == 0 || strcmp( value, "GENDER_MALE" ) == 0 )
		return GENDER_MALE;
	if ( strcmp( value, "Female" ) == 0 || strcmp( value, "GENDER_FEMALE" ) == 0 )
		return GENDER_FEMALE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGender", value ) );
	return GENDER_MALE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGlyphSpawnMode value )
{
	switch( value )
	{
		case GLYPHSPAWNMODE_RANDOMWEIGHT:
			return "RandomWeight";
		case GLYPHSPAWNMODE_ORDERED:
			return "Ordered";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EGlyphSpawnMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGlyphSpawnMode StringToEnum_EGlyphSpawnMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGlyphSpawnMode)(NStr::ToInt( value ));
	if ( strcmp( value, "RandomWeight" ) == 0 || strcmp( value, "GLYPHSPAWNMODE_RANDOMWEIGHT" ) == 0 )
		return GLYPHSPAWNMODE_RANDOMWEIGHT;
	if ( strcmp( value, "Ordered" ) == 0 || strcmp( value, "GLYPHSPAWNMODE_ORDERED" ) == 0 )
		return GLYPHSPAWNMODE_ORDERED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGlyphSpawnMode", value ) );
	return GLYPHSPAWNMODE_RANDOMWEIGHT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMenuItemAction value )
{
	switch( value )
	{
		case MENUITEMACTION_GOBACK:
			return "GoBack";
		case MENUITEMACTION_CONTACTWITHGAMEMASTER:
			return "ContactWithGameMaster";
		case MENUITEMACTION_OPENSUBMENU:
			return "OpenSubmenu";
		case MENUITEMACTION_GAMESETTINGS:
			return "GameSettings";
		case MENUITEMACTION_GRAPHICSETTINGS:
			return "GraphicSettings";
		case MENUITEMACTION_SOUNDSETTINGS:
			return "SoundSettings";
		case MENUITEMACTION_CONTROLSETTINGS:
			return "ControlSettings";
		case MENUITEMACTION_GOTOTOWN:
			return "GoToTown";
		case MENUITEMACTION_LEAVETHEGAME:
			return "LeaveTheGame";
		case MENUITEMACTION_LEAVEMINIGAME:
			return "LeaveMinigame";
		case MENUITEMACTION_ABORTMINIGAMELEVEL:
			return "AbortMinigameLevel";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMenuItemAction", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMenuItemAction StringToEnum_EMenuItemAction( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMenuItemAction)(NStr::ToInt( value ));
	if ( strcmp( value, "GoBack" ) == 0 || strcmp( value, "MENUITEMACTION_GOBACK" ) == 0 )
		return MENUITEMACTION_GOBACK;
	if ( strcmp( value, "ContactWithGameMaster" ) == 0 || strcmp( value, "MENUITEMACTION_CONTACTWITHGAMEMASTER" ) == 0 )
		return MENUITEMACTION_CONTACTWITHGAMEMASTER;
	if ( strcmp( value, "OpenSubmenu" ) == 0 || strcmp( value, "MENUITEMACTION_OPENSUBMENU" ) == 0 )
		return MENUITEMACTION_OPENSUBMENU;
	if ( strcmp( value, "GameSettings" ) == 0 || strcmp( value, "MENUITEMACTION_GAMESETTINGS" ) == 0 )
		return MENUITEMACTION_GAMESETTINGS;
	if ( strcmp( value, "GraphicSettings" ) == 0 || strcmp( value, "MENUITEMACTION_GRAPHICSETTINGS" ) == 0 )
		return MENUITEMACTION_GRAPHICSETTINGS;
	if ( strcmp( value, "SoundSettings" ) == 0 || strcmp( value, "MENUITEMACTION_SOUNDSETTINGS" ) == 0 )
		return MENUITEMACTION_SOUNDSETTINGS;
	if ( strcmp( value, "ControlSettings" ) == 0 || strcmp( value, "MENUITEMACTION_CONTROLSETTINGS" ) == 0 )
		return MENUITEMACTION_CONTROLSETTINGS;
	if ( strcmp( value, "GoToTown" ) == 0 || strcmp( value, "MENUITEMACTION_GOTOTOWN" ) == 0 )
		return MENUITEMACTION_GOTOTOWN;
	if ( strcmp( value, "LeaveTheGame" ) == 0 || strcmp( value, "MENUITEMACTION_LEAVETHEGAME" ) == 0 )
		return MENUITEMACTION_LEAVETHEGAME;
	if ( strcmp( value, "LeaveMinigame" ) == 0 || strcmp( value, "MENUITEMACTION_LEAVEMINIGAME" ) == 0 )
		return MENUITEMACTION_LEAVEMINIGAME;
	if ( strcmp( value, "AbortMinigameLevel" ) == 0 || strcmp( value, "MENUITEMACTION_ABORTMINIGAMELEVEL" ) == 0 )
		return MENUITEMACTION_ABORTMINIGAMELEVEL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMenuItemAction", value ) );
	return MENUITEMACTION_GOBACK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMenuItemType value )
{
	switch( value )
	{
		case MENUITEMTYPE_BUTTONTYPE:
			return "ButtonType";
		case MENUITEMTYPE_TEXTTYPE:
			return "TextType";
		case MENUITEMTYPE_ICONTYPE:
			return "IconType";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMenuItemType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMenuItemType StringToEnum_EMenuItemType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMenuItemType)(NStr::ToInt( value ));
	if ( strcmp( value, "ButtonType" ) == 0 || strcmp( value, "MENUITEMTYPE_BUTTONTYPE" ) == 0 )
		return MENUITEMTYPE_BUTTONTYPE;
	if ( strcmp( value, "TextType" ) == 0 || strcmp( value, "MENUITEMTYPE_TEXTTYPE" ) == 0 )
		return MENUITEMTYPE_TEXTTYPE;
	if ( strcmp( value, "IconType" ) == 0 || strcmp( value, "MENUITEMTYPE_ICONTYPE" ) == 0 )
		return MENUITEMTYPE_ICONTYPE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMenuItemType", value ) );
	return MENUITEMTYPE_BUTTONTYPE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETeamColorID value )
{
	switch( value )
	{
		case TEAMCOLORID_TEAM:
			return "Team";
		case TEAMCOLORID_HERO1:
			return "Hero1";
		case TEAMCOLORID_HERO2:
			return "Hero2";
		case TEAMCOLORID_HERO3:
			return "Hero3";
		case TEAMCOLORID_HERO4:
			return "Hero4";
		case TEAMCOLORID_HERO5:
			return "Hero5";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETeamColorID", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETeamColorID StringToEnum_ETeamColorID( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETeamColorID)(NStr::ToInt( value ));
	if ( strcmp( value, "Team" ) == 0 || strcmp( value, "TEAMCOLORID_TEAM" ) == 0 )
		return TEAMCOLORID_TEAM;
	if ( strcmp( value, "Hero1" ) == 0 || strcmp( value, "TEAMCOLORID_HERO1" ) == 0 )
		return TEAMCOLORID_HERO1;
	if ( strcmp( value, "Hero2" ) == 0 || strcmp( value, "TEAMCOLORID_HERO2" ) == 0 )
		return TEAMCOLORID_HERO2;
	if ( strcmp( value, "Hero3" ) == 0 || strcmp( value, "TEAMCOLORID_HERO3" ) == 0 )
		return TEAMCOLORID_HERO3;
	if ( strcmp( value, "Hero4" ) == 0 || strcmp( value, "TEAMCOLORID_HERO4" ) == 0 )
		return TEAMCOLORID_HERO4;
	if ( strcmp( value, "Hero5" ) == 0 || strcmp( value, "TEAMCOLORID_HERO5" ) == 0 )
		return TEAMCOLORID_HERO5;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETeamColorID", value ) );
	return TEAMCOLORID_TEAM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const GeneralServices value )
{
	switch( value )
	{
		case GENERALSERVICES_ZZBOOST:
			return "ZZBoost";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum GeneralServices", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GeneralServices StringToEnum_GeneralServices( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (GeneralServices)(NStr::ToInt( value ));
	if ( strcmp( value, "ZZBoost" ) == 0 || strcmp( value, "GENERALSERVICES_ZZBOOST" ) == 0 )
		return GENERALSERVICES_ZZBOOST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum GeneralServices", value ) );
	return GENERALSERVICES_ZZBOOST;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ImpulseBuffs value )
{
	switch( value )
	{
		case IMPULSEBUFFS_BUFF_HEALING:
			return "Buff_Healing";
		case IMPULSEBUFFS_BUFF_GETMANA:
			return "Buff_GetMana";
		case IMPULSEBUFFS_BUFF_CLEANISING:
			return "Buff_Cleanising";
		case IMPULSEBUFFS_BUFF_RISING:
			return "Buff_Rising";
		case IMPULSEBUFFS_BUFF_INVULNERABILITY:
			return "Buff_Invulnerability";
		case IMPULSEBUFFS_BUFF_BLAST:
			return "Buff_Blast";
		case IMPULSEBUFFS_BUFF_SPEED:
			return "Buff_Speed";
		case IMPULSEBUFFS_BUFF_HELP:
			return "Buff_Help";
		case IMPULSEBUFFS_BUFF_GRATITUDE1:
			return "Buff_Gratitude1";
		case IMPULSEBUFFS_BUFF_GRATITUDE2:
			return "Buff_Gratitude2";
		case IMPULSEBUFFS_BUFF_RESURRECTION:
			return "Buff_Resurrection";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ImpulseBuffs", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ImpulseBuffs StringToEnum_ImpulseBuffs( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ImpulseBuffs)(NStr::ToInt( value ));
	if ( strcmp( value, "Buff_Healing" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_HEALING" ) == 0 )
		return IMPULSEBUFFS_BUFF_HEALING;
	if ( strcmp( value, "Buff_GetMana" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_GETMANA" ) == 0 )
		return IMPULSEBUFFS_BUFF_GETMANA;
	if ( strcmp( value, "Buff_Cleanising" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_CLEANISING" ) == 0 )
		return IMPULSEBUFFS_BUFF_CLEANISING;
	if ( strcmp( value, "Buff_Rising" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_RISING" ) == 0 )
		return IMPULSEBUFFS_BUFF_RISING;
	if ( strcmp( value, "Buff_Invulnerability" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_INVULNERABILITY" ) == 0 )
		return IMPULSEBUFFS_BUFF_INVULNERABILITY;
	if ( strcmp( value, "Buff_Blast" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_BLAST" ) == 0 )
		return IMPULSEBUFFS_BUFF_BLAST;
	if ( strcmp( value, "Buff_Speed" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_SPEED" ) == 0 )
		return IMPULSEBUFFS_BUFF_SPEED;
	if ( strcmp( value, "Buff_Help" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_HELP" ) == 0 )
		return IMPULSEBUFFS_BUFF_HELP;
	if ( strcmp( value, "Buff_Gratitude1" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_GRATITUDE1" ) == 0 )
		return IMPULSEBUFFS_BUFF_GRATITUDE1;
	if ( strcmp( value, "Buff_Gratitude2" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_GRATITUDE2" ) == 0 )
		return IMPULSEBUFFS_BUFF_GRATITUDE2;
	if ( strcmp( value, "Buff_Resurrection" ) == 0 || strcmp( value, "IMPULSEBUFFS_BUFF_RESURRECTION" ) == 0 )
		return IMPULSEBUFFS_BUFF_RESURRECTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ImpulseBuffs", value ) );
	return IMPULSEBUFFS_BUFF_HEALING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TeamForceCalcMethod value )
{
	switch( value )
	{
		case TEAMFORCECALCMETHOD_MINIMUM:
			return "Minimum";
		case TEAMFORCECALCMETHOD_AVERAGE:
			return "Average";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TeamForceCalcMethod", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TeamForceCalcMethod StringToEnum_TeamForceCalcMethod( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TeamForceCalcMethod)(NStr::ToInt( value ));
	if ( strcmp( value, "Minimum" ) == 0 || strcmp( value, "TEAMFORCECALCMETHOD_MINIMUM" ) == 0 )
		return TEAMFORCECALCMETHOD_MINIMUM;
	if ( strcmp( value, "Average" ) == 0 || strcmp( value, "TEAMFORCECALCMETHOD_AVERAGE" ) == 0 )
		return TEAMFORCECALCMETHOD_AVERAGE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TeamForceCalcMethod", value ) );
	return TEAMFORCECALCMETHOD_MINIMUM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ZZRewards value )
{
	switch( value )
	{
		case ZZREWARDS_VICTORY:
			return "Victory";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ZZRewards", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ZZRewards StringToEnum_ZZRewards( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ZZRewards)(NStr::ToInt( value ));
	if ( strcmp( value, "Victory" ) == 0 || strcmp( value, "ZZREWARDS_VICTORY" ) == 0 )
		return ZZREWARDS_VICTORY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ZZRewards", value ) );
	return ZZREWARDS_VICTORY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityAndDamageScalingParams::AbilityAndDamageScalingParams() :
		abilityScaleStatLeft( 50.0f )
	, abilityScaleStatRight( 160.0f )
	, abilityScaleLifeLeft( 600.0f )
	, abilityScaleLifeRight( 3350.0f )
	, abilityScaleEnergyLeft( 600.0f )
	, abilityScaleEnergyRight( 3350.0f )
	, damageScaleStatLeft( 50.0f )
	, damageScaleStatRight( 223.0f )
	, damageScaleLifeLeft( 600.0f )
	, damageScaleLifeRight( 4683.0f )
	, damageScaleEnergyLeft( 600.0f )
	, damageScaleEnergyRight( 4683.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityAndDamageScalingParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &abilityScaleStatLeft );
	saver.Add( 3, &abilityScaleStatRight );
	saver.Add( 4, &abilityScaleLifeLeft );
	saver.Add( 5, &abilityScaleLifeRight );
	saver.Add( 6, &abilityScaleEnergyLeft );
	saver.Add( 7, &abilityScaleEnergyRight );
	saver.Add( 8, &damageScaleStatLeft );
	saver.Add( 9, &damageScaleStatRight );
	saver.Add( 10, &damageScaleLifeLeft );
	saver.Add( 11, &damageScaleLifeRight );
	saver.Add( 12, &damageScaleEnergyLeft );
	saver.Add( 13, &damageScaleEnergyRight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbilityAndDamageScalingParams::operator&( IXmlSaver &saver )
{
	saver.Add( "abilityScaleStatLeft", &abilityScaleStatLeft );
	saver.Add( "abilityScaleStatRight", &abilityScaleStatRight );
	saver.Add( "abilityScaleLifeLeft", &abilityScaleLifeLeft );
	saver.Add( "abilityScaleLifeRight", &abilityScaleLifeRight );
	saver.Add( "abilityScaleEnergyLeft", &abilityScaleEnergyLeft );
	saver.Add( "abilityScaleEnergyRight", &abilityScaleEnergyRight );
	saver.Add( "damageScaleStatLeft", &damageScaleStatLeft );
	saver.Add( "damageScaleStatRight", &damageScaleStatRight );
	saver.Add( "damageScaleLifeLeft", &damageScaleLifeLeft );
	saver.Add( "damageScaleLifeRight", &damageScaleLifeRight );
	saver.Add( "damageScaleEnergyLeft", &damageScaleEnergyLeft );
	saver.Add( "damageScaleEnergyRight", &damageScaleEnergyRight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BuyServiceCost::BuyServiceCost() :
		goldCost( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServiceCost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &goldCost );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServiceCost::operator&( IXmlSaver &saver )
{
	saver.Add( "goldCost", &goldCost );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommonSummonParameters::CommonSummonParameters() :
		primarySummonEscortDistance( 4.5f )
	, secondarySummonEscortDistance( 7.0f )
	, petEscortDistance( 2.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CommonSummonParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &primarySummonEscortDistance );
	saver.Add( 3, &secondarySummonEscortDistance );
	saver.Add( 4, &petEscortDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CommonSummonParameters::operator&( IXmlSaver &saver )
{
	saver.Add( "primarySummonEscortDistance", &primarySummonEscortDistance );
	saver.Add( "secondarySummonEscortDistance", &secondarySummonEscortDistance );
	saver.Add( "petEscortDistance", &petEscortDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsumableGroup::ConsumableGroup() :
		cooldown( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumableGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &description );
	saver.Add( 4, &cooldown );
	saver.Add( 5, &consumables );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumableGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "cooldown", &cooldown );
	saver.Add( "consumables", &consumables );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreatureHappyStateParams::CreatureHappyStateParams() :
		happyCreaturesPercent( 0.5f )
	, minRestTime( 0.5f )
	, happyCheckTick( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreatureHappyStateParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &happyCreaturesPercent );
	saver.Add( 3, &minRestTime );
	saver.Add( 4, &happyCheckTick );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreatureHappyStateParams::operator&( IXmlSaver &saver )
{
	saver.Add( "happyCreaturesPercent", &happyCreaturesPercent );
	saver.Add( "minRestTime", &minRestTime );
	saver.Add( "happyCheckTick", &happyCheckTick );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CreepsLevelUpInfo::CreepsLevelUpInfo() :
		interval( 300.0f )
	, increment( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepsLevelUpInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &interval );
	saver.Add( 3, &increment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CreepsLevelUpInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "interval", &interval );
	saver.Add( "increment", &increment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBFameRatingPair::DBFameRatingPair() :
		fameLevel( 0 )
	, rating( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFameRatingPair::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fameLevel );
	saver.Add( 3, &rating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFameRatingPair::operator&( IXmlSaver &saver )
{
	saver.Add( "fameLevel", &fameLevel );
	saver.Add( "rating", &rating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExpoModeParams::ExpoModeParams() :
		minHeroLife( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExpoModeParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statsEnhancers );
	saver.Add( 3, &minHeroLife );
	saver.Add( 4, &damageModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExpoModeParams::operator&( IXmlSaver &saver )
{
	saver.Add( "statsEnhancers", &statsEnhancers );
	saver.Add( "minHeroLife", &minHeroLife );
	saver.Add( "damageModifier", &damageModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameMenuItem::GameMenuItem() :
		itemType( MENUITEMTYPE_BUTTONTYPE )
	, itemAction( MENUITEMACTION_GOBACK )
	, minigamesOnly( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameMenuItem::operator&( IBinSaver &saver )
{
	saver.Add( 2, &itemText );
	saver.Add( 3, &itemType );
	saver.Add( 4, &itemAction );
	saver.Add( 5, &minigamesOnly );
	saver.Add( 6, &subMenu );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameMenuItem::operator&( IXmlSaver &saver )
{
	saver.Add( "itemText", &itemText );
	saver.Add( "itemType", &itemType );
	saver.Add( "itemAction", &itemAction );
	saver.Add( "minigamesOnly", &minigamesOnly );
	saver.Add( "subMenu", &subMenu );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlyphSettings::GlyphSettings() :
		minNormalSpawnDelay( 50.0f )
	, maxNormalSpawnDelay( 150.0f )
	, minAfterPickupSpawnDelay( 50.0f )
	, maxAfterPickupSpawnDelay( 240.0f )
	, spawnAttemptDelayDecrease( 50.0f )
	, maxInstances( 2 )
	, spawnMode( GLYPHSPAWNMODE_RANDOMWEIGHT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minNormalSpawnDelay );
	saver.Add( 3, &maxNormalSpawnDelay );
	saver.Add( 4, &minAfterPickupSpawnDelay );
	saver.Add( 5, &maxAfterPickupSpawnDelay );
	saver.Add( 6, &spawnAttemptDelayDecrease );
	saver.Add( 7, &maxInstances );
	saver.Add( 8, &spawnMode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GlyphSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "minNormalSpawnDelay", &minNormalSpawnDelay );
	saver.Add( "maxNormalSpawnDelay", &maxNormalSpawnDelay );
	saver.Add( "minAfterPickupSpawnDelay", &minAfterPickupSpawnDelay );
	saver.Add( "maxAfterPickupSpawnDelay", &maxAfterPickupSpawnDelay );
	saver.Add( "spawnAttemptDelayDecrease", &spawnAttemptDelayDecrease );
	saver.Add( "maxInstances", &maxInstances );
	saver.Add( "spawnMode", &spawnMode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroStatisticsParams::HeroStatisticsParams() :
		timeSlicePeriod( 60.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroStatisticsParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &timeSlicePeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroStatisticsParams::operator&( IXmlSaver &saver )
{
	saver.Add( "timeSlicePeriod", &timeSlicePeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KillTimeIntervals::KillTimeIntervals() :
		creepKillInterval( 0.5f )
	, buildingKillInterval( 2.0f )
	, heroKillerDeadInterval( 5.0f )
	, heroKillDamageInterval( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillTimeIntervals::operator&( IBinSaver &saver )
{
	saver.Add( 2, &creepKillInterval );
	saver.Add( 3, &buildingKillInterval );
	saver.Add( 4, &heroKillerDeadInterval );
	saver.Add( 5, &heroKillDamageInterval );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KillTimeIntervals::operator&( IXmlSaver &saver )
{
	saver.Add( "creepKillInterval", &creepKillInterval );
	saver.Add( "buildingKillInterval", &buildingKillInterval );
	saver.Add( "heroKillerDeadInterval", &heroKillerDeadInterval );
	saver.Add( "heroKillDamageInterval", &heroKillDamageInterval );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OvertimeRespawnParams::OvertimeRespawnParams() :
		overtime( 25.0f )
	, respawnDelayForOvertime( 1.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OvertimeRespawnParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &overtime );
	saver.Add( 3, &respawnDelayForOvertime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OvertimeRespawnParams::operator&( IXmlSaver &saver )
{
	saver.Add( "overtime", &overtime );
	saver.Add( "respawnDelayForOvertime", &respawnDelayForOvertime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentGroup::TalentGroup() :
		cooldown( 15.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &description );
	saver.Add( 4, &cooldown );
	saver.Add( 5, &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "description", &description );
	saver.Add( "cooldown", &cooldown );
	saver.Add( "talents", &talents );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeamColors::TeamColors()
{
	teamColors.resize( 6 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamColors::operator&( IBinSaver &saver )
{
	saver.Add( 2, &teamColors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamColors::operator&( IXmlSaver &saver )
{
	teamColors.resize( 6 );
	saver.Add( "teamColors", &teamColors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TurretParams::TurretParams() :
		turretAngleSpeed( 100.0f )
	, turretAngleAcceleration( 25.0f )
	, turretRotaionTolerance( 5.0f )
	, turretLastAngleResetDelay( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TurretParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &turretAngleSpeed );
	saver.Add( 3, &turretAngleAcceleration );
	saver.Add( 4, &turretRotaionTolerance );
	saver.Add( 5, &turretLastAngleResetDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TurretParams::operator&( IXmlSaver &saver )
{
	saver.Add( "turretAngleSpeed", &turretAngleSpeed );
	saver.Add( "turretAngleAcceleration", &turretAngleAcceleration );
	saver.Add( "turretRotaionTolerance", &turretRotaionTolerance );
	saver.Add( "turretLastAngleResetDelay", &turretLastAngleResetDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AILogicParameters::AILogicParameters() :
		heroAdvanceRespawnTime( 1.0f )
	, baseRedeemCost( 100.0f )
	, redeemCostPerLevel( 10.0f )
	, redeemCostrecalculateTime( 3.0f )
	, followRange( 4.0f )
	, pickupItemRange( 2.0f )
	, killAwardPartyMultiplier( 1.0f )
	, maxTrueSightRange( 15.0f )
	, channelingAbilityRangeMultiplier( 1.2f )
	, heroScreamDelay( 3.0f )
	, globalCooldownTime( 1.0f )
	, skeletonLifeTime( 10.0f )
	, assistAccountTime( 30.0f )
	, creepsWavesDelay( 30 )
	, creepLevelCap( 30 )
	, movingTimerBlock( 3.0f )
	, rotationSpeed( 1000.0f )
	, rotationSpeedZ( 100.0f )
	, expandNatureSegmentRation( 1 )
	, expandNatureGlyphsLifeTime( 30.0f )
	, expandNatureGlyphsVisibilityRadius( 10.0f )
	, buildingsDenyMinHealth( 0.0f )
	, buildingsDenyExperiencePenalty( 0.5f )
	, buildingsDenyNaftaPenalty( 0.0f )
	, buildingsDenyNaftaSpecPenalty( 0.0f )
	, buildingsDenyTeamNaftaPenalty( 0.5f )
	, buildingsMinHealthExplosionPercent( 80.0f )
	, buildingsFragEffectProbability( 0.2f )
	, talentsBuyRange( 15.0f )
	, talentBaseStatBudget( 480.0f )
	, pauseSeconds( 300.0f )
	, warFogRemoveTime( 0.4f )
	, warFogRemoveRadius( 4.0f )
	, maxCreepsCount( 256 )
	, baseEmblemHeroNeeds( 3 )
{
	teamsNames.resize( 3 );
	quarterDestroyStatsMultipliers.resize( 32, float() );
	mainBuildingTurretParams.resize( 2 );
	talentNaftaCostByLevel.resize( 6, int() );
	talentVendorCostByRarity.resize( 7, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AILogicParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &teamsNames );
	saver.Add( 3, &chestGameObject );
	saver.Add( 4, &conditionFormulas );
	saver.Add( 5, &globalConstants );
	saver.Add( 6, &heroRespawnParams );
	saver.Add( 7, &heroAdvanceRespawnTime );
	saver.Add( 8, &baseRedeemCost );
	saver.Add( 9, &redeemCostPerLevel );
	saver.Add( 10, &redeemCostrecalculateTime );
	saver.Add( 11, &followRange );
	saver.Add( 12, &pickupItemRange );
	saver.Add( 13, &killAwardPartyMultiplier );
	saver.Add( 14, &maxTrueSightRange );
	saver.Add( 15, &channelingAbilityRangeMultiplier );
	saver.Add( 16, &heroScreamDelay );
	saver.Add( 17, &globalCooldownTime );
	saver.Add( 18, &skeletonLifeTime );
	saver.Add( 19, &glyphSettings );
	saver.Add( 20, &assistAccountTime );
	saver.Add( 21, &killTimeIntervals );
	saver.Add( 22, &creepsWavesDelay );
	saver.Add( 23, &creepLevelCap );
	saver.Add( 24, &creepsLevelUpInfo );
	saver.Add( 25, &quarterDestroyStatsMultipliers );
	saver.Add( 26, &movingTimerBlock );
	saver.Add( 27, &creatureHappyStateParams );
	saver.Add( 28, &commonSummonParameters );
	saver.Add( 29, &rotationSpeed );
	saver.Add( 30, &rotationSpeedZ );
	saver.Add( 31, &towerTurretParams );
	saver.Add( 32, &mainBuildingTurretParams );
	saver.Add( 33, &expandNatureSegmentRation );
	saver.Add( 34, &expandNatureGlyphsLifeTime );
	saver.Add( 35, &expandNatureGlyphsVisibilityRadius );
	saver.Add( 36, &expandNatureGlyphGameObject );
	saver.Add( 37, &buildingsDenyAbility );
	saver.Add( 38, &buildingsDenyMinHealth );
	saver.Add( 39, &buildingsDenyExperiencePenalty );
	saver.Add( 40, &buildingsDenyNaftaPenalty );
	saver.Add( 41, &buildingsDenyNaftaSpecPenalty );
	saver.Add( 42, &buildingsDenyTeamNaftaPenalty );
	saver.Add( 43, &buildingsAbilityA );
	saver.Add( 44, &buildingsAbilityB );
	saver.Add( 45, &buildingsMinHealthExplosionPercent );
	saver.Add( 46, &buildingsFragEffectProbability );
	saver.Add( 47, &raiseFlagAbility );
	saver.Add( 48, &talentsBuyRange );
	saver.Add( 49, &defaultTalentsSet );
	saver.Add( 50, &talentBaseStatBudget );
	saver.Add( 51, &talentNaftaCostByLevel );
	saver.Add( 52, &talentVendorCostByRarity );
	saver.Add( 53, &pauseSeconds );
	saver.Add( 54, &derivativeStats );
	saver.Add( 55, &statsBudget );
	saver.Add( 56, &forceParameters );
	saver.Add( 57, &talentGroups );
	saver.Add( 58, &consumableGroups );
	saver.Add( 59, &talentKits );
	saver.Add( 60, &talentPacks );
	saver.Add( 61, &energyDamageReduction );
	saver.Add( 62, &physicalDamageReduction );
	saver.Add( 63, &heroStatisticsParams );
	saver.Add( 64, &expoModeParams );
	saver.Add( 65, &abilityAndDamageScalingParams );
	saver.Add( 66, &levelToExperienceTable );
	saver.Add( 67, &botsSettings );
	saver.Add( 68, &warFogRemoveTime );
	saver.Add( 69, &warFogRemoveRadius );
	saver.Add( 70, &maxCreepsCount );
	saver.Add( 71, &portal );
	saver.Add( 72, &heroRanks );
	saver.Add( 73, &baseEmblemHeroNeeds );
	saver.Add( 74, &behaviourTrackerParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AILogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AILogicParameters* parentPtr = (AILogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AILogicParameters::SerializeSelf( IXmlSaver &saver )
{
	teamsNames.resize( 3 );
	saver.Add( "teamsNames", &teamsNames );
	saver.Add( "chestGameObject", &chestGameObject );
	saver.Add( "conditionFormulas", &conditionFormulas );
	saver.Add( "globalConstants", &globalConstants );
	saver.Add( "heroRespawnParams", &heroRespawnParams );
	saver.Add( "heroAdvanceRespawnTime", &heroAdvanceRespawnTime );
	saver.Add( "baseRedeemCost", &baseRedeemCost );
	saver.Add( "redeemCostPerLevel", &redeemCostPerLevel );
	saver.Add( "redeemCostrecalculateTime", &redeemCostrecalculateTime );
	saver.Add( "followRange", &followRange );
	saver.Add( "pickupItemRange", &pickupItemRange );
	saver.Add( "killAwardPartyMultiplier", &killAwardPartyMultiplier );
	saver.Add( "maxTrueSightRange", &maxTrueSightRange );
	saver.Add( "channelingAbilityRangeMultiplier", &channelingAbilityRangeMultiplier );
	saver.Add( "heroScreamDelay", &heroScreamDelay );
	saver.Add( "globalCooldownTime", &globalCooldownTime );
	saver.Add( "skeletonLifeTime", &skeletonLifeTime );
	saver.Add( "glyphSettings", &glyphSettings );
	saver.Add( "assistAccountTime", &assistAccountTime );
	saver.Add( "killTimeIntervals", &killTimeIntervals );
	saver.Add( "creepsWavesDelay", &creepsWavesDelay );
	saver.Add( "creepLevelCap", &creepLevelCap );
	saver.Add( "creepsLevelUpInfo", &creepsLevelUpInfo );
	quarterDestroyStatsMultipliers.resize( 32 );
	saver.Add( "quarterDestroyStatsMultipliers", &quarterDestroyStatsMultipliers );
	saver.Add( "movingTimerBlock", &movingTimerBlock );
	saver.Add( "creatureHappyStateParams", &creatureHappyStateParams );
	saver.Add( "commonSummonParameters", &commonSummonParameters );
	saver.Add( "rotationSpeed", &rotationSpeed );
	saver.Add( "rotationSpeedZ", &rotationSpeedZ );
	saver.Add( "towerTurretParams", &towerTurretParams );
	mainBuildingTurretParams.resize( 2 );
	saver.Add( "mainBuildingTurretParams", &mainBuildingTurretParams );
	saver.Add( "expandNatureSegmentRation", &expandNatureSegmentRation );
	saver.Add( "expandNatureGlyphsLifeTime", &expandNatureGlyphsLifeTime );
	saver.Add( "expandNatureGlyphsVisibilityRadius", &expandNatureGlyphsVisibilityRadius );
	saver.Add( "expandNatureGlyphGameObject", &expandNatureGlyphGameObject );
	saver.Add( "buildingsDenyAbility", &buildingsDenyAbility );
	saver.Add( "buildingsDenyMinHealth", &buildingsDenyMinHealth );
	saver.Add( "buildingsDenyExperiencePenalty", &buildingsDenyExperiencePenalty );
	saver.Add( "buildingsDenyNaftaPenalty", &buildingsDenyNaftaPenalty );
	saver.Add( "buildingsDenyNaftaSpecPenalty", &buildingsDenyNaftaSpecPenalty );
	saver.Add( "buildingsDenyTeamNaftaPenalty", &buildingsDenyTeamNaftaPenalty );
	saver.Add( "buildingsAbilityA", &buildingsAbilityA );
	saver.Add( "buildingsAbilityB", &buildingsAbilityB );
	saver.Add( "buildingsMinHealthExplosionPercent", &buildingsMinHealthExplosionPercent );
	saver.Add( "buildingsFragEffectProbability", &buildingsFragEffectProbability );
	saver.Add( "raiseFlagAbility", &raiseFlagAbility );
	saver.Add( "talentsBuyRange", &talentsBuyRange );
	saver.Add( "defaultTalentsSet", &defaultTalentsSet );
	saver.Add( "talentBaseStatBudget", &talentBaseStatBudget );
	talentNaftaCostByLevel.resize( 6 );
	saver.Add( "talentNaftaCostByLevel", &talentNaftaCostByLevel );
	talentVendorCostByRarity.resize( 7 );
	saver.Add( "talentVendorCostByRarity", &talentVendorCostByRarity );
	saver.Add( "pauseSeconds", &pauseSeconds );
	saver.Add( "derivativeStats", &derivativeStats );
	saver.Add( "statsBudget", &statsBudget );
	saver.Add( "forceParameters", &forceParameters );
	saver.Add( "talentGroups", &talentGroups );
	saver.Add( "consumableGroups", &consumableGroups );
	saver.Add( "talentKits", &talentKits );
	saver.Add( "talentPacks", &talentPacks );
	saver.Add( "energyDamageReduction", &energyDamageReduction );
	saver.Add( "physicalDamageReduction", &physicalDamageReduction );
	saver.Add( "heroStatisticsParams", &heroStatisticsParams );
	saver.Add( "expoModeParams", &expoModeParams );
	saver.Add( "abilityAndDamageScalingParams", &abilityAndDamageScalingParams );
	saver.Add( "levelToExperienceTable", &levelToExperienceTable );
	saver.Add( "botsSettings", &botsSettings );
	saver.Add( "warFogRemoveTime", &warFogRemoveTime );
	saver.Add( "warFogRemoveRadius", &warFogRemoveRadius );
	saver.Add( "maxCreepsCount", &maxCreepsCount );
	saver.Add( "portal", &portal );
	saver.Add( "heroRanks", &heroRanks );
	saver.Add( "baseEmblemHeroNeeds", &baseEmblemHeroNeeds );
	saver.Add( "behaviourTrackerParams", &behaviourTrackerParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AILogicParameters::Assign( const AILogicParameters& _aILogicParameters )
{
	teamsNames = _aILogicParameters.teamsNames;
	chestGameObject = _aILogicParameters.chestGameObject;
	conditionFormulas = _aILogicParameters.conditionFormulas;
	globalConstants = _aILogicParameters.globalConstants;
	heroRespawnParams = _aILogicParameters.heroRespawnParams;
	heroAdvanceRespawnTime = _aILogicParameters.heroAdvanceRespawnTime;
	baseRedeemCost = _aILogicParameters.baseRedeemCost;
	redeemCostPerLevel = _aILogicParameters.redeemCostPerLevel;
	redeemCostrecalculateTime = _aILogicParameters.redeemCostrecalculateTime;
	followRange = _aILogicParameters.followRange;
	pickupItemRange = _aILogicParameters.pickupItemRange;
	killAwardPartyMultiplier = _aILogicParameters.killAwardPartyMultiplier;
	maxTrueSightRange = _aILogicParameters.maxTrueSightRange;
	channelingAbilityRangeMultiplier = _aILogicParameters.channelingAbilityRangeMultiplier;
	heroScreamDelay = _aILogicParameters.heroScreamDelay;
	globalCooldownTime = _aILogicParameters.globalCooldownTime;
	skeletonLifeTime = _aILogicParameters.skeletonLifeTime;
	glyphSettings.minNormalSpawnDelay = _aILogicParameters.glyphSettings.minNormalSpawnDelay;
	glyphSettings.maxNormalSpawnDelay = _aILogicParameters.glyphSettings.maxNormalSpawnDelay;
	glyphSettings.minAfterPickupSpawnDelay = _aILogicParameters.glyphSettings.minAfterPickupSpawnDelay;
	glyphSettings.maxAfterPickupSpawnDelay = _aILogicParameters.glyphSettings.maxAfterPickupSpawnDelay;
	glyphSettings.spawnAttemptDelayDecrease = _aILogicParameters.glyphSettings.spawnAttemptDelayDecrease;
	glyphSettings.maxInstances = _aILogicParameters.glyphSettings.maxInstances;
	glyphSettings.spawnMode = _aILogicParameters.glyphSettings.spawnMode;
	assistAccountTime = _aILogicParameters.assistAccountTime;
	killTimeIntervals.creepKillInterval = _aILogicParameters.killTimeIntervals.creepKillInterval;
	killTimeIntervals.buildingKillInterval = _aILogicParameters.killTimeIntervals.buildingKillInterval;
	killTimeIntervals.heroKillerDeadInterval = _aILogicParameters.killTimeIntervals.heroKillerDeadInterval;
	killTimeIntervals.heroKillDamageInterval = _aILogicParameters.killTimeIntervals.heroKillDamageInterval;
	creepsWavesDelay = _aILogicParameters.creepsWavesDelay;
	creepLevelCap = _aILogicParameters.creepLevelCap;
	creepsLevelUpInfo.interval = _aILogicParameters.creepsLevelUpInfo.interval;
	creepsLevelUpInfo.increment = _aILogicParameters.creepsLevelUpInfo.increment;
	quarterDestroyStatsMultipliers = _aILogicParameters.quarterDestroyStatsMultipliers;
	movingTimerBlock = _aILogicParameters.movingTimerBlock;
	creatureHappyStateParams.happyCreaturesPercent = _aILogicParameters.creatureHappyStateParams.happyCreaturesPercent;
	creatureHappyStateParams.minRestTime = _aILogicParameters.creatureHappyStateParams.minRestTime;
	creatureHappyStateParams.happyCheckTick = _aILogicParameters.creatureHappyStateParams.happyCheckTick;
	commonSummonParameters.primarySummonEscortDistance = _aILogicParameters.commonSummonParameters.primarySummonEscortDistance;
	commonSummonParameters.secondarySummonEscortDistance = _aILogicParameters.commonSummonParameters.secondarySummonEscortDistance;
	commonSummonParameters.petEscortDistance = _aILogicParameters.commonSummonParameters.petEscortDistance;
	rotationSpeed = _aILogicParameters.rotationSpeed;
	rotationSpeedZ = _aILogicParameters.rotationSpeedZ;
	towerTurretParams.turretAngleSpeed = _aILogicParameters.towerTurretParams.turretAngleSpeed;
	towerTurretParams.turretAngleAcceleration = _aILogicParameters.towerTurretParams.turretAngleAcceleration;
	towerTurretParams.turretRotaionTolerance = _aILogicParameters.towerTurretParams.turretRotaionTolerance;
	towerTurretParams.turretLastAngleResetDelay = _aILogicParameters.towerTurretParams.turretLastAngleResetDelay;
	mainBuildingTurretParams = _aILogicParameters.mainBuildingTurretParams;
	expandNatureSegmentRation = _aILogicParameters.expandNatureSegmentRation;
	expandNatureGlyphsLifeTime = _aILogicParameters.expandNatureGlyphsLifeTime;
	expandNatureGlyphsVisibilityRadius = _aILogicParameters.expandNatureGlyphsVisibilityRadius;
	expandNatureGlyphGameObject = _aILogicParameters.expandNatureGlyphGameObject;
	buildingsDenyAbility = _aILogicParameters.buildingsDenyAbility;
	buildingsDenyMinHealth = _aILogicParameters.buildingsDenyMinHealth;
	buildingsDenyExperiencePenalty = _aILogicParameters.buildingsDenyExperiencePenalty;
	buildingsDenyNaftaPenalty = _aILogicParameters.buildingsDenyNaftaPenalty;
	buildingsDenyNaftaSpecPenalty = _aILogicParameters.buildingsDenyNaftaSpecPenalty;
	buildingsDenyTeamNaftaPenalty = _aILogicParameters.buildingsDenyTeamNaftaPenalty;
	buildingsAbilityA = _aILogicParameters.buildingsAbilityA;
	buildingsAbilityB = _aILogicParameters.buildingsAbilityB;
	buildingsMinHealthExplosionPercent = _aILogicParameters.buildingsMinHealthExplosionPercent;
	buildingsFragEffectProbability = _aILogicParameters.buildingsFragEffectProbability;
	raiseFlagAbility = _aILogicParameters.raiseFlagAbility;
	talentsBuyRange = _aILogicParameters.talentsBuyRange;
	defaultTalentsSet = _aILogicParameters.defaultTalentsSet;
	talentBaseStatBudget = _aILogicParameters.talentBaseStatBudget;
	talentNaftaCostByLevel = _aILogicParameters.talentNaftaCostByLevel;
	talentVendorCostByRarity = _aILogicParameters.talentVendorCostByRarity;
	pauseSeconds = _aILogicParameters.pauseSeconds;
	derivativeStats = _aILogicParameters.derivativeStats;
	statsBudget = _aILogicParameters.statsBudget;
	forceParameters = _aILogicParameters.forceParameters;
	talentGroups = _aILogicParameters.talentGroups;
	consumableGroups = _aILogicParameters.consumableGroups;
	talentKits = _aILogicParameters.talentKits;
	talentPacks = _aILogicParameters.talentPacks;
	energyDamageReduction = _aILogicParameters.energyDamageReduction;
	physicalDamageReduction = _aILogicParameters.physicalDamageReduction;
	heroStatisticsParams.timeSlicePeriod = _aILogicParameters.heroStatisticsParams.timeSlicePeriod;
	expoModeParams.statsEnhancers = _aILogicParameters.expoModeParams.statsEnhancers;
	expoModeParams.minHeroLife = _aILogicParameters.expoModeParams.minHeroLife;
	expoModeParams.damageModifier = _aILogicParameters.expoModeParams.damageModifier;
	abilityAndDamageScalingParams.abilityScaleStatLeft = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleStatLeft;
	abilityAndDamageScalingParams.abilityScaleStatRight = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleStatRight;
	abilityAndDamageScalingParams.abilityScaleLifeLeft = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleLifeLeft;
	abilityAndDamageScalingParams.abilityScaleLifeRight = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleLifeRight;
	abilityAndDamageScalingParams.abilityScaleEnergyLeft = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleEnergyLeft;
	abilityAndDamageScalingParams.abilityScaleEnergyRight = _aILogicParameters.abilityAndDamageScalingParams.abilityScaleEnergyRight;
	abilityAndDamageScalingParams.damageScaleStatLeft = _aILogicParameters.abilityAndDamageScalingParams.damageScaleStatLeft;
	abilityAndDamageScalingParams.damageScaleStatRight = _aILogicParameters.abilityAndDamageScalingParams.damageScaleStatRight;
	abilityAndDamageScalingParams.damageScaleLifeLeft = _aILogicParameters.abilityAndDamageScalingParams.damageScaleLifeLeft;
	abilityAndDamageScalingParams.damageScaleLifeRight = _aILogicParameters.abilityAndDamageScalingParams.damageScaleLifeRight;
	abilityAndDamageScalingParams.damageScaleEnergyLeft = _aILogicParameters.abilityAndDamageScalingParams.damageScaleEnergyLeft;
	abilityAndDamageScalingParams.damageScaleEnergyRight = _aILogicParameters.abilityAndDamageScalingParams.damageScaleEnergyRight;
	levelToExperienceTable = _aILogicParameters.levelToExperienceTable;
	botsSettings = _aILogicParameters.botsSettings;
	warFogRemoveTime = _aILogicParameters.warFogRemoveTime;
	warFogRemoveRadius = _aILogicParameters.warFogRemoveRadius;
	maxCreepsCount = _aILogicParameters.maxCreepsCount;
	portal = _aILogicParameters.portal;
	heroRanks = _aILogicParameters.heroRanks;
	baseEmblemHeroNeeds = _aILogicParameters.baseEmblemHeroNeeds;
	behaviourTrackerParams = _aILogicParameters.behaviourTrackerParams;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BehaviourTrackerParams::BehaviourTrackerParams() :
		idleTime( 120 )
	, goodActionTimeout( 180 )
	, goodZumaActionTimeout( 300 )
	, feederDeathCount( 3 )
	, feederDeathTime( 240 )
	, badBehaviourComplaintsThreshold( 2 )
	, insultComplaintsThreshold( 2 )
	, autoMuteMinMessage( 0 )
	, autoMuteMessagePerTime( 3 )
	, autoMuteTimeLimit( 10 )
	, autoMuteMessageLength( 50 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BehaviourTrackerParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &idleTime );
	saver.Add( 3, &goodActionTimeout );
	saver.Add( 4, &goodZumaActionTimeout );
	saver.Add( 5, &feederDeathCount );
	saver.Add( 6, &feederDeathTime );
	saver.Add( 7, &badBehaviourComplaintsThreshold );
	saver.Add( 8, &insultComplaintsThreshold );
	saver.Add( 9, &autoMuteMinMessage );
	saver.Add( 10, &autoMuteMessagePerTime );
	saver.Add( 11, &autoMuteTimeLimit );
	saver.Add( 12, &autoMuteMessageLength );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BehaviourTrackerParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BehaviourTrackerParams* parentPtr = (BehaviourTrackerParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BehaviourTrackerParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "idleTime", &idleTime );
	saver.Add( "goodActionTimeout", &goodActionTimeout );
	saver.Add( "goodZumaActionTimeout", &goodZumaActionTimeout );
	saver.Add( "feederDeathCount", &feederDeathCount );
	saver.Add( "feederDeathTime", &feederDeathTime );
	saver.Add( "badBehaviourComplaintsThreshold", &badBehaviourComplaintsThreshold );
	saver.Add( "insultComplaintsThreshold", &insultComplaintsThreshold );
	saver.Add( "autoMuteMinMessage", &autoMuteMinMessage );
	saver.Add( "autoMuteMessagePerTime", &autoMuteMessagePerTime );
	saver.Add( "autoMuteTimeLimit", &autoMuteTimeLimit );
	saver.Add( "autoMuteMessageLength", &autoMuteMessageLength );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BehaviourTrackerParams::Assign( const BehaviourTrackerParams& _behaviourTrackerParams )
{
	idleTime = _behaviourTrackerParams.idleTime;
	goodActionTimeout = _behaviourTrackerParams.goodActionTimeout;
	goodZumaActionTimeout = _behaviourTrackerParams.goodZumaActionTimeout;
	feederDeathCount = _behaviourTrackerParams.feederDeathCount;
	feederDeathTime = _behaviourTrackerParams.feederDeathTime;
	badBehaviourComplaintsThreshold = _behaviourTrackerParams.badBehaviourComplaintsThreshold;
	insultComplaintsThreshold = _behaviourTrackerParams.insultComplaintsThreshold;
	autoMuteMinMessage = _behaviourTrackerParams.autoMuteMinMessage;
	autoMuteMessagePerTime = _behaviourTrackerParams.autoMuteMessagePerTime;
	autoMuteTimeLimit = _behaviourTrackerParams.autoMuteTimeLimit;
	autoMuteMessageLength = _behaviourTrackerParams.autoMuteMessageLength;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BotsSettings::BotsSettings() :
		manaUsePotionThreshold( 0.5f )
	, healthUsePotionThreshold( 0.5f )
	, minShoppingMoney( 100 )
	, maxHealthPotion( 2 )
	, maxManaPotion( 1 )
	, timeToGo( 45 )
	, midOnly( false )
	, enableBotsAI( true )
	, timeToTeleport( 180 )
	, healthFractionToRetreatToBase( 0.1f )
	, healthToRetreatToBase( 60.0f )
	, escapeTowerDistance( 20.0f )
	, healthFractionToMoveToFront( 0.8f )
	, forcedFollowRange( 20.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BotsSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &manaUsePotionThreshold );
	saver.Add( 3, &healthUsePotionThreshold );
	saver.Add( 4, &minShoppingMoney );
	saver.Add( 5, &maxHealthPotion );
	saver.Add( 6, &maxManaPotion );
	saver.Add( 7, &doNotBuyMana );
	saver.Add( 8, &timeToGo );
	saver.Add( 9, &midOnly );
	saver.Add( 10, &enableBotsAI );
	saver.Add( 11, &timeToTeleport );
	saver.Add( 12, &healthFractionToRetreatToBase );
	saver.Add( 13, &healthToRetreatToBase );
	saver.Add( 14, &escapeTowerDistance );
	saver.Add( 15, &healthFractionToMoveToFront );
	saver.Add( 16, &forcedFollowRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BotsSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BotsSettings* parentPtr = (BotsSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BotsSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "manaUsePotionThreshold", &manaUsePotionThreshold );
	saver.Add( "healthUsePotionThreshold", &healthUsePotionThreshold );
	saver.Add( "minShoppingMoney", &minShoppingMoney );
	saver.Add( "maxHealthPotion", &maxHealthPotion );
	saver.Add( "maxManaPotion", &maxManaPotion );
	saver.Add( "doNotBuyMana", &doNotBuyMana );
	saver.Add( "timeToGo", &timeToGo );
	saver.Add( "midOnly", &midOnly );
	saver.Add( "enableBotsAI", &enableBotsAI );
	saver.Add( "timeToTeleport", &timeToTeleport );
	saver.Add( "healthFractionToRetreatToBase", &healthFractionToRetreatToBase );
	saver.Add( "healthToRetreatToBase", &healthToRetreatToBase );
	saver.Add( "escapeTowerDistance", &escapeTowerDistance );
	saver.Add( "healthFractionToMoveToFront", &healthFractionToMoveToFront );
	saver.Add( "forcedFollowRange", &forcedFollowRange );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BotsSettings::Assign( const BotsSettings& _botsSettings )
{
	manaUsePotionThreshold = _botsSettings.manaUsePotionThreshold;
	healthUsePotionThreshold = _botsSettings.healthUsePotionThreshold;
	minShoppingMoney = _botsSettings.minShoppingMoney;
	maxHealthPotion = _botsSettings.maxHealthPotion;
	maxManaPotion = _botsSettings.maxManaPotion;
	doNotBuyMana = _botsSettings.doNotBuyMana;
	timeToGo = _botsSettings.timeToGo;
	midOnly = _botsSettings.midOnly;
	enableBotsAI = _botsSettings.enableBotsAI;
	timeToTeleport = _botsSettings.timeToTeleport;
	healthFractionToRetreatToBase = _botsSettings.healthFractionToRetreatToBase;
	healthToRetreatToBase = _botsSettings.healthToRetreatToBase;
	escapeTowerDistance = _botsSettings.escapeTowerDistance;
	healthFractionToMoveToFront = _botsSettings.healthFractionToMoveToFront;
	forcedFollowRange = _botsSettings.forcedFollowRange;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BuyServicesContainer::BuyServicesContainer()
{
	services.resize( 1 );
	buffs.resize( 11 );
	rewards.resize( 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServicesContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &services );
	saver.Add( 3, &buffs );
	saver.Add( 4, &rewards );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BuyServicesContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BuyServicesContainer* parentPtr = (BuyServicesContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuyServicesContainer::SerializeSelf( IXmlSaver &saver )
{
	services.resize( 1 );
	saver.Add( "services", &services );
	buffs.resize( 11 );
	saver.Add( "buffs", &buffs );
	rewards.resize( 1 );
	saver.Add( "rewards", &rewards );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BuyServicesContainer::Assign( const BuyServicesContainer& _buyServicesContainer )
{
	services = _buyServicesContainer.services;
	buffs = _buyServicesContainer.buffs;
	rewards = _buyServicesContainer.rewards;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChatLogicParameters::ChatLogicParameters() :
		timeBeforeDisappearing( 0 )
	, disappearingTime( 0 )
	, backgroundOpacityPermanent( 0.0f )
	, backgroundOpacityMotion( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChatLogicParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &timeBeforeDisappearing );
	saver.Add( 3, &disappearingTime );
	saver.Add( 4, &backgroundOpacityPermanent );
	saver.Add( 5, &backgroundOpacityMotion );
	saver.Add( 6, &channelStyle );
	saver.Add( 7, &nicknameStyle );
	saver.Add( 8, &messageStyle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChatLogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ChatLogicParameters* parentPtr = (ChatLogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChatLogicParameters::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "timeBeforeDisappearing", &timeBeforeDisappearing );
	saver.Add( "disappearingTime", &disappearingTime );
	saver.Add( "backgroundOpacityPermanent", &backgroundOpacityPermanent );
	saver.Add( "backgroundOpacityMotion", &backgroundOpacityMotion );
	saver.Add( "channelStyle", &channelStyle );
	saver.Add( "nicknameStyle", &nicknameStyle );
	saver.Add( "messageStyle", &messageStyle );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChatLogicParameters::Assign( const ChatLogicParameters& _chatLogicParameters )
{
	timeBeforeDisappearing = _chatLogicParameters.timeBeforeDisappearing;
	disappearingTime = _chatLogicParameters.disappearingTime;
	backgroundOpacityPermanent = _chatLogicParameters.backgroundOpacityPermanent;
	backgroundOpacityMotion = _chatLogicParameters.backgroundOpacityMotion;
	channelStyle = _chatLogicParameters.channelStyle;
	nicknameStyle = _chatLogicParameters.nicknameStyle;
	messageStyle = _chatLogicParameters.messageStyle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsumableGroupList::ConsumableGroupList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumableGroupList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &groups );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ConsumableGroupList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ConsumableGroupList* parentPtr = (ConsumableGroupList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsumableGroupList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "groups", &groups );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsumableGroupList::Assign( const ConsumableGroupList& _consumableGroupList )
{
	groups = _consumableGroupList.groups;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBGameMenu::DBGameMenu()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBGameMenu::operator&( IBinSaver &saver )
{
	saver.Add( 2, &menuItems );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBGameMenu::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBGameMenu* parentPtr = (DBGameMenu*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBGameMenu::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "menuItems", &menuItems );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBGameMenu::Assign( const DBGameMenu& _dBGameMenu )
{
	menuItems = _dBGameMenu.menuItems;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLevelToExperience::DBLevelToExperience()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLevelToExperience::operator&( IBinSaver &saver )
{
	saver.Add( 2, &Levels );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLevelToExperience::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBLevelToExperience* parentPtr = (DBLevelToExperience*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLevelToExperience::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "Levels", &Levels );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLevelToExperience::Assign( const DBLevelToExperience& _dBLevelToExperience )
{
	Levels = _dBLevelToExperience.Levels;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBRatingToFame::DBRatingToFame()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBRatingToFame::operator&( IBinSaver &saver )
{
	saver.Add( 2, &Ratings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBRatingToFame::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBRatingToFame* parentPtr = (DBRatingToFame*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBRatingToFame::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "Ratings", &Ratings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBRatingToFame::Assign( const DBRatingToFame& _dBRatingToFame )
{
	Ratings = _dBRatingToFame.Ratings;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ForceParameters::ForceParameters() :
		talentForceBonusPerStar( 5.0f )
	, classTalentForceBonusPerStar( 5.0f )
	, baseHeroForce( 0.0f )
	, defaultBaseForce( 100.0f )
	, masteryPointForce( 1.0f )
	, statBonusByForce( 1.27f )
	, defaultStatBonus( 252.0f )
	, teamForceCalcMethod( TEAMFORCECALCMETHOD_MINIMUM )
	, mapHabitantsStatsMultiplier( 0.55f )
	, trainingBotsStatsMultiplier( 0.6f )
	, talentForceModifier( 1.1f )
	, seriesMapHabitantsStatsMultiplier( 0.7f )
	, maxHeroForce( 0.0f )
{
	talentLevelForceModifiers.resize( 6, float() );
	talentRarityForceModifiers.resize( 7, float() );
	talentRarityForceSummand.resize( 7, float() );
	classTalentLevelForceModifiers.resize( 6, float() );
	talentLevelBonusPercent.resize( 6, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &talentLevelForceModifiers );
	saver.Add( 3, &talentRarityForceModifiers );
	saver.Add( 4, &talentRarityForceSummand );
	saver.Add( 5, &classTalentLevelForceModifiers );
	saver.Add( 6, &talentForceBonusPerStar );
	saver.Add( 7, &classTalentForceBonusPerStar );
	saver.Add( 8, &talentLevelBonusPercent );
	saver.Add( 9, &baseHeroForce );
	saver.Add( 10, &defaultBaseForce );
	saver.Add( 11, &masteryPointForce );
	saver.Add( 12, &statBonusByForce );
	saver.Add( 13, &defaultStatBonus );
	saver.Add( 14, &teamForceCalcMethod );
	saver.Add( 15, &mapHabitantsStatsMultiplier );
	saver.Add( 16, &trainingBotsStatsMultiplier );
	saver.Add( 17, &talentForceModifier );
	saver.Add( 18, &seriesMapHabitantsStatsMultiplier );
	saver.Add( 19, &maxHeroForce );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ForceParameters* parentPtr = (ForceParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForceParameters::SerializeSelf( IXmlSaver &saver )
{
	talentLevelForceModifiers.resize( 6 );
	saver.Add( "talentLevelForceModifiers", &talentLevelForceModifiers );
	talentRarityForceModifiers.resize( 7 );
	saver.Add( "talentRarityForceModifiers", &talentRarityForceModifiers );
	talentRarityForceSummand.resize( 7 );
	saver.Add( "talentRarityForceSummand", &talentRarityForceSummand );
	classTalentLevelForceModifiers.resize( 6 );
	saver.Add( "classTalentLevelForceModifiers", &classTalentLevelForceModifiers );
	saver.Add( "talentForceBonusPerStar", &talentForceBonusPerStar );
	saver.Add( "classTalentForceBonusPerStar", &classTalentForceBonusPerStar );
	talentLevelBonusPercent.resize( 6 );
	saver.Add( "talentLevelBonusPercent", &talentLevelBonusPercent );
	saver.Add( "baseHeroForce", &baseHeroForce );
	saver.Add( "defaultBaseForce", &defaultBaseForce );
	saver.Add( "masteryPointForce", &masteryPointForce );
	saver.Add( "statBonusByForce", &statBonusByForce );
	saver.Add( "defaultStatBonus", &defaultStatBonus );
	saver.Add( "teamForceCalcMethod", &teamForceCalcMethod );
	saver.Add( "mapHabitantsStatsMultiplier", &mapHabitantsStatsMultiplier );
	saver.Add( "trainingBotsStatsMultiplier", &trainingBotsStatsMultiplier );
	saver.Add( "talentForceModifier", &talentForceModifier );
	saver.Add( "seriesMapHabitantsStatsMultiplier", &seriesMapHabitantsStatsMultiplier );
	saver.Add( "maxHeroForce", &maxHeroForce );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForceParameters::Assign( const ForceParameters& _forceParameters )
{
	talentLevelForceModifiers = _forceParameters.talentLevelForceModifiers;
	talentRarityForceModifiers = _forceParameters.talentRarityForceModifiers;
	talentRarityForceSummand = _forceParameters.talentRarityForceSummand;
	classTalentLevelForceModifiers = _forceParameters.classTalentLevelForceModifiers;
	talentForceBonusPerStar = _forceParameters.talentForceBonusPerStar;
	classTalentForceBonusPerStar = _forceParameters.classTalentForceBonusPerStar;
	talentLevelBonusPercent = _forceParameters.talentLevelBonusPercent;
	baseHeroForce = _forceParameters.baseHeroForce;
	defaultBaseForce = _forceParameters.defaultBaseForce;
	masteryPointForce = _forceParameters.masteryPointForce;
	statBonusByForce = _forceParameters.statBonusByForce;
	defaultStatBonus = _forceParameters.defaultStatBonus;
	teamForceCalcMethod = _forceParameters.teamForceCalcMethod;
	mapHabitantsStatsMultiplier = _forceParameters.mapHabitantsStatsMultiplier;
	trainingBotsStatsMultiplier = _forceParameters.trainingBotsStatsMultiplier;
	talentForceModifier = _forceParameters.talentForceModifier;
	seriesMapHabitantsStatsMultiplier = _forceParameters.seriesMapHabitantsStatsMultiplier;
	maxHeroForce = _forceParameters.maxHeroForce;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroRespawnParams::HeroRespawnParams() :
		heroRespawnDelayMultiplier( 5.0f )
	, heroMinRespawnTime( 6.0f )
	, heroBaseRespawnTime( 5.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRespawnParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroRespawnDelayMultiplier );
	saver.Add( 3, &heroMinRespawnTime );
	saver.Add( 4, &heroBaseRespawnTime );
	saver.Add( 5, &overtimeRespawnParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRespawnParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroRespawnParams* parentPtr = (HeroRespawnParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRespawnParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "heroRespawnDelayMultiplier", &heroRespawnDelayMultiplier );
	saver.Add( "heroMinRespawnTime", &heroMinRespawnTime );
	saver.Add( "heroBaseRespawnTime", &heroBaseRespawnTime );
	saver.Add( "overtimeRespawnParams", &overtimeRespawnParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRespawnParams::Assign( const HeroRespawnParams& _heroRespawnParams )
{
	heroRespawnDelayMultiplier = _heroRespawnParams.heroRespawnDelayMultiplier;
	heroMinRespawnTime = _heroRespawnParams.heroMinRespawnTime;
	heroBaseRespawnTime = _heroRespawnParams.heroBaseRespawnTime;
	overtimeRespawnParams.overtime = _heroRespawnParams.overtimeRespawnParams.overtime;
	overtimeRespawnParams.respawnDelayForOvertime = _heroRespawnParams.overtimeRespawnParams.respawnDelayForOvertime;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigamesBasic::MinigamesBasic()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamesBasic::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinigamesBasic::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinigamesBasic* parentPtr = (MinigamesBasic*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesBasic::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigamesBasic::Assign( const MinigamesBasic& _minigamesBasic )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PF_Minigames::IMinigamesMain* MinigamesBasic::Construct() const
{
	return ( PF_Minigames::IMinigamesMain* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentGroupList::TalentGroupList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentGroupList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &groups );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentGroupList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentGroupList* parentPtr = (TalentGroupList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentGroupList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "groups", &groups );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentGroupList::Assign( const TalentGroupList& _talentGroupList )
{
	groups = _talentGroupList.groups;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentKitList::TalentKitList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentKitList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &kits );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentKitList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentKitList* parentPtr = (TalentKitList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentKitList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "kits", &kits );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentKitList::Assign( const TalentKitList& _talentKitList )
{
	kits = _talentKitList.kits;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentPackList::TalentPackList()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentPackList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &packs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentPackList::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentPackList* parentPtr = (TalentPackList*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentPackList::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "packs", &packs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentPackList::Assign( const TalentPackList& _talentPackList )
{
	packs = _talentPackList.packs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeamsColoringScheme::TeamsColoringScheme()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamsColoringScheme::operator&( IBinSaver &saver )
{
	saver.Add( 2, &teamA );
	saver.Add( 3, &teamB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamsColoringScheme::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TeamsColoringScheme* parentPtr = (TeamsColoringScheme*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeamsColoringScheme::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "teamA", &teamA );
	saver.Add( "teamB", &teamB );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TeamsColoringScheme::Assign( const TeamsColoringScheme& _teamsColoringScheme )
{
	teamA.teamColors = _teamsColoringScheme.teamA.teamColors;
	teamB.teamColors = _teamsColoringScheme.teamB.teamColors;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitDeathParameters::UnitDeathParameters() :
		fallOffset( 4.5f )
	, fallSpeed( 0.5f )
	, deathTime( 5.0f )
	, unsummonTime( 0.5f )
	, observeOffset( 5.0f )
	, effectOffset( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitDeathParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fallOffset );
	saver.Add( 3, &fallSpeed );
	saver.Add( 4, &deathTime );
	saver.Add( 5, &unsummonTime );
	saver.Add( 6, &observeOffset );
	saver.Add( 7, &effectOffset );
	saver.Add( 8, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitDeathParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitDeathParameters* parentPtr = (UnitDeathParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitDeathParameters::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "fallOffset", &fallOffset );
	saver.Add( "fallSpeed", &fallSpeed );
	saver.Add( "deathTime", &deathTime );
	saver.Add( "unsummonTime", &unsummonTime );
	saver.Add( "observeOffset", &observeOffset );
	saver.Add( "effectOffset", &effectOffset );
	saver.Add( "effect", &effect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitDeathParameters::Assign( const UnitDeathParameters& _unitDeathParameters )
{
	fallOffset = _unitDeathParameters.fallOffset;
	fallSpeed = _unitDeathParameters.fallSpeed;
	deathTime = _unitDeathParameters.deathTime;
	unsummonTime = _unitDeathParameters.unsummonTime;
	observeOffset = _unitDeathParameters.observeOffset;
	effectOffset = _unitDeathParameters.effectOffset;
	effect = _unitDeathParameters.effect;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitLogicParameters::UnitLogicParameters() :
		screamRange( 20.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitLogicParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &defaultStats );
	saver.Add( 3, &targetingPars );
	saver.Add( 4, &screamRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitLogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitLogicParameters* parentPtr = (UnitLogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitLogicParameters::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "defaultStats", &defaultStats );
	saver.Add( "targetingPars", &targetingPars );
	saver.Add( "screamRange", &screamRange );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitLogicParameters::Assign( const UnitLogicParameters& _unitLogicParameters )
{
	defaultStats = _unitLogicParameters.defaultStats;
	targetingPars = _unitLogicParameters.targetingPars;
	screamRange = _unitLogicParameters.screamRange;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitsLogicParameters::UnitsLogicParameters()
{
	unitParameters.resize( 22 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitsLogicParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &unitParameters );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitsLogicParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitsLogicParameters* parentPtr = (UnitsLogicParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitsLogicParameters::SerializeSelf( IXmlSaver &saver )
{
	unitParameters.resize( 22 );
	saver.Add( "unitParameters", &unitParameters );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitsLogicParameters::Assign( const UnitsLogicParameters& _unitsLogicParameters )
{
	unitParameters = _unitsLogicParameters.unitParameters;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitTargetingParameters::UnitTargetingParameters() :
		unitTypeTableWeight( 0.0f )
	, weightMaximumRangePersent( 0.0f )
	, rangeWeight( 0.0f )
	, attackerMeWeight( 0.5f )
	, attackerHeroTableWeight( 1.0f )
	, attackerHeroSummonWeight( 0.0f )
	, attackerTowerWeight( 8.0f )
	, attackerMasterWeight( 2.0f )
	, attackerAllyWeight( 0.2f )
	, currentTargetTableWeight( 1.0f )
	, targetRevisionTime( 7.0f )
	, healthWeight( 0.3f )
	, masterTargetWeight( 0.0f )
	, talentAttackWeight( 0.0f )
	, autoAttackWeight( 0.0f )
	, OutOfAggroWeight( 0.0f )
	, allyTargetWeight( 0.0f )
	, aggressiveNeutralWeight( 0.0f )
	, aggressiveNeutralAttackingHeroWeight( 0.0f )
	, maxTimeFromAttack( -1.0f )
	, targetingRange( 15.0f )
	, chaseRange( 30.0f )
	, aggroRange( -1.0f )
	, ignoreSiblingTarget( false )
	, isStationarySummon( false )
	, onlyAutoTargeting( false )
	, attackerNearbyHeroWeight( 0.0f )
	, nearbyRange( 0.0f )
	, longSuspendTimeout( 0.3f )
	, sortSuspendTimeout( 0.0f )
{
	unitTargetWeight.resize( 22, float() );
	attackerHeroWeight.resize( 22, float() );
	currentTargetWeight.resize( 22, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitTargetingParameters::operator&( IBinSaver &saver )
{
	saver.Add( 2, &unitTargetWeight );
	saver.Add( 3, &unitTypeTableWeight );
	saver.Add( 4, &weightMaximumRangePersent );
	saver.Add( 5, &rangeWeight );
	saver.Add( 6, &attackerMeWeight );
	saver.Add( 7, &attackerHeroWeight );
	saver.Add( 8, &attackerHeroTableWeight );
	saver.Add( 9, &attackerHeroSummonWeight );
	saver.Add( 10, &attackerTowerWeight );
	saver.Add( 11, &attackerMasterWeight );
	saver.Add( 12, &attackerAllyWeight );
	saver.Add( 13, &currentTargetWeight );
	saver.Add( 14, &currentTargetTableWeight );
	saver.Add( 15, &targetRevisionTime );
	saver.Add( 16, &healthWeight );
	saver.Add( 17, &masterTargetWeight );
	saver.Add( 18, &talentAttackWeight );
	saver.Add( 19, &autoAttackWeight );
	saver.Add( 20, &OutOfAggroWeight );
	saver.Add( 21, &allyTargetWeight );
	saver.Add( 22, &aggressiveNeutralWeight );
	saver.Add( 23, &aggressiveNeutralAttackingHeroWeight );
	saver.Add( 24, &customWeight );
	saver.Add( 25, &maxTimeFromAttack );
	saver.Add( 26, &targetingRange );
	saver.Add( 27, &chaseRange );
	saver.Add( 28, &aggroRange );
	saver.Add( 29, &ignoreSiblingTarget );
	saver.Add( 30, &isStationarySummon );
	saver.Add( 31, &onlyAutoTargeting );
	saver.Add( 32, &attackerNearbyHeroWeight );
	saver.Add( 33, &nearbyRange );
	saver.Add( 34, &longSuspendTimeout );
	saver.Add( 35, &sortSuspendTimeout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitTargetingParameters::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UnitTargetingParameters* parentPtr = (UnitTargetingParameters*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitTargetingParameters::SerializeSelf( IXmlSaver &saver )
{
	unitTargetWeight.resize( 22 );
	saver.Add( "unitTargetWeight", &unitTargetWeight );
	saver.Add( "unitTypeTableWeight", &unitTypeTableWeight );
	saver.Add( "weightMaximumRangePersent", &weightMaximumRangePersent );
	saver.Add( "rangeWeight", &rangeWeight );
	saver.Add( "attackerMeWeight", &attackerMeWeight );
	attackerHeroWeight.resize( 22 );
	saver.Add( "attackerHeroWeight", &attackerHeroWeight );
	saver.Add( "attackerHeroTableWeight", &attackerHeroTableWeight );
	saver.Add( "attackerHeroSummonWeight", &attackerHeroSummonWeight );
	saver.Add( "attackerTowerWeight", &attackerTowerWeight );
	saver.Add( "attackerMasterWeight", &attackerMasterWeight );
	saver.Add( "attackerAllyWeight", &attackerAllyWeight );
	currentTargetWeight.resize( 22 );
	saver.Add( "currentTargetWeight", &currentTargetWeight );
	saver.Add( "currentTargetTableWeight", &currentTargetTableWeight );
	saver.Add( "targetRevisionTime", &targetRevisionTime );
	saver.Add( "healthWeight", &healthWeight );
	saver.Add( "masterTargetWeight", &masterTargetWeight );
	saver.Add( "talentAttackWeight", &talentAttackWeight );
	saver.Add( "autoAttackWeight", &autoAttackWeight );
	saver.Add( "OutOfAggroWeight", &OutOfAggroWeight );
	saver.Add( "allyTargetWeight", &allyTargetWeight );
	saver.Add( "aggressiveNeutralWeight", &aggressiveNeutralWeight );
	saver.Add( "aggressiveNeutralAttackingHeroWeight", &aggressiveNeutralAttackingHeroWeight );
	saver.Add( "customWeight", &customWeight );
	saver.Add( "maxTimeFromAttack", &maxTimeFromAttack );
	saver.Add( "targetingRange", &targetingRange );
	saver.Add( "chaseRange", &chaseRange );
	saver.Add( "aggroRange", &aggroRange );
	saver.Add( "ignoreSiblingTarget", &ignoreSiblingTarget );
	saver.Add( "isStationarySummon", &isStationarySummon );
	saver.Add( "onlyAutoTargeting", &onlyAutoTargeting );
	saver.Add( "attackerNearbyHeroWeight", &attackerNearbyHeroWeight );
	saver.Add( "nearbyRange", &nearbyRange );
	saver.Add( "longSuspendTimeout", &longSuspendTimeout );
	saver.Add( "sortSuspendTimeout", &sortSuspendTimeout );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitTargetingParameters::Assign( const UnitTargetingParameters& _unitTargetingParameters )
{
	unitTargetWeight = _unitTargetingParameters.unitTargetWeight;
	unitTypeTableWeight = _unitTargetingParameters.unitTypeTableWeight;
	weightMaximumRangePersent = _unitTargetingParameters.weightMaximumRangePersent;
	rangeWeight = _unitTargetingParameters.rangeWeight;
	attackerMeWeight = _unitTargetingParameters.attackerMeWeight;
	attackerHeroWeight = _unitTargetingParameters.attackerHeroWeight;
	attackerHeroTableWeight = _unitTargetingParameters.attackerHeroTableWeight;
	attackerHeroSummonWeight = _unitTargetingParameters.attackerHeroSummonWeight;
	attackerTowerWeight = _unitTargetingParameters.attackerTowerWeight;
	attackerMasterWeight = _unitTargetingParameters.attackerMasterWeight;
	attackerAllyWeight = _unitTargetingParameters.attackerAllyWeight;
	currentTargetWeight = _unitTargetingParameters.currentTargetWeight;
	currentTargetTableWeight = _unitTargetingParameters.currentTargetTableWeight;
	targetRevisionTime = _unitTargetingParameters.targetRevisionTime;
	healthWeight = _unitTargetingParameters.healthWeight;
	masterTargetWeight = _unitTargetingParameters.masterTargetWeight;
	talentAttackWeight = _unitTargetingParameters.talentAttackWeight;
	autoAttackWeight = _unitTargetingParameters.autoAttackWeight;
	OutOfAggroWeight = _unitTargetingParameters.OutOfAggroWeight;
	allyTargetWeight = _unitTargetingParameters.allyTargetWeight;
	aggressiveNeutralWeight = _unitTargetingParameters.aggressiveNeutralWeight;
	aggressiveNeutralAttackingHeroWeight = _unitTargetingParameters.aggressiveNeutralAttackingHeroWeight;
	customWeight = _unitTargetingParameters.customWeight;
	maxTimeFromAttack = _unitTargetingParameters.maxTimeFromAttack;
	targetingRange = _unitTargetingParameters.targetingRange;
	chaseRange = _unitTargetingParameters.chaseRange;
	aggroRange = _unitTargetingParameters.aggroRange;
	ignoreSiblingTarget = _unitTargetingParameters.ignoreSiblingTarget;
	isStationarySummon = _unitTargetingParameters.isStationarySummon;
	onlyAutoTargeting = _unitTargetingParameters.onlyAutoTargeting;
	attackerNearbyHeroWeight = _unitTargetingParameters.attackerNearbyHeroWeight;
	nearbyRange = _unitTargetingParameters.nearbyRange;
	longSuspendTimeout = _unitTargetingParameters.longSuspendTimeout;
	sortSuspendTimeout = _unitTargetingParameters.sortSuspendTimeout;
}
}; // namespace NDb
