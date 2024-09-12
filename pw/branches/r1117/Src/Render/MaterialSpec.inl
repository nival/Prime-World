#include "sceneconstants.h"
#include "batch.h"
#include "SHCoeffs.h"
#include "WaterMesh.h"

#ifndef _SHIPPING

static bool s_instanceDecals = true;
REGISTER_DEV_VAR("instanceDecals", s_instanceDecals, STORAGE_NONE);

#else

enum {
  s_instanceDecals = true
};

#endif

namespace Render
{

  Matrix43 Material::worldMatrices[MAX_INSTANCES_COUNT];

inline NDb::OpacityAndEmissiveModePin ConvertOpacityAndEmissiveModeToAlpha(NDb::OpacityAndEmissiveModePin pin)
{
	switch (pin)
	{
	case NDb::OPACITYANDEMISSIVEMODEPIN_SIMPLE:             return NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY;
	case NDb::OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY:    return NDb::OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY;
	case NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY:       return NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY;
	case NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE:           return NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY;
	}
	NI_ALWAYS_ASSERT("Unknown enum");
	return NDb::OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY;
}

template <typename T> 
void SetupMaterialAccordingOpacity(float opacity, Render::RenderState &renderState, 
                                   NDb::OpacityAndEmissiveModePin &pinValue, const NDb::Ptr<T> &pDbMaterial, bool isBlendModeOverrided)
{
  if (opacity == 1.0f)
  {
    renderState.SetBlendMode(pDbMaterial->renderState.blendMode);
    renderState.SetAlphaTest(pDbMaterial->renderState.alphaTest);
    pinValue = pDbMaterial->OpacityAndEmissiveModePinValue;
  }
  else
  {
    if (pDbMaterial->renderState.blendMode == NDb::BLENDMODE_OFF && !isBlendModeOverrided)
      renderState.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
    pinValue = ConvertOpacityAndEmissiveModeToAlpha(pDbMaterial->OpacityAndEmissiveModePinValue);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void BasicFXMaterial::UpdateInternals()
{
  NI_DATA_ASSERT( !( DistortionPinValue != NDb::DISTORTIONPIN_DISTORTNONE &&
                     OpacityAndEmissiveModePinValue == NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE ),
                  NStr::StrFmt("Material has distortion & emissive at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  NI_DATA_ASSERT( !( DistortionPinValue != NDb::DISTORTIONPIN_DISTORTNONE &&
                    (renderState.blendMode == NDb::BLENDMODE_ADDCOLOR ||
                     renderState.blendMode == NDb::BLENDMODE_ADDCOLORMULALPHA) ),
                  NStr::StrFmt("Material has distortion & additive blending at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  NI_DATA_ASSERT( !(renderState.blendMode != NDb::BLENDMODE_OFF && 
                    OpacityAndEmissiveModePinValue >= NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE),
                   NStr::StrFmt("Material has emissive and blending at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  if (DistortionPinValue != NDb::DISTORTIONPIN_DISTORTNONE)
		priority = NDb::MATERIALPRIORITY_DISTORTION;
  else
    priority = (renderState.GetBlendMode() != NDb::BLENDMODE_OFF ? NDb::MATERIALPRIORITY_TRANSPARENT : NDb::MATERIALPRIORITY_MESHESOPAQUE);

	bool isEmissiveUsed = (OpacityAndEmissiveModePinValue == NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE);
	renderState.SetEmissive(isEmissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
}

inline void BasicFXMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

	CVec4 uvspeed4(uOffset, vOffset + 1, 0.f, 0.f);
	GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, uvspeed4);

  {
    bool emissiveUsed = (OpacityAndEmissiveModePinValue == NDb::EMISSIVEPIN_EMISSIVEFROMALPHA);
    renderState.SetEmissive(emissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
  }

	CVec4 opacityAndEmissive4(opacity * masterOpacity, emissive, 0, 0);
	GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityAndEmissive4);

	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, DiffuseMul);
	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, DiffuseAdd);
	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER1_MUL, DiffuseMul);
	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER1_ADD, DiffuseAdd);

  // set distortion scale
  GetRenderer()->SetPixelShaderConstantsVector4(DISTORTION_PARAMS1, CVec4(2.0f * distortion, 2.0f * distortion, -distortion, -distortion));
}

inline void BasicFXMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
	if (pDbMaterial)
	{
		HDRColor modMul, modAdd;
    MarkMaterialUpdated();
		DiffuseMul.Mad(mul, pDbMaterial->DiffuseMul, add);
		DiffuseAdd.Mul(mul, pDbMaterial->DiffuseAdd);
	}
}

