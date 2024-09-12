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
public enum ELocatorAttachFlags
{
	None = 0,
	UseJointScale = 1,
	UseJointRotation = 2,
	UseJointPosition = 4,
	CancelNormalLevelling = 8,
};

public class AnimFaceFXKey : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimFaceFXKey __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _startTime;
	private UndoRedo<int> _animation;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<string> _facefxname;

	public float startTime { get { return _startTime.Get(); } set { _startTime.Set( value ); } }

	public int animation { get { return _animation.Get(); } set { _animation.Set( value ); } }

	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	public string facefxname { get { return _facefxname.Get(); } set { _facefxname.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_startTime = new UndoRedo<float>( owner, 0.0f );
		_animation = new UndoRedo<int>( owner, 0 );
		_cycleCount = new UndoRedo<int>( owner, 0 );
		_facefxname = new UndoRedo<string>( owner, string.Empty );
		_startTime.Changed += FireChangedEvent;
		_animation.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_facefxname.Changed += FireChangedEvent;
	}

	public AnimFaceFXKey()
	{
		Initialize( GetOwner() );
	}

	public AnimFaceFXKey( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimFaceFXKey( DBResource owner, AnimFaceFXKey source )
		: this(owner, source, true){}

	protected AnimFaceFXKey( DBResource owner, AnimFaceFXKey source, bool fireEvent )
	{
		_startTime = new UndoRedo<float>( owner, source.startTime );
		_animation = new UndoRedo<int>( owner, source.animation );
		_cycleCount = new UndoRedo<int>( owner, source.cycleCount );
		_facefxname = new UndoRedo<string>( owner, source.facefxname );
		_startTime.Changed += FireChangedEvent;
		_animation.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_facefxname.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimFaceFXKey source = _source as AnimFaceFXKey;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimFaceFXKey" );
		startTime = source.startTime;
		animation = source.animation;
		cycleCount = source.cycleCount;
		facefxname = source.facefxname;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimFaceFXKey newParent = _newParent as AnimFaceFXKey;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_startTime.SetParent( newParent == null ? null : newParent._startTime );
		_animation.SetParent( newParent == null ? null : newParent._animation );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_facefxname.SetParent( newParent == null ? null : newParent._facefxname );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_startTime.Reset();
		_animation.Reset();
		_cycleCount.Reset();
		_facefxname.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_startTime.IsDerivedFromParent()
			&& _animation.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _facefxname.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "startTime" )
			_startTime.Reset();
		else if ( fieldName == "animation" )
			_animation.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "facefxname" )
			_facefxname.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "startTime" )
			return _startTime.IsDerivedFromParent();
		if ( fieldName == "animation" )
			return _animation.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "facefxname" )
			return _facefxname.IsDerivedFromParent();
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

public class LightInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LightInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<OmniLight> _light;
	private Vec3 _position;
	private Quat _rotation;
	private UndoRedo<float> _scale;
	private UndoRedo<float> _speed;
	private UndoRedo<float> _offset;
	private UndoRedo<float> _cycleLength;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<string> _jointName;

	public DBPtr<OmniLight> light { get { return _light.Get(); } set { _light.Set( value ); } }

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	public Quat rotation { get { return _rotation; } set { _rotation.Assign( value ); } }

	[Description( "Scale coefficient" )]
	public float scale { get { return _scale.Get(); } set { _scale.Set( value ); } }

	[Description( "Playback speed coefficient" )]
	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	[Description( "(sec.) pause before playback start" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	[Description( "(sec.) cycle length (0 = no repeat)" )]
	public float cycleLength { get { return _cycleLength.Get(); } set { _cycleLength.Set( value ); } }

	[Description( "Number of playback cycles (0 = infinite)" )]
	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	[Description( "Model's joint name to bind to (empty = do not bind)" )]
	public string jointName { get { return _jointName.Get(); } set { _jointName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_light = new UndoRedoDBPtr<OmniLight>( owner );
		_position = new Vec3( owner );
		_rotation = new Quat( owner );
		_scale = new UndoRedo<float>( owner, 1.0f );
		_speed = new UndoRedo<float>( owner, 1.0f );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_cycleLength = new UndoRedo<float>( owner, 0.0f );
		_cycleCount = new UndoRedo<int>( owner, 1 );
		_jointName = new UndoRedo<string>( owner, string.Empty );
		_light.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_rotation.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleLength.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
	}

	public LightInstance()
	{
		Initialize( GetOwner() );
	}

	public LightInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LightInstance( DBResource owner, LightInstance source )
		: this(owner, source, true){}

	protected LightInstance( DBResource owner, LightInstance source, bool fireEvent )
	{
		_light = new UndoRedoDBPtr<OmniLight>( owner, source.light );
		_position = new Vec3( owner, source.position );
		_rotation = new Quat( owner, source.rotation );
		_scale = new UndoRedo<float>( owner, source.scale );
		_speed = new UndoRedo<float>( owner, source.speed );
		_offset = new UndoRedo<float>( owner, source.offset );
		_cycleLength = new UndoRedo<float>( owner, source.cycleLength );
		_cycleCount = new UndoRedo<int>( owner, source.cycleCount );
		_jointName = new UndoRedo<string>( owner, source.jointName );
		_light.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_rotation.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleLength.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LightInstance source = _source as LightInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LightInstance" );
		light = source.light;
		position = source.position;
		rotation = source.rotation;
		scale = source.scale;
		speed = source.speed;
		offset = source.offset;
		cycleLength = source.cycleLength;
		cycleCount = source.cycleCount;
		jointName = source.jointName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LightInstance newParent = _newParent as LightInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_light.SetParent( newParent == null ? null : newParent._light );
		_position.SetParent( newParent == null ? null : newParent._position );
		_rotation.SetParent( newParent == null ? null : newParent._rotation );
		_scale.SetParent( newParent == null ? null : newParent._scale );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_cycleLength.SetParent( newParent == null ? null : newParent._cycleLength );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_jointName.SetParent( newParent == null ? null : newParent._jointName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_light.Reset();
		_position.Reset();
		_rotation.Reset();
		_scale.Reset();
		_speed.Reset();
		_offset.Reset();
		_cycleLength.Reset();
		_cycleCount.Reset();
		_jointName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_light.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			&& _rotation.IsDerivedFromParent()
			&& _scale.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _cycleLength.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _jointName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "light" )
			_light.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "rotation" )
			_rotation.Reset();
		else if ( fieldName == "scale" )
			_scale.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "cycleLength" )
			_cycleLength.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "jointName" )
			_jointName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "light" )
			return _light.IsDerivedFromParent();
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "rotation" )
			return _rotation.IsDerivedFromParent();
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "cycleLength" )
			return _cycleLength.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "jointName" )
			return _jointName.IsDerivedFromParent();
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

