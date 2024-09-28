#define FORCE_NIGHT_PARAMS_PRESENT

#include "_common.hlsl"
#include "_commonNight.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float4 Color1 : COLOR0;
  float4 Color2 : COLOR1;
  float4 Params : TEXCOORD0;
};

struct VS_OUT
{
  float4 Color : COLOR0;
  float4 Mapping : TEXCOORD0;
  float2 MaskUV : TEXCOORD1;
};

float4 maskMapping: register(VSHADER_LOCALCONST1);  // inherited from Terrain
float roadWidthInv : register(VSHADER_LOCALCONST2); // todo: move multiplication to geometry builder
#if CachingPinValue == FILL
float4 patchScale: register(VSHADER_LOCALCONST3); // x,y - scale, zw - patch shift
#endif

VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
{
  VS_OUT Out;

  float4 PositionWS;
  PositionWS = float4( In.Position, 1.0 );
#if CachingPinValue == FILL
  float2 pos = patchScale.xy * PositionWS.xy + patchScale.zw;
  PositionCS = float4(2.f * pos - 1.f, 0.5f, 1.f);
#else	
  PositionCS = mul( PositionWS, ViewProjection );
#endif

  Out.Color.rgb = lerp(In.Color1.rgb * In.Color1.a, In.Color2.rgb * In.Color2.a, vs_nightParams.x) * 255.0; // nightFraction
  Out.Color.a   = In.Params.w;
  Out.Mapping = float4(In.Params.xyz * roadWidthInv, 1);
  Out.MaskUV = PositionWS.xy * maskMapping.xy + maskMapping.zw;

  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/******************************************

sampler2D LandMap;

// artist variables
float TILEU;
float TILEV;
float TILEVBORDER;
float WIDTH;
float BORDER;
float FADEWIDTH;
bool TEXTUREFIT;

*******************************************/

float  fOverburn : register(PSHADER_LOCALCONST0); // inherited from TerrainElement
float4 weightMask : register(PSHADER_LOCALCONST1); // like in TerrainElement, 1.0 in one component, 0.0 in others
float4 uvScale : register(PSHADER_LOCALCONST2); // = float4(0.5 * TILEU, 0.5 * TILEV, 1 / BORDER, 0.5 * TILEVBORDER / BORDER);
float4 uvOffset : register(PSHADER_LOCALCONST3); // = float4(0.5, 0, 1, 0);
float4 fadeScale : register(PSHADER_LOCALCONST4); // = float2(-1 / FADE, -BORDER / FADE, 1 / WIDTH, -0.5);
float4 params : register(PSHADER_LOCALCONST5); // = float4(BORDER, -, -, OPACITY);


sampler2D RoadMap : register(s0);
sampler2D BorderMap : register(s1);
sampler2D NatureMap : register(s4);

//#if ShaderQualityValue == BEST
#if 0

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
#if DebugPinValue == PRESENT
  half4 finalColor = half4(0.5, 0.5, 0.5, 1);
#else
  float borderWidth = params.x;

  // adjust interpolated values
  In.Mapping.w = abs(In.Mapping.x) - In.Mapping.z;
#if TextureFitPinValue == PRESENT
  In.Mapping.x /= In.Mapping.z - borderWidth;
#endif

  // generate mapping
  float4 uv = In.Mapping.xywy * uvScale + uvOffset;

  // generate mask for road and border
  half4 alphaMask;
  // - soft mask
  alphaMask.y = saturate(In.Mapping.w * fadeScale.x + fadeScale.y);
  alphaMask.w = abs(uv.z - 0.5) < 0.5;
  // - hard mask
  alphaMask.xz = alphaMask.yw > 0;

  // blend road and border textures
  half4 roadColor = tex2D( RoadMap, uv.yx );
  half4 borderColor = tex2D( BorderMap, uv.wz );
  half4 finalColor = In.Color * (roadColor * alphaMask.xxxy + borderColor * alphaMask.zzzw);

  // terrain mask for blending different nature types
  half4 weight = tex2D(NatureMap, In.MaskUV);
  finalColor.a *= params.a * dot(weight, weightMask);
  finalColor.rgb += fOverburn * weight.a * finalColor.rgb;

  // do alpha-test with 0 and crop road length
  float2 cull;
  cull.x = finalColor.a - 1.0e-10;
  cull.y = (0.5 - abs(In.Mapping.y * fadeScale.z + fadeScale.w));
  clip(cull);
#endif // not DebugPinValue == PRESENT

  return finalColor;
}

#else

sampler2D RoadMap1 : register(s2);
sampler2D BorderMap1 : register(s3);
sampler2D RoadMap2 : register(s5);
sampler2D BorderMap2 : register(s6);

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
#if DebugPinValue == PRESENT
  half4 finalColor = half4(0.5, 0.5, 0.5, 1);
#else
  clip(0.5 - abs(In.Mapping.y * fadeScale.z + fadeScale.w));
  
  // adjust interpolated values
  In.Mapping.w = abs(In.Mapping.x) - In.Mapping.z;
#if TextureFitPinValue == PRESENT
  {
    float borderWidth = params.x;
    In.Mapping.x /= In.Mapping.z - borderWidth;
  }
#endif

  // generate mapping
  float4 uv = In.Mapping.xywy * uvScale + uvOffset;

  // generate mask for road and border
  half4 alphaMask;
  // - soft mask
  alphaMask.y = saturate(In.Mapping.w * fadeScale.x + fadeScale.y);
  alphaMask.w = abs(uv.z - 0.5) < 0.5;
  // - hard mask
  alphaMask.xz = alphaMask.yw > 0;

  // terrain mask for blending different nature types
  half4 weight = tex2D(NatureMap, In.MaskUV);
  
  // blend road and border textures
  half4 roadColor = tex2D( RoadMap, uv.yx );
  half4 borderColor = tex2D( BorderMap, uv.wz );
  half4 finalColor0 = roadColor * alphaMask.xxxy + borderColor * alphaMask.zzzw;
  finalColor0.a *= weight.r;

  roadColor = tex2D( RoadMap1, uv.yx );
  borderColor = tex2D( BorderMap1, uv.wz );
  half4 finalColor1 = roadColor * alphaMask.xxxy + borderColor * alphaMask.zzzw;
  finalColor1.a *= weight.g;

  roadColor = tex2D( RoadMap2, uv.yx );
  borderColor = tex2D( BorderMap2, uv.wz );
  half4 finalColor2 = roadColor * alphaMask.xxxy + borderColor * alphaMask.zzzw;
  finalColor2.a *= weight.b;
  
  half4 finalColor;
  finalColor.rgb = (finalColor0 * finalColor0.a + finalColor1 * finalColor1.a + finalColor2 * finalColor2.a) * In.Color.a; 
  finalColor.rgb += fOverburn * weight.a * finalColor.rgb;
  finalColor.a = finalColor0.a + finalColor1.a + finalColor2.a; 
  finalColor = saturate(params.a * In.Color * finalColor);
  
#endif // not DebugPinValue == PRESENT

  return finalColor;
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
