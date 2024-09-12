#define FORCE_NIGHT_PARAMS_PRESENT

#include "_common.hlsl"
#include "_commonNight.hlsl"

#define USING_CACHE (CachingPinValue == USE || CachingPinValue == USE2 || CachingPinValue == USE3)
#define USING_CACHE_GLOBAL (USING_CACHE && TerrainUVSetPinValue == GLOBAL)
#define USING_MASK (CachingPinValue != USE || !USING_CACHE_GLOBAL)

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
  float4 UV     : TEXCOORD0;
  float4 Mask   : COLOR1;
#if RenderModeValue == RENDERNORMAL
  float4 Color  : COLOR0;
//  float3 Normal : TEXCOORD2;
#if USING_MASK
  float2 MaskUV : TEXCOORD1;
#endif
#endif
#if CachingPinValue != FILL
#if RenderModeValue == RENDERTOSHADOW
  float2 ZW     : TEXCOORD3;
#else
  float  Z      : TEXCOORD3;
#endif
#endif // CachingPinValue != FILL
};


float tiling: register(VSHADER_LOCALCONST0);
float4 maskMapping: register(VSHADER_LOCALCONST1);
#if CachingPinValue != ORDINARY
float4 patchScale: register(VSHADER_LOCALCONST2); // x,y - scale, zw - patch shift
#endif

