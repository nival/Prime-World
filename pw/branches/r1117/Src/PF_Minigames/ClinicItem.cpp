#include "stdafx.h"

#include "ClinicItem.h"
#include "DBClinic.h"
#include "Clinic.h"
#include "MinigameClientObject.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicItem::OnClick()
{
  if(clinic->GetGameMode() == EClinicGameMode::Shop)
	{
    if(clinic->BuyUICallback()) //On local machine, request user to buy item
      clinic->BuyUICallback()->RequestBuy(this);
		return true;
	}
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicItem::OnBuyCommand()
{
  if (clinic->GetGameMode() == EClinicGameMode::Shop)
    clinic->BuyItem(this);
}


} // namespace PF_Minigames
REGISTER_SAVELOAD_CLASS_NM( ClinicItem, PF_Minigames );