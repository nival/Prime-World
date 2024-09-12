#pragma once

#include "../System/Placement.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"
#include "EditorSceneObject.h"
#include "../Scene/CollisionGeometry.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

public ref class CollSceneObject : EditorSceneObject
{
  NScene::CollisionGeometry* colGeom;

public:
  CollSceneObject( libdb::DB::DBID^ _dbId );
  ~CollSceneObject()
  {
    this->!CollSceneObject();
  }
  !CollSceneObject()
  {
    //delete colGeom;
  }
  virtual void Draw( NScene::IScene& scene ) override;
  virtual NScene::EditorSceneObject* CreateNativeObject( NScene::IScene& scene ) override
  {
    return CreateNativeObject( scene, true );
  }

};
}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
