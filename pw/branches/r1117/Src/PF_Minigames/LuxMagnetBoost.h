#pragma once

#include "LuxBoost.h"
#include "DBEasel.h"


namespace PF_Minigames
{

class CPainterPoint;
class LuxMagnet;

//////////////////////////////////////////////////////////////////////////
//
// magnet boost definition
//
//////////////////////////////////////////////////////////////////////////
class LuxMagnetBoost : public LuxBoost
{
  OBJECT_METHODS( 0x9D6BD3C5, LuxMagnetBoost );

public:
  LuxMagnetBoost( PF_Core::IWorld* _pWorld, Easel * _easel,
                 const nstl::string &_refstrName,long _cooldown,
                 int _accessLevel, int _price,
                 int _searchSec, int _R1, int _R2, int _numBallsToEat )
  : LuxBoost( _pWorld, _easel, NDb::BOOSTTYPE_MAGNET, _refstrName, _cooldown, _accessLevel, _price )
  , searchInterval(_searchSec)
  , radiusR1(_R1)
  , radiusR2(_R2)
  , numBallToEat(_numBallsToEat)
  , currentState(EState::None)
  , userPos(0,0)
  {
  }

  ~LuxMagnetBoost() {}

  int GetSearchInterval() const { return searchInterval; };
  
  int GetR1() const { return radiusR1; };
  int GetR2() const { return radiusR2; };
  
  int GetNumBallsToEat() const { return numBallToEat; };
  
  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic );
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic );
  virtual bool ProcessInput( const SEaselMouseInput & mouseInput, LuxGameLogic* _gameLogic );

private:
  LuxMagnetBoost() {}

  void Start();
  void HighlightFragmentsWithMagnet( bool _highlight, LuxGameLogic* _gameLogic );
  CPainterPoint* LocateClosestPainterPoint( const SVector& _currPos );

  void InstallMagnet( CPainterPoint* _point, LuxGameLogic* _gameLogic );
  void StepInstalledMagnets( int deltaTime,  LuxGameLogic* _gameLogic );

  struct EState
  {
    enum Enum
    {
      None,
      Started,
      WaitingForPlacement,
      Placed,
    };
  };

  typedef nstl::list< CObj<LuxMagnet> > Magnets;

  ZDATA_(LuxBoost)
  
  int searchInterval;
  int radiusR1;
  int radiusR2;
  int numBallToEat;

  EState::Enum currentState;
  SVector userPos;
  CPtr<CPainterPoint> closestPoint;
  nstl::vector< CObj<CPainterPoint> > painterPoints;

  Magnets installedMagnets;
  CObj<LuxMagnet> newMagnet;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(LuxBoost*)this); f.Add(2,&searchInterval); f.Add(3,&radiusR1); f.Add(4,&radiusR2); f.Add(5,&numBallToEat); f.Add(6,&currentState); f.Add(7,&userPos); f.Add(8,&closestPoint); f.Add(9,&painterPoints); f.Add(10,&installedMagnets); f.Add(11,&newMagnet); return 0; }
  
};

}