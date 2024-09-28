#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAbility.h"

struct IXmlSaver;

namespace NDb
{
struct Consumable;
struct GameObject;

enum EConsumableOrigin
{
	CONSUMABLEORIGIN_DEFAULT = 0,
	CONSUMABLEORIGIN_SHOP = 1,
	CONSUMABLEORIGIN_MINIGAME = 2,
	CONSUMABLEORIGIN_PICKUPABLE = 3,
	CONSUMABLEORIGIN_APPLICATOR = 4,
	CONSUMABLEORIGIN_SCRIPT = 5,
};

const char *EnumToString( const EConsumableOrigin value );
const EConsumableOrigin StringToEnum_EConsumableOrigin( const char* value );

template <>
struct KnownEnum< EConsumableOrigin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 6 };
	static const char *ToString( const EConsumableOrigin value ) { return EnumToString( value ); }
	static const EConsumableOrigin ToEnum( const char* value ) { return StringToEnum_EConsumableOrigin( value ); }
	static const EConsumableOrigin ToEnum( const string& value ) { return StringToEnum_EConsumableOrigin( value.c_str() ); }
	static const int SizeOf() { return 6; }
};

struct Consumable : public Ability
{
	DBRESOURCE_METHODS( Consumable );
public:
	enum { typeId = 0x0F68CB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)Consumable::typeId; }
	int naftaCost;
	int maxQuantity;
	Ptr< GameObject > gameObject;
	bool isPotion;
	string persistentId;

	Consumable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Consumable& operator = ( const Consumable &_consumable ) { Assign( _consumable ); return *this; }
	Consumable( const Consumable &_consumable ) { Assign( _consumable ); }
	virtual void Assign( const Consumable &_consumable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Consumable * pOther = dynamic_cast< const Consumable * > ( _pResource );
		if ( pOther ) Consumable::Assign( *pOther );
	}
};

struct ConsumablesShop : public DbResource
{
	DBRESOURCE_METHODS( ConsumablesShop );
public:
	enum { typeId = 0x0F68CB81 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ConsumablesShop::typeId; }
	vector< Ptr< Consumable > > items;
	float interactionRadius;
	bool secretShop;

	ConsumablesShop();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ConsumablesShop& operator = ( const ConsumablesShop &_consumablesShop ) { Assign( _consumablesShop ); return *this; }
	ConsumablesShop( const ConsumablesShop &_consumablesShop ) { Assign( _consumablesShop ); }
	virtual void Assign( const ConsumablesShop &_consumablesShop );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ConsumablesShop * pOther = dynamic_cast< const ConsumablesShop * > ( _pResource );
		if ( pOther ) ConsumablesShop::Assign( *pOther );
	}
};

}; // namespace NDb
