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
[Custom("DBServer", "Social")]
public enum EMapType
{
	None = 0,
	PvP = 1,
	CTE = 2,
	Training = 3,
	Tutorial = 4,
	Series = 5,
	Cooperative = 6,
};

[Custom("Social")]
public enum PartyMode
{
	NotAllowed = 0,
	OnlyAllies = 1,
	AlliesAndEnemies = 2,
};

public class AdvMapObject : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AdvMapObject __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<GameObject> _gameObject;
	private Placement2 _offset;
	private UndoRedo<EPlayerID> _player;
	private UndoRedo<bool> _lockMap;
	private UndoRedo<string> _scriptName;
	private UndoRedo<string> _scriptGroupName;

	public DBPtr<GameObject> gameObject { get { return _gameObject.Get(); } set { _gameObject.Set( value ); } }

	[Description( "Offset from node" )]
	public Placement2 offset { get { return _offset; } set { _offset.Assign( value ); } }

	[Description( "Owner player" )]
	public EPlayerID player { get { return _player.Get(); } set { _player.Set( value ); } }

	[Description( "Whether this object should lock map or not" )]
	public bool lockMap { get { return _lockMap.Get(); } set { _lockMap.Set( value ); } }

	[Description( "Name for searching object in script" )]
	public string scriptName { get { return _scriptName.Get(); } set { _scriptName.Set( value ); } }

	[Description( "Name for searching object in script" )]
	public string scriptGroupName { get { return _scriptGroupName.Get(); } set { _scriptGroupName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_gameObject = new UndoRedoDBPtr<GameObject>( owner );
		_offset = new Placement2( owner );
		_player = new UndoRedo<EPlayerID>( owner, EPlayerID.None );
		_lockMap = new UndoRedo<bool>( owner, true );
		_scriptName = new UndoRedo<string>( owner, string.Empty );
		_scriptGroupName = new UndoRedo<string>( owner, string.Empty );
		_gameObject.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_player.Changed += FireChangedEvent;
		_lockMap.Changed += FireChangedEvent;
		_scriptName.Changed += FireChangedEvent;
		_scriptGroupName.Changed += FireChangedEvent;
	}

	public AdvMapObject()
	{
		Initialize( GetOwner() );
	}

	public AdvMapObject( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AdvMapObject( DBResource owner, AdvMapObject source )
		: this(owner, source, true){}

	protected AdvMapObject( DBResource owner, AdvMapObject source, bool fireEvent )
	{
		_gameObject = new UndoRedoDBPtr<GameObject>( owner, source.gameObject );
		_offset = new Placement2( owner, source.offset );
		_player = new UndoRedo<EPlayerID>( owner, source.player );
		_lockMap = new UndoRedo<bool>( owner, source.lockMap );
		_scriptName = new UndoRedo<string>( owner, source.scriptName );
		_scriptGroupName = new UndoRedo<string>( owner, source.scriptGroupName );
		_gameObject.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_player.Changed += FireChangedEvent;
		_lockMap.Changed += FireChangedEvent;
		_scriptName.Changed += FireChangedEvent;
		_scriptGroupName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AdvMapObject source = _source as AdvMapObject;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapObject" );
		gameObject = source.gameObject;
		offset = source.offset;
		player = source.player;
		lockMap = source.lockMap;
		scriptName = source.scriptName;
		scriptGroupName = source.scriptGroupName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AdvMapObject newParent = _newParent as AdvMapObject;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_gameObject.SetParent( newParent == null ? null : newParent._gameObject );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_player.SetParent( newParent == null ? null : newParent._player );
		_lockMap.SetParent( newParent == null ? null : newParent._lockMap );
		_scriptName.SetParent( newParent == null ? null : newParent._scriptName );
		_scriptGroupName.SetParent( newParent == null ? null : newParent._scriptGroupName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_gameObject.Reset();
		_offset.Reset();
		_player.Reset();
		_lockMap.Reset();
		_scriptName.Reset();
		_scriptGroupName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_gameObject.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _player.IsDerivedFromParent()
			&& _lockMap.IsDerivedFromParent()
			&& _scriptName.IsDerivedFromParent()
			&& _scriptGroupName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "gameObject" )
			_gameObject.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "player" )
			_player.Reset();
		else if ( fieldName == "lockMap" )
			_lockMap.Reset();
		else if ( fieldName == "scriptName" )
			_scriptName.Reset();
		else if ( fieldName == "scriptGroupName" )
			_scriptGroupName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "gameObject" )
			return _gameObject.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "player" )
			return _player.IsDerivedFromParent();
		if ( fieldName == "lockMap" )
			return _lockMap.IsDerivedFromParent();
		if ( fieldName == "scriptName" )
			return _scriptName.IsDerivedFromParent();
		if ( fieldName == "scriptGroupName" )
			return _scriptGroupName.IsDerivedFromParent();
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
public class AdvMapPlayerData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AdvMapPlayerData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Hero> _hero;
	private TextRef _nickname;

	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	[Description( "Computer player nickname (use hero name if empty)" )]
	public TextRef nickname { get { return _nickname; } set { _nickname.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_hero = new UndoRedoDBPtr<Hero>( owner );
		_nickname = new TextRef( owner, new TextRef() );
		_hero.Changed += FireChangedEvent;
		_nickname.Changed += FireChangedEvent;
	}

	public AdvMapPlayerData()
	{
		Initialize( GetOwner() );
	}

	public AdvMapPlayerData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AdvMapPlayerData( DBResource owner, AdvMapPlayerData source )
		: this(owner, source, true){}

	protected AdvMapPlayerData( DBResource owner, AdvMapPlayerData source, bool fireEvent )
	{
		_hero = new UndoRedoDBPtr<Hero>( owner, source.hero );
		_nickname = new TextRef( owner, source.nickname );
		_hero.Changed += FireChangedEvent;
		_nickname.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AdvMapPlayerData source = _source as AdvMapPlayerData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapPlayerData" );
		hero = source.hero;
		nickname = source.nickname;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AdvMapPlayerData newParent = _newParent as AdvMapPlayerData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_hero.SetParent( newParent == null ? null : newParent._hero );
		_nickname.SetParent( newParent == null ? null : newParent._nickname );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_hero.Reset();
		_nickname.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& _nickname.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else if ( fieldName == "nickname" )
			_nickname.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		if ( fieldName == "nickname" )
			return _nickname.IsDerivedFromParent();
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

public class CreepAnnounce : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreepAnnounce __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<BaseCreepSpawner> _spawner;
	private UndoRedoAssignableList<DBPtr<AdvMapCreep>> _creeps;

	public DBPtr<BaseCreepSpawner> spawner { get { return _spawner.Get(); } set { _spawner.Set( value ); } }

	public libdb.IChangeableList<DBPtr<AdvMapCreep>> creeps { get { return _creeps; } set { _creeps.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_spawner = new UndoRedoDBPtr<BaseCreepSpawner>( owner );
		_creeps = new UndoRedoAssignableList<DBPtr<AdvMapCreep>>( owner );
		_spawner.Changed += FireChangedEvent;
		_creeps.Changed += FireChangedEvent;
	}

	public CreepAnnounce()
	{
		Initialize( GetOwner() );
	}

	public CreepAnnounce( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreepAnnounce( DBResource owner, CreepAnnounce source )
		: this(owner, source, true){}

	protected CreepAnnounce( DBResource owner, CreepAnnounce source, bool fireEvent )
	{
		_spawner = new UndoRedoDBPtr<BaseCreepSpawner>( owner, source.spawner );
		_creeps = new UndoRedoAssignableList<DBPtr<AdvMapCreep>>( owner );
		_creeps.Assign( source.creeps );
		_spawner.Changed += FireChangedEvent;
		_creeps.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreepAnnounce source = _source as CreepAnnounce;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepAnnounce" );
		spawner = source.spawner;
		creeps = source.creeps;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreepAnnounce newParent = _newParent as CreepAnnounce;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_spawner.SetParent( newParent == null ? null : newParent._spawner );
		_creeps.SetParent( newParent == null ? null : newParent._creeps );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_spawner.Reset();
		_creeps.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_spawner.IsDerivedFromParent()
			&& _creeps.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "spawner" )
			_spawner.Reset();
		else if ( fieldName == "creeps" )
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
		if ( fieldName == "spawner" )
			return _spawner.IsDerivedFromParent();
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

public class LoadingBackgroundImages : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LoadingBackgroundImages __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Texture> _back;
	private UndoRedoDBPtr<Texture> _logo;

	[Description( "бэк лоадинг скрина" )]
	public DBPtr<Texture> back { get { return _back.Get(); } set { _back.Set( value ); } }

	[Description( "логотип. будет выставлен по центру" )]
	public DBPtr<Texture> logo { get { return _logo.Get(); } set { _logo.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_back = new UndoRedoDBPtr<Texture>( owner );
		_logo = new UndoRedoDBPtr<Texture>( owner );
		_back.Changed += FireChangedEvent;
		_logo.Changed += FireChangedEvent;
	}

	public LoadingBackgroundImages()
	{
		Initialize( GetOwner() );
	}

	public LoadingBackgroundImages( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LoadingBackgroundImages( DBResource owner, LoadingBackgroundImages source )
		: this(owner, source, true){}

	protected LoadingBackgroundImages( DBResource owner, LoadingBackgroundImages source, bool fireEvent )
	{
		_back = new UndoRedoDBPtr<Texture>( owner, source.back );
		_logo = new UndoRedoDBPtr<Texture>( owner, source.logo );
		_back.Changed += FireChangedEvent;
		_logo.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LoadingBackgroundImages source = _source as LoadingBackgroundImages;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LoadingBackgroundImages" );
		back = source.back;
		logo = source.logo;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LoadingBackgroundImages newParent = _newParent as LoadingBackgroundImages;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_back.SetParent( newParent == null ? null : newParent._back );
		_logo.SetParent( newParent == null ? null : newParent._logo );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_back.Reset();
		_logo.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_back.IsDerivedFromParent()
			&& _logo.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "back" )
			_back.Reset();
		else if ( fieldName == "logo" )
			_logo.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "back" )
			return _back.IsDerivedFromParent();
		if ( fieldName == "logo" )
			return _logo.IsDerivedFromParent();
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
public class PrimeSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PrimeSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _giveWorldPrimeToDead;
	private UndoRedo<float> _giveWorldPrimeRessurectDelay;
	private UndoRedo<int> _startPrimePerTeam;
	private UndoRedo<int> _giveWorldPrimeAmount;
	private UndoRedoList<float> _multipliers;
	private UndoRedo<float> _naftaForKill;
	private UndoRedo<float> _naftaForAssist;
	private UndoRedo<float> _naftaSpecForKill;
	private UndoRedo<float> _teamNaftaForPresence;
	private UndoRedoDBPtr<KillExperienceModifier> _neutralKillExperienceModifier;
	private UndoRedoDBPtr<HeroNaftaParams> _heroNaftaParams;
	private UndoRedo<float> _awardSpecRange;
	private UndoRedo<float> _awardTeamRange;

	[Description( "Give prime salary to dead heroes" )]
	public bool giveWorldPrimeToDead { get { return _giveWorldPrimeToDead.Get(); } set { _giveWorldPrimeToDead.Set( value ); } }

	[Description( "World prime receiving after-resurrect delay" )]
	public float giveWorldPrimeRessurectDelay { get { return _giveWorldPrimeRessurectDelay.Get(); } set { _giveWorldPrimeRessurectDelay.Set( value ); } }

	[Description( "Amount of prime, divide with all players in team at start of game" )]
	public int startPrimePerTeam { get { return _startPrimePerTeam.Get(); } set { _startPrimePerTeam.Set( value ); } }

	[Description( "Amount of given to all heroes prime in second" )]
	public int giveWorldPrimeAmount { get { return _giveWorldPrimeAmount.Get(); } set { _giveWorldPrimeAmount.Set( value ); } }

	[Description( "NaftaSpecForKill multipliers depending on hero group size" )]
	public libdb.IChangeableList<float> multipliers { get { return _multipliers; } set { _multipliers.Assign( value ); } }

	[Description( "Heroes' NaftaForKill override. Leave -1 if not used." )]
	public float naftaForKill { get { return _naftaForKill.Get(); } set { _naftaForKill.Set( value ); } }

	[Description( "Heroes' NaftaForAssist override. Leave -1 if not used." )]
	public float naftaForAssist { get { return _naftaForAssist.Get(); } set { _naftaForAssist.Set( value ); } }

	[Description( "Heroes' NaftaSpecForKill override. Leave -1 if not used." )]
	public float naftaSpecForKill { get { return _naftaSpecForKill.Get(); } set { _naftaSpecForKill.Set( value ); } }

	[Description( "Heroes' TeamNaftaForPresence override. Leave -1 if not used." )]
	public float teamNaftaForPresence { get { return _teamNaftaForPresence.Get(); } set { _teamNaftaForPresence.Set( value ); } }

	[Description( "NaftaSpecForKill modifiers for level difference of hero and killed neutral creep" )]
	public DBPtr<KillExperienceModifier> neutralKillExperienceModifier { get { return _neutralKillExperienceModifier.Get(); } set { _neutralKillExperienceModifier.Set( value ); } }

	public DBPtr<HeroNaftaParams> heroNaftaParams { get { return _heroNaftaParams.Get(); } set { _heroNaftaParams.Set( value ); } }

	public float awardSpecRange { get { return _awardSpecRange.Get(); } set { _awardSpecRange.Set( value ); } }

	public float awardTeamRange { get { return _awardTeamRange.Get(); } set { _awardTeamRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_giveWorldPrimeToDead = new UndoRedo<bool>( owner, true );
		_giveWorldPrimeRessurectDelay = new UndoRedo<float>( owner, 0.0f );
		_startPrimePerTeam = new UndoRedo<int>( owner, 1500 );
		_giveWorldPrimeAmount = new UndoRedo<int>( owner, 2 );
		_multipliers = new UndoRedoList<float>( owner );
		_naftaForKill = new UndoRedo<float>( owner, -1.0f );
		_naftaForAssist = new UndoRedo<float>( owner, -1.0f );
		_naftaSpecForKill = new UndoRedo<float>( owner, -1.0f );
		_teamNaftaForPresence = new UndoRedo<float>( owner, -1.0f );
		_neutralKillExperienceModifier = new UndoRedoDBPtr<KillExperienceModifier>( owner );
		_heroNaftaParams = new UndoRedoDBPtr<HeroNaftaParams>( owner );
		_awardSpecRange = new UndoRedo<float>( owner, 32.0f );
		_awardTeamRange = new UndoRedo<float>( owner, 25.0f );
		_giveWorldPrimeToDead.Changed += FireChangedEvent;
		_giveWorldPrimeRessurectDelay.Changed += FireChangedEvent;
		_startPrimePerTeam.Changed += FireChangedEvent;
		_giveWorldPrimeAmount.Changed += FireChangedEvent;
		_multipliers.Changed += FireChangedEvent;
		_naftaForKill.Changed += FireChangedEvent;
		_naftaForAssist.Changed += FireChangedEvent;
		_naftaSpecForKill.Changed += FireChangedEvent;
		_teamNaftaForPresence.Changed += FireChangedEvent;
		_neutralKillExperienceModifier.Changed += FireChangedEvent;
		_heroNaftaParams.Changed += FireChangedEvent;
		_awardSpecRange.Changed += FireChangedEvent;
		_awardTeamRange.Changed += FireChangedEvent;
	}

	public PrimeSettings()
	{
		Initialize( GetOwner() );
	}

	public PrimeSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PrimeSettings( DBResource owner, PrimeSettings source )
		: this(owner, source, true){}

	protected PrimeSettings( DBResource owner, PrimeSettings source, bool fireEvent )
	{
		_giveWorldPrimeToDead = new UndoRedo<bool>( owner, source.giveWorldPrimeToDead );
		_giveWorldPrimeRessurectDelay = new UndoRedo<float>( owner, source.giveWorldPrimeRessurectDelay );
		_startPrimePerTeam = new UndoRedo<int>( owner, source.startPrimePerTeam );
		_giveWorldPrimeAmount = new UndoRedo<int>( owner, source.giveWorldPrimeAmount );
		_multipliers = new UndoRedoList<float>( owner );
		_multipliers.Assign( source.multipliers );
		_naftaForKill = new UndoRedo<float>( owner, source.naftaForKill );
		_naftaForAssist = new UndoRedo<float>( owner, source.naftaForAssist );
		_naftaSpecForKill = new UndoRedo<float>( owner, source.naftaSpecForKill );
		_teamNaftaForPresence = new UndoRedo<float>( owner, source.teamNaftaForPresence );
		_neutralKillExperienceModifier = new UndoRedoDBPtr<KillExperienceModifier>( owner, source.neutralKillExperienceModifier );
		_heroNaftaParams = new UndoRedoDBPtr<HeroNaftaParams>( owner, source.heroNaftaParams );
		_awardSpecRange = new UndoRedo<float>( owner, source.awardSpecRange );
		_awardTeamRange = new UndoRedo<float>( owner, source.awardTeamRange );
		_giveWorldPrimeToDead.Changed += FireChangedEvent;
		_giveWorldPrimeRessurectDelay.Changed += FireChangedEvent;
		_startPrimePerTeam.Changed += FireChangedEvent;
		_giveWorldPrimeAmount.Changed += FireChangedEvent;
		_multipliers.Changed += FireChangedEvent;
		_naftaForKill.Changed += FireChangedEvent;
		_naftaForAssist.Changed += FireChangedEvent;
		_naftaSpecForKill.Changed += FireChangedEvent;
		_teamNaftaForPresence.Changed += FireChangedEvent;
		_neutralKillExperienceModifier.Changed += FireChangedEvent;
		_heroNaftaParams.Changed += FireChangedEvent;
		_awardSpecRange.Changed += FireChangedEvent;
		_awardTeamRange.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PrimeSettings source = _source as PrimeSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PrimeSettings" );
		giveWorldPrimeToDead = source.giveWorldPrimeToDead;
		giveWorldPrimeRessurectDelay = source.giveWorldPrimeRessurectDelay;
		startPrimePerTeam = source.startPrimePerTeam;
		giveWorldPrimeAmount = source.giveWorldPrimeAmount;
		multipliers = source.multipliers;
		naftaForKill = source.naftaForKill;
		naftaForAssist = source.naftaForAssist;
		naftaSpecForKill = source.naftaSpecForKill;
		teamNaftaForPresence = source.teamNaftaForPresence;
		neutralKillExperienceModifier = source.neutralKillExperienceModifier;
		heroNaftaParams = source.heroNaftaParams;
		awardSpecRange = source.awardSpecRange;
		awardTeamRange = source.awardTeamRange;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PrimeSettings newParent = _newParent as PrimeSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_giveWorldPrimeToDead.SetParent( newParent == null ? null : newParent._giveWorldPrimeToDead );
		_giveWorldPrimeRessurectDelay.SetParent( newParent == null ? null : newParent._giveWorldPrimeRessurectDelay );
		_startPrimePerTeam.SetParent( newParent == null ? null : newParent._startPrimePerTeam );
		_giveWorldPrimeAmount.SetParent( newParent == null ? null : newParent._giveWorldPrimeAmount );
		_multipliers.SetParent( newParent == null ? null : newParent._multipliers );
		_naftaForKill.SetParent( newParent == null ? null : newParent._naftaForKill );
		_naftaForAssist.SetParent( newParent == null ? null : newParent._naftaForAssist );
		_naftaSpecForKill.SetParent( newParent == null ? null : newParent._naftaSpecForKill );
		_teamNaftaForPresence.SetParent( newParent == null ? null : newParent._teamNaftaForPresence );
		_neutralKillExperienceModifier.SetParent( newParent == null ? null : newParent._neutralKillExperienceModifier );
		_heroNaftaParams.SetParent( newParent == null ? null : newParent._heroNaftaParams );
		_awardSpecRange.SetParent( newParent == null ? null : newParent._awardSpecRange );
		_awardTeamRange.SetParent( newParent == null ? null : newParent._awardTeamRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_giveWorldPrimeToDead.Reset();
		_giveWorldPrimeRessurectDelay.Reset();
		_startPrimePerTeam.Reset();
		_giveWorldPrimeAmount.Reset();
		_multipliers.Reset();
		_naftaForKill.Reset();
		_naftaForAssist.Reset();
		_naftaSpecForKill.Reset();
		_teamNaftaForPresence.Reset();
		_neutralKillExperienceModifier.Reset();
		_heroNaftaParams.Reset();
		_awardSpecRange.Reset();
		_awardTeamRange.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_giveWorldPrimeToDead.IsDerivedFromParent()
			&& _giveWorldPrimeRessurectDelay.IsDerivedFromParent()
			&& _startPrimePerTeam.IsDerivedFromParent()
			&& _giveWorldPrimeAmount.IsDerivedFromParent()
			&& _multipliers.IsDerivedFromParent()
			&& _naftaForKill.IsDerivedFromParent()
			&& _naftaForAssist.IsDerivedFromParent()
			&& _naftaSpecForKill.IsDerivedFromParent()
			&& _teamNaftaForPresence.IsDerivedFromParent()
			&& _neutralKillExperienceModifier.IsDerivedFromParent()
			&& _heroNaftaParams.IsDerivedFromParent()
			&& _awardSpecRange.IsDerivedFromParent()
			&& _awardTeamRange.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "giveWorldPrimeToDead" )
			_giveWorldPrimeToDead.Reset();
		else if ( fieldName == "giveWorldPrimeRessurectDelay" )
			_giveWorldPrimeRessurectDelay.Reset();
		else if ( fieldName == "startPrimePerTeam" )
			_startPrimePerTeam.Reset();
		else if ( fieldName == "giveWorldPrimeAmount" )
			_giveWorldPrimeAmount.Reset();
		else if ( fieldName == "multipliers" )
			_multipliers.Reset();
		else if ( fieldName == "naftaForKill" )
			_naftaForKill.Reset();
		else if ( fieldName == "naftaForAssist" )
			_naftaForAssist.Reset();
		else if ( fieldName == "naftaSpecForKill" )
			_naftaSpecForKill.Reset();
		else if ( fieldName == "teamNaftaForPresence" )
			_teamNaftaForPresence.Reset();
		else if ( fieldName == "neutralKillExperienceModifier" )
			_neutralKillExperienceModifier.Reset();
		else if ( fieldName == "heroNaftaParams" )
			_heroNaftaParams.Reset();
		else if ( fieldName == "awardSpecRange" )
			_awardSpecRange.Reset();
		else if ( fieldName == "awardTeamRange" )
			_awardTeamRange.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "giveWorldPrimeToDead" )
			return _giveWorldPrimeToDead.IsDerivedFromParent();
		if ( fieldName == "giveWorldPrimeRessurectDelay" )
			return _giveWorldPrimeRessurectDelay.IsDerivedFromParent();
		if ( fieldName == "startPrimePerTeam" )
			return _startPrimePerTeam.IsDerivedFromParent();
		if ( fieldName == "giveWorldPrimeAmount" )
			return _giveWorldPrimeAmount.IsDerivedFromParent();
		if ( fieldName == "multipliers" )
			return _multipliers.IsDerivedFromParent();
		if ( fieldName == "naftaForKill" )
			return _naftaForKill.IsDerivedFromParent();
		if ( fieldName == "naftaForAssist" )
			return _naftaForAssist.IsDerivedFromParent();
		if ( fieldName == "naftaSpecForKill" )
			return _naftaSpecForKill.IsDerivedFromParent();
		if ( fieldName == "teamNaftaForPresence" )
			return _teamNaftaForPresence.IsDerivedFromParent();
		if ( fieldName == "neutralKillExperienceModifier" )
			return _neutralKillExperienceModifier.IsDerivedFromParent();
		if ( fieldName == "heroNaftaParams" )
			return _heroNaftaParams.IsDerivedFromParent();
		if ( fieldName == "awardSpecRange" )
			return _awardSpecRange.IsDerivedFromParent();
		if ( fieldName == "awardTeamRange" )
			return _awardTeamRange.IsDerivedFromParent();
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

[IndexField("key")]
public class ResourceDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ResourceDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _key;
	private UndoRedoDBPtr<DBResource> _resource;

	public string key { get { return _key.Get(); } set { _key.Set( value ); } }

	public DBPtr<DBResource> resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_key = new UndoRedo<string>( owner, string.Empty );
		_resource = new UndoRedoDBPtr<DBResource>( owner );
		_key.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
	}

	public ResourceDesc()
	{
		Initialize( GetOwner() );
	}

	public ResourceDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ResourceDesc( DBResource owner, ResourceDesc source )
		: this(owner, source, true){}

	protected ResourceDesc( DBResource owner, ResourceDesc source, bool fireEvent )
	{
		_key = new UndoRedo<string>( owner, source.key );
		_resource = new UndoRedoDBPtr<DBResource>( owner, source.resource );
		_key.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ResourceDesc source = _source as ResourceDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceDesc" );
		key = source.key;
		resource = source.resource;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ResourceDesc newParent = _newParent as ResourceDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_key.SetParent( newParent == null ? null : newParent._key );
		_resource.SetParent( newParent == null ? null : newParent._resource );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_key.Reset();
		_resource.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_key.IsDerivedFromParent()
			&& _resource.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "key" )
			_key.Reset();
		else if ( fieldName == "resource" )
			_resource.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "key" )
			return _key.IsDerivedFromParent();
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
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

public class ScriptArea : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ScriptArea __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private Vec2 _position;
	private UndoRedo<float> _radius;
	private UndoRedo<ESpellTarget> _targetType;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public Vec2 position { get { return _position; } set { _position.Assign( value ); } }

	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	public ESpellTarget targetType { get { return _targetType.Get(); } set { _targetType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_position = new Vec2( owner );
		_radius = new UndoRedo<float>( owner, 10.0f );
		_targetType = new UndoRedo<ESpellTarget>( owner, ESpellTarget.All );
		_name.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_targetType.Changed += FireChangedEvent;
	}

	public ScriptArea()
	{
		Initialize( GetOwner() );
	}

	public ScriptArea( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ScriptArea( DBResource owner, ScriptArea source )
		: this(owner, source, true){}

	protected ScriptArea( DBResource owner, ScriptArea source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_position = new Vec2( owner, source.position );
		_radius = new UndoRedo<float>( owner, source.radius );
		_targetType = new UndoRedo<ESpellTarget>( owner, source.targetType );
		_name.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_targetType.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ScriptArea source = _source as ScriptArea;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptArea" );
		name = source.name;
		position = source.position;
		radius = source.radius;
		targetType = source.targetType;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ScriptArea newParent = _newParent as ScriptArea;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_position.SetParent( newParent == null ? null : newParent._position );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_targetType.SetParent( newParent == null ? null : newParent._targetType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_position.Reset();
		_radius.Reset();
		_targetType.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _targetType.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "targetType" )
			_targetType.Reset();
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
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "targetType" )
			return _targetType.IsDerivedFromParent();
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

public class ScriptPolygonAreaPolygon : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ScriptPolygonAreaPolygon __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private Color _color;
	private UndoRedoList<int> _indexes;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[NoCode]
	public Color color { get { return _color; } set { _color.Assign( value ); } }

	public libdb.IChangeableList<int> indexes { get { return _indexes; } set { _indexes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		Color __color = new Color(); // Construct default object for color
		__color.G = 192;
		__color.A = 0;
		_color = new Color( owner, __color );
		_indexes = new UndoRedoList<int>( owner );
		_name.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_indexes.Changed += FireChangedEvent;
	}

	public ScriptPolygonAreaPolygon()
	{
		Initialize( GetOwner() );
	}

	public ScriptPolygonAreaPolygon( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ScriptPolygonAreaPolygon( DBResource owner, ScriptPolygonAreaPolygon source )
		: this(owner, source, true){}

	protected ScriptPolygonAreaPolygon( DBResource owner, ScriptPolygonAreaPolygon source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_color = new Color( owner, source.color );
		_indexes = new UndoRedoList<int>( owner );
		_indexes.Assign( source.indexes );
		_name.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_indexes.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ScriptPolygonAreaPolygon source = _source as ScriptPolygonAreaPolygon;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptPolygonAreaPolygon" );
		name = source.name;
		color = source.color;
		indexes = source.indexes;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ScriptPolygonAreaPolygon newParent = _newParent as ScriptPolygonAreaPolygon;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_color.SetParent( newParent == null ? null : newParent._color );
		_indexes.SetParent( newParent == null ? null : newParent._indexes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_color.Reset();
		_indexes.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _color.IsDerivedFromParent()
			&& _indexes.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "color" )
			_color.Reset();
		else if ( fieldName == "indexes" )
			_indexes.Reset();
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
		if ( fieldName == "color" )
			return _color.IsDerivedFromParent();
		if ( fieldName == "indexes" )
			return _indexes.IsDerivedFromParent();
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

public class StatisticBackgoundImages : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatisticBackgoundImages __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Texture> _normal;
	private UndoRedoDBPtr<Texture> _win;
	private UndoRedoDBPtr<Texture> _loose;

	[Description( "бэк текущей статистики. Во время боя" )]
	public DBPtr<Texture> normal { get { return _normal.Get(); } set { _normal.Set( value ); } }

	[Description( "бэк текущей статистики. Победа" )]
	public DBPtr<Texture> win { get { return _win.Get(); } set { _win.Set( value ); } }

	[Description( "бэк текущей статистики. Поражение" )]
	public DBPtr<Texture> loose { get { return _loose.Get(); } set { _loose.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_normal = new UndoRedoDBPtr<Texture>( owner );
		_win = new UndoRedoDBPtr<Texture>( owner );
		_loose = new UndoRedoDBPtr<Texture>( owner );
		_normal.Changed += FireChangedEvent;
		_win.Changed += FireChangedEvent;
		_loose.Changed += FireChangedEvent;
	}

	public StatisticBackgoundImages()
	{
		Initialize( GetOwner() );
	}

	public StatisticBackgoundImages( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatisticBackgoundImages( DBResource owner, StatisticBackgoundImages source )
		: this(owner, source, true){}

	protected StatisticBackgoundImages( DBResource owner, StatisticBackgoundImages source, bool fireEvent )
	{
		_normal = new UndoRedoDBPtr<Texture>( owner, source.normal );
		_win = new UndoRedoDBPtr<Texture>( owner, source.win );
		_loose = new UndoRedoDBPtr<Texture>( owner, source.loose );
		_normal.Changed += FireChangedEvent;
		_win.Changed += FireChangedEvent;
		_loose.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatisticBackgoundImages source = _source as StatisticBackgoundImages;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatisticBackgoundImages" );
		normal = source.normal;
		win = source.win;
		loose = source.loose;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatisticBackgoundImages newParent = _newParent as StatisticBackgoundImages;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_normal.SetParent( newParent == null ? null : newParent._normal );
		_win.SetParent( newParent == null ? null : newParent._win );
		_loose.SetParent( newParent == null ? null : newParent._loose );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_normal.Reset();
		_win.Reset();
		_loose.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_normal.IsDerivedFromParent()
			&& _win.IsDerivedFromParent()
			&& _loose.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "normal" )
			_normal.Reset();
		else if ( fieldName == "win" )
			_win.Reset();
		else if ( fieldName == "loose" )
			_loose.Reset();
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
		if ( fieldName == "win" )
			return _win.IsDerivedFromParent();
		if ( fieldName == "loose" )
			return _loose.IsDerivedFromParent();
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

public class TriggerMarkerBinding : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TriggerMarkerBinding __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _TriggerPoint;
	private UndoRedoList<string> _MarkerPoints;

	public string TriggerPoint { get { return _TriggerPoint.Get(); } set { _TriggerPoint.Set( value ); } }

	public libdb.IChangeableList<string> MarkerPoints { get { return _MarkerPoints; } set { _MarkerPoints.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_TriggerPoint = new UndoRedo<string>( owner, string.Empty );
		_MarkerPoints = new UndoRedoList<string>( owner );
		_TriggerPoint.Changed += FireChangedEvent;
		_MarkerPoints.Changed += FireChangedEvent;
	}

	public TriggerMarkerBinding()
	{
		Initialize( GetOwner() );
	}

	public TriggerMarkerBinding( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TriggerMarkerBinding( DBResource owner, TriggerMarkerBinding source )
		: this(owner, source, true){}

	protected TriggerMarkerBinding( DBResource owner, TriggerMarkerBinding source, bool fireEvent )
	{
		_TriggerPoint = new UndoRedo<string>( owner, source.TriggerPoint );
		_MarkerPoints = new UndoRedoList<string>( owner );
		_MarkerPoints.Assign( source.MarkerPoints );
		_TriggerPoint.Changed += FireChangedEvent;
		_MarkerPoints.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TriggerMarkerBinding source = _source as TriggerMarkerBinding;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TriggerMarkerBinding" );
		TriggerPoint = source.TriggerPoint;
		MarkerPoints = source.MarkerPoints;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TriggerMarkerBinding newParent = _newParent as TriggerMarkerBinding;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_TriggerPoint.SetParent( newParent == null ? null : newParent._TriggerPoint );
		_MarkerPoints.SetParent( newParent == null ? null : newParent._MarkerPoints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_TriggerPoint.Reset();
		_MarkerPoints.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_TriggerPoint.IsDerivedFromParent()
			&& _MarkerPoints.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "TriggerPoint" )
			_TriggerPoint.Reset();
		else if ( fieldName == "MarkerPoints" )
			_MarkerPoints.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "TriggerPoint" )
			return _TriggerPoint.IsDerivedFromParent();
		if ( fieldName == "MarkerPoints" )
			return _MarkerPoints.IsDerivedFromParent();
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
[UseTypeName("ADMP")]
public class AdvMap : DBResource
{
	private UndoRedoDBPtr<AdvMap> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMap> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AdventureCameraSettings> _cameraSettings;
	private UndoRedoDBPtr<MinimapImages> _minimapImages;
	private UndoRedoAssignableList<AdvMapObject> _objects;
	private UndoRedoDBPtr<Terrain> _terrain;
	private UndoRedoDBPtr<SoundEnvironment> _soundEnvironment;
	private UndoRedoDBPtr<LightEnvironment> _lightEnvironment;
	private UndoRedoDBPtr<LightEnvironment> _nightLightEnvironment;
	private BakedLighting _bakedLighting;
	private UndoRedoAssignableList<PointLightInfo> _pointLights;
	private UndoRedoAssignableList<ScriptArea> _scriptAreas;
	private SoundAmbienceMap _ambienceMap;
	private UndoRedoDBPtr<AdvMapSettings> _mapSettings;
	private UndoRedoDBPtr<PostFXParams> _postEffect;
	private DayNightSettings _dayNightSettings;

	public DBPtr<AdventureCameraSettings> cameraSettings { get { return _cameraSettings.Get(); } set { _cameraSettings.Set( value ); } }

	public DBPtr<MinimapImages> minimapImages { get { return _minimapImages.Get(); } set { _minimapImages.Set( value ); } }

	public libdb.IChangeableList<AdvMapObject> objects { get { return _objects; } set { _objects.Assign( value ); } }

	public DBPtr<Terrain> terrain { get { return _terrain.Get(); } set { _terrain.Set( value ); } }

	public DBPtr<SoundEnvironment> soundEnvironment { get { return _soundEnvironment.Get(); } set { _soundEnvironment.Set( value ); } }

	public DBPtr<LightEnvironment> lightEnvironment { get { return _lightEnvironment.Get(); } set { _lightEnvironment.Set( value ); } }

	public DBPtr<LightEnvironment> nightLightEnvironment { get { return _nightLightEnvironment.Get(); } set { _nightLightEnvironment.Set( value ); } }

	public BakedLighting bakedLighting { get { return _bakedLighting; } set { _bakedLighting.Assign( value ); } }

	public libdb.IChangeableList<PointLightInfo> pointLights { get { return _pointLights; } set { _pointLights.Assign( value ); } }

	public libdb.IChangeableList<ScriptArea> scriptAreas { get { return _scriptAreas; } set { _scriptAreas.Assign( value ); } }

	[Category( "Objects height layer" )]
	[DstFile("objectheight")]
	public string ObjectsLayerFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "objectheight"
	); } }
	[DstFile("watermap")]
	public string waterMapFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "watermap"
	); } }
	[Description( "Настройки звуков окружения на игровой карте с помощью текстуры." )]
	public SoundAmbienceMap ambienceMap { get { return _ambienceMap; } set { _ambienceMap.Assign( value ); } }

	[Description( "Map settings" )]
	public DBPtr<AdvMapSettings> mapSettings { get { return _mapSettings.Get(); } set { _mapSettings.Set( value ); } }

	[Description( "Override full-screen post effect" )]
	public DBPtr<PostFXParams> postEffect { get { return _postEffect.Get(); } set { _postEffect.Set( value ); } }

	public DayNightSettings dayNightSettings { get { return _dayNightSettings; } set { _dayNightSettings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMap>(owner);
		_cameraSettings = new UndoRedoDBPtr<AdventureCameraSettings>( owner );
		_minimapImages = new UndoRedoDBPtr<MinimapImages>( owner );
		_objects = new UndoRedoAssignableList<AdvMapObject>( owner );
		_terrain = new UndoRedoDBPtr<Terrain>( owner );
		_soundEnvironment = new UndoRedoDBPtr<SoundEnvironment>( owner );
		_lightEnvironment = new UndoRedoDBPtr<LightEnvironment>( owner );
		_nightLightEnvironment = new UndoRedoDBPtr<LightEnvironment>( owner );
		_bakedLighting = new BakedLighting( owner );
		_pointLights = new UndoRedoAssignableList<PointLightInfo>( owner );
		_scriptAreas = new UndoRedoAssignableList<ScriptArea>( owner );
		_ambienceMap = new SoundAmbienceMap( owner );
		_mapSettings = new UndoRedoDBPtr<AdvMapSettings>( owner );
		_postEffect = new UndoRedoDBPtr<PostFXParams>( owner );
		_dayNightSettings = new DayNightSettings( owner );
		___parent.Changed += FireChangedEvent;
		_cameraSettings.Changed += FireChangedEvent;
		_minimapImages.Changed += FireChangedEvent;
		_objects.Changed += FireChangedEvent;
		_terrain.Changed += FireChangedEvent;
		_soundEnvironment.Changed += FireChangedEvent;
		_lightEnvironment.Changed += FireChangedEvent;
		_nightLightEnvironment.Changed += FireChangedEvent;
		_bakedLighting.Changed += FireChangedEvent;
		_pointLights.Changed += FireChangedEvent;
		_scriptAreas.Changed += FireChangedEvent;
		_ambienceMap.Changed += FireChangedEvent;
		_mapSettings.Changed += FireChangedEvent;
		_postEffect.Changed += FireChangedEvent;
		_dayNightSettings.Changed += FireChangedEvent;
	}

	public AdvMap()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMap source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMap" );
		cameraSettings = source.cameraSettings;
		minimapImages = source.minimapImages;
		objects = source.objects;
		terrain = source.terrain;
		soundEnvironment = source.soundEnvironment;
		lightEnvironment = source.lightEnvironment;
		nightLightEnvironment = source.nightLightEnvironment;
		bakedLighting = source.bakedLighting;
		pointLights = source.pointLights;
		scriptAreas = source.scriptAreas;
		ambienceMap = source.ambienceMap;
		mapSettings = source.mapSettings;
		postEffect = source.postEffect;
		dayNightSettings = source.dayNightSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMap source = _source as AdvMap;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMap" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMap newParent = rawParent == null ? null : rawParent.Get<AdvMap>();
		if ( newParent == null && _newParent is AdvMap )
			newParent = _newParent as AdvMap;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cameraSettings.SetParent( newParent == null ? null : newParent._cameraSettings );
		_minimapImages.SetParent( newParent == null ? null : newParent._minimapImages );
		_objects.SetParent( newParent == null ? null : newParent._objects );
		_terrain.SetParent( newParent == null ? null : newParent._terrain );
		_soundEnvironment.SetParent( newParent == null ? null : newParent._soundEnvironment );
		_lightEnvironment.SetParent( newParent == null ? null : newParent._lightEnvironment );
		_nightLightEnvironment.SetParent( newParent == null ? null : newParent._nightLightEnvironment );
		_bakedLighting.SetParent( newParent == null ? null : newParent._bakedLighting );
		_pointLights.SetParent( newParent == null ? null : newParent._pointLights );
		_scriptAreas.SetParent( newParent == null ? null : newParent._scriptAreas );
		_ambienceMap.SetParent( newParent == null ? null : newParent._ambienceMap );
		_mapSettings.SetParent( newParent == null ? null : newParent._mapSettings );
		_postEffect.SetParent( newParent == null ? null : newParent._postEffect );
		_dayNightSettings.SetParent( newParent == null ? null : newParent._dayNightSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cameraSettings.Reset();
		_minimapImages.Reset();
		_objects.Reset();
		_terrain.Reset();
		_soundEnvironment.Reset();
		_lightEnvironment.Reset();
		_nightLightEnvironment.Reset();
		_bakedLighting.Reset();
		_pointLights.Reset();
		_scriptAreas.Reset();
		_ambienceMap.Reset();
		_mapSettings.Reset();
		_postEffect.Reset();
		_dayNightSettings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cameraSettings.IsDerivedFromParent()
			&& _minimapImages.IsDerivedFromParent()
			&& _objects.IsDerivedFromParent()
			&& _terrain.IsDerivedFromParent()
			&& _soundEnvironment.IsDerivedFromParent()
			&& _lightEnvironment.IsDerivedFromParent()
			&& _nightLightEnvironment.IsDerivedFromParent()
			&& _bakedLighting.IsDerivedFromParent()
			&& _pointLights.IsDerivedFromParent()
			&& _scriptAreas.IsDerivedFromParent()
			&& _ambienceMap.IsDerivedFromParent()
			&& _mapSettings.IsDerivedFromParent()
			&& _postEffect.IsDerivedFromParent()
			&& _dayNightSettings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cameraSettings" )
			_cameraSettings.Reset();
		else if ( fieldName == "minimapImages" )
			_minimapImages.Reset();
		else if ( fieldName == "objects" )
			_objects.Reset();
		else if ( fieldName == "terrain" )
			_terrain.Reset();
		else if ( fieldName == "soundEnvironment" )
			_soundEnvironment.Reset();
		else if ( fieldName == "lightEnvironment" )
			_lightEnvironment.Reset();
		else if ( fieldName == "nightLightEnvironment" )
			_nightLightEnvironment.Reset();
		else if ( fieldName == "bakedLighting" )
			_bakedLighting.Reset();
		else if ( fieldName == "pointLights" )
			_pointLights.Reset();
		else if ( fieldName == "scriptAreas" )
			_scriptAreas.Reset();
		else if ( fieldName == "ambienceMap" )
			_ambienceMap.Reset();
		else if ( fieldName == "mapSettings" )
			_mapSettings.Reset();
		else if ( fieldName == "postEffect" )
			_postEffect.Reset();
		else if ( fieldName == "dayNightSettings" )
			_dayNightSettings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cameraSettings" )
			return _cameraSettings.IsDerivedFromParent();
		if ( fieldName == "minimapImages" )
			return _minimapImages.IsDerivedFromParent();
		if ( fieldName == "objects" )
			return _objects.IsDerivedFromParent();
		if ( fieldName == "terrain" )
			return _terrain.IsDerivedFromParent();
		if ( fieldName == "soundEnvironment" )
			return _soundEnvironment.IsDerivedFromParent();
		if ( fieldName == "lightEnvironment" )
			return _lightEnvironment.IsDerivedFromParent();
		if ( fieldName == "nightLightEnvironment" )
			return _nightLightEnvironment.IsDerivedFromParent();
		if ( fieldName == "bakedLighting" )
			return _bakedLighting.IsDerivedFromParent();
		if ( fieldName == "pointLights" )
			return _pointLights.IsDerivedFromParent();
		if ( fieldName == "scriptAreas" )
			return _scriptAreas.IsDerivedFromParent();
		if ( fieldName == "ambienceMap" )
			return _ambienceMap.IsDerivedFromParent();
		if ( fieldName == "mapSettings" )
			return _mapSettings.IsDerivedFromParent();
		if ( fieldName == "postEffect" )
			return _postEffect.IsDerivedFromParent();
		if ( fieldName == "dayNightSettings" )
			return _dayNightSettings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xEF924380)]
[UseTypeName("CSPL")]
public class AdvMapCameraSpline : GameObject
{
	private UndoRedoDBPtr<AdvMapCameraSpline> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapCameraSpline> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Spline3DControlPointDesc> _points;
	private UndoRedo<int> _hight;
	private UndoRedo<bool> _SmoothStart;
	private UndoRedo<float> _StartTime;
	private UndoRedo<bool> _SmoothEnd;
	private UndoRedo<float> _EndTime;

	public libdb.IChangeableList<Spline3DControlPointDesc> points { get { return _points; } set { _points.Assign( value ); } }

	public int hight { get { return _hight.Get(); } set { _hight.Set( value ); } }

	public bool SmoothStart { get { return _SmoothStart.Get(); } set { _SmoothStart.Set( value ); } }

	public float StartTime { get { return _StartTime.Get(); } set { _StartTime.Set( value ); } }

	public bool SmoothEnd { get { return _SmoothEnd.Get(); } set { _SmoothEnd.Set( value ); } }

	public float EndTime { get { return _EndTime.Get(); } set { _EndTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapCameraSpline>(owner);
		_points = new UndoRedoAssignableList<Spline3DControlPointDesc>( owner );
		_hight = new UndoRedo<int>( owner, 5 );
		_SmoothStart = new UndoRedo<bool>( owner, false );
		_StartTime = new UndoRedo<float>( owner, 1.0f );
		_SmoothEnd = new UndoRedo<bool>( owner, false );
		_EndTime = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		_hight.Changed += FireChangedEvent;
		_SmoothStart.Changed += FireChangedEvent;
		_StartTime.Changed += FireChangedEvent;
		_SmoothEnd.Changed += FireChangedEvent;
		_EndTime.Changed += FireChangedEvent;
	}

	public AdvMapCameraSpline()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapCameraSpline source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCameraSpline" );
		points = source.points;
		hight = source.hight;
		SmoothStart = source.SmoothStart;
		StartTime = source.StartTime;
		SmoothEnd = source.SmoothEnd;
		EndTime = source.EndTime;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapCameraSpline source = _source as AdvMapCameraSpline;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapCameraSpline" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapCameraSpline newParent = rawParent == null ? null : rawParent.Get<AdvMapCameraSpline>();
		if ( newParent == null && _newParent is AdvMapCameraSpline )
			newParent = _newParent as AdvMapCameraSpline;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_points.SetParent( newParent == null ? null : newParent._points );
		_hight.SetParent( newParent == null ? null : newParent._hight );
		_SmoothStart.SetParent( newParent == null ? null : newParent._SmoothStart );
		_StartTime.SetParent( newParent == null ? null : newParent._StartTime );
		_SmoothEnd.SetParent( newParent == null ? null : newParent._SmoothEnd );
		_EndTime.SetParent( newParent == null ? null : newParent._EndTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_points.Reset();
		_hight.Reset();
		_SmoothStart.Reset();
		_StartTime.Reset();
		_SmoothEnd.Reset();
		_EndTime.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_points.IsDerivedFromParent()
			&& _hight.IsDerivedFromParent()
			&& _SmoothStart.IsDerivedFromParent()
			&& _StartTime.IsDerivedFromParent()
			&& _SmoothEnd.IsDerivedFromParent()
			&& _EndTime.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "points" )
			_points.Reset();
		else if ( fieldName == "hight" )
			_hight.Reset();
		else if ( fieldName == "SmoothStart" )
			_SmoothStart.Reset();
		else if ( fieldName == "StartTime" )
			_StartTime.Reset();
		else if ( fieldName == "SmoothEnd" )
			_SmoothEnd.Reset();
		else if ( fieldName == "EndTime" )
			_EndTime.Reset();
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
		if ( fieldName == "hight" )
			return _hight.IsDerivedFromParent();
		if ( fieldName == "SmoothStart" )
			return _SmoothStart.IsDerivedFromParent();
		if ( fieldName == "StartTime" )
			return _StartTime.IsDerivedFromParent();
		if ( fieldName == "SmoothEnd" )
			return _SmoothEnd.IsDerivedFromParent();
		if ( fieldName == "EndTime" )
			return _EndTime.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("title")]
[UseTypeName("ADMPDSCR")]
public class AdvMapDescription : DBResource
{
	private UndoRedoDBPtr<AdvMapDescription> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapDescription> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _title;
	private LoadingBackgroundImages _loadingBackgroundImages;
	private StatisticBackgoundImages _statisticBackgroundImages;
	private UndoRedoDBPtr<AdvMapModeDescription> _modeVisualDescription;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedo<EMapType> _mapType;
	private UndoRedoDBPtr<AdvMapDescription> _mapWithBots;
	private UndoRedo<PartyMode> _PartyMode;
	private UndoRedo<bool> _acceptNeeded;
	private TextRef _description;
	private UndoRedoDBPtr<AdvMap> _map;
	private UndoRedoDBPtr<AdvMapHeroesOverride> _heroesOverride;
	private UndoRedoDBPtr<MapMMakingSettings> _matchmakingSettings;
	private UndoRedo<int> _teamSize;
	private UndoRedo<int> _minTeamSize;
	private UndoRedo<int> _maxUncompleteTeamSize;
	private UndoRedo<bool> _productionMode;
	private UndoRedoDBPtr<AdvMapSettings> _mapSettings;
	private UndoRedoDBPtr<ModeRollSettings> _rollSettings;
	private UndoRedoDBPtr<ModeRollSettings> _guardRollSettings;
	private UndoRedoDBPtr<ScoringTable> _scoringTable;
	private UndoRedo<float> _victoryPoint;
	private UndoRedo<string> _FWODGroup;
	private UndoRedoDBPtr<FWODVisualInfo> _FirstWinVisualInfo;
	private UndoRedo<bool> _canUseSkins;
	private UndoRedo<bool> _botsUseSkins;
	private UndoRedo<int> _minimalGuildFightTeam;
	private UndoRedoDBPtr<GameSvcSettings> _gameSvcSettings;
	private UndoRedo<int> _playSameTeamTimeOut;
	private UndoRedo<bool> _AvailableForLeavers;
	private UndoRedo<bool> _PlusPointForLeave;
	private UndoRedo<bool> _MinusPointsPerFullGame;

	[Category( "Map title" )]
	[Custom("Social")]
	[Description( "Имя карты" )]
	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	[Description( "Картики на экране загрузки. Логотип и Бэк" )]
	public LoadingBackgroundImages loadingBackgroundImages { get { return _loadingBackgroundImages; } set { _loadingBackgroundImages.Assign( value ); } }

	[Description( "Картики текущей статистики. Показывается когда нету одной из комманд. Пока используется в кооперативе" )]
	public StatisticBackgoundImages statisticBackgroundImages { get { return _statisticBackgroundImages; } set { _statisticBackgroundImages.Assign( value ); } }

	[Description( "Описание модификатора. Родная земля/Форпост итд" )]
	public DBPtr<AdvMapModeDescription> modeVisualDescription { get { return _modeVisualDescription.Get(); } set { _modeVisualDescription.Set( value ); } }

	[Custom("Social")]
	[Description( "Иконка карты для отображения" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Category( "MapType" )]
	[Custom("DBServer", "Social")]
	[Description( "Тип карты, важно серверу. На основе этого поле выбирается алгоритм матчмейкинга: PVP, PVE, single-player etc" )]
	public EMapType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("Social")]
	[Description( "Карта для режима Практики" )]
	public DBPtr<AdvMapDescription> mapWithBots { get { return _mapWithBots.Get(); } set { _mapWithBots.Set( value ); } }

	[Custom("Social")]
	[Description( "Настройки для группы. NotAllowed - нельзя группой, OnlyAllies - только с напарниками, AlliesAndEnemies - напарники и соперники (ДБ)" )]
	public PartyMode PartyMode { get { return _PartyMode.Get(); } set { _PartyMode.Set( value ); } }

	[Custom("Social")]
	[Description( "Надо ли запрашивать accept на нахождение игры. По умолчанию - отключено" )]
	public bool acceptNeeded { get { return _acceptNeeded.Get(); } set { _acceptNeeded.Set( value ); } }

	[Category( "Map description" )]
	[Custom("Social")]
	[Description( "тултип для карты" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public DBPtr<AdvMap> map { get { return _map.Get(); } set { _map.Set( value ); } }

	[Custom("Social")]
	[Description( "Optional heroes override data" )]
	public DBPtr<AdvMapHeroesOverride> heroesOverride { get { return _heroesOverride.Get(); } set { _heroesOverride.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Настройки матчмейкинга, специфичные для карты; Если не указаны, то на этой карте включится тестовый матчмейкинг!" )]
	public DBPtr<MapMMakingSettings> matchmakingSettings { get { return _matchmakingSettings.Get(); } set { _matchmakingSettings.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Число игроков за одну сторону, например, 5" )]
	public int teamSize { get { return _teamSize.Get(); } set { _teamSize.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "необходимое количество игроков для карты. Нужно для кооператива. по дефолту -1" )]
	public int minTeamSize { get { return _minTeamSize.Get(); } set { _minTeamSize.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "максимальный размер неполной парти на карте. если оставить -1 будет совпадать с максимальным количеством игроков за одну сторону" )]
	public int maxUncompleteTeamSize { get { return _maxUncompleteTeamSize.Get(); } set { _maxUncompleteTeamSize.Set( value ); } }

	[Custom("DBServer")]
	[Description( "Допустим ли такой режим/карта на боевом сервере" )]
	public bool productionMode { get { return _productionMode.Get(); } set { _productionMode.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Map settings" )]
	public DBPtr<AdvMapSettings> mapSettings { get { return _mapSettings.Get(); } set { _mapSettings.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Roll settings" )]
	public DBPtr<ModeRollSettings> rollSettings { get { return _rollSettings.Get(); } set { _rollSettings.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Guard Mode roll settings" )]
	public DBPtr<ModeRollSettings> guardRollSettings { get { return _guardRollSettings.Get(); } set { _guardRollSettings.Set( value ); } }

	[Description( "Scoring table (leave empty to use default scoring)" )]
	public DBPtr<ScoringTable> scoringTable { get { return _scoringTable.Get(); } set { _scoringTable.Set( value ); } }

	[Custom("Social")]
	[Description( "Вес победы. Те кол-во очков победы, которое дается за победу. Например для Форпоста=0.5, для Пограничья=1.0" )]
	public float victoryPoint { get { return _victoryPoint.Get(); } set { _victoryPoint.Set( value ); } }

	[Custom("Social")]
	[Description( "Группа для первого выигрыша за день. Если бонус не положен - пустая строка. Чтобы был бонус один для нескольких карт (например драговальд и пограничье), строка должна совпадать" )]
	public string FWODGroup { get { return _FWODGroup.Get(); } set { _FWODGroup.Set( value ); } }

	[Custom("Social")]
	[Description( "Информация для отображение FWOD в сессии и замке. Устанавливается на карту" )]
	public DBPtr<FWODVisualInfo> FirstWinVisualInfo { get { return _FirstWinVisualInfo.Get(); } set { _FirstWinVisualInfo.Set( value ); } }

	[Custom("Social")]
	[Description( "Можно ли использовать на этой карте скины героев" )]
	public bool canUseSkins { get { return _canUseSkins.Get(); } set { _canUseSkins.Set( value ); } }

	[Custom("Social")]
	[Description( "Доступны ли ботам скины на этой карте" )]
	public bool botsUseSkins { get { return _botsUseSkins.Get(); } set { _botsUseSkins.Set( value ); } }

	[Custom("DBServer")]
	[Description( "Количество игроков с одной стороны из одного клана, чтобы  бой получил статус клановый" )]
	public int minimalGuildFightTeam { get { return _minimalGuildFightTeam.Get(); } set { _minimalGuildFightTeam.Set( value ); } }

	[Custom("DBServer")]
	[Description( "Map-specific game server settings" )]
	public DBPtr<GameSvcSettings> gameSvcSettings { get { return _gameSvcSettings.Get(); } set { _gameSvcSettings.Set( value ); } }

	[Custom("DBServer")]
	[Description( "Тайм-аут для фичи Играть в том же составе. Если 0, опция блокируется." )]
	public int playSameTeamTimeOut { get { return _playSameTeamTimeOut.Get(); } set { _playSameTeamTimeOut.Set( value ); } }

	[Custom("Social")]
	[Description( "Доступна ли карта для игры ливерам (True-доступна,False-недоступна)" )]
	public bool AvailableForLeavers { get { return _AvailableForLeavers.Get(); } set { _AvailableForLeavers.Set( value ); } }

	[Custom("Social")]
	[Description( "Будут ли даваться очки дезертира за покинутую игру на этой карте  (True-будут,False-небудут)" )]
	public bool PlusPointForLeave { get { return _PlusPointForLeave.Get(); } set { _PlusPointForLeave.Set( value ); } }

	[Custom("Social")]
	[Description( "Будут ли сниматься очки дезертира за сыгранную игру до конца на этой карте (True-будут,False-небудут)" )]
	public bool MinusPointsPerFullGame { get { return _MinusPointsPerFullGame.Get(); } set { _MinusPointsPerFullGame.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapDescription>(owner);
		_title = new TextRef( owner, new TextRef() );
		_loadingBackgroundImages = new LoadingBackgroundImages( owner );
		_statisticBackgroundImages = new StatisticBackgoundImages( owner );
		_modeVisualDescription = new UndoRedoDBPtr<AdvMapModeDescription>( owner );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_mapType = new UndoRedo<EMapType>( owner, EMapType.PvP );
		_mapWithBots = new UndoRedoDBPtr<AdvMapDescription>( owner );
		_PartyMode = new UndoRedo<PartyMode>( owner, PartyMode.AlliesAndEnemies );
		_acceptNeeded = new UndoRedo<bool>( owner, false );
		_description = new TextRef( owner, new TextRef() );
		_map = new UndoRedoDBPtr<AdvMap>( owner );
		_heroesOverride = new UndoRedoDBPtr<AdvMapHeroesOverride>( owner );
		_matchmakingSettings = new UndoRedoDBPtr<MapMMakingSettings>( owner );
		_teamSize = new UndoRedo<int>( owner, 5 );
		_minTeamSize = new UndoRedo<int>( owner, -1 );
		_maxUncompleteTeamSize = new UndoRedo<int>( owner, -1 );
		_productionMode = new UndoRedo<bool>( owner, false );
		_mapSettings = new UndoRedoDBPtr<AdvMapSettings>( owner );
		_rollSettings = new UndoRedoDBPtr<ModeRollSettings>( owner );
		_guardRollSettings = new UndoRedoDBPtr<ModeRollSettings>( owner );
		_scoringTable = new UndoRedoDBPtr<ScoringTable>( owner );
		_victoryPoint = new UndoRedo<float>( owner, 1.0f );
		_FWODGroup = new UndoRedo<string>( owner, string.Empty );
		_FirstWinVisualInfo = new UndoRedoDBPtr<FWODVisualInfo>( owner );
		_canUseSkins = new UndoRedo<bool>( owner, true );
		_botsUseSkins = new UndoRedo<bool>( owner, false );
		_minimalGuildFightTeam = new UndoRedo<int>( owner, 3 );
		_gameSvcSettings = new UndoRedoDBPtr<GameSvcSettings>( owner );
		_playSameTeamTimeOut = new UndoRedo<int>( owner, 30 );
		_AvailableForLeavers = new UndoRedo<bool>( owner, true );
		_PlusPointForLeave = new UndoRedo<bool>( owner, false );
		_MinusPointsPerFullGame = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_loadingBackgroundImages.Changed += FireChangedEvent;
		_statisticBackgroundImages.Changed += FireChangedEvent;
		_modeVisualDescription.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_mapWithBots.Changed += FireChangedEvent;
		_PartyMode.Changed += FireChangedEvent;
		_acceptNeeded.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_map.Changed += FireChangedEvent;
		_heroesOverride.Changed += FireChangedEvent;
		_matchmakingSettings.Changed += FireChangedEvent;
		_teamSize.Changed += FireChangedEvent;
		_minTeamSize.Changed += FireChangedEvent;
		_maxUncompleteTeamSize.Changed += FireChangedEvent;
		_productionMode.Changed += FireChangedEvent;
		_mapSettings.Changed += FireChangedEvent;
		_rollSettings.Changed += FireChangedEvent;
		_guardRollSettings.Changed += FireChangedEvent;
		_scoringTable.Changed += FireChangedEvent;
		_victoryPoint.Changed += FireChangedEvent;
		_FWODGroup.Changed += FireChangedEvent;
		_FirstWinVisualInfo.Changed += FireChangedEvent;
		_canUseSkins.Changed += FireChangedEvent;
		_botsUseSkins.Changed += FireChangedEvent;
		_minimalGuildFightTeam.Changed += FireChangedEvent;
		_gameSvcSettings.Changed += FireChangedEvent;
		_playSameTeamTimeOut.Changed += FireChangedEvent;
		_AvailableForLeavers.Changed += FireChangedEvent;
		_PlusPointForLeave.Changed += FireChangedEvent;
		_MinusPointsPerFullGame.Changed += FireChangedEvent;
	}

	public AdvMapDescription()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapDescription source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapDescription" );
		title = source.title;
		loadingBackgroundImages = source.loadingBackgroundImages;
		statisticBackgroundImages = source.statisticBackgroundImages;
		modeVisualDescription = source.modeVisualDescription;
		image = source.image;
		mapType = source.mapType;
		mapWithBots = source.mapWithBots;
		PartyMode = source.PartyMode;
		acceptNeeded = source.acceptNeeded;
		description = source.description;
		map = source.map;
		heroesOverride = source.heroesOverride;
		matchmakingSettings = source.matchmakingSettings;
		teamSize = source.teamSize;
		minTeamSize = source.minTeamSize;
		maxUncompleteTeamSize = source.maxUncompleteTeamSize;
		productionMode = source.productionMode;
		mapSettings = source.mapSettings;
		rollSettings = source.rollSettings;
		guardRollSettings = source.guardRollSettings;
		scoringTable = source.scoringTable;
		victoryPoint = source.victoryPoint;
		FWODGroup = source.FWODGroup;
		FirstWinVisualInfo = source.FirstWinVisualInfo;
		canUseSkins = source.canUseSkins;
		botsUseSkins = source.botsUseSkins;
		minimalGuildFightTeam = source.minimalGuildFightTeam;
		gameSvcSettings = source.gameSvcSettings;
		playSameTeamTimeOut = source.playSameTeamTimeOut;
		AvailableForLeavers = source.AvailableForLeavers;
		PlusPointForLeave = source.PlusPointForLeave;
		MinusPointsPerFullGame = source.MinusPointsPerFullGame;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapDescription source = _source as AdvMapDescription;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapDescription" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapDescription newParent = rawParent == null ? null : rawParent.Get<AdvMapDescription>();
		if ( newParent == null && _newParent is AdvMapDescription )
			newParent = _newParent as AdvMapDescription;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_title.SetParent( newParent == null ? null : newParent._title );
		_loadingBackgroundImages.SetParent( newParent == null ? null : newParent._loadingBackgroundImages );
		_statisticBackgroundImages.SetParent( newParent == null ? null : newParent._statisticBackgroundImages );
		_modeVisualDescription.SetParent( newParent == null ? null : newParent._modeVisualDescription );
		_image.SetParent( newParent == null ? null : newParent._image );
		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_mapWithBots.SetParent( newParent == null ? null : newParent._mapWithBots );
		_PartyMode.SetParent( newParent == null ? null : newParent._PartyMode );
		_acceptNeeded.SetParent( newParent == null ? null : newParent._acceptNeeded );
		_description.SetParent( newParent == null ? null : newParent._description );
		_map.SetParent( newParent == null ? null : newParent._map );
		_heroesOverride.SetParent( newParent == null ? null : newParent._heroesOverride );
		_matchmakingSettings.SetParent( newParent == null ? null : newParent._matchmakingSettings );
		_teamSize.SetParent( newParent == null ? null : newParent._teamSize );
		_minTeamSize.SetParent( newParent == null ? null : newParent._minTeamSize );
		_maxUncompleteTeamSize.SetParent( newParent == null ? null : newParent._maxUncompleteTeamSize );
		_productionMode.SetParent( newParent == null ? null : newParent._productionMode );
		_mapSettings.SetParent( newParent == null ? null : newParent._mapSettings );
		_rollSettings.SetParent( newParent == null ? null : newParent._rollSettings );
		_guardRollSettings.SetParent( newParent == null ? null : newParent._guardRollSettings );
		_scoringTable.SetParent( newParent == null ? null : newParent._scoringTable );
		_victoryPoint.SetParent( newParent == null ? null : newParent._victoryPoint );
		_FWODGroup.SetParent( newParent == null ? null : newParent._FWODGroup );
		_FirstWinVisualInfo.SetParent( newParent == null ? null : newParent._FirstWinVisualInfo );
		_canUseSkins.SetParent( newParent == null ? null : newParent._canUseSkins );
		_botsUseSkins.SetParent( newParent == null ? null : newParent._botsUseSkins );
		_minimalGuildFightTeam.SetParent( newParent == null ? null : newParent._minimalGuildFightTeam );
		_gameSvcSettings.SetParent( newParent == null ? null : newParent._gameSvcSettings );
		_playSameTeamTimeOut.SetParent( newParent == null ? null : newParent._playSameTeamTimeOut );
		_AvailableForLeavers.SetParent( newParent == null ? null : newParent._AvailableForLeavers );
		_PlusPointForLeave.SetParent( newParent == null ? null : newParent._PlusPointForLeave );
		_MinusPointsPerFullGame.SetParent( newParent == null ? null : newParent._MinusPointsPerFullGame );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_title.Reset();
		_loadingBackgroundImages.Reset();
		_statisticBackgroundImages.Reset();
		_modeVisualDescription.Reset();
		_image.Reset();
		_mapType.Reset();
		_mapWithBots.Reset();
		_PartyMode.Reset();
		_acceptNeeded.Reset();
		_description.Reset();
		_map.Reset();
		_heroesOverride.Reset();
		_matchmakingSettings.Reset();
		_teamSize.Reset();
		_minTeamSize.Reset();
		_maxUncompleteTeamSize.Reset();
		_productionMode.Reset();
		_mapSettings.Reset();
		_rollSettings.Reset();
		_guardRollSettings.Reset();
		_scoringTable.Reset();
		_victoryPoint.Reset();
		_FWODGroup.Reset();
		_FirstWinVisualInfo.Reset();
		_canUseSkins.Reset();
		_botsUseSkins.Reset();
		_minimalGuildFightTeam.Reset();
		_gameSvcSettings.Reset();
		_playSameTeamTimeOut.Reset();
		_AvailableForLeavers.Reset();
		_PlusPointForLeave.Reset();
		_MinusPointsPerFullGame.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _loadingBackgroundImages.IsDerivedFromParent()
			&& _statisticBackgroundImages.IsDerivedFromParent()
			&& _modeVisualDescription.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _mapType.IsDerivedFromParent()
			&& _mapWithBots.IsDerivedFromParent()
			&& _PartyMode.IsDerivedFromParent()
			&& _acceptNeeded.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _map.IsDerivedFromParent()
			&& _heroesOverride.IsDerivedFromParent()
			&& _matchmakingSettings.IsDerivedFromParent()
			&& _teamSize.IsDerivedFromParent()
			&& _minTeamSize.IsDerivedFromParent()
			&& _maxUncompleteTeamSize.IsDerivedFromParent()
			&& _productionMode.IsDerivedFromParent()
			&& _mapSettings.IsDerivedFromParent()
			&& _rollSettings.IsDerivedFromParent()
			&& _guardRollSettings.IsDerivedFromParent()
			&& _scoringTable.IsDerivedFromParent()
			&& _victoryPoint.IsDerivedFromParent()
			&& _FWODGroup.IsDerivedFromParent()
			&& _FirstWinVisualInfo.IsDerivedFromParent()
			&& _canUseSkins.IsDerivedFromParent()
			&& _botsUseSkins.IsDerivedFromParent()
			&& _minimalGuildFightTeam.IsDerivedFromParent()
			&& _gameSvcSettings.IsDerivedFromParent()
			&& _playSameTeamTimeOut.IsDerivedFromParent()
			&& _AvailableForLeavers.IsDerivedFromParent()
			&& _PlusPointForLeave.IsDerivedFromParent()
			&& _MinusPointsPerFullGame.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "loadingBackgroundImages" )
			_loadingBackgroundImages.Reset();
		else if ( fieldName == "statisticBackgroundImages" )
			_statisticBackgroundImages.Reset();
		else if ( fieldName == "modeVisualDescription" )
			_modeVisualDescription.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "mapWithBots" )
			_mapWithBots.Reset();
		else if ( fieldName == "PartyMode" )
			_PartyMode.Reset();
		else if ( fieldName == "acceptNeeded" )
			_acceptNeeded.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "map" )
			_map.Reset();
		else if ( fieldName == "heroesOverride" )
			_heroesOverride.Reset();
		else if ( fieldName == "matchmakingSettings" )
			_matchmakingSettings.Reset();
		else if ( fieldName == "teamSize" )
			_teamSize.Reset();
		else if ( fieldName == "minTeamSize" )
			_minTeamSize.Reset();
		else if ( fieldName == "maxUncompleteTeamSize" )
			_maxUncompleteTeamSize.Reset();
		else if ( fieldName == "productionMode" )
			_productionMode.Reset();
		else if ( fieldName == "mapSettings" )
			_mapSettings.Reset();
		else if ( fieldName == "rollSettings" )
			_rollSettings.Reset();
		else if ( fieldName == "guardRollSettings" )
			_guardRollSettings.Reset();
		else if ( fieldName == "scoringTable" )
			_scoringTable.Reset();
		else if ( fieldName == "victoryPoint" )
			_victoryPoint.Reset();
		else if ( fieldName == "FWODGroup" )
			_FWODGroup.Reset();
		else if ( fieldName == "FirstWinVisualInfo" )
			_FirstWinVisualInfo.Reset();
		else if ( fieldName == "canUseSkins" )
			_canUseSkins.Reset();
		else if ( fieldName == "botsUseSkins" )
			_botsUseSkins.Reset();
		else if ( fieldName == "minimalGuildFightTeam" )
			_minimalGuildFightTeam.Reset();
		else if ( fieldName == "gameSvcSettings" )
			_gameSvcSettings.Reset();
		else if ( fieldName == "playSameTeamTimeOut" )
			_playSameTeamTimeOut.Reset();
		else if ( fieldName == "AvailableForLeavers" )
			_AvailableForLeavers.Reset();
		else if ( fieldName == "PlusPointForLeave" )
			_PlusPointForLeave.Reset();
		else if ( fieldName == "MinusPointsPerFullGame" )
			_MinusPointsPerFullGame.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "loadingBackgroundImages" )
			return _loadingBackgroundImages.IsDerivedFromParent();
		if ( fieldName == "statisticBackgroundImages" )
			return _statisticBackgroundImages.IsDerivedFromParent();
		if ( fieldName == "modeVisualDescription" )
			return _modeVisualDescription.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "mapWithBots" )
			return _mapWithBots.IsDerivedFromParent();
		if ( fieldName == "PartyMode" )
			return _PartyMode.IsDerivedFromParent();
		if ( fieldName == "acceptNeeded" )
			return _acceptNeeded.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "map" )
			return _map.IsDerivedFromParent();
		if ( fieldName == "heroesOverride" )
			return _heroesOverride.IsDerivedFromParent();
		if ( fieldName == "matchmakingSettings" )
			return _matchmakingSettings.IsDerivedFromParent();
		if ( fieldName == "teamSize" )
			return _teamSize.IsDerivedFromParent();
		if ( fieldName == "minTeamSize" )
			return _minTeamSize.IsDerivedFromParent();
		if ( fieldName == "maxUncompleteTeamSize" )
			return _maxUncompleteTeamSize.IsDerivedFromParent();
		if ( fieldName == "productionMode" )
			return _productionMode.IsDerivedFromParent();
		if ( fieldName == "mapSettings" )
			return _mapSettings.IsDerivedFromParent();
		if ( fieldName == "rollSettings" )
			return _rollSettings.IsDerivedFromParent();
		if ( fieldName == "guardRollSettings" )
			return _guardRollSettings.IsDerivedFromParent();
		if ( fieldName == "scoringTable" )
			return _scoringTable.IsDerivedFromParent();
		if ( fieldName == "victoryPoint" )
			return _victoryPoint.IsDerivedFromParent();
		if ( fieldName == "FWODGroup" )
			return _FWODGroup.IsDerivedFromParent();
		if ( fieldName == "FirstWinVisualInfo" )
			return _FirstWinVisualInfo.IsDerivedFromParent();
		if ( fieldName == "canUseSkins" )
			return _canUseSkins.IsDerivedFromParent();
		if ( fieldName == "botsUseSkins" )
			return _botsUseSkins.IsDerivedFromParent();
		if ( fieldName == "minimalGuildFightTeam" )
			return _minimalGuildFightTeam.IsDerivedFromParent();
		if ( fieldName == "gameSvcSettings" )
			return _gameSvcSettings.IsDerivedFromParent();
		if ( fieldName == "playSameTeamTimeOut" )
			return _playSameTeamTimeOut.IsDerivedFromParent();
		if ( fieldName == "AvailableForLeavers" )
			return _AvailableForLeavers.IsDerivedFromParent();
		if ( fieldName == "PlusPointForLeave" )
			return _PlusPointForLeave.IsDerivedFromParent();
		if ( fieldName == "MinusPointsPerFullGame" )
			return _MinusPointsPerFullGame.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class AdvMapHeroesOverride : DBResource
{
	private UndoRedoDBPtr<AdvMapHeroesOverride> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapHeroesOverride> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AdvMapHeroesOverrideData> _singlePlayerMale;
	private UndoRedoDBPtr<AdvMapHeroesOverrideData> _singlePlayerFemale;
	private UndoRedo<bool> _shuffleHeroesInTeam;

	[Description( "Heroes override data for single player male" )]
	public DBPtr<AdvMapHeroesOverrideData> singlePlayerMale { get { return _singlePlayerMale.Get(); } set { _singlePlayerMale.Set( value ); } }

	[Description( "Heroes override data for single player female" )]
	public DBPtr<AdvMapHeroesOverrideData> singlePlayerFemale { get { return _singlePlayerFemale.Get(); } set { _singlePlayerFemale.Set( value ); } }

	[Description( "Перемешать героев между игроками каждой из команд" )]
	public bool shuffleHeroesInTeam { get { return _shuffleHeroesInTeam.Get(); } set { _shuffleHeroesInTeam.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapHeroesOverride>(owner);
		_singlePlayerMale = new UndoRedoDBPtr<AdvMapHeroesOverrideData>( owner );
		_singlePlayerFemale = new UndoRedoDBPtr<AdvMapHeroesOverrideData>( owner );
		_shuffleHeroesInTeam = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_singlePlayerMale.Changed += FireChangedEvent;
		_singlePlayerFemale.Changed += FireChangedEvent;
		_shuffleHeroesInTeam.Changed += FireChangedEvent;
	}

	public AdvMapHeroesOverride()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapHeroesOverride source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapHeroesOverride" );
		singlePlayerMale = source.singlePlayerMale;
		singlePlayerFemale = source.singlePlayerFemale;
		shuffleHeroesInTeam = source.shuffleHeroesInTeam;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapHeroesOverride source = _source as AdvMapHeroesOverride;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapHeroesOverride" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapHeroesOverride newParent = rawParent == null ? null : rawParent.Get<AdvMapHeroesOverride>();
		if ( newParent == null && _newParent is AdvMapHeroesOverride )
			newParent = _newParent as AdvMapHeroesOverride;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_singlePlayerMale.SetParent( newParent == null ? null : newParent._singlePlayerMale );
		_singlePlayerFemale.SetParent( newParent == null ? null : newParent._singlePlayerFemale );
		_shuffleHeroesInTeam.SetParent( newParent == null ? null : newParent._shuffleHeroesInTeam );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_singlePlayerMale.Reset();
		_singlePlayerFemale.Reset();
		_shuffleHeroesInTeam.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_singlePlayerMale.IsDerivedFromParent()
			&& _singlePlayerFemale.IsDerivedFromParent()
			&& _shuffleHeroesInTeam.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "singlePlayerMale" )
			_singlePlayerMale.Reset();
		else if ( fieldName == "singlePlayerFemale" )
			_singlePlayerFemale.Reset();
		else if ( fieldName == "shuffleHeroesInTeam" )
			_shuffleHeroesInTeam.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "singlePlayerMale" )
			return _singlePlayerMale.IsDerivedFromParent();
		if ( fieldName == "singlePlayerFemale" )
			return _singlePlayerFemale.IsDerivedFromParent();
		if ( fieldName == "shuffleHeroesInTeam" )
			return _shuffleHeroesInTeam.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class AdvMapHeroesOverrideData : DBResource
{
	private UndoRedoDBPtr<AdvMapHeroesOverrideData> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapHeroesOverrideData> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AdvMapPlayerData _ownHero;
	private UndoRedoAssignableList<AdvMapPlayerData> _allies;
	private UndoRedoAssignableList<AdvMapPlayerData> _enemies;

	[Custom("Social")]
	[Description( "Own hero - effective only in single player game" )]
	public AdvMapPlayerData ownHero { get { return _ownHero; } set { _ownHero.Assign( value ); } }

	[Description( "Allies heroes" )]
	public libdb.IChangeableList<AdvMapPlayerData> allies { get { return _allies; } set { _allies.Assign( value ); } }

	[Description( "Enemies heroes" )]
	public libdb.IChangeableList<AdvMapPlayerData> enemies { get { return _enemies; } set { _enemies.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapHeroesOverrideData>(owner);
		_ownHero = new AdvMapPlayerData( owner );
		_allies = new UndoRedoAssignableList<AdvMapPlayerData>( owner );
		_enemies = new UndoRedoAssignableList<AdvMapPlayerData>( owner );
		___parent.Changed += FireChangedEvent;
		_ownHero.Changed += FireChangedEvent;
		_allies.Changed += FireChangedEvent;
		_enemies.Changed += FireChangedEvent;
	}

	public AdvMapHeroesOverrideData()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapHeroesOverrideData source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapHeroesOverrideData" );
		ownHero = source.ownHero;
		allies = source.allies;
		enemies = source.enemies;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapHeroesOverrideData source = _source as AdvMapHeroesOverrideData;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapHeroesOverrideData" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapHeroesOverrideData newParent = rawParent == null ? null : rawParent.Get<AdvMapHeroesOverrideData>();
		if ( newParent == null && _newParent is AdvMapHeroesOverrideData )
			newParent = _newParent as AdvMapHeroesOverrideData;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ownHero.SetParent( newParent == null ? null : newParent._ownHero );
		_allies.SetParent( newParent == null ? null : newParent._allies );
		_enemies.SetParent( newParent == null ? null : newParent._enemies );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ownHero.Reset();
		_allies.Reset();
		_enemies.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ownHero.IsDerivedFromParent()
			&& _allies.IsDerivedFromParent()
			&& _enemies.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ownHero" )
			_ownHero.Reset();
		else if ( fieldName == "allies" )
			_allies.Reset();
		else if ( fieldName == "enemies" )
			_enemies.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ownHero" )
			return _ownHero.IsDerivedFromParent();
		if ( fieldName == "allies" )
			return _allies.IsDerivedFromParent();
		if ( fieldName == "enemies" )
			return _enemies.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ADMPSTTN")]
public class AdvMapSettings : DBResource
{
	private UndoRedoDBPtr<AdvMapSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _battleStartDelay;
	private UndoRedo<int> _towersVulnerabilityDelay;
	private BattleStartAnnouncementParams _customBattleStartAnnouncement;
	private UndoRedo<bool> _useCustomBattleStartAnnouncement;
	private UndoRedo<bool> _showAllHeroes;
	private UndoRedo<float> _force;
	private UndoRedo<float> _minRequiredHeroForce;
	private UndoRedo<float> _maxRequiredHeroForce;
	private UndoRedo<bool> _fullPartyOnly;
	private UndoRedoDBPtr<DictionaryPreloadingResources> _dictionary;
	private PrimeSettings _primeSettings;
	private UndoRedoDBPtr<DialogsCollection> _dialogsCollection;
	private UndoRedoDBPtr<HintsCollection> _hintsCollection;
	private UndoRedoDBPtr<SessionQuestsCollection> _questsCollection;
	private UndoRedo<float> _trainingForceCoeff;
	private UndoRedo<string> _scriptFileName;
	private UndoRedoDBPtr<HeroRespawnParams> _heroRespawnParams;
	private UndoRedoAssignableList<TriggerMarkerBinding> _triggerMarkerBinding;
	private UndoRedoDBPtr<CreepAnnounceList> _creepAnnounceList;
	private UndoRedoDBPtr<VotingForSurrenderPerMission> _votingForSurrender;
	private UndoRedoDBPtr<AdventureTooltipParams> _overrideTooltipParams;
	private UndoRedoDBPtr<DBMinimap> _overrideMinimapParams;
	private UndoRedoDBPtr<Talent> _overridePortalTalent;
	private UndoRedoDBPtr<GlyphManagerParams> _overrideGlyphSettings;
	private UndoRedoDBPtr<BotsSettings> _overrideBotsSettings;
	private UndoRedo<bool> _enableAnnouncements;
	private UndoRedo<bool> _enablePortalTalent;
	private UndoRedo<bool> _enableAllScriptFunctions;
	private UndoRedo<bool> _enableStatistics;
	private UndoRedo<int> _creepLevelCap;
	private UndoRedo<int> _emblemHeroNeeds;

	[Description( "Faction Creeps first spawn delay in seconds" )]
	public int battleStartDelay { get { return _battleStartDelay.Get(); } set { _battleStartDelay.Set( value ); } }

	[Description( "Towers vulnerability delay in seconds" )]
	public int towersVulnerabilityDelay { get { return _towersVulnerabilityDelay.Get(); } set { _towersVulnerabilityDelay.Set( value ); } }

	[Description( "Custom battle start announcement icons and text" )]
	public BattleStartAnnouncementParams customBattleStartAnnouncement { get { return _customBattleStartAnnouncement; } set { _customBattleStartAnnouncement.Assign( value ); } }

	public bool useCustomBattleStartAnnouncement { get { return _useCustomBattleStartAnnouncement.Get(); } set { _useCustomBattleStartAnnouncement.Set( value ); } }

	[Description( "Show all heroes on loading screen" )]
	public bool showAllHeroes { get { return _showAllHeroes.Get(); } set { _showAllHeroes.Set( value ); } }

	[Description( "Force of the map" )]
	public float force { get { return _force.Get(); } set { _force.Set( value ); } }

	[Custom("Social")]
	[Description( "Минимальная необходимая мощь чтобы пойти героем на карту" )]
	public float minRequiredHeroForce { get { return _minRequiredHeroForce.Get(); } set { _minRequiredHeroForce.Set( value ); } }

	[Custom("Social")]
	[Description( "Максимальная необходимая мощь чтобы пойти героем на карту" )]
	public float maxRequiredHeroForce { get { return _maxRequiredHeroForce.Get(); } set { _maxRequiredHeroForce.Set( value ); } }

	[Custom("Social", "DBServer")]
	[Description( "Включает возможность ухода в бой только группу из 5 человек" )]
	public bool fullPartyOnly { get { return _fullPartyOnly.Get(); } set { _fullPartyOnly.Set( value ); } }

	[Description( "Dictionary of preloading resources" )]
	public DBPtr<DictionaryPreloadingResources> dictionary { get { return _dictionary.Get(); } set { _dictionary.Set( value ); } }

	[Description( "Prime income settings" )]
	public PrimeSettings primeSettings { get { return _primeSettings; } set { _primeSettings.Assign( value ); } }

	[Description( "Dialogs for the map" )]
	public DBPtr<DialogsCollection> dialogsCollection { get { return _dialogsCollection.Get(); } set { _dialogsCollection.Set( value ); } }

	[Description( "Hints for the map" )]
	public DBPtr<HintsCollection> hintsCollection { get { return _hintsCollection.Get(); } set { _hintsCollection.Set( value ); } }

	[Description( "Quests for the map" )]
	public DBPtr<SessionQuestsCollection> questsCollection { get { return _questsCollection.Get(); } set { _questsCollection.Set( value ); } }

	[Description( "Multiplier to the map force for training mode" )]
	public float trainingForceCoeff { get { return _trainingForceCoeff.Get(); } set { _trainingForceCoeff.Set( value ); } }

	[Description( "Script file to run after map loading" )]
	public string scriptFileName { get { return _scriptFileName.Get(); } set { _scriptFileName.Set( value ); } }

	[Description( "Overridden params" )]
	public DBPtr<HeroRespawnParams> heroRespawnParams { get { return _heroRespawnParams.Get(); } set { _heroRespawnParams.Set( value ); } }

	[Description( "Binding of ScriptArea's Trigger and Marker points" )]
	public libdb.IChangeableList<TriggerMarkerBinding> triggerMarkerBinding { get { return _triggerMarkerBinding; } set { _triggerMarkerBinding.Assign( value ); } }

	[Description( "Neutral creeps in spawners whose killing to be announced" )]
	public DBPtr<CreepAnnounceList> creepAnnounceList { get { return _creepAnnounceList.Get(); } set { _creepAnnounceList.Set( value ); } }

	[Description( "Настройки голосования о сдаче. Если не указаны, то используются умолчания заданные для всех карт" )]
	public DBPtr<VotingForSurrenderPerMission> votingForSurrender { get { return _votingForSurrender.Get(); } set { _votingForSurrender.Set( value ); } }

	[Description( "Overridden overtip settings" )]
	public DBPtr<AdventureTooltipParams> overrideTooltipParams { get { return _overrideTooltipParams.Get(); } set { _overrideTooltipParams.Set( value ); } }

	[Description( "Overridden minimap settings" )]
	public DBPtr<DBMinimap> overrideMinimapParams { get { return _overrideMinimapParams.Get(); } set { _overrideMinimapParams.Set( value ); } }

	[Description( "Overridden portal spell" )]
	public DBPtr<Talent> overridePortalTalent { get { return _overridePortalTalent.Get(); } set { _overridePortalTalent.Set( value ); } }

	[Description( "Настройки спавна глифов. Если не указаны, то используются умолчания заданные для всех карт" )]
	public DBPtr<GlyphManagerParams> overrideGlyphSettings { get { return _overrideGlyphSettings.Get(); } set { _overrideGlyphSettings.Set( value ); } }

	[Description( "Настройки ботов. Если не указаны, то используются умолчания заданные для всех карт" )]
	public DBPtr<BotsSettings> overrideBotsSettings { get { return _overrideBotsSettings.Get(); } set { _overrideBotsSettings.Set( value ); } }

	[Description( "Show announcements in UI" )]
	public bool enableAnnouncements { get { return _enableAnnouncements.Get(); } set { _enableAnnouncements.Set( value ); } }

	[Description( "Enable portal standard hero talent" )]
	public bool enablePortalTalent { get { return _enablePortalTalent.Get(); } set { _enablePortalTalent.Set( value ); } }

	[Description( "Enable 'win game'  etc. script functions in multiplayer game" )]
	public bool enableAllScriptFunctions { get { return _enableAllScriptFunctions.Get(); } set { _enableAllScriptFunctions.Set( value ); } }

	[Description( "Enable/disable statistics logging" )]
	public bool enableStatistics { get { return _enableStatistics.Get(); } set { _enableStatistics.Set( value ); } }

	[Description( "If >= 0 - override creepLevelCap from AILogicParameters" )]
	public int creepLevelCap { get { return _creepLevelCap.Get(); } set { _creepLevelCap.Set( value ); } }

	[Description( "При скольки героях одного клана на поднятых флагах рисуется эмблема клана" )]
	public int emblemHeroNeeds { get { return _emblemHeroNeeds.Get(); } set { _emblemHeroNeeds.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapSettings>(owner);
		_battleStartDelay = new UndoRedo<int>( owner, 10 );
		_towersVulnerabilityDelay = new UndoRedo<int>( owner, 0 );
		_customBattleStartAnnouncement = new BattleStartAnnouncementParams( owner );
		_useCustomBattleStartAnnouncement = new UndoRedo<bool>( owner, false );
		_showAllHeroes = new UndoRedo<bool>( owner, true );
		_force = new UndoRedo<float>( owner, 125.0f );
		_minRequiredHeroForce = new UndoRedo<float>( owner, 0.0f );
		_maxRequiredHeroForce = new UndoRedo<float>( owner, 10000.0f );
		_fullPartyOnly = new UndoRedo<bool>( owner, false );
		_dictionary = new UndoRedoDBPtr<DictionaryPreloadingResources>( owner );
		_primeSettings = new PrimeSettings( owner );
		_dialogsCollection = new UndoRedoDBPtr<DialogsCollection>( owner );
		_hintsCollection = new UndoRedoDBPtr<HintsCollection>( owner );
		_questsCollection = new UndoRedoDBPtr<SessionQuestsCollection>( owner );
		_trainingForceCoeff = new UndoRedo<float>( owner, 1.0f );
		_scriptFileName = new UndoRedo<string>( owner, string.Empty );
		_heroRespawnParams = new UndoRedoDBPtr<HeroRespawnParams>( owner );
		_triggerMarkerBinding = new UndoRedoAssignableList<TriggerMarkerBinding>( owner );
		_creepAnnounceList = new UndoRedoDBPtr<CreepAnnounceList>( owner );
		_votingForSurrender = new UndoRedoDBPtr<VotingForSurrenderPerMission>( owner );
		_overrideTooltipParams = new UndoRedoDBPtr<AdventureTooltipParams>( owner );
		_overrideMinimapParams = new UndoRedoDBPtr<DBMinimap>( owner );
		_overridePortalTalent = new UndoRedoDBPtr<Talent>( owner );
		_overrideGlyphSettings = new UndoRedoDBPtr<GlyphManagerParams>( owner );
		_overrideBotsSettings = new UndoRedoDBPtr<BotsSettings>( owner );
		_enableAnnouncements = new UndoRedo<bool>( owner, true );
		_enablePortalTalent = new UndoRedo<bool>( owner, true );
		_enableAllScriptFunctions = new UndoRedo<bool>( owner, false );
		_enableStatistics = new UndoRedo<bool>( owner, true );
		_creepLevelCap = new UndoRedo<int>( owner, -1 );
		_emblemHeroNeeds = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_battleStartDelay.Changed += FireChangedEvent;
		_towersVulnerabilityDelay.Changed += FireChangedEvent;
		_customBattleStartAnnouncement.Changed += FireChangedEvent;
		_useCustomBattleStartAnnouncement.Changed += FireChangedEvent;
		_showAllHeroes.Changed += FireChangedEvent;
		_force.Changed += FireChangedEvent;
		_minRequiredHeroForce.Changed += FireChangedEvent;
		_maxRequiredHeroForce.Changed += FireChangedEvent;
		_fullPartyOnly.Changed += FireChangedEvent;
		_dictionary.Changed += FireChangedEvent;
		_primeSettings.Changed += FireChangedEvent;
		_dialogsCollection.Changed += FireChangedEvent;
		_hintsCollection.Changed += FireChangedEvent;
		_questsCollection.Changed += FireChangedEvent;
		_trainingForceCoeff.Changed += FireChangedEvent;
		_scriptFileName.Changed += FireChangedEvent;
		_heroRespawnParams.Changed += FireChangedEvent;
		_triggerMarkerBinding.Changed += FireChangedEvent;
		_creepAnnounceList.Changed += FireChangedEvent;
		_votingForSurrender.Changed += FireChangedEvent;
		_overrideTooltipParams.Changed += FireChangedEvent;
		_overrideMinimapParams.Changed += FireChangedEvent;
		_overridePortalTalent.Changed += FireChangedEvent;
		_overrideGlyphSettings.Changed += FireChangedEvent;
		_overrideBotsSettings.Changed += FireChangedEvent;
		_enableAnnouncements.Changed += FireChangedEvent;
		_enablePortalTalent.Changed += FireChangedEvent;
		_enableAllScriptFunctions.Changed += FireChangedEvent;
		_enableStatistics.Changed += FireChangedEvent;
		_creepLevelCap.Changed += FireChangedEvent;
		_emblemHeroNeeds.Changed += FireChangedEvent;
	}

	public AdvMapSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapSettings" );
		battleStartDelay = source.battleStartDelay;
		towersVulnerabilityDelay = source.towersVulnerabilityDelay;
		customBattleStartAnnouncement = source.customBattleStartAnnouncement;
		useCustomBattleStartAnnouncement = source.useCustomBattleStartAnnouncement;
		showAllHeroes = source.showAllHeroes;
		force = source.force;
		minRequiredHeroForce = source.minRequiredHeroForce;
		maxRequiredHeroForce = source.maxRequiredHeroForce;
		fullPartyOnly = source.fullPartyOnly;
		dictionary = source.dictionary;
		primeSettings = source.primeSettings;
		dialogsCollection = source.dialogsCollection;
		hintsCollection = source.hintsCollection;
		questsCollection = source.questsCollection;
		trainingForceCoeff = source.trainingForceCoeff;
		scriptFileName = source.scriptFileName;
		heroRespawnParams = source.heroRespawnParams;
		triggerMarkerBinding = source.triggerMarkerBinding;
		creepAnnounceList = source.creepAnnounceList;
		votingForSurrender = source.votingForSurrender;
		overrideTooltipParams = source.overrideTooltipParams;
		overrideMinimapParams = source.overrideMinimapParams;
		overridePortalTalent = source.overridePortalTalent;
		overrideGlyphSettings = source.overrideGlyphSettings;
		overrideBotsSettings = source.overrideBotsSettings;
		enableAnnouncements = source.enableAnnouncements;
		enablePortalTalent = source.enablePortalTalent;
		enableAllScriptFunctions = source.enableAllScriptFunctions;
		enableStatistics = source.enableStatistics;
		creepLevelCap = source.creepLevelCap;
		emblemHeroNeeds = source.emblemHeroNeeds;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapSettings source = _source as AdvMapSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapSettings newParent = rawParent == null ? null : rawParent.Get<AdvMapSettings>();
		if ( newParent == null && _newParent is AdvMapSettings )
			newParent = _newParent as AdvMapSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_battleStartDelay.SetParent( newParent == null ? null : newParent._battleStartDelay );
		_towersVulnerabilityDelay.SetParent( newParent == null ? null : newParent._towersVulnerabilityDelay );
		_customBattleStartAnnouncement.SetParent( newParent == null ? null : newParent._customBattleStartAnnouncement );
		_useCustomBattleStartAnnouncement.SetParent( newParent == null ? null : newParent._useCustomBattleStartAnnouncement );
		_showAllHeroes.SetParent( newParent == null ? null : newParent._showAllHeroes );
		_force.SetParent( newParent == null ? null : newParent._force );
		_minRequiredHeroForce.SetParent( newParent == null ? null : newParent._minRequiredHeroForce );
		_maxRequiredHeroForce.SetParent( newParent == null ? null : newParent._maxRequiredHeroForce );
		_fullPartyOnly.SetParent( newParent == null ? null : newParent._fullPartyOnly );
		_dictionary.SetParent( newParent == null ? null : newParent._dictionary );
		_primeSettings.SetParent( newParent == null ? null : newParent._primeSettings );
		_dialogsCollection.SetParent( newParent == null ? null : newParent._dialogsCollection );
		_hintsCollection.SetParent( newParent == null ? null : newParent._hintsCollection );
		_questsCollection.SetParent( newParent == null ? null : newParent._questsCollection );
		_trainingForceCoeff.SetParent( newParent == null ? null : newParent._trainingForceCoeff );
		_scriptFileName.SetParent( newParent == null ? null : newParent._scriptFileName );
		_heroRespawnParams.SetParent( newParent == null ? null : newParent._heroRespawnParams );
		_triggerMarkerBinding.SetParent( newParent == null ? null : newParent._triggerMarkerBinding );
		_creepAnnounceList.SetParent( newParent == null ? null : newParent._creepAnnounceList );
		_votingForSurrender.SetParent( newParent == null ? null : newParent._votingForSurrender );
		_overrideTooltipParams.SetParent( newParent == null ? null : newParent._overrideTooltipParams );
		_overrideMinimapParams.SetParent( newParent == null ? null : newParent._overrideMinimapParams );
		_overridePortalTalent.SetParent( newParent == null ? null : newParent._overridePortalTalent );
		_overrideGlyphSettings.SetParent( newParent == null ? null : newParent._overrideGlyphSettings );
		_overrideBotsSettings.SetParent( newParent == null ? null : newParent._overrideBotsSettings );
		_enableAnnouncements.SetParent( newParent == null ? null : newParent._enableAnnouncements );
		_enablePortalTalent.SetParent( newParent == null ? null : newParent._enablePortalTalent );
		_enableAllScriptFunctions.SetParent( newParent == null ? null : newParent._enableAllScriptFunctions );
		_enableStatistics.SetParent( newParent == null ? null : newParent._enableStatistics );
		_creepLevelCap.SetParent( newParent == null ? null : newParent._creepLevelCap );
		_emblemHeroNeeds.SetParent( newParent == null ? null : newParent._emblemHeroNeeds );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_battleStartDelay.Reset();
		_towersVulnerabilityDelay.Reset();
		_customBattleStartAnnouncement.Reset();
		_useCustomBattleStartAnnouncement.Reset();
		_showAllHeroes.Reset();
		_force.Reset();
		_minRequiredHeroForce.Reset();
		_maxRequiredHeroForce.Reset();
		_fullPartyOnly.Reset();
		_dictionary.Reset();
		_primeSettings.Reset();
		_dialogsCollection.Reset();
		_hintsCollection.Reset();
		_questsCollection.Reset();
		_trainingForceCoeff.Reset();
		_scriptFileName.Reset();
		_heroRespawnParams.Reset();
		_triggerMarkerBinding.Reset();
		_creepAnnounceList.Reset();
		_votingForSurrender.Reset();
		_overrideTooltipParams.Reset();
		_overrideMinimapParams.Reset();
		_overridePortalTalent.Reset();
		_overrideGlyphSettings.Reset();
		_overrideBotsSettings.Reset();
		_enableAnnouncements.Reset();
		_enablePortalTalent.Reset();
		_enableAllScriptFunctions.Reset();
		_enableStatistics.Reset();
		_creepLevelCap.Reset();
		_emblemHeroNeeds.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_battleStartDelay.IsDerivedFromParent()
			&& _towersVulnerabilityDelay.IsDerivedFromParent()
			&& _customBattleStartAnnouncement.IsDerivedFromParent()
			&& _useCustomBattleStartAnnouncement.IsDerivedFromParent()
			&& _showAllHeroes.IsDerivedFromParent()
			&& _force.IsDerivedFromParent()
			&& _minRequiredHeroForce.IsDerivedFromParent()
			&& _maxRequiredHeroForce.IsDerivedFromParent()
			&& _fullPartyOnly.IsDerivedFromParent()
			&& _dictionary.IsDerivedFromParent()
			&& _primeSettings.IsDerivedFromParent()
			&& _dialogsCollection.IsDerivedFromParent()
			&& _hintsCollection.IsDerivedFromParent()
			&& _questsCollection.IsDerivedFromParent()
			&& _trainingForceCoeff.IsDerivedFromParent()
			&& _scriptFileName.IsDerivedFromParent()
			&& _heroRespawnParams.IsDerivedFromParent()
			&& _triggerMarkerBinding.IsDerivedFromParent()
			&& _creepAnnounceList.IsDerivedFromParent()
			&& _votingForSurrender.IsDerivedFromParent()
			&& _overrideTooltipParams.IsDerivedFromParent()
			&& _overrideMinimapParams.IsDerivedFromParent()
			&& _overridePortalTalent.IsDerivedFromParent()
			&& _overrideGlyphSettings.IsDerivedFromParent()
			&& _overrideBotsSettings.IsDerivedFromParent()
			&& _enableAnnouncements.IsDerivedFromParent()
			&& _enablePortalTalent.IsDerivedFromParent()
			&& _enableAllScriptFunctions.IsDerivedFromParent()
			&& _enableStatistics.IsDerivedFromParent()
			&& _creepLevelCap.IsDerivedFromParent()
			&& _emblemHeroNeeds.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "battleStartDelay" )
			_battleStartDelay.Reset();
		else if ( fieldName == "towersVulnerabilityDelay" )
			_towersVulnerabilityDelay.Reset();
		else if ( fieldName == "customBattleStartAnnouncement" )
			_customBattleStartAnnouncement.Reset();
		else if ( fieldName == "useCustomBattleStartAnnouncement" )
			_useCustomBattleStartAnnouncement.Reset();
		else if ( fieldName == "showAllHeroes" )
			_showAllHeroes.Reset();
		else if ( fieldName == "force" )
			_force.Reset();
		else if ( fieldName == "minRequiredHeroForce" )
			_minRequiredHeroForce.Reset();
		else if ( fieldName == "maxRequiredHeroForce" )
			_maxRequiredHeroForce.Reset();
		else if ( fieldName == "fullPartyOnly" )
			_fullPartyOnly.Reset();
		else if ( fieldName == "dictionary" )
			_dictionary.Reset();
		else if ( fieldName == "primeSettings" )
			_primeSettings.Reset();
		else if ( fieldName == "dialogsCollection" )
			_dialogsCollection.Reset();
		else if ( fieldName == "hintsCollection" )
			_hintsCollection.Reset();
		else if ( fieldName == "questsCollection" )
			_questsCollection.Reset();
		else if ( fieldName == "trainingForceCoeff" )
			_trainingForceCoeff.Reset();
		else if ( fieldName == "scriptFileName" )
			_scriptFileName.Reset();
		else if ( fieldName == "heroRespawnParams" )
			_heroRespawnParams.Reset();
		else if ( fieldName == "triggerMarkerBinding" )
			_triggerMarkerBinding.Reset();
		else if ( fieldName == "creepAnnounceList" )
			_creepAnnounceList.Reset();
		else if ( fieldName == "votingForSurrender" )
			_votingForSurrender.Reset();
		else if ( fieldName == "overrideTooltipParams" )
			_overrideTooltipParams.Reset();
		else if ( fieldName == "overrideMinimapParams" )
			_overrideMinimapParams.Reset();
		else if ( fieldName == "overridePortalTalent" )
			_overridePortalTalent.Reset();
		else if ( fieldName == "overrideGlyphSettings" )
			_overrideGlyphSettings.Reset();
		else if ( fieldName == "overrideBotsSettings" )
			_overrideBotsSettings.Reset();
		else if ( fieldName == "enableAnnouncements" )
			_enableAnnouncements.Reset();
		else if ( fieldName == "enablePortalTalent" )
			_enablePortalTalent.Reset();
		else if ( fieldName == "enableAllScriptFunctions" )
			_enableAllScriptFunctions.Reset();
		else if ( fieldName == "enableStatistics" )
			_enableStatistics.Reset();
		else if ( fieldName == "creepLevelCap" )
			_creepLevelCap.Reset();
		else if ( fieldName == "emblemHeroNeeds" )
			_emblemHeroNeeds.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "battleStartDelay" )
			return _battleStartDelay.IsDerivedFromParent();
		if ( fieldName == "towersVulnerabilityDelay" )
			return _towersVulnerabilityDelay.IsDerivedFromParent();
		if ( fieldName == "customBattleStartAnnouncement" )
			return _customBattleStartAnnouncement.IsDerivedFromParent();
		if ( fieldName == "useCustomBattleStartAnnouncement" )
			return _useCustomBattleStartAnnouncement.IsDerivedFromParent();
		if ( fieldName == "showAllHeroes" )
			return _showAllHeroes.IsDerivedFromParent();
		if ( fieldName == "force" )
			return _force.IsDerivedFromParent();
		if ( fieldName == "minRequiredHeroForce" )
			return _minRequiredHeroForce.IsDerivedFromParent();
		if ( fieldName == "maxRequiredHeroForce" )
			return _maxRequiredHeroForce.IsDerivedFromParent();
		if ( fieldName == "fullPartyOnly" )
			return _fullPartyOnly.IsDerivedFromParent();
		if ( fieldName == "dictionary" )
			return _dictionary.IsDerivedFromParent();
		if ( fieldName == "primeSettings" )
			return _primeSettings.IsDerivedFromParent();
		if ( fieldName == "dialogsCollection" )
			return _dialogsCollection.IsDerivedFromParent();
		if ( fieldName == "hintsCollection" )
			return _hintsCollection.IsDerivedFromParent();
		if ( fieldName == "questsCollection" )
			return _questsCollection.IsDerivedFromParent();
		if ( fieldName == "trainingForceCoeff" )
			return _trainingForceCoeff.IsDerivedFromParent();
		if ( fieldName == "scriptFileName" )
			return _scriptFileName.IsDerivedFromParent();
		if ( fieldName == "heroRespawnParams" )
			return _heroRespawnParams.IsDerivedFromParent();
		if ( fieldName == "triggerMarkerBinding" )
			return _triggerMarkerBinding.IsDerivedFromParent();
		if ( fieldName == "creepAnnounceList" )
			return _creepAnnounceList.IsDerivedFromParent();
		if ( fieldName == "votingForSurrender" )
			return _votingForSurrender.IsDerivedFromParent();
		if ( fieldName == "overrideTooltipParams" )
			return _overrideTooltipParams.IsDerivedFromParent();
		if ( fieldName == "overrideMinimapParams" )
			return _overrideMinimapParams.IsDerivedFromParent();
		if ( fieldName == "overridePortalTalent" )
			return _overridePortalTalent.IsDerivedFromParent();
		if ( fieldName == "overrideGlyphSettings" )
			return _overrideGlyphSettings.IsDerivedFromParent();
		if ( fieldName == "overrideBotsSettings" )
			return _overrideBotsSettings.IsDerivedFromParent();
		if ( fieldName == "enableAnnouncements" )
			return _enableAnnouncements.IsDerivedFromParent();
		if ( fieldName == "enablePortalTalent" )
			return _enablePortalTalent.IsDerivedFromParent();
		if ( fieldName == "enableAllScriptFunctions" )
			return _enableAllScriptFunctions.IsDerivedFromParent();
		if ( fieldName == "enableStatistics" )
			return _enableStatistics.IsDerivedFromParent();
		if ( fieldName == "creepLevelCap" )
			return _creepLevelCap.IsDerivedFromParent();
		if ( fieldName == "emblemHeroNeeds" )
			return _emblemHeroNeeds.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[TypeId(0x146B6280)]
[UseTypeName("WTRZ")]
public class AdvMapWaterZone : GameObject
{
	private UndoRedoDBPtr<AdvMapWaterZone> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapWaterZone> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private FlatSplineDesc _area;

	public FlatSplineDesc area { get { return _area; } set { _area.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapWaterZone>(owner);
		_area = new FlatSplineDesc( owner );
		___parent.Changed += FireChangedEvent;
		_area.Changed += FireChangedEvent;
	}

	public AdvMapWaterZone()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapWaterZone source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapWaterZone" );
		area = source.area;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapWaterZone source = _source as AdvMapWaterZone;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapWaterZone" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapWaterZone newParent = rawParent == null ? null : rawParent.Get<AdvMapWaterZone>();
		if ( newParent == null && _newParent is AdvMapWaterZone )
			newParent = _newParent as AdvMapWaterZone;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_area.SetParent( newParent == null ? null : newParent._area );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_area.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_area.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "area" )
			_area.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "area" )
			return _area.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class CreepAnnounceList : DBResource
{
	private UndoRedoDBPtr<CreepAnnounceList> ___parent;
	[HideInOutliner]
	public new DBPtr<CreepAnnounceList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<CreepAnnounce> _list;

	public libdb.IChangeableList<CreepAnnounce> list { get { return _list; } set { _list.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CreepAnnounceList>(owner);
		_list = new UndoRedoAssignableList<CreepAnnounce>( owner );
		___parent.Changed += FireChangedEvent;
		_list.Changed += FireChangedEvent;
	}

	public CreepAnnounceList()
	{
		Initialize( this );
	}
	private void AssignSelf( CreepAnnounceList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CreepAnnounceList" );
		list = source.list;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CreepAnnounceList source = _source as CreepAnnounceList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepAnnounceList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CreepAnnounceList newParent = rawParent == null ? null : rawParent.Get<CreepAnnounceList>();
		if ( newParent == null && _newParent is CreepAnnounceList )
			newParent = _newParent as CreepAnnounceList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_list.SetParent( newParent == null ? null : newParent._list );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_list.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_list.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "list" )
			_list.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "list" )
			return _list.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ADMPSTTN")]
public class DbAdvMapCTESettings : AdvMapSettings
{
	private UndoRedoDBPtr<DbAdvMapCTESettings> ___parent;
	[HideInOutliner]
	public new DBPtr<DbAdvMapCTESettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _altarName_A;
	private UndoRedo<string> _altarName_B;
	private UndoRedo<string> _dragonSpawnerName;
	private UndoRedo<string> _damageVariableName;
	private UndoRedoList<float> _damageAnimationTable;

	[Description( "скриптовое имя алтаря за доктов" )]
	public string altarName_A { get { return _altarName_A.Get(); } set { _altarName_A.Set( value ); } }

	[Description( "скриптовое имя алтаря за адорнийцев" )]
	public string altarName_B { get { return _altarName_B.Get(); } set { _altarName_B.Set( value ); } }

	[Description( "скриптовое имя спавнера дракона" )]
	public string dragonSpawnerName { get { return _dragonSpawnerName.Get(); } set { _dragonSpawnerName.Set( value ); } }

	[Description( "имя переменной в алтаре куда пишется дамаг" )]
	public string damageVariableName { get { return _damageVariableName.Get(); } set { _damageVariableName.Set( value ); } }

	[Description( "таблица для анимирования дамага по алтарю, нулевой элемент стартовая точка (0), дальше градации входящего дамага в секунду" )]
	public libdb.IChangeableList<float> damageAnimationTable { get { return _damageAnimationTable; } set { _damageAnimationTable.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DbAdvMapCTESettings>(owner);
		_altarName_A = new UndoRedo<string>( owner, string.Empty );
		_altarName_B = new UndoRedo<string>( owner, string.Empty );
		_dragonSpawnerName = new UndoRedo<string>( owner, string.Empty );
		_damageVariableName = new UndoRedo<string>( owner, string.Empty );
		_damageAnimationTable = new UndoRedoList<float>( owner );
		___parent.Changed += FireChangedEvent;
		_altarName_A.Changed += FireChangedEvent;
		_altarName_B.Changed += FireChangedEvent;
		_dragonSpawnerName.Changed += FireChangedEvent;
		_damageVariableName.Changed += FireChangedEvent;
		_damageAnimationTable.Changed += FireChangedEvent;
	}

	public DbAdvMapCTESettings()
	{
		Initialize( this );
	}
	private void AssignSelf( DbAdvMapCTESettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DbAdvMapCTESettings" );
		altarName_A = source.altarName_A;
		altarName_B = source.altarName_B;
		dragonSpawnerName = source.dragonSpawnerName;
		damageVariableName = source.damageVariableName;
		damageAnimationTable = source.damageAnimationTable;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DbAdvMapCTESettings source = _source as DbAdvMapCTESettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DbAdvMapCTESettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DbAdvMapCTESettings newParent = rawParent == null ? null : rawParent.Get<DbAdvMapCTESettings>();
		if ( newParent == null && _newParent is DbAdvMapCTESettings )
			newParent = _newParent as DbAdvMapCTESettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_altarName_A.SetParent( newParent == null ? null : newParent._altarName_A );
		_altarName_B.SetParent( newParent == null ? null : newParent._altarName_B );
		_dragonSpawnerName.SetParent( newParent == null ? null : newParent._dragonSpawnerName );
		_damageVariableName.SetParent( newParent == null ? null : newParent._damageVariableName );
		_damageAnimationTable.SetParent( newParent == null ? null : newParent._damageAnimationTable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_altarName_A.Reset();
		_altarName_B.Reset();
		_dragonSpawnerName.Reset();
		_damageVariableName.Reset();
		_damageAnimationTable.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_altarName_A.IsDerivedFromParent()
			&& _altarName_B.IsDerivedFromParent()
			&& _dragonSpawnerName.IsDerivedFromParent()
			&& _damageVariableName.IsDerivedFromParent()
			&& _damageAnimationTable.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "altarName_A" )
			_altarName_A.Reset();
		else if ( fieldName == "altarName_B" )
			_altarName_B.Reset();
		else if ( fieldName == "dragonSpawnerName" )
			_dragonSpawnerName.Reset();
		else if ( fieldName == "damageVariableName" )
			_damageVariableName.Reset();
		else if ( fieldName == "damageAnimationTable" )
			_damageAnimationTable.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "altarName_A" )
			return _altarName_A.IsDerivedFromParent();
		if ( fieldName == "altarName_B" )
			return _altarName_B.IsDerivedFromParent();
		if ( fieldName == "dragonSpawnerName" )
			return _dragonSpawnerName.IsDerivedFromParent();
		if ( fieldName == "damageVariableName" )
			return _damageVariableName.IsDerivedFromParent();
		if ( fieldName == "damageAnimationTable" )
			return _damageAnimationTable.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xEF91FBC0)]
[UseTypeName("DICT")]
public class DictionaryPreloadingResources : DBResource
{
	private UndoRedoDBPtr<DictionaryPreloadingResources> ___parent;
	[HideInOutliner]
	public new DBPtr<DictionaryPreloadingResources> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ResourceDesc> _resources;

	public libdb.IChangeableList<ResourceDesc> resources { get { return _resources; } set { _resources.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DictionaryPreloadingResources>(owner);
		_resources = new UndoRedoAssignableList<ResourceDesc>( owner );
		___parent.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
	}

	public DictionaryPreloadingResources()
	{
		Initialize( this );
	}
	private void AssignSelf( DictionaryPreloadingResources source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DictionaryPreloadingResources" );
		resources = source.resources;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DictionaryPreloadingResources source = _source as DictionaryPreloadingResources;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DictionaryPreloadingResources" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DictionaryPreloadingResources newParent = rawParent == null ? null : rawParent.Get<DictionaryPreloadingResources>();
		if ( newParent == null && _newParent is DictionaryPreloadingResources )
			newParent = _newParent as DictionaryPreloadingResources;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resources.SetParent( newParent == null ? null : newParent._resources );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resources.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resources.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resources" )
			_resources.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "resources" )
			return _resources.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class FWODVisualInfo : DBResource
{
	private UndoRedoDBPtr<FWODVisualInfo> ___parent;
	[HideInOutliner]
	public new DBPtr<FWODVisualInfo> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedoDBPtr<Texture> _iconSmall;
	private TextRef _tooltip;
	private TextRef _sessionTooltip;

	[Description( "Иконка первого вина для сессии большая" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Иконка первого вина. Мелкая для замка" )]
	public DBPtr<Texture> iconSmall { get { return _iconSmall.Get(); } set { _iconSmall.Set( value ); } }

	[Description( "тултип в замке" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "тултип" )]
	public TextRef sessionTooltip { get { return _sessionTooltip; } set { _sessionTooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FWODVisualInfo>(owner);
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_iconSmall = new UndoRedoDBPtr<Texture>( owner );
		_tooltip = new TextRef( owner, new TextRef() );
		_sessionTooltip = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_iconSmall.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_sessionTooltip.Changed += FireChangedEvent;
	}

	public FWODVisualInfo()
	{
		Initialize( this );
	}
	private void AssignSelf( FWODVisualInfo source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FWODVisualInfo" );
		icon = source.icon;
		iconSmall = source.iconSmall;
		tooltip = source.tooltip;
		sessionTooltip = source.sessionTooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FWODVisualInfo source = _source as FWODVisualInfo;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FWODVisualInfo" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FWODVisualInfo newParent = rawParent == null ? null : rawParent.Get<FWODVisualInfo>();
		if ( newParent == null && _newParent is FWODVisualInfo )
			newParent = _newParent as FWODVisualInfo;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_icon.SetParent( newParent == null ? null : newParent._icon );
		_iconSmall.SetParent( newParent == null ? null : newParent._iconSmall );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_sessionTooltip.SetParent( newParent == null ? null : newParent._sessionTooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_icon.Reset();
		_iconSmall.Reset();
		_tooltip.Reset();
		_sessionTooltip.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_icon.IsDerivedFromParent()
			&& _iconSmall.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _sessionTooltip.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "iconSmall" )
			_iconSmall.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "sessionTooltip" )
			_sessionTooltip.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "iconSmall" )
			return _iconSmall.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "sessionTooltip" )
			return _sessionTooltip.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[UseTypeName("GSSTTN")]
public class GameSvcSettings : DBResource
{
	private UndoRedoDBPtr<GameSvcSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<GameSvcSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _afkMessageTimer;
	private UndoRedo<int> _afkDisconnectTimer;
	private UndoRedo<float> _timeScale;

	[Description( "AFK massage timer (sec). Counts after last player's command. 0 = disable." )]
	public int afkMessageTimer { get { return _afkMessageTimer.Get(); } set { _afkMessageTimer.Set( value ); } }

	[Description( "AFK disconnect timer (sec). Counts after last player's command. 0 = disable." )]
	public int afkDisconnectTimer { get { return _afkDisconnectTimer.Get(); } set { _afkDisconnectTimer.Set( value ); } }

	[Description( "Predefined timescale (0.1-10.0). Will be applied even if changing timescale is disabled on server." )]
	public float timeScale { get { return _timeScale.Get(); } set { _timeScale.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GameSvcSettings>(owner);
		_afkMessageTimer = new UndoRedo<int>( owner, 0 );
		_afkDisconnectTimer = new UndoRedo<int>( owner, 0 );
		_timeScale = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_afkMessageTimer.Changed += FireChangedEvent;
		_afkDisconnectTimer.Changed += FireChangedEvent;
		_timeScale.Changed += FireChangedEvent;
	}

	public GameSvcSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( GameSvcSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GameSvcSettings" );
		afkMessageTimer = source.afkMessageTimer;
		afkDisconnectTimer = source.afkDisconnectTimer;
		timeScale = source.timeScale;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GameSvcSettings source = _source as GameSvcSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GameSvcSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GameSvcSettings newParent = rawParent == null ? null : rawParent.Get<GameSvcSettings>();
		if ( newParent == null && _newParent is GameSvcSettings )
			newParent = _newParent as GameSvcSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_afkMessageTimer.SetParent( newParent == null ? null : newParent._afkMessageTimer );
		_afkDisconnectTimer.SetParent( newParent == null ? null : newParent._afkDisconnectTimer );
		_timeScale.SetParent( newParent == null ? null : newParent._timeScale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_afkMessageTimer.Reset();
		_afkDisconnectTimer.Reset();
		_timeScale.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_afkMessageTimer.IsDerivedFromParent()
			&& _afkDisconnectTimer.IsDerivedFromParent()
			&& _timeScale.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "afkMessageTimer" )
			_afkMessageTimer.Reset();
		else if ( fieldName == "afkDisconnectTimer" )
			_afkDisconnectTimer.Reset();
		else if ( fieldName == "timeScale" )
			_timeScale.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "afkMessageTimer" )
			return _afkMessageTimer.IsDerivedFromParent();
		if ( fieldName == "afkDisconnectTimer" )
			return _afkDisconnectTimer.IsDerivedFromParent();
		if ( fieldName == "timeScale" )
			return _timeScale.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class GlyphManagerParams : DBResource
{
	private UndoRedoDBPtr<GlyphManagerParams> ___parent;
	[HideInOutliner]
	public new DBPtr<GlyphManagerParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private GlyphSettings _settings;
	private UndoRedoDBPtr<GlyphsDB> _glyphs;

	[Description( "Кастомные параметры спавна глифов" )]
	public GlyphSettings settings { get { return _settings; } set { _settings.Assign( value ); } }

	[Description( "Кастомный список глифов" )]
	public DBPtr<GlyphsDB> glyphs { get { return _glyphs.Get(); } set { _glyphs.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GlyphManagerParams>(owner);
		_settings = new GlyphSettings( owner );
		_glyphs = new UndoRedoDBPtr<GlyphsDB>( owner );
		___parent.Changed += FireChangedEvent;
		_settings.Changed += FireChangedEvent;
		_glyphs.Changed += FireChangedEvent;
	}

	public GlyphManagerParams()
	{
		Initialize( this );
	}
	private void AssignSelf( GlyphManagerParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GlyphManagerParams" );
		settings = source.settings;
		glyphs = source.glyphs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GlyphManagerParams source = _source as GlyphManagerParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GlyphManagerParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GlyphManagerParams newParent = rawParent == null ? null : rawParent.Get<GlyphManagerParams>();
		if ( newParent == null && _newParent is GlyphManagerParams )
			newParent = _newParent as GlyphManagerParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_settings.SetParent( newParent == null ? null : newParent._settings );
		_glyphs.SetParent( newParent == null ? null : newParent._glyphs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_settings.Reset();
		_glyphs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_settings.IsDerivedFromParent()
			&& _glyphs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "settings" )
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

[UseTypeName("HNP")]
public class HeroNaftaParams : DBResource
{
	private UndoRedoDBPtr<HeroNaftaParams> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroNaftaParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _naftaForKill;
	private ExecutableFloatString _naftaForAssist;
	private ExecutableFloatString _naftaSpecForKill;
	private ExecutableFloatString _teamNaftaForPresence;

	public ExecutableFloatString naftaForKill { get { return _naftaForKill; } set { _naftaForKill.Assign( value ); } }

	public ExecutableFloatString naftaForAssist { get { return _naftaForAssist; } set { _naftaForAssist.Assign( value ); } }

	public ExecutableFloatString naftaSpecForKill { get { return _naftaSpecForKill; } set { _naftaSpecForKill.Assign( value ); } }

	public ExecutableFloatString teamNaftaForPresence { get { return _teamNaftaForPresence; } set { _teamNaftaForPresence.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroNaftaParams>(owner);
		ExecutableFloatString __naftaForKill = new ExecutableFloatString(); // Construct default object for naftaForKill
		__naftaForKill.sString = "0.0f";
		_naftaForKill = new ExecutableFloatString( owner, __naftaForKill );
		ExecutableFloatString __naftaForAssist = new ExecutableFloatString(); // Construct default object for naftaForAssist
		__naftaForAssist.sString = "0.0f";
		_naftaForAssist = new ExecutableFloatString( owner, __naftaForAssist );
		ExecutableFloatString __naftaSpecForKill = new ExecutableFloatString(); // Construct default object for naftaSpecForKill
		__naftaSpecForKill.sString = "0.0f";
		_naftaSpecForKill = new ExecutableFloatString( owner, __naftaSpecForKill );
		ExecutableFloatString __teamNaftaForPresence = new ExecutableFloatString(); // Construct default object for teamNaftaForPresence
		__teamNaftaForPresence.sString = "0.0f";
		_teamNaftaForPresence = new ExecutableFloatString( owner, __teamNaftaForPresence );
		___parent.Changed += FireChangedEvent;
		_naftaForKill.Changed += FireChangedEvent;
		_naftaForAssist.Changed += FireChangedEvent;
		_naftaSpecForKill.Changed += FireChangedEvent;
		_teamNaftaForPresence.Changed += FireChangedEvent;
	}

	public HeroNaftaParams()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroNaftaParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroNaftaParams" );
		naftaForKill = source.naftaForKill;
		naftaForAssist = source.naftaForAssist;
		naftaSpecForKill = source.naftaSpecForKill;
		teamNaftaForPresence = source.teamNaftaForPresence;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroNaftaParams source = _source as HeroNaftaParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroNaftaParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroNaftaParams newParent = rawParent == null ? null : rawParent.Get<HeroNaftaParams>();
		if ( newParent == null && _newParent is HeroNaftaParams )
			newParent = _newParent as HeroNaftaParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_naftaForKill.SetParent( newParent == null ? null : newParent._naftaForKill );
		_naftaForAssist.SetParent( newParent == null ? null : newParent._naftaForAssist );
		_naftaSpecForKill.SetParent( newParent == null ? null : newParent._naftaSpecForKill );
		_teamNaftaForPresence.SetParent( newParent == null ? null : newParent._teamNaftaForPresence );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_naftaForKill.Reset();
		_naftaForAssist.Reset();
		_naftaSpecForKill.Reset();
		_teamNaftaForPresence.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_naftaForKill.IsDerivedFromParent()
			&& _naftaForAssist.IsDerivedFromParent()
			&& _naftaSpecForKill.IsDerivedFromParent()
			&& _teamNaftaForPresence.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "naftaForKill" )
			_naftaForKill.Reset();
		else if ( fieldName == "naftaForAssist" )
			_naftaForAssist.Reset();
		else if ( fieldName == "naftaSpecForKill" )
			_naftaSpecForKill.Reset();
		else if ( fieldName == "teamNaftaForPresence" )
			_teamNaftaForPresence.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "naftaForKill" )
			return _naftaForKill.IsDerivedFromParent();
		if ( fieldName == "naftaForAssist" )
			return _naftaForAssist.IsDerivedFromParent();
		if ( fieldName == "naftaSpecForKill" )
			return _naftaSpecForKill.IsDerivedFromParent();
		if ( fieldName == "teamNaftaForPresence" )
			return _teamNaftaForPresence.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9A9B7C40)]
[UseTypeName("SPOL")]
public class ScriptPolygonArea : GameObject
{
	private UndoRedoDBPtr<ScriptPolygonArea> ___parent;
	[HideInOutliner]
	public new DBPtr<ScriptPolygonArea> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Vec2> _points;
	private UndoRedoAssignableList<ScriptPolygonAreaPolygon> _polygons;

	public libdb.IChangeableList<Vec2> points { get { return _points; } set { _points.Assign( value ); } }

	public libdb.IChangeableList<ScriptPolygonAreaPolygon> polygons { get { return _polygons; } set { _polygons.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScriptPolygonArea>(owner);
		_points = new UndoRedoAssignableList<Vec2>( owner );
		_polygons = new UndoRedoAssignableList<ScriptPolygonAreaPolygon>( owner );
		___parent.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		_polygons.Changed += FireChangedEvent;
	}

	public ScriptPolygonArea()
	{
		Initialize( this );
	}
	private void AssignSelf( ScriptPolygonArea source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScriptPolygonArea" );
		points = source.points;
		polygons = source.polygons;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScriptPolygonArea source = _source as ScriptPolygonArea;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScriptPolygonArea" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScriptPolygonArea newParent = rawParent == null ? null : rawParent.Get<ScriptPolygonArea>();
		if ( newParent == null && _newParent is ScriptPolygonArea )
			newParent = _newParent as ScriptPolygonArea;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_points.SetParent( newParent == null ? null : newParent._points );
		_polygons.SetParent( newParent == null ? null : newParent._polygons );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_points.Reset();
		_polygons.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_points.IsDerivedFromParent()
			&& _polygons.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "points" )
			_points.Reset();
		else if ( fieldName == "polygons" )
			_polygons.Reset();
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
		if ( fieldName == "polygons" )
			return _polygons.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
