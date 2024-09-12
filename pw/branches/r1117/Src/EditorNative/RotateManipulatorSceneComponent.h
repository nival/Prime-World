#pragma once

#include "../System/Placement.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"
#include "Utility.h"
#include "SimpleEditorScene.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

struct RotationData
{
  bool isCameraPlane;
  CQuat rotation;
  Render::Color color;

  RotationData( const CQuat& _rot, const Render::Color& _color, bool _isCameraPlane ) 
    : rotation( _rot ), color( _color ), isCameraPlane( _isCameraPlane ) {}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class RotateManipulatorSceneComponent sealed : ISceneElement
{
  static const float RADIUS = 0.5f;
  static const float CURSOR_HOT_SPOT_SIZE = 25.0f;
  static const float INITIAL_ROD = 10.0f;

  Placement* placement;
  ISceneElement^ controlItem;

  int selectedRotation;
  nstl::vector<RotationData>* rotations;

public:

  RotateManipulatorSceneComponent( ISceneElement^ _controlItem )
    : controlItem ( _controlItem ) 
  {
    selectedRotation = 0;
    rotations = new nstl::vector<RotationData>();
    rotations->push_back( RotationData( QNULL, Render::Color( 128, 255, 255 ), true ) );
    rotations->push_back( RotationData( QNULL, Render::Color( 0, 0, 255 ), false ) );
    rotations->push_back( RotationData( CQuat( float( PI / 2 ), V3_AXIS_Y ), Render::Color( 255, 0, 0 ), false ) );
    rotations->push_back( RotationData( CQuat( float( PI / 2 ), V3_AXIS_X ), Render::Color( 0, 255, 0 ), false ) );
    
    placement = new Placement(VNULL3, QNULL, CVec3(1.0f,1.0f,1.0f) );
    if ( controlItem != nullptr )
    {
      Placement curpos = controlItem->GetPlacement();
      *placement = curpos;
      //controlItem->SetPlacement( *placement );
    }
  }

  void Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene );

  void CalculateNewRotation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene );

  virtual void Create( System::IntPtr _scene ) {}
  virtual void Delete( System::IntPtr _scene ) {}
  virtual void Reinit() {}
  virtual void Draw( NScene::IScene& scene );
  virtual void SetPlacement( const Placement& placement ) {}
  virtual const Placement& GetPlacement() { return NULLPLACEMENT; }
  virtual void Apply( bool isMoved, bool isRotated, bool isScaled ) {}
  virtual void Update( float delta ) {}
  virtual void Die() {}

private:

  bool CanBeSelected( NScene::ICamera& camera, Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CQuat& rotation, bool isCameraPlane );

  float CalculateScale( const NScene::ICamera& camera )
  {
    NScene::SCameraPosition cameraPosition;
    camera.GetPosition( &cameraPosition );
    CVec3 cameraLocation = cameraPosition.vAnchor - cameraPosition.GetCameraDir() * cameraPosition.fRod;
    float scale = fabs( placement->pos - cameraLocation ) / INITIAL_ROD;
    return scale;
  }

  void DrawCircle( const nstl::vector<CVec3>& points, const Render::Color& color )
  {
    for ( int i = 0; i < points.size() - 1; ++i )
    {
      Render::DebugRenderer::DrawLine3D( points[i], points[i + 1], color, color, false );
    }
    Render::DebugRenderer::DrawLine3D( points[points.size() - 1], points[0], color, color, false );
  }

  nstl::vector<CVec3> CalculateCirclePoints( const NScene::ICamera& camera, int deltaDegree, const CQuat& rotationType, bool isCameraPlane );
  CQuat CalculateRotation( const NScene::ICamera& camera, const CQuat& rotation, bool isCameraPlane );
  int FindNearestPointIndex( const nstl::vector<CVec3>& points, const CVec2& cursorPosition, NScene::ICamera& camera, const CQuat& rotationType, bool isCameraPlane );
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
