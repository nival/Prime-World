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
public enum EImageLabelShapeType
{
	Empty = 0,
	SimpleBox = 1,
	FromShapeStyle = 2,
	FromBackgroundStyle = 3,
	FromShapeOrBackgroundStyle = 4,
	ByText = 5,
};

public enum EUI3DOvertipMode
{
	World = 0,
	Billboard = 1,
	AxisBillboard = 2,
};

public enum EUIButtonViewMode
{
	ByMaterials = 0,
	ByPins = 1,
	ByPinsWithoutDisablePin = 2,
};

public enum EUIControlMouseActions
{
	Left = 0,
	Right = 1,
	Both = 2,
};

public enum EUIDiscreteType
{
	None = 0,
	Fixed = 1,
	RelativeToItemsCount = 2,
};

public enum EUIElementAspectRatio
{
	DontCare = 0,
	WidthBased = 1,
	HeightBased = 2,
};

public enum EUIElementHAlign
{
	Left = 0,
	Right = 1,
	Center = 2,
	FixedMargins = 3,
	Proportional = 4,
};

public enum EUIElementVAlign
{
	Top = 0,
	Bottom = 1,
	Center = 2,
	FixedMargins = 3,
	Proportional = 4,
};

public enum EUIListItemsPlacingOrder
{
	ByRows = 0,
	ByColumns = 1,
	ByRowsOfColumns = 2,
	ByColumnsOfRows = 3,
};

public enum EUIListItemsPlacingOrigin
{
	LeftTop = 0,
	RightTop = 1,
	LeftBottom = 2,
	RightBottom = 3,
};

public enum EUIOvertipBindPoint
{
	None = 0,
	Center = 1,
	LeftTop = 2,
	CenterTop = 3,
	RightTop = 4,
	LeftCenter = 5,
	RightCenter = 6,
	LeftBottom = 7,
	CenterBottom = 8,
	RightBottom = 9,
};

public enum EUIProgressBarType
{
	HorizontalScalingBar = 0,
	TextureMaskedProgress = 1,
};

public enum EUIRotationType
{
	CW = 0,
	CCW = 1,
};

public enum EUIScrollBarElementStyle
{
	Normal = 0,
	Hilited = 1,
	Pressed = 2,
	Disabled = 3,
};

public enum EUIScrollBarType
{
	Vertical = 0,
	Horizontal = 1,
};

public enum EUITextEntryType
{
	Free = 0,
	Console = 1,
	Numeric = 2,
	Identifier = 3,
	PlayerName = 4,
};

public enum EUITextHAlign
{
	Right = 0,
	Center = 1,
	Left = 2,
};

public enum EUITextVAlign
{
	Top = 0,
	Center = 1,
	Bottom = 2,
};

public class UI3DOvertipDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UI3DOvertipDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<UILayout> _layout;
	private UndoRedo<EUI3DOvertipMode> _mode;
	private Vec2 _worldSize;
	private Vec2 _align;
	private UndoRedo<float> _depthBias;

	public DBPtr<UILayout> layout { get { return _layout.Get(); } set { _layout.Set( value ); } }

	public EUI3DOvertipMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	public Vec2 worldSize { get { return _worldSize; } set { _worldSize.Assign( value ); } }

	public Vec2 align { get { return _align; } set { _align.Assign( value ); } }

	public float depthBias { get { return _depthBias.Get(); } set { _depthBias.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_layout = new UndoRedoDBPtr<UILayout>( owner );
		_mode = new UndoRedo<EUI3DOvertipMode>( owner, EUI3DOvertipMode.World );
		Vec2 __worldSize = new Vec2(); // Construct default object for worldSize
		__worldSize.x = 1.0f;
		__worldSize.y = 1.0f;
		_worldSize = new Vec2( owner, __worldSize );
		Vec2 __align = new Vec2(); // Construct default object for align
		__align.x = 0.5f;
		__align.y = 0.5f;
		_align = new Vec2( owner, __align );
		_depthBias = new UndoRedo<float>( owner, 0.0f );
		_layout.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_worldSize.Changed += FireChangedEvent;
		_align.Changed += FireChangedEvent;
		_depthBias.Changed += FireChangedEvent;
	}

	public UI3DOvertipDesc()
	{
		Initialize( GetOwner() );
	}

	public UI3DOvertipDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UI3DOvertipDesc( DBResource owner, UI3DOvertipDesc source )
		: this(owner, source, true){}

	protected UI3DOvertipDesc( DBResource owner, UI3DOvertipDesc source, bool fireEvent )
	{
		_layout = new UndoRedoDBPtr<UILayout>( owner, source.layout );
		_mode = new UndoRedo<EUI3DOvertipMode>( owner, source.mode );
		_worldSize = new Vec2( owner, source.worldSize );
		_align = new Vec2( owner, source.align );
		_depthBias = new UndoRedo<float>( owner, source.depthBias );
		_layout.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_worldSize.Changed += FireChangedEvent;
		_align.Changed += FireChangedEvent;
		_depthBias.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UI3DOvertipDesc source = _source as UI3DOvertipDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UI3DOvertipDesc" );
		layout = source.layout;
		mode = source.mode;
		worldSize = source.worldSize;
		align = source.align;
		depthBias = source.depthBias;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UI3DOvertipDesc newParent = _newParent as UI3DOvertipDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_layout.SetParent( newParent == null ? null : newParent._layout );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		_worldSize.SetParent( newParent == null ? null : newParent._worldSize );
		_align.SetParent( newParent == null ? null : newParent._align );
		_depthBias.SetParent( newParent == null ? null : newParent._depthBias );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_layout.Reset();
		_mode.Reset();
		_worldSize.Reset();
		_align.Reset();
		_depthBias.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_layout.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			&& _worldSize.IsDerivedFromParent()
			&& _align.IsDerivedFromParent()
			&& _depthBias.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "layout" )
			_layout.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "worldSize" )
			_worldSize.Reset();
		else if ( fieldName == "align" )
			_align.Reset();
		else if ( fieldName == "depthBias" )
			_depthBias.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "layout" )
			return _layout.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "worldSize" )
			return _worldSize.IsDerivedFromParent();
		if ( fieldName == "align" )
			return _align.IsDerivedFromParent();
		if ( fieldName == "depthBias" )
			return _depthBias.IsDerivedFromParent();
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

