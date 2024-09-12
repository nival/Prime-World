#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct AdvMapDescription;

struct MapList : public DbResource
{
	DBRESOURCE_METHODS( MapList );
public:
	vector< Ptr< AdvMapDescription > > maps;

	MapList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	MapList& operator = ( const MapList &_mapList ) { Assign( _mapList ); return *this; }
	MapList( const MapList &_mapList ) { Assign( _mapList ); }
	virtual void Assign( const MapList &_mapList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const MapList * pOther = dynamic_cast< const MapList * > ( _pResource );
		if ( pOther ) MapList::Assign( *pOther );
	}
};

}; // namespace NDb
