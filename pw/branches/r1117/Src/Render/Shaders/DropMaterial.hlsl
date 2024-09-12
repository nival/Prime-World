#include "_common.hlsl"
#include "_commonSkinning.hlsl"
#include "_commonSH.hlsl"
#include "_bloomEncoding.hlsl"

#define SpecularPresent ((LightModePinValue == DIFFUSESPECULAR) || (LightModePinValue == DIFFUSESPECULAROPACITY) || (LightModePinValue == DIFFUSESPECULAREMISSIVE) || (LightModePinValue == DIFFUSESPECULARTOEMISSIVE))
#define NeedNormal ((BakedVertexLightingPinValue != PRESENT) || SpecularPresent || (ReflectivityPinValue > REFLECTIVITYOFF))

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

#if SkeletalMeshPinValue == 1
	float4 Weights : BLENDWEIGHT0;
	int4   Indices : BLENDINDICES0;
#endif

#if BakedVertexLightingPinValue == PRESENT
	float4 Color : COLOR0; // Additional color channel
#endif
};

#if RenderModeValue == RENDERNORMAL

struct VS_OUT
{
	float2   UV     : TEXCOORD0;
	float3   WView  : TEXCOORD1;
	float    Z      : TEXCOORD2;

#if BakedVertexLightingPinValue == PRESENT || LinearSHfromVS
	float4 Color : COLOR0; // Additional color channel
#endif

#if NeedNormal
	#if NormalMapPinValue == PRESENT
		float3x3 TBN    : TEXCOORD3;
	#else
		float3   Normal : TEXCOORD3;
	#endif
#endif
};

#else // #if RenderModeValue == RENDERNORMAL

struct VS_OUT 
{ 
	float2 ZW : TEXCOORD0; 
};

#endif

//float2 uvSpeed : register( VSHADER_LOCALCONST0 );
float4 uvOffset : register( VSHADER_LOCALCONST0 );

float3 processVectorVS( float3 v ) { return normalize(v); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	// Choose matrix
#if SkeletalMeshPinValue == 1
	float4x3 worldMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
  float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );
#else
	float4x4 worldMatrix = World;
	// Transform position & TBN (or only N)
	float3 WPos = mul( float4(In.Position, 1), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );
#endif

#if RenderModeValue == RENDERNORMAL
	// Scroll texture coordinates
	//Out.UV = In.UV + uvSpeed*totalTime;  // old
	Out.UV = In.UV.xyxy + uvOffset;        // new
	

	Out.Z = ClipSpacePosition.z;

	// Pass color	
#if BakedVertexLightingPinValue == PRESENT
	Out.Color = In.Color;
#endif

	// Transform position & TBN (or only N)
#if NeedNormal
#if NormalMapPinValue == PRESENT
	Out.TBN[0] = processVectorVS( mul( In.Tangent, (float3x3)worldMatrix ) );
	Out.TBN[1] = processVectorVS( mul( In.Binormal,(float3x3)worldMatrix ) );
	Out.TBN[2] = processVectorVS( mul( In.Normal, (float3x3)worldMatrix ) );
#else
	Out.Normal = processVectorVS( mul( In.Normal, (float3x3)worldMatrix ) );
  #if LightingPinValue == LIGHTINGSH
	Out.Color.rgb = DecodeLinearSH( Out.Normal );
	Out.Color.a   = 1;
  #endif
#endif
#endif

	// Not normalized eye direction in WCS
	Out.WView = WPos - WEyePos;

#else // #if RenderModeValue == RENDERNORMAL

	Out.ZW = ClipSpacePosition.zw;

#endif

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );
sampler normalMapSampler  : register( s1 );
sampler specMapSampler    : register( s2 );
samplerCUBE reflMapSampler   : register( s3 );

float4 outputMul : register( SAMPLER0_MUL );
float4 outputAdd : register( SAMPLER0_ADD );
float4 specularMul : register( SAMPLER2_MUL );
float4 specularAdd : register( SAMPLER2_ADD );

float4 diffuseColorLighting : register( BASICMAT_DIFFUSE1 );

float4 opacityEmissiveReflectivitySpecPower : register( OPACITY_AND_OTHERS );
float3 reflectivityLerpAddMul : register (c30);
float4 ambientParams          : register (c31);       // rgb - additional local ambient, a - global ambient multiplier

float3 reflectionColors[4]       : register (PSHADER_LOCALCONST6);

struct PS_OUT
{
#if RenderModeValue == RENDERNORMAL
  half4  color : COLOR0;
  float4 z     : COLOR1;
#else
  float4 z : COLOR0;
#endif
};

