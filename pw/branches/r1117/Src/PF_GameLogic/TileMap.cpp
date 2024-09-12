#include "stdafx.h"
#include "TileMap.h"
#include "System/ImageTGA.h"
#include "System/LogFileName.h"
#include "System/InlineProfiler.h"



#define OPTIMIZED_UPDATE				1

namespace NWorld
{
// profiling
// 0 = do not smooth at all
// 1 = always smooth
// good value = 0.6f
static float g_tileSmooth = 0.0f;
static int   g_useRoundedUnits = 1; // 0 = none, 1 = all, 2 = use settings
static TileMap* g_tileMap = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Static class variables
///////////////////////////////////////////////////////////////////////////////////////////////////
static const float BLOCK_HEIGHT_SCALE = 1.0f; // in tile size units
///////////////////////////////////////////////////////////////////////////////////////////////////
// Useful macros
///////////////////////////////////////////////////////////////////////////////////////////////////
// d = (x < 0) ? 0 : -1
#define NOT_SIGN(x,d) \
	{ d = (((unsigned)(x))>>31)-1; }

// x = min(x,0)
#define CLAMP_MAX_ZERO(x) \
	{ int d; NOT_SIGN(x,d); x &= ~d; }

// x = max(x,0)
#define CLAMP_MIN_ZERO(x) \
	{ int d; NOT_SIGN(x,d); x &= d; }

// x = max(x,y)
#define CLAMP_MIN_VALUE(x,y) \
	{ int d; NOT_SIGN(x-(y),d); x = (x & d) | (y & ~d); }

// x = min(x,y)
#define CLAMP_MAX_VALUE(x,y) \
	{ int d; NOT_SIGN((y)-x,d); x = (x & d) | (y & ~d); }

// extend sign bit #'bit' in x
//?? 'bit' argument is always SIGN_BIT ?
#define EXTEND_SIGN(x,bit) \
	{ int s = (x & (1<<bit))-1; x |= ~s; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// Building rounded mark maps
///////////////////////////////////////////////////////////////////////////////////////////////////
static const int MIN_ROUNDED_SIZE = 4;

struct MapMarkData
{
	struct MarkPoint
	{
		SVector	pos;
		int			size;
	};

	BYTE			lines[MAX_UNIT_SIZE];
	MarkPoint	points[5];
};

static MapMarkData g_markMap[MAX_UNIT_SIZE - MIN_ROUNDED_SIZE + 1];

static __forceinline MapMarkData* GetMarkMapItem(int unitSize)
{
	return g_markMap + (unitSize - MIN_ROUNDED_SIZE);
}

static void BuildMarkMaps()
{
	if (g_markMap[0].points[0].size != 0)	// already computed
		return;

	int i;

	for (int d = MIN_ROUNDED_SIZE; d <= MAX_UNIT_SIZE; d++)
	{
		// get best approximation
		float S = sqr(d) * 0.83;	// 0.83 * d^2
		int bestA   = 0;
		int bestA2  = 0;
		float bestDelta = 1000000;
		for (int a = (d & 1) ? 1 : 2; a <= d; a += 2)
		{
			// approximation with 4 squares
			float S4 = 2 * d * a - sqr(a);
			for (int a2 = a; a2 < d; a2 += 2)
			{
				// approximation with 5 squares
				float S5 = S4 + sqr(a2 - a);
				float delta = fabs(S5 - S);
				if (delta < bestDelta)
				{
					bestA     = a;
					bestA2    = a2;
					bestDelta = delta;
				}
			}
		}

//		DebugTrace("size=%d:  a=%d  a2=%d", d, bestA, bestA2);

		// precompute data for fast query/mark
		MapMarkData* mark = GetMarkMapItem(d);
		// points ...
		/*
            +--+             -
            |  |             |
          +-+  +-+        -  |
          |      |        |  | d
        +-+      +-+   -  | bestA2
        |          |   | bestA
        +-+      +-+   -  |  |
          |      |        |  |
          +-+  +-+        -  |
            |  |             |
            +--+             -
        |-|    v3
        |<->|  v1
    */
		int v1 = (d - bestA) / 2;
		int v2 = d - bestA;
		int v3 = (d - bestA2) / 2;
		for (i = 0; i < 4; i++)
		{
			MapMarkData::MarkPoint &pt = mark->points[i];
			pt.size = bestA;
			switch (i)
			{
				case 0:
					pt.pos.x = 0;
					pt.pos.y = v1;
					break;
				case 1:
					pt.pos.x = v2;
					pt.pos.y = v1;
					break;
				case 2:
					pt.pos.x = v1;
					pt.pos.y = 0;
					break;
				case 3:
					pt.pos.x = v1;
					pt.pos.y = v2;
					break;
			}
		}
		if (bestA != bestA2)
		{
			// has 5th point
			MapMarkData::MarkPoint &pt = mark->points[4];
			pt.size  = bestA2;
			pt.pos.x = v3;
			pt.pos.y = v3;
		}
		// lines ...
		for (i = 0; i < v3    ; i++)
			mark->lines[i] = bestA;
		for (     ; i < v1    ; i++)
			mark->lines[i] = bestA2;
		for (     ; i < d - v1; i++)
			mark->lines[i] = d;
		for (     ; i < d - v3; i++)
			mark->lines[i] = bestA2;
		for (     ; i < d     ; i++)
			mark->lines[i] = bestA;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// TileMap class implementation
///////////////////////////////////////////////////////////////////////////////////////////////////

TileMap::TileMap( )
: width( 0 )
, height( 0 )
, tileSize( 1.0f )
, mapMode( 0 )
, mapModeBase( 0 )
, mapModeBaseDynamic( 0 )
, mapModeCheck( 0 )
{
}

TileMap::TileMap( PFWorld* pWorld )
: PFWorldObjectBase( pWorld, 0 )
, width( 0 )
, height( 0 )
, tileSize( 1.0f )
, mapMode( 0 )
, mapModeBase( 0 )
, mapModeBaseDynamic( 0 )
, mapModeCheck( 0 )
{
	SetMode(MAP_MODE_ALL);
	BuildMarkMaps();
	g_tileMap = this;
}

void TileMap::Prepare(int sizeX, int sizeY, float sizeOfTile)
{
  NI_PROFILE_FUNCTION

	// remember sizes
	width    = sizeX;
	height   = sizeY;
	tileSize = sizeOfTile;
	// reallocate arrays
  mapData.SetSizes( width + 1, height + 1 );
	// mark all cells as free (all layers)
	int i;
	CellType filler = 0;
	for (i = 0; i < NUM_LAYERS; i++)						// compute filling constant
		filler = (filler << LAYER_BITS) | MAX_UNIT_SIZE;
  mapData.FillEvery( filler );

  for (i = 0; i < width; i++)
	{
		SetCell(i, 0, 0);
		SetCell(i, height - 1, 0);
	}
	for (i = 0; i <= height; i++)	
	{
		SetCell(0, i, 0);
		SetCell(width - 1, i, 0);
	}
}

void TileMap::ApplyHeightMap(CArray2D<float> const& heights)
{
  NI_PROFILE_FUNCTION

	int oldMode = mapMode;
	SetMode(MAP_MODE_BUILDING);					// mark on building layer to not block visibility

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// check adjacent cells
			float h0 = heights.GetUnsafe(x, y); ///*/heights[y][x];
			float maxDelta = 0;
			for (int dx = -1; dx <= 1; dx++)
			{
				int x1 = x + dx;
				if (x1 < 0 || x1 >= width)
					continue;										// outside of the world
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0)
						continue;									// skip center point
					int y1 = y + dy;
					if (y1 < 0 || y1 >= height)
						continue;									// outside of the world
					float h1 = heights.GetUnsafe(x1, y1); ///*/ heights[y1][x1];
					float dh = fabs(h0 - h1);
					if (dh > maxDelta)
						maxDelta = dh;
				}
			}
			// analyze height difference
			if (maxDelta > tileSize * BLOCK_HEIGHT_SCALE)
				SetItem(x, y, 0);
		}
	}

