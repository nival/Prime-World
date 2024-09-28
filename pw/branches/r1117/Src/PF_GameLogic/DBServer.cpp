// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../Render/DBRenderResources.h"
#include "../PF_GameLogic/DBTalent.h"
#include "DBServer.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_DBRESOURCE( GuildBonus );
BASIC_REGISTER_DBRESOURCE( RollItem );
REGISTER_DBRESOURCE( ClanWarsSettings );
REGISTER_DBRESOURCE( ContainersBySpecialPoints );
REGISTER_DBRESOURCE( FlagRollItem );
REGISTER_DBRESOURCE( GoldRollItem );
REGISTER_DBRESOURCE( GuildLevels );
REGISTER_DBRESOURCE( HeroRollItem );
REGISTER_DBRESOURCE( MapMMakingSettings );
REGISTER_DBRESOURCE( MarketingEventRollItem );
REGISTER_DBRESOURCE( ModeRollSettings );
REGISTER_DBRESOURCE( NothingRollItem );
REGISTER_DBRESOURCE( PremiumAccRollItem );
REGISTER_DBRESOURCE( RarityTalentListRollItem );
REGISTER_DBRESOURCE( ResourceRollItem );
REGISTER_DBRESOURCE( RollContainer );
REGISTER_DBRESOURCE( RollContainerCostByRank );
REGISTER_DBRESOURCE( RollContainerCountByRank );
REGISTER_DBRESOURCE( ClanWarsRollItem );
REGISTER_DBRESOURCE( RollSettings );
REGISTER_DBRESOURCE( SkinRollItem );
REGISTER_DBRESOURCE( TalentRollItem );
REGISTER_DBRESOURCE( TalentUpgradeEntity );
REGISTER_DBRESOURCE( TalentUpgradeEntityRollItem );
REGISTER_DBRESOURCE( TalentUpgradeProbabilityTable );
REGISTER_DBRESOURCE( TalentUpgradeRollItem );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ClanWarsRollItemType value )
{
	switch( value )
	{
		case CLANWARSROLLITEMTYPE_CLANRATING:
			return "ClanRating";
		case CLANWARSROLLITEMTYPE_PLAYERRATING:
			return "PlayerRating";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ClanWarsRollItemType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ClanWarsRollItemType StringToEnum_ClanWarsRollItemType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ClanWarsRollItemType)(NStr::ToInt( value ));
	if ( strcmp( value, "ClanRating" ) == 0 || strcmp( value, "CLANWARSROLLITEMTYPE_CLANRATING" ) == 0 )
		return CLANWARSROLLITEMTYPE_CLANRATING;
	if ( strcmp( value, "PlayerRating" ) == 0 || strcmp( value, "CLANWARSROLLITEMTYPE_PLAYERRATING" ) == 0 )
		return CLANWARSROLLITEMTYPE_PLAYERRATING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ClanWarsRollItemType", value ) );
	return CLANWARSROLLITEMTYPE_CLANRATING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ResourceRollConstraint value )
{
	switch( value )
	{
		case RESOURCEROLLCONSTRAINT_SILVER:
			return "Silver";
		case RESOURCEROLLCONSTRAINT_RESOURCE1:
			return "Resource1";
		case RESOURCEROLLCONSTRAINT_RESOURCE2:
			return "Resource2";
		case RESOURCEROLLCONSTRAINT_RESOURCE3:
			return "Resource3";
		case RESOURCEROLLCONSTRAINT_PEARL:
			return "Pearl";
		case RESOURCEROLLCONSTRAINT_REDPEARL:
			return "RedPearl";
		case RESOURCEROLLCONSTRAINT_SHARD:
			return "Shard";
		case RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY:
			return "CustomCurrency";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ResourceRollConstraint", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ResourceRollConstraint StringToEnum_ResourceRollConstraint( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ResourceRollConstraint)(NStr::ToInt( value ));
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_SILVER" ) == 0 )
		return RESOURCEROLLCONSTRAINT_SILVER;
	if ( strcmp( value, "Resource1" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE1" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE1;
	if ( strcmp( value, "Resource2" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE2" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE2;
	if ( strcmp( value, "Resource3" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_RESOURCE3" ) == 0 )
		return RESOURCEROLLCONSTRAINT_RESOURCE3;
	if ( strcmp( value, "Pearl" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_PEARL" ) == 0 )
		return RESOURCEROLLCONSTRAINT_PEARL;
	if ( strcmp( value, "RedPearl" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_REDPEARL" ) == 0 )
		return RESOURCEROLLCONSTRAINT_REDPEARL;
	if ( strcmp( value, "Shard" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_SHARD" ) == 0 )
		return RESOURCEROLLCONSTRAINT_SHARD;
	if ( strcmp( value, "CustomCurrency" ) == 0 || strcmp( value, "RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY" ) == 0 )
		return RESOURCEROLLCONSTRAINT_CUSTOMCURRENCY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ResourceRollConstraint", value ) );
	return RESOURCEROLLCONSTRAINT_SILVER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TalentUpgradeEntityType value )
{
	switch( value )
	{
		case TALENTUPGRADEENTITYTYPE_RUNE:
			return "Rune";
		case TALENTUPGRADEENTITYTYPE_CATALYST:
			return "Catalyst";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TalentUpgradeEntityType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TalentUpgradeEntityType StringToEnum_TalentUpgradeEntityType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TalentUpgradeEntityType)(NStr::ToInt( value ));
	if ( strcmp( value, "Rune" ) == 0 || strcmp( value, "TALENTUPGRADEENTITYTYPE_RUNE" ) == 0 )
		return TALENTUPGRADEENTITYTYPE_RUNE;
	if ( strcmp( value, "Catalyst" ) == 0 || strcmp( value, "TALENTUPGRADEENTITYTYPE_CATALYST" ) == 0 )
		return TALENTUPGRADEENTITYTYPE_CATALYST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TalentUpgradeEntityType", value ) );
	return TALENTUPGRADEENTITYTYPE_RUNE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseModifierFromQuantity::BaseModifierFromQuantity() :
		quantity( 0.0f )
	, percent( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseModifierFromQuantity::operator&( IBinSaver &saver )
{
	saver.Add( 2, &quantity );
	saver.Add( 3, &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseModifierFromQuantity::operator&( IXmlSaver &saver )
{
	saver.Add( "quantity", &quantity );
	saver.Add( "percent", &percent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EstimFunctionWeights::EstimFunctionWeights() :
		ladiesNumber( 1.0f )
	, genderPairs( 1.0f )
	, heroes( 1.0f )
	, ratingSpan( 1.0f )
	, ratingPatternDelta( 1.0f )
	, ratingTeamAvgDelta( 1.0f )
	, forceSpan( 1.0f )
	, heroClassesDifference( 1.0f )
	, heroClassesOptimum( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EstimFunctionWeights::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ladiesNumber );
	saver.Add( 3, &genderPairs );
	saver.Add( 4, &heroes );
	saver.Add( 5, &ratingSpan );
	saver.Add( 6, &ratingPatternDelta );
	saver.Add( 7, &ratingTeamAvgDelta );
	saver.Add( 8, &forceSpan );
	saver.Add( 9, &heroClassesDifference );
	saver.Add( 10, &heroClassesOptimum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EstimFunctionWeights::operator&( IXmlSaver &saver )
{
	saver.Add( "ladiesNumber", &ladiesNumber );
	saver.Add( "genderPairs", &genderPairs );
	saver.Add( "heroes", &heroes );
	saver.Add( "ratingSpan", &ratingSpan );
	saver.Add( "ratingPatternDelta", &ratingPatternDelta );
	saver.Add( "ratingTeamAvgDelta", &ratingTeamAvgDelta );
	saver.Add( "forceSpan", &forceSpan );
	saver.Add( "heroClassesDifference", &heroClassesDifference );
	saver.Add( "heroClassesOptimum", &heroClassesOptimum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FullPartyRatingModifier::FullPartyRatingModifier() :
		minRating( 0 )
	, ratingBonus( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullPartyRatingModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minRating );
	saver.Add( 3, &ratingBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullPartyRatingModifier::operator&( IXmlSaver &saver )
{
	saver.Add( "minRating", &minRating );
	saver.Add( "ratingBonus", &ratingBonus );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildLevel::GuildLevel() :
		requiredExp( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevel::operator&( IBinSaver &saver )
{
	saver.Add( 2, &requiredExp );
	saver.Add( 3, &title );
	saver.Add( 4, &tooltip );
	saver.Add( 5, &Bonuses );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevel::operator&( IXmlSaver &saver )
{
	saver.Add( "requiredExp", &requiredExp );
	saver.Add( "title", &title );
	saver.Add( "tooltip", &tooltip );
	saver.Add( "Bonuses", &Bonuses );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LerpDataItem::LerpDataItem() :
		x( 0.0f )
	, y( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LerpDataItem::operator&( IBinSaver &saver )
{
	saver.Add( 2, &x );
	saver.Add( 3, &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LerpDataItem::operator&( IXmlSaver &saver )
{
	saver.Add( "x", &x );
	saver.Add( "y", &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingHeroClass::MMakingHeroClass() :
		minEfficiency( 1.0f )
	, maxEfficiency( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingHeroClass::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minEfficiency );
	saver.Add( 3, &maxEfficiency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingHeroClass::operator&( IXmlSaver &saver )
{
	saver.Add( "minEfficiency", &minEfficiency );
	saver.Add( "maxEfficiency", &maxEfficiency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingLocationPingSettings::MMakingLocationPingSettings() :
		nicePingThreshold( 40 )
	, pingScaleMinFactor( 2.0f )
	, worstPingWaitTimePenalty( 180 )
	, goodEnoughPingFactor( 0.2f )
	, ratingThreshold( 1800 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLocationPingSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nicePingThreshold );
	saver.Add( 3, &pingScaleMinFactor );
	saver.Add( 4, &worstPingWaitTimePenalty );
	saver.Add( 5, &goodEnoughPingFactor );
	saver.Add( 6, &ratingThreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLocationPingSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "nicePingThreshold", &nicePingThreshold );
	saver.Add( "pingScaleMinFactor", &pingScaleMinFactor );
	saver.Add( "worstPingWaitTimePenalty", &worstPingWaitTimePenalty );
	saver.Add( "goodEnoughPingFactor", &goodEnoughPingFactor );
	saver.Add( "ratingThreshold", &ratingThreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingLoseStreakCorrection::MMakingLoseStreakCorrection() :
		minStreak( 2 )
	, forcePenalty( 5.0f )
	, ratingPenalty( 100.0f )
	, firstCaseThreshold( 2 )
	, firstCasePenalty( 0.25f )
	, secondCaseThreshold( 3 )
	, secondCasePenalty( 0.5f )
	, thirdCaseThreshold( 5 )
	, thirdCasePenalty( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLoseStreakCorrection::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minStreak );
	saver.Add( 3, &forcePenalty );
	saver.Add( 4, &ratingPenalty );
	saver.Add( 5, &firstCaseThreshold );
	saver.Add( 6, &firstCasePenalty );
	saver.Add( 7, &secondCaseThreshold );
	saver.Add( 8, &secondCasePenalty );
	saver.Add( 9, &thirdCaseThreshold );
	saver.Add( 10, &thirdCasePenalty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingLoseStreakCorrection::operator&( IXmlSaver &saver )
{
	saver.Add( "minStreak", &minStreak );
	saver.Add( "forcePenalty", &forcePenalty );
	saver.Add( "ratingPenalty", &ratingPenalty );
	saver.Add( "firstCaseThreshold", &firstCaseThreshold );
	saver.Add( "firstCasePenalty", &firstCasePenalty );
	saver.Add( "secondCaseThreshold", &secondCaseThreshold );
	saver.Add( "secondCasePenalty", &secondCasePenalty );
	saver.Add( "thirdCaseThreshold", &thirdCaseThreshold );
	saver.Add( "thirdCasePenalty", &thirdCasePenalty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingRank::MMakingRank() :
		lowRating( 0.0f )
	, mergeWithNextRank( false )
	, mergeRanksCount( 0 )
	, useForceMM( false )
	, usePlayerRatingMM( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lowRating );
	saver.Add( 3, &mergeWithNextRank );
	saver.Add( 4, &mergeRanksCount );
	saver.Add( 5, &debugName );
	saver.Add( 6, &useForceMM );
	saver.Add( 7, &usePlayerRatingMM );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingRank::operator&( IXmlSaver &saver )
{
	saver.Add( "lowRating", &lowRating );
	saver.Add( "mergeWithNextRank", &mergeWithNextRank );
	saver.Add( "mergeRanksCount", &mergeRanksCount );
	saver.Add( "debugName", &debugName );
	saver.Add( "useForceMM", &useForceMM );
	saver.Add( "usePlayerRatingMM", &usePlayerRatingMM );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingScale::MMakingScale() :
		low( 100 )
	, high( 1000 )
	, step( 20 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingScale::operator&( IBinSaver &saver )
{
	saver.Add( 2, &low );
	saver.Add( 3, &high );
	saver.Add( 4, &step );
	saver.Add( 5, &diffLow );
	saver.Add( 6, &diffHigh );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingScale::operator&( IXmlSaver &saver )
{
	saver.Add( "low", &low );
	saver.Add( "high", &high );
	saver.Add( "step", &step );
	saver.Add( "diffLow", &diffLow );
	saver.Add( "diffHigh", &diffHigh );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMakingWaitVsProbability::MMakingWaitVsProbability() :
		startingWaitTime( 15.0f )
	, endingWaitTime( 180.0f )
	, startingProbabilityWeight( 100 )
	, endingProbabilityWeight( 300 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingWaitVsProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &startingWaitTime );
	saver.Add( 3, &endingWaitTime );
	saver.Add( 4, &startingProbabilityWeight );
	saver.Add( 5, &endingProbabilityWeight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MMakingWaitVsProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "startingWaitTime", &startingWaitTime );
	saver.Add( "endingWaitTime", &endingWaitTime );
	saver.Add( "startingProbabilityWeight", &startingProbabilityWeight );
	saver.Add( "endingProbabilityWeight", &endingProbabilityWeight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointsToContainers::PointsToContainers() :
		specialPoints( 0 )
	, containers( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointsToContainers::operator&( IBinSaver &saver )
{
	saver.Add( 2, &specialPoints );
	saver.Add( 3, &containers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointsToContainers::operator&( IXmlSaver &saver )
{
	saver.Add( "specialPoints", &specialPoints );
	saver.Add( "containers", &containers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RatingModifier::RatingModifier() :
		minValue( 0 )
	, maxValue( 0 )
	, winModifier( 0.0f )
	, looseModifier( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RatingModifier::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minValue );
	saver.Add( 3, &maxValue );
	saver.Add( 4, &winModifier );
	saver.Add( 5, &looseModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RatingModifier::operator&( IXmlSaver &saver )
{
	saver.Add( "minValue", &minValue );
	saver.Add( "maxValue", &maxValue );
	saver.Add( "winModifier", &winModifier );
	saver.Add( "looseModifier", &looseModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionData::RecessionData() :
		isWaitingTimePremium( true )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &isWaitingTimePremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionData::operator&( IXmlSaver &saver )
{
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "isWaitingTimePremium", &isWaitingTimePremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionFullPartyTableForForceMM::RecessionFullPartyTableForForceMM()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionFullPartyTableForForceMM::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &recessionPremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionFullPartyTableForForceMM::operator&( IXmlSaver &saver )
{
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "recessionPremium", &recessionPremium );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecessionTableForPlayerRatingMM::RecessionTableForPlayerRatingMM() :
		recessionSideDiff( 0.0f )
	, recessionPremiumTimeThreshold( 0.0f )
	, recessionMaxPlayerRating( 2000 )
	, recessionMinPlayerRating( 1200 )
{
	recessionTable.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionTableForPlayerRatingMM::operator&( IBinSaver &saver )
{
	saver.Add( 2, &recessionTable );
	saver.Add( 3, &recessionSideDiff );
	saver.Add( 4, &recessionPremiumTable );
	saver.Add( 5, &recessionPremiumTimeThreshold );
	saver.Add( 6, &recessionMaxPlayerRating );
	saver.Add( 7, &recessionMinPlayerRating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RecessionTableForPlayerRatingMM::operator&( IXmlSaver &saver )
{
	recessionTable.resize( 3 );
	saver.Add( "recessionTable", &recessionTable );
	saver.Add( "recessionSideDiff", &recessionSideDiff );
	saver.Add( "recessionPremiumTable", &recessionPremiumTable );
	saver.Add( "recessionPremiumTimeThreshold", &recessionPremiumTimeThreshold );
	saver.Add( "recessionMaxPlayerRating", &recessionMaxPlayerRating );
	saver.Add( "recessionMinPlayerRating", &recessionMinPlayerRating );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollItemProbability::RollItemProbability() :
		probability( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItemProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &probability );
	saver.Add( 3, &item );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItemProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "probability", &probability );
	saver.Add( "item", &item );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollLevelInfo::RollLevelInfo() :
		level( 0 )
	, count( 0 )
	, deviation( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollLevelInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &level );
	saver.Add( 3, &count );
	saver.Add( 4, &deviation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollLevelInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "level", &level );
	saver.Add( "count", &count );
	saver.Add( "deviation", &deviation );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleRollSettings::SingleRollSettings() :
		allowedRollGroups( TALENTROLLGROUP_ALL )
	, version( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleRollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rollContainer );
	saver.Add( 3, &allowedRollGroups );
	saver.Add( 4, &version );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SingleRollSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "rollContainer", &rollContainer );
	saver.Add( "allowedRollGroups", &allowedRollGroups );
	saver.Add( "version", &version );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeProbability::TalentUpgradeProbability() :
		probability( 0.0f )
	, points( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbability::operator&( IBinSaver &saver )
{
	saver.Add( 2, &probability );
	saver.Add( 3, &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbability::operator&( IXmlSaver &saver )
{
	saver.Add( "probability", &probability );
	saver.Add( "points", &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildBonus::GuildBonus()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBonus::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildBonus::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildBonus* parentPtr = (GuildBonus*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBonus::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "tooltip", &tooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildBonus::Assign( const GuildBonus& _guildBonus )
{
	tooltip = _guildBonus.tooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollItem::RollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItem::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollItem* parentPtr = (RollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollItem::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollItem::Assign( const RollItem& _rollItem )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClanWarsSettings::ClanWarsSettings() :
		basePoints( 10.0f )
	, clanPoints( 0.3f )
	, normalizeBySessionScores( true )
	, premiumAccountModifier( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &basePoints );
	saver.Add( 3, &partyClanMembersModifier );
	saver.Add( 4, &foeCountsModifier );
	saver.Add( 5, &defeatedFoeRankModifier );
	saver.Add( 6, &clanPoints );
	saver.Add( 7, &normalizeBySessionScores );
	saver.Add( 8, &premiumAccountModifier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ClanWarsSettings* parentPtr = (ClanWarsSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "basePoints", &basePoints );
	saver.Add( "partyClanMembersModifier", &partyClanMembersModifier );
	saver.Add( "foeCountsModifier", &foeCountsModifier );
	saver.Add( "defeatedFoeRankModifier", &defeatedFoeRankModifier );
	saver.Add( "clanPoints", &clanPoints );
	saver.Add( "normalizeBySessionScores", &normalizeBySessionScores );
	saver.Add( "premiumAccountModifier", &premiumAccountModifier );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsSettings::Assign( const ClanWarsSettings& _clanWarsSettings )
{
	basePoints = _clanWarsSettings.basePoints;
	partyClanMembersModifier = _clanWarsSettings.partyClanMembersModifier;
	foeCountsModifier = _clanWarsSettings.foeCountsModifier;
	defeatedFoeRankModifier = _clanWarsSettings.defeatedFoeRankModifier;
	clanPoints = _clanWarsSettings.clanPoints;
	normalizeBySessionScores = _clanWarsSettings.normalizeBySessionScores;
	premiumAccountModifier = _clanWarsSettings.premiumAccountModifier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ContainersBySpecialPoints::ContainersBySpecialPoints()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ContainersBySpecialPoints::operator&( IBinSaver &saver )
{
	saver.Add( 2, &items );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ContainersBySpecialPoints::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ContainersBySpecialPoints* parentPtr = (ContainersBySpecialPoints*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ContainersBySpecialPoints::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "items", &items );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ContainersBySpecialPoints::Assign( const ContainersBySpecialPoints& _containersBySpecialPoints )
{
	items = _containersBySpecialPoints.items;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlagRollItem::FlagRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &flag );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlagRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FlagRollItem* parentPtr = (FlagRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "flag", &flag );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlagRollItem::Assign( const FlagRollItem& _flagRollItem )
{
	flag = _flagRollItem.flag;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldRollItem::GoldRollItem() :
		count( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GoldRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GoldRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GoldRollItem* parentPtr = (GoldRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GoldRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "count", &count );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GoldRollItem::Assign( const GoldRollItem& _goldRollItem )
{
	count = _goldRollItem.count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GuildLevels::GuildLevels() :
		requiredExpMultiplier( 100000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevels::operator&( IBinSaver &saver )
{
	saver.Add( 2, &requiredExpMultiplier );
	saver.Add( 3, &levels );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GuildLevels::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GuildLevels* parentPtr = (GuildLevels*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildLevels::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "requiredExpMultiplier", &requiredExpMultiplier );
	saver.Add( "levels", &levels );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GuildLevels::Assign( const GuildLevels& _guildLevels )
{
	requiredExpMultiplier = _guildLevels.requiredExpMultiplier;
	levels = _guildLevels.levels;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroRollItem::HeroRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &hero );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroRollItem* parentPtr = (HeroRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "hero", &hero );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRollItem::Assign( const HeroRollItem& _heroRollItem )
{
	hero = _heroRollItem.hero;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapMMakingSettings::MapMMakingSettings() :
		mock( false )
	, isTournamentMap( false )
	, normalBasePointsRepeatFactor( 5 )
	, noobBasePointsRepeatFactor( 40 )
	, ratingDiffGrowTime( 180.0f )
	, fullSweepSubsetLimit( 15 )
	, fullSweepSubsetLimitPve( 15 )
	, estimFunDecreaseTimeBegin( 180 )
	, estimFunDecreaseTimeEnd( 300 )
	, estimFunDecreaseFactor( 0.5f )
	, estimFunManoeuvresDecreaseFactor( 0.5f )
	, identicalHeroesSampleLimit( 1 )
	, identicalGuardHeroesSampleLimit( 1 )
	, identicalNoobHeroesSampleLimit( 2 )
	, lowWaitTimeThreshold( 30 )
	, lowWaitTimeFactor( 2.0f )
	, manoeuvresMinPopulation( 25 )
	, manoeuvresMaxPopulation( 10 )
	, guardManoeuvresMinPopulation( 10 )
	, guardManoeuvresMaxPopulation( 10 )
	, manoeuvresWaitThreshold( 180.0f )
	, manoeuvresFullSweepSubset( 15 )
	, trainingFemaleBotsCount( 1 )
	, necessaryLadiesCount( 1 )
	, highRatingThreshold( 1800 )
	, proRatingThreshold( 2000 )
	, noobGamesMaxNormalRating( 1500 )
	, highRatingCooldown( 60 )
	, noobsTimeout( 45.0f )
	, minimalNoobsPercentage( 60 )
	, fullPartyGameRatingDiffMin( 30 )
	, fullPartyGameRatingDiffMax( 200 )
	, waitTimeSoftLimit( 240 )
	, waitTimeHardLimit( 600 )
	, teamLeaversTimeTrashold( 600 )
	, gameLeaversTimeTrashold( 300 )
	, recessionPremiumTimeThreshold( 0.0f )
	, playerDiff( 5 )
	, rankDifferenceTimePenalty( 180.0f )
	, heroClassLimitsAttenuationTime( 120.0f )
	, useRanking( false )
	, fullPartySize( 5 )
	, fullPartyVsRandomTimeThreshold( 30.0f )
	, localeWaitTimeThreshold( 45 )
	, TeamSideTimeTreshold( 120.0f )
{
	recessionTableForForceMM.resize( 3 );
	optimalClasses.resize( 7 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapMMakingSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &mock );
	saver.Add( 3, &isTournamentMap );
	saver.Add( 4, &estimFunctionWeights );
	saver.Add( 5, &normalBasePointsRepeatFactor );
	saver.Add( 6, &noobBasePointsRepeatFactor );
	saver.Add( 7, &ratingDiffGrowTime );
	saver.Add( 8, &fullSweepSubsetLimit );
	saver.Add( 9, &fullSweepSubsetLimitPve );
	saver.Add( 10, &estimFunDecreaseTimeBegin );
	saver.Add( 11, &estimFunDecreaseTimeEnd );
	saver.Add( 12, &estimFunDecreaseFactor );
	saver.Add( 13, &estimFunManoeuvresDecreaseFactor );
	saver.Add( 14, &identicalHeroesSampleLimit );
	saver.Add( 15, &identicalGuardHeroesSampleLimit );
	saver.Add( 16, &identicalNoobHeroesSampleLimit );
	saver.Add( 17, &lowWaitTimeThreshold );
	saver.Add( 18, &lowWaitTimeFactor );
	saver.Add( 19, &manoeuvresMinPopulation );
	saver.Add( 20, &manoeuvresMaxPopulation );
	saver.Add( 21, &guardManoeuvresMinPopulation );
	saver.Add( 22, &guardManoeuvresMaxPopulation );
	saver.Add( 23, &manoeuvresWaitThreshold );
	saver.Add( 24, &manoeuvresFullSweepSubset );
	saver.Add( 25, &trainingFemaleBotsCount );
	saver.Add( 26, &necessaryLadiesCount );
	saver.Add( 27, &partySkillCompensation );
	saver.Add( 28, &loseStreakCorrection );
	saver.Add( 29, &highRatingThreshold );
	saver.Add( 30, &proRatingThreshold );
	saver.Add( 31, &noobGamesMaxNormalRating );
	saver.Add( 32, &highRatingCooldown );
	saver.Add( 33, &noobsTimeout );
	saver.Add( 34, &minimalNoobsPercentage );
	saver.Add( 35, &fullPartyGameRatingDiffMin );
	saver.Add( 36, &fullPartyGameRatingDiffMax );
	saver.Add( 37, &waitTimeSoftLimit );
	saver.Add( 38, &waitTimeHardLimit );
	saver.Add( 39, &teamLeaversTimeTrashold );
	saver.Add( 40, &gameLeaversTimeTrashold );
	saver.Add( 41, &locationPingSettings );
	saver.Add( 42, &waitVsProbability );
	saver.Add( 43, &ranks );
	saver.Add( 44, &recessionTableForForceMM );
	saver.Add( 45, &recessionPremiumTable );
	saver.Add( 46, &recessionFullPartyTableForForceMM );
	saver.Add( 47, &recessionPremiumTimeThreshold );
	saver.Add( 48, &recessionTableForPlayerRatingMM );
	saver.Add( 49, &playerDiff );
	saver.Add( 50, &rankDifferenceTimePenalty );
	saver.Add( 51, &heroClassLimitsAttenuationTime );
	saver.Add( 52, &useRanking );
	saver.Add( 53, &optimalClasses );
	saver.Add( 54, &delayPerDonorLocalePlayer );
	saver.Add( 55, &fullPartySize );
	saver.Add( 56, &fullPartyVsRandomTimeThreshold );
	saver.Add( 57, &localeWaitTimeThreshold );
	saver.Add( 58, &ratingScale );
	saver.Add( 59, &forceScale );
	saver.Add( 60, &TeamSideTimeTreshold );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MapMMakingSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MapMMakingSettings* parentPtr = (MapMMakingSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapMMakingSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "mock", &mock );
	saver.Add( "isTournamentMap", &isTournamentMap );
	saver.Add( "estimFunctionWeights", &estimFunctionWeights );
	saver.Add( "normalBasePointsRepeatFactor", &normalBasePointsRepeatFactor );
	saver.Add( "noobBasePointsRepeatFactor", &noobBasePointsRepeatFactor );
	saver.Add( "ratingDiffGrowTime", &ratingDiffGrowTime );
	saver.Add( "fullSweepSubsetLimit", &fullSweepSubsetLimit );
	saver.Add( "fullSweepSubsetLimitPve", &fullSweepSubsetLimitPve );
	saver.Add( "estimFunDecreaseTimeBegin", &estimFunDecreaseTimeBegin );
	saver.Add( "estimFunDecreaseTimeEnd", &estimFunDecreaseTimeEnd );
	saver.Add( "estimFunDecreaseFactor", &estimFunDecreaseFactor );
	saver.Add( "estimFunManoeuvresDecreaseFactor", &estimFunManoeuvresDecreaseFactor );
	saver.Add( "identicalHeroesSampleLimit", &identicalHeroesSampleLimit );
	saver.Add( "identicalGuardHeroesSampleLimit", &identicalGuardHeroesSampleLimit );
	saver.Add( "identicalNoobHeroesSampleLimit", &identicalNoobHeroesSampleLimit );
	saver.Add( "lowWaitTimeThreshold", &lowWaitTimeThreshold );
	saver.Add( "lowWaitTimeFactor", &lowWaitTimeFactor );
	saver.Add( "manoeuvresMinPopulation", &manoeuvresMinPopulation );
	saver.Add( "manoeuvresMaxPopulation", &manoeuvresMaxPopulation );
	saver.Add( "guardManoeuvresMinPopulation", &guardManoeuvresMinPopulation );
	saver.Add( "guardManoeuvresMaxPopulation", &guardManoeuvresMaxPopulation );
	saver.Add( "manoeuvresWaitThreshold", &manoeuvresWaitThreshold );
	saver.Add( "manoeuvresFullSweepSubset", &manoeuvresFullSweepSubset );
	saver.Add( "trainingFemaleBotsCount", &trainingFemaleBotsCount );
	saver.Add( "necessaryLadiesCount", &necessaryLadiesCount );
	saver.Add( "partySkillCompensation", &partySkillCompensation );
	saver.Add( "loseStreakCorrection", &loseStreakCorrection );
	saver.Add( "highRatingThreshold", &highRatingThreshold );
	saver.Add( "proRatingThreshold", &proRatingThreshold );
	saver.Add( "noobGamesMaxNormalRating", &noobGamesMaxNormalRating );
	saver.Add( "highRatingCooldown", &highRatingCooldown );
	saver.Add( "noobsTimeout", &noobsTimeout );
	saver.Add( "minimalNoobsPercentage", &minimalNoobsPercentage );
	saver.Add( "fullPartyGameRatingDiffMin", &fullPartyGameRatingDiffMin );
	saver.Add( "fullPartyGameRatingDiffMax", &fullPartyGameRatingDiffMax );
	saver.Add( "waitTimeSoftLimit", &waitTimeSoftLimit );
	saver.Add( "waitTimeHardLimit", &waitTimeHardLimit );
	saver.Add( "teamLeaversTimeTrashold", &teamLeaversTimeTrashold );
	saver.Add( "gameLeaversTimeTrashold", &gameLeaversTimeTrashold );
	saver.Add( "locationPingSettings", &locationPingSettings );
	saver.Add( "waitVsProbability", &waitVsProbability );
	saver.Add( "ranks", &ranks );
	recessionTableForForceMM.resize( 3 );
	saver.Add( "recessionTableForForceMM", &recessionTableForForceMM );
	saver.Add( "recessionPremiumTable", &recessionPremiumTable );
	saver.Add( "recessionFullPartyTableForForceMM", &recessionFullPartyTableForForceMM );
	saver.Add( "recessionPremiumTimeThreshold", &recessionPremiumTimeThreshold );
	saver.Add( "recessionTableForPlayerRatingMM", &recessionTableForPlayerRatingMM );
	saver.Add( "playerDiff", &playerDiff );
	saver.Add( "rankDifferenceTimePenalty", &rankDifferenceTimePenalty );
	saver.Add( "heroClassLimitsAttenuationTime", &heroClassLimitsAttenuationTime );
	saver.Add( "useRanking", &useRanking );
	optimalClasses.resize( 7 );
	saver.Add( "optimalClasses", &optimalClasses );
	saver.Add( "delayPerDonorLocalePlayer", &delayPerDonorLocalePlayer );
	saver.Add( "fullPartySize", &fullPartySize );
	saver.Add( "fullPartyVsRandomTimeThreshold", &fullPartyVsRandomTimeThreshold );
	saver.Add( "localeWaitTimeThreshold", &localeWaitTimeThreshold );
	saver.Add( "ratingScale", &ratingScale );
	saver.Add( "forceScale", &forceScale );
	saver.Add( "TeamSideTimeTreshold", &TeamSideTimeTreshold );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapMMakingSettings::Assign( const MapMMakingSettings& _mapMMakingSettings )
{
	mock = _mapMMakingSettings.mock;
	isTournamentMap = _mapMMakingSettings.isTournamentMap;
	estimFunctionWeights.ladiesNumber = _mapMMakingSettings.estimFunctionWeights.ladiesNumber;
	estimFunctionWeights.genderPairs = _mapMMakingSettings.estimFunctionWeights.genderPairs;
	estimFunctionWeights.heroes = _mapMMakingSettings.estimFunctionWeights.heroes;
	estimFunctionWeights.ratingSpan = _mapMMakingSettings.estimFunctionWeights.ratingSpan;
	estimFunctionWeights.ratingPatternDelta = _mapMMakingSettings.estimFunctionWeights.ratingPatternDelta;
	estimFunctionWeights.ratingTeamAvgDelta = _mapMMakingSettings.estimFunctionWeights.ratingTeamAvgDelta;
	estimFunctionWeights.forceSpan = _mapMMakingSettings.estimFunctionWeights.forceSpan;
	estimFunctionWeights.heroClassesDifference = _mapMMakingSettings.estimFunctionWeights.heroClassesDifference;
	estimFunctionWeights.heroClassesOptimum = _mapMMakingSettings.estimFunctionWeights.heroClassesOptimum;
	normalBasePointsRepeatFactor = _mapMMakingSettings.normalBasePointsRepeatFactor;
	noobBasePointsRepeatFactor = _mapMMakingSettings.noobBasePointsRepeatFactor;
	ratingDiffGrowTime = _mapMMakingSettings.ratingDiffGrowTime;
	fullSweepSubsetLimit = _mapMMakingSettings.fullSweepSubsetLimit;
	fullSweepSubsetLimitPve = _mapMMakingSettings.fullSweepSubsetLimitPve;
	estimFunDecreaseTimeBegin = _mapMMakingSettings.estimFunDecreaseTimeBegin;
	estimFunDecreaseTimeEnd = _mapMMakingSettings.estimFunDecreaseTimeEnd;
	estimFunDecreaseFactor = _mapMMakingSettings.estimFunDecreaseFactor;
	estimFunManoeuvresDecreaseFactor = _mapMMakingSettings.estimFunManoeuvresDecreaseFactor;
	identicalHeroesSampleLimit = _mapMMakingSettings.identicalHeroesSampleLimit;
	identicalGuardHeroesSampleLimit = _mapMMakingSettings.identicalGuardHeroesSampleLimit;
	identicalNoobHeroesSampleLimit = _mapMMakingSettings.identicalNoobHeroesSampleLimit;
	lowWaitTimeThreshold = _mapMMakingSettings.lowWaitTimeThreshold;
	lowWaitTimeFactor = _mapMMakingSettings.lowWaitTimeFactor;
	manoeuvresMinPopulation = _mapMMakingSettings.manoeuvresMinPopulation;
	manoeuvresMaxPopulation = _mapMMakingSettings.manoeuvresMaxPopulation;
	guardManoeuvresMinPopulation = _mapMMakingSettings.guardManoeuvresMinPopulation;
	guardManoeuvresMaxPopulation = _mapMMakingSettings.guardManoeuvresMaxPopulation;
	manoeuvresWaitThreshold = _mapMMakingSettings.manoeuvresWaitThreshold;
	manoeuvresFullSweepSubset = _mapMMakingSettings.manoeuvresFullSweepSubset;
	trainingFemaleBotsCount = _mapMMakingSettings.trainingFemaleBotsCount;
	necessaryLadiesCount = _mapMMakingSettings.necessaryLadiesCount;
	partySkillCompensation = _mapMMakingSettings.partySkillCompensation;
	loseStreakCorrection.minStreak = _mapMMakingSettings.loseStreakCorrection.minStreak;
	loseStreakCorrection.forcePenalty = _mapMMakingSettings.loseStreakCorrection.forcePenalty;
	loseStreakCorrection.ratingPenalty = _mapMMakingSettings.loseStreakCorrection.ratingPenalty;
	loseStreakCorrection.firstCaseThreshold = _mapMMakingSettings.loseStreakCorrection.firstCaseThreshold;
	loseStreakCorrection.firstCasePenalty = _mapMMakingSettings.loseStreakCorrection.firstCasePenalty;
	loseStreakCorrection.secondCaseThreshold = _mapMMakingSettings.loseStreakCorrection.secondCaseThreshold;
	loseStreakCorrection.secondCasePenalty = _mapMMakingSettings.loseStreakCorrection.secondCasePenalty;
	loseStreakCorrection.thirdCaseThreshold = _mapMMakingSettings.loseStreakCorrection.thirdCaseThreshold;
	loseStreakCorrection.thirdCasePenalty = _mapMMakingSettings.loseStreakCorrection.thirdCasePenalty;
	highRatingThreshold = _mapMMakingSettings.highRatingThreshold;
	proRatingThreshold = _mapMMakingSettings.proRatingThreshold;
	noobGamesMaxNormalRating = _mapMMakingSettings.noobGamesMaxNormalRating;
	highRatingCooldown = _mapMMakingSettings.highRatingCooldown;
	noobsTimeout = _mapMMakingSettings.noobsTimeout;
	minimalNoobsPercentage = _mapMMakingSettings.minimalNoobsPercentage;
	fullPartyGameRatingDiffMin = _mapMMakingSettings.fullPartyGameRatingDiffMin;
	fullPartyGameRatingDiffMax = _mapMMakingSettings.fullPartyGameRatingDiffMax;
	waitTimeSoftLimit = _mapMMakingSettings.waitTimeSoftLimit;
	waitTimeHardLimit = _mapMMakingSettings.waitTimeHardLimit;
	teamLeaversTimeTrashold = _mapMMakingSettings.teamLeaversTimeTrashold;
	gameLeaversTimeTrashold = _mapMMakingSettings.gameLeaversTimeTrashold;
	locationPingSettings.nicePingThreshold = _mapMMakingSettings.locationPingSettings.nicePingThreshold;
	locationPingSettings.pingScaleMinFactor = _mapMMakingSettings.locationPingSettings.pingScaleMinFactor;
	locationPingSettings.worstPingWaitTimePenalty = _mapMMakingSettings.locationPingSettings.worstPingWaitTimePenalty;
	locationPingSettings.goodEnoughPingFactor = _mapMMakingSettings.locationPingSettings.goodEnoughPingFactor;
	locationPingSettings.ratingThreshold = _mapMMakingSettings.locationPingSettings.ratingThreshold;
	waitVsProbability.startingWaitTime = _mapMMakingSettings.waitVsProbability.startingWaitTime;
	waitVsProbability.endingWaitTime = _mapMMakingSettings.waitVsProbability.endingWaitTime;
	waitVsProbability.startingProbabilityWeight = _mapMMakingSettings.waitVsProbability.startingProbabilityWeight;
	waitVsProbability.endingProbabilityWeight = _mapMMakingSettings.waitVsProbability.endingProbabilityWeight;
	ranks = _mapMMakingSettings.ranks;
	recessionTableForForceMM = _mapMMakingSettings.recessionTableForForceMM;
	recessionPremiumTable = _mapMMakingSettings.recessionPremiumTable;
	recessionFullPartyTableForForceMM.recessionTable = _mapMMakingSettings.recessionFullPartyTableForForceMM.recessionTable;
	recessionFullPartyTableForForceMM.recessionPremium = _mapMMakingSettings.recessionFullPartyTableForForceMM.recessionPremium;
	recessionPremiumTimeThreshold = _mapMMakingSettings.recessionPremiumTimeThreshold;
	recessionTableForPlayerRatingMM.recessionTable = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionTable;
	recessionTableForPlayerRatingMM.recessionSideDiff = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionSideDiff;
	recessionTableForPlayerRatingMM.recessionPremiumTable = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionPremiumTable;
	recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionPremiumTimeThreshold;
	recessionTableForPlayerRatingMM.recessionMaxPlayerRating = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionMaxPlayerRating;
	recessionTableForPlayerRatingMM.recessionMinPlayerRating = _mapMMakingSettings.recessionTableForPlayerRatingMM.recessionMinPlayerRating;
	playerDiff = _mapMMakingSettings.playerDiff;
	rankDifferenceTimePenalty = _mapMMakingSettings.rankDifferenceTimePenalty;
	heroClassLimitsAttenuationTime = _mapMMakingSettings.heroClassLimitsAttenuationTime;
	useRanking = _mapMMakingSettings.useRanking;
	optimalClasses = _mapMMakingSettings.optimalClasses;
	delayPerDonorLocalePlayer = _mapMMakingSettings.delayPerDonorLocalePlayer;
	fullPartySize = _mapMMakingSettings.fullPartySize;
	fullPartyVsRandomTimeThreshold = _mapMMakingSettings.fullPartyVsRandomTimeThreshold;
	localeWaitTimeThreshold = _mapMMakingSettings.localeWaitTimeThreshold;
	ratingScale.low = _mapMMakingSettings.ratingScale.low;
	ratingScale.high = _mapMMakingSettings.ratingScale.high;
	ratingScale.step = _mapMMakingSettings.ratingScale.step;
	ratingScale.diffLow = _mapMMakingSettings.ratingScale.diffLow;
	ratingScale.diffHigh = _mapMMakingSettings.ratingScale.diffHigh;
	forceScale.low = _mapMMakingSettings.forceScale.low;
	forceScale.high = _mapMMakingSettings.forceScale.high;
	forceScale.step = _mapMMakingSettings.forceScale.step;
	forceScale.diffLow = _mapMMakingSettings.forceScale.diffLow;
	forceScale.diffHigh = _mapMMakingSettings.forceScale.diffHigh;
	TeamSideTimeTreshold = _mapMMakingSettings.TeamSideTimeTreshold;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MarketingEventRollItem::MarketingEventRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarketingEventRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &persistentId );
	saver.Add( 3, &image );
	saver.Add( 4, &tooltip );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MarketingEventRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			MarketingEventRollItem* parentPtr = (MarketingEventRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarketingEventRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "persistentId", &persistentId );
	saver.Add( "image", &image );
	saver.Add( "tooltip", &tooltip );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarketingEventRollItem::Assign( const MarketingEventRollItem& _marketingEventRollItem )
{
	persistentId = _marketingEventRollItem.persistentId;
	image = _marketingEventRollItem.image;
	tooltip = _marketingEventRollItem.tooltip;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModeRollSettings::ModeRollSettings() :
		scoresCap( 90 )
	, containersOnWin( 0 )
	, allowedRollGroups( TALENTROLLGROUP_ALL )
	, enduranceGain( 40 )
	, enduranceCoeff( 0.33f )
	, enduranceFameCoeff( 0.33f )
	, enduranceExperienceCoeff( 0.33f )
	, enduranceResourcesCoeff( 0.33f )
	, leaversAwardsCoeff( 0.3f )
	, reliabilityOnFinishWin( 3 )
	, reliabilityOnFinishLose( 5 )
	, reliabilityOnFinishPeriod( 1800 )
	, reliabilityOnFinishPerPeriod( 1 )
	, reliabilityOnLeave( -3 )
	, reliabilityOnLeavePeriod( 300 )
	, reliabilityOnLeavePerPeriod( -1 )
	, talentsMultiplicator( 1 )
	, enduranceDisableRollBoost( true )
	, fameLoseCoeff( 0.33f )
	, experienceLoseCoeff( 0.33f )
	, resourcesLoseCoeff( 1.0f )
	, dodgePointsOnLeave( 1 )
	, ratingChangeMultiplier( 1.0f )
	, minSessionDuration( 0 )
	, applyPremiumTalent( 0 )
	, version( 0 )
	, teamWinDisconnectedWin( false )
	, fullPartySize( 4 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModeRollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &scoresCap );
	saver.Add( 3, &containersOnWin );
	saver.Add( 4, &containersOnFWOD );
	saver.Add( 5, &containersBySpecialPoints );
	saver.Add( 6, &allowedRollGroups );
	saver.Add( 7, &containers );
	saver.Add( 8, &premiumContainers );
	saver.Add( 9, &additionalPremiumContainers );
	saver.Add( 10, &defaultContainer );
	saver.Add( 11, &eventContainers );
	saver.Add( 12, &premiumEventContainers );
	saver.Add( 13, &enduranceGain );
	saver.Add( 14, &enduranceCoeff );
	saver.Add( 15, &enduranceFameCoeff );
	saver.Add( 16, &enduranceExperienceCoeff );
	saver.Add( 17, &enduranceResourcesCoeff );
	saver.Add( 18, &leaversAwardsCoeff );
	saver.Add( 19, &reliabilityOnFinishWin );
	saver.Add( 20, &reliabilityOnFinishLose );
	saver.Add( 21, &reliabilityOnFinishPeriod );
	saver.Add( 22, &reliabilityOnFinishPerPeriod );
	saver.Add( 23, &reliabilityOnLeave );
	saver.Add( 24, &reliabilityOnLeavePeriod );
	saver.Add( 25, &reliabilityOnLeavePerPeriod );
	saver.Add( 26, &talentsMultiplicator );
	saver.Add( 27, &enduranceDisableRollBoost );
	saver.Add( 28, &famePerSession );
	saver.Add( 29, &fameLoseCoeff );
	saver.Add( 30, &experienceLoseCoeff );
	saver.Add( 31, &resourcesLoseCoeff );
	saver.Add( 32, &experiencePerSession );
	saver.Add( 33, &dodgePointsOnLeave );
	saver.Add( 34, &ratingChangeMultiplier );
	saver.Add( 35, &minSessionDuration );
	saver.Add( 36, &applyPremiumTalent );
	saver.Add( 37, &FWODRewardContainer );
	saver.Add( 38, &modeName );
	saver.Add( 39, &version );
	saver.Add( 40, &teamWinDisconnectedWin );
	saver.Add( 41, &clanWarsSettings );
	saver.Add( 42, &fullPartySize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ModeRollSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ModeRollSettings* parentPtr = (ModeRollSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModeRollSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "scoresCap", &scoresCap );
	saver.Add( "containersOnWin", &containersOnWin );
	saver.Add( "containersOnFWOD", &containersOnFWOD );
	saver.Add( "containersBySpecialPoints", &containersBySpecialPoints );
	saver.Add( "allowedRollGroups", &allowedRollGroups );
	saver.Add( "containers", &containers );
	saver.Add( "premiumContainers", &premiumContainers );
	saver.Add( "additionalPremiumContainers", &additionalPremiumContainers );
	saver.Add( "defaultContainer", &defaultContainer );
	saver.Add( "eventContainers", &eventContainers );
	saver.Add( "premiumEventContainers", &premiumEventContainers );
	saver.Add( "enduranceGain", &enduranceGain );
	saver.Add( "enduranceCoeff", &enduranceCoeff );
	saver.Add( "enduranceFameCoeff", &enduranceFameCoeff );
	saver.Add( "enduranceExperienceCoeff", &enduranceExperienceCoeff );
	saver.Add( "enduranceResourcesCoeff", &enduranceResourcesCoeff );
	saver.Add( "leaversAwardsCoeff", &leaversAwardsCoeff );
	saver.Add( "reliabilityOnFinishWin", &reliabilityOnFinishWin );
	saver.Add( "reliabilityOnFinishLose", &reliabilityOnFinishLose );
	saver.Add( "reliabilityOnFinishPeriod", &reliabilityOnFinishPeriod );
	saver.Add( "reliabilityOnFinishPerPeriod", &reliabilityOnFinishPerPeriod );
	saver.Add( "reliabilityOnLeave", &reliabilityOnLeave );
	saver.Add( "reliabilityOnLeavePeriod", &reliabilityOnLeavePeriod );
	saver.Add( "reliabilityOnLeavePerPeriod", &reliabilityOnLeavePerPeriod );
	saver.Add( "talentsMultiplicator", &talentsMultiplicator );
	saver.Add( "enduranceDisableRollBoost", &enduranceDisableRollBoost );
	saver.Add( "famePerSession", &famePerSession );
	saver.Add( "fameLoseCoeff", &fameLoseCoeff );
	saver.Add( "experienceLoseCoeff", &experienceLoseCoeff );
	saver.Add( "resourcesLoseCoeff", &resourcesLoseCoeff );
	saver.Add( "experiencePerSession", &experiencePerSession );
	saver.Add( "dodgePointsOnLeave", &dodgePointsOnLeave );
	saver.Add( "ratingChangeMultiplier", &ratingChangeMultiplier );
	saver.Add( "minSessionDuration", &minSessionDuration );
	saver.Add( "applyPremiumTalent", &applyPremiumTalent );
	saver.Add( "FWODRewardContainer", &FWODRewardContainer );
	saver.Add( "modeName", &modeName );
	saver.Add( "version", &version );
	saver.Add( "teamWinDisconnectedWin", &teamWinDisconnectedWin );
	saver.Add( "clanWarsSettings", &clanWarsSettings );
	saver.Add( "fullPartySize", &fullPartySize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModeRollSettings::Assign( const ModeRollSettings& _modeRollSettings )
{
	scoresCap = _modeRollSettings.scoresCap;
	containersOnWin = _modeRollSettings.containersOnWin;
	containersOnFWOD = _modeRollSettings.containersOnFWOD;
	containersBySpecialPoints = _modeRollSettings.containersBySpecialPoints;
	allowedRollGroups = _modeRollSettings.allowedRollGroups;
	containers = _modeRollSettings.containers;
	premiumContainers = _modeRollSettings.premiumContainers;
	additionalPremiumContainers = _modeRollSettings.additionalPremiumContainers;
	defaultContainer = _modeRollSettings.defaultContainer;
	eventContainers = _modeRollSettings.eventContainers;
	premiumEventContainers = _modeRollSettings.premiumEventContainers;
	enduranceGain = _modeRollSettings.enduranceGain;
	enduranceCoeff = _modeRollSettings.enduranceCoeff;
	enduranceFameCoeff = _modeRollSettings.enduranceFameCoeff;
	enduranceExperienceCoeff = _modeRollSettings.enduranceExperienceCoeff;
	enduranceResourcesCoeff = _modeRollSettings.enduranceResourcesCoeff;
	leaversAwardsCoeff = _modeRollSettings.leaversAwardsCoeff;
	reliabilityOnFinishWin = _modeRollSettings.reliabilityOnFinishWin;
	reliabilityOnFinishLose = _modeRollSettings.reliabilityOnFinishLose;
	reliabilityOnFinishPeriod = _modeRollSettings.reliabilityOnFinishPeriod;
	reliabilityOnFinishPerPeriod = _modeRollSettings.reliabilityOnFinishPerPeriod;
	reliabilityOnLeave = _modeRollSettings.reliabilityOnLeave;
	reliabilityOnLeavePeriod = _modeRollSettings.reliabilityOnLeavePeriod;
	reliabilityOnLeavePerPeriod = _modeRollSettings.reliabilityOnLeavePerPeriod;
	talentsMultiplicator = _modeRollSettings.talentsMultiplicator;
	enduranceDisableRollBoost = _modeRollSettings.enduranceDisableRollBoost;
	famePerSession = _modeRollSettings.famePerSession;
	fameLoseCoeff = _modeRollSettings.fameLoseCoeff;
	experienceLoseCoeff = _modeRollSettings.experienceLoseCoeff;
	resourcesLoseCoeff = _modeRollSettings.resourcesLoseCoeff;
	experiencePerSession = _modeRollSettings.experiencePerSession;
	dodgePointsOnLeave = _modeRollSettings.dodgePointsOnLeave;
	ratingChangeMultiplier = _modeRollSettings.ratingChangeMultiplier;
	minSessionDuration = _modeRollSettings.minSessionDuration;
	applyPremiumTalent = _modeRollSettings.applyPremiumTalent;
	FWODRewardContainer = _modeRollSettings.FWODRewardContainer;
	modeName = _modeRollSettings.modeName;
	version = _modeRollSettings.version;
	teamWinDisconnectedWin = _modeRollSettings.teamWinDisconnectedWin;
	clanWarsSettings = _modeRollSettings.clanWarsSettings;
	fullPartySize = _modeRollSettings.fullPartySize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NothingRollItem::NothingRollItem() :
		dummy( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NothingRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &dummy );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NothingRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NothingRollItem* parentPtr = (NothingRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NothingRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "dummy", &dummy );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NothingRollItem::Assign( const NothingRollItem& _nothingRollItem )
{
	dummy = _nothingRollItem.dummy;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PremiumAccRollItem::PremiumAccRollItem() :
		days( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumAccRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &days );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PremiumAccRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PremiumAccRollItem* parentPtr = (PremiumAccRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PremiumAccRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "days", &days );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PremiumAccRollItem::Assign( const PremiumAccRollItem& _premiumAccRollItem )
{
	days = _premiumAccRollItem.days;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RarityTalentListRollItem::RarityTalentListRollItem() :
		rarity( TALENTRARITY_CLASS )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RarityTalentListRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &rarity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RarityTalentListRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RarityTalentListRollItem* parentPtr = (RarityTalentListRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RarityTalentListRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "rarity", &rarity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RarityTalentListRollItem::Assign( const RarityTalentListRollItem& _rarityTalentListRollItem )
{
	rarity = _rarityTalentListRollItem.rarity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceRollItem::ResourceRollItem() :
		type( RESOURCEROLLCONSTRAINT_SILVER )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &customCurrencyId );
	saver.Add( 4, &itemsFromLord );
	saver.Add( 5, &itemsFromHero );
	saver.Add( 6, &itemsFromRank );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ResourceRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ResourceRollItem* parentPtr = (ResourceRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "customCurrencyId", &customCurrencyId );
	saver.Add( "itemsFromLord", &itemsFromLord );
	saver.Add( "itemsFromHero", &itemsFromHero );
	saver.Add( "itemsFromRank", &itemsFromRank );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceRollItem::Assign( const ResourceRollItem& _resourceRollItem )
{
	type = _resourceRollItem.type;
	customCurrencyId = _resourceRollItem.customCurrencyId;
	itemsFromLord = _resourceRollItem.itemsFromLord;
	itemsFromHero = _resourceRollItem.itemsFromHero;
	itemsFromRank = _resourceRollItem.itemsFromRank;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainer::RollContainer() :
		multiplicator( 1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainer::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &costByRank );
	saver.Add( 3, &name );
	saver.Add( 4, &items );
	saver.Add( 5, &multiplicator );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainer::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainer* parentPtr = (RollContainer*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainer::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "costByRank", &costByRank );
	saver.Add( "name", &name );
	saver.Add( "items", &items );
	saver.Add( "multiplicator", &multiplicator );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainer::Assign( const RollContainer& _rollContainer )
{
	costByRank = _rollContainer.costByRank;
	name = _rollContainer.name;
	items = _rollContainer.items;
	multiplicator = _rollContainer.multiplicator;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainerCostByRank::RollContainerCostByRank()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCostByRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &costs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCostByRank::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainerCostByRank* parentPtr = (RollContainerCostByRank*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCostByRank::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "costs", &costs );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCostByRank::Assign( const RollContainerCostByRank& _rollContainerCostByRank )
{
	costs = _rollContainerCostByRank.costs;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollContainerCountByRank::RollContainerCountByRank()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCountByRank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &counts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollContainerCountByRank::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollContainerCountByRank* parentPtr = (RollContainerCountByRank*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCountByRank::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "counts", &counts );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollContainerCountByRank::Assign( const RollContainerCountByRank& _rollContainerCountByRank )
{
	counts = _rollContainerCountByRank.counts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClanWarsRollItem::ClanWarsRollItem() :
		type( CLANWARSROLLITEMTYPE_CLANRATING )
	, count( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &type );
	saver.Add( 3, &count );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClanWarsRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ClanWarsRollItem* parentPtr = (ClanWarsRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "type", &type );
	saver.Add( "count", &count );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClanWarsRollItem::Assign( const ClanWarsRollItem& _clanWarsRollItem )
{
	type = _clanWarsRollItem.type;
	count = _clanWarsRollItem.count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RollSettings::RollSettings() :
		requiredLevelForExclusiveTalents( 21 )
	, requiredRatingForExclusiveTalents( 1600 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pvp );
	saver.Add( 3, &defaultRollContainerCostByRank );
	saver.Add( 4, &trainingFWODSettings );
	saver.Add( 5, &ratingModifiers );
	saver.Add( 6, &fullPartyRatingModifiers );
	saver.Add( 7, &forgeRollSettings );
	saver.Add( 8, &guildLevels );
	saver.Add( 9, &requiredLevelForExclusiveTalents );
	saver.Add( 10, &requiredRatingForExclusiveTalents );
	saver.Add( 11, &clanWarsSettings );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RollSettings::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RollSettings* parentPtr = (RollSettings*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollSettings::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "pvp", &pvp );
	saver.Add( "defaultRollContainerCostByRank", &defaultRollContainerCostByRank );
	saver.Add( "trainingFWODSettings", &trainingFWODSettings );
	saver.Add( "ratingModifiers", &ratingModifiers );
	saver.Add( "fullPartyRatingModifiers", &fullPartyRatingModifiers );
	saver.Add( "forgeRollSettings", &forgeRollSettings );
	saver.Add( "guildLevels", &guildLevels );
	saver.Add( "requiredLevelForExclusiveTalents", &requiredLevelForExclusiveTalents );
	saver.Add( "requiredRatingForExclusiveTalents", &requiredRatingForExclusiveTalents );
	saver.Add( "clanWarsSettings", &clanWarsSettings );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollSettings::Assign( const RollSettings& _rollSettings )
{
	pvp = _rollSettings.pvp;
	defaultRollContainerCostByRank = _rollSettings.defaultRollContainerCostByRank;
	trainingFWODSettings = _rollSettings.trainingFWODSettings;
	ratingModifiers = _rollSettings.ratingModifiers;
	fullPartyRatingModifiers = _rollSettings.fullPartyRatingModifiers;
	forgeRollSettings.rollContainer = _rollSettings.forgeRollSettings.rollContainer;
	forgeRollSettings.allowedRollGroups = _rollSettings.forgeRollSettings.allowedRollGroups;
	forgeRollSettings.version = _rollSettings.forgeRollSettings.version;
	guildLevels = _rollSettings.guildLevels;
	requiredLevelForExclusiveTalents = _rollSettings.requiredLevelForExclusiveTalents;
	requiredRatingForExclusiveTalents = _rollSettings.requiredRatingForExclusiveTalents;
	clanWarsSettings = _rollSettings.clanWarsSettings;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkinRollItem::SkinRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &skin );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SkinRollItem* parentPtr = (SkinRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkinRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "skin", &skin );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkinRollItem::Assign( const SkinRollItem& _skinRollItem )
{
	skin = _skinRollItem.skin;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentRollItem::TalentRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &talent );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentRollItem* parentPtr = (TalentRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "talent", &talent );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentRollItem::Assign( const TalentRollItem& _talentRollItem )
{
	talent = _talentRollItem.talent;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeEntity::TalentUpgradeEntity() :
		type( TALENTUPGRADEENTITYTYPE_RUNE )
	, talentLevelLimit( 0 )
	, probability( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntity::operator&( IBinSaver &saver )
{
	saver.Add( 2, &persistentId );
	saver.Add( 3, &type );
	saver.Add( 4, &talentLevelLimit );
	saver.Add( 5, &probability );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntity::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeEntity* parentPtr = (TalentUpgradeEntity*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntity::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "persistentId", &persistentId );
	saver.Add( "type", &type );
	saver.Add( "talentLevelLimit", &talentLevelLimit );
	saver.Add( "probability", &probability );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntity::Assign( const TalentUpgradeEntity& _talentUpgradeEntity )
{
	persistentId = _talentUpgradeEntity.persistentId;
	type = _talentUpgradeEntity.type;
	talentLevelLimit = _talentUpgradeEntity.talentLevelLimit;
	probability = _talentUpgradeEntity.probability;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeEntityRollItem::TalentUpgradeEntityRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntityRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &entity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeEntityRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeEntityRollItem* parentPtr = (TalentUpgradeEntityRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntityRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "entity", &entity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeEntityRollItem::Assign( const TalentUpgradeEntityRollItem& _talentUpgradeEntityRollItem )
{
	entity = _talentUpgradeEntityRollItem.entity;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeProbabilityTable::TalentUpgradeProbabilityTable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbabilityTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &upgrades );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeProbabilityTable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeProbabilityTable* parentPtr = (TalentUpgradeProbabilityTable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeProbabilityTable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "upgrades", &upgrades );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeProbabilityTable::Assign( const TalentUpgradeProbabilityTable& _talentUpgradeProbabilityTable )
{
	upgrades = _talentUpgradeProbabilityTable.upgrades;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TalentUpgradeRollItem::TalentUpgradeRollItem()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeRollItem::operator&( IBinSaver &saver )
{
	saver.Add( 1, (RollItem*)this );
	saver.Add( 2, &upgradeTable );
	saver.Add( 3, &talentItem );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TalentUpgradeRollItem::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TalentUpgradeRollItem* parentPtr = (TalentUpgradeRollItem*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeRollItem::SerializeSelf( IXmlSaver &saver )
{
	RollItem::SerializeSelf( saver );
	saver.Add( "upgradeTable", &upgradeTable );
	saver.Add( "talentItem", &talentItem );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TalentUpgradeRollItem::Assign( const TalentUpgradeRollItem& _talentUpgradeRollItem )
{
	upgradeTable = _talentUpgradeRollItem.upgradeTable;
	talentItem = _talentUpgradeRollItem.talentItem;
}
}; // namespace NDb
