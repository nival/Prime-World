#pragma once

// ===================================================================
//
// Passability mask description.
//  Can be edied on AdvMap editor
// ===================================================================

// ===================================================================
// Includes
// ===================================================================

#include "stdafx.h"


#include "ScenePassabilityMask.h"


// ===================================================================
// Data
// ===================================================================

// Height difference, where cell means not passable
static const float NOT_PASSABLE_HEIGHT_DIF    = 2.0f;

// ===================================================================
// Methods
// ===================================================================

namespace NScene
{

ScenePassabilityMask::ScenePassabilityMask(int sizeX, int sizeY)
: m_width(sizeX),
  m_height(sizeY),
  m_mapResult(new CellType[sizeX * sizeY]),
  m_mapUser(new CellType[sizeX * sizeY]),
  m_mapObjects(new CellType[sizeX * sizeY]),
  m_mapHeights(new CellType[sizeX * sizeY])
{
  m_metersPerTile = 1.0f;
}


ScenePassabilityMask::~ScenePassabilityMask()
{
  // Automatically destroy m_mapXXX: this is ScoopedPtr
}

bool  ScenePassabilityMask::Allocate(int width, int height, float metersPerTile)
{
  CellType    *arr;
  int         i, num;
  
  
  m_width           = width;
  m_height          = height;
  m_metersPerTile   = metersPerTile;
  
  Reset(m_mapResult,  new CellType[width * height]);
  Reset(m_mapUser,    new CellType[width * height]);
  Reset(m_mapObjects, new CellType[width * height]);
  Reset(m_mapHeights, new CellType[width * height]);
  
  num = width * height;
  
  arr = Get(m_mapResult);
  for (i = 0; i < num; i++)
    arr[i] = (CellType)PASSABILITY_ENABLE;  // can be ENABLE, DISABLE
  arr = Get(m_mapUser);
  for (i = 0; i < num; i++)
    arr[i] = (CellType)PASSABILITY_FREE;    // can be FREE, ENABLE, DISABLE
  arr = Get(m_mapObjects);
  for (i = 0; i < num; i++)
    arr[i] = (CellType)PASSABILITY_ENABLE;  // can be ENABLE, DISABLE
  arr = Get(m_mapHeights);
  for (i = 0; i < num; i++)
    arr[i] = (CellType)PASSABILITY_ENABLE;  // can be ENABLE, DISABLE
  
  return true;
}

void  ScenePassabilityMask::SetCellUser(int x, int y, CellType val)
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    return;
  CellType    *arr = Get(m_mapUser);
  arr[ x + y * m_width ] = val;
}
void  ScenePassabilityMask::SetCellObjects(int x, int y, CellType val)
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    return;
  if (val != (CellType)PASSABILITY_ENABLE && val != (CellType)PASSABILITY_DISABLE)
    return;
  CellType    *arr = Get(m_mapObjects);
  arr[ x + y * m_width ] = val;
}
void  ScenePassabilityMask::SetCellHeights(int x, int y, CellType val)
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    return;
  if (val != (CellType)PASSABILITY_ENABLE && val != (CellType)PASSABILITY_DISABLE)
    return;
  CellType    *arr = Get(m_mapHeights);
  arr[ x + y * m_width ] = val;
}

void  ScenePassabilityMask::UpdateResultMap()
{
  CellType    *dest     = Get(m_mapObjects);
  CellType    *user     = Get(m_mapUser);
  CellType    *objects  = Get(m_mapObjects);
  CellType    *heights  = Get(m_mapHeights);
  CellType    result;
  int         i, num;
  
  num = m_width * m_height;
  for (i = 0; i < num; i++)
  {
    result = (*objects) | (*heights);
    if ( (*user) == PASSABILITY_ENABLE )
     result = PASSABILITY_ENABLE;
    if ( (*user) == PASSABILITY_DISABLE )
      result = PASSABILITY_DISABLE;
    *dest = result;
    
    dest++;
    user++;
    objects++;
    heights++;
  }
}


void  ScenePassabilityMask::ApplyHeightMap(::Terrain::Terrain *terrain)
{
  int     x, y, dx;
  float   h0;
  float   maxDelta;
  float   h1;
  float   dh;
  CArray2D<float> const &heights = terrain->GetHeightManager().GetHeightsAsFloat();
  
  for (x = 0; x < m_width; x++)
  {
    for (y = 0; y < m_height; y++)
    {
      // check adjacent cells
      h0 = heights[y][x];
      maxDelta = 0.0f;
      for (dx = -1; dx <= 1; dx++)
      {
        int x1 = x + dx;
        if (x1 < 0 || x1 >= m_width)
          continue;										// outside of the world
        for (int dy = -1; dy <= 1; dy++)
        {
          if (dx == 0 && dy == 0)
            continue;									// skip center point
          int y1 = y + dy;
          if (y1 < 0 || y1 >= m_height)
            continue;									// outside of the world
          h1 = heights[y1][x1];
          dh = fabs(h0 - h1);
          if (dh > maxDelta)
            maxDelta = dh;
        }
      }
      // analyze height difference
      if (maxDelta > NOT_PASSABLE_HEIGHT_DIF)
        SetCellHeights(x, y, PASSABILITY_DISABLE);
    }
  }
}

