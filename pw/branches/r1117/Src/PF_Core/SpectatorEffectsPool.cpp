#include "stdafx.h"
#include "SpectatorEffectsPool.h"

#include "DBEffect.h"
#include "BasicEffect.h"


SINGLETON4DLL_DEF(PF_Core::SpectatorEffectsPool)


namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::RegisterEffectSwitcherImpl( ISpectatorSwitchEffect* sse ) 
{
  if ( sseEffects.find(sse) == sseEffects.end() )
    sseEffects.push_back( sse );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::UnregisterEffectSwitcherImpl( ISpectatorSwitchEffect* sse ) 
{
  for ( int i = 0; i < sseEffects.size(); ++i )
  {
    if ( sseEffects[i] == sse )
    {
      sseEffects.erase( sseEffects.begin()+i );
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::ReinitAllEffectSwitchersImpl()
{
  for ( int i = 0; i < sseEffects.size(); ++i )
  {
    if (IsValid(sseEffects[i]))
      sseEffects[i]->Switch();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::RegisterBasicEffectStandaloneImpl( BasicEffectStandalone* bes, const NDb::Ptr<NDb::EffectBase>& eff1, const NDb::Ptr<NDb::EffectBase>& eff2, int cur )
{
  for ( int i = 0; i < besEffects.size(); ++i )
  {
    if ( besEffects[i].effect == bes )
      return;
  }

  BESInfo & info = besEffects.push_back();
  info.effect = bes;
  info.dbEffect[0] = eff1;
  info.dbEffect[1] = eff2;
  info.curEffect = cur;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::UnregisterBasicEffectStandaloneImpl( BasicEffectStandalone* bes ) 
{
  for ( int i = 0; i < besEffects.size(); ++i )
  {
    if ( besEffects[i].effect == bes )
    {
      besEffects.erase( besEffects.begin() + i );
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpectatorEffectsPool::ReinitAllBasicEffectStandalonesImpl()
{
  for ( int i = 0; i < besEffects.size(); ++i )
  {
    BESInfo & besInfo = besEffects[i];
    //TODO: uncomment, when besInfo.effect will be CPtr
    //NI_VERIFY(IsValid(besInfo.effect), "Dead effect in spectator's effects pool!", continue;);
    const NDb::Ptr<NDb::EffectBase>& eff = besInfo.curEffect == 0 ? besInfo.dbEffect[1] : besInfo.dbEffect[0];
    besInfo.curEffect = !besInfo.curEffect;
    besInfo.effect->SwitchEffect( eff );
  }
}

} // namespace PF_Core

BASIC_REGISTER_CLASS(PF_Core::ISpectatorSwitchEffect);