inline void BasicFXMaterial::ModifyOpacity(float opacity_)
{
  MarkMaterialUpdated();
	masterOpacity = opacity_;
  SetupMaterialAccordingOpacity(masterOpacity, renderState, OpacityAndEmissiveModePinValue, pDbMaterial, isBlendModeOverrided);
  UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void BasicFXMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();
  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void BasicFXMaterial::ModifyUVOffset(float u, float v)
{
	uOffset = u;
	vOffset = v;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// class BasicMaterial ////////////////////////////////////////////////////////////////////////////////////////

namespace {
  enum {
    SH_SIZE = sizeof(Render::SHShaderConstants) / sizeof(CVec4),
    SH_SIZE_NONLINEAR = SH_SIZE - 3
  };

  CVec4 shConstants[SH_SIZE * MAX_INSTANCES_COUNT];
  UINT  numInstances = 0;
  const float minSpecPower = 1e-2f; // Older GPUs can misbehave when specPower == 0.
}


inline void BasicMaterial::UpdateInternals()
{
  NI_DATA_ASSERT( !(renderState.blendMode != NDb::BLENDMODE_OFF && EmissivePinValue != NDb::EMISSIVEPIN_EMISSIVEOFF)
                  ||(OpacityPinValue == NDb::BOOLEANPIN_PRESENT),
                  NStr::StrFmt("Material has emissive and blending at the same time: '%s'",
                  NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  if (renderState.GetBlendMode() == NDb::BLENDMODE_OFF)
    priority = NDb::MATERIALPRIORITY_MESHESOPAQUE;
  else if (specialTransparency)
    priority = NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL;
  else
    priority = NDb::MATERIALPRIORITY_TRANSPARENT;

  bool isEmissiveUsed = (EmissivePinValue == NDb::EMISSIVEPIN_EMISSIVEFROMALPHA || EmissivePinValue == NDb::EMISSIVEPIN_EMISSIVEFROMSPECULAR);
	renderState.SetEmissive(isEmissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);

  NormalMapPinValue = (NDb::BooleanPin)(NormalMap.GetTexture() && NormalMap.GetTexture() != GetWhiteTexture2D());
  SpecularMapPinValue = (NDb::BooleanPin)(SpecularMap.GetTexture() && SpecularMap.GetTexture() != GetWhiteTexture2D());
  SpecularPinValue = (NDb::BooleanPin)(specularPower > minSpecPower);
  UpdateStaticShaderIndex();
}

inline void BasicMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

  if(GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERNORMAL)
  {
    CVec4 opacityEmissiveReflectivitySpecPower( opacity, emissive, reflectivity, max(minSpecPower, specularPower) );
    GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityEmissiveReflectivitySpecPower);

    GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, outputMul);
    GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, outputAdd);

    if (LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH)
    {
      GetRenderer()->SetVertexShaderConstantsColor(INSTANCING_AMBIENTCOLOR, SceneConstants::Global().ambientColor);
      HDRColor color(diffuseColor.R, diffuseColor.G, diffuseColor.B, lightingIntencity); 
      GetRenderer()->SetVertexShaderConstantsColor(INSTANCING_DIFFUSE_COEFF, color);

      GetRenderer()->SetVertexShaderConstantsColor(INSTANCING_COLOR_MIN, SceneConstants::Global().minBakedColor);
      GetRenderer()->SetVertexShaderConstantsColor(INSTANCING_COLOR_MAX, SceneConstants::Global().maxBakedColor);
    }
  }
/*
  {
    IDirect3DDevice9* const device = GetDevice();
    HRESULT hr = S_OK;
    DWORD val;
    hr = device->GetRenderState(D3DRS_STENCILENABLE, &val);
    hr = device->GetRenderState(D3DRS_STENCILFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILZFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILPASS, &val);
    hr = device->GetRenderState(D3DRS_STENCILFUNC, &val);
    hr = device->GetRenderState(D3DRS_STENCILREF, &val);
    hr = device->GetRenderState(D3DRS_STENCILMASK, &val);
    hr = device->GetRenderState(D3DRS_STENCILWRITEMASK, &val);
  } */
}

bool BasicMaterial::Instanceable() const
{
  return SkeletalMeshPinValue != NDb::BOOLEANPIN_PRESENT && LightingPinValue != NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH
         && (LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGDYNAMIC
             || GetRuntimePins().RenderModeValue != NDb::RENDERMODEPIN_RENDERNORMAL);
}

bool BasicMaterial::SkipIDEvaluation() const { return Need2CallUpdate(); }

void BasicMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  Renderer &renderer = *GetRenderer();

  if(GetRuntimePins().InstancingValue == NDb::BOOLEANPIN_PRESENT)
  {
    renderer.SetVertexShaderConstants(VSHADER_LOCALCONST9, 3 * numInstances, worldMatrices);
    numInstances = 0;
  }

  if(GetRuntimePins().RenderModeValue != NDb::RENDERMODEPIN_RENDERNORMAL)
    return;

  const bool lightingSH = (LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGSH);
  if(lightingSH)
  {
    NI_ASSERT(batch.pSHConsts, "Spherical harmonics constants should present in batch");

    //if(numInstances)
    //{
    //  if( NormalMapPinValue == NDb::BOOLEANPIN_NONE )
    //  {
    //    renderer.SetVertexShaderConstants(VSHADER_LOCALCONST1, 3 * numInstances, batch.pSHConsts);
    //    renderer.SetPixelShaderConstants(PSHADER_SHCONSTS, SH_SIZE_NONLINEAR * numInstances, batch.pSHConsts);
    //  }
    //  else
    //    renderer.SetPixelShaderConstants(PSHADER_SHCONSTS, SH_SIZE * numInstances, batch.pSHConsts);

    //  numInstances = 0;
    //}
    //else
    {
      renderer.SetPixelShaderConstants(PSHADER_SHCONSTS, SH_SIZE, batch.pSHConsts);
      if( NormalMapPinValue == NDb::BOOLEANPIN_NONE )
        renderer.SetVertexShaderConstants(VSHADER_LOCALCONST1, 3, batch.pSHConsts);
    }
  }

  if(lightingSH || LightingPinValue >= NDb::LIGHTINGPIN_LIGHTINGDYNAMIC)
  {
    HDRColor color(diffuseColor.R, diffuseColor.G, diffuseColor.B, lightingIntencity); 
    renderer.SetPixelShaderConstantsHDRColor(BASICMAT_DIFFUSE1, color);
  }
}

