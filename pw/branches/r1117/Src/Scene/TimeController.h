#pragma once

namespace NDb
{
	struct TimeController;
}

namespace NScene
{

class SceneComponent;

class TimeController
{
public:
	TimeController() : pDBData(NULL), pureAnimationLength(0.0f), time(0.0f), 
    speed(1.0f), numCycles2Loop(-1), tryToFinish(false) {}
	TimeController(NDb::Ptr<NDb::TimeController> pDBTC) 
		: pDBData(pDBTC)
	  , pureAnimationLength(0.0f)
    , time(0.0f)
    , speed(1.0f)
    , numCycles2Loop(-1)
    , timeOffset(0.f)
    , tryToFinish(false)
	{
  }

	void Set(NDb::Ptr<NDb::TimeController> pDBTC) { pDBData = pDBTC; }
  NDb::Ptr<NDb::TimeController> GetDBDesc() const { return pDBData; }

	void Reinit(SceneComponent &sc);
	void Update(SceneComponent &sc, float timeAdvance, float &timeDelta);
	void Finish(SceneComponent &sc);

	float GetTime() const { return time; }

	void SetPureAnimationLength(float length);
	float EvaluateAnimLength( const SceneComponent &sc ) const;

	void SetSpeed(float s) { speed = s; }
	float GetSpeed() const { return speed; }
	void ResetSpeed();

	int  GetCyclesToLoop() const { return numCycles2Loop; }

private:
  float GenerateFirstCycleOffset();

	NDb::Ptr<NDb::TimeController> pDBData;
	float time;
	float speed;
	int   numCycles2Loop;
	float pureAnimationLength;
  float timeOffset; // used for one-time offset
  bool tryToFinish;
};

}