#include "stdafx.h"
#include "ParticleSceneComponent.h"
#include "RenderableScene.h"

#include "../System/InlineProfiler.h"

namespace NScene
{

static void SetOpacity( ParticleSceneComponent* sc, float opacity )
{
  struct Func : public Render::IMaterialProcessor, public NonCopyable
  {
    float opacity;

    Func(float o) : opacity(o) {}
    virtual void operator()(Render::BaseMaterial &material)
    {
      material.ModifyOpacity(opacity);
    }
  } f(opacity);

  sc->ForAllMaterials(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleSceneComponent::ParticleSceneComponent( const NDb::DBParticleSceneComponent* pObject, 
																							 const NDb::AttachedSceneComponent* pObj, 
																							 const Placement& pos )
:	SceneComponent(pObject, pObj, pos)
, time(0.f)
, pDBObj( pObject )
, deathFadeOutTime(0.5f)
, dieTime(0.0f)
, isSetWorldSpaceMatrix(false)
{
	bool needDoubleBuffering = false;
	NDb::Ptr<NDb::TimeController> pDBTimeController = timeController.GetDBDesc();
	if (pDBTimeController)
	{
		needDoubleBuffering = pDBTimeController->cycleCount != 1 && pDBTimeController->cycleLength > 0.0f;
    if ( pDBTimeController->fadein > 0.0f || pDBTimeController->fadeout > 0.0f )
    {
      needDoubleBuffering = false;
    }
	}
	
	deathFadeOutTime = pObject->deathFadeOutTime;

	Matrix43 offsetMatrix;
	offset.GetPlacement().GetMatrix( &offsetMatrix );
  {
    static volatile bool fake;
    Render::DeviceLostHandlerLoadable::LoaderCS lock(fake);
    Reset(pParticles, new Render::ParticleFX);
    pParticles->SetDBID(dbid);
    pParticles->Initialize( offsetMatrix, pObject, needDoubleBuffering );
  }


	if (pObject->aabb.minX < pObject->aabb.maxX && 
			pObject->aabb.minY < pObject->aabb.maxY && 
			pObject->aabb.minZ < pObject->aabb.maxZ)
	{
		// User specified fixed AABB for this component
		localAABB.Set(pObject->aabb);
		//
		worldAABB.Transform(offsetMatrix, localAABB);
		// 
		fixedSizeAABB = true;
	}
	else
	{
		worldAABB.center   = pos.pos;
		worldAABB.halfSize = CVec3( 1.0, 1.0, 1.0 );
		fixedSizeAABB = false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponent::OnTimeLooped(float time2StartWith)
{
	SceneComponent::OnTimeLooped(time2StartWith);
	pParticles->OnTimeLooped(timeController.GetTime(), time2StartWith);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  time = timeController.GetTime();

	Matrix43 worldMatrix;
	worldPlacement.GetMatrix( &worldMatrix );

  Render::SceneConstants const& sceneConsts = pars.pScene ? pars.pScene->GetSceneConstants() : Render::SceneConstants::Global();
	if ( isSetWorldSpaceMatrix )
	{
	  pParticles->SetWorldMatrixForWorldSpace( worldMatrix );
		isSetWorldSpaceMatrix = false;
	}
	else
	{
		pParticles->SetWorldMatrix( worldMatrix );
	}
  pParticles->SetTime( time );
  pParticles->Update(sceneConsts.campos);

  if ( pParticles )
  {
    float totalTime = pParticles->GetTotalTime()+deathFadeOutTime;
    if ( timeController.GetDBDesc().IsEmpty() || timeController.GetDBDesc()->cycleCount == 1 )
    {
      if ( totalTime <= time )
      {
        EnableWeak(false);
        SetOpacity(this, 0.0f);
      }
    }
  }

	if ( pParticles && pParticles->IsDying() )
	{
		float delta = NHPTimer::GetScalarTime()-dieTime;
		float opacity = 1.0f-delta/deathFadeOutTime;
		opacity = Clamp( opacity, 0.0f, 1.0f );
    SetOpacity(this, opacity);
	}

	// Calculate world AABB
	if (fixedSizeAABB)
	{
		worldAABB.Transform(worldMatrix, localAABB);
    NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );
		pars.objectAABB.Grow(worldAABB);
	}
	else
	{
		if (pParticles->CalcWorldAABB(worldAABB))
		{
      NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );
			pars.objectAABB.Grow(worldAABB);
		}
		else
		{
			worldAABB.center   = worldPlacement.pos;
			worldAABB.halfSize = VNULL3;
			if (!pars.objectAABB.IsValid())
				pars.objectAABB = worldAABB;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponent::Reinit()
{
  Matrix43 worldMatrix;
  worldPlacement.GetMatrix( &worldMatrix );
  pParticles->SetWorldMatrix(worldMatrix);
	SetWorldMatrixForWorldSpace();
	SceneComponent::Reinit();
	pParticles->Reinit();
	//Set opacity to 1.0
  SetOpacity(this, 1.0f);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
	SceneComponent::RenderToQueue( queue, sceneConstants );
  pParticles->RenderToQueue( queue );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ParticleSceneComponent::GetPureAnimLength()
{
	NI_ASSERT( pParticles->GetTotalTime()<1000.0f, NStr::StrFmt( "Bad animation length %s", GetDBID().GetFileName() ) );
	return Max(SceneComponent::GetPureAnimLength(), pParticles->GetTotalTime());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleSceneComponent::ForAllMaterials(Render::IMaterialProcessor &proc)
{
	if (pParticles)
	{
		proc(*pParticles->GetMaterial());
	}
}

void ParticleSceneComponent::Attach( SceneComponent* toadd )
{
  if ( !toadd )
    return;

  SceneComponent* it = toadd;
  do 
  {
    it->SetJointIdx( -1 );
    if ( it->GetLocatorName().length() && !pDBObj.IsEmpty() && !pDBObj->locatorList.IsEmpty() )
    {
      for ( int i = 0; i < pDBObj->locatorList->locators.size(); i++ )
      {
        if ( pDBObj->locatorList->locators[i].name == it->GetLocatorName() )
        {
          const NDb::Locator& locator = pDBObj->locatorList->locators[i];
          const Placement& offset = locator.offset2.GetPlace();
          it->SetLocatorPos( offset.pos, offset.rot, offset.scale );
          it->SetLocatorName( it->GetLocatorName(), pDBObj->locatorList->locators[i].flags );
          break;
        }
      }
    }
    it = it->GetBrother();
  } while ( it && it != toadd );

  SceneComponent::Attach( toadd );
}

void ParticleSceneComponent::DisableStrongWithWaitingForFinish()
{
  if ( pParticles )
	{
		dieTime = NHPTimer::GetScalarTime();
    pParticles->Die();
	}
  SceneComponent::DisableStrongWithWaitingForFinish();
}

bool ParticleSceneComponent::Ready2Die()
{
  if ( pParticles )
    return pParticles->Ready2Die();
  return SceneComponent::Ready2Die();
}
}
