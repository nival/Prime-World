#include "stdafx.h"
#include "ShadowManager.h"
#include "batch.h"
#include "ImmediateRenderer.h"
#include "renderresourcemanager.h"
#include "smartrenderer.h"
#include "../System/nalgobase.h"
#include "../System/Transform.h"
#include "../System/InlineProfiler.h"
#include "debugrenderer.h"
#include "ShadowMap.h"
#include "DXHelpers.h"
#include "IConfigManager.h"
#include "BoundingPrimitives.h"
#include "ConvertDirection.h"


static float s_SizeScale = 1.0f;
REGISTER_VAR("shadowMapScale", s_SizeScale, STORAGE_USER)

static int s_FrustumType = 2;
REGISTER_VAR("shadowFrustumType", s_FrustumType, STORAGE_NONE)

static bool s_MaskFrustum = false;
REGISTER_DEV_VAR("shadowFrustumMask", s_MaskFrustum, STORAGE_NONE)

static bool s_ZMinFromTerrain = true;
REGISTER_DEV_VAR("shadowZMinFromTerrain", s_ZMinFromTerrain, STORAGE_NONE)

static bool s_doZClip = true;
REGISTER_DEV_VAR("shadowZClip", s_doZClip, STORAGE_NONE)

static bool s_bUnitCubeClip = true;
REGISTER_DEV_VAR("shadowUnitCubeClip", s_bUnitCubeClip, STORAGE_NONE)

static float s_fShadowLengthCoeff = 1.0f;
REGISTER_DEV_VAR("shadowLengthCoeff", s_fShadowLengthCoeff, STORAGE_NONE)

static float s_fLSPSM_NoptWeight = 1.0f;
REGISTER_DEV_VAR("shadowLSPSMWeight", s_fLSPSM_NoptWeight, STORAGE_NONE)

