#pragma once

#include "stdafx.h"
#include "PFMinimapEffect.h"
#include "AdventureScreen.h"
#include "Minimap.h"
#include "PFClientLogicObject.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFMinimapEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pObject_)
{
  SetDeathType( NDb::EFFECTDEATHTYPE_MANUAL, 0.0f );
  pObject = dynamic_cast<PFClientLogicObject*>(pObject_.GetPtr());
  NI_DATA_VERIFY(IsValid(pObject),
    NStr::StrFmt("Effect %s could not be applied on logic object", GetDBEffect().GetDBID().GetFileName().c_str()), 
    return; );

  index = AdventureScreen::Instance()->GetMinimap()->AddMinimapEffect( GetDBEffect().effect );
}

void PFMinimapEffect::Update( float timeDelta )
{
  if ( IsValid( pObject ) )
    AdventureScreen::Instance()->GetMinimap()->UpdateMinimapEffect( index, pObject->GetPosition().pos );
}

void PFMinimapEffect::Die()
{
  AdventureScreen::Instance()->GetMinimap()->SetMinimapEffect( index, (NDb::EMinimapEffects)(-1) );
  DieImmediate();
}

}
