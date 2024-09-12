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
public enum EAnimEventType
{
	NodeEnter = 0,
	NodeLeave = 1,
	NodeParam = 2,
	Marker = 3,
};

[Flags]
public enum EAttachFlags
{
	None = 0,
	UseParentScale = 1,
	UseParentRotation = 2,
	UseParentTime = 4,
	UseAGSpeedCoeff = 8,
	StayInWorld = 16,
	CancelOffsetScaling = 32,
};

public enum EEnableDisableOrder
{
	EnableThenDisable = 0,
	DisableThenEnable = 1,
};

[Flags]
public enum EGroupFlags
{
	None = 0,
	Recolorable = 4,
};

public enum ELightningAnimType
{
	None = 0,
	Sequential = 1,
	Randomized = 2,
};

public enum EOrientType
{
	None = 0,
	Axis = 1,
	Speed = 2,
	Plane = 3,
};

public enum ESCOrientation
{
	Default = 0,
	Camera = 1,
	CameraFixedZ = 2,
};

[Flags]
public enum EStandAloneEffectFlags
{
	None = 0,
	UseParentScale = 1,
	UseParentRotation = 2,
};

public enum Sound3DSimultType
{
	Melee = 0,
	Range = 1,
	CreepDeath = 2,
	Infinite = 3,
};

public class AnimatedPlacement : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimatedPlacement __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private AnimatedVec3 _pos;
	private AnimatedQuat _rot;
	private AnimatedScale _scale;

	public AnimatedVec3 pos { get { return _pos; } set { _pos.Assign( value ); } }

	public AnimatedQuat rot { get { return _rot; } set { _rot.Assign( value ); } }

	public AnimatedScale scale { get { return _scale; } set { _scale.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_pos = new AnimatedVec3( owner );
		_rot = new AnimatedQuat( owner );
		_scale = new AnimatedScale( owner, 1.0f, 1.0f, 1.0f );
		_pos.Changed += FireChangedEvent;
		_rot.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
	}

	public AnimatedPlacement()
	{
		Initialize( GetOwner() );
	}

	public AnimatedPlacement( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimatedPlacement( DBResource owner, AnimatedPlacement source )
		: this(owner, source, true){}

	protected AnimatedPlacement( DBResource owner, AnimatedPlacement source, bool fireEvent )
	{
		_pos = new AnimatedVec3( owner, source.pos );
		_rot = new AnimatedQuat( owner, source.rot );
		_scale = new AnimatedScale( owner, source.scale );
		_pos.Changed += FireChangedEvent;
		_rot.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimatedPlacement source = _source as AnimatedPlacement;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedPlacement" );
		pos = source.pos;
		rot = source.rot;
		scale = source.scale;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimatedPlacement newParent = _newParent as AnimatedPlacement;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_pos.SetParent( newParent == null ? null : newParent._pos );
		_rot.SetParent( newParent == null ? null : newParent._rot );
		_scale.SetParent( newParent == null ? null : newParent._scale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_pos.Reset();
		_rot.Reset();
		_scale.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_pos.IsDerivedFromParent()
			&& _rot.IsDerivedFromParent()
			&& _scale.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "pos" )
			_pos.Reset();
		else if ( fieldName == "rot" )
			_rot.Reset();
		else if ( fieldName == "scale" )
			_scale.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "pos" )
			return _pos.IsDerivedFromParent();
		if ( fieldName == "rot" )
			return _rot.IsDerivedFromParent();
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
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

[IndexField("component")]
public class AttachedSceneComponent : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AttachedSceneComponent __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBSceneComponent> _component;
	private UndoRedo<string> _locatorName;
	private UndoRedoDBPtr<TimeController> _timeController;
	private AnimatedPlacement _placement;
	private UndoRedo<EAttachFlags> _attachFlags;
	private UndoRedo<string> _id;
	private UndoRedoDBPtr<EnableDisableSCEvents> _events;

	public DBPtr<DBSceneComponent> component { get { return _component.Get(); } set { _component.Set( value ); } }

	[LocatorNameSelector]
	public string locatorName { get { return _locatorName.Get(); } set { _locatorName.Set( value ); } }

	public DBPtr<TimeController> timeController { get { return _timeController.Get(); } set { _timeController.Set( value ); } }

	public AnimatedPlacement placement { get { return _placement; } set { _placement.Assign( value ); } }

	public EAttachFlags attachFlags { get { return _attachFlags.Get(); } set { _attachFlags.Set( value ); } }

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	[Description( "Events for enabling and disabling this scene component" )]
	public DBPtr<EnableDisableSCEvents> events { get { return _events.Get(); } set { _events.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_component = new UndoRedoDBPtr<DBSceneComponent>( owner );
		_locatorName = new UndoRedo<string>( owner, string.Empty );
		_timeController = new UndoRedoDBPtr<TimeController>( owner );
		_placement = new AnimatedPlacement( owner );
		_attachFlags = new UndoRedo<EAttachFlags>( owner, EAttachFlags.UseAGSpeedCoeff | EAttachFlags.UseParentTime | EAttachFlags.UseParentRotation | EAttachFlags.UseParentScale );
		_id = new UndoRedo<string>( owner, string.Empty );
		_events = new UndoRedoDBPtr<EnableDisableSCEvents>( owner );
		_component.Changed += FireChangedEvent;
		_locatorName.Changed += FireChangedEvent;
		_timeController.Changed += FireChangedEvent;
		_placement.Changed += FireChangedEvent;
		_attachFlags.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
	}

	public AttachedSceneComponent()
	{
		Initialize( GetOwner() );
	}

	public AttachedSceneComponent( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AttachedSceneComponent( DBResource owner, AttachedSceneComponent source )
		: this(owner, source, true){}

	protected AttachedSceneComponent( DBResource owner, AttachedSceneComponent source, bool fireEvent )
	{
		_component = new UndoRedoDBPtr<DBSceneComponent>( owner, source.component );
		_locatorName = new UndoRedo<string>( owner, source.locatorName );
		_timeController = new UndoRedoDBPtr<TimeController>( owner, source.timeController );
		_placement = new AnimatedPlacement( owner, source.placement );
		_attachFlags = new UndoRedo<EAttachFlags>( owner, source.attachFlags );
		_id = new UndoRedo<string>( owner, source.id );
		_events = new UndoRedoDBPtr<EnableDisableSCEvents>( owner, source.events );
		_component.Changed += FireChangedEvent;
		_locatorName.Changed += FireChangedEvent;
		_timeController.Changed += FireChangedEvent;
		_placement.Changed += FireChangedEvent;
		_attachFlags.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AttachedSceneComponent source = _source as AttachedSceneComponent;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AttachedSceneComponent" );
		component = source.component;
		locatorName = source.locatorName;
		timeController = source.timeController;
		placement = source.placement;
		attachFlags = source.attachFlags;
		id = source.id;
		events = source.events;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AttachedSceneComponent newParent = _newParent as AttachedSceneComponent;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_component.SetParent( newParent == null ? null : newParent._component );
		_locatorName.SetParent( newParent == null ? null : newParent._locatorName );
		_timeController.SetParent( newParent == null ? null : newParent._timeController );
		_placement.SetParent( newParent == null ? null : newParent._placement );
		_attachFlags.SetParent( newParent == null ? null : newParent._attachFlags );
		_id.SetParent( newParent == null ? null : newParent._id );
		_events.SetParent( newParent == null ? null : newParent._events );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_component.Reset();
		_locatorName.Reset();
		_timeController.Reset();
		_placement.Reset();
		_attachFlags.Reset();
		_id.Reset();
		_events.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_component.IsDerivedFromParent()
			&& _locatorName.IsDerivedFromParent()
			&& _timeController.IsDerivedFromParent()
			&& _placement.IsDerivedFromParent()
			&& _attachFlags.IsDerivedFromParent()
			&& _id.IsDerivedFromParent()
			&& _events.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "component" )
			_component.Reset();
		else if ( fieldName == "locatorName" )
			_locatorName.Reset();
		else if ( fieldName == "timeController" )
			_timeController.Reset();
		else if ( fieldName == "placement" )
			_placement.Reset();
		else if ( fieldName == "attachFlags" )
			_attachFlags.Reset();
		else if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "events" )
			_events.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "component" )
			return _component.IsDerivedFromParent();
		if ( fieldName == "locatorName" )
			return _locatorName.IsDerivedFromParent();
		if ( fieldName == "timeController" )
			return _timeController.IsDerivedFromParent();
		if ( fieldName == "placement" )
			return _placement.IsDerivedFromParent();
		if ( fieldName == "attachFlags" )
			return _attachFlags.IsDerivedFromParent();
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "events" )
			return _events.IsDerivedFromParent();
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

public class DBLightningFXParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBLightningFXParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _animAtlasSize;
	private UndoRedo<int> _animFirstFrame;
	private UndoRedo<int> _animLastFrame;
	private UndoRedo<float> _animSpeed;
	private UndoRedo<ELightningAnimType> _animType;
	private UndoRedo<float> _opacityDistance1;
	private UndoRedo<float> _opacityDistance2;
	private HDRColor _color;
	private UndoRedo<float> _radius;
	private UndoRedo<float> _scrollSpeed;
	private UndoRedo<float> _tiling;

	[Description( "Total number of subtextures in texture atlas." )]
	public int animAtlasSize { get { return _animAtlasSize.Get(); } set { _animAtlasSize.Set( value ); } }

	[Description( "Zero-based index of the first subtexture used in animation." )]
	public int animFirstFrame { get { return _animFirstFrame.Get(); } set { _animFirstFrame.Set( value ); } }

	[Description( "Zero-based index of the last subtexture used in animation." )]
	public int animLastFrame { get { return _animLastFrame.Get(); } set { _animLastFrame.Set( value ); } }

	[Description( "Texture animation speed, in frames per second." )]
	public float animSpeed { get { return _animSpeed.Get(); } set { _animSpeed.Set( value ); } }

	[Description( "Texture animation type." )]
	public ELightningAnimType animType { get { return _animType.Get(); } set { _animType.Set( value ); } }

	[Description( "Opacity fadeout distance at the beginning" )]
	public float opacityDistance1 { get { return _opacityDistance1.Get(); } set { _opacityDistance1.Set( value ); } }

	[Description( "Opacity fadeout distance at the end" )]
	public float opacityDistance2 { get { return _opacityDistance2.Get(); } set { _opacityDistance2.Set( value ); } }

	[Description( "Color to modulate the texture." )]
	public HDRColor color { get { return _color; } set { _color.Assign( value ); } }

	[Description( "Thickness of the lightning geometry." )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Description( "Texture scroll speed, in meters per second." )]
	public float scrollSpeed { get { return _scrollSpeed.Get(); } set { _scrollSpeed.Set( value ); } }

	[Description( "Texture mapping length along the lightning, in meters." )]
	public float tiling { get { return _tiling.Get(); } set { _tiling.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_animAtlasSize = new UndoRedo<int>( owner, 1 );
		_animFirstFrame = new UndoRedo<int>( owner, 0 );
		_animLastFrame = new UndoRedo<int>( owner, 0 );
		_animSpeed = new UndoRedo<float>( owner, 0.0f );
		_animType = new UndoRedo<ELightningAnimType>( owner, ELightningAnimType.None );
		_opacityDistance1 = new UndoRedo<float>( owner, 0.0f );
		_opacityDistance2 = new UndoRedo<float>( owner, 0.0f );
		HDRColor __color = new HDRColor(); // Construct default object for color
		__color.R = 1.0f;
		__color.G = 1.0f;
		__color.B = 1.0f;
		_color = new HDRColor( owner, __color );
		_radius = new UndoRedo<float>( owner, 0.25f );
		_scrollSpeed = new UndoRedo<float>( owner, 0.0f );
		_tiling = new UndoRedo<float>( owner, 5.0f );
		_animAtlasSize.Changed += FireChangedEvent;
		_animFirstFrame.Changed += FireChangedEvent;
		_animLastFrame.Changed += FireChangedEvent;
		_animSpeed.Changed += FireChangedEvent;
		_animType.Changed += FireChangedEvent;
		_opacityDistance1.Changed += FireChangedEvent;
		_opacityDistance2.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_scrollSpeed.Changed += FireChangedEvent;
		_tiling.Changed += FireChangedEvent;
	}

	public DBLightningFXParams()
	{
		Initialize( GetOwner() );
	}

	public DBLightningFXParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBLightningFXParams( DBResource owner, DBLightningFXParams source )
		: this(owner, source, true){}

	protected DBLightningFXParams( DBResource owner, DBLightningFXParams source, bool fireEvent )
	{
		_animAtlasSize = new UndoRedo<int>( owner, source.animAtlasSize );
		_animFirstFrame = new UndoRedo<int>( owner, source.animFirstFrame );
		_animLastFrame = new UndoRedo<int>( owner, source.animLastFrame );
		_animSpeed = new UndoRedo<float>( owner, source.animSpeed );
		_animType = new UndoRedo<ELightningAnimType>( owner, source.animType );
		_opacityDistance1 = new UndoRedo<float>( owner, source.opacityDistance1 );
		_opacityDistance2 = new UndoRedo<float>( owner, source.opacityDistance2 );
		_color = new HDRColor( owner, source.color );
		_radius = new UndoRedo<float>( owner, source.radius );
		_scrollSpeed = new UndoRedo<float>( owner, source.scrollSpeed );
		_tiling = new UndoRedo<float>( owner, source.tiling );
		_animAtlasSize.Changed += FireChangedEvent;
		_animFirstFrame.Changed += FireChangedEvent;
		_animLastFrame.Changed += FireChangedEvent;
		_animSpeed.Changed += FireChangedEvent;
		_animType.Changed += FireChangedEvent;
		_opacityDistance1.Changed += FireChangedEvent;
		_opacityDistance2.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_scrollSpeed.Changed += FireChangedEvent;
		_tiling.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBLightningFXParams source = _source as DBLightningFXParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLightningFXParams" );
		animAtlasSize = source.animAtlasSize;
		animFirstFrame = source.animFirstFrame;
		animLastFrame = source.animLastFrame;
		animSpeed = source.animSpeed;
		animType = source.animType;
		opacityDistance1 = source.opacityDistance1;
		opacityDistance2 = source.opacityDistance2;
		color = source.color;
		radius = source.radius;
		scrollSpeed = source.scrollSpeed;
		tiling = source.tiling;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBLightningFXParams newParent = _newParent as DBLightningFXParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_animAtlasSize.SetParent( newParent == null ? null : newParent._animAtlasSize );
		_animFirstFrame.SetParent( newParent == null ? null : newParent._animFirstFrame );
		_animLastFrame.SetParent( newParent == null ? null : newParent._animLastFrame );
		_animSpeed.SetParent( newParent == null ? null : newParent._animSpeed );
		_animType.SetParent( newParent == null ? null : newParent._animType );
		_opacityDistance1.SetParent( newParent == null ? null : newParent._opacityDistance1 );
		_opacityDistance2.SetParent( newParent == null ? null : newParent._opacityDistance2 );
		_color.SetParent( newParent == null ? null : newParent._color );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_scrollSpeed.SetParent( newParent == null ? null : newParent._scrollSpeed );
		_tiling.SetParent( newParent == null ? null : newParent._tiling );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_animAtlasSize.Reset();
		_animFirstFrame.Reset();
		_animLastFrame.Reset();
		_animSpeed.Reset();
		_animType.Reset();
		_opacityDistance1.Reset();
		_opacityDistance2.Reset();
		_color.Reset();
		_radius.Reset();
		_scrollSpeed.Reset();
		_tiling.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_animAtlasSize.IsDerivedFromParent()
			&& _animFirstFrame.IsDerivedFromParent()
			&& _animLastFrame.IsDerivedFromParent()
			&& _animSpeed.IsDerivedFromParent()
			&& _animType.IsDerivedFromParent()
			&& _opacityDistance1.IsDerivedFromParent()
			&& _opacityDistance2.IsDerivedFromParent()
			&& _color.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _scrollSpeed.IsDerivedFromParent()
			&& _tiling.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "animAtlasSize" )
			_animAtlasSize.Reset();
		else if ( fieldName == "animFirstFrame" )
			_animFirstFrame.Reset();
		else if ( fieldName == "animLastFrame" )
			_animLastFrame.Reset();
		else if ( fieldName == "animSpeed" )
			_animSpeed.Reset();
		else if ( fieldName == "animType" )
			_animType.Reset();
		else if ( fieldName == "opacityDistance1" )
			_opacityDistance1.Reset();
		else if ( fieldName == "opacityDistance2" )
			_opacityDistance2.Reset();
		else if ( fieldName == "color" )
			_color.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "scrollSpeed" )
			_scrollSpeed.Reset();
		else if ( fieldName == "tiling" )
			_tiling.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "animAtlasSize" )
			return _animAtlasSize.IsDerivedFromParent();
		if ( fieldName == "animFirstFrame" )
			return _animFirstFrame.IsDerivedFromParent();
		if ( fieldName == "animLastFrame" )
			return _animLastFrame.IsDerivedFromParent();
		if ( fieldName == "animSpeed" )
			return _animSpeed.IsDerivedFromParent();
		if ( fieldName == "animType" )
			return _animType.IsDerivedFromParent();
		if ( fieldName == "opacityDistance1" )
			return _opacityDistance1.IsDerivedFromParent();
		if ( fieldName == "opacityDistance2" )
			return _opacityDistance2.IsDerivedFromParent();
		if ( fieldName == "color" )
			return _color.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "scrollSpeed" )
			return _scrollSpeed.IsDerivedFromParent();
		if ( fieldName == "tiling" )
			return _tiling.IsDerivedFromParent();
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

