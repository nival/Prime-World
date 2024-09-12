#include "stdafx.h"
#include "batch.h"
#include "WaterMesh.h"
#include "WaterManager.h"
#include "ShadowManager.h"
#include "GlobalMasks.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Render
{
  DECLARE_NULL_RENDER_FLAG
  DECLARE_INSTANCE_COUNTER(WaterMesh);

  void WaterMesh::Initialize( const Matrix43& worldMatrix_, const NDb::DBWaterSceneComponent* pDBComponent, const NDb::DBWaterInfo* pParams )
  {
    StaticMesh::Initialize( worldMatrix_, pDBComponent );

    // Save texture
    if(!RENDER_DISABLED) {
      pGradients = pParams->gradientMap.GetPtr() ? pParams->gradientMap->Load().GetPtr() : Render::GetWhiteTexture2D().GetPtr();
      pCaustics = pParams->causticsMap.GetPtr() ? pParams->causticsMap->Load().GetPtr() : Render::GetWhiteTexture2D().GetPtr();
    }

    // Save parameters
    //level = pDBComponent->waterLevel;
    level = localAABB.center.z;
    tiling = 0.05f * pParams->tiling;
    shininess = pParams->shininess;
    ripplesFactor = pParams->ripples > 0.0f ? 1.0f / pParams->ripples : 0.0f;
    ripplesHeight = pParams->ripplesHeight;
    refraction = pParams->refraction > 0.0f ? 1.0f / pParams->refraction : 0.0f;
    causticsTiling = 0.05f * pParams->causticsTiling;
    causticsIntensity = pParams->causticsIntensity;
    scaleH0 = pParams->depth > 0.0f ? 1.0f / pParams->depth : 1e38f;
    scaleZ0 = pParams->distance > 0.0f ? -(float)M_LN2 / pParams->distance : -1e38f;
    scaleH0refl = pParams->depthReflect > 0.0f ? 1.0f / pParams->depthReflect : 1e38f;
    speed = pParams->speed;

    // Temporarily init convexes as AABB
    convexes.Create(pDBComponent->aabb);
  }

  void WaterMesh::RenderToQueue( BatchQueue& queue )
  {
    // Don't render to reflection (at least for now)
    if ( WaterManager::Get()->IsReflectionRendering() || ShadowManager::Get()->IsShadowRendering() )
      return;

    // Only when above water surface
		if ( SceneConstants::Global().invView.zw > GetLevel() )
      WaterManager::Get()->AddWaterMesh( *this );

    // No render at this point actually
  }

  void WaterMesh::RenderToQueuePostponed( BatchQueue& queue )
  {
    int primitivesCount = pMeshGeom->primitives.size();
    for ( int i = 0; i < primitivesCount; ++i )
      queue.Push( NDb::MATERIALPRIORITY_MESHESOPAQUE, this, pMeshGeom->primitives[i], i, Get(materials[i]) );
  }

  void WaterMesh::PrepareRendererAfterMaterial( unsigned int elementNumber ) const 
  {
    if(GetRuntimePins().RenderModeValue != NDb::RENDERMODEPIN_RENDERNORMAL)
    {
      SHMatrix world;
      Copy( &world, worldMatrix );
      GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, world );
      return;
    }

    ConstantProtectionBlock block(CCONTEXT_WATER);

    StaticMesh::PrepareRendererAfterMaterial( elementNumber );

    // Rendering water surface setup
    float t = Render::SceneConstants::Global().renderTime;
    Render::GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, CVec4(causticsIntensity, shininess, 0.4f * ripplesFactor, ripplesHeight ) );
    Render::GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST1, CVec4(scaleH0, scaleZ0, refraction, scaleH0refl) );
    Render::GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST6, CVec4(ripplesHeight, 0.f, 0.f, 0.f) );
    Render::GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST2, CVec4(tiling, tiling, speed.x * t, speed.y * t));
    Render::GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST3, CVec4(causticsTiling, causticsTiling, speed.x * t, speed.y * t));

    // Set deep gradients texture
    GetStatesManager()->SetSampler(4, Render::SamplerState::PRESET_CLAMP_BILINEAR(), pGradients);
    // Set caustics texture
    GetStatesManager()->SetSampler(5, Render::SamplerState::PRESET_WRAP_BILINEAR(), pCaustics);
  }
};