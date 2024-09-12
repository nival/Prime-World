#include "_common.hlsl"
#include "_commonSkinning.hlsl"

//
struct VS_IN
{
	float3 Position : POSITION;
	float2 UV       : TEXCOORD0;
};

struct VS_OUT
{
	float2   UV       : TEXCOORD0;
	float3   WView    : TEXCOORD1;
	float    Z        : TEXCOORD2;
  float4   Position : TEXCOORD3;
};

float2 uvSpeed : register( VSHADER_LOCALCONST0 );

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
	Out.UV = In.UV;
	Out.Z = ClipSpacePosition.z;


	// Not normalized eye direction in WCS
	Out.WView = WPos - WEyePos;

  Out.Position = ClipSpacePosition;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
sampler diffuseMapSampler : register( s0 );

float4 outputMul : register( SAMPLER0_MUL );
float4 outputAdd : register( SAMPLER0_ADD );

struct PS_OUT
{
  float4 color : COLOR0;
};

PS_OUT MainPass_PSMain( VS_OUT In )
{
	// Sample diffuse texture
	float4 diffuseMap = tex2D(diffuseMapSampler, In.UV);

	PS_OUT output;
	output.color.xyz = outputMul.xyz * diffuseMap.xyz + outputAdd.xyz;
	output.color.w   = diffuseMap.w;

  output.color.a = 1 - saturate( exp ( - pow( length( In.Position.xy / In.Position.w ), 2 ) * 18 ) );
  output.color.a += smoothstep(0.8, 1.05, In.Position.z / 17.5); // In.Position.w;

	return output;
}