public class SkinPart : SkinPartBase, libdb.ICompositeDBValue, libdb.IChangeable
{

	private SkinPart __parent = null;

	private UndoRedoDBPtr<EnableDisableSkinEvents> _events;

	[Description( "Events for enabling and disabling this skin" )]
	public DBPtr<EnableDisableSkinEvents> events { get { return _events.Get(); } set { _events.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_events = new UndoRedoDBPtr<EnableDisableSkinEvents>( owner );
		_events.Changed += FireChangedEvent;
	}

	public SkinPart()
	{
		Initialize( GetOwner() );
	}

	public SkinPart( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public SkinPart( DBResource owner, SkinPart source ): base(owner, source, false)
	{
		_events = new UndoRedoDBPtr<EnableDisableSkinEvents>( owner, source.events );
		_events.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		SkinPart source = _source as SkinPart;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkinPart" );

		base.Assign( source );

		events = source.events;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		SkinPart newParent = _newParent as SkinPart;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_events.SetParent( newParent == null ? null : newParent._events );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_events.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_events.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "events" )
			_events.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "events" )
			return _events.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xA071B300)]
[UseTypeName("ANPL")]
public class AnimatedPlacementResource : DBResource
{
	private UndoRedoDBPtr<AnimatedPlacementResource> ___parent;
	[HideInOutliner]
	public new DBPtr<AnimatedPlacementResource> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AnimatedPlacement _placement;

	public AnimatedPlacement placement { get { return _placement; } set { _placement.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AnimatedPlacementResource>(owner);
		_placement = new AnimatedPlacement( owner );
		___parent.Changed += FireChangedEvent;
		_placement.Changed += FireChangedEvent;
	}

	public AnimatedPlacementResource()
	{
		Initialize( this );
	}
	private void AssignSelf( AnimatedPlacementResource source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AnimatedPlacementResource" );
		placement = source.placement;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AnimatedPlacementResource source = _source as AnimatedPlacementResource;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedPlacementResource" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AnimatedPlacementResource newParent = rawParent == null ? null : rawParent.Get<AnimatedPlacementResource>();
		if ( newParent == null && _newParent is AnimatedPlacementResource )
			newParent = _newParent as AnimatedPlacementResource;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_placement.SetParent( newParent == null ? null : newParent._placement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_placement.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_placement.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "placement" )
			_placement.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "placement" )
			return _placement.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E6433C1)]
[UseTypeName("SCEV")]
public class SCEvent : DBResource
{
	private UndoRedoDBPtr<SCEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<SCEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SCEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public SCEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( SCEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SCEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SCEvent source = _source as SCEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SCEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SCEvent newParent = rawParent == null ? null : rawParent.Get<SCEvent>();
		if ( newParent == null && _newParent is SCEvent )
			newParent = _newParent as SCEvent;
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

[NonTerminal]
public class DBSceneResource : DBResource
{
	private UndoRedoDBPtr<DBSceneResource> ___parent;
	[HideInOutliner]
	public new DBPtr<DBSceneResource> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<AttachedSceneComponent> _attached;

	public libdb.IChangeableList<AttachedSceneComponent> attached { get { return _attached; } set { _attached.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBSceneResource>(owner);
		_attached = new UndoRedoAssignableList<AttachedSceneComponent>( owner );
		___parent.Changed += FireChangedEvent;
		_attached.Changed += FireChangedEvent;
	}

	public DBSceneResource()
	{
		Initialize( this );
	}
	private void AssignSelf( DBSceneResource source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBSceneResource" );
		attached = source.attached;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBSceneResource source = _source as DBSceneResource;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSceneResource" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBSceneResource newParent = rawParent == null ? null : rawParent.Get<DBSceneResource>();
		if ( newParent == null && _newParent is DBSceneResource )
			newParent = _newParent as DBSceneResource;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_attached.SetParent( newParent == null ? null : newParent._attached );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_attached.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_attached.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "attached" )
			_attached.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "attached" )
			return _attached.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x8D5A3B40)]
public class DBAnimKey : DBResource
{
	private UndoRedoDBPtr<DBAnimKey> ___parent;
	[HideInOutliner]
	public new DBPtr<DBAnimKey> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBAnimKey>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public DBAnimKey()
	{
		Initialize( this );
	}
	private void AssignSelf( DBAnimKey source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBAnimKey" );
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBAnimKey source = _source as DBAnimKey;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBAnimKey" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBAnimKey newParent = rawParent == null ? null : rawParent.Get<DBAnimKey>();
		if ( newParent == null && _newParent is DBAnimKey )
			newParent = _newParent as DBAnimKey;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x8D5A3AC0)]
public class DBAttachAnimKey : DBAnimKey
{
	private UndoRedoDBPtr<DBAttachAnimKey> ___parent;
	[HideInOutliner]
	public new DBPtr<DBAttachAnimKey> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBSceneComponent> _component;

