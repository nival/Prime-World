#pragma once

#include "../System/Placement.h"
#include "EditorSceneComponent.h"
#include "ISceneElement.h"
#include "Utility.h"
#include "SimpleEditorScene.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

struct ScaleData
{
  bool isMulti;
  CVec3 offsetDirection;
  Render::Color color;

  ScaleData( const CVec3& _offset, const Render::Color& _color, bool _isMulti ) 
  : offsetDirection( _offset ), color( _color ), isMulti( _isMulti ) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class ScaleManipulatorSceneComponent sealed : ISceneElement
{
  static const float MARKER_SIZE = 0.1f;
  static const float INITIAL_ROD = 10.0f;

  CVec3* initialScale;
  Placement* placement;
  ISceneElement^ controlItem;

  int selectedOffset;
  nstl::vector<ScaleData>* offsets;

public:

  ScaleManipulatorSceneComponent( ISceneElement^ _controlItem )
    : controlItem ( _controlItem ) 
  {
    selectedOffset = 0;
    offsets = new nstl::vector<ScaleData>();
    offsets->push_back( ScaleData( CVec3( 0.0f, 0.0f, 0.0f ), Render::Color( 128, 255, 255 ), true ) );
    offsets->push_back( ScaleData( CVec3( 1.0f, 0.0f, 0.0f ), Render::Color( 255, 0, 0 ), false ) );
    offsets->push_back( ScaleData( CVec3( 0.0f, 1.0f, 0.0f ), Render::Color( 0, 255, 0 ), false ) );
    offsets->push_back( ScaleData( CVec3( 0.0f, 0.0f, 1.0f ), Render::Color( 0, 0, 255 ), false ) );

    if ( controlItem != nullptr )
    {
      initialScale = new CVec3(controlItem->GetPlacement().scale);
    }
    else
    {
      initialScale = new CVec3( 1.0f, 1.0f, 1.0f );
    }

    placement = new Placement(VNULL3, QNULL, CVec3(1.0f,1.0f,1.0f) );
    if ( controlItem != nullptr )
    {
      Placement curpos = controlItem->GetPlacement();
      *placement = curpos;
      //controlItem->SetPlacement( *placement );
    }
  }

  void Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene );
  void CalculateNewScale( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene );
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

  bool CanBeSelected( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CVec3& offsetDirection );

  float CalculateScale( const NScene::ICamera& camera )
  {
    NScene::SCameraPosition cameraPosition;
    camera.GetPosition( &cameraPosition );
    CVec3 cameraLocation = cameraPosition.vAnchor - cameraPosition.GetCameraDir() * cameraPosition.fRod;
    return fabs( placement->pos - cameraLocation ) / INITIAL_ROD;
  }

  void DrawScale( const NScene::ICamera& camera, const CVec3& offsetDirection, const Render::Color& color )
  {
    const CVec3 markerPosition = CalculateMarkerPosition( camera, offsetDirection );
    const float s = MARKER_SIZE / 2;

    Render::Color darkGray( 50, 50, 50 );

    const CVec3 vertices[] =
    {
      markerPosition + placement->rot.Rotate( CVec3( -s, -s,  s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3( -s,  s,  s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3(  s,  s,  s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3(  s, -s,  s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3( -s, -s, -s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3( -s,  s, -s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3(  s,  s, -s ) ) * CalculateScale( camera ),
      markerPosition + placement->rot.Rotate( CVec3(  s, -s, -s ) ) * CalculateScale( camera )
    };

    Render::DebugRenderer::DrawLine3D( vertices[0], vertices[1], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[1], vertices[2], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[2], vertices[3], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[3], vertices[0], color, color, false );

    Render::DebugRenderer::DrawLine3D( vertices[0 + 4], vertices[1 + 4], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[1 + 4], vertices[2 + 4], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[2 + 4], vertices[3 + 4], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[3 + 4], vertices[0 + 4], color, color, false );

    Render::DebugRenderer::DrawLine3D( vertices[0], vertices[4], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[1], vertices[5], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[2], vertices[6], color, color, false );
    Render::DebugRenderer::DrawLine3D( vertices[3], vertices[7], color, color, false );
    
    Render::DebugRenderer::DrawLine3D( placement->pos, markerPosition, darkGray, darkGray, false );
  }

  CVec3 CalculateMarkerPosition( const NScene::ICamera& camera, const CVec3& offsetDirection )
  {
    return placement->pos + placement->rot.Rotate( ComponentInvProduct( ComponentProduct( offsetDirection, placement->scale ), ComponentFabs( *initialScale ) ) ) * CalculateScale( camera );
  }
};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
