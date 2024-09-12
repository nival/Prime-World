#include "stdafx.h"

#include "../System/InlineProfiler.h"

#include "../MeshConverter/MeshHeader.h"
#include "smartrenderer.h"
#include "InstancedMeshResource.h"
#include <MemoryLib/UserMessage.h>

static bool s_newShadows = false;
REGISTER_DEV_VAR("shadowNew", s_newShadows, STORAGE_NONE)

DECLARE_NULL_RENDER_FLAG

SINGLETON4DLL_DEF(Render::InstancedPrimManager);

#ifndef _SHIPPING
static NDebug::DebugVar<int> s_numInstances("numInstances", "", true);
static NDebug::DebugVar<int> s_numInstDIPs("numInstDIPs", "", true);
#endif


namespace Render
{


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedPrimitive::InstancedPrimitive(InstancedMeshGeometry &geo)
	: geometry(&geo)
	, numInstances(0)
	, pInstanceData(new InstanceInfo[MAX_INSTANCES_COUNT])
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstanceInfo &InstancedPrimitive::FillNextInstance()
{
	NI_ASSERT(!IsFinished(), "No more instances availdable. Should be checked before");
  NI_ASSERT(pInstanceData != NULL, "Instance data array is broken");
	return pInstanceData[numInstances++];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedPrimitive::SetupConstants(int startConstant) const
{
  if(s_newShadows && GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERTOSHADOW)
  {
    Matrix43* const pMatrices = (Matrix43*)_malloca( numInstances * sizeof(Matrix43) );
    for(int i = 0; i < numInstances; ++i)
      pMatrices[i] = pInstanceData[i].worldMatrix;

    GetRenderer()->SetVertexShaderConstants(startConstant, numInstances * sizeof(Matrix43) / 16, pMatrices);
    _freea( pMatrices );
  }
  else
	  GetRenderer()->SetVertexShaderConstants(startConstant, numInstances * sizeof(InstanceInfo) / 16, Get(pInstanceData));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedPrimitive::Bind() const 
{ 
	geometry->Bind(); 
	SetupConstants(INSTANCE_DATA);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedPrimitive::Draw() const 
{ 
	// Draw
	geometry->Draw( const_cast<InstancedPrimitive*>(this) ); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeometryBuffers InstancedPrimitive::GetBuffers() const
{ 
  GeometryBuffers result = { { Get(geometry->pVB), 0 }, Get(geometry->pIB) };
  return result; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GeometryStatistics InstancedPrimitive::GetStats() const
{ 
  return GeometryStatistics(geometry->numPrimitives, geometry->numVertices); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedPrimManager::~InstancedPrimManager()
{
  // delete primitives
  ring::DeleteEraser<InstancedPrimitive> e;
  ring::ForAll(freePrims, e);
  ring::ForAll(usedPrims, e);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedPrimitive *InstancedPrimManager::AllocatePrimitive(InstancedMeshGeometry &geo)
{
  InstancedPrimitive *pP = NULL;

  if (!freePrims.empty())
  {
    pP = freePrims.first();
    NI_ASSERT(pP->IsValid(), "Invalid primitive! Related to NUM_TASK bug");

    pP->numInstances = 0;
    pP->geometry = &geo;
    freePrims.remove(pP);
  }
  else
  {
    pP = new InstancedPrimitive(geo);
  }

  usedPrims.addFirst(pP);
  return pP;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedPrimManager::FreeAllPrimitives()
{
  NI_PROFILE_FUNCTION

  for (ring::Range<InstancedPrimitive::ManRing> it(usedPrims); it;)
  {
    InstancedPrimitive *pP = &(*it);
    ++it;
    InstancedPrimitive::Ring::safeRemove(pP);
    InstancedPrimitive::ManRing::safeRemove(pP);
    freePrims.addFirst(pP);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedMeshGeometry::InstancedMeshGeometry( const H6GeometryFileHeader* pH6GeometryFileHeader, const nstl::string& filename )
{
	UINT originalVBSize = pH6GeometryFileHeader->commonVertexBufferSizeInBytes;

	// One fragment
	const H6FragmentHeader &fragment = pH6GeometryFileHeader->fragments[0];
	numVertices   = fragment.numVertices;
	numPrimitives = fragment.primitiveCount;
	vertexStride  = fragment.vertexStrideSizeInBytes;

	// Checking
	NI_DATA_ASSERT(pH6GeometryFileHeader->materialCount == 1 && pH6GeometryFileHeader->fragmentCount == 1, 
		NStr::StrFmt( "Instanced mesh should have only one material & primitive. The rest will be ignored. %s", filename.c_str() ) );

	NI_DATA_ASSERT(fragment.minIndex == 0 && fragment.baseVertexIndex == 0 && fragment.streamOffset == 0, 
		NStr::StrFmt( "Instanced mesh fragment has strange indices. %s", filename.c_str() ) );

	NI_ASSERT(int(pH6GeometryFileHeader->commonIndexBufferSizeInBytes) == numPrimitives * 3 * 4 ||
		int(pH6GeometryFileHeader->commonIndexBufferSizeInBytes) == 2 * numPrimitives * 3 * 4, // unfortunately hidden indices will be cut off during instancing [12/1/2010 paul.smirnov]
		NStr::StrFmt( "Invalid size of index buffer. %s", filename.c_str() ) );

  if(RENDER_DISABLED)
    return;

	// Make vertex declaration
	VertexFormatDescriptor formatDescriptor;
	formatDescriptor.AssignVertexElements( fragment.vertexElementDescriptor[0], fragment.vertexElementDescriptor.size() );
	formatDescriptor.AddVertexElement(VertexElementDescriptor(1, 0, VERTEXELEMENTTYPE_SHORT2, VERETEXELEMENTUSAGE_BLENDINDICES, 0));
	pDeclaration = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);

	const char*   pVBSrcData = (const char*)pH6GeometryFileHeader + pH6GeometryFileHeader->vbOffset;
	unsigned int* pIBSrcData = (unsigned int*)(pVBSrcData + pH6GeometryFileHeader->commonVertexBufferSizeInBytes);
	
	// Create buffers
  CreateBuffersHWI(pVBSrcData, pIBSrcData, originalVBSize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedMeshGeometry::~InstancedMeshGeometry()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMeshGeometry::CreateBuffersHWI(char const *pVtxData, unsigned int const *pIdxData, UINT originalVBSize)
{
	// Create & fill vertex buffer
	for(int i = 0; i < 40 && 0 == (pVB = CreateVB(originalVBSize, RENDER_POOL_MANAGED)); ++i)
    Sleep(200);

  if(!pVB)
    UserMessage::ShowMessageAndTerminate(EXCEPTION_BREAKPOINT, "Can't allocate DX resources");

  if( char *pBuff = LockVB<char>(Get(pVB), 0) )
	{
		memcpy(pBuff, pVtxData, originalVBSize);
		pVB->Unlock();
	}

	// Create & fill index buffer
	const UINT dataSize = numPrimitives * 3 * sizeof(UINT);
	pIB = CreateIB(dataSize, RENDER_POOL_MANAGED);
	{
		if( UINT* const pBuff = LockIB(Get(pIB), 0) )
    {
			memcpy(pBuff, pIdxData, dataSize);
      pIB->Unlock();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMeshGeometry::PrintStatistics(const char *name) const
{
	DebugTrace("%s", name);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMeshGeometry::Swap(InstancedMeshGeometry *pMesh)
{
	swap(numVertices, pMesh->numVertices);
	swap(numPrimitives, pMesh->numPrimitives);
	swap(vertexStride, pMesh->vertexStride);

	swap(pDeclaration, pMesh->pDeclaration);
	swap(pVB, pMesh->pVB);
	swap(pIB, pMesh->pIB);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMeshGeometry::Bind() const
{
	SmartRenderer::BindVertexDeclarationRaw(Get(pDeclaration));
	SmartRenderer::BindIndexBuffer(pIB);
	SmartRenderer::BindVertexBufferRaw(0, Get(pVB), vertexStride);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMeshGeometry::Draw(InstancedPrimitive *pP)
{
	NI_ASSERT(pP, "Internal error!");
#ifndef _SHIPPING
  s_numInstances.AddValue(pP->numInstances);
  s_numInstDIPs.AddValue(1);
#endif

  DipDescriptor dd;
	dd.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
	dd.baseVertexIndex = 0;
	dd.startIndex      = 0;
  dd.numVertices     = numVertices;
  dd.primitiveCount  = numPrimitives;
  SmartRenderer::EnableHardwareInstancing(pP->numInstances);
  SmartRenderer::BindInstanceVB();

	SmartRenderer::DrawIndexedPrimitive(dd);

  SmartRenderer::DisableHardwareInstancing();

  // calculate memory needs
  if ( !pP->IsInManager() )
  {
    pP->materialId = InstancedPrimitive::IN_MANAGER_MARKER;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InstancedPrimitive* InstancedMeshGeometry::RetrievePrimitive(BatchQueue &q, int materialSortId)
{
	// Search for the primitive with the same material
	int sequenceIndex = -1;
  InstancedPrimitive::Ring& currentRing = currentPrimitives[q.GetIndex()];
	for (ring::Range<InstancedPrimitive::Ring> it(currentRing); it;)
	{
		InstancedPrimitive *pP = &(*it);
		++it;

		if (pP->materialId == materialSortId)
		{
			if (!pP->IsFinished())
			{
				NI_ASSERT(pP->IsValid(), "Invalid primitive! Related to NUM_TASK bug");
				return pP;
			}
			else
			{
				// Save sequence index 
				sequenceIndex = pP->sequenceIndex;

				// Remove from ring and stop
				InstancedPrimitive::Ring::safeRemove(pP); 
				break;
			}
		}
	}

	// No primitive found. Requesting new one.
  InstancedPrimitive *pP = InstancedPrimManager::Get()->AllocatePrimitive(*this);
	NI_ASSERT(pP->IsValid(), "Invalid primitive! Related to NUM_TASK bug. New assert.");
	pP->materialId    = materialSortId;
	pP->sequenceIndex = sequenceIndex + 1;
	currentRing.addFirst(pP);
	NI_ASSERT(pP->IsValid(), "Invalid primitive! Related to NUM_TASK bug");

	return pP;
}

}