#pragma once

#include "DBEasel.h"

#include "LuxBoard.h"
#include "LuxBoost.h"

#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{


//////////////////////////////////////////////////////////////////////////
//
// main boosts board class, is responsible for boosts creation
// firing boosts event observation
//
//////////////////////////////////////////////////////////////////////////
class LuxBoostBoard : public ILuxBoard, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4CC, LuxBoostBoard )

public:
  LuxBoostBoard( PF_Core::IWorld* _pWorld, LuxGameLogic* _gameLogic );
  ~LuxBoostBoard();

  void FireBoost( NDb::EBoostType _type );
  virtual bool vProcessInput( const SEaselMouseInput & mouseInput );
  virtual void ProcessStep( int deltaTime, LuxGameLogic* _gameLogic );

  bool ThereAreWaitingBoosts() const;
  Boosts& GetBoosts() { return boosts; }

  LuxBoost* GetBoost( NDb::EBoostType _type );

  void OnUnusedPaint( const SVector& explosionPoint, NDb::EColor explosionColor, int explodedBallsNum );

private:

  LuxBoostBoard() : ILuxBoard( BOARD_NULL, 0 ) { }

  ZDATA_(ILuxBoard)
  ZPARENT(PF_Core::WorldObjectBase)

  Boosts boosts;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ILuxBoard*)this); f.Add(2,(PF_Core::WorldObjectBase*)this); f.Add(3,&boosts); return 0; }
};

}