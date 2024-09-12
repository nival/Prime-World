#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "../Sound/EventScene.h"

namespace NScene
{

class SoundSceneComponent : public SceneComponent
{
  Placement position;

  bool isInited;

  float soundLength;

  FMOD::Event *soundEvent;
  NDb::DBFMODEventDesc desc;

  float timerInterval;
  float timer;

	SoundSceneComponent() :  soundEvent(0), soundLength(0.0f), isInited(false), timerInterval(0.0f), timer(0.0f) {}

public:
	typedef NDb::DBSoundSceneComponent NDbType;

	SoundSceneComponent( const NDb::DBSoundSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
	virtual ~SoundSceneComponent();

	virtual void Reinit();
  virtual void Deinit();
  virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

  virtual void ForceSoundPlay();

	virtual float GetPureAnimLength();
protected:
  virtual void OnTraversibleChanged();

};

}

