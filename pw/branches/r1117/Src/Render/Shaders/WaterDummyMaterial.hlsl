#include "_common.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VS_INPUT
{
  float3 Position : POSITION;
};      

struct VS_OUTPUT
{
  float Z : TEXCOORD0;
};

VS_OUTPUT MainPass_VSMain(VS_INPUT In, out float4 PositionCS : POSITION)
{
  VS_OUTPUT Out;

  float4 PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionCS = mul( PositionWS, ViewProjection );

  Out.Z = PositionCS.w;
  
  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DualDepthPinValue == FALSE
float4 MainPass_PSMain( VS_OUTPUT In ) : COLOR0
{
#else
float4 MainPass_PSMain( VS_OUTPUT In, out float4 secondVal : COLOR1 ) : COLOR0
{
  secondVal = float4(In.Z, 0, 0, 1);
#endif
  return float4(In.Z, 0, 0, 1);
}
