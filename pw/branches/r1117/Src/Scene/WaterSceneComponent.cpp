#include "stdafx.h"
#include "WaterSceneComponent.h"
#include "RenderableScene.h"

namespace NScene
{

#include "TestBB.h"

WaterSceneComponent::WaterSCRing  WaterSceneComponent::waterSCRing;

WaterSceneComponent::WaterSceneComponent( const NDb::DBWaterSceneComponent* pComponent, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
  : StaticSceneComponent( pComponent, pObj, pos )
{
  // override flags
  groupFlags &= ~GROUPFLAGS_REFLECTINWATER;

	Render::WaterMesh* pWaterMesh;
	pWaterMesh = new Render::WaterMesh();
	pWaterMesh->Initialize( IDENTITY_MATRIX, pComponent, pComponent->water );
	pWaterMesh->SetDBID(dbid);
	offset.SetPlacement( offset.GetPlacement() + pos );
	Reset(pStaticMesh, pWaterMesh);

	localAABB.Set(pComponent->aabb);
  TEST_BB_UNIQUE( localAABB.IsValid() );

  waterSCRing.addLast(this);
}

WaterSceneComponent::~WaterSceneComponent()
{
  waterSCRing.remove(this);
}

void WaterSceneComponent::ForAllWaterSC(WaterSCFunc &func)
{
  WaterSceneComponent *wsc = waterSCRing.first();
  for (; wsc != waterSCRing.last(); wsc = wsc->waterSCRingPart.next)
  {
    func(*wsc);
  }
}

} // namespace NScene
