#include "_common.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VS_INPUT
{
  float3 Position : POSITION;
};      

struct VS_OUTPUT
{
  float4 PositionCS : TEXCOORD0;
  float4 PositionWS : TEXCOORD1;
  float4 UV : TEXCOORD2;
};

float4 uvOffset : register(VSHADER_LOCALCONST0); // r1cos, r1sin, -r2cos, -r2sin
float  tiling   : register(VSHADER_LOCALCONST1);

VS_OUTPUT MainPass_VSMain(VS_INPUT In, out float4 PositionCS : POSITION)
{
  VS_OUTPUT Out;

  Out.PositionWS = mul( float4( In.Position, 1.0 ), World );
  Out.PositionCS = mul( Out.PositionWS, ViewProjection );
  Out.UV = Out.PositionWS.xyxy * tiling + uvOffset;
  
  PositionCS = Out.PositionCS;
  
  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler noiseMap : register(s0);
sampler depthMap : register(s1);

float4 unproject: register(PSHADER_LOCALCONST0); // 1/w, 1/h, ---, ---
float4 viewInvZ : register(PSHADER_LOCALCONST1);
float4 params   : register(PSHADER_LOCALCONST2); // r3, noiseScale, fogFade, ---
float3 color1   : register(PSHADER_LOCALCONST3);
float3 color2   : register(PSHADER_LOCALCONST4);

half4 MainPass_PSMain( VS_OUTPUT In, float4 PixelPos : VPOS ) : COLOR0
{
  // Add noise
  half2 offset = tex2D(noiseMap, In.UV.xy).rr;
  half  noise  = tex2D(noiseMap, In.UV.zw + offset * params.x).r;

  // Restore bottom position in View Space
  float2 uv = ScreenToTexture(PixelPos);
  float  z0 = In.PositionCS.w;
  float  z  = tex2D(depthMap, uv).r;
  float2 xy = unproject.xy * In.PositionCS.xy * z / z0;
  float  h0 = In.PositionWS.z;
  float  h  = dot(float4(xy, z, 1), viewInvZ);

  // Opacity depends on height delta
  float dz = h0 - h - noise * params.y;
  half alpha = 1 - exp(params.z * dz);

  // Mix different colors
  return half4(lerp(color1, color2, noise), alpha);
}
