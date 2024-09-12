#pragma once

#include "../PF_Core/WorldObject.h"

#include "LuxBoard.h"

namespace NDb
{
  struct ELuxorStatistics;
  struct DBEaselData;
  struct EChainStatistics;
}
namespace NWorld
{
  class PFEaselPlayer;
}

namespace PF_Minigames
{

// forward declaration
class LuxGameBoardChain;
class LuxBallChain;
class LuxPath;
class LuxChainGenerator;
class LuxBall;
_interface ICollidable;

typedef nstl::vector<CObj<LuxGameBoardChain>> BoardChains;
typedef nstl::vector<CObj<LuxPath>> LuxorPaths;

class LuxGameBoard : public ILuxBoard, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C3, LuxGameBoard )

public:
    LuxGameBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic, NWorld::PFEaselPlayer* _player );
    ~LuxGameBoard();


    typedef nstl::list<CObj<ICollidable>> Colliders;
    typedef nstl::list<CObj<LuxBall>> Bullets; 

    // input processing implementation
    virtual bool vProcessInput( const SEaselMouseInput & mouseInput );
    virtual bool vProcessKeyboardEvent( EEaselKeyboardEvents::Enum event );
    virtual void ProcessStep( int deltaTime, LuxGameLogic* _gameLogic );

    void SetBoardState( LuxBoardState _newState );
    LuxBoardState GetBoardState() const { return boardState; }

    void SetFrozen( bool frozen ) { isFrozen = frozen; }
    bool IsFrozen() const { return isFrozen; }
    void SortBalls();

    void AddCollider( ICollidable* _collidable );

    BoardChains& GetChains() { return chains; }
    LuxorPaths& GetPaths() { return chainPaths; }

    Bullets& GetBullets() { return bullets; }
    void BallFired( LuxBall* _ball );

    bool IsLocalBoard() const { return GetWorld() == 0; }

private:
  LuxGameBoard() : ILuxBoard( BOARD_NULL, 0 ) { }

  ZDATA_(ILuxBoard)
  ZPARENT(PF_Core::WorldObjectBase)

  int waitTimer;     

  LuxBoardState boardState;

  Colliders colliders;

  // board active chains
  BoardChains chains;
  CObj<LuxChainGenerator> chainsGenerator;

    // board frozen flag
  bool isFrozen;

  LuxorPaths chainPaths;

  Bullets bullets;

  CPtr<NWorld::PFEaselPlayer> player;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ILuxBoard*)this); f.Add(2,(PF_Core::WorldObjectBase*)this); f.Add(3,&waitTimer); f.Add(4,&boardState); f.Add(5,&colliders); f.Add(6,&chains); f.Add(7,&chainsGenerator); f.Add(8,&isFrozen); f.Add(9,&chainPaths); f.Add(10,&bullets); f.Add(11,&player); return 0; }

private:
    void InitPaths();

    void InitChainsData( const NDb::DBEaselData* _data, EaselNotifier* pNotifier );

    bool SkipMovie();
   
    // chains methods
    bool CollideAndAddBullet( LuxBall* _bullet, int deltaTime );            // bullet-chains collision handling
    void GenerateNewChains( int deltaTime, LuxGameLogic* _gameLogic ); // making new chains
    void CheckChainReachEnd();             // chacking game failed situation (chain has reach end)

    void ChainBlastAllBalls();

    void RequestStateChange(LuxBoardState _newState);

    // notifications processing
    void UpdatePointer();

    void RemoveColliders();

    bool MoveShootingBall( LuxBall* _ball, int deltaTime );
    void MoveBullets( int deltaTime );


protected:
    // common methods
    virtual void ProcessRunStateStep( int deltaTime, LuxGameLogic* _gameLogic );
    virtual void ProcessFailStateStep( int deltaTime );
};

// helper methods
void ResetChainStatistics(NDb::EChainStatistics& chainStatistic);
void ProcessPaintBlastExplosion(const BoardChains &_chains,const SVector &_refBlastPos);
bool IsChainOnBoard(const BoardChains &_chains);
bool IsAnyChainOnBoardMoving(const BoardChains &_chains);

void SetBoardChainsSpeed(const BoardChains &_chains,int _speed);

}