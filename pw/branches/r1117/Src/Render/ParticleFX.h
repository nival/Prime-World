#pragma once

#include "RenderComponent.h"
#include "renderableprimitive.h"
#include "MaterialSpec.h"
#include "../Scene/DBScene.h"

#include "dipdescriptor.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PFXBinaryFileWrapper;

namespace Render
{
	struct HDRColorModifier;
  class SkeletalMesh;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Render
{
  struct IParticlesManager
  {
    virtual void AddBatch(Batch *_pBatch) = 0;
    virtual void FinalizeBatch() = 0;
    virtual void RenderToQueue(BatchQueue* _queue) = 0;
    virtual void Clear() = 0;
  };

  IParticlesManager* GetParticlesManager();

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class ParticleFX : public RenderComponent, public IRenderablePrimitive
	{
		REPLACE_DEFAULT_NEW_DELETE(ParticleFX);
		float oldTime[2];
		float currentTime[2];
		bool playingSecondTrack;

    // database parameters
    float camoffset;
    NDb::EOrientType orient;
    CVec2 pivot;
    bool isWorldSpace;
    bool isDblBuffered;
    BaseMaterial* pFXMaterial;
    nstl::vector<CVec4> uvPairs;

    const PFXBinaryFileWrapper* pPFXData;
    int particlesCount;
    int particlesMaxCount;
    int activeParticleCount;

    unsigned char* pMemory;
    Matrix43* pParticleMatrix;              // [particlesMaxCount]
    Matrix43* pParticleMatrixTemp;          // [particlesCount] or NULL
    struct ParticleVertexSW* pActiveParticles;      // [particlesMaxCount]
    struct ParticleIndex* pActiveParticlesReindex;  // [particlesMaxCount]
    vector<int> activeParticleIndices;

    // transformation data
    Matrix43 worldMatrix;
    float scale;
		Placement oldGlobalPos;
		Placement newGlobalPos;
    bool isFirstPlacement;

    float lastTime;

    bool isDying;

    // graphics data
    SpaceHolder vertexDataHolder;
    DXVertexDeclarationRef pVertexDecl;
    DipDescriptor dipDescr;

    friend class ParticlesManager;

		void InitializeInternal();
		void Sampling( int groupId, CVec3 const& cameraPos, const CVec3& addSpeed );
		void Sorting( /*ParticleVertexHW**/void* pVBData );
		void UpdateScale();

	public:
		ParticleFX();
		virtual ~ParticleFX();

		void Initialize( const Matrix43& _worldMatrix, const NDb::DBParticleSceneComponent* _pDBPFXInstance, bool doubleBufferred );
		void Reinit();
		void OnTimeLooped(float time, float time2StartWith);

    void Die();
    bool Ready2Die();
		bool IsDying();

		bool SetTime( float _time );
    void Update(CVec3 const& cameraPos_);
		float GetTotalTime() const;

		void SetWorldMatrixForWorldSpace( const Matrix43& transform );
		void SetWorldMatrix( const Matrix43& transform );
		const Matrix43& GetWorldMatrix() const { return worldMatrix; }
		bool CalcWorldAABB(AABB &aabb);
    
    // interface for those who don't care about internal mechanics
    int GetMaxParticleCount() const { return particlesMaxCount; }
    int GetParticleCount() const { return playingSecondTrack ? 2 * particlesCount : particlesCount; }
    bool IsParticleActive(int particleNumber) const;
    void GetParticleWorldPos(int particleNumber, CVec3 &pos) const;

    // From Render::IRenderablePrimitive
    virtual void Bind() const;
    virtual void Draw() const;
    virtual GeometryBuffers  GetBuffers() const { GeometryBuffers res = {0}; return res; }
    virtual GeometryStatistics GetStats() const
    { 
      return GeometryStatistics(dipDescr.primitiveCount * activeParticleCount, dipDescr.numVertices * activeParticleCount); 
    }

    // From Render::RenderComponent
    virtual void RenderToQueue( class BatchQueue& queue );
    virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;

    bool IsWorldSpace()
    {
      return isWorldSpace;
    }

    // Hides RenderComponent::SetMaterial?
    void SetMaterial( BaseMaterial* _pMaterial );
    BaseMaterial* GetMaterial() const { return pFXMaterial; }
    OcclusionQueries* GetQueries() const { return 0; }
	};
}; // namespace Render