#include "StdAfx.h"
#include <Render\batch.h>
#include "TerrainTextureCache.h"
#include <System\BitData.h>
#include <Terrain\TerrainElement.h>

DEFINE_DEV_VAR(s_debugCache, false, "debug_TexCache", STORAGE_NONE)
DEFINE_DEV_VAR(s_insideOnly, false, "gfx_CacheInsideOnly", STORAGE_NONE);

namespace Terrain {

using namespace Render;

// =======================================================================================
inline const TerrainElement* GetElement(const Batch* _pBatch)
{
  CHECK_TYPE(const TerrainElement, _pBatch->pOwner);
  return static_cast<const TerrainElement*>(_pBatch->pOwner);
}

// =======================================================================================
class TerrainTextureCacheImpl : public DeviceLostHandler, public TerrainTextureCache
{
  static const uint START_TIME_STAMP = 17; // Any value greater than 1 will suffice

  static const uint maxTiles = 8;
  CVec2 tags[maxTiles][maxTiles];
  uint  timeStamps[maxTiles][maxTiles];

  CVec4 scaleAndShift;// world space to texture space transform
  CVec2 visibleSize;  // visible rectangle's size
  Texture2DRef tex;
  Batch*  excessBatches[2];
  Batch** subQueueTails[2];
  uint  currTimeStamp;
  uint  numTiles;     // number of terrain tiles per cache side
  float tileSize;     // in meters
  float tileSizeUV;   // 1 / numTiles
  bool  isNatureChanging;
  AABB  cacheAABB;

  void ComputeTerrainVisibility(const BatchQueue &_batchQueue);

  bool IsCleared(const CVec2 &_tag) { return _tag.x == FLT_MAX && _tag.y == FLT_MAX; }
  void ClearTag(uint i, uint j)
  {
    tags[i][j].Set(FLT_MAX, FLT_MAX);
    timeStamps[i][j] = 0;
  }
  void ClearTags()
  {
    for(uint i = 0; i < maxTiles; ++i)
      for(uint j = 0; j < maxTiles; ++j)
        ClearTag(i, j);
  }

  SVector GetIndices(const CVec2 &_coords) const
  {
    CVec2 scaled(_coords.x * scaleAndShift.x, _coords.y * scaleAndShift.y);
    return SVector((scaled - CVec2(floor(scaled.x), floor(scaled.y))) * numTiles);
  }


public:
  TerrainTextureCacheImpl(UINT _size, UINT _tileSize) : DeviceLostHandler(HANDLERPRIORITY_SUPER_LOW)
    , currTimeStamp(START_TIME_STAMP), numTiles(maxTiles), tileSize(_tileSize), tileSizeUV(1.f/numTiles), isNatureChanging(false)
  {
    ClearTags();
    cacheAABB.Init2Empty();

    GetDevice()->EvictManagedResources();

    D3DSURFACE_DESC desc = { D3DFMT_A8R8G8B8, D3DRTYPE_SURFACE,
                             D3DUSAGE_RENDERTARGET | 0, // D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP
                             D3DPOOL_DEFAULT, D3DMULTISAMPLE_NONE, 0, _size, _size };
    tex = ::Create<Texture2D>(desc, HANDLERPRIORITY_LOW);

    const float texWidth = tex->GetWidth();
    const float texHeight = tex->GetHeight();
    scaleAndShift.z = texWidth ? -0.5f / texWidth : 0.0f;
    scaleAndShift.w = texHeight ? 0.5f / texHeight : 0.0f;
  }

  virtual ~TerrainTextureCacheImpl(void) {}

  virtual void OnDeviceLost()  { ClearTags(); }
  virtual void OnDeviceReset() {}

  virtual bool IsValid() { return IsValidPtr(tex); }

  virtual void OnNatureAttack() { isNatureChanging = true; }

  virtual void OnRender(Render::BatchQueue& _queue);
  virtual void RestoreQueue(Render::BatchQueue& _queue);
  virtual void OnFillStart(BatchQueue *_pQueue);
  virtual void OnFillEnd(BatchQueue *_pQueue);
  virtual const Texture2D* GetTexture(const CVec2 *_pCenter) const;
  virtual const AABB& GetAABB() const { return cacheAABB; }

