#include "stdafx.h"

#include "../PF_Minigames/MinigameSessionInterface.h"
#include "../PF_Core/EffectsPool.h"

#include "PFClientMinigamePlace.h"
#include "PFMinigamePlace.h"
#include "PFEaselPlayer.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientMinigamePlace::PFClientMinigamePlace(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject) 
: PFBuilding( pWO, cp, pScene, gameObject )
, currentOpacity( 1.0f )
, pNdbEffect(0)
, pEffect(0)
, locked(false)
{
  //NOTICE: Модель площадки, общая для всех МГ - это клиентский объект PFClientMinigamePlace
  //А вот /графическая/ сцена, специфичная для каждой МГ - это менеджат сами миниигры
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMinigamePlace::SetVisibility( bool bVisible )
{
  NWorld::PFEaselPlayer * easelPlayer = WorldObject()->CurrentEaselPlayer();
  if ( easelPlayer )
    if ( IsValid( easelPlayer->GetMinigames()->GetCurrentMinigame() ) )
      easelPlayer->GetMinigames()->GetCurrentMinigame()->PlaceUnderFogOfWar( !bVisible );

  bool oldVisible = IsVisible();

  PFBuilding::SetVisibility( bVisible );

  if( oldVisible != bVisible )
  {
    if( locked )
      OnLocked();
    else
      OnUnlocked();
  }
}

void PFClientMinigamePlace::OnLocked()
{
  locked = true;

  if( !IsVisible() )
    return;

  if ( pEffect )
  {
    pEffect->Die();
    pEffect = 0;
  }
}

void PFClientMinigamePlace::OnUnlocked()
{
  locked = false;

  if( !IsVisible() )
    return;

  if ( !pEffect )
  {
    pEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>( pNdbEffect );
    if ( pEffect )
    {
      pEffect->Attach( GetSceneObject() );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientMinigamePlace::Update( float timeDiff )
{
  PFBuilding::Update( timeDiff );

  float opa = 1.0f;

  //Миниигры могут фэйдить свою сцену; Мы должны синхронно фэйдить свою модель
  NWorld::PFEaselPlayer * easelPlayer = WorldObject()->CurrentEaselPlayer();
  if ( easelPlayer &&  easelPlayer->GetMinigames()->DoFade() )
    opa = easelPlayer->GetMinigames()->GetMinigamePlaceOpacity();

  if( opa != currentOpacity )
  {
    ModifyOpacity( opa );
    currentOpacity = opa;
  }
}

} // namespace NGameX
