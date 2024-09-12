#pragma once

#include "PointChecking.h"
#include "../System/BitData.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{
class RegionPointChecker: public IPointChecking, public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0x8B794300, RegionPointChecker);

  RegionPointChecker() {}

  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(IPointChecking)
  CArray2D1Bit goodTiles;
  SVector offset;
  int unitRadius;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&goodTiles); f.Add(3,&offset); f.Add(4,&unitRadius); return 0; }

  RegionPointChecker( PFWorld* world, const vector<SVector> & region, int _unitRadius );
  virtual bool IsGoodTile( const SVector &curTile ) const;

private:
  void CreateGoodTilesArray(const vector<SVector> & region);
  void MarkTile(const SVector & tile);;
};
}