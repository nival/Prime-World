#include "stdafx.h"

#include "LuxBall.h"
#include "LuxBallChain.h"
#include "LuxMagnet.h"
#include "LuxGameBoard.h"
#include "LuxGameBoardChains.h"
#include "LuxGameLogic.h"
#include "PaintPoint.h"
#include "EaselMath.h"

#include "PaintFlyingNotification.h"


#include "DBEasel.h"

namespace PF_Minigames
{


  class ClosestBallSeeker2
  {
  public:
    ClosestBallSeeker2()          { balls.clear(); balls.reserve(20); };
    virtual ~ClosestBallSeeker2() { balls.clear(); };

    void AddObject( LuxBall* _ball )
    {
      balls.push_back(_ball);
    }

    bool FindClosestBall(const SVector& _zeroPoint,
      int _internalRad,
      int _externalRad,
      NDb::EColor _color,
      /*out*/CPtr<LuxBall>& _closestBall,
      /*out*/int64& _closestDist)
    {
      if ( balls.empty()  )
        return false;

      bool fGotBall = false;   // if at least one mathc found;
      CPtr<LuxBall> _foundBall;
      int64 _foundDist = 0;   

      Balls::iterator ballsIter = balls.begin();
      for(; ballsIter != balls.end(); ++ballsIter)
      {
        CPtr<LuxBall> _ball = (*ballsIter);

        //skip balls that are located in a tunnel
        BallState ballState = _ball->State();

        if (ballState == BALL_STATE_IN_TUNNEL) 
          continue;

        if( _ball->Color() == _color )
        {
          int64 _dist = CalculateDistance(_zeroPoint,_ball->Position()); // определить расстояние до точки ...
          // сравнить расстояние с радиусами
          if(_dist <= _externalRad)
          {
            if(fGotBall == false)
            {
              _foundBall = _ball;
              _foundDist = _dist;
              fGotBall = true;
            }
            else
            {
              if(_dist < _foundDist)
              {
                _foundBall = _ball;
                _foundDist = _dist;
              }
            }
          }
        }      
      }    

      if ( fGotBall  )
      {
        _closestBall = _foundBall;
        _closestDist = _foundDist;
        return true;
      }

      return false;
    }

  private:

    typedef nstl::vector<CPtr<LuxBall>> Balls;
    Balls balls;
  };


  class ClosestChainBallSeeker2
  {
  public:
    ClosestChainBallSeeker2()          { chains.clear(); chains.reserve(20); };
    virtual ~ClosestChainBallSeeker2() { chains.clear(); };

    void AddObject( LuxBallChain* _chain )
    {
      chains.push_back(_chain);
    }

    bool FindClosestBall(const SVector& _zeroPoint,
      int _internalRad,
      int _externalRad,
      NDb::EColor _color,
      /*out*/CPtr<LuxBallChain>& _closestChain,
      /*out*/CPtr<LuxBall>& _closestBall,
      /*out*/int64& _closestDist)
    {
      if ( chains.empty()  )
        return false;

      bool fGotRes = false;
      CPtr<LuxBallChain> _foundChain;
      CPtr<LuxBall>  _foundBall;
      int64             _foundDist = 0;

      Chains::iterator chainsIter = chains.begin();
      for(; chainsIter != chains.end(); ++chainsIter)
      {
        CPtr<LuxBallChain> _chain = *chainsIter;
        CPtr<LuxBall>  _chainBall;
        int64             _chainDist = 0;

        ClosestBallSeeker2 _seeker;   
        _chain->GetBalls(_seeker);

        if ( _seeker.FindClosestBall(_zeroPoint,_internalRad,_externalRad,_color,_chainBall,_chainDist)  )
        {
          if(fGotRes == false)
          {
            _foundChain = _chain;
            _foundBall  = _chainBall;
            _foundDist  = _chainDist;
            fGotRes     = true;
          }
          else
          {
            if(_chainDist < _foundDist)
            {
              _foundChain = _chain;
              _foundBall  = _chainBall;
              _foundDist  = _chainDist;
            }
          }
        }
      }

      if ( fGotRes  )
      {
        _closestChain = _foundChain;
        _closestBall  = _foundBall;
        _closestDist  = _foundDist;

        return true;
      }

      return false;
    }

  private:

    typedef nstl::vector<CPtr<LuxBallChain>> Chains;
    Chains chains;
  };



//////////////////////////////////////////////////////////////////////////
//
// class LuxMagnet implementation
//
//////////////////////////////////////////////////////////////////////////
LuxMagnet::LuxMagnet( PF_Core::IWorld* _pWorld, int _scanTime,int _R1,int _R2, int _numBalls, LuxBoost * _magnetBoost ) :
PF_Core::WorldObjectBase( _pWorld, false ),
scanTime( _scanTime ),
radiusR1( _R1 ), radiusR2( _R2 ),
numBallsToEat( _numBalls ),
ballsEaten( 0 ),
killed( false ),
complete( false ),
magnetBoost( _magnetBoost ),
magnetTimer(0)
{
}

LuxMagnet::~LuxMagnet()
{

}

void LuxMagnet::Step( int deltaTime,  LuxGameLogic* _gameLogic )
{
  if ( !colorPoint->HasRoom() )
  {
    Complete();
    return;
  }

  if ( magnetTimer < scanTime * 1000 )
  {
    ProcessMagnetOperation( _gameLogic );

    if ( IsExhausted() || !colorPoint->HasRoom() )
    {
      Complete();
      return;
    }

    magnetTimer = scanTime * 1000;
    return;
  }

  magnetTimer -= deltaTime;
}

void LuxMagnet::ProcessMagnetOperation( LuxGameLogic* _gameLogic )
{
  int radInternal = GetRadiusInternal();
  int radExternal = GetRadiusExternal();

  bool fRes = false;
  CPtr<LuxGameBoardChain> _nearestBoardChain;
  CPtr<LuxBallChain> _nearestBallChain;
  CPtr<LuxBall> _nearestBall;
  int64 _nearestDest = 0;

  BoardChains::iterator it = _gameLogic->GetGameBoard()->GetChains().begin();
  BoardChains::iterator last = _gameLogic->GetGameBoard()->GetChains().end();

  for (;it != last; ++it )
  {
    CPtr<LuxGameBoardChain> _boardChain = *it;

    ClosestChainBallSeeker2 seeker;
    _boardChain->GetChainsWeak(seeker);

    CPtr<LuxBallChain> _chain;
    CPtr<LuxBall> _ball;
    int64 _dest = 0;

    if(seeker.FindClosestBall( Position(),
      radInternal,radExternal,
      GetColor(),
      _chain,_ball,_dest) == true)
    {
      if(fRes == false)
      {
        _nearestBoardChain = _boardChain;
        _nearestBallChain = _chain;
        _nearestBall = _ball;
        _nearestDest = _dest;
        fRes = true;
      }
      else
      {
        if(_dest < _nearestDest)
        {
          _nearestBoardChain = _boardChain;
          _nearestBallChain = _chain;
          _nearestBall = _ball;
          _nearestDest = _dest;
        }
      }
    }
  }

  if ( fRes  )  // we have found the chain ball
  {
    if(_nearestDest <= radInternal)  // it's inside the R1
    {
      colorPoint->IncCurrentCapacity(1);   // incrementing color point color counter

      PaintFlyingNotification *pnotification = new PaintFlyingNotification();  
      pnotification->from       = _nearestBall->Position();
      pnotification->spTo       =  colorPoint;

      if ( IsValid( _gameLogic->GetNotifier() ) )
        _gameLogic->GetNotifier()->Notify(*pnotification);

      // take the ball ont of the chain, notify on chain break
      CPtr<LuxBallChain> _tail;
      if ( _nearestBallChain->ExplodeBallAtPos(_nearestBall->GetCoveredPath(),_tail)  )
      {
        if(IsValid(_tail))
          _nearestBoardChain->AddChain(_tail);
        else
          _nearestBoardChain->ValidateChains();          
      }
    }
  }

}


void LuxMagnet::Complete()
{
  colorPoint->SetMode( EPainterPointMode::None );
  complete = true;
}


bool LuxMagnet::IsExhausted() const
{
  if ( killed || complete )
    return true;

  if(numBallsToEat - ballsEaten > 0)
    return false;
  
  return true;
}

NDb::EColor LuxMagnet::GetColor() const
{
  if ( IsValid( colorPoint ) )
    return colorPoint->GetColor();

  return NDb::COLOR_WHITE;
}

const SVector& LuxMagnet::Position() const 
{ 
  if ( IsValid( colorPoint ) )
    return colorPoint->GetCoord();

  static SVector stub( 0, 0 );

  return stub; 
}


bool LuxMagnet::Hit() 
{ 
  colorPoint->SetMode( EPainterPointMode::None );
  killed = true; 
  return true; 
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxMagnet, PF_Minigames )