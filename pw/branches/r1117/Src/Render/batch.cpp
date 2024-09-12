#include "stdafx.h"
#include <algorithm>
#include "renderer.h"
#include "batch.h"
#include "DXManager.h"

#include "../System/InlineProfiler.h"
#include "SmartRenderer.h"
#include "DXHelpers.h"
#include "ParticleFX.h"

//static bool g_checkSortId = false;
//REGISTER_DEV_VAR("bvsbvs", g_checkSortId, STORAGE_NONE);

static bool s_queryUP = false;
REGISTER_VAR("waterQueryUP", s_queryUP, STORAGE_NONE);

static bool s_sortNew = true;
REGISTER_DEV_VAR("newTranspSort", s_sortNew, STORAGE_NONE);

static NDebug::PerformanceDebugVar g_timeManage( "DXHint:Manage", "Render", 0, 1.0, false );
#ifndef _SHIPPING
  static NDebug::DebugVar<int> g_NumSkinnedVertices("numSkinnedVertices", "Render", true);
  static NDebug::DebugVar<int> g_NumSkinnedTriangles("numSkinnedTriangles", "Render", true);

//#define COUNT_DRAWS
//#define _CUSTOM_DEBUG
#ifdef COUNT_DRAWS
  static NDebug::DebugVar<int> g_NumBatchDraws("numBatchDraws", "Render", true);
  static NDebug::DebugVar<int> g_NumNewInstances("numNewInstances", "Render", true);
#endif

  static bool s_drawSkeletalSimple = false;
  REGISTER_DEV_VAR("drawSkeletalSimple", s_drawSkeletalSimple, STORAGE_NONE);

  static bool s_doInstancing = true;
  REGISTER_DEV_VAR("automaticInstancing", s_doInstancing, STORAGE_NONE);
#else
enum {
  s_drawSkeletalSimple = false,
  s_doInstancing = true
};
#endif
namespace Render
{

static IBatchQueueLogger *s_pLogger = 0;
static int  s_materialSwitchCounter = 0;
static bool s_renderingShadow = false;

#ifndef _SHIPPING
#define ALLOW_LOGGING
#endif

#ifdef ALLOW_LOGGING

#define COUNT_MAT_SWITCHES ++s_materialSwitchCounter

inline void LOG_RENDER_SEQUENCE(const Batch& _batch)
{
  if(s_pLogger)
    (*s_pLogger)(_batch);
}

#else

#define COUNT_MAT_SWITCHES
#define LOG_RENDER_SEQUENCE(_batch_)

#endif

#ifndef _SHIPPING
//#define _CHECK_SUBPIORITIES
#endif

#ifdef _CHECK_SUBPIORITIES

struct SPriorityCheck
{
  struct hashFunc
  {
    size_t operator()(const SPriorityCheck &_src) const { return (int&)_src.z ^ _src.subPiority; }
  };

  float z;
  int subPiority;

  SPriorityCheck(float _z, int _subPiority) : z(_z), subPiority(_subPiority) {}

  bool operator==(const SPriorityCheck &_src) const { return z == _src.z && subPiority == _src.subPiority; }
};

typedef hash_map<SPriorityCheck, string, SPriorityCheck::hashFunc> SPriorityHash;
static SPriorityHash s_SubPioritiesHash;

static bool s_checkSubPriorities = false;
REGISTER_DEV_VAR("checkSubPriorities", s_checkSubPriorities, STORAGE_NONE);

#endif


class ZeroScissor
{
  RECT  rect;
  DWORD oldVal;
  NDb::RenderModePin oldMode;
  bool  isSet;

public:
  ZeroScissor() { isSet = false; }

  void Enable(bool _enable)
  {
#ifndef _SHIPPING
    static const RECT  zeroRect = {0, 0, 1, 1};

    IDirect3DDevice9* const pDevice = GetDevice();

    if(_enable)
    {
      if(!isSet)
      {
        pDevice->GetRenderState(D3DRS_SCISSORTESTENABLE, &oldVal);
        pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);

        pDevice->GetScissorRect(&rect);
        pDevice->SetScissorRect(&zeroRect);

        oldMode = GetRuntimePins().RenderModeValue;
        GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERSHAPEONLY;
      }
    }
    else
    {
      if(!isSet)
        return;

      pDevice->SetScissorRect(&rect);
      pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
      GetRuntimePins().RenderModeValue = oldMode;
    }

