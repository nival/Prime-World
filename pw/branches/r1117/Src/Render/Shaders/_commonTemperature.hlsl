#define HLSL
#include "../GlobalMasks.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Samplers

sampler diffuseFrozenSampler : register( s0 );
sampler diffuseNormalSampler : register( s1 );
sampler diffuseBurnedSampler : register( s2 );

sampler bumpFrozenSampler : register( s3 );
sampler bumpNormalSampler : register( s4 );
sampler bumpBurnedSampler : register( s5 );

sampler specularFrozenSampler : register( s6 );
sampler specularNormalSampler : register( s7 );
sampler specularBurnedSampler : register( s8 );

sampler darkMapSampler : register( s9 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// "MAD" constants

float4 diffuseFrozenMultiplier  : register( SAMPLER0_MUL );
float4 diffuseFrozenAdd         : register( SAMPLER0_ADD );

float4 diffuseNormalMultiplier  : register( SAMPLER1_MUL );
float4 diffuseNormalAdd         : register( SAMPLER1_ADD );

float4 diffuseBurnedMultiplier  : register( SAMPLER2_MUL );
float4 diffuseBurnedAdd         : register( SAMPLER2_ADD );

float4 bumpFrozenMultiplier     : register( SAMPLER3_MUL );
float4 bumpFrozenAdd            : register( SAMPLER3_ADD );

float4 bumpNormalMultiplier     : register( SAMPLER4_MUL );
float4 bumpNormalAdd            : register( SAMPLER4_ADD );

float4 bumpBurnedMultiplier     : register( c30 );
float4 bumpBurnedAdd            : register( c31 );

float4 specularFrozenMultiplier : register( c32 );
float4 specularFrozenAdd        : register( c33 );

float4 specularNormalMultiplier : register( c34 );
float4 specularNormalAdd        : register( c35 );

float4 specularBurnedMultiplier : register( c36 );
float4 specularBurnedAdd        : register( c37 );

float4 darkMultiplier   : register( c38 );
float4 darkAdd          : register( c39 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common functions

half4 ComputeBump(float2 uv, half3 temperatureMask, half terrainTypesMask)
{
	half4 bumpFrozen = bumpFrozenMultiplier * tex2D( bumpFrozenSampler, uv ) + bumpFrozenAdd;
	half4 bumpNormal = bumpNormalMultiplier * tex2D( bumpNormalSampler, uv ) + bumpNormalAdd;
	half4 bumpBurned = bumpBurnedMultiplier * tex2D( bumpBurnedSampler, uv ) + bumpBurnedAdd;
	half4 bump = bumpFrozen * temperatureMask.b + bumpNormal * temperatureMask.g + bumpBurned * temperatureMask.r;
	return bump * terrainTypesMask;
}


float4 ComputeDiffuse(float2 uv, float3 temperatureMask, float terrainTypesMask)
{
#ifndef FORCE_SM20
	float4 diffuseFrozen = (diffuseFrozenMultiplier * tex2D( diffuseFrozenSampler, uv ) + diffuseFrozenAdd) * temperatureMask.b;
	float4 diffuseNormal = (diffuseNormalMultiplier * tex2D( diffuseNormalSampler, uv ) + diffuseNormalAdd) * temperatureMask.g;
	float4 diffuseBurned = (diffuseBurnedMultiplier * tex2D( diffuseBurnedSampler, uv ) + diffuseBurnedAdd) * temperatureMask.r;
#else
	float4 diffuseFrozen = tex2D( diffuseFrozenSampler, uv ) * temperatureMask.b;
	float4 diffuseNormal = tex2D( diffuseNormalSampler, uv ) * temperatureMask.g;
	float4 diffuseBurned = tex2D( diffuseBurnedSampler, uv ) * temperatureMask.r;
#endif

	float4 surfaceDiffuseColor = (diffuseFrozen + diffuseNormal + diffuseBurned ) * terrainTypesMask;
	return surfaceDiffuseColor;
}

float4 ComputeSpecular(float2 uv, float3 temperatureMask, float terrainTypesMask)
{
	float4 specularFrozen = (specularFrozenMultiplier * tex2D( specularFrozenSampler, uv ) + specularFrozenAdd) * temperatureMask.b;
	float4 specularNormal = (specularNormalMultiplier * tex2D( specularNormalSampler, uv ) + specularNormalAdd) * temperatureMask.g;
	float4 specularBurned = (specularBurnedMultiplier * tex2D( specularBurnedSampler, uv ) + specularBurnedAdd) * temperatureMask.r;
	float4 surfacespecularColor = (specularFrozen + specularNormal + specularBurned ) * terrainTypesMask;
	return surfacespecularColor;
}
