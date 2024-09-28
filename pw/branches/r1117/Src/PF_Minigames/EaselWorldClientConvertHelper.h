#pragma once

//#include "../System/Spline.h"

namespace PF_Minigames
{

class Easel;
class Minigames;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper for all client<->world conversions. Use this class for all time and space transformation. And let the force be with you :)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselWorldClientConvertHelper : public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC2, EaselWorldClientConvertHelper );
public:

	EaselWorldClientConvertHelper();

	void Init(const CPtr<Easel>& _easel, const CVec3& _position);

  // new position and scale setters
  void SetPlacement(const Placement& _placement);

  // returns client coordinates for SVector(0, 0) world coordinates
  const CVec3& GetWorldZeroCoordinates() const { return zeroCoordinates; }

  const Placement& GetMinigamePlacement() { return minigamePlacement; }

  // calculate client coordinates by world
	CVec3 ConvertWorldToClientCoordinates( const SVector& worldCoords, int z = 0 ) const;

  int ConvertClientToWorldLength( float clientLength ) const;

  SVector ConvertClientToWorldCoordinates( const CVec3& clientCoords ) const;

  SVector ConvertScreenToWorldCoordinates( const CVec2& screenCoords) const;

private:

  CPtr<Easel> easel;

  Placement minigamePlacement;
  Matrix43 transform;
  Matrix43 transformInversed;
  Matrix43 minigameTransform;

  CVec3 zeroCoordinates;
};

} // PF_Minigames
