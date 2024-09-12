//////////////////////////////////////////////////////////////////////////////////////////
// THIS FILE WAS GENERATED AUTOMATICALLY! DON'T CHANGE IT'S CONTENTS
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "../Render/GlobalMasks.h"
#include "MaterialSpec.h"
#include "../libdb/AnimatedWrapper.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Render::RuntimePins runtimePins = Render::RuntimePins();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RuntimePins::RuntimePins()
{
	CachingPinValue = (NDb::CachingPin)0;
	DecalModeValue = (NDb::DecalModePin)0;
	DoDepthOutValue = (NDb::BoolPin)0;
	DualDepthPinValue = (NDb::BoolPin)0;
	InstancingValue = (NDb::BooleanPin)0;
	NewParticlesValue = (NDb::BoolPin)0;
	RenderModeValue = (NDb::RenderModePin)0;
	ShaderQualityValue = (NDb::ShaderQualityPin)0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RuntimePins& GetRuntimePins()
{
	return runtimePins;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AOEMaterial::samplersOffsets[1];
int BasicFXMaterial::samplersOffsets[1];
int BasicMaskMaterial::samplersOffsets[2];
int BasicMaterial::samplersOffsets[4];
int DecalMaterial::samplersOffsets[1];
int DecalTerrainMaterial::samplersOffsets[2];
int DropMaterial::samplersOffsets[4];
int FullScreenMaterial::samplersOffsets[3];
int GrassMaterial::samplersOffsets[3];
int HeightfogMaterial::samplersOffsets[1];
int LightningMaterial::samplersOffsets[1];
int PaintMaterial::samplersOffsets[5];
int ParticleFXMaterial::samplersOffsets[1];
int RoadMaterial::samplersOffsets[2];
int ShadowMaterial::samplersOffsets[1];
int SkyMaterial::samplersOffsets[1];
int TerrainAOEMaterial::samplersOffsets[1];
int TerrainMaterial::samplersOffsets[10];
int TestTownMaterial::samplersOffsets[1];
int TraceMaterial::samplersOffsets[1];
int UIBaseMaterial::samplersOffsets[2];
int UIButtonMaterial::samplersOffsets[7];
int UIFlashMaterial::samplersOffsets[2];
int UIFontMaterial::samplersOffsets[1];
int UIGlassMaterial::samplersOffsets[4];
  
static struct SRegister_MaterialRegistrations
{
	SRegister_MaterialRegistrations()
	{
		Render::RegisterMaterialType( AIGeometryMaterialType::typeId, AIGeometryMaterialType::CreateMaterial, "AIGeometryMaterialType" );
		Render::RegisterMaterialType( AOEMaterial::typeId, AOEMaterial::CreateMaterial, "AOEMaterial" );
		Render::RegisterMaterialType( BasicFXMaterial::typeId, BasicFXMaterial::CreateMaterial, "BasicFXMaterial" );
		Render::RegisterMaterialType( BasicMaskMaterial::typeId, BasicMaskMaterial::CreateMaterial, "BasicMaskMaterial" );
		Render::RegisterMaterialType( BasicMaterial::typeId, BasicMaterial::CreateMaterial, "BasicMaterial" );
		Render::RegisterMaterialType( DebugMaterial::typeId, DebugMaterial::CreateMaterial, "DebugMaterial" );
		Render::RegisterMaterialType( DecalMaterial::typeId, DecalMaterial::CreateMaterial, "DecalMaterial" );
		Render::RegisterMaterialType( DecalTerrainMaterial::typeId, DecalTerrainMaterial::CreateMaterial, "DecalTerrainMaterial" );
		Render::RegisterMaterialType( DropMaterial::typeId, DropMaterial::CreateMaterial, "DropMaterial" );
		Render::RegisterMaterialType( FullScreenMaterial::typeId, FullScreenMaterial::CreateMaterial, "FullScreenMaterial" );
		Render::RegisterMaterialType( GrassMaterial::typeId, GrassMaterial::CreateMaterial, "GrassMaterial" );
		Render::RegisterMaterialType( HeightfogMaterial::typeId, HeightfogMaterial::CreateMaterial, "HeightfogMaterial" );
		Render::RegisterMaterialType( LightningMaterial::typeId, LightningMaterial::CreateMaterial, "LightningMaterial" );
		Render::RegisterMaterialType( NatureMapMaterial::typeId, NatureMapMaterial::CreateMaterial, "NatureMapMaterial" );
		Render::RegisterMaterialType( PaintMaterial::typeId, PaintMaterial::CreateMaterial, "PaintMaterial" );
		Render::RegisterMaterialType( ParticleFXMaterial::typeId, ParticleFXMaterial::CreateMaterial, "ParticleFXMaterial" );
		Render::RegisterMaterialType( RoadMaterial::typeId, RoadMaterial::CreateMaterial, "RoadMaterial" );
		Render::RegisterMaterialType( ShadowMaterial::typeId, ShadowMaterial::CreateMaterial, "ShadowMaterial" );
		Render::RegisterMaterialType( SilhouetteMaterial::typeId, SilhouetteMaterial::CreateMaterial, "SilhouetteMaterial" );
		Render::RegisterMaterialType( SkyMaterial::typeId, SkyMaterial::CreateMaterial, "SkyMaterial" );
		Render::RegisterMaterialType( TerrainAOEMaterial::typeId, TerrainAOEMaterial::CreateMaterial, "TerrainAOEMaterial" );
		Render::RegisterMaterialType( TerrainElementDebugMaterial::typeId, TerrainElementDebugMaterial::CreateMaterial, "TerrainElementDebugMaterial" );
		Render::RegisterMaterialType( TerrainElementMaterial::typeId, TerrainElementMaterial::CreateMaterial, "TerrainElementMaterial" );
		Render::RegisterMaterialType( TerrainHeightBuilderMaterial::typeId, TerrainHeightBuilderMaterial::CreateMaterial, "TerrainHeightBuilderMaterial" );
		Render::RegisterMaterialType( TerrainMaterial::typeId, TerrainMaterial::CreateMaterial, "TerrainMaterial" );
		Render::RegisterMaterialType( TestTownMaterial::typeId, TestTownMaterial::CreateMaterial, "TestTownMaterial" );
		Render::RegisterMaterialType( TraceMaterial::typeId, TraceMaterial::CreateMaterial, "TraceMaterial" );
		Render::RegisterMaterialType( UIBaseMaterial::typeId, UIBaseMaterial::CreateMaterial, "UIBaseMaterial" );
		Render::RegisterMaterialType( UIButtonMaterial::typeId, UIButtonMaterial::CreateMaterial, "UIButtonMaterial" );
		Render::RegisterMaterialType( UIFlashMaterial::typeId, UIFlashMaterial::CreateMaterial, "UIFlashMaterial" );
		Render::RegisterMaterialType( UIFontMaterial::typeId, UIFontMaterial::CreateMaterial, "UIFontMaterial" );
		Render::RegisterMaterialType( UIGlassMaterial::typeId, UIGlassMaterial::CreateMaterial, "UIGlassMaterial" );
		Render::RegisterMaterialType( WaterDummyMaterial::typeId, WaterDummyMaterial::CreateMaterial, "WaterDummyMaterial" );
		Render::RegisterMaterialType( WaterMapMaterial::typeId, WaterMapMaterial::CreateMaterial, "WaterMapMaterial" );
		Render::RegisterMaterialType( WaterMaterial::typeId, WaterMaterial::CreateMaterial, "WaterMaterial" );
		AOEMaterial::InitSamplersOffsets();
		BasicFXMaterial::InitSamplersOffsets();
		BasicMaskMaterial::InitSamplersOffsets();
		BasicMaterial::InitSamplersOffsets();
		DecalMaterial::InitSamplersOffsets();
		DecalTerrainMaterial::InitSamplersOffsets();
		DropMaterial::InitSamplersOffsets();
		FullScreenMaterial::InitSamplersOffsets();
		GrassMaterial::InitSamplersOffsets();
		HeightfogMaterial::InitSamplersOffsets();
		LightningMaterial::InitSamplersOffsets();
		PaintMaterial::InitSamplersOffsets();
		ParticleFXMaterial::InitSamplersOffsets();
		RoadMaterial::InitSamplersOffsets();
		ShadowMaterial::InitSamplersOffsets();
		SkyMaterial::InitSamplersOffsets();
		TerrainAOEMaterial::InitSamplersOffsets();
		TerrainMaterial::InitSamplersOffsets();
		TestTownMaterial::InitSamplersOffsets();
		TraceMaterial::InitSamplersOffsets();
		UIBaseMaterial::InitSamplersOffsets();
		UIButtonMaterial::InitSamplersOffsets();
		UIFlashMaterial::InitSamplersOffsets();
		UIFontMaterial::InitSamplersOffsets();
		UIGlassMaterial::InitSamplersOffsets();
	}
} materialRegistrations;
}; // namespace Render

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MaterialSpec.inl"