	public DBPtr<DBSceneComponent> component { get { return _component.Get(); } set { _component.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBAttachAnimKey>(owner);
		_component = new UndoRedoDBPtr<DBSceneComponent>( owner );
		___parent.Changed += FireChangedEvent;
		_component.Changed += FireChangedEvent;
	}

	public DBAttachAnimKey()
	{
		Initialize( this );
	}
	private void AssignSelf( DBAttachAnimKey source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBAttachAnimKey" );
		component = source.component;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBAttachAnimKey source = _source as DBAttachAnimKey;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBAttachAnimKey" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBAttachAnimKey newParent = rawParent == null ? null : rawParent.Get<DBAttachAnimKey>();
		if ( newParent == null && _newParent is DBAttachAnimKey )
			newParent = _newParent as DBAttachAnimKey;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_component.SetParent( newParent == null ? null : newParent._component );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_component.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_component.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "component" )
			_component.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "component" )
			return _component.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NScene::SceneComponent", "NScene::HierarchyCreator &creator", "const AttachedSceneComponent* pAttached", "const Placement& transform", ReturnType = "CObj<NScene::SceneComponent>", Define = "!VISUAL_CUTTED")]
[TypeId(0x9E656380)]
public class DBSceneComponentBase : DBSceneResource
{
	private UndoRedoDBPtr<DBSceneComponentBase> ___parent;
	[HideInOutliner]
	public new DBPtr<DBSceneComponentBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBSceneComponentBase>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public DBSceneComponentBase()
	{
		Initialize( this );
	}
	private void AssignSelf( DBSceneComponentBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBSceneComponentBase" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBSceneComponentBase source = _source as DBSceneComponentBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSceneComponentBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBSceneComponentBase newParent = rawParent == null ? null : rawParent.Get<DBSceneComponentBase>();
		if ( newParent == null && _newParent is DBSceneComponentBase )
			newParent = _newParent as DBSceneComponentBase;
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

[FactoryImpl("Create", "NScene::SceneComponent", "SceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[IndexField("caption")]
[TypeId(0x8D5A1240)]
[UseTypeName("PRXY")]
public class DBSceneComponent : DBSceneComponentBase
{
	private UndoRedoDBPtr<DBSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<LocatorList> _locatorList;
	private UndoRedo<ESCOrientation> _orientation;
	private UndoRedo<EGroupFlags> _groupFlags;
	private UndoRedo<string> _caption;

	[Description( "List of locators" )]
	public DBPtr<LocatorList> locatorList { get { return _locatorList.Get(); } set { _locatorList.Set( value ); } }

	[Description( "Automatic orientation of the component ('Default' means straight application of attachFlags)" )]
	public ESCOrientation orientation { get { return _orientation.Get(); } set { _orientation.Set( value ); } }

	[Description( "Flags allowing to mark component as belonging to some game specific group" )]
	public EGroupFlags groupFlags { get { return _groupFlags.Get(); } set { _groupFlags.Set( value ); } }

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBSceneComponent>(owner);
		_locatorList = new UndoRedoDBPtr<LocatorList>( owner );
		_orientation = new UndoRedo<ESCOrientation>( owner, ESCOrientation.Default );
		_groupFlags = new UndoRedo<EGroupFlags>( owner, EGroupFlags.None );
		_caption = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_locatorList.Changed += FireChangedEvent;
		_orientation.Changed += FireChangedEvent;
		_groupFlags.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
	}

	public DBSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBSceneComponent" );
		locatorList = source.locatorList;
		orientation = source.orientation;
		groupFlags = source.groupFlags;
		caption = source.caption;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBSceneComponent source = _source as DBSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBSceneComponent>();
		if ( newParent == null && _newParent is DBSceneComponent )
			newParent = _newParent as DBSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_locatorList.SetParent( newParent == null ? null : newParent._locatorList );
		_orientation.SetParent( newParent == null ? null : newParent._orientation );
		_groupFlags.SetParent( newParent == null ? null : newParent._groupFlags );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_locatorList.Reset();
		_orientation.Reset();
		_groupFlags.Reset();
		_caption.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_locatorList.IsDerivedFromParent()
			&& _orientation.IsDerivedFromParent()
			&& _groupFlags.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "locatorList" )
			_locatorList.Reset();
		else if ( fieldName == "orientation" )
			_orientation.Reset();
		else if ( fieldName == "groupFlags" )
			_groupFlags.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "locatorList" )
			return _locatorList.IsDerivedFromParent();
		if ( fieldName == "orientation" )
			return _orientation.IsDerivedFromParent();
		if ( fieldName == "groupFlags" )
			return _groupFlags.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NScene::AnimatedSceneComponent", "AnimatedSceneComponent.h", CreateFunction = "NScene::CreateAnimatedSceneComponent")]
[TypeId(0x8D5A1241)]
[UseTypeName("ANSC")]
public class DBAnimatedSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBAnimatedSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBAnimatedSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AnimGraphCreator> _additionalGraph;
	private UndoRedo<string> _splitBoneName;
	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private UndoRedoAssignableList<SkinPart> _skins;
	private UndoRedoAssignableList<Animation> _animations;
	private UndoRedoAssignableList<FaceFX> _faceFXAnims;
	private UndoRedoDBPtr<AnimGraphCreator> _animGraph;
	private AABB _aabb;
	private UndoRedoAssignableList<AnimFaceFXKey> _anims;
	private UndoRedoList<int> _skinOn;
	private UndoRedoAssignableList<DBPtr<DBAnimKey>> _keys;

	[Description( "Additional animation graph" )]
	public DBPtr<AnimGraphCreator> additionalGraph { get { return _additionalGraph.Get(); } set { _additionalGraph.Set( value ); } }

	[Description( "Name of bone to split animations" )]
	public string splitBoneName { get { return _splitBoneName.Get(); } set { _splitBoneName.Set( value ); } }

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

	public libdb.IChangeableList<SkinPart> skins { get { return _skins; } set { _skins.Assign( value ); } }

	public libdb.IChangeableList<Animation> animations { get { return _animations; } set { _animations.Assign( value ); } }

	public libdb.IChangeableList<FaceFX> faceFXAnims { get { return _faceFXAnims; } set { _faceFXAnims.Assign( value ); } }

	public DBPtr<AnimGraphCreator> animGraph { get { return _animGraph.Get(); } set { _animGraph.Set( value ); } }

	public AABB aabb { get { return _aabb; } set { _aabb.Assign( value ); } }

	public libdb.IChangeableList<AnimFaceFXKey> anims { get { return _anims; } set { _anims.Assign( value ); } }

	public libdb.IChangeableList<int> skinOn { get { return _skinOn; } set { _skinOn.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<DBAnimKey>> keys { get { return _keys; } set { _keys.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBAnimatedSceneComponent>(owner);
		_additionalGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		_splitBoneName = new UndoRedo<string>( owner, string.Empty );
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_skins = new UndoRedoAssignableList<SkinPart>( owner );
		_animations = new UndoRedoAssignableList<Animation>( owner );
		_faceFXAnims = new UndoRedoAssignableList<FaceFX>( owner );
		_animGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		AABB __aabb = new AABB(); // Construct default object for aabb
		__aabb.minX = 666.0f;
		__aabb.maxX = -666.0f;
		__aabb.minY = 666.0f;
		__aabb.maxY = -666.0f;
		__aabb.minZ = 666.0f;
		__aabb.maxZ = -666.0f;
		_aabb = new AABB( owner, __aabb );
		_anims = new UndoRedoAssignableList<AnimFaceFXKey>( owner );
		_skinOn = new UndoRedoList<int>( owner );
		_keys = new UndoRedoAssignableList<DBPtr<DBAnimKey>>( owner );
		___parent.Changed += FireChangedEvent;
		_additionalGraph.Changed += FireChangedEvent;
		_splitBoneName.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_skins.Changed += FireChangedEvent;
		_animations.Changed += FireChangedEvent;
		_faceFXAnims.Changed += FireChangedEvent;
		_animGraph.Changed += FireChangedEvent;
		_aabb.Changed += FireChangedEvent;
		_anims.Changed += FireChangedEvent;
		_skinOn.Changed += FireChangedEvent;
		_keys.Changed += FireChangedEvent;
	}

	public DBAnimatedSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBAnimatedSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBAnimatedSceneComponent" );
		additionalGraph = source.additionalGraph;
		splitBoneName = source.splitBoneName;
		srcFileName = source.srcFileName;
		selection = source.selection;
		skins = source.skins;
		animations = source.animations;
		faceFXAnims = source.faceFXAnims;
		animGraph = source.animGraph;
		aabb = source.aabb;
		anims = source.anims;
		skinOn = source.skinOn;
		keys = source.keys;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBAnimatedSceneComponent source = _source as DBAnimatedSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBAnimatedSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBAnimatedSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBAnimatedSceneComponent>();
		if ( newParent == null && _newParent is DBAnimatedSceneComponent )
			newParent = _newParent as DBAnimatedSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_additionalGraph.SetParent( newParent == null ? null : newParent._additionalGraph );
		_splitBoneName.SetParent( newParent == null ? null : newParent._splitBoneName );
		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_skins.SetParent( newParent == null ? null : newParent._skins );
		_animations.SetParent( newParent == null ? null : newParent._animations );
		_faceFXAnims.SetParent( newParent == null ? null : newParent._faceFXAnims );
		_animGraph.SetParent( newParent == null ? null : newParent._animGraph );
		_aabb.SetParent( newParent == null ? null : newParent._aabb );
		_anims.SetParent( newParent == null ? null : newParent._anims );
		_skinOn.SetParent( newParent == null ? null : newParent._skinOn );
		_keys.SetParent( newParent == null ? null : newParent._keys );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_additionalGraph.Reset();
		_splitBoneName.Reset();
		_srcFileName.Reset();
		_selection.Reset();
		_skins.Reset();
		_animations.Reset();
		_faceFXAnims.Reset();
		_animGraph.Reset();
		_aabb.Reset();
		_anims.Reset();
		_skinOn.Reset();
		_keys.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_additionalGraph.IsDerivedFromParent()
			&& _splitBoneName.IsDerivedFromParent()
			&& _srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _skins.IsDerivedFromParent()
			&& _animations.IsDerivedFromParent()
			&& _faceFXAnims.IsDerivedFromParent()
			&& _animGraph.IsDerivedFromParent()
			&& _aabb.IsDerivedFromParent()
			&& _anims.IsDerivedFromParent()
			&& _skinOn.IsDerivedFromParent()
			&& _keys.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "additionalGraph" )
			_additionalGraph.Reset();
		else if ( fieldName == "splitBoneName" )
			_splitBoneName.Reset();
		else if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "skins" )
			_skins.Reset();
		else if ( fieldName == "animations" )
			_animations.Reset();
		else if ( fieldName == "faceFXAnims" )
			_faceFXAnims.Reset();
		else if ( fieldName == "animGraph" )
			_animGraph.Reset();
		else if ( fieldName == "aabb" )
			_aabb.Reset();
		else if ( fieldName == "anims" )
			_anims.Reset();
		else if ( fieldName == "skinOn" )
			_skinOn.Reset();
		else if ( fieldName == "keys" )
			_keys.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "additionalGraph" )
			return _additionalGraph.IsDerivedFromParent();
		if ( fieldName == "splitBoneName" )
			return _splitBoneName.IsDerivedFromParent();
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "skins" )
			return _skins.IsDerivedFromParent();
		if ( fieldName == "animations" )
			return _animations.IsDerivedFromParent();
		if ( fieldName == "faceFXAnims" )
			return _faceFXAnims.IsDerivedFromParent();
		if ( fieldName == "animGraph" )
			return _animGraph.IsDerivedFromParent();
		if ( fieldName == "aabb" )
			return _aabb.IsDerivedFromParent();
		if ( fieldName == "anims" )
			return _anims.IsDerivedFromParent();
		if ( fieldName == "skinOn" )
			return _skinOn.IsDerivedFromParent();
		if ( fieldName == "keys" )
			return _keys.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NScene::LightningSceneComponent", "LightningSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x3B61E441)]
[UseTypeName("LGSC")]
public class DBLightningSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBLightningSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBLightningSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<LightningMaterial> _material;
	private UndoRedo<string> _fromLocator;
	private UndoRedo<string> _toLocator;
	private DBLightningFXParams _fxParams;

