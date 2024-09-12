#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Sound/DBSound.h"

struct IXmlSaver;

namespace NDb
{
enum SoundAmbientGroup
{
	SOUNDAMBIENTGROUP_BASEA = 0,
	SOUNDAMBIENTGROUP_BASEB = 1,
	SOUNDAMBIENTGROUP_FORESTN = 2,
	SOUNDAMBIENTGROUP_FORESTA = 3,
	SOUNDAMBIENTGROUP_FORESTB = 4,
	SOUNDAMBIENTGROUP_WATER = 5,
	SOUNDAMBIENTGROUP_ROAD = 6,
};

const char *EnumToString( const SoundAmbientGroup value );
const SoundAmbientGroup StringToEnum_SoundAmbientGroup( const char* value );

template <>
struct KnownEnum< SoundAmbientGroup >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const SoundAmbientGroup value ) { return EnumToString( value ); }
	static const SoundAmbientGroup ToEnum( const char* value ) { return StringToEnum_SoundAmbientGroup( value ); }
	static const SoundAmbientGroup ToEnum( const string& value ) { return StringToEnum_SoundAmbientGroup( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum SoundScene
{
	SOUNDSCENE_SESSIONA = 0,
	SOUNDSCENE_SESSIONB = 1,
	SOUNDSCENE_MINIGAME_02 = 2,
	SOUNDSCENE_LOADING = 3,
	SOUNDSCENE_DEAD = 4,
	SOUNDSCENE_BATTLE = 5,
	SOUNDSCENE_WIN = 6,
	SOUNDSCENE_DEFEAT = 7,
	SOUNDSCENE_TUTORIALA = 8,
	SOUNDSCENE_TUTORIALB = 9,
	SOUNDSCENE_TOWERDEATH = 10,
};

const char *EnumToString( const SoundScene value );
const SoundScene StringToEnum_SoundScene( const char* value );

template <>
struct KnownEnum< SoundScene >
{
	enum { isKnown = 1 };
	enum { sizeOf = 11 };
	static const char *ToString( const SoundScene value ) { return EnumToString( value ); }
	static const SoundScene ToEnum( const char* value ) { return StringToEnum_SoundScene( value ); }
	static const SoundScene ToEnum( const string& value ) { return StringToEnum_SoundScene( value.c_str() ); }
	static const int SizeOf() { return 11; }
};

struct SoundAmbientDesc
{
public:
	string paramName;
	Render::HDRColor color;
	string reverbPresetName;

	SoundAmbientDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TimerSounds
{
public:
	DBFMODEventDesc startTimerSound;
	DBFMODEventDesc startEventA;
	DBFMODEventDesc startEventB;
	DBFMODEventDesc deadTimerSound;
	string deadReverbName;
	float timeToRestorePitch;
	float timeToTickOnStart;

	TimerSounds();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundRoot : public DbResource
{
	DBRESOURCE_METHODS( SoundRoot );
private:
	static Ptr< SoundRoot > instance;
	static bool instanceInitialized;
public:
	vector< SoundSceneDesc > sceneScenes;
	TimerSounds timerSounds;
	DBFMODEventDesc heartbeat;
	DBFMODEventDesc heartbeatFemale;
	string heartbeatParamName;
	DBFMODEventDesc ambient;
	vector< SoundAmbientDesc > ambienceGroups;
	DBFMODEventDesc preferencesVolumeHasChanged;
	DBFMODEventDesc lastHit;
	float timerHeroAskIdle;
	float timeToTowerDeath;

	SoundRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SoundRoot& operator = ( const SoundRoot &_soundRoot ) { Assign( _soundRoot ); return *this; }
	SoundRoot( const SoundRoot &_soundRoot ) { Assign( _soundRoot ); }
	virtual void Assign( const SoundRoot &_soundRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SoundRoot * pOther = dynamic_cast< const SoundRoot * > ( _pResource );
		if ( pOther ) SoundRoot::Assign( *pOther );
	}
	static void InitRoot( const DBID& dbid );
	static void InitRoot( const SoundRoot* instance );
	static const Ptr< SoundRoot >& GetRoot();
};

}; // namespace NDb
