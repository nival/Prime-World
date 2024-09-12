#include "stdafx.h"

#include "TalentPanelNew.h"
#include "PFTalent.h"
#include "PFMaleHero.h"
#include "AdventureFlashInterface.h"
#include "../UI/FlashContainer2.h"
#include "../UI/ImageLabel.h"
#include "AdventureTooltip.h"
#include "AdventureScreenEvents.h"
#include "UIEventHandler.h"
#include "FlashFSCommands.h"
#include "UnitNameMap.h"
#include "PrecompiledTooltips.h"
#include "AdventureScreen.h"  // For TempDebugTrace. Remove, when unneeded
#include "AdventureScreenLogic.h"

namespace NGameX
{

TalentPanelNew::TalentPanelNew( const NDb::DBUIData * _uiData, UI::FlashContainer2 * flashContainer,
                               AdventureFlashInterface * _flashInterface, IUIEventHandler * _eventHandler,
                               UI::ImageLabel * _tooltipWindow ) :
uiData( _uiData ),
flashInterface(_flashInterface),
eventHandler(_eventHandler),
flashWindow(flashContainer)
{
  using namespace FlashFSCommands;

  flashContainer->AddFSListner(ConvertToString(TalentClicked), this);
  flashContainer->AddFSListner(ConvertToString(TalentToolTip), this);

  talentStates.resize(GetTalentsCountX()* GetTalentsCountY());

  if (IsValid(_tooltipWindow))
     tooltip = new AdventureTooltip(_tooltipWindow);
}

int TalentPanelNew::GetTalentsCountX() const
{
  return NDb::KnownEnum<NDb::ETalentSlot>::sizeOf;
}

int TalentPanelNew::GetTalentsCountY() const
{
  return NDb::KnownEnum<NDb::ETalentLevel>::sizeOf;
}

void TalentPanelNew::SetHero( NWorld::PFBaseMaleHero * pMale )
{
  hero = pMale;

  if (!pMale)
    return;

  int const nNumSlots  = GetTalentsCountX();
  int const nNumLevels = GetTalentsCountY();

  //clear states and fill it with the basic one

  //for (int i =0; i<talentStates.size(); i++)
  //  talentStates[i] = TalentUIState::NotEnoughDevPoints;

  //first fill talents in order to fill all action bat indexes
  for (int level = 0; level < nNumLevels; ++level)
  {
    for (int slot = 0; slot < nNumSlots; ++slot)
    {
      NWorld::PFTalent * pTalent = hero->GetTalent( level, slot );
      const char * talentIcon = "";
      const char * altIcon = "";
      if ( pTalent )
      {
        NDb::Ptr<NDb::Texture> const& pDBImageTexture = pTalent->GetTalentDesc()->image;
        if ( !pDBImageTexture )
        {
          NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "No image specified for talent %s", pTalent->GetTalentDesc()->GetDBID().GetFileName() ) );
        }
        else
        {
          talentIcon = pDBImageTexture->textureFileName.c_str();
        }
        NDb::Ptr<NDb::Texture> const& pDBImageTexture2 = pTalent->GetTalentDesc()->imageSecondState;
        if ( pDBImageTexture2 )
        {
          altIcon = pDBImageTexture2->textureFileName.c_str();
        }
      }

      bool isTalentActive = pTalent? pTalent->IsActive() : false;
      int actionBarIndex = pTalent? pTalent->GetActionBarIndex() : -1;

      int upgradeLevel = 0;
      bool isClassTalent = false;
      int cost = 0;

      if (NDb::Ptr<NDb::Talent> dbTalent = pTalent? pTalent->GetTalentDesc() : 0 )
      {
        upgradeLevel = dbTalent->upgradeLevel;
        isClassTalent = dbTalent->rarity == NDb::TALENTRARITY_CLASS;
        cost = pTalent->GetNaftaCost();
      }

      flashInterface->SetTalentIcon(slot, level, talentIcon, altIcon, isTalentActive, actionBarIndex, upgradeLevel, isClassTalent, cost);
    }
  }

  //then fill states
  for (int level = 0; level < nNumLevels; ++level)
  {
    for (int slot = 0; slot < nNumSlots; ++slot)
    {
      TalentUIState::ETalentUIState talentState = GetUITalentState(slot, level);

      int index = slot + nNumSlots * level;

      talentStates[index] = talentState;
      flashInterface->SetTalentState(slot, level, talentState);

      NWorld::PFTalent * talent = hero->GetTalent(slot, level);
      if (!talent)
        continue;
      SlotStatus status = ActionBarController::GetTalentStatus(talent);
      bool isAlternativeStateOn = talent->IsOn() && talent->IsMultiState() || talent->IsSecondState();
      flashInterface->SetTalentStatus(slot, level, status.slotState, status.cooldown, status.maxCooldown, isAlternativeStateOn);
    }
  }

  flashInterface->NotifyTalentsStateChaged();
}

