#define HLSL
#include "../GlobalMasks.h"
#include "MaterialSpec.hlsl"

// #define DEBUG

// vertex shader input
struct VS_INPUT
{
  float2 Position : POSITION;
  float2 Texcoord : TEXCOORD0;
#if R2VBPinValue == PRESENT
  float4  Weights : TEXCOORD1;
#endif
};			
// pixel shader input
struct VS_OUTPUT_VTF
{
#if WarFogPinValue == PRESENT
  float4 Texcoord : TEXCOORD0;
#else
  float2 Texcoord : TEXCOORD0;
#endif // WarFogPinValue
#if SharpPinValue == PRESENT
  float4 DisplacedCoords : TEXCOORD1;
#if ColorCorrectPinValue != OFF
  float4 InScale  : TEXCOORD2;
  float4 InShift  : TEXCOORD3;
  float3 OutScale : TEXCOORD4;
  float3 OutShift : TEXCOORD5;
  float4 Color    : TEXCOORD6;
#if ColorCorrectPinValue == ON
  float3 Gamma : TEXCOORD7;
#endif // ColorCorrectPinValue == ON
#else
  float2 SharpCoeffs : TEXCOORD2;
#endif // ColorCorrectPinValue != OFF
#else // SharpPinValue == PRESENT
#if ColorCorrectPinValue != OFF
  float3 InScale  : TEXCOORD1;
  float3 InShift  : TEXCOORD2;
  float3 OutScale : TEXCOORD3;
  float3 OutShift : TEXCOORD4;
  float4 Color    : TEXCOORD5;
#if ColorCorrectPinValue == ON
  float3 Gamma : TEXCOORD6;
#endif // ColorCorrectPinValue == ON
#endif // ColorCorrectPinValue != OFF
#endif // SharpPinValue
};

#include "..\OnlineShaders\_commonDepthRead.h"

sampler coeffMap : register(s0);

#if SharpPinValue == PRESENT
float4 g_pixelSize: register(VSHADER_LOCALCONST7);
float4 g_sharpPixelSize: register(VSHADER_LOCALCONST8);
float4 g_sharpCoef: register(VSHADER_LOCALCONST9);
#endif

float4 ColorCastCoef: register(VSHADER_LOCALCONST10);
float4 Params[PP_PIVOT_PARAMS_COUNT * NATURE_TYPES_COUNT]: register(VSHADER_LOCALCONST11);

VS_OUTPUT_VTF MainPass_VSMain(VS_INPUT Input, out float4 Position : POSITION)
{
#if (SharpPinValue == PRESENT) || (ColorCorrectPinValue != OFF)
#if R2VBPinValue == PRESENT
  float4 weights = Input.Weights.yxzw;
#else
  float4 weights = tex2Dlod(coeffMap, float4(0.5f, 0.5f, 0.0f, 0.0f)).yxzw;
#endif
#endif
	
  VS_OUTPUT_VTF Output;

#if WarFogPinValue == PRESENT
  Output.Texcoord.zw = VS_DepthReadParams(Input, Output.Texcoord.xy, Position);
#else
  Output.Texcoord.xy = madValueUV.xy * Input.Texcoord + madValueUV.zw;
  Position = float4(Input.Position.xy * madValuePos.xy + madValuePos.zw, 1.0f, 1.0f); 
#endif

#if SharpPinValue == PRESENT
  float sharpPixelSize = 0, sharpCoef = 0;
  float weightsSum = 0; // Overkill - this should sum up to 1.0f
  for(int i = 0; i < NATURE_TYPES_COUNT; ++i)
  {
    sharpPixelSize += g_sharpPixelSize[i] * weights[i];
	sharpCoef += g_sharpCoef[i] * weights[i];
	weightsSum += weights[i];
  }
  sharpPixelSize /= weightsSum;
  sharpCoef /= weightsSum;
  
  float2 pixelSize = g_pixelSize * sharpPixelSize;
  Output.DisplacedCoords = Output.Texcoord.xyxy + float4(pixelSize, -pixelSize);
#ifdef DEBUG
  Output.DisplacedCoords = weights;
#endif
#if ColorCorrectPinValue != OFF
  Output.InScale.w = 4.f * sharpCoef + g_pixelSize.w;
  Output.InShift.w = sharpCoef;
#else
  Output.SharpCoeffs = float2(4.f * sharpCoef + g_pixelSize.w, sharpCoef);
#endif // ColorCorrectPinValue != OFF 
#endif

#if ColorCorrectPinValue != OFF
  float3 InMin = 0, InMax = 0, OutMin = 0, OutMax = 0, Color = 0;
  float3 GammaCoef = 0;
  float  colorCastCoef = 0;
  for(int i = 0; i < NATURE_TYPES_COUNT; ++i)
  {
    InMin += Params[PP_IN_MIN * NATURE_TYPES_COUNT + i] * weights[i];
    InMax += Params[PP_IN_MAX * NATURE_TYPES_COUNT + i] * weights[i];
    OutMin += Params[PP_OUT_MIN * NATURE_TYPES_COUNT + i] * weights[i];
    OutMax += Params[PP_OUT_MAX * NATURE_TYPES_COUNT + i] * weights[i];
    GammaCoef += Params[PP_GAMMA * NATURE_TYPES_COUNT + i] * weights[i];
    Color += Params[PP_COLOR * NATURE_TYPES_COUNT + i] * weights[i];
    colorCastCoef += ColorCastCoef[i] * weights[i];
  }
  Output.InScale.xyz = 1.0f / (InMax - InMin);
  Output.InShift.xyz = -InMin * Output.InScale;
  Output.OutScale = (OutMax - OutMin);
  Output.OutShift = OutMin;
  Output.Color = float4(Color, colorCastCoef);
	
#if ColorCorrectPinValue == ON
  float3 gamma = 2 / (GammaCoef+1) - 1;
  Output.Gamma = gamma;
#endif
#endif 
  return Output;
}


