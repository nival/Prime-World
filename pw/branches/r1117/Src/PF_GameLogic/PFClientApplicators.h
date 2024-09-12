#pragma once

#include "PF_Core/LightningEffect.h"
#include "PFUniTarget.h"

namespace PF_Core
{
	class BasicEffect;
}

namespace NWorld
{
  class PFWorldObjectBase;
}

namespace NGameX
{

typedef nstl::vector<CObj<PF_Core::BasicEffectStandalone>> StandaloneEffectsVector;

void PrepareEffect( CObj<PF_Core::BasicEffect>& pEffect, const NDb::Ptr<NDb::EffectBase>& effect );
void ApplyEffect(CObj<PF_Core::BasicEffect> pEffect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );
void RestoreEffect(CObj<PF_Core::BasicEffect> pEffect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, const Placement &placementOnStart, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );
void CreateEffect(CObj<PF_Core::BasicEffect> &pEffect, const NDb::Ptr<NDb::EffectBase>& effect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL);
void PlayEffect(NWorld::PFLogicObject* pUnit, const NDb::Ptr<NDb::EffectBase>& effect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );
void KillEffect(CObj<PF_Core::BasicEffect> &pEffect, bool waitTillAnimationFinish = false);

CObj<PF_Core::LightningEffect> CreateLightningEffect( const NDb::Ptr<NDb::LightningEffect>& pEffect, const string& skinId, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );

CObj<PF_Core::BasicEffectStandalone> RetrieveStandaloneEffect(NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );
void RetrieveStandaloneEffect(StandaloneEffectsVector *effectVector, NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );
void RetrieveStandaloneEffectCollection(StandaloneEffectsVector *effectList, NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback = NULL );

}