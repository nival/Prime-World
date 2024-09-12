struct VS_OUTPUT
{
		float4 Position				 : POSITION;	 // vertex position
		float2 Texcoord				 : TEXCOORD0;	// vertex diffuse texcoords
};

sampler HDRSampler : register(s0);
sampler LuminanceSampler : register(s1);
sampler BloomSampler : register(s2);

uniform float2 TexelSize : register( c0 );	
float gaussMultiplier : register( c2 );
float exposure : register( c1 );

float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float4 hdr = tex2D( HDRSampler, Input.Texcoord );
	
	float3 weight = float3( 0.299f, 0.587f, 0.114f );
	
	float2 luminance = tex2D( LuminanceSampler, 0.5f.xx).rg;
	float4 bloom = tex2D( BloomSampler, Input.Texcoord );
	
	
	float4 final = hdr;
	//float Lp = exposure * max(hdr.r, max(hdr.g, hdr.b)) / luminance.r;
	float Lp = exposure * max(hdr.r, max(hdr.g, hdr.b)) / 0.5f;
	float Lm = 4.f;//luminance.g+gaussMultiplier*luminance.g;
	Lm *= Lm;
  float toneScalar = ( Lp * ( 1.0f +  Lp /  Lm   ) ) / ( 1.0f + Lp );
  float4 res = final * toneScalar + bloom;
  res.a = 1.0f;
	return res;
}