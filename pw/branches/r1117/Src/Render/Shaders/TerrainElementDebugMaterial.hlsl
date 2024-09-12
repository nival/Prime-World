#include "_common.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float3 Normal : NORMAL;
  float2 UV : TEXCOORD0;
  float4 Color1 : COLOR0;
  float4 Color2 : COLOR1;
  float4 Mask : COLOR2;
};

struct VS_OUT
{
  float4 UV       : TEXCOORD0;
  float3 Normal   : TEXCOORD1;
  float2 MaskUV   : TEXCOORD2;
  float4 Color    : COLOR0;
  float4 Mask     : COLOR1;
};

float4 maskMapping: register(VSHADER_LOCALCONST1);

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  float4 PositionWS;
  // PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionWS = float4( In.Position, 1.0 );
  PositionCS = mul( PositionWS, ViewProjection );

  Out.Normal = mul( float4( In.Normal, 0.0 ), World );
  Out.Color = In.Color1;
  Out.Mask = In.Mask;

  Out.UV = PositionWS.xyxy * 0.1;
#if TerrainUVSetPinValue == LOCAL
  Out.UV.xy = In.UV;
#endif

  Out.MaskUV = PositionWS.xy * maskMapping.xy + maskMapping.zw;

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 diffuseMapColor[4]     : register(PSHADER_LOCALCONST2); // 4 consecutive constants
float4 weightMask             : register(PSHADER_LOCALCONST1);
sampler natureMask            : register(s4);

float3 ambientColorMult       : register(TERRAIN_AMBIENT);
float3 light1DiffuseColorMult : register(TERRAIN_DIFFUSE1);
float3 light2DiffuseColorMult : register(TERRAIN_DIFFUSE2);

float4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  float4 mask = In.Mask.bgra;
  float4 diffuseMap = float4(0, 0, 0, 1);
/*
  float4 maximum = max(mask.rrbb, mask.ggaa);
  maximum = max(maximum.rrrr, maximum.bbbb);
  maximum = step(maximum, mask);
  float norm = dot(maximum, maximum);
  mask = norm > 1e-5f ? maximum / norm : float4(0, 0, 0, 0);
*/
  // combine texture layers
  for (int i = 0; i < 4; i++)
  {
    float4 layer = diffuseMapColor[i];
    diffuseMap.rgb += layer.rgb * mask[i];
  }

  // diffuse lighting
  float4 outputColor;
  outputColor.rgb = ambientColorMult;
  outputColor.rgb += light1DiffuseColorMult * max(0, dot(In.Normal, light1Direction));
  outputColor.rgb += light2DiffuseColorMult * max(0, dot(In.Normal, light2Direction));
  outputColor.rgb *= diffuseMap.rgb;
  outputColor.a = 1.0;

  // terrain mask for blending different nature types
  float4 weight = tex2D(natureMask, In.MaskUV);
  outputColor.rgb *= dot(weight, weightMask);

  return outputColor;
}
