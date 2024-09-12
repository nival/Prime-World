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
public enum EAnimStatePlayMode
{
	PlayNormal = 0,
	PlayUpper = 1,
	PlayBoth = 2,
};

public enum EAnimStates
{
	Invalid = 0,
	Idle = 1,
	Stun = 2,
	Move = 3,
	BlockedMove = 4,
	Attack = 5,
	Ability1 = 6,
	Ability2 = 7,
	Ability3 = 8,
	Ability4 = 9,
	Death = 10,
	Resurrect = 11,
	Summon = 12,
	Unsummon = 13,
	Hello = 14,
	Happy = 15,
	Sad = 16,
	Minigaming = 17,
	Special1 = 18,
	Special2 = 19,
	Special3 = 20,
	Special4 = 21,
	Hide = 22,
};

public enum EEmotePermission
{
	PlayNone = 0,
	PlayUpper = 1,
	PlayLower = 2,
	PlayBoth = 3,
};

public enum EEmotion
{
	Happy = 0,
	Sad = 1,
	Hello = 2,
};

public class AnimStateDataNew : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimStateDataNew __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EAnimStates> _animState;
	private UndoRedo<string> _node;
	private UndoRedo<string> _marker;

	public EAnimStates animState { get { return _animState.Get(); } set { _animState.Set( value ); } }

	public string node { get { return _node.Get(); } set { _node.Set( value ); } }

	public string marker { get { return _marker.Get(); } set { _marker.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_animState = new UndoRedo<EAnimStates>( owner, EAnimStates.Invalid );
		_node = new UndoRedo<string>( owner, string.Empty );
		_marker = new UndoRedo<string>( owner, string.Empty );
		_animState.Changed += FireChangedEvent;
		_node.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
	}

	public AnimStateDataNew()
	{
		Initialize( GetOwner() );
	}

	public AnimStateDataNew( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimStateDataNew( DBResource owner, AnimStateDataNew source )
		: this(owner, source, true){}

	protected AnimStateDataNew( DBResource owner, AnimStateDataNew source, bool fireEvent )
	{
		_animState = new UndoRedo<EAnimStates>( owner, source.animState );
		_node = new UndoRedo<string>( owner, source.node );
		_marker = new UndoRedo<string>( owner, source.marker );
		_animState.Changed += FireChangedEvent;
		_node.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimStateDataNew source = _source as AnimStateDataNew;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimStateDataNew" );
		animState = source.animState;
		node = source.node;
		marker = source.marker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimStateDataNew newParent = _newParent as AnimStateDataNew;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_animState.SetParent( newParent == null ? null : newParent._animState );
		_node.SetParent( newParent == null ? null : newParent._node );
		_marker.SetParent( newParent == null ? null : newParent._marker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_animState.Reset();
		_node.Reset();
		_marker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_animState.IsDerivedFromParent()
			&& _node.IsDerivedFromParent()
			&& _marker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "animState" )
			_animState.Reset();
		else if ( fieldName == "node" )
			_node.Reset();
		else if ( fieldName == "marker" )
			_marker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "animState" )
			return _animState.IsDerivedFromParent();
		if ( fieldName == "node" )
			return _node.IsDerivedFromParent();
		if ( fieldName == "marker" )
			return _marker.IsDerivedFromParent();
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

public class AnimStateData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimStateData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _commonNode;
	private UndoRedo<string> _upperNode;
	private UndoRedo<EAnimStatePlayMode> _playMode;
	private UndoRedo<string> _commonMarker;
	private UndoRedo<string> _upperMarker;

	public string commonNode { get { return _commonNode.Get(); } set { _commonNode.Set( value ); } }

	public string upperNode { get { return _upperNode.Get(); } set { _upperNode.Set( value ); } }

	public EAnimStatePlayMode playMode { get { return _playMode.Get(); } set { _playMode.Set( value ); } }

	public string commonMarker { get { return _commonMarker.Get(); } set { _commonMarker.Set( value ); } }

	public string upperMarker { get { return _upperMarker.Get(); } set { _upperMarker.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_commonNode = new UndoRedo<string>( owner, string.Empty );
		_upperNode = new UndoRedo<string>( owner, string.Empty );
		_playMode = new UndoRedo<EAnimStatePlayMode>( owner, EAnimStatePlayMode.PlayBoth );
		_commonMarker = new UndoRedo<string>( owner, string.Empty );
		_upperMarker = new UndoRedo<string>( owner, string.Empty );
		_commonNode.Changed += FireChangedEvent;
		_upperNode.Changed += FireChangedEvent;
		_playMode.Changed += FireChangedEvent;
		_commonMarker.Changed += FireChangedEvent;
		_upperMarker.Changed += FireChangedEvent;
	}

	public AnimStateData()
	{
		Initialize( GetOwner() );
	}

	public AnimStateData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimStateData( DBResource owner, AnimStateData source )
		: this(owner, source, true){}

	protected AnimStateData( DBResource owner, AnimStateData source, bool fireEvent )
	{
		_commonNode = new UndoRedo<string>( owner, source.commonNode );
		_upperNode = new UndoRedo<string>( owner, source.upperNode );
		_playMode = new UndoRedo<EAnimStatePlayMode>( owner, source.playMode );
		_commonMarker = new UndoRedo<string>( owner, source.commonMarker );
		_upperMarker = new UndoRedo<string>( owner, source.upperMarker );
		_commonNode.Changed += FireChangedEvent;
		_upperNode.Changed += FireChangedEvent;
		_playMode.Changed += FireChangedEvent;
		_commonMarker.Changed += FireChangedEvent;
		_upperMarker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimStateData source = _source as AnimStateData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimStateData" );
		commonNode = source.commonNode;
		upperNode = source.upperNode;
		playMode = source.playMode;
		commonMarker = source.commonMarker;
		upperMarker = source.upperMarker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimStateData newParent = _newParent as AnimStateData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_commonNode.SetParent( newParent == null ? null : newParent._commonNode );
		_upperNode.SetParent( newParent == null ? null : newParent._upperNode );
		_playMode.SetParent( newParent == null ? null : newParent._playMode );
		_commonMarker.SetParent( newParent == null ? null : newParent._commonMarker );
		_upperMarker.SetParent( newParent == null ? null : newParent._upperMarker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_commonNode.Reset();
		_upperNode.Reset();
		_playMode.Reset();
		_commonMarker.Reset();
		_upperMarker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_commonNode.IsDerivedFromParent()
			&& _upperNode.IsDerivedFromParent()
			&& _playMode.IsDerivedFromParent()
			&& _commonMarker.IsDerivedFromParent()
			&& _upperMarker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "commonNode" )
			_commonNode.Reset();
		else if ( fieldName == "upperNode" )
			_upperNode.Reset();
		else if ( fieldName == "playMode" )
			_playMode.Reset();
		else if ( fieldName == "commonMarker" )
			_commonMarker.Reset();
		else if ( fieldName == "upperMarker" )
			_upperMarker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "commonNode" )
			return _commonNode.IsDerivedFromParent();
		if ( fieldName == "upperNode" )
			return _upperNode.IsDerivedFromParent();
		if ( fieldName == "playMode" )
			return _playMode.IsDerivedFromParent();
		if ( fieldName == "commonMarker" )
			return _commonMarker.IsDerivedFromParent();
		if ( fieldName == "upperMarker" )
			return _upperMarker.IsDerivedFromParent();
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

[IndexField("caption")]
public class AnimStateChanger : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimStateChanger __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private AnimStateDataNew _oldAnimation;
	private AnimStateDataNew _newAnimation;
	private UndoRedo<string> _caption;

	public AnimStateDataNew oldAnimation { get { return _oldAnimation; } set { _oldAnimation.Assign( value ); } }

	public AnimStateDataNew newAnimation { get { return _newAnimation; } set { _newAnimation.Assign( value ); } }

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_oldAnimation = new AnimStateDataNew( owner );
		_newAnimation = new AnimStateDataNew( owner );
		_caption = new UndoRedo<string>( owner, string.Empty );
		_oldAnimation.Changed += FireChangedEvent;
		_newAnimation.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
	}

	public AnimStateChanger()
	{
		Initialize( GetOwner() );
	}

	public AnimStateChanger( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimStateChanger( DBResource owner, AnimStateChanger source )
		: this(owner, source, true){}

	protected AnimStateChanger( DBResource owner, AnimStateChanger source, bool fireEvent )
	{
		_oldAnimation = new AnimStateDataNew( owner, source.oldAnimation );
		_newAnimation = new AnimStateDataNew( owner, source.newAnimation );
		_caption = new UndoRedo<string>( owner, source.caption );
		_oldAnimation.Changed += FireChangedEvent;
		_newAnimation.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimStateChanger source = _source as AnimStateChanger;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimStateChanger" );
		oldAnimation = source.oldAnimation;
		newAnimation = source.newAnimation;
		caption = source.caption;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimStateChanger newParent = _newParent as AnimStateChanger;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_oldAnimation.SetParent( newParent == null ? null : newParent._oldAnimation );
		_newAnimation.SetParent( newParent == null ? null : newParent._newAnimation );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_oldAnimation.Reset();
		_newAnimation.Reset();
		_caption.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_oldAnimation.IsDerivedFromParent()
			&& _newAnimation.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "oldAnimation" )
			_oldAnimation.Reset();
		else if ( fieldName == "newAnimation" )
			_newAnimation.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "oldAnimation" )
			return _oldAnimation.IsDerivedFromParent();
		if ( fieldName == "newAnimation" )
			return _newAnimation.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
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

public class EmotePlayNodeParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EmotePlayNodeParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<EEmotePermission> _permissions;

	[EnumArray(typeof(EEmotion))]
	public libdb.IChangeableList<EEmotePermission> permissions { get { return _permissions; } set { _permissions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_permissions = new UndoRedoList<EEmotePermission>( owner, typeof( EEmotion ) );
		_permissions.Changed += FireChangedEvent;
	}

	public EmotePlayNodeParams()
	{
		Initialize( GetOwner() );
	}

	public EmotePlayNodeParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EmotePlayNodeParams( DBResource owner, EmotePlayNodeParams source )
		: this(owner, source, true){}

	protected EmotePlayNodeParams( DBResource owner, EmotePlayNodeParams source, bool fireEvent )
	{
		_permissions = new UndoRedoList<EEmotePermission>( owner, typeof( EEmotion ) );
		_permissions.Assign( source.permissions );
		_permissions.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EmotePlayNodeParams source = _source as EmotePlayNodeParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EmotePlayNodeParams" );
		permissions = source.permissions;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EmotePlayNodeParams newParent = _newParent as EmotePlayNodeParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_permissions.SetParent( newParent == null ? null : newParent._permissions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_permissions.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_permissions.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "permissions" )
			_permissions.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "permissions" )
			return _permissions.IsDerivedFromParent();
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

[UseTypeName("ANS")]
public class AnimSet : DBResource
{
	private UndoRedoDBPtr<AnimSet> ___parent;
	[HideInOutliner]
	public new DBPtr<AnimSet> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<AnimStateData> _states;

	[EnumArray(typeof(EAnimStates))]
	public libdb.IChangeableList<AnimStateData> states { get { return _states; } set { _states.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AnimSet>(owner);
		_states = new UndoRedoAssignableList<AnimStateData>( owner, typeof( EAnimStates ) );
		___parent.Changed += FireChangedEvent;
		_states.Changed += FireChangedEvent;
	}

	public AnimSet()
	{
		Initialize( this );
	}
	private void AssignSelf( AnimSet source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AnimSet" );
		states = source.states;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AnimSet source = _source as AnimSet;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimSet" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AnimSet newParent = rawParent == null ? null : rawParent.Get<AnimSet>();
		if ( newParent == null && _newParent is AnimSet )
			newParent = _newParent as AnimSet;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_states.SetParent( newParent == null ? null : newParent._states );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_states.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_states.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "states" )
			_states.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "states" )
			return _states.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("EMO")]
public class EmoteSettings : DBResource
{
	private UndoRedoDBPtr<EmoteSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<EmoteSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<EmotePlayNodeParams> _nodes;

	[EnumArray(typeof(EAnimStates))]
	public libdb.IChangeableList<EmotePlayNodeParams> nodes { get { return _nodes; } set { _nodes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EmoteSettings>(owner);
		_nodes = new UndoRedoAssignableList<EmotePlayNodeParams>( owner, typeof( EAnimStates ) );
		___parent.Changed += FireChangedEvent;
		_nodes.Changed += FireChangedEvent;
	}

	public EmoteSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( EmoteSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EmoteSettings" );
		nodes = source.nodes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EmoteSettings source = _source as EmoteSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EmoteSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EmoteSettings newParent = rawParent == null ? null : rawParent.Get<EmoteSettings>();
		if ( newParent == null && _newParent is EmoteSettings )
			newParent = _newParent as EmoteSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_nodes.SetParent( newParent == null ? null : newParent._nodes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_nodes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_nodes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "nodes" )
			_nodes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "nodes" )
			return _nodes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
