#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBStats.h"

struct IXmlSaver;

namespace NDb
{
struct AchievBase;
struct Talent;
struct Texture;

enum ETalentLevel
{
	TALENTLEVEL_ID0 = 0,
	TALENTLEVEL_ID1 = 1,
	TALENTLEVEL_ID2 = 2,
	TALENTLEVEL_ID3 = 3,
	TALENTLEVEL_ID4 = 4,
	TALENTLEVEL_ID5 = 5,
};

const char *EnumToString( const ETalentLevel value );
const ETalentLevel StringToEnum_ETalentLevel( const char* value );

template <>
struct KnownEnum< ETalentLevel >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const ETalentLevel value ) { return EnumToString( value ); }
	static const ETalentLevel ToEnum( const char* value ) { return StringToEnum_ETalentLevel( value ); }
	static const ETalentLevel ToEnum( const string& value ) { return StringToEnum_ETalentLevel( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum ETalentRarity
{
	TALENTRARITY_CLASS = 0,
	TALENTRARITY_ORDINARY = 1,
	TALENTRARITY_GOOD = 2,
	TALENTRARITY_EXCELLENT = 3,
	TALENTRARITY_MAGNIFICENT = 4,
	TALENTRARITY_EXCLUSIVE = 5,
	TALENTRARITY_OUTSTANDING = 6,
};

const char *EnumToString( const ETalentRarity value );
const ETalentRarity StringToEnum_ETalentRarity( const char* value );

template <>
struct KnownEnum< ETalentRarity >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ETalentRarity value ) { return EnumToString( value ); }
	static const ETalentRarity ToEnum( const char* value ) { return StringToEnum_ETalentRarity( value ); }
	static const ETalentRarity ToEnum( const string& value ) { return StringToEnum_ETalentRarity( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum ETalentRollGroup
{
	TALENTROLLGROUP_PVP = 1,
	TALENTROLLGROUP_TRAINING = 2,
	TALENTROLLGROUP_CTE = 4,
	TALENTROLLGROUP_PVE = 8,
	TALENTROLLGROUP_CASTLE = 16,
	TALENTROLLGROUP_MIDONLY = 32,
	TALENTROLLGROUP_ALL = 63,
};

const char *EnumToString( const ETalentRollGroup value );
const ETalentRollGroup StringToEnum_ETalentRollGroup( const char* value );

template <>
struct KnownEnum< ETalentRollGroup >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const ETalentRollGroup value ) { return EnumToString( value ); }
	static const ETalentRollGroup ToEnum( const char* value ) { return StringToEnum_ETalentRollGroup( value ); }
	static const ETalentRollGroup ToEnum( const string& value ) { return StringToEnum_ETalentRollGroup( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum ETalents
{
	TALENTS_POINTS_PER_LEVEL = 4,
};

const char *EnumToString( const ETalents value );
const ETalents StringToEnum_ETalents( const char* value );

template <>
struct KnownEnum< ETalents >
{
	enum { isKnown = 1 };
	enum { sizeOf = 1 };
	static const char *ToString( const ETalents value ) { return EnumToString( value ); }
	static const ETalents ToEnum( const char* value ) { return StringToEnum_ETalents( value ); }
	static const ETalents ToEnum( const string& value ) { return StringToEnum_ETalents( value.c_str() ); }
	static const int SizeOf() { return 1; }
};

enum ETalentSlot
{
	TALENTSLOT_ID0 = 0,
	TALENTSLOT_ID1 = 1,
	TALENTSLOT_ID2 = 2,
	TALENTSLOT_ID3 = 3,
	TALENTSLOT_ID4 = 4,
	TALENTSLOT_ID5 = 5,
};

const char *EnumToString( const ETalentSlot value );
const ETalentSlot StringToEnum_ETalentSlot( const char* value );

template <>
struct KnownEnum< ETalentSlot >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const ETalentSlot value ) { return EnumToString( value ); }
	static const ETalentSlot ToEnum( const char* value ) { return StringToEnum_ETalentSlot( value ); }
	static const ETalentSlot ToEnum( const string& value ) { return StringToEnum_ETalentSlot( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

enum ETalentSlotStatus
{
	TALENTSLOTSTATUS_NORMAL = 0,
	TALENTSLOTSTATUS_LOCKED = 1,
	TALENTSLOTSTATUS_UNAVAILABLE = 2,
};

const char *EnumToString( const ETalentSlotStatus value );
const ETalentSlotStatus StringToEnum_ETalentSlotStatus( const char* value );

template <>
struct KnownEnum< ETalentSlotStatus >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ETalentSlotStatus value ) { return EnumToString( value ); }
	static const ETalentSlotStatus ToEnum( const char* value ) { return StringToEnum_ETalentSlotStatus( value ); }
	static const ETalentSlotStatus ToEnum( const string& value ) { return StringToEnum_ETalentSlotStatus( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct AchievmentCondition
{
public:
	Ptr< AchievBase > achiev;
	int minRank;

	AchievmentCondition();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ConsumptionBonus
{
public:
	int constant;
	int percent;

	ConsumptionBonus();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TalentSlot
{
public:
	ETalentSlotStatus status;
	Ptr< Talent > talent;
	int refineRate;
	int aIPriority;

	TalentSlot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TalentsLevel
{
public:
	vector< TalentSlot > talents;

	TalentsLevel();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Talent : public Ability
{
	DBRESOURCE_METHODS( Talent );
public:
	enum { typeId = 0x0F690AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Talent::typeId; }
	int minLevel;
	int devPoints;
	float budget;
	vector< AchievmentCondition > activationConditions;
	int naftaCost;
	vector< Ptr< Talent > > prerequisiteTalents;
	ETalentRarity rarity;
	string persistentId;
	int vendorCost;
	ETalentRollGroup talentRollGroups;
	int askId;
	bool isGenderTalent;
	bool isTakenOnStart;
	bool isUltimateTalent;
	int upgradeLevel;
	ConsumptionBonus consumptionBonus;

	Talent();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Talent& operator = ( const Talent &_talent ) { Assign( _talent ); return *this; }
	Talent( const Talent &_talent ) { Assign( _talent ); }
	virtual void Assign( const Talent &_talent );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Talent * pOther = dynamic_cast< const Talent * > ( _pResource );
		if ( pOther ) Talent::Assign( *pOther );
	}
};

struct TalentKit : public DbResource
{
	DBRESOURCE_METHODS( TalentKit );
public:
	enum { typeId = 0xE79C6BC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TalentKit::typeId; }
	CTextRef name;
	Ptr< Talent > special;
	int kitCapacity;
	vector< Ptr< Talent > > talents;

	TalentKit();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentKit& operator = ( const TalentKit &_talentKit ) { Assign( _talentKit ); return *this; }
	TalentKit( const TalentKit &_talentKit ) { Assign( _talentKit ); }
	virtual void Assign( const TalentKit &_talentKit );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentKit * pOther = dynamic_cast< const TalentKit * > ( _pResource );
		if ( pOther ) TalentKit::Assign( *pOther );
	}
};

struct TalentPack : public DbResource
{
	DBRESOURCE_METHODS( TalentPack );
public:
	enum { typeId = 0xE79C6BC1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TalentPack::typeId; }
	string id;
	CTextRef name;
	string iconStyle;
	Ptr< Texture > icon;
	bool isRedPack;
	vector< Ptr< Talent > > talents;

	TalentPack();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentPack& operator = ( const TalentPack &_talentPack ) { Assign( _talentPack ); return *this; }
	TalentPack( const TalentPack &_talentPack ) { Assign( _talentPack ); }
	virtual void Assign( const TalentPack &_talentPack );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentPack * pOther = dynamic_cast< const TalentPack * > ( _pResource );
		if ( pOther ) TalentPack::Assign( *pOther );
	}
};

struct TalentsSet : public DbResource
{
	DBRESOURCE_METHODS( TalentsSet );
public:
	enum { typeId = 0x0F691300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TalentsSet::typeId; }
	vector< TalentsLevel > levels;

	TalentsSet();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TalentsSet& operator = ( const TalentsSet &_talentsSet ) { Assign( _talentsSet ); return *this; }
	TalentsSet( const TalentsSet &_talentsSet ) { Assign( _talentsSet ); }
	virtual void Assign( const TalentsSet &_talentsSet );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TalentsSet * pOther = dynamic_cast< const TalentsSet * > ( _pResource );
		if ( pOther ) TalentsSet::Assign( *pOther );
	}
};

}; // namespace NDb