static const UINT Vec3size = sizeof(D3DXVECTOR3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// static NDebug::DebugVar<CVec3> render_ShadowMinPnt( "ShadowMinPnt", "Shadows" );
// static NDebug::DebugVar<CVec3> render_ShadowMaxPnt( "ShadowMaxPnt", "Shadows" );
// static NDebug::DebugVar<CVec3> render_ShadowMinPnt2( "ShadowMinPnt2", "Shadows" );
// static NDebug::DebugVar<CVec3> render_ShadowMaxPnt2( "ShadowMaxPnt2", "Shadows" );
// static NDebug::DebugVar<CVec3> render_ShadowMinRod( "ShadowMinPnt", "Shadows" );
// static NDebug::DebugVar<CVec3> render_ShadowMaxRod( "ShadowMaxPnt", "Shadows" );

static NDebug::DebugVar<float> render_ShadowMinZ( "ShadowMinZ", "Shadows" );
static NDebug::DebugVar<float> render_ShadowFarFinal( "ShadowFarFinal", "Shadows" );
static NDebug::DebugVar<float> render_ShadowRangeFinal( "ShadowRangeFinal", "Shadows" );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SINGLETON4DLL_DEF(Render::ShadowManager)

// default params extracted from NDb::LightEnvironment
Render::ShadowManager::Params::Params()
  : fullSizeX( 2048 )
  , fullSizeY( 2048 )
  , fullSizeSAX( 1024 )
  , fullSizeSAY( 1024 )
  , shadowMode( NDb::SHADOWMODE_PCF )
  , powerOfESM( 80.0f )
  , depthBias( 0.0001f )
  , biasSlope( 4.0f )
  , shadowColor(0.0f, 0.0f, 0.1f, 0.25f)
  , shadowDirection()
  , shadowBlendMode( NDb::SHADOWBLENDMODE_LERPBYALPHA )
  , shadowLength( 20.0f )
  , shadowFar( 60.0f )
  , shadowFarRange( 10.0f )
{

}

void Render::ShadowManager::Params::FromLightEnvironment(const NDb::LightEnvironment* const lenv)
{
  // TODO: reset?
  if (!lenv)
    return;

  fullSizeX = lenv->fullSizeX;
  fullSizeY = lenv->fullSizeY;
  fullSizeSAX = lenv->fullSizeSAX;
  fullSizeSAY = lenv->fullSizeSAY;
  shadowMode = lenv->shadowMode;
  powerOfESM = lenv->powerOfESM;
  depthBias = lenv->depthBias;
  biasSlope = lenv->biasSlope;
  shadowColor = lenv->shadowColor;
  shadowDirection = lenv->shadowDirection;
  shadowBlendMode = lenv->shadowBlendMode;
  shadowLength = lenv->shadowLength;
  shadowFar = lenv->shadowFar;
  shadowFarRange = lenv->shadowFarRange;
}

void Render::ShadowManager::Params::FromBlend(const Params& lhs, const Params& rhs, const float t)
{
  // TODO: verify these are the same in lhs and rhs
  fullSizeX = lhs.fullSizeX;
  fullSizeY = lhs.fullSizeY;
  fullSizeSAX = lhs.fullSizeSAX;
  fullSizeSAY = lhs.fullSizeSAY;
  shadowMode = lhs.shadowMode;
  depthBias = lhs.depthBias;
  biasSlope = lhs.biasSlope;
  shadowBlendMode = lhs.shadowBlendMode;

  const float factor = Clamp(t, 0.f, 1.f);

  powerOfESM = Lerp(lhs.powerOfESM, rhs.powerOfESM, factor);
  shadowColor.Lerp(lhs.shadowColor, rhs.shadowColor, factor);
  shadowLength = Lerp(lhs.shadowLength, rhs.shadowLength, factor);
  shadowFar = Lerp(lhs.shadowFar, rhs.shadowFar, factor);
  shadowFarRange = Lerp(lhs.shadowFarRange, rhs.shadowFarRange, factor);

  // TODO: slerp?
  shadowDirection.Yaw = Lerp(lhs.shadowDirection.Yaw, rhs.shadowDirection.Yaw, factor);
  shadowDirection.Pitch = Lerp(lhs.shadowDirection.Pitch, rhs.shadowDirection.Pitch, factor);
}

namespace Render
{
  using namespace ::NDebug;

  static float m_blurRadius = 10.f;
  static float m_esmPower = 10.f;

  static bool shadowTest = true;

  REGISTER_VAR( "shadowTest", shadowTest, STORAGE_USER );

  static bool shadow_terrain = true;
  REGISTER_VAR( "shadow_terrain", shadow_terrain, STORAGE_USER );
  REGISTER_VAR_INTERFACE( "proxy_shadow_terrain", NGlobal::MakeVarProxy(&shadow_terrain), STORAGE_NONE );

	static void fromSHMatrix( D3DXMATRIX* d3dmat, const SHMatrix& mat )
	{
		memcpy( d3dmat, &mat, sizeof(SHMatrix) );
		D3DXMatrixTranspose( d3dmat, d3dmat );
	}

	static void fromD3DMatrix( SHMatrix* mat, const D3DXMATRIX& d3dmat )
	{
		D3DXMATRIX temp = d3dmat;
		D3DXMatrixTranspose( &temp, &temp );
		memcpy( mat, &temp, sizeof(SHMatrix) );
	}

  ShadowManager::ShadowManager( const NDb::LightEnvironment* lenv )
    : m_frustumPointsLS(8)
    , m_shadowColor(1.0f, 0.0f, 0.0f, 1.0f)
    , isShadowRendering(false)
    , shadowMode(NDb::SHADOWMODE_PCF)
    , m_lightDirWS(0.f, 0.f, 0.f) // this value is important for correct minimap render in editor
    , m_shadowFarFinal(1.f)
    , pShadowMap()
	{
		SetParams( lenv );
    lastShadowStat = false;
    ResizeShadows();
	}

  ShadowManager::ShadowManager()
    : m_frustumPointsLS(8)
    , m_shadowColor(1.0f, 0.0f, 0.0f, 1.0f)
    , isShadowRendering(false)
    , shadowMode(NDb::SHADOWMODE_PCF)
    , m_lightDirWS(0.f, 0.f, 0.f) // this value is important for correct minimap render in editor
    , m_shadowFarFinal(1.f)
    , pShadowMap()
	{
		SetParams( 0 );
    lastShadowStat = false;
    ResizeShadows();
	}

  ShadowManager::ShadowManager(const Params& params)
    : m_frustumPointsLS(8)
    , m_shadowColor(1.0f, 0.0f, 0.0f, 1.0f)
    , isShadowRendering(false)
    , shadowMode(NDb::SHADOWMODE_PCF)
    , m_lightDirWS(0.f, 0.f, 0.f) // this value is important for correct minimap render in editor
    , m_shadowFarFinal(1.f)
    , pShadowMap()
  {
    SetParams(params);
    lastShadowStat = false;
    ResizeShadows();
  }

  ShadowManager::~ShadowManager()
  {
    SAFE_DELETE(pShadowMap);
  }

  static void SubstituteMaterials(BatchQueue &_batchQueue, int _priority)
  { // There should be cache here
    for(Batch* pBatch = _batchQueue.GetSubQueue(_priority).pBatchList; pBatch; pBatch = pBatch->pNextBatch)
      pBatch->pMaterial = ShadowMaterial::CreateMaterial(pBatch->pMaterial);
  }

  void ShadowManager::SetRuntimeParams(const Params& params)
  {
    m_esmPower = params.powerOfESM;

    m_shadowColor = params.shadowColor;
    m_shadowLength = params.shadowLength;
    m_shadowFar = params.shadowFar;
    m_shadowFarFinal = params.shadowFar;
    m_shadowFarRange = params.shadowFarRange;

    CVec3 lightDirWS;
    ConvertDirection(params.shadowDirection, lightDirWS);
    m_lightDirWS = -lightDirWS;
  }

  void ShadowManager::SubstituteMaterials(BatchQueue &_batchQueue)
	{
    if( 0 == NGlobal::GetVar("shadowNew").GetInt64() )
      return;

    Render::SubstituteMaterials(_batchQueue, NDb::MATERIALPRIORITY_MESHESOPAQUE);
    Render::SubstituteMaterials(_batchQueue, NDb::MATERIALPRIORITY_MESHESOPAQUELATE);
    Render::SubstituteMaterials(_batchQueue, NDb::MATERIALPRIORITY_TERRAINOBJECTS);
  }


  static void RemoveMaterials(BatchQueue &_batchQueue, int _priority)
  {
    for(Batch* pBatch = _batchQueue.GetSubQueue(_priority).pBatchList; pBatch; pBatch = pBatch->pNextBatch)
    {
      delete pBatch->pMaterial;
      pBatch->pMaterial = 0;
    }
  }

  void ShadowManager::RemoveMaterials(BatchQueue &_batchQueue)
  {
    if( 0 == NGlobal::GetVar("shadowNew").GetInt64() )
      return;

    Render::RemoveMaterials(_batchQueue, NDb::MATERIALPRIORITY_TERRAINOBJECTS);
    Render::RemoveMaterials(_batchQueue, NDb::MATERIALPRIORITY_MESHESOPAQUELATE);
    Render::RemoveMaterials(_batchQueue, NDb::MATERIALPRIORITY_MESHESOPAQUE);
  }


  void ShadowManager::DrawFrustumToMap()
  {
    static ManagedResource<MaterialInit<ShadowMaterial> > shadowMaterial;

    if( ShadowMaterial* const material = (ShadowMaterial*)shadowMaterial.Get() )
    {
      material->GetDiffuseMap()->Enable(false);
      material->PrepareRenderer();
      SmartRenderer::SetFVF(D3DFVF_XYZ);

      RenderStatesManager& statesManager = *GetStatesManager();
      RenderState oldState = statesManager.GetCurrentState();
      RenderState state = oldState;
      state.SetAlphaTest(NDb::ONOFFSTATE_OFF);
      state.SetCulling(NDb::ONOFFSTATE_ON);
      statesManager.SetState(state);
      statesManager.SetStateDirect(D3DRS_ZFUNC, D3DCMP_ALWAYS);

      IDirect3DDevice9* const pDev = GetDevice();
      DWORD oldBias = 0, oldSlope = 0;
      pDev->GetRenderState(D3DRS_DEPTHBIAS, &oldBias);
      pDev->SetRenderState(D3DRS_DEPTHBIAS, 0);
      pDev->GetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, &oldSlope);
      pDev->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, 0);

      static const Matrix43 unity( CVec3(0,0,0) );
      GetRenderer()->SetVertexShaderConstants(WORLD, 3, &unity);

      NI_ASSERT(8 <= m_frustumPointsLS.size(), "Too small m_frustumPointsLS");

      CVec3 frustumPointsWS[8];
      D3DXVec3TransformCoordArray(AsD3D(frustumPointsWS), Vec3size, &m_frustumPointsLS[0], Vec3size, &m_light2World, 8);
      for(int i = 4; i < 8; ++i) {
        frustumPointsWS[i].z -= 0.2f; // Shift-down down-plane
      }
      CubeRenderer::DrawIndexedPrimitiveUP(frustumPointsWS);

#ifdef _DEBUG
      D3DXVec3TransformCoordArray(AsD3D(frustumPointsWS), Vec3size, &m_frustumPointsLS[0], Vec3size, &m_light2LightProj, 8);
      for(int i = 0; i < 8; ++i) {
        ASSERT( (fabsf(frustumPointsWS[i].x) <= 1.01f) && (fabsf(frustumPointsWS[i].y) <= 1.01f) );
        ASSERT(fabsf(frustumPointsWS[i].z -.505f) <= .507f);
      }
#endif // _DEBUG

      pDev->SetRenderState(D3DRS_DEPTHBIAS, oldBias);
      pDev->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, oldSlope);
      statesManager.SetStateDirect(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
      statesManager.SetState(oldState);
    }
  }


#ifndef _SHIPPING
  static DebugVar<int> s_numVS( "numVS_shadow", "Statistics", true );
  static DebugVar<int> s_numPS( "numPS_shadow", "Statistics", true );
  static DebugVar<int> s_numBatches( "numBatches_shadow", "Statistics", true );
#endif // _SHIPPING

  //////////////////////////////////////////////////////////////////////////////////////////////////
	void ShadowManager::CreateShadowTexture( BatchQueue &_batchQueue, const SceneConstants &_sceneConsts )
	{
		if ( !lastShadowStat )
		{
      lastShadowStat = true;
			ResizeShadows();
		}

    // in case it's not yet created due to lost device or anything
    if(!pShadowMap)
      return;
    
    SmartRenderer::BindRenderTargetColor(1, DXSurfaceRef() );
    pShadowMap->PreRender();

		// Enable rendering to shadow
		GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERTOSHADOW;

#ifndef _SHIPPING
    const int numVS = GetDebugVarValue<int>(L"numVS");
    const int numPS = GetDebugVarValue<int>(L"numPS");
    s_numBatches.SetValue(_batchQueue.GetSubQueue(NDb::MATERIALPRIORITY_MESHESOPAQUE).numBatches +
                          _batchQueue.GetSubQueue(NDb::MATERIALPRIORITY_MESHESOPAQUELATE).numBatches +
                          _batchQueue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINOBJECTS).numBatches);
