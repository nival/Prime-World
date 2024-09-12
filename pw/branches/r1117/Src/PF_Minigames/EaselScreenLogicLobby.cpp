#include "stdafx.h"
#include "EaselScreenLogicLobby.h"

#include "Minigames.h"
#include "MinigamesMain.h"
#include "MinigameCommands.h"
#include "MinigameLobbyScreen.h"

#include "EaselPriestess.h"
#include "EaselStatistics.h"

#include "LuxDef.h"

#include "Easel.h"
#include "EaselWorld.h"
#include "EaselMinigame.h"
#include "LuxBoost.h"


#include "../ui/Window.h"
#include "../ui/ImageLabel.h"
#include "../ui/Button.h"

#include "../Render/materialspec.h"


namespace PF_Minigames
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( EaselScreenLogicLobby, MinigameLobbyScreenLogic )
  LUA_METHOD_EX( "Exit", ExitGame )
  LUA_METHOD( Start )
  LUA_METHOD( IsPaintLocked )
  LUA_METHOD( IsCanBuyBoostsRegen )
  LUA_METHOD( OnLevelChanged )
  LUA_METHOD( OnRegenerateClicked )
  LUA_PROPERTY( paintId )
  LUA_PROPERTY( currentLevel )
  LUA_READONLY_PROPERTY( maxLevel )
  LUA_READONLY_PROPERTY_EX( currentLevelAward, CurrentLevelAward )
  LUA_METHOD( GetLevelForPaintID )
END_LUA_TYPEINFO( EaselScreenLogicLobby )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLogicLobby::EaselScreenLogicLobby() :
MinigameLobbyScreenLogic()
, fIsInit(false)
, paintId(1)
, currentLevel(1)
, maxLevel(1)
{

}

