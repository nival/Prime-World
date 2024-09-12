#pragma once

//#include "EaselWorldClientConvertHelper.h"

#include "../System/Spline.h"


namespace PF_Minigames
{

// forward declaration
class Easel;
class EaselWorldClientConvertHelper;


//////////////////////////////////////////////////////////////////////////
//FIXME: Фиктивный прокси-объект
//TODO: Заменить на EaselWorldClientConvertHelper
class PathConverter : public CObjectBase, public NonCopyable
{
  OBJECT_BASIC_METHODS( PathConverter )
public:
  explicit PathConverter( Easel* _easel );
  virtual ~PathConverter();

  // calculate client coordinates by world
  CVec3 ConvertWorldToClientCoordinates( const SVector& worldCoords ) const;

  // calculate client direction from world direction
  CVec3 ConvertWorldToClientDirection( const SVector& worldDirection ) const;

private:
  PathConverter() {}

  CPtr<EaselWorldClientConvertHelper> convertHelper;
};


//////////////////////////////////////////////////////////////////////////
//
// bamboo roll in converter
//
//////////////////////////////////////////////////////////////////////////
class BambooRollInConverter : public CObjectBase
{
  OBJECT_BASIC_METHODS( BambooRollInConverter )

public:
  BambooRollInConverter();
  virtual ~BambooRollInConverter();

  void  Init( const CVec3 &_from, const CVec3 &_to, const Placement &_placement );

  // calculation of client coordinates if ball is rolling in 
  float CalculateRollInCoordinate( const SVector& worldCoords ) const;
  bool  IsVisibleOnRollIn(float rollInCoordinate) const;
  CVec3 GetClientCoordsOnRollIn(float rollInCoordinate) const;
  CVec3 GetRollInDirection() const;

private:
  CVec3 rollInTo;
  CVec3 rollInToFromDirection;
  float rollInLength;

  Placement rollInPlacement;
};

//////////////////////////////////////////////////////////////////////////
//
// well roll out converter
//
//////////////////////////////////////////////////////////////////////////
class WellRollOutConverter : public CObjectBase
{
  OBJECT_BASIC_METHODS( WellRollOutConverter )

public:
  WellRollOutConverter();
  virtual ~WellRollOutConverter();

  void Init( const CVec3 &_from, const CVec3 &_middle, const CVec3 &_to, const Placement &_placement );

  float CalculateRollOutCoordinate( const SVector& worldCoords ) const;
  bool  IsVisibleOnRollOut(float rollOutCoordinate) const;
  CVec3 GetClientCoordsOnRollOut(float rollOutCoordinate);
  CVec3 GetRollOutDirection() const;

private:
  float          rollOutLength;
  CCubicSpline3D rollOutSpline;
  CVec3          rollOutDirection;

  Placement      rollOutPlacement;
};


} //namespace PF_Minigames