public class ModelInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ModelInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Skeleton> _model;
	private UndoRedoAssignableList<AnimFaceFXKey> _anims;
	private UndoRedoList<int> _skins;
	private Matrix _trasform;
	private UndoRedo<float> _speed;
	private UndoRedo<float> _offset;
	private UndoRedo<float> _cycleLength;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<float> _duration;
	private UndoRedo<float> _fadein;
	private UndoRedo<float> _fadeout;

	public DBPtr<Skeleton> model { get { return _model.Get(); } set { _model.Set( value ); } }

	[Description( "Animation & FaceFX keys" )]
	public libdb.IChangeableList<AnimFaceFXKey> anims { get { return _anims; } set { _anims.Assign( value ); } }

	[Description( "Skins" )]
	public libdb.IChangeableList<int> skins { get { return _skins; } set { _skins.Assign( value ); } }

	[Description( "Transform matrix" )]
	public Matrix trasform { get { return _trasform; } set { _trasform.Assign( value ); } }

	[Description( "Playback speed coefficient" )]
	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	[Description( "(sec.) pause before playback start" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	[Description( "(sec.) cycle length (0 = animation length)" )]
	public float cycleLength { get { return _cycleLength.Get(); } set { _cycleLength.Set( value ); } }

	[Description( "Number of playback cycles (0 = infinite)" )]
	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	[Description( "(sec.) duration (0 = use cycleLength)" )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "(sec.) FadeIn" )]
	public float fadein { get { return _fadein.Get(); } set { _fadein.Set( value ); } }

	[Description( "(sec.) FadeOut" )]
	public float fadeout { get { return _fadeout.Get(); } set { _fadeout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_model = new UndoRedoDBPtr<Skeleton>( owner );
		_anims = new UndoRedoAssignableList<AnimFaceFXKey>( owner );
		_skins = new UndoRedoList<int>( owner );
		_trasform = new Matrix( owner );
		_speed = new UndoRedo<float>( owner, 1.0f );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_cycleLength = new UndoRedo<float>( owner, 0.0f );
		_cycleCount = new UndoRedo<int>( owner, 0 );
		_duration = new UndoRedo<float>( owner, 0.0f );
		_fadein = new UndoRedo<float>( owner, 0.0f );
		_fadeout = new UndoRedo<float>( owner, 0.0f );
		_model.Changed += FireChangedEvent;
		_anims.Changed += FireChangedEvent;
		_skins.Changed += FireChangedEvent;
		_trasform.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleLength.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_fadein.Changed += FireChangedEvent;
		_fadeout.Changed += FireChangedEvent;
	}

	public ModelInstance()
	{
		Initialize( GetOwner() );
	}

	public ModelInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ModelInstance( DBResource owner, ModelInstance source )
		: this(owner, source, true){}

	protected ModelInstance( DBResource owner, ModelInstance source, bool fireEvent )
	{
		_model = new UndoRedoDBPtr<Skeleton>( owner, source.model );
		_anims = new UndoRedoAssignableList<AnimFaceFXKey>( owner );
		_anims.Assign( source.anims );
		_skins = new UndoRedoList<int>( owner );
		_skins.Assign( source.skins );
		_trasform = new Matrix( owner, source.trasform );
		_speed = new UndoRedo<float>( owner, source.speed );
		_offset = new UndoRedo<float>( owner, source.offset );
		_cycleLength = new UndoRedo<float>( owner, source.cycleLength );
		_cycleCount = new UndoRedo<int>( owner, source.cycleCount );
		_duration = new UndoRedo<float>( owner, source.duration );
		_fadein = new UndoRedo<float>( owner, source.fadein );
		_fadeout = new UndoRedo<float>( owner, source.fadeout );
		_model.Changed += FireChangedEvent;
		_anims.Changed += FireChangedEvent;
		_skins.Changed += FireChangedEvent;
		_trasform.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleLength.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_fadein.Changed += FireChangedEvent;
		_fadeout.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ModelInstance source = _source as ModelInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ModelInstance" );
		model = source.model;
		anims = source.anims;
		skins = source.skins;
		trasform = source.trasform;
		speed = source.speed;
		offset = source.offset;
		cycleLength = source.cycleLength;
		cycleCount = source.cycleCount;
		duration = source.duration;
		fadein = source.fadein;
		fadeout = source.fadeout;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ModelInstance newParent = _newParent as ModelInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_model.SetParent( newParent == null ? null : newParent._model );
		_anims.SetParent( newParent == null ? null : newParent._anims );
		_skins.SetParent( newParent == null ? null : newParent._skins );
		_trasform.SetParent( newParent == null ? null : newParent._trasform );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_cycleLength.SetParent( newParent == null ? null : newParent._cycleLength );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_fadein.SetParent( newParent == null ? null : newParent._fadein );
		_fadeout.SetParent( newParent == null ? null : newParent._fadeout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_model.Reset();
		_anims.Reset();
		_skins.Reset();
		_trasform.Reset();
		_speed.Reset();
		_offset.Reset();
		_cycleLength.Reset();
		_cycleCount.Reset();
		_duration.Reset();
		_fadein.Reset();
		_fadeout.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_model.IsDerivedFromParent()
			&& _anims.IsDerivedFromParent()
			&& _skins.IsDerivedFromParent()
			&& _trasform.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _cycleLength.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _fadein.IsDerivedFromParent()
			&& _fadeout.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "model" )
			_model.Reset();
		else if ( fieldName == "anims" )
			_anims.Reset();
		else if ( fieldName == "skins" )
			_skins.Reset();
		else if ( fieldName == "trasform" )
			_trasform.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "cycleLength" )
			_cycleLength.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "fadein" )
			_fadein.Reset();
		else if ( fieldName == "fadeout" )
			_fadeout.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "model" )
			return _model.IsDerivedFromParent();
		if ( fieldName == "anims" )
			return _anims.IsDerivedFromParent();
		if ( fieldName == "skins" )
			return _skins.IsDerivedFromParent();
		if ( fieldName == "trasform" )
			return _trasform.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "cycleLength" )
			return _cycleLength.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "fadein" )
			return _fadein.IsDerivedFromParent();
		if ( fieldName == "fadeout" )
			return _fadeout.IsDerivedFromParent();
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
public class Locator : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Locator __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private Placement2 _offset2;
	private UndoRedo<ELocatorAttachFlags> _flags;
	private UndoRedo<string> _jointName;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public Placement2 offset2 { get { return _offset2; } set { _offset2.Assign( value ); } }

	public ELocatorAttachFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[JointNamesSelector]
	public string jointName { get { return _jointName.Get(); } set { _jointName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_offset2 = new Placement2( owner );
		_flags = new UndoRedo<ELocatorAttachFlags>( owner, ELocatorAttachFlags.UseJointPosition | ELocatorAttachFlags.UseJointRotation | ELocatorAttachFlags.UseJointScale );
		_jointName = new UndoRedo<string>( owner, string.Empty );
		_name.Changed += FireChangedEvent;
		_offset2.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
	}

	public Locator()
	{
		Initialize( GetOwner() );
	}

	public Locator( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Locator( DBResource owner, Locator source )
		: this(owner, source, true){}

	protected Locator( DBResource owner, Locator source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_offset2 = new Placement2( owner, source.offset2 );
		_flags = new UndoRedo<ELocatorAttachFlags>( owner, source.flags );
		_jointName = new UndoRedo<string>( owner, source.jointName );
		_name.Changed += FireChangedEvent;
		_offset2.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Locator source = _source as Locator;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Locator" );
		name = source.name;
		offset2 = source.offset2;
		flags = source.flags;
		jointName = source.jointName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Locator newParent = _newParent as Locator;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_offset2.SetParent( newParent == null ? null : newParent._offset2 );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_jointName.SetParent( newParent == null ? null : newParent._jointName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_offset2.Reset();
		_flags.Reset();
		_jointName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _offset2.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _jointName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "offset2" )
			_offset2.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "jointName" )
			_jointName.Reset();
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
		if ( fieldName == "offset2" )
			return _offset2.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "jointName" )
			return _jointName.IsDerivedFromParent();
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

public class SoundInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _soundFile;
	private UndoRedo<float> _offset;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<float> _volume;
	private UndoRedo<bool> _is3DSound;

	[FileRef("*.wav;*.mp3;*.ogg;*.flac")]
	public string soundFile { get { return _soundFile.Get(); } set { _soundFile.Set( value ); } }

	[Description( "(sec.) pause before playback start" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	[Description( "Number of playback cycles (0 = infinite)" )]
	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	[Description( "Sound volume" )]
	public float volume { get { return _volume.Get(); } set { _volume.Set( value ); } }

	[Description( "true = 3d sound, false = 2d sound" )]
	public bool is3DSound { get { return _is3DSound.Get(); } set { _is3DSound.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_soundFile = new UndoRedo<string>( owner, string.Empty );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_cycleCount = new UndoRedo<int>( owner, 0 );
		_volume = new UndoRedo<float>( owner, 1.0f );
		_is3DSound = new UndoRedo<bool>( owner, true );
		_soundFile.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
		_is3DSound.Changed += FireChangedEvent;
	}

	public SoundInstance()
	{
		Initialize( GetOwner() );
	}

	public SoundInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundInstance( DBResource owner, SoundInstance source )
		: this(owner, source, true){}

	protected SoundInstance( DBResource owner, SoundInstance source, bool fireEvent )
	{
		_soundFile = new UndoRedo<string>( owner, source.soundFile );
		_offset = new UndoRedo<float>( owner, source.offset );
		_cycleCount = new UndoRedo<int>( owner, source.cycleCount );
		_volume = new UndoRedo<float>( owner, source.volume );
		_is3DSound = new UndoRedo<bool>( owner, source.is3DSound );
		_soundFile.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
		_is3DSound.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundInstance source = _source as SoundInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundInstance" );
		soundFile = source.soundFile;
		offset = source.offset;
		cycleCount = source.cycleCount;
		volume = source.volume;
		is3DSound = source.is3DSound;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundInstance newParent = _newParent as SoundInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_soundFile.SetParent( newParent == null ? null : newParent._soundFile );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_volume.SetParent( newParent == null ? null : newParent._volume );
		_is3DSound.SetParent( newParent == null ? null : newParent._is3DSound );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_soundFile.Reset();
		_offset.Reset();
		_cycleCount.Reset();
		_volume.Reset();
		_is3DSound.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_soundFile.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _volume.IsDerivedFromParent()
			&& _is3DSound.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "soundFile" )
			_soundFile.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "volume" )
			_volume.Reset();
		else if ( fieldName == "is3DSound" )
			_is3DSound.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "soundFile" )
			return _soundFile.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "volume" )
			return _volume.IsDerivedFromParent();
		if ( fieldName == "is3DSound" )
			return _is3DSound.IsDerivedFromParent();
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

public class ObjectLockMask : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ObjectLockMask __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _tileSize;
	private UndoRedoAssignableList<IntPoint> _mask;

	public float tileSize { get { return _tileSize.Get(); } set { _tileSize.Set( value ); } }

	public libdb.IChangeableList<IntPoint> mask { get { return _mask; } set { _mask.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_tileSize = new UndoRedo<float>( owner, 0.5f );
		_mask = new UndoRedoAssignableList<IntPoint>( owner );
		_tileSize.Changed += FireChangedEvent;
		_mask.Changed += FireChangedEvent;
	}

	public ObjectLockMask()
	{
		Initialize( GetOwner() );
	}

	public ObjectLockMask( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ObjectLockMask( DBResource owner, ObjectLockMask source )
		: this(owner, source, true){}

	protected ObjectLockMask( DBResource owner, ObjectLockMask source, bool fireEvent )
	{
		_tileSize = new UndoRedo<float>( owner, source.tileSize );
		_mask = new UndoRedoAssignableList<IntPoint>( owner );
		_mask.Assign( source.mask );
		_tileSize.Changed += FireChangedEvent;
		_mask.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ObjectLockMask source = _source as ObjectLockMask;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ObjectLockMask" );
		tileSize = source.tileSize;
		mask = source.mask;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ObjectLockMask newParent = _newParent as ObjectLockMask;
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

public class RoadControlPoint : FlatSplineControlPointDesc, libdb.ICompositeDBValue, libdb.IChangeable
{

	private RoadControlPoint __parent = null;

	private UndoRedo<float> _opacity;

	[Description( "Прозрачность материала дороги в этой точке (от 0 до 1)" )]
	public float opacity { get { return _opacity.Get(); } set { _opacity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_opacity = new UndoRedo<float>( owner, 1.0f );
		_opacity.Changed += FireChangedEvent;
	}

	public RoadControlPoint()
	{
		Initialize( GetOwner() );
	}

	public RoadControlPoint( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public RoadControlPoint( DBResource owner, RoadControlPoint source ): base(owner, source, false)
	{
		_opacity = new UndoRedo<float>( owner, source.opacity );
		_opacity.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		RoadControlPoint source = _source as RoadControlPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RoadControlPoint" );

		base.Assign( source );

		opacity = source.opacity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		RoadControlPoint newParent = _newParent as RoadControlPoint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_opacity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_opacity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "opacity" )
			_opacity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class RoadProperties : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RoadProperties __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _width;
	private UndoRedo<float> _border;
	private UndoRedo<float> _falloff;
	private UndoRedo<float> _opacity;
	private UndoRedo<float> _tileU;
	private UndoRedo<float> _tileV;
	private UndoRedo<float> _tileVBorder;
	private UndoRedo<bool> _fit;
	private UndoRedo<bool> _flip;
	private UndoRedo<float> _priority;
	private UndoRedoDBPtr<RoadMaterial> _materialN;
	private UndoRedoDBPtr<RoadMaterial> _materialA;
	private UndoRedoDBPtr<RoadMaterial> _materialB;

	[Description( "Базовая ширина дороги в метрах, относительно которой действуют настройки ширины в контрольных точках, и указываются некоторые другие параметры." )]
	public float width { get { return _width.Get(); } set { _width.Set( value ); } }

	[Description( "Значение от 0 до 1, задающая ширину бордюра в процентах от половины *базовой* ширины дороги (не текущей, а width)." )]
	public float border { get { return _border.Get(); } set { _border.Set( value ); } }

	[Description( "Значение от 0 до 1, задающая ширину затухания по краям полотна дороги в процентах от половины *базовой* ширины дороги (не текущей, а width)." )]
	public float falloff { get { return _falloff.Get(); } set { _falloff.Set( value ); } }

	[Description( "Общая прозрачность дороги (от 0 до 1), умножается на прозрачность в отдельных точках." )]
	public float opacity { get { return _opacity.Get(); } set { _opacity.Set( value ); } }

	[Description( "Значение тайлинга текстуры полотна поперек направления дороги, т.е. сколько раз текстура укладывается по ширине (*базовой* или текущей, в зависимости от fit)." )]
	public float tileU { get { return _tileU.Get(); } set { _tileU.Set( value ); } }

	[Description( "Значение тайлинга текстуры полотна вдоль направления дороги, в том же масштабе, что и  tileU." )]
	public float tileV { get { return _tileV.Get(); } set { _tileV.Set( value ); } }

	[Description( "Значение тайлинга текстуры бордюра вдоль направления дороги." )]
	public float tileVBorder { get { return _tileVBorder.Get(); } set { _tileVBorder.Set( value ); } }

	[Description( "Флаг, определяющий, должен ли маппинг текстуры растягиваться с изменением ширины дороги (true) или должен быть равномерным, задаваясь для базовой ширины (false)." )]
	public bool fit { get { return _fit.Get(); } set { _fit.Set( value ); } }

	[Description( "Флаг, определяющий, нужно ли флипнуть текстуру поперек дороги." )]
	public bool flip { get { return _flip.Get(); } set { _flip.Set( value ); } }

	[Description( "Приоритет рендера, большее число означает, что дорога будет рендериться раньше других. По умолчанию 0." )]
	public float priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "Материал дороги для нейтральной земли" )]
	public DBPtr<RoadMaterial> materialN { get { return _materialN.Get(); } set { _materialN.Set( value ); } }

	[Description( "Материал дороги для земли фракции A" )]
	public DBPtr<RoadMaterial> materialA { get { return _materialA.Get(); } set { _materialA.Set( value ); } }

	[Description( "Материал дороги для земли фракции B" )]
	public DBPtr<RoadMaterial> materialB { get { return _materialB.Get(); } set { _materialB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_width = new UndoRedo<float>( owner, 2.0f );
		_border = new UndoRedo<float>( owner, 0.2f );
		_falloff = new UndoRedo<float>( owner, 0.1f );
		_opacity = new UndoRedo<float>( owner, 1.0f );
		_tileU = new UndoRedo<float>( owner, 1.0f );
		_tileV = new UndoRedo<float>( owner, 1.0f );
		_tileVBorder = new UndoRedo<float>( owner, 1.0f );
		_fit = new UndoRedo<bool>( owner, false );
		_flip = new UndoRedo<bool>( owner, false );
		_priority = new UndoRedo<float>( owner, 0.0f );
		_materialN = new UndoRedoDBPtr<RoadMaterial>( owner );
		_materialA = new UndoRedoDBPtr<RoadMaterial>( owner );
		_materialB = new UndoRedoDBPtr<RoadMaterial>( owner );
		_width.Changed += FireChangedEvent;
		_border.Changed += FireChangedEvent;
		_falloff.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_tileU.Changed += FireChangedEvent;
		_tileV.Changed += FireChangedEvent;
		_tileVBorder.Changed += FireChangedEvent;
		_fit.Changed += FireChangedEvent;
		_flip.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_materialN.Changed += FireChangedEvent;
		_materialA.Changed += FireChangedEvent;
		_materialB.Changed += FireChangedEvent;
	}

	public RoadProperties()
	{
		Initialize( GetOwner() );
	}

	public RoadProperties( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RoadProperties( DBResource owner, RoadProperties source )
		: this(owner, source, true){}

	protected RoadProperties( DBResource owner, RoadProperties source, bool fireEvent )
	{
		_width = new UndoRedo<float>( owner, source.width );
		_border = new UndoRedo<float>( owner, source.border );
		_falloff = new UndoRedo<float>( owner, source.falloff );
		_opacity = new UndoRedo<float>( owner, source.opacity );
		_tileU = new UndoRedo<float>( owner, source.tileU );
		_tileV = new UndoRedo<float>( owner, source.tileV );
		_tileVBorder = new UndoRedo<float>( owner, source.tileVBorder );
		_fit = new UndoRedo<bool>( owner, source.fit );
		_flip = new UndoRedo<bool>( owner, source.flip );
		_priority = new UndoRedo<float>( owner, source.priority );
		_materialN = new UndoRedoDBPtr<RoadMaterial>( owner, source.materialN );
		_materialA = new UndoRedoDBPtr<RoadMaterial>( owner, source.materialA );
		_materialB = new UndoRedoDBPtr<RoadMaterial>( owner, source.materialB );
		_width.Changed += FireChangedEvent;
		_border.Changed += FireChangedEvent;
		_falloff.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_tileU.Changed += FireChangedEvent;
		_tileV.Changed += FireChangedEvent;
		_tileVBorder.Changed += FireChangedEvent;
		_fit.Changed += FireChangedEvent;
		_flip.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_materialN.Changed += FireChangedEvent;
		_materialA.Changed += FireChangedEvent;
		_materialB.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RoadProperties source = _source as RoadProperties;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RoadProperties" );
		width = source.width;
		border = source.border;
		falloff = source.falloff;
		opacity = source.opacity;
		tileU = source.tileU;
		tileV = source.tileV;
		tileVBorder = source.tileVBorder;
		fit = source.fit;
		flip = source.flip;
		priority = source.priority;
		materialN = source.materialN;
		materialA = source.materialA;
		materialB = source.materialB;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RoadProperties newParent = _newParent as RoadProperties;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_width.SetParent( newParent == null ? null : newParent._width );
		_border.SetParent( newParent == null ? null : newParent._border );
		_falloff.SetParent( newParent == null ? null : newParent._falloff );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		_tileU.SetParent( newParent == null ? null : newParent._tileU );
		_tileV.SetParent( newParent == null ? null : newParent._tileV );
		_tileVBorder.SetParent( newParent == null ? null : newParent._tileVBorder );
		_fit.SetParent( newParent == null ? null : newParent._fit );
		_flip.SetParent( newParent == null ? null : newParent._flip );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_materialN.SetParent( newParent == null ? null : newParent._materialN );
		_materialA.SetParent( newParent == null ? null : newParent._materialA );
		_materialB.SetParent( newParent == null ? null : newParent._materialB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_width.Reset();
		_border.Reset();
		_falloff.Reset();
		_opacity.Reset();
		_tileU.Reset();
		_tileV.Reset();
		_tileVBorder.Reset();
		_fit.Reset();
		_flip.Reset();
		_priority.Reset();
		_materialN.Reset();
		_materialA.Reset();
		_materialB.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_width.IsDerivedFromParent()
			&& _border.IsDerivedFromParent()
			&& _falloff.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& _tileU.IsDerivedFromParent()
			&& _tileV.IsDerivedFromParent()
			&& _tileVBorder.IsDerivedFromParent()
			&& _fit.IsDerivedFromParent()
			&& _flip.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& _materialN.IsDerivedFromParent()
			&& _materialA.IsDerivedFromParent()
			&& _materialB.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "width" )
			_width.Reset();
		else if ( fieldName == "border" )
			_border.Reset();
		else if ( fieldName == "falloff" )
			_falloff.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else if ( fieldName == "tileU" )
			_tileU.Reset();
		else if ( fieldName == "tileV" )
			_tileV.Reset();
		else if ( fieldName == "tileVBorder" )
			_tileVBorder.Reset();
		else if ( fieldName == "fit" )
			_fit.Reset();
		else if ( fieldName == "flip" )
			_flip.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else if ( fieldName == "materialN" )
			_materialN.Reset();
		else if ( fieldName == "materialA" )
			_materialA.Reset();
		else if ( fieldName == "materialB" )
			_materialB.Reset();
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
		if ( fieldName == "border" )
			return _border.IsDerivedFromParent();
		if ( fieldName == "falloff" )
			return _falloff.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		if ( fieldName == "tileU" )
			return _tileU.IsDerivedFromParent();
		if ( fieldName == "tileV" )
			return _tileV.IsDerivedFromParent();
		if ( fieldName == "tileVBorder" )
			return _tileVBorder.IsDerivedFromParent();
		if ( fieldName == "fit" )
			return _fit.IsDerivedFromParent();
		if ( fieldName == "flip" )
			return _flip.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		if ( fieldName == "materialN" )
			return _materialN.IsDerivedFromParent();
		if ( fieldName == "materialA" )
			return _materialA.IsDerivedFromParent();
		if ( fieldName == "materialB" )
			return _materialB.IsDerivedFromParent();
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

public class SoundTrack : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundTrack __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<SoundSRC> _sound;
	private UndoRedo<float> _volume;
	private UndoRedo<float> _volumeRandomization;
	private UndoRedo<int> _priority;

	public DBPtr<SoundSRC> sound { get { return _sound.Get(); } set { _sound.Set( value ); } }

	public float volume { get { return _volume.Get(); } set { _volume.Set( value ); } }

	public float volumeRandomization { get { return _volumeRandomization.Get(); } set { _volumeRandomization.Set( value ); } }

	[Description( "A priority which the Sound will be played. 0 - most important, 256 - least important" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_sound = new UndoRedoDBPtr<SoundSRC>( owner );
		_volume = new UndoRedo<float>( owner, 1.0f );
		_volumeRandomization = new UndoRedo<float>( owner, 0.0f );
		_priority = new UndoRedo<int>( owner, 0 );
		_sound.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
		_volumeRandomization.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
	}

	public SoundTrack()
	{
		Initialize( GetOwner() );
	}

	public SoundTrack( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundTrack( DBResource owner, SoundTrack source )
		: this(owner, source, true){}

	protected SoundTrack( DBResource owner, SoundTrack source, bool fireEvent )
	{
		_sound = new UndoRedoDBPtr<SoundSRC>( owner, source.sound );
		_volume = new UndoRedo<float>( owner, source.volume );
		_volumeRandomization = new UndoRedo<float>( owner, source.volumeRandomization );
		_priority = new UndoRedo<int>( owner, source.priority );
		_sound.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
		_volumeRandomization.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundTrack source = _source as SoundTrack;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundTrack" );
		sound = source.sound;
		volume = source.volume;
		volumeRandomization = source.volumeRandomization;
		priority = source.priority;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundTrack newParent = _newParent as SoundTrack;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_sound.SetParent( newParent == null ? null : newParent._sound );
		_volume.SetParent( newParent == null ? null : newParent._volume );
		_volumeRandomization.SetParent( newParent == null ? null : newParent._volumeRandomization );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_sound.Reset();
		_volume.Reset();
		_volumeRandomization.Reset();
		_priority.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_sound.IsDerivedFromParent()
			&& _volume.IsDerivedFromParent()
			&& _volumeRandomization.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "sound" )
			_sound.Reset();
		else if ( fieldName == "volume" )
			_volume.Reset();
		else if ( fieldName == "volumeRandomization" )
			_volumeRandomization.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "sound" )
			return _sound.IsDerivedFromParent();
		if ( fieldName == "volume" )
			return _volume.IsDerivedFromParent();
		if ( fieldName == "volumeRandomization" )
			return _volumeRandomization.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
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

public class StaticModelInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StaticModelInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<StaticMesh> _model;
	private Matrix _trasform;
	private UndoRedo<float> _offset;
	private UndoRedo<float> _duration;
	private UndoRedo<float> _fadein;
	private UndoRedo<float> _fadeout;

	public DBPtr<StaticMesh> model { get { return _model.Get(); } set { _model.Set( value ); } }

	[Description( "Transform matrix" )]
	public Matrix trasform { get { return _trasform; } set { _trasform.Assign( value ); } }

	[Description( "(sec.) pause before playback start" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	[Description( "(sec.) duration (0 = infinity)" )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "(sec.) FadeIn" )]
	public float fadein { get { return _fadein.Get(); } set { _fadein.Set( value ); } }

	[Description( "(sec.) FadeOut" )]
	public float fadeout { get { return _fadeout.Get(); } set { _fadeout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_model = new UndoRedoDBPtr<StaticMesh>( owner );
		_trasform = new Matrix( owner );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_duration = new UndoRedo<float>( owner, 0.0f );
		_fadein = new UndoRedo<float>( owner, 0.0f );
		_fadeout = new UndoRedo<float>( owner, 0.0f );
		_model.Changed += FireChangedEvent;
		_trasform.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_fadein.Changed += FireChangedEvent;
		_fadeout.Changed += FireChangedEvent;
	}

	public StaticModelInstance()
	{
		Initialize( GetOwner() );
	}

	public StaticModelInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StaticModelInstance( DBResource owner, StaticModelInstance source )
		: this(owner, source, true){}

	protected StaticModelInstance( DBResource owner, StaticModelInstance source, bool fireEvent )
	{
		_model = new UndoRedoDBPtr<StaticMesh>( owner, source.model );
		_trasform = new Matrix( owner, source.trasform );
		_offset = new UndoRedo<float>( owner, source.offset );
		_duration = new UndoRedo<float>( owner, source.duration );
		_fadein = new UndoRedo<float>( owner, source.fadein );
		_fadeout = new UndoRedo<float>( owner, source.fadeout );
		_model.Changed += FireChangedEvent;
		_trasform.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_fadein.Changed += FireChangedEvent;
		_fadeout.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StaticModelInstance source = _source as StaticModelInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StaticModelInstance" );
		model = source.model;
		trasform = source.trasform;
		offset = source.offset;
		duration = source.duration;
		fadein = source.fadein;
		fadeout = source.fadeout;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StaticModelInstance newParent = _newParent as StaticModelInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_model.SetParent( newParent == null ? null : newParent._model );
		_trasform.SetParent( newParent == null ? null : newParent._trasform );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_fadein.SetParent( newParent == null ? null : newParent._fadein );
		_fadeout.SetParent( newParent == null ? null : newParent._fadeout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_model.Reset();
		_trasform.Reset();
		_offset.Reset();
		_duration.Reset();
		_fadein.Reset();
		_fadeout.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_model.IsDerivedFromParent()
			&& _trasform.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _fadein.IsDerivedFromParent()
			&& _fadeout.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "model" )
			_model.Reset();
		else if ( fieldName == "trasform" )
			_trasform.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "fadein" )
			_fadein.Reset();
		else if ( fieldName == "fadeout" )
			_fadeout.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "model" )
			return _model.IsDerivedFromParent();
		if ( fieldName == "trasform" )
			return _trasform.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "fadein" )
			return _fadein.IsDerivedFromParent();
		if ( fieldName == "fadeout" )
			return _fadeout.IsDerivedFromParent();
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

public class SoundObject : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundObject __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<SoundSet> _soundSet;

	public DBPtr<SoundSet> soundSet { get { return _soundSet.Get(); } set { _soundSet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_soundSet = new UndoRedoDBPtr<SoundSet>( owner );
		_soundSet.Changed += FireChangedEvent;
	}

	public SoundObject()
	{
		Initialize( GetOwner() );
	}

	public SoundObject( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundObject( DBResource owner, SoundObject source )
		: this(owner, source, true){}

	protected SoundObject( DBResource owner, SoundObject source, bool fireEvent )
	{
		_soundSet = new UndoRedoDBPtr<SoundSet>( owner, source.soundSet );
		_soundSet.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundObject source = _source as SoundObject;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundObject" );
		soundSet = source.soundSet;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundObject newParent = _newParent as SoundObject;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_soundSet.SetParent( newParent == null ? null : newParent._soundSet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_soundSet.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_soundSet.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "soundSet" )
			_soundSet.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "soundSet" )
			return _soundSet.IsDerivedFromParent();
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

public class SoundEffect : SoundTrack, libdb.ICompositeDBValue, libdb.IChangeable
{

	private SoundEffect __parent = null;

	private UndoRedo<float> _pitch;
	private UndoRedo<float> _pitchRandomization;

	public float pitch { get { return _pitch.Get(); } set { _pitch.Set( value ); } }

	public float pitchRandomization { get { return _pitchRandomization.Get(); } set { _pitchRandomization.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_pitch = new UndoRedo<float>( owner, 0.0f );
		_pitchRandomization = new UndoRedo<float>( owner, 0.0f );
		_pitch.Changed += FireChangedEvent;
		_pitchRandomization.Changed += FireChangedEvent;
	}

	public SoundEffect()
	{
		Initialize( GetOwner() );
	}

	public SoundEffect( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public SoundEffect( DBResource owner, SoundEffect source ): base(owner, source, false)
	{
		_pitch = new UndoRedo<float>( owner, source.pitch );
		_pitchRandomization = new UndoRedo<float>( owner, source.pitchRandomization );
		_pitch.Changed += FireChangedEvent;
		_pitchRandomization.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		SoundEffect source = _source as SoundEffect;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundEffect" );

		base.Assign( source );

		pitch = source.pitch;
		pitchRandomization = source.pitchRandomization;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		SoundEffect newParent = _newParent as SoundEffect;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_pitch.SetParent( newParent == null ? null : newParent._pitch );
		_pitchRandomization.SetParent( newParent == null ? null : newParent._pitchRandomization );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_pitch.Reset();
		_pitchRandomization.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_pitch.IsDerivedFromParent()
			&& _pitchRandomization.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "pitch" )
			_pitch.Reset();
		else if ( fieldName == "pitchRandomization" )
			_pitchRandomization.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "pitch" )
			return _pitch.IsDerivedFromParent();
		if ( fieldName == "pitchRandomization" )
			return _pitchRandomization.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class EffectInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EffectInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ModelInstance _model;
	private LightInstance _light;
	private StaticModelInstance _staticmodel;
	private SoundInstance _sound;
	private FMODEventInstance _fmodEvent;
	private UndoRedo<string> _jointName;

	public ModelInstance model { get { return _model; } set { _model.Assign( value ); } }

	public LightInstance light { get { return _light; } set { _light.Assign( value ); } }

	public StaticModelInstance staticmodel { get { return _staticmodel; } set { _staticmodel.Assign( value ); } }

	public SoundInstance sound { get { return _sound; } set { _sound.Assign( value ); } }

	public FMODEventInstance fmodEvent { get { return _fmodEvent; } set { _fmodEvent.Assign( value ); } }

	[Description( "Visual Object's joint name to bind to (empty = do not bind)" )]
	public string jointName { get { return _jointName.Get(); } set { _jointName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_model = new ModelInstance( owner );
		_light = new LightInstance( owner );
		_staticmodel = new StaticModelInstance( owner );
		_sound = new SoundInstance( owner );
		_fmodEvent = new FMODEventInstance( owner );
		_jointName = new UndoRedo<string>( owner, string.Empty );
		_model.Changed += FireChangedEvent;
		_light.Changed += FireChangedEvent;
		_staticmodel.Changed += FireChangedEvent;
		_sound.Changed += FireChangedEvent;
		_fmodEvent.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
	}

	public EffectInstance()
	{
		Initialize( GetOwner() );
	}

	public EffectInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EffectInstance( DBResource owner, EffectInstance source )
		: this(owner, source, true){}

	protected EffectInstance( DBResource owner, EffectInstance source, bool fireEvent )
	{
		_model = new ModelInstance( owner, source.model );
		_light = new LightInstance( owner, source.light );
		_staticmodel = new StaticModelInstance( owner, source.staticmodel );
		_sound = new SoundInstance( owner, source.sound );
		_fmodEvent = new FMODEventInstance( owner, source.fmodEvent );
		_jointName = new UndoRedo<string>( owner, source.jointName );
		_model.Changed += FireChangedEvent;
		_light.Changed += FireChangedEvent;
		_staticmodel.Changed += FireChangedEvent;
		_sound.Changed += FireChangedEvent;
		_fmodEvent.Changed += FireChangedEvent;
		_jointName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EffectInstance source = _source as EffectInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectInstance" );
		model = source.model;
		light = source.light;
		staticmodel = source.staticmodel;
		sound = source.sound;
		fmodEvent = source.fmodEvent;
		jointName = source.jointName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EffectInstance newParent = _newParent as EffectInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_model.SetParent( newParent == null ? null : newParent._model );
		_light.SetParent( newParent == null ? null : newParent._light );
		_staticmodel.SetParent( newParent == null ? null : newParent._staticmodel );
		_sound.SetParent( newParent == null ? null : newParent._sound );
		_fmodEvent.SetParent( newParent == null ? null : newParent._fmodEvent );
		_jointName.SetParent( newParent == null ? null : newParent._jointName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_model.Reset();
		_light.Reset();
		_staticmodel.Reset();
		_sound.Reset();
		_fmodEvent.Reset();
		_jointName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_model.IsDerivedFromParent()
			&& _light.IsDerivedFromParent()
			&& _staticmodel.IsDerivedFromParent()
			&& _sound.IsDerivedFromParent()
			&& _fmodEvent.IsDerivedFromParent()
			&& _jointName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "model" )
			_model.Reset();
		else if ( fieldName == "light" )
			_light.Reset();
		else if ( fieldName == "staticmodel" )
			_staticmodel.Reset();
		else if ( fieldName == "sound" )
			_sound.Reset();
		else if ( fieldName == "fmodEvent" )
			_fmodEvent.Reset();
		else if ( fieldName == "jointName" )
			_jointName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "model" )
			return _model.IsDerivedFromParent();
		if ( fieldName == "light" )
			return _light.IsDerivedFromParent();
		if ( fieldName == "staticmodel" )
			return _staticmodel.IsDerivedFromParent();
		if ( fieldName == "sound" )
			return _sound.IsDerivedFromParent();
		if ( fieldName == "fmodEvent" )
			return _fmodEvent.IsDerivedFromParent();
		if ( fieldName == "jointName" )
			return _jointName.IsDerivedFromParent();
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

public class SyncInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SyncInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _midiFile;
	private UndoRedo<bool> _tempoSync;
	private UndoRedo<bool> _toneSync;
	private UndoRedo<float> _offset;

	[FileRef("*.mid")]
	public string midiFile { get { return _midiFile.Get(); } set { _midiFile.Set( value ); } }

	public bool tempoSync { get { return _tempoSync.Get(); } set { _tempoSync.Set( value ); } }

	public bool toneSync { get { return _toneSync.Get(); } set { _toneSync.Set( value ); } }

	[Description( "(sec.) pause before synced object" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_midiFile = new UndoRedo<string>( owner, string.Empty );
		_tempoSync = new UndoRedo<bool>( owner, false );
		_toneSync = new UndoRedo<bool>( owner, false );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_midiFile.Changed += FireChangedEvent;
		_tempoSync.Changed += FireChangedEvent;
		_toneSync.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
	}

	public SyncInfo()
	{
		Initialize( GetOwner() );
	}

	public SyncInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SyncInfo( DBResource owner, SyncInfo source )
		: this(owner, source, true){}

	protected SyncInfo( DBResource owner, SyncInfo source, bool fireEvent )
	{
		_midiFile = new UndoRedo<string>( owner, source.midiFile );
		_tempoSync = new UndoRedo<bool>( owner, source.tempoSync );
		_toneSync = new UndoRedo<bool>( owner, source.toneSync );
		_offset = new UndoRedo<float>( owner, source.offset );
		_midiFile.Changed += FireChangedEvent;
		_tempoSync.Changed += FireChangedEvent;
		_toneSync.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SyncInfo source = _source as SyncInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SyncInfo" );
		midiFile = source.midiFile;
		tempoSync = source.tempoSync;
		toneSync = source.toneSync;
		offset = source.offset;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SyncInfo newParent = _newParent as SyncInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_midiFile.SetParent( newParent == null ? null : newParent._midiFile );
		_tempoSync.SetParent( newParent == null ? null : newParent._tempoSync );
		_toneSync.SetParent( newParent == null ? null : newParent._toneSync );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_midiFile.Reset();
		_tempoSync.Reset();
		_toneSync.Reset();
		_offset.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_midiFile.IsDerivedFromParent()
			&& _tempoSync.IsDerivedFromParent()
			&& _toneSync.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "midiFile" )
			_midiFile.Reset();
		else if ( fieldName == "tempoSync" )
			_tempoSync.Reset();
		else if ( fieldName == "toneSync" )
			_toneSync.Reset();
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
		if ( fieldName == "midiFile" )
			return _midiFile.IsDerivedFromParent();
		if ( fieldName == "tempoSync" )
			return _tempoSync.IsDerivedFromParent();
		if ( fieldName == "toneSync" )
			return _toneSync.IsDerivedFromParent();
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

public class ViewCamera : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ViewCamera __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private Vec3 _anchor;
	private UndoRedo<float> _yaw;
	private UndoRedo<float> _pitch;
	private UndoRedo<float> _roll;
	private UndoRedo<int> _rod;
	private UndoRedo<int> _fov;
	private UndoRedo<string> _environment;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public Vec3 anchor { get { return _anchor; } set { _anchor.Assign( value ); } }

	public float yaw { get { return _yaw.Get(); } set { _yaw.Set( value ); } }

	public float pitch { get { return _pitch.Get(); } set { _pitch.Set( value ); } }

	public float roll { get { return _roll.Get(); } set { _roll.Set( value ); } }

	public int rod { get { return _rod.Get(); } set { _rod.Set( value ); } }

	public int fov { get { return _fov.Get(); } set { _fov.Set( value ); } }

	public string environment { get { return _environment.Get(); } set { _environment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_anchor = new Vec3( owner );
		_yaw = new UndoRedo<float>( owner, 0.0f );
		_pitch = new UndoRedo<float>( owner, 0.0f );
		_roll = new UndoRedo<float>( owner, 0.0f );
		_rod = new UndoRedo<int>( owner, 10 );
		_fov = new UndoRedo<int>( owner, 30 );
		_environment = new UndoRedo<string>( owner, string.Empty );
		_name.Changed += FireChangedEvent;
		_anchor.Changed += FireChangedEvent;
		_yaw.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
		_roll.Changed += FireChangedEvent;
		_rod.Changed += FireChangedEvent;
		_fov.Changed += FireChangedEvent;
		_environment.Changed += FireChangedEvent;
	}

	public ViewCamera()
	{
		Initialize( GetOwner() );
	}

	public ViewCamera( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ViewCamera( DBResource owner, ViewCamera source )
		: this(owner, source, true){}

	protected ViewCamera( DBResource owner, ViewCamera source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_anchor = new Vec3( owner, source.anchor );
		_yaw = new UndoRedo<float>( owner, source.yaw );
		_pitch = new UndoRedo<float>( owner, source.pitch );
		_roll = new UndoRedo<float>( owner, source.roll );
		_rod = new UndoRedo<int>( owner, source.rod );
		_fov = new UndoRedo<int>( owner, source.fov );
		_environment = new UndoRedo<string>( owner, source.environment );
		_name.Changed += FireChangedEvent;
		_anchor.Changed += FireChangedEvent;
		_yaw.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
		_roll.Changed += FireChangedEvent;
		_rod.Changed += FireChangedEvent;
		_fov.Changed += FireChangedEvent;
		_environment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ViewCamera source = _source as ViewCamera;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ViewCamera" );
		name = source.name;
		anchor = source.anchor;
		yaw = source.yaw;
		pitch = source.pitch;
		roll = source.roll;
		rod = source.rod;
		fov = source.fov;
		environment = source.environment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ViewCamera newParent = _newParent as ViewCamera;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_anchor.SetParent( newParent == null ? null : newParent._anchor );
		_yaw.SetParent( newParent == null ? null : newParent._yaw );
		_pitch.SetParent( newParent == null ? null : newParent._pitch );
		_roll.SetParent( newParent == null ? null : newParent._roll );
		_rod.SetParent( newParent == null ? null : newParent._rod );
		_fov.SetParent( newParent == null ? null : newParent._fov );
		_environment.SetParent( newParent == null ? null : newParent._environment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_anchor.Reset();
		_yaw.Reset();
		_pitch.Reset();
		_roll.Reset();
		_rod.Reset();
		_fov.Reset();
		_environment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _anchor.IsDerivedFromParent()
			&& _yaw.IsDerivedFromParent()
			&& _pitch.IsDerivedFromParent()
			&& _roll.IsDerivedFromParent()
			&& _rod.IsDerivedFromParent()
			&& _fov.IsDerivedFromParent()
			&& _environment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "anchor" )
			_anchor.Reset();
		else if ( fieldName == "yaw" )
			_yaw.Reset();
		else if ( fieldName == "pitch" )
			_pitch.Reset();
		else if ( fieldName == "roll" )
			_roll.Reset();
		else if ( fieldName == "rod" )
			_rod.Reset();
		else if ( fieldName == "fov" )
			_fov.Reset();
		else if ( fieldName == "environment" )
			_environment.Reset();
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
		if ( fieldName == "anchor" )
			return _anchor.IsDerivedFromParent();
		if ( fieldName == "yaw" )
			return _yaw.IsDerivedFromParent();
		if ( fieldName == "pitch" )
			return _pitch.IsDerivedFromParent();
		if ( fieldName == "roll" )
			return _roll.IsDerivedFromParent();
		if ( fieldName == "rod" )
			return _rod.IsDerivedFromParent();
		if ( fieldName == "fov" )
			return _fov.IsDerivedFromParent();
		if ( fieldName == "environment" )
			return _environment.IsDerivedFromParent();
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

[UseTypeName("CHEF")]
public class ChildEffect : DBResource
{
	private UndoRedoDBPtr<ChildEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<ChildEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<ChildEffect> _tranformedchild;
	private UndoRedoDBPtr<Effect> _childeffect;
	private Matrix _transform;

	public DBPtr<ChildEffect> tranformedchild { get { return _tranformedchild.Get(); } set { _tranformedchild.Set( value ); } }

	public DBPtr<Effect> childeffect { get { return _childeffect.Get(); } set { _childeffect.Set( value ); } }

	public Matrix transform { get { return _transform; } set { _transform.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChildEffect>(owner);
		_tranformedchild = new UndoRedoDBPtr<ChildEffect>( owner );
		_childeffect = new UndoRedoDBPtr<Effect>( owner );
		_transform = new Matrix( owner );
		___parent.Changed += FireChangedEvent;
		_tranformedchild.Changed += FireChangedEvent;
		_childeffect.Changed += FireChangedEvent;
		_transform.Changed += FireChangedEvent;
	}

	public ChildEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( ChildEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChildEffect" );
		tranformedchild = source.tranformedchild;
		childeffect = source.childeffect;
		transform = source.transform;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChildEffect source = _source as ChildEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChildEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChildEffect newParent = rawParent == null ? null : rawParent.Get<ChildEffect>();
		if ( newParent == null && _newParent is ChildEffect )
			newParent = _newParent as ChildEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tranformedchild.SetParent( newParent == null ? null : newParent._tranformedchild );
		_childeffect.SetParent( newParent == null ? null : newParent._childeffect );
		_transform.SetParent( newParent == null ? null : newParent._transform );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tranformedchild.Reset();
		_childeffect.Reset();
		_transform.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tranformedchild.IsDerivedFromParent()
			&& _childeffect.IsDerivedFromParent()
			&& _transform.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tranformedchild" )
			_tranformedchild.Reset();
		else if ( fieldName == "childeffect" )
			_childeffect.Reset();
		else if ( fieldName == "transform" )
			_transform.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tranformedchild" )
			return _tranformedchild.IsDerivedFromParent();
		if ( fieldName == "childeffect" )
			return _childeffect.IsDerivedFromParent();
		if ( fieldName == "transform" )
			return _transform.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("COLL")]
public class CollisionGeometry : DBResource
{
	private UndoRedoDBPtr<CollisionGeometry> ___parent;
	[HideInOutliner]
	public new DBPtr<CollisionGeometry> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName;
	private UndoRedo<string> _selection;

	[DstFileArg(0)]
	[SrcFile("Maya files", "*.mb")]
	public SrcFile srcFileName { get { return _srcFileName; } set { _srcFileName.Assign( value ); } }

	[DstFile("mayaColl")]
	[NoCode]
	public string mayaFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "mayaColl"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFile("coll")]
	public string fileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "coll"
			, libdb.DB.GeneratedCodeUtilities.GetOnlyFileName( srcFileName.ToString() )
			, selection.ToString()
	); } }
	[DstFileArg(1)]
	[NoCode]
	public string selection { get { return _selection.Get(); } set { _selection.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CollisionGeometry>(owner);
		_srcFileName = new SrcFile( owner, new SrcFile() );
		_selection = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_srcFileName.Changed += FireChangedEvent;
		_selection.Changed += FireChangedEvent;
	}

	public CollisionGeometry()
	{
		Initialize( this );
	}
	private void AssignSelf( CollisionGeometry source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CollisionGeometry" );
		srcFileName = source.srcFileName;
		selection = source.selection;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CollisionGeometry source = _source as CollisionGeometry;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CollisionGeometry" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CollisionGeometry newParent = rawParent == null ? null : rawParent.Get<CollisionGeometry>();
		if ( newParent == null && _newParent is CollisionGeometry )
			newParent = _newParent as CollisionGeometry;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName.SetParent( newParent == null ? null : newParent._srcFileName );
		_selection.SetParent( newParent == null ? null : newParent._selection );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName.Reset();
		_selection.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName.IsDerivedFromParent()
			&& _selection.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName" )
			_srcFileName.Reset();
		else if ( fieldName == "selection" )
			_selection.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("EFCT")]
public class Effect : DBResource
{
	private UndoRedoDBPtr<Effect> ___parent;
	[HideInOutliner]
	public new DBPtr<Effect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<LandTemp> _landtemp;
	private UndoRedoDBPtr<ChildEffect> _tranformedchild;
	private UndoRedoDBPtr<Effect> _child;
	private UndoRedoAssignableList<EffectInstance> _effects;
	private UndoRedo<bool> _randomizePhase;
	private UndoRedo<bool> _randomizeSpeed;

	public DBPtr<LandTemp> landtemp { get { return _landtemp.Get(); } set { _landtemp.Set( value ); } }

	public DBPtr<ChildEffect> tranformedchild { get { return _tranformedchild.Get(); } set { _tranformedchild.Set( value ); } }

	public DBPtr<Effect> child { get { return _child.Get(); } set { _child.Set( value ); } }

	public libdb.IChangeableList<EffectInstance> effects { get { return _effects; } set { _effects.Assign( value ); } }

	[Description( "Randomize effect start phase?" )]
	public bool randomizePhase { get { return _randomizePhase.Get(); } set { _randomizePhase.Set( value ); } }

	[Description( "Randomize effect speed?" )]
	public bool randomizeSpeed { get { return _randomizeSpeed.Get(); } set { _randomizeSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Effect>(owner);
		_landtemp = new UndoRedoDBPtr<LandTemp>( owner );
		_tranformedchild = new UndoRedoDBPtr<ChildEffect>( owner );
		_child = new UndoRedoDBPtr<Effect>( owner );
		_effects = new UndoRedoAssignableList<EffectInstance>( owner );
		_randomizePhase = new UndoRedo<bool>( owner, false );
		_randomizeSpeed = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_landtemp.Changed += FireChangedEvent;
		_tranformedchild.Changed += FireChangedEvent;
		_child.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_randomizePhase.Changed += FireChangedEvent;
		_randomizeSpeed.Changed += FireChangedEvent;
	}

	public Effect()
	{
		Initialize( this );
	}
	private void AssignSelf( Effect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Effect" );
		landtemp = source.landtemp;
		tranformedchild = source.tranformedchild;
		child = source.child;
		effects = source.effects;
		randomizePhase = source.randomizePhase;
		randomizeSpeed = source.randomizeSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Effect source = _source as Effect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Effect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Effect newParent = rawParent == null ? null : rawParent.Get<Effect>();
		if ( newParent == null && _newParent is Effect )
			newParent = _newParent as Effect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_landtemp.SetParent( newParent == null ? null : newParent._landtemp );
		_tranformedchild.SetParent( newParent == null ? null : newParent._tranformedchild );
		_child.SetParent( newParent == null ? null : newParent._child );
		_effects.SetParent( newParent == null ? null : newParent._effects );
		_randomizePhase.SetParent( newParent == null ? null : newParent._randomizePhase );
		_randomizeSpeed.SetParent( newParent == null ? null : newParent._randomizeSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_landtemp.Reset();
		_tranformedchild.Reset();
		_child.Reset();
		_effects.Reset();
		_randomizePhase.Reset();
		_randomizeSpeed.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_landtemp.IsDerivedFromParent()
			&& _tranformedchild.IsDerivedFromParent()
			&& _child.IsDerivedFromParent()
			&& _effects.IsDerivedFromParent()
			&& _randomizePhase.IsDerivedFromParent()
			&& _randomizeSpeed.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "landtemp" )
			_landtemp.Reset();
		else if ( fieldName == "tranformedchild" )
			_tranformedchild.Reset();
		else if ( fieldName == "child" )
			_child.Reset();
		else if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "randomizePhase" )
			_randomizePhase.Reset();
		else if ( fieldName == "randomizeSpeed" )
			_randomizeSpeed.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "landtemp" )
			return _landtemp.IsDerivedFromParent();
		if ( fieldName == "tranformedchild" )
			return _tranformedchild.IsDerivedFromParent();
		if ( fieldName == "child" )
			return _child.IsDerivedFromParent();
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "randomizePhase" )
			return _randomizePhase.IsDerivedFromParent();
		if ( fieldName == "randomizeSpeed" )
			return _randomizeSpeed.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[TypeId(0x9E5573C6)]
[UseTypeName("GMOB")]
public class GameObject : DBResource
{
	private UndoRedoDBPtr<GameObject> ___parent;
	[HideInOutliner]
	public new DBPtr<GameObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private FloatRect _collision;
	private ObjectLockMask _lockMask;
	private UndoRedo<float> _minLockScale;
	private UndoRedo<bool> _rounded;
	private UndoRedo<bool> _heightObject;

	[Description( "Relative 2D object bounds to lock map" )]
	public FloatRect collision { get { return _collision; } set { _collision.Assign( value ); } }

	[Description( "Precise mask to lock map" )]
	public ObjectLockMask lockMask { get { return _lockMask; } set { _lockMask.Assign( value ); } }

	[Description( "Threshold for object scale-dependent lock" )]
	public float minLockScale { get { return _minLockScale.Get(); } set { _minLockScale.Set( value ); } }

	[Description( "Allow rounding of object map lock" )]
	public bool rounded { get { return _rounded.Get(); } set { _rounded.Set( value ); } }

	public bool heightObject { get { return _heightObject.Get(); } set { _heightObject.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GameObject>(owner);
		_collision = new FloatRect( owner );
		_lockMask = new ObjectLockMask( owner );
		_minLockScale = new UndoRedo<float>( owner, 0.0f );
		_rounded = new UndoRedo<bool>( owner, false );
		_heightObject = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_collision.Changed += FireChangedEvent;
		_lockMask.Changed += FireChangedEvent;
		_minLockScale.Changed += FireChangedEvent;
		_rounded.Changed += FireChangedEvent;
		_heightObject.Changed += FireChangedEvent;
	}

	public GameObject()
	{
		Initialize( this );
	}
	private void AssignSelf( GameObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GameObject" );
		collision = source.collision;
		lockMask = source.lockMask;
		minLockScale = source.minLockScale;
		rounded = source.rounded;
		heightObject = source.heightObject;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GameObject source = _source as GameObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GameObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GameObject newParent = rawParent == null ? null : rawParent.Get<GameObject>();
		if ( newParent == null && _newParent is GameObject )
			newParent = _newParent as GameObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_collision.SetParent( newParent == null ? null : newParent._collision );
		_lockMask.SetParent( newParent == null ? null : newParent._lockMask );
		_minLockScale.SetParent( newParent == null ? null : newParent._minLockScale );
		_rounded.SetParent( newParent == null ? null : newParent._rounded );
		_heightObject.SetParent( newParent == null ? null : newParent._heightObject );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_collision.Reset();
		_lockMask.Reset();
		_minLockScale.Reset();
		_rounded.Reset();
		_heightObject.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_collision.IsDerivedFromParent()
			&& _lockMask.IsDerivedFromParent()
			&& _minLockScale.IsDerivedFromParent()
			&& _rounded.IsDerivedFromParent()
			&& _heightObject.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "collision" )
			_collision.Reset();
		else if ( fieldName == "lockMask" )
			_lockMask.Reset();
		else if ( fieldName == "minLockScale" )
			_minLockScale.Reset();
		else if ( fieldName == "rounded" )
			_rounded.Reset();
		else if ( fieldName == "heightObject" )
			_heightObject.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "collision" )
			return _collision.IsDerivedFromParent();
		if ( fieldName == "lockMask" )
			return _lockMask.IsDerivedFromParent();
		if ( fieldName == "minLockScale" )
			return _minLockScale.IsDerivedFromParent();
		if ( fieldName == "rounded" )
			return _rounded.IsDerivedFromParent();
		if ( fieldName == "heightObject" )
			return _heightObject.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("LNDT")]
public class LandTemp : DBResource
{
	private UndoRedoDBPtr<LandTemp> ___parent;
	[HideInOutliner]
	public new DBPtr<LandTemp> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _speed;
	private UndoRedo<int> _randomSeed;

	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	public int randomSeed { get { return _randomSeed.Get(); } set { _randomSeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LandTemp>(owner);
		_speed = new UndoRedo<float>( owner, 0.1f );
		_randomSeed = new UndoRedo<int>( owner, 50 );
		___parent.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_randomSeed.Changed += FireChangedEvent;
	}

	public LandTemp()
	{
		Initialize( this );
	}
	private void AssignSelf( LandTemp source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LandTemp" );
		speed = source.speed;
		randomSeed = source.randomSeed;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LandTemp source = _source as LandTemp;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LandTemp" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LandTemp newParent = rawParent == null ? null : rawParent.Get<LandTemp>();
		if ( newParent == null && _newParent is LandTemp )
			newParent = _newParent as LandTemp;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_speed.SetParent( newParent == null ? null : newParent._speed );
		_randomSeed.SetParent( newParent == null ? null : newParent._randomSeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_speed.Reset();
		_randomSeed.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_speed.IsDerivedFromParent()
			&& _randomSeed.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "randomSeed" )
			_randomSeed.Reset();
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
		if ( fieldName == "randomSeed" )
			return _randomSeed.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NoCode]
[TypeId(0x4964EAC0)]
[UseTypeName("PTLT")]
public class PointLightGameObject : DBResource
{
	private UndoRedoDBPtr<PointLightGameObject> ___parent;
	[HideInOutliner]
	public new DBPtr<PointLightGameObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PointLightGameObject>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public PointLightGameObject()
	{
		Initialize( this );
	}
	private void AssignSelf( PointLightGameObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PointLightGameObject" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PointLightGameObject source = _source as PointLightGameObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PointLightGameObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PointLightGameObject newParent = rawParent == null ? null : rawParent.Get<PointLightGameObject>();
		if ( newParent == null && _newParent is PointLightGameObject )
			newParent = _newParent as PointLightGameObject;
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

[TypeId(0xCB726281)]
[UseTypeName("ROAD")]
public class Road : GameObject
{
	private UndoRedoDBPtr<Road> ___parent;
	[HideInOutliner]
	public new DBPtr<Road> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<RoadControlPoint> _points;
	private RoadProperties _properties;

	[ReadOnly( true )]
	public libdb.IChangeableList<RoadControlPoint> points { get { return _points; } set { _points.Assign( value ); } }

	public RoadProperties properties { get { return _properties; } set { _properties.Assign( value ); } }

	[Description( "Сбейканные данные для ускорения загрузки игры" )]
	[DstFile("road")]
	public string bakedFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "road"
	); } }
	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Road>(owner);
		_points = new UndoRedoAssignableList<RoadControlPoint>( owner );
		_properties = new RoadProperties( owner );
		___parent.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		_properties.Changed += FireChangedEvent;
	}

	public Road()
	{
		Initialize( this );
	}
	private void AssignSelf( Road source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Road" );
		points = source.points;
		properties = source.properties;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Road source = _source as Road;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Road" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Road newParent = rawParent == null ? null : rawParent.Get<Road>();
		if ( newParent == null && _newParent is Road )
			newParent = _newParent as Road;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_points.SetParent( newParent == null ? null : newParent._points );
		_properties.SetParent( newParent == null ? null : newParent._properties );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_points.Reset();
		_properties.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_points.IsDerivedFromParent()
			&& _properties.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "points" )
			_points.Reset();
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
		if ( fieldName == "points" )
			return _points.IsDerivedFromParent();
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

[NoCode]
[TypeId(0xE7920C00)]
[UseTypeName("SCAR")]
public class ScriptAreaGameObject : GameObject
{
	private UndoRedoDBPtr<ScriptAreaGameObject> ___parent;
	[HideInOutliner]
	public new DBPtr<ScriptAreaGameObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScriptAreaGameObject>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public ScriptAreaGameObject()
	{
		Initialize( this );
	}
	private void AssignSelf( ScriptAreaGameObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScriptAreaGameObject" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScriptAreaGameObject source = _source as ScriptAreaGameObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptAreaGameObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScriptAreaGameObject newParent = rawParent == null ? null : rawParent.Get<ScriptAreaGameObject>();
		if ( newParent == null && _newParent is ScriptAreaGameObject )
			newParent = _newParent as ScriptAreaGameObject;
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

[TypeId(0xE7920C10)]
[UseTypeName("SPTH")]
public class ScriptPath : GameObject
{
	private UndoRedoDBPtr<ScriptPath> ___parent;
	[HideInOutliner]
	public new DBPtr<ScriptPath> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Vec2> _path;

	public libdb.IChangeableList<Vec2> path { get { return _path; } set { _path.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScriptPath>(owner);
		_path = new UndoRedoAssignableList<Vec2>( owner );
		___parent.Changed += FireChangedEvent;
		_path.Changed += FireChangedEvent;
	}

	public ScriptPath()
	{
		Initialize( this );
	}
	private void AssignSelf( ScriptPath source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScriptPath" );
		path = source.path;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScriptPath source = _source as ScriptPath;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptPath" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScriptPath newParent = rawParent == null ? null : rawParent.Get<ScriptPath>();
		if ( newParent == null && _newParent is ScriptPath )
			newParent = _newParent as ScriptPath;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_path.SetParent( newParent == null ? null : newParent._path );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_path.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_path.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "path" )
			_path.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "path" )
			return _path.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SoundSet : DBResource
{
	private UndoRedoDBPtr<SoundSet> ___parent;
	[HideInOutliner]
	public new DBPtr<SoundSet> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<SoundEffect> _sounds;
	private UndoRedo<int> _priority;

	public libdb.IChangeableList<SoundEffect> sounds { get { return _sounds; } set { _sounds.Assign( value ); } }

	[Description( "A priority which the Sound will be heared. 0 - most Important, 256 - least Imortant" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SoundSet>(owner);
		_sounds = new UndoRedoAssignableList<SoundEffect>( owner );
		_priority = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_sounds.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
	}

	public SoundSet()
	{
		Initialize( this );
	}
	private void AssignSelf( SoundSet source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SoundSet" );
		sounds = source.sounds;
		priority = source.priority;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SoundSet source = _source as SoundSet;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundSet" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SoundSet newParent = rawParent == null ? null : rawParent.Get<SoundSet>();
		if ( newParent == null && _newParent is SoundSet )
			newParent = _newParent as SoundSet;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sounds.SetParent( newParent == null ? null : newParent._sounds );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sounds.Reset();
		_priority.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sounds.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sounds" )
			_sounds.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sounds" )
			return _sounds.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SoundSRC : DBResource
{
	private UndoRedoDBPtr<SoundSRC> ___parent;
	[HideInOutliner]
	public new DBPtr<SoundSRC> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _soundFile;
	private SyncInfo _syncInfo;

	[FileRef("*.wav;*.mp3;*.ogg;*.flac")]
	public string soundFile { get { return _soundFile.Get(); } set { _soundFile.Set( value ); } }

	public SyncInfo syncInfo { get { return _syncInfo; } set { _syncInfo.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SoundSRC>(owner);
		_soundFile = new UndoRedo<string>( owner, string.Empty );
		_syncInfo = new SyncInfo( owner );
		___parent.Changed += FireChangedEvent;
		_soundFile.Changed += FireChangedEvent;
		_syncInfo.Changed += FireChangedEvent;
	}

	public SoundSRC()
	{
		Initialize( this );
	}
	private void AssignSelf( SoundSRC source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SoundSRC" );
		soundFile = source.soundFile;
		syncInfo = source.syncInfo;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SoundSRC source = _source as SoundSRC;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundSRC" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SoundSRC newParent = rawParent == null ? null : rawParent.Get<SoundSRC>();
		if ( newParent == null && _newParent is SoundSRC )
			newParent = _newParent as SoundSRC;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_soundFile.SetParent( newParent == null ? null : newParent._soundFile );
		_syncInfo.SetParent( newParent == null ? null : newParent._syncInfo );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_soundFile.Reset();
		_syncInfo.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_soundFile.IsDerivedFromParent()
			&& _syncInfo.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "soundFile" )
			_soundFile.Reset();
		else if ( fieldName == "syncInfo" )
			_syncInfo.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "soundFile" )
			return _soundFile.IsDerivedFromParent();
		if ( fieldName == "syncInfo" )
			return _syncInfo.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
