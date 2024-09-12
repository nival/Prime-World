#include "HLWD.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus helloWorld::doIt ( const MArgList &args )
{
	MStatus stat = MS::kSuccess;

	MSelectionList slList;
	MGlobal::getActiveSelectionList( slList);

	MGlobal::executeCommand( "shadingNode -asTexture file", false, true );
	
	MSelectionList slNew;
	MGlobal::getActiveSelectionList( slNew );
	
	MGlobal::setActiveSelectionList( slList );
	
	MObject moF;
	slNew.getDependNode( 0, moF );
	MFnDependencyNode fnF( moF );

	MPlug plOut = fnF.findPlug( MString( "outColorR" ), &stat );
	MPlug plFile = fnF.findPlug( MString( "fileTextureName" ), &stat );
	MPlug plU = fnF.findPlug( MString( "uCoord" ), &stat );
	MPlug plV = fnF.findPlug( MString( "vCoord" ), &stat );

	stat = plFile.setValue( MString( "d:/terrace_HMP.tga" ) );
	stat = plU.setValue( 0.0 );
	stat = plV.setValue( 0.5 );

	float fTmp = plOut.asFloat();
	fprintf_s( stderr, "%f\n", fTmp );

	MImage mi;
	mi.readFromFile( "d:/_.tga", MImage::kFloat );

	unsigned x;
	unsigned y;
	mi.getSize( x, y );
	fprintf_s( stderr, "%dx%d\n", x, y );

	float* pPx = mi.floatPixels();
	for ( unsigned nI = 0; nI < 16; ++nI )
	{
		fprintf_s( stderr, "%f\n", *(pPx++) );
	}

	return redoIt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus	helloWorld::redoIt()
{
	return dgMod.doIt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus	helloWorld::undoIt()
{
	return dgMod.undoIt();
}
