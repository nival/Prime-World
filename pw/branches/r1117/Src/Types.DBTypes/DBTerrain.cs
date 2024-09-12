// Automatically generated file, don't change it manually!
using System;
using System.Collections.Generic;
using System.ComponentModel;

using libdb;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;
using libdb.Diagnostics;
using libdb.Animated;

namespace DBTypes
{
public enum ENatureRoad
{
	Top = 0,
	Center = 1,
	Bottom = 2,
};

public enum ENatureType
{
	N = 0,
	A = 1,
	B = 2,
};

public class DBNatureMapRoad : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBNatureMapRoad __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<Vec2> _nodes;
	private UndoRedo<float> _leftWidth;
	private UndoRedo<float> _centerWidth;
	private UndoRedo<float> _rightWidth;

	public libdb.IChangeableList<Vec2> nodes { get { return _nodes; } set { _nodes.Assign( value ); } }

	public float leftWidth { get { return _leftWidth.Get(); } set { _leftWidth.Set( value ); } }

	public float centerWidth { get { return _centerWidth.Get(); } set { _centerWidth.Set( value ); } }

	public float rightWidth { get { return _rightWidth.Get(); } set { _rightWidth.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_nodes = new UndoRedoAssignableList<Vec2>( owner );
		_leftWidth = new UndoRedo<float>( owner, 10.0f );
		_centerWidth = new UndoRedo<float>( owner, 10.0f );
		_rightWidth = new UndoRedo<float>( owner, 10.0f );
		_nodes.Changed += FireChangedEvent;
		_leftWidth.Changed += FireChangedEvent;
		_centerWidth.Changed += FireChangedEvent;
		_rightWidth.Changed += FireChangedEvent;
	}

	public DBNatureMapRoad()
	{
		Initialize( GetOwner() );
	}

	public DBNatureMapRoad( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBNatureMapRoad( DBResource owner, DBNatureMapRoad source )
		: this(owner, source, true){}

	protected DBNatureMapRoad( DBResource owner, DBNatureMapRoad source, bool fireEvent )
	{
		_nodes = new UndoRedoAssignableList<Vec2>( owner );
		_nodes.Assign( source.nodes );
		_leftWidth = new UndoRedo<float>( owner, source.leftWidth );
		_centerWidth = new UndoRedo<float>( owner, source.centerWidth );
		_rightWidth = new UndoRedo<float>( owner, source.rightWidth );
		_nodes.Changed += FireChangedEvent;
		_leftWidth.Changed += FireChangedEvent;
		_centerWidth.Changed += FireChangedEvent;
		_rightWidth.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBNatureMapRoad source = _source as DBNatureMapRoad;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBNatureMapRoad" );
		nodes = source.nodes;
		leftWidth = source.leftWidth;
		centerWidth = source.centerWidth;
		rightWidth = source.rightWidth;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBNatureMapRoad newParent = _newParent as DBNatureMapRoad;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_nodes.SetParent( newParent == null ? null : newParent._nodes );
		_leftWidth.SetParent( newParent == null ? null : newParent._leftWidth );
		_centerWidth.SetParent( newParent == null ? null : newParent._centerWidth );
		_rightWidth.SetParent( newParent == null ? null : newParent._rightWidth );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_nodes.Reset();
		_leftWidth.Reset();
		_centerWidth.Reset();
		_rightWidth.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_nodes.IsDerivedFromParent()
			&& _leftWidth.IsDerivedFromParent()
			&& _centerWidth.IsDerivedFromParent()
			&& _rightWidth.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "nodes" )
			_nodes.Reset();
		else if ( fieldName == "leftWidth" )
			_leftWidth.Reset();
		else if ( fieldName == "centerWidth" )
			_centerWidth.Reset();
		else if ( fieldName == "rightWidth" )
			_rightWidth.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "nodes" )
			return _nodes.IsDerivedFromParent();
		if ( fieldName == "leftWidth" )
			return _leftWidth.IsDerivedFromParent();
		if ( fieldName == "centerWidth" )
			return _centerWidth.IsDerivedFromParent();
		if ( fieldName == "rightWidth" )
			return _rightWidth.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class DBNatureMapVisual : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBNatureMapVisual __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _overburnA;
	private UndoRedo<float> _overburnB;
	private UndoRedo<bool> _overburnRethreat;
	private UndoRedo<float> _attackDelay;
	private UndoRedo<float> _attackIntro;
	private UndoRedo<float> _attackTime;
	private UndoRedo<float> _attackPieces;
	private UndoRedo<float> _retreatTime;
	private UndoRedo<float> _retreatTiling;
	private UndoRedo<float> _noiseTile;
	private UndoRedo<float> _noiseR1;
	private UndoRedo<float> _noiseR2;
	private UndoRedo<float> _noiseSpeed;

	[Description( "Во сколько раз засвечивать террейн при атаке (фракция A)" )]
	public float overburnA { get { return _overburnA.Get(); } set { _overburnA.Set( value ); } }

	[Description( "Во сколько раз засвечивать террейн при атаке (фракция B)" )]
	public float overburnB { get { return _overburnB.Get(); } set { _overburnB.Set( value ); } }

	[Description( "Засвечивать ли террейн при отступлении" )]
	public bool overburnRethreat { get { return _overburnRethreat.Get(); } set { _overburnRethreat.Set( value ); } }

	[Description( "Максимальная задержка перед засвечиванием, для рандомизации атаки" )]
	public float attackDelay { get { return _attackDelay.Get(); } set { _attackDelay.Set( value ); } }

	public float attackIntro { get { return _attackIntro.Get(); } set { _attackIntro.Set( value ); } }

	[Description( "Время, в течении которого играется вижуал одного шага атаки" )]
	public float attackTime { get { return _attackTime.Get(); } set { _attackTime.Set( value ); } }

	[Description( "На сколько кусков по ширине надо разбивать каждую дорогу и лес для рандомизации атаки" )]
	public float attackPieces { get { return _attackPieces.Get(); } set { _attackPieces.Set( value ); } }

	[Description( "Время, в течении которого играется вижуал одного шага отступления" )]
	public float retreatTime { get { return _retreatTime.Get(); } set { _retreatTime.Set( value ); } }

	[Description( "Тайлинг текстурной маски, использующейся для отсутпления (Data/Tech/terrmask.dds)" )]
	public float retreatTiling { get { return _retreatTiling.Get(); } set { _retreatTiling.Set( value ); } }

	public float noiseTile { get { return _noiseTile.Get(); } set { _noiseTile.Set( value ); } }

	public float noiseR1 { get { return _noiseR1.Get(); } set { _noiseR1.Set( value ); } }

	public float noiseR2 { get { return _noiseR2.Get(); } set { _noiseR2.Set( value ); } }

	public float noiseSpeed { get { return _noiseSpeed.Get(); } set { _noiseSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_overburnA = new UndoRedo<float>( owner, 1.5f );
		_overburnB = new UndoRedo<float>( owner, 1.5f );
		_overburnRethreat = new UndoRedo<bool>( owner, false );
		_attackDelay = new UndoRedo<float>( owner, 0.0f );
		_attackIntro = new UndoRedo<float>( owner, 0.2f );
		_attackTime = new UndoRedo<float>( owner, 1.5f );
		_attackPieces = new UndoRedo<float>( owner, 1.0f );
		_retreatTime = new UndoRedo<float>( owner, 1.0f );
		_retreatTiling = new UndoRedo<float>( owner, 0.4f );
		_noiseTile = new UndoRedo<float>( owner, 0.075f );
		_noiseR1 = new UndoRedo<float>( owner, 0.2f );
		_noiseR2 = new UndoRedo<float>( owner, 4.0f );
		_noiseSpeed = new UndoRedo<float>( owner, 3.6f );
		_overburnA.Changed += FireChangedEvent;
		_overburnB.Changed += FireChangedEvent;
		_overburnRethreat.Changed += FireChangedEvent;
		_attackDelay.Changed += FireChangedEvent;
		_attackIntro.Changed += FireChangedEvent;
		_attackTime.Changed += FireChangedEvent;
		_attackPieces.Changed += FireChangedEvent;
		_retreatTime.Changed += FireChangedEvent;
		_retreatTiling.Changed += FireChangedEvent;
		_noiseTile.Changed += FireChangedEvent;
		_noiseR1.Changed += FireChangedEvent;
		_noiseR2.Changed += FireChangedEvent;
		_noiseSpeed.Changed += FireChangedEvent;
	}

	public DBNatureMapVisual()
	{
		Initialize( GetOwner() );
	}

	public DBNatureMapVisual( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBNatureMapVisual( DBResource owner, DBNatureMapVisual source )
		: this(owner, source, true){}

	protected DBNatureMapVisual( DBResource owner, DBNatureMapVisual source, bool fireEvent )
	{
		_overburnA = new UndoRedo<float>( owner, source.overburnA );
		_overburnB = new UndoRedo<float>( owner, source.overburnB );
		_overburnRethreat = new UndoRedo<bool>( owner, source.overburnRethreat );
		_attackDelay = new UndoRedo<float>( owner, source.attackDelay );
		_attackIntro = new UndoRedo<float>( owner, source.attackIntro );
		_attackTime = new UndoRedo<float>( owner, source.attackTime );
		_attackPieces = new UndoRedo<float>( owner, source.attackPieces );
		_retreatTime = new UndoRedo<float>( owner, source.retreatTime );
		_retreatTiling = new UndoRedo<float>( owner, source.retreatTiling );
		_noiseTile = new UndoRedo<float>( owner, source.noiseTile );
		_noiseR1 = new UndoRedo<float>( owner, source.noiseR1 );
		_noiseR2 = new UndoRedo<float>( owner, source.noiseR2 );
		_noiseSpeed = new UndoRedo<float>( owner, source.noiseSpeed );
		_overburnA.Changed += FireChangedEvent;
		_overburnB.Changed += FireChangedEvent;
		_overburnRethreat.Changed += FireChangedEvent;
		_attackDelay.Changed += FireChangedEvent;
		_attackIntro.Changed += FireChangedEvent;
		_attackTime.Changed += FireChangedEvent;
		_attackPieces.Changed += FireChangedEvent;
		_retreatTime.Changed += FireChangedEvent;
		_retreatTiling.Changed += FireChangedEvent;
		_noiseTile.Changed += FireChangedEvent;
		_noiseR1.Changed += FireChangedEvent;
		_noiseR2.Changed += FireChangedEvent;
		_noiseSpeed.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBNatureMapVisual source = _source as DBNatureMapVisual;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBNatureMapVisual" );
		overburnA = source.overburnA;
		overburnB = source.overburnB;
		overburnRethreat = source.overburnRethreat;
		attackDelay = source.attackDelay;
		attackIntro = source.attackIntro;
		attackTime = source.attackTime;
		attackPieces = source.attackPieces;
		retreatTime = source.retreatTime;
		retreatTiling = source.retreatTiling;
		noiseTile = source.noiseTile;
		noiseR1 = source.noiseR1;
		noiseR2 = source.noiseR2;
		noiseSpeed = source.noiseSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBNatureMapVisual newParent = _newParent as DBNatureMapVisual;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_overburnA.SetParent( newParent == null ? null : newParent._overburnA );
		_overburnB.SetParent( newParent == null ? null : newParent._overburnB );
		_overburnRethreat.SetParent( newParent == null ? null : newParent._overburnRethreat );
		_attackDelay.SetParent( newParent == null ? null : newParent._attackDelay );
		_attackIntro.SetParent( newParent == null ? null : newParent._attackIntro );
		_attackTime.SetParent( newParent == null ? null : newParent._attackTime );
		_attackPieces.SetParent( newParent == null ? null : newParent._attackPieces );
		_retreatTime.SetParent( newParent == null ? null : newParent._retreatTime );
		_retreatTiling.SetParent( newParent == null ? null : newParent._retreatTiling );
		_noiseTile.SetParent( newParent == null ? null : newParent._noiseTile );
		_noiseR1.SetParent( newParent == null ? null : newParent._noiseR1 );
		_noiseR2.SetParent( newParent == null ? null : newParent._noiseR2 );
		_noiseSpeed.SetParent( newParent == null ? null : newParent._noiseSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_overburnA.Reset();
		_overburnB.Reset();
		_overburnRethreat.Reset();
		_attackDelay.Reset();
		_attackIntro.Reset();
		_attackTime.Reset();
		_attackPieces.Reset();
		_retreatTime.Reset();
		_retreatTiling.Reset();
		_noiseTile.Reset();
		_noiseR1.Reset();
		_noiseR2.Reset();
		_noiseSpeed.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_overburnA.IsDerivedFromParent()
			&& _overburnB.IsDerivedFromParent()
			&& _overburnRethreat.IsDerivedFromParent()
			&& _attackDelay.IsDerivedFromParent()
			&& _attackIntro.IsDerivedFromParent()
			&& _attackTime.IsDerivedFromParent()
			&& _attackPieces.IsDerivedFromParent()
			&& _retreatTime.IsDerivedFromParent()
			&& _retreatTiling.IsDerivedFromParent()
			&& _noiseTile.IsDerivedFromParent()
			&& _noiseR1.IsDerivedFromParent()
			&& _noiseR2.IsDerivedFromParent()
			&& _noiseSpeed.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "overburnA" )
			_overburnA.Reset();
		else if ( fieldName == "overburnB" )
			_overburnB.Reset();
		else if ( fieldName == "overburnRethreat" )
			_overburnRethreat.Reset();
		else if ( fieldName == "attackDelay" )
			_attackDelay.Reset();
		else if ( fieldName == "attackIntro" )
			_attackIntro.Reset();
		else if ( fieldName == "attackTime" )
			_attackTime.Reset();
		else if ( fieldName == "attackPieces" )
			_attackPieces.Reset();
		else if ( fieldName == "retreatTime" )
			_retreatTime.Reset();
		else if ( fieldName == "retreatTiling" )
			_retreatTiling.Reset();
		else if ( fieldName == "noiseTile" )
			_noiseTile.Reset();
		else if ( fieldName == "noiseR1" )
			_noiseR1.Reset();
		else if ( fieldName == "noiseR2" )
			_noiseR2.Reset();
		else if ( fieldName == "noiseSpeed" )
			_noiseSpeed.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "overburnA" )
			return _overburnA.IsDerivedFromParent();
		if ( fieldName == "overburnB" )
			return _overburnB.IsDerivedFromParent();
		if ( fieldName == "overburnRethreat" )
			return _overburnRethreat.IsDerivedFromParent();
		if ( fieldName == "attackDelay" )
			return _attackDelay.IsDerivedFromParent();
		if ( fieldName == "attackIntro" )
			return _attackIntro.IsDerivedFromParent();
		if ( fieldName == "attackTime" )
			return _attackTime.IsDerivedFromParent();
		if ( fieldName == "attackPieces" )
			return _attackPieces.IsDerivedFromParent();
		if ( fieldName == "retreatTime" )
			return _retreatTime.IsDerivedFromParent();
		if ( fieldName == "retreatTiling" )
			return _retreatTiling.IsDerivedFromParent();
		if ( fieldName == "noiseTile" )
			return _noiseTile.IsDerivedFromParent();
		if ( fieldName == "noiseR1" )
			return _noiseR1.IsDerivedFromParent();
		if ( fieldName == "noiseR2" )
			return _noiseR2.IsDerivedFromParent();
		if ( fieldName == "noiseSpeed" )
			return _noiseSpeed.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
public class DBNatureMap : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBNatureMap __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _editableNatureMap;
	private UndoRedoAssignableList<DBNatureMapRoad> _attackSpaceRoads;
	private UndoRedoAssignableList<DBNatureMapRoad> _logicRoads;
	private UndoRedo<bool> _useRoadsInPathFinding;
	private UndoRedo<int> _segmentCount;
	private Vec2 _baseA;
	private UndoRedo<float> _baseAOffset;
	private UndoRedo<float> _baseAPercent;
	private Vec2 _baseB;
	private UndoRedo<float> _baseBOffset;
	private UndoRedo<float> _baseBPercent;
	private UndoRedo<float> _gridStep;
	private UndoRedo<float> _attackSpeed;
	private UndoRedo<float> _overrideSpeed;
	private DBNatureMapVisual _visual;

	[Description( "Отключить дороги и продвижение террейна, задать NatureMap вручную" )]
	public bool editableNatureMap { get { return _editableNatureMap.Get(); } set { _editableNatureMap.Set( value ); } }

	[Description( "Три дороги attack space, заданные как набор координат (произвольное количество узлов)" )]
	[EnumArray(typeof(ENatureRoad))]
	public libdb.IChangeableList<DBNatureMapRoad> attackSpaceRoads { get { return _attackSpaceRoads; } set { _attackSpaceRoads.Assign( value ); } }

	[Description( "Три дороги для хождения ботов, заданные как набор координат (произвольное количество узлов)" )]
	[EnumArray(typeof(ENatureRoad))]
	public libdb.IChangeableList<DBNatureMapRoad> logicRoads { get { return _logicRoads; } set { _logicRoads.Assign( value ); } }

	public bool useRoadsInPathFinding { get { return _useRoadsInPathFinding.Get(); } set { _useRoadsInPathFinding.Set( value ); } }

	[Description( "Количество сегментов, на которое разбивается каждая дорога (и, соответственно, леса)" )]
	public int segmentCount { get { return _segmentCount.Get(); } set { _segmentCount.Set( value ); } }

	public Vec2 baseA { get { return _baseA; } set { _baseA.Assign( value ); } }

	public float baseAOffset { get { return _baseAOffset.Get(); } set { _baseAOffset.Set( value ); } }

	[Description( "Сколько % территории занимает база" )]
	public float baseAPercent { get { return _baseAPercent.Get(); } set { _baseAPercent.Set( value ); } }

	public Vec2 baseB { get { return _baseB; } set { _baseB.Assign( value ); } }

	public float baseBOffset { get { return _baseBOffset.Get(); } set { _baseBOffset.Set( value ); } }

	[Description( "Сколько % территории занимает база" )]
	public float baseBPercent { get { return _baseBPercent.Get(); } set { _baseBPercent.Set( value ); } }

	[Description( "Размер внутренней сетки в метрах, крайне не рекомендуется менять бездумно" )]
	public float gridStep { get { return _gridStep.Get(); } set { _gridStep.Set( value ); } }

	[Description( "Скорость распространения террейна по дорогам и лесам" )]
	public float attackSpeed { get { return _attackSpeed.Get(); } set { _attackSpeed.Set( value ); } }

	[Description( "Скорость распространения террейна при локальной подмене" )]
	public float overrideSpeed { get { return _overrideSpeed.Get(); } set { _overrideSpeed.Set( value ); } }

	[Description( "Визуальные настройки природной карты" )]
	public DBNatureMapVisual visual { get { return _visual; } set { _visual.Assign( value ); } }

	[DstFile("naturemap")]
	public string natureMapFile { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "naturemap"
	); } }
	private void Initialize( DBResource owner )
	{
		_editableNatureMap = new UndoRedo<bool>( owner, false );
		_attackSpaceRoads = new UndoRedoAssignableList<DBNatureMapRoad>( owner, typeof( ENatureRoad ) );
		_logicRoads = new UndoRedoAssignableList<DBNatureMapRoad>( owner, typeof( ENatureRoad ) );
		_useRoadsInPathFinding = new UndoRedo<bool>( owner, true );
		_segmentCount = new UndoRedo<int>( owner, 4 );
		_baseA = new Vec2( owner );
		_baseAOffset = new UndoRedo<float>( owner, 0.0f );
		_baseAPercent = new UndoRedo<float>( owner, 0.0f );
		_baseB = new Vec2( owner );
		_baseBOffset = new UndoRedo<float>( owner, 0.0f );
		_baseBPercent = new UndoRedo<float>( owner, 0.0f );
		_gridStep = new UndoRedo<float>( owner, 2.5f );
		_attackSpeed = new UndoRedo<float>( owner, 0.25f );
		_overrideSpeed = new UndoRedo<float>( owner, 15.0f );
		_visual = new DBNatureMapVisual( owner );
		_editableNatureMap.Changed += FireChangedEvent;
		_attackSpaceRoads.Changed += FireChangedEvent;
		_logicRoads.Changed += FireChangedEvent;
		_useRoadsInPathFinding.Changed += FireChangedEvent;
		_segmentCount.Changed += FireChangedEvent;
		_baseA.Changed += FireChangedEvent;
		_baseAOffset.Changed += FireChangedEvent;
		_baseAPercent.Changed += FireChangedEvent;
		_baseB.Changed += FireChangedEvent;
		_baseBOffset.Changed += FireChangedEvent;
		_baseBPercent.Changed += FireChangedEvent;
		_gridStep.Changed += FireChangedEvent;
		_attackSpeed.Changed += FireChangedEvent;
		_overrideSpeed.Changed += FireChangedEvent;
		_visual.Changed += FireChangedEvent;
	}

	public DBNatureMap()
	{
		Initialize( GetOwner() );
	}

	public DBNatureMap( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBNatureMap( DBResource owner, DBNatureMap source )
		: this(owner, source, true){}

	protected DBNatureMap( DBResource owner, DBNatureMap source, bool fireEvent )
	{
		_editableNatureMap = new UndoRedo<bool>( owner, source.editableNatureMap );
		_attackSpaceRoads = new UndoRedoAssignableList<DBNatureMapRoad>( owner, typeof( ENatureRoad ) );
		_attackSpaceRoads.Assign( source.attackSpaceRoads );
		_logicRoads = new UndoRedoAssignableList<DBNatureMapRoad>( owner, typeof( ENatureRoad ) );
		_logicRoads.Assign( source.logicRoads );
		_useRoadsInPathFinding = new UndoRedo<bool>( owner, source.useRoadsInPathFinding );
		_segmentCount = new UndoRedo<int>( owner, source.segmentCount );
		_baseA = new Vec2( owner, source.baseA );
		_baseAOffset = new UndoRedo<float>( owner, source.baseAOffset );
		_baseAPercent = new UndoRedo<float>( owner, source.baseAPercent );
		_baseB = new Vec2( owner, source.baseB );
		_baseBOffset = new UndoRedo<float>( owner, source.baseBOffset );
		_baseBPercent = new UndoRedo<float>( owner, source.baseBPercent );
		_gridStep = new UndoRedo<float>( owner, source.gridStep );
		_attackSpeed = new UndoRedo<float>( owner, source.attackSpeed );
		_overrideSpeed = new UndoRedo<float>( owner, source.overrideSpeed );
		_visual = new DBNatureMapVisual( owner, source.visual );
		_editableNatureMap.Changed += FireChangedEvent;
		_attackSpaceRoads.Changed += FireChangedEvent;
		_logicRoads.Changed += FireChangedEvent;
		_useRoadsInPathFinding.Changed += FireChangedEvent;
		_segmentCount.Changed += FireChangedEvent;
		_baseA.Changed += FireChangedEvent;
		_baseAOffset.Changed += FireChangedEvent;
		_baseAPercent.Changed += FireChangedEvent;
		_baseB.Changed += FireChangedEvent;
		_baseBOffset.Changed += FireChangedEvent;
		_baseBPercent.Changed += FireChangedEvent;
		_gridStep.Changed += FireChangedEvent;
		_attackSpeed.Changed += FireChangedEvent;
		_overrideSpeed.Changed += FireChangedEvent;
		_visual.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBNatureMap source = _source as DBNatureMap;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBNatureMap" );
		editableNatureMap = source.editableNatureMap;
		attackSpaceRoads = source.attackSpaceRoads;
		logicRoads = source.logicRoads;
		useRoadsInPathFinding = source.useRoadsInPathFinding;
		segmentCount = source.segmentCount;
		baseA = source.baseA;
		baseAOffset = source.baseAOffset;
		baseAPercent = source.baseAPercent;
		baseB = source.baseB;
		baseBOffset = source.baseBOffset;
		baseBPercent = source.baseBPercent;
		gridStep = source.gridStep;
		attackSpeed = source.attackSpeed;
		overrideSpeed = source.overrideSpeed;
		visual = source.visual;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBNatureMap newParent = _newParent as DBNatureMap;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_editableNatureMap.SetParent( newParent == null ? null : newParent._editableNatureMap );
		_attackSpaceRoads.SetParent( newParent == null ? null : newParent._attackSpaceRoads );
		_logicRoads.SetParent( newParent == null ? null : newParent._logicRoads );
		_useRoadsInPathFinding.SetParent( newParent == null ? null : newParent._useRoadsInPathFinding );
		_segmentCount.SetParent( newParent == null ? null : newParent._segmentCount );
		_baseA.SetParent( newParent == null ? null : newParent._baseA );
		_baseAOffset.SetParent( newParent == null ? null : newParent._baseAOffset );
		_baseAPercent.SetParent( newParent == null ? null : newParent._baseAPercent );
		_baseB.SetParent( newParent == null ? null : newParent._baseB );
		_baseBOffset.SetParent( newParent == null ? null : newParent._baseBOffset );
		_baseBPercent.SetParent( newParent == null ? null : newParent._baseBPercent );
		_gridStep.SetParent( newParent == null ? null : newParent._gridStep );
		_attackSpeed.SetParent( newParent == null ? null : newParent._attackSpeed );
		_overrideSpeed.SetParent( newParent == null ? null : newParent._overrideSpeed );
		_visual.SetParent( newParent == null ? null : newParent._visual );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_editableNatureMap.Reset();
		_attackSpaceRoads.Reset();
		_logicRoads.Reset();
		_useRoadsInPathFinding.Reset();
		_segmentCount.Reset();
		_baseA.Reset();
		_baseAOffset.Reset();
		_baseAPercent.Reset();
		_baseB.Reset();
		_baseBOffset.Reset();
		_baseBPercent.Reset();
		_gridStep.Reset();
		_attackSpeed.Reset();
		_overrideSpeed.Reset();
		_visual.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_editableNatureMap.IsDerivedFromParent()
			&& _attackSpaceRoads.IsDerivedFromParent()
			&& _logicRoads.IsDerivedFromParent()
			&& _useRoadsInPathFinding.IsDerivedFromParent()
			&& _segmentCount.IsDerivedFromParent()
			&& _baseA.IsDerivedFromParent()
			&& _baseAOffset.IsDerivedFromParent()
			&& _baseAPercent.IsDerivedFromParent()
			&& _baseB.IsDerivedFromParent()
			&& _baseBOffset.IsDerivedFromParent()
			&& _baseBPercent.IsDerivedFromParent()
			&& _gridStep.IsDerivedFromParent()
			&& _attackSpeed.IsDerivedFromParent()
			&& _overrideSpeed.IsDerivedFromParent()
			&& _visual.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "editableNatureMap" )
			_editableNatureMap.Reset();
		else if ( fieldName == "attackSpaceRoads" )
			_attackSpaceRoads.Reset();
		else if ( fieldName == "logicRoads" )
			_logicRoads.Reset();
		else if ( fieldName == "useRoadsInPathFinding" )
			_useRoadsInPathFinding.Reset();
		else if ( fieldName == "segmentCount" )
			_segmentCount.Reset();
		else if ( fieldName == "baseA" )
			_baseA.Reset();
		else if ( fieldName == "baseAOffset" )
			_baseAOffset.Reset();
		else if ( fieldName == "baseAPercent" )
			_baseAPercent.Reset();
		else if ( fieldName == "baseB" )
			_baseB.Reset();
		else if ( fieldName == "baseBOffset" )
			_baseBOffset.Reset();
		else if ( fieldName == "baseBPercent" )
			_baseBPercent.Reset();
		else if ( fieldName == "gridStep" )
			_gridStep.Reset();
		else if ( fieldName == "attackSpeed" )
			_attackSpeed.Reset();
		else if ( fieldName == "overrideSpeed" )
			_overrideSpeed.Reset();
		else if ( fieldName == "visual" )
			_visual.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "editableNatureMap" )
			return _editableNatureMap.IsDerivedFromParent();
		if ( fieldName == "attackSpaceRoads" )
			return _attackSpaceRoads.IsDerivedFromParent();
		if ( fieldName == "logicRoads" )
			return _logicRoads.IsDerivedFromParent();
		if ( fieldName == "useRoadsInPathFinding" )
			return _useRoadsInPathFinding.IsDerivedFromParent();
		if ( fieldName == "segmentCount" )
			return _segmentCount.IsDerivedFromParent();
		if ( fieldName == "baseA" )
			return _baseA.IsDerivedFromParent();
		if ( fieldName == "baseAOffset" )
			return _baseAOffset.IsDerivedFromParent();
		if ( fieldName == "baseAPercent" )
			return _baseAPercent.IsDerivedFromParent();
		if ( fieldName == "baseB" )
			return _baseB.IsDerivedFromParent();
		if ( fieldName == "baseBOffset" )
			return _baseBOffset.IsDerivedFromParent();
		if ( fieldName == "baseBPercent" )
			return _baseBPercent.IsDerivedFromParent();
		if ( fieldName == "gridStep" )
			return _gridStep.IsDerivedFromParent();
		if ( fieldName == "attackSpeed" )
			return _attackSpeed.IsDerivedFromParent();
		if ( fieldName == "overrideSpeed" )
			return _overrideSpeed.IsDerivedFromParent();
		if ( fieldName == "visual" )
			return _visual.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class GrassLayer : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GrassLayer __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _densityFileName;
	private UndoRedo<int> _bladesPerDensity;
	private UndoRedoDBPtr<GrassMaterial> _material;

	public string densityFileName { get { return _densityFileName.Get(); } set { _densityFileName.Set( value ); } }

	[GenerateChangedEvent]
	public int bladesPerDensity { get { return _bladesPerDensity.Get(); } set { _bladesPerDensity.Set( value ); } }

	[GenerateChangedEvent]
	public DBPtr<GrassMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	public event EventHandler bladesPerDensity_Changed;

	private void Fire_bladesPerDensity_ChangedEvent( object sender, EventArgs e )
	{
		if ( bladesPerDensity_Changed != null ) bladesPerDensity_Changed( sender, e );
	}

	public event EventHandler material_Changed;

	private void Fire_material_ChangedEvent( object sender, EventArgs e )
	{
		if ( material_Changed != null ) material_Changed( sender, e );
	}

	private void Initialize( DBResource owner )
	{
		_densityFileName = new UndoRedo<string>( owner, string.Empty );
		_bladesPerDensity = new UndoRedo<int>( owner, 2 );
		_material = new UndoRedoDBPtr<GrassMaterial>( owner );
		_densityFileName.Changed += FireChangedEvent;
		_bladesPerDensity.Changed += FireChangedEvent;
		_bladesPerDensity.Changed += Fire_bladesPerDensity_ChangedEvent;
		_material.Changed += FireChangedEvent;
		_material.Changed += Fire_material_ChangedEvent;
	}

	public GrassLayer()
	{
		Initialize( GetOwner() );
	}

	public GrassLayer( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GrassLayer( DBResource owner, GrassLayer source )
		: this(owner, source, true){}

	protected GrassLayer( DBResource owner, GrassLayer source, bool fireEvent )
	{
		_densityFileName = new UndoRedo<string>( owner, source.densityFileName );
		_bladesPerDensity = new UndoRedo<int>( owner, source.bladesPerDensity );
		_material = new UndoRedoDBPtr<GrassMaterial>( owner, source.material );
		_densityFileName.Changed += FireChangedEvent;
		_bladesPerDensity.Changed += FireChangedEvent;
		_bladesPerDensity.Changed += Fire_bladesPerDensity_ChangedEvent;
		_material.Changed += FireChangedEvent;
		_material.Changed += Fire_material_ChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GrassLayer source = _source as GrassLayer;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GrassLayer" );
		densityFileName = source.densityFileName;
		bladesPerDensity = source.bladesPerDensity;
		material = source.material;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GrassLayer newParent = _newParent as GrassLayer;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_densityFileName.SetParent( newParent == null ? null : newParent._densityFileName );
		_bladesPerDensity.SetParent( newParent == null ? null : newParent._bladesPerDensity );
		_material.SetParent( newParent == null ? null : newParent._material );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_densityFileName.Reset();
		_bladesPerDensity.Reset();
		_material.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_densityFileName.IsDerivedFromParent()
			&& _bladesPerDensity.IsDerivedFromParent()
			&& _material.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "densityFileName" )
			_densityFileName.Reset();
		else if ( fieldName == "bladesPerDensity" )
			_bladesPerDensity.Reset();
		else if ( fieldName == "material" )
			_material.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "densityFileName" )
			return _densityFileName.IsDerivedFromParent();
		if ( fieldName == "bladesPerDensity" )
			return _bladesPerDensity.IsDerivedFromParent();
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TerrainElementInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TerrainElementInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _position;
	private UndoRedo<float> _angle;
	private Scale _scale;
	private UndoRedoDBPtr<StaticMesh> _terrainObject;
	private UndoRedoDBPtr<Material> _material;

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	[FloatMinMax(0, 360)]
	[GenerateChangedEvent]
	public float angle { get { return _angle.Get(); } set { _angle.Set( value ); } }

	public Scale scale { get { return _scale; } set { _scale.Assign( value ); } }

	[GenerateChangedEvent]
	public DBPtr<StaticMesh> terrainObject { get { return _terrainObject.Get(); } set { _terrainObject.Set( value ); } }

	public DBPtr<Material> material { get { return _material.Get(); } set { _material.Set( value ); } }

	public event EventHandler angle_Changed;

	private void Fire_angle_ChangedEvent( object sender, EventArgs e )
	{
		if ( angle_Changed != null ) angle_Changed( sender, e );
	}

	public event EventHandler terrainObject_Changed;

	private void Fire_terrainObject_ChangedEvent( object sender, EventArgs e )
	{
		if ( terrainObject_Changed != null ) terrainObject_Changed( sender, e );
	}

	private void Initialize( DBResource owner )
	{
		_position = new Vec3( owner );
		_angle = new UndoRedo<float>( owner, 0.0f );
		_scale = new Scale( owner );
		_terrainObject = new UndoRedoDBPtr<StaticMesh>( owner );
		_material = new UndoRedoDBPtr<Material>( owner );
		_position.Changed += FireChangedEvent;
		_angle.Changed += FireChangedEvent;
		_angle.Changed += Fire_angle_ChangedEvent;
		_scale.Changed += FireChangedEvent;
		_terrainObject.Changed += FireChangedEvent;
		_terrainObject.Changed += Fire_terrainObject_ChangedEvent;
		_material.Changed += FireChangedEvent;
	}

	public TerrainElementInstance()
	{
		Initialize( GetOwner() );
	}

	public TerrainElementInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TerrainElementInstance( DBResource owner, TerrainElementInstance source )
		: this(owner, source, true){}

	protected TerrainElementInstance( DBResource owner, TerrainElementInstance source, bool fireEvent )
	{
		_position = new Vec3( owner, source.position );
		_angle = new UndoRedo<float>( owner, source.angle );
		_scale = new Scale( owner, source.scale );
		_terrainObject = new UndoRedoDBPtr<StaticMesh>( owner, source.terrainObject );
		_material = new UndoRedoDBPtr<Material>( owner, source.material );
		_position.Changed += FireChangedEvent;
		_angle.Changed += FireChangedEvent;
		_angle.Changed += Fire_angle_ChangedEvent;
		_scale.Changed += FireChangedEvent;
		_terrainObject.Changed += FireChangedEvent;
		_terrainObject.Changed += Fire_terrainObject_ChangedEvent;
		_material.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TerrainElementInstance source = _source as TerrainElementInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainElementInstance" );
		position = source.position;
		angle = source.angle;
		scale = source.scale;
		terrainObject = source.terrainObject;
		material = source.material;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TerrainElementInstance newParent = _newParent as TerrainElementInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_position.SetParent( newParent == null ? null : newParent._position );
		_angle.SetParent( newParent == null ? null : newParent._angle );
		_scale.SetParent( newParent == null ? null : newParent._scale );
		_terrainObject.SetParent( newParent == null ? null : newParent._terrainObject );
		_material.SetParent( newParent == null ? null : newParent._material );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_position.Reset();
		_angle.Reset();
		_scale.Reset();
		_terrainObject.Reset();
		_material.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_position.IsDerivedFromParent()
			&& _angle.IsDerivedFromParent()
			&& _scale.IsDerivedFromParent()
			&& _terrainObject.IsDerivedFromParent()
			&& _material.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "angle" )
			_angle.Reset();
		else if ( fieldName == "scale" )
			_scale.Reset();
		else if ( fieldName == "terrainObject" )
			_terrainObject.Reset();
		else if ( fieldName == "material" )
			_material.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "angle" )
			return _angle.IsDerivedFromParent();
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
		if ( fieldName == "terrainObject" )
			return _terrainObject.IsDerivedFromParent();
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TerrainGeometry : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TerrainGeometry __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<TerrainElementInstance> _terrainElements;
	private UndoRedo<float> _weldThreshold;
	private UndoRedo<float> _weldLookupSize;

