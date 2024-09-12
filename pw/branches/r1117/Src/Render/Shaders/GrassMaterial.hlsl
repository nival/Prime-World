#include "_common.hlsl"
#include "_commonTemperature.hlsl"
#include "SwayComputation.hlsl"

// Switch off some PINs
#ifdef FORCE_SM20
  #undef ShadowReciverPinValue
  #define ShadowReciverPinValue 0
#endif

float4 lodParameters : register( VSHADER_LOCALCONST0 );
float4 bladeSize : register( VSHADER_LOCALCONST1 );

struct VS_OUT
{
  float4 vPosition        : POSITION;
  float3 normal           : TEXCOORD1;
  float4 UV               : TEXCOORD2;
  float  warfog           : TEXCOORD3;
  float  alpha            : TEXCOORD4;
  float4 shadowTexCoords  : TEXCOORD5;
};

VS_OUT MainPass_VSMain(
  float3  vPosition  : POSITION,
  float3  normal     : NORMAL,
  float2  vTexCoords : TEXCOORD0,
  float4  vParams    : TEXCOORD1 )
{
  VS_OUT sOutput;

  float4x4 billBoard = float4x4(
     0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, 0.0f, 0.0f, 1.0f
  );
    
  //float angle = atan2( eyeDirection.x, eyeDirection.y );
  //float2 sinCos;
  //sincos( angle, sinCos.x, sinCos.y );

  //float4x4 rotation = float4x4( 
  //  sinCos.y, sinCos.x, 0.f, 0.f,
  //  -sinCos.x, sinCos.y, 0.f, 0.f,
  //  0.f, 0.f, 1.f, 0.f,
  //  0.f, 0.f, 0.f, 1.f
  //  );
  //  
  //// rotate on camera 
  //offset = mul( rotation, offset ); 
  
  float4 offset = billBoard[vParams.x];
  
  offset.xyz *= bladeSize.xxy;
  offset.xyz *= vParams.zzz;
  
  // calculate sway angle for leave, move vertex around leave center
  const float3 noise = vPosition;
  const float vertexWeight = vParams.y;
  offset.xz = ComputeGrassSway( offset.xz, bladeSize.y * vertexWeight, noise.x * noise.y * noise.z );

  float4 worldPosition = float4( vPosition, 1.f );
  //worldPosition.xyz += offset.xyz;
  worldPosition = mul( worldPosition, World );

  sOutput.UV.zw = vTexCoords;
  sOutput.UV.xy = worldPosition.xy /************************* worldScale*/;
  sOutput.warfog = ReadWarFog( worldPosition.xy /************************* worldScale*/ );

  sOutput.shadowTexCoords = float4(0,0,0,0);/************************* mul( worldPosition, LightView );*/
  sOutput.shadowTexCoords.xy += offset.xz;
  sOutput.shadowTexCoords = float4(0,0,0,0);/************************* mul( sOutput.shadowTexCoords, LightProjection );*/

  // project to screen
  //sOutput.vPosition = mul( worldPosition, ViewProjection );

  worldPosition = mul( worldPosition, View );
  worldPosition.xy += offset.xz;
  sOutput.vPosition = mul( worldPosition, projection );
  sOutput.normal = normal;
  
  sOutput.alpha = 1.0f - saturate( ( sOutput.vPosition.z - lodParameters.x ) / lodParameters.y );

  return sOutput;   
}

half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  /*************************
  if( In.warfog < 0.1f )
    discard;

  float3 temperatureMask = tex2D( terrainTemperatureMaskSampler, In.UV.xy ).rgb;  
  float4 surfaceDiffuseColor = ComputeDiffuse( In.UV.zw, temperatureMask, 1 );
  float3 surfaceNormal = normalize( In.normal );

#if ShadowReciverPinValue == 1

  const float shadow = ComputeShadow( In.shadowTexCoords );
  SunAmbientColor *= texCUBElod( envMapSampler, float4( surfaceNormal, 5.0f ) );
  SunDiffuseColor = lerp( 0, SunDiffuseColor, shadow );
  
#endif

  WSunDir =  normalize( -WSunDir );
  float lightIntensity = saturate( dot( surfaceNormal, WSunDir ) );
  float3 diffuse = surfaceDiffuseColor.rgb * ( SunAmbientColor + SunDiffuseColor * lightIntensity );
  
  return float4( diffuse.rgb * In.warfog, surfaceDiffuseColor.a * In.alpha );
  */
  return half4(1,1,1,1);
}
