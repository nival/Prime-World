#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::debugTracks() const
{
	for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
	{
		animTrack t = animData[nI];
		fprintf_s( stderr, "---%s---\n", skeleton[nI].name.data() );
		fprintf_s( stderr, "\ttX\ttY\ttZ\t\trX\trY\trZ\trW\t\tsX\tsY\tsZ\n" );
		unsigned nJ = 0;
		while (
			nJ < t.pos.size() ||
			nJ < t.rot.size() ||
			nJ < t.scl.size() )
		{
			t.pos.debug( nJ );
			t.rot.debug( nJ );
			t.scl.debug( nJ );

			fprintf_s( stderr, "\n" );
			nJ++;
		}
	}
	return MS::kSuccess;
}

MStatus h6export::debugOutputInfo( const char* filename ) const
{
  FILE* f = 0;
  fopen_s( &f, filename, "w+" );
  for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
  {
    const animTrack& t = animData[nI];
    fprintf_s( f, "---%s---\n", skeleton[nI].name.data() );
    for ( uint timeIdx = 0; timeIdx < t.pos.size() || timeIdx < t.rot.size() || timeIdx < t.scl.size(); timeIdx++ )
    {
      fprintf_s( f, "%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\n", (float)timeIdx/30.0f,
        t.pos[timeIdx][0], t.pos[timeIdx][1], t.pos[timeIdx][2],
        t.rot[timeIdx][0], t.rot[timeIdx][1], t.rot[timeIdx][2], t.rot[timeIdx][3],
        t.scl[timeIdx][0], t.scl[timeIdx][1], t.scl[timeIdx][2] );
    }
  }
  fclose(f);
  return MS::kSuccess;
}

MStatus h6export::debugOutputInfoVertices( const char* filename ) const
{
  FILE* f = 0;
  fopen_s( &f, filename, "w+" );
  for ( unsigned nI = 0; nI < vertices.size(); ++nI )
  {
    const exportVertex& t = vertices[nI];
    fprintf_s( f, "%d\t%d\t%5.2f\t%5.2f\t%5.2f\t%d\t%5.2f\t%d\t%5.2f\t%d\t%5.2f\n",
        t.ID, t.mayaID, t.x, t.y, t.z, t.w[0].jointID, t.w[0].value,
        t.w[1].jointID, t.w[1].value, t.w[2].jointID, t.w[2].value );
  }
  fclose(f);
  return MS::kSuccess;
}

template<unsigned _nCh> MStatus TVTrack<_nCh>::debug( const unsigned& _nID ) const
{
	const TVTrack<_nCh>& t = *this;

	if ( _nID < t.size() )
	{
	fprintf_s( stderr, "%d\t", t[_nID].nF );
	}
	else
	{
		fprintf_s( stderr, "\t" );
	}

	for ( unsigned nI = 0; nI < _nCh; ++nI )
	{
		if ( _nID < t.size() )
		{
			fprintf_s( stderr, "%.10f\t", t[_nID][nI] );
		}
		else
		{
			fprintf_s( stderr, "\t" );
		}
	}
	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::debugMatrix( const MMatrix& _m, const char* _msg ) const
{
	fprintf_s( stderr, "---<%s>---\n", _msg );
	for ( unsigned nI = 0; nI < 4; ++nI )
	{
		for ( unsigned nJ = 0; nJ < 4; ++nJ )
		{
			fprintf_s( stderr, "%+f ", _m[nI][nJ] );
		}
		fprintf_s( stderr, "\n" );
	}
	return MS::kSuccess;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void h6export::writeError( const char* pszFormat, ... ) const
{
	static char charBuff[16384] = { '\0' };
	va_list va;
	va_start( va, pszFormat );
	_vsnprintf_s( charBuff, 16384 - 1, pszFormat, va );
	va_end( va );

	displayError( MString( charBuff ) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
