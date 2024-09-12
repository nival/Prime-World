#include "stdafx.h"

#include "EaselPaintView.h"
#include "EaselPaintViewFragment.h"

#include "EaselPaintLayerSceneComponent.h"
#include "EaselPaintViewPicture.h"
#include "MinigameClientObject.h"

#include "Easel.h"

#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "PaintLogic.h"

namespace PF_Minigames
{

EaselPaintView::EaselPaintView() :
  hidden(true)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintView::InitPicture( LuxGameLogic* _gameLogic )
{
  CObj<EaselPaintViewPicture> newPicture = new EaselPaintViewPicture();
  if( newPicture->Init( *_gameLogic->GetEasel() ) )
  {
    picture = newPicture;
    _gameLogic->GetEasel()->GetClient().AddObject( newPicture, false );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintView::ReleasePicture( LuxGameLogic* _gameLogic )
{
  _gameLogic->GetEasel()->GetClient().ReleaseObject( picture );
  picture = 0;
}

void EaselPaintView::Update( float deltaTime, LuxGameLogic* _gameLogic )
{
  if ( !IsValid( _gameLogic->GetGameBoard() ) )
    return;

  LuxBoardState state = _gameLogic->GetGameBoard()->GetBoardState();

  bool inGame = ( state == BOARDSTATE_LEVEL_RUN || state == BOARDSTATE_LEVEL_WON || 
                  state == BOARDSTATE_LEVEL_WON_BLAST_BALLS || state == BOARDSTATE_LEVEL_FAIL );

  if ( inGame && hidden )
  {
    CreateAll( _gameLogic );
    hidden = false;
  }

  if ( !inGame && !hidden )
  {
    DestroyAll( _gameLogic );
    hidden = true;
  }

  if ( !hidden )
  {
    // search for registered fragment
    FragmentClientObjects::iterator it = fragmentObjects.begin();
    FragmentClientObjects::iterator last = fragmentObjects.end();

    for ( ; it != last; ++it )
    {
      it->second->UpdateState();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintView::DestroyAll( LuxGameLogic* _gameLogic )
{
  FragmentClientObjects::iterator it = fragmentObjects.begin();
  FragmentClientObjects::iterator last = fragmentObjects.end();

  for ( ; it != last; ++it )
  {
    _gameLogic->GetEasel()->GetClient().ReleaseObject( CPtr<MinigameClientObject>( it->second ) );
  }

  fragmentObjects.clear();

  ReleasePicture( _gameLogic );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintView::CreateAll( LuxGameLogic* _gameLogic )
{
  InitPicture( _gameLogic );

  const PaintLogic::PaintFragments& paintFragments = _gameLogic->GetPaintLogic()->GetFragments();

  NDb::Ptr<NDb::DBPainterFragment> pPainterData = _gameLogic->GetEasel()->GetPainterLevelData();
  vector<NDb::DBFragment>::const_iterator fragmentsIter = pPainterData->painterFragment.listFragments.begin();

  NI_VERIFY( paintFragments.size() ==  pPainterData->painterFragment.listFragments.size(), "Wrong painter fragment number", return );

  PaintLogic::PaintFragments::const_iterator it = paintFragments.begin();
  PaintLogic::PaintFragments::const_iterator last = paintFragments.end();

  for ( ; it != last; ++it, ++fragmentsIter )
  {
    CObj<EaselPaintViewFragment> newFragment = new EaselPaintViewFragment();

    if( newFragment->Init(*_gameLogic->GetEasel(), picture->GetPaint(), *it, &(*fragmentsIter) ) )
    {
      fragmentObjects[ it->GetPtr() ] = newFragment;
      _gameLogic->GetEasel()->GetClient().AddObject( newFragment, false );

      newFragment->ShowFragment();
    }
  }
}

} // PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::EaselPaintView);