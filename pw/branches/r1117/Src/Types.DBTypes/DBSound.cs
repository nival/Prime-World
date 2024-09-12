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
public enum EAskSounds
{
	MOVE = 0,
	ABILITY_1 = 1,
	ABILITY_2 = 2,
	ABILITY_3 = 3,
	ABILITY_ULT = 4,
	ATTACK = 5,
	DEATH = 6,
	REVIVE = 7,
	KILL = 8,
	IDLE = 9,
	RAISEFLAG = 10,
	KILLCHAMPION = 11,
	MINIGAMEWIN = 12,
	MINIGAMEFAIL = 13,
};

public enum SoundCameraType
{
	TopDown = 0,
	Perspective = 1,
};

public class DBFMODEventDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBFMODEventDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _projectName;
	private UndoRedo<string> _groupName;
	private UndoRedo<string> _eventName;

	[Description( "Project name" )]
	public string projectName { get { return _projectName.Get(); } set { _projectName.Set( value ); } }

	[Description( "Group name" )]
	public string groupName { get { return _groupName.Get(); } set { _groupName.Set( value ); } }

	[Description( "Event name" )]
	public string eventName { get { return _eventName.Get(); } set { _eventName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_projectName = new UndoRedo<string>( owner, string.Empty );
		_groupName = new UndoRedo<string>( owner, string.Empty );
		_eventName = new UndoRedo<string>( owner, string.Empty );
		_projectName.Changed += FireChangedEvent;
		_groupName.Changed += FireChangedEvent;
		_eventName.Changed += FireChangedEvent;
	}

	public DBFMODEventDesc()
	{
		Initialize( GetOwner() );
	}

	public DBFMODEventDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBFMODEventDesc( DBResource owner, DBFMODEventDesc source )
		: this(owner, source, true){}

	protected DBFMODEventDesc( DBResource owner, DBFMODEventDesc source, bool fireEvent )
	{
		_projectName = new UndoRedo<string>( owner, source.projectName );
		_groupName = new UndoRedo<string>( owner, source.groupName );
		_eventName = new UndoRedo<string>( owner, source.eventName );
		_projectName.Changed += FireChangedEvent;
		_groupName.Changed += FireChangedEvent;
		_eventName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBFMODEventDesc source = _source as DBFMODEventDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBFMODEventDesc" );
		projectName = source.projectName;
		groupName = source.groupName;
		eventName = source.eventName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBFMODEventDesc newParent = _newParent as DBFMODEventDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_projectName.SetParent( newParent == null ? null : newParent._projectName );
		_groupName.SetParent( newParent == null ? null : newParent._groupName );
		_eventName.SetParent( newParent == null ? null : newParent._eventName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_projectName.Reset();
		_groupName.Reset();
		_eventName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_projectName.IsDerivedFromParent()
			&& _groupName.IsDerivedFromParent()
			&& _eventName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "projectName" )
			_projectName.Reset();
		else if ( fieldName == "groupName" )
			_groupName.Reset();
		else if ( fieldName == "eventName" )
			_eventName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "projectName" )
			return _projectName.IsDerivedFromParent();
		if ( fieldName == "groupName" )
			return _groupName.IsDerivedFromParent();
		if ( fieldName == "eventName" )
			return _eventName.IsDerivedFromParent();
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

public class FMODEvent : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FMODEvent __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_name.Changed += FireChangedEvent;
	}

	public FMODEvent()
	{
		Initialize( GetOwner() );
	}

	public FMODEvent( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FMODEvent( DBResource owner, FMODEvent source )
		: this(owner, source, true){}

	protected FMODEvent( DBResource owner, FMODEvent source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_name.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FMODEvent source = _source as FMODEvent;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FMODEvent" );
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FMODEvent newParent = _newParent as FMODEvent;
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

public class FMODEventGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FMODEventGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedoAssignableList<FMODEventGroup> _groups;
	private UndoRedoAssignableList<FMODEvent> _events;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public libdb.IChangeableList<FMODEventGroup> groups { get { return _groups; } set { _groups.Assign( value ); } }

	public libdb.IChangeableList<FMODEvent> events { get { return _events; } set { _events.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_groups = new UndoRedoAssignableList<FMODEventGroup>( owner );
		_events = new UndoRedoAssignableList<FMODEvent>( owner );
		_name.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
	}

	public FMODEventGroup()
	{
		Initialize( GetOwner() );
	}

	public FMODEventGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FMODEventGroup( DBResource owner, FMODEventGroup source )
		: this(owner, source, true){}

	protected FMODEventGroup( DBResource owner, FMODEventGroup source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_groups = new UndoRedoAssignableList<FMODEventGroup>( owner );
		_groups.Assign( source.groups );
		_events = new UndoRedoAssignableList<FMODEvent>( owner );
		_events.Assign( source.events );
		_name.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FMODEventGroup source = _source as FMODEventGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FMODEventGroup" );
		name = source.name;
		groups = source.groups;
		events = source.events;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FMODEventGroup newParent = _newParent as FMODEventGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_groups.SetParent( newParent == null ? null : newParent._groups );
		_events.SetParent( newParent == null ? null : newParent._events );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_groups.Reset();
		_events.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _groups.IsDerivedFromParent()
			&& _events.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "groups" )
			_groups.Reset();
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
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
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

public class FMODGroupInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FMODGroupInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<FMODEventProject> _project;
	private UndoRedo<string> _fmodGroup;

	public DBPtr<FMODEventProject> project { get { return _project.Get(); } set { _project.Set( value ); } }

	public string fmodGroup { get { return _fmodGroup.Get(); } set { _fmodGroup.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_project = new UndoRedoDBPtr<FMODEventProject>( owner );
		_fmodGroup = new UndoRedo<string>( owner, string.Empty );
		_project.Changed += FireChangedEvent;
		_fmodGroup.Changed += FireChangedEvent;
	}

	public FMODGroupInstance()
	{
		Initialize( GetOwner() );
	}

	public FMODGroupInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FMODGroupInstance( DBResource owner, FMODGroupInstance source )
		: this(owner, source, true){}

	protected FMODGroupInstance( DBResource owner, FMODGroupInstance source, bool fireEvent )
	{
		_project = new UndoRedoDBPtr<FMODEventProject>( owner, source.project );
		_fmodGroup = new UndoRedo<string>( owner, source.fmodGroup );
		_project.Changed += FireChangedEvent;
		_fmodGroup.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FMODGroupInstance source = _source as FMODGroupInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FMODGroupInstance" );
		project = source.project;
		fmodGroup = source.fmodGroup;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FMODGroupInstance newParent = _newParent as FMODGroupInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_project.SetParent( newParent == null ? null : newParent._project );
		_fmodGroup.SetParent( newParent == null ? null : newParent._fmodGroup );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_project.Reset();
		_fmodGroup.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_project.IsDerivedFromParent()
			&& _fmodGroup.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "project" )
			_project.Reset();
		else if ( fieldName == "fmodGroup" )
			_fmodGroup.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "project" )
			return _project.IsDerivedFromParent();
		if ( fieldName == "fmodGroup" )
			return _fmodGroup.IsDerivedFromParent();
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

public class FMODEventInstance : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FMODEventInstance __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private FMODGroupInstance _fmodGroup;
	private UndoRedo<string> _name;

	public FMODGroupInstance fmodGroup { get { return _fmodGroup; } set { _fmodGroup.Assign( value ); } }

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_fmodGroup = new FMODGroupInstance( owner );
		_name = new UndoRedo<string>( owner, string.Empty );
		_fmodGroup.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public FMODEventInstance()
	{
		Initialize( GetOwner() );
	}

	public FMODEventInstance( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FMODEventInstance( DBResource owner, FMODEventInstance source )
		: this(owner, source, true){}

	protected FMODEventInstance( DBResource owner, FMODEventInstance source, bool fireEvent )
	{
		_fmodGroup = new FMODGroupInstance( owner, source.fmodGroup );
		_name = new UndoRedo<string>( owner, source.name );
		_fmodGroup.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FMODEventInstance source = _source as FMODEventInstance;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FMODEventInstance" );
		fmodGroup = source.fmodGroup;
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FMODEventInstance newParent = _newParent as FMODEventInstance;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_fmodGroup.SetParent( newParent == null ? null : newParent._fmodGroup );
		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_fmodGroup.Reset();
		_name.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_fmodGroup.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "fmodGroup" )
			_fmodGroup.Reset();
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
		if ( fieldName == "fmodGroup" )
			return _fmodGroup.IsDerivedFromParent();
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

public class MusicDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MusicDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _cueName;

	public string cueName { get { return _cueName.Get(); } set { _cueName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_cueName = new UndoRedo<string>( owner, string.Empty );
		_cueName.Changed += FireChangedEvent;
	}

	public MusicDesc()
	{
		Initialize( GetOwner() );
	}

	public MusicDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MusicDesc( DBResource owner, MusicDesc source )
		: this(owner, source, true){}

	protected MusicDesc( DBResource owner, MusicDesc source, bool fireEvent )
	{
		_cueName = new UndoRedo<string>( owner, source.cueName );
		_cueName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MusicDesc source = _source as MusicDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MusicDesc" );
		cueName = source.cueName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MusicDesc newParent = _newParent as MusicDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cueName.SetParent( newParent == null ? null : newParent._cueName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cueName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cueName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cueName" )
			_cueName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "cueName" )
			return _cueName.IsDerivedFromParent();
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
public class SoundAmbienceMap : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundAmbienceMap __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Texture> _texture;
	private UndoRedo<float> _radius;
	private UndoRedo<float> _directivity;

	[Description( "Текстурная карта с областями, обозначающими различные звуки окружения в данной местности (см. документацию)." )]
	public DBPtr<Texture> texture { get { return _texture.Get(); } set { _texture.Set( value ); } }

	[Description( "Радиус осреднения текстурной карты для определения пропорций звуков окружения, в метрах вокруг слушателя (камеры)." )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Description( "Направленность ушей слушателя, т.е. зависимость сдвига осреднения от направления взгляда, в долях от радиуса. Ноль = нет направленности." )]
	public float directivity { get { return _directivity.Get(); } set { _directivity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_texture = new UndoRedoDBPtr<Texture>( owner );
		_radius = new UndoRedo<float>( owner, 30.0f );
		_directivity = new UndoRedo<float>( owner, 0.5f );
		_texture.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_directivity.Changed += FireChangedEvent;
	}

	public SoundAmbienceMap()
	{
		Initialize( GetOwner() );
	}

	public SoundAmbienceMap( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundAmbienceMap( DBResource owner, SoundAmbienceMap source )
		: this(owner, source, true){}

	protected SoundAmbienceMap( DBResource owner, SoundAmbienceMap source, bool fireEvent )
	{
		_texture = new UndoRedoDBPtr<Texture>( owner, source.texture );
		_radius = new UndoRedo<float>( owner, source.radius );
		_directivity = new UndoRedo<float>( owner, source.directivity );
		_texture.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_directivity.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundAmbienceMap source = _source as SoundAmbienceMap;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundAmbienceMap" );
		texture = source.texture;
		radius = source.radius;
		directivity = source.directivity;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundAmbienceMap newParent = _newParent as SoundAmbienceMap;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_texture.SetParent( newParent == null ? null : newParent._texture );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_directivity.SetParent( newParent == null ? null : newParent._directivity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_texture.Reset();
		_radius.Reset();
		_directivity.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_texture.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _directivity.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "texture" )
			_texture.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "directivity" )
			_directivity.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "texture" )
			return _texture.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "directivity" )
			return _directivity.IsDerivedFromParent();
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

public class SoundCamera : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundCamera __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<SoundCameraType> _type;
	private UndoRedo<float> _multiplier;

	public SoundCameraType type { get { return _type.Get(); } set { _type.Set( value ); } }

	public float multiplier { get { return _multiplier.Get(); } set { _multiplier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_type = new UndoRedo<SoundCameraType>( owner, SoundCameraType.Perspective );
		_multiplier = new UndoRedo<float>( owner, 1.0f );
		_type.Changed += FireChangedEvent;
		_multiplier.Changed += FireChangedEvent;
	}

	public SoundCamera()
	{
		Initialize( GetOwner() );
	}

	public SoundCamera( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundCamera( DBResource owner, SoundCamera source )
		: this(owner, source, true){}

	protected SoundCamera( DBResource owner, SoundCamera source, bool fireEvent )
	{
		_type = new UndoRedo<SoundCameraType>( owner, source.type );
		_multiplier = new UndoRedo<float>( owner, source.multiplier );
		_type.Changed += FireChangedEvent;
		_multiplier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundCamera source = _source as SoundCamera;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundCamera" );
		type = source.type;
		multiplier = source.multiplier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundCamera newParent = _newParent as SoundCamera;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_type.SetParent( newParent == null ? null : newParent._type );
		_multiplier.SetParent( newParent == null ? null : newParent._multiplier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_type.Reset();
		_multiplier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _multiplier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "multiplier" )
			_multiplier.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "multiplier" )
			return _multiplier.IsDerivedFromParent();
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

public class SoundSceneGroupDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundSceneGroupDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _categoryName;
	private UndoRedo<float> _pitch;
	private AnimatedFloat _volume;

	public string categoryName { get { return _categoryName.Get(); } set { _categoryName.Set( value ); } }

	public float pitch { get { return _pitch.Get(); } set { _pitch.Set( value ); } }

	public AnimatedFloat volume { get { return _volume; } set { _volume.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_categoryName = new UndoRedo<string>( owner, string.Empty );
		_pitch = new UndoRedo<float>( owner, 0.0f );
		_volume = new AnimatedFloat( owner );
		_categoryName.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
	}

	public SoundSceneGroupDesc()
	{
		Initialize( GetOwner() );
	}

	public SoundSceneGroupDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundSceneGroupDesc( DBResource owner, SoundSceneGroupDesc source )
		: this(owner, source, true){}

	protected SoundSceneGroupDesc( DBResource owner, SoundSceneGroupDesc source, bool fireEvent )
	{
		_categoryName = new UndoRedo<string>( owner, source.categoryName );
		_pitch = new UndoRedo<float>( owner, source.pitch );
		_volume = new AnimatedFloat( owner, source.volume );
		_categoryName.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundSceneGroupDesc source = _source as SoundSceneGroupDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundSceneGroupDesc" );
		categoryName = source.categoryName;
		pitch = source.pitch;
		volume = source.volume;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundSceneGroupDesc newParent = _newParent as SoundSceneGroupDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_categoryName.SetParent( newParent == null ? null : newParent._categoryName );
		_pitch.SetParent( newParent == null ? null : newParent._pitch );
		_volume.SetParent( newParent == null ? null : newParent._volume );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_categoryName.Reset();
		_pitch.Reset();
		_volume.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_categoryName.IsDerivedFromParent()
			&& _pitch.IsDerivedFromParent()
			&& _volume.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "categoryName" )
			_categoryName.Reset();
		else if ( fieldName == "pitch" )
			_pitch.Reset();
		else if ( fieldName == "volume" )
			_volume.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "categoryName" )
			return _categoryName.IsDerivedFromParent();
		if ( fieldName == "pitch" )
			return _pitch.IsDerivedFromParent();
		if ( fieldName == "volume" )
			return _volume.IsDerivedFromParent();
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

public class SoundSceneDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundSceneDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<SoundSceneGroupDesc> _soundSceneGroups;
	private MusicDesc _cue;

	public libdb.IChangeableList<SoundSceneGroupDesc> soundSceneGroups { get { return _soundSceneGroups; } set { _soundSceneGroups.Assign( value ); } }

	public MusicDesc cue { get { return _cue; } set { _cue.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_soundSceneGroups = new UndoRedoAssignableList<SoundSceneGroupDesc>( owner );
		_cue = new MusicDesc( owner );
		_soundSceneGroups.Changed += FireChangedEvent;
		_cue.Changed += FireChangedEvent;
	}

	public SoundSceneDesc()
	{
		Initialize( GetOwner() );
	}

	public SoundSceneDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundSceneDesc( DBResource owner, SoundSceneDesc source )
		: this(owner, source, true){}

	protected SoundSceneDesc( DBResource owner, SoundSceneDesc source, bool fireEvent )
	{
		_soundSceneGroups = new UndoRedoAssignableList<SoundSceneGroupDesc>( owner );
		_soundSceneGroups.Assign( source.soundSceneGroups );
		_cue = new MusicDesc( owner, source.cue );
		_soundSceneGroups.Changed += FireChangedEvent;
		_cue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundSceneDesc source = _source as SoundSceneDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundSceneDesc" );
		soundSceneGroups = source.soundSceneGroups;
		cue = source.cue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundSceneDesc newParent = _newParent as SoundSceneDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_soundSceneGroups.SetParent( newParent == null ? null : newParent._soundSceneGroups );
		_cue.SetParent( newParent == null ? null : newParent._cue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_soundSceneGroups.Reset();
		_cue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_soundSceneGroups.IsDerivedFromParent()
			&& _cue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "soundSceneGroups" )
			_soundSceneGroups.Reset();
		else if ( fieldName == "cue" )
			_cue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "soundSceneGroups" )
			return _soundSceneGroups.IsDerivedFromParent();
		if ( fieldName == "cue" )
			return _cue.IsDerivedFromParent();
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

public class FMODEventProject : DBResource
{
	private UndoRedoDBPtr<FMODEventProject> ___parent;
	[HideInOutliner]
	public new DBPtr<FMODEventProject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;
	private UndoRedoAssignableList<FMODEventGroup> _groups;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public libdb.IChangeableList<FMODEventGroup> groups { get { return _groups; } set { _groups.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FMODEventProject>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		_groups = new UndoRedoAssignableList<FMODEventGroup>( owner );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
	}

	public FMODEventProject()
	{
		Initialize( this );
	}
	private void AssignSelf( FMODEventProject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FMODEventProject" );
		name = source.name;
		groups = source.groups;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FMODEventProject source = _source as FMODEventProject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FMODEventProject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FMODEventProject newParent = rawParent == null ? null : rawParent.Get<FMODEventProject>();
		if ( newParent == null && _newParent is FMODEventProject )
			newParent = _newParent as FMODEventProject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_groups.SetParent( newParent == null ? null : newParent._groups );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_groups.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _groups.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "groups" )
			_groups.Reset();
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
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class Sound2D : DBResource
{
	private UndoRedoDBPtr<Sound2D> ___parent;
	[HideInOutliner]
	public new DBPtr<Sound2D> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _soundFile;
	private UndoRedo<float> _offset;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<float> _volume;

	[FileRef("*.wav;*.mp3;*.ogg")]
	public string soundFile { get { return _soundFile.Get(); } set { _soundFile.Set( value ); } }

	[Description( "(sec.) pause before playback start" )]
	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	[Description( "Number of playback cycles (0 = infinite)" )]
	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	[Description( "Sound volume" )]
	public float volume { get { return _volume.Get(); } set { _volume.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Sound2D>(owner);
		_soundFile = new UndoRedo<string>( owner, string.Empty );
		_offset = new UndoRedo<float>( owner, 0.0f );
		_cycleCount = new UndoRedo<int>( owner, 1 );
		_volume = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_soundFile.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
	}

	public Sound2D()
	{
		Initialize( this );
	}
	private void AssignSelf( Sound2D source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Sound2D" );
		soundFile = source.soundFile;
		offset = source.offset;
		cycleCount = source.cycleCount;
		volume = source.volume;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Sound2D source = _source as Sound2D;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Sound2D" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Sound2D newParent = rawParent == null ? null : rawParent.Get<Sound2D>();
		if ( newParent == null && _newParent is Sound2D )
			newParent = _newParent as Sound2D;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_soundFile.SetParent( newParent == null ? null : newParent._soundFile );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_volume.SetParent( newParent == null ? null : newParent._volume );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_soundFile.Reset();
		_offset.Reset();
		_cycleCount.Reset();
		_volume.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_soundFile.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _volume.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "soundFile" )
			_soundFile.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "volume" )
			_volume.Reset();
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
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "volume" )
			return _volume.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
public class SoundEnvironment : DBResource
{
	private UndoRedoDBPtr<SoundEnvironment> ___parent;
	[HideInOutliner]
	public new DBPtr<SoundEnvironment> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _language;
	private SoundCamera _soundCamera;
	private UndoRedoList<string> _fevFiles;
	private UndoRedoList<string> _banks;

	[Description( "Sound language" )]
	public TextRef language { get { return _language; } set { _language.Assign( value ); } }

	public SoundCamera soundCamera { get { return _soundCamera; } set { _soundCamera.Assign( value ); } }

	public libdb.IChangeableList<string> fevFiles { get { return _fevFiles; } set { _fevFiles.Assign( value ); } }

	public libdb.IChangeableList<string> banks { get { return _banks; } set { _banks.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SoundEnvironment>(owner);
		_language = new TextRef( owner, new TextRef() );
		_soundCamera = new SoundCamera( owner );
		_fevFiles = new UndoRedoList<string>( owner );
		_banks = new UndoRedoList<string>( owner );
		___parent.Changed += FireChangedEvent;
		_language.Changed += FireChangedEvent;
		_soundCamera.Changed += FireChangedEvent;
		_fevFiles.Changed += FireChangedEvent;
		_banks.Changed += FireChangedEvent;
	}

	public SoundEnvironment()
	{
		Initialize( this );
	}
	private void AssignSelf( SoundEnvironment source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SoundEnvironment" );
		language = source.language;
		soundCamera = source.soundCamera;
		fevFiles = source.fevFiles;
		banks = source.banks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SoundEnvironment source = _source as SoundEnvironment;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundEnvironment" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SoundEnvironment newParent = rawParent == null ? null : rawParent.Get<SoundEnvironment>();
		if ( newParent == null && _newParent is SoundEnvironment )
			newParent = _newParent as SoundEnvironment;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_language.SetParent( newParent == null ? null : newParent._language );
		_soundCamera.SetParent( newParent == null ? null : newParent._soundCamera );
		_fevFiles.SetParent( newParent == null ? null : newParent._fevFiles );
		_banks.SetParent( newParent == null ? null : newParent._banks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_language.Reset();
		_soundCamera.Reset();
		_fevFiles.Reset();
		_banks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_language.IsDerivedFromParent()
			&& _soundCamera.IsDerivedFromParent()
			&& _fevFiles.IsDerivedFromParent()
			&& _banks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "language" )
			_language.Reset();
		else if ( fieldName == "soundCamera" )
			_soundCamera.Reset();
		else if ( fieldName == "fevFiles" )
			_fevFiles.Reset();
		else if ( fieldName == "banks" )
			_banks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "language" )
			return _language.IsDerivedFromParent();
		if ( fieldName == "soundCamera" )
			return _soundCamera.IsDerivedFromParent();
		if ( fieldName == "fevFiles" )
			return _fevFiles.IsDerivedFromParent();
		if ( fieldName == "banks" )
			return _banks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SoundStream : DBResource
{
	private UndoRedoDBPtr<SoundStream> ___parent;
	[HideInOutliner]
	public new DBPtr<SoundStream> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _soundFile;
	private UndoRedo<int> _cycleCount;
	private UndoRedo<float> _volume;

	[FileRef("*.wav;*.mp3;*.ogg")]
	public string soundFile { get { return _soundFile.Get(); } set { _soundFile.Set( value ); } }

	[Description( "Number of playback cycles (0 = infinite)" )]
	public int cycleCount { get { return _cycleCount.Get(); } set { _cycleCount.Set( value ); } }

	[Description( "Sound volume" )]
	public float volume { get { return _volume.Get(); } set { _volume.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SoundStream>(owner);
		_soundFile = new UndoRedo<string>( owner, string.Empty );
		_cycleCount = new UndoRedo<int>( owner, 0 );
		_volume = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_soundFile.Changed += FireChangedEvent;
		_cycleCount.Changed += FireChangedEvent;
		_volume.Changed += FireChangedEvent;
	}

	public SoundStream()
	{
		Initialize( this );
	}
	private void AssignSelf( SoundStream source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SoundStream" );
		soundFile = source.soundFile;
		cycleCount = source.cycleCount;
		volume = source.volume;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SoundStream source = _source as SoundStream;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundStream" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SoundStream newParent = rawParent == null ? null : rawParent.Get<SoundStream>();
		if ( newParent == null && _newParent is SoundStream )
			newParent = _newParent as SoundStream;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_soundFile.SetParent( newParent == null ? null : newParent._soundFile );
		_cycleCount.SetParent( newParent == null ? null : newParent._cycleCount );
		_volume.SetParent( newParent == null ? null : newParent._volume );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_soundFile.Reset();
		_cycleCount.Reset();
		_volume.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_soundFile.IsDerivedFromParent()
			&& _cycleCount.IsDerivedFromParent()
			&& _volume.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "soundFile" )
			_soundFile.Reset();
		else if ( fieldName == "cycleCount" )
			_cycleCount.Reset();
		else if ( fieldName == "volume" )
			_volume.Reset();
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
		if ( fieldName == "cycleCount" )
			return _cycleCount.IsDerivedFromParent();
		if ( fieldName == "volume" )
			return _volume.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
