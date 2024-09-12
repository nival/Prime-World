#include "_common.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float4 Params: TEXCOORD0;
};

struct VS_OUT
{
  float2 UV : TEXCOORD0;
  float4 Color : COLOR0;
};

float4 uvScaleOffset : register(VSHADER_LOCALCONST0);
float4 color : register(VSHADER_LOCALCONST1);
float2 vertexShift : register(VSHADER_LOCALCONST2);

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  float4 PositionWS;
  In.Position.z += dot(In.Params.yz, vertexShift.xy);
  PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionCS = mul( PositionWS, ViewProjection );

  Out.UV = float2(In.Position.z, In.Params.x) * uvScaleOffset.xy + uvScaleOffset.zw;
  Out.Color = color * In.Params.w;

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMap : register(s0);

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  half4 outputColor = tex2D(diffuseMap, In.UV);
  outputColor *= In.Color;
  return outputColor;
}
