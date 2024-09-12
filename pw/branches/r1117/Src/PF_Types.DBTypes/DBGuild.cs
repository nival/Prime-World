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
[Flags]
public enum EBuildingProductionCycle
{
	First = 1,
	Second = 2,
	Third = 4,
	Fourth = 8,
	All = 15,
};

[Custom("DBServer", "Social")]
[Flags]
public enum EGameType
{
	PvP = 1,
	CTE = 2,
	PvE = 4,
	MidOnly = 8,
	All = 15,
};

[Custom("DBServer", "Social")]
[Flags]
public enum ESessionType
{
	UsualBattle = 1,
	GuildBattle = 2,
	All = 3,
};

[Custom("DBServer", "Social")]
public enum EStatBufToggle
{
	AtGameStart = 1,
	By36Level = 2,
};

[Custom("DBServer", "Social")]
public class GameProps : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GameProps __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<AdvMapDescription>> _maps;
	private UndoRedo<ESessionType> _sessionType;

	[Custom("DBServer", "Social")]
	[Description( "Список карт и режимов игры" )]
	public libdb.IChangeableList<DBPtr<AdvMapDescription>> maps { get { return _maps; } set { _maps.Assign( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_maps = new UndoRedoAssignableList<DBPtr<AdvMapDescription>>( owner );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		_maps.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public GameProps()
	{
		Initialize( GetOwner() );
	}

	public GameProps( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GameProps( DBResource owner, GameProps source )
		: this(owner, source, true){}

	protected GameProps( DBResource owner, GameProps source, bool fireEvent )
	{
		_maps = new UndoRedoAssignableList<DBPtr<AdvMapDescription>>( owner );
		_maps.Assign( source.maps );
		_sessionType = new UndoRedo<ESessionType>( owner, source.sessionType );
		_maps.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GameProps source = _source as GameProps;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GameProps" );
		maps = source.maps;
		sessionType = source.sessionType;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GameProps newParent = _newParent as GameProps;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maps.SetParent( newParent == null ? null : newParent._maps );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maps.Reset();
		_sessionType.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maps.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maps" )
			_maps.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maps" )
			return _maps.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
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

[Custom("DBServer", "Social")]
public class ValueProps : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ValueProps __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _additiveValue;
	private UndoRedo<float> _multiplicativeValue;

	[Description( "Значение, которое прибавляется (чтобы было +2 надо сюда вписать 2)" )]
	public float additiveValue { get { return _additiveValue.Get(); } set { _additiveValue.Set( value ); } }

	[Description( "Процентное значение, которое прибавляется (чтобы прибавить 15%, надо сюда вписать 0.15" )]
	public float multiplicativeValue { get { return _multiplicativeValue.Get(); } set { _multiplicativeValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_additiveValue = new UndoRedo<float>( owner, 0.0f );
		_multiplicativeValue = new UndoRedo<float>( owner, 0.0f );
		_additiveValue.Changed += FireChangedEvent;
		_multiplicativeValue.Changed += FireChangedEvent;
	}

	public ValueProps()
	{
		Initialize( GetOwner() );
	}

	public ValueProps( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ValueProps( DBResource owner, ValueProps source )
		: this(owner, source, true){}

	protected ValueProps( DBResource owner, ValueProps source, bool fireEvent )
	{
		_additiveValue = new UndoRedo<float>( owner, source.additiveValue );
		_multiplicativeValue = new UndoRedo<float>( owner, source.multiplicativeValue );
		_additiveValue.Changed += FireChangedEvent;
		_multiplicativeValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ValueProps source = _source as ValueProps;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ValueProps" );
		additiveValue = source.additiveValue;
		multiplicativeValue = source.multiplicativeValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ValueProps newParent = _newParent as ValueProps;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_additiveValue.SetParent( newParent == null ? null : newParent._additiveValue );
		_multiplicativeValue.SetParent( newParent == null ? null : newParent._multiplicativeValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_additiveValue.Reset();
		_multiplicativeValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_additiveValue.IsDerivedFromParent()
			&& _multiplicativeValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "additiveValue" )
			_additiveValue.Reset();
		else if ( fieldName == "multiplicativeValue" )
			_multiplicativeValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "additiveValue" )
			return _additiveValue.IsDerivedFromParent();
		if ( fieldName == "multiplicativeValue" )
			return _multiplicativeValue.IsDerivedFromParent();
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

[Custom("DBServer", "Social")]
public class StatBonus : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatBonus __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EStat> _statType;
	private ValueProps _modifiers;

	[Description( "Увеличиваемый стат (Will, Strength..)" )]
	public EStat statType { get { return _statType.Get(); } set { _statType.Set( value ); } }

	public ValueProps modifiers { get { return _modifiers; } set { _modifiers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_statType = new UndoRedo<EStat>( owner, EStat.Life );
		_modifiers = new ValueProps( owner );
		_statType.Changed += FireChangedEvent;
		_modifiers.Changed += FireChangedEvent;
	}

	public StatBonus()
	{
		Initialize( GetOwner() );
	}

	public StatBonus( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatBonus( DBResource owner, StatBonus source )
		: this(owner, source, true){}

	protected StatBonus( DBResource owner, StatBonus source, bool fireEvent )
	{
		_statType = new UndoRedo<EStat>( owner, source.statType );
		_modifiers = new ValueProps( owner, source.modifiers );
		_statType.Changed += FireChangedEvent;
		_modifiers.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatBonus source = _source as StatBonus;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatBonus" );
		statType = source.statType;
		modifiers = source.modifiers;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatBonus newParent = _newParent as StatBonus;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_statType.SetParent( newParent == null ? null : newParent._statType );
		_modifiers.SetParent( newParent == null ? null : newParent._modifiers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statType.Reset();
		_modifiers.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statType.IsDerivedFromParent()
			&& _modifiers.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statType" )
			_statType.Reset();
		else if ( fieldName == "modifiers" )
			_modifiers.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "statType" )
			return _statType.IsDerivedFromParent();
		if ( fieldName == "modifiers" )
			return _modifiers.IsDerivedFromParent();
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

[Custom("DBServer", "Social")]
[NonTerminal]
public class GuildShopItemBonus : DBResource
{
	private UndoRedoDBPtr<GuildShopItemBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildShopItemBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _propertyTooltip;

	[Description( "Тултип для баффа" )]
	public TextRef propertyTooltip { get { return _propertyTooltip; } set { _propertyTooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildShopItemBonus>(owner);
		_propertyTooltip = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_propertyTooltip.Changed += FireChangedEvent;
	}

	public GuildShopItemBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildShopItemBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItemBonus" );
		propertyTooltip = source.propertyTooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildShopItemBonus source = _source as GuildShopItemBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItemBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildShopItemBonus newParent = rawParent == null ? null : rawParent.Get<GuildShopItemBonus>();
		if ( newParent == null && _newParent is GuildShopItemBonus )
			newParent = _newParent as GuildShopItemBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_propertyTooltip.SetParent( newParent == null ? null : newParent._propertyTooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_propertyTooltip.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_propertyTooltip.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "propertyTooltip" )
			_propertyTooltip.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "propertyTooltip" )
			return _propertyTooltip.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class GuildBuff : DBResource
{
	private UndoRedoDBPtr<GuildBuff> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBuff> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedoAssignableList<DBPtr<GuildBuff>> _doNotWorkWith;
	private UndoRedo<bool> _isGuildBonus;
	private UndoRedo<int> _priority;
	private UndoRedo<int> _duration;
	private UndoRedo<int> _numGames;
	private TextRef _propertyTooltip;
	private UndoRedoAssignableList<DBPtr<GuildShopItemBonus>> _bonuses;

	[Description( "ID бафа" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "Список расходников, с которыми одновременно не работает" )]
	public libdb.IChangeableList<DBPtr<GuildBuff>> doNotWorkWith { get { return _doNotWorkWith; } set { _doNotWorkWith.Assign( value ); } }

	[Description( "Если true, то по выходу из клана бонус у игрока пропадает" )]
	public bool isGuildBonus { get { return _isGuildBonus.Get(); } set { _isGuildBonus.Set( value ); } }

	[Description( "Приоритет для списка расходников (вес эффекта) - какой из них остается работать" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "Длительность" )]
	public int duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "Количество игр, в течение которых активен баф" )]
	public int numGames { get { return _numGames.Get(); } set { _numGames.Set( value ); } }

	[Description( "Тултип для свойства - тот что будет показываться не в магазине, а при наведении на иконку баффа" )]
	public TextRef propertyTooltip { get { return _propertyTooltip; } set { _propertyTooltip.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<GuildShopItemBonus>> bonuses { get { return _bonuses; } set { _bonuses.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBuff>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_doNotWorkWith = new UndoRedoAssignableList<DBPtr<GuildBuff>>( owner );
		_isGuildBonus = new UndoRedo<bool>( owner, false );
		_priority = new UndoRedo<int>( owner, 0 );
		_duration = new UndoRedo<int>( owner, 0 );
		_numGames = new UndoRedo<int>( owner, 0 );
		_propertyTooltip = new TextRef( owner, new TextRef() );
		_bonuses = new UndoRedoAssignableList<DBPtr<GuildShopItemBonus>>( owner );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_doNotWorkWith.Changed += FireChangedEvent;
		_isGuildBonus.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_numGames.Changed += FireChangedEvent;
		_propertyTooltip.Changed += FireChangedEvent;
		_bonuses.Changed += FireChangedEvent;
	}

	public GuildBuff()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBuff source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBuff" );
		persistentId = source.persistentId;
		doNotWorkWith = source.doNotWorkWith;
		isGuildBonus = source.isGuildBonus;
		priority = source.priority;
		duration = source.duration;
		numGames = source.numGames;
		propertyTooltip = source.propertyTooltip;
		bonuses = source.bonuses;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBuff source = _source as GuildBuff;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBuff" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBuff newParent = rawParent == null ? null : rawParent.Get<GuildBuff>();
		if ( newParent == null && _newParent is GuildBuff )
			newParent = _newParent as GuildBuff;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_doNotWorkWith.SetParent( newParent == null ? null : newParent._doNotWorkWith );
		_isGuildBonus.SetParent( newParent == null ? null : newParent._isGuildBonus );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_numGames.SetParent( newParent == null ? null : newParent._numGames );
		_propertyTooltip.SetParent( newParent == null ? null : newParent._propertyTooltip );
		_bonuses.SetParent( newParent == null ? null : newParent._bonuses );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_doNotWorkWith.Reset();
		_isGuildBonus.Reset();
		_priority.Reset();
		_duration.Reset();
		_numGames.Reset();
		_propertyTooltip.Reset();
		_bonuses.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _doNotWorkWith.IsDerivedFromParent()
			&& _isGuildBonus.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _numGames.IsDerivedFromParent()
			&& _propertyTooltip.IsDerivedFromParent()
			&& _bonuses.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "doNotWorkWith" )
			_doNotWorkWith.Reset();
		else if ( fieldName == "isGuildBonus" )
			_isGuildBonus.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "numGames" )
			_numGames.Reset();
		else if ( fieldName == "propertyTooltip" )
			_propertyTooltip.Reset();
		else if ( fieldName == "bonuses" )
			_bonuses.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "doNotWorkWith" )
			return _doNotWorkWith.IsDerivedFromParent();
		if ( fieldName == "isGuildBonus" )
			return _isGuildBonus.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "numGames" )
			return _numGames.IsDerivedFromParent();
		if ( fieldName == "propertyTooltip" )
			return _propertyTooltip.IsDerivedFromParent();
		if ( fieldName == "bonuses" )
			return _bonuses.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("GUILDBUFFS")]
public class GuildBuffsCollection : DBResource
{
	private UndoRedoDBPtr<GuildBuffsCollection> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBuffsCollection> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<GuildBuff>> _buffs;

	public libdb.IChangeableList<DBPtr<GuildBuff>> buffs { get { return _buffs; } set { _buffs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBuffsCollection>(owner);
		_buffs = new UndoRedoAssignableList<DBPtr<GuildBuff>>( owner );
		___parent.Changed += FireChangedEvent;
		_buffs.Changed += FireChangedEvent;
	}

	public GuildBuffsCollection()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBuffsCollection source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBuffsCollection" );
		buffs = source.buffs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBuffsCollection source = _source as GuildBuffsCollection;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBuffsCollection" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBuffsCollection newParent = rawParent == null ? null : rawParent.Get<GuildBuffsCollection>();
		if ( newParent == null && _newParent is GuildBuffsCollection )
			newParent = _newParent as GuildBuffsCollection;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_buffs.SetParent( newParent == null ? null : newParent._buffs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_buffs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_buffs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "buffs" )
			_buffs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "buffs" )
			return _buffs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class HeroBonusBase : GuildShopItemBonus
{
	private UndoRedoDBPtr<HeroBonusBase> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroBonusBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Hero>> _heroes;

	public libdb.IChangeableList<DBPtr<Hero>> heroes { get { return _heroes; } set { _heroes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroBonusBase>(owner);
		_heroes = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		___parent.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
	}

	public HeroBonusBase()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroBonusBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroBonusBase" );
		heroes = source.heroes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroBonusBase source = _source as HeroBonusBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroBonusBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroBonusBase newParent = rawParent == null ? null : rawParent.Get<HeroBonusBase>();
		if ( newParent == null && _newParent is HeroBonusBase )
			newParent = _newParent as HeroBonusBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroes.SetParent( newParent == null ? null : newParent._heroes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroes" )
			_heroes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroes" )
			return _heroes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class SessionBonus : HeroBonusBase
{
	private UndoRedoDBPtr<SessionBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private GameProps _gameSettings;

	public GameProps gameSettings { get { return _gameSettings; } set { _gameSettings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionBonus>(owner);
		_gameSettings = new GameProps( owner );
		___parent.Changed += FireChangedEvent;
		_gameSettings.Changed += FireChangedEvent;
	}

	public SessionBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionBonus" );
		gameSettings = source.gameSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionBonus source = _source as SessionBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionBonus newParent = rawParent == null ? null : rawParent.Get<SessionBonus>();
		if ( newParent == null && _newParent is SessionBonus )
			newParent = _newParent as SessionBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_gameSettings.SetParent( newParent == null ? null : newParent._gameSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_gameSettings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_gameSettings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "gameSettings" )
			_gameSettings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "gameSettings" )
			return _gameSettings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class SessionValueBonus : SessionBonus
{
	private UndoRedoDBPtr<SessionValueBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionValueBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ValueProps _modifiers;

	public ValueProps modifiers { get { return _modifiers; } set { _modifiers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionValueBonus>(owner);
		_modifiers = new ValueProps( owner );
		___parent.Changed += FireChangedEvent;
		_modifiers.Changed += FireChangedEvent;
	}

	public SessionValueBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionValueBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionValueBonus" );
		modifiers = source.modifiers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionValueBonus source = _source as SessionValueBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionValueBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionValueBonus newParent = rawParent == null ? null : rawParent.Get<SessionValueBonus>();
		if ( newParent == null && _newParent is SessionValueBonus )
			newParent = _newParent as SessionValueBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_modifiers.SetParent( newParent == null ? null : newParent._modifiers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_modifiers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_modifiers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "modifiers" )
			_modifiers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "modifiers" )
			return _modifiers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class HeroEnergyBonus : SessionValueBonus
{
	private UndoRedoDBPtr<HeroEnergyBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroEnergyBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroEnergyBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public HeroEnergyBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroEnergyBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroEnergyBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroEnergyBonus source = _source as HeroEnergyBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroEnergyBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroEnergyBonus newParent = rawParent == null ? null : rawParent.Get<HeroEnergyBonus>();
		if ( newParent == null && _newParent is HeroEnergyBonus )
			newParent = _newParent as HeroEnergyBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class HeroExperienceBonus : SessionValueBonus
{
	private UndoRedoDBPtr<HeroExperienceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroExperienceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroExperienceBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public HeroExperienceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroExperienceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroExperienceBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroExperienceBonus source = _source as HeroExperienceBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroExperienceBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroExperienceBonus newParent = rawParent == null ? null : rawParent.Get<HeroExperienceBonus>();
		if ( newParent == null && _newParent is HeroExperienceBonus )
			newParent = _newParent as HeroExperienceBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[NoCode]
public class PlayerPointsBonus : SessionValueBonus
{
	private UndoRedoDBPtr<PlayerPointsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<PlayerPointsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PlayerPointsBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public PlayerPointsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( PlayerPointsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PlayerPointsBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PlayerPointsBonus source = _source as PlayerPointsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PlayerPointsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PlayerPointsBonus newParent = rawParent == null ? null : rawParent.Get<PlayerPointsBonus>();
		if ( newParent == null && _newParent is PlayerPointsBonus )
			newParent = _newParent as PlayerPointsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class GuildWarEventPass : SessionBonus
{
	private UndoRedoDBPtr<GuildWarEventPass> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildWarEventPass> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildWarEventPass>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public GuildWarEventPass()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildWarEventPass source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildWarEventPass" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildWarEventPass source = _source as GuildWarEventPass;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildWarEventPass" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildWarEventPass newParent = rawParent == null ? null : rawParent.Get<GuildWarEventPass>();
		if ( newParent == null && _newParent is GuildWarEventPass )
			newParent = _newParent as GuildWarEventPass;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class SessionResourceBonus : SessionValueBonus
{
	private UndoRedoDBPtr<SessionResourceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionResourceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EResourceType> _resource;

	public EResourceType resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionResourceBonus>(owner);
		_resource = new UndoRedo<EResourceType>( owner, EResourceType.Silver );
		___parent.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
	}

	public SessionResourceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionResourceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionResourceBonus" );
		resource = source.resource;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionResourceBonus source = _source as SessionResourceBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionResourceBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionResourceBonus newParent = rawParent == null ? null : rawParent.Get<SessionResourceBonus>();
		if ( newParent == null && _newParent is SessionResourceBonus )
			newParent = _newParent as SessionResourceBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resource.SetParent( newParent == null ? null : newParent._resource );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resource.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resource.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resource" )
			_resource.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[NoCode]
public class SessionTalentsBonus : SessionValueBonus
{
	private UndoRedoDBPtr<SessionTalentsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionTalentsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionTalentsBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public SessionTalentsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionTalentsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionTalentsBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionTalentsBonus source = _source as SessionTalentsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionTalentsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionTalentsBonus newParent = rawParent == null ? null : rawParent.Get<SessionTalentsBonus>();
		if ( newParent == null && _newParent is SessionTalentsBonus )
			newParent = _newParent as SessionTalentsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[NoCode]
public class ClanPointsBonus : SessionValueBonus
{
	private UndoRedoDBPtr<ClanPointsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<ClanPointsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ClanPointsBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public ClanPointsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( ClanPointsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ClanPointsBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ClanPointsBonus source = _source as ClanPointsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClanPointsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ClanPointsBonus newParent = rawParent == null ? null : rawParent.Get<ClanPointsBonus>();
		if ( newParent == null && _newParent is ClanPointsBonus )
			newParent = _newParent as ClanPointsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class SiegePointsBonus : SessionValueBonus
{
	private UndoRedoDBPtr<SiegePointsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SiegePointsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _fakeFieldForCastle;

	[Browsable( false )]
	[NoCode]
	public int fakeFieldForCastle { get { return _fakeFieldForCastle.Get(); } set { _fakeFieldForCastle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SiegePointsBonus>(owner);
		_fakeFieldForCastle = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_fakeFieldForCastle.Changed += FireChangedEvent;
	}

	public SiegePointsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SiegePointsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SiegePointsBonus" );
		fakeFieldForCastle = source.fakeFieldForCastle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SiegePointsBonus source = _source as SiegePointsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SiegePointsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SiegePointsBonus newParent = rawParent == null ? null : rawParent.Get<SiegePointsBonus>();
		if ( newParent == null && _newParent is SiegePointsBonus )
			newParent = _newParent as SiegePointsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fakeFieldForCastle.SetParent( newParent == null ? null : newParent._fakeFieldForCastle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fakeFieldForCastle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fakeFieldForCastle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fakeFieldForCastle" )
			_fakeFieldForCastle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fakeFieldForCastle" )
			return _fakeFieldForCastle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class StatChangeBonus : SessionBonus
{
	private UndoRedoDBPtr<StatChangeBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<StatChangeBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StatBonus> _statBonuses;
	private UndoRedoList<EStat> _excludedBufs;
	private UndoRedo<EStatBufToggle> _toggle;

	[Description( "Список возможных статов для бафа" )]
	public libdb.IChangeableList<StatBonus> statBonuses { get { return _statBonuses; } set { _statBonuses.Assign( value ); } }

	[Description( "Список характеристик, которые не работают друг с другом" )]
	public libdb.IChangeableList<EStat> excludedBufs { get { return _excludedBufs; } set { _excludedBufs.Assign( value ); } }

	[Description( "Тип действия (при старте игры или к 36 уровню)" )]
	public EStatBufToggle toggle { get { return _toggle.Get(); } set { _toggle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatChangeBonus>(owner);
		_statBonuses = new UndoRedoAssignableList<StatBonus>( owner );
		_excludedBufs = new UndoRedoList<EStat>( owner );
		_toggle = new UndoRedo<EStatBufToggle>( owner, (EStatBufToggle)0 );
		___parent.Changed += FireChangedEvent;
		_statBonuses.Changed += FireChangedEvent;
		_excludedBufs.Changed += FireChangedEvent;
		_toggle.Changed += FireChangedEvent;
	}

	public StatChangeBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( StatChangeBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatChangeBonus" );
		statBonuses = source.statBonuses;
		excludedBufs = source.excludedBufs;
		toggle = source.toggle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatChangeBonus source = _source as StatChangeBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatChangeBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatChangeBonus newParent = rawParent == null ? null : rawParent.Get<StatChangeBonus>();
		if ( newParent == null && _newParent is StatChangeBonus )
			newParent = _newParent as StatChangeBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_statBonuses.SetParent( newParent == null ? null : newParent._statBonuses );
		_excludedBufs.SetParent( newParent == null ? null : newParent._excludedBufs );
		_toggle.SetParent( newParent == null ? null : newParent._toggle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_statBonuses.Reset();
		_excludedBufs.Reset();
		_toggle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_statBonuses.IsDerivedFromParent()
			&& _excludedBufs.IsDerivedFromParent()
			&& _toggle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "statBonuses" )
			_statBonuses.Reset();
		else if ( fieldName == "excludedBufs" )
			_excludedBufs.Reset();
		else if ( fieldName == "toggle" )
			_toggle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "statBonuses" )
			return _statBonuses.IsDerivedFromParent();
		if ( fieldName == "excludedBufs" )
			return _excludedBufs.IsDerivedFromParent();
		if ( fieldName == "toggle" )
			return _toggle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class TargetHeroes : DBResource
{
	private UndoRedoDBPtr<TargetHeroes> ___parent;
	[HideInOutliner]
	public new DBPtr<TargetHeroes> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Hero>> _heroes;

	public libdb.IChangeableList<DBPtr<Hero>> heroes { get { return _heroes; } set { _heroes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TargetHeroes>(owner);
		_heroes = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		___parent.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
	}

	public TargetHeroes()
	{
		Initialize( this );
	}
	private void AssignSelf( TargetHeroes source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TargetHeroes" );
		heroes = source.heroes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TargetHeroes source = _source as TargetHeroes;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TargetHeroes" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TargetHeroes newParent = rawParent == null ? null : rawParent.Get<TargetHeroes>();
		if ( newParent == null && _newParent is TargetHeroes )
			newParent = _newParent as TargetHeroes;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroes.SetParent( newParent == null ? null : newParent._heroes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroes" )
			_heroes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroes" )
			return _heroes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
