//////////////////////////////////////////////////////////////////////////////////////////
// THIS FILE WAS GENERATED AUTOMATICALLY! DON'T CHANGE IT'S CONTENTS
//////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Render/renderer.h"
#include "../Render/GlobalMasks.h"
#include "../Render/Material.h"
#include "../Render/DBRender.h"
#include "../Render/RenderResourceManager.h"
#include "../libdb/AnimatedWrapper.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RuntimePins
{
	NDb::CachingPin CachingPinValue;
	NDb::DecalModePin DecalModeValue;
	NDb::BoolPin DoDepthOutValue;
	NDb::BoolPin DualDepthPinValue;
	NDb::BooleanPin InstancingValue;
	NDb::BoolPin NewParticlesValue;
	NDb::RenderModePin RenderModeValue;
	NDb::ShaderQualityPin ShaderQualityValue;
	RuntimePins();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RuntimePins& GetRuntimePins();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BaseMaterial : public Render::Material
{
protected:
  BaseMaterial( int priority, int flags, int shaderIndex ) : Render::Material( priority, flags, shaderIndex ) {}
public:
  virtual Render::Sampler* GetBackgroundMap() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetBackgroundMap() const { return (const Render::Sampler*)0; };
  virtual const Render::Sampler* GetBloomMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetBloomMap() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetBloomPin() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetBorderMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetBorderMap() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetCausticsTexturePin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::ColorCorrectPin GetColorCorrectPin() const { return (const NDb::ColorCorrectPin)0; };
  virtual const NDb::BooleanPin GetColorized() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetCustomizedGeometryPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetDebugPinValue() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetDepthMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetDepthMap() { return (Render::Sampler*)0; };
  virtual Render::Sampler* GetDiffuseMap() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetDiffuseMap() const { return (const Render::Sampler*)0; };
  virtual const Render::Sampler* GetDiffuseMap2() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetDiffuseMap2() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetDiffuseMapBurned() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetDiffuseMapBurned() { return (Render::Sampler*)0; };
  virtual Render::Sampler* GetDiffuseMapFrozen() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetDiffuseMapFrozen() const { return (const Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetDisablePin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetDrawContour() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::FlashBlendModePin GetFlashBlendModePin() const { return (const NDb::FlashBlendModePin)0; };
  virtual const NDb::BooleanPin GetGradient() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetHighlight() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetHighlight() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetHighlightPin() const { return (const NDb::BooleanPin)0; };
  virtual Render::Sampler* GetLackOfMana() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetLackOfMana() const { return (const Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetLackOfManaPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::LightingPin GetLightingPin() const { return (const NDb::LightingPin)0; };
  virtual const NDb::MaskingTypePin GetMasking() const { return (const NDb::MaskingTypePin)0; };
  virtual const Render::Sampler* GetMaskMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetMaskMap() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetMorphShapes() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetMultiplyVertexColorPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::OpacityAndEmissiveModePin GetOpacityModePin() const { return (const NDb::OpacityAndEmissiveModePin)0; };
  virtual const NDb::OrientTypePin GetOrientTypePin() const { return (const NDb::OrientTypePin)0; };
  virtual Render::Sampler* GetOverlayMap() { return (Render::Sampler*)0; };
  virtual const Render::Sampler* GetOverlayMap() const { return (const Render::Sampler*)0; };
  virtual const NDb::PackedMasksNumberPin GetPackedMasksNumberPin() const { return (const NDb::PackedMasksNumberPin)0; };
  virtual const NDb::PaintMaterialModePin GetPaintMaterialModePin() const { return (const NDb::PaintMaterialModePin)0; };
  virtual const NDb::BooleanPin GetPassivePin() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetPressed() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetPressed() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetPressedPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetR2VBPin() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetRoadMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetRoadMap() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetScale9Grid() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetScale9GridBitmap() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetScreenMap() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetScreenMap() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetShaderForLines() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetShadowCasterPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetSharpPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetStripes() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::TerrainUVSetPin GetTerrainUVSetPin() const { return (const NDb::TerrainUVSetPin)0; };
  virtual const NDb::TextureCountPin GetTextureCountPin() const { return (const NDb::TextureCountPin)0; };
  virtual const NDb::BooleanPin GetTextureFitPinValue() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetTraceTexturePin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetUseColorFilter() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetUseDiffuse() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetUseDiffuse2() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetUseDiffusePin() const { return (const NDb::BooleanPin)0; };
  virtual const Render::Sampler* GetWaitForActivation() const { return (const Render::Sampler*)0; };
  virtual Render::Sampler* GetWaitForActivation() { return (Render::Sampler*)0; };
  virtual const NDb::BooleanPin GetWaitForActivationPin() const { return (const NDb::BooleanPin)0; };
  virtual const NDb::BooleanPin GetWarFogPin() const { return (const NDb::BooleanPin)0; };
  virtual void ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode ) { };
  virtual void ModifyCoefs( const float coef3, const float coef4 ) { };
  virtual void ModifyColor( const Render::HDRColor &mul, const Render::HDRColor &add ) { };
  virtual void ModifyEmissive( float power ) { };
  virtual void ModifyOpacity( float opacity ) { };
  virtual void ModifyReflectionColor( const Render::HDRColor& _color0, const Render::HDRColor& _color1, const Render::HDRColor& _color2, const Render::HDRColor& _color3 ) { };
  virtual void ModifyStripesColor( const Render::HDRColor &color1, const Render::HDRColor &color2 ) { };
  virtual void ModifyStripesConstants( const float start, const float step1, const float step2, const float blendFactor1 ) { };
  virtual void ModifyUVOffset( float u, float v ) { };
  virtual void SetBlendModeOverride( bool state ) { };
  virtual void SetBloomPin( const NDb::BooleanPin value ) { };
  virtual void SetCausticsTexturePin( const NDb::BooleanPin value ) { };
  virtual void SetColorCorrectPin( const NDb::ColorCorrectPin value ) { };
  virtual void SetColorized( const NDb::BooleanPin value ) { };
  virtual void SetCustomizedGeometryPin( const NDb::BooleanPin value ) { };
  virtual void SetDebugPinValue( const NDb::BooleanPin value ) { };
  virtual void SetDisablePin( const NDb::BooleanPin value ) { };
  virtual void SetDrawContour( const NDb::BooleanPin value ) { };
  virtual void SetFlashBlendModePin( const NDb::FlashBlendModePin value ) { };
  virtual void SetGradient( const NDb::BooleanPin value ) { };
  virtual void SetHighlightPin( const NDb::BooleanPin value ) { };
  virtual void SetLackOfManaPin( const NDb::BooleanPin value ) { };
  virtual void SetLightingPin( const NDb::LightingPin value ) { };
  virtual void SetMasking( const NDb::MaskingTypePin value ) { };
  virtual void SetMorphShapes( const NDb::BooleanPin value ) { };
  virtual void SetMultiplyVertexColorPin( const NDb::BooleanPin value ) { };
  virtual void SetOpacityModePin( const NDb::OpacityAndEmissiveModePin value ) { };
  virtual void SetOrientTypePin( const NDb::OrientTypePin value ) { };
  virtual void SetPackedMasksNumberPin( const NDb::PackedMasksNumberPin value ) { };
  virtual void SetPaintMaterialModePin( const NDb::PaintMaterialModePin value ) { };
  virtual void SetPassivePin( const NDb::BooleanPin value ) { };
  virtual void SetPressedPin( const NDb::BooleanPin value ) { };
  virtual void SetR2VBPin( const NDb::BooleanPin value ) { };
  virtual void SetScale9Grid( const NDb::BooleanPin value ) { };
  virtual void SetScale9GridBitmap( const NDb::BooleanPin value ) { };
  virtual void SetShaderForLines( const NDb::BooleanPin value ) { };
  virtual void SetShadowCasterPin( const NDb::BooleanPin value ) { };
  virtual void SetSharpPin( const NDb::BooleanPin value ) { };
  virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { };
  virtual void SetSpecialTransparency( bool on ) { };
  virtual void SetStripes( const NDb::BooleanPin value ) { };
  virtual void SetTerrainUVSetPin( const NDb::TerrainUVSetPin value ) { };
  virtual void SetTextureCountPin( const NDb::TextureCountPin value ) { };
  virtual void SetTextureFitPinValue( const NDb::BooleanPin value ) { };
  virtual void SetTraceTexturePin( const NDb::BooleanPin value ) { };
  virtual void SetUseColorFilter( const NDb::BooleanPin value ) { };
  virtual void SetUseDiffuse( const NDb::BooleanPin value ) { };
  virtual void SetUseDiffuse2( const NDb::BooleanPin value ) { };
  virtual void SetUseDiffusePin( const NDb::BooleanPin value ) { };
  virtual void SetWaitForActivationPin( const NDb::BooleanPin value ) { };
  virtual void SetWarFogPin( const NDb::BooleanPin value ) { };
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AIGeometryMaterialType : public BaseMaterial
{
private:
  AIGeometryMaterialType() : BaseMaterial( NDb::AIGeometryMaterialType::priority, NDb::AIGeometryMaterialType::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(AIGeometryMaterialType::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	NDb::Ptr<NDb::AIGeometryMaterialType> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::AIGeometryMaterialType* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( AIGeometryMaterialType, renderState ) - offsetof( AIGeometryMaterialType, renderState ) + sizeof( renderState ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::AIGeometryMaterialType* dbMaterial = static_cast<const NDb::AIGeometryMaterialType*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::AIGeometryMaterialType dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::AIGeometryMaterialType::typeId, };
	static Render::Material* CreateMaterial() { return new AIGeometryMaterialType(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AOEMaterial : public BaseMaterial
{
private:
  AOEMaterial() : BaseMaterial( NDb::AOEMaterial::priority, NDb::AOEMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(AOEMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::HDRColor primaryColor;
	Render::HDRColor secondaryColor;
	float aspectRatio;
	NDb::BooleanPin CustomizedGeometryPinValue;
	NDb::Ptr<NDb::AOEMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * CustomizedGeometryPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::AOEMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		primaryColor = pDbMaterial->primaryColor;
		secondaryColor = pDbMaterial->secondaryColor;
		aspectRatio = pDbMaterial->aspectRatio;
		CustomizedGeometryPinValue = pDbMaterial->CustomizedGeometryPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( AOEMaterial, renderState ) + sizeof( renderState ) == offsetof( AOEMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( AOEMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( AOEMaterial, primaryColor ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( AOEMaterial, primaryColor ) + sizeof( primaryColor ) == offsetof( AOEMaterial, secondaryColor ), Found_gap_after_significant_field_primaryColor );
	  NI_STATIC_ASSERT( offsetof( AOEMaterial, secondaryColor ) + sizeof( secondaryColor ) == offsetof( AOEMaterial, aspectRatio ), Found_gap_after_significant_field_secondaryColor );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "CommonMaterialFunc.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( AOEMaterial, aspectRatio ) - offsetof( AOEMaterial, renderState ) + sizeof( aspectRatio ); }

public:
	virtual const NDb::BooleanPin GetCustomizedGeometryPin() const { return CustomizedGeometryPinValue; }
	virtual void SetCustomizedGeometryPin( const NDb::BooleanPin value ) { CustomizedGeometryPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::AOEMaterial* dbMaterial = static_cast<const NDb::AOEMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::AOEMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( AOEMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::AOEMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new AOEMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicFXMaterial : public BaseMaterial
{
private:
  BasicFXMaterial() : BaseMaterial( NDb::BasicFXMaterial::priority, NDb::BasicFXMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(BasicFXMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::HDRColor DiffuseMul;
	Render::HDRColor DiffuseAdd;
	float emissive;
	float distortion;
	float masterOpacity;
	int isBlendModeOverrided;
	float opacity;
	float uOffset;
	float vOffset;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseMulWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseAddWrapper;;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	NDb::BooleanPin MultiplyVertexColorPinValue;
	NDb::DistortionPin DistortionPinValue;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > opacityWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffsetWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffsetWrapper;;
	NDb::Ptr<NDb::BasicFXMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 3 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * DistortionPinValue + 6 * MultiplyVertexColorPinValue + 12 * OpacityAndEmissiveModePinValue + 48 * SkeletalMeshPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::BasicFXMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		DiffuseMul = pDbMaterial->DiffuseMul;
		DiffuseMulWrapper.Init( &DiffuseMul, pDbMaterial->DiffuseMul, 0.0f );
		DiffuseAdd = pDbMaterial->DiffuseAdd;
		DiffuseAddWrapper.Init( &DiffuseAdd, pDbMaterial->DiffuseAdd, 0.0f );
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		OpacityAndEmissiveModePinValue = pDbMaterial->OpacityAndEmissiveModePinValue;
		MultiplyVertexColorPinValue = pDbMaterial->MultiplyVertexColorPinValue;
		DistortionPinValue = pDbMaterial->DistortionPinValue;
		emissive = pDbMaterial->emissive;
		distortion = pDbMaterial->distortion;
		masterOpacity = pDbMaterial->masterOpacity;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		opacity = pDbMaterial->opacity;
		opacityWrapper.Init( &opacity, pDbMaterial->opacity, 0.0f );
		uOffset = pDbMaterial->uOffset;
		uOffsetWrapper.Init( &uOffset, pDbMaterial->uOffset, 0.0f );
		vOffset = pDbMaterial->vOffset;
		vOffsetWrapper.Init( &vOffset, pDbMaterial->vOffset, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, renderState ) + sizeof( renderState ) == offsetof( BasicFXMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( BasicFXMaterial, DiffuseMul ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, DiffuseMul ) + sizeof( DiffuseMul ) == offsetof( BasicFXMaterial, DiffuseAdd ), Found_gap_after_significant_field_DiffuseMul );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, DiffuseAdd ) + sizeof( DiffuseAdd ) == offsetof( BasicFXMaterial, emissive ), Found_gap_after_significant_field_DiffuseAdd );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, emissive ) + sizeof( emissive ) == offsetof( BasicFXMaterial, distortion ), Found_gap_after_significant_field_emissive );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, distortion ) + sizeof( distortion ) == offsetof( BasicFXMaterial, masterOpacity ), Found_gap_after_significant_field_distortion );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, masterOpacity ) + sizeof( masterOpacity ) == offsetof( BasicFXMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_masterOpacity );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, isBlendModeOverrided ) + sizeof( isBlendModeOverrided ) == offsetof( BasicFXMaterial, opacity ), Found_gap_after_significant_field_isBlendModeOverrided );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, opacity ) + sizeof( opacity ) == offsetof( BasicFXMaterial, uOffset ), Found_gap_after_significant_field_opacity );
	  NI_STATIC_ASSERT( offsetof( BasicFXMaterial, uOffset ) + sizeof( uOffset ) == offsetof( BasicFXMaterial, vOffset ), Found_gap_after_significant_field_uOffset );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "BasicFXMaterial.inl"
protected:
	virtual bool IsAnimated() const
	{
		return DiffuseMulWrapper.IsAnimated()
			|| DiffuseAddWrapper.IsAnimated()
			|| opacityWrapper.IsAnimated()
			|| uOffsetWrapper.IsAnimated()
			|| vOffsetWrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( BasicFXMaterial, vOffset ) - offsetof( BasicFXMaterial, renderState ) + sizeof( vOffset ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( DiffuseMulWrapper.IsAnimated() && DiffuseMulWrapper.GetLength() > length )
  		length = DiffuseMulWrapper.GetLength();
  	if ( DiffuseAddWrapper.IsAnimated() && DiffuseAddWrapper.GetLength() > length )
  		length = DiffuseAddWrapper.GetLength();
  	if ( opacityWrapper.IsAnimated() && opacityWrapper.GetLength() > length )
  		length = opacityWrapper.GetLength();
  	if ( uOffsetWrapper.IsAnimated() && uOffsetWrapper.GetLength() > length )
  		length = uOffsetWrapper.GetLength();
  	if ( vOffsetWrapper.IsAnimated() && vOffsetWrapper.GetLength() > length )
  		length = vOffsetWrapper.GetLength();
  	return length;
  }
  
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetMultiplyVertexColorPin() const { return MultiplyVertexColorPinValue; }
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetMultiplyVertexColorPin( const NDb::BooleanPin value ) { MultiplyVertexColorPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::BasicFXMaterial* dbMaterial = static_cast<const NDb::BasicFXMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::BasicFXMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( BasicFXMaterial, DiffuseMap );
  }
	
	virtual void Update( float dt )
	{
		if( !BasicFXMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		DiffuseMulWrapper.Step( dt );
		DiffuseAddWrapper.Step( dt );
		opacityWrapper.Step( dt );
		uOffsetWrapper.Step( dt );
		vOffsetWrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		DiffuseMulWrapper.SetStartTime( startTime );
		DiffuseAddWrapper.SetStartTime( startTime );
		opacityWrapper.SetStartTime( startTime );
		uOffsetWrapper.SetStartTime( startTime );
		vOffsetWrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::BasicFXMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new BasicFXMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicMaskMaterial : public BaseMaterial
{
private:
  BasicMaskMaterial() : BaseMaterial( NDb::BasicMaskMaterial::priority, NDb::BasicMaskMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(BasicMaskMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler Diffuse;
	Render::Sampler Mask;
	float opacity;
	int isBlendModeOverrided;
	NDb::Ptr<NDb::BasicMaskMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::BasicMaskMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->Diffuse, &Diffuse, false, texturePoolId );
		FillSampler( pDbMaterial->Mask, &Mask, false, texturePoolId );
		opacity = pDbMaterial->opacity;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( BasicMaskMaterial, renderState ) + sizeof( renderState ) == offsetof( BasicMaskMaterial, Diffuse ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( BasicMaskMaterial, Diffuse ) + sizeof( Diffuse ) == offsetof( BasicMaskMaterial, Mask ), Found_gap_after_significant_field_Diffuse );
	  NI_STATIC_ASSERT( offsetof( BasicMaskMaterial, Mask ) + sizeof( Mask ) == offsetof( BasicMaskMaterial, opacity ), Found_gap_after_significant_field_Mask );
	  NI_STATIC_ASSERT( offsetof( BasicMaskMaterial, opacity ) + sizeof( opacity ) == offsetof( BasicMaskMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_opacity );
	}

  static int samplersOffsets[2];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 2 );
  }

	#include "EaselPaintMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( BasicMaskMaterial, isBlendModeOverrided ) - offsetof( BasicMaskMaterial, renderState ) + sizeof( isBlendModeOverrided ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::BasicMaskMaterial* dbMaterial = static_cast<const NDb::BasicMaskMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::BasicMaskMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, Diffuse );
		Render::BindSampler( 3, Mask );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( BasicMaskMaterial, Diffuse );
    samplersOffsets[1] = offsetof( BasicMaskMaterial, Mask );
  }
	
	enum { typeId = NDb::BasicMaskMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new BasicMaskMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicMaterial : public BaseMaterial
{
private:
  BasicMaterial() : BaseMaterial( NDb::BasicMaterial::priority, NDb::BasicMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(BasicMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::Sampler NormalMap;
	Render::Sampler SpecularMap;
	Render::Sampler ReflectionMap;
	int isBlendModeOverrided;
	Render::HDRColor diffuseColor;
	float lightingIntencity;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	float emissive;
	float opacity;
	float reflectivity;
	float specularPower;
	bool specialTransparency;
	NDb::BooleanPin NormalMapPinValue;
	NDb::BooleanPin SpecularMapPinValue;
	NDb::ReflectivityPin ReflectivityPinValue;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::EEmissivePin EmissivePinValue;
	NDb::BooleanPin OpacityPinValue;
	NDb::BooleanPin SpecularPinValue;
	NDb::LightingPin LightingPinValue;
	NDb::Ptr<NDb::BasicMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue + 6 * GetRuntimePins().InstancingValue + 1536 * GetRuntimePins().RenderModeValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * EmissivePinValue + 12 * LightingPinValue + 96 * NormalMapPinValue + 192 * OpacityPinValue + 384 * ReflectivityPinValue + 4608 * SkeletalMeshPinValue + 9216 * SpecularMapPinValue + 18432 * SpecularPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::BasicMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		diffuseColor = pDbMaterial->diffuseColor;
		lightingIntencity = pDbMaterial->lightingIntencity;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		FillSampler( pDbMaterial->NormalMap, &NormalMap, true, texturePoolId );
		NormalMapPinValue = pDbMaterial->NormalMapPinValue;
		FillSampler( pDbMaterial->SpecularMap, &SpecularMap, true, texturePoolId );
		SpecularMapPinValue = pDbMaterial->SpecularMapPinValue;
		FillSampler( pDbMaterial->ReflectionMap, &ReflectionMap, true, texturePoolId );
		ReflectivityPinValue = pDbMaterial->ReflectivityPinValue;
		outputMul = pDbMaterial->outputMul;
		outputAdd = pDbMaterial->outputAdd;
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		EmissivePinValue = pDbMaterial->EmissivePinValue;
		OpacityPinValue = pDbMaterial->OpacityPinValue;
		SpecularPinValue = pDbMaterial->SpecularPinValue;
		LightingPinValue = pDbMaterial->LightingPinValue;
		emissive = pDbMaterial->emissive;
		opacity = pDbMaterial->opacity;
		reflectivity = pDbMaterial->reflectivity;
		specularPower = pDbMaterial->specularPower;
		specialTransparency = pDbMaterial->specialTransparency;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, renderState ) + sizeof( renderState ) == offsetof( BasicMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( BasicMaterial, NormalMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, NormalMap ) + sizeof( NormalMap ) == offsetof( BasicMaterial, SpecularMap ), Found_gap_after_significant_field_NormalMap );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, SpecularMap ) + sizeof( SpecularMap ) == offsetof( BasicMaterial, ReflectionMap ), Found_gap_after_significant_field_SpecularMap );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, ReflectionMap ) + sizeof( ReflectionMap ) == offsetof( BasicMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_ReflectionMap );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, isBlendModeOverrided ) + sizeof( isBlendModeOverrided ) == offsetof( BasicMaterial, diffuseColor ), Found_gap_after_significant_field_isBlendModeOverrided );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, diffuseColor ) + sizeof( diffuseColor ) == offsetof( BasicMaterial, lightingIntencity ), Found_gap_after_significant_field_diffuseColor );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, lightingIntencity ) + sizeof( lightingIntencity ) == offsetof( BasicMaterial, outputMul ), Found_gap_after_significant_field_lightingIntencity );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, outputMul ) + sizeof( outputMul ) == offsetof( BasicMaterial, outputAdd ), Found_gap_after_significant_field_outputMul );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, outputAdd ) + sizeof( outputAdd ) == offsetof( BasicMaterial, emissive ), Found_gap_after_significant_field_outputAdd );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, emissive ) + sizeof( emissive ) == offsetof( BasicMaterial, opacity ), Found_gap_after_significant_field_emissive );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, opacity ) + sizeof( opacity ) == offsetof( BasicMaterial, reflectivity ), Found_gap_after_significant_field_opacity );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, reflectivity ) + sizeof( reflectivity ) == offsetof( BasicMaterial, specularPower ), Found_gap_after_significant_field_reflectivity );
	  NI_STATIC_ASSERT( offsetof( BasicMaterial, specularPower ) + sizeof( specularPower ) == offsetof( BasicMaterial, specialTransparency ), Found_gap_after_significant_field_specularPower );
	}

  static int samplersOffsets[4];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 4 );
  }

	#include "BasicMaterialWithBatch.inl"
	#include "SpecialTransparency.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( BasicMaterial, specialTransparency ) - offsetof( BasicMaterial, renderState ) + sizeof( specialTransparency ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::LightingPin GetLightingPin() const { return LightingPinValue; }
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetLightingPin( const NDb::LightingPin value ) { LightingPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::BasicMaterial* dbMaterial = static_cast<const NDb::BasicMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::BasicMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
		Render::BindSampler( 1, NormalMap );
		Render::BindSampler( 2, SpecularMap );
		Render::BindSampler( 3, ReflectionMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( BasicMaterial, DiffuseMap );
    samplersOffsets[1] = offsetof( BasicMaterial, NormalMap );
    samplersOffsets[2] = offsetof( BasicMaterial, SpecularMap );
    samplersOffsets[3] = offsetof( BasicMaterial, ReflectionMap );
  }
	
	enum { typeId = NDb::BasicMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new BasicMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DebugMaterial : public BaseMaterial
{
private:
  DebugMaterial() : BaseMaterial( NDb::DebugMaterial::priority, NDb::DebugMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(DebugMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::BooleanPin DarkMapPinValue;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::DebugPin DebugPinValue;
	NDb::Ptr<NDb::DebugMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 6 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * DarkMapPinValue + 2 * DebugPinValue + 12 * SkeletalMeshPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::DebugMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		DarkMapPinValue = pDbMaterial->DarkMapPinValue;
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		DebugPinValue = pDbMaterial->DebugPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::DebugMaterial* dbMaterial = static_cast<const NDb::DebugMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::DebugMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::DebugMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new DebugMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DecalMaterial : public BaseMaterial
{
private:
  DecalMaterial() : BaseMaterial( NDb::DecalMaterial::priority, NDb::DecalMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(DecalMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::HDRColor DiffuseMul;
	Render::HDRColor DiffuseAdd;
	float radius;
	float distortion;
	int isBlendModeOverrided;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseMulWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseAddWrapper;;
	NDb::BooleanPin AccessibilityPinValue;
	NDb::OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	NDb::BooleanPin DistortionPinValue;
	NDb::BooleanPin DecalPlanePinValue;
	bool putOnWater;
	float masterOpacity;
	float opacity;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > opacityWrapper;;
	NDb::Ptr<NDb::DecalMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DecalModeValue + 24 * GetRuntimePins().DoDepthOutValue + 48 * GetRuntimePins().InstancingValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * AccessibilityPinValue + 6 * DecalPlanePinValue + 12 * DistortionPinValue + 96 * OpacityAndEmissiveModePinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::DecalMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		DiffuseMul = pDbMaterial->DiffuseMul;
		DiffuseMulWrapper.Init( &DiffuseMul, pDbMaterial->DiffuseMul, 0.0f );
		DiffuseAdd = pDbMaterial->DiffuseAdd;
		DiffuseAddWrapper.Init( &DiffuseAdd, pDbMaterial->DiffuseAdd, 0.0f );
		radius = pDbMaterial->radius;
		AccessibilityPinValue = pDbMaterial->AccessibilityPinValue;
		OpacityAndEmissiveModePinValue = pDbMaterial->OpacityAndEmissiveModePinValue;
		DistortionPinValue = pDbMaterial->DistortionPinValue;
		DecalPlanePinValue = pDbMaterial->DecalPlanePinValue;
		distortion = pDbMaterial->distortion;
		putOnWater = pDbMaterial->putOnWater;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		masterOpacity = pDbMaterial->masterOpacity;
		opacity = pDbMaterial->opacity;
		opacityWrapper.Init( &opacity, pDbMaterial->opacity, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, renderState ) + sizeof( renderState ) == offsetof( DecalMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( DecalMaterial, DiffuseMul ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, DiffuseMul ) + sizeof( DiffuseMul ) == offsetof( DecalMaterial, DiffuseAdd ), Found_gap_after_significant_field_DiffuseMul );
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, DiffuseAdd ) + sizeof( DiffuseAdd ) == offsetof( DecalMaterial, radius ), Found_gap_after_significant_field_DiffuseAdd );
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, radius ) + sizeof( radius ) == offsetof( DecalMaterial, distortion ), Found_gap_after_significant_field_radius );
	  NI_STATIC_ASSERT( offsetof( DecalMaterial, distortion ) + sizeof( distortion ) == offsetof( DecalMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_distortion );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "BasicMaterial.inl"
protected:
	virtual bool IsAnimated() const
	{
		return DiffuseMulWrapper.IsAnimated()
			|| DiffuseAddWrapper.IsAnimated()
			|| opacityWrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( DecalMaterial, isBlendModeOverrided ) - offsetof( DecalMaterial, renderState ) + sizeof( isBlendModeOverrided ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( DiffuseMulWrapper.IsAnimated() && DiffuseMulWrapper.GetLength() > length )
  		length = DiffuseMulWrapper.GetLength();
  	if ( DiffuseAddWrapper.IsAnimated() && DiffuseAddWrapper.GetLength() > length )
  		length = DiffuseAddWrapper.GetLength();
  	if ( opacityWrapper.IsAnimated() && opacityWrapper.GetLength() > length )
  		length = opacityWrapper.GetLength();
  	return length;
  }
  
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::DecalMaterial* dbMaterial = static_cast<const NDb::DecalMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::DecalMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( DecalMaterial, DiffuseMap );
  }
	
	virtual void Update( float dt )
	{
		if( !DecalMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		DiffuseMulWrapper.Step( dt );
		DiffuseAddWrapper.Step( dt );
		opacityWrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		DiffuseMulWrapper.SetStartTime( startTime );
		DiffuseAddWrapper.SetStartTime( startTime );
		opacityWrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::DecalMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new DecalMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DecalTerrainMaterial : public BaseMaterial
{
private:
  DecalTerrainMaterial() : BaseMaterial( NDb::DecalTerrainMaterial::priority, NDb::DecalTerrainMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(DecalTerrainMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::Sampler MaskMap;
	Render::HDRColor DiffuseMul;
	Render::HDRColor DiffuseAdd;
	float radius;
	float distortion;
	int isBlendModeOverrided;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseMulWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> > DiffuseAddWrapper;;
	NDb::BooleanPin AccessibilityPinValue;
	NDb::OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	NDb::BooleanPin DistortionPinValue;
	NDb::BooleanPin DecalPlanePinValue;
	bool putOnWater;
	float masterOpacity;
	float opacity;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > opacityWrapper;;
	NDb::Ptr<NDb::DecalTerrainMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DecalModeValue + 24 * GetRuntimePins().DoDepthOutValue + 48 * GetRuntimePins().InstancingValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * AccessibilityPinValue + 6 * DecalPlanePinValue + 12 * DistortionPinValue + 96 * OpacityAndEmissiveModePinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::DecalTerrainMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->MaskMap, &MaskMap, false, texturePoolId );
		DiffuseMul = pDbMaterial->DiffuseMul;
		DiffuseMulWrapper.Init( &DiffuseMul, pDbMaterial->DiffuseMul, 0.0f );
		DiffuseAdd = pDbMaterial->DiffuseAdd;
		DiffuseAddWrapper.Init( &DiffuseAdd, pDbMaterial->DiffuseAdd, 0.0f );
		radius = pDbMaterial->radius;
		AccessibilityPinValue = pDbMaterial->AccessibilityPinValue;
		OpacityAndEmissiveModePinValue = pDbMaterial->OpacityAndEmissiveModePinValue;
		DistortionPinValue = pDbMaterial->DistortionPinValue;
		DecalPlanePinValue = pDbMaterial->DecalPlanePinValue;
		distortion = pDbMaterial->distortion;
		putOnWater = pDbMaterial->putOnWater;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		masterOpacity = pDbMaterial->masterOpacity;
		opacity = pDbMaterial->opacity;
		opacityWrapper.Init( &opacity, pDbMaterial->opacity, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, renderState ) + sizeof( renderState ) == offsetof( DecalTerrainMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( DecalTerrainMaterial, MaskMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, MaskMap ) + sizeof( MaskMap ) == offsetof( DecalTerrainMaterial, DiffuseMul ), Found_gap_after_significant_field_MaskMap );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, DiffuseMul ) + sizeof( DiffuseMul ) == offsetof( DecalTerrainMaterial, DiffuseAdd ), Found_gap_after_significant_field_DiffuseMul );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, DiffuseAdd ) + sizeof( DiffuseAdd ) == offsetof( DecalTerrainMaterial, radius ), Found_gap_after_significant_field_DiffuseAdd );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, radius ) + sizeof( radius ) == offsetof( DecalTerrainMaterial, distortion ), Found_gap_after_significant_field_radius );
	  NI_STATIC_ASSERT( offsetof( DecalTerrainMaterial, distortion ) + sizeof( distortion ) == offsetof( DecalTerrainMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_distortion );
	}

  static int samplersOffsets[2];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 2 );
  }

	#include "BasicMaterial.inl"
protected:
	virtual bool IsAnimated() const
	{
		return DiffuseMulWrapper.IsAnimated()
			|| DiffuseAddWrapper.IsAnimated()
			|| opacityWrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( DecalTerrainMaterial, isBlendModeOverrided ) - offsetof( DecalTerrainMaterial, renderState ) + sizeof( isBlendModeOverrided ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( DiffuseMulWrapper.IsAnimated() && DiffuseMulWrapper.GetLength() > length )
  		length = DiffuseMulWrapper.GetLength();
  	if ( DiffuseAddWrapper.IsAnimated() && DiffuseAddWrapper.GetLength() > length )
  		length = DiffuseAddWrapper.GetLength();
  	if ( opacityWrapper.IsAnimated() && opacityWrapper.GetLength() > length )
  		length = opacityWrapper.GetLength();
  	return length;
  }
  
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::DecalTerrainMaterial* dbMaterial = static_cast<const NDb::DecalTerrainMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::DecalTerrainMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
		Render::BindSampler( 1, MaskMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( DecalTerrainMaterial, DiffuseMap );
    samplersOffsets[1] = offsetof( DecalTerrainMaterial, MaskMap );
  }
	
	virtual void Update( float dt )
	{
		if( !DecalTerrainMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		DiffuseMulWrapper.Step( dt );
		DiffuseAddWrapper.Step( dt );
		opacityWrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		DiffuseMulWrapper.SetStartTime( startTime );
		DiffuseAddWrapper.SetStartTime( startTime );
		opacityWrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::DecalTerrainMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new DecalTerrainMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DropMaterial : public BaseMaterial
{
private:
  DropMaterial() : BaseMaterial( NDb::DropMaterial::priority, NDb::DropMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(DropMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::Sampler NormalMap;
	Render::Sampler SpecularMap;
	Render::Sampler ReflectionMap;
	Render::HDRColor diffuseColor;
	float lightingIntencity;
	float ambientIntensity;
	Render::HDRColor additionalAmbient;
	Render::HDRColor reflectionMapColor0;
	Render::HDRColor reflectionMapColor1;
	Render::HDRColor reflectionMapColor2;
	Render::HDRColor reflectionMapColor3;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	int isBlendModeOverrided;
	float emissive;
	float opacity;
	float reflectivityLerp;
	float reflectivityAdd;
	float reflectivityMul;
	float specularPower;
	float uOffset1;
	float vOffset1;
	float uOffset2;
	float vOffset2;
	NDb::BooleanPin NormalMapPinValue;
	NDb::BooleanPin SpecularMapPinValue;
	NDb::ReflectivityPin ReflectivityPinValue;
	NDb::TextureColorizePin colorizeReflectionMap;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::LightModePin LightModePinValue;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > opacityWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffset1Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffset1Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffset2Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffset2Wrapper;;
	NDb::Ptr<NDb::DropMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 5 * GetRuntimePins().DoDepthOutValue + 560 * GetRuntimePins().RenderModeValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * colorizeReflectionMap + 10 * LightModePinValue + 70 * NormalMapPinValue + 140 * ReflectivityPinValue + 1680 * SkeletalMeshPinValue + 3360 * SpecularMapPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::DropMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		diffuseColor = pDbMaterial->diffuseColor;
		lightingIntencity = pDbMaterial->lightingIntencity;
		ambientIntensity = pDbMaterial->ambientIntensity;
		additionalAmbient = pDbMaterial->additionalAmbient;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		FillSampler( pDbMaterial->NormalMap, &NormalMap, true, texturePoolId );
		NormalMapPinValue = pDbMaterial->NormalMapPinValue;
		FillSampler( pDbMaterial->SpecularMap, &SpecularMap, true, texturePoolId );
		SpecularMapPinValue = pDbMaterial->SpecularMapPinValue;
		FillSampler( pDbMaterial->ReflectionMap, &ReflectionMap, true, texturePoolId );
		ReflectivityPinValue = pDbMaterial->ReflectivityPinValue;
		colorizeReflectionMap = pDbMaterial->colorizeReflectionMap;
		reflectionMapColor0 = pDbMaterial->reflectionMapColor0;
		reflectionMapColor1 = pDbMaterial->reflectionMapColor1;
		reflectionMapColor2 = pDbMaterial->reflectionMapColor2;
		reflectionMapColor3 = pDbMaterial->reflectionMapColor3;
		outputMul = pDbMaterial->outputMul;
		outputAdd = pDbMaterial->outputAdd;
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		LightModePinValue = pDbMaterial->LightModePinValue;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		emissive = pDbMaterial->emissive;
		opacity = pDbMaterial->opacity;
		opacityWrapper.Init( &opacity, pDbMaterial->opacity, 0.0f );
		reflectivityLerp = pDbMaterial->reflectivityLerp;
		reflectivityAdd = pDbMaterial->reflectivityAdd;
		reflectivityMul = pDbMaterial->reflectivityMul;
		specularPower = pDbMaterial->specularPower;
		uOffset1 = pDbMaterial->uOffset1;
		uOffset1Wrapper.Init( &uOffset1, pDbMaterial->uOffset1, 0.0f );
		vOffset1 = pDbMaterial->vOffset1;
		vOffset1Wrapper.Init( &vOffset1, pDbMaterial->vOffset1, 0.0f );
		uOffset2 = pDbMaterial->uOffset2;
		uOffset2Wrapper.Init( &uOffset2, pDbMaterial->uOffset2, 0.0f );
		vOffset2 = pDbMaterial->vOffset2;
		vOffset2Wrapper.Init( &vOffset2, pDbMaterial->vOffset2, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( DropMaterial, renderState ) + sizeof( renderState ) == offsetof( DropMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( DropMaterial, NormalMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, NormalMap ) + sizeof( NormalMap ) == offsetof( DropMaterial, SpecularMap ), Found_gap_after_significant_field_NormalMap );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, SpecularMap ) + sizeof( SpecularMap ) == offsetof( DropMaterial, ReflectionMap ), Found_gap_after_significant_field_SpecularMap );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, ReflectionMap ) + sizeof( ReflectionMap ) == offsetof( DropMaterial, diffuseColor ), Found_gap_after_significant_field_ReflectionMap );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, diffuseColor ) + sizeof( diffuseColor ) == offsetof( DropMaterial, lightingIntencity ), Found_gap_after_significant_field_diffuseColor );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, lightingIntencity ) + sizeof( lightingIntencity ) == offsetof( DropMaterial, ambientIntensity ), Found_gap_after_significant_field_lightingIntencity );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, ambientIntensity ) + sizeof( ambientIntensity ) == offsetof( DropMaterial, additionalAmbient ), Found_gap_after_significant_field_ambientIntensity );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, additionalAmbient ) + sizeof( additionalAmbient ) == offsetof( DropMaterial, reflectionMapColor0 ), Found_gap_after_significant_field_additionalAmbient );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectionMapColor0 ) + sizeof( reflectionMapColor0 ) == offsetof( DropMaterial, reflectionMapColor1 ), Found_gap_after_significant_field_reflectionMapColor0 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectionMapColor1 ) + sizeof( reflectionMapColor1 ) == offsetof( DropMaterial, reflectionMapColor2 ), Found_gap_after_significant_field_reflectionMapColor1 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectionMapColor2 ) + sizeof( reflectionMapColor2 ) == offsetof( DropMaterial, reflectionMapColor3 ), Found_gap_after_significant_field_reflectionMapColor2 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectionMapColor3 ) + sizeof( reflectionMapColor3 ) == offsetof( DropMaterial, outputMul ), Found_gap_after_significant_field_reflectionMapColor3 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, outputMul ) + sizeof( outputMul ) == offsetof( DropMaterial, outputAdd ), Found_gap_after_significant_field_outputMul );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, outputAdd ) + sizeof( outputAdd ) == offsetof( DropMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_outputAdd );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, isBlendModeOverrided ) + sizeof( isBlendModeOverrided ) == offsetof( DropMaterial, emissive ), Found_gap_after_significant_field_isBlendModeOverrided );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, emissive ) + sizeof( emissive ) == offsetof( DropMaterial, opacity ), Found_gap_after_significant_field_emissive );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, opacity ) + sizeof( opacity ) == offsetof( DropMaterial, reflectivityLerp ), Found_gap_after_significant_field_opacity );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectivityLerp ) + sizeof( reflectivityLerp ) == offsetof( DropMaterial, reflectivityAdd ), Found_gap_after_significant_field_reflectivityLerp );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectivityAdd ) + sizeof( reflectivityAdd ) == offsetof( DropMaterial, reflectivityMul ), Found_gap_after_significant_field_reflectivityAdd );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, reflectivityMul ) + sizeof( reflectivityMul ) == offsetof( DropMaterial, specularPower ), Found_gap_after_significant_field_reflectivityMul );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, specularPower ) + sizeof( specularPower ) == offsetof( DropMaterial, uOffset1 ), Found_gap_after_significant_field_specularPower );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, uOffset1 ) + sizeof( uOffset1 ) == offsetof( DropMaterial, vOffset1 ), Found_gap_after_significant_field_uOffset1 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, vOffset1 ) + sizeof( vOffset1 ) == offsetof( DropMaterial, uOffset2 ), Found_gap_after_significant_field_vOffset1 );
	  NI_STATIC_ASSERT( offsetof( DropMaterial, uOffset2 ) + sizeof( uOffset2 ) == offsetof( DropMaterial, vOffset2 ), Found_gap_after_significant_field_uOffset2 );
	}

  static int samplersOffsets[4];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 4 );
  }

	#include "DropMaterial.inl"
