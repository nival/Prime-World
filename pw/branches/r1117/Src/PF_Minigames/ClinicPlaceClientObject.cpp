#include "stdafx.h"

#include "ClinicPlaceClientObject.h"

#include "Clinic.h"
#include "ClinicPlace.h"
#include "ClinicCreep.h"
#include "../UI/ImageLabel.h"
#include "../UI/ProgressBar.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlaceClientObject::ClinicPlaceClientObject() :	
	sceneObjectDirty50(0),
  sceneObjectDirty100(0),
	collisionHullDirty50(0),
  collisionHullDirty100(0),
  visible(true),
  dirtyState(EPlaceDirtyState::Clear)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicPlaceClientObject::~ClinicPlaceClientObject()
{
	if ( IsValid( collisionHullDirty50 ) && IsValid( scene ) )
	{
		scene->GetCollisionMap()->RemoveHull( collisionHullDirty50 );
		collisionHullDirty50 = 0;
	}

  if ( IsValid( collisionHullDirty100 ) && IsValid( scene ) )
  {
    scene->GetCollisionMap()->RemoveHull( collisionHullDirty100 );
    collisionHullDirty100 = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::InitClinicPlace( ClinicPlace * _place, const NDb::DBSceneObject* _DBSceneObjectDirty50, const NDb::DBSceneObject* _DBSceneObjectDirty100 )
{
  NI_ASSERT( IsValid( clinic ), "" );
  clinicPlace = _place;

  InitSceneObject( _DBSceneObjectDirty50, scene, sceneObjectDirty50 );
  PostInitSceneObject( Get( sceneObjectDirty50 ), scene, collisionHullDirty50, IsVisibleAfterAll() );

  InitSceneObject( _DBSceneObjectDirty100, scene, sceneObjectDirty100 );
  PostInitSceneObject( Get( sceneObjectDirty100 ), scene, collisionHullDirty100, IsVisibleAfterAll() );

  if ( sceneObject )
  {
    sceneObjectDirty50->SetOwnerID( sceneObject->GetOwnerID() );
    sceneObjectDirty100->SetOwnerID( sceneObject->GetOwnerID() );
  }

  MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty50 ), false );
  MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty100 ), false );

  clinic->InsertMinigameSceneObject( Get( sceneObjectDirty50 ) );
  clinic->InsertMinigameSceneObject( Get( sceneObjectDirty100 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::SetVisible( bool _visible )
{
  visible = _visible;

  if ( _visible )
  {
    CDynamicCast<ClinicPlace> clinicPlaceWorldObject = worldObject;

    if ( IsValid( clinicPlaceWorldObject ) )
    {
      float soil = clinicPlaceWorldObject->GetSoil();

      dirtyState = EPlaceDirtyState::Soil100;

      if (soil < 0.5f)
        dirtyState = EPlaceDirtyState::Clear;
      else if (soil < 1.0f)
        dirtyState = EPlaceDirtyState::Soil50;

      switch( dirtyState )
      {
      case EPlaceDirtyState::Clear:
        MinigameClientObject::SetVisible( scene, Get( sceneObject ), true );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty50 ), false );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty100 ), false );
        break;
      case EPlaceDirtyState::Soil50:
        MinigameClientObject::SetVisible( scene, Get( sceneObject ), false );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty50 ), true );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty100 ), false );
        break;
      case EPlaceDirtyState::Soil100:
        MinigameClientObject::SetVisible( scene, Get( sceneObject ), false );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty50 ), true );
        MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty100 ), true );
        break;
      }
    }
  }
  else
  {
    MinigameClientObject::SetVisible( scene, Get( sceneObject ), false );
    MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty50 ), false );
    MinigameClientObject::SetVisible( scene, Get( sceneObjectDirty100 ), false );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlaceClientObject::IsVisible()
{
  return visible;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicPlaceClientObject::NeedHighlight() const
{
  return ( EClinicGameMode::Shop != clinic->GetGameMode() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::HDRColor& ClinicPlaceClientObject::GetHighlightColor() const
{
  return clinic->GetClinicDesc()->preselection.colorPreselect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject * ClinicPlaceClientObject::RedirectMouseOver()
{
  if ( IsValid(clinicPlace) )
    if ( IsValid( clinicPlace->GetOccupied() ) )
      return clinic->GetClientObject( clinicPlace->GetOccupied()->GetObjectID() );

  return this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::OnMouseEnter()
{
  MinigameClientObject::OnMouseEnter();

  /*
  if( IsValid( clinicPlace ) )
    if( IsValid( clinicPlace->GetOccupied() ) )
    {
      clinic->GetClientObject( currentWorldPick->GetObjectID() )
      clinicPlace->GetOccupied();
    }
  */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::OnMouseLeave()
{
  MinigameClientObject::OnMouseLeave();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::Update( float deltaTime, bool gameOnPause )
{
  MinigameClientObject::Update( deltaTime, gameOnPause );

  MoveSceneObject( FixPlacement( worldObject->GetPlacement() ), Get( sceneObjectDirty50 ), collisionHullDirty50 );
  MoveSceneObject( FixPlacement( worldObject->GetPlacement() ), Get( sceneObjectDirty100 ), collisionHullDirty100 );

  CDynamicCast<ClinicPlace> clinicPlaceWorldObject = worldObject;

  if ( IsValid( clinicPlaceWorldObject ) )
  {
    float soil = clinicPlaceWorldObject->GetSoil();

    EPlaceDirtyState::Enum newDirtyState = EPlaceDirtyState::Soil100;

    if (soil < 0.5f)
      newDirtyState = EPlaceDirtyState::Clear;
    else if (soil < 1.0f)
      newDirtyState = EPlaceDirtyState::Soil50;

    if ( newDirtyState != dirtyState )
    {
      dirtyState = newDirtyState;
      if(visible)
        SetVisible( true );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::SetupOvertipLayout(pWindow, overtipId);

  CheckControlOut(&wndTick,       pWindow, "Tick");
  CheckControlOut(&wndCooldown,   pWindow, "Cooldown");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicPlaceClientObject::UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::UpdateOvertipLayout(pWindow, overtipId);

  if(!IsValid(clinicPlace))
    return;

  if(IsValid(wndTick))
    wndTick->Show(clinicPlace->IsInRoute());

  if(IsValid(wndCooldown))
  {
    float cooldown = 0.0f;
    if(clinicPlace->IsCreepWorking(cooldown))
    {
      wndCooldown->Show(true);
      wndCooldown->SetProgressValue(cooldown);
    }
    else
      wndCooldown->Show(false);
  }
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::ClinicPlaceClientObject)