void BasicMaterial::RegisterInstancedBatch(const Batch &batch)
{
  ASSERT(numInstances < MAX_INSTANCES_COUNT);
  if(NDb::RENDERMODEPIN_RENDERNORMAL == GetRuntimePins().RenderModeValue)
  {
    if(NDb::LIGHTINGPIN_LIGHTINGSH == LightingPinValue)
    {
      if(NDb::BOOLEANPIN_NONE == NormalMapPinValue)
      {
        memcpy( shConstants + 3 * numInstances, batch.pSHConsts, 3 * sizeof(CVec4) );
        memcpy( shConstants + 3 * MAX_INSTANCES_COUNT + SH_SIZE_NONLINEAR * numInstances,
          (char*)(batch.pSHConsts) + 3 * sizeof(CVec4), SH_SIZE_NONLINEAR * sizeof(CVec4) );
      }
      else
        memcpy( shConstants + SH_SIZE * numInstances, batch.pSHConsts, SH_SIZE * sizeof(CVec4) );
    }
  }
  worldMatrices[numInstances++] = batch.pOwner->GetWorldMatrix();
}

inline void BasicMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
  MarkMaterialUpdated();
	outputMul = mul;
	outputAdd = add;
}

inline void BasicMaterial::ModifyEmissive(float power)
{
  if (!pDbMaterial)
    return;

  MarkMaterialUpdated();

  emissive = power * pDbMaterial->emissive;

  UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void BasicMaterial::ModifyOpacity(float opacity_)
{
	if (!pDbMaterial)
		return;

  MarkMaterialUpdated();

	opacity = opacity_ * pDbMaterial->opacity;
	if (opacity == 1.0f)
	{
		renderState.SetBlendMode(pDbMaterial->renderState.blendMode);
		renderState.SetAlphaTest(pDbMaterial->renderState.alphaTest);
		EmissivePinValue = pDbMaterial->EmissivePinValue;
    OpacityPinValue = NDb::BOOLEANPIN_NONE;
	}
	else
	{
    EmissivePinValue = NDb::EMISSIVEPIN_EMISSIVEOFF;
    OpacityPinValue = NDb::BOOLEANPIN_PRESENT;
    if ( !isBlendModeOverrided )
		  renderState.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
	}
	UpdateStaticShaderIndex();
	UpdateInternals();
}

inline void BasicMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();

  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ParticleFXMaterial::UpdateInternals()
{
  NI_DATA_ASSERT( !(renderState.blendMode != NDb::BLENDMODE_OFF && 
                    OpacityAndEmissiveModePinValue >= NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE),
                   NStr::StrFmt("Material has emissive and blending at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  if (DistortionPinValue != NDb::BOOLEANPIN_NONE)
		priority = NDb::MATERIALPRIORITY_DISTORTION;
	else
		priority = (renderState.GetBlendMode() != NDb::BLENDMODE_OFF ? NDb::MATERIALPRIORITY_TRANSPARENT : NDb::MATERIALPRIORITY_MESHESOPAQUE);
}

inline void ParticleFXMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

  if(DistortionPinValue == NDb::BOOLEANPIN_PRESENT || GetRuntimePins().NewParticlesValue == FALSE)
  {
    CVec4 opacityAndEmissive4(opacity, 0, 0, 0);
    GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityAndEmissive4);
  }
    // set distortion scale
  if(DistortionPinValue == NDb::BOOLEANPIN_PRESENT)
    GetRenderer()->SetPixelShaderConstantsVector4(DISTORTION_PARAMS1, CVec4(2.0f * distortion, 2.0f * distortion, -distortion, -distortion));
}

inline void ParticleFXMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
  if (pDbMaterial)
  {
    MarkMaterialUpdated();

    HDRColor modMul, modAdd;
    modMul.Mad(mul, pDbMaterial->DiffuseMap.Multiplier, add);
    modAdd.Mul(mul, pDbMaterial->DiffuseMap.Add);
    DiffuseMap.SetMultiplierAndAdd(modMul, modAdd);
  }
}

