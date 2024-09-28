#include "stdafx.h"

#include "ScaleColorEffect.h"
#include "ColorModificationChannel.h"

namespace PF_Core
{

struct TurnOnOff : public NScene::TraverserByGroupFlags
{
  bool turnOff;
  bool fullRecolor;

  TurnOnOff( bool turnOff, bool _fullRecolor ) : NScene::TraverserByGroupFlags( 0, true ), turnOff( turnOff ), fullRecolor( _fullRecolor )	{}

  bool NeedToProcess(const NScene::SceneComponent* comp) const
  {
    enum
    {
      flagEffectIgnoreColorModification = NDb::EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION | NScene::SceneComponent::GROUPFLAGS_EFFECT,
      flagEffectRecolorable = NDb::GROUPFLAGS_RECOLORABLE | NScene::SceneComponent::GROUPFLAGS_EFFECT,
      flagRecolorable = NDb::GROUPFLAGS_RECOLORABLE,
    };

    const int flags = comp->GetGroupFlags();

    if ((flags & flagEffectIgnoreColorModification) == flagEffectIgnoreColorModification)
      return false;

    if ((flags & flagEffectRecolorable) == flagRecolorable)
      return true;

    return fullRecolor;
  }

  void operator()( NScene::SceneComponent* comp ) const 
  {
    comp->SetHide( turnOff );
  }
};

void ScaleColorEffect::Init()
{
  const NDb::ScaleColorEffect& DB = GetDBEffect();

  fadeOutStartTime  = -1.0f;
  fadeOutStartParam = 0.0f;
  lifeTime = 0.0f;
  dbFadeInTime = DB.fadeInTime;
  dbScale = DB.scale;
  curScale = 1.0f;
  isVisible = true;

  if ( DB.scaleIn.IsAnimated() )
  {
    scaleInWrapper.Init( &scaleIn, DB.scaleIn, 0.0f );
  }
  if ( DB.scaleOut.IsAnimated() )
  {
    scaleOutWrapper.Init( &scaleOut, DB.scaleOut, 0.0f );
  }

  shouldChangeColor = ( ( DB.colorMul.R < 1.0f ) || ( DB.colorMul.G < 1.0f ) || ( DB.colorMul.B < 1.0f ) || ( DB.colorMul.A < 1.0f ) ) ||
    ( ( DB.colorAdd.R > 0.0f ) || ( DB.colorAdd.G > 0.0f ) || ( DB.colorAdd.B > 0.0f ) || ( DB.colorAdd.A > 0.0f ) );

	BasicEffect::Init();
}

void ScaleColorEffect::Apply( CPtr<PF_Core::ClientObjectBase> const& _pUnit )
{
  const NDb::ScaleColorEffect& DB = GetDBEffect();

  pUnit = _pUnit;

  if( IsValid( pUnit ) && shouldChangeColor )
  {
    pChannel = pUnit->CreateColorModificationChannel( PF_Core::CMC_EFFECT1, DB.fullRecolor );
    pChannel->SetMulColor( DB.colorMul );
    pChannel->SetAddColor( DB.colorAdd );
    pChannel->SetOpacity( 1.0f );
    pChannel->SetBlendMode( DB.blendMode );
  }
}

void ScaleColorEffect::Apply( float t, bool shouldChangeScale )
{
  using NScene::SceneObject;

  if (!IsValid(pUnit))
    return;

  if (shouldChangeScale)
  {
    ApplyScale( ( 1.0f - t ) + t * dbScale );
  }

  if (!IsValid(pChannel))
    return;

  if (shouldChangeColor)
  {
    pChannel->SetOpacity( 1.0f - t );

    const NDb::ScaleColorEffect& DB = GetDBEffect();

    if (DB.colorAdd.A > 0.0f || DB.colorMul.A > 0.0f)
      return;

    if (t < 1.0f)
    {
      if (!isVisible)
      {
        isVisible = true;

        if (SceneObject* const sceneObject = pUnit->GetSceneObject())
        {
          TurnOnOff f(false, DB.fullRecolor);
          sceneObject->Traverse(f);
        }
      }
    }
    else
    {
      if (isVisible)
      {
        isVisible = false;

        if (SceneObject* const sceneObject = pUnit->GetSceneObject())
        {
          TurnOnOff f(true, DB.fullRecolor);
          sceneObject->Traverse(f);
        }
      }
    }
  }
}

void ScaleColorEffect::ApplyScale( float scale )
{
  float scaleDiff = scale / curScale;

  if ( IsValid( pUnit ) )
  {
    pUnit->MultiplyTemporaryScale( scaleDiff );
    pUnit->MultiplyAnimSpeed( scaleDiff );
  }

  curScale = scale;
}

void ScaleColorEffect::Die() 
{
  if ( bDying )
  {
    return;
  }

  const NDb::ScaleColorEffect& DB = GetDBEffect();

  bDying = true;
  timePassed = 0.0f;

  if ( DB.fadeOutTime == 0.0f )
  {
    Apply( 0.0f, true );
    DieImmediate();
    return;
  }

  fadeOutStartTime = lifeTime;
  fadeOutStartParam = 1.0f;
  if ( ( dbFadeInTime > 0.0f ) && ( lifeTime < dbFadeInTime ) )
  {
    fadeOutStartParam = lifeTime / dbFadeInTime;
  }
}

void ScaleColorEffect::DieImmediate()
{
  EffectBase::DieImmediate();

  if( IsValid(pChannel) )
  {
    pUnit->RemoveColorModificationChannel( pChannel );
    pChannel = NULL;
  }

  pUnit = 0;
}

void ScaleColorEffect::Update( float timeDelta )
{
  const NDb::ScaleColorEffect& DB = GetDBEffect();

  BasicEffect::Update( timeDelta );

	if ( !IsValid( pUnit ) )
		return;

	NI_ASSERT( ( fadeOutStartTime < 0.0f ) || ( ( lifeTime - fadeOutStartTime ) < DB.fadeOutTime ), "Effect is dead already" );

  lifeTime += timeDelta;

  if ( fadeOutStartTime >= 0.0f )
  {
    if ( ( lifeTime - fadeOutStartTime ) < DB.fadeOutTime )
    {
      // fade-out phase
      float relativeScale = ( 1.0f - ( lifeTime - fadeOutStartTime ) / DB.fadeOutTime ) * fadeOutStartParam;
      bool shouldChangeScale = true;
      if ( DB.scaleOut.IsAnimated() )
      {
        scaleOutWrapper.Step( timeDelta * scaleOutWrapper.GetLength() / DB.fadeOutTime );
        const float animBeginScale = DB.scaleOut.GetPoint( DB.scaleOut.begin() ).y;
        const float animEndScale   = DB.scaleOut.GetPoint( DB.scaleOut.end() - 1 ).y;
        if ( abs( animEndScale - animBeginScale ) <= EPS_VALUE )
        {
          NI_DATA_VERIFY( abs( dbScale - 1.0f ) <= EPS_VALUE, "ScaleColorEffect: scale must be equal 1 if scales in {0} and {1} are equal! Setting scale to 1.", dbScale = 1.0f );
          ApplyScale( scaleOut - animEndScale + 1.0f );
          shouldChangeScale = false;
        }
        else
        {
          NI_DATA_ASSERT( Sign( animBeginScale - animEndScale ) == Sign( dbScale - 1.0f ), "ScaleColorEffect: bad ratio of scale and animated variable!" );
          relativeScale = ( scaleOut - animEndScale ) / ( animBeginScale - animEndScale );
        }
      }
      Apply( relativeScale, shouldChangeScale );
    }
    else
    {
      Apply( 0.0f, true );
      DieImmediate();
    }
  }
  else if ( lifeTime < dbFadeInTime )
  {
    // fade-in phase
    float relativeScale = lifeTime / dbFadeInTime;
    bool shouldChangeScale = true;
    if ( DB.scaleIn.IsAnimated() )
    {
      scaleInWrapper.Step( timeDelta * scaleInWrapper.GetLength() / dbFadeInTime );
      const float animBeginScale = DB.scaleIn.GetPoint( DB.scaleIn.begin() ).y;
      const float animEndScale   = DB.scaleIn.GetPoint( DB.scaleIn.end() - 1 ).y;
      if ( abs( animEndScale - animBeginScale ) <= EPS_VALUE )
      {
        NI_DATA_VERIFY( abs( dbScale - 1.0f ) <= EPS_VALUE, "ScaleColorEffect: scale must be equal 1 if scales in {0} and {1} are equal! Setting scale to 1.", dbScale = 1.0f );
        ApplyScale( scaleIn - animBeginScale + 1.0f );
        shouldChangeScale = false;
      }
      else
      {
        NI_DATA_ASSERT( Sign( animEndScale - animBeginScale ) == Sign( dbScale - 1.0f ), "ScaleColorEffect: bad ratio of scale and animated variable!" );
        relativeScale = ( scaleIn - animBeginScale ) / ( animEndScale - animBeginScale );
      }
    }
    Apply( relativeScale, shouldChangeScale );
  }
  else
  {
    // full phase
    Apply( 1.0f, true );
  }
}

bool ScaleColorEffect::Ready2Die()
{
	if ( !IsValid( pUnit ) || GetDBEffect().fadeOutTime == 0.0f )
		return true;
	return ( lifeTime - fadeOutStartTime ) > GetDBEffect().fadeOutTime;
}
}
BASIC_REGISTER_CLASS( PF_Core::ColorModificationChannel );