protected:
	virtual bool IsAnimated() const
	{
		return opacityWrapper.IsAnimated()
			|| uOffset1Wrapper.IsAnimated()
			|| vOffset1Wrapper.IsAnimated()
			|| uOffset2Wrapper.IsAnimated()
			|| vOffset2Wrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( DropMaterial, vOffset2 ) - offsetof( DropMaterial, renderState ) + sizeof( vOffset2 ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( opacityWrapper.IsAnimated() && opacityWrapper.GetLength() > length )
  		length = opacityWrapper.GetLength();
  	if ( uOffset1Wrapper.IsAnimated() && uOffset1Wrapper.GetLength() > length )
  		length = uOffset1Wrapper.GetLength();
  	if ( vOffset1Wrapper.IsAnimated() && vOffset1Wrapper.GetLength() > length )
  		length = vOffset1Wrapper.GetLength();
  	if ( uOffset2Wrapper.IsAnimated() && uOffset2Wrapper.GetLength() > length )
  		length = uOffset2Wrapper.GetLength();
  	if ( vOffset2Wrapper.IsAnimated() && vOffset2Wrapper.GetLength() > length )
  		length = vOffset2Wrapper.GetLength();
  	return length;
  }
  
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::DropMaterial* dbMaterial = static_cast<const NDb::DropMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::DropMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
		Render::BindSampler( 1, NormalMap );
		Render::BindSampler( 2, SpecularMap );
		Render::BindSampler( 3, ReflectionMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( DropMaterial, DiffuseMap );
    samplersOffsets[1] = offsetof( DropMaterial, NormalMap );
    samplersOffsets[2] = offsetof( DropMaterial, SpecularMap );
    samplersOffsets[3] = offsetof( DropMaterial, ReflectionMap );
  }
	
	virtual void Update( float dt )
	{
		if( !DropMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		opacityWrapper.Step( dt );
		uOffset1Wrapper.Step( dt );
		vOffset1Wrapper.Step( dt );
		uOffset2Wrapper.Step( dt );
		vOffset2Wrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		opacityWrapper.SetStartTime( startTime );
		uOffset1Wrapper.SetStartTime( startTime );
		vOffset1Wrapper.SetStartTime( startTime );
		uOffset2Wrapper.SetStartTime( startTime );
		vOffset2Wrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::DropMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new DropMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FullScreenMaterial : public BaseMaterial
{
private:
  FullScreenMaterial() : BaseMaterial( NDb::FullScreenMaterial::priority, NDb::FullScreenMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(FullScreenMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DepthMap;
	Render::Sampler DiffuseMap;
	Render::Sampler BloomMap;
	NDb::BooleanPin SharpPinValue;
	NDb::BooleanPin BloomPinValue;
	NDb::BooleanPin WarFogPinValue;
	NDb::BooleanPin R2VBPinValue;
	NDb::ColorCorrectPin ColorCorrectPinValue;
	NDb::Ptr<NDb::FullScreenMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 8 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * BloomPinValue + 2 * ColorCorrectPinValue + 16 * R2VBPinValue + 32 * SharpPinValue + 64 * WarFogPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::FullScreenMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DepthMap, &DepthMap, false, texturePoolId );
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->BloomMap, &BloomMap, false, texturePoolId );
		SharpPinValue = pDbMaterial->SharpPinValue;
		BloomPinValue = pDbMaterial->BloomPinValue;
		WarFogPinValue = pDbMaterial->WarFogPinValue;
		R2VBPinValue = pDbMaterial->R2VBPinValue;
		ColorCorrectPinValue = pDbMaterial->ColorCorrectPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( FullScreenMaterial, renderState ) + sizeof( renderState ) == offsetof( FullScreenMaterial, DepthMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( FullScreenMaterial, DepthMap ) + sizeof( DepthMap ) == offsetof( FullScreenMaterial, DiffuseMap ), Found_gap_after_significant_field_DepthMap );
	  NI_STATIC_ASSERT( offsetof( FullScreenMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( FullScreenMaterial, BloomMap ), Found_gap_after_significant_field_DiffuseMap );
	}

  static int samplersOffsets[3];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 3 );
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( FullScreenMaterial, BloomMap ) - offsetof( FullScreenMaterial, renderState ) + sizeof( BloomMap ); }

public:
	virtual const Render::Sampler* GetBloomMap() const { return &BloomMap; }
	virtual Render::Sampler* GetBloomMap() { return &BloomMap; }
	virtual const NDb::BooleanPin GetBloomPin() const { return BloomPinValue; }
	virtual const NDb::ColorCorrectPin GetColorCorrectPin() const { return ColorCorrectPinValue; }
	virtual const Render::Sampler* GetDepthMap() const { return &DepthMap; }
	virtual Render::Sampler* GetDepthMap() { return &DepthMap; }
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetR2VBPin() const { return R2VBPinValue; }
	virtual const NDb::BooleanPin GetSharpPin() const { return SharpPinValue; }
	virtual const NDb::BooleanPin GetWarFogPin() const { return WarFogPinValue; }
	virtual void SetBloomPin( const NDb::BooleanPin value ) { BloomPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetColorCorrectPin( const NDb::ColorCorrectPin value ) { ColorCorrectPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetR2VBPin( const NDb::BooleanPin value ) { R2VBPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetSharpPin( const NDb::BooleanPin value ) { SharpPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetWarFogPin( const NDb::BooleanPin value ) { WarFogPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::FullScreenMaterial* dbMaterial = static_cast<const NDb::FullScreenMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::FullScreenMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DepthMap );
		Render::BindSampler( 1, DiffuseMap );
		Render::BindSampler( 2, BloomMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( FullScreenMaterial, DepthMap );
    samplersOffsets[1] = offsetof( FullScreenMaterial, DiffuseMap );
    samplersOffsets[2] = offsetof( FullScreenMaterial, BloomMap );
  }
	
	enum { typeId = NDb::FullScreenMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new FullScreenMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GrassMaterial : public BaseMaterial
{
private:
  GrassMaterial() : BaseMaterial( NDb::GrassMaterial::priority, NDb::GrassMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(GrassMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler FrozenDiffuseMap;
	Render::Sampler NormalDiffuseMap;
	Render::Sampler BurnedDiffuseMap;
	CVec2 bladeSize;
	float elasticity;
	NDb::BooleanPin ShadowReciverPinValue;
	NDb::Ptr<NDb::GrassMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * ShadowReciverPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::GrassMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->FrozenDiffuseMap, &FrozenDiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->NormalDiffuseMap, &NormalDiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->BurnedDiffuseMap, &BurnedDiffuseMap, false, texturePoolId );
		ShadowReciverPinValue = pDbMaterial->ShadowReciverPinValue;
		bladeSize = pDbMaterial->bladeSize;
		elasticity = pDbMaterial->elasticity;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( GrassMaterial, renderState ) + sizeof( renderState ) == offsetof( GrassMaterial, FrozenDiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( GrassMaterial, FrozenDiffuseMap ) + sizeof( FrozenDiffuseMap ) == offsetof( GrassMaterial, NormalDiffuseMap ), Found_gap_after_significant_field_FrozenDiffuseMap );
	  NI_STATIC_ASSERT( offsetof( GrassMaterial, NormalDiffuseMap ) + sizeof( NormalDiffuseMap ) == offsetof( GrassMaterial, BurnedDiffuseMap ), Found_gap_after_significant_field_NormalDiffuseMap );
	  NI_STATIC_ASSERT( offsetof( GrassMaterial, BurnedDiffuseMap ) + sizeof( BurnedDiffuseMap ) == offsetof( GrassMaterial, bladeSize ), Found_gap_after_significant_field_BurnedDiffuseMap );
	  NI_STATIC_ASSERT( offsetof( GrassMaterial, bladeSize ) + sizeof( bladeSize ) == offsetof( GrassMaterial, elasticity ), Found_gap_after_significant_field_bladeSize );
	}

  static int samplersOffsets[3];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 3 );
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( GrassMaterial, elasticity ) - offsetof( GrassMaterial, renderState ) + sizeof( elasticity ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::GrassMaterial* dbMaterial = static_cast<const NDb::GrassMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::GrassMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, FrozenDiffuseMap );
		Render::BindSampler( 1, NormalDiffuseMap );
		Render::BindSampler( 2, BurnedDiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( GrassMaterial, FrozenDiffuseMap );
    samplersOffsets[1] = offsetof( GrassMaterial, NormalDiffuseMap );
    samplersOffsets[2] = offsetof( GrassMaterial, BurnedDiffuseMap );
  }
	
	enum { typeId = NDb::GrassMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new GrassMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HeightfogMaterial : public BaseMaterial
{
private:
  HeightfogMaterial() : BaseMaterial( NDb::HeightfogMaterial::priority, NDb::HeightfogMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(HeightfogMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler noiseMap;
	float noiseR1;
	float noiseR2;
	float noiseR3;
	float speed;
	float tiling;
	Render::HDRColor color1;
	Render::HDRColor color2;
	float roughnessScale;
	float halfFadeDistance;
	NDb::Ptr<NDb::HeightfogMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::HeightfogMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->noiseMap, &noiseMap, false, texturePoolId );
		noiseR1 = pDbMaterial->noiseR1;
		noiseR2 = pDbMaterial->noiseR2;
		noiseR3 = pDbMaterial->noiseR3;
		speed = pDbMaterial->speed;
		tiling = pDbMaterial->tiling;
		color1 = pDbMaterial->color1;
		color2 = pDbMaterial->color2;
		roughnessScale = pDbMaterial->roughnessScale;
		halfFadeDistance = pDbMaterial->halfFadeDistance;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, renderState ) + sizeof( renderState ) == offsetof( HeightfogMaterial, noiseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, noiseMap ) + sizeof( noiseMap ) == offsetof( HeightfogMaterial, noiseR1 ), Found_gap_after_significant_field_noiseMap );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, noiseR1 ) + sizeof( noiseR1 ) == offsetof( HeightfogMaterial, noiseR2 ), Found_gap_after_significant_field_noiseR1 );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, noiseR2 ) + sizeof( noiseR2 ) == offsetof( HeightfogMaterial, noiseR3 ), Found_gap_after_significant_field_noiseR2 );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, noiseR3 ) + sizeof( noiseR3 ) == offsetof( HeightfogMaterial, speed ), Found_gap_after_significant_field_noiseR3 );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, speed ) + sizeof( speed ) == offsetof( HeightfogMaterial, tiling ), Found_gap_after_significant_field_speed );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, tiling ) + sizeof( tiling ) == offsetof( HeightfogMaterial, color1 ), Found_gap_after_significant_field_tiling );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, color1 ) + sizeof( color1 ) == offsetof( HeightfogMaterial, color2 ), Found_gap_after_significant_field_color1 );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, color2 ) + sizeof( color2 ) == offsetof( HeightfogMaterial, roughnessScale ), Found_gap_after_significant_field_color2 );
	  NI_STATIC_ASSERT( offsetof( HeightfogMaterial, roughnessScale ) + sizeof( roughnessScale ) == offsetof( HeightfogMaterial, halfFadeDistance ), Found_gap_after_significant_field_roughnessScale );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "HeightfogMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( HeightfogMaterial, halfFadeDistance ) - offsetof( HeightfogMaterial, renderState ) + sizeof( halfFadeDistance ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::HeightfogMaterial* dbMaterial = static_cast<const NDb::HeightfogMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::HeightfogMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, noiseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( HeightfogMaterial, noiseMap );
  }
	
	enum { typeId = NDb::HeightfogMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new HeightfogMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LightningMaterial : public BaseMaterial
{
private:
  LightningMaterial() : BaseMaterial( NDb::LightningMaterial::priority, NDb::LightningMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(LightningMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	NDb::Ptr<NDb::LightningMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::LightningMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( LightningMaterial, renderState ) + sizeof( renderState ) == offsetof( LightningMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( LightningMaterial, DiffuseMap ) - offsetof( LightningMaterial, renderState ) + sizeof( DiffuseMap ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::LightningMaterial* dbMaterial = static_cast<const NDb::LightningMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::LightningMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( LightningMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::LightningMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new LightningMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NatureMapMaterial : public BaseMaterial
{
private:
  NatureMapMaterial() : BaseMaterial( NDb::NatureMapMaterial::priority, NDb::NatureMapMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(NatureMapMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::Ptr<NDb::NatureMapMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::NatureMapMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::NatureMapMaterial* dbMaterial = static_cast<const NDb::NatureMapMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::NatureMapMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::NatureMapMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new NatureMapMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PaintMaterial : public BaseMaterial
{
private:
  PaintMaterial() : BaseMaterial( NDb::PaintMaterial::priority, NDb::PaintMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(PaintMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler Draft;
	Render::Sampler Background;
	Render::Sampler BaseBackground;
	Render::Sampler Complete;
	Render::Sampler Mask;
	float opacity;
	int isBlendModeOverrided;
	NDb::PackedMasksNumberPin masksNumber;
	NDb::PaintMaterialModePin paintMode;
	NDb::Ptr<NDb::PaintMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * masksNumber + 40 * paintMode;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::PaintMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		masksNumber = pDbMaterial->masksNumber;
		paintMode = pDbMaterial->paintMode;
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->Draft, &Draft, false, texturePoolId );
		FillSampler( pDbMaterial->Background, &Background, false, texturePoolId );
		FillSampler( pDbMaterial->BaseBackground, &BaseBackground, false, texturePoolId );
		FillSampler( pDbMaterial->Complete, &Complete, false, texturePoolId );
		FillSampler( pDbMaterial->Mask, &Mask, false, texturePoolId );
		opacity = pDbMaterial->opacity;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, renderState ) + sizeof( renderState ) == offsetof( PaintMaterial, Draft ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, Draft ) + sizeof( Draft ) == offsetof( PaintMaterial, Background ), Found_gap_after_significant_field_Draft );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, Background ) + sizeof( Background ) == offsetof( PaintMaterial, BaseBackground ), Found_gap_after_significant_field_Background );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, BaseBackground ) + sizeof( BaseBackground ) == offsetof( PaintMaterial, Complete ), Found_gap_after_significant_field_BaseBackground );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, Complete ) + sizeof( Complete ) == offsetof( PaintMaterial, Mask ), Found_gap_after_significant_field_Complete );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, Mask ) + sizeof( Mask ) == offsetof( PaintMaterial, opacity ), Found_gap_after_significant_field_Mask );
	  NI_STATIC_ASSERT( offsetof( PaintMaterial, opacity ) + sizeof( opacity ) == offsetof( PaintMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_opacity );
	}

  static int samplersOffsets[5];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 5 );
  }

	#include "EaselPaintMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( PaintMaterial, isBlendModeOverrided ) - offsetof( PaintMaterial, renderState ) + sizeof( isBlendModeOverrided ); }

