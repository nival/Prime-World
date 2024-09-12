//!Component('Scene/SceneObject')
//!Component('Scene/TestSceneComponent')
//!Component('System/Math')
//!Component('System/Random')
//!Component('Render/Math')
//!Component('Scene/TestHelpers')
//!Component('Scene/TimeControllerTestHelpers')
//!Component('Scene/AnimationGraph')
//!Component('System/FileSystem/TestFileSystem')
//!Component('Scene/AnimationGraph')
//!Component('Render/ConfigManager')
//!Component('Scene/Collision')
//!Component('Sound/Main')
//!Component('Render/Base')
//!Component('Render/DebugRenderer')
//!Component('System/Compatibility')
//!Component('Render/PostEffects')
//!Component('System/MainFrame')
//!Component('Terrain/TerrainHeights')
//!Component('Terrain/Core')
//!Component('Terrain/TerrainManagers')
//!Component('Terrain/Visual')
//!Component('Render/DBRender')

#include "stdafx.h"
#include <CxxTest.h>

#include "TestSceneComponent.h"
#include "SceneObject.h"
#include <Scene/DiAnGr.h>
#include "System/FileSystem/TestFileSystem.h"
#include <Render/texture.h>
#include <iostream>
#include <Scene/SceneObjectCreation.h>
#include "../Render/RenderInterface.h"
#include <Scene/ParticleSceneComponent.h>
#include <Scene/StaticSceneComponent.h>
#include <Scene/AnimatedSceneComponent.h>

namespace Render
{
  class TestInterface : public Render::Interface
  {
  public:
    TestInterface( HWND hwnd = 0 ) : Render::Interface( hwnd ) {}
    virtual void ConstrainRender( const RECT &_rect ) {}
  };
};

static struct SRegister_InterfaceFactorySetter
{
  static Render::Interface * CreateRenderInterface(HWND hwnd) { return new Render::TestInterface(hwnd); }
  SRegister_InterfaceFactorySetter() { Render::Interface::RegisterFactory( &CreateRenderInterface ); }
} interfaceFactorySetter;

class TimeControllerTestSuite : public CxxTest::TestSuite
{
  CObj<TestFileSystem> pFileSystem;
  Render::Interface* pInterface;
public:

