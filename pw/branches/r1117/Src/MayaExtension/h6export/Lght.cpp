#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::lght()
{
	SIGN = lghtSIGN;
	MStatus stat;

	// Get selected and verify
	MDagPathArray dpA;
	MPlugArray paRadius;
	MPlugArray paR;
	MPlugArray paG;
	MPlugArray paB;
	for ( unsigned i = 0; i < slList.length(); ++i )
	{
		MDagPath dp;
		slList.getDagPath( i, dp);
		if ( dp.apiType() != MFn::kTransform )
		{
			continue;
		}

		MFnTransform fnT( dp.node() );

		MPlug plRadius = fnT.findPlug( "radius", &stat );
		if ( stat != MS::kSuccess )
		{
			continue;
		}

		MPlug plR = fnT.findPlug( "fxColorR", &stat );
		if ( stat != MS::kSuccess )
		{
			continue;
		}

		MPlug plG = fnT.findPlug( "fxColorG", &stat );
		if ( stat != MS::kSuccess )
		{
			continue;
		}

		MPlug plB = fnT.findPlug( "fxColorB", &stat );
		if ( stat != MS::kSuccess )
		{
			continue;
		}

		dpA.append( dp );

		paRadius.append( plRadius );
		
		paR.append( plR );
		paG.append( plG );
		paB.append( plB );
	}

	unsigned nLights = dpA.length();
	if ( nLights == 0 )
	{
		displayError( "No valid FX light transforms in selection." );
		return MS::kFailure;
	}

	lghtData.resize( nLights );

	MGlobal::executeCommand( "cycleCheck -e off" );

	int nMaxFrame, nMinFrame;
	MGlobal::executeCommand( "playbackOptions -q -max", nMaxFrame );
	MGlobal::executeCommand( "playbackOptions -q -min", nMinFrame );

	for ( int nFrame = nMinFrame; nFrame <= nMaxFrame; ++nFrame )
	{
		MGlobal::viewFrame( nFrame );

		for ( unsigned nI = 0; nI < dpA.length(); ++nI )
		{
			TVAnimKey<3> aK3;
			aK3.nF = nFrame;

			MMatrix mx = dpA[nI].inclusiveMatrix();

			aK3.x = float( mx.matrix[3][0] );
			aK3.y = float( mx.matrix[3][1] );
			aK3.z = float( mx.matrix[3][2] );
			lghtData[nI].pos.push_back( aK3 );

			TVAnimKey<1> aK1;
			aK1.nF = nFrame;
			stat = paRadius[nI].getValue( aK1.r );
			lghtData[nI].radius.push_back( aK1 );

			stat = paR[nI].getValue( aK3.r );
			stat = paR[nI].getValue( aK3.g );
			stat = paR[nI].getValue( aK3.b );
			lghtData[nI].col.push_back( aK3 );
		}
	}

	for ( unsigned nI = 0; nI < lghtData.size(); ++nI )
	{
		lghtData[nI].pos.compress( fTolerance );
		lghtData[nI].radius.compress( fTolerance );
		lghtData[nI].col.compress( fTolerance );
	}

	return MS::kSuccess;
}

