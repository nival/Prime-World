#include "stdafx.h"
#include "LuxGameBoard.h"

#include "PF_Core/BasicEffect.h"

#include "DBEasel.h"
#include "PF_GameLogic/DBMinigamesTypes.h"
#include "PF_GameLogic/PFEaselPlayer.h"

#include "LuxPath.h"

#include "LuxBallHitNotification.h"

#include "LuxPlatform.h"

#include "LuxChainGenerator.h"
#include "LuxGameBoardChains.h"

#include "LuxChainMovingNotification.h"
#include "LuxChainStoppedNotification.h"

#include "LuxChainFallingNotification.h"

#include "LuxBoardRequestStateChangeNotification.h"

#include "Easel.h"
#include "EaselWorld.h"

#include "EaselGameWonNotitfication.h"
#include "EaselGameLostNotitfication.h"

#include "LuxMagnet.h"

#include "LuxGameLogic.h"
#include "LuxPlatformBoard.h"


namespace PF_Minigames
{

int EASEL_AFTER_EXIT_DISTANCE = 1500;

int EASEL_SPLINE_FALLING_CHAIN_SPEED = 80;

int EASEL_LEVEL_END_DELAY1 = 1000;

int EASEL_LEVEL_END_DELAY2 = 4000;

int EASEL_LEVEL_FAIL_END_DELAY = 4000;

const int MAX_EASEL_CHAINS = 5;

//////////////////////////////////////////////////////////////////////////
void ResetChainStatistics(NDb::EChainStatistics& chainStatistic)
{
  chainStatistic.allBallsNum = 0;

  for(int i = 0; i < NDb::KnownEnum<NDb::EColor>::sizeOf; ++i)
  {
    chainStatistic.colorBallsNum[i] = 0;
  }
}

//////////////////////////////////////////////////////////////////////////
struct CollideBalls
{
  CollideBalls() : bestTime(INT_MAX), collisionFound(false) {}

  double bestTime;
  bool collisionFound;

  CPtr<LuxBall> bullet;
  CPtr<LuxBall> bestBall;

  CPtr<LuxBallChain> currentChain;
  CPtr<LuxBallChain> bestChain;

  CPtr<LuxGameBoardChain> currentPath;
  CPtr<LuxGameBoardChain> bestPath;

  // $TODO [AZ] Ќадо всЄ это в онднородную массу превратить
  CPtr<ICollidable> bestCollider;

  void operator ()( LuxBall* ball )
  {
    double collisionTime = 0;

    if ( !ball->CanCollide() )
      return;

    if ( bullet->GetCollisionTime( ball, collisionTime ) )    
    {
      if ( collisionTime < bestTime )
      {
        bestTime = collisionTime;
        bestChain = currentChain;
        bestPath = currentPath;
        bestBall = ball;
        collisionFound = true;
      }
    }
  }

