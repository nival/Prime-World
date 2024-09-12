#pragma once

#include "stdafx.h"
#include "../Scene/SceneObject.h"
#include "PFClientCreature.h"
#include "PFWorldNatureMap.h"
#include "PFUnitSceneObjectModify.h"
#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitSceneObjectModify::Apply(CPtr<PF_Core::ClientObjectBase> const &pObject)
{
	pCreature = dynamic_cast<PFClientCreature*>(pObject.GetPtr());
	NI_DATA_VERIFY(pCreature,
								 NStr::StrFmt("Effect %s could be applied on creature", GetDBEffect().GetDBID().GetFileName().c_str()), 
								 return; );

	NScene::SceneObject *pSO = pCreature->GetSceneObject();
	NI_VERIFY(pSO, NStr::StrFmt("Creature should have Scene Object", GetDBEffect().GetDBID().GetFileName().c_str()), return; );

	CVec3 const &pos = pCreature->GetPosition().pos;
  const NWorld::PFLogicObject *pLO = pCreature->WorldObject();
	int natureType = pLO->GetWorld()->GetNatureMap()->GetNatureInPoint(pos.x, pos.y);
	NI_VERIFY(0 <= natureType && natureType < 3, "Invalid nature type", return; )
	
	NDb::Ptr<NDb::DBSceneObject> pDBSceneObject = GetDBEffect().sceneObjects[natureType];
	if (!pDBSceneObject)
		pDBSceneObject = GetDBEffect().sceneObjects[0];
	NI_DATA_VERIFY(pDBSceneObject, 
		             NStr::StrFmt("Effect %s should contain scene object at least in Neutral state", GetDBEffect().GetDBID().GetFileName().c_str()), 
								 return; );

	NScene::IScene *pScene = pSO->GetScene();
	NI_ASSERT(pScene, "Scene object should present in scene")

	Reset(pSceneObjectHolder, new SingleSceneObjectHolder(pScene, pCreature->WorldObject()->GetObjectId(), pSO->GetPosition(), pDBSceneObject, pDBSceneObject->collisionGeometry, pCreature->GetNodeName()));

	if (GetDBEffect().mode == NDb::UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC)
	{
		//pCreature->Show(false);
   // pLO->UpdateHiddenState(false);
    pCreature->SetVisibility(false);
	}

  Update(0.0f);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFUnitSceneObjectModify::Update(float timeDelta)
{
  NI_VERIFY(IsValid(pCreature), "Creature is invalid", return);

  bool bVisible = false;

  BasicEffect::Update(timeDelta);
  
  if (const NWorld::PFLogicObject *pLO = pCreature->WorldObject())
  {
     NDb::EFaction playerFaction = AdventureScreen::Instance()->GetPlayerFaction();
   
     bVisible = playerFaction == pLO->GetFaction() ? true : AdventureScreen::Instance()->GetClientVisibilityMap()->IsPointVisible(pLO->GetPosition().AsVec2D());
  }

  if (GetDBEffect().visibilityMode == NDb::SCENEOBJECTVISIBILITYMODE_ASOBJECT)
  {
    pSceneObjectHolder->SetVisibility(bVisible);
  }
  else
  {
    pSceneObjectHolder->SetVisibility(true);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitSceneObjectModify::Die()
{
	if (GetDBEffect().mode == NDb::UNITSCENEOBJECTMODIFYMODE_REPLACESTATIC)
	{
		//pCreature->Show(true);
    pCreature->SetVisibility(true);
	}
	Reset(pSceneObjectHolder);
	pCreature = 0;

  BasicEffect::Die();
}


}