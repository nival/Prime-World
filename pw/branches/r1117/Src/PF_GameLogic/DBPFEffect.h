#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_Core/DBEffect.h"

struct IXmlSaver;
// forward declarations for factories
namespace PF_Core
{
	class BasicEffect;
	class ObjectsPool;
}; //namespace PF_Core

namespace NDb
{
struct AnimatedPlacementResource;
struct BasicEffectStandalone;
struct DBSceneObject;
struct EffectBase;

enum EAuraType
{
	AURATYPE_ALLY = 0,
	AURATYPE_ENEMY = 1,
};

const char *EnumToString( const EAuraType value );
const EAuraType StringToEnum_EAuraType( const char* value );

template <>
struct KnownEnum< EAuraType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EAuraType value ) { return EnumToString( value ); }
	static const EAuraType ToEnum( const char* value ) { return StringToEnum_EAuraType( value ); }
	static const EAuraType ToEnum( const string& value ) { return StringToEnum_EAuraType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EEffectSwitchLogic
{
	EFFECTSWITCHLOGIC_FACTIONVISIBILITY = 0,
	EFFECTSWITCHLOGIC_SENDERFACTION = 1,
};

const char *EnumToString( const EEffectSwitchLogic value );
const EEffectSwitchLogic StringToEnum_EEffectSwitchLogic( const char* value );

template <>
struct KnownEnum< EEffectSwitchLogic >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EEffectSwitchLogic value ) { return EnumToString( value ); }
	static const EEffectSwitchLogic ToEnum( const char* value ) { return StringToEnum_EEffectSwitchLogic( value ); }
	static const EEffectSwitchLogic ToEnum( const string& value ) { return StringToEnum_EEffectSwitchLogic( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EMinimapEffects
{
	MINIMAPEFFECTS_EGGCARRIER = 0,
	MINIMAPEFFECTS_MARKERALLY = 1,
	MINIMAPEFFECTS_MARKERHOSTILE = 2,
	MINIMAPEFFECTS_CHAT = 3,
};

const char *EnumToString( const EMinimapEffects value );
const EMinimapEffects StringToEnum_EMinimapEffects( const char* value );

template <>
struct KnownEnum< EMinimapEffects >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EMinimapEffects value ) { return EnumToString( value ); }
	static const EMinimapEffects ToEnum( const char* value ) { return StringToEnum_EMinimapEffects( value ); }
	static const EMinimapEffects ToEnum( const string& value ) { return StringToEnum_EMinimapEffects( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum ESceneObjectVisibilityMode
{
	SCENEOBJECTVISIBILITYMODE_ASOBJECT = 0,
	SCENEOBJECTVISIBILITYMODE_ASBUILDING = 1,
};

const char *EnumToString( const ESceneObjectVisibilityMode value );
const ESceneObjectVisibilityMode StringToEnum_ESceneObjectVisibilityMode( const char* value );

template <>
struct KnownEnum< ESceneObjectVisibilityMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ESceneObjectVisibilityMode value ) { return EnumToString( value ); }
	static const ESceneObjectVisibilityMode ToEnum( const char* value ) { return StringToEnum_ESceneObjectVisibilityMode( value ); }
	static const ESceneObjectVisibilityMode ToEnum( const string& value ) { return StringToEnum_ESceneObjectVisibilityMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EUnitSceneObjectModifyMode
{
	UNITSCENEOBJECTMODIFYMODE_APPEND = 0,
	UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC = 1,
	UNITSCENEOBJECTMODIFYMODE_REPLACEANIMATED = 2,
};

const char *EnumToString( const EUnitSceneObjectModifyMode value );
const EUnitSceneObjectModifyMode StringToEnum_EUnitSceneObjectModifyMode( const char* value );

template <>
struct KnownEnum< EUnitSceneObjectModifyMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EUnitSceneObjectModifyMode value ) { return EnumToString( value ); }
	static const EUnitSceneObjectModifyMode ToEnum( const char* value ) { return StringToEnum_EUnitSceneObjectModifyMode( value ); }
	static const EUnitSceneObjectModifyMode ToEnum( const string& value ) { return StringToEnum_EUnitSceneObjectModifyMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct AuraEffect : public EffectBase
{
	DBRESOURCE_METHODS( AuraEffect );
public:
	enum { typeId = 0x9E71DC80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AuraEffect::typeId; }
	EAuraType type;

	AuraEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AuraEffect& operator = ( const AuraEffect &_auraEffect ) { Assign( _auraEffect ); return *this; }
	AuraEffect( const AuraEffect &_auraEffect ) { Assign( _auraEffect ); }
	virtual void Assign( const AuraEffect &_auraEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AuraEffect * pOther = dynamic_cast< const AuraEffect * > ( _pResource );
		if ( pOther ) AuraEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct EffectSwitcher : public EffectBase
{
	DBRESOURCE_METHODS( EffectSwitcher );
public:
	enum { typeId = 0x9E71EC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)EffectSwitcher::typeId; }
	EEffectSwitchLogic logic;
	Ptr< EffectBase > effectOnVisible;
	Ptr< EffectBase > effectOnInvisible;
	bool isVisibleUnderWarfog;

	EffectSwitcher();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	EffectSwitcher& operator = ( const EffectSwitcher &_effectSwitcher ) { Assign( _effectSwitcher ); return *this; }
	EffectSwitcher( const EffectSwitcher &_effectSwitcher ) { Assign( _effectSwitcher ); }
	virtual void Assign( const EffectSwitcher &_effectSwitcher );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const EffectSwitcher * pOther = dynamic_cast< const EffectSwitcher * > ( _pResource );
		if ( pOther ) EffectSwitcher::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct InvisibilityEffect : public ScaleColorEffect
{
	DBRESOURCE_METHODS( InvisibilityEffect );
public:
	enum { typeId = 0x0B732380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)InvisibilityEffect::typeId; }

	InvisibilityEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	InvisibilityEffect& operator = ( const InvisibilityEffect &_invisibilityEffect ) { Assign( _invisibilityEffect ); return *this; }
	InvisibilityEffect( const InvisibilityEffect &_invisibilityEffect ) { Assign( _invisibilityEffect ); }
	virtual void Assign( const InvisibilityEffect &_invisibilityEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const InvisibilityEffect * pOther = dynamic_cast< const InvisibilityEffect * > ( _pResource );
		if ( pOther ) InvisibilityEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct MinimapEffect : public EffectBase
{
	DBRESOURCE_METHODS( MinimapEffect );
public:
	enum { typeId = 0xE78B94C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MinimapEffect::typeId; }
	EMinimapEffects effect;

	MinimapEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinimapEffect& operator = ( const MinimapEffect &_minimapEffect ) { Assign( _minimapEffect ); return *this; }
	MinimapEffect( const MinimapEffect &_minimapEffect ) { Assign( _minimapEffect ); }
	virtual void Assign( const MinimapEffect &_minimapEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinimapEffect * pOther = dynamic_cast< const MinimapEffect * > ( _pResource );
		if ( pOther ) MinimapEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct PlayAnimationEffect : public EffectBase
{
	DBRESOURCE_METHODS( PlayAnimationEffect );
public:
	enum { typeId = 0x9E67B282 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PlayAnimationEffect::typeId; }
	string animGraphNode;
	float markerReachTime;
	string marker;
	bool goToOtherNodeOnStop;
	string returnAnimGraphNode;

	PlayAnimationEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PlayAnimationEffect& operator = ( const PlayAnimationEffect &_playAnimationEffect ) { Assign( _playAnimationEffect ); return *this; }
	PlayAnimationEffect( const PlayAnimationEffect &_playAnimationEffect ) { Assign( _playAnimationEffect ); }
	virtual void Assign( const PlayAnimationEffect &_playAnimationEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PlayAnimationEffect * pOther = dynamic_cast< const PlayAnimationEffect * > ( _pResource );
		if ( pOther ) PlayAnimationEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct PriestessSignEffect : public BasicEffectStandalone
{
	DBRESOURCE_METHODS( PriestessSignEffect );
public:
	enum { typeId = 0xA06CEC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PriestessSignEffect::typeId; }
	Ptr< BasicEffectStandalone > soulEffect;
	string destinationLocator;
	float flyInDelay;
	Ptr< AnimatedPlacementResource > flyInPath;
	string flyInAnim;
	string flyOutAnim;

	PriestessSignEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PriestessSignEffect& operator = ( const PriestessSignEffect &_priestessSignEffect ) { Assign( _priestessSignEffect ); return *this; }
	PriestessSignEffect( const PriestessSignEffect &_priestessSignEffect ) { Assign( _priestessSignEffect ); }
	virtual void Assign( const PriestessSignEffect &_priestessSignEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PriestessSignEffect * pOther = dynamic_cast< const PriestessSignEffect * > ( _pResource );
		if ( pOther ) PriestessSignEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct RandomEffect : public EffectBase
{
	DBRESOURCE_METHODS( RandomEffect );
public:
	enum { typeId = 0x0B753AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)RandomEffect::typeId; }
	vector< Ptr< EffectBase > > effects;

	RandomEffect();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RandomEffect& operator = ( const RandomEffect &_randomEffect ) { Assign( _randomEffect ); return *this; }
	RandomEffect( const RandomEffect &_randomEffect ) { Assign( _randomEffect ); }
	virtual void Assign( const RandomEffect &_randomEffect );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RandomEffect * pOther = dynamic_cast< const RandomEffect * > ( _pResource );
		if ( pOther ) RandomEffect::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct UnitSceneObjectModify : public EffectBase
{
	DBRESOURCE_METHODS( UnitSceneObjectModify );
public:
	enum { typeId = 0x9E720B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UnitSceneObjectModify::typeId; }
	EUnitSceneObjectModifyMode mode;
	ESceneObjectVisibilityMode visibilityMode;
	vector< Ptr< DBSceneObject > > sceneObjects;

	UnitSceneObjectModify();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UnitSceneObjectModify& operator = ( const UnitSceneObjectModify &_unitSceneObjectModify ) { Assign( _unitSceneObjectModify ); return *this; }
	UnitSceneObjectModify( const UnitSceneObjectModify &_unitSceneObjectModify ) { Assign( _unitSceneObjectModify ); }
	virtual void Assign( const UnitSceneObjectModify &_unitSceneObjectModify );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UnitSceneObjectModify * pOther = dynamic_cast< const UnitSceneObjectModify * > ( _pResource );
		if ( pOther ) UnitSceneObjectModify::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<PF_Core::BasicEffect> Retrieve( PF_Core::ObjectsPool &pool ) const;
#endif // #ifndef VISUAL_CUTTED
};

}; // namespace NDb
