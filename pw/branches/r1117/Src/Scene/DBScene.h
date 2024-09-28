#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Render/DBRenderResources.h"
#include "../Scene/DBSceneBase.h"
#include "../Sound/DBSound.h"

struct IXmlSaver;
// forward declarations for factories
namespace NScene
{
	class SceneComponent;
	class HierarchyCreator;
}; //namespace NScene

namespace NDb
{
struct AnimGraphCreator;
struct CollisionGeometry;
struct DBAnimKey;
struct DBSceneComponent;
struct DBWaterInfo;
struct EnableDisableSCEvents;
struct EnableDisableSkinEvents;
struct LightningMaterial;
struct LocatorList;
struct Material;
struct ParticleFXMaterial;
struct SceneObjectTrack;
struct SceneObjectTracks;
struct SCEvent;
struct Texture;
struct TimeController;
struct TraceMaterial;

enum EAnimEventType
{
	ANIMEVENTTYPE_NODEENTER = 0,
	ANIMEVENTTYPE_NODELEAVE = 1,
	ANIMEVENTTYPE_NODEPARAM = 2,
	ANIMEVENTTYPE_MARKER = 3,
};

const char *EnumToString( const EAnimEventType value );
const EAnimEventType StringToEnum_EAnimEventType( const char* value );

template <>
struct KnownEnum< EAnimEventType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EAnimEventType value ) { return EnumToString( value ); }
	static const EAnimEventType ToEnum( const char* value ) { return StringToEnum_EAnimEventType( value ); }
	static const EAnimEventType ToEnum( const string& value ) { return StringToEnum_EAnimEventType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EAttachFlags
{
	ATTACHFLAGS_NONE = 0,
	ATTACHFLAGS_USEPARENTSCALE = 1,
	ATTACHFLAGS_USEPARENTROTATION = 2,
	ATTACHFLAGS_USEPARENTTIME = 4,
	ATTACHFLAGS_USEAGSPEEDCOEFF = 8,
	ATTACHFLAGS_STAYINWORLD = 16,
	ATTACHFLAGS_CANCELOFFSETSCALING = 32,
};

const char *EnumToString( const EAttachFlags value );
const EAttachFlags StringToEnum_EAttachFlags( const char* value );

template <>
struct KnownEnum< EAttachFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EAttachFlags value ) { return EnumToString( value ); }
	static const EAttachFlags ToEnum( const char* value ) { return StringToEnum_EAttachFlags( value ); }
	static const EAttachFlags ToEnum( const string& value ) { return StringToEnum_EAttachFlags( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EEnableDisableOrder
{
	ENABLEDISABLEORDER_ENABLETHENDISABLE = 0,
	ENABLEDISABLEORDER_DISABLETHENENABLE = 1,
};

const char *EnumToString( const EEnableDisableOrder value );
const EEnableDisableOrder StringToEnum_EEnableDisableOrder( const char* value );

template <>
struct KnownEnum< EEnableDisableOrder >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EEnableDisableOrder value ) { return EnumToString( value ); }
	static const EEnableDisableOrder ToEnum( const char* value ) { return StringToEnum_EEnableDisableOrder( value ); }
	static const EEnableDisableOrder ToEnum( const string& value ) { return StringToEnum_EEnableDisableOrder( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EGroupFlags
{
	GROUPFLAGS_NONE = 0,
	GROUPFLAGS_RECOLORABLE = 4,
};

const char *EnumToString( const EGroupFlags value );
const EGroupFlags StringToEnum_EGroupFlags( const char* value );

template <>
struct KnownEnum< EGroupFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EGroupFlags value ) { return EnumToString( value ); }
	static const EGroupFlags ToEnum( const char* value ) { return StringToEnum_EGroupFlags( value ); }
	static const EGroupFlags ToEnum( const string& value ) { return StringToEnum_EGroupFlags( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ELightningAnimType
{
	LIGHTNINGANIMTYPE_NONE = 0,
	LIGHTNINGANIMTYPE_SEQUENTIAL = 1,
	LIGHTNINGANIMTYPE_RANDOMIZED = 2,
};

const char *EnumToString( const ELightningAnimType value );
const ELightningAnimType StringToEnum_ELightningAnimType( const char* value );

template <>
struct KnownEnum< ELightningAnimType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ELightningAnimType value ) { return EnumToString( value ); }
	static const ELightningAnimType ToEnum( const char* value ) { return StringToEnum_ELightningAnimType( value ); }
	static const ELightningAnimType ToEnum( const string& value ) { return StringToEnum_ELightningAnimType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EOrientType
{
	ORIENTTYPE_NONE = 0,
	ORIENTTYPE_AXIS = 1,
	ORIENTTYPE_SPEED = 2,
	ORIENTTYPE_PLANE = 3,
};

const char *EnumToString( const EOrientType value );
const EOrientType StringToEnum_EOrientType( const char* value );

template <>
struct KnownEnum< EOrientType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EOrientType value ) { return EnumToString( value ); }
	static const EOrientType ToEnum( const char* value ) { return StringToEnum_EOrientType( value ); }
	static const EOrientType ToEnum( const string& value ) { return StringToEnum_EOrientType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum ESCOrientation
{
	SCORIENTATION_DEFAULT = 0,
	SCORIENTATION_CAMERA = 1,
	SCORIENTATION_CAMERAFIXEDZ = 2,
};

const char *EnumToString( const ESCOrientation value );
const ESCOrientation StringToEnum_ESCOrientation( const char* value );

template <>
struct KnownEnum< ESCOrientation >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ESCOrientation value ) { return EnumToString( value ); }
	static const ESCOrientation ToEnum( const char* value ) { return StringToEnum_ESCOrientation( value ); }
	static const ESCOrientation ToEnum( const string& value ) { return StringToEnum_ESCOrientation( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EStandAloneEffectFlags
{
	STANDALONEEFFECTFLAGS_NONE = 0,
	STANDALONEEFFECTFLAGS_USEPARENTSCALE = 1,
	STANDALONEEFFECTFLAGS_USEPARENTROTATION = 2,
};

const char *EnumToString( const EStandAloneEffectFlags value );
const EStandAloneEffectFlags StringToEnum_EStandAloneEffectFlags( const char* value );

template <>
struct KnownEnum< EStandAloneEffectFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EStandAloneEffectFlags value ) { return EnumToString( value ); }
	static const EStandAloneEffectFlags ToEnum( const char* value ) { return StringToEnum_EStandAloneEffectFlags( value ); }
	static const EStandAloneEffectFlags ToEnum( const string& value ) { return StringToEnum_EStandAloneEffectFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum Sound3DSimultType
{
	SOUND3DSIMULTTYPE_MELEE = 0,
	SOUND3DSIMULTTYPE_RANGE = 1,
	SOUND3DSIMULTTYPE_CREEPDEATH = 2,
	SOUND3DSIMULTTYPE_INFINITE = 3,
};

const char *EnumToString( const Sound3DSimultType value );
const Sound3DSimultType StringToEnum_Sound3DSimultType( const char* value );

template <>
struct KnownEnum< Sound3DSimultType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const Sound3DSimultType value ) { return EnumToString( value ); }
	static const Sound3DSimultType ToEnum( const char* value ) { return StringToEnum_Sound3DSimultType( value ); }
	static const Sound3DSimultType ToEnum( const string& value ) { return StringToEnum_Sound3DSimultType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

struct AnimatedPlacement
{
public:
	Animated<CVec3, NDb::AnimatedAlgorithms::Linear> pos;
	Animated<CQuat, NDb::AnimatedAlgorithms::Linear> rot;
	Animated<CVec3, NDb::AnimatedAlgorithms::Linear> scale;

	AnimatedPlacement();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AttachedSceneComponent
{
public:
	Ptr< DBSceneComponent > component;
	string locatorName;
	Ptr< TimeController > timeController;
	AnimatedPlacement placement;
	EAttachFlags attachFlags;
	string id;
	Ptr< EnableDisableSCEvents > events;

	AttachedSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBLightningFXParams
{
public:
	int animAtlasSize;
	int animFirstFrame;
	int animLastFrame;
	float animSpeed;
	ELightningAnimType animType;
	float opacityDistance1;
	float opacityDistance2;
	Render::HDRColor color;
	float radius;
	float scrollSpeed;
	float tiling;

	DBLightningFXParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SkinPart : public SkinPartBase
{
public:
	Ptr< EnableDisableSkinEvents > events;

	SkinPart();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimatedPlacementResource : public DbResource
{
	DBRESOURCE_METHODS( AnimatedPlacementResource );
public:
	enum { typeId = 0xA071B300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AnimatedPlacementResource::typeId; }
	AnimatedPlacement placement;

	AnimatedPlacementResource();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AnimatedPlacementResource& operator = ( const AnimatedPlacementResource &_animatedPlacementResource ) { Assign( _animatedPlacementResource ); return *this; }
	AnimatedPlacementResource( const AnimatedPlacementResource &_animatedPlacementResource ) { Assign( _animatedPlacementResource ); }
	virtual void Assign( const AnimatedPlacementResource &_animatedPlacementResource );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AnimatedPlacementResource * pOther = dynamic_cast< const AnimatedPlacementResource * > ( _pResource );
		if ( pOther ) AnimatedPlacementResource::Assign( *pOther );
	}
};

struct SCEvent : public DbResource
{
	DBRESOURCE_METHODS( SCEvent );
public:
	enum { typeId = 0x9E6433C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SCEvent::typeId; }

	SCEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SCEvent& operator = ( const SCEvent &_sCEvent ) { Assign( _sCEvent ); return *this; }
	SCEvent( const SCEvent &_sCEvent ) { Assign( _sCEvent ); }
	virtual void Assign( const SCEvent &_sCEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SCEvent * pOther = dynamic_cast< const SCEvent * > ( _pResource );
		if ( pOther ) SCEvent::Assign( *pOther );
	}
};

struct DBSceneResource : public DbResource
{
public:
	vector< AttachedSceneComponent > attached;

	DBSceneResource();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBSceneResource& operator = ( const DBSceneResource &_dBSceneResource ) { Assign( _dBSceneResource ); return *this; }
	DBSceneResource( const DBSceneResource &_dBSceneResource ) { Assign( _dBSceneResource ); }
	virtual void Assign( const DBSceneResource &_dBSceneResource );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBSceneResource * pOther = dynamic_cast< const DBSceneResource * > ( _pResource );
		if ( pOther ) DBSceneResource::Assign( *pOther );
	}
};

struct DBAnimKey : public DbResource
{
	DBRESOURCE_METHODS( DBAnimKey );
public:
	enum { typeId = 0x8D5A3B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBAnimKey::typeId; }
	string name;

	DBAnimKey();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBAnimKey& operator = ( const DBAnimKey &_dBAnimKey ) { Assign( _dBAnimKey ); return *this; }
	DBAnimKey( const DBAnimKey &_dBAnimKey ) { Assign( _dBAnimKey ); }
	virtual void Assign( const DBAnimKey &_dBAnimKey );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBAnimKey * pOther = dynamic_cast< const DBAnimKey * > ( _pResource );
		if ( pOther ) DBAnimKey::Assign( *pOther );
	}
};

struct DBAttachAnimKey : public DBAnimKey
{
	DBRESOURCE_METHODS( DBAttachAnimKey );
public:
	enum { typeId = 0x8D5A3AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBAttachAnimKey::typeId; }
	Ptr< DBSceneComponent > component;

	DBAttachAnimKey();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBAttachAnimKey& operator = ( const DBAttachAnimKey &_dBAttachAnimKey ) { Assign( _dBAttachAnimKey ); return *this; }
	DBAttachAnimKey( const DBAttachAnimKey &_dBAttachAnimKey ) { Assign( _dBAttachAnimKey ); }
	virtual void Assign( const DBAttachAnimKey &_dBAttachAnimKey );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBAttachAnimKey * pOther = dynamic_cast< const DBAttachAnimKey * > ( _pResource );
		if ( pOther ) DBAttachAnimKey::Assign( *pOther );
	}
};

struct DBSceneComponentBase : public DBSceneResource
{
	DBRESOURCE_METHODS( DBSceneComponentBase );
public:
	enum { typeId = 0x9E656380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBSceneComponentBase::typeId; }

	DBSceneComponentBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBSceneComponentBase& operator = ( const DBSceneComponentBase &_dBSceneComponentBase ) { Assign( _dBSceneComponentBase ); return *this; }
	DBSceneComponentBase( const DBSceneComponentBase &_dBSceneComponentBase ) { Assign( _dBSceneComponentBase ); }
	virtual void Assign( const DBSceneComponentBase &_dBSceneComponentBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBSceneComponentBase * pOther = dynamic_cast< const DBSceneComponentBase * > ( _pResource );
		if ( pOther ) DBSceneComponentBase::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBSceneComponent : public DBSceneComponentBase
{
	DBRESOURCE_METHODS( DBSceneComponent );
public:
	enum { typeId = 0x8D5A1240 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBSceneComponent::typeId; }
	Ptr< LocatorList > locatorList;
	ESCOrientation orientation;
	EGroupFlags groupFlags;

	DBSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBSceneComponent& operator = ( const DBSceneComponent &_dBSceneComponent ) { Assign( _dBSceneComponent ); return *this; }
	DBSceneComponent( const DBSceneComponent &_dBSceneComponent ) { Assign( _dBSceneComponent ); }
	virtual void Assign( const DBSceneComponent &_dBSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBSceneComponent * pOther = dynamic_cast< const DBSceneComponent * > ( _pResource );
		if ( pOther ) DBSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBAnimatedSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBAnimatedSceneComponent );
public:
	enum { typeId = 0x8D5A1241 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBAnimatedSceneComponent::typeId; }
	Ptr< AnimGraphCreator > additionalGraph;
	string splitBoneName;
	string srcFileName;
	string skeletonFileName;
	vector< SkinPart > skins;
	vector< Animation > animations;
	vector< FaceFX > faceFXAnims;
	Ptr< AnimGraphCreator > animGraph;
	AABB aabb;
	vector< AnimFaceFXKey > anims;
	vector< int > skinOn;
	vector< Ptr< DBAnimKey > > keys;

	DBAnimatedSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBAnimatedSceneComponent& operator = ( const DBAnimatedSceneComponent &_dBAnimatedSceneComponent ) { Assign( _dBAnimatedSceneComponent ); return *this; }
	DBAnimatedSceneComponent( const DBAnimatedSceneComponent &_dBAnimatedSceneComponent ) { Assign( _dBAnimatedSceneComponent ); }
	virtual void Assign( const DBAnimatedSceneComponent &_dBAnimatedSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBAnimatedSceneComponent * pOther = dynamic_cast< const DBAnimatedSceneComponent * > ( _pResource );
		if ( pOther ) DBAnimatedSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBLightningSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBLightningSceneComponent );
public:
	enum { typeId = 0x3B61E441 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBLightningSceneComponent::typeId; }
	Ptr< LightningMaterial > material;
	string fromLocator;
	string toLocator;
	DBLightningFXParams fxParams;

	DBLightningSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBLightningSceneComponent& operator = ( const DBLightningSceneComponent &_dBLightningSceneComponent ) { Assign( _dBLightningSceneComponent ); return *this; }
	DBLightningSceneComponent( const DBLightningSceneComponent &_dBLightningSceneComponent ) { Assign( _dBLightningSceneComponent ); }
	virtual void Assign( const DBLightningSceneComponent &_dBLightningSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBLightningSceneComponent * pOther = dynamic_cast< const DBLightningSceneComponent * > ( _pResource );
		if ( pOther ) DBLightningSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBSceneObject : public DBSceneResource
{
	DBRESOURCE_METHODS( DBSceneObject );
public:
	Ptr< SceneObjectTracks > tracksList;
	Ptr< CollisionGeometry > collisionGeometry;
	bool ignoreAttachesToNonDefaultLocators;

	DBSceneObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBSceneObject& operator = ( const DBSceneObject &_dBSceneObject ) { Assign( _dBSceneObject ); return *this; }
	DBSceneObject( const DBSceneObject &_dBSceneObject ) { Assign( _dBSceneObject ); }
	virtual void Assign( const DBSceneObject &_dBSceneObject );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBSceneObject * pOther = dynamic_cast< const DBSceneObject * > ( _pResource );
		if ( pOther ) DBSceneObject::Assign( *pOther );
	}
};

struct DBParticleSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBParticleSceneComponent );
public:
	enum { typeId = 0x8D5A1243 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBParticleSceneComponent::typeId; }
	float camoffset;
	EOrientType orient;
	CVec2 pivot;
	bool leaveParticlesWhereStarted;
	float deathFadeOutTime;
	Ptr< ParticleFXMaterial > material;
	vector< UVPair > uvPairs;
	AABB aabb;
	string fxFileName;
	string srcFileName;

	DBParticleSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBParticleSceneComponent& operator = ( const DBParticleSceneComponent &_dBParticleSceneComponent ) { Assign( _dBParticleSceneComponent ); return *this; }
	DBParticleSceneComponent( const DBParticleSceneComponent &_dBParticleSceneComponent ) { Assign( _dBParticleSceneComponent ); }
	virtual void Assign( const DBParticleSceneComponent &_dBParticleSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBParticleSceneComponent * pOther = dynamic_cast< const DBParticleSceneComponent * > ( _pResource );
		if ( pOther ) DBParticleSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBSoundSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBSoundSceneComponent );
public:
	enum { typeId = 0x4D5B9BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBSoundSceneComponent::typeId; }
	DBFMODEventDesc desc;
	float timeInterval;

	DBSoundSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBSoundSceneComponent& operator = ( const DBSoundSceneComponent &_dBSoundSceneComponent ) { Assign( _dBSoundSceneComponent ); return *this; }
	DBSoundSceneComponent( const DBSoundSceneComponent &_dBSoundSceneComponent ) { Assign( _dBSoundSceneComponent ); }
	virtual void Assign( const DBSoundSceneComponent &_dBSoundSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBSoundSceneComponent * pOther = dynamic_cast< const DBSoundSceneComponent * > ( _pResource );
		if ( pOther ) DBSoundSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBStaticSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBStaticSceneComponent );
public:
	enum { typeId = 0x8D5A1242 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBStaticSceneComponent::typeId; }
	string srcFileName;
	string geometryFileName;
	AABB aabb;
	vector< Ptr< Material > > materialsReferences;

	DBStaticSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBStaticSceneComponent& operator = ( const DBStaticSceneComponent &_dBStaticSceneComponent ) { Assign( _dBStaticSceneComponent ); return *this; }
	DBStaticSceneComponent( const DBStaticSceneComponent &_dBStaticSceneComponent ) { Assign( _dBStaticSceneComponent ); }
	virtual void Assign( const DBStaticSceneComponent &_dBStaticSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBStaticSceneComponent * pOther = dynamic_cast< const DBStaticSceneComponent * > ( _pResource );
		if ( pOther ) DBStaticSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBTraceSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( DBTraceSceneComponent );
public:
	enum { typeId = 0x3B6184C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBTraceSceneComponent::typeId; }
	Ptr< TraceMaterial > material;
	string locator1Name;
	string locator2Name;
	float maxLength;
	float speedStart;
	float speedStop;
	Render::HDRColor colorFirst;
	Render::HDRColor colorLast;
	float offsetColor;
	float offsetAlpha;
	float fadeoutSpeed;
	float skewness;

	DBTraceSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBTraceSceneComponent& operator = ( const DBTraceSceneComponent &_dBTraceSceneComponent ) { Assign( _dBTraceSceneComponent ); return *this; }
	DBTraceSceneComponent( const DBTraceSceneComponent &_dBTraceSceneComponent ) { Assign( _dBTraceSceneComponent ); }
	virtual void Assign( const DBTraceSceneComponent &_dBTraceSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBTraceSceneComponent * pOther = dynamic_cast< const DBTraceSceneComponent * > ( _pResource );
		if ( pOther ) DBTraceSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct DBWaterInfo : public DbResource
{
	DBRESOURCE_METHODS( DBWaterInfo );
public:
	enum { typeId = 0x3B622C41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBWaterInfo::typeId; }
	float tiling;
	float shininess;
	float ripples;
	float ripplesHeight;
	float distance;
	float refraction;
	float depth;
	float depthReflect;
	CVec2 speed;
	float causticsTiling;
	float causticsIntensity;
	Ptr< Texture > gradientMap;
	Ptr< Texture > causticsMap;

	DBWaterInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBWaterInfo& operator = ( const DBWaterInfo &_dBWaterInfo ) { Assign( _dBWaterInfo ); return *this; }
	DBWaterInfo( const DBWaterInfo &_dBWaterInfo ) { Assign( _dBWaterInfo ); }
	virtual void Assign( const DBWaterInfo &_dBWaterInfo );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBWaterInfo * pOther = dynamic_cast< const DBWaterInfo * > ( _pResource );
		if ( pOther ) DBWaterInfo::Assign( *pOther );
	}
};

struct DBWaterSceneComponent : public DBStaticSceneComponent
{
	DBRESOURCE_METHODS( DBWaterSceneComponent );
public:
	enum { typeId = 0x3B622C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DBWaterSceneComponent::typeId; }
	Ptr< DBWaterInfo > water;
	float waterLevel;

	DBWaterSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBWaterSceneComponent& operator = ( const DBWaterSceneComponent &_dBWaterSceneComponent ) { Assign( _dBWaterSceneComponent ); return *this; }
	DBWaterSceneComponent( const DBWaterSceneComponent &_dBWaterSceneComponent ) { Assign( _dBWaterSceneComponent ); }
	virtual void Assign( const DBWaterSceneComponent &_dBWaterSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBWaterSceneComponent * pOther = dynamic_cast< const DBWaterSceneComponent * > ( _pResource );
		if ( pOther ) DBWaterSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct EnableDisableSCEvents : public DbResource
{
	DBRESOURCE_METHODS( EnableDisableSCEvents );
public:
	enum { typeId = 0x9E64AA80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EnableDisableSCEvents::typeId; }
	EEnableDisableOrder order;
	bool restartComponent;
	vector< Ptr< SCEvent > > enableEvents;
	vector< Ptr< SCEvent > > disableEvents;

	EnableDisableSCEvents();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EnableDisableSCEvents& operator = ( const EnableDisableSCEvents &_enableDisableSCEvents ) { Assign( _enableDisableSCEvents ); return *this; }
	EnableDisableSCEvents( const EnableDisableSCEvents &_enableDisableSCEvents ) { Assign( _enableDisableSCEvents ); }
	virtual void Assign( const EnableDisableSCEvents &_enableDisableSCEvents );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EnableDisableSCEvents * pOther = dynamic_cast< const EnableDisableSCEvents * > ( _pResource );
		if ( pOther ) EnableDisableSCEvents::Assign( *pOther );
	}
};

struct EnableDisableSkinEvents : public DbResource
{
	DBRESOURCE_METHODS( EnableDisableSkinEvents );
public:
	enum { typeId = 0x9D759480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EnableDisableSkinEvents::typeId; }
	EEnableDisableOrder order;
	vector< Ptr< SCEvent > > enableEvents;
	vector< Ptr< SCEvent > > disableEvents;

	EnableDisableSkinEvents();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EnableDisableSkinEvents& operator = ( const EnableDisableSkinEvents &_enableDisableSkinEvents ) { Assign( _enableDisableSkinEvents ); return *this; }
	EnableDisableSkinEvents( const EnableDisableSkinEvents &_enableDisableSkinEvents ) { Assign( _enableDisableSkinEvents ); }
	virtual void Assign( const EnableDisableSkinEvents &_enableDisableSkinEvents );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EnableDisableSkinEvents * pOther = dynamic_cast< const EnableDisableSkinEvents * > ( _pResource );
		if ( pOther ) EnableDisableSkinEvents::Assign( *pOther );
	}
};

struct GroundHitSCEvent : public SCEvent
{
	DBRESOURCE_METHODS( GroundHitSCEvent );
public:
	enum { typeId = 0x9E6433C3 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GroundHitSCEvent::typeId; }
	float heightAboveGround;

	GroundHitSCEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GroundHitSCEvent& operator = ( const GroundHitSCEvent &_groundHitSCEvent ) { Assign( _groundHitSCEvent ); return *this; }
	GroundHitSCEvent( const GroundHitSCEvent &_groundHitSCEvent ) { Assign( _groundHitSCEvent ); }
	virtual void Assign( const GroundHitSCEvent &_groundHitSCEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GroundHitSCEvent * pOther = dynamic_cast< const GroundHitSCEvent * > ( _pResource );
		if ( pOther ) GroundHitSCEvent::Assign( *pOther );
	}
};

struct LocatorList : public DbResource
{
	DBRESOURCE_METHODS( LocatorList );
public:
	enum { typeId = 0x146AAB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)LocatorList::typeId; }
	vector< Locator > locators;

	LocatorList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LocatorList& operator = ( const LocatorList &_locatorList ) { Assign( _locatorList ); return *this; }
	LocatorList( const LocatorList &_locatorList ) { Assign( _locatorList ); }
	virtual void Assign( const LocatorList &_locatorList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LocatorList * pOther = dynamic_cast< const LocatorList * > ( _pResource );
		if ( pOther ) LocatorList::Assign( *pOther );
	}
};

struct NamedSCEvent : public SCEvent
{
	DBRESOURCE_METHODS( NamedSCEvent );
public:
	enum { typeId = 0xA06A4B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NamedSCEvent::typeId; }
	string name;

	NamedSCEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NamedSCEvent& operator = ( const NamedSCEvent &_namedSCEvent ) { Assign( _namedSCEvent ); return *this; }
	NamedSCEvent( const NamedSCEvent &_namedSCEvent ) { Assign( _namedSCEvent ); }
	virtual void Assign( const NamedSCEvent &_namedSCEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NamedSCEvent * pOther = dynamic_cast< const NamedSCEvent * > ( _pResource );
		if ( pOther ) NamedSCEvent::Assign( *pOther );
	}
};

struct SceneObjectTrack : public DbResource
{
	DBRESOURCE_METHODS( SceneObjectTrack );
public:
	AnimatedPlacement placement;
	Animated<float, NDb::AnimatedAlgorithms::Linear> opacity;
	string name;

	SceneObjectTrack();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SceneObjectTrack& operator = ( const SceneObjectTrack &_sceneObjectTrack ) { Assign( _sceneObjectTrack ); return *this; }
	SceneObjectTrack( const SceneObjectTrack &_sceneObjectTrack ) { Assign( _sceneObjectTrack ); }
	virtual void Assign( const SceneObjectTrack &_sceneObjectTrack );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SceneObjectTrack * pOther = dynamic_cast< const SceneObjectTrack * > ( _pResource );
		if ( pOther ) SceneObjectTrack::Assign( *pOther );
	}
};

struct SceneObjectTracks : public DbResource
{
	DBRESOURCE_METHODS( SceneObjectTracks );
public:
	vector< Ptr< SceneObjectTrack > > animatedTracks;

	SceneObjectTracks();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SceneObjectTracks& operator = ( const SceneObjectTracks &_sceneObjectTracks ) { Assign( _sceneObjectTracks ); return *this; }
	SceneObjectTracks( const SceneObjectTracks &_sceneObjectTracks ) { Assign( _sceneObjectTracks ); }
	virtual void Assign( const SceneObjectTracks &_sceneObjectTracks );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SceneObjectTracks * pOther = dynamic_cast< const SceneObjectTracks * > ( _pResource );
		if ( pOther ) SceneObjectTracks::Assign( *pOther );
	}
};

struct AnimationSCEvent : public SCEvent
{
	DBRESOURCE_METHODS( AnimationSCEvent );
public:
	enum { typeId = 0x9E6433C2 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AnimationSCEvent::typeId; }
	EAnimEventType type;
	string name;
	float animParam;
	float probability;

	AnimationSCEvent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AnimationSCEvent& operator = ( const AnimationSCEvent &_animationSCEvent ) { Assign( _animationSCEvent ); return *this; }
	AnimationSCEvent( const AnimationSCEvent &_animationSCEvent ) { Assign( _animationSCEvent ); }
	virtual void Assign( const AnimationSCEvent &_animationSCEvent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AnimationSCEvent * pOther = dynamic_cast< const AnimationSCEvent * > ( _pResource );
		if ( pOther ) AnimationSCEvent::Assign( *pOther );
	}
};

struct TimeController : public DbResource
{
	DBRESOURCE_METHODS( TimeController );
public:
	enum { typeId = 0x9E647A80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TimeController::typeId; }
	float speed;
	float startDelay;
	float firstCycleOffset;
	float firstCycleOffsetDelta;
	float cycleLength;
	int cycleCount;
	float fadein;
	float fadeout;

	TimeController();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TimeController& operator = ( const TimeController &_timeController ) { Assign( _timeController ); return *this; }
	TimeController( const TimeController &_timeController ) { Assign( _timeController ); }
	virtual void Assign( const TimeController &_timeController );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TimeController * pOther = dynamic_cast< const TimeController * > ( _pResource );
		if ( pOther ) TimeController::Assign( *pOther );
	}
};

}; // namespace NDb