	SetMode(oldMode);
}

void TileMap::OnLoaded()
{
  NI_PROFILE_FUNCTION

	// recompute passability for all map layers
	int oldMode = mapMode;
	for (int layer = 0; layer < NUM_LAYERS; layer++)
	{
		SetMode(1 << layer);
		UpdateMap();
	}
	SetMode(oldMode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// There is a few functions with access to mapData and relative to data storage format
///////////////////////////////////////////////////////////////////////////////////////////////////
// mapData cell format:
//
// CellType is split to NUM_LAYERS equal parts, LAYER_BITS each.
// Each value is treated as signed integer. Positive value means distance to nearest
// obstacle (equals maximal size of unit, which can stand here). Zero value means
// cell is blocked. Negative values means cell is blocked by a few obstacles (this is a
// valid situation).
///////////////////////////////////////////////////////////////////////////////////////////////////

void TileMap::SetMode(int newMode)
{
  if (newMode < 0 || newMode > __MAP_MODE_MAX)
    return;

	NI_STATIC_ASSERT(MAX_UNIT_SIZE <= LAYER_MASK>>1, MAX_UNIT_SIZE_is_too_large)
	mapMode = newMode;

	mapModeBase = 0;
	for (int base = 1, mode = mapMode; mode; base <<= LAYER_BITS, mode >>= 1)
  {
		if (mode & 1)
			mapModeBase |= base;
  }
	mapModeCheck = mapModeBase << (LAYER_BITS-1);	// sign for each layer
	mapModeBaseDynamic  = mapModeBase & 0xFF00FF00;										// 1 for each layer
	mapModeBase         = mapModeBase & 0x00FF00FF;										// 1 for each layer

	if ((mapMode & (mapMode-1)) == 0)
	{
		// get mode index (log2)
		int index = -1;
		for (int tempMode = newMode; tempMode; tempMode >>= 1)
			index++;
		// working with a single layer
		checkShift = LAYER_BITS * index;
		checkMask  = ~(LAYER_MASK << checkShift);
	}
	else
	{
		// should not modify map in this mode
		// just in case - set constants too
		checkShift = 0;
		checkMask  = 0;
	}
}

__forceinline int TileMap::GetItem(int x, int y) const
{
	int v = (GetCell(x, y) >> checkShift) & LAYER_MASK;
	EXTEND_SIGN(v, SIGN_BIT);
	return v;
}

__forceinline void TileMap::SetItem(int x, int y, int value)
{
  SetCell( x, y, GetCell(x, y) & checkMask | ((value & LAYER_MASK) << checkShift) );
}

/*-------------------------------------------------------------------------------------------------
Idea used in optimized TileMap::CanUnitGo():
--------------------------------------------
- prepare part is in TileMap::SetMode()
- algorithm: SIMD-like algorithm: using CellType value (currently this is int32) divided to NUM_LAYERS
    values (each value is LAYER_BITS)
  1) check sign bits for each layer - if 1 => cannot go
  2) subtract from "data" value of nTileSize placed into all selected layers (nTileSize*mapModeBase)
  3) if any of selected layers got negative value due to overflow - we cannot go: value in a layer
     is smaller than nTileSize
  4) of course, when (3) will give overflow, we will get damaged upper layer values, but it does
     not matter: we are checking for ANY negatove value, and we are got it on (3)
  5) step (1) is required for situation when cell is locked with multiple objects (value < 0)
     and we are trying to place here unit with some large size; example: cell=9 (-7), unit=2,
     cell-unit = 9-7 = 5 -- positive value!
- example:
  * mapMode is 5 (0101 binary)
  * nTileSize is 4
  * data from map is A407  (layer#3=A - negative, locked, layer#2=4 - free for unit size 4,
    layer#1=0 - locked, layer#0=7 - free for unit size 7
  - mapModeBase will be 101 (1 for selected layers)
  - mapModeCheck = 808 (sign bits for selected layers)
  - checking:
    - data & mapModeCheck = 0000 - all selected layers are ready to go (if non-zero value -
      one of selected layers has "value < 0" - no way to go)
    - data - nTileSize * mapModeBase = A407 - 404 = A003; AND mapModeCheck => 0000
  * let's suppose we have mapMode=9 (1001 binary):
    - data & mapModeCheck = 8000 - no way to go
  * let's check mapMode=5 and nTileSize=6
    - data & mapModeCheck = 0000
    - data - nTileSize * mapModeBase = A407 - 6 * 101 = A407 - 606 => here we will get negative
      value in layer #2, and after masking result with mapModeCheck we will get 0800 - cannot go
-------------------------------------------------------------------------------------------------*/

bool TileMap::CanUnitGo( int tileSize, int tileSizeDynamic, const SVector& tile ) const
{
  //This function may be called more than 115000 times. This is too heavy.
  //NI_PROFILE_HEAVY_FUNCTION

  if ( IsPointOutsideMap( tile.x, tile.y ) )
		return false;

  const CellType& data = GetCell( tile.x, tile.y );
  const int checkTileSize = tileSize * mapModeBase + tileSizeDynamic * mapModeBaseDynamic;
	const int check = (data | (data - checkTileSize)) & mapModeCheck;
  return check == 0;
}

bool TileMap::CanUnitGoDebug( int x, int y, int mode, int tileSize ) const
{
  if ( IsPointOutsideMap( x, y ) )
		return false;

	int modeBase = 0;
	for ( int base = 1; mode; base <<= LAYER_BITS, mode >>= 1 )
  {
		if ( mode & 1 )
			modeBase |= base;
  }
	int modeCheck = modeBase << (LAYER_BITS-1);

  const CellType& data = GetCell( x, y );
  const int checkTileSize = tileSize * modeBase;
	const int check = (data | (data - checkTileSize)) & modeCheck;
  return check == 0;
}

bool TileMap::CanUnitGoByDir( int tileSize, int tileSizeDynamic, const SVector& tile, const SVector& shift ) const
{
	const SVector tileToGo( tile + shift );
	if ( !CanUnitGo( tileSize, tileSizeDynamic, tileToGo ) )
    return false;
 
  if ( shift.x == 0 && shift.y == 0 )
    return true;

	SVector tile2;
	tile2.x = tileToGo.x;
	tile2.y = tile.y;
	if ( !CanUnitGo( tileSize, tileSizeDynamic, tile2 ) )
    return false;

  tile2.x = tile.x;
  tile2.y = tileToGo.y;
  return CanUnitGo( tileSize, tileSizeDynamic, tile2 );
}

int TileMap::GetStaticObject(int x, int y, int range)
{
	NI_STATIC_ASSERT(MAP_MODE_STATIC == 1, Code_Requires_Static_Layer_First)
	if (IsPointOutsideMap(x, y))
		return 1;						// outside the map
	const CellType& data = GetCell(x, y);
	int v = data & LAYER_MASK;
	EXTEND_SIGN(v, SIGN_BIT);
	if (v < range)
		return 1;						// tile is occupied by static-layer object (but not by terrain)
	return 0;							// tile is not occupied
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void TileMap::MarkObject(const vector<SVector> & tilesToMark, bool _lock, int _markMode)
{
	// setup layer to mark
	int oldMode = mapMode;
	SetMode(_markMode);

  int xMin = INT_MAX;
  int xMax = 0;
  int yMin = INT_MAX;
  int yMax = 0;

  for (int i = 0; i< tilesToMark.size(); i++)
  {
    int x = tilesToMark[i].x;
    int y = tilesToMark[i].y;

    xMin = min(x, xMin);
    yMin = min(y, yMin);

    xMax = max(x, xMax);
    yMax = max(y, yMax);

    // mark tile
    int v = GetItem(x, y);
		if (_lock)
			v = (v > 0) ? 0 : v - 1;
		else
			v = v + 1;
		SetItem(x, y, v);
  }
	
  UpdateMap(xMin - MAX_UNIT_SIZE, xMax + MAX_UNIT_SIZE, yMin - MAX_UNIT_SIZE, yMax + MAX_UNIT_SIZE);

  // restore working map layer
	SetMode(oldMode);
}


void TileMap::FillOccupiedTiles(vector<SVector> & tilesToMark, const CTRect<float>& _coll, const float _tileSize, const vector<CTPoint<int>>& _mask,
                         const Placement &_place,CTRect<int> *_pTileRect) const
{
  CTRect<float> C = _coll;
  if (C.x1 >= C.x2 || C.y1 >= C.y2)
    return;							// null area

  tilesToMark.reserve(_mask.size());
  int maskSizeX = 0, maskSizeY = 0;
  // compute float->int scales
  // Vint = Vfloat * Va + Vb
  float Xa = 0, Xb = 0, Ya = 0, Yb = 0;     // can be uninitialized, but silly compiler flags ...
  static AutoPtr<bool> expandedMask(NULL);  // static to not reallocate every time
  static int expandedMaskSize = 0;
  bool *xMask = Get(expandedMask);

  float myTileSize = _tileSize;
  NI_VERIFY(myTileSize > 0, "Bad myTileSize", myTileSize = 0.5f);
  // snap C.[x|y][Min|Max] to tile size
  C.x1 = floor(C.x1 / myTileSize) * myTileSize;
  C.y1 = floor(C.y1 / myTileSize) * myTileSize;
  C.x2 = ceil (C.x2 / myTileSize) * myTileSize;
  C.y2 = ceil (C.y2 / myTileSize) * myTileSize;

  if (!_mask.empty())
  {
    maskSizeX = (C.x2 - C.x1) / myTileSize;
    maskSizeY = (C.y2 - C.y1) / myTileSize;
    // Xint = floor(N * (Xfloat - Xmin) / (Xmax - Xmin))
    Xa =  maskSizeX / (C.x2 - C.x1);
    Xb = -maskSizeX * C.x1 / (C.x2 - C.x1);
    Ya =  maskSizeY / (C.y2 - C.y1);
    Yb = -maskSizeY * C.y1 / (C.y2 - C.y1);
    // expand mask: convert list of items to 2D-array of bool
    int size = maskSizeX * maskSizeY;
    if (size > expandedMaskSize)
    {
      expandedMaskSize = size;
      xMask = new bool[size];
			::Reset(expandedMask, xMask);
    }
    memset(xMask, 0, size);
    for (int item = 0; item < _mask.size(); item++)
    {
      const CTPoint<int> &v = _mask[item];
      int maskIndex = v.x + maskSizeX * v.y ;
      NI_DATA_VERIFY(v.x >= 0 && v.x < maskSizeX && v.y >= 0 && v.y < maskSizeY,
        NStr::StrFmt("Found bad lock mask: item(%d,%d)", v.x, v.y),
        continue
        )
        NI_VERIFY(maskIndex >= 0 && maskIndex < expandedMaskSize, "Bad expandedMaskSize?", continue); // just in case
      xMask[maskIndex] = true;
    }
  }

  // prepare ...
  float xPos = _place.pos.x;
  float yPos = _place.pos.y;
  // compute object position; code is based on PFSimpleObject.cpp, CreateSceneObject()
  Placement finalPlacement = NULLPLACEMENT;
  finalPlacement.pos   = CVec3(xPos, yPos, 0.0f);
  finalPlacement.rot   = _place.rot;
  finalPlacement.scale = _place.scale;
  // get matrix from finalPlacement
  Matrix43 M;
  finalPlacement.GetMatrix(&M);
  // compute object 2D bounds
  CVec3 bMin( 10000000,  10000000,  10000000);
  CVec3 bMax(-10000000, -10000000, -10000000);
  for (int i = 0; i < 4; i++)
  {
    // get local corner coordinate
    CVec3 point;
    point.x = (i & 1) ? C.x1 : C.x2;
    point.y = (i & 2) ? C.y1 : C.y2;
    point.z = 0.0f;
    // transform object-space corner coordinate to world
    point = Transform(point, M);
    // and expand bounds
    bMin.Minimize(point);
    bMax.Maximize(point);
  }
  // convert 'float' bounds to tiles
  int xMin = floor(bMin.x / tileSize);
  int xMax = floor(bMax.x / tileSize);
  int yMin = floor(bMin.y / tileSize);
  int yMax = floor(bMax.y / tileSize);
  // clamp by map size
  xMin = ClampFast(xMin, 0, width-1);
  xMax = ClampFast(xMax, 0, width-1);
  yMin = ClampFast(yMin, 0, height-1);
  yMax = ClampFast(yMax, 0, height-1);
 
  // if we have been requested for tile rect - fill it
  if (_pTileRect)
  {
    _pTileRect->x1 = xMin;
    _pTileRect->x2 = xMax;
    _pTileRect->y1 = yMin;
    _pTileRect->y2 = yMax;
  }

  // invert matrix for later use
  M = M.GetInversed();
  // mark tiles
  for (int y = yMin; y <= yMax; y++)
  {
    for (int x = xMin; x <= xMax; x++)
    {
      // check few points; first - tile center, later - corners
      static const CVec3 offsets[] =
      {
#define POINT(x,y)  CVec3(x * tileSize * 0.49f, y * tileSize * 0.49f, 0.0f)
        POINT(0,0), POINT(-1,-1), POINT(1,-1), POINT(-1,1), POINT(1,1)
#undef POINT
      };

      for (int i = 0; i < ARRAY_SIZE(offsets); i++)
      {
        CVec3 origin( x * tileSize, y * tileSize, 0.0f );
        origin += offsets[i];
        CVec3 projected = Transform(origin, M);
        // validate projected point; can use table lookup later
        if (projected.x < C.x1 || projected.x > C.x2 ||
          projected.y < C.y1 || projected.y > C.y2)
          continue;					// point rejected
        // check mask
        if (!_mask.empty())
        {
          // convert float position to cell index
          int maskX = floor(projected.x * Xa + Xb);
          int maskY = floor(projected.y * Ya + Yb);
          //				DebugTrace("mask=(%g,%g) -> %d,%d [%d,%d]", projected.x, projected.y, maskX, maskY, maskSizeX, maskSizeY);
          if (maskX < 0 || maskX >= maskSizeX ||
            maskY < 0 || maskY >= maskSizeY)
            continue;				// point rejected, check next offset
          // check mask
          if (!xMask[maskX + maskSizeX * maskY])
            continue;				// item not found, check next offset
        }
        tilesToMark.push_back(SVector(x,y));
        break; // no more offset tests
      }
    }
  }
}

void TileMap::UpdateMap(int x0, int x1, int y0, int y1)
{
  NI_PROFILE_FUNCTION
	// do not update map's borders
	x0 = ClampFast(x0, 1, width-2);
	x1 = ClampFast(x1, 1, width-2);
	y0 = ClampFast(y0, 1, height-2);
	y1 = ClampFast(y1, 1, height-2);

	for( int y = y0; y <= y1; ++y )
	{
		int left = GetItem( x0 - 1, y );
		CLAMP_MIN_ZERO( left );
		for( int x = x0; x <= x1; ++x )
		{
			int v0 = GetItem( x, y );
			if ( v0 > 0 )
			{
				int top = GetItem( x, y - 1 );
				CLAMP_MIN_ZERO( top );
				v0 = Min( MAX_UNIT_SIZE, Min( left, top ) + 1 );
				SetItem( x, y, v0 );
			}
			left = v0;
			CLAMP_MIN_ZERO( left );
		}
	}

	for( int y = y1; y >= y0; --y )
	{
		int right = GetItem( x1 + 1, y );
		CLAMP_MIN_ZERO( right );
		for( int x = x1; x >= x0; --x )
		{
			int v0 = GetItem( x, y );
			if ( v0 > 0 )
			{
				int bottom = GetItem( x, y + 1 );
				CLAMP_MIN_ZERO( bottom );
				v0 = Min( MAX_UNIT_SIZE, Min( v0, Min( right, bottom ) + 1 ) );
				SetItem( x, y, v0 );
			}
			right = v0;
			CLAMP_MIN_ZERO( right );
		}
	}
}


void TileMap::GetUnitUpdateRect(const CVec2 &pos, int size, int& xMin, int& xMax, int& yMin, int& yMax) const
{
	NI_VERIFY(size <= MAX_UNIT_SIZE, "Unit tile size is too large", size = MAX_UNIT_SIZE);

	float offset = size * tileSize / 2.0f;
	SVector tile = GetTile( CVec2( pos.x - offset, pos.y - offset ) );

	// truncate rect (just in case, unit should not go outside map if it is moved to valid map cell)
	xMin = Max(tile.x, 0);
	yMin = Max(tile.y, 0);
	xMax = Min(tile.x + size - 1, width - 1);
	yMax = Min(tile.y + size - 1, height - 1);
}

void TileMap::MarkUnitTiles(const CVec2 &pos, int size, bool blocked, bool rounded)
{
  int xMin, xMax, yMin, yMax;
	GetUnitUpdateRect(pos, size, xMin, xMax, yMin, yMax);

	switch (g_useRoundedUnits)
	{
	case 0:
		rounded = false;
		break;
	case 1:
		rounded = true;
		break;
	}

	if (!rounded || size < MIN_ROUNDED_SIZE)
	{
		if (blocked)
		{
			for (int y = yMin; y <= yMax; y++)
			{
				for (int x = xMin; x <= xMax; x++)
				{
					int v = GetItem(x, y);
					v = (v > 0) ? 0 : v-1;
					SetItem(x, y, v);
				}
			}
		}
		else
		{
			for (int y = yMin; y <= yMax; y++)
			{
				// mark as free if possible
				for (int x = xMin; x <= xMax; x++)
					SetItem(x, y, GetItem(x, y) + 1);
			}
		}
	}
	else
	{
		// will not work with smoothing (g_tileSmooth > 0)
		const MapMarkData* mark = GetMarkMapItem(size);
		for (int i = 0; i < size; i++)
		{
			int y = yMin + i;		/// ignore yMax
			int len = mark->lines[i];
			int xMin2 = xMin + (size - len) / 2;
			int xMax2 = xMin2 + len - 1;
			// mark/unmark
			if (blocked)
			{
				for (int x = xMin2; x <= xMax2; x++)
				{
					int v = GetItem(x, y);
					v = (v > 0) ? 0 : v-1;
					SetItem(x, y, v);
				}
			}
			else
			{
				// mark as free if possible
				for (int x = xMin2; x <= xMax2; x++)
					SetItem(x, y, GetItem(x, y) + 1);
			}
		}
	}

	// Recompute passability for affected tiles.
	// Should recompute 'MAX_UNIT_SIZE-1' cells toward zero and 'size-1' cells
	// toward 'map_size'.
	UpdateMap( xMin - MAX_UNIT_SIZE + 1, xMax + MAX_UNIT_SIZE - 1, yMin - MAX_UNIT_SIZE + 1, yMax + MAX_UNIT_SIZE - 1 );
}

bool TileMap::CheckCollision(const CVec2 &pos, int size) const
{
	int xMin, xMax, yMin, yMax;
	GetUnitUpdateRect(pos, size, xMin, xMax, yMin, yMax);

#ifdef TRICK_COLLISION_DETECTION

  int numRows = 0, numCols = 0;
  for (int y = yMin; y <= yMax; y++)
  {
    int count = 0;
    for (int x = xMin; x <= xMax; x++)
    {
      int v = GetItem(x, y);
      if (v < 0) count++;									// optimization: count += (v >> 31)
    }
    if (count)
    {
    	numCols = max(numCols, count);
    	numRows++;
    }
  }

  return (numRows > 1) && (numCols > 1);	// optimization: insert into outer loop (earlier loop termination)

#else

  for (int y = yMin; y <= yMax; y++)
  {
    for (int x = xMin; x <= xMax; x++)
    {
      if (GetItem(x, y) < 0)
        return true;
    }
  }
  return false;

#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TileMap::Dump( const char* fileName, int mapMode, const vector<SVector>* wayPoints /* = 0 */, const  vector<SVector>* wayPoints2 /* = 0 */)
{
	const int tileSize = 3;

  if ( mapMode == 0 )
    return;
  nstl::vector<int> mapModeShifts;
  mapModeShifts.reserve(NUM_LAYERS);
  
  //int mapModeShift = 0;
  
  for( int i = 0; i <= NUM_LAYERS; ++i)//, mapModeShift += LAYER_BITS )
  {
    if ( mapMode & 1 << i )
    {
      mapModeShifts.push_back(LAYER_BITS*i);
    }
  }

  NI_ASSERT(mapModeShifts.size(), "map types are not setted" );

  vector<Render::Color> colors( MAX_UNIT_SIZE + 1 );
  colors[MAX_UNIT_SIZE] = Render::Color( 0, 255, 0 );
  colors[MAX_UNIT_SIZE - 1] = Render::Color( 255, 255, 0 );
  colors[MAX_UNIT_SIZE - 2] = Render::Color( 255, 128, 0 );
  for( int i = 0; i < MAX_UNIT_SIZE - 2; ++i )
    colors[i] = Render::Color( i * 255 / ( MAX_UNIT_SIZE - 2 ), 0, 0 );

  CArray2D<Render::Color> image( width * tileSize - 1, height * tileSize - 1 );
  image.FillZero();
  for( int y = 0; y < height; ++y )
  {
    for( int x = 0; x < width; ++x )
    {
      int data = MAX_UNIT_SIZE;// by default its max size
      for (int i=0; i<mapModeShifts.size(); i++)
      {
        int curData = ( GetCell( x, y ) >> mapModeShifts[i]) & LAYER_MASK;
        EXTEND_SIGN( curData, SIGN_BIT );
        curData= Clamp( curData, 0, MAX_UNIT_SIZE );
        data = min (curData, data);
      }
      int inverseY = height -1 -y;
      for( int y1 = inverseY * tileSize; y1 < inverseY * tileSize + tileSize - 1; ++y1 )
      {
        for( int x1 = x * tileSize; x1 < x * tileSize + tileSize - 1; ++x1 )
          image[y1][x1] = colors[data];
      }
    }
  }

  if (wayPoints)
  {
    Render::Color wayColor = Render::Color( 255, 255, 255 );

    for ( vector<SVector>::const_iterator it = wayPoints->begin(); it != wayPoints->end(); ++it )
    {
      int inverseY = height -1 - it->y;
      for( int y1 = inverseY * tileSize; y1 < inverseY * tileSize + tileSize - 1; ++y1 )
      {
        for( int x1 = it->x * tileSize; x1 < it->x * tileSize + tileSize - 1; ++x1 )
          image[y1][x1] = wayColor;
      }
    }
  }

  if (wayPoints2)
  {
    Render::Color wayColor = Render::Color( 0, 0, 255 );

    for ( vector<SVector>::const_iterator it = wayPoints2->begin(); it != wayPoints2->end(); ++it )
    {
      for( int y1 = it->y * tileSize; y1 < it->y * tileSize + tileSize - 1; ++y1 )
      {
        for( int x1 = it->x * tileSize; x1 < it->x * tileSize + tileSize - 1; ++x1 )
          image[y1][x1] = wayColor;
      }
    }
  }

  CObj<Stream> file = new FileStream( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
  NImage::WriteImageTGA( file, image );
}

bool DumpTileMap( const char *name, const vector<wstring> &params )
{
	if ( !g_tileMap )
		return true;

	g_tileMap->Dump( NDebug::GenerateDebugFileName( "dynamic", "tga" ).c_str(), MAP_MODE_DYNAMIC );
	g_tileMap->Dump( NDebug::GenerateDebugFileName( "idle", "tga" ).c_str(), MAP_MODE_IDLE );
  g_tileMap->Dump( NDebug::GenerateDebugFileName( "building", "tga" ).c_str(), MAP_MODE_BUILDING );
  g_tileMap->Dump( NDebug::GenerateDebugFileName( "static", "tga" ).c_str(), MAP_MODE_STATIC );

	return true;
}

REGISTER_DEV_VAR( "tile_smooth", g_tileSmooth, STORAGE_NONE );
REGISTER_DEV_VAR( "rounded_units", g_useRoundedUnits, STORAGE_NONE );
REGISTER_DEV_CMD( dump_tilemap, DumpTileMap );
} // namespace

REGISTER_WORLD_OBJECT_NM(TileMap, NWorld)