  __forceinline bool IsCached(const SVector& _indices, const CVec2& _center) const
  {
    return (currTimeStamp - timeStamps[_indices.x][_indices.y] < 2) && (tags[_indices.x][_indices.y] == _center);
  }

  bool IsCached(const CVec2& _center) const
  {
    return IsCached(GetIndices(_center), _center);
  }

  bool RefreshCache(const Batch *_pBatch)
  {
    const TerrainElement* const pElement = GetElement(_pBatch);
    const CVec2 &center = pElement->worldAABB.center.AsVec2D();
    const SVector& indices = GetIndices(center);
    if(pElement->cacheParams.layer1_element != PatchCacheParams::NON_CACHED_OR_SINGLE)
      ClearTag(indices.x, indices.y);
    else
      if( IsCached(indices, center) )
        timeStamps[indices.x][indices.y] = currTimeStamp;

    return false;
  }

  // SplitQueues helper. To cache or not to cache - this is decided here
  bool RegisterBatch(const Batch *_pBatch);

  // SplitQueues helpers. Used with MATERIALPRIORITY_TERRAINLAYER1 batches
  static bool RegisterBatch1(const Batch *_pBatch);
  static bool MarkAsMultiLayer(const Batch *_pBatch);
  bool IsNotCached(const Batch *_pBatch);
  void PreRenderLayer0(Batch **_pQueue, Batch* (&cachedBatches)[3], Batch** (&queueTailes)[3]);
};


// =======================================================================================
// == TerrainTextureCacheImpl helpers =============================================
// =======================================================================================
#define MAKE_PRED_(_method, _arg_type) \
  class _method##Pred : public nstl::unary_function<bool, _arg_type>, NonCopyable  \
  {                                                                                \
    TerrainTextureCacheImpl &cache;                                                \
  public:                                                                          \
    _method##Pred(TerrainTextureCacheImpl &_cache) : cache(_cache) {}              \
    bool operator()(_arg_type _arg) const { return cache._method(_arg); }    \
  };

#define MAKE_PRED(_method) MAKE_PRED_(_method, const Batch *)

MAKE_PRED(RefreshCache)
MAKE_PRED(RegisterBatch)
MAKE_PRED(RegisterBatch1)
MAKE_PRED(MarkAsMultiLayer)
MAKE_PRED(IsNotCached)

// =======================================================================================
template<class Pred> void Iterate(const Pred &_pred, const Batch* _batches)
{
  for(const Batch* pBatch = _batches;  pBatch;  pBatch = pBatch->pNextBatch)
    _pred(pBatch);
}

// =======================================================================================
void SetPin(const Batch* _batches, NDb::CachingPin _value)
{
  for(const Batch* pBatch = _batches;  pBatch;  pBatch = pBatch->pNextBatch)
    GetElement(pBatch)->cacheParams.pin = _value;
}

// Splits queue in 2 parts - 1-st contains those batches satisfying Pred, 2-nd - the rest. Returns pointer to 2-nd queue part
// =======================================================================================
template<class Pred> Batch* SplitQueues(const Pred &_pred, /*in-out*/ Batch **_pQueue, /*out*/ Batch ***_ppQueueTail)
{
  Batch *tempQueue = 0;
  for(Batch *pBatch = *_pQueue;  pBatch;) {
    Batch* const pNextBatch = pBatch->pNextBatch;
    if( _pred(pBatch) )
      _pQueue = &pBatch->pNextBatch;
    else { // move excess batch to temporary queue
      // skip excess batch
      *_pQueue = pNextBatch;
      // add it to temporary queue's head
      Batch *temp = tempQueue;
      tempQueue = pBatch;
      tempQueue->pNextBatch = temp;
    }
    pBatch = pNextBatch;
  }
  *_ppQueueTail = _pQueue;
  return tempQueue;
}

// =======================================================================================
// == TerrainTextureCacheImpl implementation =============================================
// =======================================================================================
void TerrainTextureCacheImpl::ComputeTerrainVisibility( const BatchQueue &_batchQueue )
{
  CTRect<float> visibleRect;
  for(const Batch* pBatch = _batchQueue.GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER0);
    pBatch; pBatch = pBatch->pNextBatch)
  {
    const TerrainElement* const pElement = GetElement(pBatch);
    const AABB &aabb = pElement->GetWorldAABB();
    visibleRect.Union( CTRect<float>(aabb.center.AsVec2D() - aabb.halfSize.AsVec2D(),
                                     aabb.center.AsVec2D() + aabb.halfSize.AsVec2D()) );
  }
  { // temporary hack
    //const AABB &aabb(static_cast<const TerrainElement*>(_queue.GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER0)->pOwner)->GetWorldAABB());
    //visibleSize.Set(aabb.halfSize.x * 16, aabb.halfSize.y * 16);
    const CVec2 currSize( visibleRect.GetSizeX(), visibleRect.GetSizeY() );
    float sideSize = numTiles * tileSize;
    const float effCurrSize = sqrtf(currSize.x * currSize.y);
    const uint oldNumTiles = numTiles;
    if(effCurrSize < 0.6f * sideSize)
      numTiles >>= 1;
    else if(effCurrSize > 1.5f * sideSize)
      numTiles <<= 1;

    if(numTiles < 2)
      numTiles = 2;
    if(numTiles > maxTiles)
      numTiles = maxTiles;

    if(oldNumTiles != numTiles) {
      sideSize = numTiles * tileSize;
      ClearTags();
    }

    visibleSize.Set(sideSize, sideSize);
  }
  scaleAndShift.x = 1.f / visibleSize.x;
  scaleAndShift.y = 1.f / visibleSize.y;
  TerrainElement::SetCacheScaleShift(scaleAndShift);
}

