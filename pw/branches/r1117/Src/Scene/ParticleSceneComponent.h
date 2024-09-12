#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "../Render/ParticleFX.h"

namespace Render
{
class ParticleFX;
}

namespace NScene
{

class ParticleSceneComponent : public SceneComponent
{
  NDb::Ptr<NDb::DBParticleSceneComponent> pDBObj;

	float deathFadeOutTime;
	float dieTime;
	bool isSetWorldSpaceMatrix;

protected:
	float								time;
	bool                fixedSizeAABB;
	ScopedPtr<Render::ParticleFX> pParticles;

	ParticleSceneComponent() : time ( 0.f ), pParticles( 0 ), pDBObj( 0 ), deathFadeOutTime(0.0f), dieTime(0.0f), isSetWorldSpaceMatrix(false) {}

public:
	ParticleSceneComponent( const NDb::DBParticleSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );

	virtual void Reinit();
	virtual void OnTimeLooped(float time2StartWith);
	virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

  virtual void Attach( SceneComponent* toadd );
  virtual void DisableStrongWithWaitingForFinish();
  virtual bool Ready2Die();

	virtual void ForAllMaterials(Render::IMaterialProcessor &proc);
  virtual bool IsStayInWorld()
  {
    return SceneComponent::IsStayInWorld() || pParticles->IsWorldSpace();
  }

	virtual float GetPureAnimLength() /*const*/;

  void GetParticleAABB( Render::AABB& aabb )
  {
    if ( pParticles )
      pParticles->CalcWorldAABB( aabb );
  }

	void SetWorldMatrixForWorldSpace()
	{
		isSetWorldSpaceMatrix = true;
	}

};

}

