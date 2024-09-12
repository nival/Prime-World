#include "_common.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NO_REFRACTION

float4 uvScaleOffset : register(VSHADER_LOCALCONST2); // per object: tiling and scrolling
float4 uvScaleOffsetCaustics : register(VSHADER_LOCALCONST3); // per object: tiling and scrolling

#ifdef NO_REFRACTION
float4 mtxRefraction[4] : register(VSHADER_LOCALCONST6);
#endif

struct VS_INPUT
{
  float3 Position : POSITION;
};      

struct VS_OUTPUT
{
  float4 PositionCS : TEXCOORD0;
  float4 PositionWS : TEXCOORD1;
  float3 EyeDir     : TEXCOORD2;
  float4 Coords     : TEXCOORD3;
#ifdef NO_REFRACTION
  float4 ScreenUV   : TEXCOORD4;
#endif
};

VS_OUTPUT MainPass_VSMain(VS_INPUT In, out float4 PositionCS : POSITION)
{
  VS_OUTPUT Out;

  Out.PositionWS = mul( float4( In.Position, 1.0 ), World );
  Out.PositionCS = mul( Out.PositionWS, ViewProjection );
  Out.EyeDir = Out.PositionWS - WEyePos;
  Out.Coords.xy = Out.PositionWS.xy * uvScaleOffset.xy + uvScaleOffset.zw;
  Out.Coords.zw = Out.PositionWS.xy * uvScaleOffsetCaustics.xy + uvScaleOffsetCaustics.zw;

  PositionCS = Out.PositionCS;
#ifdef NO_REFRACTION
  Out.ScreenUV = float4( dot(Out.PositionWS, mtxRefraction[0]),
                         dot(Out.PositionWS, mtxRefraction[1]),
                         0,
                         dot(Out.PositionWS, mtxRefraction[3]) );
#else
  float4 uv;
#endif
  
  return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sampler reflectionMap : register(s0);
sampler refractionMap : register(s1);
sampler depthMap : register(s2);
sampler heightMap : register(s3);
sampler gradientMap : register(s4); // this sampler mast be in CLAMP mode
sampler causticsMap : register(s5);

float4 params0 : register(WATER_PARAMS0); // per level: unproj_x, unproj_y
float4 params1 : register(PSHADER_LOCALCONST0); // per object: caus_scale, fres_power, norm_scale, rippleHeightScale
float4 params2 : register(PSHADER_LOCALCONST1); // per object: height_scale, dist_scale, refr_coef, fres_height_scale
float4 mtxReflection[4] : register(WATER_REFLECTION_MTX);
#ifndef NO_REFRACTION
float4 mtxRefraction[4] : register(WATER_REFRACTION_MTX);
#endif
float4 viewInvZ : register(WATER_VIEWINV_Z);
float4 color0 : register(PSHADER_LOCALCONST3); // first color in reflected palette
float4 color1 : register(PSHADER_LOCALCONST4); // second color in reflected palette
float2 viewport : register(PSHADER_LOCALCONST5); // viewport scale


half4 GetFFT(float2 uv)
{
  half4 fft = tex2D(heightMap, uv);
  fft.xyz = ( fft * 2.0 - 1.0 ) /** params1.w*/;
  return fft;
}

half GetFresnel(half NdotE)
{
  return 1.0 / pow(1 + saturate(-NdotE), params1.y);
}

half3 GetReflection(float4 Pos, half3 R)
{
#if ShaderQualityValue == FAST
  return lerp(half3(color1.xyz), half3(color0.xyz), R.z);
#else
  Pos.xyz += R / max(0.1, R.z);
  // float4 uv = mul(Pos, mtxReflection);
  float4 uv = float4( dot(Pos, mtxReflection[0]), dot(Pos, mtxReflection[1]), 0, dot(Pos, mtxReflection[3]) );
  return tex2Dproj(reflectionMap, uv).rgb;
#endif
}

half3 GetRefraction(float4 Pos, half3 T, inout float4 uv)
{
#ifndef NO_REFRACTION
  Pos.xyz -= T / T.z;
  // uv = mul(Pos, mtxRefraction);
  uv = float4( dot(Pos, mtxRefraction[0]), dot(Pos, mtxRefraction[1]), 0, dot(Pos, mtxRefraction[3]) );
#endif  
  return tex2Dproj(refractionMap, uv).rgb;
}

half3 ApplyCaustics(half3 Cb, float2 uv, half scale)
{
#if CausticsTexturePinValue == PRESENT
  half3 caustics = tex2D(causticsMap, uv).rgb;
  scale *= params1.x;
  return Cb * (1 + caustics * scale);
#else                                 
  return Cb;
#endif
}

half3 Deep(float4 uv, half delta_h, half3 Cb, VS_OUTPUT In, out float depthScale)
{
  // Restore bottom position in View Space
  float  z0 = In.PositionCS.w; // water pixel distance in View Space
  float4 uv_corrected = uv;
  // uv_corrected.xy *= viewport;
  float  z  = tex2Dproj(depthMap, uv_corrected).r + delta_h * params1.w;
  float2 xy = params0.xy * In.PositionCS.xy * z / z0;

  // Restore bottom position in World Space
  float h0 = In.PositionWS.z; // water pixel height in World Space
  float h  = dot(float4(xy, z, 1), viewInvZ);

  // Calculate bottom's depth and distance
  float depth = h0 - h;
  float dH = params2.x * depth;
  float dL = params2.y * (z - z0);

  // Add caustics to bottom
  depthScale = saturate(params2.w * depth);
  Cb = ApplyCaustics(Cb, In.Coords.zw, depthScale);

  // Mix attenuated energies given as textures
  half3 lo = tex2D(gradientMap, float2(dH, 0.0)) * Cb;
  half3 hi = tex2D(gradientMap, float2(dH, 1.0));
  return lerp( hi, lo, saturate(exp(dL)) );
}

half4 MainPass_PSMain( VS_OUTPUT In ) : COLOR
{
  // Build normal
  half4 fft = GetFFT(In.Coords.xy);
  half3 N = normalize(float3(fft.xy, params1.z));

  // Calculate reflected color
  half3 E = normalize(In.EyeDir);
  half  NdotE = dot(N, E);
  half3 R = E - 2 * NdotE * N;
  half3 Cr = GetReflection(In.PositionWS, R);

  // Calculate transmitted color
#ifdef NO_REFRACTION
  float4 uv = In.ScreenUV;
#else
  float4 uv;
#endif
  float depthScale;
  half3 T = E;//refract(E, N, params2.z);
  half3 Cb = GetRefraction(In.PositionWS, T, /*out*/ uv);
  half3 Ct = Deep(uv, fft.z, Cb, In, /*out*/ depthScale);

  // Mix reflected and transmitted colors
  half alpha = GetFresnel(NdotE);
  alpha *= depthScale;

  return half4(lerp(Ct, Cr, alpha), 1);
}
