#include "commandClasses.h"
#include "h6export/H6EX.h"
#include "helloWorld/HLWD.h"
#include "displace/DSPL.h"


// Do not try to move this to libs.h, or double-definition will occure
#include <maya/MFnPlugin.h>

__declspec(dllexport) MStatus initializePlugin( MObject obj )
{
	//DEBUG
	//MessageBox( 0, "d", "d", MB_OK );
	MFnPlugin plugin( obj, "Nival Interactive", "1.0" );

	MStatus stat = MS::kSuccess;
	do
	{
		stat = plugin.registerCommand( "helloWorld", helloWorld::creator );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerCommand( "setVertexNormals", setVertexNormals::creator, setVertexNormals::newSyntax );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerCommand( "bindFile", bindFile::creator );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerCommand( "polyTrace", polyTrace::creator, polyTrace::newSyntax );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerCommand( "mapFaces", mapFaces::creator, mapFaces::newSyntax );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerCommand( "h6export", h6export::creator, h6export::newSyntax );
		if ( !stat ) 
		{
			break;
		}

		MString UserClassify = "utility/color";
		stat = plugin.registerNode(
			"cvColorShader", 
			cvColorShader::id, 
			cvColorShader::creator, 
			cvColorShader::initialize,
			MPxNode::kDependNode, 
			&UserClassify);
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.registerNode(
			"blindDataMesh",
			blindDataMesh::id,
			blindDataMesh::creator,
			blindDataMesh::initialize );

		if ( !stat )
		{
			break;
		}

		//stat = plugin.registerNode(
		//	"displace",
		//	displace::id,
		//	displace::creator,  
		//	displace::initialize,
		//	MPxNode::kDeformerNode ); 

		//if ( !stat )
		//{
		//	break;
		//}

	} while ( false );

	if ( !stat )
		stat.perror( "registerCommand failed");

	return stat;
}

__declspec(dllexport) MStatus uninitializePlugin( MObject obj )
{
	MFnPlugin plugin( obj );

	MStatus	stat = MS::kSuccess;
	do
	{
		stat = plugin.deregisterCommand( "setVertexNormals" );
		if ( !stat )
		{
			break;
		}

		stat = plugin.deregisterCommand( "helloWorld" );
		if ( !stat )
		{
			break;
		}

		stat = plugin.deregisterCommand( "bindFile" );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.deregisterCommand( "polyTrace" );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.deregisterNode( cvColorShader::id );
		if ( !stat ) 
		{
			break;
		}

		stat = plugin.deregisterNode( blindDataMesh::id );
		if ( !stat)
		{
			break;
		}

		//stat = plugin.deregisterNode( displace::id );
		//if ( !stat)
		//{
		//	break;
		//}

		stat = plugin.deregisterCommand( "mapFaces" );
		if ( !stat )
		{
			break;
		}

		stat = plugin.deregisterCommand( "h6export" );
		if ( !stat )
		{
			break;
		}

	} while ( false );
	
	if ( !stat )
		stat.perror( "deregisterCommand failed" );

	return stat;
}

