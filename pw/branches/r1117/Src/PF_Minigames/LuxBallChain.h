#pragma once

#include "DBEasel.h"
#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{

// forward declaration
class LuxBall;
class LuxPath;
class LuxBall;
class EaselNotifier;
class Easel;


class LuxBallChain : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C8, LuxBallChain )
public:
  // common chain balls implementation

  enum State
  {
    STATE_ROLL_IN = 0,        // chain is rolling in on the board 
    STATE_ON_BOARD,           // chain is currently on board
    STATE_ROLL_OUT          // chain is rolling out from board
  };

  class BallRecord
  {
  public:
    BallRecord() :
        insertedBall(false)
      , edgePoint(0)
      , edgeVelocity(0)
      , currentVelocity(0)
      , offset(0)
      , tunnelEnd(0)
      , explosionCountdown(5)
    {
    }

    ZDATA

    CObj<LuxBall> ball;           //< ball itself
    bool insertedBall;
    int explosionCountdown;

    int64 edgePoint;                         //< edge point of the ball. The one from end of trajectory side
    float edgeVelocity;
    float currentVelocity;
    float offset;

    float tunnelEnd;

    ZEND int operator&( IBinSaver &f ) { f.Add(2,&ball); f.Add(3,&insertedBall); f.Add(4,&explosionCountdown); f.Add(5,&edgePoint); f.Add(6,&edgeVelocity); f.Add(7,&currentVelocity); f.Add(8,&offset); f.Add(9,&tunnelEnd); return 0; }

    bool CanExplode() 
    {
      if ( insertedBall )
        explosionCountdown--;

      return insertedBall && ( explosionCountdown <= 0);
    }
  };

  typedef nstl::list<BallRecord> ChainBalls;

  LuxBallChain( LuxPath* _path, EaselNotifier *pNotifier, Easel* _easel );
  ~LuxBallChain();

  // chains copier
  template<class TReceiver>
  void GetBalls(TReceiver& _receiver)
  {
    ChainBalls::iterator ballsIter = chainBalls.begin();
    for(; ballsIter != chainBalls.end(); ++ballsIter)
      _receiver.AddObject(ballsIter->ball);
  }

  bool IsIntersects(const LuxBallChain& otherChain);

  // chain explosion methods
  void ExplodeChainBalls();

  // ball explosion at position
  bool ExplodeBallAtPos(int64 _pos,/*out*/CPtr<LuxBallChain>& tearedOfftail);

  // chain sort methods
  void SortChain();

  // chain balls insertion/deletion (used with initialization)
  // chain balls position will not be set 
  void AddChainBallInit( LuxBall* spBall );

  // chain ball insertion/deletion at run-time
  void AddChainBallRunTime( LuxBall* spBall, bool& fColorMatched );

  // chain position set/get (based on chain first element)
  int64 GetChainPosition() const; 
  int64 GetChainEnd() const;
  int64 GetChainLength() const;

  int   SetChainPosition(int64 newPosition); 

  // getters
  int   GetNumChainBalls() const { return chainBalls.size(); };

  State GetState() const { return state; }

  int   GetSpeed() const { return (float)chainSpeed; };

  void  SetDefaultSpeed(int newSpeed) { chainDefaultSpeed = newSpeed; }
  void  SetSpeed(int newSpeed) { chainSpeed = newSpeed; } 

  bool MergeTail( LuxBallChain* other );

  // chain movement (will calculate path, based on speed)
  int MoveChain(int deltaTime);

  void UpdateChainSpeed(bool lastChain);

  // explodes 3+ same color segment of the chain from the head and return teared off tail.
  // return false if there in no 3+ same color segments and true otherwise
  // smart pointer will be empty if there is no teared off tail
  LuxBallChain* ExplodeFirstSameColorSegment();

  LuxBallChain* BackwardTearOffTonnel();

  // explodes all paint blast balls within the ball radius (just one wave)
  LuxBallChain* ExplodePaintBlastWave(const SVector &_refBlastPos,int64 _radius);

  // tunnels
  void ProcessTunnelsIntersection();

  template <typename Func>
  void ForAllBalls( Func& func )
  {
    ChainBalls::iterator it = chainBalls.begin();
    ChainBalls::iterator last = chainBalls.end();

    for ( ; it != last; ++it )
    {
      func.currentChain = this;
      func( it->ball );
    }
  }

  ChainBalls& GetBalls() { return chainBalls; }
  LuxPath* GetPath() { return chainPath; }

