#pragma once

#include "../System/Placement.h"
#include "ISceneElement.h"
#include "EditorSceneComponent.h"
#include "../Scene/ParticleSceneComponent.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/StaticSceneComponent.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

public ref class AABBSceneElement sealed : ISceneElement
{
  EditorSceneComponent^ sceneComponent;
  Placement* placement;
  libdb::UndoRedo::UndoRedoManager^ undoManager;
  
  Placement* placementToDraw;
  Placement* offset;

  Render::AABB* nativeAABB;
  Render::AABB* nativeAABBtoDraw;
  void InitPlacement( DBTypes::AABB^ aabb );
  void FillAABB( DBTypes::AABB^ aabb );


public:
  AABBSceneElement(EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager);

  void SetPlacementRot( float x, float y, float z, float w );
  
  virtual void Apply( bool isMoved, bool isRotated, bool isScaled );

  virtual void Create( System::IntPtr _scene ) {}
  virtual void Delete( System::IntPtr _scene ) {}
  virtual void Reinit() {}
  virtual void Draw( NScene::IScene& scene );
  virtual void SetPlacement( const Placement& _placement );
  virtual const Placement& GetPlacement();
  virtual void Update( float delta ) {}
  virtual void Die() {}
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
