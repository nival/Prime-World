#define HLSL
#include "../GlobalMasks.h"
#include "MaterialSpec.hlsl"

#ifndef __COMMON_HLSL__
#define __COMMON_HLSL__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex shader constants & samplers

float4x4 View               : register( VIEW );
float4x4 World              : register( WORLD );
float4x4 ViewProjection     : register( VIEWPROJECTION );
float4x4 projection         : register( PROJECTION );
float4 WEyePos              : register( EYEPOSITION );
float4 eyeDirection         : register( CAMERADIRECTION );
float totalTime             : register( RENDERTIME );

//float4x4 PrevWVP            : register( VSHADER_LOCALCONST9 );


//sampler warfogSampler       : register( WARFOGSAMPLERINDEX );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pixel shader constants & samplers

float3 ambientColor       : register( AMBIENTCOLOR );
float3 light1DiffuseColor : register( LIGHT1DIFFUSECOLOR );
float3 light2DiffuseColor : register( LIGHT2DIFFUSECOLOR );
float3 light1Direction    : register( LIGHT1DIRECTION );
float3 light2Direction    : register( LIGHT2DIRECTION );
float4 screenScaleOffset    : register( SCREEN_TO_TEXTURE );

// @BVS@TODO Remove renaming after full materials migration
#define SunAmbientColor ambientColor
#define SunDiffuseColor light1DiffuseColor
#define WSunDir         light1Direction

samplerCUBE envMapSampler   : register( GLOBALENVIROMENTSAMPLERINDEX );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common functions

float2 ScreenToTexture( float2 screenXY )
{
  return screenXY * screenScaleOffset.xy + screenScaleOffset.zw;
}

half ComputeLuminance( half3 color )
{
  half3 weight = half3( 0.299f, 0.587f, 0.114f );
  //float luminance = max(average.r, max(average.g, average.b) );
  return dot( color.rgb, weight);
}

// Warfog is DEAD!
half ReadWarFog(float2 pos)
{
  //return tex2Dlod( warfogSampler, float4(pos*worldScale, 0, 0) ).r;
  return 1.0f;
}

#define DO_DEPTH_OUT (DoDepthOutValue == TRUE)

#endif //__COMMON_HLSL__