#endif // _SHIPPING

#ifdef _DEBUG_VIEWPORT
    D3DVIEWPORT9 vp;
    GetDevice()->GetViewport(&vp);
    RECT sr;
    GetDevice()->GetScissorRect(&sr);
#endif // _DEBUG

    if(s_MaskFrustum && s_FrustumType)
      DrawFrustumToMap();

    _batchQueue.Render( NDb::MATERIALPRIORITY_MESHESOPAQUE, NDb::MATERIALPRIORITY_MESHESSILHOUETTE );

    _batchQueue.Render( NDb::MATERIALPRIORITY_TERRAINOBJECTS );

    Renderer &renderer = *GetRenderer();
    if(shadow_terrain || shadowMode != NDb::SHADOWMODE_PCF)
    {
#ifndef _SHIPPING
      s_numBatches.AddValue(_batchQueue.GetSubQueue(NDb::MATERIALPRIORITY_TERRAINLAYER0).numBatches);
#endif // _SHIPPING
      Render::RenderState state = Render::RenderState::NoBlendNoTest();
      state.SetAlphaTestRef(127);
      state.SetCulling(NDb::ONOFFSTATE_ON);

      Render::RenderStatesManager &statesManager = *Render::GetStatesManager();
      statesManager.SetState(state);
      statesManager.SetSamplerState( 0, SamplerState::PRESET_WRAP_BILINEAR() );

      _batchQueue.Render( NDb::MATERIALPRIORITY_TERRAINLAYER0 );
      renderer.ResetConstantProtectionBlock(Render::CCONTEXT_TERRAIN);
    }

#ifndef _SHIPPING
    s_numVS.SetValue(GetDebugVarValue<int>(L"numVS") - numVS);
    s_numPS.SetValue(GetDebugVarValue<int>(L"numPS") - numPS);
