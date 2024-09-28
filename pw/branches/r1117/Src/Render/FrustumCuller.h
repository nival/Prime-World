#pragma once

#include "batch.h"
#include "BoundingPrimitives.h"

namespace Render
{

class FrustumCuller
{
  SHMatrix viewProjection;
  BoundingBox  worldAABB;

  bool accumulateBB;

  void AccumulateAABB(const RenderComponent& _item);
  bool SkipItem(Batch *_pBatch);

public:
  FrustumCuller(SHMatrix _viewProjection) : viewProjection(_viewProjection) {}

  void ResetWorldAABB()                   { worldAABB.Invalidate(); }
  const BoundingBox& GetWorldAABB() const { return worldAABB; }

  // Cull out items not in frustum. Accumulate world AABB for items with priorities in _prioritiesToAccumulate
  // _prioritiesToAccumulate should be sorted in ascending order. This function DOESN'T ResetWorldAABB before accumulation!
  void Clip( BatchQueue* _pQueue, const vector<int>& _prioritiesToAccumulate = vector<int>() );
};

} // Render