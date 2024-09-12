#include "stdafx.h"

#include "StaticPathInternal.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCommonStaticPath::CCommonStaticPath( NWorld::PFWorld* world, const vector<SVector>& tiles, int _length )
: PFWorldObjectBase( world, 0 )
, length( _length )
{
  path.resize( length );
  nstl::copy( tiles.begin(), tiles.begin() + length, path.begin() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonStaticPath::MergePath( const vector<SVector> &tiles, int startIndex )
{
  if ( mDistance( GetFinishTile(), tiles[startIndex] ) > 2 )
    return false;

  if ( GetFinishTile() == tiles[startIndex] )
    ++startIndex;

  const int newLength = length + tiles.size() - startIndex;
  path.resize( newLength );
  nstl::copy( tiles.begin() + startIndex, tiles.end(), path.begin() + length );

  length = newLength;
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_WORLD_OBJECT( CCommonStaticPath );
