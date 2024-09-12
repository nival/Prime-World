#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct FMODEventProject;
struct Texture;

enum EAskSounds
{
	ASKSOUNDS_MOVE = 0,
	ASKSOUNDS_ABILITY_1 = 1,
	ASKSOUNDS_ABILITY_2 = 2,
	ASKSOUNDS_ABILITY_3 = 3,
	ASKSOUNDS_ABILITY_ULT = 4,
	ASKSOUNDS_ATTACK = 5,
	ASKSOUNDS_DEATH = 6,
	ASKSOUNDS_REVIVE = 7,
	ASKSOUNDS_KILL = 8,
	ASKSOUNDS_IDLE = 9,
	ASKSOUNDS_RAISEFLAG = 10,
	ASKSOUNDS_KILLCHAMPION = 11,
	ASKSOUNDS_MINIGAMEWIN = 12,
	ASKSOUNDS_MINIGAMEFAIL = 13,
};

const char *EnumToString( const EAskSounds value );
const EAskSounds StringToEnum_EAskSounds( const char* value );

template <>
struct KnownEnum< EAskSounds >
{
	enum { isKnown = 1 };
	enum { sizeOf = 14 };
	static const char *ToString( const EAskSounds value ) { return EnumToString( value ); }
	static const EAskSounds ToEnum( const char* value ) { return StringToEnum_EAskSounds( value ); }
	static const EAskSounds ToEnum( const string& value ) { return StringToEnum_EAskSounds( value.c_str() ); }
	static const int SizeOf() { return 14; }
};

enum SoundCameraType
{
	SOUNDCAMERATYPE_TOPDOWN = 0,
	SOUNDCAMERATYPE_PERSPECTIVE = 1,
};

const char *EnumToString( const SoundCameraType value );
const SoundCameraType StringToEnum_SoundCameraType( const char* value );

template <>
struct KnownEnum< SoundCameraType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const SoundCameraType value ) { return EnumToString( value ); }
	static const SoundCameraType ToEnum( const char* value ) { return StringToEnum_SoundCameraType( value ); }
	static const SoundCameraType ToEnum( const string& value ) { return StringToEnum_SoundCameraType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct DBFMODEventDesc
{
public:
	string projectName;
	string groupName;
	string eventName;

	DBFMODEventDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FMODEvent
{
public:
	string name;

	FMODEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FMODEventGroup
{
public:
	string name;
	vector< FMODEventGroup > groups;
	vector< FMODEvent > events;

	FMODEventGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FMODGroupInstance
{
public:
	Ptr< FMODEventProject > project;
	string fmodGroup;

	FMODGroupInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FMODEventInstance
{
public:
	FMODGroupInstance fmodGroup;
	string name;

	FMODEventInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MusicDesc
{
public:
	string cueName;

	MusicDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundAmbienceMap
{
public:
	Ptr< Texture > texture;
	float radius;
	float directivity;

	SoundAmbienceMap();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundCamera
{
public:
	SoundCameraType type;
	float multiplier;

	SoundCamera();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundSceneGroupDesc
{
public:
	string categoryName;
	float pitch;
	Animated<float, NDb::AnimatedAlgorithms::Linear> volume;

	SoundSceneGroupDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundSceneDesc
{
public:
	vector< SoundSceneGroupDesc > soundSceneGroups;
	MusicDesc cue;

	SoundSceneDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FMODEventProject : public DbResource
{
	DBRESOURCE_METHODS( FMODEventProject );
public:
	string name;
	vector< FMODEventGroup > groups;

	FMODEventProject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FMODEventProject& operator = ( const FMODEventProject &_fMODEventProject ) { Assign( _fMODEventProject ); return *this; }
	FMODEventProject( const FMODEventProject &_fMODEventProject ) { Assign( _fMODEventProject ); }
	virtual void Assign( const FMODEventProject &_fMODEventProject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FMODEventProject * pOther = dynamic_cast< const FMODEventProject * > ( _pResource );
		if ( pOther ) FMODEventProject::Assign( *pOther );
	}
};

struct Sound2D : public DbResource
{
	DBRESOURCE_METHODS( Sound2D );
public:
	string soundFile;
	float offset;
	int cycleCount;
	float volume;

	Sound2D();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Sound2D& operator = ( const Sound2D &_sound2D ) { Assign( _sound2D ); return *this; }
	Sound2D( const Sound2D &_sound2D ) { Assign( _sound2D ); }
	virtual void Assign( const Sound2D &_sound2D );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Sound2D * pOther = dynamic_cast< const Sound2D * > ( _pResource );
		if ( pOther ) Sound2D::Assign( *pOther );
	}
};

struct SoundEnvironment : public DbResource
{
	DBRESOURCE_METHODS( SoundEnvironment );
public:
	CTextRef language;
	SoundCamera soundCamera;
	vector< string > fevFiles;
	vector< string > banks;

	SoundEnvironment();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SoundEnvironment& operator = ( const SoundEnvironment &_soundEnvironment ) { Assign( _soundEnvironment ); return *this; }
	SoundEnvironment( const SoundEnvironment &_soundEnvironment ) { Assign( _soundEnvironment ); }
	virtual void Assign( const SoundEnvironment &_soundEnvironment );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SoundEnvironment * pOther = dynamic_cast< const SoundEnvironment * > ( _pResource );
		if ( pOther ) SoundEnvironment::Assign( *pOther );
	}
};

struct SoundStream : public DbResource
{
	DBRESOURCE_METHODS( SoundStream );
public:
	string soundFile;
	int cycleCount;
	float volume;

	SoundStream();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SoundStream& operator = ( const SoundStream &_soundStream ) { Assign( _soundStream ); return *this; }
	SoundStream( const SoundStream &_soundStream ) { Assign( _soundStream ); }
	virtual void Assign( const SoundStream &_soundStream );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SoundStream * pOther = dynamic_cast< const SoundStream * > ( _pResource );
		if ( pOther ) SoundStream::Assign( *pOther );
	}
};

}; // namespace NDb