#endif // _SHIPPING


		// Disable rendering to shadow
		GetRuntimePins().RenderModeValue = NDb::RENDERMODEPIN_RENDERNORMAL;

    //if ( shadowMode == NDb::SHADOWMODE_SAESM )
    if ( shadowMode != NDb::SHADOWMODE_PCF )
    {
      const SHMatrix &proj = _sceneConsts.projection;
      renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST2, CVec4(-proj._34, proj._33, 0.0f, 0.0f) );
      renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST3, CVec4(1, 0, m_blurRadius, m_esmPower) ); 
    }

		pShadowMap->PostRender();

    SmartRenderer::BindRenderTargetDefault();

		Verify();
	}

	void ShadowManager::NoShadows()
	{
		//Verify();
		if ( lastShadowStat )
		{
      lastShadowStat = false;
			ResizeShadows();
		}
		//SmartRenderer::BindRenderTarget(pShadowTexture, pDepth);
		//GetRenderer()->Clear(Color(255,255,255,255));
		//SmartRenderer::BindRenderTargetDefault();
		//Verify();
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////
	void ShadowManager::ShowShadowTexture()
	{
    if(pShadowMap)
      pShadowMap->ShowTexture( CTRect<float>(-0.9f, -0.5f, -0.2f, 0.5f) );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////
	void ShadowManager::ApplyFullscreenShadows(const SceneConstants &viewSceneConsts, Texture2DRef const& pDepthTexture)
	{
    // in case it's not yet created due to lost device or anything
    if(!pShadowMap)
      return;

    RenderState renderState;
    renderState.SetBlendMode(m_blendMode == NDb::SHADOWBLENDMODE_MULCOLOR ? NDb::BLENDMODE_MULCOLOR : NDb::BLENDMODE_LERPBYALPHA);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
		//renderState.SetAlphaTestRef(0);

    RenderStatesManager &statesManager = *GetStatesManager();
		statesManager.SetState(renderState);
		statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
		statesManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
		statesManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);
    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x07); // disable alpha corruption
    statesManager.SetStencilState(STENCILSTATE_CHECKBITS, STENCILBIT_SHADOWRECEIVER);

    float shadowFarRange = m_shadowFarRange * m_shadowFarFinal / m_shadowFar;

    render_ShadowFarFinal.SetValue( m_shadowFarFinal );
    render_ShadowRangeFinal.SetValue( shadowFarRange );


    float fadeMul = -1.0f / Max(0.1f, shadowFarRange); // at least 0.1 meters for safety
    float fadeAdd = -fadeMul * m_shadowFarFinal;
		SHMatrix mLightViewProj;
		fromD3DMatrix(&mLightViewProj, m_world2LightProj);
		SHMatrix mViewToLightSpace;
		Multiply(&mViewToLightSpace, mLightViewProj, viewSceneConsts.invView);

    CVec4 uvScaleOffset;
    {
      int x, y, w, h;
      SmartRenderer::GetMainViewport(x, y, w, h);
      const float invWScale = 1.f / w;
      const float invHScale = 1.f / h;
      const float xScale = 1.f / viewSceneConsts.projection._11;
      const float yScale = 1.f / viewSceneConsts.projection._22;
      uvScaleOffset.Set( xScale * 2.f * pDepthTexture->GetWidth() * invWScale,
                        -yScale * 2.f * pDepthTexture->GetHeight() * invHScale,
                        -xScale * (x * invWScale + 1.f), yScale * (y * invHScale + 1.f) );
      //CVec4(2.0f * xScale, -2.0f * yScale, -xScale, yScale),
    }

    CVec4 coeffs[4] = {
      uvScaleOffset, (CVec4&)m_shadowColor,
      CVec4(0, 0, m_blendMode == NDb::SHADOWBLENDMODE_MULCOLOR ? 1.0f : 0.0f, 888.888f),
      CVec4(fadeMul, fadeAdd, m_blurRadius, m_esmPower)
    };

    //statesManager.SetSampler(0, SamplerState::PRESET_CLAMP_POINT(), pDepthTexture);
    pShadowMap->Apply(mViewToLightSpace, coeffs, pDepthTexture);

		// restore states
    statesManager.SetStateDirect(D3DRS_COLORWRITEENABLE, 0x0F); // enable alpha
    statesManager.SetStencilState(STENCILSTATE_IGNORE);
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////
  void ShadowManager::ResizeShadows()
	{
    SAFE_DELETE(pShadowMap);

    if(!lastShadowStat)
      return;

    PushDXPoolGuard dxPool("Renderer");

    if ( shadowMode == NDb::SHADOWMODE_PCF )
    {
      sizeX = fullsizeX;
      sizeY = fullsizeY;
    }
    else
    {
      sizeX = sizeSAX;
      sizeY = sizeSAY;
    }

    if(s_SizeScale < 0.125f)
      s_SizeScale = 0.125f;

    if(s_SizeScale > 2.0f)
      s_SizeScale = 2.0f;

    sizeX *= s_SizeScale;
    sizeY *= s_SizeScale;

    GetDevice()->EvictManagedResources();

    pShadowMap = CreateShadowMap(shadowMode);
    if( pShadowMap && !pShadowMap->Init(sizeX, sizeY, depthBias, biasSlope) )
    {
      delete pShadowMap;
      pShadowMap = 0;
    }
		Verify();
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////
	void ShadowManager::SetParams( const NDb::LightEnvironment* lenv )
	{
    // todo: create default NDb::LightEnvironment and use it if (!lenv) [3/16/2010 smirnov]
		if ( lenv )
		{
			fullsizeX = lenv->fullSizeX;
			fullsizeY = lenv->fullSizeY;
      sizeSAX = lenv->fullSizeSAY;
      sizeSAY = lenv->fullSizeSAY;
      shadowMode = lenv->shadowMode;
      depthBias = lenv->depthBias;
      biasSlope = lenv->biasSlope;

      m_esmPower = lenv->powerOfESM;

      m_shadowColor = lenv->shadowColor;
      m_blendMode = lenv->shadowBlendMode;
      m_shadowLength = lenv->shadowLength;
      m_shadowFarFinal = m_shadowFar = lenv->shadowFar;
      m_shadowFarRange = lenv->shadowFarRange;

      CVec3 lightDirWS;
      ConvertDirection(lenv->shadowDirection, lightDirWS);
      m_lightDirWS = -lightDirWS;
		}
		else // remove this duplication [3/16/2010 smirnov]
		{
			fullsizeX = 2048;
			fullsizeY = 2048;
      sizeSAX = 1024;
      sizeSAY = 1024;

      m_shadowColor = HDRColor(0.0f, 0.0f, 0.1f, 0.25f);
      m_blendMode = NDb::SHADOWBLENDMODE_LERPBYALPHA;
      m_shadowLength = 20.0f;
      m_shadowFar = 60.0f;
      m_shadowFarRange = 10.0f;
		}

    const IConfigManager* const pConfigManager = GetIConfigManager();
    if( !pConfigManager->HasDSM() && pConfigManager->HasDF24() )
      shadowMode = NDb::SHADOWMODE_SAESM;
	}


  void ShadowManager::SetParams(const Params& params)
  {
    fullsizeX = params.fullSizeX;
    fullsizeY = params.fullSizeY;
    sizeSAX = params.fullSizeSAY;
    sizeSAY = params.fullSizeSAY;
    shadowMode = params.shadowMode;
    depthBias = params.depthBias;
    biasSlope = params.biasSlope;

    m_esmPower = params.powerOfESM;

    m_shadowColor = params.shadowColor;
    m_blendMode = params.shadowBlendMode;
    m_shadowLength = params.shadowLength;
    m_shadowFar = params.shadowFar;
    m_shadowFarFinal = params.shadowFar;
    m_shadowFarRange = params.shadowFarRange;

    CVec3 lightDirWS;
    ConvertDirection(params.shadowDirection, lightDirWS);
    m_lightDirWS = -lightDirWS;

    const IConfigManager* const pConfigManager = GetIConfigManager();
    if( !pConfigManager->HasDSM() && pConfigManager->HasDF24() )
      shadowMode = NDb::SHADOWMODE_SAESM;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  static __forceinline void ClampByZMin(CVec3 *_pOut, CVec3 &_companion, float _zMin)
  {
    if(_pOut->z < _zMin) {
      const CVec3 diff = *_pOut - _companion;
      const float t = min(1.f, max(0.f, (_zMin - _companion.z) / diff.z));
      *_pOut = _companion + diff * t;
    }
  }

  static __forceinline void ClampByZMax(CVec3 *_pOut, const CVec3 &_companion, float _zMax)
  {
    if(_pOut->z > _zMax) {
      const CVec3 diff = *_pOut - _companion;
      const float t = min(1.f, max(0.f, (_zMax - _companion.z) / diff.z));
      *_pOut = _companion + diff * t;
    }
  }
/*
  static inline void ClampRay(CVec3 *_pNear, CVec3 *_pFar, float _zMin, float _zMax)
  {
    const CVec3 diff = *_pNear - *_pFar;
    const float diffLength = diff.Length();
    const float bound = 0.01f * diffLength;
    if(diff.z > bound) {
      //ClampByZMax(_pNear, *_pFar, diff, _zMax);
      //ClampByZMin(_pFar, *_pNear,-diff, _zMin);
    }
    //else if(diff.z < -bound) {
    //  ClampByZMin(_pNear, *_pFar, diff, _zMin);
    //  ClampByZMax(_pFar, *_pNear,-diff, _zMax);
    //}
  }
*/

  static inline void ClampFrustum(CVec3(&_frustum)[8], float _hMin, float _hMax, bool _lookingDown)
  {
    if(_hMax < 12.0f) // Temporary hack
      _hMax = 12.0f;

    static const int indices[8] = {0, 1, 2, 3,
                                   5, 6, 7, 4};

    const int  *upIndices  = _lookingDown ? indices : indices + 4; 
    const int *downIndices = _lookingDown ? indices + 4 : indices; 

    if(_frustum[upIndices[0]].z >= _hMax && _frustum[upIndices[1]].z >= _hMax &&
       _frustum[upIndices[2]].z >= _hMax && _frustum[upIndices[3]].z >= _hMax)
    {
      ClampByZMax(&_frustum[upIndices[0]], _frustum[downIndices[0]], _hMax);
      ClampByZMax(&_frustum[upIndices[1]], _frustum[downIndices[1]], _hMax);
      ClampByZMax(&_frustum[upIndices[2]], _frustum[downIndices[2]], _hMax);
      ClampByZMax(&_frustum[upIndices[3]], _frustum[downIndices[3]], _hMax);
    }

    if(_frustum[downIndices[0]].z <= _hMin && _frustum[downIndices[1]].z <= _hMin &&
       _frustum[downIndices[2]].z <= _hMin && _frustum[downIndices[3]].z <= _hMin)
    {
      ClampByZMin(&_frustum[downIndices[0]], _frustum[upIndices[0]], _hMin);
      ClampByZMin(&_frustum[downIndices[1]], _frustum[upIndices[1]], _hMin);
      ClampByZMin(&_frustum[downIndices[2]], _frustum[upIndices[2]], _hMin);
      ClampByZMin(&_frustum[downIndices[3]], _frustum[upIndices[3]], _hMin);
    }
  }


  static void CreateLightFrustum(/*out*/ CVec3 *pUp, CVec3(&_frustumPointsWS)[8], float *_pzNear,
                                 /*in-out*/ float *_phMin, float* _phMax,
                                 const D3DXVECTOR3& _lightDir, const SceneConstants &_viewSceneConsts, float _zFar)
  {
    D3DXMATRIX viewProjectionD3D, invViewProjectionD3D;
    fromSHMatrix(&viewProjectionD3D, _viewSceneConsts.viewProjection);
    D3DXMatrixInverse(&invViewProjectionD3D, NULL, &viewProjectionD3D);

    static D3DXVECTOR3 cornersCS[8] = {
      D3DXVECTOR3(-1.f, -1.f, 0.f), D3DXVECTOR3( 1.f, -1.f, 0.f), D3DXVECTOR3(1.f,  1.f, 0.f), D3DXVECTOR3(-1.f, 1.f, 0.f),
      D3DXVECTOR3(-1.f,  1.f, 1.f), D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3( 1.f, 1.f, 1.f)
    };

    {
      const SHMatrix &proj = _viewSceneConsts.projection;
      const float zFar = (_zFar * proj._33 + proj._34) / (_zFar * proj._43 + proj._44);
      cornersCS[4].z = cornersCS[5].z = cornersCS[6].z = cornersCS[7].z = zFar;
    }
    D3DXVec3TransformCoordArray(AsD3D(_frustumPointsWS), Vec3size, cornersCS, Vec3size, &invViewProjectionD3D, 8);

    CVec3 centerNear = CVec3(invViewProjectionD3D.m[3]) / invViewProjectionD3D._44 - _viewSceneConsts.campos;

    ClampFrustum(_frustumPointsWS, *_phMin, *_phMax, centerNear.z < 0);

    if(_pzNear) {
      const float zNear = centerNear.Length();
      const float invZNear = 1.f / zNear;
      float zMax = FLT_MIN, zMin = FLT_MAX;
      for(int i = 0; i < 8; ++i) {
        const float z = centerNear.Dot( _frustumPointsWS[i] - _viewSceneConsts.campos );
        ASSERT(z > 0.f);
        if(zMin > z)
          zMin = z;
        if(zMax < z)
          zMax = z;
      }
      *_phMin = zMin * invZNear;
      *_phMax = zMax * invZNear;
      *_pzNear = zNear;
    }

    if(pUp) {
      const CVec3 vUpWS = _frustumPointsWS[4] - _frustumPointsWS[5] + _frustumPointsWS[7] - _frustumPointsWS[6];
      CVec3 vUp(vUpWS);
      CVec3 lightDir( _lightDir );
      Normalize(&lightDir);

      vUp -= lightDir * vUp.Dot(lightDir);
      Normalize(&vUp);
      *pUp = vUp;
    }
  }


  void ShadowManager::ComputeCastersAABB(AABB *_pCastersAABB, bool _buildProj)
  {
    BoundingBox frustumAABB(m_frustumPointsLS);
#ifdef _DEBUG
    D3DXVECTOR3 bbSize = frustumAABB.maxPt - frustumAABB.minPt;
    ASSERT( !ALMOST_ZERO(bbSize.x) && !ALMOST_ZERO(bbSize.y) && !ALMOST_ZERO(bbSize.z) );
#endif // _DEBUG
    frustumAABB.minPt.z -= m_shadowLength;
    m_casterBoundsLS.Set( CVec3(frustumAABB.minPt), CVec3(frustumAABB.maxPt) );

    D3DXMatrixInverse( &m_light2World, 0, &m_world2Light );
    // find casters area in World Space
    BoundingBox casterBoundsWS;
    XFormBoundingBox(&casterBoundsWS, frustumAABB, m_light2World);
    _pCastersAABB->Set( CVec3(casterBoundsWS.minPt), CVec3(casterBoundsWS.maxPt) );

    if(_buildProj) // build orthogonal projection matrix
      D3DXMatrixOrthoOffCenterLH(&m_light2LightProj, frustumAABB.minPt.x, frustumAABB.maxPt.x, 
        frustumAABB.maxPt.y, frustumAABB.minPt.y, frustumAABB.minPt.z, frustumAABB.maxPt.z);
  }


  //-----------------------------------------------------------------------------
  // Name: BuildLiSPSMProjectionMatrix
  // Desc: Builds a light-space perspective shadow map projection matrix
  //       Much thanks to Oles Shishkovstov, who provided the original implementation
  //-----------------------------------------------------------------------------
  void ShadowManager::BuildLSPSMProjectionMatrices(/*out*/ AABB *_pCastersAABB, const SceneConstants &_viewSceneConsts,
                                                   float _minZ, float _maxZ)
  {
    const D3DXVECTOR3* const pViewDir = AsD3D( &_viewSceneConsts.view.GetZ().AsVec3D() );
    const float cosGamma = D3DXVec3Dot(&m_lightDirWS, pViewDir);

    if(fabsf(cosGamma) >= 0.97f) { // degenerates to uniform shadow map
      BuildTightOrthoMatrices(_pCastersAABB, _viewSceneConsts, _minZ, _maxZ);
      return;
    }

    ////  compute shadow casters & receivers
    //ComputeVirtualCameraParameters( );

    //  build the convex body B by stretching the view frustum in light direction
    const int numFrustumPoints = 8;
    CVec3 frustumPointsWS[numFrustumPoints];
    float zNear;
    CreateLightFrustum(NULL, frustumPointsWS, &zNear, &_minZ, &_maxZ, m_lightDirWS, _viewSceneConsts, m_shadowFar);

    const D3DXVECTOR3 lightShift = m_lightDirWS * m_shadowLength * s_fShadowLengthCoeff;
    const int numBodyPoints = numFrustumPoints*2;
    D3DXVECTOR3 bodyB[numBodyPoints];
    for(int i = 0; i < numFrustumPoints; ++i)
      bodyB[i+numFrustumPoints] = (bodyB[i] = frustumPointsWS[i]) + lightShift;

    //  compute the "light-space" basis, using the algorithm described in the paper
    //  note:  since bodyB is defined in eye space, all of these vectors should also be defined in eye space
    D3DXVECTOR3 leftVector, upVector, viewVector;

    const D3DXVECTOR3 eyeVector( 0.f, 0.f, -1.f );  // eye vector in eye space is always -Z
    D3DXVec3TransformNormal(&upVector, &m_lightDirWS, &m_world2View);  // lightDir is defined in world space, so xform it
    //  note: lightDir points away from the scene, so it is already the "negative" up direction; no need to re-negate it.
    D3DXVec3Cross( &leftVector, &upVector, &eyeVector );
    D3DXVec3Normalize( &leftVector, &leftVector );
    D3DXVec3Cross( &viewVector, &upVector, &leftVector );
    if(!s_bUnitCubeClip)
      leftVector = -leftVector;

    D3DXMATRIX view2Light(leftVector.x, upVector.x, viewVector.x, 0.f,
                          leftVector.y, upVector.y, viewVector.y, 0.f,
                          leftVector.z, upVector.z, viewVector.z, 0.f,
                          0.f,          0.f,        0.f,          1.f);

    //  rotate all points into this new basis
    D3DXMATRIX world2Light;
    D3DXMatrixMultiply(&world2Light, &m_world2View, &view2Light);
    D3DXVec3TransformCoordArray(bodyB, Vec3size, bodyB, Vec3size, &world2Light, numBodyPoints);

    BoundingBox lightSpaceBox(bodyB, numBodyPoints);
    D3DXVECTOR3 lightSpaceOrigin;
    //  for some reason, the paper recommended using the x coordinate of the xformed viewpoint as
    //  the x-origin for lightspace, but that doesn't seem to make sense...  instead, we'll take
    //  the x-midpt of body B (like for the Y axis)
    lightSpaceBox.Centroid( &lightSpaceOrigin );
    const float sinGamma = sqrtf( 1.f - cosGamma*cosGamma );

    //  use average of the "real" near/far distance and the optimized near/far distance to get a more pleasant result
    const float Nopt0 = _minZ + sqrtf(_minZ * _maxZ);
    const float Nopt1 = zNear + sqrtf(zNear * _viewSceneConsts.farplane);
    float fLSPSM_Nopt = (Nopt0 + Nopt1) / (2.f*sinGamma);
    //  now use the weighting to scale between 0.1 and the computed Nopt
    float Nopt = 0.1f + s_fLSPSM_NoptWeight * fLSPSM_Nopt; // Note - we never set Nopt less than 0.1

    lightSpaceOrigin.z = lightSpaceBox.minPt.z - Nopt;

    //  xlate all points in lsBodyB, to match the new light-space origin
    D3DXMATRIX lsTranslate;  
    D3DXMatrixTranslation(&lsTranslate, -lightSpaceOrigin.x, -lightSpaceOrigin.y, -lightSpaceOrigin.z);
    D3DXMatrixMultiply( &view2Light, &view2Light, &lsTranslate );
    D3DXMatrixMultiply(&m_world2Light, &m_world2View, &view2Light);

    // compute the fov and aspect ratio
    const float boxSize = CVec3(lightSpaceBox.maxPt - lightSpaceBox.minPt).Length();
    float maxx=0.f, maxy=0.f, maxz=0.f;
    for(int i = 0; i < numBodyPoints; ++i) {
      D3DXVECTOR3 tmp = bodyB[i] - lightSpaceOrigin;
      ASSERT( fabsf(tmp.z) > 0.001f*boxSize );
      maxx = max(maxx, fabsf(tmp.x / tmp.z));
      maxy = max(maxy, fabsf(tmp.y / tmp.z));
      maxz = max(maxz, tmp.z);
    }
#ifdef _DEBUG
    float fovy = atanf(maxy);fovy;
    float fovx = atanf(maxx);fovx;
#endif // _DEBUG

    { // compute light projection matrix
      D3DXMATRIX lsPerspective;  
      D3DXMatrixPerspectiveLH( &lsPerspective, 2.f*maxx*Nopt, 2.f*maxy*Nopt, Nopt, maxz );

      // now rotate the entire post-projective cube, so that the shadow map is looking down the Y-axis
      static const D3DXMATRIX lsPermute(1.f,  0.f,  0.f,  0.f,
                                        0.f,  0.f, -1.f,  0.f,
                                        0.f,  1.f,  0.f,  0.f,
                                        0.f, -0.5f, 1.5f, 1.f);

      D3DXMATRIX lsOrtho;
      D3DXMatrixOrthoLH( &lsOrtho, 2.f, 1.f, 0.5f, 2.5f );

      D3DXMatrixMultiply(&lsPerspective, &lsPerspective, &lsPermute);
      D3DXMatrixMultiply(&m_light2LightProj, &lsPerspective, &lsOrtho);
    }

    if( s_bUnitCubeClip ) {
      D3DXMATRIX world2LightProj;
      D3DXMatrixMultiply(&world2LightProj, &m_world2Light, &m_light2LightProj);

      D3DXMatrixMultiply(&lsTranslate, &lsTranslate, &m_light2LightProj);
      D3DXVec3TransformCoordArray(bodyB, Vec3size, bodyB, Vec3size, &lsTranslate, numBodyPoints);
      // rotate post-projection space for more tight bounds
      D3DXVECTOR3 vUp = bodyB[7] - bodyB[4];
      D3DXVec3Normalize(&vUp, &vUp);

      D3DXMATRIX rotation(vUp.x,  vUp.y, 0.f, 0.f,
                          vUp.y, -vUp.x, 0.f, 0.f,
                          0.f,    0.f,   1.f, 0.f,
                          0.f,    0.f,   0.f, 1.f);

      D3DXVec2TransformNormalArray((D3DXVECTOR2*)bodyB, Vec3size, (D3DXVECTOR2*)bodyB, Vec3size, &rotation, numBodyPoints);

      BoundingBox bodyBox(bodyB, numBodyPoints);
      //bodyBox.maxPt.x = min( 1.f, bodyBox.maxPt.x );
      //bodyBox.minPt.x = max(-1.f, bodyBox.minPt.x );
      //bodyBox.maxPt.y = min( 1.f, bodyBox.maxPt.y );
      //bodyBox.minPt.y = max(-1.f, bodyBox.minPt.y );
      const float boxWidth  = bodyBox.maxPt.x - bodyBox.minPt.x;
      const float boxHeight = bodyBox.maxPt.y - bodyBox.minPt.y;
      const float boxDepth  = bodyBox.maxPt.z - bodyBox.minPt.z;

      if( !ALMOST_ZERO(boxWidth) && !ALMOST_ZERO(boxHeight) && !ALMOST_ZERO(boxDepth) )
      {
        const float boxX = ( bodyBox.maxPt.x + bodyBox.minPt.x ) * 0.5f;
        const float boxY = ( bodyBox.maxPt.y + bodyBox.minPt.y ) * 0.5f;

        //static const float zMin = 9.e-2f;
        static const float zMin = 0.f;
        const float zScale = s_doZClip ? (1 - zMin)/boxDepth : 1.f;
        const float zShift = s_doZClip ? (zMin*bodyBox.maxPt.z - bodyBox.minPt.z)/boxDepth : 0.f;

        D3DXMATRIX clipMatrix(2.f/boxWidth,       0.f,                0.f,    0.f,
                              0.f,                2.f/boxHeight,      0.f,    0.f,
                              0.f,                0.f,                zScale, 0.f,
                             -2.f*boxX/boxWidth, -2.f*boxY/boxHeight, zShift, 1.f);
        D3DXMatrixMultiply( &rotation, &rotation, &clipMatrix );
        D3DXMatrixMultiply( &m_light2LightProj, &m_light2LightProj, &rotation );
      }
    }

    D3DXMatrixMultiply( &m_world2LightProj, &m_world2Light, &m_light2LightProj );
#ifdef _DEBUG
    {
      D3DXVECTOR3 bodyPtsWS[numBodyPoints];
      for(int i = 0; i < numFrustumPoints; ++i)
        bodyPtsWS[i+numFrustumPoints] = (bodyPtsWS[i] = frustumPointsWS[i]) + lightShift;

      D3DXVec3TransformCoordArray(bodyPtsWS, Vec3size, bodyPtsWS, Vec3size, &m_world2LightProj, numBodyPoints);
      for(int i = 0; i < numBodyPoints; ++i) {
        ASSERT( (fabsf(bodyPtsWS[i].x) <= 1.01f) && (fabsf(bodyPtsWS[i].y) <= 1.01f) );
        ASSERT( bodyPtsWS[i].z <= 1.01f && bodyPtsWS[i].z > -0.01f );
      }
    }
#endif // _DEBUG

    m_frustumPointsLS.resize(numFrustumPoints);
    D3DXVec3TransformCoordArray(&m_frustumPointsLS[0], Vec3size, AsD3D(frustumPointsWS), Vec3size, &m_world2Light, numFrustumPoints);

    ComputeCastersAABB(_pCastersAABB);
  }


  void ShadowManager::BuildTightOrthoMatrices(/*out*/ AABB *_pCastersAABB, const SceneConstants &_viewSceneConsts,
                                              float _minZ, float _maxZ)
  {
    CVec3 frustumPoints[8];
    CVec3 vUp;
    CreateLightFrustum(&vUp, frustumPoints, NULL, &_minZ, &_maxZ, m_lightDirWS, _viewSceneConsts, m_shadowFar);

    D3DXVECTOR3 lightAt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 lightDir(-m_lightDirWS);
    D3DXMatrixLookAtLH(&m_world2Light, &lightAt, &lightDir, (const D3DXVECTOR3*)&vUp);

    D3DXVec3TransformCoordArray(&m_frustumPointsLS[0], Vec3size, (D3DXVECTOR3*)frustumPoints, Vec3size, &m_world2Light, 8);
    
    ComputeCastersAABB(_pCastersAABB, true);

    // prepare all matrices
    D3DXMatrixMultiply( &m_world2LightProj, &m_world2Light, &m_light2LightProj );

    //Matrix43 m( frustumPoints[0] );
    //DebugRenderer::DrawCross3D( m, 0.2f, 0.2f, Color(0xFFFF0000UL), true );
    //m.SetTranslation(frustumPoints[1]);
    //DebugRenderer::DrawCross3D( m, 0.2f, 0.2f, Color(0xFF00FF00UL), true );
    //m.SetTranslation(frustumPoints[2]);
    //DebugRenderer::DrawCross3D( m, 0.2f, 0.2f, Color(0xFF0000FFUL), true );
    //m.SetTranslation(frustumPoints[3]);
    //DebugRenderer::DrawCross3D( m, 0.2f, 0.2f, Color(0xFFFFFF00UL), true );

    //m.SetTranslation(frustumPoints[4]);
    //DebugRenderer::DrawCross3D( m, 20.2f, 20.2f, Color(0xFFFF00FFUL), false );
    //m.SetTranslation(frustumPoints[5]);
    //DebugRenderer::DrawCross3D( m, 20.2f, 20.2f, Color(0xFF00FFFFUL), false );
    //m.SetTranslation(frustumPoints[6]);
    //DebugRenderer::DrawCross3D( m, 20.2f, 20.2f, Color(0xFFFFFFFFUL), false );
    //m.SetTranslation(frustumPoints[7]);
    //DebugRenderer::DrawCross3D( m, 20.2f, 20.2f, Color(0xFF000000UL), false );
  }

  void ShadowManager::BuildLightMatrices( /*out*/ SceneConstants* lightSceneConsts, AABB *_pCasterAABB,
                                          const SceneConstants &_viewSceneConsts, const CVec3& _frustumEdge,
                                          float _minHeight, float _maxHeight )
  {
    NI_PROFILE_FUNCTION
		//Verify();
		m_shadowReceiverPointsVS.clear();

// 		CVec3 minpos = _minpos;
// 		CVec3 maxpos = _maxpos;

// 		render_ShadowMinPnt.SetValue( minpos );
// 		render_ShadowMaxPnt.SetValue( maxpos );

//		CVec3 minpntVS;
// 		_viewSceneConsts.view.RotateVector( &minpntVS, minpos );
//		CVec3 maxpntVS;
// 		_viewSceneConsts.view.RotateVector( &maxpntVS, maxpos );

// 		render_ShadowMinPnt2.SetValue( minpntVS );
// 		render_ShadowMinPnt2.SetValue( maxpntVS );

// 		minpntVS = CVec3( -fRod*2.f, -fRod*2.f, 0/*-fRod*2.f*/ );
// 		maxpntVS = CVec3( fRod*2.f, fRod*2.f, fRod*2.f );

// 		render_ShadowMinRod.SetValue( minpntVS );
// 		render_ShadowMinRod.SetValue( maxpntVS );

    if( s_ZMinFromTerrain && IsValid(shadowReceiverVolume) )
    {
      //NI_PROFILE_BLOCK("receiversAABB")

      AABB receiversAABB;
      shadowReceiverVolume->GetBoundsInCamera( _viewSceneConsts.cameraAABB, receiversAABB );

      if( receiversAABB.IsValid() )
      {
        _minHeight = receiversAABB.center.z - receiversAABB.halfSize.z;

        const float maxZ = receiversAABB.center.z + receiversAABB.halfSize.z;
        if(maxZ > _maxHeight)
          _maxHeight = maxZ;
      }
    }

    //m_lightDirWS = -_viewSceneConsts.shadowDirection.AsVec3D();
    fromSHMatrix( &m_world2View, _viewSceneConsts.view );
    fromSHMatrix( &m_view2Proj, _viewSceneConsts.projection );

    switch(s_FrustumType)
    {
    case 1:
      BuildTightOrthoMatrices(_pCasterAABB, _viewSceneConsts, _minHeight, _maxHeight);
      break;
    case 2:
      BuildLSPSMProjectionMatrices(_pCasterAABB, _viewSceneConsts, _minHeight, _maxHeight);
      break;
    default:
      {
        Matrix43 invViewMtx;
        Matrix43 viewMtx;
        invViewMtx.Set( _viewSceneConsts.invView );
        viewMtx.Set( _viewSceneConsts.view );

        CVec3 testDirection1 = Transform( CVec3(0,0,0.f), invViewMtx );
        CVec3 testDirection2 = Transform( CVec3(0,0,1.f), invViewMtx );

        CVec3 dir = _frustumEdge;

        m_shadowFarFinal = m_shadowFar;

        if ( shadowTest )
        {
          CVec3 testVector1 = CVec3(0,0,0.5f);
          testVector1 = Transform( testVector1, invViewMtx );          

          if ( testVector1.z > _minHeight )
            m_shadowFarFinal = Min( m_shadowFar, (testVector1.z - _minHeight) * 3.0f );
        }

        dir *= m_shadowFarFinal;

        render_ShadowMinZ.SetValue( _minHeight );

        CVec3 shifts[4] = { CVec3(1,1,1), CVec3(1,-1,1), CVec3(-1,-1,1), CVec3(-1,1,1) };

        for ( int i = 0; i < 4; ++i )
        {
          CVec3 point = CVec3( dir.x * shifts[i].x, dir.y * shifts[i].y, dir.z * shifts[i].z );

          if ( shadowTest )
          {
            //           CVec3 testVector1 = CVec3(0,0,0);
            //           CVec3 testVector2 = point;
            // 
            //           testVector1 = Transform( testVector1, invViewMtx );          
            //           testVector2 = Transform( testVector2, invViewMtx );          
            // 
            //           if ( testVector1.z > minZ && testVector2.z < minZ )
            //           {
            //             float factor = fabs( testVector1.z - minZ ) / fabs ( testVector1.z - testVector2.z );
            //             point *= factor * 1.2f;
            //           }
          }

          m_shadowReceiverPointsVS.push_back( D3DXVECTOR3( point.x, point.y, point.z ) );
        }

        m_shadowReceiverPointsVS.push_back( D3DXVECTOR3(  0.0f,  0.0f,  0.0f ) );

        BuildOrthoShadowProjectionMatrix(_pCasterAABB);
      }
    }

 		fromD3DMatrix( &lightSceneConsts->view, m_world2Light );
 		fromD3DMatrix( &lightSceneConsts->projection, m_light2LightProj );
		lightSceneConsts->Update();
	}

	void ShadowManager::BuildOrthoShadowProjectionMatrix(/*out*/ AABB *_pCastersAABB)
	{
		//Verify();

		D3DXVECTOR3 lightDirVS;
		D3DXVec3TransformNormal(&lightDirVS, &m_lightDirWS, &m_world2View);

    // choose "up" axis
    D3DXVECTOR3 axisVS;
		if ( fabsf(lightDirVS.y) > 0.99f )
			axisVS = D3DXVECTOR3(0.f, 0.f, 1.f); // Z-axis
		else
			axisVS = D3DXVECTOR3(0.f, 1.f, 0.f); // Y-axis

    // create Light Space matrix
    D3DXMATRIX view2Light;
    D3DXVECTOR3 centerVS(-lightDirVS);
    D3DXVECTOR3 lightPointVS(0.0f, 0.0f, 0.0f);
		D3DXMatrixLookAtLH( &view2Light, &lightPointVS, &centerVS, &axisVS );

    // transform frustum to Light Space
    static vector<D3DXVECTOR3> shadowReceiverPointsLS; 
    shadowReceiverPointsLS.resize(m_shadowReceiverPointsVS.size());
    D3DXVec3TransformCoordArray( &shadowReceiverPointsLS[0], Vec3size, &m_shadowReceiverPointsVS[0], Vec3size,
                                 &view2Light, m_shadowReceiverPointsVS.size() );

    // find area with casters and correct Light Space
    BoundingBox casterBoundsLS(shadowReceiverPointsLS);
    casterBoundsLS.minPt.z -= m_shadowLength; // extrude bbox
    m_casterBoundsLS.Set(CVec3(casterBoundsLS.minPt.x, casterBoundsLS.minPt.y, casterBoundsLS.minPt.z), 
      CVec3(casterBoundsLS.maxPt.x, casterBoundsLS.maxPt.y, casterBoundsLS.maxPt.z));

    // build orthogonal projection matrix
		D3DXMatrixOrthoOffCenterLH( &m_light2LightProj, casterBoundsLS.minPt.x, casterBoundsLS.maxPt.x,
			casterBoundsLS.minPt.y, casterBoundsLS.maxPt.y, casterBoundsLS.minPt.z, casterBoundsLS.maxPt.z );

    // prepare all matrices
		D3DXMatrixMultiply( &m_world2Light, &m_world2View, &view2Light );
		D3DXMatrixMultiply( &m_world2LightProj, &m_world2Light, &m_light2LightProj );
		D3DXMatrixInverse( &m_light2World, 0, &m_world2Light );

    // find casters area in World Space
    BoundingBox casterBoundsWS;
    XFormBoundingBox(&casterBoundsWS, casterBoundsLS, m_light2World);
    _pCastersAABB->Set( CVec3(casterBoundsWS.minPt), CVec3(casterBoundsWS.maxPt) );

    //////////////////////////////////////////////////////////////////////////////////////
    /*
    {
      vector<D3DXVECTOR3> shadowReceiverPointsWS(shadowReceiverPointsLS.size());
      for (int i = 0, n = shadowReceiverPointsLS.size(); i < n; i++)
        D3DXVec3TransformCoord(&shadowReceiverPointsWS[i], &shadowReceiverPointsLS[i], &m_light2World);
      Render::Color c0(0,255,0), c0dark(0,63,0);
      for (int i = 1, n = shadowReceiverPointsWS.size(); i < n; i++)
      {
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&shadowReceiverPointsWS[0], *(CVec3*)&shadowReceiverPointsWS[i], c0dark, c0dark, false);
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&shadowReceiverPointsWS[0], *(CVec3*)&shadowReceiverPointsWS[i], c0, c0, true);

        int j = (i == n - 1) ? 1 : i + 1;
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&shadowReceiverPointsWS[i], *(CVec3*)&shadowReceiverPointsWS[j], c0dark, c0dark, false);
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&shadowReceiverPointsWS[i], *(CVec3*)&shadowReceiverPointsWS[j], c0, c0, true);
      }
      vector<D3DXVECTOR3> casterBoundsPointsLS(8);
      casterBoundsPointsLS[0] = casterBoundsLS.minPt;
      casterBoundsPointsLS[1].x = casterBoundsLS.maxPt.x;
      casterBoundsPointsLS[1].y = casterBoundsLS.minPt.y;
      casterBoundsPointsLS[1].z = casterBoundsLS.minPt.z;
      casterBoundsPointsLS[2].x = casterBoundsLS.maxPt.x;
      casterBoundsPointsLS[2].y = casterBoundsLS.maxPt.y;
      casterBoundsPointsLS[2].z = casterBoundsLS.minPt.z;
      casterBoundsPointsLS[3].x = casterBoundsLS.minPt.x;
      casterBoundsPointsLS[3].y = casterBoundsLS.maxPt.y;
      casterBoundsPointsLS[3].z = casterBoundsLS.minPt.z;
      casterBoundsPointsLS[4].x = casterBoundsLS.minPt.x;
      casterBoundsPointsLS[4].y = casterBoundsLS.minPt.y;
      casterBoundsPointsLS[4].z = casterBoundsLS.maxPt.z;
      casterBoundsPointsLS[5].x = casterBoundsLS.maxPt.x;
      casterBoundsPointsLS[5].y = casterBoundsLS.minPt.y;
      casterBoundsPointsLS[5].z = casterBoundsLS.maxPt.z;
      casterBoundsPointsLS[6].x = casterBoundsLS.maxPt.x;
      casterBoundsPointsLS[6].y = casterBoundsLS.maxPt.y;
      casterBoundsPointsLS[6].z = casterBoundsLS.maxPt.z;
      casterBoundsPointsLS[7].x = casterBoundsLS.minPt.x;
      casterBoundsPointsLS[7].y = casterBoundsLS.maxPt.y;
      casterBoundsPointsLS[7].z = casterBoundsLS.maxPt.z;
      vector<D3DXVECTOR3> casterBoundsPointsWS(casterBoundsPointsLS.size());
      for (int i = 0, n = casterBoundsPointsLS.size(); i < n; i++)
        D3DXVec3TransformCoord(&casterBoundsPointsWS[i], &casterBoundsPointsLS[i], &m_light2World);
      Render::Color c1(0,255,255), c1dark(0,63,63);
      for (int i = 0, n = casterBoundsPointsWS.size(); i < n; i++)
      {
        int inext = (i + 1) % 4 + i / 4 * 4;
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&casterBoundsPointsWS[i], *(CVec3*)&casterBoundsPointsWS[inext], c1dark, c1dark, false);
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&casterBoundsPointsWS[i], *(CVec3*)&casterBoundsPointsWS[inext], c1, c1, true);
      }
      for (int i = 0, n = casterBoundsPointsWS.size() / 2; i < n; i++)
      {
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&casterBoundsPointsWS[i], *(CVec3*)&casterBoundsPointsWS[i+n], c1dark, c1dark, false);
        Render::DebugRenderer::DrawLine3D(*(CVec3*)&casterBoundsPointsWS[i], *(CVec3*)&casterBoundsPointsWS[i+n], c1, c1, true);
      }

      Render::DebugRenderer::DrawAABB(casterAABB, Render::Color(63,0,0), false);
      Render::DebugRenderer::DrawAABB(casterAABB, Render::Color(255,0,0), true);
    }
    */
	}
/*
	void ShadowManager::BuildOrthoShadowProjectionMatrixCrap()
	{
		Verify();
		CVec3 from( 0.0f, -6.f, 10.f );
		CVec3 to( from.x, from.y+0.3f, from.z-0.5f );
		CVec3 up( 0.f, 1.f, 0.f );

		D3DXVECTOR3 d3dx_from( from.x, from.y, from.z );
		D3DXVECTOR3 d3dx_to( to.x, to.y, to.z );
		D3DXVECTOR3 d3dx_up( -up.x, -up.y, -up.z );
		D3DXMatrixLookAtLH( &m_world2Light, &d3dx_from, &d3dx_to, &d3dx_up );
		D3DXMatrixOrthoLH( &m_light2LightProj, 20.0f, 20.0f, -10.0f, 40.0f );
		D3DXMatrixMultiply( &m_world2LightProj, &m_world2Light, &m_light2LightProj );
	}
*/
	void ShadowManager::Reload()
	{
		//Verify();
		lastShadowStat = false;
    ResizeShadows();
	}

	void ShadowManager::Verify()
	{
		NI_ASSERT( fullsizeX >= 4 && fullsizeX <= 4096, "Bad shadow params" );
		NI_ASSERT( fullsizeY >= 4 && fullsizeY <= 4096, "Bad shadow params" );

		NI_ASSERT( pShadowMap, "Bad shadow params" );
	}

	static bool reload( const char *name, const vector<wstring> &params )
	{
		ShadowManager::Get()->Reload();
    return true;
	}

  static bool setShadowMode( const char *name, const vector<wstring> &params )
  {
    if ( params.size() != 1 )
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "usage: shadowMode <modeID>" << endl;
      return false;
    }

    int mode = NGlobal::VariantValue( params[0] ).GetInt64();

    ShadowManager::Get()->SetMode( NDb::ShadowMode( mode ) );
    return true;
  }

  void ShadowManager::SetMode( NDb::ShadowMode _shadowMode )
  {
    if ( shadowMode != _shadowMode)
    {
      shadowMode = _shadowMode;
      ResizeShadows();
    }
  }

	REGISTER_CMD( shadowReload, reload );
  REGISTER_CMD( shadowMode, setShadowMode );
};

