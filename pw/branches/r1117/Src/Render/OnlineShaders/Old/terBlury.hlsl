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
		//Output.Position -= float4( 4/1024.f, 4/768.f, 0, 0);
		Output.Texcoord = Input.Texcoord;
		//Output.Vertexcolor = Input.Vertexcolor;
		return Output;
}

sampler DiffuseMap : register(s0);


float4 PS_main(VS_OUTPUT Input) : COLOR
{
	//float4 diffuse = tex2D(DiffuseMap, float2(Input.Texcoord.x+1/256.f,Input.Texcoord.y +1/192.f));
	float3 TexelSize = float3(1/256.f, 1/256.f, 0.5f);
	const float samples[8] = {
		-3.5,
		-2.5,
		-1.5,
		-0.5,
		 0.5,
		 1.5,
		 2.5,
		 3.5 };

	const float weights[8] = {
		0.010784,
		0.069608,
		0.180392,
		0.239216,
		0.239216,
		0.180392,
		0.069608,
		0.010784 };
    
  float4 res = float4( 0, 0, 0, 0 );

  float2 texccord = Input.Texcoord + TexelSize * 0.5;

	for( int i = 0; i < 8; i++ ) 
		res += weights[i] * tex2D( DiffuseMap, texccord + float2( 0, samples[i]  * TexelSize.y * TexelSize.z )  );



  return res;


}
