uniform float4x4 MatWorldView	 : register(c0);
uniform float4x4 MatProj			 : register(c4);

struct VS_INPUT
{
	float3 Position			: POSITION;
	float2 UVCorners		: TEXCOORD0;
	float4 VertexColor	: COLOR0;
};	

struct VS_OUTPUT
{
	float4 Position			: POSITION;	 
	float4 VertexColor	: COLOR0;
};		

VS_OUTPUT VS_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	float4 Position = mul( float4(Input.Position, 1.f), MatWorldView );
	float2 disp = Input.UVCorners.xy;
	Position.xy += disp;
	Output.Position = mul( Position, MatProj );
	Output.VertexColor = Input.VertexColor;
	return Output;
}

float4 PS_main(VS_OUTPUT Input) : COLOR
{
	return Input.VertexColor; 
}