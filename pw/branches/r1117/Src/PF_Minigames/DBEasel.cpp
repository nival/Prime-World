// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../UI/DBUI.h"
#include "../PF_GameLogic/DBConsumable.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../Scene/DBScene.h"
#include "../PF_Core/DBEffect.h"
#include "../Render/DBRenderResources.h"
#include "../Render/DBRender.h"
#include "DBEasel.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( DBEaselChains );
REGISTER_DBRESOURCE( DBEaselCommon );
REGISTER_DBRESOURCE( DBEaselData );
REGISTER_DBRESOURCE( DBEaselGame );
REGISTER_DBRESOURCE( DBEaselPath );
REGISTER_DBRESOURCE( DBEaselSoundsData );
REGISTER_DBRESOURCE( DBEaselSpline );
REGISTER_DBRESOURCE( DBLuxBall );
REGISTER_DBRESOURCE( DBPainterFragment );
REGISTER_DBRESOURCE( DBPainterPoint );
REGISTER_DBRESOURCE( DBPriestessLevelStats );
REGISTER_DBRESOURCE( DBPriestessStats );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DBEaselDropState value )
{
	switch( value )
	{
		case DBEASELDROPSTATE_IDLE:
			return "Idle";
		case DBEASELDROPSTATE_MOVE:
			return "Move";
		case DBEASELDROPSTATE_DEAD:
			return "Dead";
		case DBEASELDROPSTATE_MOVEUNDERGROUND:
			return "MoveUnderground";
		case DBEASELDROPSTATE_JUMPIN:
			return "JumpIn";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DBEaselDropState", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DBEaselDropState StringToEnum_DBEaselDropState( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DBEaselDropState)(NStr::ToInt( value ));
	if ( strcmp( value, "Idle" ) == 0 || strcmp( value, "DBEASELDROPSTATE_IDLE" ) == 0 )
		return DBEASELDROPSTATE_IDLE;
	if ( strcmp( value, "Move" ) == 0 || strcmp( value, "DBEASELDROPSTATE_MOVE" ) == 0 )
		return DBEASELDROPSTATE_MOVE;
	if ( strcmp( value, "Dead" ) == 0 || strcmp( value, "DBEASELDROPSTATE_DEAD" ) == 0 )
		return DBEASELDROPSTATE_DEAD;
	if ( strcmp( value, "MoveUnderground" ) == 0 || strcmp( value, "DBEASELDROPSTATE_MOVEUNDERGROUND" ) == 0 )
		return DBEASELDROPSTATE_MOVEUNDERGROUND;
	if ( strcmp( value, "JumpIn" ) == 0 || strcmp( value, "DBEASELDROPSTATE_JUMPIN" ) == 0 )
		return DBEASELDROPSTATE_JUMPIN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DBEaselDropState", value ) );
	return DBEASELDROPSTATE_IDLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBoostsCategory value )
{
	switch( value )
	{
		case BOOSTSCATEGORY_EASY:
			return "Easy";
		case BOOSTSCATEGORY_MEDIUM:
			return "Medium";
		case BOOSTSCATEGORY_HARD:
			return "Hard";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBoostsCategory", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBoostsCategory StringToEnum_EBoostsCategory( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBoostsCategory)(NStr::ToInt( value ));
	if ( strcmp( value, "Easy" ) == 0 || strcmp( value, "BOOSTSCATEGORY_EASY" ) == 0 )
		return BOOSTSCATEGORY_EASY;
	if ( strcmp( value, "Medium" ) == 0 || strcmp( value, "BOOSTSCATEGORY_MEDIUM" ) == 0 )
		return BOOSTSCATEGORY_MEDIUM;
	if ( strcmp( value, "Hard" ) == 0 || strcmp( value, "BOOSTSCATEGORY_HARD" ) == 0 )
		return BOOSTSCATEGORY_HARD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBoostsCategory", value ) );
	return BOOSTSCATEGORY_EASY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBoostType value )
{
	switch( value )
	{
		case BOOSTTYPE_UNKNOWN:
			return "Unknown";
		case BOOSTTYPE_PAINTBLAST:
			return "PaintBlast";
		case BOOSTTYPE_FREEZE:
			return "Freeze";
		case BOOSTTYPE_JOKER:
			return "Joker";
		case BOOSTTYPE_INSPIRATION:
			return "Inspiration";
		case BOOSTTYPE_BRIGHTENING:
			return "Brightening";
		case BOOSTTYPE_SORTER:
			return "Sorter";
		case BOOSTTYPE_MAGNET:
			return "Magnet";
		case BOOSTTYPE_ALCHEMIST:
			return "Alchemist";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBoostType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBoostType StringToEnum_EBoostType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBoostType)(NStr::ToInt( value ));
	if ( strcmp( value, "Unknown" ) == 0 || strcmp( value, "BOOSTTYPE_UNKNOWN" ) == 0 )
		return BOOSTTYPE_UNKNOWN;
	if ( strcmp( value, "PaintBlast" ) == 0 || strcmp( value, "BOOSTTYPE_PAINTBLAST" ) == 0 )
		return BOOSTTYPE_PAINTBLAST;
	if ( strcmp( value, "Freeze" ) == 0 || strcmp( value, "BOOSTTYPE_FREEZE" ) == 0 )
		return BOOSTTYPE_FREEZE;
	if ( strcmp( value, "Joker" ) == 0 || strcmp( value, "BOOSTTYPE_JOKER" ) == 0 )
		return BOOSTTYPE_JOKER;
	if ( strcmp( value, "Inspiration" ) == 0 || strcmp( value, "BOOSTTYPE_INSPIRATION" ) == 0 )
		return BOOSTTYPE_INSPIRATION;
	if ( strcmp( value, "Brightening" ) == 0 || strcmp( value, "BOOSTTYPE_BRIGHTENING" ) == 0 )
		return BOOSTTYPE_BRIGHTENING;
	if ( strcmp( value, "Sorter" ) == 0 || strcmp( value, "BOOSTTYPE_SORTER" ) == 0 )
		return BOOSTTYPE_SORTER;
	if ( strcmp( value, "Magnet" ) == 0 || strcmp( value, "BOOSTTYPE_MAGNET" ) == 0 )
		return BOOSTTYPE_MAGNET;
	if ( strcmp( value, "Alchemist" ) == 0 || strcmp( value, "BOOSTTYPE_ALCHEMIST" ) == 0 )
		return BOOSTTYPE_ALCHEMIST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBoostType", value ) );
	return BOOSTTYPE_UNKNOWN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EBoostUsage value )
{
	switch( value )
	{
		case BOOSTUSAGE_UNKNOWN:
			return "Unknown";
		case BOOSTUSAGE_INGAME:
			return "InGame";
		case BOOSTUSAGE_ATEXIT:
			return "AtExit";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EBoostUsage", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EBoostUsage StringToEnum_EBoostUsage( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EBoostUsage)(NStr::ToInt( value ));
	if ( strcmp( value, "Unknown" ) == 0 || strcmp( value, "BOOSTUSAGE_UNKNOWN" ) == 0 )
		return BOOSTUSAGE_UNKNOWN;
	if ( strcmp( value, "InGame" ) == 0 || strcmp( value, "BOOSTUSAGE_INGAME" ) == 0 )
		return BOOSTUSAGE_INGAME;
	if ( strcmp( value, "AtExit" ) == 0 || strcmp( value, "BOOSTUSAGE_ATEXIT" ) == 0 )
		return BOOSTUSAGE_ATEXIT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EBoostUsage", value ) );
	return BOOSTUSAGE_UNKNOWN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EChainsStatisticsType value )
{
	switch( value )
	{
		case CHAINSSTATISTICSTYPE_FIRST_VISIBLE_CHAIN:
			return "first_visible_chain";
		case CHAINSSTATISTICSTYPE_ALL_VISIBLE_BALLS:
			return "all_visible_balls";
		case CHAINSSTATISTICSTYPE_ALL_CHAINS:
			return "all_chains";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EChainsStatisticsType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EChainsStatisticsType StringToEnum_EChainsStatisticsType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EChainsStatisticsType)(NStr::ToInt( value ));
	if ( strcmp( value, "first_visible_chain" ) == 0 || strcmp( value, "CHAINSSTATISTICSTYPE_FIRST_VISIBLE_CHAIN" ) == 0 )
		return CHAINSSTATISTICSTYPE_FIRST_VISIBLE_CHAIN;
	if ( strcmp( value, "all_visible_balls" ) == 0 || strcmp( value, "CHAINSSTATISTICSTYPE_ALL_VISIBLE_BALLS" ) == 0 )
		return CHAINSSTATISTICSTYPE_ALL_VISIBLE_BALLS;
	if ( strcmp( value, "all_chains" ) == 0 || strcmp( value, "CHAINSSTATISTICSTYPE_ALL_CHAINS" ) == 0 )
		return CHAINSSTATISTICSTYPE_ALL_CHAINS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EChainsStatisticsType", value ) );
	return CHAINSSTATISTICSTYPE_FIRST_VISIBLE_CHAIN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EColor value )
{
	switch( value )
	{
		case COLOR_BLACK:
			return "black";
		case COLOR_BLUE:
			return "blue";
		case COLOR_GREEN:
			return "green";
		case COLOR_RED:
			return "red";
		case COLOR_WHITE:
			return "white";
		case COLOR_CYAN:
			return "cyan";
		case COLOR_YELLOW:
			return "yellow";
		case COLOR_MAGENTA:
			return "magenta";
		case COLOR_ANY:
			return "any";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EColor", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EColor StringToEnum_EColor( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EColor)(NStr::ToInt( value ));
	if ( strcmp( value, "black" ) == 0 || strcmp( value, "COLOR_BLACK" ) == 0 )
		return COLOR_BLACK;
	if ( strcmp( value, "blue" ) == 0 || strcmp( value, "COLOR_BLUE" ) == 0 )
		return COLOR_BLUE;
	if ( strcmp( value, "green" ) == 0 || strcmp( value, "COLOR_GREEN" ) == 0 )
		return COLOR_GREEN;
	if ( strcmp( value, "red" ) == 0 || strcmp( value, "COLOR_RED" ) == 0 )
		return COLOR_RED;
	if ( strcmp( value, "white" ) == 0 || strcmp( value, "COLOR_WHITE" ) == 0 )
		return COLOR_WHITE;
	if ( strcmp( value, "cyan" ) == 0 || strcmp( value, "COLOR_CYAN" ) == 0 )
		return COLOR_CYAN;
	if ( strcmp( value, "yellow" ) == 0 || strcmp( value, "COLOR_YELLOW" ) == 0 )
		return COLOR_YELLOW;
	if ( strcmp( value, "magenta" ) == 0 || strcmp( value, "COLOR_MAGENTA" ) == 0 )
		return COLOR_MAGENTA;
	if ( strcmp( value, "any" ) == 0 || strcmp( value, "COLOR_ANY" ) == 0 )
		return COLOR_ANY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EColor", value ) );
	return COLOR_BLACK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EComboType value )
{
	switch( value )
	{
		case COMBOTYPE_NONE:
			return "none";
		case COMBOTYPE_X2:
			return "x2";
		case COMBOTYPE_X3:
			return "x3";
		case COMBOTYPE_X4:
			return "x4";
		case COMBOTYPE_X6:
			return "x6";
		case COMBOTYPE_X8:
			return "x8";
		case COMBOTYPE_X9:
			return "x9";
		case COMBOTYPE_X16:
			return "x16";
		case COMBOTYPE_PLUS3:
			return "plus3";
		case COMBOTYPE_PLUS10:
			return "plus10";
		case COMBOTYPE_PLUS20:
			return "plus20";
		case COMBOTYPE_GODLIKE:
			return "godlike";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EComboType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EComboType StringToEnum_EComboType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EComboType)(NStr::ToInt( value ));
	if ( strcmp( value, "none" ) == 0 || strcmp( value, "COMBOTYPE_NONE" ) == 0 )
		return COMBOTYPE_NONE;
	if ( strcmp( value, "x2" ) == 0 || strcmp( value, "COMBOTYPE_X2" ) == 0 )
		return COMBOTYPE_X2;
	if ( strcmp( value, "x3" ) == 0 || strcmp( value, "COMBOTYPE_X3" ) == 0 )
		return COMBOTYPE_X3;
	if ( strcmp( value, "x4" ) == 0 || strcmp( value, "COMBOTYPE_X4" ) == 0 )
		return COMBOTYPE_X4;
	if ( strcmp( value, "x6" ) == 0 || strcmp( value, "COMBOTYPE_X6" ) == 0 )
		return COMBOTYPE_X6;
	if ( strcmp( value, "x8" ) == 0 || strcmp( value, "COMBOTYPE_X8" ) == 0 )
		return COMBOTYPE_X8;
	if ( strcmp( value, "x9" ) == 0 || strcmp( value, "COMBOTYPE_X9" ) == 0 )
		return COMBOTYPE_X9;
	if ( strcmp( value, "x16" ) == 0 || strcmp( value, "COMBOTYPE_X16" ) == 0 )
		return COMBOTYPE_X16;
	if ( strcmp( value, "plus3" ) == 0 || strcmp( value, "COMBOTYPE_PLUS3" ) == 0 )
		return COMBOTYPE_PLUS3;
	if ( strcmp( value, "plus10" ) == 0 || strcmp( value, "COMBOTYPE_PLUS10" ) == 0 )
		return COMBOTYPE_PLUS10;
	if ( strcmp( value, "plus20" ) == 0 || strcmp( value, "COMBOTYPE_PLUS20" ) == 0 )
		return COMBOTYPE_PLUS20;
	if ( strcmp( value, "godlike" ) == 0 || strcmp( value, "COMBOTYPE_GODLIKE" ) == 0 )
		return COMBOTYPE_GODLIKE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EComboType", value ) );
	return COMBOTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ECursor value )
{
	switch( value )
	{
		case CURSOR_AIM:
			return "aim";
		case CURSOR_PAINTBLAST:
			return "paintblast";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ECursor", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ECursor StringToEnum_ECursor( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ECursor)(NStr::ToInt( value ));
	if ( strcmp( value, "aim" ) == 0 || strcmp( value, "CURSOR_AIM" ) == 0 )
		return CURSOR_AIM;
	if ( strcmp( value, "paintblast" ) == 0 || strcmp( value, "CURSOR_PAINTBLAST" ) == 0 )
		return CURSOR_PAINTBLAST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ECursor", value ) );
	return CURSOR_AIM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDifficultyLevel value )
{
	switch( value )
	{
		case DIFFICULTYLEVEL_UNKNOWN:
			return "Unknown";
		case DIFFICULTYLEVEL_EASY:
			return "Easy";
		case DIFFICULTYLEVEL_MEDIUM:
			return "Medium";
		case DIFFICULTYLEVEL_HARD:
			return "Hard";
		case DIFFICULTYLEVEL_IMPOSSIBLE:
			return "Impossible";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDifficultyLevel", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDifficultyLevel StringToEnum_EDifficultyLevel( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDifficultyLevel)(NStr::ToInt( value ));
	if ( strcmp( value, "Unknown" ) == 0 || strcmp( value, "DIFFICULTYLEVEL_UNKNOWN" ) == 0 )
		return DIFFICULTYLEVEL_UNKNOWN;
	if ( strcmp( value, "Easy" ) == 0 || strcmp( value, "DIFFICULTYLEVEL_EASY" ) == 0 )
		return DIFFICULTYLEVEL_EASY;
	if ( strcmp( value, "Medium" ) == 0 || strcmp( value, "DIFFICULTYLEVEL_MEDIUM" ) == 0 )
		return DIFFICULTYLEVEL_MEDIUM;
	if ( strcmp( value, "Hard" ) == 0 || strcmp( value, "DIFFICULTYLEVEL_HARD" ) == 0 )
		return DIFFICULTYLEVEL_HARD;
	if ( strcmp( value, "Impossible" ) == 0 || strcmp( value, "DIFFICULTYLEVEL_IMPOSSIBLE" ) == 0 )
		return DIFFICULTYLEVEL_IMPOSSIBLE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDifficultyLevel", value ) );
	return DIFFICULTYLEVEL_UNKNOWN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEaselRoundStatus value )
{
	switch( value )
	{
		case EASELROUNDSTATUS_UNINITIALIZED:
			return "Uninitialized";
		case EASELROUNDSTATUS_INCOMPLETE:
			return "Incomplete";
		case EASELROUNDSTATUS_WON:
			return "Won";
		case EASELROUNDSTATUS_FAILED:
			return "Failed";
		case EASELROUNDSTATUS_CANCELED:
			return "Canceled";
		case EASELROUNDSTATUS_CANCELEDBYSESSION:
			return "CanceledBySession";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEaselRoundStatus", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEaselRoundStatus StringToEnum_EEaselRoundStatus( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEaselRoundStatus)(NStr::ToInt( value ));
	if ( strcmp( value, "Uninitialized" ) == 0 || strcmp( value, "EASELROUNDSTATUS_UNINITIALIZED" ) == 0 )
		return EASELROUNDSTATUS_UNINITIALIZED;
	if ( strcmp( value, "Incomplete" ) == 0 || strcmp( value, "EASELROUNDSTATUS_INCOMPLETE" ) == 0 )
		return EASELROUNDSTATUS_INCOMPLETE;
	if ( strcmp( value, "Won" ) == 0 || strcmp( value, "EASELROUNDSTATUS_WON" ) == 0 )
		return EASELROUNDSTATUS_WON;
	if ( strcmp( value, "Failed" ) == 0 || strcmp( value, "EASELROUNDSTATUS_FAILED" ) == 0 )
		return EASELROUNDSTATUS_FAILED;
	if ( strcmp( value, "Canceled" ) == 0 || strcmp( value, "EASELROUNDSTATUS_CANCELED" ) == 0 )
		return EASELROUNDSTATUS_CANCELED;
	if ( strcmp( value, "CanceledBySession" ) == 0 || strcmp( value, "EASELROUNDSTATUS_CANCELEDBYSESSION" ) == 0 )
		return EASELROUNDSTATUS_CANCELEDBYSESSION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEaselRoundStatus", value ) );
	return EASELROUNDSTATUS_UNINITIALIZED;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEaselSoundType value )
{
	switch( value )
	{
		case EASELSOUNDTYPE_BALLFIRED:
			return "ballfired";
		case EASELSOUNDTYPE_BALLHIT:
			return "ballhit";
		case EASELSOUNDTYPE_BALLMISS:
			return "ballmiss";
		case EASELSOUNDTYPE_BALLCOLORCHANGED:
			return "ballcolorchanged";
		case EASELSOUNDTYPE_BALLEXPLODED:
			return "ballexploded";
		case EASELSOUNDTYPE_BALLHIT_COLOR_MATCH:
			return "ballhit_color_match";
		case EASELSOUNDTYPE_BALLHIT_COLOR_MISSMATCH:
			return "ballhit_color_missmatch";
		case EASELSOUNDTYPE_GAME_WIN:
			return "game_win";
		case EASELSOUNDTYPE_GAME_LOOSE:
			return "game_loose";
		case EASELSOUNDTYPE_BOOST_BRIGHTEN_CLICK:
			return "boost_brighten_click";
		case EASELSOUNDTYPE_BOOST_FREEZE_CLICK:
			return "boost_freeze_click";
		case EASELSOUNDTYPE_BOOST_INSPIRE_CLICK:
			return "boost_inspire_click";
		case EASELSOUNDTYPE_BOOST_JOKER_CLICK:
			return "boost_joker_click";
		case EASELSOUNDTYPE_BOOST_PAINTBLAST_CLICK:
			return "boost_paintblast_click";
		case EASELSOUNDTYPE_BOOST_PAINTBLAST_EXPLOSION:
			return "boost_paintblast_explosion";
		case EASELSOUNDTYPE_BOOST_SPEEDBALL_CLICK:
			return "boost_speedball_click";
		case EASELSOUNDTYPE_BOOST_SPEEDBALL_FIRED:
			return "boost_speedball_fired";
		case EASELSOUNDTYPE_EXPLOSION_COMBO_2X:
			return "explosion_combo_2x";
		case EASELSOUNDTYPE_EXPLOSION_COMBO_3X:
			return "explosion_combo_3x";
		case EASELSOUNDTYPE_EXPLOSION_COMBO_4X:
			return "explosion_combo_4x";
		case EASELSOUNDTYPE_EXPLOSION_COMBO_5X:
			return "explosion_combo_5x";
		case EASELSOUNDTYPE_PAINT_FLOW:
			return "paint_flow";
		case EASELSOUNDTYPE_CHAINS_MOVING:
			return "chains_moving";
		case EASELSOUNDTYPE_DROP_SLIDING_LOW:
			return "drop_sliding_low";
		case EASELSOUNDTYPE_DROP_SLIDING_HIGH:
			return "drop_sliding_high";
		case EASELSOUNDTYPE_LEVEL_SCROLL_START:
			return "level_scroll_start";
		case EASELSOUNDTYPE_LEVEL_SCROLL_END:
			return "level_scroll_end";
		case EASELSOUNDTYPE_CHAIN_NEAR_EXIT:
			return "chain_near_exit";
		case EASELSOUNDTYPE_CHAIN_NEAR_EXIT_ZZ:
			return "chain_near_exit_zz";
		case EASELSOUNDTYPE_CHAIN_REACHED_END:
			return "chain_reached_end";
		case EASELSOUNDTYPE_CHAIN_DESTROYED:
			return "chain_destroyed";
		case EASELSOUNDTYPE_CHAIN_MERGED:
			return "chain_merged";
		case EASELSOUNDTYPE_RESULT_GOLD_MEDAL:
			return "result_gold_medal";
		case EASELSOUNDTYPE_RESULT_SILVER_MEDAL:
			return "result_silver_medal";
		case EASELSOUNDTYPE_SCORPION_START:
			return "scorpion_start";
		case EASELSOUNDTYPE_NEW_BOOST_OBTAINED:
			return "new_boost_obtained";
		case EASELSOUNDTYPE_BALL_IN_TUNNEL:
			return "ball_in_tunnel";
		case EASELSOUNDTYPE_BALL_OUT_TUNNEL:
			return "ball_out_tunnel";
		case EASELSOUNDTYPE_TUNNEL_APPEARED:
			return "tunnel_appeared";
		case EASELSOUNDTYPE_COIN_CATCHED:
			return "coin_catched";
		case EASELSOUNDTYPE_BOOST_SORTER_CLICK:
			return "boost_sorter_click";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEaselSoundType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEaselSoundType StringToEnum_EEaselSoundType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEaselSoundType)(NStr::ToInt( value ));
	if ( strcmp( value, "ballfired" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLFIRED" ) == 0 )
		return EASELSOUNDTYPE_BALLFIRED;
	if ( strcmp( value, "ballhit" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLHIT" ) == 0 )
		return EASELSOUNDTYPE_BALLHIT;
	if ( strcmp( value, "ballmiss" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLMISS" ) == 0 )
		return EASELSOUNDTYPE_BALLMISS;
	if ( strcmp( value, "ballcolorchanged" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLCOLORCHANGED" ) == 0 )
		return EASELSOUNDTYPE_BALLCOLORCHANGED;
	if ( strcmp( value, "ballexploded" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLEXPLODED" ) == 0 )
		return EASELSOUNDTYPE_BALLEXPLODED;
	if ( strcmp( value, "ballhit_color_match" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLHIT_COLOR_MATCH" ) == 0 )
		return EASELSOUNDTYPE_BALLHIT_COLOR_MATCH;
	if ( strcmp( value, "ballhit_color_missmatch" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALLHIT_COLOR_MISSMATCH" ) == 0 )
		return EASELSOUNDTYPE_BALLHIT_COLOR_MISSMATCH;
	if ( strcmp( value, "game_win" ) == 0 || strcmp( value, "EASELSOUNDTYPE_GAME_WIN" ) == 0 )
		return EASELSOUNDTYPE_GAME_WIN;
	if ( strcmp( value, "game_loose" ) == 0 || strcmp( value, "EASELSOUNDTYPE_GAME_LOOSE" ) == 0 )
		return EASELSOUNDTYPE_GAME_LOOSE;
	if ( strcmp( value, "boost_brighten_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_BRIGHTEN_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_BRIGHTEN_CLICK;
	if ( strcmp( value, "boost_freeze_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_FREEZE_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_FREEZE_CLICK;
	if ( strcmp( value, "boost_inspire_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_INSPIRE_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_INSPIRE_CLICK;
	if ( strcmp( value, "boost_joker_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_JOKER_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_JOKER_CLICK;
	if ( strcmp( value, "boost_paintblast_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_PAINTBLAST_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_PAINTBLAST_CLICK;
	if ( strcmp( value, "boost_paintblast_explosion" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_PAINTBLAST_EXPLOSION" ) == 0 )
		return EASELSOUNDTYPE_BOOST_PAINTBLAST_EXPLOSION;
	if ( strcmp( value, "boost_speedball_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_SPEEDBALL_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_SPEEDBALL_CLICK;
	if ( strcmp( value, "boost_speedball_fired" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_SPEEDBALL_FIRED" ) == 0 )
		return EASELSOUNDTYPE_BOOST_SPEEDBALL_FIRED;
	if ( strcmp( value, "explosion_combo_2x" ) == 0 || strcmp( value, "EASELSOUNDTYPE_EXPLOSION_COMBO_2X" ) == 0 )
		return EASELSOUNDTYPE_EXPLOSION_COMBO_2X;
	if ( strcmp( value, "explosion_combo_3x" ) == 0 || strcmp( value, "EASELSOUNDTYPE_EXPLOSION_COMBO_3X" ) == 0 )
		return EASELSOUNDTYPE_EXPLOSION_COMBO_3X;
	if ( strcmp( value, "explosion_combo_4x" ) == 0 || strcmp( value, "EASELSOUNDTYPE_EXPLOSION_COMBO_4X" ) == 0 )
		return EASELSOUNDTYPE_EXPLOSION_COMBO_4X;
	if ( strcmp( value, "explosion_combo_5x" ) == 0 || strcmp( value, "EASELSOUNDTYPE_EXPLOSION_COMBO_5X" ) == 0 )
		return EASELSOUNDTYPE_EXPLOSION_COMBO_5X;
	if ( strcmp( value, "paint_flow" ) == 0 || strcmp( value, "EASELSOUNDTYPE_PAINT_FLOW" ) == 0 )
		return EASELSOUNDTYPE_PAINT_FLOW;
	if ( strcmp( value, "chains_moving" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAINS_MOVING" ) == 0 )
		return EASELSOUNDTYPE_CHAINS_MOVING;
	if ( strcmp( value, "drop_sliding_low" ) == 0 || strcmp( value, "EASELSOUNDTYPE_DROP_SLIDING_LOW" ) == 0 )
		return EASELSOUNDTYPE_DROP_SLIDING_LOW;
	if ( strcmp( value, "drop_sliding_high" ) == 0 || strcmp( value, "EASELSOUNDTYPE_DROP_SLIDING_HIGH" ) == 0 )
		return EASELSOUNDTYPE_DROP_SLIDING_HIGH;
	if ( strcmp( value, "level_scroll_start" ) == 0 || strcmp( value, "EASELSOUNDTYPE_LEVEL_SCROLL_START" ) == 0 )
		return EASELSOUNDTYPE_LEVEL_SCROLL_START;
	if ( strcmp( value, "level_scroll_end" ) == 0 || strcmp( value, "EASELSOUNDTYPE_LEVEL_SCROLL_END" ) == 0 )
		return EASELSOUNDTYPE_LEVEL_SCROLL_END;
	if ( strcmp( value, "chain_near_exit" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAIN_NEAR_EXIT" ) == 0 )
		return EASELSOUNDTYPE_CHAIN_NEAR_EXIT;
	if ( strcmp( value, "chain_near_exit_zz" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAIN_NEAR_EXIT_ZZ" ) == 0 )
		return EASELSOUNDTYPE_CHAIN_NEAR_EXIT_ZZ;
	if ( strcmp( value, "chain_reached_end" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAIN_REACHED_END" ) == 0 )
		return EASELSOUNDTYPE_CHAIN_REACHED_END;
	if ( strcmp( value, "chain_destroyed" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAIN_DESTROYED" ) == 0 )
		return EASELSOUNDTYPE_CHAIN_DESTROYED;
	if ( strcmp( value, "chain_merged" ) == 0 || strcmp( value, "EASELSOUNDTYPE_CHAIN_MERGED" ) == 0 )
		return EASELSOUNDTYPE_CHAIN_MERGED;
	if ( strcmp( value, "result_gold_medal" ) == 0 || strcmp( value, "EASELSOUNDTYPE_RESULT_GOLD_MEDAL" ) == 0 )
		return EASELSOUNDTYPE_RESULT_GOLD_MEDAL;
	if ( strcmp( value, "result_silver_medal" ) == 0 || strcmp( value, "EASELSOUNDTYPE_RESULT_SILVER_MEDAL" ) == 0 )
		return EASELSOUNDTYPE_RESULT_SILVER_MEDAL;
	if ( strcmp( value, "scorpion_start" ) == 0 || strcmp( value, "EASELSOUNDTYPE_SCORPION_START" ) == 0 )
		return EASELSOUNDTYPE_SCORPION_START;
	if ( strcmp( value, "new_boost_obtained" ) == 0 || strcmp( value, "EASELSOUNDTYPE_NEW_BOOST_OBTAINED" ) == 0 )
		return EASELSOUNDTYPE_NEW_BOOST_OBTAINED;
	if ( strcmp( value, "ball_in_tunnel" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALL_IN_TUNNEL" ) == 0 )
		return EASELSOUNDTYPE_BALL_IN_TUNNEL;
	if ( strcmp( value, "ball_out_tunnel" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BALL_OUT_TUNNEL" ) == 0 )
		return EASELSOUNDTYPE_BALL_OUT_TUNNEL;
	if ( strcmp( value, "tunnel_appeared" ) == 0 || strcmp( value, "EASELSOUNDTYPE_TUNNEL_APPEARED" ) == 0 )
		return EASELSOUNDTYPE_TUNNEL_APPEARED;
	if ( strcmp( value, "coin_catched" ) == 0 || strcmp( value, "EASELSOUNDTYPE_COIN_CATCHED" ) == 0 )
		return EASELSOUNDTYPE_COIN_CATCHED;
	if ( strcmp( value, "boost_sorter_click" ) == 0 || strcmp( value, "EASELSOUNDTYPE_BOOST_SORTER_CLICK" ) == 0 )
		return EASELSOUNDTYPE_BOOST_SORTER_CLICK;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEaselSoundType", value ) );
	return EASELSOUNDTYPE_BALLFIRED;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFallingObject value )
{
	switch( value )
	{
		case FALLINGOBJECT_COIN:
			return "coin";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFallingObject", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFallingObject StringToEnum_EFallingObject( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFallingObject)(NStr::ToInt( value ));
	if ( strcmp( value, "coin" ) == 0 || strcmp( value, "FALLINGOBJECT_COIN" ) == 0 )
		return FALLINGOBJECT_COIN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFallingObject", value ) );
	return FALLINGOBJECT_COIN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPaintType value )
{
	switch( value )
	{
		case PAINTTYPE_TYPE_0:
			return "type_0";
		case PAINTTYPE_TYPE_1:
			return "type_1";
		case PAINTTYPE_TYPE_2:
			return "type_2";
		case PAINTTYPE_TYPE_3:
			return "type_3";
		case PAINTTYPE_TYPE_4:
			return "type_4";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPaintType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPaintType StringToEnum_EPaintType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPaintType)(NStr::ToInt( value ));
	if ( strcmp( value, "type_0" ) == 0 || strcmp( value, "PAINTTYPE_TYPE_0" ) == 0 )
		return PAINTTYPE_TYPE_0;
	if ( strcmp( value, "type_1" ) == 0 || strcmp( value, "PAINTTYPE_TYPE_1" ) == 0 )
		return PAINTTYPE_TYPE_1;
	if ( strcmp( value, "type_2" ) == 0 || strcmp( value, "PAINTTYPE_TYPE_2" ) == 0 )
		return PAINTTYPE_TYPE_2;
	if ( strcmp( value, "type_3" ) == 0 || strcmp( value, "PAINTTYPE_TYPE_3" ) == 0 )
		return PAINTTYPE_TYPE_3;
	if ( strcmp( value, "type_4" ) == 0 || strcmp( value, "PAINTTYPE_TYPE_4" ) == 0 )
		return PAINTTYPE_TYPE_4;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPaintType", value ) );
	return PAINTTYPE_TYPE_0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPriestessLevel value )
{
	switch( value )
	{
		case PRIESTESSLEVEL_LEVEL_0:
			return "level_0";
		case PRIESTESSLEVEL_LEVEL_1:
			return "level_1";
		case PRIESTESSLEVEL_LEVEL_2:
			return "level_2";
		case PRIESTESSLEVEL_LEVEL_3:
			return "level_3";
		case PRIESTESSLEVEL_LEVEL_4:
			return "level_4";
		case PRIESTESSLEVEL_LEVEL_5:
			return "level_5";
		case PRIESTESSLEVEL_LEVEL_6:
			return "level_6";
		case PRIESTESSLEVEL_LEVEL_7:
			return "level_7";
		case PRIESTESSLEVEL_LEVEL_8:
			return "level_8";
		case PRIESTESSLEVEL_LEVEL_9:
			return "level_9";
		case PRIESTESSLEVEL_LEVEL_10:
			return "level_10";
		case PRIESTESSLEVEL_LEVEL_11:
			return "level_11";
		case PRIESTESSLEVEL_LEVEL_12:
			return "level_12";
		case PRIESTESSLEVEL_LEVEL_13:
			return "level_13";
		case PRIESTESSLEVEL_LEVEL_14:
			return "level_14";
		case PRIESTESSLEVEL_LEVEL_15:
			return "level_15";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPriestessLevel", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPriestessLevel StringToEnum_EPriestessLevel( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPriestessLevel)(NStr::ToInt( value ));
	if ( strcmp( value, "level_0" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_0" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_0;
	if ( strcmp( value, "level_1" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_1" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_1;
	if ( strcmp( value, "level_2" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_2" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_2;
	if ( strcmp( value, "level_3" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_3" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_3;
	if ( strcmp( value, "level_4" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_4" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_4;
	if ( strcmp( value, "level_5" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_5" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_5;
	if ( strcmp( value, "level_6" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_6" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_6;
	if ( strcmp( value, "level_7" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_7" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_7;
	if ( strcmp( value, "level_8" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_8" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_8;
	if ( strcmp( value, "level_9" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_9" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_9;
	if ( strcmp( value, "level_10" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_10" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_10;
	if ( strcmp( value, "level_11" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_11" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_11;
	if ( strcmp( value, "level_12" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_12" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_12;
	if ( strcmp( value, "level_13" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_13" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_13;
	if ( strcmp( value, "level_14" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_14" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_14;
	if ( strcmp( value, "level_15" ) == 0 || strcmp( value, "PRIESTESSLEVEL_LEVEL_15" ) == 0 )
		return PRIESTESSLEVEL_LEVEL_15;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPriestessLevel", value ) );
	return PRIESTESSLEVEL_LEVEL_0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const WonGameHearts value )
{
	switch( value )
	{
		case WONGAMEHEARTS_LEVEL:
			return "Level";
		case WONGAMEHEARTS_SILVERMEDAL:
			return "SilverMedal";
		case WONGAMEHEARTS_GOLDMEDAL:
			return "GoldMedal";
		case WONGAMEHEARTS_GOLDOVERSILVERMEDAL:
			return "GoldOverSilverMedal";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum WonGameHearts", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const WonGameHearts StringToEnum_WonGameHearts( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (WonGameHearts)(NStr::ToInt( value ));
	if ( strcmp( value, "Level" ) == 0 || strcmp( value, "WONGAMEHEARTS_LEVEL" ) == 0 )
		return WONGAMEHEARTS_LEVEL;
	if ( strcmp( value, "SilverMedal" ) == 0 || strcmp( value, "WONGAMEHEARTS_SILVERMEDAL" ) == 0 )
		return WONGAMEHEARTS_SILVERMEDAL;
	if ( strcmp( value, "GoldMedal" ) == 0 || strcmp( value, "WONGAMEHEARTS_GOLDMEDAL" ) == 0 )
		return WONGAMEHEARTS_GOLDMEDAL;
	if ( strcmp( value, "GoldOverSilverMedal" ) == 0 || strcmp( value, "WONGAMEHEARTS_GOLDOVERSILVERMEDAL" ) == 0 )
		return WONGAMEHEARTS_GOLDOVERSILVERMEDAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum WonGameHearts", value ) );
	return WONGAMEHEARTS_LEVEL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const WonGameMedal value )
{
	switch( value )
	{
		case WONGAMEMEDAL_NONE:
			return "None";
		case WONGAMEMEDAL_SILVER:
			return "Silver";
		case WONGAMEMEDAL_GOLD:
			return "Gold";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum WonGameMedal", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const WonGameMedal StringToEnum_WonGameMedal( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (WonGameMedal)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "WONGAMEMEDAL_NONE" ) == 0 )
		return WONGAMEMEDAL_NONE;
	if ( strcmp( value, "Silver" ) == 0 || strcmp( value, "WONGAMEMEDAL_SILVER" ) == 0 )
		return WONGAMEMEDAL_SILVER;
	if ( strcmp( value, "Gold" ) == 0 || strcmp( value, "WONGAMEMEDAL_GOLD" ) == 0 )
		return WONGAMEMEDAL_GOLD;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum WonGameMedal", value ) );
	return WONGAMEMEDAL_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BallVelocities::BallVelocities() :
		bulletVelocity( 150000.0f )
	, bulletPointerVelocity( 1500000.0f )
	, ballInChainVelocity( 10000.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BallVelocities::operator&( IBinSaver &saver )
{
	saver.Add( 2, &bulletVelocity );
	saver.Add( 3, &bulletPointerVelocity );
	saver.Add( 4, &ballInChainVelocity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BallVelocities::operator&( IXmlSaver &saver )
{
	saver.Add( "bulletVelocity", &bulletVelocity );
	saver.Add( "bulletPointerVelocity", &bulletPointerVelocity );
	saver.Add( "ballInChainVelocity", &ballInChainVelocity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChainGate::ChainGate() :
		valid( false )
	, startChainId( 0 )
	, endChainId( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChainGate::operator&( IBinSaver &saver )
{
	saver.Add( 2, &valid );
	saver.Add( 3, &startChainId );
	saver.Add( 4, &endChainId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ChainGate::operator&( IXmlSaver &saver )
{
	saver.Add( "valid", &valid );
	saver.Add( "startChainId", &startChainId );
	saver.Add( "endChainId", &endChainId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BulletStatistics::BulletStatistics() :
		drillerGatePassed( false )
	, gatesPassed( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BulletStatistics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &drillerGatePassed );
	saver.Add( 3, &drillerGate );
	saver.Add( 4, &gatesPassed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BulletStatistics::operator&( IXmlSaver &saver )
{
	saver.Add( "drillerGatePassed", &drillerGatePassed );
	saver.Add( "drillerGate", &drillerGate );
	saver.Add( "gatesPassed", &gatesPassed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Coin::Coin() :
		fallingPercentage( 5 )
	, catchRadius( 1.0f )
	, gravity( 10.0f )
	, jumpSpeed( 10.0f )
	, zLift( 3.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Coin::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fallingPercentage );
	saver.Add( 3, &catchRadius );
	saver.Add( 4, &gravity );
	saver.Add( 5, &jumpSpeed );
	saver.Add( 6, &zLift );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Coin::operator&( IXmlSaver &saver )
{
	saver.Add( "fallingPercentage", &fallingPercentage );
	saver.Add( "catchRadius", &catchRadius );
	saver.Add( "gravity", &gravity );
	saver.Add( "jumpSpeed", &jumpSpeed );
	saver.Add( "zLift", &zLift );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBBoost::DBBoost() :
		name( "Unknown" )
	, accesslevel( 0 )
	, cooldown( 0 )
	, price( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &accesslevel );
	saver.Add( 4, &cooldown );
	saver.Add( 5, &price );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "accesslevel", &accesslevel );
	saver.Add( "cooldown", &cooldown );
	saver.Add( "price", &price );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBBoard::DBBoard() :
		width( 10000 )
	, height( 10000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoard::operator&( IBinSaver &saver )
{
	saver.Add( 2, &width );
	saver.Add( 3, &height );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoard::operator&( IXmlSaver &saver )
{
	saver.Add( "width", &width );
	saver.Add( "height", &height );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBAlchemistBoost::DBAlchemistBoost() :
		alchemistDuration( 0 )
	, additionalPaint( 0 )
	, paintMult( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAlchemistBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );
	saver.Add( 3, &alchemistDuration );
	saver.Add( 4, &additionalPaint );
	saver.Add( 5, &paintMult );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBAlchemistBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );
	saver.Add( "alchemistDuration", &alchemistDuration );
	saver.Add( "additionalPaint", &additionalPaint );
	saver.Add( "paintMult", &paintMult );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBBoostTemplate::DBBoostTemplate() :
		boostUsage( BOOSTUSAGE_UNKNOWN )
	, boostCategory( BOOSTSCATEGORY_EASY )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoostTemplate::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostUsage );
	saver.Add( 3, &boostCategory );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoostTemplate::operator&( IXmlSaver &saver )
{
	saver.Add( "boostUsage", &boostUsage );
	saver.Add( "boostCategory", &boostCategory );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBFreezeBoost::DBFreezeBoost() :
		seconds( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFreezeBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );
	saver.Add( 3, &seconds );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFreezeBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );
	saver.Add( "seconds", &seconds );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBBrighteningBoost::DBBrighteningBoost() :
		ballsnum( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBrighteningBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );
	saver.Add( 3, &ballsnum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBrighteningBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );
	saver.Add( "ballsnum", &ballsnum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselArtifacts::DBEaselArtifacts()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselArtifacts::operator&( IBinSaver &saver )
{
	saver.Add( 2, &artifact );
	saver.Add( 3, &scroll );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselArtifacts::operator&( IXmlSaver &saver )
{
	saver.Add( "artifact", &artifact );
	saver.Add( "scroll", &scroll );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselBallsView::DBEaselBallsView() :
		shadowRotation( 0.0f )
	, shadowOpacityChangeSpeed( 1.0f )
{
	colorBalls.resize( 9 );
	switchToAnimation.resize( 5 );
	animationsBaseSpeed.resize( 5, float() );
	animationsSpeedModifier.resize( 5, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBallsView::operator&( IBinSaver &saver )
{
	saver.Add( 2, &colorBalls );
	saver.Add( 3, &switchToAnimation );
	saver.Add( 4, &animationsBaseSpeed );
	saver.Add( 5, &animationsSpeedModifier );
	saver.Add( 6, &paintBlastBall );
	saver.Add( 7, &paintBlastBallFlying );
	saver.Add( 8, &jokerBall );
	saver.Add( 9, &shadowRotation );
	saver.Add( 10, &shadowOpacityChangeSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBallsView::operator&( IXmlSaver &saver )
{
	colorBalls.resize( 9 );
	saver.Add( "colorBalls", &colorBalls );
	switchToAnimation.resize( 5 );
	saver.Add( "switchToAnimation", &switchToAnimation );
	animationsBaseSpeed.resize( 5 );
	saver.Add( "animationsBaseSpeed", &animationsBaseSpeed );
	animationsSpeedModifier.resize( 5 );
	saver.Add( "animationsSpeedModifier", &animationsSpeedModifier );
	saver.Add( "paintBlastBall", &paintBlastBall );
	saver.Add( "paintBlastBallFlying", &paintBlastBallFlying );
	saver.Add( "jokerBall", &jokerBall );
	saver.Add( "shadowRotation", &shadowRotation );
	saver.Add( "shadowOpacityChangeSpeed", &shadowOpacityChangeSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselBidonEffectDesc::DBEaselBidonEffectDesc() :
		speedClockCooldownCoefficient( 1.0f )
	, speedClockPriceCoefficient( 1.0f )
	, glueSpeedReductionCoefficient( 0.7f )
	, glueAppearancePercentageDistance( 0.7f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBidonEffectDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &speedClockCooldownCoefficient );
	saver.Add( 3, &speedClockPriceCoefficient );
	saver.Add( 4, &glueSpeedReductionCoefficient );
	saver.Add( 5, &glueAppearancePercentageDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBidonEffectDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "speedClockCooldownCoefficient", &speedClockCooldownCoefficient );
	saver.Add( "speedClockPriceCoefficient", &speedClockPriceCoefficient );
	saver.Add( "glueSpeedReductionCoefficient", &glueSpeedReductionCoefficient );
	saver.Add( "glueAppearancePercentageDistance", &glueAppearancePercentageDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselBoostsTutorialDesc::DBEaselBoostsTutorialDesc() :
		changeBallsSecondsFromMovieEnd( 5 )
	, changeBallsCounts( 2 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBoostsTutorialDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &changeBallsSecondsFromMovieEnd );
	saver.Add( 3, &changeBallsCounts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselBoostsTutorialDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "changeBallsSecondsFromMovieEnd", &changeBallsSecondsFromMovieEnd );
	saver.Add( "changeBallsCounts", &changeBallsCounts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselCursorView::DBEaselCursorView()
{
	cursors.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselCursorView::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cursors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselCursorView::operator&( IXmlSaver &saver )
{
	cursors.resize( 2 );
	saver.Add( "cursors", &cursors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselFlowEffectGroup::DBEaselFlowEffectGroup() :
		intervalEndDistance( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselFlowEffectGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &intervalEndDistance );
	saver.Add( 3, &flowEffect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselFlowEffectGroup::operator&( IXmlSaver &saver )
{
	saver.Add( "intervalEndDistance", &intervalEndDistance );
	saver.Add( "flowEffect", &flowEffect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ExplosionParams::ExplosionParams() :
		minRotationAngle( 90.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExplosionParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minRotationAngle );
	saver.Add( 3, &maxScale );
	saver.Add( 4, &minScale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ExplosionParams::operator&( IXmlSaver &saver )
{
	saver.Add( "minRotationAngle", &minRotationAngle );
	saver.Add( "maxScale", &maxScale );
	saver.Add( "minScale", &minScale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselLevel::DBEaselLevel() :
		difficulty( DIFFICULTYLEVEL_UNKNOWN )
	, additionalDifficulty( DIFFICULTYLEVEL_UNKNOWN )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselLevel::operator&( IBinSaver &saver )
{
	saver.Add( 2, &difficulty );
	saver.Add( 3, &additionalDifficulty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselLevel::operator&( IXmlSaver &saver )
{
	saver.Add( "difficulty", &difficulty );
	saver.Add( "additionalDifficulty", &additionalDifficulty );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselPlatfrom::DBEaselPlatfrom()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselPlatfrom::operator&( IBinSaver &saver )
{
	saver.Add( 2, &platformObject );
	saver.Add( 3, &triplePlatformObject );
	saver.Add( 4, &laser );
	saver.Add( 5, &laser2 );
	saver.Add( 6, &laserPointer );
	saver.Add( 7, &laserSource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselPlatfrom::operator&( IXmlSaver &saver )
{
	saver.Add( "platformObject", &platformObject );
	saver.Add( "triplePlatformObject", &triplePlatformObject );
	saver.Add( "laser", &laser );
	saver.Add( "laser2", &laser2 );
	saver.Add( "laserPointer", &laserPointer );
	saver.Add( "laserSource", &laserSource );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselSound::DBEaselSound()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSound::operator&( IBinSaver &saver )
{
	saver.Add( 2, &eventName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSound::operator&( IXmlSaver &saver )
{
	saver.Add( "eventName", &eventName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBFragment::DBFragment() :
		fragmentColor( COLOR_BLACK )
	, paintFragmentId( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFragment::operator&( IBinSaver &saver )
{
	saver.Add( 2, &fragmentColor );
	saver.Add( 3, &fragmentPoints );
	saver.Add( 4, &paintFragmentId );
	saver.Add( 5, &completeEffectMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBFragment::operator&( IXmlSaver &saver )
{
	saver.Add( "fragmentColor", &fragmentColor );
	saver.Add( "fragmentPoints", &fragmentPoints );
	saver.Add( "paintFragmentId", &paintFragmentId );
	saver.Add( "completeEffectMaterial", &completeEffectMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBJokerBoost::DBJokerBoost()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBJokerBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBJokerBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBMagnetBoost::DBMagnetBoost() :
		searchSeconds( 0 )
	, radiusR1( 0 )
	, radiusR2( 0 )
	, numBallToEat( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMagnetBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );
	saver.Add( 3, &searchSeconds );
	saver.Add( 4, &radiusR1 );
	saver.Add( 5, &radiusR2 );
	saver.Add( 6, &numBallToEat );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMagnetBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );
	saver.Add( "searchSeconds", &searchSeconds );
	saver.Add( "radiusR1", &radiusR1 );
	saver.Add( "radiusR2", &radiusR2 );
	saver.Add( "numBallToEat", &numBallToEat );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBListFragments::DBListFragments()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBListFragments::operator&( IBinSaver &saver )
{
	saver.Add( 2, &listFragments );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBListFragments::operator&( IXmlSaver &saver )
{
	saver.Add( "listFragments", &listFragments );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLogicPoint::DBLogicPoint() :
		x( 0 )
	, y( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLogicPoint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &x );
	saver.Add( 3, &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLogicPoint::operator&( IXmlSaver &saver )
{
	saver.Add( "x", &x );
	saver.Add( "y", &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLuxorPlatformGeneratorParams::DBLuxorPlatformGeneratorParams() :
		firstChainInfluenceStart( 0 )
	, firstChainInfluenceEnd( 100 )
	, colorWeightsPower( 4.0f )
	, colorWeightsMultiplier( 0.95f )
	, lowActChance( 0.95f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLuxorPlatformGeneratorParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &firstChainInfluenceStart );
	saver.Add( 3, &firstChainInfluenceEnd );
	saver.Add( 4, &colorWeightsPower );
	saver.Add( 5, &colorWeightsMultiplier );
	saver.Add( 6, &lowActChance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLuxorPlatformGeneratorParams::operator&( IXmlSaver &saver )
{
	saver.Add( "firstChainInfluenceStart", &firstChainInfluenceStart );
	saver.Add( "firstChainInfluenceEnd", &firstChainInfluenceEnd );
	saver.Add( "colorWeightsPower", &colorWeightsPower );
	saver.Add( "colorWeightsMultiplier", &colorWeightsMultiplier );
	saver.Add( "lowActChance", &lowActChance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPaintBlastBoost::DBPaintBlastBoost() :
		radius( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPaintBlastBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );
	saver.Add( 3, &radius );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPaintBlastBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );
	saver.Add( "radius", &radius );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPicture::DBPicture()
{
	pictureparams.resize( 16 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPicture::operator&( IBinSaver &saver )
{
	saver.Add( 2, &picturefile );
	saver.Add( 3, &picturename );
	saver.Add( 4, &pictureparams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPicture::operator&( IXmlSaver &saver )
{
	saver.Add( "picturefile", &picturefile );
	saver.Add( "picturename", &picturename );
	pictureparams.resize( 16 );
	saver.Add( "pictureparams", &pictureparams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSorterBoost::DBSorterBoost()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSorterBoost::operator&( IBinSaver &saver )
{
	saver.Add( 2, &boostBase );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSorterBoost::operator&( IXmlSaver &saver )
{
	saver.Add( "boostBase", &boostBase );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPaint::DBPaint()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPaint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &picture );
	saver.Add( 3, &paintQuad );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPaint::operator&( IXmlSaver &saver )
{
	saver.Add( "picture", &picture );
	saver.Add( "paintQuad", &paintQuad );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPoint::DBPoint() :
		xCoord( 0 )
	, yCoord( 0 )
	, zCoord( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPoint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &xCoord );
	saver.Add( 3, &yCoord );
	saver.Add( 4, &zCoord );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPoint::operator&( IXmlSaver &saver )
{
	saver.Add( "xCoord", &xCoord );
	saver.Add( "yCoord", &yCoord );
	saver.Add( "zCoord", &zCoord );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBBoostList::DBBoostList() :
		rerollOnWinStreak( 1 )
	, rerollOnFailStreak( 3 )
{
	slots.resize( 16 );
	canReroll.resize( 16, bool() );
	boostsTemplate.resize( 9 );
	boostsTooltips.resize( 9 );
	slotsPrices.resize( 3, int() );
	regenPrices.resize( 3, int() );
	images.resize( 9 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoostList::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rerollOnWinStreak );
	saver.Add( 3, &rerollOnFailStreak );
	saver.Add( 4, &slots );
	saver.Add( 5, &canReroll );
	saver.Add( 6, &boostsTemplate );
	saver.Add( 7, &boostsTooltips );
	saver.Add( 8, &slotsPrices );
	saver.Add( 9, &regenPrices );
	saver.Add( 10, &images );
	saver.Add( 11, &paintblast );
	saver.Add( 12, &freeze );
	saver.Add( 13, &joker );
	saver.Add( 14, &sorter );
	saver.Add( 15, &magnet );
	saver.Add( 16, &alchemist );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBBoostList::operator&( IXmlSaver &saver )
{
	saver.Add( "rerollOnWinStreak", &rerollOnWinStreak );
	saver.Add( "rerollOnFailStreak", &rerollOnFailStreak );
	slots.resize( 16 );
	saver.Add( "slots", &slots );
	canReroll.resize( 16 );
	saver.Add( "canReroll", &canReroll );
	boostsTemplate.resize( 9 );
	saver.Add( "boostsTemplate", &boostsTemplate );
	boostsTooltips.resize( 9 );
	saver.Add( "boostsTooltips", &boostsTooltips );
	slotsPrices.resize( 3 );
	saver.Add( "slotsPrices", &slotsPrices );
	regenPrices.resize( 3 );
	saver.Add( "regenPrices", &regenPrices );
	images.resize( 9 );
	saver.Add( "images", &images );
	saver.Add( "paintblast", &paintblast );
	saver.Add( "freeze", &freeze );
	saver.Add( "joker", &joker );
	saver.Add( "sorter", &sorter );
	saver.Add( "magnet", &magnet );
	saver.Add( "alchemist", &alchemist );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSpeedMarker::DBSpeedMarker() :
		position( 0 )
	, speedmultiplier( 0 )
	, speedconstant( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSpeedMarker::operator&( IBinSaver &saver )
{
	saver.Add( 2, &position );
	saver.Add( 3, &speedmultiplier );
	saver.Add( 4, &speedconstant );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSpeedMarker::operator&( IXmlSaver &saver )
{
	saver.Add( "position", &position );
	saver.Add( "speedmultiplier", &speedmultiplier );
	saver.Add( "speedconstant", &speedconstant );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSplinePoints::DBSplinePoints()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplinePoints::operator&( IBinSaver &saver )
{
	saver.Add( 2, &point );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplinePoints::operator&( IXmlSaver &saver )
{
	saver.Add( "point", &point );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSplineSpeedMarkers::DBSplineSpeedMarkers()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineSpeedMarkers::operator&( IBinSaver &saver )
{
	saver.Add( 2, &speedmarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineSpeedMarkers::operator&( IXmlSaver &saver )
{
	saver.Add( "speedmarker", &speedmarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSpline::DBSpline() :
		degree( 3 )
	, cpnum( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSpline::operator&( IBinSaver &saver )
{
	saver.Add( 2, &degree );
	saver.Add( 3, &cpnum );
	saver.Add( 4, &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSpline::operator&( IXmlSaver &saver )
{
	saver.Add( "degree", &degree );
	saver.Add( "cpnum", &cpnum );
	saver.Add( "points", &points );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSplineStartEndPoint::DBSplineStartEndPoint()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineStartEndPoint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &placement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineStartEndPoint::operator&( IXmlSaver &saver )
{
	saver.Add( "placement", &placement );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBTunnel::DBTunnel() :
		begin( 0 )
	, end( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTunnel::operator&( IBinSaver &saver )
{
	saver.Add( 2, &begin );
	saver.Add( 3, &end );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBTunnel::operator&( IXmlSaver &saver )
{
	saver.Add( "begin", &begin );
	saver.Add( "end", &end );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSplineTunnels::DBSplineTunnels()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineTunnels::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tunnel );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineTunnels::operator&( IXmlSaver &saver )
{
	saver.Add( "tunnel", &tunnel );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBSplineData::DBSplineData() :
		splinelenght( 0 )
{
	chainparams.resize( 16 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &splinelenght );
	saver.Add( 3, &tunnels );
	saver.Add( 4, &speedmarkers );
	saver.Add( 5, &startPoint );
	saver.Add( 6, &endPoint );
	saver.Add( 7, &atExitPoint );
	saver.Add( 8, &chainparams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBSplineData::operator&( IXmlSaver &saver )
{
	saver.Add( "splinelenght", &splinelenght );
	saver.Add( "tunnels", &tunnels );
	saver.Add( "speedmarkers", &speedmarkers );
	saver.Add( "startPoint", &startPoint );
	saver.Add( "endPoint", &endPoint );
	saver.Add( "atExitPoint", &atExitPoint );
	chainparams.resize( 16 );
	saver.Add( "chainparams", &chainparams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EChainStatistics::EChainStatistics() :
		allBallsNum( 0 )
{
	colorBallsNum.resize( 9, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EChainStatistics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &colorBallsNum );
	saver.Add( 3, &allBallsNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EChainStatistics::operator&( IXmlSaver &saver )
{
	colorBallsNum.resize( 9 );
	saver.Add( "colorBallsNum", &colorBallsNum );
	saver.Add( "allBallsNum", &allBallsNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EPlatformGeneratorStatistics::EPlatformGeneratorStatistics() :
		lastColor( COLOR_BLACK )
	, lastColorRepeatNum( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPlatformGeneratorStatistics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lastColor );
	saver.Add( 3, &lastColorRepeatNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPlatformGeneratorStatistics::operator&( IXmlSaver &saver )
{
	saver.Add( "lastColor", &lastColor );
	saver.Add( "lastColorRepeatNum", &lastColorRepeatNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EPaintStatistics::EPaintStatistics() :
		remainColorsToPaint( 0 )
	, remainPaintCapacity( 0 )
{
	remainColorCapacity.resize( 9, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPaintStatistics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &remainColorCapacity );
	saver.Add( 3, &allPaintColors );
	saver.Add( 4, &remainColorsToPaint );
	saver.Add( 5, &remainPaintCapacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPaintStatistics::operator&( IXmlSaver &saver )
{
	remainColorCapacity.resize( 9 );
	saver.Add( "remainColorCapacity", &remainColorCapacity );
	saver.Add( "allPaintColors", &allPaintColors );
	saver.Add( "remainColorsToPaint", &remainColorsToPaint );
	saver.Add( "remainPaintCapacity", &remainPaintCapacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EPlatformGeneratorParams::EPlatformGeneratorParams() :
		maxRepeatColorNum( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPlatformGeneratorParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &maxRepeatColorNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EPlatformGeneratorParams::operator&( IXmlSaver &saver )
{
	saver.Add( "maxRepeatColorNum", &maxRepeatColorNum );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ELuxorStatistics::ELuxorStatistics() :
		remainDistanceForFirstChain( 0 )
	, remainDistanceForFirstChainPercent( 0 )
{
	chainStatistics.resize( 3 );
	colorWeights.resize( 9, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ELuxorStatistics::operator&( IBinSaver &saver )
{
	saver.Add( 2, &remainDistanceForFirstChain );
	saver.Add( 3, &remainDistanceForFirstChainPercent );
	saver.Add( 4, &chainStatistics );
	saver.Add( 5, &generatorStatistics );
	saver.Add( 6, &bulletStats );
	saver.Add( 7, &colorWeights );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ELuxorStatistics::operator&( IXmlSaver &saver )
{
	saver.Add( "remainDistanceForFirstChain", &remainDistanceForFirstChain );
	saver.Add( "remainDistanceForFirstChainPercent", &remainDistanceForFirstChainPercent );
	chainStatistics.resize( 3 );
	saver.Add( "chainStatistics", &chainStatistics );
	saver.Add( "generatorStatistics", &generatorStatistics );
	saver.Add( "bulletStats", &bulletStats );
	colorWeights.resize( 9 );
	saver.Add( "colorWeights", &colorWeights );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PaintFragmentFillParams::PaintFragmentFillParams() :
		paintFillStartTime( 1.1f )
	, fillInterval( 1.0f )
	, completeFadeIn( 1.0f )
	, completeEffectFadeIn( 1.0f )
	, completeEffectFadeOut( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintFragmentFillParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &paintFillStartTime );
	saver.Add( 3, &fillInterval );
	saver.Add( 4, &completeFadeIn );
	saver.Add( 5, &completeEffectFadeIn );
	saver.Add( 6, &completeEffectFadeOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintFragmentFillParams::operator&( IXmlSaver &saver )
{
	saver.Add( "paintFillStartTime", &paintFillStartTime );
	saver.Add( "fillInterval", &fillInterval );
	saver.Add( "completeFadeIn", &completeFadeIn );
	saver.Add( "completeEffectFadeIn", &completeEffectFadeIn );
	saver.Add( "completeEffectFadeOut", &completeEffectFadeOut );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Magnet::Magnet()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Magnet::operator&( IBinSaver &saver )
{
	saver.Add( 2, &magnetHighlight );
	saver.Add( 3, &magnetPreselect );
	saver.Add( 4, &magnet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Magnet::operator&( IXmlSaver &saver )
{
	saver.Add( "magnetHighlight", &magnetHighlight );
	saver.Add( "magnetPreselect", &magnetPreselect );
	saver.Add( "magnet", &magnet );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselEffectView::DBEaselEffectView() :
		flowIntervalsStartDistance( 0.0f )
	, flowScale( 10.0f )
	, pathfinderVelocity( 1000000.0f )
	, pathfinderInterval( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselEffectView::operator&( IBinSaver &saver )
{
	saver.Add( 2, &paintblastExplosion );
	saver.Add( 3, &freezeEffect );
	saver.Add( 4, &coinPickUp );
	saver.Add( 5, &gameStartEffect );
	saver.Add( 6, &gameWonEffect );
	saver.Add( 7, &sortEffect );
	saver.Add( 8, &ballExplosion );
	saver.Add( 9, &explosionParams );
	saver.Add( 10, &flowIntervalsStartDistance );
	saver.Add( 11, &flowScale );
	saver.Add( 12, &fillParams );
	saver.Add( 13, &flowGroups );
	saver.Add( 14, &flowTouchEffect );
	saver.Add( 15, &pathfinderHead );
	saver.Add( 16, &pathfinderTail );
	saver.Add( 17, &pathfinderVelocity );
	saver.Add( 18, &pathfinderInterval );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselEffectView::operator&( IXmlSaver &saver )
{
	saver.Add( "paintblastExplosion", &paintblastExplosion );
	saver.Add( "freezeEffect", &freezeEffect );
	saver.Add( "coinPickUp", &coinPickUp );
	saver.Add( "gameStartEffect", &gameStartEffect );
	saver.Add( "gameWonEffect", &gameWonEffect );
	saver.Add( "sortEffect", &sortEffect );
	saver.Add( "ballExplosion", &ballExplosion );
	saver.Add( "explosionParams", &explosionParams );
	saver.Add( "flowIntervalsStartDistance", &flowIntervalsStartDistance );
	saver.Add( "flowScale", &flowScale );
	saver.Add( "fillParams", &fillParams );
	saver.Add( "flowGroups", &flowGroups );
	saver.Add( "flowTouchEffect", &flowTouchEffect );
	saver.Add( "pathfinderHead", &pathfinderHead );
	saver.Add( "pathfinderTail", &pathfinderTail );
	saver.Add( "pathfinderVelocity", &pathfinderVelocity );
	saver.Add( "pathfinderInterval", &pathfinderInterval );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TunnelParams::TunnelParams() :
		startPointOffset( 250 )
	, endPointOffset( 100 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TunnelParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tunnel );
	saver.Add( 3, &startPointOffset );
	saver.Add( 4, &endPointOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TunnelParams::operator&( IXmlSaver &saver )
{
	saver.Add( "tunnel", &tunnel );
	saver.Add( "startPointOffset", &startPointOffset );
	saver.Add( "endPointOffset", &endPointOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselChains::DBEaselChains() :
		numBallsInChain( 20 )
	, minSameColorChain( 3 )
	, maxSameColorChain( 8 )
	, speedMultiplier( 100 )
	, firstChainDelay( 0 )
	, nextChainDelay( 10000 )
	, colorsDistortionPercentage( 100 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselChains::operator&( IBinSaver &saver )
{
	saver.Add( 2, &numBallsInChain );
	saver.Add( 3, &minSameColorChain );
	saver.Add( 4, &maxSameColorChain );
	saver.Add( 5, &speedMultiplier );
	saver.Add( 6, &firstChainDelay );
	saver.Add( 7, &nextChainDelay );
	saver.Add( 8, &colorsDistortionPercentage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselChains::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselChains* parentPtr = (DBEaselChains*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselChains::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "numBallsInChain", &numBallsInChain );
	saver.Add( "minSameColorChain", &minSameColorChain );
	saver.Add( "maxSameColorChain", &maxSameColorChain );
	saver.Add( "speedMultiplier", &speedMultiplier );
	saver.Add( "firstChainDelay", &firstChainDelay );
	saver.Add( "nextChainDelay", &nextChainDelay );
	saver.Add( "colorsDistortionPercentage", &colorsDistortionPercentage );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselChains::Assign( const DBEaselChains& _dBEaselChains )
{
	numBallsInChain = _dBEaselChains.numBallsInChain;
	minSameColorChain = _dBEaselChains.minSameColorChain;
	maxSameColorChain = _dBEaselChains.maxSameColorChain;
	speedMultiplier = _dBEaselChains.speedMultiplier;
	firstChainDelay = _dBEaselChains.firstChainDelay;
	nextChainDelay = _dBEaselChains.nextChainDelay;
	colorsDistortionPercentage = _dBEaselChains.colorsDistortionPercentage;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselCommon::DBEaselCommon() :
		chainTravelTime( 60000 )
	, waitForResultScreen( 4.0f )
	, ballFireInterval( 0.2f )
	, explosionCountdown( 3 )
{
	colors.resize( 9 );
	fallingObjects.resize( 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselCommon::operator&( IBinSaver &saver )
{
	saver.Add( 2, &colors );
	saver.Add( 3, &priestessAnimGraph );
	saver.Add( 4, &camera );
	saver.Add( 5, &aimCursors );
	saver.Add( 6, &platform );
	saver.Add( 7, &luxorPlacement );
	saver.Add( 8, &balls );
	saver.Add( 9, &effects );
	saver.Add( 10, &tunnels );
	saver.Add( 11, &fallingObjects );
	saver.Add( 12, &platformGeneratorParams );
	saver.Add( 13, &startPipe );
	saver.Add( 14, &endWell );
	saver.Add( 15, &magnetEffects );
	saver.Add( 16, &alchemistPot );
	saver.Add( 17, &glueEffect );
	saver.Add( 18, &chainTravelTime );
	saver.Add( 19, &coin );
	saver.Add( 20, &ballVelocities );
	saver.Add( 21, &waitForResultScreen );
	saver.Add( 22, &priestessDefaultPlacement );
	saver.Add( 23, &ballFireInterval );
	saver.Add( 24, &explosionCountdown );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselCommon::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselCommon* parentPtr = (DBEaselCommon*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselCommon::SerializeSelf( IXmlSaver &saver )
{
	colors.resize( 9 );
	saver.Add( "colors", &colors );
	saver.Add( "priestessAnimGraph", &priestessAnimGraph );
	saver.Add( "camera", &camera );
	saver.Add( "aimCursors", &aimCursors );
	saver.Add( "platform", &platform );
	saver.Add( "luxorPlacement", &luxorPlacement );
	saver.Add( "balls", &balls );
	saver.Add( "effects", &effects );
	saver.Add( "tunnels", &tunnels );
	fallingObjects.resize( 1 );
	saver.Add( "fallingObjects", &fallingObjects );
	saver.Add( "platformGeneratorParams", &platformGeneratorParams );
	saver.Add( "startPipe", &startPipe );
	saver.Add( "endWell", &endWell );
	saver.Add( "magnetEffects", &magnetEffects );
	saver.Add( "alchemistPot", &alchemistPot );
	saver.Add( "glueEffect", &glueEffect );
	saver.Add( "chainTravelTime", &chainTravelTime );
	saver.Add( "coin", &coin );
	saver.Add( "ballVelocities", &ballVelocities );
	saver.Add( "waitForResultScreen", &waitForResultScreen );
	saver.Add( "priestessDefaultPlacement", &priestessDefaultPlacement );
	saver.Add( "ballFireInterval", &ballFireInterval );
	saver.Add( "explosionCountdown", &explosionCountdown );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselCommon::Assign( const DBEaselCommon& _dBEaselCommon )
{
	colors = _dBEaselCommon.colors;
	priestessAnimGraph = _dBEaselCommon.priestessAnimGraph;
	camera.name = _dBEaselCommon.camera.name;
	camera.anchor = _dBEaselCommon.camera.anchor;
	camera.yaw = _dBEaselCommon.camera.yaw;
	camera.pitch = _dBEaselCommon.camera.pitch;
	camera.roll = _dBEaselCommon.camera.roll;
	camera.rod = _dBEaselCommon.camera.rod;
	camera.fov = _dBEaselCommon.camera.fov;
	camera.environment = _dBEaselCommon.camera.environment;
	aimCursors.cursors = _dBEaselCommon.aimCursors.cursors;
	platform.platformObject = _dBEaselCommon.platform.platformObject;
	platform.triplePlatformObject = _dBEaselCommon.platform.triplePlatformObject;
	platform.laser = _dBEaselCommon.platform.laser;
	platform.laser2 = _dBEaselCommon.platform.laser2;
	platform.laserPointer = _dBEaselCommon.platform.laserPointer;
	platform.laserSource = _dBEaselCommon.platform.laserSource;
	luxorPlacement = _dBEaselCommon.luxorPlacement;
	balls.colorBalls = _dBEaselCommon.balls.colorBalls;
	balls.switchToAnimation = _dBEaselCommon.balls.switchToAnimation;
	balls.animationsBaseSpeed = _dBEaselCommon.balls.animationsBaseSpeed;
	balls.animationsSpeedModifier = _dBEaselCommon.balls.animationsSpeedModifier;
	balls.paintBlastBall = _dBEaselCommon.balls.paintBlastBall;
	balls.paintBlastBallFlying = _dBEaselCommon.balls.paintBlastBallFlying;
	balls.jokerBall = _dBEaselCommon.balls.jokerBall;
	balls.shadowRotation = _dBEaselCommon.balls.shadowRotation;
	balls.shadowOpacityChangeSpeed = _dBEaselCommon.balls.shadowOpacityChangeSpeed;
	effects.paintblastExplosion = _dBEaselCommon.effects.paintblastExplosion;
	effects.freezeEffect = _dBEaselCommon.effects.freezeEffect;
	effects.coinPickUp = _dBEaselCommon.effects.coinPickUp;
	effects.gameStartEffect = _dBEaselCommon.effects.gameStartEffect;
	effects.gameWonEffect = _dBEaselCommon.effects.gameWonEffect;
	effects.sortEffect = _dBEaselCommon.effects.sortEffect;
	effects.ballExplosion = _dBEaselCommon.effects.ballExplosion;
	effects.explosionParams.minRotationAngle = _dBEaselCommon.effects.explosionParams.minRotationAngle;
	effects.explosionParams.maxScale = _dBEaselCommon.effects.explosionParams.maxScale;
	effects.explosionParams.minScale = _dBEaselCommon.effects.explosionParams.minScale;
	effects.flowIntervalsStartDistance = _dBEaselCommon.effects.flowIntervalsStartDistance;
	effects.flowScale = _dBEaselCommon.effects.flowScale;
	effects.fillParams.paintFillStartTime = _dBEaselCommon.effects.fillParams.paintFillStartTime;
	effects.fillParams.fillInterval = _dBEaselCommon.effects.fillParams.fillInterval;
	effects.fillParams.completeFadeIn = _dBEaselCommon.effects.fillParams.completeFadeIn;
	effects.fillParams.completeEffectFadeIn = _dBEaselCommon.effects.fillParams.completeEffectFadeIn;
	effects.fillParams.completeEffectFadeOut = _dBEaselCommon.effects.fillParams.completeEffectFadeOut;
	effects.flowGroups = _dBEaselCommon.effects.flowGroups;
	effects.flowTouchEffect = _dBEaselCommon.effects.flowTouchEffect;
	effects.pathfinderHead = _dBEaselCommon.effects.pathfinderHead;
	effects.pathfinderTail = _dBEaselCommon.effects.pathfinderTail;
	effects.pathfinderVelocity = _dBEaselCommon.effects.pathfinderVelocity;
	effects.pathfinderInterval = _dBEaselCommon.effects.pathfinderInterval;
	tunnels.tunnel = _dBEaselCommon.tunnels.tunnel;
	tunnels.startPointOffset = _dBEaselCommon.tunnels.startPointOffset;
	tunnels.endPointOffset = _dBEaselCommon.tunnels.endPointOffset;
	fallingObjects = _dBEaselCommon.fallingObjects;
	platformGeneratorParams.firstChainInfluenceStart = _dBEaselCommon.platformGeneratorParams.firstChainInfluenceStart;
	platformGeneratorParams.firstChainInfluenceEnd = _dBEaselCommon.platformGeneratorParams.firstChainInfluenceEnd;
	platformGeneratorParams.colorWeightsPower = _dBEaselCommon.platformGeneratorParams.colorWeightsPower;
	platformGeneratorParams.colorWeightsMultiplier = _dBEaselCommon.platformGeneratorParams.colorWeightsMultiplier;
	platformGeneratorParams.lowActChance = _dBEaselCommon.platformGeneratorParams.lowActChance;
	startPipe = _dBEaselCommon.startPipe;
	endWell = _dBEaselCommon.endWell;
	magnetEffects.magnetHighlight = _dBEaselCommon.magnetEffects.magnetHighlight;
	magnetEffects.magnetPreselect = _dBEaselCommon.magnetEffects.magnetPreselect;
	magnetEffects.magnet = _dBEaselCommon.magnetEffects.magnet;
	alchemistPot = _dBEaselCommon.alchemistPot;
	glueEffect = _dBEaselCommon.glueEffect;
	chainTravelTime = _dBEaselCommon.chainTravelTime;
	coin.fallingPercentage = _dBEaselCommon.coin.fallingPercentage;
	coin.catchRadius = _dBEaselCommon.coin.catchRadius;
	coin.gravity = _dBEaselCommon.coin.gravity;
	coin.jumpSpeed = _dBEaselCommon.coin.jumpSpeed;
	coin.zLift = _dBEaselCommon.coin.zLift;
	ballVelocities.bulletVelocity = _dBEaselCommon.ballVelocities.bulletVelocity;
	ballVelocities.bulletPointerVelocity = _dBEaselCommon.ballVelocities.bulletPointerVelocity;
	ballVelocities.ballInChainVelocity = _dBEaselCommon.ballVelocities.ballInChainVelocity;
	waitForResultScreen = _dBEaselCommon.waitForResultScreen;
	priestessDefaultPlacement.pos = _dBEaselCommon.priestessDefaultPlacement.pos;
	priestessDefaultPlacement.rot = _dBEaselCommon.priestessDefaultPlacement.rot;
	priestessDefaultPlacement.scale = _dBEaselCommon.priestessDefaultPlacement.scale;
	ballFireInterval = _dBEaselCommon.ballFireInterval;
	explosionCountdown = _dBEaselCommon.explosionCountdown;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselData::DBEaselData() :
		startPointOffset( -400 )
	, killChainAfterOffset( 400 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &title );
	saver.Add( 3, &startPointOffset );
	saver.Add( 4, &killChainAfterOffset );
	saver.Add( 5, &game );
	saver.Add( 6, &commonParams );
	saver.Add( 7, &soundData );
	saver.Add( 8, &priestessStats );
	saver.Add( 9, &gameboosts );
	saver.Add( 10, &bidonEffectDesc );
	saver.Add( 11, &boostsTutorialDesc );
	saver.Add( 12, &artifacts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselData::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselData* parentPtr = (DBEaselData*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselData::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "title", &title );
	saver.Add( "startPointOffset", &startPointOffset );
	saver.Add( "killChainAfterOffset", &killChainAfterOffset );
	saver.Add( "game", &game );
	saver.Add( "commonParams", &commonParams );
	saver.Add( "soundData", &soundData );
	saver.Add( "priestessStats", &priestessStats );
	saver.Add( "gameboosts", &gameboosts );
	saver.Add( "bidonEffectDesc", &bidonEffectDesc );
	saver.Add( "boostsTutorialDesc", &boostsTutorialDesc );
	saver.Add( "artifacts", &artifacts );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselData::Assign( const DBEaselData& _dBEaselData )
{
	title = _dBEaselData.title;
	startPointOffset = _dBEaselData.startPointOffset;
	killChainAfterOffset = _dBEaselData.killChainAfterOffset;
	game = _dBEaselData.game;
	commonParams = _dBEaselData.commonParams;
	soundData = _dBEaselData.soundData;
	priestessStats = _dBEaselData.priestessStats;
	gameboosts.rerollOnWinStreak = _dBEaselData.gameboosts.rerollOnWinStreak;
	gameboosts.rerollOnFailStreak = _dBEaselData.gameboosts.rerollOnFailStreak;
	gameboosts.slots = _dBEaselData.gameboosts.slots;
	gameboosts.canReroll = _dBEaselData.gameboosts.canReroll;
	gameboosts.boostsTemplate = _dBEaselData.gameboosts.boostsTemplate;
	gameboosts.boostsTooltips = _dBEaselData.gameboosts.boostsTooltips;
	gameboosts.slotsPrices = _dBEaselData.gameboosts.slotsPrices;
	gameboosts.regenPrices = _dBEaselData.gameboosts.regenPrices;
	gameboosts.images = _dBEaselData.gameboosts.images;
	gameboosts.paintblast.boostBase.name = _dBEaselData.gameboosts.paintblast.boostBase.name;
	gameboosts.paintblast.boostBase.accesslevel = _dBEaselData.gameboosts.paintblast.boostBase.accesslevel;
	gameboosts.paintblast.boostBase.cooldown = _dBEaselData.gameboosts.paintblast.boostBase.cooldown;
	gameboosts.paintblast.boostBase.price = _dBEaselData.gameboosts.paintblast.boostBase.price;
	gameboosts.paintblast.radius = _dBEaselData.gameboosts.paintblast.radius;
	gameboosts.freeze.boostBase.name = _dBEaselData.gameboosts.freeze.boostBase.name;
	gameboosts.freeze.boostBase.accesslevel = _dBEaselData.gameboosts.freeze.boostBase.accesslevel;
	gameboosts.freeze.boostBase.cooldown = _dBEaselData.gameboosts.freeze.boostBase.cooldown;
	gameboosts.freeze.boostBase.price = _dBEaselData.gameboosts.freeze.boostBase.price;
	gameboosts.freeze.seconds = _dBEaselData.gameboosts.freeze.seconds;
	gameboosts.joker.boostBase.name = _dBEaselData.gameboosts.joker.boostBase.name;
	gameboosts.joker.boostBase.accesslevel = _dBEaselData.gameboosts.joker.boostBase.accesslevel;
	gameboosts.joker.boostBase.cooldown = _dBEaselData.gameboosts.joker.boostBase.cooldown;
	gameboosts.joker.boostBase.price = _dBEaselData.gameboosts.joker.boostBase.price;
	gameboosts.sorter.boostBase.name = _dBEaselData.gameboosts.sorter.boostBase.name;
	gameboosts.sorter.boostBase.accesslevel = _dBEaselData.gameboosts.sorter.boostBase.accesslevel;
	gameboosts.sorter.boostBase.cooldown = _dBEaselData.gameboosts.sorter.boostBase.cooldown;
	gameboosts.sorter.boostBase.price = _dBEaselData.gameboosts.sorter.boostBase.price;
	gameboosts.magnet.boostBase.name = _dBEaselData.gameboosts.magnet.boostBase.name;
	gameboosts.magnet.boostBase.accesslevel = _dBEaselData.gameboosts.magnet.boostBase.accesslevel;
	gameboosts.magnet.boostBase.cooldown = _dBEaselData.gameboosts.magnet.boostBase.cooldown;
	gameboosts.magnet.boostBase.price = _dBEaselData.gameboosts.magnet.boostBase.price;
	gameboosts.magnet.searchSeconds = _dBEaselData.gameboosts.magnet.searchSeconds;
	gameboosts.magnet.radiusR1 = _dBEaselData.gameboosts.magnet.radiusR1;
	gameboosts.magnet.radiusR2 = _dBEaselData.gameboosts.magnet.radiusR2;
	gameboosts.magnet.numBallToEat = _dBEaselData.gameboosts.magnet.numBallToEat;
	gameboosts.alchemist.boostBase.name = _dBEaselData.gameboosts.alchemist.boostBase.name;
	gameboosts.alchemist.boostBase.accesslevel = _dBEaselData.gameboosts.alchemist.boostBase.accesslevel;
	gameboosts.alchemist.boostBase.cooldown = _dBEaselData.gameboosts.alchemist.boostBase.cooldown;
	gameboosts.alchemist.boostBase.price = _dBEaselData.gameboosts.alchemist.boostBase.price;
	gameboosts.alchemist.alchemistDuration = _dBEaselData.gameboosts.alchemist.alchemistDuration;
	gameboosts.alchemist.additionalPaint = _dBEaselData.gameboosts.alchemist.additionalPaint;
	gameboosts.alchemist.paintMult = _dBEaselData.gameboosts.alchemist.paintMult;
	bidonEffectDesc.speedClockCooldownCoefficient = _dBEaselData.bidonEffectDesc.speedClockCooldownCoefficient;
	bidonEffectDesc.speedClockPriceCoefficient = _dBEaselData.bidonEffectDesc.speedClockPriceCoefficient;
	bidonEffectDesc.glueSpeedReductionCoefficient = _dBEaselData.bidonEffectDesc.glueSpeedReductionCoefficient;
	bidonEffectDesc.glueAppearancePercentageDistance = _dBEaselData.bidonEffectDesc.glueAppearancePercentageDistance;
	boostsTutorialDesc.changeBallsSecondsFromMovieEnd = _dBEaselData.boostsTutorialDesc.changeBallsSecondsFromMovieEnd;
	boostsTutorialDesc.changeBallsCounts = _dBEaselData.boostsTutorialDesc.changeBallsCounts;
	artifacts.artifact = _dBEaselData.artifacts.artifact;
	artifacts.scroll = _dBEaselData.artifacts.scroll;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselGame::DBEaselGame() :
		firstLevelForceTrajectory( 5 )
	, failureExperienceFactor( 0.3f )
{
	levels.resize( 16 );
	availabilityTable.resize( 5, int() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselGame::operator&( IBinSaver &saver )
{
	saver.Add( 2, &levels );
	saver.Add( 3, &trajectories );
	saver.Add( 4, &firstLevelForceTrajectory );
	saver.Add( 5, &designerChainParams );
	saver.Add( 6, &paint );
	saver.Add( 7, &availabilityTable );
	saver.Add( 8, &failureExperienceFactor );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselGame::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselGame* parentPtr = (DBEaselGame*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselGame::SerializeSelf( IXmlSaver &saver )
{
	levels.resize( 16 );
	saver.Add( "levels", &levels );
	saver.Add( "trajectories", &trajectories );
	saver.Add( "firstLevelForceTrajectory", &firstLevelForceTrajectory );
	saver.Add( "designerChainParams", &designerChainParams );
	saver.Add( "paint", &paint );
	availabilityTable.resize( 5 );
	saver.Add( "availabilityTable", &availabilityTable );
	saver.Add( "failureExperienceFactor", &failureExperienceFactor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselGame::Assign( const DBEaselGame& _dBEaselGame )
{
	levels = _dBEaselGame.levels;
	trajectories = _dBEaselGame.trajectories;
	firstLevelForceTrajectory = _dBEaselGame.firstLevelForceTrajectory;
	designerChainParams = _dBEaselGame.designerChainParams;
	paint.picture = _dBEaselGame.paint.picture;
	paint.paintQuad = _dBEaselGame.paint.paintQuad;
	availabilityTable = _dBEaselGame.availabilityTable;
	failureExperienceFactor = _dBEaselGame.failureExperienceFactor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselPath::DBEaselPath()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselPath::operator&( IBinSaver &saver )
{
	saver.Add( 2, &spline );
	saver.Add( 3, &splineData );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselPath::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselPath* parentPtr = (DBEaselPath*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselPath::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "spline", &spline );
	saver.Add( "splineData", &splineData );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselPath::Assign( const DBEaselPath& _dBEaselPath )
{
	spline.degree = _dBEaselPath.spline.degree;
	spline.cpnum = _dBEaselPath.spline.cpnum;
	spline.points.point = _dBEaselPath.spline.points.point;
	splineData.splinelenght = _dBEaselPath.splineData.splinelenght;
	splineData.tunnels.tunnel = _dBEaselPath.splineData.tunnels.tunnel;
	splineData.speedmarkers.speedmarker = _dBEaselPath.splineData.speedmarkers.speedmarker;
	splineData.startPoint.placement.pos = _dBEaselPath.splineData.startPoint.placement.pos;
	splineData.startPoint.placement.rot = _dBEaselPath.splineData.startPoint.placement.rot;
	splineData.startPoint.placement.scale = _dBEaselPath.splineData.startPoint.placement.scale;
	splineData.endPoint.placement.pos = _dBEaselPath.splineData.endPoint.placement.pos;
	splineData.endPoint.placement.rot = _dBEaselPath.splineData.endPoint.placement.rot;
	splineData.endPoint.placement.scale = _dBEaselPath.splineData.endPoint.placement.scale;
	splineData.atExitPoint = _dBEaselPath.splineData.atExitPoint;
	splineData.chainparams = _dBEaselPath.splineData.chainparams;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselSoundsData::DBEaselSoundsData()
{
	sounds.resize( 41 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSoundsData::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sounds );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSoundsData::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselSoundsData* parentPtr = (DBEaselSoundsData*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselSoundsData::SerializeSelf( IXmlSaver &saver )
{
	sounds.resize( 41 );
	saver.Add( "sounds", &sounds );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselSoundsData::Assign( const DBEaselSoundsData& _dBEaselSoundsData )
{
	sounds = _dBEaselSoundsData.sounds;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBEaselSpline::DBEaselSpline() :
		overridePristessPosition( false )
	, colorWeightsPower( 0.0f )
	, colorWeightsMultiplier( 0.0f )
	, overrideColorWeightsParams( false )
	, difficulty( DIFFICULTYLEVEL_UNKNOWN )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSpline::operator&( IBinSaver &saver )
{
	saver.Add( 2, &priestessPosition );
	saver.Add( 3, &overridePristessPosition );
	saver.Add( 4, &colorWeightsPower );
	saver.Add( 5, &colorWeightsMultiplier );
	saver.Add( 6, &overrideColorWeightsParams );
	saver.Add( 7, &difficulty );
	saver.Add( 8, &board );
	saver.Add( 9, &path );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBEaselSpline::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBEaselSpline* parentPtr = (DBEaselSpline*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselSpline::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "priestessPosition", &priestessPosition );
	saver.Add( "overridePristessPosition", &overridePristessPosition );
	saver.Add( "colorWeightsPower", &colorWeightsPower );
	saver.Add( "colorWeightsMultiplier", &colorWeightsMultiplier );
	saver.Add( "overrideColorWeightsParams", &overrideColorWeightsParams );
	saver.Add( "difficulty", &difficulty );
	saver.Add( "board", &board );
	saver.Add( "path", &path );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBEaselSpline::Assign( const DBEaselSpline& _dBEaselSpline )
{
	priestessPosition.pos = _dBEaselSpline.priestessPosition.pos;
	priestessPosition.rot = _dBEaselSpline.priestessPosition.rot;
	priestessPosition.scale = _dBEaselSpline.priestessPosition.scale;
	overridePristessPosition = _dBEaselSpline.overridePristessPosition;
	colorWeightsPower = _dBEaselSpline.colorWeightsPower;
	colorWeightsMultiplier = _dBEaselSpline.colorWeightsMultiplier;
	overrideColorWeightsParams = _dBEaselSpline.overrideColorWeightsParams;
	difficulty = _dBEaselSpline.difficulty;
	board.width = _dBEaselSpline.board.width;
	board.height = _dBEaselSpline.board.height;
	path = _dBEaselSpline.path;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBLuxBall::DBLuxBall() :
		ballColor( COLOR_BLACK )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLuxBall::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ballColor );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBLuxBall::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBLuxBall* parentPtr = (DBLuxBall*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLuxBall::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "ballColor", &ballColor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBLuxBall::Assign( const DBLuxBall& _dBLuxBall )
{
	ballColor = _dBLuxBall.ballColor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPainterFragment::DBPainterFragment()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPainterFragment::operator&( IBinSaver &saver )
{
	saver.Add( 2, &painterFragment );
	saver.Add( 3, &paintMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPainterFragment::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBPainterFragment* parentPtr = (DBPainterFragment*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPainterFragment::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "painterFragment", &painterFragment );
	saver.Add( "paintMaterial", &paintMaterial );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPainterFragment::Assign( const DBPainterFragment& _dBPainterFragment )
{
	painterFragment.listFragments = _dBPainterFragment.painterFragment.listFragments;
	paintMaterial = _dBPainterFragment.paintMaterial;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPainterPoint::DBPainterPoint() :
		pointCapacity( 1 )
	, pointColor( COLOR_BLACK )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPainterPoint::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pointCoords );
	saver.Add( 3, &pointCapacity );
	saver.Add( 4, &pointColor );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPainterPoint::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBPainterPoint* parentPtr = (DBPainterPoint*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPainterPoint::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "pointCoords", &pointCoords );
	saver.Add( "pointCapacity", &pointCapacity );
	saver.Add( "pointColor", &pointColor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPainterPoint::Assign( const DBPainterPoint& _dBPainterPoint )
{
	pointCoords.xCoord = _dBPainterPoint.pointCoords.xCoord;
	pointCoords.yCoord = _dBPainterPoint.pointCoords.yCoord;
	pointCoords.zCoord = _dBPainterPoint.pointCoords.zCoord;
	pointCapacity = _dBPainterPoint.pointCapacity;
	pointColor = _dBPainterPoint.pointColor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPriestessLevelStats::DBPriestessLevelStats() :
		level( PRIESTESSLEVEL_LEVEL_0 )
	, pictureEndNafta( 0 )
	, ballExplosionNafta( 0 )
	, chainKillNafta( 0 )
	, paintFragmentFinishedNafta( 0 )
	, fastCompletePerSecondNafta( 0 )
	, naftaRequired( 0 )
	, goldMedalTime( 100.0f )
	, silverMedalTime( 150.0f )
	, goldMedalNafta( 0 )
	, silverMedalNafta( 0 )
	, failNaftaReturnMultiplier( 0.66f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPriestessLevelStats::operator&( IBinSaver &saver )
{
	saver.Add( 2, &level );
	saver.Add( 3, &pictureEndNafta );
	saver.Add( 4, &ballExplosionNafta );
	saver.Add( 5, &chainKillNafta );
	saver.Add( 6, &paintFragmentFinishedNafta );
	saver.Add( 7, &fastCompletePerSecondNafta );
	saver.Add( 8, &naftaRequired );
	saver.Add( 9, &goldMedalTime );
	saver.Add( 10, &silverMedalTime );
	saver.Add( 11, &goldMedalNafta );
	saver.Add( 12, &silverMedalNafta );
	saver.Add( 13, &failNaftaReturnMultiplier );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPriestessLevelStats::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBPriestessLevelStats* parentPtr = (DBPriestessLevelStats*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPriestessLevelStats::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "level", &level );
	saver.Add( "pictureEndNafta", &pictureEndNafta );
	saver.Add( "ballExplosionNafta", &ballExplosionNafta );
	saver.Add( "chainKillNafta", &chainKillNafta );
	saver.Add( "paintFragmentFinishedNafta", &paintFragmentFinishedNafta );
	saver.Add( "fastCompletePerSecondNafta", &fastCompletePerSecondNafta );
	saver.Add( "naftaRequired", &naftaRequired );
	saver.Add( "goldMedalTime", &goldMedalTime );
	saver.Add( "silverMedalTime", &silverMedalTime );
	saver.Add( "goldMedalNafta", &goldMedalNafta );
	saver.Add( "silverMedalNafta", &silverMedalNafta );
	saver.Add( "failNaftaReturnMultiplier", &failNaftaReturnMultiplier );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPriestessLevelStats::Assign( const DBPriestessLevelStats& _dBPriestessLevelStats )
{
	level = _dBPriestessLevelStats.level;
	pictureEndNafta = _dBPriestessLevelStats.pictureEndNafta;
	ballExplosionNafta = _dBPriestessLevelStats.ballExplosionNafta;
	chainKillNafta = _dBPriestessLevelStats.chainKillNafta;
	paintFragmentFinishedNafta = _dBPriestessLevelStats.paintFragmentFinishedNafta;
	fastCompletePerSecondNafta = _dBPriestessLevelStats.fastCompletePerSecondNafta;
	naftaRequired = _dBPriestessLevelStats.naftaRequired;
	goldMedalTime = _dBPriestessLevelStats.goldMedalTime;
	silverMedalTime = _dBPriestessLevelStats.silverMedalTime;
	goldMedalNafta = _dBPriestessLevelStats.goldMedalNafta;
	silverMedalNafta = _dBPriestessLevelStats.silverMedalNafta;
	failNaftaReturnMultiplier = _dBPriestessLevelStats.failNaftaReturnMultiplier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBPriestessStats::DBPriestessStats() :
		comboNafta( 10 )
	, coinNafta( 10 )
	, heartsForLevelsStartsFrom( 5 )
{
	stats.resize( 16 );
	wonGameHearts.resize( 4, float() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPriestessStats::operator&( IBinSaver &saver )
{
	saver.Add( 2, &stats );
	saver.Add( 3, &comboNafta );
	saver.Add( 4, &coinNafta );
	saver.Add( 5, &heartsForLevelsStartsFrom );
	saver.Add( 6, &wonGameHearts );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBPriestessStats::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBPriestessStats* parentPtr = (DBPriestessStats*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPriestessStats::SerializeSelf( IXmlSaver &saver )
{
	stats.resize( 16 );
	saver.Add( "stats", &stats );
	saver.Add( "comboNafta", &comboNafta );
	saver.Add( "coinNafta", &coinNafta );
	saver.Add( "heartsForLevelsStartsFrom", &heartsForLevelsStartsFrom );
	wonGameHearts.resize( 4 );
	saver.Add( "wonGameHearts", &wonGameHearts );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBPriestessStats::Assign( const DBPriestessStats& _dBPriestessStats )
{
	stats = _dBPriestessStats.stats;
	comboNafta = _dBPriestessStats.comboNafta;
	coinNafta = _dBPriestessStats.coinNafta;
	heartsForLevelsStartsFrom = _dBPriestessStats.heartsForLevelsStartsFrom;
	wonGameHearts = _dBPriestessStats.wonGameHearts;
}
}; // namespace NDb