sampler diffuseMap : register(s1);

half4 DoSharp(float2 texcoord, float4 displaced_coords, half2 Coeffs)
{
	half4 center = tex2D(diffuseMap, texcoord);

	// Sample the neighbor pixels
	half4 l = tex2D(diffuseMap, displaced_coords.xy) + tex2D(diffuseMap, displaced_coords.zy) +
			  tex2D(diffuseMap, displaced_coords.xw) + tex2D(diffuseMap, displaced_coords.zw);

#if ColorCorrectPinValue == DESATURATE_ONLY
	return  saturate(center * Coeffs.x - l * Coeffs.y);
#else
	return  center * Coeffs.x - l * Coeffs.y;
#endif
}


#if BloomPinValue == PRESENT
sampler2D bloomMap : register(s2);
#endif
#if WarFogPinValue == PRESENT
sampler2D DepthMap : register(s0);
sampler2D warFogSampler : register( WARFOGSAMPLERINDEX );

float2 BasePos : register( PSHADER_LOCALCONST0 );
float  zNear   : register( PSHADER_LOCALCONST1 );
#endif

static const float3 LuminanceConv = { 0.299, 0.587, 0.114 };

half4 MainPass_PSMain(VS_OUTPUT_VTF Input) : COLOR
{
#if SharpPinValue == PRESENT
#ifdef DEBUG
  return Input.DisplacedCoords.yxzw;
#endif
#if ColorCorrectPinValue != OFF
  float2 coeffs = float2(Input.InScale.w, Input.InShift.w);
#else
  float2 coeffs = Input.SharpCoeffs;
#endif // ColorCorrectPinValue
  half3 c0 = DoSharp(Input.Texcoord, Input.DisplacedCoords, coeffs);
#else
  half3 c0 = tex2D(diffuseMap, Input.Texcoord);
#endif // SharpPinValue
#if BloomPinValue == PRESENT
  c0 += tex2D(bloomMap, Input.Texcoord);
#endif
#if WarFogPinValue == PRESENT
  float z = tex2D(DepthMap, Input.Texcoord).r;
  if (z > zNear) // smirnov [2010/12/16]: don't warfog on-screen special effects (costs +1 'cmp' instruction)
  {
    float2 warfogMapping = BasePos + z * Input.Texcoord.zw;
    half4 warFog = tex2D(warFogSampler, 1.f-warfogMapping.yx);
    c0 = lerp(c0, warFog.xyz, warFog.a);
  }
#endif
	
#if ColorCorrectPinValue != OFF
#if ColorCorrectPinValue != DESATURATE_ONLY
  c0 = saturate(c0 * Input.InScale + Input.InShift);
#endif
#if ColorCorrectPinValue == ON
  c0 = pow(c0, Input.Gamma);
#endif
  half gs = dot(c0, LuminanceConv);
  c0 = lerp(c0, Input.Color * gs, Input.Color.w);
#if ColorCorrectPinValue != DESATURATE_ONLY
  c0 = c0 * Input.OutScale + Input.OutShift;
#endif
#endif
  return half4(c0, 1);
}
