#include "stdafx.h"
#include "NatureMap.h"
#include "../System/lerp.h"
#include "../System/Crc32Checksum.h"
#include "../Render/debugrenderer.h"
#include "System/BinSaver.h"

#include "System/InlineProfiler.h"

#define SLICES_PER_SEGMENT 10

DEV_VAR_STATIC bool g_showAttackSpace = false;
DEV_VAR_STATIC bool g_showNatureMap = false;


namespace Terrain
{

namespace
{
  // split number into integer and POSITIVE fraction
  static int FloorAndFrac(float x, float* fraction)
  {
    ASSERT(fraction != 0);
    float xfloor = floorf(x);
    *fraction = x - xfloor;
    return (int)xfloor;
  }

  template <class T>
  void addChecksum(Crc32Checksum& crc, vector<T> const& v)
  {
    crc.Add(reinterpret_cast<unsigned char const*>(&v.front()), v.size() * sizeof(T));
  }

  void addChecksum(Crc32Checksum& crc, NDb::DBNatureMapRoad const& road)
  {
    crc.Add(road.leftWidth);
    crc.Add(road.centerWidth);
    crc.Add(road.rightWidth);
    addChecksum(crc, road.nodes);
  }

  unsigned long buildChecksum(const NDb::DBNatureMap& dbNatureMap, const CVec3& worldSize)
  {
    Crc32Checksum crc;
    crc.Add(worldSize.x).Add(worldSize.y).Add(dbNatureMap.gridStep);
    crc.Add(dbNatureMap.segmentCount);
    for (int i = 0, n = dbNatureMap.attackSpaceRoads.size(); i < n; i++)
      addChecksum(crc, dbNatureMap.attackSpaceRoads[i]);
    for (int i = 0, n = dbNatureMap.logicRoads.size(); i < n; i++)
      addChecksum(crc, dbNatureMap.logicRoads[i]);
    crc.Add(dbNatureMap.baseA).Add(dbNatureMap.baseAOffset);
    crc.Add(dbNatureMap.baseB).Add(dbNatureMap.baseBOffset);
    crc.Add(sizeof(NatureMapElementInfo));
    crc.Add(NatureMapElementInfo::VERSION);
    return crc.Get();
  }

  void MinMax(int& a, int& b)
  {
    if (a > b)
    {
      int c = a;
      a = b;
      b = c;
    }
  }