    isSet = _enable;
#endif // _SHIPPING
  }
};

static ZeroScissor s_ZeroScissor;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CompareFarToNear
{
  // FAR = large negative sortValue
	static bool Less( const Batch* pP1, const Batch* pP2 )
	{
		if ( pP1->sortValue != pP2->sortValue )
    {
      if(s_sortNew)
      {
        return pP1->sortValue > pP2->sortValue;
      }
			return pP1->sortValue < pP2->sortValue;
    }
		else
    {
      const int prio1 = pP1->pMaterial->GetSubPriority();
      const int prio2 = pP2->pMaterial->GetSubPriority();
			return prio1 > prio2;
    }
	}
	static void BatchProcess( Batch &batch ) {}
};
/*
struct CompareNearToFar
{
	static bool Less( const Batch* pP1, const Batch* pP2 )
	{
		if ( pP1->sortValue != pP2->sortValue )
			return pP1->sortValue < pP2->sortValue;
		else
			return pP1->pMaterial->GetSubPriority() > pP2->pMaterial->GetSubPriority();
	}
	static void BatchProcess( Batch &batch ) {}
};
*/
struct CompareSortId
{
	static bool Less( const Batch* pP1, const Batch* pP2 )
	{
    const UINT sortId1 = pP1->GetSortId(), sortId2 = pP2->GetSortId();
    if(sortId1 == sortId2)
      return pP1->pPrimitive < pP2->pPrimitive;
    else
		  return sortId1 < sortId2;
	}

