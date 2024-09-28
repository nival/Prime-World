#pragma once

#include "EaselConstants.h"

#include "../PF_Core/WorldObject.h"

namespace NDb
{
  enum EColor;
}

namespace PF_Minigames
{

namespace EPainterPointMode
{
  enum Enum
  {
    None,
    MagnetHighlight,
    MagnetPreselect,
    MagnetInstalled
  };
}

class CPaintFragment;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPainterPoint : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBB01, CPainterPoint );

public:
  CPainterPoint( PF_Core::IWorld* _pWorld, CPaintFragment* _fragment, SVector _pointCoord, int _pointCapacity, NDb::EColor _pointColor );
  ~CPainterPoint();

  // checker methods
  bool HasRoom() { return paintAmount < capacity; }

  // getter methods
  const SVector & GetCoord() const { return coord; };
  int GetCapacity() const { return capacity; };
  int GetAmount() const { return paintAmount; };
  int GetRoomLeft() const { return ( paintAmount <= capacity ) ? capacity - paintAmount : 0; }
  NDb::EColor GetColor() const { return colour; };

  void IncCurrentCapacity(int value);

  EPainterPointMode::Enum GetMode() const { return mode; }
  void SetMode( EPainterPointMode::Enum _mode ) { mode = _mode; }

  CPaintFragment* GetFragment() { return fragment; }
  
private:
  CPainterPoint() {}

  ZDATA_(PF_Core::WorldObjectBase)

  SVector     coord;       // logic point coordinates
  int         capacity;    // max amount of paint to flow in
  int         paintAmount;   // amount of paint already flowed in
  NDb::EColor colour;       // point accepted color

  EPainterPointMode::Enum mode;

  CPtr<CPaintFragment> fragment;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&coord); f.Add(3,&capacity); f.Add(4,&paintAmount); f.Add(5,&colour); f.Add(6,&mode); f.Add(7,&fragment); return 0; }
};

} //namespace PF_Minigames
