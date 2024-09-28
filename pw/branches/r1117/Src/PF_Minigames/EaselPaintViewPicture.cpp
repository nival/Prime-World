#include "stdafx.h"

#include "DBEasel.h"

#include "../Scene/SceneObject.h"

#include "Easel.h"
#include "EaselPaintViewPicture.h"
#include "EaselPaintLayerSceneComponent.h"
#include "EaselWorldClientConvertHelper.h"

#include "EaselConstants.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselPaintViewPicture::Init(Easel& easel)
{
	scene = easel.GetScene();

  const NDb::Ptr<NDb::DBPainterFragment>& painterData = easel.GetPainterLevelData();
  const NDb::Ptr<NDb::DBEaselCommon>& commonData = easel.GetData()->commonParams;
  const NDb::Ptr<NDb::DBSceneObject>& quadObject = easel.GetData()->game->paint.paintQuad;

  if ( !IsValid( painterData ) || !IsValid( commonData ) || !IsValid( quadObject ) )
    return false;

  if ( quadObject->attached.size() < 1 )
    return false;

  const NDb::AttachedSceneComponent& attachedCmp = quadObject->attached[0];

  const NDb::Ptr<NDb::DBStaticSceneComponent>& staticPart 
    = dynamic_cast<const NDb::DBStaticSceneComponent*>( attachedCmp.component.GetPtr() );

  if ( !staticPart )
    return false;

  // create placement
  Placement objPlacement = easel.GetPlacement();
  objPlacement.pos = easel.GetConvertHelper()->ConvertWorldToClientCoordinates(SVector(EaselConst::Get_LOGIC_FIELD_WIDTH()/2,EaselConst::Get_LOGIC_FIELD_HEIGHT()/2));

  sceneObject = AutoPtr<NScene::SceneObject>(new NScene::SceneObject( scene ) );

  Placement componentPlacement( attachedCmp.placement.pos, attachedCmp.placement.rot, attachedCmp.placement.scale );
  paint = new NScene::EaselPaintSceneComponent( staticPart->geometryFileName, painterData->paintMaterial, componentPlacement );

  sceneObject->Add( paint );

  sceneObject->UpdateForced();
  sceneObject->AddToScene( scene );

  sceneObject->SetPlacement( objPlacement );
  tmpAABB = sceneObject->GetWorldAABB();

  fIsInit = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintViewPicture::Update(float deltaTime, bool gameOnPause)
{
	MinigameClientObject::Update( deltaTime, gameOnPause );
}

void EaselPaintViewPicture::Hide()
{
  if(fIsInit == true && fIsHidden == false)
  {
    SetVisible(false);
    fIsHidden = true;
  }
}

void EaselPaintViewPicture::Show()
{
  if ( fIsInit == true && fIsHidden  )
  {
    SetVisible(true);
    fIsHidden = false;
  }
}


} // PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::EaselPaintViewPicture );