#pragma once
#include "System\StarForce\HiddenVars.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBSpline
{
  typedef Protection::HiddenVar<CVec2, 4> TPoint;
private:
ZDATA
  TPoint::T x; 
	CVec2 dx, d2x, d3x;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&x); f.Add(3,&dx); f.Add(4,&d2x); f.Add(5,&d3x); return 0; }
public:
	CBSpline() : x( VNULL2 ), dx( VNULL2 ), d2x( VNULL2 ), d3x( VNULL2 ) {}

	// для просмотра вперёд на предмет залоканных тайлов на пути
	const static int   N_OF_ITERATONS;

  void Init( const CVec2 &p3, const CVec2 &p2, const CVec2 &p1, const CVec2 &p0 );

	void Iterate();

	TPoint::TConstRef GetPoint() const { return x;  }
	const CVec2& GetDX() const    { return dx; }
	
	friend void Recrypt( CBSpline &val )
  {
     Recrypt( val.x );
  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