EaselScreenLogicLobby::~EaselScreenLogicLobby()
{
  Uninit();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::Init( PF_Minigames::Minigames* minigames, int _maxLevel )
{
  if ( fIsInit  )
    return;

  maxLevel = _maxLevel;

  // need to get minigame notificator object
  easelMinigame = minigames->GetNativeMinigame<EaselMinigame>( "Easel" );
  NI_VERIFY( IsValid( easelMinigame ), "Missing EaselMinigame object", return );

  localEasel = easelMinigame->GetLocalEasel();
  if( !IsValid(localEasel) )
  {
    systemLog(NLogg::LEVEL_ASSERT) << "EaselScreenLogicLobby: Unable to get Easel minigame base object" << endl;
    return;
  }

  // getting proxy object ...
  UpdateLobby();  

  fIsInit = true;
}

void EaselScreenLogicLobby::InitLayout()
{
  if(!IsValid(pBaseWindow))
    return;

  ptrRegenBtn = UI::GetChildChecked<UI::Button>(pBaseWindow,"regenerate_button",true);
  if(IsValid(ptrRegenBtn))
    regenTooltip = ptrRegenBtn->GetTooltipText();

  levelSelectorWindow = pBaseWindow->FindChild("LevelSelector");
  paintSelectorWindow = pBaseWindow->FindChild("Paint selection region");
}

int EaselScreenLogicLobby::GetLevelForPaintID( int paintId )
{
  localEasel = easelMinigame->GetLocalEasel();
  if( !IsValid(localEasel) )
  {
    return 0;
  }

  return easelMinigame->GetLevelForPaintID( paintId );
}

void EaselScreenLogicLobby::UpdateLobby()
{
  priestessProxy = localEasel->GetWorld()->GetPriestessProxy(); 

  const EaselLevelStatistics * lastLevel = localEasel->GetStatistics().GetCurrentLevelStatistics();

  // set previous paint and level
  if( lastLevel )
  {
    paintId = lastLevel->GetPaintID() + 1;
    currentLevel = lastLevel->GetLevelID() + 1;

    // if last picture was complete - advance level
    if(lastLevel->GetRoundStatus() == NDb::EASELROUNDSTATUS_WON)
    {
      currentLevel++;
    }

    currentLevel = min(currentLevel, maxLevel);
  }

  if(IsValid(pBaseWindow))
    pBaseWindow->CallHandler("UpdateAll");
}

void EaselScreenLogicLobby::SetMaxLevel(int _maxLevel) 
{ 
  maxLevel = _maxLevel; 
}

void EaselScreenLogicLobby::Uninit()
{
  if(fIsInit == false)
    return;

  fIsInit = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::Start()
{
  // start easel level
	if( IsValid( easelMinigame ) )
	{
    easelMinigame->StartLevelLocal( currentLevel -1, paintId - 1 ); // if fails, lobby regains control ...
	}
  else
  {
    systemLog(NLogg::LEVEL_ASSERT) << "EaselScreenLogicLobby: easel minigame is invalid" << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::ExitGame()
{
  if ( !fIsInit )
    return;

  GetScreen()->ShowMainWindow( false );

  if ( IsValid( easelMinigame ) )
    easelMinigame->OnExitImmediate();

  //Мы пока не убиваем экран изела, т.к. в нем лежит камера, она должна доинтерполироваться
  MinigameLobbyScreenLogic::ExitLobby();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLogicLobby::IsCanBuyBoostsRegen()
{
  if ( !IsValid( localEasel ) || !IsValid( priestessProxy) )
    return false;

  return localEasel->CanRegenerateBoosts( currentLevel - 1, priestessProxy->GetGold() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * EaselScreenLogicLobby::CurrentLevelAward() const
{
  NDb::WonGameMedal award = localEasel->GetStatistics().GetLevelMedalEarned( currentLevel - 1 );
  return EnumToString( award );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::OnLevelChanged()
{
  UpdateBoostsImages();

  // need to update stats
  UI::Window * pWindow = UI::GetChildChecked<UI::Window>(pBaseWindow, "lobby boosts", true );
  if( pWindow )
  {
    pWindow->CallHandler( "UpdateStats" );

    if( IsValid( ptrRegenBtn ) )
    {
      wstring strTooltip = regenTooltip;
      strTooltip += NStr::IntToWStr( localEasel->GetRegenerateBoostPrice( currentLevel - 1 ) );

      ptrRegenBtn->SetTooltipTextW( strTooltip );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::OnRegenerateClicked()
{
  if( !IsCanBuyBoostsRegen() )
    return;

  // метод должен вызываться у EaselMinigame (для транспорта по сети)
  if ( easelMinigame->RegenerateBoosts( true, currentLevel - 1 ) )
    UpdateBoostsImages();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::UpdateBoostsImages()
{
  if( !IsValid( localEasel ) )
    return;

  NDb::Ptr<NDb::DBEaselData> gameData = localEasel->GetData();

  if( !IsValid( gameData ) )
    return;


  boostsNamemaps.clear();

  const Easel::CurrentBoosts & currentBoosts = localEasel->GetCurrentBoosts();
  
  for( int i = 0; i < (int)currentBoosts.capacity(); ++i )
  {
    const NDb::UITexture * boostPic = gameData->gameboosts.images[ currentBoosts[i] ];
    if ( !boostPic )
      continue;

    UI::ImageLabel * image = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, NStr::StrFmt( "slot%d", i ), true );
    if( !IsValid( image ) )
      continue;

    const bool enabled = ( i < localEasel->GetLevelBoostCount( currentLevel - 1 ) );

    Strong<PF_Minigames::LuxBoostNameMapProxy> nameMap = new PF_Minigames::LuxBoostNameMapProxy( localEasel->GetBoostPrice( currentBoosts[i] ) );
    boostsNamemaps[ currentBoosts[i] ] = nameMap;
    image->AssignNameMap( nameMap );

    image->SetTooltipTextW( gameData->gameboosts.boostsTooltips[ currentBoosts[i] ].GetText() );

    Render::BaseMaterial * material = image->GetRenderMaterial().GetRenderMaterial();
    if ( material )
    {
      material->SetDisablePin( enabled ? NDb::BOOLEANPIN_NONE : NDb::BOOLEANPIN_PRESENT );

      Render::Texture2DRef boostTexture = Render::Load2DTextureFromFile( boostPic->textureFileName );
      image->SetBackgroundTexture( boostTexture );
    }
  }
  
  if(IsValid(ptrRegenBtn))
  {
    wstring strTooltip = regenTooltip;
    strTooltip += NStr::IntToWStr( localEasel->GetRegenerateBoostPrice( currentLevel - 1 ) );  

    ptrRegenBtn->SetTooltipTextW(strTooltip);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselScreenLogicLobby::IsPaintLocked(int id)
{
  return (id != 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogicLobby::Step( float deltaTime )
{
  MinigameLobbyScreenLogic::Step( deltaTime );

  // need to update stats
  UI::Window * pWindow = pBaseWindow->FindChild( "lobby boosts" );
  if( pWindow )
    pWindow->CallHandler( "UpdateStats" );
}

} //namespace PF_Minigames
