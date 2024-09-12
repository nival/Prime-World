#pragma once

#include "PFLogicObject.h"


namespace NWorld
{
class PFBaseHero;

class PFPickupableObjectBase : public PFLogicObject
{
public:
  PFPickupableObjectBase( const CPtr<PFWorld>& pWorld, const CVec3& pos, const NDb::GameObject* objectDesc );
  
  bool         PickUp( PFBaseUnit* pPicker );
  virtual bool CanBePickedUpBy( const PFBaseUnit* pPicker ) const;
  void SetIsBeingPickuped( bool bValue ) { isBeingPickuped = bValue; }
  virtual const NDb::Ability* GetPickupAbility() const { return 0; }

protected:
  explicit PFPickupableObjectBase() {};
  virtual void OnPickedUp( PFBaseUnit* pPicker ) {}
  virtual bool Step(float dt);
  
  ZDATA_(PFLogicObject)
  bool isBeingPickuped;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFLogicObject*)this); f.Add(2,&isBeingPickuped); return 0; }
};

} //namespace NWorld