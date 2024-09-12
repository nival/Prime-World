//!Component("System/Math")
//!Component("System/Commands")
#include "cxxtest/TestSuite.h"
#include "stdafx.h"
#include "Geom.h"

class GetLineCircleIntersectionTestSuite : public CxxTest::TestSuite 
{
public:

  void BadLineTest()
  {
    const CLine2 line( 0, 0, 2 );
    const CCircle circle( CVec2( 0, 0 ), 3 );

    CVec2 p1, p2;
    GetLineCircleIntersection( line, circle, p1, p2 );
  }

  void BadCirclesTest()
  {
    const CLine2 line( 1, 1, 1 );

    CCircle circle( CVec2( 0, 0 ), 0 );

    CVec2 p1, p2;
    GetLineCircleIntersection( line, circle, p1, p2 );
    circle = CCircle( CVec2( 0, 0 ), -1 );
    GetLineCircleIntersection( line, circle, p1, p2 );
  }

  void testNoIntersection()
  {
    const float r = 2;
    const CCircle circle( CVec2( 0, 0 ), r );

    const CLine2 l1( CVec2( r + 1, 0 ), CVec2( r + 1, 1 ) );
    const CLine2 l2( CVec2( 0, r + 1 ), CVec2( 1, r + 1 ) );
    const CLine2 l3( CVec2( - r - 1, 0 ), CVec2( - r - 1, 1 ) );
    const CLine2 l4( CVec2( 0, - r - 1 ), CVec2( 1, - r - 1 ) );

    CVec2 p1, p2;
    const int res1 = GetLineCircleIntersection( l1, circle, p1, p2 );
    const int res2 = GetLineCircleIntersection( l2, circle, p1, p2 );
    const int res3 = GetLineCircleIntersection( l3, circle, p1, p2 );
    const int res4 = GetLineCircleIntersection( l4, circle, p1, p2 );

    if ( ( res1 != 0 ) || ( res2 != 0 ) || ( res3 != 0 ) || ( res4 != 0 ) )
    {
      TS_FAIL( "NoIntersection: roots count" );
    }
  }

  void testOneIntersection()
  {
    const float r = 2;
    const CCircle circle( CVec2( 0, 0 ), r );

    const CVec2 p1( r, 0 );
    const CVec2 p2( 0, r );
    const CVec2 p3( -r, 0 );
    const CVec2 p4( 0, -r );

    const CVec2 pPlusR( r, r );
    const CVec2 pMinusR( -r, -r );

    const CLine2 l1( p1, pPlusR );
    const CLine2 l2( p2, pPlusR );
    const CLine2 l3( p3, pMinusR );
    const CLine2 l4( p4, pMinusR );

    CVec2 x1, x;
    const int res1 = GetLineCircleIntersection( l1, circle, x1, x );
    CVec2 x2;
    const int res2 = GetLineCircleIntersection( l2, circle, x2, x );
    CVec2 x3;
    const int res3 = GetLineCircleIntersection( l3, circle, x3, x );
    CVec2 x4;
    const int res4 = GetLineCircleIntersection( l4, circle, x4, x );

    if ( ( res1 != 1 ) || ( res2 != 1 ) || ( res3 != 1 ) || ( res4 != 1 ) )
    {
      TS_FAIL( "OneIntersection: roots count" );
    }

    if ( ( x1 != p1 ) || ( x2 != p2 ) || ( x3 != p3 ) || ( x4 != p4 ) )
    {
      TS_FAIL( "OneIntersection: root value" );
    }
  }

  void testTwoIntersections()
  {
    const float r = 2;
    CCircle circle( CVec2( 0, 0 ), r );

    const CVec2 p1( r, 0 );
    const CVec2 p2( 0, r );
    const CVec2 p3( -r, 0 );
    const CVec2 p4( 0, -r );

    const CLine2 l1( p1, p2 );
    const CLine2 l2( p2, p3 );
    const CLine2 l3( p3, p4 );
    const CLine2 l4( p4, p1 );
    const CLine2 l5( p1, p3 );
    const CLine2 l6( p2, p4 );

    CVec2 x00, x01;
    const int res1 = GetLineCircleIntersection( l1, circle, x00, x01 );
    CVec2 x10, x11;
    const int res2 = GetLineCircleIntersection( l2, circle, x10, x11 );
    CVec2 x20, x21;
    const int res3 = GetLineCircleIntersection( l3, circle, x20, x21 );
    CVec2 x30, x31;
    const int res4 = GetLineCircleIntersection( l4, circle, x30, x31 );
    CVec2 x40, x41;
    const int res5 = GetLineCircleIntersection( l5, circle, x40, x41 );
    CVec2 x50, x51;
    const int res6 = GetLineCircleIntersection( l6, circle, x50, x51 );

    if ( ( res1 != 2 ) || ( res2 != 2 ) || ( res3 != 2 ) || ( res4 != 2 ) || ( res5 != 2 ) || ( res6 != 2 ) )
    {
      TS_FAIL( "TwoIntersections: roots count" );
    }

    if ( !( ( ( x00 == p1 ) && ( x01 == p2 ) ) || ( ( x00 == p2 ) && ( x01 == p1 ) ) ) ||
         !( ( ( x10 == p2 ) && ( x11 == p3 ) ) || ( ( x10 == p3 ) && ( x11 == p2 ) ) ) ||
         !( ( ( x20 == p3 ) && ( x21 == p4 ) ) || ( ( x20 == p4 ) && ( x21 == p3 ) ) ) ||
         !( ( ( x30 == p4 ) && ( x31 == p1 ) ) || ( ( x30 == p1 ) && ( x31 == p4 ) ) ) ||
         !( ( ( x40 == p1 ) && ( x41 == p3 ) ) || ( ( x40 == p3 ) && ( x41 == p1 ) ) ) ||
         !( ( ( x50 == p2 ) && ( x51 == p4 ) ) || ( ( x50 == p4 ) && ( x51 == p2 ) ) ) )
    {
      TS_FAIL( "TwoIntersections: root value" );
    }
  }

  void testFloatIsNotEnough()
  {
    const CCircle circle( CVec2( 38.38665f, 21.20026f ), 8.0f );

    const CLine2 line1( 4.4280548f, -0.094490051f, -203.39771f );
    const CLine2 line2( -2.3486271f, -0.11591721f, 111.42590f );



    CVec2 p1, p2;
    GetLineCircleIntersection( line1, circle, p1, p2 );
    GetLineCircleIntersection( line2, circle, p1, p2 );
  }
};
