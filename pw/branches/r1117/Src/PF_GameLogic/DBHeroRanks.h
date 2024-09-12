#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct Texture;

struct Rank
{
public:
	int rating;
	CTextRef rankNameA;
	CTextRef rankNameB;
	CTextRef rankGroupNameA;
	CTextRef rankGroupNameB;
	CTextRef rankTooltipA;
	CTextRef rankTooltipB;
	Ptr< Texture > iconA;
	Ptr< Texture > bigIconA;
	Ptr< Texture > iconB;
	Ptr< Texture > bigIconB;
	float recommendedForce;
	int rewardTalentsCountForUI;

	Rank();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct HeroRanks : public DbResource
{
	DBRESOURCE_METHODS( HeroRanks );
public:
	int highLevelsMMRating;
	vector< Rank > ranks;

	HeroRanks();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroRanks& operator = ( const HeroRanks &_heroRanks ) { Assign( _heroRanks ); return *this; }
	HeroRanks( const HeroRanks &_heroRanks ) { Assign( _heroRanks ); }
	virtual void Assign( const HeroRanks &_heroRanks );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroRanks * pOther = dynamic_cast< const HeroRanks * > ( _pResource );
		if ( pOther ) HeroRanks::Assign( *pOther );
	}
};

}; // namespace NDb
