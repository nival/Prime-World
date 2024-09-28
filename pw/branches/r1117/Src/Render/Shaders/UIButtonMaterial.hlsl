#include "_commonUI.hlsl"

sampler background : register(s0);
sampler icon       : register(s1);
sampler waitForAct : register(s2);
sampler lackMana   : register(s3);
sampler pressed    : register(s4);
sampler highlight  : register(s5);
sampler screen     : register(s6);

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

static const float3 luminanceConv = {0.2125f, 0.7154f, 0.0721f};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4 MainPass_PSMain( VS_OUTPUT Input ) : COLOR
{
#if UseDiffusePin
  float4 diffuseA = tex2D( icon, Input.Texcoord );
#else
  float4 diffuseA = float4( 0, 0, 0, 0 );
#endif

#if DisablePin == PRESENT
  diffuseA.rgb = dot( diffuseA, luminanceConv ).xxx;
#endif

#if PassivePin == PRESENT
  float3 diffuse = diffuseA.rgb;
  float finalAlpha = diffuseA.a;
#else
  float4 diffuseB = tex2D( background, Input.Texcoord );
  float3 diffuse = lerp( diffuseB.rgb, diffuseA.rgb, diffuseA.a );
  float finalAlpha = max( diffuseA.a, diffuseB.a ) ;
#endif

#if LackOfManaPin == PRESENT
  float4 effectColor   = tex2D( screen, Input.Texcoord );
  float4 lackManaColor = tex2D( lackMana, Input.Texcoord );

  effectColor.rgb = lerp( float3(1, 1, 1), effectColor.rgb, effectColor.a );
  effectColor.rgb = lerp( effectColor.rgb, diffuse.rgb, diffuseA.a );
  effectColor.rgb = lackManaColor.rgb * dot( effectColor.rgb, luminanceConv ).xxx * 2.0;

  diffuse.rgb = lerp(  diffuse.rgb, effectColor.rgb, lackManaColor.a );
#endif

#if HighlightPin == PRESENT
  float4 highlightColor = tex2D( highlight, Input.Texcoord );
  diffuse.rgb = lerp(  diffuse.rgb * finalAlpha, highlightColor.rgb, highlightColor.a );
  finalAlpha = max( finalAlpha, highlightColor.a ) ;
//  diffuse.rgb = lerp(  diffuse.rgb, Overlay( diffuse.rgb, highlightColor.rgb ), highlightColor.a );
#endif

#if WaitForActivationPin == PRESENT
  float4 waitColor = tex2D( waitForAct, Input.Texcoord );
  diffuse.rgb = lerp(  diffuse.rgb, waitColor.rgb, waitColor.a );
//  diffuse.rgb = lerp(  diffuse.rgb, saturate( diffuse.rgb + waitColor.rgb ), waitColor.a );
#endif

#if PressedPin == PRESENT
  float4 pressedColor = tex2D( pressed, Input.Texcoord );
  diffuse.rgb = lerp(  diffuse.rgb, pressedColor.rgb, pressedColor.a );
#endif

#if PassivePin == PRESENT
  return float4( diffuse, finalAlpha ) * Input.Vertexcolor;
#else

  // screen layer
//   float4 screenColor   = tex2D( screen, Input.Texcoord );
//   diffuse.rgb = lerp( diffuse,  Screen( diffuse, screenColor ),  screenColor.a * coefs.x );  

  return float4( diffuse, finalAlpha ) * Input.Vertexcolor;
#endif
}
