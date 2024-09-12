#include "StdAfx.h"
#include "RegionPointChecker.h"

namespace NWorld
{

RegionPointChecker::RegionPointChecker( PFWorld* world, const vector<SVector> & region, int _unitRadius )
: PFWorldObjectBase( world, 0 ), unitRadius(_unitRadius)
{
  //array creation
  CreateGoodTilesArray(region); 

  //mark reagion tiles
  for (int i = 0; i<region.size(); i++)
  { 
    MarkTile(region[i]);
  }
}

void RegionPointChecker::CreateGoodTilesArray(const vector<SVector> & region)
{
  int xmin = INT_MAX;
  int ymin = INT_MAX;
  int xmax = 0;
  int ymax = 0;

  //determine border
  for (int i = 0; i<region.size(); i++)
  {
    SVector curTile = region[i];

    xmin = min(xmin, curTile.x);
    ymin = min(ymin, curTile.y);

    xmax = max(xmax, curTile.x);
    ymax = max(ymax, curTile.y);
  }

  //make border wider.
  offset.x = max(xmin - unitRadius*2, 0);
  offset.y = max(ymin - unitRadius*2, 0);

  goodTiles.SetSizes(xmax + unitRadius*2 - offset.x, ymax + unitRadius*2 - offset.y);
  goodTiles.SetZeroFast();
}

void RegionPointChecker::MarkTile( const SVector & tile )
{
  int x = tile.x - offset.x;
  int y = tile.y - offset.y;

  for( int dx = x-unitRadius; dx <= x + unitRadius; ++dx )
  {
    for ( int dy = y-unitRadius; dy <= y+unitRadius; ++dy )
    {
      bool inBounds = (dx>=0 && dx<goodTiles.GetSizeX()) && (dy>=0 && dy<goodTiles.GetSizeY());
      if(!inBounds)
        continue;
      if ( abs( dx - x) + abs( dy - y) <= unitRadius)
        goodTiles.SetData(dx, dy);
    }
  }
}

bool RegionPointChecker::IsGoodTile( const SVector &curTile ) const
{
  int x = curTile.x - offset.x;
  int y = curTile.y - offset.y;

  //bounds check
  if (x<0 || y<0)
    return false;

  if (x>=goodTiles.GetSizeX() || y>=goodTiles.GetSizeY())
    return false;

  return  goodTiles.GetData(x, y);
}
}

REGISTER_WORLD_OBJECT_NM(RegionPointChecker,  NWorld)
