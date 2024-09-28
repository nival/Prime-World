#include "stdafx.h"
#include "Bloom.h"

#include "smartrenderer.h"
#include "ImmediateRenderer.h"
#include "Filter.h"

static float g_bloom = 1.5f;
static float g_bloomSigma = 2.5f;
static bool s_bloomSimple = true;


static bool g_bloomEnable = true;
REGISTER_VAR("bloomEnable", g_bloomEnable, STORAGE_USER);
REGISTER_VAR_INTERFACE( "proxy_bloomEnable", NGlobal::MakeVarProxy(&g_bloomEnable), STORAGE_NONE );

namespace Render {

Bloom::Bloom() : curIdx(0), exposure(g_bloom), sigma(g_bloomSigma)
{
	if (g_bloom < 0.001f)
		return;

	const RenderMode& mode = GetRenderer()->GetCurrentRenderMode();

	static const int SCALE = 4; // This value must be the same as in ApplyAlpha4 shader
  unsigned width = mode.width/SCALE, height = mode.height/SCALE;
	pBuffer[0] = CreateRenderTexture2D(width, height, FORMAT_A8R8G8B8);
	pBuffer[1] = CreateRenderTexture2D(width, height, FORMAT_A8R8G8B8);
	InitKernels();
}

Bloom::~Bloom()
{
}

void Bloom::InitKernels()
{
	float dx = 1.0f / (float)pBuffer[0]->GetWidth();
	float dy = 1.0f / (float)pBuffer[0]->GetHeight();
	Filter::Gaussian1D gauss(sigma);
	Filter::FillKernel1D(gauss, kernelH, KERNEL_SIZE, dx, 0.0f, exposure);
	Filter::FillKernel1D(gauss, kernelV, KERNEL_SIZE, 0.0f, dy, exposure);
}

bool Bloom::Prepare(Texture2DRef const& pTexture)
{
	if (g_bloom < 0.001f || !pBuffer[0] || !pBuffer[1] || !g_bloomEnable)
		return false;

	if (exposure != g_bloom || sigma != g_bloomSigma)
	{
		sigma = g_bloomSigma;
		exposure = g_bloom;
		InitKernels();
	}

	RenderStatesManager& statesManager = *GetStatesManager();
  RenderState renderState;
	renderState.SetBlendMode(NDb::BLENDMODE_OFF);
	renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
	statesManager.SetState(renderState);

	// Make a smaller copy of back buffer & select bloom areas
	curIdx = 0;
	SmartRenderer::BindRenderTarget(pBuffer[curIdx]);
  Renderer& renderer = *GetRenderer();
  const float stepScale = s_bloomSimple ? 2.0f : 1.0f;
  const float texStepX = stepScale / pTexture->GetWidth();
  const float texStepY = stepScale / pTexture->GetHeight();
  CVec4 screenAndTextureStep(0.5f / pBuffer[0]->GetWidth() - 0.5f * texStepX,
                             0.5f / pBuffer[0]->GetHeight() - 0.5f * texStepY,
                             texStepX, texStepY);
  renderer.SetPixelShaderConstantsVector4(PSHADER_LOCALCONST1, screenAndTextureStep);
	GetImmRenderer()->RenderScreenQuad( s_bloomSimple ? ImmRenderer::Params("ApplyAlpha2", pTexture, &SamplerState::PRESET_CLAMP_POINT())
                                                    : ImmRenderer::Params("ApplyAlpha4", pTexture, &SamplerState::PRESET_CLAMP_POINT()) );

	// Horizontal Gaussian blur
	renderer.SetPixelShaderConstants(PSHADER_LOCALCONST1, ARRAY_SIZE(kernelH), kernelH);
	MakePass("Convolve7");

	// Vertical Gaussian blur
	renderer.SetPixelShaderConstants(PSHADER_LOCALCONST1, ARRAY_SIZE(kernelV), kernelV);
	MakePass("Convolve7");

  //SmartRenderer::BindRenderTarget(pTexture);

  return true;
}


Texture2D* Bloom::GetBlendSource()
{
  return g_bloomEnable ? pBuffer[curIdx].GetPtr() : 0;
}


void Bloom::MakePass(char const* pShaderName)
{
	SmartRenderer::BindRenderTarget(pBuffer[!curIdx]);
	GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params(pShaderName, pBuffer[curIdx]));
	curIdx = !curIdx;
}

} // namespace Render

REGISTER_VAR( "bloom", g_bloom, STORAGE_NONE );
REGISTER_VAR( "bloom_sigma", g_bloomSigma, STORAGE_NONE );
REGISTER_VAR( "bloomSimple", s_bloomSimple, STORAGE_NONE );

// end of Bloom.cpp