[NeedAssignOperator]
[NeedEqualOperator]
public class UICatchEvents : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UICatchEvents __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _mouseMove;
	private UndoRedo<bool> _leftMouseDown;
	private UndoRedo<bool> _rightMouseDown;
	private UndoRedo<bool> _leftMouseUp;
	private UndoRedo<bool> _rightMouseUp;
	private UndoRedo<bool> _leftDoubleClick;
	private UndoRedo<bool> _rightDoubleClick;

	public bool mouseMove { get { return _mouseMove.Get(); } set { _mouseMove.Set( value ); } }

	public bool leftMouseDown { get { return _leftMouseDown.Get(); } set { _leftMouseDown.Set( value ); } }

	public bool rightMouseDown { get { return _rightMouseDown.Get(); } set { _rightMouseDown.Set( value ); } }

	public bool leftMouseUp { get { return _leftMouseUp.Get(); } set { _leftMouseUp.Set( value ); } }

	public bool rightMouseUp { get { return _rightMouseUp.Get(); } set { _rightMouseUp.Set( value ); } }

	public bool leftDoubleClick { get { return _leftDoubleClick.Get(); } set { _leftDoubleClick.Set( value ); } }

	public bool rightDoubleClick { get { return _rightDoubleClick.Get(); } set { _rightDoubleClick.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_mouseMove = new UndoRedo<bool>( owner, true );
		_leftMouseDown = new UndoRedo<bool>( owner, true );
		_rightMouseDown = new UndoRedo<bool>( owner, true );
		_leftMouseUp = new UndoRedo<bool>( owner, true );
		_rightMouseUp = new UndoRedo<bool>( owner, true );
		_leftDoubleClick = new UndoRedo<bool>( owner, true );
		_rightDoubleClick = new UndoRedo<bool>( owner, true );
		_mouseMove.Changed += FireChangedEvent;
		_leftMouseDown.Changed += FireChangedEvent;
		_rightMouseDown.Changed += FireChangedEvent;
		_leftMouseUp.Changed += FireChangedEvent;
		_rightMouseUp.Changed += FireChangedEvent;
		_leftDoubleClick.Changed += FireChangedEvent;
		_rightDoubleClick.Changed += FireChangedEvent;
	}

	public UICatchEvents()
	{
		Initialize( GetOwner() );
	}

	public UICatchEvents( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UICatchEvents( DBResource owner, UICatchEvents source )
		: this(owner, source, true){}

	protected UICatchEvents( DBResource owner, UICatchEvents source, bool fireEvent )
	{
		_mouseMove = new UndoRedo<bool>( owner, source.mouseMove );
		_leftMouseDown = new UndoRedo<bool>( owner, source.leftMouseDown );
		_rightMouseDown = new UndoRedo<bool>( owner, source.rightMouseDown );
		_leftMouseUp = new UndoRedo<bool>( owner, source.leftMouseUp );
		_rightMouseUp = new UndoRedo<bool>( owner, source.rightMouseUp );
		_leftDoubleClick = new UndoRedo<bool>( owner, source.leftDoubleClick );
		_rightDoubleClick = new UndoRedo<bool>( owner, source.rightDoubleClick );
		_mouseMove.Changed += FireChangedEvent;
		_leftMouseDown.Changed += FireChangedEvent;
		_rightMouseDown.Changed += FireChangedEvent;
		_leftMouseUp.Changed += FireChangedEvent;
		_rightMouseUp.Changed += FireChangedEvent;
		_leftDoubleClick.Changed += FireChangedEvent;
		_rightDoubleClick.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UICatchEvents source = _source as UICatchEvents;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICatchEvents" );
		mouseMove = source.mouseMove;
		leftMouseDown = source.leftMouseDown;
		rightMouseDown = source.rightMouseDown;
		leftMouseUp = source.leftMouseUp;
		rightMouseUp = source.rightMouseUp;
		leftDoubleClick = source.leftDoubleClick;
		rightDoubleClick = source.rightDoubleClick;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UICatchEvents newParent = _newParent as UICatchEvents;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_mouseMove.SetParent( newParent == null ? null : newParent._mouseMove );
		_leftMouseDown.SetParent( newParent == null ? null : newParent._leftMouseDown );
		_rightMouseDown.SetParent( newParent == null ? null : newParent._rightMouseDown );
		_leftMouseUp.SetParent( newParent == null ? null : newParent._leftMouseUp );
		_rightMouseUp.SetParent( newParent == null ? null : newParent._rightMouseUp );
		_leftDoubleClick.SetParent( newParent == null ? null : newParent._leftDoubleClick );
		_rightDoubleClick.SetParent( newParent == null ? null : newParent._rightDoubleClick );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_mouseMove.Reset();
		_leftMouseDown.Reset();
		_rightMouseDown.Reset();
		_leftMouseUp.Reset();
		_rightMouseUp.Reset();
		_leftDoubleClick.Reset();
		_rightDoubleClick.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_mouseMove.IsDerivedFromParent()
			&& _leftMouseDown.IsDerivedFromParent()
			&& _rightMouseDown.IsDerivedFromParent()
			&& _leftMouseUp.IsDerivedFromParent()
			&& _rightMouseUp.IsDerivedFromParent()
			&& _leftDoubleClick.IsDerivedFromParent()
			&& _rightDoubleClick.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "mouseMove" )
			_mouseMove.Reset();
		else if ( fieldName == "leftMouseDown" )
			_leftMouseDown.Reset();
		else if ( fieldName == "rightMouseDown" )
			_rightMouseDown.Reset();
		else if ( fieldName == "leftMouseUp" )
			_leftMouseUp.Reset();
		else if ( fieldName == "rightMouseUp" )
			_rightMouseUp.Reset();
		else if ( fieldName == "leftDoubleClick" )
			_leftDoubleClick.Reset();
		else if ( fieldName == "rightDoubleClick" )
			_rightDoubleClick.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "mouseMove" )
			return _mouseMove.IsDerivedFromParent();
		if ( fieldName == "leftMouseDown" )
			return _leftMouseDown.IsDerivedFromParent();
		if ( fieldName == "rightMouseDown" )
			return _rightMouseDown.IsDerivedFromParent();
		if ( fieldName == "leftMouseUp" )
			return _leftMouseUp.IsDerivedFromParent();
		if ( fieldName == "rightMouseUp" )
			return _rightMouseUp.IsDerivedFromParent();
		if ( fieldName == "leftDoubleClick" )
			return _leftDoubleClick.IsDerivedFromParent();
		if ( fieldName == "rightDoubleClick" )
			return _rightDoubleClick.IsDerivedFromParent();
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

public class UIConstant : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIConstant __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<string> _value;
	private UndoRedo<string> _comment;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public string value { get { return _value.Get(); } set { _value.Set( value ); } }

	public string comment { get { return _comment.Get(); } set { _comment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_value = new UndoRedo<string>( owner, string.Empty );
		_comment = new UndoRedo<string>( owner, string.Empty );
		_name.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
	}

	public UIConstant()
	{
		Initialize( GetOwner() );
	}

	public UIConstant( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIConstant( DBResource owner, UIConstant source )
		: this(owner, source, true){}

	protected UIConstant( DBResource owner, UIConstant source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_value = new UndoRedo<string>( owner, source.value );
		_comment = new UndoRedo<string>( owner, source.comment );
		_name.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIConstant source = _source as UIConstant;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIConstant" );
		name = source.name;
		value = source.value;
		comment = source.comment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIConstant newParent = _newParent as UIConstant;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_value.SetParent( newParent == null ? null : newParent._value );
		_comment.SetParent( newParent == null ? null : newParent._comment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_value.Reset();
		_comment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			&& _comment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "comment" )
			_comment.Reset();
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
		if ( fieldName == "comment" )
			return _comment.IsDerivedFromParent();
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

public class UIContentGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIContentGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _groupId;
	private UndoRedoAssignableList<DBPtr<UIContentResource>> _resources;
	private UndoRedo<string> _comment;

	public string groupId { get { return _groupId.Get(); } set { _groupId.Set( value ); } }

	public libdb.IChangeableList<DBPtr<UIContentResource>> resources { get { return _resources; } set { _resources.Assign( value ); } }

	public string comment { get { return _comment.Get(); } set { _comment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_groupId = new UndoRedo<string>( owner, string.Empty );
		_resources = new UndoRedoAssignableList<DBPtr<UIContentResource>>( owner );
		_comment = new UndoRedo<string>( owner, string.Empty );
		_groupId.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
	}

	public UIContentGroup()
	{
		Initialize( GetOwner() );
	}

	public UIContentGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIContentGroup( DBResource owner, UIContentGroup source )
		: this(owner, source, true){}

	protected UIContentGroup( DBResource owner, UIContentGroup source, bool fireEvent )
	{
		_groupId = new UndoRedo<string>( owner, source.groupId );
		_resources = new UndoRedoAssignableList<DBPtr<UIContentResource>>( owner );
		_resources.Assign( source.resources );
		_comment = new UndoRedo<string>( owner, source.comment );
		_groupId.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIContentGroup source = _source as UIContentGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIContentGroup" );
		groupId = source.groupId;
		resources = source.resources;
		comment = source.comment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIContentGroup newParent = _newParent as UIContentGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_groupId.SetParent( newParent == null ? null : newParent._groupId );
		_resources.SetParent( newParent == null ? null : newParent._resources );
		_comment.SetParent( newParent == null ? null : newParent._comment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_groupId.Reset();
		_resources.Reset();
		_comment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_groupId.IsDerivedFromParent()
			&& _resources.IsDerivedFromParent()
			&& _comment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "groupId" )
			_groupId.Reset();
		else if ( fieldName == "resources" )
			_resources.Reset();
		else if ( fieldName == "comment" )
			_comment.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "groupId" )
			return _groupId.IsDerivedFromParent();
		if ( fieldName == "resources" )
			return _resources.IsDerivedFromParent();
		if ( fieldName == "comment" )
			return _comment.IsDerivedFromParent();
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

public class UICursorDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UICursorDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _cursorId;
	private UndoRedoDBPtr<UICursorBase> _cursor;
	private UndoRedoDBPtr<UICursorBase> _cursorOverlay;
	private IntPoint _cursorOverlayOffset;

	public string cursorId { get { return _cursorId.Get(); } set { _cursorId.Set( value ); } }

	public DBPtr<UICursorBase> cursor { get { return _cursor.Get(); } set { _cursor.Set( value ); } }

	public DBPtr<UICursorBase> cursorOverlay { get { return _cursorOverlay.Get(); } set { _cursorOverlay.Set( value ); } }

	public IntPoint cursorOverlayOffset { get { return _cursorOverlayOffset; } set { _cursorOverlayOffset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_cursorId = new UndoRedo<string>( owner, string.Empty );
		_cursor = new UndoRedoDBPtr<UICursorBase>( owner );
		_cursorOverlay = new UndoRedoDBPtr<UICursorBase>( owner );
		_cursorOverlayOffset = new IntPoint( owner );
		_cursorId.Changed += FireChangedEvent;
		_cursor.Changed += FireChangedEvent;
		_cursorOverlay.Changed += FireChangedEvent;
		_cursorOverlayOffset.Changed += FireChangedEvent;
	}

	public UICursorDesc()
	{
		Initialize( GetOwner() );
	}

	public UICursorDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UICursorDesc( DBResource owner, UICursorDesc source )
		: this(owner, source, true){}

	protected UICursorDesc( DBResource owner, UICursorDesc source, bool fireEvent )
	{
		_cursorId = new UndoRedo<string>( owner, source.cursorId );
		_cursor = new UndoRedoDBPtr<UICursorBase>( owner, source.cursor );
		_cursorOverlay = new UndoRedoDBPtr<UICursorBase>( owner, source.cursorOverlay );
		_cursorOverlayOffset = new IntPoint( owner, source.cursorOverlayOffset );
		_cursorId.Changed += FireChangedEvent;
		_cursor.Changed += FireChangedEvent;
		_cursorOverlay.Changed += FireChangedEvent;
		_cursorOverlayOffset.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UICursorDesc source = _source as UICursorDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICursorDesc" );
		cursorId = source.cursorId;
		cursor = source.cursor;
		cursorOverlay = source.cursorOverlay;
		cursorOverlayOffset = source.cursorOverlayOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UICursorDesc newParent = _newParent as UICursorDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cursorId.SetParent( newParent == null ? null : newParent._cursorId );
		_cursor.SetParent( newParent == null ? null : newParent._cursor );
		_cursorOverlay.SetParent( newParent == null ? null : newParent._cursorOverlay );
		_cursorOverlayOffset.SetParent( newParent == null ? null : newParent._cursorOverlayOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cursorId.Reset();
		_cursor.Reset();
		_cursorOverlay.Reset();
		_cursorOverlayOffset.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cursorId.IsDerivedFromParent()
			&& _cursor.IsDerivedFromParent()
			&& _cursorOverlay.IsDerivedFromParent()
			&& _cursorOverlayOffset.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cursorId" )
			_cursorId.Reset();
		else if ( fieldName == "cursor" )
			_cursor.Reset();
		else if ( fieldName == "cursorOverlay" )
			_cursorOverlay.Reset();
		else if ( fieldName == "cursorOverlayOffset" )
			_cursorOverlayOffset.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "cursorId" )
			return _cursorId.IsDerivedFromParent();
		if ( fieldName == "cursor" )
			return _cursor.IsDerivedFromParent();
		if ( fieldName == "cursorOverlay" )
			return _cursorOverlay.IsDerivedFromParent();
		if ( fieldName == "cursorOverlayOffset" )
			return _cursorOverlayOffset.IsDerivedFromParent();
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

[NeedAssignOperator]
[NeedEqualOperator]
public class UICursors : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UICursors __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _normal;
	private UndoRedo<string> _dragging;
	private UndoRedo<string> _dragable;
	private UndoRedo<string> _focused;
	private UndoRedo<string> _disabled;
	private UndoRedo<string> _pushing;
	private UndoRedo<string> _pushable;

	public string normal { get { return _normal.Get(); } set { _normal.Set( value ); } }

	public string dragging { get { return _dragging.Get(); } set { _dragging.Set( value ); } }

	public string dragable { get { return _dragable.Get(); } set { _dragable.Set( value ); } }

	public string focused { get { return _focused.Get(); } set { _focused.Set( value ); } }

	public string disabled { get { return _disabled.Get(); } set { _disabled.Set( value ); } }

	public string pushing { get { return _pushing.Get(); } set { _pushing.Set( value ); } }

	public string pushable { get { return _pushable.Get(); } set { _pushable.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_normal = new UndoRedo<string>( owner, "ui_normal" );
		_dragging = new UndoRedo<string>( owner, "ui_dragging" );
		_dragable = new UndoRedo<string>( owner, "ui_dragable" );
		_focused = new UndoRedo<string>( owner, "ui_focused" );
		_disabled = new UndoRedo<string>( owner, "ui_disabled" );
		_pushing = new UndoRedo<string>( owner, "ui_pushing" );
		_pushable = new UndoRedo<string>( owner, "ui_pushable" );
		_normal.Changed += FireChangedEvent;
		_dragging.Changed += FireChangedEvent;
		_dragable.Changed += FireChangedEvent;
		_focused.Changed += FireChangedEvent;
		_disabled.Changed += FireChangedEvent;
		_pushing.Changed += FireChangedEvent;
		_pushable.Changed += FireChangedEvent;
	}

	public UICursors()
	{
		Initialize( GetOwner() );
	}

	public UICursors( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UICursors( DBResource owner, UICursors source )
		: this(owner, source, true){}

	protected UICursors( DBResource owner, UICursors source, bool fireEvent )
	{
		_normal = new UndoRedo<string>( owner, source.normal );
		_dragging = new UndoRedo<string>( owner, source.dragging );
		_dragable = new UndoRedo<string>( owner, source.dragable );
		_focused = new UndoRedo<string>( owner, source.focused );
		_disabled = new UndoRedo<string>( owner, source.disabled );
		_pushing = new UndoRedo<string>( owner, source.pushing );
		_pushable = new UndoRedo<string>( owner, source.pushable );
		_normal.Changed += FireChangedEvent;
		_dragging.Changed += FireChangedEvent;
		_dragable.Changed += FireChangedEvent;
		_focused.Changed += FireChangedEvent;
		_disabled.Changed += FireChangedEvent;
		_pushing.Changed += FireChangedEvent;
		_pushable.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UICursors source = _source as UICursors;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICursors" );
		normal = source.normal;
		dragging = source.dragging;
		dragable = source.dragable;
		focused = source.focused;
		disabled = source.disabled;
		pushing = source.pushing;
		pushable = source.pushable;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UICursors newParent = _newParent as UICursors;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_normal.SetParent( newParent == null ? null : newParent._normal );
		_dragging.SetParent( newParent == null ? null : newParent._dragging );
		_dragable.SetParent( newParent == null ? null : newParent._dragable );
		_focused.SetParent( newParent == null ? null : newParent._focused );
		_disabled.SetParent( newParent == null ? null : newParent._disabled );
		_pushing.SetParent( newParent == null ? null : newParent._pushing );
		_pushable.SetParent( newParent == null ? null : newParent._pushable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_normal.Reset();
		_dragging.Reset();
		_dragable.Reset();
		_focused.Reset();
		_disabled.Reset();
		_pushing.Reset();
		_pushable.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_normal.IsDerivedFromParent()
			&& _dragging.IsDerivedFromParent()
			&& _dragable.IsDerivedFromParent()
			&& _focused.IsDerivedFromParent()
			&& _disabled.IsDerivedFromParent()
			&& _pushing.IsDerivedFromParent()
			&& _pushable.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "normal" )
			_normal.Reset();
		else if ( fieldName == "dragging" )
			_dragging.Reset();
		else if ( fieldName == "dragable" )
			_dragable.Reset();
		else if ( fieldName == "focused" )
			_focused.Reset();
		else if ( fieldName == "disabled" )
			_disabled.Reset();
		else if ( fieldName == "pushing" )
			_pushing.Reset();
		else if ( fieldName == "pushable" )
			_pushable.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "normal" )
			return _normal.IsDerivedFromParent();
		if ( fieldName == "dragging" )
			return _dragging.IsDerivedFromParent();
		if ( fieldName == "dragable" )
			return _dragable.IsDerivedFromParent();
		if ( fieldName == "focused" )
			return _focused.IsDerivedFromParent();
		if ( fieldName == "disabled" )
			return _disabled.IsDerivedFromParent();
		if ( fieldName == "pushing" )
			return _pushing.IsDerivedFromParent();
		if ( fieldName == "pushable" )
			return _pushable.IsDerivedFromParent();
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

[IndexField("propertyName", true)]
[NeedEqualOperator]
public class UIFlashProperties : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIFlashProperties __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _propertyName;
	private TextRef _propertyValue;

	public string propertyName { get { return _propertyName.Get(); } set { _propertyName.Set( value ); } }

	public TextRef propertyValue { get { return _propertyValue; } set { _propertyValue.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_propertyName = new UndoRedo<string>( owner, string.Empty );
		_propertyValue = new TextRef( owner, new TextRef() );
		_propertyName.Changed += FireChangedEvent;
		_propertyValue.Changed += FireChangedEvent;
	}

	public UIFlashProperties()
	{
		Initialize( GetOwner() );
	}

	public UIFlashProperties( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIFlashProperties( DBResource owner, UIFlashProperties source )
		: this(owner, source, true){}

	protected UIFlashProperties( DBResource owner, UIFlashProperties source, bool fireEvent )
	{
		_propertyName = new UndoRedo<string>( owner, source.propertyName );
		_propertyValue = new TextRef( owner, source.propertyValue );
		_propertyName.Changed += FireChangedEvent;
		_propertyValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIFlashProperties source = _source as UIFlashProperties;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFlashProperties" );
		propertyName = source.propertyName;
		propertyValue = source.propertyValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIFlashProperties newParent = _newParent as UIFlashProperties;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_propertyName.SetParent( newParent == null ? null : newParent._propertyName );
		_propertyValue.SetParent( newParent == null ? null : newParent._propertyValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_propertyName.Reset();
		_propertyValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_propertyName.IsDerivedFromParent()
			&& _propertyValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "propertyName" )
			_propertyName.Reset();
		else if ( fieldName == "propertyValue" )
			_propertyValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "propertyName" )
			return _propertyName.IsDerivedFromParent();
		if ( fieldName == "propertyValue" )
			return _propertyValue.IsDerivedFromParent();
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

public class UIHealthStripes : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIHealthStripes __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _stripe1Step;
	private UndoRedo<float> _stripe2Step;
	private HDRColor _allyColor100;
	private HDRColor _enemyColor100;
	private HDRColor _allyColor1000;
	private HDRColor _enemyColor1000;

	public float stripe1Step { get { return _stripe1Step.Get(); } set { _stripe1Step.Set( value ); } }

	public float stripe2Step { get { return _stripe2Step.Get(); } set { _stripe2Step.Set( value ); } }

	public HDRColor allyColor100 { get { return _allyColor100; } set { _allyColor100.Assign( value ); } }

	public HDRColor enemyColor100 { get { return _enemyColor100; } set { _enemyColor100.Assign( value ); } }

	public HDRColor allyColor1000 { get { return _allyColor1000; } set { _allyColor1000.Assign( value ); } }

	public HDRColor enemyColor1000 { get { return _enemyColor1000; } set { _enemyColor1000.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_stripe1Step = new UndoRedo<float>( owner, 100.0f );
		_stripe2Step = new UndoRedo<float>( owner, 1000.0f );
		_allyColor100 = new HDRColor( owner );
		_enemyColor100 = new HDRColor( owner );
		HDRColor __allyColor1000 = new HDRColor(); // Construct default object for allyColor1000
		__allyColor1000.R = 1.0f;
		__allyColor1000.G = 0.68f;
		__allyColor1000.B = 0.19f;
		_allyColor1000 = new HDRColor( owner, __allyColor1000 );
		HDRColor __enemyColor1000 = new HDRColor(); // Construct default object for enemyColor1000
		__enemyColor1000.R = 1.0f;
		__enemyColor1000.G = 0.68f;
		__enemyColor1000.B = 0.19f;
		_enemyColor1000 = new HDRColor( owner, __enemyColor1000 );
		_stripe1Step.Changed += FireChangedEvent;
		_stripe2Step.Changed += FireChangedEvent;
		_allyColor100.Changed += FireChangedEvent;
		_enemyColor100.Changed += FireChangedEvent;
		_allyColor1000.Changed += FireChangedEvent;
		_enemyColor1000.Changed += FireChangedEvent;
	}

	public UIHealthStripes()
	{
		Initialize( GetOwner() );
	}

	public UIHealthStripes( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIHealthStripes( DBResource owner, UIHealthStripes source )
		: this(owner, source, true){}

	protected UIHealthStripes( DBResource owner, UIHealthStripes source, bool fireEvent )
	{
		_stripe1Step = new UndoRedo<float>( owner, source.stripe1Step );
		_stripe2Step = new UndoRedo<float>( owner, source.stripe2Step );
		_allyColor100 = new HDRColor( owner, source.allyColor100 );
		_enemyColor100 = new HDRColor( owner, source.enemyColor100 );
		_allyColor1000 = new HDRColor( owner, source.allyColor1000 );
		_enemyColor1000 = new HDRColor( owner, source.enemyColor1000 );
		_stripe1Step.Changed += FireChangedEvent;
		_stripe2Step.Changed += FireChangedEvent;
		_allyColor100.Changed += FireChangedEvent;
		_enemyColor100.Changed += FireChangedEvent;
		_allyColor1000.Changed += FireChangedEvent;
		_enemyColor1000.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIHealthStripes source = _source as UIHealthStripes;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIHealthStripes" );
		stripe1Step = source.stripe1Step;
		stripe2Step = source.stripe2Step;
		allyColor100 = source.allyColor100;
		enemyColor100 = source.enemyColor100;
		allyColor1000 = source.allyColor1000;
		enemyColor1000 = source.enemyColor1000;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIHealthStripes newParent = _newParent as UIHealthStripes;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_stripe1Step.SetParent( newParent == null ? null : newParent._stripe1Step );
		_stripe2Step.SetParent( newParent == null ? null : newParent._stripe2Step );
		_allyColor100.SetParent( newParent == null ? null : newParent._allyColor100 );
		_enemyColor100.SetParent( newParent == null ? null : newParent._enemyColor100 );
		_allyColor1000.SetParent( newParent == null ? null : newParent._allyColor1000 );
		_enemyColor1000.SetParent( newParent == null ? null : newParent._enemyColor1000 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_stripe1Step.Reset();
		_stripe2Step.Reset();
		_allyColor100.Reset();
		_enemyColor100.Reset();
		_allyColor1000.Reset();
		_enemyColor1000.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_stripe1Step.IsDerivedFromParent()
			&& _stripe2Step.IsDerivedFromParent()
			&& _allyColor100.IsDerivedFromParent()
			&& _enemyColor100.IsDerivedFromParent()
			&& _allyColor1000.IsDerivedFromParent()
			&& _enemyColor1000.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "stripe1Step" )
			_stripe1Step.Reset();
		else if ( fieldName == "stripe2Step" )
			_stripe2Step.Reset();
		else if ( fieldName == "allyColor100" )
			_allyColor100.Reset();
		else if ( fieldName == "enemyColor100" )
			_enemyColor100.Reset();
		else if ( fieldName == "allyColor1000" )
			_allyColor1000.Reset();
		else if ( fieldName == "enemyColor1000" )
			_enemyColor1000.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "stripe1Step" )
			return _stripe1Step.IsDerivedFromParent();
		if ( fieldName == "stripe2Step" )
			return _stripe2Step.IsDerivedFromParent();
		if ( fieldName == "allyColor100" )
			return _allyColor100.IsDerivedFromParent();
		if ( fieldName == "enemyColor100" )
			return _enemyColor100.IsDerivedFromParent();
		if ( fieldName == "allyColor1000" )
			return _allyColor1000.IsDerivedFromParent();
		if ( fieldName == "enemyColor1000" )
			return _enemyColor1000.IsDerivedFromParent();
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
public class UIPageTabElement : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIPageTabElement __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<UIRadioButtonLayout> _button;
	private UndoRedoDBPtr<UIImageLabelLayout> _page;

	public DBPtr<UIRadioButtonLayout> button { get { return _button.Get(); } set { _button.Set( value ); } }

	public DBPtr<UIImageLabelLayout> page { get { return _page.Get(); } set { _page.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_button = new UndoRedoDBPtr<UIRadioButtonLayout>( owner );
		_page = new UndoRedoDBPtr<UIImageLabelLayout>( owner );
		_button.Changed += FireChangedEvent;
		_page.Changed += FireChangedEvent;
	}

	public UIPageTabElement()
	{
		Initialize( GetOwner() );
	}

	public UIPageTabElement( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIPageTabElement( DBResource owner, UIPageTabElement source )
		: this(owner, source, true){}

	protected UIPageTabElement( DBResource owner, UIPageTabElement source, bool fireEvent )
	{
		_button = new UndoRedoDBPtr<UIRadioButtonLayout>( owner, source.button );
		_page = new UndoRedoDBPtr<UIImageLabelLayout>( owner, source.page );
		_button.Changed += FireChangedEvent;
		_page.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIPageTabElement source = _source as UIPageTabElement;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIPageTabElement" );
		button = source.button;
		page = source.page;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIPageTabElement newParent = _newParent as UIPageTabElement;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_button.SetParent( newParent == null ? null : newParent._button );
		_page.SetParent( newParent == null ? null : newParent._page );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_button.Reset();
		_page.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_button.IsDerivedFromParent()
			&& _page.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "button" )
			_button.Reset();
		else if ( fieldName == "page" )
			_page.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "button" )
			return _button.IsDerivedFromParent();
		if ( fieldName == "page" )
			return _page.IsDerivedFromParent();
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

public class UIPlainOvertipDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIPlainOvertipDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EUIOvertipBindPoint> _bindPoint;
	private UndoRedoDBPtr<UILayout> _layout;
	private UndoRedo<bool> _useDepth;
	private UndoRedo<float> _depthBias;
	private FloatPoint _offset;

	public EUIOvertipBindPoint bindPoint { get { return _bindPoint.Get(); } set { _bindPoint.Set( value ); } }

	public DBPtr<UILayout> layout { get { return _layout.Get(); } set { _layout.Set( value ); } }

	public bool useDepth { get { return _useDepth.Get(); } set { _useDepth.Set( value ); } }

	public float depthBias { get { return _depthBias.Get(); } set { _depthBias.Set( value ); } }

	public FloatPoint offset { get { return _offset; } set { _offset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_bindPoint = new UndoRedo<EUIOvertipBindPoint>( owner, EUIOvertipBindPoint.Center );
		_layout = new UndoRedoDBPtr<UILayout>( owner );
		_useDepth = new UndoRedo<bool>( owner, false );
		_depthBias = new UndoRedo<float>( owner, 0.0f );
		_offset = new FloatPoint( owner );
		_bindPoint.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
		_useDepth.Changed += FireChangedEvent;
		_depthBias.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
	}

	public UIPlainOvertipDesc()
	{
		Initialize( GetOwner() );
	}

	public UIPlainOvertipDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIPlainOvertipDesc( DBResource owner, UIPlainOvertipDesc source )
		: this(owner, source, true){}

	protected UIPlainOvertipDesc( DBResource owner, UIPlainOvertipDesc source, bool fireEvent )
	{
		_bindPoint = new UndoRedo<EUIOvertipBindPoint>( owner, source.bindPoint );
		_layout = new UndoRedoDBPtr<UILayout>( owner, source.layout );
		_useDepth = new UndoRedo<bool>( owner, source.useDepth );
		_depthBias = new UndoRedo<float>( owner, source.depthBias );
		_offset = new FloatPoint( owner, source.offset );
		_bindPoint.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
		_useDepth.Changed += FireChangedEvent;
		_depthBias.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIPlainOvertipDesc source = _source as UIPlainOvertipDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIPlainOvertipDesc" );
		bindPoint = source.bindPoint;
		layout = source.layout;
		useDepth = source.useDepth;
		depthBias = source.depthBias;
		offset = source.offset;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIPlainOvertipDesc newParent = _newParent as UIPlainOvertipDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_bindPoint.SetParent( newParent == null ? null : newParent._bindPoint );
		_layout.SetParent( newParent == null ? null : newParent._layout );
		_useDepth.SetParent( newParent == null ? null : newParent._useDepth );
		_depthBias.SetParent( newParent == null ? null : newParent._depthBias );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_bindPoint.Reset();
		_layout.Reset();
		_useDepth.Reset();
		_depthBias.Reset();
		_offset.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_bindPoint.IsDerivedFromParent()
			&& _layout.IsDerivedFromParent()
			&& _useDepth.IsDerivedFromParent()
			&& _depthBias.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "bindPoint" )
			_bindPoint.Reset();
		else if ( fieldName == "layout" )
			_layout.Reset();
		else if ( fieldName == "useDepth" )
			_useDepth.Reset();
		else if ( fieldName == "depthBias" )
			_depthBias.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "bindPoint" )
			return _bindPoint.IsDerivedFromParent();
		if ( fieldName == "layout" )
			return _layout.IsDerivedFromParent();
		if ( fieldName == "useDepth" )
			return _useDepth.IsDerivedFromParent();
		if ( fieldName == "depthBias" )
			return _depthBias.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
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

[IndexField("id")]
[NeedAssignOperator]
[NeedEqualOperator]
public class UIRelatedLayout : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIRelatedLayout __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private UndoRedoDBPtr<UILayout> _layout;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public DBPtr<UILayout> layout { get { return _layout.Get(); } set { _layout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_layout = new UndoRedoDBPtr<UILayout>( owner );
		_id.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
	}

	public UIRelatedLayout()
	{
		Initialize( GetOwner() );
	}

	public UIRelatedLayout( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIRelatedLayout( DBResource owner, UIRelatedLayout source )
		: this(owner, source, true){}

	protected UIRelatedLayout( DBResource owner, UIRelatedLayout source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_layout = new UndoRedoDBPtr<UILayout>( owner, source.layout );
		_id.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIRelatedLayout source = _source as UIRelatedLayout;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIRelatedLayout" );
		id = source.id;
		layout = source.layout;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIRelatedLayout newParent = _newParent as UIRelatedLayout;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_layout.SetParent( newParent == null ? null : newParent._layout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_layout.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _layout.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "layout" )
			_layout.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "layout" )
			return _layout.IsDerivedFromParent();
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

[IndexField("id")]
[NeedAssignOperator]
[NeedEqualOperator]
public class UIRelatedText : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIRelatedText __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private TextRef _relatedText;
	private UndoRedo<string> _comment;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public TextRef relatedText { get { return _relatedText; } set { _relatedText.Assign( value ); } }

	public string comment { get { return _comment.Get(); } set { _comment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_relatedText = new TextRef( owner, new TextRef() );
		_comment = new UndoRedo<string>( owner, string.Empty );
		_id.Changed += FireChangedEvent;
		_relatedText.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
	}

	public UIRelatedText()
	{
		Initialize( GetOwner() );
	}

	public UIRelatedText( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIRelatedText( DBResource owner, UIRelatedText source )
		: this(owner, source, true){}

	protected UIRelatedText( DBResource owner, UIRelatedText source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_relatedText = new TextRef( owner, source.relatedText );
		_comment = new UndoRedo<string>( owner, source.comment );
		_id.Changed += FireChangedEvent;
		_relatedText.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIRelatedText source = _source as UIRelatedText;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIRelatedText" );
		id = source.id;
		relatedText = source.relatedText;
		comment = source.comment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIRelatedText newParent = _newParent as UIRelatedText;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_relatedText.SetParent( newParent == null ? null : newParent._relatedText );
		_comment.SetParent( newParent == null ? null : newParent._comment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_relatedText.Reset();
		_comment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _relatedText.IsDerivedFromParent()
			&& _comment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "relatedText" )
			_relatedText.Reset();
		else if ( fieldName == "comment" )
			_comment.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "relatedText" )
			return _relatedText.IsDerivedFromParent();
		if ( fieldName == "comment" )
			return _comment.IsDerivedFromParent();
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

[IndexField("screenId")]
public class UIScreenDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIScreenDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _screenId;
	private UndoRedoDBPtr<UIBaseLayout> _baseLayout;
	private UndoRedo<string> _comment;

	public string screenId { get { return _screenId.Get(); } set { _screenId.Set( value ); } }

	public DBPtr<UIBaseLayout> baseLayout { get { return _baseLayout.Get(); } set { _baseLayout.Set( value ); } }

	public string comment { get { return _comment.Get(); } set { _comment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_screenId = new UndoRedo<string>( owner, string.Empty );
		_baseLayout = new UndoRedoDBPtr<UIBaseLayout>( owner );
		_comment = new UndoRedo<string>( owner, string.Empty );
		_screenId.Changed += FireChangedEvent;
		_baseLayout.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
	}

	public UIScreenDesc()
	{
		Initialize( GetOwner() );
	}

	public UIScreenDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIScreenDesc( DBResource owner, UIScreenDesc source )
		: this(owner, source, true){}

	protected UIScreenDesc( DBResource owner, UIScreenDesc source, bool fireEvent )
	{
		_screenId = new UndoRedo<string>( owner, source.screenId );
		_baseLayout = new UndoRedoDBPtr<UIBaseLayout>( owner, source.baseLayout );
		_comment = new UndoRedo<string>( owner, source.comment );
		_screenId.Changed += FireChangedEvent;
		_baseLayout.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIScreenDesc source = _source as UIScreenDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScreenDesc" );
		screenId = source.screenId;
		baseLayout = source.baseLayout;
		comment = source.comment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIScreenDesc newParent = _newParent as UIScreenDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_screenId.SetParent( newParent == null ? null : newParent._screenId );
		_baseLayout.SetParent( newParent == null ? null : newParent._baseLayout );
		_comment.SetParent( newParent == null ? null : newParent._comment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_screenId.Reset();
		_baseLayout.Reset();
		_comment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_screenId.IsDerivedFromParent()
			&& _baseLayout.IsDerivedFromParent()
			&& _comment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "screenId" )
			_screenId.Reset();
		else if ( fieldName == "baseLayout" )
			_baseLayout.Reset();
		else if ( fieldName == "comment" )
			_comment.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "screenId" )
			return _screenId.IsDerivedFromParent();
		if ( fieldName == "baseLayout" )
			return _baseLayout.IsDerivedFromParent();
		if ( fieldName == "comment" )
			return _comment.IsDerivedFromParent();
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

public class UIScriptDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIScriptDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _scriptFile;

	public string scriptFile { get { return _scriptFile.Get(); } set { _scriptFile.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_scriptFile = new UndoRedo<string>( owner, string.Empty );
		_scriptFile.Changed += FireChangedEvent;
	}

	public UIScriptDesc()
	{
		Initialize( GetOwner() );
	}

	public UIScriptDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIScriptDesc( DBResource owner, UIScriptDesc source )
		: this(owner, source, true){}

	protected UIScriptDesc( DBResource owner, UIScriptDesc source, bool fireEvent )
	{
		_scriptFile = new UndoRedo<string>( owner, source.scriptFile );
		_scriptFile.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIScriptDesc source = _source as UIScriptDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScriptDesc" );
		scriptFile = source.scriptFile;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIScriptDesc newParent = _newParent as UIScriptDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_scriptFile.SetParent( newParent == null ? null : newParent._scriptFile );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_scriptFile.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_scriptFile.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "scriptFile" )
			_scriptFile.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "scriptFile" )
			return _scriptFile.IsDerivedFromParent();
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
public class UIScrollLimits : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIScrollLimits __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _inMin;
	private UndoRedo<float> _inMax;
	private UndoRedo<int> _outMin;
	private UndoRedo<int> _outMax;

	public float inMin { get { return _inMin.Get(); } set { _inMin.Set( value ); } }

	public float inMax { get { return _inMax.Get(); } set { _inMax.Set( value ); } }

	public int outMin { get { return _outMin.Get(); } set { _outMin.Set( value ); } }

	public int outMax { get { return _outMax.Get(); } set { _outMax.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_inMin = new UndoRedo<float>( owner, 0.0f );
		_inMax = new UndoRedo<float>( owner, 1.0f );
		_outMin = new UndoRedo<int>( owner, 0 );
		_outMax = new UndoRedo<int>( owner, 0 );
		_inMin.Changed += FireChangedEvent;
		_inMax.Changed += FireChangedEvent;
		_outMin.Changed += FireChangedEvent;
		_outMax.Changed += FireChangedEvent;
	}

	public UIScrollLimits()
	{
		Initialize( GetOwner() );
	}

	public UIScrollLimits( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIScrollLimits( DBResource owner, UIScrollLimits source )
		: this(owner, source, true){}

	protected UIScrollLimits( DBResource owner, UIScrollLimits source, bool fireEvent )
	{
		_inMin = new UndoRedo<float>( owner, source.inMin );
		_inMax = new UndoRedo<float>( owner, source.inMax );
		_outMin = new UndoRedo<int>( owner, source.outMin );
		_outMax = new UndoRedo<int>( owner, source.outMax );
		_inMin.Changed += FireChangedEvent;
		_inMax.Changed += FireChangedEvent;
		_outMin.Changed += FireChangedEvent;
		_outMax.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIScrollLimits source = _source as UIScrollLimits;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScrollLimits" );
		inMin = source.inMin;
		inMax = source.inMax;
		outMin = source.outMin;
		outMax = source.outMax;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIScrollLimits newParent = _newParent as UIScrollLimits;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_inMin.SetParent( newParent == null ? null : newParent._inMin );
		_inMax.SetParent( newParent == null ? null : newParent._inMax );
		_outMin.SetParent( newParent == null ? null : newParent._outMin );
		_outMax.SetParent( newParent == null ? null : newParent._outMax );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_inMin.Reset();
		_inMax.Reset();
		_outMin.Reset();
		_outMax.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_inMin.IsDerivedFromParent()
			&& _inMax.IsDerivedFromParent()
			&& _outMin.IsDerivedFromParent()
			&& _outMax.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "inMin" )
			_inMin.Reset();
		else if ( fieldName == "inMax" )
			_inMax.Reset();
		else if ( fieldName == "outMin" )
			_outMin.Reset();
		else if ( fieldName == "outMax" )
			_outMax.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "inMin" )
			return _inMin.IsDerivedFromParent();
		if ( fieldName == "inMax" )
			return _inMax.IsDerivedFromParent();
		if ( fieldName == "outMin" )
			return _outMin.IsDerivedFromParent();
		if ( fieldName == "outMax" )
			return _outMax.IsDerivedFromParent();
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

public class UISoundDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UISoundDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}


	private void Initialize( DBResource owner )
	{
	}

	public UISoundDesc()
	{
		Initialize( GetOwner() );
	}

	public UISoundDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UISoundDesc( DBResource owner, UISoundDesc source )
		: this(owner, source, true){}

	protected UISoundDesc( DBResource owner, UISoundDesc source, bool fireEvent )
	{
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UISoundDesc source = _source as UISoundDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISoundDesc" );
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UISoundDesc newParent = _newParent as UISoundDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			true;
	}

	public virtual void ResetField( string fieldName )
	{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
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

[Custom("Social")]
[IndexField("name")]
public class UIStyleAlias : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIStyleAlias __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedoDBPtr<BaseUIMaterial> _material;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public DBPtr<BaseUIMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_material = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_name.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
	}

	public UIStyleAlias()
	{
		Initialize( GetOwner() );
	}

	public UIStyleAlias( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIStyleAlias( DBResource owner, UIStyleAlias source )
		: this(owner, source, true){}

	protected UIStyleAlias( DBResource owner, UIStyleAlias source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_material = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.material );
		_name.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIStyleAlias source = _source as UIStyleAlias;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIStyleAlias" );
		name = source.name;
		material = source.material;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIStyleAlias newParent = _newParent as UIStyleAlias;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_material.SetParent( newParent == null ? null : newParent._material );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_material.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _material.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
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
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
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

[Custom("Social")]
[IndexField("id")]
public class UITextSubstitute : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UITextSubstitute __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private TextRef _captionText;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public TextRef captionText { get { return _captionText; } set { _captionText.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_captionText = new TextRef( owner, new TextRef() );
		_id.Changed += FireChangedEvent;
		_captionText.Changed += FireChangedEvent;
	}

	public UITextSubstitute()
	{
		Initialize( GetOwner() );
	}

	public UITextSubstitute( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UITextSubstitute( DBResource owner, UITextSubstitute source )
		: this(owner, source, true){}

	protected UITextSubstitute( DBResource owner, UITextSubstitute source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_captionText = new TextRef( owner, source.captionText );
		_id.Changed += FireChangedEvent;
		_captionText.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UITextSubstitute source = _source as UITextSubstitute;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UITextSubstitute" );
		id = source.id;
		captionText = source.captionText;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UITextSubstitute newParent = _newParent as UITextSubstitute;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_captionText.SetParent( newParent == null ? null : newParent._captionText );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_captionText.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _captionText.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "captionText" )
			_captionText.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "captionText" )
			return _captionText.IsDerivedFromParent();
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

public class UICursorBase : DBResource
{
	private UndoRedoDBPtr<UICursorBase> ___parent;
	[HideInOutliner]
	public new DBPtr<UICursorBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UICursorBase>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UICursorBase()
	{
		Initialize( this );
	}
	private void AssignSelf( UICursorBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UICursorBase" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UICursorBase source = _source as UICursorBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICursorBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UICursorBase newParent = rawParent == null ? null : rawParent.Get<UICursorBase>();
		if ( newParent == null && _newParent is UICursorBase )
			newParent = _newParent as UICursorBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[HasStates]
[IndexField("name")]
[NeedAssignOperator]
[NeedEqualOperator]
public class UILayout : DBResource
{
	private UndoRedoDBPtr<UILayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UILayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;
	private UndoRedo<bool> _visible;
	private UndoRedo<bool> _enabled;
	private FloatPoint _location;
	private FloatPoint _size;
	private UndoRedo<EUIElementHAlign> _hAlign;
	private UndoRedo<EUIElementVAlign> _vAlign;
	private UndoRedo<EUIElementAspectRatio> _keepAspectRatio;
	private UndoRedo<string> _subclass;
	private UndoRedo<string> _scriptFile;
	private UICursors _cursors;
	private UndoRedoAssignableList<DBPtr<UILayout>> _subLayouts;
	private UndoRedo<bool> _draggable;
	private UICatchEvents _defaultEventsCatch;
	private UndoRedo<bool> _transparent;
	private UndoRedo<bool> _cursorTransparent;
	private UndoRedo<bool> _needCrop;
	private UndoRedoAssignableList<UIRelatedLayout> _relatedLayouts;
	private UndoRedoAssignableList<UIRelatedText> _relatedTexts;
	private TextRef _tooltipText;
	private DBFMODEventDesc _soundShow;
	private DBFMODEventDesc _soundHide;
	private DBFMODEventDesc _soundActivate;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public bool visible { get { return _visible.Get(); } set { _visible.Set( value ); } }

	public bool enabled { get { return _enabled.Get(); } set { _enabled.Set( value ); } }

	public FloatPoint location { get { return _location; } set { _location.Assign( value ); } }

	public FloatPoint size { get { return _size; } set { _size.Assign( value ); } }

	public EUIElementHAlign hAlign { get { return _hAlign.Get(); } set { _hAlign.Set( value ); } }

	public EUIElementVAlign vAlign { get { return _vAlign.Get(); } set { _vAlign.Set( value ); } }

	public EUIElementAspectRatio keepAspectRatio { get { return _keepAspectRatio.Get(); } set { _keepAspectRatio.Set( value ); } }

	public string subclass { get { return _subclass.Get(); } set { _subclass.Set( value ); } }

	[FileRef("*.lua")]
	public string scriptFile { get { return _scriptFile.Get(); } set { _scriptFile.Set( value ); } }

	public UICursors cursors { get { return _cursors; } set { _cursors.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<UILayout>> subLayouts { get { return _subLayouts; } set { _subLayouts.Assign( value ); } }

	public bool draggable { get { return _draggable.Get(); } set { _draggable.Set( value ); } }

	public UICatchEvents defaultEventsCatch { get { return _defaultEventsCatch; } set { _defaultEventsCatch.Assign( value ); } }

	public bool transparent { get { return _transparent.Get(); } set { _transparent.Set( value ); } }

	public bool cursorTransparent { get { return _cursorTransparent.Get(); } set { _cursorTransparent.Set( value ); } }

	public bool needCrop { get { return _needCrop.Get(); } set { _needCrop.Set( value ); } }

	public libdb.IChangeableList<UIRelatedLayout> relatedLayouts { get { return _relatedLayouts; } set { _relatedLayouts.Assign( value ); } }

	public libdb.IChangeableList<UIRelatedText> relatedTexts { get { return _relatedTexts; } set { _relatedTexts.Assign( value ); } }

	public TextRef tooltipText { get { return _tooltipText; } set { _tooltipText.Assign( value ); } }

	[Description( "Sound event that will be started when window becomes visible" )]
	public DBFMODEventDesc soundShow { get { return _soundShow; } set { _soundShow.Assign( value ); } }

	[Description( "Sound event that will be started when window becomes invisible" )]
	public DBFMODEventDesc soundHide { get { return _soundHide; } set { _soundHide.Assign( value ); } }

	[Description( "Sound event that will be started on activation" )]
	public DBFMODEventDesc soundActivate { get { return _soundActivate; } set { _soundActivate.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UILayout>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		_visible = new UndoRedo<bool>( owner, true );
		_enabled = new UndoRedo<bool>( owner, true );
		_location = new FloatPoint( owner );
		FloatPoint __size = new FloatPoint(); // Construct default object for size
		__size.x = 1280;
		__size.y = 1024;
		_size = new FloatPoint( owner, __size );
		_hAlign = new UndoRedo<EUIElementHAlign>( owner, EUIElementHAlign.Left );
		_vAlign = new UndoRedo<EUIElementVAlign>( owner, EUIElementVAlign.Top );
		_keepAspectRatio = new UndoRedo<EUIElementAspectRatio>( owner, EUIElementAspectRatio.DontCare );
		_subclass = new UndoRedo<string>( owner, string.Empty );
		_scriptFile = new UndoRedo<string>( owner, string.Empty );
		_cursors = new UICursors( owner );
		_subLayouts = new UndoRedoAssignableList<DBPtr<UILayout>>( owner );
		_draggable = new UndoRedo<bool>( owner, false );
		_defaultEventsCatch = new UICatchEvents( owner );
		_transparent = new UndoRedo<bool>( owner, false );
		_cursorTransparent = new UndoRedo<bool>( owner, false );
		_needCrop = new UndoRedo<bool>( owner, false );
		_relatedLayouts = new UndoRedoAssignableList<UIRelatedLayout>( owner );
		_relatedTexts = new UndoRedoAssignableList<UIRelatedText>( owner );
		_tooltipText = new TextRef( owner, new TextRef() );
		_soundShow = new DBFMODEventDesc( owner );
		_soundHide = new DBFMODEventDesc( owner );
		_soundActivate = new DBFMODEventDesc( owner );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_visible.Changed += FireChangedEvent;
		_enabled.Changed += FireChangedEvent;
		_location.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
		_hAlign.Changed += FireChangedEvent;
		_vAlign.Changed += FireChangedEvent;
		_keepAspectRatio.Changed += FireChangedEvent;
		_subclass.Changed += FireChangedEvent;
		_scriptFile.Changed += FireChangedEvent;
		_cursors.Changed += FireChangedEvent;
		_subLayouts.Changed += FireChangedEvent;
		_draggable.Changed += FireChangedEvent;
		_defaultEventsCatch.Changed += FireChangedEvent;
		_transparent.Changed += FireChangedEvent;
		_cursorTransparent.Changed += FireChangedEvent;
		_needCrop.Changed += FireChangedEvent;
		_relatedLayouts.Changed += FireChangedEvent;
		_relatedTexts.Changed += FireChangedEvent;
		_tooltipText.Changed += FireChangedEvent;
		_soundShow.Changed += FireChangedEvent;
		_soundHide.Changed += FireChangedEvent;
		_soundActivate.Changed += FireChangedEvent;
	}

	public UILayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UILayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UILayout" );
		name = source.name;
		visible = source.visible;
		enabled = source.enabled;
		location = source.location;
		size = source.size;
		hAlign = source.hAlign;
		vAlign = source.vAlign;
		keepAspectRatio = source.keepAspectRatio;
		subclass = source.subclass;
		scriptFile = source.scriptFile;
		cursors = source.cursors;
		subLayouts = source.subLayouts;
		draggable = source.draggable;
		defaultEventsCatch = source.defaultEventsCatch;
		transparent = source.transparent;
		cursorTransparent = source.cursorTransparent;
		needCrop = source.needCrop;
		relatedLayouts = source.relatedLayouts;
		relatedTexts = source.relatedTexts;
		tooltipText = source.tooltipText;
		soundShow = source.soundShow;
		soundHide = source.soundHide;
		soundActivate = source.soundActivate;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UILayout source = _source as UILayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UILayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UILayout newParent = rawParent == null ? null : rawParent.Get<UILayout>();
		if ( newParent == null && _newParent is UILayout )
			newParent = _newParent as UILayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_visible.SetParent( newParent == null ? null : newParent._visible );
		_enabled.SetParent( newParent == null ? null : newParent._enabled );
		_location.SetParent( newParent == null ? null : newParent._location );
		_size.SetParent( newParent == null ? null : newParent._size );
		_hAlign.SetParent( newParent == null ? null : newParent._hAlign );
		_vAlign.SetParent( newParent == null ? null : newParent._vAlign );
		_keepAspectRatio.SetParent( newParent == null ? null : newParent._keepAspectRatio );
		_subclass.SetParent( newParent == null ? null : newParent._subclass );
		_scriptFile.SetParent( newParent == null ? null : newParent._scriptFile );
		_cursors.SetParent( newParent == null ? null : newParent._cursors );
		_subLayouts.SetParent( newParent == null ? null : newParent._subLayouts );
		_draggable.SetParent( newParent == null ? null : newParent._draggable );
		_defaultEventsCatch.SetParent( newParent == null ? null : newParent._defaultEventsCatch );
		_transparent.SetParent( newParent == null ? null : newParent._transparent );
		_cursorTransparent.SetParent( newParent == null ? null : newParent._cursorTransparent );
		_needCrop.SetParent( newParent == null ? null : newParent._needCrop );
		_relatedLayouts.SetParent( newParent == null ? null : newParent._relatedLayouts );
		_relatedTexts.SetParent( newParent == null ? null : newParent._relatedTexts );
		_tooltipText.SetParent( newParent == null ? null : newParent._tooltipText );
		_soundShow.SetParent( newParent == null ? null : newParent._soundShow );
		_soundHide.SetParent( newParent == null ? null : newParent._soundHide );
		_soundActivate.SetParent( newParent == null ? null : newParent._soundActivate );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_visible.Reset();
		_enabled.Reset();
		_location.Reset();
		_size.Reset();
		_hAlign.Reset();
		_vAlign.Reset();
		_keepAspectRatio.Reset();
		_subclass.Reset();
		_scriptFile.Reset();
		_cursors.Reset();
		_subLayouts.Reset();
		_draggable.Reset();
		_defaultEventsCatch.Reset();
		_transparent.Reset();
		_cursorTransparent.Reset();
		_needCrop.Reset();
		_relatedLayouts.Reset();
		_relatedTexts.Reset();
		_tooltipText.Reset();
		_soundShow.Reset();
		_soundHide.Reset();
		_soundActivate.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _visible.IsDerivedFromParent()
			&& _enabled.IsDerivedFromParent()
			&& _location.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& _hAlign.IsDerivedFromParent()
			&& _vAlign.IsDerivedFromParent()
			&& _keepAspectRatio.IsDerivedFromParent()
			&& _subclass.IsDerivedFromParent()
			&& _scriptFile.IsDerivedFromParent()
			&& _cursors.IsDerivedFromParent()
			&& _subLayouts.IsDerivedFromParent()
			&& _draggable.IsDerivedFromParent()
			&& _defaultEventsCatch.IsDerivedFromParent()
			&& _transparent.IsDerivedFromParent()
			&& _cursorTransparent.IsDerivedFromParent()
			&& _needCrop.IsDerivedFromParent()
			&& _relatedLayouts.IsDerivedFromParent()
			&& _relatedTexts.IsDerivedFromParent()
			&& _tooltipText.IsDerivedFromParent()
			&& _soundShow.IsDerivedFromParent()
			&& _soundHide.IsDerivedFromParent()
			&& _soundActivate.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "visible" )
			_visible.Reset();
		else if ( fieldName == "enabled" )
			_enabled.Reset();
		else if ( fieldName == "location" )
			_location.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else if ( fieldName == "hAlign" )
			_hAlign.Reset();
		else if ( fieldName == "vAlign" )
			_vAlign.Reset();
		else if ( fieldName == "keepAspectRatio" )
			_keepAspectRatio.Reset();
		else if ( fieldName == "subclass" )
			_subclass.Reset();
		else if ( fieldName == "scriptFile" )
			_scriptFile.Reset();
		else if ( fieldName == "cursors" )
			_cursors.Reset();
		else if ( fieldName == "subLayouts" )
			_subLayouts.Reset();
		else if ( fieldName == "draggable" )
			_draggable.Reset();
		else if ( fieldName == "defaultEventsCatch" )
			_defaultEventsCatch.Reset();
		else if ( fieldName == "transparent" )
			_transparent.Reset();
		else if ( fieldName == "cursorTransparent" )
			_cursorTransparent.Reset();
		else if ( fieldName == "needCrop" )
			_needCrop.Reset();
		else if ( fieldName == "relatedLayouts" )
			_relatedLayouts.Reset();
		else if ( fieldName == "relatedTexts" )
			_relatedTexts.Reset();
		else if ( fieldName == "tooltipText" )
			_tooltipText.Reset();
		else if ( fieldName == "soundShow" )
			_soundShow.Reset();
		else if ( fieldName == "soundHide" )
			_soundHide.Reset();
		else if ( fieldName == "soundActivate" )
			_soundActivate.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "visible" )
			return _visible.IsDerivedFromParent();
		if ( fieldName == "enabled" )
			return _enabled.IsDerivedFromParent();
		if ( fieldName == "location" )
			return _location.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		if ( fieldName == "hAlign" )
			return _hAlign.IsDerivedFromParent();
		if ( fieldName == "vAlign" )
			return _vAlign.IsDerivedFromParent();
		if ( fieldName == "keepAspectRatio" )
			return _keepAspectRatio.IsDerivedFromParent();
		if ( fieldName == "subclass" )
			return _subclass.IsDerivedFromParent();
		if ( fieldName == "scriptFile" )
			return _scriptFile.IsDerivedFromParent();
		if ( fieldName == "cursors" )
			return _cursors.IsDerivedFromParent();
		if ( fieldName == "subLayouts" )
			return _subLayouts.IsDerivedFromParent();
		if ( fieldName == "draggable" )
			return _draggable.IsDerivedFromParent();
		if ( fieldName == "defaultEventsCatch" )
			return _defaultEventsCatch.IsDerivedFromParent();
		if ( fieldName == "transparent" )
			return _transparent.IsDerivedFromParent();
		if ( fieldName == "cursorTransparent" )
			return _cursorTransparent.IsDerivedFromParent();
		if ( fieldName == "needCrop" )
			return _needCrop.IsDerivedFromParent();
		if ( fieldName == "relatedLayouts" )
			return _relatedLayouts.IsDerivedFromParent();
		if ( fieldName == "relatedTexts" )
			return _relatedTexts.IsDerivedFromParent();
		if ( fieldName == "tooltipText" )
			return _tooltipText.IsDerivedFromParent();
		if ( fieldName == "soundShow" )
			return _soundShow.IsDerivedFromParent();
		if ( fieldName == "soundHide" )
			return _soundHide.IsDerivedFromParent();
		if ( fieldName == "soundActivate" )
			return _soundActivate.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("General", "Image Label", "Layout")]
[UseTypeName("IMGLBL")]
public class UIImageLabelLayout : UILayout
{
	private UndoRedoDBPtr<UIImageLabelLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIImageLabelLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _backgroundMaterial;
	private UndoRedo<EImageLabelShapeType> _shapeType;
	private TextRef _captionText;
	private UndoRedo<string> _fontStyle;
	private UndoRedo<bool> _wordWrap;
	private UndoRedo<bool> _stretchText;
	private UndoRedo<bool> _rawTextMode;
	private UndoRedo<EUITextVAlign> _textVAlign;
	private UndoRedo<EUITextHAlign> _textHAlign;
	private FloatRect _textMargins;
	private UndoRedo<float> _captionOpacity;

	public DBPtr<BaseUIMaterial> backgroundMaterial { get { return _backgroundMaterial.Get(); } set { _backgroundMaterial.Set( value ); } }

	[Category( "Shape" )]
	public EImageLabelShapeType shapeType { get { return _shapeType.Get(); } set { _shapeType.Set( value ); } }

	[Category( "Text" )]
	public TextRef captionText { get { return _captionText; } set { _captionText.Assign( value ); } }

	[Category( "Text" )]
	public string fontStyle { get { return _fontStyle.Get(); } set { _fontStyle.Set( value ); } }

	[Description( "Words in text will wrap around right margin" )]
	public bool wordWrap { get { return _wordWrap.Get(); } set { _wordWrap.Set( value ); } }

	[Description( "Text will stretch to given width, if possible" )]
	public bool stretchText { get { return _stretchText.Get(); } set { _stretchText.Set( value ); } }

	[Description( "Disable text formating tags etc" )]
	public bool rawTextMode { get { return _rawTextMode.Get(); } set { _rawTextMode.Set( value ); } }

	[Category( "Text" )]
	public EUITextVAlign textVAlign { get { return _textVAlign.Get(); } set { _textVAlign.Set( value ); } }

	[Category( "Text" )]
	public EUITextHAlign textHAlign { get { return _textHAlign.Get(); } set { _textHAlign.Set( value ); } }

	[Category( "Text" )]
	public FloatRect textMargins { get { return _textMargins; } set { _textMargins.Assign( value ); } }

	[Category( "Text" )]
	public float captionOpacity { get { return _captionOpacity.Get(); } set { _captionOpacity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIImageLabelLayout>(owner);
		_backgroundMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_shapeType = new UndoRedo<EImageLabelShapeType>( owner, EImageLabelShapeType.FromShapeOrBackgroundStyle );
		_captionText = new TextRef( owner, new TextRef() );
		_fontStyle = new UndoRedo<string>( owner, string.Empty );
		_wordWrap = new UndoRedo<bool>( owner, true );
		_stretchText = new UndoRedo<bool>( owner, false );
		_rawTextMode = new UndoRedo<bool>( owner, false );
		_textVAlign = new UndoRedo<EUITextVAlign>( owner, EUITextVAlign.Center );
		_textHAlign = new UndoRedo<EUITextHAlign>( owner, EUITextHAlign.Center );
		_textMargins = new FloatRect( owner );
		_captionOpacity = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_backgroundMaterial.Changed += FireChangedEvent;
		_shapeType.Changed += FireChangedEvent;
		_captionText.Changed += FireChangedEvent;
		_fontStyle.Changed += FireChangedEvent;
		_wordWrap.Changed += FireChangedEvent;
		_stretchText.Changed += FireChangedEvent;
		_rawTextMode.Changed += FireChangedEvent;
		_textVAlign.Changed += FireChangedEvent;
		_textHAlign.Changed += FireChangedEvent;
		_textMargins.Changed += FireChangedEvent;
		_captionOpacity.Changed += FireChangedEvent;
	}

	public UIImageLabelLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIImageLabelLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIImageLabelLayout" );
		backgroundMaterial = source.backgroundMaterial;
		shapeType = source.shapeType;
		captionText = source.captionText;
		fontStyle = source.fontStyle;
		wordWrap = source.wordWrap;
		stretchText = source.stretchText;
		rawTextMode = source.rawTextMode;
		textVAlign = source.textVAlign;
		textHAlign = source.textHAlign;
		textMargins = source.textMargins;
		captionOpacity = source.captionOpacity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIImageLabelLayout source = _source as UIImageLabelLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIImageLabelLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIImageLabelLayout newParent = rawParent == null ? null : rawParent.Get<UIImageLabelLayout>();
		if ( newParent == null && _newParent is UIImageLabelLayout )
			newParent = _newParent as UIImageLabelLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_backgroundMaterial.SetParent( newParent == null ? null : newParent._backgroundMaterial );
		_shapeType.SetParent( newParent == null ? null : newParent._shapeType );
		_captionText.SetParent( newParent == null ? null : newParent._captionText );
		_fontStyle.SetParent( newParent == null ? null : newParent._fontStyle );
		_wordWrap.SetParent( newParent == null ? null : newParent._wordWrap );
		_stretchText.SetParent( newParent == null ? null : newParent._stretchText );
		_rawTextMode.SetParent( newParent == null ? null : newParent._rawTextMode );
		_textVAlign.SetParent( newParent == null ? null : newParent._textVAlign );
		_textHAlign.SetParent( newParent == null ? null : newParent._textHAlign );
		_textMargins.SetParent( newParent == null ? null : newParent._textMargins );
		_captionOpacity.SetParent( newParent == null ? null : newParent._captionOpacity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_backgroundMaterial.Reset();
		_shapeType.Reset();
		_captionText.Reset();
		_fontStyle.Reset();
		_wordWrap.Reset();
		_stretchText.Reset();
		_rawTextMode.Reset();
		_textVAlign.Reset();
		_textHAlign.Reset();
		_textMargins.Reset();
		_captionOpacity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_backgroundMaterial.IsDerivedFromParent()
			&& _shapeType.IsDerivedFromParent()
			&& _captionText.IsDerivedFromParent()
			&& _fontStyle.IsDerivedFromParent()
			&& _wordWrap.IsDerivedFromParent()
			&& _stretchText.IsDerivedFromParent()
			&& _rawTextMode.IsDerivedFromParent()
			&& _textVAlign.IsDerivedFromParent()
			&& _textHAlign.IsDerivedFromParent()
			&& _textMargins.IsDerivedFromParent()
			&& _captionOpacity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "backgroundMaterial" )
			_backgroundMaterial.Reset();
		else if ( fieldName == "shapeType" )
			_shapeType.Reset();
		else if ( fieldName == "captionText" )
			_captionText.Reset();
		else if ( fieldName == "fontStyle" )
			_fontStyle.Reset();
		else if ( fieldName == "wordWrap" )
			_wordWrap.Reset();
		else if ( fieldName == "stretchText" )
			_stretchText.Reset();
		else if ( fieldName == "rawTextMode" )
			_rawTextMode.Reset();
		else if ( fieldName == "textVAlign" )
			_textVAlign.Reset();
		else if ( fieldName == "textHAlign" )
			_textHAlign.Reset();
		else if ( fieldName == "textMargins" )
			_textMargins.Reset();
		else if ( fieldName == "captionOpacity" )
			_captionOpacity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "backgroundMaterial" )
			return _backgroundMaterial.IsDerivedFromParent();
		if ( fieldName == "shapeType" )
			return _shapeType.IsDerivedFromParent();
		if ( fieldName == "captionText" )
			return _captionText.IsDerivedFromParent();
		if ( fieldName == "fontStyle" )
			return _fontStyle.IsDerivedFromParent();
		if ( fieldName == "wordWrap" )
			return _wordWrap.IsDerivedFromParent();
		if ( fieldName == "stretchText" )
			return _stretchText.IsDerivedFromParent();
		if ( fieldName == "rawTextMode" )
			return _rawTextMode.IsDerivedFromParent();
		if ( fieldName == "textVAlign" )
			return _textVAlign.IsDerivedFromParent();
		if ( fieldName == "textHAlign" )
			return _textHAlign.IsDerivedFromParent();
		if ( fieldName == "textMargins" )
			return _textMargins.IsDerivedFromParent();
		if ( fieldName == "captionOpacity" )
			return _captionOpacity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CTRL")]
public class UICommonControl : UIImageLabelLayout
{
	private UndoRedoDBPtr<UICommonControl> ___parent;
	[HideInOutliner]
	public new DBPtr<UICommonControl> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUIControlMouseActions> _mouseActions;
	private DBFMODEventDesc _soundHilite;
	private UndoRedo<string> _activationBind;

	public EUIControlMouseActions mouseActions { get { return _mouseActions.Get(); } set { _mouseActions.Set( value ); } }

	[Description( "Sound event that will be started on mouse over" )]
	public DBFMODEventDesc soundHilite { get { return _soundHilite; } set { _soundHilite.Assign( value ); } }

	[Description( "Input bind identifier thaat will activate this control" )]
	public string activationBind { get { return _activationBind.Get(); } set { _activationBind.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UICommonControl>(owner);
		_mouseActions = new UndoRedo<EUIControlMouseActions>( owner, EUIControlMouseActions.Left );
		_soundHilite = new DBFMODEventDesc( owner );
		_activationBind = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_mouseActions.Changed += FireChangedEvent;
		_soundHilite.Changed += FireChangedEvent;
		_activationBind.Changed += FireChangedEvent;
	}

	public UICommonControl()
	{
		Initialize( this );
	}
	private void AssignSelf( UICommonControl source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UICommonControl" );
		mouseActions = source.mouseActions;
		soundHilite = source.soundHilite;
		activationBind = source.activationBind;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UICommonControl source = _source as UICommonControl;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICommonControl" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UICommonControl newParent = rawParent == null ? null : rawParent.Get<UICommonControl>();
		if ( newParent == null && _newParent is UICommonControl )
			newParent = _newParent as UICommonControl;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mouseActions.SetParent( newParent == null ? null : newParent._mouseActions );
		_soundHilite.SetParent( newParent == null ? null : newParent._soundHilite );
		_activationBind.SetParent( newParent == null ? null : newParent._activationBind );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mouseActions.Reset();
		_soundHilite.Reset();
		_activationBind.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mouseActions.IsDerivedFromParent()
			&& _soundHilite.IsDerivedFromParent()
			&& _activationBind.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mouseActions" )
			_mouseActions.Reset();
		else if ( fieldName == "soundHilite" )
			_soundHilite.Reset();
		else if ( fieldName == "activationBind" )
			_activationBind.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mouseActions" )
			return _mouseActions.IsDerivedFromParent();
		if ( fieldName == "soundHilite" )
			return _soundHilite.IsDerivedFromParent();
		if ( fieldName == "activationBind" )
			return _activationBind.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Button", "Button")]
[UseTypeName("BTN")]
public class UIButtonLayout : UICommonControl
{
	private UndoRedoDBPtr<UIButtonLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIButtonLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _highlightMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _pushedMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _disabledMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _flashedMaterial;
	private UndoRedo<EUIButtonViewMode> _viewMode;

	public DBPtr<BaseUIMaterial> highlightMaterial { get { return _highlightMaterial.Get(); } set { _highlightMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> pushedMaterial { get { return _pushedMaterial.Get(); } set { _pushedMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> disabledMaterial { get { return _disabledMaterial.Get(); } set { _disabledMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> flashedMaterial { get { return _flashedMaterial.Get(); } set { _flashedMaterial.Set( value ); } }

	[Description( "Use background material advanced pins or multiple materials" )]
	public EUIButtonViewMode viewMode { get { return _viewMode.Get(); } set { _viewMode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIButtonLayout>(owner);
		_highlightMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_pushedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_disabledMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_flashedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_viewMode = new UndoRedo<EUIButtonViewMode>( owner, EUIButtonViewMode.ByMaterials );
		___parent.Changed += FireChangedEvent;
		_highlightMaterial.Changed += FireChangedEvent;
		_pushedMaterial.Changed += FireChangedEvent;
		_disabledMaterial.Changed += FireChangedEvent;
		_flashedMaterial.Changed += FireChangedEvent;
		_viewMode.Changed += FireChangedEvent;
	}

	public UIButtonLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIButtonLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIButtonLayout" );
		highlightMaterial = source.highlightMaterial;
		pushedMaterial = source.pushedMaterial;
		disabledMaterial = source.disabledMaterial;
		flashedMaterial = source.flashedMaterial;
		viewMode = source.viewMode;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIButtonLayout source = _source as UIButtonLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIButtonLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIButtonLayout newParent = rawParent == null ? null : rawParent.Get<UIButtonLayout>();
		if ( newParent == null && _newParent is UIButtonLayout )
			newParent = _newParent as UIButtonLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_highlightMaterial.SetParent( newParent == null ? null : newParent._highlightMaterial );
		_pushedMaterial.SetParent( newParent == null ? null : newParent._pushedMaterial );
		_disabledMaterial.SetParent( newParent == null ? null : newParent._disabledMaterial );
		_flashedMaterial.SetParent( newParent == null ? null : newParent._flashedMaterial );
		_viewMode.SetParent( newParent == null ? null : newParent._viewMode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_highlightMaterial.Reset();
		_pushedMaterial.Reset();
		_disabledMaterial.Reset();
		_flashedMaterial.Reset();
		_viewMode.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_highlightMaterial.IsDerivedFromParent()
			&& _pushedMaterial.IsDerivedFromParent()
			&& _disabledMaterial.IsDerivedFromParent()
			&& _flashedMaterial.IsDerivedFromParent()
			&& _viewMode.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "highlightMaterial" )
			_highlightMaterial.Reset();
		else if ( fieldName == "pushedMaterial" )
			_pushedMaterial.Reset();
		else if ( fieldName == "disabledMaterial" )
			_disabledMaterial.Reset();
		else if ( fieldName == "flashedMaterial" )
			_flashedMaterial.Reset();
		else if ( fieldName == "viewMode" )
			_viewMode.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "highlightMaterial" )
			return _highlightMaterial.IsDerivedFromParent();
		if ( fieldName == "pushedMaterial" )
			return _pushedMaterial.IsDerivedFromParent();
		if ( fieldName == "disabledMaterial" )
			return _disabledMaterial.IsDerivedFromParent();
		if ( fieldName == "flashedMaterial" )
			return _flashedMaterial.IsDerivedFromParent();
		if ( fieldName == "viewMode" )
			return _viewMode.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class UIContentResource : DBResource
{
	private UndoRedoDBPtr<UIContentResource> ___parent;
	[HideInOutliner]
	public new DBPtr<UIContentResource> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _contentId;

	public string contentId { get { return _contentId.Get(); } set { _contentId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIContentResource>(owner);
		_contentId = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_contentId.Changed += FireChangedEvent;
	}

	public UIContentResource()
	{
		Initialize( this );
	}
	private void AssignSelf( UIContentResource source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIContentResource" );
		contentId = source.contentId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIContentResource source = _source as UIContentResource;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIContentResource" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIContentResource newParent = rawParent == null ? null : rawParent.Get<UIContentResource>();
		if ( newParent == null && _newParent is UIContentResource )
			newParent = _newParent as UIContentResource;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_contentId.SetParent( newParent == null ? null : newParent._contentId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_contentId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_contentId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "contentId" )
			_contentId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "contentId" )
			return _contentId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[UseTypeName("ICUR")]
public class UICursor : UICursorBase
{
	private UndoRedoDBPtr<UICursor> ___parent;
	[HideInOutliner]
	public new DBPtr<UICursor> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _texture;
	private UndoRedo<int> _hotSpotX;
	private UndoRedo<int> _hotSpotY;

	public DBPtr<Texture> texture { get { return _texture.Get(); } set { _texture.Set( value ); } }

	public int hotSpotX { get { return _hotSpotX.Get(); } set { _hotSpotX.Set( value ); } }

	public int hotSpotY { get { return _hotSpotY.Get(); } set { _hotSpotY.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UICursor>(owner);
		_texture = new UndoRedoDBPtr<Texture>( owner );
		_hotSpotX = new UndoRedo<int>( owner, 0 );
		_hotSpotY = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
		_hotSpotX.Changed += FireChangedEvent;
		_hotSpotY.Changed += FireChangedEvent;
	}

	public UICursor()
	{
		Initialize( this );
	}
	private void AssignSelf( UICursor source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UICursor" );
		texture = source.texture;
		hotSpotX = source.hotSpotX;
		hotSpotY = source.hotSpotY;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UICursor source = _source as UICursor;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICursor" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UICursor newParent = rawParent == null ? null : rawParent.Get<UICursor>();
		if ( newParent == null && _newParent is UICursor )
			newParent = _newParent as UICursor;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_texture.SetParent( newParent == null ? null : newParent._texture );
		_hotSpotX.SetParent( newParent == null ? null : newParent._hotSpotX );
		_hotSpotY.SetParent( newParent == null ? null : newParent._hotSpotY );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_texture.Reset();
		_hotSpotX.Reset();
		_hotSpotY.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_texture.IsDerivedFromParent()
			&& _hotSpotX.IsDerivedFromParent()
			&& _hotSpotY.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "texture" )
			_texture.Reset();
		else if ( fieldName == "hotSpotX" )
			_hotSpotX.Reset();
		else if ( fieldName == "hotSpotY" )
			_hotSpotY.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "texture" )
			return _texture.IsDerivedFromParent();
		if ( fieldName == "hotSpotX" )
			return _hotSpotX.IsDerivedFromParent();
		if ( fieldName == "hotSpotY" )
			return _hotSpotY.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[UseTypeName("ACUR")]
public class UIAnimatedCursor : UICursorBase
{
	private UndoRedoDBPtr<UIAnimatedCursor> ___parent;
	[HideInOutliner]
	public new DBPtr<UIAnimatedCursor> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<int> _frameCount;
	private UndoRedo<int> _fps;
	private UndoRedo<float> _delay;
	private UndoRedo<int> _hotSpotX;
	private UndoRedo<int> _hotSpotY;

	[Description( "»м€ файла первого кадра секвенции, должно содержать на конце номер (обычно 01 или вроде того)." )]
	[SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[Description( "»м€ файла дл€ сымпортированного курсора, генерируетс€ автоматически." )]
	[DstFile("ani")]
	public string dstFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "ani"
	); } }
	[Description( " оличество кадров в секвенции, каждый кадр беретс€ из отдельного файла по пор€дку номеров." )]
	[IntMin(1)]
	public int frameCount { get { return _frameCount.Get(); } set { _frameCount.Set( value ); } }

	[Description( "ѕримерна€ скорость проигрывани€ анимации в кадрах в секунду, от 1 до 60." )]
	[IntMinMax(1, 60)]
	public int fps { get { return _fps.Get(); } set { _fps.Set( value ); } }

	[Description( "ѕримерна€ задержка (длительность первого кадра) перед зацикливанием последовательности." )]
	[FloatMin(0)]
	public float delay { get { return _delay.Get(); } set { _delay.Set( value ); } }

	[Description( "X-координата хотспота, ноль - слева." )]
	public int hotSpotX { get { return _hotSpotX.Get(); } set { _hotSpotX.Set( value ); } }

	[Description( "Y-координата хотспота, ноль - сверху." )]
	public int hotSpotY { get { return _hotSpotY.Get(); } set { _hotSpotY.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIAnimatedCursor>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_frameCount = new UndoRedo<int>( owner, 1 );
		_fps = new UndoRedo<int>( owner, 10 );
		_delay = new UndoRedo<float>( owner, 0.0f );
		_hotSpotX = new UndoRedo<int>( owner, 0 );
		_hotSpotY = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_frameCount.Changed += FireChangedEvent;
		_fps.Changed += FireChangedEvent;
		_delay.Changed += FireChangedEvent;
		_hotSpotX.Changed += FireChangedEvent;
		_hotSpotY.Changed += FireChangedEvent;
	}

	public UIAnimatedCursor()
	{
		Initialize( this );
	}
	private void AssignSelf( UIAnimatedCursor source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIAnimatedCursor" );
		srcFileName = source.srcFileName;
		frameCount = source.frameCount;
		fps = source.fps;
		delay = source.delay;
		hotSpotX = source.hotSpotX;
		hotSpotY = source.hotSpotY;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIAnimatedCursor source = _source as UIAnimatedCursor;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIAnimatedCursor" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIAnimatedCursor newParent = rawParent == null ? null : rawParent.Get<UIAnimatedCursor>();
		if ( newParent == null && _newParent is UIAnimatedCursor )
			newParent = _newParent as UIAnimatedCursor;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_frameCount.SetParent( newParent == null ? null : newParent._frameCount );
		_fps.SetParent( newParent == null ? null : newParent._fps );
		_delay.SetParent( newParent == null ? null : newParent._delay );
		_hotSpotX.SetParent( newParent == null ? null : newParent._hotSpotX );
		_hotSpotY.SetParent( newParent == null ? null : newParent._hotSpotY );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_frameCount.Reset();
		_fps.Reset();
		_delay.Reset();
		_hotSpotX.Reset();
		_hotSpotY.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _frameCount.IsDerivedFromParent()
			&& _fps.IsDerivedFromParent()
			&& _delay.IsDerivedFromParent()
			&& _hotSpotX.IsDerivedFromParent()
			&& _hotSpotY.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "frameCount" )
			_frameCount.Reset();
		else if ( fieldName == "fps" )
			_fps.Reset();
		else if ( fieldName == "delay" )
			_delay.Reset();
		else if ( fieldName == "hotSpotX" )
			_hotSpotX.Reset();
		else if ( fieldName == "hotSpotY" )
			_hotSpotY.Reset();
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
		if ( fieldName == "frameCount" )
			return _frameCount.IsDerivedFromParent();
		if ( fieldName == "fps" )
			return _fps.IsDerivedFromParent();
		if ( fieldName == "delay" )
			return _delay.IsDerivedFromParent();
		if ( fieldName == "hotSpotX" )
			return _hotSpotX.IsDerivedFromParent();
		if ( fieldName == "hotSpotY" )
			return _hotSpotY.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Edit Box", "Layout")]
[UseTypeName("EditBox")]
public class UIEditBoxLayout : UIImageLabelLayout
{
	private UndoRedoDBPtr<UIEditBoxLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIEditBoxLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _disabledMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _cursorMaterial;
	private UndoRedo<int> _maxLength;
	private UndoRedo<bool> _isPassword;
	private UndoRedo<int> _maxLines;
	private UndoRedo<EUITextEntryType> _textEntryType;

	[LuaProperty]
	public DBPtr<BaseUIMaterial> disabledMaterial { get { return _disabledMaterial.Get(); } set { _disabledMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> cursorMaterial { get { return _cursorMaterial.Get(); } set { _cursorMaterial.Set( value ); } }

	[Category( "Text" )]
	[LuaProperty]
	public int maxLength { get { return _maxLength.Get(); } set { _maxLength.Set( value ); } }

	[Category]
	[LuaProperty]
	public bool isPassword { get { return _isPassword.Get(); } set { _isPassword.Set( value ); } }

	[Category( "Text" )]
	[LuaProperty]
	public int maxLines { get { return _maxLines.Get(); } set { _maxLines.Set( value ); } }

	[Category( "Text" )]
	[LuaProperty]
	public EUITextEntryType textEntryType { get { return _textEntryType.Get(); } set { _textEntryType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIEditBoxLayout>(owner);
		_disabledMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_cursorMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_maxLength = new UndoRedo<int>( owner, 65535 );
		_isPassword = new UndoRedo<bool>( owner, false );
		_maxLines = new UndoRedo<int>( owner, 1 );
		_textEntryType = new UndoRedo<EUITextEntryType>( owner, EUITextEntryType.Free );
		___parent.Changed += FireChangedEvent;
		_disabledMaterial.Changed += FireChangedEvent;
		_cursorMaterial.Changed += FireChangedEvent;
		_maxLength.Changed += FireChangedEvent;
		_isPassword.Changed += FireChangedEvent;
		_maxLines.Changed += FireChangedEvent;
		_textEntryType.Changed += FireChangedEvent;
	}

	public UIEditBoxLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIEditBoxLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIEditBoxLayout" );
		disabledMaterial = source.disabledMaterial;
		cursorMaterial = source.cursorMaterial;
		maxLength = source.maxLength;
		isPassword = source.isPassword;
		maxLines = source.maxLines;
		textEntryType = source.textEntryType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIEditBoxLayout source = _source as UIEditBoxLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIEditBoxLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIEditBoxLayout newParent = rawParent == null ? null : rawParent.Get<UIEditBoxLayout>();
		if ( newParent == null && _newParent is UIEditBoxLayout )
			newParent = _newParent as UIEditBoxLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_disabledMaterial.SetParent( newParent == null ? null : newParent._disabledMaterial );
		_cursorMaterial.SetParent( newParent == null ? null : newParent._cursorMaterial );
		_maxLength.SetParent( newParent == null ? null : newParent._maxLength );
		_isPassword.SetParent( newParent == null ? null : newParent._isPassword );
		_maxLines.SetParent( newParent == null ? null : newParent._maxLines );
		_textEntryType.SetParent( newParent == null ? null : newParent._textEntryType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_disabledMaterial.Reset();
		_cursorMaterial.Reset();
		_maxLength.Reset();
		_isPassword.Reset();
		_maxLines.Reset();
		_textEntryType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_disabledMaterial.IsDerivedFromParent()
			&& _cursorMaterial.IsDerivedFromParent()
			&& _maxLength.IsDerivedFromParent()
			&& _isPassword.IsDerivedFromParent()
			&& _maxLines.IsDerivedFromParent()
			&& _textEntryType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "disabledMaterial" )
			_disabledMaterial.Reset();
		else if ( fieldName == "cursorMaterial" )
			_cursorMaterial.Reset();
		else if ( fieldName == "maxLength" )
			_maxLength.Reset();
		else if ( fieldName == "isPassword" )
			_isPassword.Reset();
		else if ( fieldName == "maxLines" )
			_maxLines.Reset();
		else if ( fieldName == "textEntryType" )
			_textEntryType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "disabledMaterial" )
			return _disabledMaterial.IsDerivedFromParent();
		if ( fieldName == "cursorMaterial" )
			return _cursorMaterial.IsDerivedFromParent();
		if ( fieldName == "maxLength" )
			return _maxLength.IsDerivedFromParent();
		if ( fieldName == "isPassword" )
			return _isPassword.IsDerivedFromParent();
		if ( fieldName == "maxLines" )
			return _maxLines.IsDerivedFromParent();
		if ( fieldName == "textEntryType" )
			return _textEntryType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Flash", "Layout")]
public class UIFlashLayout : UILayout
{
	private UndoRedoDBPtr<UIFlashLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIFlashLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _srcFileName;
	private UndoRedo<bool> _useScissorTest;
	private UndoRedo<bool> _useOwnSize;
	private UndoRedo<float> _triangulationError;
	private UndoRedoAssignableList<UIFlashProperties> _properties;

	[SwfFileRef("*.swf")]
	public string srcFileName { get { return _srcFileName.Get(); } set { _srcFileName.Set( value ); } }

	public bool useScissorTest { get { return _useScissorTest.Get(); } set { _useScissorTest.Set( value ); } }

	[Description( "Use size from SWF file" )]
	public bool useOwnSize { get { return _useOwnSize.Get(); } set { _useOwnSize.Set( value ); } }

	[Description( "Triangulation pixel error" )]
	public float triangulationError { get { return _triangulationError.Get(); } set { _triangulationError.Set( value ); } }

	[Description( "Public properties of flash control" )]
	[FixedList]
	public libdb.IChangeableList<UIFlashProperties> properties { get { return _properties; } set { _properties.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIFlashLayout>(owner);
		_srcFileName = new UndoRedo<string>( owner, string.Empty );
		_useScissorTest = new UndoRedo<bool>( owner, false );
		_useOwnSize = new UndoRedo<bool>( owner, false );
		_triangulationError = new UndoRedo<float>( owner, 1.0f );
		_properties = new UndoRedoAssignableList<UIFlashProperties>( owner );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_useScissorTest.Changed += FireChangedEvent;
		_useOwnSize.Changed += FireChangedEvent;
		_triangulationError.Changed += FireChangedEvent;
		_properties.Changed += FireChangedEvent;
	}

	public UIFlashLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIFlashLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIFlashLayout" );
		srcFileName = source.srcFileName;
		useScissorTest = source.useScissorTest;
		useOwnSize = source.useOwnSize;
		triangulationError = source.triangulationError;
		properties = source.properties;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIFlashLayout source = _source as UIFlashLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFlashLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIFlashLayout newParent = rawParent == null ? null : rawParent.Get<UIFlashLayout>();
		if ( newParent == null && _newParent is UIFlashLayout )
			newParent = _newParent as UIFlashLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_useScissorTest.SetParent( newParent == null ? null : newParent._useScissorTest );
		_useOwnSize.SetParent( newParent == null ? null : newParent._useOwnSize );
		_triangulationError.SetParent( newParent == null ? null : newParent._triangulationError );
		_properties.SetParent( newParent == null ? null : newParent._properties );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_useScissorTest.Reset();
		_useOwnSize.Reset();
		_triangulationError.Reset();
		_properties.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _useScissorTest.IsDerivedFromParent()
			&& _useOwnSize.IsDerivedFromParent()
			&& _triangulationError.IsDerivedFromParent()
			&& _properties.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "useScissorTest" )
			_useScissorTest.Reset();
		else if ( fieldName == "useOwnSize" )
			_useOwnSize.Reset();
		else if ( fieldName == "triangulationError" )
			_triangulationError.Reset();
		else if ( fieldName == "properties" )
			_properties.Reset();
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
		if ( fieldName == "useScissorTest" )
			return _useScissorTest.IsDerivedFromParent();
		if ( fieldName == "useOwnSize" )
			return _useOwnSize.IsDerivedFromParent();
		if ( fieldName == "triangulationError" )
			return _triangulationError.IsDerivedFromParent();
		if ( fieldName == "properties" )
			return _properties.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Flash2", "Layout")]
public class UIFlashLayout2 : UIFlashLayout
{
	private UndoRedoDBPtr<UIFlashLayout2> ___parent;
	[HideInOutliner]
	public new DBPtr<UIFlashLayout2> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIFlashLayout2>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UIFlashLayout2()
	{
		Initialize( this );
	}
	private void AssignSelf( UIFlashLayout2 source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIFlashLayout2" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIFlashLayout2 source = _source as UIFlashLayout2;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFlashLayout2" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIFlashLayout2 newParent = rawParent == null ? null : rawParent.Get<UIFlashLayout2>();
		if ( newParent == null && _newParent is UIFlashLayout2 )
			newParent = _newParent as UIFlashLayout2;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(1)]
[IndexField("styleName")]
[UseTypeName("IFNT")]
public class UIFontStyle : DBResource
{
	private UndoRedoDBPtr<UIFontStyle> ___parent;
	[HideInOutliner]
	public new DBPtr<UIFontStyle> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _styleName;
	private UndoRedo<bool> _drawContour;
	private HDRColor _primaryColor;
	private HDRColor _secondaryColor;
	private RenderState _renderState;
	private UndoRedo<string> _ttfFileName;
	private UndoRedo<string> _fontFamily;
	private UndoRedo<int> _fontSize;
	private UndoRedo<int> _lineGap;
	private UndoRedo<float> _additionalAdvance;
	private UndoRedo<float> _spaceScale;
	private UndoRedo<bool> _bold;
	private UndoRedo<bool> _italic;
	private UndoRedo<bool> _disableImageScaling;

	public string styleName { get { return _styleName.Get(); } set { _styleName.Set( value ); } }

	public bool drawContour { get { return _drawContour.Get(); } set { _drawContour.Set( value ); } }

	public HDRColor primaryColor { get { return _primaryColor; } set { _primaryColor.Assign( value ); } }

	public HDRColor secondaryColor { get { return _secondaryColor; } set { _secondaryColor.Assign( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[FileRef("*.ttf;*.pfb")]
	public string ttfFileName { get { return _ttfFileName.Get(); } set { _ttfFileName.Set( value ); } }

	[Category( "Text" )]
	public string fontFamily { get { return _fontFamily.Get(); } set { _fontFamily.Set( value ); } }

	public int fontSize { get { return _fontSize.Get(); } set { _fontSize.Set( value ); } }

	public int lineGap { get { return _lineGap.Get(); } set { _lineGap.Set( value ); } }

	[Description( "Additional horizontal advance between letters " )]
	public float additionalAdvance { get { return _additionalAdvance.Get(); } set { _additionalAdvance.Set( value ); } }

	[Description( "Relative size of white-space char; Used to tweak font render" )]
	public float spaceScale { get { return _spaceScale.Get(); } set { _spaceScale.Set( value ); } }

	public bool bold { get { return _bold.Get(); } set { _bold.Set( value ); } }

	public bool italic { get { return _italic.Get(); } set { _italic.Set( value ); } }

	[Custom("Social")]
	[NoCode]
	public bool disableImageScaling { get { return _disableImageScaling.Get(); } set { _disableImageScaling.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIFontStyle>(owner);
		_styleName = new UndoRedo<string>( owner, string.Empty );
		_drawContour = new UndoRedo<bool>( owner, false );
		HDRColor __primaryColor = new HDRColor(); // Construct default object for primaryColor
		__primaryColor.R = 1.0f;
		__primaryColor.G = 1.0f;
		__primaryColor.B = 1.0f;
		_primaryColor = new HDRColor( owner, __primaryColor );
		_secondaryColor = new HDRColor( owner );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		_ttfFileName = new UndoRedo<string>( owner, string.Empty );
		_fontFamily = new UndoRedo<string>( owner, string.Empty );
		_fontSize = new UndoRedo<int>( owner, 0 );
		_lineGap = new UndoRedo<int>( owner, 0 );
		_additionalAdvance = new UndoRedo<float>( owner, 0.0f );
		_spaceScale = new UndoRedo<float>( owner, 1.0f );
		_bold = new UndoRedo<bool>( owner, false );
		_italic = new UndoRedo<bool>( owner, false );
		_disableImageScaling = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_styleName.Changed += FireChangedEvent;
		_drawContour.Changed += FireChangedEvent;
		_primaryColor.Changed += FireChangedEvent;
		_secondaryColor.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_ttfFileName.Changed += FireChangedEvent;
		_fontFamily.Changed += FireChangedEvent;
		_fontSize.Changed += FireChangedEvent;
		_lineGap.Changed += FireChangedEvent;
		_additionalAdvance.Changed += FireChangedEvent;
		_spaceScale.Changed += FireChangedEvent;
		_bold.Changed += FireChangedEvent;
		_italic.Changed += FireChangedEvent;
		_disableImageScaling.Changed += FireChangedEvent;
	}

	public UIFontStyle()
	{
		Initialize( this );
	}
	private void AssignSelf( UIFontStyle source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIFontStyle" );
		styleName = source.styleName;
		drawContour = source.drawContour;
		primaryColor = source.primaryColor;
		secondaryColor = source.secondaryColor;
		renderState = source.renderState;
		ttfFileName = source.ttfFileName;
		fontFamily = source.fontFamily;
		fontSize = source.fontSize;
		lineGap = source.lineGap;
		additionalAdvance = source.additionalAdvance;
		spaceScale = source.spaceScale;
		bold = source.bold;
		italic = source.italic;
		disableImageScaling = source.disableImageScaling;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIFontStyle source = _source as UIFontStyle;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFontStyle" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIFontStyle newParent = rawParent == null ? null : rawParent.Get<UIFontStyle>();
		if ( newParent == null && _newParent is UIFontStyle )
			newParent = _newParent as UIFontStyle;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_styleName.SetParent( newParent == null ? null : newParent._styleName );
		_drawContour.SetParent( newParent == null ? null : newParent._drawContour );
		_primaryColor.SetParent( newParent == null ? null : newParent._primaryColor );
		_secondaryColor.SetParent( newParent == null ? null : newParent._secondaryColor );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_ttfFileName.SetParent( newParent == null ? null : newParent._ttfFileName );
		_fontFamily.SetParent( newParent == null ? null : newParent._fontFamily );
		_fontSize.SetParent( newParent == null ? null : newParent._fontSize );
		_lineGap.SetParent( newParent == null ? null : newParent._lineGap );
		_additionalAdvance.SetParent( newParent == null ? null : newParent._additionalAdvance );
		_spaceScale.SetParent( newParent == null ? null : newParent._spaceScale );
		_bold.SetParent( newParent == null ? null : newParent._bold );
		_italic.SetParent( newParent == null ? null : newParent._italic );
		_disableImageScaling.SetParent( newParent == null ? null : newParent._disableImageScaling );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_styleName.Reset();
		_drawContour.Reset();
		_primaryColor.Reset();
		_secondaryColor.Reset();
		_renderState.Reset();
		_ttfFileName.Reset();
		_fontFamily.Reset();
		_fontSize.Reset();
		_lineGap.Reset();
		_additionalAdvance.Reset();
		_spaceScale.Reset();
		_bold.Reset();
		_italic.Reset();
		_disableImageScaling.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_styleName.IsDerivedFromParent()
			&& _drawContour.IsDerivedFromParent()
			&& _primaryColor.IsDerivedFromParent()
			&& _secondaryColor.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& _ttfFileName.IsDerivedFromParent()
			&& _fontFamily.IsDerivedFromParent()
			&& _fontSize.IsDerivedFromParent()
			&& _lineGap.IsDerivedFromParent()
			&& _additionalAdvance.IsDerivedFromParent()
			&& _spaceScale.IsDerivedFromParent()
			&& _bold.IsDerivedFromParent()
			&& _italic.IsDerivedFromParent()
			&& _disableImageScaling.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "styleName" )
			_styleName.Reset();
		else if ( fieldName == "drawContour" )
			_drawContour.Reset();
		else if ( fieldName == "primaryColor" )
			_primaryColor.Reset();
		else if ( fieldName == "secondaryColor" )
			_secondaryColor.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "ttfFileName" )
			_ttfFileName.Reset();
		else if ( fieldName == "fontFamily" )
			_fontFamily.Reset();
		else if ( fieldName == "fontSize" )
			_fontSize.Reset();
		else if ( fieldName == "lineGap" )
			_lineGap.Reset();
		else if ( fieldName == "additionalAdvance" )
			_additionalAdvance.Reset();
		else if ( fieldName == "spaceScale" )
			_spaceScale.Reset();
		else if ( fieldName == "bold" )
			_bold.Reset();
		else if ( fieldName == "italic" )
			_italic.Reset();
		else if ( fieldName == "disableImageScaling" )
			_disableImageScaling.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "styleName" )
			return _styleName.IsDerivedFromParent();
		if ( fieldName == "drawContour" )
			return _drawContour.IsDerivedFromParent();
		if ( fieldName == "primaryColor" )
			return _primaryColor.IsDerivedFromParent();
		if ( fieldName == "secondaryColor" )
			return _secondaryColor.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "ttfFileName" )
			return _ttfFileName.IsDerivedFromParent();
		if ( fieldName == "fontFamily" )
			return _fontFamily.IsDerivedFromParent();
		if ( fieldName == "fontSize" )
			return _fontSize.IsDerivedFromParent();
		if ( fieldName == "lineGap" )
			return _lineGap.IsDerivedFromParent();
		if ( fieldName == "additionalAdvance" )
			return _additionalAdvance.IsDerivedFromParent();
		if ( fieldName == "spaceScale" )
			return _spaceScale.IsDerivedFromParent();
		if ( fieldName == "bold" )
			return _bold.IsDerivedFromParent();
		if ( fieldName == "italic" )
			return _italic.IsDerivedFromParent();
		if ( fieldName == "disableImageScaling" )
			return _disableImageScaling.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Indicators", "Health Bar", "View")]
[UseTypeName("HealthBar")]
public class UIHealthBarLayout : UIImageLabelLayout
{
	private UndoRedoDBPtr<UIHealthBarLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIHealthBarLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _healthMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _shieldMaterial;
	private UndoRedo<bool> _showShield;
	private UndoRedo<bool> _showStripes;

	public DBPtr<BaseUIMaterial> healthMaterial { get { return _healthMaterial.Get(); } set { _healthMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> shieldMaterial { get { return _shieldMaterial.Get(); } set { _shieldMaterial.Set( value ); } }

	public bool showShield { get { return _showShield.Get(); } set { _showShield.Set( value ); } }

	public bool showStripes { get { return _showStripes.Get(); } set { _showStripes.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIHealthBarLayout>(owner);
		_healthMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_shieldMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_showShield = new UndoRedo<bool>( owner, false );
		_showStripes = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_healthMaterial.Changed += FireChangedEvent;
		_shieldMaterial.Changed += FireChangedEvent;
		_showShield.Changed += FireChangedEvent;
		_showStripes.Changed += FireChangedEvent;
	}

	public UIHealthBarLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIHealthBarLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIHealthBarLayout" );
		healthMaterial = source.healthMaterial;
		shieldMaterial = source.shieldMaterial;
		showShield = source.showShield;
		showStripes = source.showStripes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIHealthBarLayout source = _source as UIHealthBarLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIHealthBarLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIHealthBarLayout newParent = rawParent == null ? null : rawParent.Get<UIHealthBarLayout>();
		if ( newParent == null && _newParent is UIHealthBarLayout )
			newParent = _newParent as UIHealthBarLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_healthMaterial.SetParent( newParent == null ? null : newParent._healthMaterial );
		_shieldMaterial.SetParent( newParent == null ? null : newParent._shieldMaterial );
		_showShield.SetParent( newParent == null ? null : newParent._showShield );
		_showStripes.SetParent( newParent == null ? null : newParent._showStripes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_healthMaterial.Reset();
		_shieldMaterial.Reset();
		_showShield.Reset();
		_showStripes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_healthMaterial.IsDerivedFromParent()
			&& _shieldMaterial.IsDerivedFromParent()
			&& _showShield.IsDerivedFromParent()
			&& _showStripes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "healthMaterial" )
			_healthMaterial.Reset();
		else if ( fieldName == "shieldMaterial" )
			_shieldMaterial.Reset();
		else if ( fieldName == "showShield" )
			_showShield.Reset();
		else if ( fieldName == "showStripes" )
			_showStripes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "healthMaterial" )
			return _healthMaterial.IsDerivedFromParent();
		if ( fieldName == "shieldMaterial" )
			return _shieldMaterial.IsDerivedFromParent();
		if ( fieldName == "showShield" )
			return _showShield.IsDerivedFromParent();
		if ( fieldName == "showStripes" )
			return _showStripes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Check Box", "Button")]
[UseTypeName("CheckBox")]
public class UICheckBoxLayout : UICommonControl
{
	private UndoRedoDBPtr<UICheckBoxLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UICheckBoxLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _highlightMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _checkedMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _highlightCheckedMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _disabledMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _disabledCheckedMaterial;

	[LuaProperty]
	public DBPtr<BaseUIMaterial> highlightMaterial { get { return _highlightMaterial.Get(); } set { _highlightMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> checkedMaterial { get { return _checkedMaterial.Get(); } set { _checkedMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> highlightCheckedMaterial { get { return _highlightCheckedMaterial.Get(); } set { _highlightCheckedMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> disabledMaterial { get { return _disabledMaterial.Get(); } set { _disabledMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> disabledCheckedMaterial { get { return _disabledCheckedMaterial.Get(); } set { _disabledCheckedMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UICheckBoxLayout>(owner);
		_highlightMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_checkedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_highlightCheckedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_disabledMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_disabledCheckedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		___parent.Changed += FireChangedEvent;
		_highlightMaterial.Changed += FireChangedEvent;
		_checkedMaterial.Changed += FireChangedEvent;
		_highlightCheckedMaterial.Changed += FireChangedEvent;
		_disabledMaterial.Changed += FireChangedEvent;
		_disabledCheckedMaterial.Changed += FireChangedEvent;
	}

	public UICheckBoxLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UICheckBoxLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UICheckBoxLayout" );
		highlightMaterial = source.highlightMaterial;
		checkedMaterial = source.checkedMaterial;
		highlightCheckedMaterial = source.highlightCheckedMaterial;
		disabledMaterial = source.disabledMaterial;
		disabledCheckedMaterial = source.disabledCheckedMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UICheckBoxLayout source = _source as UICheckBoxLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UICheckBoxLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UICheckBoxLayout newParent = rawParent == null ? null : rawParent.Get<UICheckBoxLayout>();
		if ( newParent == null && _newParent is UICheckBoxLayout )
			newParent = _newParent as UICheckBoxLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_highlightMaterial.SetParent( newParent == null ? null : newParent._highlightMaterial );
		_checkedMaterial.SetParent( newParent == null ? null : newParent._checkedMaterial );
		_highlightCheckedMaterial.SetParent( newParent == null ? null : newParent._highlightCheckedMaterial );
		_disabledMaterial.SetParent( newParent == null ? null : newParent._disabledMaterial );
		_disabledCheckedMaterial.SetParent( newParent == null ? null : newParent._disabledCheckedMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_highlightMaterial.Reset();
		_checkedMaterial.Reset();
		_highlightCheckedMaterial.Reset();
		_disabledMaterial.Reset();
		_disabledCheckedMaterial.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_highlightMaterial.IsDerivedFromParent()
			&& _checkedMaterial.IsDerivedFromParent()
			&& _highlightCheckedMaterial.IsDerivedFromParent()
			&& _disabledMaterial.IsDerivedFromParent()
			&& _disabledCheckedMaterial.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "highlightMaterial" )
			_highlightMaterial.Reset();
		else if ( fieldName == "checkedMaterial" )
			_checkedMaterial.Reset();
		else if ( fieldName == "highlightCheckedMaterial" )
			_highlightCheckedMaterial.Reset();
		else if ( fieldName == "disabledMaterial" )
			_disabledMaterial.Reset();
		else if ( fieldName == "disabledCheckedMaterial" )
			_disabledCheckedMaterial.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "highlightMaterial" )
			return _highlightMaterial.IsDerivedFromParent();
		if ( fieldName == "checkedMaterial" )
			return _checkedMaterial.IsDerivedFromParent();
		if ( fieldName == "highlightCheckedMaterial" )
			return _highlightCheckedMaterial.IsDerivedFromParent();
		if ( fieldName == "disabledMaterial" )
			return _disabledMaterial.IsDerivedFromParent();
		if ( fieldName == "disabledCheckedMaterial" )
			return _disabledCheckedMaterial.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("General", "Base", "Layout")]
public class UIBaseLayout : UILayout
{
	private UndoRedoDBPtr<UIBaseLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIBaseLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIBaseLayout>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UIBaseLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIBaseLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIBaseLayout" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIBaseLayout source = _source as UIBaseLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIBaseLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIBaseLayout newParent = rawParent == null ? null : rawParent.Get<UIBaseLayout>();
		if ( newParent == null && _newParent is UIBaseLayout )
			newParent = _newParent as UIBaseLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class UIObjectOvertips : DBResource
{
	private UndoRedoDBPtr<UIObjectOvertips> ___parent;
	[HideInOutliner]
	public new DBPtr<UIObjectOvertips> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UIPlainOvertipDesc> _plain;
	private UndoRedoAssignableList<UI3DOvertipDesc> _threeDimensional;

	public libdb.IChangeableList<UIPlainOvertipDesc> plain { get { return _plain; } set { _plain.Assign( value ); } }

	public libdb.IChangeableList<UI3DOvertipDesc> threeDimensional { get { return _threeDimensional; } set { _threeDimensional.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIObjectOvertips>(owner);
		_plain = new UndoRedoAssignableList<UIPlainOvertipDesc>( owner );
		_threeDimensional = new UndoRedoAssignableList<UI3DOvertipDesc>( owner );
		___parent.Changed += FireChangedEvent;
		_plain.Changed += FireChangedEvent;
		_threeDimensional.Changed += FireChangedEvent;
	}

	public UIObjectOvertips()
	{
		Initialize( this );
	}
	private void AssignSelf( UIObjectOvertips source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIObjectOvertips" );
		plain = source.plain;
		threeDimensional = source.threeDimensional;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIObjectOvertips source = _source as UIObjectOvertips;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIObjectOvertips" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIObjectOvertips newParent = rawParent == null ? null : rawParent.Get<UIObjectOvertips>();
		if ( newParent == null && _newParent is UIObjectOvertips )
			newParent = _newParent as UIObjectOvertips;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_plain.SetParent( newParent == null ? null : newParent._plain );
		_threeDimensional.SetParent( newParent == null ? null : newParent._threeDimensional );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_plain.Reset();
		_threeDimensional.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_plain.IsDerivedFromParent()
			&& _threeDimensional.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "plain" )
			_plain.Reset();
		else if ( fieldName == "threeDimensional" )
			_threeDimensional.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "plain" )
			return _plain.IsDerivedFromParent();
		if ( fieldName == "threeDimensional" )
			return _threeDimensional.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Containers", "PageTabControl", "Layout")]
public class UIPageTabControlLayout : UIImageLabelLayout
{
	private UndoRedoDBPtr<UIPageTabControlLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIPageTabControlLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UIPageTabElement> _tabs;

	[Category]
	public libdb.IChangeableList<UIPageTabElement> tabs { get { return _tabs; } set { _tabs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIPageTabControlLayout>(owner);
		_tabs = new UndoRedoAssignableList<UIPageTabElement>( owner );
		___parent.Changed += FireChangedEvent;
		_tabs.Changed += FireChangedEvent;
	}

	public UIPageTabControlLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIPageTabControlLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIPageTabControlLayout" );
		tabs = source.tabs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIPageTabControlLayout source = _source as UIPageTabControlLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIPageTabControlLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIPageTabControlLayout newParent = rawParent == null ? null : rawParent.Get<UIPageTabControlLayout>();
		if ( newParent == null && _newParent is UIPageTabControlLayout )
			newParent = _newParent as UIPageTabControlLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tabs.SetParent( newParent == null ? null : newParent._tabs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tabs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tabs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tabs" )
			_tabs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tabs" )
			return _tabs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Indicators", "Progress Bar", "View")]
[UseTypeName("Progress")]
public class UIProgressBarLayout : UIImageLabelLayout
{
	private UndoRedoDBPtr<UIProgressBarLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIProgressBarLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _progressMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _rotationEffectMaterial;
	private FloatPoint _rotationEffectPivot;
	private UndoRedo<EUIRotationType> _effectRotationType;
	private UndoRedo<EUIProgressBarType> _progressBarType;
	private UndoRedo<int> _maskGradientItems;

	public DBPtr<BaseUIMaterial> progressMaterial { get { return _progressMaterial.Get(); } set { _progressMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> rotationEffectMaterial { get { return _rotationEffectMaterial.Get(); } set { _rotationEffectMaterial.Set( value ); } }

	[Category( "Image" )]
	public FloatPoint rotationEffectPivot { get { return _rotationEffectPivot; } set { _rotationEffectPivot.Assign( value ); } }

	[Category( "Image" )]
	public EUIRotationType effectRotationType { get { return _effectRotationType.Get(); } set { _effectRotationType.Set( value ); } }

	[Category( "Image" )]
	public EUIProgressBarType progressBarType { get { return _progressBarType.Get(); } set { _progressBarType.Set( value ); } }

	[Category( "Image" )]
	public int maskGradientItems { get { return _maskGradientItems.Get(); } set { _maskGradientItems.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIProgressBarLayout>(owner);
		_progressMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_rotationEffectMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		FloatPoint __rotationEffectPivot = new FloatPoint(); // Construct default object for rotationEffectPivot
		__rotationEffectPivot.x = -1;
		__rotationEffectPivot.y = -1;
		_rotationEffectPivot = new FloatPoint( owner, __rotationEffectPivot );
		_effectRotationType = new UndoRedo<EUIRotationType>( owner, EUIRotationType.CW );
		_progressBarType = new UndoRedo<EUIProgressBarType>( owner, EUIProgressBarType.HorizontalScalingBar );
		_maskGradientItems = new UndoRedo<int>( owner, 1 );
		___parent.Changed += FireChangedEvent;
		_progressMaterial.Changed += FireChangedEvent;
		_rotationEffectMaterial.Changed += FireChangedEvent;
		_rotationEffectPivot.Changed += FireChangedEvent;
		_effectRotationType.Changed += FireChangedEvent;
		_progressBarType.Changed += FireChangedEvent;
		_maskGradientItems.Changed += FireChangedEvent;
	}

	public UIProgressBarLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIProgressBarLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIProgressBarLayout" );
		progressMaterial = source.progressMaterial;
		rotationEffectMaterial = source.rotationEffectMaterial;
		rotationEffectPivot = source.rotationEffectPivot;
		effectRotationType = source.effectRotationType;
		progressBarType = source.progressBarType;
		maskGradientItems = source.maskGradientItems;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIProgressBarLayout source = _source as UIProgressBarLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIProgressBarLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIProgressBarLayout newParent = rawParent == null ? null : rawParent.Get<UIProgressBarLayout>();
		if ( newParent == null && _newParent is UIProgressBarLayout )
			newParent = _newParent as UIProgressBarLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_progressMaterial.SetParent( newParent == null ? null : newParent._progressMaterial );
		_rotationEffectMaterial.SetParent( newParent == null ? null : newParent._rotationEffectMaterial );
		_rotationEffectPivot.SetParent( newParent == null ? null : newParent._rotationEffectPivot );
		_effectRotationType.SetParent( newParent == null ? null : newParent._effectRotationType );
		_progressBarType.SetParent( newParent == null ? null : newParent._progressBarType );
		_maskGradientItems.SetParent( newParent == null ? null : newParent._maskGradientItems );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_progressMaterial.Reset();
		_rotationEffectMaterial.Reset();
		_rotationEffectPivot.Reset();
		_effectRotationType.Reset();
		_progressBarType.Reset();
		_maskGradientItems.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_progressMaterial.IsDerivedFromParent()
			&& _rotationEffectMaterial.IsDerivedFromParent()
			&& _rotationEffectPivot.IsDerivedFromParent()
			&& _effectRotationType.IsDerivedFromParent()
			&& _progressBarType.IsDerivedFromParent()
			&& _maskGradientItems.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "progressMaterial" )
			_progressMaterial.Reset();
		else if ( fieldName == "rotationEffectMaterial" )
			_rotationEffectMaterial.Reset();
		else if ( fieldName == "rotationEffectPivot" )
			_rotationEffectPivot.Reset();
		else if ( fieldName == "effectRotationType" )
			_effectRotationType.Reset();
		else if ( fieldName == "progressBarType" )
			_progressBarType.Reset();
		else if ( fieldName == "maskGradientItems" )
			_maskGradientItems.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "progressMaterial" )
			return _progressMaterial.IsDerivedFromParent();
		if ( fieldName == "rotationEffectMaterial" )
			return _rotationEffectMaterial.IsDerivedFromParent();
		if ( fieldName == "rotationEffectPivot" )
			return _rotationEffectPivot.IsDerivedFromParent();
		if ( fieldName == "effectRotationType" )
			return _effectRotationType.IsDerivedFromParent();
		if ( fieldName == "progressBarType" )
			return _progressBarType.IsDerivedFromParent();
		if ( fieldName == "maskGradientItems" )
			return _maskGradientItems.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Radio Button", "Button")]
public class UIRadioButtonLayout : UICommonControl
{
	private UndoRedoDBPtr<UIRadioButtonLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIRadioButtonLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseUIMaterial> _highlightMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _selectedMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _disabledMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _disabledSelectedMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _flashedMaterial;
	private UndoRedo<int> _group;

	[LuaProperty]
	public DBPtr<BaseUIMaterial> highlightMaterial { get { return _highlightMaterial.Get(); } set { _highlightMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> selectedMaterial { get { return _selectedMaterial.Get(); } set { _selectedMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> disabledMaterial { get { return _disabledMaterial.Get(); } set { _disabledMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> disabledSelectedMaterial { get { return _disabledSelectedMaterial.Get(); } set { _disabledSelectedMaterial.Set( value ); } }

	[LuaProperty]
	public DBPtr<BaseUIMaterial> flashedMaterial { get { return _flashedMaterial.Get(); } set { _flashedMaterial.Set( value ); } }

	[LuaProperty]
	public int group { get { return _group.Get(); } set { _group.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIRadioButtonLayout>(owner);
		_highlightMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_selectedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_disabledMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_disabledSelectedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_flashedMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_group = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_highlightMaterial.Changed += FireChangedEvent;
		_selectedMaterial.Changed += FireChangedEvent;
		_disabledMaterial.Changed += FireChangedEvent;
		_disabledSelectedMaterial.Changed += FireChangedEvent;
		_flashedMaterial.Changed += FireChangedEvent;
		_group.Changed += FireChangedEvent;
	}

	public UIRadioButtonLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIRadioButtonLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIRadioButtonLayout" );
		highlightMaterial = source.highlightMaterial;
		selectedMaterial = source.selectedMaterial;
		disabledMaterial = source.disabledMaterial;
		disabledSelectedMaterial = source.disabledSelectedMaterial;
		flashedMaterial = source.flashedMaterial;
		group = source.group;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIRadioButtonLayout source = _source as UIRadioButtonLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIRadioButtonLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIRadioButtonLayout newParent = rawParent == null ? null : rawParent.Get<UIRadioButtonLayout>();
		if ( newParent == null && _newParent is UIRadioButtonLayout )
			newParent = _newParent as UIRadioButtonLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_highlightMaterial.SetParent( newParent == null ? null : newParent._highlightMaterial );
		_selectedMaterial.SetParent( newParent == null ? null : newParent._selectedMaterial );
		_disabledMaterial.SetParent( newParent == null ? null : newParent._disabledMaterial );
		_disabledSelectedMaterial.SetParent( newParent == null ? null : newParent._disabledSelectedMaterial );
		_flashedMaterial.SetParent( newParent == null ? null : newParent._flashedMaterial );
		_group.SetParent( newParent == null ? null : newParent._group );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_highlightMaterial.Reset();
		_selectedMaterial.Reset();
		_disabledMaterial.Reset();
		_disabledSelectedMaterial.Reset();
		_flashedMaterial.Reset();
		_group.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_highlightMaterial.IsDerivedFromParent()
			&& _selectedMaterial.IsDerivedFromParent()
			&& _disabledMaterial.IsDerivedFromParent()
			&& _disabledSelectedMaterial.IsDerivedFromParent()
			&& _flashedMaterial.IsDerivedFromParent()
			&& _group.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "highlightMaterial" )
			_highlightMaterial.Reset();
		else if ( fieldName == "selectedMaterial" )
			_selectedMaterial.Reset();
		else if ( fieldName == "disabledMaterial" )
			_disabledMaterial.Reset();
		else if ( fieldName == "disabledSelectedMaterial" )
			_disabledSelectedMaterial.Reset();
		else if ( fieldName == "flashedMaterial" )
			_flashedMaterial.Reset();
		else if ( fieldName == "group" )
			_group.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "highlightMaterial" )
			return _highlightMaterial.IsDerivedFromParent();
		if ( fieldName == "selectedMaterial" )
			return _selectedMaterial.IsDerivedFromParent();
		if ( fieldName == "disabledMaterial" )
			return _disabledMaterial.IsDerivedFromParent();
		if ( fieldName == "disabledSelectedMaterial" )
			return _disabledSelectedMaterial.IsDerivedFromParent();
		if ( fieldName == "flashedMaterial" )
			return _flashedMaterial.IsDerivedFromParent();
		if ( fieldName == "group" )
			return _group.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Containers", "Radio Panel", "Layout")]
public class UIRadioPanelLayout : UIImageLabelLayout
{
	private UndoRedoDBPtr<UIRadioPanelLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIRadioPanelLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIRadioPanelLayout>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UIRadioPanelLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIRadioPanelLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIRadioPanelLayout" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIRadioPanelLayout source = _source as UIRadioPanelLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIRadioPanelLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIRadioPanelLayout newParent = rawParent == null ? null : rawParent.Get<UIRadioPanelLayout>();
		if ( newParent == null && _newParent is UIRadioPanelLayout )
			newParent = _newParent as UIRadioPanelLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
public class UIRoot : DBResource
{
	private UndoRedoDBPtr<UIRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<UIRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UIScreenDesc> _screens;
	private UndoRedoAssignableList<UICursorDesc> _cursors;
	private UndoRedoAssignableList<UIScriptDesc> _scripts;
	private UndoRedoAssignableList<UIContentGroup> _contents;
	private UndoRedoAssignableList<UIConstant> _consts;
	private UndoRedoAssignableList<UITextSubstitute> _substitutes;
	private UndoRedoAssignableList<UIStyleAlias> _styleAliases;
	private UndoRedoAssignableList<DBPtr<UIFontStyle>> _fontStyles;
	private UndoRedoDBPtr<Preferences> _preferences;
	private UndoRedoDBPtr<VotingForSurrender> _votingForSurrender;
	private UIHealthStripes _healthStripes;

	public libdb.IChangeableList<UIScreenDesc> screens { get { return _screens; } set { _screens.Assign( value ); } }

	public libdb.IChangeableList<UICursorDesc> cursors { get { return _cursors; } set { _cursors.Assign( value ); } }

	public libdb.IChangeableList<UIScriptDesc> scripts { get { return _scripts; } set { _scripts.Assign( value ); } }

	public libdb.IChangeableList<UIContentGroup> contents { get { return _contents; } set { _contents.Assign( value ); } }

	public libdb.IChangeableList<UIConstant> consts { get { return _consts; } set { _consts.Assign( value ); } }

	[Custom("Social")]
	public libdb.IChangeableList<UITextSubstitute> substitutes { get { return _substitutes; } set { _substitutes.Assign( value ); } }

	[Custom("Social")]
	public libdb.IChangeableList<UIStyleAlias> styleAliases { get { return _styleAliases; } set { _styleAliases.Assign( value ); } }

	[Custom("Social")]
	public libdb.IChangeableList<DBPtr<UIFontStyle>> fontStyles { get { return _fontStyles; } set { _fontStyles.Assign( value ); } }

	public DBPtr<Preferences> preferences { get { return _preferences.Get(); } set { _preferences.Set( value ); } }

	public DBPtr<VotingForSurrender> votingForSurrender { get { return _votingForSurrender.Get(); } set { _votingForSurrender.Set( value ); } }

	public UIHealthStripes healthStripes { get { return _healthStripes; } set { _healthStripes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIRoot>(owner);
		_screens = new UndoRedoAssignableList<UIScreenDesc>( owner );
		_cursors = new UndoRedoAssignableList<UICursorDesc>( owner );
		_scripts = new UndoRedoAssignableList<UIScriptDesc>( owner );
		_contents = new UndoRedoAssignableList<UIContentGroup>( owner );
		_consts = new UndoRedoAssignableList<UIConstant>( owner );
		_substitutes = new UndoRedoAssignableList<UITextSubstitute>( owner );
		_styleAliases = new UndoRedoAssignableList<UIStyleAlias>( owner );
		_fontStyles = new UndoRedoAssignableList<DBPtr<UIFontStyle>>( owner );
		_preferences = new UndoRedoDBPtr<Preferences>( owner );
		_votingForSurrender = new UndoRedoDBPtr<VotingForSurrender>( owner );
		_healthStripes = new UIHealthStripes( owner );
		___parent.Changed += FireChangedEvent;
		_screens.Changed += FireChangedEvent;
		_cursors.Changed += FireChangedEvent;
		_scripts.Changed += FireChangedEvent;
		_contents.Changed += FireChangedEvent;
		_consts.Changed += FireChangedEvent;
		_substitutes.Changed += FireChangedEvent;
		_styleAliases.Changed += FireChangedEvent;
		_fontStyles.Changed += FireChangedEvent;
		_preferences.Changed += FireChangedEvent;
		_votingForSurrender.Changed += FireChangedEvent;
		_healthStripes.Changed += FireChangedEvent;
	}

	public UIRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( UIRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIRoot" );
		screens = source.screens;
		cursors = source.cursors;
		scripts = source.scripts;
		contents = source.contents;
		consts = source.consts;
		substitutes = source.substitutes;
		styleAliases = source.styleAliases;
		fontStyles = source.fontStyles;
		preferences = source.preferences;
		votingForSurrender = source.votingForSurrender;
		healthStripes = source.healthStripes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIRoot source = _source as UIRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIRoot newParent = rawParent == null ? null : rawParent.Get<UIRoot>();
		if ( newParent == null && _newParent is UIRoot )
			newParent = _newParent as UIRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_screens.SetParent( newParent == null ? null : newParent._screens );
		_cursors.SetParent( newParent == null ? null : newParent._cursors );
		_scripts.SetParent( newParent == null ? null : newParent._scripts );
		_contents.SetParent( newParent == null ? null : newParent._contents );
		_consts.SetParent( newParent == null ? null : newParent._consts );
		_substitutes.SetParent( newParent == null ? null : newParent._substitutes );
		_styleAliases.SetParent( newParent == null ? null : newParent._styleAliases );
		_fontStyles.SetParent( newParent == null ? null : newParent._fontStyles );
		_preferences.SetParent( newParent == null ? null : newParent._preferences );
		_votingForSurrender.SetParent( newParent == null ? null : newParent._votingForSurrender );
		_healthStripes.SetParent( newParent == null ? null : newParent._healthStripes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_screens.Reset();
		_cursors.Reset();
		_scripts.Reset();
		_contents.Reset();
		_consts.Reset();
		_substitutes.Reset();
		_styleAliases.Reset();
		_fontStyles.Reset();
		_preferences.Reset();
		_votingForSurrender.Reset();
		_healthStripes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_screens.IsDerivedFromParent()
			&& _cursors.IsDerivedFromParent()
			&& _scripts.IsDerivedFromParent()
			&& _contents.IsDerivedFromParent()
			&& _consts.IsDerivedFromParent()
			&& _substitutes.IsDerivedFromParent()
			&& _styleAliases.IsDerivedFromParent()
			&& _fontStyles.IsDerivedFromParent()
			&& _preferences.IsDerivedFromParent()
			&& _votingForSurrender.IsDerivedFromParent()
			&& _healthStripes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "screens" )
			_screens.Reset();
		else if ( fieldName == "cursors" )
			_cursors.Reset();
		else if ( fieldName == "scripts" )
			_scripts.Reset();
		else if ( fieldName == "contents" )
			_contents.Reset();
		else if ( fieldName == "consts" )
			_consts.Reset();
		else if ( fieldName == "substitutes" )
			_substitutes.Reset();
		else if ( fieldName == "styleAliases" )
			_styleAliases.Reset();
		else if ( fieldName == "fontStyles" )
			_fontStyles.Reset();
		else if ( fieldName == "preferences" )
			_preferences.Reset();
		else if ( fieldName == "votingForSurrender" )
			_votingForSurrender.Reset();
		else if ( fieldName == "healthStripes" )
			_healthStripes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "screens" )
			return _screens.IsDerivedFromParent();
		if ( fieldName == "cursors" )
			return _cursors.IsDerivedFromParent();
		if ( fieldName == "scripts" )
			return _scripts.IsDerivedFromParent();
		if ( fieldName == "contents" )
			return _contents.IsDerivedFromParent();
		if ( fieldName == "consts" )
			return _consts.IsDerivedFromParent();
		if ( fieldName == "substitutes" )
			return _substitutes.IsDerivedFromParent();
		if ( fieldName == "styleAliases" )
			return _styleAliases.IsDerivedFromParent();
		if ( fieldName == "fontStyles" )
			return _fontStyles.IsDerivedFromParent();
		if ( fieldName == "preferences" )
			return _preferences.IsDerivedFromParent();
		if ( fieldName == "votingForSurrender" )
			return _votingForSurrender.IsDerivedFromParent();
		if ( fieldName == "healthStripes" )
			return _healthStripes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Scroll Window", "Layout")]
public class UIScrollableWindowLayout : UILayout
{
	private UndoRedoDBPtr<UIScrollableWindowLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIScrollableWindowLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<UIScrollAreaLayout> _scrollArea;
	private UndoRedoDBPtr<UIScrollBarLayout> _scrollBar;

	[Category]
	public DBPtr<UIScrollAreaLayout> scrollArea { get { return _scrollArea.Get(); } set { _scrollArea.Set( value ); } }

	[Category]
	public DBPtr<UIScrollBarLayout> scrollBar { get { return _scrollBar.Get(); } set { _scrollBar.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIScrollableWindowLayout>(owner);
		_scrollArea = new UndoRedoDBPtr<UIScrollAreaLayout>( owner );
		_scrollBar = new UndoRedoDBPtr<UIScrollBarLayout>( owner );
		___parent.Changed += FireChangedEvent;
		_scrollArea.Changed += FireChangedEvent;
		_scrollBar.Changed += FireChangedEvent;
	}

	public UIScrollableWindowLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIScrollableWindowLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIScrollableWindowLayout" );
		scrollArea = source.scrollArea;
		scrollBar = source.scrollBar;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIScrollableWindowLayout source = _source as UIScrollableWindowLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScrollableWindowLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIScrollableWindowLayout newParent = rawParent == null ? null : rawParent.Get<UIScrollableWindowLayout>();
		if ( newParent == null && _newParent is UIScrollableWindowLayout )
			newParent = _newParent as UIScrollableWindowLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_scrollArea.SetParent( newParent == null ? null : newParent._scrollArea );
		_scrollBar.SetParent( newParent == null ? null : newParent._scrollBar );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_scrollArea.Reset();
		_scrollBar.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_scrollArea.IsDerivedFromParent()
			&& _scrollBar.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "scrollArea" )
			_scrollArea.Reset();
		else if ( fieldName == "scrollBar" )
			_scrollBar.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "scrollArea" )
			return _scrollArea.IsDerivedFromParent();
		if ( fieldName == "scrollBar" )
			return _scrollBar.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Containers", "Scroll Area", "Layout")]
public class UIScrollAreaLayout : UILayout
{
	private UndoRedoDBPtr<UIScrollAreaLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIScrollAreaLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _handleMsgForXScroll;
	private UndoRedo<string> _handleMsgForYScroll;
	private UIScrollLimits _scrollXLimits;
	private UIScrollLimits _scrollYLimits;
	private UndoRedo<string> _spawnMsgOnLimitsChanged;

	[Category( "Script" )]
	public string handleMsgForXScroll { get { return _handleMsgForXScroll.Get(); } set { _handleMsgForXScroll.Set( value ); } }

	[Category( "Script" )]
	public string handleMsgForYScroll { get { return _handleMsgForYScroll.Get(); } set { _handleMsgForYScroll.Set( value ); } }

	[Category( "Script" )]
	public UIScrollLimits scrollXLimits { get { return _scrollXLimits; } set { _scrollXLimits.Assign( value ); } }

	[Category( "Script" )]
	public UIScrollLimits scrollYLimits { get { return _scrollYLimits; } set { _scrollYLimits.Assign( value ); } }

	[Category( "Script" )]
	public string spawnMsgOnLimitsChanged { get { return _spawnMsgOnLimitsChanged.Get(); } set { _spawnMsgOnLimitsChanged.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIScrollAreaLayout>(owner);
		_handleMsgForXScroll = new UndoRedo<string>( owner, string.Empty );
		_handleMsgForYScroll = new UndoRedo<string>( owner, string.Empty );
		_scrollXLimits = new UIScrollLimits( owner );
		_scrollYLimits = new UIScrollLimits( owner );
		_spawnMsgOnLimitsChanged = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_handleMsgForXScroll.Changed += FireChangedEvent;
		_handleMsgForYScroll.Changed += FireChangedEvent;
		_scrollXLimits.Changed += FireChangedEvent;
		_scrollYLimits.Changed += FireChangedEvent;
		_spawnMsgOnLimitsChanged.Changed += FireChangedEvent;
	}

	public UIScrollAreaLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIScrollAreaLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIScrollAreaLayout" );
		handleMsgForXScroll = source.handleMsgForXScroll;
		handleMsgForYScroll = source.handleMsgForYScroll;
		scrollXLimits = source.scrollXLimits;
		scrollYLimits = source.scrollYLimits;
		spawnMsgOnLimitsChanged = source.spawnMsgOnLimitsChanged;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIScrollAreaLayout source = _source as UIScrollAreaLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScrollAreaLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIScrollAreaLayout newParent = rawParent == null ? null : rawParent.Get<UIScrollAreaLayout>();
		if ( newParent == null && _newParent is UIScrollAreaLayout )
			newParent = _newParent as UIScrollAreaLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_handleMsgForXScroll.SetParent( newParent == null ? null : newParent._handleMsgForXScroll );
		_handleMsgForYScroll.SetParent( newParent == null ? null : newParent._handleMsgForYScroll );
		_scrollXLimits.SetParent( newParent == null ? null : newParent._scrollXLimits );
		_scrollYLimits.SetParent( newParent == null ? null : newParent._scrollYLimits );
		_spawnMsgOnLimitsChanged.SetParent( newParent == null ? null : newParent._spawnMsgOnLimitsChanged );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_handleMsgForXScroll.Reset();
		_handleMsgForYScroll.Reset();
		_scrollXLimits.Reset();
		_scrollYLimits.Reset();
		_spawnMsgOnLimitsChanged.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_handleMsgForXScroll.IsDerivedFromParent()
			&& _handleMsgForYScroll.IsDerivedFromParent()
			&& _scrollXLimits.IsDerivedFromParent()
			&& _scrollYLimits.IsDerivedFromParent()
			&& _spawnMsgOnLimitsChanged.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "handleMsgForXScroll" )
			_handleMsgForXScroll.Reset();
		else if ( fieldName == "handleMsgForYScroll" )
			_handleMsgForYScroll.Reset();
		else if ( fieldName == "scrollXLimits" )
			_scrollXLimits.Reset();
		else if ( fieldName == "scrollYLimits" )
			_scrollYLimits.Reset();
		else if ( fieldName == "spawnMsgOnLimitsChanged" )
			_spawnMsgOnLimitsChanged.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "handleMsgForXScroll" )
			return _handleMsgForXScroll.IsDerivedFromParent();
		if ( fieldName == "handleMsgForYScroll" )
			return _handleMsgForYScroll.IsDerivedFromParent();
		if ( fieldName == "scrollXLimits" )
			return _scrollXLimits.IsDerivedFromParent();
		if ( fieldName == "scrollYLimits" )
			return _scrollYLimits.IsDerivedFromParent();
		if ( fieldName == "spawnMsgOnLimitsChanged" )
			return _spawnMsgOnLimitsChanged.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Controls", "Scroll Bar", "Layout")]
public class UIScrollBarLayout : UILayout
{
	private UndoRedoDBPtr<UIScrollBarLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIScrollBarLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUIScrollBarType> _scrollBarType;
	private UndoRedo<int> _discretePositionsCount;
	private UndoRedo<EUIDiscreteType> _discreteType;
	private UndoRedo<string> _spawnMsgOnScrolled;
	private UndoRedoDBPtr<BaseUIMaterial> _leverAreaMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _leverAreaDisabledMaterial;
	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _leverMaterials;
	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _firstButtonMaterials;
	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _secondButtonMaterials;
	private UndoRedo<int> _leverSize;
	private UndoRedo<int> _firstButtonSize;
	private UndoRedo<int> _secondButtonSize;

	public EUIScrollBarType scrollBarType { get { return _scrollBarType.Get(); } set { _scrollBarType.Set( value ); } }

	public int discretePositionsCount { get { return _discretePositionsCount.Get(); } set { _discretePositionsCount.Set( value ); } }

	public EUIDiscreteType discreteType { get { return _discreteType.Get(); } set { _discreteType.Set( value ); } }

	public string spawnMsgOnScrolled { get { return _spawnMsgOnScrolled.Get(); } set { _spawnMsgOnScrolled.Set( value ); } }

	public DBPtr<BaseUIMaterial> leverAreaMaterial { get { return _leverAreaMaterial.Get(); } set { _leverAreaMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> leverAreaDisabledMaterial { get { return _leverAreaDisabledMaterial.Get(); } set { _leverAreaDisabledMaterial.Set( value ); } }

	[EnumArray(typeof(EUIScrollBarElementStyle))]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> leverMaterials { get { return _leverMaterials; } set { _leverMaterials.Assign( value ); } }

	[EnumArray(typeof(EUIScrollBarElementStyle))]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> firstButtonMaterials { get { return _firstButtonMaterials; } set { _firstButtonMaterials.Assign( value ); } }

	[EnumArray(typeof(EUIScrollBarElementStyle))]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> secondButtonMaterials { get { return _secondButtonMaterials; } set { _secondButtonMaterials.Assign( value ); } }

	public int leverSize { get { return _leverSize.Get(); } set { _leverSize.Set( value ); } }

	public int firstButtonSize { get { return _firstButtonSize.Get(); } set { _firstButtonSize.Set( value ); } }

	public int secondButtonSize { get { return _secondButtonSize.Get(); } set { _secondButtonSize.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIScrollBarLayout>(owner);
		_scrollBarType = new UndoRedo<EUIScrollBarType>( owner, EUIScrollBarType.Vertical );
		_discretePositionsCount = new UndoRedo<int>( owner, 0 );
		_discreteType = new UndoRedo<EUIDiscreteType>( owner, EUIDiscreteType.None );
		_spawnMsgOnScrolled = new UndoRedo<string>( owner, string.Empty );
		_leverAreaMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_leverAreaDisabledMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_leverMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( EUIScrollBarElementStyle ) );
		_firstButtonMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( EUIScrollBarElementStyle ) );
		_secondButtonMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( EUIScrollBarElementStyle ) );
		_leverSize = new UndoRedo<int>( owner, 0 );
		_firstButtonSize = new UndoRedo<int>( owner, 0 );
		_secondButtonSize = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_scrollBarType.Changed += FireChangedEvent;
		_discretePositionsCount.Changed += FireChangedEvent;
		_discreteType.Changed += FireChangedEvent;
		_spawnMsgOnScrolled.Changed += FireChangedEvent;
		_leverAreaMaterial.Changed += FireChangedEvent;
		_leverAreaDisabledMaterial.Changed += FireChangedEvent;
		_leverMaterials.Changed += FireChangedEvent;
		_firstButtonMaterials.Changed += FireChangedEvent;
		_secondButtonMaterials.Changed += FireChangedEvent;
		_leverSize.Changed += FireChangedEvent;
		_firstButtonSize.Changed += FireChangedEvent;
		_secondButtonSize.Changed += FireChangedEvent;
	}

	public UIScrollBarLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIScrollBarLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIScrollBarLayout" );
		scrollBarType = source.scrollBarType;
		discretePositionsCount = source.discretePositionsCount;
		discreteType = source.discreteType;
		spawnMsgOnScrolled = source.spawnMsgOnScrolled;
		leverAreaMaterial = source.leverAreaMaterial;
		leverAreaDisabledMaterial = source.leverAreaDisabledMaterial;
		leverMaterials = source.leverMaterials;
		firstButtonMaterials = source.firstButtonMaterials;
		secondButtonMaterials = source.secondButtonMaterials;
		leverSize = source.leverSize;
		firstButtonSize = source.firstButtonSize;
		secondButtonSize = source.secondButtonSize;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIScrollBarLayout source = _source as UIScrollBarLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScrollBarLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIScrollBarLayout newParent = rawParent == null ? null : rawParent.Get<UIScrollBarLayout>();
		if ( newParent == null && _newParent is UIScrollBarLayout )
			newParent = _newParent as UIScrollBarLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_scrollBarType.SetParent( newParent == null ? null : newParent._scrollBarType );
		_discretePositionsCount.SetParent( newParent == null ? null : newParent._discretePositionsCount );
		_discreteType.SetParent( newParent == null ? null : newParent._discreteType );
		_spawnMsgOnScrolled.SetParent( newParent == null ? null : newParent._spawnMsgOnScrolled );
		_leverAreaMaterial.SetParent( newParent == null ? null : newParent._leverAreaMaterial );
		_leverAreaDisabledMaterial.SetParent( newParent == null ? null : newParent._leverAreaDisabledMaterial );
		_leverMaterials.SetParent( newParent == null ? null : newParent._leverMaterials );
		_firstButtonMaterials.SetParent( newParent == null ? null : newParent._firstButtonMaterials );
		_secondButtonMaterials.SetParent( newParent == null ? null : newParent._secondButtonMaterials );
		_leverSize.SetParent( newParent == null ? null : newParent._leverSize );
		_firstButtonSize.SetParent( newParent == null ? null : newParent._firstButtonSize );
		_secondButtonSize.SetParent( newParent == null ? null : newParent._secondButtonSize );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_scrollBarType.Reset();
		_discretePositionsCount.Reset();
		_discreteType.Reset();
		_spawnMsgOnScrolled.Reset();
		_leverAreaMaterial.Reset();
		_leverAreaDisabledMaterial.Reset();
		_leverMaterials.Reset();
		_firstButtonMaterials.Reset();
		_secondButtonMaterials.Reset();
		_leverSize.Reset();
		_firstButtonSize.Reset();
		_secondButtonSize.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_scrollBarType.IsDerivedFromParent()
			&& _discretePositionsCount.IsDerivedFromParent()
			&& _discreteType.IsDerivedFromParent()
			&& _spawnMsgOnScrolled.IsDerivedFromParent()
			&& _leverAreaMaterial.IsDerivedFromParent()
			&& _leverAreaDisabledMaterial.IsDerivedFromParent()
			&& _leverMaterials.IsDerivedFromParent()
			&& _firstButtonMaterials.IsDerivedFromParent()
			&& _secondButtonMaterials.IsDerivedFromParent()
			&& _leverSize.IsDerivedFromParent()
			&& _firstButtonSize.IsDerivedFromParent()
			&& _secondButtonSize.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "scrollBarType" )
			_scrollBarType.Reset();
		else if ( fieldName == "discretePositionsCount" )
			_discretePositionsCount.Reset();
		else if ( fieldName == "discreteType" )
			_discreteType.Reset();
		else if ( fieldName == "spawnMsgOnScrolled" )
			_spawnMsgOnScrolled.Reset();
		else if ( fieldName == "leverAreaMaterial" )
			_leverAreaMaterial.Reset();
		else if ( fieldName == "leverAreaDisabledMaterial" )
			_leverAreaDisabledMaterial.Reset();
		else if ( fieldName == "leverMaterials" )
			_leverMaterials.Reset();
		else if ( fieldName == "firstButtonMaterials" )
			_firstButtonMaterials.Reset();
		else if ( fieldName == "secondButtonMaterials" )
			_secondButtonMaterials.Reset();
		else if ( fieldName == "leverSize" )
			_leverSize.Reset();
		else if ( fieldName == "firstButtonSize" )
			_firstButtonSize.Reset();
		else if ( fieldName == "secondButtonSize" )
			_secondButtonSize.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "scrollBarType" )
			return _scrollBarType.IsDerivedFromParent();
		if ( fieldName == "discretePositionsCount" )
			return _discretePositionsCount.IsDerivedFromParent();
		if ( fieldName == "discreteType" )
			return _discreteType.IsDerivedFromParent();
		if ( fieldName == "spawnMsgOnScrolled" )
			return _spawnMsgOnScrolled.IsDerivedFromParent();
		if ( fieldName == "leverAreaMaterial" )
			return _leverAreaMaterial.IsDerivedFromParent();
		if ( fieldName == "leverAreaDisabledMaterial" )
			return _leverAreaDisabledMaterial.IsDerivedFromParent();
		if ( fieldName == "leverMaterials" )
			return _leverMaterials.IsDerivedFromParent();
		if ( fieldName == "firstButtonMaterials" )
			return _firstButtonMaterials.IsDerivedFromParent();
		if ( fieldName == "secondButtonMaterials" )
			return _secondButtonMaterials.IsDerivedFromParent();
		if ( fieldName == "leverSize" )
			return _leverSize.IsDerivedFromParent();
		if ( fieldName == "firstButtonSize" )
			return _firstButtonSize.IsDerivedFromParent();
		if ( fieldName == "secondButtonSize" )
			return _secondButtonSize.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("Containers", "Scroll List", "Layout")]
public class UIScrollListLayout : UIScrollAreaLayout
{
	private UndoRedoDBPtr<UIScrollListLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIScrollListLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUIListItemsPlacingOrigin> _placingOrigin;
	private UndoRedo<EUIListItemsPlacingOrder> _placingOrder;
	private FloatPoint _minItemSize;
	private FloatPoint _maxItemSize;
	private UndoRedo<int> _maxItemsTotal;
	private UndoRedo<int> _maxStrideItems;
	private UndoRedoDBPtr<BaseUIMaterial> _hilightMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _preselectMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _selectionMaterial;
	private UndoRedo<string> _spawnMsgOnItemHighlighted;
	private UndoRedo<string> _spawnMsgOnItemSelected;

	[Category( "List Items" )]
	public EUIListItemsPlacingOrigin placingOrigin { get { return _placingOrigin.Get(); } set { _placingOrigin.Set( value ); } }

	[Category( "List Items" )]
	public EUIListItemsPlacingOrder placingOrder { get { return _placingOrder.Get(); } set { _placingOrder.Set( value ); } }

	[Category( "List Items" )]
	public FloatPoint minItemSize { get { return _minItemSize; } set { _minItemSize.Assign( value ); } }

	[Category( "List Items" )]
	public FloatPoint maxItemSize { get { return _maxItemSize; } set { _maxItemSize.Assign( value ); } }

	[Category( "List Items" )]
	public int maxItemsTotal { get { return _maxItemsTotal.Get(); } set { _maxItemsTotal.Set( value ); } }

	[Category( "List Items" )]
	public int maxStrideItems { get { return _maxStrideItems.Get(); } set { _maxStrideItems.Set( value ); } }

	public DBPtr<BaseUIMaterial> hilightMaterial { get { return _hilightMaterial.Get(); } set { _hilightMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> preselectMaterial { get { return _preselectMaterial.Get(); } set { _preselectMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> selectionMaterial { get { return _selectionMaterial.Get(); } set { _selectionMaterial.Set( value ); } }

	[Category( "Script" )]
	public string spawnMsgOnItemHighlighted { get { return _spawnMsgOnItemHighlighted.Get(); } set { _spawnMsgOnItemHighlighted.Set( value ); } }

	[Category( "Script" )]
	public string spawnMsgOnItemSelected { get { return _spawnMsgOnItemSelected.Get(); } set { _spawnMsgOnItemSelected.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIScrollListLayout>(owner);
		_placingOrigin = new UndoRedo<EUIListItemsPlacingOrigin>( owner, EUIListItemsPlacingOrigin.LeftTop );
		_placingOrder = new UndoRedo<EUIListItemsPlacingOrder>( owner, EUIListItemsPlacingOrder.ByRows );
		_minItemSize = new FloatPoint( owner );
		_maxItemSize = new FloatPoint( owner );
		_maxItemsTotal = new UndoRedo<int>( owner, 0 );
		_maxStrideItems = new UndoRedo<int>( owner, 0 );
		_hilightMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_preselectMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_selectionMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_spawnMsgOnItemHighlighted = new UndoRedo<string>( owner, string.Empty );
		_spawnMsgOnItemSelected = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_placingOrigin.Changed += FireChangedEvent;
		_placingOrder.Changed += FireChangedEvent;
		_minItemSize.Changed += FireChangedEvent;
		_maxItemSize.Changed += FireChangedEvent;
		_maxItemsTotal.Changed += FireChangedEvent;
		_maxStrideItems.Changed += FireChangedEvent;
		_hilightMaterial.Changed += FireChangedEvent;
		_preselectMaterial.Changed += FireChangedEvent;
		_selectionMaterial.Changed += FireChangedEvent;
		_spawnMsgOnItemHighlighted.Changed += FireChangedEvent;
		_spawnMsgOnItemSelected.Changed += FireChangedEvent;
	}

	public UIScrollListLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIScrollListLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIScrollListLayout" );
		placingOrigin = source.placingOrigin;
		placingOrder = source.placingOrder;
		minItemSize = source.minItemSize;
		maxItemSize = source.maxItemSize;
		maxItemsTotal = source.maxItemsTotal;
		maxStrideItems = source.maxStrideItems;
		hilightMaterial = source.hilightMaterial;
		preselectMaterial = source.preselectMaterial;
		selectionMaterial = source.selectionMaterial;
		spawnMsgOnItemHighlighted = source.spawnMsgOnItemHighlighted;
		spawnMsgOnItemSelected = source.spawnMsgOnItemSelected;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIScrollListLayout source = _source as UIScrollListLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIScrollListLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIScrollListLayout newParent = rawParent == null ? null : rawParent.Get<UIScrollListLayout>();
		if ( newParent == null && _newParent is UIScrollListLayout )
			newParent = _newParent as UIScrollListLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_placingOrigin.SetParent( newParent == null ? null : newParent._placingOrigin );
		_placingOrder.SetParent( newParent == null ? null : newParent._placingOrder );
		_minItemSize.SetParent( newParent == null ? null : newParent._minItemSize );
		_maxItemSize.SetParent( newParent == null ? null : newParent._maxItemSize );
		_maxItemsTotal.SetParent( newParent == null ? null : newParent._maxItemsTotal );
		_maxStrideItems.SetParent( newParent == null ? null : newParent._maxStrideItems );
		_hilightMaterial.SetParent( newParent == null ? null : newParent._hilightMaterial );
		_preselectMaterial.SetParent( newParent == null ? null : newParent._preselectMaterial );
		_selectionMaterial.SetParent( newParent == null ? null : newParent._selectionMaterial );
		_spawnMsgOnItemHighlighted.SetParent( newParent == null ? null : newParent._spawnMsgOnItemHighlighted );
		_spawnMsgOnItemSelected.SetParent( newParent == null ? null : newParent._spawnMsgOnItemSelected );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_placingOrigin.Reset();
		_placingOrder.Reset();
		_minItemSize.Reset();
		_maxItemSize.Reset();
		_maxItemsTotal.Reset();
		_maxStrideItems.Reset();
		_hilightMaterial.Reset();
		_preselectMaterial.Reset();
		_selectionMaterial.Reset();
		_spawnMsgOnItemHighlighted.Reset();
		_spawnMsgOnItemSelected.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_placingOrigin.IsDerivedFromParent()
			&& _placingOrder.IsDerivedFromParent()
			&& _minItemSize.IsDerivedFromParent()
			&& _maxItemSize.IsDerivedFromParent()
			&& _maxItemsTotal.IsDerivedFromParent()
			&& _maxStrideItems.IsDerivedFromParent()
			&& _hilightMaterial.IsDerivedFromParent()
			&& _preselectMaterial.IsDerivedFromParent()
			&& _selectionMaterial.IsDerivedFromParent()
			&& _spawnMsgOnItemHighlighted.IsDerivedFromParent()
			&& _spawnMsgOnItemSelected.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "placingOrigin" )
			_placingOrigin.Reset();
		else if ( fieldName == "placingOrder" )
			_placingOrder.Reset();
		else if ( fieldName == "minItemSize" )
			_minItemSize.Reset();
		else if ( fieldName == "maxItemSize" )
			_maxItemSize.Reset();
		else if ( fieldName == "maxItemsTotal" )
			_maxItemsTotal.Reset();
		else if ( fieldName == "maxStrideItems" )
			_maxStrideItems.Reset();
		else if ( fieldName == "hilightMaterial" )
			_hilightMaterial.Reset();
		else if ( fieldName == "preselectMaterial" )
			_preselectMaterial.Reset();
		else if ( fieldName == "selectionMaterial" )
			_selectionMaterial.Reset();
		else if ( fieldName == "spawnMsgOnItemHighlighted" )
			_spawnMsgOnItemHighlighted.Reset();
		else if ( fieldName == "spawnMsgOnItemSelected" )
			_spawnMsgOnItemSelected.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "placingOrigin" )
			return _placingOrigin.IsDerivedFromParent();
		if ( fieldName == "placingOrder" )
			return _placingOrder.IsDerivedFromParent();
		if ( fieldName == "minItemSize" )
			return _minItemSize.IsDerivedFromParent();
		if ( fieldName == "maxItemSize" )
			return _maxItemSize.IsDerivedFromParent();
		if ( fieldName == "maxItemsTotal" )
			return _maxItemsTotal.IsDerivedFromParent();
		if ( fieldName == "maxStrideItems" )
			return _maxStrideItems.IsDerivedFromParent();
		if ( fieldName == "hilightMaterial" )
			return _hilightMaterial.IsDerivedFromParent();
		if ( fieldName == "preselectMaterial" )
			return _preselectMaterial.IsDerivedFromParent();
		if ( fieldName == "selectionMaterial" )
			return _selectionMaterial.IsDerivedFromParent();
		if ( fieldName == "spawnMsgOnItemHighlighted" )
			return _spawnMsgOnItemHighlighted.IsDerivedFromParent();
		if ( fieldName == "spawnMsgOnItemSelected" )
			return _spawnMsgOnItemSelected.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Load", "Render::Texture2D", "../Render/TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2D")]
[FactoryImpl("LoadInPool", "Render::Texture2D", "../Render/TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2DIntoPool")]
[UseTypeName("ITEX")]
public class UITexture : Texture
{
	private UndoRedoDBPtr<UITexture> ___parent;
	[HideInOutliner]
	public new DBPtr<UITexture> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _importOnlyShape;
	private UndoRedo<int> _shapeAlphaThreshold;

	public bool importOnlyShape { get { return _importOnlyShape.Get(); } set { _importOnlyShape.Set( value ); } }

	public int shapeAlphaThreshold { get { return _shapeAlphaThreshold.Get(); } set { _shapeAlphaThreshold.Set( value ); } }

	[DstFile("shp")]
	public string shapeFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "shp"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, generatedFileName.ToString()
	); } }
	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UITexture>(owner);
		_importOnlyShape = new UndoRedo<bool>( owner, false );
		_shapeAlphaThreshold = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_importOnlyShape.Changed += FireChangedEvent;
		_shapeAlphaThreshold.Changed += FireChangedEvent;
	}

	public UITexture()
	{
		Initialize( this );
	}
	private void AssignSelf( UITexture source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UITexture" );
		importOnlyShape = source.importOnlyShape;
		shapeAlphaThreshold = source.shapeAlphaThreshold;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UITexture source = _source as UITexture;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UITexture" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UITexture newParent = rawParent == null ? null : rawParent.Get<UITexture>();
		if ( newParent == null && _newParent is UITexture )
			newParent = _newParent as UITexture;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_importOnlyShape.SetParent( newParent == null ? null : newParent._importOnlyShape );
		_shapeAlphaThreshold.SetParent( newParent == null ? null : newParent._shapeAlphaThreshold );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_importOnlyShape.Reset();
		_shapeAlphaThreshold.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_importOnlyShape.IsDerivedFromParent()
			&& _shapeAlphaThreshold.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "importOnlyShape" )
			_importOnlyShape.Reset();
		else if ( fieldName == "shapeAlphaThreshold" )
			_shapeAlphaThreshold.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "importOnlyShape" )
			return _importOnlyShape.IsDerivedFromParent();
		if ( fieldName == "shapeAlphaThreshold" )
			return _shapeAlphaThreshold.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[ToolBoxItem("General", "View", "View")]
[UseTypeName("View")]
public class UIViewLayout : UILayout
{
	private UndoRedoDBPtr<UIViewLayout> ___parent;
	[HideInOutliner]
	public new DBPtr<UIViewLayout> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _provider;
	private UndoRedo<string> _address;
	private UndoRedo<int> _framesPerSecond;

	[Category( "View" )]
	public string provider { get { return _provider.Get(); } set { _provider.Set( value ); } }

	[Category( "View" )]
	public string address { get { return _address.Get(); } set { _address.Set( value ); } }

	[Category( "Image" )]
	public int framesPerSecond { get { return _framesPerSecond.Get(); } set { _framesPerSecond.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIViewLayout>(owner);
		_provider = new UndoRedo<string>( owner, string.Empty );
		_address = new UndoRedo<string>( owner, string.Empty );
		_framesPerSecond = new UndoRedo<int>( owner, 15 );
		___parent.Changed += FireChangedEvent;
		_provider.Changed += FireChangedEvent;
		_address.Changed += FireChangedEvent;
		_framesPerSecond.Changed += FireChangedEvent;
	}

	public UIViewLayout()
	{
		Initialize( this );
	}
	private void AssignSelf( UIViewLayout source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIViewLayout" );
		provider = source.provider;
		address = source.address;
		framesPerSecond = source.framesPerSecond;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIViewLayout source = _source as UIViewLayout;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIViewLayout" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIViewLayout newParent = rawParent == null ? null : rawParent.Get<UIViewLayout>();
		if ( newParent == null && _newParent is UIViewLayout )
			newParent = _newParent as UIViewLayout;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_provider.SetParent( newParent == null ? null : newParent._provider );
		_address.SetParent( newParent == null ? null : newParent._address );
		_framesPerSecond.SetParent( newParent == null ? null : newParent._framesPerSecond );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_provider.Reset();
		_address.Reset();
		_framesPerSecond.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_provider.IsDerivedFromParent()
			&& _address.IsDerivedFromParent()
			&& _framesPerSecond.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "provider" )
			_provider.Reset();
		else if ( fieldName == "address" )
			_address.Reset();
		else if ( fieldName == "framesPerSecond" )
			_framesPerSecond.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "provider" )
			return _provider.IsDerivedFromParent();
		if ( fieldName == "address" )
			return _address.IsDerivedFromParent();
		if ( fieldName == "framesPerSecond" )
			return _framesPerSecond.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
