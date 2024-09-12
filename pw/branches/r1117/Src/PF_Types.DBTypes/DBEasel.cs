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
public enum DBEaselDropState
{
	Idle = 0,
	Move = 1,
	Dead = 2,
	MoveUnderground = 3,
	JumpIn = 4,
};

public enum EBoostsCategory
{
	Easy = 0,
	Medium = 1,
	Hard = 2,
};

public enum EBoostType
{
	Unknown = 0,
	PaintBlast = 1,
	Freeze = 2,
	Joker = 3,
	Inspiration = 4,
	Brightening = 5,
	Sorter = 6,
	Magnet = 7,
	Alchemist = 8,
};

public enum EBoostUsage
{
	Unknown = 0,
	InGame = 1,
	AtExit = 2,
};

public enum EChainsStatisticsType
{
	first_visible_chain = 0,
	all_visible_balls = 1,
	all_chains = 2,
};

public enum EColor
{
	black = 0,
	blue = 1,
	green = 2,
	red = 3,
	white = 4,
	cyan = 5,
	yellow = 6,
	magenta = 7,
	any = 8,
};

public enum EComboType
{
	none = 0,
	x2 = 1,
	x3 = 2,
	x4 = 3,
	x6 = 4,
	x8 = 5,
	x9 = 6,
	x16 = 7,
	plus3 = 8,
	plus10 = 9,
	plus20 = 10,
	godlike = 11,
};

public enum ECursor
{
	aim = 0,
	paintblast = 1,
};

public enum EDifficultyLevel
{
	Unknown = 0,
	Easy = 1,
	Medium = 2,
	Hard = 3,
	Impossible = 4,
};

public enum EEaselRoundStatus
{
	Uninitialized = 0,
	Incomplete = 1,
	Won = 2,
	Failed = 3,
	Canceled = 4,
	CanceledBySession = 5,
};

public enum EEaselSoundType
{
	ballfired = 0,
	ballhit = 1,
	ballmiss = 2,
	ballcolorchanged = 3,
	ballexploded = 4,
	ballhit_color_match = 5,
	ballhit_color_missmatch = 6,
	game_win = 7,
	game_loose = 8,
	boost_brighten_click = 9,
	boost_freeze_click = 10,
	boost_inspire_click = 11,
	boost_joker_click = 12,
	boost_paintblast_click = 13,
	boost_paintblast_explosion = 14,
	boost_speedball_click = 15,
	boost_speedball_fired = 16,
	explosion_combo_2x = 17,
	explosion_combo_3x = 18,
	explosion_combo_4x = 19,
	explosion_combo_5x = 20,
	paint_flow = 21,
	chains_moving = 22,
	drop_sliding_low = 23,
	drop_sliding_high = 24,
	level_scroll_start = 25,
	level_scroll_end = 26,
	chain_near_exit = 27,
	chain_near_exit_zz = 28,
	chain_reached_end = 29,
	chain_destroyed = 30,
	chain_merged = 31,
	result_gold_medal = 32,
	result_silver_medal = 33,
	scorpion_start = 34,
	new_boost_obtained = 35,
	ball_in_tunnel = 36,
	ball_out_tunnel = 37,
	tunnel_appeared = 38,
	coin_catched = 39,
	boost_sorter_click = 40,
};

public enum EFallingObject
{
	coin = 0,
};

public enum EPaintType
{
	type_0 = 0,
	type_1 = 1,
	type_2 = 2,
	type_3 = 3,
	type_4 = 4,
};

public enum EPriestessLevel
{
	level_0 = 0,
	level_1 = 1,
	level_2 = 2,
	level_3 = 3,
	level_4 = 4,
	level_5 = 5,
	level_6 = 6,
	level_7 = 7,
	level_8 = 8,
	level_9 = 9,
	level_10 = 10,
	level_11 = 11,
	level_12 = 12,
	level_13 = 13,
	level_14 = 14,
	level_15 = 15,
};

public enum WonGameHearts
{
	Level = 0,
	SilverMedal = 1,
	GoldMedal = 2,
	GoldOverSilverMedal = 3,
};

public enum WonGameMedal
{
	None = 0,
	Silver = 1,
	Gold = 2,
};

