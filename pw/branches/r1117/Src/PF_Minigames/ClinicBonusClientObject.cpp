#include "stdafx.h"

#include "ClinicBonusClientObject.h"

#include "Clinic.h"
#include "ClinicBonus.h"
#include "../UI/ImageLabel.h"
#include "../UI/ProgressBar.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonusClientObject::SetVisible( bool _visible )
{
  visible = _visible;
  MinigameClientObject::SetVisible(_visible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicBonusClientObject::NeedHighlight() const
{
  return ( EClinicGameMode::Shop != clinic->GetGameMode() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::HDRColor& ClinicBonusClientObject::GetHighlightColor() const
{
  return clinic->GetClinicDesc()->preselection.colorPreselect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonusClientObject::InitClinicBonus( ClinicBonus * _bonus )
{
  NI_ASSERT( IsValid( clinic ), "" );
  clinicBonus = _bonus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonusClientObject::SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::SetupOvertipLayout(pWindow, overtipId);

  CheckControlOut( &wndPrice,        pWindow, "Price" );
  CheckControlOut( &wndTick,         pWindow, "Tick" );
  CheckControlOut( &wndCooldown,     pWindow, "Cooldown" );
  CheckControlOut( &wndName,         pWindow, "Name" );

  if(IsValid(clinicBonus) && IsValid(wndPrice))
    if(clinicBonus->GetUseCost())
    {
      wndPrice->Show(true);

      wstring coinText = wndPrice->GetRelatedText("Coin");
      wndPrice->SetCaptionTextW(NStr::StrFmtW(L"%i%s", clinicBonus->GetUseCost(), coinText.c_str()));
    }
    else
      wndPrice->Show(false);

  if ( IsValid( clinicBonus ) && IsValid( wndName ) )
    wndName->SetCaptionTextW( clinicBonus->GetName() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicBonusClientObject::UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId)
{
  MinigameClientObject::UpdateOvertipLayout(pWindow, overtipId);

  if(!IsValid(clinicBonus))
    return;

  if(IsValid(wndTick))
    wndTick->Show(clinicBonus->IsInRoute());

  if(IsValid(wndCooldown))
  {
    float cooldown = clinicBonus->GetCooldownPersent();
    if(cooldown > 0)
    {
      wndCooldown->Show(true);
      wndCooldown->SetProgressValue(cooldown);
    }
    else
      wndCooldown->Show(false);
  }
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::ClinicBonusClientObject)
