#include "_common.hlsl"

//
uniform float4x4 mtxWorldViewProjection : register(VSHADER_LOCALCONST0);
uniform float4   ViewOffset : register(VSHADER_LOCALCONST8);
uniform float4x4 mtxWorld : register(VSHADER_LOCALCONST4);

struct VS_INPUT
{
  float3 Position : POSITION;
  float3 Normal : NORMAL;
};      

struct VS_OUTPUT
{
  float4 Position : POSITION;  
  float4 HeightAndNormal : TEXCOORD0; 
};

VS_OUTPUT MainPass_VSMain(VS_INPUT Input)
{
  VS_OUTPUT Output;
  Output.Position = mul( float4( Input.Position, 1.f), mtxWorldViewProjection ) + ViewOffset;
  Output.HeightAndNormal.w = mul( Input.Position, mtxWorld ).z;
  Output.HeightAndNormal.xyz = mul( Input.Normal, mtxWorld );

  return Output;
}

float4 MainPass_PSMain(VS_OUTPUT Input) : COLOR0
{
  float2 normalXY = normalize(Input.HeightAndNormal.xyz).xy;
  float4 color = float4(Input.HeightAndNormal.w, normalXY, 0.0);
  return color;
}
