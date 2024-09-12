#include "common.hlsl"

///////////////// VS /////////////////////
VS_CONSTANT( float4x4 MatWorldViewProj	 : register(c0); )
VS_CONSTANT( float4x4 MatWorld		 : register(c4); )
VS_CONSTANT( float4x4 MatViewProj: register(c8); )


float3 SunLightDirection		 : register(c14);
float4 SunLightColor				 : register(c15);
float4 SunSpecularColor			: register(c16);

float3 CameraViewVector			: register(c17);
float3 CameraViewVectorPixel : register(c26);

PS_CONSTANT( float3 AmbientColor				 : register(c0); )
#if DIFFUSE == 1
	PS_CONSTANT( float4 DiffuseColor			 : register(c1); )
#endif


#if OMNILIGHTS > 0 
	float4 OmniLightsPositionsAndRadiuses[OMNILIGHTS] : register(c18);
	float4 OmniLightsColors[OMNILIGHTS] : register(c22);
#endif

static const int MAX_MATRICES = 75;
VS_CONSTANT( float4x3 BonesMatrices[MAX_MATRICES] : register(c30); )


struct VS_OUTPUT
{
	float4 Position				 : POSITION;	 // vertex position
	float3 Normal					 : TEXCOORD0;	// vertex normal
	float2 Texcoord				 : TEXCOORD1;	// vertex diffuse texcoords
	float3 WorldPosition		: TEXCOORD2;
#if NORMALMAP == 1
	float3 SunLightDirInTangentSpace : TEXCOORD3;
	float3 CameraDirInTangentSpace	 : TEXCOORD4;
#endif
#if NORMALMAP == 0
	float3 SunLightDir : TEXCOORD3;
	float3 CameraDir	 : TEXCOORD4;
#endif
};

struct VS_INPUT
{
	float4 Position				 : POSITION;
	float3 Normal					 : NORMAL;
	float3 Tangent					: BINORMAL;
	float3 Binormal				 : TANGENT;
	float2 Texcoord				 : TEXCOORD0;
	float4 Weights					: BLENDWEIGHT0;
	int4 Indices						: BLENDINDICES0;
};			

#ifdef VS
VS_OUTPUT VS_main(VS_INPUT Input)
{
		VS_OUTPUT Output;

		float4 weights = Input.Weights;
		int4 indices = 255 * Input.Indices.zyxw;//.zyxw; // rgba -> bgra
		
		float4x3 skinMatrix = weights[0] * BonesMatrices[ indices[0] ];
		skinMatrix += weights[1] * BonesMatrices[ indices[1] ];
		skinMatrix += weights[2] * BonesMatrices[ indices[2] ];
		skinMatrix += weights[3] * BonesMatrices[ indices[3] ];

		float3 worldPos = mul( Input.Position, skinMatrix );
		float3 normal = normalize( mul( Input.Normal, (float3x3)skinMatrix ) );

		Output.Position = mul( float4(worldPos, 1.0), MatViewProj );
		Output.Normal = normal;
		Output.Texcoord = Input.Texcoord;
		Output.WorldPosition = worldPos;

		#if NORMALMAP == 1 
			float3x3 matTangentSpace; 
			
			matTangentSpace[0] = normalize( mul( Input.Tangent, (float3x3)skinMatrix ) ); // x
			matTangentSpace[1] = normalize( mul( Input.Binormal, (float3x3)skinMatrix ) );// y
			matTangentSpace[2] = normal;	// z

			// Calculate light vector and move into tangent space
			Output.SunLightDirInTangentSpace.x = dot(SunLightDirection, matTangentSpace[0]); 
			Output.SunLightDirInTangentSpace.y = dot(SunLightDirection, matTangentSpace[1]); 
			Output.SunLightDirInTangentSpace.z = dot(SunLightDirection, matTangentSpace[2]); 

			Output.CameraDirInTangentSpace.x = dot(CameraViewVector, matTangentSpace[0]); 
			Output.CameraDirInTangentSpace.y = dot(CameraViewVector, matTangentSpace[1]); 
			Output.CameraDirInTangentSpace.z = dot(CameraViewVector, matTangentSpace[2]); 
		#endif

		#if NORMALMAP == 0
			Output.SunLightDir = SunLightDirection;
			Output.CameraDir = CameraViewVector;
		#endif

		return Output;
}
#endif // VS

#if DIFFUSE == 0
	sampler DiffuseMap : register(s0);
#endif
#if SPECULAR > 0
	sampler SpecularMap : register(s1);
#endif
#if NORMALMAP == 1
	sampler NormalMap : register(s2);
