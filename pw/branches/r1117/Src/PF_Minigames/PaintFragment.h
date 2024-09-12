#pragma once

namespace NDb
{
  enum EColor;
  struct DBFragment;
}

namespace PF_Minigames
{

class CPainterPoint;

//////////////////////////////////////////////////////////////////////////
//
// Painter Logic Fragment (fragment points container)
//
//////////////////////////////////////////////////////////////////////////
class CPaintFragment : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBB00, CPaintFragment );

public:
  typedef nstl::vector<CObj<CPainterPoint>> FragmentPoints;

public:
  CPaintFragment( PF_Core::IWorld* _pWorld, const NDb::DBFragment& _dbFragment );
  ~CPaintFragment();

  // getter methods
  int GetNumPoints() const { return fragmentPoints.size(); };
  const FragmentPoints& GetPoints() const { return fragmentPoints; }; 
  CPainterPoint* GetPoint( int point );

  // current ammount and capacity for specified color
  int GetColorAmount( NDb::EColor color ) const;
  int GetColorCapacity( NDb::EColor color ) const;
  int GetRemainCapacity( NDb::EColor color ) const;

  int GetPointColorAmount(NDb::EColor color, int point) const;

  // checkers (attention! methods will take time to calculate)
  bool CheckIfHasColor(NDb::EColor color) const ;
  bool CheckIfPainted();

  // calculation methods

  //Ugly static
  static CPainterPoint* GetClosestPoint( FragmentPoints & points, const SVector & destCoord, bool notFilledOnly, NDb::EColor color, int64 & refDist, bool ignoreMagent = false ); //color can be NDb::COLOR_ANY

  CPainterPoint* GetClosestPoint( const SVector & destCoord, bool notFilledOnly, NDb::EColor color, int64 & refDist, bool ignoreMagent = false ); //color can be NDb::COLOR_ANY
  CPainterPoint* GetLeastFilledPoint();

  template <typename Func>
  void ForAllPoints( Func& func )
  {
    FragmentPoints::iterator it = fragmentPoints.begin();
    FragmentPoints::iterator last = fragmentPoints.end();

    for ( ; it != last; ++it )
    {
      func( *it );
    }
  }

private:
  CPaintFragment() {}

  ZDATA_(PF_Core::WorldObjectBase)

  FragmentPoints fragmentPoints;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&fragmentPoints); return 0; }
};

}
