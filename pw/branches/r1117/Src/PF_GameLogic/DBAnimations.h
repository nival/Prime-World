#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
enum EAnimStatePlayMode
{
	ANIMSTATEPLAYMODE_PLAYNORMAL = 0,
	ANIMSTATEPLAYMODE_PLAYUPPER = 1,
	ANIMSTATEPLAYMODE_PLAYBOTH = 2,
};

const char *EnumToString( const EAnimStatePlayMode value );
const EAnimStatePlayMode StringToEnum_EAnimStatePlayMode( const char* value );

template <>
struct KnownEnum< EAnimStatePlayMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAnimStatePlayMode value ) { return EnumToString( value ); }
	static const EAnimStatePlayMode ToEnum( const char* value ) { return StringToEnum_EAnimStatePlayMode( value ); }
	static const EAnimStatePlayMode ToEnum( const string& value ) { return StringToEnum_EAnimStatePlayMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EAnimStates
{
	ANIMSTATES_INVALID = 0,
	ANIMSTATES_IDLE = 1,
	ANIMSTATES_STUN = 2,
	ANIMSTATES_MOVE = 3,
	ANIMSTATES_BLOCKEDMOVE = 4,
	ANIMSTATES_ATTACK = 5,
	ANIMSTATES_ABILITY1 = 6,
	ANIMSTATES_ABILITY2 = 7,
	ANIMSTATES_ABILITY3 = 8,
	ANIMSTATES_ABILITY4 = 9,
	ANIMSTATES_DEATH = 10,
	ANIMSTATES_RESURRECT = 11,
	ANIMSTATES_SUMMON = 12,
	ANIMSTATES_UNSUMMON = 13,
	ANIMSTATES_HELLO = 14,
	ANIMSTATES_HAPPY = 15,
	ANIMSTATES_SAD = 16,
	ANIMSTATES_MINIGAMING = 17,
	ANIMSTATES_SPECIAL1 = 18,
	ANIMSTATES_SPECIAL2 = 19,
	ANIMSTATES_SPECIAL3 = 20,
	ANIMSTATES_SPECIAL4 = 21,
	ANIMSTATES_HIDE = 22,
};

const char *EnumToString( const EAnimStates value );
const EAnimStates StringToEnum_EAnimStates( const char* value );

template <>
struct KnownEnum< EAnimStates >
{
	enum { isKnown = 1 };
	enum { sizeOf = 23 };
	static const char *ToString( const EAnimStates value ) { return EnumToString( value ); }
	static const EAnimStates ToEnum( const char* value ) { return StringToEnum_EAnimStates( value ); }
	static const EAnimStates ToEnum( const string& value ) { return StringToEnum_EAnimStates( value.c_str() ); }
	static const int SizeOf() { return 23; }
};

enum EEmotePermission
{
	EMOTEPERMISSION_PLAYNONE = 0,
	EMOTEPERMISSION_PLAYUPPER = 1,
	EMOTEPERMISSION_PLAYLOWER = 2,
	EMOTEPERMISSION_PLAYBOTH = 3,
};

const char *EnumToString( const EEmotePermission value );
const EEmotePermission StringToEnum_EEmotePermission( const char* value );

template <>
struct KnownEnum< EEmotePermission >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EEmotePermission value ) { return EnumToString( value ); }
	static const EEmotePermission ToEnum( const char* value ) { return StringToEnum_EEmotePermission( value ); }
	static const EEmotePermission ToEnum( const string& value ) { return StringToEnum_EEmotePermission( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EEmotion
{
	EMOTION_HAPPY = 0,
	EMOTION_SAD = 1,
	EMOTION_HELLO = 2,
};

const char *EnumToString( const EEmotion value );
const EEmotion StringToEnum_EEmotion( const char* value );

template <>
struct KnownEnum< EEmotion >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEmotion value ) { return EnumToString( value ); }
	static const EEmotion ToEnum( const char* value ) { return StringToEnum_EEmotion( value ); }
	static const EEmotion ToEnum( const string& value ) { return StringToEnum_EEmotion( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct AnimStateDataNew
{
public:
	EAnimStates animState;
	string node;
	string marker;

	AnimStateDataNew();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimStateData
{
public:
	string commonNode;
	string upperNode;
	EAnimStatePlayMode playMode;
	string commonMarker;
	string upperMarker;

	AnimStateData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimStateChanger
{
public:
	AnimStateDataNew oldAnimation;
	AnimStateDataNew newAnimation;

	AnimStateChanger();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EmotePlayNodeParams
{
public:
	vector< EEmotePermission > permissions;

	EmotePlayNodeParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimSet : public DbResource
{
	DBRESOURCE_METHODS( AnimSet );
public:
	vector< AnimStateData > states;

	AnimSet();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AnimSet& operator = ( const AnimSet &_animSet ) { Assign( _animSet ); return *this; }
	AnimSet( const AnimSet &_animSet ) { Assign( _animSet ); }
	virtual void Assign( const AnimSet &_animSet );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AnimSet * pOther = dynamic_cast< const AnimSet * > ( _pResource );
		if ( pOther ) AnimSet::Assign( *pOther );
	}
};

struct EmoteSettings : public DbResource
{
	DBRESOURCE_METHODS( EmoteSettings );
public:
	vector< EmotePlayNodeParams > nodes;

	EmoteSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EmoteSettings& operator = ( const EmoteSettings &_emoteSettings ) { Assign( _emoteSettings ); return *this; }
	EmoteSettings( const EmoteSettings &_emoteSettings ) { Assign( _emoteSettings ); }
	virtual void Assign( const EmoteSettings &_emoteSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EmoteSettings * pOther = dynamic_cast< const EmoteSettings * > ( _pResource );
		if ( pOther ) EmoteSettings::Assign( *pOther );
	}
};

}; // namespace NDb