#if RenderModeValue == RENDERSHAPEONLY
void   MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
#else
VS_OUT MainPass_VSMain( VS_IN In, out float4 PositionCS: POSITION )
#endif
{
  float4 PositionWS;
  // PositionWS = mul( float4( In.Position, 1.0 ), World );
  PositionWS = float4( In.Position, 1.0 );
#if CachingPinValue == FILL
  float2 pos = patchScale.xy * PositionWS.xy + patchScale.zw;
  PositionCS = float4(2.f * pos - 1.f, 0.5f, 1.f);
#else	
  PositionCS = mul( PositionWS, ViewProjection );
#endif
  
#if RenderModeValue != RENDERSHAPEONLY
  VS_OUT Out;

#if CachingPinValue != FILL
#if RenderModeValue == RENDERTOSHADOW
  Out.ZW = PositionCS.zw;
#else
  Out.Z = PositionCS.w;
#endif
#endif // CachingPinValue != FILL

  Out.Mask = In.Mask;
#if USING_CACHE
  float2 uvTemp = patchScale * PositionWS * float2(1.f, -1.f);
  Out.UV = uvTemp.xyxy;
#else
  Out.UV = PositionWS.xyxy * tiling;
#endif // USING_CACHE
#if TerrainUVSetPinValue == LOCAL
  Out.UV.xy = In.UV;
#endif
#if RenderModeValue == RENDERNORMAL
  // Out.Normal = mul( float4( In.Normal, 0.0 ), World );
  Out.Color.rgb = lerp(In.Color1.rgb * In.Color1.a, In.Color2.rgb * In.Color2.a, vs_nightParams.x) * 255.0; // nightFraction
  Out.Color.a   = 1.0;
#if USING_MASK
  Out.MaskUV = PositionWS.xy * maskMapping.xy + maskMapping.zw;
#endif
#endif // RenderModeValue == RENDERNORMAL

  return Out;
#endif  // RenderModeValue != RENDERSHAPEONLY
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler[4]  : register(TERRAIN_DIFFUSESAMPLER0); // 4 consecutive samplers
sampler natureMask            : register(s4);

float  fOverburn              : register(PSHADER_LOCALCONST0);
float4 weightMask             : register(PSHADER_LOCALCONST1);
float4 weightMask1            : register(PSHADER_LOCALCONST2);
float4 weightMask2            : register(PSHADER_LOCALCONST3);

float3 ambientColorMult       : register(TERRAIN_AMBIENT);
float3 light1DiffuseColorMult : register(TERRAIN_DIFFUSE1);
float3 light2DiffuseColorMult : register(TERRAIN_DIFFUSE2);

struct PS_OUT
{
#if RenderModeValue == RENDERNORMAL
  half4  color : COLOR0;
#if DO_DEPTH_OUT && (CachingPinValue != FILL)
  float4 z     : COLOR1;
#endif
#else
  float4 z : COLOR0;
#endif
};


#if (CachingPinValue == USE2 || CachingPinValue == USE3) && TerrainUVSetPinValue == LOCAL

PS_OUT MainPass_PSMain( VS_OUT In, float4 PixelPos : VPOS )
{
  PS_OUT output;
#if RenderModeValue == RENDERSHAPEONLY
  output.z = 1.0f;
  return output;
#endif // RenderModeValue == RENDERSHAPEONLY
  half4 layer0 = tex2D(diffuseMapSampler[0], In.UV);
#if RenderModeValue == RENDERTOSHADOW
  output.z = float4( (In.ZW.x/In.ZW.y).xxx, layer0.a );
  return output;
#elif RenderModeValue == RENDERNORMAL
  half4 mask = In.Mask.bgra;
  half4 layer1 = tex2D(diffuseMapSampler[2], In.UV);
  // terrain mask for blending different nature types
  half4 weight = tex2D(natureMask, In.MaskUV);
  // we should not use output.color for intermediate calculations, as this will raise precision requirements
  half4 color = layer0 * dot(weight, weightMask) + layer1 * dot(weight, weightMask1);
#if CachingPinValue == USE3
  half4 layer2 = tex2D(diffuseMapSampler[3], In.UV);
  color += layer2 * dot(weight, weightMask2);
#endif // RenderModeValue == RENDERTOSHADOW
  half4 cachedColor = tex2D(diffuseMapSampler[1], In.UV.zw);
  color.rgb = (color * In.Color * mask[0] * cachedColor.a + cachedColor);
  output.color = color;
#endif // RenderModeValue == RENDERTOSHADOW
  // color.rgb += fOverburn * weight.a * outputColor.rgb;
#if DO_DEPTH_OUT && RenderModeValue == RENDERNORMAL
  output.z = In.Z;
#endif
  return output;
}

#else // (CachingPinValue == USE2 || CachingPinValue == USE3) && TerrainUVSetPinValue == LOCAL

PS_OUT MainPass_PSMain( VS_OUT In, float4 PixelPos : VPOS )
{
  PS_OUT output;
#if RenderModeValue != RENDERNORMAL
#if (CachingPinValue == FILL) || (RenderModeValue == RENDERSHAPEONLY)
  output.z = 1.f;
#else
  half4 layer0 = tex2D(diffuseMapSampler[0], In.UV.xy);
  output.z = float4( (In.ZW.x/In.ZW.y).xxx, layer0.a );
#endif
  return output;
#else // RenderModeValue != RENDERNORMAL
  half4 mask = In.Mask.bgra;
#if (CachingPinValue == FILL && TerrainUVSetPinValue == LOCAL) || USING_CACHE_GLOBAL
  half4 diffuseMap = half4(0, 0, 0, 1);
#else
  half4 diffuseMap = tex2D(diffuseMapSampler[0], In.UV.xy);
  diffuseMap.rgb *= mask[0];
#endif // CachingPinValue == FILL

#if USING_CACHE
  half4 cachedColor = tex2D(diffuseMapSampler[1], In.UV.zw);
  output.color.rgb = (diffuseMap * In.Color * cachedColor.a + cachedColor);
  output.color.a = diffuseMap.a;
#else
  // combine texture layers
  for (int i = 1; i <= TextureCountPinValue; i++)
  {
    half4 layer = tex2D(diffuseMapSampler[i], In.UV.zw);
    diffuseMap += layer * mask[i];
  }

  // diffuse lighting
  half4 outputColor = In.Color * diffuseMap;

  // terrain mask for blending different nature types
  half4 weight = tex2D(natureMask, In.MaskUV);
  outputColor.rgb *= dot(weight, weightMask);
  outputColor.rgb += fOverburn * weight.a * outputColor.rgb;
#if CachingPinValue == FILL
  output.color = half4(outputColor.rgb, 1.f);
#else
  output.color = outputColor;
#endif // CachingPinValue == FILL
#endif // USING_CACHE

#if DO_DEPTH_OUT && (CachingPinValue != FILL)
  output.z = In.Z;
#endif
  return output;
#endif // RenderModeValue == RENDERSHAPEONLY
}

#endif // CachingPinValue == USE2