// =======================================================================================
void TerrainTextureCacheImpl::OnRender(Render::BatchQueue& _queue)
{
  Batch* &subQueue1 = _queue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER1).pBatchList;
//#ifdef _DEBUG
//  {
//    nstl::hash_set<const void*> elemSet;
//    for(Batch *pBatch = subQueue1;  pBatch;  pBatch = pBatch->pNextBatch)
//    {
//      ASSERT( elemSet.find(pBatch->pOwner) == elemSet.end() );
//      elemSet.insert(pBatch->pOwner);
//    }
//  }
//#endif // _DEBUG
  // don't render cached LAYER1 batches - they are baked to LAYER0
  excessBatches[1] = SplitQueues(IsNotCachedPred(*this), &subQueue1, subQueueTails + 1);

  Batch* cachedBatches[3];
  Batch** queueTailes[3];
  Batch* &_subQueue = _queue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER0).pBatchList;
  PreRenderLayer0(&_subQueue, cachedBatches, queueTailes);

  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_USE;
  swap(_subQueue, cachedBatches[0]);
  _queue.Render(NDb::MATERIALPRIORITY_TERRAINLAYER0);
  swap(_subQueue, cachedBatches[0]);

  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_USE2;
  swap(_subQueue, cachedBatches[1]);
  _queue.Render(NDb::MATERIALPRIORITY_TERRAINLAYER0);
  swap(_subQueue, cachedBatches[1]);

  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_USE3;
  swap(_subQueue, cachedBatches[2]);
  _queue.Render(NDb::MATERIALPRIORITY_TERRAINLAYER0);
  swap(_subQueue, cachedBatches[2]);

  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_ORDINARY;
  // merge cachedBatches to one tail list
  *queueTailes[1] = cachedBatches[1];
  //if(queueTailes[2])
    *queueTailes[2] = cachedBatches[2];
  excessBatches[0] = cachedBatches[0];
  subQueueTails[0] = queueTailes[0];
}

// =======================================================================================
void TerrainTextureCacheImpl::RestoreQueue(Render::BatchQueue& _queue)
{
  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_ORDINARY;

  *subQueueTails[0] = excessBatches[0]; // restore MATERIALPRIORITY_TERRAINLAYER0 batch queue
  *subQueueTails[1] = excessBatches[1]; // restore MATERIALPRIORITY_TERRAINLAYER1 batch queue

  //for(const Batch* pBatch = excessBatches[0];  pBatch;  pBatch = pBatch->pNextBatch)
  //  GetElement(pBatch)->ClearCachingState();
  for(const Batch* pBatch = _queue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER0).pBatchList;  pBatch;  pBatch = pBatch->pNextBatch)
    GetElement(pBatch)->ClearCachingState();
  for(const Batch* pBatch = _queue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER1).pBatchList;  pBatch;  pBatch = pBatch->pNextBatch)
    GetElement(pBatch)->ClearCachingState();
}

