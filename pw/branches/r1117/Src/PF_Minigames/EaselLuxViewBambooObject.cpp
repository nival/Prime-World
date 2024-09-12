#include "stdafx.h"
#include "EaselLuxViewBambooObject.h"

#include "../Scene/SceneObject.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class EaselLuxViewBambooObject implementation
//
//////////////////////////////////////////////////////////////////////////
EaselLuxViewBambooObject::EaselLuxViewBambooObject()
: EaselLuxStaticObject()
, startLocator(VNULL3)
, endLocator(VNULL3)
{

}

EaselLuxViewBambooObject::~EaselLuxViewBambooObject()
{

}

bool EaselLuxViewBambooObject::InitBambooObject(const CPtr<Easel>& _easel,
                                                const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                                                const Placement& _placement)
{
  if(InitObject(_easel,_DBSceneObject,_placement) == false)
    return false;

  //get locators for start point
  const NScene::Locator* startPointLocator1 = sceneObject->FindLocator( "start_point_start" );
  const NScene::Locator* startPointLocator2 = sceneObject->FindLocator( "start_point_end" );

  if( (startPointLocator1 != NULL) && (startPointLocator2 != NULL))
  {
    startPointLocator1->CalculateWorldPosition(startLocator);
    _placement.Transform( startLocator, startLocator);

    startPointLocator2->CalculateWorldPosition(endLocator);
    _placement.Transform( endLocator, endLocator);

    return true;
  }
  
  return false;
}



}
