#include "../commandClasses.h"

//add arguments:
const char *MPFS_scaleUFlag	= "-su",	*MPFS_scaleULongFlag = "-scaleU";

MSyntax mapFaces::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag( MPFS_scaleUFlag, MPFS_scaleULongFlag, MSyntax::kDouble );

	syntax.setObjectType( MSyntax::kSelectionList, 1, 1 );
	syntax.useSelectionAsDefault( true );

	return syntax;
}

MStatus mapFaces::doIt ( const MArgList &args )
{
	MStatus stat = MS::kSuccess;

	double fX = 0.0;

	// Parse arguments
	MArgDatabase argData( syntax(), args, &stat );

	if ( stat != MS::kSuccess )
	{
		return MS::kFailure;
	}

	// Process flags
	if ( argData.isFlagSet( MPFS_scaleUFlag ))
	{
		argData.getFlagArgument( MPFS_scaleUFlag, 0, fX );	
	}

		// Get mesh
	MSelectionList slList;
	argData.getObjects( slList );
	
	MObject moMesh;
	slList.getDependNode( 0, moMesh );

	if ( !moMesh.hasFn( MFn::kMesh ))
	{
		displayError( "polyTrace: Found non-mesh object to operate on." );
		return MS::kFailure;
	}

	// Create function set FROM DAG PATH!!! (to make kWorld work correctly )
	MDagPath dp;
	slList.getDagPath( 0, dp );
	MFnMesh mfMesh( dp );

	mfMesh.clearUVs();

	MItMeshPolygon itFace( moMesh );
	unsigned int nUVid = 0;
	for ( ; !itFace.isDone(); itFace.next() )
	{
		// Get face normal
		MVector vFaceNormal;
		mfMesh.getPolygonNormal( itFace.index(), vFaceNormal, MSpace::kWorld );

		MVector vUp;
		vUp.x = 0;
		vUp.y = 0;
		vUp.z = 1;

		// Rotation normal to up for planar projection
		MQuaternion q( vFaceNormal, vUp );

		MMatrix m = q.asMatrix();

		MIntArray vertices;
		itFace.getVertices( vertices );
		for ( unsigned int nI = 0; nI < vertices.length(); ++nI )
		{
			MPoint p;
			mfMesh.getPoint( vertices[nI], p, MSpace::kWorld );

			MPoint pNew = p * m;

			float fU = float( pNew.x );
			float fV = float( pNew.y );
			mfMesh.setUV( nUVid, fU, fV );
			mfMesh.assignUV( itFace.index(), nI, nUVid );

			nUVid++;
		}
	}

	return redoIt();
}

MStatus	mapFaces::redoIt()
{
	return dgMod.doIt();
}

MStatus	mapFaces::undoIt()
{
	return dgMod.undoIt();
}
//===============================================================

