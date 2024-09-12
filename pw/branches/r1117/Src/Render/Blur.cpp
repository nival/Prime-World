#include "stdafx.h"
#include "Blur.h"

#include "smartrenderer.h"
#include "ImmediateRenderer.h"
#include "Filter.h"

namespace Render
{

Blur9::Blur9(unsigned texWidth, unsigned texHeight)
{
  Init(texWidth, texHeight);
}

void Blur9::Init(unsigned texWidth, unsigned texHeight)
{
  // prepare filtration kernel
  float kernel[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
  NI_STATIC_ASSERT(ARRAY_SIZE(kernel) == FILTER_SIDE * FILTER_SIDE, KERNEL_SIZE_MISMATCH);
  Render::Filter::ArrayFunc2D f(kernel, FILTER_SIDE, FILTER_SIDE);
  float dx = 1.0f / (float)texWidth;
  float dy = 1.0f / (float)texHeight;
  Render::Filter::FillKernel2D(f, filterKernel, FILTER_SIDE, dx, dy, 1.0f);
}

void Blur9::Apply(Render::Texture2DRef const& pSrc, Render::Texture2DRef const& pDst, char const* pShaderName/* = 0*/)
{
  using namespace Render;
  // set default image processing states // smirnov [2009/3/3]: refactor
  RenderStatesManager &rsManager = *GetStatesManager();
  rsManager.SetState( RenderState::NoBlendNoTest() );
  rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
  rsManager.SetStateDirect(D3DRS_ZWRITEENABLE, 0);
  rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, 0);

  // set shader parameters
 GetRenderer()->SetPixelShaderConstants(PSHADER_LOCALCONST1, ARRAY_SIZE(filterKernel), filterKernel);

  // execute shader
 SmartRenderer::BindRenderTarget(pDst);
 GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params(pShaderName ? pShaderName : "Convolve9", pSrc));
 SmartRenderer::BindRenderTargetDefault();
}

} // namespace Render
