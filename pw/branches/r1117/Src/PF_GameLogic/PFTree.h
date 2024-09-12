#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "../System/Geom.h"

#include "../PF_Core/WorldObject.h"
#include "PFLogicObject.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "../System/ScopedArray.h"
#include "../System/ScopedPtr.h"


// Maximum possible unit visibility radius

namespace NGameX { class PFClientTree; }

namespace NWorld
{

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////
class PFTree : public PFLogicObject
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x16616C40, PFTree, NGameX::PFClientTree)
public:
  PFTree( PFWorld* pWorld, const NDb::AdvMapObject& dbObject );
  
  void    DropTree( const CVec2& dir, const CPtr<PFBaseUnit>& pUnitThatDropsTree );
  void    RestoreTree();
	virtual void Reset();
  virtual void Hide( bool hide );

  virtual bool IsVisibleForFaction( int faction ) const;

protected:
  
  PFTree() { }
  virtual bool Step( float dtInSeconds );
	virtual void UpdateNatureType();
  virtual void UpdateDayNightState(const bool night);
	virtual bool NeedToBeStepped() { return false; }
  virtual bool NeedToSerialize();
  virtual void CalculateSize( PFWorld* pWorld );
  virtual void UpdateSize( bool bNormal );
  
  enum TreeState
  {
    stateNormal,
    stateGrowDelay,
    stateWaitForFog,
  };

  ZDATA_(PFLogicObject);
  TreeState currentState;
  float     cooldown;
  bool      wonderfulTree;
  int       prevNatureType;
  bool      prevNight;
  int       lastUpdateStepNum;
	
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObjectCopy; // for marking on tile map
  vector<SVector> occupiedTiles;
  float      treeObjectSize;        // unit size, in meters (rounded up to tile size)
  int        treeObjectTileSize;    // unit size, in tiles
  int        treeObjectDynTileSize; // unit size, in tiles
  ZNOMAPOBJECTEND
  ZNOCRCEND

  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFLogicObject*)this); f.Add(2,&currentState); f.Add(3,&cooldown); f.Add(4,&wonderfulTree); f.Add(5,&prevNatureType); f.Add(6,&prevNight); f.Add(7,&lastUpdateStepNum);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(8,&dbObjectCopy); f.Add(9,&occupiedTiles); f.Add(10,&treeObjectSize); f.Add(11,&treeObjectTileSize); f.Add(12,&treeObjectDynTileSize);  }  } return 0; }
};

} // namespace NWorld

