#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::stat()
{
	SIGN = statSIGN;

	// Get mesh
	slList.getDependNode( 0, moMesh );

	if ( !moMesh.hasFn( MFn::kMesh ))
	{
		displayError( "Mesh export works only on objects of type mesh." );
		return MS::kFailure;
	}

	// Create function set FROM DAG PATH!!! (to make kWorld work correctly )
	MDagPath dp;
	slList.getDagPath( 0, dp );
	MFnMesh mfMesh( dp );

	nUVsets = mfMesh.numUVSets();
	if ( nUVsets < 1 )
	{
		displayError( "No UV sets found." );
		return MS::kFailure;
	}

	if ( nUVsets > 4 )
	{
		// Accept only first 4
		nUVsets = 4;
	}

	MStringArray UVsetNames;
	mfMesh.getUVSetNames( UVsetNames );

	MObjectArray materials;
	MIntArray faceMaterialIDs;
	MStatus status = mfMesh.getConnectedShaders( 0, materials, faceMaterialIDs );

	if ( status == MS::kFailure )
	{
		displayError( "Cannot get shaders." );
		return MS::kFailure;
	}

	nMaterials = materials.length();

	if ( nMaterials < 1 )
	{
		displayError( "No materials assigned to mesh." );
		return MS::kFailure;
	}

	// Sort materials by name
	//sortMaterials( materials, faceMaterialIDs );

	faceMaterials.resize( nMaterials );

	// Storage for colors
	MColor mcDefault( 1.0f, 1.0f, 1.0f, 1.0f );
	MColorArray vertexColors;
	status = mfMesh.getVertexColors( vertexColors, 0, &mcDefault );
	if ( status == MS::kFailure )
	{
		//displayWarning( "Cannot get vertex colors. Assuming default color." );
		vertexColors = MColorArray( mfMesh.numVertices(), mcDefault );
	}

	// Iterate through faces
	std::vector<exportVertex> allVertices;
	allVertices.clear();

	MItMeshPolygon itFace( dp );
	for ( ; !itFace.isDone(); itFace.next() )
	{
		faceMaterials[ faceMaterialIDs[itFace.index()] ].append( itFace.index() );

		MIntArray faceVertices;
		itFace.getVertices( faceVertices );

		if ( faceVertices.length() != 3 )
		{
			displayError( "Mesh should be triangulated before export." );
			return MS::kFailure;
		}

		// Iterate through face vertices
		for ( unsigned nI = 0; nI < faceVertices.length(); ++nI )
		{
			exportVertex vertex( nUVsets );

			vertex.mayaID = itFace.vertexIndex( nI );
			vertex.normalID = itFace.normalIndex( nI );
			vertex.uvIDs.clear();
			for ( unsigned nJ = 0; nJ < nUVsets; ++nJ )
			{
				int ID;
				MStatus status;
				status = itFace.getUVIndex( nI, ID, &UVsetNames[nJ] );
				if ( status != MS::kSuccess )
				{
					displayError( "Getting UVIndex failed." );
					return MS::kFailure;
				}

				vertex.uvIDs.push_back( ID );
			}

			// Position
			MPoint p;
			mfMesh.getPoint( faceVertices[nI], p, MSpace::kWorld );
			vertex.x = float( p.x );
			vertex.y = float( p.y );
			vertex.z = float( p.z );

			// Color
			//int nColorID;
			//mfMesh.getColorIndex( itFace.index(), nI, nColorID );
			
			MColor c = vertexColors[faceVertices[nI]];
			//mfMesh.getColor( nColorID, c, 0, &MColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
			vertex.r = float( c.r );
			vertex.g = float( c.g );
			vertex.b = float( c.b );
			vertex.a = float( c.a );

			// Normal
			MVector v;
			mfMesh.getFaceVertexNormal( itFace.index(), faceVertices[nI], v, MSpace::kWorld );
			vertex.nx = float( v.x );
			vertex.ny = float( v.y );
			vertex.nz = float( v.z);

			// Tangent
			mfMesh.getFaceVertexTangent( itFace.index(), faceVertices[nI], v, MSpace::kWorld );
			vertex.tx = float( v.x );
			vertex.ty = float( v.y );
			vertex.tz = float( v.z );

			// Binormal
			mfMesh.getFaceVertexBinormal( itFace.index(), faceVertices[nI], v, MSpace::kWorld );
			vertex.bx = float( v.x );
			vertex.by = float( v.y );
			vertex.bz = float( v.z );

			// UVs
			vertex.u.clear();
			vertex.v.clear();
			for ( unsigned nJ = 0; nJ < nUVsets; ++nJ )
			{
				float fU;
				float fV;
				mfMesh.getPolygonUV( itFace.index(), nI, fU, fV, &UVsetNames[nJ] );
				vertex.u.push_back( fU );
				vertex.v.push_back( fV );
			}

			// Store vertex ID itself
			vertex.ID = unsigned( allVertices.size() );

			allVertices.push_back( vertex );
		}
	}

	// Build unique vertex array and face index
	std::sort( allVertices.begin(), allVertices.end() );

	faces.setLength( unsigned( allVertices.size() ) );

	// Fill the first one
	vertices.clear();
	vertices.push_back( allVertices[0] );
	faces[allVertices[0].ID] = 0;

	// Fill others starting from the second one, testing it with previous
	unsigned nUniqueID = 0;
	for ( unsigned nI = 1; nI < allVertices.size(); ++nI )
	{
		if ( allVertices[nI] != allVertices[nI-1] )
		{
			vertices.push_back( allVertices[nI] );
			faces[allVertices[nI].ID] = ++nUniqueID;
		}
		else
		{
			faces[allVertices[nI].ID] = nUniqueID;
		}
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::sortMaterials( const MObjectArray& _moA, MIntArray& _IDs )
{
	// Replace indexes in _IDs by sorted-by-names ones

	// Using DAGjoint since it already has all we need
	std::vector<DAGjoint> index;
	for ( unsigned nI = 0; nI < _moA.length(); ++nI )
	{
		MFnDependencyNode fnDn( _moA[nI] );
		DAGjoint dj;
		dj.level = 0;
		dj.name = fnDn.name().asChar();
		dj.mayaID = nI;
		index.push_back( dj );
	}

	std::sort( index.begin(), index.end(), sort_hierarchy_by_name() );

	for ( unsigned nI = 0; nI < index.size(); ++nI )
	{
		index[nI].exportID = nI;
	}

	std::sort( index.begin(), index.end(), sort_by_mayaID() );

	for ( unsigned nI = 0; nI < _IDs.length(); ++nI )
	{
		_IDs[nI] = index[ _IDs[nI] ].exportID;
	}

	return MS::kSuccess;
}
