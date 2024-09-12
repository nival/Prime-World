#include "../commandClasses.h"
#include "BNFL.h"

MStatus bindFile::reader(MString filename,
				 MFnSkinCluster skinCluster,
				 MDagPath meshPath,
				 MObject meshComponent,
				 double tolerance)
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
	if ( signature != SIGNATURE )
	{
		fprintf(stderr, "reader: File %s is not a valid bind file!\n", filename.asChar());
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

	MPointArray vertices;
	vertices.clear();
	
	for( i = 0; i < vertexCount; i++ )
	{
		MPoint vertex;
		fread( &vertex.x, sizeof(vertex.x), 1, file );
		fread( &vertex.y, sizeof(vertex.y), 1, file );
		fread( &vertex.z, sizeof(vertex.z), 1, file );
		vertices.append(vertex);
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
/*
	// Let's test vertices for sharing the same position
	bool fail = false;
	MItMeshVertex itVertex(meshPath, meshComponent);
	for( ; !itVertex.isDone(); itVertex.next() )
	{
		MPoint p1 = itVertex.position(MSpace::kWorld);
		int i1 = itVertex.index();
		MItMeshVertex itVertex1(meshPath, meshComponent);
		for( ; !itVertex1.isDone(); itVertex1.next() )
		{
			MPoint p2 = itVertex1.position(MSpace::kWorld);
			int i2 = itVertex1.index();
			if(i1 != i2)
				if(p1.isEquivalent( p2, tolerance))
				{
					fail = true;
					fprintf(stderr,"Share position: %f %f %f;\n", p1.x, p1.y, p1.z);
				}
		}
		
	}

	if (fail)
	{
		fprintf(stderr,"bindFile reader: Some vertices share the same position!\n");
		return MS::kFailure;
	}

	// Let's remember vertex positions
	MPointArray vertexBuffer;
	MItMeshVertex itVertex(meshPath, meshComponent);
	for( ; !itVertex.isDone(); itVertex.next() )
		vertexBuffer.append(itVertex.position(MSpace::kWorld));

	// Let's switch off normalize in skinCuster 
	// and zero weights for	selected vertices
	MFloatArray newComponentWeights;
	newComponentWeights.clear();
	itVertex.reset();
	for( ; !itVertex.isDone(); itVertex.next() )
		newComponentWeights.append(0);

	MDagPathArray influenceObjects;
	skinCluster.influenceObjects(influenceObjects, &stat);
	MIntArray indices;
	indices.clear();
	for(i = 0; i < influenceObjects.length(); i++)
		indices.append( skinCluster.indexForInfluenceObject(influenceObjects[i], &stat ) );

	skinCluster.setWeights( meshPath, meshComponent, indices, newComponentWeights, false);
*/
	// Let's find closest vertices in buffer to vertices
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
			MPoint meshVertex = itVertex.position( MSpace::kWorld );
			unsigned ind = itVertex.index( &stat );
			if( vertices[i].isEquivalent( meshVertex, tolerance) )
			{
				MSelectionList lst;
				lst.clear();
				lst.add( meshPath, itVertex.vertex(), true );
				
				MDagPath pth;
				MObject cmpt;
				lst.getDagPath( 0, pth, cmpt );
				skinCluster.setWeights( pth, cmpt, jointIndices, weightsVector[i], false);
			}
		}
	}
	return MS::kSuccess;
}