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
public enum EAnGrMarkerOwner
{
	ANGRM_NODE = 0,
	ANGRM_TRANSACTION = 1,
};

public enum EAnGrNodeType
{
	Normal = 0,
	Dispatcher = 1,
	SubNode = 2,
};

public enum EAnGrTransactionKind
{
	Uniform = 0,
	Parabolic3 = 1,
	RecParabolic3 = 2,
	Sine = 3,
	RecSine = 4,
	Spline = 5,
	RecSpline = 6,
};

public enum EAnGrTransactionUpdate
{
	PoseToPose = 0,
	AnimToPose = 1,
	PoseToAnim = 2,
	AnimToAnim = 3,
};

[Flags]
public enum EGeometryUsageFlags
{
	None = 0,
	Lighting = 1,
	NormalMapping = 2,
	VertexColors = 4,
};

public enum MipLevel
{
	AutoGenerate = 0,
	NoMips = 1,
};

public enum TextureType
{
	Color = 0,
	Normal = 1,
};

public class AABB : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AABB __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minX;
	private UndoRedo<float> _maxX;
	private UndoRedo<float> _minY;
	private UndoRedo<float> _maxY;
	private UndoRedo<float> _minZ;
	private UndoRedo<float> _maxZ;

	public float minX { get { return _minX.Get(); } set { _minX.Set( value ); } }

	public float maxX { get { return _maxX.Get(); } set { _maxX.Set( value ); } }

	public float minY { get { return _minY.Get(); } set { _minY.Set( value ); } }

	public float maxY { get { return _maxY.Get(); } set { _maxY.Set( value ); } }

	public float minZ { get { return _minZ.Get(); } set { _minZ.Set( value ); } }

	public float maxZ { get { return _maxZ.Get(); } set { _maxZ.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minX = new UndoRedo<float>( owner, 0.0f );
		_maxX = new UndoRedo<float>( owner, 0.0f );
		_minY = new UndoRedo<float>( owner, 0.0f );
		_maxY = new UndoRedo<float>( owner, 0.0f );
		_minZ = new UndoRedo<float>( owner, 0.0f );
		_maxZ = new UndoRedo<float>( owner, 0.0f );
		_minX.Changed += FireChangedEvent;
		_maxX.Changed += FireChangedEvent;
		_minY.Changed += FireChangedEvent;
		_maxY.Changed += FireChangedEvent;
		_minZ.Changed += FireChangedEvent;
		_maxZ.Changed += FireChangedEvent;
	}

	public AABB()
	{
		Initialize( GetOwner() );
	}

	public AABB( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AABB( DBResource owner, AABB source )
		: this(owner, source, true){}

	protected AABB( DBResource owner, AABB source, bool fireEvent )
	{
		_minX = new UndoRedo<float>( owner, source.minX );
		_maxX = new UndoRedo<float>( owner, source.maxX );
		_minY = new UndoRedo<float>( owner, source.minY );
		_maxY = new UndoRedo<float>( owner, source.maxY );
		_minZ = new UndoRedo<float>( owner, source.minZ );
		_maxZ = new UndoRedo<float>( owner, source.maxZ );
		_minX.Changed += FireChangedEvent;
		_maxX.Changed += FireChangedEvent;
		_minY.Changed += FireChangedEvent;
		_maxY.Changed += FireChangedEvent;
		_minZ.Changed += FireChangedEvent;
		_maxZ.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AABB source = _source as AABB;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AABB" );
		minX = source.minX;
		maxX = source.maxX;
		minY = source.minY;
		maxY = source.maxY;
		minZ = source.minZ;
		maxZ = source.maxZ;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AABB newParent = _newParent as AABB;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minX.SetParent( newParent == null ? null : newParent._minX );
		_maxX.SetParent( newParent == null ? null : newParent._maxX );
		_minY.SetParent( newParent == null ? null : newParent._minY );
		_maxY.SetParent( newParent == null ? null : newParent._maxY );
		_minZ.SetParent( newParent == null ? null : newParent._minZ );
		_maxZ.SetParent( newParent == null ? null : newParent._maxZ );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minX.Reset();
		_maxX.Reset();
		_minY.Reset();
		_maxY.Reset();
		_minZ.Reset();
		_maxZ.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minX.IsDerivedFromParent()
			&& _maxX.IsDerivedFromParent()
			&& _minY.IsDerivedFromParent()
			&& _maxY.IsDerivedFromParent()
			&& _minZ.IsDerivedFromParent()
			&& _maxZ.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minX" )
			_minX.Reset();
		else if ( fieldName == "maxX" )
			_maxX.Reset();
		else if ( fieldName == "minY" )
			_minY.Reset();
		else if ( fieldName == "maxY" )
			_maxY.Reset();
		else if ( fieldName == "minZ" )
			_minZ.Reset();
		else if ( fieldName == "maxZ" )
			_maxZ.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minX" )
			return _minX.IsDerivedFromParent();
		if ( fieldName == "maxX" )
			return _maxX.IsDerivedFromParent();
		if ( fieldName == "minY" )
			return _minY.IsDerivedFromParent();
		if ( fieldName == "maxY" )
			return _maxY.IsDerivedFromParent();
		if ( fieldName == "minZ" )
			return _minZ.IsDerivedFromParent();
		if ( fieldName == "maxZ" )
			return _maxZ.IsDerivedFromParent();
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

public class AnGrExternalParameter : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrExternalParameter __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _paramName;
	private UndoRedo<float> _defaultValue;

	[Description( "Name of the external parameter" )]
	public string paramName { get { return _paramName.Get(); } set { _paramName.Set( value ); } }

	[Description( "Default value" )]
	public float defaultValue { get { return _defaultValue.Get(); } set { _defaultValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_paramName = new UndoRedo<string>( owner, "CHANGE_NAME!" );
		_defaultValue = new UndoRedo<float>( owner, 0.0f );
		_paramName.Changed += FireChangedEvent;
		_defaultValue.Changed += FireChangedEvent;
	}

	public AnGrExternalParameter()
	{
		Initialize( GetOwner() );
	}

	public AnGrExternalParameter( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrExternalParameter( DBResource owner, AnGrExternalParameter source )
		: this(owner, source, true){}

	protected AnGrExternalParameter( DBResource owner, AnGrExternalParameter source, bool fireEvent )
	{
		_paramName = new UndoRedo<string>( owner, source.paramName );
		_defaultValue = new UndoRedo<float>( owner, source.defaultValue );
		_paramName.Changed += FireChangedEvent;
		_defaultValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrExternalParameter source = _source as AnGrExternalParameter;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrExternalParameter" );
		paramName = source.paramName;
		defaultValue = source.defaultValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrExternalParameter newParent = _newParent as AnGrExternalParameter;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_paramName.SetParent( newParent == null ? null : newParent._paramName );
		_defaultValue.SetParent( newParent == null ? null : newParent._defaultValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_paramName.Reset();
		_defaultValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_paramName.IsDerivedFromParent()
			&& _defaultValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "paramName" )
			_paramName.Reset();
		else if ( fieldName == "defaultValue" )
			_defaultValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "paramName" )
			return _paramName.IsDerivedFromParent();
		if ( fieldName == "defaultValue" )
			return _defaultValue.IsDerivedFromParent();
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

public class AnGrExternalParameterCoeff : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrExternalParameterCoeff __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<float> _value;

	[Description( "Name of the external parameter" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[Description( "Default value" )]
	public float value { get { return _value.Get(); } set { _value.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_value = new UndoRedo<float>( owner, 1.0f );
		_name.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
	}

	public AnGrExternalParameterCoeff()
	{
		Initialize( GetOwner() );
	}

	public AnGrExternalParameterCoeff( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrExternalParameterCoeff( DBResource owner, AnGrExternalParameterCoeff source )
		: this(owner, source, true){}

	protected AnGrExternalParameterCoeff( DBResource owner, AnGrExternalParameterCoeff source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_value = new UndoRedo<float>( owner, source.value );
		_name.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrExternalParameterCoeff source = _source as AnGrExternalParameterCoeff;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrExternalParameterCoeff" );
		name = source.name;
		value = source.value;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrExternalParameterCoeff newParent = _newParent as AnGrExternalParameterCoeff;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_value.SetParent( newParent == null ? null : newParent._value );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_value.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
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

public class AnGrFormula : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrFormula __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _value;
	private UndoRedoAssignableList<AnGrExternalParameterCoeff> _coeffs;

	public float value { get { return _value.Get(); } set { _value.Set( value ); } }

	public libdb.IChangeableList<AnGrExternalParameterCoeff> coeffs { get { return _coeffs; } set { _coeffs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_value = new UndoRedo<float>( owner, 0.0f );
		_coeffs = new UndoRedoAssignableList<AnGrExternalParameterCoeff>( owner );
		_value.Changed += FireChangedEvent;
		_coeffs.Changed += FireChangedEvent;
	}

	public AnGrFormula()
	{
		Initialize( GetOwner() );
	}

	public AnGrFormula( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrFormula( DBResource owner, AnGrFormula source )
		: this(owner, source, true){}

	protected AnGrFormula( DBResource owner, AnGrFormula source, bool fireEvent )
	{
		_value = new UndoRedo<float>( owner, source.value );
		_coeffs = new UndoRedoAssignableList<AnGrExternalParameterCoeff>( owner );
		_coeffs.Assign( source.coeffs );
		_value.Changed += FireChangedEvent;
		_coeffs.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrFormula source = _source as AnGrFormula;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrFormula" );
		value = source.value;
		coeffs = source.coeffs;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrFormula newParent = _newParent as AnGrFormula;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_value.SetParent( newParent == null ? null : newParent._value );
		_coeffs.SetParent( newParent == null ? null : newParent._coeffs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_value.Reset();
		_coeffs.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_value.IsDerivedFromParent()
			&& _coeffs.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "coeffs" )
			_coeffs.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "coeffs" )
			return _coeffs.IsDerivedFromParent();
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

public class AnGrMarker : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrMarker __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<float> _virtPar;

	[Description( "Name of the marker" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[Description( "Virtual parameter of the marker: in [0..1]" )]
	public float virtPar { get { return _virtPar.Get(); } set { _virtPar.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, "newmarker" );
		_virtPar = new UndoRedo<float>( owner, 0.0f );
		_name.Changed += FireChangedEvent;
		_virtPar.Changed += FireChangedEvent;
	}

	public AnGrMarker()
	{
		Initialize( GetOwner() );
	}

	public AnGrMarker( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrMarker( DBResource owner, AnGrMarker source )
		: this(owner, source, true){}

	protected AnGrMarker( DBResource owner, AnGrMarker source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_virtPar = new UndoRedo<float>( owner, source.virtPar );
		_name.Changed += FireChangedEvent;
		_virtPar.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrMarker source = _source as AnGrMarker;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrMarker" );
		name = source.name;
		virtPar = source.virtPar;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrMarker newParent = _newParent as AnGrMarker;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_virtPar.SetParent( newParent == null ? null : newParent._virtPar );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_virtPar.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _virtPar.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "virtPar" )
			_virtPar.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "virtPar" )
			return _virtPar.IsDerivedFromParent();
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

public class AnGrFlTransaction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrFlTransaction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EAnGrTransactionUpdate> _blending;
	private UndoRedo<EAnGrTransactionKind> _kind;
	private AnGrFormula _parA;
	private AnGrFormula _parB;
	private AnGrFormula _fromMin;
	private AnGrFormula _fromMax;
	private AnGrFormula _toParam;
	private UndoRedo<float> _duration;
	private UndoRedoAssignableList<AnGrMarker> _markers;

	[Description( "Type of float transaction update" )]
	[ReadOnly( true )]
	public EAnGrTransactionUpdate blending { get { return _blending.Get(); } set { _blending.Set( value ); } }

	[Description( "Kind of transaction" )]
	[ReadOnly( true )]
	public EAnGrTransactionKind kind { get { return _kind.Get(); } set { _kind.Set( value ); } }

	[Description( "Parameter 1" )]
	[ReadOnly( true )]
	public AnGrFormula parA { get { return _parA; } set { _parA.Assign( value ); } }

	[Description( "Parameter 2" )]
	[ReadOnly( true )]
	public AnGrFormula parB { get { return _parB; } set { _parB.Assign( value ); } }

	[Description( "Start parameter of interval" )]
	[ReadOnly( true )]
	public AnGrFormula fromMin { get { return _fromMin; } set { _fromMin.Assign( value ); } }

	[Description( "Stop parameter of interval" )]
	[ReadOnly( true )]
	public AnGrFormula fromMax { get { return _fromMax; } set { _fromMax.Assign( value ); } }

	[Description( "Destination virtPar of target node" )]
	[ReadOnly( true )]
	public AnGrFormula toParam { get { return _toParam; } set { _toParam.Assign( value ); } }

	[Description( "Transaction speed in seconds" )]
	[ReadOnly( true )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	public libdb.IChangeableList<AnGrMarker> markers { get { return _markers; } set { _markers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_blending = new UndoRedo<EAnGrTransactionUpdate>( owner, EAnGrTransactionUpdate.PoseToAnim );
		_kind = new UndoRedo<EAnGrTransactionKind>( owner, EAnGrTransactionKind.Uniform );
		_parA = new AnGrFormula( owner );
		_parB = new AnGrFormula( owner );
		_fromMin = new AnGrFormula( owner );
		_fromMax = new AnGrFormula( owner );
		_toParam = new AnGrFormula( owner );
		_duration = new UndoRedo<float>( owner, 0.3f );
		_markers = new UndoRedoAssignableList<AnGrMarker>( owner );
		_blending.Changed += FireChangedEvent;
		_kind.Changed += FireChangedEvent;
		_parA.Changed += FireChangedEvent;
		_parB.Changed += FireChangedEvent;
		_fromMin.Changed += FireChangedEvent;
		_fromMax.Changed += FireChangedEvent;
		_toParam.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_markers.Changed += FireChangedEvent;
	}

	public AnGrFlTransaction()
	{
		Initialize( GetOwner() );
	}

	public AnGrFlTransaction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrFlTransaction( DBResource owner, AnGrFlTransaction source )
		: this(owner, source, true){}

	protected AnGrFlTransaction( DBResource owner, AnGrFlTransaction source, bool fireEvent )
	{
		_blending = new UndoRedo<EAnGrTransactionUpdate>( owner, source.blending );
		_kind = new UndoRedo<EAnGrTransactionKind>( owner, source.kind );
		_parA = new AnGrFormula( owner, source.parA );
		_parB = new AnGrFormula( owner, source.parB );
		_fromMin = new AnGrFormula( owner, source.fromMin );
		_fromMax = new AnGrFormula( owner, source.fromMax );
		_toParam = new AnGrFormula( owner, source.toParam );
		_duration = new UndoRedo<float>( owner, source.duration );
		_markers = new UndoRedoAssignableList<AnGrMarker>( owner );
		_markers.Assign( source.markers );
		_blending.Changed += FireChangedEvent;
		_kind.Changed += FireChangedEvent;
		_parA.Changed += FireChangedEvent;
		_parB.Changed += FireChangedEvent;
		_fromMin.Changed += FireChangedEvent;
		_fromMax.Changed += FireChangedEvent;
		_toParam.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_markers.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrFlTransaction source = _source as AnGrFlTransaction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrFlTransaction" );
		blending = source.blending;
		kind = source.kind;
		parA = source.parA;
		parB = source.parB;
		fromMin = source.fromMin;
		fromMax = source.fromMax;
		toParam = source.toParam;
		duration = source.duration;
		markers = source.markers;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrFlTransaction newParent = _newParent as AnGrFlTransaction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_blending.SetParent( newParent == null ? null : newParent._blending );
		_kind.SetParent( newParent == null ? null : newParent._kind );
		_parA.SetParent( newParent == null ? null : newParent._parA );
		_parB.SetParent( newParent == null ? null : newParent._parB );
		_fromMin.SetParent( newParent == null ? null : newParent._fromMin );
		_fromMax.SetParent( newParent == null ? null : newParent._fromMax );
		_toParam.SetParent( newParent == null ? null : newParent._toParam );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_markers.SetParent( newParent == null ? null : newParent._markers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_blending.Reset();
		_kind.Reset();
		_parA.Reset();
		_parB.Reset();
		_fromMin.Reset();
		_fromMax.Reset();
		_toParam.Reset();
		_duration.Reset();
		_markers.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_blending.IsDerivedFromParent()
			&& _kind.IsDerivedFromParent()
			&& _parA.IsDerivedFromParent()
			&& _parB.IsDerivedFromParent()
			&& _fromMin.IsDerivedFromParent()
			&& _fromMax.IsDerivedFromParent()
			&& _toParam.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _markers.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "blending" )
			_blending.Reset();
		else if ( fieldName == "kind" )
			_kind.Reset();
		else if ( fieldName == "parA" )
			_parA.Reset();
		else if ( fieldName == "parB" )
			_parB.Reset();
		else if ( fieldName == "fromMin" )
			_fromMin.Reset();
		else if ( fieldName == "fromMax" )
			_fromMax.Reset();
		else if ( fieldName == "toParam" )
			_toParam.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "markers" )
			_markers.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "blending" )
			return _blending.IsDerivedFromParent();
		if ( fieldName == "kind" )
			return _kind.IsDerivedFromParent();
		if ( fieldName == "parA" )
			return _parA.IsDerivedFromParent();
		if ( fieldName == "parB" )
			return _parB.IsDerivedFromParent();
		if ( fieldName == "fromMin" )
			return _fromMin.IsDerivedFromParent();
		if ( fieldName == "fromMax" )
			return _fromMax.IsDerivedFromParent();
		if ( fieldName == "toParam" )
			return _toParam.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "markers" )
			return _markers.IsDerivedFromParent();
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

[TypeId(0x14591F84)]
[UseTypeName("AGFT")]
public class AnGrFlMultiTransaction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrFlMultiTransaction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _targetNode;
	private UndoRedo<float> _probability;
	private AnGrFlTransaction _parameters;

	[Description( "Target node" )]
	[ReadOnly( true )]
	public string targetNode { get { return _targetNode.Get(); } set { _targetNode.Set( value ); } }

	[Description( "Probability" )]
	[ReadOnly( true )]
	public float probability { get { return _probability.Get(); } set { _probability.Set( value ); } }

	public AnGrFlTransaction parameters { get { return _parameters; } set { _parameters.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_targetNode = new UndoRedo<string>( owner, string.Empty );
		_probability = new UndoRedo<float>( owner, 0.0f );
		_parameters = new AnGrFlTransaction( owner );
		_targetNode.Changed += FireChangedEvent;
		_probability.Changed += FireChangedEvent;
		_parameters.Changed += FireChangedEvent;
	}

	public AnGrFlMultiTransaction()
	{
		Initialize( GetOwner() );
	}

	public AnGrFlMultiTransaction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrFlMultiTransaction( DBResource owner, AnGrFlMultiTransaction source )
		: this(owner, source, true){}

	protected AnGrFlMultiTransaction( DBResource owner, AnGrFlMultiTransaction source, bool fireEvent )
	{
		_targetNode = new UndoRedo<string>( owner, source.targetNode );
		_probability = new UndoRedo<float>( owner, source.probability );
		_parameters = new AnGrFlTransaction( owner, source.parameters );
		_targetNode.Changed += FireChangedEvent;
		_probability.Changed += FireChangedEvent;
		_parameters.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrFlMultiTransaction source = _source as AnGrFlMultiTransaction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrFlMultiTransaction" );
		targetNode = source.targetNode;
		probability = source.probability;
		parameters = source.parameters;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrFlMultiTransaction newParent = _newParent as AnGrFlMultiTransaction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_targetNode.SetParent( newParent == null ? null : newParent._targetNode );
		_probability.SetParent( newParent == null ? null : newParent._probability );
		_parameters.SetParent( newParent == null ? null : newParent._parameters );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_targetNode.Reset();
		_probability.Reset();
		_parameters.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_targetNode.IsDerivedFromParent()
			&& _probability.IsDerivedFromParent()
			&& _parameters.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "targetNode" )
			_targetNode.Reset();
		else if ( fieldName == "probability" )
			_probability.Reset();
		else if ( fieldName == "parameters" )
			_parameters.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "targetNode" )
			return _targetNode.IsDerivedFromParent();
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
		if ( fieldName == "parameters" )
			return _parameters.IsDerivedFromParent();
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

public class AnGrMacronode : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnGrMacronode __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _nodeName;
	private UndoRedo<EAnGrNodeType> _nodeType;
	private UndoRedo<string> _nextNode;
	private UndoRedo<float> _surfSpeedX;
	private UndoRedo<float> _surfSpeedY;
	private UndoRedo<string> _sequenceName;
	private AnGrFormula _startPar;
	private AnGrFormula _stopPar;
	private AnGrFormula _speed;
	private UndoRedoAssignableList<AnGrFlMultiTransaction> _simpleTransactions;
	private UndoRedo<int> _posX;
	private UndoRedo<int> _posY;
	private UndoRedoAssignableList<AnGrMarker> _markers;

	[Description( "Name of the node" )]
	[ReadOnly( true )]
	public string nodeName { get { return _nodeName.Get(); } set { _nodeName.Set( value ); } }

	[Description( "Type of this node" )]
	[ReadOnly( true )]
	public EAnGrNodeType nodeType { get { return _nodeType.Get(); } set { _nodeType.Set( value ); } }

	[Description( "Default next node name (can be this node ==> node is looped)" )]
	[ReadOnly( true )]
	public string nextNode { get { return _nextNode.Get(); } set { _nextNode.Set( value ); } }

	[Description( "Speed of the surface for this node" )]
	[ReadOnly( true )]
	public float surfSpeedX { get { return _surfSpeedX.Get(); } set { _surfSpeedX.Set( value ); } }

	[Description( "Speed of the surface for this node" )]
	[ReadOnly( true )]
	public float surfSpeedY { get { return _surfSpeedY.Get(); } set { _surfSpeedY.Set( value ); } }

	[Description( "Name of animation" )]
	[ReadOnly( true )]
	public string sequenceName { get { return _sequenceName.Get(); } set { _sequenceName.Set( value ); } }

	[Description( "Start VPar of animation" )]
	[ReadOnly( true )]
	public AnGrFormula startPar { get { return _startPar; } set { _startPar.Assign( value ); } }

	[Description( "Stop VPar of animation" )]
	[ReadOnly( true )]
	public AnGrFormula stopPar { get { return _stopPar; } set { _stopPar.Assign( value ); } }

	[Description( "Sequence speed" )]
	[ReadOnly( true )]
	public AnGrFormula speed { get { return _speed; } set { _speed.Assign( value ); } }

	[ReadOnly( true )]
	public libdb.IChangeableList<AnGrFlMultiTransaction> simpleTransactions { get { return _simpleTransactions; } set { _simpleTransactions.Assign( value ); } }

	[Description( "X-position of node" )]
	[ReadOnly( true )]
	public int posX { get { return _posX.Get(); } set { _posX.Set( value ); } }

	[Description( "Y-position of node" )]
	[ReadOnly( true )]
	public int posY { get { return _posY.Get(); } set { _posY.Set( value ); } }

	public libdb.IChangeableList<AnGrMarker> markers { get { return _markers; } set { _markers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_nodeName = new UndoRedo<string>( owner, string.Empty );
		_nodeType = new UndoRedo<EAnGrNodeType>( owner, EAnGrNodeType.Normal );
		_nextNode = new UndoRedo<string>( owner, string.Empty );
		_surfSpeedX = new UndoRedo<float>( owner, 0.0f );
		_surfSpeedY = new UndoRedo<float>( owner, 0.0f );
		_sequenceName = new UndoRedo<string>( owner, string.Empty );
		_startPar = new AnGrFormula( owner );
		_stopPar = new AnGrFormula( owner );
		_speed = new AnGrFormula( owner );
		_simpleTransactions = new UndoRedoAssignableList<AnGrFlMultiTransaction>( owner );
		_posX = new UndoRedo<int>( owner, -1 );
		_posY = new UndoRedo<int>( owner, -1 );
		_markers = new UndoRedoAssignableList<AnGrMarker>( owner );
		_nodeName.Changed += FireChangedEvent;
		_nodeType.Changed += FireChangedEvent;
		_nextNode.Changed += FireChangedEvent;
		_surfSpeedX.Changed += FireChangedEvent;
		_surfSpeedY.Changed += FireChangedEvent;
		_sequenceName.Changed += FireChangedEvent;
		_startPar.Changed += FireChangedEvent;
		_stopPar.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_simpleTransactions.Changed += FireChangedEvent;
		_posX.Changed += FireChangedEvent;
		_posY.Changed += FireChangedEvent;
		_markers.Changed += FireChangedEvent;
	}

	public AnGrMacronode()
	{
		Initialize( GetOwner() );
	}

	public AnGrMacronode( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnGrMacronode( DBResource owner, AnGrMacronode source )
		: this(owner, source, true){}

	protected AnGrMacronode( DBResource owner, AnGrMacronode source, bool fireEvent )
	{
		_nodeName = new UndoRedo<string>( owner, source.nodeName );
		_nodeType = new UndoRedo<EAnGrNodeType>( owner, source.nodeType );
		_nextNode = new UndoRedo<string>( owner, source.nextNode );
		_surfSpeedX = new UndoRedo<float>( owner, source.surfSpeedX );
		_surfSpeedY = new UndoRedo<float>( owner, source.surfSpeedY );
		_sequenceName = new UndoRedo<string>( owner, source.sequenceName );
		_startPar = new AnGrFormula( owner, source.startPar );
		_stopPar = new AnGrFormula( owner, source.stopPar );
		_speed = new AnGrFormula( owner, source.speed );
		_simpleTransactions = new UndoRedoAssignableList<AnGrFlMultiTransaction>( owner );
		_simpleTransactions.Assign( source.simpleTransactions );
		_posX = new UndoRedo<int>( owner, source.posX );
		_posY = new UndoRedo<int>( owner, source.posY );
		_markers = new UndoRedoAssignableList<AnGrMarker>( owner );
		_markers.Assign( source.markers );
		_nodeName.Changed += FireChangedEvent;
		_nodeType.Changed += FireChangedEvent;
		_nextNode.Changed += FireChangedEvent;
		_surfSpeedX.Changed += FireChangedEvent;
		_surfSpeedY.Changed += FireChangedEvent;
		_sequenceName.Changed += FireChangedEvent;
		_startPar.Changed += FireChangedEvent;
		_stopPar.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_simpleTransactions.Changed += FireChangedEvent;
		_posX.Changed += FireChangedEvent;
		_posY.Changed += FireChangedEvent;
		_markers.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnGrMacronode source = _source as AnGrMacronode;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnGrMacronode" );
		nodeName = source.nodeName;
		nodeType = source.nodeType;
		nextNode = source.nextNode;
		surfSpeedX = source.surfSpeedX;
		surfSpeedY = source.surfSpeedY;
		sequenceName = source.sequenceName;
		startPar = source.startPar;
		stopPar = source.stopPar;
		speed = source.speed;
		simpleTransactions = source.simpleTransactions;
		posX = source.posX;
		posY = source.posY;
		markers = source.markers;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnGrMacronode newParent = _newParent as AnGrMacronode;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_nodeName.SetParent( newParent == null ? null : newParent._nodeName );
		_nodeType.SetParent( newParent == null ? null : newParent._nodeType );
		_nextNode.SetParent( newParent == null ? null : newParent._nextNode );
		_surfSpeedX.SetParent( newParent == null ? null : newParent._surfSpeedX );
		_surfSpeedY.SetParent( newParent == null ? null : newParent._surfSpeedY );
		_sequenceName.SetParent( newParent == null ? null : newParent._sequenceName );
		_startPar.SetParent( newParent == null ? null : newParent._startPar );
		_stopPar.SetParent( newParent == null ? null : newParent._stopPar );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_simpleTransactions.SetParent( newParent == null ? null : newParent._simpleTransactions );
		_posX.SetParent( newParent == null ? null : newParent._posX );
		_posY.SetParent( newParent == null ? null : newParent._posY );
		_markers.SetParent( newParent == null ? null : newParent._markers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_nodeName.Reset();
		_nodeType.Reset();
		_nextNode.Reset();
		_surfSpeedX.Reset();
		_surfSpeedY.Reset();
		_sequenceName.Reset();
		_startPar.Reset();
		_stopPar.Reset();
		_speed.Reset();
		_simpleTransactions.Reset();
		_posX.Reset();
		_posY.Reset();
		_markers.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_nodeName.IsDerivedFromParent()
			&& _nodeType.IsDerivedFromParent()
			&& _nextNode.IsDerivedFromParent()
			&& _surfSpeedX.IsDerivedFromParent()
			&& _surfSpeedY.IsDerivedFromParent()
			&& _sequenceName.IsDerivedFromParent()
			&& _startPar.IsDerivedFromParent()
			&& _stopPar.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _simpleTransactions.IsDerivedFromParent()
			&& _posX.IsDerivedFromParent()
			&& _posY.IsDerivedFromParent()
			&& _markers.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "nodeName" )
			_nodeName.Reset();
		else if ( fieldName == "nodeType" )
			_nodeType.Reset();
		else if ( fieldName == "nextNode" )
			_nextNode.Reset();
		else if ( fieldName == "surfSpeedX" )
			_surfSpeedX.Reset();
		else if ( fieldName == "surfSpeedY" )
			_surfSpeedY.Reset();
		else if ( fieldName == "sequenceName" )
			_sequenceName.Reset();
		else if ( fieldName == "startPar" )
			_startPar.Reset();
		else if ( fieldName == "stopPar" )
			_stopPar.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "simpleTransactions" )
			_simpleTransactions.Reset();
		else if ( fieldName == "posX" )
			_posX.Reset();
		else if ( fieldName == "posY" )
			_posY.Reset();
		else if ( fieldName == "markers" )
			_markers.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "nodeName" )
			return _nodeName.IsDerivedFromParent();
		if ( fieldName == "nodeType" )
			return _nodeType.IsDerivedFromParent();
		if ( fieldName == "nextNode" )
			return _nextNode.IsDerivedFromParent();
		if ( fieldName == "surfSpeedX" )
			return _surfSpeedX.IsDerivedFromParent();
		if ( fieldName == "surfSpeedY" )
			return _surfSpeedY.IsDerivedFromParent();
		if ( fieldName == "sequenceName" )
			return _sequenceName.IsDerivedFromParent();
		if ( fieldName == "startPar" )
			return _startPar.IsDerivedFromParent();
		if ( fieldName == "stopPar" )
			return _stopPar.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "simpleTransactions" )
			return _simpleTransactions.IsDerivedFromParent();
		if ( fieldName == "posX" )
			return _posX.IsDerivedFromParent();
		if ( fieldName == "posY" )
			return _posY.IsDerivedFromParent();
		if ( fieldName == "markers" )
			return _markers.IsDerivedFromParent();
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

public class AnimKey : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimKey __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _time;
	private UndoRedo<string> _name;

	public float time { get { return _time.Get(); } set { _time.Set( value ); } }

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_time = new UndoRedo<float>( owner, 0.0f );
		_name = new UndoRedo<string>( owner, string.Empty );
		_time.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public AnimKey()
	{
		Initialize( GetOwner() );
	}

	public AnimKey( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimKey( DBResource owner, AnimKey source )
		: this(owner, source, true){}

	protected AnimKey( DBResource owner, AnimKey source, bool fireEvent )
	{
		_time = new UndoRedo<float>( owner, source.time );
		_name = new UndoRedo<string>( owner, source.name );
		_time.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimKey source = _source as AnimKey;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimKey" );
		time = source.time;
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimKey newParent = _newParent as AnimKey;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_time.SetParent( newParent == null ? null : newParent._time );
		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_time.Reset();
		_name.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_time.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "time" )
			_time.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "time" )
			return _time.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
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

[IndexField("name")]
public class Animation : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Animation __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedoAssignableList<AnimKey> _animkeys;
	private SrcFile _srcFileName;
	private UndoRedo<float> _compression;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public libdb.IChangeableList<AnimKey> animkeys { get { return _animkeys; } set { _animkeys.Assign( value ); } }

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.ma")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaAnim")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "mayaAnim"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
	); } }
	[DstFile("anim")]
	public string animationFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "anim"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
	); } }
	[NoCode]
	public float compression { get { return _compression.Get(); } set { _compression.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_animkeys = new UndoRedoAssignableList<AnimKey>( owner );
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_compression = new UndoRedo<float>( owner, 0.0f );
		_name.Changed += FireChangedEvent;
		_animkeys.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_compression.Changed += FireChangedEvent;
	}

	public Animation()
	{
		Initialize( GetOwner() );
	}

	public Animation( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Animation( DBResource owner, Animation source )
		: this(owner, source, true){}

	protected Animation( DBResource owner, Animation source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_animkeys = new UndoRedoAssignableList<AnimKey>( owner );
		_animkeys.Assign( source.animkeys );
		_srcFileName = new SrcFile( owner, source.srcFileName );
		_compression = new UndoRedo<float>( owner, source.compression );
		_name.Changed += FireChangedEvent;
		_animkeys.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_compression.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Animation source = _source as Animation;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Animation" );
		name = source.name;
		animkeys = source.animkeys;
		srcFileName = source.srcFileName;
		compression = source.compression;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Animation newParent = _newParent as Animation;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_animkeys.SetParent( newParent == null ? null : newParent._animkeys );
		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_compression.SetParent( newParent == null ? null : newParent._compression );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_animkeys.Reset();
		_srcFileName.Reset();
		_compression.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _animkeys.IsDerivedFromParent()
			&& _srcFileName.IsDerivedFromParent()
			&& _compression.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "animkeys" )
			_animkeys.Reset();
		else if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "compression" )
			_compression.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "animkeys" )
			return _animkeys.IsDerivedFromParent();
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "compression" )
			return _compression.IsDerivedFromParent();
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

public class FaceFX : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FaceFX __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SrcFile _srcFileName;

	[DstFileArg(0)]
	[SrcFile("Face FX Animation files", "*.fxa")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("fxa")]
	public string fxaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "fxa"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
	); } }
	private void Initialize( DBResource owner )
	{
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_srcFileName.Changed += FireChangedEvent;
	}

	public FaceFX()
	{
		Initialize( GetOwner() );
	}

	public FaceFX( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FaceFX( DBResource owner, FaceFX source )
		: this(owner, source, true){}

	protected FaceFX( DBResource owner, FaceFX source, bool fireEvent )
	{
		_srcFileName = new SrcFile( owner, source.srcFileName );
		_srcFileName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FaceFX source = _source as FaceFX;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FaceFX" );
		srcFileName = source.srcFileName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FaceFX newParent = _newParent as FaceFX;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_srcFileName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
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

public class FlatSplineControlPointDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FlatSplineControlPointDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec2 _location;
	private UndoRedo<float> _width;

	public Vec2 location { get { return _location; } set { _location.Assign( value ); } }

	public float width { get { return _width.Get(); } set { _width.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_location = new Vec2( owner );
		_width = new UndoRedo<float>( owner, 10.0f );
		_location.Changed += FireChangedEvent;
		_width.Changed += FireChangedEvent;
	}

	public FlatSplineControlPointDesc()
	{
		Initialize( GetOwner() );
	}

	public FlatSplineControlPointDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FlatSplineControlPointDesc( DBResource owner, FlatSplineControlPointDesc source )
		: this(owner, source, true){}

	protected FlatSplineControlPointDesc( DBResource owner, FlatSplineControlPointDesc source, bool fireEvent )
	{
		_location = new Vec2( owner, source.location );
		_width = new UndoRedo<float>( owner, source.width );
		_location.Changed += FireChangedEvent;
		_width.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FlatSplineControlPointDesc source = _source as FlatSplineControlPointDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlatSplineControlPointDesc" );
		location = source.location;
		width = source.width;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FlatSplineControlPointDesc newParent = _newParent as FlatSplineControlPointDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_location.SetParent( newParent == null ? null : newParent._location );
		_width.SetParent( newParent == null ? null : newParent._width );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_location.Reset();
		_width.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_location.IsDerivedFromParent()
			&& _width.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "location" )
			_location.Reset();
		else if ( fieldName == "width" )
			_width.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "location" )
			return _location.IsDerivedFromParent();
		if ( fieldName == "width" )
			return _width.IsDerivedFromParent();
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

public class FlatSplineDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FlatSplineDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<FlatSplineControlPointDesc> _points;
	private UndoRedo<bool> _HasWidth;
	private UndoRedo<bool> _IsCircle;
	private UndoRedo<bool> _AbsolutePosition;

	public libdb.IChangeableList<FlatSplineControlPointDesc> points { get { return _points; } set { _points.Assign( value ); } }

	public bool HasWidth { get { return _HasWidth.Get(); } set { _HasWidth.Set( value ); } }

	public bool IsCircle { get { return _IsCircle.Get(); } set { _IsCircle.Set( value ); } }

	public bool AbsolutePosition { get { return _AbsolutePosition.Get(); } set { _AbsolutePosition.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_points = new UndoRedoAssignableList<FlatSplineControlPointDesc>( owner );
		_HasWidth = new UndoRedo<bool>( owner, false );
		_IsCircle = new UndoRedo<bool>( owner, false );
		_AbsolutePosition = new UndoRedo<bool>( owner, false );
		_points.Changed += FireChangedEvent;
		_HasWidth.Changed += FireChangedEvent;
		_IsCircle.Changed += FireChangedEvent;
		_AbsolutePosition.Changed += FireChangedEvent;
	}

	public FlatSplineDesc()
	{
		Initialize( GetOwner() );
	}

	public FlatSplineDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FlatSplineDesc( DBResource owner, FlatSplineDesc source )
		: this(owner, source, true){}

	protected FlatSplineDesc( DBResource owner, FlatSplineDesc source, bool fireEvent )
	{
		_points = new UndoRedoAssignableList<FlatSplineControlPointDesc>( owner );
		_points.Assign( source.points );
		_HasWidth = new UndoRedo<bool>( owner, source.HasWidth );
		_IsCircle = new UndoRedo<bool>( owner, source.IsCircle );
		_AbsolutePosition = new UndoRedo<bool>( owner, source.AbsolutePosition );
		_points.Changed += FireChangedEvent;
		_HasWidth.Changed += FireChangedEvent;
		_IsCircle.Changed += FireChangedEvent;
		_AbsolutePosition.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FlatSplineDesc source = _source as FlatSplineDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlatSplineDesc" );
		points = source.points;
		HasWidth = source.HasWidth;
		IsCircle = source.IsCircle;
		AbsolutePosition = source.AbsolutePosition;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FlatSplineDesc newParent = _newParent as FlatSplineDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_points.SetParent( newParent == null ? null : newParent._points );
		_HasWidth.SetParent( newParent == null ? null : newParent._HasWidth );
		_IsCircle.SetParent( newParent == null ? null : newParent._IsCircle );
		_AbsolutePosition.SetParent( newParent == null ? null : newParent._AbsolutePosition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_points.Reset();
		_HasWidth.Reset();
		_IsCircle.Reset();
		_AbsolutePosition.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_points.IsDerivedFromParent()
			&& _HasWidth.IsDerivedFromParent()
			&& _IsCircle.IsDerivedFromParent()
			&& _AbsolutePosition.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "points" )
			_points.Reset();
		else if ( fieldName == "HasWidth" )
			_HasWidth.Reset();
		else if ( fieldName == "IsCircle" )
			_IsCircle.Reset();
		else if ( fieldName == "AbsolutePosition" )
			_AbsolutePosition.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "points" )
			return _points.IsDerivedFromParent();
		if ( fieldName == "HasWidth" )
			return _HasWidth.IsDerivedFromParent();
		if ( fieldName == "IsCircle" )
			return _IsCircle.IsDerivedFromParent();
		if ( fieldName == "AbsolutePosition" )
			return _AbsolutePosition.IsDerivedFromParent();
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

public class FullScreenFXParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FullScreenFXParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _InMin;
	private Vec3 _InMax;
	private Vec3 _OutMin;
	private Vec3 _OutMax;
	private Vec3 _Gamma;
	private HDRColor _Color;
	private UndoRedo<float> _ColorCastCoef;
	private UndoRedo<float> _SharpPixelSize;
	private UndoRedo<float> _SharpCoef;

	public Vec3 InMin { get { return _InMin; } set { _InMin.Assign( value ); } }

	public Vec3 InMax { get { return _InMax; } set { _InMax.Assign( value ); } }

	public Vec3 OutMin { get { return _OutMin; } set { _OutMin.Assign( value ); } }

	public Vec3 OutMax { get { return _OutMax; } set { _OutMax.Assign( value ); } }

	public Vec3 Gamma { get { return _Gamma; } set { _Gamma.Assign( value ); } }

	public HDRColor Color { get { return _Color; } set { _Color.Assign( value ); } }

	public float ColorCastCoef { get { return _ColorCastCoef.Get(); } set { _ColorCastCoef.Set( value ); } }

	public float SharpPixelSize { get { return _SharpPixelSize.Get(); } set { _SharpPixelSize.Set( value ); } }

	public float SharpCoef { get { return _SharpCoef.Get(); } set { _SharpCoef.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_InMin = new Vec3( owner );
		Vec3 __InMax = new Vec3(); // Construct default object for InMax
		__InMax.x = 255.0f;
		__InMax.y = 255.0f;
		__InMax.z = 255.0f;
		_InMax = new Vec3( owner, __InMax );
		_OutMin = new Vec3( owner );
		Vec3 __OutMax = new Vec3(); // Construct default object for OutMax
		__OutMax.x = 255.0f;
		__OutMax.y = 255.0f;
		__OutMax.z = 255.0f;
		_OutMax = new Vec3( owner, __OutMax );
		_Gamma = new Vec3( owner );
		HDRColor __Color = new HDRColor(); // Construct default object for Color
		__Color.R = 1.0f;
		__Color.G = 1.0f;
		__Color.B = 1.0f;
		_Color = new HDRColor( owner, __Color );
		_ColorCastCoef = new UndoRedo<float>( owner, 0.0f );
		_SharpPixelSize = new UndoRedo<float>( owner, 1.0f );
		_SharpCoef = new UndoRedo<float>( owner, 0.0f );
		_InMin.Changed += FireChangedEvent;
		_InMax.Changed += FireChangedEvent;
		_OutMin.Changed += FireChangedEvent;
		_OutMax.Changed += FireChangedEvent;
		_Gamma.Changed += FireChangedEvent;
		_Color.Changed += FireChangedEvent;
		_ColorCastCoef.Changed += FireChangedEvent;
		_SharpPixelSize.Changed += FireChangedEvent;
		_SharpCoef.Changed += FireChangedEvent;
	}

	public FullScreenFXParams()
	{
		Initialize( GetOwner() );
	}

	public FullScreenFXParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FullScreenFXParams( DBResource owner, FullScreenFXParams source )
		: this(owner, source, true){}

	protected FullScreenFXParams( DBResource owner, FullScreenFXParams source, bool fireEvent )
	{
		_InMin = new Vec3( owner, source.InMin );
		_InMax = new Vec3( owner, source.InMax );
		_OutMin = new Vec3( owner, source.OutMin );
		_OutMax = new Vec3( owner, source.OutMax );
		_Gamma = new Vec3( owner, source.Gamma );
		_Color = new HDRColor( owner, source.Color );
		_ColorCastCoef = new UndoRedo<float>( owner, source.ColorCastCoef );
		_SharpPixelSize = new UndoRedo<float>( owner, source.SharpPixelSize );
		_SharpCoef = new UndoRedo<float>( owner, source.SharpCoef );
		_InMin.Changed += FireChangedEvent;
		_InMax.Changed += FireChangedEvent;
		_OutMin.Changed += FireChangedEvent;
		_OutMax.Changed += FireChangedEvent;
		_Gamma.Changed += FireChangedEvent;
		_Color.Changed += FireChangedEvent;
		_ColorCastCoef.Changed += FireChangedEvent;
		_SharpPixelSize.Changed += FireChangedEvent;
		_SharpCoef.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FullScreenFXParams source = _source as FullScreenFXParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FullScreenFXParams" );
		InMin = source.InMin;
		InMax = source.InMax;
		OutMin = source.OutMin;
		OutMax = source.OutMax;
		Gamma = source.Gamma;
		Color = source.Color;
		ColorCastCoef = source.ColorCastCoef;
		SharpPixelSize = source.SharpPixelSize;
		SharpCoef = source.SharpCoef;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FullScreenFXParams newParent = _newParent as FullScreenFXParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_InMin.SetParent( newParent == null ? null : newParent._InMin );
		_InMax.SetParent( newParent == null ? null : newParent._InMax );
		_OutMin.SetParent( newParent == null ? null : newParent._OutMin );
		_OutMax.SetParent( newParent == null ? null : newParent._OutMax );
		_Gamma.SetParent( newParent == null ? null : newParent._Gamma );
		_Color.SetParent( newParent == null ? null : newParent._Color );
		_ColorCastCoef.SetParent( newParent == null ? null : newParent._ColorCastCoef );
		_SharpPixelSize.SetParent( newParent == null ? null : newParent._SharpPixelSize );
		_SharpCoef.SetParent( newParent == null ? null : newParent._SharpCoef );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_InMin.Reset();
		_InMax.Reset();
		_OutMin.Reset();
		_OutMax.Reset();
		_Gamma.Reset();
		_Color.Reset();
		_ColorCastCoef.Reset();
		_SharpPixelSize.Reset();
		_SharpCoef.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_InMin.IsDerivedFromParent()
			&& _InMax.IsDerivedFromParent()
			&& _OutMin.IsDerivedFromParent()
			&& _OutMax.IsDerivedFromParent()
			&& _Gamma.IsDerivedFromParent()
			&& _Color.IsDerivedFromParent()
			&& _ColorCastCoef.IsDerivedFromParent()
			&& _SharpPixelSize.IsDerivedFromParent()
			&& _SharpCoef.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "InMin" )
			_InMin.Reset();
		else if ( fieldName == "InMax" )
			_InMax.Reset();
		else if ( fieldName == "OutMin" )
			_OutMin.Reset();
		else if ( fieldName == "OutMax" )
			_OutMax.Reset();
		else if ( fieldName == "Gamma" )
			_Gamma.Reset();
		else if ( fieldName == "Color" )
			_Color.Reset();
		else if ( fieldName == "ColorCastCoef" )
			_ColorCastCoef.Reset();
		else if ( fieldName == "SharpPixelSize" )
			_SharpPixelSize.Reset();
		else if ( fieldName == "SharpCoef" )
			_SharpCoef.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "InMin" )
			return _InMin.IsDerivedFromParent();
		if ( fieldName == "InMax" )
			return _InMax.IsDerivedFromParent();
		if ( fieldName == "OutMin" )
			return _OutMin.IsDerivedFromParent();
		if ( fieldName == "OutMax" )
			return _OutMax.IsDerivedFromParent();
		if ( fieldName == "Gamma" )
			return _Gamma.IsDerivedFromParent();
		if ( fieldName == "Color" )
			return _Color.IsDerivedFromParent();
		if ( fieldName == "ColorCastCoef" )
			return _ColorCastCoef.IsDerivedFromParent();
		if ( fieldName == "SharpPixelSize" )
			return _SharpPixelSize.IsDerivedFromParent();
		if ( fieldName == "SharpCoef" )
			return _SharpCoef.IsDerivedFromParent();
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

[IndexField("selection")]
public class SkinPartBase : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SkinPartBase __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private UndoRedo<int> _uvSetCount;
	private UndoRedo<int> _jointsCountPerVertex;
	private UndoRedo<string> _skinPartName;
	private UndoRedoAssignableList<DBPtr<Material>> _materialsReferences;

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaSkin")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "mayaSkin"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFile("skin")]
	public string geometryFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "skin"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	[NoCode]
	public int uvSetCount { get { return _uvSetCount.Get(); } set { _uvSetCount.Set( value ); } }

	[NoCode]
	public int jointsCountPerVertex { get { return _jointsCountPerVertex.Get(); } set { _jointsCountPerVertex.Set( value ); } }

	public string skinPartName { get { return _skinPartName.Get(); } set { _skinPartName.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Material>> materialsReferences { get { return _materialsReferences; } set { _materialsReferences.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_uvSetCount = new UndoRedo<int>( owner, 1 );
		_jointsCountPerVertex = new UndoRedo<int>( owner, 4 );
		_skinPartName = new UndoRedo<string>( owner, string.Empty );
		_materialsReferences = new UndoRedoAssignableList<DBPtr<Material>>( owner );
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_uvSetCount.Changed += FireChangedEvent;
		_jointsCountPerVertex.Changed += FireChangedEvent;
		_skinPartName.Changed += FireChangedEvent;
		_materialsReferences.Changed += FireChangedEvent;
	}

	public SkinPartBase()
	{
		Initialize( GetOwner() );
	}

	public SkinPartBase( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SkinPartBase( DBResource owner, SkinPartBase source )
		: this(owner, source, true){}

	protected SkinPartBase( DBResource owner, SkinPartBase source, bool fireEvent )
	{
		_srcFileName = new SrcFile( owner, source.srcFileName );
		_selection = new UndoRedo<string>( owner, source.selection );
		_uvSetCount = new UndoRedo<int>( owner, source.uvSetCount );
		_jointsCountPerVertex = new UndoRedo<int>( owner, source.jointsCountPerVertex );
		_skinPartName = new UndoRedo<string>( owner, source.skinPartName );
		_materialsReferences = new UndoRedoAssignableList<DBPtr<Material>>( owner );
		_materialsReferences.Assign( source.materialsReferences );
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_uvSetCount.Changed += FireChangedEvent;
		_jointsCountPerVertex.Changed += FireChangedEvent;
		_skinPartName.Changed += FireChangedEvent;
		_materialsReferences.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SkinPartBase source = _source as SkinPartBase;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkinPartBase" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		uvSetCount = source.uvSetCount;
		jointsCountPerVertex = source.jointsCountPerVertex;
		skinPartName = source.skinPartName;
		materialsReferences = source.materialsReferences;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SkinPartBase newParent = _newParent as SkinPartBase;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_uvSetCount.SetParent( newParent == null ? null : newParent._uvSetCount );
		_jointsCountPerVertex.SetParent( newParent == null ? null : newParent._jointsCountPerVertex );
		_skinPartName.SetParent( newParent == null ? null : newParent._skinPartName );
		_materialsReferences.SetParent( newParent == null ? null : newParent._materialsReferences );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		_uvSetCount.Reset();
		_jointsCountPerVertex.Reset();
		_skinPartName.Reset();
		_materialsReferences.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _uvSetCount.IsDerivedFromParent()
			&& _jointsCountPerVertex.IsDerivedFromParent()
			&& _skinPartName.IsDerivedFromParent()
			&& _materialsReferences.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "uvSetCount" )
			_uvSetCount.Reset();
		else if ( fieldName == "jointsCountPerVertex" )
			_jointsCountPerVertex.Reset();
		else if ( fieldName == "skinPartName" )
			_skinPartName.Reset();
		else if ( fieldName == "materialsReferences" )
			_materialsReferences.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "uvSetCount" )
			return _uvSetCount.IsDerivedFromParent();
		if ( fieldName == "jointsCountPerVertex" )
			return _jointsCountPerVertex.IsDerivedFromParent();
		if ( fieldName == "skinPartName" )
			return _skinPartName.IsDerivedFromParent();
		if ( fieldName == "materialsReferences" )
			return _materialsReferences.IsDerivedFromParent();
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

public class Spline3DControlPointDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Spline3DControlPointDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _rotation;
	private Vec3 _position;
	private UndoRedo<float> _tension;

	public Vec3 rotation { get { return _rotation; } set { _rotation.Assign( value ); } }

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	public float tension { get { return _tension.Get(); } set { _tension.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rotation = new Vec3( owner );
		_position = new Vec3( owner );
		_tension = new UndoRedo<float>( owner, 0.0f );
		_rotation.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_tension.Changed += FireChangedEvent;
	}

	public Spline3DControlPointDesc()
	{
		Initialize( GetOwner() );
	}

	public Spline3DControlPointDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Spline3DControlPointDesc( DBResource owner, Spline3DControlPointDesc source )
		: this(owner, source, true){}

	protected Spline3DControlPointDesc( DBResource owner, Spline3DControlPointDesc source, bool fireEvent )
	{
		_rotation = new Vec3( owner, source.rotation );
		_position = new Vec3( owner, source.position );
		_tension = new UndoRedo<float>( owner, source.tension );
		_rotation.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_tension.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Spline3DControlPointDesc source = _source as Spline3DControlPointDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Spline3DControlPointDesc" );
		rotation = source.rotation;
		position = source.position;
		tension = source.tension;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Spline3DControlPointDesc newParent = _newParent as Spline3DControlPointDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rotation.SetParent( newParent == null ? null : newParent._rotation );
		_position.SetParent( newParent == null ? null : newParent._position );
		_tension.SetParent( newParent == null ? null : newParent._tension );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rotation.Reset();
		_position.Reset();
		_tension.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rotation.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			&& _tension.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rotation" )
			_rotation.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "tension" )
			_tension.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rotation" )
			return _rotation.IsDerivedFromParent();
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "tension" )
			return _tension.IsDerivedFromParent();
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

public class TextureSize : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TextureSize __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _width;
	private UndoRedo<int> _height;

	public int width { get { return _width.Get(); } set { _width.Set( value ); } }

	public int height { get { return _height.Get(); } set { _height.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_width = new UndoRedo<int>( owner, 0 );
		_height = new UndoRedo<int>( owner, 0 );
		_width.Changed += FireChangedEvent;
		_height.Changed += FireChangedEvent;
	}

	public TextureSize()
	{
		Initialize( GetOwner() );
	}

	public TextureSize( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TextureSize( DBResource owner, TextureSize source )
		: this(owner, source, true){}

	protected TextureSize( DBResource owner, TextureSize source, bool fireEvent )
	{
		_width = new UndoRedo<int>( owner, source.width );
		_height = new UndoRedo<int>( owner, source.height );
		_width.Changed += FireChangedEvent;
		_height.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TextureSize source = _source as TextureSize;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TextureSize" );
		width = source.width;
		height = source.height;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TextureSize newParent = _newParent as TextureSize;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_width.SetParent( newParent == null ? null : newParent._width );
		_height.SetParent( newParent == null ? null : newParent._height );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_width.Reset();
		_height.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_width.IsDerivedFromParent()
			&& _height.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "width" )
			_width.Reset();
		else if ( fieldName == "height" )
			_height.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "width" )
			return _width.IsDerivedFromParent();
		if ( fieldName == "height" )
			return _height.IsDerivedFromParent();
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

[TypeId(0xC867EC41)]
public class TgaTextureName : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TgaTextureName __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SrcFile _name;

	[SrcFile("Image files", "*.tga")]
	public SrcFile name { get { return _name; } set { _name.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new SrcFile( owner, new SrcFile() );
		_name.Changed += FireChangedEvent;
	}

	public TgaTextureName()
	{
		Initialize( GetOwner() );
	}

	public TgaTextureName( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TgaTextureName( DBResource owner, TgaTextureName source )
		: this(owner, source, true){}

	protected TgaTextureName( DBResource owner, TgaTextureName source, bool fireEvent )
	{
		_name = new SrcFile( owner, source.name );
		_name.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TgaTextureName source = _source as TgaTextureName;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TgaTextureName" );
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TgaTextureName newParent = _newParent as TgaTextureName;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
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

public class UVPair : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UVPair __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec2 _uvTopLeft;
	private Vec2 _uvBottomRight;

	public Vec2 uvTopLeft { get { return _uvTopLeft; } set { _uvTopLeft.Assign( value ); } }

	public Vec2 uvBottomRight { get { return _uvBottomRight; } set { _uvBottomRight.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_uvTopLeft = new Vec2( owner );
		_uvBottomRight = new Vec2( owner );
		_uvTopLeft.Changed += FireChangedEvent;
		_uvBottomRight.Changed += FireChangedEvent;
	}

	public UVPair()
	{
		Initialize( GetOwner() );
	}

	public UVPair( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UVPair( DBResource owner, UVPair source )
		: this(owner, source, true){}

	protected UVPair( DBResource owner, UVPair source, bool fireEvent )
	{
		_uvTopLeft = new Vec2( owner, source.uvTopLeft );
		_uvBottomRight = new Vec2( owner, source.uvBottomRight );
		_uvTopLeft.Changed += FireChangedEvent;
		_uvBottomRight.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UVPair source = _source as UVPair;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UVPair" );
		uvTopLeft = source.uvTopLeft;
		uvBottomRight = source.uvBottomRight;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UVPair newParent = _newParent as UVPair;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_uvTopLeft.SetParent( newParent == null ? null : newParent._uvTopLeft );
		_uvBottomRight.SetParent( newParent == null ? null : newParent._uvBottomRight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_uvTopLeft.Reset();
		_uvBottomRight.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_uvTopLeft.IsDerivedFromParent()
			&& _uvBottomRight.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "uvTopLeft" )
			_uvTopLeft.Reset();
		else if ( fieldName == "uvBottomRight" )
			_uvBottomRight.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "uvTopLeft" )
			return _uvTopLeft.IsDerivedFromParent();
		if ( fieldName == "uvBottomRight" )
			return _uvBottomRight.IsDerivedFromParent();
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
[TypeId(0x145573F8)]
[UseTypeName("ANGR")]
public class AnimGraphCreator : DBResource
{
	private UndoRedoDBPtr<AnimGraphCreator> ___parent;
	[HideInOutliner]
	public new DBPtr<AnimGraphCreator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _defaultNode;
	private UndoRedoAssignableList<AnGrMacronode> _macroNodes;

	public string defaultNode { get { return _defaultNode.Get(); } set { _defaultNode.Set( value ); } }

	[ReadOnly( true )]
	public libdb.IChangeableList<AnGrMacronode> macroNodes { get { return _macroNodes; } set { _macroNodes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AnimGraphCreator>(owner);
		_defaultNode = new UndoRedo<string>( owner, "idle" );
		_macroNodes = new UndoRedoAssignableList<AnGrMacronode>( owner );
		___parent.Changed += FireChangedEvent;
		_defaultNode.Changed += FireChangedEvent;
		_macroNodes.Changed += FireChangedEvent;
	}

	public AnimGraphCreator()
	{
		Initialize( this );
	}
	private void AssignSelf( AnimGraphCreator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AnimGraphCreator" );
		defaultNode = source.defaultNode;
		macroNodes = source.macroNodes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AnimGraphCreator source = _source as AnimGraphCreator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimGraphCreator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AnimGraphCreator newParent = rawParent == null ? null : rawParent.Get<AnimGraphCreator>();
		if ( newParent == null && _newParent is AnimGraphCreator )
			newParent = _newParent as AnimGraphCreator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_defaultNode.SetParent( newParent == null ? null : newParent._defaultNode );
		_macroNodes.SetParent( newParent == null ? null : newParent._macroNodes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultNode.Reset();
		_macroNodes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_defaultNode.IsDerivedFromParent()
			&& _macroNodes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultNode" )
			_defaultNode.Reset();
		else if ( fieldName == "macroNodes" )
			_macroNodes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "defaultNode" )
			return _defaultNode.IsDerivedFromParent();
		if ( fieldName == "macroNodes" )
			return _macroNodes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class OmniLight : DBResource
{
	private UndoRedoDBPtr<OmniLight> ___parent;
	[HideInOutliner]
	public new DBPtr<OmniLight> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private HDRColor _diffuseColor;
	private HDRColor _specularColor;
	private UndoRedo<float> _radius;

	public HDRColor diffuseColor { get { return _diffuseColor; } set { _diffuseColor.Assign( value ); } }

	public HDRColor specularColor { get { return _specularColor; } set { _specularColor.Assign( value ); } }

	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OmniLight>(owner);
		_diffuseColor = new HDRColor( owner );
		_specularColor = new HDRColor( owner );
		_radius = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_diffuseColor.Changed += FireChangedEvent;
		_specularColor.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
	}

	public OmniLight()
	{
		Initialize( this );
	}
	private void AssignSelf( OmniLight source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OmniLight" );
		diffuseColor = source.diffuseColor;
		specularColor = source.specularColor;
		radius = source.radius;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OmniLight source = _source as OmniLight;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OmniLight" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OmniLight newParent = rawParent == null ? null : rawParent.Get<OmniLight>();
		if ( newParent == null && _newParent is OmniLight )
			newParent = _newParent as OmniLight;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_diffuseColor.SetParent( newParent == null ? null : newParent._diffuseColor );
		_specularColor.SetParent( newParent == null ? null : newParent._specularColor );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_diffuseColor.Reset();
		_specularColor.Reset();
		_radius.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_diffuseColor.IsDerivedFromParent()
			&& _specularColor.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "diffuseColor" )
			_diffuseColor.Reset();
		else if ( fieldName == "specularColor" )
			_specularColor.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "diffuseColor" )
			return _diffuseColor.IsDerivedFromParent();
		if ( fieldName == "specularColor" )
			return _specularColor.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xC867EC40)]
public class PaintPackedMasks : DBResource
{
	private UndoRedoDBPtr<PaintPackedMasks> ___parent;
	[HideInOutliner]
	public new DBPtr<PaintPackedMasks> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TgaTextureName> _masks;
	private UndoRedo<EPower2> _size;
	private UndoRedoAssignableList<DBPtr<Texture>> _packedMasks;

	[NoCode]
	public libdb.IChangeableList<TgaTextureName> masks { get { return _masks; } set { _masks.Assign( value ); } }

	[NoCode]
	public EPower2 size { get { return _size.Get(); } set { _size.Set( value ); } }

	[ReadOnly( true )]
	public libdb.IChangeableList<DBPtr<Texture>> packedMasks { get { return _packedMasks; } set { _packedMasks.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PaintPackedMasks>(owner);
		_masks = new UndoRedoAssignableList<TgaTextureName>( owner );
		_size = new UndoRedo<EPower2>( owner, EPower2._256 );
		_packedMasks = new UndoRedoAssignableList<DBPtr<Texture>>( owner );
		___parent.Changed += FireChangedEvent;
		_masks.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
		_packedMasks.Changed += FireChangedEvent;
	}

	public PaintPackedMasks()
	{
		Initialize( this );
	}
	private void AssignSelf( PaintPackedMasks source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PaintPackedMasks" );
		masks = source.masks;
		size = source.size;
		packedMasks = source.packedMasks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PaintPackedMasks source = _source as PaintPackedMasks;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PaintPackedMasks" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PaintPackedMasks newParent = rawParent == null ? null : rawParent.Get<PaintPackedMasks>();
		if ( newParent == null && _newParent is PaintPackedMasks )
			newParent = _newParent as PaintPackedMasks;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_masks.SetParent( newParent == null ? null : newParent._masks );
		_size.SetParent( newParent == null ? null : newParent._size );
		_packedMasks.SetParent( newParent == null ? null : newParent._packedMasks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_masks.Reset();
		_size.Reset();
		_packedMasks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_masks.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& _packedMasks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "masks" )
			_masks.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else if ( fieldName == "packedMasks" )
			_packedMasks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "masks" )
			return _masks.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		if ( fieldName == "packedMasks" )
			return _packedMasks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("PART")]
public class ParticleFX : DBResource
{
	private UndoRedoDBPtr<ParticleFX> ___parent;
	[HideInOutliner]
	public new DBPtr<ParticleFX> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private UndoRedo<float> _compression;

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaPart")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "mayaPart"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFile("part")]
	public string fxFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "part"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	[NoCode]
	public float compression { get { return _compression.Get(); } set { _compression.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ParticleFX>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_compression = new UndoRedo<float>( owner, 2.0f );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_compression.Changed += FireChangedEvent;
	}

	public ParticleFX()
	{
		Initialize( this );
	}
	private void AssignSelf( ParticleFX source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ParticleFX" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		compression = source.compression;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ParticleFX source = _source as ParticleFX;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ParticleFX" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ParticleFX newParent = rawParent == null ? null : rawParent.Get<ParticleFX>();
		if ( newParent == null && _newParent is ParticleFX )
			newParent = _newParent as ParticleFX;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_compression.SetParent( newParent == null ? null : newParent._compression );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		_compression.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _compression.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "compression" )
			_compression.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "compression" )
			return _compression.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("SKEL")]
public class Skeleton : DBResource
{
	private UndoRedoDBPtr<Skeleton> ___parent;
	[HideInOutliner]
	public new DBPtr<Skeleton> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private UndoRedoAssignableList<SkinPartBase> _skins;
	private UndoRedoAssignableList<Animation> _animations;
	private UndoRedoDBPtr<AnimGraphCreator> _animGraph;
	private UndoRedoDBPtr<AnimGraphCreator> _additionalGraph;
	private UndoRedoAssignableList<FaceFX> _faceFXAnims;

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaSkel")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "mayaSkel"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFile("skel")]
	public string skeletonFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "skel"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	public libdb.IChangeableList<SkinPartBase> skins { get { return _skins; } set { _skins.Assign( value ); } }

	public libdb.IChangeableList<Animation> animations { get { return _animations; } set { _animations.Assign( value ); } }

	public DBPtr<AnimGraphCreator> animGraph { get { return _animGraph.Get(); } set { _animGraph.Set( value ); } }

	public DBPtr<AnimGraphCreator> additionalGraph { get { return _additionalGraph.Get(); } set { _additionalGraph.Set( value ); } }

	public libdb.IChangeableList<FaceFX> faceFXAnims { get { return _faceFXAnims; } set { _faceFXAnims.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Skeleton>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_skins = new UndoRedoAssignableList<SkinPartBase>( owner );
		_animations = new UndoRedoAssignableList<Animation>( owner );
		_animGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		_additionalGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		_faceFXAnims = new UndoRedoAssignableList<FaceFX>( owner );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_skins.Changed += FireChangedEvent;
		_animations.Changed += FireChangedEvent;
		_animGraph.Changed += FireChangedEvent;
		_additionalGraph.Changed += FireChangedEvent;
		_faceFXAnims.Changed += FireChangedEvent;
	}

	public Skeleton()
	{
		Initialize( this );
	}
	private void AssignSelf( Skeleton source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Skeleton" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		skins = source.skins;
		animations = source.animations;
		animGraph = source.animGraph;
		additionalGraph = source.additionalGraph;
		faceFXAnims = source.faceFXAnims;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Skeleton source = _source as Skeleton;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Skeleton" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Skeleton newParent = rawParent == null ? null : rawParent.Get<Skeleton>();
		if ( newParent == null && _newParent is Skeleton )
			newParent = _newParent as Skeleton;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_skins.SetParent( newParent == null ? null : newParent._skins );
		_animations.SetParent( newParent == null ? null : newParent._animations );
		_animGraph.SetParent( newParent == null ? null : newParent._animGraph );
		_additionalGraph.SetParent( newParent == null ? null : newParent._additionalGraph );
		_faceFXAnims.SetParent( newParent == null ? null : newParent._faceFXAnims );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		_skins.Reset();
		_animations.Reset();
		_animGraph.Reset();
		_additionalGraph.Reset();
		_faceFXAnims.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _skins.IsDerivedFromParent()
			&& _animations.IsDerivedFromParent()
			&& _animGraph.IsDerivedFromParent()
			&& _additionalGraph.IsDerivedFromParent()
			&& _faceFXAnims.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "skins" )
			_skins.Reset();
		else if ( fieldName == "animations" )
			_animations.Reset();
		else if ( fieldName == "animGraph" )
			_animGraph.Reset();
		else if ( fieldName == "additionalGraph" )
			_additionalGraph.Reset();
		else if ( fieldName == "faceFXAnims" )
			_faceFXAnims.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "skins" )
			return _skins.IsDerivedFromParent();
		if ( fieldName == "animations" )
			return _animations.IsDerivedFromParent();
		if ( fieldName == "animGraph" )
			return _animGraph.IsDerivedFromParent();
		if ( fieldName == "additionalGraph" )
			return _additionalGraph.IsDerivedFromParent();
		if ( fieldName == "faceFXAnims" )
			return _faceFXAnims.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("geometryFileName")]
[TypeId(0x9E5573C0)]
[UseTypeName("STAT")]
public class StaticMesh : DBResource
{
	private UndoRedoDBPtr<StaticMesh> ___parent;
	[HideInOutliner]
	public new DBPtr<StaticMesh> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private UndoRedo<int> _uvSetCount;
	private UndoRedoAssignableList<DBPtr<Material>> _materialsReferences;
	private AABB _aabb;

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaStat")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "mayaStat"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFile("stat")]
	public string geometryFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "stat"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	[NoCode]
	public int uvSetCount { get { return _uvSetCount.Get(); } set { _uvSetCount.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Material>> materialsReferences { get { return _materialsReferences; } set { _materialsReferences.Assign( value ); } }

	[ReadOnly( true )]
	public AABB aabb { get { return _aabb; } set { _aabb.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StaticMesh>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_uvSetCount = new UndoRedo<int>( owner, 1 );
		_materialsReferences = new UndoRedoAssignableList<DBPtr<Material>>( owner );
		_aabb = new AABB( owner );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_uvSetCount.Changed += FireChangedEvent;
		_materialsReferences.Changed += FireChangedEvent;
		_aabb.Changed += FireChangedEvent;
	}

	public StaticMesh()
	{
		Initialize( this );
	}
	private void AssignSelf( StaticMesh source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StaticMesh" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		uvSetCount = source.uvSetCount;
		materialsReferences = source.materialsReferences;
		aabb = source.aabb;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StaticMesh source = _source as StaticMesh;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StaticMesh" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StaticMesh newParent = rawParent == null ? null : rawParent.Get<StaticMesh>();
		if ( newParent == null && _newParent is StaticMesh )
			newParent = _newParent as StaticMesh;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_uvSetCount.SetParent( newParent == null ? null : newParent._uvSetCount );
		_materialsReferences.SetParent( newParent == null ? null : newParent._materialsReferences );
		_aabb.SetParent( newParent == null ? null : newParent._aabb );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		_uvSetCount.Reset();
		_materialsReferences.Reset();
		_aabb.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _uvSetCount.IsDerivedFromParent()
			&& _materialsReferences.IsDerivedFromParent()
			&& _aabb.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "uvSetCount" )
			_uvSetCount.Reset();
		else if ( fieldName == "materialsReferences" )
			_materialsReferences.Reset();
		else if ( fieldName == "aabb" )
			_aabb.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "uvSetCount" )
			return _uvSetCount.IsDerivedFromParent();
		if ( fieldName == "materialsReferences" )
			return _materialsReferences.IsDerivedFromParent();
		if ( fieldName == "aabb" )
			return _aabb.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Load", "Render::Texture2D", "TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2D")]
[FactoryImpl("LoadInPool", "Render::Texture2D", "TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2DIntoPool")]
[IndexField("srcFileName")]
[UseTypeName("TXTR")]
public class Texture : TextureBase
{
	private UndoRedoDBPtr<Texture> ___parent;
	[HideInOutliner]
	public new DBPtr<Texture> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _generatedFileName;
	private UndoRedo<MipLevel> _mipLevelUsage;
	private UndoRedo<int> _mipLevels;
	private UndoRedo<int> _startMipLevel;
	private UndoRedo<string> _mipSharpenPasses;
	private TextureSize _size;
	private UndoRedo<TextureType> _textureType;
	private UndoRedo<EPixelFormat> _pixelFormat;

	[DstFileArg(0)]
	[SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFileArg(1)]
	[NoCode]
	[ReadOnly( true )]
	public string generatedFileName { get { return _generatedFileName.Get(); } set { _generatedFileName.Set( value ); } }

	[DstFile("dds")]
	public string textureFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "dds"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, generatedFileName.ToString()
	); } }
	[NoCode]
	public MipLevel mipLevelUsage { get { return _mipLevelUsage.Get(); } set { _mipLevelUsage.Set( value ); } }

	[IntMinMax(0, 13)]
	[NoCode]
	public int mipLevels { get { return _mipLevels.Get(); } set { _mipLevels.Set( value ); } }

	[IntMinMax(0, 12)]
	[NoCode]
	public int startMipLevel { get { return _startMipLevel.Get(); } set { _startMipLevel.Set( value ); } }

	[Description( "Sharpen passes for each mip level. Up to 10 passes for up to 10 mip levels, starting from 1-st mip. Example: 1 0 2 0 : Sharpen 1-st mip 1 time; 2-nd not sharpen; 3-rd sharpen 2 times" )]
	[NoCode]
	public string mipSharpenPasses { get { return _mipSharpenPasses.Get(); } set { _mipSharpenPasses.Set( value ); } }

	[NoCode]
	[ReadOnly( true )]
	public TextureSize size { get { return _size; } set { _size.Assign( value ); } }

	[NoCode]
	public TextureType textureType { get { return _textureType.Get(); } set { _textureType.Set( value ); } }

	[NoCode]
	public EPixelFormat pixelFormat { get { return _pixelFormat.Get(); } set { _pixelFormat.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Texture>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_generatedFileName = new UndoRedo<string>( owner, string.Empty );
		_mipLevelUsage = new UndoRedo<MipLevel>( owner, MipLevel.AutoGenerate );
		_mipLevels = new UndoRedo<int>( owner, 0 );
		_startMipLevel = new UndoRedo<int>( owner, 0 );
		_mipSharpenPasses = new UndoRedo<string>( owner, string.Empty );
		_size = new TextureSize( owner );
		_textureType = new UndoRedo<TextureType>( owner, TextureType.Color );
		_pixelFormat = new UndoRedo<EPixelFormat>( owner, EPixelFormat.DXT1 );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_generatedFileName.Changed += FireChangedEvent;
		_mipLevelUsage.Changed += FireChangedEvent;
		_mipLevels.Changed += FireChangedEvent;
		_startMipLevel.Changed += FireChangedEvent;
		_mipSharpenPasses.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
		_textureType.Changed += FireChangedEvent;
		_pixelFormat.Changed += FireChangedEvent;
	}

	public Texture()
	{
		Initialize( this );
	}
	private void AssignSelf( Texture source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Texture" );
		srcFileName = source.srcFileName;
		generatedFileName = source.generatedFileName;
		mipLevelUsage = source.mipLevelUsage;
		mipLevels = source.mipLevels;
		startMipLevel = source.startMipLevel;
		mipSharpenPasses = source.mipSharpenPasses;
		size = source.size;
		textureType = source.textureType;
		pixelFormat = source.pixelFormat;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Texture source = _source as Texture;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Texture" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Texture newParent = rawParent == null ? null : rawParent.Get<Texture>();
		if ( newParent == null && _newParent is Texture )
			newParent = _newParent as Texture;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_generatedFileName.SetParent( newParent == null ? null : newParent._generatedFileName );
		_mipLevelUsage.SetParent( newParent == null ? null : newParent._mipLevelUsage );
		_mipLevels.SetParent( newParent == null ? null : newParent._mipLevels );
		_startMipLevel.SetParent( newParent == null ? null : newParent._startMipLevel );
		_mipSharpenPasses.SetParent( newParent == null ? null : newParent._mipSharpenPasses );
		_size.SetParent( newParent == null ? null : newParent._size );
		_textureType.SetParent( newParent == null ? null : newParent._textureType );
		_pixelFormat.SetParent( newParent == null ? null : newParent._pixelFormat );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_generatedFileName.Reset();
		_mipLevelUsage.Reset();
		_mipLevels.Reset();
		_startMipLevel.Reset();
		_mipSharpenPasses.Reset();
		_size.Reset();
		_textureType.Reset();
		_pixelFormat.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _generatedFileName.IsDerivedFromParent()
			&& _mipLevelUsage.IsDerivedFromParent()
			&& _mipLevels.IsDerivedFromParent()
			&& _startMipLevel.IsDerivedFromParent()
			&& _mipSharpenPasses.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& _textureType.IsDerivedFromParent()
			&& _pixelFormat.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "generatedFileName" )
			_generatedFileName.Reset();
		else if ( fieldName == "mipLevelUsage" )
			_mipLevelUsage.Reset();
		else if ( fieldName == "mipLevels" )
			_mipLevels.Reset();
		else if ( fieldName == "startMipLevel" )
			_startMipLevel.Reset();
		else if ( fieldName == "mipSharpenPasses" )
			_mipSharpenPasses.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else if ( fieldName == "textureType" )
			_textureType.Reset();
		else if ( fieldName == "pixelFormat" )
			_pixelFormat.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "generatedFileName" )
			return _generatedFileName.IsDerivedFromParent();
		if ( fieldName == "mipLevelUsage" )
			return _mipLevelUsage.IsDerivedFromParent();
		if ( fieldName == "mipLevels" )
			return _mipLevels.IsDerivedFromParent();
		if ( fieldName == "startMipLevel" )
			return _startMipLevel.IsDerivedFromParent();
		if ( fieldName == "mipSharpenPasses" )
			return _mipSharpenPasses.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		if ( fieldName == "textureType" )
			return _textureType.IsDerivedFromParent();
		if ( fieldName == "pixelFormat" )
			return _pixelFormat.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
