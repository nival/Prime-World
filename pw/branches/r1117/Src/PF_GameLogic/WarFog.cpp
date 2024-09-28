#include "stdafx.h"

#include "WarFog.h"

#include "System/InlineProfiler.h"

#include "System/ImageTGA.h"
#include "System/LogFileName.h"

#include "PFWorld.h"
#include "TileMap.h"
#include "Scene/HeightsController.h"

#include "System/niterator.h"

namespace
{
  template <class T>
  static inline bool CheckArrayIndex(const CArray2D<T>& arr, const int x, const int y)
  {
    if (x < 0)
      return false;
    if (y < 0)
      return false;
    if (x >= arr.GetSizeX())
      return false;
    if (y >= arr.GetSizeY())
      return false;

    return true;
  }
}

namespace
{
//means that this object is free now
static const SVector BAD_POS(-1,-1);

static int g_showWarFog = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This exponent used to make integer value from floating point angle value for deterministic comparisons.
// The actual precision allows exponent of 100000.0f, but we use 10000.0f for sure.
const float roundingExponent = 10000.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inline function to make integer value from floating point angle value for deterministic comparisons.
inline int MakeInt(float floatValue)
{
  return Float2Int(floatValue * roundingExponent);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predicate for searching hiding sector of another sector by its middle angle
// Compares without including own bounding angles (use > and <)
struct FindHidingSectorPred
{
  int angle;

  FindHidingSectorPred(float _angle) : angle(MakeInt(_angle)) {}

  bool operator()(NWorld::FogOfWar::SectorData const & sd)
  {
    return (angle > MakeInt(sd.angleMin) && angle < MakeInt(sd.angleMax));
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predicate for searching hiding sector of another sector by its middle angle
// Compares including own bounding angles (use >= and <=)
struct FindHidingSectorPred2
{
  int angle;

  FindHidingSectorPred2(float _angle) : angle(MakeInt(_angle)) {}

  bool operator()(NWorld::FogOfWar::SectorData const & sd)
  {
    return (angle >= MakeInt(sd.angleMin) && angle <= MakeInt(sd.angleMax));
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Predicate for sorting sectors in the nstl::set. 
// Dicides that A < B, when max bounding angle of A is less than min bounding angle of B.
struct SortSectorsPred
{
  bool operator () (NWorld::FogOfWar::SectorData const & sd1, NWorld::FogOfWar::SectorData const & sd2)
  {
    return (MakeInt(sd1.angleMax) < MakeInt(sd2.angleMin));
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef nstl::set<NWorld::FogOfWar::SectorData, SortSectorsPred> TSectors;
typedef nstl::vector<NWorld::FogOfWar::TileData>                 TCircle;
typedef nstl::vector<TCircle>                                    TCircles;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddPoint(int x, int y, float angleMin, float angleMid, float angleMax, TCircle & circle)
{
  circle.push_back(NWorld::FogOfWar::TileData(x, y, angleMin, angleMid, angleMax));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Add4Points(int x, int y, float angleMin, float angleMid, float angleMax, TCircle & circle)
{
  AddPoint(x, y, angleMin, angleMid, angleMax, circle);
  if (x != 0) AddPoint(-x,  y, FP_PI - angleMax, FP_PI - angleMid, FP_PI - angleMin, circle);
  if (y != 0) AddPoint( x, -y, FP_2PI - angleMax, FP_2PI - angleMid, FP_2PI - angleMin, circle);
  if (x != 0 && y != 0) AddPoint(-x, -y, FP_PI + angleMin, FP_PI + angleMid, FP_PI + angleMax, circle);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Add8Points(int x, int y, TCircle & circle)
{
  CVec2 p0(x, y);
  CVec2 p1((y)?((float)x + 0.5f):((float)x - 0.5f),  (float)y - 0.5f);
  CVec2 p2((float)x - 0.5f, (float)y + 0.5f);

  Normalize(p0.x, p0.y);
  Normalize(p1.x, p1.y);
  Normalize(p2.x, p2.y);

  float angleMin = (y)?(acos(p1.x)):(-acos(p1.x));
  float angleMid = acos(p0.x);
  float angleMax = acos(p2.x);

  Add4Points(x, y, angleMin, angleMid, angleMax, circle);
  if (x != y) Add4Points(y, x, FP_PI2 - angleMax, FP_PI2 - angleMid, FP_PI2 - angleMin, circle);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillCircle(int radius, TCircle & circle)
{
  if (radius < 1)
    return;

  float x = radius;
  float y = 0;
  float radiusMin = (float)radius - 0.5f;
  float radiusMax = (float)radius + 0.5f;

  while (x >= y)
  {
    float dist = fabs((float)x,(float)y);
    if ( dist > radiusMin && dist <= radiusMax )
    {
      Add8Points(x,y, circle);

      if (x-1 >= y)
      {
        dist = fabs((float)(x-1),(float)(y));
        if ( dist > radiusMin && dist <= radiusMax )
        {
          Add8Points(x-1,y, circle);
        }
      }

      y++;
    }
    else
    {
      x--;
    }
  }

  // Now sort tiles of the circle, so the closer to the center will come first.
  // That's needed, because they may hide nearby tiles, which are farther from the center.

  struct SortTilesPred
  {
    bool operator() (NWorld::FogOfWar::TileData const & td1, NWorld::FogOfWar::TileData const & td2)
    {
      return (fabs((float)(td1.x),(float)(td1.y)) < fabs((float)(td2.x),(float)(td2.y)));
    }
  } sortTilesPred;

  sort(circle.begin(), circle.end(), sortTilesPred);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddCircles(int circlesToAdd, TCircles & circles)
{
  if (circlesToAdd < 1)
    return;

  int oldCirclesCount = circles.size();
  int newCirclesCount = oldCirclesCount + circlesToAdd;

  circles.resize(newCirclesCount);

  for(int i = oldCirclesCount; i < newCirclesCount; ++i)
  {
    FillCircle( i + 1, circles[i] );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
TSectors::iterator FindHidingSector(float angle, TSectors & sectors)
{
  return find_if(sectors.begin(), sectors.end(), T( (MakeInt(angle) < 0)?(angle + FP_2PI):(angle) ));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsVisible(NWorld::FogOfWar::TileData & tile, TSectors & sectors)
{
  tile.isVisible = true;

  if (MakeInt(tile.angleMid) != 0)
  {
    TSectors::iterator iHidingSector = FindHidingSector<FindHidingSectorPred>(tile.angleMid, sectors);

    if (iHidingSector != sectors.end())
    {
      tile.isVisible = false;
      tile.fromRadius = iHidingSector->fromRadius;
    }
  }
  else
  {
    if (sectors.size())
    {
      TSectors::iterator iHidingSector1 = sectors.begin();
      TSectors::reverse_iterator iHidingSector2 = sectors.rbegin();

      if (!(MakeInt(iHidingSector1->angleMin) > 0 && MakeInt(iHidingSector2->angleMax) < MakeInt(FP_2PI)))
      {
        tile.isVisible = false;
        tile.fromRadius = min(iHidingSector1->fromRadius, iHidingSector2->fromRadius);
      }
    }
  }

  return tile.isVisible;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddSector(const NWorld::FogOfWar::SectorData& sector, TSectors & sectors)
{
  // find blocker for min
  TSectors::iterator iHidingSectorMin = FindHidingSector<FindHidingSectorPred2>(sector.angleMin, sectors);
  // find blocker for max
  TSectors::iterator iHidingSectorMax = FindHidingSector<FindHidingSectorPred2>(sector.angleMax, sectors);

  // if both blocked - merge blokers ignore sector
  if (iHidingSectorMin != sectors.end() && iHidingSectorMax != sectors.end())
  {
    // only if not blocked by the same sector
    if (iHidingSectorMin != iHidingSectorMax)
    {
      if (MakeInt(iHidingSectorMin->angleMax) > MakeInt(iHidingSectorMax->angleMin))
      {
        iHidingSectorMin->angleMax = FP_2PI;
        iHidingSectorMax->angleMin = 0.0f;
      }
      else
      {
        iHidingSectorMin->angleMax = iHidingSectorMax->angleMax;
        iHidingSectorMin->fromRadius = min(iHidingSectorMin->fromRadius, iHidingSectorMax->fromRadius);
        sectors.erase(iHidingSectorMax);
      }
    }
  }
  // if min blocked - merge sector with blocker
  else if (iHidingSectorMin != sectors.end())
  {
    if (MakeInt(sector.angleMin) < 0)
    {
      iHidingSectorMin->angleMax = FP_2PI;
      NWorld::FogOfWar::SectorData sector1(0.0f, sector.angleMax, iHidingSectorMin->fromRadius);
      sectors.insert(sector1);
    }
    else
    {
      iHidingSectorMin->angleMax = sector.angleMax;
    }
  }
  // if max blocked - merge sector with blocker
  else if (iHidingSectorMax != sectors.end())
  {
    if (MakeInt(sector.angleMin) < 0)
    {
      iHidingSectorMax->angleMin = 0.0f;
      NWorld::FogOfWar::SectorData sector1(FP_2PI + sector.angleMin, FP_2PI, iHidingSectorMax->fromRadius);
      sectors.insert(sector1);
    }
    else
    {
      iHidingSectorMax->angleMin = sector.angleMin;
    }
  }
  // if none blocked - add sector
  else
  {
    if (MakeInt(sector.angleMin) < 0)
    {
      NWorld::FogOfWar::SectorData sector1(FP_2PI + sector.angleMin, FP_2PI, sector.fromRadius);
      NWorld::FogOfWar::SectorData sector2(0.0f, sector.angleMax, sector.fromRadius);

      sectors.insert(sector1);
      sectors.insert(sector2);
    }
    else
    {
      sectors.insert(sector);
    }
  }
}
 
}//end of anonymous namespace

namespace NWorld
{

static FogOfWar* g_warFog = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FogOfWar::FogOfWar(PFWorld* pWorld, int teams, int _width, int _height, int _visTileSize, int _obstacleDeepVisibility)
  : PFWorldObjectBase( pWorld, 0 )
  , visTileSize( _visTileSize )
  , maxRadius(0)
  , useHeightsDelta(false)
  , maxHeightsDelta(0.0f)
  , warFogType(NDb::WARFOGTYPE_DUALLAYER)
  , revision(0U)
{
  g_warFog = this;

  NI_VERIFY(visTileSize > 0, NStr::StrFmt( "visTileSize (%d) should be greater that 0", visTileSize ), visTileSize = 1);

  width =  DivideByVisTile(_width);
  height = DivideByVisTile(_height);
  obstacleDeepVisibility = DivideByVisTile(_obstacleDeepVisibility);

  NI_VERIFY(obstacleDeepVisibility > 0, "invalid obstacle view deep", obstacleDeepVisibility = 1);

  visibilityMap.resize(teams);
  visibilityMapMask.resize(teams);

  for (int i=0; i<teams; i++)
  {
    visibilityMap[i].SetSizes(width, height);
    visibilityMap[i].FillZero();
    visibilityMapMask[i].SetSizes(width, height);
    visibilityMapMask[i].FillZero();
  }

  obstacles.SetSizes(width, height);
  obstacles.FillZero();

  heights.SetSizes(width, height);
  heights.FillZero();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FogOfWar::~FogOfWar()
{
  g_warFog = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::Reset()
{
	//objects.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ResetVisibility()
{
  for (int i = 0; i < visibilityMap.size(); ++i)
  {
    visibilityMap[i].FillZero();
    visibilityMapMask[i].FillZero();
  }

  for (int i = 0; i < objects.size(); ++i)
  {
    objects[i].isDirty = true;
    objects[i].isValidVisibleTiles = false;
  }

  StepVisibility(0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ApplyHeightMap( const CArray2D<float>& _heights, const NScene::IHeightsController& heightsController )
{
  for (int x = 0; x < heights.GetSizeX(); ++x)
  {
    for (int y = 0; y < heights.GetSizeY(); ++y)
    {
      int xFrom = x * visTileSize;
      int yFrom = y * visTileSize;
      int xTo   = Min(xFrom + visTileSize, _heights.GetSizeY());
      int yTo   = Min(yFrom + visTileSize, _heights.GetSizeX());

      float minHeight = MAX_FLOAT;

      for (int xCurr = xFrom; xCurr < xTo; ++xCurr )
      {
        for (int yCurr = yFrom; yCurr < yTo; ++yCurr)
        {
          float currHeight;
          heightsController.GetHeightByTile(xCurr, yCurr, 1, &currHeight, 0 );

          if (currHeight < minHeight)
          {
            minHeight = currHeight;
          }
        }
      }

      heights[x][y] = minHeight;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ApplyHeightSettings( bool _useHeightsDelta, float _maxHeightsDelta )
{
  NI_VERIFY((_useHeightsDelta ? _maxHeightsDelta > 0.f : true), NStr::StrFmt("maxHeightsDelta (%0.2f) should be greater than 0!", _maxHeightsDelta ), return);

  useHeightsDelta = _useHeightsDelta;
  maxHeightsDelta = _maxHeightsDelta;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::AddTempObject( const SVector& position, int team, int visRadius, float lifeTime )
{
  const int index = AddObject(position, team, visRadius);

  NI_VERIFY(index != WAR_FOG_BAD_ID, "Invalid object ID!", return);

  objects[index].lifeTime = lifeTime;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FogOfWar::AddObject( const SVector& position, int team, int visRadius, const bool cancelHidingSectors )
{
  ObjectInfo * object = NULL;
  int index = WAR_FOG_BAD_ID;

  for (int i = 0; i < objects.size(); ++i)
  {
    if (objects[i].newParams.position == BAD_POS)
    {
      object = &(objects[i]);
      index = i;
      break;
    }
  }

  if (!object)
  {
   object = &(objects.push_back());
   index = objects.size() - 1;
  }

  NI_VERIFY(object, "Failed to add object!", return WAR_FOG_BAD_ID);

  object->isDirty = true;
  object->newParams.position = ConvertToVisTile(position);
  object->newParams.team = team;
  object->newParams.visRadius = DivideByVisTile(visRadius);
  object->cancelHidingSectors = cancelHidingSectors;

  object->oldParams = object->newParams;

  maxRadius = Max(maxRadius, object->newParams.visRadius);

  return index;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::MoveObject( int id, const SVector& position )
{
  NI_PROFILE_FUNCTION

  NI_VERIFY(IsValidObjectIndex(id), "Invalid object ID!", return);

  ObjectInfo & object =  objects[id];

  NI_VERIFY(object.newParams.position != BAD_POS, "Removed object can't move!", return );

  SVector visTile = ConvertToVisTile(position);

  if (object.newParams.position == visTile)
    return;

  object.newParams.position = visTile;
  object.isDirty = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::RemoveObject( int id )
{
  NI_VERIFY(IsValidObjectIndex(id), "Invalid object ID!", return);

  ObjectInfo& object = objects[id];

  if (object.newParams.position == BAD_POS)
    return;

  object.UnMark(this);
  object.newParams.position = BAD_POS;
  object.isValidVisibleTiles = false;
  object.lifeTime = -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ChangeVisibility( int id, int visRadius )
{
  NI_VERIFY(IsValidObjectIndex(id), "Invalid object ID!", return);

  const int newRadius = DivideByVisTile(visRadius);

  if (objects[id].newParams.visRadius == newRadius)
    return;

  objects[id].newParams.visRadius = newRadius;
  objects[id].isDirty = true;

  maxRadius = Max(maxRadius, newRadius);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ChangeTeam( int id, int team )
{
  NI_VERIFY(IsValidObjectIndex(id), "Invalid object ID!", return);

  objects[id].newParams.team = team;
  objects[id].isDirty = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FogOfWar::IsTileVisible( const SVector& tile, int team ) const
{
  NI_VERIFY(IsValidTeam(team), "Invalid team!", return false);

  const int x = tile.x / visTileSize;
  const int y = tile.y / visTileSize;

  NI_VERIFY(IsValidPosition(x, y), "Invalid tile position!", return false);

  return visibilityMap[team][x][y];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FogOfWar::CanObjectSeePosition( int id, const SVector & target ) const
{
  if (!IsValidObjectIndex(id))
    return false;

  const ObjectInfo & object = objects[id];
  
  const SVector relativeVisTarget = ConvertToVisTile(target) - object.oldParams.position;

  const int x = relativeVisTarget.x + object.oldParams.visRadius;
  const int y = relativeVisTarget.y + object.oldParams.visRadius;

  if (x < 0)
    return false;
  if (y < 0)
    return false;
  if (x >= object.visibleTiles.GetSizeX())
    return false;
  if (y >= object.visibleTiles.GetSizeY())
    return false;

  return
    (object.visibleTiles[x][y]) ||
    (object.potentiallyVisibleTiles[x][y] && IsTileVisible(target, object.oldParams.team));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FogOfWar::Step(float dt)
{
  // Do nothing here. War fog steps via StepVisibility after moving units step
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::StepVisibility(float dt)
{
  NI_PROFILE_FUNCTION;

  unsigned changes = 0U;

  for (int i =0; i<objects.size(); i++)
  {
    ObjectInfo & object = objects[i];
    
    //skip deleted objects
    if (object.newParams.position == BAD_POS)
      continue;

    if (object.lifeTime > 0.0f && dt > 0.0f)
    {
      object.lifeTime = max(0.0f, object.lifeTime - dt);
    }
    else if (!object.lifeTime)
    {
      ++changes;

      RemoveObject(i);
      continue;
    }

    if (object.isDirty)
    {
      ++changes;

      object.UnMark(this);
      object.Mark(this);
      object.oldParams = object.newParams;
      object.isDirty = false;
    }
  }

  if (changes)
  {
    ++revision;
  }

  // TODO: update revision for dual-layer fog

  NI_PROFILE_BLOCK("WarFogFill")

  if (NDb::WARFOGTYPE_DUALLAYER == warFogType)
  {
    for (int team = 0; team < visibilityMap.size(); ++team)
    {
      VisMap& visMap = visibilityMap[team];
      VisMapMask& visMapMask = visibilityMapMask[team];

      for (int j = 0; j < height; ++j)
      {
        VisMap::SubArray visMapRow = visMap[j];
        VisMapMask::SubArray visMapMaskRow = visMapMask[j];

        for (int k = 0; k < width; ++k)
        {
          VisMap::ValueType& value = visMapRow[k];
          VisMapMask::ValueType& mask_value = visMapMaskRow[k];

          mask_value = mask_value || (value != 0);
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FogOfWar::DivideByVisTile(int toDivide) const
{
  return (toDivide+visTileSize-1) /visTileSize;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVector FogOfWar::ConvertToVisTile( const SVector & normalTile ) const
{
  return SVector(normalTile.x/visTileSize, normalTile.y/visTileSize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::AddObstacle( const vector<SVector> & tiles )
{
  NI_PROFILE_FUNCTION
  ChangeObstacle(tiles, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::RemoveObstacle( const vector<SVector> & tiles )
{
  NI_PROFILE_FUNCTION
  ChangeObstacle(tiles, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::FillVisibilityMap( const SVector & pos, const int visRad, const int team, const bool unmark/* = false*/ )
{
  const SVector & position = ConvertToVisTile(pos); 
  const int visRadius = DivideByVisTile(visRad); 
  int x = position.x;
  int y = position.y;

  CArray2D<byte> & visMap = visibilityMap[team];

  bool isPositionInsideTheMap = ( x >= 0 ) && ( x < visMap.GetSizeX() ) && ( y >= 0 ) && ( y < visMap.GetSizeY() );
  NI_VERIFY( isPositionInsideTheMap, NStr::StrFmt( "Unit at (%6.2f, %6.2f) is not inside the map!", x, y ), return; );

  // Mark center
  if( unmark )
    visMap[x][y]--;
  else
    visMap[x][y]++;

  if (circles.size() < visRadius)
    AddCircles(visRadius - circles.size(), circles);

  //
  TSectors sectors;

  for (int i = 0; i < visRadius; ++i)
  {
    vector<FogOfWar::TileData> & circle = circles[i];

    for (int j = 0; j < circle.size(); ++j)
    {
      SVector pos(circle[j].x, circle[j].y);
      pos += position;

      if (pos.x < 0 || pos.y < 0 || pos.x >= obstacles.GetSizeX() || pos.y >= obstacles.GetSizeY())
        continue;

      if (IsVisible(circle[j], sectors))
      {
        if( unmark )
          visMap[pos.x][pos.y]--;
        else
          visMap[pos.x][pos.y]++;
      }

      float heightDelta = heights[pos.x][pos.y] - heights[x][y];
      bool  heightLimit = useHeightsDelta && (heightDelta > maxHeightsDelta);

      // Has obstacle?
      if (obstacles[pos.x][pos.y] || heightLimit)
      {
        // Handle obstacleDeepVisibility only if not height limit
        if (!heightLimit && !circle[j].isVisible && i+1-circle[j].fromRadius < obstacleDeepVisibility )
        {
          if( unmark )
            visMap[pos.x][pos.y]--;
          else
            visMap[pos.x][pos.y]++;
        }
        // Add sector
        AddSector(FogOfWar::SectorData(circle[j].angleMin, circle[j].angleMax, i+1), sectors );
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ChangeObstacle( const vector<SVector> & tiles, bool remove )
{
  int minx = INT_MAX;
  int miny = INT_MAX;

  int maxx = 0;
  int maxy = 0;

  for (int i=0; i< tiles.size(); i++)
  {
    SVector visTile = ConvertToVisTile(tiles[i]);
    NI_VERIFY(visTile.x>=0 && visTile.x<=obstacles.GetSizeX(), "bad tile", continue);
    NI_VERIFY(visTile.y>=0 && visTile.y<=obstacles.GetSizeY(), "bad tile", continue);
    
    byte & tileVisValue = obstacles[visTile.x][visTile.y];
    remove? tileVisValue--: tileVisValue++;

    NI_VERIFY(tileVisValue>=0, "remove obstacle was called more times than add", tileVisValue=0);

    //determine border
    minx = min(minx, visTile.x);
    miny = min(miny, visTile.y);

    maxx = max(maxx, visTile.x);
    maxy = max(maxy, visTile.y);
  }

  //make border wider by maxRad
  minx = max(0, minx - maxRadius);
  miny = max(0, miny - maxRadius);
  maxx = min(maxx + maxRadius, width);
  maxy = min(maxy + maxRadius, height);

  for ( int i = 0; i<objects.size(); i++)
  {
    ObjectInfo & object = objects[i];
    
    if (object.newParams.position == BAD_POS)
      continue;

    int x = object.newParams.position.x;
    int y = object.newParams.position.y;

    bool isInRegion = x>=minx && x<=maxx && y>=miny && y<=maxy;

    if (isInRegion)
      object.isDirty = true;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FogOfWar::ObjectInfo::ObjectInfo()
 : isDirty(true)
 , isValidVisibleTiles(false)
 , lifeTime(-1.0f)
 , cancelHidingSectors(false)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ObjectInfo::UnMark(FogOfWar *pWarfog)
{
  NI_PROFILE_FUNCTION

  NI_VERIFY(pWarfog, "Can't unmark object on zero WarFog pointer!", return)

  if (!isValidVisibleTiles)
    return;

  const SVector origin(oldParams.position.x - oldParams.visRadius, oldParams.position.y - oldParams.visRadius);

  CArray2D<byte> & visibilityMap = pWarfog->visibilityMap[oldParams.team];

  for (int i = 0; i < visibleTiles.GetSizeX(); ++i)
  {
    for (int j = 0; j < visibleTiles.GetSizeY(); ++j)
    {
      if (!visibleTiles[i][j])
        continue;

      const int px = origin.x + i;
      const int py = origin.y + j;

      const bool shouldUnmark = CheckArrayIndex(visibilityMap, px, py);

      if (shouldUnmark)
        visibilityMap[px][py]--;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::ObjectInfo::Mark(FogOfWar *pWarfog)
{
  NI_PROFILE_FUNCTION

  NI_VERIFY(pWarfog, "Can't mark object on zero WarFog pointer!", return)

  CArray2D<byte> & visibilityMap = pWarfog->visibilityMap[newParams.team];
  vector<vector<TileData>> & circles = pWarfog->circles;

  const bool isPositionInsideTheMap = CheckArrayIndex(visibilityMap, newParams.position.x, newParams.position.y);

  NI_VERIFY( isPositionInsideTheMap, NStr::StrFmt( "Unit at (%d, %d) is not inside the map!", newParams.position.x, newParams.position.y ), return );

  const int newSize = newParams.visRadius * 2 + 1;

  if (visibleTiles.GetSizeX()!=newSize || visibleTiles.GetSizeY()!=newSize)
  {
    visibleTiles.SetSizes(newSize, newSize);
    potentiallyVisibleTiles.SetSizes(newSize, newSize);
  }

  visibleTiles.FillZero();
  potentiallyVisibleTiles.FillZero();

  // Mark center
  ShouldMarkTile(newParams.position);

  pWarfog->visibilityMap[newParams.team][newParams.position.x][newParams.position.y]++;

  isValidVisibleTiles = true;

  if (circles.size() < newParams.visRadius)
    AddCircles(newParams.visRadius - circles.size(), circles);

  //
  TSectors obstacleSectors;
  TSectors heightLimitSectors;

  for (int i = 0; i < newParams.visRadius; ++i)
  {
    vector<FogOfWar::TileData> & circle = circles[i];

    for (int j = 0; j < circle.size(); ++j)
    {
      SVector pos(circle[j].x, circle[j].y);

      pos += newParams.position;

      if (!CheckArrayIndex(pWarfog->obstacles, pos.x, pos.y))
        continue;

      if (IsVisible(circle[j], obstacleSectors))
      {
        if (IsVisible(circle[j], heightLimitSectors))
        {
          if (ShouldMarkTile(pos))
          {
            visibilityMap[pos.x][pos.y]++;
          }
        }
        else
          ShouldMarkTileAsHeightLimited(pos);
      }
      
      
      if( cancelHidingSectors ) continue; // prevent hiding tiles by sectors

      // Has obstacle?
      if (pWarfog->obstacles[pos.x][pos.y])
      {
        // Handle obstacleDeepVisibility only if not height limit
        if (!circle[j].isVisible && i+1-circle[j].fromRadius < pWarfog->obstacleDeepVisibility)
        {
          if (ShouldMarkTile(pos))
            visibilityMap[pos.x][pos.y]++;
        }
        // Add sector
        AddSector(FogOfWar::SectorData(circle[j].angleMin, circle[j].angleMax, i+1), obstacleSectors);
      }

      float heightDelta = pWarfog->heights[pos.x][pos.y] - pWarfog->heights[newParams.position.x][newParams.position.y];
      bool  heightLimit = pWarfog->useHeightsDelta && (heightDelta > pWarfog->maxHeightsDelta);

      if (heightLimit)
        AddSector(FogOfWar::SectorData(circle[j].angleMin, circle[j].angleMax, i+1), heightLimitSectors);
    }
  }

#ifndef _SHIPPING
  _obstacleSectors.clear();
  _heightLimitSectors.clear();

  nstl::copy(obstacleSectors.begin(), obstacleSectors.end(), nstl::back_inserter(_obstacleSectors));
  nstl::copy(heightLimitSectors.begin(), heightLimitSectors.end(), nstl::back_inserter(_heightLimitSectors));
#endif // _SHIPPING
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FogOfWar::ObjectInfo::ShouldMarkTile( const SVector & tile )
{
  SVector relative = tile - newParams.position + SVector(newParams.visRadius, newParams.visRadius);

  bool markTile = (visibleTiles[relative.x][relative.y] == 0);
  visibleTiles[relative.x][relative.y]++;
  return markTile;
}

bool FogOfWar::ObjectInfo::ShouldMarkTileAsHeightLimited( const SVector & tile )
{
  SVector relative = tile - newParams.position + SVector(newParams.visRadius, newParams.visRadius);

  bool markTile = (potentiallyVisibleTiles[relative.x][relative.y] == 0);
  potentiallyVisibleTiles[relative.x][relative.y]++;
  return markTile;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PutColor(CArray2D<Render::Color> & image, const Render::Color & color, int x, int y)
{
  const int pngTileSize = 3;

  for( int y1 = y * pngTileSize; y1 < y * pngTileSize + pngTileSize - 1; ++y1 )
  {
    for( int x1 = x * pngTileSize; x1 < x * pngTileSize + pngTileSize - 1; ++x1 )
    {
      image[y1][x1] = (color*0.5 + image[y1][x1]*0.5);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::Dump( const char* fileName)
{
  const int pngTileSize = 3;

  Render::Color teamUnitColors[3] = {Render::Color( 0, 255, 0 ), Render::Color( 0, 0, 255 ), Render::Color( 255, 0, 0)};
  Render::Color teamColors[3] = {teamUnitColors[0]*0.5, teamUnitColors[1]*0.5, teamUnitColors[2]*0.5};
  
  Render::Color obstacleColor = Render::Color(255,255,255);
  Render::Color freeColor = Render::Color(0,0,0);

  CArray2D<Render::Color> image( width * pngTileSize - 1, height * pngTileSize - 1 );
  image.FillEvery(freeColor);
 
  for( int y = 0; y < height; ++y )
  {
    for( int x = 0; x < width; ++x )
    {
      int invertY = height -1 - y;
      if (obstacles[x][y])
      {
        PutColor(image, obstacleColor, x, invertY);
      }

      for (int t=0; t<3; t++)
      {
        if (visibilityMap[t][x][y])
          PutColor(image, teamColors[t], x, invertY);
      }
    }
  }

  for (int i=0; i<objects.size(); i++)
  {
    Render::Color color = teamUnitColors[objects[i].oldParams.team];
    int x = objects[i].oldParams.position.x;
    int y = height -1-objects[i].oldParams.position.y;
    PutColor(image, color, x, y);
  }

  CObj<Stream> file = new FileStream( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
  NImage::WriteImageTGA( file, image );
}

void FogOfWar::MakeAllVisible()
{
  for (int i=0; i<visibilityMap.size(); i++)
  {
    visibilityMap[i].FillEvery(255);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DumpWarFog( const char *name, const vector<wstring> &params )
{
  if ( !g_warFog )
    return true;

  g_warFog->Dump( NDebug::GenerateDebugFileName( "warFog", "tga" ).c_str() );
  
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateMinMaxTile( const NWorld::TileMap * pTileMap, const CVec2 & point, SVector & min, SVector & max )
{
  const SVector tile = pTileMap->GetTile( point );
  min.x = Min( min.x, tile.x );
  min.y = Min( min.y, tile.y );
  max.x = Max( max.x, tile.x );
  max.y = Max( max.y, tile.y );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
  const Render::Color color1(  0, 255,   0);		// green
  const Render::Color color2( 96,  96,  96);		// grey
  const Render::Color color3(255,   0,   0);		// red
  const Render::Color color4(128,   0,   0);		// dark red
  const Render::Color color5(255, 255,   0);		// yellow
  const Render::Color color6(128, 128,   0);		// dark yellow

  const Render::Color sectorColor1(255, 120, 0, 255);
  const Render::Color sectorColor2(0, 120, 255, 255);
}

void DrawWarFogTile(const CVec3 & pos, const Render::Color * color, float warfogToWorld, float margin)
{
  CVec3 v[4];

  v[0].Set(pos.x + margin                , pos.y + margin                , pos.z);
  v[1].Set(pos.x + warfogToWorld - margin, v[0].y                        , pos.z);
  v[2].Set(v[1].x                        , pos.y + warfogToWorld - margin, pos.z);
  v[3].Set(v[0].x                        , v[2].y                        , pos.z);

  Render::DebugRenderer::DrawLine3D(v[0], v[1], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[1], v[2], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[2], v[3], *color, *color, false);
  Render::DebugRenderer::DrawLine3D(v[3], v[0], *color, *color, false);
}

void DrawWarFogSector(const CVec3 & pos, const Render::Color& color, const FogOfWar::SectorData& sector, const float tileSize = 1.f)
{
  static const float step = FP_2PI / 36.f;

  const float a = Min(sector.angleMin, sector.angleMax);
  const float b = Max(sector.angleMin, sector.angleMax);
  const float r = float(sector.fromRadius) * tileSize;

  const float ia = floorf(a / step) * step;
  const float ib = ceilf(b / step) * step;

  NI_VERIFY(ia < ib, "Invalid sector", return);

  vector<CVec3> points;

  for (float alpha = ia; alpha < ib; alpha += step)
  {
    const float angle = Clamp(alpha, a, b);

    CVec3& p = points.push_back();

    p.x = pos.x + r * cosf(angle);
    p.y = pos.y + r * sinf(angle);
    p.z = pos.z;
  }

  Render::DebugRenderer::DrawLine3D(pos, points.front(), color, color, false);

  for (int i = 0, j = 1, count = points.size(); j < count; ++i, ++j)
    Render::DebugRenderer::DrawLine3D(points[i], points[j], color, color, false);

  Render::DebugRenderer::DrawLine3D(pos, points.back(), color, color, false);
}

typedef vector<FogOfWar::SectorData> SectorVector;

void DrawWarFogSectors(const CVec3 & pos, const Render::Color& color, const SectorVector& sectors, const float tileSize = 1.f)
{
  SectorVector::const_iterator it = sectors.begin();
  SectorVector::const_iterator it_end = sectors.end();
  for (; it != it_end; ++it)
  {
    DrawWarFogSector(pos, color, *it);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FogOfWar::DrawWarFogDebug(NWorld::PFWorld* pWorld) const
{
#ifndef _SHIPPING
  if (g_showWarFog == 0 || g_showWarFog > 3)
    return;

  const NWorld::TileMap * pTileMap = pWorld->GetTileMap();
  const NScene::IScene * pScene = pWorld->GetScene();
  if (!pTileMap || !pScene)
    return;

  const IRenderableScene * pRenderableScene = pScene->GetRenderScene();
  if (!pRenderableScene)
    return;

  const FrustumIntersection & fi = pRenderableScene->GetCameraFrustumIntersection();  

  SVector min, max;
  min = max = pTileMap->GetTile(fi.points[0]);
  UpdateMinMaxTile(pTileMap, fi.points[1], min, max);
  UpdateMinMaxTile(pTileMap, fi.points[2], min, max);
  UpdateMinMaxTile(pTileMap, fi.points[3], min, max);
  min.x = Max(0, min.x / visTileSize);
  min.y = Max(0, min.y / visTileSize);
  max.x = Min(heights.GetSizeX() - 1, max.x / visTileSize);
  max.y = Min(heights.GetSizeY() - 1, max.y / visTileSize);

  float warfogToWorld = visTileSize * pTileMap->GetTileSize();
  CVec3 v[4];

  // Draw all warfog tiles in the camera frustum
  for ( int x = min.x; x <= max.x; ++x)
  {
    for ( int y = min.y; y < max.y; ++y)
    {
      CVec3 pos((float)x * warfogToWorld, (float)y * warfogToWorld, heights[x][y]);
      bool isTileVisible = visibilityMap[g_showWarFog-1][x][y];
      Render::Color const * color = (isTileVisible) ? (&color1) : (&color2);

      DrawWarFogTile(pos, color, warfogToWorld, 0.1f);

      // Draw obstacle if set at current tile
      if (obstacles[x][y])
      {
        Render::Color const * color = (isTileVisible) ? (&color3) : (&color4);

        DrawWarFogTile(pos, color, warfogToWorld, 0.3f);
      }
    }
  }

  // Draw all objects
  for (int i = 0; i < objects.size(); ++i)
  {
    int warfogX = objects[i].newParams.position.x;
    int warfogY = objects[i].newParams.position.y;

    if (warfogX < 0 || warfogX >= heights.GetSizeX()
        || warfogY < 0 || warfogY >= heights.GetSizeY())
      continue;

    CVec3 pos((float)warfogX * warfogToWorld, (float)warfogY * warfogToWorld, heights[warfogX][warfogY]);
    Render::Color const * color = (visibilityMap[g_showWarFog-1][warfogX][warfogY]) ? (&color5) : (&color6);

    DrawWarFogTile(pos, color, warfogToWorld, 0.3f);

    DrawWarFogSectors(pos, sectorColor1, objects[i]._obstacleSectors, visTileSize);
    DrawWarFogSectors(pos, sectorColor2, objects[i]._heightLimitSectors, visTileSize);
  }
#endif // _SHIPPING
}

REGISTER_DEV_CMD( dump_warfog, DumpWarFog );
REGISTER_DEV_VAR("show_war_fog",  g_showWarFog,  STORAGE_NONE);

} // namespace NWorld


REGISTER_WORLD_OBJECT_NM(FogOfWar,  NWorld)
