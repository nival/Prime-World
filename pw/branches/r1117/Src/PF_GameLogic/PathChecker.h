#pragma once


#include "TileMap.h"
#include "PointChecking.h"


namespace NWorld
{

// Range between unit (pSelf) and target point
class RangeChecking : public IPointChecking, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0xC56CEB40, RangeChecking);

protected:
	RangeChecking()
		: minDist( 0.0f )
		, targetTile( 0, 0 )
	{}
	ZDATA_(PFWorldObjectBase)
  ZNOPARENT(IPointChecking)
public:
  float   minDist;			// in tile units, but float
  CVec2   targetTile;		// may be between tiles, so - float ...
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&minDist); f.Add(3,&targetTile); return 0; }

	RangeChecking( const CVec2& target, PFBaseUnit* pSelf, float stopRange )
		: PFWorldObjectBase( pSelf->GetWorld(), 0 ), minDist( 0 ), targetTile( 0, 0 )
	{
    TileMap* pMap  = pSelf->GetTileMap();
    float tileSize = pMap->GetTileSize();

    // allowed distance in tiles
    minDist = floor( stopRange / tileSize );
    
    // apply offset to a targetTile to avoid extra computations in IsGoodTile()
    const SVector tile = pMap->GetTile( target );
    targetTile = CVec2( tile.x, tile.y );
	}

  virtual bool IsGoodTile( const SVector& curTile) const
  {
    const CVec2 delta( curTile.x - targetTile.x, curTile.y - targetTile.y );
    return ( fabs2( delta ) <= fabs( minDist ) );
  }
};

// Range between unit (pSelf) and another unit (pTarget)
class ObjectRangeChecking : public RangeChecking
{
	WORLD_OBJECT_METHODS( 0xC56CEB41, ObjectRangeChecking);

public:
	ObjectRangeChecking()
	{}
	ObjectRangeChecking(PFBaseUnit *pTarget, PFBaseUnit *pSelf, float stopRange)
	: RangeChecking( pTarget->GetPosition().AsVec2D(), pSelf, stopRange + pTarget->GetObjectSize() * 0.5f )
	{}
};

} // namespace
