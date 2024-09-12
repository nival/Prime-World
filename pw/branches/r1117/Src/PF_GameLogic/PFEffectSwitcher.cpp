#pragma once

#include "stdafx.h"
#include "PFEffectSwitcher.h"
#include "PFClientLogicObject.h"
#include "PFLogicConst.h"

#include "ClientVisibilityHelper.h"

namespace NGameX
{
 
  PFEffectSwitcher::PFEffectSwitcher( const NDb::EffectBase& dbEffect) : EffectBase( dbEffect )
    , fadeInTime( 0.0f )
    , isFadeInTimeOverrided( false )
    , switchByVisibility( false ) 
    , lastVisible( false )
    , pEnableCallback(0)
  {
  }

  PFEffectSwitcher::~PFEffectSwitcher()
  {
    PF_Core::SpectatorEffectsPool::Get()->UnregisterEffectSwitcher(this);
  }

  void PFEffectSwitcher::Init()
  {
    EffectDBLinker::Init();

    PF_Core::SpectatorEffectsPool::Get()->RegisterEffectSwitcher(this);
  }

  void PFEffectSwitcher::Apply( CPtr<PF_Core::ClientObjectBase> const &pObject )
  {
    if ( IsValid( pObject ) )
      Apply(pObject, static_cast<NDb::EFaction>(FACTION_UNKNOWN));
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFEffectSwitcher::Apply( CPtr<PF_Core::ClientObjectBase> const &pObject, NDb::EFaction senderFaction)
  {
    PF_Core::SpectatorEffectsPool::Get()->RegisterEffectSwitcher(this);

    if ( !IsValid( pObject ) )
      return;

    pUnit = pObject;

    const CDynamicCast<PFClientLogicObject> pClientLogicObject(pObject.GetPtr());

    NI_DATA_VERIFY(IsValid(pClientLogicObject),
      NStr::StrFmt("Effect %s could not be applied on logic object", GetDBEffect().GetDBID().GetFileName().c_str()), 
      return; );

    const NWorld::PFLogicObject* const pLogicObject = pClientLogicObject->WorldObject();

    const NDb::EFaction receiverFaction = pLogicObject->GetFaction();
    const NDb::EFaction playerFaction = ClientVisibilityHelper::GetPlayerFaction();

    bool isEffectVisible = (receiverFaction == playerFaction);

    switch (GetDBEffect().logic)
    {
    case NDb::EFFECTSWITCHLOGIC_FACTIONVISIBILITY:
      origAction = EFFECT_SWITCHER_APPLY_FACTIONVISIBILITY;
      origSourceFaction = receiverFaction;

      if (switchByVisibility)
        isEffectVisible = isEffectVisible || ClientVisibilityHelper::IsVisibleForPlayer(pLogicObject);

      break;
    case NDb::EFFECTSWITCHLOGIC_SENDERFACTION:
      origAction = EFFECT_SWITCHER_APPLY_SENDERFACTION;
      origSourceFaction = senderFaction;

      if (senderFaction != FACTION_UNKNOWN)
        isEffectVisible = (senderFaction == playerFaction);

      break;
    }

    // Logic of visibility selection
    SetEffect(isEffectVisible);
  }

  // Only for Invisibility Applicator!
  void PFEffectSwitcher::SwitchEffect( bool visible, CPtr<PF_Core::ClientObjectBase> const &pObject )
  {
    if ( !IsValid( pObject ) )
      return;

    origAction = EFFECT_SWITCHER_APPLY_SWITCH;
    origVisible = visible;

    pUnit = pObject;

    // return if new effect is old one
    if ( !effects.empty() && visible == lastVisible )
      return;

    SetEffect( visible );
  }

  void PFEffectSwitcher::SetEffect( bool visible )
  {
    NDb::Ptr<NDb::EffectBase> pDBEffect;

    origVisible = visible;

    if ( visible )
    {
      pDBEffect = GetDBEffect().effectOnVisible;
      lastVisible = true;
    }
    else
    {
      pDBEffect = GetDBEffect().effectOnInvisible;
      lastVisible = false;
    }

    DieEffects();

    ApplyEffect( pDBEffect );
  }

  void PFEffectSwitcher::ApplyEffect( NDb::Ptr<NDb::EffectBase> const& pDBEffect )
  {
    if (pDBEffect)
    {
      NDb::Ptr<NDb::EffectBase> pDBEffectSwitcher(&GetDBEffect());

      if ( pDBEffect->GetObjectTypeID() == NDb::EffectList::typeId )
      {
        const vector<NDb::Ptr<NDb::EffectBase>>& vecEffects = static_cast<NDb::EffectList const*>(pDBEffect.GetPtr())->effects;
        effects.resize(vecEffects.size());
        for ( int i = 0, cnt = vecEffects.size(); i < cnt; i++ )
        {
          PrepareAndApplyChildEffect( vecEffects[i], effects[i] );
        }
      }
      else
      {
        effects.resize(1);
        PrepareAndApplyChildEffect( pDBEffect, effects[0] );
      }
    }
  }

  void PFEffectSwitcher::SetDBFadeInTime( float _time )
  {
    isFadeInTimeOverrided = true;
    fadeInTime = _time;
  }

  void PFEffectSwitcher::PrepareAndApplyChildEffect( NDb::Ptr<NDb::EffectBase> const& pDBEffect, CObj<BasicEffect>& pEffect )
  {
    pDBEffect.ChangeState(stateName);
    pEffect = PF_Core::EffectsPool::Get()->Retrieve(pDBEffect);

    NI_VERIFY( pEffect, NI_STRFMT( "Can't retrieve effect %s for EffectSwitcher", pDBEffect->GetDBID().GetFormatted().c_str() ), return );

    if ( isFadeInTimeOverrided && ( pDBEffect->GetObjectTypeID() == NDb::InvisibilityEffect::typeId ) )
    {
      PF_Core::ScaleColorEffect* pScaleColorEffect = static_cast<PF_Core::ScaleColorEffect*>( pEffect.GetPtr() );
      pScaleColorEffect->SetDBFadeInTime( fadeInTime );
    }

    pEffect->SetEnableCallback(pEnableCallback);
    pEffect->Apply( pUnit );

    SetDeathType( pDBEffect->deathType, pEffect->GetLifeTime() );
  }

  void PFEffectSwitcher::SetSwitchByVisibility()
  {
    switchByVisibility = true;
  }

  void PFEffectSwitcher::Die()
  {
    PF_Core::SpectatorEffectsPool::Get()->UnregisterEffectSwitcher(this);

    DieEffects();

    BasicEffect::Die();
  }

  void PFEffectSwitcher::DieImmediate()
  {
    PF_Core::SpectatorEffectsPool::Get()->UnregisterEffectSwitcher(this);

    BasicEffect::DieImmediate();
  }

  void PFEffectSwitcher::DieEffects()
  {
    if ( effects.empty() )
      return;

    for ( int i = 0; i < effects.size(); i++ )
    {
      if ( effects[i] )
      {
        effects[i]->Die();
        effects[i] = 0;
      }
    }

    effects.clear();
  }

  void PFEffectSwitcher::Switch()
  { 
    if (IsValid(pUnit))
    {
      switch (origAction)
      {
      case EFFECT_SWITCHER_APPLY_FACTIONVISIBILITY:
        Apply(pUnit);
        break;
      case EFFECT_SWITCHER_APPLY_SENDERFACTION:
        Apply(pUnit, origSourceFaction);
        break;
      case EFFECT_SWITCHER_APPLY_SWITCH:
        SwitchEffect(origVisible, pUnit);
        break;
      };
    }
  }

  nstl::string PFEffectSwitcher::GetDBInfo()
  {
    return GetDBEffect().GetDBID().GetFormatted();
  }

}

BASIC_REGISTER_CLASS(NGameX::PFEffectSwitcher)