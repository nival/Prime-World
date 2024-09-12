//!Component('Scene/SceneObject')
//!Component('Scene/TestSceneComponent')
//!Component('System/Math')
//!Component('System/Random')
//!Component('Render/Math')
//!Component('Scene/TestHelpers')
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
#include "TestHelpers.h"

#include <Scene/DiAnGr.h>
#include "AGTrace.h"

class SceneObjectTestSuite : public CxxTest::TestSuite
{
public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testBoundingBoxTest()
	{
    NScene::SceneObject so;
		so.SetPlacement( NULLPLACEMENT );
    CObj<NScene::TestSceneComponent> sc( new NScene::TestSceneComponent( NULLPLACEMENT ) );
		so.Add( sc );
    so.UpdateForced( 0.1f );
    const Render::AABB &aabb = so.GetWorldAABB();
		TS_ASSERT( fabs( aabb.center - CVec3( 0.f, 0.f, 0.f ) ) < 0.01f );
    TS_ASSERT( fabs( aabb.halfSize - CVec3( 1.f, 1.f, 1.f ) ) < 0.01f );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testBoundingBoxPlacementTest()
	{
		NScene::SceneObject so;
		so.SetPlacement( NULLPLACEMENT );
		Placement pos = NULLPLACEMENT;
		pos.pos = CVec3( 4.f, 5.f, 6.f );
    CObj<NScene::TestSceneComponent> sc( new NScene::TestSceneComponent( pos ) );
		so.Add( sc );
		so.UpdateForced( 0.1f );
		const Render::AABB &aabb = so.GetWorldAABB();
		TS_ASSERT( fabs( aabb.center - CVec3( 4.f, 5.f, 6.f ) ) < 0.01f );
    TS_ASSERT( fabs( aabb.halfSize - CVec3( 1.f, 1.f, 1.f ) ) < 0.01f );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void testUpdateTimeTest()
	{
		NScene::SceneObject so;
		so.SetPlacement( NULLPLACEMENT );
		CObj<NScene::TestSceneComponent> sc( new NScene::TestSceneComponent( NULLPLACEMENT ) );
		so.Add( sc );
		CObj<NScene::TestSceneComponent> sc2( new NScene::TestSceneComponent( NULLPLACEMENT ) );
		sc->Attach( sc2 );
		TS_ASSERT( sc->GetAnimatedTime() < 0.01f );
		TS_ASSERT( sc2->GetAnimatedTime() < 0.01f );
		so.UpdateForced( 0.000001f );
		so.UpdateForced( 0.1f );
		so.UpdateForced( 0.1f );
		so.UpdateForced( 0.1f );
		TS_ASSERT( fabs( sc->GetAnimatedTime() - 0.3f ) < 0.01f );
		TS_ASSERT( fabs( sc2->GetAnimatedTime() - 0.3f ) < 0.01f );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testBoundingBoxHierarchyTest()
	{
		NScene::SceneObject so;
		so.SetPlacement( NULLPLACEMENT );
		Placement pos = NULLPLACEMENT;
		
    pos.pos = CVec3( 2.f, 0.f, 0.f );
    CObj<NScene::TestSceneComponent> sc( new NScene::TestSceneComponent( pos ) );
    so.Add( sc );
		
    pos.pos = CVec3( -4.f, 0.f, 0.f );
    CObj<NScene::TestSceneComponent> sc2( new NScene::TestSceneComponent( pos ) );
    sc->Attach( sc2 );

		so.UpdateForced( 0.1f );

		const Render::AABB &aabb = so.GetWorldAABB();
		TS_ASSERT( fabs( aabb.center - CVec3( 0.f, 0.f, 0.f ) ) < 0.1f );
    TS_ASSERT( fabs( aabb.halfSize - CVec3( 3.f, 1.f, 1.f ) ) < 0.1f );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testBoundingBoxHierarchyPlacementTest()
	{
		NScene::SceneObject so;
		Placement placement = NULLPLACEMENT;
		placement.pos = CVec3( 11.f, 0.f, 0.f );
		so.SetPlacement( placement );

		Placement pos = NULLPLACEMENT;
		
    pos.pos = CVec3( 2.f, 0.f, 0.f );
    CObj<NScene::TestSceneComponent> sc( new NScene::TestSceneComponent( pos ) );
    so.Add( sc );

		pos.pos = CVec3( -4.f, 0.f, 0.f );
    CObj<NScene::TestSceneComponent> sc2( new NScene::TestSceneComponent( pos ) );
    sc->Attach( sc2 );

		so.UpdateForced( 0.1f );
		const Render::AABB &aabb = so.GetWorldAABB();
		TS_ASSERT( fabs( aabb.center - CVec3( 11.f, 0.f, 0.f ) ) < 0.1f );
    TS_ASSERT( fabs( aabb.halfSize - CVec3( 3.f, 1.f, 1.f ) ) < 0.1f );
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void testHierarchyTest()
	{
		//NScene::SceneObject* so = new NScene::SceneObject;
		//Placement placement = NULLPLACEMENT;
		//IntrusivePtr<NScene::TestSceneComponent> sc  = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc2 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc3 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc4 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc5 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//TS_ASSERT( so->GetRootComponent() == 0 );
		//so->Add( Get( sc ) );
		//TS_ASSERT( so->GetRootComponent() == Get( sc ) );
		//so->Add( Get( sc2 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother() == Get( sc2 ) );
		//sc2->Attach( Get( sc3 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetChild() == Get( sc3 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetChild()->GetParent() == Get( sc2 ) );
		//sc->Attach( Get( sc5 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild() == Get( sc5 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild()->GetParent() == Get( sc ) );
		//sc3->Attach( Get( sc4 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetChild()->GetChild() == Get( sc4 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetChild()->GetChild()->GetParent() == Get( sc3 ) );
		//so->UpdateForced( 0.0001f );
		//so->UpdateForced( 1.0f );
		//TS_ASSERT( fabs( sc->GetAnimatedTime() - 1.f ) < 0.01f );
		//TS_ASSERT( fabs( sc2->GetAnimatedTime() - 1.f ) < 0.01f );
		//TS_ASSERT( fabs( sc3->GetAnimatedTime() - 1.f ) < 0.01f );
		//TS_ASSERT( fabs( sc4->GetAnimatedTime() - 1.f ) < 0.01f );
		//TS_ASSERT( fabs( sc5->GetAnimatedTime() - 1.f ) < 0.01f );

		//sc3->Detach();
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetChild() == 0 );
		//TS_ASSERT( so->GetRootComponent()->GetChild() == Get( sc5 ) );
		//delete so;

		//NScene::SceneObject* so2 = new NScene::SceneObject;
		//IntrusivePtr<NScene::TestSceneComponent> sc21 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc22 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc23 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//so2->Add( Get( sc21 ) );
		//so2->Add( Get( sc22 ) );
		//so2->Add( Get( sc23 ) );
		//TS_ASSERT( so->GetRootComponent() == Get( sc21 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother() == Get( sc23 ) );
		//TS_ASSERT( so->GetRootComponent()->GetBrother()->GetBrother() == Get( sc22 ) );
		//delete so2;

		//NScene::SceneObject* so3 = new NScene::SceneObject;
		//NScene::SceneObject* so4 = new NScene::SceneObject;
		//IntrusivePtr<NScene::TestSceneComponent> sc31 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc32 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc41 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc42 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//IntrusivePtr<NScene::TestSceneComponent> sc43 = INSTANTIATE_REF( NScene::TestSceneComponent, ( placement ) );
		//so3->Add( Get( sc31 ) );
		//sc31->Attach( Get( sc32 ) );
		//so4->Add( Get( sc41 ) );
		//so4->Add( Get( sc42 ) );
		//sc42->Attach( Get( sc43 ) );
		//so4->SetOwner( so3 );
		//delete so4;
		//TS_ASSERT( so->GetRootComponent() == Get( sc31 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild() == Get( sc32 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild()->GetBrother() == Get( sc41 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild()->GetBrother()->GetBrother() == Get( sc42 ) );
		//TS_ASSERT( so->GetRootComponent()->GetChild()->GetBrother()->GetBrother()->GetChild() == Get( sc43 ) );
		//delete so3;
	}
};
