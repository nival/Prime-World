#ifndef VOXELGRID_H_FEFD6C9A_C7FB_48DE_A
#define VOXELGRID_H_FEFD6C9A_C7FB_48DE_A

#include <System/PooledContainer.h>
#include <System/2DArray.h>

#include "Protocol.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
  _interface IDebugRender;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

_interface IDebugDraw;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PoolElement
{
  int objectID;

  byte cellX;
  byte cellY;

  int thisElement;
  int nextElement;
  int prevElement;

  PoolElement() : objectID(Protocol::invalidObjectId), thisElement(-1), nextElement(-1), prevElement(-1), cellX(0), cellY(0) {}
};

#ifdef TOWN_SIMULATION
  typedef PooledContainer<PoolElement, 1> PlayerContainer;
#else
  typedef PooledContainer<PoolElement, 1024> PlayerContainer;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VoxelDesc
{
  PlayerContainer players;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef CTPoint<byte> VoxelCoords; 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VoxelGrid
{
public:
  VoxelGrid();
  virtual ~VoxelGrid();

  bool GetCoords( float x, float y, VoxelCoords& coords );  
  void Setup( float _minX, float _maxX, float _minY, float _maxY, byte _widthN, byte _heightN );
  void PreAlloc();

  PoolElement& AddObject( float x, float y, int objectID );
  PoolElement& AddObjectAtCell( byte x, byte y, int objectID );
  void RemoveObject( PoolElement& element );

  void Clear();

  // TFunc( int _objectID )
  template < typename TFunc >
  void ForAllNeighbours( int x, int y, int radius, TFunc &func ) const
  { 
    int startX = max( 0, x - radius );
    int stopX = min( widthN - 1, x + radius );
    int startY = max( 0, y - radius );
    int stopY = min( heightN - 1, y + radius );

    for ( int i = startX; i <= stopX; ++i )
    {
      for ( int j = startY; j <= stopY; ++j )
      {
        ForAllInVoxel( i, j, func );
      }
    }
  }

  // TFunc( int _objectID )
  template < typename TFunc >
  void ForAllNeighboursDelta( int x, int y, int sx, int sy, int radius, TFunc &func ) const
  { 
    if ( sx != 0 )
    {
      int startY = max( 0, y + sy - radius );
      int stopY = min( heightN - 1, y + sy + radius );

      int _X1 = x + sx - radius;
      int _X2 = x + sx + radius;

      if ( sx < 0 && _X1 >= 0 )
      {
        for ( int j = startY; j <= stopY; ++j )
        {
          ForAllInVoxel( _X1, j, func );
        }
      }

      if ( sx > 0 && _X2 < widthN )
      {
        for ( int j = startY; j <= stopY; ++j )
        {
          ForAllInVoxel( _X2, j, func );
        }
      }
    }

    if ( sy != 0 )
    {
      int startX = sx < 0 ? max( 0, x - radius ) : max( 0, x + sx - radius );
      int stopX = sx > 0 ? min( widthN - 1, x + radius ) : min( widthN - 1, x + sx + radius );

      int _Y1 = y + sy - radius;
      int _Y2 = y + sy + radius;

      if ( sy < 0 && _Y1 >= 0 )
      {
        for ( int i = startX; i <= stopX; ++i )
        {
          ForAllInVoxel( i, _Y1, func );
        }
      }

      if ( sy >= 0 && _Y2 < heightN )
      {
        for ( int i = startX; i <= stopX; ++i )
        {
          ForAllInVoxel( i, _Y2, func );
        }
      }
    }
  }

  // TFunc( int _objectID )
  template < typename TFunc >
  void ForAllInVoxel( int x, int y, TFunc &func ) const
  { 
    PlayerContainer::const_iterator it = voxels[y][x].players.Begin();
    PlayerContainer::const_iterator last = voxels[y][x].players.End();

    for (; it != last; ++it)
    {
      func( it->objectID );
    }
  }

  void Draw( Location::IDebugDraw* debugDraw ) const;

private:

  CArray2D<VoxelDesc> voxels;

  float minX; 
  float maxX; 
  float minY; 
  float maxY; 
  byte  widthN; 
  byte  heightN;
  float cellSizeX;
  float cellSizeY;

  PoolElement emptyElement;
};

} // namespace Location

#endif //#define VOXELGRID_H_FEFD6C9A_C7FB_48DE_A