#pragma once

#include "StringUtils.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline NDb::Ptr<T> GetObject( libdb::DB::DBID^ dbId )
{
	if ( ( (System::Object^)dbId) != nullptr )
	{
		return NDb::Get<T>( NDb::DBID( ToMBCS( dbId->Name ) ) );
	}
	else
	{
		return nullptr;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool FileExists( System::String^ fileName )
{
	SFileInfo info;
	return RootFileSystem::GetFileInfo( &info, ToMBCS( fileName ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 GetRayIntersection( NScene::ICamera& camera, const CVec2& point, const CVec3& center, const CVec3& normal )
{
	CVec3 A;
	CVec3 B;
	camera.GetProjectiveRayPoints( &A, &B, point );

	const CVec3& P = center;
	const CVec3& n = normal;
	return A + ( ( P - A ) * n ) / ( ( B - A ) * n ) * ( B - A );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 GetCameraDir( const NScene::ICamera& camera )
{
	NScene::SCameraPosition position;
	camera.GetPosition( &position );
	return position.GetCameraDir();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec2 PerformProjection( NScene::ICamera& camera, const CVec3& point )
{
	const SHMatrix& projectiveMatrix = camera.GetProjectiveMatrix();
	const SHMatrix& viewMatrix = camera.GetViewMatrix();

	CVec4 transformedLocation;
	viewMatrix.RotateHVector( &transformedLocation, point );
	projectiveMatrix.RotateHVector( &transformedLocation, transformedLocation );

	const CVec2 transformedLocation2D = ( CVec2( transformedLocation.x, transformedLocation.y ) / transformedLocation.w + CVec2( 1, 1 ) ) / 2;

	const float width = camera.GetScreenWidth();
	const float height = camera.GetScreenHeight();

	return CVec2( transformedLocation2D.x * width, height - transformedLocation2D.y * height );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IntervalsIntersected( float x0, float x1, float y0, float y1 )
{
	if ( x0 < y0)
	{
		return y0 <= x1;
	}
	else
	{
		return x0 <= y1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 ComponentProduct( const CVec3& v1, const CVec3& v2 )
{
	return CVec3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 ComponentInvProduct( const CVec3& v1, const CVec3& v2 )
{
	return CVec3( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline CVec3 ComponentFabs( const CVec3& v )
{
	return CVec3( fabs( v.x ), fabs( v.y ), fabs( v.z ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool IsInRect( const CVec2& point, const CVec2& rectCenter, float rectSize )
{
	const float up = rectCenter.y - rectSize / 2;
	const float down = rectCenter.y + rectSize / 2;
	const float right = rectCenter.x + rectSize / 2;
	const float left = rectCenter.x - rectSize / 2;
	return point.x >= left && point.x <= right && point.y >= up && point.y <= down;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float RoundToBounds( float value, float minValue, float maxValue )
{
	if ( value > maxValue )
	{
		return maxValue;
	}
	else if ( value < minValue )
	{
		return minValue;
	}
	else
	{
		return value;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawLine3D( const CVec3& p1, const CVec3& p2, System::Drawing::Color _color )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
	Render::DebugRenderer::DrawLine3D( p1, p2, color, color, false );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawLine3D( const CVec3& p1, const CVec3& p2, System::Drawing::Color _color, bool useZTest )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
	Render::DebugRenderer::DrawLine3D( p1, p2, color, color, useZTest );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawLine2D( const CVec2& p1, const CVec2& p2, System::Drawing::Color _color )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
	Render::DebugRenderer::DrawLine2D( p1.x, p1.y, p2.x, p2.y, color, color );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawPoint3D( const CVec3& point, float size, System::Drawing::Color _color )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
	Render::DebugRenderer::DrawPoint3D( point, size, color, false );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawCircle3D( const CVec3& point, float size, int numSegments, System::Drawing::Color _color )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
  Render::DebugRenderer::DrawCircle3D( point, size, numSegments, color, false );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DrawPoint2D( const CVec2& point, float size, System::Drawing::Color _color )
{
	const Render::Color color( _color.R, _color.G, _color.B, _color.A );
	Render::DebugRenderer::DrawPoint2D( point.x, point.y, size, color );
}

inline Placement ConvertFromWorldToOffset( const Placement& offset, const Placement& worldPlacement )
{
  Placement localPlacement;
  localPlacement = -offset + worldPlacement;
  return localPlacement;
}

inline Placement ConvertFromOffsetToWorld( const Placement& offset, const Placement& offsetPlacement )
{
  Placement worldPlacement;
  worldPlacement = offset + offsetPlacement;
  return worldPlacement;
}

inline void convertPlacement(DBTypes::Placement2^ from, Placement* to)
{
  to->pos.x = from->translateX;
  to->pos.y = from->translateY;
  to->pos.z = from->translateZ;

  CQuat rotation;
  rotation.FromEulerAngles( ToRadian(from->rotationZ), ToRadian(from->rotationY), ToRadian(from->rotationX) );

  to->rot.x = rotation.x;
  to->rot.y = rotation.y;
  to->rot.z = rotation.z;
  to->rot.w = rotation.w;

  to->scale.x = from->scaleX;
  to->scale.y = from->scaleY;
  to->scale.z = from->scaleZ;
}

inline void convertPlacement( const Placement* from, DBTypes::Placement2^ to)
{
  to->translateX = from->pos.x;
  to->translateY = from->pos.y;
  to->translateZ = from->pos.z;

  CVec3 rotation;
  from->rot.DecompEulerAngles( &rotation.z, &rotation.y, &rotation.x );
  to->rotationX = ToDegree(rotation.x);
  to->rotationY = ToDegree(rotation.y);
  to->rotationZ = ToDegree(rotation.z);

  to->scaleX = from->scale.x;
  to->scaleY = from->scale.y;
  to->scaleZ = from->scale.z;
}

inline void convertPlacement(DBTypes::Placement^ from, Placement* to)
{
  to->pos.x = from->location->x;
  to->pos.y = from->location->y;
  to->pos.z = from->location->z;

  to->rot.x = from->rotation->x;
  to->rot.y = from->rotation->y;
  to->rot.z = from->rotation->z;
  to->rot.w = from->rotation->w;

  to->scale.x = from->scale->x;
  to->scale.y = from->scale->y;
  to->scale.z = from->scale->z;
}

inline void convertPlacement(const Placement* from, DBTypes::Placement^ to)
{
  to->location->x = from->pos.x;
  to->location->y = from->pos.y;
  to->location->z = from->pos.z;

  to->rotation->x = from->rot.x;
  to->rotation->y = from->rot.y;
  to->rotation->z = from->rot.z;
  to->rotation->w = from->rot.w;

  to->scale->x = from->scale.x;
  to->scale->y = from->scale.y;
  to->scale->z = from->scale.z;
}

}	// namespace EditorNative
