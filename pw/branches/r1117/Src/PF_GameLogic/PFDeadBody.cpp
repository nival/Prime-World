/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PFDeadBody.h"
#include "PFAIWorld.h"

#ifndef VISUAL_CUTTED
#include "PFClientCreature.h"
#include "../PF_Core/EffectsPool.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

  CPtr<PFDeadBody> PFDeadBody::Make( PFWorld *pWorld, const CVec3& pos, CPtr<NGameX::PFClientCreature> const& unitClientObject, NDb::Ptr<NDb::EffectBase> const& onUnitDieEffect, float onUnitDieEffectOffset, bool playEffects )
{
  NDb::SingleStateObject desc;
  //desc.sceneObject = NULL;
  return new PFDeadBody( pWorld, pos, &desc, unitClientObject, onUnitDieEffect, onUnitDieEffectOffset, playEffects );
}

PFDeadBody::PFDeadBody(PFWorld *pWorld, const CVec3& pos, const NDb::SingleStateObject* pObjectDesc, CPtr<NGameX::PFClientCreature> const& unitClientObject, NDb::Ptr<NDb::EffectBase> const& onUnitDieEffect, float onUnitDieEffectOffset, bool playEffects )
  : PFLogicObject( pWorld, pos, pObjectDesc )
  , lifeTime(pWorld->GetAIWorld()->GetAIParameters().skeletonLifeTime)
  , unitBody(unitClientObject)
  , onUnitDieEffect(onUnitDieEffect)
  , onUnitDieEffectOffset(onUnitDieEffectOffset)
  , playOnUnitDieEffect(playEffects)
{
  InitData id;
  id.type = NDb::UNITTYPE_DEADBODY;
  id.faction = NDb::FACTION_NEUTRAL;
  id.playerId = -1;
  Initialize(id);
}

bool PFDeadBody::Step(float dt)
{
  NI_PROFILE_FUNCTION

  if ( playOnUnitDieEffect && onUnitDieEffect && IsValid(unitBody) )
  {
    float deadTime = unitBody->GetTimeDead();
    if ( /*deadTime > 0.0f &&*/ deadTime > onUnitDieEffectOffset )
    {
      if ( onUnitDieEffect->GetObjectTypeID() == NDb::EffectList::typeId )
      {
        const vector<NDb::Ptr<NDb::EffectBase>>& vecEffects = static_cast<NDb::EffectList const*>(onUnitDieEffect.GetPtr())->effects;
        for ( int i = 0, cnt = vecEffects.size(); i < cnt; i++ )
        {
          NDb::Ptr<NDb::EffectBase> const& pDBEffect = vecEffects[i];
          if ( CObj<PF_Core::BasicEffectStandalone> effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>(pDBEffect) )
          {
            effect->Apply( unitBody.GetPtr() );
          }
        }
      }
      else if ( CObj<PF_Core::BasicEffectStandalone> effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>(onUnitDieEffect) )
      {
        effect->Apply( unitBody.GetPtr() );
      }

      unitBody = NULL;
    }
  }

  lifeTime -= dt;
  if ( lifeTime < 0 )
  {
    Die();
  }
  return true;
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFDeadBody, NWorld)
