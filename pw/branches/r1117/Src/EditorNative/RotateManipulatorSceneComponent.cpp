#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "RotateManipulatorSceneComponent.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

bool RotateManipulatorSceneComponent::CanBeSelected( NScene::ICamera& camera, Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CQuat& rotation, bool isCameraPlane )
{
  CVec2 cursorPosition = scene->ConvertCursorPosition( cursorPositionManaged );
  nstl::vector<CVec3> points( CalculateCirclePoints( camera, 1, rotation, isCameraPlane ) );
  for ( int i = 0; i < points.size(); ++i )
  {
    if ( IsInRect( PerformProjection( camera, points[i] ), cursorPosition, CURSOR_HOT_SPOT_SIZE ) )
    {
      return true;
    }
  }
  return false;
}

void RotateManipulatorSceneComponent::CalculateNewRotation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene )
{
  if ( selectedRotation == -1 ) return;

  CVec2 nativeDelta( delta->X, delta->Y );
  nativeDelta.x *= scene->GetCursorScale().x;
  nativeDelta.y *= scene->GetCursorScale().y;

  CVec2 cursorPosition = scene->ConvertCursorPosition( initialCursorPosition );
  NScene::ICamera& camera = *scene->NativeScene->GetCamera();

  if ( fabs( nativeDelta ) == 0 ) return;

  nstl::vector<CVec3> points( CalculateCirclePoints( camera, 1, (*rotations)[selectedRotation].rotation, (*rotations)[selectedRotation].isCameraPlane ) );
  int i = FindNearestPointIndex( points, cursorPosition, camera, (*rotations)[selectedRotation].rotation, (*rotations)[selectedRotation].isCameraPlane );

  if ( i < 0 )
  {
    return;
  }

  const CVec3 begin = points[i];
  const CVec3 end = points[(i + 1) % points.size()];

  Render::DebugRenderer::DrawPoint3D( points[i], 0.01f * CalculateScale( camera ), Render::Color( 255, 255, 255 ), true );

  const CVec3 normal = CalculateRotation( camera, (*rotations)[selectedRotation].rotation, (*rotations)[selectedRotation].isCameraPlane ).Rotate( V3_AXIS_Z );

  const CVec3 beginRealDelta = GetRayIntersection( camera, cursorPosition, placement->pos, normal );
  const CVec3 endRealDelta = GetRayIntersection( camera, cursorPosition + nativeDelta, placement->pos, normal );

  const float projection = ( end - begin ) * ( endRealDelta - beginRealDelta ) / fabs( end - begin );
  const CVec3 realDelta = ( end - begin ) * ( projection / fabs( end - begin ) );

  const float radius = fabs( placement->pos - beginRealDelta );

  if ( fabs( projection ) > 0.00001 && radius > 0.00001 )
  {
    if ( controlItem != nullptr )
    {
      Placement curpos = controlItem->GetPlacement();
      *placement = curpos;
      placement->rot = CQuat( projection / fabs( projection ) * fabs( realDelta ) / radius, normal, true ) * placement->rot;
      controlItem->SetPlacement( *placement );
    }
  }
}

void RotateManipulatorSceneComponent::Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene )
{
  NScene::ICamera& camera = *scene->NativeScene->GetCamera();

  for ( int i = 0; i < rotations->size(); i++ )
  {
    if ( CanBeSelected( camera, cursorPositionManaged, scene, (*rotations)[i].rotation, (*rotations)[i].isCameraPlane ) )
    {
      selectedRotation = i;
      return;
    }
  }
  selectedRotation = -1;
}

void RotateManipulatorSceneComponent::Draw( NScene::IScene& scene )
{
  Render::Color yellowColor( 255, 255, 0 );

  for ( int i = 0; i < rotations->size(); i++ )
  {
    if ( i != selectedRotation )
    {
      DrawCircle( CalculateCirclePoints( *scene.GetCamera(), 10, (*rotations)[i].rotation, (*rotations)[i].isCameraPlane ), (*rotations)[i].color );
    }
    else
    {
      DrawCircle( CalculateCirclePoints( *scene.GetCamera(), 10, (*rotations)[i].rotation, (*rotations)[i].isCameraPlane ), yellowColor );
    }
  }
}

nstl::vector<CVec3> RotateManipulatorSceneComponent::CalculateCirclePoints( const NScene::ICamera& camera, int deltaDegree, const CQuat& rotationType, bool isCameraPlane )
{
  const CVec3 location = placement->pos;
  const CQuat rotation = CalculateRotation( camera, rotationType, isCameraPlane );
  const CVec3 base = rotation.Rotate( V3_AXIS_X ) * ( CalculateScale( camera ) * ( isCameraPlane ? RADIUS*1.5f : RADIUS ) );
  const CVec3 normal = rotation.Rotate( V3_AXIS_Z );

  nstl::vector<CVec3> points;
  for ( int degree = 0; degree < 360; degree += deltaDegree )
  {
    points.push_back( location + CQuat( ToRadian( degree ), normal, true ).Rotate( base ) );
  }
  return points;
}

CQuat RotateManipulatorSceneComponent::CalculateRotation( const NScene::ICamera& camera, const CQuat& rotation, bool isCameraPlane )
{
  if ( isCameraPlane )
  {
    NScene::SCameraPosition position;
    camera.GetPosition( &position );
    return ShortestArc( V3_AXIS_Z, position.GetCameraDir() );
  }
  else
    return placement->rot * rotation;
}

int RotateManipulatorSceneComponent::FindNearestPointIndex( const nstl::vector<CVec3>& points, const CVec2& cursorPosition, NScene::ICamera& camera, const CQuat& rotationType, bool isCameraPlane )
{
  const CVec3 location = placement->pos;
  const CVec3 intersection = GetRayIntersection( camera, cursorPosition, location, CalculateRotation( camera, rotationType, isCameraPlane ).Rotate( V3_AXIS_Z ) );
  const CVec3 delta =  intersection - location;
  const float length = fabs( delta );

  if ( length > 0.0001 )
  {
    const CVec3 point = location + delta / length * ( CalculateScale( camera ) * isCameraPlane ? RADIUS*1.5f : RADIUS );
    float minDistIndex = 0;
    float minDist = Single::MaxValue;
    for ( int i = 0; i < points.size(); ++i )
    {
      const float dist = fabs( PerformProjection( camera, points[i] ) - cursorPosition );
      if ( dist < minDist )
      {
        minDist = dist;
        minDistIndex = i;
      }
    }
    return minDistIndex;
  }
  else
  {
    return -1;
  }
}
