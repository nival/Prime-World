#include "stdafx.h"
#include "InstancedMeshResource.h"
#include "MaterialSpec.h"
#include "InstancedMesh.h"

namespace Render
{

DECLARE_INSTANCE_COUNTER(InstancedMesh);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMesh::Initialize( const NDb::DBStaticSceneComponent* pDBMeshResource )
{
	Identity(&worldMatrix); 

	NI_ASSERT(pDBMeshResource->materialsReferences.size() == 1, 
    NStr::StrFmt("Instancing is supported only for a single material mesh (found %i materials). This should be checked earlier. See '%s'",
    pDBMeshResource->materialsReferences.size(), GetFormattedDbId(pDBMeshResource->GetDBID()).c_str()));

	pGeometry = Render::RenderResourceManager::LoadInstancedMeshGeometry( pDBMeshResource->geometryFileName );
	if (pGeometry == 0)
	{
		return;
	}

	// Create material
	const NDb::Material* pDBMat = pDBMeshResource->materialsReferences[0];
 	NI_ASSERT(pDBMat->GetObjectTypeID() == NDb::BasicMaterial::typeId, 
    NStr::StrFmt("Instancing is supported only for BasicMaterial (found %s). This should be checked earlier. See '%s'", 
    pDBMat->GetObjectTypeName(), GetFormattedDbId(pDBMeshResource->GetDBID()).c_str())); 
	Reset(pMaterial, static_cast<BasicMaterial*>(Render::CreateRenderMaterial( pDBMat )));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMesh::RenderToQueue( Render::BatchQueue &q )
{
	InstancedPrimitive *pP = pGeometry->RetrievePrimitive(q, pMaterial->GetSortId());
  NI_VERIFY(pP != NULL, "InstancedPrimitive should be valid", return; );
  NI_VERIFY(pP->pInstanceData != NULL, "InstancedData is broken", return; );  
	InstanceInfo &info = pP->FillNextInstance();
	info.worldMatrix = worldMatrix;
	NI_ASSERT(q.GetCurrentSHShaderConstants(), "Current shader constants should present!");
	info.shConstants = *q.GetCurrentSHShaderConstants();

	// Here I'll control data that I'll put to primitive
	if (pP->IsFresh())
	{
		int priority = pMaterial->GetPriority();
		q.Push( priority, this, pP, 0, Get(pMaterial) );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InstancedMesh::ForAllMaterials(Render::IMaterialProcessor &proc)
{
	proc(*pMaterial);
}

}