inline void ParticleFXMaterial::ModifyOpacity(float opacity_)
{
	if (!pDbMaterial)
		return;
  MarkMaterialUpdated();

	opacity = opacity_ * pDbMaterial->opacity;
  SetupMaterialAccordingOpacity(opacity, renderState, OpacityAndEmissiveModePinValue, pDbMaterial, isBlendModeOverrided);
	UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void ParticleFXMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();
  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    if( (scale < 0) && (blendMode == NDb::BLENDMODE_LERPBYALPHA) )
      blendMode = NDb::BLENDMODE_ADDCOLORMULALPHA;

    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

static bool s_doParticleInstancing = false;

void ParticleFXMaterial::SetInstancingFlag(bool enabled) { s_doParticleInstancing = enabled; }

int ParticleFXMaterial::GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize) const
{
  struct SamplerSignificantPart
  {
    SamplerState samplerState;
    void* pTexture;
  };

  if(DistortionPinValue == NDb::BOOLEANPIN_PRESENT || !s_doParticleInstancing)
    return Material::GetRSandSamplersRep(_pRep, _pProcessedSize);

  if(_pRep) {
    *((RenderState*)_pRep) = CorrectRS( renderState.GetCRCValue() );

    SamplerSignificantPart* const pSParts = (SamplerSignificantPart*)(_pRep + sizeof(RenderState));

    const int * const pDisplacements = samplers.samplers;
    PBYTE pMemberBase = PBYTE(this);

    for(int i = 0; i < samplers.count; ++i)
    {
      const Sampler *pSampler = (const Sampler*)(pMemberBase + pDisplacements[i]);
      Sampler::SignificantPart sp;
      pSampler->GetSignificantPart(&sp);
      pSParts[i].samplerState = sp.samplerState;
      pSParts[i].pTexture = sp.pTexture;
    }
  }

  if(_pProcessedSize)
    *_pProcessedSize = sizeof(RenderState) + samplers.count * sizeof(Sampler);

  return sizeof(RenderState) + samplers.count * sizeof(SamplerSignificantPart);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CVec2 g_aoeScaleHACK(1.0f, 1.0f);
CVec2 g_aoeOffsetHACK(0.0f, 0.0f);
CVec2& GetAOEScaleHACK() { return g_aoeScaleHACK; }
CVec2& GetAOEOffsetHACK() { return g_aoeOffsetHACK; }

inline void TerrainAOEMaterial::UpdateInternals()
{
//	priority = (default_BlendState.blendIsEnabled ? PRIORITY_NOPOSTEFFECT_TRANS : PRIORITY_NOPOSTEFFECT_SOLID);
}

inline void TerrainAOEMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

	uvScale = g_aoeScaleHACK;
	uvOffset = g_aoeOffsetHACK;

	CVec4 uvScaleOffset(uvScale.x, uvScale.y, uvOffset.x, uvOffset.y);
	GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, uvScaleOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// class TerrainMaterial ////////////////////////////////////////////////////////////////////////////////////////

// Get corrected render state and samplers representation for SortID calculation needs.
// Given null pointer, return size of required memory block
int TerrainMaterial::GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize) const
{
  if(_pProcessedSize)
    *_pProcessedSize = samplers.count * sizeof(Sampler);

  return Material::GetSamplersRep(_pRep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// class DecalMaterial ////////////////////////////////////////////////////////////////////////////////////////

namespace {
  struct DecalInstanceData
  {
    Matrix43 world;
    CVec4  opacityAndPlane;
  } decalInstanceData[MAX_INSTANCES_COUNT];
}


inline void DecalMaterial::UpdateInternals()
{
  NI_DATA_ASSERT( !(renderState.blendMode != NDb::BLENDMODE_OFF && 
                    OpacityAndEmissiveModePinValue >= NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE),
                   NStr::StrFmt("Material has emissive and blending at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  if (DistortionPinValue != NDb::BOOLEANPIN_NONE)
    priority = NDb::MATERIALPRIORITY_DISTORTION;
  else if (putOnWater)
    priority = NDb::MATERIALPRIORITY_WATERDECALS;
  else
    priority = NDb::MATERIALPRIORITY_TERRAINDECALS;
}

bool DecalMaterial::Instanceable() const
{
  return s_instanceDecals;
}

bool DecalMaterial::SkipIDEvaluation() const { return false; }

void DecalMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  if(GetRuntimePins().InstancingValue == NDb::BOOLEANPIN_PRESENT)
  {
    GetRenderer()->SetVertexShaderConstants(INSTANCE_DATA, 4 * numInstances, decalInstanceData);
    numInstances = 0;
  }
  else
  {
    // store the level of bounding box bottom plane
    AABB aabb;
    aabb.Transform(batch.pOwner->GetWorldMatrix(), batch.pOwner->GetLocalAABB());
    GetRenderer()->SetVertexShaderConstantsFloat(VSHADER_LOCALCONST0, aabb.center.z - aabb.halfSize.z);
  }
}

void DecalMaterial::RegisterInstancedBatch(const Batch &batch)
{
  ASSERT(numInstances < MAX_INSTANCES_COUNT);
  ASSERT(batch.pMaterial->GetDBMaterial()->GetObjectTypeID() == NDb::DecalMaterial::typeId);
  DecalMaterial* const pMaterial = static_cast<DecalMaterial*>(batch.pMaterial);

  decalInstanceData[numInstances].world = batch.pOwner->GetWorldMatrix();
  decalInstanceData[numInstances].opacityAndPlane.x = pMaterial->opacity * pMaterial->masterOpacity;
  
  // store the level of bounding box bottom plane
  AABB aabb;
  aabb.Transform(batch.pOwner->GetWorldMatrix(), batch.pOwner->GetLocalAABB());
  decalInstanceData[numInstances].opacityAndPlane.y = aabb.center.z - aabb.halfSize.z;

  ++numInstances;
}

inline void DecalMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

	CVec4 uvScaleOffset(0.5f / radius, -0.5f / radius, 0.5f, 0.5f);
	GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST2, uvScaleOffset);

	if(GetRuntimePins().InstancingValue != NDb::BOOLEANPIN_PRESENT)
  {
    CVec4 opacityAndEmissive4(opacity * masterOpacity, 0, 0, 0);
    GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityAndEmissive4);
  }

	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, DiffuseMul);
//  if( memcmp(&HDRColor::WHITE(), &DiffuseMul, sizeof(HDRColor)) )
//    DiffuseMul = DiffuseMul;

	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, DiffuseAdd);
