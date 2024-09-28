#include "stdafx.h"

#include "EaselClient.h"
#include "MinigameClientObject.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/LightningEffect.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselClient::EaselClient() :
showAll( true )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::Reset( bool allObjects )
{
  for ( TClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); )
    if ( allObjects || !it->second )
      it = clientObjects.erase( it );
    else
      ++it;

  usedEffects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::AddObject( MinigameClientObject * object, bool permanent )
{
	clientObjects[object] = permanent;

  if ( !showAll )
    object->OverrideVisible( false );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::ReleaseObject( MinigameClientObject* object )
{
	if ( !IsValid(object) )
		return;

	CObj<MinigameClientObject> object2erase = object;
	clientObjects.erase( object2erase );
}


void EaselClient::ReleaseAll()
{
  clientObjects.clear();

  TEffects::iterator it = usedEffects.begin();
  TEffects::iterator last = usedEffects.end();

  for ( ; it != last; ++it )
  {
    (*it)->DieImmediate();
  }

  usedEffects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PF_Core::BasicEffectStandalone> EaselClient::CreateStandaloneEffect( const NDb::BasicEffectStandalone * dbEffect, bool trackLifetime )
{
  if ( !showAll )
    return 0;

  CObj<PF_Core::BasicEffectStandalone> eff = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectStandalone>( dbEffect );

  if ( trackLifetime )
  {
    NI_ASSERT( usedEffects.find( eff.GetPtr() ) == usedEffects.end()
      , NStr::StrFmt( "EaselClient: creating the same StandaloneEffect %s second time", dbEffect->GetDBID().GetFileName().c_str() ) );
    usedEffects.insert( eff.GetPtr() );
  }
  return eff;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PF_Core::BasicEffectAttached> EaselClient::CreateAttachedEffect( const NDb::BasicEffectAttached * dbEffect, bool trackLifetime )
{
  if ( !showAll )
    return 0;

  CObj<PF_Core::BasicEffectAttached> eff = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>( dbEffect );

  if ( trackLifetime )
  {
    NI_ASSERT( usedEffects.find( eff.GetPtr() ) == usedEffects.end()
      , NStr::StrFmt( "EaselClient: creating the same EffectAttached %s second time", dbEffect->GetDBID().GetFileName().c_str() ) );
    usedEffects.insert( eff.GetPtr() );
  }
  return eff;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<PF_Core::LightningEffect> EaselClient::CreateLightningEffect( const NDb::LightningEffect * dbEffect, bool trackLifetime )
{
  if ( !showAll )
    return 0;

  CObj<PF_Core::LightningEffect> eff = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::LightningEffect>( dbEffect );

  if ( trackLifetime )
  {
    NI_ASSERT( usedEffects.find( eff.GetPtr() ) == usedEffects.end()
      , NStr::StrFmt( "EaselClient: creating the same LightningEffect %s second time", dbEffect->GetDBID().GetFileName().c_str() ) );
    usedEffects.insert( eff.GetPtr() );
  }
  return eff;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::ReleaseEffect( PF_Core::BasicEffect * effect, bool immediate )
{
  if ( immediate )
    effect->DieImmediate();
  else
    effect->Die();

  //DevTrace("EaselClient::ReleaseEffect() [%x08], usedEffects count: %d", (int)this, usedEffects.size());

  if(usedEffects.size() != 0)
    usedEffects.erase( effect );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::ShowAll( bool show )
{
  if ( show == showAll )
    return;

  DebugTrace( "%s CLIENT", show ? "SHOW" : "HIDE" );

  showAll = show;
	for( TClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it )
    it->first->OverrideVisible( show );

  if ( !showAll )
  {
    for( TEffects::iterator it = usedEffects.begin(); it != usedEffects.end(); ++it )
      (*it)->Die();

    usedEffects.clear();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::Update( float deltaTime, bool gameOnPause )
{
  for ( TClientObjects::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it )
    it->first->Update( deltaTime, gameOnPause );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselClient::Step( float deltaTime )
{
  TClientObjects::iterator it = clientObjects.begin();
  const TClientObjects::iterator itEnd = clientObjects.end();
  for(; it != itEnd; ++it)
    it->first->Step( deltaTime );

  for( TEffects::iterator it = usedEffects.begin(); it != usedEffects.end(); )
  {
    TEffects::iterator e = it++;
    if ( (*e)->Ready2Die() )
      usedEffects.erase( e );
  }
}

} // PF_Minigames
