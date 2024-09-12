#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct Texture;

struct CurrencyDescription
{
public:
	string Id;
	CTextRef Description;
	Ptr< Texture > Icon;

	CurrencyDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CurrencyDescriptionList : public DbResource
{
	DBRESOURCE_METHODS( CurrencyDescriptionList );
public:
	vector< CurrencyDescription > CurrencyList;

	CurrencyDescriptionList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CurrencyDescriptionList& operator = ( const CurrencyDescriptionList &_currencyDescriptionList ) { Assign( _currencyDescriptionList ); return *this; }
	CurrencyDescriptionList( const CurrencyDescriptionList &_currencyDescriptionList ) { Assign( _currencyDescriptionList ); }
	virtual void Assign( const CurrencyDescriptionList &_currencyDescriptionList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CurrencyDescriptionList * pOther = dynamic_cast< const CurrencyDescriptionList * > ( _pResource );
		if ( pOther ) CurrencyDescriptionList::Assign( *pOther );
	}
};

}; // namespace NDb