// =======================================================================================
void TerrainTextureCacheImpl::OnFillStart(BatchQueue *_pQueue)
{
  ++currTimeStamp;
  if(currTimeStamp < START_TIME_STAMP)
    currTimeStamp = START_TIME_STAMP;
  ComputeTerrainVisibility(*_pQueue);

  SmartRenderer::BindRenderTarget(tex);
  if(s_debugCache) {
    GetRenderer()->ClearColorOnly( Color(0) );
    ClearTags(); // Temporary hack
  }

  Batch* &subQueue1 = _pQueue->GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER1).pBatchList;
  if(isNatureChanging)
    Iterate(MarkAsMultiLayerPred(*this), subQueue1);

  cacheAABB.Init2Empty();
  Batch* &subQueue0 = _pQueue->GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER0).pBatchList;
  Iterate(RefreshCachePred(*this), subQueue0);

  // batches in TERRAINLAYER1 are first candidates to cache
  excessBatches[0] = SplitQueues(RegisterBatchPred(*this), &subQueue0, subQueueTails);
  excessBatches[1] = SplitQueues(RegisterBatch1Pred(*this), &subQueue1, subQueueTails + 1);

#ifdef _DEBUG
  class TestPred : public NonCopyable
  {
    const AABB &aabb;
  public:
    TestPred(const TerrainTextureCacheImpl &_cache) : aabb(_cache.GetAABB()) {}
    void operator()(const Batch* _pBatch) const
    {
      bool isLocalAABB = false;
      NI_ASSERT(_pBatch->pOwner->GetAABB(&isLocalAABB).IsIntersectedBy(aabb) && !isLocalAABB, "Wrong AABB");
    }
  } testPred(*this);

  if( !cacheAABB.IsEmpty() ) {
    Iterate(testPred, subQueue0);
    Iterate(testPred, subQueue1);
  }
#endif // _DEBUG

  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_FILL;
}

// =======================================================================================
void TerrainTextureCacheImpl::OnFillEnd(BatchQueue *_pQueue)
{
  GetRuntimePins().CachingPinValue = NDb::CACHINGPIN_ORDINARY;

  SetPin(_pQueue->GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER0), NDb::CACHINGPIN_ORDINARY);
  *subQueueTails[0] = excessBatches[0]; // merge all batches to subqueue
  SetPin(_pQueue->GetBatches(NDb::MATERIALPRIORITY_TERRAINLAYER1), NDb::CACHINGPIN_ORDINARY);
  *subQueueTails[1] = excessBatches[1]; // merge all batches to subqueue
}

// =======================================================================================
const Texture2D* TerrainTextureCacheImpl::GetTexture(const CVec2 *_pCenter) const
{
  if(_pCenter) {
    const SVector& indices = GetIndices(*_pCenter);
    if(tags[indices.x][indices.y] != *_pCenter)
      return 0;
  }
  return tex;
}

// =======================================================================================
inline bool TerrainTextureCacheImpl::RegisterBatch(const Batch *_pBatch)
{
  if(s_insideOnly && !_pBatch->isInside)
    return false;
  const TerrainElement* const pElement = GetElement(_pBatch);
  const CVec2 &center = pElement->worldAABB.center.AsVec2D();
  if(pElement->cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE)
  {
    const SVector& indices = GetIndices(center);
    uint &timeStamp = timeStamps[indices.x][indices.y];
    if( currTimeStamp != timeStamp ) {
      timeStamp = currTimeStamp;
      tags[indices.x][indices.y] = center;
      pElement->cacheParams.pin = NDb::CACHINGPIN_FILL;
      cacheAABB.Grow(pElement->worldAABB);
      return true;
    }
  }
  return false;
}

// =======================================================================================
inline bool TerrainTextureCacheImpl::RegisterBatch1(const Batch *_pBatch)
{
  return NDb::CACHINGPIN_FILL == GetElement(_pBatch)->cacheParams.pin;
}

