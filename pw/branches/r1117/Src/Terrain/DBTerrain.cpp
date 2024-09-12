// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"
#include "DBTerrain.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Terrain );
BASIC_REGISTER_DBRESOURCE( TerrainTypeInfo );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ENatureRoad value )
{
	switch( value )
	{
		case NATUREROAD_TOP:
			return "Top";
		case NATUREROAD_CENTER:
			return "Center";
		case NATUREROAD_BOTTOM:
			return "Bottom";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ENatureRoad", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ENatureRoad StringToEnum_ENatureRoad( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ENatureRoad)(NStr::ToInt( value ));
	if ( strcmp( value, "Top" ) == 0 || strcmp( value, "NATUREROAD_TOP" ) == 0 )
		return NATUREROAD_TOP;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "NATUREROAD_CENTER" ) == 0 )
		return NATUREROAD_CENTER;
	if ( strcmp( value, "Bottom" ) == 0 || strcmp( value, "NATUREROAD_BOTTOM" ) == 0 )
		return NATUREROAD_BOTTOM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ENatureRoad", value ) );
	return NATUREROAD_TOP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ENatureType value )
{
	switch( value )
	{
		case NATURETYPE_N:
			return "N";
		case NATURETYPE_A:
			return "A";
		case NATURETYPE_B:
			return "B";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ENatureType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ENatureType StringToEnum_ENatureType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ENatureType)(NStr::ToInt( value ));
	if ( strcmp( value, "N" ) == 0 || strcmp( value, "NATURETYPE_N" ) == 0 )
		return NATURETYPE_N;
	if ( strcmp( value, "A" ) == 0 || strcmp( value, "NATURETYPE_A" ) == 0 )
		return NATURETYPE_A;
	if ( strcmp( value, "B" ) == 0 || strcmp( value, "NATURETYPE_B" ) == 0 )
		return NATURETYPE_B;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ENatureType", value ) );
	return NATURETYPE_N;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBNatureMapRoad::DBNatureMapRoad() :
		leftWidth( 10.0f )
	, centerWidth( 10.0f )
	, rightWidth( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMapRoad::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nodes );
	saver.Add( 3, &leftWidth );
	saver.Add( 4, &centerWidth );
	saver.Add( 5, &rightWidth );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMapRoad::operator&( IXmlSaver &saver )
{
	saver.Add( "nodes", &nodes );
	saver.Add( "leftWidth", &leftWidth );
	saver.Add( "centerWidth", &centerWidth );
	saver.Add( "rightWidth", &rightWidth );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBNatureMapVisual::DBNatureMapVisual() :
		overburnA( 1.5f )
	, overburnB( 1.5f )
	, overburnRethreat( false )
	, attackDelay( 0.0f )
	, attackIntro( 0.2f )
	, attackTime( 1.5f )
	, attackPieces( 1.0f )
	, retreatTime( 1.0f )
	, retreatTiling( 0.4f )
	, noiseTile( 0.075f )
	, noiseR1( 0.2f )
	, noiseR2( 4.0f )
	, noiseSpeed( 3.6f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMapVisual::operator&( IBinSaver &saver )
{
	saver.Add( 2, &overburnA );
	saver.Add( 3, &overburnB );
	saver.Add( 4, &overburnRethreat );
	saver.Add( 5, &attackDelay );
	saver.Add( 6, &attackIntro );
	saver.Add( 7, &attackTime );
	saver.Add( 8, &attackPieces );
	saver.Add( 9, &retreatTime );
	saver.Add( 10, &retreatTiling );
	saver.Add( 11, &noiseTile );
	saver.Add( 12, &noiseR1 );
	saver.Add( 13, &noiseR2 );
	saver.Add( 14, &noiseSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMapVisual::operator&( IXmlSaver &saver )
{
	saver.Add( "overburnA", &overburnA );
	saver.Add( "overburnB", &overburnB );
	saver.Add( "overburnRethreat", &overburnRethreat );
	saver.Add( "attackDelay", &attackDelay );
	saver.Add( "attackIntro", &attackIntro );
	saver.Add( "attackTime", &attackTime );
	saver.Add( "attackPieces", &attackPieces );
	saver.Add( "retreatTime", &retreatTime );
	saver.Add( "retreatTiling", &retreatTiling );
	saver.Add( "noiseTile", &noiseTile );
	saver.Add( "noiseR1", &noiseR1 );
	saver.Add( "noiseR2", &noiseR2 );
	saver.Add( "noiseSpeed", &noiseSpeed );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBNatureMap::DBNatureMap() :
		editableNatureMap( false )
	, useRoadsInPathFinding( true )
	, segmentCount( 4 )
	, baseAOffset( 0.0f )
	, baseAPercent( 0.0f )
	, baseBOffset( 0.0f )
	, baseBPercent( 0.0f )
	, gridStep( 2.5f )
	, attackSpeed( 0.25f )
	, overrideSpeed( 15.0f )
{
	attackSpaceRoads.resize( 3 );
	logicRoads.resize( 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMap::operator&( IBinSaver &saver )
{
	saver.Add( 2, &editableNatureMap );
	saver.Add( 3, &attackSpaceRoads );
	saver.Add( 4, &logicRoads );
	saver.Add( 5, &useRoadsInPathFinding );
	saver.Add( 6, &segmentCount );
	saver.Add( 7, &baseA );
	saver.Add( 8, &baseAOffset );
	saver.Add( 9, &baseAPercent );
	saver.Add( 10, &baseB );
	saver.Add( 11, &baseBOffset );
	saver.Add( 12, &baseBPercent );
	saver.Add( 13, &gridStep );
	saver.Add( 14, &attackSpeed );
	saver.Add( 15, &overrideSpeed );
	saver.Add( 16, &visual );
	saver.Add( 17, &natureMapFile );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBNatureMap::operator&( IXmlSaver &saver )
{
	saver.Add( "editableNatureMap", &editableNatureMap );
	attackSpaceRoads.resize( 3 );
	saver.Add( "attackSpaceRoads", &attackSpaceRoads );
	logicRoads.resize( 3 );
	saver.Add( "logicRoads", &logicRoads );
	saver.Add( "useRoadsInPathFinding", &useRoadsInPathFinding );
	saver.Add( "segmentCount", &segmentCount );
	saver.Add( "baseA", &baseA );
	saver.Add( "baseAOffset", &baseAOffset );
	saver.Add( "baseAPercent", &baseAPercent );
	saver.Add( "baseB", &baseB );
	saver.Add( "baseBOffset", &baseBOffset );
	saver.Add( "baseBPercent", &baseBPercent );
	saver.Add( "gridStep", &gridStep );
	saver.Add( "attackSpeed", &attackSpeed );
	saver.Add( "overrideSpeed", &overrideSpeed );
	saver.Add( "visual", &visual );
	saver.Add( "natureMapFile", &natureMapFile );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GrassLayer::GrassLayer() :
		bladesPerDensity( 2 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassLayer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &densityFileName );
	saver.Add( 3, &bladesPerDensity );
	saver.Add( 4, &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassLayer::operator&( IXmlSaver &saver )
{
	saver.Add( "densityFileName", &densityFileName );
	saver.Add( "bladesPerDensity", &bladesPerDensity );
	saver.Add( "material", &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElementInstance::TerrainElementInstance() :
		angle( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementInstance::operator&( IBinSaver &saver )
{
	saver.Add( 2, &position );
	saver.Add( 3, &angle );
	saver.Add( 4, &scale );
	saver.Add( 5, &terrainObject );
	saver.Add( 6, &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementInstance::operator&( IXmlSaver &saver )
{
	saver.Add( "position", &position );
	saver.Add( "angle", &angle );
	saver.Add( "scale", &scale );
	saver.Add( "terrainObject", &terrainObject );
	saver.Add( "material", &material );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainGeometry::TerrainGeometry() :
		weldThreshold( 0.25f )
	, weldLookupSize( 2.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainGeometry::operator&( IBinSaver &saver )
{
	saver.Add( 2, &TCVFileName );
	saver.Add( 3, &bakedTerrainFileName );
	saver.Add( 4, &heightmapFileName );
	saver.Add( 5, &terrainElements );
	saver.Add( 6, &weldThreshold );
	saver.Add( 7, &weldLookupSize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainGeometry::operator&( IXmlSaver &saver )
{
	saver.Add( "TCVFileName", &TCVFileName );
	saver.Add( "bakedTerrainFileName", &bakedTerrainFileName );
	saver.Add( "heightmapFileName", &heightmapFileName );
	saver.Add( "terrainElements", &terrainElements );
	saver.Add( "weldThreshold", &weldThreshold );
	saver.Add( "weldLookupSize", &weldLookupSize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainLayer::TerrainLayer()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainLayer::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pTerrainType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainLayer::operator&( IXmlSaver &saver )
{
	saver.Add( "pTerrainType", &pTerrainType );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainLayers::TerrainLayers()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainLayers::operator&( IBinSaver &saver )
{
	saver.Add( 2, &terrainLayers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainLayers::operator&( IXmlSaver &saver )
{
	saver.Add( "terrainLayers", &terrainLayers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Terrain::Terrain() :
		elemXCount( 32 )
	, elemYCount( 32 )
	, tilesPerElement( 4 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Terrain::operator&( IBinSaver &saver )
{
	saver.Add( 2, &elemXCount );
	saver.Add( 3, &elemYCount );
	saver.Add( 4, &tilesPerElement );
	saver.Add( 5, &layerMaskFile );
	saver.Add( 6, &natureMap );
	saver.Add( 7, &geometry );
	saver.Add( 8, &layers );
	saver.Add( 9, &grassLayers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Terrain::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Terrain* parentPtr = (Terrain*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Terrain::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "elemXCount", &elemXCount );
	saver.Add( "elemYCount", &elemYCount );
	saver.Add( "tilesPerElement", &tilesPerElement );
	saver.Add( "layerMaskFile", &layerMaskFile );
	saver.Add( "natureMap", &natureMap );
	saver.Add( "geometry", &geometry );
	saver.Add( "layers", &layers );
	saver.Add( "grassLayers", &grassLayers );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Terrain::Assign( const Terrain& _terrain )
{
	elemXCount = _terrain.elemXCount;
	elemYCount = _terrain.elemYCount;
	tilesPerElement = _terrain.tilesPerElement;
	layerMaskFile = _terrain.layerMaskFile;
	natureMap.editableNatureMap = _terrain.natureMap.editableNatureMap;
	natureMap.attackSpaceRoads = _terrain.natureMap.attackSpaceRoads;
	natureMap.logicRoads = _terrain.natureMap.logicRoads;
	natureMap.useRoadsInPathFinding = _terrain.natureMap.useRoadsInPathFinding;
	natureMap.segmentCount = _terrain.natureMap.segmentCount;
	natureMap.baseA = _terrain.natureMap.baseA;
	natureMap.baseAOffset = _terrain.natureMap.baseAOffset;
	natureMap.baseAPercent = _terrain.natureMap.baseAPercent;
	natureMap.baseB = _terrain.natureMap.baseB;
	natureMap.baseBOffset = _terrain.natureMap.baseBOffset;
	natureMap.baseBPercent = _terrain.natureMap.baseBPercent;
	natureMap.gridStep = _terrain.natureMap.gridStep;
	natureMap.attackSpeed = _terrain.natureMap.attackSpeed;
	natureMap.overrideSpeed = _terrain.natureMap.overrideSpeed;
	natureMap.visual.overburnA = _terrain.natureMap.visual.overburnA;
	natureMap.visual.overburnB = _terrain.natureMap.visual.overburnB;
	natureMap.visual.overburnRethreat = _terrain.natureMap.visual.overburnRethreat;
	natureMap.visual.attackDelay = _terrain.natureMap.visual.attackDelay;
	natureMap.visual.attackIntro = _terrain.natureMap.visual.attackIntro;
	natureMap.visual.attackTime = _terrain.natureMap.visual.attackTime;
	natureMap.visual.attackPieces = _terrain.natureMap.visual.attackPieces;
	natureMap.visual.retreatTime = _terrain.natureMap.visual.retreatTime;
	natureMap.visual.retreatTiling = _terrain.natureMap.visual.retreatTiling;
	natureMap.visual.noiseTile = _terrain.natureMap.visual.noiseTile;
	natureMap.visual.noiseR1 = _terrain.natureMap.visual.noiseR1;
	natureMap.visual.noiseR2 = _terrain.natureMap.visual.noiseR2;
	natureMap.visual.noiseSpeed = _terrain.natureMap.visual.noiseSpeed;
	natureMap.natureMapFile = _terrain.natureMap.natureMapFile;
	geometry.TCVFileName = _terrain.geometry.TCVFileName;
	geometry.bakedTerrainFileName = _terrain.geometry.bakedTerrainFileName;
	geometry.heightmapFileName = _terrain.geometry.heightmapFileName;
	geometry.terrainElements = _terrain.geometry.terrainElements;
	geometry.weldThreshold = _terrain.geometry.weldThreshold;
	geometry.weldLookupSize = _terrain.geometry.weldLookupSize;
	layers.terrainLayers = _terrain.layers.terrainLayers;
	grassLayers = _terrain.grassLayers;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainTypeInfo::TerrainTypeInfo()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainTypeInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &pDBMaterial );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainTypeInfo::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainTypeInfo* parentPtr = (TerrainTypeInfo*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainTypeInfo::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "pDBMaterial", &pDBMaterial );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainTypeInfo::Assign( const TerrainTypeInfo& _terrainTypeInfo )
{
	pDBMaterial = _terrainTypeInfo.pDBMaterial;
}
}; // namespace NDb
