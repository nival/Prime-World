#include "StdAfx.h"
#include "ImmediateRenderer.h"
#include "Stretcher.h"
#include "..\System\Math\ieeehalfprecision.h"

namespace Render
{

static const int NumTablePixels = 128;

float Lanczos2(float _arg)
{
  const float x = fabsf(_arg);
  if(x < 2.f) {
    const float pi_x = PI * x;
    if(x > 1.e-4f)
      return 2.f * (sinf(pi_x) / pi_x) * (sinf(.5f * pi_x) / pi_x);
    else
      return 1.f;
  }
  else
    return 0.f;
}


bool StretcherTwoPass::SetTableTex()
{
  if(!pTable)
    return false;

  if(!pTableTex) {
    D3DSURFACE_DESC desc = { D3DFMT_A16B16G16R16F, D3DRTYPE_SURFACE, 0,
                             D3DPOOL_MANAGED, D3DMULTISAMPLE_NONE, 0, NumTablePixels, 1 };

    pTableTex = Create<Texture2D>(desc);
    if( !pTableTex->GetDXTexture() ) {
      desc.Format = D3DFMT_A32B32G32R32F;
      pTableTex = Create<Texture2D>(desc);
    }
    if( !pTableTex->GetDXTexture() ) {
      pTableTex = 0;
      return false;
    }
    const LockedRect &lRect = pTableTex->LockRect(0, LOCK_DEFAULT);
    if(lRect.data) {
      CVec4 * const src = Get(pTable);
      if(D3DFMT_A16B16G16R16F == desc.Format)
        singles2halfp(lRect.data, src, 4 * NumTablePixels);
      else
        memcpy(lRect.data, src, sizeof(CVec4) * NumTablePixels);

      pTableTex->UnlockRect(0);
    }
  }

  GetStatesManager()->SetSampler(1, SamplerState::PRESET_CLAMP_BILINEAR(), pTableTex);

  return true;
}


StretcherTwoPass::StretcherTwoPass(Func func) : pTable(new CVec4[2 * NumTablePixels])
{
  if(pTable) {
    CVec4 * const pData = Get(pTable);
    for(int i = 0; i < NumTablePixels; ++i) {
      CVec4 &entry = pData[i];
      float x = float(i) / NumTablePixels;
      entry.Set( func(x - 2.f), func(x - 1.f), func(x), func(x + 1.f) );
      float sum = entry.x + entry.y + entry.z + entry.w;
      entry /= sum;
    }
  }
}


HRESULT StretcherTwoPass::Stretch(const Texture2DRef& _src, const CTRect<int> *_srcRect,
                                  const Texture2DRef& _dest, const Texture2DRef& _scratch)
{
  HRESULT hr = S_OK;
  if( SetTableTex() ) {
    ASSERT(_src);
    CTRect<int> srcRect( _srcRect ? *_srcRect
                                  : CTRect<int>(0, 0, _src->GetWidth(), _src->GetHeight()) );
    const float screen_shift_x = 1.f / _scratch->GetWidth();  // to compensate half-pixel shift 
    const float screen_shift_y = 1.f / _scratch->GetHeight(); // to compensate half-pixel shift

    GetStatesManager()->SetState( RenderState::NoBlendNoTest() );
    ImmRenderer& immRenderer = *GetImmRenderer();
    Renderer&    renderer    = *GetRenderer();
    { // first pass
      const float scaleV = 1.f / _src->GetHeight();
      ImmRenderer::Params params( "UpscaleH", _src );
      //ImmRenderer::Params params( "UpscaleH", _src, &SamplerState::PRESET_CLAMP_POINT() );
      params.uvRect = srcRect;
      params.uvRect.top *= scaleV;
      params.uvRect.bottom *= scaleV;

      SmartRenderer::BindRenderTarget(_scratch);
      const float invTexWidth = 1.f / _src->GetWidth();
      renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, CVec4(-invTexWidth, 0, invTexWidth, 2.f * invTexWidth) );
      immRenderer.RenderScreenQuad(CTRect<float>(-1.f + screen_shift_x,
                                                  1.f - 2.f * float(srcRect.Height()) / _scratch->GetHeight(),
                                                  1.f + screen_shift_x, 1.f),
                                   params);
    }
    // Second pass
    SmartRenderer::BindRenderTarget(_dest);
    ImmRenderer::Params params( "UpscaleV", _scratch );
    //ImmRenderer::Params params( "UpscaleV", _scratch, &SamplerState::PRESET_CLAMP_POINT() );
    params.uvRect.top    = srcRect.top;
    params.uvRect.bottom = srcRect.bottom;

    const float invTexHeight = 1.f / _scratch->GetHeight();
    renderer.SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, CVec4(0, -invTexHeight, invTexHeight,  2.f * invTexHeight) );
    immRenderer.RenderScreenQuad(CTRect<float>(-1.f, -1.f - screen_shift_y, 1.f,  1.f - screen_shift_y), params);
  }
  return hr;
}

}; // namespace PF_Render
