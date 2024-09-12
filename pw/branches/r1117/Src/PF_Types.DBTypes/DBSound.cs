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
public enum SoundAmbientGroup
{
	BaseA = 0,
	BaseB = 1,
	ForestN = 2,
	ForestA = 3,
	ForestB = 4,
	Water = 5,
	Road = 6,
};

public enum SoundScene
{
	SessionA = 0,
	SessionB = 1,
	Minigame_02 = 2,
	Loading = 3,
	Dead = 4,
	Battle = 5,
	Win = 6,
	Defeat = 7,
	TutorialA = 8,
	TutorialB = 9,
	TowerDeath = 10,
};

public class SoundAmbientDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SoundAmbientDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _paramName;
	private HDRColor _color;
	private UndoRedo<string> _reverbPresetName;

	public string paramName { get { return _paramName.Get(); } set { _paramName.Set( value ); } }

	public HDRColor color { get { return _color; } set { _color.Assign( value ); } }

	public string reverbPresetName { get { return _reverbPresetName.Get(); } set { _reverbPresetName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_paramName = new UndoRedo<string>( owner, string.Empty );
		HDRColor __color = new HDRColor(); // Construct default object for color
		__color.A = 0.0f;
		_color = new HDRColor( owner, __color );
		_reverbPresetName = new UndoRedo<string>( owner, "Ambient" );
		_paramName.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_reverbPresetName.Changed += FireChangedEvent;
	}

	public SoundAmbientDesc()
	{
		Initialize( GetOwner() );
	}

	public SoundAmbientDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SoundAmbientDesc( DBResource owner, SoundAmbientDesc source )
		: this(owner, source, true){}

	protected SoundAmbientDesc( DBResource owner, SoundAmbientDesc source, bool fireEvent )
	{
		_paramName = new UndoRedo<string>( owner, source.paramName );
		_color = new HDRColor( owner, source.color );
		_reverbPresetName = new UndoRedo<string>( owner, source.reverbPresetName );
		_paramName.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_reverbPresetName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SoundAmbientDesc source = _source as SoundAmbientDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundAmbientDesc" );
		paramName = source.paramName;
		color = source.color;
		reverbPresetName = source.reverbPresetName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SoundAmbientDesc newParent = _newParent as SoundAmbientDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_paramName.SetParent( newParent == null ? null : newParent._paramName );
		_color.SetParent( newParent == null ? null : newParent._color );
		_reverbPresetName.SetParent( newParent == null ? null : newParent._reverbPresetName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_paramName.Reset();
		_color.Reset();
		_reverbPresetName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_paramName.IsDerivedFromParent()
			&& _color.IsDerivedFromParent()
			&& _reverbPresetName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "paramName" )
			_paramName.Reset();
		else if ( fieldName == "color" )
			_color.Reset();
		else if ( fieldName == "reverbPresetName" )
			_reverbPresetName.Reset();
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
		if ( fieldName == "color" )
			return _color.IsDerivedFromParent();
		if ( fieldName == "reverbPresetName" )
			return _reverbPresetName.IsDerivedFromParent();
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
public class TimerSounds : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TimerSounds __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBFMODEventDesc _startTimerSound;
	private DBFMODEventDesc _startEventA;
	private DBFMODEventDesc _startEventB;
	private DBFMODEventDesc _deadTimerSound;
	private UndoRedo<string> _deadReverbName;
	private UndoRedo<float> _timeToRestorePitch;
	private UndoRedo<float> _timeToTickOnStart;

	[Description( "Start timer sound" )]
	public DBFMODEventDesc startTimerSound { get { return _startTimerSound; } set { _startTimerSound.Assign( value ); } }

	[Description( "Start event for A" )]
	public DBFMODEventDesc startEventA { get { return _startEventA; } set { _startEventA.Assign( value ); } }

	[Description( "Start event for B" )]
	public DBFMODEventDesc startEventB { get { return _startEventB; } set { _startEventB.Assign( value ); } }

	[Description( "Dead timer sound" )]
	public DBFMODEventDesc deadTimerSound { get { return _deadTimerSound; } set { _deadTimerSound.Assign( value ); } }

	[Description( "Dead reverb preset name" )]
	public string deadReverbName { get { return _deadReverbName.Get(); } set { _deadReverbName.Set( value ); } }

	public float timeToRestorePitch { get { return _timeToRestorePitch.Get(); } set { _timeToRestorePitch.Set( value ); } }

	public float timeToTickOnStart { get { return _timeToTickOnStart.Get(); } set { _timeToTickOnStart.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_startTimerSound = new DBFMODEventDesc( owner );
		_startEventA = new DBFMODEventDesc( owner );
		_startEventB = new DBFMODEventDesc( owner );
		_deadTimerSound = new DBFMODEventDesc( owner );
		_deadReverbName = new UndoRedo<string>( owner, string.Empty );
		_timeToRestorePitch = new UndoRedo<float>( owner, 5.0f );
		_timeToTickOnStart = new UndoRedo<float>( owner, 10.0f );
		_startTimerSound.Changed += FireChangedEvent;
		_startEventA.Changed += FireChangedEvent;
		_startEventB.Changed += FireChangedEvent;
		_deadTimerSound.Changed += FireChangedEvent;
		_deadReverbName.Changed += FireChangedEvent;
		_timeToRestorePitch.Changed += FireChangedEvent;
		_timeToTickOnStart.Changed += FireChangedEvent;
	}

	public TimerSounds()
	{
		Initialize( GetOwner() );
	}

	public TimerSounds( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TimerSounds( DBResource owner, TimerSounds source )
		: this(owner, source, true){}

	protected TimerSounds( DBResource owner, TimerSounds source, bool fireEvent )
	{
		_startTimerSound = new DBFMODEventDesc( owner, source.startTimerSound );
		_startEventA = new DBFMODEventDesc( owner, source.startEventA );
		_startEventB = new DBFMODEventDesc( owner, source.startEventB );
		_deadTimerSound = new DBFMODEventDesc( owner, source.deadTimerSound );
		_deadReverbName = new UndoRedo<string>( owner, source.deadReverbName );
		_timeToRestorePitch = new UndoRedo<float>( owner, source.timeToRestorePitch );
		_timeToTickOnStart = new UndoRedo<float>( owner, source.timeToTickOnStart );
		_startTimerSound.Changed += FireChangedEvent;
		_startEventA.Changed += FireChangedEvent;
		_startEventB.Changed += FireChangedEvent;
		_deadTimerSound.Changed += FireChangedEvent;
		_deadReverbName.Changed += FireChangedEvent;
		_timeToRestorePitch.Changed += FireChangedEvent;
		_timeToTickOnStart.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TimerSounds source = _source as TimerSounds;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TimerSounds" );
		startTimerSound = source.startTimerSound;
		startEventA = source.startEventA;
		startEventB = source.startEventB;
		deadTimerSound = source.deadTimerSound;
		deadReverbName = source.deadReverbName;
		timeToRestorePitch = source.timeToRestorePitch;
		timeToTickOnStart = source.timeToTickOnStart;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TimerSounds newParent = _newParent as TimerSounds;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_startTimerSound.SetParent( newParent == null ? null : newParent._startTimerSound );
		_startEventA.SetParent( newParent == null ? null : newParent._startEventA );
		_startEventB.SetParent( newParent == null ? null : newParent._startEventB );
		_deadTimerSound.SetParent( newParent == null ? null : newParent._deadTimerSound );
		_deadReverbName.SetParent( newParent == null ? null : newParent._deadReverbName );
		_timeToRestorePitch.SetParent( newParent == null ? null : newParent._timeToRestorePitch );
		_timeToTickOnStart.SetParent( newParent == null ? null : newParent._timeToTickOnStart );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_startTimerSound.Reset();
		_startEventA.Reset();
		_startEventB.Reset();
		_deadTimerSound.Reset();
		_deadReverbName.Reset();
		_timeToRestorePitch.Reset();
		_timeToTickOnStart.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_startTimerSound.IsDerivedFromParent()
			&& _startEventA.IsDerivedFromParent()
			&& _startEventB.IsDerivedFromParent()
			&& _deadTimerSound.IsDerivedFromParent()
			&& _deadReverbName.IsDerivedFromParent()
			&& _timeToRestorePitch.IsDerivedFromParent()
			&& _timeToTickOnStart.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "startTimerSound" )
			_startTimerSound.Reset();
		else if ( fieldName == "startEventA" )
			_startEventA.Reset();
		else if ( fieldName == "startEventB" )
			_startEventB.Reset();
		else if ( fieldName == "deadTimerSound" )
			_deadTimerSound.Reset();
		else if ( fieldName == "deadReverbName" )
			_deadReverbName.Reset();
		else if ( fieldName == "timeToRestorePitch" )
			_timeToRestorePitch.Reset();
		else if ( fieldName == "timeToTickOnStart" )
			_timeToTickOnStart.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "startTimerSound" )
			return _startTimerSound.IsDerivedFromParent();
		if ( fieldName == "startEventA" )
			return _startEventA.IsDerivedFromParent();
		if ( fieldName == "startEventB" )
			return _startEventB.IsDerivedFromParent();
		if ( fieldName == "deadTimerSound" )
			return _deadTimerSound.IsDerivedFromParent();
		if ( fieldName == "deadReverbName" )
			return _deadReverbName.IsDerivedFromParent();
		if ( fieldName == "timeToRestorePitch" )
			return _timeToRestorePitch.IsDerivedFromParent();
		if ( fieldName == "timeToTickOnStart" )
			return _timeToTickOnStart.IsDerivedFromParent();
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

[DbRoot]
public class SoundRoot : DBResource
{
	private UndoRedoDBPtr<SoundRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SoundRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<SoundSceneDesc> _sceneScenes;
	private TimerSounds _timerSounds;
	private DBFMODEventDesc _heartbeat;
	private DBFMODEventDesc _heartbeatFemale;
	private UndoRedo<string> _heartbeatParamName;
	private DBFMODEventDesc _ambient;
	private UndoRedoAssignableList<SoundAmbientDesc> _ambienceGroups;
	private DBFMODEventDesc _preferencesVolumeHasChanged;
	private DBFMODEventDesc _lastHit;
	private UndoRedo<float> _timerHeroAskIdle;
	private UndoRedo<float> _timeToTowerDeath;

	[EnumArray(typeof(SoundScene))]
	public libdb.IChangeableList<SoundSceneDesc> sceneScenes { get { return _sceneScenes; } set { _sceneScenes.Assign( value ); } }

	public TimerSounds timerSounds { get { return _timerSounds; } set { _timerSounds.Assign( value ); } }

	[Description( "Heartbeat sound" )]
	public DBFMODEventDesc heartbeat { get { return _heartbeat; } set { _heartbeat.Assign( value ); } }

	[Description( "Heartbeat sound for female" )]
	public DBFMODEventDesc heartbeatFemale { get { return _heartbeatFemale; } set { _heartbeatFemale.Assign( value ); } }

	[Description( "Heartbeat sound - life parameter name" )]
	public string heartbeatParamName { get { return _heartbeatParamName.Get(); } set { _heartbeatParamName.Set( value ); } }

	[Description( "Ambient sound" )]
	public DBFMODEventDesc ambient { get { return _ambient; } set { _ambient.Assign( value ); } }

	[EnumArray(typeof(SoundAmbientGroup))]
	public libdb.IChangeableList<SoundAmbientDesc> ambienceGroups { get { return _ambienceGroups; } set { _ambienceGroups.Assign( value ); } }

	[Description( "Звук воспроизводится в экране настроек после изменения положения ползунка громкости" )]
	public DBFMODEventDesc preferencesVolumeHasChanged { get { return _preferencesVolumeHasChanged; } set { _preferencesVolumeHasChanged.Assign( value ); } }

	[Description( "Звук убийства крипа героем ( lastHit )" )]
	public DBFMODEventDesc lastHit { get { return _lastHit; } set { _lastHit.Assign( value ); } }

	[Description( "Timer for playing ask idle" )]
	public float timerHeroAskIdle { get { return _timerHeroAskIdle.Get(); } set { _timerHeroAskIdle.Set( value ); } }

	[Description( "Время, после которого опять может начать играть сцена разрушения башни" )]
	public float timeToTowerDeath { get { return _timeToTowerDeath.Get(); } set { _timeToTowerDeath.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SoundRoot>(owner);
		_sceneScenes = new UndoRedoAssignableList<SoundSceneDesc>( owner, typeof( SoundScene ) );
		_timerSounds = new TimerSounds( owner );
		_heartbeat = new DBFMODEventDesc( owner );
		_heartbeatFemale = new DBFMODEventDesc( owner );
		_heartbeatParamName = new UndoRedo<string>( owner, string.Empty );
		_ambient = new DBFMODEventDesc( owner );
		_ambienceGroups = new UndoRedoAssignableList<SoundAmbientDesc>( owner, typeof( SoundAmbientGroup ) );
		_preferencesVolumeHasChanged = new DBFMODEventDesc( owner );
		_lastHit = new DBFMODEventDesc( owner );
		_timerHeroAskIdle = new UndoRedo<float>( owner, 15.0f );
		_timeToTowerDeath = new UndoRedo<float>( owner, 60.0f );
		___parent.Changed += FireChangedEvent;
		_sceneScenes.Changed += FireChangedEvent;
		_timerSounds.Changed += FireChangedEvent;
		_heartbeat.Changed += FireChangedEvent;
		_heartbeatFemale.Changed += FireChangedEvent;
		_heartbeatParamName.Changed += FireChangedEvent;
		_ambient.Changed += FireChangedEvent;
		_ambienceGroups.Changed += FireChangedEvent;
		_preferencesVolumeHasChanged.Changed += FireChangedEvent;
		_lastHit.Changed += FireChangedEvent;
		_timerHeroAskIdle.Changed += FireChangedEvent;
		_timeToTowerDeath.Changed += FireChangedEvent;
	}

	public SoundRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SoundRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SoundRoot" );
		sceneScenes = source.sceneScenes;
		timerSounds = source.timerSounds;
		heartbeat = source.heartbeat;
		heartbeatFemale = source.heartbeatFemale;
		heartbeatParamName = source.heartbeatParamName;
		ambient = source.ambient;
		ambienceGroups = source.ambienceGroups;
		preferencesVolumeHasChanged = source.preferencesVolumeHasChanged;
		lastHit = source.lastHit;
		timerHeroAskIdle = source.timerHeroAskIdle;
		timeToTowerDeath = source.timeToTowerDeath;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SoundRoot source = _source as SoundRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SoundRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SoundRoot newParent = rawParent == null ? null : rawParent.Get<SoundRoot>();
		if ( newParent == null && _newParent is SoundRoot )
			newParent = _newParent as SoundRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sceneScenes.SetParent( newParent == null ? null : newParent._sceneScenes );
		_timerSounds.SetParent( newParent == null ? null : newParent._timerSounds );
		_heartbeat.SetParent( newParent == null ? null : newParent._heartbeat );
		_heartbeatFemale.SetParent( newParent == null ? null : newParent._heartbeatFemale );
		_heartbeatParamName.SetParent( newParent == null ? null : newParent._heartbeatParamName );
		_ambient.SetParent( newParent == null ? null : newParent._ambient );
		_ambienceGroups.SetParent( newParent == null ? null : newParent._ambienceGroups );
		_preferencesVolumeHasChanged.SetParent( newParent == null ? null : newParent._preferencesVolumeHasChanged );
		_lastHit.SetParent( newParent == null ? null : newParent._lastHit );
		_timerHeroAskIdle.SetParent( newParent == null ? null : newParent._timerHeroAskIdle );
		_timeToTowerDeath.SetParent( newParent == null ? null : newParent._timeToTowerDeath );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sceneScenes.Reset();
		_timerSounds.Reset();
		_heartbeat.Reset();
		_heartbeatFemale.Reset();
		_heartbeatParamName.Reset();
		_ambient.Reset();
		_ambienceGroups.Reset();
		_preferencesVolumeHasChanged.Reset();
		_lastHit.Reset();
		_timerHeroAskIdle.Reset();
		_timeToTowerDeath.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sceneScenes.IsDerivedFromParent()
			&& _timerSounds.IsDerivedFromParent()
			&& _heartbeat.IsDerivedFromParent()
			&& _heartbeatFemale.IsDerivedFromParent()
			&& _heartbeatParamName.IsDerivedFromParent()
			&& _ambient.IsDerivedFromParent()
			&& _ambienceGroups.IsDerivedFromParent()
			&& _preferencesVolumeHasChanged.IsDerivedFromParent()
			&& _lastHit.IsDerivedFromParent()
			&& _timerHeroAskIdle.IsDerivedFromParent()
			&& _timeToTowerDeath.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sceneScenes" )
			_sceneScenes.Reset();
		else if ( fieldName == "timerSounds" )
			_timerSounds.Reset();
		else if ( fieldName == "heartbeat" )
			_heartbeat.Reset();
		else if ( fieldName == "heartbeatFemale" )
			_heartbeatFemale.Reset();
		else if ( fieldName == "heartbeatParamName" )
			_heartbeatParamName.Reset();
		else if ( fieldName == "ambient" )
			_ambient.Reset();
		else if ( fieldName == "ambienceGroups" )
			_ambienceGroups.Reset();
		else if ( fieldName == "preferencesVolumeHasChanged" )
			_preferencesVolumeHasChanged.Reset();
		else if ( fieldName == "lastHit" )
			_lastHit.Reset();
		else if ( fieldName == "timerHeroAskIdle" )
			_timerHeroAskIdle.Reset();
		else if ( fieldName == "timeToTowerDeath" )
			_timeToTowerDeath.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sceneScenes" )
			return _sceneScenes.IsDerivedFromParent();
		if ( fieldName == "timerSounds" )
			return _timerSounds.IsDerivedFromParent();
		if ( fieldName == "heartbeat" )
			return _heartbeat.IsDerivedFromParent();
		if ( fieldName == "heartbeatFemale" )
			return _heartbeatFemale.IsDerivedFromParent();
		if ( fieldName == "heartbeatParamName" )
			return _heartbeatParamName.IsDerivedFromParent();
		if ( fieldName == "ambient" )
			return _ambient.IsDerivedFromParent();
		if ( fieldName == "ambienceGroups" )
			return _ambienceGroups.IsDerivedFromParent();
		if ( fieldName == "preferencesVolumeHasChanged" )
			return _preferencesVolumeHasChanged.IsDerivedFromParent();
		if ( fieldName == "lastHit" )
			return _lastHit.IsDerivedFromParent();
		if ( fieldName == "timerHeroAskIdle" )
			return _timerHeroAskIdle.IsDerivedFromParent();
		if ( fieldName == "timeToTowerDeath" )
			return _timeToTowerDeath.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