private:

  LuxBallChain() {}

  bool CheckOnExplosion( const ChainBalls::iterator& _it );

  // init internal insertion/deletion methods 
  void InitAddBallEnd(LuxBall* spBall);

  // run-time internal insertion/deletion methods
  void RunTimeAddBallFront(LuxBall* spBall, /*out*/bool &fColorMatched);
  void RunTimeAddBallMiddle(LuxBall* spBall, /*out*/bool &fColorMatched);
  void RunTimeAddBallEnd(LuxBall* spBall, /*out*/bool &fColorMatched);

  // Paintblast area methos
  bool IsInsidePaintBlast(const SVector &_refballPos,const SVector &_refblastPos,int64 blastRadius);
  LuxBallChain* PaintBlastExplodeBalls(const ChainBalls::iterator& _explodeFrom, const ChainBalls::iterator& _explodeTo);

  bool CheckCanExplodeBalls( const ChainBalls::iterator & explodeFrom, const ChainBalls::iterator & explodeTo, int numBalls ) const;
  LuxBallChain* ExplodeBalls(const ChainBalls::iterator& explodeFrom, const ChainBalls::iterator& _explodeTo, int numBalls);
  LuxBallChain* ExplodeBall(const ChainBalls::iterator& _ball);

  // returns new tail 
  LuxBallChain* ProcessTailTearOff(const ChainBalls::iterator& _From, const ChainBalls::iterator& _To);
  LuxBallChain* TearOffTail(const ChainBalls::iterator& tailStart);

  // returns iterator to first added tail element
  ChainBalls::iterator StealBallsToTail( LuxBallChain* chain );

  // nortifies view about new added ball
  void NotifyNewBallAdded( LuxBall* _ball  );

      
  void SendChainElementExplodedNotification(LuxBall* spBall,int _ballsNum);
  void SendChainSlideLowNotification();

  // internal helper methods
  void CalculateOffset(int64 start, int64 end, int deltaTime, float& offset, int64& currentPoint, float& currentVelocity);
  void RecalculatePoint(float previous, float offset, int64& currentPoint, float& currentVelocity);
  void RecalculateBallsSize();

  void MoveBallsAndChangeSizes(int deltaTime );
  void MoveChainBallsByVelocity(int deltaTime );

  float CalculateEdgeAcceleration(int64 start, int64 curretn, int64 end, int deltaTime);
  bool StepVelocity(int desiredBallVelocity, int deltaTime, float& currentBallVelocity);

  ZDATA_(PF_Core::WorldObjectBase)

  State state;

  CPtr<LuxPath> chainPath;

  int        chainDefaultSpeed;
  int        chainSpeed;        // current chain speed
  int64      firstEdgePoint;    // first point of chain.
  float      firstEdgePointVelocity;
  ChainBalls chainBalls;        // all balls in chain
  CPtr<Easel> easel;

  // paint and view notifier and methods
  CPtr<EaselNotifier> pviewNotifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&state); f.Add(3,&chainPath); f.Add(4,&chainDefaultSpeed); f.Add(5,&chainSpeed); f.Add(6,&firstEdgePoint); f.Add(7,&firstEdgePointVelocity); f.Add(8,&chainBalls); f.Add(9,&easel); f.Add(10,&pviewNotifier); return 0; }
private:

protected:
  // recalculating all chain balls based on moved position
  void RecalculateBallsPositionsOnMove();
  void RecalculateBallPosition( LuxBall* refBall );

  // set all balls positions anew, based on hear pos
  void SetBallsPositions( int64 newPos );
  
public:
  void OnReconnect();
};

}