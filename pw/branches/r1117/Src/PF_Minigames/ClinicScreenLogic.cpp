#include "stdafx.h"

#include "../UI/ImageLabel.h"
#include "../UI/ProgressBar.h"
#include "../UI/Root.h"

#include "../Client/ScreenCommands.h"
#include "../Scene/CollisionHull.h"
#include "../Core/WorldCommand.h"

//#include "../PF_GameLogic/GameMenuScreen.h"

#include "ClinicScreenLogic.h"
#include "Minigames.h"
#include "MinigamesMain.h"
#include "MinigameWorldObject.h"
#include "ClinicResultsScreen.h"
#include "Clinic.h"
#include "ClinicCreepClientObject.h"
#include "ClinicCommands.h"


namespace UI
{


class ClinicGameMenuProxy : public NGameX::IGameMenuMinigameActions, public CObjectBase
{
  OBJECT_BASIC_METHODS(ClinicGameMenuProxy);
  ClinicGameMenuProxy();
public:
  ClinicGameMenuProxy( ClinicScreenLogic * _logic ) : logic( _logic ) {}

  virtual bool NeedToShowMinigameMenuItems() { return true; }
  virtual bool OnGameMenuEscapeButton() { return false; }
  virtual void OnGameMenuPopup() {}
  virtual void GameMenuClosed() { logic->GameMenuClosed(); }
  virtual void AbortMinigameLevel() { logic->AbortMinigameLevel(); }

private:
  Weak<ClinicScreenLogic> logic;
};





using namespace NScript;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( ClinicScreenLogic, PF_Minigames::MinigameScreenLogic )
  LUA_METHOD( PopGameMenu )
END_LUA_TYPEINFO( ClinicScreenLogic )


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClinicScreenLogic::ClinicScreenLogic() :
cursorPos(-1.f, -1.f),
scene(NULL),
clinic(NULL),
exitDone(false)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::ProcessCounters()
{
  if( IsValid( clinic ) )
  {
    UpdateGameTime();
   // UpdateGameHearts( clinic->GetHearts() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::MinigameUIStylesDesc& ClinicScreenLogic::GetUIStylesDesc() const
{
  static NDb::MinigameUIStylesDesc error;
  const NDb::DBMinigame_Clinic * pDesc = clinic->GetClinicDesc();
  NI_VERIFY( pDesc,"clinic desc not found", return error);
  return pDesc->uiStyles;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::InitScene(PF_Minigames::Minigames * _minigames, int _levelID)
{
  giftsDialog = new ClinicGiftsDialog;

	clinic = _minigames->GetNativeMinigame<PF_Minigames::Clinic>( "Clinic" );
  clinic->SetOvertips(this);

	NI_VERIFY( IsValid( clinic ), "", return );

	scene = _minigames->GetNativeMain()->GetScene();

  InitOvertips(scene);

  _minigames->GetNativeMain()->SendWorldCommand(PF_Minigames::CreateStartClinicLevelCommand(_minigames->GetWorldSessionInterface(), _levelID, true));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::OnLeftClick()
{
  CPtr<PF_Minigames::MinigamesMain> mgMain = clinic->GetMinigames()->GetNativeMain();

  if ( IsValid( currentWorldClickPick ) )
    mgMain->SendWorldCommand( PF_Minigames::CreateClinicClickCommand( clinic->GetMinigames()->GetWorldSessionInterface(), currentWorldClickPick->GetObjectID() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::OnRightClick()
{
  CPtr<PF_Minigames::MinigamesMain> mgMain = clinic->GetMinigames()->GetNativeMain();

  mgMain->SendWorldCommand( PF_Minigames::CreateClinicRightClickCommand( clinic->GetMinigames()->GetWorldSessionInterface() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::OnEscapeKey()
{
  PopGameMenu();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::UpdatePick()
{
  if( !IsValid( scene ) || !IsValid( clinic ))
    return;

  NI_ASSERT( cursorPos.x != -1 && cursorPos.y != -1, "Uninitialized cursorPos value" );

  NScene::PickResult pickResult;
  scene->Pick( &pickResult, cursorPos );

  currentWorldClickPick = NULL;
  CPtr<PF_Minigames::MinigameClientObject> newClientPick;

  for ( int i = 0, count = pickResult.usedIntersections; i < count; ++i )
  {
    NScene::Intersection const & intersection = pickResult.intersections[i];
    NScene::SceneObject * sceneObject = intersection.pHull ? intersection.pHull->GetSceneObject() : 0;

    if ( 0 == sceneObject )
      continue;

    if ( !IsValid( sceneObject->GetScene() ) )
      continue;

    if ( clinic->IsMinigameSceneObject( sceneObject ) )
    {
      //world's object pick
      CPtr<PF_Minigames::MinigameWorldObject> worldObject = clinic->GetWorldObject( sceneObject->GetOwnerID() );

      if ( !IsValid( worldObject ) )
        continue;

      if ( !worldObject->ReceiveClicks() )
        continue;

      currentWorldClickPick = worldObject;
      newClientPick = clinic->GetClientObject( currentWorldClickPick->GetObjectID() );
      break;
    }
  }

  CPtr<PF_Minigames::MinigameClientObject> newestClientPick = IsValid( newClientPick ) ? newClientPick->RedirectMouseOver() : NULL;

  //world pick calls
  if ( !IsValid ( currentClientOverPick ) ) //Fix == operation for CPtr<>
    currentClientOverPick = NULL;

  if ( currentClientOverPick != newestClientPick )
  {
    if ( IsValid( currentClientOverPick ) )
      currentClientOverPick->OnMouseLeave();

    if ( IsValid( newestClientPick ) )
      newestClientPick->OnMouseEnter();

    currentClientOverPick = newestClientPick;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::SetCursorPos( const CVec2& _cursorPos )
{
  cursorPos = _cursorPos;
  UpdatePick();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::UpdateGameTime()
{
  float timeLeft = Max(0.f, clinic->GetLevelDuration() - clinic->GetLevelTime());

  if (UI::ImageLabel *lbl = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "GameTime", true ) )
    lbl->SetCaptionTextW(NStr::StrFmtW( L"%u", (unsigned)timeLeft ));

  UI::ProgressBar * pBar = UI::GetChildChecked<UI::ProgressBar>( pBaseWindow, "Clock", true );
  if (pBar)
    pBar->SetProgressValue( timeLeft / clinic->GetLevelDuration() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::UpdateGameHearts(int hearts)
{
  if ( UI::ImageLabel *lbl = UI::GetChildChecked<UI::ImageLabel>( pBaseWindow, "GameHearts", true ) )
    lbl->SetCaptionTextW( NStr::ToUnicode( NStr::StrFmt( "Hearts: %d", hearts) ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::ExitGame()
{
  if ( exitDone ) // $TODO refactor it
    return;

  //Get clinic and creeps desc etc
  PF_Minigames::ClinicLevelUIDesc levelDesc;
  clinic->GetLevelUIDesc(&levelDesc);

  PF_Minigames::ClinicCreepsUIDesc creepsDesc;
  clinic->FillCreepResults(creepsDesc);

  PF_Minigames::MinigameCreeps spawnCreeps;
  clinic->FillCreepSpawnResults(spawnCreeps);

  //Stop clinic level
  CObj<NCore::WorldCommand> worldCommand = PF_Minigames::CreateStopClinicLevelCommand( clinic->GetMinigames()->GetWorldSessionInterface(), spawnCreeps );
  clinic->GetMinigames()->GetNativeMain()->SendWorldCommand( worldCommand );

  //Maybe push gifts dialog over the top
  if(!clinic->GetGiftedPlaces().empty())
  {
    giftsDialog->ResetGifts();
    const PF_Minigames::Clinic::ClinicPlaces & gifts = clinic->GetGiftedPlaces();
    for(PF_Minigames::Clinic::ClinicPlaces::const_iterator it = gifts.begin(); it != gifts.end(); ++it)
      giftsDialog->AddGift( it->second );
    giftsDialog->PopUp();
  }

  //Create and push results screen
  Weak<PF_Minigames::ClinicResultsScreen> clinicResultsScreen = new PF_Minigames::ClinicResultsScreen();
  clinicResultsScreen->InitResults(creepsDesc, levelDesc, clinic->GetClinicDesc());
  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( clinicResultsScreen ) );

  //Pop self
  NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( "ClinicScreen" ) );

  exitDone = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::PopGameMenu()
{
  if( IsValid( clinic ) )
    if( clinic->GetGameMode() == PF_Minigames::EClinicGameMode::Shop )
    {
      ExitGame();
      return;
    }

  if(clinic->IsPaused())
    return;
  clinic->InitiatePause( true );

  //CObj<NGameX::GameMenuScreen> screen = new NGameX::GameMenuScreen( this );
  //NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( screen ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::Step( float deltaTime )
{
  if( !IsValid( clinic ) )
    return;
  if( !IsValid( clinic->GetMinigames()->GetWorldSessionInterface() ) )
    return;

  MinigameScreenLogic::Step( deltaTime );

  ProcessCounters();

  StepOvertips();

  if ( IsValid( clinic ) )
  {
    if ( PF_Minigames::EClinicGameMode::GameIsLosed == clinic->GetGameMode() || 
      PF_Minigames::EClinicGameMode::GameIsWon == clinic->GetGameMode() )
    {
      ExitGame();
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClinicScreenLogic::GetCursor( string * id, const UI::Point & screenCoords ) const
{
  if( MinigameScreenLogic::GetCursor( id, screenCoords ) )
    return true;

  if ( IsValid( currentWorldClickPick ) )
    *id = "Cur_Pointer_Red";
  else
    *id = "Cur_Pointer_Green";

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::GameMenuClosed()
{
  if( IsValid( clinic ) )
    clinic->InitiatePause( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClinicScreenLogic::AbortMinigameLevel()
{
  //этот механизм в Клинике недоделан
  //TODO: вообще лучше реализовать интерфейс NGameX::IGameMenuMinigameActions в объекте Clinic

  if( IsValid( clinic ) )
    clinic->InitiatePause(false);

  ExitGame();
}

} //namespace UI