public:
	virtual const NDb::PackedMasksNumberPin GetPackedMasksNumberPin() const { return masksNumber; }
	virtual const NDb::PaintMaterialModePin GetPaintMaterialModePin() const { return paintMode; }
	virtual void SetPackedMasksNumberPin( const NDb::PackedMasksNumberPin value ) { masksNumber = value; UpdateStaticShaderIndex(); }
	virtual void SetPaintMaterialModePin( const NDb::PaintMaterialModePin value ) { paintMode = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::PaintMaterial* dbMaterial = static_cast<const NDb::PaintMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::PaintMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, Draft );
		Render::BindSampler( 1, Background );
		Render::BindSampler( 2, BaseBackground );
		Render::BindSampler( 3, Complete );
		Render::BindSampler( 4, Mask );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( PaintMaterial, Draft );
    samplersOffsets[1] = offsetof( PaintMaterial, Background );
    samplersOffsets[2] = offsetof( PaintMaterial, BaseBackground );
    samplersOffsets[3] = offsetof( PaintMaterial, Complete );
    samplersOffsets[4] = offsetof( PaintMaterial, Mask );
  }
	
	enum { typeId = NDb::PaintMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new PaintMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParticleFXMaterial : public BaseMaterial
{
private:
  ParticleFXMaterial() : BaseMaterial( NDb::ParticleFXMaterial::priority, NDb::ParticleFXMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(ParticleFXMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	float opacity;
	float distortion;
	CVec2 uvSpeed;
	int isBlendModeOverrided;
	float scale;
	NDb::OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	NDb::OrientTypePin OrientTypePinValue;
	NDb::BooleanPin DistortionPinValue;
	NDb::Ptr<NDb::ParticleFXMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue + 4 * GetRuntimePins().NewParticlesValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * DistortionPinValue + 8 * OpacityAndEmissiveModePinValue + 32 * OrientTypePinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::ParticleFXMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		OpacityAndEmissiveModePinValue = pDbMaterial->OpacityAndEmissiveModePinValue;
		OrientTypePinValue = pDbMaterial->OrientTypePinValue;
		DistortionPinValue = pDbMaterial->DistortionPinValue;
		opacity = pDbMaterial->opacity;
		distortion = pDbMaterial->distortion;
		uvSpeed = pDbMaterial->uvSpeed;
		isBlendModeOverrided = pDbMaterial->isBlendModeOverrided;
		scale = pDbMaterial->scale;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, renderState ) + sizeof( renderState ) == offsetof( ParticleFXMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( ParticleFXMaterial, opacity ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, opacity ) + sizeof( opacity ) == offsetof( ParticleFXMaterial, distortion ), Found_gap_after_significant_field_opacity );
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, distortion ) + sizeof( distortion ) == offsetof( ParticleFXMaterial, uvSpeed ), Found_gap_after_significant_field_distortion );
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, uvSpeed ) + sizeof( uvSpeed ) == offsetof( ParticleFXMaterial, isBlendModeOverrided ), Found_gap_after_significant_field_uvSpeed );
	  NI_STATIC_ASSERT( offsetof( ParticleFXMaterial, isBlendModeOverrided ) + sizeof( isBlendModeOverrided ) == offsetof( ParticleFXMaterial, scale ), Found_gap_after_significant_field_isBlendModeOverrided );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "ParticleFXMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( ParticleFXMaterial, scale ) - offsetof( ParticleFXMaterial, renderState ) + sizeof( scale ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::OpacityAndEmissiveModePin GetOpacityModePin() const { return OpacityAndEmissiveModePinValue; }
	virtual const NDb::OrientTypePin GetOrientTypePin() const { return OrientTypePinValue; }
	virtual void SetOpacityModePin( const NDb::OpacityAndEmissiveModePin value ) { OpacityAndEmissiveModePinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetOrientTypePin( const NDb::OrientTypePin value ) { OrientTypePinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::ParticleFXMaterial* dbMaterial = static_cast<const NDb::ParticleFXMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::ParticleFXMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( ParticleFXMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::ParticleFXMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new ParticleFXMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoadMaterial : public BaseMaterial
{
private:
  RoadMaterial() : BaseMaterial( NDb::RoadMaterial::priority, NDb::RoadMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(RoadMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler RoadMap;
	Render::Sampler BorderMap;
	NDb::BooleanPin TextureFitPinValue;
	NDb::BooleanPin DebugPinValue;
	NDb::Ptr<NDb::RoadMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().CachingPinValue + 10 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 5 * DebugPinValue + 20 * TextureFitPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::RoadMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->RoadMap, &RoadMap, true, texturePoolId );
		FillSampler( pDbMaterial->BorderMap, &BorderMap, true, texturePoolId );
		TextureFitPinValue = pDbMaterial->TextureFitPinValue;
		DebugPinValue = pDbMaterial->DebugPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( RoadMaterial, renderState ) + sizeof( renderState ) == offsetof( RoadMaterial, RoadMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( RoadMaterial, RoadMap ) + sizeof( RoadMap ) == offsetof( RoadMaterial, BorderMap ), Found_gap_after_significant_field_RoadMap );
	}

  static int samplersOffsets[2];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 2 );
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( RoadMaterial, BorderMap ) - offsetof( RoadMaterial, renderState ) + sizeof( BorderMap ); }

public:
	virtual const Render::Sampler* GetBorderMap() const { return &BorderMap; }
	virtual Render::Sampler* GetBorderMap() { return &BorderMap; }
	virtual const NDb::BooleanPin GetDebugPinValue() const { return DebugPinValue; }
	virtual const Render::Sampler* GetRoadMap() const { return &RoadMap; }
	virtual Render::Sampler* GetRoadMap() { return &RoadMap; }
	virtual const NDb::BooleanPin GetTextureFitPinValue() const { return TextureFitPinValue; }
	virtual void SetDebugPinValue( const NDb::BooleanPin value ) { DebugPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetTextureFitPinValue( const NDb::BooleanPin value ) { TextureFitPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::RoadMaterial* dbMaterial = static_cast<const NDb::RoadMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::RoadMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, RoadMap );
		Render::BindSampler( 1, BorderMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( RoadMaterial, RoadMap );
    samplersOffsets[1] = offsetof( RoadMaterial, BorderMap );
  }
	
	enum { typeId = NDb::RoadMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new RoadMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ShadowMaterial : public BaseMaterial
{
private:
  ShadowMaterial() : BaseMaterial( NDb::ShadowMaterial::priority, NDb::ShadowMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(ShadowMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::Ptr<NDb::ShadowMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue + 2 * GetRuntimePins().InstancingValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 4 * SkeletalMeshPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::ShadowMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( ShadowMaterial, renderState ) + sizeof( renderState ) == offsetof( ShadowMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "ShadowMaterialFunc.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( ShadowMaterial, DiffuseMap ) - offsetof( ShadowMaterial, renderState ) + sizeof( DiffuseMap ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::ShadowMaterial* dbMaterial = static_cast<const NDb::ShadowMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::ShadowMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( ShadowMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::ShadowMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new ShadowMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SilhouetteMaterial : public BaseMaterial
{
private:
  SilhouetteMaterial() : BaseMaterial( NDb::SilhouetteMaterial::priority, NDb::SilhouetteMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(SilhouetteMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	NDb::BooleanPin SkeletalMeshPinValue;
	NDb::Ptr<NDb::SilhouetteMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * SkeletalMeshPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::SilhouetteMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		SkeletalMeshPinValue = pDbMaterial->SkeletalMeshPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

	#include "WaterMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( SilhouetteMaterial, renderState ) - offsetof( SilhouetteMaterial, renderState ) + sizeof( renderState ); }

public:
	virtual const NDb::BooleanPin GetSkeletalMeshPin() const { return SkeletalMeshPinValue; }
	virtual void SetSkeletalMeshPin( const NDb::BooleanPin value ) { SkeletalMeshPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::SilhouetteMaterial* dbMaterial = static_cast<const NDb::SilhouetteMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::SilhouetteMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::SilhouetteMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new SilhouetteMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SkyMaterial : public BaseMaterial
{
private:
  SkyMaterial() : BaseMaterial( NDb::SkyMaterial::priority, NDb::SkyMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(SkyMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	float uOffset1;
	float vOffset1;
	float uOffset2;
	float vOffset2;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffset1Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffset1Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffset2Wrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffset2Wrapper;;
	NDb::Ptr<NDb::SkyMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::SkyMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, true, texturePoolId );
		outputMul = pDbMaterial->outputMul;
		outputAdd = pDbMaterial->outputAdd;
		uOffset1 = pDbMaterial->uOffset1;
		uOffset1Wrapper.Init( &uOffset1, pDbMaterial->uOffset1, 0.0f );
		vOffset1 = pDbMaterial->vOffset1;
		vOffset1Wrapper.Init( &vOffset1, pDbMaterial->vOffset1, 0.0f );
		uOffset2 = pDbMaterial->uOffset2;
		uOffset2Wrapper.Init( &uOffset2, pDbMaterial->uOffset2, 0.0f );
		vOffset2 = pDbMaterial->vOffset2;
		vOffset2Wrapper.Init( &vOffset2, pDbMaterial->vOffset2, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, renderState ) + sizeof( renderState ) == offsetof( SkyMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( SkyMaterial, outputMul ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, outputMul ) + sizeof( outputMul ) == offsetof( SkyMaterial, outputAdd ), Found_gap_after_significant_field_outputMul );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, outputAdd ) + sizeof( outputAdd ) == offsetof( SkyMaterial, uOffset1 ), Found_gap_after_significant_field_outputAdd );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, uOffset1 ) + sizeof( uOffset1 ) == offsetof( SkyMaterial, vOffset1 ), Found_gap_after_significant_field_uOffset1 );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, vOffset1 ) + sizeof( vOffset1 ) == offsetof( SkyMaterial, uOffset2 ), Found_gap_after_significant_field_vOffset1 );
	  NI_STATIC_ASSERT( offsetof( SkyMaterial, uOffset2 ) + sizeof( uOffset2 ) == offsetof( SkyMaterial, vOffset2 ), Found_gap_after_significant_field_uOffset2 );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "SkyMaterial.inl"
protected:
	virtual bool IsAnimated() const
	{
		return uOffset1Wrapper.IsAnimated()
			|| vOffset1Wrapper.IsAnimated()
			|| uOffset2Wrapper.IsAnimated()
			|| vOffset2Wrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( SkyMaterial, vOffset2 ) - offsetof( SkyMaterial, renderState ) + sizeof( vOffset2 ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( uOffset1Wrapper.IsAnimated() && uOffset1Wrapper.GetLength() > length )
  		length = uOffset1Wrapper.GetLength();
  	if ( vOffset1Wrapper.IsAnimated() && vOffset1Wrapper.GetLength() > length )
  		length = vOffset1Wrapper.GetLength();
  	if ( uOffset2Wrapper.IsAnimated() && uOffset2Wrapper.GetLength() > length )
  		length = uOffset2Wrapper.GetLength();
  	if ( vOffset2Wrapper.IsAnimated() && vOffset2Wrapper.GetLength() > length )
  		length = vOffset2Wrapper.GetLength();
  	return length;
  }
  
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::SkyMaterial* dbMaterial = static_cast<const NDb::SkyMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::SkyMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( SkyMaterial, DiffuseMap );
  }
	
	virtual void Update( float dt )
	{
		if( !SkyMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		uOffset1Wrapper.Step( dt );
		vOffset1Wrapper.Step( dt );
		uOffset2Wrapper.Step( dt );
		vOffset2Wrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		uOffset1Wrapper.SetStartTime( startTime );
		vOffset1Wrapper.SetStartTime( startTime );
		uOffset2Wrapper.SetStartTime( startTime );
		vOffset2Wrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::SkyMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new SkyMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainAOEMaterial : public BaseMaterial
{
private:
  TerrainAOEMaterial() : BaseMaterial( NDb::TerrainAOEMaterial::priority, NDb::TerrainAOEMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TerrainAOEMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	CVec2 uvScale;
	CVec2 uvOffset;
	NDb::Ptr<NDb::TerrainAOEMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TerrainAOEMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		uvScale = pDbMaterial->uvScale;
		uvOffset = pDbMaterial->uvOffset;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( TerrainAOEMaterial, renderState ) + sizeof( renderState ) == offsetof( TerrainAOEMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( TerrainAOEMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( TerrainAOEMaterial, uvScale ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TerrainAOEMaterial, uvScale ) + sizeof( uvScale ) == offsetof( TerrainAOEMaterial, uvOffset ), Found_gap_after_significant_field_uvScale );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "CommonMaterialFunc.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( TerrainAOEMaterial, uvOffset ) - offsetof( TerrainAOEMaterial, renderState ) + sizeof( uvOffset ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TerrainAOEMaterial* dbMaterial = static_cast<const NDb::TerrainAOEMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TerrainAOEMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( TerrainAOEMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::TerrainAOEMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TerrainAOEMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainElementDebugMaterial : public BaseMaterial
{
private:
  TerrainElementDebugMaterial() : BaseMaterial( NDb::TerrainElementDebugMaterial::priority, NDb::TerrainElementDebugMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TerrainElementDebugMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::Ptr<NDb::TerrainElementDebugMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TerrainElementDebugMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TerrainElementDebugMaterial* dbMaterial = static_cast<const NDb::TerrainElementDebugMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TerrainElementDebugMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::TerrainElementDebugMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TerrainElementDebugMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainElementMaterial : public BaseMaterial
{
private:
  TerrainElementMaterial() : BaseMaterial( NDb::TerrainElementMaterial::priority, NDb::TerrainElementMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TerrainElementMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::TerrainUVSetPin TerrainUVSetPinValue;
	NDb::TextureCountPin TextureCountPinValue;
	NDb::Ptr<NDb::TerrainElementMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().CachingPinValue + 5 * GetRuntimePins().DoDepthOutValue + 10 * GetRuntimePins().RenderModeValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 30 * TerrainUVSetPinValue + 60 * TextureCountPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TerrainElementMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		TerrainUVSetPinValue = pDbMaterial->TerrainUVSetPinValue;
		TextureCountPinValue = pDbMaterial->TextureCountPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual const NDb::TerrainUVSetPin GetTerrainUVSetPin() const { return TerrainUVSetPinValue; }
	virtual const NDb::TextureCountPin GetTextureCountPin() const { return TextureCountPinValue; }
	virtual void SetTerrainUVSetPin( const NDb::TerrainUVSetPin value ) { TerrainUVSetPinValue = value; UpdateStaticShaderIndex(); }
	virtual void SetTextureCountPin( const NDb::TextureCountPin value ) { TextureCountPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TerrainElementMaterial* dbMaterial = static_cast<const NDb::TerrainElementMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TerrainElementMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::TerrainElementMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TerrainElementMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainHeightBuilderMaterial : public BaseMaterial
{
private:
  TerrainHeightBuilderMaterial() : BaseMaterial( NDb::TerrainHeightBuilderMaterial::priority, NDb::TerrainHeightBuilderMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TerrainHeightBuilderMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	NDb::Ptr<NDb::TerrainHeightBuilderMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TerrainHeightBuilderMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( TerrainHeightBuilderMaterial, renderState ) - offsetof( TerrainHeightBuilderMaterial, renderState ) + sizeof( renderState ); }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TerrainHeightBuilderMaterial* dbMaterial = static_cast<const NDb::TerrainHeightBuilderMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TerrainHeightBuilderMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::TerrainHeightBuilderMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TerrainHeightBuilderMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TerrainMaterial : public BaseMaterial
{
private:
  TerrainMaterial() : BaseMaterial( NDb::TerrainMaterial::priority, NDb::TerrainMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TerrainMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler A_DiffuseMap;
	Render::Sampler N_DiffuseMap;
	Render::Sampler B_DiffuseMap;
	Render::Sampler FrozenNormalMap;
	Render::Sampler NormalNormalMap;
	Render::Sampler BurnedNormalMap;
	Render::Sampler FrozenSpecularMap;
	Render::Sampler NormalSpecularMap;
	Render::Sampler BurnedSpecularMap;
	Render::Sampler DarkMap;
	CTRect<float> grassRect;
	NDb::BooleanPin NormalMapPinValue;
	NDb::BooleanPin ShadowReciverPinValue;
	NDb::BooleanPin ShadowCasterPinValue;
	NDb::BooleanPin SpecularMapPinValue;
	NDb::BooleanPin EnvMapPinValue;
	NDb::BooleanPin DarkMapPinValue;
	NDb::TerrainUVSetPin TerrainUVSetPinValue;
	NDb::Ptr<NDb::TerrainMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * DarkMapPinValue + 4 * EnvMapPinValue + 8 * NormalMapPinValue + 16 * ShadowCasterPinValue + 32 * ShadowReciverPinValue + 64 * SpecularMapPinValue + 128 * TerrainUVSetPinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TerrainMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		grassRect = pDbMaterial->grassRect;
		FillSampler( pDbMaterial->A_DiffuseMap, &A_DiffuseMap, true, texturePoolId );
		FillSampler( pDbMaterial->N_DiffuseMap, &N_DiffuseMap, true, texturePoolId );
		FillSampler( pDbMaterial->B_DiffuseMap, &B_DiffuseMap, true, texturePoolId );
		FillSampler( pDbMaterial->FrozenNormalMap, &FrozenNormalMap, true, texturePoolId );
		FillSampler( pDbMaterial->NormalNormalMap, &NormalNormalMap, true, texturePoolId );
		FillSampler( pDbMaterial->BurnedNormalMap, &BurnedNormalMap, true, texturePoolId );
		FillSampler( pDbMaterial->FrozenSpecularMap, &FrozenSpecularMap, true, texturePoolId );
		FillSampler( pDbMaterial->NormalSpecularMap, &NormalSpecularMap, true, texturePoolId );
		FillSampler( pDbMaterial->BurnedSpecularMap, &BurnedSpecularMap, true, texturePoolId );
		FillSampler( pDbMaterial->DarkMap, &DarkMap, true, texturePoolId );
		NormalMapPinValue = pDbMaterial->NormalMapPinValue;
		ShadowReciverPinValue = pDbMaterial->ShadowReciverPinValue;
		ShadowCasterPinValue = pDbMaterial->ShadowCasterPinValue;
		SpecularMapPinValue = pDbMaterial->SpecularMapPinValue;
		EnvMapPinValue = pDbMaterial->EnvMapPinValue;
		DarkMapPinValue = pDbMaterial->DarkMapPinValue;
		TerrainUVSetPinValue = pDbMaterial->TerrainUVSetPinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, A_DiffuseMap ) + sizeof( A_DiffuseMap ) == offsetof( TerrainMaterial, N_DiffuseMap ), Found_gap_after_significant_field_A_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, N_DiffuseMap ) + sizeof( N_DiffuseMap ) == offsetof( TerrainMaterial, B_DiffuseMap ), Found_gap_after_significant_field_N_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, B_DiffuseMap ) + sizeof( B_DiffuseMap ) == offsetof( TerrainMaterial, FrozenNormalMap ), Found_gap_after_significant_field_B_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, FrozenNormalMap ) + sizeof( FrozenNormalMap ) == offsetof( TerrainMaterial, NormalNormalMap ), Found_gap_after_significant_field_FrozenNormalMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, NormalNormalMap ) + sizeof( NormalNormalMap ) == offsetof( TerrainMaterial, BurnedNormalMap ), Found_gap_after_significant_field_NormalNormalMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, BurnedNormalMap ) + sizeof( BurnedNormalMap ) == offsetof( TerrainMaterial, FrozenSpecularMap ), Found_gap_after_significant_field_BurnedNormalMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, FrozenSpecularMap ) + sizeof( FrozenSpecularMap ) == offsetof( TerrainMaterial, NormalSpecularMap ), Found_gap_after_significant_field_FrozenSpecularMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, NormalSpecularMap ) + sizeof( NormalSpecularMap ) == offsetof( TerrainMaterial, BurnedSpecularMap ), Found_gap_after_significant_field_NormalSpecularMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, BurnedSpecularMap ) + sizeof( BurnedSpecularMap ) == offsetof( TerrainMaterial, DarkMap ), Found_gap_after_significant_field_BurnedSpecularMap );
	  NI_STATIC_ASSERT( offsetof( TerrainMaterial, DarkMap ) + sizeof( DarkMap ) == offsetof( TerrainMaterial, grassRect ), Found_gap_after_significant_field_DarkMap );
	}

  static int samplersOffsets[10];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 10 );
  }

	#include "TerrainMaterialFunc.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( TerrainMaterial, grassRect ) - offsetof( TerrainMaterial, A_DiffuseMap ) + sizeof( grassRect ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &N_DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &N_DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMapBurned() const { return &B_DiffuseMap; }
	virtual Render::Sampler* GetDiffuseMapBurned() { return &B_DiffuseMap; }
	virtual Render::Sampler* GetDiffuseMapFrozen() { return &A_DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMapFrozen() const { return &A_DiffuseMap; }
	virtual const NDb::BooleanPin GetShadowCasterPin() const { return ShadowCasterPinValue; }
	virtual void SetShadowCasterPin( const NDb::BooleanPin value ) { ShadowCasterPinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TerrainMaterial* dbMaterial = static_cast<const NDb::TerrainMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TerrainMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
		Render::BindSampler( 0, A_DiffuseMap );
		Render::BindSampler( 1, N_DiffuseMap );
		Render::BindSampler( 2, B_DiffuseMap );
		Render::BindSampler( 3, FrozenNormalMap );
		Render::BindSampler( 4, NormalNormalMap );
		Render::BindSampler( 5, BurnedNormalMap );
		Render::BindSampler( 6, FrozenSpecularMap );
		Render::BindSampler( 7, NormalSpecularMap );
		Render::BindSampler( 8, BurnedSpecularMap );
		Render::BindSampler( 9, DarkMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( TerrainMaterial, A_DiffuseMap );
    samplersOffsets[1] = offsetof( TerrainMaterial, N_DiffuseMap );
    samplersOffsets[2] = offsetof( TerrainMaterial, B_DiffuseMap );
    samplersOffsets[3] = offsetof( TerrainMaterial, FrozenNormalMap );
    samplersOffsets[4] = offsetof( TerrainMaterial, NormalNormalMap );
    samplersOffsets[5] = offsetof( TerrainMaterial, BurnedNormalMap );
    samplersOffsets[6] = offsetof( TerrainMaterial, FrozenSpecularMap );
    samplersOffsets[7] = offsetof( TerrainMaterial, NormalSpecularMap );
    samplersOffsets[8] = offsetof( TerrainMaterial, BurnedSpecularMap );
    samplersOffsets[9] = offsetof( TerrainMaterial, DarkMap );
  }
	
	enum { typeId = NDb::TerrainMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TerrainMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TestTownMaterial : public BaseMaterial
{
private:
  TestTownMaterial() : BaseMaterial( NDb::TestTownMaterial::priority, NDb::TestTownMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TestTownMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState RenderState;
	Render::Sampler DiffuseMap;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	NDb::BooleanPin UseDiffuse;
	NDb::Ptr<NDb::TestTownMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * UseDiffuse;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TestTownMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		RenderState = pDbMaterial->RenderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		UseDiffuse = pDbMaterial->UseDiffuse;
		outputMul = pDbMaterial->outputMul;
		outputAdd = pDbMaterial->outputAdd;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( TestTownMaterial, RenderState ) + sizeof( RenderState ) == offsetof( TestTownMaterial, DiffuseMap ), Found_gap_after_significant_field_RenderState );
	  NI_STATIC_ASSERT( offsetof( TestTownMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( TestTownMaterial, outputMul ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TestTownMaterial, outputMul ) + sizeof( outputMul ) == offsetof( TestTownMaterial, outputAdd ), Found_gap_after_significant_field_outputMul );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "TestTownMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( TestTownMaterial, outputAdd ) - offsetof( TestTownMaterial, RenderState ) + sizeof( outputAdd ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetUseDiffuse() const { return UseDiffuse; }
	virtual void SetUseDiffuse( const NDb::BooleanPin value ) { UseDiffuse = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TestTownMaterial* dbMaterial = static_cast<const NDb::TestTownMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TestTownMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( RenderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( TestTownMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::TestTownMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TestTownMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TraceMaterial : public BaseMaterial
{
private:
  TraceMaterial() : BaseMaterial( NDb::TraceMaterial::priority, NDb::TraceMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(TraceMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::RenderState renderState;
	Render::Sampler DiffuseMap;
	float uScale;
	float vScale;
	float uOffset;
	float vOffset;
	NDb::BooleanPin TraceTexturePinValue;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > uOffsetWrapper;;
	NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > vOffsetWrapper;;
	NDb::Ptr<NDb::TraceMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * TraceTexturePinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::TraceMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		renderState = pDbMaterial->renderState;
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		TraceTexturePinValue = pDbMaterial->TraceTexturePinValue;
		uScale = pDbMaterial->uScale;
		vScale = pDbMaterial->vScale;
		uOffset = pDbMaterial->uOffset;
		uOffsetWrapper.Init( &uOffset, pDbMaterial->uOffset, 0.0f );
		vOffset = pDbMaterial->vOffset;
		vOffsetWrapper.Init( &vOffset, pDbMaterial->vOffset, 0.0f );
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( TraceMaterial, renderState ) + sizeof( renderState ) == offsetof( TraceMaterial, DiffuseMap ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( TraceMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( TraceMaterial, uScale ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( TraceMaterial, uScale ) + sizeof( uScale ) == offsetof( TraceMaterial, vScale ), Found_gap_after_significant_field_uScale );
	  NI_STATIC_ASSERT( offsetof( TraceMaterial, vScale ) + sizeof( vScale ) == offsetof( TraceMaterial, uOffset ), Found_gap_after_significant_field_vScale );
	  NI_STATIC_ASSERT( offsetof( TraceMaterial, uOffset ) + sizeof( uOffset ) == offsetof( TraceMaterial, vOffset ), Found_gap_after_significant_field_uOffset );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "CommonMaterialFunc.inl"
protected:
	virtual bool IsAnimated() const
	{
		return uOffsetWrapper.IsAnimated()
			|| vOffsetWrapper.IsAnimated();
	}
	
	virtual int SignificantPartLength() const { return offsetof( TraceMaterial, vOffset ) - offsetof( TraceMaterial, renderState ) + sizeof( vOffset ); }

public:
  virtual float GetAnimLength() const
  {
  	float length = 0.0f;
  	if ( uOffsetWrapper.IsAnimated() && uOffsetWrapper.GetLength() > length )
  		length = uOffsetWrapper.GetLength();
  	if ( vOffsetWrapper.IsAnimated() && vOffsetWrapper.GetLength() > length )
  		length = vOffsetWrapper.GetLength();
  	return length;
  }
  
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetTraceTexturePin() const { return TraceTexturePinValue; }
	virtual void SetTraceTexturePin( const NDb::BooleanPin value ) { TraceTexturePinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::TraceMaterial* dbMaterial = static_cast<const NDb::TraceMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::TraceMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( TraceMaterial, DiffuseMap );
  }
	
	virtual void Update( float dt )
	{
		if( !TraceMaterial::IsAnimated() )
			return;
		MarkMaterialUpdated();
		uOffsetWrapper.Step( dt );
		vOffsetWrapper.Step( dt );
	}
	
	virtual void SetStartTime( float startTime )
	{
		uOffsetWrapper.SetStartTime( startTime );
		vOffsetWrapper.SetStartTime( startTime );
	}
	
	enum { typeId = NDb::TraceMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new TraceMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIBaseMaterial : public BaseMaterial
{
private:
  UIBaseMaterial() : BaseMaterial( NDb::UIBaseMaterial::priority, NDb::UIBaseMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(UIBaseMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler DiffuseMap;
	Render::Sampler MaskMap;
	Render::RenderState renderState;
	Render::HDRColor color1;
	Render::HDRColor color2;
	float coef1;
	float coef2;
	float coef3;
	float coef4;
	float stripesStart;
	float stripesStep1;
	float stripesStep2;
	float stripesBlendFactor1;
	Render::HDRColor colorStripe100;
	Render::HDRColor colorStripe1000;
	NDb::BooleanPin UseDiffuse;
	NDb::MaskingTypePin Masking;
	NDb::BooleanPin Gradient;
	NDb::BooleanPin Colorized;
	NDb::BooleanPin Stripes;
	NDb::Ptr<NDb::UIBaseMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * Colorized + 4 * Gradient + 8 * Masking + 24 * Stripes + 48 * UseDiffuse;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::UIBaseMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->MaskMap, &MaskMap, false, texturePoolId );
		color1 = pDbMaterial->color1;
		color2 = pDbMaterial->color2;
		coef1 = pDbMaterial->coef1;
		coef2 = pDbMaterial->coef2;
		coef3 = pDbMaterial->coef3;
		coef4 = pDbMaterial->coef4;
		stripesStart = pDbMaterial->stripesStart;
		stripesStep1 = pDbMaterial->stripesStep1;
		stripesStep2 = pDbMaterial->stripesStep2;
		stripesBlendFactor1 = pDbMaterial->stripesBlendFactor1;
		UseDiffuse = pDbMaterial->UseDiffuse;
		Masking = pDbMaterial->Masking;
		Gradient = pDbMaterial->Gradient;
		Colorized = pDbMaterial->Colorized;
		Stripes = pDbMaterial->Stripes;
		colorStripe100 = pDbMaterial->colorStripe100;
		colorStripe1000 = pDbMaterial->colorStripe1000;
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( UIBaseMaterial, MaskMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, MaskMap ) + sizeof( MaskMap ) == offsetof( UIBaseMaterial, renderState ), Found_gap_after_significant_field_MaskMap );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, renderState ) + sizeof( renderState ) == offsetof( UIBaseMaterial, color1 ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, color1 ) + sizeof( color1 ) == offsetof( UIBaseMaterial, color2 ), Found_gap_after_significant_field_color1 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, color2 ) + sizeof( color2 ) == offsetof( UIBaseMaterial, coef1 ), Found_gap_after_significant_field_color2 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, coef1 ) + sizeof( coef1 ) == offsetof( UIBaseMaterial, coef2 ), Found_gap_after_significant_field_coef1 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, coef2 ) + sizeof( coef2 ) == offsetof( UIBaseMaterial, coef3 ), Found_gap_after_significant_field_coef2 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, coef3 ) + sizeof( coef3 ) == offsetof( UIBaseMaterial, coef4 ), Found_gap_after_significant_field_coef3 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, coef4 ) + sizeof( coef4 ) == offsetof( UIBaseMaterial, stripesStart ), Found_gap_after_significant_field_coef4 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, stripesStart ) + sizeof( stripesStart ) == offsetof( UIBaseMaterial, stripesStep1 ), Found_gap_after_significant_field_stripesStart );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, stripesStep1 ) + sizeof( stripesStep1 ) == offsetof( UIBaseMaterial, stripesStep2 ), Found_gap_after_significant_field_stripesStep1 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, stripesStep2 ) + sizeof( stripesStep2 ) == offsetof( UIBaseMaterial, stripesBlendFactor1 ), Found_gap_after_significant_field_stripesStep2 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, stripesBlendFactor1 ) + sizeof( stripesBlendFactor1 ) == offsetof( UIBaseMaterial, colorStripe100 ), Found_gap_after_significant_field_stripesBlendFactor1 );
	  NI_STATIC_ASSERT( offsetof( UIBaseMaterial, colorStripe100 ) + sizeof( colorStripe100 ) == offsetof( UIBaseMaterial, colorStripe1000 ), Found_gap_after_significant_field_colorStripe100 );
	}

  static int samplersOffsets[2];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 2 );
  }

	#include "UIBaseMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( UIBaseMaterial, colorStripe1000 ) - offsetof( UIBaseMaterial, DiffuseMap ) + sizeof( colorStripe1000 ); }

public:
	virtual const NDb::BooleanPin GetColorized() const { return Colorized; }
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetGradient() const { return Gradient; }
	virtual const NDb::MaskingTypePin GetMasking() const { return Masking; }
	virtual const Render::Sampler* GetMaskMap() const { return &MaskMap; }
	virtual Render::Sampler* GetMaskMap() { return &MaskMap; }
	virtual const NDb::BooleanPin GetStripes() const { return Stripes; }
	virtual const NDb::BooleanPin GetUseDiffuse() const { return UseDiffuse; }
	virtual void SetColorized( const NDb::BooleanPin value ) { Colorized = value; UpdateStaticShaderIndex(); }
	virtual void SetGradient( const NDb::BooleanPin value ) { Gradient = value; UpdateStaticShaderIndex(); }
	virtual void SetMasking( const NDb::MaskingTypePin value ) { Masking = value; UpdateStaticShaderIndex(); }
	virtual void SetStripes( const NDb::BooleanPin value ) { Stripes = value; UpdateStaticShaderIndex(); }
	virtual void SetUseDiffuse( const NDb::BooleanPin value ) { UseDiffuse = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::UIBaseMaterial* dbMaterial = static_cast<const NDb::UIBaseMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::UIBaseMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
		Render::BindSampler( 1, MaskMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( UIBaseMaterial, DiffuseMap );
    samplersOffsets[1] = offsetof( UIBaseMaterial, MaskMap );
  }
	
	enum { typeId = NDb::UIBaseMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new UIBaseMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIButtonMaterial : public BaseMaterial
{
private:
  UIButtonMaterial() : BaseMaterial( NDb::UIButtonMaterial::priority, NDb::UIButtonMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(UIButtonMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler BackgroundMap;
	Render::Sampler DiffuseMap;
	Render::Sampler WaitForActMap;
	Render::Sampler LackOfManaMap;
	Render::Sampler PressedMap;
	Render::Sampler HighlightMap;
	Render::Sampler ScreenMap;
	Render::RenderState renderState;
	float ScreenOpacity;
	NDb::BooleanPin WaitForActivationPin;
	NDb::BooleanPin LackOfManaPin;
	NDb::BooleanPin PressedPin;
	NDb::BooleanPin HighlightPin;
	NDb::BooleanPin DisablePin;
	NDb::BooleanPin PassivePin;
	NDb::BooleanPin UseDiffusePin;
	NDb::Ptr<NDb::UIButtonMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * DisablePin + 4 * HighlightPin + 8 * LackOfManaPin + 16 * PassivePin + 32 * PressedPin + 64 * UseDiffusePin + 128 * WaitForActivationPin;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::UIButtonMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		FillSampler( pDbMaterial->BackgroundMap, &BackgroundMap, false, texturePoolId );
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->WaitForActMap, &WaitForActMap, false, texturePoolId );
		FillSampler( pDbMaterial->LackOfManaMap, &LackOfManaMap, false, texturePoolId );
		FillSampler( pDbMaterial->PressedMap, &PressedMap, false, texturePoolId );
		FillSampler( pDbMaterial->HighlightMap, &HighlightMap, false, texturePoolId );
		FillSampler( pDbMaterial->ScreenMap, &ScreenMap, false, texturePoolId );
		WaitForActivationPin = pDbMaterial->WaitForActivationPin;
		LackOfManaPin = pDbMaterial->LackOfManaPin;
		PressedPin = pDbMaterial->PressedPin;
		HighlightPin = pDbMaterial->HighlightPin;
		DisablePin = pDbMaterial->DisablePin;
		PassivePin = pDbMaterial->PassivePin;
		UseDiffusePin = pDbMaterial->UseDiffusePin;
		ScreenOpacity = pDbMaterial->ScreenOpacity;
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, BackgroundMap ) + sizeof( BackgroundMap ) == offsetof( UIButtonMaterial, DiffuseMap ), Found_gap_after_significant_field_BackgroundMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( UIButtonMaterial, WaitForActMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, WaitForActMap ) + sizeof( WaitForActMap ) == offsetof( UIButtonMaterial, LackOfManaMap ), Found_gap_after_significant_field_WaitForActMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, LackOfManaMap ) + sizeof( LackOfManaMap ) == offsetof( UIButtonMaterial, PressedMap ), Found_gap_after_significant_field_LackOfManaMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, PressedMap ) + sizeof( PressedMap ) == offsetof( UIButtonMaterial, HighlightMap ), Found_gap_after_significant_field_PressedMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, HighlightMap ) + sizeof( HighlightMap ) == offsetof( UIButtonMaterial, ScreenMap ), Found_gap_after_significant_field_HighlightMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, ScreenMap ) + sizeof( ScreenMap ) == offsetof( UIButtonMaterial, renderState ), Found_gap_after_significant_field_ScreenMap );
	  NI_STATIC_ASSERT( offsetof( UIButtonMaterial, renderState ) + sizeof( renderState ) == offsetof( UIButtonMaterial, ScreenOpacity ), Found_gap_after_significant_field_renderState );
	}

  static int samplersOffsets[7];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 7 );
  }

	#include "UIButtonMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( UIButtonMaterial, ScreenOpacity ) - offsetof( UIButtonMaterial, BackgroundMap ) + sizeof( ScreenOpacity ); }

public:
	virtual Render::Sampler* GetBackgroundMap() { return &BackgroundMap; }
	virtual const Render::Sampler* GetBackgroundMap() const { return &BackgroundMap; }
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetDisablePin() const { return DisablePin; }
	virtual const Render::Sampler* GetHighlight() const { return &HighlightMap; }
	virtual Render::Sampler* GetHighlight() { return &HighlightMap; }
	virtual const NDb::BooleanPin GetHighlightPin() const { return HighlightPin; }
	virtual Render::Sampler* GetLackOfMana() { return &LackOfManaMap; }
	virtual const Render::Sampler* GetLackOfMana() const { return &LackOfManaMap; }
	virtual const NDb::BooleanPin GetLackOfManaPin() const { return LackOfManaPin; }
	virtual const NDb::BooleanPin GetPassivePin() const { return PassivePin; }
	virtual const Render::Sampler* GetPressed() const { return &PressedMap; }
	virtual Render::Sampler* GetPressed() { return &PressedMap; }
	virtual const NDb::BooleanPin GetPressedPin() const { return PressedPin; }
	virtual const Render::Sampler* GetScreenMap() const { return &ScreenMap; }
	virtual Render::Sampler* GetScreenMap() { return &ScreenMap; }
	virtual const NDb::BooleanPin GetUseDiffusePin() const { return UseDiffusePin; }
	virtual const Render::Sampler* GetWaitForActivation() const { return &WaitForActMap; }
	virtual Render::Sampler* GetWaitForActivation() { return &WaitForActMap; }
	virtual const NDb::BooleanPin GetWaitForActivationPin() const { return WaitForActivationPin; }
	virtual void SetDisablePin( const NDb::BooleanPin value ) { DisablePin = value; UpdateStaticShaderIndex(); }
	virtual void SetHighlightPin( const NDb::BooleanPin value ) { HighlightPin = value; UpdateStaticShaderIndex(); }
	virtual void SetLackOfManaPin( const NDb::BooleanPin value ) { LackOfManaPin = value; UpdateStaticShaderIndex(); }
	virtual void SetPassivePin( const NDb::BooleanPin value ) { PassivePin = value; UpdateStaticShaderIndex(); }
	virtual void SetPressedPin( const NDb::BooleanPin value ) { PressedPin = value; UpdateStaticShaderIndex(); }
	virtual void SetUseDiffusePin( const NDb::BooleanPin value ) { UseDiffusePin = value; UpdateStaticShaderIndex(); }
	virtual void SetWaitForActivationPin( const NDb::BooleanPin value ) { WaitForActivationPin = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::UIButtonMaterial* dbMaterial = static_cast<const NDb::UIButtonMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::UIButtonMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, BackgroundMap );
		Render::BindSampler( 1, DiffuseMap );
		Render::BindSampler( 2, WaitForActMap );
		Render::BindSampler( 3, LackOfManaMap );
		Render::BindSampler( 4, PressedMap );
		Render::BindSampler( 5, HighlightMap );
		Render::BindSampler( 6, ScreenMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( UIButtonMaterial, BackgroundMap );
    samplersOffsets[1] = offsetof( UIButtonMaterial, DiffuseMap );
    samplersOffsets[2] = offsetof( UIButtonMaterial, WaitForActMap );
    samplersOffsets[3] = offsetof( UIButtonMaterial, LackOfManaMap );
    samplersOffsets[4] = offsetof( UIButtonMaterial, PressedMap );
    samplersOffsets[5] = offsetof( UIButtonMaterial, HighlightMap );
    samplersOffsets[6] = offsetof( UIButtonMaterial, ScreenMap );
  }
	
	enum { typeId = NDb::UIButtonMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new UIButtonMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIFlashMaterial : public BaseMaterial
{
private:
  UIFlashMaterial() : BaseMaterial( NDb::UIFlashMaterial::priority, NDb::UIFlashMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(UIFlashMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler DiffuseMap;
	Render::Sampler DiffuseMap2;
	Render::HDRColor CXFormMul;
	Render::HDRColor CXFormAdd;
	NDb::BooleanPin UseDiffuse;
	NDb::BooleanPin UseDiffuse2;
	NDb::BooleanPin MorphShapes;
	NDb::BooleanPin ShaderForLines;
	NDb::BooleanPin UseColorFilter;
	NDb::BooleanPin Scale9Grid;
	NDb::BooleanPin Scale9GridBitmap;
	NDb::FlashBlendModePin FlashBlendMode;
	NDb::Ptr<NDb::UIFlashMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * FlashBlendMode + 32 * MorphShapes + 64 * Scale9Grid + 128 * Scale9GridBitmap + 256 * ShaderForLines + 512 * UseColorFilter + 1024 * UseDiffuse + 2048 * UseDiffuse2;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::UIFlashMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->DiffuseMap2, &DiffuseMap2, false, texturePoolId );
		UseDiffuse = pDbMaterial->UseDiffuse;
		UseDiffuse2 = pDbMaterial->UseDiffuse2;
		MorphShapes = pDbMaterial->MorphShapes;
		ShaderForLines = pDbMaterial->ShaderForLines;
		UseColorFilter = pDbMaterial->UseColorFilter;
		Scale9Grid = pDbMaterial->Scale9Grid;
		Scale9GridBitmap = pDbMaterial->Scale9GridBitmap;
		FlashBlendMode = pDbMaterial->FlashBlendMode;
		CXFormMul = pDbMaterial->CXFormMul;
		CXFormAdd = pDbMaterial->CXFormAdd;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( UIFlashMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( UIFlashMaterial, DiffuseMap2 ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( UIFlashMaterial, DiffuseMap2 ) + sizeof( DiffuseMap2 ) == offsetof( UIFlashMaterial, CXFormMul ), Found_gap_after_significant_field_DiffuseMap2 );
	  NI_STATIC_ASSERT( offsetof( UIFlashMaterial, CXFormMul ) + sizeof( CXFormMul ) == offsetof( UIFlashMaterial, CXFormAdd ), Found_gap_after_significant_field_CXFormMul );
	}

  static int samplersOffsets[2];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 2 );
  }

protected:
	virtual int SignificantPartLength() const { return offsetof( UIFlashMaterial, CXFormAdd ) - offsetof( UIFlashMaterial, DiffuseMap ) + sizeof( CXFormAdd ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap2() const { return &DiffuseMap2; }
	virtual Render::Sampler* GetDiffuseMap2() { return &DiffuseMap2; }
	virtual const NDb::FlashBlendModePin GetFlashBlendModePin() const { return FlashBlendMode; }
	virtual const NDb::BooleanPin GetMorphShapes() const { return MorphShapes; }
	virtual const NDb::BooleanPin GetScale9Grid() const { return Scale9Grid; }
	virtual const NDb::BooleanPin GetScale9GridBitmap() const { return Scale9GridBitmap; }
	virtual const NDb::BooleanPin GetShaderForLines() const { return ShaderForLines; }
	virtual const NDb::BooleanPin GetUseColorFilter() const { return UseColorFilter; }
	virtual const NDb::BooleanPin GetUseDiffuse() const { return UseDiffuse; }
	virtual const NDb::BooleanPin GetUseDiffuse2() const { return UseDiffuse2; }
	virtual void SetFlashBlendModePin( const NDb::FlashBlendModePin value ) { FlashBlendMode = value; UpdateStaticShaderIndex(); }
	virtual void SetMorphShapes( const NDb::BooleanPin value ) { MorphShapes = value; UpdateStaticShaderIndex(); }
	virtual void SetScale9Grid( const NDb::BooleanPin value ) { Scale9Grid = value; UpdateStaticShaderIndex(); }
	virtual void SetScale9GridBitmap( const NDb::BooleanPin value ) { Scale9GridBitmap = value; UpdateStaticShaderIndex(); }
	virtual void SetShaderForLines( const NDb::BooleanPin value ) { ShaderForLines = value; UpdateStaticShaderIndex(); }
	virtual void SetUseColorFilter( const NDb::BooleanPin value ) { UseColorFilter = value; UpdateStaticShaderIndex(); }
	virtual void SetUseDiffuse( const NDb::BooleanPin value ) { UseDiffuse = value; UpdateStaticShaderIndex(); }
	virtual void SetUseDiffuse2( const NDb::BooleanPin value ) { UseDiffuse2 = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::UIFlashMaterial* dbMaterial = static_cast<const NDb::UIFlashMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::UIFlashMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
		Render::BindSampler( 0, DiffuseMap );
		Render::BindSampler( 1, DiffuseMap2 );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( UIFlashMaterial, DiffuseMap );
    samplersOffsets[1] = offsetof( UIFlashMaterial, DiffuseMap2 );
  }
	
	enum { typeId = NDb::UIFlashMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new UIFlashMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIFontMaterial : public BaseMaterial
{
private:
  UIFontMaterial() : BaseMaterial( NDb::UIFontMaterial::priority, NDb::UIFontMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(UIFontMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler DiffuseMap;
	Render::RenderState renderState;
	Render::HDRColor PrimaryColor;
	Render::HDRColor SecondaryColor;
	NDb::BooleanPin UseDiffuse;
	NDb::BooleanPin DrawContour;
	NDb::Ptr<NDb::UIFontMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 2 * DrawContour + 4 * UseDiffuse;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::UIFontMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		UseDiffuse = pDbMaterial->UseDiffuse;
		DrawContour = pDbMaterial->DrawContour;
		PrimaryColor = pDbMaterial->PrimaryColor;
		SecondaryColor = pDbMaterial->SecondaryColor;
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( UIFontMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( UIFontMaterial, renderState ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( UIFontMaterial, renderState ) + sizeof( renderState ) == offsetof( UIFontMaterial, PrimaryColor ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( UIFontMaterial, PrimaryColor ) + sizeof( PrimaryColor ) == offsetof( UIFontMaterial, SecondaryColor ), Found_gap_after_significant_field_PrimaryColor );
	}

  static int samplersOffsets[1];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 1 );
  }

	#include "UIFontMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( UIFontMaterial, SecondaryColor ) - offsetof( UIFontMaterial, DiffuseMap ) + sizeof( SecondaryColor ); }

public:
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual const NDb::BooleanPin GetDrawContour() const { return DrawContour; }
	virtual const NDb::BooleanPin GetUseDiffuse() const { return UseDiffuse; }
	virtual void SetDrawContour( const NDb::BooleanPin value ) { DrawContour = value; UpdateStaticShaderIndex(); }
	virtual void SetUseDiffuse( const NDb::BooleanPin value ) { UseDiffuse = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::UIFontMaterial* dbMaterial = static_cast<const NDb::UIFontMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::UIFontMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, DiffuseMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( UIFontMaterial, DiffuseMap );
  }
	
	enum { typeId = NDb::UIFontMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new UIFontMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIGlassMaterial : public BaseMaterial
{
private:
  UIGlassMaterial() : BaseMaterial( NDb::UIGlassMaterial::priority, NDb::UIGlassMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(UIGlassMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	Render::Sampler BackgroundMap;
	Render::Sampler DiffuseMap;
	Render::Sampler OverlayMap;
	Render::Sampler ScreenMap;
	Render::RenderState renderState;
	float OverlayOpacity;
	float ScreenOpacity;
	NDb::Ptr<NDb::UIGlassMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::UIGlassMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		FillSampler( pDbMaterial->BackgroundMap, &BackgroundMap, false, texturePoolId );
		FillSampler( pDbMaterial->DiffuseMap, &DiffuseMap, false, texturePoolId );
		FillSampler( pDbMaterial->OverlayMap, &OverlayMap, false, texturePoolId );
		FillSampler( pDbMaterial->ScreenMap, &ScreenMap, false, texturePoolId );
		OverlayOpacity = pDbMaterial->OverlayOpacity;
		ScreenOpacity = pDbMaterial->ScreenOpacity;
		renderState = pDbMaterial->renderState;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, BackgroundMap ) + sizeof( BackgroundMap ) == offsetof( UIGlassMaterial, DiffuseMap ), Found_gap_after_significant_field_BackgroundMap );
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, DiffuseMap ) + sizeof( DiffuseMap ) == offsetof( UIGlassMaterial, OverlayMap ), Found_gap_after_significant_field_DiffuseMap );
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, OverlayMap ) + sizeof( OverlayMap ) == offsetof( UIGlassMaterial, ScreenMap ), Found_gap_after_significant_field_OverlayMap );
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, ScreenMap ) + sizeof( ScreenMap ) == offsetof( UIGlassMaterial, renderState ), Found_gap_after_significant_field_ScreenMap );
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, renderState ) + sizeof( renderState ) == offsetof( UIGlassMaterial, OverlayOpacity ), Found_gap_after_significant_field_renderState );
	  NI_STATIC_ASSERT( offsetof( UIGlassMaterial, OverlayOpacity ) + sizeof( OverlayOpacity ) == offsetof( UIGlassMaterial, ScreenOpacity ), Found_gap_after_significant_field_OverlayOpacity );
	}

  static int samplersOffsets[4];
  
  void InitSamplers()
  {
    SetSamplers( samplersOffsets, 4 );
  }

	#include "UIGlassMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return offsetof( UIGlassMaterial, ScreenOpacity ) - offsetof( UIGlassMaterial, BackgroundMap ) + sizeof( ScreenOpacity ); }

public:
	virtual Render::Sampler* GetBackgroundMap() { return &BackgroundMap; }
	virtual const Render::Sampler* GetBackgroundMap() const { return &BackgroundMap; }
	virtual Render::Sampler* GetDiffuseMap() { return &DiffuseMap; }
	virtual const Render::Sampler* GetDiffuseMap() const { return &DiffuseMap; }
	virtual Render::Sampler* GetOverlayMap() { return &OverlayMap; }
	virtual const Render::Sampler* GetOverlayMap() const { return &OverlayMap; }
	virtual const Render::Sampler* GetScreenMap() const { return &ScreenMap; }
	virtual Render::Sampler* GetScreenMap() { return &ScreenMap; }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::UIGlassMaterial* dbMaterial = static_cast<const NDb::UIGlassMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::UIGlassMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		  Render::SetRenderState( renderState );
		}
		Render::BindSampler( 0, BackgroundMap );
		Render::BindSampler( 1, DiffuseMap );
		Render::BindSampler( 2, OverlayMap );
		Render::BindSampler( 3, ScreenMap );
	}
	
	static void InitSamplersOffsets()
  {
    samplersOffsets[0] = offsetof( UIGlassMaterial, BackgroundMap );
    samplersOffsets[1] = offsetof( UIGlassMaterial, DiffuseMap );
    samplersOffsets[2] = offsetof( UIGlassMaterial, OverlayMap );
    samplersOffsets[3] = offsetof( UIGlassMaterial, ScreenMap );
  }
	
	enum { typeId = NDb::UIGlassMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new UIGlassMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WaterDummyMaterial : public BaseMaterial
{
private:
  WaterDummyMaterial() : BaseMaterial( NDb::WaterDummyMaterial::priority, NDb::WaterDummyMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(WaterDummyMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::Ptr<NDb::WaterDummyMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue + 2 * GetRuntimePins().DualDepthPinValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::WaterDummyMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::WaterDummyMaterial* dbMaterial = static_cast<const NDb::WaterDummyMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::WaterDummyMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::WaterDummyMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new WaterDummyMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WaterMapMaterial : public BaseMaterial
{
private:
  WaterMapMaterial() : BaseMaterial( NDb::WaterMapMaterial::priority, NDb::WaterMapMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(WaterMapMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::Ptr<NDb::WaterMapMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 1 * GetRuntimePins().DoDepthOutValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 0;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::WaterMapMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::WaterMapMaterial* dbMaterial = static_cast<const NDb::WaterMapMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::WaterMapMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::WaterMapMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new WaterMapMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WaterMaterial : public BaseMaterial
{
private:
  WaterMaterial() : BaseMaterial( NDb::WaterMaterial::priority, NDb::WaterMaterial::flags, Render::RenderResourceManager::GetShaderIndexByTypeId(WaterMaterial::typeId) )
  {
    CheckTypesSizes();
    InitSamplers();
  }
	
	NDb::BooleanPin CausticsTexturePinValue;
	NDb::Ptr<NDb::WaterMaterial> pDbMaterial;

	unsigned int GetDynamicShaderIndex() const
	{
		return 2 * GetRuntimePins().DoDepthOutValue + 4 * GetRuntimePins().ShaderQualityValue;
	}

	void UpdateStaticShaderIndex()
	{
		staticShaderIndex = 1 * CausticsTexturePinValue;
		MarkShadersUpdated();
	}

	void FillMaterialInternal( const NDb::WaterMaterial* pDbMaterial, void * texturePoolId )
	{
		MarkMaterialUpdated();
		CausticsTexturePinValue = pDbMaterial->CausticsTexturePinValue;
		Render::Material::FillMaterial( pDbMaterial, texturePoolId );

		UpdateStaticShaderIndex();
		UpdateInternals();
	}

	unsigned int GetShaderIndex() const { return staticShaderIndex + GetDynamicShaderIndex(); }
	
	void CheckTypesSizes() const
	{
	}

  
  
  void InitSamplers()
  {
    
  }

	#include "WaterMaterial.inl"
protected:
	virtual int SignificantPartLength() const { return 0; }

public:
	virtual const NDb::BooleanPin GetCausticsTexturePin() const { return CausticsTexturePinValue; }
	virtual void SetCausticsTexturePin( const NDb::BooleanPin value ) { CausticsTexturePinValue = value; UpdateStaticShaderIndex(); }
	virtual void FillMaterial( const NDb::Material* _pDbMaterial, void * texturePoolId, bool _savePointer = true )
	{
		const NDb::WaterMaterial* dbMaterial = static_cast<const NDb::WaterMaterial*>( _pDbMaterial );
		if ( _savePointer )
			pDbMaterial = dbMaterial;
		FillMaterialInternal( dbMaterial, texturePoolId );
	}

	virtual void FillMaterial()
	{
		NDb::WaterMaterial dbMaterial;
		FillMaterialInternal( &dbMaterial, 0 );
	}

	virtual const NDb::Material* GetDBMaterial() const { return pDbMaterial.GetPtr(); }

  virtual void PrepareRenderer()
	{
    Render::BindShader( GetResourceManagerShaderIndex(), GetShaderIndex() );
		OnPrepareRender();
		if ( !GetDBMaterial() || !GetDBMaterial()->ignoreRenderState )
		{
		}
	}
	
	static void InitSamplersOffsets()
  {
  }
	
	enum { typeId = NDb::WaterMaterial::typeId, };
	static Render::Material* CreateMaterial() { return new WaterMaterial(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace Render
