// Statistics on used registers is gathered here:
// Do not forget to update.

#include "_common.hlsl"
#include "_commonSkinning.hlsl"
#include "_commonSH.hlsl"
#include "_commonNight.hlsl"
#include "_bloomEncoding.hlsl"

// instancing doesn't support some features
#if LightingPinValue == LIGHTINGINSTANCEDSH
#undef  NormalMapPinValue
#define NormalMapPinValue    NONE
#undef  SpecularMapPinValue
#define SpecularMapPinValue  NONE
#undef  ReflectivityPinValue
#define ReflectivityPinValue REFLECTIVITYOFF
#undef  SkeletalMeshPinValue
#define SkeletalMeshPinValue NONE
#undef  SpecularPinValue
#define SpecularPinValue     NONE
#endif // LightingPinValue == LIGHTINGINSTANCEDSH


// cannot use normal map unless present
#if (NormalMapPinValue == NONE) && (ReflectivityPinValue == REFLECTIVITYFROMNORMALMAP)
#undef  ReflectivityPinValue
#define ReflectivityPinValue REFLECTIVITYSIMPLE
#endif

// cannot use specular map unless present
#if (SpecularMapPinValue == NONE) && (ReflectivityPinValue == REFLECTIVITYFROMSPECULARMAP)
#undef  ReflectivityPinValue
#define ReflectivityPinValue REFLECTIVITYSIMPLE
#endif


#define NeedReflection ((SpecularPinValue == PRESENT) || (ReflectivityPinValue > REFLECTIVITYOFF))
#define NeedSpecular   ((SpecularPinValue == PRESENT) || (EmissivePinValue == EMISSIVEFROMSPECULAR))
#define NeedNormal (NeedReflection || (LightingPinValue != LIGHTINGBAKED))
#define NewInstancing ((InstancingValue == PRESENT) && (SkeletalMeshPinValue == NONE))

//
struct VS_IN
{
	float3 Position : POSITION;
#if NeedNormal
	#if NormalMapPinValue == PRESENT
		float3 Tangent  : TANGENT;
		float3 Binormal : BINORMAL;
	#endif
		float3 Normal   : NORMAL;
#endif

	float2 UV       : TEXCOORD0;

#if SkeletalMeshPinValue == PRESENT
	float4 Weights : BLENDWEIGHT0;
	int4   Indices : BLENDINDICES0;
#elif LightingPinValue == LIGHTINGINSTANCEDSH || NewInstancing
	int InstanceId : BLENDINDICES0;
#endif

#if LightingPinValue == LIGHTINGBAKED
	float4 Color1 : COLOR0; // Additional color channel
  float4 Color2 : COLOR1;
#endif
};

#define ColorInVS_OUT ((LightingPinValue == LIGHTINGBAKED) || (LightingPinValue == LIGHTINGINSTANCEDSH) || LinearSHfromVS)
#define ReflectInVS (NormalMapPinValue != PRESENT)
// #define ReflectInVS ((NormalMapPinValue != PRESENT) && (ShaderQualityValue != BEST))

#if RenderModeValue == RENDERNORMAL

struct VS_OUT
{
	float2 UV       : TEXCOORD0;

#if NeedReflection
  #if ReflectInVS
    half3  reflVec : TEXCOORD1;
  #else
    float3  WView  : TEXCOORD1;
  #endif
#endif

#if DO_DEPTH_OUT
	float4 PositionWSCS : TEXCOORD2;
#else
	float3 PositionWSCS : TEXCOORD2;
#endif

#if ColorInVS_OUT
	float3 Color    : COLOR0; // Additional color channel or Computed SH (for instancing)
#endif

#if NeedNormal
	#if NormalMapPinValue == PRESENT
		float3x3 TBN  : TEXCOORD3;
	#elif LightingPinValue != LIGHTINGINSTANCEDSH
		float3 Normal : TEXCOORD3;
	#endif
#endif
};

#else // #if RenderModeValue == RENDERNORMAL

struct VS_OUT 
{ 
	float2 UV : TEXCOORD0;
#if RenderModeValue == RENDERTOSHADOW
	float2 ZW : TEXCOORD1;
#endif // #if RenderModeValue == RENDERTOSHADOW
};

#endif

#if LightingPinValue == LIGHTINGINSTANCEDSH
struct InstanceData
{
	float4x3 worldMatrix;
	float4   shConstants[7];
};

