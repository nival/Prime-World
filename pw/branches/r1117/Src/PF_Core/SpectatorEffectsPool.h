#pragma once

#include "System/Singleton4DLL.h"


namespace NGameX
{
  class PFEffectSwitcher;
}

namespace NDb
{
  struct EffectBase;
}


namespace PF_Core
{
class BasicEffectStandalone;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ISpectatorSwitchEffect : public IObjectBase
{
  virtual void Switch() = 0;
  virtual ~ISpectatorSwitchEffect() {}
  virtual nstl::string GetDBInfo() = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SpectatorEffectsPool
  : public Singleton4DLL<PF_Core::SpectatorEffectsPool>
  , public NonCopyable
{
  struct BESInfo
  {
    NDb::Ptr<NDb::EffectBase> dbEffect[2];
    int curEffect;
    // TODO: Fix problem with "Special debug code" in BasicEffect::Update before making it CPtr
    //CPtr<PF_Core::BasicEffectStandalone> effect;
    PF_Core::BasicEffectStandalone * effect;
  };

  typedef vector<CPtr<ISpectatorSwitchEffect> > TSwitchEffects;
  typedef vector<BESInfo> TBaseEffects;

  TSwitchEffects sseEffects;
  TBaseEffects besEffects;

  const bool isSpectator;

  void RegisterEffectSwitcherImpl( ISpectatorSwitchEffect* sse ); 
  void UnregisterEffectSwitcherImpl( ISpectatorSwitchEffect* sse );
  void ReinitAllEffectSwitchersImpl();

  void RegisterBasicEffectStandaloneImpl( BasicEffectStandalone* bes, const NDb::Ptr<NDb::EffectBase>& eff1, const NDb::Ptr<NDb::EffectBase>& eff2, int cur ); 
  void UnregisterBasicEffectStandaloneImpl( BasicEffectStandalone* bes );
  void ReinitAllBasicEffectStandalonesImpl();
public:
  SpectatorEffectsPool() : isSpectator( false ) {}
  SpectatorEffectsPool( bool _isSpectator ) : isSpectator( _isSpectator ) {}

  bool IsSpectator() const { return isSpectator; }

  inline void RegisterEffectSwitcher( ISpectatorSwitchEffect* sse )
  {
    if (!isSpectator)
      return;
    if (!sse)
      return;

    RegisterEffectSwitcherImpl(sse);
  }

  inline void UnregisterEffectSwitcher( ISpectatorSwitchEffect* sse )
  {
    if (!isSpectator)
      return;
    if (!sse)
      return;

    UnregisterEffectSwitcherImpl(sse);
  }

  inline void ReinitAllEffectSwitchers()
  {
    if (!isSpectator)
      return;

    ReinitAllEffectSwitchersImpl();
  }

  inline void RegisterBasicEffectStandalone( BasicEffectStandalone* bes, const NDb::Ptr<NDb::EffectBase>& eff1, const NDb::Ptr<NDb::EffectBase>& eff2, int cur )
  {
    if (!isSpectator)
      return;
    if (!bes)
      return;

    RegisterBasicEffectStandaloneImpl(bes, eff1, eff2, cur);
  }

  inline void UnregisterBasicEffectStandalone( BasicEffectStandalone* bes )
  {
    if (!isSpectator)
      return;
    if (!bes)
      return;

    UnregisterBasicEffectStandaloneImpl(bes);
  }

  inline void ReinitAllBasicEffectStandalones()
  {
    if (!isSpectator)
      return;

    ReinitAllBasicEffectStandalonesImpl();
  }
};

} // namespace PF_Core
