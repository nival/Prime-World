#include "_commonUI.hlsl"

sampler background : register(s0);
sampler original   : register(s1);
sampler overlay    : register(s2);
sampler screen     : register(s3);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUTPUT MainPass_VSMain( VS_INPUT Input )
{
	VS_OUTPUT Output;
	Output.Position = CommonTransform( Input.Position );
	Output.Texcoord = Input.Texcoord;
	Output.Texcoord2 = Input.Texcoord2;

  Output.Vertexcolor = Input.Vertexcolor * color1;
  
  return Output;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float3 Overlay( float3 c1, float3 c2 )
{
   float3 white = float3( 1.0, 1.0, 1.0 ), grey = float3( 0.5, 0.5, 0.5 );

   float3 r1 = saturate( 2.0 * c1 * c2 );
   float3 r2 = saturate( white - 2.0 * ( white - c1 ) * ( white - c2 ) );
   
   return lerp( r1, r2, step( grey, c1 ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float3 Screen( float3 c1, float3 c2 )
{
  float3 white = float3( 1.0, 1.0, 1.0 );
  
  return white - ( white - c1 ) * ( white - c2 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4 MainPass_PSMain( VS_OUTPUT Input ) : COLOR
{
  float4 diffuseA     = tex2D( original, Input.Texcoord );
  float4 diffuseB     = tex2D( background, Input.Texcoord );
  float3 diffuse      = lerp( diffuseB.rgb, diffuseA.rgb, diffuseA.a );

  float4 screenColor = tex2D(screen, Input.Texcoord);
  float4 overlayColor = tex2D(overlay, Input.Texcoord);

  float3 resColor = lerp( diffuse,  Screen( diffuse, screenColor ),  screenColor.a * coefs.y );  
  resColor = lerp( resColor, Overlay( diffuse.rgb, overlayColor.rgb ), overlayColor.a * coefs.x );  

  return float4( resColor, /*diffuseA.a*/1.0 ) * Input.Vertexcolor;
}
