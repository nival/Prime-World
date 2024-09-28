// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRenderResources.h"
#include "DBHeroRanks.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( HeroRanks );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Rank::Rank() :
		rating( 0 )
	, recommendedForce( 0.0f )
	, rewardTalentsCountForUI( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Rank::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rating );
	saver.Add( 3, &rankNameA );
	saver.Add( 4, &rankNameB );
	saver.Add( 5, &rankGroupNameA );
	saver.Add( 6, &rankGroupNameB );
	saver.Add( 7, &rankTooltipA );
	saver.Add( 8, &rankTooltipB );
	saver.Add( 9, &iconA );
	saver.Add( 10, &bigIconA );
	saver.Add( 11, &iconB );
	saver.Add( 12, &bigIconB );
	saver.Add( 13, &recommendedForce );
	saver.Add( 14, &rewardTalentsCountForUI );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Rank::operator&( IXmlSaver &saver )
{
	saver.Add( "rating", &rating );
	saver.Add( "rankNameA", &rankNameA );
	saver.Add( "rankNameB", &rankNameB );
	saver.Add( "rankGroupNameA", &rankGroupNameA );
	saver.Add( "rankGroupNameB", &rankGroupNameB );
	saver.Add( "rankTooltipA", &rankTooltipA );
	saver.Add( "rankTooltipB", &rankTooltipB );
	saver.Add( "iconA", &iconA );
	saver.Add( "bigIconA", &bigIconA );
	saver.Add( "iconB", &iconB );
	saver.Add( "bigIconB", &bigIconB );
	saver.Add( "recommendedForce", &recommendedForce );
	saver.Add( "rewardTalentsCountForUI", &rewardTalentsCountForUI );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeroRanks::HeroRanks() :
		highLevelsMMRating( 2000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRanks::operator&( IBinSaver &saver )
{
	saver.Add( 2, &highLevelsMMRating );
	saver.Add( 3, &ranks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeroRanks::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeroRanks* parentPtr = (HeroRanks*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRanks::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "highLevelsMMRating", &highLevelsMMRating );
	saver.Add( "ranks", &ranks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeroRanks::Assign( const HeroRanks& _heroRanks )
{
	highLevelsMMRating = _heroRanks.highLevelsMMRating;
	ranks = _heroRanks.ranks;
}
}; // namespace NDb
