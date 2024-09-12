#pragma once

#include "../System/Placement.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"
#include "Utility.h"
#include "SimpleEditorScene.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

struct AxisData
{
  CQuat axis;
  Render::Color color;
  bool isFreeMoving;

  AxisData( const CQuat& _axis, const Render::Color& _color, bool _isFreeMoving ) 
    : axis(_axis), color(_color), isFreeMoving(_isFreeMoving) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class MoveManipulatorSceneComponent sealed : ISceneElement
{
  static const float INITIAL_ROD = 6.0f;
  static const float CURSOR_HOT_SPOT_SIZE = 25.0f;
  static const float SIZE = 20.0f;

  Placement* placement;
  ISceneElement^ controlItem;

  int selectedAxis;
  nstl::vector<AxisData>* axis;

public:

  MoveManipulatorSceneComponent( ISceneElement^ _controlItem )
    : controlItem ( _controlItem ) 
  {
    selectedAxis = 0;
    axis = new nstl::vector<AxisData>();
    axis->push_back( AxisData( QNULL, Render::Color( 128, 255, 255 ), true ) );
    axis->push_back( AxisData( QNULL, Render::Color( 255, 0, 0 ), false ) );
    axis->push_back( AxisData( CQuat( float( PI / 2 ), V3_AXIS_Z ), Render::Color( 0, 255, 0 ), false ) );
    axis->push_back( AxisData( CQuat( float( -PI / 2 ), V3_AXIS_Y ), Render::Color( 0, 0, 255 ), false ) );

    placement = new Placement(VNULL3, QNULL, CVec3(1.0f,1.0f,1.0f) );
    if ( controlItem != nullptr )
    {
      Placement curpos = controlItem->GetPlacement();
      *placement = curpos;
      //controlItem->SetPlacement( *placement );
    }
  }

  void Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene );
  void CalculateNewLocation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene );
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

  bool CanBeSelected( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CQuat& tryAxis, bool isFreeMoving );

  float CalculateScale( const NScene::ICamera& camera )
  {
    NScene::SCameraPosition cameraPosition;
    camera.GetPosition( &cameraPosition );
    CVec3 cameraLocation = cameraPosition.vAnchor - cameraPosition.GetCameraDir() * cameraPosition.fRod;
    return fabs( placement->pos - cameraLocation ) / INITIAL_ROD;
  }

  void DrawArrow( NScene::ICamera& camera, const CQuat& rotation, const Render::Color& color, bool isFreeMoving )
  {
    if ( isFreeMoving )
    {
      const float size = SIZE;

      const CVec2 upLeft = PerformProjection( camera, placement->pos ) + CVec2( -size / 2, -size / 2 );
      const CVec2 upRight = upLeft + CVec2( size, 0 );
      const CVec2 downRight = upRight + CVec2( 0, size );
      const CVec2 downLeft = upLeft + CVec2( 0, size );

      Render::DebugRenderer::DrawLine2D( upLeft.x, upLeft.y, upRight.x, upRight.y, color, color );
      Render::DebugRenderer::DrawLine2D( upRight.x, upRight.y, downRight.x, downRight.y, color, color );
      Render::DebugRenderer::DrawLine2D( downRight.x, downRight.y, downLeft.x, downLeft.y, color, color );
      Render::DebugRenderer::DrawLine2D( downLeft.x, downLeft.y, upLeft.x, upLeft.y, color, color );
    }
    else
    {
      const CVec3 begin = placement->pos;
      const CVec3 end = CalculateEnd( camera, rotation );
      const CVec3 direction = end - begin;
      const CVec3 dir = direction / fabs( direction );

      const CVec3 axis = V3_AXIS_Z * dir > 0.0001 ? V3_AXIS_Y : V3_AXIS_Z;
      const CVec3 delta = CQuat( float( PI / 16 ), axis ).Rotate( -direction / 4 );
      const float angle = float( PI / 2 );

      const CVec3 direction1 = CQuat( 0 * angle, dir ).Rotate( delta );
      const CVec3 direction2 = CQuat( 1 * angle, dir ).Rotate( delta );
      const CVec3 direction3 = CQuat( 2 * angle, dir ).Rotate( delta );
      const CVec3 direction4 = CQuat( 3 * angle, dir ).Rotate( delta );

      Render::DebugRenderer::DrawLine3D( begin, end, color, color, false );

      Render::DebugRenderer::DrawLine3D( end, end + direction1, color, color, false );
      Render::DebugRenderer::DrawLine3D( end, end + direction2, color, color, false );
      Render::DebugRenderer::DrawLine3D( end, end + direction3, color, color, false );
      Render::DebugRenderer::DrawLine3D( end, end + direction4, color, color, false );

      Render::DebugRenderer::DrawLine3D( end + direction1, end + direction2, color, color, false );
      Render::DebugRenderer::DrawLine3D( end + direction2, end + direction3, color, color, false );
      Render::DebugRenderer::DrawLine3D( end + direction3, end + direction4, color, color, false );
      Render::DebugRenderer::DrawLine3D( end + direction4, end + direction1, color, color, false );
    }
  }

  CVec3 CalculateEnd( const NScene::ICamera& camera, CQuat rotation )
  {
    const CVec3 begin = placement->pos;
    const CVec3 dir = rotation.Rotate( V3_AXIS_X );
    const CVec3 direction = dir * CalculateScale( camera ) / 1.5;
    return begin + direction;
  }
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
