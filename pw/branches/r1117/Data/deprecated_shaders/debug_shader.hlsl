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

uniform float2 screenResolution	: register( c0 );		

VS_OUTPUT VS_main(VS_INPUT Input)
{
		VS_OUTPUT Output;
		float2 xy = Input.Position.xy;
		xy.x /= screenResolution.x;
		xy.y /= screenResolution.y;
		Output.Position = float4(xy.x * 2.f - 1.f, 1.f - xy.y * 2.f, 0.f, 1.f); 
		Output.Position -= float4( 1.f/screenResolution.x, 1.f/screenResolution.y, 0, 0 );
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
