#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Scene/DBScene.h"

struct IXmlSaver;

namespace NDb
{
struct MinigameVisualStateChange;

enum ChangesApplyType
{
	CHANGESAPPLYTYPE_DONOTAPPLY = 0,
	CHANGESAPPLYTYPE_APPLYDEFAULT = 1,
	CHANGESAPPLYTYPE_APPLYABSOLUTEROTATION = 2,
	CHANGESAPPLYTYPE_APPLYABSOLUTEALL = 3,
	CHANGESAPPLYTYPE_APPLYRELATIONAL = 4,
};

const char *EnumToString( const ChangesApplyType value );
const ChangesApplyType StringToEnum_ChangesApplyType( const char* value );

template <>
struct KnownEnum< ChangesApplyType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const ChangesApplyType value ) { return EnumToString( value ); }
	static const ChangesApplyType ToEnum( const char* value ) { return StringToEnum_ChangesApplyType( value ); }
	static const ChangesApplyType ToEnum( const string& value ) { return StringToEnum_ChangesApplyType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum EBidonType
{
	BIDONTYPE_NONE = 0,
	BIDONTYPE_SPEEDCLOCK = 1,
	BIDONTYPE_SLOWDOWNGLUE = 2,
	BIDONTYPE_MAGICPOINTER = 3,
	BIDONTYPE_PALETTE = 4,
};

const char *EnumToString( const EBidonType value );
const EBidonType StringToEnum_EBidonType( const char* value );

template <>
struct KnownEnum< EBidonType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EBidonType value ) { return EnumToString( value ); }
	static const EBidonType ToEnum( const char* value ) { return StringToEnum_EBidonType( value ); }
	static const EBidonType ToEnum( const string& value ) { return StringToEnum_EBidonType( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum MinigameClientType
{
	MINIGAMECLIENTTYPE_LOCAL = 0,
	MINIGAMECLIENTTYPE_REMOTE = 1,
	MINIGAMECLIENTTYPE_ANY = 2,
};

const char *EnumToString( const MinigameClientType value );
const MinigameClientType StringToEnum_MinigameClientType( const char* value );

template <>
struct KnownEnum< MinigameClientType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const MinigameClientType value ) { return EnumToString( value ); }
	static const MinigameClientType ToEnum( const char* value ) { return StringToEnum_MinigameClientType( value ); }
	static const MinigameClientType ToEnum( const string& value ) { return StringToEnum_MinigameClientType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum MinigameVisualState
{
	MINIGAMEVISUALSTATE_NONE = 0,
	MINIGAMEVISUALSTATE_SESSION = 1,
	MINIGAMEVISUALSTATE_CLINIC_LOBBY = 2,
	MINIGAMEVISUALSTATE_CLINIC_INGAME = 3,
	MINIGAMEVISUALSTATE_CLINIC_SHOP = 4,
	MINIGAMEVISUALSTATE_EASEL_LOBBY = 5,
	MINIGAMEVISUALSTATE_EASEL_LEAVINGLOBBY = 6,
	MINIGAMEVISUALSTATE_EASEL_INGAME = 7,
};

const char *EnumToString( const MinigameVisualState value );
const MinigameVisualState StringToEnum_MinigameVisualState( const char* value );

template <>
struct KnownEnum< MinigameVisualState >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const MinigameVisualState value ) { return EnumToString( value ); }
	static const MinigameVisualState ToEnum( const char* value ) { return StringToEnum_MinigameVisualState( value ); }
	static const MinigameVisualState ToEnum( const string& value ) { return StringToEnum_MinigameVisualState( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

struct MinigamePlaceParams : public DbResource
{
	DBRESOURCE_METHODS( MinigamePlaceParams );
public:
	enum { typeId = 0xE96B3440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MinigamePlaceParams::typeId; }
	vector< Ptr< MinigameVisualStateChange > > stateChanges;

	MinigamePlaceParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinigamePlaceParams& operator = ( const MinigamePlaceParams &_minigamePlaceParams ) { Assign( _minigamePlaceParams ); return *this; }
	MinigamePlaceParams( const MinigamePlaceParams &_minigamePlaceParams ) { Assign( _minigamePlaceParams ); }
	virtual void Assign( const MinigamePlaceParams &_minigamePlaceParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinigamePlaceParams * pOther = dynamic_cast< const MinigamePlaceParams * > ( _pResource );
		if ( pOther ) MinigamePlaceParams::Assign( *pOther );
	}
};

struct MinigameVisualStateChange : public DbResource
{
	DBRESOURCE_METHODS( MinigameVisualStateChange );
public:
	enum { typeId = 0xE96AD341 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)MinigameVisualStateChange::typeId; }
	MinigameVisualState fromState;
	MinigameVisualState toState;
	MinigameClientType clientType;
	AnimatedPlacement newPlacement;
	ChangesApplyType changePlacement;

	MinigameVisualStateChange();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MinigameVisualStateChange& operator = ( const MinigameVisualStateChange &_minigameVisualStateChange ) { Assign( _minigameVisualStateChange ); return *this; }
	MinigameVisualStateChange( const MinigameVisualStateChange &_minigameVisualStateChange ) { Assign( _minigameVisualStateChange ); }
	virtual void Assign( const MinigameVisualStateChange &_minigameVisualStateChange );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MinigameVisualStateChange * pOther = dynamic_cast< const MinigameVisualStateChange * > ( _pResource );
		if ( pOther ) MinigameVisualStateChange::Assign( *pOther );
	}
};

}; // namespace NDb
