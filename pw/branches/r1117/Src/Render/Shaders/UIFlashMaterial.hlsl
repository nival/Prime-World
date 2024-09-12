#include "_commonUI.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ShaderForLines == PRESENT
sampler borderMask : register( s2 );
#endif

#if UseDiffuse == PRESENT
sampler diffuseMapSampler : register( s0 );
#endif 

#if UseDiffuse2 == PRESENT
sampler diffuseMapSampler2 : register( s1 );
#endif 

sampler destMapSampler : register( s3 );

float4 screenScaleOffset    : register( SCREEN_TO_TEXTURE );

uniform float4 colorAdd  : register( PSHADER_LOCALCONST8 );
uniform float4x4 colorMatrix  : register( PSHADER_LOCALCONST9 );

uniform float4 textureMatrix1_1 : register( c30 );
uniform float4 textureMatrix1_2 : register( c31 );
uniform float4 textureMatrix2_1 : register( c32 );
uniform float4 textureMatrix2_2 : register( c33 );

uniform float4 scale9GridXConst : register( c34 );
uniform float4 scale9GridYConst : register( c35 );
uniform float4 trans9GridConst : register( c36 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VS_INPUT_FLASH
{
  float2 Position		 : POSITION0;
  float2 Shift  		 : TEXCOORD0;
  float4 VertexColor : COLOR0;	
  float2 Aliasing    : TEXCOORD1;	

#if ShaderForLines == PRESENT
  float2 Border      : TEXCOORD2;	
#endif

  float2 DiffuseUV   : TEXCOORD3;	
};

#define UseUV ( UseDiffuse == PRESENT ) || ( ( UseDiffuse2 == PRESENT ) && ( MorphShapes == PRESENT ) )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VS_OUTPUT_FLASH
{
  float4 Position		 : POSITION;   // vertex position
  float4 VertexColor : COLOR0;

  float2 Aliasing    : TEXCOORD1;	

#if ShaderForLines == PRESENT
  float2 Border      : TEXCOORD2;	
#endif

#if UseUV
  float2 DiffuseUV	 : TEXCOORD3;
#endif
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplyScale9Grid( float _coord, float4 consts )
{
  if ( consts.x < _coord && _coord < consts.y )
    return lerp( consts.x, _coord, consts.z );
  else if ( consts.y <= _coord )
    return _coord + consts.w;

  return _coord;    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float2 PrepareUV( float2 vertexPosition, float2 defaultUV )
{
#if MorphShapes == PRESENT
    float2x2 texMat1 = { textureMatrix1_1.x, textureMatrix1_1.y,
                        textureMatrix1_2.x, textureMatrix1_2.y };
    float2x2 texMat2 = { textureMatrix2_1.x, textureMatrix2_1.y,
                         textureMatrix2_2.x, textureMatrix2_2.y };

    float2x2 texMat = lerp( texMat1, texMat2, flashConstants.z );
    float2 texTrans = lerp( float2( textureMatrix1_1.z, textureMatrix1_2.z ), float2( textureMatrix2_1.z, textureMatrix2_2.z ), flashConstants.z );                        

  #if UseUV
    return ( mul( texMat, vertexPosition ) + texTrans );
  #endif
#else
  #if UseDiffuse == PRESENT
    #if Scale9GridBitmap == PRESENT    
      return defaultUV;
    #else
      float2x2 texMat = { textureMatrix1_1.x, textureMatrix1_1.y,
                          textureMatrix1_2.x, textureMatrix1_2.y };
                          
      return ( mul( texMat, vertexPosition ) + float2( textureMatrix1_1.z, textureMatrix1_2.z ) );
    #endif
  #endif
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUTPUT_FLASH MainPass_VSMain( VS_INPUT_FLASH Input )
{
	VS_OUTPUT_FLASH Output;

#if ShaderForLines == PRESENT
  Input.Shift.xy *= flashConstants.y;
	Output.Position = float4( Input.Position + Input.Shift.xy, 0.0, 1.0 );
#else
	Output.Position = float4( Input.Position, 0.0, 1.0 );
#endif 


#if ( UseUV ) && ( Scale9Grid != PRESENT )
  Output.DiffuseUV = PrepareUV( Output.Position.xy, Input.DiffuseUV );
#endif

  Output.Position = mul( modelMatrix, Output.Position );

#if Scale9Grid == PRESENT
  Output.Position.x = ApplyScale9Grid( Output.Position.x, scale9GridXConst );
  Output.Position.y = ApplyScale9Grid( Output.Position.y, scale9GridYConst );

  #if UseUV
    Output.DiffuseUV = PrepareUV( Output.Position.xy / trans9GridConst.xy, Input.DiffuseUV );
  #endif  
  
  Output.Position.xy += trans9GridConst.zw;
#endif

  Output.Position = mul( viewMatrix, Output.Position );

  Output.VertexColor = Input.VertexColor;
  Output.Aliasing = Input.Aliasing;

#if ShaderForLines == PRESENT
  Output.Border = Input.Border;

  float length = abs( Input.Aliasing.y * modelMatrix._11 * viewMatrix._11 / flashConstants.x );
  Output.Aliasing.y = length > 1 ? 1 / length : 0.8f; // TMP
#endif 

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
float4 MainPass_PSMain(VS_OUTPUT_FLASH Input, float4 PixelPos : VPOS ) : COLOR
{
#if DebugMode == PRESENT
  return( 0, 0, 0, 1 );
#else

  float4 destColor = tex2D(destMapSampler, PixelPos.xy * screenScaleOffset.xy + screenScaleOffset.zw );

  #if  FlashBlendMode == COPY_BACKGRUOND
    return destColor;
  #else

    #if UseDiffuse == PRESENT
      float4 color = tex2D( diffuseMapSampler, Input.DiffuseUV );
    #else
      float4 color = Input.VertexColor;
    #endif
    
    #if MorphShapes == PRESENT
      #if UseDiffuse2 == PRESENT
        float4 colorMorph = tex2D( diffuseMapSampler2, Input.DiffuseUV );
      #else
        float4 colorMorph = Input.VertexColor;
      #endif
      
      color = lerp( color, colorMorph, flashConstants.z );
    #endif


      color = color * color1 + color2;

    #if UseColorFilter == PRESENT
      color = mul( color, colorMatrix ) + colorAdd;
    #endif

    #if ShaderForLines == PRESENT
	    float border = tex2D( borderMask, Input.Border ).x * 2.0 - 1.0;
      color.a *= smoothstep(0.0, Input.Aliasing.y * 1.4, -border );
    #endif

    #if (FlashBlendMode == DARKEN) || (FlashBlendMode == MULTIPLY)
	    return float4( color.rgb + ( 1 - color.a ), color.a );
    #elif (FlashBlendMode == ADD)
	    return float4( color.rgb * color.a, color.a );
    #elif (FlashBlendMode == INVERT)
	    return float4( color.aaa, color.a );
    #elif (FlashBlendMode == _DIFFERENCE)
	    return float4( abs( color.rgb - destColor.rgb ), color.a );
    #elif (FlashBlendMode == OVERLAY)
	    return float4( Overlay( destColor.rgb, color.rgb ), color.a );
    #elif (FlashBlendMode == HARDLIGHT)
	    return float4( Overlay( color.rgb, destColor.rgb ), color.a );
    #elif (FlashBlendMode == SCREEN)
	    return float4(color.rgb * color.aaa, color.a);
    #else
	    return color;
    #endif

  #endif

#endif

}
