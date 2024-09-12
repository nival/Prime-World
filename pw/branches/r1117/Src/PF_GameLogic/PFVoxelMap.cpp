#include "stdafx.h"

#include "TileMap.h"
#include "PFVoxelMap.h"

#include "../System/InlineProfiler.h"

//#if !defined(_TESTRUN)
#include "PFBaseUnit.h"
//#endif

namespace NWorld
{

namespace
{
float const s_VoxelSize     = 10.0f; // in meters
float const s_VoxelSizeInv  = (1.0f / s_VoxelSize);

float const s_SQRT_TWO_INV  = (1.f / sqrt(2.0f));
float const s_MAP_EPS       = 0.001f;
}
//////////////////////////////////////////////////////////////////////////
PFLogicObject* PFVoxelMap::SelectObjects::Cast(PFLogicObject* obj) 
{ 
  return obj; 
}
//////////////////////////////////////////////////////////////////////////
PFBaseUnit* PFVoxelMap::SelectUnits::Cast(PFLogicObject* obj) 
{ 
  return static_cast<PFBaseUnit *>(obj); 
}

//////////////////////////////////////////////////////////////////////////
PFVoxelMap::PFVoxelMap( PFWorld* world )
: PFWorldObjectBase( world, 0 )
, width(0)
, height(0)
, widthF(0.0f)
, heightF(0.0f)
{
}

//////////////////////////////////////////////////////////////////////////
PFVoxelMap::PFVoxelMap( )
: width(0)
, height(0)
, widthF(0.0f)
, heightF(0.0f)
{
}

//////////////////////////////////////////////////////////////////////////
void PFVoxelMap::SetVoxelMapSizes(const TileMap *map)
{
  NI_PROFILE_FUNCTION

  NI_ASSERT(map != NULL, "No tile map");

  widthF  = float(map->GetSizeX()) * map->GetTileSize();
  heightF = float(map->GetSizeY()) * map->GetTileSize();

  width   = ceil(widthF * s_VoxelSizeInv);
  height  = ceil(heightF * s_VoxelSizeInv);
  NI_ASSERT(width > 0 && height > 0, "Invalid tile map sizes!");

  // correct real width and height so that evey point in bbox will map to some voxel
  widthF  -= s_MAP_EPS;
  heightF -= s_MAP_EPS;

  // allocate and fill voxels
  pVoxels.resize(width * height);
}
void PFVoxelMap::OnUnitMove(PFBaseUnit &unit)
{
  NI_PROFILE_FUNCTION
  
  // remove from ring
  RemoveObject(unit);
  //PFLogicObject::LORing::remove(static_cast<PFLogicObject *>(&unit));
  // add to ring
  AddObject(unit);
}
//////////////////////////////////////////////////////////////////////////
bool PFVoxelMap::IsPointInRange(const CVec3 &pos, const Range &range)
{
  float xs = pos.x - range.center.x;
  float ys = pos.y - range.center.y;
  return ((xs * xs + ys * ys) <= range.radiusSquared);
}
//////////////////////////////////////////////////////////////////////////
void PFVoxelMap::CalcVoxelIndices(float x, float y, int &voxelI, int &voxelJ)
{
  voxelI = floor(x * s_VoxelSizeInv);
  voxelJ = floor(y * s_VoxelSizeInv);
}
//////////////////////////////////////////////////////////////////////////
PFVoxelMap::Voxel &PFVoxelMap::GetVoxel(PFLogicObject &obj)
{
  const CVec3 &pos = obj.GetPosition();
  int i = floor(pos.x * s_VoxelSizeInv);
  int j = floor(pos.y * s_VoxelSizeInv);

  NI_ASSERT(0 <= i && i < width && 0 <= j && j < height, "Wrong obj coordinates");
  return GetVoxel(i, j);
}
//////////////////////////////////////////////////////////////////////////
PFVoxelMap::Voxel &PFVoxelMap::GetVoxel(int i, int j)
{
  NI_ASSERT(0 <= i && i < width && 0 <= j && j < height, "Wrong voxel coordinates");
  return pVoxels[j * height + i];
}
const PFVoxelMap::Voxel &PFVoxelMap::GetVoxel(int i, int j) const
{
  NI_ASSERT(0 <= i && i < width && 0 <= j && j < height, "Wrong voxel coordinates");
  return pVoxels[j * height + i];
}
//////////////////////////////////////////////////////////////////////////
PFVoxelMap::Voxel &PFVoxelMap::GetVoxel(int linearI)
{
  NI_ASSERT(0 <= linearI && linearI < width * height, "Wrong voxel coordinates");
  return pVoxels[linearI];
}
const PFVoxelMap::Voxel &PFVoxelMap::GetVoxel(int linearI) const
{
  NI_ASSERT(0 <= linearI && linearI < width * height, "Wrong voxel coordinates");
  return pVoxels[linearI];
}

//////////////////////////////////////////////////////////////////////////
template <class RingT> void PFVoxelMap::insertSorted(RingT &r, PFLogicObject *o)
{
  PFLogicObject * const last = r.last();
  for (PFLogicObject * current = r.first(); current != last; current = RingT::next(current))
  {
    if(current->GetObjectId() > o->GetObjectId())
    {
      r.insertBefore(o, current);
      return;
    }
  }
  // in case ring in empty or we have not found proper place
  r.addLast(o);
}
//////////////////////////////////////////////////////////////////////////
void PFVoxelMap::AddObject(PFLogicObject &obj)
{
  // test for borders
  int i, j;
  CalcVoxelIndices(obj.GetPosition().x, obj.GetPosition().y, i, j);
  NI_DATA_VERIFY(0 <= i && i < width && 0 <= j && j < height, NStr::StrFmt("Object at (%6.2f, %6.2f) should be moved to fit inside map", obj.GetPosition().x, obj.GetPosition().y), return);

  // add to ring
  PFLogicObject *p = &obj;
  NI_ASSERT(p != NULL, "Logic failed!");
  PFLogicObject::LORing &r = GetVoxel(obj).objectsRing;
  insertSorted(r, p);
}
//////////////////////////////////////////////////////////////////////////
void PFVoxelMap::AddObject(PFBaseUnit &unit)
{
  // test for borders
  int i, j;
  CalcVoxelIndices(unit.GetPosition().x, unit.GetPosition().y, i, j);
  NI_DATA_VERIFY(0 <= i && i < width && 0 <= j && j < height, NStr::StrFmt("Unit at (%6.2f, %6.2f) should be moved to fit inside map", unit.GetPosition().x, unit.GetPosition().y), return);

  // add to ring
  PFBaseUnit *p = &unit;
  NI_ASSERT(p != NULL, "Logic failed(2)!");
  PFLogicObject::LORing &r = GetVoxel(unit).unitsRing;
  insertSorted(r, p);
}
//////////////////////////////////////////////////////////////////////////
// This function is similar for PFLogicObject and PFBaseUnit
void PFVoxelMap::RemoveObject(PFLogicObject &obj)
{
  ringElemRemovalHandler.OnRemove( &obj );

  PFLogicObject::LORing::remove(&obj);
}
//////////////////////////////////////////////////////////////////////////

BBox2D PFVoxelMap::ConvertRangeToBBox(CVec3 const& vPos, float range) const
{
  BBox2D bbox; // don't initialize
  
  NI_ASSERT( range > 0.0f, "Bad practice: calculating BBox with range 0.0!" );
  // work with range as with an inscribed circle
  bbox.minx = max(vPos.x - range, 0.0f);
  bbox.miny = max(vPos.y - range, 0.0f);
  bbox.maxx = min(vPos.x + range, widthF);
  bbox.maxy = min(vPos.y + range, heightF);

  return bbox;
}

//////////////////////////////////////////////////////////////////////////
void PFVoxelMap::OnDestroyContents()
{
  for (int i = 0, count = width * height; i < count; ++i)
  {
    Clear(pVoxels[i].objectsRing);
    Clear(pVoxels[i].unitsRing);
  }
}

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFVoxelMap, NWorld);
