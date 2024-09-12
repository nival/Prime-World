#pragma once

#include "Animated.h"
#include "AnimatedAlgorithms.h"
#include "../System/Spline.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TAnimated>
class Animated2Spline
{
public:
  Animated2Spline() : dest( 0 ), time( 0.0f ), needSpline( true ) {}

  void Init( typename TAnimated::TAnimatedType* _dest, const TAnimated& _src, float startTime )
  {
    dest = _dest;
    src = _src;
    time = startTime;
    
    NI_VERIFY ( src.Count() > 0, "Unexpected number of Animated points!", return );

    needSpline = ( src.Count() > 2 );

    if ( needSpline )
    {
      nstl::vector<CVec2> points;
     for ( int i = 0; i < src.Count(); i++ )
     {
        points.push_back( src.GetPoint( i ) );
     }

     spline.Build( points );
    }

    Evaluate();
  }
  
  void SetStartTime( float startTime )
  {
    time = startTime;

    Evaluate();
  }

  void Step( float dt )
  {
    if ( !IsAnimated() )
    {
      return;
    }

    time += dt;

    Evaluate();
  }

  float GetDiff()
  {
    if ( needSpline )
    {
      return spline.GetDiff( time );
    }

    return src.GetDiff( time );
  }

  void Evaluate()
  {
    if ( !IsAnimated() )
    {
      return;
    }

    if ( needSpline )
    {
      *dest = spline.Get( time );
    }
    else
    {
      *dest = src.GetValue( time );
      return;
    }
  }

  bool IsAnimated() const { return src.IsAnimated(); }

  float GetLength() const { return src.GetLength(); }

  bool IsFinished() const { return src.GetLength() < time; }

private:
  typename TAnimated::TAnimatedType* dest;
  TAnimated src;
  float time;

  bool needSpline;
  CubicSpline spline;

  typename TAnimated::const_iterator left;
  typename TAnimated::const_iterator right;

  typename TAnimated::const_iterator firstInSpline;
  typename TAnimated::const_iterator lastInSpline;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
