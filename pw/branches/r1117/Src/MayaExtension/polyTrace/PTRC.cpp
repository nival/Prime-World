#include "../commandClasses.h"

// Argument flags:
const char *PTRC_positionFlag	= "-p";
const char *PTRC_positionLongFlag = "-position";

const char *PTRC_directionFlag	= "-d";
const char *PTRC_directionLongFlag = "-direction";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MSyntax polyTrace::newSyntax()
{
	// Register arguments

	MSyntax syntax;

	syntax.addFlag( 
		PTRC_positionFlag, PTRC_positionLongFlag, 
		MSyntax::kDouble, MSyntax::kDouble, MSyntax::kDouble );

	syntax.addFlag( 
		PTRC_directionFlag, PTRC_directionLongFlag, 
		MSyntax::kDouble, MSyntax::kDouble, MSyntax::kDouble );

	syntax.setObjectType( MSyntax::kSelectionList, 1, 1 );
	syntax.useSelectionAsDefault();

	return syntax;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus polyTrace::doIt ( const MArgList &args )
{
	// Main

	clearResult();

	MStatus stat;

	// Set defaults
	
	// Ray start
	double fX = 0.0;
	double fY = 0.0;
	double fZ = 0.0;

	// Ray direction
	double fDx = 1.0;
	double fDy = 0.0;
	double fDz = 0.0;

	// Parse arguments
	MArgDatabase argData( syntax(), args, &stat );

	if ( stat != MS::kSuccess )
	{
		return MS::kFailure;
	}

	// Process flags
	if ( argData.isFlagSet( PTRC_positionFlag ))
	{
		argData.getFlagArgument( PTRC_positionFlag, 0, fX );
		argData.getFlagArgument( PTRC_positionFlag, 1, fY );
		argData.getFlagArgument( PTRC_positionFlag, 2, fZ );
	}

	if ( argData.isFlagSet( PTRC_directionFlag ))
	{
		argData.getFlagArgument( PTRC_directionFlag, 0, fDx );
		argData.getFlagArgument( PTRC_directionFlag, 1, fDy );
		argData.getFlagArgument( PTRC_directionFlag, 2, fDz );
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

	// Create function set
	MFnMesh mfMesh( moMesh );

	// Data for tracing
	MFloatPoint mfpPosition;
		mfpPosition.x = float(fX);
		mfpPosition.y = float(fY);
		mfpPosition.z = float(fZ);

	MFloatVector mfvDirection;
		mfvDirection.x = float(fDx);
		mfvDirection.y = float(fDy);
		mfvDirection.z = float(fDz);

	MIntArray miaFaceIDs;
	MIntArray miaTriIDs;
	bool isSorted = true;
	float fMaxParam = 10.0f;
	bool testBothDirections = true;
	MMeshIsectAccelParams accelerator;
	MFloatPoint mfpHit;
	float fHitRayParam = 0;
	int nHitFaceID = 0;
	int nHitTriID = 0;
	float fHitBary1 = 0;
	float fHitBary2 = 0;
	float fTolerance = 0.000001f;

	// Trace it!
	if ( !mfMesh.closestIntersection(
		mfpPosition,
		mfvDirection,
		NULL,
		NULL,
		NULL,
		MSpace::kTransform,//kWorld doesn't work for some unknown reason. 
		fMaxParam,
		testBothDirections,
		NULL,
		mfpHit,
		&fHitRayParam,
		&nHitFaceID,
		&nHitTriID,
		&fHitBary1,
		&fHitBary2,
		fTolerance,
		&stat ))
	{
		printf( "No hit!\n" );
		if ( stat == MS::kInvalidParameter )
		{
			printf( "Param error!\n" );
		}
	}

	appendToResult( nHitTriID );

/*
	appendToResult( mfpHit.x );
	appendToResult( mfpHit.y );
	appendToResult( mfpHit.z );
*/	
	printf( "polytrace: Hello World!\n" );
	
	return MS::kSuccess;
}
