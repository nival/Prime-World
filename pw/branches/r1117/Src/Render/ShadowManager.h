#pragma once

#include "System/Singleton4DLL.h"
#include "sceneconstants.h"
#include "System/GeomMisc.h"
#include "Vendor/DirectX/Include/d3dx9.h"
#include "GlobalMasks.h"
#include "aabb.h"
#include "ShadowReceiverVolume.h"

namespace Render
{
	class BatchQueue;

	class ShadowManager : public Singleton4DLL<ShadowManager>
	{
    unsigned int fullsizeX;
    unsigned int fullsizeY;
    unsigned int sizeX;
		unsigned int sizeY;
    unsigned int sizeSAX;
    unsigned int sizeSAY;
    NDb::ShadowMode shadowMode;
    float depthBias;
    float biasSlope;

		D3DXMATRIX m_world2LightProj;
		D3DXMATRIX m_world2Light; /// видовая матрица трансформации источника света
		D3DXMATRIX m_light2World; /// инверсированная видовая матрица трансформации источника света
		D3DXMATRIX m_light2LightProj;
		D3DXVECTOR3 m_lightDirWS;
		D3DXMATRIX m_world2View, m_view2Proj;
    AABB m_casterBoundsLS;
		//float m_fCosGamma;
		//float m_fSlideBack; // smirnov [2009/7/16]: unused

		//float m_zNear, m_zFar; // smirnov [2009/7/16]: unused

		vector<D3DXVECTOR3> m_shadowReceiverPointsVS;
    vector<D3DXVECTOR3> m_frustumPointsLS;

		bool lastShadowStat;

    HDRColor m_shadowColor;
    float m_shadowLength;
    float m_shadowFar;
    float m_shadowFarRange;
    float m_shadowFarFinal;
    bool isShadowRendering;
    NDb::ShadowBlendMode m_blendMode;

    CPtr<IShadowReceiverVolume> shadowReceiverVolume;

    class ShadowMap* pShadowMap;

	public:

    // extracted from NDb::LightEnvironment
    struct Params
    {
      int fullSizeX;
      int fullSizeY;
      int fullSizeSAX;
      int fullSizeSAY;
      NDb::ShadowMode shadowMode;
      float powerOfESM;
      float depthBias;
      float biasSlope;
      Render::HDRColor shadowColor;
      NDb::Direction shadowDirection;
      NDb::ShadowBlendMode shadowBlendMode;
      float shadowLength;
      float shadowFar;
      float shadowFarRange;

      Params();

      void FromLightEnvironment(const NDb::LightEnvironment* const lenv);
      void FromBlend(const Params& lhs, const Params& rhs, const float t);
    };

		ShadowManager();
		ShadowManager( const NDb::LightEnvironment* lenv );
    ShadowManager( const Params& params );
    ~ShadowManager();

    bool IsShadowRendering() { return isShadowRendering; }
    void SetShadowRenderingFlag( bool isShadRendering ) { isShadowRendering = isShadRendering; }
    void SetShadowReceiverVolume( IShadowReceiverVolume* _shadowReceiverVolume ) { shadowReceiverVolume = _shadowReceiverVolume; }

    void BuildLightMatrices(/*out*/ SceneConstants* lightSceneConsts, AABB *_pCasterAABB,
                            const SceneConstants &_viewSceneConsts, const CVec3& _frustumEdge,
                            float _minHeight, float _maxHeight);
    AABB const& GetCastersBoundsLS() const { return m_casterBoundsLS; }
    void CreateShadowTexture( BatchQueue &_batchQueue, const SceneConstants &_sceneConsts );
		void ShowShadowTexture();
		void ApplyFullscreenShadows(const SceneConstants &viewSceneConsts, Texture2DRef const& pDepthTexture);
		void NoShadows();
		void Reload();

    void SetMode( NDb::ShadowMode _shadowMode );
    float GetShadowHeight() { return (m_shadowFar + m_shadowFarRange) * m_lightDirWS.z; }

    void SetRuntimeParams(const Params& params);

    static void SubstituteMaterials(BatchQueue &_batchQueue);
    static void RemoveMaterials(BatchQueue &_batchQueue);

	private: // summed area block
    void DrawFrustumToMap();

    void RenderESMShadowMap();

    void ResizeShadows();

		void SetParams( const NDb::LightEnvironment* lenv );
    void SetParams(const Params& params);

    void ComputeCastersAABB(Render::AABB *_pCastersAABB, bool _buildProj = 0);
		void BuildOrthoShadowProjectionMatrix(/*out*/ Render::AABB *_pCastersAABB);
    //void BuildOrthoShadowProjectionMatrixCrap();// smirnov [2009/7/16]: unused
    void BuildTightOrthoMatrices(/*out*/ AABB *_pCastersAABB, const SceneConstants &_viewSceneConsts,
                                 float _minZ, float _maxZ);
    void BuildLSPSMProjectionMatrices(/*out*/ AABB *_pCastersAABB, const SceneConstants &_viewSceneConsts,
                                      float _minZ, float _maxZ);

		void Verify();
	};

};//namespace Render