#include "../commandClasses.h"
#include "BNFL.h"

MStatus bindFile::writerBlind(
	MObject mesh,
	MDagPathArray jointPaths, 
	MIntArray vertexIDs, 
	std::vector<MFloatArray> weightsVector)
{
	unsigned signature = SIGNATUREBLIND;
	MStatus stat = MS::kFailure;

	// Build array for string blind data
	MStringArray data;
	MDoubleArray dataD;
	data.clear();
	dataD.clear();
	for ( unsigned i = 0; i < vertexIDs.length(); ++i )
	{
		MString tmp = "";
		for ( unsigned j = 0; j < jointPaths.length(); ++j )
		{
			// Ignore small weights
			if ( weightsVector[i][j] < tolerance )
			{
				continue;
			}
			
			tmp += jointPaths[j].partialPathName()	+ " "	+ weightsVector[i][j]	+ " ";
		}

		data.append( tmp );
		dataD.append( 1.23 );
	}

//------------------------
	displayError("Hello!\n");
	MSelectionList sl;
	sl.clear();
	sl.add( "pCubeShape1" );
	sl.getDependNode( 0, mesh );

	MFnMesh meshFn( mesh );
	int blindDataID = 60;
	if (!meshFn.isBlindDataTypeUsed(blindDataID, &stat))
	{
		MStringArray longNames, shortNames, formatNames;
		
		longNames.append("red_color");
		shortNames.append("red");
		formatNames.append("double");

		longNames.append("green");
		shortNames.append("grn");
		formatNames.append("double");
		
		longNames.append("blue_color");
		shortNames.append("blue");
		formatNames.append("double");

		stat = meshFn.createBlindDataType(
			blindDataID, longNames, shortNames, formatNames );
		if (!stat) return stat;
	}
	else if (!stat) return stat;

	// Iterate through the mesh vertices and assign to each some
	// color value that is related to the height of the vertex
	// so that it goes from dark blue at the lowest point to
	// white at the highest..
	//
	// Find the lowest and the highest points.
	//
	MItMeshVertex itVertex(mesh);
	double lowest = 1e10, highest = -1e10;
	for ( ; !itVertex.isDone(); itVertex.next() )
	{
		MPoint vertexPosition = itVertex.position();
		double height = vertexPosition[1];
		if (height < lowest) lowest = height;
		if (height > highest) highest = height;
	}

	double range = highest - lowest;
	for ( itVertex.reset(mesh); !itVertex.isDone(); itVertex.next() )
	{
		MPoint vertexPosition = itVertex.position();
		double height = vertexPosition[1] - lowest;
		double red, green, blue;

		// Calculate the interpolated color for each vertex
		// using its relative height
		//
		red = 2.0 * ( height / range ) - 1.0;
		if (height > range/2.0) {
			if (red < 0.7) green = 0.7;
			else green = red;
		}
		else green = 0.7 * (1.0 - (((range/2.0) - height) / (range/2.0))
			* (((range/2.0) - height) / (range/2.0)));
		if (height > range/2.0) blue = red;
		else blue = 1.0 - (green*green);
		if (red < 0.0) red = 0.0;

		// Set the color values in the blind data
		//
		stat = meshFn.setDoubleBlindData(itVertex.index(),
			MFn::kMeshVertComponent, blindDataID, "red", red);
		if (!stat) return stat;
		stat = meshFn.setDoubleBlindData(itVertex.index(),
			MFn::kMeshVertComponent, blindDataID, "green", green);
		if (!stat) return stat;
		stat = meshFn.setDoubleBlindData(itVertex.index(),
			MFn::kMeshVertComponent, blindDataID, "blue", blue);
		if (!stat) return stat;
	}

	return stat;
//------------------------
	
/*
	// Check for possible blindData existance. Create one if none exists
	MFnMesh meshFn( mesh );
	if ( !meshFn.isBlindDataTypeUsed( SIGNATUREBLIND, &stat) )
	{
		MStringArray longNames;
		MStringArray shortNames;
		MStringArray formatNames;

		longNames.clear();
		shortNames.clear();
		formatNames.clear();

		longNames.append( ATTRLONGNAME );
		shortNames.append( ATTRSHORTNAME );
		formatNames.append( "string" );

		stat = meshFn.createBlindDataType(
			SIGNATUREBLIND,
			longNames,
			shortNames,
			formatNames );

		//if (!stat)
		{
			//return stat;
		}
	}

	return meshFn.setStringBlindData( 
		vertexIDs, 
		MFn::kMeshVertComponent, 
		SIGNATUREBLIND, 
		ATTRLONGNAME, 
		data );
*/
}