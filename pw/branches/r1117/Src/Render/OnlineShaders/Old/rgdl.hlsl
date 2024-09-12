struct VS_OUTPUT
{
		float4 Position				 : POSITION;	 // vertex position
		float2 Texcoord				 : TEXCOORD0;	// vertex diffuse texcoords
};			


float2 srcres : register(c0);
sampler DiffuseMap : register(s0);
float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float average = 0;
	float maximum = 0; 
	const float2 shifts[4] = { -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};
	[unroll(4)]for(int i = 0; i < 4; ++i)
	{
		float2 color = tex2D(DiffuseMap, Input.Texcoord + shifts[i]*srcres).rg;
		
		maximum = max(maximum,  color.g);
		average += color.r;
	}
	average *= 0.25f;	
	return float4(average, maximum, 0.f, 0.f); 
}