#include "_common.hlsl"

#if paintMode != INWORK
  #define SkeletalMeshPinValue 1
  #include "_commonSkinning.hlsl"
  #undef SkeletalMeshPinValue
#endif  

struct VS_IN
{
	float3 Position : POSITION;
	float2 UV       : TEXCOORD0;
#if paintMode != INWORK
  float4 Weights : BLENDWEIGHT0;
  int4 Indices   : BLENDINDICES0;
#endif
};

struct VS_OUT
{
	float2   UV     : TEXCOORD0;
	float    Z      : TEXCOORD2;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
	VS_OUT Out;

	// Choose matrix
#if paintMode == INWORK
	float4x4 worldMatrix = World;
	float3 WPos = mul( float4( In.Position, 1.0 ), worldMatrix );
#else
  float4x3 skinMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
  float3 WPos = mul( float4( In.Position, 1.0 ), skinMatrix );
#endif

	ClipSpacePosition = mul( float4( WPos, 1.0 ), ViewProjection );

	// Scroll texture coordinates
	Out.UV = In.UV;
	Out.Z = ClipSpacePosition.z;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler draftMapSampler  : register( s0 );
sampler backgroundMapSampler  : register( s1 );
sampler backgroundBaseMapSampler  : register( s2 );
sampler completeMapSampler : register( s3 );
sampler maskSampler   : register( s4 );

float paintFragments[masksNumber + 1] : register( PSHADER_LOCALCONST1 );

struct PS_OUT
{
  float4 color : COLOR0;
  float4 z : COLOR1;
};

static const float3 fragmentFrame = { 5.0 / 255.0, 14.0 / 255.0, 10.0 / 255.0 };  


PS_OUT MainPass_PSMain( VS_OUT In )
{
  // Sample textures
  half3 draftMap = tex2D(draftMapSampler, In.UV).rgb;
  half4 backgroundMap = tex2D(backgroundMapSampler, In.UV);
  half3 backgroundBaseMap = tex2D(backgroundBaseMapSampler, In.UV).rgb;
  half3 completeMap = tex2D(completeMapSampler, In.UV).rgb;
  half  mask = tex2D(maskSampler, In.UV).r;
  half  flow = backgroundMap.a;
	
  half fadeFactor = 0;
  half fragmentBase = fragmentFrame.x;
  [unroll]
  for(int i = 0; i <= masksNumber; ++i, fragmentBase += fragmentFrame.z)
    if(fragmentBase < mask)
      fadeFactor = paintFragments[i];
	  
// WARNING - ps_3_0 hardware can't index constant registers, the compiler will emulate this functionality
// fadeFactor = paintFragments[(mask - fragmentFrame.x)/fragmentFrame.z];

  half maskTotal = step(mask, fragmentFrame.y + masksNumber * fragmentFrame.z);
// fadeFactor *= maskTotal; // There is no need in this, as maskTotal will be applied later

  half fillCoeffDraft = saturate(1 - fadeFactor);
  half fFillSmoothStep = 0.1;
  half alphaByPaint = smoothstep(fillCoeffDraft, fillCoeffDraft + fFillSmoothStep, flow) * smoothstep(0.05, 0.1, flow);

  half4 diffuseMap = half4(backgroundMap.rgb, 1.f);
#if paintMode == INWORK
  diffuseMap.rgb = lerp(diffuseMap.rgb, draftMap, alphaByPaint);
  diffuseMap.rgb = lerp(diffuseMap.rgb, completeMap, saturate(fadeFactor-1));
#elif paintMode == FINAL
  diffuseMap.rgb = completeMap;
#endif
  diffuseMap = half4(lerp(backgroundBaseMap, diffuseMap.rgb, maskTotal), 1.f);

  PS_OUT output;
  output.z     = In.Z; // Output z value
  output.color = diffuseMap;

  return output;
}
