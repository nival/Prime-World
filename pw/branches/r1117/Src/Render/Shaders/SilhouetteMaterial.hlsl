#include "_common.hlsl"
#include "_commonSkinning.hlsl"

// Vertex
struct VS_IN
{
	float3 Position : POSITION;
  float3 Normal   : NORMAL;

#if SkeletalMeshPinValue == PRESENT
	float4 Weights : BLENDWEIGHT0;
	int4   Indices : BLENDINDICES0;
#endif
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 params : register(VSHADER_LOCALCONST0);

void MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
#if 0

  // Inflate original model
  In.Position.xyz += thickness * In.Normal.xyz;

	// Choose matrix
#if SkeletalMeshPinValue == PRESENT
	float4x3 worldMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
#else
	float4x4 worldMatrix = World;
#endif

	// Transform position
	float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );

#else

	// Choose matrix
#if SkeletalMeshPinValue == PRESENT
	float4x3 worldMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
#else
	float4x4 worldMatrix = World;
#endif

	// Transform position
	float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
	float3 ViewSpacePosition = mul( float4( WPos, 1.0 ), View );

	// Transform normal
	float3 WNorm = mul( In.Normal, (float3x3)worldMatrix );
	float3 ViewSpaceNormal = mul( WNorm, (float3x3)View );

  // Inflate model in view space
  float2 ScreenNormal = ViewSpaceNormal.xy;
  float sqLength = dot(ScreenNormal, ScreenNormal);
  ScreenNormal = (sqLength == 0) ? 0 : ScreenNormal * rsqrt(sqLength);
  ViewSpacePosition.xy += params.x * ScreenNormal;

	// Transform position
	ClipSpacePosition = mul( float4( ViewSpacePosition, 1.0), projection );
	ClipSpacePosition.z = params.z * ClipSpacePosition.w;

#endif

	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float4 color : register(PSHADER_LOCALCONST0);

struct PS_OUT
{
  half4  color : COLOR0;
#if DO_DEPTH_OUT
  float4 z     : COLOR1;
#endif
};

PS_OUT MainPass_PSMain( ) : COLOR0
{
  PS_OUT output;

  output.color = color;

#if DO_DEPTH_OUT
	output.z = 0.0;
#endif
	return output;
}
