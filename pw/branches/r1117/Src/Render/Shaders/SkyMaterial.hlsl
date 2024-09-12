#include "_common.hlsl"
#include "_bloomEncoding.hlsl"

//
struct VS_IN
{
	float3 Position : POSITION;
	float2 UV       : TEXCOORD0;
#if BakedVertexLightingPinValue == PRESENT
	float4 Color : COLOR0; // Additional color channel
#endif
};


struct VS_OUT
{
	float2   UV     : TEXCOORD0;

#if BakedVertexLightingPinValue == PRESENT || LinearSHfromVS
	float4 Color : COLOR0; // Additional color channel
#endif
};

float4 uvOffset : register( VSHADER_LOCALCONST0 );

float3 processVectorVS( float3 v ) { return normalize(v); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	float4x4 worldMatrix = World;
	// Transform position & TBN (or only N)
	float3 WPos = mul( float4(In.Position, 1), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );

	// Scroll texture coordinates
	//Out.UV = In.UV + uvSpeed*totalTime;  // old
	Out.UV = In.UV.xyxy + uvOffset;        // new

	// Pass color	
#if BakedVertexLightingPinValue == PRESENT
	Out.Color = In.Color;
#endif

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );

float4 outputMul : register( SAMPLER0_MUL );
float4 outputAdd : register( SAMPLER0_ADD );

struct PS_OUT
{
  half4  color : COLOR0;
};

PS_OUT MainPass_PSMain( VS_OUT In )
{
	// Sample diffuse texture
	float4 diffuseMap = tex2D(diffuseMapSampler, In.UV);

	PS_OUT output;
	output.color.rgb = outputMul * diffuseMap + outputAdd;
	output.color.a   = diffuseMap.a;
	//output.color. = EncodeBloomVal(diffuseMap.a, emissive);

	return output;
}
