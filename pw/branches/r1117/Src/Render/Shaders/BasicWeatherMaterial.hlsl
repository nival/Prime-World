#include "_common.hlsl"
#include "_commonTemperature.hlsl"

//
struct VS_IN
{
	float3 Position : POSITION;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD0;
};

struct VS_OUT
{
	float3x3 TBN  : TEXCOORD0; //0,1,2
	float2 UV     : TEXCOORD3;
	float3 WView  : TEXCOORD5;
};


VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	float3 WPos;	
	Out.UV = In.UV;

	
	ClipSpacePosition = mul( float4( In.Position, 1.f ), World );
	ClipSpacePosition = mul( ClipSpacePosition, ViewProjection );
	WPos = mul ( float4( In.Position, 1.f ), World );
	Out.TBN[0] = mul( float4( In.Tangent, 0.f ), World );
	Out.TBN[1] = mul( float4( In.Binormal, 0.f ), World );
	Out.TBN[2] = mul( float4( In.Normal, 0.f ), World );

	Out.WView = WPos - WEyePos;

	return Out;
}


half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
	half4 surfaceDiffuseColor = diffuseNormalMultiplier * tex2D( diffuseNormalSampler, In.UV ) + diffuseNormalAdd;
	
#if NormalMapPinValue == 0
	half3 surfaceNormal = normalize( In.TBN[2] );
#else
	half3 Tn = normalize( In.TBN[0] );
	half3 Bn = normalize( In.TBN[1] );
	half3 Nn = normalize( In.TBN[2] );
	half4 bump = bumpNormalMultiplier * tex2D( bumpNormalSampler, In.UV ) + bumpNormalAdd;
	half3 surfaceNormal = normalize( Nn + ( bump.x * Tn + bump.y * Bn ));
#endif
	
	half lightIntensity = saturate( dot(surfaceNormal, normalize(WSunDir)) );
	half3 diffuse = surfaceDiffuseColor.rgb * ( SunAmbientColor + SunDiffuseColor * lightIntensity );
	
	return half4( diffuse,  surfaceDiffuseColor.a );
}
