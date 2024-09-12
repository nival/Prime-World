
#define LinearSHfromVS ((LightingPinValue == LIGHTINGSH) && (NormalMapPinValue != PRESENT))

float4 shCoeffs[7] : register( PSHADER_SHCONSTS );

float3 DecodeSH( float3 normal, float4 coeffs[7] )
{
  float3 color;

	float4 vNormal = float4(normal, 1.0);
  
  // Linear + constant polynomial terms
  color.r = dot(coeffs[0],vNormal);
  color.g = dot(coeffs[1],vNormal);
  color.b = dot(coeffs[2],vNormal);
  
  // 4 of the quadratic polynomials
  float4 vB = vNormal.xyzz * vNormal.yzzx;   
  color.r += dot(coeffs[3],vB);
  color.g += dot(coeffs[4],vB);
  color.b += dot(coeffs[5],vB);
 
  // Final quadratic polynomial
  float vC = vNormal.x*vNormal.x - vNormal.y*vNormal.y;
  color.rgb += coeffs[6].rgb * vC;    

  return color;
}

#if LinearSHfromVS
float4   shCoeffsVS[3] : register(VSHADER_LOCALCONST1);

float3 DecodeLinearSH( float3 normal )
{
  float3 color;

  float4 vNormal = float4(normal, 1.0);
  
  // Linear + constant polynomial terms
  color.r = dot(shCoeffsVS[0],vNormal);
  color.g = dot(shCoeffsVS[1],vNormal);
  color.b = dot(shCoeffsVS[2],vNormal);

  return color;
}
#endif // LinearSHfromVS

#if NormalMapPinValue == PRESENT
half3 DecodeSHinPS( half3 normal )
{
  half3 color;
#else
half3 DecodeSHinPS( half3 normal, half3 color)
{
#endif

  half4 vNormal = half4(normal, 1.0);
#if NormalMapPinValue == PRESENT
  // Linear + constant polynomial terms
  color.r = dot(shCoeffs[0],vNormal);
  color.g = dot(shCoeffs[1],vNormal);
  color.b = dot(shCoeffs[2],vNormal);
#endif
  // 4 of the quadratic polynomials
  half4 vB = vNormal.xyzz * vNormal.yzzx;   
  color.r += dot(shCoeffs[3],vB);
  color.g += dot(shCoeffs[4],vB);
  color.b += dot(shCoeffs[5],vB);
 
  // Final quadratic polynomial
  half vC = vNormal.x*vNormal.x - vNormal.y*vNormal.y;
  color += shCoeffs[6].rgb * vC;    
  return color;
}


