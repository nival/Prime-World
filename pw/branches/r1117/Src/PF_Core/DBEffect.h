#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"
#include "../Scene/DBScene.h"

struct IXmlSaver;
// forward declarations for factories
namespace PF_Core
{
	class BasicEffect;
	class ObjectsPool;
}; //namespace PF_Core
namespace NScene
{
	class SceneComponent;
	class HierarchyCreator;
}; //namespace NScene
namespace Render
{
	class Texture;
}; //namespace Render

namespace NDb
{
struct AnimatedPlacementResource;
struct BasicEffectStandalone;
struct ConditionFormula;
struct DBLightningSceneComponent;
struct DBSceneComponent;
struct EffectBase;
struct EffectSelector;
struct Material;
struct PositionRandomizer;
struct Texture;
struct Trace;

enum EEffectAlignment
{
	EFFECTALIGNMENT_NONE = 0,
	EFFECTALIGNMENT_GROUND = 1,
};

const char *EnumToString( const EEffectAlignment value );
const EEffectAlignment StringToEnum_EEffectAlignment( const char* value );

template <>
struct KnownEnum< EEffectAlignment >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EEffectAlignment value ) { return EnumToString( value ); }
	static const EEffectAlignment ToEnum( const char* value ) { return StringToEnum_EEffectAlignment( value ); }
	static const EEffectAlignment ToEnum( const string& value ) { return StringToEnum_EEffectAlignment( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EEffectAttachType
{
	EFFECTATTACHTYPE_GENERAL = 0,
	EFFECTATTACHTYPE_ABOVE = 1,
	EFFECTATTACHTYPE_GROUND = 2,
	EFFECTATTACHTYPE_BODY = 3,
	EFFECTATTACHTYPE_DEATH = 4,
	EFFECTATTACHTYPE_HEAD = 5,
};

const char *EnumToString( const EEffectAttachType value );
const EEffectAttachType StringToEnum_EEffectAttachType( const char* value );

template <>
struct KnownEnum< EEffectAttachType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EEffectAttachType value ) { return EnumToString( value ); }
	static const EEffectAttachType ToEnum( const char* value ) { return StringToEnum_EEffectAttachType( value ); }
	static const EEffectAttachType ToEnum( const string& value ) { return StringToEnum_EEffectAttachType( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum EEffectDeathType
{
	EFFECTDEATHTYPE_MANUAL = 0,
	EFFECTDEATHTYPE_ANIM = 1,
	EFFECTDEATHTYPE_TIME = 2,
};

const char *EnumToString( const EEffectDeathType value );
const EEffectDeathType StringToEnum_EEffectDeathType( const char* value );

template <>
struct KnownEnum< EEffectDeathType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEffectDeathType value ) { return EnumToString( value ); }
	static const EEffectDeathType ToEnum( const char* value ) { return StringToEnum_EEffectDeathType( value ); }
	static const EEffectDeathType ToEnum( const string& value ) { return StringToEnum_EEffectDeathType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EEffectEvent
{
	EFFECTEVENT_ATTACK = 0,
	EFFECTEVENT_DEATH = 1,
	EFFECTEVENT_STOP = 2,
};

const char *EnumToString( const EEffectEvent value );
const EEffectEvent StringToEnum_EEffectEvent( const char* value );

template <>
struct KnownEnum< EEffectEvent >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEffectEvent value ) { return EnumToString( value ); }
	static const EEffectEvent ToEnum( const char* value ) { return StringToEnum_EEffectEvent( value ); }
	static const EEffectEvent ToEnum( const string& value ) { return StringToEnum_EEffectEvent( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EEffectGenPolicy
{
	EFFECTGENPOLICY_START = 0,
	EFFECTGENPOLICY_DEATH = 1,
	EFFECTGENPOLICY_REGULAR = 2,
};

const char *EnumToString( const EEffectGenPolicy value );
const EEffectGenPolicy StringToEnum_EEffectGenPolicy( const char* value );

template <>
struct KnownEnum< EEffectGenPolicy >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEffectGenPolicy value ) { return EnumToString( value ); }
	static const EEffectGenPolicy ToEnum( const char* value ) { return StringToEnum_EEffectGenPolicy( value ); }
	static const EEffectGenPolicy ToEnum( const string& value ) { return StringToEnum_EEffectGenPolicy( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EEffectGroupFlags
{
	EFFECTGROUPFLAGS_NONE = 0,
	EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION = 1048576,
	EFFECTGROUPFLAGS_IGNOREINVISIBILITY = 2097152,
};

const char *EnumToString( const EEffectGroupFlags value );
const EEffectGroupFlags StringToEnum_EEffectGroupFlags( const char* value );

template <>
struct KnownEnum< EEffectGroupFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEffectGroupFlags value ) { return EnumToString( value ); }
	static const EEffectGroupFlags ToEnum( const char* value ) { return StringToEnum_EEffectGroupFlags( value ); }
	static const EEffectGroupFlags ToEnum( const string& value ) { return StringToEnum_EEffectGroupFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EEffects
{
	EFFECTS_EMPTY = 0,
	EFFECTS_LEVELUP = 1,
	EFFECTS_CLICKONTERRAIN = 2,
	EFFECTS_ONDAMAGEFRAGTEAMA = 3,
	EFFECTS_ONDAMAGEFRAGTEAMB = 4,
	EFFECTS_ONBUILDINGDESTRUCTTEAMA = 5,
	EFFECTS_ONBUILDINGDESTRUCTTEAMB = 6,
	EFFECTS_CONTROLLEDHEROAURA = 7,
	EFFECTS_SELECTIONAURASELF = 8,
	EFFECTS_SELECTIONAURAALLY = 9,
	EFFECTS_SELECTIONAURAHOSTILE = 10,
	EFFECTS_PRESELECTIONAURASELF = 11,
	EFFECTS_PRESELECTIONAURAALLY = 12,
	EFFECTS_PRESELECTIONAURAHOSTILE = 13,
	EFFECTS_SELECTIONPICKSELF = 14,
	EFFECTS_SELECTIONPICKALLY = 15,
	EFFECTS_SELECTIONPICKHOSTILE = 16,
	EFFECTS_SELECTIONBUILDINGPICKSELF = 17,
	EFFECTS_SELECTIONBUILDINGPICKALLY = 18,
	EFFECTS_SELECTIONBUILDINGPICKHOSTILE = 19,
	EFFECTS_MARKERALLY = 20,
	EFFECTS_MARKERHOSTILE = 21,
	EFFECTS_MARKERCHAT = 22,
	EFFECTS_DEFAULTEFFECT = 23,
	EFFECTS_GLOWEFFECTA = 24,
	EFFECTS_GLOWEFFECTB = 25,
	EFFECTS_ROTATEANIMATIONEFFECT = 26,
	EFFECTS_MINIGAMESCROLLGIVEN = 27,
	EFFECTS_TOWERATTACKEFFECTALLY = 28,
	EFFECTS_TOWERATTACKEFFECTENEMY = 29,
};

const char *EnumToString( const EEffects value );
const EEffects StringToEnum_EEffects( const char* value );

template <>
struct KnownEnum< EEffects >
{
	enum { isKnown = 1 };
	enum { sizeOf = 30 };
	static const char *ToString( const EEffects value ) { return EnumToString( value ); }
	static const EEffects ToEnum( const char* value ) { return StringToEnum_EEffects( value ); }
	static const EEffects ToEnum( const string& value ) { return StringToEnum_EEffects( value.c_str() ); }
	static const int SizeOf() { return 30; }
};

enum EEffectSelectionPolicy
{
	EFFECTSELECTIONPOLICY_RANDOM = 0,
	EFFECTSELECTIONPOLICY_SEQUENTIAL = 1,
};

const char *EnumToString( const EEffectSelectionPolicy value );
const EEffectSelectionPolicy StringToEnum_EEffectSelectionPolicy( const char* value );

template <>
struct KnownEnum< EEffectSelectionPolicy >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EEffectSelectionPolicy value ) { return EnumToString( value ); }
	static const EEffectSelectionPolicy ToEnum( const char* value ) { return StringToEnum_EEffectSelectionPolicy( value ); }
	static const EEffectSelectionPolicy ToEnum( const string& value ) { return StringToEnum_EEffectSelectionPolicy( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EnableSCEffectMode
{
	NABLESCEFFECTMODE_COMPONENTID = 0,
	NABLESCEFFECTMODE_EVENTNAME = 1,
};

const char *EnumToString( const EnableSCEffectMode value );
const EnableSCEffectMode StringToEnum_EnableSCEffectMode( const char* value );

template <>
struct KnownEnum< EnableSCEffectMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EnableSCEffectMode value ) { return EnumToString( value ); }
	static const EnableSCEffectMode ToEnum( const char* value ) { return StringToEnum_EnableSCEffectMode( value ); }
	static const EnableSCEffectMode ToEnum( const string& value ) { return StringToEnum_EnableSCEffectMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct EffectEventAction
{
public:
	string animation;
	string marker;

	EffectEventAction();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SpringParamDynamics
{
public:
	float speed;
	float maxValue;

	SpringParamDynamics();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TraceInfo
{
public:
	string nodeName;
	string locatorName;
	Ptr< Trace > traces;

	TraceInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct EffectBase : public DbResource
{
	DBRESOURCE_METHODS( EffectBase );
protected:
	mutable DBResourceStateManager stateManager;
	virtual DBResourceStateManager* GetStatesManager() const { return &stateManager; }
public:
	enum { typeId = 0xA06253C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EffectBase::typeId; }
	EEffectDeathType deathType;
	float lifeTime;
	Ptr< ConditionFormula > enableCondition;

	EffectBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectBase& operator = ( const EffectBase &_effectBase ) { Assign( _effectBase ); return *this; }
	EffectBase( const EffectBase &_effectBase ) { Assign( _effectBase ); }
	virtual void Assign( const EffectBase &_effectBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectBase * pOther = dynamic_cast< const EffectBase * > ( _pResource );
		if ( pOther ) EffectBase::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct BasicEffect : public EffectBase
{
	DBRESOURCE_METHODS( BasicEffect );
public:
	enum { typeId = 0xA06253C1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicEffect::typeId; }
	Ptr< DBSceneComponent > component;
	float fadeIn;
	float fadeOut;

	BasicEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicEffect& operator = ( const BasicEffect &_basicEffect ) { Assign( _basicEffect ); return *this; }
	BasicEffect( const BasicEffect &_basicEffect ) { Assign( _basicEffect ); }
	virtual void Assign( const BasicEffect &_basicEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicEffect * pOther = dynamic_cast< const BasicEffect * > ( _pResource );
		if ( pOther ) BasicEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct BasicEffectStandalone : public BasicEffect
{
	DBRESOURCE_METHODS( BasicEffectStandalone );
public:
	enum { typeId = 0xA06253C2 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicEffectStandalone::typeId; }
	bool visibilityLimited;
	float visibleTime;
	bool isVisibleUnderWarfog;
	string parentType;
	EStandAloneEffectFlags parentFlags;

	BasicEffectStandalone();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicEffectStandalone& operator = ( const BasicEffectStandalone &_basicEffectStandalone ) { Assign( _basicEffectStandalone ); return *this; }
	BasicEffectStandalone( const BasicEffectStandalone &_basicEffectStandalone ) { Assign( _basicEffectStandalone ); }
	virtual void Assign( const BasicEffectStandalone &_basicEffectStandalone );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicEffectStandalone * pOther = dynamic_cast< const BasicEffectStandalone * > ( _pResource );
		if ( pOther ) BasicEffectStandalone::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct CameraShakeSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( CameraShakeSceneComponent );
public:
	enum { typeId = 0xA0698AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)CameraShakeSceneComponent::typeId; }
	Ptr< AnimatedPlacementResource > displacement;
	float range;

	CameraShakeSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CameraShakeSceneComponent& operator = ( const CameraShakeSceneComponent &_cameraShakeSceneComponent ) { Assign( _cameraShakeSceneComponent ); return *this; }
	CameraShakeSceneComponent( const CameraShakeSceneComponent &_cameraShakeSceneComponent ) { Assign( _cameraShakeSceneComponent ); }
	virtual void Assign( const CameraShakeSceneComponent &_cameraShakeSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CameraShakeSceneComponent * pOther = dynamic_cast< const CameraShakeSceneComponent * > ( _pResource );
		if ( pOther ) CameraShakeSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct ChangeMaterialEffect : public EffectBase
{
	DBRESOURCE_METHODS( ChangeMaterialEffect );
public:
	enum { typeId = 0x9DAA1380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ChangeMaterialEffect::typeId; }
	float fadeInTime;
	float fadeOutTime;
	vector< Ptr< Material > > materials;

	ChangeMaterialEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ChangeMaterialEffect& operator = ( const ChangeMaterialEffect &_changeMaterialEffect ) { Assign( _changeMaterialEffect ); return *this; }
	ChangeMaterialEffect( const ChangeMaterialEffect &_changeMaterialEffect ) { Assign( _changeMaterialEffect ); }
	virtual void Assign( const ChangeMaterialEffect &_changeMaterialEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ChangeMaterialEffect * pOther = dynamic_cast< const ChangeMaterialEffect * > ( _pResource );
		if ( pOther ) ChangeMaterialEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct PositionRandomizer : public DbResource
{
	DBRESOURCE_METHODS( PositionRandomizer );
public:

	PositionRandomizer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PositionRandomizer& operator = ( const PositionRandomizer &_positionRandomizer ) { Assign( _positionRandomizer ); return *this; }
	PositionRandomizer( const PositionRandomizer &_positionRandomizer ) { Assign( _positionRandomizer ); }
	virtual void Assign( const PositionRandomizer &_positionRandomizer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PositionRandomizer * pOther = dynamic_cast< const PositionRandomizer * > ( _pResource );
		if ( pOther ) PositionRandomizer::Assign( *pOther );
	}
};

struct BasicEffectAttached : public BasicEffect
{
	DBRESOURCE_METHODS( BasicEffectAttached );
public:
	enum { typeId = 0xA06253C3 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicEffectAttached::typeId; }
	string attachType;
	EAttachFlags attachFlags;
	EEffectGroupFlags groupFlags;

	BasicEffectAttached();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicEffectAttached& operator = ( const BasicEffectAttached &_basicEffectAttached ) { Assign( _basicEffectAttached ); return *this; }
	BasicEffectAttached( const BasicEffectAttached &_basicEffectAttached ) { Assign( _basicEffectAttached ); }
	virtual void Assign( const BasicEffectAttached &_basicEffectAttached );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicEffectAttached * pOther = dynamic_cast< const BasicEffectAttached * > ( _pResource );
		if ( pOther ) BasicEffectAttached::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct ControlledStatusEffect : public BasicEffectAttached
{
	DBRESOURCE_METHODS( ControlledStatusEffect );
public:
	enum { typeId = 0xA06CEBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ControlledStatusEffect::typeId; }
	vector< EffectEventAction > eventActions;
	Ptr< BasicEffectStandalone > onDeathEffect;

	ControlledStatusEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ControlledStatusEffect& operator = ( const ControlledStatusEffect &_controlledStatusEffect ) { Assign( _controlledStatusEffect ); return *this; }
	ControlledStatusEffect( const ControlledStatusEffect &_controlledStatusEffect ) { Assign( _controlledStatusEffect ); }
	virtual void Assign( const ControlledStatusEffect &_controlledStatusEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ControlledStatusEffect * pOther = dynamic_cast< const ControlledStatusEffect * > ( _pResource );
		if ( pOther ) ControlledStatusEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct EffectGenSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( EffectGenSceneComponent );
public:
	enum { typeId = 0x9E6433C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EffectGenSceneComponent::typeId; }
	Ptr< EffectSelector > effect;
	EEffectGenPolicy generationPolicy;
	float minPeriod;
	float maxPeriod;
	Ptr< PositionRandomizer > posRandomizer;
	bool randomizeDirection;
	EEffectAlignment alignment;
	float offset;

	EffectGenSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectGenSceneComponent& operator = ( const EffectGenSceneComponent &_effectGenSceneComponent ) { Assign( _effectGenSceneComponent ); return *this; }
	EffectGenSceneComponent( const EffectGenSceneComponent &_effectGenSceneComponent ) { Assign( _effectGenSceneComponent ); }
	virtual void Assign( const EffectGenSceneComponent &_effectGenSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectGenSceneComponent * pOther = dynamic_cast< const EffectGenSceneComponent * > ( _pResource );
		if ( pOther ) EffectGenSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct EffectList : public EffectBase
{
	DBRESOURCE_METHODS( EffectList );
public:
	enum { typeId = 0x2B823BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EffectList::typeId; }
	vector< Ptr< EffectBase > > effects;

	EffectList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectList& operator = ( const EffectList &_effectList ) { Assign( _effectList ); return *this; }
	EffectList( const EffectList &_effectList ) { Assign( _effectList ); }
	virtual void Assign( const EffectList &_effectList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectList * pOther = dynamic_cast< const EffectList * > ( _pResource );
		if ( pOther ) EffectList::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct EffectSelector : public DbResource
{
	DBRESOURCE_METHODS( EffectSelector );
public:
	vector< Ptr< BasicEffectStandalone > > effects;
	EEffectSelectionPolicy selectionPolicy;

	EffectSelector();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectSelector& operator = ( const EffectSelector &_effectSelector ) { Assign( _effectSelector ); return *this; }
	EffectSelector( const EffectSelector &_effectSelector ) { Assign( _effectSelector ); }
	virtual void Assign( const EffectSelector &_effectSelector );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectSelector * pOther = dynamic_cast< const EffectSelector * > ( _pResource );
		if ( pOther ) EffectSelector::Assign( *pOther );
	}
};

struct EffectsPool : public DbResource
{
	DBRESOURCE_METHODS( EffectsPool );
public:
	vector< Ptr< EffectBase > > effectsList;

	EffectsPool();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectsPool& operator = ( const EffectsPool &_effectsPool ) { Assign( _effectsPool ); return *this; }
	EffectsPool( const EffectsPool &_effectsPool ) { Assign( _effectsPool ); }
	virtual void Assign( const EffectsPool &_effectsPool );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectsPool * pOther = dynamic_cast< const EffectsPool * > ( _pResource );
		if ( pOther ) EffectsPool::Assign( *pOther );
	}
};

struct EnableSCEffect : public EffectBase
{
	DBRESOURCE_METHODS( EnableSCEffect );
public:
	enum { typeId = 0xA0626B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EnableSCEffect::typeId; }
	string nameStart;
	string nameStop;
	EnableSCEffectMode mode;
	bool enable;

	EnableSCEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EnableSCEffect& operator = ( const EnableSCEffect &_enableSCEffect ) { Assign( _enableSCEffect ); return *this; }
	EnableSCEffect( const EnableSCEffect &_enableSCEffect ) { Assign( _enableSCEffect ); }
	virtual void Assign( const EnableSCEffect &_enableSCEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EnableSCEffect * pOther = dynamic_cast< const EnableSCEffect * > ( _pResource );
		if ( pOther ) EnableSCEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct GhostEffect : public EffectBase
{
	DBRESOURCE_METHODS( GhostEffect );
public:
	enum { typeId = 0xA06B93C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GhostEffect::typeId; }

	GhostEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GhostEffect& operator = ( const GhostEffect &_ghostEffect ) { Assign( _ghostEffect ); return *this; }
	GhostEffect( const GhostEffect &_ghostEffect ) { Assign( _ghostEffect ); }
	virtual void Assign( const GhostEffect &_ghostEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GhostEffect * pOther = dynamic_cast< const GhostEffect * > ( _pResource );
		if ( pOther ) GhostEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct LightningEffect : public EffectBase
{
	DBRESOURCE_METHODS( LightningEffect );
public:
	enum { typeId = 0xA0629380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)LightningEffect::typeId; }
	Ptr< DBLightningSceneComponent > component;
	bool controlledVisibility;

	LightningEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LightningEffect& operator = ( const LightningEffect &_lightningEffect ) { Assign( _lightningEffect ); return *this; }
	LightningEffect( const LightningEffect &_lightningEffect ) { Assign( _lightningEffect ); }
	virtual void Assign( const LightningEffect &_lightningEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LightningEffect * pOther = dynamic_cast< const LightningEffect * > ( _pResource );
		if ( pOther ) LightningEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct ParticleSceneComponentWithEffect : public DBParticleSceneComponent
{
	DBRESOURCE_METHODS( ParticleSceneComponentWithEffect );
public:
	enum { typeId = 0xA065DB40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ParticleSceneComponentWithEffect::typeId; }
	Ptr< BasicEffectStandalone > effect;

	ParticleSceneComponentWithEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ParticleSceneComponentWithEffect& operator = ( const ParticleSceneComponentWithEffect &_particleSceneComponentWithEffect ) { Assign( _particleSceneComponentWithEffect ); return *this; }
	ParticleSceneComponentWithEffect( const ParticleSceneComponentWithEffect &_particleSceneComponentWithEffect ) { Assign( _particleSceneComponentWithEffect ); }
	virtual void Assign( const ParticleSceneComponentWithEffect &_particleSceneComponentWithEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ParticleSceneComponentWithEffect * pOther = dynamic_cast< const ParticleSceneComponentWithEffect * > ( _pResource );
		if ( pOther ) ParticleSceneComponentWithEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct CircleRandomizer : public PositionRandomizer
{
	DBRESOURCE_METHODS( CircleRandomizer );
public:
	float radius;

	CircleRandomizer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CircleRandomizer& operator = ( const CircleRandomizer &_circleRandomizer ) { Assign( _circleRandomizer ); return *this; }
	CircleRandomizer( const CircleRandomizer &_circleRandomizer ) { Assign( _circleRandomizer ); }
	virtual void Assign( const CircleRandomizer &_circleRandomizer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CircleRandomizer * pOther = dynamic_cast< const CircleRandomizer * > ( _pResource );
		if ( pOther ) CircleRandomizer::Assign( *pOther );
	}
};

struct PostFXParams : public DbResource
{
	DBRESOURCE_METHODS( PostFXParams );
public:
	enum { typeId = 0xA06C5B40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PostFXParams::typeId; }
	vector< FullScreenFXParams > fullScreenFXParams;
	float mipMapLodBias;

	PostFXParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PostFXParams& operator = ( const PostFXParams &_postFXParams ) { Assign( _postFXParams ); return *this; }
	PostFXParams( const PostFXParams &_postFXParams ) { Assign( _postFXParams ); }
	virtual void Assign( const PostFXParams &_postFXParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PostFXParams * pOther = dynamic_cast< const PostFXParams * > ( _pResource );
		if ( pOther ) PostFXParams::Assign( *pOther );
	}
};

struct RectangleRandomizer : public PositionRandomizer
{
	DBRESOURCE_METHODS( RectangleRandomizer );
public:
	CVec2 min;
	CVec2 max;

	RectangleRandomizer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RectangleRandomizer& operator = ( const RectangleRandomizer &_rectangleRandomizer ) { Assign( _rectangleRandomizer ); return *this; }
	RectangleRandomizer( const RectangleRandomizer &_rectangleRandomizer ) { Assign( _rectangleRandomizer ); }
	virtual void Assign( const RectangleRandomizer &_rectangleRandomizer );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RectangleRandomizer * pOther = dynamic_cast< const RectangleRandomizer * > ( _pResource );
		if ( pOther ) RectangleRandomizer::Assign( *pOther );
	}
};

struct ScaleColorEffect : public EffectBase
{
	DBRESOURCE_METHODS( ScaleColorEffect );
public:
	enum { typeId = 0xA06253C4 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScaleColorEffect::typeId; }
	float scale;
	Render::HDRColor colorMul;
	Render::HDRColor colorAdd;
	BlendMode blendMode;
	Animated<float, NDb::AnimatedAlgorithms::Linear> scaleIn;
	Animated<float, NDb::AnimatedAlgorithms::Linear> scaleOut;
	float fadeInTime;
	float fadeOutTime;
	bool fullRecolor;

	ScaleColorEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScaleColorEffect& operator = ( const ScaleColorEffect &_scaleColorEffect ) { Assign( _scaleColorEffect ); return *this; }
	ScaleColorEffect( const ScaleColorEffect &_scaleColorEffect ) { Assign( _scaleColorEffect ); }
	virtual void Assign( const ScaleColorEffect &_scaleColorEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScaleColorEffect * pOther = dynamic_cast< const ScaleColorEffect * > ( _pResource );
		if ( pOther ) ScaleColorEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct SpringSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( SpringSceneComponent );
public:
	enum { typeId = 0xA071EBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SpringSceneComponent::typeId; }
	SpringParamDynamics posDynamics;
	SpringParamDynamics rotDynamics;
	SpringParamDynamics scaleDynamics;

	SpringSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SpringSceneComponent& operator = ( const SpringSceneComponent &_springSceneComponent ) { Assign( _springSceneComponent ); return *this; }
	SpringSceneComponent( const SpringSceneComponent &_springSceneComponent ) { Assign( _springSceneComponent ); }
	virtual void Assign( const SpringSceneComponent &_springSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SpringSceneComponent * pOther = dynamic_cast< const SpringSceneComponent * > ( _pResource );
		if ( pOther ) SpringSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct TextureAnimated : public Texture
{
	DBRESOURCE_METHODS( TextureAnimated );
public:
	int animCount;
	float animSpeed;

	TextureAnimated();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TextureAnimated& operator = ( const TextureAnimated &_textureAnimated ) { Assign( _textureAnimated ); return *this; }
	TextureAnimated( const TextureAnimated &_textureAnimated ) { Assign( _textureAnimated ); }
	virtual void Assign( const TextureAnimated &_textureAnimated );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TextureAnimated * pOther = dynamic_cast< const TextureAnimated * > ( _pResource );
		if ( pOther ) TextureAnimated::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<Render::Texture> Load() const;
	virtual CObj<Render::Texture> LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct TextureRecolorable : public TextureBase
{
	DBRESOURCE_METHODS( TextureRecolorable );
public:
	Ptr< Texture > main;
	Ptr< Texture > mask;
	Render::HDRColor baseRGB;

	TextureRecolorable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TextureRecolorable& operator = ( const TextureRecolorable &_textureRecolorable ) { Assign( _textureRecolorable ); return *this; }
	TextureRecolorable( const TextureRecolorable &_textureRecolorable ) { Assign( _textureRecolorable ); }
	virtual void Assign( const TextureRecolorable &_textureRecolorable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TextureRecolorable * pOther = dynamic_cast< const TextureRecolorable * > ( _pResource );
		if ( pOther ) TextureRecolorable::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<Render::Texture> Load() const;
	virtual CObj<Render::Texture> LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct Trace : public DbResource
{
	DBRESOURCE_METHODS( Trace );
public:
	Ptr< EffectSelector > waterTrace;
	vector< Ptr< EffectSelector > > terrainTrace;

	Trace();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Trace& operator = ( const Trace &_trace ) { Assign( _trace ); return *this; }
	Trace( const Trace &_trace ) { Assign( _trace ); }
	virtual void Assign( const Trace &_trace );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Trace * pOther = dynamic_cast< const Trace * > ( _pResource );
		if ( pOther ) Trace::Assign( *pOther );
	}
};

struct TraceGenSceneComponent : public DBSceneComponent
{
	DBRESOURCE_METHODS( TraceGenSceneComponent );
public:
	enum { typeId = 0xA065B300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TraceGenSceneComponent::typeId; }
	Ptr< Trace > defaultTraces;
	string defaultLocatorName;
	vector< TraceInfo > traceByAnim;

	TraceGenSceneComponent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TraceGenSceneComponent& operator = ( const TraceGenSceneComponent &_traceGenSceneComponent ) { Assign( _traceGenSceneComponent ); return *this; }
	TraceGenSceneComponent( const TraceGenSceneComponent &_traceGenSceneComponent ) { Assign( _traceGenSceneComponent ); }
	virtual void Assign( const TraceGenSceneComponent &_traceGenSceneComponent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TraceGenSceneComponent * pOther = dynamic_cast< const TraceGenSceneComponent * > ( _pResource );
		if ( pOther ) TraceGenSceneComponent::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<NScene::SceneComponent> Create( NScene::HierarchyCreator &creator, const AttachedSceneComponent* pAttached, const Placement& transform ) const;
#endif // #ifndef VISUAL_CUTTED
};

}; // namespace NDb
