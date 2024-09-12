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


float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float diffuse = tex2D(DiffuseMap, Input.Texcoord).r;
	//if(diffuse > 0.f)
		//return float4(diffuse/1024.f, 0, 0, 1.f);
	return float4(diffuse, 0.f, 0.f, 1.f);
	
}
