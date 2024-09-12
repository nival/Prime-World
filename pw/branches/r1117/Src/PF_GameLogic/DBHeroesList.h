#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct Hero;

struct HeroesDB : public DbResource
{
	DBRESOURCE_METHODS( HeroesDB );
public:
	vector< Ptr< Hero > > heroes;

	HeroesDB();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroesDB& operator = ( const HeroesDB &_heroesDB ) { Assign( _heroesDB ); return *this; }
	HeroesDB( const HeroesDB &_heroesDB ) { Assign( _heroesDB ); }
	virtual void Assign( const HeroesDB &_heroesDB );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroesDB * pOther = dynamic_cast< const HeroesDB * > ( _pResource );
		if ( pOther ) HeroesDB::Assign( *pOther );
	}
};

}; // namespace NDb
