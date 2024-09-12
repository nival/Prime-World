// pixel shader input
struct VS_OUTPUT_DR
{
  float2 Texcoord : TEXCOORD0;
  float4 ZScale   : TEXCOORD1;
};


float4 madValueUV : register(VSHADER_LOCALCONST0);
float4 madValuePos : register(VSHADER_LOCALCONST1);
float4 uvScaleOffset : register(VSHADER_LOCALCONST2);
float4x4 ViewToTargetSpace : register(VSHADER_LOCALCONST3); // ViewInv * LightViewProj for shadows, VS2FogMapping for warfog


float4 VS_DepthReadParams(VS_INPUT Input, out float2 Texcoord, out float4 Position : POSITION)
{
  Position = float4(Input.Position.xy * madValuePos.xy + madValuePos.zw, 1.0f, 1.0f); 

  float2 texCoord = madValueUV.xy * Input.Texcoord + madValueUV.zw;
  Texcoord = texCoord;
  
  float3 zScale = float3( (texCoord * uvScaleOffset.xy + uvScaleOffset.zw), 1.0f );
  return mul(zScale, ViewToTargetSpace);
}
