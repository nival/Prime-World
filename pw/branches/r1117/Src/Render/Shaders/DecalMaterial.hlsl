#include "_common.hlsl"
#include "_commonDistortion.hlsl"
#include "_applyOpacity.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if InstancingValue == PRESENT
struct InstanceData
{
	float4x3 worldMatrix;
	float2   opacityAndPlane;
};

InstanceData instanceData[MAX_INSTANCES_COUNT] : register ( INSTANCE_DATA );
#else
float planeLevel : register(VSHADER_LOCALCONST0);
#endif

struct VS_INPUT
{
  float3 Position : POSITION;
#if InstancingValue == PRESENT
	int InstanceId : BLENDINDICES0;
#endif
};      

struct VS_OUTPUT
{
  float4 PositionCSplane : TEXCOORD0; // (p, q, 0, z)
  float4 PositionWSeye : TEXCOORD1; // (v.x, v.y, e.x, e.y)
#if InstancingValue == PRESENT
	float opacity : TEXCOORD2;
#endif
};

VS_OUTPUT MainPass_VSMain(VS_INPUT In, out float4 PositionCS : POSITION)
{
  VS_OUTPUT Out;

  float4 PositionWS;
#if InstancingValue == PRESENT
  float planeLevel = instanceData[In.InstanceId].opacityAndPlane.y;
  Out.opacity = instanceData[In.InstanceId].opacityAndPlane.x;
  float4x3 WorldMatrix = instanceData[In.InstanceId].worldMatrix; 
#else
  float4x3 WorldMatrix = World; 
#endif
  PositionWS = float4( mul(float4(In.Position, 1.0), WorldMatrix), 1.0f );
  PositionCS = mul( PositionWS, ViewProjection );

  // apply scale to UV coordinates
  float4 scale = float4(1, 1, 1, 0);
  scale.x = 1.0 / length(WorldMatrix._11_12);
  scale.y = 1.0 / length(WorldMatrix._21_22);
  scale *= scale;

  float2x2 WorldInv;
  WorldInv._11_21 = WorldMatrix._11_12 * scale.x;
  WorldInv._12_22 = WorldMatrix._21_22 * scale.y;

  float2 origin = mul(WorldMatrix._41_42, WorldInv);
  Out.PositionCSplane = PositionCS; // note: .xyz is not used, xy is overwritten below
  Out.PositionWSeye.xy = mul(PositionWS.xy, WorldInv) - origin;
  Out.PositionWSeye.zw = mul(WEyePos.xy, WorldInv) - origin;

#if DecalPlanePinValue == PRESENT
  Out.PositionCSplane.xy = float2(WEyePos.z - planeLevel, WEyePos.z - PositionWS.z);
#endif
  
  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler diffuseMap : register(s0);
sampler depthMap : register(s2);
#if DecalModeValue == DUALDEPTH
sampler depthMapTerrain : register(s3);
#endif

float4 diffuseMul : register( SAMPLER0_MUL );
float4 diffuseAdd : register( SAMPLER0_ADD );
float4 scaleOffset : register(PSHADER_LOCALCONST2);
#if DecalModeValue == ZDECODE
float2 QZnQ : register(PSHADER_LOCALCONST3);
#endif

float2 GetProjectionWS(VS_OUTPUT In, float2 PixelPos, out float z)
{
  float2 uv = PixelPos * screenScaleOffset.xy + screenScaleOffset.zw;
  z = tex2D(depthMap, uv);
#if DecalModeValue == ZDECODE
  z = QZnQ.x / (QZnQ.y - z);
#endif
#if DecalPlanePinValue == PRESENT
  float z0 = In.PositionCSplane.w * In.PositionCSplane.x / In.PositionCSplane.y;
  z = min(z, z0);
#endif
#if DecalModeValue == DUALDEPTH
  float z_t = tex2D(depthMapTerrain, uv);
#if DecalPlanePinValue == PRESENT
  z_t = min(z_t, z0);
#endif
  clip( 1.0e-5 * z - abs(z - z_t) );
#endif
  return lerp(In.PositionWSeye.zw, In.PositionWSeye.xy, z / In.PositionCSplane.w);
}

half4 MainPass_PSMain( VS_OUTPUT In, float2 PixelPos : VPOS ) : COLOR0
{
  float z = 1.0;
  float2 prjPosition = GetProjectionWS(In, PixelPos, z);
  float2 uv = prjPosition.xy * scaleOffset.xy + scaleOffset.zw;

  half4 outputColor = tex2Dlod(diffuseMap, float4(uv,0,0));
//  float4 outputColor = tex2D(diffuseMap, uv);
//  if (outputColor.a > 0.0)
//    outputColor.a = 1;

#if DistortionPinValue != PRESENT
  outputColor = outputColor * diffuseMul + diffuseAdd;
#endif

#if InstancingValue == PRESENT
	ApplyOpacity2(outputColor, In.opacity);
#else
	ApplyOpacity(outputColor);
#endif

#if DistortionPinValue == PRESENT
  float fxScale = outputColor.a / z;
  half3 backbuffer = SampleBackbuffer(PixelPos, ScaleDistortion(outputColor.rg, fxScale));
  half3 backbufferMAD = backbuffer * diffuseMul + diffuseAdd;
  outputColor = half4(lerp(backbuffer, backbufferMAD, outputColor.a), outputColor.a);
#endif

#if AccessibilityPinValue == PRESENT
  outputColor.rgb += float3(0, 0.1, 0);
  outputColor.a = 1;
#endif

  return outputColor;
}
