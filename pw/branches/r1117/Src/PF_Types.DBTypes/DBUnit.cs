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
public enum BooleanLockMode
{
	Lock = 0,
	UnLock = 1,
};

public enum EAskRecipient
{
	Self = 0,
	Target = 1,
	Allies = 2,
	Enemies = 3,
	All = 4,
};

public enum EBotRollMode
{
	Enabled = 0,
	Disabled = 1,
	DisabledAsEnemy = 2,
};

public enum ECreepType
{
	FactionalNormal = 0,
	FactionalSiege = 1,
	FactionalChampion = 2,
	NeutralMinion = 3,
	NeutralNormal = 4,
	NeutralChampion = 5,
	NeutralBoss = 6,
};

public enum EDamageType
{
	Material = 0,
	Energy = 1,
};

public enum EGlyph
{
	DoubleDamager = 0,
	LifeRestorer = 1,
	EnergyRestorer = 2,
	Refresher = 3,
	Booster = 4,
	Invisibler = 5,
};

[Custom("Social")]
[Flags]
public enum EHeroRaces
{
	Zero = 0,
	A = 1,
	B = 2,
};

public enum ESelectionAoeVisualType
{
	Primary = 0,
	Secondary = 1,
};

[Flags]
public enum ESpawnType
{
	Before = 1,
	After = 2,
};

public enum EUnitCategory
{
	Invalid = 0,
	Heroes = 1,
	Creeps = 2,
	Buildings = 3,
};

[Flags]
public enum MapForceStatModifierApplication
{
	None = 0,
	Base = 1,
	LevelUp = 2,
	All = 3,
};

[Custom("DBServer")]
[NoCode]
public enum MMakingHeroClassEnum
{
	None = 0,
	Protector = 1,
	Vanguard = 2,
	Executioner = 3,
	Fighter = 4,
	Support = 5,
	Jungler = 6,
};

public class NeutralSpawnObject : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private NeutralSpawnObject __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<AdvMapCreep> _creep;
	private Placement _offset;
	private UndoRedo<int> _waveDelayToAppear;
	private UndoRedo<bool> _useSpawnerWalkLimit;
	private UndoRedo<float> _limitWalkDistance;
	private UndoRedo<bool> _specialAwarding;

	public DBPtr<AdvMapCreep> creep { get { return _creep.Get(); } set { _creep.Set( value ); } }

	public Placement offset { get { return _offset; } set { _offset.Assign( value ); } }

	public int waveDelayToAppear { get { return _waveDelayToAppear.Get(); } set { _waveDelayToAppear.Set( value ); } }

	[Description( "Defines whether to use spawner's maximum allowed walk distance setting." )]
	public bool useSpawnerWalkLimit { get { return _useSpawnerWalkLimit.Get(); } set { _useSpawnerWalkLimit.Set( value ); } }

	[Description( "Defines maximum distance, to which creep is allowed to walk away from its initial position. -1 = no limit. Effective only when useSpawnerWalkLimit = false." )]
	public float limitWalkDistance { get { return _limitWalkDistance.Get(); } set { _limitWalkDistance.Set( value ); } }

	[Description( "Ignore level diff when awarding a killer (for the case of custom neutralKillExperienceModifier map settings)" )]
	public bool specialAwarding { get { return _specialAwarding.Get(); } set { _specialAwarding.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_creep = new UndoRedoDBPtr<AdvMapCreep>( owner );
		_offset = new Placement( owner );
		_waveDelayToAppear = new UndoRedo<int>( owner, 0 );
		_useSpawnerWalkLimit = new UndoRedo<bool>( owner, true );
		_limitWalkDistance = new UndoRedo<float>( owner, -1.0f );
		_specialAwarding = new UndoRedo<bool>( owner, false );
		_creep.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_waveDelayToAppear.Changed += FireChangedEvent;
		_useSpawnerWalkLimit.Changed += FireChangedEvent;
		_limitWalkDistance.Changed += FireChangedEvent;
		_specialAwarding.Changed += FireChangedEvent;
	}

	public NeutralSpawnObject()
	{
		Initialize( GetOwner() );
	}

	public NeutralSpawnObject( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public NeutralSpawnObject( DBResource owner, NeutralSpawnObject source )
		: this(owner, source, true){}

	protected NeutralSpawnObject( DBResource owner, NeutralSpawnObject source, bool fireEvent )
	{
		_creep = new UndoRedoDBPtr<AdvMapCreep>( owner, source.creep );
		_offset = new Placement( owner, source.offset );
		_waveDelayToAppear = new UndoRedo<int>( owner, source.waveDelayToAppear );
		_useSpawnerWalkLimit = new UndoRedo<bool>( owner, source.useSpawnerWalkLimit );
		_limitWalkDistance = new UndoRedo<float>( owner, source.limitWalkDistance );
		_specialAwarding = new UndoRedo<bool>( owner, source.specialAwarding );
		_creep.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_waveDelayToAppear.Changed += FireChangedEvent;
		_useSpawnerWalkLimit.Changed += FireChangedEvent;
		_limitWalkDistance.Changed += FireChangedEvent;
		_specialAwarding.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		NeutralSpawnObject source = _source as NeutralSpawnObject;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NeutralSpawnObject" );
		creep = source.creep;
		offset = source.offset;
		waveDelayToAppear = source.waveDelayToAppear;
		useSpawnerWalkLimit = source.useSpawnerWalkLimit;
		limitWalkDistance = source.limitWalkDistance;
		specialAwarding = source.specialAwarding;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		NeutralSpawnObject newParent = _newParent as NeutralSpawnObject;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_creep.SetParent( newParent == null ? null : newParent._creep );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_waveDelayToAppear.SetParent( newParent == null ? null : newParent._waveDelayToAppear );
		_useSpawnerWalkLimit.SetParent( newParent == null ? null : newParent._useSpawnerWalkLimit );
		_limitWalkDistance.SetParent( newParent == null ? null : newParent._limitWalkDistance );
		_specialAwarding.SetParent( newParent == null ? null : newParent._specialAwarding );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_creep.Reset();
		_offset.Reset();
		_waveDelayToAppear.Reset();
		_useSpawnerWalkLimit.Reset();
		_limitWalkDistance.Reset();
		_specialAwarding.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_creep.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _waveDelayToAppear.IsDerivedFromParent()
			&& _useSpawnerWalkLimit.IsDerivedFromParent()
			&& _limitWalkDistance.IsDerivedFromParent()
			&& _specialAwarding.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "creep" )
			_creep.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "waveDelayToAppear" )
			_waveDelayToAppear.Reset();
		else if ( fieldName == "useSpawnerWalkLimit" )
			_useSpawnerWalkLimit.Reset();
		else if ( fieldName == "limitWalkDistance" )
			_limitWalkDistance.Reset();
		else if ( fieldName == "specialAwarding" )
			_specialAwarding.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "creep" )
			return _creep.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "waveDelayToAppear" )
			return _waveDelayToAppear.IsDerivedFromParent();
		if ( fieldName == "useSpawnerWalkLimit" )
			return _useSpawnerWalkLimit.IsDerivedFromParent();
		if ( fieldName == "limitWalkDistance" )
			return _limitWalkDistance.IsDerivedFromParent();
		if ( fieldName == "specialAwarding" )
			return _specialAwarding.IsDerivedFromParent();
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

