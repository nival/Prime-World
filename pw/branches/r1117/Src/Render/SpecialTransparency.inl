public:

void SetSpecialTransparency(bool on) { specialTransparency = on; }
bool GetSpecialTransparency() const { return specialTransparency; }

void PrepareRenderer_SpecialTransparency()
{
  Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
}

private:
