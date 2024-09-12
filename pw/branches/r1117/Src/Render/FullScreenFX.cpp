#include "stdafx.h"
#include "FullScreenFX.h"

#include "smartrenderer.h"
#include "ImmediateRenderer.h"
#include "Filter.h"
#include "MaterialSpec.h"
#include "Render/atir2vb.h"

namespace Render {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class FullScreenMaterialHolder

class FullScreenMaterialHolder
{
  union Flags {
    struct Pins {
      NDb::ColorCorrectPin colorCorrectPin : 3; // reserve space for sign bit
      NDb::BooleanPin      sharpPin : 2;        // reserve space for sign bit
      NDb::BooleanPin      bloomPin : 2;        // reserve space for sign bit
      NDb::BooleanPin     warFogPin : 2;        // reserve space for sign bit
      NDb::BooleanPin       useR2VB : 2;        // reserve space for sign bit
    } pins;
    DWORD bitmask;

    typedef NDb::BooleanPin BoolPin;

    Flags(DWORD _bitmask) : bitmask(_bitmask) {}
    Flags(NDb::ColorCorrectPin _colorCorrectPin, BoolPin _sharpPin, BoolPin _bloomPin, BoolPin _warFogPin, BoolPin _useR2VB)
    {
      SetPins(_colorCorrectPin, _sharpPin, _bloomPin, _warFogPin, _useR2VB);
    }
    Flags& SetPins(NDb::ColorCorrectPin _colorCorrectPin, BoolPin _sharpPin, BoolPin _bloomPin, BoolPin _warFogPin, BoolPin _useR2VB)
    {
      pins.colorCorrectPin = _colorCorrectPin;
      pins.sharpPin = _sharpPin;
      pins.bloomPin = _bloomPin;
      pins.warFogPin = _warFogPin;
      pins.useR2VB = _useR2VB;
      return *this;
    }
  };

  Flags newFlags, oldFlags;
  static const Flags mask;
  ManagedResource<MaterialInit<FullScreenMaterial> >  material;

  bool wasTexturesCnanged;

public:
  FullScreenMaterialHolder() : newFlags(0), oldFlags(0) {} // I assume here, that NDb::FullScreenMaterial() initializes all pins to 0

  void SetPins(NDb::ColorCorrectPin _colorCorrectPinVal, bool _doSharp, bool _doBloom, bool _doWarFog, bool _useR2VB)
  {
    newFlags.SetPins(_colorCorrectPinVal,
                     _doSharp  ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE,
                     _doBloom  ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE,
                     _doWarFog ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE,
                     _useR2VB  ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE);
  }

  FullScreenMaterial* GetMaterial()
  {
    FullScreenMaterial* const pMat = material.Get();
    if(pMat) {
      if((newFlags.bitmask ^ oldFlags.bitmask) & mask.bitmask)
      { // some flag was changed
        Flags::Pins oldPins = oldFlags.pins, newPins = newFlags.pins;

        if(oldPins.colorCorrectPin != newPins.colorCorrectPin)
          pMat->SetColorCorrectPin(newPins.colorCorrectPin);

        if(oldPins.sharpPin != newPins.sharpPin)
          pMat->SetSharpPin(newPins.sharpPin);

        if(oldPins.bloomPin != newPins.bloomPin)
          pMat->SetBloomPin(newPins.bloomPin);

        if(oldPins.warFogPin != newPins.warFogPin)
          pMat->SetWarFogPin(newPins.warFogPin);

        if(oldPins.useR2VB != newPins.useR2VB)
          pMat->SetR2VBPin(newPins.useR2VB);

        oldFlags = newFlags;
      }
    }
    return pMat;
  }
};

// TODO - make this initialization error-proof(less dependent on enums definitions)
const FullScreenMaterialHolder::Flags FullScreenMaterialHolder::mask =
  FullScreenMaterialHolder::Flags(0).SetPins(NDb::COLORCORRECTPIN_DESATURATE_ONLY, NDb::BOOLEANPIN_PRESENT,
                                             NDb::BOOLEANPIN_PRESENT, NDb::BOOLEANPIN_PRESENT, NDb::BOOLEANPIN_PRESENT);

FullScreenMaterialHolder s_MaterialHolder;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class FullScreenFX

static FullScreenFX::Params g_defaultParams;

FullScreenFX::Params::Params()
{
  InMin  = CVec4(0.f, 0.f, 0.f, 0.f);
  InMax  = CVec4(1.f, 1.f, 1.f, 0.f);
  OutMin = CVec4(0.f, 0.f, 0.f, 0.f);
  OutMax = CVec4(1.f, 1.f, 1.f, 0.f);
  Gamma  = CVec4(0.f, 0.f, 0.f, 0.f);

  Color = CVec4(1.f, 1.f, 1.f, 1.f);
  ColorCastCoef = 0.f;

  SharpPixelSize = 0.0027f;
  SharpCoef = 0.f;
}

FullScreenFX::FullScreenFX() : pBloom(new Bloom)
{
  // dip descriptor
  VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement(VertexElementDescriptor(0, 0,	VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0));
  formatDescriptor.AddVertexElement(VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 0));
  //formatDescriptor.AddVertexElement(VertexElementDescriptor(15, 0, VERTEXELEMENTTYPE_FLOAT16_4, VERETEXELEMENTUSAGE_COLOR, 0));
  formatDescriptor.AddVertexElement(VertexElementDescriptor(15, 0, VERTEXELEMENTTYPE_FLOAT16_4, VERETEXELEMENTUSAGE_TEXCOORD, 1));
  pVDecl = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
}

FullScreenFX::~FullScreenFX()
{
}

static void SetWarFogParams(const SceneConstants &viewSceneConsts)
{
  RenderStatesManager& statesManager = *GetStatesManager();
  statesManager.SetStateDirect(D3DRS_ZENABLE, 0);
  statesManager.SetStencilState(STENCILSTATE_IGNORE);

  float xScale = 1.0f / viewSceneConsts.projection._11;
  float yScale = 1.0f / viewSceneConsts.projection._22;
  float zNear = fabs(viewSceneConsts.projection._33) < FP_EPSILON ? 0.0f : -viewSceneConsts.projection._34 / viewSceneConsts.projection._33;
  SHMatrix mScreen2WarFog;
  {
    //static const SHMatrix mScreen2View(2 * xScale, 0, -xScale, 0,
    //                                   0, -2* yScale,  yScale, 0,
    //                                   0,          0,       1, 0,
    //                                   0,          0,       0, 1);

    //Multiply(&mScreen2WarFog, viewSceneConsts.invView, mScreen2View);
  } {
    const SHMatrix mWorld2WarFog(1.0f / viewSceneConsts.worldSize.x, 0, 0, 0,
                                 0,-1.0f / viewSceneConsts.worldSize.y, 0, 1,
                                 0,                                  0, 1, 0,
                                 0,                                  0, 0, 1);
    mScreen2WarFog = mWorld2WarFog * viewSceneConsts.invView;
  }

  Renderer* const renderer = GetRenderer();
  renderer->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST2, CVec4(2.0f * xScale, -2.0f * yScale, -xScale, yScale));
  renderer->SetVertexShaderConstantsMatrix(VSHADER_LOCALCONST3, mScreen2WarFog);
  renderer->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST0, mScreen2WarFog.GetTrans4() );
  renderer->SetPixelShaderConstantsFloat(PSHADER_LOCALCONST1, zNear + 0.001f);
}


static float s_sharpCenterScale = 1.0f;
REGISTER_DEV_VAR("pfx_sharp_center", s_sharpCenterScale, STORAGE_USER);

// Given a pointer to FullScreenFX::Params member of type T, fill an array of _count values of type T
template<class T>
static void inline FillParam(const T &_src, T* _dest)
{
  const UINT stride = sizeof(FullScreenFX::Params);
  const T* _pSrc = &_src;
  for(UINT n = 0; n < NATURE_TYPES_COUNT; ++n)
  {
    _dest[n] = *_pSrc;
    _pSrc = (T*)((char*)_pSrc + stride);
  }
}


static void inline SetSampler(Sampler *_sampler, Texture2D* _tex)
{
  _sampler->Enable( bool(_tex) );
  if(_tex)
    _sampler->SetTexture(_tex);
}


static NDb::ColorCorrectPin inline ComputeColorCorrectMode(FullScreenFX::Params const *params, CVec4 const &colorCastCoeff)
{
  NDb::ColorCorrectPin colorCorrectPinValue = NDb::COLORCORRECTPIN_ON;

  bool izGammaZero = true;
  for(int i = 0; i < NATURE_TYPES_COUNT; ++i) {
    const CVec4& gamma = params[i].Gamma;
    izGammaZero &= (0 == gamma[0]) && (0 == gamma[1]) && (0 == gamma[2]);
  }

  if(izGammaZero) {
    colorCorrectPinValue = NDb::COLORCORRECTPIN_NO_GAMMA;
    bool noInOutCorrection = true;
    for(int i = 0; i < NATURE_TYPES_COUNT; ++i) {
      const CVec4& InMin = params[i].InMin;
      noInOutCorrection &= (.0f == InMin[0]) && (.0f == InMin[1]) && (.0f == InMin[2]);
      const CVec4& InMax = params[i].InMax;
      noInOutCorrection &= (1.f == InMax[0]) && (1.f == InMax[1]) && (1.f == InMax[2]);
      const CVec4& OutMin = params[i].OutMin;
      noInOutCorrection &= (.0f == OutMin[0]) && (.0f == OutMin[1]) && (.0f == OutMin[2]);
      const CVec4& OutMax = params[i].OutMax;
      noInOutCorrection &= (1.f == OutMax[0]) && (1.f == OutMax[1]) && (1.f == OutMax[2]);
    }

    if(noInOutCorrection) {
      colorCorrectPinValue = NDb::COLORCORRECTPIN_DESATURATE_ONLY;
      bool noCorrection = true;
      for(int i = 0; i < NATURE_TYPES_COUNT; ++i) {
        noCorrection &= (.0f == colorCastCoeff[i]);
      }
      if(noCorrection)
        colorCorrectPinValue = NDb::COLORCORRECTPIN_OFF;
    }
  }

  return colorCorrectPinValue;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FullScreenFX::Apply(const SceneConstants &viewSceneConsts, Texture2D *pTexture, TextureVtx *pCoeffTexture,
                         bool doColorCorrect, bool doSharp, float colorSaturation, Texture2D *pDepthTexture, Params const *params,
                         const CVec4& satColor, bool useSatColor )
{
  Texture2D* const pBloomTexture = pBloom->GetBlendSource();

  /////////////////////////////////////////////////////////////////////////////
  // set shader constants
  if (!params)
    params = &g_defaultParams;

  CVec4 colorCastCoef;
  FillParam(params[0].ColorCastCoef, colorCastCoef.m);

  //In colorCastCoef value 1.0f means grayscale; colorCastCoef.w is ignored
  const float invSat = 1 - colorSaturation;
  colorCastCoef.AsVec3D() *= colorSaturation;
  colorCastCoef.AsVec3D() += CVec3(invSat, invSat, invSat);

  NI_STATIC_ASSERT(NATURE_TYPES_COUNT <= 4, TOO_MUCH_NATURE_TYPES);

  const UINT numParams = PP_PIVOT_PARAMS_COUNT * NATURE_TYPES_COUNT;
  CVec4 pivotParams[numParams];
  FillParam(params[0].InMin, pivotParams + PP_IN_MIN * NATURE_TYPES_COUNT);
  FillParam(params[0].InMax, pivotParams + PP_IN_MAX * NATURE_TYPES_COUNT);
  FillParam(params[0].OutMin, pivotParams + PP_OUT_MIN * NATURE_TYPES_COUNT);
  FillParam(params[0].OutMax, pivotParams + PP_OUT_MAX * NATURE_TYPES_COUNT);
  FillParam(params[0].Gamma,  pivotParams + PP_GAMMA * NATURE_TYPES_COUNT);

  if ( useSatColor )
    FillParam(satColor,  pivotParams + PP_COLOR * NATURE_TYPES_COUNT);
  else
    FillParam(params[0].Color,  pivotParams + PP_COLOR * NATURE_TYPES_COUNT);

  const bool useCoeffTexture = pCoeffTexture && (doSharp || doColorCorrect);
  const bool useR2VB = useCoeffTexture && pCoeffTexture->UsingR2VB();

  RenderStatesManager& statesManager = *GetStatesManager();

  if(useR2VB)
    statesManager.SetStateDirect( D3DRS_POINTSIZE, r2vbGlbEnable_Set(TRUE) );

  Renderer& renderer = *GetRenderer();
  renderer.SetVertexShaderConstantsVector4(VSHADER_LOCALCONST10, colorCastCoef);
  renderer.SetVertexShaderConstants(VSHADER_LOCALCONST11, numParams, pivotParams);

  NDb::ColorCorrectPin colorCorrectPinValue = doColorCorrect && pCoeffTexture ? ComputeColorCorrectMode(params, colorCastCoef)
                                                                              : NDb::COLORCORRECTPIN_OFF;

  /////////////////////////////////////////////////////////////////////////////
  // Set material pins and textures
  s_MaterialHolder.SetPins(colorCorrectPinValue, doSharp && pCoeffTexture, pBloomTexture, pDepthTexture, useR2VB);

  FullScreenMaterial* const pMaterial = s_MaterialHolder.GetMaterial();

  if(pDepthTexture) {
    SetWarFogParams(viewSceneConsts);
    pMaterial->GetDepthMap()->SetTexture(pDepthTexture);
  }
  pMaterial->GetDepthMap()->Enable( bool(pDepthTexture) );

  SetSampler(pMaterial->GetBloomMap(), pBloomTexture);
  SetSampler(pMaterial->GetDiffuseMap(), pTexture);

  if(useCoeffTexture) {
    // pixelSize, sharpPixelSize, SharpCoef
    CVec4 sharpParams[3] = { CVec4(1.0f/pTexture->GetWidth(), 1.0f/pTexture->GetHeight(), 0.f, s_sharpCenterScale) };
    FillParam(params[0].SharpPixelSize, sharpParams[1].m);
    FillParam(params[0].SharpCoef, sharpParams[2].m);

    renderer.SetVertexShaderConstants(VSHADER_LOCALCONST7, 3, sharpParams);
    pCoeffTexture->Bind(Sampler::MIN_VS_SAMPLER_INDEX);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Render
  statesManager.SetState( RenderState::NoBlendNoTest() );
  if(useR2VB)
    GetImmRenderer()->RenderScreenQuad(ImmRenderer::MaterialParams(pMaterial), pVDecl);
  else
    GetImmRenderer()->RenderScreenQuad( ImmRenderer::MaterialParams(pMaterial) );

  GetDevice()->SetTexture(1, 0); // Unbind pTexture (because it is RT)
  if(useCoeffTexture)
    pCoeffTexture->UnBind();

  if(useR2VB)
    statesManager.SetStateDirect( D3DRS_POINTSIZE, r2vbGlbEnable_Set(FALSE) );
}

} // namespace Render

// end of FullScreenFX.cpp
