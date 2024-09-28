#include "_common.hlsl"
#include "_commonTemperature.hlsl"

struct VS_IN
{
  float3 Position : POSITION;
  float3 Normal   : NORMAL;
  float2 UV       : TEXCOORD0;
};

struct VS_OUT
{
  float3 Normal : TEXCOORD0; //0,1,2
  float2 UV     : TEXCOORD1;
  float3 WPos   : TEXCOORD2;
  float3 WView  : TEXCOORD3;
};

VS_OUT MainPass_VSMain( VS_IN In, out float4 ClipSpacePosition: POSITION )
{
  VS_OUT Out;

  ClipSpacePosition = mul( float4( In.Position, 1.f ), World );
  ClipSpacePosition = mul( ClipSpacePosition, ViewProjection );


  Out.WPos = mul ( float4( In.Position, 1.f ), World );
  Out.Normal = mul( float4( In.Normal, 0.f ), World );
  Out.WView = normalize( Out.WPos - WEyePos );
  
  float2 uvscale = 0.1f.xx;
  
#if TerrainUVSetPinValue == 0
  Out.UV = Out.WPos.xy*uvscale;
#else
  Out.UV = In.UV;
#endif
  return Out;
}


half4 MainPass_PSMain( VS_OUT In ) : COLOR
{
  half4 surfaceDiffuseColor = diffuseNormalMultiplier * tex2D( diffuseNormalSampler, In.UV ) + diffuseNormalAdd;
  
  half lightIntensity = saturate( dot( In.Normal, WSunDir ) );
  half3 diffuse = surfaceDiffuseColor.rgb * ( SunAmbientColor + SunDiffuseColor * lightIntensity );

	return half4( diffuse,  1.f );
}
