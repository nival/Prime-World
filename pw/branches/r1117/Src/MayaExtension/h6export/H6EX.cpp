#include "H6EX.h"

//add arguments:

// Filename to export
const char *H6EX_fileNameFlag	= "-f";
const char *H6EX_fileNameLongFlag = "-file";

// Type of export - static mesh, skeletal mesh, skeleton, animation, etc
const char *H6EX_typeFlag	= "-t";
const char *H6EX_typeLongFlag = "-type";

const char *H6EX_bFlag	= "-lof";
const char *H6EX_bLongFlag = "-lofik";

// Number of influences per vertex to export 
const char *H6EX_influenceFlag	= "-ic";
const char *H6EX_influenceLongFlag = "-influenceCount";

// Export translation? 
const char *H6EX_animTFlag	= "-at";
const char *H6EX_animTLongFlag = "-animateTranslation";

// Export rotation? 
const char *H6EX_animRFlag	= "-ar";
const char *H6EX_animRLongFlag = "-animateRotation";

// Export scale? 
const char *H6EX_animSFlag	= "-as";
const char *H6EX_animSLongFlag = "-animateScale";

// Compression tolerance, % 
const char *H6EX_toleranceFlag	= "-ct";
const char *H6EX_toleranceLongFlag = "-compressionTolerance";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
h6export::h6export()
{
	// Obsolete since coordinate transform moved to engine
	const float m[4][4] = 
	{	
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	mSys = MMatrix( m );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MSyntax h6export::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag( H6EX_fileNameFlag, H6EX_fileNameLongFlag, MSyntax::kString );
	syntax.addFlag( H6EX_typeFlag, H6EX_typeLongFlag, MSyntax::kString );
  syntax.addFlag( H6EX_bFlag, H6EX_bLongFlag, MSyntax::kString );
	syntax.addFlag( H6EX_influenceFlag, H6EX_influenceLongFlag, MSyntax::kUnsigned );
	syntax.addFlag( H6EX_animTFlag, H6EX_animTLongFlag, MSyntax::kNoArg );
	syntax.addFlag( H6EX_animRFlag, H6EX_animRLongFlag, MSyntax::kNoArg );
	syntax.addFlag( H6EX_animSFlag, H6EX_animSLongFlag, MSyntax::kNoArg );
	syntax.addFlag( H6EX_toleranceFlag, H6EX_toleranceLongFlag, MSyntax::kDouble );

	syntax.setObjectType( MSyntax::kSelectionList, 1, 1 );
	syntax.useSelectionAsDefault( true );

	return syntax;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus h6export::doIt ( const MArgList &args )
{
  //MessageBoxA(0,"A","B",MB_OK);
	MStatus status = MS::kSuccess;

	// Parse arguments
	MArgDatabase argData( syntax(), args, &status );

	if ( status != MS::kSuccess )
	{
		displayError( "Cannot get arguments." );
		return MS::kFailure;
	}

	// Get selection or specified object
	argData.getObjects( slList );

	// Process flags
	if ( !argData.isFlagSet( H6EX_fileNameFlag ) )
	{
		displayError( "Filename not defined." );
		return MS::kFailure;
	}

	argData.getFlagArgument( H6EX_fileNameFlag, 0, msFileName );

	if ( !argData.isFlagSet( H6EX_typeFlag ) )
	{
		displayError( "Export type not defined." );
		return MS::kFailure;
	}

	argData.getFlagArgument( H6EX_typeFlag, 0, msType );

  if ( argData.isFlagSet( H6EX_bFlag ) )
  {
    argData.getFlagArgument( H6EX_bFlag, 0, msSelection );
  }

	if ( msType == "stat" )
	{
		status = stat();
	}
	else if ( msType == "skin" )
	{
		nInfluences = 8;
		status = skin();
	}
	else if ( msType == "skel" )
	{
		status = skel();
	}
	else if ( msType == "anim" || msType == "part" || msType == "lght" )
	{
		// Get animation compression tolerance, witch is common 
		// for animation of joints, particles and lights
		if ( argData.isFlagSet( H6EX_toleranceFlag ) )
		{
			double tmp = 5.0;
			argData.getFlagArgument( H6EX_toleranceFlag, 0, tmp );
			tmp = tmp < 0 ? abs( tmp ) : tmp;
			tmp = tmp > 10.0 ? 10.0 : tmp;

			fTolerance = float( tmp );
		}
		else
		{
			fTolerance = 2.5f;
		}

		// Get specific export data
		if ( msType == "anim" )		
		{
			animType = 0;
			if ( argData.isFlagSet( H6EX_animTFlag ) )
			{
				animType |= TRS;
			}
			if ( argData.isFlagSet( H6EX_animRFlag ) )
			{
				animType |= ROT;
			}
			if ( argData.isFlagSet( H6EX_animSFlag ) )
			{
				animType |= SCL;
			}

			if ( animType == 0 )
			{
				animType |= ROT;
			}

			status = anim();
		}
		else if ( msType == "part" )
		{
			status = part();
		}
		else
		{
			status = lght();
		}
	}
	else
	{
		displayError( "Unsupported export type." );
		return MS::kFailure;
	}

	if ( status != MS::kSuccess )
	{
		displayError( "Export data gathering failed." );
		return MS::kFailure;
	}

	if ( write() != MS::kSuccess )
	{
		displayError( "Export to file failed." );
		return MS::kFailure;
	}

	setResult( "Exported successfully." );
	return redoIt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus	h6export::redoIt()
{
	return dgMod.doIt();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus	h6export::undoIt()
{
	return dgMod.undoIt();
}

void h6export::FillDagPaths( MFnSkinCluster& mfSkin, MDagPathArray& dpA, MDagPathArray& realJoints )
{
  MStatus status;
  mfSkin.influenceObjects( realJoints, &status );
  if ( status != MS::kSuccess )
  {
    displayError( "Joints DAG paths retrieval failed." );
    return;
  }

  std::string rootJointName = msSelection.asChar();

  MItDag dagIter( MItDag::kBreadthFirst, MFn::kInvalid, &status );
  for ( ; !dagIter.isDone(); dagIter.next())
  {
    MDagPath dagPath;
    status = dagIter.getPath( dagPath );
    MStringArray tmp;
    dagPath.fullPathName().split( '|', tmp );
    for ( unsigned int i = 0; i < tmp.length(); i++ )
    {
      std::string name = tmp[i].asChar();
      if ( name == rootJointName && dagPath.apiType() ==  MFn::kJoint )
      {
        dpA.append(dagPath);
        break;
      }
    }
  }
}