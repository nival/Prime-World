#include "stdafx.h"

#include "DBEasel.h"
#include "PaintPoint.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int POINT_RECT_OFFSET        = 50*EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER();
static const int POINT_MEASUREMENT_HEIGHT = 1000;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint::CPainterPoint( PF_Core::IWorld* _pWorld, CPaintFragment* _fragment, SVector _pointCoord, int _pointCapacity, NDb::EColor _pointColor ) :
  PF_Core::WorldObjectBase( _pWorld, false ),
  fragment( _fragment ),
  coord( _pointCoord ),
  capacity( _pointCapacity ), 
  paintAmount( 0 ),
  colour( _pointColor ),
  mode(EPainterPointMode::None)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPainterPoint::~CPainterPoint()
{
  capacity  = 0;
  paintAmount = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPainterPoint::IncCurrentCapacity(int value)
{
  paintAmount += value;
  paintAmount = min(paintAmount, capacity);
}

} // namespace PF_Minigames

REGISTER_SAVELOAD_CLASS_NM( CPainterPoint, PF_Minigames )
