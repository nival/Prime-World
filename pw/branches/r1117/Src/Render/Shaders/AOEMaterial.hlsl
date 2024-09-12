#include "_common.hlsl"

struct VS_IN
{
  float2 Position : POSITION;
  int Index : BLENDINDICES0;
};

struct VS_OUT
{
  float2 UV : TEXCOORD0;
};

float radius : register(VSHADER_LOCALCONST0);

#if CustomizedGeometryPinValue == PRESENT
float4 position[9] : register(VSHADER_LOCALCONST1);
#endif

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

#if CustomizedGeometryPinValue == PRESENT
  // Receive position an UV via constant register
  float4 fanParams = position[In.Index];
  float2 dir = float2(1.0, sign(In.Position.y));
  In.Position.xy = dir * fanParams.xy;
  Out.UV = float2(0.5, 0.5) + dir * (fanParams.zw - float2(0.5, 0.5));
#else
  static const float4 xy2uv = float4(0.5f, -0.5f, 0.5f, 0.5f);
  Out.UV = In.Position.xy * xy2uv.xy + xy2uv.zw;
#endif

  float4 PositionWS;
  PositionWS = mul( float4( radius * In.Position, 0.0, 1.0 ), World );
  PositionCS = mul( PositionWS, ViewProjection );

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );
float4 color : register(PSHADER_LOCALCONST0);

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  half4 diffuseMap = tex2D(diffuseMapSampler, In.UV);
  return color * diffuseMap;
}