  void setUpSuite()
  {
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A_Speed.PRXY.xdb", "A_Speed.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/B.PRXY.xdb", "B.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/B_FadeInOut.PRXY.xdb", "B_FadeInOut.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/B_Speed.PRXY.xdb", "B_Speed.PRXY.xdb" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/C.PRXY.xdb", "C.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/C_Speed.PRXY.xdb", "C_Speed.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/CpPlane1.stat", "CpPlane1.stat" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/Droot.skel", "Droot.skel" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/DpPlane1.skin", "DpPlane1.skin" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/idle1.anim", "idle1.anim" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/idle2.anim", "idle2.anim" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/DautoClip.anim", "DautoClip.anim" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D.PRXY.xdb", "D.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Effect.PRXY.xdb", "D_Effect.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Short.PRXY.xdb", "D_Short.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Speed.PRXY.xdb", "D_Speed.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Random.PRXY.xdb", "D_Random.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Random_Short.PRXY.xdb", "D_Random_Short.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/D_Random_Speed.PRXY.xdb", "D_Random_Speed.PRXY.xdb" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/E.PRSC.xdb", "E.PRSC.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/E.PRXY.xdb", "E.PRXY.xdb" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/Test.TXTR.xdb", "Test.TXTR.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/Test_00.dds", "Test_00.dds" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A.dds", "A.dds" );
    pFileSystem->AssignFileWithFile( "Tech/Default/DefaultTexture.dds", "A.dds" );

    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A_FadeInOut.PRXY.xdb", "A_FadeInOut.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A3.part", "A3.part" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A.PRXY.xdb", "A.PRXY.xdb" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A.part", "A.part" );
    pFileSystem->AssignFileWithFile( "GFX_Textures/Atlases/atlas_0.TXTR.xdb", "atlas_0.TXTR.xdb" );
    pFileSystem->AssignFileWithFile( "GFX_Textures/Atlases/atlas_0.dds", "atlas_0.dds" );
    pFileSystem->AssignFileWithFile( "Test/TimeSlider/A.PRSC.xdb", "A.PRSC.xdb" );
    pFileSystem->AssignFileWithFile( "Tech/Default/Default.stat", "Default.stat" );

    pFileSystem->AssignFileWithFile( "Shaders/OnlineShaders/default_shader.vsb", "default_shader.vsb" );
    pFileSystem->AssignFileWithFile( "Shaders/OnlineShaders/default_shader.psb", "default_shader.psb" );
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/UIGlassMaterial.shd", "UIGlassMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/UIFlashMaterial.shd","UIFlashMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/UIButtonMaterial.shd", "UIButtonMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/ShadowMaterial.shd", "ShadowMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/ParticleFXMaterial.shd", "ParticleFXMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TerrainElementMaterial.shd", "TerrainElementMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/BasicMaterial.shd", "BasicMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/SilhouetteMaterial.shd", "SilhouetteMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/WaterMapMaterial.shd", "WaterMapMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/DebugMaterial.shd", "DebugMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/LightningMaterial.shd", "LightningMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/FullScreenMaterial.shd", "FullScreenMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/NatureMapMaterial.shd", "NatureMapMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/BasicFXMaterial.shd", "BasicFXMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/BasicMaskMaterial.shd", "BasicMaskMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TraceMaterial.shd", "TraceMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/DecalMaterial.shd", "DecalMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/SkyMaterial.shd", "SkyMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/WaterDummyMaterial.shd", "WaterDummyMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/GrassMaterial.shd", "GrassMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/UIFontMaterial.shd", "UIFontMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TerrainElementDebugMaterial.shd", "TerrainElementDebugMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/WaterMaterial.shd", "WaterMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/DropMaterial.shd", "DropMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TerrainMaterial.shd", "TerrainMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/RoadMaterial.shd", "RoadMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TestTownMaterial.shd", "TestTownMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/HeightfogMaterial.shd", "HeightfogMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/AIGeometryMaterialType.shd", "AIGeometryMaterialType.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/AOEMaterial.shd", "AOEMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TerrainHeightBuilderMaterial.shd", "TerrainHeightBuilderMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/TerrainAOEMaterial.shd", "TerrainAOEMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/UIBaseMaterial.shd", "UIBaseMaterial.shd");
    pFileSystem->AssignFileWithFile( "Shaders/UberShaders/PaintMaterial.shd", "PaintMaterial.shd");


    RootFileSystem::ClearFileSystems();
    RootFileSystem::RegisterFileSystem( pFileSystem );

    HWND hwndC = GetConsoleWindow();
    pInterface = Render::Interface::Create(hwndC);
    Render::RenderMode renderMode;
    renderMode.width = 1024;
    renderMode.height = 768;
    renderMode.isFullScreen = false;
    renderMode.vsyncCount = 0;
    renderMode.multiSampleQuality = 0;
    renderMode.multiSampleType = Render::MULTISAMPLE_NONE;
    renderMode.refreshRate = 0;
    pInterface->Start( renderMode );
  }

  void tearDownSuite()
  {
    pInterface->Stop();
    delete pInterface;
    pInterface = 0;
    RootFileSystem::ClearFileSystems();
    pFileSystem = 0;
  }

  void testSimpleParticleSceneComponent()
  {
/*    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/A.PRSC" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent());
    TS_ASSERT(psc);

    float v1 = psc->GetPureAnimLength();
    float v2 = psc->GetSubTreeAnimLength();
    float v3 = psc->CalculateTransformedAnimLength();
    v1;v2;v3;

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 15.0333f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    float v4 = psc->GetCurTime();
    float v5 = psc->GetAnimatedTime();
    v4;v5;

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 3.5f, 10e-2f );*/
  }

