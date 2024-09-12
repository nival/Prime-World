#ifndef _PLACEMENT_H_
#define _PLACEMENT_H_

#include "matrix43.h"

struct Placement
{
	CVec3 pos;
	CQuat rot;
	CVec3 scale;

	Placement()
	{
		pos = VNULL3;
		rot = QNULL;
		scale = CVec3( 1.f, 1.f, 1.f );
	}

	Placement( const Placement& a )
	{
		pos = a.pos;
		rot = a.rot;
		scale = a.scale;
	}

	Placement( const CVec3& p, const CQuat& r, const CVec3 s )
	{
		pos = p;
		rot = r;
		scale = s;
	}

	Placement( const CVec3& p )
	{
		pos   = p;
		rot   = QNULL;
		scale = CVec3(1.0f, 1.0f, 1.0f);
	}

	void GetMatrix( Matrix43* res ) const
	{
		ComposeMatrix( *res, pos, rot, scale );
	}

	void FromMatrix( const Matrix43& src )
	{
		DecomposeMatrix( src, pos, rot, scale );
	}

	void Shift(const CVec3 &inPos)
	{
		CVec3 shiftPos;
		rot.Rotate( &shiftPos, inPos );
		shiftPos.Mul( shiftPos, scale );
		pos += shiftPos;
	}

  void Interpolate(const Placement& p1, const Placement& p2, const float t)
  {
    pos.Interpolate(p1.pos, p2.pos, t);
    rot.Interpolate(p1.rot, p2.rot, t);
    scale.Interpolate(p1.scale, p2.scale, t);
  }

	void Transform(const CVec3 &inPos, CVec3 &outPos) const
	{
		rot.Rotate( &outPos, inPos );
		outPos.Mul( outPos, scale );
		outPos += pos;
	}

	Placement& operator+=( const Placement& a )
	{
		Shift(a.pos);
		rot = rot * a.rot;
		scale.Mul( scale, a.scale );
		return *this;
	}

  Placement operator+( const Placement& a ) const
  {
    Placement res = *this;
    res += a;
    return res;
  }

  Placement operator-() const
  {
    Placement res;
    res.pos = -pos;
    res.pos.Div(res.pos,scale);
    res.scale.x = 1/scale.x;
    res.scale.y = 1/scale.y;
    res.scale.z = 1/scale.z;
    res.rot = rot;
    res.rot.Inverse();
    return res;
  }

  Placement& operator-=( const Placement& a )
  {
    scale.Div( scale, a.scale );
    CQuat inverse = a.rot;
    inverse.Inverse();
    rot = rot * inverse;
    Shift(-a.pos);
    return *this;
  }

  Placement operator-( const Placement& a ) const
  {
    Placement res = *this;
    res -= a;
    return res;
  }

  CVec2 Get2DDirection() const
  {
    CVec3 res;
    rot.Rotate(&res, INITIALDIR3);
    return CVec2(res.x,res.y);
  }

  bool IsValid() const
  {
    return pos.IsFinite() && rot.IsFinite() && scale.IsFinite();
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Placement NULLPLACEMENT ( VNULL3, QNULL, CVec3( 1.f, 1.f, 1.f ) );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif 	// _PLACEMENT_H_

