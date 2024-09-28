void OnPrepareRender(const Batch &/*batch*/)
{
	NI_ASSERT( fabs( pivot.x ) <= 2.f && fabs( pivot.y ) <= 2.f, "Try to set too big pivot offset!" );

	if( pivot == VNULL2 )
		pivot.Set( 0.0f, 0.2f );

	// set leave rotation pivot, elasticity
	const CVec4 animationConstants( pivot, elasticity, 0.f );
	Render::GetRenderer()->SetVertexShaderConstantsVector4( 251, animationConstants );

	// set wind speed in [m/s] [1 ..]
	const CVec4 wind( 20.f, 0.f, 0.f, 0.f );
	Render::GetRenderer()->SetVertexShaderConstantsVector4( 252, wind );
}
