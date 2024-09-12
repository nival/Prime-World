#pragma once

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/ScaleColorEffect.h"
#include "../PF_Core/SpectatorEffectsPool.h"
#include "DBPFEffect.h"

namespace NScene { _interface IScene; }

namespace NGameX
{

class PFClientBaseUnit;

enum PFEffectSwitcherApplyLogic
{
  EFFECT_SWITCHER_APPLY_SENDERFACTION,
  EFFECT_SWITCHER_APPLY_FACTIONVISIBILITY,
  EFFECT_SWITCHER_APPLY_SWITCH
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFEffectSwitcher : public PF_Core::EffectDBLinker<NDb::EffectSwitcher>, public PF_Core::ISpectatorSwitchEffect
{
  OBJECT_BASIC_METHODS( PFEffectSwitcher )

public:
  PFEffectSwitcher() : pEnableCallback(0) {}
	PFEffectSwitcher( const NDb::EffectBase& dbEffect);
  ~PFEffectSwitcher();

  virtual void Init();

	virtual void Apply( CPtr<PF_Core::ClientObjectBase> const &pObject );
  virtual void Apply(CPtr<PF_Core::ClientObjectBase> const &pObject, NDb::EFaction senderFaction);

  void SetDBFadeInTime( float _time );

  void SetSwitchByVisibility();

  void SwitchEffect( bool visible, CPtr<PF_Core::ClientObjectBase> const &pObject );
  
  void ApplyEffect( NDb::Ptr<NDb::EffectBase> const& pDBEffect );

  void SetActiveStateName(const string& name) {stateName = name;}

  virtual void Switch();
  virtual nstl::string GetDBInfo();
  
protected:
	virtual void Die();
	virtual void DieImmediate();

private:
  void SetEffect( bool visible );
  void DieEffects();
  void PrepareAndApplyChildEffect( NDb::Ptr<NDb::EffectBase> const& pDBEffect, CObj<BasicEffect>& pEffect );

  virtual void SetEnableCallback(PF_Core::IEffectEnableConditionCallback *pCallback) { pEnableCallback = pCallback; }

  CPtr<PF_Core::ClientObjectBase> pUnit;
	vector<CObj<BasicEffect>> effects;
  float fadeInTime;
  bool isFadeInTimeOverrided;
  bool switchByVisibility;
  string stateName;
  bool lastVisible;
  CPtr<PF_Core::IEffectEnableConditionCallback> pEnableCallback;

  PFEffectSwitcherApplyLogic origAction;
  NDb::EFaction origSourceFaction;
  bool origVisible;
};

}
