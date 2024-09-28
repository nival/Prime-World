#include "stdafx.h"
#include "PFPickupable.h"
#include "PFClientLogicObject.h"
#include "PFBaseUnit.h"


namespace NWorld
{

PFPickupableObjectBase::PFPickupableObjectBase( const CPtr<PFWorld>& pWorld, const CVec3& pos, const NDb::GameObject* objectDesc )
  : PFLogicObject( pWorld, pos, objectDesc ), isBeingPickuped(false)
{
  InitData data;
  data.faction = NDb::FACTION_NEUTRAL;
  data.playerId = 0xffffffff;
  data.type = NDb::UNITTYPE_PICKUPABLE;
  PFLogicObject::Initialize(data);
}

bool PFPickupableObjectBase::PickUp( PFBaseUnit* pPicker )
{
  isBeingPickuped = false;
  const bool canBePickedUp = CanBePickedUpBy(pPicker);
  if ( canBePickedUp )
  {
    OnPickedUp(pPicker);
    Die();
  }

  return canBePickedUp;
}

bool PFPickupableObjectBase::CanBePickedUpBy( const PFBaseUnit* pPicker ) const
{
  return isBeingPickuped == false && pPicker->CheckFlag( NDb::UNITFLAG_FORBIDINTERACT ) == false;
}

bool PFPickupableObjectBase::Step(float dt)
{
  NI_PROFILE_FUNCTION
  CALL_CLIENT(UpdateVisibility);
  return PFLogicObject::Step(dt);
}

} //namespace NWorld