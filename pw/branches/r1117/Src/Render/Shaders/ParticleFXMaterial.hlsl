#include "_common.hlsl"
#include "_commonBasic.hlsl"
#include "_commonDistortion.hlsl"
#include "_applyOpacity.hlsl"

#if (NewParticlesValue == TRUE)
struct INSTANCE_DATA
{
  float4  constants; // x - cam offset, y - scale, zw - pivot
  float4  xPlaneAxis; // w - dontMulByAlpha & NoAlpha flags
  float4  yPlaneAxis; // w - dontClearAlpha flag
  float4  dmMultiply;
  float4  dmAdd;
};

float4    cornersScale  : register(VSHADER_LOCALCONST0);
INSTANCE_DATA data[PFX_MAX_INSTANCES] : register(VSHADER_LOCALCONST1);

struct VS_INPUT
{
  float4 PositionAndID      : POSITION;
  float4 DirectionAndOrient : NORMAL;
  float4 UV                 : TEXCOORD0;
  float3 RotationAndSize    : TEXCOORD1;
  float4 Color              : COLOR0;
  float4 CornerMask         : TEXCOORD2;
};

struct VS_OUTPUT
{
  float4 Color0                 : COLOR0;
  float4 Color1                 : COLOR1;
  float4 UV                     : TEXCOORD0;
#if DistortionPinValue == PRESENT
  float  Z                      : TEXCOORD1;
#endif
};

#else

float4    cornersScale  : register(VSHADER_LOCALCONST0);
float4    constants     : register(VSHADER_LOCALCONST1); // x - cam offset, y - scale, zw - pivot
float4    xPlaneAxis    : register(VSHADER_LOCALCONST2);
float3    yPlaneAxis    : register(VSHADER_LOCALCONST3);

struct VS_INPUT
{
  float3 Position               : POSITION;
  float3 Direction              : NORMAL;
  float4 UV                     : TEXCOORD0;
  float3 RotationAndSize        : TEXCOORD1;
  float4 Color                  : COLOR0;
  float4 CornerMask             : TEXCOORD2;
};

struct VS_OUTPUT
{
  float4 Color                  : COLOR0;
  float2 UV                     : TEXCOORD0;
#if DistortionPinValue == PRESENT
  float  Z                      : TEXCOORD1;
#endif
};

#endif

float2 UnpackCorner(float4 value, float4 mask)
{
  float4 masked = value * mask;
  return masked.xy + masked.zw;
}

