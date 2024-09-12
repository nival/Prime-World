float4 animationConstants : register( c251 );
float3 wind : register( c252 );

float CalculateWindAffection( float sizeElasticity, float random )
{
	// calculate sway angle, move vertice around leave center
	const float noiseLimit = radians( 120.f );
	const float noise = fmod( random, noiseLimit );
	
	const float windIntensity = 0.42f * animationConstants.z * sizeElasticity;
	const float windAmplitude = length( wind ) * animationConstants.z;
	return radians( sin( (totalTime + noise) * windIntensity  ) * windAmplitude );
}

float2 ComputeSway( float2 vertex, float sizeElasticity, float random )
{
	const float angle = CalculateWindAffection( sizeElasticity, random );
	
	const float pivotOffset = 0.8f + fmod( random, 0.2f );
	const float2 pivot = animationConstants.xy * pivotOffset.xx;
		
	float2 sway;
	sincos( angle, sway.y, sway.x );
	float2 offset = vertex + pivot;
	
	// apply sway to offset
	return float2( sway.x * offset.x - sway.y * offset.y, sway.y * offset.x + sway.x * offset.y ) - pivot;
}

float2 ComputeGrassSway( float2 vertex, float sizeElasticity, float random )
{
	const float angle = CalculateWindAffection( sizeElasticity, random );	

	float2 sway;
	sincos( angle, sway.y, sway.x );
	
	// apply sway to offset
	return float2( sway.x * vertex.x - sway.y * vertex.y, sway.y * vertex.x + sway.x * vertex.y );
}