float3 instancingAmbient : register( INSTANCING_AMBIENTCOLOR );
float4 instancingDiffuse : register( INSTANCING_DIFFUSE_COEFF );
float4 instancingColorMin : register( INSTANCING_COLOR_MIN );
float4 instancingColorMax : register( INSTANCING_COLOR_MAX );

InstanceData instanceData[MAX_INSTANCES_COUNT] : register ( INSTANCE_DATA );
#elif NewInstancing
float4x3 instanceData[MAX_INSTANCES_COUNT] : register ( VSHADER_LOCALCONST9 );
#endif // LightingPinValue == LIGHTINGINSTANCEDSH

float3 processVectorVS( float3 v ) { return normalize(v); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	// Choose matrix
#if SkeletalMeshPinValue == PRESENT
	float4x3 worldMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
#elif LightingPinValue == LIGHTINGINSTANCEDSH
  float4x3 worldMatrix = instanceData[In.InstanceId].worldMatrix;
#elif NewInstancing
  float4x3 worldMatrix = instanceData[In.InstanceId];
#else
	float4x4 worldMatrix = World;
#endif

	// Transform position
	float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );

#if RenderModeValue == RENDERNORMAL
	// Scroll texture coordinates
	Out.UV.xy = In.UV;

  Out.PositionWSCS.xyz = WPos;
#if DO_DEPTH_OUT
  Out.PositionWSCS.w = ClipSpacePosition.w;
#endif
	// Transform TBN (or only N)
#if NeedNormal
	float3 normal = processVectorVS( mul( In.Normal, (float3x3)worldMatrix ) );
  #if NormalMapPinValue == PRESENT
  	Out.TBN[0] = processVectorVS( mul( In.Tangent, (float3x3)worldMatrix ) );
  	Out.TBN[1] = processVectorVS( mul( In.Binormal,(float3x3)worldMatrix ) );
  	Out.TBN[2] = normal;
  #elif LightingPinValue != LIGHTINGINSTANCEDSH
    Out.Normal = normal;
  #endif
#endif

	// Not normalized eye direction in WCS
#if NeedReflection
  #if ReflectInVS
    Out.reflVec = normalize( reflect(WPos - WEyePos, normal) );
  #else
    Out.WView = WPos - WEyePos;
  #endif
#endif

	// Pass color	
#if LightingPinValue == LIGHTINGBAKED
	Out.Color.rgb = lerp(In.Color1.rgb * In.Color1.a, In.Color2.rgb * In.Color2.a, vs_nightParams.x) * 255.0; // nightFraction
#elif LightingPinValue == LIGHTINGINSTANCEDSH
	float3 shColor = DecodeSH( normal, instanceData[In.InstanceId].shConstants );
	Out.Color.rgb = instancingDiffuse.rgb * ( instancingAmbient + instancingDiffuse.a * shColor );
	Out.Color.rgb = clamp(Out.Color.rgb, instancingColorMin, instancingColorMax );
#elif LinearSHfromVS
	Out.Color.rgb = DecodeLinearSH( normal );
#endif

#else // #if RenderModeValue == RENDERNORMAL

	// Scroll texture coordinates
	Out.UV = In.UV;
#if RenderModeValue == RENDERTOSHADOW
	Out.ZW = ClipSpacePosition.zw;
#endif // #if RenderModeValue == RENDERTOSHADOW

#endif

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );
sampler normalMapSampler  : register( s1 );
sampler specMapSampler    : register( s2 );

float4 outputMul : register( SAMPLER0_MUL );
float4 outputAdd : register( SAMPLER0_ADD );

#if NeedSpecular
float4 specularMul : register( SAMPLER2_MUL );
float4 specularAdd : register( SAMPLER2_ADD );
#endif // specular

float4 diffuseColorLighting : register( BASICMAT_DIFFUSE1 );

float4 opacityEmissiveReflectivitySpecPower : register( OPACITY_AND_OTHERS );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if RenderModeValue != RENDERNORMAL
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

