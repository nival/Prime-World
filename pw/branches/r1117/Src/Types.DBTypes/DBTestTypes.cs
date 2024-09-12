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
[Flags]
public enum FlagEnum
{
	Zero = 0,
	One = 1,
	Two = 2,
	Four = 4,
	Five = 5,
	Eight = 8,
	Fifteen = 15,
	Sixteen = 16,
};

public enum SimpleEnum
{
	Zero = 0,
	One = 1,
	Two = 2,
	Four = 4,
	Five = 5,
	Eight = 8,
	Fifteen = 15,
	Sixteen = 16,
};

public class JustTestStruct : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private JustTestStruct __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> __intValue;
	private UndoRedo<SimpleEnum> __enumValue;
	private UndoRedoDBPtr<JustTestType> _childObject;

	public int _intValue { get { return __intValue.Get(); } set { __intValue.Set( value ); } }

	public SimpleEnum _enumValue { get { return __enumValue.Get(); } set { __enumValue.Set( value ); } }

	public DBPtr<JustTestType> childObject { get { return _childObject.Get(); } set { _childObject.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		__intValue = new UndoRedo<int>( owner, 0 );
		__enumValue = new UndoRedo<SimpleEnum>( owner, SimpleEnum.Zero );
		_childObject = new UndoRedoDBPtr<JustTestType>( owner );
		__intValue.Changed += FireChangedEvent;
		__enumValue.Changed += FireChangedEvent;
		_childObject.Changed += FireChangedEvent;
	}

	public JustTestStruct()
	{
		Initialize( GetOwner() );
	}

	public JustTestStruct( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public JustTestStruct( DBResource owner, JustTestStruct source )
		: this(owner, source, true){}

	protected JustTestStruct( DBResource owner, JustTestStruct source, bool fireEvent )
	{
		__intValue = new UndoRedo<int>( owner, source._intValue );
		__enumValue = new UndoRedo<SimpleEnum>( owner, source._enumValue );
		_childObject = new UndoRedoDBPtr<JustTestType>( owner, source.childObject );
		__intValue.Changed += FireChangedEvent;
		__enumValue.Changed += FireChangedEvent;
		_childObject.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		JustTestStruct source = _source as JustTestStruct;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for JustTestStruct" );
		_intValue = source._intValue;
		_enumValue = source._enumValue;
		childObject = source.childObject;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		JustTestStruct newParent = _newParent as JustTestStruct;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		__intValue.SetParent( newParent == null ? null : newParent.__intValue );
		__enumValue.SetParent( newParent == null ? null : newParent.__enumValue );
		_childObject.SetParent( newParent == null ? null : newParent._childObject );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		__intValue.Reset();
		__enumValue.Reset();
		_childObject.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			__intValue.IsDerivedFromParent()
			&& __enumValue.IsDerivedFromParent()
			&& _childObject.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "_intValue" )
			__intValue.Reset();
		else if ( fieldName == "_enumValue" )
			__enumValue.Reset();
		else if ( fieldName == "childObject" )
			_childObject.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "_intValue" )
			return __intValue.IsDerivedFromParent();
		if ( fieldName == "_enumValue" )
			return __enumValue.IsDerivedFromParent();
		if ( fieldName == "childObject" )
			return _childObject.IsDerivedFromParent();
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

public class ObjectLockItemT : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ObjectLockItemT __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public ObjectLockItemT()
	{
		Initialize( GetOwner() );
	}

	public ObjectLockItemT( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ObjectLockItemT( DBResource owner, ObjectLockItemT source )
		: this(owner, source, true){}

	protected ObjectLockItemT( DBResource owner, ObjectLockItemT source, bool fireEvent )
	{
		_x = new UndoRedo<int>( owner, source.x );
		_y = new UndoRedo<int>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ObjectLockItemT source = _source as ObjectLockItemT;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ObjectLockItemT" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ObjectLockItemT newParent = _newParent as ObjectLockItemT;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
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

public class ObjectLockMaskT : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ObjectLockMaskT __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _tileSize;
	private UndoRedoAssignableList<ObjectLockItemT> _mask;

	public float tileSize { get { return _tileSize.Get(); } set { _tileSize.Set( value ); } }

	public libdb.IChangeableList<ObjectLockItemT> mask { get { return _mask; } set { _mask.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_tileSize = new UndoRedo<float>( owner, 0.5f );
		_mask = new UndoRedoAssignableList<ObjectLockItemT>( owner );
		_tileSize.Changed += FireChangedEvent;
		_mask.Changed += FireChangedEvent;
	}

	public ObjectLockMaskT()
	{
		Initialize( GetOwner() );
	}

	public ObjectLockMaskT( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ObjectLockMaskT( DBResource owner, ObjectLockMaskT source )
		: this(owner, source, true){}

	protected ObjectLockMaskT( DBResource owner, ObjectLockMaskT source, bool fireEvent )
	{
		_tileSize = new UndoRedo<float>( owner, source.tileSize );
		_mask = new UndoRedoAssignableList<ObjectLockItemT>( owner );
		_mask.Assign( source.mask );
		_tileSize.Changed += FireChangedEvent;
		_mask.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ObjectLockMaskT source = _source as ObjectLockMaskT;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ObjectLockMaskT" );
		tileSize = source.tileSize;
		mask = source.mask;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ObjectLockMaskT newParent = _newParent as ObjectLockMaskT;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_tileSize.SetParent( newParent == null ? null : newParent._tileSize );
		_mask.SetParent( newParent == null ? null : newParent._mask );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_tileSize.Reset();
		_mask.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_tileSize.IsDerivedFromParent()
			&& _mask.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "tileSize" )
			_tileSize.Reset();
		else if ( fieldName == "mask" )
			_mask.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "tileSize" )
			return _tileSize.IsDerivedFromParent();
		if ( fieldName == "mask" )
			return _mask.IsDerivedFromParent();
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

[NeedEqualOperator]
public class PseudoStruct : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PseudoStruct __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public PseudoStruct()
	{
		Initialize( GetOwner() );
	}

	public PseudoStruct( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PseudoStruct( DBResource owner, PseudoStruct source )
		: this(owner, source, true){}

	protected PseudoStruct( DBResource owner, PseudoStruct source, bool fireEvent )
	{
		_x = new UndoRedo<int>( owner, source.x );
		_y = new UndoRedo<int>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PseudoStruct source = _source as PseudoStruct;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PseudoStruct" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PseudoStruct newParent = _newParent as PseudoStruct;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
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

public class SimpleTestProperty : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SimpleTestProperty __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<string> _field;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public string field { get { return _field.Get(); } set { _field.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_field = new UndoRedo<string>( owner, string.Empty );
		_name.Changed += FireChangedEvent;
		_field.Changed += FireChangedEvent;
	}

	public SimpleTestProperty()
	{
		Initialize( GetOwner() );
	}

	public SimpleTestProperty( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SimpleTestProperty( DBResource owner, SimpleTestProperty source )
		: this(owner, source, true){}

	protected SimpleTestProperty( DBResource owner, SimpleTestProperty source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_field = new UndoRedo<string>( owner, source.field );
		_name.Changed += FireChangedEvent;
		_field.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SimpleTestProperty source = _source as SimpleTestProperty;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SimpleTestProperty" );
		name = source.name;
		field = source.field;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SimpleTestProperty newParent = _newParent as SimpleTestProperty;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_field.SetParent( newParent == null ? null : newParent._field );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_field.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _field.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "field" )
			_field.Reset();
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
		if ( fieldName == "field" )
			return _field.IsDerivedFromParent();
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

[HasStates]
public class JustTestType : DBResource
{
	private UndoRedoDBPtr<JustTestType> ___parent;
	[HideInOutliner]
	public new DBPtr<JustTestType> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AnimatedInt __ints;
	private AnimatedVec3 __vecs;
	private AnimatedQuat __quats;
	private UndoRedo<SimpleEnum> _simple;
	private UndoRedo<FlagEnum> _flags;
	private Vec3 _v3;
	private Quat _quat;
	private AnimatedVec3 _avec3;
	private AnimatedQuat _aquat;
	private SrcFile _srcFileName;
	private TextRef _text;
	private UndoRedo<string> _file;
	private JustTestStruct _nestedStruct;
	private UndoRedoDBPtr<JustTestType> _childObject;

	public AnimatedInt _ints { get { return __ints; } set { __ints.Assign( value ); } }

	public AnimatedVec3 _vecs { get { return __vecs; } set { __vecs.Assign( value ); } }

	public AnimatedQuat _quats { get { return __quats; } set { __quats.Assign( value ); } }

	public SimpleEnum simple { get { return _simple.Get(); } set { _simple.Set( value ); } }

	public FlagEnum flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	public Vec3 v3 { get { return _v3; } set { _v3.Assign( value ); } }

	public Quat quat { get { return _quat; } set { _quat.Assign( value ); } }

	public AnimatedVec3 avec3 { get { return _avec3; } set { _avec3.Assign( value ); } }

	public AnimatedQuat aquat { get { return _aquat; } set { _aquat.Assign( value ); } }

	[SrcFile("Maya files", "*.tga")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	[FileRef("*.tga")]
	public string file { get { return _file.Get(); } set { _file.Set( value ); } }

	public JustTestStruct nestedStruct { get { return _nestedStruct; } set { _nestedStruct.Assign( value ); } }

	public DBPtr<JustTestType> childObject { get { return _childObject.Get(); } set { _childObject.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<JustTestType>(owner);
		__ints = new AnimatedInt( owner, 0 );
		__vecs = new AnimatedVec3( owner, 1.0f, 2.0f, 3.0f );
		__quats = new AnimatedQuat( owner );
		_simple = new UndoRedo<SimpleEnum>( owner, SimpleEnum.Zero );
		_flags = new UndoRedo<FlagEnum>( owner, FlagEnum.Zero );
		_v3 = new Vec3( owner );
		_quat = new Quat( owner );
		_avec3 = new AnimatedVec3( owner );
		_aquat = new AnimatedQuat( owner );
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_text = new TextRef( owner, new TextRef() );
		_file = new UndoRedo<string>( owner, string.Empty );
		_nestedStruct = new JustTestStruct( owner );
		_childObject = new UndoRedoDBPtr<JustTestType>( owner );
		___parent.Changed += FireChangedEvent;
		__ints.Changed += FireChangedEvent;
		__vecs.Changed += FireChangedEvent;
		__quats.Changed += FireChangedEvent;
		_simple.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_v3.Changed += FireChangedEvent;
		_quat.Changed += FireChangedEvent;
		_avec3.Changed += FireChangedEvent;
		_aquat.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		_file.Changed += FireChangedEvent;
		_nestedStruct.Changed += FireChangedEvent;
		_childObject.Changed += FireChangedEvent;
	}

	public JustTestType()
	{
		Initialize( this );
	}
	private void AssignSelf( JustTestType source )
	{
		DataBase.UndoRedoManager.Start( "Assign for JustTestType" );
		_ints = source._ints;
		_vecs = source._vecs;
		_quats = source._quats;
		simple = source.simple;
		flags = source.flags;
		v3 = source.v3;
		quat = source.quat;
		avec3 = source.avec3;
		aquat = source.aquat;
		srcFileName = source.srcFileName;
		text = source.text;
		file = source.file;
		nestedStruct = source.nestedStruct;
		childObject = source.childObject;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		JustTestType source = _source as JustTestType;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for JustTestType" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		JustTestType newParent = rawParent == null ? null : rawParent.Get<JustTestType>();
		if ( newParent == null && _newParent is JustTestType )
			newParent = _newParent as JustTestType;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		__ints.SetParent( newParent == null ? null : newParent.__ints );
		__vecs.SetParent( newParent == null ? null : newParent.__vecs );
		__quats.SetParent( newParent == null ? null : newParent.__quats );
		_simple.SetParent( newParent == null ? null : newParent._simple );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_v3.SetParent( newParent == null ? null : newParent._v3 );
		_quat.SetParent( newParent == null ? null : newParent._quat );
		_avec3.SetParent( newParent == null ? null : newParent._avec3 );
		_aquat.SetParent( newParent == null ? null : newParent._aquat );
		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_text.SetParent( newParent == null ? null : newParent._text );
		_file.SetParent( newParent == null ? null : newParent._file );
		_nestedStruct.SetParent( newParent == null ? null : newParent._nestedStruct );
		_childObject.SetParent( newParent == null ? null : newParent._childObject );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		__ints.Reset();
		__vecs.Reset();
		__quats.Reset();
		_simple.Reset();
		_flags.Reset();
		_v3.Reset();
		_quat.Reset();
		_avec3.Reset();
		_aquat.Reset();
		_srcFileName.Reset();
		_text.Reset();
		_file.Reset();
		_nestedStruct.Reset();
		_childObject.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			__ints.IsDerivedFromParent()
			&& __vecs.IsDerivedFromParent()
			&& __quats.IsDerivedFromParent()
			&& _simple.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _v3.IsDerivedFromParent()
			&& _quat.IsDerivedFromParent()
			&& _avec3.IsDerivedFromParent()
			&& _aquat.IsDerivedFromParent()
			&& _srcFileName.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			&& _file.IsDerivedFromParent()
			&& _nestedStruct.IsDerivedFromParent()
			&& _childObject.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "_ints" )
			__ints.Reset();
		else if ( fieldName == "_vecs" )
			__vecs.Reset();
		else if ( fieldName == "_quats" )
			__quats.Reset();
		else if ( fieldName == "simple" )
			_simple.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "v3" )
			_v3.Reset();
		else if ( fieldName == "quat" )
			_quat.Reset();
		else if ( fieldName == "avec3" )
			_avec3.Reset();
		else if ( fieldName == "aquat" )
			_aquat.Reset();
		else if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else if ( fieldName == "file" )
			_file.Reset();
		else if ( fieldName == "nestedStruct" )
			_nestedStruct.Reset();
		else if ( fieldName == "childObject" )
			_childObject.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "_ints" )
			return __ints.IsDerivedFromParent();
		if ( fieldName == "_vecs" )
			return __vecs.IsDerivedFromParent();
		if ( fieldName == "_quats" )
			return __quats.IsDerivedFromParent();
		if ( fieldName == "simple" )
			return _simple.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "v3" )
			return _v3.IsDerivedFromParent();
		if ( fieldName == "quat" )
			return _quat.IsDerivedFromParent();
		if ( fieldName == "avec3" )
			return _avec3.IsDerivedFromParent();
		if ( fieldName == "aquat" )
			return _aquat.IsDerivedFromParent();
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		if ( fieldName == "file" )
			return _file.IsDerivedFromParent();
		if ( fieldName == "nestedStruct" )
			return _nestedStruct.IsDerivedFromParent();
		if ( fieldName == "childObject" )
			return _childObject.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class JustTestType2 : JustTestType
{
	private UndoRedoDBPtr<JustTestType2> ___parent;
	[HideInOutliner]
	public new DBPtr<JustTestType2> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _intList;
	private UndoRedoAssignableList<SimpleTestProperty> _structList;
	private UndoRedoAssignableList<DBPtr<JustTestType>> _ptrList;

	public libdb.IChangeableList<int> intList { get { return _intList; } set { _intList.Assign( value ); } }

	public libdb.IChangeableList<SimpleTestProperty> structList { get { return _structList; } set { _structList.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<JustTestType>> ptrList { get { return _ptrList; } set { _ptrList.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<JustTestType2>(owner);
		_intList = new UndoRedoList<int>( owner );
		_structList = new UndoRedoAssignableList<SimpleTestProperty>( owner );
		_ptrList = new UndoRedoAssignableList<DBPtr<JustTestType>>( owner );
		___parent.Changed += FireChangedEvent;
		_intList.Changed += FireChangedEvent;
		_structList.Changed += FireChangedEvent;
		_ptrList.Changed += FireChangedEvent;
	}

	public JustTestType2()
	{
		Initialize( this );
	}
	private void AssignSelf( JustTestType2 source )
	{
		DataBase.UndoRedoManager.Start( "Assign for JustTestType2" );
		intList = source.intList;
		structList = source.structList;
		ptrList = source.ptrList;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		JustTestType2 source = _source as JustTestType2;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for JustTestType2" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		JustTestType2 newParent = rawParent == null ? null : rawParent.Get<JustTestType2>();
		if ( newParent == null && _newParent is JustTestType2 )
			newParent = _newParent as JustTestType2;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_intList.SetParent( newParent == null ? null : newParent._intList );
		_structList.SetParent( newParent == null ? null : newParent._structList );
		_ptrList.SetParent( newParent == null ? null : newParent._ptrList );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_intList.Reset();
		_structList.Reset();
		_ptrList.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_intList.IsDerivedFromParent()
			&& _structList.IsDerivedFromParent()
			&& _ptrList.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "intList" )
			_intList.Reset();
		else if ( fieldName == "structList" )
			_structList.Reset();
		else if ( fieldName == "ptrList" )
			_ptrList.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "intList" )
			return _intList.IsDerivedFromParent();
		if ( fieldName == "structList" )
			return _structList.IsDerivedFromParent();
		if ( fieldName == "ptrList" )
			return _ptrList.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class JustTestType3 : DBResource
{
	private UndoRedoDBPtr<JustTestType3> ___parent;
	[HideInOutliner]
	public new DBPtr<JustTestType3> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ObjectLockMaskT _lockMask;

	public ObjectLockMaskT lockMask { get { return _lockMask; } set { _lockMask.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<JustTestType3>(owner);
		_lockMask = new ObjectLockMaskT( owner );
		___parent.Changed += FireChangedEvent;
		_lockMask.Changed += FireChangedEvent;
	}

	public JustTestType3()
	{
		Initialize( this );
	}
	private void AssignSelf( JustTestType3 source )
	{
		DataBase.UndoRedoManager.Start( "Assign for JustTestType3" );
		lockMask = source.lockMask;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		JustTestType3 source = _source as JustTestType3;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for JustTestType3" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		JustTestType3 newParent = rawParent == null ? null : rawParent.Get<JustTestType3>();
		if ( newParent == null && _newParent is JustTestType3 )
			newParent = _newParent as JustTestType3;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lockMask.SetParent( newParent == null ? null : newParent._lockMask );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lockMask.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lockMask.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lockMask" )
			_lockMask.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lockMask" )
			return _lockMask.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class LofComplexInheritable : DBResource
{
	private UndoRedoDBPtr<LofComplexInheritable> ___parent;
	[HideInOutliner]
	public new DBPtr<LofComplexInheritable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> __int;
	private UndoRedoAssignableList<PseudoStruct> __list;

	public int _int { get { return __int.Get(); } set { __int.Set( value ); } }

	public libdb.IChangeableList<PseudoStruct> _list { get { return __list; } set { __list.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LofComplexInheritable>(owner);
		__int = new UndoRedo<int>( owner, 0 );
		__list = new UndoRedoAssignableList<PseudoStruct>( owner );
		___parent.Changed += FireChangedEvent;
		__int.Changed += FireChangedEvent;
		__list.Changed += FireChangedEvent;
	}

	public LofComplexInheritable()
	{
		Initialize( this );
	}
	private void AssignSelf( LofComplexInheritable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LofComplexInheritable" );
		_int = source._int;
		_list = source._list;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LofComplexInheritable source = _source as LofComplexInheritable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LofComplexInheritable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LofComplexInheritable newParent = rawParent == null ? null : rawParent.Get<LofComplexInheritable>();
		if ( newParent == null && _newParent is LofComplexInheritable )
			newParent = _newParent as LofComplexInheritable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		__int.SetParent( newParent == null ? null : newParent.__int );
		__list.SetParent( newParent == null ? null : newParent.__list );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		__int.Reset();
		__list.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			__int.IsDerivedFromParent()
			&& __list.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "_int" )
			__int.Reset();
		else if ( fieldName == "_list" )
			__list.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "_int" )
			return __int.IsDerivedFromParent();
		if ( fieldName == "_list" )
			return __list.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class LofHardInheritable : DBResource
{
	private UndoRedoDBPtr<LofHardInheritable> ___parent;
	[HideInOutliner]
	public new DBPtr<LofHardInheritable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> __int;
	private UndoRedoList<int> __list;

	public int _int { get { return __int.Get(); } set { __int.Set( value ); } }

	public libdb.IChangeableList<int> _list { get { return __list; } set { __list.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LofHardInheritable>(owner);
		__int = new UndoRedo<int>( owner, 0 );
		__list = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		__int.Changed += FireChangedEvent;
		__list.Changed += FireChangedEvent;
	}

	public LofHardInheritable()
	{
		Initialize( this );
	}
	private void AssignSelf( LofHardInheritable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LofHardInheritable" );
		_int = source._int;
		_list = source._list;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LofHardInheritable source = _source as LofHardInheritable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LofHardInheritable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LofHardInheritable newParent = rawParent == null ? null : rawParent.Get<LofHardInheritable>();
		if ( newParent == null && _newParent is LofHardInheritable )
			newParent = _newParent as LofHardInheritable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		__int.SetParent( newParent == null ? null : newParent.__int );
		__list.SetParent( newParent == null ? null : newParent.__list );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		__int.Reset();
		__list.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			__int.IsDerivedFromParent()
			&& __list.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "_int" )
			__int.Reset();
		else if ( fieldName == "_list" )
			__list.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "_int" )
			return __int.IsDerivedFromParent();
		if ( fieldName == "_list" )
			return __list.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class LofSimpleInheritable : DBResource
{
	private UndoRedoDBPtr<LofSimpleInheritable> ___parent;
	[HideInOutliner]
	public new DBPtr<LofSimpleInheritable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> __bool;
	private UndoRedo<int> __int;
	private UndoRedo<float> __float;
	private UndoRedo<string> __string;

	public bool _bool { get { return __bool.Get(); } set { __bool.Set( value ); } }

	public int _int { get { return __int.Get(); } set { __int.Set( value ); } }

	public float _float { get { return __float.Get(); } set { __float.Set( value ); } }

	public string _string { get { return __string.Get(); } set { __string.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LofSimpleInheritable>(owner);
		__bool = new UndoRedo<bool>( owner, false );
		__int = new UndoRedo<int>( owner, 0 );
		__float = new UndoRedo<float>( owner, 0.0f );
		__string = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		__bool.Changed += FireChangedEvent;
		__int.Changed += FireChangedEvent;
		__float.Changed += FireChangedEvent;
		__string.Changed += FireChangedEvent;
	}

	public LofSimpleInheritable()
	{
		Initialize( this );
	}
	private void AssignSelf( LofSimpleInheritable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LofSimpleInheritable" );
		_bool = source._bool;
		_int = source._int;
		_float = source._float;
		_string = source._string;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LofSimpleInheritable source = _source as LofSimpleInheritable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LofSimpleInheritable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LofSimpleInheritable newParent = rawParent == null ? null : rawParent.Get<LofSimpleInheritable>();
		if ( newParent == null && _newParent is LofSimpleInheritable )
			newParent = _newParent as LofSimpleInheritable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		__bool.SetParent( newParent == null ? null : newParent.__bool );
		__int.SetParent( newParent == null ? null : newParent.__int );
		__float.SetParent( newParent == null ? null : newParent.__float );
		__string.SetParent( newParent == null ? null : newParent.__string );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		__bool.Reset();
		__int.Reset();
		__float.Reset();
		__string.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			__bool.IsDerivedFromParent()
			&& __int.IsDerivedFromParent()
			&& __float.IsDerivedFromParent()
			&& __string.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "_bool" )
			__bool.Reset();
		else if ( fieldName == "_int" )
			__int.Reset();
		else if ( fieldName == "_float" )
			__float.Reset();
		else if ( fieldName == "_string" )
			__string.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "_bool" )
			return __bool.IsDerivedFromParent();
		if ( fieldName == "_int" )
			return __int.IsDerivedFromParent();
		if ( fieldName == "_float" )
			return __float.IsDerivedFromParent();
		if ( fieldName == "_string" )
			return __string.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class LofSimpleChild : LofSimpleInheritable
{
	private UndoRedoDBPtr<LofSimpleChild> ___parent;
	[HideInOutliner]
	public new DBPtr<LofSimpleChild> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<LofSimpleInheritable> _twin;
	private PseudoStruct __data;

	public DBPtr<LofSimpleInheritable> twin { get { return _twin.Get(); } set { _twin.Set( value ); } }

	public PseudoStruct _data { get { return __data; } set { __data.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LofSimpleChild>(owner);
		_twin = new UndoRedoDBPtr<LofSimpleInheritable>( owner );
		__data = new PseudoStruct( owner );
		___parent.Changed += FireChangedEvent;
		_twin.Changed += FireChangedEvent;
		__data.Changed += FireChangedEvent;
	}

	public LofSimpleChild()
	{
		Initialize( this );
	}
	private void AssignSelf( LofSimpleChild source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LofSimpleChild" );
		twin = source.twin;
		_data = source._data;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LofSimpleChild source = _source as LofSimpleChild;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LofSimpleChild" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LofSimpleChild newParent = rawParent == null ? null : rawParent.Get<LofSimpleChild>();
		if ( newParent == null && _newParent is LofSimpleChild )
			newParent = _newParent as LofSimpleChild;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_twin.SetParent( newParent == null ? null : newParent._twin );
		__data.SetParent( newParent == null ? null : newParent.__data );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_twin.Reset();
		__data.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_twin.IsDerivedFromParent()
			&& __data.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "twin" )
			_twin.Reset();
		else if ( fieldName == "_data" )
			__data.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "twin" )
			return _twin.IsDerivedFromParent();
		if ( fieldName == "_data" )
			return __data.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
