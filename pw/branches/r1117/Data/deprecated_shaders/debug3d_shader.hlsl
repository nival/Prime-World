struct VS_OUTPUT
{
		float4 Position				 : POSITION;	 // vertex position
		float Texcoord				 : TEXCOORD0;	// vertex diffuse texcoords
		float4 Vertexcolor			: COLOR0;
};

struct VS_INPUT
{
		float3 Position				 : POSITION;
		float Texcoord				 : TEXCOORD0;
		int4 Vertexcolor			: COLOR0;	
};

uniform float4x4 MatWorldView	 : register(c0);
uniform float4x4 MatProj			 : register(c4);	

VS_OUTPUT VS_main(VS_INPUT Input)
{
		VS_OUTPUT Output;
		Output.Position = mul( float4( Input.Position, 1.f ), MatWorldView);
		Output.Position = mul( Output.Position, MatProj);
		Output.Texcoord = Input.Texcoord;
		Output.Vertexcolor = Input.Vertexcolor;
		return Output;
}

sampler maskSampler : register( s0 );

float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float4 color = Input.Vertexcolor;
	return color; 
}
