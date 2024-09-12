#pragma once
#include "SceneComponent.h"

class DiAnimGraph;

namespace NScene
{

class TimeCtrlSceneComponent : public SceneComponent
{
	TimeCtrlSceneComponent() : activeState(ST_INACTIVE), onDeactivateCB(NULL), SceneComponent(0, 0) { Activate(); }

public:
	typedef NDb::DBTimeCtrlSceneComponent NDbType;

  typedef void (*Callback)(TimeCtrlSceneComponent &tcsc, void *pData);

  enum State
  {
    ST_INACTIVE = 0,

    ST_PLAY,
    ST_FADE_OUT
  };

  enum Action
  {
    ACTION_ACTIVATE = 0,
    ACTION_DEACTIVATE
  };

  TimeCtrlSceneComponent(const NDb::DBTimeCtrlSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos)
    : SceneComponent(pObj, pObject),
			activeState(ST_INACTIVE),
      onDeactivateCB(NULL),
      duration(-1.f),
      loopTime(1.f),
      curLocalTime(0.f),
      lastUpdateLocalTime(0.f),
      numLoops(0),
      numLoopsToPlay(0)
  {
    pDBObject = pObject;
  }

  ~TimeCtrlSceneComponent() {}

  virtual void OnAfterAttached();
	virtual void Update( IScene *pScene, const Placement& parentPos, Render::AABB &objectAABB, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants ) {}

  State GetActiveState() const { return activeState; }
  void Activate();
  void Deactivate();

  bool SetupTriggeredAction(NDb::EAnimEventType evt, char const *name, float param, Action act);
  void SetOnDeactivateCB(Callback cb, void *pData) { onDeactivateCB = cb; pUserData = pData;}

  virtual bool IsTraversable() const { return (activeState != ST_INACTIVE); }

protected:
  DiAnimGraph *GetAnimGraph();

  NDb::Ptr<NDb::DBTimeCtrlSceneComponent> pDBObject;

  float   duration;
  float   loopTime;

  // run-time values
  float   curLocalTime;
  float   lastUpdateLocalTime;
  int     numLoops;
  int     numLoopsToPlay;
  
  State   activeState;
  float   activationTime;

  Callback     onDeactivateCB;
  void        *pUserData;
};

}