//  static const HDRColor Black(0.0f,0.0f,0.0f,0.0f);
//  if( memcmp(&Black, &DiffuseAdd, sizeof(HDRColor)) )
//    DiffuseAdd = DiffuseAdd;

  // set distortion scale
  GetRenderer()->SetPixelShaderConstantsVector4(DISTORTION_PARAMS1, CVec4(2.0f * distortion, 2.0f * distortion, -distortion, -distortion));
/*
  {
    IDirect3DDevice9* const device = GetDevice();
    HRESULT hr = S_OK;
    DWORD val;
    hr = device->GetRenderState(D3DRS_STENCILENABLE, &val);
    hr = device->GetRenderState(D3DRS_STENCILFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILZFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILPASS, &val);
    hr = device->GetRenderState(D3DRS_STENCILFUNC, &val);
    hr = device->GetRenderState(D3DRS_STENCILREF, &val);
    hr = device->GetRenderState(D3DRS_STENCILMASK, &val);
    hr = device->GetRenderState(D3DRS_STENCILWRITEMASK, &val);
  } */
}

inline void DecalMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
  if (pDbMaterial)
  {
/*
		NI_DATA_ASSERT(!pDbMaterial->DiffuseMul.IsAnimated() && !pDbMaterial->DiffuseAdd.IsAnimated(), 
									 NStr::StrFmt("You can't recolor material (%s, %s) with animated diffuse mul & add", 
																pDbMaterial->GetDBID().GetFileName().c_str(),
																pDbMaterial->GetDBID().GetId().c_str()));
*/
    MarkMaterialUpdated();
    HDRColor modMul, modAdd;
    DiffuseMul.Mad(mul, pDbMaterial->DiffuseMul, add);
    DiffuseAdd.Mul(mul, pDbMaterial->DiffuseAdd);
  }
}

inline void DecalMaterial::ModifyEmissive(float power)
{

}

inline void DecalMaterial::ModifyOpacity(float opacity_)
{
  MarkMaterialUpdated();
	masterOpacity = opacity_;
  SetupMaterialAccordingOpacity(masterOpacity, renderState, OpacityAndEmissiveModePinValue, pDbMaterial, isBlendModeOverrided);
  UpdateStaticShaderIndex();
	UpdateInternals();
}

inline void DecalMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();
  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void DecalTerrainMaterial::UpdateInternals()
{
  NI_DATA_ASSERT( !(renderState.blendMode != NDb::BLENDMODE_OFF && 
                    OpacityAndEmissiveModePinValue >= NDb::OPACITYANDEMISSIVEMODEPIN_EMISSIVE),
                   NStr::StrFmt("Material has emissive and blending at the same time: '%s'",
                               NDb::GetFormattedDbId(GetDBMaterial()->GetDBID()).c_str()) );

  if (DistortionPinValue != NDb::BOOLEANPIN_NONE)
    priority = NDb::MATERIALPRIORITY_DISTORTION;
  else if (putOnWater)
    priority = NDb::MATERIALPRIORITY_WATERDECALS;
  else
    priority = NDb::MATERIALPRIORITY_TERRAINDOMINATIONDECALS;
}

bool DecalTerrainMaterial::Instanceable() const
{
  return s_instanceDecals;
}

bool DecalTerrainMaterial::SkipIDEvaluation() const { return false; }

void DecalTerrainMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  if(GetRuntimePins().InstancingValue == NDb::BOOLEANPIN_PRESENT)
  {
    GetRenderer()->SetVertexShaderConstants(INSTANCE_DATA, 4 * numInstances, decalInstanceData);
    numInstances = 0;
  }
  else
  {
    // store the level of bounding box bottom plane
    AABB aabb;
    aabb.Transform(batch.pOwner->GetWorldMatrix(), batch.pOwner->GetLocalAABB());
    GetRenderer()->SetVertexShaderConstantsFloat(VSHADER_LOCALCONST0, aabb.center.z - aabb.halfSize.z);
  }
}

void DecalTerrainMaterial::RegisterInstancedBatch(const Batch &batch)
{
  ASSERT(numInstances < MAX_INSTANCES_COUNT);
  ASSERT(batch.pMaterial->GetDBMaterial()->GetObjectTypeID() == NDb::DecalTerrainMaterial::typeId);
  DecalTerrainMaterial* const pMaterial = static_cast<DecalTerrainMaterial*>(batch.pMaterial);

  decalInstanceData[numInstances].world = batch.pOwner->GetWorldMatrix();
  decalInstanceData[numInstances].opacityAndPlane.x = pMaterial->opacity * pMaterial->masterOpacity;
  
  // store the level of bounding box bottom plane
  AABB aabb;
  aabb.Transform(batch.pOwner->GetWorldMatrix(), batch.pOwner->GetLocalAABB());
  decalInstanceData[numInstances].opacityAndPlane.y = aabb.center.z - aabb.halfSize.z;

  ++numInstances;
}

inline void DecalTerrainMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

	CVec4 uvScaleOffset(0.5f / radius, -0.5f / radius, 0.5f, 0.5f);
	GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST2, uvScaleOffset);

	if(GetRuntimePins().InstancingValue != NDb::BOOLEANPIN_PRESENT)
  {
    CVec4 opacityAndEmissive4(opacity * masterOpacity, 0, 0, 0);
    GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityAndEmissive4);
  }

	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, DiffuseMul);
