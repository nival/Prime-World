#include "../commandClasses.h"
#include "BNFL.h"

MStatus bindFile::writerIDX(	MString						filename,
					MDagPathArray				jointPaths, 
					MIntArray					vertexIDs, 
					std::vector<MFloatArray>	weightsVector)
{
	FILE* file;

	fopen_s( &file, filename.asChar(), "wb" );
	if ( file == NULL )
	{
		fprintf(stderr, "writer: Cannot open file %s!\n", filename.asChar());
		return MS::kFailure;
	}

	unsigned signature = SIGNATUREIDX;
	fwrite( &signature, sizeof(signature), 1, file );
	
	unsigned jointCount = jointPaths.length();
	fwrite( &jointCount, sizeof(jointCount), 1, file );
	
	unsigned vertexCount = vertexIDs.length();
	fwrite( &vertexCount, sizeof(vertexCount), 1, file );

	unsigned i;
	for( i = 0; i < jointCount; i++ )
	{
		MString path = jointPaths[i].fullPathName();
		unsigned size = path.length();
		fwrite( &size, sizeof(size), 1, file );		
		fwrite( path.asChar(), size, 1, file );
	}

	for( i = 0; i < vertexCount; i++ )
		fwrite( &vertexIDs[i], sizeof(vertexIDs[i]), 1, file );

	for( i = 0; i < vertexCount; i++ )
		for( unsigned j = 0; j < jointCount; j++ )
			fwrite( &weightsVector[i][j], sizeof(weightsVector[i][j]), 1, file );		

	fclose( file );

	return MS::kSuccess;
}