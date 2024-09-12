#include "H6EX.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::skel()
{
// 	MObject moRoot;
// 	slList.getDependNode( 0, moRoot );	
// 
// 	if ( moRoot.apiType() != MFn::kJoint )
// 	{
// 		displayError( "Non-joint root selected." );
// 		return MS::kFailure;
// 	}
// 
// 	// Gather joints skipping end ones
// 	MDagPathArray dpA;
// 	dpA.clear();
// 
// 	MItDag itDAG;
// 	itDAG.reset( moRoot, MItDag::kBreadthFirst, MFn::kJoint );
// 	for ( ; !itDAG.isDone(); itDAG.next() )
// 	{
// 		MDagPath dp;
// 		itDAG.getPath( dp );
// 
// 		if ( isEndJoint( dp ) )
// 		{
// 			continue;
// 		}
// 
// 		dpA.append( dp );
// 	}

	SIGN = skelSIGN;

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

  // Get Joints
  MDagPathArray dpA;
  MDagPathArray realJoints;
  MFnSkinCluster mfSkin( moSkin );

  FillDagPaths( mfSkin, dpA, realJoints );

  // Build joints' index
	if ( indexDAG( dpA ) != MS::kSuccess )
	{
		displayError( "Joints index building failed." );
		return MS::kFailure;
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::indexDAG( const MDagPathArray &_dpA )
{
	// skeleton will be sorted by exportID on return
	
	// Fill 
	skeleton.clear();

	unsigned nMinLevel = 0xFFFFFFFF; // For non-top level compensation
	for ( unsigned nI = 0; nI < _dpA.length(); ++nI )
	{											 
		DAGjoint j;

		MStringArray tmp;
		_dpA[nI].fullPathName().split( '|', tmp );
		j.level = tmp.length() - 1;
		j.name = _dpA[nI].partialPathName().asChar();
		j.fullName = _dpA[nI].fullPathName().asChar();
		j.mayaID = nI;
		j.dp = _dpA[nI];
		j.exportID = 0xFFFFFFFF;
		j.parentID = 0xFFFFFFFF;

		if ( j.level < nMinLevel )
		{
			nMinLevel = j.level;
		}

		skeleton.push_back( j );
	}

	// Compensate non-top level and fill matrices
	for ( unsigned nI = 0; nI < skeleton.size(); ++nI )
	{
		skeleton[nI].level -= nMinLevel;
		skeleton[nI].m = getMatrix( nI ) * mSys;

		// This does not work properely on multiple skins. 
		// bindPose changes with each new mesh binded.
		//// Store bind pose matrix
		//// bindPose plug contains last occured bind matrix
		//// or identity matrix	if there was no bind
		//MStatus status;
		//MFnTransform mf( skeleton[nI].dp.node() );
		//MPlug mp = mf.findPlug( MString( "bindPose" ));
		//MObject mo;
		//mp.getValue( mo );
		//MFnMatrixData mfMD( mo );
		//skeleton[nI].mBind = mfMD.matrix().inverse();

		skeleton[nI].mBind = skeleton[nI].dp.inclusiveMatrix().inverse();
	}

	// Build export index																					 
	std::sort( skeleton.begin(), skeleton.end(), sort_hierarchy_by_name() );

	for ( unsigned nI = 0; nI < skeleton.size(); nI++ )
	{
		skeleton[nI].exportID = nI;
	}

	// Build parent index
	for ( unsigned nI = 0; nI < skeleton.size(); nI++ )
	{
		if ( skeleton[nI].level == 0 )
		{
			skeleton[nI].parentID = 0xFFFFFFFF;
			continue;
		}

		// Get parent fullName from fullName
		unsigned n = unsigned( skeleton[nI].fullName.find_last_of( "|" ) );
		std::string sParent = skeleton[nI].fullName.substr( 0, n );

		// Find parent to get index
		itSkeleton = std::find( skeleton.begin(), skeleton.end(), sParent );
		if ( itSkeleton == skeleton.end() )
		{
			writeError( "No parent for %s\n", skeleton[nI].fullName.data() );
			return MS::kFailure;
		}

		skeleton[nI].parentID = (*itSkeleton).exportID;
	}

	return MS::kSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MMatrix h6export::getMatrix( const unsigned &_nID )
{
	MDagPath dp = skeleton[_nID].dp;
	MMatrix mResult;

  // Hierarchical bone placements
  if ( skeleton[_nID].level == 0 )
	{
		// World space for root
		mResult = dp.inclusiveMatrix();		
	}
	else
	{
		// Local for others
		MMatrix m1 = dp.inclusiveMatrix();
		MMatrix m2 = dp.exclusiveMatrixInverse();
		mResult = m1 * m2;
	}

  // Absolute bone placements
  //mResult = dp.inclusiveMatrix();		

	return mResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool h6export::isEndJoint( const MDagPath& _dp ) const
{
	bool bEndJoint = true;
	for ( unsigned nI = 0; nI < _dp.childCount(); ++nI )
	{
		if ( _dp.child( nI ).apiType() == MFn::kJoint )
		{
			bEndJoint = false;
			break;
		}
	}

	return bEndJoint;
}