#include "_common.hlsl"

#define NUM_HEXES_SUPPORTED 20
#define CONSTANTS_PER_HEX   2

struct VS_IN
{
  float3 Position : POSITION;
  float  Index    : TEXCOORD0;
};

struct VS_OUT
{
  float4 Color    : COLOR0;
  float2 UV       : TEXCOORD0;
};

sampler retreatMask : register(s0);
float4 scaleOffset : register( VSHADER_LOCALCONST0 );
float4 globalParams : register( VSHADER_LOCALCONST1 ); // maskTiling, -, - ,-
float4 hexParams[NUM_HEXES_SUPPORTED * CONSTANTS_PER_HEX] : register( VSHADER_LOCALCONST2 );

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  int index = CONSTANTS_PER_HEX * int(In.Index);
  In.Position.xy += hexParams[index].xy;

  float4 PositionWS;
  PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionCS.xy = PositionWS.xy * scaleOffset.xy + scaleOffset.zw;
  PositionCS.zw = float2( 1, 1 );

  Out.Color = hexParams[index + 1];
  Out.UV = PositionWS.xy * globalParams.xx;

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  float3 threshold = tex2D(retreatMask, In.UV).rrr * (In.Color.a == 0);
  threshold.rb = 1 - threshold.rb;

  In.Color.rgb = saturate(2 * In.Color.rgb - threshold);
  return In.Color;
}
