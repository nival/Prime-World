//#include "RenderResources.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;
using Render.DBRenderResources;

namespace Terrain.DBTerrain
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class GrassLayer
	{
		public string densityFileName = string.Empty;

		[GenerateChangedEvent]
		public int bladesPerDensity = 2;

		[GenerateChangedEvent]
		public DBPtr<GrassMaterial> material;
	}
	//////////////////////////////////////////////////////////////////////////
	[NonTerminal]
	public class TerrainTypeInfo : DBResource
	{
		public DBPtr<TerrainMaterial> pDBMaterial;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class TerrainLayer
	{
		[GenerateChangedEvent]
		public DBPtr<TerrainTypeInfo> pTerrainType;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class TerrainElementInstance
	{
		public Vec3 position;

		[GenerateChangedEvent]
		[FloatMinMaxAttribute( 0.0f, 360.0f )]
		public float angle = 0;

		public Scale scale;

		[GenerateChangedEvent]
    public DBPtr<StaticMesh> terrainObject;

    public DBPtr<Material> material;
  }
	//////////////////////////////////////////////////////////////////////////
	public class TerrainGeometry
	{
		[FieldCategory( "TCV" )]
    [DstFile( "tcv_data" )]
		public string TCVFileName = String.Empty;

		[FieldCategory( "Terrain elements" )]
    [DstFile( "baked_terrain" )]
    public string bakedTerrainFileName = String.Empty;

    [FieldCategory("Terrain elements")]
    [DstFile( "heightmap" )]
    public string heightmapFileName = String.Empty;

    [FieldCategory("Terrain elements")]
		public List<TerrainElementInstance> terrainElements = new List<TerrainElementInstance>();

    [FieldCategory("Weld parameters")]
    [Description("Maximum distance between vertices to be welded.")]
    public float weldThreshold = 0.25f;

    [FieldCategory("Weld parameters")]
    [Description("ширина пограничной зоны патча, в пределах которой ищутся дубликаты вершин. При поиске к ней также добавляется weldThreshold.")]
    public float weldLookupSize = 2.0f;
  }
	//////////////////////////////////////////////////////////////////////////
	public class TerrainLayers
	{
		public List<TerrainLayer> terrainLayers = new List<TerrainLayer>();
	}
	//////////////////////////////////////////////////////////////////////////
  public enum ENatureType // corresponds to EFaction
  {
    N,
    A,
    B,
  }
  public enum ENatureRoad // see also: ERoute
  {
    Top,
    Center,
    Bottom,
  }
  public class DBNatureMapRoad
  {
    public List<Vec2> nodes = new List<Vec2>();
    public float leftWidth = 10.0f;
    public float centerWidth = 10.0f;
    public float rightWidth = 10.0f;
  }
  public class DBNatureMapVisual
  {
    [Description("Во сколько раз засвечивать террейн при атаке (фракция A)")]
    public float overburnA = 1.5f;
    [Description("Во сколько раз засвечивать террейн при атаке (фракция B)")]
    public float overburnB = 1.5f;
    [Description( "Засвечивать ли террейн при отступлении" )]
    public bool overburnRethreat = false;
    [Description( "Максимальная задержка перед засвечиванием, для рандомизации атаки" )]
    public float attackDelay = 0.0f;
    public float attackIntro = 0.2f;
    [Description("Время, в течении которого играется вижуал одного шага атаки")]
    public float attackTime = 1.5f;
    [Description("На сколько кусков по ширине надо разбивать каждую дорогу и лес для рандомизации атаки")]
    public float attackPieces = 1;
    [Description("Время, в течении которого играется вижуал одного шага отступления")]
    public float retreatTime = 1.0f;
    [Description("Тайлинг текстурной маски, использующейся для отсутпления (Data/Tech/terrmask.dds)")]
    public float retreatTiling = 0.4f;
    
    public float noiseTile = 0.075f;
    public float noiseR1 = 0.2f;
    public float noiseR2 = 4.0f;
    public float noiseSpeed = 3.6f;
  }
  [DBVersion(0)]
  public class DBNatureMap
	{
    [Description("Отключить дороги и продвижение террейна, задать NatureMap вручную")]
    public bool editableNatureMap = false;

    [Description( "Три дороги attack space, заданные как набор координат (произвольное количество узлов)" )]
    [EnumArray( typeof( ENatureRoad ) )]
    public List<DBNatureMapRoad> attackSpaceRoads = new List<DBNatureMapRoad>();

    [Description( "Три дороги для хождения ботов, заданные как набор координат (произвольное количество узлов)" )]
    [EnumArray( typeof( ENatureRoad ) )]
    public List<DBNatureMapRoad> logicRoads = new List<DBNatureMapRoad>();

    public bool useRoadsInPathFinding = true;

    [Description("Количество сегментов, на которое разбивается каждая дорога (и, соответственно, леса)")]
    public int segmentCount = 4;
    public Vec2 baseA = new Vec2();
    public float baseAOffset = 0.0f;
    [Description( "Сколько % территории занимает база" )]
    public float baseAPercent = 0.0f;
    public Vec2 baseB = new Vec2();
    public float baseBOffset = 0.0f;
    [Description( "Сколько % территории занимает база" )]
    public float baseBPercent = 0.0f;
    [Description("Размер внутренней сетки в метрах, крайне не рекомендуется менять бездумно")]
    public float gridStep = 2.5f;
    [Description("Скорость распространения террейна по дорогам и лесам")]
    public float attackSpeed = 0.25f;
    [Description("Скорость распространения террейна при локальной подмене")]
    public float overrideSpeed = 15.0f;
    [Description("Визуальные настройки природной карты")]
    public DBNatureMapVisual visual;

    [DstFile( "naturemap" )]
    public string natureMapFile = string.Empty;
  }
	//////////////////////////////////////////////////////////////////////////
	[UseTypeName("TERN")]
  [DBVersion(3)]
	public class Terrain : DBResource
	{
		public int elemXCount = 32;
		public int elemYCount = 32;
		public int tilesPerElement = 4;

    [DstFile( "layer_mask" )]
		public string layerMaskFile = string.Empty;

    public DBNatureMap natureMap = new DBNatureMap();
		public TerrainGeometry geometry = new TerrainGeometry();
		public TerrainLayers layers = new TerrainLayers();
		public List<GrassLayer> grassLayers = new List<GrassLayer>();
  }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
