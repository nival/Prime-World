// Statistics on used registers is gathered here:
// Do not forget to update.

#include "_common.hlsl"
#include "_commonSkinning.hlsl"
#include "_commonDistortion.hlsl"
#include "_bloomEncoding.hlsl"
#include "_applyOpacity.hlsl"

sampler diffuse1Map : register( s0 );
sampler diffuse2Map : register( s1 );

float4 diffuse1Mul : register( SAMPLER0_MUL );
float4 diffuse1Add : register( SAMPLER0_ADD );
float4 diffuse2Mul : register( SAMPLER1_MUL );
float4 diffuse2Add : register( SAMPLER1_ADD );

float4 uvOffsetBoth  : register( VSHADER_LOCALCONST0 );

struct VS_IN
{
  float3 Position : POSITION;
#if MultiplyVertexColorPinValue == PRESENT
  float4 Color    : COLOR0;
#endif
  float2 UV       : TEXCOORD0;
#if SkeletalMeshPinValue == 1
  float4 Weights : BLENDWEIGHT0;
  int4 Indices   : BLENDINDICES0;
#endif
};

struct VS_OUT
{
#if MultiplyVertexColorPinValue == PRESENT
  float4 Color  : COLOR0;
#endif
  float4 UV     : TEXCOORD0;
#if DistortionPinValue != DISTORTNONE
  float2 UVNoise  : TEXCOORD1;
  float  Z : TEXCOORD2;
#endif
};

void MainPass_VSMain( VS_IN In, out float4 PositionCS : POSITION, out VS_OUT Out )
{
  float4 PositionWS;
#if SkeletalMeshPinValue == 1
  float4x3 skinMatrix = MakeSkinnedMatrix(In.Weights, In.Indices.xyzw);
  PositionWS = float4( mul( float4( In.Position, 1.0 ), skinMatrix ), 1.0 );
#else
  PositionWS = mul( float4( In.Position, 1.0 ), World );
#endif
  PositionCS = mul( PositionWS, ViewProjection );

#if MultiplyVertexColorPinValue == PRESENT
  Out.Color = In.Color;
#endif

#if DistortionPinValue != DISTORTNONE
  Out.UVNoise = In.UV.xy;
  Out.Z = PositionCS.w;
#endif
  Out.UV = In.UV.xyxy + uvOffsetBoth;
}

half4 MainPass_PSMain( VS_OUT In, float4 PixelPos : VPOS ) : COLOR
{
  half4 texColor = diffuse1Mul * tex2D(diffuse1Map, In.UV.xy) + diffuse1Add;

  half4 diffuseColor = texColor;
	ApplyOpacity(diffuseColor);

#if OpacityAndEmissiveModePinValue != EMISSIVE
  #if DistortionPinValue == DISTORTNOISE
    half  fxScale = texColor.a / In.Z;
    half3 backbuffer = SampleBackbuffer(PixelPos, SampleDistortion(In.UVNoise, fxScale));
    diffuseColor = half4(lerp(backbuffer, diffuseColor.rgb, diffuseColor.a), 1);
  #elif DistortionPinValue == DISTORTMAP
    half  fxScale = diffuseColor.a / In.Z;
    half3 backbuffer = SampleBackbuffer(PixelPos, ScaleDistortion(diffuseColor.rg, fxScale));
    diffuseColor = half4(backbuffer, 1);
  #endif

  #if MultiplyVertexColorPinValue == PRESENT
    diffuseColor *= In.Color;
  #endif
#else
  diffuseColor.w = EncodeBloomVal(diffuseColor.w, opacityAndEmissive.y);
#endif

  return diffuseColor;
}
