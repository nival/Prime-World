#pragma once

#include "ObjectsPool.h"
#include "DBEffect.h"
#include "BasicEffect.h"
#include "ControlledStatusEffect.h"
#include "../System/Singleton4DLL.h"

namespace PF_Core
{

// Create somewhere on loading
class EffectsPool : public Singleton4DLL<EffectsPool>
{
public:
  typedef nstl::hash_map<DWORD, DWORD>  TypeToPoolMap;

	EffectsPool( NDb::Ptr<NDb::EffectsPool> const& pDBEffects );

	CObj<BasicEffect> Retrieve(NDb::EEffects effect);
	CObj<BasicEffect> Retrieve(NDb::Ptr<NDb::EffectBase> const &pDBObj);

	template <class T, typename PARAM>
	CObj<T> RetrieveKnownEffect(PARAM effect)
	{
		CObj<BasicEffect> pEffect = Retrieve(effect);
		if (!pEffect)
			return CObj<T>();

		T *pEffectKnown = dynamic_cast<T*>(pEffect.GetPtr());
		NI_VERIFY(pEffectKnown, 
			        NStr::StrFmt("Effect type assumed by user (%s) doesn't correspond to real effect type in database (%s)", 
													 T::GetTypeName(), pEffect->GetObjectTypeName()), ; );
		return CObj<T>(pEffectKnown);
	}

	template <class T>
	CObj<T> Retrieve(NDb::Ptr<typename T::DBType> const &pDBObj)
	{
		return RetrieveKnownEffect<T>(NDb::Ptr<NDb::EffectBase>(pDBObj.GetPtr()));
	}

  void TearDown();

private:
  virtual CObj<BasicEffect> RetrieveFactory(DWORD pool, NDb::Ptr<NDb::EffectBase> const &pDBObj);

	NDb::Ptr<NDb::EffectsPool> pDBEffectsPool;
	vector<CObj<ObjectsPool> > pools;
  TypeToPoolMap  typeToPoolMap;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
BasicEffect* CreateEffectFromPool(const NDb::EffectBase &dbObj, ObjectsPool &pool)
{
	return pool.Retrieve<T>(dbObj);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KillAllActiveEffects();

}
