#include "stdafx.h"
#include "MarkersController.h"
#include "PFBaseUnit.h"
#include "PFClientBaseUnit.h"
#include "../PF_Core/EffectsPool.h"
#include "AdventureScreen.h"
#include "Minimap.h"
#include "../Sound/EventScene.h"

namespace NGameX
{

UnitMarker::UnitMarker( CPtr<NWorld::PFBaseUnit> const& pUnit, float duration, CObj<PF_Core::BasicEffect>& pAttachEffect, NDb::EMinimapEffects minimapEffect, Minimap * _minimap )
  : pUnit(pUnit)
  , duration(duration)
  , pAttachEffect(pAttachEffect)
  , faction(pUnit->GetFaction())
  , minimap(_minimap)
{
  pAttachEffect->Apply( pUnit->ClientObject() );
  
  if (IsValid(minimap))
    minimapEffectIndex = minimap->AddMinimapEffect( minimapEffect );
}

UnitMarker::~UnitMarker()
{
  pAttachEffect->Die();
  pAttachEffect = 0;

  if (IsValid(minimap))
    minimap->SetMinimapEffect( minimapEffectIndex, (NDb::EMinimapEffects)(-1) );
}

void MarkersController::AddMarker( CPtr<NWorld::PFBaseUnit> const& pUnit, NDb::EFaction faction )
{
  RemoveAdjacentMarkers(pUnit);

  bool isAlly = pUnit->GetFaction() == faction;
  CObj<PF_Core::BasicEffect> pAttachEffect = PF_Core::EffectsPool::Get()->Retrieve( isAlly ? NDb::EFFECTS_MARKERALLY : NDb::EFFECTS_MARKERHOSTILE );
  NDb::EMinimapEffects minimapEffect = isAlly ? NDb::MINIMAPEFFECTS_MARKERALLY : NDb::MINIMAPEFFECTS_MARKERHOSTILE;

  Strong<UnitMarker> marker = new UnitMarker( pUnit, pUIData->markerSettings.duration, pAttachEffect, minimapEffect, minimap );
  markers.push_back( marker );

  NSoundScene::EventStart( pUIData->soundEvents.minimapSignal );
}

void MarkersController::AddChatMarker(CPtr<NWorld::PFBaseUnit> const& pUnit)
{
  RemoveAdjacentMarkers(pUnit);

  CObj<PF_Core::BasicEffect> pAttachEffect = PF_Core::EffectsPool::Get()->Retrieve(NDb::EFFECTS_MARKERCHAT);
  NDb::EMinimapEffects minimapEffect = NDb::MINIMAPEFFECTS_CHAT;

  Strong<UnitMarker> marker = new UnitMarker( pUnit, pUIData->markerSettings.duration, pAttachEffect, minimapEffect, minimap );
  markers.push_back( marker );

  NSoundScene::EventStart( pUIData->soundEvents.chatMarker );
}

void MarkersController::Update( float dt )
{
  struct Updater
  {
    Updater( Minimap * _minimap, NDb::EFaction faction, float dt ): minimap(_minimap), faction(faction), dt(dt) {}

    bool operator()( Strong<UnitMarker>& unitMarker )
    {
      unitMarker->duration -= dt;
      if ( unitMarker->duration <= EPS_VALUE 
        || !IsUnitValid( unitMarker->pUnit ) 
        || !unitMarker->pUnit->IsVisibleForFaction( faction ) 
        || unitMarker->faction != unitMarker->pUnit->GetFaction() )
        return true;

      PFClientBaseUnit const* pClient = unitMarker->pUnit->ClientObject();

      if ( IsValid(pClient) && IsValid(minimap))
        minimap->UpdateMinimapEffect( unitMarker->minimapEffectIndex, pClient->GetPosition().pos );

      return false;
    }

    CPtr<Minimap> minimap;
    NDb::EFaction faction;
    float dt;
  } updater( minimap, playerFaction, dt );

  markers.erase( remove_if( markers.begin(), markers.end(), updater ), markers.end() );
}

void MarkersController::RemoveAdjacentMarkers(CPtr<NWorld::PFBaseUnit> const& pUnit)
{
  struct DistChecker
  {
    DistChecker( CPtr<NWorld::PFBaseUnit> const& pUnit, float dist ) : pCheckedUnit(pUnit.GetPtr()), distance2(dist*dist) {}

    bool operator()( Strong<UnitMarker> const& unitMarker )
    {
      return fabs2( unitMarker->pUnit->GetPosition().AsVec2D() - pCheckedUnit->GetPosition().AsVec2D() ) < distance2;
    }

    NWorld::PFBaseUnit const* pCheckedUnit;
    float distance2;
  } distChecker( pUnit, pUIData->markerSettings.otherMarkersCheckRange );

  markers.erase( remove_if( markers.begin(), markers.end(), distChecker ), markers.end() );
}

}