#endif
#if SPECULAR == 2
	sampler SpecularCubeMap : register(s3);
#endif

//////////////////////////// PS /////////////////////////////////////////////////////
#ifdef PS
float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float4 diffuse;
	float4 Output;

	float3 normal;
#if NORMALMAP == 1 
	normal = tex2D(NormalMap, Input.Texcoord).xyz * 2 - float3(1,1,1);
#endif
#if NORMALMAP == 0
	normal = normalize(Input.Normal); 
#endif

#if DIFFUSE == 0	
	diffuse = tex2D(DiffuseMap, Input.Texcoord);
#endif
#if DIFFUSE == 1
	diffuse = DiffuseColor;
#endif

	float sunAffectValue;
#if NORMALMAP == 1
	sunAffectValue = max( 0, dot( normal, Input.SunLightDirInTangentSpace ) );
#endif
#if NORMALMAP == 0
	sunAffectValue = max( 0, dot( normal, Input.SunLightDir ) );
#endif
	float3 sunAffectColor = SunLightColor.xyz * SunLightColor.w * sunAffectValue;

	float3 resultLightColor = sunAffectColor + AmbientColor;
	
#if SPECULAR == 2
	#if NORMALMAP == 0
		float v = min(tex2D(SpecularMap, Input.Texcoord).a , 1);
		diffuse = diffuse * v + texCUBE(SpecularCubeMap, reflect(Input.CameraDir, normal)) * (1 - v);// * 0.001;

		float3 sv = normalize( reflect(Input.SunLightDir, normal) );
		float4 spec = tex2D(SpecularMap, Input.Texcoord);
		float specularValue = pow(max(0, dot(sv, Input.CameraDir) ), spec.a * 550) * 3;
		resultLightColor += texCUBE(SpecularCubeMap, reflect(Input.CameraDir, normal)) * specularValue;
	#endif
	#if NORMALMAP == 1
		float3 sv = normalize( reflect(Input.SunLightDirInTangentSpace, normal) );
		float4 spec = tex2D(SpecularMap, Input.Texcoord);
		float specularValue = pow(max(0, dot(sv, Input.CameraDirInTangentSpace) ), spec.a * 10) * 3;

		float v = min(tex2D(SpecularMap, Input.Texcoord).a * specularValue * 0.4, 1);
		diffuse.xyz = diffuse.xyz * (1 - v) + texCUBE(SpecularCubeMap, reflect(CameraViewVectorPixel, Input.Normal)).xyz * v;// * 0.001;

		resultLightColor += texCUBE(SpecularCubeMap, reflect(CameraViewVectorPixel, Input.Normal)) * specularValue;
	#endif
#endif
	#if	SPECULAR == 1 
		float3 reflectedSunVector;
		#if NORMALMAP == 1
			reflectedSunVector = normalize( reflect(Input.SunLightDirInTangentSpace, normal) );
		#endif
		#if NORMALMAP == 0
			reflectedSunVector = normalize( reflect(Input.SunLightDir, normal) );
		#endif

		float4 spec = tex2D(SpecularMap, Input.Texcoord);

		float specularValue;
		#if NORMALMAP == 1
			specularValue = pow(max(0, dot(reflectedSunVector, Input.CameraDirInTangentSpace) ), spec.a * 150) * 3;
		#endif
		#if NORMALMAP == 0
			specularValue = pow(max(0, dot(reflectedSunVector, Input.CameraDir) ), spec.a * 150) * 3;
		#endif

		float3 specularAffectColor = specularValue * spec.xyz;
		resultLightColor += specularAffectColor;
	#endif

	#if OMNILIGHTS > 0
		for ( int i = 0; i < OMNILIGHTS; i++)
		{
			float3 vecFromLightToVertex = OmniLightsPositionsAndRadiuses[i].xyz - Input.WorldPosition.xyz;
			float3 omniVec = normalize( vecFromLightToVertex );
			float lengthSqr = dot(vecFromLightToVertex, vecFromLightToVertex);
			float fade = clamp( ( (1 /	sqrt(lengthSqr) ) - OmniLightsPositionsAndRadiuses[i].w ) * OmniLightsColors[i].w, 0, 1); 
/*
			#if SPECULAR == 1
				float3 reflectedOmniVec = reflect(omniVec, normal);
				resultLightColor += OmniLightsColors[i].xyz * max(0, dot(reflectedOmniVec, normal) ) * fade;
			#endif
*/
			resultLightColor += OmniLightsColors[i].xyz * max(0, dot(omniVec, normal) ) * fade;
		}
	#endif

	Output = float4( resultLightColor, 1 ) * diffuse;

	return Output;
}
#endif // PS
