// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBSmartChat.h"
#include "../PF_GameLogic/DBResources.h"
#include "../UI/DBUI.h"
#include "../Render/DBRender.h"
#include "DBStats.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_DBRESOURCE( AchievBase );
BASIC_REGISTER_DBRESOURCE( AchievRuler );
REGISTER_DBRESOURCE( AchievAvenge );
BASIC_REGISTER_DBRESOURCE( AchievStreak );
REGISTER_DBRESOURCE( AchievBaseStrike );
REGISTER_DBRESOURCE( AchievBorderGuard );
REGISTER_DBRESOURCE( AchievBossSlayer );
REGISTER_DBRESOURCE( AchievCeremonialKill );
REGISTER_DBRESOURCE( AchievChase );
REGISTER_DBRESOURCE( AchievCleanUpCreeps );
REGISTER_DBRESOURCE( AchievClearWay );
REGISTER_DBRESOURCE( AchievCraftWoman );
REGISTER_DBRESOURCE( AchievDemolishingSpree );
REGISTER_DBRESOURCE( AchievDominate );
REGISTER_DBRESOURCE( AchievDoubleAssist );
REGISTER_DBRESOURCE( AchievDoubleKill );
REGISTER_DBRESOURCE( AchievDragonSlayer );
REGISTER_DBRESOURCE( AchievDuel );
REGISTER_DBRESOURCE( AchievFirstAssault );
REGISTER_DBRESOURCE( AchievFirstBlood );
REGISTER_DBRESOURCE( AchievFirstMinigameComplete );
REGISTER_DBRESOURCE( AchievForestHunter );
REGISTER_DBRESOURCE( AchievGoldRite );
REGISTER_DBRESOURCE( AchievKillingSpree );
REGISTER_DBRESOURCE( AchievKittySlayer );
REGISTER_DBRESOURCE( AchievLegend );
REGISTER_DBRESOURCE( AchievMassAssist );
REGISTER_DBRESOURCE( AchievMassKill );
REGISTER_DBRESOURCE( AchievMasterControl );
REGISTER_DBRESOURCE( AchievNecklaceOfGlory );
REGISTER_DBRESOURCE( AchievAssistingSpree );
REGISTER_DBRESOURCE( AchievSaviour );
REGISTER_DBRESOURCE( AchievSessionDuration );
REGISTER_DBRESOURCE( AchievAscension );
REGISTER_DBRESOURCE( AchievTowerDeny );
REGISTER_DBRESOURCE( AchievVandalism );
REGISTER_DBRESOURCE( AchievVendetta );
REGISTER_DBRESOURCE( AchievWarLord );
REGISTER_DBRESOURCE( Actor );
REGISTER_DBRESOURCE( AdventureCameraSettings );
REGISTER_DBRESOURCE( AdventureTooltipParams );
REGISTER_DBRESOURCE( AdventureTooltipSettings );
REGISTER_DBRESOURCE( AdvMapModeDescription );
REGISTER_DBRESOURCE( BindCategory );
REGISTER_DBRESOURCE( CustomFlag );
REGISTER_DBRESOURCE( DBMinimap );
REGISTER_DBRESOURCE( DBStatisticData );
REGISTER_DBRESOURCE( DBTooltip );
REGISTER_DBRESOURCE( DBUIData );
REGISTER_DBRESOURCE( DerivativeStatsContainer );
REGISTER_DBRESOURCE( Dialog );
REGISTER_DBRESOURCE( DialogsCollection );
REGISTER_DBRESOURCE( FactionScoringTable );
BASIC_REGISTER_DBRESOURCE( FakeObj );
REGISTER_DBRESOURCE( HeroScoringTable );
REGISTER_DBRESOURCE( HintsCollection );
REGISTER_DBRESOURCE( MinimapImages );
REGISTER_DBRESOURCE( PFTerrainTypeInfo );
REGISTER_DBRESOURCE( PFUIGameLogicRoot );
REGISTER_DBRESOURCE( ScoringTable );
REGISTER_DBRESOURCE( SessionQuestsCollection );
REGISTER_DBRESOURCE( StatsBudgetContainer );
REGISTER_DBRESOURCE( StatsContainer );
REGISTER_DBRESOURCE( StatsEnhancersContainer );
REGISTER_DBRESOURCE( UIEvent );
REGISTER_DBRESOURCE( UIEventsCustom );
BASIC_REGISTER_DBRESOURCE( UISign );
REGISTER_DBRESOURCE( UISignAnnouncement );
REGISTER_DBRESOURCE( UISignFlyOffText );
REGISTER_DBRESOURCE( UISignMessageToChat );
REGISTER_DBRESOURCE( UISignMessageToStatusLine );
REGISTER_DBRESOURCE( UISignPlaySound );
REGISTER_DBRESOURCE( UITeamInfoParams );
REGISTER_DBRESOURCE( WebTowerCameraSettings );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#include "PFAchievement.h"
#include "PFUIEvent.h"

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BasicResourceType value )
{
	switch( value )
	{
		case BASICRESOURCETYPE_NONE:
			return "None";
		case BASICRESOURCETYPE_GOLD:
			return "Gold";
		case BASICRESOURCETYPE_SILVER:
			return "Silver";
		case BASICRESOURCETYPE_CRYSTAL:
			return "Crystal";
		case BASICRESOURCETYPE_REDCRYSTAL:
			return "RedCrystal";
		case BASICRESOURCETYPE_RESOURCE1:
			return "Resource1";
		case BASICRESOURCETYPE_RESOURCE2:
			return "Resource2";
		case BASICRESOURCETYPE_RESOURCE3:
			return "Resource3";
		case BASICRESOURCETYPE_POPULATION:
			return "Population";
		case BASICRESOURCETYPE_CLANWARPOINTS:
			return "ClanWarPoints";
		case BASICRESOURCETYPE_PLAYERWARPOINTS:
			return "PlayerWarPoints";
		case BASICRESOURCETYPE_SHARD:
			return "Shard";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BasicResourceType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BasicResourceType StringToEnum_BasicResourceType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BasicResourceType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "BASICRESOURCETYPE_NONE" ) == 0 )
		return BASICRESOURCETYPE_NONE;
	if ( strcmp( value, "Gold" ) == 0 || strcmp( value, "BASICRESOURCETYPE_GOLD" ) == 0 )
		return BASICRESOURCETYPE_GOLD;
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "BASICRESOURCETYPE_SILVER" ) == 0 )
		return BASICRESOURCETYPE_SILVER;
	if ( strcmp( value, "Crystal" ) == 0 || strcmp( value, "BASICRESOURCETYPE_CRYSTAL" ) == 0 )
		return BASICRESOURCETYPE_CRYSTAL;
	if ( strcmp( value, "RedCrystal" ) == 0 || strcmp( value, "BASICRESOURCETYPE_REDCRYSTAL" ) == 0 )
		return BASICRESOURCETYPE_REDCRYSTAL;
	if ( strcmp( value, "Resource1" ) == 0 || strcmp( value, "BASICRESOURCETYPE_RESOURCE1" ) == 0 )
		return BASICRESOURCETYPE_RESOURCE1;
	if ( strcmp( value, "Resource2" ) == 0 || strcmp( value, "BASICRESOURCETYPE_RESOURCE2" ) == 0 )
		return BASICRESOURCETYPE_RESOURCE2;
	if ( strcmp( value, "Resource3" ) == 0 || strcmp( value, "BASICRESOURCETYPE_RESOURCE3" ) == 0 )
		return BASICRESOURCETYPE_RESOURCE3;
	if ( strcmp( value, "Population" ) == 0 || strcmp( value, "BASICRESOURCETYPE_POPULATION" ) == 0 )
		return BASICRESOURCETYPE_POPULATION;
	if ( strcmp( value, "ClanWarPoints" ) == 0 || strcmp( value, "BASICRESOURCETYPE_CLANWARPOINTS" ) == 0 )
		return BASICRESOURCETYPE_CLANWARPOINTS;
	if ( strcmp( value, "PlayerWarPoints" ) == 0 || strcmp( value, "BASICRESOURCETYPE_PLAYERWARPOINTS" ) == 0 )
		return BASICRESOURCETYPE_PLAYERWARPOINTS;
	if ( strcmp( value, "Shard" ) == 0 || strcmp( value, "BASICRESOURCETYPE_SHARD" ) == 0 )
		return BASICRESOURCETYPE_SHARD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BasicResourceType", value ) );
	return BASICRESOURCETYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAchievementType value )
{
	switch( value )
	{
		case ACHIEVEMENTTYPE_FIRSTBLOOD:
			return "FirstBlood";
		case ACHIEVEMENTTYPE_DOUBLEKILL:
			return "DoubleKill";
		case ACHIEVEMENTTYPE_MASSKILL:
			return "MassKill";
		case ACHIEVEMENTTYPE_DUEL:
			return "Duel";
		case ACHIEVEMENTTYPE_CHASE:
			return "Chase";
		case ACHIEVEMENTTYPE_AVENGE:
			return "Avenge";
		case ACHIEVEMENTTYPE_DOMINATE:
			return "Dominate";
		case ACHIEVEMENTTYPE_VENDETTA:
			return "Vendetta";
		case ACHIEVEMENTTYPE_CEREMONIALKILL:
			return "CeremonialKill";
		case ACHIEVEMENTTYPE_KILLINGSPREE:
			return "KillingSpree";
		case ACHIEVEMENTTYPE_DOUBLEASSIST:
			return "DoubleAssist";
		case ACHIEVEMENTTYPE_MASSASSIST:
			return "MassAssist";
		case ACHIEVEMENTTYPE_SAVIOUR:
			return "Saviour";
		case ACHIEVEMENTTYPE_MASTERCONTROL:
			return "MasterControl";
		case ACHIEVEMENTTYPE_ASSISTINGSPREE:
			return "AssistingSpree";
		case ACHIEVEMENTTYPE_BORDERGUARD:
			return "BorderGuard";
		case ACHIEVEMENTTYPE_FIRSTASSAULT:
			return "FirstAssault";
		case ACHIEVEMENTTYPE_DEMOLISHINGSPREE:
			return "DemolishingSpree";
		case ACHIEVEMENTTYPE_TOWERDENY:
			return "TowerDeny";
		case ACHIEVEMENTTYPE_CLEARWAY:
			return "ClearWay";
		case ACHIEVEMENTTYPE_BASESTRIKE:
			return "BaseStrike";
		case ACHIEVEMENTTYPE_VANDALISM:
			return "Vandalism";
		case ACHIEVEMENTTYPE_WARLORD:
			return "WarLord";
		case ACHIEVEMENTTYPE_CLEANUPCREEPS:
			return "CleanUpCreeps";
		case ACHIEVEMENTTYPE_DRAGONSLAYER:
			return "DragonSlayer";
		case ACHIEVEMENTTYPE_KITTYSLAYER:
			return "KittySlayer";
		case ACHIEVEMENTTYPE_LEGEND:
			return "Legend";
		case ACHIEVEMENTTYPE_FORESTHUNTER:
			return "ForestHunter";
		case ACHIEVEMENTTYPE_ASCENSION:
			return "Ascension";
		case ACHIEVEMENTTYPE_SLIVERRITE:
			return "SliverRite";
		case ACHIEVEMENTTYPE_GOLDRITE:
			return "GoldRite";
		case ACHIEVEMENTTYPE_FIRSTMINIGAMECOMPLETE:
			return "FirstMinigameComplete";
		case ACHIEVEMENTTYPE_SESSIONDURATION:
			return "SessionDuration";
		case ACHIEVEMENTTYPE_BOSSSLAYER:
			return "BossSlayer";
		case ACHIEVEMENTTYPE_INVALIDACHIVEMENT:
			return "InvalidAchivement";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAchievementType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAchievementType StringToEnum_EAchievementType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAchievementType)(NStr::ToInt( value ));
	if ( strcmp( value, "FirstBlood" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_FIRSTBLOOD" ) == 0 )
		return ACHIEVEMENTTYPE_FIRSTBLOOD;
	if ( strcmp( value, "DoubleKill" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DOUBLEKILL" ) == 0 )
		return ACHIEVEMENTTYPE_DOUBLEKILL;
	if ( strcmp( value, "MassKill" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_MASSKILL" ) == 0 )
		return ACHIEVEMENTTYPE_MASSKILL;
	if ( strcmp( value, "Duel" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DUEL" ) == 0 )
		return ACHIEVEMENTTYPE_DUEL;
	if ( strcmp( value, "Chase" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_CHASE" ) == 0 )
		return ACHIEVEMENTTYPE_CHASE;
	if ( strcmp( value, "Avenge" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_AVENGE" ) == 0 )
		return ACHIEVEMENTTYPE_AVENGE;
	if ( strcmp( value, "Dominate" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DOMINATE" ) == 0 )
		return ACHIEVEMENTTYPE_DOMINATE;
	if ( strcmp( value, "Vendetta" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_VENDETTA" ) == 0 )
		return ACHIEVEMENTTYPE_VENDETTA;
	if ( strcmp( value, "CeremonialKill" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_CEREMONIALKILL" ) == 0 )
		return ACHIEVEMENTTYPE_CEREMONIALKILL;
	if ( strcmp( value, "KillingSpree" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_KILLINGSPREE" ) == 0 )
		return ACHIEVEMENTTYPE_KILLINGSPREE;
	if ( strcmp( value, "DoubleAssist" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DOUBLEASSIST" ) == 0 )
		return ACHIEVEMENTTYPE_DOUBLEASSIST;
	if ( strcmp( value, "MassAssist" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_MASSASSIST" ) == 0 )
		return ACHIEVEMENTTYPE_MASSASSIST;
	if ( strcmp( value, "Saviour" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_SAVIOUR" ) == 0 )
		return ACHIEVEMENTTYPE_SAVIOUR;
	if ( strcmp( value, "MasterControl" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_MASTERCONTROL" ) == 0 )
		return ACHIEVEMENTTYPE_MASTERCONTROL;
	if ( strcmp( value, "AssistingSpree" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_ASSISTINGSPREE" ) == 0 )
		return ACHIEVEMENTTYPE_ASSISTINGSPREE;
	if ( strcmp( value, "BorderGuard" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_BORDERGUARD" ) == 0 )
		return ACHIEVEMENTTYPE_BORDERGUARD;
	if ( strcmp( value, "FirstAssault" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_FIRSTASSAULT" ) == 0 )
		return ACHIEVEMENTTYPE_FIRSTASSAULT;
	if ( strcmp( value, "DemolishingSpree" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DEMOLISHINGSPREE" ) == 0 )
		return ACHIEVEMENTTYPE_DEMOLISHINGSPREE;
	if ( strcmp( value, "TowerDeny" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_TOWERDENY" ) == 0 )
		return ACHIEVEMENTTYPE_TOWERDENY;
	if ( strcmp( value, "ClearWay" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_CLEARWAY" ) == 0 )
		return ACHIEVEMENTTYPE_CLEARWAY;
	if ( strcmp( value, "BaseStrike" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_BASESTRIKE" ) == 0 )
		return ACHIEVEMENTTYPE_BASESTRIKE;
	if ( strcmp( value, "Vandalism" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_VANDALISM" ) == 0 )
		return ACHIEVEMENTTYPE_VANDALISM;
	if ( strcmp( value, "WarLord" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_WARLORD" ) == 0 )
		return ACHIEVEMENTTYPE_WARLORD;
	if ( strcmp( value, "CleanUpCreeps" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_CLEANUPCREEPS" ) == 0 )
		return ACHIEVEMENTTYPE_CLEANUPCREEPS;
	if ( strcmp( value, "DragonSlayer" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_DRAGONSLAYER" ) == 0 )
		return ACHIEVEMENTTYPE_DRAGONSLAYER;
	if ( strcmp( value, "KittySlayer" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_KITTYSLAYER" ) == 0 )
		return ACHIEVEMENTTYPE_KITTYSLAYER;
	if ( strcmp( value, "Legend" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_LEGEND" ) == 0 )
		return ACHIEVEMENTTYPE_LEGEND;
	if ( strcmp( value, "ForestHunter" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_FORESTHUNTER" ) == 0 )
		return ACHIEVEMENTTYPE_FORESTHUNTER;
	if ( strcmp( value, "Ascension" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_ASCENSION" ) == 0 )
		return ACHIEVEMENTTYPE_ASCENSION;
	if ( strcmp( value, "SliverRite" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_SLIVERRITE" ) == 0 )
		return ACHIEVEMENTTYPE_SLIVERRITE;
	if ( strcmp( value, "GoldRite" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_GOLDRITE" ) == 0 )
		return ACHIEVEMENTTYPE_GOLDRITE;
	if ( strcmp( value, "FirstMinigameComplete" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_FIRSTMINIGAMECOMPLETE" ) == 0 )
		return ACHIEVEMENTTYPE_FIRSTMINIGAMECOMPLETE;
	if ( strcmp( value, "SessionDuration" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_SESSIONDURATION" ) == 0 )
		return ACHIEVEMENTTYPE_SESSIONDURATION;
	if ( strcmp( value, "BossSlayer" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_BOSSSLAYER" ) == 0 )
		return ACHIEVEMENTTYPE_BOSSSLAYER;
	if ( strcmp( value, "InvalidAchivement" ) == 0 || strcmp( value, "ACHIEVEMENTTYPE_INVALIDACHIVEMENT" ) == 0 )
		return ACHIEVEMENTTYPE_INVALIDACHIVEMENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAchievementType", value ) );
	return ACHIEVEMENTTYPE_FIRSTBLOOD;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAdventureTooltipStretchMode value )
{
	switch( value )
	{
		case ADVENTURETOOLTIPSTRETCHMODE_NONE:
			return "None";
		case ADVENTURETOOLTIPSTRETCHMODE_DYNAMIC:
			return "Dynamic";
		case ADVENTURETOOLTIPSTRETCHMODE_STATIC:
			return "Static";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAdventureTooltipStretchMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAdventureTooltipStretchMode StringToEnum_EAdventureTooltipStretchMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAdventureTooltipStretchMode)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ADVENTURETOOLTIPSTRETCHMODE_NONE" ) == 0 )
		return ADVENTURETOOLTIPSTRETCHMODE_NONE;
	if ( strcmp( value, "Dynamic" ) == 0 || strcmp( value, "ADVENTURETOOLTIPSTRETCHMODE_DYNAMIC" ) == 0 )
		return ADVENTURETOOLTIPSTRETCHMODE_DYNAMIC;
	if ( strcmp( value, "Static" ) == 0 || strcmp( value, "ADVENTURETOOLTIPSTRETCHMODE_STATIC" ) == 0 )
		return ADVENTURETOOLTIPSTRETCHMODE_STATIC;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAdventureTooltipStretchMode", value ) );
	return ADVENTURETOOLTIPSTRETCHMODE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnnouncementType value )
{
	switch( value )
	{
		case ANNOUNCEMENTTYPE_PLAYERKILLED:
			return "PlayerKilled";
		case ANNOUNCEMENTTYPE_ACHIEVMENT:
			return "Achievment";
		case ANNOUNCEMENTTYPE_TOWERDESTROYED:
			return "TowerDestroyed";
		case ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS:
			return "SpawnSuperCreeps";
		case ANNOUNCEMENTTYPE_PLAYERLEFT:
			return "PlayerLeft";
		case ANNOUNCEMENTTYPE_PLAYERRECONNECTED:
			return "PlayerReconnected";
		case ANNOUNCEMENTTYPE_QUESTRECIEVED:
			return "QuestRecieved";
		case ANNOUNCEMENTTYPE_QUESTCOMPLETE:
			return "QuestComplete";
		case ANNOUNCEMENTTYPE_EGGANNOUNCEMENT:
			return "EggAnnouncement";
		case ANNOUNCEMENTTYPE_SUPERSIEGESPAWNED:
			return "SuperSiegeSpawned";
		case ANNOUNCEMENTTYPE_CUSTOMANNOUNCEMENT:
			return "CustomAnnouncement";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnnouncementType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnnouncementType StringToEnum_EAnnouncementType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnnouncementType)(NStr::ToInt( value ));
	if ( strcmp( value, "PlayerKilled" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_PLAYERKILLED" ) == 0 )
		return ANNOUNCEMENTTYPE_PLAYERKILLED;
	if ( strcmp( value, "Achievment" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_ACHIEVMENT" ) == 0 )
		return ANNOUNCEMENTTYPE_ACHIEVMENT;
	if ( strcmp( value, "TowerDestroyed" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_TOWERDESTROYED" ) == 0 )
		return ANNOUNCEMENTTYPE_TOWERDESTROYED;
	if ( strcmp( value, "SpawnSuperCreeps" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS" ) == 0 )
		return ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS;
	if ( strcmp( value, "PlayerLeft" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_PLAYERLEFT" ) == 0 )
		return ANNOUNCEMENTTYPE_PLAYERLEFT;
	if ( strcmp( value, "PlayerReconnected" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_PLAYERRECONNECTED" ) == 0 )
		return ANNOUNCEMENTTYPE_PLAYERRECONNECTED;
	if ( strcmp( value, "QuestRecieved" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_QUESTRECIEVED" ) == 0 )
		return ANNOUNCEMENTTYPE_QUESTRECIEVED;
	if ( strcmp( value, "QuestComplete" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_QUESTCOMPLETE" ) == 0 )
		return ANNOUNCEMENTTYPE_QUESTCOMPLETE;
	if ( strcmp( value, "EggAnnouncement" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_EGGANNOUNCEMENT" ) == 0 )
		return ANNOUNCEMENTTYPE_EGGANNOUNCEMENT;
	if ( strcmp( value, "SuperSiegeSpawned" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_SUPERSIEGESPAWNED" ) == 0 )
		return ANNOUNCEMENTTYPE_SUPERSIEGESPAWNED;
	if ( strcmp( value, "CustomAnnouncement" ) == 0 || strcmp( value, "ANNOUNCEMENTTYPE_CUSTOMANNOUNCEMENT" ) == 0 )
		return ANNOUNCEMENTTYPE_CUSTOMANNOUNCEMENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnnouncementType", value ) );
	return ANNOUNCEMENTTYPE_PLAYERKILLED;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBossSlayerAchievMode value )
{
	switch( value )
	{
		case BOSSSLAYERACHIEVMODE_ONLYFORKILLER:
			return "OnlyForKiller";
		case BOSSSLAYERACHIEVMODE_FORKILLERANDASSISTER:
			return "ForKillerAndAssister";
		case BOSSSLAYERACHIEVMODE_FORALLTEAMMATES:
			return "ForAllTeammates";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBossSlayerAchievMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBossSlayerAchievMode StringToEnum_EBossSlayerAchievMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBossSlayerAchievMode)(NStr::ToInt( value ));
	if ( strcmp( value, "OnlyForKiller" ) == 0 || strcmp( value, "BOSSSLAYERACHIEVMODE_ONLYFORKILLER" ) == 0 )
		return BOSSSLAYERACHIEVMODE_ONLYFORKILLER;
	if ( strcmp( value, "ForKillerAndAssister" ) == 0 || strcmp( value, "BOSSSLAYERACHIEVMODE_FORKILLERANDASSISTER" ) == 0 )
		return BOSSSLAYERACHIEVMODE_FORKILLERANDASSISTER;
	if ( strcmp( value, "ForAllTeammates" ) == 0 || strcmp( value, "BOSSSLAYERACHIEVMODE_FORALLTEAMMATES" ) == 0 )
		return BOSSSLAYERACHIEVMODE_FORALLTEAMMATES;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBossSlayerAchievMode", value ) );
	return BOSSSLAYERACHIEVMODE_ONLYFORKILLER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EChatChannel value )
{
	switch( value )
	{
		case CHATCHANNEL_GLOBAL:
			return "Global";
		case CHATCHANNEL_MYTEAM:
			return "MyTeam";
		case CHATCHANNEL_BOTHTEAMS:
			return "BothTeams";
		case CHATCHANNEL_SYSTEM:
			return "System";
		case CHATCHANNEL_ACHIEVMENTS:
			return "Achievments";
		case CHATCHANNEL_PRIVATE:
			return "Private";
		case CHATCHANNEL_TAMBUR:
			return "Tambur";
		case CHATCHANNEL_GUILD:
			return "Guild";
		case CHATCHANNEL_LOOKINGFORGROUPE:
			return "LookingForGroupe";
		case CHATCHANNEL_ADMINISTRATION:
			return "Administration";
		case CHATCHANNEL_SMARTCHAT:
			return "SmartChat";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EChatChannel", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EChatChannel StringToEnum_EChatChannel( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EChatChannel)(NStr::ToInt( value ));
	if ( strcmp( value, "Global" ) == 0 || strcmp( value, "CHATCHANNEL_GLOBAL" ) == 0 )
		return CHATCHANNEL_GLOBAL;
	if ( strcmp( value, "MyTeam" ) == 0 || strcmp( value, "CHATCHANNEL_MYTEAM" ) == 0 )
		return CHATCHANNEL_MYTEAM;
	if ( strcmp( value, "BothTeams" ) == 0 || strcmp( value, "CHATCHANNEL_BOTHTEAMS" ) == 0 )
		return CHATCHANNEL_BOTHTEAMS;
	if ( strcmp( value, "System" ) == 0 || strcmp( value, "CHATCHANNEL_SYSTEM" ) == 0 )
		return CHATCHANNEL_SYSTEM;
	if ( strcmp( value, "Achievments" ) == 0 || strcmp( value, "CHATCHANNEL_ACHIEVMENTS" ) == 0 )
		return CHATCHANNEL_ACHIEVMENTS;
	if ( strcmp( value, "Private" ) == 0 || strcmp( value, "CHATCHANNEL_PRIVATE" ) == 0 )
		return CHATCHANNEL_PRIVATE;
	if ( strcmp( value, "Tambur" ) == 0 || strcmp( value, "CHATCHANNEL_TAMBUR" ) == 0 )
		return CHATCHANNEL_TAMBUR;
	if ( strcmp( value, "Guild" ) == 0 || strcmp( value, "CHATCHANNEL_GUILD" ) == 0 )
		return CHATCHANNEL_GUILD;
	if ( strcmp( value, "LookingForGroupe" ) == 0 || strcmp( value, "CHATCHANNEL_LOOKINGFORGROUPE" ) == 0 )
		return CHATCHANNEL_LOOKINGFORGROUPE;
	if ( strcmp( value, "Administration" ) == 0 || strcmp( value, "CHATCHANNEL_ADMINISTRATION" ) == 0 )
		return CHATCHANNEL_ADMINISTRATION;
	if ( strcmp( value, "SmartChat" ) == 0 || strcmp( value, "CHATCHANNEL_SMARTCHAT" ) == 0 )
		return CHATCHANNEL_SMARTCHAT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EChatChannel", value ) );
	return CHATCHANNEL_GLOBAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EClanWarsResourceType value )
{
	switch( value )
	{
		case CLANWARSRESOURCETYPE_CLANRATING:
			return "ClanRating";
		case CLANWARSRESOURCETYPE_PLAYERRATING:
			return "PlayerRating";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EClanWarsResourceType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EClanWarsResourceType StringToEnum_EClanWarsResourceType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EClanWarsResourceType)(NStr::ToInt( value ));
	if ( strcmp( value, "ClanRating" ) == 0 || strcmp( value, "CLANWARSRESOURCETYPE_CLANRATING" ) == 0 )
		return CLANWARSRESOURCETYPE_CLANRATING;
	if ( strcmp( value, "PlayerRating" ) == 0 || strcmp( value, "CLANWARSRESOURCETYPE_PLAYERRATING" ) == 0 )
		return CLANWARSRESOURCETYPE_PLAYERRATING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EClanWarsResourceType", value ) );
	return CLANWARSRESOURCETYPE_CLANRATING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDerivativeStat value )
{
	switch( value )
	{
		case DERIVATIVESTAT_LIFEREGENTOTAL:
			return "LifeRegenTotal";
		case DERIVATIVESTAT_ENERGYREGENTOTAL:
			return "EnergyRegenTotal";
		case DERIVATIVESTAT_DAMAGEMIN:
			return "DamageMin";
		case DERIVATIVESTAT_DAMAGEMAX:
			return "DamageMax";
		case DERIVATIVESTAT_DEXTERITYDAMAGEMULT:
			return "DexterityDamageMult";
		case DERIVATIVESTAT_MOVESPEEDMPS:
			return "MoveSpeedMpS";
		case DERIVATIVESTAT_CRITCHANCE:
			return "CritChance";
		case DERIVATIVESTAT_ATTACKSPERSECOND:
			return "AttacksPerSecond";
		case DERIVATIVESTAT_BODYDEFENCE:
			return "BodyDefence";
		case DERIVATIVESTAT_SPIRITDEFENCE:
			return "SpiritDefence";
		case DERIVATIVESTAT_PENETRATIONFROMATTACKSPEED:
			return "PenetrationFromAttackSpeed";
		case DERIVATIVESTAT_PENETRATIONFROMDEXTERITY:
			return "PenetrationFromDexterity";
		case DERIVATIVESTAT_PENETRATIONTOTAL:
			return "PenetrationTotal";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDerivativeStat", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDerivativeStat StringToEnum_EDerivativeStat( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDerivativeStat)(NStr::ToInt( value ));
	if ( strcmp( value, "LifeRegenTotal" ) == 0 || strcmp( value, "DERIVATIVESTAT_LIFEREGENTOTAL" ) == 0 )
		return DERIVATIVESTAT_LIFEREGENTOTAL;
	if ( strcmp( value, "EnergyRegenTotal" ) == 0 || strcmp( value, "DERIVATIVESTAT_ENERGYREGENTOTAL" ) == 0 )
		return DERIVATIVESTAT_ENERGYREGENTOTAL;
	if ( strcmp( value, "DamageMin" ) == 0 || strcmp( value, "DERIVATIVESTAT_DAMAGEMIN" ) == 0 )
		return DERIVATIVESTAT_DAMAGEMIN;
	if ( strcmp( value, "DamageMax" ) == 0 || strcmp( value, "DERIVATIVESTAT_DAMAGEMAX" ) == 0 )
		return DERIVATIVESTAT_DAMAGEMAX;
	if ( strcmp( value, "DexterityDamageMult" ) == 0 || strcmp( value, "DERIVATIVESTAT_DEXTERITYDAMAGEMULT" ) == 0 )
		return DERIVATIVESTAT_DEXTERITYDAMAGEMULT;
	if ( strcmp( value, "MoveSpeedMpS" ) == 0 || strcmp( value, "DERIVATIVESTAT_MOVESPEEDMPS" ) == 0 )
		return DERIVATIVESTAT_MOVESPEEDMPS;
	if ( strcmp( value, "CritChance" ) == 0 || strcmp( value, "DERIVATIVESTAT_CRITCHANCE" ) == 0 )
		return DERIVATIVESTAT_CRITCHANCE;
	if ( strcmp( value, "AttacksPerSecond" ) == 0 || strcmp( value, "DERIVATIVESTAT_ATTACKSPERSECOND" ) == 0 )
		return DERIVATIVESTAT_ATTACKSPERSECOND;
	if ( strcmp( value, "BodyDefence" ) == 0 || strcmp( value, "DERIVATIVESTAT_BODYDEFENCE" ) == 0 )
		return DERIVATIVESTAT_BODYDEFENCE;
	if ( strcmp( value, "SpiritDefence" ) == 0 || strcmp( value, "DERIVATIVESTAT_SPIRITDEFENCE" ) == 0 )
		return DERIVATIVESTAT_SPIRITDEFENCE;
	if ( strcmp( value, "PenetrationFromAttackSpeed" ) == 0 || strcmp( value, "DERIVATIVESTAT_PENETRATIONFROMATTACKSPEED" ) == 0 )
		return DERIVATIVESTAT_PENETRATIONFROMATTACKSPEED;
	if ( strcmp( value, "PenetrationFromDexterity" ) == 0 || strcmp( value, "DERIVATIVESTAT_PENETRATIONFROMDEXTERITY" ) == 0 )
		return DERIVATIVESTAT_PENETRATIONFROMDEXTERITY;
	if ( strcmp( value, "PenetrationTotal" ) == 0 || strcmp( value, "DERIVATIVESTAT_PENETRATIONTOTAL" ) == 0 )
		return DERIVATIVESTAT_PENETRATIONTOTAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDerivativeStat", value ) );
	return DERIVATIVESTAT_LIFEREGENTOTAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EErrorMessageType value )
{
	switch( value )
	{
		case ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY:
			return "NotEnoughPrimeToBuy";
		case ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY:
			return "NotEnoughManaForAbility";
		case ERRORMESSAGETYPE_ABILITYONCOOLDOWN:
			return "AbilityOnCooldown";
		case ERRORMESSAGETYPE_WRONGTARGET:
			return "WrongTarget";
		case ERRORMESSAGETYPE_INVULNERABLETARGET:
			return "InvulnerableTarget";
		case ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYTOWER:
			return "FlagpoleProtectedByTower";
		case ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYNEXT:
			return "FlagpoleProtectedByNext";
		case ERRORMESSAGETYPE_FLAGPOLETOOFAR:
			return "FlagpoleTooFar";
		case ERRORMESSAGETYPE_FLAGPOLECURRENTLYRISING:
			return "FlagpoleCurrentlyRising";
		case ERRORMESSAGETYPE_MINIGAMEBUSY:
			return "MinigameBusy";
		case ERRORMESSAGETYPE_MINIGAMEPROTECTEDBYTOWERS:
			return "MinigameProtectedByTowers";
		case ERRORMESSAGETYPE_WAITINGFORTARGET:
			return "WaitingForTarget";
		case ERRORMESSAGETYPE_OUTOFINVENTORY:
			return "OutOfInventory";
		case ERRORMESSAGETYPE_MINIGAMENOTREADY:
			return "MinigameNotReady";
		case ERRORMESSAGETYPE_MINIGAMEDISABLED:
			return "MinigameDisabled";
		case ERRORMESSAGETYPE_NOTENOUGHLIFEFORABILITY:
			return "NotEnoughLifeForAbility";
		case ERRORMESSAGETYPE_PINGRESTRICTED:
			return "PingRestricted";
		case ERRORMESSAGETYPE_SMARTCHATRESTRICTED:
			return "SmartChatRestricted";
		case ERRORMESSAGETYPE_REPLAYENDED:
			return "ReplayEnded";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EErrorMessageType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EErrorMessageType StringToEnum_EErrorMessageType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EErrorMessageType)(NStr::ToInt( value ));
	if ( strcmp( value, "NotEnoughPrimeToBuy" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY" ) == 0 )
		return ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY;
	if ( strcmp( value, "NotEnoughManaForAbility" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY" ) == 0 )
		return ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY;
	if ( strcmp( value, "AbilityOnCooldown" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_ABILITYONCOOLDOWN" ) == 0 )
		return ERRORMESSAGETYPE_ABILITYONCOOLDOWN;
	if ( strcmp( value, "WrongTarget" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_WRONGTARGET" ) == 0 )
		return ERRORMESSAGETYPE_WRONGTARGET;
	if ( strcmp( value, "InvulnerableTarget" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_INVULNERABLETARGET" ) == 0 )
		return ERRORMESSAGETYPE_INVULNERABLETARGET;
	if ( strcmp( value, "FlagpoleProtectedByTower" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYTOWER" ) == 0 )
		return ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYTOWER;
	if ( strcmp( value, "FlagpoleProtectedByNext" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYNEXT" ) == 0 )
		return ERRORMESSAGETYPE_FLAGPOLEPROTECTEDBYNEXT;
	if ( strcmp( value, "FlagpoleTooFar" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_FLAGPOLETOOFAR" ) == 0 )
		return ERRORMESSAGETYPE_FLAGPOLETOOFAR;
	if ( strcmp( value, "FlagpoleCurrentlyRising" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_FLAGPOLECURRENTLYRISING" ) == 0 )
		return ERRORMESSAGETYPE_FLAGPOLECURRENTLYRISING;
	if ( strcmp( value, "MinigameBusy" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_MINIGAMEBUSY" ) == 0 )
		return ERRORMESSAGETYPE_MINIGAMEBUSY;
	if ( strcmp( value, "MinigameProtectedByTowers" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_MINIGAMEPROTECTEDBYTOWERS" ) == 0 )
		return ERRORMESSAGETYPE_MINIGAMEPROTECTEDBYTOWERS;
	if ( strcmp( value, "WaitingForTarget" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_WAITINGFORTARGET" ) == 0 )
		return ERRORMESSAGETYPE_WAITINGFORTARGET;
	if ( strcmp( value, "OutOfInventory" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_OUTOFINVENTORY" ) == 0 )
		return ERRORMESSAGETYPE_OUTOFINVENTORY;
	if ( strcmp( value, "MinigameNotReady" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_MINIGAMENOTREADY" ) == 0 )
		return ERRORMESSAGETYPE_MINIGAMENOTREADY;
	if ( strcmp( value, "MinigameDisabled" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_MINIGAMEDISABLED" ) == 0 )
		return ERRORMESSAGETYPE_MINIGAMEDISABLED;
	if ( strcmp( value, "NotEnoughLifeForAbility" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_NOTENOUGHLIFEFORABILITY" ) == 0 )
		return ERRORMESSAGETYPE_NOTENOUGHLIFEFORABILITY;
	if ( strcmp( value, "PingRestricted" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_PINGRESTRICTED" ) == 0 )
		return ERRORMESSAGETYPE_PINGRESTRICTED;
	if ( strcmp( value, "SmartChatRestricted" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_SMARTCHATRESTRICTED" ) == 0 )
		return ERRORMESSAGETYPE_SMARTCHATRESTRICTED;
	if ( strcmp( value, "ReplayEnded" ) == 0 || strcmp( value, "ERRORMESSAGETYPE_REPLAYENDED" ) == 0 )
		return ERRORMESSAGETYPE_REPLAYENDED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EErrorMessageType", value ) );
	return ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFaction value )
{
	switch( value )
	{
		case FACTION_NEUTRAL:
			return "Neutral";
		case FACTION_FREEZE:
			return "Freeze";
		case FACTION_BURN:
			return "Burn";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFaction", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFaction StringToEnum_EFaction( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFaction)(NStr::ToInt( value ));
	if ( strcmp( value, "Neutral" ) == 0 || strcmp( value, "FACTION_NEUTRAL" ) == 0 )
		return FACTION_NEUTRAL;
	if ( strcmp( value, "Freeze" ) == 0 || strcmp( value, "FACTION_FREEZE" ) == 0 )
		return FACTION_FREEZE;
	if ( strcmp( value, "Burn" ) == 0 || strcmp( value, "FACTION_BURN" ) == 0 )
		return FACTION_BURN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFaction", value ) );
	return FACTION_NEUTRAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFactionFlags value )
{
	switch( value )
	{
		case FACTIONFLAGS_FACTIONFREEZE:
			return "FactionFreeze";
		case FACTIONFLAGS_FACTIONBURN:
			return "FactionBurn";
		case FACTIONFLAGS_NEUTRAL:
			return "Neutral";
		case FACTIONFLAGS_SELF:
			return "Self";
		case FACTIONFLAGS_OPPOSITE:
			return "Opposite";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFactionFlags StringToEnum_EFactionFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFactionFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "FactionFreeze" ) == 0 || strcmp( value, "FACTIONFLAGS_FACTIONFREEZE" ) == 0 )
		return FACTIONFLAGS_FACTIONFREEZE;
	if ( strcmp( value, "FactionBurn" ) == 0 || strcmp( value, "FACTIONFLAGS_FACTIONBURN" ) == 0 )
		return FACTIONFLAGS_FACTIONBURN;
	if ( strcmp( value, "Neutral" ) == 0 || strcmp( value, "FACTIONFLAGS_NEUTRAL" ) == 0 )
		return FACTIONFLAGS_NEUTRAL;
	if ( strcmp( value, "Self" ) == 0 || strcmp( value, "FACTIONFLAGS_SELF" ) == 0 )
		return FACTIONFLAGS_SELF;
	if ( strcmp( value, "Opposite" ) == 0 || strcmp( value, "FACTIONFLAGS_OPPOSITE" ) == 0 )
		return FACTIONFLAGS_OPPOSITE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFactionFlags", value ) );
	return FACTIONFLAGS_FACTIONFREEZE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFlyOffAlign value )
{
	switch( value )
	{
		case FLYOFFALIGN_LEFT:
			return "Left";
		case FLYOFFALIGN_CENTER:
			return "Center";
		case FLYOFFALIGN_RIGHT:
			return "Right";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFlyOffAlign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFlyOffAlign StringToEnum_EFlyOffAlign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFlyOffAlign)(NStr::ToInt( value ));
	if ( strcmp( value, "Left" ) == 0 || strcmp( value, "FLYOFFALIGN_LEFT" ) == 0 )
		return FLYOFFALIGN_LEFT;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "FLYOFFALIGN_CENTER" ) == 0 )
		return FLYOFFALIGN_CENTER;
	if ( strcmp( value, "Right" ) == 0 || strcmp( value, "FLYOFFALIGN_RIGHT" ) == 0 )
		return FLYOFFALIGN_RIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFlyOffAlign", value ) );
	return FLYOFFALIGN_LEFT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFormatType value )
{
	switch( value )
	{
		case FORMATTYPE_INTEGER:
			return "Integer";
		case FORMATTYPE_ONEDIGIT:
			return "OneDigit";
		case FORMATTYPE_TWODIGITS:
			return "TwoDigits";
		case FORMATTYPE_PERCENT:
			return "Percent";
		case FORMATTYPE_ONEDIGITPERCENT:
			return "OneDigitPercent";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFormatType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFormatType StringToEnum_EFormatType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFormatType)(NStr::ToInt( value ));
	if ( strcmp( value, "Integer" ) == 0 || strcmp( value, "FORMATTYPE_INTEGER" ) == 0 )
		return FORMATTYPE_INTEGER;
	if ( strcmp( value, "OneDigit" ) == 0 || strcmp( value, "FORMATTYPE_ONEDIGIT" ) == 0 )
		return FORMATTYPE_ONEDIGIT;
	if ( strcmp( value, "TwoDigits" ) == 0 || strcmp( value, "FORMATTYPE_TWODIGITS" ) == 0 )
		return FORMATTYPE_TWODIGITS;
	if ( strcmp( value, "Percent" ) == 0 || strcmp( value, "FORMATTYPE_PERCENT" ) == 0 )
		return FORMATTYPE_PERCENT;
	if ( strcmp( value, "OneDigitPercent" ) == 0 || strcmp( value, "FORMATTYPE_ONEDIGITPERCENT" ) == 0 )
		return FORMATTYPE_ONEDIGITPERCENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFormatType", value ) );
	return FORMATTYPE_INTEGER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EHeroTitle value )
{
	switch( value )
	{
		case HEROTITLE_BESTKILLER:
			return "BestKiller";
		case HEROTITLE_BESTASSISTER:
			return "BestAssister";
		case HEROTITLE_TOPCREEPKILLS:
			return "TopCreepKills";
		case HEROTITLE_TOPTOWERKILLS:
			return "TopTowerKills";
		case HEROTITLE_LEASTDEATHS:
			return "LeastDeaths";
		case HEROTITLE_TOPNAFTA:
			return "TopNafta";
		case HEROTITLE_PAINTER_MG2:
			return "Painter_mg2";
		case HEROTITLE_DEDICATED_MG2:
			return "Dedicated_mg2";
		case HEROTITLE_MERCILESS:
			return "Merciless";
		case HEROTITLE_WANDERER:
			return "Wanderer";
		case HEROTITLE_TELEPORTER:
			return "Teleporter";
		case HEROTITLE_STAY_AT_HOME:
			return "Stay_at_home";
		case HEROTITLE_TOPCONSUMABLEUSER:
			return "TopConsumableUser";
		case HEROTITLE_LEASTCONSUMABLEUSER:
			return "LeastConsumableUser";
		case HEROTITLE_ASCETIC:
			return "Ascetic";
		case HEROTITLE_TOPKILLSTREAKER:
			return "TopKillStreaker";
		case HEROTITLE_SHINIGAMI:
			return "Shinigami";
		case HEROTITLE_ADVENTURER:
			return "Adventurer";
		case HEROTITLE_TOPTOWERDENIER:
			return "TopTowerDenier";
		case HEROTITLE_TOPNEUTRALKILLER:
			return "TopNeutralKiller";
		case HEROTITLE_TOPCEREMONIALKILLER:
			return "TopCeremonialKiller";
		case HEROTITLE_TOPONEHEROKILLER:
			return "TopOneHeroKiller";
		case HEROTITLE_AVENGER:
			return "Avenger";
		case HEROTITLE_LASTHITTOMAINBUILDING:
			return "LastHitToMainBuilding";
		case HEROTITLE_TOPIDLETIME:
			return "TopIdleTime";
		case HEROTITLE_HUNTSMAN:
			return "Huntsman";
		case HEROTITLE_DRAGONSLAYER:
			return "DragonSlayer";
		case HEROTITLE_LEGEND:
			return "Legend";
		case HEROTITLE_KAMIKAZE:
			return "Kamikaze";
		case HEROTITLE_NOVICE:
			return "Novice";
		case HEROTITLE_BOSSSLAYER:
			return "BossSlayer";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EHeroTitle", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EHeroTitle StringToEnum_EHeroTitle( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EHeroTitle)(NStr::ToInt( value ));
	if ( strcmp( value, "BestKiller" ) == 0 || strcmp( value, "HEROTITLE_BESTKILLER" ) == 0 )
		return HEROTITLE_BESTKILLER;
	if ( strcmp( value, "BestAssister" ) == 0 || strcmp( value, "HEROTITLE_BESTASSISTER" ) == 0 )
		return HEROTITLE_BESTASSISTER;
	if ( strcmp( value, "TopCreepKills" ) == 0 || strcmp( value, "HEROTITLE_TOPCREEPKILLS" ) == 0 )
		return HEROTITLE_TOPCREEPKILLS;
	if ( strcmp( value, "TopTowerKills" ) == 0 || strcmp( value, "HEROTITLE_TOPTOWERKILLS" ) == 0 )
		return HEROTITLE_TOPTOWERKILLS;
	if ( strcmp( value, "LeastDeaths" ) == 0 || strcmp( value, "HEROTITLE_LEASTDEATHS" ) == 0 )
		return HEROTITLE_LEASTDEATHS;
	if ( strcmp( value, "TopNafta" ) == 0 || strcmp( value, "HEROTITLE_TOPNAFTA" ) == 0 )
		return HEROTITLE_TOPNAFTA;
	if ( strcmp( value, "Painter_mg2" ) == 0 || strcmp( value, "HEROTITLE_PAINTER_MG2" ) == 0 )
		return HEROTITLE_PAINTER_MG2;
	if ( strcmp( value, "Dedicated_mg2" ) == 0 || strcmp( value, "HEROTITLE_DEDICATED_MG2" ) == 0 )
		return HEROTITLE_DEDICATED_MG2;
	if ( strcmp( value, "Merciless" ) == 0 || strcmp( value, "HEROTITLE_MERCILESS" ) == 0 )
		return HEROTITLE_MERCILESS;
	if ( strcmp( value, "Wanderer" ) == 0 || strcmp( value, "HEROTITLE_WANDERER" ) == 0 )
		return HEROTITLE_WANDERER;
	if ( strcmp( value, "Teleporter" ) == 0 || strcmp( value, "HEROTITLE_TELEPORTER" ) == 0 )
		return HEROTITLE_TELEPORTER;
	if ( strcmp( value, "Stay_at_home" ) == 0 || strcmp( value, "HEROTITLE_STAY_AT_HOME" ) == 0 )
		return HEROTITLE_STAY_AT_HOME;
	if ( strcmp( value, "TopConsumableUser" ) == 0 || strcmp( value, "HEROTITLE_TOPCONSUMABLEUSER" ) == 0 )
		return HEROTITLE_TOPCONSUMABLEUSER;
	if ( strcmp( value, "LeastConsumableUser" ) == 0 || strcmp( value, "HEROTITLE_LEASTCONSUMABLEUSER" ) == 0 )
		return HEROTITLE_LEASTCONSUMABLEUSER;
	if ( strcmp( value, "Ascetic" ) == 0 || strcmp( value, "HEROTITLE_ASCETIC" ) == 0 )
		return HEROTITLE_ASCETIC;
	if ( strcmp( value, "TopKillStreaker" ) == 0 || strcmp( value, "HEROTITLE_TOPKILLSTREAKER" ) == 0 )
		return HEROTITLE_TOPKILLSTREAKER;
	if ( strcmp( value, "Shinigami" ) == 0 || strcmp( value, "HEROTITLE_SHINIGAMI" ) == 0 )
		return HEROTITLE_SHINIGAMI;
	if ( strcmp( value, "Adventurer" ) == 0 || strcmp( value, "HEROTITLE_ADVENTURER" ) == 0 )
		return HEROTITLE_ADVENTURER;
	if ( strcmp( value, "TopTowerDenier" ) == 0 || strcmp( value, "HEROTITLE_TOPTOWERDENIER" ) == 0 )
		return HEROTITLE_TOPTOWERDENIER;
	if ( strcmp( value, "TopNeutralKiller" ) == 0 || strcmp( value, "HEROTITLE_TOPNEUTRALKILLER" ) == 0 )
		return HEROTITLE_TOPNEUTRALKILLER;
	if ( strcmp( value, "TopCeremonialKiller" ) == 0 || strcmp( value, "HEROTITLE_TOPCEREMONIALKILLER" ) == 0 )
		return HEROTITLE_TOPCEREMONIALKILLER;
	if ( strcmp( value, "TopOneHeroKiller" ) == 0 || strcmp( value, "HEROTITLE_TOPONEHEROKILLER" ) == 0 )
		return HEROTITLE_TOPONEHEROKILLER;
	if ( strcmp( value, "Avenger" ) == 0 || strcmp( value, "HEROTITLE_AVENGER" ) == 0 )
		return HEROTITLE_AVENGER;
	if ( strcmp( value, "LastHitToMainBuilding" ) == 0 || strcmp( value, "HEROTITLE_LASTHITTOMAINBUILDING" ) == 0 )
		return HEROTITLE_LASTHITTOMAINBUILDING;
	if ( strcmp( value, "TopIdleTime" ) == 0 || strcmp( value, "HEROTITLE_TOPIDLETIME" ) == 0 )
		return HEROTITLE_TOPIDLETIME;
	if ( strcmp( value, "Huntsman" ) == 0 || strcmp( value, "HEROTITLE_HUNTSMAN" ) == 0 )
		return HEROTITLE_HUNTSMAN;
	if ( strcmp( value, "DragonSlayer" ) == 0 || strcmp( value, "HEROTITLE_DRAGONSLAYER" ) == 0 )
		return HEROTITLE_DRAGONSLAYER;
	if ( strcmp( value, "Legend" ) == 0 || strcmp( value, "HEROTITLE_LEGEND" ) == 0 )
		return HEROTITLE_LEGEND;
	if ( strcmp( value, "Kamikaze" ) == 0 || strcmp( value, "HEROTITLE_KAMIKAZE" ) == 0 )
		return HEROTITLE_KAMIKAZE;
	if ( strcmp( value, "Novice" ) == 0 || strcmp( value, "HEROTITLE_NOVICE" ) == 0 )
		return HEROTITLE_NOVICE;
	if ( strcmp( value, "BossSlayer" ) == 0 || strcmp( value, "HEROTITLE_BOSSSLAYER" ) == 0 )
		return HEROTITLE_BOSSSLAYER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EHeroTitle", value ) );
	return HEROTITLE_BESTKILLER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMessage value )
{
	switch( value )
	{
		case MESSAGE_SIMPLE_MESSAGE:
			return "SIMPLE_MESSAGE";
		case MESSAGE_LINEAR_FEAT_MESSAGE:
			return "LINEAR_FEAT_MESSAGE";
		case MESSAGE_ONLY_FOR_PRIESTESS_MESSAGE:
			return "ONLY_FOR_PRIESTESS_MESSAGE";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMessage", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMessage StringToEnum_EMessage( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMessage)(NStr::ToInt( value ));
	if ( strcmp( value, "SIMPLE_MESSAGE" ) == 0 || strcmp( value, "MESSAGE_SIMPLE_MESSAGE" ) == 0 )
		return MESSAGE_SIMPLE_MESSAGE;
	if ( strcmp( value, "LINEAR_FEAT_MESSAGE" ) == 0 || strcmp( value, "MESSAGE_LINEAR_FEAT_MESSAGE" ) == 0 )
		return MESSAGE_LINEAR_FEAT_MESSAGE;
	if ( strcmp( value, "ONLY_FOR_PRIESTESS_MESSAGE" ) == 0 || strcmp( value, "MESSAGE_ONLY_FOR_PRIESTESS_MESSAGE" ) == 0 )
		return MESSAGE_ONLY_FOR_PRIESTESS_MESSAGE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMessage", value ) );
	return MESSAGE_SIMPLE_MESSAGE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EMinimapIcons value )
{
	switch( value )
	{
		case MINIMAPICONS_DEFAULT:
			return "Default";
		case MINIMAPICONS_MAINBUILDINGA:
			return "MainBuildingA";
		case MINIMAPICONS_MAINBUILDINGB:
			return "MainBuildingB";
		case MINIMAPICONS_SHOPA:
			return "ShopA";
		case MINIMAPICONS_SHOPB:
			return "ShopB";
		case MINIMAPICONS_SHOPN:
			return "ShopN";
		case MINIMAPICONS_QUARTERA:
			return "QuarterA";
		case MINIMAPICONS_QUARTERB:
			return "QuarterB";
		case MINIMAPICONS_TOWERA:
			return "TowerA";
		case MINIMAPICONS_TOWERB:
			return "TowerB";
		case MINIMAPICONS_NEUTRALSWEAK:
			return "NeutralsWeak";
		case MINIMAPICONS_NEUTRALSSTRONG:
			return "NeutralsStrong";
		case MINIMAPICONS_NEUTRALSBOSS:
			return "NeutralsBoss";
		case MINIMAPICONS_MINIGAME:
			return "Minigame";
		case MINIMAPICONS_FOUNTAINA:
			return "FountainA";
		case MINIMAPICONS_FOUNTAINB:
			return "FountainB";
		case MINIMAPICONS_FLAGPOLE:
			return "Flagpole";
		case MINIMAPICONS_ALTARA:
			return "AltarA";
		case MINIMAPICONS_ALTARB:
			return "AltarB";
		case MINIMAPICONS_EGG:
			return "Egg";
		case MINIMAPICONS_ALCHEMISTCIRCLE:
			return "AlchemistCircle";
		case MINIMAPICONS_GLYPH:
			return "Glyph";
		case MINIMAPICONS_BRIDGEPASSABLE:
			return "BridgePassable";
		case MINIMAPICONS_BRIDGEIMPASSABLE:
			return "BridgeImpassable";
		case MINIMAPICONS_PUSHBUTTON:
			return "PushButton";
		case MINIMAPICONS_NONE:
			return "None";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EMinimapIcons", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EMinimapIcons StringToEnum_EMinimapIcons( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EMinimapIcons)(NStr::ToInt( value ));
	if ( strcmp( value, "Default" ) == 0 || strcmp( value, "MINIMAPICONS_DEFAULT" ) == 0 )
		return MINIMAPICONS_DEFAULT;
	if ( strcmp( value, "MainBuildingA" ) == 0 || strcmp( value, "MINIMAPICONS_MAINBUILDINGA" ) == 0 )
		return MINIMAPICONS_MAINBUILDINGA;
	if ( strcmp( value, "MainBuildingB" ) == 0 || strcmp( value, "MINIMAPICONS_MAINBUILDINGB" ) == 0 )
		return MINIMAPICONS_MAINBUILDINGB;
	if ( strcmp( value, "ShopA" ) == 0 || strcmp( value, "MINIMAPICONS_SHOPA" ) == 0 )
		return MINIMAPICONS_SHOPA;
	if ( strcmp( value, "ShopB" ) == 0 || strcmp( value, "MINIMAPICONS_SHOPB" ) == 0 )
		return MINIMAPICONS_SHOPB;
	if ( strcmp( value, "ShopN" ) == 0 || strcmp( value, "MINIMAPICONS_SHOPN" ) == 0 )
		return MINIMAPICONS_SHOPN;
	if ( strcmp( value, "QuarterA" ) == 0 || strcmp( value, "MINIMAPICONS_QUARTERA" ) == 0 )
		return MINIMAPICONS_QUARTERA;
	if ( strcmp( value, "QuarterB" ) == 0 || strcmp( value, "MINIMAPICONS_QUARTERB" ) == 0 )
		return MINIMAPICONS_QUARTERB;
	if ( strcmp( value, "TowerA" ) == 0 || strcmp( value, "MINIMAPICONS_TOWERA" ) == 0 )
		return MINIMAPICONS_TOWERA;
	if ( strcmp( value, "TowerB" ) == 0 || strcmp( value, "MINIMAPICONS_TOWERB" ) == 0 )
		return MINIMAPICONS_TOWERB;
	if ( strcmp( value, "NeutralsWeak" ) == 0 || strcmp( value, "MINIMAPICONS_NEUTRALSWEAK" ) == 0 )
		return MINIMAPICONS_NEUTRALSWEAK;
	if ( strcmp( value, "NeutralsStrong" ) == 0 || strcmp( value, "MINIMAPICONS_NEUTRALSSTRONG" ) == 0 )
		return MINIMAPICONS_NEUTRALSSTRONG;
	if ( strcmp( value, "NeutralsBoss" ) == 0 || strcmp( value, "MINIMAPICONS_NEUTRALSBOSS" ) == 0 )
		return MINIMAPICONS_NEUTRALSBOSS;
	if ( strcmp( value, "Minigame" ) == 0 || strcmp( value, "MINIMAPICONS_MINIGAME" ) == 0 )
		return MINIMAPICONS_MINIGAME;
	if ( strcmp( value, "FountainA" ) == 0 || strcmp( value, "MINIMAPICONS_FOUNTAINA" ) == 0 )
		return MINIMAPICONS_FOUNTAINA;
	if ( strcmp( value, "FountainB" ) == 0 || strcmp( value, "MINIMAPICONS_FOUNTAINB" ) == 0 )
		return MINIMAPICONS_FOUNTAINB;
	if ( strcmp( value, "Flagpole" ) == 0 || strcmp( value, "MINIMAPICONS_FLAGPOLE" ) == 0 )
		return MINIMAPICONS_FLAGPOLE;
	if ( strcmp( value, "AltarA" ) == 0 || strcmp( value, "MINIMAPICONS_ALTARA" ) == 0 )
		return MINIMAPICONS_ALTARA;
	if ( strcmp( value, "AltarB" ) == 0 || strcmp( value, "MINIMAPICONS_ALTARB" ) == 0 )
		return MINIMAPICONS_ALTARB;
	if ( strcmp( value, "Egg" ) == 0 || strcmp( value, "MINIMAPICONS_EGG" ) == 0 )
		return MINIMAPICONS_EGG;
	if ( strcmp( value, "AlchemistCircle" ) == 0 || strcmp( value, "MINIMAPICONS_ALCHEMISTCIRCLE" ) == 0 )
		return MINIMAPICONS_ALCHEMISTCIRCLE;
	if ( strcmp( value, "Glyph" ) == 0 || strcmp( value, "MINIMAPICONS_GLYPH" ) == 0 )
		return MINIMAPICONS_GLYPH;
	if ( strcmp( value, "BridgePassable" ) == 0 || strcmp( value, "MINIMAPICONS_BRIDGEPASSABLE" ) == 0 )
		return MINIMAPICONS_BRIDGEPASSABLE;
	if ( strcmp( value, "BridgeImpassable" ) == 0 || strcmp( value, "MINIMAPICONS_BRIDGEIMPASSABLE" ) == 0 )
		return MINIMAPICONS_BRIDGEIMPASSABLE;
	if ( strcmp( value, "PushButton" ) == 0 || strcmp( value, "MINIMAPICONS_PUSHBUTTON" ) == 0 )
		return MINIMAPICONS_PUSHBUTTON;
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MINIMAPICONS_NONE" ) == 0 )
		return MINIMAPICONS_NONE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EMinimapIcons", value ) );
	return MINIMAPICONS_DEFAULT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPathMarker value )
{
	switch( value )
	{
		case PATHMARKER_GREEN:
			return "Green";
		case PATHMARKER_RED:
			return "Red";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPathMarker", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPathMarker StringToEnum_EPathMarker( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPathMarker)(NStr::ToInt( value ));
	if ( strcmp( value, "Green" ) == 0 || strcmp( value, "PATHMARKER_GREEN" ) == 0 )
		return PATHMARKER_GREEN;
	if ( strcmp( value, "Red" ) == 0 || strcmp( value, "PATHMARKER_RED" ) == 0 )
		return PATHMARKER_RED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPathMarker", value ) );
	return PATHMARKER_GREEN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPlayerID value )
{
	switch( value )
	{
		case PLAYERID_NONE:
			return "None";
		case PLAYERID_PLAYER_1:
			return "Player_1";
		case PLAYERID_PLAYER_2:
			return "Player_2";
		case PLAYERID_PLAYER_3:
			return "Player_3";
		case PLAYERID_PLAYER_4:
			return "Player_4";
		case PLAYERID_PLAYER_5:
			return "Player_5";
		case PLAYERID_PLAYER_6:
			return "Player_6";
		case PLAYERID_PLAYER_7:
			return "Player_7";
		case PLAYERID_PLAYER_8:
			return "Player_8";
		case PLAYERID_PLAYER_9:
			return "Player_9";
		case PLAYERID_PLAYER_10:
			return "Player_10";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPlayerID", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPlayerID StringToEnum_EPlayerID( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPlayerID)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "PLAYERID_NONE" ) == 0 )
		return PLAYERID_NONE;
	if ( strcmp( value, "Player_1" ) == 0 || strcmp( value, "PLAYERID_PLAYER_1" ) == 0 )
		return PLAYERID_PLAYER_1;
	if ( strcmp( value, "Player_2" ) == 0 || strcmp( value, "PLAYERID_PLAYER_2" ) == 0 )
		return PLAYERID_PLAYER_2;
	if ( strcmp( value, "Player_3" ) == 0 || strcmp( value, "PLAYERID_PLAYER_3" ) == 0 )
		return PLAYERID_PLAYER_3;
	if ( strcmp( value, "Player_4" ) == 0 || strcmp( value, "PLAYERID_PLAYER_4" ) == 0 )
		return PLAYERID_PLAYER_4;
	if ( strcmp( value, "Player_5" ) == 0 || strcmp( value, "PLAYERID_PLAYER_5" ) == 0 )
		return PLAYERID_PLAYER_5;
	if ( strcmp( value, "Player_6" ) == 0 || strcmp( value, "PLAYERID_PLAYER_6" ) == 0 )
		return PLAYERID_PLAYER_6;
	if ( strcmp( value, "Player_7" ) == 0 || strcmp( value, "PLAYERID_PLAYER_7" ) == 0 )
		return PLAYERID_PLAYER_7;
	if ( strcmp( value, "Player_8" ) == 0 || strcmp( value, "PLAYERID_PLAYER_8" ) == 0 )
		return PLAYERID_PLAYER_8;
	if ( strcmp( value, "Player_9" ) == 0 || strcmp( value, "PLAYERID_PLAYER_9" ) == 0 )
		return PLAYERID_PLAYER_9;
	if ( strcmp( value, "Player_10" ) == 0 || strcmp( value, "PLAYERID_PLAYER_10" ) == 0 )
		return PLAYERID_PLAYER_10;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPlayerID", value ) );
	return PLAYERID_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ERecipients value )
{
	switch( value )
	{
		case RECIPIENTS_EVENT_PARTICIPANTS:
			return "EVENT_PARTICIPANTS";
		case RECIPIENTS_EVENT_MAKER_TEAM:
			return "EVENT_MAKER_TEAM";
		case RECIPIENTS_EVENT_MAKER_OPPOSITE_TEAM:
			return "EVENT_MAKER_OPPOSITE_TEAM";
		case RECIPIENTS_ALL_PLAYERS:
			return "ALL_PLAYERS";
		case RECIPIENTS_ALL_PLAYERS_WITHOUT_PRIESTESS:
			return "ALL_PLAYERS_WITHOUT_PRIESTESS";
		case RECIPIENTS_PLAYER_ONLY:
			return "PLAYER_ONLY";
		case RECIPIENTS_USE_FROM_PARENT:
			return "USE_FROM_PARENT";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ERecipients", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ERecipients StringToEnum_ERecipients( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ERecipients)(NStr::ToInt( value ));
	if ( strcmp( value, "EVENT_PARTICIPANTS" ) == 0 || strcmp( value, "RECIPIENTS_EVENT_PARTICIPANTS" ) == 0 )
		return RECIPIENTS_EVENT_PARTICIPANTS;
	if ( strcmp( value, "EVENT_MAKER_TEAM" ) == 0 || strcmp( value, "RECIPIENTS_EVENT_MAKER_TEAM" ) == 0 )
		return RECIPIENTS_EVENT_MAKER_TEAM;
	if ( strcmp( value, "EVENT_MAKER_OPPOSITE_TEAM" ) == 0 || strcmp( value, "RECIPIENTS_EVENT_MAKER_OPPOSITE_TEAM" ) == 0 )
		return RECIPIENTS_EVENT_MAKER_OPPOSITE_TEAM;
	if ( strcmp( value, "ALL_PLAYERS" ) == 0 || strcmp( value, "RECIPIENTS_ALL_PLAYERS" ) == 0 )
		return RECIPIENTS_ALL_PLAYERS;
	if ( strcmp( value, "ALL_PLAYERS_WITHOUT_PRIESTESS" ) == 0 || strcmp( value, "RECIPIENTS_ALL_PLAYERS_WITHOUT_PRIESTESS" ) == 0 )
		return RECIPIENTS_ALL_PLAYERS_WITHOUT_PRIESTESS;
	if ( strcmp( value, "PLAYER_ONLY" ) == 0 || strcmp( value, "RECIPIENTS_PLAYER_ONLY" ) == 0 )
		return RECIPIENTS_PLAYER_ONLY;
	if ( strcmp( value, "USE_FROM_PARENT" ) == 0 || strcmp( value, "RECIPIENTS_USE_FROM_PARENT" ) == 0 )
		return RECIPIENTS_USE_FROM_PARENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ERecipients", value ) );
	return RECIPIENTS_EVENT_PARTICIPANTS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EResourceType value )
{
	switch( value )
	{
		case RESOURCETYPE_SILVER:
			return "Silver";
		case RESOURCETYPE_CRYSTAL:
			return "Crystal";
		case RESOURCETYPE_RESOURCE1:
			return "Resource1";
		case RESOURCETYPE_RESOURCE2:
			return "Resource2";
		case RESOURCETYPE_RESOURCE3:
			return "Resource3";
		case RESOURCETYPE_REDCRYSTAL:
			return "RedCrystal";
		case RESOURCETYPE_SHARD:
			return "Shard";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EResourceType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EResourceType StringToEnum_EResourceType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EResourceType)(NStr::ToInt( value ));
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "RESOURCETYPE_SILVER" ) == 0 )
		return RESOURCETYPE_SILVER;
	if ( strcmp( value, "Crystal" ) == 0 || strcmp( value, "RESOURCETYPE_CRYSTAL" ) == 0 )
		return RESOURCETYPE_CRYSTAL;
	if ( strcmp( value, "Resource1" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE1" ) == 0 )
		return RESOURCETYPE_RESOURCE1;
	if ( strcmp( value, "Resource2" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE2" ) == 0 )
		return RESOURCETYPE_RESOURCE2;
	if ( strcmp( value, "Resource3" ) == 0 || strcmp( value, "RESOURCETYPE_RESOURCE3" ) == 0 )
		return RESOURCETYPE_RESOURCE3;
	if ( strcmp( value, "RedCrystal" ) == 0 || strcmp( value, "RESOURCETYPE_REDCRYSTAL" ) == 0 )
		return RESOURCETYPE_REDCRYSTAL;
	if ( strcmp( value, "Shard" ) == 0 || strcmp( value, "RESOURCETYPE_SHARD" ) == 0 )
		return RESOURCETYPE_SHARD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EResourceType", value ) );
	return RESOURCETYPE_SILVER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ERoute value )
{
	switch( value )
	{
		case ROUTE_TOP:
			return "Top";
		case ROUTE_CENTER:
			return "Center";
		case ROUTE_BOTTOM:
			return "Bottom";
		case ROUTE_TREE:
			return "Tree";
		case ROUTE_UNASSIGNED:
			return "Unassigned";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ERoute", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ERoute StringToEnum_ERoute( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ERoute)(NStr::ToInt( value ));
	if ( strcmp( value, "Top" ) == 0 || strcmp( value, "ROUTE_TOP" ) == 0 )
		return ROUTE_TOP;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "ROUTE_CENTER" ) == 0 )
		return ROUTE_CENTER;
	if ( strcmp( value, "Bottom" ) == 0 || strcmp( value, "ROUTE_BOTTOM" ) == 0 )
		return ROUTE_BOTTOM;
	if ( strcmp( value, "Tree" ) == 0 || strcmp( value, "ROUTE_TREE" ) == 0 )
		return ROUTE_TREE;
	if ( strcmp( value, "Unassigned" ) == 0 || strcmp( value, "ROUTE_UNASSIGNED" ) == 0 )
		return ROUTE_UNASSIGNED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ERoute", value ) );
	return ROUTE_TOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EScoreType value )
{
	switch( value )
	{
		case SCORETYPE_HEROKILLCOUNT:
			return "HeroKillCount";
		case SCORETYPE_DEATHCOUNT:
			return "DeathCount";
		case SCORETYPE_ASSISTCOUNT:
			return "AssistCount";
		case SCORETYPE_SCORE:
			return "Score";
		case SCORETYPE_TOTALNAFTA:
			return "TotalNafta";
		case SCORETYPE_ACHIEVMENTCOUNT:
			return "AchievmentCount";
		case SCORETYPE_TOWERSDESTROYED:
			return "TowersDestroyed";
		case SCORETYPE_TOWERSDENIED:
			return "TowersDenied";
		case SCORETYPE_FLAGSRAISED:
			return "FlagsRaised";
		case SCORETYPE_FLAGSDESTROYED:
			return "FlagsDestroyed";
		case SCORETYPE_MINIGAMELEVELSWON:
			return "MinigameLevelsWon";
		case SCORETYPE_CREEPSKILLED:
			return "CreepsKilled";
		case SCORETYPE_NEUTRALCREEPSCOUNT:
			return "NeutralCreepsCount";
		case SCORETYPE_TIMEINDEATH:
			return "TimeInDeath";
		case SCORETYPE_HELEADAMOUNT:
			return "HeleadAmount";
		case SCORETYPE_SEXHELP:
			return "SexHelp";
		case SCORETYPE_DAMAGEDEALED:
			return "DamageDealed";
		case SCORETYPE_DAMAGERECIEVED:
			return "DamageRecieved";
		case SCORETYPE_DANAGEHERODEALED:
			return "DanageHeroDealed";
		case SCORETYPE_DANAGEHERORECIEVED:
			return "DanageHeroRecieved";
		case SCORETYPE_METERIALDAMAGEDEALED:
			return "MeterialDamageDealed";
		case SCORETYPE_METERIALDAMAGERECIEVED:
			return "MeterialDamageRecieved";
		case SCORETYPE_ENERGYDAMAGEDEALED:
			return "EnergyDamageDealed";
		case SCORETYPE_ENERGYDAMAGERECIEVED:
			return "EnergyDamageRecieved";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EScoreType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EScoreType StringToEnum_EScoreType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EScoreType)(NStr::ToInt( value ));
	if ( strcmp( value, "HeroKillCount" ) == 0 || strcmp( value, "SCORETYPE_HEROKILLCOUNT" ) == 0 )
		return SCORETYPE_HEROKILLCOUNT;
	if ( strcmp( value, "DeathCount" ) == 0 || strcmp( value, "SCORETYPE_DEATHCOUNT" ) == 0 )
		return SCORETYPE_DEATHCOUNT;
	if ( strcmp( value, "AssistCount" ) == 0 || strcmp( value, "SCORETYPE_ASSISTCOUNT" ) == 0 )
		return SCORETYPE_ASSISTCOUNT;
	if ( strcmp( value, "Score" ) == 0 || strcmp( value, "SCORETYPE_SCORE" ) == 0 )
		return SCORETYPE_SCORE;
	if ( strcmp( value, "TotalNafta" ) == 0 || strcmp( value, "SCORETYPE_TOTALNAFTA" ) == 0 )
		return SCORETYPE_TOTALNAFTA;
	if ( strcmp( value, "AchievmentCount" ) == 0 || strcmp( value, "SCORETYPE_ACHIEVMENTCOUNT" ) == 0 )
		return SCORETYPE_ACHIEVMENTCOUNT;
	if ( strcmp( value, "TowersDestroyed" ) == 0 || strcmp( value, "SCORETYPE_TOWERSDESTROYED" ) == 0 )
		return SCORETYPE_TOWERSDESTROYED;
	if ( strcmp( value, "TowersDenied" ) == 0 || strcmp( value, "SCORETYPE_TOWERSDENIED" ) == 0 )
		return SCORETYPE_TOWERSDENIED;
	if ( strcmp( value, "FlagsRaised" ) == 0 || strcmp( value, "SCORETYPE_FLAGSRAISED" ) == 0 )
		return SCORETYPE_FLAGSRAISED;
	if ( strcmp( value, "FlagsDestroyed" ) == 0 || strcmp( value, "SCORETYPE_FLAGSDESTROYED" ) == 0 )
		return SCORETYPE_FLAGSDESTROYED;
	if ( strcmp( value, "MinigameLevelsWon" ) == 0 || strcmp( value, "SCORETYPE_MINIGAMELEVELSWON" ) == 0 )
		return SCORETYPE_MINIGAMELEVELSWON;
	if ( strcmp( value, "CreepsKilled" ) == 0 || strcmp( value, "SCORETYPE_CREEPSKILLED" ) == 0 )
		return SCORETYPE_CREEPSKILLED;
	if ( strcmp( value, "NeutralCreepsCount" ) == 0 || strcmp( value, "SCORETYPE_NEUTRALCREEPSCOUNT" ) == 0 )
		return SCORETYPE_NEUTRALCREEPSCOUNT;
	if ( strcmp( value, "TimeInDeath" ) == 0 || strcmp( value, "SCORETYPE_TIMEINDEATH" ) == 0 )
		return SCORETYPE_TIMEINDEATH;
	if ( strcmp( value, "HeleadAmount" ) == 0 || strcmp( value, "SCORETYPE_HELEADAMOUNT" ) == 0 )
		return SCORETYPE_HELEADAMOUNT;
	if ( strcmp( value, "SexHelp" ) == 0 || strcmp( value, "SCORETYPE_SEXHELP" ) == 0 )
		return SCORETYPE_SEXHELP;
	if ( strcmp( value, "DamageDealed" ) == 0 || strcmp( value, "SCORETYPE_DAMAGEDEALED" ) == 0 )
		return SCORETYPE_DAMAGEDEALED;
	if ( strcmp( value, "DamageRecieved" ) == 0 || strcmp( value, "SCORETYPE_DAMAGERECIEVED" ) == 0 )
		return SCORETYPE_DAMAGERECIEVED;
	if ( strcmp( value, "DanageHeroDealed" ) == 0 || strcmp( value, "SCORETYPE_DANAGEHERODEALED" ) == 0 )
		return SCORETYPE_DANAGEHERODEALED;
	if ( strcmp( value, "DanageHeroRecieved" ) == 0 || strcmp( value, "SCORETYPE_DANAGEHERORECIEVED" ) == 0 )
		return SCORETYPE_DANAGEHERORECIEVED;
	if ( strcmp( value, "MeterialDamageDealed" ) == 0 || strcmp( value, "SCORETYPE_METERIALDAMAGEDEALED" ) == 0 )
		return SCORETYPE_METERIALDAMAGEDEALED;
	if ( strcmp( value, "MeterialDamageRecieved" ) == 0 || strcmp( value, "SCORETYPE_METERIALDAMAGERECIEVED" ) == 0 )
		return SCORETYPE_METERIALDAMAGERECIEVED;
	if ( strcmp( value, "EnergyDamageDealed" ) == 0 || strcmp( value, "SCORETYPE_ENERGYDAMAGEDEALED" ) == 0 )
		return SCORETYPE_ENERGYDAMAGEDEALED;
	if ( strcmp( value, "EnergyDamageRecieved" ) == 0 || strcmp( value, "SCORETYPE_ENERGYDAMAGERECIEVED" ) == 0 )
		return SCORETYPE_ENERGYDAMAGERECIEVED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EScoreType", value ) );
	return SCORETYPE_HEROKILLCOUNT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ESign value )
{
	switch( value )
	{
		case SIGN_NONE:
			return "NONE";
		case SIGN_SEND_MESSAGE_TO_CHAT:
			return "SEND_MESSAGE_TO_CHAT";
		case SIGN_SEND_MESSAGE_TO_STATUS_LINE:
			return "SEND_MESSAGE_TO_STATUS_LINE";
		case SIGN_PLAY_SOUND:
			return "PLAY_SOUND";
		case SIGN_FLYOFF_TEXT:
			return "FLYOFF_TEXT";
		case SIGN_ANNOUNCEMENT:
			return "ANNOUNCEMENT";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ESign", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ESign StringToEnum_ESign( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ESign)(NStr::ToInt( value ));
	if ( strcmp( value, "NONE" ) == 0 || strcmp( value, "SIGN_NONE" ) == 0 )
		return SIGN_NONE;
	if ( strcmp( value, "SEND_MESSAGE_TO_CHAT" ) == 0 || strcmp( value, "SIGN_SEND_MESSAGE_TO_CHAT" ) == 0 )
		return SIGN_SEND_MESSAGE_TO_CHAT;
	if ( strcmp( value, "SEND_MESSAGE_TO_STATUS_LINE" ) == 0 || strcmp( value, "SIGN_SEND_MESSAGE_TO_STATUS_LINE" ) == 0 )
		return SIGN_SEND_MESSAGE_TO_STATUS_LINE;
	if ( strcmp( value, "PLAY_SOUND" ) == 0 || strcmp( value, "SIGN_PLAY_SOUND" ) == 0 )
		return SIGN_PLAY_SOUND;
	if ( strcmp( value, "FLYOFF_TEXT" ) == 0 || strcmp( value, "SIGN_FLYOFF_TEXT" ) == 0 )
		return SIGN_FLYOFF_TEXT;
	if ( strcmp( value, "ANNOUNCEMENT" ) == 0 || strcmp( value, "SIGN_ANNOUNCEMENT" ) == 0 )
		return SIGN_ANNOUNCEMENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ESign", value ) );
	return SIGN_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStat value )
{
	switch( value )
	{
		case STAT_LIFE:
			return "Life";
		case STAT_ENERGY:
			return "Energy";
		case STAT_RANGE:
			return "Range";
		case STAT_MOVESPEED:
			return "MoveSpeed";
		case STAT_ATTACKSPEED:
			return "AttackSpeed";
		case STAT_CRITICALCHANCE:
			return "CriticalChance";
		case STAT_CRITICALMULTIPLIER:
			return "CriticalMultiplier";
		case STAT_LIFEDRAIN:
			return "LifeDrain";
		case STAT_ENERGYDRAIN:
			return "EnergyDrain";
		case STAT_EVASION:
			return "Evasion";
		case STAT_LIFEREGENERATION:
			return "LifeRegeneration";
		case STAT_LIFEREGENERATIONABSOLUTE:
			return "LifeRegenerationAbsolute";
		case STAT_ENERGYREGENERATION:
			return "EnergyRegeneration";
		case STAT_ENERGYREGENERATIONABSOLUTE:
			return "EnergyRegenerationAbsolute";
		case STAT_VISIBILITYRANGE:
			return "VisibilityRange";
		case STAT_STRENGTH:
			return "Strength";
		case STAT_INTELLECT:
			return "Intellect";
		case STAT_DEXTERITY:
			return "Dexterity";
		case STAT_BASEATTACK:
			return "BaseAttack";
		case STAT_STAMINA:
			return "Stamina";
		case STAT_WILL:
			return "Will";
		case STAT_VIRTUALSTAT:
			return "VirtualStat";
		case STAT_CRITCHANCEBONUS:
			return "CritChanceBonus";
		case STAT_ENERGYDAMAGEDECREASE:
			return "EnergyDamageDecrease";
		case STAT_MATERIALDAMAGEDECREASE:
			return "MaterialDamageDecrease";
		case STAT_MISSCHANCE:
			return "MissChance";
		case STAT_LEVEL:
			return "Level";
		case STAT_NAFTAFORKILL:
			return "NaftaForKill";
		case STAT_NAFTAFORASSIST:
			return "NaftaForAssist";
		case STAT_NAFTASPECFORKILL:
			return "NaftaSpecForKill";
		case STAT_TEAMNAFTAFORKILL:
			return "TeamNaftaForKill";
		case STAT_TEAMNAFTAFORPRESENCE:
			return "TeamNaftaForPresence";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStat", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStat StringToEnum_EStat( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStat)(NStr::ToInt( value ));
	if ( strcmp( value, "Life" ) == 0 || strcmp( value, "STAT_LIFE" ) == 0 )
		return STAT_LIFE;
	if ( strcmp( value, "Energy" ) == 0 || strcmp( value, "STAT_ENERGY" ) == 0 )
		return STAT_ENERGY;
	if ( strcmp( value, "Range" ) == 0 || strcmp( value, "STAT_RANGE" ) == 0 )
		return STAT_RANGE;
	if ( strcmp( value, "MoveSpeed" ) == 0 || strcmp( value, "STAT_MOVESPEED" ) == 0 )
		return STAT_MOVESPEED;
	if ( strcmp( value, "AttackSpeed" ) == 0 || strcmp( value, "STAT_ATTACKSPEED" ) == 0 )
		return STAT_ATTACKSPEED;
	if ( strcmp( value, "CriticalChance" ) == 0 || strcmp( value, "STAT_CRITICALCHANCE" ) == 0 )
		return STAT_CRITICALCHANCE;
	if ( strcmp( value, "CriticalMultiplier" ) == 0 || strcmp( value, "STAT_CRITICALMULTIPLIER" ) == 0 )
		return STAT_CRITICALMULTIPLIER;
	if ( strcmp( value, "LifeDrain" ) == 0 || strcmp( value, "STAT_LIFEDRAIN" ) == 0 )
		return STAT_LIFEDRAIN;
	if ( strcmp( value, "EnergyDrain" ) == 0 || strcmp( value, "STAT_ENERGYDRAIN" ) == 0 )
		return STAT_ENERGYDRAIN;
	if ( strcmp( value, "Evasion" ) == 0 || strcmp( value, "STAT_EVASION" ) == 0 )
		return STAT_EVASION;
	if ( strcmp( value, "LifeRegeneration" ) == 0 || strcmp( value, "STAT_LIFEREGENERATION" ) == 0 )
		return STAT_LIFEREGENERATION;
	if ( strcmp( value, "LifeRegenerationAbsolute" ) == 0 || strcmp( value, "STAT_LIFEREGENERATIONABSOLUTE" ) == 0 )
		return STAT_LIFEREGENERATIONABSOLUTE;
	if ( strcmp( value, "EnergyRegeneration" ) == 0 || strcmp( value, "STAT_ENERGYREGENERATION" ) == 0 )
		return STAT_ENERGYREGENERATION;
	if ( strcmp( value, "EnergyRegenerationAbsolute" ) == 0 || strcmp( value, "STAT_ENERGYREGENERATIONABSOLUTE" ) == 0 )
		return STAT_ENERGYREGENERATIONABSOLUTE;
	if ( strcmp( value, "VisibilityRange" ) == 0 || strcmp( value, "STAT_VISIBILITYRANGE" ) == 0 )
		return STAT_VISIBILITYRANGE;
	if ( strcmp( value, "Strength" ) == 0 || strcmp( value, "STAT_STRENGTH" ) == 0 )
		return STAT_STRENGTH;
	if ( strcmp( value, "Intellect" ) == 0 || strcmp( value, "STAT_INTELLECT" ) == 0 )
		return STAT_INTELLECT;
	if ( strcmp( value, "Dexterity" ) == 0 || strcmp( value, "STAT_DEXTERITY" ) == 0 )
		return STAT_DEXTERITY;
	if ( strcmp( value, "BaseAttack" ) == 0 || strcmp( value, "STAT_BASEATTACK" ) == 0 )
		return STAT_BASEATTACK;
	if ( strcmp( value, "Stamina" ) == 0 || strcmp( value, "STAT_STAMINA" ) == 0 )
		return STAT_STAMINA;
	if ( strcmp( value, "Will" ) == 0 || strcmp( value, "STAT_WILL" ) == 0 )
		return STAT_WILL;
	if ( strcmp( value, "VirtualStat" ) == 0 || strcmp( value, "STAT_VIRTUALSTAT" ) == 0 )
		return STAT_VIRTUALSTAT;
	if ( strcmp( value, "CritChanceBonus" ) == 0 || strcmp( value, "STAT_CRITCHANCEBONUS" ) == 0 )
		return STAT_CRITCHANCEBONUS;
	if ( strcmp( value, "EnergyDamageDecrease" ) == 0 || strcmp( value, "STAT_ENERGYDAMAGEDECREASE" ) == 0 )
		return STAT_ENERGYDAMAGEDECREASE;
	if ( strcmp( value, "MaterialDamageDecrease" ) == 0 || strcmp( value, "STAT_MATERIALDAMAGEDECREASE" ) == 0 )
		return STAT_MATERIALDAMAGEDECREASE;
	if ( strcmp( value, "MissChance" ) == 0 || strcmp( value, "STAT_MISSCHANCE" ) == 0 )
		return STAT_MISSCHANCE;
	if ( strcmp( value, "Level" ) == 0 || strcmp( value, "STAT_LEVEL" ) == 0 )
		return STAT_LEVEL;
	if ( strcmp( value, "NaftaForKill" ) == 0 || strcmp( value, "STAT_NAFTAFORKILL" ) == 0 )
		return STAT_NAFTAFORKILL;
	if ( strcmp( value, "NaftaForAssist" ) == 0 || strcmp( value, "STAT_NAFTAFORASSIST" ) == 0 )
		return STAT_NAFTAFORASSIST;
	if ( strcmp( value, "NaftaSpecForKill" ) == 0 || strcmp( value, "STAT_NAFTASPECFORKILL" ) == 0 )
		return STAT_NAFTASPECFORKILL;
	if ( strcmp( value, "TeamNaftaForKill" ) == 0 || strcmp( value, "STAT_TEAMNAFTAFORKILL" ) == 0 )
		return STAT_TEAMNAFTAFORKILL;
	if ( strcmp( value, "TeamNaftaForPresence" ) == 0 || strcmp( value, "STAT_TEAMNAFTAFORPRESENCE" ) == 0 )
		return STAT_TEAMNAFTAFORPRESENCE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStat", value ) );
	return STAT_LIFE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EStatOwner value )
{
	switch( value )
	{
		case STATOWNER_NONE:
			return "None";
		case STATOWNER_CREATURE:
			return "Creature";
		case STATOWNER_ENEMYCREATURE:
			return "EnemyCreature";
		case STATOWNER_ENEMYHERO:
			return "EnemyHero";
		case STATOWNER_HERO:
			return "Hero";
		case STATOWNER_PLAYER:
			return "Player";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EStatOwner", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EStatOwner StringToEnum_EStatOwner( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EStatOwner)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "STATOWNER_NONE" ) == 0 )
		return STATOWNER_NONE;
	if ( strcmp( value, "Creature" ) == 0 || strcmp( value, "STATOWNER_CREATURE" ) == 0 )
		return STATOWNER_CREATURE;
	if ( strcmp( value, "EnemyCreature" ) == 0 || strcmp( value, "STATOWNER_ENEMYCREATURE" ) == 0 )
		return STATOWNER_ENEMYCREATURE;
	if ( strcmp( value, "EnemyHero" ) == 0 || strcmp( value, "STATOWNER_ENEMYHERO" ) == 0 )
		return STATOWNER_ENEMYHERO;
	if ( strcmp( value, "Hero" ) == 0 || strcmp( value, "STATOWNER_HERO" ) == 0 )
		return STATOWNER_HERO;
	if ( strcmp( value, "Player" ) == 0 || strcmp( value, "STATOWNER_PLAYER" ) == 0 )
		return STATOWNER_PLAYER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EStatOwner", value ) );
	return STATOWNER_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ETerrainType value )
{
	switch( value )
	{
		case TERRAINTYPE_PLAINS:
			return "Plains";
		case TERRAINTYPE_SWAMP:
			return "Swamp";
		case TERRAINTYPE_DESERT:
			return "Desert";
		case TERRAINTYPE_ROCK:
			return "Rock";
		case TERRAINTYPE_WATER:
			return "Water";
		case TERRAINTYPE_ROAD:
			return "Road";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ETerrainType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ETerrainType StringToEnum_ETerrainType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ETerrainType)(NStr::ToInt( value ));
	if ( strcmp( value, "Plains" ) == 0 || strcmp( value, "TERRAINTYPE_PLAINS" ) == 0 )
		return TERRAINTYPE_PLAINS;
	if ( strcmp( value, "Swamp" ) == 0 || strcmp( value, "TERRAINTYPE_SWAMP" ) == 0 )
		return TERRAINTYPE_SWAMP;
	if ( strcmp( value, "Desert" ) == 0 || strcmp( value, "TERRAINTYPE_DESERT" ) == 0 )
		return TERRAINTYPE_DESERT;
	if ( strcmp( value, "Rock" ) == 0 || strcmp( value, "TERRAINTYPE_ROCK" ) == 0 )
		return TERRAINTYPE_ROCK;
	if ( strcmp( value, "Water" ) == 0 || strcmp( value, "TERRAINTYPE_WATER" ) == 0 )
		return TERRAINTYPE_WATER;
	if ( strcmp( value, "Road" ) == 0 || strcmp( value, "TERRAINTYPE_ROAD" ) == 0 )
		return TERRAINTYPE_ROAD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ETerrainType", value ) );
	return TERRAINTYPE_PLAINS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EVisualStyle value )
{
	switch( value )
	{
		case VISUALSTYLE_ALWAYS:
			return "Always";
		case VISUALSTYLE_CHANGED:
			return "Changed";
		case VISUALSTYLE_DONTSHOW:
			return "DontShow";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EVisualStyle", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EVisualStyle StringToEnum_EVisualStyle( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EVisualStyle)(NStr::ToInt( value ));
	if ( strcmp( value, "Always" ) == 0 || strcmp( value, "VISUALSTYLE_ALWAYS" ) == 0 )
		return VISUALSTYLE_ALWAYS;
	if ( strcmp( value, "Changed" ) == 0 || strcmp( value, "VISUALSTYLE_CHANGED" ) == 0 )
		return VISUALSTYLE_CHANGED;
	if ( strcmp( value, "DontShow" ) == 0 || strcmp( value, "VISUALSTYLE_DONTSHOW" ) == 0 )
		return VISUALSTYLE_DONTSHOW;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EVisualStyle", value ) );
	return VISUALSTYLE_ALWAYS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const GuildShopCategoryType value )
{
	switch( value )
	{
		case GUILDSHOPCATEGORYTYPE_CLANBUFS:
			return "ClanBufs";
		case GUILDSHOPCATEGORYTYPE_PLAYERBUFS:
			return "PlayerBufs";
		case GUILDSHOPCATEGORYTYPE_SKINSANDFLAGS:
			return "SkinsAndFlags";
		case GUILDSHOPCATEGORYTYPE_PRODUCTIONBONUS:
			return "ProductionBonus";
		case GUILDSHOPCATEGORYTYPE_TALENTS:
			return "Talents";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum GuildShopCategoryType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GuildShopCategoryType StringToEnum_GuildShopCategoryType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (GuildShopCategoryType)(NStr::ToInt( value ));
	if ( strcmp( value, "ClanBufs" ) == 0 || strcmp( value, "GUILDSHOPCATEGORYTYPE_CLANBUFS" ) == 0 )
		return GUILDSHOPCATEGORYTYPE_CLANBUFS;
	if ( strcmp( value, "PlayerBufs" ) == 0 || strcmp( value, "GUILDSHOPCATEGORYTYPE_PLAYERBUFS" ) == 0 )
		return GUILDSHOPCATEGORYTYPE_PLAYERBUFS;
	if ( strcmp( value, "SkinsAndFlags" ) == 0 || strcmp( value, "GUILDSHOPCATEGORYTYPE_SKINSANDFLAGS" ) == 0 )
		return GUILDSHOPCATEGORYTYPE_SKINSANDFLAGS;
	if ( strcmp( value, "ProductionBonus" ) == 0 || strcmp( value, "GUILDSHOPCATEGORYTYPE_PRODUCTIONBONUS" ) == 0 )
		return GUILDSHOPCATEGORYTYPE_PRODUCTIONBONUS;
	if ( strcmp( value, "Talents" ) == 0 || strcmp( value, "GUILDSHOPCATEGORYTYPE_TALENTS" ) == 0 )
		return GUILDSHOPCATEGORYTYPE_TALENTS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum GuildShopCategoryType", value ) );
	return GUILDSHOPCATEGORYTYPE_CLANBUFS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const PhraseTerminateEvent value )
{
	switch( value )
	{
		case PHRASETERMINATEEVENT_PRESSKEY:
			return "PressKey";
		case PHRASETERMINATEEVENT_TIME:
			return "Time";
		case PHRASETERMINATEEVENT_TIMEANDKEY:
			return "TimeAndKey";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum PhraseTerminateEvent", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PhraseTerminateEvent StringToEnum_PhraseTerminateEvent( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PhraseTerminateEvent)(NStr::ToInt( value ));
	if ( strcmp( value, "PressKey" ) == 0 || strcmp( value, "PHRASETERMINATEEVENT_PRESSKEY" ) == 0 )
		return PHRASETERMINATEEVENT_PRESSKEY;
	if ( strcmp( value, "Time" ) == 0 || strcmp( value, "PHRASETERMINATEEVENT_TIME" ) == 0 )
		return PHRASETERMINATEEVENT_TIME;
	if ( strcmp( value, "TimeAndKey" ) == 0 || strcmp( value, "PHRASETERMINATEEVENT_TIMEANDKEY" ) == 0 )
		return PHRASETERMINATEEVENT_TIMEANDKEY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PhraseTerminateEvent", value ) );
	return PHRASETERMINATEEVENT_PRESSKEY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const PortretOrientation value )
{
	switch( value )
	{
		case PORTRETORIENTATION_LEFT:
			return "Left";
		case PORTRETORIENTATION_RIGHT:
			return "Right";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum PortretOrientation", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PortretOrientation StringToEnum_PortretOrientation( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PortretOrientation)(NStr::ToInt( value ));
	if ( strcmp( value, "Left" ) == 0 || strcmp( value, "PORTRETORIENTATION_LEFT" ) == 0 )
		return PORTRETORIENTATION_LEFT;
	if ( strcmp( value, "Right" ) == 0 || strcmp( value, "PORTRETORIENTATION_RIGHT" ) == 0 )
		return PORTRETORIENTATION_RIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PortretOrientation", value ) );
	return PORTRETORIENTATION_LEFT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbuseSettings::AbuseSettings() :
		cooldownTime( 15.0f )
	, maxUsagesPerPeriod( 6 )
	, period( 3.0f )
	, maxUsagesPerRestrictedPeriod( 1 )
	, restrictedPeriod( 3.0f )
	, refreshRestrictedPeriod( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbuseSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cooldownTime );
	saver.Add( 3, &maxUsagesPerPeriod );
	saver.Add( 4, &period );
	saver.Add( 5, &maxUsagesPerRestrictedPeriod );
	saver.Add( 6, &restrictedPeriod );
	saver.Add( 7, &refreshRestrictedPeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AbuseSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "cooldownTime", &cooldownTime );
	saver.Add( "maxUsagesPerPeriod", &maxUsagesPerPeriod );
	saver.Add( "period", &period );
	saver.Add( "maxUsagesPerRestrictedPeriod", &maxUsagesPerRestrictedPeriod );
	saver.Add( "restrictedPeriod", &restrictedPeriod );
	saver.Add( "refreshRestrictedPeriod", &refreshRestrictedPeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievBossSlayerData::AchievBossSlayerData() :
		perAchievementScore( 0 )
	, limit( 0 )
	, mode( BOSSSLAYERACHIEVMODE_ONLYFORKILLER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBossSlayerData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boss );
	saver.Add( 3, &name );
	saver.Add( 4, &perAchievementScore );
	saver.Add( 5, &limit );
	saver.Add( 6, &tooltip );
	saver.Add( 7, &image );
	saver.Add( 8, &evUI );
	saver.Add( 9, &mode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBossSlayerData::operator&( IXmlSaver &saver )
{
	saver.Add( "boss", &boss );
	saver.Add( "name", &name );
	saver.Add( "perAchievementScore", &perAchievementScore );
	saver.Add( "limit", &limit );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "image", &image );
	saver.Add( "evUI", &evUI );
	saver.Add( "mode", &mode );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnnouncementDescription::AnnouncementDescription() :
		lifeTime( 3.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnnouncementDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &textMessage );
	saver.Add( 3, &lifeTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnnouncementDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "textMessage", &textMessage );
	saver.Add( "lifeTime", &lifeTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttackType::AttackType()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackType::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statName );
	saver.Add( 3, &phisicalAttackName );
	saver.Add( 4, &energyAttackName );
	saver.Add( 5, &pureAttackName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AttackType::operator&( IXmlSaver &saver )
{
	saver.Add( "statName", &statName );
	saver.Add( "phisicalAttackName", &phisicalAttackName );
	saver.Add( "energyAttackName", &energyAttackName );
	saver.Add( "pureAttackName", &pureAttackName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BattleStartAnnouncementParams::BattleStartAnnouncementParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BattleStartAnnouncementParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &imageBurn );
	saver.Add( 3, &imageFreeze );
	saver.Add( 4, &announcementText );
	saver.Add( 5, &battleStartSound );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BattleStartAnnouncementParams::operator&( IXmlSaver &saver )
{
	saver.Add( "imageBurn", &imageBurn );
	saver.Add( "imageFreeze", &imageFreeze );
	saver.Add( "announcementText", &announcementText );
	saver.Add( "battleStartSound", &battleStartSound );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HotkeyBind::HotkeyBind() :
		bindFactor( 0.0f )
	, isHelperKey( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HotkeyBind::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &bindKey );
	saver.Add( 4, &dependentBindKey );
	saver.Add( 5, &bindFactor );
	saver.Add( 6, &isHelperKey );
	saver.Add( 7, &tooltip );
	saver.Add( 8, &category );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HotkeyBind::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "bindKey", &bindKey );
	saver.Add( "dependentBindKey", &dependentBindKey );
	saver.Add( "bindFactor", &bindFactor );
	saver.Add( "isHelperKey", &isHelperKey );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "category", &category );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CountryFlag::CountryFlag()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountryFlag::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &icon );
	saver.Add( 4, &name );
	saver.Add( 5, &countryCode );
	saver.Add( 6, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CountryFlag::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "icon", &icon );
	saver.Add( "name", &name );
	saver.Add( "countryCode", &countryCode );
	saver.Add( "tooltip", &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CharStatTooltips::CharStatTooltips()
{
	baseStatTooltips.resize( 32 );
	derivativeStatTooltips.resize( 13 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CharStatTooltips::operator&( IBinSaver &saver )
{
	saver.Add( 2, &baseStatTooltips );
	saver.Add( 3, &derivativeStatTooltips );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CharStatTooltips::operator&( IXmlSaver &saver )
{
	baseStatTooltips.resize( 32 );
	saver.Add( "baseStatTooltips", &baseStatTooltips );
	derivativeStatTooltips.resize( 13 );
	saver.Add( "derivativeStatTooltips", &derivativeStatTooltips );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChatChannelDescription::ChatChannelDescription() :
		showChannelName( false )
	, showPlayerName( false )
	, showBlinkOnMessage( true )
	, clearMessagesOnLeave( true )
	, spamInGlobalChannel( true )
	, cooldownOnSpam( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChatChannelDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &channelName );
	saver.Add( 3, &channelColor );
	saver.Add( 4, &castleChannelName );
	saver.Add( 5, &castleChannelColor );
	saver.Add( 6, &showChannelName );
	saver.Add( 7, &showPlayerName );
	saver.Add( 8, &chatChannelIconA );
	saver.Add( 9, &chatChannelIconB );
	saver.Add( 10, &showBlinkOnMessage );
	saver.Add( 11, &shortcuts );
	saver.Add( 12, &clearMessagesOnLeave );
	saver.Add( 13, &spamInGlobalChannel );
	saver.Add( 14, &cooldownOnSpam );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChatChannelDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "channelName", &channelName );
	saver.Add( "channelColor", &channelColor );
	saver.Add( "castleChannelName", &castleChannelName );
	saver.Add( "castleChannelColor", &castleChannelColor );
	saver.Add( "showChannelName", &showChannelName );
	saver.Add( "showPlayerName", &showPlayerName );
	saver.Add( "chatChannelIconA", &chatChannelIconA );
	saver.Add( "chatChannelIconB", &chatChannelIconB );
	saver.Add( "showBlinkOnMessage", &showBlinkOnMessage );
	saver.Add( "shortcuts", &shortcuts );
	saver.Add( "clearMessagesOnLeave", &clearMessagesOnLeave );
	saver.Add( "spamInGlobalChannel", &spamInGlobalChannel );
	saver.Add( "cooldownOnSpam", &cooldownOnSpam );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CombatStatuses::CombatStatuses()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CombatStatuses::operator&( IBinSaver &saver )
{
	saver.Add( 2, &replaySpeed );
	saver.Add( 3, &replayPause );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CombatStatuses::operator&( IXmlSaver &saver )
{
	saver.Add( "replaySpeed", &replaySpeed );
	saver.Add( "replayPause", &replayPause );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BotDefaultFlags::BotDefaultFlags()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BotDefaultFlags::operator&( IBinSaver &saver )
{
	saver.Add( 2, &adornianDefaultFlag );
	saver.Add( 3, &doctDefaultFlag );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BotDefaultFlags::operator&( IXmlSaver &saver )
{
	saver.Add( "adornianDefaultFlag", &adornianDefaultFlag );
	saver.Add( "doctDefaultFlag", &doctDefaultFlag );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DamageBloodMaskParams::DamageBloodMaskParams() :
		lowHealthAlpha( 0.2f )
	, nearDeathAlpha( 0.4f )
	, lowHealthLevel( 0.33f )
	, nearDeathLevel( 0.16f )
	, lowHealthSaturation( 0.5f )
	, nearDeathSaturation( 0.2f )
	, afterDeathSaturation( 0.0f )
	, afterLoseSaturation( 0.3f )
	, saturationChangeSpeed( 0.3333333f )
	, saturationChangeSpeedAfterLose( 0.1111111f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageBloodMaskParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &alphaCurve );
	saver.Add( 3, &lowHealthAlpha );
	saver.Add( 4, &nearDeathAlpha );
	saver.Add( 5, &lowHealthLevel );
	saver.Add( 6, &nearDeathLevel );
	saver.Add( 7, &lowHealthSaturation );
	saver.Add( 8, &nearDeathSaturation );
	saver.Add( 9, &afterDeathSaturation );
	saver.Add( 10, &afterLoseSaturation );
	saver.Add( 11, &saturationChangeSpeed );
	saver.Add( 12, &saturationChangeSpeedAfterLose );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DamageBloodMaskParams::operator&( IXmlSaver &saver )
{
	saver.Add( "alphaCurve", &alphaCurve );
	saver.Add( "lowHealthAlpha", &lowHealthAlpha );
	saver.Add( "nearDeathAlpha", &nearDeathAlpha );
	saver.Add( "lowHealthLevel", &lowHealthLevel );
	saver.Add( "nearDeathLevel", &nearDeathLevel );
	saver.Add( "lowHealthSaturation", &lowHealthSaturation );
	saver.Add( "nearDeathSaturation", &nearDeathSaturation );
	saver.Add( "afterDeathSaturation", &afterDeathSaturation );
	saver.Add( "afterLoseSaturation", &afterLoseSaturation );
	saver.Add( "saturationChangeSpeed", &saturationChangeSpeed );
	saver.Add( "saturationChangeSpeedAfterLose", &saturationChangeSpeedAfterLose );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DampSmoothing::DampSmoothing() :
		dampTimeObserv( 0.4f )
	, dampTimeMove( 0.2f )
	, anchorShiftObserv( 2.5f )
	, projCorretionShiftObservMaxZoom( 2.2f )
	, projCorretionShiftObservMinZoom( 0.0f )
	, firstJumpTime( 0.2f )
	, zoomFactorMove( 0.1f )
	, zoomFactorObserv( 0.7f )
	, maxSpeed( 60.0f )
	, timeToMaxSpeed( 3.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DampSmoothing::operator&( IBinSaver &saver )
{
	saver.Add( 2, &dampTimeObserv );
	saver.Add( 3, &dampTimeMove );
	saver.Add( 4, &anchorShiftObserv );
	saver.Add( 5, &projCorretionShiftObservMaxZoom );
	saver.Add( 6, &projCorretionShiftObservMinZoom );
	saver.Add( 7, &firstJumpTime );
	saver.Add( 8, &zoomFactorMove );
	saver.Add( 9, &zoomFactorObserv );
	saver.Add( 10, &maxSpeed );
	saver.Add( 11, &timeToMaxSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DampSmoothing::operator&( IXmlSaver &saver )
{
	saver.Add( "dampTimeObserv", &dampTimeObserv );
	saver.Add( "dampTimeMove", &dampTimeMove );
	saver.Add( "anchorShiftObserv", &anchorShiftObserv );
	saver.Add( "projCorretionShiftObservMaxZoom", &projCorretionShiftObservMaxZoom );
	saver.Add( "projCorretionShiftObservMinZoom", &projCorretionShiftObservMinZoom );
	saver.Add( "firstJumpTime", &firstJumpTime );
	saver.Add( "zoomFactorMove", &zoomFactorMove );
	saver.Add( "zoomFactorObserv", &zoomFactorObserv );
	saver.Add( "maxSpeed", &maxSpeed );
	saver.Add( "timeToMaxSpeed", &timeToMaxSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DialogsSettings::DialogsSettings() :
		defaultPhraseDuration( 30.0f )
	, defaultSilenceDuration( 0.0f )
	, FadeInOutPercentage( 0.4f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DialogsSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &defaultPhraseDuration );
	saver.Add( 3, &defaultSilenceDuration );
	saver.Add( 4, &FadeInOutPercentage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DialogsSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "defaultPhraseDuration", &defaultPhraseDuration );
	saver.Add( "defaultSilenceDuration", &defaultSilenceDuration );
	saver.Add( "FadeInOutPercentage", &FadeInOutPercentage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RestrictedScoring::RestrictedScoring() :
		score( 0 )
	, maxScore( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RestrictedScoring::operator&( IBinSaver &saver )
{
	saver.Add( 2, &score );
	saver.Add( 3, &maxScore );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RestrictedScoring::operator&( IXmlSaver &saver )
{
	saver.Add( "score", &score );
	saver.Add( "maxScore", &maxScore );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ErrorMessageDescription::ErrorMessageDescription() :
		shouldPlaySound( false )
	, lifeTime( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ErrorMessageDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &textMessage );
	saver.Add( 3, &shouldPlaySound );
	saver.Add( 4, &lifeTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ErrorMessageDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "textMessage", &textMessage );
	saver.Add( "shouldPlaySound", &shouldPlaySound );
	saver.Add( "lifeTime", &lifeTime );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlyOffText::FlyOffText() :
		lifeTime( 0.0f )
	, startOpacity( 0.0f )
	, endOpacity( 0.0f )
	, align( FLYOFFALIGN_LEFT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlyOffText::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lifeTime );
	saver.Add( 3, &offset );
	saver.Add( 4, &velocity );
	saver.Add( 5, &acceleration );
	saver.Add( 6, &startOpacity );
	saver.Add( 7, &endOpacity );
	saver.Add( 8, &align );
	saver.Add( 9, &layout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlyOffText::operator&( IXmlSaver &saver )
{
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "offset", &offset );
	saver.Add( "velocity", &velocity );
	saver.Add( "acceleration", &acceleration );
	saver.Add( "startOpacity", &startOpacity );
	saver.Add( "endOpacity", &endOpacity );
	saver.Add( "align", &align );
	saver.Add( "layout", &layout );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ForceColor::ForceColor() :
		force( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceColor::operator&( IBinSaver &saver )
{
	saver.Add( 2, &force );
	saver.Add( 3, &color );
	saver.Add( 4, &style );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceColor::operator&( IXmlSaver &saver )
{
	saver.Add( "force", &force );
	saver.Add( "color", &color );
	saver.Add( "style", &style );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ForceToColorTable::ForceToColorTable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceToColorTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &forceColors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ForceToColorTable::operator&( IXmlSaver &saver )
{
	saver.Add( "forceColors", &forceColors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameUIData::GameUIData()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameUIData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &gamePauseMessage );
	saver.Add( 3, &gameResumeMessage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameUIData::operator&( IXmlSaver &saver )
{
	saver.Add( "gamePauseMessage", &gamePauseMessage );
	saver.Add( "gameResumeMessage", &gameResumeMessage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildShopTab::GuildShopTab() :
		category( GUILDSHOPCATEGORYTYPE_CLANBUFS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildShopTab::operator&( IBinSaver &saver )
{
	saver.Add( 2, &category );
	saver.Add( 3, &name );
	saver.Add( 4, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildShopTab::operator&( IXmlSaver &saver )
{
	saver.Add( "category", &category );
	saver.Add( "name", &name );
	saver.Add( "tooltip", &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroTitle::HeroTitle() :
		score( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroTitle::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maleName );
	saver.Add( 3, &femaleName );
	saver.Add( 4, &tooltip );
	saver.Add( 5, &image );
	saver.Add( 6, &score );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroTitle::operator&( IXmlSaver &saver )
{
	saver.Add( "maleName", &maleName );
	saver.Add( "femaleName", &femaleName );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "image", &image );
	saver.Add( "score", &score );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Hint::Hint()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Hint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Hint::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "text", &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HintImage::HintImage()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HintImage::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Hint*)this );
	saver.Add( 2, &image );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HintImage::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (Hint*)this );
	saver.Add( "image", &image );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::Binds()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Binds::operator&( IBinSaver &saver )
{
	saver.Add( 2, &bindList );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Binds::operator&( IXmlSaver &saver )
{
	saver.Add( "bindList", &bindList );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IgnoreListParams::IgnoreListParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IgnoreListParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &outOfIgnorePlace );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IgnoreListParams::operator&( IXmlSaver &saver )
{
	saver.Add( "outOfIgnorePlace", &outOfIgnorePlace );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImpulsiveBuffsParams::ImpulsiveBuffsParams() :
		minLifeTime( 0.0f )
	, maxLifeTime( 0.0f )
	, normalBlendTime( 0.0f )
	, fastBlendTime( 0.0f )
	, cancelDelay( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minLifeTime );
	saver.Add( 3, &maxLifeTime );
	saver.Add( 4, &normalBlendTime );
	saver.Add( 5, &fastBlendTime );
	saver.Add( 6, &cancelDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ImpulsiveBuffsParams::operator&( IXmlSaver &saver )
{
	saver.Add( "minLifeTime", &minLifeTime );
	saver.Add( "maxLifeTime", &maxLifeTime );
	saver.Add( "normalBlendTime", &normalBlendTime );
	saver.Add( "fastBlendTime", &fastBlendTime );
	saver.Add( "cancelDelay", &cancelDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Locale::Locale()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locale::operator&( IBinSaver &saver )
{
	saver.Add( 2, &locale );
	saver.Add( 3, &tooltip );
	saver.Add( 4, &localeImage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Locale::operator&( IXmlSaver &saver )
{
	saver.Add( "locale", &locale );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "localeImage", &localeImage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapModeCustomDescriptions::MapModeCustomDescriptions()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapModeCustomDescriptions::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maneuvers );
	saver.Add( 3, &guardBattle );
	saver.Add( 4, &guildBattle );
	saver.Add( 5, &customBattle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapModeCustomDescriptions::operator&( IXmlSaver &saver )
{
	saver.Add( "maneuvers", &maneuvers );
	saver.Add( "guardBattle", &guardBattle );
	saver.Add( "guildBattle", &guildBattle );
	saver.Add( "customBattle", &customBattle );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MarkerSettings::MarkerSettings() :
		duration( 10.0f )
	, otherMarkersCheckRange( 100.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarkerSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &duration );
	saver.Add( 3, &otherMarkersCheckRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarkerSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "duration", &duration );
	saver.Add( "otherMarkersCheckRange", &otherMarkersCheckRange );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PathMarkerColor::PathMarkerColor()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PathMarkerColor::operator&( IBinSaver &saver )
{
	saver.Add( 2, &mul );
	saver.Add( 3, &add );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PathMarkerColor::operator&( IXmlSaver &saver )
{
	saver.Add( "mul", &mul );
	saver.Add( "add", &add );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Phrase::Phrase() :
		duration( -1.0f )
	, terminate( PHRASETERMINATEEVENT_TIME )
	, orientation( PORTRETORIENTATION_LEFT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Phrase::operator&( IBinSaver &saver )
{
	saver.Add( 2, &actorMale );
	saver.Add( 3, &actorFemale );
	saver.Add( 4, &textMale );
	saver.Add( 5, &textFemale );
	saver.Add( 6, &colorTextMale );
	saver.Add( 7, &colorTextFemale );
	saver.Add( 8, &soundMale );
	saver.Add( 9, &soundFemale );
	saver.Add( 10, &socialSoundMale );
	saver.Add( 11, &socialSoundFemale );
	saver.Add( 12, &duration );
	saver.Add( 13, &scriptName );
	saver.Add( 14, &terminate );
	saver.Add( 15, &orientation );
	saver.Add( 16, &hintImages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Phrase::operator&( IXmlSaver &saver )
{
	saver.Add( "actorMale", &actorMale );
	saver.Add( "actorFemale", &actorFemale );
	saver.Add( "textMale", &textMale );
	saver.Add( "textFemale", &textFemale );
	saver.Add( "colorTextMale", &colorTextMale );
	saver.Add( "colorTextFemale", &colorTextFemale );
	saver.Add( "soundMale", &soundMale );
	saver.Add( "soundFemale", &soundFemale );
	saver.Add( "socialSoundMale", &socialSoundMale );
	saver.Add( "socialSoundFemale", &socialSoundFemale );
	saver.Add( "duration", &duration );
	saver.Add( "scriptName", &scriptName );
	saver.Add( "terminate", &terminate );
	saver.Add( "orientation", &orientation );
	saver.Add( "hintImages", &hintImages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PingAbuseSettings::PingAbuseSettings()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PingAbuseSettings::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AbuseSettings*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PingAbuseSettings::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (AbuseSettings*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PremiumVisualInfo::PremiumVisualInfo()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumVisualInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &premiumTooltipAddition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumVisualInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "premiumTooltipAddition", &premiumTooltipAddition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PWSoundEvents::PWSoundEvents()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PWSoundEvents::operator&( IBinSaver &saver )
{
	saver.Add( 2, &selection );
	saver.Add( 3, &targetCancelled );
	saver.Add( 4, &targetSelected );
	saver.Add( 5, &minimapSignal );
	saver.Add( 6, &chatMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PWSoundEvents::operator&( IXmlSaver &saver )
{
	saver.Add( "selection", &selection );
	saver.Add( "targetCancelled", &targetCancelled );
	saver.Add( "targetSelected", &targetSelected );
	saver.Add( "minimapSignal", &minimapSignal );
	saver.Add( "chatMarker", &chatMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReportType::ReportType() :
		id( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ReportType::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &id );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ReportType::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "id", &id );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceDescription::ResourceDescription()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &resourceTooltipFreeze );
	saver.Add( 3, &resourceTooltipBurn );
	saver.Add( 4, &imageFreeze );
	saver.Add( 5, &imageBurn );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "resourceTooltipFreeze", &resourceTooltipFreeze );
	saver.Add( "resourceTooltipBurn", &resourceTooltipBurn );
	saver.Add( "imageFreeze", &imageFreeze );
	saver.Add( "imageBurn", &imageBurn );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiscreteScoring::DiscreteScoring() :
		count( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DiscreteScoring::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RestrictedScoring*)this );
	saver.Add( 2, &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DiscreteScoring::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (RestrictedScoring*)this );
	saver.Add( "count", &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScoreDescription::ScoreDescription() :
		outputPriority( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoreDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &icon );
	saver.Add( 4, &outputPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoreDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "icon", &icon );
	saver.Add( "outputPriority", &outputPriority );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionQuest::SessionQuest() :
		counter( 0 )
	, primary( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionQuest::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &text );
	saver.Add( 4, &counter );
	saver.Add( 5, &primary );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionQuest::operator&( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "text", &text );
	saver.Add( "counter", &counter );
	saver.Add( "primary", &primary );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartChatAbuseSettings::SmartChatAbuseSettings()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatAbuseSettings::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AbuseSettings*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatAbuseSettings::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (AbuseSettings*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatBudget::StatBudget() :
		stat( STAT_LIFE )
	, budget( 0.0f )
	, upgradesWithForce( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatBudget::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stat );
	saver.Add( 3, &budget );
	saver.Add( 4, &upgradesWithForce );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatBudget::operator&( IXmlSaver &saver )
{
	saver.Add( "stat", &stat );
	saver.Add( "budget", &budget );
	saver.Add( "upgradesWithForce", &upgradesWithForce );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatEnhancer::StatEnhancer() :
		statId( STAT_LIFE )
	, statAddModifier( 0.0f )
	, statMullModifier( 1.0f )
	, incrementAddModifier( 0.0f )
	, incrementMullModifier( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatEnhancer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statId );
	saver.Add( 3, &statAddModifier );
	saver.Add( 4, &statMullModifier );
	saver.Add( 5, &incrementAddModifier );
	saver.Add( 6, &incrementMullModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatEnhancer::operator&( IXmlSaver &saver )
{
	saver.Add( "statId", &statId );
	saver.Add( "statAddModifier", &statAddModifier );
	saver.Add( "statMullModifier", &statMullModifier );
	saver.Add( "incrementAddModifier", &incrementAddModifier );
	saver.Add( "incrementMullModifier", &incrementMullModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatParams::StatParams() :
		visualStyle( VISUALSTYLE_ALWAYS )
	, format( FORMATTYPE_INTEGER )
	, defValue( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &visualStyle );
	saver.Add( 4, &format );
	saver.Add( 5, &defValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatParams::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "visualStyle", &visualStyle );
	saver.Add( "format", &format );
	saver.Add( "defValue", &defValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatUpgrade::StatUpgrade() :
		level( 0 )
	, increment( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatUpgrade::operator&( IBinSaver &saver )
{
	saver.Add( 2, &level );
	saver.Add( 3, &increment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatUpgrade::operator&( IXmlSaver &saver )
{
	saver.Add( "level", &level );
	saver.Add( "increment", &increment );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StringTextRefPair::StringTextRefPair()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StringTextRefPair::operator&( IBinSaver &saver )
{
	saver.Add( 2, &key );
	saver.Add( 3, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StringTextRefPair::operator&( IXmlSaver &saver )
{
	saver.Add( "key", &key );
	saver.Add( "text", &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeamInfTooltipSettings::TeamInfTooltipSettings()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamInfTooltipSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroTooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TeamInfTooltipSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "heroTooltip", &heroTooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TipOfTheDay::TipOfTheDay()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TipOfTheDay::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tipText );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TipOfTheDay::operator&( IXmlSaver &saver )
{
	saver.Add( "tipText", &tipText );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitOvertipSettings::UnitOvertipSettings()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitOvertipSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ally );
	saver.Add( 3, &enemy );
	saver.Add( 4, &neutral );
	saver.Add( 5, &invulnerableAlly );
	saver.Add( 6, &invulnerableEnemy );
	saver.Add( 7, &localHero );
	saver.Add( 8, &localHeroSlave );
	saver.Add( 9, &invulnerableLocalHero );
	saver.Add( 10, &invulnerableLocalHeroSlave );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitOvertipSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "ally", &ally );
	saver.Add( "enemy", &enemy );
	saver.Add( "neutral", &neutral );
	saver.Add( "invulnerableAlly", &invulnerableAlly );
	saver.Add( "invulnerableEnemy", &invulnerableEnemy );
	saver.Add( "localHero", &localHero );
	saver.Add( "localHeroSlave", &localHeroSlave );
	saver.Add( "invulnerableLocalHero", &invulnerableLocalHero );
	saver.Add( "invulnerableLocalHeroSlave", &invulnerableLocalHeroSlave );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UnitStat::UnitStat() :
		statId( STAT_LIFE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitStat::operator&( IBinSaver &saver )
{
	saver.Add( 2, &value );
	saver.Add( 3, &increment );
	saver.Add( 4, &statId );
	saver.Add( 5, &levelUpgrades );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UnitStat::operator&( IXmlSaver &saver )
{
	saver.Add( "value", &value );
	saver.Add( "increment", &increment );
	saver.Add( "statId", &statId );
	saver.Add( "levelUpgrades", &levelUpgrades );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VictoryDefeatImages::VictoryDefeatImages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VictoryDefeatImages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &DefeatBurn );
	saver.Add( 3, &DefeatFreeze );
	saver.Add( 4, &VictoryBurn );
	saver.Add( 5, &VictoryFreeze );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VictoryDefeatImages::operator&( IXmlSaver &saver )
{
	saver.Add( "DefeatBurn", &DefeatBurn );
	saver.Add( "DefeatFreeze", &DefeatFreeze );
	saver.Add( "VictoryBurn", &VictoryBurn );
	saver.Add( "VictoryFreeze", &VictoryFreeze );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievBase::AchievBase() :
		achievType( ACHIEVEMENTTYPE_INVALIDACHIVEMENT )
	, perAchievementScore( 0 )
	, limit( 0 )
	, multiplier( 1.0f )
	, priority( 0 )
	, naftaAward( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBase::operator&( IBinSaver &saver )
{
	saver.Add( 2, &achievType );
	saver.Add( 3, &name );
	saver.Add( 4, &perAchievementScore );
	saver.Add( 5, &limit );
	saver.Add( 6, &multiplier );
	saver.Add( 7, &tooltip );
	saver.Add( 8, &priority );
	saver.Add( 9, &image );
	saver.Add( 10, &evUI );
	saver.Add( 11, &naftaAward );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievBase* parentPtr = (AchievBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBase::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "achievType", &achievType );
	saver.Add( "name", &name );
	saver.Add( "perAchievementScore", &perAchievementScore );
	saver.Add( "limit", &limit );
	saver.Add( "multiplier", &multiplier );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "priority", &priority );
	saver.Add( "image", &image );
	saver.Add( "evUI", &evUI );
	saver.Add( "naftaAward", &naftaAward );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBase::Assign( const AchievBase& _achievBase )
{
	achievType = _achievBase.achievType;
	name = _achievBase.name;
	perAchievementScore = _achievBase.perAchievementScore;
	limit = _achievBase.limit;
	multiplier = _achievBase.multiplier;
	tooltip = _achievBase.tooltip;
	priority = _achievBase.priority;
	image = _achievBase.image;
	evUI = _achievBase.evUI;
	naftaAward = _achievBase.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievBase::Create( NWorld::PFWorld* world ) const
{
	return ( NWorld::PFAchievBase* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievRuler::AchievRuler() :
		start( 2 )
	, step( 1 )
	, breakOnDeath( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievRuler::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &start );
	saver.Add( 3, &step );
	saver.Add( 4, &breakOnDeath );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievRuler::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievRuler* parentPtr = (AchievRuler*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievRuler::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "start", &start );
	saver.Add( "step", &step );
	saver.Add( "breakOnDeath", &breakOnDeath );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievRuler::Assign( const AchievRuler& _achievRuler )
{
	start = _achievRuler.start;
	step = _achievRuler.step;
	breakOnDeath = _achievRuler.breakOnDeath;
	achievType = _achievRuler.achievType;
	name = _achievRuler.name;
	perAchievementScore = _achievRuler.perAchievementScore;
	limit = _achievRuler.limit;
	multiplier = _achievRuler.multiplier;
	tooltip = _achievRuler.tooltip;
	priority = _achievRuler.priority;
	image = _achievRuler.image;
	evUI = _achievRuler.evUI;
	naftaAward = _achievRuler.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievRuler::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievRuler( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievAvenge::AchievAvenge() :
		timeLimit( 15 )
	, distanceLimit( 50.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAvenge::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &timeLimit );
	saver.Add( 3, &distanceLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAvenge::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievAvenge* parentPtr = (AchievAvenge*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAvenge::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "timeLimit", &timeLimit );
	saver.Add( "distanceLimit", &distanceLimit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAvenge::Assign( const AchievAvenge& _achievAvenge )
{
	timeLimit = _achievAvenge.timeLimit;
	distanceLimit = _achievAvenge.distanceLimit;
	achievType = _achievAvenge.achievType;
	name = _achievAvenge.name;
	perAchievementScore = _achievAvenge.perAchievementScore;
	limit = _achievAvenge.limit;
	multiplier = _achievAvenge.multiplier;
	tooltip = _achievAvenge.tooltip;
	priority = _achievAvenge.priority;
	image = _achievAvenge.image;
	evUI = _achievAvenge.evUI;
	naftaAward = _achievAvenge.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievAvenge::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievAvenge( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievStreak::AchievStreak() :
		start( 3 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievStreak::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &start );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievStreak::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievStreak* parentPtr = (AchievStreak*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievStreak::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "start", &start );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievStreak::Assign( const AchievStreak& _achievStreak )
{
	start = _achievStreak.start;
	achievType = _achievStreak.achievType;
	name = _achievStreak.name;
	perAchievementScore = _achievStreak.perAchievementScore;
	limit = _achievStreak.limit;
	multiplier = _achievStreak.multiplier;
	tooltip = _achievStreak.tooltip;
	priority = _achievStreak.priority;
	image = _achievStreak.image;
	evUI = _achievStreak.evUI;
	naftaAward = _achievStreak.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievStreak::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievStreak( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievBaseStrike::AchievBaseStrike() :
		minBarracks( 2 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBaseStrike::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minBarracks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBaseStrike::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievBaseStrike* parentPtr = (AchievBaseStrike*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBaseStrike::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minBarracks", &minBarracks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBaseStrike::Assign( const AchievBaseStrike& _achievBaseStrike )
{
	minBarracks = _achievBaseStrike.minBarracks;
	achievType = _achievBaseStrike.achievType;
	name = _achievBaseStrike.name;
	perAchievementScore = _achievBaseStrike.perAchievementScore;
	limit = _achievBaseStrike.limit;
	multiplier = _achievBaseStrike.multiplier;
	tooltip = _achievBaseStrike.tooltip;
	priority = _achievBaseStrike.priority;
	image = _achievBaseStrike.image;
	evUI = _achievBaseStrike.evUI;
	naftaAward = _achievBaseStrike.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievBaseStrike::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievBaseStrike( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievBorderGuard::AchievBorderGuard() :
		byTowerLifePercent( 50 )
	, timePeriod( 30 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBorderGuard::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &byTowerLifePercent );
	saver.Add( 3, &timePeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBorderGuard::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievBorderGuard* parentPtr = (AchievBorderGuard*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBorderGuard::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "byTowerLifePercent", &byTowerLifePercent );
	saver.Add( "timePeriod", &timePeriod );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBorderGuard::Assign( const AchievBorderGuard& _achievBorderGuard )
{
	byTowerLifePercent = _achievBorderGuard.byTowerLifePercent;
	timePeriod = _achievBorderGuard.timePeriod;
	achievType = _achievBorderGuard.achievType;
	name = _achievBorderGuard.name;
	perAchievementScore = _achievBorderGuard.perAchievementScore;
	limit = _achievBorderGuard.limit;
	multiplier = _achievBorderGuard.multiplier;
	tooltip = _achievBorderGuard.tooltip;
	priority = _achievBorderGuard.priority;
	image = _achievBorderGuard.image;
	evUI = _achievBorderGuard.evUI;
	naftaAward = _achievBorderGuard.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievBorderGuard::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievBorderGuard( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievBossSlayer::AchievBossSlayer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBossSlayer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &creatures );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievBossSlayer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievBossSlayer* parentPtr = (AchievBossSlayer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBossSlayer::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "creatures", &creatures );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievBossSlayer::Assign( const AchievBossSlayer& _achievBossSlayer )
{
	creatures = _achievBossSlayer.creatures;
	achievType = _achievBossSlayer.achievType;
	name = _achievBossSlayer.name;
	perAchievementScore = _achievBossSlayer.perAchievementScore;
	limit = _achievBossSlayer.limit;
	multiplier = _achievBossSlayer.multiplier;
	tooltip = _achievBossSlayer.tooltip;
	priority = _achievBossSlayer.priority;
	image = _achievBossSlayer.image;
	evUI = _achievBossSlayer.evUI;
	naftaAward = _achievBossSlayer.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievBossSlayer::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievBossSlayer( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievCeremonialKill::AchievCeremonialKill()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCeremonialKill::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCeremonialKill::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievCeremonialKill* parentPtr = (AchievCeremonialKill*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCeremonialKill::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCeremonialKill::Assign( const AchievCeremonialKill& _achievCeremonialKill )
{
	achievType = _achievCeremonialKill.achievType;
	name = _achievCeremonialKill.name;
	perAchievementScore = _achievCeremonialKill.perAchievementScore;
	limit = _achievCeremonialKill.limit;
	multiplier = _achievCeremonialKill.multiplier;
	tooltip = _achievCeremonialKill.tooltip;
	priority = _achievCeremonialKill.priority;
	image = _achievCeremonialKill.image;
	evUI = _achievCeremonialKill.evUI;
	naftaAward = _achievCeremonialKill.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievCeremonialKill::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievCeremonialKill( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievChase::AchievChase() :
		distanceMult( 0.25f )
	, timeLimit( 30 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievChase::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &distanceMult );
	saver.Add( 3, &timeLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievChase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievChase* parentPtr = (AchievChase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievChase::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "distanceMult", &distanceMult );
	saver.Add( "timeLimit", &timeLimit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievChase::Assign( const AchievChase& _achievChase )
{
	distanceMult = _achievChase.distanceMult;
	timeLimit = _achievChase.timeLimit;
	achievType = _achievChase.achievType;
	name = _achievChase.name;
	perAchievementScore = _achievChase.perAchievementScore;
	limit = _achievChase.limit;
	multiplier = _achievChase.multiplier;
	tooltip = _achievChase.tooltip;
	priority = _achievChase.priority;
	image = _achievChase.image;
	evUI = _achievChase.evUI;
	naftaAward = _achievChase.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievChase::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievChase( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievCleanUpCreeps::AchievCleanUpCreeps() :
		minCreepsKilled( 30 )
	, timePeriod( 5 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCleanUpCreeps::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minCreepsKilled );
	saver.Add( 3, &timePeriod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCleanUpCreeps::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievCleanUpCreeps* parentPtr = (AchievCleanUpCreeps*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCleanUpCreeps::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minCreepsKilled", &minCreepsKilled );
	saver.Add( "timePeriod", &timePeriod );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCleanUpCreeps::Assign( const AchievCleanUpCreeps& _achievCleanUpCreeps )
{
	minCreepsKilled = _achievCleanUpCreeps.minCreepsKilled;
	timePeriod = _achievCleanUpCreeps.timePeriod;
	achievType = _achievCleanUpCreeps.achievType;
	name = _achievCleanUpCreeps.name;
	perAchievementScore = _achievCleanUpCreeps.perAchievementScore;
	limit = _achievCleanUpCreeps.limit;
	multiplier = _achievCleanUpCreeps.multiplier;
	tooltip = _achievCleanUpCreeps.tooltip;
	priority = _achievCleanUpCreeps.priority;
	image = _achievCleanUpCreeps.image;
	evUI = _achievCleanUpCreeps.evUI;
	naftaAward = _achievCleanUpCreeps.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievCleanUpCreeps::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievCleanUpCreeps( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievClearWay::AchievClearWay() :
		minClearWayTowers( 3 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievClearWay::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minClearWayTowers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievClearWay::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievClearWay* parentPtr = (AchievClearWay*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievClearWay::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minClearWayTowers", &minClearWayTowers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievClearWay::Assign( const AchievClearWay& _achievClearWay )
{
	minClearWayTowers = _achievClearWay.minClearWayTowers;
	achievType = _achievClearWay.achievType;
	name = _achievClearWay.name;
	perAchievementScore = _achievClearWay.perAchievementScore;
	limit = _achievClearWay.limit;
	multiplier = _achievClearWay.multiplier;
	tooltip = _achievClearWay.tooltip;
	priority = _achievClearWay.priority;
	image = _achievClearWay.image;
	evUI = _achievClearWay.evUI;
	naftaAward = _achievClearWay.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievClearWay::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievClearWay( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievCraftWoman::AchievCraftWoman() :
		heartsCnt( 5.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCraftWoman::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &heartsCnt );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievCraftWoman::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievCraftWoman* parentPtr = (AchievCraftWoman*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCraftWoman::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "heartsCnt", &heartsCnt );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievCraftWoman::Assign( const AchievCraftWoman& _achievCraftWoman )
{
	heartsCnt = _achievCraftWoman.heartsCnt;
	achievType = _achievCraftWoman.achievType;
	name = _achievCraftWoman.name;
	perAchievementScore = _achievCraftWoman.perAchievementScore;
	limit = _achievCraftWoman.limit;
	multiplier = _achievCraftWoman.multiplier;
	tooltip = _achievCraftWoman.tooltip;
	priority = _achievCraftWoman.priority;
	image = _achievCraftWoman.image;
	evUI = _achievCraftWoman.evUI;
	naftaAward = _achievCraftWoman.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievCraftWoman::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievCraftWoman( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDemolishingSpree::AchievDemolishingSpree()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDemolishingSpree::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDemolishingSpree::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDemolishingSpree* parentPtr = (AchievDemolishingSpree*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDemolishingSpree::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDemolishingSpree::Assign( const AchievDemolishingSpree& _achievDemolishingSpree )
{
	start = _achievDemolishingSpree.start;
	step = _achievDemolishingSpree.step;
	breakOnDeath = _achievDemolishingSpree.breakOnDeath;
	achievType = _achievDemolishingSpree.achievType;
	name = _achievDemolishingSpree.name;
	perAchievementScore = _achievDemolishingSpree.perAchievementScore;
	limit = _achievDemolishingSpree.limit;
	multiplier = _achievDemolishingSpree.multiplier;
	tooltip = _achievDemolishingSpree.tooltip;
	priority = _achievDemolishingSpree.priority;
	image = _achievDemolishingSpree.image;
	evUI = _achievDemolishingSpree.evUI;
	naftaAward = _achievDemolishingSpree.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDemolishingSpree::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDemolishingSpree( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDominate::AchievDominate() :
		minKillsForDominate( 3 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDominate::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minKillsForDominate );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDominate::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDominate* parentPtr = (AchievDominate*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDominate::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minKillsForDominate", &minKillsForDominate );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDominate::Assign( const AchievDominate& _achievDominate )
{
	minKillsForDominate = _achievDominate.minKillsForDominate;
	achievType = _achievDominate.achievType;
	name = _achievDominate.name;
	perAchievementScore = _achievDominate.perAchievementScore;
	limit = _achievDominate.limit;
	multiplier = _achievDominate.multiplier;
	tooltip = _achievDominate.tooltip;
	priority = _achievDominate.priority;
	image = _achievDominate.image;
	evUI = _achievDominate.evUI;
	naftaAward = _achievDominate.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDominate::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDominate( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDoubleAssist::AchievDoubleAssist() :
		timeLimit( 8 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDoubleAssist::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &timeLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDoubleAssist::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDoubleAssist* parentPtr = (AchievDoubleAssist*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDoubleAssist::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "timeLimit", &timeLimit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDoubleAssist::Assign( const AchievDoubleAssist& _achievDoubleAssist )
{
	timeLimit = _achievDoubleAssist.timeLimit;
	achievType = _achievDoubleAssist.achievType;
	name = _achievDoubleAssist.name;
	perAchievementScore = _achievDoubleAssist.perAchievementScore;
	limit = _achievDoubleAssist.limit;
	multiplier = _achievDoubleAssist.multiplier;
	tooltip = _achievDoubleAssist.tooltip;
	priority = _achievDoubleAssist.priority;
	image = _achievDoubleAssist.image;
	evUI = _achievDoubleAssist.evUI;
	naftaAward = _achievDoubleAssist.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDoubleAssist::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDoubleAssist( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDoubleKill::AchievDoubleKill() :
		timeLimit( 8 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDoubleKill::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &timeLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDoubleKill::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDoubleKill* parentPtr = (AchievDoubleKill*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDoubleKill::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "timeLimit", &timeLimit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDoubleKill::Assign( const AchievDoubleKill& _achievDoubleKill )
{
	timeLimit = _achievDoubleKill.timeLimit;
	achievType = _achievDoubleKill.achievType;
	name = _achievDoubleKill.name;
	perAchievementScore = _achievDoubleKill.perAchievementScore;
	limit = _achievDoubleKill.limit;
	multiplier = _achievDoubleKill.multiplier;
	tooltip = _achievDoubleKill.tooltip;
	priority = _achievDoubleKill.priority;
	image = _achievDoubleKill.image;
	evUI = _achievDoubleKill.evUI;
	naftaAward = _achievDoubleKill.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDoubleKill::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDoubleKill( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDragonSlayer::AchievDragonSlayer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDragonSlayer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &dragons );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDragonSlayer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDragonSlayer* parentPtr = (AchievDragonSlayer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDragonSlayer::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "dragons", &dragons );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDragonSlayer::Assign( const AchievDragonSlayer& _achievDragonSlayer )
{
	dragons = _achievDragonSlayer.dragons;
	achievType = _achievDragonSlayer.achievType;
	name = _achievDragonSlayer.name;
	perAchievementScore = _achievDragonSlayer.perAchievementScore;
	limit = _achievDragonSlayer.limit;
	multiplier = _achievDragonSlayer.multiplier;
	tooltip = _achievDragonSlayer.tooltip;
	priority = _achievDragonSlayer.priority;
	image = _achievDragonSlayer.image;
	evUI = _achievDragonSlayer.evUI;
	naftaAward = _achievDragonSlayer.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDragonSlayer::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDragonSlayer( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievDuel::AchievDuel() :
		maxRestLifePercent( 10 )
	, minLifePercent( 5 )
	, timeLimit( 30 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDuel::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &maxRestLifePercent );
	saver.Add( 3, &minLifePercent );
	saver.Add( 4, &timeLimit );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievDuel::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievDuel* parentPtr = (AchievDuel*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDuel::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "maxRestLifePercent", &maxRestLifePercent );
	saver.Add( "minLifePercent", &minLifePercent );
	saver.Add( "timeLimit", &timeLimit );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievDuel::Assign( const AchievDuel& _achievDuel )
{
	maxRestLifePercent = _achievDuel.maxRestLifePercent;
	minLifePercent = _achievDuel.minLifePercent;
	timeLimit = _achievDuel.timeLimit;
	achievType = _achievDuel.achievType;
	name = _achievDuel.name;
	perAchievementScore = _achievDuel.perAchievementScore;
	limit = _achievDuel.limit;
	multiplier = _achievDuel.multiplier;
	tooltip = _achievDuel.tooltip;
	priority = _achievDuel.priority;
	image = _achievDuel.image;
	evUI = _achievDuel.evUI;
	naftaAward = _achievDuel.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievDuel::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievDuel( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievFirstAssault::AchievFirstAssault()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstAssault::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstAssault::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievFirstAssault* parentPtr = (AchievFirstAssault*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstAssault::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstAssault::Assign( const AchievFirstAssault& _achievFirstAssault )
{
	achievType = _achievFirstAssault.achievType;
	name = _achievFirstAssault.name;
	perAchievementScore = _achievFirstAssault.perAchievementScore;
	limit = _achievFirstAssault.limit;
	multiplier = _achievFirstAssault.multiplier;
	tooltip = _achievFirstAssault.tooltip;
	priority = _achievFirstAssault.priority;
	image = _achievFirstAssault.image;
	evUI = _achievFirstAssault.evUI;
	naftaAward = _achievFirstAssault.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievFirstAssault::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievFirstAssault( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievFirstBlood::AchievFirstBlood()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstBlood::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstBlood::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievFirstBlood* parentPtr = (AchievFirstBlood*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstBlood::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstBlood::Assign( const AchievFirstBlood& _achievFirstBlood )
{
	achievType = _achievFirstBlood.achievType;
	name = _achievFirstBlood.name;
	perAchievementScore = _achievFirstBlood.perAchievementScore;
	limit = _achievFirstBlood.limit;
	multiplier = _achievFirstBlood.multiplier;
	tooltip = _achievFirstBlood.tooltip;
	priority = _achievFirstBlood.priority;
	image = _achievFirstBlood.image;
	evUI = _achievFirstBlood.evUI;
	naftaAward = _achievFirstBlood.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievFirstBlood::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievFirstBlood( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievFirstMinigameComplete::AchievFirstMinigameComplete()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstMinigameComplete::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievFirstMinigameComplete::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievFirstMinigameComplete* parentPtr = (AchievFirstMinigameComplete*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstMinigameComplete::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievFirstMinigameComplete::Assign( const AchievFirstMinigameComplete& _achievFirstMinigameComplete )
{
	achievType = _achievFirstMinigameComplete.achievType;
	name = _achievFirstMinigameComplete.name;
	perAchievementScore = _achievFirstMinigameComplete.perAchievementScore;
	limit = _achievFirstMinigameComplete.limit;
	multiplier = _achievFirstMinigameComplete.multiplier;
	tooltip = _achievFirstMinigameComplete.tooltip;
	priority = _achievFirstMinigameComplete.priority;
	image = _achievFirstMinigameComplete.image;
	evUI = _achievFirstMinigameComplete.evUI;
	naftaAward = _achievFirstMinigameComplete.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievFirstMinigameComplete::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievFirstMinigameComplete( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievForestHunter::AchievForestHunter()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievForestHunter::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievForestHunter::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievForestHunter* parentPtr = (AchievForestHunter*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievForestHunter::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievForestHunter::Assign( const AchievForestHunter& _achievForestHunter )
{
	start = _achievForestHunter.start;
	step = _achievForestHunter.step;
	breakOnDeath = _achievForestHunter.breakOnDeath;
	achievType = _achievForestHunter.achievType;
	name = _achievForestHunter.name;
	perAchievementScore = _achievForestHunter.perAchievementScore;
	limit = _achievForestHunter.limit;
	multiplier = _achievForestHunter.multiplier;
	tooltip = _achievForestHunter.tooltip;
	priority = _achievForestHunter.priority;
	image = _achievForestHunter.image;
	evUI = _achievForestHunter.evUI;
	naftaAward = _achievForestHunter.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievForestHunter::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievForestHunter( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievGoldRite::AchievGoldRite()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievGoldRite::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievStreak*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievGoldRite::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievGoldRite* parentPtr = (AchievGoldRite*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievGoldRite::SerializeSelf( IXmlSaver &saver )
{
	AchievStreak::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievGoldRite::Assign( const AchievGoldRite& _achievGoldRite )
{
	start = _achievGoldRite.start;
	achievType = _achievGoldRite.achievType;
	name = _achievGoldRite.name;
	perAchievementScore = _achievGoldRite.perAchievementScore;
	limit = _achievGoldRite.limit;
	multiplier = _achievGoldRite.multiplier;
	tooltip = _achievGoldRite.tooltip;
	priority = _achievGoldRite.priority;
	image = _achievGoldRite.image;
	evUI = _achievGoldRite.evUI;
	naftaAward = _achievGoldRite.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievGoldRite::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievGoldRite( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievKillingSpree::AchievKillingSpree()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievKillingSpree::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievKillingSpree::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievKillingSpree* parentPtr = (AchievKillingSpree*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievKillingSpree::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievKillingSpree::Assign( const AchievKillingSpree& _achievKillingSpree )
{
	start = _achievKillingSpree.start;
	step = _achievKillingSpree.step;
	breakOnDeath = _achievKillingSpree.breakOnDeath;
	achievType = _achievKillingSpree.achievType;
	name = _achievKillingSpree.name;
	perAchievementScore = _achievKillingSpree.perAchievementScore;
	limit = _achievKillingSpree.limit;
	multiplier = _achievKillingSpree.multiplier;
	tooltip = _achievKillingSpree.tooltip;
	priority = _achievKillingSpree.priority;
	image = _achievKillingSpree.image;
	evUI = _achievKillingSpree.evUI;
	naftaAward = _achievKillingSpree.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievKillingSpree::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievKillingSpree( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievKittySlayer::AchievKittySlayer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievKittySlayer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &kitties );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievKittySlayer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievKittySlayer* parentPtr = (AchievKittySlayer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievKittySlayer::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "kitties", &kitties );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievKittySlayer::Assign( const AchievKittySlayer& _achievKittySlayer )
{
	kitties = _achievKittySlayer.kitties;
	achievType = _achievKittySlayer.achievType;
	name = _achievKittySlayer.name;
	perAchievementScore = _achievKittySlayer.perAchievementScore;
	limit = _achievKittySlayer.limit;
	multiplier = _achievKittySlayer.multiplier;
	tooltip = _achievKittySlayer.tooltip;
	priority = _achievKittySlayer.priority;
	image = _achievKittySlayer.image;
	evUI = _achievKittySlayer.evUI;
	naftaAward = _achievKittySlayer.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievKittySlayer::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievKittySlayer( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievLegend::AchievLegend()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievLegend::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &creatures );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievLegend::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievLegend* parentPtr = (AchievLegend*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievLegend::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "creatures", &creatures );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievLegend::Assign( const AchievLegend& _achievLegend )
{
	creatures = _achievLegend.creatures;
	achievType = _achievLegend.achievType;
	name = _achievLegend.name;
	perAchievementScore = _achievLegend.perAchievementScore;
	limit = _achievLegend.limit;
	multiplier = _achievLegend.multiplier;
	tooltip = _achievLegend.tooltip;
	priority = _achievLegend.priority;
	image = _achievLegend.image;
	evUI = _achievLegend.evUI;
	naftaAward = _achievLegend.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievLegend::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievLegend( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievMassAssist::AchievMassAssist() :
		timeLimit( 8 )
	, cnt( 4 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMassAssist::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &timeLimit );
	saver.Add( 3, &cnt );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMassAssist::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievMassAssist* parentPtr = (AchievMassAssist*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMassAssist::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "timeLimit", &timeLimit );
	saver.Add( "cnt", &cnt );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMassAssist::Assign( const AchievMassAssist& _achievMassAssist )
{
	timeLimit = _achievMassAssist.timeLimit;
	cnt = _achievMassAssist.cnt;
	achievType = _achievMassAssist.achievType;
	name = _achievMassAssist.name;
	perAchievementScore = _achievMassAssist.perAchievementScore;
	limit = _achievMassAssist.limit;
	multiplier = _achievMassAssist.multiplier;
	tooltip = _achievMassAssist.tooltip;
	priority = _achievMassAssist.priority;
	image = _achievMassAssist.image;
	evUI = _achievMassAssist.evUI;
	naftaAward = _achievMassAssist.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievMassAssist::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievMassAssist( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievMassKill::AchievMassKill() :
		timeLimit( 8 )
	, cnt( 4 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMassKill::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &timeLimit );
	saver.Add( 3, &cnt );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMassKill::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievMassKill* parentPtr = (AchievMassKill*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMassKill::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "timeLimit", &timeLimit );
	saver.Add( "cnt", &cnt );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMassKill::Assign( const AchievMassKill& _achievMassKill )
{
	timeLimit = _achievMassKill.timeLimit;
	cnt = _achievMassKill.cnt;
	achievType = _achievMassKill.achievType;
	name = _achievMassKill.name;
	perAchievementScore = _achievMassKill.perAchievementScore;
	limit = _achievMassKill.limit;
	multiplier = _achievMassKill.multiplier;
	tooltip = _achievMassKill.tooltip;
	priority = _achievMassKill.priority;
	image = _achievMassKill.image;
	evUI = _achievMassKill.evUI;
	naftaAward = _achievMassKill.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievMassKill::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievMassKill( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievMasterControl::AchievMasterControl()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMasterControl::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievMasterControl::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievMasterControl* parentPtr = (AchievMasterControl*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMasterControl::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievMasterControl::Assign( const AchievMasterControl& _achievMasterControl )
{
	start = _achievMasterControl.start;
	step = _achievMasterControl.step;
	breakOnDeath = _achievMasterControl.breakOnDeath;
	achievType = _achievMasterControl.achievType;
	name = _achievMasterControl.name;
	perAchievementScore = _achievMasterControl.perAchievementScore;
	limit = _achievMasterControl.limit;
	multiplier = _achievMasterControl.multiplier;
	tooltip = _achievMasterControl.tooltip;
	priority = _achievMasterControl.priority;
	image = _achievMasterControl.image;
	evUI = _achievMasterControl.evUI;
	naftaAward = _achievMasterControl.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievMasterControl::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievMasterControl( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievNecklaceOfGlory::AchievNecklaceOfGlory()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievNecklaceOfGlory::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievStreak*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievNecklaceOfGlory::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievNecklaceOfGlory* parentPtr = (AchievNecklaceOfGlory*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievNecklaceOfGlory::SerializeSelf( IXmlSaver &saver )
{
	AchievStreak::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievNecklaceOfGlory::Assign( const AchievNecklaceOfGlory& _achievNecklaceOfGlory )
{
	start = _achievNecklaceOfGlory.start;
	achievType = _achievNecklaceOfGlory.achievType;
	name = _achievNecklaceOfGlory.name;
	perAchievementScore = _achievNecklaceOfGlory.perAchievementScore;
	limit = _achievNecklaceOfGlory.limit;
	multiplier = _achievNecklaceOfGlory.multiplier;
	tooltip = _achievNecklaceOfGlory.tooltip;
	priority = _achievNecklaceOfGlory.priority;
	image = _achievNecklaceOfGlory.image;
	evUI = _achievNecklaceOfGlory.evUI;
	naftaAward = _achievNecklaceOfGlory.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievNecklaceOfGlory::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievNecklaceOfGlory( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievAssistingSpree::AchievAssistingSpree()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAssistingSpree::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAssistingSpree::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievAssistingSpree* parentPtr = (AchievAssistingSpree*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAssistingSpree::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAssistingSpree::Assign( const AchievAssistingSpree& _achievAssistingSpree )
{
	start = _achievAssistingSpree.start;
	step = _achievAssistingSpree.step;
	breakOnDeath = _achievAssistingSpree.breakOnDeath;
	achievType = _achievAssistingSpree.achievType;
	name = _achievAssistingSpree.name;
	perAchievementScore = _achievAssistingSpree.perAchievementScore;
	limit = _achievAssistingSpree.limit;
	multiplier = _achievAssistingSpree.multiplier;
	tooltip = _achievAssistingSpree.tooltip;
	priority = _achievAssistingSpree.priority;
	image = _achievAssistingSpree.image;
	evUI = _achievAssistingSpree.evUI;
	naftaAward = _achievAssistingSpree.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievAssistingSpree::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievAssistingSpree( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievSaviour::AchievSaviour() :
		minLifePercent( 50 )
	, damageDealedPeriod( 5 )
	, cooldownPeriod( 60 )
	, timeToLive( 5.0f )
	, timeToNoDamage( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievSaviour::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minLifePercent );
	saver.Add( 3, &damageDealedPeriod );
	saver.Add( 4, &applicatorTypes );
	saver.Add( 5, &exactApplicators );
	saver.Add( 6, &cooldownPeriod );
	saver.Add( 7, &timeToLive );
	saver.Add( 8, &timeToNoDamage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievSaviour::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievSaviour* parentPtr = (AchievSaviour*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievSaviour::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minLifePercent", &minLifePercent );
	saver.Add( "damageDealedPeriod", &damageDealedPeriod );
	saver.Add( "applicatorTypes", &applicatorTypes );
	saver.Add( "exactApplicators", &exactApplicators );
	saver.Add( "cooldownPeriod", &cooldownPeriod );
	saver.Add( "timeToLive", &timeToLive );
	saver.Add( "timeToNoDamage", &timeToNoDamage );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievSaviour::Assign( const AchievSaviour& _achievSaviour )
{
	minLifePercent = _achievSaviour.minLifePercent;
	damageDealedPeriod = _achievSaviour.damageDealedPeriod;
	applicatorTypes = _achievSaviour.applicatorTypes;
	exactApplicators = _achievSaviour.exactApplicators;
	cooldownPeriod = _achievSaviour.cooldownPeriod;
	timeToLive = _achievSaviour.timeToLive;
	timeToNoDamage = _achievSaviour.timeToNoDamage;
	achievType = _achievSaviour.achievType;
	name = _achievSaviour.name;
	perAchievementScore = _achievSaviour.perAchievementScore;
	limit = _achievSaviour.limit;
	multiplier = _achievSaviour.multiplier;
	tooltip = _achievSaviour.tooltip;
	priority = _achievSaviour.priority;
	image = _achievSaviour.image;
	evUI = _achievSaviour.evUI;
	naftaAward = _achievSaviour.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievSaviour::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievSaviour( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievSessionDuration::AchievSessionDuration() :
		minTime( 0.0f )
	, maxTime( 0.0f )
	, winners( true )
	, loosers( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievSessionDuration::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minTime );
	saver.Add( 3, &maxTime );
	saver.Add( 4, &winners );
	saver.Add( 5, &loosers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievSessionDuration::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievSessionDuration* parentPtr = (AchievSessionDuration*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievSessionDuration::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minTime", &minTime );
	saver.Add( "maxTime", &maxTime );
	saver.Add( "winners", &winners );
	saver.Add( "loosers", &loosers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievSessionDuration::Assign( const AchievSessionDuration& _achievSessionDuration )
{
	minTime = _achievSessionDuration.minTime;
	maxTime = _achievSessionDuration.maxTime;
	winners = _achievSessionDuration.winners;
	loosers = _achievSessionDuration.loosers;
	achievType = _achievSessionDuration.achievType;
	name = _achievSessionDuration.name;
	perAchievementScore = _achievSessionDuration.perAchievementScore;
	limit = _achievSessionDuration.limit;
	multiplier = _achievSessionDuration.multiplier;
	tooltip = _achievSessionDuration.tooltip;
	priority = _achievSessionDuration.priority;
	image = _achievSessionDuration.image;
	evUI = _achievSessionDuration.evUI;
	naftaAward = _achievSessionDuration.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievSessionDuration::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievSessionDuration( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievAscension::AchievAscension()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAscension::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievStreak*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievAscension::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievAscension* parentPtr = (AchievAscension*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAscension::SerializeSelf( IXmlSaver &saver )
{
	AchievStreak::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievAscension::Assign( const AchievAscension& _achievAscension )
{
	start = _achievAscension.start;
	achievType = _achievAscension.achievType;
	name = _achievAscension.name;
	perAchievementScore = _achievAscension.perAchievementScore;
	limit = _achievAscension.limit;
	multiplier = _achievAscension.multiplier;
	tooltip = _achievAscension.tooltip;
	priority = _achievAscension.priority;
	image = _achievAscension.image;
	evUI = _achievAscension.evUI;
	naftaAward = _achievAscension.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievAscension::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievAscension( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievTowerDeny::AchievTowerDeny()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievTowerDeny::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievTowerDeny::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievTowerDeny* parentPtr = (AchievTowerDeny*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievTowerDeny::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievTowerDeny::Assign( const AchievTowerDeny& _achievTowerDeny )
{
	achievType = _achievTowerDeny.achievType;
	name = _achievTowerDeny.name;
	perAchievementScore = _achievTowerDeny.perAchievementScore;
	limit = _achievTowerDeny.limit;
	multiplier = _achievTowerDeny.multiplier;
	tooltip = _achievTowerDeny.tooltip;
	priority = _achievTowerDeny.priority;
	image = _achievTowerDeny.image;
	evUI = _achievTowerDeny.evUI;
	naftaAward = _achievTowerDeny.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievTowerDeny::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievTowerDeny( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievVandalism::AchievVandalism()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievVandalism::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievVandalism::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievVandalism* parentPtr = (AchievVandalism*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievVandalism::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievVandalism::Assign( const AchievVandalism& _achievVandalism )
{
	start = _achievVandalism.start;
	step = _achievVandalism.step;
	breakOnDeath = _achievVandalism.breakOnDeath;
	achievType = _achievVandalism.achievType;
	name = _achievVandalism.name;
	perAchievementScore = _achievVandalism.perAchievementScore;
	limit = _achievVandalism.limit;
	multiplier = _achievVandalism.multiplier;
	tooltip = _achievVandalism.tooltip;
	priority = _achievVandalism.priority;
	image = _achievVandalism.image;
	evUI = _achievVandalism.evUI;
	naftaAward = _achievVandalism.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievVandalism::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievVandalism( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievVendetta::AchievVendetta() :
		minKillsForDominate( 3 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievVendetta::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievBase*)this );
	saver.Add( 2, &minKillsForDominate );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievVendetta::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievVendetta* parentPtr = (AchievVendetta*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievVendetta::SerializeSelf( IXmlSaver &saver )
{
	AchievBase::SerializeSelf( saver );
	saver.Add( "minKillsForDominate", &minKillsForDominate );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievVendetta::Assign( const AchievVendetta& _achievVendetta )
{
	minKillsForDominate = _achievVendetta.minKillsForDominate;
	achievType = _achievVendetta.achievType;
	name = _achievVendetta.name;
	perAchievementScore = _achievVendetta.perAchievementScore;
	limit = _achievVendetta.limit;
	multiplier = _achievVendetta.multiplier;
	tooltip = _achievVendetta.tooltip;
	priority = _achievVendetta.priority;
	image = _achievVendetta.image;
	evUI = _achievVendetta.evUI;
	naftaAward = _achievVendetta.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievVendetta::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievVendetta( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AchievWarLord::AchievWarLord()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievWarLord::operator&( IBinSaver &saver )
{
	saver.Add( 1, (AchievRuler*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AchievWarLord::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AchievWarLord* parentPtr = (AchievWarLord*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievWarLord::SerializeSelf( IXmlSaver &saver )
{
	AchievRuler::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AchievWarLord::Assign( const AchievWarLord& _achievWarLord )
{
	start = _achievWarLord.start;
	step = _achievWarLord.step;
	breakOnDeath = _achievWarLord.breakOnDeath;
	achievType = _achievWarLord.achievType;
	name = _achievWarLord.name;
	perAchievementScore = _achievWarLord.perAchievementScore;
	limit = _achievWarLord.limit;
	multiplier = _achievWarLord.multiplier;
	tooltip = _achievWarLord.tooltip;
	priority = _achievWarLord.priority;
	image = _achievWarLord.image;
	evUI = _achievWarLord.evUI;
	naftaAward = _achievWarLord.naftaAward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFAchievBase* AchievWarLord::Create( NWorld::PFWorld* world ) const
{
	return new NWorld::PFAchievWarLord( *this, world );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Actor::Actor()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Actor::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &icon );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Actor::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Actor* parentPtr = (Actor*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Actor::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "icon", &icon );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Actor::Assign( const Actor& _actor )
{
	name = _actor.name;
	icon = _actor.icon;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdventureCameraSettings::AdventureCameraSettings() :
		movementSpeed( 3.0f )
	, vertAngleBottom( 0.0f )
	, vertLengthBottom( 0.0f )
	, vertAngleTop( 0.0f )
	, vertLengthTop( 0.0f )
	, vertTime( 0.0f )
	, horCenterAngle( 0.0f )
	, horAngle( 0.0f )
	, horTime( 0.0f )
	, limitRadiusHor( 200.0f )
	, limitRadiusVert( 200.0f )
	, fov( 70.0f )
	, fovCorrectionAngle( 66.0f )
	, smoothRadius( 3.0f )
	, smoothDiscrete( 3 )
	, smoothDensity( 2.0f )
	, pitchRMax( 3.0f )
	, pitchRConst( 1.0f )
	, pitchDiscrete( 3 )
	, minCameraHeight( 1.0f )
	, zoomSpeed( 1.0f )
	, maxZoomFactor( 1.0f )
	, lockMultRadiusHor( 1.0f )
	, lockMultRadiusVert( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureCameraSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &movementSpeed );
	saver.Add( 4, &vertAngleBottom );
	saver.Add( 5, &vertLengthBottom );
	saver.Add( 6, &vertAngleTop );
	saver.Add( 7, &vertLengthTop );
	saver.Add( 8, &vertTime );
	saver.Add( 9, &horCenterAngle );
	saver.Add( 10, &horAngle );
	saver.Add( 11, &horTime );
	saver.Add( 12, &limitRadiusHor );
	saver.Add( 13, &limitRadiusVert );
	saver.Add( 14, &fov );
	saver.Add( 15, &fovCorrectionAngle );
	saver.Add( 16, &smoothRadius );
	saver.Add( 17, &smoothDiscrete );
	saver.Add( 18, &smoothDensity );
	saver.Add( 19, &pitchRMax );
	saver.Add( 20, &pitchRConst );
	saver.Add( 21, &pitchDiscrete );
	saver.Add( 22, &minCameraHeight );
	saver.Add( 23, &centerOffset );
	saver.Add( 24, &zoomSpeed );
	saver.Add( 25, &maxZoomFactor );
	saver.Add( 26, &lockMultRadiusHor );
	saver.Add( 27, &lockMultRadiusVert );
	saver.Add( 28, &lockCenterOffset );
	saver.Add( 29, &dampSmoothing );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureCameraSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdventureCameraSettings* parentPtr = (AdventureCameraSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureCameraSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "movementSpeed", &movementSpeed );
	saver.Add( "vertAngleBottom", &vertAngleBottom );
	saver.Add( "vertLengthBottom", &vertLengthBottom );
	saver.Add( "vertAngleTop", &vertAngleTop );
	saver.Add( "vertLengthTop", &vertLengthTop );
	saver.Add( "vertTime", &vertTime );
	saver.Add( "horCenterAngle", &horCenterAngle );
	saver.Add( "horAngle", &horAngle );
	saver.Add( "horTime", &horTime );
	saver.Add( "limitRadiusHor", &limitRadiusHor );
	saver.Add( "limitRadiusVert", &limitRadiusVert );
	saver.Add( "fov", &fov );
	saver.Add( "fovCorrectionAngle", &fovCorrectionAngle );
	saver.Add( "smoothRadius", &smoothRadius );
	saver.Add( "smoothDiscrete", &smoothDiscrete );
	saver.Add( "smoothDensity", &smoothDensity );
	saver.Add( "pitchRMax", &pitchRMax );
	saver.Add( "pitchRConst", &pitchRConst );
	saver.Add( "pitchDiscrete", &pitchDiscrete );
	saver.Add( "minCameraHeight", &minCameraHeight );
	saver.Add( "centerOffset", &centerOffset );
	saver.Add( "zoomSpeed", &zoomSpeed );
	saver.Add( "maxZoomFactor", &maxZoomFactor );
	saver.Add( "lockMultRadiusHor", &lockMultRadiusHor );
	saver.Add( "lockMultRadiusVert", &lockMultRadiusVert );
	saver.Add( "lockCenterOffset", &lockCenterOffset );
	saver.Add( "dampSmoothing", &dampSmoothing );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureCameraSettings::Assign( const AdventureCameraSettings& _adventureCameraSettings )
{
	name = _adventureCameraSettings.name;
	movementSpeed = _adventureCameraSettings.movementSpeed;
	vertAngleBottom = _adventureCameraSettings.vertAngleBottom;
	vertLengthBottom = _adventureCameraSettings.vertLengthBottom;
	vertAngleTop = _adventureCameraSettings.vertAngleTop;
	vertLengthTop = _adventureCameraSettings.vertLengthTop;
	vertTime = _adventureCameraSettings.vertTime;
	horCenterAngle = _adventureCameraSettings.horCenterAngle;
	horAngle = _adventureCameraSettings.horAngle;
	horTime = _adventureCameraSettings.horTime;
	limitRadiusHor = _adventureCameraSettings.limitRadiusHor;
	limitRadiusVert = _adventureCameraSettings.limitRadiusVert;
	fov = _adventureCameraSettings.fov;
	fovCorrectionAngle = _adventureCameraSettings.fovCorrectionAngle;
	smoothRadius = _adventureCameraSettings.smoothRadius;
	smoothDiscrete = _adventureCameraSettings.smoothDiscrete;
	smoothDensity = _adventureCameraSettings.smoothDensity;
	pitchRMax = _adventureCameraSettings.pitchRMax;
	pitchRConst = _adventureCameraSettings.pitchRConst;
	pitchDiscrete = _adventureCameraSettings.pitchDiscrete;
	minCameraHeight = _adventureCameraSettings.minCameraHeight;
	centerOffset = _adventureCameraSettings.centerOffset;
	zoomSpeed = _adventureCameraSettings.zoomSpeed;
	maxZoomFactor = _adventureCameraSettings.maxZoomFactor;
	lockMultRadiusHor = _adventureCameraSettings.lockMultRadiusHor;
	lockMultRadiusVert = _adventureCameraSettings.lockMultRadiusVert;
	lockCenterOffset = _adventureCameraSettings.lockCenterOffset;
	dampSmoothing.dampTimeObserv = _adventureCameraSettings.dampSmoothing.dampTimeObserv;
	dampSmoothing.dampTimeMove = _adventureCameraSettings.dampSmoothing.dampTimeMove;
	dampSmoothing.anchorShiftObserv = _adventureCameraSettings.dampSmoothing.anchorShiftObserv;
	dampSmoothing.projCorretionShiftObservMaxZoom = _adventureCameraSettings.dampSmoothing.projCorretionShiftObservMaxZoom;
	dampSmoothing.projCorretionShiftObservMinZoom = _adventureCameraSettings.dampSmoothing.projCorretionShiftObservMinZoom;
	dampSmoothing.firstJumpTime = _adventureCameraSettings.dampSmoothing.firstJumpTime;
	dampSmoothing.zoomFactorMove = _adventureCameraSettings.dampSmoothing.zoomFactorMove;
	dampSmoothing.zoomFactorObserv = _adventureCameraSettings.dampSmoothing.zoomFactorObserv;
	dampSmoothing.maxSpeed = _adventureCameraSettings.dampSmoothing.maxSpeed;
	dampSmoothing.timeToMaxSpeed = _adventureCameraSettings.dampSmoothing.timeToMaxSpeed;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdventureTooltipParams::AdventureTooltipParams()
{
	units.resize( 22 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureTooltipParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &units );
	saver.Add( 3, &locatorName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureTooltipParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdventureTooltipParams* parentPtr = (AdventureTooltipParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureTooltipParams::SerializeSelf( IXmlSaver &saver )
{
	units.resize( 22 );
	saver.Add( "units", &units );
	saver.Add( "locatorName", &locatorName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureTooltipParams::Assign( const AdventureTooltipParams& _adventureTooltipParams )
{
	units = _adventureTooltipParams.units;
	locatorName = _adventureTooltipParams.locatorName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdventureTooltipSettings::AdventureTooltipSettings() :
		showDesc( true )
	, stretch( ADVENTURETOOLTIPSTRETCHMODE_NONE )
	, uiState( "tooltip_layout" )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureTooltipSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &showDesc );
	saver.Add( 3, &stretch );
	saver.Add( 4, &uiState );
	saver.Add( 5, &uiStateShort );
	saver.Add( 6, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdventureTooltipSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdventureTooltipSettings* parentPtr = (AdventureTooltipSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureTooltipSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "showDesc", &showDesc );
	saver.Add( "stretch", &stretch );
	saver.Add( "uiState", &uiState );
	saver.Add( "uiStateShort", &uiStateShort );
	saver.Add( "text", &text );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdventureTooltipSettings::Assign( const AdventureTooltipSettings& _adventureTooltipSettings )
{
	showDesc = _adventureTooltipSettings.showDesc;
	stretch = _adventureTooltipSettings.stretch;
	uiState = _adventureTooltipSettings.uiState;
	uiStateShort = _adventureTooltipSettings.uiStateShort;
	text = _adventureTooltipSettings.text;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdvMapModeDescription::AdvMapModeDescription()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapModeDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &icon );
	saver.Add( 3, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AdvMapModeDescription::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AdvMapModeDescription* parentPtr = (AdvMapModeDescription*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapModeDescription::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "icon", &icon );
	saver.Add( "tooltip", &tooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdvMapModeDescription::Assign( const AdvMapModeDescription& _advMapModeDescription )
{
	icon = _advMapModeDescription.icon;
	tooltip = _advMapModeDescription.tooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BindCategory::BindCategory() :
		index( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BindCategory::operator&( IBinSaver &saver )
{
	saver.Add( 2, &index );
	saver.Add( 3, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BindCategory::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BindCategory* parentPtr = (BindCategory*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BindCategory::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "index", &index );
	saver.Add( "name", &name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BindCategory::Assign( const BindCategory& _bindCategory )
{
	index = _bindCategory.index;
	name = _bindCategory.name;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CustomFlag::CustomFlag() :
		Price( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CustomFlag::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &icon );
	saver.Add( 4, &bigIcon );
	saver.Add( 5, &name );
	saver.Add( 6, &tooltip );
	saver.Add( 7, &Price );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CustomFlag::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CustomFlag* parentPtr = (CustomFlag*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CustomFlag::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "icon", &icon );
	saver.Add( "bigIcon", &bigIcon );
	saver.Add( "name", &name );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "Price", &Price );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CustomFlag::Assign( const CustomFlag& _customFlag )
{
	id = _customFlag.id;
	icon = _customFlag.icon;
	bigIcon = _customFlag.bigIcon;
	name = _customFlag.name;
	tooltip = _customFlag.tooltip;
	Price = _customFlag.Price;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBMinimap::DBMinimap() :
		normalOpacity( 1.0f )
	, minigameOpacity( 0.2f )
	, transitionVelocity( 1.0f )
	, signalLifeTime( 5.0f )
	, targetZoneLineThickness( 2 )
{
	icons.resize( 26 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinimap::operator&( IBinSaver &saver )
{
	saver.Add( 2, &normalOpacity );
	saver.Add( 3, &minigameOpacity );
	saver.Add( 4, &transitionVelocity );
	saver.Add( 5, &signalLifeTime );
	saver.Add( 6, &signalDefaultColor );
	saver.Add( 7, &enemyColor );
	saver.Add( 8, &allyColor );
	saver.Add( 9, &neutralColor );
	saver.Add( 10, &enemyHeroFrame );
	saver.Add( 11, &allyHeroFrame );
	saver.Add( 12, &localHeroFrame );
	saver.Add( 13, &icons );
	saver.Add( 14, &targetZoneColor );
	saver.Add( 15, &targetZoneLineThickness );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinimap::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBMinimap* parentPtr = (DBMinimap*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinimap::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "normalOpacity", &normalOpacity );
	saver.Add( "minigameOpacity", &minigameOpacity );
	saver.Add( "transitionVelocity", &transitionVelocity );
	saver.Add( "signalLifeTime", &signalLifeTime );
	saver.Add( "signalDefaultColor", &signalDefaultColor );
	saver.Add( "enemyColor", &enemyColor );
	saver.Add( "allyColor", &allyColor );
	saver.Add( "neutralColor", &neutralColor );
	saver.Add( "enemyHeroFrame", &enemyHeroFrame );
	saver.Add( "allyHeroFrame", &allyHeroFrame );
	saver.Add( "localHeroFrame", &localHeroFrame );
	icons.resize( 26 );
	saver.Add( "icons", &icons );
	saver.Add( "targetZoneColor", &targetZoneColor );
	saver.Add( "targetZoneLineThickness", &targetZoneLineThickness );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinimap::Assign( const DBMinimap& _dBMinimap )
{
	normalOpacity = _dBMinimap.normalOpacity;
	minigameOpacity = _dBMinimap.minigameOpacity;
	transitionVelocity = _dBMinimap.transitionVelocity;
	signalLifeTime = _dBMinimap.signalLifeTime;
	signalDefaultColor = _dBMinimap.signalDefaultColor;
	enemyColor = _dBMinimap.enemyColor;
	allyColor = _dBMinimap.allyColor;
	neutralColor = _dBMinimap.neutralColor;
	enemyHeroFrame = _dBMinimap.enemyHeroFrame;
	allyHeroFrame = _dBMinimap.allyHeroFrame;
	localHeroFrame = _dBMinimap.localHeroFrame;
	icons = _dBMinimap.icons;
	targetZoneColor = _dBMinimap.targetZoneColor;
	targetZoneLineThickness = _dBMinimap.targetZoneLineThickness;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBStatisticData::DBStatisticData()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBStatisticData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &winnersTeamStr );
	saver.Add( 3, &losersTeamStr );
	saver.Add( 4, &levelFormatStr );
	saver.Add( 5, &favoritesFeatsStr );
	saver.Add( 6, &timeUnderBlessingStr );
	saver.Add( 7, &totalHeartsStr );
	saver.Add( 8, &heartsFromMenAndMinigamesStr );
	saver.Add( 9, &goldAndSilverFromMinigameStr );
	saver.Add( 10, &killingAssistantsStr );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBStatisticData::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBStatisticData* parentPtr = (DBStatisticData*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBStatisticData::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "winnersTeamStr", &winnersTeamStr );
	saver.Add( "losersTeamStr", &losersTeamStr );
	saver.Add( "levelFormatStr", &levelFormatStr );
	saver.Add( "favoritesFeatsStr", &favoritesFeatsStr );
	saver.Add( "timeUnderBlessingStr", &timeUnderBlessingStr );
	saver.Add( "totalHeartsStr", &totalHeartsStr );
	saver.Add( "heartsFromMenAndMinigamesStr", &heartsFromMenAndMinigamesStr );
	saver.Add( "goldAndSilverFromMinigameStr", &goldAndSilverFromMinigameStr );
	saver.Add( "killingAssistantsStr", &killingAssistantsStr );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBStatisticData::Assign( const DBStatisticData& _dBStatisticData )
{
	winnersTeamStr = _dBStatisticData.winnersTeamStr;
	losersTeamStr = _dBStatisticData.losersTeamStr;
	levelFormatStr = _dBStatisticData.levelFormatStr;
	favoritesFeatsStr = _dBStatisticData.favoritesFeatsStr;
	timeUnderBlessingStr = _dBStatisticData.timeUnderBlessingStr;
	totalHeartsStr = _dBStatisticData.totalHeartsStr;
	heartsFromMenAndMinigamesStr = _dBStatisticData.heartsFromMenAndMinigamesStr;
	goldAndSilverFromMinigameStr = _dBStatisticData.goldAndSilverFromMinigameStr;
	killingAssistantsStr = _dBStatisticData.killingAssistantsStr;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBTooltip::DBTooltip()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTooltip::operator&( IBinSaver &saver )
{
	saver.Add( 2, &friendStyle );
	saver.Add( 3, &enemyStyle );
	saver.Add( 4, &heroInfo );
	saver.Add( 5, &unitInfo );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTooltip::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBTooltip* parentPtr = (DBTooltip*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBTooltip::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "friendStyle", &friendStyle );
	saver.Add( "enemyStyle", &enemyStyle );
	saver.Add( "heroInfo", &heroInfo );
	saver.Add( "unitInfo", &unitInfo );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBTooltip::Assign( const DBTooltip& _dBTooltip )
{
	friendStyle = _dBTooltip.friendStyle;
	enemyStyle = _dBTooltip.enemyStyle;
	heroInfo = _dBTooltip.heroInfo;
	unitInfo = _dBTooltip.unitInfo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBUIData::DBUIData() :
		outlineThickness( 0.1f )
	, tooltipDownScaleLimit( 0.5f )
	, mouseScrollingFieldSize( 20.0f )
	, RecentPlayers( 20 )
{
	elements.resize( 32 );
	pathMarkerColor.resize( 2 );
	rarityValue.resize( 7 );
	errorMessageDescriptions.resize( 19 );
	chatChannelDescriptions.resize( 11 );
	resourcesDescriptions.resize( 7 );
	clanWarsResourcesDescriptions.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBUIData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &elements );
	saver.Add( 3, &combatStatuses );
	saver.Add( 4, &soundEvents );
	saver.Add( 5, &attackType );
	saver.Add( 6, &impulsiveBuffsParams );
	saver.Add( 7, &colorPreselect );
	saver.Add( 8, &outlineAllyColor );
	saver.Add( 9, &outlineHostileColor );
	saver.Add( 10, &outlineSelfColor );
	saver.Add( 11, &outlineThickness );
	saver.Add( 12, &gameUIData );
	saver.Add( 13, &pathMarkerColor );
	saver.Add( 14, &rarityValue );
	saver.Add( 15, &bloodMaskParams );
	saver.Add( 16, &errorMessageDescriptions );
	saver.Add( 17, &charStatTooltips );
	saver.Add( 18, &minimap );
	saver.Add( 19, &tooltipDownScaleLimit );
	saver.Add( 20, &battleStartAnnouncementParams );
	saver.Add( 21, &mouseScrollingFieldSize );
	saver.Add( 22, &chatChannelDescriptions );
	saver.Add( 23, &adminMessageColor );
	saver.Add( 24, &resourcesDescriptions );
	saver.Add( 25, &clanWarsResourcesDescriptions );
	saver.Add( 26, &victoryDefeatImages );
	saver.Add( 27, &ignoreListParams );
	saver.Add( 28, &markerSettings );
	saver.Add( 29, &forceColors );
	saver.Add( 30, &dialogsSettings );
	saver.Add( 31, &pingAbuseSettings );
	saver.Add( 32, &blockSaturationColor );
	saver.Add( 33, &mapModeCustomDescriptions );
	saver.Add( 34, &loadingScreenStatuses );
	saver.Add( 35, &premiumVisualInfo );
	saver.Add( 36, &locales );
	saver.Add( 37, &tips );
	saver.Add( 38, &reportTypes );
	saver.Add( 39, &binds );
	saver.Add( 40, &countryFlags );
	saver.Add( 41, &botFlags );
	saver.Add( 42, &customFlags );
	saver.Add( 43, &adminFlags );
	saver.Add( 44, &guildShopTabs );
	saver.Add( 45, &smartChat );
	saver.Add( 46, &smartChatAbuseSettings );
	saver.Add( 47, &RecentPlayers );
	saver.Add( 48, &currencies );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBUIData::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBUIData* parentPtr = (DBUIData*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBUIData::SerializeSelf( IXmlSaver &saver )
{
	elements.resize( 32 );
	saver.Add( "elements", &elements );
	saver.Add( "combatStatuses", &combatStatuses );
	saver.Add( "soundEvents", &soundEvents );
	saver.Add( "attackType", &attackType );
	saver.Add( "impulsiveBuffsParams", &impulsiveBuffsParams );
	saver.Add( "colorPreselect", &colorPreselect );
	saver.Add( "outlineAllyColor", &outlineAllyColor );
	saver.Add( "outlineHostileColor", &outlineHostileColor );
	saver.Add( "outlineSelfColor", &outlineSelfColor );
	saver.Add( "outlineThickness", &outlineThickness );
	saver.Add( "gameUIData", &gameUIData );
	pathMarkerColor.resize( 2 );
	saver.Add( "pathMarkerColor", &pathMarkerColor );
	rarityValue.resize( 7 );
	saver.Add( "rarityValue", &rarityValue );
	saver.Add( "bloodMaskParams", &bloodMaskParams );
	errorMessageDescriptions.resize( 19 );
	saver.Add( "errorMessageDescriptions", &errorMessageDescriptions );
	saver.Add( "charStatTooltips", &charStatTooltips );
	saver.Add( "minimap", &minimap );
	saver.Add( "tooltipDownScaleLimit", &tooltipDownScaleLimit );
	saver.Add( "battleStartAnnouncementParams", &battleStartAnnouncementParams );
	saver.Add( "mouseScrollingFieldSize", &mouseScrollingFieldSize );
	chatChannelDescriptions.resize( 11 );
	saver.Add( "chatChannelDescriptions", &chatChannelDescriptions );
	saver.Add( "adminMessageColor", &adminMessageColor );
	resourcesDescriptions.resize( 7 );
	saver.Add( "resourcesDescriptions", &resourcesDescriptions );
	clanWarsResourcesDescriptions.resize( 2 );
	saver.Add( "clanWarsResourcesDescriptions", &clanWarsResourcesDescriptions );
	saver.Add( "victoryDefeatImages", &victoryDefeatImages );
	saver.Add( "ignoreListParams", &ignoreListParams );
	saver.Add( "markerSettings", &markerSettings );
	saver.Add( "forceColors", &forceColors );
	saver.Add( "dialogsSettings", &dialogsSettings );
	saver.Add( "pingAbuseSettings", &pingAbuseSettings );
	saver.Add( "blockSaturationColor", &blockSaturationColor );
	saver.Add( "mapModeCustomDescriptions", &mapModeCustomDescriptions );
	saver.Add( "loadingScreenStatuses", &loadingScreenStatuses );
	saver.Add( "premiumVisualInfo", &premiumVisualInfo );
	saver.Add( "locales", &locales );
	saver.Add( "tips", &tips );
	saver.Add( "reportTypes", &reportTypes );
	saver.Add( "binds", &binds );
	saver.Add( "countryFlags", &countryFlags );
	saver.Add( "botFlags", &botFlags );
	saver.Add( "customFlags", &customFlags );
	saver.Add( "adminFlags", &adminFlags );
	saver.Add( "guildShopTabs", &guildShopTabs );
	saver.Add( "smartChat", &smartChat );
	saver.Add( "smartChatAbuseSettings", &smartChatAbuseSettings );
	saver.Add( "RecentPlayers", &RecentPlayers );
	saver.Add( "currencies", &currencies );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBUIData::Assign( const DBUIData& _dBUIData )
{
	elements = _dBUIData.elements;
	combatStatuses.replaySpeed = _dBUIData.combatStatuses.replaySpeed;
	combatStatuses.replayPause = _dBUIData.combatStatuses.replayPause;
	soundEvents.selection.projectName = _dBUIData.soundEvents.selection.projectName;
	soundEvents.selection.groupName = _dBUIData.soundEvents.selection.groupName;
	soundEvents.selection.eventName = _dBUIData.soundEvents.selection.eventName;
	soundEvents.targetCancelled.projectName = _dBUIData.soundEvents.targetCancelled.projectName;
	soundEvents.targetCancelled.groupName = _dBUIData.soundEvents.targetCancelled.groupName;
	soundEvents.targetCancelled.eventName = _dBUIData.soundEvents.targetCancelled.eventName;
	soundEvents.targetSelected.projectName = _dBUIData.soundEvents.targetSelected.projectName;
	soundEvents.targetSelected.groupName = _dBUIData.soundEvents.targetSelected.groupName;
	soundEvents.targetSelected.eventName = _dBUIData.soundEvents.targetSelected.eventName;
	soundEvents.minimapSignal.projectName = _dBUIData.soundEvents.minimapSignal.projectName;
	soundEvents.minimapSignal.groupName = _dBUIData.soundEvents.minimapSignal.groupName;
	soundEvents.minimapSignal.eventName = _dBUIData.soundEvents.minimapSignal.eventName;
	soundEvents.chatMarker.projectName = _dBUIData.soundEvents.chatMarker.projectName;
	soundEvents.chatMarker.groupName = _dBUIData.soundEvents.chatMarker.groupName;
	soundEvents.chatMarker.eventName = _dBUIData.soundEvents.chatMarker.eventName;
	attackType.statName = _dBUIData.attackType.statName;
	attackType.phisicalAttackName = _dBUIData.attackType.phisicalAttackName;
	attackType.energyAttackName = _dBUIData.attackType.energyAttackName;
	attackType.pureAttackName = _dBUIData.attackType.pureAttackName;
	impulsiveBuffsParams.minLifeTime = _dBUIData.impulsiveBuffsParams.minLifeTime;
	impulsiveBuffsParams.maxLifeTime = _dBUIData.impulsiveBuffsParams.maxLifeTime;
	impulsiveBuffsParams.normalBlendTime = _dBUIData.impulsiveBuffsParams.normalBlendTime;
	impulsiveBuffsParams.fastBlendTime = _dBUIData.impulsiveBuffsParams.fastBlendTime;
	impulsiveBuffsParams.cancelDelay = _dBUIData.impulsiveBuffsParams.cancelDelay;
	colorPreselect = _dBUIData.colorPreselect;
	outlineAllyColor = _dBUIData.outlineAllyColor;
	outlineHostileColor = _dBUIData.outlineHostileColor;
	outlineSelfColor = _dBUIData.outlineSelfColor;
	outlineThickness = _dBUIData.outlineThickness;
	gameUIData.gamePauseMessage = _dBUIData.gameUIData.gamePauseMessage;
	gameUIData.gameResumeMessage = _dBUIData.gameUIData.gameResumeMessage;
	pathMarkerColor = _dBUIData.pathMarkerColor;
	rarityValue = _dBUIData.rarityValue;
	bloodMaskParams.alphaCurve = _dBUIData.bloodMaskParams.alphaCurve;
	bloodMaskParams.lowHealthAlpha = _dBUIData.bloodMaskParams.lowHealthAlpha;
	bloodMaskParams.nearDeathAlpha = _dBUIData.bloodMaskParams.nearDeathAlpha;
	bloodMaskParams.lowHealthLevel = _dBUIData.bloodMaskParams.lowHealthLevel;
	bloodMaskParams.nearDeathLevel = _dBUIData.bloodMaskParams.nearDeathLevel;
	bloodMaskParams.lowHealthSaturation = _dBUIData.bloodMaskParams.lowHealthSaturation;
	bloodMaskParams.nearDeathSaturation = _dBUIData.bloodMaskParams.nearDeathSaturation;
	bloodMaskParams.afterDeathSaturation = _dBUIData.bloodMaskParams.afterDeathSaturation;
	bloodMaskParams.afterLoseSaturation = _dBUIData.bloodMaskParams.afterLoseSaturation;
	bloodMaskParams.saturationChangeSpeed = _dBUIData.bloodMaskParams.saturationChangeSpeed;
	bloodMaskParams.saturationChangeSpeedAfterLose = _dBUIData.bloodMaskParams.saturationChangeSpeedAfterLose;
	errorMessageDescriptions = _dBUIData.errorMessageDescriptions;
	charStatTooltips.baseStatTooltips = _dBUIData.charStatTooltips.baseStatTooltips;
	charStatTooltips.derivativeStatTooltips = _dBUIData.charStatTooltips.derivativeStatTooltips;
	minimap = _dBUIData.minimap;
	tooltipDownScaleLimit = _dBUIData.tooltipDownScaleLimit;
	battleStartAnnouncementParams.imageBurn = _dBUIData.battleStartAnnouncementParams.imageBurn;
	battleStartAnnouncementParams.imageFreeze = _dBUIData.battleStartAnnouncementParams.imageFreeze;
	battleStartAnnouncementParams.announcementText = _dBUIData.battleStartAnnouncementParams.announcementText;
	battleStartAnnouncementParams.battleStartSound.projectName = _dBUIData.battleStartAnnouncementParams.battleStartSound.projectName;
	battleStartAnnouncementParams.battleStartSound.groupName = _dBUIData.battleStartAnnouncementParams.battleStartSound.groupName;
	battleStartAnnouncementParams.battleStartSound.eventName = _dBUIData.battleStartAnnouncementParams.battleStartSound.eventName;
	mouseScrollingFieldSize = _dBUIData.mouseScrollingFieldSize;
	chatChannelDescriptions = _dBUIData.chatChannelDescriptions;
	adminMessageColor = _dBUIData.adminMessageColor;
	resourcesDescriptions = _dBUIData.resourcesDescriptions;
	clanWarsResourcesDescriptions = _dBUIData.clanWarsResourcesDescriptions;
	victoryDefeatImages.DefeatBurn = _dBUIData.victoryDefeatImages.DefeatBurn;
	victoryDefeatImages.DefeatFreeze = _dBUIData.victoryDefeatImages.DefeatFreeze;
	victoryDefeatImages.VictoryBurn = _dBUIData.victoryDefeatImages.VictoryBurn;
	victoryDefeatImages.VictoryFreeze = _dBUIData.victoryDefeatImages.VictoryFreeze;
	ignoreListParams.outOfIgnorePlace = _dBUIData.ignoreListParams.outOfIgnorePlace;
	markerSettings.duration = _dBUIData.markerSettings.duration;
	markerSettings.otherMarkersCheckRange = _dBUIData.markerSettings.otherMarkersCheckRange;
	forceColors.forceColors = _dBUIData.forceColors.forceColors;
	dialogsSettings.defaultPhraseDuration = _dBUIData.dialogsSettings.defaultPhraseDuration;
	dialogsSettings.defaultSilenceDuration = _dBUIData.dialogsSettings.defaultSilenceDuration;
	dialogsSettings.FadeInOutPercentage = _dBUIData.dialogsSettings.FadeInOutPercentage;
	pingAbuseSettings.cooldownTime = _dBUIData.pingAbuseSettings.cooldownTime;
	pingAbuseSettings.maxUsagesPerPeriod = _dBUIData.pingAbuseSettings.maxUsagesPerPeriod;
	pingAbuseSettings.period = _dBUIData.pingAbuseSettings.period;
	pingAbuseSettings.maxUsagesPerRestrictedPeriod = _dBUIData.pingAbuseSettings.maxUsagesPerRestrictedPeriod;
	pingAbuseSettings.restrictedPeriod = _dBUIData.pingAbuseSettings.restrictedPeriod;
	pingAbuseSettings.refreshRestrictedPeriod = _dBUIData.pingAbuseSettings.refreshRestrictedPeriod;
	blockSaturationColor = _dBUIData.blockSaturationColor;
	mapModeCustomDescriptions.maneuvers = _dBUIData.mapModeCustomDescriptions.maneuvers;
	mapModeCustomDescriptions.guardBattle = _dBUIData.mapModeCustomDescriptions.guardBattle;
	mapModeCustomDescriptions.guildBattle = _dBUIData.mapModeCustomDescriptions.guildBattle;
	mapModeCustomDescriptions.customBattle = _dBUIData.mapModeCustomDescriptions.customBattle;
	loadingScreenStatuses = _dBUIData.loadingScreenStatuses;
	premiumVisualInfo.premiumTooltipAddition = _dBUIData.premiumVisualInfo.premiumTooltipAddition;
	locales = _dBUIData.locales;
	tips = _dBUIData.tips;
	reportTypes = _dBUIData.reportTypes;
	binds.bindList = _dBUIData.binds.bindList;
	countryFlags = _dBUIData.countryFlags;
	botFlags.adornianDefaultFlag.id = _dBUIData.botFlags.adornianDefaultFlag.id;
	botFlags.adornianDefaultFlag.icon = _dBUIData.botFlags.adornianDefaultFlag.icon;
	botFlags.adornianDefaultFlag.name = _dBUIData.botFlags.adornianDefaultFlag.name;
	botFlags.adornianDefaultFlag.countryCode = _dBUIData.botFlags.adornianDefaultFlag.countryCode;
	botFlags.adornianDefaultFlag.tooltip = _dBUIData.botFlags.adornianDefaultFlag.tooltip;
	botFlags.doctDefaultFlag.id = _dBUIData.botFlags.doctDefaultFlag.id;
	botFlags.doctDefaultFlag.icon = _dBUIData.botFlags.doctDefaultFlag.icon;
	botFlags.doctDefaultFlag.name = _dBUIData.botFlags.doctDefaultFlag.name;
	botFlags.doctDefaultFlag.countryCode = _dBUIData.botFlags.doctDefaultFlag.countryCode;
	botFlags.doctDefaultFlag.tooltip = _dBUIData.botFlags.doctDefaultFlag.tooltip;
	customFlags = _dBUIData.customFlags;
	adminFlags = _dBUIData.adminFlags;
	guildShopTabs = _dBUIData.guildShopTabs;
	smartChat = _dBUIData.smartChat;
	smartChatAbuseSettings.cooldownTime = _dBUIData.smartChatAbuseSettings.cooldownTime;
	smartChatAbuseSettings.maxUsagesPerPeriod = _dBUIData.smartChatAbuseSettings.maxUsagesPerPeriod;
	smartChatAbuseSettings.period = _dBUIData.smartChatAbuseSettings.period;
	smartChatAbuseSettings.maxUsagesPerRestrictedPeriod = _dBUIData.smartChatAbuseSettings.maxUsagesPerRestrictedPeriod;
	smartChatAbuseSettings.restrictedPeriod = _dBUIData.smartChatAbuseSettings.restrictedPeriod;
	smartChatAbuseSettings.refreshRestrictedPeriod = _dBUIData.smartChatAbuseSettings.refreshRestrictedPeriod;
	RecentPlayers = _dBUIData.RecentPlayers;
	currencies = _dBUIData.currencies;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DerivativeStatsContainer::DerivativeStatsContainer()
{
	derivativeStats.resize( 13 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DerivativeStatsContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &derivativeStats );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DerivativeStatsContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DerivativeStatsContainer* parentPtr = (DerivativeStatsContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DerivativeStatsContainer::SerializeSelf( IXmlSaver &saver )
{
	derivativeStats.resize( 13 );
	saver.Add( "derivativeStats", &derivativeStats );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DerivativeStatsContainer::Assign( const DerivativeStatsContainer& _derivativeStatsContainer )
{
	derivativeStats = _derivativeStatsContainer.derivativeStats;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dialog::Dialog()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Dialog::operator&( IBinSaver &saver )
{
	saver.Add( 2, &id );
	saver.Add( 3, &title );
	saver.Add( 4, &phrasesA );
	saver.Add( 5, &phrasesB );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Dialog::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Dialog* parentPtr = (Dialog*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dialog::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "id", &id );
	saver.Add( "title", &title );
	saver.Add( "phrasesA", &phrasesA );
	saver.Add( "phrasesB", &phrasesB );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dialog::Assign( const Dialog& _dialog )
{
	id = _dialog.id;
	title = _dialog.title;
	phrasesA = _dialog.phrasesA;
	phrasesB = _dialog.phrasesB;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DialogsCollection::DialogsCollection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DialogsCollection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &dialogs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DialogsCollection::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DialogsCollection* parentPtr = (DialogsCollection*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DialogsCollection::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "dialogs", &dialogs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DialogsCollection::Assign( const DialogsCollection& _dialogsCollection )
{
	dialogs = _dialogsCollection.dialogs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactionScoringTable::FactionScoringTable() :
		loose( 10 )
	, win( 30 )
	, towerDestroyedBase( 1.0f )
	, towerDestroyedLevelMul( 1.0f )
	, bossKill( 1 )
	, topKills( 5 )
	, topAssists( 5 )
	, maxBossKillScore( 5 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FactionScoringTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &loose );
	saver.Add( 3, &win );
	saver.Add( 4, &towerDestroyedBase );
	saver.Add( 5, &towerDestroyedLevelMul );
	saver.Add( 6, &bossKill );
	saver.Add( 7, &topKills );
	saver.Add( 8, &topAssists );
	saver.Add( 9, &maxBossKillScore );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FactionScoringTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FactionScoringTable* parentPtr = (FactionScoringTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FactionScoringTable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "loose", &loose );
	saver.Add( "win", &win );
	saver.Add( "towerDestroyedBase", &towerDestroyedBase );
	saver.Add( "towerDestroyedLevelMul", &towerDestroyedLevelMul );
	saver.Add( "bossKill", &bossKill );
	saver.Add( "topKills", &topKills );
	saver.Add( "topAssists", &topAssists );
	saver.Add( "maxBossKillScore", &maxBossKillScore );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FactionScoringTable::Assign( const FactionScoringTable& _factionScoringTable )
{
	loose = _factionScoringTable.loose;
	win = _factionScoringTable.win;
	towerDestroyedBase = _factionScoringTable.towerDestroyedBase;
	towerDestroyedLevelMul = _factionScoringTable.towerDestroyedLevelMul;
	bossKill = _factionScoringTable.bossKill;
	topKills = _factionScoringTable.topKills;
	topAssists = _factionScoringTable.topAssists;
	maxBossKillScore = _factionScoringTable.maxBossKillScore;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FakeObj::FakeObj()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FakeObj::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FakeObj::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FakeObj* parentPtr = (FakeObj*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FakeObj::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FakeObj::Assign( const FakeObj& _fakeObj )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NWorld::PFWorld* FakeObj::Create() const
{
	return ( NWorld::PFWorld* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroScoringTable::HeroScoringTable() :
		heroOfTheDay( 5 )
	, towerKill( 2 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoringTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &heroOfTheDay );
	saver.Add( 3, &towerKill );
	saver.Add( 4, &heroKill );
	saver.Add( 5, &bossKill );
	saver.Add( 6, &goldMedals );
	saver.Add( 7, &silverMedals );
	saver.Add( 8, &buildingDestroy );
	saver.Add( 9, &flagRaise );
	saver.Add( 10, &flagDrop );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroScoringTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroScoringTable* parentPtr = (HeroScoringTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroScoringTable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "heroOfTheDay", &heroOfTheDay );
	saver.Add( "towerKill", &towerKill );
	saver.Add( "heroKill", &heroKill );
	saver.Add( "bossKill", &bossKill );
	saver.Add( "goldMedals", &goldMedals );
	saver.Add( "silverMedals", &silverMedals );
	saver.Add( "buildingDestroy", &buildingDestroy );
	saver.Add( "flagRaise", &flagRaise );
	saver.Add( "flagDrop", &flagDrop );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroScoringTable::Assign( const HeroScoringTable& _heroScoringTable )
{
	heroOfTheDay = _heroScoringTable.heroOfTheDay;
	towerKill = _heroScoringTable.towerKill;
	heroKill.score = _heroScoringTable.heroKill.score;
	heroKill.maxScore = _heroScoringTable.heroKill.maxScore;
	bossKill.score = _heroScoringTable.bossKill.score;
	bossKill.maxScore = _heroScoringTable.bossKill.maxScore;
	goldMedals.score = _heroScoringTable.goldMedals.score;
	goldMedals.maxScore = _heroScoringTable.goldMedals.maxScore;
	silverMedals.score = _heroScoringTable.silverMedals.score;
	silverMedals.maxScore = _heroScoringTable.silverMedals.maxScore;
	buildingDestroy.score = _heroScoringTable.buildingDestroy.score;
	buildingDestroy.maxScore = _heroScoringTable.buildingDestroy.maxScore;
	flagRaise.count = _heroScoringTable.flagRaise.count;
	flagRaise.score = _heroScoringTable.flagRaise.score;
	flagRaise.maxScore = _heroScoringTable.flagRaise.maxScore;
	flagDrop.count = _heroScoringTable.flagDrop.count;
	flagDrop.score = _heroScoringTable.flagDrop.score;
	flagDrop.maxScore = _heroScoringTable.flagDrop.maxScore;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HintsCollection::HintsCollection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HintsCollection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &hints );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HintsCollection::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HintsCollection* parentPtr = (HintsCollection*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HintsCollection::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "hints", &hints );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HintsCollection::Assign( const HintsCollection& _hintsCollection )
{
	hints = _hintsCollection.hints;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinimapImages::MinimapImages() :
		scaleFactor( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinimapImages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &firstMap );
	saver.Add( 3, &secondMap );
	saver.Add( 4, &neutralMap );
	saver.Add( 5, &centerOffset );
	saver.Add( 6, &scaleFactor );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MinimapImages::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MinimapImages* parentPtr = (MinimapImages*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinimapImages::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "firstMap", &firstMap );
	saver.Add( "secondMap", &secondMap );
	saver.Add( "neutralMap", &neutralMap );
	saver.Add( "centerOffset", &centerOffset );
	saver.Add( "scaleFactor", &scaleFactor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinimapImages::Assign( const MinimapImages& _minimapImages )
{
	firstMap = _minimapImages.firstMap;
	secondMap = _minimapImages.secondMap;
	neutralMap = _minimapImages.neutralMap;
	centerOffset = _minimapImages.centerOffset;
	scaleFactor = _minimapImages.scaleFactor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFTerrainTypeInfo::PFTerrainTypeInfo() :
		eType( TERRAINTYPE_PLAINS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFTerrainTypeInfo::operator&( IBinSaver &saver )
{
	saver.Add( 1, (TerrainTypeInfo*)this );
	saver.Add( 2, &eType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFTerrainTypeInfo::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PFTerrainTypeInfo* parentPtr = (PFTerrainTypeInfo*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTerrainTypeInfo::SerializeSelf( IXmlSaver &saver )
{
	TerrainTypeInfo::SerializeSelf( saver );
	saver.Add( "eType", &eType );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFTerrainTypeInfo::Assign( const PFTerrainTypeInfo& _pFTerrainTypeInfo )
{
	eType = _pFTerrainTypeInfo.eType;
	pDBMaterial = _pFTerrainTypeInfo.pDBMaterial;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFUIGameLogicRoot::PFUIGameLogicRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFUIGameLogicRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statisticData );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFUIGameLogicRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PFUIGameLogicRoot* parentPtr = (PFUIGameLogicRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUIGameLogicRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "statisticData", &statisticData );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUIGameLogicRoot::Assign( const PFUIGameLogicRoot& _pFUIGameLogicRoot )
{
	statisticData = _pFUIGameLogicRoot.statisticData;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScoringTable::ScoringTable()
{
	heroTitles.resize( 31 );
	scoreDescriptions.resize( 24 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoringTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &faction );
	saver.Add( 3, &hero );
	saver.Add( 4, &achievementsList );
	saver.Add( 5, &heroTitles );
	saver.Add( 6, &scoreDescriptions );
	saver.Add( 7, &teleporterAbilities );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScoringTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ScoringTable* parentPtr = (ScoringTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScoringTable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "faction", &faction );
	saver.Add( "hero", &hero );
	saver.Add( "achievementsList", &achievementsList );
	heroTitles.resize( 31 );
	saver.Add( "heroTitles", &heroTitles );
	scoreDescriptions.resize( 24 );
	saver.Add( "scoreDescriptions", &scoreDescriptions );
	saver.Add( "teleporterAbilities", &teleporterAbilities );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScoringTable::Assign( const ScoringTable& _scoringTable )
{
	faction = _scoringTable.faction;
	hero = _scoringTable.hero;
	achievementsList = _scoringTable.achievementsList;
	heroTitles = _scoringTable.heroTitles;
	scoreDescriptions = _scoringTable.scoreDescriptions;
	teleporterAbilities = _scoringTable.teleporterAbilities;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionQuestsCollection::SessionQuestsCollection()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionQuestsCollection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &quests );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionQuestsCollection::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionQuestsCollection* parentPtr = (SessionQuestsCollection*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionQuestsCollection::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "quests", &quests );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionQuestsCollection::Assign( const SessionQuestsCollection& _sessionQuestsCollection )
{
	quests = _sessionQuestsCollection.quests;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatsBudgetContainer::StatsBudgetContainer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsBudgetContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stats );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsBudgetContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatsBudgetContainer* parentPtr = (StatsBudgetContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsBudgetContainer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "stats", &stats );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsBudgetContainer::Assign( const StatsBudgetContainer& _statsBudgetContainer )
{
	stats = _statsBudgetContainer.stats;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatsContainer::StatsContainer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stats );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatsContainer* parentPtr = (StatsContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsContainer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "stats", &stats );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsContainer::Assign( const StatsContainer& _statsContainer )
{
	stats = _statsContainer.stats;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatsEnhancersContainer::StatsEnhancersContainer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsEnhancersContainer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &statsEnhancers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StatsEnhancersContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StatsEnhancersContainer* parentPtr = (StatsEnhancersContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsEnhancersContainer::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "statsEnhancers", &statsEnhancers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StatsEnhancersContainer::Assign( const StatsEnhancersContainer& _statsEnhancersContainer )
{
	statsEnhancers = _statsEnhancersContainer.statsEnhancers;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIEvent::UIEvent() :
		signRecipients( RECIPIENTS_ALL_PLAYERS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEvent::operator&( IBinSaver &saver )
{
	saver.Add( 2, &signRecipients );
	saver.Add( 3, &UISigns );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEvent::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIEvent* parentPtr = (UIEvent*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEvent::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "signRecipients", &signRecipients );
	saver.Add( "UISigns", &UISigns );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEvent::Assign( const UIEvent& _uIEvent )
{
	signRecipients = _uIEvent.signRecipients;
	UISigns = _uIEvent.UISigns;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIEventsCustom::UIEventsCustom()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEventsCustom::operator&( IBinSaver &saver )
{
	saver.Add( 2, &evMiss );
	saver.Add( 3, &evGetNafta );
	saver.Add( 4, &evHeroKill );
	saver.Add( 5, &evHeroKillByAI );
	saver.Add( 6, &evHeroKillByNeutralAI );
	saver.Add( 7, &evTowerDestroy );
	saver.Add( 8, &evTowerDestroyByAI );
	saver.Add( 9, &evTowerDestroyByNeutralAI );
	saver.Add( 10, &evItemTransfer );
	saver.Add( 11, &evItemGain );
	saver.Add( 12, &evHeroCheat );
	saver.Add( 13, &evHeroReconnected );
	saver.Add( 14, &evHeroDisconnected );
	saver.Add( 15, &evHeroDisconnectedAFK );
	saver.Add( 16, &evHeroFriendDisconnected );
	saver.Add( 17, &evHeroFriendDisconnectedAFK );
	saver.Add( 18, &evHeroLeft );
	saver.Add( 19, &evHeroFriendLeft );
	saver.Add( 20, &evHeroFriendReconnected );
	saver.Add( 21, &evHeroAFK );
	saver.Add( 22, &evHeroAFKEnded );
	saver.Add( 23, &evBarrackDestroyed );
	saver.Add( 24, &evFriendBarrackDestroyed );
	saver.Add( 25, &evVictory );
	saver.Add( 26, &evDefeat );
	saver.Add( 27, &evSpectatorJoin );
	saver.Add( 28, &evAdminMuted );
	saver.Add( 29, &evStartAiForPlayer );
	saver.Add( 30, &evLeaverMuted );
	saver.Add( 31, &evLeaverPartyMuted );
	saver.Add( 32, &evAdminMutedNotify );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIEventsCustom::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIEventsCustom* parentPtr = (UIEventsCustom*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEventsCustom::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "evMiss", &evMiss );
	saver.Add( "evGetNafta", &evGetNafta );
	saver.Add( "evHeroKill", &evHeroKill );
	saver.Add( "evHeroKillByAI", &evHeroKillByAI );
	saver.Add( "evHeroKillByNeutralAI", &evHeroKillByNeutralAI );
	saver.Add( "evTowerDestroy", &evTowerDestroy );
	saver.Add( "evTowerDestroyByAI", &evTowerDestroyByAI );
	saver.Add( "evTowerDestroyByNeutralAI", &evTowerDestroyByNeutralAI );
	saver.Add( "evItemTransfer", &evItemTransfer );
	saver.Add( "evItemGain", &evItemGain );
	saver.Add( "evHeroCheat", &evHeroCheat );
	saver.Add( "evHeroReconnected", &evHeroReconnected );
	saver.Add( "evHeroDisconnected", &evHeroDisconnected );
	saver.Add( "evHeroDisconnectedAFK", &evHeroDisconnectedAFK );
	saver.Add( "evHeroFriendDisconnected", &evHeroFriendDisconnected );
	saver.Add( "evHeroFriendDisconnectedAFK", &evHeroFriendDisconnectedAFK );
	saver.Add( "evHeroLeft", &evHeroLeft );
	saver.Add( "evHeroFriendLeft", &evHeroFriendLeft );
	saver.Add( "evHeroFriendReconnected", &evHeroFriendReconnected );
	saver.Add( "evHeroAFK", &evHeroAFK );
	saver.Add( "evHeroAFKEnded", &evHeroAFKEnded );
	saver.Add( "evBarrackDestroyed", &evBarrackDestroyed );
	saver.Add( "evFriendBarrackDestroyed", &evFriendBarrackDestroyed );
	saver.Add( "evVictory", &evVictory );
	saver.Add( "evDefeat", &evDefeat );
	saver.Add( "evSpectatorJoin", &evSpectatorJoin );
	saver.Add( "evAdminMuted", &evAdminMuted );
	saver.Add( "evStartAiForPlayer", &evStartAiForPlayer );
	saver.Add( "evLeaverMuted", &evLeaverMuted );
	saver.Add( "evLeaverPartyMuted", &evLeaverPartyMuted );
	saver.Add( "evAdminMutedNotify", &evAdminMutedNotify );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIEventsCustom::Assign( const UIEventsCustom& _uIEventsCustom )
{
	evMiss = _uIEventsCustom.evMiss;
	evGetNafta = _uIEventsCustom.evGetNafta;
	evHeroKill = _uIEventsCustom.evHeroKill;
	evHeroKillByAI = _uIEventsCustom.evHeroKillByAI;
	evHeroKillByNeutralAI = _uIEventsCustom.evHeroKillByNeutralAI;
	evTowerDestroy = _uIEventsCustom.evTowerDestroy;
	evTowerDestroyByAI = _uIEventsCustom.evTowerDestroyByAI;
	evTowerDestroyByNeutralAI = _uIEventsCustom.evTowerDestroyByNeutralAI;
	evItemTransfer = _uIEventsCustom.evItemTransfer;
	evItemGain = _uIEventsCustom.evItemGain;
	evHeroCheat = _uIEventsCustom.evHeroCheat;
	evHeroReconnected = _uIEventsCustom.evHeroReconnected;
	evHeroDisconnected = _uIEventsCustom.evHeroDisconnected;
	evHeroDisconnectedAFK = _uIEventsCustom.evHeroDisconnectedAFK;
	evHeroFriendDisconnected = _uIEventsCustom.evHeroFriendDisconnected;
	evHeroFriendDisconnectedAFK = _uIEventsCustom.evHeroFriendDisconnectedAFK;
	evHeroLeft = _uIEventsCustom.evHeroLeft;
	evHeroFriendLeft = _uIEventsCustom.evHeroFriendLeft;
	evHeroFriendReconnected = _uIEventsCustom.evHeroFriendReconnected;
	evHeroAFK = _uIEventsCustom.evHeroAFK;
	evHeroAFKEnded = _uIEventsCustom.evHeroAFKEnded;
	evBarrackDestroyed = _uIEventsCustom.evBarrackDestroyed;
	evFriendBarrackDestroyed = _uIEventsCustom.evFriendBarrackDestroyed;
	evVictory = _uIEventsCustom.evVictory;
	evDefeat = _uIEventsCustom.evDefeat;
	evSpectatorJoin = _uIEventsCustom.evSpectatorJoin;
	evAdminMuted = _uIEventsCustom.evAdminMuted;
	evStartAiForPlayer = _uIEventsCustom.evStartAiForPlayer;
	evLeaverMuted = _uIEventsCustom.evLeaverMuted;
	evLeaverPartyMuted = _uIEventsCustom.evLeaverPartyMuted;
	evAdminMutedNotify = _uIEventsCustom.evAdminMutedNotify;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISign::UISign() :
		signRecipients( RECIPIENTS_USE_FROM_PARENT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISign::operator&( IBinSaver &saver )
{
	saver.Add( 2, &signRecipients );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISign::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISign* parentPtr = (UISign*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISign::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "signRecipients", &signRecipients );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISign::Assign( const UISign& _uISign )
{
	signRecipients = _uISign.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISign::Create() const
{
	return ( NGameX::PFUISign* )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISignAnnouncement::UISignAnnouncement() :
		announcementType( ANNOUNCEMENTTYPE_PLAYERKILLED )
	, priority( 0 )
	, lifeTime( 3.0f )
	, announcementSoundCooldown( 0.0f )
	, UseInTutorial( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignAnnouncement::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UISign*)this );
	saver.Add( 2, &announcementType );
	saver.Add( 3, &txt );
	saver.Add( 4, &imageBurn );
	saver.Add( 5, &imageFreeze );
	saver.Add( 6, &priority );
	saver.Add( 7, &lifeTime );
	saver.Add( 8, &announcementSound );
	saver.Add( 9, &announcementSoundCooldown );
	saver.Add( 10, &UseInTutorial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignAnnouncement::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISignAnnouncement* parentPtr = (UISignAnnouncement*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignAnnouncement::SerializeSelf( IXmlSaver &saver )
{
	UISign::SerializeSelf( saver );
	saver.Add( "announcementType", &announcementType );
	saver.Add( "txt", &txt );
	saver.Add( "imageBurn", &imageBurn );
	saver.Add( "imageFreeze", &imageFreeze );
	saver.Add( "priority", &priority );
	saver.Add( "lifeTime", &lifeTime );
	saver.Add( "announcementSound", &announcementSound );
	saver.Add( "announcementSoundCooldown", &announcementSoundCooldown );
	saver.Add( "UseInTutorial", &UseInTutorial );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignAnnouncement::Assign( const UISignAnnouncement& _uISignAnnouncement )
{
	announcementType = _uISignAnnouncement.announcementType;
	txt = _uISignAnnouncement.txt;
	imageBurn = _uISignAnnouncement.imageBurn;
	imageFreeze = _uISignAnnouncement.imageFreeze;
	priority = _uISignAnnouncement.priority;
	lifeTime = _uISignAnnouncement.lifeTime;
	announcementSound.projectName = _uISignAnnouncement.announcementSound.projectName;
	announcementSound.groupName = _uISignAnnouncement.announcementSound.groupName;
	announcementSound.eventName = _uISignAnnouncement.announcementSound.eventName;
	announcementSoundCooldown = _uISignAnnouncement.announcementSoundCooldown;
	UseInTutorial = _uISignAnnouncement.UseInTutorial;
	signRecipients = _uISignAnnouncement.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISignAnnouncement::Create() const
{
	return new NGameX::PFUISignAnnouncement( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISignFlyOffText::UISignFlyOffText()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignFlyOffText::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UISign*)this );
	saver.Add( 2, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignFlyOffText::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISignFlyOffText* parentPtr = (UISignFlyOffText*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignFlyOffText::SerializeSelf( IXmlSaver &saver )
{
	UISign::SerializeSelf( saver );
	saver.Add( "text", &text );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignFlyOffText::Assign( const UISignFlyOffText& _uISignFlyOffText )
{
	text.lifeTime = _uISignFlyOffText.text.lifeTime;
	text.offset = _uISignFlyOffText.text.offset;
	text.velocity = _uISignFlyOffText.text.velocity;
	text.acceleration = _uISignFlyOffText.text.acceleration;
	text.startOpacity = _uISignFlyOffText.text.startOpacity;
	text.endOpacity = _uISignFlyOffText.text.endOpacity;
	text.align = _uISignFlyOffText.text.align;
	text.layout = _uISignFlyOffText.text.layout;
	signRecipients = _uISignFlyOffText.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISignFlyOffText::Create() const
{
	return new NGameX::PFUISignFlyOffText( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISignMessageToChat::UISignMessageToChat() :
		channel( CHATCHANNEL_ACHIEVMENTS )
{
	messages.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignMessageToChat::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UISign*)this );
	saver.Add( 2, &messages );
	saver.Add( 3, &channel );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignMessageToChat::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISignMessageToChat* parentPtr = (UISignMessageToChat*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignMessageToChat::SerializeSelf( IXmlSaver &saver )
{
	UISign::SerializeSelf( saver );
	messages.resize( 3 );
	saver.Add( "messages", &messages );
	saver.Add( "channel", &channel );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignMessageToChat::Assign( const UISignMessageToChat& _uISignMessageToChat )
{
	messages = _uISignMessageToChat.messages;
	channel = _uISignMessageToChat.channel;
	signRecipients = _uISignMessageToChat.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISignMessageToChat::Create() const
{
	return new NGameX::PFUISignMessageToChat( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISignMessageToStatusLine::UISignMessageToStatusLine()
{
	messages.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignMessageToStatusLine::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UISign*)this );
	saver.Add( 2, &messages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignMessageToStatusLine::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISignMessageToStatusLine* parentPtr = (UISignMessageToStatusLine*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignMessageToStatusLine::SerializeSelf( IXmlSaver &saver )
{
	UISign::SerializeSelf( saver );
	messages.resize( 3 );
	saver.Add( "messages", &messages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignMessageToStatusLine::Assign( const UISignMessageToStatusLine& _uISignMessageToStatusLine )
{
	messages = _uISignMessageToStatusLine.messages;
	signRecipients = _uISignMessageToStatusLine.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISignMessageToStatusLine::Create() const
{
	return new NGameX::PFUISignMessageToStatusLine( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UISignPlaySound::UISignPlaySound()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignPlaySound::operator&( IBinSaver &saver )
{
	saver.Add( 1, (UISign*)this );
	saver.Add( 2, &soundDesc );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UISignPlaySound::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UISignPlaySound* parentPtr = (UISignPlaySound*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignPlaySound::SerializeSelf( IXmlSaver &saver )
{
	UISign::SerializeSelf( saver );
	saver.Add( "soundDesc", &soundDesc );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UISignPlaySound::Assign( const UISignPlaySound& _uISignPlaySound )
{
	soundDesc.projectName = _uISignPlaySound.soundDesc.projectName;
	soundDesc.groupName = _uISignPlaySound.soundDesc.groupName;
	soundDesc.eventName = _uISignPlaySound.soundDesc.eventName;
	signRecipients = _uISignPlaySound.signRecipients;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NGameX::PFUISign* UISignPlaySound::Create() const
{
	return new NGameX::PFUISignPlaySound( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UITeamInfoParams::UITeamInfoParams()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITeamInfoParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tooltipSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UITeamInfoParams::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UITeamInfoParams* parentPtr = (UITeamInfoParams*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UITeamInfoParams::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "tooltipSettings", &tooltipSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UITeamInfoParams::Assign( const UITeamInfoParams& _uITeamInfoParams )
{
	tooltipSettings.heroTooltip = _uITeamInfoParams.tooltipSettings.heroTooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WebTowerCameraSettings::WebTowerCameraSettings() :
		linearSpeed( 4.0f )
	, initialPitch( -0.4f )
	, yawSpeed( 1.0f )
	, heightOffset( 0.0f )
	, minRod( 1.0f )
	, maxRod( 15.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WebTowerCameraSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &linearSpeed );
	saver.Add( 3, &initialPitch );
	saver.Add( 4, &yawSpeed );
	saver.Add( 5, &heightOffset );
	saver.Add( 6, &minRod );
	saver.Add( 7, &maxRod );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WebTowerCameraSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WebTowerCameraSettings* parentPtr = (WebTowerCameraSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WebTowerCameraSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "linearSpeed", &linearSpeed );
	saver.Add( "initialPitch", &initialPitch );
	saver.Add( "yawSpeed", &yawSpeed );
	saver.Add( "heightOffset", &heightOffset );
	saver.Add( "minRod", &minRod );
	saver.Add( "maxRod", &maxRod );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WebTowerCameraSettings::Assign( const WebTowerCameraSettings& _webTowerCameraSettings )
{
	linearSpeed = _webTowerCameraSettings.linearSpeed;
	initialPitch = _webTowerCameraSettings.initialPitch;
	yawSpeed = _webTowerCameraSettings.yawSpeed;
	heightOffset = _webTowerCameraSettings.heightOffset;
	minRod = _webTowerCameraSettings.minRod;
	maxRod = _webTowerCameraSettings.maxRod;
}
}; // namespace NDb
