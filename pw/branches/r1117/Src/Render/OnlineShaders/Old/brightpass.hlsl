struct VS_OUTPUT
{
		float4 Position				 : POSITION;	 // vertex position
		float2 Texcoord				 : TEXCOORD0;	// vertex diffuse texcoords
};			


float2 srcres : register(c0);
float2 threshold : register(c1);
//float emissiveThreshold : register(c3);
sampler DiffuseMap : register(s0);
sampler luminanceSampler : register(s1);
float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float4 average = 0;
	const float2 shifts[4] = { -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};
	[unroll(4)]for(int i = 0; i < 4; ++i)
	{
		float4 color = tex2D(DiffuseMap, Input.Texcoord + shifts[i]*srcres);
				float3 weight = float3( 0.299f, 0.587f, 0.114f );
		
		average += color;
	}
	average *= 0.25f;
	float3 weight = float3( 0.299f, 0.587f, 0.114f );	
	
	float luminance = dot(average.rgb, weight);
	
	float averageLuminance = tex2D(luminanceSampler, 0.5f.xx).r;
	float th = threshold.x * averageLuminance + threshold.y;
	if((luminance - th) < 0.f)
		return 0;
	return float4(average.rgb, 1.f); 
}