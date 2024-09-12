#include "DSPL.h"
#include <maya/MFnGenericAttribute.h>

MTypeId displace::id( 0x28a0f57 ); // Random unique id
MObject displace::heightMap;
MObject displace::BBox1;
MObject displace::BBox2;
MObject displace::hmUpdate;

displace::displace()
{
	nSX = 1;
	nSY = 1;
	miHM.create( nSX, nSY, 3, MImage::kFloat );
	pPx = miHM.floatPixels();
	*( pPx + 0 ) = 0.0f;
	*( pPx + 1 ) = 0.0f;
	*( pPx + 2 ) = 0.0f;
}

displace::~displace() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* displace::creator()
{
	return new displace();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus displace::initialize() 
{ 
	MFnNumericAttribute nAttr; 
	heightMap = nAttr.createColor( "heightMap", "hm" );
	nAttr.setKeyable( true );
	nAttr.setStorable( true );
	nAttr.setDefault( 0.0f, 0.0f, 0.0f );
	addAttribute( heightMap ); 
	attributeAffects( displace::heightMap, displace::outputGeom ); 

	BBox1 = nAttr.createPoint( "boundingBox1", "bb1" );
	nAttr.setKeyable( true );
	nAttr.setStorable( true );
	nAttr.setDefault( 0.0f, 0.0f, 0.0f );
	addAttribute( BBox1 ); 
	attributeAffects( displace::BBox1, displace::outputGeom ); 

	BBox2 = nAttr.createPoint( "boundingBox2", "bb2" );
	nAttr.setKeyable( true );
	nAttr.setStorable( true );
	nAttr.setDefault( 1.0f, 1.0f, 1.0f );
	addAttribute( BBox2 ); 
	attributeAffects( displace::BBox2, displace::outputGeom ); 

	// This is only for height map change detection in compute method
	hmUpdate = nAttr.create( "heightMapUpdate", "hmu", MFnNumericData::kFloat, 0.0 );
	addAttribute( hmUpdate );
	attributeAffects( displace::heightMap, displace::hmUpdate ); 

	return MStatus::kSuccess; 
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus displace::deform(
	MDataBlock& block, 
	MItGeometry& iter, 
	const MMatrix& mat, 
	unsigned multiIndex )

{ 
	MStatus stat = MS::kFailure;

	MDataHandle bb1Data = block.inputValue( BBox1, &stat ); 
	if ( MS::kSuccess != stat )
	{
		return stat; 
	}
	MPoint ptBB1 = bb1Data.asFloat3();

	MDataHandle bb2Data = block.inputValue( BBox2, &stat ); 
	if ( MS::kSuccess != stat )
	{
		return stat; 
	}
	MPoint ptBB2 = bb2Data.asFloat3();

	for ( ; !iter.isDone(); iter.next() ) 
	{ 
		MPoint pt = iter.position( MSpace::kWorld ); 

		pt.z = pt.z - getHeight( pt.x - ptBB1.x, pt.y - ptBB1.y ) * abs( ptBB2.z - ptBB1.z );

		iter.setPosition( pt ); 
	} 

	return stat;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float displace::getHeight( const double& _fU, const double& _fV ) const
{
	// Returns height at _fU _fV from miHM

	// Perform bi-linear interpolation
	float fX = float( _fU * ( nSX - 1 ));
	float fY = float( _fV * ( nSY - 1 ));

	int nX = int( fX );
	int nY = int( fY );

	float fDX = fX - nX;
	float fDY = fY - nY;
	float fOX = 1 - fDX;
	float fOY = 1 - fDY;

	MColor mcBL =
		fOX * fOY * getPixel( nX + 0, nY + 0 ) + 
		fOX * fDY * getPixel( nX + 0, nY + 1 ) +
		fDX * fOY * getPixel( nX + 1, nY + 0 ) +
		fDX * fDY * getPixel( nX + 1, nY + 1 );

	return mcBL.r;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MColor displace::getPixel( const int& _nX, const int& _nY ) const
{
	MColor mcRes;

	int nX = _nX;
	int nY = _nY;

	if ( nX < 0 )
	{
		nX = 0;
	}

	if ( nY < 0 )
	{
		nY = 0;
	}

	if ( nX >= nSX )
	{
		nX = nSX - 1;
	}

	if ( nY >= nSY )
	{
		nY = nSY - 1;
	}

	// Get offset
	unsigned nOffset = ( nY * nSX + nX ) * 4;

	mcRes.r = *( pPx + nOffset + 0 ) / 255.0f;
	mcRes.g = *( pPx + nOffset + 1 ) / 255.0f;
	mcRes.b = *( pPx + nOffset + 2 ) / 255.0f;
	mcRes.a = 1.0f;

	return mcRes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MStatus displace::compute( const MPlug& _pl, MDataBlock& _db )
{
	// Refreshes height map data

	MStatus stat = MS::kFailure;

	//MString msCommand = MString( "print \"" ) + _pl.name() + MString( "\\n\"" );
	//MGlobal::executeCommand( msCommand );

	if ( _pl != hmUpdate )
	{
		return MStatus::kUnknownParameter; 
	}

	// Find the file node with height map
	MPlug plHM( thisMObject(), heightMap );
	MPlugArray pla;
	bool bConnected = plHM.connectedTo( pla, true, false, &stat );
	if ( pla.length() == 1 )
	{
		MObject moFile = pla[0].node();
		if ( moFile.hasFn( MFn::kFileTexture ) )
		{
			// Load new height map
			//stat = miHM.readFromFile( "d:/terrace_HMP.tga", MImage::kFloat );
			stat = miHM.readFromTextureNode( moFile, MImage::kFloat );
			if ( MS::kSuccess != stat )
			{
				return stat; 
			}

			// Get height map size
			unsigned nX;
			unsigned nY;
			miHM.getSize( nX, nY );
			nSX = int( nX );
			nSY = int( nY );

			// Get raw image data pointer
			pPx = miHM.floatPixels();


			_db.setClean( _pl );

			return MS::kSuccess;
		}
	}

	// Just get color 
	MFloatVector fvHM = _db.inputValue( heightMap, &stat ).asFloatVector();
	*( pPx + 0 ) = fvHM.x * 255;
	*( pPx + 1 ) = fvHM.y * 255;
	*( pPx + 2 ) = fvHM.z * 255;

	_db.setClean( _pl );

	return MS::kSuccess;
}

