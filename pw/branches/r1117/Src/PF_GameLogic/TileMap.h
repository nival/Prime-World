#pragma once

#include "../System/2Darray.h"
#include "PFWorldObjectBase.h"

#include "DI/DI.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
const int MAX_UNIT_SIZE = 16;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Valid map modes. Bit mask. Should specify 1-bit value for map modification (can modify single layer
// only), and OR of few values (few non-zero bits) for checking map (for CanUnitGo()).
// Number of items should be in sync with TileMap::NUM_LAYERS.
enum
{
	MAP_MODE_NONE      = 0,			// none mode for initialization and verification purposes
	// bitmask, corresponds to NUM_LAYERS
	MAP_MODE_STATIC    = 1,			// static map geometry, will never be changed
	MAP_MODE_DYNAMIC   = 2,			// moving units with tiny sizes
	MAP_MODE_BUILDING  = 4,			// buildings are marked here (marks can be removed and placed at runtime)
	MAP_MODE_IDLE = 8,			    // moving units with real sizes
	// synthetic modes
	MAP_MODE_ALL   = MAP_MODE_STATIC + MAP_MODE_DYNAMIC + MAP_MODE_BUILDING, // collide with everything (synchronous world)
	MAP_MODE_ALL_STATICS = MAP_MODE_STATIC + MAP_MODE_BUILDING,						   // collide with all static layers
	__MAP_MODE_MAX = MAP_MODE_ALL + MAP_MODE_IDLE
};
class MapModeChanger;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TileMap
  : public PFWorldObjectBase
  , public DI::SelfProvider<TileMap>
{
  WORLD_OBJECT_METHODS(0x1E59B440, TileMap);

  friend MapModeChanger;
public:
  TileMap();
  TileMap( PFWorld* pWorld );

  // prepare map
	void Prepare(int sizeX, int sizeY, float sizeOfTile);
	void ApplyHeightMap(CArray2D<float> const& heights);
	void OnLoaded();

	// updating passability map
	void UpdateMap( int x0, int x1, int y0, int y1 );
	void UpdateMap() { UpdateMap( 0, width-1, 0, height-1 ); }

	// note: MarkUnitTiles() uses float position to ensure units, not placed exactly
	// on tile occupy adjacent tiles too
	void MarkUnitTiles(const CVec2 &pos, int size, bool blocked, bool rounded);
	void MarkObject(const vector<SVector> & tilesToMark, bool _lock, int _markMode);
  void FillOccupiedTiles(vector<SVector> & tilesToMark, const CTRect<float>& _coll, const float _tileSize, const vector<CTPoint<int>>& _mask, 
    const Placement &_place,CTRect<int> *_pTileRect = 0) const;

	// Check collision on TileMap (few objects occupy the same place); return true
	// when one of cells is occupied by more than one objects, and false when
	// no collision detected.
	bool CheckCollision(const CVec2 &pos, int size) const;

  bool CanUnitGo( int tileSize, const SVector &tile ) const { return CanUnitGo( tileSize, tileSize, tile ); }
  bool CanUnitGo( int tileSize, int tileSizeDynamic, const SVector& tile ) const;
  bool CanUnitGoByDir( int tileSize, const SVector& tile, const SVector& shift ) const { return CanUnitGoByDir( tileSize, tileSize, tile, shift ); }
  bool CanUnitGoByDir( int tileSize, int tileSizeDynamic, const SVector& tile, const SVector& shift ) const;

	int GetSizeX() const { return width;   }
	int GetSizeY() const { return height;  }
  bool IsPointOutsideMap( int x, int y ) const { return ( ( x | y | width - x - 1 | height - y - 1 ) < 0 ); }
	int GetMode()  const { return mapMode; }

	// map tile information
	int GetStaticObject(int x, int y, int range);

	// floats <-> tiles conversion
	float GetTileSize() const { return tileSize; }
  int GetLenghtInTiles(float lenght) const {return floor(lenght/ tileSize);}
	const SVector GetTile(float x, float y) const { return SVector(floor(x / tileSize), floor(y / tileSize)); }
	const SVector GetTile(const CVec2 &point) const { return GetTile(point.x, point.y); }
	CVec2 GetPointByTile(int x, int y) const { return CVec2((x + 0.5f) * tileSize, (y + 0.5f) * tileSize); }
	CVec2 GetPointByTile(const SVector &tile) const { return GetPointByTile(tile.x, tile.y); }

	// debugging
	void Dump( const char* fileName, int mapMode, const vector<SVector>* wayPoints = 0, const vector<SVector>* wayPoints2 = 0 );
  bool CanUnitGoDebug( int x, int y, int mode, int tileSize ) const;
protected:
	void SetMode(int newMode);
	void GetUnitUpdateRect(const CVec2 &pos, int size, int& xMin, int& xMax, int& yMin, int& yMax) const;

private:
	typedef DWORD CellType;
	static const int							 NUM_LAYERS = 4;
	static const int               LAYER_BITS = sizeof(TileMap::CellType) * 8 / NUM_LAYERS;
	static const TileMap::CellType LAYER_MASK = (1 << LAYER_BITS) - 1;
	static const int               SIGN_BIT   = LAYER_BITS - 1;

	const CellType& GetCell( int x, int y ) const { return mapData.Get( x, y ); }
  void SetCell( int x, int y, const CellType& value ) { mapData.Set( x, y, value ); }

	int  GetItem(int x, int y) const;
	void SetItem(int x, int y, int value);

  ZDATA_(PFWorldObjectBase)
  ZNOPARENT( DI::SelfProvider<TileMap> )
	int                 width;
	int                 height;
	float			          tileSize;
  
  ZNOCRC
  CArray2D<CellType>  mapData;

  CellType	checkMask;			// used by GetItem()/SetItem()
	int				checkShift;			// ...

	int				mapMode;
	int				mapModeBase;
  int       mapModeBaseDynamic;
	int				mapModeCheck;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&width); f.Add(3,&height); f.Add(4,&tileSize);  if(!f.IsChecksum()){ f.Add(5,&mapData); f.Add(6,&checkMask); f.Add(7,&checkShift); f.Add(8,&mapMode); f.Add(9,&mapModeBase); f.Add(10,&mapModeBaseDynamic); f.Add(11,&mapModeCheck);  } return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MapModeChanger
{
private:
	int				prevMode;
	TileMap*	pTileMap;

public:
	MapModeChanger(int mode, TileMap* tileMap)
	{
		pTileMap = tileMap;
		prevMode = pTileMap->GetMode();
		pTileMap->SetMode(mode);
	}
	~MapModeChanger()
	{
		pTileMap->SetMode(prevMode);
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
