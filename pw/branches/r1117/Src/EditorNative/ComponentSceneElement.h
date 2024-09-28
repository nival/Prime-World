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

public ref class ComponentSceneElement : ISceneElement
{
protected:
  EditorSceneComponent^ sceneComponent;
  Placement* placement;
  libdb::UndoRedo::UndoRedoManager^ undoManager;

  Placement* offset;

  Placement* dbPlacement;


public:
  ComponentSceneElement(EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager);

  virtual void Apply( bool isMoved, bool isRotated, bool isScaled );

  virtual void Create( System::IntPtr _scene ) {}
  virtual void Delete( System::IntPtr _scene ) {}
  virtual void Reinit() {}
  virtual void Draw( NScene::IScene& scene );
  virtual void SetPlacement( const Placement& _placement );
  virtual const Placement& GetPlacement();
  void InitPlacement( DBTypes::Placement^ from );
  DBTypes::Placement^ GetInitPlacement();
  DBTypes::Placement^ GetDBPlacement();
  virtual void Update( float delta ) {}
  virtual void Die() {}
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
