#pragma once
namespace Render
{

inline void ConvertDirection(const NDb::Direction &dir, CVec3 &vec)
{
  CQuat quat( dir.Yaw / 180.0f * FP_PI, 0.f, dir.Pitch / 180.0f * FP_PI );
  CVec3 src( 0.f, 1.f, 0.f );
  quat.Rotate( &vec, src );
  Normalize(&vec);
}

} // namespace Render
