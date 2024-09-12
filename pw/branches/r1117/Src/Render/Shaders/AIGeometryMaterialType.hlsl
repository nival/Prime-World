#include "_common.hlsl"

struct VS_INPUT
{
  float3 Position         : POSITION;
  int4 Color : COLOR;
};      


struct VS_OUTPUT
{
  float4 Position         : POSITION;   // vertex position
  float4 Color : Color;
};


VS_OUTPUT MainPass_VSMain(VS_INPUT Input)
{
  VS_OUTPUT Output;
  Output.Position = mul( float4( Input.Position, 1.f ), World );
  Output.Position = mul( Output.Position, ViewProjection );
  Output.Color = Input.Color;
  return Output;
}

float4 MainPass_PSMain(VS_OUTPUT Input) : COLOR
{
  return Input.Color;
}
