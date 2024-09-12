#include "stdafx.h"
#include "EaselScreenLogicResults.h"

//#include "../Client/ScreenCommands.h"
#include "../Ui/Window.h"

#include "Minigames.h"
#include "MinigamesMain.h"
#include "MinigameCommands.h"
#include "EaselStatistics.h"
#include "EaselWorld.h"

#include "LuxDef.h"

#include "EaselMinigame.h"
#include "EaselSoundsInterface.h"

#include "PF_GameLogic/PFHero.h"
#include "PF_GameLogic/PFAbilityData.h"
#include "PF_GameLogic/PFConsumable.h"
#include "PF_GameLogic/DBConsumable.h"
#include "PF_GameLogic/PrecompiledTooltips.h"


namespace PF_Minigames
{


class EaselResultsPlayerNMap : public BaseObjectST, public NNameMap::IMap
{
  NI_DECLARE_REFCOUNT_CLASS_2( EaselResultsPlayerNMap, BaseObjectST, NNameMap::IMap )
  NAMEMAP_DECLARE

public:
  EaselResultsPlayerNMap( const wstring & _name ) : name( _name ) {}

private:
  wstring name;
};

NAMEMAP_BEGIN( EaselResultsPlayerNMap )
  NAMEMAP_VAR( name )
NAMEMAP_END






BEGIN_LUA_TYPEINFO( EaselScreenLogicResults, UI::ClientScreenUILogicBase )
  LUA_METHOD( SelectHero )
  LUA_METHOD( TransferScroll )
  LUA_METHOD( DiscardScroll )
  LUA_READONLY_PROPERTY( paintId )
END_LUA_TYPEINFO( EaselScreenLogicResults )



EaselScreenLogicResults::EaselScreenLogicResults() :
UI::ClientScreenUILogicBase(),
waitTime(0),
paintId( EaselConst::Get_EASEL_PAINT_MIN() ),
uiStatus( eStatusEmpty ),
statusAutoClearTimeLeft( 0 ),
timeToTargetsUpdate( 0 )
{
}



void EaselScreenLogicResults::Init(PF_Minigames::Minigames* minigames)
{
	associatedMinigames = minigames;

  // need to get minigame notificator object
  easelMinigameClient = associatedMinigames->GetNativeMinigame<EaselMinigame>("Easel");
  NI_VERIFY( IsValid( easelMinigameClient ),"Missing EaselMinigame object", return);

  localEasel = easelMinigameClient->GetLocalEasel();
  NI_VERIFY( localEasel, "", return );

  paintId = easelMinigameClient->GetPaintID() + 1;

  easelMinigameClient->InitiatePause( true );

  waitTime = localEasel->GetData()->commonParams->waitForResultScreen;
}



void EaselScreenLogicResults::OnLoadedScreenLayout()
{
  if( waitTime > 0 )
    pBaseWindow->Show( false );

  localEasel = easelMinigameClient->GetLocalEasel();
  NI_VERIFY( IsValid( localEasel ), "", return );

  //NOTE: This function switches states and thus re-creates windows
  SetupRewardLayouts();

  for ( int i = 1; ; ++i )
  {
    UI::RadioButton * wnd = GetUIWindow<UI::RadioButton>( NStr::StrFmt( "Hero%d", i ), true, false );
    if ( !wnd )
      break;
    heroesButtons.push_back( wnd );
  }

  transferButton =      GetUIWindow<UI::Window>( "TransferButton" );
  discardButton =       GetUIWindow<UI::Window>( "DiscardButton" );

  noValidTargetsText =  GetUIWindow<UI::Window>( "NoValidTargetsText" );
  waitText =            GetUIWindow<UI::Window>( "WaitText" );
  failureText =         GetUIWindow<UI::Window>( "TransferFailureText" );

  inputBlocker =        GetUIWindow<UI::Window>( "InputBlocker" );

  SetupScrollIcon();
  SetupTransferTargets();
  UpdateStatusWindows();
}



void EaselScreenLogicResults::SetupScrollIcon()
{
  UI::ImageLabel * scrollIcon = GetUIWindow<UI::ImageLabel>( "ScrollIcon" );
  if ( !scrollIcon )
    return;

  NDb::Ptr<NDb::Consumable> reward = localEasel->GetWorld()->GetPriestessProxy()->GetRewardItem();

  Render::Texture2DRef renderTex = reward->image ? Render::Load2DTextureFromFile( reward->image->textureFileName ) : Render::Texture2DRef();
  if ( renderTex )
    scrollIcon->SetBackgroundTexture( renderTex );

  ///Generate tooltip text via mocks///
  NWorld::PFBaseUnit * baseUnit = dynamic_cast<NWorld::PFBaseUnit *>( localEasel->GetWorldSessionInterface() );

  CObj<NWorld::PFConsumable> consumable = new NWorld::PFConsumable( 0, baseUnit, reward );
  
  NGameX::SConstUISubst subst;
  subst.Add( L"commonDescription", consumable->GetDBDesc()->commonDescription.GetText() );

  NGameX::PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init( consumable, reward->description.GetText(), &subst );

  wstring text;
  precompiledTooltip.MakeText(text);

  scrollIcon->SetTooltipTextW( text );
}



void EaselScreenLogicResults::SetupRewardLayouts()
{
  Weak<UI::Window> rewardArea = GetUIWindow<UI::ImageLabel>( "RewardArea" );

  const EaselLevelStatistics * levelStatistics = localEasel->GetStatistics().GetCurrentLevelStatistics();

  NI_VERIFY( rewardArea && levelStatistics, "", return );

  NDb::WonGameMedal medal = levelStatistics ? levelStatistics->GetMedal() : NDb::WONGAMEMEDAL_NONE;

  if ( medal == NDb::WONGAMEMEDAL_GOLD )
  {
    rewardArea->SetState( "GoldMedal" );
    localEasel->GetWorld()->GetSound()->PlaySound( NDb::EASELSOUNDTYPE_RESULT_GOLD_MEDAL );
  }
  else if ( medal == NDb::WONGAMEMEDAL_SILVER )
  {
    rewardArea->SetState( "SilverMedal" );
    localEasel->GetWorld()->GetSound()->PlaySound( NDb::EASELSOUNDTYPE_RESULT_SILVER_MEDAL );
  }

  Weak<UI::ImageLabel> goldText = GetUISubWindow<UI::ImageLabel>( rewardArea, "Gold" );
  if ( goldText )
  {
    NI_ASSERT( localEasel->GetWorld()->GetPriestessProxy(), "" );
    int earnedGold = localEasel->GetWorld()->GetPriestessProxy()->GetDelayedGold();
    goldText->SetCaptionTextW( NStr::StrFmtW( L"%d", earnedGold ) );
  }
}



void EaselScreenLogicResults::GetDropTargets()
{
  localEasel->GetWorldSessionInterface()->GetItemTransferTargets( currentTargets );

  for ( int i = 0; i < currentTargets.size(); ++i )
    if ( currentTargets[i]->IsLocal() )
    {
      swap( currentTargets[0], currentTargets[i] );
      break;
    }
}



void EaselScreenLogicResults::SetupTransferTargets()
{
  GetDropTargets();

  playerNameMaps.clear();

  for ( int i = 0; i < heroesButtons.size(); ++i )
  {
    NI_ASSERT( heroesButtons[i], "" );

    NWorld::PFBaseHero * target = ( i < currentTargets.size() ) ? currentTargets[i] : 0;
    if ( !target )
    {
      heroesButtons[i]->Show( false );
      continue;
    }

    NDb::Ptr<NDb::Consumable> reward = localEasel->GetWorld()->GetPriestessProxy()->GetRewardItem();

    bool canAdd = target->CanAddItem( reward, 1 );
    heroesButtons[i]->Enable( canAdd );

  /*  if ( target->GetOriginalFaction() == NDb::FACTION_FREEZE )
      heroesButtons[i]->OverrideDiffuseTexture( target->GetDbHero()->heroImageA );
    else
      heroesButtons[i]->OverrideDiffuseTexture( target->GetDbHero()->heroImageB );
*/
    heroesButtons[i]->OverrideDiffuseTexture( target->GetUiAvatarImage() );
    playerNameMaps.push_back( new EaselResultsPlayerNMap( target->GetPlayerName() ) );
    heroesButtons[i]->AssignNameMap( playerNameMaps.back() );

    const char * ttId = 0;
    if ( target->IsLocal() )
      ttId = canAdd ? "normalOwnTooltip" : "disabledOwnTooltip";
    else
      ttId = canAdd ? "normalTooltip" : "disabledTooltip";

    if ( ttId )
    {
      wstring ttip = heroesButtons[i]->GetParent()->GetRelatedText( ttId );
      heroesButtons[i]->SetTooltipTextW( ttip );
    }
  }
  
  UpdateSelection();
}



void EaselScreenLogicResults::SetStatus( EStatus st, float autoClearPeriod )
{
  statusAutoClearTimeLeft = autoClearPeriod;
  if ( uiStatus != st )
  {
    uiStatus = st;
    UpdateStatusWindows();
  }
}



void EaselScreenLogicResults::UpdateStatusWindows()
{
  if ( !( transferButton && discardButton && noValidTargetsText && waitText && failureText && inputBlocker ) )
    return;

  transferButton->Show( uiStatus != eStatusNoValidTargets );
  transferButton->Enable( uiStatus != eStatusWaitForTransfer );
  discardButton->Show( uiStatus == eStatusNoValidTargets );

  noValidTargetsText->Show( uiStatus == eStatusNoValidTargets );
  waitText->Show( uiStatus == eStatusWaitForTransfer );
  failureText->Show( uiStatus == eStatusTransferFailure );

  inputBlocker->Show( uiStatus == eStatusWaitForTransfer );
}



void EaselScreenLogicResults::UpdateSelection()
{
  CPtr<NWorld::PFBaseHero> newSel;
  for ( int i = 0; ( i < heroesButtons.size() ) && ( i < currentTargets.size() ); ++i )
    if ( heroesButtons[i]->IsEnabled() )
    {
      if ( !newSel || ( currentTargets[i] == selectedTarget ) )
      {
        newSel = currentTargets[i];
        heroesButtons[i]->SetSelected( true, 0 );
      }
    }

  selectedTarget = newSel;

  bool targetValid = IsValid( selectedTarget );
  if ( transferButton && discardButton && noValidTargetsText )
  {
    transferButton->Show( targetValid );
    discardButton->Show( !targetValid );
    noValidTargetsText->Show( !targetValid );
  }
}



void EaselScreenLogicResults::Step( float deltaTime )
{
  if( waitTime > 0 )
  {
    waitTime -= deltaTime;
    if( waitTime <= 0 )
      pBaseWindow->Show( true );
  }

  if( !IsValid( easelMinigameClient ) )
    return;

  const float TargetsUpdatePeriod = 5.0f;
  timeToTargetsUpdate -= deltaTime;
  if ( timeToTargetsUpdate <= 0 )
  {
    timeToTargetsUpdate = TargetsUpdatePeriod;
    SetupTransferTargets();
  }

  if ( uiStatus == eStatusWaitForTransfer )
  {
    bool lastTransferResult = false;
    if ( easelMinigameClient->Local_PopItemTransferResult( lastTransferResult ) )
    {
      if ( lastTransferResult )
        FinishWithThis();
      else
        SetStatus( eStatusTransferFailure, 5.0f );
    }
  }

  if ( ( uiStatus != eStatusEmpty ) && ( statusAutoClearTimeLeft > 0 ) )
  {
    statusAutoClearTimeLeft -= deltaTime;
    if ( statusAutoClearTimeLeft <= 0 )
    {
      uiStatus = eStatusEmpty;
      UpdateStatusWindows();
    }
  }
}



void EaselScreenLogicResults::SelectHero( int index )
{
  if ( index > 0 && index <= currentTargets.size() )
    selectedTarget = currentTargets[index - 1];
}



void EaselScreenLogicResults::TransferScroll()
{
  if( IsValid( easelMinigameClient ) )
  {
    easelMinigameClient->Local_StartItemTransfer( IsValid( selectedTarget ) ? selectedTarget : 0 );

    SetStatus( eStatusWaitForTransfer );
  }
}



void EaselScreenLogicResults::DiscardScroll()
{
  SetStatus( eStatusEmpty );

  FinishWithThis();
}



void EaselScreenLogicResults::FinishWithThis()
{
  // stop easel level
  if( IsValid( easelMinigameClient ) )
  {
    easelMinigameClient->InitiatePause( false );
    easelMinigameClient->StopLevelLocal();

    easelMinigameClient->GetScreensManager().PopResultsScreen();
  }
}

} //namespace PF_Minigames


NI_DEFINE_REFCOUNT( PF_Minigames::EaselResultsPlayerNMap );
