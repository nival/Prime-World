#include "stdafx.h"
#include "PFApplFx.h"
#include "PFTargetSelector.h"
#include "PFBaseUnit.h"

namespace NWorld
{

bool PFApplFX::Start()
{
  CObj<PFSingleTargetSelector> pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().auxillaryTarget->Create( GetWorld() ));

  if ( pTargetSelector )
  {
    PFTargetSelector::RequestParams rp( *this, GetTarget() );
    pTargetSelector->FindTarget( rp, origin );
  }

  return PFApplBuff::Start();
}

PFLogicObject* PFApplFX::GetEffectOrigin()
{
  return origin.IsObjectValid( true ) ? origin.GetObject().GetPtr() : GetAbilityOwner().GetPtr();
}

PFLogicObject* PFApplFX::GetEffectTarget()
{
  if ( (GetDB().flags & NDb::FXFLAGS_APPLYFXTOAUX) != 0 )
  {
    NI_VERIFY( origin.IsObjectValid( true ), "Invalid FX target", return pReceiver );
    return origin.GetObject();
  }

  return pReceiver;
}

const IUnitFormulaPars* PFApplFX::GetObject( char const* objName ) const
{
  if ( strcmp( objName, "AuxTarget" ) == 0 )
  {
    return origin.IsObjectValid( true ) ? origin.GetObject().GetPtr() : pReceiver.GetPtr();
  }

  return Base::GetObject( objName );
}

}

REGISTER_WORLD_OBJECT_NM(PFApplFX, NWorld);
