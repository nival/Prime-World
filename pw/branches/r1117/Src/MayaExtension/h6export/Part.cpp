#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::part()
{
	SIGN = partSIGN;

	MStatus stat;

	MObjectArray PObjects;

	for ( unsigned nP = 0; nP < slList.length(); ++nP )
	{
		MDagPath dpTransform;
		slList.getDagPath( nP, dpTransform );
		for ( unsigned j = 0; j < dpTransform.childCount(); ++j )
		{
			if ( dpTransform.child(j).apiType() == MFn::kParticle )
			{
				PObjects.append( dpTransform.child(j) );
			}
		}
	}

	if ( PObjects.length() == 0 )
	{
		displayError( "No particles in selection." );
		return MS::kFailure;
	}

	MGlobal::executeCommand( "cycleCheck -e off" );

	int nMaxFrame, nMinFrame;
	MGlobal::executeCommand( "playbackOptions -q -max", nMaxFrame );
	MGlobal::executeCommand( "playbackOptions -q -min", nMinFrame );

	unsigned nFrames = unsigned( nMaxFrame - nMinFrame + 1 );
	unsigned nPObjects = PObjects.length();
	
	// Gather raw data
	for ( unsigned nF = 0; nF < nFrames; ++nF )
	{
		MGlobal::viewFrame( nF + nMinFrame );
		for ( unsigned nO = 0; nO < nPObjects; ++nO )
		{
			MObject oTmp;
			MFnDagNode nodeFn;
			nodeFn.setObject( PObjects[nO] );

			// Get particles count
			MPlug plug = nodeFn.findPlug( MString("count"), &stat );
			int nTmp;
			stat = plug.getValue( nTmp );
			unsigned nParticles = unsigned( nTmp );
			if ( nParticles <= 0 )
			{
				continue;
			}

			// Get id mappings and indexes
			plug = nodeFn.findPlug( MString("idMapping"), &stat );

			std::vector<unsigned> sortedId, idIndex;
			sortedId.resize( nParticles );
			idIndex.resize( nParticles );

			MPlug chPlug = plug.child(0);
			stat = chPlug.getValue(oTmp);
			{
				MFnIntArrayData tmpi(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					sortedId[nP] = tmpi[nP];
				}
			}

			chPlug = plug.child(1);
			stat = chPlug.getValue(oTmp);
			{
				MFnIntArrayData tmpi(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					idIndex[nP] = tmpi[nP];
				}
			}

			// Get data for current frame
			struct tmpP // Temporary storage for 1 particle
			{
				float X;
				float Y;
				float Z;

				float sx;
				float sy;

				float twist;

				float R;
				float G;
				float B;
				float A;

				float sprite;
			};

			std::vector<tmpP> tmpPD( nParticles ); // Temporary storage for 1 particle object for current frame

			// World position
			plug = nodeFn.findPlug( MString("worldPosition"), &stat );
			stat = plug.getValue(oTmp);
			MFnVectorArrayData wpos(oTmp, &stat);
			for ( unsigned nP = 0; nP < nParticles; ++nP )
			{
				tmpPD[nP].X = float( wpos[idIndex[nP]].x );
				tmpPD[nP].Y = float( wpos[idIndex[nP]].y );
				tmpPD[nP].Z = float( wpos[idIndex[nP]].z );

				// Fill default values for others. Will be used if attributes not found
				tmpPD[nP].sx = 1.0f;
				tmpPD[nP].sy = 1.0f;

				tmpPD[nP].twist = 1.0f;

				tmpPD[nP].R = 1.0f;
				tmpPD[nP].G = 1.0f;
				tmpPD[nP].B = 1.0f;
				tmpPD[nP].A = 1.0f;

				tmpPD[nP].sprite = 0.0f;
			}

			// ScaleX
			plug = nodeFn.findPlug( MString("spriteScaleXPP"), &stat );
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnDoubleArrayData scaleX(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].sx = float( scaleX[idIndex[nP]] );
				}
			}

			// ScaleY
			plug = nodeFn.findPlug( MString("spriteScaleYPP"), &stat );
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnDoubleArrayData scaleY(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].sy = float( scaleY[idIndex[nP]] );
				}
			}

			// Twist
			plug = nodeFn.findPlug( MString("spriteTwistPP"), &stat );
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnDoubleArrayData rot(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].twist = float( rot[idIndex[nP]] * PI / 180 );
				}
			}

			// Color
			plug = nodeFn.findPlug( MString("rgbPP"), &stat );
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnVectorArrayData rgb(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].R = float( rgb[idIndex[nP]].x );
					tmpPD[nP].G = float( rgb[idIndex[nP]].y );
					tmpPD[nP].B = float( rgb[idIndex[nP]].z );
				}
			}

			// Opacity
			plug = nodeFn.findPlug(MString("opacityPP"),&stat);
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnDoubleArrayData opacity(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].A = float( opacity[idIndex[nP]] );
				}
			}

			// Sprite
			plug = nodeFn.findPlug( MString("spriteNumPP"), &stat );
			if ( stat == MS::kSuccess )
			{
				stat = plug.getValue(oTmp);
				MFnDoubleArrayData sprite(oTmp, &stat);
				for ( unsigned nP = 0; nP < nParticles; ++nP )
				{
					tmpPD[nP].sprite = float( sprite[idIndex[nP]] );
				}
			}

			// Update to hash_map
			for ( unsigned nP = 0; nP < nParticles; ++nP )
			{
				unsigned PID = ( nO << 24 ) + sortedId[nP];

				TVAnimKey<3> aK3;
				aK3.nF = nF;

				aK3.x = tmpPD[nP].X;
				aK3.y = tmpPD[nP].Y;
				aK3.z = tmpPD[nP].Z;
				partData[PID].pos.push_back( aK3 );

				aK3.x = tmpPD[nP].sx;
				aK3.y = tmpPD[nP].sy;
				aK3.z = tmpPD[nP].twist;
				partData[PID].scr.push_back( aK3 );

				TVAnimKey<4> aK4;
				aK4.nF = nF;
				aK4.r = tmpPD[nP].R;
				aK4.g = tmpPD[nP].G;
				aK4.b = tmpPD[nP].B;
				aK4.a = tmpPD[nP].A;
				partData[PID].col.push_back( aK4 );

				TVAnimKey<1> aK1;
				aK1.nF = nF;
				aK1.x = tmpPD[nP].sprite;
				partData[PID].spr.push_back( aK1 );
			}
		}
	}

	// Remove single-frame particles
	for ( hmPartData::iterator it = partData.begin(); it != partData.end();	it )
	{
		particle& P = it->second;
		if ( P.pos.size()	< 2 )
		{
			it = partData.erase( it );
			continue;
		}

		++it;
	}

	// Compress and get range values
	partObj.fDur = 0.0f;
	partObj.fFPS = 30.0f;
	partObj.nParticles = partData.size();

	for ( hmPartData::iterator it = partData.begin(); it != partData.end();	++it )
	{
		particle& P = it->second;

		P.pos.compress( fTolerance );
		P.scr.compress( fTolerance );
		P.col.compress( fTolerance );
		P.spr.compressStepped();

		P.nStart = P.pos.front().nF;
		P.nEnd = P.pos.back().nF;

		float fDur = ( P.nEnd + 1 ) / partObj.fFPS;
		if ( partObj.fDur < fDur )
		{
			partObj.fDur = fDur;
		}
	}

	return MS::kSuccess;
}