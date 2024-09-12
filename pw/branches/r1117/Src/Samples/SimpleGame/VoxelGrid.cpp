#include "stdafx.h"

#include "DebugDraw.h"
#include "VoxelGrid.h"
#include "World.h"

namespace Location 
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VoxelGrid::VoxelGrid() :
  minX(0.f), 
  maxX(0.f), 
  minY(0.f), 
  maxY(0.f), 
  widthN(1), 
  heightN(1),
  cellSizeX(1.f), 
  cellSizeY(1.f) 
{
  emptyElement.thisElement = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VoxelGrid::~VoxelGrid()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VoxelGrid::GetCoords( float x, float y, VoxelCoords& coords )
{
  if ( x < minX || maxX < x || y < minY || maxY < y )
    return false;

  coords.x = floorf( ( x - minX ) / cellSizeX );
  coords.y = floorf( ( y - minY ) / cellSizeY );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VoxelGrid::Setup( float _minX, float _maxX, float _minY, float _maxY, byte _widthN, byte _heightN )
{
  minX = _minX;
  maxX = _maxX;
  minY = _minY;
  maxY = _maxY; 
  widthN = _widthN; 
  heightN = _heightN;  

  if ( minX > maxX )
    minX = maxX;

  if ( minY > maxY )
    minY = maxY;

  cellSizeX = ( maxX - minX ) / static_cast<float>( widthN );
  cellSizeY = ( maxY - minY ) / static_cast<float>( heightN );

  voxels.SetSizes( widthN, heightN );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VoxelGrid::PreAlloc()
{
  for ( int i = 0; i < widthN; ++i )
  {
    for ( int j = 0; j < heightN; ++j )
    {
      voxels[i][j].players.PreAlloc();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoolElement& VoxelGrid::AddObject( float x, float y, int objectID )
{
  VoxelCoords coords;

  if ( GetCoords( x, y, coords ) )
  {
    PoolElement& element = voxels.Get( coords.x, coords.y ).players.AllocAndGet();

    element.objectID = objectID;
    element.cellX = coords.x;
    element.cellY = coords.y;

    return element;
  }

  return emptyElement;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoolElement& VoxelGrid::AddObjectAtCell( byte x, byte y, int objectID )
{
  PoolElement& element = voxels.Get( x, y ).players.AllocAndGet();

  element.objectID = objectID;
  element.cellX = x;
  element.cellY = y;

  return element;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VoxelGrid::RemoveObject( PoolElement& element )
{
  if ( element.cellX != -1 && element.cellY != -1 )
  {
    voxels.Get( element.cellX, element.cellY ).players.Free( element.thisElement );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VoxelGrid::Clear()
{
  for ( int i = 0; i < widthN; ++i )
  {
    for ( int j = 0; j < heightN; ++j )
    {
      voxels[i][j].players.Clear();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VoxelGrid::Draw( Location::IDebugDraw* debugDraw ) const
{
  if ( !debugDraw )
    return;

  for ( int i = 0; i <= widthN; ++i )
  {
    CVec3 point1( minX + float(i) * cellSizeX, minY, TownDebug::TOWN_GROUND_Z); 
    CVec3 point2( minX + float(i) * cellSizeX, maxY, TownDebug::TOWN_GROUND_Z); 

    debugDraw->DrawLine( point1.x, point1.y, point2.x, point2.y );
  }

  for ( int j = 0; j <= heightN; ++j )
  {
    CVec3 point1( minX, minY + float(j) * cellSizeY, TownDebug::TOWN_GROUND_Z); 
    CVec3 point2( maxX, minY + float(j) * cellSizeY, TownDebug::TOWN_GROUND_Z); 

    debugDraw->DrawLine( point1.x, point1.y, point2.x, point2.y );
  }
}

} // namespace Location