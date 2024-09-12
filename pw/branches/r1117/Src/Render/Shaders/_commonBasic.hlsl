//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Samplers

sampler diffuseMapSampler : register( s0 );

#if NormalMapPinValue > 0
sampler normalMapSampler : register( s1 );
#endif

#if DarkMapPinValue == 1
sampler darkMapSampler : register( s2 );
#endif

#if SpecularMapPinValue == 1
sampler specMapSampler : register( s3 );
#endif

#if WaterBottomPinValue == 1
sampler waterGradSampler  : register( s5 );
sampler waterMapSampler    : register( WATERREFLECTIONSAMPLERINDEX );
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// "MAD" constants

float4 diffuseMultiplier : register( c20 );
float4 diffuseAdd         : register( c21 );

float4 normalMultiplier : register( c22 );
float4 normalAdd          : register( c23 );

float4 darkMultiplier : register( c24 );
float4 darkAdd          : register( c25 );

float4 specularMultiplier : register( c26 );
float4 specularAdd          : register( c27 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pixel shader constants

float4 WaterBottomPars    : register( c8 ); 
