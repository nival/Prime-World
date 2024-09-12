#include "stdafx.h"

#include "Scripts/lua.hpp"

#include "Core/GameTypes.h"
#include "Core/CoreFSM.h"
#include "Client/ScreenCommands.h"
#include "Client/MainTimer.h"

#include "ClinicResultsScreenLogic.h"
#include "ClinicResultsScreen.h"
#include "ClinicScreen.h"
#include "UI/ScrollList.h"
#include "UI/ProgressBar.h"
#include "UI/ImageLabel.h"
#include "DBClinic.h"


namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( ClinicResultsScreenLogic, ClientScreenUILogicBase )
  LUA_METHOD( Exit )
END_LUA_TYPEINFO( ClinicResultsScreenLogic )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::InitLayout(const PF_Minigames::ClinicCreepsUIDesc & creeps, const PF_Minigames::ClinicLevelUIDesc & _levelUIDesc, const NDb::DBMinigame_Clinic * _pDBDesc)
{
  pDesc = _pDBDesc;
  levelUIDesc = _levelUIDesc;
	float showTime = 0;

  AddGoldAnim(0, levelUIDesc.goldMade);

  AddCreatures(creeps, &showTime);
	UpdateMedal(&showTime);
  UpdateText(levelUIDesc.lastStatus != PF_Minigames::EClinicLevelStatus::Incomplete);
  UpdateGold(0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::MinigameUIStylesDesc& ClinicResultsScreenLogic::GetUIDB() const
{
  NI_ASSERT(pDesc,"");
  return pDesc->uiStyles;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::AddGoldAnim(float time, int deltaGold)
{
  if(goldAnim.empty())
    goldAnim[0] = 0;

  TGoldAnim::iterator back = goldAnim.end();
  --back;

  float lastTime = back->first;
  int lastGold = back->second;
  if(time >= lastTime)
  {
    goldAnim[time] = lastGold;
    float animTime = deltaGold / GetUIDB().naftaAnimationSpeed;
    goldAnim[time + animTime] = lastGold + deltaGold;
  }
  else
  {
    goldAnim.erase(back);
    goldAnim[time] = lastGold + deltaGold;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::AddCreatures(const PF_Minigames::ClinicCreepsUIDesc & creeps, float * pShowTime)
{
  windowsToShow.clear();

  *pShowTime += GetUIDB().creepsAppearPause;

  UI::Window * pBase = UI::GetChildChecked<UI::Window>(pBaseWindow, "Creeps", true);
  UI::Window * pMain = pBase->GetParent();

  CTPoint<int> base = pBase->GetPos();
  int maxWidth = pBase->GetSize().x;
  int addHeight = 0;

  int index = 0;
  for(PF_Minigames::ClinicCreepsUIDesc::const_iterator it = creeps.begin(); it != creeps.end(); ++it, ++index)
  {
    string wndName = CreepWndName(index);

    UI::Window * pNew = pMain->CreateChild( wndName.c_str(), "CreatureTemplate", 0, 0, 0, 0, NDb::UIELEMENTHALIGN_LEFT, NDb::UIELEMENTVALIGN_TOP);

    //lets align creeps cards...
    CTPoint<int> size = pNew->GetSize();
    NI_VERIFY(size.x, "'CreatureTemplate' width is zero!", return);
    int maxInRow = max(maxWidth / size.x, 1);
    int rowsCount = (creeps.size() + maxInRow - 1) / maxInRow;
    int rowIndex = index / maxInRow, indexInRow = index % maxInRow;

    addHeight = (rowIndex > 0) ? (rowIndex * size.y) : 0;

    int itemsInThisRow = (rowIndex < rowsCount - 1) ? maxInRow : (creeps.size() - rowIndex * maxInRow);
    int xMargin = (maxWidth - size.x * itemsInThisRow) / 2;
    pNew->SetLocation(base.x + xMargin + size.x * indexInRow, base.y + size.y * rowIndex);

    //@iA@TODO: Анимация opacity вырезана; здесь ее планируется заменить flsh-анимацией
    //поэтому функционал windowsToShow + goldAnim пока сохрянем, может пригодится

    //setup creep card
    pNew->SetOpacity( 1.f );
    //pNew->AddOpacity(0.f, *pShowTime, EANIMATORBLENDTYPE_LINEAR);
    //pNew->AddOpacity(1.f, GetUIDB().creepAppearTime, EANIMATORBLENDTYPE_LINEAR);
    //pNew->ForceUpdate();
    windowsToShow.push_back(pNew);

    AddGoldAnim(*pShowTime, it->goldMade);
    *pShowTime += GetUIDB().creepAppearTime;

    if(UI::ImageLabel * pName = UI::GetChildChecked<UI::ImageLabel>(pNew, "Name", true))
      pName->SetCaptionTextW( it->creepName );
    if(UI::ImageLabel * pIcon = UI::GetChildChecked<UI::ImageLabel>(pNew, "Icon", true))
      pIcon->SetBackgroundMaterial( it->imageMaterial );
    if(UI::ImageLabel * pFled = UI::GetChildChecked<UI::ImageLabel>(pNew, "Fled", true))
      pFled->Show( it->isFled );

    if(UI::ProgressBar * pBar = UI::GetChildChecked<UI::ProgressBar>(pNew, "Bar", true))
      pBar->SetProgressValue( it->barValue );

    //TODO: move this percents to DB
    const char * medalLOName = 0;
    if(it->award == PF_Minigames::EClinicCreepAward::GoldMedal)
      medalLOName = "MedalGold";
    else if(it->award == PF_Minigames::EClinicCreepAward::SilverMedal)
      medalLOName = "MedalSilver";

    if( medalLOName )
      if( UI::ImageLabel * pMedal = UI::GetChildChecked<UI::ImageLabel>( pNew, medalLOName, true ) )
      {
        pMedal->Show(true);
        pMedal->SetOpacity( 1.f );
        //pMedal->AddOpacity(0.f, *pShowTime, EANIMATORBLENDTYPE_LINEAR);
        //pMedal->AddOpacity(1.f, GetUIDB().creepMedalAppearTime, EANIMATORBLENDTYPE_LINEAR);
        //pMedal->ForceUpdate();
        windowsToShow.push_back(pMedal);
        *pShowTime += GetUIDB().creepMedalAppearTime;
      }
  }

  CTPoint<int> mainSz = pMain->GetSize();
  pMain->SetSize(mainSz.x, mainSz.y + addHeight, false );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::UpdateMedal(float * pShowTime)
{
  *pShowTime += GetUIDB().medalAppearPause;
  //посчитать средее заполненности бара кричей
  //TODO: move this win ratios to DB

  const char * medalLOName = 0;
  if(levelUIDesc.lastStatus == PF_Minigames::EClinicLevelStatus::GoldMedal)
    medalLOName = "MedalGold";
  else if(levelUIDesc.lastStatus == PF_Minigames::EClinicLevelStatus::SilverMedal)
    medalLOName = "MedalSilver";

  if( medalLOName )
    if( UI::ImageLabel * pMedal = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, medalLOName, true ) )
    {
      pMedal->SetOpacity( 1.f );
      //pMedal->AddOpacity(0.f, *pShowTime, EANIMATORBLENDTYPE_LINEAR);
      //pMedal->AddOpacity(1.f, GetUIDB().medalAppearTime, EANIMATORBLENDTYPE_LINEAR);
      //pMedal->Show(true);
      windowsToShow.push_back(pMedal);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::UpdateText(bool bWon)
{
  if( Weak<UI::ImageLabel> pItem = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "MinigameName", true ) )
    pItem->SetCaptionTextW( pBaseWindow->GetRelatedText( bWon ? "you_won" : "you_loose" ) );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::UpdateGold(float time)
{
  if(goldAnim.size() < 2)
    return;

  TGoldAnim::iterator it = goldAnim.lower_bound(time), from = goldAnim.end(), to = goldAnim.end();

  if(it == goldAnim.end()) //Время ушло
  {
    --it;
    from = to = it;
  }
  else if(it == goldAnim.begin()) //Время еще не пришло
  {
    from = to = it;
  }
  else //анимация
  {
    to = it;
    --it;
    from = it;
  }

  float t = (time - from->first) / (to->first - from->first);
  t = max(t, .0f);
  t = min(t, 1.f);
  int newValue = (int)(from->second * (1.f - t) + to->second * t + 0.5f);

  if(newValue != lastGoldValue)
  {
    if(UI::ImageLabel * pWnd = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "Gold", true) )
      pWnd->SetCaptionTextW(NStr::StrFmtW(L"%d", newValue));
    lastGoldValue = newValue;
  }

  //TODO: Тут планировался мега сплэш на счетчике денег, но ничего не вышло :(
  // - opacity почему-то нифига не анимируется
  // - при скалировании контрола текст не скалится совсем :(
  // - поэтому просто немного поиграем иконкой денег

  //Если дошли до постоянного участка, проиграем сплэш
  if(from->second == to->second && newValue != lastSplashValue && time >= from->first)
    if(UI::ImageLabel * pWnd = UI::GetChildChecked<UI::ImageLabel>(pBaseWindow, "GoldDecor", true))
    {
      lastSplashValue = newValue;
      //@iA@TODO: Вот здесь вот было проигрывание супер-мега-FX на контроле pWnd (отображает выигранную сумму денех)
      //Но, так как анимация location/size была вырезана, теперь здесь никаких FX-ов нет
      //TODO: запустить штоль здесь какую-нить флэшку
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::OnLeftClick()
{
  for(TWndList::iterator it = windowsToShow.begin(); it != windowsToShow.end(); ++it)
    if(IsValid(*it))
      (*it)->SetOpacity( 1.0f );
  windowsToShow.clear();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::Step( float deltaTime )
{
  float time = NMainLoop::GetTime();

  if(!updateStart && time)
    updateStart = time;

  UpdateGold(time - updateStart);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicResultsScreenLogic::Exit()
{
	NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( "ClinicResultsScreen" ) );
}

}
