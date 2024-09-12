#pragma once

#include "MaterialSpec.h"
#include "RenderComponent.h"
#include "renderableprimitive.h"
#include "../System/noncopyable.h"

namespace Render
{

struct SHShaderConstants;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__declspec(align(16))
struct Batch
{
	const RenderComponent      *pOwner;
	unsigned int                elementNumber;
	const IRenderablePrimitive *pPrimitive;
	BaseMaterial               *pMaterial;
	float                       sortValue;
	const SHShaderConstants    *pSHConsts;
	Batch                      *pNextBatch;
  bool                        dontDraw;
  bool                        isInside;

  static void SetWaterLevel(bool _enable, float _level = 0.0f);

	__forceinline unsigned int GetSortId() const { return pMaterial->GetSortId(); }

	void Prepare() const;
	void Draw() const;
  void IssueQueryUP();
  void IssueQuery();
};

class BatchQueueSorter
{
private:
	nstl::vector<Batch*> batchPtrs;
  bool simpleCopy;

public:
	BatchQueueSorter( int maxSize = 512, bool _simpleCopy = false )
  {
    batchPtrs.reserve( maxSize );
    simpleCopy = _simpleCopy;
  }

	template <class CMP_POLICY>
	Batch** Sort(int numBatches, Batch *pList, int &numBatchesOut);
};


_interface IBatchQueueLogger
{
	virtual void operator()(const Batch &batch) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BatchQueue : public NonCopyable
{ 
public:
  struct Priority
  {
    bool   bSort;
    int    numBatches;
    Batch  *pBatchList;
  };

private:
	nstl::vector<Batch>       elements;
	BatchQueueSorter          &sorter;
	Priority                  priorities[NDb::MATERIALPRIORITY_COUNT];
	float                     curSortingValue;
	const SHShaderConstants   *pCurSHConsts;
	int                       index;

  std::auto_ptr<class DXManager>  resourceManager;

	static void RenderBatchesList(Batch *pBatch);
  static void RenderBatchesPtrArray(UINT numBatches, Batch **pBatches);

  void PushInternal( int priority, 
    const RenderComponent *pOwner, const IRenderablePrimitive *pPrimitive, 
    unsigned int elementNumber, BaseMaterial *pMaterial );

public:
	enum Index
	{
		INDEX_MAIN = 0,
		INDEX_SECONDARY,
		INDEX_COUNT,
	};

	BatchQueue( Index index, BatchQueueSorter &_sorter, int maxSize = 4096*16 );
  ~BatchQueue();

  void EnableResourceManagment(bool _enable = true);
  bool OnNextFrame();
  bool ManageResources();

  Priority& GetSubQueue(int priority) { return priorities[priority]; }
	int  GetIndex() const { return index; }
	void SetSorting( int priority, bool bSorting );
	void Clear();
	void SetCurrentSortingValue( float val ) { curSortingValue = val; }
  float GetCurrentSortingValue() const     { return curSortingValue; }
	void SetCurrentSHShaderConstants( const SHShaderConstants *pCurSHConsts_ ) { pCurSHConsts = pCurSHConsts_; }
	void Push( int priority, 
						 const RenderComponent *pOwner, const IRenderablePrimitive *pPrimitive, 
		         unsigned int elementNumber, BaseMaterial *pMaterial );

  void ReplaceMaterial( int beginPriority, int endPriority, BaseMaterial *pMaterial );
  void ReplaceMaterial( int priority, BaseMaterial *pMaterial );
  void ReplaceMaterial( BaseMaterial *pMaterial )
  {
    ReplaceMaterial( 0, NDb::MATERIALPRIORITY_COUNT, pMaterial );
  }

	const SHShaderConstants *GetCurrentSHShaderConstants() const { return pCurSHConsts; }

	static void SetRenderLogger(IBatchQueueLogger *pL);
	static bool IsLoggingActive();

	static void DropMaterialSwitchCounter();
	static int  GetMaterialSwitchCounter();

  bool IsEmpty( int priority ) const { return priorities[priority].numBatches == 0; }

  Batch* GetBatches( int priority ) const { return priorities[priority].pBatchList; }

	void Render( int beginPriority, int endPriority ) const;
	void Render( int priority ) const;
	void Render( ) const
	{
		Render( 0, NDb::MATERIALPRIORITY_COUNT );
	}

  void Render_SpecialTransparency( int priority ) const;
};

}