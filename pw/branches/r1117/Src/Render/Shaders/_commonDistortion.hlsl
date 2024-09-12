#include "_common.hlsl"

#ifndef __COMMONDISTORSION_HLSL__
#define __COMMONDISTORSION_HLSL__

sampler distortBufferSampler : register( DISTORTIONBUFFERSAMPLERINDEX );
sampler distortNoiseSampler : register( DISTORTIONNOISESAMPLERINDEX );

float4 distortScaleOffset : register(DISTORTION_PARAMS1);

half3 SampleBackbuffer(float2 xyPixel, float2 noise)
{
  // convert pixel coordinates to texture space
  float2 uv = ScreenToTexture(xyPixel);
  half3 backbuffer = tex2D(distortBufferSampler, uv + noise).rgb;
  return backbuffer;
}

half2 SampleDistortion(float2 uv, half scale)
{
  half2 value = tex2D(distortNoiseSampler, uv).xy;
  half2 noise = scale * (value * distortScaleOffset.xy + distortScaleOffset.zw);
  return noise;
}

half2 ScaleDistortion(float2 value, half scale)
{
  half2 noise = scale * (value * distortScaleOffset.xy + distortScaleOffset.zw);
  return noise;
}

#endif // __COMMONDISTORSION_HLSL__
