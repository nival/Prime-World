#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "ScaleManipulatorSceneComponent.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

bool ScaleManipulatorSceneComponent::CanBeSelected( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CVec3& offsetDirection )
{
  CVec2 cursorPosition = scene->ConvertCursorPosition( cursorPositionManaged );
  NScene::ICamera& camera = *scene->NativeScene->GetCamera();

  const CVec3 markerPosition = CalculateMarkerPosition( camera, offsetDirection );

  static const CVec3 normals[] =
  {
    V3_AXIS_X,
    V3_AXIS_Y,
    V3_AXIS_Z,
    -V3_AXIS_X,
    -V3_AXIS_Y,
    -V3_AXIS_Z
  };

  static const CVec3 rights[] =
  {
    -V3_AXIS_Y,
    V3_AXIS_X,
    V3_AXIS_X
  };

  static const CVec3 ups[] =
  {
    V3_AXIS_Z,
    V3_AXIS_Z,
    -V3_AXIS_Y
  };

  const float scale = CalculateScale( camera );
  const float halfSize = MARKER_SIZE / 2 * scale;
  for ( int i = 0; i < sizeof( normals ) / sizeof( CVec3 ); ++i )
  {
    const CVec3 normal = placement->rot.Rotate( normals[i] );
    const CVec3 center = markerPosition + normal * halfSize;
    const CVec3 intersection = GetRayIntersection( camera, cursorPosition, center, normal );
    const CVec3 right = placement->rot.Rotate( rights[i % ( sizeof(rights) / sizeof( CVec3 ) )] );
    const CVec3 up = placement->rot.Rotate( ups[i % ( sizeof(ups) / sizeof( CVec3 ) )] );

    const float projectionRight = right * ( intersection - center );
    const float projectionUp = up * ( intersection - center );

    if ( fabs( projectionRight ) <= halfSize && fabs( projectionUp ) <= halfSize )
    {
      return true;
    }
  }

  return false;
}

void ScaleManipulatorSceneComponent::CalculateNewScale( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene )
{
  if ( selectedOffset == -1 ) return;

  NScene::ICamera& camera = *scene->NativeScene->GetCamera();
  CVec2 nativeDelta( delta->X, delta->Y );
  nativeDelta.x *= scene->GetCursorScale().x;
  nativeDelta.y *= scene->GetCursorScale().y;

  if ( (*offsets)[selectedOffset].isMulti && fabs( nativeDelta.x ) > 0.0f )
  {
    CVec2 cursorPosition = scene->ConvertCursorPosition( initialCursorPosition );

    const CVec3 intersection1 = GetRayIntersection( camera, cursorPosition, placement->pos, GetCameraDir( camera ) );
    const CVec3 intersection2 = GetRayIntersection( camera, cursorPosition + CVec2( nativeDelta.x, 0), placement->pos, GetCameraDir( camera ) );
    const float d = fabs( intersection2 - intersection1 ) * nativeDelta.x / fabs( nativeDelta.x );

    if ( controlItem != nullptr )
    {
      Placement curpos = controlItem->GetPlacement();
      *placement = curpos;
      placement->scale += ComponentProduct( CVec3( d, d, d ), *initialScale );
      controlItem->SetPlacement( *placement );
    }
  }
  else
  {
    const CVec3 dir = CalculateMarkerPosition( camera, (*offsets)[selectedOffset].offsetDirection ) - placement->pos;
    const CVec3 direction = dir / fabs( dir );
    const CVec2 projectedDirection = PerformProjection( camera, placement->pos + direction ) - PerformProjection( camera, placement->pos );

    const float projectedDirectionLength = fabs( projectedDirection );
    if ( projectedDirectionLength > 0.00001 )
    {
      const float projection = projectedDirection * nativeDelta / projectedDirectionLength;
      const CVec3 realDelta = direction * ( projection / projectedDirectionLength ) / CalculateScale( camera );
      CQuat invertRotation = placement->rot;
      invertRotation.Inverse();

      if ( controlItem != nullptr )
      {
        Placement curpos = controlItem->GetPlacement();
        *placement = curpos;
        placement->scale += ComponentProduct( invertRotation.Rotate( realDelta ), ComponentFabs( *initialScale ) );
        controlItem->SetPlacement( *placement );
      }
    }
  }
}

void ScaleManipulatorSceneComponent::Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene )
{
  for ( int i = 0; i < offsets->size(); i++ )
  {
    if ( CanBeSelected( cursorPositionManaged, scene, (*offsets)[i].offsetDirection ) )
    {
      selectedOffset = i;
      return;
    }
  }
  selectedOffset = -1;
}

void ScaleManipulatorSceneComponent::Draw( NScene::IScene& scene )
{
  Render::Color yellowColor( 255, 255, 0 );

  for ( int i = 0; i < offsets->size(); i++ )
  {
    if ( i != selectedOffset )
    {
      DrawScale( *scene.GetCamera(), (*offsets)[i].offsetDirection, (*offsets)[i].color );
    }
    else
    {
      DrawScale( *scene.GetCamera(), (*offsets)[i].offsetDirection, yellowColor );
    }
  }
}
