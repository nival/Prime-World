#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Render/DBRenderResources.h"
#include "../Sound/DBSound.h"

struct IXmlSaver;

namespace NDb
{
struct ChildEffect;
struct Effect;
struct LandTemp;
struct OmniLight;
struct RoadMaterial;
struct Skeleton;
struct SoundSet;
struct SoundSRC;
struct StaticMesh;

enum ELocatorAttachFlags
{
	LOCATORATTACHFLAGS_NONE = 0,
	LOCATORATTACHFLAGS_USEJOINTSCALE = 1,
	LOCATORATTACHFLAGS_USEJOINTROTATION = 2,
	LOCATORATTACHFLAGS_USEJOINTPOSITION = 4,
	LOCATORATTACHFLAGS_CANCELNORMALLEVELLING = 8,
};

const char *EnumToString( const ELocatorAttachFlags value );
const ELocatorAttachFlags StringToEnum_ELocatorAttachFlags( const char* value );

template <>
struct KnownEnum< ELocatorAttachFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const ELocatorAttachFlags value ) { return EnumToString( value ); }
	static const ELocatorAttachFlags ToEnum( const char* value ) { return StringToEnum_ELocatorAttachFlags( value ); }
	static const ELocatorAttachFlags ToEnum( const string& value ) { return StringToEnum_ELocatorAttachFlags( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

struct AnimFaceFXKey
{
public:
	float startTime;
	int animation;
	int cycleCount;
	string facefxname;

	AnimFaceFXKey();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LightInstance
{
public:
	Ptr< OmniLight > light;
	CVec3 position;
	CQuat rotation;
	float scale;
	float speed;
	float offset;
	float cycleLength;
	int cycleCount;
	string jointName;

	LightInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ModelInstance
{
public:
	Ptr< Skeleton > model;
	vector< AnimFaceFXKey > anims;
	vector< int > skins;
	Matrix43 trasform;
	float speed;
	float offset;
	float cycleLength;
	int cycleCount;
	float duration;
	float fadein;
	float fadeout;

	ModelInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Locator
{
public:
	string name;
	CPlacement offset2;
	ELocatorAttachFlags flags;
	string jointName;

	Locator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundInstance
{
public:
	string soundFile;
	float offset;
	int cycleCount;
	float volume;
	bool is3DSound;

	SoundInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ObjectLockMask
{
public:
	float tileSize;
	vector< CTPoint<int> > mask;

	ObjectLockMask();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RoadControlPoint : public FlatSplineControlPointDesc
{
public:
	float opacity;

	RoadControlPoint();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RoadProperties
{
public:
	float width;
	float border;
	float falloff;
	float opacity;
	float tileU;
	float tileV;
	float tileVBorder;
	bool fit;
	bool flip;
	float priority;
	Ptr< RoadMaterial > materialN;
	Ptr< RoadMaterial > materialA;
	Ptr< RoadMaterial > materialB;

	RoadProperties();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundTrack
{
public:
	Ptr< SoundSRC > sound;
	float volume;
	float volumeRandomization;
	int priority;

	SoundTrack();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StaticModelInstance
{
public:
	Ptr< StaticMesh > model;
	Matrix43 trasform;
	float offset;
	float duration;
	float fadein;
	float fadeout;

	StaticModelInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundObject
{
public:
	Ptr< SoundSet > soundSet;

	SoundObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SoundEffect : public SoundTrack
{
public:
	float pitch;
	float pitchRandomization;

	SoundEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EffectInstance
{
public:
	ModelInstance model;
	LightInstance light;
	StaticModelInstance staticmodel;
	SoundInstance sound;
	FMODEventInstance fmodEvent;
	string jointName;

	EffectInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SyncInfo
{
public:
	string midiFile;
	bool tempoSync;
	bool toneSync;
	float offset;

	SyncInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ViewCamera
{
public:
	string name;
	CVec3 anchor;
	float yaw;
	float pitch;
	float roll;
	int rod;
	int fov;
	string environment;

	ViewCamera();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ChildEffect : public DbResource
{
	DBRESOURCE_METHODS( ChildEffect );
public:
	Ptr< ChildEffect > tranformedchild;
	Ptr< Effect > childeffect;
	Matrix43 transform;

	ChildEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChildEffect& operator = ( const ChildEffect &_childEffect ) { Assign( _childEffect ); return *this; }
	ChildEffect( const ChildEffect &_childEffect ) { Assign( _childEffect ); }
	virtual void Assign( const ChildEffect &_childEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChildEffect * pOther = dynamic_cast< const ChildEffect * > ( _pResource );
		if ( pOther ) ChildEffect::Assign( *pOther );
	}
};

struct CollisionGeometry : public DbResource
{
	DBRESOURCE_METHODS( CollisionGeometry );
public:
	string srcFileName;
	string fileName;

	CollisionGeometry();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CollisionGeometry& operator = ( const CollisionGeometry &_collisionGeometry ) { Assign( _collisionGeometry ); return *this; }
	CollisionGeometry( const CollisionGeometry &_collisionGeometry ) { Assign( _collisionGeometry ); }
	virtual void Assign( const CollisionGeometry &_collisionGeometry );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CollisionGeometry * pOther = dynamic_cast< const CollisionGeometry * > ( _pResource );
		if ( pOther ) CollisionGeometry::Assign( *pOther );
	}
};

struct Effect : public DbResource
{
	DBRESOURCE_METHODS( Effect );
public:
	Ptr< LandTemp > landtemp;
	Ptr< ChildEffect > tranformedchild;
	Ptr< Effect > child;
	vector< EffectInstance > effects;
	bool randomizePhase;
	bool randomizeSpeed;

	Effect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Effect& operator = ( const Effect &_effect ) { Assign( _effect ); return *this; }
	Effect( const Effect &_effect ) { Assign( _effect ); }
	virtual void Assign( const Effect &_effect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Effect * pOther = dynamic_cast< const Effect * > ( _pResource );
		if ( pOther ) Effect::Assign( *pOther );
	}
};

struct GameObject : public DbResource
{
	DBRESOURCE_METHODS( GameObject );
public:
	enum { typeId = 0x9E5573C6 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GameObject::typeId; }
	CTRect<float> collision;
	ObjectLockMask lockMask;
	float minLockScale;
	bool rounded;
	bool heightObject;

	GameObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GameObject& operator = ( const GameObject &_gameObject ) { Assign( _gameObject ); return *this; }
	GameObject( const GameObject &_gameObject ) { Assign( _gameObject ); }
	virtual void Assign( const GameObject &_gameObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GameObject * pOther = dynamic_cast< const GameObject * > ( _pResource );
		if ( pOther ) GameObject::Assign( *pOther );
	}
};

struct LandTemp : public DbResource
{
	DBRESOURCE_METHODS( LandTemp );
public:
	float speed;
	int randomSeed;

	LandTemp();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LandTemp& operator = ( const LandTemp &_landTemp ) { Assign( _landTemp ); return *this; }
	LandTemp( const LandTemp &_landTemp ) { Assign( _landTemp ); }
	virtual void Assign( const LandTemp &_landTemp );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LandTemp * pOther = dynamic_cast< const LandTemp * > ( _pResource );
		if ( pOther ) LandTemp::Assign( *pOther );
	}
};

struct Road : public GameObject
{
	DBRESOURCE_METHODS( Road );
public:
	enum { typeId = 0xCB726281 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Road::typeId; }
	vector< RoadControlPoint > points;
	RoadProperties properties;
	string bakedFileName;

	Road();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Road& operator = ( const Road &_road ) { Assign( _road ); return *this; }
	Road( const Road &_road ) { Assign( _road ); }
	virtual void Assign( const Road &_road );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Road * pOther = dynamic_cast< const Road * > ( _pResource );
		if ( pOther ) Road::Assign( *pOther );
	}
};

struct ScriptPath : public GameObject
{
	DBRESOURCE_METHODS( ScriptPath );
public:
	enum { typeId = 0xE7920C10 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScriptPath::typeId; }
	vector< CVec2 > path;

	ScriptPath();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScriptPath& operator = ( const ScriptPath &_scriptPath ) { Assign( _scriptPath ); return *this; }
	ScriptPath( const ScriptPath &_scriptPath ) { Assign( _scriptPath ); }
	virtual void Assign( const ScriptPath &_scriptPath );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScriptPath * pOther = dynamic_cast< const ScriptPath * > ( _pResource );
		if ( pOther ) ScriptPath::Assign( *pOther );
	}
};

struct SoundSet : public DbResource
{
	DBRESOURCE_METHODS( SoundSet );
public:
	vector< SoundEffect > sounds;
	int priority;

	SoundSet();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SoundSet& operator = ( const SoundSet &_soundSet ) { Assign( _soundSet ); return *this; }
	SoundSet( const SoundSet &_soundSet ) { Assign( _soundSet ); }
	virtual void Assign( const SoundSet &_soundSet );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SoundSet * pOther = dynamic_cast< const SoundSet * > ( _pResource );
		if ( pOther ) SoundSet::Assign( *pOther );
	}
};

struct SoundSRC : public DbResource
{
	DBRESOURCE_METHODS( SoundSRC );
public:
	string soundFile;
	SyncInfo syncInfo;

	SoundSRC();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SoundSRC& operator = ( const SoundSRC &_soundSRC ) { Assign( _soundSRC ); return *this; }
	SoundSRC( const SoundSRC &_soundSRC ) { Assign( _soundSRC ); }
	virtual void Assign( const SoundSRC &_soundSRC );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SoundSRC * pOther = dynamic_cast< const SoundSRC * > ( _pResource );
		if ( pOther ) SoundSRC::Assign( *pOther );
	}
};

}; // namespace NDb
