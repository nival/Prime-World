#include "_commonPostProcess.h"
#include "_commonDepthRead.h"

sampler depthMap : register(s0);
sampler shadowMap : register(s1);

float4 shadowColor : register( PSHADER_LOCALCONST1 );
float3 params : register( PSHADER_LOCALCONST2 ); // 1/size, -1/size, 0
float4 rangeAndScale : register( PSHADER_LOCALCONST3 ); // fadeMUL, fadeADD, scaleCenter * shadowColor.a, scaleCorners * shadowColor.a
float4 screenScaleOffset : register( SCREEN_TO_TEXTURE );

float4 BasePos : register( PSHADER_LOCALCONST4 );

//#define DEBUG_COORDS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

half4 PS_main(VS_OUTPUT_DR Input, float2 screenPos : VPOS) : COLOR
{
#ifdef DEBUG_COORDS
  float2 uv = screenPos.xy * screenScaleOffset.xy + screenScaleOffset.zw;
  float2 uvDiff = abs(uv - Input.Texcoord) / screenScaleOffset.xy;
  if( (uvDiff.x > 0.001f) || (uvDiff.y > 0.001f) )
    return half4(uvDiff,0,1);
#endif
  // restore position in View Space
  float z = tex2D(depthMap, Input.Texcoord).r;
  float4 PositionLS = BasePos + z * Input.ZScale;

  half test = tex2Dproj(shadowMap, PositionLS);
  // fade in the distance

#ifdef DO_PCF4
  float3 texelShift = params * PositionLS.w;

  half test2 = tex2Dproj(shadowMap, PositionLS + texelShift.xxzz);
  test2 += tex2Dproj(shadowMap, PositionLS + texelShift.yxzz);
  test2 += tex2Dproj(shadowMap, PositionLS + texelShift.xyzz);
  test2 += tex2Dproj(shadowMap, PositionLS + texelShift.yyzz);

  half alpha = half(shadowColor.a) - half(rangeAndScale.z) * test - half(rangeAndScale.w) * test2;
#else
  half alpha = half(shadowColor.a) * (1.0f - test);
#endif

  alpha *= saturate(half(z) * half(rangeAndScale.x) + half(rangeAndScale.y));

  // select between multiplicative and blended shadows
#ifdef SHADOW_MULTIPLICATIVE
  return half4(lerp(1, half3(shadowColor.xyz), alpha), alpha);
#else
  return half4(shadowColor.xyz, alpha);
#endif
}
