// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBAnimations.h"
#include "../PF_Core/DBEffect.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBStats.h"
#include "DBVisualRoots.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SessionAudioRoot );
REGISTER_DBRESOURCE( SessionUIRoot );
REGISTER_DBRESOURCE( SessionVisualRoot );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnimSetID value )
{
	switch( value )
	{
		case ANIMSETID_CREEP:
			return "Creep";
		case ANIMSETID_HERO:
			return "Hero";
		case ANIMSETID_PRIESTESS:
			return "Priestess";
		case ANIMSETID_SITTINGPRIESTESS:
			return "SittingPriestess";
		case ANIMSETID_CRITTER:
			return "Critter";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnimSetID", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnimSetID StringToEnum_EAnimSetID( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnimSetID)(NStr::ToInt( value ));
	if ( strcmp( value, "Creep" ) == 0 || strcmp( value, "ANIMSETID_CREEP" ) == 0 )
		return ANIMSETID_CREEP;
	if ( strcmp( value, "Hero" ) == 0 || strcmp( value, "ANIMSETID_HERO" ) == 0 )
		return ANIMSETID_HERO;
	if ( strcmp( value, "Priestess" ) == 0 || strcmp( value, "ANIMSETID_PRIESTESS" ) == 0 )
		return ANIMSETID_PRIESTESS;
	if ( strcmp( value, "SittingPriestess" ) == 0 || strcmp( value, "ANIMSETID_SITTINGPRIESTESS" ) == 0 )
		return ANIMSETID_SITTINGPRIESTESS;
	if ( strcmp( value, "Critter" ) == 0 || strcmp( value, "ANIMSETID_CRITTER" ) == 0 )
		return ANIMSETID_CRITTER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnimSetID", value ) );
	return ANIMSETID_CREEP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAuraEffectType value )
{
	switch( value )
	{
		case AURAEFFECTTYPE_ALLY:
			return "Ally";
		case AURAEFFECTTYPE_ENEMY:
			return "Enemy";
		case AURAEFFECTTYPE_MIXED:
			return "Mixed";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAuraEffectType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAuraEffectType StringToEnum_EAuraEffectType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAuraEffectType)(NStr::ToInt( value ));
	if ( strcmp( value, "Ally" ) == 0 || strcmp( value, "AURAEFFECTTYPE_ALLY" ) == 0 )
		return AURAEFFECTTYPE_ALLY;
	if ( strcmp( value, "Enemy" ) == 0 || strcmp( value, "AURAEFFECTTYPE_ENEMY" ) == 0 )
		return AURAEFFECTTYPE_ENEMY;
	if ( strcmp( value, "Mixed" ) == 0 || strcmp( value, "AURAEFFECTTYPE_MIXED" ) == 0 )
		return AURAEFFECTTYPE_MIXED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAuraEffectType", value ) );
	return AURAEFFECTTYPE_ALLY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EFemaleMaleAssistEffectSate value )
{
	switch( value )
	{
		case FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE:
			return "HeroToMiddle";
		case FEMALEMALEASSISTEFFECTSATE_MIDDLETOHERO:
			return "MiddleToHero";
		case FEMALEMALEASSISTEFFECTSATE_SINGLEATMIDLE:
			return "SingleAtMidle";
		case FEMALEMALEASSISTEFFECTSATE_STARTFLASH:
			return "StartFlash";
		case FEMALEMALEASSISTEFFECTSATE_DESTROY:
			return "Destroy";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EFemaleMaleAssistEffectSate", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EFemaleMaleAssistEffectSate StringToEnum_EFemaleMaleAssistEffectSate( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EFemaleMaleAssistEffectSate)(NStr::ToInt( value ));
	if ( strcmp( value, "HeroToMiddle" ) == 0 || strcmp( value, "FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE" ) == 0 )
		return FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE;
	if ( strcmp( value, "MiddleToHero" ) == 0 || strcmp( value, "FEMALEMALEASSISTEFFECTSATE_MIDDLETOHERO" ) == 0 )
		return FEMALEMALEASSISTEFFECTSATE_MIDDLETOHERO;
	if ( strcmp( value, "SingleAtMidle" ) == 0 || strcmp( value, "FEMALEMALEASSISTEFFECTSATE_SINGLEATMIDLE" ) == 0 )
		return FEMALEMALEASSISTEFFECTSATE_SINGLEATMIDLE;
	if ( strcmp( value, "StartFlash" ) == 0 || strcmp( value, "FEMALEMALEASSISTEFFECTSATE_STARTFLASH" ) == 0 )
		return FEMALEMALEASSISTEFFECTSATE_STARTFLASH;
	if ( strcmp( value, "Destroy" ) == 0 || strcmp( value, "FEMALEMALEASSISTEFFECTSATE_DESTROY" ) == 0 )
		return FEMALEMALEASSISTEFFECTSATE_DESTROY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EFemaleMaleAssistEffectSate", value ) );
	return FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EWinLose value )
{
	switch( value )
	{
		case WINLOSE_WIN:
			return "Win";
		case WINLOSE_LOSE:
			return "Lose";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EWinLose", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EWinLose StringToEnum_EWinLose( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EWinLose)(NStr::ToInt( value ));
	if ( strcmp( value, "Win" ) == 0 || strcmp( value, "WINLOSE_WIN" ) == 0 )
		return WINLOSE_WIN;
	if ( strcmp( value, "Lose" ) == 0 || strcmp( value, "WINLOSE_LOSE" ) == 0 )
		return WINLOSE_LOSE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EWinLose", value ) );
	return WINLOSE_WIN;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimSets::AnimSets()
{
	sets.resize( 5 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimSets::operator&( IBinSaver &saver )
{
	saver.Add( 2, &sets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimSets::operator&( IXmlSaver &saver )
{
	sets.resize( 5 );
	saver.Add( "sets", &sets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AuraEffects::AuraEffects() :
		minimalEffectIntencity( 0.5f )
	, maximalAuraCount( 3 )
{
	auraEffects.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraEffects::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minimalEffectIntencity );
	saver.Add( 3, &maximalAuraCount );
	saver.Add( 4, &auraEffects );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AuraEffects::operator&( IXmlSaver &saver )
{
	saver.Add( "minimalEffectIntencity", &minimalEffectIntencity );
	saver.Add( "maximalAuraCount", &maximalAuraCount );
	auraEffects.resize( 3 );
	saver.Add( "auraEffects", &auraEffects );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectWithDelay::EffectWithDelay() :
		deltaTime( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectWithDelay::operator&( IBinSaver &saver )
{
	saver.Add( 2, &deltaTime );
	saver.Add( 3, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int EffectWithDelay::operator&( IXmlSaver &saver )
{
	saver.Add( "deltaTime", &deltaTime );
	saver.Add( "effect", &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FemaleMaleAssistEffect::FemaleMaleAssistEffect() :
		minDistanceBetweenHeroes( 23.0f )
	, middlePosHeight( 4.0f )
{
	effectsWithDelay.resize( 5 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FemaleMaleAssistEffect::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minDistanceBetweenHeroes );
	saver.Add( 3, &middlePosHeight );
	saver.Add( 4, &effectsWithDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FemaleMaleAssistEffect::operator&( IXmlSaver &saver )
{
	saver.Add( "minDistanceBetweenHeroes", &minDistanceBetweenHeroes );
	saver.Add( "middlePosHeight", &middlePosHeight );
	effectsWithDelay.resize( 5 );
	saver.Add( "effectsWithDelay", &effectsWithDelay );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WinLoseEffect::WinLoseEffect() :
		cameraMovementTime( 3.0f )
	, effectDelay( 3.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WinLoseEffect::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cameraMovementTime );
	saver.Add( 3, &cameraPos );
	saver.Add( 4, &effectDelay );
	saver.Add( 5, &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WinLoseEffect::operator&( IXmlSaver &saver )
{
	saver.Add( "cameraMovementTime", &cameraMovementTime );
	saver.Add( "cameraPos", &cameraPos );
	saver.Add( "effectDelay", &effectDelay );
	saver.Add( "effect", &effect );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionAudioRoot::SessionAudioRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionAudioRoot::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionAudioRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionAudioRoot* parentPtr = (SessionAudioRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionAudioRoot::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionAudioRoot::Assign( const SessionAudioRoot& _sessionAudioRoot )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionUIRoot::SessionUIRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionUIRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &unitCategories );
	saver.Add( 3, &unitCategoriesParams );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionUIRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionUIRoot* parentPtr = (SessionUIRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionUIRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "unitCategories", &unitCategories );
	saver.Add( "unitCategoriesParams", &unitCategoriesParams );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionUIRoot::Assign( const SessionUIRoot& _sessionUIRoot )
{
	unitCategories = _sessionUIRoot.unitCategories;
	unitCategoriesParams = _sessionUIRoot.unitCategoriesParams;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionVisualRoot::SessionVisualRoot() :
		wallTargetZoneWidth( 1.0f )
{
	selfAuraEffects.resize( 3 );
	winLoseEffects.resize( 2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionVisualRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &emoteSettings );
	saver.Add( 3, &teamColoringScheme );
	saver.Add( 4, &effects );
	saver.Add( 5, &selfAuraEffects );
	saver.Add( 6, &animSets );
	saver.Add( 7, &auraEffects );
	saver.Add( 8, &uiEvents );
	saver.Add( 9, &cameras );
	saver.Add( 10, &winLoseEffects );
	saver.Add( 11, &femaleMaleAssistEffect );
	saver.Add( 12, &wallTargetZoneWidth );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionVisualRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionVisualRoot* parentPtr = (SessionVisualRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionVisualRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "emoteSettings", &emoteSettings );
	saver.Add( "teamColoringScheme", &teamColoringScheme );
	saver.Add( "effects", &effects );
	selfAuraEffects.resize( 3 );
	saver.Add( "selfAuraEffects", &selfAuraEffects );
	saver.Add( "animSets", &animSets );
	saver.Add( "auraEffects", &auraEffects );
	saver.Add( "uiEvents", &uiEvents );
	saver.Add( "cameras", &cameras );
	winLoseEffects.resize( 2 );
	saver.Add( "winLoseEffects", &winLoseEffects );
	saver.Add( "femaleMaleAssistEffect", &femaleMaleAssistEffect );
	saver.Add( "wallTargetZoneWidth", &wallTargetZoneWidth );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionVisualRoot::Assign( const SessionVisualRoot& _sessionVisualRoot )
{
	emoteSettings = _sessionVisualRoot.emoteSettings;
	teamColoringScheme = _sessionVisualRoot.teamColoringScheme;
	effects = _sessionVisualRoot.effects;
	selfAuraEffects = _sessionVisualRoot.selfAuraEffects;
	animSets.sets = _sessionVisualRoot.animSets.sets;
	auraEffects.minimalEffectIntencity = _sessionVisualRoot.auraEffects.minimalEffectIntencity;
	auraEffects.maximalAuraCount = _sessionVisualRoot.auraEffects.maximalAuraCount;
	auraEffects.auraEffects = _sessionVisualRoot.auraEffects.auraEffects;
	uiEvents = _sessionVisualRoot.uiEvents;
	cameras = _sessionVisualRoot.cameras;
	winLoseEffects = _sessionVisualRoot.winLoseEffects;
	femaleMaleAssistEffect.minDistanceBetweenHeroes = _sessionVisualRoot.femaleMaleAssistEffect.minDistanceBetweenHeroes;
	femaleMaleAssistEffect.middlePosHeight = _sessionVisualRoot.femaleMaleAssistEffect.middlePosHeight;
	femaleMaleAssistEffect.effectsWithDelay = _sessionVisualRoot.femaleMaleAssistEffect.effectsWithDelay;
	wallTargetZoneWidth = _sessionVisualRoot.wallTargetZoneWidth;
}
}; // namespace NDb
