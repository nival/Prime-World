#include "stdafx.h"
#include "RollCoordsConverter.h"

#include "Easel.h"
#include "EaselWorldClientConvertHelper.h"

#include "EaselConstants.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class PathConverter implementation
//
//////////////////////////////////////////////////////////////////////////
PathConverter::PathConverter( Easel* _easel )
{
  //convertHelper.Init(_easel,*(_easel->GetMinigames()));
  convertHelper = _easel->GetConvertHelper();
}

PathConverter::~PathConverter()
{

}

CVec3 PathConverter::ConvertWorldToClientCoordinates(const SVector& worldCoords ) const
{
  return convertHelper->ConvertWorldToClientCoordinates(worldCoords);
}


CVec3 PathConverter::ConvertWorldToClientDirection(const SVector& worldDirection ) const
{
  return (convertHelper->ConvertWorldToClientCoordinates(worldDirection) - convertHelper->GetWorldZeroCoordinates());
}

//////////////////////////////////////////////////////////////////////////
//
// class BambooRollInConverter implementation
//
//////////////////////////////////////////////////////////////////////////
BambooRollInConverter::BambooRollInConverter()
: rollInTo(VNULL3)
, rollInToFromDirection(0,0,0)
, rollInLength(0.0f)
, rollInPlacement(NULLPLACEMENT)
{

}

void BambooRollInConverter::Init( const CVec3 &_from, const CVec3 &_to, const Placement &_placement )
{
  rollInTo = _to;
  rollInToFromDirection = _from - _to;
  rollInLength = rollInToFromDirection.Length();
  rollInPlacement = _placement;

  Normalize(&rollInToFromDirection);
}

BambooRollInConverter::~BambooRollInConverter()
{
  
}

float BambooRollInConverter::CalculateRollInCoordinate( const SVector& worldCoords ) const
{
  CVec3 result(0, 0, 0);
  
  result.x = (float)worldCoords.x / EaselConst::Get_LOGIC_FIELD_HEIGHT();
  result.y = (float)worldCoords.y / EaselConst::Get_LOGIC_FIELD_WIDTH();

  return result.Length() * 8;
}

bool  BambooRollInConverter::IsVisibleOnRollIn(float rollInCoordinate) const
{
  NI_VERIFY( rollInCoordinate >= 0, "EaselWorldClientConvertHelper: roll in coordinate can't be less than zero ", return false);
  return (rollInCoordinate < rollInLength) ;
}

CVec3 BambooRollInConverter::GetClientCoordsOnRollIn(float rollInCoordinate) const
{
  NI_VERIFY( rollInCoordinate >= 0, "EaselWorldClientConvertHelper: roll in coordinate can't be less than zero ", return CVec3(0, 0, 0));

  CVec3 result = rollInTo;
  result += rollInToFromDirection * rollInCoordinate;

  return result;
}

CVec3 BambooRollInConverter::GetRollInDirection() const
{
  return -rollInToFromDirection;
}

//////////////////////////////////////////////////////////////////////////
//
// class WellRollOutConverter implementation
//
//////////////////////////////////////////////////////////////////////////
WellRollOutConverter::WellRollOutConverter()
: rollOutLength(0.0f)
, rollOutPlacement(NULLPLACEMENT)
, rollOutDirection(VNULL3)
{

}

WellRollOutConverter::~WellRollOutConverter()
{

}

void WellRollOutConverter::Init( const CVec3 &_from, const CVec3 &_middle, const CVec3 &_to, const Placement &_placement )
{
  rollOutPlacement = _placement;
  nstl::vector<CVec3> path;

  path.push_back(_from);
  path.push_back(_to);

  CVec3 startDir = _from - _middle;
  CVec3 endDir = _middle - _to;

  Normalize(&startDir);
  Normalize(&endDir);

  rollOutDirection = -startDir;

  static float tension = 6.0f;

  rollOutSpline.Setup(path, startDir, endDir, tension );
  rollOutLength = rollOutSpline.GetTotalLength();
}

float WellRollOutConverter::CalculateRollOutCoordinate( const SVector& worldCoords ) const
{
  CVec3 result(0, 0, 0);

  result.x = (float)worldCoords.x / EaselConst::Get_LOGIC_FIELD_HEIGHT();
  result.y = (float)worldCoords.y / EaselConst::Get_LOGIC_FIELD_WIDTH();

  return result.Length() * 8;
}

bool  WellRollOutConverter::IsVisibleOnRollOut(float rollOutCoordinate) const
{
  NI_VERIFY( rollOutCoordinate >= 0, "EaselWorldClientConvertHelper: roll out coordinate can't be less than zero ", return false);
  return (rollOutCoordinate < rollOutLength) ;
}

CVec3 WellRollOutConverter::GetClientCoordsOnRollOut(float rollOutCoordinate)
{
  CVec3 result;
  rollOutSpline.GetValue(&result, rollOutCoordinate);

  return result;
}

CVec3 WellRollOutConverter::GetRollOutDirection() const
{
  return rollOutDirection;
}

}

BASIC_REGISTER_CLASS( PF_Minigames::PathConverter )
BASIC_REGISTER_CLASS( PF_Minigames::BambooRollInConverter )
BASIC_REGISTER_CLASS( PF_Minigames::WellRollOutConverter )
