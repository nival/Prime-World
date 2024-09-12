#pragma once

#include "DBEasel.h"
#include "EaselNotifications.h"

#include "../PF_Core/WorldObject.h"

namespace NDb
{
  enum EColor;
  struct DBFragment;
  struct DBPainterPoint;
  struct EPaintStatistics;
}

namespace PF_Minigames
{
class EaselNotifier;

class CPainterPoint;
class CPaintFragment;

class EaselWorld;
class LuxGameLogic;
class Easel;

class PaintLogic : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6B7401, PaintLogic );

public:
  typedef nstl::vector<CObj<CPaintFragment>> PaintFragments;

public:
  PaintLogic( PF_Core::IWorld* _pWorld, EaselWorld* _world );
  virtual ~PaintLogic();

  typedef nstl::map<NDb::EColor, int> ColorCapacity;
  void GetColorCurrentCapacity( ColorCapacity& colorCapacity ) const;

  // getters
  const PaintFragments& GetFragments() const { return paintFragments; };

  void OnPaintFlow( const SVector & refpaintPosition, NDb::EColor refpaintColor, int paintAmmount );

  int GetNumPaintPoints() const;
  void GetPainterPoints( nstl::vector<CObj<CPainterPoint>>& points );

  float CalculateFillRatio() const; // filled balls / total capacity

  // common init/unit methods
  void InitLogic(Easel* _easel,
                EaselNotifier* spNotifier);
  void UninitLogic();

  int ProcessStep( int deltaTime, LuxGameLogic* _gameLogic );

  // alchemist
  int FillWithUnusedPaint( int unusedPaintAmount );

  void GetPaintStatistics( NDb::EPaintStatistics& stat );

  template <typename Func>
  void ForAllPoints( Func& func )
  {
    PaintFragments::iterator it = paintFragments.begin();
    PaintFragments::iterator last = paintFragments.end();

    for ( ; it != last; ++it )
    {
      (*it)->ForAllPoints( func );
    }
  }

private:
  PaintLogic() {}

  bool CheckPainted();

  void InitStatisticForPaint( NDb::EPaintStatistics& stat );
  void ResetStatistics( NDb::EPaintStatistics& stat );

  
  ZDATA_(PF_Core::WorldObjectBase)

  bool fIsCompletePainted; // all is painted flag
  PaintFragments paintFragments;

  CPtr<EaselWorld> world;
  // logic-view notification mechanism
  CPtr<EaselNotifier> viewNotifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&fIsCompletePainted); f.Add(3,&paintFragments); f.Add(4,&world); f.Add(5,&viewNotifier); return 0; }
protected:

  void SendPaintFlyingNotification( const SVector & from, CPainterPoint* spTo, CPaintFragment* spFragment, EaselNotifier* pNotifier );

  void SendPaintFlyingInPointNotification( const SVector & _from, const SVector & _to, NDb::EColor _paintColor, EaselNotifier *pNotifier );

  void OnFragmentPaintedNotification();

  // return false if point not found
  bool FillNearestPoint( const SVector & refpaintPosition, NDb::EColor refpaintColor, int paintAmmount, CPtr<CPainterPoint>& spTo, CPtr<CPaintFragment>& spFragment );
  bool FillMostWantedPoint( int paintAmmount, CPtr<CPainterPoint> & spToPoint );
};


}