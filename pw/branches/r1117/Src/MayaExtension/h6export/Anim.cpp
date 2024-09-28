#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::anim()
{
	// For linking purposes
	TVTrack<1> tmp1;
	tmp1.compress( 0.0f );
	TVTrack<2> tmp2;
	tmp2.compress( 0.0f );
	TVTrack<3> tmp3;
	tmp3.compress( 0.0f );
	TVTrack<4> tmp4;
	tmp4.compress( 0.0f );

	// Get skeleton data via skeleton export
  if ( skeleton.empty() )
  {
    if ( skel() != MS::kSuccess )
  	{
	  	displayError( "Skeleton data gathering failed." );
		  return MS::kFailure;
	  }
  }

	SIGN = animSIGN;

	int nMaxFrame, nMinFrame;
	MGlobal::executeCommand( "playbackOptions -q -max", nMaxFrame );
	MGlobal::executeCommand( "playbackOptions -q -min", nMinFrame );

	// Gather data
	animData.clear();
	animData.resize( skeleton.size() );
	for ( int nFrame = nMinFrame; nFrame <= nMaxFrame; ++nFrame )
	{
		MGlobal::viewFrame( nFrame );

		for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
		{
			getJointFrame( nI, nFrame - nMinFrame );// Need zero-based
		}
	}

	// Compress
	//for ( unsigned nI = 0; nI < animData.size(); ++nI )
	//{
	//	flipQuaternion( animData[nI] );
	//	animData[nI].pos.compress( fTolerance );
	//  animData[nI].rot.compress( fTolerance );
	//	animData[nI].scl.compress( fTolerance );
	//}

  //debugOutputInfo( "c:/pos.txt" );

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::getJointFrame( const unsigned& _nID, const unsigned& _nFrame )
{
	// Get transform matrix for joint of _nID from skeleton
	
	MMatrix m = getMatrix( _nID );

	MTransformationMatrix mTM( m );

	MVector t = mTM.getTranslation( MSpace::kPostTransform );
	MQuaternion r;
  mTM.getRotationQuaternion( r.x, r.y, r.z, r.w, MSpace::kPostTransform );
	double s[3];
	mTM.getScale( s, MSpace::kPostTransform );

	TVAnimKey<3> aK3;
	aK3.nF = _nFrame;
	aK3.x = float( t.x );
	aK3.y = float( t.y );
	aK3.z = float( t.z );
	animData[_nID].pos.push_back( aK3 );

	TVAnimKey<4> aK4;
	aK4.nF = _nFrame;
	aK4.x = float( r.x );
	aK4.y = float( r.y );
	aK4.z = float( r.z );
	aK4.w = float( r.w );
	animData[_nID].rot.push_back( aK4 );

	aK3.x = float( s[0] );
	aK3.y = float( s[1] );
	aK3.z = float( s[2] );
	animData[_nID].scl.push_back( aK3 );

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::flipQuaternion( animTrack& _t )
{
	// Search track for possible quaternion flips an flip them back.
	// This should be made before keys compression!

	float fX0 = _t.rot[0].x;
	float fY0 = _t.rot[0].y;
	float fZ0 = _t.rot[0].z;
	float fW0 = _t.rot[0].w;
	for ( unsigned nI = 1; nI < _t.rot.size(); ++nI )
	{
		float fDot = 
			fX0 * _t.rot[nI].x + 
			fY0 * _t.rot[nI].y +	
			fZ0 * _t.rot[nI].z +	
			fW0 * _t.rot[nI].w;

		if ( fDot < 0.0f )
		{
			// Got flip!
			_t.rot[nI].x = - _t.rot[nI].x;
			_t.rot[nI].y = - _t.rot[nI].y;
			_t.rot[nI].z = - _t.rot[nI].z;
			_t.rot[nI].w = - _t.rot[nI].w;
		}

		fX0 = _t.rot[nI].x;
		fY0 = _t.rot[nI].y;
		fZ0 = _t.rot[nI].z;
		fW0 = _t.rot[nI].w;
	}
	return MS::kSuccess;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<unsigned _nCh> MStatus TVTrack<_nCh>::compress( const float& _fTolerance )
{
	// Remove keys that deviate from line less than tolerance

	TVTrack<_nCh>& t = *this;
	if ( t.size() == 0 )
	{
		return MS::kFailure;
	}

	// Get absolute fEps from relative fTolerance for each channel
	float fEps[_nCh];
	for ( unsigned nI = 0; nI < _nCh; ++nI )
	{
		float fMin = fBiggest;
		float fMax = fSmallest;
		for ( unsigned nJ = 0; nJ < t.size(); ++nJ )
		{
			if ( t[nJ][nI] > fMax )
			{
				fMax = t[nJ][nI];
			}
			if ( t[nJ][nI] < fMin )
			{
				fMin = t[nJ][nI];
			}
		}

		// If min = max, then we have flat curve, use 1.0 as fEps to get only edge keys
		fEps[nI] = fMax - fMin < fZero ? 1.0f : _fTolerance * abs( fMax - fMin ) / 100.0f;
	}

	// Original curve offset "up" and "down" by fEps and new 
	// part-linear curve built to fit into this "tunnel"

	TVTrack<_nCh> compressed; // Storage for result keys
	compressed.push_back( t[0] );
	unsigned nCurr = 0;
	while ( compressed.back().nF < t.back().nF )
	{
		compressed.push_back( findNextKey( fEps, nCurr ));
	}

	// Copy to original
	t = compressed;

	return MS::kSuccess;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<unsigned _nCh> TVAnimKey<_nCh> TVTrack<_nCh>::findNextKey( 
	const float* _fEps,						 // Compression value
	unsigned& _nCurr )             // Current element index
{
	// Find furthest "visible" key in "tunnel"

	TVTrack<_nCh>& t = *this;
	TVAnimKey<_nCh> aKRes; // Result storage
	aKRes.nF = 0xFFFFFFFF;

	// Min-Max values for each channel init
	float fMin[_nCh];
	float fMax[_nCh];
	for ( unsigned nI = 0; nI < _nCh; ++nI )
	{
		aKRes[nI] = 0.0f;
		fMin[nI] = fSmallest;
		fMax[nI] = fBiggest;
	}

	TVAnimKey<_nCh> prev = t[_nCurr];
	while ( ++_nCurr < t.size() ) 
	{
		TVAnimKey<_nCh> next = t[_nCurr];

		unsigned nDx = next.nF - prev.nF;
		if ( nDx <= 0 )
		{
			return aKRes; // Bullshit! Return 0xFFFFFFFF as frame number
		}

		for ( unsigned nI = 0; nI < _nCh; ++nI )
		{
			if ( _fEps[nI] < fZero )
			{
				aKRes = next;
				return aKRes;
			}

			// Make "tunnel" and get current-to-next min-max tangents
			float fNextMin = ( next[nI] - _fEps[nI] - prev[nI] ) / float( nDx );
			float fNextMax = ( next[nI] + _fEps[nI] - prev[nI] ) / float( nDx );

			// Check "visibility"
			bool bMinVisible = false;
			if ( fNextMin > fMin[nI] && fNextMin < fMax[nI] )
			{
				fMin[nI] = fNextMin;
				bMinVisible = true;
			}

			bool bMaxVisible = false;
			if ( fNextMax < fMax[nI] && fNextMax > fMin[nI] )
			{
				fMax[nI] = fNextMax;
				bMaxVisible = true;
			}

			if ( bMinVisible && bMaxVisible )
			{
				// Still visible - proceed
				continue;
			}

			// Return last visible
			aKRes = t[--_nCurr];
			return aKRes;
		}
	}

	return t.back();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus TVTrack<1>::compressStepped()
{
	// Treat float values as stepped integers

	TVTrack<1>& t = *this;
	if ( t.size() == 0 )
	{
		return MS::kFailure;
	}

	TVTrack<1> compressed; // Storage for result keys

	TVAnimKey<1> aK = t.front();
	aK[0] = float( int( aK[0] ));
	compressed.push_back( aK );

	for ( unsigned nI = 1; nI < t.size() - 1; nI++ )
	{
		TVAnimKey<1> aKCurr = t[nI];
		if ( int( aK[0] ) != int( aKCurr[0] ) )
		{
			aK = aKCurr;
			aK[0] = float( int( aKCurr[0] ));
			compressed.push_back( aK );
		}
	}

	aK = t.back();					
	aK[0] = float( int( aK[0] ));
	compressed.push_back( aK );

	// Copy to original
	t = compressed;

	return MS::kSuccess;
}
