struct PS_INPUT
{
	float2 Texcoord : TEXCOORD0;
};

samplerCUBE envMapSampler : register( s12 );

float3x3 reconstructionMatrix : register( c0 );

float4 PS_main(PS_INPUT In) : COLOR
{
	float3 vec = mul( float3( In.Texcoord * 2 - 1, 1 ), reconstructionMatrix );
	return texCUBE( envMapSampler, vec );
}
