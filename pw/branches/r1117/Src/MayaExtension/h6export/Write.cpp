#include "H6EX.h"

#define FWRITE( smth ) writer->Write( &smth, sizeof(smth) );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::write()
{
	MStatus status = MS::kSuccess;

  writer = new FastWriter();

	// Write header
	FWRITE( SIGN );

	switch( SIGN )
	{
		case statSIGN:
		{
			status = writeMesh();
		}
		break;

		case skinSIGN:
		{
			status = writeMesh();
		}
		break;

		case skelSIGN:
		{
			status = writeSkel();
		}
		break;

		case animSIGN:
		{
			status = writeAnim();
		}
		break;

		case partSIGN:
		{
			status = writePart();
		}
		break;

		case lghtSIGN:
		{
			status = writeLght();
		}
		break;

		default:
			break;
	}

  fopen_s( &pFile, msFileName.asChar(), "wb" );
  if ( pFile == NULL )
  {
    displayError( "Open file for writing failed." );
    return MS::kFailure;
  }
  fwrite( writer->GetBuffer(), writer->GetSize(), 1, pFile );
	fclose( pFile );
	
  delete writer;

	if ( status != MS::kSuccess )
	{
		displayError( "Write to file failed." );
		return MS::kFailure;
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeMesh() const
{
	writeVertices();

	writeFaces();

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeVertices() const
{
	// Write header
	unsigned nBufferSize = vertices.size();
	FWRITE( nBufferSize );

	// Write vertex buffer
	for ( unsigned nI = 0; nI < vertices.size(); ++nI )
	{
		FWRITE( vertices[nI].x );
		FWRITE( vertices[nI].y );
		FWRITE( vertices[nI].z );

		FWRITE( vertices[nI].r );
		FWRITE( vertices[nI].g );
		FWRITE( vertices[nI].b );
		FWRITE( vertices[nI].a );

		FWRITE( vertices[nI].nx );
		FWRITE( vertices[nI].ny );
		FWRITE( vertices[nI].nz );

		FWRITE( vertices[nI].tx );
		FWRITE( vertices[nI].ty );
		FWRITE( vertices[nI].tz );

		FWRITE( vertices[nI].bx );
		FWRITE( vertices[nI].by );
		FWRITE( vertices[nI].bz );

		for ( unsigned nJ = 0; nJ < 4; ++nJ )
		{
			if ( nJ < nUVsets )
			{
				FWRITE( vertices[nI].u[nJ] );
				FWRITE( vertices[nI].v[nJ] );
			}
			else
			{
				float fTmp = 0.0;
				FWRITE( fTmp );
				FWRITE( fTmp );
			}
		}

		if ( SIGN == skinSIGN ) 
		{
			// Write weights
			for ( unsigned nJ = 0; nJ < nInfluences; ++nJ )
			{
				FWRITE( vertices[nI].w[nJ].value );
			}
			for ( unsigned nJ = 0; nJ < nInfluences; ++nJ )
			{
				FWRITE( vertices[nI].w[nJ].jointID );
			}
		}									 
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeFaces() const
{
	FWRITE( nMaterials );

	for ( unsigned nI = 0; nI < faceMaterials.size(); ++nI )
	{
		unsigned nFaces = faceMaterials[nI].length();
		FWRITE( nFaces );

		// Count unique vertices

		// Fill non-unique
		std::vector<int> vertexIDs;
		vertexIDs.clear();
		for ( unsigned nJ = 0; nJ < nFaces; ++nJ )
		{
				vertexIDs.push_back( faces[ faceMaterials[nI][nJ] * 3 ] );
				vertexIDs.push_back( faces[ faceMaterials[nI][nJ] * 3 + 1 ] );
				vertexIDs.push_back( faces[ faceMaterials[nI][nJ] * 3 + 2 ] );
		}

		// Make unique
		std::sort( vertexIDs.begin(), vertexIDs.end() );
		std::vector <int>::iterator vIter;
		std::vector <int>::iterator vIterEnd;
		vIterEnd = std::unique( vertexIDs.begin(), vertexIDs.end() );

		unsigned nUnique = 0;
		for ( vIter = vertexIDs.begin(); vIter < vIterEnd; vIter++ )
		{
			nUnique++;
		}

		FWRITE( nUnique );

		for ( unsigned nJ = 0; nJ < nFaces; ++nJ )
		{
			unsigned nTmp = 0;
			nTmp = faces[ faceMaterials[nI][nJ] * 3 ];
			FWRITE( nTmp );
			nTmp = faces[ faceMaterials[nI][nJ] * 3 + 1 ];
			FWRITE( nTmp );
			nTmp = faces[ faceMaterials[nI][nJ] * 3 + 2 ];
			FWRITE( nTmp );
		}
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeSkel() const
{
	unsigned nTmp = skeleton.size();
	FWRITE( nTmp );

	for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
	{
    writer->Write( skeleton[nI].name.data(), skeleton[nI].name.size() );

		// String terminator
		char c = 0;

		FWRITE( c );

		FWRITE( skeleton[nI].parentID );

		for ( unsigned nJ = 0; nJ < 3; ++nJ )
		{
			for ( unsigned nK = 0; nK < 4; ++nK )
			{
				float fTmp = float( skeleton[nI].mBind[nK][nJ] );
				FWRITE( fTmp );
			}
		}
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeAnim() const
{
	FWRITE( animType );

	unsigned nTmp = skeleton.size();
	FWRITE( nTmp );

	for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
	{
		animData[nI].pos.write( writer );
		animData[nI].rot.write( writer );
		animData[nI].scl.write( writer );
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writePart() const
{
	FWRITE( partObj.fDur );
	FWRITE( partObj.fFPS );
	FWRITE( partObj.nParticles );

	for ( hmPartData::const_iterator it = partData.begin(); it != partData.end();	++it )
	{
		const particle& P = it->second;

		FWRITE( P.nStart );
		FWRITE( P.nEnd );

		P.pos.write( writer );
		P.scr.write( writer );
		P.col.write( writer );
		P.spr.write( writer );
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::writeLght() const
{
	unsigned nTmp = lghtData.size();
	FWRITE( nTmp );

	for ( unsigned nI = 0; nI < lghtData.size(); ++nI )
	{
		lghtData[nI].pos.write( writer );
		lghtData[nI].radius.write( writer );
		lghtData[nI].col.write( writer );
	}

	return MS::kSuccess;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<unsigned _nCh> MStatus TVTrack<_nCh>::write( FastWriter* writer ) const
{
	const TVTrack<_nCh>& t = *this;

	unsigned nTmp = size();
	FWRITE( nTmp );
	for ( unsigned nI = 0; nI < nTmp; ++nI )
	{
		FWRITE( t[nI].nF );

		for ( unsigned nJ = 0; nJ < _nCh; ++nJ )
		{
			FWRITE( t[nI][nJ] );
		}
	}

	return MS::kSuccess;
}

#undef FWRITE