	[Description( "LightningMaterial to use" )]
	public DBPtr<LightningMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	[Description( "The first locator name" )]
	public string fromLocator { get { return _fromLocator.Get(); } set { _fromLocator.Set( value ); } }

	[Description( "The second locator name" )]
	public string toLocator { get { return _toLocator.Get(); } set { _toLocator.Set( value ); } }

	[Description( "FX Parameters" )]
	public DBLightningFXParams fxParams { get { return _fxParams; } set { _fxParams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBLightningSceneComponent>(owner);
		_material = new UndoRedoDBPtr<LightningMaterial>( owner );
		_fromLocator = new UndoRedo<string>( owner, string.Empty );
		_toLocator = new UndoRedo<string>( owner, string.Empty );
		_fxParams = new DBLightningFXParams( owner );
		___parent.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
		_fromLocator.Changed += FireChangedEvent;
		_toLocator.Changed += FireChangedEvent;
		_fxParams.Changed += FireChangedEvent;
	}

	public DBLightningSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBLightningSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBLightningSceneComponent" );
		material = source.material;
		fromLocator = source.fromLocator;
		toLocator = source.toLocator;
		fxParams = source.fxParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBLightningSceneComponent source = _source as DBLightningSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLightningSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBLightningSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBLightningSceneComponent>();
		if ( newParent == null && _newParent is DBLightningSceneComponent )
			newParent = _newParent as DBLightningSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_material.SetParent( newParent == null ? null : newParent._material );
		_fromLocator.SetParent( newParent == null ? null : newParent._fromLocator );
		_toLocator.SetParent( newParent == null ? null : newParent._toLocator );
		_fxParams.SetParent( newParent == null ? null : newParent._fxParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_material.Reset();
		_fromLocator.Reset();
		_toLocator.Reset();
		_fxParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_material.IsDerivedFromParent()
			&& _fromLocator.IsDerivedFromParent()
			&& _toLocator.IsDerivedFromParent()
			&& _fxParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "material" )
			_material.Reset();
		else if ( fieldName == "fromLocator" )
			_fromLocator.Reset();
		else if ( fieldName == "toLocator" )
			_toLocator.Reset();
		else if ( fieldName == "fxParams" )
			_fxParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		if ( fieldName == "fromLocator" )
			return _fromLocator.IsDerivedFromParent();
		if ( fieldName == "toLocator" )
			return _toLocator.IsDerivedFromParent();
		if ( fieldName == "fxParams" )
			return _fxParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("SOBJ")]
public class DBSceneObject : DBSceneResource
{
	private UndoRedoDBPtr<DBSceneObject> ___parent;
	[HideInOutliner]
	public new DBPtr<DBSceneObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SceneObjectTracks> _tracksList;
	private UndoRedoDBPtr<CollisionGeometry> _collisionGeometry;
	private UndoRedo<bool> _ignoreAttachesToNonDefaultLocators;

	public DBPtr<SceneObjectTracks> tracksList { get { return _tracksList.Get(); } set { _tracksList.Set( value ); } }

	public DBPtr<CollisionGeometry> collisionGeometry { get { return _collisionGeometry.Get(); } set { _collisionGeometry.Set( value ); } }

	[Description( "Do not accept effect attaches to non-default locators" )]
	public bool ignoreAttachesToNonDefaultLocators { get { return _ignoreAttachesToNonDefaultLocators.Get(); } set { _ignoreAttachesToNonDefaultLocators.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBSceneObject>(owner);
		_tracksList = new UndoRedoDBPtr<SceneObjectTracks>( owner );
		_collisionGeometry = new UndoRedoDBPtr<CollisionGeometry>( owner );
		_ignoreAttachesToNonDefaultLocators = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_tracksList.Changed += FireChangedEvent;
		_collisionGeometry.Changed += FireChangedEvent;
		_ignoreAttachesToNonDefaultLocators.Changed += FireChangedEvent;
	}

	public DBSceneObject()
	{
		Initialize( this );
	}
	private void AssignSelf( DBSceneObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBSceneObject" );
		tracksList = source.tracksList;
		collisionGeometry = source.collisionGeometry;
		ignoreAttachesToNonDefaultLocators = source.ignoreAttachesToNonDefaultLocators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBSceneObject source = _source as DBSceneObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSceneObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBSceneObject newParent = rawParent == null ? null : rawParent.Get<DBSceneObject>();
		if ( newParent == null && _newParent is DBSceneObject )
			newParent = _newParent as DBSceneObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tracksList.SetParent( newParent == null ? null : newParent._tracksList );
		_collisionGeometry.SetParent( newParent == null ? null : newParent._collisionGeometry );
		_ignoreAttachesToNonDefaultLocators.SetParent( newParent == null ? null : newParent._ignoreAttachesToNonDefaultLocators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tracksList.Reset();
		_collisionGeometry.Reset();
		_ignoreAttachesToNonDefaultLocators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tracksList.IsDerivedFromParent()
			&& _collisionGeometry.IsDerivedFromParent()
			&& _ignoreAttachesToNonDefaultLocators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tracksList" )
			_tracksList.Reset();
		else if ( fieldName == "collisionGeometry" )
			_collisionGeometry.Reset();
		else if ( fieldName == "ignoreAttachesToNonDefaultLocators" )
			_ignoreAttachesToNonDefaultLocators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tracksList" )
			return _tracksList.IsDerivedFromParent();
		if ( fieldName == "collisionGeometry" )
			return _collisionGeometry.IsDerivedFromParent();
		if ( fieldName == "ignoreAttachesToNonDefaultLocators" )
			return _ignoreAttachesToNonDefaultLocators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NScene::ParticleSceneComponent", "ParticleSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x8D5A1243)]
[UseTypeName("PRSC")]
public class DBParticleSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBParticleSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBParticleSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _camoffset;
	private UndoRedo<EOrientType> _orient;
	private Vec2 _pivot;
	private UndoRedo<bool> _leaveParticlesWhereStarted;
	private UndoRedo<float> _deathFadeOutTime;
	private UndoRedoDBPtr<ParticleFXMaterial> _material;
	private UndoRedoAssignableList<SrcFile> _textures;
	private UndoRedoAssignableList<SrcFile> _normaltextures;
	private UndoRedoAssignableList<SrcFile> _speculartextures;
	private UndoRedoAssignableList<UVPair> _uvPairs;
	private AABB _aabb;
	private UndoRedo<float> _compression;
	private UndoRedo<string> _selection;
	private SrcFile _srcFileName;

	[Description( "Particle to camera offset" )]
	public float camoffset { get { return _camoffset.Get(); } set { _camoffset.Set( value ); } }

	[Description( "Is Oriented?" )]
	public EOrientType orient { get { return _orient.Get(); } set { _orient.Set( value ); } }

	[Description( "Particle pivot" )]
	public Vec2 pivot { get { return _pivot; } set { _pivot.Assign( value ); } }

	[Description( "Do we need particles be attached to it's source or leaved at birth place?" )]
	public bool leaveParticlesWhereStarted { get { return _leaveParticlesWhereStarted.Get(); } set { _leaveParticlesWhereStarted.Set( value ); } }

	[Description( "FadeOut time for dying particles with leaveParticlesWhereStarted = true" )]
	public float deathFadeOutTime { get { return _deathFadeOutTime.Get(); } set { _deathFadeOutTime.Set( value ); } }

	public DBPtr<ParticleFXMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	[NoCode]
	[SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
	public libdb.IChangeableList<SrcFile> textures { get { return _textures; } set { _textures.Assign( value ); } }

	[NoCode]
	[SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
	public libdb.IChangeableList<SrcFile> normaltextures { get { return _normaltextures; } set { _normaltextures.Assign( value ); } }

	[NoCode]
	[SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
	public libdb.IChangeableList<SrcFile> speculartextures { get { return _speculartextures; } set { _speculartextures.Assign( value ); } }

	public libdb.IChangeableList<UVPair> uvPairs { get { return _uvPairs; } set { _uvPairs.Assign( value ); } }

	public AABB aabb { get { return _aabb; } set { _aabb.Assign( value ); } }

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
	[NoCode]
	public float compression { get { return _compression.Get(); } set { _compression.Set( value ); } }

	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBParticleSceneComponent>(owner);
		_camoffset = new UndoRedo<float>( owner, 0.0f );
		_orient = new UndoRedo<EOrientType>( owner, EOrientType.None );
		_pivot = new Vec2( owner );
		_leaveParticlesWhereStarted = new UndoRedo<bool>( owner, false );
		_deathFadeOutTime = new UndoRedo<float>( owner, 0.5f );
		_material = new UndoRedoDBPtr<ParticleFXMaterial>( owner );
		_textures = new UndoRedoAssignableList<SrcFile>( owner );
		_normaltextures = new UndoRedoAssignableList<SrcFile>( owner );
		_speculartextures = new UndoRedoAssignableList<SrcFile>( owner );
		_uvPairs = new UndoRedoAssignableList<UVPair>( owner );
		AABB __aabb = new AABB(); // Construct default object for aabb
		__aabb.minX = 666.0f;
		__aabb.maxX = -666.0f;
		__aabb.minY = 666.0f;
		__aabb.maxY = -666.0f;
		__aabb.minZ = 666.0f;
		__aabb.maxZ = -666.0f;
		_aabb = new AABB( owner, __aabb );
		_compression = new UndoRedo<float>( owner, 2.0f );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_srcFileName = new SrcFile( owner, new SrcFile() );
		___parent.Changed += FireChangedEvent;
		_camoffset.Changed += FireChangedEvent;
		_orient.Changed += FireChangedEvent;
		_pivot.Changed += FireChangedEvent;
		_leaveParticlesWhereStarted.Changed += FireChangedEvent;
		_deathFadeOutTime.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
		_textures.Changed += FireChangedEvent;
		_normaltextures.Changed += FireChangedEvent;
		_speculartextures.Changed += FireChangedEvent;
		_uvPairs.Changed += FireChangedEvent;
		_aabb.Changed += FireChangedEvent;
		_compression.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
	}

	public DBParticleSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBParticleSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBParticleSceneComponent" );
		camoffset = source.camoffset;
		orient = source.orient;
		pivot = source.pivot;
		leaveParticlesWhereStarted = source.leaveParticlesWhereStarted;
		deathFadeOutTime = source.deathFadeOutTime;
		material = source.material;
		textures = source.textures;
		normaltextures = source.normaltextures;
		speculartextures = source.speculartextures;
		uvPairs = source.uvPairs;
		aabb = source.aabb;
		compression = source.compression;
		selection = source.selection;
		srcFileName = source.srcFileName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBParticleSceneComponent source = _source as DBParticleSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBParticleSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBParticleSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBParticleSceneComponent>();
		if ( newParent == null && _newParent is DBParticleSceneComponent )
			newParent = _newParent as DBParticleSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_camoffset.SetParent( newParent == null ? null : newParent._camoffset );
		_orient.SetParent( newParent == null ? null : newParent._orient );
		_pivot.SetParent( newParent == null ? null : newParent._pivot );
		_leaveParticlesWhereStarted.SetParent( newParent == null ? null : newParent._leaveParticlesWhereStarted );
		_deathFadeOutTime.SetParent( newParent == null ? null : newParent._deathFadeOutTime );
		_material.SetParent( newParent == null ? null : newParent._material );
		_textures.SetParent( newParent == null ? null : newParent._textures );
		_normaltextures.SetParent( newParent == null ? null : newParent._normaltextures );
		_speculartextures.SetParent( newParent == null ? null : newParent._speculartextures );
		_uvPairs.SetParent( newParent == null ? null : newParent._uvPairs );
		_aabb.SetParent( newParent == null ? null : newParent._aabb );
		_compression.SetParent( newParent == null ? null : newParent._compression );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_camoffset.Reset();
		_orient.Reset();
		_pivot.Reset();
		_leaveParticlesWhereStarted.Reset();
		_deathFadeOutTime.Reset();
		_material.Reset();
		_textures.Reset();
		_normaltextures.Reset();
		_speculartextures.Reset();
		_uvPairs.Reset();
		_aabb.Reset();
		_compression.Reset();
		_selection.Reset();
		_srcFileName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_camoffset.IsDerivedFromParent()
			&& _orient.IsDerivedFromParent()
			&& _pivot.IsDerivedFromParent()
			&& _leaveParticlesWhereStarted.IsDerivedFromParent()
			&& _deathFadeOutTime.IsDerivedFromParent()
			&& _material.IsDerivedFromParent()
			&& _textures.IsDerivedFromParent()
			&& _normaltextures.IsDerivedFromParent()
			&& _speculartextures.IsDerivedFromParent()
			&& _uvPairs.IsDerivedFromParent()
			&& _aabb.IsDerivedFromParent()
			&& _compression.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _srcFileName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "camoffset" )
			_camoffset.Reset();
		else if ( fieldName == "orient" )
			_orient.Reset();
		else if ( fieldName == "pivot" )
			_pivot.Reset();
		else if ( fieldName == "leaveParticlesWhereStarted" )
			_leaveParticlesWhereStarted.Reset();
		else if ( fieldName == "deathFadeOutTime" )
			_deathFadeOutTime.Reset();
		else if ( fieldName == "material" )
			_material.Reset();
		else if ( fieldName == "textures" )
			_textures.Reset();
		else if ( fieldName == "normaltextures" )
			_normaltextures.Reset();
		else if ( fieldName == "speculartextures" )
			_speculartextures.Reset();
		else if ( fieldName == "uvPairs" )
			_uvPairs.Reset();
		else if ( fieldName == "aabb" )
			_aabb.Reset();
		else if ( fieldName == "compression" )
			_compression.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "camoffset" )
			return _camoffset.IsDerivedFromParent();
		if ( fieldName == "orient" )
			return _orient.IsDerivedFromParent();
		if ( fieldName == "pivot" )
			return _pivot.IsDerivedFromParent();
		if ( fieldName == "leaveParticlesWhereStarted" )
			return _leaveParticlesWhereStarted.IsDerivedFromParent();
		if ( fieldName == "deathFadeOutTime" )
			return _deathFadeOutTime.IsDerivedFromParent();
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		if ( fieldName == "textures" )
			return _textures.IsDerivedFromParent();
		if ( fieldName == "normaltextures" )
			return _normaltextures.IsDerivedFromParent();
		if ( fieldName == "speculartextures" )
			return _speculartextures.IsDerivedFromParent();
		if ( fieldName == "uvPairs" )
			return _uvPairs.IsDerivedFromParent();
		if ( fieldName == "aabb" )
			return _aabb.IsDerivedFromParent();
		if ( fieldName == "compression" )
			return _compression.IsDerivedFromParent();
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "srcFileName" )
			return _srcFileName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NScene::SoundSceneComponent", "SoundSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x4D5B9BC0)]
