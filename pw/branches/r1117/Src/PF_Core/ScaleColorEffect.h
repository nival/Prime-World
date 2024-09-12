#pragma once

#include "BasicEffect.h"
#include "DBEffect.h"

namespace PF_Core
{

class ColorModificationChannel;

class ScaleColorEffect : public EffectDBLinker<NDb::ScaleColorEffect>
{
	OBJECT_METHODS( 0x9E691382, ScaleColorEffect )
public:
  ScaleColorEffect( const NDb::EffectBase &dbEffect ) : EffectBase( dbEffect ), pChannel( NULL ), shouldChangeColor( false ),
    curScale( 1.0f ), dbScale( 1.0f ), dbFadeInTime( 0.0f ), isVisible( true ), scaleIn( 1.0f ), scaleOut( 1.0f ) { }
	ScaleColorEffect() { }

  void Init();

	virtual void Apply( CPtr<PF_Core::ClientObjectBase> const& _pUnit );
  virtual void Die();
  virtual void Update( float timeDelta );
	virtual bool Ready2Die();

  void  SetDBFadeInTime( float _dbFadeInTime ) { dbFadeInTime = _dbFadeInTime; }
  float GetDBFadeInTime() const { return dbFadeInTime; }

protected:
  virtual void DieImmediate();
  virtual void Apply( float t, bool shouldChangeScale );

  void ApplyScale( float scale );

  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>> scaleInWrapper;
  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear>> scaleOutWrapper;
  float scaleIn;
  float scaleOut;

  float dbScale;
  float dbFadeInTime;

  bool shouldChangeColor;

	CPtr<PF_Core::ClientObjectBase> pUnit;
  float lifeTime;

  float curScale;

  float fadeOutStartTime;
  float fadeOutStartParam;
  CPtr<ColorModificationChannel> pChannel;

	bool isVisible;
};

}
