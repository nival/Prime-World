#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLine
{
	int a, b, c;
	SVector p1, p2;
public:
	CLine() : a( 0 ), b( 0 ), c( 0 ), p1( -1, -1 ), p2( -1, -1 ) {};
	CLine( const SVector &ptStart, const SVector &ptFinish )
		: a( ptFinish.y - ptStart.y ), b( ptStart.x - ptFinish.x ), c( ptFinish.x*ptStart.y - ptStart.x*ptFinish.y ),
			p1( ptStart ), p2( ptFinish ) {}

	bool IsPointOnLine( const SVector &point )	const { return a*point.x + b*point.y + c == 0; }
	const int GetHPLineSign( const SVector &point ) const { return Sign( a*point.x + b*point.y + c ); }
	bool IsSegmIntersectLine( const SVector &ptStart, const SVector &ptFinish) const
	{
		const int t1 = Sign( GetHPLineSign( ptStart ) );
		const int t2 = Sign( GetHPLineSign( ptFinish ) );
		return (t1 >= 0) && (t2 <= 0) || (t1 <= 0) && (t2 >= 0);
	}
	float GetDistFromLine( const SVector &point ) const
	{
		return a*point.x + b*point.y + c;
	}
	bool IsBeamIntersectLine( const SVector &ptStart, const SVector &ptSecond ) const
	{
		return ( fabs( GetDistFromLine( ptStart ) ) > fabs( GetDistFromLine( ptSecond ) ) ) || IsSegmIntersectLine( ptStart, ptSecond );
	} 
	bool IsBeamIntersectSegm( const SVector &ptStart, const SVector &ptSecond ) const
	{
		if ( !IsBeamIntersectLine( ptStart, ptSecond ) )
			return false;
		const CLine line( ptStart, ptSecond );
		return line.IsSegmIntersectLine( p1, p2 );
	}
	const CLine GetPerpendicular( const SVector &point ) const { return CLine( point, SVector( point.x - a, point.y - b ) ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
