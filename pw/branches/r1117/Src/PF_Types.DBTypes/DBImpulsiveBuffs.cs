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
public enum ECompareOperator
{
	Equal = 0,
	Greater = 1,
	GreaterOrEqual = 2,
	Less = 3,
	LessOrEqual = 4,
};

public enum EEventsCombineMove
{
	AND = 0,
	OR = 1,
	XOR = 2,
};

public enum ELevelCheckType
{
	Exact = 0,
	AvgOfSelfTeam = 1,
	AvgOfOppositeTeam = 2,
};

public enum ERangeType
{
	ExactValue = 0,
	AttackRange = 1,
};

public enum ImpulseBuffClass
{
	Class_BuffTower = 0,
	Class_BuffHero = 1,
};

public enum ImpulsiveEventType
{
	HeroEvent = 0,
	TowerEvent = 1,
};

public class AccessCost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AccessCost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _impulsesPoints;
	private UndoRedo<int> _gamesLimit;

	[Description( "Количество очков, необходимое для получения импульств этого уровня." )]
	public int impulsesPoints { get { return _impulsesPoints.Get(); } set { _impulsesPoints.Set( value ); } }

	[Description( "Импульсы из скольки последних игр (включая текущую) учитываем. 0 — без ограничений." )]
	public int gamesLimit { get { return _gamesLimit.Get(); } set { _gamesLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_impulsesPoints = new UndoRedo<int>( owner, 0 );
		_gamesLimit = new UndoRedo<int>( owner, 0 );
		_impulsesPoints.Changed += FireChangedEvent;
		_gamesLimit.Changed += FireChangedEvent;
	}

	public AccessCost()
	{
		Initialize( GetOwner() );
	}

	public AccessCost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AccessCost( DBResource owner, AccessCost source )
		: this(owner, source, true){}

	protected AccessCost( DBResource owner, AccessCost source, bool fireEvent )
	{
		_impulsesPoints = new UndoRedo<int>( owner, source.impulsesPoints );
		_gamesLimit = new UndoRedo<int>( owner, source.gamesLimit );
		_impulsesPoints.Changed += FireChangedEvent;
		_gamesLimit.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AccessCost source = _source as AccessCost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AccessCost" );
		impulsesPoints = source.impulsesPoints;
		gamesLimit = source.gamesLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AccessCost newParent = _newParent as AccessCost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_impulsesPoints.SetParent( newParent == null ? null : newParent._impulsesPoints );
		_gamesLimit.SetParent( newParent == null ? null : newParent._gamesLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_impulsesPoints.Reset();
		_gamesLimit.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_impulsesPoints.IsDerivedFromParent()
			&& _gamesLimit.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "impulsesPoints" )
			_impulsesPoints.Reset();
		else if ( fieldName == "gamesLimit" )
			_gamesLimit.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "impulsesPoints" )
			return _impulsesPoints.IsDerivedFromParent();
		if ( fieldName == "gamesLimit" )
			return _gamesLimit.IsDerivedFromParent();
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

public class AccessInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AccessInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedo<int> _points;

	[Description( "Уровень доступности импульса (0, 1, ... )" )]
	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	[Description( "Сколько очков добавится герою при взятии этого импульса" )]
	public int points { get { return _points.Get(); } set { _points.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_points = new UndoRedo<int>( owner, 1 );
		_level.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
	}

	public AccessInfo()
	{
		Initialize( GetOwner() );
	}

	public AccessInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AccessInfo( DBResource owner, AccessInfo source )
		: this(owner, source, true){}

	protected AccessInfo( DBResource owner, AccessInfo source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_points = new UndoRedo<int>( owner, source.points );
		_level.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AccessInfo source = _source as AccessInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AccessInfo" );
		level = source.level;
		points = source.points;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AccessInfo newParent = _newParent as AccessInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_points.SetParent( newParent == null ? null : newParent._points );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_points.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _points.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
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
		if ( fieldName == "level" )
			return _level.IsDerivedFromParent();
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

[DBVersion(1)]
[IndexField("caption")]
public class ImpulsiveBuff : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ImpulsiveBuff __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Ability> _buff;
	private UndoRedoAssignableList<DBPtr<ImpulsiveEvent>> _events;
	private AccessInfo _accessInfo;
	private UndoRedo<string> _caption;
	private UndoRedo<bool> _canBeOfferedToDead;
	private UndoRedo<float> _offerTime;
	private UndoRedo<float> _cooldown;
	private UndoRedo<string> _cooldownGroup;
	private UndoRedo<float> _priority;
	private UndoRedo<ImpulseBuffClass> _buffClass;
	private UndoRedo<bool> _isSimple;
	private UndoRedo<bool> _oncePerTeam;

	public DBPtr<Ability> buff { get { return _buff.Get(); } set { _buff.Set( value ); } }

	public libdb.IChangeableList<DBPtr<ImpulsiveEvent>> events { get { return _events; } set { _events.Assign( value ); } }

	[Description( "Информация про доступность импульса" )]
	public AccessInfo accessInfo { get { return _accessInfo; } set { _accessInfo.Assign( value ); } }

	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	public bool canBeOfferedToDead { get { return _canBeOfferedToDead.Get(); } set { _canBeOfferedToDead.Set( value ); } }

	[Description( "Force buff message display time. If 0 - used default time is used" )]
	public float offerTime { get { return _offerTime.Get(); } set { _offerTime.Set( value ); } }

	[Description( "Cooldown of that impulse to be activated" )]
	public float cooldown { get { return _cooldown.Get(); } set { _cooldown.Set( value ); } }

	[Description( "Cooldowns are shared through the same groups" )]
	public string cooldownGroup { get { return _cooldownGroup.Get(); } set { _cooldownGroup.Set( value ); } }

	[Description( "Priority" )]
	[FloatMinMax(0, 1)]
	public float priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "Specifies buff target class" )]
	public ImpulseBuffClass buffClass { get { return _buffClass.Get(); } set { _buffClass.Set( value ); } }

	[Description( "If true - creates new state, cancels current states, etc; if false - just uses external ability" )]
	public bool isSimple { get { return _isSimple.Get(); } set { _isSimple.Set( value ); } }

	[Description( "Describes if this impulse can be bought only once per team" )]
	public bool oncePerTeam { get { return _oncePerTeam.Get(); } set { _oncePerTeam.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_buff = new UndoRedoDBPtr<Ability>( owner );
		_events = new UndoRedoAssignableList<DBPtr<ImpulsiveEvent>>( owner );
		_accessInfo = new AccessInfo( owner );
		_caption = new UndoRedo<string>( owner, string.Empty );
		_canBeOfferedToDead = new UndoRedo<bool>( owner, false );
		_offerTime = new UndoRedo<float>( owner, 0.0f );
		_cooldown = new UndoRedo<float>( owner, 10.0f );
		_cooldownGroup = new UndoRedo<string>( owner, "A" );
		_priority = new UndoRedo<float>( owner, 0.3f );
		_buffClass = new UndoRedo<ImpulseBuffClass>( owner, ImpulseBuffClass.Class_BuffHero );
		_isSimple = new UndoRedo<bool>( owner, true );
		_oncePerTeam = new UndoRedo<bool>( owner, false );
		_buff.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		_accessInfo.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_canBeOfferedToDead.Changed += FireChangedEvent;
		_offerTime.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_cooldownGroup.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_buffClass.Changed += FireChangedEvent;
		_isSimple.Changed += FireChangedEvent;
		_oncePerTeam.Changed += FireChangedEvent;
	}

	public ImpulsiveBuff()
	{
		Initialize( GetOwner() );
	}

	public ImpulsiveBuff( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ImpulsiveBuff( DBResource owner, ImpulsiveBuff source )
		: this(owner, source, true){}

	protected ImpulsiveBuff( DBResource owner, ImpulsiveBuff source, bool fireEvent )
	{
		_buff = new UndoRedoDBPtr<Ability>( owner, source.buff );
		_events = new UndoRedoAssignableList<DBPtr<ImpulsiveEvent>>( owner );
		_events.Assign( source.events );
		_accessInfo = new AccessInfo( owner, source.accessInfo );
		_caption = new UndoRedo<string>( owner, source.caption );
		_canBeOfferedToDead = new UndoRedo<bool>( owner, source.canBeOfferedToDead );
		_offerTime = new UndoRedo<float>( owner, source.offerTime );
		_cooldown = new UndoRedo<float>( owner, source.cooldown );
		_cooldownGroup = new UndoRedo<string>( owner, source.cooldownGroup );
		_priority = new UndoRedo<float>( owner, source.priority );
		_buffClass = new UndoRedo<ImpulseBuffClass>( owner, source.buffClass );
		_isSimple = new UndoRedo<bool>( owner, source.isSimple );
		_oncePerTeam = new UndoRedo<bool>( owner, source.oncePerTeam );
		_buff.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		_accessInfo.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_canBeOfferedToDead.Changed += FireChangedEvent;
		_offerTime.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_cooldownGroup.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_buffClass.Changed += FireChangedEvent;
		_isSimple.Changed += FireChangedEvent;
		_oncePerTeam.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ImpulsiveBuff source = _source as ImpulsiveBuff;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveBuff" );
		buff = source.buff;
		events = source.events;
		accessInfo = source.accessInfo;
		caption = source.caption;
		canBeOfferedToDead = source.canBeOfferedToDead;
		offerTime = source.offerTime;
		cooldown = source.cooldown;
		cooldownGroup = source.cooldownGroup;
		priority = source.priority;
		buffClass = source.buffClass;
		isSimple = source.isSimple;
		oncePerTeam = source.oncePerTeam;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ImpulsiveBuff newParent = _newParent as ImpulsiveBuff;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_buff.SetParent( newParent == null ? null : newParent._buff );
		_events.SetParent( newParent == null ? null : newParent._events );
		_accessInfo.SetParent( newParent == null ? null : newParent._accessInfo );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		_canBeOfferedToDead.SetParent( newParent == null ? null : newParent._canBeOfferedToDead );
		_offerTime.SetParent( newParent == null ? null : newParent._offerTime );
		_cooldown.SetParent( newParent == null ? null : newParent._cooldown );
		_cooldownGroup.SetParent( newParent == null ? null : newParent._cooldownGroup );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_buffClass.SetParent( newParent == null ? null : newParent._buffClass );
		_isSimple.SetParent( newParent == null ? null : newParent._isSimple );
		_oncePerTeam.SetParent( newParent == null ? null : newParent._oncePerTeam );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_buff.Reset();
		_events.Reset();
		_accessInfo.Reset();
		_caption.Reset();
		_canBeOfferedToDead.Reset();
		_offerTime.Reset();
		_cooldown.Reset();
		_cooldownGroup.Reset();
		_priority.Reset();
		_buffClass.Reset();
		_isSimple.Reset();
		_oncePerTeam.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_buff.IsDerivedFromParent()
			&& _events.IsDerivedFromParent()
			&& _accessInfo.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			&& _canBeOfferedToDead.IsDerivedFromParent()
			&& _offerTime.IsDerivedFromParent()
			&& _cooldown.IsDerivedFromParent()
			&& _cooldownGroup.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& _buffClass.IsDerivedFromParent()
			&& _isSimple.IsDerivedFromParent()
			&& _oncePerTeam.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "buff" )
			_buff.Reset();
		else if ( fieldName == "events" )
			_events.Reset();
		else if ( fieldName == "accessInfo" )
			_accessInfo.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "canBeOfferedToDead" )
			_canBeOfferedToDead.Reset();
		else if ( fieldName == "offerTime" )
			_offerTime.Reset();
		else if ( fieldName == "cooldown" )
			_cooldown.Reset();
		else if ( fieldName == "cooldownGroup" )
			_cooldownGroup.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else if ( fieldName == "buffClass" )
			_buffClass.Reset();
		else if ( fieldName == "isSimple" )
			_isSimple.Reset();
		else if ( fieldName == "oncePerTeam" )
			_oncePerTeam.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "buff" )
			return _buff.IsDerivedFromParent();
		if ( fieldName == "events" )
			return _events.IsDerivedFromParent();
		if ( fieldName == "accessInfo" )
			return _accessInfo.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "canBeOfferedToDead" )
			return _canBeOfferedToDead.IsDerivedFromParent();
		if ( fieldName == "offerTime" )
			return _offerTime.IsDerivedFromParent();
		if ( fieldName == "cooldown" )
			return _cooldown.IsDerivedFromParent();
		if ( fieldName == "cooldownGroup" )
			return _cooldownGroup.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		if ( fieldName == "buffClass" )
			return _buffClass.IsDerivedFromParent();
		if ( fieldName == "isSimple" )
			return _isSimple.IsDerivedFromParent();
		if ( fieldName == "oncePerTeam" )
			return _oncePerTeam.IsDerivedFromParent();
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