public class BallVelocities : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BallVelocities __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _bulletVelocity;
	private UndoRedo<float> _bulletPointerVelocity;
	private UndoRedo<float> _ballInChainVelocity;

	[Description( "Bullet velocity" )]
	public float bulletVelocity { get { return _bulletVelocity.Get(); } set { _bulletVelocity.Set( value ); } }

	[Description( "Bullet velocity with Palette (Laser Pointer) Bidon" )]
	public float bulletPointerVelocity { get { return _bulletPointerVelocity.Get(); } set { _bulletPointerVelocity.Set( value ); } }

	[Description( "Bullet velocity in chain" )]
	public float ballInChainVelocity { get { return _ballInChainVelocity.Get(); } set { _ballInChainVelocity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_bulletVelocity = new UndoRedo<float>( owner, 150000.0f );
		_bulletPointerVelocity = new UndoRedo<float>( owner, 1500000.0f );
		_ballInChainVelocity = new UndoRedo<float>( owner, 10000.0f );
		_bulletVelocity.Changed += FireChangedEvent;
		_bulletPointerVelocity.Changed += FireChangedEvent;
		_ballInChainVelocity.Changed += FireChangedEvent;
	}

	public BallVelocities()
	{
		Initialize( GetOwner() );
	}

	public BallVelocities( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BallVelocities( DBResource owner, BallVelocities source )
		: this(owner, source, true){}

	protected BallVelocities( DBResource owner, BallVelocities source, bool fireEvent )
	{
		_bulletVelocity = new UndoRedo<float>( owner, source.bulletVelocity );
		_bulletPointerVelocity = new UndoRedo<float>( owner, source.bulletPointerVelocity );
		_ballInChainVelocity = new UndoRedo<float>( owner, source.ballInChainVelocity );
		_bulletVelocity.Changed += FireChangedEvent;
		_bulletPointerVelocity.Changed += FireChangedEvent;
		_ballInChainVelocity.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BallVelocities source = _source as BallVelocities;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BallVelocities" );
		bulletVelocity = source.bulletVelocity;
		bulletPointerVelocity = source.bulletPointerVelocity;
		ballInChainVelocity = source.ballInChainVelocity;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BallVelocities newParent = _newParent as BallVelocities;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_bulletVelocity.SetParent( newParent == null ? null : newParent._bulletVelocity );
		_bulletPointerVelocity.SetParent( newParent == null ? null : newParent._bulletPointerVelocity );
		_ballInChainVelocity.SetParent( newParent == null ? null : newParent._ballInChainVelocity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_bulletVelocity.Reset();
		_bulletPointerVelocity.Reset();
		_ballInChainVelocity.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_bulletVelocity.IsDerivedFromParent()
			&& _bulletPointerVelocity.IsDerivedFromParent()
			&& _ballInChainVelocity.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "bulletVelocity" )
			_bulletVelocity.Reset();
		else if ( fieldName == "bulletPointerVelocity" )
			_bulletPointerVelocity.Reset();
		else if ( fieldName == "ballInChainVelocity" )
			_ballInChainVelocity.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "bulletVelocity" )
			return _bulletVelocity.IsDerivedFromParent();
		if ( fieldName == "bulletPointerVelocity" )
			return _bulletPointerVelocity.IsDerivedFromParent();
		if ( fieldName == "ballInChainVelocity" )
			return _ballInChainVelocity.IsDerivedFromParent();
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

public class ChainGate : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ChainGate __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _valid;
	private UndoRedo<int> _startChainId;
	private UndoRedo<int> _endChainId;

	public bool valid { get { return _valid.Get(); } set { _valid.Set( value ); } }

	public int startChainId { get { return _startChainId.Get(); } set { _startChainId.Set( value ); } }

	public int endChainId { get { return _endChainId.Get(); } set { _endChainId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_valid = new UndoRedo<bool>( owner, false );
		_startChainId = new UndoRedo<int>( owner, 0 );
		_endChainId = new UndoRedo<int>( owner, 0 );
		_valid.Changed += FireChangedEvent;
		_startChainId.Changed += FireChangedEvent;
		_endChainId.Changed += FireChangedEvent;
	}

	public ChainGate()
	{
		Initialize( GetOwner() );
	}

	public ChainGate( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ChainGate( DBResource owner, ChainGate source )
		: this(owner, source, true){}

	protected ChainGate( DBResource owner, ChainGate source, bool fireEvent )
	{
		_valid = new UndoRedo<bool>( owner, source.valid );
		_startChainId = new UndoRedo<int>( owner, source.startChainId );
		_endChainId = new UndoRedo<int>( owner, source.endChainId );
		_valid.Changed += FireChangedEvent;
		_startChainId.Changed += FireChangedEvent;
		_endChainId.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ChainGate source = _source as ChainGate;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChainGate" );
		valid = source.valid;
		startChainId = source.startChainId;
		endChainId = source.endChainId;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ChainGate newParent = _newParent as ChainGate;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_valid.SetParent( newParent == null ? null : newParent._valid );
		_startChainId.SetParent( newParent == null ? null : newParent._startChainId );
		_endChainId.SetParent( newParent == null ? null : newParent._endChainId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_valid.Reset();
		_startChainId.Reset();
		_endChainId.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_valid.IsDerivedFromParent()
			&& _startChainId.IsDerivedFromParent()
			&& _endChainId.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "valid" )
			_valid.Reset();
		else if ( fieldName == "startChainId" )
			_startChainId.Reset();
		else if ( fieldName == "endChainId" )
			_endChainId.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "valid" )
			return _valid.IsDerivedFromParent();
		if ( fieldName == "startChainId" )
			return _startChainId.IsDerivedFromParent();
		if ( fieldName == "endChainId" )
			return _endChainId.IsDerivedFromParent();
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

public class BulletStatistics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BulletStatistics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _drillerGatePassed;
	private ChainGate _drillerGate;
	private UndoRedo<int> _gatesPassed;

	public bool drillerGatePassed { get { return _drillerGatePassed.Get(); } set { _drillerGatePassed.Set( value ); } }

	public ChainGate drillerGate { get { return _drillerGate; } set { _drillerGate.Assign( value ); } }

	public int gatesPassed { get { return _gatesPassed.Get(); } set { _gatesPassed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_drillerGatePassed = new UndoRedo<bool>( owner, false );
		_drillerGate = new ChainGate( owner );
		_gatesPassed = new UndoRedo<int>( owner, 0 );
		_drillerGatePassed.Changed += FireChangedEvent;
		_drillerGate.Changed += FireChangedEvent;
		_gatesPassed.Changed += FireChangedEvent;
	}

	public BulletStatistics()
	{
		Initialize( GetOwner() );
	}

	public BulletStatistics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BulletStatistics( DBResource owner, BulletStatistics source )
		: this(owner, source, true){}

	protected BulletStatistics( DBResource owner, BulletStatistics source, bool fireEvent )
	{
		_drillerGatePassed = new UndoRedo<bool>( owner, source.drillerGatePassed );
		_drillerGate = new ChainGate( owner, source.drillerGate );
		_gatesPassed = new UndoRedo<int>( owner, source.gatesPassed );
		_drillerGatePassed.Changed += FireChangedEvent;
		_drillerGate.Changed += FireChangedEvent;
		_gatesPassed.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BulletStatistics source = _source as BulletStatistics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BulletStatistics" );
		drillerGatePassed = source.drillerGatePassed;
		drillerGate = source.drillerGate;
		gatesPassed = source.gatesPassed;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BulletStatistics newParent = _newParent as BulletStatistics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_drillerGatePassed.SetParent( newParent == null ? null : newParent._drillerGatePassed );
		_drillerGate.SetParent( newParent == null ? null : newParent._drillerGate );
		_gatesPassed.SetParent( newParent == null ? null : newParent._gatesPassed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_drillerGatePassed.Reset();
		_drillerGate.Reset();
		_gatesPassed.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_drillerGatePassed.IsDerivedFromParent()
			&& _drillerGate.IsDerivedFromParent()
			&& _gatesPassed.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "drillerGatePassed" )
			_drillerGatePassed.Reset();
		else if ( fieldName == "drillerGate" )
			_drillerGate.Reset();
		else if ( fieldName == "gatesPassed" )
			_gatesPassed.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "drillerGatePassed" )
			return _drillerGatePassed.IsDerivedFromParent();
		if ( fieldName == "drillerGate" )
			return _drillerGate.IsDerivedFromParent();
		if ( fieldName == "gatesPassed" )
			return _gatesPassed.IsDerivedFromParent();
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

public class Coin : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Coin __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _fallingPercentage;
	private UndoRedo<float> _catchRadius;
	private UndoRedo<float> _gravity;
	private UndoRedo<float> _jumpSpeed;
	private UndoRedo<float> _zLift;

	[MinMaxSize(0, 100)]
	public int fallingPercentage { get { return _fallingPercentage.Get(); } set { _fallingPercentage.Set( value ); } }

	public float catchRadius { get { return _catchRadius.Get(); } set { _catchRadius.Set( value ); } }

	public float gravity { get { return _gravity.Get(); } set { _gravity.Set( value ); } }

	public float jumpSpeed { get { return _jumpSpeed.Get(); } set { _jumpSpeed.Set( value ); } }

	public float zLift { get { return _zLift.Get(); } set { _zLift.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_fallingPercentage = new UndoRedo<int>( owner, 5 );
		_catchRadius = new UndoRedo<float>( owner, 1.0f );
		_gravity = new UndoRedo<float>( owner, 10.0f );
		_jumpSpeed = new UndoRedo<float>( owner, 10.0f );
		_zLift = new UndoRedo<float>( owner, 3.0f );
		_fallingPercentage.Changed += FireChangedEvent;
		_catchRadius.Changed += FireChangedEvent;
		_gravity.Changed += FireChangedEvent;
		_jumpSpeed.Changed += FireChangedEvent;
		_zLift.Changed += FireChangedEvent;
	}

	public Coin()
	{
		Initialize( GetOwner() );
	}

	public Coin( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Coin( DBResource owner, Coin source )
		: this(owner, source, true){}

	protected Coin( DBResource owner, Coin source, bool fireEvent )
	{
		_fallingPercentage = new UndoRedo<int>( owner, source.fallingPercentage );
		_catchRadius = new UndoRedo<float>( owner, source.catchRadius );
		_gravity = new UndoRedo<float>( owner, source.gravity );
		_jumpSpeed = new UndoRedo<float>( owner, source.jumpSpeed );
		_zLift = new UndoRedo<float>( owner, source.zLift );
		_fallingPercentage.Changed += FireChangedEvent;
		_catchRadius.Changed += FireChangedEvent;
		_gravity.Changed += FireChangedEvent;
		_jumpSpeed.Changed += FireChangedEvent;
		_zLift.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Coin source = _source as Coin;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Coin" );
		fallingPercentage = source.fallingPercentage;
		catchRadius = source.catchRadius;
		gravity = source.gravity;
		jumpSpeed = source.jumpSpeed;
		zLift = source.zLift;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Coin newParent = _newParent as Coin;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_fallingPercentage.SetParent( newParent == null ? null : newParent._fallingPercentage );
		_catchRadius.SetParent( newParent == null ? null : newParent._catchRadius );
		_gravity.SetParent( newParent == null ? null : newParent._gravity );
		_jumpSpeed.SetParent( newParent == null ? null : newParent._jumpSpeed );
		_zLift.SetParent( newParent == null ? null : newParent._zLift );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_fallingPercentage.Reset();
		_catchRadius.Reset();
		_gravity.Reset();
		_jumpSpeed.Reset();
		_zLift.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_fallingPercentage.IsDerivedFromParent()
			&& _catchRadius.IsDerivedFromParent()
			&& _gravity.IsDerivedFromParent()
			&& _jumpSpeed.IsDerivedFromParent()
			&& _zLift.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "fallingPercentage" )
			_fallingPercentage.Reset();
		else if ( fieldName == "catchRadius" )
			_catchRadius.Reset();
		else if ( fieldName == "gravity" )
			_gravity.Reset();
		else if ( fieldName == "jumpSpeed" )
			_jumpSpeed.Reset();
		else if ( fieldName == "zLift" )
			_zLift.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "fallingPercentage" )
			return _fallingPercentage.IsDerivedFromParent();
		if ( fieldName == "catchRadius" )
			return _catchRadius.IsDerivedFromParent();
		if ( fieldName == "gravity" )
			return _gravity.IsDerivedFromParent();
		if ( fieldName == "jumpSpeed" )
			return _jumpSpeed.IsDerivedFromParent();
		if ( fieldName == "zLift" )
			return _zLift.IsDerivedFromParent();
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

public class DBBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<int> _accesslevel;
	private UndoRedo<int> _cooldown;
	private UndoRedo<int> _price;

	[Category( "Boost base parameters" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[IntMin(0)]
	public int accesslevel { get { return _accesslevel.Get(); } set { _accesslevel.Set( value ); } }

	[IntMin(0)]
	public int cooldown { get { return _cooldown.Get(); } set { _cooldown.Set( value ); } }

	[IntMin(0)]
	public int price { get { return _price.Get(); } set { _price.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, "Unknown" );
		_accesslevel = new UndoRedo<int>( owner, 0 );
		_cooldown = new UndoRedo<int>( owner, 0 );
		_price = new UndoRedo<int>( owner, 0 );
		_name.Changed += FireChangedEvent;
		_accesslevel.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
	}

	public DBBoost()
	{
		Initialize( GetOwner() );
	}

	public DBBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBBoost( DBResource owner, DBBoost source )
		: this(owner, source, true){}

	protected DBBoost( DBResource owner, DBBoost source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_accesslevel = new UndoRedo<int>( owner, source.accesslevel );
		_cooldown = new UndoRedo<int>( owner, source.cooldown );
		_price = new UndoRedo<int>( owner, source.price );
		_name.Changed += FireChangedEvent;
		_accesslevel.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBBoost source = _source as DBBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBBoost" );
		name = source.name;
		accesslevel = source.accesslevel;
		cooldown = source.cooldown;
		price = source.price;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBBoost newParent = _newParent as DBBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_accesslevel.SetParent( newParent == null ? null : newParent._accesslevel );
		_cooldown.SetParent( newParent == null ? null : newParent._cooldown );
		_price.SetParent( newParent == null ? null : newParent._price );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_accesslevel.Reset();
		_cooldown.Reset();
		_price.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _accesslevel.IsDerivedFromParent()
			&& _cooldown.IsDerivedFromParent()
			&& _price.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "accesslevel" )
			_accesslevel.Reset();
		else if ( fieldName == "cooldown" )
			_cooldown.Reset();
		else if ( fieldName == "price" )
			_price.Reset();
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
		if ( fieldName == "accesslevel" )
			return _accesslevel.IsDerivedFromParent();
		if ( fieldName == "cooldown" )
			return _cooldown.IsDerivedFromParent();
		if ( fieldName == "price" )
			return _price.IsDerivedFromParent();
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

public class DBBoard : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBBoard __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _width;
	private UndoRedo<int> _height;

	[Category( "Game board parameters" )]
	[IntMinMax(0, 10000)]
	public int width { get { return _width.Get(); } set { _width.Set( value ); } }

	[IntMinMax(0, 10000)]
	public int height { get { return _height.Get(); } set { _height.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_width = new UndoRedo<int>( owner, 10000 );
		_height = new UndoRedo<int>( owner, 10000 );
		_width.Changed += FireChangedEvent;
		_height.Changed += FireChangedEvent;
	}

	public DBBoard()
	{
		Initialize( GetOwner() );
	}

	public DBBoard( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBBoard( DBResource owner, DBBoard source )
		: this(owner, source, true){}

	protected DBBoard( DBResource owner, DBBoard source, bool fireEvent )
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
		DBBoard source = _source as DBBoard;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBBoard" );
		width = source.width;
		height = source.height;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBBoard newParent = _newParent as DBBoard;
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

public class DBAlchemistBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBAlchemistBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;
	private UndoRedo<int> _alchemistDuration;
	private UndoRedo<int> _additionalPaint;
	private UndoRedo<float> _paintMult;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	[IntMin(0)]
	public int alchemistDuration { get { return _alchemistDuration.Get(); } set { _alchemistDuration.Set( value ); } }

	public int additionalPaint { get { return _additionalPaint.Get(); } set { _additionalPaint.Set( value ); } }

	public float paintMult { get { return _paintMult.Get(); } set { _paintMult.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_alchemistDuration = new UndoRedo<int>( owner, 0 );
		_additionalPaint = new UndoRedo<int>( owner, 0 );
		_paintMult = new UndoRedo<float>( owner, 1.0f );
		_boostBase.Changed += FireChangedEvent;
		_alchemistDuration.Changed += FireChangedEvent;
		_additionalPaint.Changed += FireChangedEvent;
		_paintMult.Changed += FireChangedEvent;
	}

	public DBAlchemistBoost()
	{
		Initialize( GetOwner() );
	}

	public DBAlchemistBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBAlchemistBoost( DBResource owner, DBAlchemistBoost source )
		: this(owner, source, true){}

	protected DBAlchemistBoost( DBResource owner, DBAlchemistBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_alchemistDuration = new UndoRedo<int>( owner, source.alchemistDuration );
		_additionalPaint = new UndoRedo<int>( owner, source.additionalPaint );
		_paintMult = new UndoRedo<float>( owner, source.paintMult );
		_boostBase.Changed += FireChangedEvent;
		_alchemistDuration.Changed += FireChangedEvent;
		_additionalPaint.Changed += FireChangedEvent;
		_paintMult.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBAlchemistBoost source = _source as DBAlchemistBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBAlchemistBoost" );
		boostBase = source.boostBase;
		alchemistDuration = source.alchemistDuration;
		additionalPaint = source.additionalPaint;
		paintMult = source.paintMult;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBAlchemistBoost newParent = _newParent as DBAlchemistBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		_alchemistDuration.SetParent( newParent == null ? null : newParent._alchemistDuration );
		_additionalPaint.SetParent( newParent == null ? null : newParent._additionalPaint );
		_paintMult.SetParent( newParent == null ? null : newParent._paintMult );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
		_alchemistDuration.Reset();
		_additionalPaint.Reset();
		_paintMult.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			&& _alchemistDuration.IsDerivedFromParent()
			&& _additionalPaint.IsDerivedFromParent()
			&& _paintMult.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else if ( fieldName == "alchemistDuration" )
			_alchemistDuration.Reset();
		else if ( fieldName == "additionalPaint" )
			_additionalPaint.Reset();
		else if ( fieldName == "paintMult" )
			_paintMult.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
		if ( fieldName == "alchemistDuration" )
			return _alchemistDuration.IsDerivedFromParent();
		if ( fieldName == "additionalPaint" )
			return _additionalPaint.IsDerivedFromParent();
		if ( fieldName == "paintMult" )
			return _paintMult.IsDerivedFromParent();
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

public class DBBoostTemplate : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBBoostTemplate __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EBoostUsage> _boostUsage;
	private UndoRedo<EBoostsCategory> _boostCategory;

	public EBoostUsage boostUsage { get { return _boostUsage.Get(); } set { _boostUsage.Set( value ); } }

	public EBoostsCategory boostCategory { get { return _boostCategory.Get(); } set { _boostCategory.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostUsage = new UndoRedo<EBoostUsage>( owner, EBoostUsage.Unknown );
		_boostCategory = new UndoRedo<EBoostsCategory>( owner, EBoostsCategory.Easy );
		_boostUsage.Changed += FireChangedEvent;
		_boostCategory.Changed += FireChangedEvent;
	}

	public DBBoostTemplate()
	{
		Initialize( GetOwner() );
	}

	public DBBoostTemplate( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBBoostTemplate( DBResource owner, DBBoostTemplate source )
		: this(owner, source, true){}

	protected DBBoostTemplate( DBResource owner, DBBoostTemplate source, bool fireEvent )
	{
		_boostUsage = new UndoRedo<EBoostUsage>( owner, source.boostUsage );
		_boostCategory = new UndoRedo<EBoostsCategory>( owner, source.boostCategory );
		_boostUsage.Changed += FireChangedEvent;
		_boostCategory.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBBoostTemplate source = _source as DBBoostTemplate;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBBoostTemplate" );
		boostUsage = source.boostUsage;
		boostCategory = source.boostCategory;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBBoostTemplate newParent = _newParent as DBBoostTemplate;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostUsage.SetParent( newParent == null ? null : newParent._boostUsage );
		_boostCategory.SetParent( newParent == null ? null : newParent._boostCategory );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostUsage.Reset();
		_boostCategory.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostUsage.IsDerivedFromParent()
			&& _boostCategory.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostUsage" )
			_boostUsage.Reset();
		else if ( fieldName == "boostCategory" )
			_boostCategory.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostUsage" )
			return _boostUsage.IsDerivedFromParent();
		if ( fieldName == "boostCategory" )
			return _boostCategory.IsDerivedFromParent();
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

public class DBFreezeBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBFreezeBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;
	private UndoRedo<int> _seconds;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	[IntMin(0)]
	public int seconds { get { return _seconds.Get(); } set { _seconds.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_seconds = new UndoRedo<int>( owner, 0 );
		_boostBase.Changed += FireChangedEvent;
		_seconds.Changed += FireChangedEvent;
	}

	public DBFreezeBoost()
	{
		Initialize( GetOwner() );
	}

	public DBFreezeBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBFreezeBoost( DBResource owner, DBFreezeBoost source )
		: this(owner, source, true){}

	protected DBFreezeBoost( DBResource owner, DBFreezeBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_seconds = new UndoRedo<int>( owner, source.seconds );
		_boostBase.Changed += FireChangedEvent;
		_seconds.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBFreezeBoost source = _source as DBFreezeBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBFreezeBoost" );
		boostBase = source.boostBase;
		seconds = source.seconds;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBFreezeBoost newParent = _newParent as DBFreezeBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		_seconds.SetParent( newParent == null ? null : newParent._seconds );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
		_seconds.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			&& _seconds.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else if ( fieldName == "seconds" )
			_seconds.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
		if ( fieldName == "seconds" )
			return _seconds.IsDerivedFromParent();
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

public class DBBrighteningBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBBrighteningBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;
	private UndoRedo<int> _ballsnum;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	[IntMin(0)]
	public int ballsnum { get { return _ballsnum.Get(); } set { _ballsnum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_ballsnum = new UndoRedo<int>( owner, 0 );
		_boostBase.Changed += FireChangedEvent;
		_ballsnum.Changed += FireChangedEvent;
	}

	public DBBrighteningBoost()
	{
		Initialize( GetOwner() );
	}

	public DBBrighteningBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBBrighteningBoost( DBResource owner, DBBrighteningBoost source )
		: this(owner, source, true){}

	protected DBBrighteningBoost( DBResource owner, DBBrighteningBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_ballsnum = new UndoRedo<int>( owner, source.ballsnum );
		_boostBase.Changed += FireChangedEvent;
		_ballsnum.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBBrighteningBoost source = _source as DBBrighteningBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBBrighteningBoost" );
		boostBase = source.boostBase;
		ballsnum = source.ballsnum;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBBrighteningBoost newParent = _newParent as DBBrighteningBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		_ballsnum.SetParent( newParent == null ? null : newParent._ballsnum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
		_ballsnum.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			&& _ballsnum.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else if ( fieldName == "ballsnum" )
			_ballsnum.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
		if ( fieldName == "ballsnum" )
			return _ballsnum.IsDerivedFromParent();
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
public class DBEaselArtifacts : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselArtifacts __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<Consumable>> _artifact;
	private UndoRedoAssignableList<DBPtr<SingleStateObject>> _scroll;

	[Category( "Easel artifacts parameters" )]
	public libdb.IChangeableList<DBPtr<Consumable>> artifact { get { return _artifact; } set { _artifact.Assign( value ); } }

	[Category( "Easel scrolls" )]
	public libdb.IChangeableList<DBPtr<SingleStateObject>> scroll { get { return _scroll; } set { _scroll.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_artifact = new UndoRedoAssignableList<DBPtr<Consumable>>( owner );
		_scroll = new UndoRedoAssignableList<DBPtr<SingleStateObject>>( owner );
		_artifact.Changed += FireChangedEvent;
		_scroll.Changed += FireChangedEvent;
	}

	public DBEaselArtifacts()
	{
		Initialize( GetOwner() );
	}

	public DBEaselArtifacts( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselArtifacts( DBResource owner, DBEaselArtifacts source )
		: this(owner, source, true){}

	protected DBEaselArtifacts( DBResource owner, DBEaselArtifacts source, bool fireEvent )
	{
		_artifact = new UndoRedoAssignableList<DBPtr<Consumable>>( owner );
		_artifact.Assign( source.artifact );
		_scroll = new UndoRedoAssignableList<DBPtr<SingleStateObject>>( owner );
		_scroll.Assign( source.scroll );
		_artifact.Changed += FireChangedEvent;
		_scroll.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselArtifacts source = _source as DBEaselArtifacts;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselArtifacts" );
		artifact = source.artifact;
		scroll = source.scroll;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselArtifacts newParent = _newParent as DBEaselArtifacts;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_artifact.SetParent( newParent == null ? null : newParent._artifact );
		_scroll.SetParent( newParent == null ? null : newParent._scroll );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_artifact.Reset();
		_scroll.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_artifact.IsDerivedFromParent()
			&& _scroll.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "artifact" )
			_artifact.Reset();
		else if ( fieldName == "scroll" )
			_scroll.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "artifact" )
			return _artifact.IsDerivedFromParent();
		if ( fieldName == "scroll" )
			return _scroll.IsDerivedFromParent();
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

public class DBEaselBallsView : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselBallsView __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _colorBalls;
	private UndoRedoList<string> _switchToAnimation;
	private UndoRedoList<float> _animationsBaseSpeed;
	private UndoRedoList<float> _animationsSpeedModifier;
	private UndoRedoDBPtr<BasicEffectStandalone> _paintBlastBall;
	private UndoRedoDBPtr<BasicEffectStandalone> _paintBlastBallFlying;
	private UndoRedoDBPtr<DBSceneObject> _jokerBall;
	private UndoRedo<float> _shadowRotation;
	private UndoRedo<float> _shadowOpacityChangeSpeed;

	[EnumArray(typeof(EColor))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> colorBalls { get { return _colorBalls; } set { _colorBalls.Assign( value ); } }

	[EnumArray(typeof(DBEaselDropState))]
	public libdb.IChangeableList<string> switchToAnimation { get { return _switchToAnimation; } set { _switchToAnimation.Assign( value ); } }

	[EnumArray(typeof(DBEaselDropState))]
	public libdb.IChangeableList<float> animationsBaseSpeed { get { return _animationsBaseSpeed; } set { _animationsBaseSpeed.Assign( value ); } }

	[EnumArray(typeof(DBEaselDropState))]
	public libdb.IChangeableList<float> animationsSpeedModifier { get { return _animationsSpeedModifier; } set { _animationsSpeedModifier.Assign( value ); } }

	public DBPtr<BasicEffectStandalone> paintBlastBall { get { return _paintBlastBall.Get(); } set { _paintBlastBall.Set( value ); } }

	public DBPtr<BasicEffectStandalone> paintBlastBallFlying { get { return _paintBlastBallFlying.Get(); } set { _paintBlastBallFlying.Set( value ); } }

	public DBPtr<DBSceneObject> jokerBall { get { return _jokerBall.Get(); } set { _jokerBall.Set( value ); } }

	public float shadowRotation { get { return _shadowRotation.Get(); } set { _shadowRotation.Set( value ); } }

	public float shadowOpacityChangeSpeed { get { return _shadowOpacityChangeSpeed.Get(); } set { _shadowOpacityChangeSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_colorBalls = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( EColor ) );
		_switchToAnimation = new UndoRedoList<string>( owner, typeof( DBEaselDropState ) );
		_animationsBaseSpeed = new UndoRedoList<float>( owner, typeof( DBEaselDropState ) );
		_animationsSpeedModifier = new UndoRedoList<float>( owner, typeof( DBEaselDropState ) );
		_paintBlastBall = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_paintBlastBallFlying = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_jokerBall = new UndoRedoDBPtr<DBSceneObject>( owner );
		_shadowRotation = new UndoRedo<float>( owner, 0.0f );
		_shadowOpacityChangeSpeed = new UndoRedo<float>( owner, 1.0f );
		_colorBalls.Changed += FireChangedEvent;
		_switchToAnimation.Changed += FireChangedEvent;
		_animationsBaseSpeed.Changed += FireChangedEvent;
		_animationsSpeedModifier.Changed += FireChangedEvent;
		_paintBlastBall.Changed += FireChangedEvent;
		_paintBlastBallFlying.Changed += FireChangedEvent;
		_jokerBall.Changed += FireChangedEvent;
		_shadowRotation.Changed += FireChangedEvent;
		_shadowOpacityChangeSpeed.Changed += FireChangedEvent;
	}

	public DBEaselBallsView()
	{
		Initialize( GetOwner() );
	}

	public DBEaselBallsView( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselBallsView( DBResource owner, DBEaselBallsView source )
		: this(owner, source, true){}

	protected DBEaselBallsView( DBResource owner, DBEaselBallsView source, bool fireEvent )
	{
		_colorBalls = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( EColor ) );
		_colorBalls.Assign( source.colorBalls );
		_switchToAnimation = new UndoRedoList<string>( owner, typeof( DBEaselDropState ) );
		_switchToAnimation.Assign( source.switchToAnimation );
		_animationsBaseSpeed = new UndoRedoList<float>( owner, typeof( DBEaselDropState ) );
		_animationsBaseSpeed.Assign( source.animationsBaseSpeed );
		_animationsSpeedModifier = new UndoRedoList<float>( owner, typeof( DBEaselDropState ) );
		_animationsSpeedModifier.Assign( source.animationsSpeedModifier );
		_paintBlastBall = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.paintBlastBall );
		_paintBlastBallFlying = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.paintBlastBallFlying );
		_jokerBall = new UndoRedoDBPtr<DBSceneObject>( owner, source.jokerBall );
		_shadowRotation = new UndoRedo<float>( owner, source.shadowRotation );
		_shadowOpacityChangeSpeed = new UndoRedo<float>( owner, source.shadowOpacityChangeSpeed );
		_colorBalls.Changed += FireChangedEvent;
		_switchToAnimation.Changed += FireChangedEvent;
		_animationsBaseSpeed.Changed += FireChangedEvent;
		_animationsSpeedModifier.Changed += FireChangedEvent;
		_paintBlastBall.Changed += FireChangedEvent;
		_paintBlastBallFlying.Changed += FireChangedEvent;
		_jokerBall.Changed += FireChangedEvent;
		_shadowRotation.Changed += FireChangedEvent;
		_shadowOpacityChangeSpeed.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselBallsView source = _source as DBEaselBallsView;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselBallsView" );
		colorBalls = source.colorBalls;
		switchToAnimation = source.switchToAnimation;
		animationsBaseSpeed = source.animationsBaseSpeed;
		animationsSpeedModifier = source.animationsSpeedModifier;
		paintBlastBall = source.paintBlastBall;
		paintBlastBallFlying = source.paintBlastBallFlying;
		jokerBall = source.jokerBall;
		shadowRotation = source.shadowRotation;
		shadowOpacityChangeSpeed = source.shadowOpacityChangeSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselBallsView newParent = _newParent as DBEaselBallsView;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_colorBalls.SetParent( newParent == null ? null : newParent._colorBalls );
		_switchToAnimation.SetParent( newParent == null ? null : newParent._switchToAnimation );
		_animationsBaseSpeed.SetParent( newParent == null ? null : newParent._animationsBaseSpeed );
		_animationsSpeedModifier.SetParent( newParent == null ? null : newParent._animationsSpeedModifier );
		_paintBlastBall.SetParent( newParent == null ? null : newParent._paintBlastBall );
		_paintBlastBallFlying.SetParent( newParent == null ? null : newParent._paintBlastBallFlying );
		_jokerBall.SetParent( newParent == null ? null : newParent._jokerBall );
		_shadowRotation.SetParent( newParent == null ? null : newParent._shadowRotation );
		_shadowOpacityChangeSpeed.SetParent( newParent == null ? null : newParent._shadowOpacityChangeSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_colorBalls.Reset();
		_switchToAnimation.Reset();
		_animationsBaseSpeed.Reset();
		_animationsSpeedModifier.Reset();
		_paintBlastBall.Reset();
		_paintBlastBallFlying.Reset();
		_jokerBall.Reset();
		_shadowRotation.Reset();
		_shadowOpacityChangeSpeed.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_colorBalls.IsDerivedFromParent()
			&& _switchToAnimation.IsDerivedFromParent()
			&& _animationsBaseSpeed.IsDerivedFromParent()
			&& _animationsSpeedModifier.IsDerivedFromParent()
			&& _paintBlastBall.IsDerivedFromParent()
			&& _paintBlastBallFlying.IsDerivedFromParent()
			&& _jokerBall.IsDerivedFromParent()
			&& _shadowRotation.IsDerivedFromParent()
			&& _shadowOpacityChangeSpeed.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "colorBalls" )
			_colorBalls.Reset();
		else if ( fieldName == "switchToAnimation" )
			_switchToAnimation.Reset();
		else if ( fieldName == "animationsBaseSpeed" )
			_animationsBaseSpeed.Reset();
		else if ( fieldName == "animationsSpeedModifier" )
			_animationsSpeedModifier.Reset();
		else if ( fieldName == "paintBlastBall" )
			_paintBlastBall.Reset();
		else if ( fieldName == "paintBlastBallFlying" )
			_paintBlastBallFlying.Reset();
		else if ( fieldName == "jokerBall" )
			_jokerBall.Reset();
		else if ( fieldName == "shadowRotation" )
			_shadowRotation.Reset();
		else if ( fieldName == "shadowOpacityChangeSpeed" )
			_shadowOpacityChangeSpeed.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "colorBalls" )
			return _colorBalls.IsDerivedFromParent();
		if ( fieldName == "switchToAnimation" )
			return _switchToAnimation.IsDerivedFromParent();
		if ( fieldName == "animationsBaseSpeed" )
			return _animationsBaseSpeed.IsDerivedFromParent();
		if ( fieldName == "animationsSpeedModifier" )
			return _animationsSpeedModifier.IsDerivedFromParent();
		if ( fieldName == "paintBlastBall" )
			return _paintBlastBall.IsDerivedFromParent();
		if ( fieldName == "paintBlastBallFlying" )
			return _paintBlastBallFlying.IsDerivedFromParent();
		if ( fieldName == "jokerBall" )
			return _jokerBall.IsDerivedFromParent();
		if ( fieldName == "shadowRotation" )
			return _shadowRotation.IsDerivedFromParent();
		if ( fieldName == "shadowOpacityChangeSpeed" )
			return _shadowOpacityChangeSpeed.IsDerivedFromParent();
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

public class DBEaselBidonEffectDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselBidonEffectDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _speedClockCooldownCoefficient;
	private UndoRedo<float> _speedClockPriceCoefficient;
	private UndoRedo<float> _glueSpeedReductionCoefficient;
	private UndoRedo<float> _glueAppearancePercentageDistance;

	[Description( "Multiplier coefficient for a Cooldown" )]
	public float speedClockCooldownCoefficient { get { return _speedClockCooldownCoefficient.Get(); } set { _speedClockCooldownCoefficient.Set( value ); } }

	[Description( "Multiplier coefficient for a Price" )]
	public float speedClockPriceCoefficient { get { return _speedClockPriceCoefficient.Get(); } set { _speedClockPriceCoefficient.Set( value ); } }

	[Description( "Multiplier coefficient for a glue speed reduction" )]
	public float glueSpeedReductionCoefficient { get { return _glueSpeedReductionCoefficient.Get(); } set { _glueSpeedReductionCoefficient.Set( value ); } }

	[Description( "Percentage distance for a glue spot appearance (from the starting point)" )]
	public float glueAppearancePercentageDistance { get { return _glueAppearancePercentageDistance.Get(); } set { _glueAppearancePercentageDistance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_speedClockCooldownCoefficient = new UndoRedo<float>( owner, 1.0f );
		_speedClockPriceCoefficient = new UndoRedo<float>( owner, 1.0f );
		_glueSpeedReductionCoefficient = new UndoRedo<float>( owner, 0.7f );
		_glueAppearancePercentageDistance = new UndoRedo<float>( owner, 0.7f );
		_speedClockCooldownCoefficient.Changed += FireChangedEvent;
		_speedClockPriceCoefficient.Changed += FireChangedEvent;
		_glueSpeedReductionCoefficient.Changed += FireChangedEvent;
		_glueAppearancePercentageDistance.Changed += FireChangedEvent;
	}

	public DBEaselBidonEffectDesc()
	{
		Initialize( GetOwner() );
	}

	public DBEaselBidonEffectDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselBidonEffectDesc( DBResource owner, DBEaselBidonEffectDesc source )
		: this(owner, source, true){}

	protected DBEaselBidonEffectDesc( DBResource owner, DBEaselBidonEffectDesc source, bool fireEvent )
	{
		_speedClockCooldownCoefficient = new UndoRedo<float>( owner, source.speedClockCooldownCoefficient );
		_speedClockPriceCoefficient = new UndoRedo<float>( owner, source.speedClockPriceCoefficient );
		_glueSpeedReductionCoefficient = new UndoRedo<float>( owner, source.glueSpeedReductionCoefficient );
		_glueAppearancePercentageDistance = new UndoRedo<float>( owner, source.glueAppearancePercentageDistance );
		_speedClockCooldownCoefficient.Changed += FireChangedEvent;
		_speedClockPriceCoefficient.Changed += FireChangedEvent;
		_glueSpeedReductionCoefficient.Changed += FireChangedEvent;
		_glueAppearancePercentageDistance.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselBidonEffectDesc source = _source as DBEaselBidonEffectDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselBidonEffectDesc" );
		speedClockCooldownCoefficient = source.speedClockCooldownCoefficient;
		speedClockPriceCoefficient = source.speedClockPriceCoefficient;
		glueSpeedReductionCoefficient = source.glueSpeedReductionCoefficient;
		glueAppearancePercentageDistance = source.glueAppearancePercentageDistance;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselBidonEffectDesc newParent = _newParent as DBEaselBidonEffectDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_speedClockCooldownCoefficient.SetParent( newParent == null ? null : newParent._speedClockCooldownCoefficient );
		_speedClockPriceCoefficient.SetParent( newParent == null ? null : newParent._speedClockPriceCoefficient );
		_glueSpeedReductionCoefficient.SetParent( newParent == null ? null : newParent._glueSpeedReductionCoefficient );
		_glueAppearancePercentageDistance.SetParent( newParent == null ? null : newParent._glueAppearancePercentageDistance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_speedClockCooldownCoefficient.Reset();
		_speedClockPriceCoefficient.Reset();
		_glueSpeedReductionCoefficient.Reset();
		_glueAppearancePercentageDistance.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_speedClockCooldownCoefficient.IsDerivedFromParent()
			&& _speedClockPriceCoefficient.IsDerivedFromParent()
			&& _glueSpeedReductionCoefficient.IsDerivedFromParent()
			&& _glueAppearancePercentageDistance.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "speedClockCooldownCoefficient" )
			_speedClockCooldownCoefficient.Reset();
		else if ( fieldName == "speedClockPriceCoefficient" )
			_speedClockPriceCoefficient.Reset();
		else if ( fieldName == "glueSpeedReductionCoefficient" )
			_glueSpeedReductionCoefficient.Reset();
		else if ( fieldName == "glueAppearancePercentageDistance" )
			_glueAppearancePercentageDistance.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "speedClockCooldownCoefficient" )
			return _speedClockCooldownCoefficient.IsDerivedFromParent();
		if ( fieldName == "speedClockPriceCoefficient" )
			return _speedClockPriceCoefficient.IsDerivedFromParent();
		if ( fieldName == "glueSpeedReductionCoefficient" )
			return _glueSpeedReductionCoefficient.IsDerivedFromParent();
		if ( fieldName == "glueAppearancePercentageDistance" )
			return _glueAppearancePercentageDistance.IsDerivedFromParent();
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

public class DBEaselBoostsTutorialDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselBoostsTutorialDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _changeBallsSecondsFromMovieEnd;
	private UndoRedo<int> _changeBallsCounts;

	[Description( "Describes how many seconds should passed after StartMovie end to fire change balls tutorial" )]
	public int changeBallsSecondsFromMovieEnd { get { return _changeBallsSecondsFromMovieEnd.Get(); } set { _changeBallsSecondsFromMovieEnd.Set( value ); } }

	[Description( "Describes how many balls changes required to cancel tutorial about the color change" )]
	public int changeBallsCounts { get { return _changeBallsCounts.Get(); } set { _changeBallsCounts.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_changeBallsSecondsFromMovieEnd = new UndoRedo<int>( owner, 5 );
		_changeBallsCounts = new UndoRedo<int>( owner, 2 );
		_changeBallsSecondsFromMovieEnd.Changed += FireChangedEvent;
		_changeBallsCounts.Changed += FireChangedEvent;
	}

	public DBEaselBoostsTutorialDesc()
	{
		Initialize( GetOwner() );
	}

	public DBEaselBoostsTutorialDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselBoostsTutorialDesc( DBResource owner, DBEaselBoostsTutorialDesc source )
		: this(owner, source, true){}

	protected DBEaselBoostsTutorialDesc( DBResource owner, DBEaselBoostsTutorialDesc source, bool fireEvent )
	{
		_changeBallsSecondsFromMovieEnd = new UndoRedo<int>( owner, source.changeBallsSecondsFromMovieEnd );
		_changeBallsCounts = new UndoRedo<int>( owner, source.changeBallsCounts );
		_changeBallsSecondsFromMovieEnd.Changed += FireChangedEvent;
		_changeBallsCounts.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselBoostsTutorialDesc source = _source as DBEaselBoostsTutorialDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselBoostsTutorialDesc" );
		changeBallsSecondsFromMovieEnd = source.changeBallsSecondsFromMovieEnd;
		changeBallsCounts = source.changeBallsCounts;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselBoostsTutorialDesc newParent = _newParent as DBEaselBoostsTutorialDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_changeBallsSecondsFromMovieEnd.SetParent( newParent == null ? null : newParent._changeBallsSecondsFromMovieEnd );
		_changeBallsCounts.SetParent( newParent == null ? null : newParent._changeBallsCounts );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_changeBallsSecondsFromMovieEnd.Reset();
		_changeBallsCounts.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_changeBallsSecondsFromMovieEnd.IsDerivedFromParent()
			&& _changeBallsCounts.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "changeBallsSecondsFromMovieEnd" )
			_changeBallsSecondsFromMovieEnd.Reset();
		else if ( fieldName == "changeBallsCounts" )
			_changeBallsCounts.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "changeBallsSecondsFromMovieEnd" )
			return _changeBallsSecondsFromMovieEnd.IsDerivedFromParent();
		if ( fieldName == "changeBallsCounts" )
			return _changeBallsCounts.IsDerivedFromParent();
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

public class DBEaselCursorView : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselCursorView __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<BasicEffectStandalone>> _cursors;

	[EnumArray(typeof(ECursor))]
	public libdb.IChangeableList<DBPtr<BasicEffectStandalone>> cursors { get { return _cursors; } set { _cursors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_cursors = new UndoRedoAssignableList<DBPtr<BasicEffectStandalone>>( owner, typeof( ECursor ) );
		_cursors.Changed += FireChangedEvent;
	}

	public DBEaselCursorView()
	{
		Initialize( GetOwner() );
	}

	public DBEaselCursorView( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselCursorView( DBResource owner, DBEaselCursorView source )
		: this(owner, source, true){}

	protected DBEaselCursorView( DBResource owner, DBEaselCursorView source, bool fireEvent )
	{
		_cursors = new UndoRedoAssignableList<DBPtr<BasicEffectStandalone>>( owner, typeof( ECursor ) );
		_cursors.Assign( source.cursors );
		_cursors.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselCursorView source = _source as DBEaselCursorView;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselCursorView" );
		cursors = source.cursors;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselCursorView newParent = _newParent as DBEaselCursorView;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cursors.SetParent( newParent == null ? null : newParent._cursors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cursors.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cursors.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cursors" )
			_cursors.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "cursors" )
			return _cursors.IsDerivedFromParent();
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

public class DBEaselFlowEffectGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselFlowEffectGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _intervalEndDistance;
	private UndoRedoDBPtr<BasicEffectStandalone> _flowEffect;

	[Description( "group distance interval starts from previous interval and ends by this value" )]
	public float intervalEndDistance { get { return _intervalEndDistance.Get(); } set { _intervalEndDistance.Set( value ); } }

	public DBPtr<BasicEffectStandalone> flowEffect { get { return _flowEffect.Get(); } set { _flowEffect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_intervalEndDistance = new UndoRedo<float>( owner, 0.0f );
		_flowEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_intervalEndDistance.Changed += FireChangedEvent;
		_flowEffect.Changed += FireChangedEvent;
	}

	public DBEaselFlowEffectGroup()
	{
		Initialize( GetOwner() );
	}

	public DBEaselFlowEffectGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselFlowEffectGroup( DBResource owner, DBEaselFlowEffectGroup source )
		: this(owner, source, true){}

	protected DBEaselFlowEffectGroup( DBResource owner, DBEaselFlowEffectGroup source, bool fireEvent )
	{
		_intervalEndDistance = new UndoRedo<float>( owner, source.intervalEndDistance );
		_flowEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.flowEffect );
		_intervalEndDistance.Changed += FireChangedEvent;
		_flowEffect.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselFlowEffectGroup source = _source as DBEaselFlowEffectGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselFlowEffectGroup" );
		intervalEndDistance = source.intervalEndDistance;
		flowEffect = source.flowEffect;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselFlowEffectGroup newParent = _newParent as DBEaselFlowEffectGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_intervalEndDistance.SetParent( newParent == null ? null : newParent._intervalEndDistance );
		_flowEffect.SetParent( newParent == null ? null : newParent._flowEffect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_intervalEndDistance.Reset();
		_flowEffect.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_intervalEndDistance.IsDerivedFromParent()
			&& _flowEffect.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "intervalEndDistance" )
			_intervalEndDistance.Reset();
		else if ( fieldName == "flowEffect" )
			_flowEffect.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "intervalEndDistance" )
			return _intervalEndDistance.IsDerivedFromParent();
		if ( fieldName == "flowEffect" )
			return _flowEffect.IsDerivedFromParent();
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

public class ExplosionParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ExplosionParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minRotationAngle;
	private Vec3 _maxScale;
	private Vec3 _minScale;

	[Description( "Minimal value of rotation angle of explosion effect between two calls in degrees" )]
	public float minRotationAngle { get { return _minRotationAngle.Get(); } set { _minRotationAngle.Set( value ); } }

	public Vec3 maxScale { get { return _maxScale; } set { _maxScale.Assign( value ); } }

	public Vec3 minScale { get { return _minScale; } set { _minScale.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_minRotationAngle = new UndoRedo<float>( owner, 90.0f );
		Vec3 __maxScale = new Vec3(); // Construct default object for maxScale
		__maxScale.x = 1.0f;
		__maxScale.y = 1.0f;
		__maxScale.z = 1.0f;
		_maxScale = new Vec3( owner, __maxScale );
		Vec3 __minScale = new Vec3(); // Construct default object for minScale
		__minScale.x = 1.0f;
		__minScale.y = 1.0f;
		__minScale.z = 1.0f;
		_minScale = new Vec3( owner, __minScale );
		_minRotationAngle.Changed += FireChangedEvent;
		_maxScale.Changed += FireChangedEvent;
		_minScale.Changed += FireChangedEvent;
	}

	public ExplosionParams()
	{
		Initialize( GetOwner() );
	}

	public ExplosionParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ExplosionParams( DBResource owner, ExplosionParams source )
		: this(owner, source, true){}

	protected ExplosionParams( DBResource owner, ExplosionParams source, bool fireEvent )
	{
		_minRotationAngle = new UndoRedo<float>( owner, source.minRotationAngle );
		_maxScale = new Vec3( owner, source.maxScale );
		_minScale = new Vec3( owner, source.minScale );
		_minRotationAngle.Changed += FireChangedEvent;
		_maxScale.Changed += FireChangedEvent;
		_minScale.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ExplosionParams source = _source as ExplosionParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExplosionParams" );
		minRotationAngle = source.minRotationAngle;
		maxScale = source.maxScale;
		minScale = source.minScale;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ExplosionParams newParent = _newParent as ExplosionParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minRotationAngle.SetParent( newParent == null ? null : newParent._minRotationAngle );
		_maxScale.SetParent( newParent == null ? null : newParent._maxScale );
		_minScale.SetParent( newParent == null ? null : newParent._minScale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minRotationAngle.Reset();
		_maxScale.Reset();
		_minScale.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minRotationAngle.IsDerivedFromParent()
			&& _maxScale.IsDerivedFromParent()
			&& _minScale.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minRotationAngle" )
			_minRotationAngle.Reset();
		else if ( fieldName == "maxScale" )
			_maxScale.Reset();
		else if ( fieldName == "minScale" )
			_minScale.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minRotationAngle" )
			return _minRotationAngle.IsDerivedFromParent();
		if ( fieldName == "maxScale" )
			return _maxScale.IsDerivedFromParent();
		if ( fieldName == "minScale" )
			return _minScale.IsDerivedFromParent();
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

public class DBEaselLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EDifficultyLevel> _difficulty;
	private UndoRedo<EDifficultyLevel> _additionalDifficulty;

	public EDifficultyLevel difficulty { get { return _difficulty.Get(); } set { _difficulty.Set( value ); } }

	public EDifficultyLevel additionalDifficulty { get { return _additionalDifficulty.Get(); } set { _additionalDifficulty.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_difficulty = new UndoRedo<EDifficultyLevel>( owner, EDifficultyLevel.Unknown );
		_additionalDifficulty = new UndoRedo<EDifficultyLevel>( owner, EDifficultyLevel.Unknown );
		_difficulty.Changed += FireChangedEvent;
		_additionalDifficulty.Changed += FireChangedEvent;
	}

	public DBEaselLevel()
	{
		Initialize( GetOwner() );
	}

	public DBEaselLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselLevel( DBResource owner, DBEaselLevel source )
		: this(owner, source, true){}

	protected DBEaselLevel( DBResource owner, DBEaselLevel source, bool fireEvent )
	{
		_difficulty = new UndoRedo<EDifficultyLevel>( owner, source.difficulty );
		_additionalDifficulty = new UndoRedo<EDifficultyLevel>( owner, source.additionalDifficulty );
		_difficulty.Changed += FireChangedEvent;
		_additionalDifficulty.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselLevel source = _source as DBEaselLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselLevel" );
		difficulty = source.difficulty;
		additionalDifficulty = source.additionalDifficulty;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselLevel newParent = _newParent as DBEaselLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_difficulty.SetParent( newParent == null ? null : newParent._difficulty );
		_additionalDifficulty.SetParent( newParent == null ? null : newParent._additionalDifficulty );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_difficulty.Reset();
		_additionalDifficulty.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_difficulty.IsDerivedFromParent()
			&& _additionalDifficulty.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "difficulty" )
			_difficulty.Reset();
		else if ( fieldName == "additionalDifficulty" )
			_additionalDifficulty.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "difficulty" )
			return _difficulty.IsDerivedFromParent();
		if ( fieldName == "additionalDifficulty" )
			return _additionalDifficulty.IsDerivedFromParent();
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

public class DBEaselPlatfrom : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselPlatfrom __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBSceneObject> _platformObject;
	private UndoRedoDBPtr<DBSceneObject> _triplePlatformObject;
	private UndoRedoDBPtr<LightningEffect> _laser;
	private UndoRedoDBPtr<LightningEffect> _laser2;
	private UndoRedoDBPtr<BasicEffectStandalone> _laserPointer;
	private UndoRedoDBPtr<BasicEffectAttached> _laserSource;

	public DBPtr<DBSceneObject> platformObject { get { return _platformObject.Get(); } set { _platformObject.Set( value ); } }

	public DBPtr<DBSceneObject> triplePlatformObject { get { return _triplePlatformObject.Get(); } set { _triplePlatformObject.Set( value ); } }

	public DBPtr<LightningEffect> laser { get { return _laser.Get(); } set { _laser.Set( value ); } }

	public DBPtr<LightningEffect> laser2 { get { return _laser2.Get(); } set { _laser2.Set( value ); } }

	public DBPtr<BasicEffectStandalone> laserPointer { get { return _laserPointer.Get(); } set { _laserPointer.Set( value ); } }

	public DBPtr<BasicEffectAttached> laserSource { get { return _laserSource.Get(); } set { _laserSource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_platformObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_triplePlatformObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_laser = new UndoRedoDBPtr<LightningEffect>( owner );
		_laser2 = new UndoRedoDBPtr<LightningEffect>( owner );
		_laserPointer = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_laserSource = new UndoRedoDBPtr<BasicEffectAttached>( owner );
		_platformObject.Changed += FireChangedEvent;
		_triplePlatformObject.Changed += FireChangedEvent;
		_laser.Changed += FireChangedEvent;
		_laser2.Changed += FireChangedEvent;
		_laserPointer.Changed += FireChangedEvent;
		_laserSource.Changed += FireChangedEvent;
	}

	public DBEaselPlatfrom()
	{
		Initialize( GetOwner() );
	}

	public DBEaselPlatfrom( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselPlatfrom( DBResource owner, DBEaselPlatfrom source )
		: this(owner, source, true){}

	protected DBEaselPlatfrom( DBResource owner, DBEaselPlatfrom source, bool fireEvent )
	{
		_platformObject = new UndoRedoDBPtr<DBSceneObject>( owner, source.platformObject );
		_triplePlatformObject = new UndoRedoDBPtr<DBSceneObject>( owner, source.triplePlatformObject );
		_laser = new UndoRedoDBPtr<LightningEffect>( owner, source.laser );
		_laser2 = new UndoRedoDBPtr<LightningEffect>( owner, source.laser2 );
		_laserPointer = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.laserPointer );
		_laserSource = new UndoRedoDBPtr<BasicEffectAttached>( owner, source.laserSource );
		_platformObject.Changed += FireChangedEvent;
		_triplePlatformObject.Changed += FireChangedEvent;
		_laser.Changed += FireChangedEvent;
		_laser2.Changed += FireChangedEvent;
		_laserPointer.Changed += FireChangedEvent;
		_laserSource.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselPlatfrom source = _source as DBEaselPlatfrom;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselPlatfrom" );
		platformObject = source.platformObject;
		triplePlatformObject = source.triplePlatformObject;
		laser = source.laser;
		laser2 = source.laser2;
		laserPointer = source.laserPointer;
		laserSource = source.laserSource;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselPlatfrom newParent = _newParent as DBEaselPlatfrom;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_platformObject.SetParent( newParent == null ? null : newParent._platformObject );
		_triplePlatformObject.SetParent( newParent == null ? null : newParent._triplePlatformObject );
		_laser.SetParent( newParent == null ? null : newParent._laser );
		_laser2.SetParent( newParent == null ? null : newParent._laser2 );
		_laserPointer.SetParent( newParent == null ? null : newParent._laserPointer );
		_laserSource.SetParent( newParent == null ? null : newParent._laserSource );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_platformObject.Reset();
		_triplePlatformObject.Reset();
		_laser.Reset();
		_laser2.Reset();
		_laserPointer.Reset();
		_laserSource.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_platformObject.IsDerivedFromParent()
			&& _triplePlatformObject.IsDerivedFromParent()
			&& _laser.IsDerivedFromParent()
			&& _laser2.IsDerivedFromParent()
			&& _laserPointer.IsDerivedFromParent()
			&& _laserSource.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "platformObject" )
			_platformObject.Reset();
		else if ( fieldName == "triplePlatformObject" )
			_triplePlatformObject.Reset();
		else if ( fieldName == "laser" )
			_laser.Reset();
		else if ( fieldName == "laser2" )
			_laser2.Reset();
		else if ( fieldName == "laserPointer" )
			_laserPointer.Reset();
		else if ( fieldName == "laserSource" )
			_laserSource.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "platformObject" )
			return _platformObject.IsDerivedFromParent();
		if ( fieldName == "triplePlatformObject" )
			return _triplePlatformObject.IsDerivedFromParent();
		if ( fieldName == "laser" )
			return _laser.IsDerivedFromParent();
		if ( fieldName == "laser2" )
			return _laser2.IsDerivedFromParent();
		if ( fieldName == "laserPointer" )
			return _laserPointer.IsDerivedFromParent();
		if ( fieldName == "laserSource" )
			return _laserSource.IsDerivedFromParent();
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
public class DBEaselSound : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselSound __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _eventName;

	public string eventName { get { return _eventName.Get(); } set { _eventName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_eventName = new UndoRedo<string>( owner, string.Empty );
		_eventName.Changed += FireChangedEvent;
	}

	public DBEaselSound()
	{
		Initialize( GetOwner() );
	}

	public DBEaselSound( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselSound( DBResource owner, DBEaselSound source )
		: this(owner, source, true){}

	protected DBEaselSound( DBResource owner, DBEaselSound source, bool fireEvent )
	{
		_eventName = new UndoRedo<string>( owner, source.eventName );
		_eventName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselSound source = _source as DBEaselSound;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselSound" );
		eventName = source.eventName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselSound newParent = _newParent as DBEaselSound;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_eventName.SetParent( newParent == null ? null : newParent._eventName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_eventName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_eventName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "eventName" )
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

public class DBFragment : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBFragment __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EColor> _fragmentColor;
	private UndoRedoAssignableList<DBPtr<DBPainterPoint>> _fragmentPoints;
	private UndoRedo<int> _paintFragmentId;
	private UndoRedoDBPtr<Material> _completeEffectMaterial;

	[Category( "Painter fragment" )]
	public EColor fragmentColor { get { return _fragmentColor.Get(); } set { _fragmentColor.Set( value ); } }

	public libdb.IChangeableList<DBPtr<DBPainterPoint>> fragmentPoints { get { return _fragmentPoints; } set { _fragmentPoints.Assign( value ); } }

	public int paintFragmentId { get { return _paintFragmentId.Get(); } set { _paintFragmentId.Set( value ); } }

	[Category( "Painter render parameters" )]
	public DBPtr<Material> completeEffectMaterial { get { return _completeEffectMaterial.Get(); } set { _completeEffectMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_fragmentColor = new UndoRedo<EColor>( owner, EColor.black );
		_fragmentPoints = new UndoRedoAssignableList<DBPtr<DBPainterPoint>>( owner );
		_paintFragmentId = new UndoRedo<int>( owner, 0 );
		_completeEffectMaterial = new UndoRedoDBPtr<Material>( owner );
		_fragmentColor.Changed += FireChangedEvent;
		_fragmentPoints.Changed += FireChangedEvent;
		_paintFragmentId.Changed += FireChangedEvent;
		_completeEffectMaterial.Changed += FireChangedEvent;
	}

	public DBFragment()
	{
		Initialize( GetOwner() );
	}

	public DBFragment( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBFragment( DBResource owner, DBFragment source )
		: this(owner, source, true){}

	protected DBFragment( DBResource owner, DBFragment source, bool fireEvent )
	{
		_fragmentColor = new UndoRedo<EColor>( owner, source.fragmentColor );
		_fragmentPoints = new UndoRedoAssignableList<DBPtr<DBPainterPoint>>( owner );
		_fragmentPoints.Assign( source.fragmentPoints );
		_paintFragmentId = new UndoRedo<int>( owner, source.paintFragmentId );
		_completeEffectMaterial = new UndoRedoDBPtr<Material>( owner, source.completeEffectMaterial );
		_fragmentColor.Changed += FireChangedEvent;
		_fragmentPoints.Changed += FireChangedEvent;
		_paintFragmentId.Changed += FireChangedEvent;
		_completeEffectMaterial.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBFragment source = _source as DBFragment;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBFragment" );
		fragmentColor = source.fragmentColor;
		fragmentPoints = source.fragmentPoints;
		paintFragmentId = source.paintFragmentId;
		completeEffectMaterial = source.completeEffectMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBFragment newParent = _newParent as DBFragment;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_fragmentColor.SetParent( newParent == null ? null : newParent._fragmentColor );
		_fragmentPoints.SetParent( newParent == null ? null : newParent._fragmentPoints );
		_paintFragmentId.SetParent( newParent == null ? null : newParent._paintFragmentId );
		_completeEffectMaterial.SetParent( newParent == null ? null : newParent._completeEffectMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_fragmentColor.Reset();
		_fragmentPoints.Reset();
		_paintFragmentId.Reset();
		_completeEffectMaterial.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_fragmentColor.IsDerivedFromParent()
			&& _fragmentPoints.IsDerivedFromParent()
			&& _paintFragmentId.IsDerivedFromParent()
			&& _completeEffectMaterial.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "fragmentColor" )
			_fragmentColor.Reset();
		else if ( fieldName == "fragmentPoints" )
			_fragmentPoints.Reset();
		else if ( fieldName == "paintFragmentId" )
			_paintFragmentId.Reset();
		else if ( fieldName == "completeEffectMaterial" )
			_completeEffectMaterial.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "fragmentColor" )
			return _fragmentColor.IsDerivedFromParent();
		if ( fieldName == "fragmentPoints" )
			return _fragmentPoints.IsDerivedFromParent();
		if ( fieldName == "paintFragmentId" )
			return _paintFragmentId.IsDerivedFromParent();
		if ( fieldName == "completeEffectMaterial" )
			return _completeEffectMaterial.IsDerivedFromParent();
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

public class DBJokerBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBJokerBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_boostBase.Changed += FireChangedEvent;
	}

	public DBJokerBoost()
	{
		Initialize( GetOwner() );
	}

	public DBJokerBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBJokerBoost( DBResource owner, DBJokerBoost source )
		: this(owner, source, true){}

	protected DBJokerBoost( DBResource owner, DBJokerBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_boostBase.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBJokerBoost source = _source as DBJokerBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBJokerBoost" );
		boostBase = source.boostBase;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBJokerBoost newParent = _newParent as DBJokerBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
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

public class DBMagnetBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBMagnetBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;
	private UndoRedo<int> _searchSeconds;
	private UndoRedo<int> _radiusR1;
	private UndoRedo<int> _radiusR2;
	private UndoRedo<int> _numBallToEat;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	[IntMin(0)]
	public int searchSeconds { get { return _searchSeconds.Get(); } set { _searchSeconds.Set( value ); } }

	[IntMin(0)]
	public int radiusR1 { get { return _radiusR1.Get(); } set { _radiusR1.Set( value ); } }

	[IntMin(0)]
	public int radiusR2 { get { return _radiusR2.Get(); } set { _radiusR2.Set( value ); } }

	[IntMin(0)]
	public int numBallToEat { get { return _numBallToEat.Get(); } set { _numBallToEat.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_searchSeconds = new UndoRedo<int>( owner, 0 );
		_radiusR1 = new UndoRedo<int>( owner, 0 );
		_radiusR2 = new UndoRedo<int>( owner, 0 );
		_numBallToEat = new UndoRedo<int>( owner, 0 );
		_boostBase.Changed += FireChangedEvent;
		_searchSeconds.Changed += FireChangedEvent;
		_radiusR1.Changed += FireChangedEvent;
		_radiusR2.Changed += FireChangedEvent;
		_numBallToEat.Changed += FireChangedEvent;
	}

	public DBMagnetBoost()
	{
		Initialize( GetOwner() );
	}

	public DBMagnetBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBMagnetBoost( DBResource owner, DBMagnetBoost source )
		: this(owner, source, true){}

	protected DBMagnetBoost( DBResource owner, DBMagnetBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_searchSeconds = new UndoRedo<int>( owner, source.searchSeconds );
		_radiusR1 = new UndoRedo<int>( owner, source.radiusR1 );
		_radiusR2 = new UndoRedo<int>( owner, source.radiusR2 );
		_numBallToEat = new UndoRedo<int>( owner, source.numBallToEat );
		_boostBase.Changed += FireChangedEvent;
		_searchSeconds.Changed += FireChangedEvent;
		_radiusR1.Changed += FireChangedEvent;
		_radiusR2.Changed += FireChangedEvent;
		_numBallToEat.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBMagnetBoost source = _source as DBMagnetBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMagnetBoost" );
		boostBase = source.boostBase;
		searchSeconds = source.searchSeconds;
		radiusR1 = source.radiusR1;
		radiusR2 = source.radiusR2;
		numBallToEat = source.numBallToEat;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBMagnetBoost newParent = _newParent as DBMagnetBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		_searchSeconds.SetParent( newParent == null ? null : newParent._searchSeconds );
		_radiusR1.SetParent( newParent == null ? null : newParent._radiusR1 );
		_radiusR2.SetParent( newParent == null ? null : newParent._radiusR2 );
		_numBallToEat.SetParent( newParent == null ? null : newParent._numBallToEat );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
		_searchSeconds.Reset();
		_radiusR1.Reset();
		_radiusR2.Reset();
		_numBallToEat.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			&& _searchSeconds.IsDerivedFromParent()
			&& _radiusR1.IsDerivedFromParent()
			&& _radiusR2.IsDerivedFromParent()
			&& _numBallToEat.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else if ( fieldName == "searchSeconds" )
			_searchSeconds.Reset();
		else if ( fieldName == "radiusR1" )
			_radiusR1.Reset();
		else if ( fieldName == "radiusR2" )
			_radiusR2.Reset();
		else if ( fieldName == "numBallToEat" )
			_numBallToEat.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
		if ( fieldName == "searchSeconds" )
			return _searchSeconds.IsDerivedFromParent();
		if ( fieldName == "radiusR1" )
			return _radiusR1.IsDerivedFromParent();
		if ( fieldName == "radiusR2" )
			return _radiusR2.IsDerivedFromParent();
		if ( fieldName == "numBallToEat" )
			return _numBallToEat.IsDerivedFromParent();
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

public class DBListFragments : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBListFragments __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBFragment> _listFragments;

	[Category( "FragmentsList" )]
	public libdb.IChangeableList<DBFragment> listFragments { get { return _listFragments; } set { _listFragments.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_listFragments = new UndoRedoAssignableList<DBFragment>( owner );
		_listFragments.Changed += FireChangedEvent;
	}

	public DBListFragments()
	{
		Initialize( GetOwner() );
	}

	public DBListFragments( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBListFragments( DBResource owner, DBListFragments source )
		: this(owner, source, true){}

	protected DBListFragments( DBResource owner, DBListFragments source, bool fireEvent )
	{
		_listFragments = new UndoRedoAssignableList<DBFragment>( owner );
		_listFragments.Assign( source.listFragments );
		_listFragments.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBListFragments source = _source as DBListFragments;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBListFragments" );
		listFragments = source.listFragments;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBListFragments newParent = _newParent as DBListFragments;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_listFragments.SetParent( newParent == null ? null : newParent._listFragments );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_listFragments.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_listFragments.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "listFragments" )
			_listFragments.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "listFragments" )
			return _listFragments.IsDerivedFromParent();
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

public class DBLogicPoint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBLogicPoint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	[IntMinMax(0, 10000)]
	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	[IntMinMax(0, 10000)]
	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public DBLogicPoint()
	{
		Initialize( GetOwner() );
	}

	public DBLogicPoint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBLogicPoint( DBResource owner, DBLogicPoint source )
		: this(owner, source, true){}

	protected DBLogicPoint( DBResource owner, DBLogicPoint source, bool fireEvent )
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
		DBLogicPoint source = _source as DBLogicPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLogicPoint" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBLogicPoint newParent = _newParent as DBLogicPoint;
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

public class DBLuxorPlatformGeneratorParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBLuxorPlatformGeneratorParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _firstChainInfluenceStart;
	private UndoRedo<int> _firstChainInfluenceEnd;
	private UndoRedo<float> _colorWeightsPower;
	private UndoRedo<float> _colorWeightsMultiplier;
	private UndoRedo<float> _lowActChance;

	[Description( "0 - begin of path, 100 - end of path[OBSOLETE]" )]
	[MinMaxSize(0, 100)]
	public int firstChainInfluenceStart { get { return _firstChainInfluenceStart.Get(); } set { _firstChainInfluenceStart.Set( value ); } }

	[Description( "0 - begin of path, 100 - end of path [OBSOLETE]" )]
	[MinMaxSize(0, 100)]
	public int firstChainInfluenceEnd { get { return _firstChainInfluenceEnd.Get(); } set { _firstChainInfluenceEnd.Set( value ); } }

	public float colorWeightsPower { get { return _colorWeightsPower.Get(); } set { _colorWeightsPower.Set( value ); } }

	public float colorWeightsMultiplier { get { return _colorWeightsMultiplier.Get(); } set { _colorWeightsMultiplier.Set( value ); } }

	public float lowActChance { get { return _lowActChance.Get(); } set { _lowActChance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_firstChainInfluenceStart = new UndoRedo<int>( owner, 0 );
		_firstChainInfluenceEnd = new UndoRedo<int>( owner, 100 );
		_colorWeightsPower = new UndoRedo<float>( owner, 4.0f );
		_colorWeightsMultiplier = new UndoRedo<float>( owner, 0.95f );
		_lowActChance = new UndoRedo<float>( owner, 0.95f );
		_firstChainInfluenceStart.Changed += FireChangedEvent;
		_firstChainInfluenceEnd.Changed += FireChangedEvent;
		_colorWeightsPower.Changed += FireChangedEvent;
		_colorWeightsMultiplier.Changed += FireChangedEvent;
		_lowActChance.Changed += FireChangedEvent;
	}

	public DBLuxorPlatformGeneratorParams()
	{
		Initialize( GetOwner() );
	}

	public DBLuxorPlatformGeneratorParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBLuxorPlatformGeneratorParams( DBResource owner, DBLuxorPlatformGeneratorParams source )
		: this(owner, source, true){}

	protected DBLuxorPlatformGeneratorParams( DBResource owner, DBLuxorPlatformGeneratorParams source, bool fireEvent )
	{
		_firstChainInfluenceStart = new UndoRedo<int>( owner, source.firstChainInfluenceStart );
		_firstChainInfluenceEnd = new UndoRedo<int>( owner, source.firstChainInfluenceEnd );
		_colorWeightsPower = new UndoRedo<float>( owner, source.colorWeightsPower );
		_colorWeightsMultiplier = new UndoRedo<float>( owner, source.colorWeightsMultiplier );
		_lowActChance = new UndoRedo<float>( owner, source.lowActChance );
		_firstChainInfluenceStart.Changed += FireChangedEvent;
		_firstChainInfluenceEnd.Changed += FireChangedEvent;
		_colorWeightsPower.Changed += FireChangedEvent;
		_colorWeightsMultiplier.Changed += FireChangedEvent;
		_lowActChance.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBLuxorPlatformGeneratorParams source = _source as DBLuxorPlatformGeneratorParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLuxorPlatformGeneratorParams" );
		firstChainInfluenceStart = source.firstChainInfluenceStart;
		firstChainInfluenceEnd = source.firstChainInfluenceEnd;
		colorWeightsPower = source.colorWeightsPower;
		colorWeightsMultiplier = source.colorWeightsMultiplier;
		lowActChance = source.lowActChance;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBLuxorPlatformGeneratorParams newParent = _newParent as DBLuxorPlatformGeneratorParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_firstChainInfluenceStart.SetParent( newParent == null ? null : newParent._firstChainInfluenceStart );
		_firstChainInfluenceEnd.SetParent( newParent == null ? null : newParent._firstChainInfluenceEnd );
		_colorWeightsPower.SetParent( newParent == null ? null : newParent._colorWeightsPower );
		_colorWeightsMultiplier.SetParent( newParent == null ? null : newParent._colorWeightsMultiplier );
		_lowActChance.SetParent( newParent == null ? null : newParent._lowActChance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_firstChainInfluenceStart.Reset();
		_firstChainInfluenceEnd.Reset();
		_colorWeightsPower.Reset();
		_colorWeightsMultiplier.Reset();
		_lowActChance.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_firstChainInfluenceStart.IsDerivedFromParent()
			&& _firstChainInfluenceEnd.IsDerivedFromParent()
			&& _colorWeightsPower.IsDerivedFromParent()
			&& _colorWeightsMultiplier.IsDerivedFromParent()
			&& _lowActChance.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "firstChainInfluenceStart" )
			_firstChainInfluenceStart.Reset();
		else if ( fieldName == "firstChainInfluenceEnd" )
			_firstChainInfluenceEnd.Reset();
		else if ( fieldName == "colorWeightsPower" )
			_colorWeightsPower.Reset();
		else if ( fieldName == "colorWeightsMultiplier" )
			_colorWeightsMultiplier.Reset();
		else if ( fieldName == "lowActChance" )
			_lowActChance.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "firstChainInfluenceStart" )
			return _firstChainInfluenceStart.IsDerivedFromParent();
		if ( fieldName == "firstChainInfluenceEnd" )
			return _firstChainInfluenceEnd.IsDerivedFromParent();
		if ( fieldName == "colorWeightsPower" )
			return _colorWeightsPower.IsDerivedFromParent();
		if ( fieldName == "colorWeightsMultiplier" )
			return _colorWeightsMultiplier.IsDerivedFromParent();
		if ( fieldName == "lowActChance" )
			return _lowActChance.IsDerivedFromParent();
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

public class DBPaintBlastBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBPaintBlastBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;
	private UndoRedo<int> _radius;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	[IntMin(0)]
	public int radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_radius = new UndoRedo<int>( owner, 0 );
		_boostBase.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
	}

	public DBPaintBlastBoost()
	{
		Initialize( GetOwner() );
	}

	public DBPaintBlastBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBPaintBlastBoost( DBResource owner, DBPaintBlastBoost source )
		: this(owner, source, true){}

	protected DBPaintBlastBoost( DBResource owner, DBPaintBlastBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_radius = new UndoRedo<int>( owner, source.radius );
		_boostBase.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBPaintBlastBoost source = _source as DBPaintBlastBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPaintBlastBoost" );
		boostBase = source.boostBase;
		radius = source.radius;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPaintBlastBoost newParent = _newParent as DBPaintBlastBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
		_radius.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
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

public class DBPicture : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBPicture __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _picturefile;
	private UndoRedo<string> _picturename;
	private UndoRedoAssignableList<DBPtr<DBPainterFragment>> _pictureparams;

	public string picturefile { get { return _picturefile.Get(); } set { _picturefile.Set( value ); } }

	public string picturename { get { return _picturename.Get(); } set { _picturename.Set( value ); } }

	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<DBPtr<DBPainterFragment>> pictureparams { get { return _pictureparams; } set { _pictureparams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_picturefile = new UndoRedo<string>( owner, string.Empty );
		_picturename = new UndoRedo<string>( owner, string.Empty );
		_pictureparams = new UndoRedoAssignableList<DBPtr<DBPainterFragment>>( owner, typeof( EPriestessLevel ) );
		_picturefile.Changed += FireChangedEvent;
		_picturename.Changed += FireChangedEvent;
		_pictureparams.Changed += FireChangedEvent;
	}

	public DBPicture()
	{
		Initialize( GetOwner() );
	}

	public DBPicture( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBPicture( DBResource owner, DBPicture source )
		: this(owner, source, true){}

	protected DBPicture( DBResource owner, DBPicture source, bool fireEvent )
	{
		_picturefile = new UndoRedo<string>( owner, source.picturefile );
		_picturename = new UndoRedo<string>( owner, source.picturename );
		_pictureparams = new UndoRedoAssignableList<DBPtr<DBPainterFragment>>( owner, typeof( EPriestessLevel ) );
		_pictureparams.Assign( source.pictureparams );
		_picturefile.Changed += FireChangedEvent;
		_picturename.Changed += FireChangedEvent;
		_pictureparams.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBPicture source = _source as DBPicture;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPicture" );
		picturefile = source.picturefile;
		picturename = source.picturename;
		pictureparams = source.pictureparams;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPicture newParent = _newParent as DBPicture;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_picturefile.SetParent( newParent == null ? null : newParent._picturefile );
		_picturename.SetParent( newParent == null ? null : newParent._picturename );
		_pictureparams.SetParent( newParent == null ? null : newParent._pictureparams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_picturefile.Reset();
		_picturename.Reset();
		_pictureparams.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_picturefile.IsDerivedFromParent()
			&& _picturename.IsDerivedFromParent()
			&& _pictureparams.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "picturefile" )
			_picturefile.Reset();
		else if ( fieldName == "picturename" )
			_picturename.Reset();
		else if ( fieldName == "pictureparams" )
			_pictureparams.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "picturefile" )
			return _picturefile.IsDerivedFromParent();
		if ( fieldName == "picturename" )
			return _picturename.IsDerivedFromParent();
		if ( fieldName == "pictureparams" )
			return _pictureparams.IsDerivedFromParent();
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

public class DBSorterBoost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSorterBoost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBBoost _boostBase;

	public DBBoost boostBase { get { return _boostBase; } set { _boostBase.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_boostBase = new DBBoost( owner );
		_boostBase.Changed += FireChangedEvent;
	}

	public DBSorterBoost()
	{
		Initialize( GetOwner() );
	}

	public DBSorterBoost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSorterBoost( DBResource owner, DBSorterBoost source )
		: this(owner, source, true){}

	protected DBSorterBoost( DBResource owner, DBSorterBoost source, bool fireEvent )
	{
		_boostBase = new DBBoost( owner, source.boostBase );
		_boostBase.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSorterBoost source = _source as DBSorterBoost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSorterBoost" );
		boostBase = source.boostBase;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSorterBoost newParent = _newParent as DBSorterBoost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boostBase.SetParent( newParent == null ? null : newParent._boostBase );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boostBase.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boostBase.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boostBase" )
			_boostBase.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boostBase" )
			return _boostBase.IsDerivedFromParent();
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

public class DBPaint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBPaint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPicture> _picture;
	private UndoRedoDBPtr<DBSceneObject> _paintQuad;

	public libdb.IChangeableList<DBPicture> picture { get { return _picture; } set { _picture.Assign( value ); } }

	public DBPtr<DBSceneObject> paintQuad { get { return _paintQuad.Get(); } set { _paintQuad.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_picture = new UndoRedoAssignableList<DBPicture>( owner );
		_paintQuad = new UndoRedoDBPtr<DBSceneObject>( owner );
		_picture.Changed += FireChangedEvent;
		_paintQuad.Changed += FireChangedEvent;
	}

	public DBPaint()
	{
		Initialize( GetOwner() );
	}

	public DBPaint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBPaint( DBResource owner, DBPaint source )
		: this(owner, source, true){}

	protected DBPaint( DBResource owner, DBPaint source, bool fireEvent )
	{
		_picture = new UndoRedoAssignableList<DBPicture>( owner );
		_picture.Assign( source.picture );
		_paintQuad = new UndoRedoDBPtr<DBSceneObject>( owner, source.paintQuad );
		_picture.Changed += FireChangedEvent;
		_paintQuad.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBPaint source = _source as DBPaint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPaint" );
		picture = source.picture;
		paintQuad = source.paintQuad;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPaint newParent = _newParent as DBPaint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_picture.SetParent( newParent == null ? null : newParent._picture );
		_paintQuad.SetParent( newParent == null ? null : newParent._paintQuad );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_picture.Reset();
		_paintQuad.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_picture.IsDerivedFromParent()
			&& _paintQuad.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "picture" )
			_picture.Reset();
		else if ( fieldName == "paintQuad" )
			_paintQuad.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "picture" )
			return _picture.IsDerivedFromParent();
		if ( fieldName == "paintQuad" )
			return _paintQuad.IsDerivedFromParent();
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

public class DBPoint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBPoint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _xCoord;
	private UndoRedo<int> _yCoord;
	private UndoRedo<int> _zCoord;

	public int xCoord { get { return _xCoord.Get(); } set { _xCoord.Set( value ); } }

	public int yCoord { get { return _yCoord.Get(); } set { _yCoord.Set( value ); } }

	public int zCoord { get { return _zCoord.Get(); } set { _zCoord.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_xCoord = new UndoRedo<int>( owner, 0 );
		_yCoord = new UndoRedo<int>( owner, 0 );
		_zCoord = new UndoRedo<int>( owner, 0 );
		_xCoord.Changed += FireChangedEvent;
		_yCoord.Changed += FireChangedEvent;
		_zCoord.Changed += FireChangedEvent;
	}

	public DBPoint()
	{
		Initialize( GetOwner() );
	}

	public DBPoint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBPoint( DBResource owner, DBPoint source )
		: this(owner, source, true){}

	protected DBPoint( DBResource owner, DBPoint source, bool fireEvent )
	{
		_xCoord = new UndoRedo<int>( owner, source.xCoord );
		_yCoord = new UndoRedo<int>( owner, source.yCoord );
		_zCoord = new UndoRedo<int>( owner, source.zCoord );
		_xCoord.Changed += FireChangedEvent;
		_yCoord.Changed += FireChangedEvent;
		_zCoord.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBPoint source = _source as DBPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPoint" );
		xCoord = source.xCoord;
		yCoord = source.yCoord;
		zCoord = source.zCoord;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPoint newParent = _newParent as DBPoint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_xCoord.SetParent( newParent == null ? null : newParent._xCoord );
		_yCoord.SetParent( newParent == null ? null : newParent._yCoord );
		_zCoord.SetParent( newParent == null ? null : newParent._zCoord );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_xCoord.Reset();
		_yCoord.Reset();
		_zCoord.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_xCoord.IsDerivedFromParent()
			&& _yCoord.IsDerivedFromParent()
			&& _zCoord.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "xCoord" )
			_xCoord.Reset();
		else if ( fieldName == "yCoord" )
			_yCoord.Reset();
		else if ( fieldName == "zCoord" )
			_zCoord.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "xCoord" )
			return _xCoord.IsDerivedFromParent();
		if ( fieldName == "yCoord" )
			return _yCoord.IsDerivedFromParent();
		if ( fieldName == "zCoord" )
			return _zCoord.IsDerivedFromParent();
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
public class DBBoostList : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBBoostList __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _rerollOnWinStreak;
	private UndoRedo<int> _rerollOnFailStreak;
	private UndoRedoList<EBoostsCategory> _slots;
	private UndoRedoList<bool> _canReroll;
	private UndoRedoAssignableList<DBBoostTemplate> _boostsTemplate;
	private UndoRedoAssignableList<TextRef> _boostsTooltips;
	private UndoRedoList<int> _slotsPrices;
	private UndoRedoList<int> _regenPrices;
	private UndoRedoAssignableList<DBPtr<UITexture>> _images;
	private DBPaintBlastBoost _paintblast;
	private DBFreezeBoost _freeze;
	private DBJokerBoost _joker;
	private DBSorterBoost _sorter;
	private DBMagnetBoost _magnet;
	private DBAlchemistBoost _alchemist;

	[Category( "Reroll streak" )]
	[IntMin(1)]
	public int rerollOnWinStreak { get { return _rerollOnWinStreak.Get(); } set { _rerollOnWinStreak.Set( value ); } }

	[IntMin(1)]
	public int rerollOnFailStreak { get { return _rerollOnFailStreak.Get(); } set { _rerollOnFailStreak.Set( value ); } }

	[Category( "Slots by level" )]
	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<EBoostsCategory> slots { get { return _slots; } set { _slots.Assign( value ); } }

	[Category( "Re-roll by Level" )]
	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<bool> canReroll { get { return _canReroll; } set { _canReroll.Assign( value ); } }

	[Category( "Boosts usage templates" )]
	[EnumArray(typeof(EBoostType))]
	public libdb.IChangeableList<DBBoostTemplate> boostsTemplate { get { return _boostsTemplate; } set { _boostsTemplate.Assign( value ); } }

	[Category( "Boosts tooltips" )]
	[EnumArray(typeof(EBoostType))]
	public libdb.IChangeableList<TextRef> boostsTooltips { get { return _boostsTooltips; } set { _boostsTooltips.Assign( value ); } }

	[Category( "Slots pricing" )]
	[EnumArray(typeof(EBoostsCategory))]
	public libdb.IChangeableList<int> slotsPrices { get { return _slotsPrices; } set { _slotsPrices.Assign( value ); } }

	[Category( "Regenerate pricing" )]
	[EnumArray(typeof(EBoostsCategory))]
	public libdb.IChangeableList<int> regenPrices { get { return _regenPrices; } set { _regenPrices.Assign( value ); } }

	[Category( "Boosts UI images" )]
	[EnumArray(typeof(EBoostType))]
	public libdb.IChangeableList<DBPtr<UITexture>> images { get { return _images; } set { _images.Assign( value ); } }

	[Category( "Complete boosts set" )]
	public DBPaintBlastBoost paintblast { get { return _paintblast; } set { _paintblast.Assign( value ); } }

	public DBFreezeBoost freeze { get { return _freeze; } set { _freeze.Assign( value ); } }

	public DBJokerBoost joker { get { return _joker; } set { _joker.Assign( value ); } }

	public DBSorterBoost sorter { get { return _sorter; } set { _sorter.Assign( value ); } }

	public DBMagnetBoost magnet { get { return _magnet; } set { _magnet.Assign( value ); } }

	public DBAlchemistBoost alchemist { get { return _alchemist; } set { _alchemist.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_rerollOnWinStreak = new UndoRedo<int>( owner, 1 );
		_rerollOnFailStreak = new UndoRedo<int>( owner, 3 );
		_slots = new UndoRedoList<EBoostsCategory>( owner, typeof( EPriestessLevel ) );
		_canReroll = new UndoRedoList<bool>( owner, typeof( EPriestessLevel ) );
		_boostsTemplate = new UndoRedoAssignableList<DBBoostTemplate>( owner, typeof( EBoostType ) );
		_boostsTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EBoostType ) );
		_slotsPrices = new UndoRedoList<int>( owner, typeof( EBoostsCategory ) );
		_regenPrices = new UndoRedoList<int>( owner, typeof( EBoostsCategory ) );
		_images = new UndoRedoAssignableList<DBPtr<UITexture>>( owner, typeof( EBoostType ) );
		_paintblast = new DBPaintBlastBoost( owner );
		_freeze = new DBFreezeBoost( owner );
		_joker = new DBJokerBoost( owner );
		_sorter = new DBSorterBoost( owner );
		_magnet = new DBMagnetBoost( owner );
		_alchemist = new DBAlchemistBoost( owner );
		_rerollOnWinStreak.Changed += FireChangedEvent;
		_rerollOnFailStreak.Changed += FireChangedEvent;
		_slots.Changed += FireChangedEvent;
		_canReroll.Changed += FireChangedEvent;
		_boostsTemplate.Changed += FireChangedEvent;
		_boostsTooltips.Changed += FireChangedEvent;
		_slotsPrices.Changed += FireChangedEvent;
		_regenPrices.Changed += FireChangedEvent;
		_images.Changed += FireChangedEvent;
		_paintblast.Changed += FireChangedEvent;
		_freeze.Changed += FireChangedEvent;
		_joker.Changed += FireChangedEvent;
		_sorter.Changed += FireChangedEvent;
		_magnet.Changed += FireChangedEvent;
		_alchemist.Changed += FireChangedEvent;
	}

	public DBBoostList()
	{
		Initialize( GetOwner() );
	}

	public DBBoostList( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBBoostList( DBResource owner, DBBoostList source )
		: this(owner, source, true){}

	protected DBBoostList( DBResource owner, DBBoostList source, bool fireEvent )
	{
		_rerollOnWinStreak = new UndoRedo<int>( owner, source.rerollOnWinStreak );
		_rerollOnFailStreak = new UndoRedo<int>( owner, source.rerollOnFailStreak );
		_slots = new UndoRedoList<EBoostsCategory>( owner, typeof( EPriestessLevel ) );
		_slots.Assign( source.slots );
		_canReroll = new UndoRedoList<bool>( owner, typeof( EPriestessLevel ) );
		_canReroll.Assign( source.canReroll );
		_boostsTemplate = new UndoRedoAssignableList<DBBoostTemplate>( owner, typeof( EBoostType ) );
		_boostsTemplate.Assign( source.boostsTemplate );
		_boostsTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EBoostType ) );
		_boostsTooltips.Assign( source.boostsTooltips );
		_slotsPrices = new UndoRedoList<int>( owner, typeof( EBoostsCategory ) );
		_slotsPrices.Assign( source.slotsPrices );
		_regenPrices = new UndoRedoList<int>( owner, typeof( EBoostsCategory ) );
		_regenPrices.Assign( source.regenPrices );
		_images = new UndoRedoAssignableList<DBPtr<UITexture>>( owner, typeof( EBoostType ) );
		_images.Assign( source.images );
		_paintblast = new DBPaintBlastBoost( owner, source.paintblast );
		_freeze = new DBFreezeBoost( owner, source.freeze );
		_joker = new DBJokerBoost( owner, source.joker );
		_sorter = new DBSorterBoost( owner, source.sorter );
		_magnet = new DBMagnetBoost( owner, source.magnet );
		_alchemist = new DBAlchemistBoost( owner, source.alchemist );
		_rerollOnWinStreak.Changed += FireChangedEvent;
		_rerollOnFailStreak.Changed += FireChangedEvent;
		_slots.Changed += FireChangedEvent;
		_canReroll.Changed += FireChangedEvent;
		_boostsTemplate.Changed += FireChangedEvent;
		_boostsTooltips.Changed += FireChangedEvent;
		_slotsPrices.Changed += FireChangedEvent;
		_regenPrices.Changed += FireChangedEvent;
		_images.Changed += FireChangedEvent;
		_paintblast.Changed += FireChangedEvent;
		_freeze.Changed += FireChangedEvent;
		_joker.Changed += FireChangedEvent;
		_sorter.Changed += FireChangedEvent;
		_magnet.Changed += FireChangedEvent;
		_alchemist.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBBoostList source = _source as DBBoostList;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBBoostList" );
		rerollOnWinStreak = source.rerollOnWinStreak;
		rerollOnFailStreak = source.rerollOnFailStreak;
		slots = source.slots;
		canReroll = source.canReroll;
		boostsTemplate = source.boostsTemplate;
		boostsTooltips = source.boostsTooltips;
		slotsPrices = source.slotsPrices;
		regenPrices = source.regenPrices;
		images = source.images;
		paintblast = source.paintblast;
		freeze = source.freeze;
		joker = source.joker;
		sorter = source.sorter;
		magnet = source.magnet;
		alchemist = source.alchemist;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBBoostList newParent = _newParent as DBBoostList;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rerollOnWinStreak.SetParent( newParent == null ? null : newParent._rerollOnWinStreak );
		_rerollOnFailStreak.SetParent( newParent == null ? null : newParent._rerollOnFailStreak );
		_slots.SetParent( newParent == null ? null : newParent._slots );
		_canReroll.SetParent( newParent == null ? null : newParent._canReroll );
		_boostsTemplate.SetParent( newParent == null ? null : newParent._boostsTemplate );
		_boostsTooltips.SetParent( newParent == null ? null : newParent._boostsTooltips );
		_slotsPrices.SetParent( newParent == null ? null : newParent._slotsPrices );
		_regenPrices.SetParent( newParent == null ? null : newParent._regenPrices );
		_images.SetParent( newParent == null ? null : newParent._images );
		_paintblast.SetParent( newParent == null ? null : newParent._paintblast );
		_freeze.SetParent( newParent == null ? null : newParent._freeze );
		_joker.SetParent( newParent == null ? null : newParent._joker );
		_sorter.SetParent( newParent == null ? null : newParent._sorter );
		_magnet.SetParent( newParent == null ? null : newParent._magnet );
		_alchemist.SetParent( newParent == null ? null : newParent._alchemist );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rerollOnWinStreak.Reset();
		_rerollOnFailStreak.Reset();
		_slots.Reset();
		_canReroll.Reset();
		_boostsTemplate.Reset();
		_boostsTooltips.Reset();
		_slotsPrices.Reset();
		_regenPrices.Reset();
		_images.Reset();
		_paintblast.Reset();
		_freeze.Reset();
		_joker.Reset();
		_sorter.Reset();
		_magnet.Reset();
		_alchemist.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rerollOnWinStreak.IsDerivedFromParent()
			&& _rerollOnFailStreak.IsDerivedFromParent()
			&& _slots.IsDerivedFromParent()
			&& _canReroll.IsDerivedFromParent()
			&& _boostsTemplate.IsDerivedFromParent()
			&& _boostsTooltips.IsDerivedFromParent()
			&& _slotsPrices.IsDerivedFromParent()
			&& _regenPrices.IsDerivedFromParent()
			&& _images.IsDerivedFromParent()
			&& _paintblast.IsDerivedFromParent()
			&& _freeze.IsDerivedFromParent()
			&& _joker.IsDerivedFromParent()
			&& _sorter.IsDerivedFromParent()
			&& _magnet.IsDerivedFromParent()
			&& _alchemist.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rerollOnWinStreak" )
			_rerollOnWinStreak.Reset();
		else if ( fieldName == "rerollOnFailStreak" )
			_rerollOnFailStreak.Reset();
		else if ( fieldName == "slots" )
			_slots.Reset();
		else if ( fieldName == "canReroll" )
			_canReroll.Reset();
		else if ( fieldName == "boostsTemplate" )
			_boostsTemplate.Reset();
		else if ( fieldName == "boostsTooltips" )
			_boostsTooltips.Reset();
		else if ( fieldName == "slotsPrices" )
			_slotsPrices.Reset();
		else if ( fieldName == "regenPrices" )
			_regenPrices.Reset();
		else if ( fieldName == "images" )
			_images.Reset();
		else if ( fieldName == "paintblast" )
			_paintblast.Reset();
		else if ( fieldName == "freeze" )
			_freeze.Reset();
		else if ( fieldName == "joker" )
			_joker.Reset();
		else if ( fieldName == "sorter" )
			_sorter.Reset();
		else if ( fieldName == "magnet" )
			_magnet.Reset();
		else if ( fieldName == "alchemist" )
			_alchemist.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rerollOnWinStreak" )
			return _rerollOnWinStreak.IsDerivedFromParent();
		if ( fieldName == "rerollOnFailStreak" )
			return _rerollOnFailStreak.IsDerivedFromParent();
		if ( fieldName == "slots" )
			return _slots.IsDerivedFromParent();
		if ( fieldName == "canReroll" )
			return _canReroll.IsDerivedFromParent();
		if ( fieldName == "boostsTemplate" )
			return _boostsTemplate.IsDerivedFromParent();
		if ( fieldName == "boostsTooltips" )
			return _boostsTooltips.IsDerivedFromParent();
		if ( fieldName == "slotsPrices" )
			return _slotsPrices.IsDerivedFromParent();
		if ( fieldName == "regenPrices" )
			return _regenPrices.IsDerivedFromParent();
		if ( fieldName == "images" )
			return _images.IsDerivedFromParent();
		if ( fieldName == "paintblast" )
			return _paintblast.IsDerivedFromParent();
		if ( fieldName == "freeze" )
			return _freeze.IsDerivedFromParent();
		if ( fieldName == "joker" )
			return _joker.IsDerivedFromParent();
		if ( fieldName == "sorter" )
			return _sorter.IsDerivedFromParent();
		if ( fieldName == "magnet" )
			return _magnet.IsDerivedFromParent();
		if ( fieldName == "alchemist" )
			return _alchemist.IsDerivedFromParent();
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

public class DBSpeedMarker : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSpeedMarker __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _position;
	private UndoRedo<int> _speedmultiplier;
	private UndoRedo<int> _speedconstant;

	[Category( "SpeedMarker" )]
	[IntMin(0)]
	public int position { get { return _position.Get(); } set { _position.Set( value ); } }

	[IntMinMax(0, 100)]
	public int speedmultiplier { get { return _speedmultiplier.Get(); } set { _speedmultiplier.Set( value ); } }

	[IntMinMax(0, 1000)]
	public int speedconstant { get { return _speedconstant.Get(); } set { _speedconstant.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_position = new UndoRedo<int>( owner, 0 );
		_speedmultiplier = new UndoRedo<int>( owner, 0 );
		_speedconstant = new UndoRedo<int>( owner, 0 );
		_position.Changed += FireChangedEvent;
		_speedmultiplier.Changed += FireChangedEvent;
		_speedconstant.Changed += FireChangedEvent;
	}

	public DBSpeedMarker()
	{
		Initialize( GetOwner() );
	}

	public DBSpeedMarker( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSpeedMarker( DBResource owner, DBSpeedMarker source )
		: this(owner, source, true){}

	protected DBSpeedMarker( DBResource owner, DBSpeedMarker source, bool fireEvent )
	{
		_position = new UndoRedo<int>( owner, source.position );
		_speedmultiplier = new UndoRedo<int>( owner, source.speedmultiplier );
		_speedconstant = new UndoRedo<int>( owner, source.speedconstant );
		_position.Changed += FireChangedEvent;
		_speedmultiplier.Changed += FireChangedEvent;
		_speedconstant.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSpeedMarker source = _source as DBSpeedMarker;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSpeedMarker" );
		position = source.position;
		speedmultiplier = source.speedmultiplier;
		speedconstant = source.speedconstant;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSpeedMarker newParent = _newParent as DBSpeedMarker;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_position.SetParent( newParent == null ? null : newParent._position );
		_speedmultiplier.SetParent( newParent == null ? null : newParent._speedmultiplier );
		_speedconstant.SetParent( newParent == null ? null : newParent._speedconstant );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_position.Reset();
		_speedmultiplier.Reset();
		_speedconstant.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_position.IsDerivedFromParent()
			&& _speedmultiplier.IsDerivedFromParent()
			&& _speedconstant.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "speedmultiplier" )
			_speedmultiplier.Reset();
		else if ( fieldName == "speedconstant" )
			_speedconstant.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "speedmultiplier" )
			return _speedmultiplier.IsDerivedFromParent();
		if ( fieldName == "speedconstant" )
			return _speedconstant.IsDerivedFromParent();
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

public class DBSplinePoints : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSplinePoints __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBLogicPoint> _point;

	[Category( "Spline control points" )]
	public libdb.IChangeableList<DBLogicPoint> point { get { return _point; } set { _point.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_point = new UndoRedoAssignableList<DBLogicPoint>( owner );
		_point.Changed += FireChangedEvent;
	}

	public DBSplinePoints()
	{
		Initialize( GetOwner() );
	}

	public DBSplinePoints( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSplinePoints( DBResource owner, DBSplinePoints source )
		: this(owner, source, true){}

	protected DBSplinePoints( DBResource owner, DBSplinePoints source, bool fireEvent )
	{
		_point = new UndoRedoAssignableList<DBLogicPoint>( owner );
		_point.Assign( source.point );
		_point.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSplinePoints source = _source as DBSplinePoints;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSplinePoints" );
		point = source.point;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSplinePoints newParent = _newParent as DBSplinePoints;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_point.SetParent( newParent == null ? null : newParent._point );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_point.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_point.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "point" )
			_point.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "point" )
			return _point.IsDerivedFromParent();
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

public class DBSplineSpeedMarkers : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSplineSpeedMarkers __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBSpeedMarker> _speedmarker;

	[Category( "Spline speed markers" )]
	public libdb.IChangeableList<DBSpeedMarker> speedmarker { get { return _speedmarker; } set { _speedmarker.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_speedmarker = new UndoRedoAssignableList<DBSpeedMarker>( owner );
		_speedmarker.Changed += FireChangedEvent;
	}

	public DBSplineSpeedMarkers()
	{
		Initialize( GetOwner() );
	}

	public DBSplineSpeedMarkers( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSplineSpeedMarkers( DBResource owner, DBSplineSpeedMarkers source )
		: this(owner, source, true){}

	protected DBSplineSpeedMarkers( DBResource owner, DBSplineSpeedMarkers source, bool fireEvent )
	{
		_speedmarker = new UndoRedoAssignableList<DBSpeedMarker>( owner );
		_speedmarker.Assign( source.speedmarker );
		_speedmarker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSplineSpeedMarkers source = _source as DBSplineSpeedMarkers;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSplineSpeedMarkers" );
		speedmarker = source.speedmarker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSplineSpeedMarkers newParent = _newParent as DBSplineSpeedMarkers;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_speedmarker.SetParent( newParent == null ? null : newParent._speedmarker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_speedmarker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_speedmarker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "speedmarker" )
			_speedmarker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "speedmarker" )
			return _speedmarker.IsDerivedFromParent();
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

public class DBSpline : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSpline __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _degree;
	private UndoRedo<int> _cpnum;
	private DBSplinePoints _points;

	[Category( "Spline parameters" )]
	[IntMinMax(0, 10)]
	public int degree { get { return _degree.Get(); } set { _degree.Set( value ); } }

	[IntMinMax(0, 100)]
	public int cpnum { get { return _cpnum.Get(); } set { _cpnum.Set( value ); } }

	public DBSplinePoints points { get { return _points; } set { _points.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_degree = new UndoRedo<int>( owner, 3 );
		_cpnum = new UndoRedo<int>( owner, 0 );
		_points = new DBSplinePoints( owner );
		_degree.Changed += FireChangedEvent;
		_cpnum.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
	}

	public DBSpline()
	{
		Initialize( GetOwner() );
	}

	public DBSpline( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSpline( DBResource owner, DBSpline source )
		: this(owner, source, true){}

	protected DBSpline( DBResource owner, DBSpline source, bool fireEvent )
	{
		_degree = new UndoRedo<int>( owner, source.degree );
		_cpnum = new UndoRedo<int>( owner, source.cpnum );
		_points = new DBSplinePoints( owner, source.points );
		_degree.Changed += FireChangedEvent;
		_cpnum.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSpline source = _source as DBSpline;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSpline" );
		degree = source.degree;
		cpnum = source.cpnum;
		points = source.points;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSpline newParent = _newParent as DBSpline;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_degree.SetParent( newParent == null ? null : newParent._degree );
		_cpnum.SetParent( newParent == null ? null : newParent._cpnum );
		_points.SetParent( newParent == null ? null : newParent._points );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_degree.Reset();
		_cpnum.Reset();
		_points.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_degree.IsDerivedFromParent()
			&& _cpnum.IsDerivedFromParent()
			&& _points.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "degree" )
			_degree.Reset();
		else if ( fieldName == "cpnum" )
			_cpnum.Reset();
		else if ( fieldName == "points" )
			_points.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "degree" )
			return _degree.IsDerivedFromParent();
		if ( fieldName == "cpnum" )
			return _cpnum.IsDerivedFromParent();
		if ( fieldName == "points" )
			return _points.IsDerivedFromParent();
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

public class DBSplineStartEndPoint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSplineStartEndPoint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private AnimatedPlacement _placement;

	public AnimatedPlacement placement { get { return _placement; } set { _placement.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_placement = new AnimatedPlacement( owner );
		_placement.Changed += FireChangedEvent;
	}

	public DBSplineStartEndPoint()
	{
		Initialize( GetOwner() );
	}

	public DBSplineStartEndPoint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSplineStartEndPoint( DBResource owner, DBSplineStartEndPoint source )
		: this(owner, source, true){}

	protected DBSplineStartEndPoint( DBResource owner, DBSplineStartEndPoint source, bool fireEvent )
	{
		_placement = new AnimatedPlacement( owner, source.placement );
		_placement.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSplineStartEndPoint source = _source as DBSplineStartEndPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSplineStartEndPoint" );
		placement = source.placement;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSplineStartEndPoint newParent = _newParent as DBSplineStartEndPoint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_placement.SetParent( newParent == null ? null : newParent._placement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_placement.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_placement.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "placement" )
			_placement.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "placement" )
			return _placement.IsDerivedFromParent();
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

public class DBTunnel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBTunnel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _begin;
	private UndoRedo<int> _end;

	[Category( "Tunnel" )]
	[IntMin(0)]
	public int begin { get { return _begin.Get(); } set { _begin.Set( value ); } }

	[IntMin(0)]
	public int end { get { return _end.Get(); } set { _end.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_begin = new UndoRedo<int>( owner, 0 );
		_end = new UndoRedo<int>( owner, 0 );
		_begin.Changed += FireChangedEvent;
		_end.Changed += FireChangedEvent;
	}

	public DBTunnel()
	{
		Initialize( GetOwner() );
	}

	public DBTunnel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBTunnel( DBResource owner, DBTunnel source )
		: this(owner, source, true){}

	protected DBTunnel( DBResource owner, DBTunnel source, bool fireEvent )
	{
		_begin = new UndoRedo<int>( owner, source.begin );
		_end = new UndoRedo<int>( owner, source.end );
		_begin.Changed += FireChangedEvent;
		_end.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBTunnel source = _source as DBTunnel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBTunnel" );
		begin = source.begin;
		end = source.end;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBTunnel newParent = _newParent as DBTunnel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_begin.SetParent( newParent == null ? null : newParent._begin );
		_end.SetParent( newParent == null ? null : newParent._end );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_begin.Reset();
		_end.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_begin.IsDerivedFromParent()
			&& _end.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "begin" )
			_begin.Reset();
		else if ( fieldName == "end" )
			_end.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "begin" )
			return _begin.IsDerivedFromParent();
		if ( fieldName == "end" )
			return _end.IsDerivedFromParent();
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

public class DBSplineTunnels : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSplineTunnels __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBTunnel> _tunnel;

	[Category( "Spline tunnels" )]
	public libdb.IChangeableList<DBTunnel> tunnel { get { return _tunnel; } set { _tunnel.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_tunnel = new UndoRedoAssignableList<DBTunnel>( owner );
		_tunnel.Changed += FireChangedEvent;
	}

	public DBSplineTunnels()
	{
		Initialize( GetOwner() );
	}

	public DBSplineTunnels( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSplineTunnels( DBResource owner, DBSplineTunnels source )
		: this(owner, source, true){}

	protected DBSplineTunnels( DBResource owner, DBSplineTunnels source, bool fireEvent )
	{
		_tunnel = new UndoRedoAssignableList<DBTunnel>( owner );
		_tunnel.Assign( source.tunnel );
		_tunnel.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSplineTunnels source = _source as DBSplineTunnels;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSplineTunnels" );
		tunnel = source.tunnel;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSplineTunnels newParent = _newParent as DBSplineTunnels;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_tunnel.SetParent( newParent == null ? null : newParent._tunnel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_tunnel.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_tunnel.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "tunnel" )
			_tunnel.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "tunnel" )
			return _tunnel.IsDerivedFromParent();
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

public class DBSplineData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSplineData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _splinelenght;
	private DBSplineTunnels _tunnels;
	private DBSplineSpeedMarkers _speedmarkers;
	private DBSplineStartEndPoint _startPoint;
	private DBSplineStartEndPoint _endPoint;
	private Vec2 _atExitPoint;
	private UndoRedoAssignableList<DBPtr<DBEaselChains>> _chainparams;

	[IntMin(0)]
	public int splinelenght { get { return _splinelenght.Get(); } set { _splinelenght.Set( value ); } }

	public DBSplineTunnels tunnels { get { return _tunnels; } set { _tunnels.Assign( value ); } }

	public DBSplineSpeedMarkers speedmarkers { get { return _speedmarkers; } set { _speedmarkers.Assign( value ); } }

	public DBSplineStartEndPoint startPoint { get { return _startPoint; } set { _startPoint.Assign( value ); } }

	public DBSplineStartEndPoint endPoint { get { return _endPoint; } set { _endPoint.Assign( value ); } }

	public Vec2 atExitPoint { get { return _atExitPoint; } set { _atExitPoint.Assign( value ); } }

	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<DBPtr<DBEaselChains>> chainparams { get { return _chainparams; } set { _chainparams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_splinelenght = new UndoRedo<int>( owner, 0 );
		_tunnels = new DBSplineTunnels( owner );
		_speedmarkers = new DBSplineSpeedMarkers( owner );
		_startPoint = new DBSplineStartEndPoint( owner );
		_endPoint = new DBSplineStartEndPoint( owner );
		Vec2 __atExitPoint = new Vec2(); // Construct default object for atExitPoint
		__atExitPoint.y = 15.0f;
		_atExitPoint = new Vec2( owner, __atExitPoint );
		_chainparams = new UndoRedoAssignableList<DBPtr<DBEaselChains>>( owner, typeof( EPriestessLevel ) );
		_splinelenght.Changed += FireChangedEvent;
		_tunnels.Changed += FireChangedEvent;
		_speedmarkers.Changed += FireChangedEvent;
		_startPoint.Changed += FireChangedEvent;
		_endPoint.Changed += FireChangedEvent;
		_atExitPoint.Changed += FireChangedEvent;
		_chainparams.Changed += FireChangedEvent;
	}

	public DBSplineData()
	{
		Initialize( GetOwner() );
	}

	public DBSplineData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSplineData( DBResource owner, DBSplineData source )
		: this(owner, source, true){}

	protected DBSplineData( DBResource owner, DBSplineData source, bool fireEvent )
	{
		_splinelenght = new UndoRedo<int>( owner, source.splinelenght );
		_tunnels = new DBSplineTunnels( owner, source.tunnels );
		_speedmarkers = new DBSplineSpeedMarkers( owner, source.speedmarkers );
		_startPoint = new DBSplineStartEndPoint( owner, source.startPoint );
		_endPoint = new DBSplineStartEndPoint( owner, source.endPoint );
		_atExitPoint = new Vec2( owner, source.atExitPoint );
		_chainparams = new UndoRedoAssignableList<DBPtr<DBEaselChains>>( owner, typeof( EPriestessLevel ) );
		_chainparams.Assign( source.chainparams );
		_splinelenght.Changed += FireChangedEvent;
		_tunnels.Changed += FireChangedEvent;
		_speedmarkers.Changed += FireChangedEvent;
		_startPoint.Changed += FireChangedEvent;
		_endPoint.Changed += FireChangedEvent;
		_atExitPoint.Changed += FireChangedEvent;
		_chainparams.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSplineData source = _source as DBSplineData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSplineData" );
		splinelenght = source.splinelenght;
		tunnels = source.tunnels;
		speedmarkers = source.speedmarkers;
		startPoint = source.startPoint;
		endPoint = source.endPoint;
		atExitPoint = source.atExitPoint;
		chainparams = source.chainparams;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSplineData newParent = _newParent as DBSplineData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_splinelenght.SetParent( newParent == null ? null : newParent._splinelenght );
		_tunnels.SetParent( newParent == null ? null : newParent._tunnels );
		_speedmarkers.SetParent( newParent == null ? null : newParent._speedmarkers );
		_startPoint.SetParent( newParent == null ? null : newParent._startPoint );
		_endPoint.SetParent( newParent == null ? null : newParent._endPoint );
		_atExitPoint.SetParent( newParent == null ? null : newParent._atExitPoint );
		_chainparams.SetParent( newParent == null ? null : newParent._chainparams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_splinelenght.Reset();
		_tunnels.Reset();
		_speedmarkers.Reset();
		_startPoint.Reset();
		_endPoint.Reset();
		_atExitPoint.Reset();
		_chainparams.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_splinelenght.IsDerivedFromParent()
			&& _tunnels.IsDerivedFromParent()
			&& _speedmarkers.IsDerivedFromParent()
			&& _startPoint.IsDerivedFromParent()
			&& _endPoint.IsDerivedFromParent()
			&& _atExitPoint.IsDerivedFromParent()
			&& _chainparams.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "splinelenght" )
			_splinelenght.Reset();
		else if ( fieldName == "tunnels" )
			_tunnels.Reset();
		else if ( fieldName == "speedmarkers" )
			_speedmarkers.Reset();
		else if ( fieldName == "startPoint" )
			_startPoint.Reset();
		else if ( fieldName == "endPoint" )
			_endPoint.Reset();
		else if ( fieldName == "atExitPoint" )
			_atExitPoint.Reset();
		else if ( fieldName == "chainparams" )
			_chainparams.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "splinelenght" )
			return _splinelenght.IsDerivedFromParent();
		if ( fieldName == "tunnels" )
			return _tunnels.IsDerivedFromParent();
		if ( fieldName == "speedmarkers" )
			return _speedmarkers.IsDerivedFromParent();
		if ( fieldName == "startPoint" )
			return _startPoint.IsDerivedFromParent();
		if ( fieldName == "endPoint" )
			return _endPoint.IsDerivedFromParent();
		if ( fieldName == "atExitPoint" )
			return _atExitPoint.IsDerivedFromParent();
		if ( fieldName == "chainparams" )
			return _chainparams.IsDerivedFromParent();
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

public class EChainStatistics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EChainStatistics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<int> _colorBallsNum;
	private UndoRedo<int> _allBallsNum;

	[EnumArray(typeof(EColor))]
	public libdb.IChangeableList<int> colorBallsNum { get { return _colorBallsNum; } set { _colorBallsNum.Assign( value ); } }

	public int allBallsNum { get { return _allBallsNum.Get(); } set { _allBallsNum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_colorBallsNum = new UndoRedoList<int>( owner, typeof( EColor ) );
		_allBallsNum = new UndoRedo<int>( owner, 0 );
		_colorBallsNum.Changed += FireChangedEvent;
		_allBallsNum.Changed += FireChangedEvent;
	}

	public EChainStatistics()
	{
		Initialize( GetOwner() );
	}

	public EChainStatistics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EChainStatistics( DBResource owner, EChainStatistics source )
		: this(owner, source, true){}

	protected EChainStatistics( DBResource owner, EChainStatistics source, bool fireEvent )
	{
		_colorBallsNum = new UndoRedoList<int>( owner, typeof( EColor ) );
		_colorBallsNum.Assign( source.colorBallsNum );
		_allBallsNum = new UndoRedo<int>( owner, source.allBallsNum );
		_colorBallsNum.Changed += FireChangedEvent;
		_allBallsNum.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EChainStatistics source = _source as EChainStatistics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EChainStatistics" );
		colorBallsNum = source.colorBallsNum;
		allBallsNum = source.allBallsNum;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EChainStatistics newParent = _newParent as EChainStatistics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_colorBallsNum.SetParent( newParent == null ? null : newParent._colorBallsNum );
		_allBallsNum.SetParent( newParent == null ? null : newParent._allBallsNum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_colorBallsNum.Reset();
		_allBallsNum.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_colorBallsNum.IsDerivedFromParent()
			&& _allBallsNum.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "colorBallsNum" )
			_colorBallsNum.Reset();
		else if ( fieldName == "allBallsNum" )
			_allBallsNum.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "colorBallsNum" )
			return _colorBallsNum.IsDerivedFromParent();
		if ( fieldName == "allBallsNum" )
			return _allBallsNum.IsDerivedFromParent();
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

public class EPlatformGeneratorStatistics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EPlatformGeneratorStatistics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EColor> _lastColor;
	private UndoRedo<int> _lastColorRepeatNum;

	public EColor lastColor { get { return _lastColor.Get(); } set { _lastColor.Set( value ); } }

	public int lastColorRepeatNum { get { return _lastColorRepeatNum.Get(); } set { _lastColorRepeatNum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lastColor = new UndoRedo<EColor>( owner, EColor.black );
		_lastColorRepeatNum = new UndoRedo<int>( owner, 0 );
		_lastColor.Changed += FireChangedEvent;
		_lastColorRepeatNum.Changed += FireChangedEvent;
	}

	public EPlatformGeneratorStatistics()
	{
		Initialize( GetOwner() );
	}

	public EPlatformGeneratorStatistics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EPlatformGeneratorStatistics( DBResource owner, EPlatformGeneratorStatistics source )
		: this(owner, source, true){}

	protected EPlatformGeneratorStatistics( DBResource owner, EPlatformGeneratorStatistics source, bool fireEvent )
	{
		_lastColor = new UndoRedo<EColor>( owner, source.lastColor );
		_lastColorRepeatNum = new UndoRedo<int>( owner, source.lastColorRepeatNum );
		_lastColor.Changed += FireChangedEvent;
		_lastColorRepeatNum.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EPlatformGeneratorStatistics source = _source as EPlatformGeneratorStatistics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EPlatformGeneratorStatistics" );
		lastColor = source.lastColor;
		lastColorRepeatNum = source.lastColorRepeatNum;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EPlatformGeneratorStatistics newParent = _newParent as EPlatformGeneratorStatistics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lastColor.SetParent( newParent == null ? null : newParent._lastColor );
		_lastColorRepeatNum.SetParent( newParent == null ? null : newParent._lastColorRepeatNum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lastColor.Reset();
		_lastColorRepeatNum.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lastColor.IsDerivedFromParent()
			&& _lastColorRepeatNum.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lastColor" )
			_lastColor.Reset();
		else if ( fieldName == "lastColorRepeatNum" )
			_lastColorRepeatNum.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lastColor" )
			return _lastColor.IsDerivedFromParent();
		if ( fieldName == "lastColorRepeatNum" )
			return _lastColorRepeatNum.IsDerivedFromParent();
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

public class EPaintStatistics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EPaintStatistics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<int> _remainColorCapacity;
	private UndoRedoList<EColor> _allPaintColors;
	private UndoRedo<int> _remainColorsToPaint;
	private UndoRedo<int> _remainPaintCapacity;

	[EnumArray(typeof(EColor))]
	public libdb.IChangeableList<int> remainColorCapacity { get { return _remainColorCapacity; } set { _remainColorCapacity.Assign( value ); } }

	public libdb.IChangeableList<EColor> allPaintColors { get { return _allPaintColors; } set { _allPaintColors.Assign( value ); } }

	public int remainColorsToPaint { get { return _remainColorsToPaint.Get(); } set { _remainColorsToPaint.Set( value ); } }

	public int remainPaintCapacity { get { return _remainPaintCapacity.Get(); } set { _remainPaintCapacity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_remainColorCapacity = new UndoRedoList<int>( owner, typeof( EColor ) );
		_allPaintColors = new UndoRedoList<EColor>( owner );
		_remainColorsToPaint = new UndoRedo<int>( owner, 0 );
		_remainPaintCapacity = new UndoRedo<int>( owner, 0 );
		_remainColorCapacity.Changed += FireChangedEvent;
		_allPaintColors.Changed += FireChangedEvent;
		_remainColorsToPaint.Changed += FireChangedEvent;
		_remainPaintCapacity.Changed += FireChangedEvent;
	}

	public EPaintStatistics()
	{
		Initialize( GetOwner() );
	}

	public EPaintStatistics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EPaintStatistics( DBResource owner, EPaintStatistics source )
		: this(owner, source, true){}

	protected EPaintStatistics( DBResource owner, EPaintStatistics source, bool fireEvent )
	{
		_remainColorCapacity = new UndoRedoList<int>( owner, typeof( EColor ) );
		_remainColorCapacity.Assign( source.remainColorCapacity );
		_allPaintColors = new UndoRedoList<EColor>( owner );
		_allPaintColors.Assign( source.allPaintColors );
		_remainColorsToPaint = new UndoRedo<int>( owner, source.remainColorsToPaint );
		_remainPaintCapacity = new UndoRedo<int>( owner, source.remainPaintCapacity );
		_remainColorCapacity.Changed += FireChangedEvent;
		_allPaintColors.Changed += FireChangedEvent;
		_remainColorsToPaint.Changed += FireChangedEvent;
		_remainPaintCapacity.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EPaintStatistics source = _source as EPaintStatistics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EPaintStatistics" );
		remainColorCapacity = source.remainColorCapacity;
		allPaintColors = source.allPaintColors;
		remainColorsToPaint = source.remainColorsToPaint;
		remainPaintCapacity = source.remainPaintCapacity;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EPaintStatistics newParent = _newParent as EPaintStatistics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_remainColorCapacity.SetParent( newParent == null ? null : newParent._remainColorCapacity );
		_allPaintColors.SetParent( newParent == null ? null : newParent._allPaintColors );
		_remainColorsToPaint.SetParent( newParent == null ? null : newParent._remainColorsToPaint );
		_remainPaintCapacity.SetParent( newParent == null ? null : newParent._remainPaintCapacity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_remainColorCapacity.Reset();
		_allPaintColors.Reset();
		_remainColorsToPaint.Reset();
		_remainPaintCapacity.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_remainColorCapacity.IsDerivedFromParent()
			&& _allPaintColors.IsDerivedFromParent()
			&& _remainColorsToPaint.IsDerivedFromParent()
			&& _remainPaintCapacity.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "remainColorCapacity" )
			_remainColorCapacity.Reset();
		else if ( fieldName == "allPaintColors" )
			_allPaintColors.Reset();
		else if ( fieldName == "remainColorsToPaint" )
			_remainColorsToPaint.Reset();
		else if ( fieldName == "remainPaintCapacity" )
			_remainPaintCapacity.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "remainColorCapacity" )
			return _remainColorCapacity.IsDerivedFromParent();
		if ( fieldName == "allPaintColors" )
			return _allPaintColors.IsDerivedFromParent();
		if ( fieldName == "remainColorsToPaint" )
			return _remainColorsToPaint.IsDerivedFromParent();
		if ( fieldName == "remainPaintCapacity" )
			return _remainPaintCapacity.IsDerivedFromParent();
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

public class EPlatformGeneratorParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EPlatformGeneratorParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _maxRepeatColorNum;

	[MinMaxSize(0, 10)]
	public int maxRepeatColorNum { get { return _maxRepeatColorNum.Get(); } set { _maxRepeatColorNum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_maxRepeatColorNum = new UndoRedo<int>( owner, 0 );
		_maxRepeatColorNum.Changed += FireChangedEvent;
	}

	public EPlatformGeneratorParams()
	{
		Initialize( GetOwner() );
	}

	public EPlatformGeneratorParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EPlatformGeneratorParams( DBResource owner, EPlatformGeneratorParams source )
		: this(owner, source, true){}

	protected EPlatformGeneratorParams( DBResource owner, EPlatformGeneratorParams source, bool fireEvent )
	{
		_maxRepeatColorNum = new UndoRedo<int>( owner, source.maxRepeatColorNum );
		_maxRepeatColorNum.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EPlatformGeneratorParams source = _source as EPlatformGeneratorParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EPlatformGeneratorParams" );
		maxRepeatColorNum = source.maxRepeatColorNum;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EPlatformGeneratorParams newParent = _newParent as EPlatformGeneratorParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maxRepeatColorNum.SetParent( newParent == null ? null : newParent._maxRepeatColorNum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maxRepeatColorNum.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maxRepeatColorNum.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maxRepeatColorNum" )
			_maxRepeatColorNum.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maxRepeatColorNum" )
			return _maxRepeatColorNum.IsDerivedFromParent();
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

public class ELuxorStatistics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ELuxorStatistics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _remainDistanceForFirstChain;
	private UndoRedo<int> _remainDistanceForFirstChainPercent;
	private UndoRedoAssignableList<EChainStatistics> _chainStatistics;
	private EPlatformGeneratorStatistics _generatorStatistics;
	private BulletStatistics _bulletStats;
	private UndoRedoList<float> _colorWeights;

	public int remainDistanceForFirstChain { get { return _remainDistanceForFirstChain.Get(); } set { _remainDistanceForFirstChain.Set( value ); } }

	public int remainDistanceForFirstChainPercent { get { return _remainDistanceForFirstChainPercent.Get(); } set { _remainDistanceForFirstChainPercent.Set( value ); } }

	[EnumArray(typeof(EChainsStatisticsType))]
	public libdb.IChangeableList<EChainStatistics> chainStatistics { get { return _chainStatistics; } set { _chainStatistics.Assign( value ); } }

	public EPlatformGeneratorStatistics generatorStatistics { get { return _generatorStatistics; } set { _generatorStatistics.Assign( value ); } }

	public BulletStatistics bulletStats { get { return _bulletStats; } set { _bulletStats.Assign( value ); } }

	[Description( "Weights of colors based on sum of ratios : COLOR_BALL_PATH/PATH_LENGTH " )]
	[EnumArray(typeof(EColor))]
	public libdb.IChangeableList<float> colorWeights { get { return _colorWeights; } set { _colorWeights.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_remainDistanceForFirstChain = new UndoRedo<int>( owner, 0 );
		_remainDistanceForFirstChainPercent = new UndoRedo<int>( owner, 0 );
		_chainStatistics = new UndoRedoAssignableList<EChainStatistics>( owner, typeof( EChainsStatisticsType ) );
		_generatorStatistics = new EPlatformGeneratorStatistics( owner );
		_bulletStats = new BulletStatistics( owner );
		_colorWeights = new UndoRedoList<float>( owner, typeof( EColor ) );
		_remainDistanceForFirstChain.Changed += FireChangedEvent;
		_remainDistanceForFirstChainPercent.Changed += FireChangedEvent;
		_chainStatistics.Changed += FireChangedEvent;
		_generatorStatistics.Changed += FireChangedEvent;
		_bulletStats.Changed += FireChangedEvent;
		_colorWeights.Changed += FireChangedEvent;
	}

	public ELuxorStatistics()
	{
		Initialize( GetOwner() );
	}

	public ELuxorStatistics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ELuxorStatistics( DBResource owner, ELuxorStatistics source )
		: this(owner, source, true){}

	protected ELuxorStatistics( DBResource owner, ELuxorStatistics source, bool fireEvent )
	{
		_remainDistanceForFirstChain = new UndoRedo<int>( owner, source.remainDistanceForFirstChain );
		_remainDistanceForFirstChainPercent = new UndoRedo<int>( owner, source.remainDistanceForFirstChainPercent );
		_chainStatistics = new UndoRedoAssignableList<EChainStatistics>( owner, typeof( EChainsStatisticsType ) );
		_chainStatistics.Assign( source.chainStatistics );
		_generatorStatistics = new EPlatformGeneratorStatistics( owner, source.generatorStatistics );
		_bulletStats = new BulletStatistics( owner, source.bulletStats );
		_colorWeights = new UndoRedoList<float>( owner, typeof( EColor ) );
		_colorWeights.Assign( source.colorWeights );
		_remainDistanceForFirstChain.Changed += FireChangedEvent;
		_remainDistanceForFirstChainPercent.Changed += FireChangedEvent;
		_chainStatistics.Changed += FireChangedEvent;
		_generatorStatistics.Changed += FireChangedEvent;
		_bulletStats.Changed += FireChangedEvent;
		_colorWeights.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ELuxorStatistics source = _source as ELuxorStatistics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ELuxorStatistics" );
		remainDistanceForFirstChain = source.remainDistanceForFirstChain;
		remainDistanceForFirstChainPercent = source.remainDistanceForFirstChainPercent;
		chainStatistics = source.chainStatistics;
		generatorStatistics = source.generatorStatistics;
		bulletStats = source.bulletStats;
		colorWeights = source.colorWeights;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ELuxorStatistics newParent = _newParent as ELuxorStatistics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_remainDistanceForFirstChain.SetParent( newParent == null ? null : newParent._remainDistanceForFirstChain );
		_remainDistanceForFirstChainPercent.SetParent( newParent == null ? null : newParent._remainDistanceForFirstChainPercent );
		_chainStatistics.SetParent( newParent == null ? null : newParent._chainStatistics );
		_generatorStatistics.SetParent( newParent == null ? null : newParent._generatorStatistics );
		_bulletStats.SetParent( newParent == null ? null : newParent._bulletStats );
		_colorWeights.SetParent( newParent == null ? null : newParent._colorWeights );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_remainDistanceForFirstChain.Reset();
		_remainDistanceForFirstChainPercent.Reset();
		_chainStatistics.Reset();
		_generatorStatistics.Reset();
		_bulletStats.Reset();
		_colorWeights.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_remainDistanceForFirstChain.IsDerivedFromParent()
			&& _remainDistanceForFirstChainPercent.IsDerivedFromParent()
			&& _chainStatistics.IsDerivedFromParent()
			&& _generatorStatistics.IsDerivedFromParent()
			&& _bulletStats.IsDerivedFromParent()
			&& _colorWeights.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "remainDistanceForFirstChain" )
			_remainDistanceForFirstChain.Reset();
		else if ( fieldName == "remainDistanceForFirstChainPercent" )
			_remainDistanceForFirstChainPercent.Reset();
		else if ( fieldName == "chainStatistics" )
			_chainStatistics.Reset();
		else if ( fieldName == "generatorStatistics" )
			_generatorStatistics.Reset();
		else if ( fieldName == "bulletStats" )
			_bulletStats.Reset();
		else if ( fieldName == "colorWeights" )
			_colorWeights.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "remainDistanceForFirstChain" )
			return _remainDistanceForFirstChain.IsDerivedFromParent();
		if ( fieldName == "remainDistanceForFirstChainPercent" )
			return _remainDistanceForFirstChainPercent.IsDerivedFromParent();
		if ( fieldName == "chainStatistics" )
			return _chainStatistics.IsDerivedFromParent();
		if ( fieldName == "generatorStatistics" )
			return _generatorStatistics.IsDerivedFromParent();
		if ( fieldName == "bulletStats" )
			return _bulletStats.IsDerivedFromParent();
		if ( fieldName == "colorWeights" )
			return _colorWeights.IsDerivedFromParent();
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

public class PaintFragmentFillParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PaintFragmentFillParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _paintFillStartTime;
	private UndoRedo<float> _fillInterval;
	private UndoRedo<float> _completeFadeIn;
	private UndoRedo<float> _completeEffectFadeIn;
	private UndoRedo<float> _completeEffectFadeOut;

	public float paintFillStartTime { get { return _paintFillStartTime.Get(); } set { _paintFillStartTime.Set( value ); } }

	public float fillInterval { get { return _fillInterval.Get(); } set { _fillInterval.Set( value ); } }

	public float completeFadeIn { get { return _completeFadeIn.Get(); } set { _completeFadeIn.Set( value ); } }

	public float completeEffectFadeIn { get { return _completeEffectFadeIn.Get(); } set { _completeEffectFadeIn.Set( value ); } }

	public float completeEffectFadeOut { get { return _completeEffectFadeOut.Get(); } set { _completeEffectFadeOut.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_paintFillStartTime = new UndoRedo<float>( owner, 1.1f );
		_fillInterval = new UndoRedo<float>( owner, 1.0f );
		_completeFadeIn = new UndoRedo<float>( owner, 1.0f );
		_completeEffectFadeIn = new UndoRedo<float>( owner, 1.0f );
		_completeEffectFadeOut = new UndoRedo<float>( owner, 2.0f );
		_paintFillStartTime.Changed += FireChangedEvent;
		_fillInterval.Changed += FireChangedEvent;
		_completeFadeIn.Changed += FireChangedEvent;
		_completeEffectFadeIn.Changed += FireChangedEvent;
		_completeEffectFadeOut.Changed += FireChangedEvent;
	}

	public PaintFragmentFillParams()
	{
		Initialize( GetOwner() );
	}

	public PaintFragmentFillParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PaintFragmentFillParams( DBResource owner, PaintFragmentFillParams source )
		: this(owner, source, true){}

	protected PaintFragmentFillParams( DBResource owner, PaintFragmentFillParams source, bool fireEvent )
	{
		_paintFillStartTime = new UndoRedo<float>( owner, source.paintFillStartTime );
		_fillInterval = new UndoRedo<float>( owner, source.fillInterval );
		_completeFadeIn = new UndoRedo<float>( owner, source.completeFadeIn );
		_completeEffectFadeIn = new UndoRedo<float>( owner, source.completeEffectFadeIn );
		_completeEffectFadeOut = new UndoRedo<float>( owner, source.completeEffectFadeOut );
		_paintFillStartTime.Changed += FireChangedEvent;
		_fillInterval.Changed += FireChangedEvent;
		_completeFadeIn.Changed += FireChangedEvent;
		_completeEffectFadeIn.Changed += FireChangedEvent;
		_completeEffectFadeOut.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PaintFragmentFillParams source = _source as PaintFragmentFillParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PaintFragmentFillParams" );
		paintFillStartTime = source.paintFillStartTime;
		fillInterval = source.fillInterval;
		completeFadeIn = source.completeFadeIn;
		completeEffectFadeIn = source.completeEffectFadeIn;
		completeEffectFadeOut = source.completeEffectFadeOut;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PaintFragmentFillParams newParent = _newParent as PaintFragmentFillParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_paintFillStartTime.SetParent( newParent == null ? null : newParent._paintFillStartTime );
		_fillInterval.SetParent( newParent == null ? null : newParent._fillInterval );
		_completeFadeIn.SetParent( newParent == null ? null : newParent._completeFadeIn );
		_completeEffectFadeIn.SetParent( newParent == null ? null : newParent._completeEffectFadeIn );
		_completeEffectFadeOut.SetParent( newParent == null ? null : newParent._completeEffectFadeOut );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_paintFillStartTime.Reset();
		_fillInterval.Reset();
		_completeFadeIn.Reset();
		_completeEffectFadeIn.Reset();
		_completeEffectFadeOut.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_paintFillStartTime.IsDerivedFromParent()
			&& _fillInterval.IsDerivedFromParent()
			&& _completeFadeIn.IsDerivedFromParent()
			&& _completeEffectFadeIn.IsDerivedFromParent()
			&& _completeEffectFadeOut.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "paintFillStartTime" )
			_paintFillStartTime.Reset();
		else if ( fieldName == "fillInterval" )
			_fillInterval.Reset();
		else if ( fieldName == "completeFadeIn" )
			_completeFadeIn.Reset();
		else if ( fieldName == "completeEffectFadeIn" )
			_completeEffectFadeIn.Reset();
		else if ( fieldName == "completeEffectFadeOut" )
			_completeEffectFadeOut.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "paintFillStartTime" )
			return _paintFillStartTime.IsDerivedFromParent();
		if ( fieldName == "fillInterval" )
			return _fillInterval.IsDerivedFromParent();
		if ( fieldName == "completeFadeIn" )
			return _completeFadeIn.IsDerivedFromParent();
		if ( fieldName == "completeEffectFadeIn" )
			return _completeEffectFadeIn.IsDerivedFromParent();
		if ( fieldName == "completeEffectFadeOut" )
			return _completeEffectFadeOut.IsDerivedFromParent();
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

public class Magnet : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Magnet __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<BasicEffectStandalone> _magnetHighlight;
	private UndoRedoDBPtr<BasicEffectStandalone> _magnetPreselect;
	private UndoRedoDBPtr<BasicEffectStandalone> _magnet;

	public DBPtr<BasicEffectStandalone> magnetHighlight { get { return _magnetHighlight.Get(); } set { _magnetHighlight.Set( value ); } }

	public DBPtr<BasicEffectStandalone> magnetPreselect { get { return _magnetPreselect.Get(); } set { _magnetPreselect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> magnet { get { return _magnet.Get(); } set { _magnet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_magnetHighlight = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_magnetPreselect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_magnet = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_magnetHighlight.Changed += FireChangedEvent;
		_magnetPreselect.Changed += FireChangedEvent;
		_magnet.Changed += FireChangedEvent;
	}

	public Magnet()
	{
		Initialize( GetOwner() );
	}

	public Magnet( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Magnet( DBResource owner, Magnet source )
		: this(owner, source, true){}

	protected Magnet( DBResource owner, Magnet source, bool fireEvent )
	{
		_magnetHighlight = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.magnetHighlight );
		_magnetPreselect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.magnetPreselect );
		_magnet = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.magnet );
		_magnetHighlight.Changed += FireChangedEvent;
		_magnetPreselect.Changed += FireChangedEvent;
		_magnet.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Magnet source = _source as Magnet;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Magnet" );
		magnetHighlight = source.magnetHighlight;
		magnetPreselect = source.magnetPreselect;
		magnet = source.magnet;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Magnet newParent = _newParent as Magnet;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_magnetHighlight.SetParent( newParent == null ? null : newParent._magnetHighlight );
		_magnetPreselect.SetParent( newParent == null ? null : newParent._magnetPreselect );
		_magnet.SetParent( newParent == null ? null : newParent._magnet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_magnetHighlight.Reset();
		_magnetPreselect.Reset();
		_magnet.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_magnetHighlight.IsDerivedFromParent()
			&& _magnetPreselect.IsDerivedFromParent()
			&& _magnet.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "magnetHighlight" )
			_magnetHighlight.Reset();
		else if ( fieldName == "magnetPreselect" )
			_magnetPreselect.Reset();
		else if ( fieldName == "magnet" )
			_magnet.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "magnetHighlight" )
			return _magnetHighlight.IsDerivedFromParent();
		if ( fieldName == "magnetPreselect" )
			return _magnetPreselect.IsDerivedFromParent();
		if ( fieldName == "magnet" )
			return _magnet.IsDerivedFromParent();
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

[DBVersion(3)]
public class DBEaselEffectView : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBEaselEffectView __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<BasicEffectStandalone> _paintblastExplosion;
	private UndoRedoDBPtr<BasicEffectStandalone> _freezeEffect;
	private UndoRedoDBPtr<BasicEffectAttached> _coinPickUp;
	private UndoRedoDBPtr<BasicEffectStandalone> _gameStartEffect;
	private UndoRedoDBPtr<BasicEffectStandalone> _gameWonEffect;
	private UndoRedoDBPtr<BasicEffectStandalone> _sortEffect;
	private UndoRedoDBPtr<BasicEffectStandalone> _ballExplosion;
	private ExplosionParams _explosionParams;
	private UndoRedo<float> _flowIntervalsStartDistance;
	private UndoRedo<float> _flowScale;
	private PaintFragmentFillParams _fillParams;
	private UndoRedoAssignableList<DBEaselFlowEffectGroup> _flowGroups;
	private UndoRedoDBPtr<BasicEffectStandalone> _flowTouchEffect;
	private UndoRedoDBPtr<BasicEffectStandalone> _pathfinderHead;
	private UndoRedoDBPtr<BasicEffectStandalone> _pathfinderTail;
	private UndoRedo<float> _pathfinderVelocity;
	private UndoRedo<float> _pathfinderInterval;

	public DBPtr<BasicEffectStandalone> paintblastExplosion { get { return _paintblastExplosion.Get(); } set { _paintblastExplosion.Set( value ); } }

	public DBPtr<BasicEffectStandalone> freezeEffect { get { return _freezeEffect.Get(); } set { _freezeEffect.Set( value ); } }

	public DBPtr<BasicEffectAttached> coinPickUp { get { return _coinPickUp.Get(); } set { _coinPickUp.Set( value ); } }

	public DBPtr<BasicEffectStandalone> gameStartEffect { get { return _gameStartEffect.Get(); } set { _gameStartEffect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> gameWonEffect { get { return _gameWonEffect.Get(); } set { _gameWonEffect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> sortEffect { get { return _sortEffect.Get(); } set { _sortEffect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> ballExplosion { get { return _ballExplosion.Get(); } set { _ballExplosion.Set( value ); } }

	public ExplosionParams explosionParams { get { return _explosionParams; } set { _explosionParams.Assign( value ); } }

	[Description( "there is no flow effect if distance for paint flow is less than this value" )]
	public float flowIntervalsStartDistance { get { return _flowIntervalsStartDistance.Get(); } set { _flowIntervalsStartDistance.Set( value ); } }

	[Description( "Base scale for flow effects" )]
	public float flowScale { get { return _flowScale.Get(); } set { _flowScale.Set( value ); } }

	public PaintFragmentFillParams fillParams { get { return _fillParams; } set { _fillParams.Assign( value ); } }

	[Description( "flow effects groups by distance intervals that they should fly by" )]
	public libdb.IChangeableList<DBEaselFlowEffectGroup> flowGroups { get { return _flowGroups; } set { _flowGroups.Assign( value ); } }

	public DBPtr<BasicEffectStandalone> flowTouchEffect { get { return _flowTouchEffect.Get(); } set { _flowTouchEffect.Set( value ); } }

	public DBPtr<BasicEffectStandalone> pathfinderHead { get { return _pathfinderHead.Get(); } set { _pathfinderHead.Set( value ); } }

	public DBPtr<BasicEffectStandalone> pathfinderTail { get { return _pathfinderTail.Get(); } set { _pathfinderTail.Set( value ); } }

	public float pathfinderVelocity { get { return _pathfinderVelocity.Get(); } set { _pathfinderVelocity.Set( value ); } }

	public float pathfinderInterval { get { return _pathfinderInterval.Get(); } set { _pathfinderInterval.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_paintblastExplosion = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_freezeEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_coinPickUp = new UndoRedoDBPtr<BasicEffectAttached>( owner );
		_gameStartEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_gameWonEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_sortEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_ballExplosion = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_explosionParams = new ExplosionParams( owner );
		_flowIntervalsStartDistance = new UndoRedo<float>( owner, 0.0f );
		_flowScale = new UndoRedo<float>( owner, 10.0f );
		_fillParams = new PaintFragmentFillParams( owner );
		_flowGroups = new UndoRedoAssignableList<DBEaselFlowEffectGroup>( owner );
		_flowTouchEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_pathfinderHead = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_pathfinderTail = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_pathfinderVelocity = new UndoRedo<float>( owner, 1000000.0f );
		_pathfinderInterval = new UndoRedo<float>( owner, 10.0f );
		_paintblastExplosion.Changed += FireChangedEvent;
		_freezeEffect.Changed += FireChangedEvent;
		_coinPickUp.Changed += FireChangedEvent;
		_gameStartEffect.Changed += FireChangedEvent;
		_gameWonEffect.Changed += FireChangedEvent;
		_sortEffect.Changed += FireChangedEvent;
		_ballExplosion.Changed += FireChangedEvent;
		_explosionParams.Changed += FireChangedEvent;
		_flowIntervalsStartDistance.Changed += FireChangedEvent;
		_flowScale.Changed += FireChangedEvent;
		_fillParams.Changed += FireChangedEvent;
		_flowGroups.Changed += FireChangedEvent;
		_flowTouchEffect.Changed += FireChangedEvent;
		_pathfinderHead.Changed += FireChangedEvent;
		_pathfinderTail.Changed += FireChangedEvent;
		_pathfinderVelocity.Changed += FireChangedEvent;
		_pathfinderInterval.Changed += FireChangedEvent;
	}

	public DBEaselEffectView()
	{
		Initialize( GetOwner() );
	}

	public DBEaselEffectView( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBEaselEffectView( DBResource owner, DBEaselEffectView source )
		: this(owner, source, true){}

	protected DBEaselEffectView( DBResource owner, DBEaselEffectView source, bool fireEvent )
	{
		_paintblastExplosion = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.paintblastExplosion );
		_freezeEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.freezeEffect );
		_coinPickUp = new UndoRedoDBPtr<BasicEffectAttached>( owner, source.coinPickUp );
		_gameStartEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.gameStartEffect );
		_gameWonEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.gameWonEffect );
		_sortEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.sortEffect );
		_ballExplosion = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.ballExplosion );
		_explosionParams = new ExplosionParams( owner, source.explosionParams );
		_flowIntervalsStartDistance = new UndoRedo<float>( owner, source.flowIntervalsStartDistance );
		_flowScale = new UndoRedo<float>( owner, source.flowScale );
		_fillParams = new PaintFragmentFillParams( owner, source.fillParams );
		_flowGroups = new UndoRedoAssignableList<DBEaselFlowEffectGroup>( owner );
		_flowGroups.Assign( source.flowGroups );
		_flowTouchEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.flowTouchEffect );
		_pathfinderHead = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.pathfinderHead );
		_pathfinderTail = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.pathfinderTail );
		_pathfinderVelocity = new UndoRedo<float>( owner, source.pathfinderVelocity );
		_pathfinderInterval = new UndoRedo<float>( owner, source.pathfinderInterval );
		_paintblastExplosion.Changed += FireChangedEvent;
		_freezeEffect.Changed += FireChangedEvent;
		_coinPickUp.Changed += FireChangedEvent;
		_gameStartEffect.Changed += FireChangedEvent;
		_gameWonEffect.Changed += FireChangedEvent;
		_sortEffect.Changed += FireChangedEvent;
		_ballExplosion.Changed += FireChangedEvent;
		_explosionParams.Changed += FireChangedEvent;
		_flowIntervalsStartDistance.Changed += FireChangedEvent;
		_flowScale.Changed += FireChangedEvent;
		_fillParams.Changed += FireChangedEvent;
		_flowGroups.Changed += FireChangedEvent;
		_flowTouchEffect.Changed += FireChangedEvent;
		_pathfinderHead.Changed += FireChangedEvent;
		_pathfinderTail.Changed += FireChangedEvent;
		_pathfinderVelocity.Changed += FireChangedEvent;
		_pathfinderInterval.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBEaselEffectView source = _source as DBEaselEffectView;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselEffectView" );
		paintblastExplosion = source.paintblastExplosion;
		freezeEffect = source.freezeEffect;
		coinPickUp = source.coinPickUp;
		gameStartEffect = source.gameStartEffect;
		gameWonEffect = source.gameWonEffect;
		sortEffect = source.sortEffect;
		ballExplosion = source.ballExplosion;
		explosionParams = source.explosionParams;
		flowIntervalsStartDistance = source.flowIntervalsStartDistance;
		flowScale = source.flowScale;
		fillParams = source.fillParams;
		flowGroups = source.flowGroups;
		flowTouchEffect = source.flowTouchEffect;
		pathfinderHead = source.pathfinderHead;
		pathfinderTail = source.pathfinderTail;
		pathfinderVelocity = source.pathfinderVelocity;
		pathfinderInterval = source.pathfinderInterval;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBEaselEffectView newParent = _newParent as DBEaselEffectView;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_paintblastExplosion.SetParent( newParent == null ? null : newParent._paintblastExplosion );
		_freezeEffect.SetParent( newParent == null ? null : newParent._freezeEffect );
		_coinPickUp.SetParent( newParent == null ? null : newParent._coinPickUp );
		_gameStartEffect.SetParent( newParent == null ? null : newParent._gameStartEffect );
		_gameWonEffect.SetParent( newParent == null ? null : newParent._gameWonEffect );
		_sortEffect.SetParent( newParent == null ? null : newParent._sortEffect );
		_ballExplosion.SetParent( newParent == null ? null : newParent._ballExplosion );
		_explosionParams.SetParent( newParent == null ? null : newParent._explosionParams );
		_flowIntervalsStartDistance.SetParent( newParent == null ? null : newParent._flowIntervalsStartDistance );
		_flowScale.SetParent( newParent == null ? null : newParent._flowScale );
		_fillParams.SetParent( newParent == null ? null : newParent._fillParams );
		_flowGroups.SetParent( newParent == null ? null : newParent._flowGroups );
		_flowTouchEffect.SetParent( newParent == null ? null : newParent._flowTouchEffect );
		_pathfinderHead.SetParent( newParent == null ? null : newParent._pathfinderHead );
		_pathfinderTail.SetParent( newParent == null ? null : newParent._pathfinderTail );
		_pathfinderVelocity.SetParent( newParent == null ? null : newParent._pathfinderVelocity );
		_pathfinderInterval.SetParent( newParent == null ? null : newParent._pathfinderInterval );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_paintblastExplosion.Reset();
		_freezeEffect.Reset();
		_coinPickUp.Reset();
		_gameStartEffect.Reset();
		_gameWonEffect.Reset();
		_sortEffect.Reset();
		_ballExplosion.Reset();
		_explosionParams.Reset();
		_flowIntervalsStartDistance.Reset();
		_flowScale.Reset();
		_fillParams.Reset();
		_flowGroups.Reset();
		_flowTouchEffect.Reset();
		_pathfinderHead.Reset();
		_pathfinderTail.Reset();
		_pathfinderVelocity.Reset();
		_pathfinderInterval.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_paintblastExplosion.IsDerivedFromParent()
			&& _freezeEffect.IsDerivedFromParent()
			&& _coinPickUp.IsDerivedFromParent()
			&& _gameStartEffect.IsDerivedFromParent()
			&& _gameWonEffect.IsDerivedFromParent()
			&& _sortEffect.IsDerivedFromParent()
			&& _ballExplosion.IsDerivedFromParent()
			&& _explosionParams.IsDerivedFromParent()
			&& _flowIntervalsStartDistance.IsDerivedFromParent()
			&& _flowScale.IsDerivedFromParent()
			&& _fillParams.IsDerivedFromParent()
			&& _flowGroups.IsDerivedFromParent()
			&& _flowTouchEffect.IsDerivedFromParent()
			&& _pathfinderHead.IsDerivedFromParent()
			&& _pathfinderTail.IsDerivedFromParent()
			&& _pathfinderVelocity.IsDerivedFromParent()
			&& _pathfinderInterval.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "paintblastExplosion" )
			_paintblastExplosion.Reset();
		else if ( fieldName == "freezeEffect" )
			_freezeEffect.Reset();
		else if ( fieldName == "coinPickUp" )
			_coinPickUp.Reset();
		else if ( fieldName == "gameStartEffect" )
			_gameStartEffect.Reset();
		else if ( fieldName == "gameWonEffect" )
			_gameWonEffect.Reset();
		else if ( fieldName == "sortEffect" )
			_sortEffect.Reset();
		else if ( fieldName == "ballExplosion" )
			_ballExplosion.Reset();
		else if ( fieldName == "explosionParams" )
			_explosionParams.Reset();
		else if ( fieldName == "flowIntervalsStartDistance" )
			_flowIntervalsStartDistance.Reset();
		else if ( fieldName == "flowScale" )
			_flowScale.Reset();
		else if ( fieldName == "fillParams" )
			_fillParams.Reset();
		else if ( fieldName == "flowGroups" )
			_flowGroups.Reset();
		else if ( fieldName == "flowTouchEffect" )
			_flowTouchEffect.Reset();
		else if ( fieldName == "pathfinderHead" )
			_pathfinderHead.Reset();
		else if ( fieldName == "pathfinderTail" )
			_pathfinderTail.Reset();
		else if ( fieldName == "pathfinderVelocity" )
			_pathfinderVelocity.Reset();
		else if ( fieldName == "pathfinderInterval" )
			_pathfinderInterval.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "paintblastExplosion" )
			return _paintblastExplosion.IsDerivedFromParent();
		if ( fieldName == "freezeEffect" )
			return _freezeEffect.IsDerivedFromParent();
		if ( fieldName == "coinPickUp" )
			return _coinPickUp.IsDerivedFromParent();
		if ( fieldName == "gameStartEffect" )
			return _gameStartEffect.IsDerivedFromParent();
		if ( fieldName == "gameWonEffect" )
			return _gameWonEffect.IsDerivedFromParent();
		if ( fieldName == "sortEffect" )
			return _sortEffect.IsDerivedFromParent();
		if ( fieldName == "ballExplosion" )
			return _ballExplosion.IsDerivedFromParent();
		if ( fieldName == "explosionParams" )
			return _explosionParams.IsDerivedFromParent();
		if ( fieldName == "flowIntervalsStartDistance" )
			return _flowIntervalsStartDistance.IsDerivedFromParent();
		if ( fieldName == "flowScale" )
			return _flowScale.IsDerivedFromParent();
		if ( fieldName == "fillParams" )
			return _fillParams.IsDerivedFromParent();
		if ( fieldName == "flowGroups" )
			return _flowGroups.IsDerivedFromParent();
		if ( fieldName == "flowTouchEffect" )
			return _flowTouchEffect.IsDerivedFromParent();
		if ( fieldName == "pathfinderHead" )
			return _pathfinderHead.IsDerivedFromParent();
		if ( fieldName == "pathfinderTail" )
			return _pathfinderTail.IsDerivedFromParent();
		if ( fieldName == "pathfinderVelocity" )
			return _pathfinderVelocity.IsDerivedFromParent();
		if ( fieldName == "pathfinderInterval" )
			return _pathfinderInterval.IsDerivedFromParent();
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

public class TunnelParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TunnelParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBSceneObject> _tunnel;
	private UndoRedo<int> _startPointOffset;
	private UndoRedo<int> _endPointOffset;

	public DBPtr<DBSceneObject> tunnel { get { return _tunnel.Get(); } set { _tunnel.Set( value ); } }

	public int startPointOffset { get { return _startPointOffset.Get(); } set { _startPointOffset.Set( value ); } }

	public int endPointOffset { get { return _endPointOffset.Get(); } set { _endPointOffset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_tunnel = new UndoRedoDBPtr<DBSceneObject>( owner );
		_startPointOffset = new UndoRedo<int>( owner, 250 );
		_endPointOffset = new UndoRedo<int>( owner, 100 );
		_tunnel.Changed += FireChangedEvent;
		_startPointOffset.Changed += FireChangedEvent;
		_endPointOffset.Changed += FireChangedEvent;
	}

	public TunnelParams()
	{
		Initialize( GetOwner() );
	}

	public TunnelParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TunnelParams( DBResource owner, TunnelParams source )
		: this(owner, source, true){}

	protected TunnelParams( DBResource owner, TunnelParams source, bool fireEvent )
	{
		_tunnel = new UndoRedoDBPtr<DBSceneObject>( owner, source.tunnel );
		_startPointOffset = new UndoRedo<int>( owner, source.startPointOffset );
		_endPointOffset = new UndoRedo<int>( owner, source.endPointOffset );
		_tunnel.Changed += FireChangedEvent;
		_startPointOffset.Changed += FireChangedEvent;
		_endPointOffset.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TunnelParams source = _source as TunnelParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TunnelParams" );
		tunnel = source.tunnel;
		startPointOffset = source.startPointOffset;
		endPointOffset = source.endPointOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TunnelParams newParent = _newParent as TunnelParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_tunnel.SetParent( newParent == null ? null : newParent._tunnel );
		_startPointOffset.SetParent( newParent == null ? null : newParent._startPointOffset );
		_endPointOffset.SetParent( newParent == null ? null : newParent._endPointOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_tunnel.Reset();
		_startPointOffset.Reset();
		_endPointOffset.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_tunnel.IsDerivedFromParent()
			&& _startPointOffset.IsDerivedFromParent()
			&& _endPointOffset.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "tunnel" )
			_tunnel.Reset();
		else if ( fieldName == "startPointOffset" )
			_startPointOffset.Reset();
		else if ( fieldName == "endPointOffset" )
			_endPointOffset.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "tunnel" )
			return _tunnel.IsDerivedFromParent();
		if ( fieldName == "startPointOffset" )
			return _startPointOffset.IsDerivedFromParent();
		if ( fieldName == "endPointOffset" )
			return _endPointOffset.IsDerivedFromParent();
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

public class DBEaselChains : DBResource
{
	private UndoRedoDBPtr<DBEaselChains> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselChains> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _numBallsInChain;
	private UndoRedo<int> _minSameColorChain;
	private UndoRedo<int> _maxSameColorChain;
	private UndoRedo<int> _speedMultiplier;
	private UndoRedo<int> _firstChainDelay;
	private UndoRedo<int> _nextChainDelay;
	private UndoRedo<int> _colorsDistortionPercentage;

	[MinMaxSize(3, 100)]
	public int numBallsInChain { get { return _numBallsInChain.Get(); } set { _numBallsInChain.Set( value ); } }

	[MinMaxSize(0, 100)]
	public int minSameColorChain { get { return _minSameColorChain.Get(); } set { _minSameColorChain.Set( value ); } }

	[MinMaxSize(1, 100)]
	public int maxSameColorChain { get { return _maxSameColorChain.Get(); } set { _maxSameColorChain.Set( value ); } }

	[MinMaxSize(0, 200)]
	public int speedMultiplier { get { return _speedMultiplier.Get(); } set { _speedMultiplier.Set( value ); } }

	public int firstChainDelay { get { return _firstChainDelay.Get(); } set { _firstChainDelay.Set( value ); } }

	public int nextChainDelay { get { return _nextChainDelay.Get(); } set { _nextChainDelay.Set( value ); } }

	[Description( "0 - maximum random, 100 - minimum" )]
	[MinMaxSize(0, 100)]
	public int colorsDistortionPercentage { get { return _colorsDistortionPercentage.Get(); } set { _colorsDistortionPercentage.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselChains>(owner);
		_numBallsInChain = new UndoRedo<int>( owner, 20 );
		_minSameColorChain = new UndoRedo<int>( owner, 3 );
		_maxSameColorChain = new UndoRedo<int>( owner, 8 );
		_speedMultiplier = new UndoRedo<int>( owner, 100 );
		_firstChainDelay = new UndoRedo<int>( owner, 0 );
		_nextChainDelay = new UndoRedo<int>( owner, 10000 );
		_colorsDistortionPercentage = new UndoRedo<int>( owner, 100 );
		___parent.Changed += FireChangedEvent;
		_numBallsInChain.Changed += FireChangedEvent;
		_minSameColorChain.Changed += FireChangedEvent;
		_maxSameColorChain.Changed += FireChangedEvent;
		_speedMultiplier.Changed += FireChangedEvent;
		_firstChainDelay.Changed += FireChangedEvent;
		_nextChainDelay.Changed += FireChangedEvent;
		_colorsDistortionPercentage.Changed += FireChangedEvent;
	}

	public DBEaselChains()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselChains source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselChains" );
		numBallsInChain = source.numBallsInChain;
		minSameColorChain = source.minSameColorChain;
		maxSameColorChain = source.maxSameColorChain;
		speedMultiplier = source.speedMultiplier;
		firstChainDelay = source.firstChainDelay;
		nextChainDelay = source.nextChainDelay;
		colorsDistortionPercentage = source.colorsDistortionPercentage;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselChains source = _source as DBEaselChains;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselChains" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselChains newParent = rawParent == null ? null : rawParent.Get<DBEaselChains>();
		if ( newParent == null && _newParent is DBEaselChains )
			newParent = _newParent as DBEaselChains;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_numBallsInChain.SetParent( newParent == null ? null : newParent._numBallsInChain );
		_minSameColorChain.SetParent( newParent == null ? null : newParent._minSameColorChain );
		_maxSameColorChain.SetParent( newParent == null ? null : newParent._maxSameColorChain );
		_speedMultiplier.SetParent( newParent == null ? null : newParent._speedMultiplier );
		_firstChainDelay.SetParent( newParent == null ? null : newParent._firstChainDelay );
		_nextChainDelay.SetParent( newParent == null ? null : newParent._nextChainDelay );
		_colorsDistortionPercentage.SetParent( newParent == null ? null : newParent._colorsDistortionPercentage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_numBallsInChain.Reset();
		_minSameColorChain.Reset();
		_maxSameColorChain.Reset();
		_speedMultiplier.Reset();
		_firstChainDelay.Reset();
		_nextChainDelay.Reset();
		_colorsDistortionPercentage.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_numBallsInChain.IsDerivedFromParent()
			&& _minSameColorChain.IsDerivedFromParent()
			&& _maxSameColorChain.IsDerivedFromParent()
			&& _speedMultiplier.IsDerivedFromParent()
			&& _firstChainDelay.IsDerivedFromParent()
			&& _nextChainDelay.IsDerivedFromParent()
			&& _colorsDistortionPercentage.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "numBallsInChain" )
			_numBallsInChain.Reset();
		else if ( fieldName == "minSameColorChain" )
			_minSameColorChain.Reset();
		else if ( fieldName == "maxSameColorChain" )
			_maxSameColorChain.Reset();
		else if ( fieldName == "speedMultiplier" )
			_speedMultiplier.Reset();
		else if ( fieldName == "firstChainDelay" )
			_firstChainDelay.Reset();
		else if ( fieldName == "nextChainDelay" )
			_nextChainDelay.Reset();
		else if ( fieldName == "colorsDistortionPercentage" )
			_colorsDistortionPercentage.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "numBallsInChain" )
			return _numBallsInChain.IsDerivedFromParent();
		if ( fieldName == "minSameColorChain" )
			return _minSameColorChain.IsDerivedFromParent();
		if ( fieldName == "maxSameColorChain" )
			return _maxSameColorChain.IsDerivedFromParent();
		if ( fieldName == "speedMultiplier" )
			return _speedMultiplier.IsDerivedFromParent();
		if ( fieldName == "firstChainDelay" )
			return _firstChainDelay.IsDerivedFromParent();
		if ( fieldName == "nextChainDelay" )
			return _nextChainDelay.IsDerivedFromParent();
		if ( fieldName == "colorsDistortionPercentage" )
			return _colorsDistortionPercentage.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class DBEaselCommon : DBResource
{
	private UndoRedoDBPtr<DBEaselCommon> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselCommon> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<HDRColor> _colors;
	private UndoRedoDBPtr<AnimGraphCreator> _priestessAnimGraph;
	private ViewCamera _camera;
	private DBEaselCursorView _aimCursors;
	private DBEaselPlatfrom _platform;
	private Placement _luxorPlacement;
	private DBEaselBallsView _balls;
	private DBEaselEffectView _effects;
	private TunnelParams _tunnels;
	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _fallingObjects;
	private DBLuxorPlatformGeneratorParams _platformGeneratorParams;
	private UndoRedoDBPtr<DBSceneObject> _startPipe;
	private UndoRedoDBPtr<DBSceneObject> _endWell;
	private Magnet _magnetEffects;
	private UndoRedoDBPtr<BasicEffectAttached> _alchemistPot;
	private UndoRedoDBPtr<BasicEffectStandalone> _glueEffect;
	private UndoRedo<int> _chainTravelTime;
	private Coin _coin;
	private BallVelocities _ballVelocities;
	private UndoRedo<float> _waitForResultScreen;
	private AnimatedPlacement _priestessDefaultPlacement;
	private UndoRedo<float> _ballFireInterval;
	private UndoRedo<int> _explosionCountdown;

	[EnumArray(typeof(EColor))]
	public libdb.IChangeableList<HDRColor> colors { get { return _colors; } set { _colors.Assign( value ); } }

	public DBPtr<AnimGraphCreator> priestessAnimGraph { get { return _priestessAnimGraph.Get(); } set { _priestessAnimGraph.Set( value ); } }

	public ViewCamera camera { get { return _camera; } set { _camera.Assign( value ); } }

	public DBEaselCursorView aimCursors { get { return _aimCursors; } set { _aimCursors.Assign( value ); } }

	public DBEaselPlatfrom platform { get { return _platform; } set { _platform.Assign( value ); } }

	public Placement luxorPlacement { get { return _luxorPlacement; } set { _luxorPlacement.Assign( value ); } }

	public DBEaselBallsView balls { get { return _balls; } set { _balls.Assign( value ); } }

	public DBEaselEffectView effects { get { return _effects; } set { _effects.Assign( value ); } }

	public TunnelParams tunnels { get { return _tunnels; } set { _tunnels.Assign( value ); } }

	[EnumArray(typeof(EFallingObject))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> fallingObjects { get { return _fallingObjects; } set { _fallingObjects.Assign( value ); } }

	public DBLuxorPlatformGeneratorParams platformGeneratorParams { get { return _platformGeneratorParams; } set { _platformGeneratorParams.Assign( value ); } }

	public DBPtr<DBSceneObject> startPipe { get { return _startPipe.Get(); } set { _startPipe.Set( value ); } }

	public DBPtr<DBSceneObject> endWell { get { return _endWell.Get(); } set { _endWell.Set( value ); } }

	public Magnet magnetEffects { get { return _magnetEffects; } set { _magnetEffects.Assign( value ); } }

	public DBPtr<BasicEffectAttached> alchemistPot { get { return _alchemistPot.Get(); } set { _alchemistPot.Set( value ); } }

	public DBPtr<BasicEffectStandalone> glueEffect { get { return _glueEffect.Get(); } set { _glueEffect.Set( value ); } }

	public int chainTravelTime { get { return _chainTravelTime.Get(); } set { _chainTravelTime.Set( value ); } }

	public Coin coin { get { return _coin; } set { _coin.Assign( value ); } }

	public BallVelocities ballVelocities { get { return _ballVelocities; } set { _ballVelocities.Assign( value ); } }

	public float waitForResultScreen { get { return _waitForResultScreen.Get(); } set { _waitForResultScreen.Set( value ); } }

	public AnimatedPlacement priestessDefaultPlacement { get { return _priestessDefaultPlacement; } set { _priestessDefaultPlacement.Assign( value ); } }

	public float ballFireInterval { get { return _ballFireInterval.Get(); } set { _ballFireInterval.Set( value ); } }

	[Description( "Number of ticks ( 100 msec ) before ball explodes after insertion" )]
	public int explosionCountdown { get { return _explosionCountdown.Get(); } set { _explosionCountdown.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselCommon>(owner);
		_colors = new UndoRedoAssignableList<HDRColor>( owner, typeof( EColor ) );
		_priestessAnimGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		_camera = new ViewCamera( owner );
		_aimCursors = new DBEaselCursorView( owner );
		_platform = new DBEaselPlatfrom( owner );
		_luxorPlacement = new Placement( owner );
		_balls = new DBEaselBallsView( owner );
		_effects = new DBEaselEffectView( owner );
		_tunnels = new TunnelParams( owner );
		_fallingObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( EFallingObject ) );
		_platformGeneratorParams = new DBLuxorPlatformGeneratorParams( owner );
		_startPipe = new UndoRedoDBPtr<DBSceneObject>( owner );
		_endWell = new UndoRedoDBPtr<DBSceneObject>( owner );
		_magnetEffects = new Magnet( owner );
		_alchemistPot = new UndoRedoDBPtr<BasicEffectAttached>( owner );
		_glueEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_chainTravelTime = new UndoRedo<int>( owner, 60000 );
		_coin = new Coin( owner );
		_ballVelocities = new BallVelocities( owner );
		_waitForResultScreen = new UndoRedo<float>( owner, 4.0f );
		_priestessDefaultPlacement = new AnimatedPlacement( owner );
		_ballFireInterval = new UndoRedo<float>( owner, 0.2f );
		_explosionCountdown = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_colors.Changed += FireChangedEvent;
		_priestessAnimGraph.Changed += FireChangedEvent;
		_camera.Changed += FireChangedEvent;
		_aimCursors.Changed += FireChangedEvent;
		_platform.Changed += FireChangedEvent;
		_luxorPlacement.Changed += FireChangedEvent;
		_balls.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_tunnels.Changed += FireChangedEvent;
		_fallingObjects.Changed += FireChangedEvent;
		_platformGeneratorParams.Changed += FireChangedEvent;
		_startPipe.Changed += FireChangedEvent;
		_endWell.Changed += FireChangedEvent;
		_magnetEffects.Changed += FireChangedEvent;
		_alchemistPot.Changed += FireChangedEvent;
		_glueEffect.Changed += FireChangedEvent;
		_chainTravelTime.Changed += FireChangedEvent;
		_coin.Changed += FireChangedEvent;
		_ballVelocities.Changed += FireChangedEvent;
		_waitForResultScreen.Changed += FireChangedEvent;
		_priestessDefaultPlacement.Changed += FireChangedEvent;
		_ballFireInterval.Changed += FireChangedEvent;
		_explosionCountdown.Changed += FireChangedEvent;
	}

	public DBEaselCommon()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselCommon source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselCommon" );
		colors = source.colors;
		priestessAnimGraph = source.priestessAnimGraph;
		camera = source.camera;
		aimCursors = source.aimCursors;
		platform = source.platform;
		luxorPlacement = source.luxorPlacement;
		balls = source.balls;
		effects = source.effects;
		tunnels = source.tunnels;
		fallingObjects = source.fallingObjects;
		platformGeneratorParams = source.platformGeneratorParams;
		startPipe = source.startPipe;
		endWell = source.endWell;
		magnetEffects = source.magnetEffects;
		alchemistPot = source.alchemistPot;
		glueEffect = source.glueEffect;
		chainTravelTime = source.chainTravelTime;
		coin = source.coin;
		ballVelocities = source.ballVelocities;
		waitForResultScreen = source.waitForResultScreen;
		priestessDefaultPlacement = source.priestessDefaultPlacement;
		ballFireInterval = source.ballFireInterval;
		explosionCountdown = source.explosionCountdown;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselCommon source = _source as DBEaselCommon;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselCommon" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselCommon newParent = rawParent == null ? null : rawParent.Get<DBEaselCommon>();
		if ( newParent == null && _newParent is DBEaselCommon )
			newParent = _newParent as DBEaselCommon;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_colors.SetParent( newParent == null ? null : newParent._colors );
		_priestessAnimGraph.SetParent( newParent == null ? null : newParent._priestessAnimGraph );
		_camera.SetParent( newParent == null ? null : newParent._camera );
		_aimCursors.SetParent( newParent == null ? null : newParent._aimCursors );
		_platform.SetParent( newParent == null ? null : newParent._platform );
		_luxorPlacement.SetParent( newParent == null ? null : newParent._luxorPlacement );
		_balls.SetParent( newParent == null ? null : newParent._balls );
		_effects.SetParent( newParent == null ? null : newParent._effects );
		_tunnels.SetParent( newParent == null ? null : newParent._tunnels );
		_fallingObjects.SetParent( newParent == null ? null : newParent._fallingObjects );
		_platformGeneratorParams.SetParent( newParent == null ? null : newParent._platformGeneratorParams );
		_startPipe.SetParent( newParent == null ? null : newParent._startPipe );
		_endWell.SetParent( newParent == null ? null : newParent._endWell );
		_magnetEffects.SetParent( newParent == null ? null : newParent._magnetEffects );
		_alchemistPot.SetParent( newParent == null ? null : newParent._alchemistPot );
		_glueEffect.SetParent( newParent == null ? null : newParent._glueEffect );
		_chainTravelTime.SetParent( newParent == null ? null : newParent._chainTravelTime );
		_coin.SetParent( newParent == null ? null : newParent._coin );
		_ballVelocities.SetParent( newParent == null ? null : newParent._ballVelocities );
		_waitForResultScreen.SetParent( newParent == null ? null : newParent._waitForResultScreen );
		_priestessDefaultPlacement.SetParent( newParent == null ? null : newParent._priestessDefaultPlacement );
		_ballFireInterval.SetParent( newParent == null ? null : newParent._ballFireInterval );
		_explosionCountdown.SetParent( newParent == null ? null : newParent._explosionCountdown );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_colors.Reset();
		_priestessAnimGraph.Reset();
		_camera.Reset();
		_aimCursors.Reset();
		_platform.Reset();
		_luxorPlacement.Reset();
		_balls.Reset();
		_effects.Reset();
		_tunnels.Reset();
		_fallingObjects.Reset();
		_platformGeneratorParams.Reset();
		_startPipe.Reset();
		_endWell.Reset();
		_magnetEffects.Reset();
		_alchemistPot.Reset();
		_glueEffect.Reset();
		_chainTravelTime.Reset();
		_coin.Reset();
		_ballVelocities.Reset();
		_waitForResultScreen.Reset();
		_priestessDefaultPlacement.Reset();
		_ballFireInterval.Reset();
		_explosionCountdown.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_colors.IsDerivedFromParent()
			&& _priestessAnimGraph.IsDerivedFromParent()
			&& _camera.IsDerivedFromParent()
			&& _aimCursors.IsDerivedFromParent()
			&& _platform.IsDerivedFromParent()
			&& _luxorPlacement.IsDerivedFromParent()
			&& _balls.IsDerivedFromParent()
			&& _effects.IsDerivedFromParent()
			&& _tunnels.IsDerivedFromParent()
			&& _fallingObjects.IsDerivedFromParent()
			&& _platformGeneratorParams.IsDerivedFromParent()
			&& _startPipe.IsDerivedFromParent()
			&& _endWell.IsDerivedFromParent()
			&& _magnetEffects.IsDerivedFromParent()
			&& _alchemistPot.IsDerivedFromParent()
			&& _glueEffect.IsDerivedFromParent()
			&& _chainTravelTime.IsDerivedFromParent()
			&& _coin.IsDerivedFromParent()
			&& _ballVelocities.IsDerivedFromParent()
			&& _waitForResultScreen.IsDerivedFromParent()
			&& _priestessDefaultPlacement.IsDerivedFromParent()
			&& _ballFireInterval.IsDerivedFromParent()
			&& _explosionCountdown.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "colors" )
			_colors.Reset();
		else if ( fieldName == "priestessAnimGraph" )
			_priestessAnimGraph.Reset();
		else if ( fieldName == "camera" )
			_camera.Reset();
		else if ( fieldName == "aimCursors" )
			_aimCursors.Reset();
		else if ( fieldName == "platform" )
			_platform.Reset();
		else if ( fieldName == "luxorPlacement" )
			_luxorPlacement.Reset();
		else if ( fieldName == "balls" )
			_balls.Reset();
		else if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "tunnels" )
			_tunnels.Reset();
		else if ( fieldName == "fallingObjects" )
			_fallingObjects.Reset();
		else if ( fieldName == "platformGeneratorParams" )
			_platformGeneratorParams.Reset();
		else if ( fieldName == "startPipe" )
			_startPipe.Reset();
		else if ( fieldName == "endWell" )
			_endWell.Reset();
		else if ( fieldName == "magnetEffects" )
			_magnetEffects.Reset();
		else if ( fieldName == "alchemistPot" )
			_alchemistPot.Reset();
		else if ( fieldName == "glueEffect" )
			_glueEffect.Reset();
		else if ( fieldName == "chainTravelTime" )
			_chainTravelTime.Reset();
		else if ( fieldName == "coin" )
			_coin.Reset();
		else if ( fieldName == "ballVelocities" )
			_ballVelocities.Reset();
		else if ( fieldName == "waitForResultScreen" )
			_waitForResultScreen.Reset();
		else if ( fieldName == "priestessDefaultPlacement" )
			_priestessDefaultPlacement.Reset();
		else if ( fieldName == "ballFireInterval" )
			_ballFireInterval.Reset();
		else if ( fieldName == "explosionCountdown" )
			_explosionCountdown.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "colors" )
			return _colors.IsDerivedFromParent();
		if ( fieldName == "priestessAnimGraph" )
			return _priestessAnimGraph.IsDerivedFromParent();
		if ( fieldName == "camera" )
			return _camera.IsDerivedFromParent();
		if ( fieldName == "aimCursors" )
			return _aimCursors.IsDerivedFromParent();
		if ( fieldName == "platform" )
			return _platform.IsDerivedFromParent();
		if ( fieldName == "luxorPlacement" )
			return _luxorPlacement.IsDerivedFromParent();
		if ( fieldName == "balls" )
			return _balls.IsDerivedFromParent();
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "tunnels" )
			return _tunnels.IsDerivedFromParent();
		if ( fieldName == "fallingObjects" )
			return _fallingObjects.IsDerivedFromParent();
		if ( fieldName == "platformGeneratorParams" )
			return _platformGeneratorParams.IsDerivedFromParent();
		if ( fieldName == "startPipe" )
			return _startPipe.IsDerivedFromParent();
		if ( fieldName == "endWell" )
			return _endWell.IsDerivedFromParent();
		if ( fieldName == "magnetEffects" )
			return _magnetEffects.IsDerivedFromParent();
		if ( fieldName == "alchemistPot" )
			return _alchemistPot.IsDerivedFromParent();
		if ( fieldName == "glueEffect" )
			return _glueEffect.IsDerivedFromParent();
		if ( fieldName == "chainTravelTime" )
			return _chainTravelTime.IsDerivedFromParent();
		if ( fieldName == "coin" )
			return _coin.IsDerivedFromParent();
		if ( fieldName == "ballVelocities" )
			return _ballVelocities.IsDerivedFromParent();
		if ( fieldName == "waitForResultScreen" )
			return _waitForResultScreen.IsDerivedFromParent();
		if ( fieldName == "priestessDefaultPlacement" )
			return _priestessDefaultPlacement.IsDerivedFromParent();
		if ( fieldName == "ballFireInterval" )
			return _ballFireInterval.IsDerivedFromParent();
		if ( fieldName == "explosionCountdown" )
			return _explosionCountdown.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
public class DBEaselData : DBResource
{
	private UndoRedoDBPtr<DBEaselData> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselData> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _title;
	private UndoRedo<int> _startPointOffset;
	private UndoRedo<int> _killChainAfterOffset;
	private UndoRedoDBPtr<DBEaselGame> _game;
	private UndoRedoDBPtr<DBEaselCommon> _commonParams;
	private UndoRedoDBPtr<DBEaselSoundsData> _soundData;
	private UndoRedoDBPtr<DBPriestessStats> _priestessStats;
	private DBBoostList _gameboosts;
	private DBEaselBidonEffectDesc _bidonEffectDesc;
	private DBEaselBoostsTutorialDesc _boostsTutorialDesc;
	private DBEaselArtifacts _artifacts;

	[Category( "Minigame Name" )]
	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	[Category( "Generated chain will be placed on the spline from this offset" )]
	public int startPointOffset { get { return _startPointOffset.Get(); } set { _startPointOffset.Set( value ); } }

	[Category( "Chain will be killed after end + offset" )]
	public int killChainAfterOffset { get { return _killChainAfterOffset.Get(); } set { _killChainAfterOffset.Set( value ); } }

	public DBPtr<DBEaselGame> game { get { return _game.Get(); } set { _game.Set( value ); } }

	[Category( "Painter params" )]
	public DBPtr<DBEaselCommon> commonParams { get { return _commonParams.Get(); } set { _commonParams.Set( value ); } }

	[Category( "Sound params" )]
	public DBPtr<DBEaselSoundsData> soundData { get { return _soundData.Get(); } set { _soundData.Set( value ); } }

	[Category( "Stats params" )]
	public DBPtr<DBPriestessStats> priestessStats { get { return _priestessStats.Get(); } set { _priestessStats.Set( value ); } }

	[Category( "Boosts parameters" )]
	public DBBoostList gameboosts { get { return _gameboosts; } set { _gameboosts.Assign( value ); } }

	[Description( "Describes how Bidons affect the Easel MiniGame" )]
	public DBEaselBidonEffectDesc bidonEffectDesc { get { return _bidonEffectDesc; } set { _bidonEffectDesc.Assign( value ); } }

	[Description( "Describes some boosts tutorial parameters" )]
	public DBEaselBoostsTutorialDesc boostsTutorialDesc { get { return _boostsTutorialDesc; } set { _boostsTutorialDesc.Assign( value ); } }

	public DBEaselArtifacts artifacts { get { return _artifacts; } set { _artifacts.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselData>(owner);
		_title = new TextRef( owner, new TextRef() );
		_startPointOffset = new UndoRedo<int>( owner, -400 );
		_killChainAfterOffset = new UndoRedo<int>( owner, 400 );
		_game = new UndoRedoDBPtr<DBEaselGame>( owner );
		_commonParams = new UndoRedoDBPtr<DBEaselCommon>( owner );
		_soundData = new UndoRedoDBPtr<DBEaselSoundsData>( owner );
		_priestessStats = new UndoRedoDBPtr<DBPriestessStats>( owner );
		_gameboosts = new DBBoostList( owner );
		_bidonEffectDesc = new DBEaselBidonEffectDesc( owner );
		_boostsTutorialDesc = new DBEaselBoostsTutorialDesc( owner );
		_artifacts = new DBEaselArtifacts( owner );
		___parent.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_startPointOffset.Changed += FireChangedEvent;
		_killChainAfterOffset.Changed += FireChangedEvent;
		_game.Changed += FireChangedEvent;
		_commonParams.Changed += FireChangedEvent;
		_soundData.Changed += FireChangedEvent;
		_priestessStats.Changed += FireChangedEvent;
		_gameboosts.Changed += FireChangedEvent;
		_bidonEffectDesc.Changed += FireChangedEvent;
		_boostsTutorialDesc.Changed += FireChangedEvent;
		_artifacts.Changed += FireChangedEvent;
	}

	public DBEaselData()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselData source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselData" );
		title = source.title;
		startPointOffset = source.startPointOffset;
		killChainAfterOffset = source.killChainAfterOffset;
		game = source.game;
		commonParams = source.commonParams;
		soundData = source.soundData;
		priestessStats = source.priestessStats;
		gameboosts = source.gameboosts;
		bidonEffectDesc = source.bidonEffectDesc;
		boostsTutorialDesc = source.boostsTutorialDesc;
		artifacts = source.artifacts;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselData source = _source as DBEaselData;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselData" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselData newParent = rawParent == null ? null : rawParent.Get<DBEaselData>();
		if ( newParent == null && _newParent is DBEaselData )
			newParent = _newParent as DBEaselData;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_title.SetParent( newParent == null ? null : newParent._title );
		_startPointOffset.SetParent( newParent == null ? null : newParent._startPointOffset );
		_killChainAfterOffset.SetParent( newParent == null ? null : newParent._killChainAfterOffset );
		_game.SetParent( newParent == null ? null : newParent._game );
		_commonParams.SetParent( newParent == null ? null : newParent._commonParams );
		_soundData.SetParent( newParent == null ? null : newParent._soundData );
		_priestessStats.SetParent( newParent == null ? null : newParent._priestessStats );
		_gameboosts.SetParent( newParent == null ? null : newParent._gameboosts );
		_bidonEffectDesc.SetParent( newParent == null ? null : newParent._bidonEffectDesc );
		_boostsTutorialDesc.SetParent( newParent == null ? null : newParent._boostsTutorialDesc );
		_artifacts.SetParent( newParent == null ? null : newParent._artifacts );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_title.Reset();
		_startPointOffset.Reset();
		_killChainAfterOffset.Reset();
		_game.Reset();
		_commonParams.Reset();
		_soundData.Reset();
		_priestessStats.Reset();
		_gameboosts.Reset();
		_bidonEffectDesc.Reset();
		_boostsTutorialDesc.Reset();
		_artifacts.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _startPointOffset.IsDerivedFromParent()
			&& _killChainAfterOffset.IsDerivedFromParent()
			&& _game.IsDerivedFromParent()
			&& _commonParams.IsDerivedFromParent()
			&& _soundData.IsDerivedFromParent()
			&& _priestessStats.IsDerivedFromParent()
			&& _gameboosts.IsDerivedFromParent()
			&& _bidonEffectDesc.IsDerivedFromParent()
			&& _boostsTutorialDesc.IsDerivedFromParent()
			&& _artifacts.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "startPointOffset" )
			_startPointOffset.Reset();
		else if ( fieldName == "killChainAfterOffset" )
			_killChainAfterOffset.Reset();
		else if ( fieldName == "game" )
			_game.Reset();
		else if ( fieldName == "commonParams" )
			_commonParams.Reset();
		else if ( fieldName == "soundData" )
			_soundData.Reset();
		else if ( fieldName == "priestessStats" )
			_priestessStats.Reset();
		else if ( fieldName == "gameboosts" )
			_gameboosts.Reset();
		else if ( fieldName == "bidonEffectDesc" )
			_bidonEffectDesc.Reset();
		else if ( fieldName == "boostsTutorialDesc" )
			_boostsTutorialDesc.Reset();
		else if ( fieldName == "artifacts" )
			_artifacts.Reset();
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
		if ( fieldName == "startPointOffset" )
			return _startPointOffset.IsDerivedFromParent();
		if ( fieldName == "killChainAfterOffset" )
			return _killChainAfterOffset.IsDerivedFromParent();
		if ( fieldName == "game" )
			return _game.IsDerivedFromParent();
		if ( fieldName == "commonParams" )
			return _commonParams.IsDerivedFromParent();
		if ( fieldName == "soundData" )
			return _soundData.IsDerivedFromParent();
		if ( fieldName == "priestessStats" )
			return _priestessStats.IsDerivedFromParent();
		if ( fieldName == "gameboosts" )
			return _gameboosts.IsDerivedFromParent();
		if ( fieldName == "bidonEffectDesc" )
			return _bidonEffectDesc.IsDerivedFromParent();
		if ( fieldName == "boostsTutorialDesc" )
			return _boostsTutorialDesc.IsDerivedFromParent();
		if ( fieldName == "artifacts" )
			return _artifacts.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class DBEaselGame : DBResource
{
	private UndoRedoDBPtr<DBEaselGame> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselGame> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBEaselLevel> _levels;
	private UndoRedoAssignableList<DBPtr<DBEaselSpline>> _trajectories;
	private UndoRedo<int> _firstLevelForceTrajectory;
	private UndoRedoDBPtr<DBEaselChains> _designerChainParams;
	private DBPaint _paint;
	private UndoRedoList<int> _availabilityTable;
	private UndoRedo<float> _failureExperienceFactor;

	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<DBEaselLevel> levels { get { return _levels; } set { _levels.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<DBEaselSpline>> trajectories { get { return _trajectories; } set { _trajectories.Assign( value ); } }

	[Description( "Forces trajectory for first level for first time. -1 turns off trajectory force" )]
	public int firstLevelForceTrajectory { get { return _firstLevelForceTrajectory.Get(); } set { _firstLevelForceTrajectory.Set( value ); } }

	public DBPtr<DBEaselChains> designerChainParams { get { return _designerChainParams.Get(); } set { _designerChainParams.Set( value ); } }

	public DBPaint paint { get { return _paint; } set { _paint.Assign( value ); } }

	[Description( "— какого уровн€ миниигры открываетс€ новый свиток" )]
	[EnumArray(typeof(EPaintType))]
	public libdb.IChangeableList<int> availabilityTable { get { return _availabilityTable; } set { _availabilityTable.Assign( value ); } }

	public float failureExperienceFactor { get { return _failureExperienceFactor.Get(); } set { _failureExperienceFactor.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselGame>(owner);
		_levels = new UndoRedoAssignableList<DBEaselLevel>( owner, typeof( EPriestessLevel ) );
		_trajectories = new UndoRedoAssignableList<DBPtr<DBEaselSpline>>( owner );
		_firstLevelForceTrajectory = new UndoRedo<int>( owner, 5 );
		_designerChainParams = new UndoRedoDBPtr<DBEaselChains>( owner );
		_paint = new DBPaint( owner );
		_availabilityTable = new UndoRedoList<int>( owner, typeof( EPaintType ) );
		_failureExperienceFactor = new UndoRedo<float>( owner, 0.3f );
		___parent.Changed += FireChangedEvent;
		_levels.Changed += FireChangedEvent;
		_trajectories.Changed += FireChangedEvent;
		_firstLevelForceTrajectory.Changed += FireChangedEvent;
		_designerChainParams.Changed += FireChangedEvent;
		_paint.Changed += FireChangedEvent;
		_availabilityTable.Changed += FireChangedEvent;
		_failureExperienceFactor.Changed += FireChangedEvent;
	}

	public DBEaselGame()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselGame source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselGame" );
		levels = source.levels;
		trajectories = source.trajectories;
		firstLevelForceTrajectory = source.firstLevelForceTrajectory;
		designerChainParams = source.designerChainParams;
		paint = source.paint;
		availabilityTable = source.availabilityTable;
		failureExperienceFactor = source.failureExperienceFactor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselGame source = _source as DBEaselGame;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselGame" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselGame newParent = rawParent == null ? null : rawParent.Get<DBEaselGame>();
		if ( newParent == null && _newParent is DBEaselGame )
			newParent = _newParent as DBEaselGame;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_levels.SetParent( newParent == null ? null : newParent._levels );
		_trajectories.SetParent( newParent == null ? null : newParent._trajectories );
		_firstLevelForceTrajectory.SetParent( newParent == null ? null : newParent._firstLevelForceTrajectory );
		_designerChainParams.SetParent( newParent == null ? null : newParent._designerChainParams );
		_paint.SetParent( newParent == null ? null : newParent._paint );
		_availabilityTable.SetParent( newParent == null ? null : newParent._availabilityTable );
		_failureExperienceFactor.SetParent( newParent == null ? null : newParent._failureExperienceFactor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_levels.Reset();
		_trajectories.Reset();
		_firstLevelForceTrajectory.Reset();
		_designerChainParams.Reset();
		_paint.Reset();
		_availabilityTable.Reset();
		_failureExperienceFactor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_levels.IsDerivedFromParent()
			&& _trajectories.IsDerivedFromParent()
			&& _firstLevelForceTrajectory.IsDerivedFromParent()
			&& _designerChainParams.IsDerivedFromParent()
			&& _paint.IsDerivedFromParent()
			&& _availabilityTable.IsDerivedFromParent()
			&& _failureExperienceFactor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "levels" )
			_levels.Reset();
		else if ( fieldName == "trajectories" )
			_trajectories.Reset();
		else if ( fieldName == "firstLevelForceTrajectory" )
			_firstLevelForceTrajectory.Reset();
		else if ( fieldName == "designerChainParams" )
			_designerChainParams.Reset();
		else if ( fieldName == "paint" )
			_paint.Reset();
		else if ( fieldName == "availabilityTable" )
			_availabilityTable.Reset();
		else if ( fieldName == "failureExperienceFactor" )
			_failureExperienceFactor.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "levels" )
			return _levels.IsDerivedFromParent();
		if ( fieldName == "trajectories" )
			return _trajectories.IsDerivedFromParent();
		if ( fieldName == "firstLevelForceTrajectory" )
			return _firstLevelForceTrajectory.IsDerivedFromParent();
		if ( fieldName == "designerChainParams" )
			return _designerChainParams.IsDerivedFromParent();
		if ( fieldName == "paint" )
			return _paint.IsDerivedFromParent();
		if ( fieldName == "availabilityTable" )
			return _availabilityTable.IsDerivedFromParent();
		if ( fieldName == "failureExperienceFactor" )
			return _failureExperienceFactor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class DBEaselPath : DBResource
{
	private UndoRedoDBPtr<DBEaselPath> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselPath> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private DBSpline _spline;
	private DBSplineData _splineData;

	[Category( "Spline" )]
	public DBSpline spline { get { return _spline; } set { _spline.Assign( value ); } }

	[Category( "Spline data" )]
	public DBSplineData splineData { get { return _splineData; } set { _splineData.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselPath>(owner);
		_spline = new DBSpline( owner );
		_splineData = new DBSplineData( owner );
		___parent.Changed += FireChangedEvent;
		_spline.Changed += FireChangedEvent;
		_splineData.Changed += FireChangedEvent;
	}

	public DBEaselPath()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselPath source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselPath" );
		spline = source.spline;
		splineData = source.splineData;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselPath source = _source as DBEaselPath;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselPath" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselPath newParent = rawParent == null ? null : rawParent.Get<DBEaselPath>();
		if ( newParent == null && _newParent is DBEaselPath )
			newParent = _newParent as DBEaselPath;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_spline.SetParent( newParent == null ? null : newParent._spline );
		_splineData.SetParent( newParent == null ? null : newParent._splineData );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_spline.Reset();
		_splineData.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_spline.IsDerivedFromParent()
			&& _splineData.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "spline" )
			_spline.Reset();
		else if ( fieldName == "splineData" )
			_splineData.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "spline" )
			return _spline.IsDerivedFromParent();
		if ( fieldName == "splineData" )
			return _splineData.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class DBEaselSoundsData : DBResource
{
	private UndoRedoDBPtr<DBEaselSoundsData> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselSoundsData> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBEaselSound> _sounds;

	[Category( "Easel sounds data" )]
	[EnumArray(typeof(EEaselSoundType))]
	public libdb.IChangeableList<DBEaselSound> sounds { get { return _sounds; } set { _sounds.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselSoundsData>(owner);
		_sounds = new UndoRedoAssignableList<DBEaselSound>( owner, typeof( EEaselSoundType ) );
		___parent.Changed += FireChangedEvent;
		_sounds.Changed += FireChangedEvent;
	}

	public DBEaselSoundsData()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselSoundsData source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselSoundsData" );
		sounds = source.sounds;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselSoundsData source = _source as DBEaselSoundsData;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselSoundsData" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselSoundsData newParent = rawParent == null ? null : rawParent.Get<DBEaselSoundsData>();
		if ( newParent == null && _newParent is DBEaselSoundsData )
			newParent = _newParent as DBEaselSoundsData;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sounds.SetParent( newParent == null ? null : newParent._sounds );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sounds.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sounds.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sounds" )
			_sounds.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class DBEaselSpline : DBResource
{
	private UndoRedoDBPtr<DBEaselSpline> ___parent;
	[HideInOutliner]
	public new DBPtr<DBEaselSpline> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private AnimatedPlacement _priestessPosition;
	private UndoRedo<bool> _overridePristessPosition;
	private UndoRedo<float> _colorWeightsPower;
	private UndoRedo<float> _colorWeightsMultiplier;
	private UndoRedo<bool> _overrideColorWeightsParams;
	private UndoRedo<EDifficultyLevel> _difficulty;
	private DBBoard _board;
	private UndoRedoAssignableList<DBPtr<DBEaselPath>> _path;

	public AnimatedPlacement priestessPosition { get { return _priestessPosition; } set { _priestessPosition.Assign( value ); } }

	public bool overridePristessPosition { get { return _overridePristessPosition.Get(); } set { _overridePristessPosition.Set( value ); } }

	public float colorWeightsPower { get { return _colorWeightsPower.Get(); } set { _colorWeightsPower.Set( value ); } }

	public float colorWeightsMultiplier { get { return _colorWeightsMultiplier.Get(); } set { _colorWeightsMultiplier.Set( value ); } }

	public bool overrideColorWeightsParams { get { return _overrideColorWeightsParams.Get(); } set { _overrideColorWeightsParams.Set( value ); } }

	public EDifficultyLevel difficulty { get { return _difficulty.Get(); } set { _difficulty.Set( value ); } }

	[Category( "Board" )]
	public DBBoard board { get { return _board; } set { _board.Assign( value ); } }

	[Category( "Paths" )]
	public libdb.IChangeableList<DBPtr<DBEaselPath>> path { get { return _path; } set { _path.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBEaselSpline>(owner);
		_priestessPosition = new AnimatedPlacement( owner );
		_overridePristessPosition = new UndoRedo<bool>( owner, false );
		_colorWeightsPower = new UndoRedo<float>( owner, 0.0f );
		_colorWeightsMultiplier = new UndoRedo<float>( owner, 0.0f );
		_overrideColorWeightsParams = new UndoRedo<bool>( owner, false );
		_difficulty = new UndoRedo<EDifficultyLevel>( owner, EDifficultyLevel.Unknown );
		_board = new DBBoard( owner );
		_path = new UndoRedoAssignableList<DBPtr<DBEaselPath>>( owner );
		___parent.Changed += FireChangedEvent;
		_priestessPosition.Changed += FireChangedEvent;
		_overridePristessPosition.Changed += FireChangedEvent;
		_colorWeightsPower.Changed += FireChangedEvent;
		_colorWeightsMultiplier.Changed += FireChangedEvent;
		_overrideColorWeightsParams.Changed += FireChangedEvent;
		_difficulty.Changed += FireChangedEvent;
		_board.Changed += FireChangedEvent;
		_path.Changed += FireChangedEvent;
	}

	public DBEaselSpline()
	{
		Initialize( this );
	}
	private void AssignSelf( DBEaselSpline source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBEaselSpline" );
		priestessPosition = source.priestessPosition;
		overridePristessPosition = source.overridePristessPosition;
		colorWeightsPower = source.colorWeightsPower;
		colorWeightsMultiplier = source.colorWeightsMultiplier;
		overrideColorWeightsParams = source.overrideColorWeightsParams;
		difficulty = source.difficulty;
		board = source.board;
		path = source.path;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBEaselSpline source = _source as DBEaselSpline;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBEaselSpline" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBEaselSpline newParent = rawParent == null ? null : rawParent.Get<DBEaselSpline>();
		if ( newParent == null && _newParent is DBEaselSpline )
			newParent = _newParent as DBEaselSpline;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_priestessPosition.SetParent( newParent == null ? null : newParent._priestessPosition );
		_overridePristessPosition.SetParent( newParent == null ? null : newParent._overridePristessPosition );
		_colorWeightsPower.SetParent( newParent == null ? null : newParent._colorWeightsPower );
		_colorWeightsMultiplier.SetParent( newParent == null ? null : newParent._colorWeightsMultiplier );
		_overrideColorWeightsParams.SetParent( newParent == null ? null : newParent._overrideColorWeightsParams );
		_difficulty.SetParent( newParent == null ? null : newParent._difficulty );
		_board.SetParent( newParent == null ? null : newParent._board );
		_path.SetParent( newParent == null ? null : newParent._path );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_priestessPosition.Reset();
		_overridePristessPosition.Reset();
		_colorWeightsPower.Reset();
		_colorWeightsMultiplier.Reset();
		_overrideColorWeightsParams.Reset();
		_difficulty.Reset();
		_board.Reset();
		_path.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_priestessPosition.IsDerivedFromParent()
			&& _overridePristessPosition.IsDerivedFromParent()
			&& _colorWeightsPower.IsDerivedFromParent()
			&& _colorWeightsMultiplier.IsDerivedFromParent()
			&& _overrideColorWeightsParams.IsDerivedFromParent()
			&& _difficulty.IsDerivedFromParent()
			&& _board.IsDerivedFromParent()
			&& _path.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "priestessPosition" )
			_priestessPosition.Reset();
		else if ( fieldName == "overridePristessPosition" )
			_overridePristessPosition.Reset();
		else if ( fieldName == "colorWeightsPower" )
			_colorWeightsPower.Reset();
		else if ( fieldName == "colorWeightsMultiplier" )
			_colorWeightsMultiplier.Reset();
		else if ( fieldName == "overrideColorWeightsParams" )
			_overrideColorWeightsParams.Reset();
		else if ( fieldName == "difficulty" )
			_difficulty.Reset();
		else if ( fieldName == "board" )
			_board.Reset();
		else if ( fieldName == "path" )
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
		if ( fieldName == "priestessPosition" )
			return _priestessPosition.IsDerivedFromParent();
		if ( fieldName == "overridePristessPosition" )
			return _overridePristessPosition.IsDerivedFromParent();
		if ( fieldName == "colorWeightsPower" )
			return _colorWeightsPower.IsDerivedFromParent();
		if ( fieldName == "colorWeightsMultiplier" )
			return _colorWeightsMultiplier.IsDerivedFromParent();
		if ( fieldName == "overrideColorWeightsParams" )
			return _overrideColorWeightsParams.IsDerivedFromParent();
		if ( fieldName == "difficulty" )
			return _difficulty.IsDerivedFromParent();
		if ( fieldName == "board" )
			return _board.IsDerivedFromParent();
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

public class DBLuxBall : DBResource
{
	private UndoRedoDBPtr<DBLuxBall> ___parent;
	[HideInOutliner]
	public new DBPtr<DBLuxBall> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EColor> _ballColor;

	public EColor ballColor { get { return _ballColor.Get(); } set { _ballColor.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBLuxBall>(owner);
		_ballColor = new UndoRedo<EColor>( owner, EColor.black );
		___parent.Changed += FireChangedEvent;
		_ballColor.Changed += FireChangedEvent;
	}

	public DBLuxBall()
	{
		Initialize( this );
	}
	private void AssignSelf( DBLuxBall source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBLuxBall" );
		ballColor = source.ballColor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBLuxBall source = _source as DBLuxBall;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLuxBall" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBLuxBall newParent = rawParent == null ? null : rawParent.Get<DBLuxBall>();
		if ( newParent == null && _newParent is DBLuxBall )
			newParent = _newParent as DBLuxBall;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ballColor.SetParent( newParent == null ? null : newParent._ballColor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ballColor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ballColor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ballColor" )
			_ballColor.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ballColor" )
			return _ballColor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
public class DBPainterFragment : DBResource
{
	private UndoRedoDBPtr<DBPainterFragment> ___parent;
	[HideInOutliner]
	public new DBPtr<DBPainterFragment> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private DBListFragments _painterFragment;
	private UndoRedoDBPtr<PaintMaterial> _paintMaterial;

	[Category( "Painter fragment resource" )]
	public DBListFragments painterFragment { get { return _painterFragment; } set { _painterFragment.Assign( value ); } }

	[Category( "Painter render parameters" )]
	public DBPtr<PaintMaterial> paintMaterial { get { return _paintMaterial.Get(); } set { _paintMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBPainterFragment>(owner);
		_painterFragment = new DBListFragments( owner );
		_paintMaterial = new UndoRedoDBPtr<PaintMaterial>( owner );
		___parent.Changed += FireChangedEvent;
		_painterFragment.Changed += FireChangedEvent;
		_paintMaterial.Changed += FireChangedEvent;
	}

	public DBPainterFragment()
	{
		Initialize( this );
	}
	private void AssignSelf( DBPainterFragment source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBPainterFragment" );
		painterFragment = source.painterFragment;
		paintMaterial = source.paintMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBPainterFragment source = _source as DBPainterFragment;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPainterFragment" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBPainterFragment newParent = rawParent == null ? null : rawParent.Get<DBPainterFragment>();
		if ( newParent == null && _newParent is DBPainterFragment )
			newParent = _newParent as DBPainterFragment;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_painterFragment.SetParent( newParent == null ? null : newParent._painterFragment );
		_paintMaterial.SetParent( newParent == null ? null : newParent._paintMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_painterFragment.Reset();
		_paintMaterial.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_painterFragment.IsDerivedFromParent()
			&& _paintMaterial.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "painterFragment" )
			_painterFragment.Reset();
		else if ( fieldName == "paintMaterial" )
			_paintMaterial.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "painterFragment" )
			return _painterFragment.IsDerivedFromParent();
		if ( fieldName == "paintMaterial" )
			return _paintMaterial.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class DBPainterPoint : DBResource
{
	private UndoRedoDBPtr<DBPainterPoint> ___parent;
	[HideInOutliner]
	public new DBPtr<DBPainterPoint> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private DBPoint _pointCoords;
	private UndoRedo<int> _pointCapacity;
	private UndoRedo<EColor> _pointColor;

	[Category( "PainterPoint" )]
	[Description( "Point data for painter operations" )]
	public DBPoint pointCoords { get { return _pointCoords; } set { _pointCoords.Assign( value ); } }

	public int pointCapacity { get { return _pointCapacity.Get(); } set { _pointCapacity.Set( value ); } }

	public EColor pointColor { get { return _pointColor.Get(); } set { _pointColor.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBPainterPoint>(owner);
		_pointCoords = new DBPoint( owner );
		_pointCapacity = new UndoRedo<int>( owner, 1 );
		_pointColor = new UndoRedo<EColor>( owner, EColor.black );
		___parent.Changed += FireChangedEvent;
		_pointCoords.Changed += FireChangedEvent;
		_pointCapacity.Changed += FireChangedEvent;
		_pointColor.Changed += FireChangedEvent;
	}

	public DBPainterPoint()
	{
		Initialize( this );
	}
	private void AssignSelf( DBPainterPoint source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBPainterPoint" );
		pointCoords = source.pointCoords;
		pointCapacity = source.pointCapacity;
		pointColor = source.pointColor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBPainterPoint source = _source as DBPainterPoint;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPainterPoint" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBPainterPoint newParent = rawParent == null ? null : rawParent.Get<DBPainterPoint>();
		if ( newParent == null && _newParent is DBPainterPoint )
			newParent = _newParent as DBPainterPoint;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_pointCoords.SetParent( newParent == null ? null : newParent._pointCoords );
		_pointCapacity.SetParent( newParent == null ? null : newParent._pointCapacity );
		_pointColor.SetParent( newParent == null ? null : newParent._pointColor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_pointCoords.Reset();
		_pointCapacity.Reset();
		_pointColor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_pointCoords.IsDerivedFromParent()
			&& _pointCapacity.IsDerivedFromParent()
			&& _pointColor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "pointCoords" )
			_pointCoords.Reset();
		else if ( fieldName == "pointCapacity" )
			_pointCapacity.Reset();
		else if ( fieldName == "pointColor" )
			_pointColor.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "pointCoords" )
			return _pointCoords.IsDerivedFromParent();
		if ( fieldName == "pointCapacity" )
			return _pointCapacity.IsDerivedFromParent();
		if ( fieldName == "pointColor" )
			return _pointColor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
public class DBPriestessLevelStats : DBResource
{
	private UndoRedoDBPtr<DBPriestessLevelStats> ___parent;
	[HideInOutliner]
	public new DBPtr<DBPriestessLevelStats> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EPriestessLevel> _level;
	private UndoRedo<int> _pictureEndNafta;
	private UndoRedo<int> _ballExplosionNafta;
	private UndoRedo<int> _chainKillNafta;
	private UndoRedo<int> _paintFragmentFinishedNafta;
	private UndoRedo<int> _fastCompletePerSecondNafta;
	private UndoRedo<int> _naftaRequired;
	private UndoRedo<float> _goldMedalTime;
	private UndoRedo<float> _silverMedalTime;
	private UndoRedo<int> _goldMedalNafta;
	private UndoRedo<int> _silverMedalNafta;
	private UndoRedo<float> _failNaftaReturnMultiplier;

	public EPriestessLevel level { get { return _level.Get(); } set { _level.Set( value ); } }

	public int pictureEndNafta { get { return _pictureEndNafta.Get(); } set { _pictureEndNafta.Set( value ); } }

	public int ballExplosionNafta { get { return _ballExplosionNafta.Get(); } set { _ballExplosionNafta.Set( value ); } }

	public int chainKillNafta { get { return _chainKillNafta.Get(); } set { _chainKillNafta.Set( value ); } }

	public int paintFragmentFinishedNafta { get { return _paintFragmentFinishedNafta.Get(); } set { _paintFragmentFinishedNafta.Set( value ); } }

	public int fastCompletePerSecondNafta { get { return _fastCompletePerSecondNafta.Get(); } set { _fastCompletePerSecondNafta.Set( value ); } }

	public int naftaRequired { get { return _naftaRequired.Get(); } set { _naftaRequired.Set( value ); } }

	public float goldMedalTime { get { return _goldMedalTime.Get(); } set { _goldMedalTime.Set( value ); } }

	public float silverMedalTime { get { return _silverMedalTime.Get(); } set { _silverMedalTime.Set( value ); } }

	public int goldMedalNafta { get { return _goldMedalNafta.Get(); } set { _goldMedalNafta.Set( value ); } }

	public int silverMedalNafta { get { return _silverMedalNafta.Get(); } set { _silverMedalNafta.Set( value ); } }

	[Category( "How much nafta will be returned to priestess on level fail. [0, 1]" )]
	[FloatMinMax(0, 1)]
	public float failNaftaReturnMultiplier { get { return _failNaftaReturnMultiplier.Get(); } set { _failNaftaReturnMultiplier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBPriestessLevelStats>(owner);
		_level = new UndoRedo<EPriestessLevel>( owner, EPriestessLevel.level_0 );
		_pictureEndNafta = new UndoRedo<int>( owner, 0 );
		_ballExplosionNafta = new UndoRedo<int>( owner, 0 );
		_chainKillNafta = new UndoRedo<int>( owner, 0 );
		_paintFragmentFinishedNafta = new UndoRedo<int>( owner, 0 );
		_fastCompletePerSecondNafta = new UndoRedo<int>( owner, 0 );
		_naftaRequired = new UndoRedo<int>( owner, 0 );
		_goldMedalTime = new UndoRedo<float>( owner, 100.0f );
		_silverMedalTime = new UndoRedo<float>( owner, 150.0f );
		_goldMedalNafta = new UndoRedo<int>( owner, 0 );
		_silverMedalNafta = new UndoRedo<int>( owner, 0 );
		_failNaftaReturnMultiplier = new UndoRedo<float>( owner, 0.66f );
		___parent.Changed += FireChangedEvent;
		_level.Changed += FireChangedEvent;
		_pictureEndNafta.Changed += FireChangedEvent;
		_ballExplosionNafta.Changed += FireChangedEvent;
		_chainKillNafta.Changed += FireChangedEvent;
		_paintFragmentFinishedNafta.Changed += FireChangedEvent;
		_fastCompletePerSecondNafta.Changed += FireChangedEvent;
		_naftaRequired.Changed += FireChangedEvent;
		_goldMedalTime.Changed += FireChangedEvent;
		_silverMedalTime.Changed += FireChangedEvent;
		_goldMedalNafta.Changed += FireChangedEvent;
		_silverMedalNafta.Changed += FireChangedEvent;
		_failNaftaReturnMultiplier.Changed += FireChangedEvent;
	}

	public DBPriestessLevelStats()
	{
		Initialize( this );
	}
	private void AssignSelf( DBPriestessLevelStats source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBPriestessLevelStats" );
		level = source.level;
		pictureEndNafta = source.pictureEndNafta;
		ballExplosionNafta = source.ballExplosionNafta;
		chainKillNafta = source.chainKillNafta;
		paintFragmentFinishedNafta = source.paintFragmentFinishedNafta;
		fastCompletePerSecondNafta = source.fastCompletePerSecondNafta;
		naftaRequired = source.naftaRequired;
		goldMedalTime = source.goldMedalTime;
		silverMedalTime = source.silverMedalTime;
		goldMedalNafta = source.goldMedalNafta;
		silverMedalNafta = source.silverMedalNafta;
		failNaftaReturnMultiplier = source.failNaftaReturnMultiplier;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBPriestessLevelStats source = _source as DBPriestessLevelStats;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPriestessLevelStats" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBPriestessLevelStats newParent = rawParent == null ? null : rawParent.Get<DBPriestessLevelStats>();
		if ( newParent == null && _newParent is DBPriestessLevelStats )
			newParent = _newParent as DBPriestessLevelStats;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_level.SetParent( newParent == null ? null : newParent._level );
		_pictureEndNafta.SetParent( newParent == null ? null : newParent._pictureEndNafta );
		_ballExplosionNafta.SetParent( newParent == null ? null : newParent._ballExplosionNafta );
		_chainKillNafta.SetParent( newParent == null ? null : newParent._chainKillNafta );
		_paintFragmentFinishedNafta.SetParent( newParent == null ? null : newParent._paintFragmentFinishedNafta );
		_fastCompletePerSecondNafta.SetParent( newParent == null ? null : newParent._fastCompletePerSecondNafta );
		_naftaRequired.SetParent( newParent == null ? null : newParent._naftaRequired );
		_goldMedalTime.SetParent( newParent == null ? null : newParent._goldMedalTime );
		_silverMedalTime.SetParent( newParent == null ? null : newParent._silverMedalTime );
		_goldMedalNafta.SetParent( newParent == null ? null : newParent._goldMedalNafta );
		_silverMedalNafta.SetParent( newParent == null ? null : newParent._silverMedalNafta );
		_failNaftaReturnMultiplier.SetParent( newParent == null ? null : newParent._failNaftaReturnMultiplier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_level.Reset();
		_pictureEndNafta.Reset();
		_ballExplosionNafta.Reset();
		_chainKillNafta.Reset();
		_paintFragmentFinishedNafta.Reset();
		_fastCompletePerSecondNafta.Reset();
		_naftaRequired.Reset();
		_goldMedalTime.Reset();
		_silverMedalTime.Reset();
		_goldMedalNafta.Reset();
		_silverMedalNafta.Reset();
		_failNaftaReturnMultiplier.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _pictureEndNafta.IsDerivedFromParent()
			&& _ballExplosionNafta.IsDerivedFromParent()
			&& _chainKillNafta.IsDerivedFromParent()
			&& _paintFragmentFinishedNafta.IsDerivedFromParent()
			&& _fastCompletePerSecondNafta.IsDerivedFromParent()
			&& _naftaRequired.IsDerivedFromParent()
			&& _goldMedalTime.IsDerivedFromParent()
			&& _silverMedalTime.IsDerivedFromParent()
			&& _goldMedalNafta.IsDerivedFromParent()
			&& _silverMedalNafta.IsDerivedFromParent()
			&& _failNaftaReturnMultiplier.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
		else if ( fieldName == "pictureEndNafta" )
			_pictureEndNafta.Reset();
		else if ( fieldName == "ballExplosionNafta" )
			_ballExplosionNafta.Reset();
		else if ( fieldName == "chainKillNafta" )
			_chainKillNafta.Reset();
		else if ( fieldName == "paintFragmentFinishedNafta" )
			_paintFragmentFinishedNafta.Reset();
		else if ( fieldName == "fastCompletePerSecondNafta" )
			_fastCompletePerSecondNafta.Reset();
		else if ( fieldName == "naftaRequired" )
			_naftaRequired.Reset();
		else if ( fieldName == "goldMedalTime" )
			_goldMedalTime.Reset();
		else if ( fieldName == "silverMedalTime" )
			_silverMedalTime.Reset();
		else if ( fieldName == "goldMedalNafta" )
			_goldMedalNafta.Reset();
		else if ( fieldName == "silverMedalNafta" )
			_silverMedalNafta.Reset();
		else if ( fieldName == "failNaftaReturnMultiplier" )
			_failNaftaReturnMultiplier.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "level" )
			return _level.IsDerivedFromParent();
		if ( fieldName == "pictureEndNafta" )
			return _pictureEndNafta.IsDerivedFromParent();
		if ( fieldName == "ballExplosionNafta" )
			return _ballExplosionNafta.IsDerivedFromParent();
		if ( fieldName == "chainKillNafta" )
			return _chainKillNafta.IsDerivedFromParent();
		if ( fieldName == "paintFragmentFinishedNafta" )
			return _paintFragmentFinishedNafta.IsDerivedFromParent();
		if ( fieldName == "fastCompletePerSecondNafta" )
			return _fastCompletePerSecondNafta.IsDerivedFromParent();
		if ( fieldName == "naftaRequired" )
			return _naftaRequired.IsDerivedFromParent();
		if ( fieldName == "goldMedalTime" )
			return _goldMedalTime.IsDerivedFromParent();
		if ( fieldName == "silverMedalTime" )
			return _silverMedalTime.IsDerivedFromParent();
		if ( fieldName == "goldMedalNafta" )
			return _goldMedalNafta.IsDerivedFromParent();
		if ( fieldName == "silverMedalNafta" )
			return _silverMedalNafta.IsDerivedFromParent();
		if ( fieldName == "failNaftaReturnMultiplier" )
			return _failNaftaReturnMultiplier.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class DBPriestessStats : DBResource
{
	private UndoRedoDBPtr<DBPriestessStats> ___parent;
	[HideInOutliner]
	public new DBPtr<DBPriestessStats> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<DBPriestessLevelStats>> _stats;
	private UndoRedo<int> _comboNafta;
	private UndoRedo<int> _coinNafta;
	private UndoRedo<int> _heartsForLevelsStartsFrom;
	private UndoRedoList<float> _wonGameHearts;

	[Category( "Easel statistics params" )]
	[EnumArray(typeof(EPriestessLevel))]
	public libdb.IChangeableList<DBPtr<DBPriestessLevelStats>> stats { get { return _stats; } set { _stats.Assign( value ); } }

	public int comboNafta { get { return _comboNafta.Get(); } set { _comboNafta.Set( value ); } }

	public int coinNafta { get { return _coinNafta.Get(); } set { _coinNafta.Set( value ); } }

	[IntMin(0)]
	public int heartsForLevelsStartsFrom { get { return _heartsForLevelsStartsFrom.Get(); } set { _heartsForLevelsStartsFrom.Set( value ); } }

	[EnumArray(typeof(WonGameHearts))]
	public libdb.IChangeableList<float> wonGameHearts { get { return _wonGameHearts; } set { _wonGameHearts.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBPriestessStats>(owner);
		_stats = new UndoRedoAssignableList<DBPtr<DBPriestessLevelStats>>( owner, typeof( EPriestessLevel ) );
		_comboNafta = new UndoRedo<int>( owner, 10 );
		_coinNafta = new UndoRedo<int>( owner, 10 );
		_heartsForLevelsStartsFrom = new UndoRedo<int>( owner, 5 );
		_wonGameHearts = new UndoRedoList<float>( owner, typeof( WonGameHearts ) );
		___parent.Changed += FireChangedEvent;
		_stats.Changed += FireChangedEvent;
		_comboNafta.Changed += FireChangedEvent;
		_coinNafta.Changed += FireChangedEvent;
		_heartsForLevelsStartsFrom.Changed += FireChangedEvent;
		_wonGameHearts.Changed += FireChangedEvent;
	}

	public DBPriestessStats()
	{
		Initialize( this );
	}
	private void AssignSelf( DBPriestessStats source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBPriestessStats" );
		stats = source.stats;
		comboNafta = source.comboNafta;
		coinNafta = source.coinNafta;
		heartsForLevelsStartsFrom = source.heartsForLevelsStartsFrom;
		wonGameHearts = source.wonGameHearts;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBPriestessStats source = _source as DBPriestessStats;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBPriestessStats" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBPriestessStats newParent = rawParent == null ? null : rawParent.Get<DBPriestessStats>();
		if ( newParent == null && _newParent is DBPriestessStats )
			newParent = _newParent as DBPriestessStats;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stats.SetParent( newParent == null ? null : newParent._stats );
		_comboNafta.SetParent( newParent == null ? null : newParent._comboNafta );
		_coinNafta.SetParent( newParent == null ? null : newParent._coinNafta );
		_heartsForLevelsStartsFrom.SetParent( newParent == null ? null : newParent._heartsForLevelsStartsFrom );
		_wonGameHearts.SetParent( newParent == null ? null : newParent._wonGameHearts );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stats.Reset();
		_comboNafta.Reset();
		_coinNafta.Reset();
		_heartsForLevelsStartsFrom.Reset();
		_wonGameHearts.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stats.IsDerivedFromParent()
			&& _comboNafta.IsDerivedFromParent()
			&& _coinNafta.IsDerivedFromParent()
			&& _heartsForLevelsStartsFrom.IsDerivedFromParent()
			&& _wonGameHearts.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stats" )
			_stats.Reset();
		else if ( fieldName == "comboNafta" )
			_comboNafta.Reset();
		else if ( fieldName == "coinNafta" )
			_coinNafta.Reset();
		else if ( fieldName == "heartsForLevelsStartsFrom" )
			_heartsForLevelsStartsFrom.Reset();
		else if ( fieldName == "wonGameHearts" )
			_wonGameHearts.Reset();
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
		if ( fieldName == "comboNafta" )
			return _comboNafta.IsDerivedFromParent();
		if ( fieldName == "coinNafta" )
			return _coinNafta.IsDerivedFromParent();
		if ( fieldName == "heartsForLevelsStartsFrom" )
			return _heartsForLevelsStartsFrom.IsDerivedFromParent();
		if ( fieldName == "wonGameHearts" )
			return _wonGameHearts.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
