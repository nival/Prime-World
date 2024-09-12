#pragma once
#include "../Scene/RoadSceneObject.h"
using namespace System;

namespace EditorNative {

  ref class EditorScene;

namespace SceneElements {

public ref class RoadWrapper: public IDisposable
{
public:
  RoadWrapper( DBTypes::Road^ road, DBTypes::Placement2^ place, EditorNative::EditorScene^ _scene);
  ~RoadWrapper();
  !RoadWrapper();

  DBTypes::RoadControlPoint^ GetPoint( int index );
  
  int GetPointsCount();
  
  bool IsIntersectWith( float terrainX, float terrainY, EditorNative::Vector3^ pickLocation );

  void Rebuild();

  void Store(System::String^ fileName);

private:
  bool disposed;   // Track whether Dispose has been called.

  NScene::RoadSceneObject* road;

  NDb::RoadControlPoint ToNativePoint(DBTypes::RoadControlPoint^ _point);
  NDb::RoadProperties ToNativeProperties(DBTypes::RoadProperties^ _properties);
  Placement ToNativePlacement(DBTypes::Placement2^ _placement);
};

}// namespace EditorNative
}// namespace SceneElements
