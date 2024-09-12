#include "StdAfx.h"
#include <Render/MeshResource.h>
#include <Render/primitive.h>
#include <Render/MaterialSpec.h>
#include "RoadGeometryVertex.h"
#include "RoadPrimitive.h"
#include "TerrainTextureCache.h"
#include "TEGetter.h"

typedef RoadGeometryVertex Vertex;

using namespace Render;

namespace Terrain
{

static TEGetter *pGetter = 0;


PatchMapping::PatchMapping(const Render::MeshGeometry *_pGeometry)
{
  using namespace Render;

  if(_pGeometry) {
    ASSERT(_pGeometry->primitives.size() == 1);
    vector<uint> patchIDs;

    const Primitive& prim = *_pGeometry->primitives[0];
    DXVertexBufferRef pVB = prim.GetVertexBuffer();
    NI_VERIFY(Get(pVB), "NULL vertex buffer", return);
    DXIndexBufferRef pIB = prim.GetIndexBuffer();
    NI_VERIFY(Get(pIB), "NULL vertex buffer", return);

    D3DVERTEXBUFFER_DESC vbDesc;
    pVB->GetDesc(&vbDesc);
#ifdef _DEBUG
    const uint numVertices = vbDesc.Size / sizeof(Vertex);
#endif // _DEBUG

    if( Index* pInd = LockIB(Get(pIB), D3DLOCK_NOSYSLOCK) )
    {
      const DipDescriptor& desc = prim.GetDipDescriptor();
      uint step = UINT_MAX;
      switch(desc.primitiveType) {
      case RENDERPRIMITIVE_TRIANGLELIST:
        step = 3; break;
      case RENDERPRIMITIVE_TRIANGLESTRIP:
        step = 1; break;
      default:
        NI_VERIFY_TRACE(false, "unsupported primitive type in road data", return);
      }
      Index* pIndices = pInd + desc.startIndex;
      const uint numIndices =  3 + step * (desc.primitiveCount - 1);

      if( const Vertex* pVertices = LockVB<Vertex>(Get(pVB), D3DLOCK_READONLY) )
      {
        const Index* const indEnd = pIndices + numIndices;
#ifdef _DEBUG
        for(const Index* pIdx = pIndices; pIdx < indEnd; pIdx += step)
          NI_ASSERT(pIdx[0] < numVertices, "corrupted road indices");
#endif // _DEBUG
        patchIDs.reserve(desc.primitiveCount);
        for(const Index* triangle = pIndices; triangle < indEnd; triangle += step)
        {
          CVec2 center = pVertices[triangle[0]].position.AsVec2D() +
                         pVertices[triangle[1]].position.AsVec2D() +
                         pVertices[triangle[2]].position.AsVec2D();
          patchIDs.push_back( pGetter->GetScaledPatchID(center) ); 
        }
        pVB->Unlock();
      }

      patchIDs.push_back(UINT_MAX); // make barrier - UINT_MAX should be invalid patch ID
      CreatePatches( &patchIDs[0], patchIDs.size() );
      patchIDs.clear();

      ScopedPtr<Index> pTmp(new Index[numIndices]);
      memcpy( Get(pTmp), pIndices, numIndices * sizeof(Index) );
      MergePatches( pIndices, Get(pTmp) );

      pIB->Unlock();
    }

    Patch* currPatch = &patches[0];
    for(const Patch* const end = currPatch + patches.size(); currPatch < end; ++currPatch)
      currPatch->pParams = pGetter->GetCacheParams(currPatch->patch);
  }
}


void PatchMapping::CreatePatches( const uint* _pIDsStart, uint _numTris)
{
  const uint* triangle = _pIDsStart, *lastPatch = _pIDsStart;
  for(const uint* const end = triangle + _numTris - 1; triangle < end; ++triangle)
    if( triangle[0] != triangle[1] ) {
      patches.push_back( Patch(lastPatch - _pIDsStart, triangle - lastPatch, *lastPatch) );
      lastPatch = triangle + 1;
    }
}


void PatchMapping::MergePatches(Index* _pIndices, const Index* _pTemp)
{ // merge all triangles that belongs to the same terrain patch
  Map newPatches( 1, Patch(0, 0, patches[0].patch) );

  sort( patches.begin(), patches.end() );
  patches.push_back( Patch(0, 0, UINT_MAX) ); // barrier
  Patch* currPatch = &patches[0];
  Index* indices = _pIndices;
  for(const Patch* const end = currPatch + patches.size() - 1; currPatch < end; ++currPatch)
  {
    const Index* source = _pTemp + currPatch->start * 3;
    const uint patchSize = (currPatch->size + 1) * 3;
    for(uint n = 0; n < patchSize; n += 3)
    {
      indices[n + 0] = source[n + 0];
      indices[n + 1] = source[n + 1];
      indices[n + 2] = source[n + 2];
    }
    indices += patchSize;

    if( currPatch->patch != currPatch[1].patch ) {
      Patch &newPatch = newPatches.back();
      const uint displacement = indices - _pIndices;
      newPatch.size = (displacement - newPatch.start) / 3;
      ASSERT(uint(newPatch.size * 3) == displacement - newPatch.start);
      newPatches.push_back( Patch(displacement, 0, currPatch[1].patch) );
    }
  }

  newPatches.pop_back();
  patches.swap(newPatches);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RoadPrimitive implementation
///////////////////////////////////////////////////////////////////////////////////////////////////

void RoadPrimitive::SetTEGetter(TEGetter* _pGetter)
{
  pGetter = _pGetter;
}


void RoadPrimitive::FillCache() const
{
  DipDescriptor dipDesc = pPrimitive->GetDipDescriptor();
  ASSERT(dipDesc.startIndex == 0);
  dipDesc.primitiveCount = 0;

  PatchMapping::Map::const_iterator it = pPatchMapping->patches.begin();
  CVec4 scaleShift = it->pParams->scaleShift;
  for(PatchMapping::Map::const_iterator const end = pPatchMapping->patches.end(); it != end; ++it)
  {
    const PatchCacheParams* pParams = it->pParams;
    if(pParams->pin == NDb::CACHINGPIN_FILL && pParams->scaleShift == scaleShift)
      dipDesc.primitiveCount += it->size;
    else {
      if(dipDesc.primitiveCount) {
        GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST3, scaleShift);
        SmartRenderer::DrawIndexedPrimitive(dipDesc);
      }

      scaleShift = pParams->scaleShift;
      if(pParams->pin == NDb::CACHINGPIN_FILL) {
        dipDesc.primitiveCount = it->size;
        dipDesc.startIndex = it->start;
      }
      else { // skip current part
        dipDesc.primitiveCount = 0;
        dipDesc.startIndex = it->start + it->size * 3u;
      }
    }
  }
  if(dipDesc.primitiveCount) {
    GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST3, scaleShift);
    SmartRenderer::DrawIndexedPrimitive(dipDesc);
  }
}


