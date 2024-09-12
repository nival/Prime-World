#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct GrassMaterial;
struct Material;
struct StaticMesh;
struct TerrainMaterial;
struct TerrainTypeInfo;

enum ENatureRoad
{
	NATUREROAD_TOP = 0,
	NATUREROAD_CENTER = 1,
	NATUREROAD_BOTTOM = 2,
};

const char *EnumToString( const ENatureRoad value );
const ENatureRoad StringToEnum_ENatureRoad( const char* value );

template <>
struct KnownEnum< ENatureRoad >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ENatureRoad value ) { return EnumToString( value ); }
	static const ENatureRoad ToEnum( const char* value ) { return StringToEnum_ENatureRoad( value ); }
	static const ENatureRoad ToEnum( const string& value ) { return StringToEnum_ENatureRoad( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ENatureType
{
	NATURETYPE_N = 0,
	NATURETYPE_A = 1,
	NATURETYPE_B = 2,
};

const char *EnumToString( const ENatureType value );
const ENatureType StringToEnum_ENatureType( const char* value );

template <>
struct KnownEnum< ENatureType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ENatureType value ) { return EnumToString( value ); }
	static const ENatureType ToEnum( const char* value ) { return StringToEnum_ENatureType( value ); }
	static const ENatureType ToEnum( const string& value ) { return StringToEnum_ENatureType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct DBNatureMapRoad
{
public:
	vector< CVec2 > nodes;
	float leftWidth;
	float centerWidth;
	float rightWidth;

	DBNatureMapRoad();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBNatureMapVisual
{
public:
	float overburnA;
	float overburnB;
	bool overburnRethreat;
	float attackDelay;
	float attackIntro;
	float attackTime;
	float attackPieces;
	float retreatTime;
	float retreatTiling;
	float noiseTile;
	float noiseR1;
	float noiseR2;
	float noiseSpeed;

	DBNatureMapVisual();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBNatureMap
{
public:
	bool editableNatureMap;
	vector< DBNatureMapRoad > attackSpaceRoads;
	vector< DBNatureMapRoad > logicRoads;
	bool useRoadsInPathFinding;
	int segmentCount;
	CVec2 baseA;
	float baseAOffset;
	float baseAPercent;
	CVec2 baseB;
	float baseBOffset;
	float baseBPercent;
	float gridStep;
	float attackSpeed;
	float overrideSpeed;
	DBNatureMapVisual visual;
	string natureMapFile;

	DBNatureMap();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct GrassLayer
{
public:
	string densityFileName;
	int bladesPerDensity;
	Ptr< GrassMaterial > material;

	GrassLayer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TerrainElementInstance
{
public:
	CVec3 position;
	float angle;
	CVec3 scale;
	Ptr< StaticMesh > terrainObject;
	Ptr< Material > material;

	TerrainElementInstance();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TerrainGeometry
{
public:
	string TCVFileName;
	string bakedTerrainFileName;
	string heightmapFileName;
	vector< TerrainElementInstance > terrainElements;
	float weldThreshold;
	float weldLookupSize;

	TerrainGeometry();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TerrainLayer
{
public:
	Ptr< TerrainTypeInfo > pTerrainType;

	TerrainLayer();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TerrainLayers
{
public:
	vector< TerrainLayer > terrainLayers;

	TerrainLayers();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Terrain : public DbResource
{
	DBRESOURCE_METHODS( Terrain );
public:
	int elemXCount;
	int elemYCount;
	int tilesPerElement;
	string layerMaskFile;
	DBNatureMap natureMap;
	TerrainGeometry geometry;
	TerrainLayers layers;
	vector< GrassLayer > grassLayers;

	Terrain();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Terrain& operator = ( const Terrain &_terrain ) { Assign( _terrain ); return *this; }
	Terrain( const Terrain &_terrain ) { Assign( _terrain ); }
	virtual void Assign( const Terrain &_terrain );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Terrain * pOther = dynamic_cast< const Terrain * > ( _pResource );
		if ( pOther ) Terrain::Assign( *pOther );
	}
};

struct TerrainTypeInfo : public DbResource
{
public:
	Ptr< TerrainMaterial > pDBMaterial;

	TerrainTypeInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainTypeInfo& operator = ( const TerrainTypeInfo &_terrainTypeInfo ) { Assign( _terrainTypeInfo ); return *this; }
	TerrainTypeInfo( const TerrainTypeInfo &_terrainTypeInfo ) { Assign( _terrainTypeInfo ); }
	virtual void Assign( const TerrainTypeInfo &_terrainTypeInfo );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainTypeInfo * pOther = dynamic_cast< const TerrainTypeInfo * > ( _pResource );
		if ( pOther ) TerrainTypeInfo::Assign( *pOther );
	}
};

}; // namespace NDb
