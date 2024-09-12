// Statistics on used registers is gathered here:
// Do not forget to update.

#include "_common.hlsl"
#include "_commonSkinning.hlsl"


#define NewInstancing ((InstancingValue == PRESENT) && (SkeletalMeshPinValue == NONE))

#if NewInstancing
float4x3 instanceData[MAX_INSTANCES_COUNT] : register ( INSTANCE_DATA );
#endif // LightingPinValue == LIGHTINGINSTANCEDSH

//
struct VS_IN
{
	float3 Position : POSITION;
	float2 UV       : TEXCOORD0;

#if SkeletalMeshPinValue == PRESENT
	float4 Weights : BLENDWEIGHT0;
	int4   Indices : BLENDINDICES0;
#elif NewInstancing
	int InstanceId : BLENDINDICES0;
#endif
};


struct VS_OUT
{
#if DO_DEPTH_OUT
	float4 UV       : TEXCOORD0;
#else
	float2 UV       : TEXCOORD0;
#endif
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	// Choose matrix
#if SkeletalMeshPinValue == PRESENT
	float4x3 worldMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
#elif NewInstancing
	float4x3 worldMatrix = instanceData[In.InstanceId];
#else
	float4x4 worldMatrix = World;
#endif

	// Transform position
	float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );

	// Scroll texture coordinates
	Out.UV.xy = In.UV;
#if DO_DEPTH_OUT
	Out.UV.zw = ClipSpacePosition.zw;
#endif

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMapSampler : register( s0 );


half4 MainPass_PSMain( VS_OUT In ) : COLOR0
{
	// Sample diffuse texture for alpha test
	half4 diffuseMap = tex2D(diffuseMapSampler, In.UV.xy);
#if DO_DEPTH_OUT
	return half4( (In.UV.z/In.UV.w).xxx, diffuseMap.a );
#else
	return half4(1, 1, 1, diffuseMap.a); // does anybody need any specific color?
#endif // #if DO_DEPTH_OUT
}
