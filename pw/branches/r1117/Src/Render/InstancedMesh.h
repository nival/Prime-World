#pragma once

#include "StaticMesh.h"

namespace Render
{

class InstancedMeshGeometry;
class InstancingMaterial;

__declspec(align(16))
class InstancedMesh : public StaticMeshBase
{
	REPLACE_DEFAULT_NEW_DELETE(InstancedMesh);
	ScopedPtr<BasicMaterial>  pMaterial;
	InstancedMeshGeometry         *pGeometry;

public:	
	void Initialize( const NDb::DBStaticSceneComponent* pDBMeshResource );

	virtual void RenderToQueue( Render::BatchQueue &q );

  OcclusionQueries* GetQueries() const { return 0; }
	virtual void ForAllMaterials(Render::IMaterialProcessor &proc);

	virtual bool IsInstanced() const { return true; }
};


}