	[Category( "TCV" )]
	[DstFile("tcv_data")]
	public string TCVFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "tcv_data"
	); } }
	[Category( "Terrain elements" )]
	[DstFile("baked_terrain")]
	public string bakedTerrainFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "baked_terrain"
	); } }
	[Category( "Terrain elements" )]
	[DstFile("heightmap")]
	public string heightmapFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "heightmap"
	); } }
	[Category( "Terrain elements" )]
	public libdb.IChangeableList<TerrainElementInstance> terrainElements { get { return _terrainElements; } set { _terrainElements.Assign( value ); } }

	[Category( "Weld parameters" )]
	[Description( "Maximum distance between vertices to be welded." )]
	public float weldThreshold { get { return _weldThreshold.Get(); } set { _weldThreshold.Set( value ); } }

	[Category( "Weld parameters" )]
	[Description( "ширина пограничной зоны патча, в пределах которой ищутся дубликаты вершин. При поиске к ней также добавляется weldThreshold." )]
	public float weldLookupSize { get { return _weldLookupSize.Get(); } set { _weldLookupSize.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_terrainElements = new UndoRedoAssignableList<TerrainElementInstance>( owner );
		_weldThreshold = new UndoRedo<float>( owner, 0.25f );
		_weldLookupSize = new UndoRedo<float>( owner, 2.0f );
		_terrainElements.Changed += FireChangedEvent;
		_weldThreshold.Changed += FireChangedEvent;
		_weldLookupSize.Changed += FireChangedEvent;
	}

	public TerrainGeometry()
	{
		Initialize( GetOwner() );
	}

	public TerrainGeometry( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TerrainGeometry( DBResource owner, TerrainGeometry source )
		: this(owner, source, true){}

	protected TerrainGeometry( DBResource owner, TerrainGeometry source, bool fireEvent )
	{
		_terrainElements = new UndoRedoAssignableList<TerrainElementInstance>( owner );
		_terrainElements.Assign( source.terrainElements );
		_weldThreshold = new UndoRedo<float>( owner, source.weldThreshold );
		_weldLookupSize = new UndoRedo<float>( owner, source.weldLookupSize );
		_terrainElements.Changed += FireChangedEvent;
		_weldThreshold.Changed += FireChangedEvent;
		_weldLookupSize.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TerrainGeometry source = _source as TerrainGeometry;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainGeometry" );
		terrainElements = source.terrainElements;
		weldThreshold = source.weldThreshold;
		weldLookupSize = source.weldLookupSize;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TerrainGeometry newParent = _newParent as TerrainGeometry;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_terrainElements.SetParent( newParent == null ? null : newParent._terrainElements );
		_weldThreshold.SetParent( newParent == null ? null : newParent._weldThreshold );
		_weldLookupSize.SetParent( newParent == null ? null : newParent._weldLookupSize );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_terrainElements.Reset();
		_weldThreshold.Reset();
		_weldLookupSize.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_terrainElements.IsDerivedFromParent()
			&& _weldThreshold.IsDerivedFromParent()
			&& _weldLookupSize.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "terrainElements" )
			_terrainElements.Reset();
		else if ( fieldName == "weldThreshold" )
			_weldThreshold.Reset();
		else if ( fieldName == "weldLookupSize" )
			_weldLookupSize.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "terrainElements" )
			return _terrainElements.IsDerivedFromParent();
		if ( fieldName == "weldThreshold" )
			return _weldThreshold.IsDerivedFromParent();
		if ( fieldName == "weldLookupSize" )
			return _weldLookupSize.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TerrainLayer : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TerrainLayer __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<TerrainTypeInfo> _pTerrainType;

	[GenerateChangedEvent]
	public DBPtr<TerrainTypeInfo> pTerrainType { get { return _pTerrainType.Get(); } set { _pTerrainType.Set( value ); } }

	public event EventHandler pTerrainType_Changed;

	private void Fire_pTerrainType_ChangedEvent( object sender, EventArgs e )
	{
		if ( pTerrainType_Changed != null ) pTerrainType_Changed( sender, e );
	}

	private void Initialize( DBResource owner )
	{
		_pTerrainType = new UndoRedoDBPtr<TerrainTypeInfo>( owner );
		_pTerrainType.Changed += FireChangedEvent;
		_pTerrainType.Changed += Fire_pTerrainType_ChangedEvent;
	}

	public TerrainLayer()
	{
		Initialize( GetOwner() );
	}

	public TerrainLayer( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TerrainLayer( DBResource owner, TerrainLayer source )
		: this(owner, source, true){}

	protected TerrainLayer( DBResource owner, TerrainLayer source, bool fireEvent )
	{
		_pTerrainType = new UndoRedoDBPtr<TerrainTypeInfo>( owner, source.pTerrainType );
		_pTerrainType.Changed += FireChangedEvent;
		_pTerrainType.Changed += Fire_pTerrainType_ChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TerrainLayer source = _source as TerrainLayer;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainLayer" );
		pTerrainType = source.pTerrainType;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TerrainLayer newParent = _newParent as TerrainLayer;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_pTerrainType.SetParent( newParent == null ? null : newParent._pTerrainType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_pTerrainType.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_pTerrainType.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "pTerrainType" )
			_pTerrainType.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "pTerrainType" )
			return _pTerrainType.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TerrainLayers : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TerrainLayers __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<TerrainLayer> _terrainLayers;

	public libdb.IChangeableList<TerrainLayer> terrainLayers { get { return _terrainLayers; } set { _terrainLayers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_terrainLayers = new UndoRedoAssignableList<TerrainLayer>( owner );
		_terrainLayers.Changed += FireChangedEvent;
	}

	public TerrainLayers()
	{
		Initialize( GetOwner() );
	}

	public TerrainLayers( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TerrainLayers( DBResource owner, TerrainLayers source )
		: this(owner, source, true){}

	protected TerrainLayers( DBResource owner, TerrainLayers source, bool fireEvent )
	{
		_terrainLayers = new UndoRedoAssignableList<TerrainLayer>( owner );
		_terrainLayers.Assign( source.terrainLayers );
		_terrainLayers.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TerrainLayers source = _source as TerrainLayers;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainLayers" );
		terrainLayers = source.terrainLayers;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TerrainLayers newParent = _newParent as TerrainLayers;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_terrainLayers.SetParent( newParent == null ? null : newParent._terrainLayers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_terrainLayers.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_terrainLayers.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "terrainLayers" )
			_terrainLayers.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "terrainLayers" )
			return _terrainLayers.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[UseTypeName("TERN")]
public class Terrain : DBResource
{
	private UndoRedoDBPtr<Terrain> ___parent;
	[HideInOutliner]
	public new DBPtr<Terrain> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _elemXCount;
	private UndoRedo<int> _elemYCount;
	private UndoRedo<int> _tilesPerElement;
	private DBNatureMap _natureMap;
	private TerrainGeometry _geometry;
	private TerrainLayers _layers;
	private UndoRedoAssignableList<GrassLayer> _grassLayers;

	public int elemXCount { get { return _elemXCount.Get(); } set { _elemXCount.Set( value ); } }

	public int elemYCount { get { return _elemYCount.Get(); } set { _elemYCount.Set( value ); } }

	public int tilesPerElement { get { return _tilesPerElement.Get(); } set { _tilesPerElement.Set( value ); } }

	[DstFile("layer_mask")]
	public string layerMaskFile { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "layer_mask"
	); } }
	public DBNatureMap natureMap { get { return _natureMap; } set { _natureMap.Assign( value ); } }

	public TerrainGeometry geometry { get { return _geometry; } set { _geometry.Assign( value ); } }

	public TerrainLayers layers { get { return _layers; } set { _layers.Assign( value ); } }

	public libdb.IChangeableList<GrassLayer> grassLayers { get { return _grassLayers; } set { _grassLayers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Terrain>(owner);
		_elemXCount = new UndoRedo<int>( owner, 32 );
		_elemYCount = new UndoRedo<int>( owner, 32 );
		_tilesPerElement = new UndoRedo<int>( owner, 4 );
		_natureMap = new DBNatureMap( owner );
		_geometry = new TerrainGeometry( owner );
		_layers = new TerrainLayers( owner );
		_grassLayers = new UndoRedoAssignableList<GrassLayer>( owner );
		___parent.Changed += FireChangedEvent;
		_elemXCount.Changed += FireChangedEvent;
		_elemYCount.Changed += FireChangedEvent;
		_tilesPerElement.Changed += FireChangedEvent;
		_natureMap.Changed += FireChangedEvent;
		_geometry.Changed += FireChangedEvent;
		_layers.Changed += FireChangedEvent;
		_grassLayers.Changed += FireChangedEvent;
	}

	public Terrain()
	{
		Initialize( this );
	}
	private void AssignSelf( Terrain source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Terrain" );
		elemXCount = source.elemXCount;
		elemYCount = source.elemYCount;
		tilesPerElement = source.tilesPerElement;
		natureMap = source.natureMap;
		geometry = source.geometry;
		layers = source.layers;
		grassLayers = source.grassLayers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Terrain source = _source as Terrain;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Terrain" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Terrain newParent = rawParent == null ? null : rawParent.Get<Terrain>();
		if ( newParent == null && _newParent is Terrain )
			newParent = _newParent as Terrain;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_elemXCount.SetParent( newParent == null ? null : newParent._elemXCount );
		_elemYCount.SetParent( newParent == null ? null : newParent._elemYCount );
		_tilesPerElement.SetParent( newParent == null ? null : newParent._tilesPerElement );
		_natureMap.SetParent( newParent == null ? null : newParent._natureMap );
		_geometry.SetParent( newParent == null ? null : newParent._geometry );
		_layers.SetParent( newParent == null ? null : newParent._layers );
		_grassLayers.SetParent( newParent == null ? null : newParent._grassLayers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_elemXCount.Reset();
		_elemYCount.Reset();
		_tilesPerElement.Reset();
		_natureMap.Reset();
		_geometry.Reset();
		_layers.Reset();
		_grassLayers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_elemXCount.IsDerivedFromParent()
			&& _elemYCount.IsDerivedFromParent()
			&& _tilesPerElement.IsDerivedFromParent()
			&& _natureMap.IsDerivedFromParent()
			&& _geometry.IsDerivedFromParent()
			&& _layers.IsDerivedFromParent()
			&& _grassLayers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "elemXCount" )
			_elemXCount.Reset();
		else if ( fieldName == "elemYCount" )
			_elemYCount.Reset();
		else if ( fieldName == "tilesPerElement" )
			_tilesPerElement.Reset();
		else if ( fieldName == "natureMap" )
			_natureMap.Reset();
		else if ( fieldName == "geometry" )
			_geometry.Reset();
		else if ( fieldName == "layers" )
			_layers.Reset();
		else if ( fieldName == "grassLayers" )
			_grassLayers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "elemXCount" )
			return _elemXCount.IsDerivedFromParent();
		if ( fieldName == "elemYCount" )
			return _elemYCount.IsDerivedFromParent();
		if ( fieldName == "tilesPerElement" )
			return _tilesPerElement.IsDerivedFromParent();
		if ( fieldName == "natureMap" )
			return _natureMap.IsDerivedFromParent();
		if ( fieldName == "geometry" )
			return _geometry.IsDerivedFromParent();
		if ( fieldName == "layers" )
			return _layers.IsDerivedFromParent();
		if ( fieldName == "grassLayers" )
			return _grassLayers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
public class TerrainTypeInfo : DBResource
{
	private UndoRedoDBPtr<TerrainTypeInfo> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainTypeInfo> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TerrainMaterial> _pDBMaterial;

	public DBPtr<TerrainMaterial> pDBMaterial { get { return _pDBMaterial.Get(); } set { _pDBMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainTypeInfo>(owner);
		_pDBMaterial = new UndoRedoDBPtr<TerrainMaterial>( owner );
		___parent.Changed += FireChangedEvent;
		_pDBMaterial.Changed += FireChangedEvent;
	}

	public TerrainTypeInfo()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainTypeInfo source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainTypeInfo" );
		pDBMaterial = source.pDBMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainTypeInfo source = _source as TerrainTypeInfo;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainTypeInfo" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainTypeInfo newParent = rawParent == null ? null : rawParent.Get<TerrainTypeInfo>();
		if ( newParent == null && _newParent is TerrainTypeInfo )
			newParent = _newParent as TerrainTypeInfo;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_pDBMaterial.SetParent( newParent == null ? null : newParent._pDBMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_pDBMaterial.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_pDBMaterial.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "pDBMaterial" )
			_pDBMaterial.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "pDBMaterial" )
			return _pDBMaterial.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