[UseTypeName("SNSC")]
public class DBSoundSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBSoundSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBSoundSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private DBFMODEventDesc _desc;
	private UndoRedo<float> _timeInterval;

	[Description( "Sound event description" )]
	public DBFMODEventDesc desc { get { return _desc; } set { _desc.Assign( value ); } }

	[Description( "Sound will playing in this time interval" )]
	public float timeInterval { get { return _timeInterval.Get(); } set { _timeInterval.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBSoundSceneComponent>(owner);
		_desc = new DBFMODEventDesc( owner );
		_timeInterval = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_desc.Changed += FireChangedEvent;
		_timeInterval.Changed += FireChangedEvent;
	}

	public DBSoundSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBSoundSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBSoundSceneComponent" );
		desc = source.desc;
		timeInterval = source.timeInterval;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBSoundSceneComponent source = _source as DBSoundSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSoundSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBSoundSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBSoundSceneComponent>();
		if ( newParent == null && _newParent is DBSoundSceneComponent )
			newParent = _newParent as DBSoundSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_desc.SetParent( newParent == null ? null : newParent._desc );
		_timeInterval.SetParent( newParent == null ? null : newParent._timeInterval );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_desc.Reset();
		_timeInterval.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_desc.IsDerivedFromParent()
			&& _timeInterval.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "desc" )
			_desc.Reset();
		else if ( fieldName == "timeInterval" )
			_timeInterval.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "desc" )
			return _desc.IsDerivedFromParent();
		if ( fieldName == "timeInterval" )
			return _timeInterval.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NScene::StaticSceneComponent", "SceneObjectCreation.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x8D5A1242)]
[UseTypeName("STSC")]
public class DBStaticSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBStaticSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBStaticSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;
	private AABB _aabb;
	private UndoRedo<int> _uvSetCount;
	private UndoRedoAssignableList<DBPtr<Material>> _materialsReferences;

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

	[ReadOnly( true )]
	public AABB aabb { get { return _aabb; } set { _aabb.Assign( value ); } }

	[NoCode]
	public int uvSetCount { get { return _uvSetCount.Get(); } set { _uvSetCount.Set( value ); } }

	[Description( "List of materials" )]
	public libdb.IChangeableList<DBPtr<Material>> materialsReferences { get { return _materialsReferences; } set { _materialsReferences.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBStaticSceneComponent>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		_aabb = new AABB( owner );
		_uvSetCount = new UndoRedo<int>( owner, 1 );
		_materialsReferences = new UndoRedoAssignableList<DBPtr<Material>>( owner );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
		_aabb.Changed += FireChangedEvent;
		_uvSetCount.Changed += FireChangedEvent;
		_materialsReferences.Changed += FireChangedEvent;
	}

	public DBStaticSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBStaticSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBStaticSceneComponent" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		aabb = source.aabb;
		uvSetCount = source.uvSetCount;
		materialsReferences = source.materialsReferences;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBStaticSceneComponent source = _source as DBStaticSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBStaticSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBStaticSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBStaticSceneComponent>();
		if ( newParent == null && _newParent is DBStaticSceneComponent )
			newParent = _newParent as DBStaticSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		_aabb.SetParent( newParent == null ? null : newParent._aabb );
		_uvSetCount.SetParent( newParent == null ? null : newParent._uvSetCount );
		_materialsReferences.SetParent( newParent == null ? null : newParent._materialsReferences );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		_aabb.Reset();
		_uvSetCount.Reset();
		_materialsReferences.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& _aabb.IsDerivedFromParent()
			&& _uvSetCount.IsDerivedFromParent()
			&& _materialsReferences.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "aabb" )
			_aabb.Reset();
		else if ( fieldName == "uvSetCount" )
			_uvSetCount.Reset();
		else if ( fieldName == "materialsReferences" )
			_materialsReferences.Reset();
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
		if ( fieldName == "aabb" )
			return _aabb.IsDerivedFromParent();
		if ( fieldName == "uvSetCount" )
			return _uvSetCount.IsDerivedFromParent();
		if ( fieldName == "materialsReferences" )
			return _materialsReferences.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NScene::TraceSceneComponent", "TraceSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x3B6184C0)]