//  if( memcmp(&HDRColor::WHITE(), &DiffuseMul, sizeof(HDRColor)) )
//    DiffuseMul = DiffuseMul;

	GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, DiffuseAdd);
//  static const HDRColor Black(0.0f,0.0f,0.0f,0.0f);
//  if( memcmp(&Black, &DiffuseAdd, sizeof(HDRColor)) )
//    DiffuseAdd = DiffuseAdd;

  // set distortion scale
  GetRenderer()->SetPixelShaderConstantsVector4(DISTORTION_PARAMS1, CVec4(2.0f * distortion, 2.0f * distortion, -distortion, -distortion));
/*
  {
    IDirect3DDevice9* const device = GetDevice();
    HRESULT hr = S_OK;
    DWORD val;
    hr = device->GetRenderState(D3DRS_STENCILENABLE, &val);
    hr = device->GetRenderState(D3DRS_STENCILFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILZFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILPASS, &val);
    hr = device->GetRenderState(D3DRS_STENCILFUNC, &val);
    hr = device->GetRenderState(D3DRS_STENCILREF, &val);
    hr = device->GetRenderState(D3DRS_STENCILMASK, &val);
    hr = device->GetRenderState(D3DRS_STENCILWRITEMASK, &val);
  } */
}

inline void DecalTerrainMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
  if (pDbMaterial)
  {
/*
		NI_DATA_ASSERT(!pDbMaterial->DiffuseMul.IsAnimated() && !pDbMaterial->DiffuseAdd.IsAnimated(), 
									 NStr::StrFmt("You can't recolor material (%s, %s) with animated diffuse mul & add", 
																pDbMaterial->GetDBID().GetFileName().c_str(),
																pDbMaterial->GetDBID().GetId().c_str()));
*/
    MarkMaterialUpdated();
    HDRColor modMul, modAdd;
    DiffuseMul.Mad(mul, pDbMaterial->DiffuseMul, add);
    DiffuseAdd.Mul(mul, pDbMaterial->DiffuseAdd);
  }
}

inline void DecalTerrainMaterial::ModifyEmissive(float power)
{

}

inline void DecalTerrainMaterial::ModifyOpacity(float opacity_)
{
  MarkMaterialUpdated();
	masterOpacity = opacity_;
  SetupMaterialAccordingOpacity(masterOpacity, renderState, OpacityAndEmissiveModePinValue, pDbMaterial, isBlendModeOverrided);
  UpdateStaticShaderIndex();
	UpdateInternals();
}

inline void DecalTerrainMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();
  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void HeightfogMaterial::UpdateInternals()
{
}

inline void HeightfogMaterial::OnPrepareRender()
{
	Material::OnPrepareRender();

	const SceneConstants &sceneConsts = SceneConstants::Global();
	float a = speed * 0.01f * sceneConsts.renderTime * FP_2PI;
	float sina = sinf(a), cosa = cosf(a);

	GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, CVec4(noiseR1 * cosa, noiseR1 * sina, -noiseR2 * cosa, -noiseR2 * sina));
	GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST1, CVec4(1.0f / tiling, 888.888f, 888.888f, 888.888f));

	static const float FP_LN_2 = 0.69314718056f;
	GetRenderer()->SetPixelShaderConstantsVector4(PSHADER_LOCALCONST2, CVec4(noiseR3, roughnessScale, -FP_LN_2 / halfFadeDistance, 888.888f));
	GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST3, color1);
	GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST4, color2);

}

void HeightfogMaterial::ModifyOpacity(float _opacity)
{
  if (!pDbMaterial)
    return;

  MarkMaterialUpdated();

  const float maxDist = 32.f;
  halfFadeDistance = pDbMaterial->halfFadeDistance * (_opacity + maxDist * (1 - _opacity));

  UpdateStaticShaderIndex();
  UpdateInternals();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DropMaterial::UpdateInternals()
{
  priority = (renderState.GetBlendMode() != NDb::BLENDMODE_OFF ? NDb::MATERIALPRIORITY_TRANSPARENT : NDb::MATERIALPRIORITY_MESHESOPAQUE);

  bool isEmissiveUsed = (
    LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSEEMISSIVE || 
    LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE || 
    LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE);
  renderState.SetEmissive(isEmissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
}

inline void DropMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();

  // old
  //CVec4 uvspeed4(uvSpeed, 0, 0);
  //GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, uvspeed4);

  // new
  CVec4 uvspeed4(uOffset1, vOffset1, uOffset2, vOffset2);
  GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, uvspeed4);
  //

  {
    bool emissiveUsed = (LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSEEMISSIVE
                         || LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE
                         || LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE);
    renderState.SetEmissive(emissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
  }
  CVec4 opacityEmissiveReflectivitySpecPower(opacity, emissive, 0.0f, specularPower);
  GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityEmissiveReflectivitySpecPower);

  CVec4 reflectivityLerpAdd(reflectivityLerp, reflectivityAdd, reflectivityMul, 0.0f);
  GetRenderer()->SetPixelShaderConstantsVector4(c30, reflectivityLerpAdd);

  CVec4 ambientParams( additionalAmbient.R, additionalAmbient.G, additionalAmbient.B, ambientIntensity );
  GetRenderer()->SetPixelShaderConstantsVector4(c31, ambientParams);

  GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, outputMul);
  GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, outputAdd);
}

