#ifndef CLINICENTRANCECLIENTOBJECT_H_INCLUDED
#define CLINICENTRANCECLIENTOBJECT_H_INCLUDED

#include "MinigameClientObject.h"

namespace UI
{
class ImageLabel;
};

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class ClinicEntrance;


class ClinicEntranceClientObject : public MinigameClientObject
{
	OBJECT_BASIC_METHODS( ClinicEntranceClientObject )

public:
  ClinicEntranceClientObject() : visible(true) {}
  virtual ~ClinicEntranceClientObject() {}

  void SetClinic( Clinic * _clinic ) { clinic = _clinic; }
  void InitClinicEntrance( ClinicEntrance * _entrance );

  virtual void SetVisible( bool _visible );
  virtual bool NeedHighlight() const;
  virtual const Render::HDRColor& GetHighlightColor() const;

private:
  //IOvertipTarget:
  virtual bool IsOvertipVisible() const { return visible; }
  virtual void SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);
  virtual void UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);

  bool visible;

  CPtr<Clinic>  clinic;
  CPtr<ClinicEntrance>  clinicEntrance;

  Weak<UI::ImageLabel>  wndTick;
};

} // namespace PF_Minigames

#endif //CLINICENTRANCECLIENTOBJECT_H_INCLUDED
