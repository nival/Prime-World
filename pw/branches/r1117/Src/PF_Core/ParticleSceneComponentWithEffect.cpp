#include "stdafx.h"
#include "ParticleSceneComponentWithEffect.h"

#include "EffectsPool.h"

#include "../System/InlineProfiler.h"

namespace PF_Core
{

ParticleSceneComponentWithEffect::ParticleSceneComponentWithEffect( const NDb::ParticleSceneComponentWithEffect* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
  : ParticleSceneComponent(pObject, pObj, pos)
  , pDBObj(pObject)
{
  effectInstances.resize( pParticles->GetMaxParticleCount() );
}

void ParticleSceneComponentWithEffect::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  ParticleSceneComponent::UpdateComponent(pars, parentPos, timeDiff);

  int numParticles = pParticles->GetParticleCount();
  int i;
  for (i = 0; i < numParticles; ++i)
  {
    // spawn or kill effect as needed
    if ( pParticles->IsParticleActive(i) )
    {
      if ( !IsValid(effectInstances[i]) )
      {
        effectInstances[i] = EffectsPool::Get()->Retrieve<BasicEffectStandalone>( pDBObj->effect );
        //TODO: fix this code
        if ( IsValid(effectInstances[i]) )
        {
          effectInstances[i]->AddToScene(pars.pScene);
        }
      }
    }
    else
    {
      if ( IsValid(effectInstances[i]) )
      {
        effectInstances[i]->DieImmediate();
        effectInstances[i] = NULL;
      }
    }

    // update effect position
    if ( IsValid(effectInstances[i]) )
    {
      Placement place;

      pParticles->GetParticleWorldPos(i, place.pos);
      effectInstances[i]->SetPosition(place);
    }
  }

  // destroy effects that correspond to particles that do not exist
  for (; i < effectInstances.size(); ++i)
  {
    if ( IsValid(effectInstances[i]) )
    {
      NI_ALWAYS_ASSERT("This shouldn't happen AFAIK, particle count never decreases");
      effectInstances[i]->DieImmediate();
      effectInstances[i] = NULL;
    }
  }
}

}

