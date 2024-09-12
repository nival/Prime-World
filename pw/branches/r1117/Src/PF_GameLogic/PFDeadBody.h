#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "PFLogicObject.h"

namespace NGameX
{
  class PFClientCreature;
}

namespace NWorld
{

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

class PFDeadBody : public PFLogicObject
{
  WORLD_OBJECT_METHODS( 0xF63D300, PFDeadBody );

public:
  static CPtr<PFDeadBody> Make( PFWorld *pWorld, const CVec3& pos, CPtr<NGameX::PFClientCreature> const& unitClientObject,
                                NDb::Ptr<NDb::EffectBase> const& onUnitDieEffect, float onUnitDieEffectOffset, bool playEffects );
protected:
  PFDeadBody(PFWorld *pWorld, const CVec3& pos, const NDb::SingleStateObject* pObjectDesc, CPtr<NGameX::PFClientCreature> const& unitClientObject, NDb::Ptr<NDb::EffectBase> const& onUnitDieEffect, float onUnitDieEffectOffset, bool playEffects );
  virtual bool Step(float dt);
  
  PFDeadBody() : playOnUnitDieEffect(true) { }
  
  // ~~ Visual Data ~~
  CPtr<NGameX::PFClientCreature>    unitBody;               // creature client object (visual body)
  NDb::Ptr<NDb::EffectBase>         onUnitDieEffect;        // unit die effect
  float                             onUnitDieEffectOffset;  // time offset then unit die effect would be started
  bool                              playOnUnitDieEffect;

  ZDATA_(PFLogicObject);
  float                             lifeTime;               // life time of dead body
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFLogicObject*)this); f.Add(2,&lifeTime); return 0; }
};

} // namespace NWorld