  void testSimpleProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/A.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 11.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 10.0f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 10.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testFadeInOutProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/A_FadeInOut.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 11.0f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 11.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testSpeedProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/A_Speed.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 7.5111f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 7.5111f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 7.0f, 10e-2f );
  }

  void testCycleNullProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/B.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 15.0333f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testCycleNullFadeInOutProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/B_FadeInOut.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 11.0f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 11.0f, 10e-2f );
    so->UpdateForced(1.1f);
    so->UpdateForced(1.1f);
    so->UpdateForced(1.1f);
    so->UpdateForced(1.1f);
    so->UpdateForced(1.1f);
    so->UpdateForced(1.1f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 5.6f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 5.6f, 10e-2f );
  }

  void testCycleNullSpeedProxySceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/B_Speed.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 7.5111f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 7.5111f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 7.0f, 10e-2f );
  }

  void testStaticSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/C.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::StaticSceneComponent* ssc = dynamic_cast<NScene::StaticSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(ssc);

    TS_ASSERT_DELTA( ssc->GetPureAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( ssc->GetSubTreeAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( ssc->CalculateTransformedAnimLength(), 15.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( ssc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( ssc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testSpeedStaticSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/C_Speed.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::StaticSceneComponent* ssc = dynamic_cast<NScene::StaticSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(ssc);

    TS_ASSERT_DELTA( ssc->GetPureAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( ssc->GetSubTreeAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( ssc->CalculateTransformedAnimLength(), 7.5f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( ssc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( ssc->GetAnimatedTime(), 7.0f, 10e-2f );
  }

  void testAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 15.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testSpeedAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Speed.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 7.5f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testShortAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Short.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 7.5f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testRandomAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Random.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 15.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testSpeedRandomAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Random_Speed.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 7.5f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testShortRandomAnimatedSceneComponent()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Random_Short.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(asc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 7.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 7.5f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testAnimatedSceneComponentWithEffect()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/D_Effect.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>(so->GetRootComponent()->GetChild());
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild()->GetChild()->GetChild());
    TS_ASSERT(asc);
    TS_ASSERT(psc);

    TS_ASSERT_DELTA( asc->GetPureAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetSubTreeAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( asc->CalculateTransformedAnimLength(), 15.0f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 11.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 10.0f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 10.0f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( asc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( asc->GetAnimatedTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 3.5f, 10e-2f );
  }

  void testComplexHierarchy()
  {
    NDb::Ptr<NDb::DBSceneComponent> dbsc = Get<NDb::DBSceneComponent>( NDb::DBID( "Test/TimeSlider/E.PRXY" ) );
    AutoPtr<NScene::SceneObject> so = NScene::CreateSceneObject( 0, *(dbsc.GetPtr()) );
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild());
    TS_ASSERT(psc);

    NScene::ParticleSceneComponent* psc2 = dynamic_cast<NScene::ParticleSceneComponent*>(so->GetRootComponent()->GetChild()->GetChild());
    TS_ASSERT(psc2);

    TS_ASSERT_DELTA( psc->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetSubTreeAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc->CalculateTransformedAnimLength(), 7.5111f, 10e-2f );

    TS_ASSERT_DELTA( psc2->GetPureAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc2->GetSubTreeAnimLength(), 15.0333f, 10e-2f );
    TS_ASSERT_DELTA( psc2->CalculateTransformedAnimLength(), 15.0333f, 10e-2f );
    so->UpdateForced(1.0f);
    so->UpdateForced(0.5f);
    so->UpdateForced(1.5f);
    so->UpdateForced(0.5f);

    TS_ASSERT_DELTA( psc->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc->GetAnimatedTime(), 7.0f, 10e-2f );
    TS_ASSERT_DELTA( psc2->GetCurTime(), 3.5f, 10e-2f );
    TS_ASSERT_DELTA( psc2->GetAnimatedTime(), 3.5f, 10e-2f );
  }

};
