#pragma once

#include "../System/Placement.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"
#include "Utility.h"
#include "SimpleEditorScene.h"
#include "MoveManipulatorSceneComponent.h"
#include "ScaleManipulatorSceneComponent.h"
#include "RotateManipulatorSceneComponent.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class ManipulatorSceneObject sealed : ISceneElement
{
  ISceneElement^ controlItem;

  MoveManipulatorSceneComponent^ mover;
  ScaleManipulatorSceneComponent^ scaler;
  RotateManipulatorSceneComponent^ rotator;

   bool isMoved;
   bool isRotated;
   bool isScaled;

	 EditorNative::ManipulatorTypes mode;

public:

  ManipulatorSceneObject( ISceneElement^ _controlItem )
  : controlItem ( _controlItem )
  {
    isMoved = false;
    isRotated = false;
    isScaled = false;
    mover = nullptr;
    scaler = nullptr;
    rotator = nullptr;
    mover = gcnew MoveManipulatorSceneComponent( controlItem );
    //scaler = gcnew ScaleManipulatorSceneComponent( controlItem );
    //rotator = gcnew RotateManipulatorSceneComponent( controlItem );
  }

  void Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene );

  void CalculateNewLocation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene );

  virtual void Create( System::IntPtr _scene );
  virtual void Delete( System::IntPtr _scene ) {}
  virtual void Reinit() {}
  virtual void Draw( NScene::IScene& scene );
  virtual void Apply( bool _isMoved, bool _isRotated, bool _isScaled ) 
  {
    if ( !isMoved && !isRotated && !isScaled )
      return;
    if ( controlItem != nullptr )
    {
      controlItem->Apply( isMoved, isRotated, isScaled );
      isMoved = false;
      isRotated = false;
      isScaled = false;
    }
  }
  virtual void Update( float delta ) {}
  virtual void Die() {}
  virtual void SetPlacement( const Placement& placement ) {}
  virtual const Placement& GetPlacement()
  {
    return NULLPLACEMENT;
  }

	EditorNative::ManipulatorTypes GetMode()
	{
		return mode;
	}

  void SetMode( EditorNative::ManipulatorTypes _mode )
  {
		mode = _mode;
		if ( mode == EditorNative::ManipulatorTypes::Mover )
    {
      scaler = nullptr;
      rotator = nullptr;
      mover = gcnew MoveManipulatorSceneComponent( controlItem );
      isMoved = true;
      return;
    }
    if ( mode == EditorNative::ManipulatorTypes::Rotator )
    {
      mover = nullptr;
      scaler = nullptr;
      rotator = gcnew RotateManipulatorSceneComponent( controlItem );
      isRotated = true;
    }
    if ( mode == EditorNative::ManipulatorTypes::Scaler )
    {
      mover = nullptr;
      rotator = nullptr;
      scaler = gcnew ScaleManipulatorSceneComponent( controlItem );
      isScaled = true;
    }
  }
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