VS_OUTPUT MainPass_VSMain(VS_INPUT Input, out float4 PositionCS : POSITION)
{
  VS_OUTPUT Output;

  // displace corners
#if(NewParticlesValue == TRUE)
  float  id = Input.PositionAndID.w; // Array of structures {constants, xPlaneAxis, yPlaneAxis}
  float2 disp = (UnpackCorner(cornersScale, Input.CornerMask) - data[id].constants.zw) * Input.RotationAndSize.xy * data[id].constants.yy;

  // rotate
  float sinz, cosz;
  sincos(Input.RotationAndSize.z, sinz, cosz);
  float2 rot = float2( disp.x * cosz - disp.y * sinz, disp.x * sinz + disp.y * cosz );

  // get final corner position
  float4 Position = float4(Input.PositionAndID.xyz, 1.0f);

  if(Input.DirectionAndOrient.w == 0)
    Position.xyz += data[id].xPlaneAxis.xyz * rot.x + data[id].yPlaneAxis.xyz * rot.y;

  // Apply camera offset
  float3 offset = normalize(WEyePos.xyz - Position.xyz);
  Position.xyz += offset * data[id].constants.x;

  if(Input.DirectionAndOrient.w == 1) {
    float3 tangentAxis = normalize(cross(offset, Input.DirectionAndOrient.xyz));
    Position.xyz += -tangentAxis * rot.x + Input.DirectionAndOrient.xyz * rot.y;
  }

  PositionCS = mul( Position, ViewProjection );

  Output.UV.xy = UnpackCorner(Input.UV, Input.CornerMask) * float2(1.0, -1.0); // invert V-axis

  float noMulNoAlpha = data[id].xPlaneAxis.w;
  float noAlpha = frac(noMulNoAlpha); // non-zero for textures with all-white alpha

  Output.UV.z = noMulNoAlpha - noAlpha; // pass-through dontMulByAlpha flag
  Output.UV.w = data[id].yPlaneAxis.w;  // pass-through dontClearAlpha flag

  Output.Color0 = Input.Color * data[id].dmMultiply;
  if(noAlpha)
    Output.Color0.rgb *= saturate(Output.Color0.a);
	
  Output.Color1 = Input.Color * data[id].dmAdd;

#else // NewParticlesValue

  float2 disp = (UnpackCorner(cornersScale, Input.CornerMask) - constants.zw) * Input.RotationAndSize.xy * constants.yy;

  // rotate
  float sinz, cosz;
  sincos(Input.RotationAndSize.z, sinz, cosz);
  float2 rot = float2( disp.x * cosz - disp.y * sinz, disp.x * sinz + disp.y * cosz );

  // get final corner position
  float4 Position = float4(Input.Position, 1.0f);
#if (OrientTypePinValue == NONETYPE) || (OrientTypePinValue == PLANETYPE)
  Position.xyz += xPlaneAxis.xyz * rot.x + yPlaneAxis * rot.y;
#endif
  // Apply camera offset
  float3 offset = normalize(WEyePos.xyz - Position.xyz);
  Position.xyz += offset*constants.x;

#if (OrientTypePinValue == AXISTYPE) || (OrientTypePinValue == SPEEDTYPE)
  float3 tangentAxis = normalize(cross(offset, Input.Direction));
  Position.xyz += -tangentAxis * rot.x + Input.Direction * rot.y;
#endif

  PositionCS = mul( Position, ViewProjection );

  Output.UV = UnpackCorner(Input.UV, Input.CornerMask) * float2(1.0, -1.0); // invert V-axis
  Output.Color = Input.Color;
#if OpacityModePinValue == ADDITIVEOPACITY
	Output.Color.xyz *= xPlaneAxis.w;
#elif OpacityModePinValue == BLENDOPACITY
	Output.Color.w *= xPlaneAxis.w;
#endif
#endif // NewParticlesValue

#if DistortionPinValue == PRESENT
  Output.Z = PositionCS.w;
#endif
  return Output;
}

#if(NewParticlesValue == TRUE)
half4 MainPass_PSMain(VS_OUTPUT Input, float4 PixelPos : VPOS) : COLOR
{
  half4 color = saturate(Input.Color0 * tex2D(diffuseMapSampler, Input.UV) + Input.Color1);
  color.rgb *= saturate(color.a + Input.UV.z);
  color.a *= Input.UV.w;
  return color;
}

#else

half4 MainPass_PSMain(VS_OUTPUT Input, float4 PixelPos : VPOS) : COLOR
{
#if DistortionPinValue != PRESENT
  half4 color = (diffuseMultiplier * tex2D(diffuseMapSampler, Input.UV) + diffuseAdd) * Input.Color;
#else
  half4 color = tex2D(diffuseMapSampler, Input.UV);
  color.a *= Input.Color.a;
	ApplyOpacity(color);

  half fxScale = color.a / Input.Z;
  half3 backbuffer = SampleBackbuffer(PixelPos, ScaleDistortion(color.rg, fxScale));
  half3 backbufferMAD = backbuffer * diffuseMultiplier + diffuseAdd;
  #if VertexColorModePinValue != DIFFUSEMAPONLY
    backbufferMAD *= Input.Color.rgb;
  #endif
  color = half4(lerp(backbuffer, backbufferMAD, color.a), color.a);
#endif

  return color;
}

#endif
