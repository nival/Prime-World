#include "stdafx.h"
#include "WaterMathTex.h"
#include "GlobalMasks.h"
#include "ImmediateRenderer.h"
#include "smartrenderer.h"

static float g_layerAmplitude1 = 1.0f;
static float g_layerAmplitude2 = 0.5f;
static float g_layerAmplitude3 = 0.3f;
static float g_layerVelocity1 = 0.1f;
static float g_layerVelocity2 = 0.1f;
static float g_layerVelocity3 = 0.1f;

namespace Render
{
namespace Water
{

// *******************************************************************
// methods 
ScrollTexture :: ScrollTexture( int nNumMipmaps, Render::ERenderFormat format )
{
  baseHeightmapTexture = Load2DTextureFromFile( "Tech/Default/Waterhmap.dds" );

  hTexture     = CreateRenderTexture2D(256, 256, FORMAT_R32F);
  hDxDyTexture = CreateRenderTexture2D(256, 256, format);
  texDuDv      = CVec2( 1.0f / 256.0f, 1.0f / 256.0f );
 
  InitLayersParams();
}

void ScrollTexture :: InitLayersParams()
{
  float n1[ 2 ] = { 1, 3 }, n2[ 2 ] = { 2, 2 };

  for( int i = 0; i != ARRAY_SIZE( rotationMatrices ); ++i )
    rotationMatrices[ i ] = CVec4( n1[ i ], -n2[ i ], n2[ i ], n1[ i ] );
}

void ScrollTexture :: Update( float time )
{
  curTime = time;

  layersVelocities = CVec3( g_layerVelocity1, g_layerVelocity2, g_layerVelocity3 );
  layersA          = CVec3( g_layerAmplitude1, g_layerAmplitude2, g_layerAmplitude3 );
  heightCoeff      = 1.0f / ( layersA.x + layersA.y + layersA.z );

  // generate texture
  RenderStatesManager& rsManager = *GetStatesManager();
  rsManager.SetState( RenderState::NoBlendNoTest().SetCulling(NDb::ONOFFSTATE_OFF) );
  rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
  rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);

 	SmartRenderer::BindRenderTarget(hTexture);

  rsManager.SetSampler(0, SamplerState::PRESET_WRAP_BILINEAR(), baseHeightmapTexture);

  Renderer &renderer = *GetRenderer();
  renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, rotationMatrices[ 0 ] );
  renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST1, rotationMatrices[ 1 ] );
  renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST2, CVec4( layersVelocities, curTime ) );
  renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST3, CVec4( layersA, heightCoeff ) );
  renderer.ClearColorOnly(Render::Color(0, 0, 0, 0));

	GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("WaterHMap"));
  Render::SmartRenderer::BindRenderTargetDefault();

  // 2nd pass
  SmartRenderer::BindRenderTarget(hDxDyTexture);

  rsManager.SetSampler(0, SamplerState::PRESET_CLAMP_POINT(), hTexture);
  renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, CVec4( texDuDv, 0, 0 ) );
  renderer.ClearColorOnly(Render::Color(0, 0, 0, 0));

  GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("WaterHDXDYMap"));
  Render::SmartRenderer::BindRenderTargetDefault();
}

} // namespace Water
} // namespace Render

REGISTER_VAR( "layerAmplitude1", g_layerAmplitude1, STORAGE_NONE );
REGISTER_VAR( "layerAmplitude2", g_layerAmplitude2, STORAGE_NONE );
REGISTER_VAR( "layerAmplitude3", g_layerAmplitude3, STORAGE_NONE );
REGISTER_VAR( "layerVelocity1",  g_layerVelocity1, STORAGE_NONE );
REGISTER_VAR( "layerVelocity2",  g_layerVelocity2, STORAGE_NONE );
REGISTER_VAR( "layerVelocity3",  g_layerVelocity3, STORAGE_NONE );
