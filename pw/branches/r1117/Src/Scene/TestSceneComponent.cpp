#include "stdafx.h"
#include "TestSceneComponent.h"

namespace NScene
{

TestSceneComponent::TestSceneComponent( const Placement& pos )
:	SceneComponent(0, 0, pos)
{
	offset.SetPlacement( offset.GetPlacement() + pos );

  localAABB.center = CVec3(0.0f, 0.0f, 0.0f);
  localAABB.halfSize = CVec3(1.0f, 1.0f, 1.0f);
}

void TestSceneComponent::UpdateComponent( UpdatePars& pars, const Placement& parentPos, float timeDiff )
{
  // Make result matrix
  Matrix43 resultmatrix;
  worldPlacement.GetMatrix( &resultmatrix );

  // Transform local AABB to global one
  worldAABB.Transform( resultmatrix, localAABB );
  NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );

  // Update object's AABB
  pars.objectAABB.Grow(worldAABB);
}

}
