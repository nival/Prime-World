#include "H6EX.h"

unsigned int GetExportId( const std::vector<DAGjoint>& skeleton, const MDagPathArray& realJoints, unsigned int idx )
{
  std::string realname = realJoints[idx].fullPathName().asChar();
  for ( unsigned int i = 0; i < skeleton.size(); i++ )
  {
    if ( realname == skeleton[i].fullName )
    {
      return skeleton[i].exportID;
    }
  }
  return idx;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::skin()
{
	// Get geometry data via static mesh export
  if ( vertices.empty() )
  {
	  if ( stat() != MS::kSuccess )
	  {
		  displayError( "Static mesh data gathering failed." );
		  return MS::kFailure;
	  }
  }

	SIGN = skinSIGN;

	// Let's find skinCluster, connected to moMesh.
	MItDependencyNodes iterDG(MFn::kSkinClusterFilter);
	MObject moSkin;
	for ( ; !iterDG.isDone(); iterDG.next() )
	{
		moSkin = iterDG.item();
		MFnSkinCluster mfSkin( moSkin );

		MObjectArray tmp;
		mfSkin.getOutputGeometry( tmp );

		if ( tmp[0] == moMesh )
		{
			break;
		}
	}

	if( moSkin.isNull() )
	{
		displayError( "No skinCluster connected to mesh." );
		return MS::kFailure;
	}

	MFnSkinCluster mfSkin( moSkin );
  MDagPathArray dpA;
  MDagPathArray realJoints;
  MStatus status;

  FillDagPaths( mfSkin, dpA, realJoints );
  unsigned nJoints = dpA.length();

	// Build joints' index
  if ( skeleton.empty() )
  {
	  if ( indexDAG( dpA ) != MS::kSuccess )
	  {
		  displayError( "Joints index building failed." );
		  return MS::kFailure;
	  }
  }

	// Re-index to match exportID<>mayaID
	std::sort( skeleton.begin(), skeleton.end(), sort_by_mayaID() );

	// Get raw weights of current joint
	MDagPath dp;
	slList.getDagPath( 0, dp );
	MItGeometry itG( dp );

	// Iterate through vertices
	unsigned vID = 0;
	for ( ; !itG.isDone(); itG.next() )
	{
		MObject moComponent = itG.currentItem();
		MDoubleArray rawWeights;
		status = mfSkin.getWeights( dp, moComponent, rawWeights, nJoints ); 

		// Fill all mayaID-shared vertices, which expected to be sorted
		while ( vertices[vID].mayaID == itG.index() )
		{
			vertices[vID].w.clear();
			for ( unsigned nI = 0; nI < rawWeights.length(); nI++ )
			{
				jointWeight jw = { float( rawWeights[nI] ), GetExportId( skeleton, realJoints, nI ) };
				vertices[vID].w.push_back( jw );
			}
			
			pruneWeights( vertices[vID].w );

			if ( ++vID == vertices.size() ) 
			{
				break;
			}
		}
	}

	//toBindPose();

  //debugOutputInfoVertices("c:/vertex.txt");

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::pruneWeights( std::vector<jointWeight> &_jW )
{
	std::sort( _jW.begin(), _jW.end(), sort_weights_desc() );
	_jW.resize( nInfluences );
	
	// Normalize
	float fSum = 0.f;
	for ( unsigned nI = 0; nI < _jW.size(); ++nI )
	{
		fSum += _jW[nI].value;
	}

	float f = 1.f / fSum;
	for ( unsigned nI = 0; nI < _jW.size(); ++nI )
	{
		_jW[nI].value *= f;
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::toBindPose()
{
	// Re-index skeleton to match exportIDs
	std::sort( skeleton.begin(), skeleton.end(), sort_hierarchy_by_name() );

	for ( unsigned nI = 0; nI < vertices.size(); ++nI )
	{
		MPoint p;
		p.x = vertices[nI].x;
		p.y = vertices[nI].y;
		p.z = vertices[nI].z;
		
		// Convert to bind pose
		MMatrix mResult;
		memset( &mResult, 0, sizeof( MMatrix ));
		for ( unsigned nJ = 0; nJ < nInfluences; ++nJ )
		{
			float fW = vertices[nI].w[nJ].value;
			if ( fW > fZero )
			{
				unsigned nJoint = vertices[nI].w[nJ].jointID;

				MDagPath dp = skeleton[nJoint].dp;
				MMatrix mJointWorld = dp.inclusiveMatrix();
				MMatrix mBindWorldInverse = skeleton[nJoint].mBind;
				MMatrix mInf = mBindWorldInverse * mJointWorld;
				mInf *= fW;
				mResult += mInf;
			}
		}
		
		mResult = mResult.inverse();
		p *= mResult;

		vertices[nI].x = float( p.x );
		vertices[nI].y = float( p.y );
		vertices[nI].z = float( p.z );
	}

	return MS::kSuccess;
}
