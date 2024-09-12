#include "stdafx.h"
#include "LuxBallChain.h"

#include "../System/lerp.h"

#include "LuxDef.h"

#include "DBEasel.h"
#include "EaselNotifications.h"
#include "EaselTrajectory.h"
#include "Easel.h"
#include "EaselWorld.h"

#include "LuxPath.h"
#include "LuxBall.h"

#include "LuxChainElementExplodedNotification.h"
#include "LuxBallExplodedNotification.h"
#include "LuxChainBallAddedNotification.h"
#include "LuxChainSlideLowNotification.h"
#include "LuxBallHitNotification.h"
#include "LuxBallCreateNotification.h"
#include "LuxGameLogic.h"
#include "LuxFallingBoard.h"
#include "PaintLogic.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// ball in tunnel checker predicate
//
//////////////////////////////////////////////////////////////////////////
class TunnelCheckPred : public unary_function<NDb::DBTunnel,bool>
{
public:
  TunnelCheckPred(int64 _pos) : position(_pos/EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER()) {};
  ~TunnelCheckPred() {};

  bool operator()(const NDb::DBTunnel &rhs) const
  {
    if(position >= rhs.begin && position <= rhs.end)
      return true;
    else
      return false;
  }

private:
  TunnelCheckPred();
  
  int64 position;

protected:

};


//////////////////////////////////////////////////////////////////////////
//
// class LuxBallChain implementation
//
//////////////////////////////////////////////////////////////////////////
LuxBallChain::LuxBallChain(LuxPath* _path,
                           EaselNotifier *pNotifier, Easel* _easel )
: PF_Core::WorldObjectBase( _path->GetWorld(), false )
, chainPath(_path)
, chainSpeed(0)
, pviewNotifier(pNotifier)
, chainDefaultSpeed(0)
, state( STATE_ROLL_IN )
, firstEdgePoint(0)
, firstEdgePointVelocity(0)
, easel(_easel)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain::~LuxBallChain()
{

}

int64 LuxBallChain::GetChainPosition() const 
{ 
  if ( chainBalls.empty() )
    return 0;

  CPtr<LuxBall> frontBall = chainBalls.front().ball; 

  return frontBall->GetCoveredPath() + (frontBall->Size()/2);
}

int64 LuxBallChain::GetChainLength() const
{ 
  if ( chainBalls.empty() )
    return 0;

  CPtr<LuxBall> lastBall = chainBalls.back().ball;

  return GetChainPosition() - (lastBall->GetCoveredPath() - lastBall->Size()/2);
}


