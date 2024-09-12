#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;

namespace NDb
{
struct AdventureCameraSettings;
struct AnimSet;
struct BasicEffectAttached;
struct BasicEffectStandalone;
struct EffectBase;
struct EffectsPool;
struct EmoteSettings;
struct TeamsColoringScheme;
struct UIEventsCustom;
struct UnitCategories;
struct UnitCategoriesParams;

enum EAnimSetID
{
	ANIMSETID_CREEP = 0,
	ANIMSETID_HERO = 1,
	ANIMSETID_PRIESTESS = 2,
	ANIMSETID_SITTINGPRIESTESS = 3,
	ANIMSETID_CRITTER = 4,
};

const char *EnumToString( const EAnimSetID value );
const EAnimSetID StringToEnum_EAnimSetID( const char* value );

template <>
struct KnownEnum< EAnimSetID >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EAnimSetID value ) { return EnumToString( value ); }
	static const EAnimSetID ToEnum( const char* value ) { return StringToEnum_EAnimSetID( value ); }
	static const EAnimSetID ToEnum( const string& value ) { return StringToEnum_EAnimSetID( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EAuraEffectType
{
	AURAEFFECTTYPE_ALLY = 0,
	AURAEFFECTTYPE_ENEMY = 1,
	AURAEFFECTTYPE_MIXED = 2,
};

const char *EnumToString( const EAuraEffectType value );
const EAuraEffectType StringToEnum_EAuraEffectType( const char* value );

template <>
struct KnownEnum< EAuraEffectType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAuraEffectType value ) { return EnumToString( value ); }
	static const EAuraEffectType ToEnum( const char* value ) { return StringToEnum_EAuraEffectType( value ); }
	static const EAuraEffectType ToEnum( const string& value ) { return StringToEnum_EAuraEffectType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EFemaleMaleAssistEffectSate
{
	FEMALEMALEASSISTEFFECTSATE_HEROTOMIDDLE = 0,
	FEMALEMALEASSISTEFFECTSATE_MIDDLETOHERO = 1,
	FEMALEMALEASSISTEFFECTSATE_SINGLEATMIDLE = 2,
	FEMALEMALEASSISTEFFECTSATE_STARTFLASH = 3,
	FEMALEMALEASSISTEFFECTSATE_DESTROY = 4,
};

const char *EnumToString( const EFemaleMaleAssistEffectSate value );
const EFemaleMaleAssistEffectSate StringToEnum_EFemaleMaleAssistEffectSate( const char* value );

template <>
struct KnownEnum< EFemaleMaleAssistEffectSate >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EFemaleMaleAssistEffectSate value ) { return EnumToString( value ); }
	static const EFemaleMaleAssistEffectSate ToEnum( const char* value ) { return StringToEnum_EFemaleMaleAssistEffectSate( value ); }
	static const EFemaleMaleAssistEffectSate ToEnum( const string& value ) { return StringToEnum_EFemaleMaleAssistEffectSate( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EWinLose
{
	WINLOSE_WIN = 0,
	WINLOSE_LOSE = 1,
};

const char *EnumToString( const EWinLose value );
const EWinLose StringToEnum_EWinLose( const char* value );

template <>
struct KnownEnum< EWinLose >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EWinLose value ) { return EnumToString( value ); }
	static const EWinLose ToEnum( const char* value ) { return StringToEnum_EWinLose( value ); }
	static const EWinLose ToEnum( const string& value ) { return StringToEnum_EWinLose( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct AnimSets
{
public:
	vector< Ptr< AnimSet > > sets;

	AnimSets();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AuraEffects
{
public:
	float minimalEffectIntencity;
	int maximalAuraCount;
	vector< Ptr< BasicEffectAttached > > auraEffects;

	AuraEffects();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EffectWithDelay
{
public:
	float deltaTime;
	Ptr< EffectBase > effect;

	EffectWithDelay();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FemaleMaleAssistEffect
{
public:
	float minDistanceBetweenHeroes;
	float middlePosHeight;
	vector< EffectWithDelay > effectsWithDelay;

	FemaleMaleAssistEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct WinLoseEffect
{
public:
	float cameraMovementTime;
	ViewCamera cameraPos;
	float effectDelay;
	Ptr< BasicEffectStandalone > effect;

	WinLoseEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SessionAudioRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionAudioRoot );
public:

	SessionAudioRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionAudioRoot& operator = ( const SessionAudioRoot &_sessionAudioRoot ) { Assign( _sessionAudioRoot ); return *this; }
	SessionAudioRoot( const SessionAudioRoot &_sessionAudioRoot ) { Assign( _sessionAudioRoot ); }
	virtual void Assign( const SessionAudioRoot &_sessionAudioRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionAudioRoot * pOther = dynamic_cast< const SessionAudioRoot * > ( _pResource );
		if ( pOther ) SessionAudioRoot::Assign( *pOther );
	}
};

struct SessionUIRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionUIRoot );
public:
	Ptr< UnitCategories > unitCategories;
	Ptr< UnitCategoriesParams > unitCategoriesParams;

	SessionUIRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionUIRoot& operator = ( const SessionUIRoot &_sessionUIRoot ) { Assign( _sessionUIRoot ); return *this; }
	SessionUIRoot( const SessionUIRoot &_sessionUIRoot ) { Assign( _sessionUIRoot ); }
	virtual void Assign( const SessionUIRoot &_sessionUIRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionUIRoot * pOther = dynamic_cast< const SessionUIRoot * > ( _pResource );
		if ( pOther ) SessionUIRoot::Assign( *pOther );
	}
};

struct SessionVisualRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionVisualRoot );
public:
	Ptr< EmoteSettings > emoteSettings;
	Ptr< TeamsColoringScheme > teamColoringScheme;
	Ptr< EffectsPool > effects;
	vector< Ptr< BasicEffectAttached > > selfAuraEffects;
	AnimSets animSets;
	AuraEffects auraEffects;
	Ptr< UIEventsCustom > uiEvents;
	vector< Ptr< AdventureCameraSettings > > cameras;
	vector< WinLoseEffect > winLoseEffects;
	FemaleMaleAssistEffect femaleMaleAssistEffect;
	float wallTargetZoneWidth;

	SessionVisualRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionVisualRoot& operator = ( const SessionVisualRoot &_sessionVisualRoot ) { Assign( _sessionVisualRoot ); return *this; }
	SessionVisualRoot( const SessionVisualRoot &_sessionVisualRoot ) { Assign( _sessionVisualRoot ); }
	virtual void Assign( const SessionVisualRoot &_sessionVisualRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionVisualRoot * pOther = dynamic_cast< const SessionVisualRoot * > ( _pResource );
		if ( pOther ) SessionVisualRoot::Assign( *pOther );
	}
};

}; // namespace NDb
