#include "StdAfx.h"
#include "CharInfoContainer.h"

#include "../ui/FlashContainer2.h"

#include "CharInfoController.h"
#include "FlashFSCommands.h"
#include "UIEventHandler.h"

#include "PFMaleHero.h"

namespace NGameX
{

CharInfoContainer::CharInfoContainer( UI::FlashContainer2* flashContainer, UI::ImageLabel* _tooltipWnd, NDb::Ptr<NDb::DBUIData> _uiData,
                                      AdventureFlashInterface* _flashInterface, IUIEventHandler * _eventHandler )
  : flashInterface( _flashInterface )
  , flashWnd( flashContainer )
  , uiData( _uiData )
  , tooltipWnd( _tooltipWnd )
  , eventHandler(_eventHandler)
{
  using namespace FlashFSCommands;

  flashWnd->AddFSListner( ConvertToString( FillCharStatForUnit ), this );
  flashWnd->AddFSListner( ConvertToString( OpenTalentsForUnit  ), this );
  flashWnd->AddFSListner( ConvertToString( StartSpectate ), this );

  selectionCharInfoController = new CharInfoController( flashWnd, tooltipWnd, uiData, flashInterface, CharType::Selection );
}

CharInfoContainer::~CharInfoContainer()
{
  using namespace FlashFSCommands;
  flashWnd->RemoveFSListner( ConvertToString( FillCharStatForUnit ) );
}

void CharInfoContainer::Update( int mouseX, int mouseY )
{
  //update our controller
  UpdateController( charInfoController, mouseX, mouseY );
  UpdateController( selectionCharInfoController, mouseX, mouseY );

  //update all heroes controller
  for ( HeroControllers::iterator iter = heroControllers.begin(); iter != heroControllers.end(); ++iter )
  {
    UpdateController( iter->second, mouseX, mouseY );
  }
}

void CharInfoContainer::UpdateController( CharInfoController* controller, int mouseX, int mouseY )
{
  if ( !IsValid( ourHero ) || !controller )
  {
    return;
  }

  const NWorld::PFBaseUnit* unit = controller->GetUnit();
  bool isVisible = IsValid( unit ) ? unit->IsVisibleForFaction( ourHero->GetFaction() ) : false;
  controller->Update( mouseX, mouseY, isVisible );
}

void CharInfoContainer::SetOurHero( const NWorld::PFBaseHero* _hero )
{
  ourHero = _hero;

  charInfoController = 0;
  charInfoController = new CharInfoController( flashWnd, tooltipWnd, uiData, flashInterface, CharType::OurHero );

  //our char stat is always active
  charInfoController->SetUnit( _hero, true );
  charInfoController->ActivateStats( true );
}

void CharInfoContainer::AddHero( const NWorld::PFBaseHero* _hero )
{
  if ( !IsValid( _hero ) )
  {
    return;
  }

  CharInfoController* controller = new CharInfoController( flashWnd, tooltipWnd, uiData, flashInterface, CharType::Selection );

  heroControllers[_hero->GetPlayerId()] = controller;
  bool isVisible = IsValid(ourHero) ? _hero->IsVisibleForFaction( ourHero->GetFaction() ) : false;
  controller->SetUnit( _hero, isVisible );
}

void CharInfoContainer::SetSelectionUnit( const NWorld::PFBaseUnit* _unit )
{
  selectionUnit = _unit;
}

void CharInfoContainer::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
  using namespace FlashFSCommands;

  if ( !IsValid( uiData ) )
  {
    return;
  }

  int isHero = 0;
  int heroId = 0;


  switch ( ConvertToFSCommand( listenerID ) )
  {
  case FillCharStatForUnit:
    {
      sscanf_s( args, "%d %d", &isHero, &heroId );

      if( currentCharInfoController && currentCharInfoController->IsStatsActive() )
      {
        currentCharInfoController->ActivateStats( false );
      }

      if ( !isHero )
      {
        selectionCharInfoController->SetUnit( selectionUnit );
        currentCharInfoController = selectionCharInfoController;
      }
      else
      {
        if ( heroControllers.find( heroId ) == heroControllers.end() )
        {
          return;
        }

        currentCharInfoController = heroControllers[heroId];
      }

      currentCharInfoController->ActivateStats( true );
      break;
    }
  case OpenTalentsForUnit:
    {
      sscanf_s( args, "%d %d", &isHero, &heroId );

      if ( isHero == 0 )
      {
        return;
      }

      if( currentTalentsController && currentTalentsController->IsTalentsActive() )
      {
        currentTalentsController->ActivateTalents( false );
      }

      if ( heroControllers.find( heroId ) == heroControllers.end() )
      {
        return;
      }

      currentTalentsController = heroControllers[heroId];
      currentTalentsController->ActivateTalents( true );
      break;
    }

  case StartSpectate:
    {
      sscanf_s( args, "%d", &heroId );

      if (eventHandler)
        eventHandler->StartSpectateById(heroId);

      break;
    }
    
  default:
    NI_ALWAYS_ASSERT( "Something bad happened to the CharInfoContainer listener" );
  }
}

}

NI_DEFINE_REFCOUNT( NGameX::CharInfoContainer )