void  ScenePassabilityMask::ApplyObject(NDb::GameObject   *obj)
{
/*
	// this code is copy-pasted from NWorld::TileMap::MarkObject()
  if (!obj)
    return;
  const CTRect<float>& C = obj->collision;
  if (C.xMin >= C.xMax || C.yMin >= C.yMax)
    return;			// null area


  const NDb::PassabilityMask* mask = &obj->passabilityMask;
  int maskSizeX = 0, maskSizeY = 0;
  // verify passability mask
  maskSizeY = mask->mask.size();
  if (maskSizeY)
    maskSizeX = mask->mask[0].row.size();
  if (maskSizeX && maskSizeY)
  {
    for (int y = 1; y < maskSizeY; y++)
      if (mask->mask[y].row.size() != maskSizeX)
      {
        NI_VERIFY(false, "Mismatching mask sizeX between lines", ;);
        mask = NULL;
        break;
      }
  }
  else
  {
    mask = NULL;
  }
  // compute float->int scales
  // Vint = Vfloat * Va + Vb
  float Xa = 0, Xb = 0, Ya = 0, Yb = 0; // can be uninitialized, but silly compiler flags ...
  if (mask)
  {
    // Xint = floor(N * (Xfloat - Xmin) / (Xmax - Xmin))
    Xa = maskSizeX / (C.xMax - C.xMin);
    Xb = -maskSizeX * C.xMin / (C.xMax - C.xMin);
    Ya = maskSizeY / (C.yMax - C.yMin);
    Yb = -maskSizeY * C.yMin / (C.yMax - C.yMin);
  }
  
  // !!!!!!!!!!!!!!!!!!!!!!!!!
  // Need correct code
  // !!!!!!!!!!!!!!!!!!!!!!!!!
  
  Matrix43    place = IDENTITY_MATRIX;
  //Matrix43    place = obj->visualObject->cmplace;
  CVec3       pos;
  
  pos.x = place._14;
  pos.y = place._24;
  pos.z = place._34;
  
  int   x = (int)(pos.x / m_metersPerTile);
  int   y = (int)(pos.y / m_metersPerTile);
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    return;
  SetCellObjects(x, y, PASSABILITY_DISABLE);
*/
  /*
  const Placement &place = desc.place.GetPlace();
  // prepare ...
  float xPos = place.pos.x;
  float yPos = place.pos.y;
  // compute object position; code is based on PFSimpleObject.cpp, CreateSceneObject()
  Placement finalPlacement = NULLPLACEMENT;
  finalPlacement.pos   = CVec3(xPos, yPos, 0.0f);
  finalPlacement.rot   = CQuat(FP_PI2 * static_cast<float>(desc.orientation), CVec3(0.0f, 0.0f, 1.0f)) * place.rot;
  finalPlacement.scale = place.scale;
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
    point.x = (i & 1) ? C.xMin : C.xMax;
    point.y = (i & 2) ? C.yMin : C.yMax;
    point.z = 0.0f;
    // transform object-space corner coordinate to world
    point = Transform(point, M);
    // and expand bounds
    bMin.Minimize(point);
    bMax.Maximize(point);
  }
  // convert 'float' bounds to tiles
  int xMin = floor(bMin.x / tileSize);
  int xMax = ceil (bMax.x / tileSize);
  int yMin = floor(bMin.y / tileSize);
  int yMax = ceil (bMax.y / tileSize);
  // clamp by map size
  xMin = ClampFast(xMin, 0, width-1);
  xMax = ClampFast(xMax, 0, width-1);
  yMin = ClampFast(yMin, 0, height-1);
  yMax = ClampFast(yMax, 0, height-1);

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
        CVec3 origin((x + 0.5f) * tileSize, (y + 0.5f) * tileSize, 0.0f);
        origin += offsets[i];
        CVec3 projected = Transform(origin, M);
        // validate projected point; can use table lookup later
        if (projected.x < C.xMin || projected.x > C.xMax ||
          projected.y < C.yMin || projected.y > C.yMax)
          continue;			// point rejected
        // check mask
        if (mask)
        {
          // convert float position to cell index
          int maskX = floor(projected.x * Xa + Xb);
          int maskY = floor(projected.y * Ya + Yb);
          //				DebugTrace("mask=(%g,%g) -> %d,%d [%d,%d]", projected.x, projected.y, maskX, maskY, maskSizeX, maskSizeY);
          if (maskX < 0 || maskX >= maskSizeX ||
            maskY < 0 || maskY >= maskSizeY)
            continue;		// point rejected
          if (mask->mask[maskY].row[maskX] == false)
            continue;		// point is masked
        }
        // mark tile
        int v = GetItem(x, y);
        v = (v > 0) ? 0 : v-1;
        SetItem(x, y, MARK_BUILDING); //!! should use 'v'
        break;
      }
    }
  }
  */

}


} // namespace



