#pragma once

#include "../libdb/Animated.h"
#include "../libdb/AnimatedWrapper.h"

namespace NWorld  { class PFBaseHero; }
namespace UI { class ImageLabel; }
namespace NDb { struct DamageBloodMaskParams;}

namespace NGameX
{

class DamageBloodMask : public CObjectBase
{
  OBJECT_METHODS(0x8B7A73C0, DamageBloodMask)
  DamageBloodMask() {};

  Weak<UI::ImageLabel> bloodMaskImage;
  
  //its a copy from db params
  float lowHealthAlpha;
  float nearDeathAlpha;
  float lowHealthLevel;
  float nearDeathLevel;
 
  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > alphaCurveWrapper;

  float timePassedFromHit;
  float usedAlpha;
  float currenAlpha;

public:
  DamageBloodMask(UI::ImageLabel * _bloodMask, const NDb::DamageBloodMaskParams & _bloodMaskParams);
  void OnHeroDamaged(const NWorld::PFBaseHero * hero);
  void Update(float dt);

};

}