public class AskSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AskSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minInterval;
	private UndoRedo<EAskRecipient> _ask3dRecipient;

	[Description( "Defines minimum time interval, which is allowed between two ask plays. (seconds)" )]
	public float minInterval { get { return _minInterval.Get(); } set { _minInterval.Set( value ); } }

	[Description( "Defines allowed recipients for 3d asks." )]
	public EAskRecipient ask3dRecipient { get { return _ask3dRecipient.Get(); } set { _ask3dRecipient.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minInterval = new UndoRedo<float>( owner, 3.0f );
		_ask3dRecipient = new UndoRedo<EAskRecipient>( owner, EAskRecipient.Enemies );
		_minInterval.Changed += FireChangedEvent;
		_ask3dRecipient.Changed += FireChangedEvent;
	}

	public AskSettings()
	{
		Initialize( GetOwner() );
	}

	public AskSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AskSettings( DBResource owner, AskSettings source )
		: this(owner, source, true){}

	protected AskSettings( DBResource owner, AskSettings source, bool fireEvent )
	{
		_minInterval = new UndoRedo<float>( owner, source.minInterval );
		_ask3dRecipient = new UndoRedo<EAskRecipient>( owner, source.ask3dRecipient );
		_minInterval.Changed += FireChangedEvent;
		_ask3dRecipient.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AskSettings source = _source as AskSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AskSettings" );
		minInterval = source.minInterval;
		ask3dRecipient = source.ask3dRecipient;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AskSettings newParent = _newParent as AskSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minInterval.SetParent( newParent == null ? null : newParent._minInterval );
		_ask3dRecipient.SetParent( newParent == null ? null : newParent._ask3dRecipient );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minInterval.Reset();
		_ask3dRecipient.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minInterval.IsDerivedFromParent()
			&& _ask3dRecipient.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minInterval" )
			_minInterval.Reset();
		else if ( fieldName == "ask3dRecipient" )
			_ask3dRecipient.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minInterval" )
			return _minInterval.IsDerivedFromParent();
		if ( fieldName == "ask3dRecipient" )
			return _ask3dRecipient.IsDerivedFromParent();
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

public class AskSounds : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AskSounds __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>> _sounds;
	private UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>> _sounds3d;
	private UndoRedoAssignableList<AskSettings> _settings;

	[EnumArray(typeof(EAskSounds))]
	public libdb.IChangeableList<DBPtr<DBSoundSceneComponent>> sounds { get { return _sounds; } set { _sounds.Assign( value ); } }

	[EnumArray(typeof(EAskSounds))]
	public libdb.IChangeableList<DBPtr<DBSoundSceneComponent>> sounds3d { get { return _sounds3d; } set { _sounds3d.Assign( value ); } }

	[EnumArray(typeof(EAskSounds))]
	public libdb.IChangeableList<AskSettings> settings { get { return _settings; } set { _settings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_sounds = new UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>>( owner, typeof( EAskSounds ) );
		_sounds3d = new UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>>( owner, typeof( EAskSounds ) );
		_settings = new UndoRedoAssignableList<AskSettings>( owner, typeof( EAskSounds ) );
		_sounds.Changed += FireChangedEvent;
		_sounds3d.Changed += FireChangedEvent;
		_settings.Changed += FireChangedEvent;
	}

	public AskSounds()
	{
		Initialize( GetOwner() );
	}

	public AskSounds( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AskSounds( DBResource owner, AskSounds source )
		: this(owner, source, true){}

	protected AskSounds( DBResource owner, AskSounds source, bool fireEvent )
	{
		_sounds = new UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>>( owner, typeof( EAskSounds ) );
		_sounds.Assign( source.sounds );
		_sounds3d = new UndoRedoAssignableList<DBPtr<DBSoundSceneComponent>>( owner, typeof( EAskSounds ) );
		_sounds3d.Assign( source.sounds3d );
		_settings = new UndoRedoAssignableList<AskSettings>( owner, typeof( EAskSounds ) );
		_settings.Assign( source.settings );
		_sounds.Changed += FireChangedEvent;
		_sounds3d.Changed += FireChangedEvent;
		_settings.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AskSounds source = _source as AskSounds;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AskSounds" );
		sounds = source.sounds;
		sounds3d = source.sounds3d;
		settings = source.settings;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AskSounds newParent = _newParent as AskSounds;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_sounds.SetParent( newParent == null ? null : newParent._sounds );
		_sounds3d.SetParent( newParent == null ? null : newParent._sounds3d );
		_settings.SetParent( newParent == null ? null : newParent._settings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_sounds.Reset();
		_sounds3d.Reset();
		_settings.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_sounds.IsDerivedFromParent()
			&& _sounds3d.IsDerivedFromParent()
			&& _settings.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "sounds" )
			_sounds.Reset();
		else if ( fieldName == "sounds3d" )
			_sounds3d.Reset();
		else if ( fieldName == "settings" )
			_settings.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "sounds" )
			return _sounds.IsDerivedFromParent();
		if ( fieldName == "sounds3d" )
			return _sounds3d.IsDerivedFromParent();
		if ( fieldName == "settings" )
			return _settings.IsDerivedFromParent();
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

public class EvadeData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EvadeData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _waitForEvadeTime;
	private UndoRedo<float> _waitForNextTargetTime;
	private UndoRedo<float> _evadeTimeout;
	private UndoRedo<float> _restoreHealthPercent;

	[Description( "Defines maximum time to wait for enemy after receiving damage, before entering Evade State. (seconds)" )]
	public float waitForEvadeTime { get { return _waitForEvadeTime.Get(); } set { _waitForEvadeTime.Set( value ); } }

	[Description( "Defines maximum time to wait for next enemy after previous is died, before entering Evade State. (seconds)" )]
	public float waitForNextTargetTime { get { return _waitForNextTargetTime.Get(); } set { _waitForNextTargetTime.Set( value ); } }

	[Description( "Defines maximum time the Evade State may be active. (seconds)" )]
	public float evadeTimeout { get { return _evadeTimeout.Get(); } set { _evadeTimeout.Set( value ); } }

	[Description( "Defines health restore per second amount as a percent of maximum health. (percents in range 0-1)" )]
	public float restoreHealthPercent { get { return _restoreHealthPercent.Get(); } set { _restoreHealthPercent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_waitForEvadeTime = new UndoRedo<float>( owner, 3.0f );
		_waitForNextTargetTime = new UndoRedo<float>( owner, 3.0f );
		_evadeTimeout = new UndoRedo<float>( owner, 60.0f );
		_restoreHealthPercent = new UndoRedo<float>( owner, 0.2f );
		_waitForEvadeTime.Changed += FireChangedEvent;
		_waitForNextTargetTime.Changed += FireChangedEvent;
		_evadeTimeout.Changed += FireChangedEvent;
		_restoreHealthPercent.Changed += FireChangedEvent;
	}

	public EvadeData()
	{
		Initialize( GetOwner() );
	}

	public EvadeData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EvadeData( DBResource owner, EvadeData source )
		: this(owner, source, true){}

	protected EvadeData( DBResource owner, EvadeData source, bool fireEvent )
	{
		_waitForEvadeTime = new UndoRedo<float>( owner, source.waitForEvadeTime );
		_waitForNextTargetTime = new UndoRedo<float>( owner, source.waitForNextTargetTime );
		_evadeTimeout = new UndoRedo<float>( owner, source.evadeTimeout );
		_restoreHealthPercent = new UndoRedo<float>( owner, source.restoreHealthPercent );
		_waitForEvadeTime.Changed += FireChangedEvent;
		_waitForNextTargetTime.Changed += FireChangedEvent;
		_evadeTimeout.Changed += FireChangedEvent;
		_restoreHealthPercent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EvadeData source = _source as EvadeData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvadeData" );
		waitForEvadeTime = source.waitForEvadeTime;
		waitForNextTargetTime = source.waitForNextTargetTime;
		evadeTimeout = source.evadeTimeout;
		restoreHealthPercent = source.restoreHealthPercent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EvadeData newParent = _newParent as EvadeData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_waitForEvadeTime.SetParent( newParent == null ? null : newParent._waitForEvadeTime );
		_waitForNextTargetTime.SetParent( newParent == null ? null : newParent._waitForNextTargetTime );
		_evadeTimeout.SetParent( newParent == null ? null : newParent._evadeTimeout );
		_restoreHealthPercent.SetParent( newParent == null ? null : newParent._restoreHealthPercent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_waitForEvadeTime.Reset();
		_waitForNextTargetTime.Reset();
		_evadeTimeout.Reset();
		_restoreHealthPercent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_waitForEvadeTime.IsDerivedFromParent()
			&& _waitForNextTargetTime.IsDerivedFromParent()
			&& _evadeTimeout.IsDerivedFromParent()
			&& _restoreHealthPercent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "waitForEvadeTime" )
			_waitForEvadeTime.Reset();
		else if ( fieldName == "waitForNextTargetTime" )
			_waitForNextTargetTime.Reset();
		else if ( fieldName == "evadeTimeout" )
			_evadeTimeout.Reset();
		else if ( fieldName == "restoreHealthPercent" )
			_restoreHealthPercent.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "waitForEvadeTime" )
			return _waitForEvadeTime.IsDerivedFromParent();
		if ( fieldName == "waitForNextTargetTime" )
			return _waitForNextTargetTime.IsDerivedFromParent();
		if ( fieldName == "evadeTimeout" )
			return _evadeTimeout.IsDerivedFromParent();
		if ( fieldName == "restoreHealthPercent" )
			return _restoreHealthPercent.IsDerivedFromParent();
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

public class GlyphEntry : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GlyphEntry __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Glyph> _glyph;
	private UndoRedo<int> _weight;

	public DBPtr<Glyph> glyph { get { return _glyph.Get(); } set { _glyph.Set( value ); } }

	[IntMin(1)]
	public int weight { get { return _weight.Get(); } set { _weight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_glyph = new UndoRedoDBPtr<Glyph>( owner );
		_weight = new UndoRedo<int>( owner, 1 );
		_glyph.Changed += FireChangedEvent;
		_weight.Changed += FireChangedEvent;
	}

	public GlyphEntry()
	{
		Initialize( GetOwner() );
	}

	public GlyphEntry( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GlyphEntry( DBResource owner, GlyphEntry source )
		: this(owner, source, true){}

	protected GlyphEntry( DBResource owner, GlyphEntry source, bool fireEvent )
	{
		_glyph = new UndoRedoDBPtr<Glyph>( owner, source.glyph );
		_weight = new UndoRedo<int>( owner, source.weight );
		_glyph.Changed += FireChangedEvent;
		_weight.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GlyphEntry source = _source as GlyphEntry;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GlyphEntry" );
		glyph = source.glyph;
		weight = source.weight;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GlyphEntry newParent = _newParent as GlyphEntry;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_glyph.SetParent( newParent == null ? null : newParent._glyph );
		_weight.SetParent( newParent == null ? null : newParent._weight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_glyph.Reset();
		_weight.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_glyph.IsDerivedFromParent()
			&& _weight.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "glyph" )
			_glyph.Reset();
		else if ( fieldName == "weight" )
			_weight.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "glyph" )
			return _glyph.IsDerivedFromParent();
		if ( fieldName == "weight" )
			return _weight.IsDerivedFromParent();
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

public class LevelDiffModifier : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LevelDiffModifier __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _difference;
	private UndoRedo<float> _modifier;

	public int difference { get { return _difference.Get(); } set { _difference.Set( value ); } }

	public float modifier { get { return _modifier.Get(); } set { _modifier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_difference = new UndoRedo<int>( owner, 0 );
		_modifier = new UndoRedo<float>( owner, 0.0f );
		_difference.Changed += FireChangedEvent;
		_modifier.Changed += FireChangedEvent;
	}

	public LevelDiffModifier()
	{
		Initialize( GetOwner() );
	}

	public LevelDiffModifier( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LevelDiffModifier( DBResource owner, LevelDiffModifier source )
		: this(owner, source, true){}

	protected LevelDiffModifier( DBResource owner, LevelDiffModifier source, bool fireEvent )
	{
		_difference = new UndoRedo<int>( owner, source.difference );
		_modifier = new UndoRedo<float>( owner, source.modifier );
		_difference.Changed += FireChangedEvent;
		_modifier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LevelDiffModifier source = _source as LevelDiffModifier;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LevelDiffModifier" );
		difference = source.difference;
		modifier = source.modifier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LevelDiffModifier newParent = _newParent as LevelDiffModifier;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_difference.SetParent( newParent == null ? null : newParent._difference );
		_modifier.SetParent( newParent == null ? null : newParent._modifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_difference.Reset();
		_modifier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_difference.IsDerivedFromParent()
			&& _modifier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "difference" )
			_difference.Reset();
		else if ( fieldName == "modifier" )
			_modifier.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "difference" )
			return _difference.IsDerivedFromParent();
		if ( fieldName == "modifier" )
			return _modifier.IsDerivedFromParent();
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

[DBVersion(1)]
public class LevelUpInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LevelUpInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _lifetimeLevelUp;
	private UndoRedo<float> _interval;
	private UndoRedo<int> _increment;
	private UndoRedo<int> _spawnLevelUpInterval;
	private UndoRedo<int> _spawnLevelUpIncrement;

	public bool lifetimeLevelUp { get { return _lifetimeLevelUp.Get(); } set { _lifetimeLevelUp.Set( value ); } }

	public float interval { get { return _interval.Get(); } set { _interval.Set( value ); } }

	public int increment { get { return _increment.Get(); } set { _increment.Set( value ); } }

	[Description( "Defines per-spawn level up interval, i.e. after each N spawns creep will get aditional levels (0 = no per-spawn levelups)." )]
	public int spawnLevelUpInterval { get { return _spawnLevelUpInterval.Get(); } set { _spawnLevelUpInterval.Set( value ); } }

	[Description( "Defines per-spawn level up increment, i.e. for each per-spawn level up creep will get N aditional levels (0 = no increment)." )]
	public int spawnLevelUpIncrement { get { return _spawnLevelUpIncrement.Get(); } set { _spawnLevelUpIncrement.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lifetimeLevelUp = new UndoRedo<bool>( owner, false );
		_interval = new UndoRedo<float>( owner, -1.0f );
		_increment = new UndoRedo<int>( owner, -1 );
		_spawnLevelUpInterval = new UndoRedo<int>( owner, 0 );
		_spawnLevelUpIncrement = new UndoRedo<int>( owner, 0 );
		_lifetimeLevelUp.Changed += FireChangedEvent;
		_interval.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		_spawnLevelUpInterval.Changed += FireChangedEvent;
		_spawnLevelUpIncrement.Changed += FireChangedEvent;
	}

	public LevelUpInfo()
	{
		Initialize( GetOwner() );
	}

	public LevelUpInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LevelUpInfo( DBResource owner, LevelUpInfo source )
		: this(owner, source, true){}

	protected LevelUpInfo( DBResource owner, LevelUpInfo source, bool fireEvent )
	{
		_lifetimeLevelUp = new UndoRedo<bool>( owner, source.lifetimeLevelUp );
		_interval = new UndoRedo<float>( owner, source.interval );
		_increment = new UndoRedo<int>( owner, source.increment );
		_spawnLevelUpInterval = new UndoRedo<int>( owner, source.spawnLevelUpInterval );
		_spawnLevelUpIncrement = new UndoRedo<int>( owner, source.spawnLevelUpIncrement );
		_lifetimeLevelUp.Changed += FireChangedEvent;
		_interval.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		_spawnLevelUpInterval.Changed += FireChangedEvent;
		_spawnLevelUpIncrement.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LevelUpInfo source = _source as LevelUpInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LevelUpInfo" );
		lifetimeLevelUp = source.lifetimeLevelUp;
		interval = source.interval;
		increment = source.increment;
		spawnLevelUpInterval = source.spawnLevelUpInterval;
		spawnLevelUpIncrement = source.spawnLevelUpIncrement;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LevelUpInfo newParent = _newParent as LevelUpInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lifetimeLevelUp.SetParent( newParent == null ? null : newParent._lifetimeLevelUp );
		_interval.SetParent( newParent == null ? null : newParent._interval );
		_increment.SetParent( newParent == null ? null : newParent._increment );
		_spawnLevelUpInterval.SetParent( newParent == null ? null : newParent._spawnLevelUpInterval );
		_spawnLevelUpIncrement.SetParent( newParent == null ? null : newParent._spawnLevelUpIncrement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lifetimeLevelUp.Reset();
		_interval.Reset();
		_increment.Reset();
		_spawnLevelUpInterval.Reset();
		_spawnLevelUpIncrement.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lifetimeLevelUp.IsDerivedFromParent()
			&& _interval.IsDerivedFromParent()
			&& _increment.IsDerivedFromParent()
			&& _spawnLevelUpInterval.IsDerivedFromParent()
			&& _spawnLevelUpIncrement.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lifetimeLevelUp" )
			_lifetimeLevelUp.Reset();
		else if ( fieldName == "interval" )
			_interval.Reset();
		else if ( fieldName == "increment" )
			_increment.Reset();
		else if ( fieldName == "spawnLevelUpInterval" )
			_spawnLevelUpInterval.Reset();
		else if ( fieldName == "spawnLevelUpIncrement" )
			_spawnLevelUpIncrement.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lifetimeLevelUp" )
			return _lifetimeLevelUp.IsDerivedFromParent();
		if ( fieldName == "interval" )
			return _interval.IsDerivedFromParent();
		if ( fieldName == "increment" )
			return _increment.IsDerivedFromParent();
		if ( fieldName == "spawnLevelUpInterval" )
			return _spawnLevelUpInterval.IsDerivedFromParent();
		if ( fieldName == "spawnLevelUpIncrement" )
			return _spawnLevelUpIncrement.IsDerivedFromParent();
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

public class AdvMapNeutralCreepsGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AdvMapNeutralCreepsGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<NeutralSpawnObject> _creeps;

	public libdb.IChangeableList<NeutralSpawnObject> creeps { get { return _creeps; } set { _creeps.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_creeps = new UndoRedoAssignableList<NeutralSpawnObject>( owner );
		_creeps.Changed += FireChangedEvent;
	}

	public AdvMapNeutralCreepsGroup()
	{
		Initialize( GetOwner() );
	}

	public AdvMapNeutralCreepsGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AdvMapNeutralCreepsGroup( DBResource owner, AdvMapNeutralCreepsGroup source )
		: this(owner, source, true){}

	protected AdvMapNeutralCreepsGroup( DBResource owner, AdvMapNeutralCreepsGroup source, bool fireEvent )
	{
		_creeps = new UndoRedoAssignableList<NeutralSpawnObject>( owner );
		_creeps.Assign( source.creeps );
		_creeps.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AdvMapNeutralCreepsGroup source = _source as AdvMapNeutralCreepsGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapNeutralCreepsGroup" );
		creeps = source.creeps;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AdvMapNeutralCreepsGroup newParent = _newParent as AdvMapNeutralCreepsGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_creeps.SetParent( newParent == null ? null : newParent._creeps );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_creeps.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_creeps.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "creeps" )
			_creeps.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "creeps" )
			return _creeps.IsDerivedFromParent();
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

public class SpawnObject : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SpawnObject __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<AdvMapCreep> _creep;
	private Placement _place;
	private UndoRedoDBPtr<CreepSpawnTimer> _timer;

	public DBPtr<AdvMapCreep> creep { get { return _creep.Get(); } set { _creep.Set( value ); } }

	public Placement place { get { return _place; } set { _place.Assign( value ); } }

	public DBPtr<CreepSpawnTimer> timer { get { return _timer.Get(); } set { _timer.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_creep = new UndoRedoDBPtr<AdvMapCreep>( owner );
		_place = new Placement( owner );
		_timer = new UndoRedoDBPtr<CreepSpawnTimer>( owner );
		_creep.Changed += FireChangedEvent;
		_place.Changed += FireChangedEvent;
		_timer.Changed += FireChangedEvent;
	}

	public SpawnObject()
	{
		Initialize( GetOwner() );
	}

	public SpawnObject( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SpawnObject( DBResource owner, SpawnObject source )
		: this(owner, source, true){}

	protected SpawnObject( DBResource owner, SpawnObject source, bool fireEvent )
	{
		_creep = new UndoRedoDBPtr<AdvMapCreep>( owner, source.creep );
		_place = new Placement( owner, source.place );
		_timer = new UndoRedoDBPtr<CreepSpawnTimer>( owner, source.timer );
		_creep.Changed += FireChangedEvent;
		_place.Changed += FireChangedEvent;
		_timer.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SpawnObject source = _source as SpawnObject;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpawnObject" );
		creep = source.creep;
		place = source.place;
		timer = source.timer;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SpawnObject newParent = _newParent as SpawnObject;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_creep.SetParent( newParent == null ? null : newParent._creep );
		_place.SetParent( newParent == null ? null : newParent._place );
		_timer.SetParent( newParent == null ? null : newParent._timer );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_creep.Reset();
		_place.Reset();
		_timer.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_creep.IsDerivedFromParent()
			&& _place.IsDerivedFromParent()
			&& _timer.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "creep" )
			_creep.Reset();
		else if ( fieldName == "place" )
			_place.Reset();
		else if ( fieldName == "timer" )
			_timer.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "creep" )
			return _creep.IsDerivedFromParent();
		if ( fieldName == "place" )
			return _place.IsDerivedFromParent();
		if ( fieldName == "timer" )
			return _timer.IsDerivedFromParent();
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

[DBVersion(4)]
public class SummonedUnits : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SummonedUnits __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Summoned> _unitA;
	private UndoRedoDBPtr<Summoned> _unitB;

	[Description( "Summon for first faction" )]
	public DBPtr<Summoned> unitA { get { return _unitA.Get(); } set { _unitA.Set( value ); } }

	[Description( "Summon for second faction" )]
	public DBPtr<Summoned> unitB { get { return _unitB.Get(); } set { _unitB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_unitA = new UndoRedoDBPtr<Summoned>( owner );
		_unitB = new UndoRedoDBPtr<Summoned>( owner );
		_unitA.Changed += FireChangedEvent;
		_unitB.Changed += FireChangedEvent;
	}

	public SummonedUnits()
	{
		Initialize( GetOwner() );
	}

	public SummonedUnits( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SummonedUnits( DBResource owner, SummonedUnits source )
		: this(owner, source, true){}

	protected SummonedUnits( DBResource owner, SummonedUnits source, bool fireEvent )
	{
		_unitA = new UndoRedoDBPtr<Summoned>( owner, source.unitA );
		_unitB = new UndoRedoDBPtr<Summoned>( owner, source.unitB );
		_unitA.Changed += FireChangedEvent;
		_unitB.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SummonedUnits source = _source as SummonedUnits;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonedUnits" );
		unitA = source.unitA;
		unitB = source.unitB;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SummonedUnits newParent = _newParent as SummonedUnits;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_unitA.SetParent( newParent == null ? null : newParent._unitA );
		_unitB.SetParent( newParent == null ? null : newParent._unitB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_unitA.Reset();
		_unitB.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_unitA.IsDerivedFromParent()
			&& _unitB.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "unitA" )
			_unitA.Reset();
		else if ( fieldName == "unitB" )
			_unitB.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "unitA" )
			return _unitA.IsDerivedFromParent();
		if ( fieldName == "unitB" )
			return _unitB.IsDerivedFromParent();
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

public class TransactionEffects : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TransactionEffects __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<EffectBase> _effectIn;
	private UndoRedoDBPtr<EffectBase> _effectOut;

	public DBPtr<EffectBase> effectIn { get { return _effectIn.Get(); } set { _effectIn.Set( value ); } }

	public DBPtr<EffectBase> effectOut { get { return _effectOut.Get(); } set { _effectOut.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_effectIn = new UndoRedoDBPtr<EffectBase>( owner );
		_effectOut = new UndoRedoDBPtr<EffectBase>( owner );
		_effectIn.Changed += FireChangedEvent;
		_effectOut.Changed += FireChangedEvent;
	}

	public TransactionEffects()
	{
		Initialize( GetOwner() );
	}

	public TransactionEffects( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TransactionEffects( DBResource owner, TransactionEffects source )
		: this(owner, source, true){}

	protected TransactionEffects( DBResource owner, TransactionEffects source, bool fireEvent )
	{
		_effectIn = new UndoRedoDBPtr<EffectBase>( owner, source.effectIn );
		_effectOut = new UndoRedoDBPtr<EffectBase>( owner, source.effectOut );
		_effectIn.Changed += FireChangedEvent;
		_effectOut.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TransactionEffects source = _source as TransactionEffects;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TransactionEffects" );
		effectIn = source.effectIn;
		effectOut = source.effectOut;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TransactionEffects newParent = _newParent as TransactionEffects;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_effectIn.SetParent( newParent == null ? null : newParent._effectIn );
		_effectOut.SetParent( newParent == null ? null : newParent._effectOut );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_effectIn.Reset();
		_effectOut.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_effectIn.IsDerivedFromParent()
			&& _effectOut.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "effectIn" )
			_effectIn.Reset();
		else if ( fieldName == "effectOut" )
			_effectOut.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "effectIn" )
			return _effectIn.IsDerivedFromParent();
		if ( fieldName == "effectOut" )
			return _effectOut.IsDerivedFromParent();
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

public class UnitCategoryParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UnitCategoryParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _selectionPriority;

	public int selectionPriority { get { return _selectionPriority.Get(); } set { _selectionPriority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_selectionPriority = new UndoRedo<int>( owner, 0 );
		_selectionPriority.Changed += FireChangedEvent;
	}

	public UnitCategoryParams()
	{
		Initialize( GetOwner() );
	}

	public UnitCategoryParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UnitCategoryParams( DBResource owner, UnitCategoryParams source )
		: this(owner, source, true){}

	protected UnitCategoryParams( DBResource owner, UnitCategoryParams source, bool fireEvent )
	{
		_selectionPriority = new UndoRedo<int>( owner, source.selectionPriority );
		_selectionPriority.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UnitCategoryParams source = _source as UnitCategoryParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitCategoryParams" );
		selectionPriority = source.selectionPriority;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UnitCategoryParams newParent = _newParent as UnitCategoryParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_selectionPriority.SetParent( newParent == null ? null : newParent._selectionPriority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_selectionPriority.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_selectionPriority.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "selectionPriority" )
			_selectionPriority.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "selectionPriority" )
			return _selectionPriority.IsDerivedFromParent();
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

[TypeId(0x0F641B40)]
[UseTypeName("SSO")]
public class SingleStateObject : GameObject
{
	private UndoRedoDBPtr<SingleStateObject> ___parent;
	[HideInOutliner]
	public new DBPtr<SingleStateObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBSceneObject> _sceneObject;

	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SingleStateObject>(owner);
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		___parent.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
	}

	public SingleStateObject()
	{
		Initialize( this );
	}
	private void AssignSelf( SingleStateObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SingleStateObject" );
		sceneObject = source.sceneObject;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SingleStateObject source = _source as SingleStateObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SingleStateObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SingleStateObject newParent = rawParent == null ? null : rawParent.Get<SingleStateObject>();
		if ( newParent == null && _newParent is SingleStateObject )
			newParent = _newParent as SingleStateObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sceneObject.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sceneObject.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class BaseCreepSpawner : GameObject
{
	private UndoRedoDBPtr<BaseCreepSpawner> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseCreepSpawner> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private LevelUpInfo _levelUpInfo;
	private UndoRedo<float> _firstSpawnTimeOffset;

	public LevelUpInfo levelUpInfo { get { return _levelUpInfo; } set { _levelUpInfo.Assign( value ); } }

	[Description( "Defines first spawn time offset from the battle start delay (can be negative)(seconds)." )]
	public float firstSpawnTimeOffset { get { return _firstSpawnTimeOffset.Get(); } set { _firstSpawnTimeOffset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseCreepSpawner>(owner);
		_levelUpInfo = new LevelUpInfo( owner );
		_firstSpawnTimeOffset = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_levelUpInfo.Changed += FireChangedEvent;
		_firstSpawnTimeOffset.Changed += FireChangedEvent;
	}

	public BaseCreepSpawner()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseCreepSpawner source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseCreepSpawner" );
		levelUpInfo = source.levelUpInfo;
		firstSpawnTimeOffset = source.firstSpawnTimeOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseCreepSpawner source = _source as BaseCreepSpawner;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseCreepSpawner" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseCreepSpawner newParent = rawParent == null ? null : rawParent.Get<BaseCreepSpawner>();
		if ( newParent == null && _newParent is BaseCreepSpawner )
			newParent = _newParent as BaseCreepSpawner;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_levelUpInfo.SetParent( newParent == null ? null : newParent._levelUpInfo );
		_firstSpawnTimeOffset.SetParent( newParent == null ? null : newParent._firstSpawnTimeOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_levelUpInfo.Reset();
		_firstSpawnTimeOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_levelUpInfo.IsDerivedFromParent()
			&& _firstSpawnTimeOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "levelUpInfo" )
			_levelUpInfo.Reset();
		else if ( fieldName == "firstSpawnTimeOffset" )
			_firstSpawnTimeOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "levelUpInfo" )
			return _levelUpInfo.IsDerivedFromParent();
		if ( fieldName == "firstSpawnTimeOffset" )
			return _firstSpawnTimeOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[TypeId(0x0F6163C0)]
[UseTypeName("NCSPN")]
public class AdvMapNeutralCreepSpawner : BaseCreepSpawner
{
	private UndoRedoDBPtr<AdvMapNeutralCreepSpawner> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapNeutralCreepSpawner> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<AdvMapNeutralCreepsGroup> _groups;
	private UndoRedo<int> _spawnDelay;
	private UndoRedo<int> _waveCount;
	private UndoRedo<int> _baseLevel;
	private UndoRedo<int> _naftaForGroupKill;
	private UndoRedo<EMinimapIcons> _minimapIcon;
	private UndoRedo<bool> _showMinimapIcon;
	private UndoRedoAssignableList<Vec2> _path;
	private UndoRedo<float> _limitWalkDistance;
	private UndoRedo<bool> _useEvade;
	private EvadeData _evadeParams;
	private UndoRedo<bool> _isAggressive;
	private UndoRedo<MapForceStatModifierApplication> _mapForceStatModifierApplication;

	public libdb.IChangeableList<AdvMapNeutralCreepsGroup> groups { get { return _groups; } set { _groups.Assign( value ); } }

	public int spawnDelay { get { return _spawnDelay.Get(); } set { _spawnDelay.Set( value ); } }

	public int waveCount { get { return _waveCount.Get(); } set { _waveCount.Set( value ); } }

	public int baseLevel { get { return _baseLevel.Get(); } set { _baseLevel.Set( value ); } }

	public int naftaForGroupKill { get { return _naftaForGroupKill.Get(); } set { _naftaForGroupKill.Set( value ); } }

	public EMinimapIcons minimapIcon { get { return _minimapIcon.Get(); } set { _minimapIcon.Set( value ); } }

	public bool showMinimapIcon { get { return _showMinimapIcon.Get(); } set { _showMinimapIcon.Set( value ); } }

	[Description( "If defined, spawned neutrals will go by path instead of stay on spawn point" )]
	public libdb.IChangeableList<Vec2> path { get { return _path; } set { _path.Assign( value ); } }

	[Description( "Defines maximum distance, to which creeps are allowed to walk away from its initial position. -1 = no limit. May be overriden by creep's settings" )]
	public float limitWalkDistance { get { return _limitWalkDistance.Get(); } set { _limitWalkDistance.Set( value ); } }

	[Description( "Defines whether to use Evade logic for creeps in this spawner." )]
	public bool useEvade { get { return _useEvade.Get(); } set { _useEvade.Set( value ); } }

	[Description( "Evade logic parameters." )]
	public EvadeData evadeParams { get { return _evadeParams; } set { _evadeParams.Assign( value ); } }

	[Description( "Крипы спаунера агрессивные." )]
	public bool isAggressive { get { return _isAggressive.Get(); } set { _isAggressive.Set( value ); } }

	[Description( "Способ применения модификатора статов от мощи карты" )]
	public MapForceStatModifierApplication mapForceStatModifierApplication { get { return _mapForceStatModifierApplication.Get(); } set { _mapForceStatModifierApplication.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapNeutralCreepSpawner>(owner);
		_groups = new UndoRedoAssignableList<AdvMapNeutralCreepsGroup>( owner );
		_spawnDelay = new UndoRedo<int>( owner, 45 );
		_waveCount = new UndoRedo<int>( owner, 0 );
		_baseLevel = new UndoRedo<int>( owner, 0 );
		_naftaForGroupKill = new UndoRedo<int>( owner, 0 );
		_minimapIcon = new UndoRedo<EMinimapIcons>( owner, EMinimapIcons.Default );
		_showMinimapIcon = new UndoRedo<bool>( owner, true );
		_path = new UndoRedoAssignableList<Vec2>( owner );
		_limitWalkDistance = new UndoRedo<float>( owner, -1.0f );
		_useEvade = new UndoRedo<bool>( owner, true );
		_evadeParams = new EvadeData( owner );
		_isAggressive = new UndoRedo<bool>( owner, false );
		_mapForceStatModifierApplication = new UndoRedo<MapForceStatModifierApplication>( owner, MapForceStatModifierApplication.All );
		___parent.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
		_spawnDelay.Changed += FireChangedEvent;
		_waveCount.Changed += FireChangedEvent;
		_baseLevel.Changed += FireChangedEvent;
		_naftaForGroupKill.Changed += FireChangedEvent;
		_minimapIcon.Changed += FireChangedEvent;
		_showMinimapIcon.Changed += FireChangedEvent;
		_path.Changed += FireChangedEvent;
		_limitWalkDistance.Changed += FireChangedEvent;
		_useEvade.Changed += FireChangedEvent;
		_evadeParams.Changed += FireChangedEvent;
		_isAggressive.Changed += FireChangedEvent;
		_mapForceStatModifierApplication.Changed += FireChangedEvent;
	}

	public AdvMapNeutralCreepSpawner()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapNeutralCreepSpawner source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapNeutralCreepSpawner" );
		groups = source.groups;
		spawnDelay = source.spawnDelay;
		waveCount = source.waveCount;
		baseLevel = source.baseLevel;
		naftaForGroupKill = source.naftaForGroupKill;
		minimapIcon = source.minimapIcon;
		showMinimapIcon = source.showMinimapIcon;
		path = source.path;
		limitWalkDistance = source.limitWalkDistance;
		useEvade = source.useEvade;
		evadeParams = source.evadeParams;
		isAggressive = source.isAggressive;
		mapForceStatModifierApplication = source.mapForceStatModifierApplication;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapNeutralCreepSpawner source = _source as AdvMapNeutralCreepSpawner;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapNeutralCreepSpawner" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapNeutralCreepSpawner newParent = rawParent == null ? null : rawParent.Get<AdvMapNeutralCreepSpawner>();
		if ( newParent == null && _newParent is AdvMapNeutralCreepSpawner )
			newParent = _newParent as AdvMapNeutralCreepSpawner;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_groups.SetParent( newParent == null ? null : newParent._groups );
		_spawnDelay.SetParent( newParent == null ? null : newParent._spawnDelay );
		_waveCount.SetParent( newParent == null ? null : newParent._waveCount );
		_baseLevel.SetParent( newParent == null ? null : newParent._baseLevel );
		_naftaForGroupKill.SetParent( newParent == null ? null : newParent._naftaForGroupKill );
		_minimapIcon.SetParent( newParent == null ? null : newParent._minimapIcon );
		_showMinimapIcon.SetParent( newParent == null ? null : newParent._showMinimapIcon );
		_path.SetParent( newParent == null ? null : newParent._path );
		_limitWalkDistance.SetParent( newParent == null ? null : newParent._limitWalkDistance );
		_useEvade.SetParent( newParent == null ? null : newParent._useEvade );
		_evadeParams.SetParent( newParent == null ? null : newParent._evadeParams );
		_isAggressive.SetParent( newParent == null ? null : newParent._isAggressive );
		_mapForceStatModifierApplication.SetParent( newParent == null ? null : newParent._mapForceStatModifierApplication );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_groups.Reset();
		_spawnDelay.Reset();
		_waveCount.Reset();
		_baseLevel.Reset();
		_naftaForGroupKill.Reset();
		_minimapIcon.Reset();
		_showMinimapIcon.Reset();
		_path.Reset();
		_limitWalkDistance.Reset();
		_useEvade.Reset();
		_evadeParams.Reset();
		_isAggressive.Reset();
		_mapForceStatModifierApplication.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_groups.IsDerivedFromParent()
			&& _spawnDelay.IsDerivedFromParent()
			&& _waveCount.IsDerivedFromParent()
			&& _baseLevel.IsDerivedFromParent()
			&& _naftaForGroupKill.IsDerivedFromParent()
			&& _minimapIcon.IsDerivedFromParent()
			&& _showMinimapIcon.IsDerivedFromParent()
			&& _path.IsDerivedFromParent()
			&& _limitWalkDistance.IsDerivedFromParent()
			&& _useEvade.IsDerivedFromParent()
			&& _evadeParams.IsDerivedFromParent()
			&& _isAggressive.IsDerivedFromParent()
			&& _mapForceStatModifierApplication.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "groups" )
			_groups.Reset();
		else if ( fieldName == "spawnDelay" )
			_spawnDelay.Reset();
		else if ( fieldName == "waveCount" )
			_waveCount.Reset();
		else if ( fieldName == "baseLevel" )
			_baseLevel.Reset();
		else if ( fieldName == "naftaForGroupKill" )
			_naftaForGroupKill.Reset();
		else if ( fieldName == "minimapIcon" )
			_minimapIcon.Reset();
		else if ( fieldName == "showMinimapIcon" )
			_showMinimapIcon.Reset();
		else if ( fieldName == "path" )
			_path.Reset();
		else if ( fieldName == "limitWalkDistance" )
			_limitWalkDistance.Reset();
		else if ( fieldName == "useEvade" )
			_useEvade.Reset();
		else if ( fieldName == "evadeParams" )
			_evadeParams.Reset();
		else if ( fieldName == "isAggressive" )
			_isAggressive.Reset();
		else if ( fieldName == "mapForceStatModifierApplication" )
			_mapForceStatModifierApplication.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
		if ( fieldName == "spawnDelay" )
			return _spawnDelay.IsDerivedFromParent();
		if ( fieldName == "waveCount" )
			return _waveCount.IsDerivedFromParent();
		if ( fieldName == "baseLevel" )
			return _baseLevel.IsDerivedFromParent();
		if ( fieldName == "naftaForGroupKill" )
			return _naftaForGroupKill.IsDerivedFromParent();
		if ( fieldName == "minimapIcon" )
			return _minimapIcon.IsDerivedFromParent();
		if ( fieldName == "showMinimapIcon" )
			return _showMinimapIcon.IsDerivedFromParent();
		if ( fieldName == "path" )
			return _path.IsDerivedFromParent();
		if ( fieldName == "limitWalkDistance" )
			return _limitWalkDistance.IsDerivedFromParent();
		if ( fieldName == "useEvade" )
			return _useEvade.IsDerivedFromParent();
		if ( fieldName == "evadeParams" )
			return _evadeParams.IsDerivedFromParent();
		if ( fieldName == "isAggressive" )
			return _isAggressive.IsDerivedFromParent();
		if ( fieldName == "mapForceStatModifierApplication" )
			return _mapForceStatModifierApplication.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xE7879C40)]
[UseTypeName("OBST")]
public class AdvMapObstacle : GameObject
{
	private UndoRedoDBPtr<AdvMapObstacle> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapObstacle> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _opaque;
	private UndoRedo<BooleanLockMode> _LockMode;

	[Description( "Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом." )]
	public bool opaque { get { return _opaque.Get(); } set { _opaque.Set( value ); } }

	[Description( "Lock/Unlock области" )]
	public BooleanLockMode LockMode { get { return _LockMode.Get(); } set { _LockMode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapObstacle>(owner);
		_opaque = new UndoRedo<bool>( owner, false );
		_LockMode = new UndoRedo<BooleanLockMode>( owner, BooleanLockMode.Lock );
		___parent.Changed += FireChangedEvent;
		_opaque.Changed += FireChangedEvent;
		_LockMode.Changed += FireChangedEvent;
	}

	public AdvMapObstacle()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapObstacle source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapObstacle" );
		opaque = source.opaque;
		LockMode = source.LockMode;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapObstacle source = _source as AdvMapObstacle;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapObstacle" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapObstacle newParent = rawParent == null ? null : rawParent.Get<AdvMapObstacle>();
		if ( newParent == null && _newParent is AdvMapObstacle )
			newParent = _newParent as AdvMapObstacle;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_opaque.SetParent( newParent == null ? null : newParent._opaque );
		_LockMode.SetParent( newParent == null ? null : newParent._LockMode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_opaque.Reset();
		_LockMode.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_opaque.IsDerivedFromParent()
			&& _LockMode.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "opaque" )
			_opaque.Reset();
		else if ( fieldName == "LockMode" )
			_LockMode.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "opaque" )
			return _opaque.IsDerivedFromParent();
		if ( fieldName == "LockMode" )
			return _LockMode.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[TypeId(0xB1A4F2C1)]
[UseTypeName("VISAOE")]
public class AoeVisual : DBResource
{
	private UndoRedoDBPtr<AoeVisual> ___parent;
	[HideInOutliner]
	public new DBPtr<AoeVisual> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _size;
	private ExecutableBoolString _enabled;
	private UndoRedoDBPtr<AOEMaterial> _material;

	[Category( "UI" )]
	[Description( "Aoe radius in meters." )]
	public ExecutableFloatString size { get { return _size; } set { _size.Assign( value ); } }

	[Category( "UI" )]
	[Description( "Enables/disables radius." )]
	public ExecutableBoolString enabled { get { return _enabled; } set { _enabled.Assign( value ); } }

	[Category( "UI" )]
	[Description( "Aoe zone material." )]
	public DBPtr<AOEMaterial> material { get { return _material.Get(); } set { _material.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AoeVisual>(owner);
		ExecutableFloatString __size = new ExecutableFloatString(); // Construct default object for size
		__size.sString = "0.0f";
		_size = new ExecutableFloatString( owner, __size );
		ExecutableBoolString __enabled = new ExecutableBoolString(); // Construct default object for enabled
		__enabled.sString = "true";
		_enabled = new ExecutableBoolString( owner, __enabled );
		_material = new UndoRedoDBPtr<AOEMaterial>( owner );
		___parent.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
		_enabled.Changed += FireChangedEvent;
		_material.Changed += FireChangedEvent;
	}

	public AoeVisual()
	{
		Initialize( this );
	}
	private void AssignSelf( AoeVisual source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AoeVisual" );
		size = source.size;
		enabled = source.enabled;
		material = source.material;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AoeVisual source = _source as AoeVisual;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AoeVisual" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AoeVisual newParent = rawParent == null ? null : rawParent.Get<AoeVisual>();
		if ( newParent == null && _newParent is AoeVisual )
			newParent = _newParent as AoeVisual;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_size.SetParent( newParent == null ? null : newParent._size );
		_enabled.SetParent( newParent == null ? null : newParent._enabled );
		_material.SetParent( newParent == null ? null : newParent._material );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_size.Reset();
		_enabled.Reset();
		_material.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_size.IsDerivedFromParent()
			&& _enabled.IsDerivedFromParent()
			&& _material.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "size" )
			_size.Reset();
		else if ( fieldName == "enabled" )
			_enabled.Reset();
		else if ( fieldName == "material" )
			_material.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		if ( fieldName == "enabled" )
			return _enabled.IsDerivedFromParent();
		if ( fieldName == "material" )
			return _material.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ASKS")]
public class AskSoundsRef : DBResource
{
	private UndoRedoDBPtr<AskSoundsRef> ___parent;
	[HideInOutliner]
	public new DBPtr<AskSoundsRef> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AskSounds _asks;

	public AskSounds asks { get { return _asks; } set { _asks.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AskSoundsRef>(owner);
		_asks = new AskSounds( owner );
		___parent.Changed += FireChangedEvent;
		_asks.Changed += FireChangedEvent;
	}

	public AskSoundsRef()
	{
		Initialize( this );
	}
	private void AssignSelf( AskSoundsRef source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AskSoundsRef" );
		asks = source.asks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AskSoundsRef source = _source as AskSoundsRef;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AskSoundsRef" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AskSoundsRef newParent = rawParent == null ? null : rawParent.Get<AskSoundsRef>();
		if ( newParent == null && _newParent is AskSoundsRef )
			newParent = _newParent as AskSoundsRef;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_asks.SetParent( newParent == null ? null : newParent._asks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_asks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_asks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "asks" )
			_asks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "asks" )
			return _asks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2C5AB3C0)]
[UseTypeName("CSPN")]
public class AdvMapCreepSpawner : BaseCreepSpawner
{
	private UndoRedoDBPtr<AdvMapCreepSpawner> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapCreepSpawner> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<SpawnObject> _creeps;
	private UndoRedoAssignableList<Vec2> _path;
	private UndoRedo<EFaction> _faction;
	private UndoRedo<ERoute> _routeID;
	private UndoRedo<bool> _mustRegisterInAIWorld;
	private UndoRedo<bool> _useEvade;
	private EvadeData _evadeParams;
	private UndoRedo<float> _limitWalkDistance;

	public libdb.IChangeableList<SpawnObject> creeps { get { return _creeps; } set { _creeps.Assign( value ); } }

	public libdb.IChangeableList<Vec2> path { get { return _path; } set { _path.Assign( value ); } }

	public EFaction faction { get { return _faction.Get(); } set { _faction.Set( value ); } }

	public ERoute routeID { get { return _routeID.Get(); } set { _routeID.Set( value ); } }

	public bool mustRegisterInAIWorld { get { return _mustRegisterInAIWorld.Get(); } set { _mustRegisterInAIWorld.Set( value ); } }

	[Description( "Defines whether to use Evade logic for creeps in this spawner." )]
	public bool useEvade { get { return _useEvade.Get(); } set { _useEvade.Set( value ); } }

	[Description( "Evade logic parameters." )]
	public EvadeData evadeParams { get { return _evadeParams; } set { _evadeParams.Assign( value ); } }

	[Description( "Defines maximum distance, to which creeps are allowed to walk away from its initial position. -1 = no limit. May be overriden by creep's settings" )]
	public float limitWalkDistance { get { return _limitWalkDistance.Get(); } set { _limitWalkDistance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapCreepSpawner>(owner);
		_creeps = new UndoRedoAssignableList<SpawnObject>( owner );
		_path = new UndoRedoAssignableList<Vec2>( owner );
		_faction = new UndoRedo<EFaction>( owner, EFaction.Neutral );
		_routeID = new UndoRedo<ERoute>( owner, ERoute.Center );
		_mustRegisterInAIWorld = new UndoRedo<bool>( owner, true );
		_useEvade = new UndoRedo<bool>( owner, true );
		_evadeParams = new EvadeData( owner );
		_limitWalkDistance = new UndoRedo<float>( owner, -1.0f );
		___parent.Changed += FireChangedEvent;
		_creeps.Changed += FireChangedEvent;
		_path.Changed += FireChangedEvent;
		_faction.Changed += FireChangedEvent;
		_routeID.Changed += FireChangedEvent;
		_mustRegisterInAIWorld.Changed += FireChangedEvent;
		_useEvade.Changed += FireChangedEvent;
		_evadeParams.Changed += FireChangedEvent;
		_limitWalkDistance.Changed += FireChangedEvent;
	}

	public AdvMapCreepSpawner()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapCreepSpawner source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCreepSpawner" );
		creeps = source.creeps;
		path = source.path;
		faction = source.faction;
		routeID = source.routeID;
		mustRegisterInAIWorld = source.mustRegisterInAIWorld;
		useEvade = source.useEvade;
		evadeParams = source.evadeParams;
		limitWalkDistance = source.limitWalkDistance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapCreepSpawner source = _source as AdvMapCreepSpawner;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCreepSpawner" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapCreepSpawner newParent = rawParent == null ? null : rawParent.Get<AdvMapCreepSpawner>();
		if ( newParent == null && _newParent is AdvMapCreepSpawner )
			newParent = _newParent as AdvMapCreepSpawner;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_creeps.SetParent( newParent == null ? null : newParent._creeps );
		_path.SetParent( newParent == null ? null : newParent._path );
		_faction.SetParent( newParent == null ? null : newParent._faction );
		_routeID.SetParent( newParent == null ? null : newParent._routeID );
		_mustRegisterInAIWorld.SetParent( newParent == null ? null : newParent._mustRegisterInAIWorld );
		_useEvade.SetParent( newParent == null ? null : newParent._useEvade );
		_evadeParams.SetParent( newParent == null ? null : newParent._evadeParams );
		_limitWalkDistance.SetParent( newParent == null ? null : newParent._limitWalkDistance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_creeps.Reset();
		_path.Reset();
		_faction.Reset();
		_routeID.Reset();
		_mustRegisterInAIWorld.Reset();
		_useEvade.Reset();
		_evadeParams.Reset();
		_limitWalkDistance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_creeps.IsDerivedFromParent()
			&& _path.IsDerivedFromParent()
			&& _faction.IsDerivedFromParent()
			&& _routeID.IsDerivedFromParent()
			&& _mustRegisterInAIWorld.IsDerivedFromParent()
			&& _useEvade.IsDerivedFromParent()
			&& _evadeParams.IsDerivedFromParent()
			&& _limitWalkDistance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "creeps" )
			_creeps.Reset();
		else if ( fieldName == "path" )
			_path.Reset();
		else if ( fieldName == "faction" )
			_faction.Reset();
		else if ( fieldName == "routeID" )
			_routeID.Reset();
		else if ( fieldName == "mustRegisterInAIWorld" )
			_mustRegisterInAIWorld.Reset();
		else if ( fieldName == "useEvade" )
			_useEvade.Reset();
		else if ( fieldName == "evadeParams" )
			_evadeParams.Reset();
		else if ( fieldName == "limitWalkDistance" )
			_limitWalkDistance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "creeps" )
			return _creeps.IsDerivedFromParent();
		if ( fieldName == "path" )
			return _path.IsDerivedFromParent();
		if ( fieldName == "faction" )
			return _faction.IsDerivedFromParent();
		if ( fieldName == "routeID" )
			return _routeID.IsDerivedFromParent();
		if ( fieldName == "mustRegisterInAIWorld" )
			return _mustRegisterInAIWorld.IsDerivedFromParent();
		if ( fieldName == "useEvade" )
			return _useEvade.IsDerivedFromParent();
		if ( fieldName == "evadeParams" )
			return _evadeParams.IsDerivedFromParent();
		if ( fieldName == "limitWalkDistance" )
			return _limitWalkDistance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[TypeId(0x9E678C00)]
[UseTypeName("UNIT")]
public class Unit : SingleStateObject
{
	private UndoRedoDBPtr<Unit> ___parent;
	[HideInOutliner]
	public new DBPtr<Unit> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<StatsContainer> _stats;
	private UndoRedoDBPtr<UnitTargetingParameters> _targetingParams;
	private UndoRedoDBPtr<BaseAttack> _attackAbility;
	private TextRef _description;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedo<int> _overtipBarsWidth;
	private UndoRedo<float> _overtipVerticalOffset;
	private UndoRedo<EDamageType> _nativeAttack;
	private UndoRedo<EDamageType> _nativeDefence;
	private UndoRedoDBPtr<UnitDeathParameters> _deathParameters;
	private UndoRedoAssignableList<DBPtr<Ability>> _abilities;
	private UndoRedo<float> _size;
	private UndoRedo<float> _sizeDynamic;
	private UndoRedo<float> _normalLevelling;
	private UndoRedo<EMinimapIcons> _minimapIcon;
	private UndoRedoAssignableList<DBPtr<AoeVisual>> _selectionAoe;
	private UndoRedo<int> _pathFindingSteps;
	private UndoRedoDBPtr<Interaction> _interaction;

	[Category( "Stats" )]
	[Custom("Social")]
	public DBPtr<StatsContainer> stats { get { return _stats.Get(); } set { _stats.Set( value ); } }

	[Category( "Targeting" )]
	public DBPtr<UnitTargetingParameters> targetingParams { get { return _targetingParams.Get(); } set { _targetingParams.Set( value ); } }

	[Category( "Base attack" )]
	[Description( "Basic attack ability of the unit" )]
	public DBPtr<BaseAttack> attackAbility { get { return _attackAbility.Get(); } set { _attackAbility.Set( value ); } }

	[Category( "Description" )]
	[Description( "Basic human readable name for a unit" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Description( "Common UI avatar picture for first faction" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Description( "Unit health bar width in UI pixels" )]
	public int overtipBarsWidth { get { return _overtipBarsWidth.Get(); } set { _overtipBarsWidth.Set( value ); } }

	[Description( "Vertical offset from middle of unit's AABB top face to health bar center" )]
	public float overtipVerticalOffset { get { return _overtipVerticalOffset.Get(); } set { _overtipVerticalOffset.Set( value ); } }

	[Custom("Social")]
	[Description( "Type of attack, native to the unit" )]
	public EDamageType nativeAttack { get { return _nativeAttack.Get(); } set { _nativeAttack.Set( value ); } }

	[Description( "Type of defense, native to the unit" )]
	public EDamageType nativeDefence { get { return _nativeDefence.Get(); } set { _nativeDefence.Set( value ); } }

	[Description( "Unit visual parameters of death" )]
	public DBPtr<UnitDeathParameters> deathParameters { get { return _deathParameters.Get(); } set { _deathParameters.Set( value ); } }

	[Description( "Абилки кричи" )]
	[EnumArray(typeof(EAbility))]
	public libdb.IChangeableList<DBPtr<Ability>> abilities { get { return _abilities; } set { _abilities.Assign( value ); } }

	[Description( "Object size in meters" )]
	public float size { get { return _size.Get(); } set { _size.Set( value ); } }

	[Description( "Object size for pathfinding in meters, specify -1 for use value from size" )]
	public float sizeDynamic { get { return _sizeDynamic.Get(); } set { _sizeDynamic.Set( value ); } }

	[Description( "Насколько выравнивать по нормали (0 — никак, 1 — полностью)" )]
	public float normalLevelling { get { return _normalLevelling.Get(); } set { _normalLevelling.Set( value ); } }

	[Description( "Custom minimap icon" )]
	public EMinimapIcons minimapIcon { get { return _minimapIcon.Get(); } set { _minimapIcon.Set( value ); } }

	[Description( "Visual parameters of the area of effect" )]
	[EnumArray(typeof(ESelectionAoeVisualType))]
	public libdb.IChangeableList<DBPtr<AoeVisual>> selectionAoe { get { return _selectionAoe; } set { _selectionAoe.Assign( value ); } }

	[Description( "Качество поиска пути. Для героев ставить 10, для остальных 1" )]
	public int pathFindingSteps { get { return _pathFindingSteps.Get(); } set { _pathFindingSteps.Set( value ); } }

	[Description( "Interaction params" )]
	public DBPtr<Interaction> interaction { get { return _interaction.Get(); } set { _interaction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Unit>(owner);
		_stats = new UndoRedoDBPtr<StatsContainer>( owner );
		_targetingParams = new UndoRedoDBPtr<UnitTargetingParameters>( owner );
		_attackAbility = new UndoRedoDBPtr<BaseAttack>( owner );
		_description = new TextRef( owner, new TextRef() );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_overtipBarsWidth = new UndoRedo<int>( owner, 0 );
		_overtipVerticalOffset = new UndoRedo<float>( owner, 0.0f );
		_nativeAttack = new UndoRedo<EDamageType>( owner, EDamageType.Material );
		_nativeDefence = new UndoRedo<EDamageType>( owner, EDamageType.Material );
		_deathParameters = new UndoRedoDBPtr<UnitDeathParameters>( owner );
		_abilities = new UndoRedoAssignableList<DBPtr<Ability>>( owner, typeof( EAbility ) );
		_size = new UndoRedo<float>( owner, 2.0f );
		_sizeDynamic = new UndoRedo<float>( owner, -1.0f );
		_normalLevelling = new UndoRedo<float>( owner, 0.0f );
		_minimapIcon = new UndoRedo<EMinimapIcons>( owner, EMinimapIcons.Default );
		_selectionAoe = new UndoRedoAssignableList<DBPtr<AoeVisual>>( owner, typeof( ESelectionAoeVisualType ) );
		_pathFindingSteps = new UndoRedo<int>( owner, 1 );
		_interaction = new UndoRedoDBPtr<Interaction>( owner );
		___parent.Changed += FireChangedEvent;
		_stats.Changed += FireChangedEvent;
		_targetingParams.Changed += FireChangedEvent;
		_attackAbility.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_overtipBarsWidth.Changed += FireChangedEvent;
		_overtipVerticalOffset.Changed += FireChangedEvent;
		_nativeAttack.Changed += FireChangedEvent;
		_nativeDefence.Changed += FireChangedEvent;
		_deathParameters.Changed += FireChangedEvent;
		_abilities.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
		_sizeDynamic.Changed += FireChangedEvent;
		_normalLevelling.Changed += FireChangedEvent;
		_minimapIcon.Changed += FireChangedEvent;
		_selectionAoe.Changed += FireChangedEvent;
		_pathFindingSteps.Changed += FireChangedEvent;
		_interaction.Changed += FireChangedEvent;
	}

	public Unit()
	{
		Initialize( this );
	}
	private void AssignSelf( Unit source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Unit" );
		stats = source.stats;
		targetingParams = source.targetingParams;
		attackAbility = source.attackAbility;
		description = source.description;
		image = source.image;
		overtipBarsWidth = source.overtipBarsWidth;
		overtipVerticalOffset = source.overtipVerticalOffset;
		nativeAttack = source.nativeAttack;
		nativeDefence = source.nativeDefence;
		deathParameters = source.deathParameters;
		abilities = source.abilities;
		size = source.size;
		sizeDynamic = source.sizeDynamic;
		normalLevelling = source.normalLevelling;
		minimapIcon = source.minimapIcon;
		selectionAoe = source.selectionAoe;
		pathFindingSteps = source.pathFindingSteps;
		interaction = source.interaction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Unit source = _source as Unit;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Unit" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Unit newParent = rawParent == null ? null : rawParent.Get<Unit>();
		if ( newParent == null && _newParent is Unit )
			newParent = _newParent as Unit;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stats.SetParent( newParent == null ? null : newParent._stats );
		_targetingParams.SetParent( newParent == null ? null : newParent._targetingParams );
		_attackAbility.SetParent( newParent == null ? null : newParent._attackAbility );
		_description.SetParent( newParent == null ? null : newParent._description );
		_image.SetParent( newParent == null ? null : newParent._image );
		_overtipBarsWidth.SetParent( newParent == null ? null : newParent._overtipBarsWidth );
		_overtipVerticalOffset.SetParent( newParent == null ? null : newParent._overtipVerticalOffset );
		_nativeAttack.SetParent( newParent == null ? null : newParent._nativeAttack );
		_nativeDefence.SetParent( newParent == null ? null : newParent._nativeDefence );
		_deathParameters.SetParent( newParent == null ? null : newParent._deathParameters );
		_abilities.SetParent( newParent == null ? null : newParent._abilities );
		_size.SetParent( newParent == null ? null : newParent._size );
		_sizeDynamic.SetParent( newParent == null ? null : newParent._sizeDynamic );
		_normalLevelling.SetParent( newParent == null ? null : newParent._normalLevelling );
		_minimapIcon.SetParent( newParent == null ? null : newParent._minimapIcon );
		_selectionAoe.SetParent( newParent == null ? null : newParent._selectionAoe );
		_pathFindingSteps.SetParent( newParent == null ? null : newParent._pathFindingSteps );
		_interaction.SetParent( newParent == null ? null : newParent._interaction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stats.Reset();
		_targetingParams.Reset();
		_attackAbility.Reset();
		_description.Reset();
		_image.Reset();
		_overtipBarsWidth.Reset();
		_overtipVerticalOffset.Reset();
		_nativeAttack.Reset();
		_nativeDefence.Reset();
		_deathParameters.Reset();
		_abilities.Reset();
		_size.Reset();
		_sizeDynamic.Reset();
		_normalLevelling.Reset();
		_minimapIcon.Reset();
		_selectionAoe.Reset();
		_pathFindingSteps.Reset();
		_interaction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stats.IsDerivedFromParent()
			&& _targetingParams.IsDerivedFromParent()
			&& _attackAbility.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _overtipBarsWidth.IsDerivedFromParent()
			&& _overtipVerticalOffset.IsDerivedFromParent()
			&& _nativeAttack.IsDerivedFromParent()
			&& _nativeDefence.IsDerivedFromParent()
			&& _deathParameters.IsDerivedFromParent()
			&& _abilities.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& _sizeDynamic.IsDerivedFromParent()
			&& _normalLevelling.IsDerivedFromParent()
			&& _minimapIcon.IsDerivedFromParent()
			&& _selectionAoe.IsDerivedFromParent()
			&& _pathFindingSteps.IsDerivedFromParent()
			&& _interaction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stats" )
			_stats.Reset();
		else if ( fieldName == "targetingParams" )
			_targetingParams.Reset();
		else if ( fieldName == "attackAbility" )
			_attackAbility.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "overtipBarsWidth" )
			_overtipBarsWidth.Reset();
		else if ( fieldName == "overtipVerticalOffset" )
			_overtipVerticalOffset.Reset();
		else if ( fieldName == "nativeAttack" )
			_nativeAttack.Reset();
		else if ( fieldName == "nativeDefence" )
			_nativeDefence.Reset();
		else if ( fieldName == "deathParameters" )
			_deathParameters.Reset();
		else if ( fieldName == "abilities" )
			_abilities.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else if ( fieldName == "sizeDynamic" )
			_sizeDynamic.Reset();
		else if ( fieldName == "normalLevelling" )
			_normalLevelling.Reset();
		else if ( fieldName == "minimapIcon" )
			_minimapIcon.Reset();
		else if ( fieldName == "selectionAoe" )
			_selectionAoe.Reset();
		else if ( fieldName == "pathFindingSteps" )
			_pathFindingSteps.Reset();
		else if ( fieldName == "interaction" )
			_interaction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "stats" )
			return _stats.IsDerivedFromParent();
		if ( fieldName == "targetingParams" )
			return _targetingParams.IsDerivedFromParent();
		if ( fieldName == "attackAbility" )
			return _attackAbility.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "overtipBarsWidth" )
			return _overtipBarsWidth.IsDerivedFromParent();
		if ( fieldName == "overtipVerticalOffset" )
			return _overtipVerticalOffset.IsDerivedFromParent();
		if ( fieldName == "nativeAttack" )
			return _nativeAttack.IsDerivedFromParent();
		if ( fieldName == "nativeDefence" )
			return _nativeDefence.IsDerivedFromParent();
		if ( fieldName == "deathParameters" )
			return _deathParameters.IsDerivedFromParent();
		if ( fieldName == "abilities" )
			return _abilities.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		if ( fieldName == "sizeDynamic" )
			return _sizeDynamic.IsDerivedFromParent();
		if ( fieldName == "normalLevelling" )
			return _normalLevelling.IsDerivedFromParent();
		if ( fieldName == "minimapIcon" )
			return _minimapIcon.IsDerivedFromParent();
		if ( fieldName == "selectionAoe" )
			return _selectionAoe.IsDerivedFromParent();
		if ( fieldName == "pathFindingSteps" )
			return _pathFindingSteps.IsDerivedFromParent();
		if ( fieldName == "interaction" )
			return _interaction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(2)]
[TypeId(0x9E722340)]
[UseTypeName("UNIT")]
public class Creature : Unit
{
	private UndoRedoDBPtr<Creature> ___parent;
	[HideInOutliner]
	public new DBPtr<Creature> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private HDRColor _recolor;

	public HDRColor recolor { get { return _recolor; } set { _recolor.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Creature>(owner);
		HDRColor __recolor = new HDRColor(); // Construct default object for recolor
		__recolor.A = 0.0f;
		_recolor = new HDRColor( owner, __recolor );
		___parent.Changed += FireChangedEvent;
		_recolor.Changed += FireChangedEvent;
	}

	public Creature()
	{
		Initialize( this );
	}
	private void AssignSelf( Creature source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Creature" );
		recolor = source.recolor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Creature source = _source as Creature;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Creature" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Creature newParent = rawParent == null ? null : rawParent.Get<Creature>();
		if ( newParent == null && _newParent is Creature )
			newParent = _newParent as Creature;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_recolor.SetParent( newParent == null ? null : newParent._recolor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_recolor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_recolor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "recolor" )
			_recolor.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "recolor" )
			return _recolor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[TypeId(0x0F67ACC0)]
[UseTypeName("SBLD")]
public class Building : Unit
{
	private UndoRedoDBPtr<Building> ___parent;
	[HideInOutliner]
	public new DBPtr<Building> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EFaction> _faction;
	private UndoRedo<ERoute> _routeID;
	private UndoRedo<int> _routeLevel;
	private UndoRedoDBPtr<DBSceneObject> _ruinSceneObject;
	private UndoRedo<float> _showRuinDelay;
	private UndoRedo<string> _ruinLocator;
	private UndoRedoDBPtr<EffectBase> _onDamageFragEffect;
	private UndoRedoDBPtr<BasicEffectStandalone> _onDestructionEffect;
	private UndoRedo<bool> _isDecoration;
	private Vec2 _minimapIconOffset;
	private UndoRedo<float> _levelUpInterval;
	private UndoRedo<bool> _updateUnderWarfog;

	public EFaction faction { get { return _faction.Get(); } set { _faction.Set( value ); } }

	[Category( "Chains" )]
	public ERoute routeID { get { return _routeID.Get(); } set { _routeID.Set( value ); } }

	public int routeLevel { get { return _routeLevel.Get(); } set { _routeLevel.Set( value ); } }

	public DBPtr<DBSceneObject> ruinSceneObject { get { return _ruinSceneObject.Get(); } set { _ruinSceneObject.Set( value ); } }

	public float showRuinDelay { get { return _showRuinDelay.Get(); } set { _showRuinDelay.Set( value ); } }

	[Description( "Locator used for ruin placement" )]
	public string ruinLocator { get { return _ruinLocator.Get(); } set { _ruinLocator.Set( value ); } }

	public DBPtr<EffectBase> onDamageFragEffect { get { return _onDamageFragEffect.Get(); } set { _onDamageFragEffect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> onDestructionEffect { get { return _onDestructionEffect.Get(); } set { _onDestructionEffect.Set( value ); } }

	public bool isDecoration { get { return _isDecoration.Get(); } set { _isDecoration.Set( value ); } }

	public Vec2 minimapIconOffset { get { return _minimapIconOffset; } set { _minimapIconOffset.Assign( value ); } }

	[Description( "Периодичность левел-апа здания в секундах (0=никогда)" )]
	public float levelUpInterval { get { return _levelUpInterval.Get(); } set { _levelUpInterval.Set( value ); } }

	[Description( "Апдейтить вижуал здания под туманом" )]
	public bool updateUnderWarfog { get { return _updateUnderWarfog.Get(); } set { _updateUnderWarfog.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Building>(owner);
		_faction = new UndoRedo<EFaction>( owner, EFaction.Neutral );
		_routeID = new UndoRedo<ERoute>( owner, ERoute.Unassigned );
		_routeLevel = new UndoRedo<int>( owner, 0 );
		_ruinSceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_showRuinDelay = new UndoRedo<float>( owner, 0.0f );
		_ruinLocator = new UndoRedo<string>( owner, "Crash" );
		_onDamageFragEffect = new UndoRedoDBPtr<EffectBase>( owner );
		_onDestructionEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_isDecoration = new UndoRedo<bool>( owner, false );
		_minimapIconOffset = new Vec2( owner );
		_levelUpInterval = new UndoRedo<float>( owner, 0.0f );
		_updateUnderWarfog = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_faction.Changed += FireChangedEvent;
		_routeID.Changed += FireChangedEvent;
		_routeLevel.Changed += FireChangedEvent;
		_ruinSceneObject.Changed += FireChangedEvent;
		_showRuinDelay.Changed += FireChangedEvent;
		_ruinLocator.Changed += FireChangedEvent;
		_onDamageFragEffect.Changed += FireChangedEvent;
		_onDestructionEffect.Changed += FireChangedEvent;
		_isDecoration.Changed += FireChangedEvent;
		_minimapIconOffset.Changed += FireChangedEvent;
		_levelUpInterval.Changed += FireChangedEvent;
		_updateUnderWarfog.Changed += FireChangedEvent;
	}

	public Building()
	{
		Initialize( this );
	}
	private void AssignSelf( Building source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Building" );
		faction = source.faction;
		routeID = source.routeID;
		routeLevel = source.routeLevel;
		ruinSceneObject = source.ruinSceneObject;
		showRuinDelay = source.showRuinDelay;
		ruinLocator = source.ruinLocator;
		onDamageFragEffect = source.onDamageFragEffect;
		onDestructionEffect = source.onDestructionEffect;
		isDecoration = source.isDecoration;
		minimapIconOffset = source.minimapIconOffset;
		levelUpInterval = source.levelUpInterval;
		updateUnderWarfog = source.updateUnderWarfog;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Building source = _source as Building;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Building" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Building newParent = rawParent == null ? null : rawParent.Get<Building>();
		if ( newParent == null && _newParent is Building )
			newParent = _newParent as Building;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_faction.SetParent( newParent == null ? null : newParent._faction );
		_routeID.SetParent( newParent == null ? null : newParent._routeID );
		_routeLevel.SetParent( newParent == null ? null : newParent._routeLevel );
		_ruinSceneObject.SetParent( newParent == null ? null : newParent._ruinSceneObject );
		_showRuinDelay.SetParent( newParent == null ? null : newParent._showRuinDelay );
		_ruinLocator.SetParent( newParent == null ? null : newParent._ruinLocator );
		_onDamageFragEffect.SetParent( newParent == null ? null : newParent._onDamageFragEffect );
		_onDestructionEffect.SetParent( newParent == null ? null : newParent._onDestructionEffect );
		_isDecoration.SetParent( newParent == null ? null : newParent._isDecoration );
		_minimapIconOffset.SetParent( newParent == null ? null : newParent._minimapIconOffset );
		_levelUpInterval.SetParent( newParent == null ? null : newParent._levelUpInterval );
		_updateUnderWarfog.SetParent( newParent == null ? null : newParent._updateUnderWarfog );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_faction.Reset();
		_routeID.Reset();
		_routeLevel.Reset();
		_ruinSceneObject.Reset();
		_showRuinDelay.Reset();
		_ruinLocator.Reset();
		_onDamageFragEffect.Reset();
		_onDestructionEffect.Reset();
		_isDecoration.Reset();
		_minimapIconOffset.Reset();
		_levelUpInterval.Reset();
		_updateUnderWarfog.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_faction.IsDerivedFromParent()
			&& _routeID.IsDerivedFromParent()
			&& _routeLevel.IsDerivedFromParent()
			&& _ruinSceneObject.IsDerivedFromParent()
			&& _showRuinDelay.IsDerivedFromParent()
			&& _ruinLocator.IsDerivedFromParent()
			&& _onDamageFragEffect.IsDerivedFromParent()
			&& _onDestructionEffect.IsDerivedFromParent()
			&& _isDecoration.IsDerivedFromParent()
			&& _minimapIconOffset.IsDerivedFromParent()
			&& _levelUpInterval.IsDerivedFromParent()
			&& _updateUnderWarfog.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "faction" )
			_faction.Reset();
		else if ( fieldName == "routeID" )
			_routeID.Reset();
		else if ( fieldName == "routeLevel" )
			_routeLevel.Reset();
		else if ( fieldName == "ruinSceneObject" )
			_ruinSceneObject.Reset();
		else if ( fieldName == "showRuinDelay" )
			_showRuinDelay.Reset();
		else if ( fieldName == "ruinLocator" )
			_ruinLocator.Reset();
		else if ( fieldName == "onDamageFragEffect" )
			_onDamageFragEffect.Reset();
		else if ( fieldName == "onDestructionEffect" )
			_onDestructionEffect.Reset();
		else if ( fieldName == "isDecoration" )
			_isDecoration.Reset();
		else if ( fieldName == "minimapIconOffset" )
			_minimapIconOffset.Reset();
		else if ( fieldName == "levelUpInterval" )
			_levelUpInterval.Reset();
		else if ( fieldName == "updateUnderWarfog" )
			_updateUnderWarfog.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "faction" )
			return _faction.IsDerivedFromParent();
		if ( fieldName == "routeID" )
			return _routeID.IsDerivedFromParent();
		if ( fieldName == "routeLevel" )
			return _routeLevel.IsDerivedFromParent();
		if ( fieldName == "ruinSceneObject" )
			return _ruinSceneObject.IsDerivedFromParent();
		if ( fieldName == "showRuinDelay" )
			return _showRuinDelay.IsDerivedFromParent();
		if ( fieldName == "ruinLocator" )
			return _ruinLocator.IsDerivedFromParent();
		if ( fieldName == "onDamageFragEffect" )
			return _onDamageFragEffect.IsDerivedFromParent();
		if ( fieldName == "onDestructionEffect" )
			return _onDestructionEffect.IsDerivedFromParent();
		if ( fieldName == "isDecoration" )
			return _isDecoration.IsDerivedFromParent();
		if ( fieldName == "minimapIconOffset" )
			return _minimapIconOffset.IsDerivedFromParent();
		if ( fieldName == "levelUpInterval" )
			return _levelUpInterval.IsDerivedFromParent();
		if ( fieldName == "updateUnderWarfog" )
			return _updateUnderWarfog.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
public class BattleBuilding : Building
{
	private UndoRedoDBPtr<BattleBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<BattleBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _baseRotation;

	[Description( "Tower turret initial and idle rotation (angles)" )]
	[FloatMinMax(0, 360)]
	public float baseRotation { get { return _baseRotation.Get(); } set { _baseRotation.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BattleBuilding>(owner);
		_baseRotation = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_baseRotation.Changed += FireChangedEvent;
	}

	public BattleBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( BattleBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BattleBuilding" );
		baseRotation = source.baseRotation;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BattleBuilding source = _source as BattleBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BattleBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BattleBuilding newParent = rawParent == null ? null : rawParent.Get<BattleBuilding>();
		if ( newParent == null && _newParent is BattleBuilding )
			newParent = _newParent as BattleBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_baseRotation.SetParent( newParent == null ? null : newParent._baseRotation );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_baseRotation.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_baseRotation.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "baseRotation" )
			_baseRotation.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "baseRotation" )
			return _baseRotation.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[TypeId(0x2C5BE300)]
[UseTypeName("TOWR")]
public class Tower : BattleBuilding
{
	private UndoRedoDBPtr<Tower> ___parent;
	[HideInOutliner]
	public new DBPtr<Tower> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Tower>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public Tower()
	{
		Initialize( this );
	}
	private void AssignSelf( Tower source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Tower" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Tower source = _source as Tower;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Tower" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Tower newParent = rawParent == null ? null : rawParent.Get<Tower>();
		if ( newParent == null && _newParent is Tower )
			newParent = _newParent as Tower;
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

[DBVersion(3)]
[TypeId(0x1E59D400)]
[UseTypeName("CREEP")]
public class AdvMapCreep : Creature
{
	private UndoRedoDBPtr<AdvMapCreep> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapCreep> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ECreepType> _creepType;

	public ECreepType creepType { get { return _creepType.Get(); } set { _creepType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapCreep>(owner);
		_creepType = new UndoRedo<ECreepType>( owner, ECreepType.FactionalNormal );
		___parent.Changed += FireChangedEvent;
		_creepType.Changed += FireChangedEvent;
	}

	public AdvMapCreep()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapCreep source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCreep" );
		creepType = source.creepType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapCreep source = _source as AdvMapCreep;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCreep" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapCreep newParent = rawParent == null ? null : rawParent.Get<AdvMapCreep>();
		if ( newParent == null && _newParent is AdvMapCreep )
			newParent = _newParent as AdvMapCreep;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_creepType.SetParent( newParent == null ? null : newParent._creepType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_creepType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_creepType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "creepType" )
			_creepType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "creepType" )
			return _creepType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[IndexField("persistentId")]
[TypeId(0xB199C400)]
[UseTypeName("CREEPSKIN")]
public class CreepSkin : DBResource
{
	private UndoRedoDBPtr<CreepSkin> ___parent;
	[HideInOutliner]
	public new DBPtr<CreepSkin> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _heroPersistentId;
	private TextRef _description;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedoDBPtr<DBSceneObject> _sceneObject;
	private UndoRedoDBPtr<UnitDeathParameters> _deathParameters;

	[Custom("Social")]
	[Description( "Hero Skin ID" )]
	public string heroPersistentId { get { return _heroPersistentId.Get(); } set { _heroPersistentId.Set( value ); } }

	[Custom("Social")]
	[Description( "Human readable skin name" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Custom("Social")]
	[Description( "Hero UI avatar picture" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Description( "Scene object" )]
	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	[Description( "Death parameters" )]
	public DBPtr<UnitDeathParameters> deathParameters { get { return _deathParameters.Get(); } set { _deathParameters.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CreepSkin>(owner);
		_heroPersistentId = new UndoRedo<string>( owner, string.Empty );
		_description = new TextRef( owner, new TextRef() );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_deathParameters = new UndoRedoDBPtr<UnitDeathParameters>( owner );
		___parent.Changed += FireChangedEvent;
		_heroPersistentId.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_deathParameters.Changed += FireChangedEvent;
	}

	public CreepSkin()
	{
		Initialize( this );
	}
	private void AssignSelf( CreepSkin source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CreepSkin" );
		heroPersistentId = source.heroPersistentId;
		description = source.description;
		image = source.image;
		sceneObject = source.sceneObject;
		deathParameters = source.deathParameters;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CreepSkin source = _source as CreepSkin;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepSkin" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CreepSkin newParent = rawParent == null ? null : rawParent.Get<CreepSkin>();
		if ( newParent == null && _newParent is CreepSkin )
			newParent = _newParent as CreepSkin;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroPersistentId.SetParent( newParent == null ? null : newParent._heroPersistentId );
		_description.SetParent( newParent == null ? null : newParent._description );
		_image.SetParent( newParent == null ? null : newParent._image );
		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		_deathParameters.SetParent( newParent == null ? null : newParent._deathParameters );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroPersistentId.Reset();
		_description.Reset();
		_image.Reset();
		_sceneObject.Reset();
		_deathParameters.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroPersistentId.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _sceneObject.IsDerivedFromParent()
			&& _deathParameters.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroPersistentId" )
			_heroPersistentId.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else if ( fieldName == "deathParameters" )
			_deathParameters.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroPersistentId" )
			return _heroPersistentId.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
		if ( fieldName == "deathParameters" )
			return _deathParameters.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0F6693C0)]
[UseTypeName("CSTM")]
public class CreepSpawnTimer : DBResource
{
	private UndoRedoDBPtr<CreepSpawnTimer> ___parent;
	[HideInOutliner]
	public new DBPtr<CreepSpawnTimer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _startDelay;
	private UndoRedo<int> _spawnDelay;
	private UndoRedo<ESpawnType> _spawnType;

	public int startDelay { get { return _startDelay.Get(); } set { _startDelay.Set( value ); } }

	public int spawnDelay { get { return _spawnDelay.Get(); } set { _spawnDelay.Set( value ); } }

	[Description( "Defines when CREEP should spawn, BEFORE or AFTER destruction of the barracks on the line, or both." )]
	public ESpawnType spawnType { get { return _spawnType.Get(); } set { _spawnType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CreepSpawnTimer>(owner);
		_startDelay = new UndoRedo<int>( owner, 0 );
		_spawnDelay = new UndoRedo<int>( owner, 1 );
		_spawnType = new UndoRedo<ESpawnType>( owner, ESpawnType.After | ESpawnType.Before );
		___parent.Changed += FireChangedEvent;
		_startDelay.Changed += FireChangedEvent;
		_spawnDelay.Changed += FireChangedEvent;
		_spawnType.Changed += FireChangedEvent;
	}

	public CreepSpawnTimer()
	{
		Initialize( this );
	}
	private void AssignSelf( CreepSpawnTimer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CreepSpawnTimer" );
		startDelay = source.startDelay;
		spawnDelay = source.spawnDelay;
		spawnType = source.spawnType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CreepSpawnTimer source = _source as CreepSpawnTimer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepSpawnTimer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CreepSpawnTimer newParent = rawParent == null ? null : rawParent.Get<CreepSpawnTimer>();
		if ( newParent == null && _newParent is CreepSpawnTimer )
			newParent = _newParent as CreepSpawnTimer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_startDelay.SetParent( newParent == null ? null : newParent._startDelay );
		_spawnDelay.SetParent( newParent == null ? null : newParent._spawnDelay );
		_spawnType.SetParent( newParent == null ? null : newParent._spawnType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_startDelay.Reset();
		_spawnDelay.Reset();
		_spawnType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_startDelay.IsDerivedFromParent()
			&& _spawnDelay.IsDerivedFromParent()
			&& _spawnType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "startDelay" )
			_startDelay.Reset();
		else if ( fieldName == "spawnDelay" )
			_spawnDelay.Reset();
		else if ( fieldName == "spawnType" )
			_spawnType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "startDelay" )
			return _startDelay.IsDerivedFromParent();
		if ( fieldName == "spawnDelay" )
			return _spawnDelay.IsDerivedFromParent();
		if ( fieldName == "spawnType" )
			return _spawnType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2B832BC0)]
[UseTypeName("CRITTER")]
public class Critter : SingleStateObject
{
	private UndoRedoDBPtr<Critter> ___parent;
	[HideInOutliner]
	public new DBPtr<Critter> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _moveRadius;
	private UndoRedo<float> _alarmRadius;
	private UndoRedo<float> _calmDownTime;
	private UndoRedo<float> _moveSpeed;
	private UndoRedo<bool> _isVisibleUnderWarfog;

	[Description( "На сколько можем отбегать от ''базы''" )]
	public float moveRadius { get { return _moveRadius.Get(); } set { _moveRadius.Set( value ); } }

	[Description( "На каком расстоянии замечаем героев" )]
	public float alarmRadius { get { return _alarmRadius.Get(); } set { _alarmRadius.Set( value ); } }

	[Description( "Через сколько секунд после ухода героя возвращаемся" )]
	public float calmDownTime { get { return _calmDownTime.Get(); } set { _calmDownTime.Set( value ); } }

	[Description( "Скорость перемещения" )]
	public float moveSpeed { get { return _moveSpeed.Get(); } set { _moveSpeed.Set( value ); } }

	[Description( "Виден ли этот Critter под варфогом. Если в true, то он виден, но при этом фризится" )]
	public bool isVisibleUnderWarfog { get { return _isVisibleUnderWarfog.Get(); } set { _isVisibleUnderWarfog.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Critter>(owner);
		_moveRadius = new UndoRedo<float>( owner, 0.0f );
		_alarmRadius = new UndoRedo<float>( owner, 0.0f );
		_calmDownTime = new UndoRedo<float>( owner, 0.0f );
		_moveSpeed = new UndoRedo<float>( owner, 0.0f );
		_isVisibleUnderWarfog = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_moveRadius.Changed += FireChangedEvent;
		_alarmRadius.Changed += FireChangedEvent;
		_calmDownTime.Changed += FireChangedEvent;
		_moveSpeed.Changed += FireChangedEvent;
		_isVisibleUnderWarfog.Changed += FireChangedEvent;
	}

	public Critter()
	{
		Initialize( this );
	}
	private void AssignSelf( Critter source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Critter" );
		moveRadius = source.moveRadius;
		alarmRadius = source.alarmRadius;
		calmDownTime = source.calmDownTime;
		moveSpeed = source.moveSpeed;
		isVisibleUnderWarfog = source.isVisibleUnderWarfog;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Critter source = _source as Critter;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Critter" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Critter newParent = rawParent == null ? null : rawParent.Get<Critter>();
		if ( newParent == null && _newParent is Critter )
			newParent = _newParent as Critter;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_moveRadius.SetParent( newParent == null ? null : newParent._moveRadius );
		_alarmRadius.SetParent( newParent == null ? null : newParent._alarmRadius );
		_calmDownTime.SetParent( newParent == null ? null : newParent._calmDownTime );
		_moveSpeed.SetParent( newParent == null ? null : newParent._moveSpeed );
		_isVisibleUnderWarfog.SetParent( newParent == null ? null : newParent._isVisibleUnderWarfog );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_moveRadius.Reset();
		_alarmRadius.Reset();
		_calmDownTime.Reset();
		_moveSpeed.Reset();
		_isVisibleUnderWarfog.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_moveRadius.IsDerivedFromParent()
			&& _alarmRadius.IsDerivedFromParent()
			&& _calmDownTime.IsDerivedFromParent()
			&& _moveSpeed.IsDerivedFromParent()
			&& _isVisibleUnderWarfog.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "moveRadius" )
			_moveRadius.Reset();
		else if ( fieldName == "alarmRadius" )
			_alarmRadius.Reset();
		else if ( fieldName == "calmDownTime" )
			_calmDownTime.Reset();
		else if ( fieldName == "moveSpeed" )
			_moveSpeed.Reset();
		else if ( fieldName == "isVisibleUnderWarfog" )
			_isVisibleUnderWarfog.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "moveRadius" )
			return _moveRadius.IsDerivedFromParent();
		if ( fieldName == "alarmRadius" )
			return _alarmRadius.IsDerivedFromParent();
		if ( fieldName == "calmDownTime" )
			return _calmDownTime.IsDerivedFromParent();
		if ( fieldName == "moveSpeed" )
			return _moveSpeed.IsDerivedFromParent();
		if ( fieldName == "isVisibleUnderWarfog" )
			return _isVisibleUnderWarfog.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0B768C41)]
[UseTypeName("FLAG")]
public class Flagpole : Unit
{
	private UndoRedoDBPtr<Flagpole> ___parent;
	[HideInOutliner]
	public new DBPtr<Flagpole> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _ownerTowers;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _effect;
	private UndoRedoAssignableList<DBPtr<Texture>> _factionImages;
	private UndoRedoAssignableList<TextRef> _factionDescriptions;

	[Description( "Выбор башен, которые дают неуязвимость флагу" )]
	public DBPtr<TargetSelector> ownerTowers { get { return _ownerTowers.Get(); } set { _ownerTowers.Set( value ); } }

	[Description( "Эффект" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> effect { get { return _effect; } set { _effect.Assign( value ); } }

	[Description( "Иконки для разных фракций" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<Texture>> factionImages { get { return _factionImages; } set { _factionImages.Assign( value ); } }

	[Description( "Описание для разных фракций" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<TextRef> factionDescriptions { get { return _factionDescriptions; } set { _factionDescriptions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Flagpole>(owner);
		_ownerTowers = new UndoRedoDBPtr<TargetSelector>( owner );
		_effect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		_factionImages = new UndoRedoAssignableList<DBPtr<Texture>>( owner, typeof( ETeamID ) );
		_factionDescriptions = new UndoRedoAssignableList<TextRef>( owner, typeof( ETeamID ) );
		___parent.Changed += FireChangedEvent;
		_ownerTowers.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
		_factionImages.Changed += FireChangedEvent;
		_factionDescriptions.Changed += FireChangedEvent;
	}

	public Flagpole()
	{
		Initialize( this );
	}
	private void AssignSelf( Flagpole source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Flagpole" );
		ownerTowers = source.ownerTowers;
		effect = source.effect;
		factionImages = source.factionImages;
		factionDescriptions = source.factionDescriptions;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Flagpole source = _source as Flagpole;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Flagpole" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Flagpole newParent = rawParent == null ? null : rawParent.Get<Flagpole>();
		if ( newParent == null && _newParent is Flagpole )
			newParent = _newParent as Flagpole;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ownerTowers.SetParent( newParent == null ? null : newParent._ownerTowers );
		_effect.SetParent( newParent == null ? null : newParent._effect );
		_factionImages.SetParent( newParent == null ? null : newParent._factionImages );
		_factionDescriptions.SetParent( newParent == null ? null : newParent._factionDescriptions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ownerTowers.Reset();
		_effect.Reset();
		_factionImages.Reset();
		_factionDescriptions.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ownerTowers.IsDerivedFromParent()
			&& _effect.IsDerivedFromParent()
			&& _factionImages.IsDerivedFromParent()
			&& _factionDescriptions.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ownerTowers" )
			_ownerTowers.Reset();
		else if ( fieldName == "effect" )
			_effect.Reset();
		else if ( fieldName == "factionImages" )
			_factionImages.Reset();
		else if ( fieldName == "factionDescriptions" )
			_factionDescriptions.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ownerTowers" )
			return _ownerTowers.IsDerivedFromParent();
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
		if ( fieldName == "factionImages" )
			return _factionImages.IsDerivedFromParent();
		if ( fieldName == "factionDescriptions" )
			return _factionDescriptions.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0F61A400)]
[UseTypeName("FNTN")]
public class Fountain : Building
{
	private UndoRedoDBPtr<Fountain> ___parent;
	[HideInOutliner]
	public new DBPtr<Fountain> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Fountain>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public Fountain()
	{
		Initialize( this );
	}
	private void AssignSelf( Fountain source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Fountain" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Fountain source = _source as Fountain;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Fountain" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Fountain newParent = rawParent == null ? null : rawParent.Get<Fountain>();
		if ( newParent == null && _newParent is Fountain )
			newParent = _newParent as Fountain;
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

[TypeId(0x0F61DC00)]
[UseTypeName("GLPH")]
public class Glyph : Ability
{
	private UndoRedoDBPtr<Glyph> ___parent;
	[HideInOutliner]
	public new DBPtr<Glyph> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EGlyph> _id;
	private UndoRedoDBPtr<SingleStateObject> _gameObject;
	private HDRColor _color;
	private UndoRedo<int> _naftaCost;
	private UndoRedo<float> _openWarFogRadius;
	private UndoRedo<EMinimapIcons> _minimapIcon;
	private UndoRedoDBPtr<Ability> _pickupAbility;

	public EGlyph id { get { return _id.Get(); } set { _id.Set( value ); } }

	public DBPtr<SingleStateObject> gameObject { get { return _gameObject.Get(); } set { _gameObject.Set( value ); } }

	public HDRColor color { get { return _color; } set { _color.Assign( value ); } }

	[Category( "Logic" )]
	public int naftaCost { get { return _naftaCost.Get(); } set { _naftaCost.Set( value ); } }

	[Description( "Radius to open warfog at glyph (0 to disable)" )]
	public float openWarFogRadius { get { return _openWarFogRadius.Get(); } set { _openWarFogRadius.Set( value ); } }

	public EMinimapIcons minimapIcon { get { return _minimapIcon.Get(); } set { _minimapIcon.Set( value ); } }

	public DBPtr<Ability> pickupAbility { get { return _pickupAbility.Get(); } set { _pickupAbility.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Glyph>(owner);
		_id = new UndoRedo<EGlyph>( owner, EGlyph.DoubleDamager );
		_gameObject = new UndoRedoDBPtr<SingleStateObject>( owner );
		HDRColor __color = new HDRColor(); // Construct default object for color
		__color.R = 1.0f;
		__color.G = 1.0f;
		__color.B = 1.0f;
		_color = new HDRColor( owner, __color );
		_naftaCost = new UndoRedo<int>( owner, 0 );
		_openWarFogRadius = new UndoRedo<float>( owner, 0.0f );
		_minimapIcon = new UndoRedo<EMinimapIcons>( owner, EMinimapIcons.None );
		_pickupAbility = new UndoRedoDBPtr<Ability>( owner );
		___parent.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_gameObject.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_naftaCost.Changed += FireChangedEvent;
		_openWarFogRadius.Changed += FireChangedEvent;
		_minimapIcon.Changed += FireChangedEvent;
		_pickupAbility.Changed += FireChangedEvent;
	}

	public Glyph()
	{
		Initialize( this );
	}
	private void AssignSelf( Glyph source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Glyph" );
		id = source.id;
		gameObject = source.gameObject;
		color = source.color;
		naftaCost = source.naftaCost;
		openWarFogRadius = source.openWarFogRadius;
		minimapIcon = source.minimapIcon;
		pickupAbility = source.pickupAbility;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Glyph source = _source as Glyph;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Glyph" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Glyph newParent = rawParent == null ? null : rawParent.Get<Glyph>();
		if ( newParent == null && _newParent is Glyph )
			newParent = _newParent as Glyph;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_id.SetParent( newParent == null ? null : newParent._id );
		_gameObject.SetParent( newParent == null ? null : newParent._gameObject );
		_color.SetParent( newParent == null ? null : newParent._color );
		_naftaCost.SetParent( newParent == null ? null : newParent._naftaCost );
		_openWarFogRadius.SetParent( newParent == null ? null : newParent._openWarFogRadius );
		_minimapIcon.SetParent( newParent == null ? null : newParent._minimapIcon );
		_pickupAbility.SetParent( newParent == null ? null : newParent._pickupAbility );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_id.Reset();
		_gameObject.Reset();
		_color.Reset();
		_naftaCost.Reset();
		_openWarFogRadius.Reset();
		_minimapIcon.Reset();
		_pickupAbility.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _gameObject.IsDerivedFromParent()
			&& _color.IsDerivedFromParent()
			&& _naftaCost.IsDerivedFromParent()
			&& _openWarFogRadius.IsDerivedFromParent()
			&& _minimapIcon.IsDerivedFromParent()
			&& _pickupAbility.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "gameObject" )
			_gameObject.Reset();
		else if ( fieldName == "color" )
			_color.Reset();
		else if ( fieldName == "naftaCost" )
			_naftaCost.Reset();
		else if ( fieldName == "openWarFogRadius" )
			_openWarFogRadius.Reset();
		else if ( fieldName == "minimapIcon" )
			_minimapIcon.Reset();
		else if ( fieldName == "pickupAbility" )
			_pickupAbility.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "gameObject" )
			return _gameObject.IsDerivedFromParent();
		if ( fieldName == "color" )
			return _color.IsDerivedFromParent();
		if ( fieldName == "naftaCost" )
			return _naftaCost.IsDerivedFromParent();
		if ( fieldName == "openWarFogRadius" )
			return _openWarFogRadius.IsDerivedFromParent();
		if ( fieldName == "minimapIcon" )
			return _minimapIcon.IsDerivedFromParent();
		if ( fieldName == "pickupAbility" )
			return _pickupAbility.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("GLDB")]
public class GlyphsDB : DBResource
{
	private UndoRedoDBPtr<GlyphsDB> ___parent;
	[HideInOutliner]
	public new DBPtr<GlyphsDB> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<GlyphEntry> _glyphs;

	public libdb.IChangeableList<GlyphEntry> glyphs { get { return _glyphs; } set { _glyphs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GlyphsDB>(owner);
		_glyphs = new UndoRedoAssignableList<GlyphEntry>( owner );
		___parent.Changed += FireChangedEvent;
		_glyphs.Changed += FireChangedEvent;
	}

	public GlyphsDB()
	{
		Initialize( this );
	}
	private void AssignSelf( GlyphsDB source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GlyphsDB" );
		glyphs = source.glyphs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GlyphsDB source = _source as GlyphsDB;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GlyphsDB" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GlyphsDB newParent = rawParent == null ? null : rawParent.Get<GlyphsDB>();
		if ( newParent == null && _newParent is GlyphsDB )
			newParent = _newParent as GlyphsDB;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_glyphs.SetParent( newParent == null ? null : newParent._glyphs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_glyphs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_glyphs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "glyphs" )
			_glyphs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "glyphs" )
			return _glyphs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0F61DC01)]
[UseTypeName("GLSPN")]
public class GlyphSpawner : GameObject
{
	private UndoRedoDBPtr<GlyphSpawner> ___parent;
	[HideInOutliner]
	public new DBPtr<GlyphSpawner> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _useGlyphManager;
	private GlyphSettings _settings;
	private UndoRedoDBPtr<GlyphsDB> _glyphs;

	[Description( "Использовать глобальные настройки глифов?" )]
	public bool useGlyphManager { get { return _useGlyphManager.Get(); } set { _useGlyphManager.Set( value ); } }

	[Description( "Кастомные параметры спавна глифов" )]
	public GlyphSettings settings { get { return _settings; } set { _settings.Assign( value ); } }

	[Description( "Кастомный список глифов" )]
	public DBPtr<GlyphsDB> glyphs { get { return _glyphs.Get(); } set { _glyphs.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GlyphSpawner>(owner);
		_useGlyphManager = new UndoRedo<bool>( owner, true );
		_settings = new GlyphSettings( owner );
		_glyphs = new UndoRedoDBPtr<GlyphsDB>( owner );
		___parent.Changed += FireChangedEvent;
		_useGlyphManager.Changed += FireChangedEvent;
		_settings.Changed += FireChangedEvent;
		_glyphs.Changed += FireChangedEvent;
	}

	public GlyphSpawner()
	{
		Initialize( this );
	}
	private void AssignSelf( GlyphSpawner source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GlyphSpawner" );
		useGlyphManager = source.useGlyphManager;
		settings = source.settings;
		glyphs = source.glyphs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GlyphSpawner source = _source as GlyphSpawner;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GlyphSpawner" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GlyphSpawner newParent = rawParent == null ? null : rawParent.Get<GlyphSpawner>();
		if ( newParent == null && _newParent is GlyphSpawner )
			newParent = _newParent as GlyphSpawner;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_useGlyphManager.SetParent( newParent == null ? null : newParent._useGlyphManager );
		_settings.SetParent( newParent == null ? null : newParent._settings );
		_glyphs.SetParent( newParent == null ? null : newParent._glyphs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_useGlyphManager.Reset();
		_settings.Reset();
		_glyphs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_useGlyphManager.IsDerivedFromParent()
			&& _settings.IsDerivedFromParent()
			&& _glyphs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "useGlyphManager" )
			_useGlyphManager.Reset();
		else if ( fieldName == "settings" )
			_settings.Reset();
		else if ( fieldName == "glyphs" )
			_glyphs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "useGlyphManager" )
			return _useGlyphManager.IsDerivedFromParent();
		if ( fieldName == "settings" )
			return _settings.IsDerivedFromParent();
		if ( fieldName == "glyphs" )
			return _glyphs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(5)]
public class BaseHero : Creature
{
	private UndoRedoDBPtr<BaseHero> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseHero> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _heroSceneObjects;
	private UndoRedo<EGender> _gender;
	private UndoRedoAssignableList<AskSounds> _askLists;
	private UndoRedoAssignableList<AskSounds> _askListsSecondState;
	private TextRef _heroNameA;
	private TextRef _heroNameB;
	private UndoRedoDBPtr<Texture> _heroImageA;
	private UndoRedoDBPtr<Texture> _heroImageB;
	private UndoRedo<string> _persistentId;
	private UndoRedo<string> _antagonistId;
	private UndoRedoList<string> _mmakingAntagonists;
	private UndoRedoDBPtr<Texture> _minimapIconA;
	private UndoRedoDBPtr<Texture> _minimapIconB;
	private UndoRedo<EHeroRaces> _heroRace;
	private UndoRedoList<EStat> _recommendedStats;
	private UndoRedoAssignableList<DBPtr<HeroSkin>> _heroSkins;
	private UndoRedoAssignableList<SummonedUnits> _summonedUnits;
	private UndoRedo<float> _totalStatsBudget;
	private UndoRedoDBPtr<HeroResource> _uniqueResource;

	[Description( "Scene objects by team ID" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> heroSceneObjects { get { return _heroSceneObjects; } set { _heroSceneObjects.Assign( value ); } }

	[Custom("DBServer", "Social")]
	public EGender gender { get { return _gender.Get(); } set { _gender.Set( value ); } }

	[Category( "Asks" )]
	[Description( "Hero acknowledgment sounds by team ID" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<AskSounds> askLists { get { return _askLists; } set { _askLists.Assign( value ); } }

	[Category( "Asks" )]
	[Description( "Hero acknowledgment sounds by team ID (second hero state)" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<AskSounds> askListsSecondState { get { return _askListsSecondState; } set { _askListsSecondState.Assign( value ); } }

	[Custom("Social")]
	[Description( "Human readable hero name for first faction" )]
	public TextRef heroNameA { get { return _heroNameA; } set { _heroNameA.Assign( value ); } }

	[Custom("Social")]
	[Description( "Human readable hero name for second faction" )]
	public TextRef heroNameB { get { return _heroNameB; } set { _heroNameB.Assign( value ); } }

	[Custom("Social")]
	[Description( "Hero UI avatar picture for first faction" )]
	public DBPtr<Texture> heroImageA { get { return _heroImageA.Get(); } set { _heroImageA.Set( value ); } }

	[Custom("Social")]
	[Description( "Hero UI avatar picture for second faction" )]
	public DBPtr<Texture> heroImageB { get { return _heroImageB.Get(); } set { _heroImageB.Set( value ); } }

	[Custom("Social")]
	[Description( "Global Hero ID" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Custom("Social")]
	[Description( "ID for antagonist" )]
	public string antagonistId { get { return _antagonistId.Get(); } set { _antagonistId.Set( value ); } }

	[Custom("DBServer")]
	[Description( "IDs of antagonists for matchmaking" )]
	public libdb.IChangeableList<string> mmakingAntagonists { get { return _mmakingAntagonists; } set { _mmakingAntagonists.Assign( value ); } }

	[Custom("Social")]
	[Description( "Hero minimap icon for first faction" )]
	public DBPtr<Texture> minimapIconA { get { return _minimapIconA.Get(); } set { _minimapIconA.Set( value ); } }

	[Custom("Social")]
	[Description( "Hero minimap icon for second faction" )]
	public DBPtr<Texture> minimapIconB { get { return _minimapIconB.Get(); } set { _minimapIconB.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Enabled hero races" )]
	public EHeroRaces heroRace { get { return _heroRace.Get(); } set { _heroRace.Set( value ); } }

	[Custom("Social")]
	[Description( "Recommended stats" )]
	public libdb.IChangeableList<EStat> recommendedStats { get { return _recommendedStats; } set { _recommendedStats.Assign( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "List of available skins" )]
	public libdb.IChangeableList<DBPtr<HeroSkin>> heroSkins { get { return _heroSkins; } set { _heroSkins.Assign( value ); } }

	[Description( "Units available to summon" )]
	public libdb.IChangeableList<SummonedUnits> summonedUnits { get { return _summonedUnits; } set { _summonedUnits.Assign( value ); } }

	[Browsable( false )]
	[Custom("Social")]
	[NoCode]
	public float totalStatsBudget { get { return _totalStatsBudget.Get(); } set { _totalStatsBudget.Set( value ); } }

	[Custom("Social")]
	public DBPtr<HeroResource> uniqueResource { get { return _uniqueResource.Get(); } set { _uniqueResource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseHero>(owner);
		_heroSceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ETeamID ) );
		_gender = new UndoRedo<EGender>( owner, EGender.Male );
		_askLists = new UndoRedoAssignableList<AskSounds>( owner, typeof( ETeamID ) );
		_askListsSecondState = new UndoRedoAssignableList<AskSounds>( owner, typeof( ETeamID ) );
		_heroNameA = new TextRef( owner, new TextRef() );
		_heroNameB = new TextRef( owner, new TextRef() );
		_heroImageA = new UndoRedoDBPtr<Texture>( owner );
		_heroImageB = new UndoRedoDBPtr<Texture>( owner );
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_antagonistId = new UndoRedo<string>( owner, string.Empty );
		_mmakingAntagonists = new UndoRedoList<string>( owner );
		_minimapIconA = new UndoRedoDBPtr<Texture>( owner );
		_minimapIconB = new UndoRedoDBPtr<Texture>( owner );
		_heroRace = new UndoRedo<EHeroRaces>( owner, EHeroRaces.B | EHeroRaces.A );
		_recommendedStats = new UndoRedoList<EStat>( owner );
		_heroSkins = new UndoRedoAssignableList<DBPtr<HeroSkin>>( owner );
		_summonedUnits = new UndoRedoAssignableList<SummonedUnits>( owner );
		_totalStatsBudget = new UndoRedo<float>( owner, 0.0f );
		_uniqueResource = new UndoRedoDBPtr<HeroResource>( owner );
		___parent.Changed += FireChangedEvent;
		_heroSceneObjects.Changed += FireChangedEvent;
		_gender.Changed += FireChangedEvent;
		_askLists.Changed += FireChangedEvent;
		_askListsSecondState.Changed += FireChangedEvent;
		_heroNameA.Changed += FireChangedEvent;
		_heroNameB.Changed += FireChangedEvent;
		_heroImageA.Changed += FireChangedEvent;
		_heroImageB.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_antagonistId.Changed += FireChangedEvent;
		_mmakingAntagonists.Changed += FireChangedEvent;
		_minimapIconA.Changed += FireChangedEvent;
		_minimapIconB.Changed += FireChangedEvent;
		_heroRace.Changed += FireChangedEvent;
		_recommendedStats.Changed += FireChangedEvent;
		_heroSkins.Changed += FireChangedEvent;
		_summonedUnits.Changed += FireChangedEvent;
		_totalStatsBudget.Changed += FireChangedEvent;
		_uniqueResource.Changed += FireChangedEvent;
	}

	public BaseHero()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseHero source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseHero" );
		heroSceneObjects = source.heroSceneObjects;
		gender = source.gender;
		askLists = source.askLists;
		askListsSecondState = source.askListsSecondState;
		heroNameA = source.heroNameA;
		heroNameB = source.heroNameB;
		heroImageA = source.heroImageA;
		heroImageB = source.heroImageB;
		persistentId = source.persistentId;
		antagonistId = source.antagonistId;
		mmakingAntagonists = source.mmakingAntagonists;
		minimapIconA = source.minimapIconA;
		minimapIconB = source.minimapIconB;
		heroRace = source.heroRace;
		recommendedStats = source.recommendedStats;
		heroSkins = source.heroSkins;
		summonedUnits = source.summonedUnits;
		totalStatsBudget = source.totalStatsBudget;
		uniqueResource = source.uniqueResource;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseHero source = _source as BaseHero;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseHero" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseHero newParent = rawParent == null ? null : rawParent.Get<BaseHero>();
		if ( newParent == null && _newParent is BaseHero )
			newParent = _newParent as BaseHero;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroSceneObjects.SetParent( newParent == null ? null : newParent._heroSceneObjects );
		_gender.SetParent( newParent == null ? null : newParent._gender );
		_askLists.SetParent( newParent == null ? null : newParent._askLists );
		_askListsSecondState.SetParent( newParent == null ? null : newParent._askListsSecondState );
		_heroNameA.SetParent( newParent == null ? null : newParent._heroNameA );
		_heroNameB.SetParent( newParent == null ? null : newParent._heroNameB );
		_heroImageA.SetParent( newParent == null ? null : newParent._heroImageA );
		_heroImageB.SetParent( newParent == null ? null : newParent._heroImageB );
		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_antagonistId.SetParent( newParent == null ? null : newParent._antagonistId );
		_mmakingAntagonists.SetParent( newParent == null ? null : newParent._mmakingAntagonists );
		_minimapIconA.SetParent( newParent == null ? null : newParent._minimapIconA );
		_minimapIconB.SetParent( newParent == null ? null : newParent._minimapIconB );
		_heroRace.SetParent( newParent == null ? null : newParent._heroRace );
		_recommendedStats.SetParent( newParent == null ? null : newParent._recommendedStats );
		_heroSkins.SetParent( newParent == null ? null : newParent._heroSkins );
		_summonedUnits.SetParent( newParent == null ? null : newParent._summonedUnits );
		_totalStatsBudget.SetParent( newParent == null ? null : newParent._totalStatsBudget );
		_uniqueResource.SetParent( newParent == null ? null : newParent._uniqueResource );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroSceneObjects.Reset();
		_gender.Reset();
		_askLists.Reset();
		_askListsSecondState.Reset();
		_heroNameA.Reset();
		_heroNameB.Reset();
		_heroImageA.Reset();
		_heroImageB.Reset();
		_persistentId.Reset();
		_antagonistId.Reset();
		_mmakingAntagonists.Reset();
		_minimapIconA.Reset();
		_minimapIconB.Reset();
		_heroRace.Reset();
		_recommendedStats.Reset();
		_heroSkins.Reset();
		_summonedUnits.Reset();
		_totalStatsBudget.Reset();
		_uniqueResource.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroSceneObjects.IsDerivedFromParent()
			&& _gender.IsDerivedFromParent()
			&& _askLists.IsDerivedFromParent()
			&& _askListsSecondState.IsDerivedFromParent()
			&& _heroNameA.IsDerivedFromParent()
			&& _heroNameB.IsDerivedFromParent()
			&& _heroImageA.IsDerivedFromParent()
			&& _heroImageB.IsDerivedFromParent()
			&& _persistentId.IsDerivedFromParent()
			&& _antagonistId.IsDerivedFromParent()
			&& _mmakingAntagonists.IsDerivedFromParent()
			&& _minimapIconA.IsDerivedFromParent()
			&& _minimapIconB.IsDerivedFromParent()
			&& _heroRace.IsDerivedFromParent()
			&& _recommendedStats.IsDerivedFromParent()
			&& _heroSkins.IsDerivedFromParent()
			&& _summonedUnits.IsDerivedFromParent()
			&& _totalStatsBudget.IsDerivedFromParent()
			&& _uniqueResource.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroSceneObjects" )
			_heroSceneObjects.Reset();
		else if ( fieldName == "gender" )
			_gender.Reset();
		else if ( fieldName == "askLists" )
			_askLists.Reset();
		else if ( fieldName == "askListsSecondState" )
			_askListsSecondState.Reset();
		else if ( fieldName == "heroNameA" )
			_heroNameA.Reset();
		else if ( fieldName == "heroNameB" )
			_heroNameB.Reset();
		else if ( fieldName == "heroImageA" )
			_heroImageA.Reset();
		else if ( fieldName == "heroImageB" )
			_heroImageB.Reset();
		else if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "antagonistId" )
			_antagonistId.Reset();
		else if ( fieldName == "mmakingAntagonists" )
			_mmakingAntagonists.Reset();
		else if ( fieldName == "minimapIconA" )
			_minimapIconA.Reset();
		else if ( fieldName == "minimapIconB" )
			_minimapIconB.Reset();
		else if ( fieldName == "heroRace" )
			_heroRace.Reset();
		else if ( fieldName == "recommendedStats" )
			_recommendedStats.Reset();
		else if ( fieldName == "heroSkins" )
			_heroSkins.Reset();
		else if ( fieldName == "summonedUnits" )
			_summonedUnits.Reset();
		else if ( fieldName == "totalStatsBudget" )
			_totalStatsBudget.Reset();
		else if ( fieldName == "uniqueResource" )
			_uniqueResource.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroSceneObjects" )
			return _heroSceneObjects.IsDerivedFromParent();
		if ( fieldName == "gender" )
			return _gender.IsDerivedFromParent();
		if ( fieldName == "askLists" )
			return _askLists.IsDerivedFromParent();
		if ( fieldName == "askListsSecondState" )
			return _askListsSecondState.IsDerivedFromParent();
		if ( fieldName == "heroNameA" )
			return _heroNameA.IsDerivedFromParent();
		if ( fieldName == "heroNameB" )
			return _heroNameB.IsDerivedFromParent();
		if ( fieldName == "heroImageA" )
			return _heroImageA.IsDerivedFromParent();
		if ( fieldName == "heroImageB" )
			return _heroImageB.IsDerivedFromParent();
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "antagonistId" )
			return _antagonistId.IsDerivedFromParent();
		if ( fieldName == "mmakingAntagonists" )
			return _mmakingAntagonists.IsDerivedFromParent();
		if ( fieldName == "minimapIconA" )
			return _minimapIconA.IsDerivedFromParent();
		if ( fieldName == "minimapIconB" )
			return _minimapIconB.IsDerivedFromParent();
		if ( fieldName == "heroRace" )
			return _heroRace.IsDerivedFromParent();
		if ( fieldName == "recommendedStats" )
			return _recommendedStats.IsDerivedFromParent();
		if ( fieldName == "heroSkins" )
			return _heroSkins.IsDerivedFromParent();
		if ( fieldName == "summonedUnits" )
			return _summonedUnits.IsDerivedFromParent();
		if ( fieldName == "totalStatsBudget" )
			return _totalStatsBudget.IsDerivedFromParent();
		if ( fieldName == "uniqueResource" )
			return _uniqueResource.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[UseTypeName("HLVL")]
public class HeroesLevelUps : DBResource
{
	private UndoRedoDBPtr<HeroesLevelUps> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroesLevelUps> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _developmentPoints;
	private UndoRedoDBPtr<KillExperienceModifier> _killExperienceModifiers;

	public libdb.IChangeableList<int> developmentPoints { get { return _developmentPoints; } set { _developmentPoints.Assign( value ); } }

	public DBPtr<KillExperienceModifier> killExperienceModifiers { get { return _killExperienceModifiers.Get(); } set { _killExperienceModifiers.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroesLevelUps>(owner);
		_developmentPoints = new UndoRedoList<int>( owner );
		_killExperienceModifiers = new UndoRedoDBPtr<KillExperienceModifier>( owner );
		___parent.Changed += FireChangedEvent;
		_developmentPoints.Changed += FireChangedEvent;
		_killExperienceModifiers.Changed += FireChangedEvent;
	}

	public HeroesLevelUps()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroesLevelUps source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroesLevelUps" );
		developmentPoints = source.developmentPoints;
		killExperienceModifiers = source.killExperienceModifiers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroesLevelUps source = _source as HeroesLevelUps;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroesLevelUps" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroesLevelUps newParent = rawParent == null ? null : rawParent.Get<HeroesLevelUps>();
		if ( newParent == null && _newParent is HeroesLevelUps )
			newParent = _newParent as HeroesLevelUps;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_developmentPoints.SetParent( newParent == null ? null : newParent._developmentPoints );
		_killExperienceModifiers.SetParent( newParent == null ? null : newParent._killExperienceModifiers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_developmentPoints.Reset();
		_killExperienceModifiers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_developmentPoints.IsDerivedFromParent()
			&& _killExperienceModifiers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "developmentPoints" )
			_developmentPoints.Reset();
		else if ( fieldName == "killExperienceModifiers" )
			_killExperienceModifiers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "developmentPoints" )
			return _developmentPoints.IsDerivedFromParent();
		if ( fieldName == "killExperienceModifiers" )
			return _killExperienceModifiers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2C5B3C81)]
[UseTypeName("HPLH")]
public class HeroPlaceHolder : GameObject
{
	private UndoRedoDBPtr<HeroPlaceHolder> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroPlaceHolder> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETeamID> _teamId;

	public ETeamID teamId { get { return _teamId.Get(); } set { _teamId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroPlaceHolder>(owner);
		_teamId = new UndoRedo<ETeamID>( owner, ETeamID.A );
		___parent.Changed += FireChangedEvent;
		_teamId.Changed += FireChangedEvent;
	}

	public HeroPlaceHolder()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroPlaceHolder source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroPlaceHolder" );
		teamId = source.teamId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroPlaceHolder source = _source as HeroPlaceHolder;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroPlaceHolder" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroPlaceHolder newParent = rawParent == null ? null : rawParent.Get<HeroPlaceHolder>();
		if ( newParent == null && _newParent is HeroPlaceHolder )
			newParent = _newParent as HeroPlaceHolder;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_teamId.SetParent( newParent == null ? null : newParent._teamId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_teamId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_teamId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "teamId" )
			_teamId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "teamId" )
			return _teamId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class HeroResource : DBResource
{
	private UndoRedoDBPtr<HeroResource> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroResource> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _formulaNameValue;
	private UndoRedo<string> _formulaNameMaximum;
	private UndoRedo<string> _formulaNameRegeneration;
	private UndoRedoDBPtr<BaseUIMaterial> _overtipManaProgressMaterial;
	private Color _uiManaBarColor;
	private TextRef _name;
	private TextRef _tooltip;
	private UndoRedo<float> _castleValueMaximum;

	public string formulaNameValue { get { return _formulaNameValue.Get(); } set { _formulaNameValue.Set( value ); } }

	public string formulaNameMaximum { get { return _formulaNameMaximum.Get(); } set { _formulaNameMaximum.Set( value ); } }

	public string formulaNameRegeneration { get { return _formulaNameRegeneration.Get(); } set { _formulaNameRegeneration.Set( value ); } }

	public DBPtr<BaseUIMaterial> overtipManaProgressMaterial { get { return _overtipManaProgressMaterial.Get(); } set { _overtipManaProgressMaterial.Set( value ); } }

	public Color uiManaBarColor { get { return _uiManaBarColor; } set { _uiManaBarColor.Assign( value ); } }

	[Custom("Social")]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Custom("Social")]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Custom("Social")]
	public float castleValueMaximum { get { return _castleValueMaximum.Get(); } set { _castleValueMaximum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroResource>(owner);
		_formulaNameValue = new UndoRedo<string>( owner, string.Empty );
		_formulaNameMaximum = new UndoRedo<string>( owner, string.Empty );
		_formulaNameRegeneration = new UndoRedo<string>( owner, string.Empty );
		_overtipManaProgressMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		Color __uiManaBarColor = new Color(); // Construct default object for uiManaBarColor
		__uiManaBarColor.R = 255;
		__uiManaBarColor.B = 255;
		_uiManaBarColor = new Color( owner, __uiManaBarColor );
		_name = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_castleValueMaximum = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_formulaNameValue.Changed += FireChangedEvent;
		_formulaNameMaximum.Changed += FireChangedEvent;
		_formulaNameRegeneration.Changed += FireChangedEvent;
		_overtipManaProgressMaterial.Changed += FireChangedEvent;
		_uiManaBarColor.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_castleValueMaximum.Changed += FireChangedEvent;
	}

	public HeroResource()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroResource source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroResource" );
		formulaNameValue = source.formulaNameValue;
		formulaNameMaximum = source.formulaNameMaximum;
		formulaNameRegeneration = source.formulaNameRegeneration;
		overtipManaProgressMaterial = source.overtipManaProgressMaterial;
		uiManaBarColor = source.uiManaBarColor;
		name = source.name;
		tooltip = source.tooltip;
		castleValueMaximum = source.castleValueMaximum;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroResource source = _source as HeroResource;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroResource" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroResource newParent = rawParent == null ? null : rawParent.Get<HeroResource>();
		if ( newParent == null && _newParent is HeroResource )
			newParent = _newParent as HeroResource;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_formulaNameValue.SetParent( newParent == null ? null : newParent._formulaNameValue );
		_formulaNameMaximum.SetParent( newParent == null ? null : newParent._formulaNameMaximum );
		_formulaNameRegeneration.SetParent( newParent == null ? null : newParent._formulaNameRegeneration );
		_overtipManaProgressMaterial.SetParent( newParent == null ? null : newParent._overtipManaProgressMaterial );
		_uiManaBarColor.SetParent( newParent == null ? null : newParent._uiManaBarColor );
		_name.SetParent( newParent == null ? null : newParent._name );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_castleValueMaximum.SetParent( newParent == null ? null : newParent._castleValueMaximum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_formulaNameValue.Reset();
		_formulaNameMaximum.Reset();
		_formulaNameRegeneration.Reset();
		_overtipManaProgressMaterial.Reset();
		_uiManaBarColor.Reset();
		_name.Reset();
		_tooltip.Reset();
		_castleValueMaximum.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_formulaNameValue.IsDerivedFromParent()
			&& _formulaNameMaximum.IsDerivedFromParent()
			&& _formulaNameRegeneration.IsDerivedFromParent()
			&& _overtipManaProgressMaterial.IsDerivedFromParent()
			&& _uiManaBarColor.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _castleValueMaximum.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "formulaNameValue" )
			_formulaNameValue.Reset();
		else if ( fieldName == "formulaNameMaximum" )
			_formulaNameMaximum.Reset();
		else if ( fieldName == "formulaNameRegeneration" )
			_formulaNameRegeneration.Reset();
		else if ( fieldName == "overtipManaProgressMaterial" )
			_overtipManaProgressMaterial.Reset();
		else if ( fieldName == "uiManaBarColor" )
			_uiManaBarColor.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "castleValueMaximum" )
			_castleValueMaximum.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "formulaNameValue" )
			return _formulaNameValue.IsDerivedFromParent();
		if ( fieldName == "formulaNameMaximum" )
			return _formulaNameMaximum.IsDerivedFromParent();
		if ( fieldName == "formulaNameRegeneration" )
			return _formulaNameRegeneration.IsDerivedFromParent();
		if ( fieldName == "overtipManaProgressMaterial" )
			return _overtipManaProgressMaterial.IsDerivedFromParent();
		if ( fieldName == "uiManaBarColor" )
			return _uiManaBarColor.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "castleValueMaximum" )
			return _castleValueMaximum.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[IndexField("persistentId")]
[TypeId(0xB1988440)]
[UseTypeName("HEROSKIN")]
public class HeroSkin : DBResource
{
	private UndoRedoDBPtr<HeroSkin> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroSkin> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _legal;
	private UndoRedo<string> _persistentId;
	private UndoRedo<EGender> _gender;
	private TextRef _heroName;
	private UndoRedoDBPtr<Texture> _heroImageA;
	private UndoRedoDBPtr<Texture> _heroImageB;
	private UndoRedoDBPtr<Texture> _heroRenderA;
	private UndoRedoDBPtr<Texture> _heroRenderB;
	private UndoRedo<EHeroRaces> _heroRace;
	private UndoRedoDBPtr<DBSceneObject> _sceneObject;
	private UndoRedo<string> _lobbyAskSound;
	private UndoRedoDBPtr<AskSoundsRef> _askList;
	private UndoRedoDBPtr<AskSoundsRef> _askListSecondState;
	private UndoRedoDBPtr<UnitDeathParameters> _deathParameters;
	private UndoRedo<int> _cost;
	private UndoRedo<bool> _mute;
	private UndoRedo<bool> _botRoll;
	private UndoRedo<string> _antagonistSkinId;

	[Custom("DBServer", "Social")]
	public bool legal { get { return _legal.Get(); } set { _legal.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Global Hero Skin ID" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Custom("DBServer", "DBServer", "Social")]
	public EGender gender { get { return _gender.Get(); } set { _gender.Set( value ); } }

	[Custom("Social")]
	[Description( "Human readable skin name" )]
	public TextRef heroName { get { return _heroName; } set { _heroName.Assign( value ); } }

	[Custom("Social")]
	[Description( "Hero UI avatar picture for first faction" )]
	public DBPtr<Texture> heroImageA { get { return _heroImageA.Get(); } set { _heroImageA.Set( value ); } }

	[Custom("Social")]
	[Description( "Hero UI avatar picture for second faction" )]
	public DBPtr<Texture> heroImageB { get { return _heroImageB.Get(); } set { _heroImageB.Set( value ); } }

	[Custom("Social")]
	[Description( "Hero UI big avatar picture for first faction" )]
	public DBPtr<Texture> heroRenderA { get { return _heroRenderA.Get(); } set { _heroRenderA.Set( value ); } }

	[Custom("Social")]
	[Description( "Hero UI big avatar picture for second faction" )]
	public DBPtr<Texture> heroRenderB { get { return _heroRenderB.Get(); } set { _heroRenderB.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Allowed hero races for skin" )]
	public EHeroRaces heroRace { get { return _heroRace.Get(); } set { _heroRace.Set( value ); } }

	[Description( "Scene object" )]
	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	[Custom("Social")]
	[Description( "Path to sound, played on hero click in castle. Relative path from Resources/Sound/, without file extension." )]
	[NoCode]
	public string lobbyAskSound { get { return _lobbyAskSound.Get(); } set { _lobbyAskSound.Set( value ); } }

	[Category( "Asks" )]
	[Description( "Hero acknowledgment sounds for this skin" )]
	public DBPtr<AskSoundsRef> askList { get { return _askList.Get(); } set { _askList.Set( value ); } }

	[Category( "Asks" )]
	[Description( "Hero acknowledgment sounds for this skin (second hero state)" )]
	public DBPtr<AskSoundsRef> askListSecondState { get { return _askListSecondState.Get(); } set { _askListSecondState.Set( value ); } }

	[Description( "Death parameters" )]
	public DBPtr<UnitDeathParameters> deathParameters { get { return _deathParameters.Get(); } set { _deathParameters.Set( value ); } }

	[Custom("Social")]
	[Description( "Cost of skin in gold" )]
	public int cost { get { return _cost.Get(); } set { _cost.Set( value ); } }

	[Custom("Social")]
	[Description( "Disable all acknowledgment sounds" )]
	public bool mute { get { return _mute.Get(); } set { _mute.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Allowed for bots" )]
	public bool botRoll { get { return _botRoll.Get(); } set { _botRoll.Set( value ); } }

	[Custom("Social")]
	[Description( "ID for antagonist" )]
	public string antagonistSkinId { get { return _antagonistSkinId.Get(); } set { _antagonistSkinId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroSkin>(owner);
		_legal = new UndoRedo<bool>( owner, false );
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_gender = new UndoRedo<EGender>( owner, EGender.Male );
		_heroName = new TextRef( owner, new TextRef() );
		_heroImageA = new UndoRedoDBPtr<Texture>( owner );
		_heroImageB = new UndoRedoDBPtr<Texture>( owner );
		_heroRenderA = new UndoRedoDBPtr<Texture>( owner );
		_heroRenderB = new UndoRedoDBPtr<Texture>( owner );
		_heroRace = new UndoRedo<EHeroRaces>( owner, EHeroRaces.B | EHeroRaces.A );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_lobbyAskSound = new UndoRedo<string>( owner, string.Empty );
		_askList = new UndoRedoDBPtr<AskSoundsRef>( owner );
		_askListSecondState = new UndoRedoDBPtr<AskSoundsRef>( owner );
		_deathParameters = new UndoRedoDBPtr<UnitDeathParameters>( owner );
		_cost = new UndoRedo<int>( owner, 500 );
		_mute = new UndoRedo<bool>( owner, false );
		_botRoll = new UndoRedo<bool>( owner, false );
		_antagonistSkinId = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_legal.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_gender.Changed += FireChangedEvent;
		_heroName.Changed += FireChangedEvent;
		_heroImageA.Changed += FireChangedEvent;
		_heroImageB.Changed += FireChangedEvent;
		_heroRenderA.Changed += FireChangedEvent;
		_heroRenderB.Changed += FireChangedEvent;
		_heroRace.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_lobbyAskSound.Changed += FireChangedEvent;
		_askList.Changed += FireChangedEvent;
		_askListSecondState.Changed += FireChangedEvent;
		_deathParameters.Changed += FireChangedEvent;
		_cost.Changed += FireChangedEvent;
		_mute.Changed += FireChangedEvent;
		_botRoll.Changed += FireChangedEvent;
		_antagonistSkinId.Changed += FireChangedEvent;
	}

	public HeroSkin()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroSkin source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroSkin" );
		legal = source.legal;
		persistentId = source.persistentId;
		gender = source.gender;
		heroName = source.heroName;
		heroImageA = source.heroImageA;
		heroImageB = source.heroImageB;
		heroRenderA = source.heroRenderA;
		heroRenderB = source.heroRenderB;
		heroRace = source.heroRace;
		sceneObject = source.sceneObject;
		lobbyAskSound = source.lobbyAskSound;
		askList = source.askList;
		askListSecondState = source.askListSecondState;
		deathParameters = source.deathParameters;
		cost = source.cost;
		mute = source.mute;
		botRoll = source.botRoll;
		antagonistSkinId = source.antagonistSkinId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroSkin source = _source as HeroSkin;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroSkin" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroSkin newParent = rawParent == null ? null : rawParent.Get<HeroSkin>();
		if ( newParent == null && _newParent is HeroSkin )
			newParent = _newParent as HeroSkin;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_legal.SetParent( newParent == null ? null : newParent._legal );
		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_gender.SetParent( newParent == null ? null : newParent._gender );
		_heroName.SetParent( newParent == null ? null : newParent._heroName );
		_heroImageA.SetParent( newParent == null ? null : newParent._heroImageA );
		_heroImageB.SetParent( newParent == null ? null : newParent._heroImageB );
		_heroRenderA.SetParent( newParent == null ? null : newParent._heroRenderA );
		_heroRenderB.SetParent( newParent == null ? null : newParent._heroRenderB );
		_heroRace.SetParent( newParent == null ? null : newParent._heroRace );
		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		_lobbyAskSound.SetParent( newParent == null ? null : newParent._lobbyAskSound );
		_askList.SetParent( newParent == null ? null : newParent._askList );
		_askListSecondState.SetParent( newParent == null ? null : newParent._askListSecondState );
		_deathParameters.SetParent( newParent == null ? null : newParent._deathParameters );
		_cost.SetParent( newParent == null ? null : newParent._cost );
		_mute.SetParent( newParent == null ? null : newParent._mute );
		_botRoll.SetParent( newParent == null ? null : newParent._botRoll );
		_antagonistSkinId.SetParent( newParent == null ? null : newParent._antagonistSkinId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_legal.Reset();
		_persistentId.Reset();
		_gender.Reset();
		_heroName.Reset();
		_heroImageA.Reset();
		_heroImageB.Reset();
		_heroRenderA.Reset();
		_heroRenderB.Reset();
		_heroRace.Reset();
		_sceneObject.Reset();
		_lobbyAskSound.Reset();
		_askList.Reset();
		_askListSecondState.Reset();
		_deathParameters.Reset();
		_cost.Reset();
		_mute.Reset();
		_botRoll.Reset();
		_antagonistSkinId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_legal.IsDerivedFromParent()
			&& _persistentId.IsDerivedFromParent()
			&& _gender.IsDerivedFromParent()
			&& _heroName.IsDerivedFromParent()
			&& _heroImageA.IsDerivedFromParent()
			&& _heroImageB.IsDerivedFromParent()
			&& _heroRenderA.IsDerivedFromParent()
			&& _heroRenderB.IsDerivedFromParent()
			&& _heroRace.IsDerivedFromParent()
			&& _sceneObject.IsDerivedFromParent()
			&& _lobbyAskSound.IsDerivedFromParent()
			&& _askList.IsDerivedFromParent()
			&& _askListSecondState.IsDerivedFromParent()
			&& _deathParameters.IsDerivedFromParent()
			&& _cost.IsDerivedFromParent()
			&& _mute.IsDerivedFromParent()
			&& _botRoll.IsDerivedFromParent()
			&& _antagonistSkinId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "legal" )
			_legal.Reset();
		else if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "gender" )
			_gender.Reset();
		else if ( fieldName == "heroName" )
			_heroName.Reset();
		else if ( fieldName == "heroImageA" )
			_heroImageA.Reset();
		else if ( fieldName == "heroImageB" )
			_heroImageB.Reset();
		else if ( fieldName == "heroRenderA" )
			_heroRenderA.Reset();
		else if ( fieldName == "heroRenderB" )
			_heroRenderB.Reset();
		else if ( fieldName == "heroRace" )
			_heroRace.Reset();
		else if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else if ( fieldName == "lobbyAskSound" )
			_lobbyAskSound.Reset();
		else if ( fieldName == "askList" )
			_askList.Reset();
		else if ( fieldName == "askListSecondState" )
			_askListSecondState.Reset();
		else if ( fieldName == "deathParameters" )
			_deathParameters.Reset();
		else if ( fieldName == "cost" )
			_cost.Reset();
		else if ( fieldName == "mute" )
			_mute.Reset();
		else if ( fieldName == "botRoll" )
			_botRoll.Reset();
		else if ( fieldName == "antagonistSkinId" )
			_antagonistSkinId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "legal" )
			return _legal.IsDerivedFromParent();
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "gender" )
			return _gender.IsDerivedFromParent();
		if ( fieldName == "heroName" )
			return _heroName.IsDerivedFromParent();
		if ( fieldName == "heroImageA" )
			return _heroImageA.IsDerivedFromParent();
		if ( fieldName == "heroImageB" )
			return _heroImageB.IsDerivedFromParent();
		if ( fieldName == "heroRenderA" )
			return _heroRenderA.IsDerivedFromParent();
		if ( fieldName == "heroRenderB" )
			return _heroRenderB.IsDerivedFromParent();
		if ( fieldName == "heroRace" )
			return _heroRace.IsDerivedFromParent();
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
		if ( fieldName == "lobbyAskSound" )
			return _lobbyAskSound.IsDerivedFromParent();
		if ( fieldName == "askList" )
			return _askList.IsDerivedFromParent();
		if ( fieldName == "askListSecondState" )
			return _askListSecondState.IsDerivedFromParent();
		if ( fieldName == "deathParameters" )
			return _deathParameters.IsDerivedFromParent();
		if ( fieldName == "cost" )
			return _cost.IsDerivedFromParent();
		if ( fieldName == "mute" )
			return _mute.IsDerivedFromParent();
		if ( fieldName == "botRoll" )
			return _botRoll.IsDerivedFromParent();
		if ( fieldName == "antagonistSkinId" )
			return _antagonistSkinId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xE7A8B300)]
[UseTypeName("IACT")]
public class Interaction : DBResource
{
	private UndoRedoDBPtr<Interaction> ___parent;
	[HideInOutliner]
	public new DBPtr<Interaction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Ability> _externalAbility;
	private UndoRedo<EFactionFlags> _allowedFactions;

	[Description( "Ability that will be used by hero on interaction" )]
	public DBPtr<Ability> externalAbility { get { return _externalAbility.Get(); } set { _externalAbility.Set( value ); } }

	[Description( "Фракции которые могут юзать этот юнит" )]
	public EFactionFlags allowedFactions { get { return _allowedFactions.Get(); } set { _allowedFactions.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Interaction>(owner);
		_externalAbility = new UndoRedoDBPtr<Ability>( owner );
		_allowedFactions = new UndoRedo<EFactionFlags>( owner, EFactionFlags.Self );
		___parent.Changed += FireChangedEvent;
		_externalAbility.Changed += FireChangedEvent;
		_allowedFactions.Changed += FireChangedEvent;
	}

	public Interaction()
	{
		Initialize( this );
	}
	private void AssignSelf( Interaction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Interaction" );
		externalAbility = source.externalAbility;
		allowedFactions = source.allowedFactions;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Interaction source = _source as Interaction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Interaction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Interaction newParent = rawParent == null ? null : rawParent.Get<Interaction>();
		if ( newParent == null && _newParent is Interaction )
			newParent = _newParent as Interaction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_externalAbility.SetParent( newParent == null ? null : newParent._externalAbility );
		_allowedFactions.SetParent( newParent == null ? null : newParent._allowedFactions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_externalAbility.Reset();
		_allowedFactions.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_externalAbility.IsDerivedFromParent()
			&& _allowedFactions.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "externalAbility" )
			_externalAbility.Reset();
		else if ( fieldName == "allowedFactions" )
			_allowedFactions.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "externalAbility" )
			return _externalAbility.IsDerivedFromParent();
		if ( fieldName == "allowedFactions" )
			return _allowedFactions.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("KLEM")]
public class KillExperienceModifier : DBResource
{
	private UndoRedoDBPtr<KillExperienceModifier> ___parent;
	[HideInOutliner]
	public new DBPtr<KillExperienceModifier> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _otherDifferenceLessCoeff;
	private UndoRedo<float> _otherDifferenceGreaterCoeff;
	private UndoRedoAssignableList<LevelDiffModifier> _levelModifiers;

	public float otherDifferenceLessCoeff { get { return _otherDifferenceLessCoeff.Get(); } set { _otherDifferenceLessCoeff.Set( value ); } }

	public float otherDifferenceGreaterCoeff { get { return _otherDifferenceGreaterCoeff.Get(); } set { _otherDifferenceGreaterCoeff.Set( value ); } }

	public libdb.IChangeableList<LevelDiffModifier> levelModifiers { get { return _levelModifiers; } set { _levelModifiers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<KillExperienceModifier>(owner);
		_otherDifferenceLessCoeff = new UndoRedo<float>( owner, 10.0f );
		_otherDifferenceGreaterCoeff = new UndoRedo<float>( owner, 150.0f );
		_levelModifiers = new UndoRedoAssignableList<LevelDiffModifier>( owner );
		___parent.Changed += FireChangedEvent;
		_otherDifferenceLessCoeff.Changed += FireChangedEvent;
		_otherDifferenceGreaterCoeff.Changed += FireChangedEvent;
		_levelModifiers.Changed += FireChangedEvent;
	}

	public KillExperienceModifier()
	{
		Initialize( this );
	}
	private void AssignSelf( KillExperienceModifier source )
	{
		DataBase.UndoRedoManager.Start( "Assign for KillExperienceModifier" );
		otherDifferenceLessCoeff = source.otherDifferenceLessCoeff;
		otherDifferenceGreaterCoeff = source.otherDifferenceGreaterCoeff;
		levelModifiers = source.levelModifiers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		KillExperienceModifier source = _source as KillExperienceModifier;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for KillExperienceModifier" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		KillExperienceModifier newParent = rawParent == null ? null : rawParent.Get<KillExperienceModifier>();
		if ( newParent == null && _newParent is KillExperienceModifier )
			newParent = _newParent as KillExperienceModifier;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_otherDifferenceLessCoeff.SetParent( newParent == null ? null : newParent._otherDifferenceLessCoeff );
		_otherDifferenceGreaterCoeff.SetParent( newParent == null ? null : newParent._otherDifferenceGreaterCoeff );
		_levelModifiers.SetParent( newParent == null ? null : newParent._levelModifiers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_otherDifferenceLessCoeff.Reset();
		_otherDifferenceGreaterCoeff.Reset();
		_levelModifiers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_otherDifferenceLessCoeff.IsDerivedFromParent()
			&& _otherDifferenceGreaterCoeff.IsDerivedFromParent()
			&& _levelModifiers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "otherDifferenceLessCoeff" )
			_otherDifferenceLessCoeff.Reset();
		else if ( fieldName == "otherDifferenceGreaterCoeff" )
			_otherDifferenceGreaterCoeff.Reset();
		else if ( fieldName == "levelModifiers" )
			_levelModifiers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "otherDifferenceLessCoeff" )
			return _otherDifferenceLessCoeff.IsDerivedFromParent();
		if ( fieldName == "otherDifferenceGreaterCoeff" )
			return _otherDifferenceGreaterCoeff.IsDerivedFromParent();
		if ( fieldName == "levelModifiers" )
			return _levelModifiers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[TypeId(0x2C5BE302)]
[UseTypeName("MBLD")]
public class MainBuilding : Building
{
	private UndoRedoDBPtr<MainBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<MainBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _aoeUnitsCount;
	private UndoRedo<ESpellTarget> _aoeUnitsTypes;
	private UndoRedo<EFactionFlags> _aoeUnitsFactions;
	private UndoRedo<float> _aoeRadius;
	private UndoRedo<float> _minAOEDelay;
	private UndoRedo<float> _maxAOEDelay;
	private UndoRedoDBPtr<Ability> _aoeAttack;

	public int aoeUnitsCount { get { return _aoeUnitsCount.Get(); } set { _aoeUnitsCount.Set( value ); } }

	public ESpellTarget aoeUnitsTypes { get { return _aoeUnitsTypes.Get(); } set { _aoeUnitsTypes.Set( value ); } }

	public EFactionFlags aoeUnitsFactions { get { return _aoeUnitsFactions.Get(); } set { _aoeUnitsFactions.Set( value ); } }

	public float aoeRadius { get { return _aoeRadius.Get(); } set { _aoeRadius.Set( value ); } }

	public float minAOEDelay { get { return _minAOEDelay.Get(); } set { _minAOEDelay.Set( value ); } }

	public float maxAOEDelay { get { return _maxAOEDelay.Get(); } set { _maxAOEDelay.Set( value ); } }

	public DBPtr<Ability> aoeAttack { get { return _aoeAttack.Get(); } set { _aoeAttack.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MainBuilding>(owner);
		_aoeUnitsCount = new UndoRedo<int>( owner, 10 );
		_aoeUnitsTypes = new UndoRedo<ESpellTarget>( owner, ESpellTarget.All );
		_aoeUnitsFactions = new UndoRedo<EFactionFlags>( owner, EFactionFlags.Opposite | EFactionFlags.Neutral );
		_aoeRadius = new UndoRedo<float>( owner, 20.0f );
		_minAOEDelay = new UndoRedo<float>( owner, 10.0f );
		_maxAOEDelay = new UndoRedo<float>( owner, 20.0f );
		_aoeAttack = new UndoRedoDBPtr<Ability>( owner );
		___parent.Changed += FireChangedEvent;
		_aoeUnitsCount.Changed += FireChangedEvent;
		_aoeUnitsTypes.Changed += FireChangedEvent;
		_aoeUnitsFactions.Changed += FireChangedEvent;
		_aoeRadius.Changed += FireChangedEvent;
		_minAOEDelay.Changed += FireChangedEvent;
		_maxAOEDelay.Changed += FireChangedEvent;
		_aoeAttack.Changed += FireChangedEvent;
	}

	public MainBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( MainBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MainBuilding" );
		aoeUnitsCount = source.aoeUnitsCount;
		aoeUnitsTypes = source.aoeUnitsTypes;
		aoeUnitsFactions = source.aoeUnitsFactions;
		aoeRadius = source.aoeRadius;
		minAOEDelay = source.minAOEDelay;
		maxAOEDelay = source.maxAOEDelay;
		aoeAttack = source.aoeAttack;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MainBuilding source = _source as MainBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MainBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MainBuilding newParent = rawParent == null ? null : rawParent.Get<MainBuilding>();
		if ( newParent == null && _newParent is MainBuilding )
			newParent = _newParent as MainBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_aoeUnitsCount.SetParent( newParent == null ? null : newParent._aoeUnitsCount );
		_aoeUnitsTypes.SetParent( newParent == null ? null : newParent._aoeUnitsTypes );
		_aoeUnitsFactions.SetParent( newParent == null ? null : newParent._aoeUnitsFactions );
		_aoeRadius.SetParent( newParent == null ? null : newParent._aoeRadius );
		_minAOEDelay.SetParent( newParent == null ? null : newParent._minAOEDelay );
		_maxAOEDelay.SetParent( newParent == null ? null : newParent._maxAOEDelay );
		_aoeAttack.SetParent( newParent == null ? null : newParent._aoeAttack );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_aoeUnitsCount.Reset();
		_aoeUnitsTypes.Reset();
		_aoeUnitsFactions.Reset();
		_aoeRadius.Reset();
		_minAOEDelay.Reset();
		_maxAOEDelay.Reset();
		_aoeAttack.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_aoeUnitsCount.IsDerivedFromParent()
			&& _aoeUnitsTypes.IsDerivedFromParent()
			&& _aoeUnitsFactions.IsDerivedFromParent()
			&& _aoeRadius.IsDerivedFromParent()
			&& _minAOEDelay.IsDerivedFromParent()
			&& _maxAOEDelay.IsDerivedFromParent()
			&& _aoeAttack.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "aoeUnitsCount" )
			_aoeUnitsCount.Reset();
		else if ( fieldName == "aoeUnitsTypes" )
			_aoeUnitsTypes.Reset();
		else if ( fieldName == "aoeUnitsFactions" )
			_aoeUnitsFactions.Reset();
		else if ( fieldName == "aoeRadius" )
			_aoeRadius.Reset();
		else if ( fieldName == "minAOEDelay" )
			_minAOEDelay.Reset();
		else if ( fieldName == "maxAOEDelay" )
			_maxAOEDelay.Reset();
		else if ( fieldName == "aoeAttack" )
			_aoeAttack.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "aoeUnitsCount" )
			return _aoeUnitsCount.IsDerivedFromParent();
		if ( fieldName == "aoeUnitsTypes" )
			return _aoeUnitsTypes.IsDerivedFromParent();
		if ( fieldName == "aoeUnitsFactions" )
			return _aoeUnitsFactions.IsDerivedFromParent();
		if ( fieldName == "aoeRadius" )
			return _aoeRadius.IsDerivedFromParent();
		if ( fieldName == "minAOEDelay" )
			return _minAOEDelay.IsDerivedFromParent();
		if ( fieldName == "maxAOEDelay" )
			return _maxAOEDelay.IsDerivedFromParent();
		if ( fieldName == "aoeAttack" )
			return _aoeAttack.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9D62D2C1)]
[UseTypeName("MINI")]
public class MinigamePlace : Building
{
	private UndoRedoDBPtr<MinigamePlace> ___parent;
	[HideInOutliner]
	public new DBPtr<MinigamePlace> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MinigamePlaceParams> _placeParams;
	private UndoRedo<string> _minigameId;
	private Vec2 _artifactsSpawnPosition;
	private UndoRedoDBPtr<BasicEffectAttached> _onIdleEffect;

	public DBPtr<MinigamePlaceParams> placeParams { get { return _placeParams.Get(); } set { _placeParams.Set( value ); } }

	public string minigameId { get { return _minigameId.Get(); } set { _minigameId.Set( value ); } }

	public Vec2 artifactsSpawnPosition { get { return _artifactsSpawnPosition; } set { _artifactsSpawnPosition.Assign( value ); } }

	public DBPtr<BasicEffectAttached> onIdleEffect { get { return _onIdleEffect.Get(); } set { _onIdleEffect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinigamePlace>(owner);
		_placeParams = new UndoRedoDBPtr<MinigamePlaceParams>( owner );
		_minigameId = new UndoRedo<string>( owner, string.Empty );
		_artifactsSpawnPosition = new Vec2( owner );
		_onIdleEffect = new UndoRedoDBPtr<BasicEffectAttached>( owner );
		___parent.Changed += FireChangedEvent;
		_placeParams.Changed += FireChangedEvent;
		_minigameId.Changed += FireChangedEvent;
		_artifactsSpawnPosition.Changed += FireChangedEvent;
		_onIdleEffect.Changed += FireChangedEvent;
	}

	public MinigamePlace()
	{
		Initialize( this );
	}
	private void AssignSelf( MinigamePlace source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinigamePlace" );
		placeParams = source.placeParams;
		minigameId = source.minigameId;
		artifactsSpawnPosition = source.artifactsSpawnPosition;
		onIdleEffect = source.onIdleEffect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinigamePlace source = _source as MinigamePlace;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinigamePlace" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinigamePlace newParent = rawParent == null ? null : rawParent.Get<MinigamePlace>();
		if ( newParent == null && _newParent is MinigamePlace )
			newParent = _newParent as MinigamePlace;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_placeParams.SetParent( newParent == null ? null : newParent._placeParams );
		_minigameId.SetParent( newParent == null ? null : newParent._minigameId );
		_artifactsSpawnPosition.SetParent( newParent == null ? null : newParent._artifactsSpawnPosition );
		_onIdleEffect.SetParent( newParent == null ? null : newParent._onIdleEffect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_placeParams.Reset();
		_minigameId.Reset();
		_artifactsSpawnPosition.Reset();
		_onIdleEffect.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_placeParams.IsDerivedFromParent()
			&& _minigameId.IsDerivedFromParent()
			&& _artifactsSpawnPosition.IsDerivedFromParent()
			&& _onIdleEffect.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "placeParams" )
			_placeParams.Reset();
		else if ( fieldName == "minigameId" )
			_minigameId.Reset();
		else if ( fieldName == "artifactsSpawnPosition" )
			_artifactsSpawnPosition.Reset();
		else if ( fieldName == "onIdleEffect" )
			_onIdleEffect.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "placeParams" )
			return _placeParams.IsDerivedFromParent();
		if ( fieldName == "minigameId" )
			return _minigameId.IsDerivedFromParent();
		if ( fieldName == "artifactsSpawnPosition" )
			return _artifactsSpawnPosition.IsDerivedFromParent();
		if ( fieldName == "onIdleEffect" )
			return _onIdleEffect.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[TypeId(0x8D81AB80)]
[UseTypeName("TREF")]
public class MSOTransactions : DBResource
{
	private UndoRedoDBPtr<MSOTransactions> ___parent;
	[HideInOutliner]
	public new DBPtr<MSOTransactions> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TransactionEffects _effectN;
	private TransactionEffects _effectA;
	private TransactionEffects _effectB;

	public TransactionEffects effectN { get { return _effectN; } set { _effectN.Assign( value ); } }

	public TransactionEffects effectA { get { return _effectA; } set { _effectA.Assign( value ); } }

	public TransactionEffects effectB { get { return _effectB; } set { _effectB.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MSOTransactions>(owner);
		_effectN = new TransactionEffects( owner );
		_effectA = new TransactionEffects( owner );
		_effectB = new TransactionEffects( owner );
		___parent.Changed += FireChangedEvent;
		_effectN.Changed += FireChangedEvent;
		_effectA.Changed += FireChangedEvent;
		_effectB.Changed += FireChangedEvent;
	}

	public MSOTransactions()
	{
		Initialize( this );
	}
	private void AssignSelf( MSOTransactions source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MSOTransactions" );
		effectN = source.effectN;
		effectA = source.effectA;
		effectB = source.effectB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MSOTransactions source = _source as MSOTransactions;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MSOTransactions" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MSOTransactions newParent = rawParent == null ? null : rawParent.Get<MSOTransactions>();
		if ( newParent == null && _newParent is MSOTransactions )
			newParent = _newParent as MSOTransactions;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effectN.SetParent( newParent == null ? null : newParent._effectN );
		_effectA.SetParent( newParent == null ? null : newParent._effectA );
		_effectB.SetParent( newParent == null ? null : newParent._effectB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effectN.Reset();
		_effectA.Reset();
		_effectB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effectN.IsDerivedFromParent()
			&& _effectA.IsDerivedFromParent()
			&& _effectB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effectN" )
			_effectN.Reset();
		else if ( fieldName == "effectA" )
			_effectA.Reset();
		else if ( fieldName == "effectB" )
			_effectB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effectN" )
			return _effectN.IsDerivedFromParent();
		if ( fieldName == "effectA" )
			return _effectA.IsDerivedFromParent();
		if ( fieldName == "effectB" )
			return _effectB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[TypeId(0x0F64B3C0)]
[UseTypeName("MSO")]
public class MultiStateObject : GameObject
{
	private UndoRedoDBPtr<MultiStateObject> ___parent;
	[HideInOutliner]
	public new DBPtr<MultiStateObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _sceneObjects;
	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _nightSceneObjects;
	private UndoRedoDBPtr<MSOTransactions> _effects;
	private UndoRedoDBPtr<MSOTransactions> _nightEffects;
	private UndoRedo<bool> _opaque;
	private UndoRedo<float> _fadeInOffset;
	private UndoRedo<float> _dropTime;
	private UndoRedo<bool> _isVisibleUnderWarfog;
	private UndoRedo<bool> _distinct;

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> sceneObjects { get { return _sceneObjects; } set { _sceneObjects.Assign( value ); } }

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> nightSceneObjects { get { return _nightSceneObjects; } set { _nightSceneObjects.Assign( value ); } }

	[Description( "MSO transactions" )]
	public DBPtr<MSOTransactions> effects { get { return _effects.Get(); } set { _effects.Set( value ); } }

	[Description( "MSO night transactions" )]
	public DBPtr<MSOTransactions> nightEffects { get { return _nightEffects.Get(); } set { _nightEffects.Set( value ); } }

	[Description( "Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом." )]
	public bool opaque { get { return _opaque.Get(); } set { _opaque.Set( value ); } }

	[Description( "Fade offset in time" )]
	public float fadeInOffset { get { return _fadeInOffset.Get(); } set { _fadeInOffset.Set( value ); } }

	[Description( "Время падения дерева. Должно совпадать с длиной трека drop." )]
	public float dropTime { get { return _dropTime.Get(); } set { _dropTime.Set( value ); } }

	[Description( "Виден ли этот Object под варфогом. Если в true, то он виден." )]
	public bool isVisibleUnderWarfog { get { return _isVisibleUnderWarfog.Get(); } set { _isVisibleUnderWarfog.Set( value ); } }

	[Description( "Явно разделяет дневное и ночное состояния. Если false, то при отсутствии дневных или ночных SceneObject'ов вместо них будут использоваться, соответственно, ночные или дневные." )]
	public bool distinct { get { return _distinct.Get(); } set { _distinct.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MultiStateObject>(owner);
		_sceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ENatureType ) );
		_nightSceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ENatureType ) );
		_effects = new UndoRedoDBPtr<MSOTransactions>( owner );
		_nightEffects = new UndoRedoDBPtr<MSOTransactions>( owner );
		_opaque = new UndoRedo<bool>( owner, false );
		_fadeInOffset = new UndoRedo<float>( owner, 0.0f );
		_dropTime = new UndoRedo<float>( owner, 1.0f );
		_isVisibleUnderWarfog = new UndoRedo<bool>( owner, false );
		_distinct = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_sceneObjects.Changed += FireChangedEvent;
		_nightSceneObjects.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_nightEffects.Changed += FireChangedEvent;
		_opaque.Changed += FireChangedEvent;
		_fadeInOffset.Changed += FireChangedEvent;
		_dropTime.Changed += FireChangedEvent;
		_isVisibleUnderWarfog.Changed += FireChangedEvent;
		_distinct.Changed += FireChangedEvent;
	}

	public MultiStateObject()
	{
		Initialize( this );
	}
	private void AssignSelf( MultiStateObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MultiStateObject" );
		sceneObjects = source.sceneObjects;
		nightSceneObjects = source.nightSceneObjects;
		effects = source.effects;
		nightEffects = source.nightEffects;
		opaque = source.opaque;
		fadeInOffset = source.fadeInOffset;
		dropTime = source.dropTime;
		isVisibleUnderWarfog = source.isVisibleUnderWarfog;
		distinct = source.distinct;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MultiStateObject source = _source as MultiStateObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MultiStateObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MultiStateObject newParent = rawParent == null ? null : rawParent.Get<MultiStateObject>();
		if ( newParent == null && _newParent is MultiStateObject )
			newParent = _newParent as MultiStateObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sceneObjects.SetParent( newParent == null ? null : newParent._sceneObjects );
		_nightSceneObjects.SetParent( newParent == null ? null : newParent._nightSceneObjects );
		_effects.SetParent( newParent == null ? null : newParent._effects );
		_nightEffects.SetParent( newParent == null ? null : newParent._nightEffects );
		_opaque.SetParent( newParent == null ? null : newParent._opaque );
		_fadeInOffset.SetParent( newParent == null ? null : newParent._fadeInOffset );
		_dropTime.SetParent( newParent == null ? null : newParent._dropTime );
		_isVisibleUnderWarfog.SetParent( newParent == null ? null : newParent._isVisibleUnderWarfog );
		_distinct.SetParent( newParent == null ? null : newParent._distinct );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sceneObjects.Reset();
		_nightSceneObjects.Reset();
		_effects.Reset();
		_nightEffects.Reset();
		_opaque.Reset();
		_fadeInOffset.Reset();
		_dropTime.Reset();
		_isVisibleUnderWarfog.Reset();
		_distinct.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sceneObjects.IsDerivedFromParent()
			&& _nightSceneObjects.IsDerivedFromParent()
			&& _effects.IsDerivedFromParent()
			&& _nightEffects.IsDerivedFromParent()
			&& _opaque.IsDerivedFromParent()
			&& _fadeInOffset.IsDerivedFromParent()
			&& _dropTime.IsDerivedFromParent()
			&& _isVisibleUnderWarfog.IsDerivedFromParent()
			&& _distinct.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sceneObjects" )
			_sceneObjects.Reset();
		else if ( fieldName == "nightSceneObjects" )
			_nightSceneObjects.Reset();
		else if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "nightEffects" )
			_nightEffects.Reset();
		else if ( fieldName == "opaque" )
			_opaque.Reset();
		else if ( fieldName == "fadeInOffset" )
			_fadeInOffset.Reset();
		else if ( fieldName == "dropTime" )
			_dropTime.Reset();
		else if ( fieldName == "isVisibleUnderWarfog" )
			_isVisibleUnderWarfog.Reset();
		else if ( fieldName == "distinct" )
			_distinct.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sceneObjects" )
			return _sceneObjects.IsDerivedFromParent();
		if ( fieldName == "nightSceneObjects" )
			return _nightSceneObjects.IsDerivedFromParent();
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "nightEffects" )
			return _nightEffects.IsDerivedFromParent();
		if ( fieldName == "opaque" )
			return _opaque.IsDerivedFromParent();
		if ( fieldName == "fadeInOffset" )
			return _fadeInOffset.IsDerivedFromParent();
		if ( fieldName == "dropTime" )
			return _dropTime.IsDerivedFromParent();
		if ( fieldName == "isVisibleUnderWarfog" )
			return _isVisibleUnderWarfog.IsDerivedFromParent();
		if ( fieldName == "distinct" )
			return _distinct.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2C5BE301)]
[UseTypeName("QRTR")]
public class Quarter : Building
{
	private UndoRedoDBPtr<Quarter> ___parent;
	[HideInOutliner]
	public new DBPtr<Quarter> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Quarter>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public Quarter()
	{
		Initialize( this );
	}
	private void AssignSelf( Quarter source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Quarter" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Quarter source = _source as Quarter;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Quarter" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Quarter newParent = rawParent == null ? null : rawParent.Get<Quarter>();
		if ( newParent == null && _newParent is Quarter )
			newParent = _newParent as Quarter;
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

[TypeId(0x9A9BA381)]
[UseTypeName("FLAG")]
public class ScriptedFlagpole : Flagpole
{
	private UndoRedoDBPtr<ScriptedFlagpole> ___parent;
	[HideInOutliner]
	public new DBPtr<ScriptedFlagpole> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScriptedFlagpole>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public ScriptedFlagpole()
	{
		Initialize( this );
	}
	private void AssignSelf( ScriptedFlagpole source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScriptedFlagpole" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScriptedFlagpole source = _source as ScriptedFlagpole;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptedFlagpole" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScriptedFlagpole newParent = rawParent == null ? null : rawParent.Get<ScriptedFlagpole>();
		if ( newParent == null && _newParent is ScriptedFlagpole )
			newParent = _newParent as ScriptedFlagpole;
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

[TypeId(0x0F61AC41)]
[UseTypeName("SHOP")]
public class Shop : Building
{
	private UndoRedoDBPtr<Shop> ___parent;
	[HideInOutliner]
	public new DBPtr<Shop> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<ConsumablesShop> _shop;

	public DBPtr<ConsumablesShop> shop { get { return _shop.Get(); } set { _shop.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Shop>(owner);
		_shop = new UndoRedoDBPtr<ConsumablesShop>( owner );
		___parent.Changed += FireChangedEvent;
		_shop.Changed += FireChangedEvent;
	}

	public Shop()
	{
		Initialize( this );
	}
	private void AssignSelf( Shop source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Shop" );
		shop = source.shop;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Shop source = _source as Shop;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Shop" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Shop newParent = rawParent == null ? null : rawParent.Get<Shop>();
		if ( newParent == null && _newParent is Shop )
			newParent = _newParent as Shop;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_shop.SetParent( newParent == null ? null : newParent._shop );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_shop.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_shop.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "shop" )
			_shop.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "shop" )
			return _shop.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x8E547B04)]
[UseTypeName("SMPL")]
public class SimpleObject : SingleStateObject
{
	private UndoRedoDBPtr<SimpleObject> ___parent;
	[HideInOutliner]
	public new DBPtr<SimpleObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _health;
	private UndoRedo<bool> _opaque;
	private UndoRedo<bool> _isVisibleUnderWarfog;

	[Category( "Destructible" )]
	public int health { get { return _health.Get(); } set { _health.Set( value ); } }

	[Description( "Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом." )]
	public bool opaque { get { return _opaque.Get(); } set { _opaque.Set( value ); } }

	[Description( "Виден ли этот Object под варфогом. Если в true, то он виден" )]
	public bool isVisibleUnderWarfog { get { return _isVisibleUnderWarfog.Get(); } set { _isVisibleUnderWarfog.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SimpleObject>(owner);
		_health = new UndoRedo<int>( owner, -1 );
		_opaque = new UndoRedo<bool>( owner, false );
		_isVisibleUnderWarfog = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_health.Changed += FireChangedEvent;
		_opaque.Changed += FireChangedEvent;
		_isVisibleUnderWarfog.Changed += FireChangedEvent;
	}

	public SimpleObject()
	{
		Initialize( this );
	}
	private void AssignSelf( SimpleObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SimpleObject" );
		health = source.health;
		opaque = source.opaque;
		isVisibleUnderWarfog = source.isVisibleUnderWarfog;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SimpleObject source = _source as SimpleObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SimpleObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SimpleObject newParent = rawParent == null ? null : rawParent.Get<SimpleObject>();
		if ( newParent == null && _newParent is SimpleObject )
			newParent = _newParent as SimpleObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_health.SetParent( newParent == null ? null : newParent._health );
		_opaque.SetParent( newParent == null ? null : newParent._opaque );
		_isVisibleUnderWarfog.SetParent( newParent == null ? null : newParent._isVisibleUnderWarfog );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_health.Reset();
		_opaque.Reset();
		_isVisibleUnderWarfog.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_health.IsDerivedFromParent()
			&& _opaque.IsDerivedFromParent()
			&& _isVisibleUnderWarfog.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "health" )
			_health.Reset();
		else if ( fieldName == "opaque" )
			_opaque.Reset();
		else if ( fieldName == "isVisibleUnderWarfog" )
			_isVisibleUnderWarfog.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "health" )
			return _health.IsDerivedFromParent();
		if ( fieldName == "opaque" )
			return _opaque.IsDerivedFromParent();
		if ( fieldName == "isVisibleUnderWarfog" )
			return _isVisibleUnderWarfog.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("id")]
[TypeId(0x2C5B3C40)]
[UseTypeName("HROB")]
public class Hero : BaseHero
{
	private UndoRedoDBPtr<Hero> ___parent;
	[HideInOutliner]
	public new DBPtr<Hero> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _id;
	private UndoRedo<bool> _legal;
	private UndoRedo<EBotRollMode> _botRollMode;
	private UndoRedoList<float> _classEfficiency;
	private UndoRedo<bool> _canMount;
	private UndoRedo<float> _askBlessCooldown;
	private UndoRedoAssignableList<DBPtr<TalentsSet>> _defaultTalentsSets;
	private UndoRedoDBPtr<TalentsSet> _mightyTalentSet;
	private LobbyHeroData _lobbyData;

	[Custom("DBServer", "Social")]
	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	[Custom("DBServer", "Social")]
	public bool legal { get { return _legal.Get(); } set { _legal.Set( value ); } }

	[Custom("DBServer")]
	public EBotRollMode botRollMode { get { return _botRollMode.Get(); } set { _botRollMode.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Таблица эффективности героя в по каждому классу, для матчмекинга" )]
	[EnumArray(typeof(MMakingHeroClassEnum))]
	public libdb.IChangeableList<float> classEfficiency { get { return _classEfficiency; } set { _classEfficiency.Assign( value ); } }

	public bool canMount { get { return _canMount.Get(); } set { _canMount.Set( value ); } }

	public float askBlessCooldown { get { return _askBlessCooldown.Get(); } set { _askBlessCooldown.Set( value ); } }

	[Custom("Social")]
	public libdb.IChangeableList<DBPtr<TalentsSet>> defaultTalentsSets { get { return _defaultTalentsSets; } set { _defaultTalentsSets.Assign( value ); } }

	[Custom("Social")]
	[NoCode]
	public DBPtr<TalentsSet> mightyTalentSet { get { return _mightyTalentSet.Get(); } set { _mightyTalentSet.Set( value ); } }

	[Custom("Social")]
	[Description( "For social client" )]
	[NoCode]
	public LobbyHeroData lobbyData { get { return _lobbyData; } set { _lobbyData.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Hero>(owner);
		_id = new UndoRedo<string>( owner, string.Empty );
		_legal = new UndoRedo<bool>( owner, true );
		_botRollMode = new UndoRedo<EBotRollMode>( owner, EBotRollMode.Enabled );
		_classEfficiency = new UndoRedoList<float>( owner, typeof( MMakingHeroClassEnum ) );
		_canMount = new UndoRedo<bool>( owner, false );
		_askBlessCooldown = new UndoRedo<float>( owner, 0.0f );
		_defaultTalentsSets = new UndoRedoAssignableList<DBPtr<TalentsSet>>( owner );
		_mightyTalentSet = new UndoRedoDBPtr<TalentsSet>( owner );
		_lobbyData = new LobbyHeroData( owner );
		___parent.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_legal.Changed += FireChangedEvent;
		_botRollMode.Changed += FireChangedEvent;
		_classEfficiency.Changed += FireChangedEvent;
		_canMount.Changed += FireChangedEvent;
		_askBlessCooldown.Changed += FireChangedEvent;
		_defaultTalentsSets.Changed += FireChangedEvent;
		_mightyTalentSet.Changed += FireChangedEvent;
		_lobbyData.Changed += FireChangedEvent;
	}

	public Hero()
	{
		Initialize( this );
	}
	private void AssignSelf( Hero source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Hero" );
		id = source.id;
		legal = source.legal;
		botRollMode = source.botRollMode;
		classEfficiency = source.classEfficiency;
		canMount = source.canMount;
		askBlessCooldown = source.askBlessCooldown;
		defaultTalentsSets = source.defaultTalentsSets;
		mightyTalentSet = source.mightyTalentSet;
		lobbyData = source.lobbyData;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Hero source = _source as Hero;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Hero" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Hero newParent = rawParent == null ? null : rawParent.Get<Hero>();
		if ( newParent == null && _newParent is Hero )
			newParent = _newParent as Hero;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_id.SetParent( newParent == null ? null : newParent._id );
		_legal.SetParent( newParent == null ? null : newParent._legal );
		_botRollMode.SetParent( newParent == null ? null : newParent._botRollMode );
		_classEfficiency.SetParent( newParent == null ? null : newParent._classEfficiency );
		_canMount.SetParent( newParent == null ? null : newParent._canMount );
		_askBlessCooldown.SetParent( newParent == null ? null : newParent._askBlessCooldown );
		_defaultTalentsSets.SetParent( newParent == null ? null : newParent._defaultTalentsSets );
		_mightyTalentSet.SetParent( newParent == null ? null : newParent._mightyTalentSet );
		_lobbyData.SetParent( newParent == null ? null : newParent._lobbyData );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_id.Reset();
		_legal.Reset();
		_botRollMode.Reset();
		_classEfficiency.Reset();
		_canMount.Reset();
		_askBlessCooldown.Reset();
		_defaultTalentsSets.Reset();
		_mightyTalentSet.Reset();
		_lobbyData.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _legal.IsDerivedFromParent()
			&& _botRollMode.IsDerivedFromParent()
			&& _classEfficiency.IsDerivedFromParent()
			&& _canMount.IsDerivedFromParent()
			&& _askBlessCooldown.IsDerivedFromParent()
			&& _defaultTalentsSets.IsDerivedFromParent()
			&& _mightyTalentSet.IsDerivedFromParent()
			&& _lobbyData.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "legal" )
			_legal.Reset();
		else if ( fieldName == "botRollMode" )
			_botRollMode.Reset();
		else if ( fieldName == "classEfficiency" )
			_classEfficiency.Reset();
		else if ( fieldName == "canMount" )
			_canMount.Reset();
		else if ( fieldName == "askBlessCooldown" )
			_askBlessCooldown.Reset();
		else if ( fieldName == "defaultTalentsSets" )
			_defaultTalentsSets.Reset();
		else if ( fieldName == "mightyTalentSet" )
			_mightyTalentSet.Reset();
		else if ( fieldName == "lobbyData" )
			_lobbyData.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "legal" )
			return _legal.IsDerivedFromParent();
		if ( fieldName == "botRollMode" )
			return _botRollMode.IsDerivedFromParent();
		if ( fieldName == "classEfficiency" )
			return _classEfficiency.IsDerivedFromParent();
		if ( fieldName == "canMount" )
			return _canMount.IsDerivedFromParent();
		if ( fieldName == "askBlessCooldown" )
			return _askBlessCooldown.IsDerivedFromParent();
		if ( fieldName == "defaultTalentsSets" )
			return _defaultTalentsSets.IsDerivedFromParent();
		if ( fieldName == "mightyTalentSet" )
			return _mightyTalentSet.IsDerivedFromParent();
		if ( fieldName == "lobbyData" )
			return _lobbyData.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[TypeId(0xB199C440)]
[UseTypeName("SUMMONED")]
public class Summoned : Creature
{
	private UndoRedoDBPtr<Summoned> ___parent;
	[HideInOutliner]
	public new DBPtr<Summoned> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<CreepSkin>> _creepSkins;

	[Description( "List of available skins" )]
	public libdb.IChangeableList<DBPtr<CreepSkin>> creepSkins { get { return _creepSkins; } set { _creepSkins.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Summoned>(owner);
		_creepSkins = new UndoRedoAssignableList<DBPtr<CreepSkin>>( owner );
		___parent.Changed += FireChangedEvent;
		_creepSkins.Changed += FireChangedEvent;
	}

	public Summoned()
	{
		Initialize( this );
	}
	private void AssignSelf( Summoned source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Summoned" );
		creepSkins = source.creepSkins;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Summoned source = _source as Summoned;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Summoned" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Summoned newParent = rawParent == null ? null : rawParent.Get<Summoned>();
		if ( newParent == null && _newParent is Summoned )
			newParent = _newParent as Summoned;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_creepSkins.SetParent( newParent == null ? null : newParent._creepSkins );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_creepSkins.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_creepSkins.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "creepSkins" )
			_creepSkins.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "creepSkins" )
			return _creepSkins.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2C6C1340)]
[UseTypeName("TOWR")]
public class ControllableTower : Tower
{
	private UndoRedoDBPtr<ControllableTower> ___parent;
	[HideInOutliner]
	public new DBPtr<ControllableTower> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ControllableTower>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public ControllableTower()
	{
		Initialize( this );
	}
	private void AssignSelf( ControllableTower source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ControllableTower" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ControllableTower source = _source as ControllableTower;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ControllableTower" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ControllableTower newParent = rawParent == null ? null : rawParent.Get<ControllableTower>();
		if ( newParent == null && _newParent is ControllableTower )
			newParent = _newParent as ControllableTower;
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

[DBVersion(1)]
[TypeId(0x2C616C00)]
[UseTypeName("TREE")]
public class TreeObject : MultiStateObject
{
	private UndoRedoDBPtr<TreeObject> ___parent;
	[HideInOutliner]
	public new DBPtr<TreeObject> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _stubsSceneObjects;
	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _nightStubsSceneObjects;
	private UndoRedo<bool> _wonderfulTree;

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> stubsSceneObjects { get { return _stubsSceneObjects; } set { _stubsSceneObjects.Assign( value ); } }

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> nightStubsSceneObjects { get { return _nightStubsSceneObjects; } set { _nightStubsSceneObjects.Assign( value ); } }

	public bool wonderfulTree { get { return _wonderfulTree.Get(); } set { _wonderfulTree.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TreeObject>(owner);
		_stubsSceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ENatureType ) );
		_nightStubsSceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ENatureType ) );
		_wonderfulTree = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_stubsSceneObjects.Changed += FireChangedEvent;
		_nightStubsSceneObjects.Changed += FireChangedEvent;
		_wonderfulTree.Changed += FireChangedEvent;
	}

	public TreeObject()
	{
		Initialize( this );
	}
	private void AssignSelf( TreeObject source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TreeObject" );
		stubsSceneObjects = source.stubsSceneObjects;
		nightStubsSceneObjects = source.nightStubsSceneObjects;
		wonderfulTree = source.wonderfulTree;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TreeObject source = _source as TreeObject;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TreeObject" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TreeObject newParent = rawParent == null ? null : rawParent.Get<TreeObject>();
		if ( newParent == null && _newParent is TreeObject )
			newParent = _newParent as TreeObject;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stubsSceneObjects.SetParent( newParent == null ? null : newParent._stubsSceneObjects );
		_nightStubsSceneObjects.SetParent( newParent == null ? null : newParent._nightStubsSceneObjects );
		_wonderfulTree.SetParent( newParent == null ? null : newParent._wonderfulTree );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stubsSceneObjects.Reset();
		_nightStubsSceneObjects.Reset();
		_wonderfulTree.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stubsSceneObjects.IsDerivedFromParent()
			&& _nightStubsSceneObjects.IsDerivedFromParent()
			&& _wonderfulTree.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stubsSceneObjects" )
			_stubsSceneObjects.Reset();
		else if ( fieldName == "nightStubsSceneObjects" )
			_nightStubsSceneObjects.Reset();
		else if ( fieldName == "wonderfulTree" )
			_wonderfulTree.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "stubsSceneObjects" )
			return _stubsSceneObjects.IsDerivedFromParent();
		if ( fieldName == "nightStubsSceneObjects" )
			return _nightStubsSceneObjects.IsDerivedFromParent();
		if ( fieldName == "wonderfulTree" )
			return _wonderfulTree.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x11624C43)]
[UseTypeName("PTOB")]
public class BasePet : Creature
{
	private UndoRedoDBPtr<BasePet> ___parent;
	[HideInOutliner]
	public new DBPtr<BasePet> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _test;

	public float test { get { return _test.Get(); } set { _test.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasePet>(owner);
		_test = new UndoRedo<float>( owner, 0.15f );
		___parent.Changed += FireChangedEvent;
		_test.Changed += FireChangedEvent;
	}

	public BasePet()
	{
		Initialize( this );
	}
	private void AssignSelf( BasePet source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasePet" );
		test = source.test;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasePet source = _source as BasePet;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasePet" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasePet newParent = rawParent == null ? null : rawParent.Get<BasePet>();
		if ( newParent == null && _newParent is BasePet )
			newParent = _newParent as BasePet;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_test.SetParent( newParent == null ? null : newParent._test );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_test.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_test.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "test" )
			_test.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "test" )
			return _test.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("UTCT")]
public class UnitCategories : DBResource
{
	private UndoRedoDBPtr<UnitCategories> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitCategories> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<EUnitCategory> _elements;

	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<EUnitCategory> elements { get { return _elements; } set { _elements.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitCategories>(owner);
		_elements = new UndoRedoList<EUnitCategory>( owner, typeof( EUnitType ) );
		___parent.Changed += FireChangedEvent;
		_elements.Changed += FireChangedEvent;
	}

	public UnitCategories()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitCategories source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitCategories" );
		elements = source.elements;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitCategories source = _source as UnitCategories;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitCategories" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitCategories newParent = rawParent == null ? null : rawParent.Get<UnitCategories>();
		if ( newParent == null && _newParent is UnitCategories )
			newParent = _newParent as UnitCategories;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_elements.SetParent( newParent == null ? null : newParent._elements );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_elements.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_elements.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "elements" )
			_elements.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "elements" )
			return _elements.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("UCP")]
public class UnitCategoriesParams : DBResource
{
	private UndoRedoDBPtr<UnitCategoriesParams> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitCategoriesParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UnitCategoryParams> _elements;

	[EnumArray(typeof(EUnitCategory))]
	public libdb.IChangeableList<UnitCategoryParams> elements { get { return _elements; } set { _elements.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitCategoriesParams>(owner);
		_elements = new UndoRedoAssignableList<UnitCategoryParams>( owner, typeof( EUnitCategory ) );
		___parent.Changed += FireChangedEvent;
		_elements.Changed += FireChangedEvent;
	}

	public UnitCategoriesParams()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitCategoriesParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitCategoriesParams" );
		elements = source.elements;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitCategoriesParams source = _source as UnitCategoriesParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitCategoriesParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitCategoriesParams newParent = rawParent == null ? null : rawParent.Get<UnitCategoriesParams>();
		if ( newParent == null && _newParent is UnitCategoriesParams )
			newParent = _newParent as UnitCategoriesParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_elements.SetParent( newParent == null ? null : newParent._elements );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_elements.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_elements.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "elements" )
			_elements.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "elements" )
			return _elements.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xE78B3C80)]
[UseTypeName("USBL")]
public class UsableBuilding : Building
{
	private UndoRedoDBPtr<UsableBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<UsableBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UsableBuilding>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UsableBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( UsableBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UsableBuilding" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UsableBuilding source = _source as UsableBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UsableBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UsableBuilding newParent = rawParent == null ? null : rawParent.Get<UsableBuilding>();
		if ( newParent == null && _newParent is UsableBuilding )
			newParent = _newParent as UsableBuilding;
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

[TypeId(0xEF91A282)]
[UseTypeName("WFUB")]
public class WarFogUnblock : GameObject
{
	private UndoRedoDBPtr<WarFogUnblock> ___parent;
	[HideInOutliner]
	public new DBPtr<WarFogUnblock> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _radius;
	private UndoRedo<EFactionFlags> _faction;

	[Description( "Объект открывает warfog в данном радиусе" )]
	public int radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Description( "Объект открывает туман войны только для указаной фракции" )]
	[HideEnumValues("Self", "Opposite")]
	public EFactionFlags faction { get { return _faction.Get(); } set { _faction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WarFogUnblock>(owner);
		_radius = new UndoRedo<int>( owner, 0 );
		_faction = new UndoRedo<EFactionFlags>( owner, EFactionFlags.FactionBurn | EFactionFlags.FactionFreeze );
		___parent.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_faction.Changed += FireChangedEvent;
	}

	public WarFogUnblock()
	{
		Initialize( this );
	}
	private void AssignSelf( WarFogUnblock source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WarFogUnblock" );
		radius = source.radius;
		faction = source.faction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WarFogUnblock source = _source as WarFogUnblock;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WarFogUnblock" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WarFogUnblock newParent = rawParent == null ? null : rawParent.Get<WarFogUnblock>();
		if ( newParent == null && _newParent is WarFogUnblock )
			newParent = _newParent as WarFogUnblock;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_radius.SetParent( newParent == null ? null : newParent._radius );
		_faction.SetParent( newParent == null ? null : newParent._faction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_radius.Reset();
		_faction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_radius.IsDerivedFromParent()
			&& _faction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "faction" )
			_faction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "faction" )
			return _faction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