[UseTypeName("TRSC")]
public class DBTraceSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<DBTraceSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBTraceSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TraceMaterial> _material;
	private UndoRedo<string> _locator1Name;
	private UndoRedo<string> _locator2Name;
	private UndoRedo<float> _maxLength;
	private UndoRedo<float> _speedStart;
	private UndoRedo<float> _speedStop;
	private HDRColor _colorFirst;
	private HDRColor _colorLast;
	private UndoRedo<float> _offsetColor;
	private UndoRedo<float> _offsetAlpha;
	private UndoRedo<float> _fadeoutSpeed;
	private UndoRedo<float> _skewness;

	[Description( "TraceMaterial to use" )]
	public DBPtr<TraceMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	[Description( "The first locator name" )]
	public string locator1Name { get { return _locator1Name.Get(); } set { _locator1Name.Set( value ); } }

	[Description( "The second locator name" )]
	public string locator2Name { get { return _locator2Name.Get(); } set { _locator2Name.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Maximal trace length allowed, in meters" )]
	public float maxLength { get { return _maxLength.Get(); } set { _maxLength.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "When to start generating trace, in mps" )]
	public float speedStart { get { return _speedStart.Get(); } set { _speedStart.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "When to stop generating trace, in mps" )]
	public float speedStop { get { return _speedStop.Get(); } set { _speedStop.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Color of trace near the blade" )]
	public HDRColor colorFirst { get { return _colorFirst; } set { _colorFirst.Assign( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Color of trace to fade into" )]
	public HDRColor colorLast { get { return _colorLast; } set { _colorLast.Assign( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Delay for color interpolation, in 0..1" )]
	public float offsetColor { get { return _offsetColor.Get(); } set { _offsetColor.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Delay for transparency interpolation, in 0..1" )]
	public float offsetAlpha { get { return _offsetAlpha.Get(); } set { _offsetAlpha.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Fadeout speed, in mps" )]
	public float fadeoutSpeed { get { return _fadeoutSpeed.Get(); } set { _fadeoutSpeed.Set( value ); } }

	[Category( "Effect Parameters" )]
	[Description( "Coefficient of trace skewness, in 0..1" )]
	public float skewness { get { return _skewness.Get(); } set { _skewness.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBTraceSceneComponent>(owner);
		_material = new UndoRedoDBPtr<TraceMaterial>( owner );
		_locator1Name = new UndoRedo<string>( owner, string.Empty );
		_locator2Name = new UndoRedo<string>( owner, string.Empty );
		_maxLength = new UndoRedo<float>( owner, 1.0f );
		_speedStart = new UndoRedo<float>( owner, 10.0f );
		_speedStop = new UndoRedo<float>( owner, 2.0f );
		HDRColor __colorFirst = new HDRColor(); // Construct default object for colorFirst
		__colorFirst.R = 1.0f;
		__colorFirst.G = 1.0f;
		_colorFirst = new HDRColor( owner, __colorFirst );
		HDRColor __colorLast = new HDRColor(); // Construct default object for colorLast
		__colorLast.B = 1.0f;
		_colorLast = new HDRColor( owner, __colorLast );
		_offsetColor = new UndoRedo<float>( owner, 0.0f );
		_offsetAlpha = new UndoRedo<float>( owner, 0.0f );
		_fadeoutSpeed = new UndoRedo<float>( owner, 10.0f );
		_skewness = new UndoRedo<float>( owner, 0.5f );
		___parent.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
		_locator1Name.Changed += FireChangedEvent;
		_locator2Name.Changed += FireChangedEvent;
		_maxLength.Changed += FireChangedEvent;
		_speedStart.Changed += FireChangedEvent;
		_speedStop.Changed += FireChangedEvent;
		_colorFirst.Changed += FireChangedEvent;
		_colorLast.Changed += FireChangedEvent;
		_offsetColor.Changed += FireChangedEvent;
		_offsetAlpha.Changed += FireChangedEvent;
		_fadeoutSpeed.Changed += FireChangedEvent;
		_skewness.Changed += FireChangedEvent;
	}

	public DBTraceSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBTraceSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBTraceSceneComponent" );
		material = source.material;
		locator1Name = source.locator1Name;
		locator2Name = source.locator2Name;
		maxLength = source.maxLength;
		speedStart = source.speedStart;
		speedStop = source.speedStop;
		colorFirst = source.colorFirst;
		colorLast = source.colorLast;
		offsetColor = source.offsetColor;
		offsetAlpha = source.offsetAlpha;
		fadeoutSpeed = source.fadeoutSpeed;
		skewness = source.skewness;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBTraceSceneComponent source = _source as DBTraceSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBTraceSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBTraceSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBTraceSceneComponent>();
		if ( newParent == null && _newParent is DBTraceSceneComponent )
			newParent = _newParent as DBTraceSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_material.SetParent( newParent == null ? null : newParent._material );
		_locator1Name.SetParent( newParent == null ? null : newParent._locator1Name );
		_locator2Name.SetParent( newParent == null ? null : newParent._locator2Name );
		_maxLength.SetParent( newParent == null ? null : newParent._maxLength );
		_speedStart.SetParent( newParent == null ? null : newParent._speedStart );
		_speedStop.SetParent( newParent == null ? null : newParent._speedStop );
		_colorFirst.SetParent( newParent == null ? null : newParent._colorFirst );
		_colorLast.SetParent( newParent == null ? null : newParent._colorLast );
		_offsetColor.SetParent( newParent == null ? null : newParent._offsetColor );
		_offsetAlpha.SetParent( newParent == null ? null : newParent._offsetAlpha );
		_fadeoutSpeed.SetParent( newParent == null ? null : newParent._fadeoutSpeed );
		_skewness.SetParent( newParent == null ? null : newParent._skewness );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_material.Reset();
		_locator1Name.Reset();
		_locator2Name.Reset();
		_maxLength.Reset();
		_speedStart.Reset();
		_speedStop.Reset();
		_colorFirst.Reset();
		_colorLast.Reset();
		_offsetColor.Reset();
		_offsetAlpha.Reset();
		_fadeoutSpeed.Reset();
		_skewness.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_material.IsDerivedFromParent()
			&& _locator1Name.IsDerivedFromParent()
			&& _locator2Name.IsDerivedFromParent()
			&& _maxLength.IsDerivedFromParent()
			&& _speedStart.IsDerivedFromParent()
			&& _speedStop.IsDerivedFromParent()
			&& _colorFirst.IsDerivedFromParent()
			&& _colorLast.IsDerivedFromParent()
			&& _offsetColor.IsDerivedFromParent()
			&& _offsetAlpha.IsDerivedFromParent()
			&& _fadeoutSpeed.IsDerivedFromParent()
			&& _skewness.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "material" )
			_material.Reset();
		else if ( fieldName == "locator1Name" )
			_locator1Name.Reset();
		else if ( fieldName == "locator2Name" )
			_locator2Name.Reset();
		else if ( fieldName == "maxLength" )
			_maxLength.Reset();
		else if ( fieldName == "speedStart" )
			_speedStart.Reset();
		else if ( fieldName == "speedStop" )
			_speedStop.Reset();
		else if ( fieldName == "colorFirst" )
			_colorFirst.Reset();
		else if ( fieldName == "colorLast" )
			_colorLast.Reset();
		else if ( fieldName == "offsetColor" )
			_offsetColor.Reset();
		else if ( fieldName == "offsetAlpha" )
			_offsetAlpha.Reset();
		else if ( fieldName == "fadeoutSpeed" )
			_fadeoutSpeed.Reset();
		else if ( fieldName == "skewness" )
			_skewness.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		if ( fieldName == "locator1Name" )
			return _locator1Name.IsDerivedFromParent();
		if ( fieldName == "locator2Name" )
			return _locator2Name.IsDerivedFromParent();
		if ( fieldName == "maxLength" )
			return _maxLength.IsDerivedFromParent();
		if ( fieldName == "speedStart" )
			return _speedStart.IsDerivedFromParent();
		if ( fieldName == "speedStop" )
			return _speedStop.IsDerivedFromParent();
		if ( fieldName == "colorFirst" )
			return _colorFirst.IsDerivedFromParent();
		if ( fieldName == "colorLast" )
			return _colorLast.IsDerivedFromParent();
		if ( fieldName == "offsetColor" )
			return _offsetColor.IsDerivedFromParent();
		if ( fieldName == "offsetAlpha" )
			return _offsetAlpha.IsDerivedFromParent();
		if ( fieldName == "fadeoutSpeed" )
			return _fadeoutSpeed.IsDerivedFromParent();
		if ( fieldName == "skewness" )
			return _skewness.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x3B622C41)]
[UseTypeName("WAIN")]
public class DBWaterInfo : DBResource
{
	private UndoRedoDBPtr<DBWaterInfo> ___parent;
	[HideInOutliner]
	public new DBPtr<DBWaterInfo> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _tiling;
	private UndoRedo<float> _shininess;
	private UndoRedo<float> _ripples;
	private UndoRedo<float> _ripplesHeight;
	private UndoRedo<float> _distance;
	private UndoRedo<float> _refraction;
	private UndoRedo<float> _depth;
	private UndoRedo<float> _depthReflect;
	private Vec2 _speed;
	private UndoRedo<float> _causticsTiling;
	private UndoRedo<float> _causticsIntensity;
	private UndoRedoDBPtr<Texture> _gradientMap;
	private UndoRedoDBPtr<Texture> _causticsMap;

	[Description( "Ripples texture tiling. Increase to make ripples smaller in size." )]
	public float tiling { get { return _tiling.Get(); } set { _tiling.Set( value ); } }

	[Description( "Shininess controls reflections. Decrease to make more reflective, even from above." )]
	public float shininess { get { return _shininess.Get(); } set { _shininess.Set( value ); } }

	[Description( "Increase to make ripples (waves) harder." )]
	public float ripples { get { return _ripples.Get(); } set { _ripples.Set( value ); } }

	[Description( "Increase to make ripples (waves) higher. Most obvious at border." )]
	public float ripplesHeight { get { return _ripplesHeight.Get(); } set { _ripplesHeight.Set( value ); } }

	[Description( "Controls 'fog'. Distance at which bottom color is faded twice, in meters." )]
	public float distance { get { return _distance.Get(); } set { _distance.Set( value ); } }

	[Description( "=NOT USED YET=" )]
	public float refraction { get { return _refraction.Get(); } set { _refraction.Set( value ); } }

	[Description( "Water depth for gradient texture mapping, in meters." )]
	public float depth { get { return _depth.Get(); } set { _depth.Set( value ); } }

	[Description( "Water depth for reflections to appear, in meters." )]
	public float depthReflect { get { return _depthReflect.Get(); } set { _depthReflect.Set( value ); } }

	[Description( "Speed and direction of river current (texture scrolling)." )]
	public Vec2 speed { get { return _speed; } set { _speed.Assign( value ); } }

	[Description( "Caustics texture tiling. Increase to make ripples smaller in size." )]
	public float causticsTiling { get { return _causticsTiling.Get(); } set { _causticsTiling.Set( value ); } }

	[Description( "Caustics texture intensity multiplier." )]
	public float causticsIntensity { get { return _causticsIntensity.Get(); } set { _causticsIntensity.Set( value ); } }

	public DBPtr<Texture> gradientMap { get { return _gradientMap.Get(); } set { _gradientMap.Set( value ); } }

	public DBPtr<Texture> causticsMap { get { return _causticsMap.Get(); } set { _causticsMap.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBWaterInfo>(owner);
		_tiling = new UndoRedo<float>( owner, 2.0f );
		_shininess = new UndoRedo<float>( owner, 4.0f );
		_ripples = new UndoRedo<float>( owner, 1.0f );
		_ripplesHeight = new UndoRedo<float>( owner, 0.1f );
		_distance = new UndoRedo<float>( owner, 5.0f );
		_refraction = new UndoRedo<float>( owner, 1.05f );
		_depth = new UndoRedo<float>( owner, 10.0f );
		_depthReflect = new UndoRedo<float>( owner, 0.0f );
		_speed = new Vec2( owner );
		_causticsTiling = new UndoRedo<float>( owner, 2.0f );
		_causticsIntensity = new UndoRedo<float>( owner, 1.0f );
		_gradientMap = new UndoRedoDBPtr<Texture>( owner );
		_causticsMap = new UndoRedoDBPtr<Texture>( owner );
		___parent.Changed += FireChangedEvent;
		_tiling.Changed += FireChangedEvent;
		_shininess.Changed += FireChangedEvent;
		_ripples.Changed += FireChangedEvent;
		_ripplesHeight.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
		_refraction.Changed += FireChangedEvent;
		_depth.Changed += FireChangedEvent;
		_depthReflect.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_causticsTiling.Changed += FireChangedEvent;
		_causticsIntensity.Changed += FireChangedEvent;
		_gradientMap.Changed += FireChangedEvent;
		_causticsMap.Changed += FireChangedEvent;
	}

	public DBWaterInfo()
	{
		Initialize( this );
	}
	private void AssignSelf( DBWaterInfo source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBWaterInfo" );
		tiling = source.tiling;
		shininess = source.shininess;
		ripples = source.ripples;
		ripplesHeight = source.ripplesHeight;
		distance = source.distance;
		refraction = source.refraction;
		depth = source.depth;
		depthReflect = source.depthReflect;
		speed = source.speed;
		causticsTiling = source.causticsTiling;
		causticsIntensity = source.causticsIntensity;
		gradientMap = source.gradientMap;
		causticsMap = source.causticsMap;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBWaterInfo source = _source as DBWaterInfo;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBWaterInfo" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBWaterInfo newParent = rawParent == null ? null : rawParent.Get<DBWaterInfo>();
		if ( newParent == null && _newParent is DBWaterInfo )
			newParent = _newParent as DBWaterInfo;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tiling.SetParent( newParent == null ? null : newParent._tiling );
		_shininess.SetParent( newParent == null ? null : newParent._shininess );
		_ripples.SetParent( newParent == null ? null : newParent._ripples );
		_ripplesHeight.SetParent( newParent == null ? null : newParent._ripplesHeight );
		_distance.SetParent( newParent == null ? null : newParent._distance );
		_refraction.SetParent( newParent == null ? null : newParent._refraction );
		_depth.SetParent( newParent == null ? null : newParent._depth );
		_depthReflect.SetParent( newParent == null ? null : newParent._depthReflect );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_causticsTiling.SetParent( newParent == null ? null : newParent._causticsTiling );
		_causticsIntensity.SetParent( newParent == null ? null : newParent._causticsIntensity );
		_gradientMap.SetParent( newParent == null ? null : newParent._gradientMap );
		_causticsMap.SetParent( newParent == null ? null : newParent._causticsMap );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tiling.Reset();
		_shininess.Reset();
		_ripples.Reset();
		_ripplesHeight.Reset();
		_distance.Reset();
		_refraction.Reset();
		_depth.Reset();
		_depthReflect.Reset();
		_speed.Reset();
		_causticsTiling.Reset();
		_causticsIntensity.Reset();
		_gradientMap.Reset();
		_causticsMap.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tiling.IsDerivedFromParent()
			&& _shininess.IsDerivedFromParent()
			&& _ripples.IsDerivedFromParent()
			&& _ripplesHeight.IsDerivedFromParent()
			&& _distance.IsDerivedFromParent()
			&& _refraction.IsDerivedFromParent()
			&& _depth.IsDerivedFromParent()
			&& _depthReflect.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _causticsTiling.IsDerivedFromParent()
			&& _causticsIntensity.IsDerivedFromParent()
			&& _gradientMap.IsDerivedFromParent()
			&& _causticsMap.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tiling" )
			_tiling.Reset();
		else if ( fieldName == "shininess" )
			_shininess.Reset();
		else if ( fieldName == "ripples" )
			_ripples.Reset();
		else if ( fieldName == "ripplesHeight" )
			_ripplesHeight.Reset();
		else if ( fieldName == "distance" )
			_distance.Reset();
		else if ( fieldName == "refraction" )
			_refraction.Reset();
		else if ( fieldName == "depth" )
			_depth.Reset();
		else if ( fieldName == "depthReflect" )
			_depthReflect.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "causticsTiling" )
			_causticsTiling.Reset();
		else if ( fieldName == "causticsIntensity" )
			_causticsIntensity.Reset();
		else if ( fieldName == "gradientMap" )
			_gradientMap.Reset();
		else if ( fieldName == "causticsMap" )
			_causticsMap.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tiling" )
			return _tiling.IsDerivedFromParent();
		if ( fieldName == "shininess" )
			return _shininess.IsDerivedFromParent();
		if ( fieldName == "ripples" )
			return _ripples.IsDerivedFromParent();
		if ( fieldName == "ripplesHeight" )
			return _ripplesHeight.IsDerivedFromParent();
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		if ( fieldName == "refraction" )
			return _refraction.IsDerivedFromParent();
		if ( fieldName == "depth" )
			return _depth.IsDerivedFromParent();
		if ( fieldName == "depthReflect" )
			return _depthReflect.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "causticsTiling" )
			return _causticsTiling.IsDerivedFromParent();
		if ( fieldName == "causticsIntensity" )
			return _causticsIntensity.IsDerivedFromParent();
		if ( fieldName == "gradientMap" )
			return _gradientMap.IsDerivedFromParent();
		if ( fieldName == "causticsMap" )
			return _causticsMap.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NScene::WaterSceneComponent", "WaterSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x3B622C40)]
[UseTypeName("WASC")]
public class DBWaterSceneComponent : DBStaticSceneComponent
{
	private UndoRedoDBPtr<DBWaterSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<DBWaterSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBWaterInfo> _water;
	private UndoRedo<float> _waterLevel;

	[Category( "Water Settings" )]
	public DBPtr<DBWaterInfo> water { get { return _water.Get(); } set { _water.Set( value ); } }

	[Category( "Water Settings" )]
	[ReadOnly( true )]
	public float waterLevel { get { return _waterLevel.Get(); } set { _waterLevel.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBWaterSceneComponent>(owner);
		_water = new UndoRedoDBPtr<DBWaterInfo>( owner );
		_waterLevel = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_water.Changed += FireChangedEvent;
		_waterLevel.Changed += FireChangedEvent;
	}

	public DBWaterSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( DBWaterSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBWaterSceneComponent" );
		water = source.water;
		waterLevel = source.waterLevel;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBWaterSceneComponent source = _source as DBWaterSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBWaterSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBWaterSceneComponent newParent = rawParent == null ? null : rawParent.Get<DBWaterSceneComponent>();
		if ( newParent == null && _newParent is DBWaterSceneComponent )
			newParent = _newParent as DBWaterSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_water.SetParent( newParent == null ? null : newParent._water );
		_waterLevel.SetParent( newParent == null ? null : newParent._waterLevel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_water.Reset();
		_waterLevel.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_water.IsDerivedFromParent()
			&& _waterLevel.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "water" )
			_water.Reset();
		else if ( fieldName == "waterLevel" )
			_waterLevel.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "water" )
			return _water.IsDerivedFromParent();
		if ( fieldName == "waterLevel" )
			return _waterLevel.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E64AA80)]
[UseTypeName("EDEV")]
public class EnableDisableSCEvents : DBResource
{
	private UndoRedoDBPtr<EnableDisableSCEvents> ___parent;
	[HideInOutliner]
	public new DBPtr<EnableDisableSCEvents> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EEnableDisableOrder> _order;
	private UndoRedo<bool> _restartComponent;
	private UndoRedoAssignableList<DBPtr<SCEvent>> _enableEvents;
	private UndoRedoAssignableList<DBPtr<SCEvent>> _disableEvents;

	[Description( "Order of component enabling/disabling. When component is enabled-then-disabled, it will be disabled on start." )]
	public EEnableDisableOrder order { get { return _order.Get(); } set { _order.Set( value ); } }

	[Description( "Forces component to reinit on enable & deinit on disable" )]
	public bool restartComponent { get { return _restartComponent.Get(); } set { _restartComponent.Set( value ); } }

	[Description( "List of enable events" )]
	public libdb.IChangeableList<DBPtr<SCEvent>> enableEvents { get { return _enableEvents; } set { _enableEvents.Assign( value ); } }

	[Description( "List of disable events" )]
	public libdb.IChangeableList<DBPtr<SCEvent>> disableEvents { get { return _disableEvents; } set { _disableEvents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EnableDisableSCEvents>(owner);
		_order = new UndoRedo<EEnableDisableOrder>( owner, EEnableDisableOrder.EnableThenDisable );
		_restartComponent = new UndoRedo<bool>( owner, true );
		_enableEvents = new UndoRedoAssignableList<DBPtr<SCEvent>>( owner );
		_disableEvents = new UndoRedoAssignableList<DBPtr<SCEvent>>( owner );
		___parent.Changed += FireChangedEvent;
		_order.Changed += FireChangedEvent;
		_restartComponent.Changed += FireChangedEvent;
		_enableEvents.Changed += FireChangedEvent;
		_disableEvents.Changed += FireChangedEvent;
	}

	public EnableDisableSCEvents()
	{
		Initialize( this );
	}
	private void AssignSelf( EnableDisableSCEvents source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EnableDisableSCEvents" );
		order = source.order;
		restartComponent = source.restartComponent;
		enableEvents = source.enableEvents;
		disableEvents = source.disableEvents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EnableDisableSCEvents source = _source as EnableDisableSCEvents;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EnableDisableSCEvents" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EnableDisableSCEvents newParent = rawParent == null ? null : rawParent.Get<EnableDisableSCEvents>();
		if ( newParent == null && _newParent is EnableDisableSCEvents )
			newParent = _newParent as EnableDisableSCEvents;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_order.SetParent( newParent == null ? null : newParent._order );
		_restartComponent.SetParent( newParent == null ? null : newParent._restartComponent );
		_enableEvents.SetParent( newParent == null ? null : newParent._enableEvents );
		_disableEvents.SetParent( newParent == null ? null : newParent._disableEvents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_order.Reset();
		_restartComponent.Reset();
		_enableEvents.Reset();
		_disableEvents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_order.IsDerivedFromParent()
			&& _restartComponent.IsDerivedFromParent()
			&& _enableEvents.IsDerivedFromParent()
			&& _disableEvents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "order" )
			_order.Reset();
		else if ( fieldName == "restartComponent" )
			_restartComponent.Reset();
		else if ( fieldName == "enableEvents" )
			_enableEvents.Reset();
		else if ( fieldName == "disableEvents" )
			_disableEvents.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "order" )
			return _order.IsDerivedFromParent();
		if ( fieldName == "restartComponent" )
			return _restartComponent.IsDerivedFromParent();
		if ( fieldName == "enableEvents" )
			return _enableEvents.IsDerivedFromParent();
		if ( fieldName == "disableEvents" )
			return _disableEvents.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9D759480)]
[UseTypeName("EDEV")]
public class EnableDisableSkinEvents : DBResource
{
	private UndoRedoDBPtr<EnableDisableSkinEvents> ___parent;
	[HideInOutliner]
	public new DBPtr<EnableDisableSkinEvents> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EEnableDisableOrder> _order;
	private UndoRedoAssignableList<DBPtr<SCEvent>> _enableEvents;
	private UndoRedoAssignableList<DBPtr<SCEvent>> _disableEvents;

	[Description( "Order of component enabling/disabling. When component is enabled-then-disabled, it will be disabled on start." )]
	public EEnableDisableOrder order { get { return _order.Get(); } set { _order.Set( value ); } }

	[Description( "List of enable events" )]
	public libdb.IChangeableList<DBPtr<SCEvent>> enableEvents { get { return _enableEvents; } set { _enableEvents.Assign( value ); } }

	[Description( "List of disable events" )]
	public libdb.IChangeableList<DBPtr<SCEvent>> disableEvents { get { return _disableEvents; } set { _disableEvents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EnableDisableSkinEvents>(owner);
		_order = new UndoRedo<EEnableDisableOrder>( owner, EEnableDisableOrder.EnableThenDisable );
		_enableEvents = new UndoRedoAssignableList<DBPtr<SCEvent>>( owner );
		_disableEvents = new UndoRedoAssignableList<DBPtr<SCEvent>>( owner );
		___parent.Changed += FireChangedEvent;
		_order.Changed += FireChangedEvent;
		_enableEvents.Changed += FireChangedEvent;
		_disableEvents.Changed += FireChangedEvent;
	}

	public EnableDisableSkinEvents()
	{
		Initialize( this );
	}
	private void AssignSelf( EnableDisableSkinEvents source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EnableDisableSkinEvents" );
		order = source.order;
		enableEvents = source.enableEvents;
		disableEvents = source.disableEvents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EnableDisableSkinEvents source = _source as EnableDisableSkinEvents;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EnableDisableSkinEvents" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EnableDisableSkinEvents newParent = rawParent == null ? null : rawParent.Get<EnableDisableSkinEvents>();
		if ( newParent == null && _newParent is EnableDisableSkinEvents )
			newParent = _newParent as EnableDisableSkinEvents;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_order.SetParent( newParent == null ? null : newParent._order );
		_enableEvents.SetParent( newParent == null ? null : newParent._enableEvents );
		_disableEvents.SetParent( newParent == null ? null : newParent._disableEvents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_order.Reset();
		_enableEvents.Reset();
		_disableEvents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_order.IsDerivedFromParent()
			&& _enableEvents.IsDerivedFromParent()
			&& _disableEvents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "order" )
			_order.Reset();
		else if ( fieldName == "enableEvents" )
			_enableEvents.Reset();
		else if ( fieldName == "disableEvents" )
			_disableEvents.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "order" )
			return _order.IsDerivedFromParent();
		if ( fieldName == "enableEvents" )
			return _enableEvents.IsDerivedFromParent();
		if ( fieldName == "disableEvents" )
			return _disableEvents.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E6433C3)]
public class GroundHitSCEvent : SCEvent
{
	private UndoRedoDBPtr<GroundHitSCEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<GroundHitSCEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _heightAboveGround;

	[Description( "Event will be triggered when height of the component above ground reach this value" )]
	public float heightAboveGround { get { return _heightAboveGround.Get(); } set { _heightAboveGround.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GroundHitSCEvent>(owner);
		_heightAboveGround = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_heightAboveGround.Changed += FireChangedEvent;
	}

	public GroundHitSCEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( GroundHitSCEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GroundHitSCEvent" );
		heightAboveGround = source.heightAboveGround;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GroundHitSCEvent source = _source as GroundHitSCEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GroundHitSCEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GroundHitSCEvent newParent = rawParent == null ? null : rawParent.Get<GroundHitSCEvent>();
		if ( newParent == null && _newParent is GroundHitSCEvent )
			newParent = _newParent as GroundHitSCEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heightAboveGround.SetParent( newParent == null ? null : newParent._heightAboveGround );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heightAboveGround.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heightAboveGround.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heightAboveGround" )
			_heightAboveGround.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heightAboveGround" )
			return _heightAboveGround.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x146AAB40)]
[UseTypeName("LOLS")]
public class LocatorList : DBResource
{
	private UndoRedoDBPtr<LocatorList> ___parent;
	[HideInOutliner]
	public new DBPtr<LocatorList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Locator> _locators;

	[Description( "List of locators" )]
	public libdb.IChangeableList<Locator> locators { get { return _locators; } set { _locators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LocatorList>(owner);
		_locators = new UndoRedoAssignableList<Locator>( owner );
		___parent.Changed += FireChangedEvent;
		_locators.Changed += FireChangedEvent;
	}

	public LocatorList()
	{
		Initialize( this );
	}
	private void AssignSelf( LocatorList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LocatorList" );
		locators = source.locators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LocatorList source = _source as LocatorList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LocatorList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LocatorList newParent = rawParent == null ? null : rawParent.Get<LocatorList>();
		if ( newParent == null && _newParent is LocatorList )
			newParent = _newParent as LocatorList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_locators.SetParent( newParent == null ? null : newParent._locators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_locators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_locators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "locators" )
			_locators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "locators" )
			return _locators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xA06A4B80)]
public class NamedSCEvent : SCEvent
{
	private UndoRedoDBPtr<NamedSCEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<NamedSCEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;

	[Description( "Event name" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NamedSCEvent>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public NamedSCEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( NamedSCEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NamedSCEvent" );
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NamedSCEvent source = _source as NamedSCEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NamedSCEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NamedSCEvent newParent = rawParent == null ? null : rawParent.Get<NamedSCEvent>();
		if ( newParent == null && _newParent is NamedSCEvent )
			newParent = _newParent as NamedSCEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("name")]
[UseTypeName("SOTRACK")]
public class SceneObjectTrack : DBResource
{
	private UndoRedoDBPtr<SceneObjectTrack> ___parent;
	[HideInOutliner]
	public new DBPtr<SceneObjectTrack> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AnimatedPlacement _placement;
	private AnimatedFloat _opacity;
	private UndoRedo<string> _name;

	public AnimatedPlacement placement { get { return _placement; } set { _placement.Assign( value ); } }

	public AnimatedFloat opacity { get { return _opacity; } set { _opacity.Assign( value ); } }

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SceneObjectTrack>(owner);
		_placement = new AnimatedPlacement( owner );
		_opacity = new AnimatedFloat( owner, 1.0f );
		_name = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_placement.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public SceneObjectTrack()
	{
		Initialize( this );
	}
	private void AssignSelf( SceneObjectTrack source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectTrack" );
		placement = source.placement;
		opacity = source.opacity;
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SceneObjectTrack source = _source as SceneObjectTrack;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectTrack" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SceneObjectTrack newParent = rawParent == null ? null : rawParent.Get<SceneObjectTrack>();
		if ( newParent == null && _newParent is SceneObjectTrack )
			newParent = _newParent as SceneObjectTrack;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_placement.SetParent( newParent == null ? null : newParent._placement );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_placement.Reset();
		_opacity.Reset();
		_name.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_placement.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "placement" )
			_placement.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "placement" )
			return _placement.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("SOTRACKS")]
public class SceneObjectTracks : DBResource
{
	private UndoRedoDBPtr<SceneObjectTracks> ___parent;
	[HideInOutliner]
	public new DBPtr<SceneObjectTracks> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<SceneObjectTrack>> _animatedTracks;

	public libdb.IChangeableList<DBPtr<SceneObjectTrack>> animatedTracks { get { return _animatedTracks; } set { _animatedTracks.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SceneObjectTracks>(owner);
		_animatedTracks = new UndoRedoAssignableList<DBPtr<SceneObjectTrack>>( owner );
		___parent.Changed += FireChangedEvent;
		_animatedTracks.Changed += FireChangedEvent;
	}

	public SceneObjectTracks()
	{
		Initialize( this );
	}
	private void AssignSelf( SceneObjectTracks source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectTracks" );
		animatedTracks = source.animatedTracks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SceneObjectTracks source = _source as SceneObjectTracks;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectTracks" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SceneObjectTracks newParent = rawParent == null ? null : rawParent.Get<SceneObjectTracks>();
		if ( newParent == null && _newParent is SceneObjectTracks )
			newParent = _newParent as SceneObjectTracks;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_animatedTracks.SetParent( newParent == null ? null : newParent._animatedTracks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_animatedTracks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_animatedTracks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "animatedTracks" )
			_animatedTracks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "animatedTracks" )
			return _animatedTracks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E6433C2)]
public class AnimationSCEvent : SCEvent
{
	private UndoRedoDBPtr<AnimationSCEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<AnimationSCEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAnimEventType> _type;
	private UndoRedo<string> _name;
	private UndoRedo<float> _animParam;
	private UndoRedo<float> _probability;

	[Description( "Type of event" )]
	public EAnimEventType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[AnimationScEventSelector]
	[Description( "Name of animation sequence or marker" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[Description( "Animation parameter [0..1]" )]
	public float animParam { get { return _animParam.Get(); } set { _animParam.Set( value ); } }

	[Description( "Probability in per cent[0..100]" )]
	public float probability { get { return _probability.Get(); } set { _probability.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AnimationSCEvent>(owner);
		_type = new UndoRedo<EAnimEventType>( owner, EAnimEventType.NodeParam );
		_name = new UndoRedo<string>( owner, string.Empty );
		_animParam = new UndoRedo<float>( owner, 0.0f );
		_probability = new UndoRedo<float>( owner, 100.0f );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_animParam.Changed += FireChangedEvent;
		_probability.Changed += FireChangedEvent;
	}

	public AnimationSCEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( AnimationSCEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AnimationSCEvent" );
		type = source.type;
		name = source.name;
		animParam = source.animParam;
		probability = source.probability;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AnimationSCEvent source = _source as AnimationSCEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimationSCEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AnimationSCEvent newParent = rawParent == null ? null : rawParent.Get<AnimationSCEvent>();
		if ( newParent == null && _newParent is AnimationSCEvent )
			newParent = _newParent as AnimationSCEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		_name.SetParent( newParent == null ? null : newParent._name );
		_animParam.SetParent( newParent == null ? null : newParent._animParam );
		_probability.SetParent( newParent == null ? null : newParent._probability );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		_name.Reset();
		_animParam.Reset();
		_probability.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _animParam.IsDerivedFromParent()
			&& _probability.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "animParam" )
			_animParam.Reset();
		else if ( fieldName == "probability" )
			_probability.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "animParam" )
			return _animParam.IsDerivedFromParent();
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E647A80)]
public class TimeController : DBResource
{
	private UndoRedoDBPtr<TimeController> ___parent;
	[HideInOutliner]
	public new DBPtr<TimeController> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _speed;
	private UndoRedo<float> _startDelay;
	private UndoRedo<float> _firstCycleOffset;
	private UndoRedo<float> _firstCycleOffsetDelta;
	private UndoRedo<float> _cycleLength;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<float> _fadein;
	private UndoRedo<float> _fadeout;

	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	public float startDelay { get { return _startDelay.Get(); } set { _startDelay.Set( value ); } }

	public float firstCycleOffset { get { return _firstCycleOffset.Get(); } set { _firstCycleOffset.Set( value ); } }

	public float firstCycleOffsetDelta { get { return _firstCycleOffsetDelta.Get(); } set { _firstCycleOffsetDelta.Set( value ); } }

	public float cycleLength { get { return _cycleLength.Get(); } set { _cycleLength.Set( value ); } }

	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	public float fadein { get { return _fadein.Get(); } set { _fadein.Set( value ); } }

	public float fadeout { get { return _fadeout.Get(); } set { _fadeout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TimeController>(owner);
		_speed = new UndoRedo<float>( owner, 1.0f );
		_startDelay = new UndoRedo<float>( owner, 0.0f );
		_firstCycleOffset = new UndoRedo<float>( owner, 0.0f );
		_firstCycleOffsetDelta = new UndoRedo<float>( owner, 0.0f );
		_cycleLength = new UndoRedo<float>( owner, 0.0f );
		_cycleCount = new UndoRedo<int>( owner, 1 );
		_fadein = new UndoRedo<float>( owner, 0.0f );
		_fadeout = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_startDelay.Changed += FireChangedEvent;
		_firstCycleOffset.Changed += FireChangedEvent;
		_firstCycleOffsetDelta.Changed += FireChangedEvent;
		_cycleLength.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_fadein.Changed += FireChangedEvent;
		_fadeout.Changed += FireChangedEvent;
	}

	public TimeController()
	{
		Initialize( this );
	}
	private void AssignSelf( TimeController source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TimeController" );
		speed = source.speed;
		startDelay = source.startDelay;
		firstCycleOffset = source.firstCycleOffset;
		firstCycleOffsetDelta = source.firstCycleOffsetDelta;
		cycleLength = source.cycleLength;
		cycleCount = source.cycleCount;
		fadein = source.fadein;
		fadeout = source.fadeout;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TimeController source = _source as TimeController;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TimeController" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TimeController newParent = rawParent == null ? null : rawParent.Get<TimeController>();
		if ( newParent == null && _newParent is TimeController )
			newParent = _newParent as TimeController;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_speed.SetParent( newParent == null ? null : newParent._speed );
		_startDelay.SetParent( newParent == null ? null : newParent._startDelay );
		_firstCycleOffset.SetParent( newParent == null ? null : newParent._firstCycleOffset );
		_firstCycleOffsetDelta.SetParent( newParent == null ? null : newParent._firstCycleOffsetDelta );
		_cycleLength.SetParent( newParent == null ? null : newParent._cycleLength );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_fadein.SetParent( newParent == null ? null : newParent._fadein );
		_fadeout.SetParent( newParent == null ? null : newParent._fadeout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_speed.Reset();
		_startDelay.Reset();
		_firstCycleOffset.Reset();
		_firstCycleOffsetDelta.Reset();
		_cycleLength.Reset();
		_cycleCount.Reset();
		_fadein.Reset();
		_fadeout.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_speed.IsDerivedFromParent()
			&& _startDelay.IsDerivedFromParent()
			&& _firstCycleOffset.IsDerivedFromParent()
			&& _firstCycleOffsetDelta.IsDerivedFromParent()
			&& _cycleLength.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _fadein.IsDerivedFromParent()
			&& _fadeout.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "startDelay" )
			_startDelay.Reset();
		else if ( fieldName == "firstCycleOffset" )
			_firstCycleOffset.Reset();
		else if ( fieldName == "firstCycleOffsetDelta" )
			_firstCycleOffsetDelta.Reset();
		else if ( fieldName == "cycleLength" )
			_cycleLength.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "fadein" )
			_fadein.Reset();
		else if ( fieldName == "fadeout" )
			_fadeout.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "startDelay" )
			return _startDelay.IsDerivedFromParent();
		if ( fieldName == "firstCycleOffset" )
			return _firstCycleOffset.IsDerivedFromParent();
		if ( fieldName == "firstCycleOffsetDelta" )
			return _firstCycleOffsetDelta.IsDerivedFromParent();
		if ( fieldName == "cycleLength" )
			return _cycleLength.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "fadein" )
			return _fadein.IsDerivedFromParent();
		if ( fieldName == "fadeout" )
			return _fadeout.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
