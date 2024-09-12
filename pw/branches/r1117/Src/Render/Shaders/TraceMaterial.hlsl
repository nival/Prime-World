#include "_common.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float2 Alpha    : TEXCOORD0;
};

struct VS_OUT
{
  float4 Color : COLOR;
#if TraceTexturePinValue == PRESENT
  float2 UV : TEXCOORD0;
#endif
};

float4 aScaleOffset : register(VSHADER_LOCALCONST0);
float4 colorFirst : register(VSHADER_LOCALCONST1);
float4 colorLast  : register(VSHADER_LOCALCONST2);
float4 uvScaleOffset : register(VSHADER_LOCALCONST3);

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  float4 PositionWS;
  PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionCS = mul( PositionWS, ViewProjection );

  float2 alpha = saturate(In.Alpha.x * aScaleOffset.xy + aScaleOffset.zw);
  Out.Color = lerp(colorLast, colorFirst, alpha.x);
  Out.Color.a *= alpha.y;

#if TraceTexturePinValue == PRESENT
  Out.UV = float2(alpha.y, In.Alpha.y) * uvScaleOffset.xy + uvScaleOffset.zw;
#endif

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );

float4 MainPass_PSMain( VS_OUT In ) : COLOR
{
#if TraceTexturePinValue == PRESENT
  return In.Color * tex2D(diffuseMapSampler, 1-In.UV);
#else
  return In.Color;
#endif
}
