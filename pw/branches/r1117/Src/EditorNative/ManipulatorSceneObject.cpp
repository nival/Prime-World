#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "ManipulatorSceneObject.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

void ManipulatorSceneObject::CalculateNewLocation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene )
{
  if ( mover != nullptr )
  {
    mover->CalculateNewLocation( initialCursorPosition, delta, scene );
  }
  else if ( scaler != nullptr )
  {
    scaler->CalculateNewScale( initialCursorPosition, delta, scene );
  }
  else if ( rotator != nullptr )
  {
    rotator->CalculateNewRotation( initialCursorPosition, delta, scene );
  }
}

void ManipulatorSceneObject::Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene )
{
  if ( mover != nullptr )
  {
    mover->Select( cursorPositionManaged, scene );
  }
  else if ( scaler != nullptr )
  {
    scaler->Select( cursorPositionManaged, scene );
  }
  else if ( rotator != nullptr )
  {
    rotator->Select( cursorPositionManaged, scene );
  }
}

void ManipulatorSceneObject::Draw( NScene::IScene& scene )
{
  if ( mover != nullptr )
  {
    mover->Draw( scene );
  }
  else if ( scaler != nullptr )
  {
    scaler->Draw( scene );
  }
  else if ( rotator != nullptr )
  {
    rotator->Draw( scene );
  }
}

void ManipulatorSceneObject::Create( System::IntPtr _scene )
{
  if ( mover != nullptr )
  {
    mover->Create( _scene );
  }
  else if ( scaler != nullptr )
  {
    scaler->Create( _scene );
  }
  else if ( rotator != nullptr )
  {
    rotator->Create( _scene );
  }
}