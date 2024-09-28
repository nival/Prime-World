#pragma once

#include "../System/Ring.h"
#include "SHCoeffs.h"
#include "batch.h"
//#include "DxIntrusivePtr.h"
//#include "dxutils.h"

struct H6GeometryFileHeader;

namespace Render
{

class InstancedMeshGeometry;
class InstancedPrimManager;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct InstanceInfo
{
	Matrix43           worldMatrix;
	SHShaderConstants  shConstants;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InstancedPrimitive : public IRenderablePrimitive
{
public:
	InstancedPrimitive(InstancedMeshGeometry &geo);
	~InstancedPrimitive() 
	{ 
		Ring::safeRemove(this);
    ManRing::safeRemove(this);
	}

	InstanceInfo &FillNextInstance();

	bool IsFresh() const { return numInstances == 1; }
	bool IsFinished() const;
	int  GetNumInstances() const { return numInstances; }

	bool IsInManager() const { return materialId == IN_MANAGER_MARKER; }

	bool IsValid() const { return pInstanceData; }

private:
	enum { IN_MANAGER_MARKER = -2 };

	InstancedMeshGeometry *geometry;
	
	seDECLARE_RING(InstancedPrimitive, ringPart, Ring);
  seDECLARE_RING(InstancedPrimitive, manRingPart, ManRing);

	// Material Id primitive is used for
	int materialId;

	// 
	int                       sequenceIndex;
	int                       numInstances;
	ScopedArray<InstanceInfo> pInstanceData;

	// Should be called from material
	void SetupConstants(int startConstant) const;

	virtual void Bind() const;
	virtual void Draw() const;
  virtual GeometryBuffers  GetBuffers() const;
  virtual GeometryStatistics GetStats() const;

  friend class InstancedPrimManager;
	friend class InstancedMeshGeometry;
  friend class InstancedMesh;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InstancedPrimManager : public Singleton4DLL<InstancedPrimManager>
{
public:
  ~InstancedPrimManager();
  InstancedPrimitive *AllocatePrimitive(InstancedMeshGeometry &geo);
  void FreeAllPrimitives();

private:
  InstancedPrimitive::ManRing freePrims;
  InstancedPrimitive::ManRing usedPrims;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class InstancedMeshGeometry
{
public: 
	InstancedMeshGeometry(const H6GeometryFileHeader* pH6GeometryFileHeader, const nstl::string& filename );
  ~InstancedMeshGeometry();

	void Bind() const;
	void Draw(InstancedPrimitive *pP);

	int GetMaxInstances() const { return s_maxInstances; }

	InstancedPrimitive * RetrievePrimitive(BatchQueue &q, int materialSortId);

	void PrintStatistics(const char *name) const;

	void Swap(InstancedMeshGeometry *pMesh);

private:
  void CreateBuffersHWI(char const *pVtxData, unsigned int const *pIdxData, UINT originalVBSize);

	int                    numVertices;
	int                    numPrimitives;
	int                    vertexStride;
	DXVertexDeclarationRef pDeclaration;
	DXVertexBufferRef      pVB;
	DXIndexBufferRef       pIB;

  // Current primitives for all batches
  InstancedPrimitive::Ring currentPrimitives[BatchQueue::INDEX_COUNT];

  static const size_t s_maxInstances = MAX_INSTANCES_COUNT;

	friend class InstancedPrimitive;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool InstancedPrimitive::IsFinished() const { return numInstances == geometry->GetMaxInstances(); }

}