uniform float4x4 MatWorldView	 : register(c0);
uniform float4x4 MatProj			 : register(c4);
uniform float2 screenResolution	: register( c8 );

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
	float2 Center	: COLOR1;
	float2 CurrPos	: COLOR2;
	float Size : COLOR3;
};		

VS_OUTPUT VS_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	float2 xy = Input.Position.xy;
	
	Output.Center = Input.Position.xy;
	
	xy.x /= screenResolution.x;
	xy.y /= screenResolution.y;
	
	Output.Position = float4( xy.x * 2.f - 1.f, 1.f - xy.y * 2.f, 0.f, 1.f ); 
	Output.Position -= float4( 1.f/screenResolution.x, 1.f/screenResolution.y, 0, 0 );
	
	float2 disp = Input.UVCorners.xy;
	disp /= screenResolution.xy;
	
	Output.Position.xy += disp;
	Output.VertexColor = Input.VertexColor;
	
	Output.Size = pow(Input.UVCorners.x - 1, 2);
	Output.CurrPos = Output.Center + Input.UVCorners.xy;
	
	return Output;
}

float4 PS_main(VS_OUTPUT Input) : COLOR
{
	float2 dist = Input.Center - Input.CurrPos;
	if(dot(dist, dist) > Input.Size)
	{
		 discard;
	}
	
	return Input.VertexColor; 
}