void RoadPrimitive::DrawWithCache() const // Actually, this function draws only NON-CACHED road part
{
  DipDescriptor dipDesc = pPrimitive->GetDipDescriptor();
  ASSERT(dipDesc.startIndex == 0);
  dipDesc.primitiveCount = 0;

  PatchMapping::Map::const_iterator const end = pPatchMapping->patches.end();
  for(PatchMapping::Map::const_iterator it = pPatchMapping->patches.begin(); it != end; ++it)
  {
    if(it->pParams->pin == NDb::CACHINGPIN_ORDINARY)
      dipDesc.primitiveCount += it->size;
    else {
      if(dipDesc.primitiveCount)
        SmartRenderer::DrawIndexedPrimitive(dipDesc);
      dipDesc.startIndex += (dipDesc.primitiveCount + it->size) * 3;
      ASSERT(dipDesc.startIndex == it->start + it->size * 3u);
      dipDesc.primitiveCount = 0;
    }
  }
  if(dipDesc.primitiveCount)
    SmartRenderer::DrawIndexedPrimitive(dipDesc);
}


void RoadPrimitive::Draw() const
{
  switch(GetRuntimePins().CachingPinValue)
  {
  case NDb::CACHINGPIN_ORDINARY:
    pPrimitive->Draw(); break;
  case NDb::CACHINGPIN_FILL:
    FillCache(); break;
  default:
    DrawWithCache();
  }
}

}