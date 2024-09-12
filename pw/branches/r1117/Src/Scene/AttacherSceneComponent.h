#pragma once
#include "SceneComponent.h"
#include "SceneObject.h"

namespace NScene
{

/*
struct Policy
{
	typename XXX Object;
	static void Render(XXX* pO, class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants);
	static void Update(XXX* pO, const Placement &pl, float timeDiff);
	static void RetrieveWorldAABB(XXX* pO, Render::AABB &aabb);
	static void Reinit(XXX* pO);
	static void Deinit(XXX* pO);
};
*/

template <typename POLICY>
class AttacherSceneComponent : public SceneComponent
{
public:
	AttacherSceneComponent( typename POLICY::Object *pO ) : pObj(pO) {}

	virtual void Reinit() { POLICY::Reinit(pObj); }
	virtual void Deinit() { POLICY::Deinit(pObj); } 

	virtual void Update( UpdatePars &pars, const Placement& parentPos, float timeAdvance )
	{
		float timeDelta = 0;
		timeController.Update(*this, timeAdvance, timeDelta);
		offset.Step(timeDelta);

		// Update world placement
		ConstructWorldPlacement(parentPos, pars.pScene);

		// Set placement
		POLICY::Update(pObj, worldPlacement, timeDelta);

		// Copy world AABB
		POLICY::RetrieveWorldAABB(pObj, worldAABB);
		pars.objectAABB.Grow(worldAABB);
	}


	virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
	{
		POLICY::Render(pObj, queue, sceneConstants);
	}

protected:
	typename POLICY::Object *pObj;
};

}

