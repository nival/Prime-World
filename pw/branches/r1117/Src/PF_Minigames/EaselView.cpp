#include "stdafx.h"

#include "EaselView.h"
#include "Easel.h"

#include "EaselLuxView.h"
#include "EaselPaintView.h"
#include "EaselViewEffects.h"

#include "EaselWorld.h"

#include "MinigameSessionInterface.h"
#include "EaselMinigame.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselView::EaselView( Easel* _easel, bool local /*= true*/ ) :
  easel(_easel)
{
  if ( local )
  {
    luxorView = new EaselLuxView( easel );
    paintView = new EaselPaintView();
    effects = new EaselViewEffects();

    effects->Init(*_easel);
  }
}

EaselView::~EaselView()
{
  Reset();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EaselView::Step( float deltaTime, EaselWorld* _world )
{
  IMinigames * mgs = _world->GetEasel()->GetWorldSessionInterface()->GetMinigames();
  EaselMinigame * minigame = dynamic_cast<EaselMinigame*>(  mgs->GetMinigame( "Easel" ) );

  if ( luxorView && minigame->GetVisualState() == NDb::MINIGAMEVISUALSTATE_EASEL_INGAME )
    luxorView->Step( deltaTime, _world->GetLogic() );

  return true;
}

void EaselView::Update( float deltaTime, EaselWorld* _world )
{
  IMinigames * mgs = _world->GetEasel()->GetWorldSessionInterface()->GetMinigames();
  EaselMinigame * minigame = dynamic_cast<EaselMinigame*>(  mgs->GetMinigame( "Easel" ) );

  if ( luxorView && minigame->GetVisualState() == NDb::MINIGAMEVISUALSTATE_EASEL_INGAME )
    luxorView->Update( deltaTime, _world->GetLogic() );

  if ( effects && minigame->GetVisualState() == NDb::MINIGAMEVISUALSTATE_EASEL_INGAME )
    effects->Update( deltaTime, _world->GetLogic() );

  if ( paintView && minigame->GetVisualState() == NDb::MINIGAMEVISUALSTATE_EASEL_INGAME )
    paintView->Update( deltaTime, _world->GetLogic() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselView::Reset()
{
  if ( luxorView )
	  luxorView->Reset();
  if ( effects )
    effects->Reset();
}

void EaselView::InitAfterWorld( EaselWorld* _world )
{
  if ( luxorView )
    luxorView->InitAfterWorld( _world->GetLogic() );
}

void EaselView::ReleaseAfterWorld( EaselWorld* _world )
{
  if ( luxorView )
    luxorView->ReleaseAfterWorld( _world->GetLogic() );
}

}

REGISTER_SAVELOAD_CLASS_NM( EaselView, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselNullView, PF_Minigames )
