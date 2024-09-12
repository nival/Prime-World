#pragma once

#include "../PF_Core/WorldObject.h"
#include "../System/noncopyable.h"

#include "LuxBallChain.h"

namespace NDb
{
  struct DBEaselData;
  struct EChainStatistics;
}

namespace PF_Minigames
{

class EaselNotifier;
class LuxPath;
class LuxGameBoard;
class LuxChainGenerator;
class LuxGameLogic;

//////////////////////////////////////////////////////////////////////////
//
// chains clean up pred
//
//////////////////////////////////////////////////////////////////////////
class CleanUpChainsPred : public unary_function<CObj<LuxBallChain>,bool>
{
public:

  bool operator()(const CObj<LuxBallChain> &rhs) const
  {
    if(rhs->GetNumChainBalls() == 0)
      return true;
    else
      return false;
  }
};

//////////////////////////////////////////////////////////////////////////
//
// this class provides chains storage and generation functionality for single path 
//
//////////////////////////////////////////////////////////////////////////

typedef nstl::list<CObj<LuxBallChain>> BallChains;

class LuxGameBoardChain : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C2, LuxGameBoardChain )
public:

  LuxGameBoardChain( PF_Core::IWorld* _pWorld, LuxGameBoard *_pGameBoard );

  // checker
  bool IsAnyChainMoving() const;

  // chains speed setter
  void SetChainsSpeed(int _speed);

  // init chains generator with parameters from DB
  // LUX_OK on success, LUX_ERROR - otherwise
  int Init( const NDb::DBEaselData* _data, EaselNotifier* notifier, 
            LuxPath* _path, 
            LuxChainGenerator* _chainsGenerator);

  void AddChain( LuxBallChain* _newChain );

  // chain duplicate cloner
  template<class TReceiver>
  void GetChainsWeak(TReceiver& _receiver)
  {
    BallChains::iterator chainsIter = chains.begin();
    for(; chainsIter != chains.end(); ++chainsIter)
      _receiver.AddObject((*chainsIter));
  }

  // sort methods
  void SortAllChainsElements();

  bool CheckChainReachedEnd(int64 _endOffset) const;

  void ForceNewChainGeneration( LuxGameLogic* _gameLogic );          // forced mechanism
  void GenerateNewChains( int deltaTime, LuxGameLogic* _gameLogic );   // неудачный метод

  // move all chains by delta time
  void MoveChains(int deltaTime);

  void UpdateChainsSpeed();

  // chains cleanup
  void CleanUpChains();

  // merge in one intersecting chains
  void MergeIntersectingChains();

  // remove chains that passed end point
  void RemoveChainsCameToEnd( int _afterExitDistance );

  // remove all new 3+ sequences
  void RemoveSameColorSequences( LuxGameBoard* _gameBoard );

  // chain destruction (inspire boost and others) 
  void DestroyAllChains();

  // paintblast ball processing method ...
  void ProcessPaintBlast(const SVector &_refBlastPos,int64 _radius);

  void ValidateChains();

  template <typename Func>
  void ForAllChains( Func& func )
  {
    BallChains::iterator it = chains.begin();
    BallChains::iterator last = chains.end();

    for ( ; it != last; ++it )
    {
      func.currentPath = this;
      (*it)->ForAllBalls( func );
    }
  }

  BallChains& GetChains() { return chains; }

private:
  LuxGameBoardChain() {}

  void GenerateNewChain( LuxGameLogic* _gameLogic );

  

  ZDATA_(PF_Core::WorldObjectBase)

  CPtr<LuxChainGenerator> chainsGenerator; 
  CPtr<LuxPath>           chainPath;
  NDb::Ptr<NDb::DBEaselData> gameData;

  int defaultChainSpeed;
  int chainSpeed;

  BallChains chains;

  int nextChainTimeLeft;
  int newChainOffset;
  int64 killAfterEndOffset;

  CPtr<EaselNotifier> pNotifier;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&chainsGenerator); f.Add(3,&chainPath); f.Add(4,&gameData); f.Add(5,&defaultChainSpeed); f.Add(6,&chainSpeed); f.Add(7,&chains); f.Add(8,&nextChainTimeLeft); f.Add(9,&newChainOffset); f.Add(10,&killAfterEndOffset); f.Add(11,&pNotifier); return 0; }
};

//////////////////////////////////////////////////////////////////////////
//
// helper methods
//
//////////////////////////////////////////////////////////////////////////

// bullet-chains collision handling
void AddHittedBallToChain(LuxBallChain& chain, int64 ballPos, LuxBall* bullet, /*out*/bool &fColorMatched);

} // PF_Minigames