  void MinMax(int& outMin, int& outMax, int a, int b, int c, int d)
  {
    MinMax(a, b);
    MinMax(c, d);
    outMin = Min(a, c);
    outMax = Max(b, d);
  }

} // anonymous namespace

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMap::NatureMap(bool editable_)
: editable(editable_)
, xCount(0)
, yCount(0)
, roadsStep(0.0f)
, overridesAdded(0)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMap::~NatureMap()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::Initialize(NatureMapParams const& params_, NatureMapElementIdList *modifiedElemsListener)
{
  NI_VERIFY(params_.pDBNatureMap, "Database object is missing", return false);
  worldSize = params_.worldSize;

  dbNatureMap = *params_.pDBNatureMap;
  modifiedElems = modifiedElemsListener;

  ResetImpl();
  
  // try to load data first
  bool loadOk = false;
  CObj<Stream> pStream = RootFileSystem::OpenFile(dbNatureMap.natureMapFile, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
  if (pStream)
    loadOk = OnLoad(pStream, -1, false);

  if( IsValid( pStream ) )
    pStream->Close();

  // otherwise create if allowed to
  bool createOk = false;
  if (!loadOk && editable)
    createOk = OnCreate();

  return loadOk || createOk;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::Save(nstl::string const& name) const
{
  ASSERT(editable);

  bool saveOk = false;
  CObj<Stream> pStream = RootFileSystem::OpenFile(name, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
  if (pStream)
    saveOk = OnSave(pStream, false);

  MessageTrace( "NatureMap::Save done" );
  return saveOk;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::InitElement(NatureMapElementId id, NatureMapElementInfo& info)
{
  CVec2 pos;
  GetElementPosition(id, pos);
  info.attackPos = attackSpace.FindCoordinatesAS(pos);
  info.ownerData = 0;
  info.natureCur = GetNaturePrecise(info.attackPos);
  info.natureBase = info.natureOld = info.natureCur;
  MarkAsModified(id, info);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::OnCreate()
{
  checksum = buildChecksum(dbNatureMap, worldSize);

  ASSERT(editable);
  bool createOk = attackSpace.Create(dbNatureMap, worldSize);

  ForAllElements(this, &NatureMap::InitElement);

  InitSortedList();

  return createOk;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::OnLoad( Stream* pStream, int fraction, bool fromRecconect )
{
  for (int roadIndex = 0; roadIndex < dbNatureMap.attackSpaceRoads.size(); roadIndex++)
  {
    if ( dbNatureMap.attackSpaceRoads[roadIndex].nodes.empty() || dbNatureMap.attackSpaceRoads[roadIndex].centerWidth <= 1 )
      continue;

    validRoads.push_back(roadIndex);
  }

  ASSERT(pStream);
  checksum = buildChecksum(dbNatureMap, worldSize);
  unsigned long storedCRC = 0xBAADF00D;
  pStream->Read(&storedCRC, sizeof(storedCRC));
  if (checksum != storedCRC)
  {
    systemLog( NLogg::LEVEL_ASSERT ) << "Ignoring stored NatureAttackSpace binary data because of CRC32 mismatch." << endl;
    return false;
  }

  bool loadOk = attackSpace.Load(dbNatureMap, pStream);

  if ( fromRecconect )
  {
    nstl::vector<ReconnectElemInfo> smallVector( elemList.size() );
    int length = smallVector.size() * sizeof(ReconnectElemInfo);

    int bytesRead = pStream->Read(&smallVector[0], length);
    NI_VERIFY(bytesRead == length, "Unable to load entire nature map data", return false);

    for ( int i = 0; i < elemList.size(); ++i )
    {
      elemList[i].ownerData = smallVector[i].ownerData;
      elemList[i].natureCur = smallVector[i].natureCur;
      elemList[i].natureOld = smallVector[i].natureOld;
      elemList[i].natureBase = smallVector[i].natureBase;
    }

  }
  else
  {
    //ForAllElements(this, &NatureMap::InitElement);
    int numElems = GetSizeX() * GetSizeY();
    elemList.resize(numElems);
    int length = numElems * sizeof(NatureMapElementInfo);
    int bytesRead = pStream->Read(&elemList[0], length);
    NI_VERIFY(bytesRead == length, "Unable to load entire nature map data", return false);
  }

  InitSortedList();

  ForAllElements(this, &NatureMap::MarkAsModified);

  return loadOk;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::LoadAtRuntime( Stream* pStream, bool fromRecconect )
{
  ResetImpl();
  OnLoadAtRuntime( pStream, -1, fromRecconect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::OnSave( Stream* pStream, bool fromRecconect ) const
{
  NI_PROFILE_FUNCTION

  unsigned long checkSum = buildChecksum(dbNatureMap, worldSize);
  ASSERT(pStream);
  pStream->Write(&checkSum, sizeof(checkSum));

  bool saveOk = attackSpace.Save(pStream);

  if ( fromRecconect )
  {
    nstl::vector<ReconnectElemInfo> smallVector( elemList.size() );

    for ( int i = 0; i < elemList.size(); ++i )
    {
      smallVector[i].ownerData = (elemList[i].ownerData != 0) ? 1 : 0;
      smallVector[i].natureCur = elemList[i].natureCur;
      smallVector[i].natureOld = elemList[i].natureOld;
      smallVector[i].natureBase = elemList[i].natureBase;
    }

    int length = elemList.size() * sizeof(ReconnectElemInfo);
    int bytesWritten = pStream->Write(&smallVector[0], length);
    NI_VERIFY(bytesWritten == length, "Unable to save nature map data", return false);
  }
  else
  {
    int length = elemList.size() * sizeof(NatureMapElementInfo);
    int bytesWritten = pStream->Write(&elemList[0], length);
    NI_VERIFY(bytesWritten == length, "Unable to save nature map data", return false);
  }

  return saveOk;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::SaveAtRuntime( Stream* pStream, bool fromRecconect ) const
{
  OnSaveAtRuntime( pStream, fromRecconect );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMapElementId NatureMap::LocateElement(float x, float y) const
{
  // project on square grid
  float ifrac = 0.0f, jfrac = 0.0f;
  int i = FloorAndFrac(y / dbNatureMap.gridStep, &ifrac);
  int j = FloorAndFrac(x / dbNatureMap.gridStep, &jfrac);

  // adjust coordinates to enclosing hexagon's (top left border is included)
  if (i & 1)
  {
    i++;
    if (ifrac <= 1.0f - Max(jfrac, 1.0f - jfrac) * 2.0f / 3.0f)
      i--;
    else if (jfrac >= 0.5f)
      j++;
  }
  else
  {
    if (ifrac > Max(jfrac, 1.0f - jfrac) * 2.0f / 3.0f)
      i++;
    else if (jfrac >= 0.5f)
      j++;
  }

  if (i < 0 || i >= (int)yCount || j < 0 || j >= (int)xCount)
    return NATUREMAPELEMENTID_BAD;

  return LocateElement((unsigned)i, (unsigned)j);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::GetElementPosition(NatureMapElementId id, CVec2& pos) const
{
  unsigned i = GetElementRow(id);
  unsigned j = GetElementColumn(id);
  pos.Set(0.5f * (float)(2 * j + (i & 1)) * dbNatureMap.gridStep, (float)i * dbNatureMap.gridStep);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::GetElementBounds(NatureMapElementId id, Render::AABB& aabb) const
{
  CVec2 pos;
  GetElementPosition(id, pos);
  aabb.center.Set(pos.x, pos.y, 0.0f);
  aabb.halfSize.Set(0.5f * dbNatureMap.gridStep, 2.0f * dbNatureMap.gridStep / 3.0f, 0.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::IsAtBase(float x, float y) const
{
  NatureMapElementId const id = LocateElement( x, y );
  if( NATUREMAPELEMENTID_BAD == id )
    return false;
  
  CVec2 const& pos = GetElementInfo( id ).attackPos;
  return (pos.x < 0 || pos.x > attackSpace.GetNumSegments());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMapElementInfo& NatureMap::GetElementInfo(NatureMapElementId id)
{
  ASSERT(id < NatureMapElementId(GetSizeX()*GetSizeY()));
  if ( overrideElementInfo )
    return *overrideElementInfo;
  return elemList[ id ];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NatureMapElementInfo const& NatureMap::GetElementInfo(NatureMapElementId id) const
{
  ASSERT(id < NatureMapElementId(GetSizeX()*GetSizeY()));
  if ( overrideElementInfo )
    return *overrideElementInfo;
  return elemList[ id ];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::SetDesiredPosition(NDb::ENatureType faction, NDb::ENatureRoad roadIndex, int segment)
{
  systemLog( NLogg::LEVEL_DEBUG ) << "Nature map advance, " << NDb::EnumToString(faction) << " on " << NDb::EnumToString(roadIndex) << " targeted at " << segment << endl;

  // faction
  int id = faction - 1;
  NI_ASSERT(id == 0 || id == 1, NStr::StrFmt("Faction converted to array index is expected to be either 0 or 1, not %i (%s).", id, NDb::EnumToString(faction)));
  // road
  NI_ASSERT(0 <= roadIndex && roadIndex < ARRAY_SIZE(roads), NStr::StrFmt("Road index must be between 0 and %u, not %i (%s)", ARRAY_SIZE(roads), roadIndex, NDb::EnumToString(roadIndex)));
  RoadProgress::Border* borders = roads[roadIndex].borders;
  // segment
  int numSegments = attackSpace.GetNumSegments();
  NI_ASSERT(-1 <= segment && segment <= numSegments, NStr::StrFmt("Segment index must be between -1 and %i, not %i.", numSegments, segment));

  systemLog( NLogg::LEVEL_DEBUG ) << "Nature map state, "
    "A @ " << borders[0].last << "->" << borders[0].position << "->" << borders[0].target << ", " << 
    "B @ " << borders[1].last << "->" << borders[1].position << "->" << borders[1].target << endl;

  // set new target line
  int targetSegment;

  if (id)
  {
    targetSegment = numSegments - segment;  // For elf
  }
  else
  {
    targetSegment = segment;  // For humans

    // Shift segment one step forward, if not the first or the last segment. NUM_TASK
    if (segment > 0 && segment < numSegments)
    {
      ++targetSegment;
    }
  }

  borders[id].target = SLICES_PER_SEGMENT * targetSegment;

  // check the opposite faction and force it to be correct (borders should not overlap)
  NI_ASSERT(borders[id].target + borders[!id].target <= numSegments * SLICES_PER_SEGMENT,
    NStr::StrFmt("Nature borders conflict, '%s' is targeted at %i while the other is at segment %i.", 
    NDb::EnumToString(faction), segment, (!id ? numSegments - borders[!id].target / SLICES_PER_SEGMENT : borders[!id].target / SLICES_PER_SEGMENT)));
  borders[!id].target = Min(borders[!id].target, numSegments * SLICES_PER_SEGMENT - borders[id].target);

  // drop the leftover // why? [7/5/2010 smirnov]
  roadsStep = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::Attack(NDb::ENatureType faction, NDb::ENatureRoad roadIndex, int numSegments)
{
  NI_ALWAYS_ASSERT("Obsolete method NatureMap::Attack is called. The caller must be refactored according to new design.");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::ApplyOverride(NatureOverrideElement const &ovr)
{
  NatureMapElementInfo& info = GetElementInfo(ovr.id);
  info.natureOld = info.natureCur;
  info.natureCur = ovr.data.nature; // doesn't matter if it changed or not
  info.ownerData = ovr.data.ownerData;
  MarkAsModified(ovr.id, info);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::ExpireOverride(NatureOverrideElement const &ovr)
{
  NatureMapElementInfo& info = GetElementInfo(ovr.id);
  info.natureOld = info.natureCur;
  info.natureCur = info.natureBase; // restore original, even if it's the same
  info.ownerData = 0;
  MarkAsModified(ovr.id, info);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::OverrideInternal(NatureMapElementId id, NDb::ENatureType faction, float timeToApply, float lifeTime, unsigned ownerData)
{
  NatureOverrideElement &ovr = overrideElements.push_back();

  ovr.id = id;
  ovr.data.nature = faction;
  ovr.timeToApply = timeToApply;
  ovr.data.timeSpan = lifeTime;
  ovr.data.ownerData = ownerData;

  overridesAdded++;

  // if no delay apply immediately
  if (ovr.timeToApply <= 0.f)
  {
    ApplyOverride(ovr);
  }
}


void NatureMap::UnOverrideInternal(NatureMapElementId id, unsigned ownerData)
{
  for (int i = 0; i < overrideElements.size(); ++i)
  {
    NatureOverrideElement & elem = overrideElements[i];
    if (overrideElements[i].id == id)
    {
      if (elem.data.ownerData == ownerData)
      {
        // Just set the timer to zero so it will expire naturally
        elem.data.timeSpan = 0.0f;
      }
      else
      {
        // Well the override is probably inactive - find and remove
        for (TInactiveStak::iterator it = elem.inactiveStack.begin(); it != elem.inactiveStack.end(); ++it)
        {
          if (it->ownerData == ownerData)
          {
            elem.inactiveStack.erase(it);
            break;
          }
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::Override(NDb::ENatureType faction, const CCircle & circle, float lifeTime, unsigned ownerData)
{
  NatureOverride newOverrideData;
  newOverrideData.faction = faction;
  newOverrideData.circle = circle;
  newOverrideData.lifeTime = lifeTime;

  for (TOverrides::iterator it = overrides.begin(); it != overrides.end(); )
  {
    if (it->second.faction != faction && it->second.circle.IsIntersected(circle))
    {
      UnOverride(it->second, it->first);
      overrides.erase(it++);
    }
    else
    {
      ++it;
    }
  }
  overrides.insert(make_pair(ownerData, newOverrideData));

  // get rough estimate of the area
  CTRect<float> rect;
  newOverrideData.GetBounds(rect);
  if (rect.IsEmpty())
    return;

  // clip by world size
  rect.Intersect(CTRect<float>(VNULL2, worldSize.AsVec2D()));
  rect *= 1.0f / dbNatureMap.gridStep;

  // some quick consts
  static const float ONE_THIRD  = 1.0f / 3.0f;
  static const float TWO_THIRDS = 2.0f / 3.0f;
  static const float ONE_SIXTH  = 1.0f / 6.0f;

  // even/odd hexmap line boundaries
  unsigned imins[] = {2 * (unsigned)(0.5f * rect.miny + TWO_THIRDS), 1 + 2 * (unsigned)(0.5f * rect.miny + ONE_SIXTH)};
  unsigned imaxs[] = {2 * (unsigned)(0.5f * rect.maxy + ONE_THIRD), 1 + 2 * (unsigned)(0.5f * rect.maxy - ONE_SIXTH)};
  unsigned jmins[] = {(unsigned)(rect.minx + 0.5f), (unsigned)(rect.minx)};
  unsigned jmaxs[] = {(unsigned)(rect.maxx + 0.5f), (unsigned)(rect.maxx)};

  // process all lines
  unsigned imin = Min(imins[0], imins[1]);
  unsigned imax = Max(imaxs[0], imaxs[1]);
  for (unsigned i = imin; i <= imax; i++)
  {
    unsigned jmin = jmins[i & 1];
    unsigned jmax = jmaxs[i & 1];
    NatureMapElementId id = LocateElement(i, jmin);
    for (unsigned j = jmin; j <= jmax; j++, id++)
    {
      CVec2 pos;
      GetElementPosition(id, pos);
      if (newOverrideData.IsInside(pos))
      {
        float startDelay = 0.f;
        if (dbNatureMap.overrideSpeed > 1e-5f)
        {
          startDelay = fabs(pos - circle.center) / dbNatureMap.overrideSpeed;
        }

        float life = lifeTime - startDelay;
        if (life > 0.f)
        {
          OverrideInternal(id, faction, startDelay, life, ownerData);
        }
      }
    }
  }
}

void NatureMap::UnOverride(NatureOverride overrideData, unsigned int id)
{
  CVec2 center = overrideData.circle.center;
  float lifeTime = overrideData.lifeTime;
  unsigned ownerData = id;

  // get rough estimate of the area
  CTRect<float> rect;
  overrideData.GetBounds(rect);
  if (rect.IsEmpty())
    return;

  // clip by world size
  rect.Intersect(CTRect<float>(VNULL2, worldSize.AsVec2D()));
  rect *= 1.0f / dbNatureMap.gridStep;

  // some quick consts
  static const float ONE_THIRD  = 1.0f / 3.0f;
  static const float TWO_THIRDS = 2.0f / 3.0f;
  static const float ONE_SIXTH  = 1.0f / 6.0f;

  // even/odd hexmap line boundaries
  unsigned imins[] = {2 * (unsigned)(0.5f * rect.miny + TWO_THIRDS), 1 + 2 * (unsigned)(0.5f * rect.miny + ONE_SIXTH)};
  unsigned imaxs[] = {2 * (unsigned)(0.5f * rect.maxy + ONE_THIRD), 1 + 2 * (unsigned)(0.5f * rect.maxy - ONE_SIXTH)};
  unsigned jmins[] = {(unsigned)(rect.minx + 0.5f), (unsigned)(rect.minx)};
  unsigned jmaxs[] = {(unsigned)(rect.maxx + 0.5f), (unsigned)(rect.maxx)};

  // process all lines
  unsigned imin = Min(imins[0], imins[1]);
  unsigned imax = Max(imaxs[0], imaxs[1]);
  for (unsigned i = imin; i <= imax; i++)
  {
    unsigned jmin = jmins[i & 1];
    unsigned jmax = jmaxs[i & 1];
    NatureMapElementId id = LocateElement(i, jmin);
    for (unsigned j = jmin; j <= jmax; j++, id++)
    {
      CVec2 pos;
      GetElementPosition(id, pos);
      if (overrideData.IsInside(pos))
      {
        float startDelay = 0.f;
        if (dbNatureMap.overrideSpeed > 1e-5f)
        {
          startDelay = fabs(pos - overrideData.circle.center) / dbNatureMap.overrideSpeed;
        }

        float life = lifeTime - startDelay;
        if (life > 0.f)
        {
          UnOverrideInternal(id, ownerData);
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::OverrideStep(float dt)
{
  nstl::vector<NatureOverrideElement*> uniqueOverrides;
  nstl::vector<NatureOverrideElement*> changedOverrides;
  nstl::vector<NatureOverrideElement*> aliveOverrides;
  int overridesChanged = 0;
  int i;

  for (TOverrides::iterator it = overrides.begin(); it != overrides.end(); )
  {
    it->second.lifeTime -= dt;
    if (it->second.lifeTime <= 0.0f)
    {
      overrides.erase(it++);
    }
    else
    {
      ++it;
    }
  }

  // prolongate/override overrides
  for (i = 0; i < overrideElements.size(); ++i)
  {
    NatureOverrideElement& ovr = overrideElements[i];

    // if override will be started on this step
    if ( ovr.timeToApply > 0.f &&
         ovr.timeToApply - dt <= 0.f )
    {
      // Find active or starting on this step override at the same element.
      // This logic will gather all conflicts under active override element (if any)
      // and under the last starting on this step element if there are no active one.
      int activeElemConflict = -1;
      int startingElemConflict = -1;
      for (int j = 0; j < overrideElements.size(); ++j)
      {
        if ( overrideElements[j].id == ovr.id )
        {
          if ( overrideElements[j].timeToApply <= 0.f )
          {
            activeElemConflict = j;
          }
          else if ( overrideElements[j].timeToApply > 0.f &&
                    overrideElements[j].timeToApply - dt <= 0.f &&
                    i != j )
          {
            // Case of another starting on this step override. The last will be picked.
            startingElemConflict = j;
          }
        }
      }

      int elemConflict = (activeElemConflict >= 0) ? activeElemConflict : startingElemConflict;

      if ( elemConflict >= 0 )
      {
        // if nature changes remember this fact
        if (overrideElements[elemConflict].data.nature != ovr.data.nature)
        {
          changedOverrides.push_back(&overrideElements[elemConflict]);
          ++overridesChanged;
        }
        // Put old override to inactive stack, so we will be able to restore it, if needed
        overrideElements[elemConflict].inactiveStack.push_back(overrideElements[elemConflict].data);

        // copy data from new override to active one
        overrideElements[elemConflict].data    = ovr.data;

        // Invalidate the new one
        ovr.id = NATUREMAPELEMENTID_BAD;
      }
    }

    if (ovr.id != NATUREMAPELEMENTID_BAD)
    {
      uniqueOverrides.push_back(&ovr);
    }
  }

  // activate/expire overrides
  for (i = 0; i < uniqueOverrides.size(); ++i)
  {
    NatureOverrideElement& ovr = *uniqueOverrides[i];

    if (ovr.id == NATUREMAPELEMENTID_BAD)
      continue;

    if (ovr.timeToApply > 0.f)
    {
      ovr.timeToApply -= dt;

      if (ovr.timeToApply <= 0.f)
      {
        ApplyOverride(ovr);
        ++overridesChanged;
      }

      aliveOverrides.push_back(&ovr);
    }
    else
    {
      // Step inactive overrides stack and erase expired
      for (TInactiveStak::iterator it = ovr.inactiveStack.begin(); it != ovr.inactiveStack.end();)
      {
        it->timeSpan -= dt;
        if (it->timeSpan <= 0.0f)
        {
          it = ovr.inactiveStack.erase(it);
        }
        else
        {
          ++it;
        }
      }
      ovr.data.timeSpan -= dt;
      if (ovr.data.timeSpan <= 0.0f) // expired
      {
        ++overridesChanged;
        // If we have inactive but still actual overrides for the same element -
        // bring the top of them back to be active. Otherwise - just expire.
        if (ovr.inactiveStack.size() > 0)
        {
          TInactiveStak::iterator it = ovr.inactiveStack.end() - 1;
          ovr.data = *it;
          ovr.inactiveStack.pop_back();
          aliveOverrides.push_back(&ovr);
        }
        else
        {
          ExpireOverride(ovr);
        }
      }
      else
      {
        aliveOverrides.push_back(&ovr);
      }
    }
  }

  // apply override overrides
  for (i = 0; i < changedOverrides.size(); ++i)
  {
    ApplyOverride(*changedOverrides[i]);
  }

  // rebuild list
  {
    nstl::vector<NatureOverrideElement> tmp;
    tmp.resize(aliveOverrides.size());
    for (i = 0; i < aliveOverrides.size(); ++i)
    {
      tmp[i] = *aliveOverrides[i];
    }
    overrideElements = tmp;
  }

  bool changed = overridesAdded || overridesChanged;

  return changed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NatureMap::OnStep(float dt)
{
  dt = Max(0.0f, dt);

  float speed = dbNatureMap.attackSpeed;
  roadsStep += speed * dt * SLICES_PER_SEGMENT;
  float leftover = 0.0f;
  int roadsSlices = FloorAndFrac(roadsStep, &leftover);

  // move terrain borders towards their targets
  bool changed = false;
  bool changedRoad[ARRAY_SIZE(roads)];
  if ( !dbNatureMap.editableNatureMap )
  {
    for (int roadIndex = 0; roadIndex < ARRAY_SIZE(roads); roadIndex++)
    {
      RoadProgress& road = roads[roadIndex];
      changedRoad[roadIndex] = false;
      for (int natureIndex = 0; natureIndex < ARRAY_SIZE(road.borders); natureIndex++)
      {
        RoadProgress::Border& border = road.borders[natureIndex];
        int span = border.target - border.position;
        if (span)
        {
          int sign = Sign(span);
          span *= sign;
          ASSERT(span > 0);

          int slices = ClampFast(roadsSlices, 0, span);
          if (slices)
          {
            ASSERT(slices > 0);
            border.last = border.position;
            border.position += slices * sign;
            changed = true;
            changedRoad[roadIndex] = true;
          }
        }
      }
    }
    roadsStep = leftover;
  }

  // update override times
  bool changedOverrides = OverrideStep(dt);

  // check which elements could change their nature and notify
  if (changed)
  {
    ASSERT(attackSpace.GetNumStrips() == 5);
    static int const numRows = 5/*attackSpace.GetNumStrips()*/ + 2;
    int const numCols = attackSpace.GetNumSegments() + 2;
    static int const maxRoad = ARRAY_SIZE(roads) - 1;
    static int const MAX_NUM_ENDPOINTS = numRows * 2 * 2; // two endpoints for two natures per row
    int changedQuads[MAX_NUM_ENDPOINTS];
    int i = 0;

    for (int row = 0; row < numRows; row++)
    {
      int stripIndex = row - 1;
      int dnIdx = ClampFast(maxRoad - stripIndex / 2, 0, maxRoad);
      int upIdx = ClampFast(maxRoad - (stripIndex + 1) / 2, 0, maxRoad);

      if (changedRoad[dnIdx] || changedRoad[upIdx])
      {
        NI_STATIC_ASSERT(ARRAY_SIZE(roads->borders) == 2, ONLY_TWO_NATURES_SUPPORTED_HERE);
        int left[2], right[2];
        MinMax(left[0], right[0],
          roads[dnIdx].borders[0].position, roads[dnIdx].borders[0].last,
          roads[upIdx].borders[0].position, roads[upIdx].borders[0].last);
        left[0] = (left[0] + SLICES_PER_SEGMENT) / SLICES_PER_SEGMENT;
        right[0] = (right[0] + SLICES_PER_SEGMENT - 1) / SLICES_PER_SEGMENT;
        MinMax(right[1], left[1],
          roads[dnIdx].borders[1].position, roads[dnIdx].borders[1].last,
          roads[upIdx].borders[1].position, roads[upIdx].borders[1].last);
        left[1] = numCols-1 - (left[1] + SLICES_PER_SEGMENT - 1) / SLICES_PER_SEGMENT;
        right[1] = numCols-1 - (right[1] + SLICES_PER_SEGMENT) / SLICES_PER_SEGMENT;

        int startQuad = row * numCols;
        if (right[0] < left[1] - 1 || right[1] < left[0] - 1)
        {
          // add them separately
          ASSERT(i + 4 <= MAX_NUM_ENDPOINTS);
          changedQuads[i++] = startQuad + left[0];
          changedQuads[i++] = startQuad + right[0];
          changedQuads[i++] = startQuad + left[1];
          changedQuads[i++] = startQuad + right[1];
        }
        else
        {
          // join interval
          ASSERT(i + 2 <= MAX_NUM_ENDPOINTS);
          changedQuads[i++] = startQuad + Min(left[0], left[1]);
          changedQuads[i++] = startQuad + Max(right[0], right[1]);
        }
      } // end if row changed
    } // end for all rows
    
    OnNatureChanged(changedQuads, i/2);
  }
  else if (changedOverrides )
  {
    OnNatureChanged(0, 0);
    overridesAdded = 0; // reset
    
  }
  if ( !editedElements.empty() )
  {
    for (nstl::vector<NatureMapElementId>::iterator it = editedElements.begin(); it != editedElements.end(); ++it )
    {
      NatureMapElementId id = *it;
      MarkAsModified(id, GetElementInfo(id));
    }
    editedElements.clear();
    OnNatureChanged(0, 0);
    changed = true;
  }

  return (changed || changedOverrides);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NatureMap::GetNature(float x, float y) const
{
  NatureMapElementId id = LocateElement(x, y);
  if ( id == -1 )
    return 0;
  if ( overrideElementInfo )
    return overrideElementInfo->natureCur;
  return (int)elemList[id].natureCur;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NatureMap::GetNature( NatureMapElementId id ) const
{
  if ( overrideElementInfo )
    return overrideElementInfo->natureCur;
  return (int)elemList[id].natureCur;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float NatureMap::GetNaturePercent(NDb::ENatureType faction, NDb::ENatureRoad roadIndex) const
{
  int id = faction - 1;
  ASSERT(id == 0 || id == 1);
  ASSERT(0 <= roadIndex && roadIndex < ARRAY_SIZE(roads));
  float slices = roads[roadIndex].borders[id].position;
  float total = attackSpace.GetNumSegments() * SLICES_PER_SEGMENT;
  return slices / total;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NatureMap::GetNumSegments() const
{
  return attackSpace.GetNumSegments();
}

//////////////////////////////////////////////////////////////////////////
float NatureMap::GetNaturePercent(NDb::ENatureType faction) const
{
  int id = faction - 1;
  ASSERT(id == 0 || id == 1);

  

  float basePercent[2] = {dbNatureMap.baseAPercent*0.01f, dbNatureMap.baseBPercent*0.01f};
  int segmentsPerBase[2] = { basePercent[0] > 0.0f ? 0 : 1,
                             basePercent[1] > 0.0f ? 0 : 1 };
  
  int total = (attackSpace.GetNumSegments() + segmentsPerBase[0] + segmentsPerBase[1]) * SLICES_PER_SEGMENT * validRoads.size();
  int slices = 0;
  for (TValidRoads::const_iterator roadIndex = validRoads.begin(); roadIndex != validRoads.end(); ++roadIndex)
  {
    slices += roads[(*roadIndex)].borders[id].position + segmentsPerBase[id] * SLICES_PER_SEGMENT;
  }
  
  return (float)slices / (float)total * (1.0f - (basePercent[0] + basePercent[1])) + basePercent[id];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CVec2 NatureMap::GetNatureBound(NDb::ENatureType faction, NDb::ENatureRoad roadIndex) const
{
  // road
  ASSERT(0 <= roadIndex && roadIndex < ARRAY_SIZE(roads));
  float x[] = {
    (float)roads[roadIndex].borders[0].position / (float)SLICES_PER_SEGMENT, 
    (float)attackSpace.GetNumSegments() - (float)roads[roadIndex].borders[1].position / (float)SLICES_PER_SEGMENT
  };
  float y = 2.0f * (float)(ARRAY_SIZE(roads) - roadIndex - 1) + 0.5f;
  // faction
  int id = faction - 1;
  ASSERT(id == 0 || id == 1);
  return attackSpace.FindCoordinatesWS(CVec2(x[id], y));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureMap::GetNatureSegment(CVec2 const &pos, NDb::ENatureRoad &road, int &segment) const
{
  CVec2 _attackPos = attackSpace.FindCoordinatesAS(pos);

  if (_attackPos.y < 2)
    road = NDb::NATUREROAD_BOTTOM;
  else if (_attackPos.y < 4)
    road = NDb::NATUREROAD_CENTER;
  else
    road = NDb::NATUREROAD_TOP;
  segment = (int) _attackPos.x;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::UpdateNature(NatureMapElementId id, NatureMapElementInfo& info)
{
  NDb::ENatureType shouldBe = GetNaturePrecise(info.attackPos);
  if ((unsigned)shouldBe == info.natureBase) // basic nature has not changed, ignore (keep override if any)
    return;

  // If we have override - do not destroy it, just change
  // the nature base and it will restore properly when expired.
  if (info.ownerData != 0)
  {
    info.natureBase = shouldBe;
    return;
  }

  info.natureBase = shouldBe; // update basic nature
  info.ownerData  = 0; // reset owner
  if (info.natureCur != (unsigned)shouldBe)
  {
    info.natureOld  = info.natureCur;
    info.natureCur  = shouldBe; // overrides are lost here if any
    MarkAsModified(id, info);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NDb::ENatureType NatureMap::GetNaturePrecise(CVec2 const& _attackPos)
{
  int const maxRoad = ARRAY_SIZE(roads) - 1;
  float left = 0, right = attackSpace.GetNumSegments();
  int stripIndex = ClampFast((int)floor(_attackPos.y), 0, maxRoad * 2);
  float stripOffset = _attackPos.y - stripIndex;
  int dnIdx = ClampFast(maxRoad - stripIndex / 2, 0, maxRoad);
  int upIdx = ClampFast(maxRoad - (stripIndex + 1) / 2, 0, maxRoad);

  left  += Lerp((float)roads[dnIdx].borders[0].position, (float)roads[upIdx].borders[0].position, stripOffset) / (float)SLICES_PER_SEGMENT;
  right -= Lerp((float)roads[dnIdx].borders[1].position, (float)roads[upIdx].borders[1].position, stripOffset) / (float)SLICES_PER_SEGMENT;

  NDb::ENatureType natureType;
  if (_attackPos.x <= left)
    natureType = NDb::NATURETYPE_A;
  else if (_attackPos.x >= right)
    natureType = NDb::NATURETYPE_B;
  else
    natureType = NDb::NATURETYPE_N;
  
  return natureType;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::OnNatureChanged(int const* pQuadRanges, int numQuadRanges)
{
  // ForAllElementsInRange
  while (numQuadRanges-- > 0)
  {
    int firstQuad = *(pQuadRanges++);
    int lastQuad = *(pQuadRanges++);

    int start = quadToOffset[firstQuad];
    int end = quadToOffset[lastQuad + 1];
    for (int i = start; i < end; i++)
    {
      NatureMapElementId id = elemListSorted[i];
      UpdateNature(id, GetElementInfo(id));
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::MarkAsModified(NatureMapElementId id, NatureMapElementInfo& /*info*/)
{
  if (modifiedElems->find(id) == modifiedElems->end())
    modifiedElems->push_back(id);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::InitSortedList()
{
  int numElements = elemList.size();
  int rowsCount = attackSpace.GetNumStrips() + 2;
  int colsCount = attackSpace.GetNumSegments() + 2;

  // prepare unsorted arrays
  nstl::vector<int> elemListQuads;
  elemListSorted.resize(numElements);
  elemListQuads.resize(numElements);
  for (int i = 0; i < numElements; i++)
  {
    CVec2 const& _attackPos = GetElementInfo(i).attackPos;
    int col = ClampFast((int)floor(_attackPos.x) + 1, 0, colsCount - 1);
    int row = ClampFast((int)floor(_attackPos.y) + 1, 0, rowsCount - 1);

    elemListSorted[i] = i;
    elemListQuads[i] = row * colsCount + col;
  }

  // sort by quad index (counting sort)
  {
    int numQuads = rowsCount * colsCount;
    quadToOffset.resize(numQuads + 1, 0);

    // count elements in each quad
    for (int i = 0; i < numElements; i++)
    {
      ASSERT(0 <= elemListQuads[i] && elemListQuads[i] < numQuads);
      quadToOffset[elemListQuads[i]]++;
    }

    // accumulate to find top boundaries
    for (int j = 1; j < numQuads; j++)
      quadToOffset[j] += quadToOffset[j - 1];
    ASSERT(quadToOffset[numQuads-1] == numElements);

    // distribute elements starting from last
    for (int i = numElements - 1; i >= 0; i--)
      elemListSorted[--quadToOffset[elemListQuads[i]]] = i;

    // additional fake offset
    quadToOffset[numQuads] = numElements;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Render::Color colorB(200, 0, 0);
static Render::Color colorN(0, 200, 0);
static Render::Color colorF(0, 0, 255);

Render::Color * GetDebugNatureColor(unsigned int natureType)
{
  if (natureType == 0)
    return &colorN;
  else if (natureType == 1)
    return &colorF;
  else
    return &colorB;
}

void DrawNatureHexagon(unsigned int natureType, CVec2 pos, float size)
{
  Render::Color * color = GetDebugNatureColor(natureType);

  CVec3 v[6];
  float shiftY = size/3;

  v[0].Set(pos.x       , pos.y + size + shiftY, 0);
  v[1].Set(pos.x + size, pos.y + size - shiftY, 0);
  v[2].Set(pos.x + size, pos.y - size + shiftY, 0);
  v[3].Set(pos.x       , pos.y - size - shiftY, 0);
  v[4].Set(pos.x - size, pos.y - size + shiftY, 0);
  v[5].Set(pos.x - size, pos.y + size - shiftY, 0);

  Render::DebugRenderer::DrawLine3D(v[0], v[1], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[1], v[2], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[2], v[3], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[3], v[4], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[4], v[5], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[5], v[0], *color, *color, false);
}

void NatureMap::RenderDebug()
{
#ifndef VISUAL_CUTTED
  if (g_showAttackSpace)
  {
    ShowAttackSpace();
  }

  if (g_showNatureMap)
  {
    float size = GetElementSize();

    for (int i = 0; i < elemListSorted.size(); ++i)
    {
      CVec2 pos;
      GetElementPosition(elemListSorted[i], pos);
      NatureMapElementInfo const & elemInfo = GetElementInfo(elemListSorted[i]);
      DrawNatureHexagon(elemInfo.natureCur, pos, size/2-0.1);
      if (elemInfo.natureOld != elemInfo.natureCur)
        DrawNatureHexagon(elemInfo.natureOld, pos, size/2-0.2);
      if (elemInfo.natureBase != elemInfo.natureCur)
       DrawNatureHexagon(elemInfo.natureBase, pos, size/2-0.3);
    }

    for (int i = 0; i < overrideElements.size(); ++i)
    {
      if (overrideElements[i].inactiveStack.size() > 0)
      {
        CVec2 pos;
        GetElementPosition(overrideElements[i].id, pos);
        DrawNatureHexagon(overrideElements[i].inactiveStack.back().nature, pos, size/5);
      }
    }

    for (TOverrides::iterator it = overrides.begin(); it != overrides.end(); ++it)
    {
      CCircle & overrideCircle = it->second.circle;
      Render::Color * color = GetDebugNatureColor(it->second.faction);
      int numSegments = max<int>(10, int(overrideCircle.r * PI));
      Render::DebugRenderer::DrawCircle3D(CVec3(overrideCircle.center, 0.0F), overrideCircle.r, numSegments, *color, false);
    }
  }
#endif
}

void NatureMap::ShowAttackSpace()
{
  // render grid
  attackSpace.RenderDebug();

  // render roads
  Render::Color color(255, 0, 0);
  for (int i = 0, n = dbNatureMap.attackSpaceRoads.size(); i < n; i++)
  {
    NDb::DBNatureMapRoad const& road = dbNatureMap.attackSpaceRoads[i];
    for (int j = 0, m = road.nodes.size(); j < m-1; j++)
    {
      CVec3 a(road.nodes[j], 0.0f);
      CVec3 b(road.nodes[j+1], 0.0f);
      Render::DebugRenderer::DrawLine3D(a, b, color, color, false);
    }
  }

  // render tile under cursor and show precise nature type
  Render::Color colors[] = {Render::Color(0, 128, 0), Render::Color(0, 0, 128), Render::Color(128, 0, 0)};
  CVec2 _attackPos = attackSpace.FindCoordinatesAS(debugPos);
  NDb::ENatureType debugNatureType = GetNaturePrecise(_attackPos);
  attackSpace.RenderDebugTile(_attackPos, colors[debugNatureType]);

  // render logic nature borders
  for (int natureType = 1; natureType <= 2; natureType++)
  {
    for (int roadIndex = 0; roadIndex < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf; roadIndex++)
    {
      CVec2 pos = GetNatureBound((NDb::ENatureType)natureType, (NDb::ENatureRoad)roadIndex);
      Render::DebugRenderer::DrawPoint3D(CVec3(pos, 0.0f), 2.0f, colors[natureType], false);
    }
  }

  // show hex bbox under cursor with stored nature type
  NatureMapElementId id = LocateElement(debugPos.x, debugPos.y);
  if (id != NATUREMAPELEMENTID_BAD)
  {
    NatureMapElementInfo& info = GetElementInfo(id);
    Render::AABB aabb;
    GetElementBounds(id, aabb);
    aabb.halfSize.z = 1.0f;
    Render::DebugRenderer::DrawAABB(aabb, colors[info.natureCur], false);
  }

  // show overrides
  for (int i = 0; i < overrideElements.size(); ++i)
  {
    CVec2 pos;
    GetElementPosition(overrideElements[i].id, pos);
    Render::AABB aabb( CVec3(pos.x, pos.y, 0.f), CVec3(1.f, 1.f, 0.f) );
    if (overrideElements[i].timeToApply <= 0.f)
    {
      Render::DebugRenderer::DrawAABB(aabb, Render::Color(0, 255, 0), false);
    }
    else
    {
      int intensity = (int)(255.f * Clamp(1.f - overrideElements[i].timeToApply, 0.f, 1.f));
      Render::DebugRenderer::DrawAABB(aabb, Render::Color(intensity, intensity, 0), false);
    }
  }
}

bool NatureMap::IsOverrideActive(unsigned int ownerData) const
{
  TOverrides::iterator it = overrides.find(ownerData);
  return it != overrides.end();
}

bool NatureMap::Reinit( NDb::ENatureType faction, const NDb::DBNatureMap* pDbNatureMap, bool forceCreate )
{
  if(pDbNatureMap)
    dbNatureMap = *pDbNatureMap;

  if ( faction == -1 )
    ::Reset(overrideElementInfo, 0);
  else 
  {
    ::Reset(overrideElementInfo, new NatureMapElementInfo());
    overrideElementInfo->natureBase = 3;
    overrideElementInfo->natureCur = faction;
    overrideElementInfo->natureOld = 3;
  }

  if ( dbNatureMap.editableNatureMap )
  {

    ForAllElements(this, &NatureMap::MarkAsModified);
    return true;
  }


  ResetImpl();

  bool loadOk = false;
  if(!forceCreate) {
    // try to load data first
    CObj<Stream> pStream = RootFileSystem::OpenFile(dbNatureMap.natureMapFile, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
    if (pStream)
      loadOk = OnLoad(pStream, faction, false);

    if( IsValid( pStream ) )
      pStream->Close();
  }

  // otherwise create if allowed to
  bool createOk = false;
  if (!loadOk && editable)
    createOk = OnCreate();

  return loadOk || createOk;
}

void NatureMap::Reset()
{
  Reinit(static_cast<NDb::ENatureType>(-1), 0, false );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::EditNature(NatureMapElementId id, NDb::ENatureType faction)
{
  NI_VERIFY( dbNatureMap.editableNatureMap, "Cannot edit non-editable Nature Map ", return );

  if ( overrideElementInfo )
    return;

  NatureMapElementInfo& info = GetElementInfo(id);

  uint shouldBe = (uint)faction;
  info.natureBase = shouldBe; // update basic nature
  info.ownerData  = 0; // reset owner
  if (info.natureCur != (unsigned)shouldBe)
  {
    info.natureOld  = info.natureCur;
    info.natureCur  = shouldBe; 
    //MarkAsModified(id, info);
    editedElements.push_back( id );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NatureMap::ResetImpl()
{
  xCount = Max(1U, (unsigned)(worldSize.x / dbNatureMap.gridStep)) + 1;
  yCount = Max(1U, (unsigned)(worldSize.y / dbNatureMap.gridStep)) + 1;

  debugPos = 0.5f * worldSize.AsVec2D();

  NatureMapElementInfo empty;
  elemList.resize(xCount * yCount, empty);
  elemListSorted.clear();
  quadToOffset.clear();
  overrideElements.clear();
  overrides.clear();
  overridesAdded = 0;

  for (int i = 0; i < ARRAY_SIZE(roads); i++)
  {
    roads[i].borders[0].last = roads[i].borders[0].position = roads[i].borders[0].target = 0;
    roads[i].borders[1].last = roads[i].borders[1].position = roads[i].borders[1].target = 0;
  }
  roadsStep = 0.0f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int NatureMap::operator&( IBinSaver &f ) 
{  
  if( f.IsChecksum() )
    return 0;

  int nCount;
  
  if( f.IsReading() )
  {
     f.Add(1, &nCount);
     MemoryStream stream( nCount );
     f.AddRawData( 2, stream.GetBuffer(), nCount );
     LoadAtRuntime( &stream, true );
  }
  else
  {
    MemoryStream stream;
    SaveAtRuntime( &stream, true );
    nCount = stream.GetSize();
    f.Add(1, &nCount);
    f.AddRawData( 2, stream.GetBuffer(), nCount ); 
  }
  
  f.AddRawData( 3, roads, ARRAY_SIZE(roads) * sizeof(RoadProgress) );
  f.Add( 4, &roadsStep );
  f.Add( 5, &overrideElements );
  f.Add( 6, &overridesAdded );
  f.Add( 7, &overrides );
  f.Add( 8, &editedElements );

  return 0; 
}

} // namespace Terrain

REGISTER_DEV_VAR( "nattackshow", g_showAttackSpace, STORAGE_NONE );
REGISTER_DEV_VAR( "show_nature_map", g_showNatureMap, STORAGE_NONE );

// end of NatureMap.cpp