PS_OUT MainPass_PSMain( VS_OUT In )
{
#if RenderModeValue == RENDERNORMAL

	// Retrieve normal
#if NeedNormal
	#if NormalMapPinValue == PRESENT
		half4 normalMap = tex2D(normalMapSampler, In.UV);
		half3 normal = mul(normalMap * 2 - 1, In.TBN);
	#else
		half3 normal = In.Normal;
	#endif
#else
	half3 normal = half3(0,0,0); // It will be automatically deprecated because it wouldn't be used
#endif

	// Sample diffuse texture
	float4 diffuseMap = tex2D(diffuseMapSampler, In.UV);

	// Sample specular texture
#if SpecularMapPinValue == PRESENT
	float4 specularMap = tex2D(specMapSampler, In.UV);
#endif

	// Reflection 
	half3 reflVec = normalize( reflect( In.WView, normal ) );
	half3 reflectionResult = half3(0, 0, 0);
	half reflectionAdd = reflectivityLerpAddMul.g;
#if ReflectivityPinValue > REFLECTIVITYOFF
	half4 reflectionMap = texCUBE( reflMapSampler, reflVec );
		
	half reflectionCoeff = 1.0f;
	half reflectionLerp = reflectivityLerpAddMul.r;
	half reflectionMul = reflectivityLerpAddMul.b;
	
	#if ReflectivityPinValue > REFLECTIVITYSIMPLE
		#if (ReflectivityPinValue == REFLECTIVITYFROMNORMALMAP) && (NormalMapPinValue == PRESENT)
			reflectionCoeff *= normalMap.w;
		#endif
		#if (ReflectivityPinValue == REFLECTIVITYFROMSPECULARMAP) && (SpecularMapPinValue == PRESENT)
			reflectionCoeff *= specularMap.w;
		#endif
	#endif

 #if (colorizeReflectionMap == ADDCOLOREDALPHA)
  reflectionMap.rgb += reflectionMap.a * reflectionColors[0];
 #elif (colorizeReflectionMap == MULCOLORBYALPHA)
  reflectionMap.rgb *= lerp( half3(1, 1, 1), reflectionColors[0], reflectionMap.a);
 #elif (colorizeReflectionMap == COLORFOREVERYCHANEL)
  half3 colorizeResult = reflectionMap.r * reflectionColors[0];
  colorizeResult += reflectionMap.g * reflectionColors[1];
  colorizeResult += reflectionMap.b * reflectionColors[2];
  colorizeResult += reflectionMap.a * reflectionColors[3];
  reflectionMap.rgb = colorizeResult;
 #endif

	reflectionResult = reflectionMap.rgb * reflectionCoeff;
	diffuseMap.xyz = lerp( diffuseMap.xyz, reflectionMap.rgb, reflectionLerp * reflectionCoeff );
	diffuseMap.xyz *= lerp( 1, reflectionMap.rgb, reflectionMul * reflectionCoeff );



#endif

	// Diffuse dot product (basic)
	half ldn = dot( normal, light1Direction );

	// Diffuse lighting
	half4 outputColor; 
// Use spherical harmonics
#if NormalMapPinValue == PRESENT
	outputColor.xyz = diffuseColorLighting.xyz * ( ambientColor*ambientParams.a + ambientParams.rgb + diffuseColorLighting.w * DecodeSHinPS( normal ) ); 
#else
	outputColor.xyz = diffuseColorLighting.xyz * ( ambientColor*ambientParams.a + ambientParams.rgb + diffuseColorLighting.w * DecodeSHinPS( normal, In.Color ) ); 
#endif
	outputColor.xyz *= diffuseMap.xyz;

  // Specular lighting
	#if SpecularPresent
		half3 specular = pow( saturate( dot(reflVec, WSunDir) ), opacityEmissiveReflectivitySpecPower.w );
		if (ldn < 0.0f)
			specular = 0;
		#if SpecularMapPinValue == PRESENT
			specular *= specularMul * specularMap.xyz + specularAdd;
		#else
			specular *= specularMul;
		#endif
		outputColor.xyz += specular;
	#endif

	// Applying opacity & emissive
	#if (LightModePinValue == DIFFUSE) || (LightModePinValue == DIFFUSESPECULAR)
		outputColor.a = diffuseMap.a;
	#elif (LightModePinValue == DIFFUSEOPACITY) || (LightModePinValue == DIFFUSESPECULAROPACITY)
		outputColor.a = diffuseMap.a * opacityEmissiveReflectivitySpecPower.x;
	#elif (LightModePinValue == DIFFUSEEMISSIVE) || (LightModePinValue == DIFFUSESPECULAREMISSIVE) || (LightModePinValue == DIFFUSESPECULARTOEMISSIVE)
    half emissive = opacityEmissiveReflectivitySpecPower.y;
    #if (LightModePinValue == DIFFUSESPECULARTOEMISSIVE)
      outputColor.a = 1 - lerp(emissive * ComputeLuminance(specular) * diffuseMap.a, diffuseMap.a, BLOOM_ENCODING_THRESHOLD);
    #else
      outputColor.a = EncodeBloomVal(diffuseMap.a, emissive);
    #endif
	#endif

	PS_OUT output;
	output.color.xyz = outputMul.xyz * outputColor.xyz + outputAdd.xyz + reflectionResult*reflectionAdd;
	output.color.w   = outputColor.w;
	output.z     = In.Z; // Output z value

#else

	PS_OUT output;
	output.z = float4( (In.ZW.x/In.ZW.y).xxx, 1.0f );

#endif

	return output;
}
