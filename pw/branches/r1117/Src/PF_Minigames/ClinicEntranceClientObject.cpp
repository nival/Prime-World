#include "stdafx.h"

#include "ClinicEntranceClientObject.h"

#include "Clinic.h"
#include "clinicEntrance.h"
#include "../UI/ImageLabel.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntranceClientObject::InitClinicEntrance( ClinicEntrance * _entrance )
{
  NI_ASSERT( IsValid( clinic ), "" );
  clinicEntrance = _entrance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntranceClientObject::SetVisible( bool _visible )
{
  visible = _visible;

  MinigameClientObject::SetVisible(_visible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicEntranceClientObject::NeedHighlight() const
{
  return ( EClinicGameMode::Shop != clinic->GetGameMode() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::HDRColor& ClinicEntranceClientObject::GetHighlightColor() const
{
  return clinic->GetClinicDesc()->preselection.colorPreselect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntranceClientObject::SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::SetupOvertipLayout(pWindow, overtipId);

  CheckControlOut(&wndTick,       pWindow, "Tick");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicEntranceClientObject::UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::UpdateOvertipLayout(pWindow, overtipId);

  if(!IsValid(clinicEntrance))
    return;

  if(IsValid(wndTick))
    wndTick->Show(clinicEntrance->IsInRoute());
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::ClinicEntranceClientObject)
