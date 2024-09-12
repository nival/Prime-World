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
		//Output.Position -= float4( 1/1024.f, 1/768.f, 0, 0);
		Output.Texcoord = Input.Texcoord;
		//Output.Vertexcolor = Input.Vertexcolor;
		return Output;
}

sampler DiffuseMap : register(s0);
float2 texelSize : register(c0);


float4 PS_main(VS_OUTPUT Input) : COLOR
{
  float4 res = float4( 0, 0, 0, 0 );

	#include "bloomGauss.hlsl" // for( i ) cycle is inside include
		res += weights[i] * tex2D( DiffuseMap, Input.Texcoord + float2( samples[i] * texelSize.x, 0 ) );

  return res;


}
