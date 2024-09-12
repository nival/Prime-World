#include "stdafx.h"
#include "ClinicBuyDialog.h"
#include "../Client/MessageScreen.h"
#include "MinigamesMain.h"

#include "../Client/ScreenCommands.h"
#include "../UI/ImageLabel.h"

#include "Clinic.h"
#include "ClinicBonus.h"
#include "ClinicPlace.h"
#include "ClinicCommands.h"
#include "Minigames.h"


namespace UI
{

static const char *   FIELD_ITEM_NAME =     "ItemName";
static const char *   FIELD_ITEM_DESC =     "ItemDesc";
static const char *   FIELD_ITEM_PRICE =    "ItemPrice";
static const char *   FIELD_ITEM_TOOMUCH =  "TextTooMuch";
static const char *   FIELD_ITEM_YES_BUTT = "YesButton";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinigBuyDialog::Popup(PF_Minigames::ClinicItem * pItem)
{
  NI_ASSERT(!IsValid(item2Buy), "Old bought place is not reset");

  if(pItem->IsBought())
    return;

  item2Buy = pItem;
  itemPrice = pItem->GetCost();
  itemName = pItem->GetName();
  itemDesc = pItem->GetDescription();
  isItemAffordable = clinic->ItemCanBeBought(pItem);

  Strong<NMainLoop::MessageScreen> buyRequestScreen = new NMainLoop::MessageScreen();
  buyRequestScreen->Configure(this, "ClinicBuyItem");
  NScreenCommands::PushCommand(NScreenCommands::CreatePushScreenCommand(buyRequestScreen));
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinigBuyDialog::SetupMessageWindow(UI::Window * pScreenBaseWindow)
{
  Weak<UI::ImageLabel> pName = UI::GetChildChecked<UI::ImageLabel>(pScreenBaseWindow, FIELD_ITEM_NAME, true);
  NI_DATA_VERIFY(IsValid(pName), NStr::StrFmt("Could not find element '%s!'", FIELD_ITEM_NAME), return);
  pName->SetCaptionTextW(itemName);

  Weak<UI::ImageLabel> pDesc = UI::GetChildChecked<UI::ImageLabel>(pScreenBaseWindow, FIELD_ITEM_DESC, true);
  NI_DATA_VERIFY(IsValid(pDesc), NStr::StrFmt("Could not find element '%s!'", FIELD_ITEM_DESC), return);
  pDesc->SetCaptionTextW(itemDesc);

  Weak<UI::ImageLabel> pPrice = UI::GetChildChecked<UI::ImageLabel>(pScreenBaseWindow, FIELD_ITEM_PRICE, true);
  NI_DATA_VERIFY(IsValid(pPrice), NStr::StrFmt("Could not find element '%s'!", FIELD_ITEM_PRICE), return);
  pPrice->SetCaptionTextW(NStr::StrFmtW(L"%i", itemPrice));

  Weak<UI::ImageLabel> pTooMuch = UI::GetChildChecked<UI::ImageLabel>(pScreenBaseWindow, FIELD_ITEM_TOOMUCH, true);
  NI_DATA_VERIFY(IsValid(pTooMuch), NStr::StrFmt("Could not find element '%s'!", FIELD_ITEM_TOOMUCH), return);
  pTooMuch->Show(!isItemAffordable);

  Weak<UI::ImageLabel> pYes = UI::GetChildChecked<UI::ImageLabel>(pScreenBaseWindow, FIELD_ITEM_YES_BUTT, true);
  NI_DATA_VERIFY(IsValid(pYes), NStr::StrFmt("Could not find element '%s'!", FIELD_ITEM_YES_BUTT), return);
  pYes->Enable(isItemAffordable);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinigBuyDialog::OnYesButton()
{
  if(IsValid(clinic))
  {
    CPtr<PF_Minigames::MinigamesMain> mgMain = clinic->GetMinigames()->GetNativeMain();
    PF_Minigames::IWorldSessionInterface * MgPlace = clinic->GetMinigames()->GetWorldSessionInterface();

    if(IsValid(item2Buy))
      mgMain->SendWorldCommand(PF_Minigames::CreateClinicBuyCommand(MgPlace, item2Buy->GetObjectID()));
  }

  ResetData();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinigBuyDialog::OnNoButton()
{
  ResetData();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinigBuyDialog::OnEscapeKey()
{
  ResetData();
  return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinigBuyDialog::ResetData()
{
  item2Buy = NULL;
  itemPrice = 0;
  itemName.clear();
  itemDesc.clear();
  isItemAffordable = false;
}


}; //namespace UI

NI_DEFINE_REFCOUNT( UI::ClinigBuyDialog );
