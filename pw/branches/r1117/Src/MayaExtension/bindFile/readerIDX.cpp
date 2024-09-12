#include "../commandClasses.h"
#include "BNFL.h"

MStatus bindFile::readerIDX(MString filename,
				 MFnSkinCluster skinCluster,
				 MDagPath meshPath,
				 MObject meshComponent)
{
	// First of all let's read all data from file.
	
	FILE* file;
	unsigned signature;
	MStatus stat;

	fopen_s( &file, filename.asChar(), "rb" );
	if ( file == NULL )
	{
		fprintf(stderr, "reader: Cannot open file %s\n", filename.asChar());
		return MS::kFailure;
	}

	fread( &signature, sizeof(signature), 1, file );
	if ( signature != SIGNATUREIDX )
	{
		fprintf(stderr, "reader: File %s is not a valid IDX bind file!\n", filename.asChar());
		return MS::kFailure;
	}

	unsigned jointCount;
	fread( &jointCount, sizeof(jointCount), 1, file );

	unsigned vertexCount;
	fread( &vertexCount, sizeof(vertexCount), 1, file );
	
	MDagPathArray jointPaths;
	jointPaths.clear();
	
	unsigned i;
	for( i = 0; i < jointCount; i++ )
	{
		unsigned size;
		fread( &size, sizeof(size), 1, file );		

		char* tmp = new char [size];
		fread( tmp, size, 1, file );
		MString path = "";
		path.set( tmp, size );
		delete[] tmp;
		
		MSelectionList list;
		list.clear();
		stat = list.add(path);
		if(stat != MS::kSuccess)
		{
			fprintf(stderr,"bindFile reader: Bind File contains wrong joint:\n%s\n\n", path.asChar());
			return MS::kFailure;
		}

		MDagPath dagPath;
		list.getDagPath(0, dagPath);
		jointPaths.append(dagPath);
	}

	MIntArray vertexIDs;
	vertexIDs.clear();
	
	for( i = 0; i < vertexCount; i++ )
	{
		unsigned vID;
		fread( &vID, sizeof(vID), 1, file );
		vertexIDs.append(vID);
	}

	std::vector<MFloatArray>	weightsVector;
	weightsVector.resize( vertexCount );
	for( i = 0; i < vertexCount; i++ )
		weightsVector[i].clear();
	
	for( i = 0; i < vertexCount; i++ )
		for( unsigned j = 0; j < jointCount; j++ )
		{
			float tmp;
			fread( &tmp, sizeof(tmp), 1, file );
			weightsVector[i].append(tmp);
		}

	fclose( file );

	// Let's build joint indices array
	MIntArray jointIndices;
	jointIndices.clear();

	for( i = 0; i < jointCount; i++ )
	{
		unsigned tmp = skinCluster.indexForInfluenceObject(jointPaths[i], &stat);
		if(stat != MS::kSuccess)
		{
			fprintf(stderr,"bindFile reader: No such joint:\n%s\nin %s\n", 
							jointPaths[i].fullPathName().asChar(),
							skinCluster.name().asChar());
			return MS::kFailure;
		}
		jointIndices.append(tmp);
	}

	// Let's find closest vertices in mesh to vertices
	// from file, arrange them as components and build weights array.
	MSelectionList targetList;
	targetList.clear();
	MFloatArray newComponentWeights;
	newComponentWeights.clear();
	for( i = 0; i < vertexCount; i++ )
	{
		MItMeshVertex itVertex(meshPath, meshComponent);
		for( ; !itVertex.isDone(); itVertex.next() )
		{
			unsigned vID = itVertex.index( &stat );
			if( vertexIDs[i] == vID )
			{
				targetList.add( meshPath, itVertex.vertex(), true );
				for( unsigned j = 0; j < weightsVector[i].length(); j++ )
					newComponentWeights.append( weightsVector[i][j] );
				break;
			}
		}
	}

	targetList.getDagPath( 0, meshPath, meshComponent );
	skinCluster.setWeights( meshPath, meshComponent, jointIndices, newComponentWeights, false);

	return MS::kSuccess;
}