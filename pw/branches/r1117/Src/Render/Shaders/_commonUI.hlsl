#define HLSL
#include "../GlobalMasks.h"
#include "MaterialSpec.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4x4 viewMatrix : register( VIEW );
float4x4 modelMatrix : register( WORLD );

uniform float4 color1  : register( VSHADER_LOCALCONST0 );
uniform float4 color2  : register( VSHADER_LOCALCONST1 );
uniform float4 fontTexScale : register( VSHADER_LOCALCONST2 );
uniform float4 resolutionCoef : register( VSHADER_LOCALCONST3 );		
uniform float4 coefs : register( VSHADER_LOCALCONST4 );	
uniform float forceZ : register( VSHADER_LOCALCONST5 );	
uniform float forceW : register( VSHADER_LOCALCONST6 );
uniform float4 flashConstants : register( VSHADER_LOCALCONST7 );
uniform float4 stripesCoefs : register( VSHADER_LOCALCONST8 );
uniform float4 stripeCol100 : register( VSHADER_LOCALCONST9 );
uniform float4 stripeCol1000 : register( VSHADER_LOCALCONST10 );

struct VS_OUTPUT
{
    float4 Position		: POSITION;   // vertex position
    float2 Texcoord		: TEXCOORD0;  // vertex texcoords
    float2 Texcoord2		: TEXCOORD1;  // vertex texcoords2
    float2 Texcoord3    : TEXCOORD2;
    float4 Vertexcolor		: COLOR0;
};

struct VS_INPUT
{
    float2 Position		: POSITION;
    float2 Texcoord		: TEXCOORD0;
    float2 Texcoord2	: TEXCOORD1;
    int4 Vertexcolor	: COLOR0;	
};


float4 CommonTransform(float2 position)
{
  float4 newPos = float4(
    (position.x * resolutionCoef.x - 1.f) * forceW,
    (1.f - position.y * resolutionCoef.y) * forceW,
    forceZ,
    forceW);
  return mul(newPos, modelMatrix);
};
