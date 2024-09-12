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

float2 resolution : register(c0);
VS_OUTPUT VS_main(VS_INPUT Input)
{
		VS_OUTPUT Output;
		Output.Position = float4(Input.Position.x,Input.Position.y, 0.f, 1.f); 
		float2 texelSize = float2( -1.f/ resolution.x, 1.f/ resolution.y );
		Output.Position.xy += texelSize;
		Output.Texcoord = Input.Texcoord;
		return Output;
}