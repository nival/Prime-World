#include "stdafx.h"
#include "SkeletalMesh.h"
#include "batch.h"
#include "ConvexVolume.h"
#include "../MeshConverter/SkeletalAnimationHeader.h"
#include "SkeletalAnimationBlender.h"
#include "SkeletonReindexResource.h"
#include "renderresourcemanager.h"
#include "SkeletonWrapper.h"
#include "GlobalMasks.h"

static NDebug::DebugVar<int> render_Skel_Update( "Skel_Update", "PerfCnt", true );
static NDebug::DebugVar<int> render_Skel_Render( "Skel_Render", "PerfCnt", true );

namespace
{
  DECLARE_NULL_RENDER_FLAG

#ifndef _SHIPPING
  bool s_NoAnimation = false;
  REGISTER_DEV_VAR("animDisable", s_NoAnimation, STORAGE_NONE);

  bool s_drawSkeletal = true;
  REGISTER_DEV_VAR("draw_skeletons", s_drawSkeletal, STORAGE_NONE);
#else
  enum {
    s_NoAnimation = false,
    s_drawSkeletal = true
  };
#endif

inline bool VertexHasColors(DXVertexDeclarationRef decl)
{
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

namespace Render
{
	DECLARE_INSTANCE_COUNTER(SkeletalMesh);
	void SkeletalMesh::Update(bool bNeedBlenderUpdate)
	{
    if(bNeedBlenderUpdate)
    {
		  pSkeletalAnimationBlender->Sample( pSkeletonWrapper->GetSampledMatrix() );
    }
		pSkeletonWrapper->Update( worldMatrix );

		render_Skel_Update.AddValue(1);
	}

  void SkeletalMesh::RenderToQueue( BatchQueue& queue )
	{
    if(!s_drawSkeletal)
      return;

		render_Skel_Render.AddValue(1);

    UINT numPointLights = 0;
    if (lightsFlags != 0)
      numPointLights = lightsData.Fill(worldAABB);

    for(int slotNumber = 0, mask = 1; slotNumber < maxSlotsCount; ++slotNumber, mask <<= 1)
    {
      SkeletalMeshElement &slot = elementSlots[slotNumber];
      if( slot.IsEmpty() || !slot.IsEnabled() )
        continue;
      BaseMaterial* const pMaterial = slot.pMaterialInstance;
      if( lightsFlags & mask )
        pMaterial->SetLightingPin( NDb::LightingPin(NDb::LIGHTINGPIN_LIGHTINGDYNAMIC + numPointLights) );

      //pMaterial->SetSkeletalMeshPin(s_NoAnimation ? NDb::BOOLEANPIN_NONE : NDb::BOOLEANPIN_PRESENT);

			queue.Push( pMaterial->GetPriority(), this, slot.GetPrimitive(), slotNumber, pMaterial ); 
		}
  }

	void SkeletalMesh::PrepareRendererAfterMaterial( unsigned int slotNumber ) const
	{
		RenderComponent::PrepareRendererAfterMaterial( slotNumber );

		SHMatrix world;
		Copy( &world, worldMatrix );
		Render::GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, world );

    if(!s_NoAnimation)
    {
      NI_ASSERT( !elementSlots[slotNumber].IsEmpty(), "slot is empty!" );
      const unsigned int currentBoneCount = elementSlots[slotNumber].GetFragmentReindex()->size();
      NI_VERIFY( currentBoneCount <= maxBoneCountPerFragment, "bone count exceed the limit", return );
      const Matrix43* matrixArray = pSkeletonWrapper->GetSkinWorldMatrices() + elementSlots[slotNumber].GetMatrixIndex();
      Render::GetRenderer()->SetVertexShaderConstantsMatrix43( BONES, currentBoneCount, matrixArray );
    }

    // set lighting parameters
    if (lightsFlags & (1 << slotNumber))
      lightsData.Setup();
	}

  SkeletalMesh::SkeletalMesh() : pSkeletonWrapper(0), pSkeletalAnimationBlender(0), lightsFlags(0), needLightingSH( false )
	{
		Identity(&worldMatrix);
    localAABB.Init2Empty();
    worldAABB.center.Set(0.0f, 0.0f, 0.0f);
    worldAABB.halfSize.Set(0.5f, 0.5f, 0.5f);
	}

	void SkeletalMesh::Initialize( const Matrix43& _worldMatrix, const nstl::string& skeletonFileName )
	{
		worldMatrix = _worldMatrix;
#ifdef _DEBUG
		skeletonSourceFileName = skeletonFileName;
#endif
		pSkeletonWrapper = new SkeletonWrapper( RenderResourceManager::LoadSkeletonData( skeletonFileName ) );
	}

	void SkeletalMesh::AddSkinPart( const NDb::SkinPartBase* pDBSkinPartResource, unsigned int* pPartIndexes, unsigned int* pPartsCount )
	{
		NI_VERIFY( pDBSkinPartResource, "pDBSkinPartResource is null", return );
		NI_ASSERT( pPartIndexes, "null ptr to pPartIndexes" );
		NI_ASSERT( pPartsCount, "null ptr to pPartsCount" );

		const MeshGeometry* pMeshGeometry = Render::RenderResourceManager::LoadSkeletalMeshGeometry(pDBSkinPartResource->geometryFileName);
		NI_VERIFY( pMeshGeometry, "Cannot create mesh geometry", return );

		const int primitiveCount = pMeshGeometry->primitives.size();
		NI_ASSERT( pMeshGeometry->fragmentCount < maxSlotsCount , "execeeded the limit of elements per skinpart" );
		NI_ASSERT( pMeshGeometry->materialCount == pDBSkinPartResource->materialsReferences.size() , "wrong number of materials" );
		int counter = 0;
		for ( int i = 0; i < maxSlotsCount; ++i )
		{
			if( !elementSlots[i].IsEmpty() )
				continue;

      BaseMaterial* pMaterial = static_cast<BaseMaterial*>( Render::CreateRenderMaterial( pDBSkinPartResource->materialsReferences[pMeshGeometry->materialID[counter]].GetPtr() ));
			elementSlots[i].Initialize( pMaterial, pMeshGeometry, counter );

      // check material lighting for correctness and initialize
      if (pMaterial)
      {
        BasicMaterial* pBasicMaterial = dynamic_cast<BasicMaterial*>(pMaterial);
        if (pBasicMaterial)
        {
          if (pBasicMaterial->GetLightingPin() == NDb::LIGHTINGPIN_LIGHTINGDYNAMIC)
            lightsFlags |= (1 << i);
          else if (pBasicMaterial->GetLightingPin() == NDb::LIGHTINGPIN_LIGHTINGSH)
            needLightingSH = true;
          else
          {
            NI_DATA_ALWAYS_ASSERT(NStr::StrFmt("Unsupported lighting (%s) is specified in material for animated mesh. See '%s'", 
              NDb::EnumToString(pBasicMaterial->GetLightingPin()), GetDBID() ? GetFormattedDbId(*GetDBID()).c_str() : pDBSkinPartResource->geometryFileName));
          }
        }
      }

			pPartIndexes[counter] = i;
			++counter;
			if(counter == primitiveCount)
				break;
		}
		NI_ASSERT(counter == primitiveCount, "not all elements of skinpart have been added!" );
		*pPartsCount = counter;

    UpdateReindexMap();
	}

  void SkeletalMesh::RemoveSkinPart( unsigned int partsCount, const unsigned int* pPartIndexes )
  {
    NI_ASSERT( partsCount < maxSlotsCount, "parts count more than slots" );
    for ( unsigned int i = 0; i < partsCount; ++i )
    {
      elementSlots[pPartIndexes[i]].Destroy();
    }

    UpdateReindexMap();
  }

  void SkeletalMesh::SetEnableSkinPart( unsigned int partsCount, const unsigned int* pPartIndexes, bool val )
  {
    NI_ASSERT( partsCount < maxSlotsCount, "parts count more than slots" );
    for ( unsigned int i = 0; i < partsCount; ++i )
    {
      elementSlots[pPartIndexes[i]].SetEnabled( val );
    }
  }

  void SkeletalMesh::UpdateReindexMap()
  {
    int startIndex = 0;

    for ( unsigned int slotNumber = 0; slotNumber < maxSlotsCount; ++slotNumber )
    {
      if ( elementSlots[slotNumber].IsEmpty() )
        continue;

      startIndex += elementSlots[slotNumber].GetFragmentReindex()->size();
    }

    pSkeletonWrapper->SetActiveBones( startIndex );

    startIndex = 0;

    for ( unsigned int slotNumber = 0; slotNumber < maxSlotsCount; ++slotNumber )
    {
      if ( elementSlots[slotNumber].IsEmpty() )
        continue;

      elementSlots[slotNumber].SetMatrixIndex( startIndex );

      const unsigned int currentFragmentBoneCount = elementSlots[slotNumber].GetFragmentReindex()->size();

      for( unsigned int boneNumber = 0; boneNumber < currentFragmentBoneCount; ++boneNumber )
      {
        pSkeletonWrapper->SetReindex( *(elementSlots[slotNumber].GetFragmentReindex()->at(boneNumber)), startIndex + boneNumber );
      }

      startIndex += currentFragmentBoneCount;
    }
  }

  /////////////////////////////////////////////////////////////////////////
  bool SkeletalMesh::FillOBB(CVec3 (&_vertices)[8]) const
  {
    if( localAABB.IsEmpty() )
      return false;

    RenderComponent::FillOBB(localAABB, worldMatrix, &_vertices[0]);
    return true;
  }

	void SkeletalMesh::SetAnimationBlender( SkeletalAnimationBlender* pSampler )
	{
		NI_ASSERT(pSampler, "null ptr to SkeletonAnimationSampler");
		pSkeletalAnimationBlender = pSampler;
	}

	//void SkeletalMesh::SetSkeletonWrapper( SkeletonWrapper* _pSkeletonWrapper )
	//{
	//	NI_ASSERT(_pSkeletonWrapper, "null ptr to SkeletonWrapper");
	//	pSkeletonWrapper = _pSkeletonWrapper;
	//}

	void SkeletalMesh::SetWorldMatrix( const Matrix43& transform )
	{
		worldMatrix = transform; 
	}
  
  void SkeletalMesh::SetMaterial( int slotNumber, BaseMaterial* _pMaterial )
  {
    NI_VERIFY( slotNumber < (int)maxSlotsCount && slotNumber >= 0, "", return );

    if ( elementSlots[slotNumber].IsEmpty() )
      return;

    elementSlots[slotNumber].SetMaterial( _pMaterial );
  }

  BaseMaterial* SkeletalMesh::GetMaterial( int slotNumber )
  {
    NI_VERIFY( slotNumber < (int)maxSlotsCount && slotNumber >= 0, "", return 0);

    if ( elementSlots[slotNumber].IsEmpty() )
      return 0;

    return elementSlots[slotNumber].GetMaterial();
  }

	SkeletalMesh::~SkeletalMesh()
	{
    delete pSkeletonWrapper;
		pSkeletonWrapper = NULL;
	}

  void SkeletalMesh::ForAllMaterials(Render::IMaterialProcessor &proc)
  {
    Render::BaseMaterial *pMat = 0; 
    for (int i = 0; i < maxSlotsCount; ++i)
    {
      pMat = GetMaterial(i);
      if (pMat)
        proc(*pMat);
    }
  }

	void SkeletalMeshElement:: Initialize( BaseMaterial* pMaterial, MeshGeometry const *meshGeom, int index )
	{
		NI_ASSERT( pMaterial, "null ptr to material" );
    NI_ASSERT( meshGeom, "null ptr to mesh geometry" );
    NI_ASSERT( index < meshGeom->primitives.size() && index >= 0, "invalid primtive index" );
		NI_ASSERT( meshGeom->primitives[ index ], "null ptr to primitive" );
		NI_ASSERT( meshGeom->pReindex->reindex.at( index ), "null ptr to reindex" );
		
    pMeshGeom = meshGeom;
    primitiveIndex = index;
    SetMaterial(pMaterial);
    isEnabled = true;
	}

	SkeletalMeshElement::~SkeletalMeshElement()
	{
		Destroy();
	}

	void SkeletalMeshElement::Destroy()
	{
		delete pMaterialInstance; 
    pMaterialInstance = 0; 
    pMeshGeom = 0;
	}

	void SkeletalMeshElement::SetMaterial( BaseMaterial* _pMaterial )
	{
		NI_VERIFY( _pMaterial, "null ptr to material", return ); 
    if (pMaterialInstance)
		  delete pMaterialInstance; 

    _pMaterial->SetSkeletalMeshPin(NDb::BOOLEANPIN_PRESENT);

    if (pMeshGeom && !RENDER_DISABLED &&
        pMeshGeom->primitives[primitiveIndex])
    {
      _pMaterial->SetMultiplyVertexColorPin( VertexHasColors(pMeshGeom->primitives[primitiveIndex]->GetVertexDeclaration()) ?
                                             NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
    }

    pMaterialInstance = _pMaterial;
	}

  Primitive const* SkeletalMeshElement::GetPrimitive() const
  {
    NI_ASSERT( primitiveIndex < pMeshGeom->primitives.size() && primitiveIndex >= 0, "invalid primtive index" );
		
    Primitive const *res = pMeshGeom->primitives[ primitiveIndex ];
    NI_ASSERT( res, "null ptr to primitive" );

    return res;
  }

  StaticVector<unsigned short> const* SkeletalMeshElement::GetFragmentReindex() const
  {
    NI_ASSERT( primitiveIndex < pMeshGeom->primitives.size() && primitiveIndex >= 0, "invalid primtive index" );

    StaticVector<unsigned short> const* res = pMeshGeom->pReindex->reindex.at( primitiveIndex );
		NI_ASSERT( res, "null ptr to reindex" );

    return res;
  }

};
