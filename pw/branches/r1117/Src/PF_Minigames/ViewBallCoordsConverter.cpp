#include "stdafx.h"
#include "ViewBallCoordsConverter.h"

#include "RollCoordsConverter.h"

// remove after 30.06.2009
#include "LuxPath.h"
#include "LuxBall.h"
#include "EaselTrajectory.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class BallCoordsConverter implementation
//
//////////////////////////////////////////////////////////////////////////
BallCoordsConverter::BallCoordsConverter( PathConverter* _converter)
: pathConverter(_converter)
{

}

BallCoordsConverter::~BallCoordsConverter()
{

}

CVec3 BallCoordsConverter::GetClientCoords( LuxBall* _ball )
{
  NI_VERIFY(_ball,"Converter error: LuxBall is corrupt", return CVec3(0,0,0));
  
  return vCalculateClientCoords(_ball);
}

CVec3 BallCoordsConverter::vCalculateClientCoords( LuxBall* _ball )
{
  return pathConverter->ConvertWorldToClientCoordinates(_ball->Position());
}

CVec3 BallCoordsConverter::GetClientDirection( LuxBall* _ball )
{
  NI_VERIFY(_ball,"Converter error: LuxBall is corrupt", return CVec3(0,0,0));

  return vCalculateClientDirection(_ball);
}

CVec3 BallCoordsConverter::vCalculateClientDirection( LuxBall* _ball )
{
  return pathConverter->ConvertWorldToClientDirection( _ball->Direction() );
}

//////////////////////////////////////////////////////////////////////////
//
// class SplineBallCoordsConverter implementation
//
//////////////////////////////////////////////////////////////////////////
SplineBallCoordsConverter::SplineBallCoordsConverter(PathConverter* _converter,
                                                     BambooRollInConverter* _rollin,
                                                     WellRollOutConverter* _rollout) 
: BallCoordsConverter(_converter)
, rollinConverter(_rollin)
, rolloutConverter(_rollout)
{

}

SplineBallCoordsConverter::~SplineBallCoordsConverter()
{ 

}

CVec3 SplineBallCoordsConverter::vCalculateClientCoords( LuxBall* _ball )
{
  switch(_ball->State())
  {
    case BALL_STATE_ROLL_OUT:
      return CalculateBForRollOut(_ball->Position());
    
    case BALL_STATE_ROLL_IN:
      return CalculateBForRollIn(_ball->Position());
    
    default:
      return BallCoordsConverter::vCalculateClientCoords(_ball);
 
  }
}

CVec3 SplineBallCoordsConverter::vCalculateClientDirection( LuxBall* _ball )
{
  switch(_ball->State())
  {
  case BALL_STATE_ROLL_OUT:
    return rolloutConverter->GetRollOutDirection();

  case BALL_STATE_ROLL_IN:
    return rollinConverter->GetRollInDirection();

  default:
    return BallCoordsConverter::vCalculateClientDirection(_ball);

  }
}

CVec3 SplineBallCoordsConverter::CalculateBForRollIn(const SVector &worldCoords)
{
  float rollInCoords = rollinConverter->CalculateRollInCoordinate(worldCoords);

  if( rollinConverter->IsVisibleOnRollIn(rollInCoords) )
  {
    return rollinConverter->GetClientCoordsOnRollIn(rollInCoords);
  }
  else
  {
    return CVec3(-1,-1,-1);
  }
}

CVec3 SplineBallCoordsConverter::CalculateBForRollOut(const SVector &worldCoords)
{
  float rollOutCoords = rolloutConverter->CalculateRollOutCoordinate(worldCoords);

  if( rolloutConverter->IsVisibleOnRollOut(rollOutCoords) )
  {
    return rolloutConverter->GetClientCoordsOnRollOut(rollOutCoords);
  }
  else
  {
    return CVec3(-1,-1,-1);
  }
}

//////////////////////////////////////////////////////////////////////////
//
// class ScorpionCoordsConverter implementation
//
//////////////////////////////////////////////////////////////////////////
ScorpionCoordsConverter::ScorpionCoordsConverter(PathConverter* _converter,
                                                 BambooRollInConverter* _rollin,
                                                 WellRollOutConverter* _rollout)
: pathConverter(_converter)
, rollinConverter(_rollin)
, rolloutConverter(_rollout)
{

}

ScorpionCoordsConverter::~ScorpionCoordsConverter()
{

}

CVec3 ScorpionCoordsConverter::GetClientCoords(LuxPath* _path,
                                               int64 currDistance,
                                               const SVector &worldCoords)
{
  int64 completeLenght = _path->GetTrajectory()->GetLenght();
  if(currDistance > completeLenght)
    return CalculateBForRollOut(worldCoords);
  else if(currDistance < 0)
    return CalculateBForRollIn(worldCoords);
  else
    return CalculateBForOnBoard(worldCoords);
}

CVec3 ScorpionCoordsConverter::CalculateBForRollIn(const SVector &worldCoords)
{
  float rollInCoords = rollinConverter->CalculateRollInCoordinate(worldCoords);

  if( rollinConverter->IsVisibleOnRollIn(rollInCoords) )
  {
    return rollinConverter->GetClientCoordsOnRollIn(rollInCoords);
  }
  else
  {
    return CVec3(-1,-1,-1);
  }
}

CVec3 ScorpionCoordsConverter::CalculateBForRollOut(const SVector &worldCoords)
{
  float rollOutCoords = rolloutConverter->CalculateRollOutCoordinate(worldCoords);

  if( rolloutConverter->IsVisibleOnRollOut(rollOutCoords) )
  {
    return rolloutConverter->GetClientCoordsOnRollOut(rollOutCoords);
  }
  else
  {
    return CVec3(-1,-1,-1);
  }
}

CVec3 ScorpionCoordsConverter::CalculateBForOnBoard(const SVector &worldCoords)
{
  return pathConverter->ConvertWorldToClientCoordinates(worldCoords);
}

}

BASIC_REGISTER_CLASS( PF_Minigames::BallCoordsConverter )
BASIC_REGISTER_CLASS( PF_Minigames::SplineBallCoordsConverter )

BASIC_REGISTER_CLASS( PF_Minigames::ScorpionCoordsConverter ) 
