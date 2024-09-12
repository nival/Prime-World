#pragma once

#include "RenderComponent.h"
#include "MaterialSpec.h"
#include "../System/staticvector.h"
#include "MeshResource.h"

namespace Render
{
	class Primitive;

	class SkeletalMeshElement 
	{
		SkeletalMeshElement(const SkeletalMeshElement&);
		SkeletalMeshElement& operator=(const SkeletalMeshElement&);
    bool isEnabled;
	public:
		BaseMaterial       *pMaterialInstance;
    MeshGeometry const *pMeshGeom;
    int                 primitiveIndex;
    int                 matrixIndex;
		//Primitive* pPrimitive;
		//const StaticVector<unsigned short>* pSkeletonFragmentReindex;
		//////////////////////////////////////////////////////////////////////////
		SkeletalMeshElement() : pMaterialInstance(0), /*pPrimitive(0), pSkeletonFragmentReindex(0)*/pMeshGeom( 0 ), primitiveIndex( 0 ), isEnabled(true) {}

		//void Initialize( BaseMaterial* pMaterial, Primitive* _pPrimitive, const StaticVector<unsigned short>* _pSkeletonFragmentReindex );
    void Initialize( BaseMaterial* pMaterial, MeshGeometry const *meshGeom, int index );

    //void SetPrimitive( Primitive* _pPrimitive ) { NI_ASSERT( _pPrimitive, "null ptr to primitive" ); pPrimitive = _pPrimitive; }
		//void SetFragmentReindex( const StaticVector<unsigned short>* _pSkeletonFragmentReindex ) {NI_ASSERT( _pSkeletonFragmentReindex, "null ptr to primitive" ); pSkeletonFragmentReindex = _pSkeletonFragmentReindex;} 
    void SetPrimitive( MeshGeometry const *meshGeom, int index );

    void SetMaterial( BaseMaterial* _pMaterial );
    BaseMaterial* GetMaterial( void ) { return pMaterialInstance; }
    Primitive const* GetPrimitive() const;

    StaticVector<unsigned short> const* GetFragmentReindex() const;
    int GetMatrixIndex() const { return matrixIndex; }
    void SetMatrixIndex( int _matrixIndex ) { matrixIndex = _matrixIndex; }

		//bool IsEmpty() const { return !(pMaterialInstance && pPrimitive && pSkeletonFragmentReindex);  }
    bool IsEmpty() const { return !(pMaterialInstance && pMeshGeom);  }
		void Destroy();
    bool IsEnabled()
    {
      return isEnabled;
    }
    void SetEnabled( bool val )
    {
      isEnabled = val;
    }
		~SkeletalMeshElement();
	};

	class SkeletalAnimationBlender;
	class SkeletonWrapper;

	class SkeletalMesh : public RenderComponent
	{
		REPLACE_DEFAULT_NEW_DELETE(SkeletalMesh);
		static const unsigned int maxBoneCountPerFragment = MAX_BONES;
		static const unsigned int maxSlotsCount = 16;
		static const unsigned int maxMaxFragmentCountPerSkinPart = 4;
		Matrix43 worldMatrix;
		SkeletalMeshElement elementSlots[maxSlotsCount];
		SkeletonWrapper* pSkeletonWrapper;
		SkeletalAnimationBlender* pSkeletalAnimationBlender;
		SkeletalMesh& operator=(const SkeletalMesh&);
		SkeletalMesh(const SkeletalMesh&);

    AABB localAABB;
    AABB worldAABB;
    LightsData lightsData;
    unsigned long lightsFlags;

    mutable DeviceLostWrapper<OcclusionQueries> queries;

    bool needLightingSH;

#ifdef _DEBUG
		string skeletonSourceFileName;
#endif

    void UpdateReindexMap();

	public:
		SkeletalMesh();
		virtual ~SkeletalMesh();

		void Initialize( const Matrix43& _worldMatrix, const nstl::string& skeletonFileName );

		void AddSkinPart( const NDb::SkinPartBase* pDBSkinPartResource, unsigned int* pPartIndexes, unsigned int* pPartsCount );

		void PrepareRendererAfterMaterial( unsigned int slotNumber ) const;

		void RemoveSkinPart( unsigned int partsCount, const  unsigned int* pPartIndexes );
    void SetEnableSkinPart( unsigned int partsCount, const unsigned int* pPartIndexes, bool val );

    void SetLocalAABB(AABB const& aabb) { localAABB = aabb; }
    void SetWorldAABB(AABB const& aabb) { worldAABB = aabb; }
		void SetWorldMatrix(const Matrix43& transform);
		const Matrix43& GetWorldMatrix() const { return worldMatrix; }

		void Update(bool bNeedBlenderUpdate);

		virtual void RenderToQueue( BatchQueue& queue );

    virtual void SetMaterial( int slotNumber, BaseMaterial* _pMaterial );
    virtual BaseMaterial* GetMaterial( int slotNumber );

    OcclusionQueries* GetQueries() const { return &queries; }
    bool FillOBB(CVec3 (&_vertices)[8]) const ;
    const AABB& GetLocalAABB() const  { return localAABB; }
    const AABB& GetAABB(bool *_pIsLocal) const
    {
      if( localAABB.IsEmpty() ) {
        *_pIsLocal = false;
        return worldAABB;
      }
      return *_pIsLocal ? localAABB : worldAABB;
    }

    bool NeedLightingSH() const { return needLightingSH; }

		void SetAnimationBlender( SkeletalAnimationBlender* pSampler );
		SkeletalAnimationBlender* GetAnimationBlender() const { return pSkeletalAnimationBlender; }
		SkeletonWrapper* GetSkeletonWrapper() const { return pSkeletonWrapper; }

		//void SetSkeletonWrapper(SkeletonWrapper* _pSkeletonWrapper);

    void ForAllMaterials(Render::IMaterialProcessor &proc);
	};
	
};
