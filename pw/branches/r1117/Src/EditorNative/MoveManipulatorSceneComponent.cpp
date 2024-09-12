#include "stdafx.h"
#include "EditorScene.h"
#include "Utility.h"
#include "MoveManipulatorSceneComponent.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;


static bool HasCrossing(
                        const CVec2& p11, const CVec2& p12,   // координаты первого отрезка
                        const CVec2& p21, const CVec2& p22		// координаты второго отрезка
                        )
{
  // знаменатель
  double Z  = (p12.y-p11.y)*(p21.x-p22.x)-(p21.y-p22.y)*(p12.x-p11.x);
  // числитель 1
  double Ca = (p12.y-p11.y)*(p21.x-p11.x)-(p21.y-p11.y)*(p12.x-p11.x);
  // числитель 2
  double Cb = (p21.y-p11.y)*(p21.x-p22.x)-(p21.y-p22.y)*(p21.x-p11.x);

  // если числители и знаменатель = 0, прямые совпадают
  if( (Z == 0)&&(Ca == 0)&&(Cb == 0) )
  {
    return true;
  }

  // если знаменатель = 0, прямые параллельны
  if( Z == 0 )
  {
    return false;
  }

  double Ua = Ca/Z;
  double Ub = Cb/Z;

  // если 0<=Ua<=1 и 0<=Ub<=1, точка пересечения в пределах отрезков
  if( (0 <= Ua)&&(Ua <= 1)&&(0 <= Ub)&&(Ub <= 1) )
  {
    return true;
  }
  // иначе точка пересечения за пределами отрезков
  else
  {
    return false;
  }
}


bool MoveManipulatorSceneComponent::CanBeSelected( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene, const CQuat& tryAxis, bool isFreeMoving )
{
  CVec2 cursorPosition = scene->ConvertCursorPosition( cursorPositionManaged );
  NScene::ICamera& camera = *scene->NativeScene->GetCamera();

  if ( isFreeMoving )
  {
    const float size = SIZE;
    const float hotSpotSize = CURSOR_HOT_SPOT_SIZE;

    const CVec2 location = PerformProjection( camera, placement->pos );

    const float up = location.y - size / 2;
    const float cursorUp = cursorPosition.y - hotSpotSize / 2;

    const float down = location.y + size / 2;
    const float cursorDown = cursorPosition.y + hotSpotSize / 2;

    const float right = location.x + size / 2;
    const float cursorRight = cursorPosition.x + hotSpotSize / 2;

    const float left = location.x - size / 2;
    const float cursorLeft = cursorPosition.x - hotSpotSize / 2;

    return IntervalsIntersected( up, down, cursorUp, cursorDown ) && IntervalsIntersected( left, right, cursorLeft, cursorRight );
  }

  const float hotSpotSize = CURSOR_HOT_SPOT_SIZE;

  const CVec3 begin = placement->pos;
  const CVec3 end = CalculateEnd( camera, tryAxis );

  const CVec2 projectedBegin = PerformProjection( camera, begin );
  const CVec2 projectedEnd = PerformProjection( camera, end );

  const CVec2 upLeft = cursorPosition + CVec2( -hotSpotSize / 2, -hotSpotSize / 2 );
  const CVec2 upRight = upLeft + CVec2( hotSpotSize, 0 );
  const CVec2 downRight = upRight + CVec2( 0, hotSpotSize );
  const CVec2 downLeft = upLeft + CVec2( 0, hotSpotSize );

  return
    HasCrossing( projectedBegin, projectedEnd, upLeft, upRight ) ||
    HasCrossing( projectedBegin, projectedEnd, upRight, downRight ) ||
    HasCrossing( projectedBegin, projectedEnd, downRight, downLeft ) ||
    HasCrossing( projectedBegin, projectedEnd, downLeft, upLeft );
}

void MoveManipulatorSceneComponent::CalculateNewLocation( Vector2^ initialCursorPosition, Vector2^ delta, SimpleEditorScene^ scene )
{
  if ( selectedAxis == -1 ) return;

  CVec2 nativeDelta( delta->X, delta->Y );
  nativeDelta.x *= scene->GetCursorScale().x;
  nativeDelta.y *= scene->GetCursorScale().y;

  if ( fabs( nativeDelta ) > 0 )
  {
    NScene::ICamera& camera = *scene->NativeScene->GetCamera();

    if ( (*axis)[selectedAxis].isFreeMoving )
    {
      CVec3 dummy;
      CVec2 cursorPosition = scene->ConvertCursorPosition( initialCursorPosition );
      CVec3 initialRayFar;
      camera.GetProjectiveRayPoints( &dummy, &initialRayFar, cursorPosition );

      CVec3 currentRayFar;
      camera.GetProjectiveRayPoints( &dummy, &currentRayFar, cursorPosition + nativeDelta );

      CVec3 cameraLocation;
      camera.GetProjectiveRay( &cameraLocation, &dummy, cursorPosition );

      const CVec3 direction = currentRayFar - initialRayFar;
      const float coef = fabs( placement->pos - cameraLocation ) / fabs( initialRayFar - cameraLocation );

      if ( controlItem != nullptr )
      {
        Placement curpos = controlItem->GetPlacement();
        *placement = curpos;
        placement->pos += direction * coef;
        controlItem->SetPlacement( *placement );
      }
    }
    else
    {
      const CVec3 begin = placement->pos;
      const CVec3 end = CalculateEnd( camera, (*axis)[selectedAxis].axis );

      const CVec2 projectedBegin = PerformProjection( camera, begin );
      const CVec2 projectedEnd = PerformProjection( camera, end );

      const CVec2 projectedDir = projectedEnd - projectedBegin;
      const float projection = projectedDir * nativeDelta / fabs( projectedDir );

      const CVec3 dir = end - begin;
      const float coef = projection / fabs( projectedDir );

      if ( controlItem != nullptr )
      {
        Placement curpos = controlItem->GetPlacement();
        *placement = curpos;
        placement->pos += ( end - begin ) * coef;
        controlItem->SetPlacement( *placement );
      }
    }
  }
}

void MoveManipulatorSceneComponent::Select( Vector2^ cursorPositionManaged, SimpleEditorScene^ scene )
{
  for ( int i = 0; i < axis->size(); i++ )
  {
    if ( CanBeSelected( cursorPositionManaged, scene, (*axis)[i].axis, (*axis)[i].isFreeMoving ) )
    {
      selectedAxis = i;
      return;
    }
  }
  selectedAxis = -1;
}

void MoveManipulatorSceneComponent::Draw( NScene::IScene& scene )
{
  Render::Color yellowColor( 255, 255, 0 );

  for ( int i = 0; i < axis->size(); i++ )
  {
    if ( i != selectedAxis )
    {
      DrawArrow( *scene.GetCamera(), (*axis)[i].axis, (*axis)[i].color, (*axis)[i].isFreeMoving );
    }
    else
    {
      DrawArrow( *scene.GetCamera(), (*axis)[i].axis, yellowColor, (*axis)[i].isFreeMoving );
    }
  }
}
