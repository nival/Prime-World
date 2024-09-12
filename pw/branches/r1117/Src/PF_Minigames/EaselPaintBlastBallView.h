#pragma once

#include "MinigameClientObject.h"

#include "LuxBall.h"
#include "EaselLuxLerp.h"

namespace NDb
{
	struct DBSceneObject;
  enum EColor;
}

namespace PF_Core
{
  class BasicEffectStandalone;
}

namespace PF_Minigames
{

class Easel;
class Minigames;
class BallCoordsConverter;

class EaselPainBlastBallView : public MinigameClientObject
{
	OBJECT_METHODS(0x99639B00, EaselPainBlastBallView);
public:

	EaselPainBlastBallView();

  virtual void OnDestroyContents(); 

  ILuxViewLerp* GetLerpProcessor() const { return lerpBallPos; };

	bool Init(Easel& _easel, LuxBall* ball, BallCoordsConverter* _converter);

	virtual void Update(float deltaTime, bool gameOnPause);
  virtual void SetVisible( bool _visible );

private:
  void CheckExploded();
  void ShowEffect( bool show );

  // interpolation data
  CObj<ILuxViewLerp> lerpBallPos;
  
	CPtr<Easel> easel;
	CPtr<LuxBall> logicBall;
  bool exploded;

  NDb::EColor color;

  CObj<PF_Core::BasicEffectStandalone> effect;
};

} // PF_Minigames
