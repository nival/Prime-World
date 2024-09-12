#pragma once

#include "LuxDef.h"
#include "LuxBoard.h"

#include "../PF_Core/WorldObject.h"

namespace NDb
{
  struct EPaintStatistics;
  struct DBEaselData;
}
namespace NWorld
{
  class PFEaselPlayer;
}

namespace PF_Minigames
{
//forward declarations
_interface IPriestessProxy;
class EaselNotifier;
class LuxPlatformBoard;
class LuxGameBoard;
class LuxBoostBoard;
class LuxFallingBoard;
class PaintLogic;
class Easel;

//////////////////////////////////////////////////////////////////////////
//
// common luxor logic class.
// class is responsible for step processing, and other objects
// instantiation
//
//////////////////////////////////////////////////////////////////////////
class LuxGameLogic : public PF_Core::WorldObjectBase
{  
  OBJECT_METHODS( 0x9D6B7400, LuxGameLogic );

public:
	LuxGameLogic( PF_Core::IWorld* _pWorld );
  virtual ~LuxGameLogic() {}

	// common administrative functionality
	void InitGame(Easel* _easel,
               EaselNotifier* spNotifier,
               PaintLogic* _paintLogic,
               IPriestessProxy* refspPriestessProxy, NWorld::PFEaselPlayer* player);
	void StartGame();

  void UpdateInputMove(SVector _mousePos);
	void ProcessStep( int deltaTime, const SEaselMouseInput & input );

  void ProcessInput( const SEaselMouseInput & mouseInput );

  bool ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event );

  LuxBoostBoard* GetBoostBoard() { return boostBoard; }
  LuxGameBoard* GetGameBoard() { return gameBoard; }
  LuxPlatformBoard* GetPlatformBoard() { return platformBoard; }
  LuxFallingBoard* GetFallingBoard() { return fallingBoard; }

  EaselNotifier* GetNotifier() { return m_spNotifier; }
  PaintLogic* GetPaintLogic() { return paintLogic; }
  IPriestessProxy* GetPristessProxy() { return priestessProxy; }
  const NDb::DBEaselData* GetGameData();
  Easel* GetEasel() { return easel; }

private:
  LuxGameLogic() {}

  ZDATA_(PF_Core::WorldObjectBase)

  CObj<LuxPlatformBoard> platformBoard;
  CObj<LuxGameBoard> gameBoard;
  CObj<LuxBoostBoard> boostBoard;
  CObj<LuxFallingBoard> fallingBoard;

  CPtr<IPriestessProxy> priestessProxy;

  CPtr<PaintLogic> paintLogic;
  CPtr<Easel> easel;
  CPtr<EaselNotifier> m_spNotifier;   // Luxor logic-view notification system
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&platformBoard); f.Add(3,&gameBoard); f.Add(4,&boostBoard); f.Add(5,&fallingBoard); f.Add(6,&priestessProxy); f.Add(7,&paintLogic); f.Add(8,&easel); f.Add(9,&m_spNotifier); return 0; }
private:

  
};

} // namespace PF_Minigames
