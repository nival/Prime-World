#pragma once

#include "BasicEffect.h"
#include "DBEffect.h"

namespace PF_Core
{

class ChangeMaterialEffect : public EffectDBLinker<NDb::ChangeMaterialEffect>
{
	OBJECT_METHODS( 0x9DAA1382, ChangeMaterialEffect )
public:
  ChangeMaterialEffect( const NDb::EffectBase &dbEffect ) : 
    EffectBase( dbEffect ), 
    dbFadeInTime(0.f), dbFadeOutTime(0.f), 
    curFadeInTime(0.f), curFadeOutTime(0.f),
    doFadeIn(false), doFadeOut(false)
  { }

	ChangeMaterialEffect() { }

  void Init();

	virtual void Apply( CPtr<PF_Core::ClientObjectBase> const& _pUnit );
  virtual void Die();
  virtual void Update( float timeDelta );
	virtual bool Ready2Die();

protected:
  virtual void DieImmediate();

private:
  void SetFading( bool fading );
  void ModifyBaseOpacity( float opacity );
  void ModifyAltEmissive( float power );
  void SetEnableAltPriority( bool state );

  CPtr<PF_Core::ClientObjectBase> pUnit;

  typedef nstl::vector<Render::BaseMaterial*> Materials;

  Materials baseMaterials;
  Materials altMaterials;


  float dbFadeInTime;
  float dbFadeOutTime;

  float curFadeInTime;
  float curFadeOutTime;

  bool doFadeIn;
  bool doFadeOut;
};

}
