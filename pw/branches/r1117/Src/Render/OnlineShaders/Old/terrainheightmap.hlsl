struct VS_INPUT
{
		float2 Position				 : POSITION;
		float2 Texcoord				 : TEXCOORD0;
};			

struct VS_OUTPUT
{
		float4 Position				 : POSITION;	 // vertex position
		float2 Texcoord				 : TEXCOORD0;	// vertex diffuse texcoords
};


VS_OUTPUT VS_main(VS_INPUT Input)
{
		VS_OUTPUT Output;
		Output.Position = float4(Input.Position.x,Input.Position.y, 0.f, 1.f); 
		Output.Position -= float4( 1.f/1024.f, 1.f/768.f, 0, 0);
		Output.Texcoord = Input.Texcoord;
		return Output;
}

sampler DiffuseMap : register(s0);
uniform float scale : register(c0);
sampler gradientMap : register(s1);

float4 PS_main(VS_OUTPUT Input) : COLOR
{
#ifndef FORCE_SM20
	float height = tex2Dlod(DiffuseMap, float4(Input.Texcoord,0,0)).g;
	float clampedHeight = clamp(height/scale, -1, 1)*0.5+0.5;
	float4 color = tex1Dlod( gradientMap, float4(clampedHeight, 0,0,0) );
#else
	float height = tex2D(DiffuseMap, Input.Texcoord).g;
	float clampedHeight = clamp(height/scale, -1, 1)*0.5+0.5;
	float4 color = tex1D( gradientMap, clampedHeight );
#endif	
	return color;
}
