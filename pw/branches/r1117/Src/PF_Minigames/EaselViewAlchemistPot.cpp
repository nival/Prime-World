#include "stdafx.h"

#include "EaselViewAlchemistPot.h"
#include "Easel.h"
#include "MinigameSessionInterface.h"
#include "LuxBoost.h"
#include "BoostBoard.h"
#include "LuxGameLogic.h"
#include "EaselWorld.h"

#include "../Scene/SceneObject.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_GameLogic/PFMinigamePlace.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewAlchemistPot::OnDestroyContents()
{
  KillEffect();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselViewAlchemistPot::InitPot( Easel * _easel, const NDb::BasicEffectAttached * dbEffect )
{
  easel = _easel;

  NWorld::PFMinigamePlace * place = easel->GetWorldSessionInterface()->GetMinigamePlace();
  NScene::SceneObject * minigamePlaceSceneObject = IsValid( place )? place->GetClientSceneObject(): 0;

  NI_VERIFY( minigamePlaceSceneObject, "minigameplace is not valid", return false; ); 

  CObj<PF_Core::BasicEffectAttached> ef = easel->GetClient().CreateAttachedEffect( dbEffect, true );
  if( ef )
  {
    ef->Attach( minigamePlaceSceneObject );
    minigamePlaceSceneObject->UpdateForced(); //to get valid placement
    effect = ef;
    potPlacement = ef->GetRootComponent()->GetWorldPlacement();
  }
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselViewAlchemistPot::KillEffect()
{
  if ( effect )
  {
    effect->Die();

    if ( IsValid( easel ) )
      easel->GetClient().ReleaseEffect( effect );

    effect = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

class MaterialUVModifier : public Render::IMaterialProcessor
{
public:
  MaterialUVModifier( float _u, float _v ) : u( _u ), v( _v ) {}
  virtual void operator()( Render::BaseMaterial & material )
  {
    material.ModifyUVOffset( u, v );
  }
private:
  float u, v;
};

}


void EaselViewAlchemistPot::Update( float deltaTime, bool gameOnPause )
{
  if ( !effect  )
    return;

  CPtr<LuxBoost> boost = easel->GetWorld()->GetLogic()->GetBoostBoard()->GetBoost( NDb::BOOSTTYPE_ALCHEMIST );

  const float offs = IsValid( boost ) ? boost->ActivityProgress() : 0.f;

  if ( effect->GetRootComponent() )
  {
    for( NScene::SceneComponent * c = effect->GetRootComponent()->GetChild(); c; c = c->GetBrother() )
      if ( c->GetId() == "time" )
      {
        MaterialUVModifier m( 0.0f, offs );
        c->ForAllMaterials( m );
        break;
      }
  }
}

} //namespace PF_Minigames