int64 LuxBallChain::GetChainEnd() const 
{ 
  return GetChainPosition() - GetChainLength(); 
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::TearOffTail(const ChainBalls::iterator& tailStart)
{
  LuxBallChain* pChain = new LuxBallChain( chainPath, pviewNotifier, easel );
  
  // setting base parameters
  pChain->state = state;
  pChain->chainSpeed      = chainSpeed;
  pChain->chainDefaultSpeed = chainDefaultSpeed;
  pChain->firstEdgePoint = firstEdgePoint;
  pChain->firstEdgePointVelocity = firstEdgePointVelocity;

  // cloning balls

  pChain->chainBalls.assign( tailStart, chainBalls.end() );  
  chainBalls.erase(tailStart, chainBalls.end() );

  chainBalls.front().edgeVelocity = 0;

  return pChain;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain::ChainBalls::iterator LuxBallChain::StealBallsToTail( LuxBallChain* chain )
{
  if(chain->chainBalls.empty())
  {
    return chainBalls.end();
  }

  ChainBalls::iterator itCurrent = chain->chainBalls.begin();
  const ChainBalls::iterator itEnd = chain->chainBalls.end();

  ChainBalls::iterator result = chainBalls.insert(chainBalls.end(), *itCurrent);
  ++itCurrent;

  chainBalls.insert(chainBalls.end(), itCurrent, itEnd);
  chain->chainBalls.clear();

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::ProcessTunnelsIntersection()
{
  static float nextTunnelOffset = EaselConst::Get_BALL_DEF_DIAMETER() * 2;

  const nstl::vector<NDb::DBTunnel>& _tunnels = chainPath->GetTunnels();

  ChainBalls::iterator it = chainBalls.begin();
  ChainBalls::iterator last = chainBalls.end();

  for ( ; it != last; ++it )
  {
    int64 ballPos = it->ball->GetCoveredPath();

    TunnelCheckPred pred(ballPos);
    TunnelCheckPred predNext(ballPos + nextTunnelOffset);

    nstl::vector<NDb::DBTunnel>::const_iterator tunnelIter = find_if(_tunnels.begin(),_tunnels.end(),pred);
    nstl::vector<NDb::DBTunnel>::const_iterator tunnelNextIter = find_if(_tunnels.begin(),_tunnels.end(),predNext);
    

    if(tunnelNextIter != _tunnels.end())
    {
      it->ball->SetNextTunelPoint( tunnelNextIter->begin * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER());
    }

    if(tunnelIter == _tunnels.end()) // we are outside any tunnel
    {
      BallState ballState = it->ball->State();
      if( ballState == BALL_STATE_IN_TUNNEL )
      {
        it->ball->SetLastTunelPoint( it->tunnelEnd );
        switch(state)
        {
        case STATE_ON_BOARD:
          it->ball->SetState(BALL_STATE_ON_BOARD);
          break;
        case STATE_ROLL_IN:
          it->ball->SetState(BALL_STATE_ROLL_IN);
          break;
        case STATE_ROLL_OUT:
          it->ball->SetState(BALL_STATE_ROLL_OUT);
          break;
        }          
      }      
    }
    else if(GetSpeed() >= 0) // we are inside the tunnel
    {

      it->ball->SetLastTunelPoint( tunnelIter->begin * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER());
      it->tunnelEnd = tunnelIter->end * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
      it->ball->SetState( BALL_STATE_IN_TUNNEL );
    }
  }
}

///////////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::ExplodeChainBalls()
{
  ChainBalls::iterator ballsIter = chainBalls.begin();
  for(; ballsIter != chainBalls.end(); ++ballsIter)
  {
    ballsIter->ball->SetState(BALL_STATE_EXPLODED);
    SendChainElementExplodedNotification( ballsIter->ball, 1 );
  }

  chainBalls.clear();
}

bool LuxBallChain::ExplodeBallAtPos(int64 _pos,/*out*/CPtr<LuxBallChain>& tearedOfftail)
{
  ChainBalls::iterator ballsIter = chainBalls.begin();
  for(; ballsIter != chainBalls.end(); ++ballsIter)
  {
    if(ballsIter->ball->GetCoveredPath() == _pos)
    {
      tearedOfftail = ExplodeBall(ballsIter);
      return true;
    }
  }
  
  return false;
}


void LuxBallChain::SortChain()
{
  // setting stable sort predicate ...
  struct SortPred : public nstl::binary_function<BallRecord,BallRecord,bool>
  {
    bool operator()(const BallRecord &lhs, const BallRecord &rhs) const
    {
      NDb::EColor firstColor = lhs.ball->Color();
      NDb::EColor secondColor = rhs.ball->Color();
      return (firstColor < secondColor);
    }
  };

  // sort 
  chainBalls.sort( SortPred() );

  RecalculateBallsSize();
  RecalculateBallsPositionsOnMove();
  ProcessTunnelsIntersection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::AddChainBallInit( LuxBall* spBall )
{
  int newBallRadius = spBall->Size() / 2;
  int64 newBallPos = -GetChainLength() - newBallRadius;

  spBall->SetCoveredPath( newBallPos);

  // add new ball record
  BallRecord& newBallRecord = chainBalls.push_back();
  newBallRecord.ball = spBall;
  newBallRecord.edgePoint = newBallPos + newBallRadius;
  firstEdgePoint = newBallPos - newBallRadius;

  NotifyNewBallAdded( spBall );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::InitAddBallEnd(LuxBall* spBall)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::AddChainBallRunTime( LuxBall* spBall, bool& fColorMatched )
{
  RunTimeAddBallMiddle( spBall, fColorMatched );
  NotifyNewBallAdded( spBall );
}

void LuxBallChain::NotifyNewBallAdded(LuxBall* _ball)
{
  LuxChainBallAddedNotification *pnotification = new LuxChainBallAddedNotification();

  pnotification->path = chainPath;
  pnotification->ball = _ball;

  if ( IsValid( pviewNotifier ) )
    pviewNotifier->Notify(*pnotification);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RunTimeAddBallFront(LuxBall* spBall, bool& fColorMatched)
{
  int newBallRadius = spBall->Size() / 2;
  int64 newBallPosition = spBall->GetCoveredPath();

  spBall->SetCoveredPath(newBallPosition);
  spBall->SetSpeed(0);

  if(!chainBalls.empty())
  {
    NDb::EColor _ballColor = spBall->Color();
    NDb::EColor _frontColor = chainBalls.front().ball->Color();

    fColorMatched = (_ballColor == NDb::COLOR_ANY) || (_frontColor == NDb::COLOR_ANY);
    fColorMatched = fColorMatched || (_ballColor == _frontColor);
  }

  BallRecord& newBallRecord = chainBalls.push_front();
  newBallRecord.ball = spBall;
  newBallRecord.insertedBall = CheckOnExplosion( chainBalls.begin() );
  newBallRecord.explosionCountdown = easel->GetData()->commonParams->explosionCountdown;
  newBallRecord.edgePoint = newBallPosition - newBallRadius;

  RecalculateBallsSize();
  RecalculateBallsPositionsOnMove();
  ProcessTunnelsIntersection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RunTimeAddBallEnd(LuxBall* spBall, bool& fColorMatched)
{
  int newBallRadius = spBall->Size()/2;
  int64 newBallPos = spBall->GetCoveredPath();

  spBall->SetSpeed(0);

  if(!chainBalls.empty())
  {
    NDb::EColor _ballColor = spBall->Color();
    NDb::EColor _backColor = chainBalls.back().ball->Color();

    fColorMatched = (_ballColor == NDb::COLOR_ANY) || (_backColor == NDb::COLOR_ANY);
    fColorMatched = fColorMatched || (_ballColor == _backColor);
  }

  // create new ball record
  ChainBalls::iterator newIterator = chainBalls.insert( chainBalls.end() );
  BallRecord& newBallRecord = *newIterator;
  newBallRecord.ball = spBall;
  newBallRecord.insertedBall = CheckOnExplosion( newIterator );
  newBallRecord.explosionCountdown = easel->GetData()->commonParams->explosionCountdown;
  newBallRecord.edgePoint = newBallPos + newBallRadius;
  firstEdgePoint = newBallPos - newBallRadius;

  RecalculateBallsSize();
  RecalculateBallsPositionsOnMove();
  ProcessTunnelsIntersection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RunTimeAddBallMiddle(LuxBall* spBall, bool& fColorMatched)
{
    static int64 nextTunnelOffset = EaselConst::Get_BALL_DEF_DIAMETER();

    int64 newBallPos = spBall->GetCoveredPath();

    fColorMatched = true;

    bool lastBallInTunnel = true;

    // find the intersected ball iterator
    ChainBalls::iterator ballsIter = chainBalls.begin();
    for(; ballsIter != chainBalls.end(); ballsIter++)
    {
        int64 currballPos = ballsIter->ball->GetCoveredPath();
        BallState state = ballsIter->ball->State();
        
        bool inTunnel = (state == BALL_STATE_IN_TUNNEL);
        float distanceToNextTunnel = ( ballsIter->ball->GetNextTunnelPoint() - currballPos );
        bool justInFrontOfTunnel = ( distanceToNextTunnel < nextTunnelOffset ) && ( distanceToNextTunnel > 0 );
        if( ( newBallPos > currballPos ) && ( !inTunnel || !lastBallInTunnel ) && !justInFrontOfTunnel )
            break;
        lastBallInTunnel = inTunnel;
    }

    if(ballsIter == chainBalls.begin())
    {
      // ball insertion is not at middle, but at the beginning of the chain
      RunTimeAddBallFront(spBall, fColorMatched);
      return;
    }

    if(ballsIter == chainBalls.end())
    {
      // ball insertion is not at middle, but at end
      RunTimeAddBallEnd(spBall,fColorMatched);
      return;
    }

    // caclulate ball color match

    ChainBalls::iterator prevBallsIter = ballsIter;
    --prevBallsIter;

    NDb::EColor _ballColor = spBall->Color();
    NDb::EColor _prevColor = prevBallsIter->ball->Color();
    NDb::EColor _nextColor = ballsIter->ball->Color();

    fColorMatched = (_prevColor == NDb::COLOR_ANY) || (_ballColor == NDb::COLOR_ANY) || (_nextColor == NDb::COLOR_ANY);
    fColorMatched = fColorMatched || (_ballColor == _prevColor) || (_ballColor == _nextColor);

    //
    int currBallSize = spBall->Size();
    spBall->SetSpeed(0);

    // create new ball record
    ChainBalls::iterator newIterator = chainBalls.insert( ballsIter );
    BallRecord& newBallRecord = *newIterator;
    newBallRecord.ball = spBall;
    newBallRecord.insertedBall = CheckOnExplosion( newIterator );
    newBallRecord.explosionCountdown = easel->GetData()->commonParams->explosionCountdown;
    newBallRecord.edgePoint = newBallPos - (currBallSize/2); 

    RecalculateBallsSize();
    RecalculateBallsPositionsOnMove();
    ProcessTunnelsIntersection();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::IsIntersects(const LuxBallChain& otherChain)
{
  int64 positionHead1 = GetChainPosition();
  int64 positionTail1 = GetChainEnd();

  int64 positionHead2 = otherChain.GetChainPosition();
  int64 positionTail2 = otherChain.GetChainEnd();

  return ( (positionHead1 > positionTail2) && (positionHead2 > positionTail1) );

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::CheckOnExplosion( const ChainBalls::iterator& _it )
{
  int counter = 1;
  NDb::EColor ballColor = _it->ball->Color();  
  bool jocker = ( ballColor == NDb::COLOR_ANY );

  {
    bool leftJocker = jocker;

    ChainBalls::iterator itLeft = _it;

    if ( itLeft != chainBalls.begin() )
    {
      bool firstBall = true;

      do 
      {
        --itLeft;

        if ( leftJocker && firstBall )
        {
          ballColor = itLeft->ball->Color();
          firstBall = false;
        }

        if ( NDb::COLOR_ANY == itLeft->ball->Color() )
          leftJocker = true;

        if ( ballColor == itLeft->ball->Color() || NDb::COLOR_ANY == itLeft->ball->Color() )
          counter++;
        else
          break;

      } while ( itLeft != chainBalls.begin() );
    }
  }

  {
    bool rightJocker = jocker;

    ChainBalls::iterator itRight = _it;

    bool firstBall = true;
    itRight++;

    while ( itRight != chainBalls.end() )
    {
      if ( rightJocker && firstBall )
      {
        ballColor = itRight->ball->Color();
        firstBall = false;
      }

      if ( NDb::COLOR_ANY == itRight->ball->Color() )
        rightJocker = true;

      if ( ballColor == itRight->ball->Color() || NDb::COLOR_ANY == itRight->ball->Color() )
        counter++;
      else
        break;

      ++itRight;
    }
  }

  return ( counter >= EaselConst::Get_MIN_BALLS_TO_BLOW() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::MergeTail( LuxBallChain* other )
{
  // workaround merging in tunnels
  if( (other->GetSpeed() <= 0) && (GetSpeed() >= 0) )
  {
    return false;
  }

  firstEdgePoint = other->firstEdgePoint;
  firstEdgePointVelocity = other->firstEdgePointVelocity;
  
  SetSpeed( other->GetSpeed() );
  state = other->state;
  
  bool checkExplosion = ( chainBalls.back().ball->Color() == other->chainBalls.front().ball->Color() );

  ChainBalls::iterator lastBall = chainBalls.end();
  --lastBall;

  // copy balls to our tail
  ChainBalls::iterator tail = StealBallsToTail(other);

  if ( checkExplosion )
  {
    lastBall->insertedBall = CheckOnExplosion( lastBall );
    lastBall->explosionCountdown = easel->GetData()->commonParams->explosionCountdown;
  }

  RecalculateBallsSize();

  // need to recalculate balls position
  RecalculateBallsPositionsOnMove();
  ProcessTunnelsIntersection();

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::ExplodePaintBlastWave(const SVector &_refBlastPos,int64 _radius)
{
  if ( chainBalls.empty() )
    return 0;

  ChainBalls::iterator currentBall = chainBalls.begin();
  const ChainBalls::iterator endBall = chainBalls.end();

  BallState ballState = currentBall->ball->State();
  bool ballInTunnel = (ballState == BALL_STATE_IN_TUNNEL);

  bool fGotExplosion = !ballInTunnel && IsInsidePaintBlast(currentBall->ball->Position(),_refBlastPos,_radius);
  ChainBalls::iterator explosionStart = currentBall;  
  
  for(; currentBall != endBall; ++currentBall)
  {
    ballState = currentBall->ball->State();
    ballInTunnel = (ballState == BALL_STATE_IN_TUNNEL);

    bool isExploded = !ballInTunnel && IsInsidePaintBlast(currentBall->ball->Position(),_refBlastPos,_radius);
    if(isExploded == false)
    {
      if ( fGotExplosion  ) 
      {
        // у нас определилася область взрыва, рвем все
        return PaintBlastExplodeBalls(explosionStart,currentBall);
      }
    }
    else
    {
      if(fGotExplosion == false)
      {
        fGotExplosion = true;
        explosionStart = currentBall;
      }      
    }
  }

  if ( fGotExplosion  )
  {
    return PaintBlastExplodeBalls(explosionStart,currentBall);
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::IsInsidePaintBlast(const SVector &_refballPos,const SVector &_refblastPos,int64 blastRadius)
{
  double deltaX = abs(_refballPos.x-_refblastPos.x);
  double deltaY = abs(_refballPos.y-_refblastPos.y);

  int64 length = sqrt(deltaX*deltaX+deltaY*deltaY);

  if(length <= blastRadius)
    return true;
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::ExplodeFirstSameColorSegment()
{
  if ( chainBalls.empty() )
    return 0;

  ChainBalls::iterator currentBall = chainBalls.begin();
  const ChainBalls::iterator endBall = chainBalls.end();

  ChainBalls::iterator collapseFrom = currentBall;

  int numSameColorBalls = 1;

  bool collisionOccured = collapseFrom->CanExplode();
  NDb::EColor collapseColor = collapseFrom->ball->Color();

  ++currentBall;

  // traverse chain balls
  for(; currentBall != endBall; ++currentBall)
  {
    BallState ballState = currentBall->ball->State();
    bool ballInTunnel = ( ballState == BALL_STATE_IN_TUNNEL );

    //rolling out balls behave the same as balls in tunnels
    if ( ballState == BALL_STATE_ROLL_IN)
      ballInTunnel = true;

    // data for combo chain explosions and terminator
    if(collapseColor == NDb::COLOR_ANY && !ballInTunnel)
    {
      collapseColor = currentBall->ball->Color();
      ++numSameColorBalls;
      collisionOccured = collisionOccured || currentBall->CanExplode();
    }
    else
    {
      NDb::EColor currBallColor = currentBall->ball->Color();
      
      // count balls with the same color and without gap between them
      if( currBallColor == collapseColor && !ballInTunnel)
      {
        // another ball of the same color
        ++numSameColorBalls;
        collisionOccured = collisionOccured || currentBall->CanExplode();
      }
      else if(currBallColor == NDb::COLOR_ANY && !ballInTunnel)
      {
        collapseColor = NDb::COLOR_ANY;
        ++numSameColorBalls;
        collisionOccured = collisionOccured || currentBall->CanExplode();
      }
      else
      {
        // explode all ball chains with 3+ and collision on the current update
        if( (numSameColorBalls >= EaselConst::Get_MIN_BALLS_TO_BLOW()) && collisionOccured)
        {
          if ( CheckCanExplodeBalls(collapseFrom,currentBall,numSameColorBalls)  )
          {
            return ExplodeBalls(collapseFrom, currentBall, numSameColorBalls);
          }
        }

        // prepare inner variables for next color group
        numSameColorBalls = 1;
        collapseFrom = currentBall; 
        collisionOccured = collapseFrom->CanExplode();
        collapseColor = collapseFrom->ball->Color();
      }
    }    
  }

  // explode last balll chain of 3+ with collision ball(s) inside
  if( (numSameColorBalls >= EaselConst::Get_MIN_BALLS_TO_BLOW()) && collisionOccured)
  {
    if ( CheckCanExplodeBalls( collapseFrom, currentBall, numSameColorBalls ) )
    {
      return ExplodeBalls( collapseFrom, currentBall, numSameColorBalls );
    }
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::CheckCanExplodeBalls( const ChainBalls::iterator & explodeFrom, const ChainBalls::iterator & explodeTo, int numBalls ) const
{
  for(ChainBalls::iterator cbIter = explodeFrom; cbIter != explodeTo; cbIter++)
  {
    if(cbIter->ball->Color() != NDb::COLOR_ANY)
      return true;
  }
  
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::PaintBlastExplodeBalls(const ChainBalls::iterator& _explodeFrom, const ChainBalls::iterator& _explodeTo)
{
  ChainBalls::iterator explodeTo = _explodeTo;

  // need to notify ball explosion and deletion
  for(ChainBalls::iterator cbIter = _explodeFrom; cbIter != explodeTo; cbIter++)
  {
    cbIter->ball->SetState(BALL_STATE_EXPLODED);
    SendChainElementExplodedNotification(cbIter->ball, 1);  
  }

  LuxBallChain* tail = ProcessTailTearOff(_explodeFrom,_explodeTo);

  return tail;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::ExplodeBalls(const ChainBalls::iterator& explodeFrom, const ChainBalls::iterator& _explodeTo, int numBalls)
{
  ChainBalls::iterator explodeTo = _explodeTo;

  // need to notify ball explosion and deletion
  int midPos = 0;
  for( ChainBalls::iterator cbIter = explodeFrom; cbIter != explodeTo; ++cbIter, ++midPos )
  {
    cbIter->ball->SetState( BALL_STATE_EXPLODED );
  }

  // sending explosion paint/statistics notification 
  midPos = midPos / 2;
  ChainBalls::iterator chainExpl = explodeFrom;
  while( midPos )
  {
    ++chainExpl;
    --midPos;
  }

  SendChainElementExplodedNotification(/*explodeFrom->ball*/chainExpl->ball, numBalls);  
  SVector explosionCoords = chainExpl->ball->Position();

  return ProcessTailTearOff(explodeFrom, explodeTo);
}

LuxBallChain* LuxBallChain::ExplodeBall(const ChainBalls::iterator& _ball)
{
  ChainBalls::iterator _explodeBall = _ball;
  _explodeBall->ball->SetState(BALL_STATE_EXPLODED);

  ChainBalls::iterator _from = _explodeBall;
  ChainBalls::iterator _to   = _explodeBall;
  ++_to;

  return ProcessTailTearOff(_from,_to);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::ProcessTailTearOff(const ChainBalls::iterator& _From, const ChainBalls::iterator& _To)
{
  ChainBalls::iterator explodeTo = _To;

  LuxBallChain* tail = 0;

  static int backSpeed = 50000;

  // tear off tail if we have one 
  // we should change speed teared off head depend on adjacent colors
  if( (_From != chainBalls.begin()) && (explodeTo != chainBalls.end()) )
  {
    // calculate speed for teared off chain head
    // chain will stop if adjacent to it balls have same colors. Otherwise it will reverse its movement
    ChainBalls::iterator prevBall = _From;
    --prevBall;
    int newChainSpeed = 0;

    bool sameColorOnTheEnds = (prevBall->ball->Color() == explodeTo->ball->Color());

    if(GetSpeed() > 0)
    {
      if(sameColorOnTheEnds)
      {
         newChainSpeed = -backSpeed;
         SendChainSlideLowNotification();
      }
    }
    else
    {
      newChainSpeed = chainSpeed;
    }

    tail = TearOffTail(explodeTo);

    if(state == STATE_ROLL_IN)
    {
      state = STATE_ON_BOARD;
    }

    explodeTo = chainBalls.end();

    tail->SetSpeed( chainSpeed );

    SetSpeed( newChainSpeed );
  }

  if((_From != chainBalls.begin()) && (_From != chainBalls.end()))
  {
    firstEdgePoint = _From->edgePoint;
    firstEdgePointVelocity = _From->edgeVelocity;
  }

  chainBalls.erase(_From, explodeTo);

  return tail;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuxBallChain::SetChainPosition(int64 newPosition)
{
    SetBallsPositions( newPosition );   // chain position has changed, recalculation

    RecalculateBallsPositionsOnMove();
    ProcessTunnelsIntersection();

    firstEdgePoint = GetChainEnd();

    return LUX_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::UpdateChainSpeed(bool lastChain)
{
  if( (state == STATE_ROLL_IN) && ( GetChainPosition() - GetChainLength() < 0 ) && (GetChainLength() != 0) )
  {
    int mult = 3;

    int64 newSpeed = (chainDefaultSpeed * mult * GetChainPosition()) / GetChainLength();
    newSpeed = max(0, newSpeed);
    newSpeed = chainDefaultSpeed * (mult + 1) - newSpeed;
    SetSpeed(newSpeed);
  }
  else if ( GetChainPosition() > chainPath->GetTrajectory()->GetLenght() )
  {
    state = STATE_ROLL_OUT;

    int mult = 6;
    int64 accelerationDistance = 1000 * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

    int64 newSpeed =  (chainDefaultSpeed * mult * (GetChainPosition() - chainPath->GetTrajectory()->GetLenght() ) ) / accelerationDistance;
    newSpeed = min(newSpeed, chainDefaultSpeed * mult);
    newSpeed = max(0, newSpeed);
    newSpeed = chainDefaultSpeed + newSpeed;
    SetSpeed(newSpeed);
  }
  else if( state == STATE_ROLL_IN )
  {
    state = STATE_ON_BOARD;

    SetSpeed(chainDefaultSpeed);
  } if( lastChain )
  {
    if(chainSpeed <= 0)
    {
      SetSpeed(chainDefaultSpeed);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float LuxBallChain::CalculateEdgeAcceleration(int64 start, int64 current, int64 end, int deltaTime)
{
  static float kc = 6.0e-6f;
  static float fr_max = 0.0f;

  float fc_start = kc * (EaselConst::Get_BALL_DEF_DIAMETER() - (current - start) );
  float fc_end = kc * (EaselConst::Get_BALL_DEF_DIAMETER() - (end - current));

  float f = fc_start - fc_end;

  // add resistance force
  float fr = min(f, fr_max);
  fr = max(fr, -fr_max);

  f = f - fr;

  // calculate velocities
  float acceleration = f * deltaTime;

  return acceleration;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxBallChain::StepVelocity(int desiredBallVelocity, int deltaTime, float& currentBallVelocity)
{
  static int speedChangeMult = 50;

  if( (desiredBallVelocity - currentBallVelocity) > 0)
  {
    currentBallVelocity = currentBallVelocity + deltaTime*speedChangeMult;
    currentBallVelocity = min(currentBallVelocity, desiredBallVelocity);
    
    return true;
  }
  else if(desiredBallVelocity != currentBallVelocity)
  {
    currentBallVelocity = currentBallVelocity - deltaTime*speedChangeMult;
    currentBallVelocity = max(currentBallVelocity, desiredBallVelocity);
    return true;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::MoveChainBallsByVelocity(int deltaTime)
{
  
  static float backwardMult = 10;
  static float speedInc = 10;

  if(chainBalls.empty())
  {
    return;
  }

  
  float chainVelocity = (float)chainSpeed;
  if(chainVelocity >= 0)
  {
    float diff = chainBalls.back().ball->GetCoveredPath() - chainBalls.back().ball->GetLastTunnelPoint();
    float minVelocity = (diff > 0 && diff < EaselConst::Get_BALL_DEF_DIAMETER() * 2) ? chainDefaultSpeed : 0.0f;
    chainVelocity = max(chainVelocity, minVelocity);
  }

  if(chainSpeed < 0)
  {
    StepVelocity(chainVelocity*backwardMult, deltaTime, firstEdgePointVelocity);
  }
  else
  {
    StepVelocity(chainVelocity, deltaTime, firstEdgePointVelocity);
  }
 
  firstEdgePoint += firstEdgePointVelocity * deltaTime;

  ChainBalls::iterator beginBallIter = chainBalls.begin();
  ChainBalls::iterator endBallIter = chainBalls.end();

  for(ChainBalls::iterator currentBallIter = beginBallIter; currentBallIter != endBallIter; ++currentBallIter)
  {
    int desiredBallVelocity = chainVelocity;

    if((currentBallIter == beginBallIter) && (GetState() == STATE_ROLL_OUT))
    {
      desiredBallVelocity *= speedInc;
    }

    if(StepVelocity(desiredBallVelocity, deltaTime, currentBallIter->currentVelocity))
    {
      currentBallIter->ball->SetSpeed(currentBallIter->currentVelocity);
    }

    currentBallIter->edgePoint += currentBallIter->currentVelocity*deltaTime;
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::CalculateOffset(int64 start, int64 end, int deltaTime,float& offset, int64& currentPoint, float& currentVelocity)
{        

  static float dumping = 0.0001f;

  float acceleration = CalculateEdgeAcceleration(start, currentPoint, end, deltaTime) - dumping * currentVelocity * deltaTime;
  currentVelocity += acceleration * deltaTime;
  offset = currentVelocity * deltaTime;
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RecalculatePoint(float previous, float offset, int64& currentPoint, float& currentVelocity)
{
  static float maxSize = 2.5f;
  static float minSize = 1.5f;

  int64 newPoint = currentPoint + offset;

  if(newPoint > previous + EaselConst::Get_BALL_DEF_RADIUS() * maxSize)
  {
    newPoint = previous + EaselConst::Get_BALL_DEF_RADIUS() * maxSize;
    currentVelocity = 0;
  }

  if(newPoint < previous + EaselConst::Get_BALL_DEF_RADIUS() * minSize)
  {
    newPoint = previous + EaselConst::Get_BALL_DEF_RADIUS() * minSize;
    currentVelocity = 0;
  }

  currentPoint = newPoint;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RecalculateBallsSize()
{
  int64 lastEdgePoint = firstEdgePoint;

  ChainBalls::iterator beginBallIter = chainBalls.begin();
  ChainBalls::iterator currentBalIter = chainBalls.end();
  do
  {
    --currentBalIter;


    CPtr<LuxBall> ball = currentBalIter->ball;

    RecalculatePoint(lastEdgePoint, currentBalIter->offset, currentBalIter->edgePoint, currentBalIter->edgeVelocity);

    int size = currentBalIter->edgePoint - lastEdgePoint;
    ball->SetSize( size );
    ball->SetCoveredPath( lastEdgePoint + (size/2) );

    lastEdgePoint = currentBalIter->edgePoint;
  }  while(currentBalIter != beginBallIter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::MoveBallsAndChangeSizes( int deltaTime )
{
  
  if(chainBalls.empty())
  {
    return;
  }

  ChainBalls::iterator beginBallIter = chainBalls.begin();
  ChainBalls::iterator endBallIter = chainBalls.end();

  int64 lastEdgePoint = firstEdgePoint;

  // move balls' edge points
  ChainBalls::iterator currentBalIter = endBallIter;
  --currentBalIter;
  while(currentBalIter != beginBallIter)
  {
    
    int64& currentPoint = currentBalIter->edgePoint;
    float& currentVelocity = currentBalIter->edgeVelocity;
    float& offset = currentBalIter->offset;

    --currentBalIter;

    int64 nextEdgePoint =  currentBalIter->edgePoint; 

    int64 lastEdgePoint2 = lastEdgePoint;
    lastEdgePoint = currentPoint;

    CalculateOffset(lastEdgePoint2, nextEdgePoint, deltaTime, offset, currentPoint, currentVelocity);
  
    
  } 

  {
    int64& currentPoint = currentBalIter->edgePoint;
    float& currentVelocity = currentBalIter->edgeVelocity;
    float& offset = currentBalIter->offset;

    CalculateOffset(lastEdgePoint, currentPoint + EaselConst::Get_BALL_DEF_DIAMETER(), deltaTime, offset, currentPoint, currentVelocity);
  }

  RecalculateBallsSize();
}

static int divider = 1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuxBallChain::MoveChain(int deltaTime)
{
  deltaTime /= divider;

  static float period = 1000.0f;
  static float timePassed = 0;

  timePassed += float(deltaTime) / period;

  if ( chainBalls.empty() )
    return LUX_OK;

  MoveChainBallsByVelocity(deltaTime);

  static int timeStep = 20;

  int i = timeStep;
  for(; i < deltaTime; i+=timeStep)
  {
    MoveBallsAndChangeSizes(timeStep);
  }

  MoveBallsAndChangeSizes(deltaTime - i);

  RecalculateBallsPositionsOnMove();

	ProcessTunnelsIntersection();

return LUX_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RecalculateBallsPositionsOnMove()
{
    ChainBalls::iterator ballsIter = chainBalls.begin();
    for(; ballsIter != chainBalls.end(); ballsIter++)
      RecalculateBallPosition(ballsIter->ball);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::RecalculateBallPosition( LuxBall* refBall )
{
  int64 ballPath = refBall->GetCoveredPath();

  SVector ballDirection;
  int iRes = chainPath->GetTrajectory()->GetTangentByLenght(ballPath, ballDirection);
  if( (iRes == LUX_OK) && (ballDirection != SVector(0, 0)))
  {
    refBall->SetDirection( ballDirection );
  }

  if(ballPath < 0)
  {
    refBall->SetPosition( SVector(ballPath, 0) );
    refBall->SetState( BALL_STATE_ROLL_IN );
    return;
  }

  SVector ballCoords; // new ball coordinates
  iRes = chainPath->GetTrajectory()->GetCoordsByLenght(ballPath,ballCoords);
  if(iRes == LUX_ERROR || iRes == LUX_LENGHT_TOO_BIG)
  {
    refBall->SetPosition(SVector(chainPath->GetTrajectory()->GetLenght() - ballPath, 0));
    refBall->SetState( BALL_STATE_ROLL_OUT );
    return;
  }

  refBall->SetPosition( ballCoords );

  if ( refBall->State() != BALL_STATE_IN_TUNNEL )
    refBall->SetState( BALL_STATE_ON_BOARD );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::SetBallsPositions( int64 newPos )
{
  ChainBalls::iterator ballsIter = chainBalls.begin();
  for(int i=0; ballsIter != chainBalls.end(); ballsIter++,i++)
  {
    CPtr<LuxBall> currentBall = ballsIter->ball;
    int currentBallRadius = currentBall->Size()/2;

    newPos -= currentBallRadius;
    
    ballsIter->ball->SetCoveredPath(newPos);
    ballsIter->edgePoint = newPos + currentBallRadius;

    newPos -= currentBallRadius;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::SendChainElementExplodedNotification( LuxBall* spBall,int _ballsNum )
{
  if(pviewNotifier != 0)
  {
    NI_VERIFY(chainBalls.size() >= _ballsNum, "LuxBallChain: more balls explode than currently present in chain", return);

    LuxChainElementExplodedNotification *pNotification = new LuxChainElementExplodedNotification();
    pNotification->pointExplosion   = spBall->Position();
    pNotification->colorExplosion   = spBall->Color();
    pNotification->explodedBallsNum = _ballsNum;

    if ( IsValid( pviewNotifier ) )
      pviewNotifier->Notify(*pNotification);
  }

  easel->GetWorld()->GetLogic()->GetFallingBoard()->DropCoin( spBall->Position() );
  easel->GetWorld()->GetPriestessProxy()->AddGoldDelayed( easel->GetPriestessLevelStats()->ballExplosionNafta * _ballsNum );
  easel->GetWorld()->GetPaintLogic()->OnPaintFlow( spBall->Position(), spBall->Color(), _ballsNum );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxBallChain::SendChainSlideLowNotification()
{
  if(pviewNotifier != 0)
  {
    LuxChainSlideLowNotification *pnotification = new LuxChainSlideLowNotification();

    if ( IsValid( pviewNotifier ) )
      pviewNotifier->Notify(*pnotification);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LuxBallChain* LuxBallChain::BackwardTearOffTonnel()
{
  LuxBallChain* tearedOffTail = 0;

  if(chainBalls.empty() )
  {
    // nothing to tear off
    return tearedOffTail;
  }

  if(chainSpeed >= 0)
  {
     return tearedOffTail;
  }

  // if the last ball is in tunnel there is no need to tear off tail
  BallState backBallState = chainBalls.back().ball->State();
  if ( backBallState == BALL_STATE_IN_TUNNEL )
  {
    SetSpeed( 0 );
    return tearedOffTail;
  }

  ChainBalls::iterator currentBall = chainBalls.end();
  const ChainBalls::iterator firstBall = chainBalls.begin();

  while (currentBall != firstBall)
  {
    --currentBall;

    BallState ballState = currentBall->ball->State();
    if ( ballState == BALL_STATE_IN_TUNNEL )
    {
      ++currentBall;
      tearedOffTail = TearOffTail(currentBall);

      NI_VERIFY(!tearedOffTail->chainBalls.empty(), "LuxBallChain: there is no balls in the teared off tail", return 0);

      tearedOffTail->SetSpeed( chainSpeed );

      SetSpeed( 0 );
      firstEdgePoint = tearedOffTail->chainBalls.front().edgePoint;
      firstEdgePointVelocity = tearedOffTail->chainBalls.front().edgeVelocity;

      RecalculateBallsSize();
      RecalculateBallsPositionsOnMove();
      ProcessTunnelsIntersection();


      tearedOffTail->RecalculateBallsSize();
      tearedOffTail->RecalculateBallsPositionsOnMove();
      tearedOffTail->ProcessTunnelsIntersection();

      return tearedOffTail;
    }
  } 

  return tearedOffTail;
}

}

REGISTER_SAVELOAD_CLASS_NM( LuxBallChain, PF_Minigames );