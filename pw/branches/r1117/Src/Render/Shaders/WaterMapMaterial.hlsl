#include "_common.hlsl"

uniform float4 worldSize : register( VSHADER_LOCALCONST0 );

struct VS_IN
{
  float2 Position : POSITION;
};

void MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  float4 pos3d = mul( float4(In.Position.xy, 0, 1), World );
  PositionCS = float4(2 * pos3d.xy / worldSize - 1, 1, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 MainPass_PSMain( void ) : COLOR
{
  return float4(1, 1, 1, 1);
}
