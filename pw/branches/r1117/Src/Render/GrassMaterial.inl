Render::GetRenderer()->SetVertexShaderConstantsVector4( 250, CVec4( bladeSize, 0.f, 0.f ) );

// set leave rotation pivot, elasticity
const CVec4 animationConstants( VNULL2, elasticity, 0.f );
Render::GetRenderer()->SetVertexShaderConstantsVector4( 251, animationConstants );

// set wind speed in [m/s] [1 ..]
const CVec4 wind( 20.f, 0.f, 0.f, 0.f );
Render::GetRenderer()->SetVertexShaderConstantsVector4( 252, wind );

