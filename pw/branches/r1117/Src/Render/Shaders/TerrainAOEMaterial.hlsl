#include "_common.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float2 UV : TEXCOORD0;
};

struct VS_OUT
{
  float2 UV : TEXCOORD0;
};

float4 uvScaleOffset : register(VSHADER_LOCALCONST0);

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  float4 PositionWS;
  PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionCS = mul( PositionWS, ViewProjection );

  Out.UV = PositionWS.xy * uvScaleOffset.xy + uvScaleOffset.zw;

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  half4 diffuseMap = tex2D(diffuseMapSampler, In.UV);
  return diffuseMap;
}
