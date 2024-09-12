#ifndef CLINICBONUSCLIENTOBJECT_H_INCLUDED
#define CLINICBONUSCLIENTOBJECT_H_INCLUDED

#include "MinigameClientObject.h"

namespace UI
{
class ImageLabel;
class ProgressBar;
};

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class ClinicBonus;

class ClinicBonusClientObject : public MinigameClientObject
{
	OBJECT_BASIC_METHODS( ClinicBonusClientObject )

public:
  ClinicBonusClientObject() : visible(true) {}
  virtual ~ClinicBonusClientObject() {}

  virtual void SetVisible( bool _visible );
  virtual bool NeedHighlight() const;
  virtual const Render::HDRColor& GetHighlightColor() const;
  
  void SetClinic( Clinic * _clinic ) { clinic = _clinic; }
  void InitClinicBonus( ClinicBonus * _bonus );

protected:
  //IOvertipTarget:
  virtual bool IsOvertipVisible() const { return visible; }
  virtual void SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);
  virtual void UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);

  CPtr<Clinic>            clinic;
  CPtr<ClinicBonus>       clinicBonus;

  bool                    visible;
  Weak<UI::ImageLabel>    wndPrice;
  Weak<UI::ImageLabel>    wndTick;
  Weak<UI::ProgressBar>   wndCooldown;
  Weak<UI::ImageLabel>    wndName;
};

} // namespace PF_Minigames

#endif //CLINICBONUSCLIENTOBJECT_H_INCLUDED
