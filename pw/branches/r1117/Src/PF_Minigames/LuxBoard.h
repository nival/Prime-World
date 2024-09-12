#pragma once

#include "LuxDef.h"

#include "EaselNotifications.h"

#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// logic board types enumeration
//
//////////////////////////////////////////////////////////////////////////
enum LuxBoardType    // types int values go from 0 with 1 inc
{
	BOARD_NULL,
  BOARD_SHOOTING,
	BOARD_PLATFORM,
	BOARD_FALLING,
	BOARD_GAME,
  BOARD_BOOSTS,
  BOARD_TASK,
};

//////////////////////////////////////////////////////////////////////////
//
// board state types
//
//////////////////////////////////////////////////////////////////////////
enum LuxBoardState
{
  BOARDSTATE_NONE,
  BOARDSTATE_LEVEL_BEGIN,
  BOARDSTATE_LEVEL_RUN,
  BOARDSTATE_LEVEL_WON,
  BOARDSTATE_LEVEL_WON_BLAST_BALLS,
  BOARDSTATE_LEVEL_WON_MOVIE,
  BOARDSTATE_LEVEL_WON_FINAL,
  BOARDSTATE_LEVEL_FAIL,
  BOARDSTATE_LEVEL_FAIL_FINAL,
};

//////////////////////////////////////////////////////////////////////////
//
// common LuxorBoard interface
// supports all basic board operations and links, 
// also provides common initialization mechanism
//
// any board implementation always has 1 instance, no more
//
//////////////////////////////////////////////////////////////////////////
class LuxGameLogic;
_interface IPriestessProxy;

namespace EEaselKeyboardEvents { enum Enum; }

class ILuxBoard : public IObjectBase
{
public:
  ILuxBoard( LuxBoardType boardType, LuxGameLogic* _gameLogic );
  virtual ~ILuxBoard();

  LuxGameLogic* GetGameLogic() { return gameLogic; }

  // process game logic based on world's delta time
  virtual void ProcessStep( int deltaTime, LuxGameLogic* _gameLogic ) = 0;

  // if input happens, this method is called
  virtual bool vProcessInput( const SEaselMouseInput & mouseInput );

  virtual bool vProcessKeyboardEvent( EEaselKeyboardEvents::Enum event ) { return false; }

protected:
  ILuxBoard() {}

  ZDATA
  ZNOPARENT(IObjectBase)
  // priestess data access object
  CPtr<LuxGameLogic> gameLogic;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&gameLogic); return 0; }
};

} // namespace PF_Minigames