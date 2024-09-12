#include "stdafx.h"

#include "PFInvisibilityEffect.h"
#include "PFClientLogicObject.h"

#include "ClientVisibilityHelper.h"

namespace NGameX
{

void InvisibilityEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pObject)
{
  ScaleColorEffect::Apply(pObject);

  NI_VERIFY(IsValid(pObject), "Invalid object", return);

  pClientLogicObject = dynamic_cast<NGameX::PFClientLogicObject*>(pObject.GetPtr());

  NI_VERIFY(IsValid(pClientLogicObject), "Invalid object type", return);
}

void InvisibilityEffect::Apply(float t, bool)
{
  if (!IsValid(pChannel))
    return;
  if (!IsValid(pClientLogicObject))
    return;

  float opacity = 1.f - t;

  if (!ClientVisibilityHelper::IsVisibleForPlayer(pClientLogicObject))
    opacity = 0.f;

  pChannel->SetOpacity( opacity );
}

}
