#pragma once

#include "MovingUnitClientObject.h"

#include "LuxPlatform.h"
#include "EaselLuxLerp.h"

namespace PF_Core
{
  class BasicEffectAttached;
  class BasicEffectStandalone;
  class LightningEffect;
}

namespace PF_Minigames
{

class Easel;
class Minigames;
class LuxPlatform;

class EaselLuxViewPlatform : public MinigameClientObject // MovingUnitClientObject
{
	OBJECT_METHODS(0x9963A240, EaselLuxViewPlatform);
public:

  EaselLuxViewPlatform();
  virtual void OnDestroyContents();

  ILuxViewLerp* GetLerpProcessor() const { return lerpPlatformPos; };

	bool InitPlatform(Easel& _easel, LuxPlatform* platform);

	virtual void Update(float deltaTime, bool gameOnPause);

  bool GetLaserPointA( CVec3& _pos ) const;
  bool GetLaserPointB( CVec3& _pos ) const;

private:
  void ShowLaserEffects();
  void HideLaserEffects();
  void InitLaserEffect( CObj<PF_Core::LightningEffect>& laser, const NDb::LightningEffect* dbEffect );

  CObj<ILuxViewLerp> lerpPlatformPos;
  bool showPointer;
  CPtr<LuxPlatform> platform;
	CPtr<Easel> easel;

  CObj<PF_Core::BasicEffectAttached> sourceEffect;
  CObj<PF_Core::BasicEffectStandalone> targetEffect;
  CObj<PF_Core::LightningEffect> laserEffect1;
  CObj<PF_Core::LightningEffect> laserEffect2;
};

} // PF_Minigames
