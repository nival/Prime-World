#include "StdAfx.h"
#include "EditorScene.h"
#include "RoadWrapper.h"

namespace EditorNative {
namespace SceneElements {


RoadWrapper::RoadWrapper( DBTypes::Road^ _road, DBTypes::Placement2^ place, EditorScene^ _scene )
{
  // what is the use-case? [5/12/2010 smirnov]
  if ( libdb::DB::DBID::IsNullOrEmpty( _road->DBId ) )
  {
    // manually convert database structure to native one
    NDb::Road nativeRoad;
    nativeRoad.properties = ToNativeProperties(_road->properties);
    nativeRoad.points.resize(_road->points->Count);
    for (int i = 0; i < _road->points->Count; ++i)
      nativeRoad.points.push_back(ToNativePoint(_road->points[i]));

    road = new NScene::RoadSceneObject( _scene->NativeScene, &nativeRoad, true );
  }
  else
  {
    // access native database structure
    road = new NScene::RoadSceneObject( _scene->NativeScene, GetObject<NDb::Road>( _road->DBId ), true );
  }

  road->AddToScene( _scene->NativeScene );

  disposed = false;
}

RoadWrapper::~RoadWrapper()
{
  // Call C++ finalizer to clean up unmanaged resources.
  this->!RoadWrapper();

  // Mark the class as disposed. This flag allows you to throw an
  // exception if a disposed object is accessed.
  disposed = true;
}

// The C++ finalizer destructor ensures that unmanaged resources get
// released if the user releases the object without explicitly 
// disposing of it.
RoadWrapper::!RoadWrapper()
{
  if ( road )
  {
    road->RemoveFromScene();
    delete road;
    road = 0;
  }
}

DBTypes::RoadControlPoint^ RoadWrapper::GetPoint( int index )
{
  DBTypes::RoadControlPoint^ result = gcnew DBTypes::RoadControlPoint();
  
  result->location->x = 0;
  result->location->y = 0;
  result->width = 0;
  
  return result;
}

int RoadWrapper::GetPointsCount()
{
  return 0;
}

bool RoadWrapper::IsIntersectWith( float terrainX, float terrainY, EditorNative::Vector3^ pickLocation )
{
  CVec3 vec;
  vec.Set(pickLocation->X, pickLocation->Y, pickLocation->Z);

  return road->IsIntersectWith(terrainX, terrainY, vec);
}

void RoadWrapper::Rebuild()
{
  road->Rebuild(false);
}

void RoadWrapper::Store(System::String^ fileName)
{
  CObj<Stream> pStream = RootFileSystem::OpenFile( ToMBCS(fileName), FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
  NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open road baked file for writing %s", fileName ), return );
  
  road->Store(pStream);
}

NDb::RoadControlPoint RoadWrapper::ToNativePoint(DBTypes::RoadControlPoint^ _point)
{
  NDb::RoadControlPoint result = NDb::RoadControlPoint();
  
  result.location.x = _point->location->x;
  result.location.y = _point->location->y;
  result.width = _point->width;

  return result;
}

NDb::RoadProperties RoadWrapper::ToNativeProperties(DBTypes::RoadProperties^ _properties)
{
  return NDb::RoadProperties();
}

Placement RoadWrapper::ToNativePlacement(DBTypes::Placement2^ _placement)
{
  Placement placement;

  placement.pos.x = _placement->translateX;
  placement.pos.y = _placement->translateY;
  placement.pos.z = _placement->translateZ;

  placement.rot.x = _placement->rotationX;
  placement.rot.y = _placement->rotationY;
  placement.rot.z = _placement->rotationZ;
  placement.rot.w = 1.f;

  placement.scale.x = _placement->scaleX;
  placement.scale.y = _placement->scaleY;
  placement.scale.z = _placement->scaleZ;

  return placement;
}

}// namespace EditorNative
}// namespace SceneElements
