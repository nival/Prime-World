#include "stdafx.h"
#include "EaselScreenLogic.h"

#include "../Client/ScreenCommands.h"
//#include "../PF_GameLogic/GameMenuScreen.h"
#include "../Render/materialspec.h"

#include "Minigames.h"
#include "MinigamesMain.h"
#include "MinigameCommands.h"

#include "../UI/Button.h"
#include "../UI/ProgressBar.h"
#include "../UI/ImageLabel.h"
#include "../UI/Resolution.h"
#include "../UI/FlashContainer2.h"

#include "LuxDef.h"

#include "DBEasel.h"

#include "Easel.h"
#include "EaselMinigame.h"
#include "EaselWorld.h"

#include "LuxBoost.h"
#include "LuxPath.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"
#include "BoostBoard.h"

#include "EaselWorldClientConvertHelper.h"

#include "EaselScreen.h"

#include "EaselCommands.h"

#include "../PF_GameLogic/SessionEventType.h"


namespace PF_Minigames
{

const int ZZ_AT_EXIT_WIDTH_OFFSET  = 125;
const int ZZ_AT_EXIT_HEIGHT_OFFSET = 80;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::BaseMaterial * EaselScreenLogic::BoostBtnData::GetButtonMaterial()
{
  if ( IsValid ( button ) )
    return button->GetRenderMaterial().GetRenderMaterial();

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( EaselScreenLogic, UI::ClientScreenUILogicBase )
  LUA_METHOD( FireBoostByButtIndex )
  LUA_METHOD( OnMouseMove )
  LUA_METHOD( OnLMouseDown )
  LUA_METHOD( OnRMouseDown )
END_LUA_TYPEINFO( EaselScreenLogic )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselScreenLogic::EaselScreenLogic() 
: MinigameScreenLogic()
, fIsInit(false)
{

}

EaselScreenLogic::~EaselScreenLogic()
{
  Uninit();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::Init( PF_Minigames::Minigames* minigames, EaselScreen * _screen )
{
  NI_ASSERT( !fIsInit, "" );

  boostButtonsInGame.resize(EASEL_BOOSTS_NUM);

  screen = _screen;

  // need to get minigame notificator object
  easelMinigame = minigames->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY( IsValid( easelMinigame ), "Missing EaselMinigame object",  return );

  gameLogic  = easelMinigame->GetLocalEasel()->GetWorld()->GetLogic();
  NI_ASSERT( IsValid( gameLogic ), "" );

  fIsInit = true;
}

void EaselScreenLogic::InitBoosts()
{
  if(fIsInit == false)
    return;

  // initializing boosts buttons container
  InitInGameBoostButtonsContainer();
}

void EaselScreenLogic::Uninit()
{
  if(fIsInit == false)
    return;

  boostButtonsInGame.clear();

  fIsInit = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EaselScreenLogic::ProcessStep()
{
  if ( !IsValid( easelMinigame ))
    return;

  UpdateInGameButtonStates();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::UpdateInGameButtonStates()
{
  //Intro mode
  if ( gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN )
  {
    for( int index = 0; index < boostButtonsInGame.size(); ++index )
    {
      BoostBtnData& btnData = boostButtonsInGame[index];
      if( !btnData.used || !IsValid( btnData.wpBoost ) )
        continue;

      NI_VERIFY( IsValid( btnData.button ) && IsValid( btnData.priceWnd ) && IsValid( btnData.progressBar ), "", continue );

      btnData.button->Enable( false );
      btnData.priceWnd->Show( false );
      btnData.progressBar->Show( false );

      Render::BaseMaterial * mat = btnData.GetButtonMaterial();
      if ( !mat )
        continue;

      mat->SetDisablePin( NDb::BOOLEANPIN_PRESENT );
      mat->SetLackOfManaPin( NDb::BOOLEANPIN_NONE );
    }

    return;
  }

  // Gameplay mode
  for( int index = 0; index < boostButtonsInGame.size(); ++index )
  {
    BoostBtnData& btnData = boostButtonsInGame[index];

    if( !btnData.used || !IsValid( btnData.wpBoost ) )
      continue;

    NI_VERIFY( IsValid( btnData.button ) && IsValid( btnData.priceWnd ) && IsValid( btnData.progressBar ), "", continue );

    Render::BaseMaterial * mat = btnData.GetButtonMaterial();
    NI_VERIFY( mat, "Wrong boost button material", continue );

    bool enabled = btnData.wpBoost->IsCanAccess() && !btnData.wpBoost->IsCoolingDown() && btnData.wpBoost->IsCanBuy();
    enabled = enabled && !gameLogic->GetBoostBoard()->ThereAreWaitingBoosts();

    btnData.button->Enable( enabled );

    //If there are boosts waiting for activation AND they are not us :) gray button out
    bool anotherBoostWaiting = gameLogic->GetBoostBoard()->ThereAreWaitingBoosts() && !btnData.wpBoost->IsWaitingActivation();

    mat->SetDisablePin( ( btnData.wpBoost->IsCanAccess() && !anotherBoostWaiting ) ? NDb::BOOLEANPIN_NONE : NDb::BOOLEANPIN_PRESENT );

    if ( !btnData.wpBoost->IsCanAccess() )
    {
      btnData.progressBar->Show( false );
      btnData.priceWnd->Show( false );
      continue;
    }

    btnData.priceWnd->Show( true );

    mat->SetLackOfManaPin( btnData.wpBoost->IsCanBuy() ? NDb::BOOLEANPIN_NONE : NDb::BOOLEANPIN_PRESENT );

    mat->SetWaitForActivationPin( btnData.wpBoost->IsWaitingActivation() ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );

    //Cooldown
    if( btnData.wpBoost->IsCoolingDown() )
    { 
      float p = ( (float)btnData.wpBoost->GetCurrentCooldown() / (float)btnData.wpBoost->GetCooldown() );
      btnData.progressBar->Show( true );
      btnData.progressBar->SetProgressValue( Clamp( 1.0f - p, 0.0f, 1.0f ) );
    }
    else
      btnData.progressBar->Show( false );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::ExitGame()
{
  if(fIsInit == false)
    return;

  // stop easel level
	if(IsValid( easelMinigame ) )
		easelMinigame->StopLevelLocal();

  // pop screen from stack
  easelMinigame->GetScreensManager().PopEaselScreen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::FireBoostByButtIndex( int index, bool heroic )
{
  if ( !fIsInit || ( gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN ) )
    return;

  BoostButtons & boosts = boostButtonsInGame;

  if ( index < 0 || index >= boosts.size() )
    return;

  BoostBtnData& _data = boosts[index];
  if( _data.forbidden || !IsValid(_data.wpBoost) )
    return;

  easelMinigame->GetCommandSender()->SendBoostFiredCommand( _data.wpBoost->GetBoostType() ); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::OnMouseMove( int x, int y )
{
  NI_ASSERT( IsValid( screen ), "" );
  screen->OnMouseMove( UI::ConvertToScreen( UI::Point( x, y ) ) );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::OnLMouseDown()
{
  NI_ASSERT( IsValid( screen ), "" );
  screen->OnLMouseDown();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselScreenLogic::OnRMouseDown()
{
  NI_ASSERT( IsValid( screen ), "" );
  screen->OnRMouseDown();
}

void EaselScreenLogic::InitInGameBoostButtonsContainer()
{
  // получить бусты от данных
  if( !IsValid( easelMinigame ) )
    return;

  Boosts _boost = gameLogic->GetBoostBoard()->GetBoosts();
  
  // need to set base layout state ...
  Weak<UI::Window> _baseBoosts = UI::GetChildChecked<UI::Window>(pBaseWindow,"BoostsLayout",true);
  if(!IsValid(_baseBoosts))
    return;

  int _numBoosts = _boost.size();
  if(_numBoosts < 0 && _numBoosts > EASEL_BOOSTS_NUM)
  {
    _baseBoosts->SetState("0");
    return;   // should be default state set
  }

  _baseBoosts->SetState((NStr::IntToStr(_numBoosts)).c_str());  

  Boosts::iterator _boostsIter = _boost.begin();
  for( int i = 0; _boostsIter != _boost.end(); ++i, ++_boostsIter )
  {
    SetupBoostBtnLayout(
      _baseBoosts, boostButtonsInGame[i], *_boostsIter,
      string( NStr::StrFmt( "Boost%i", i ) ).c_str(), //Resolve static buffer from StrFmt
      string( NStr::StrFmt( "easel_mg_boost%d", i + 1 ) ).c_str() );
  }
}

void EaselScreenLogic::SetupBoostBtnLayout( UI::Window * _baseWindow, BoostBtnData& _data, LuxBoost* _boost, const char * _layoutStr, const char * bindName )
{
  _data.used = true;
  _data.wpBoost = _boost;

  _data.nameMap = new PF_Minigames::LuxBoostNameMapProxy( _boost->GetPrice() );

  UI::Window * boostLayout = UI::GetChildChecked<UI::Window>( _baseWindow, _layoutStr, true );
  NI_VERIFY( boostLayout, "Boost layout not found", return );

  boostLayout->AssignNameMap( _data.nameMap );

  _data.button = UI::GetChildChecked<UI::Button>( boostLayout, "Button", true );
  _data.priceWnd = UI::GetChildChecked<UI::ImageLabel>( boostLayout, "Price", true );

	bool isSpeedClockBidon =  easelMinigame->GetLocalEasel()->GetWorldSessionInterface()->GetCurrentBidon() == NDb::BIDONTYPE_SPEEDCLOCK;

  //hide inactive bar
  Weak<UI::ProgressBar> oldBar = UI::GetChildChecked<UI::ProgressBar>( boostLayout, !isSpeedClockBidon? "ProgressFired" : "Progress", true );
  NI_ASSERT( IsValid( oldBar ), "Progress bar is not found" );

  if ( IsValid( oldBar ) )
  {
    oldBar->SetProgressValue(0.0f);
    oldBar->Show(false);
  }

  _data.progressBar = UI::GetChildChecked<UI::ProgressBar>( boostLayout, isSpeedClockBidon? "ProgressFired" : "Progress", true );


  NI_VERIFY( IsValid( _data.button ) && IsValid( _data.priceWnd ) && IsValid( _data.progressBar ), "Wrong boost button layout", return );

  NDb::Ptr<NDb::DBEaselData> gameData = gameLogic->GetGameData();

  _data.button->SetTooltipTextW( gameData->gameboosts.boostsTooltips[ _boost->GetBoostType() ].GetText() );

  _data.button->SetActivationBind( bindName );

  const NDb::UITexture * image = gameData->gameboosts.images[ _boost->GetBoostType() ];

  if ( image )
  {
    Render::Texture2DRef pIconTexture =  Render::Load2DTextureFromFile( image->textureFileName );
    _data.button->SetBackgroundTexture( pIconTexture );
  }


  _data.progressBar->SetProgressValue( 0.0f );
  _data.progressBar->Show( false );
}

}

using namespace PF_Minigames;
