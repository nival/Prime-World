#include "stdafx.h"

#include "PaintLogic.h"

#include "DBEasel.h"
#include "LuxDef.h"
#include "EaselNotifications.h"
#include "PaintFlyingNotification.h"
#include "LuxAlchemistBoostsNotifications.h"

#include "EaselWorld.h"
#include "LuxGameLogic.h"
#include "LuxGameBoard.h"

#include "Easel.h"

#include "PaintPoint.h"
#include "PaintFragment.h"

#include "BoostBoard.h"


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PaintLogic::PaintLogic( PF_Core::IWorld* _pWorld, EaselWorld* _world ) : 
  PF_Core::WorldObjectBase( _pWorld, false ),
  fIsCompletePainted(true),
  world(_world)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PaintLogic::~PaintLogic()
{
  UninitLogic();
}

void PaintLogic::GetColorCurrentCapacity( ColorCapacity& colorCapacity ) const
{
  colorCapacity.clear();

  PaintFragments::const_iterator it = paintFragments.begin();
  PaintFragments::const_iterator last = paintFragments.end();

  for ( ; it != last; ++it )
  {
    CPaintFragment::FragmentPoints::const_iterator itP = (*it)->GetPoints().begin();
    CPaintFragment::FragmentPoints::const_iterator lastP = (*it)->GetPoints().end();

    for (; itP != lastP; ++itP )
    {
      colorCapacity[ (*itP)->GetColor() ] += (*itP)->GetRoomLeft();
    }
  }
}

