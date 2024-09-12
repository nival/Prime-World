#pragma once

#include "../System/Placement.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

public interface class ISceneElement
{
  virtual void Create( System::IntPtr _scene ) = 0;
  virtual void Delete( System::IntPtr _scene ) = 0;
  virtual void Reinit() = 0;
  virtual void Draw( NScene::IScene& scene ) = 0;
  virtual void SetPlacement( const Placement& placement ) = 0;
  virtual const Placement& GetPlacement() = 0;
  virtual void Apply( bool isMoved, bool isRotated, bool isScaled ) = 0;
  virtual void Update( float delta ) = 0;
  virtual void Die() = 0;
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
