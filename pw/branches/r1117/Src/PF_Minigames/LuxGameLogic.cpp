#include "stdafx.h"
#include "LuxGameLogic.h"

#include "LuxDef.h"

#include "LuxPlatformBoard.h"
#include "LuxGameBoard.h"
#include "LuxFallingBoard.h"
#include "BoostBoard.h"
#include "EaselConstants.h"
#include "Easel.h"

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// class LuxGameLogic implementation
//
//////////////////////////////////////////////////////////////////////////
LuxGameLogic::LuxGameLogic( PF_Core::IWorld* _pWorld ) :
  PF_Core::WorldObjectBase( _pWorld, false )
{

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuxGameLogic::InitGame(Easel* _easel,
  EaselNotifier* spNotifier,
  PaintLogic* _paintLogic,
  IPriestessProxy* refspPriestessProxy, NWorld::PFEaselPlayer* player)
{
  easel = _easel;
  m_spNotifier = spNotifier;    // referencing luxor-view notifier objects
  paintLogic = _paintLogic;
  priestessProxy = refspPriestessProxy;

  platformBoard = new LuxPlatformBoard( easel->GetPFWorld(), this );
  gameBoard = new LuxGameBoard( easel->GetPFWorld(), this, player );
  boostBoard = new LuxBoostBoard( easel->GetPFWorld(), this );
  fallingBoard = new LuxFallingBoard( easel->GetPFWorld(), this );
}

const NDb::DBEaselData* LuxGameLogic::GetGameData()
{
  return easel->GetData();
}

void LuxGameLogic::StartGame()
{
  gameBoard->SetBoardState( BOARDSTATE_LEVEL_BEGIN );
}

void LuxGameLogic::ProcessStep( int deltaTime, const SEaselMouseInput & mouseInput )
{
  SEaselMouseInput mouseCopy = mouseInput;

  mouseCopy.xCoord *= EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  mouseCopy.yCoord *= EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();

  if ( deltaTime == 0 )
  {
    ProcessInput( mouseCopy );
  }


  platformBoard->ProcessStep( deltaTime, this );
  fallingBoard->ProcessStep( deltaTime, this );
  gameBoard->ProcessStep( deltaTime, this );
  boostBoard->ProcessStep( deltaTime, this );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LuxGameLogic::ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event )
{
  return gameBoard->vProcessKeyboardEvent( event );
}

void LuxGameLogic::ProcessInput( const SEaselMouseInput & mouseInput )
{
  if ( !boostBoard->vProcessInput( mouseInput ) )
  {
    platformBoard->vProcessInput( mouseInput ); 
    gameBoard->vProcessInput( mouseInput );
  }
}

void LuxGameLogic::UpdateInputMove( SVector _mousePos )
{
  SEaselMouseInput inputCopy;
  inputCopy.xCoord = _mousePos.x * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  inputCopy.yCoord = _mousePos.y * EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
  inputCopy.leftBtnClicked  = false;
  inputCopy.rightBtnClicked = false;

  ProcessInput( inputCopy );
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( LuxGameLogic, PF_Minigames )
