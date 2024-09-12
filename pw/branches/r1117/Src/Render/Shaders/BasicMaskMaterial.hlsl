#include "_common.hlsl"
#include "_commonSkinning.hlsl"
#include "_bloomEncoding.hlsl"

//
struct VS_IN
{
	float3 Position : POSITION;
#if NormalMapPinValue == PRESENT
	float3 Tangent  : TANGENT;
	float3 Binormal : BINORMAL;
#endif
	float3 Normal   : NORMAL;
	float2 UV       : TEXCOORD0;

#if SkeletalMeshPinValue == 1
	float4 Weights : BLENDWEIGHT0;
	int4   Indices : BLENDINDICES0;
#endif
};

struct VS_OUT
{
#if RenderModeValue == RENDERNORMAL

	float2   UV     : TEXCOORD0;
	float3   WView  : TEXCOORD1;
	float    Z      : TEXCOORD2;
#if NormalMapPinValue == PRESENT
	float3x3 TBN    : TEXCOORD3;
#else
	float3   Normal : TEXCOORD3;
#endif

#else

	float2   ZW : TEXCOORD0;

#endif
};

float2 uvSpeed : register( VSHADER_LOCALCONST0 );

float3 processVectorVS( float3 v ) { return normalize(v); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

  uvSpeed = 0;

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
	Out.UV = In.UV + uvSpeed*totalTime;

	Out.Z = ClipSpacePosition.z;

	// Transform position & TBN (or only N)
	//float3 WPos = mul( In.Position, worldMatrix );
	//ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );
	
#if NormalMapPinValue == PRESENT
	Out.TBN[0] = processVectorVS( mul( In.Tangent, (float3x3)worldMatrix ) );
	Out.TBN[1] = processVectorVS( mul( In.Binormal,(float3x3)worldMatrix ) );
	Out.TBN[2] = processVectorVS( mul( In.Normal, (float3x3)worldMatrix ) );
#else
	Out.Normal = processVectorVS( mul( In.Normal, (float3x3)worldMatrix ) );
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
sampler maskSampler       : register( s3 );

float4 specularMul : register( SAMPLER2_MUL );
float4 specularAdd : register( SAMPLER2_ADD );

float3 ambientColorMult       : register( BASICMAT_AMBIENT );
float3 light1DiffuseColorMult : register( BASICMAT_DIFFUSE1 );
float3 light2DiffuseColorMult : register( BASICMAT_DIFFUSE2 );

float4 opacityEmissiveReflectivitySpecPower : register( OPACITY_AND_OTHERS );

struct PS_OUT
{
#if RenderModeValue == RENDERNORMAL
  half4  color : COLOR0;
  float4 z : COLOR1;
#else
  float4 z : COLOR0;
#endif
};

PS_OUT MainPass_PSMain( VS_OUT In )
{
#if RenderModeValue == RENDERNORMAL
#if NormalMapPinValue == PRESENT
	half4 normalMap = tex2D(normalMapSampler, In.UV);
	half3 normal = mul(normalMap * 2 - 1, In.TBN);
#else
	half3 normal = In.Normal;
#endif

	// Sample diffuse texture
	half4 diffuseMap = tex2D(diffuseMapSampler, In.UV);
	half4 mask = tex2D(maskSampler, In.UV);
	
	diffuseMap.a = mask.a;

// 	// Sample specular texture
// #if SpecularMapPinValue == PRESENT
// 	half4 specularMap = tex2D(specMapSampler, In.UV);
// #endif
// 
// 	// Reflection 
// 	half3 reflVec = normalize( reflect( In.WView, normal ) );
// #if ReflectivityPinValue > REFLECTIVITYOFF
// 	half3 reflectionMap = texCUBE( envMapSampler, reflVec );
// 	
// 	half reflectionCoeff = opacityEmissiveReflectivitySpecPower.z;
// 	#if ReflectivityPinValue > REFLECTIVITYSIMPLE
// 		#if (ReflectivityPinValue == REFLECTIVITYFROMNORMALMAP) && (NormalMapPinValue == PRESENT)
// 			reflectionCoeff *= normalMap.w;
// 		#endif
// 		#if (ReflectivityPinValue == REFLECTIVITYFROMSPECULARMAP) && (SpecularMapPinValue == PRESENT)
// 			reflectionCoeff *= specularMap.w;
// 		#endif
// 	#endif
// 
// 	diffuseMap.xyz = lerp( diffuseMap.xyz, reflectionMap, reflectionCoeff );
// #endif
// 
// 	// Diffuse dot product (basic)
// 	half ldn = dot( normal, light1Direction );
// 
// 	// Diffuse lighting
// 	half4 outputColor; 
// 	outputColor.xyz = ambientColorMult + light1DiffuseColorMult * max(0, ldn) + light2DiffuseColorMult * max(0, dot( normal, light2Direction ));
// 	outputColor.xyz *= diffuseMap.xyz;
// 
//   // Specular lighting
// 	#if (LightModePinValue == DIFFUSESPECULAR) || (LightModePinValue == DIFFUSESPECULAROPACITY) || (LightModePinValue == DIFFUSESPECULAREMISSIVE) || (LightModePinValue == DIFFUSESPECULARTOEMISSIVE)
// 		half3 specular = pow( max( 0, dot( reflVec, WSunDir ) ), opacityEmissiveReflectivitySpecPower.w );
// 		if (ldn < 0.0f)
// 			specular = 0;
// 		#if SpecularMapPinValue == PRESENT
// 			specular *= specularMul * specularMap.xyz + specularAdd;
// 		#else
// 			specular *= specularMul;
// 		#endif
// 		outputColor.xyz += specular;
// 	#endif
// 
// 	#if (LightModePinValue == DIFFUSE) || (LightModePinValue == DIFFUSESPECULAR)
// 		outputColor.w = diffuseMap.w;
// 	#elif (LightModePinValue == DIFFUSEOPACITY) || (LightModePinValue == DIFFUSESPECULAROPACITY)
// 		outputColor.w = diffuseMap.w * opacityEmissiveReflectivitySpecPower.x;
// 	#elif (LightModePinValue == DIFFUSEEMISSIVE) || (LightModePinValue == DIFFUSESPECULAREMISSIVE)
// 		outputColor.w = (diffuseMap.w * opacityEmissiveReflectivitySpecPower.y);
// 	#elif (LightModePinValue == DIFFUSESPECULARTOEMISSIVE)
// 		outputColor.w = dot( half3(0.33f, 0.33f, 0.33f), specular ) * opacityEmissiveReflectivitySpecPower.y;
// 	#endif
// 
 	PS_OUT output;
// 	output.color = outputColor;
 	output.z     = In.Z; // Output z value
 	output.color = diffuseMap * opacityEmissiveReflectivitySpecPower.r;
 	return output;

#else

	PS_OUT output;
	output.z = float4( (In.ZW.x/In.ZW.y).xxx, 1.0f );

#endif

	return output;
}
