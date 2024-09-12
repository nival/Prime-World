#include "stdafx.h"

#include "EaselLuxStaticObject.h"

#include "Easel.h"
#include "DBEasel.h"

#include "Minigames.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class EaselLuxStaticObject implementation
//
//////////////////////////////////////////////////////////////////////////
EaselLuxStaticObject::EaselLuxStaticObject() : MinigameClientObject()
{

}

EaselLuxStaticObject::~EaselLuxStaticObject()
{

}

bool EaselLuxStaticObject::InitObject(const CPtr<Easel>& _easel,
                                      const NDb::Ptr<NDb::DBSceneObject> _DBSceneObject,
                                      const Placement& _placement)
{
  NI_VERIFY(IsValid(_DBSceneObject), "EaselLuxStaticObject: passed NDb::DBSceneObject is invalid", return false);

  easel = _easel;
  
  //const CPtr<Minigames> minigames = _easel->GetMinigames();
  //NI_VERIFY( IsValid( minigames ), "EaselLuxStaticObject: minigames is dead or null", return false );

  return MinigameClientObject::Init(NULL, _easel->GetScene(), _DBSceneObject.GetPtr(), _placement, false);
}



}