void PaintLogic::OnPaintFlow( const SVector & refpaintPosition, NDb::EColor refpaintColor, int paintAmmount )
{
  CPtr<CPainterPoint> spPoint;
  CPtr<CPaintFragment> spFragment;

  bool nearestPointFound = FillNearestPoint( refpaintPosition, refpaintColor, paintAmmount, spPoint, spFragment );

  if ( nearestPointFound )
  {
    NI_VERIFY(IsValid(spPoint), "PaintLogic: found point is invalid", return);
    NI_VERIFY(IsValid(spFragment), "PaintLogic: found fragment is invalid", return);

    // fragment is found, need to notify view
    SendPaintFlyingNotification( refpaintPosition, spPoint, spFragment, viewNotifier );
  }
  else
  {
    world->GetLogic()->GetBoostBoard()->OnUnusedPaint( refpaintPosition, refpaintColor, paintAmmount );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintLogic::GetNumPaintPoints() const
{
  int _result = 0;

  PaintFragments::const_iterator frIter = paintFragments.begin();
  for(; frIter != paintFragments.end(); ++frIter)
  {
    _result += (*frIter)->GetNumPoints();
  }

  return _result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintLogic::GetPainterPoints( nstl::vector<CObj<CPainterPoint>>& _result )
{
  _result.clear();

  _result.reserve( GetNumPaintPoints() );

  const PaintLogic::PaintFragments& _fragments = GetFragments();
  PaintFragments::const_iterator frIter = _fragments.begin();
  for(; frIter != _fragments.end(); ++frIter)
  {
    const CPaintFragment::FragmentPoints& _points = (*frIter)->GetPoints();
    _result.insert(_result.end(),_points.begin(),_points.end());
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PaintLogic::CalculateFillRatio() const
{
  int amount = 0, capa = 0;
  for ( int i = 0; i < paintFragments.size(); ++i )
  {
    const CPaintFragment * frag = paintFragments[i];
    for ( int j = 0; j < frag->GetPoints().size(); ++j )
    {
      const CPainterPoint * point = frag->GetPoints()[j];
      amount += point->GetAmount();
      capa += point->GetCapacity();
    }
  }

  if ( !capa )
    return 0.0f;

  return (float)amount / (float)capa;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintLogic::InitLogic( Easel* _easel, EaselNotifier* notifier )
{
  NDb::Ptr<NDb::DBPainterFragment> pPainterData = _easel->GetPainterLevelData();
  vector<NDb::DBFragment>::const_iterator fragmentsIter = pPainterData->painterFragment.listFragments.begin();

  for(; fragmentsIter != pPainterData->painterFragment.listFragments.end(); fragmentsIter++)
  {
    CObj<CPaintFragment> spFragment = new CPaintFragment( GetWorld(), *fragmentsIter );
    paintFragments.push_back(spFragment);
  }

  viewNotifier = notifier;

  fIsCompletePainted = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintLogic::UninitLogic()
{
  paintFragments.clear();
  fIsCompletePainted = true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PaintLogic::FillNearestPoint( const SVector & refpaintPosition, NDb::EColor refpaintColor, int paintAmmount, CPtr<CPainterPoint>& spTo, CPtr<CPaintFragment>& spFragment )
{
  NI_VERIFY(paintAmmount >= 0, "PaintLogic: paint amount is less than zero", return false);

  if ( fIsCompletePainted )
    return false;

  // checker data
  int64  closestDist = 0;
  CPainterPoint * closestPoint = 0;
  CPaintFragment * closestFrag = 0;

  // looking for the closest point
  PaintFragments::iterator currFragment = paintFragments.begin();
  for( ; currFragment != paintFragments.end(); currFragment++ )
  {
    int64 distance = 0;
    CPainterPoint * point = (*currFragment)->GetClosestPoint( refpaintPosition, true, refpaintColor, distance, true );
    if ( !point )
      continue;

    if ( !closestPoint || ( distance < closestDist ) )
    {
      closestPoint = point;
      closestFrag = *currFragment;
      closestDist = distance;
    }
  }

  if ( closestPoint )
  {
    // need to increment point fill count
    closestPoint->IncCurrentCapacity( paintAmmount );

    // if fragment completely painted - send notification
    if( !closestPoint->HasRoom() )
      OnFragmentPaintedNotification();

    spTo = closestPoint;
    spFragment = closestFrag;

    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PaintLogic::FillMostWantedPoint( int paintAmmount, CPtr<CPainterPoint> & spToPoint )
{
  NI_VERIFY(paintAmmount >= 0, "PaintLogic: paint amount is less than zero", return false);

  if ( fIsCompletePainted )
    return false;

  // checker data
  int bestRoom = 0;
  CPainterPoint * bestPoint = 0;

  // looking for the closest point
  PaintFragments::iterator currFragment = paintFragments.begin();
  for( ; currFragment != paintFragments.end(); currFragment++ )
  {
    CPainterPoint * point = (*currFragment)->GetLeastFilledPoint();
    if ( !point )
      continue;

    int room = point->GetRoomLeft();

    if ( !bestPoint || ( room > bestRoom ) )
    {
      bestPoint = point;
      bestRoom = room;
    }
  }

  if ( bestPoint && ( bestRoom > 0 ) )
  {
    // need to increment point fill count
    bestPoint->IncCurrentCapacity( paintAmmount );

    // if fragment completely painted - send notification
    if( !bestPoint->HasRoom() )
      OnFragmentPaintedNotification();

    spToPoint = bestPoint;
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintLogic::ProcessStep( int deltaTime, LuxGameLogic* _gameLogic )
{
  if (_gameLogic->GetGameBoard()->GetBoardState() != BOARDSTATE_LEVEL_RUN)
    return LUX_OK;

  // checking if paint is completely painted
  if ( !fIsCompletePainted && CheckPainted() )
  {
    _gameLogic->GetGameBoard()->SetBoardState( BOARDSTATE_LEVEL_WON );
    fIsCompletePainted = true;
  }

  return LUX_OK;
}


bool PaintLogic::CheckPainted()
{
  // checking painted
  PaintFragments::iterator fragmentsIter = paintFragments.begin();
  for(; fragmentsIter != paintFragments.end(); fragmentsIter++)
  {
    if((*fragmentsIter)->CheckIfPainted() == false)
      return false;
  }
  
  return true;
}

void PaintLogic::SendPaintFlyingNotification( const SVector & from, CPainterPoint* spTo, CPaintFragment* spFragment, EaselNotifier* pNotifier )
{
  PaintFlyingNotification *pNotification = new PaintFlyingNotification();
  pNotification->from = from;
  pNotification->spTo = spTo;
  
  if ( IsValid( pNotifier ) )
    pNotifier->Notify(*pNotification);
}

void PaintLogic::OnFragmentPaintedNotification()
{
  world->GetPriestessProxy()->AddGoldDelayed( world->GetLogic()->GetEasel()->GetPriestessLevelStats()->paintFragmentFinishedNafta );
  DevTrace( "MG2 DEBUG: Add gold for FragmentPainted: paintFragmentFinishedNafta(%d) = total(%d)", world->GetLogic()->GetEasel()->GetPriestessLevelStats()->paintFragmentFinishedNafta, world->GetLogic()->GetEasel()->GetPriestessLevelStats()->paintFragmentFinishedNafta );
}

void PaintLogic::InitStatisticForPaint( NDb::EPaintStatistics& stat )
{
  stat.allPaintColors.clear();

  // check all colors for every fragment
  int numFragments = paintFragments.size();
  for(int currColor = 0; currColor < NDb::KnownEnum<NDb::EColor>::sizeOf; ++currColor)
  {
    for(int i = 0; i < numFragments; ++i)
    {
      const CPaintFragment& fragment = *paintFragments[i];

      if(fragment.CheckIfHasColor( NDb::EColor(currColor) ))
      {
        stat.allPaintColors.push_back(NDb::EColor(currColor));
        break;
      }
    }
  }
}

void PaintLogic::ResetStatistics( NDb::EPaintStatistics& stat )
{
  stat.remainPaintCapacity = 0;
  stat.remainColorsToPaint = 0;

  for(int i = 0; i < NDb::KnownEnum<NDb::EColor>::sizeOf; ++i)
  {
    stat.remainColorCapacity[i] = 0;
  }
}

void PaintLogic::GetPaintStatistics( NDb::EPaintStatistics& stat )
{
  // drop statistics
  ResetStatistics( stat );
  InitStatisticForPaint( stat );

  // calculate capacity for every paint fragment
  int numFragments = paintFragments.size();
  //for each color calculate remain capacity
  for(int currColor = 0; currColor < NDb::KnownEnum<NDb::EColor>::sizeOf; ++currColor)
  {
    bool colorPresent = false;
    for(int i = 0; i < numFragments; ++i)
    {
      const CPaintFragment& fragment = *paintFragments[i];

      int remainCapacity = fragment.GetRemainCapacity( NDb::EColor(currColor) );
      NI_VERIFY(remainCapacity >= 0, "PaintLogic: amount of color overflowed its capacity", remainCapacity = 0;)

      if(remainCapacity > 0)
      {
        stat.remainPaintCapacity += remainCapacity;
        stat.remainColorCapacity[ currColor ] += remainCapacity;
        colorPresent = true;
      }
    }

    if(colorPresent)
    {
      ++stat.remainColorsToPaint;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintLogic::FillWithUnusedPaint( int unusedPaintAmount )
{
  if( unusedPaintAmount <= 0 )
    return LUX_OK;

  CPtr<CPainterPoint> point;

  if( FillMostWantedPoint( unusedPaintAmount, point ) )
  {
    NI_VERIFY( IsValid( point ), "", return LUX_ERROR );

    if ( IsValid( viewNotifier ) )
      viewNotifier->Notify( * new LuxAlchemistOutgoinFlowNotification( point->GetColor(), point ) );
  }

  return LUX_OK;
}

}

REGISTER_SAVELOAD_CLASS_NM( PaintLogic, PF_Minigames )