  void CollideWithOthers( LuxGameBoard::Colliders& colliders, LuxBall* ball )
  {
    LuxGameBoard::Colliders::iterator it = colliders.begin();
    LuxGameBoard::Colliders::iterator last = colliders.end();

    for ( ; it != last; ++it )
    {
      double collisionTime = 0;

      if ( (*it)->IsExhausted() )
        continue;

      if ( ball->GetCollisionTime( *it, collisionTime ) )    
      { 
        if ( collisionTime < bestTime )
        {
          bestCollider = *it;
          bestTime = collisionTime;
          collisionFound = true;
        }      
      }
    }
  }
};

void ProcessPaintBlastExplosion(const BoardChains &_chains,const SVector &_refBlastPos)
{
  BoardChains::const_iterator chainsIter = _chains.begin();
  for(; chainsIter != _chains.end(); ++chainsIter)
    (*chainsIter)->ProcessPaintBlast(_refBlastPos, 3 * EaselConst::Get_BALL_DEF_DIAMETER() );
}

bool IsChainOnBoard(const BoardChains &_chains)
{
  BoardChains::const_iterator chainsIter = _chains.begin();
  for(; chainsIter != _chains.end(); ++chainsIter)
  {
    if ( !(*chainsIter)->GetChains().empty()  )
      return true;
  }

  return false;
}

bool IsAnyChainOnBoardMoving(const BoardChains &_chains)
{
  BoardChains::const_iterator chainsIter = _chains.begin();
  for(; chainsIter != _chains.end(); ++chainsIter)
  {
    if ( (*chainsIter)->IsAnyChainMoving()  )
      return true;
  }
  
  return false;
}

void SetBoardChainsSpeed(const BoardChains &_chains,int _speed)
{
  BoardChains::const_iterator chainsIter = _chains.begin();
  for(; chainsIter != _chains.end(); ++chainsIter)
  {
    (*chainsIter)->SetChainsSpeed(_speed);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxGameBoard::LuxGameBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic, NWorld::PFEaselPlayer* _player ) 
: ILuxBoard( BOARD_GAME, _gameLogic )
, PF_Core::WorldObjectBase( _pWorld, false )
, isFrozen(false)
, boardState(BOARDSTATE_NONE)
, waitTimer(0)
, player(_player)
{
  chains.reserve(MAX_EASEL_CHAINS);
  chainPaths.reserve(MAX_EASEL_CHAINS);

  // getting chains spline path objects
  InitPaths();

  chainsGenerator = new LuxChainGenerator( _pWorld );
  chainsGenerator->Init( gameLogic->GetNotifier(), _gameLogic->GetEasel()->GetRandomSeed() );

  NDb::Ptr<NDb::DBEaselData> pDBData = _gameLogic->GetGameData();
  InitChainsData( _gameLogic->GetEasel()->GetData(), gameLogic->GetNotifier() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxGameBoard::~LuxGameBoard()
{

}


void LuxGameBoard::InitPaths()
{
  int levelID = gameLogic->GetEasel()->GetLevelID();
  int trajectory = gameLogic->GetEasel()->SelectTrajectory();

  if ( trajectory < 0 )
    return;

  NDb::Ptr<NDb::DBEaselSpline> splineData =  gameLogic->GetGameData()->game->trajectories[ trajectory ];

  if ( !IsValid( splineData ) )
    return;

  nstl::vector<NDb::Ptr<NDb::DBEaselPath>>::const_iterator it = splineData->path.begin();
  nstl::vector<NDb::Ptr<NDb::DBEaselPath>>::const_iterator last = splineData->path.end();

  for ( int pathId = 1 ;it != last; ++it, ++pathId )
  {
    CObj<LuxPath> path = new LuxPath( gameLogic->GetEasel()->GetPFWorld(), pathId, levelID, it->GetPtr() );
    chainPaths.push_back(path);    
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxGameBoard::vProcessInput( const SEaselMouseInput & mouseInput )
{
  if ( mouseInput.leftBtnClicked || mouseInput.rightBtnClicked )
    SkipMovie();

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxGameBoard::vProcessKeyboardEvent( EEaselKeyboardEvents::Enum event )
{
  switch ( event )
  {
    default:
      break;

    case EEaselKeyboardEvents::SkipMovie:
      if ( SkipMovie() )
        return true;
      break;
  }

  return false;
}


void LuxGameBoard::AddCollider( ICollidable* _collidable )
{
  colliders.push_back( _collidable );
}

bool LuxGameBoard::SkipMovie()
{
  switch( boardState )
  {
    case BOARDSTATE_LEVEL_BEGIN:
      RequestStateChange(BOARDSTATE_LEVEL_RUN);
      return true;

    case BOARDSTATE_LEVEL_WON_MOVIE:
      {
        EaselLevelWonSkipNotification *pnotification = new EaselLevelWonSkipNotification();

        if ( IsValid( gameLogic->GetNotifier() ) )
          gameLogic->GetNotifier()->Notify(*pnotification);   

        SetBoardState( BOARDSTATE_LEVEL_WON_FINAL );
        return true;
      }

    case BOARDSTATE_LEVEL_FAIL:
      //ѕрикинемс€, будто мы обработали запрос. Ётим мы запретим по€вление Escape-меню во врем€ анимации провала уровн€
      return true;
  }

  return false;
}


bool LuxGameBoard::CollideAndAddBullet( LuxBall* _bullet, int deltaTime )
{
  if ( !IsValid( _bullet ) )
    return false;

  CollideBalls collider;

  collider.bullet = _bullet;

  for (BoardChains::iterator it = chains.begin() ; it != chains.end(); ++it )
    (*it)->ForAllChains( collider );

  collider.CollideWithOthers( colliders, _bullet );

  if ( IsValid( collider.bestCollider ) && ( collider.bestTime < double( deltaTime ) ) )
  {
    if ( collider.bestCollider->Hit() )
    {
      double X = 0.0, Y = 0.0;

      _bullet->GetCollisionPoint( collider.bestCollider, collider.bestTime, X, Y );
      _bullet->SetState( BALL_STATE_EXPLODED );
      _bullet->SetPosition( SVector( X, Y ) );

      return true;
    }
  }

  if ( collider.collisionFound && ( collider.bestTime < double( deltaTime ) ) )
  {
    bool fColorMatched = true;

    if ( _bullet->Type() == EBallType::PainBlast )
    {
      _bullet->SetState(BALL_STATE_EXPLODED);

      double X = 0.0, Y = 0.0;
      _bullet->GetCollisionPoint( collider.bestBall, collider.bestTime, X, Y );

      ProcessPaintBlastExplosion( chains, SVector( X, Y ) );
    }
    else
    {
      double shift = _bullet->GetInsertionShift( collider.bestBall, collider.bestTime );
      shift *= EaselConst::Get_BALL_DEF_DIAMETER() * 0.5f;
      AddHittedBallToChain(*collider.bestChain, collider.bestBall->GetCoveredPath() + shift, _bullet, fColorMatched);
    }

    // setting BALL_HIT event
    if ( _bullet->State() == BALL_STATE_ON_BOARD )
    {
      if ( fColorMatched  )
        _bullet->SetState( BALL_STATE_HIT_MATCH );
      else
        _bullet->SetState( BALL_STATE_HIT_MISSMATCH );
    }

    for (BoardChains::iterator it = chains.begin() ; it != chains.end(); ++it )
      (*it)->RemoveSameColorSequences( this );
    return true;
  }

  return false;
}

void LuxGameBoard::GenerateNewChains( int deltaTime, LuxGameLogic* _gameLogic )
{
  if ( !isFrozen )
  {
    BoardChains::iterator chainsIter = chains.begin();
    for(; chainsIter != chains.end(); ++chainsIter)
      (*chainsIter)->GenerateNewChains( deltaTime, _gameLogic );  
  }

  // checking all chains are destroyed (nobody on board)
  if ( !IsChainOnBoard( chains ) )
    chains[0]->ForceNewChainGeneration( _gameLogic );  
}

void LuxGameBoard::SetBoardState( LuxBoardState _newState )
{
  switch ( boardState )
  {
    case BOARDSTATE_NONE:
      {
        if( _newState == BOARDSTATE_LEVEL_BEGIN )
        {
          waitTimer = gameLogic->GetGameData()->commonParams->effects.gameStartEffect->lifeTime * 1000;

          if ( !IsLocalBoard() && IsValid( player ) )
            player->MinigameEvent(NDb::BASEUNITEVENT_MINIGAMELEVELSTARTED);
        }
      }
      break;

    case BOARDSTATE_LEVEL_RUN:
      {
        if ( _newState == BOARDSTATE_LEVEL_FAIL )
        {
          LuxChainsFallingNotification *pnotification = new LuxChainsFallingNotification();

          if ( IsValid( gameLogic->GetNotifier() ) )
            gameLogic->GetNotifier()->Notify(*pnotification);

          // setting falling chains speed
          SetBoardChainsSpeed(chains,EASEL_SPLINE_FALLING_CHAIN_SPEED*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER());

          if ( !IsLocalBoard() && IsValid( player ) )
            player->MinigameEvent(NDb::BASEUNITEVENT_MINIGAMELEVELFAILED);
        } 
        else if ( _newState == BOARDSTATE_LEVEL_WON )
        {
          waitTimer = EASEL_LEVEL_END_DELAY1;

          if ( IsValid( gameLogic->GetNotifier() ) )
            gameLogic->GetNotifier()->Notify(*new EaselLevelWonBeginNotification());

          gameLogic->GetEasel()->GetWorld()->GetLevelStatistics()->OnGameWon();

          if ( !IsLocalBoard() && IsValid( player ) )
            player->MinigameEvent(NDb::BASEUNITEVENT_MINIGAMELEVELWON);
        }
      }
      break;
  }

  NI_VERIFY( 
    !((boardState == BOARDSTATE_LEVEL_FAIL || boardState == BOARDSTATE_LEVEL_FAIL_FINAL) &&
    (_newState == BOARDSTATE_LEVEL_WON)), "Minigame tries to win after fail!", return);
  
  NI_VERIFY( 
    !((boardState == BOARDSTATE_LEVEL_WON || 
    boardState == BOARDSTATE_LEVEL_WON_BLAST_BALLS ||
    boardState == BOARDSTATE_LEVEL_WON_MOVIE||
    boardState == BOARDSTATE_LEVEL_WON_FINAL) &&
    (_newState == BOARDSTATE_LEVEL_FAIL)), "Minigame tries to fail after win!", return);

  boardState = _newState;
}

void LuxGameBoard::RequestStateChange(LuxBoardState _newState)
{
  LuxBoardRequestStateChangeNotification *pnotification = new LuxBoardRequestStateChangeNotification();
  pnotification->currState = boardState;
  pnotification->requestState = _newState;

  if ( IsValid( gameLogic->GetNotifier() ) )
    gameLogic->GetNotifier()->Notify(*pnotification);

  SetBoardState( _newState );
}

void LuxGameBoard::ProcessStep(int deltaTime, LuxGameLogic* _gameLogic )
{
  waitTimer -= deltaTime;

  switch( boardState )
  {
  case BOARDSTATE_LEVEL_BEGIN:
    {
      if ( waitTimer <= 0 )
        RequestStateChange( BOARDSTATE_LEVEL_RUN );
      break;
    }

  case BOARDSTATE_LEVEL_RUN:
    ProcessRunStateStep( deltaTime, _gameLogic );
    break;

  case BOARDSTATE_LEVEL_WON:
    if ( waitTimer <= 0 )
    {
      ChainBlastAllBalls();
      waitTimer = EASEL_LEVEL_END_DELAY2;
      SetBoardState( BOARDSTATE_LEVEL_WON_BLAST_BALLS );

      if ( IsLocalBoard() && IsValid(player) )
        player->PlayAskSound(NDb::ASKSOUNDS_MINIGAMEWIN);
    }

    break;

  case BOARDSTATE_LEVEL_WON_BLAST_BALLS:
    if ( waitTimer <= 0 )
    {
      waitTimer = _gameLogic->GetGameData()->commonParams->effects.gameWonEffect->lifeTime * 1000;
      SetBoardState( BOARDSTATE_LEVEL_WON_MOVIE );
    }

    break;

  case BOARDSTATE_LEVEL_WON_MOVIE:
    if ( waitTimer <= 0 )
    {
      SetBoardState( BOARDSTATE_LEVEL_WON_FINAL );
    }

    break;

  case BOARDSTATE_LEVEL_FAIL:
    ProcessFailStateStep( deltaTime );
    if ( waitTimer <= 0 )
    {
      waitTimer = EASEL_LEVEL_FAIL_END_DELAY;

      if ( IsLocalBoard() && IsValid(player) )
        player->PlayAskSound(NDb::ASKSOUNDS_MINIGAMEFAIL);
    }
    break;
  }

  // move bullets in any state
  MoveBullets( deltaTime );
}

void LuxGameBoard::ProcessRunStateStep( int deltaTime, LuxGameLogic* _gameLogic )
{
  for(BoardChains::iterator chainsIter = chains.begin(); chainsIter != chains.end(); ++chainsIter)
  {
    LuxGameBoardChain * chain = *chainsIter;
    chain->CleanUpChains();
    chain->UpdateChainsSpeed();

    if ( !isFrozen )
      chain->MoveChains(deltaTime);
  }

  UpdatePointer();

  for ( BoardChains::iterator chainsIter = chains.begin(); chainsIter != chains.end(); ++chainsIter )
  {
    LuxGameBoardChain * chain = *chainsIter;
    chain->MergeIntersectingChains();
    chain->RemoveChainsCameToEnd( EASEL_AFTER_EXIT_DISTANCE );
    chain->RemoveSameColorSequences( this );
  }

  for ( Bullets::iterator it = bullets.begin(); it != bullets.end(); )
  {
    if ( CollideAndAddBullet( *it, deltaTime ) )
    {
      it = bullets.erase( it );
    }
    else
    {
      ++it;
    }
  }

  GenerateNewChains( deltaTime, _gameLogic );

  // checking if chains are standing still or moving
  if ( IsAnyChainOnBoardMoving(chains)  )
  {
    LuxChainMovingNotification *pnotification = new LuxChainMovingNotification();

    if ( IsValid( gameLogic->GetNotifier() ) )
      gameLogic->GetNotifier()->Notify( *pnotification );
  }
  else
  {
    LuxChainStoppedNotification *pnotification = new LuxChainStoppedNotification();

    if ( IsValid( gameLogic->GetNotifier() ) )
      gameLogic->GetNotifier()->Notify( *pnotification );
  }

  CheckChainReachEnd();  // checking if any chain has reached the exit point

  RemoveColliders();
}

void LuxGameBoard::RemoveColliders()
{
  LuxGameBoard::Colliders::iterator it = colliders.begin();

  for ( ; it != colliders.end(); )
  {
    if ( (*it)->IsExhausted() )
      it = colliders.erase( it );
    else
      ++it;
  }
}

void LuxGameBoard::ProcessFailStateStep(int deltaTime)
{
  bool hasChains = false;

  for (BoardChains::iterator it = chains.begin(); it != chains.end(); ++it)
  {
    if ( !(*it)->GetChains().empty() )
    {
      LuxGameBoardChain * chain = *it;
      if ( !isFrozen )
        chain->MoveChains(deltaTime);
      chain->RemoveChainsCameToEnd( EASEL_AFTER_EXIT_DISTANCE );

      hasChains = true;
    }
  }

  if ( !hasChains )
  {
    // if all is done, send lost notification
    EaselGameLostNotification *pnotification = new EaselGameLostNotification();

    if ( IsValid( gameLogic->GetNotifier() ) )
      gameLogic->GetNotifier()->Notify(*pnotification);

    gameLogic->GetEasel()->GetWorld()->GetLevelStatistics()->OnGameLost();

    SetBoardState( BOARDSTATE_LEVEL_FAIL_FINAL );
  }
}

void LuxGameBoard::CheckChainReachEnd()
{
  if (GetBoardState() != BOARDSTATE_LEVEL_RUN)
    return;

  BoardChains::iterator chainsIter = chains.begin();
  for(; chainsIter != chains.end(); ++chainsIter)
  {
    if ( (*chainsIter)->CheckChainReachedEnd(EASEL_AFTER_EXIT_DISTANCE*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER())  )
    {
      isFrozen = false;
      RequestStateChange(BOARDSTATE_LEVEL_FAIL); // sending fail state request      
      return;
    }
  }
}

void LuxGameBoard::InitChainsData( const NDb::DBEaselData* _data,
                                  EaselNotifier* pNotifier)
{
  if ( chainPaths.empty()  )
    return;

  chains.clear();

  LuxorPaths::iterator pathsIter = chainPaths.begin();
  for(; pathsIter != chainPaths.end(); ++pathsIter)
  {
    CObj<LuxGameBoardChain> boardChain = new LuxGameBoardChain( GetWorld(), this );
    boardChain->Init( _data, pNotifier, (*pathsIter),chainsGenerator );
    chains.push_back( boardChain );
  }
}

void LuxGameBoard::SortBalls()
{
  BoardChains::const_iterator chainsIter = chains.begin();
  for(; chainsIter != chains.end(); ++chainsIter)
    (*chainsIter)->SortAllChainsElements();

}

void LuxGameBoard::UpdatePointer()
{
  CPtr<LuxPlatform> platform = gameLogic->GetPlatformBoard()->GetPlatform();

  if ( !IsValid( platform ) )
    return;

  if ( !IsValid( platform->GetBulletBall() ) )
    return;

  CollideBalls collider;

  collider.bullet = platform->GetBulletBall();

  for ( BoardChains::iterator it = chains.begin() ; it != chains.end(); ++it )
    (*it)->ForAllChains( collider );

  collider.CollideWithOthers( colliders, platform->GetBulletBall() );

  if ( collider.collisionFound )
  {
    double X, Y;
    
    if ( collider.bestCollider )
      platform->GetBulletBall()->GetCollisionPoint( collider.bestCollider, collider.bestTime, X, Y );
    else
      platform->GetBulletBall()->GetCollisionPoint( collider.bestBall, collider.bestTime, X, Y );

    platform->SetCollisionPoint( SVector( X, Y ) );
    platform->SetHasCollision( true );
  }
}

void LuxGameBoard::ChainBlastAllBalls()
{
  BoardChains::const_iterator chainsIter = chains.begin();

  for(; chainsIter != chains.end(); ++chainsIter)
  {
    (*chainsIter)->DestroyAllChains();
  }
}

void LuxGameBoard::BallFired( LuxBall* _ball )
{
  bullets.push_back( _ball );
}

bool LuxGameBoard::MoveShootingBall( LuxBall* _ball, int deltaTime)
{
  int iCoveredPath = deltaTime * _ball->Speed();
  SVector ballPos = _ball->Position();

  //check this strange 'out of board' condition; It might be reached on _previous_ step
  if ( ballPos.y == EaselConst::Get_BORDER_HEIGHT_OFFSET() )  // missed
  {
    _ball->SetState(BALL_STATE_MISSED);
    return true;
  }

  // integrating y coordinate
  if ( ballPos.y - iCoveredPath > EaselConst::Get_BORDER_HEIGHT_OFFSET() ) // mot missed yet
  {
    ballPos.y = ballPos.y - iCoveredPath;
    _ball->SetPosition( ballPos );

    return false;
  }

  //Out of board
  ballPos.y = EaselConst::Get_BORDER_HEIGHT_OFFSET();
  _ball->SetPosition( ballPos );

  return false;  // ball almost missed
}

void LuxGameBoard::MoveBullets( int deltaTime )
{
  Bullets::iterator it = bullets.begin();

  for ( ; it != bullets.end(); )
  {
    if ( MoveShootingBall( *it, deltaTime ) )
    {
      it = bullets.erase( it );
    }
    else
    {
      ++it;
    }
  }
}


}

REGISTER_SAVELOAD_CLASS_NM( LuxGameBoard, PF_Minigames )
