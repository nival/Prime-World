//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyCoefs( const float _coef3, const float _coef4 ) 
{ 
  coef3 = _coef3;
  coef4 = _coef4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyStripesColor( const Render::HDRColor &color1, const Render::HDRColor &color2 )
{
  colorStripe100 = color1;
  colorStripe1000 = color2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyStripesConstants( const float start, const float step1, const float step2, const float blendFactor1 )
{
  stripesStart = start;
  stripesStep1 = step1;
  stripesStep2 = step2;
  stripesBlendFactor1 = blendFactor1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ModifyColor( const HDRColor &mul, const HDRColor &add )
{
  color1 = mul;
  color2 = add;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateInternals()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnPrepareRender()
{
	Material::OnPrepareRender();

  GetRenderer()->SetVertexShaderConstantsColor( VSHADER_LOCALCONST0, color1 );
  GetRenderer()->SetVertexShaderConstantsColor( VSHADER_LOCALCONST1, color2 );

  GetRenderer()->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST0, color1 );
  GetRenderer()->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST1, color2 );

  CVec4 coefs( coef1, coef2, coef3, coef4 );
  CVec4 stripesCoefs( stripesStart, stripesStep1, stripesStep2, stripesBlendFactor1 );

  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST4, coefs );
  GetRenderer()->SetPixelShaderConstantsVector4( VSHADER_LOCALCONST4, coefs );

  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST8, stripesCoefs );
  GetRenderer()->SetPixelShaderConstantsVector4( VSHADER_LOCALCONST8, stripesCoefs );

  GetRenderer()->SetPixelShaderConstantsHDRColor( VSHADER_LOCALCONST9, colorStripe100 );
  GetRenderer()->SetPixelShaderConstantsHDRColor( VSHADER_LOCALCONST10, colorStripe1000 );
}


