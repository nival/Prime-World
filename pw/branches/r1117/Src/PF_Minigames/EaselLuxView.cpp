#include "stdafx.h"

#include "Core/Transceiver.h"

#include "EaselLuxView.h"


#include "LuxBallCreateNotification.h"
#include "LuxBallDeleteNotification.h"
#include "LuxBallHitNotification.h"
#include "LuxChainBallAddedNotification.h"
#include "EaselWorldClientConvertHelper.h"

#include "MinigameClientObject.h"

#include "LuxPath.h"

#include "Easel.h"
#include "EaselPaintBlastBallView.h"
#include "EaselBallView.h"
#include "EaselLuxViewPlatform.h"
#include "EaselLuxViewFallingObject.h"
#include "EaselLuxViewTunnelPoint.h"
#include "EaselLuxViewPath.h"
#include "EaselView.h"
#include "EaselViewEffects.h"
#include "EaselWorld.h"
#include "EaselSoundsInterface.h"

#include "Easel.h"

#include "DBEasel.h"

#include "../PF_Core/BasicEffect.h"
#include "../PF_Core/EffectsPool.h"

#include "LuxGameLogic.h"
#include "LuxPlatformBoard.h"
#include "LuxGameBoard.h"
#include "LuxFallingBoard.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselLuxView::EaselLuxView() :
  easel( 0 ),
  levelStarted(false),
  clientIsFrozen(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselLuxView::EaselLuxView( Easel* _easel ) :
  easel( _easel ),
  levelStarted(false),
  clientIsFrozen(false)
{
  subConverter = new PathConverter( _easel );
  pathConverter = new BallCoordsConverter( subConverter );

  easel->GetNotifier()->Register( *this );
  SubscribeUpdates();
}

void EaselLuxView::InitAfterWorld( LuxGameLogic* _gameLogic )
{
  levelStarted = false;
  CreatePlatform( _gameLogic->GetPlatformBoard()->GetPlatform() );
  CreatePaths( _gameLogic );
  CreateTunnels( _gameLogic );
}

void EaselLuxView::ReleaseAfterWorld( LuxGameLogic* _gameLogic )
{
  ballPaths.clear();
  clientObjects.clear();
  platformObject = 0;
  easel->GetClient().ReleaseAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::Reset()
{
  for ( FallingObjects::iterator it = fallingObjects.begin(); it != fallingObjects.end(); ++it)
  {
    // NUM_TASK ѕадало, тк easel уже был удален. ј вот почему такой пор€док, наверное будут разбиратьс€ в NUM_TASK
    if ( IsValid(easel) )
      easel->GetClient().ReleaseObject( *it );
  }
  fallingObjects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::SubscribeUpdates()
{
	Subscribe( &EaselLuxView::CreateBallHandler );
	Subscribe( &EaselLuxView::DeleteBallHandler );
  Subscribe( &EaselLuxView::ChainBallAddedHandler );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::AddBall( LuxBall * ball )
{
  NI_VERIFY(IsValid(easel), "", return );

  if ( !IsValid( ball ) )
    return;

  switch ( ball->Type() )
  {
    case EBallType::Simple:
    case EBallType::Joker:
      return AddCommonBall( ball );
    case EBallType::PainBlast:
      return AddPainBlastBall( ball );
  }
}

void EaselLuxView::AddPainBlastBall( LuxBall* ball )
{
  CObj<EaselPainBlastBallView> newBall = new EaselPainBlastBallView;

  if( newBall->Init( *easel, ball, pathConverter ) )
  {
    // setting up client objects
    clientObjects[ball] = newBall;
    easel->GetClient().AddObject( newBall, false );

    // placing created object in lerp container
    lerpContainer.AddLerpProcessor( newBall->GetLerpProcessor() );
  }
}

void EaselLuxView::AddCommonBall( LuxBall* ball )
{
  CObj<EaselBallView> newBallView = new EaselBallView;

  if( newBallView->Init( *easel, ball, pathConverter ) )
  {
    // disabling speed component
    newBallView->EnableComponent( "trail", false );

    // setting up client objects
    clientObjects[ball] = newBallView;
    easel->GetClient().AddObject( newBallView, false );

    // placing created object in lerp container
    lerpContainer.AddLerpProcessor( newBallView->GetLerpProcessor() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::DeleteBall( void* ball )
{
  ReleaseClientObject( ball );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::CreateBallHandler(const LuxBallCreateNotification& notification)
{
  DeleteBall(notification.ball);
  AddBall(notification.ball);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::DeleteBallHandler(const LuxBallDeleteNotification& notification)
{
  DeleteBall( notification.ballPointer );
}

void EaselLuxView::StartPickEffect()
{
  NI_VERIFY( IsValid( easel ), "", return );

  NI_VERIFY( IsValid( platformObject ), "", return );

  NDb::Ptr<NDb::BasicEffectAttached> dbEffect = easel->GetData()->commonParams->effects.coinPickUp; 
  CObj<PF_Core::BasicEffectAttached> effect = easel->GetClient().CreateAttachedEffect( dbEffect, false );
  if( !effect )
    return;

  platformObject->AttachEffect( effect );

  easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_COIN_CATCHED);
}


void EaselLuxView::CreatePlatform( LuxPlatform* _worldPlatform )
{
  CObj<EaselLuxViewPlatform> newPlatform = new EaselLuxViewPlatform();  

  if( newPlatform->InitPlatform(*easel, _worldPlatform) )
  {
    ReleaseClientObject( platformObject.GetPtr() );
    platformObject = newPlatform;
    easel->GetClient().AddObject( newPlatform, false );

    // placing created object in lerp container
    lerpContainer.AddLerpProcessor(newPlatform->GetLerpProcessor());
  }
}


void EaselLuxView::CreatePaths( LuxGameLogic* _gameLogic )
{
  LuxorPaths::const_iterator it = _gameLogic->GetGameBoard()->GetPaths().begin();
  LuxorPaths::const_iterator last = _gameLogic->GetGameBoard()->GetPaths().end();

  for ( ; it != last; ++it )
  {
    CObj<EaselLuxViewPath> viewPath = new EaselLuxViewPath( easel, *it );
    ballPaths.insert( make_pair( (*it)->GetID(), viewPath ) );
  }
}


void EaselLuxView::CreateTunnels( LuxGameLogic* _gameLogic )
{
  float startOffset =_gameLogic->GetGameData()->commonParams->tunnels.startPointOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  float endOffset = _gameLogic->GetGameData()->commonParams->tunnels.endPointOffset * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

  LuxorPaths::const_iterator it = _gameLogic->GetGameBoard()->GetPaths().begin();
  LuxorPaths::const_iterator last = _gameLogic->GetGameBoard()->GetPaths().end();

  for ( ; it != last; ++it )
  {
    const CPtr<PolylineTrajectory>& _trajectory = (*it)->GetTrajectory();

    const nstl::vector<NDb::DBTunnel>& tunnels = (*it)->GetTunnels();

    nstl::vector<NDb::DBTunnel>::const_iterator tunnelIter = tunnels.begin();

    for ( ; tunnelIter != tunnels.end(); ++tunnelIter )
    {
      int64 _begin = tunnelIter->begin * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
      int64 _end   = tunnelIter->end * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

      SVector beginPoint;
      SVector endPoint;

      _trajectory->GetCoordsByLenght( _begin + startOffset, beginPoint );
      _trajectory->GetCoordsByLenght( _end + endOffset, endPoint );

      CreateTunnelPoint( beginPoint );
      CreateTunnelPoint( endPoint );
    }
  }
}

void EaselLuxView::CreateTunnelPoint( const SVector& _point )
{
  CObj<EaselLuxViewTunnelPoint> newTunnelPoint = new EaselLuxViewTunnelPoint();

  if ( newTunnelPoint->Init( *easel, _point ) )
  {
    decorativeObjects.push_back( newTunnelPoint.GetPtr() );
    easel->GetClient().AddObject( newTunnelPoint, false );
    newTunnelPoint->SetVisible( false );
  }
}

void EaselLuxView::ChainBallAddedHandler(const LuxChainBallAddedNotification& notification)
{
  if(IsValid(notification.path) == false || IsValid(notification.ball) == false)
    return;

  CPtr<LuxBall> _ball = notification.ball;

  // найти траекторию
  Paths::iterator pathIter = ballPaths.find(notification.path->GetID());
  if(pathIter == ballPaths.end())
    return;

  TClientObjects::iterator itFound = clientObjects.find(_ball);
  if( itFound == clientObjects.end() )
    return;

  if ( !IsValid( itFound->second ) )
    return;

  EaselBallView *pviewDrop = 0;
  pviewDrop = CastToUserObject(itFound->second.GetPtr(), (EaselBallView *)0);
  if(pviewDrop != 0)
  {
    CObj<EaselBallViewLerp> newLerp = new EaselBallViewLerp( _ball, pathIter->second->GetCoordsConverter() );
    NI_VERIFY( IsValid( newLerp ), "EaselLuxView: Unable to process ChainBallAddedHandler (lerp object not created)", return );

    // restore current placement;
    CPtr<ILuxViewLerp> currentLerp = pviewDrop->GetLerpProcessor();

    if( IsValid( currentLerp ) )
    {
      Placement currentPlacement;
      if( currentLerp->vLerp( currentPlacement ) )
      {
        newLerp->ForcePlacement( currentPlacement );
      }
    }

    // setting new lerp 
    pviewDrop->SetLerpProcessor(newLerp);
    lerpContainer.AddLerpProcessor(newLerp);
    return;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselLuxView::ReleaseClientObject(void* logicObject)
{
	NI_VERIFY(IsValid(easel), "EaselLuxView: strange. easel already dead", return );

	TClientObjects::iterator itFound = clientObjects.find(logicObject);
  if( itFound != clientObjects.end() )
    if ( IsValid( itFound->second ) )
    {
      easel->GetClient().ReleaseObject( CPtr<MinigameClientObject>(itFound->second) );
      clientObjects.erase(itFound);
    }
}

void EaselLuxView::Step( float deltaTime, LuxGameLogic* _gameLogic )
{
  lerpContainer.Step( easel->GetScene()->GetStepLengthInSeconds() );

  if ( ( _gameLogic->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_RUN )  &&
       ( !levelStarted ) )
  {
    OnLevelStarted();
    levelStarted = true;
  }

  if ( ( _gameLogic->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_FAIL || 
         _gameLogic->GetGameBoard()->GetBoardState() == BOARDSTATE_LEVEL_WON ) &&
       ( levelStarted ) )
  {
    OnLevelFinished();
    levelStarted = false;
   }
   
  CheckFreezeBoost( _gameLogic );

  StepFallingObjects( _gameLogic );
}

void EaselLuxView::Update( float deltaTime, LuxGameLogic* _gameLogic )
{
  Paths::iterator it = ballPaths.begin();
  Paths::iterator last = ballPaths.end();

  for ( ; it != last; ++it )
  {
    it->second->Step( deltaTime, _gameLogic );
  }
}

void EaselLuxView::OnLevelStarted()
{
  DecorativeObjects::iterator it = decorativeObjects.begin();
  DecorativeObjects::iterator last = decorativeObjects.end();

  for ( ; it != last; ++it )
  {
    (*it)->OnLevelStarted();
  }
}

void EaselLuxView::OnLevelFinished()
{
  DecorativeObjects::iterator it = decorativeObjects.begin();
  DecorativeObjects::iterator last = decorativeObjects.end();

  for ( ; it != last; ++it )
  {
    (*it)->OnLevelFinished();
  }
}

void EaselLuxView::CheckFreezeBoost( LuxGameLogic* _gameLogic )
{
  if ( _gameLogic->GetGameBoard()->IsFrozen() && !clientIsFrozen )
  {
    easel->GetView()->GetEffects()->OnFreeze();
    easel->GetWorld()->GetSound()->PlaySound(NDb::EASELSOUNDTYPE_BOOST_FREEZE_CLICK);
    clientIsFrozen = true;
  }

  if ( !_gameLogic->GetGameBoard()->IsFrozen() && clientIsFrozen )
  {
    easel->GetView()->GetEffects()->OnUnfreeze();
    clientIsFrozen = false;
  }
}

void EaselLuxView::StepFallingObjects( LuxGameLogic* _gameLogic )
{
  for ( FallingObjects::iterator it = fallingObjects.begin(); it != fallingObjects.end(); )
  {
    if ( (*it)->IsPicked() )
      StartPickEffect();

    if ( !(*it)->IsWorldObjectValid() || (*it)->IsPicked() )
    {
      easel->GetClient().ReleaseObject( *it );
      it = fallingObjects.erase( it );
    }
    else
      ++it;
  }

  {
    LuxFallingBoard::FallingObjects::iterator itF = _gameLogic->GetFallingBoard()->GetFallingObjects().begin();
    LuxFallingBoard::FallingObjects::iterator lastF = _gameLogic->GetFallingBoard()->GetFallingObjects().end();

    for ( ; itF != lastF; ++itF )
    {
      if ( (*itF)->GetClientID() == -1 )
      {
        CObj<EaselLuxViewFallingObject> newObject = new EaselLuxViewFallingObject();
        newObject->Init( _gameLogic->GetEasel(), *itF );
        easel->GetClient().AddObject( newObject, false );

        fallingObjects.push_back( newObject );

        (*itF)->SetClientID( 1 );
      }
    }
  }
}


} // PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::EaselLuxView);
