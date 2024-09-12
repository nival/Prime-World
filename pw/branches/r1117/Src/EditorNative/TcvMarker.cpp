#include "stdafx.h"
#include "Utility.h"
#include "Settings.h"
#include "TcvMarker.h"
#include "EditorScene.h"

static const float RECT_SIZE = 2.5f * 0.15f;
static const float MIN_DISTANCE = 70;
static const float MAX_DISTANCE = 3 * MIN_DISTANCE;

typedef Terrain::TerrainGeometryManager TerrainGeometryManager;

using namespace System;

using namespace EditorNative;
using namespace EditorNative::Terrain;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TcvMarker::TcvMarker( int _row, int _column )
: widthInPixels( 0 )
, heightInPixels( 0 )
,	color ( System::Drawing::Color::White )
,	row( _row )
,	column( _column )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnPositionChanged()
{
	SceneElement::OnPositionChanged();

	if ( !ReferenceEquals( Scene, nullptr ) )
	{
		Matrix43 transform;

		// TODO: модифицировать функцию декомпозиции, для корректной работы с масштабом.
    ComposeMatrix( transform, Location->Native, Rotation->Native, /*Quaternion::Identity->Native,*/ Vector3::Ones->Native );

		Scene->NativeScene->GetTerrain()->SetTCV( column, row, transform );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnTCVChanged()
{
	Matrix43 matrix = Scene->NativeScene->GetTerrain()->GetTCV( column, row );

	CVec3 translation;
	CQuat rotation;
	CVec3 scale;
	DecomposeMatrix( matrix, translation, rotation, scale );

	Location = gcnew Vector3( translation );
	Rotation = gcnew Quaternion( rotation );

	// TODO: модифицировать функцию декомпозиции, для корректной работы с масштабом.
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnManipulatorChanged()
{
	for each ( TcvMarker^ marker in Scene->SceneTerrain->TcvMarkers )
	{
		if ( !ReferenceEquals( marker, this ) )
		{
			bool visible = IsSelected || Scene->CurrentManipulator == ManipulatorTypes::None;
			marker->IsSelectable = visible;
			marker->IsVisible = visible;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::Update()
{
	if ( !ReferenceEquals( Scene, nullptr ) )
	{
		Camera^ camera = Scene->SceneCamera;
		const CVec3 location = Location->Native;

		float distance = fabs( camera->Location->Native - location );
		const CVec3 direction = ( camera->Location->Native - location ) / distance;

		distance = distance < MIN_DISTANCE ? MIN_DISTANCE : distance;
		const CVec3 fakeLocation = camera->Location->Native + direction * distance;

		NScene::ICamera& nativeCamera = *Scene->NativeScene->GetCamera();
		const CVec3 upVector = camera->UpDirection->Native * RECT_SIZE;

		const CVec2 up = PerformProjection( nativeCamera, fakeLocation + upVector );
		const CVec2 down = PerformProjection( nativeCamera, fakeLocation - upVector );

		const float size = fabs( up.y - down.y );
		WidthInPixels = size;
		HeightInPixels = size;

		if ( !IsSelected )
		{
			const float A = 128 / ( 2 * ( MIN_DISTANCE - MAX_DISTANCE ) );
			const float B = 255 - 128 * A;

			const float colorIndex = A * distance + B;

			const Byte byteColorIndex =
				colorIndex < 128 ? 128 :
				colorIndex > 255 ? 255 :
				(Byte)colorIndex;

			Color = System::Drawing::Color::FromArgb( byteColorIndex, byteColorIndex, byteColorIndex );
		}
		else
		{
			Color = System::Drawing::Color::Red;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnSelectionChanged()
{
	Update();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnBeforeOwnerChanged()
{
	// Do nothing.
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::OnOwnerChanged()
{
	if ( !ReferenceEquals( Scene, nullptr ) )
	{
		OnTCVChanged();
		Update();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::Draw( const CVec2& projectedLocation )
{
  if ( IsVisible )
  {
    CVec2 vertices[] =
    {
      projectedLocation + CVec2( -WidthInPixels / 2, -HeightInPixels / 2 ),
      projectedLocation + CVec2(  WidthInPixels / 2, -HeightInPixels / 2 ),
      projectedLocation + CVec2(  WidthInPixels / 2,  HeightInPixels / 2 ),
      projectedLocation + CVec2( -WidthInPixels / 2,  HeightInPixels / 2 ),
    };
    EditorNative::DrawLine2D( vertices[0], vertices[1], color );
    EditorNative::DrawLine2D( vertices[1], vertices[2], color );
    EditorNative::DrawLine2D( vertices[2], vertices[3], color );
    EditorNative::DrawLine2D( vertices[3], vertices[0], color );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TcvMarker::TryPick( NScene::ICamera& camera, const CVec2& cursorPosition, CVec3& pickCoordinate )
{
  const float hotSpotSize = CURSOR_HOT_SPOT_SIZE;

  const CVec2 location = PerformProjection( camera, Location->Native );

  const float up = location.y - heightInPixels / 2;
  const float cursorUp = cursorPosition.y - hotSpotSize / 2;

  const float down = location.y + heightInPixels / 2;
  const float cursorDown = cursorPosition.y + hotSpotSize / 2;

  const float right = location.x + widthInPixels / 2;
  const float cursorRight = cursorPosition.x + hotSpotSize / 2;

  const float left = location.x - widthInPixels / 2;
  const float cursorLeft = cursorPosition.x - hotSpotSize / 2;

  if ( IntervalsIntersected( up, down, cursorUp, cursorDown ) && IntervalsIntersected( left, right, cursorLeft, cursorRight ) )
  {
    pickCoordinate = Location->Native;
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TcvMarker::Draw()
{
  if ( IsVisible )
  {
    Draw( PerformProjection( Scene->NativeCamera, Location->Native ) );
  }
}