public class NegativeEffectCondition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private NegativeEffectCondition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _minCount;
	private UndoRedo<EDispellPriority> _priority;

	public int minCount { get { return _minCount.Get(); } set { _minCount.Set( value ); } }

	public EDispellPriority priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minCount = new UndoRedo<int>( owner, 1 );
		_priority = new UndoRedo<EDispellPriority>( owner, EDispellPriority.NonDispellable );
		_minCount.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
	}

	public NegativeEffectCondition()
	{
		Initialize( GetOwner() );
	}

	public NegativeEffectCondition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public NegativeEffectCondition( DBResource owner, NegativeEffectCondition source )
		: this(owner, source, true){}

	protected NegativeEffectCondition( DBResource owner, NegativeEffectCondition source, bool fireEvent )
	{
		_minCount = new UndoRedo<int>( owner, source.minCount );
		_priority = new UndoRedo<EDispellPriority>( owner, source.priority );
		_minCount.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		NegativeEffectCondition source = _source as NegativeEffectCondition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NegativeEffectCondition" );
		minCount = source.minCount;
		priority = source.priority;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		NegativeEffectCondition newParent = _newParent as NegativeEffectCondition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minCount.SetParent( newParent == null ? null : newParent._minCount );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minCount.Reset();
		_priority.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minCount.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minCount" )
			_minCount.Reset();
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
		if ( fieldName == "minCount" )
			return _minCount.IsDerivedFromParent();
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

public class UnitCountingWeights : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UnitCountingWeights __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _setName;
	private UndoRedoList<int> _weights;

	public string setName { get { return _setName.Get(); } set { _setName.Set( value ); } }

	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<int> weights { get { return _weights; } set { _weights.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_setName = new UndoRedo<string>( owner, string.Empty );
		_weights = new UndoRedoList<int>( owner, typeof( EUnitType ) );
		_setName.Changed += FireChangedEvent;
		_weights.Changed += FireChangedEvent;
	}

	public UnitCountingWeights()
	{
		Initialize( GetOwner() );
	}

	public UnitCountingWeights( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UnitCountingWeights( DBResource owner, UnitCountingWeights source )
		: this(owner, source, true){}

	protected UnitCountingWeights( DBResource owner, UnitCountingWeights source, bool fireEvent )
	{
		_setName = new UndoRedo<string>( owner, source.setName );
		_weights = new UndoRedoList<int>( owner, typeof( EUnitType ) );
		_weights.Assign( source.weights );
		_setName.Changed += FireChangedEvent;
		_weights.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UnitCountingWeights source = _source as UnitCountingWeights;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitCountingWeights" );
		setName = source.setName;
		weights = source.weights;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UnitCountingWeights newParent = _newParent as UnitCountingWeights;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_setName.SetParent( newParent == null ? null : newParent._setName );
		_weights.SetParent( newParent == null ? null : newParent._weights );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_setName.Reset();
		_weights.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_setName.IsDerivedFromParent()
			&& _weights.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "setName" )
			_setName.Reset();
		else if ( fieldName == "weights" )
			_weights.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "setName" )
			return _setName.IsDerivedFromParent();
		if ( fieldName == "weights" )
			return _weights.IsDerivedFromParent();
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

[FactoryBase("Create", "NWorld::ImpulsiveEvent", "class NWorld::ImpulsiveBuffsManager* _buffsManager", Define = "!SERVER_DB")]
[IndexField("caption")]
[NonTerminal]
public class ImpulsiveEvent : DBResource
{
	private UndoRedoDBPtr<ImpulsiveEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<ImpulsiveEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;
	private UndoRedo<bool> _suggestTarget;
	private UndoRedo<ImpulsiveEventType> _eventType;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	public bool suggestTarget { get { return _suggestTarget.Get(); } set { _suggestTarget.Set( value ); } }

	public ImpulsiveEventType eventType { get { return _eventType.Get(); } set { _eventType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ImpulsiveEvent>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		_suggestTarget = new UndoRedo<bool>( owner, false );
		_eventType = new UndoRedo<ImpulsiveEventType>( owner, ImpulsiveEventType.HeroEvent );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_suggestTarget.Changed += FireChangedEvent;
		_eventType.Changed += FireChangedEvent;
	}

	public ImpulsiveEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( ImpulsiveEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveEvent" );
		caption = source.caption;
		suggestTarget = source.suggestTarget;
		eventType = source.eventType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ImpulsiveEvent source = _source as ImpulsiveEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ImpulsiveEvent newParent = rawParent == null ? null : rawParent.Get<ImpulsiveEvent>();
		if ( newParent == null && _newParent is ImpulsiveEvent )
			newParent = _newParent as ImpulsiveEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_suggestTarget.SetParent( newParent == null ? null : newParent._suggestTarget );
		_eventType.SetParent( newParent == null ? null : newParent._eventType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		_suggestTarget.Reset();
		_eventType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _suggestTarget.IsDerivedFromParent()
			&& _eventType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "suggestTarget" )
			_suggestTarget.Reset();
		else if ( fieldName == "eventType" )
			_eventType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "suggestTarget" )
			return _suggestTarget.IsDerivedFromParent();
		if ( fieldName == "eventType" )
			return _eventType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtComplexEvent", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C4B00)]
public class EvtComplexEvent : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtComplexEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtComplexEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EEventsCombineMove> _combineMode;
	private UndoRedoAssignableList<DBPtr<ImpulsiveEvent>> _events;

	public EEventsCombineMove combineMode { get { return _combineMode.Get(); } set { _combineMode.Set( value ); } }

	public libdb.IChangeableList<DBPtr<ImpulsiveEvent>> events { get { return _events; } set { _events.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtComplexEvent>(owner);
		_combineMode = new UndoRedo<EEventsCombineMove>( owner, EEventsCombineMove.AND );
		_events = new UndoRedoAssignableList<DBPtr<ImpulsiveEvent>>( owner );
		___parent.Changed += FireChangedEvent;
		_combineMode.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
	}

	public EvtComplexEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtComplexEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtComplexEvent" );
		combineMode = source.combineMode;
		events = source.events;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtComplexEvent source = _source as EvtComplexEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtComplexEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtComplexEvent newParent = rawParent == null ? null : rawParent.Get<EvtComplexEvent>();
		if ( newParent == null && _newParent is EvtComplexEvent )
			newParent = _newParent as EvtComplexEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_combineMode.SetParent( newParent == null ? null : newParent._combineMode );
		_events.SetParent( newParent == null ? null : newParent._events );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_combineMode.Reset();
		_events.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_combineMode.IsDerivedFromParent()
			&& _events.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "combineMode" )
			_combineMode.Reset();
		else if ( fieldName == "events" )
			_events.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "combineMode" )
			return _combineMode.IsDerivedFromParent();
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

[FactoryImpl("Create", "NWorld::EvtCondition", "PFImpulsiveEvents.h")]
[TypeId(0x4977E4C0)]
public class EvtCondition : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableBoolString _condition;

	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtCondition>(owner);
		ExecutableBoolString __condition = new ExecutableBoolString(); // Construct default object for condition
		__condition.sString = "true";
		_condition = new ExecutableBoolString( owner, __condition );
		___parent.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
	}

	public EvtCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtCondition" );
		condition = source.condition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtCondition source = _source as EvtCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtCondition newParent = rawParent == null ? null : rawParent.Get<EvtCondition>();
		if ( newParent == null && _newParent is EvtCondition )
			newParent = _newParent as EvtCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_condition.SetParent( newParent == null ? null : newParent._condition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_condition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_condition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "condition" )
			_condition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtDead", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C8440)]
public class EvtDead : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtDead> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtDead> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtDead>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public EvtDead()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtDead source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtDead" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtDead source = _source as EvtDead;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtDead" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtDead newParent = rawParent == null ? null : rawParent.Get<EvtDead>();
		if ( newParent == null && _newParent is EvtDead )
			newParent = _newParent as EvtDead;
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

[FactoryImpl("Create", "NWorld::EvtEnemyDanger", "PFImpulsiveEvents.h")]
[TypeId(0x0F664C02)]
public class EvtEnemyDanger : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtEnemyDanger> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtEnemyDanger> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _count;
	private UndoRedo<float> _distance;
	private UndoRedo<ESpellTarget> _unitTypes;
	private UndoRedo<bool> _treatNeutralAsHostile;

	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	public float distance { get { return _distance.Get(); } set { _distance.Set( value ); } }

	public ESpellTarget unitTypes { get { return _unitTypes.Get(); } set { _unitTypes.Set( value ); } }

	public bool treatNeutralAsHostile { get { return _treatNeutralAsHostile.Get(); } set { _treatNeutralAsHostile.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtEnemyDanger>(owner);
		_count = new UndoRedo<int>( owner, 1 );
		_distance = new UndoRedo<float>( owner, 150.0f );
		_unitTypes = new UndoRedo<ESpellTarget>( owner, ESpellTarget.HeroFemale | ESpellTarget.HeroMale );
		_treatNeutralAsHostile = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
		_unitTypes.Changed += FireChangedEvent;
		_treatNeutralAsHostile.Changed += FireChangedEvent;
	}

	public EvtEnemyDanger()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtEnemyDanger source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtEnemyDanger" );
		count = source.count;
		distance = source.distance;
		unitTypes = source.unitTypes;
		treatNeutralAsHostile = source.treatNeutralAsHostile;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtEnemyDanger source = _source as EvtEnemyDanger;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtEnemyDanger" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtEnemyDanger newParent = rawParent == null ? null : rawParent.Get<EvtEnemyDanger>();
		if ( newParent == null && _newParent is EvtEnemyDanger )
			newParent = _newParent as EvtEnemyDanger;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_count.SetParent( newParent == null ? null : newParent._count );
		_distance.SetParent( newParent == null ? null : newParent._distance );
		_unitTypes.SetParent( newParent == null ? null : newParent._unitTypes );
		_treatNeutralAsHostile.SetParent( newParent == null ? null : newParent._treatNeutralAsHostile );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_count.Reset();
		_distance.Reset();
		_unitTypes.Reset();
		_treatNeutralAsHostile.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_count.IsDerivedFromParent()
			&& _distance.IsDerivedFromParent()
			&& _unitTypes.IsDerivedFromParent()
			&& _treatNeutralAsHostile.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "count" )
			_count.Reset();
		else if ( fieldName == "distance" )
			_distance.Reset();
		else if ( fieldName == "unitTypes" )
			_unitTypes.Reset();
		else if ( fieldName == "treatNeutralAsHostile" )
			_treatNeutralAsHostile.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		if ( fieldName == "unitTypes" )
			return _unitTypes.IsDerivedFromParent();
		if ( fieldName == "treatNeutralAsHostile" )
			return _treatNeutralAsHostile.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtEnemyFlees", "PFImpulsiveEvents.h")]
[TypeId(0x2C72D3C1)]
public class EvtEnemyFlees : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtEnemyFlees> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtEnemyFlees> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _health;
	private UndoRedo<ECompareOperator> _operation;
	private UndoRedo<float> _fleeTime;
	private UndoRedo<float> _cowardDetectRange;
	private UndoRedo<float> _cowardChaseRange;

	[FloatMinMax(0, 100)]
	public float health { get { return _health.Get(); } set { _health.Set( value ); } }

	public ECompareOperator operation { get { return _operation.Get(); } set { _operation.Set( value ); } }

	public float fleeTime { get { return _fleeTime.Get(); } set { _fleeTime.Set( value ); } }

	public float cowardDetectRange { get { return _cowardDetectRange.Get(); } set { _cowardDetectRange.Set( value ); } }

	public float cowardChaseRange { get { return _cowardChaseRange.Get(); } set { _cowardChaseRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtEnemyFlees>(owner);
		_health = new UndoRedo<float>( owner, 10.0f );
		_operation = new UndoRedo<ECompareOperator>( owner, ECompareOperator.Less );
		_fleeTime = new UndoRedo<float>( owner, 10.0f );
		_cowardDetectRange = new UndoRedo<float>( owner, 20.0f );
		_cowardChaseRange = new UndoRedo<float>( owner, 20.0f );
		___parent.Changed += FireChangedEvent;
		_health.Changed += FireChangedEvent;
		_operation.Changed += FireChangedEvent;
		_fleeTime.Changed += FireChangedEvent;
		_cowardDetectRange.Changed += FireChangedEvent;
		_cowardChaseRange.Changed += FireChangedEvent;
	}

	public EvtEnemyFlees()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtEnemyFlees source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtEnemyFlees" );
		health = source.health;
		operation = source.operation;
		fleeTime = source.fleeTime;
		cowardDetectRange = source.cowardDetectRange;
		cowardChaseRange = source.cowardChaseRange;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtEnemyFlees source = _source as EvtEnemyFlees;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtEnemyFlees" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtEnemyFlees newParent = rawParent == null ? null : rawParent.Get<EvtEnemyFlees>();
		if ( newParent == null && _newParent is EvtEnemyFlees )
			newParent = _newParent as EvtEnemyFlees;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_health.SetParent( newParent == null ? null : newParent._health );
		_operation.SetParent( newParent == null ? null : newParent._operation );
		_fleeTime.SetParent( newParent == null ? null : newParent._fleeTime );
		_cowardDetectRange.SetParent( newParent == null ? null : newParent._cowardDetectRange );
		_cowardChaseRange.SetParent( newParent == null ? null : newParent._cowardChaseRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_health.Reset();
		_operation.Reset();
		_fleeTime.Reset();
		_cowardDetectRange.Reset();
		_cowardChaseRange.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_health.IsDerivedFromParent()
			&& _operation.IsDerivedFromParent()
			&& _fleeTime.IsDerivedFromParent()
			&& _cowardDetectRange.IsDerivedFromParent()
			&& _cowardChaseRange.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "health" )
			_health.Reset();
		else if ( fieldName == "operation" )
			_operation.Reset();
		else if ( fieldName == "fleeTime" )
			_fleeTime.Reset();
		else if ( fieldName == "cowardDetectRange" )
			_cowardDetectRange.Reset();
		else if ( fieldName == "cowardChaseRange" )
			_cowardChaseRange.Reset();
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
		if ( fieldName == "operation" )
			return _operation.IsDerivedFromParent();
		if ( fieldName == "fleeTime" )
			return _fleeTime.IsDerivedFromParent();
		if ( fieldName == "cowardDetectRange" )
			return _cowardDetectRange.IsDerivedFromParent();
		if ( fieldName == "cowardChaseRange" )
			return _cowardChaseRange.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtEnteringBattleLine", "PFImpulsiveEvents.h")]
[TypeId(0x2C72D3C0)]
public class EvtEnteringBattleLine : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtEnteringBattleLine> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtEnteringBattleLine> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _battleRange;
	private UndoRedo<int> _fightingAllies;
	private UndoRedo<float> _roadRange;

	[Description( "Distance from hero to battle" )]
	public float battleRange { get { return _battleRange.Get(); } set { _battleRange.Set( value ); } }

	[Description( "Minimum allies count to treat their fight as battle" )]
	public int fightingAllies { get { return _fightingAllies.Get(); } set { _fightingAllies.Set( value ); } }

	[Description( "Distance from road line to heroes to treat they are at road" )]
	public float roadRange { get { return _roadRange.Get(); } set { _roadRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtEnteringBattleLine>(owner);
		_battleRange = new UndoRedo<float>( owner, 100.0f );
		_fightingAllies = new UndoRedo<int>( owner, 1 );
		_roadRange = new UndoRedo<float>( owner, 15.0f );
		___parent.Changed += FireChangedEvent;
		_battleRange.Changed += FireChangedEvent;
		_fightingAllies.Changed += FireChangedEvent;
		_roadRange.Changed += FireChangedEvent;
	}

	public EvtEnteringBattleLine()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtEnteringBattleLine source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtEnteringBattleLine" );
		battleRange = source.battleRange;
		fightingAllies = source.fightingAllies;
		roadRange = source.roadRange;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtEnteringBattleLine source = _source as EvtEnteringBattleLine;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtEnteringBattleLine" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtEnteringBattleLine newParent = rawParent == null ? null : rawParent.Get<EvtEnteringBattleLine>();
		if ( newParent == null && _newParent is EvtEnteringBattleLine )
			newParent = _newParent as EvtEnteringBattleLine;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_battleRange.SetParent( newParent == null ? null : newParent._battleRange );
		_fightingAllies.SetParent( newParent == null ? null : newParent._fightingAllies );
		_roadRange.SetParent( newParent == null ? null : newParent._roadRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_battleRange.Reset();
		_fightingAllies.Reset();
		_roadRange.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_battleRange.IsDerivedFromParent()
			&& _fightingAllies.IsDerivedFromParent()
			&& _roadRange.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "battleRange" )
			_battleRange.Reset();
		else if ( fieldName == "fightingAllies" )
			_fightingAllies.Reset();
		else if ( fieldName == "roadRange" )
			_roadRange.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "battleRange" )
			return _battleRange.IsDerivedFromParent();
		if ( fieldName == "fightingAllies" )
			return _fightingAllies.IsDerivedFromParent();
		if ( fieldName == "roadRange" )
			return _roadRange.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtHeroTotalNaftaCondition", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C4C40)]
public class EvtHeroTotalNaftaCondition : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtHeroTotalNaftaCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtHeroTotalNaftaCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ELevelCheckType> _type;
	private UndoRedo<ECompareOperator> _operation;
	private UndoRedo<int> _totalNafta;

	public ELevelCheckType type { get { return _type.Get(); } set { _type.Set( value ); } }

	public ECompareOperator operation { get { return _operation.Get(); } set { _operation.Set( value ); } }

	public int totalNafta { get { return _totalNafta.Get(); } set { _totalNafta.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtHeroTotalNaftaCondition>(owner);
		_type = new UndoRedo<ELevelCheckType>( owner, ELevelCheckType.Exact );
		_operation = new UndoRedo<ECompareOperator>( owner, ECompareOperator.Equal );
		_totalNafta = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_operation.Changed += FireChangedEvent;
		_totalNafta.Changed += FireChangedEvent;
	}

	public EvtHeroTotalNaftaCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtHeroTotalNaftaCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtHeroTotalNaftaCondition" );
		type = source.type;
		operation = source.operation;
		totalNafta = source.totalNafta;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtHeroTotalNaftaCondition source = _source as EvtHeroTotalNaftaCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtHeroTotalNaftaCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtHeroTotalNaftaCondition newParent = rawParent == null ? null : rawParent.Get<EvtHeroTotalNaftaCondition>();
		if ( newParent == null && _newParent is EvtHeroTotalNaftaCondition )
			newParent = _newParent as EvtHeroTotalNaftaCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		_operation.SetParent( newParent == null ? null : newParent._operation );
		_totalNafta.SetParent( newParent == null ? null : newParent._totalNafta );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		_operation.Reset();
		_totalNafta.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _operation.IsDerivedFromParent()
			&& _totalNafta.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "operation" )
			_operation.Reset();
		else if ( fieldName == "totalNafta" )
			_totalNafta.Reset();
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
		if ( fieldName == "operation" )
			return _operation.IsDerivedFromParent();
		if ( fieldName == "totalNafta" )
			return _totalNafta.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtInMinigame", "PFImpulsiveEvents.h")]
[TypeId(0x2B78EBC0)]
public class EvtInMinigame : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtInMinigame> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtInMinigame> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtInMinigame>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public EvtInMinigame()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtInMinigame source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtInMinigame" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtInMinigame source = _source as EvtInMinigame;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtInMinigame" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtInMinigame newParent = rawParent == null ? null : rawParent.Get<EvtInMinigame>();
		if ( newParent == null && _newParent is EvtInMinigame )
			newParent = _newParent as EvtInMinigame;
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

[FactoryImpl("Create", "NWorld::EvtInverseEvent", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C4C00)]
public class EvtInverseEvent : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtInverseEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtInverseEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<ImpulsiveEvent> _evt;

	public DBPtr<ImpulsiveEvent> evt { get { return _evt.Get(); } set { _evt.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtInverseEvent>(owner);
		_evt = new UndoRedoDBPtr<ImpulsiveEvent>( owner );
		___parent.Changed += FireChangedEvent;
		_evt.Changed += FireChangedEvent;
	}

	public EvtInverseEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtInverseEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtInverseEvent" );
		evt = source.evt;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtInverseEvent source = _source as EvtInverseEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtInverseEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtInverseEvent newParent = rawParent == null ? null : rawParent.Get<EvtInverseEvent>();
		if ( newParent == null && _newParent is EvtInverseEvent )
			newParent = _newParent as EvtInverseEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_evt.SetParent( newParent == null ? null : newParent._evt );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_evt.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_evt.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "evt" )
			_evt.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "evt" )
			return _evt.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtMinEnergy", "PFImpulsiveEvents.h")]
[TypeId(0x0F664C01)]
public class EvtMinEnergy : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtMinEnergy> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtMinEnergy> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _minEnergy;

	public float minEnergy { get { return _minEnergy.Get(); } set { _minEnergy.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtMinEnergy>(owner);
		_minEnergy = new UndoRedo<float>( owner, 0.2f );
		___parent.Changed += FireChangedEvent;
		_minEnergy.Changed += FireChangedEvent;
	}

	public EvtMinEnergy()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtMinEnergy source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtMinEnergy" );
		minEnergy = source.minEnergy;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtMinEnergy source = _source as EvtMinEnergy;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtMinEnergy" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtMinEnergy newParent = rawParent == null ? null : rawParent.Get<EvtMinEnergy>();
		if ( newParent == null && _newParent is EvtMinEnergy )
			newParent = _newParent as EvtMinEnergy;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minEnergy.SetParent( newParent == null ? null : newParent._minEnergy );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minEnergy.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minEnergy.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minEnergy" )
			_minEnergy.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minEnergy" )
			return _minEnergy.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtMinHealth", "PFImpulsiveEvents.h")]
[TypeId(0x0F664C00)]
public class EvtMinHealth : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtMinHealth> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtMinHealth> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _minHealth;

	public float minHealth { get { return _minHealth.Get(); } set { _minHealth.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtMinHealth>(owner);
		_minHealth = new UndoRedo<float>( owner, 0.2f );
		___parent.Changed += FireChangedEvent;
		_minHealth.Changed += FireChangedEvent;
	}

	public EvtMinHealth()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtMinHealth source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtMinHealth" );
		minHealth = source.minHealth;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtMinHealth source = _source as EvtMinHealth;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtMinHealth" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtMinHealth newParent = rawParent == null ? null : rawParent.Get<EvtMinHealth>();
		if ( newParent == null && _newParent is EvtMinHealth )
			newParent = _newParent as EvtMinHealth;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minHealth.SetParent( newParent == null ? null : newParent._minHealth );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minHealth.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minHealth.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minHealth" )
			_minHealth.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minHealth" )
			return _minHealth.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtNegativeEffects", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C1C80)]
public class EvtNegativeEffects : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtNegativeEffects> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtNegativeEffects> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minTotalEffects;
	private UndoRedoAssignableList<NegativeEffectCondition> _priorityConditions;

	public int minTotalEffects { get { return _minTotalEffects.Get(); } set { _minTotalEffects.Set( value ); } }

	public libdb.IChangeableList<NegativeEffectCondition> priorityConditions { get { return _priorityConditions; } set { _priorityConditions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtNegativeEffects>(owner);
		_minTotalEffects = new UndoRedo<int>( owner, 1 );
		_priorityConditions = new UndoRedoAssignableList<NegativeEffectCondition>( owner );
		___parent.Changed += FireChangedEvent;
		_minTotalEffects.Changed += FireChangedEvent;
		_priorityConditions.Changed += FireChangedEvent;
	}

	public EvtNegativeEffects()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtNegativeEffects source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtNegativeEffects" );
		minTotalEffects = source.minTotalEffects;
		priorityConditions = source.priorityConditions;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtNegativeEffects source = _source as EvtNegativeEffects;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtNegativeEffects" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtNegativeEffects newParent = rawParent == null ? null : rawParent.Get<EvtNegativeEffects>();
		if ( newParent == null && _newParent is EvtNegativeEffects )
			newParent = _newParent as EvtNegativeEffects;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minTotalEffects.SetParent( newParent == null ? null : newParent._minTotalEffects );
		_priorityConditions.SetParent( newParent == null ? null : newParent._priorityConditions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minTotalEffects.Reset();
		_priorityConditions.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minTotalEffects.IsDerivedFromParent()
			&& _priorityConditions.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minTotalEffects" )
			_minTotalEffects.Reset();
		else if ( fieldName == "priorityConditions" )
			_priorityConditions.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minTotalEffects" )
			return _minTotalEffects.IsDerivedFromParent();
		if ( fieldName == "priorityConditions" )
			return _priorityConditions.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtPriestessGainMaxLevel", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C83C1)]
public class EvtPriestessGainMaxLevel : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtPriestessGainMaxLevel> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtPriestessGainMaxLevel> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtPriestessGainMaxLevel>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public EvtPriestessGainMaxLevel()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtPriestessGainMaxLevel source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtPriestessGainMaxLevel" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtPriestessGainMaxLevel source = _source as EvtPriestessGainMaxLevel;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtPriestessGainMaxLevel" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtPriestessGainMaxLevel newParent = rawParent == null ? null : rawParent.Get<EvtPriestessGainMaxLevel>();
		if ( newParent == null && _newParent is EvtPriestessGainMaxLevel )
			newParent = _newParent as EvtPriestessGainMaxLevel;
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

[FactoryImpl("Create", "NWorld::EvtSpellLowMana", "PFImpulsiveEvents.h")]
[TypeId(0x0F665B80)]
public class EvtSpellLowMana : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtSpellLowMana> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtSpellLowMana> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtSpellLowMana>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public EvtSpellLowMana()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtSpellLowMana source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtSpellLowMana" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtSpellLowMana source = _source as EvtSpellLowMana;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtSpellLowMana" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtSpellLowMana newParent = rawParent == null ? null : rawParent.Get<EvtSpellLowMana>();
		if ( newParent == null && _newParent is EvtSpellLowMana )
			newParent = _newParent as EvtSpellLowMana;
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

[FactoryImpl("Create", "NWorld::EvtTargetInRange", "PFImpulsiveEvents.h")]
[TypeId(0x2C6CAAC0)]
public class EvtTargetInRange : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtTargetInRange> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtTargetInRange> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _range;
	private UndoRedo<ERangeType> _rangeType;

	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	public ERangeType rangeType { get { return _rangeType.Get(); } set { _rangeType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtTargetInRange>(owner);
		_range = new UndoRedo<float>( owner, 0.0f );
		_rangeType = new UndoRedo<ERangeType>( owner, ERangeType.ExactValue );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_rangeType.Changed += FireChangedEvent;
	}

	public EvtTargetInRange()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtTargetInRange source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtTargetInRange" );
		range = source.range;
		rangeType = source.rangeType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtTargetInRange source = _source as EvtTargetInRange;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtTargetInRange" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtTargetInRange newParent = rawParent == null ? null : rawParent.Get<EvtTargetInRange>();
		if ( newParent == null && _newParent is EvtTargetInRange )
			newParent = _newParent as EvtTargetInRange;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_rangeType.SetParent( newParent == null ? null : newParent._rangeType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_rangeType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _rangeType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "rangeType" )
			_rangeType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "rangeType" )
			return _rangeType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtUnitsInRange", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C4BC0)]
public class EvtUnitsInRange : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtUnitsInRange> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtUnitsInRange> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _range;
	private UndoRedo<ERangeType> _rangeType;
	private UndoRedo<EFactionFlags> _factions;
	private UndoRedo<ESpellTarget> _unitTypes;
	private UndoRedo<int> _minCount;
	private UndoRedo<int> _maxCount;
	private UndoRedo<bool> _acceptSelf;
	private UndoRedo<string> _countingSet;

	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	public ERangeType rangeType { get { return _rangeType.Get(); } set { _rangeType.Set( value ); } }

	public EFactionFlags factions { get { return _factions.Get(); } set { _factions.Set( value ); } }

	public ESpellTarget unitTypes { get { return _unitTypes.Get(); } set { _unitTypes.Set( value ); } }

	public int minCount { get { return _minCount.Get(); } set { _minCount.Set( value ); } }

	public int maxCount { get { return _maxCount.Get(); } set { _maxCount.Set( value ); } }

	public bool acceptSelf { get { return _acceptSelf.Get(); } set { _acceptSelf.Set( value ); } }

	public string countingSet { get { return _countingSet.Get(); } set { _countingSet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtUnitsInRange>(owner);
		_range = new UndoRedo<float>( owner, 0.0f );
		_rangeType = new UndoRedo<ERangeType>( owner, ERangeType.ExactValue );
		_factions = new UndoRedo<EFactionFlags>( owner, (EFactionFlags)0 );
		_unitTypes = new UndoRedo<ESpellTarget>( owner, (ESpellTarget)0 );
		_minCount = new UndoRedo<int>( owner, 0 );
		_maxCount = new UndoRedo<int>( owner, 1000 );
		_acceptSelf = new UndoRedo<bool>( owner, true );
		_countingSet = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_rangeType.Changed += FireChangedEvent;
		_factions.Changed += FireChangedEvent;
		_unitTypes.Changed += FireChangedEvent;
		_minCount.Changed += FireChangedEvent;
		_maxCount.Changed += FireChangedEvent;
		_acceptSelf.Changed += FireChangedEvent;
		_countingSet.Changed += FireChangedEvent;
	}

	public EvtUnitsInRange()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtUnitsInRange source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtUnitsInRange" );
		range = source.range;
		rangeType = source.rangeType;
		factions = source.factions;
		unitTypes = source.unitTypes;
		minCount = source.minCount;
		maxCount = source.maxCount;
		acceptSelf = source.acceptSelf;
		countingSet = source.countingSet;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtUnitsInRange source = _source as EvtUnitsInRange;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtUnitsInRange" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtUnitsInRange newParent = rawParent == null ? null : rawParent.Get<EvtUnitsInRange>();
		if ( newParent == null && _newParent is EvtUnitsInRange )
			newParent = _newParent as EvtUnitsInRange;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_rangeType.SetParent( newParent == null ? null : newParent._rangeType );
		_factions.SetParent( newParent == null ? null : newParent._factions );
		_unitTypes.SetParent( newParent == null ? null : newParent._unitTypes );
		_minCount.SetParent( newParent == null ? null : newParent._minCount );
		_maxCount.SetParent( newParent == null ? null : newParent._maxCount );
		_acceptSelf.SetParent( newParent == null ? null : newParent._acceptSelf );
		_countingSet.SetParent( newParent == null ? null : newParent._countingSet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_rangeType.Reset();
		_factions.Reset();
		_unitTypes.Reset();
		_minCount.Reset();
		_maxCount.Reset();
		_acceptSelf.Reset();
		_countingSet.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _rangeType.IsDerivedFromParent()
			&& _factions.IsDerivedFromParent()
			&& _unitTypes.IsDerivedFromParent()
			&& _minCount.IsDerivedFromParent()
			&& _maxCount.IsDerivedFromParent()
			&& _acceptSelf.IsDerivedFromParent()
			&& _countingSet.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "rangeType" )
			_rangeType.Reset();
		else if ( fieldName == "factions" )
			_factions.Reset();
		else if ( fieldName == "unitTypes" )
			_unitTypes.Reset();
		else if ( fieldName == "minCount" )
			_minCount.Reset();
		else if ( fieldName == "maxCount" )
			_maxCount.Reset();
		else if ( fieldName == "acceptSelf" )
			_acceptSelf.Reset();
		else if ( fieldName == "countingSet" )
			_countingSet.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "rangeType" )
			return _rangeType.IsDerivedFromParent();
		if ( fieldName == "factions" )
			return _factions.IsDerivedFromParent();
		if ( fieldName == "unitTypes" )
			return _unitTypes.IsDerivedFromParent();
		if ( fieldName == "minCount" )
			return _minCount.IsDerivedFromParent();
		if ( fieldName == "maxCount" )
			return _maxCount.IsDerivedFromParent();
		if ( fieldName == "acceptSelf" )
			return _acceptSelf.IsDerivedFromParent();
		if ( fieldName == "countingSet" )
			return _countingSet.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtUnitsInRangeWithProperHealth", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C5C80)]
public class EvtUnitsInRangeWithProperHealth : EvtUnitsInRange
{
	private UndoRedoDBPtr<EvtUnitsInRangeWithProperHealth> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtUnitsInRangeWithProperHealth> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _health;
	private UndoRedo<ECompareOperator> _operation;

	public float health { get { return _health.Get(); } set { _health.Set( value ); } }

	public ECompareOperator operation { get { return _operation.Get(); } set { _operation.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtUnitsInRangeWithProperHealth>(owner);
		_health = new UndoRedo<float>( owner, 0.0f );
		_operation = new UndoRedo<ECompareOperator>( owner, ECompareOperator.Equal );
		___parent.Changed += FireChangedEvent;
		_health.Changed += FireChangedEvent;
		_operation.Changed += FireChangedEvent;
	}

	public EvtUnitsInRangeWithProperHealth()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtUnitsInRangeWithProperHealth source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtUnitsInRangeWithProperHealth" );
		health = source.health;
		operation = source.operation;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtUnitsInRangeWithProperHealth source = _source as EvtUnitsInRangeWithProperHealth;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtUnitsInRangeWithProperHealth" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtUnitsInRangeWithProperHealth newParent = rawParent == null ? null : rawParent.Get<EvtUnitsInRangeWithProperHealth>();
		if ( newParent == null && _newParent is EvtUnitsInRangeWithProperHealth )
			newParent = _newParent as EvtUnitsInRangeWithProperHealth;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_health.SetParent( newParent == null ? null : newParent._health );
		_operation.SetParent( newParent == null ? null : newParent._operation );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_health.Reset();
		_operation.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_health.IsDerivedFromParent()
			&& _operation.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "health" )
			_health.Reset();
		else if ( fieldName == "operation" )
			_operation.Reset();
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
		if ( fieldName == "operation" )
			return _operation.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtUsedImpulsiveBuff", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C5C40)]
public class EvtUsedImpulsiveBuff : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtUsedImpulsiveBuff> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtUsedImpulsiveBuff> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _buffIndex;
	private UndoRedo<bool> _usedByAlly;
	private UndoRedo<bool> _acceptSelf;
	private UndoRedo<float> _range;
	private UndoRedo<ERangeType> _rangeType;

	public int buffIndex { get { return _buffIndex.Get(); } set { _buffIndex.Set( value ); } }

	public bool usedByAlly { get { return _usedByAlly.Get(); } set { _usedByAlly.Set( value ); } }

	public bool acceptSelf { get { return _acceptSelf.Get(); } set { _acceptSelf.Set( value ); } }

	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	public ERangeType rangeType { get { return _rangeType.Get(); } set { _rangeType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtUsedImpulsiveBuff>(owner);
		_buffIndex = new UndoRedo<int>( owner, -1 );
		_usedByAlly = new UndoRedo<bool>( owner, false );
		_acceptSelf = new UndoRedo<bool>( owner, false );
		_range = new UndoRedo<float>( owner, 0.0f );
		_rangeType = new UndoRedo<ERangeType>( owner, ERangeType.ExactValue );
		___parent.Changed += FireChangedEvent;
		_buffIndex.Changed += FireChangedEvent;
		_usedByAlly.Changed += FireChangedEvent;
		_acceptSelf.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_rangeType.Changed += FireChangedEvent;
	}

	public EvtUsedImpulsiveBuff()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtUsedImpulsiveBuff source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtUsedImpulsiveBuff" );
		buffIndex = source.buffIndex;
		usedByAlly = source.usedByAlly;
		acceptSelf = source.acceptSelf;
		range = source.range;
		rangeType = source.rangeType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtUsedImpulsiveBuff source = _source as EvtUsedImpulsiveBuff;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtUsedImpulsiveBuff" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtUsedImpulsiveBuff newParent = rawParent == null ? null : rawParent.Get<EvtUsedImpulsiveBuff>();
		if ( newParent == null && _newParent is EvtUsedImpulsiveBuff )
			newParent = _newParent as EvtUsedImpulsiveBuff;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_buffIndex.SetParent( newParent == null ? null : newParent._buffIndex );
		_usedByAlly.SetParent( newParent == null ? null : newParent._usedByAlly );
		_acceptSelf.SetParent( newParent == null ? null : newParent._acceptSelf );
		_range.SetParent( newParent == null ? null : newParent._range );
		_rangeType.SetParent( newParent == null ? null : newParent._rangeType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_buffIndex.Reset();
		_usedByAlly.Reset();
		_acceptSelf.Reset();
		_range.Reset();
		_rangeType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_buffIndex.IsDerivedFromParent()
			&& _usedByAlly.IsDerivedFromParent()
			&& _acceptSelf.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _rangeType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "buffIndex" )
			_buffIndex.Reset();
		else if ( fieldName == "usedByAlly" )
			_usedByAlly.Reset();
		else if ( fieldName == "acceptSelf" )
			_acceptSelf.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "rangeType" )
			_rangeType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "buffIndex" )
			return _buffIndex.IsDerivedFromParent();
		if ( fieldName == "usedByAlly" )
			return _usedByAlly.IsDerivedFromParent();
		if ( fieldName == "acceptSelf" )
			return _acceptSelf.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "rangeType" )
			return _rangeType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[TypeId(0x0F664BC0)]
[UseTypeName("IBCN")]
public class ImpulsiveBuffsContainer : DBResource
{
	private UndoRedoDBPtr<ImpulsiveBuffsContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<ImpulsiveBuffsContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BuyServicesContainer> _servicesCosts;
	private UndoRedoAssignableList<ImpulsiveBuff> _buffs;
	private UndoRedoAssignableList<AccessCost> _accessLevelsCosts;
	private UndoRedo<float> _globalCooldown;
	private UndoRedo<float> _buffUseEventLifeTime;
	private UndoRedo<float> _priestessEventsLifeTime;
	private UndoRedoAssignableList<UnitCountingWeights> _unitCountingParams;

	[Description( "all services cost" )]
	public DBPtr<BuyServicesContainer> servicesCosts { get { return _servicesCosts.Get(); } set { _servicesCosts.Set( value ); } }

	[Description( "Heroes & Tower impulsive buffs" )]
	[EnumArray(typeof(ImpulseBuffs))]
	public libdb.IChangeableList<ImpulsiveBuff> buffs { get { return _buffs; } set { _buffs.Assign( value ); } }

	public libdb.IChangeableList<AccessCost> accessLevelsCosts { get { return _accessLevelsCosts; } set { _accessLevelsCosts.Assign( value ); } }

	public float globalCooldown { get { return _globalCooldown.Get(); } set { _globalCooldown.Set( value ); } }

	public float buffUseEventLifeTime { get { return _buffUseEventLifeTime.Get(); } set { _buffUseEventLifeTime.Set( value ); } }

	public float priestessEventsLifeTime { get { return _priestessEventsLifeTime.Get(); } set { _priestessEventsLifeTime.Set( value ); } }

	public libdb.IChangeableList<UnitCountingWeights> unitCountingParams { get { return _unitCountingParams; } set { _unitCountingParams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ImpulsiveBuffsContainer>(owner);
		_servicesCosts = new UndoRedoDBPtr<BuyServicesContainer>( owner );
		_buffs = new UndoRedoAssignableList<ImpulsiveBuff>( owner, typeof( ImpulseBuffs ) );
		_accessLevelsCosts = new UndoRedoAssignableList<AccessCost>( owner );
		_globalCooldown = new UndoRedo<float>( owner, 0.0f );
		_buffUseEventLifeTime = new UndoRedo<float>( owner, 15.0f );
		_priestessEventsLifeTime = new UndoRedo<float>( owner, 15.0f );
		_unitCountingParams = new UndoRedoAssignableList<UnitCountingWeights>( owner );
		___parent.Changed += FireChangedEvent;
		_servicesCosts.Changed += FireChangedEvent;
		_buffs.Changed += FireChangedEvent;
		_accessLevelsCosts.Changed += FireChangedEvent;
		_globalCooldown.Changed += FireChangedEvent;
		_buffUseEventLifeTime.Changed += FireChangedEvent;
		_priestessEventsLifeTime.Changed += FireChangedEvent;
		_unitCountingParams.Changed += FireChangedEvent;
	}

	public ImpulsiveBuffsContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( ImpulsiveBuffsContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveBuffsContainer" );
		servicesCosts = source.servicesCosts;
		buffs = source.buffs;
		accessLevelsCosts = source.accessLevelsCosts;
		globalCooldown = source.globalCooldown;
		buffUseEventLifeTime = source.buffUseEventLifeTime;
		priestessEventsLifeTime = source.priestessEventsLifeTime;
		unitCountingParams = source.unitCountingParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ImpulsiveBuffsContainer source = _source as ImpulsiveBuffsContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveBuffsContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ImpulsiveBuffsContainer newParent = rawParent == null ? null : rawParent.Get<ImpulsiveBuffsContainer>();
		if ( newParent == null && _newParent is ImpulsiveBuffsContainer )
			newParent = _newParent as ImpulsiveBuffsContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_servicesCosts.SetParent( newParent == null ? null : newParent._servicesCosts );
		_buffs.SetParent( newParent == null ? null : newParent._buffs );
		_accessLevelsCosts.SetParent( newParent == null ? null : newParent._accessLevelsCosts );
		_globalCooldown.SetParent( newParent == null ? null : newParent._globalCooldown );
		_buffUseEventLifeTime.SetParent( newParent == null ? null : newParent._buffUseEventLifeTime );
		_priestessEventsLifeTime.SetParent( newParent == null ? null : newParent._priestessEventsLifeTime );
		_unitCountingParams.SetParent( newParent == null ? null : newParent._unitCountingParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_servicesCosts.Reset();
		_buffs.Reset();
		_accessLevelsCosts.Reset();
		_globalCooldown.Reset();
		_buffUseEventLifeTime.Reset();
		_priestessEventsLifeTime.Reset();
		_unitCountingParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_servicesCosts.IsDerivedFromParent()
			&& _buffs.IsDerivedFromParent()
			&& _accessLevelsCosts.IsDerivedFromParent()
			&& _globalCooldown.IsDerivedFromParent()
			&& _buffUseEventLifeTime.IsDerivedFromParent()
			&& _priestessEventsLifeTime.IsDerivedFromParent()
			&& _unitCountingParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "servicesCosts" )
			_servicesCosts.Reset();
		else if ( fieldName == "buffs" )
			_buffs.Reset();
		else if ( fieldName == "accessLevelsCosts" )
			_accessLevelsCosts.Reset();
		else if ( fieldName == "globalCooldown" )
			_globalCooldown.Reset();
		else if ( fieldName == "buffUseEventLifeTime" )
			_buffUseEventLifeTime.Reset();
		else if ( fieldName == "priestessEventsLifeTime" )
			_priestessEventsLifeTime.Reset();
		else if ( fieldName == "unitCountingParams" )
			_unitCountingParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "servicesCosts" )
			return _servicesCosts.IsDerivedFromParent();
		if ( fieldName == "buffs" )
			return _buffs.IsDerivedFromParent();
		if ( fieldName == "accessLevelsCosts" )
			return _accessLevelsCosts.IsDerivedFromParent();
		if ( fieldName == "globalCooldown" )
			return _globalCooldown.IsDerivedFromParent();
		if ( fieldName == "buffUseEventLifeTime" )
			return _buffUseEventLifeTime.IsDerivedFromParent();
		if ( fieldName == "priestessEventsLifeTime" )
			return _priestessEventsLifeTime.IsDerivedFromParent();
		if ( fieldName == "unitCountingParams" )
			return _unitCountingParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::EvtAttackedByUnits", "PFImpulsiveEvents.h")]
[TypeId(0x2C6C5381)]
public class EvtAttackedByUnits : ImpulsiveEvent
{
	private UndoRedoDBPtr<EvtAttackedByUnits> ___parent;
	[HideInOutliner]
	public new DBPtr<EvtAttackedByUnits> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _range;
	private UndoRedo<ERangeType> _rangeType;
	private UndoRedo<EFactionFlags> _attackedFactions;
	private UndoRedo<ESpellTarget> _attackedTypes;
	private UndoRedo<bool> _attackedAcceptSelf;
	private UndoRedo<EFactionFlags> _attackersFactions;
	private UndoRedo<ESpellTarget> _attackersTypes;
	private UndoRedo<bool> _attackersAcceptSelf;
	private UndoRedo<int> _minAttackersCount;
	private UndoRedo<int> _maxAttackersCount;
	private UndoRedo<bool> _suggestVictim;
	private UndoRedo<string> _countingSet;

	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	public ERangeType rangeType { get { return _rangeType.Get(); } set { _rangeType.Set( value ); } }

	public EFactionFlags attackedFactions { get { return _attackedFactions.Get(); } set { _attackedFactions.Set( value ); } }

	public ESpellTarget attackedTypes { get { return _attackedTypes.Get(); } set { _attackedTypes.Set( value ); } }

	public bool attackedAcceptSelf { get { return _attackedAcceptSelf.Get(); } set { _attackedAcceptSelf.Set( value ); } }

	public EFactionFlags attackersFactions { get { return _attackersFactions.Get(); } set { _attackersFactions.Set( value ); } }

	public ESpellTarget attackersTypes { get { return _attackersTypes.Get(); } set { _attackersTypes.Set( value ); } }

	public bool attackersAcceptSelf { get { return _attackersAcceptSelf.Get(); } set { _attackersAcceptSelf.Set( value ); } }

	public int minAttackersCount { get { return _minAttackersCount.Get(); } set { _minAttackersCount.Set( value ); } }

	public int maxAttackersCount { get { return _maxAttackersCount.Get(); } set { _maxAttackersCount.Set( value ); } }

	public bool suggestVictim { get { return _suggestVictim.Get(); } set { _suggestVictim.Set( value ); } }

	public string countingSet { get { return _countingSet.Get(); } set { _countingSet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EvtAttackedByUnits>(owner);
		_range = new UndoRedo<float>( owner, 0.0f );
		_rangeType = new UndoRedo<ERangeType>( owner, ERangeType.ExactValue );
		_attackedFactions = new UndoRedo<EFactionFlags>( owner, (EFactionFlags)0 );
		_attackedTypes = new UndoRedo<ESpellTarget>( owner, (ESpellTarget)0 );
		_attackedAcceptSelf = new UndoRedo<bool>( owner, true );
		_attackersFactions = new UndoRedo<EFactionFlags>( owner, (EFactionFlags)0 );
		_attackersTypes = new UndoRedo<ESpellTarget>( owner, (ESpellTarget)0 );
		_attackersAcceptSelf = new UndoRedo<bool>( owner, true );
		_minAttackersCount = new UndoRedo<int>( owner, 0 );
		_maxAttackersCount = new UndoRedo<int>( owner, 1000 );
		_suggestVictim = new UndoRedo<bool>( owner, true );
		_countingSet = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_rangeType.Changed += FireChangedEvent;
		_attackedFactions.Changed += FireChangedEvent;
		_attackedTypes.Changed += FireChangedEvent;
		_attackedAcceptSelf.Changed += FireChangedEvent;
		_attackersFactions.Changed += FireChangedEvent;
		_attackersTypes.Changed += FireChangedEvent;
		_attackersAcceptSelf.Changed += FireChangedEvent;
		_minAttackersCount.Changed += FireChangedEvent;
		_maxAttackersCount.Changed += FireChangedEvent;
		_suggestVictim.Changed += FireChangedEvent;
		_countingSet.Changed += FireChangedEvent;
	}

	public EvtAttackedByUnits()
	{
		Initialize( this );
	}
	private void AssignSelf( EvtAttackedByUnits source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EvtAttackedByUnits" );
		range = source.range;
		rangeType = source.rangeType;
		attackedFactions = source.attackedFactions;
		attackedTypes = source.attackedTypes;
		attackedAcceptSelf = source.attackedAcceptSelf;
		attackersFactions = source.attackersFactions;
		attackersTypes = source.attackersTypes;
		attackersAcceptSelf = source.attackersAcceptSelf;
		minAttackersCount = source.minAttackersCount;
		maxAttackersCount = source.maxAttackersCount;
		suggestVictim = source.suggestVictim;
		countingSet = source.countingSet;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EvtAttackedByUnits source = _source as EvtAttackedByUnits;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EvtAttackedByUnits" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EvtAttackedByUnits newParent = rawParent == null ? null : rawParent.Get<EvtAttackedByUnits>();
		if ( newParent == null && _newParent is EvtAttackedByUnits )
			newParent = _newParent as EvtAttackedByUnits;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_rangeType.SetParent( newParent == null ? null : newParent._rangeType );
		_attackedFactions.SetParent( newParent == null ? null : newParent._attackedFactions );
		_attackedTypes.SetParent( newParent == null ? null : newParent._attackedTypes );
		_attackedAcceptSelf.SetParent( newParent == null ? null : newParent._attackedAcceptSelf );
		_attackersFactions.SetParent( newParent == null ? null : newParent._attackersFactions );
		_attackersTypes.SetParent( newParent == null ? null : newParent._attackersTypes );
		_attackersAcceptSelf.SetParent( newParent == null ? null : newParent._attackersAcceptSelf );
		_minAttackersCount.SetParent( newParent == null ? null : newParent._minAttackersCount );
		_maxAttackersCount.SetParent( newParent == null ? null : newParent._maxAttackersCount );
		_suggestVictim.SetParent( newParent == null ? null : newParent._suggestVictim );
		_countingSet.SetParent( newParent == null ? null : newParent._countingSet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_rangeType.Reset();
		_attackedFactions.Reset();
		_attackedTypes.Reset();
		_attackedAcceptSelf.Reset();
		_attackersFactions.Reset();
		_attackersTypes.Reset();
		_attackersAcceptSelf.Reset();
		_minAttackersCount.Reset();
		_maxAttackersCount.Reset();
		_suggestVictim.Reset();
		_countingSet.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _rangeType.IsDerivedFromParent()
			&& _attackedFactions.IsDerivedFromParent()
			&& _attackedTypes.IsDerivedFromParent()
			&& _attackedAcceptSelf.IsDerivedFromParent()
			&& _attackersFactions.IsDerivedFromParent()
			&& _attackersTypes.IsDerivedFromParent()
			&& _attackersAcceptSelf.IsDerivedFromParent()
			&& _minAttackersCount.IsDerivedFromParent()
			&& _maxAttackersCount.IsDerivedFromParent()
			&& _suggestVictim.IsDerivedFromParent()
			&& _countingSet.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "rangeType" )
			_rangeType.Reset();
		else if ( fieldName == "attackedFactions" )
			_attackedFactions.Reset();
		else if ( fieldName == "attackedTypes" )
			_attackedTypes.Reset();
		else if ( fieldName == "attackedAcceptSelf" )
			_attackedAcceptSelf.Reset();
		else if ( fieldName == "attackersFactions" )
			_attackersFactions.Reset();
		else if ( fieldName == "attackersTypes" )
			_attackersTypes.Reset();
		else if ( fieldName == "attackersAcceptSelf" )
			_attackersAcceptSelf.Reset();
		else if ( fieldName == "minAttackersCount" )
			_minAttackersCount.Reset();
		else if ( fieldName == "maxAttackersCount" )
			_maxAttackersCount.Reset();
		else if ( fieldName == "suggestVictim" )
			_suggestVictim.Reset();
		else if ( fieldName == "countingSet" )
			_countingSet.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "rangeType" )
			return _rangeType.IsDerivedFromParent();
		if ( fieldName == "attackedFactions" )
			return _attackedFactions.IsDerivedFromParent();
		if ( fieldName == "attackedTypes" )
			return _attackedTypes.IsDerivedFromParent();
		if ( fieldName == "attackedAcceptSelf" )
			return _attackedAcceptSelf.IsDerivedFromParent();
		if ( fieldName == "attackersFactions" )
			return _attackersFactions.IsDerivedFromParent();
		if ( fieldName == "attackersTypes" )
			return _attackersTypes.IsDerivedFromParent();
		if ( fieldName == "attackersAcceptSelf" )
			return _attackersAcceptSelf.IsDerivedFromParent();
		if ( fieldName == "minAttackersCount" )
			return _minAttackersCount.IsDerivedFromParent();
		if ( fieldName == "maxAttackersCount" )
			return _maxAttackersCount.IsDerivedFromParent();
		if ( fieldName == "suggestVictim" )
			return _suggestVictim.IsDerivedFromParent();
		if ( fieldName == "countingSet" )
			return _countingSet.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
