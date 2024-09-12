#ifndef _BRESENHAM_H_
#define _BRESENHAM_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBresenham2
{
	int x1, y1;
	int x2, y2;
	int xlen, ylen, len;
	int xinc, yinc;
	int xerr, yerr;
public:
	CBresenham2( int _x1, int _y1, int _x2, int _y2 )
		: x1( _x1 ), y1( _y1 ), x2( _x2 ), y2( _y2 ),
		xlen( abs(x2 - x1) + 1 ), ylen( abs(y2 - y1) + 1 ), len( Max(xlen, ylen) ),
		xinc( Sign(x2 - x1) ), yinc( Sign(y2 - y1) ),
		xerr( 0 ), yerr( 0 ) {	}
		//
		void Next()
		{
			// x component
			xerr += xlen;
			if ( xerr >= len )
				x1 += xinc, xerr -= len;
			// y component
			yerr += ylen;
			if ( yerr >= len )
				y1 += yinc, yerr -= len;
		}
		// check for line's end
		bool IsEnd() const { return (x1 == x2) && (y1 == y2); }
		// coords access
		int GetX() const { return x1; }
		int GetY() const { return y1; }
};
template <class TFunctional>
void MakeLine2( int x1, int y1, int x2, int y2, TFunctional &func )
{
	CBresenham2 line( x1, y1, x2, y2 );
	// first point
	func( line.GetX(), line.GetY() );
	// iterate line
	while ( !line.IsEnd() )
	{
		line.Next();
		func( line.GetX(), line.GetY() );
	}
}
template <class TFunctional>
void ScanLine2( int x1, int y1, int x2, int y2, TFunctional &func )
{
	CBresenham2 line( x1, y1, x2, y2 );
	// first point
	if ( func( line.GetX(), line.GetY() ) == false )
		return;
	// iterate line
	while ( !line.IsEnd() )
	{
		line.Next();
		if ( func( line.GetX(), line.GetY() ) == false )
			break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*															CBres																*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBres
{
	int xerr, yerr;
	int xlen, ylen, len;
	int xinc, yinc;

	SVector dir;
	//
	void Initialize()
	{
		xerr = 0;
		yerr = 0;

		xinc = Sign( xlen );
		yinc = Sign( ylen );
		xlen = abs( xlen ) + 1;
		ylen = abs( ylen ) + 1;
		len = Max( xlen, ylen );
	}

public:
	// для того, чтобы выдавал направления
	void Init( const SVector &start, const SVector &finish)
	{ 
		xlen = finish.x - start.x;
		ylen = finish.y - start.y;

		Initialize(); 
	}

	// для того, чтобы выдавал точки
	void InitPointByDirection( const SVector& start, const SVector &direction )
	{ 
		dir = start;
		xlen = direction.x;
		ylen = direction.y;

		Initialize(); 
	}

	// для того, чтобы выдавал точки
	void InitPoint( const SVector &start, const SVector &finish)
	{
		dir = start;
		xlen = finish.x - start.x;
		ylen = finish.y - start.y;

		Initialize();
	}

	//
	void MakeStep()
	{
		xerr += xlen;
		if ( xerr >= len )
			dir.x = xinc, xerr -= len;
		else
			dir.x = 0;

		yerr += ylen;
		if ( yerr >= len )
			dir.y = yinc, yerr -= len;
		else
			dir.y = 0;
	}

	void MakePointStep()
	{
		xerr += xlen;
		if ( xerr >= len )
			dir.x += xinc, xerr -= len;

		yerr += ylen;
		if ( yerr >= len )
			dir.y += yinc, yerr -= len;
	}

	const SVector& GetDirection() const { return dir; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*	 Line - grid intersection, Xiaolin Wu's algorithm											*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// bool TFunctional( int x, int y, float xEnter, float yEnter, float xLeave, float yLeave )
template <class TFunctional>
void ScanCoveredGridCells( float x1, float y1, float x2, float y2, TFunctional &func )
{
	const bool swapXY = fabs( x2 - x1 ) < fabs( y2 - y1 );

	if ( swapXY )
	{
		__swap( x1, y1 );
		__swap( x2, y2 );
	}

	const bool swapBE = x2 < x1;

	if ( swapBE )
	{
		__swap( x1, x2 );
		__swap( y1, y2 );
	}

	NI_VERIFY( x2 - x1 > 1.f, "Tool short line", return );

	const float gradient = (y2 - y1 ) / ( x2 - x1 );

	int xStart = x1;
	int xEnd = x2;

	if ( !swapBE )
	{
		float interY = y1 + gradient * (xStart - x1); 

		for ( int x = xStart; x <= xEnd; ++x )
		{
			//float nextInterFrac = ( interY - (int)interY ) + gradient;
			float nextInter = interY + gradient;

			bool res = true;
			if ( !swapXY )
			{
				res = func( x, (int)interY, x, interY, x + 1, nextInter );
				//if ( nextInterFrac > 1.f )
				//	res = res && func( x, (int)interY + 1, interY, x, nextInter, x + 1 );
			}
			else
			{
				res = func( (int)interY, x, interY, x, nextInter, x + 1 );
				//if ( nextInterFrac > 1.f )
				//	res = res && func( (int)interY + 1, x, interY, x, nextInter, x + 1 );
			}

			if ( !res )
				break;

			interY = nextInter;
		}
	}
	else
	{
		float interY = y2 + gradient * (xEnd - x2); 

		for ( int x = xEnd ; x >= xStart; --x )
		{
			//float nextInterFrac = ( interY - (int)interY ) - gradient;
			float nextInter = interY - gradient;

			bool res = true;
			if ( !swapXY )
			{
				res = func( x, (int)interY, x, interY, x - 1, nextInter );
				//if ( nextInterFrac > 1.f )
				//	res = res && func( x, (int)interY - 1, x, interY, x - 1, nextInter );
			}
			else
			{
				res = func( (int)interY, x, interY, x, nextInter, x - 1 );
				//if ( nextInterFrac > 1.f )
				//	res = res && func( (int)interY - 1, x, interY, x, nextInter, x - 1 );
			}

			if ( !res )
				break;

			interY = interY - gradient;
		}
	}

}

#endif
