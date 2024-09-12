#define HLSL
#include "../GlobalMasks.h"

// vertex shader input
struct VS_INPUT
{
  float2 Position : POSITION;
  float2 Texcoord : TEXCOORD0;
};			

// pixel shader input
struct VS_OUTPUT
{
  float2 Texcoord : TEXCOORD0;
};

// pixel shader input
struct VS_OUTPUT_VTF
{
#ifdef DO_SHARP
  float2 Texcoord : TEXCOORD0;
  float4 SharpPixelSizeAndCoeff : TEXCOORD1;
#else
  float4 Texcoord : TEXCOORD0;
  float3 InScale  : TEXCOORD1;
  float3 InShift  : TEXCOORD2;
  float3 OutScale : TEXCOORD3;
  float3 OutShift : TEXCOORD4;
  float3 Color    : TEXCOORD5;
  float4 ColorCastCoeffAndGamma : TEXCOORD6;
#endif
};
