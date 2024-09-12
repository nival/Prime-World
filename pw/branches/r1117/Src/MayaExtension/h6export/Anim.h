// Animation data structures

// The Smallest, The Biggest And Zero
#define fSmallest -1e10f
#define fBiggest 1e10f
#define fZero 1e-10f

class FastWriter;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<unsigned _nCh> class TVAnimKey
{
	// Animation key for multiple channels
private:
	float v[_nCh];
public:
	unsigned nF;    // Frame number

	float& x;
	float& y;
	float& z;
	float& w;

	float& r;
	float& g;
	float& b;
	float& a;

	TVAnimKey() : 
		x( v[0] ),
		y( _nCh > 1 ? v[1] : v[0] ),
		z( _nCh > 2 ? v[2] : v[0] ),
		w( _nCh > 3 ? v[3] : v[0] ),
		r( v[0] ),
		g( _nCh > 1 ? v[1] : v[0] ),
		b( _nCh > 2 ? v[2] : v[0] ),
		a( _nCh > 3 ? v[3] : v[0] )
	{
	}

	const float& operator [] ( const unsigned _nI )	const
	{
		if ( _nI < _nCh )
		{
			return v[_nI];
		}
		return v[0];
	}

	float& operator [] ( const unsigned _nI )
	{
		if ( _nI < _nCh )
		{
			return v[_nI];
		}
		return v[0];
	}

	TVAnimKey<_nCh>& operator = ( const TVAnimKey<_nCh>& _aK )
	{
		nF = _aK.nF;
		for ( unsigned nI = 0; nI < _nCh; ++nI )
		{
			v[nI] = _aK[nI];
		}
		return *this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<unsigned _nCh> class TVTrack : public std::vector<TVAnimKey<_nCh>>
{
	// Animation track
private:
	TVAnimKey<_nCh> findNextKey( 
		const float* _fEps,					
		unsigned& _nCurr );             

public:
	MStatus compress( const float& _fTolerance );
	MStatus compressStepped();
	MStatus write( FastWriter* writer ) const;
	MStatus debug( const unsigned& _nID ) const;
};

struct animTrack
{
	TVTrack<3> pos;
	TVTrack<4> rot;
	TVTrack<3> scl;
};

