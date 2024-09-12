uniform float4x4 World : register( c4 );
uniform float4x4 ViewProjection : register( c12 );

struct VS_INPUT
{
  float3 Position         : POSITION;
};      


struct VS_OUTPUT
{
  float4 Position         : POSITION;   // vertex position
};


VS_OUTPUT VS_main(VS_INPUT Input)
{
    	VS_OUTPUT Output;
	Output.Position = mul( float4( Input.Position, 1.f ), World );
	Output.Position = mul( Output.Position, ViewProjection );
	return Output;
}

float4 PS_main() : COLOR
{
  return float4(1,1,0,1);
}