#include "../commandClasses.h"



//===============================================
//=						 setVertexNormals								=
//===============================================



//	syntax: setVertexNormals -c x -r y
//
//	flags:
//			-c	-"convexity"				x(double)	-angle tangent
//			-r	- random					y(double)	-random in degrees
			
		

//add arguments:
const char *VNRM_convexFlag	= "-c",	*VNRM_convexLongFlag = "-convex";
const char *VNRM_randomFlag	= "-r",	*VNRM_randomLongFlag = "-random";
const char *VNRM_keeptoFlag	= "-kt",	*VNRM_keeptoLongFlag = "-keepTogether";
const char *VNRM_parFlag		= "-p",		*VNRM_parLongFlag	= "-paralNormals";

MSyntax setVertexNormals::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag( VNRM_convexFlag, VNRM_convexLongFlag, MSyntax::kDouble );
	syntax.addFlag( VNRM_randomFlag, VNRM_randomLongFlag, MSyntax::kDouble );
	syntax.addFlag( VNRM_keeptoFlag, VNRM_keeptoLongFlag, MSyntax::kBoolean );
	syntax.addFlag( VNRM_parFlag,	VNRM_parLongFlag,	MSyntax::kBoolean );
	return syntax;
}



MStatus setVertexNormals::doIt ( const MArgList &args )
{
	

//default tang angle and random
	double tan_a	= 0.0;
	double random	= 0.0;
	bool keepto		= true;
	bool par		= true;
	MStatus stat;
	

//parsing arguments	
	MArgDatabase argData( syntax(), args, &stat );

	if (stat!=MS::kSuccess ) printf ("\nMArgDatabase error!");

		if( argData.isFlagSet( VNRM_convexFlag ) )
		argData.getFlagArgument( VNRM_convexFlag, 0, tan_a );

		if( argData.isFlagSet( VNRM_randomFlag ) )
		argData.getFlagArgument( VNRM_randomFlag, 0, random );

	if( argData.isFlagSet( VNRM_keeptoFlag ) )
		argData.getFlagArgument( VNRM_keeptoFlag, 0, keepto );

	if( argData.isFlagSet( VNRM_parFlag ) )
		argData.getFlagArgument( VNRM_parFlag, 0, par);
	
//from radians to degrees
	random = random*M_PI/180.0;


//basic vars:
	MDagPath						node;
		MObject						 component;
		MSelectionList			list;
		MFnDagNode					nodeFn;
	MVector				polyNormal, vertexVector,newNormal;
	MPointArray			facePoints;
	MIntArray			vertsIDs;
	MPoint				vertPoint;
	double nr1, nr2, nr3;


	//get selected objects:
	MGlobal::getActiveSelectionList( list );
	MItSelectionList listIter( list);

	//iteration on PolyMeshes
	for ( ; !listIter.isDone(); listIter.next() )
	{
		listIter.getDagPath( node, component );
		MFnMesh meshFn(node);
		MItMeshPolygon	polyIter(node, component);
		MItMeshVertex	vrtxIter(node, component);

		//iteration on Polygons
		
		if (par)
			{
				nr1 = (float(rand())/RAND_MAX - 0.5)*2*random;
				nr2 = (float(rand())/RAND_MAX - 0.5)*2*random;
				nr3 = (float(rand())/RAND_MAX - 0.5)*2*random;			
			}
		
		
		for ( ; !polyIter.isDone(); polyIter.next() )
		{


			//get normal of current polygon
			meshFn.getPolygonNormal(polyIter.index(), polyNormal, MSpace::kWorld);

			//adding random rotation to normal if needed for every face
			
			if (!par)
			{
				nr1 = (float(rand())/RAND_MAX - 0.5)*2*random;
				nr2 = (float(rand())/RAND_MAX - 0.5)*2*random;
				nr3 = (float(rand())/RAND_MAX - 0.5)*2*random;			
			}
			MEulerRotation eulRot(nr1, nr2, nr3, MEulerRotation::kXYZ);
			polyNormal = (polyNormal.rotateBy(eulRot)).normal();
			
			
			//get polygon center
			MVector centerPoly(polyIter.center(MSpace::kWorld));

			//get polygon vertexes 
			polyIter.getPoints(facePoints,MSpace::kWorld);

			//get vertexes IDs
			polyIter.getVertices(vertsIDs);

			//iteration on vertixes
			for ( unsigned i = 0; i< vertsIDs.length(); i++)
			{
				
				//calculation new normal for each vertex
				meshFn.getPoint(vertsIDs[i], vertPoint, MSpace::kWorld);
				
				newNormal = (polyNormal*tan_a + (MVector(vertPoint) - centerPoly)).normal();
			
				//set new normal for each vertex
				meshFn.setFaceVertexNormal (newNormal,polyIter.index(), vertsIDs[i], MSpace::kWorld, &dgMod);		
			}

			
		}
		if (keepto)
			{
				
				for ( ; !vrtxIter.isDone(); vrtxIter.next() )
				{
					MVectorArray normalsAllVrtx;
					vrtxIter.getNormals(normalsAllVrtx, MSpace::kWorld);
					MVector combNormal(MVector::zero);
					if (normalsAllVrtx.length()!=1)
					{
						
						 for (unsigned int i = 0; i< normalsAllVrtx.length(); i++) 
						 {
							 combNormal+=normalsAllVrtx[i];
							

						 }
						 combNormal.normalize();
						 int idvrt = vrtxIter.index();
						 meshFn.setVertexNormal(combNormal, idvrt, MSpace::kWorld, &dgMod);
					}
					
					

				}

				
			}


	}//---

	return redoIt();
}


MStatus	setVertexNormals::redoIt()
{
	return dgMod.doIt();
}

MStatus	setVertexNormals::undoIt()
{
	return dgMod.undoIt();
}
//===============================================================

