#include "stdafx.h"

#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/SpectatorEffectsPool.h"
#include "PFClientLogicObject.h"
#include "PFClientBaseUnit.h"

#include "PFClientApplicators.h"
#include "AdventureScreen.h"
#include "PFEffectSwitcher.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateEffect(CObj<PF_Core::BasicEffect>& pEffect, const NDb::Ptr<NDb::EffectBase>& effect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  PrepareEffect( pEffect, effect );
  ApplyEffect(pEffect, pSender, pTarget, pOrigin, pEnableCallback );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrepareEffect( CObj<PF_Core::BasicEffect>& pEffect, const NDb::Ptr<NDb::EffectBase>& effect )
{
  if ( !effect )
  {
    return;
  }

  pEffect = PF_Core::EffectsPool::Get()->Retrieve( effect );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool CanApplyEffect(CObj<PF_Core::BasicEffect> pEffect, NWorld::PFLogicObject* pOrigin, NWorld::PFLogicObject* pTarget )
{
  if (!pEffect)
    return false;
  if (!pEffect->GetDBDesc())
    return true;

  const NDb::EffectBase* const desc= pEffect->GetDBDesc();

  // TODO: почему именно эти эффекты?
  switch (desc->GetObjectTypeID())
  {
  case NDb::PlayAnimationEffect::typeId:
  case NDb::ScaleColorEffect::typeId:
    return true;
  default:
    break;
  }

  const bool visible =
    (pTarget->IsVisibleForFaction(AdventureScreen::Instance()->GetPlayerFaction())) ||
    (pOrigin && pOrigin->IsVisibleForFaction(AdventureScreen::Instance()->GetPlayerFaction()));

  if (visible)
    return true;

  switch (desc->GetObjectTypeID())
  {
  case NDb::EffectSwitcher::typeId:
    {
      NDb::Ptr<NDb::EffectSwitcher> native = static_cast<const NDb::EffectSwitcher*>(desc);

      if (native->effectOnInvisible && (native->effectOnInvisible->GetObjectTypeID() == NDb::BasicEffectAttached::typeId))
        return true;

      return native->isVisibleUnderWarfog;
    }
    break;
  case NDb::BasicEffectStandalone::typeId:
    {
      NDb::Ptr<NDb::BasicEffectStandalone> native = dynamic_cast<const NDb::BasicEffectStandalone*>(desc);

      return native->isVisibleUnderWarfog;
    }
    break;
  case NDb::LightningEffect::typeId:
    {
      NDb::Ptr<NDb::LightningEffect> native = static_cast<const NDb::LightningEffect*>(desc);

      return native->controlledVisibility;
    }
    break;
  case NDb::ChangeMaterialEffect::typeId:
  case NDb::EffectList::typeId:
  case NDb::EnableSCEffect::typeId:
    return true;
  default:
    if (PF_Core::BasicEffectAttached* effAtt = dynamic_cast<PF_Core::BasicEffectAttached*>(pEffect.GetPtr()))
      return true;
    break;
  }

  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ApplyEffect( CObj<PF_Core::BasicEffect> pEffect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  if ( !AdventureScreen::Instance()->IsSpectator() )
  {
    if( !CanApplyEffect(pEffect, pOrigin, pTarget) )
    {
      return;
    }
  }
  else
  {
    if ( !pEffect )
      return;
  }

  pEffect->SetEnableCallback(pEnableCallback);

  PF_Core::LightningEffect* pLightning = dynamic_cast<PF_Core::LightningEffect*>( pEffect.GetPtr() );
  if ( pLightning )
  {
    pLightning->Apply( pOrigin->ClientObject(), pTarget->ClientObject() );
  }
  else
  {
    pEffect->SetActiveStateName( pSender->GetSkinId() );
    pEffect->Apply( pTarget->ClientObject() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RestoreEffect(CObj<PF_Core::BasicEffect> pEffect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pTarget, NWorld::PFLogicObject* pOrigin, const Placement &placementOnStart, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  if( !CanApplyEffect(pEffect, pOrigin, pTarget) )
    return;

  pEffect->SetEnableCallback(pEnableCallback);

  typedef PF_Core::LightningEffect LghtEff;
  typedef PF_Core::BasicEffectStandalone StndEff;

  if ( LghtEff* pLght = dynamic_cast<LghtEff *>( pEffect.GetPtr() ) )
  {
    pLght->Apply( pOrigin->ClientObject(), pTarget->ClientObject() );
  }
  else if( StndEff* pStnd = dynamic_cast<StndEff *>( pEffect.GetPtr() ) )
  {
    pStnd->SetPosition( placementOnStart );
    pStnd->AddToScene( pTarget->GetWorld()->GetScene() );
  }
  else
  {
    pEffect->Apply( pTarget->ClientObject() );
  }

  // skip all animated changes
  pEffect->Update( 100 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillEffect(CObj<PF_Core::BasicEffect> &pEffect, bool waitTillAnimationFinish)
{
	if (IsValid(pEffect))
	{
		if (waitTillAnimationFinish)
    {
      pEffect->SetDeathType(NDb::EFFECTDEATHTYPE_ANIM);
    }
    else
    {
      pEffect->Die();
      pEffect = 0;
    }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlayEffect( NWorld::PFLogicObject* pUnit, const NDb::Ptr<NDb::EffectBase>& effect, NWorld::PFBaseUnit* pSender, NWorld::PFLogicObject* pOrigin, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
	CObj<PF_Core::BasicEffect> pEffect;
	CreateEffect(pEffect, effect, pSender, pUnit, pOrigin, pEnableCallback);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PF_Core::LightningEffect> CreateLightningEffect( const NDb::Ptr<NDb::LightningEffect>& pEffect, const string& skinId, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  pEffect.ChangeState(skinId);
  CObj<PF_Core::LightningEffect> lightningEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::LightningEffect>(pEffect);

  lightningEffect->SetEnableCallback(pEnableCallback);

  return lightningEffect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RetrieveStandaloneEffectCollection(StandaloneEffectsVector *effectList, NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  NI_VERIFY( _dispatchEffect, NStr::StrFmt( "Null dbptr in RetrieveStandaloneEffect" ) , return; );

  if (_dispatchEffect->GetObjectTypeID() == NDb::EffectList::typeId)
  {
    const NDb::EffectList * _effectList = static_cast<const NDb::EffectList *>(_dispatchEffect);
    nstl::vector<NDb::Ptr<NDb::EffectBase>>::const_iterator iter = _effectList->effects.begin();

    for(;iter !=  _effectList->effects.end();++iter)
    {
      RetrieveStandaloneEffect(effectList, *iter, pSender, pEnableCallback);
    }
  }
  else
  {
    RetrieveStandaloneEffect(effectList, _dispatchEffect, pSender, pEnableCallback);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PF_Core::BasicEffectStandalone> RetrieveStandaloneEffect( NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  bool needRegister = false;
  int curEffect = 0;
  NDb::Ptr<NDb::EffectBase> eff1;
  NDb::Ptr<NDb::EffectBase> eff2;
  const NDb::EffectBase* dispatchEffect = _dispatchEffect;

  CObj<PF_Core::BasicEffectStandalone> effect;

  NI_VERIFY( dispatchEffect, NStr::StrFmt( "Null dbptr in RetrieveStandaloneEffect" ) , return NULL );

  if (dispatchEffect->GetObjectTypeID() == NDb::EffectSwitcher::typeId)
  {
    needRegister = true;
    NDb::Ptr<NDb::EffectSwitcher> pEffSwitcher = static_cast<NDb::EffectSwitcher const*>(dispatchEffect);
    const NDb::Ptr<NDb::EffectBase> *ppSubEffect;
    // Logic of visibility selection

    eff1 = pEffSwitcher->effectOnVisible;
    eff2 = pEffSwitcher->effectOnInvisible;

    if (AdventureScreen::Instance()->GetPlayerFaction() == pSender->GetFaction())
    {
      ppSubEffect = &pEffSwitcher->effectOnVisible;
      curEffect = 0;
    }
    else
    {
      ppSubEffect = &pEffSwitcher->effectOnInvisible;
      curEffect = 1;
    }

    NI_VERIFY( ppSubEffect && *ppSubEffect, NStr::StrFmt( "Cannot find sub-effect in switch effect \"%s\"", pEffSwitcher->GetDBID().GetId().c_str() ), return NULL );

    ppSubEffect->ChangeState(pSender->GetSkinId());
    dispatchEffect = ppSubEffect->GetPtr();
    effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( dispatchEffect );
  }
  else
  {
    const NDb::Ptr<NDb::EffectBase> eff = dispatchEffect;
    eff.ChangeState(pSender->GetSkinId());
    effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( eff );
  }

  if ( AdventureScreen::Instance()->IsSpectator() )
  {
    if ( needRegister )
    {
      PF_Core::SpectatorEffectsPool::Get()->RegisterBasicEffectStandalone( effect.GetPtr(), eff1, eff2, curEffect );
    }
  }

  NI_VERIFY( effect, NStr::StrFmt( "Cannot retrieve standalone effect for \"%s\"", dispatchEffect->GetDBID().GetId().c_str() ), return NULL );

  effect->SetEnableCallback(pEnableCallback);

  return effect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RetrieveStandaloneEffect(StandaloneEffectsVector* effectVector, NDb::EffectBase const *_dispatchEffect, NWorld::PFBaseUnit const* pSender, PF_Core::IEffectEnableConditionCallback *pEnableCallback /*= NULL*/ )
{
  if(!effectVector) return;

  bool needRegister = false;
  int curEffect = 0;
  NDb::Ptr<NDb::EffectBase> eff1;
  NDb::Ptr<NDb::EffectBase> eff2;
  const NDb::EffectBase* dispatchEffect = _dispatchEffect;

  NI_VERIFY( dispatchEffect, NStr::StrFmt( "Null dbptr in RetrieveStandaloneEffect" ) , return ; );

  if (dispatchEffect->GetObjectTypeID() == NDb::EffectSwitcher::typeId)
	{
    needRegister = true;
    NDb::Ptr<NDb::EffectSwitcher> pEffSwitcher = static_cast<NDb::EffectSwitcher const*>(dispatchEffect);
		const NDb::Ptr<NDb::EffectBase> *ppSubEffect;
		// Logic of visibility selection

    eff1 = pEffSwitcher->effectOnVisible;
    eff2 = pEffSwitcher->effectOnInvisible;

    if (AdventureScreen::Instance()->GetPlayerFaction() == pSender->GetFaction())
		{
			ppSubEffect = &pEffSwitcher->effectOnVisible;
      curEffect = 0;
		}
		else
		{
			ppSubEffect = &pEffSwitcher->effectOnInvisible;
      curEffect = 1;
		}
    
    NI_VERIFY( ppSubEffect && *ppSubEffect, NStr::StrFmt( "Cannot find sub-effect in switch effect \"%s\"", pEffSwitcher->GetDBID().GetId().c_str() ), return );

    ppSubEffect->ChangeState(pSender->GetSkinId());
    dispatchEffect = ppSubEffect->GetPtr();

    if(dispatchEffect->GetObjectTypeID() == NDb::EffectList::typeId)
    {
      const NDb::EffectList * _effectList = static_cast<const NDb::EffectList *>(dispatchEffect);
      nstl::vector<NDb::Ptr<NDb::EffectBase>>::const_iterator iter = _effectList->effects.begin();

      for(;iter !=  _effectList->effects.end();++iter)
      {
        CObj<PF_Core::BasicEffectStandalone> &effect = effectVector->push_back();
        effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( *iter );
        effect->SetEnableCallback(pEnableCallback);

        NI_VERIFY( effect, NStr::StrFmt( "Cannot retrieve standalone effect for \"%s\"", dispatchEffect->GetDBID().GetId().c_str() ), return );
      }
    }
    else
    {
      CObj<PF_Core::BasicEffectStandalone> &effect = effectVector->push_back();
      effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( dispatchEffect );
      effect->SetEnableCallback(pEnableCallback);

      NI_VERIFY( effect, NStr::StrFmt( "Cannot retrieve standalone effect for \"%s\"", dispatchEffect->GetDBID().GetId().c_str() ), return );

      if ( AdventureScreen::Instance()->IsSpectator() )
      {
        if ( needRegister )
        {
          PF_Core::SpectatorEffectsPool::Get()->RegisterBasicEffectStandalone( effect.GetPtr(), eff1, eff2, curEffect );
        }
      }
    }
	}
  else
  {
    const NDb::Ptr<NDb::EffectBase> eff = dispatchEffect;
    eff.ChangeState(pSender->GetSkinId());

    CObj<PF_Core::BasicEffectStandalone> &effect = effectVector->push_back();
    effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( eff );
    effect->SetEnableCallback(pEnableCallback);

    NI_VERIFY( effect, NStr::StrFmt( "Cannot retrieve standalone effect for \"%s\"", dispatchEffect->GetDBID().GetId().c_str() ), return );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}