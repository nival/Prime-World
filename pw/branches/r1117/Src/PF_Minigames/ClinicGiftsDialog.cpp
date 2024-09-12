#include "stdafx.h"
#include "ClinicGiftsDialog.h"
#include "../Client/MessageScreen.h"
#include "../Client/ScreenCommands.h"
#include "../UI/ImageLabel.h"

#include "Clinic.h"
#include "ClinicPlace.h"


namespace UI
{

static const char *   FIELD_ITEM_LAYOUT =   "Gift";
static const char *   FIELD_ITEM_ORG =      "Origin";
static const char *   FIELD_ITEM_TEXT =     "Text";
static const char *   FIELD_ITEM_IMAGE =    "Image";


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicGiftsDialog::PopUp()
{
  Strong<NMainLoop::MessageScreen> screen = new NMainLoop::MessageScreen();
  screen->Configure(this, "ClinicGifts");
  screen->SetScreenTransparent( false );
  NScreenCommands::PushCommand(NScreenCommands::CreatePushScreenCommand(screen));
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicGiftsDialog::SetupMessageWindow(UI::Window * pScreenBaseWindow)
{
  UI::Window * pOrigin = UI::GetChildChecked<UI::Window>(pScreenBaseWindow, FIELD_ITEM_ORG, true);
  NI_DATA_VERIFY(pOrigin, NStr::StrFmt("Could not find element '%s!'", FIELD_ITEM_ORG), return);
  UI::Window * pParent = pOrigin->GetParent();

  const NDb::UILayout * pDbLayout = pParent->GetRelatedLayout(FIELD_ITEM_LAYOUT);
  NI_DATA_VERIFY(pDbLayout, NStr::StrFmt("Could not find related layout '%s!'", FIELD_ITEM_LAYOUT), return);
  
  CTPoint<int> pos = pOrigin->GetPos();
  int sizeAdd = 0;
  
  int counter = 0;
  for(PlacesSet::const_iterator it = giftedPlaces.begin(); it != giftedPlaces.end(); ++it, ++counter)
  {
    CPtr<PF_Minigames::ClinicPlace> place = *it;
    NI_ASSERT(IsValid(place), "Getting place description for gifts dialog");

    string name = string("WindowName_abyrvalg_") + NStr::StrFmt("%03i", counter);

    if( pParent->CreateChild( name.c_str(), FIELD_ITEM_LAYOUT, pos.x, pos.y, 0, 0, NDb::UIELEMENTHALIGN_LEFT, NDb::UIELEMENTVALIGN_TOP ) )
    {
      UI::Window * pGiftLayout = pParent->GetChild( name.c_str() );

      UI::ImageLabel * pText = UI::GetChildChecked<UI::ImageLabel>(pGiftLayout, FIELD_ITEM_TEXT, true);
      NI_DATA_VERIFY(pText, NStr::StrFmt("Could not find element '%s!'", FIELD_ITEM_TEXT), return);
      wstring text = place->GetName() + L"<br>" + place->GetDescription();
      pText->SetCaptionTextW(text);

      UI::ImageLabel * pImage = UI::GetChildChecked<UI::ImageLabel>(pGiftLayout, FIELD_ITEM_IMAGE, true);
      NI_DATA_VERIFY(pImage, NStr::StrFmt("Could not find element '%s!'", FIELD_ITEM_IMAGE), return);
      pImage->SetBackgroundMaterial( place->GetIconMaterial() );

      if(counter > 0) //первый не считаем
        sizeAdd += pDbLayout->size.y;
      pos.y += pDbLayout->size.y;
    }
  }

  UI::Window * pMain = pOrigin->GetParent();
  NI_VERIFY(pMain, "Main window not found", return);
  CTPoint<int> mainSz = pMain->GetSize();
  pMain->SetSize(mainSz.x, mainSz.y + sizeAdd, false);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicGiftsDialog::OnYesButton()
{
  ResetGifts();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicGiftsDialog::OnEscapeKey()
{
  ResetGifts();

  return true;
}

}; //namespace UI

NI_DEFINE_REFCOUNT( UI::ClinicGiftsDialog );
