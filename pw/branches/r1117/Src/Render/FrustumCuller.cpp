#include "StdAfx.h"
#include "FrustumCuller.h"
#include "../System/InlineProfiler.h"

//#define USE_D3DX

#ifdef USE_D3DX
#include <d3dx9math.h>
#endif

namespace Render
{

static NDebug::DebugVar<int> s_culledPrimsIn("culledPrimsIn", "PerfCnt", true);

static NDebug::DebugVar<int> s_culledPrimitives("culledPrims", "PerfCnt", true);

static bool s_enableCulling = true;
REGISTER_DEV_VAR("frustumNew", s_enableCulling, STORAGE_NONE);

static void Multiply(SHMatrix *_result, const SHMatrix &_viewProjection, const Matrix43 &_world )
{
  static SHMatrix res;
  const bool overlappedArgs = abs( (char*)_result - (char*)&_viewProjection ) > sizeof(SHMatrix);
  SHMatrix* const __restrict pRes = overlappedArgs ? &res : _result;

  pRes->_11 = _viewProjection._11 * _world._11 + _viewProjection._12 * _world._21 + _viewProjection._13 * _world._31;
  pRes->_12 = _viewProjection._11 * _world._12 + _viewProjection._12 * _world._22 + _viewProjection._13 * _world._32;
  pRes->_13 = _viewProjection._11 * _world._13 + _viewProjection._12 * _world._23 + _viewProjection._13 * _world._33;
  pRes->_14 = _viewProjection._11 * _world._14 + _viewProjection._12 * _world._24 + _viewProjection._13 * _world._34 + _viewProjection._14;

  pRes->_21 = _viewProjection._21 * _world._11 + _viewProjection._22 * _world._21 + _viewProjection._23 * _world._31;
  pRes->_22 = _viewProjection._21 * _world._12 + _viewProjection._22 * _world._22 + _viewProjection._23 * _world._32;
  pRes->_23 = _viewProjection._21 * _world._13 + _viewProjection._22 * _world._23 + _viewProjection._23 * _world._33;
  pRes->_24 = _viewProjection._21 * _world._14 + _viewProjection._22 * _world._24 + _viewProjection._23 * _world._34 + _viewProjection._24;

  pRes->_31 = _viewProjection._31 * _world._11 + _viewProjection._32 * _world._21 + _viewProjection._33 * _world._31;
  pRes->_32 = _viewProjection._31 * _world._12 + _viewProjection._32 * _world._22 + _viewProjection._33 * _world._32;
  pRes->_33 = _viewProjection._31 * _world._13 + _viewProjection._32 * _world._23 + _viewProjection._33 * _world._33;
  pRes->_34 = _viewProjection._31 * _world._14 + _viewProjection._32 * _world._24 + _viewProjection._33 * _world._34 + _viewProjection._34;

  pRes->_41 = _viewProjection._41 * _world._11 + _viewProjection._42 * _world._21 + _viewProjection._43 * _world._31;
  pRes->_42 = _viewProjection._41 * _world._12 + _viewProjection._42 * _world._22 + _viewProjection._43 * _world._32;
  pRes->_43 = _viewProjection._41 * _world._13 + _viewProjection._42 * _world._23 + _viewProjection._43 * _world._33;
  pRes->_44 = _viewProjection._41 * _world._14 + _viewProjection._42 * _world._24 + _viewProjection._43 * _world._34 + _viewProjection._44;

  if(overlappedArgs)
    memcpy( _result, pRes, sizeof(SHMatrix) );
}

inline void FrustumCuller::AccumulateAABB(const RenderComponent& _item) // return true for items to remove
{
  AABB itemWorldAABB;

  bool isLocal = false;
  const AABB *pItemAABB = &_item.GetAABB(&isLocal);
  if(isLocal) {
    itemWorldAABB.Transform(_item.GetWorldMatrix(), *pItemAABB);
    pItemAABB = &itemWorldAABB;
  }
  else
    if(AABB::Huge() == *pItemAABB)
      return;

  CVec3 bbPoints[2] = { pItemAABB->center - pItemAABB->halfSize, pItemAABB->center + pItemAABB->halfSize };
  worldAABB.Merge(AsD3D(bbPoints), 2);
}

inline bool FrustumCuller::SkipItem(Batch *_pBatch) // return true for items to remove
{
  SHMatrix wvp;
  
  bool isLocal = true;
  const RenderComponent& item = *(_pBatch->pOwner);
  const AABB &bb = item.GetAABB(&isLocal);

  if(isLocal) {
#ifdef USE_D3DX
    D3DXMATRIX mVWP;
#else
    Multiply( &wvp, viewProjection, item.GetWorldMatrix() );
#endif
  }

  CVec4 clipSpaceOBB[8];
  const SHMatrix &transform = isLocal ? wvp : viewProjection;
  RenderComponent::FillOBBH(bb, transform, clipSpaceOBB);

  char flags[8], inside = -1, outside = 0;
  for(int i = 0; i < 8; ++i)
  {
    const CVec4 &vertex = clipSpaceOBB[i];

    char flag = vertex.x <= vertex.w;
    flag |= char(vertex.x >= -vertex.w) << 1;
    flag |= char(vertex.y <=  vertex.w) << 2;
    flag |= char(vertex.y >= -vertex.w) << 3;
    flag |= char(vertex.z <=  vertex.w) << 4;
    flag |= char(vertex.z >= 0) << 5;

    flags[i] = flag;
    outside |= flag;
    inside  &= flag;
  }
  _pBatch->isInside = (inside == 0x3F);
  const bool skip = outside != 0x3F;
  if(accumulateBB && !skip)
    AccumulateAABB(item);

  return skip;
}

void FrustumCuller::Clip(BatchQueue* _pQueue, const vector<int>& _prioritiesToAccumulate)
{
  if(!s_enableCulling)
    return;

  NI_PROFILE_FUNCTION

  vector<int>::const_iterator it = _prioritiesToAccumulate.begin(), end = _prioritiesToAccumulate.end();
  int numClipped = 0, numInputs = 0;

  for(int priority = 0; priority < NDb::MATERIALPRIORITY_COUNT; ++priority)
  {
    while(it != end && *it < priority)
      ++it;
    accumulateBB = it != end && *it == priority;

    for(Batch **ppBatch = &(_pQueue->GetSubQueue(priority).pBatchList), *pBatch = *ppBatch;
        pBatch; pBatch = pBatch->pNextBatch)
    {
#ifdef DEBUG_MATERIAL
      if( const NDb::Material* pDBMaterial = pBatch->pMaterial->GetDBMaterial() )
        if(pDBMaterial->GetObjectTypeID() == NDb::DropMaterial::typeId)
        {
          int a = 1; a;
        }
#endif // DEBUG_MATERIAL
      ++numInputs;

      if( SkipItem(pBatch) ) {
        *ppBatch = pBatch->pNextBatch;
        ++numClipped;
      }
      else
        ppBatch = &pBatch->pNextBatch;
    }
  }

  s_culledPrimitives.AddValue(numClipped);
  s_culledPrimsIn.AddValue(numInputs);
}


} // Render
