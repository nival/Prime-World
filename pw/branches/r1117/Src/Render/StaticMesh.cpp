#include "stdafx.h"
#include "light.h"
#include "StaticMesh.h"
#include "batch.h"
#include "ConvexVolume.h"
#include "GlobalMasks.h"
#include "SHCoeffs.h"
#include "sceneconstants.h"

static NDebug::DebugVar<int> render_SM_Render( "Stat_Render", "PerfCnt", true );

namespace Render
{

namespace
{

DECLARE_NULL_RENDER_FLAG

inline bool VertexHasColors(DXVertexDeclarationRef decl)
{
  if(RENDER_DISABLED)
    return false;

  D3DVERTEXELEMENT9  elements[MAXD3DDECLLENGTH];
  unsigned int n;
  decl->GetDeclaration(elements, &n);

  for (unsigned int i = 0; i < n; ++i)
  {
    if (elements[i].Usage == D3DDECLUSAGE_COLOR)
    {
      return true;
    }
  }

  return false;
}

}

DECLARE_INSTANCE_COUNTER(StaticMesh);

static UINT s_QueryTriBound = 1000;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticMesh::StaticMesh()
: pMeshGeom( 0 )
, materialsCount( 0 )
, lightsFlags( 0 )
{
	Identity(&worldMatrix); 
#ifdef _DEBUG
	triangleCount = 0; 
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticMesh::~StaticMesh()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::CreateStubMesh()
{
	NDb::Ptr<NDb::DBStaticSceneComponent> pDefaultStaticMesh = NDb::Get<NDb::DBStaticSceneComponent>( NDb::DBID( "/Tech/Default/Default.STSC" ) );
  NI_ASSERT( !pMeshGeom, "" );
	pMeshGeom = Render::RenderResourceManager::LoadStaticMeshGeometry( pDefaultStaticMesh->geometryFileName, false );

	Reset(materials[0], static_cast<BaseMaterial*>( Render::CreateRenderMaterial( pDefaultStaticMesh->materialsReferences[0] ) ) );
	materialsCount = 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::InitializeDynamicLighting()
{
  unsigned numMaterials = materials.capacity();
  NI_ASSERT(numMaterials <= 8 * sizeof(lightsFlags), "There's not enough bits to store all flags");
  
  lightsFlags = 0;
  for (unsigned i = 0; i < numMaterials; i++)
  {
    MaterialPtr& pMaterial = materials[i];
    if (pMaterial)
    {
      BasicMaterial* pBasicMaterial = dynamic_cast<BasicMaterial*>(Get(pMaterial));
      if (pBasicMaterial && pBasicMaterial->GetLightingPin() == NDb::LIGHTINGPIN_LIGHTINGDYNAMIC)
        lightsFlags |= (1 << i);
    }
  }

  if (lightsFlags != 0)
    lightsData.Initialize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// used in simple StaticSceneComponent from ... [2/11/2010 smirnov]
void StaticMesh::Initialize( const Matrix43& _worldMatrix, const NDb::StaticMesh* pDBMeshResource )
{
	worldMatrix = _worldMatrix;

	localAABB.Set( pDBMeshResource->aabb );

  NI_ASSERT( !pMeshGeom, "" );
	pMeshGeom = Render::RenderResourceManager::LoadStaticMeshGeometry( pDBMeshResource->geometryFileName, false );
	if(pMeshGeom == 0)
	{
		CreateStubMesh();
		return;
	}

	// Allocate elements
	const int primitiveCount = pMeshGeom->primitives.size();

	materialsCount = pDBMeshResource->materialsReferences.size();
	NI_VERIFY( primitiveCount == materialsCount, "wrong number of materials", CreateStubMesh(); return; );
	for ( int i = 0; i < primitiveCount; ++i )
	{
		const NDb::Material* pMatType = pDBMeshResource->materialsReferences[i];
		NI_VERIFY(pMatType, "no material set for fragment #", continue; );
		BaseMaterial* pMatInstance = static_cast<BaseMaterial*>( Render::CreateRenderMaterial( pMatType ) );
		ASSERT(pMatInstance);
		pMatInstance->SetSkeletalMeshPin( NDb::BOOLEANPIN_NONE );
    
    pMatInstance->SetMultiplyVertexColorPin( VertexHasColors(pMeshGeom->primitives[i]->GetVertexDeclaration()) ?
                                             NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
    
    Reset(materials[i], pMatInstance);
	}
  InitializeDynamicLighting();
#ifdef _DEBUG
	triangleCount = pMeshGeom->triangleCount;
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// used in EaselPaintLayerSceneComponent [2/11/2010 smirnov]
void StaticMesh::Initialize( const Matrix43& _worldMatrix, const MeshGeometry* geom, vector<Render::BaseMaterial*> materials_ )
{
  NI_ASSERT( !pMeshGeom, "" );

	worldMatrix = _worldMatrix;
	pMeshGeom   = geom;

	localAABB.center   = CVec3( 0.0f, 0.0f, 0.0f );
	localAABB.halfSize = CVec3( 1.0f, 1.0f, 1.0f );

	// Allocate elements
	const int primitiveCount = pMeshGeom->primitives.size();

	materialsCount = materials_.size();
	NI_ASSERT( primitiveCount == materialsCount , "wrong number of materials" );
	for ( int i = 0; i < primitiveCount; ++i )
		Reset(materials[i], materials_[i]);
  InitializeDynamicLighting();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// used in normal StaticSceneComponent from ... [2/11/2010 smirnov]
// returns true if mesh was successfully loaded (otherwise stub mesh was created)
bool StaticMesh::Initialize( const Matrix43& _worldMatrix, const NDb::DBStaticSceneComponent* pDBMeshResource, bool appendColorStream )
{
	worldMatrix = _worldMatrix;

	localAABB.Set( pDBMeshResource->aabb );

  NI_ASSERT( !pMeshGeom, "" );
	pMeshGeom = Render::RenderResourceManager::LoadStaticMeshGeometry( pDBMeshResource->geometryFileName, appendColorStream );
	if (pMeshGeom == 0)
	{
		CreateStubMesh();
		return false;
	}

  NI_DATA_VERIFY( pMeshGeom->colorStreamAppended == appendColorStream, 
    NStr::StrFmt("Couldn't append vertex colors to '%s'. See '%s'", pDBMeshResource->geometryFileName, GetFormattedDbId(pDBMeshResource->GetDBID()).c_str()), 
    return false; );

	// Allocate elements
	const int primitiveCount = pMeshGeom->primitives.size();
	materialsCount = pDBMeshResource->materialsReferences.size();
  NI_DATA_VERIFY( primitiveCount == materialsCount,
    NStr::StrFmt( "Number of primitives (%d) and materials (%d) mismatch in '%s'", primitiveCount, materialsCount, NDb::GetFormattedDbId( pDBMeshResource->GetDBID() ).c_str() ),
    CreateStubMesh(); return false; );

  for ( int i = 0; i < materialsCount; ++i )
	{
    Reset(materials[i], 0);
		const NDb::Material* pMatType = pDBMeshResource->materialsReferences[i];
		NI_VERIFY(pMatType, NStr::StrFmt("No material in slot %i in '%s'", i, NDb::GetFormattedDbId(pDBMeshResource->GetDBID()).c_str()), continue);
    BaseMaterial* pMatInstance = static_cast<BaseMaterial*>( Render::CreateRenderMaterial( pMatType ) );
		NI_VERIFY(pMatInstance, NStr::StrFmt("Couldn't create material %i in '%s'", i, NDb::GetFormattedDbId(pDBMeshResource->GetDBID()).c_str()), continue);
		pMatInstance->SetSkeletalMeshPin( NDb::BOOLEANPIN_NONE ); // since assigned to static mesh
    pMatInstance->SetMultiplyVertexColorPin( VertexHasColors(pMeshGeom->primitives[i]->GetVertexDeclaration()) ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
		Reset(materials[i], pMatInstance);
	}
  InitializeDynamicLighting();
#ifdef _DEBUG
	triangleCount = pMeshGeom->triangleCount;
#endif

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::SetVertexColors(AutoPtr<MeshVertexColors> pColors, bool fake)
{
  pVertexColors = pColors;
  if ( fake )
    pVertexColors = AutoPtr<MeshVertexColors>( new MeshVertexColors );
  ASSERT(pMeshGeom);
  pVertexColors->InitializeBuffer(*pMeshGeom, fake);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::SetMaterial( int nElementIdx, BaseMaterial* _pMaterial )
{
	NI_VERIFY( nElementIdx < (int)materialsCount && nElementIdx >= 0, "", return );
  Reset(materials[nElementIdx], _pMaterial);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::RenderToQueue( BatchQueue& queue )
{
  const int primitiveCount = pMeshGeom->primitives.size();
  NI_VERIFY( primitiveCount == materialsCount, "wrong number of materials", return );

  UINT numPointLights = 0;
  if (lightsFlags != 0)
  {
    AABB aabb;
    aabb.Transform(worldMatrix, localAABB);
    numPointLights = lightsData.Fill(aabb);
  }

  for(int i = 0, mask = 1; i < primitiveCount; ++i, mask <<= 1)
  {
    BaseMaterial* const pMaterial = Get(materials[i]);
    if( lightsFlags & mask )
      pMaterial->SetLightingPin( NDb::LightingPin(NDb::LIGHTINGPIN_LIGHTINGDYNAMIC + numPointLights) );

	  queue.Push( pMaterial->GetPriority(), this, pMeshGeom->primitives[i], i, pMaterial );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OcclusionQueries* StaticMesh::GetQueries() const
{
  return GetTriangleCount() > s_QueryTriBound ? &queries : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StaticMesh::FillOBB(CVec3 (&_vertices)[8]) const
{
  if(GetTriangleCount() <= s_QueryTriBound)
    return false;

  RenderComponent::FillOBB(localAABB, worldMatrix, &_vertices[0]);
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::SetQueryTriBound(UINT _bound) { s_QueryTriBound = _bound; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
	RenderComponent::PrepareRendererAfterMaterial( elementNumber );

	// Bind vertex colors
	if (pVertexColors)
		pVertexColors->Bind(elementNumber);

  if(GetRuntimePins().InstancingValue == NDb::BOOLEANPIN_NONE)
  {
    SHMatrix world;
    Copy( &world, worldMatrix );
    GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, world );
  }

  // set lighting parameters
  if(GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERNORMAL)
    if (lightsFlags & (1 << elementNumber))
      lightsData.Setup();

	render_SM_Render.AddValue(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMeshBase::SetWorldMatrix( const Matrix43& transform )
{
	worldMatrix = transform; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMeshBase::SetWorldMatrix( const SHMatrix& transform )
{
	worldMatrix.Set( transform ); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  for (int i = 0; i < materialsCount; ++i)
    proc( *materials[i] );
}

namespace LightingCalculator
{
  struct Vertex
  {
    CVec3 position;
    CVec3 normal;
  };

  struct Context : public NonCopyable
  {
    const Render::SceneConstants& sceneConst;

    unsigned stride;
    unsigned numVertices;
    unsigned materialCount;

    void* geometry;
    Render::Color* colors;

    Render::AABB aabb;

    const Render::HDRColor* matDiffuseColor[16];
    float matLightIntensity[16];

    explicit Context(const Render::SceneConstants& _sceneConst)
      : sceneConst(_sceneConst)
      , stride(0U)
      , numVertices(0U)
      , materialCount(0U)
      , geometry(NULL)
      , colors(NULL)
      , aabb()
    {

    }
  private:
    Context();
  };

  void Calculate(const Context& ctx)
  {

  }
}

void StaticMesh::DoCalculateLighting(const SceneConstants& sceneConst, const DXVertexBufferRef& vb, const NDb::ELightEnvironment selector) const
{
  struct Vertex
  {
    CVec3 position;
    CVec3 normal;
  };

  Render::HDRColor const &ambientColor = sceneConst.ambientColor;

  Render::HDRColor defaultColor(1.f, 1.f, 1.f);
  Render::HDRColor const *matDiffuseColor[16];
  float matLightIntensity[16];

  // extract material light response
  {
    for (int i = 0; i < materialsCount; ++i)
    {
      Material *pMaterial = Get(materials[i]);

      const NDb::Material *pDBMat = pMaterial->GetDBMaterial();
      if (pDBMat->GetObjectTypeID() != NDb::BasicMaterial::typeId)
      {
        matDiffuseColor[i] = &defaultColor;
        matLightIntensity[i] = 1.f;
      }
      else
      {
        const NDb::BasicMaterial *pDBBaseMat = static_cast<const NDb::BasicMaterial*>(pDBMat);
        matDiffuseColor[i] = &pDBBaseMat->diffuseColor;
        matLightIntensity[i] = pDBBaseMat->lightingIntencity;
      }
    }
  }

  // collect lights affecting this object
  AABB aabb;
  aabb.Transform(worldMatrix, localAABB);

  Render::PointLightsCollector clf(selector);

  GetLightsManager()->ForLightsAffectingBBox( aabb, clf );

  NI_ASSERT(pMeshGeom->primitives[0], "No primitives");
  NI_ASSERT(Get(pMeshGeom->primitives[0]->GetVertexBuffer()), "No vertex buffer");

  // calculate total number of vertices
  unsigned int numVertices = 0;
  for (int i = 0; i < pMeshGeom->fragmentCount; ++i)
  {
    numVertices += pMeshGeom->primitives[i]->GetDipDescriptor().numVertices;
  }

  // calculate vertex stride
  D3DVERTEXBUFFER_DESC desc;
  pMeshGeom->primitives[0]->GetVertexBuffer()->GetDesc(&desc);
  unsigned int stride = desc.Size / numVertices;

  NI_ASSERT(stride * numVertices == desc.Size, "Invalid number of vertices");
  NI_ASSERT(stride >= sizeof(Vertex), "Vertex too small to hold required data");

  unsigned char *geovb = LockVB<unsigned char>(Get(pMeshGeom->primitives[0]->GetVertexBuffer()), 0);
  Render::Color *colors = LockVB<Render::Color>(Get(vb), 0);

  for (int i = 0; i < pMeshGeom->fragmentCount; ++i)
  {
    DipDescriptor &dip = pMeshGeom->primitives[i]->GetDipDescriptor();
    int matIdx = pMeshGeom->materialID[i];

    for (unsigned int j = 0; j < dip.numVertices; ++j)
    {
      int idx = dip.baseVertexIndex + dip.minIndex + j;
      Vertex *pV = (Vertex*)(geovb + idx * stride);

      CVec3 pos = Transform(pV->position, worldMatrix);
      CVec3 n = Rotate(pV->normal, worldMatrix);
      Normalize(&n);

      // calculate environment lighting
      HDRColor sceneEnvLight;
      EvaluateLightingBySHShaderConstants(sceneConst.envLighting, n, sceneEnvLight);

      // calculate lighting by point lights
      Render::HDRColor c = Render::HDRColor(0.f, 0.f, 0.f, 1.f);
      for (int j = 0; j < clf.lights.size(); ++j)
      {
        Render::PointLight const &pl = *clf.lights[j];

        CVec3 d = pl.GetLocation() - pos;
        float t = 1.f;

        float l = d.Length();
        if (l > 0.f)
        {
          t = n.Dot(d) * pl.GetAttenuation(l) / l;
          t = Clamp(t, 0.f, 1.f);
        }

        t *= pl.m_diffuseIntensity;

        c.Mad(pl.m_diffuseColor, Render::HDRColor(t,t,t,1.f), c);
      }

      c = ( ambientColor + (sceneEnvLight + c) * matLightIntensity[matIdx] ) * (*matDiffuseColor[matIdx]);

      Render::HDRColor const &minBakedColor = sceneConst.minBakedColor;
      Render::HDRColor const &maxBakedColor = sceneConst.maxBakedColor;
      c.R = Clamp(c.R, minBakedColor.R, Min(255.f, maxBakedColor.R));
      c.G = Clamp(c.G, minBakedColor.G, Min(255.f, maxBakedColor.G));
      c.B = Clamp(c.B, minBakedColor.B, Min(255.f, maxBakedColor.B));

      // adaptive scaling to allow HDR
      float max = Max(c.R, c.G);
      max = ceil(Max(max, c.B));
      float scale = 255.f / max;

      colors[ idx ] = Color(c.R * scale, c.G * scale, c.B * scale, max);
    }
  }

  vb->Unlock();
  pMeshGeom->primitives[0]->GetVertexBuffer()->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::CalculateLighting(SceneConstants const &sceneConst)
{
  CalculateLightingEx(sceneConst, NDb::LIGHTENVIRONMENT_DAY);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::CalculateLightingEx(SceneConstants const &sceneConst, NDb::ELightEnvironment const selector)
{
  if (!pVertexColors)
    return;

  DXVertexBufferRef vb;

  switch (selector)
  {
  case NDb::LIGHTENVIRONMENT_DAY:
    vb = pVertexColors->pVB1;
    break;
  case NDb::LIGHTENVIRONMENT_NIGHT:
    vb = pVertexColors->pVB2;
    break;
  }

  if (!Get(vb))
    return;

  DoCalculateLighting(sceneConst, vb, selector);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::AddGeometryCRC(Crc32Checksum &crc)
{
  if(RENDER_DISABLED)
    return;

  D3DVERTEXBUFFER_DESC desc;
  pMeshGeom->primitives[0]->GetVertexBuffer()->GetDesc(&desc);
  unsigned char *geovb = LockVB<unsigned char>(Get(pMeshGeom->primitives[0]->GetVertexBuffer()), 0);
  crc.Add(geovb, desc.Size);
  pMeshGeom->primitives[0]->GetVertexBuffer()->Unlock();
}

}; // namespace Render