void TalentPanelNew::Update(int mouseX, int mouseY)
{
  if (!IsValid(hero) || !IsValid(flashInterface) )
    return;

  int const nNumSlots  = GetTalentsCountX();
  int const nNumLevels = GetTalentsCountY();

  unsigned changed = 0;

  // Update enable/disable for buttons
  for (int level = 0; level < nNumLevels; ++level)
  {
    for (int slot = 0; slot < nNumSlots; ++slot)
    {
      if (!hero->GetTalent(level, slot))
        continue;

      TalentUIState::ETalentUIState talentState = GetUITalentState(slot, level);
      
      int index = slot + nNumSlots * level;

      if (talentStates[index]!=talentState)
      {
        talentStates[index] = talentState;
        flashInterface->SetTalentState(slot, level, talentState);

        ++changed;
      }
    }
  }

  if (changed)
    flashInterface->NotifyTalentsStateChaged();

  if (tooltip->IsVisible())
    tooltip->SetLocation(mouseX, mouseY);
}

TalentUIState::ETalentUIState TalentPanelNew::GetUITalentState(int column, int row)
{
  NWorld::PFTalent *pTalent = hero->GetTalent(row, column);

  if (!pTalent)
    return TalentUIState::NotEnoughDevPoints;

  if (pTalent->IsActivated())
    return TalentUIState::Bought;
  else
  {
    switch (hero->CanActivateTalent(row, column))
    {
    case NWorld::ETalentActivation::Ok: return TalentUIState::CanBuy;
    case NWorld::ETalentActivation::NoMoney: return TalentUIState::NotEnoughPrime;
    case NWorld::ETalentActivation::Denied: return TalentUIState::NotEnoughDevPoints;
    }
  }

  NI_ALWAYS_ASSERT("NWorld::ETalentActivation enum");
  return TalentUIState::NotEnoughDevPoints;
}

void TalentPanelNew::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  )
{
  if ( !args || ! _wnd )
  {
    return;
  }
  
  using namespace FlashFSCommands;

  switch ( ConvertToFSCommand( listenerID ) )
  {
  case TalentClicked:
    ProcessTalentClick(args);
    break;
  case TalentToolTip:
    ProcessTalentTooltip(args);
    break;
  default:
    NI_ALWAYS_ASSERT( "wrong fs listener" );
  }
}


void TalentPanelNew::ProcessTalentClick( const char* args )
{
  int slot = 0;
  int level = 0;

  sscanf_s(args, "%d %d", &slot, &level);

  TempDebugTrace(NStr::StrFmt("TalentPanelNew::ProcessTalentClick() row=%d col=%d", level, slot));

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (NGameX::AdventureScreenLogic* pAdvScreenLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(pAdvScreen->GetLogic()))
    {
      pAdvScreenLogic->SetLastTalentClicked( level, slot );
    }
  }

  if (NWorld::PFTalent const *pTalent = hero->GetTalent(level, slot))
  {
    if (IsValid(eventHandler))
    {
      eventHandler->OnTalentSetButtonClick(level, slot);
    }
  }
}

void TalentPanelNew::ProcessTalentTooltip( const char* args )
{
  int show = 0;  
  int slot = 0;
  int level = 0;

  sscanf_s(args,"%d %d %d", &show, &slot, &level);

  ShowTooltip(slot, level, show);
}

void TalentPanelNew::ShowTooltip( int column, int row, bool show )
{
	if (!IsValid(tooltip))
		return;

	if ( NWorld::PFTalent *pTalent =  hero->GetTalent(row, column) )
	{
	  if (show)
		  UpdateTooltipText(column, row);

	  tooltip->Show(show);
    eventHandler->TargetZoneTooltip(show?pTalent:0);
	}
	else
	{
	  tooltip->Show(false);
	}
}



void TalentPanelNew::UpdateTooltipText( int column, int row)
{
 
  if ( NWorld::PFTalent *pTalent =  hero->GetTalent(row, column) )
  {
    typedef NMeta::MakeTypeList<NWorld::PFTalent, NWorld::PFBaseMaleHero>::Result myList;
    UnitInfoNameMap<myList> myMap;

    Field<NWorld::PFTalent>(myMap).pObject       = pTalent;
    Field<NWorld::PFBaseMaleHero>(myMap).pObject = hero;

    NI_VERIFY(pTalent->GetTalentDesc(), "Wrong DB ptr", return);

    SConstUISubst subst;
    subst.Add( L"commonDescription", pTalent->GetTalentDesc()->commonDescription.GetText() );
    PrecompiledTooltip pt;
    pt.Init( &myMap, pTalent->GetTalentDesc()->description.GetText(), &subst );

    wstring newText;
    pt.MakeText(newText);

    tooltip->SetText( newText, uiData->tooltipDownScaleLimit );
  }
}


} //namespace NGameX

NI_DEFINE_REFCOUNT(NGameX::TalentPanelNew);
