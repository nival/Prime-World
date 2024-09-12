#include "stdafx.h"

#include "WorldObject.h"
#include "ScaleColorEffect.h"
#include "EnableSCEffect.h"
#include "LightningEffect.h"
#include "EffectsPool.h"
#include "../Render/DxResourcesControl.h"

SINGLETON4DLL_DEF(PF_Core::EffectsPool)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<unsigned int> stats_EffectPoolsCount( "EffectPools", "Statistics" );
static NDebug::DebugVar<unsigned int> stats_Effects( "Effects", "Statistics" );


namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EffectsPool::EffectsPool( NDb::Ptr<NDb::EffectsPool> const& pDBEffects )
{
	pDBEffectsPool = pDBEffects;
	NI_VERIFY( IsValid( pDBEffectsPool ), NStr::StrFmt( "Invalid effects pool!" ), return; );

	// Create all objects pools
	const int size = NDb::KnownEnum<NDb::EEffects>::SizeOf();
	pools.resize(size);
	for (int i = 0; i < size; i++)
  {
		pools[i] = new ObjectsPool();
		stats_EffectPoolsCount.AddValue(1);
    
    if ( pDBEffectsPool->effectsList[i] )
    {
      typeToPoolMap[ pDBEffectsPool->effectsList[i]->GetDBID().GetHashKey() ] = i;
    }
  }
}

void EffectsPool::TearDown()
{
  pDBEffectsPool = 0;
  pools.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<BasicEffect> EffectsPool::RetrieveFactory(DWORD pool, NDb::Ptr<NDb::EffectBase> const &pDBObj)
{
  NI_VERIFY( IsValid( pDBObj ), "Invalid effect", return 0 );
  PushDXPoolGuard dxPool("Effects");

  
  int cnt = pools[pool]->GetObjectsCreatedCount();
	CObj<BasicEffect> pEffect = pDBObj->Retrieve(*pools[pool]);
	stats_Effects.AddValue(pools[pool]->GetObjectsCreatedCount() - cnt);

	return pEffect;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<BasicEffect> EffectsPool::Retrieve(NDb::EEffects effect)
{
	if (effect == NDb::EFFECTS_EMPTY)
	{
		return NULL;
	}
	return RetrieveFactory(effect, pDBEffectsPool->effectsList[effect]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<BasicEffect> EffectsPool::Retrieve(NDb::Ptr<NDb::EffectBase> const &pDBObj)
{
	int pool = -1;

	if (pDBObj.IsEmpty())
	{
		return NULL;
	}

	// find pool idx by type id
	TypeToPoolMap::iterator it = typeToPoolMap.find( pDBObj.GetStateDependentHashKey() );
	if ( it != typeToPoolMap.end() )
	{
		pool = it->second;
	}
	else
	{
		// not found -- create new pool
		pool = pools.size();
		typeToPoolMap[ pDBObj.GetStateDependentHashKey() ] = pool;
		pools.push_back( new ObjectsPool() );
		stats_EffectPoolsCount.AddValue(1);
	}

	return RetrieveFactory(pool, pDBObj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillAllActiveEffects()
{
	struct Func : public IUpdateableFunc 
	{
		virtual void operator()(IUpdateable *pObj)
		{
			BasicEffect *pEffect = dynamic_cast<BasicEffect*>(pObj);
			if (pEffect)
				pEffect->DieImmediate();
		}
	} f;

	IUpdateable::ForAll(f);
}

}

BASIC_REGISTER_CLASS(PF_Core::WorldObjectBase);