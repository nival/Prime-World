#include "stdafx.h"
#include "EaselLuxViewWellObject.h"

#include "../Scene/SceneObject.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class EaselLuxViewWellObject implementation
//
//////////////////////////////////////////////////////////////////////////
EaselLuxViewWellObject::EaselLuxViewWellObject()
: EaselLuxStaticObject()
, startLocator(VNULL3)
, midLocator(VNULL3)
, endLocator(VNULL3)
{

}

EaselLuxViewWellObject::~EaselLuxViewWellObject()
{

}

bool EaselLuxViewWellObject::InitWellObject(const CPtr<Easel>& _easel,
                                            const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                                            const Placement& _placement)
{
  if(InitObject(_easel,_DBSceneObject,_placement) == false)
    return false;

  // get locators for end point
  const NScene::Locator* endPointLocator1 = sceneObject->FindLocator( "end_point_start" );
  const NScene::Locator* endPointLocator2 = sceneObject->FindLocator( "end_point_middle" );
  const NScene::Locator* endPointLocator3 = sceneObject->FindLocator( "end_point_end" );

  if( (endPointLocator1 != NULL) && (endPointLocator2 != NULL) && (endPointLocator3 != NULL))
  {
    endPointLocator1->CalculateWorldPosition(startLocator);
    _placement.Transform( startLocator, startLocator );

    endPointLocator2->CalculateWorldPosition(midLocator);
    _placement.Transform( midLocator, midLocator );

    endPointLocator3->CalculateWorldPosition(endLocator);
    _placement.Transform( endLocator, endLocator);

    return true;
  }
  
  return false;
}

}