	static void BatchProcess( Batch &batch )
	{
		// Evaluate sort ID when needed
		batch.GetSortId();
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class CMP_POLICY>
void insertSort(T a[], long size)
{
	T x;
	long i, j;

	// цикл проходов, i - номер прохода
	for ( i = 0; i < size; ++i ) 
	{
		x = a[i];

		// поиск места элемента в готовой последовательности 
		for ( j = i - 1; j >= 0 && CMP_POLICY::Less(x,a[j]); --j )
		{
			a[j+1] = a[j];  	// сдвигаем элемент направо, пока не дошли
		}

		// место найдено, вставить элемент
		a[j+1] = x;
	}
}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool s_enableWaterLevel = false;
static float s_WaterLevel = 0.0f;

void Batch::SetWaterLevel(bool _enable, float _level)
{
  s_enableWaterLevel = _enable;
  s_WaterLevel = _level + 0.02f;
}


__forceinline void Batch::Prepare() const
{
  s_ZeroScissor.Enable(s_drawSkeletalSimple && pMaterial->GetSkeletalMeshPin() == NDb::BOOLEANPIN_PRESENT);

  if(s_renderingShadow && static_cast<ShadowMaterial*>(pMaterial)->oldInstancing)
  {
    GUARD_VALUE(GetRuntimePins().InstancingValue, NDb::BOOLEANPIN_PRESENT);
    pMaterial->PrepareRenderer();
  }
  else
    pMaterial->PrepareRenderer();

  COUNT_MAT_SWITCHES;
}


__forceinline void Batch::Draw() const
{
  if( dontDraw )
    return;

#ifndef _SHIPPING // Collect skinning statistics
  if( NDb::BOOLEANPIN_PRESENT == pMaterial->GetSkeletalMeshPin() &&
      NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH != pMaterial->GetLightingPin() )
  {
    const GeometryStatistics& stats = pPrimitive->GetStats();
    g_NumSkinnedVertices.AddValue( min(stats.numVertices, stats.numTriangles * 3) );
    g_NumSkinnedTriangles.AddValue(stats.numTriangles);
  }
#ifdef COUNT_DRAWS
  g_NumBatchDraws.AddValue(1);
#endif
#endif

  pMaterial->PrepareRendererWithBatch(*this);
  pOwner->PrepareRendererAfterMaterial(elementNumber);
  pPrimitive->Bind();
  pPrimitive->Draw();

  LOG_RENDER_SEQUENCE(*this);
}

__forceinline void Batch::IssueQueryUP()
{
  static CVec3 Vertices[8];

  dontDraw = false;
  if( OcclusionQueries* const queries = pOwner->GetQueries() )
  {
    OcclusionQueriesBank& bank = queries->Get();
    if( SUCCEEDED(bank.BeginNextQuery()) )
    {
      if( pOwner->FillOBB(Vertices) )
      {
        // Close truncated OBB. I assume here that basis[2] is Z-aligned and the basis is orthogonal
        if(s_enableWaterLevel && Vertices[0].z < s_WaterLevel && Vertices[6].z > s_WaterLevel)
        {
          Vertices[0].z = s_WaterLevel;
          Vertices[1].z = s_WaterLevel;
          Vertices[2].z = s_WaterLevel;
          Vertices[3].z = s_WaterLevel;
        }

        CubeRenderer::DrawIndexedPrimitiveUP(Vertices);
      }
      bank.EndNextQuery();
    }
  }
}

__forceinline void Batch::IssueQuery()
{
  dontDraw = false;
  if( OcclusionQueries* const queries = pOwner->GetQueries() )
  {
    OcclusionQueriesBank& bank = queries->Get();
    if( SUCCEEDED(bank.BeginNextQuery()) )
    {
      static const float zEps = 0.02f;

      const Matrix43& world = pOwner->GetWorldMatrix();
      const AABB& localAABB = pOwner->GetLocalAABB();
      CVec3 localPos = localAABB.center;
      CVec3 halfSize = localAABB.halfSize;
      const float diff = s_WaterLevel + zEps - (localPos.z - halfSize.z) - world._34;
      if(diff > 0.0f)
      {
        const float shift = diff * 0.5f;
        localPos.z += shift;
        halfSize.z -= shift;
      }
      if(halfSize.z > 0.0f)
      {
        Matrix43 worldCorrected(localPos);
        worldCorrected.SetScale(halfSize);
        worldCorrected = world * worldCorrected;
        GetRenderer()->SetVertexShaderConstants(WORLD, 3, &worldCorrected);
        CubeRenderer::Draw();
      }
      bank.EndNextQuery();
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::SetRenderLogger(IBatchQueueLogger *pL) { s_pLogger = pL; }
bool BatchQueue::IsLoggingActive() { return s_pLogger != 0; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BatchQueue::BatchQueue( Index ndx, BatchQueueSorter &_sorter, int maxSize )
	: sorter(_sorter)
	, curSortingValue(0.0f)
	, pCurSHConsts(0)
	, index(ndx)
{ 
	elements.reserve(maxSize); 

	for (int i = 0; i < NDb::MATERIALPRIORITY_COUNT; ++i)
		priorities[i].bSort = false;

  Clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BatchQueue::~BatchQueue() {} // this destructor is defined here because exact meaning of <class DXManager> is defined only here

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::EnableResourceManagment(bool _enable)
{
  if( _enable && resourceManager.get() )
    return;

  resourceManager = std::auto_ptr<DXManager>(_enable ? new DeviceLostWrapper<DXManager> : 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BatchQueue::OnNextFrame()
{
  NDebug::PerformanceDebugVarGuard perfGuard(g_timeManage, true);

  if(!resourceManager.get() )
    return false;

  resourceManager->OnNextFrame();
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BatchQueue::ManageResources()
{
  NDebug::PerformanceDebugVarGuard perfGuard(g_timeManage, false);

  if(!resourceManager.get() )
    return false;

  resourceManager->Manage();
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::SetSorting( int priority, bool bSorting )
{
	ASSERT( 0 <= priority && priority < NDb::MATERIALPRIORITY_COUNT );
	priorities[priority].bSort = bSorting;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::Clear()
{
	elements.resize(0);
	// Drop structure
	for (int i = 0; i < NDb::MATERIALPRIORITY_COUNT; ++i)
	{
		priorities[i].numBatches = 0;
		priorities[i].pBatchList = 0;
	}
#ifdef _CHECK_SUBPIORITIES
  s_SubPioritiesHash.clear();
#endif
}

void BatchQueue::Push( int priority, 
                      const RenderComponent *pOwner, const IRenderablePrimitive *pPrimitive, 
                      unsigned int elementNumber, BaseMaterial *pMaterial )
{
  if ( pMaterial->GetAlternativeMaterial())
  {
    if(pMaterial->IsAltPriorityEnabled())
    {
      PushInternal( pMaterial->GetAlternativeMaterial()->GetAltPriority(), pOwner, pPrimitive, elementNumber, static_cast<BaseMaterial*>( pMaterial->GetAlternativeMaterial() ) );
      if ( pMaterial->GetAlternativeMaterial()->IsFadingAlternativeMaterial() )
        PushInternal( pMaterial->GetAlternativeMaterial()->GetBasePriority(), pOwner, pPrimitive, elementNumber, pMaterial );
    }
    else
      PushInternal( pMaterial->GetAlternativeMaterial()->GetPriority(), pOwner, pPrimitive, elementNumber, static_cast<BaseMaterial*>( pMaterial->GetAlternativeMaterial() ) );
  }
  else
  {
    PushInternal( priority, pOwner, pPrimitive, elementNumber, pMaterial );
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::PushInternal(int priority,
											const RenderComponent *pOwner, const IRenderablePrimitive *pPrimitive, 
											unsigned int elementNumber, BaseMaterial *pMaterial)
{
#ifdef _DEBUG
	ASSERT(*(uint*)this != 0xFEEEFEEE);
#endif // _DEBUG

	ASSERT( 0 <= priority && priority < NDb::MATERIALPRIORITY_COUNT );
  ASSERT( Material::SUBPRIORITY_MIN <= pMaterial->GetSubPriority() && pMaterial->GetSubPriority() <= Material::SUBPRIORITY_MAX );

	const int old_capacity = elements.capacity();
	Batch &batch = elements.push_back();
	const int new_capacity = elements.capacity();
	ASSERT(old_capacity == new_capacity);
	batch.pOwner        = pOwner;
	batch.elementNumber = elementNumber;
	batch.pPrimitive    = pPrimitive;
	ASSERT(pMaterial);
	batch.pMaterial     = pMaterial;
	batch.sortValue     = curSortingValue;
	batch.pSHConsts     = pCurSHConsts;
  batch.dontDraw      = false;
  batch.isInside      = false;

  Priority &batchList = priorities[priority];
	batch.pNextBatch    = batchList.pBatchList;
#ifdef _DEBUG
  ASSERT(*(uint*)&batch != 0xFEEEFEEE);
	if(batch.pNextBatch) {
		ASSERT(*(uint*)batch.pNextBatch != 0xFEEEFEEE);
	}
#endif // _DEBUG
	
	batchList.pBatchList = &batch; 
	batchList.numBatches++;

#ifdef _CHECK_SUBPIORITIES
  if(s_checkSubPriorities)
  {
    const int subPriority = batch.pMaterial->GetSubPriority();
    const float sortValue = batch.sortValue;
    const NDb::DBID* const pDBID = batch.pOwner->GetDBID();
    const string &name = pDBID ? pDBID->GetFileName() : string("");

    const pair<SPriorityHash::iterator, bool> &insResult =
      s_SubPioritiesHash.insert( make_pair(SPriorityCheck(sortValue, subPriority), name) );
    ASSERT(insResult.first.operator->());
    const string &prevName = insResult.first->second;
    NI_ASSERT( insResult.second, NStr::StrFmt("Duplicated (z,subPriority) pair found!\n\tNew object:%s,\n\tprev. object:%s",
                                     name.c_str(), prevName.c_str()) );
  }
#endif

  NDebug::PerformanceDebugVarGuard perfGuard(g_timeManage, false);

  if( DXManager* const pManager = resourceManager.get() )
  {
    pManager->AddGeometry( pPrimitive->GetBuffers() );
    pManager->AddTextures( pMaterial );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::ReplaceMaterial(int priority, BaseMaterial *pMaterial)
{
  for(Batch* pBatch = priorities[priority].pBatchList; pBatch; pBatch = pBatch->pNextBatch)
    pBatch->pMaterial = pMaterial;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::ReplaceMaterial(int beginPriority, int endPriority, BaseMaterial *pMaterial)
{
  ASSERT( 0 <= beginPriority && beginPriority < endPriority && endPriority <= NDb::MATERIALPRIORITY_COUNT );
  for (int priority = beginPriority; priority < endPriority; ++priority)
    ReplaceMaterial(priority, pMaterial);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BatchChunkBase
{
protected:

  Batch*   pBatch;
  BaseMaterial* pMaterial;
  IRenderablePrimitive const *currPrimitive;
  UINT numInstances;
  bool instanceable;
  enum
  {
    IM_UNDEFINED,
    IM_DISABLED,
    IM_ENABLED
  } instancingMode;

  static const UINT INSTANCING_BOUND = 10000;

  void DisableInstancing()
  {
    SmartRenderer::DisableHardwareInstancing();
    GetRuntimePins().InstancingValue = NDb::BOOLEANPIN_NONE;
    pBatch->Prepare();
    instancingMode = IM_DISABLED;
  }

  void DrawInstanced(Batch* _pBatch)
  {
    if(numInstances) {
      ASSERT(pBatch);
      if(instancingMode != IM_ENABLED) {
        GetRuntimePins().InstancingValue = NDb::BOOLEANPIN_PRESENT;
        pBatch->Prepare();
        instancingMode = IM_ENABLED;
      }
      pMaterial->RegisterInstancedBatch(*pBatch);
      SmartRenderer::EnableHardwareInstancing(numInstances + 1);
      SmartRenderer::BindInstanceVB();
      pBatch->Draw();
      numInstances = 0;
    }

    currPrimitive = (pBatch = _pBatch)->pPrimitive;
  }

  void DrawSingle() 
  {
    if(!numInstances)
    {
      if(instancingMode == IM_ENABLED && pBatch->pPrimitive->GetStats().numVertices < INSTANCING_BOUND)
      {
        pMaterial->RegisterInstancedBatch(*pBatch);
        SmartRenderer::EnableHardwareInstancing(1);
      }
      else if(instancingMode != IM_DISABLED )
        DisableInstancing();

      pBatch->Draw();
    }
    else
      numInstances = 0;
  }

public:
  BatchChunkBase() { Reset(); }

  void Reset()
  {
    pBatch = 0;
    currPrimitive = 0;
    numInstances = 0;
    instanceable = false;
    instancingMode = IM_UNDEFINED;
  }

  void AddBatch(Batch* _pBatch)
  {
    if(instanceable)
    {
      ASSERT(_pBatch);

      if(_pBatch->pPrimitive == currPrimitive && MAX_INSTANCES_COUNT - 1 > numInstances)
      {
        pMaterial->RegisterInstancedBatch(*_pBatch);
        ++numInstances;
      }
      else
        DrawInstanced(_pBatch);
    }
    else
      _pBatch->Draw();
  }

}; // class BatchChunkBase


template<typename Iterator = Batch**>
class BatchChunk : public BatchChunkBase
{
  Iterator ppStartBatch;

public:
  BatchChunk() : ppStartBatch() {}

  void Reset()
  {
    BatchChunkBase::Reset();
    ppStartBatch = Iterator();
  }

  void Finish(Iterator const _ppNewBatch)
  {
    if( instanceable && (Iterator() != ppStartBatch) )
    {
      DrawInstanced(pBatch);

      pBatch = *ppStartBatch;
      currPrimitive = pBatch->pPrimitive;

      while(++ppStartBatch != _ppNewBatch)
      {
        Batch* const pCurBatch = *ppStartBatch;
        if(pCurBatch->pPrimitive != currPrimitive || MAX_INSTANCES_COUNT <= numInstances)
        {
          currPrimitive = pCurBatch->pPrimitive;
          DrawSingle();
        }
        else
          ++numInstances;

        pBatch = pCurBatch;
      }
      DrawSingle();
    }

    instancingMode = IM_UNDEFINED;
  }

  void NewMaterial(Iterator _ppBatch)
  {
    pBatch = *_ppBatch;
    pMaterial = pBatch->pMaterial;
    ASSERT(pMaterial);

    instanceable = s_doInstancing && pMaterial->Instanceable();

    if(!instanceable)
    {
      DisableInstancing();
      pBatch->Draw();
      return;
    }

    ppStartBatch = _ppBatch;
    currPrimitive = pBatch->pPrimitive;
  }
};


static BatchChunk<> s_batchChunk;

#pragma warning(push)
#pragma warning(disable:4706)  // Disable C4706: assignment within conditional expression

template<UINT mode> 
static __forceinline void RenderBatch(Batch &batch, UINT &curSortId)
{
  const bool checkQueries = mode & OcclusionQueries::QUM_CHECK;
  if( checkQueries )
    if( OcclusionQueries* const queries = batch.pOwner->GetQueries() )
       if( batch.dontDraw = (queries->Get().GetLatestResults() == 0) )
         return;

  const UINT sortId = batch.GetSortId();

  if( (sortId != curSortId) || (sortId == 0) )
  {
	  batch.Prepare();
	  curSortId = sortId;
  }

  if( mode & OcclusionQueries::QUM_ISSUE  )
  {
	  OcclusionQueriesBank *pQueriesBank = 0;

    if( checkQueries || !batch.dontDraw ) // in checkQueries mode we don't need check batch.dontDraw here
    {
      if( OcclusionQueries* const queries = batch.pOwner->GetQueries() )
      {
        OcclusionQueriesBank& bank = queries->Get();
        if( SUCCEEDED(bank.BeginNextQuery()) )
          pQueriesBank = &bank;
      }
      batch.Draw();

      if(pQueriesBank)
        pQueriesBank->EndNextQuery();
    }
  }
  else
    batch.Draw();
}


#pragma warning(pop)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::RenderBatchesPtrArray(UINT numBatches, Batch **pBatches)
{
  if(!numBatches)
    return;

  unsigned int curSortId = 0;
#ifdef COUNT_DRAWS
  const IRenderablePrimitive* curPrimitive = 0;
#endif

  ////Debug code
  //for (int i = numBatches; --i > 0;)
  //{
  //  unsigned int prevSortId = pBatches[i-1]->pMaterial->GetSortId();	
  //  Batch &batch = *pBatches[i];
  //  unsigned int sortId = batch.GetSortId();

  //  if (prevSortId > 0 && sortId > 0 && (sortId == prevSortId) != (batch.pMaterial->Compare(*pBatches[i-1]->pMaterial) == 0))
  //  {
  //    batch.pMaterial->MarkMaterialUpdated();
  //    sortId = batch.GetSortId();
  //  }
  //}

  Batch** const pBound = pBatches + numBatches;
  switch( OcclusionQueries::GetUseMode() )
  {
  case OcclusionQueries::QUM_NONE:
    s_batchChunk.Reset();

    do {
      Batch* const pBatch = *pBatches;
#ifdef COUNT_DRAWS
      if(curPrimitive != pBatch->pPrimitive)
        curPrimitive = pBatch->pPrimitive;
      else
        if( curSortId == pBatch->pMaterial->GetSortId() )
          g_NumNewInstances.AddValue(1);
#endif
      const UINT sortId = pBatch->GetSortId();

      if( (sortId != curSortId) || EqualIDs(sortId, 0) )
      {
        s_batchChunk.Finish(pBatches);
        s_batchChunk.NewMaterial(pBatches);
        curSortId = sortId;
      }
      else
        s_batchChunk.AddBatch(pBatch);
    } while(++pBatches != pBound);

    s_batchChunk.Finish(pBatches);
    SmartRenderer::DisableHardwareInstancing();
    break;
  case OcclusionQueries::QUM_CHECK:
    do RenderBatch<OcclusionQueries::QUM_CHECK>(**pBatches, curSortId);
    while(++pBatches != pBound);
    break;
  case OcclusionQueries::QUM_ISSUE:
    do RenderBatch<OcclusionQueries::QUM_ISSUE>(**pBatches, curSortId);
    while(++pBatches != pBound);
    break;
  case OcclusionQueries::QUM_CHECK_AND_ISSUE:
    do RenderBatch<OcclusionQueries::QUM_CHECK_AND_ISSUE>(**pBatches, curSortId);
    while(++pBatches != pBound);
    break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::RenderBatchesList(Batch *pBatch)
{
  unsigned int curSortId = 0;

  bool const renderToShadow = (GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERTOSHADOW);
	for (; pBatch; pBatch = pBatch->pNextBatch)
	{
		// when rendering to shadow, skip non-casters
		if(renderToShadow && (pBatch->pMaterial->GetMaterialFlags() & NDb::MATERIALFLAGS_SHADOWCASTER) == 0)
			continue;

    const UINT sortId = pBatch->GetSortId();

    if( (sortId != curSortId) || (sortId == 0) )
    {
      pBatch->Prepare();
      curSortId = sortId;
    }

		pBatch->Draw();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::Render_SpecialTransparency( int priority ) const
{
  if ( IsEmpty(priority) )
    return;

  int numBatches;
  Batch **pBatches = sorter.Sort<CompareFarToNear>( priorities[priority].numBatches, priorities[priority].pBatchList, numBatches );

  for (int i = 0; i < numBatches; ++i)
  {
    Batch& batch = *pBatches[i];

    GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 1);
    GetStatesManager()->SetStateDirect(D3DRS_COLORWRITEENABLE, 0x00); // disable back buffer
    GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERSHAPEONLY;

    batch.Prepare();
    batch.Draw();

    GetStatesManager()->SetStateDirect(D3DRS_ZWRITEENABLE, 0);
    GetStatesManager()->SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption
    GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERNORMAL;

    BasicMaterial* pBasicMaterial = dynamic_cast<BasicMaterial*>(batch.pMaterial);
    NI_ASSERT(pBasicMaterial, "Only BasicMaterial batches allowed in this queue");
    pBasicMaterial->PrepareRenderer_SpecialTransparency();
    batch.pPrimitive->Draw();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ProcessParticleBatches(Batch** _pSortedArray, UINT _numSortedBatches)
{
  NI_PROFILE_FUNCTION

  IParticlesManager* const pManager = GetParticlesManager();
  pManager->Clear();

  Batch** const bound = _pSortedArray + _numSortedBatches;
  bool lastBatchWasPFX = false;
  for(Batch** ppBatch = _pSortedArray; ppBatch < bound; ++ppBatch)
  {
    Batch* const pBatch = *ppBatch;
    if(pBatch->pMaterial->GetDBMaterial()->GetObjectTypeID() == NDb::ParticleFXMaterial::typeId)
    //if( 0 != dynamic_cast<const ParticleFX*>(pBatch->pOwner) )
    {
      pManager->AddBatch(pBatch);
      lastBatchWasPFX = true;
    }
    else if(lastBatchWasPFX)
    {
      pManager->FinalizeBatch();
      lastBatchWasPFX = false;
    }
  }

  if(lastBatchWasPFX)
    pManager->FinalizeBatch();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Issue occlusion queries for objects that are marked invisible
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void IssueQueriesInvisible(Batch* _pBatchList)
{
  if( s_queryUP )
  {
    BBEffectUP effect;
    effect.Begin();

    for(Batch *pBatch = _pBatchList; pBatch; pBatch = pBatch->pNextBatch)
      if(pBatch->dontDraw)
        pBatch->IssueQueryUP();

    effect.End();
  }
  else
  {
    BBEffect effect;
    effect.Begin();
    CubeRenderer::Bind();

    for(Batch *pBatch = _pBatchList; pBatch; pBatch = pBatch->pNextBatch)
      if(pBatch->dontDraw)
        pBatch->IssueQuery();

    effect.End();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::Render( int priority ) const
{
  NI_PROFILE_FUNCTION

  const int numBatches = priorities[priority].numBatches;
  if(!numBatches)
		return;

  s_renderingShadow = GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERTOSHADOW &&
                      0 != NGlobal::GetVar("shadowNew").GetInt64();

  Batch* const pBatchList = priorities[priority].pBatchList;
                           
  if( OcclusionQueries::GetUseMode() == OcclusionQueries::QUM_ISSUE )
    IssueQueriesInvisible(pBatchList);
  else
  {
    int numSortedBatches;
    Batch **pSortedArray = priorities[priority].bSort ? sorter.Sort<CompareFarToNear>(numBatches, pBatchList, numSortedBatches)
                                                      : sorter.Sort<CompareSortId>(numBatches, pBatchList, numSortedBatches);
    if(priority == NDb::MATERIALPRIORITY_TRANSPARENT && GetRuntimePins().NewParticlesValue == NDb::BOOLPIN_TRUE)
      ProcessParticleBatches(pSortedArray, numSortedBatches);

    RenderBatchesPtrArray( numSortedBatches, pSortedArray );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::Render(int beginPriority, int endPriority) const
{
	ASSERT( 0 <= beginPriority && beginPriority < endPriority && endPriority <= NDb::MATERIALPRIORITY_COUNT );

	for (int priority = beginPriority; priority < endPriority; ++priority)
		Render(priority);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class CMP_POLICY>
Batch** BatchQueueSorter::Sort(int numBatches, Batch *pList, int &numBatchesOut)
{
	batchPtrs.resize(0);
	batchPtrs.reserve(numBatches);

	bool const isntRenderToShadow = (GetRuntimePins().RenderModeValue != NDb::RENDERMODEPIN_RENDERTOSHADOW);
  Batch *pBatch = pList;
  {
    NI_PROFILE_BLOCK( "Batches List to vector" );
    while ( pBatch )
    {
#ifdef _CUSTOM_DEBUG // Debug break
      {
        BaseMaterial* const pMaterial = pBatch->pMaterial;

        if( Batch * const pNextBatch = pBatch->pNextBatch )
          if( pBatch->pPrimitive == pNextBatch->pPrimitive )
            if( pBatch->pOwner && pNextBatch->pOwner )
              if( pBatch->pOwner->GetDBID() && pNextBatch->pOwner->GetDBID() )
                if( pBatch->pOwner->GetDBID()->GetFileName() == pNextBatch->pOwner->GetDBID()->GetFileName() )
                  if( !pMaterial->Compare(*pNextBatch->pMaterial) )
                  {
                    int equal = true;
                    equal;
                  }

                  if( NDb::BOOLEANPIN_PRESENT == pMaterial->GetSkeletalMeshPin() &&
                    NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH != pMaterial->GetLightingPin() &&
                    !(NDb::MATERIALFLAGS_SHADOWCASTER & pMaterial->GetMaterialFlags()) )

                  {
                    const string &name = pBatch->pOwner->GetDBID()->GetFileName();
                    name;
                  }
      }
#endif // _CUSTOM_DEBUG

      // skip empty batches AND when rendering to shadow, skip non-casters
      if( simpleCopy || pBatch->pPrimitive && 
         (isntRenderToShadow || (pBatch->pMaterial->GetMaterialFlags() & NDb::MATERIALFLAGS_SHADOWCASTER)) )
      {
        CMP_POLICY::BatchProcess(*pBatch);  // Process batch
        batchPtrs.push_back( pBatch );      // Add batch
      }

      pBatch = pBatch->pNextBatch;
    }
  }

	// stable sort is expected, don't change to qsort [6/22/2010 smirnov]
  if(!simpleCopy)
	  insertSort<Batch*, CMP_POLICY>(batchPtrs.begin(), batchPtrs.size());
	numBatchesOut = batchPtrs.size();

	return batchPtrs.begin();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BatchQueue::DropMaterialSwitchCounter() { s_materialSwitchCounter = 0; }
int  BatchQueue::GetMaterialSwitchCounter() { return s_materialSwitchCounter; }

}

