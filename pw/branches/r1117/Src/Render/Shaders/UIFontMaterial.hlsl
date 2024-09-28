#include "_commonUI.hlsl"

sampler fontCacheSampler : register( s0 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUTPUT MainPass_VSMain( VS_INPUT Input )
{
	VS_OUTPUT Output;
	Output.Position = CommonTransform( Input.Position );
	Output.Texcoord = Input.Texcoord;
	Output.Texcoord2 = Input.Texcoord2;
	Output.Vertexcolor = Input.Vertexcolor;
	return Output;
}

#define OutlineMode 2

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
half4 MainPass_PSMain( VS_OUTPUT Input ) : COLOR
{
	half4 s0 = half4( 1.f, 1.f, 1.f, tex2D( fontCacheSampler, Input.Texcoord ).x );

#if DrawContour == PRESENT
#if OutlineMode == 0
  float uStep = fontTexScale.x;
  float vStep = fontTexScale.y;

  half a1 = 0;
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(-uStep,0) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(uStep,0) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(0,-vStep) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(0, vStep) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(-uStep,-vStep) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2( uStep,-vStep) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2(-uStep, vStep) ).x );
  a1 = max( a1, tex2D( fontCacheSampler, Input.Texcoord + float2( uStep, vStep) ).x );

  half4 result = color2;
  result.a *= a1;

  result.rgb = result.rgb * (1 - s0.a) + s0.rgb * Input.Vertexcolor.rgb * s0.a;
  result.a = ( 1 - (1 - result.a) * (1 - s0.a) ) * Input.Vertexcolor.a;

  return result;
  
#else

  half  a = tex2D(fontCacheSampler, Input.Texcoord).x;
  half3 result = lerp(color2.rgb, Input.Vertexcolor.rgb, a);
  
  float4 coords = Input.Texcoord.xyxy + 0.5 * float4(fontTexScale.xy, - fontTexScale.xy);
  half4 a1;
  a1.x = tex2D(fontCacheSampler, coords.xy).x;
  a1.y = tex2D(fontCacheSampler, coords.xw).x;
  a1.z = tex2D(fontCacheSampler, coords.zy).x;
  a1.w = tex2D(fontCacheSampler, coords.zw).x;
  
#if OutlineMode == 1
  a = sqrt(dot(a1 * a1, 4));
#elif OutlineMode == 2
  a = dot(a1, 2);
#endif
  
  return half4( result, Input.Vertexcolor.a * saturate(a) );
  
#endif

#else

	return s0 * Input.Vertexcolor;

#endif
}