half4 MainPass_PSMain( VS_OUT In ) : COLOR0
{
	// Sample diffuse texture for alpha test
	half4 diffuseMap = tex2D(diffuseMapSampler, In.UV.xy);
#if RenderModeValue == RENDERTOSHADOW
	return half4( (In.ZW.x/In.ZW.y).xxx, diffuseMap.a );
#elif RenderModeValue == RENDERSHAPEONLY
	return half4(1, 1, 1, diffuseMap.a); // does anybody need any specific color?
#else
#error Unknown RenderModeValue
#endif // #if RenderModeValue == RENDERTOSHADOW
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else // normal rendering
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PS_OUT
{
  half4  color : COLOR0;
#if DO_DEPTH_OUT
  float4 z     : COLOR1;
#endif
};

#if LightingPinValue >= LIGHTINGDYNAMIC

float4 lightData[2 * POINTLIGHTSCOUNT] : register(POINTLIGHTSDATA); // pos, color
float4 lightZone[(POINTLIGHTSCOUNT + 3)/4] : register(POINTLIGHTFACTOR); // 1/radius^2

#define POINTLIGHTSCOUNT_ACTUAL (LightingPinValue - LIGHTINGDYNAMIC)

half3 Lighting( float3 Position, half3 Normal )
{
  half3 color;
  color  = light1DiffuseColor * saturate(dot(Normal, light1Direction));
  color += light2DiffuseColor * saturate(dot(Normal, light2Direction));

  for (int i = 0; i < POINTLIGHTSCOUNT_ACTUAL; i += 4)
  {
    const int numComponents = min(4, POINTLIGHTSCOUNT_ACTUAL - i);
    const int startIdx = 2*i;
    // switch() doesn't compile properly 
    if(numComponents == 1)
    {
      float3 L = lightData[startIdx].xyz - Position;
      float LdotL = dot(L,L);
      half attn = saturate(LdotL * lightZone[i/4].x) - 1;
      half NdotL = saturate(dot(Normal, L) * rsqrt(LdotL));
      NdotL *= attn*attn;
      color += lightData[startIdx+1].rgb * NdotL;
    } else
    if(numComponents == 2)
    {
      half2 NdotL;
      float2 LdotL;
      
      float3 L = lightData[startIdx].xyz - Position;
      LdotL.x = dot(L,L);
      NdotL.x = dot(Normal, L);
      
      L = lightData[startIdx+2].xyz - Position;
      LdotL.y = dot(L,L);
      NdotL.y = dot(Normal, L);
      
      half2 attn = saturate(LdotL * lightZone[i/4]) - 1;
      NdotL = saturate(NdotL * rsqrt(LdotL));
      NdotL *= attn*attn;

      color += lightData[startIdx+1].rgb * NdotL.x + lightData[startIdx+3].rgb * NdotL.y;
    } else
    if(numComponents == 3)
    {
      half3 NdotL;
      float3 LdotL;
      
      float3 L = lightData[startIdx].xyz - Position;
      LdotL.x = dot(L,L);
      NdotL.x = dot(Normal, L);
      
      L = lightData[startIdx+2].xyz - Position;
      LdotL.y = dot(L,L);
      NdotL.y = dot(Normal, L);
      
      L = lightData[startIdx+4].xyz - Position;
      LdotL.z = dot(L,L);
      NdotL.z = dot(Normal, L);
      
      half3 attn = saturate(LdotL * lightZone[i/4]) - 1;
      NdotL = saturate(NdotL * rsqrt(LdotL));
      NdotL *= attn*attn;

      for(int j = 0; j < numComponents; j++)
        color += lightData[2*(i+j)+1].rgb * NdotL[j];
    } else
    if(numComponents == 4)
    {
      half4 NdotL;
      float4 LdotL;
      
      float3 L = lightData[startIdx].xyz - Position;
      LdotL.x = dot(L,L);
      NdotL.x = dot(Normal, L);
      
      L = lightData[startIdx+2].xyz - Position;
      LdotL.y = dot(L,L);
      NdotL.y = dot(Normal, L);
      
      L = lightData[startIdx+4].xyz - Position;
      LdotL.z = dot(L,L);
      NdotL.z = dot(Normal, L);
      
      L = lightData[startIdx+6].xyz - Position;
      LdotL.w = dot(L,L);
      NdotL.w = dot(Normal, L);
      
      half4 attn = saturate(LdotL * lightZone[i/4]) - 1;
      NdotL = saturate(NdotL * rsqrt(LdotL));
      NdotL *= attn*attn;

      for(int j = 0; j < numComponents; j++)
        color += lightData[2*(i+j)+1].rgb * NdotL[j];
    }
  }

  return color;
}
#endif

PS_OUT MainPass_PSMain( VS_OUT In )
{
	// Retrieve normal
#if NeedNormal && (LightingPinValue != LIGHTINGINSTANCEDSH)
	#if NormalMapPinValue == PRESENT
		half4 normalMap = tex2D(normalMapSampler, In.UV.xy);
		half3 normal = mul(normalMap.rgb * 2 - 1, In.TBN);
	#else
		half3 normal = In.Normal;
	#endif
#else
	half3 normal = float3(0,0,0); // It will be automatically deprecated because it wouldn't be used
#endif

	// Sample diffuse texture
	half4 diffuseMap = tex2D(diffuseMapSampler, In.UV.xy);

	// Sample specular texture
#if SpecularMapPinValue == PRESENT
	half4 specularMap = tex2D(specMapSampler, In.UV.xy);
#endif

#if NeedReflection
  #if ReflectInVS
    half3 reflVec = normalize(In.reflVec);
  #else
	  half3 reflVec = normalize( reflect( In.WView, normal ) );
  #endif
#endif

	// Reflection 
#if ReflectivityPinValue > REFLECTIVITYOFF
	half reflectionCoeff = opacityEmissiveReflectivitySpecPower.z;
 	#if ReflectivityPinValue == REFLECTIVITYFROMNORMALMAP
 		reflectionCoeff *= normalMap.a;
 	#elif ReflectivityPinValue == REFLECTIVITYFROMSPECULARMAP
 		reflectionCoeff *= specularMap.a;
 	#endif

	half3 reflectionMap = texCUBE( envMapSampler, reflVec );
	diffuseMap.rgb = lerp( diffuseMap.rgb, reflectionMap, reflectionCoeff );
#endif

	// Diffuse lighting
	half4 outputColor; 
#if (LightingPinValue == LIGHTINGBAKED) || (LightingPinValue == LIGHTINGINSTANCEDSH)
	outputColor.rgb = In.Color; 
#elif LightingPinValue >= LIGHTINGDYNAMIC
	outputColor.rgb = diffuseColorLighting.rgb * ( ambientColor + diffuseColorLighting.a * Lighting( In.PositionWSCS.xyz, normal ) ); 
#else // Use spherical harmonics
  #if NormalMapPinValue == PRESENT
	outputColor.rgb = diffuseColorLighting.rgb * ( ambientColor + diffuseColorLighting.a * DecodeSHinPS( normal ) ); 
  #else
	outputColor.rgb = diffuseColorLighting.rgb * ( ambientColor + diffuseColorLighting.a * DecodeSHinPS( normal, In.Color ) ); 
  #endif
#endif
	outputColor.rgb *= diffuseMap.rgb;

  // Specular lighting
#if NeedSpecular
	#if SpecularPinValue == PRESENT
		half3 specular = pow( saturate(dot(reflVec, WSunDir)), opacityEmissiveReflectivitySpecPower.w );
	#else
		half3 specular = 1.f;
	#endif

	#if SpecularMapPinValue == PRESENT
		specular *= specularMul * specularMap.rgb + specularAdd;
	#else
		specular *= specularMul;
	#endif
  outputColor.rgb += specular * ps_nightParams.y; // nightSpecularReduction
#endif

	PS_OUT output;
  outputColor.a = diffuseMap.a;
	output.color.rgb = outputMul.rgb * outputColor.rgb + outputAdd.rgb;
  
	// Applying opacity & emissive
#if OpacityPinValue == PRESENT
  outputColor.a *= opacityEmissiveReflectivitySpecPower.x;
  // output.color.rgb *= outputColor.a; // pre-multiplied alpha
#endif

#if EmissivePinValue != EMISSIVEOFF
  half emissive = opacityEmissiveReflectivitySpecPower.y;
  #if EmissivePinValue == EMISSIVEFROMSPECULAR
    outputColor.a = 1 - lerp(emissive * ComputeLuminance(specular) * diffuseMap.a, diffuseMap.a, BLOOM_ENCODING_THRESHOLD);
  #else
    outputColor.a = EncodeBloomVal(diffuseMap.a, emissive);
  #endif
#endif
  output.color.a = outputColor.a;

#if DO_DEPTH_OUT
	output.z = In.PositionWSCS.w;
#endif
	return output;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // not shadows
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
