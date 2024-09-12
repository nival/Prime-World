#include "StdAfx.h"

#include "DamageBloodMask.h"

#include "DBStats.h"
#include "../ui/ImageLabel.h"
#include "PFHero.h"

namespace NGameX
{
//////////////////////////////////////////////////////////////////////////
  DamageBloodMask::DamageBloodMask( UI::ImageLabel * _bloodMask, const NDb::DamageBloodMaskParams & _bloodMaskParams )
: timePassedFromHit(1000) //pretty big number
, bloodMaskImage(_bloodMask)
, currenAlpha(0)
{
  NI_ASSERT (IsValid(_bloodMask), "invalid window");
   
  lowHealthAlpha = _bloodMaskParams.lowHealthAlpha;
  nearDeathAlpha = _bloodMaskParams.nearDeathAlpha;
  lowHealthLevel = _bloodMaskParams.lowHealthLevel;
  nearDeathLevel = _bloodMaskParams.nearDeathLevel;

  alphaCurveWrapper.Init(&currenAlpha, _bloodMaskParams.alphaCurve, 0.0f);
 
}

//////////////////////////////////////////////////////////////////////////
void DamageBloodMask::OnHeroDamaged( const NWorld::PFBaseHero * hero )
{
  NI_VERIFY(IsValid(hero), "invalid hero", return);

  if ( hero->GetHealthPercent()<=lowHealthLevel && timePassedFromHit> alphaCurveWrapper.GetLength())
  {
    usedAlpha = nearDeathLevel>=hero->GetHealthPercent()? nearDeathAlpha: lowHealthAlpha;
    alphaCurveWrapper.SetStartTime(0);
    timePassedFromHit = 0;
  }
}

//////////////////////////////////////////////////////////////////////////
void DamageBloodMask::Update( float dt )
{
  NI_PROFILE_FUNCTION

  NI_VERIFY (IsValid(bloodMaskImage), "invalid window", return);
   
  if (timePassedFromHit> alphaCurveWrapper.GetLength())
  {
    if (bloodMaskImage->IsVisible())
      bloodMaskImage->Show(false);
    return;
  }
  
  bloodMaskImage->SetOpacity(currenAlpha * usedAlpha);

  if (!bloodMaskImage->IsVisible())
    bloodMaskImage->Show(true);

  alphaCurveWrapper.Step(dt);
  timePassedFromHit+=dt;
}

}//namespace NGameX


BASIC_REGISTER_CLASS(NGameX::DamageBloodMask)