bool DropMaterial::Instanceable() const
{
  return false;
}

inline void DropMaterial::ModifyEmissive(float power)
{

}

bool DropMaterial::SkipIDEvaluation() const { return Need2CallUpdate(); }

void DropMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  //if(numInstances)
  //  GetRenderer()->SetVertexShaderConstants(VSHADER_LOCALCONST9, numInstances  * 3, worldMatrices);
  //else
  {
    NI_ASSERT(batch.pSHConsts, "Spherical harmonics constants should present in batch");
    NI_STATIC_ASSERT(sizeof(SHShaderConstants) == 7 * sizeof(CVec4), Invalid_SHShaderConstants_size_assumption);
    GetRenderer()->SetPixelShaderConstants(PSHADER_SHCONSTS, 7, batch.pSHConsts);
    if( NormalMapPinValue == NDb::BOOLEANPIN_NONE )
      GetRenderer()->SetVertexShaderConstants(VSHADER_LOCALCONST1, 3, batch.pSHConsts);
  }

	HDRColor color(diffuseColor.R, diffuseColor.G, diffuseColor.B, lightingIntencity); 
	GetRenderer()->SetPixelShaderConstantsHDRColor(BASICMAT_DIFFUSE1, color);

//    HDRColor cubeMapColorize[4];
//    cubeMapColorize[0] = reflectionMapColor0;
//    cubeMapColorize[1] = reflectionMapColor1;
//    cubeMapColorize[2] = reflectionMapColor2;
//    cubeMapColorize[3] = reflectionMapColor3;

//    GetRenderer()->SetPixelShaderConstants( PSHADER_LOCALCONST6, 4, &cubeMapColorize[0].R);

  GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST6, reflectionMapColor0);
  GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST7, reflectionMapColor1);
  GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST8, reflectionMapColor2);
  GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST9, reflectionMapColor3);

  numInstances = 0;
}

void DropMaterial::RegisterInstancedBatch(const Batch &batch)
{
  ASSERT(numInstances < MAX_INSTANCES_COUNT);

  if(NDb::LIGHTINGPIN_LIGHTINGSH == LightModePinValue)
  {
    if(NDb::BOOLEANPIN_NONE == NormalMapPinValue)
    {
      memcpy( shConstants + 3 * numInstances, batch.pSHConsts, 3 * sizeof(CVec4) );
      memcpy( shConstants + 3 * MAX_INSTANCES_COUNT + SH_SIZE_NONLINEAR * numInstances,
        (char*)(batch.pSHConsts) + 3 * sizeof(CVec4), SH_SIZE_NONLINEAR * sizeof(CVec4) );
    }
    else
      memcpy( shConstants + SH_SIZE * numInstances, batch.pSHConsts, SH_SIZE * sizeof(CVec4) );
  }

  worldMatrices[numInstances++] = batch.pOwner->GetWorldMatrix();
}

inline void DropMaterial::ModifyColor(const HDRColor &mul, const HDRColor &add)
{
  MarkMaterialUpdated();
  outputMul = mul;
  outputAdd = add;

  if(mul.R < 0)
  {
    int i = abs(mul.R);
    switch(i)
    {
    case 1: 
      reflectionMapColor0 = add;
      break;
    case 2: 
      reflectionMapColor1 = add;
      break;
    case 3: 
      reflectionMapColor2 = add;
      break;
    case 4: 
      reflectionMapColor3 = add;
      break;
    }
  }
}

inline void DropMaterial::ModifyReflectionColor(const HDRColor& _color0, const HDRColor& _color1, const HDRColor& _color2, const HDRColor& _color3)
{
  reflectionMapColor0 = _color0;
  reflectionMapColor1 = _color1;
  reflectionMapColor2 = _color2;
  reflectionMapColor3 = _color3;
}

inline void DropMaterial::ModifyOpacity(float opacity_)
{
  if (!pDbMaterial)
    return;

  MarkMaterialUpdated();

  opacity = opacity_;
  if (opacity == 1.0f)
  {
    renderState.SetBlendMode(pDbMaterial->renderState.blendMode);
    renderState.SetAlphaTest(pDbMaterial->renderState.alphaTest);
    LightModePinValue = pDbMaterial->LightModePinValue;
  }
  else
  {
    switch (pDbMaterial->LightModePinValue)
    {
    case NDb::LIGHTMODEPIN_DIFFUSE: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSEOPACITY; break;
    case NDb::LIGHTMODEPIN_DIFFUSESPECULAR: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSESPECULAROPACITY; break;
    case NDb::LIGHTMODEPIN_DIFFUSEEMISSIVE: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSEOPACITY; break;
    case NDb::LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE: 
    case NDb::LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE:
      LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSESPECULAROPACITY; 
      break;
    }
    if ( !isBlendModeOverrided )
      renderState.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
    renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

inline void DropMaterial::ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode )
{
  MarkMaterialUpdated();
  if ( isSetDefaultBlendMode )
  {
    isBlendModeOverrided = 0;
    renderState.SetBlendMode( pDbMaterial->renderState.blendMode );
  }
  else
  {
    isBlendModeOverrided = 1;
    renderState.SetBlendMode( blendMode );
  }
  UpdateStaticShaderIndex();
  UpdateInternals();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void TraceMaterial::UpdateInternals()
{
  if (GetDiffuseMap() && GetDiffuseMap()->GetTexture() && GetDiffuseMap()->GetTexture() != GetWhiteTexture2D())
    TraceTexturePinValue = NDb::BOOLEANPIN_PRESENT;
  else
    TraceTexturePinValue = NDb::BOOLEANPIN_NONE;
  UpdateStaticShaderIndex();
}

inline void TraceMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();

  CVec4 uvScaleOffset(uScale, vScale, uOffset, vOffset);
  GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST3, uvScaleOffset);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void WaterMaterial::UpdateInternals()
{
}

inline void WaterMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();
}

