#define HLSL
#include "../GlobalMasks.h"
#include "MaterialSpec.hlsl"

float4x4 World          : register( c4 );
float4x4 ViewProjection : register( c12 );
float4   WEyePos        : register( c22 );

#if SkeletalMeshPinValue == 1
float4x3 BonesMatrices[MAX_BONES] : register( BONES );
#endif

// Switch off some PINs
#ifdef FORCE_SM20
	#undef DarkMapPinValue
	#define DarkMapPinValue 0
	#undef WaterBottomPinValue
	#define WaterBottomPinValue 0
#endif


//
struct VS_IN
{
	float3 Position : POSITION;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD0;
#if DarkMapPinValue == 1
	float2 UV2 : TEXCOORD1;
#endif
#if SkeletalMeshPinValue == 1
	float4 Weights : BLENDWEIGHT0;
	int4 Indices   : BLENDINDICES0;
#endif
};

struct VS_OUT
{
	float3x3 TBN  : TEXCOORD0; //0,1,2
	float2 UV     : TEXCOORD3;
	float3 WPos   : TEXCOORD4;
	float3 WView  : TEXCOORD5;
#if DarkMapPinValue == 1
	float2 UV2    : TEXCOORD6;
#endif
#if WaterBottomPinValue == 1
	float4 BottomCoords : TEXCOORD8;
#endif
};

float4 WaterBottomMapData : register( c252 );

#if ScrollingUVPinValue == 1
	float uvtime : register( c253 );
	float2 uvspeed : register( c254 );
#endif

VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;
	
	
#if ScrollingUVPinValue == 0	
		Out.UV = In.UV;
	#if DarkMapPinValue == 1
		Out.UV2 = In.UV2;
	#endif
#else
		Out.UV = In.UV + uvspeed*uvtime;
	#if DarkMapPinValue == 1
		Out.UV2 = In.UV2 + uvspeed*uvtime;
	#endif
#endif
	

#if SkeletalMeshPinValue == 1
	float4 weights = In.Weights;
	int4 indices = 255 * In.Indices.xyzw;//.zyxw; // rgba -> bgra
		
	float4x3 skinMatrix = weights[0] * BonesMatrices[ indices[0] ];
	skinMatrix += weights[1] * BonesMatrices[ indices[1] ];
	skinMatrix += weights[2] * BonesMatrices[ indices[2] ];
	skinMatrix += weights[3] * BonesMatrices[ indices[3] ];

	float3 worldPos = mul( float4( In.Position, 1.f ), skinMatrix );
	
	float3 C3 = float3(1,-1,1);
	float3 normal = normalize( mul( In.Normal, (float3x3)skinMatrix ) ) * C3;

	ClipSpacePosition = mul( float4( worldPos, 1.0 ), ViewProjection );
	Out.WPos = worldPos;
	Out.TBN[0] = mul( In.Tangent, (float3x3)skinMatrix ) * C3;
	Out.TBN[1] = mul( In.Binormal,(float3x3)skinMatrix ) * C3;

	Out.TBN[2] = normal;
#else
	//ClipSpacePosition = mul( float4( In.Position, 1.f ), WorldViewProjection );
	ClipSpacePosition = mul( float4( In.Position, 1.f ), World );
	Out.WPos = ClipSpacePosition;
	ClipSpacePosition = mul( ClipSpacePosition, ViewProjection );
	//Out.WPos = mul ( float4( In.Position, 1.f ), World );
	Out.TBN[0] = mul( float4( In.Tangent, 0.f ), World );
	Out.TBN[1] = mul( float4( In.Binormal, 0.f ), World );
	Out.TBN[2] = mul( float4( In.Normal, 0.f ), World );
#endif

	float3 eyeDir = Out.WPos - WEyePos;
	Out.WView = eyeDir;

	return Out;
}


//// pixel


float3 WSunDir : register( c0 );


sampler diffuseMapSampler : register( s0 );

sampler normalMapSampler : register( s1 );

sampler darkMapSampler : register( s2 );





float3 SunDiffuseColor : register( c1 );
float3 SunAmbientColor : register( c2 );

float4 WaterBottomPars : register( c8 ); 

float4 MainPass_PSMain( VS_OUT In ) : COLOR
{
#if DebugPinValue == 0
	float3 norm = In.TBN[2];
	float ldn = dot(WSunDir, norm);
	return float4( ldn.xxx, 1.f );
#endif
#if DebugPinValue == 1
	float3 norm = normalize(In.TBN[2]);
	return float4( norm, 1.f );
#endif
#if DebugPinValue == 2
	float3 mips = tex2D(diffuseMapSampler, In.UV).rgb;
	return float4( mips, 1.f );
#endif
}
