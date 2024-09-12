//
// Copyright (C) 2001 Nival Interactive 
// 
// File: bindFile.cpp
//
// MEL UndoRedoCommand: bindFile
//
// Author: Andrew Chernyshov
//

#include "../commandClasses.h"
#include "BNFL.h"

MStatus bindFile::doIt( const MArgList &args )
//
//	Description:
//		implements the MEL bindFile command.
//
//	Arguments:
//		args - the argument list that was passes to the command from MEL
//		
//	Syntax: bindFile <string mode> <string file>
//
//			mode - == "-r"	- read skinCluster from file
//					 == "-w"	- write skinCluster to file
//
//	Return Value:
//		MS::kSuccess - command succeeded
//		MS::kFailure - command failed (returning this value will cause the 
//										 MEL script that is being run to terminate unless the
//										 error is caught using a "catch" statement.
//
{
	MStatus stat = MS::kSuccess;

	// Since this class is derived off of MPxCommand, you can use the 
	// inherited methods to return values and set error messages
	
	
	// Getting selectionList
	MSelectionList selection;
 	MGlobal::getActiveSelectionList( selection );
	if ( selection.length() != 1 )
	{
		displayError("bindFile: Wrong number of selected objects!\n");
		return MS::kFailure;
	}

	MDagPath meshPath;
	MObject meshComponent;
	selection.getDagPath( 0, meshPath, meshComponent );
	if ( meshComponent.apiType() != MFn::kMeshVertComponent )
	{
		displayError("bindFile: Only mesh vertices should be selected!\n");
		return MS::kFailure;
	}
	MObject meshObject;
	selection.getDependNode( 0, meshObject );
	
	// Let's find skinCluster, connected to selected meshObject.
	MObject skinClusterObject;
	MItDependencyNodes iterDG(MFn::kSkinClusterFilter);
	int foundFlag = 0;
	for ( ; !iterDG.isDone(); iterDG.next() )
	{
		skinClusterObject = iterDG.item();
		MFnSkinCluster cluster( skinClusterObject, &stat );

		MObjectArray meshObjectArray;
		cluster.getOutputGeometry( meshObjectArray );

		if ( meshObjectArray[0] == meshObject )
		{
			foundFlag = 1;
			break;
		}
	}

	if( foundFlag == 0)
	{
		displayError("bindFile: No skinCluster connected to selected mesh!\n");
		return MS::kFailure;
	}

	MFnSkinCluster skinCluster( skinClusterObject, &stat );
	MFnMesh mesh( meshObject );
	
	// Parse the arguments.
	//
	if (args.length() < 3 )
	{
		displayError("Bad number of arguments passed to bindFile command!\n");
		return MS::kFailure;
	}

	int IDmode = args.asInt( 0, &stat );
	
	MString mode = args.asString( 1, &stat );
	if ( (mode != MString("-r")) && (mode != MString("-w")) )
	{
		displayError("bindFile: Invalid file mode specified!\n");
		return MS::kFailure;
	}


	MString filename = args.asString( 2, &stat );
	tolerance = 1e-4;
	if( args.length() == 4 )
	{
		tolerance = args.asDouble( 3, &stat );
		if ( stat != MS::kSuccess)
		{
			displayError("bindFile: Bad tolerance value!\n");
			return MS::kFailure;
		}	
	}

	// End of parsing arguments
	//
	// mesh - mesh
	// meshPath - meshPath
	// meshComponent - vertices
	//
	// skinCluster - skinCluster
	//
	// mode - read/write;
	// filename - filename;

	MDagPathArray jointPaths;
	skinCluster.influenceObjects( jointPaths, &stat );
	
	MPointArray vertices;
	MIntArray vertexIDs;
	std::vector <MFloatArray> weightsVector;
	
	MItMeshVertex itVertex(meshPath, meshComponent);
	weightsVector.resize( itVertex.count() );
	unsigned i = 0;
	for( ; !itVertex.isDone(); itVertex.next() )
	{
		// Let's get vertex world position
		vertices.append( itVertex.position(MSpace::kWorld) );
		vertexIDs.append( itVertex.index( &stat ) );

		// Let's get vertex weights
		MObject vertex = itVertex.vertex( &stat );
		unsigned count;
		MFloatArray vertexWeights;
		skinCluster.getWeights(meshPath, vertex, vertexWeights, count);

		weightsVector[i++] = vertexWeights;
	}
	
	if( mode == MString("-w") )
	{
		switch (IDmode)
		{
			case 0:
			{
				stat = writer(filename, jointPaths, vertices, weightsVector);
				break;
			}
			case 1:
			{
				stat = writerIDX(filename, jointPaths, vertexIDs, weightsVector);
				break;
			}
			case 2:
			{
				stat = writerBlind(meshObject, jointPaths, vertexIDs, weightsVector);
				break;
			}
			default:
			{
				break;
			}
		}

		if( stat != MS::kSuccess )
		{
			displayError("bindFile: writer has failed!\n");
			return MS::kFailure;
		}
	}
	else
	{
		if (IDmode)
			stat = readerIDX(filename, skinCluster, meshPath, meshComponent);
		else
			stat = reader(filename, skinCluster, meshPath, meshComponent, tolerance);

		if( stat != MS::kSuccess )
		{
			displayError("bindFile: reader has failed!\n");
			return MS::kFailure;
		}
	}

	setResult( "bindFile command executed!\n" );

	return redoIt();
}

MStatus	bindFile::redoIt()
{
	return dgMod.doIt();
}

MStatus	bindFile::undoIt()
{
	return dgMod.undoIt();
}