void WaterMaterial::PrepareRendererWithBatch(const Batch &batch)
{
	NI_ASSERT(dynamic_cast<WaterMesh const*>(batch.pOwner) != 0, "WaterMaterial must be on WaterMesh'es only");
	WaterMesh const* pMesh = static_cast<WaterMesh const*>(batch.pOwner);
	NDb::BooleanPin NewCausticsTexturePinValue = pMesh->HasCaustics() ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE;
	if (CausticsTexturePinValue != NewCausticsTexturePinValue)
	{
		CausticsTexturePinValue = NewCausticsTexturePinValue;
		UpdateInternals();
		UpdateStaticShaderIndex();
		Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkyMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();

  CVec4 uvspeed4(uOffset1, vOffset1, uOffset2, vOffset2);
  GetRenderer()->SetVertexShaderConstantsVector4(VSHADER_LOCALCONST0, uvspeed4);

  GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_MUL, outputMul);
  GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER0_ADD, outputAdd);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void SilhouetteMaterial::UpdateInternals()
{
}

inline void SilhouetteMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();
}

void SilhouetteMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  Render::Color uintColor(*(unsigned long *)&batch.sortValue);
  GetRenderer()->SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST0, HDRColor(uintColor));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void AOEMaterial::UpdateInternals()
{
}

inline void AOEMaterial::OnPrepareRender()
{
  Material::OnPrepareRender();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ShadowMaterial::Instanceable()     const { return SkeletalMeshPinValue != NDb::BOOLEANPIN_PRESENT && !oldInstancing; }
bool ShadowMaterial::SkipIDEvaluation() const { return false; }

void ShadowMaterial::PrepareRendererWithBatch(const Batch &batch)
{
  if(GetRuntimePins().InstancingValue == NDb::BOOLEANPIN_PRESENT)
  {
    GetRenderer()->SetVertexShaderConstants(INSTANCE_DATA, 3 * numInstances, worldMatrices);
    numInstances = 0;
  }
}

void ShadowMaterial::RegisterInstancedBatch(const Batch &batch)
{
  ASSERT(numInstances < MAX_INSTANCES_COUNT);
  worldMatrices[numInstances++] = batch.pOwner->GetWorldMatrix();
}


int ShadowMaterial::GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize) const
{
  enum { sizeOfSSP = sizeof(Sampler::SignificantPart),
         sspRestOffset = offsetof(Sampler::SignificantPart, samplerState),
         sspRestSize = offsetof(Sampler::SignificantPart, pTexture) + sizeof(void*) - sspRestOffset
  };

  int sspSize = 0, sspOffset = 0;
  if( renderState.GetAlphaTest() ) {
    if( DiffuseMap.HasModifiers() )
      sspSize = sizeOfSSP;
    else {
      sspSize = sspRestSize;
      sspOffset = sspRestOffset;
    }
  }
  const int size = sspSize + sizeof(renderState) + sizeof(oldInstancing);

  if(_pRep) {
    if( renderState.GetAlphaTest() )
    {
      Sampler::SignificantPart ssp;
      DiffuseMap.GetSignificantPart(&ssp);
      memcpy(_pRep, PBYTE(&ssp) + sspOffset, sspSize);
      _pRep += sspSize;
    }

    *((RenderState*)_pRep) = renderState.GetCRCValue();
    _pRep += sizeof(RenderState);
    *_pRep = oldInstancing;
  }

  if(_pProcessedSize)
    *_pProcessedSize = sizeof(RenderState) + samplers.count * sizeof(Sampler);

  return size;
}


ShadowMaterial* ShadowMaterial::CreateMaterial(BaseMaterial *pMaterial)
{
  ShadowMaterial* pNewMat = new ShadowMaterial;
  ASSERT(pMaterial && pNewMat);
  // HACK: static_cast is used here to get access rights to SignificantPartLength
  const int length = static_cast<ShadowMaterial*>(pMaterial)->SignificantPartLength();
  if(length > 0) {
    RenderState* const rs = (RenderState*)( PBYTE(pMaterial) + sizeof(BaseMaterial) );
    pNewMat->renderState = rs->GetCRCValue().SetBlendMode(NDb::BLENDMODE_OFF);
    const Render::Sampler* pSrcDiffuseMap = pMaterial->GetDiffuseMap();
    if(rs->alphaTest && pSrcDiffuseMap)
        pNewMat->DiffuseMap = *pSrcDiffuseMap;
      else
        pNewMat->DiffuseMap.Enable(false);
  }
  pNewMat->SetSkeletalMeshPin( pMaterial->GetSkeletalMeshPin() );
  pNewMat->SetPriority( pMaterial->GetPriority() );
  pNewMat->SetSubPriority( pMaterial->GetSubPriority() );
  pNewMat->SetMaterialFlags( pMaterial->GetMaterialFlags() );
  pNewMat->oldInstancing = ( pMaterial->GetLightingPin() == NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH );
  return pNewMat;
}

}
