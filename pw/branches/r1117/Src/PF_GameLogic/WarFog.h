#pragma once

#include "System/2DArray.h"
#include "PFWorldObjectBase.h"

#include "DI/DI.hpp"

namespace NScene
{
  struct IHeightsController;
}

namespace NWorld
{
  static const int WAR_FOG_BAD_ID = -1;

  class FogOfWar
    : public PFWorldObjectBase
    , public DI::SelfProvider<FogOfWar>
  {
    WORLD_OBJECT_METHODS( 0x8B7A2380, FogOfWar );
  public:
    struct TileData
    {
      ZDATA
      int   x;
      int   y;
      float angleMin;
      float angleMid;
      float angleMax;
      int   fromRadius;
      bool  isVisible;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&x); f.Add(3,&y); f.Add(4,&angleMin); f.Add(5,&angleMid); f.Add(6,&angleMax); f.Add(7,&fromRadius); f.Add(8,&isVisible); return 0; }

      TileData()
        : x(0)
        , y(0)
        , angleMin(0.0f)
        , angleMid(0.0f)
        , angleMax(0.0f)
        , fromRadius(0)
        , isVisible(false)
      {
      }

      TileData(int _x, int _y, float _angleMin, float _angleMid, float _angleMax)
        : x(_x)
        , y(_y)
        , angleMin(_angleMin)
        , angleMid(_angleMid)
        , angleMax(_angleMax)
        , fromRadius(0)
        , isVisible(true)
      {
      }
    };

    struct SectorData
    {
      ZDATA
      float angleMin;
      float angleMax;
      int   fromRadius;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&angleMin); f.Add(3,&angleMax); f.Add(4,&fromRadius); return 0; }

      SectorData()
        : angleMin(0.0f)
        , angleMax(0.0f)
        , fromRadius(0)
      {
      }

      SectorData(float _angleMin, float _angleMax, int _fromRadius)
        : angleMin(_angleMin)
        , angleMax(_angleMax)
        , fromRadius(_fromRadius)
      {
      }
    };

    typedef CArray2D<byte> VisMap;
    typedef CArray2D<bool> VisMapMask;

    FogOfWar(PFWorld* pWorld, int teams, int _width, int _height, int _visTileSize, int _obstacleDeepVisibility);
    virtual ~FogOfWar();

    void ApplyHeightMap( const CArray2D<float>& _heights, const NScene::IHeightsController& heightsController );
    void ApplyHeightSettings( bool _useHeightsDelta, float _maxHeightsDelta );

    void AddObstacle( const vector<SVector> & tiles );
    void RemoveObstacle( const vector<SVector> & tiles );

    int AddObject( const SVector& position, int team, int visRadius, const bool cancelHidingSectors = false );
    void AddTempObject( const SVector& position, int team, int visRadius, float lifeTime);

    void Reset();
    void ResetVisibility();
    void FillVisibilityMap( const SVector & pos, const int visRad, const int team, const bool unmark = false );

    void MoveObject( int id, const SVector& position );

    void ChangeVisibility( int id, int visRadius );
    void ChangeTeam( int id, int team );
    void RemoveObject( int id );

    virtual bool Step(float dt);
    void StepVisibility(float dt);

    bool IsTileVisible( const SVector& tile, int team ) const;

    bool CanObjectSeePosition(int id, const SVector & target) const;

    void MakeAllVisible();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetVisTileSize() const { return visTileSize; }

    unsigned GetRevision() const { return revision; }

    const VisMap* GetVisMap(const uint team) const
    {
      if (team < static_cast<uint>(visibilityMap.size()))
        return &visibilityMap[team];
      return NULL;
    }
    const VisMapMask* GetVisMapMask(const uint team) const
    {
      if (team < static_cast<uint>(visibilityMapMask.size()))
        return &visibilityMapMask[team];
      return NULL;
    }

    void Dump( const char* fileName);
    void DrawWarFogDebug(NWorld::PFWorld* pWorld) const;

    void SetWarFogType(NDb::WarFogType _type) { warFogType = _type; }

  private:
    struct SVectorHash
    {
      int operator()( const SVector& vec ) const { return vec.x ^ vec.y; }
    };

    typedef hash_map<SVector, vector<SVector>, SVectorHash> Bresenhams;

    struct ObjectParams
    {
      ZDATA
      SVector position;
      int team;
      int visRadius;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&position); f.Add(3,&team); f.Add(4,&visRadius); return 0; }

      ObjectParams() : position(0, 0), team(0), visRadius(0) {};
    };

    struct ObjectInfo
    {
      ZDATA
      CArray2D<byte>  visibleTiles;
      CArray2D<byte>  potentiallyVisibleTiles; //tiles that hidden by height limited but they can be seen with help field of view of a teammate (or ward)
      ObjectParams    oldParams;
      ObjectParams    newParams;
      bool            isDirty;
      bool            isValidVisibleTiles;
      float           lifeTime;
      bool            cancelHidingSectors;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&visibleTiles); f.Add(3,&potentiallyVisibleTiles); f.Add(4,&oldParams); f.Add(5,&newParams); f.Add(6,&isDirty); f.Add(7,&isValidVisibleTiles); f.Add(8,&lifeTime); f.Add(9,&cancelHidingSectors); return 0; }

#ifndef _SHIPPING
      vector<SectorData>  _obstacleSectors;
      vector<SectorData>  _heightLimitSectors;
#endif // _SHIPPING

      ObjectInfo();

      void UnMark(FogOfWar *pWarfog);
      void Mark(FogOfWar *pWarfog);
      bool ShouldMarkTile(const SVector & tile);
      bool ShouldMarkTileAsHeightLimited( const SVector & tile );
    };

    FogOfWar()
      : visTileSize(1)
    {
    }

    vector<vector<TileData>> circles;

    CArray2D<float> heights;

    ZDATA_(PFWorldObjectBase)
    ZNOPARENT( DI::SelfProvider<FogOfWar> )
    vector<VisMap> visibilityMap;
    vector<ObjectInfo> objects;
    CArray2D<byte> obstacles;

    int obstacleDeepVisibility;

    int width;
    int height;

    int visTileSize;

    int maxRadius;
    bool useHeightsDelta;
    float maxHeightsDelta;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&visibilityMap); f.Add(3,&objects); f.Add(4,&obstacles); f.Add(5,&obstacleDeepVisibility); f.Add(6,&width); f.Add(7,&height); f.Add(8,&visTileSize); f.Add(9,&maxRadius); f.Add(10,&useHeightsDelta); f.Add(11,&maxHeightsDelta); return 0; }

  private:
    int DivideByVisTile(int toDivide) const;
    SVector ConvertToVisTile(const SVector & normalTile) const;

    void ChangeObstacle( const vector<SVector> & tiles, bool remove);

    bool IsValidObjectIndex(const int index) const
    {
      if (index == WAR_FOG_BAD_ID)
        return false;

      if (index < 0)
        return false;
      if (index >= objects.size())
        return false;

      return true;
    }

    bool IsValidPosition(const int x, const int y) const
    {
      if (x < 0)
        return false;
      if (y < 0)
        return false;
      if (x >= width)
        return false;
      if (y >= height)
        return false;

      return true;
    }

    bool IsValidTeam(const int team) const
    {
      if (team < 0)
        return false;
      if (team >= visibilityMap.size())
        return false;

      return true;
    }

    vector<VisMapMask> visibilityMapMask;

    NDb::WarFogType warFogType;

    unsigned revision;
  };
} // namespace NWorld
