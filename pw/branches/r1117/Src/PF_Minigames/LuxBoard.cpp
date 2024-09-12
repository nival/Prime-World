#include "stdafx.h"

#include "LuxBoard.h"
#include "EaselPriestess.h"
#include "LuxDef.h"

namespace PF_Minigames
{

ILuxBoard::ILuxBoard( LuxBoardType boardType, LuxGameLogic* _gameLogic ) 
: gameLogic(_gameLogic)
{
	
}

ILuxBoard::~ILuxBoard()
{

}

bool ILuxBoard::vProcessInput( const SEaselMouseInput & mouseInput )
{
  return false;
}


} // namespace PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::ILuxBoard )