// =======================================================================================
inline bool TerrainTextureCacheImpl::MarkAsMultiLayer(const Batch *_pBatch)
{
  //PatchCacheParams &cacheParams = GetElement(_pBatch)->cacheParams;
  //if(cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE)
  //  cacheParams.layer1_element = _pBatch->elementNumber;
  //else
  //  cacheParams.layer1_element2 = _pBatch->elementNumber;
  GetElement(_pBatch)->cacheParams.layer1_element = 17; // Any number, different from NON_CACHED_OR_SINGLE, will fit
  return false;
}

// =======================================================================================
inline bool TerrainTextureCacheImpl::IsNotCached(const Batch *_pBatch)
{
  const TerrainElement* const pElement = GetElement(_pBatch);
  if( IsCached(pElement->GetWorldAABB().center.AsVec2D()) ) {
    PatchCacheParams &cacheParams = pElement->cacheParams;

    ASSERT(cacheParams.layer1_element2 == PatchCacheParams::NON_CACHED_OR_SINGLE);
    if(cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE)
      cacheParams.layer1_element = _pBatch->elementNumber;
    else
      cacheParams.layer1_element2 = _pBatch->elementNumber;

    return isNatureChanging;
  }
  return true;
}

// =======================================================================================
inline void TerrainTextureCacheImpl::PreRenderLayer0(Batch **_pQueue, Batch* (&cachedBatches)[3], Batch** (&queueTailes)[3])
{
  Batch *use_queue = 0, *use2_queue = 0, *use3_queue = 0;
  Batch **pUseQueueTail = cachedBatches;
  Batch **pUse2QueueTail = cachedBatches + 1;
  for(Batch *pBatch = *_pQueue;  pBatch;) {
    Batch* const pNextBatch = pBatch->pNextBatch;
    const TerrainElement* const pElement = GetElement(pBatch);
    bool skipped = false;

    if( isNatureChanging && (pElement->cacheParams.layer1_element != PatchCacheParams::NON_CACHED_OR_SINGLE) )
    { // don't render USE2/USE3 patches with cache while nature is attacking
      const SVector& indices = GetIndices( pElement->GetWorldAABB().center.AsVec2D() );
      ClearTag(indices.x, indices.y);
      pElement->ClearCachingState();
      skipped = true;
    }
    
    if( skipped || !IsCached(pElement->worldAABB.center.AsVec2D()) )
      _pQueue = &pBatch->pNextBatch;
    else { // move excess batch to temporary queue
      // skip excess batch
      *_pQueue = pNextBatch;
      // add it to one of temporary queues' head
      if(pElement->cacheParams.layer1_element == PatchCacheParams::NON_CACHED_OR_SINGLE)
      {
        Batch *temp = use_queue;
        use_queue = pBatch;
        use_queue->pNextBatch = temp;
        pElement->cacheParams.pin = NDb::CACHINGPIN_USE;
        if(pUseQueueTail == cachedBatches)
          pUseQueueTail = &use_queue->pNextBatch;
      }
      else if(pElement->cacheParams.layer1_element2 == PatchCacheParams::NON_CACHED_OR_SINGLE)
      {
        Batch *temp = use2_queue;
        use2_queue = pBatch;
        use2_queue->pNextBatch = temp;
        pElement->cacheParams.pin = NDb::CACHINGPIN_USE2;
        if(pUse2QueueTail == cachedBatches + 1)
          pUse2QueueTail = &use2_queue->pNextBatch;
      }
      else {
        Batch *temp = use3_queue;
        use3_queue = pBatch;
        use3_queue->pNextBatch = temp;
        pElement->cacheParams.pin = NDb::CACHINGPIN_USE3;
      }
    }
    pBatch = pNextBatch;
  }
  cachedBatches[0] = use_queue;
  cachedBatches[1] = use2_queue;
  cachedBatches[2] = use3_queue;
  queueTailes[0] = _pQueue;
  queueTailes[1] = pUseQueueTail;
  queueTailes[2] = pUse2QueueTail;

  isNatureChanging = false;
}

// =======================================================================================
TerrainTextureCache* TerrainTextureCache::Create(UINT _size, UINT _tileSize)
{
  return ::Create<TerrainTextureCacheImpl>(_size, _tileSize);
}

} // namespace Terrain