#pragma once

#include "RenderComponent.h"
#include "MeshResource.h"
#include "MaterialSpec.h"
#include "VertexColorStream.h"

#include "renderresourcemanager.h"
#include "MaterialResourceInterface.h"

#include "DBRenderResources.h"
#include "../System/Crc32Checksum.h"
#include "../Scene/DBScene.h"

extern uint StaticMeshInstanceCounter;

namespace NScene
{
  class LightingScene;
}

namespace Render
{

struct SceneConstants;

__declspec(align(16))
class StaticMeshBase : public RenderComponent
{
protected:
	Matrix43  worldMatrix;

public:
	virtual MeshVertexColors const *GetVertexColors() const { return 0; }
	virtual void CalculateLighting(SceneConstants const &/*sceneConst*/) {}
  virtual void CalculateLightingEx(SceneConstants const &, NDb::ELightEnvironment const) {}

	virtual void ForAllMaterials(Render::IMaterialProcessor &proc) = 0;

	virtual bool IsInstanced() const = 0;

	void SetWorldMatrix(const Matrix43& transform);
	void SetWorldMatrix(const SHMatrix& transform);
	const Matrix43& GetWorldMatrix() const { return worldMatrix; }

  virtual void AddGeometryCRC(Crc32Checksum &crc) {}
};

__declspec(align(16))
class StaticMesh : public StaticMeshBase
{
	REPLACE_DEFAULT_NEW_DELETE(StaticMesh);
	
  void CreateStubMesh();
  void InitializeDynamicLighting();
  void FindLights();
	
protected:
	typedef ScopedPtr<BaseMaterial> MaterialPtr;
	
	AABB      localAABB;

	const MeshGeometry           *pMeshGeom;
	StaticArray<MaterialPtr, 16> materials;
	int                          materialsCount;
	AutoPtr<MeshVertexColors>    pVertexColors;
  
  LightsData lightsData;
  unsigned long lightsFlags;
	
  mutable DeviceLostWrapper<OcclusionQueries> queries;

#ifdef _DEBUG
	unsigned int  triangleCount;
#endif

  void DoCalculateLighting(const SceneConstants& sceneConst, const DXVertexBufferRef& vb, const NDb::ELightEnvironment selector) const;

public:
	StaticMesh();
  virtual ~StaticMesh();

	void Initialize( const Matrix43& _worldMatrix, const NDb::StaticMesh* pDBMeshResource );
	bool Initialize( const Matrix43& _worldMatrix, const NDb::DBStaticSceneComponent* pDBMeshResource, bool appendColorStream = false );
	void Initialize( const Matrix43& _worldMatrix, const MeshGeometry* geom, vector<Render::BaseMaterial*> materials );

	void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;

	virtual void RenderToQueue( BatchQueue& queue );

  OcclusionQueries* GetQueries() const;
  virtual bool FillOBB(CVec3 (&_vertices)[8]) const;
  virtual const AABB& GetLocalAABB() const  { return localAABB; }
  virtual const AABB& GetAABB(bool *_pIsLocal) const { *_pIsLocal = true; return localAABB; }

  static void SetQueryTriBound(UINT _bound);

	void SetMaterial( int nElementIdx, BaseMaterial* _pMaterial );
	int GetElementsCount() const { ASSERT( pMeshGeom ); return pMeshGeom->primitives.size(); }
	
  virtual void ForAllMaterials(Render::IMaterialProcessor &proc);

  virtual MeshVertexColors const *GetVertexColors() const { return Get(pVertexColors); }
  void SetVertexColors(AutoPtr<MeshVertexColors> pColors, bool fake);

  virtual void CalculateLighting(SceneConstants const &sceneConst);
  virtual void CalculateLightingEx(SceneConstants const &sceneConst, NDb::ELightEnvironment const selector);

	virtual bool IsInstanced() const { return false; }

#ifdef _DEBUG
	unsigned int GetTriangleCount() const { return triangleCount; }
#else
  unsigned int GetTriangleCount() const { ASSERT(pMeshGeom); return pMeshGeom->triangleCount; }
#endif

  virtual void AddGeometryCRC(Crc32Checksum &crc);
};

}//namespace Render
