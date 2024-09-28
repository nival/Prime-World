#include "_commonUI.hlsl"
#include "_convertersUI.hlsl"

#if UseDiffuse == PRESENT
sampler diffuseMapSampler : register( s0 );
#endif 

#if Masking != 0
sampler maskingMapSampler : register( s1 );
#endif 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUTPUT MainPass_VSMain( VS_INPUT Input )
{
	VS_OUTPUT Output;
	Output.Position = CommonTransform( Input.Position );
	Output.Texcoord3 = Input.Position;
	Output.Texcoord = Input.Texcoord;
	Output.Texcoord2 = Input.Texcoord2;

#if Gradient == PRESENT
	float4 gradient = color2 * (-coefs.z) + color1 * (1.f + coefs.z);
	gradient.a = 1.f;

  Output.Vertexcolor = Input.Vertexcolor * gradient;
#else
  Output.Vertexcolor = Input.Vertexcolor * color1;
#endif
  
  return Output;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if Colorized == PRESENT
  float4 MainPass_PSMain( VS_OUTPUT Input ) : COLOR
  {
	  float4 grad_color = (color2 * (-coefs.z) + color1 * (1.f +coefs.z)) * 20.f;
  #if Masking == 1 || Masking == 2
	  float4 mask = tex2D( maskingMapSampler, Input.Texcoord );
  #else
	  float4 mask = float4(1,1,1,1);
  #endif

  #if Masking != 0
    #if Masking == 2
      float maskFactor = ( coefs.w - clamp( mask.a + coefs.z, 0.0, coefs.w ) ) / coefs.w;
    #elif Masking == 1
      float maskFactor = clamp( mask.a + coefs.z, 0.0, coefs.w ) / coefs.w;
    #endif

    grad_color.a = grad_color.a * clamp( maskFactor, 0.0, 1.0 );
  #endif // Masking != 0
  	
  #if UseDiffuse == PRESENT
	  float4 diffuse_color = tex2D( diffuseMapSampler, Input.Texcoord );
  #else
	  float4 diffuse_color = float4(1,1,1,1);
  #endif

    float3 hsv_diff_color = RGB2HSV(float3(diffuse_color.x,diffuse_color.y,diffuse_color.z));
	  float3 hsv_grad_color = RGB2HSV(float3(grad_color.x,grad_color.y,grad_color.z));
	  hsv_grad_color.z = hsv_diff_color.z;

	  return float4(HSV2RGB(hsv_grad_color),grad_color.a); 
  }

#else
  float4 MainPass_PSMain( VS_OUTPUT Input ) : COLOR
  {
    float4 color = Input.Vertexcolor;

  #if Masking != 0
    float4 mask = tex2D( maskingMapSampler, Input.Texcoord );

    #if Masking == 2
      float maskFactor = ( coefs.w - clamp( mask.a + coefs.z, 0.0, coefs.w ) ) / coefs.w;
    #elif Masking == 1
      float maskFactor = clamp( mask.a + coefs.z, 0.0, coefs.w ) / coefs.w;
    #endif

    color.a	= color.a * clamp( maskFactor, 0.0, 1.0 );
  #endif

  #if UseDiffuse == PRESENT
    color *= tex2D( diffuseMapSampler, Input.Texcoord );
  #endif

  #if Gradient == PRESENT
    float4 gradient = (color2 * (-coefs.z) + color1 * (1.f + coefs.z)) * 5.f;
    gradient.a = 1.f;

    color = color * gradient;
  #endif
  
  #if Stripes == PRESENT
    const float screen_x = Input.Texcoord3.x * resolutionCoef.z - stripesCoefs.x;

    volatile float line_factor;

    {
      line_factor = screen_x % stripesCoefs.y;
      line_factor = line_factor > 1.f ? 1.f : stripesCoefs.w;

      color = lerp(stripeCol100, color, line_factor);
    }

    {
      line_factor = screen_x % stripesCoefs.z;
      line_factor = line_factor > 2.f ? 1.f : 0.f;

      color = lerp(stripeCol1000, color, line_factor);
    }
  #endif
    
    return color;
  }
#endif
