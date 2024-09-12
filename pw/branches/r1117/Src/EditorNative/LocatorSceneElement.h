#pragma once

#include "../System/Placement.h"
#include "ISceneElement.h"
#include "EditorSceneComponent.h"
#include "EditorSceneObject.h"
#include "../Scene/ParticleSceneComponent.h"
#include "../Scene/AnimatedSceneComponent.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

public ref class LocatorSceneElement sealed : ISceneElement
{
  EditorSceneComponent^ sceneComponent;
	Placement* placement;
  libdb::UndoRedo::UndoRedoManager^ undoManager;
  nstl::string* locatorName;
  NScene::Locator* locator;

  Matrix43* worldMatrix;
public:
  LocatorSceneElement( EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager, System::String^ _locator );
	~LocatorSceneElement()
	{
		this->!LocatorSceneElement();
	}
	!LocatorSceneElement()
	{
		delete placement;
		delete locatorName;
		delete worldMatrix;
		if ( locator )
			delete locator;
	}

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
