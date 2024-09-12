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
[Custom("DBServer")]
[Flags]
public enum EBuildingProductionCycle
{
	First = 1,
	Second = 2,
	Third = 4,
	Fourth = 8,
	All = 15,
};

[Custom("DBServer")]
[Flags]
public enum EGameType
{
	PvP = 1,
	CTE = 2,
	PvE = 4,
	MidOnly = 8,
	All = 15,
};

[Custom("DBServer")]
[Flags]
public enum ESessionType
{
	UsualBattle = 1,
	GuildBattle = 2,
	All = 3,
};

[Custom("DBServer")]
public enum EStatBufToggle
{
	AtGameStart = 1,
	By36Level = 2,
};

public class ShopLevelToItemsAmount : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ShopLevelToItemsAmount __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _shopLevel;
	private UndoRedo<int> _buysPerTime;

	[Description( "Уровень магазина" )]
	public int shopLevel { get { return _shopLevel.Get(); } set { _shopLevel.Set( value ); } }

	[Description( "Максимальное количество за сутки" )]
	public int buysPerTime { get { return _buysPerTime.Get(); } set { _buysPerTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_shopLevel = new UndoRedo<int>( owner, 0 );
		_buysPerTime = new UndoRedo<int>( owner, 0 );
		_shopLevel.Changed += FireChangedEvent;
		_buysPerTime.Changed += FireChangedEvent;
	}

	public ShopLevelToItemsAmount()
	{
		Initialize( GetOwner() );
	}

	public ShopLevelToItemsAmount( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ShopLevelToItemsAmount( DBResource owner, ShopLevelToItemsAmount source )
		: this(owner, source, true){}

	protected ShopLevelToItemsAmount( DBResource owner, ShopLevelToItemsAmount source, bool fireEvent )
	{
		_shopLevel = new UndoRedo<int>( owner, source.shopLevel );
		_buysPerTime = new UndoRedo<int>( owner, source.buysPerTime );
		_shopLevel.Changed += FireChangedEvent;
		_buysPerTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ShopLevelToItemsAmount source = _source as ShopLevelToItemsAmount;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ShopLevelToItemsAmount" );
		shopLevel = source.shopLevel;
		buysPerTime = source.buysPerTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ShopLevelToItemsAmount newParent = _newParent as ShopLevelToItemsAmount;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_shopLevel.SetParent( newParent == null ? null : newParent._shopLevel );
		_buysPerTime.SetParent( newParent == null ? null : newParent._buysPerTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_shopLevel.Reset();
		_buysPerTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_shopLevel.IsDerivedFromParent()
			&& _buysPerTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "shopLevel" )
			_shopLevel.Reset();
		else if ( fieldName == "buysPerTime" )
			_buysPerTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "shopLevel" )
			return _shopLevel.IsDerivedFromParent();
		if ( fieldName == "buysPerTime" )
			return _buysPerTime.IsDerivedFromParent();
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
	private ExecutableFloatString _additiveValue;
	private ExecutableFloatString _multiplicativeValue;

	[Description( "Увеличиваемый стат (Will, Strength..)" )]
	public EStat statType { get { return _statType.Get(); } set { _statType.Set( value ); } }

	[Description( "Значение, которое прибавляется (чтобы было +2 надо сюда вписать 2)" )]
	public ExecutableFloatString additiveValue { get { return _additiveValue; } set { _additiveValue.Assign( value ); } }

	[Description( "Процентное значение, которое прибавляется (чтобы прибавить 15%, надо сюда вписать 0.15" )]
	public ExecutableFloatString multiplicativeValue { get { return _multiplicativeValue; } set { _multiplicativeValue.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_statType = new UndoRedo<EStat>( owner, EStat.Life );
		_additiveValue = new ExecutableFloatString( owner );
		_multiplicativeValue = new ExecutableFloatString( owner );
		_statType.Changed += FireChangedEvent;
		_additiveValue.Changed += FireChangedEvent;
		_multiplicativeValue.Changed += FireChangedEvent;
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
		_additiveValue = new ExecutableFloatString( owner, source.additiveValue );
		_multiplicativeValue = new ExecutableFloatString( owner, source.multiplicativeValue );
		_statType.Changed += FireChangedEvent;
		_additiveValue.Changed += FireChangedEvent;
		_multiplicativeValue.Changed += FireChangedEvent;
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
		additiveValue = source.additiveValue;
		multiplicativeValue = source.multiplicativeValue;
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
		_additiveValue.SetParent( newParent == null ? null : newParent._additiveValue );
		_multiplicativeValue.SetParent( newParent == null ? null : newParent._multiplicativeValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statType.Reset();
		_additiveValue.Reset();
		_multiplicativeValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statType.IsDerivedFromParent()
			&& _additiveValue.IsDerivedFromParent()
			&& _multiplicativeValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statType" )
			_statType.Reset();
		else if ( fieldName == "additiveValue" )
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
		if ( fieldName == "statType" )
			return _statType.IsDerivedFromParent();
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

[NonTerminal]
public class GuildShopItemTarget : DBResource
{
	private UndoRedoDBPtr<GuildShopItemTarget> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildShopItemTarget> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _NumPlayers;

	[Description( "Максимальное кол-во игроков гильдиий, на которых можно распространить баф" )]
	public int NumPlayers { get { return _NumPlayers.Get(); } set { _NumPlayers.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildShopItemTarget>(owner);
		_NumPlayers = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_NumPlayers.Changed += FireChangedEvent;
	}

	public GuildShopItemTarget()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildShopItemTarget source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItemTarget" );
		NumPlayers = source.NumPlayers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildShopItemTarget source = _source as GuildShopItemTarget;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItemTarget" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildShopItemTarget newParent = rawParent == null ? null : rawParent.Get<GuildShopItemTarget>();
		if ( newParent == null && _newParent is GuildShopItemTarget )
			newParent = _newParent as GuildShopItemTarget;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_NumPlayers.SetParent( newParent == null ? null : newParent._NumPlayers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_NumPlayers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_NumPlayers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "NumPlayers" )
			_NumPlayers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "NumPlayers" )
			return _NumPlayers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
public class GuildShopItemBonus : DBResource
{
	private UndoRedoDBPtr<GuildShopItemBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildShopItemBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _additiveValue;
	private ExecutableFloatString _multiplicativeValue;

	[Description( "Значение, которое прибавляется (чтобы было +2 надо сюда вписать 2)" )]
	public ExecutableFloatString additiveValue { get { return _additiveValue; } set { _additiveValue.Assign( value ); } }

	[Description( "Процентное значение, которое прибавляется (чтобы прибавить 15%, надо сюда вписать 0.15" )]
	public ExecutableFloatString multiplicativeValue { get { return _multiplicativeValue; } set { _multiplicativeValue.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildShopItemBonus>(owner);
		_additiveValue = new ExecutableFloatString( owner );
		ExecutableFloatString __multiplicativeValue = new ExecutableFloatString(); // Construct default object for multiplicativeValue
		__multiplicativeValue.sString = "1.0f";
		_multiplicativeValue = new ExecutableFloatString( owner, __multiplicativeValue );
		___parent.Changed += FireChangedEvent;
		_additiveValue.Changed += FireChangedEvent;
		_multiplicativeValue.Changed += FireChangedEvent;
	}

	public GuildShopItemBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildShopItemBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItemBonus" );
		additiveValue = source.additiveValue;
		multiplicativeValue = source.multiplicativeValue;
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

		_additiveValue.SetParent( newParent == null ? null : newParent._additiveValue );
		_multiplicativeValue.SetParent( newParent == null ? null : newParent._multiplicativeValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_additiveValue.Reset();
		_multiplicativeValue.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_additiveValue.IsDerivedFromParent()
			&& _multiplicativeValue.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "additiveValue" )
			_additiveValue.Reset();
		else if ( fieldName == "multiplicativeValue" )
			_multiplicativeValue.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "additiveValue" )
			return _additiveValue.IsDerivedFromParent();
		if ( fieldName == "multiplicativeValue" )
			return _multiplicativeValue.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class AllHeroExperienceBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<AllHeroExperienceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<AllHeroExperienceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EGameType> _mapType;
	private UndoRedo<ESessionType> _sessionType;

	[Custom("DBServer", "Social")]
	[Description( "Map type" )]
	public EGameType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AllHeroExperienceBonus>(owner);
		_mapType = new UndoRedo<EGameType>( owner, EGameType.All );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		___parent.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public AllHeroExperienceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( AllHeroExperienceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AllHeroExperienceBonus" );
		mapType = source.mapType;
		sessionType = source.sessionType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AllHeroExperienceBonus source = _source as AllHeroExperienceBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AllHeroExperienceBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AllHeroExperienceBonus newParent = rawParent == null ? null : rawParent.Get<AllHeroExperienceBonus>();
		if ( newParent == null && _newParent is AllHeroExperienceBonus )
			newParent = _newParent as AllHeroExperienceBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mapType.Reset();
		_sessionType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mapType.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class BestGuildInvesters : GuildShopItemTarget
{
	private UndoRedoDBPtr<BestGuildInvesters> ___parent;
	[HideInOutliner]
	public new DBPtr<BestGuildInvesters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _daysToCount;

	[Description( "Период за который считаем лучшими" )]
	public int daysToCount { get { return _daysToCount.Get(); } set { _daysToCount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BestGuildInvesters>(owner);
		_daysToCount = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_daysToCount.Changed += FireChangedEvent;
	}

	public BestGuildInvesters()
	{
		Initialize( this );
	}
	private void AssignSelf( BestGuildInvesters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BestGuildInvesters" );
		daysToCount = source.daysToCount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BestGuildInvesters source = _source as BestGuildInvesters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BestGuildInvesters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BestGuildInvesters newParent = rawParent == null ? null : rawParent.Get<BestGuildInvesters>();
		if ( newParent == null && _newParent is BestGuildInvesters )
			newParent = _newParent as BestGuildInvesters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_daysToCount.SetParent( newParent == null ? null : newParent._daysToCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_daysToCount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_daysToCount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "daysToCount" )
			_daysToCount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "daysToCount" )
			return _daysToCount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class BestRankedPlayers : GuildShopItemTarget
{
	private UndoRedoDBPtr<BestRankedPlayers> ___parent;
	[HideInOutliner]
	public new DBPtr<BestRankedPlayers> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BestRankedPlayers>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BestRankedPlayers()
	{
		Initialize( this );
	}
	private void AssignSelf( BestRankedPlayers source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BestRankedPlayers" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BestRankedPlayers source = _source as BestRankedPlayers;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BestRankedPlayers" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BestRankedPlayers newParent = rawParent == null ? null : rawParent.Get<BestRankedPlayers>();
		if ( newParent == null && _newParent is BestRankedPlayers )
			newParent = _newParent as BestRankedPlayers;
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

public class Buyer : GuildShopItemTarget
{
	private UndoRedoDBPtr<Buyer> ___parent;
	[HideInOutliner]
	public new DBPtr<Buyer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Buyer>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public Buyer()
	{
		Initialize( this );
	}
	private void AssignSelf( Buyer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Buyer" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Buyer source = _source as Buyer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Buyer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Buyer newParent = rawParent == null ? null : rawParent.Get<Buyer>();
		if ( newParent == null && _newParent is Buyer )
			newParent = _newParent as Buyer;
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

public class ClanPointsBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<ClanPointsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<ClanPointsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;
	private UndoRedo<EGameType> _mapType;
	private UndoRedo<ESessionType> _sessionType;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Map type" )]
	public EGameType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ClanPointsBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		_mapType = new UndoRedo<EGameType>( owner, EGameType.All );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public ClanPointsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( ClanPointsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ClanPointsBonus" );
		targetHeroes = source.targetHeroes;
		mapType = source.mapType;
		sessionType = source.sessionType;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
		_mapType.Reset();
		_sessionType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetHeroes.IsDerivedFromParent()
			&& _mapType.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("persistentId")]
[NonTerminal]
public class GuildShopItem : DBResource
{
	private UndoRedoDBPtr<GuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private TextRef _description;
	private TextRef _tooltip;
	private UndoRedoDBPtr<Texture> _icon;
	private ResourcesTable _price;
	private UndoRedo<int> _discount;
	private UndoRedoAssignableList<ShopLevelToItemsAmount> _shopLevelToItemsAmount;
	private UndoRedo<int> _levelToUnlock;
	private UndoRedo<GuildShopCategoryType> _shopCategory;

	[Description( "ID товара" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Цена" )]
	public ResourcesTable price { get { return _price; } set { _price.Assign( value ); } }

	[Description( "Скидка в процентах" )]
	public int discount { get { return _discount.Get(); } set { _discount.Set( value ); } }

	[Description( "Кол-во доступных айтемов в зависимости от уровня магазина. Если айтемы бесконечны, не заполняем" )]
	public libdb.IChangeableList<ShopLevelToItemsAmount> shopLevelToItemsAmount { get { return _shopLevelToItemsAmount; } set { _shopLevelToItemsAmount.Assign( value ); } }

	[Description( "Требуем ранг магазина с которого становится доступным" )]
	public int levelToUnlock { get { return _levelToUnlock.Get(); } set { _levelToUnlock.Set( value ); } }

	[Description( "Категория в магазине" )]
	public GuildShopCategoryType shopCategory { get { return _shopCategory.Get(); } set { _shopCategory.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildShopItem>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_description = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_price = new ResourcesTable( owner );
		_discount = new UndoRedo<int>( owner, 0 );
		_shopLevelToItemsAmount = new UndoRedoAssignableList<ShopLevelToItemsAmount>( owner );
		_levelToUnlock = new UndoRedo<int>( owner, 0 );
		_shopCategory = new UndoRedo<GuildShopCategoryType>( owner, GuildShopCategoryType.ClanBufs );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
		_discount.Changed += FireChangedEvent;
		_shopLevelToItemsAmount.Changed += FireChangedEvent;
		_levelToUnlock.Changed += FireChangedEvent;
		_shopCategory.Changed += FireChangedEvent;
	}

	public GuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItem" );
		persistentId = source.persistentId;
		description = source.description;
		tooltip = source.tooltip;
		icon = source.icon;
		price = source.price;
		discount = source.discount;
		shopLevelToItemsAmount = source.shopLevelToItemsAmount;
		levelToUnlock = source.levelToUnlock;
		shopCategory = source.shopCategory;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildShopItem source = _source as GuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildShopItem newParent = rawParent == null ? null : rawParent.Get<GuildShopItem>();
		if ( newParent == null && _newParent is GuildShopItem )
			newParent = _newParent as GuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_description.SetParent( newParent == null ? null : newParent._description );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_price.SetParent( newParent == null ? null : newParent._price );
		_discount.SetParent( newParent == null ? null : newParent._discount );
		_shopLevelToItemsAmount.SetParent( newParent == null ? null : newParent._shopLevelToItemsAmount );
		_levelToUnlock.SetParent( newParent == null ? null : newParent._levelToUnlock );
		_shopCategory.SetParent( newParent == null ? null : newParent._shopCategory );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_description.Reset();
		_tooltip.Reset();
		_icon.Reset();
		_price.Reset();
		_discount.Reset();
		_shopLevelToItemsAmount.Reset();
		_levelToUnlock.Reset();
		_shopCategory.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _price.IsDerivedFromParent()
			&& _discount.IsDerivedFromParent()
			&& _shopLevelToItemsAmount.IsDerivedFromParent()
			&& _levelToUnlock.IsDerivedFromParent()
			&& _shopCategory.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "price" )
			_price.Reset();
		else if ( fieldName == "discount" )
			_discount.Reset();
		else if ( fieldName == "shopLevelToItemsAmount" )
			_shopLevelToItemsAmount.Reset();
		else if ( fieldName == "levelToUnlock" )
			_levelToUnlock.Reset();
		else if ( fieldName == "shopCategory" )
			_shopCategory.Reset();
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
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "price" )
			return _price.IsDerivedFromParent();
		if ( fieldName == "discount" )
			return _discount.IsDerivedFromParent();
		if ( fieldName == "shopLevelToItemsAmount" )
			return _shopLevelToItemsAmount.IsDerivedFromParent();
		if ( fieldName == "levelToUnlock" )
			return _levelToUnlock.IsDerivedFromParent();
		if ( fieldName == "shopCategory" )
			return _shopCategory.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class GuildBuf : DBResource
{
	private UndoRedoDBPtr<GuildBuf> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBuf> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedoAssignableList<DBPtr<GuildBuf>> _doNotWorkWith;
	private UndoRedo<bool> _isGuildBonus;
	private UndoRedo<int> _priority;
	private UndoRedo<int> _duration;
	private UndoRedo<int> _numWins;
	private TextRef _propertyTooltip;
	private UndoRedoAssignableList<DBPtr<GuildShopItemBonus>> _bonuses;

	[Description( "ID бафа" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "Список расходников, с которыми одновременно не работает" )]
	public libdb.IChangeableList<DBPtr<GuildBuf>> doNotWorkWith { get { return _doNotWorkWith; } set { _doNotWorkWith.Assign( value ); } }

	[Description( "Если true, то по выходу из клана бонус у игрока пропадает" )]
	public bool isGuildBonus { get { return _isGuildBonus.Get(); } set { _isGuildBonus.Set( value ); } }

	[Description( "Приоритет для списка расходников (вес эффекта) - какой из них остается работать" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "Длительность" )]
	public int duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "Количество побед, в течение которых активен баф" )]
	public int numWins { get { return _numWins.Get(); } set { _numWins.Set( value ); } }

	[Description( "Тултип для свойства - тот что будет показываться не в магазине, а при наведении на иконку баффа" )]
	public TextRef propertyTooltip { get { return _propertyTooltip; } set { _propertyTooltip.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<GuildShopItemBonus>> bonuses { get { return _bonuses; } set { _bonuses.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBuf>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_doNotWorkWith = new UndoRedoAssignableList<DBPtr<GuildBuf>>( owner );
		_isGuildBonus = new UndoRedo<bool>( owner, false );
		_priority = new UndoRedo<int>( owner, 0 );
		_duration = new UndoRedo<int>( owner, 0 );
		_numWins = new UndoRedo<int>( owner, 0 );
		_propertyTooltip = new TextRef( owner, new TextRef() );
		_bonuses = new UndoRedoAssignableList<DBPtr<GuildShopItemBonus>>( owner );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_doNotWorkWith.Changed += FireChangedEvent;
		_isGuildBonus.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_numWins.Changed += FireChangedEvent;
		_propertyTooltip.Changed += FireChangedEvent;
		_bonuses.Changed += FireChangedEvent;
	}

	public GuildBuf()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBuf source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBuf" );
		persistentId = source.persistentId;
		doNotWorkWith = source.doNotWorkWith;
		isGuildBonus = source.isGuildBonus;
		priority = source.priority;
		duration = source.duration;
		numWins = source.numWins;
		propertyTooltip = source.propertyTooltip;
		bonuses = source.bonuses;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBuf source = _source as GuildBuf;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBuf" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBuf newParent = rawParent == null ? null : rawParent.Get<GuildBuf>();
		if ( newParent == null && _newParent is GuildBuf )
			newParent = _newParent as GuildBuf;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_doNotWorkWith.SetParent( newParent == null ? null : newParent._doNotWorkWith );
		_isGuildBonus.SetParent( newParent == null ? null : newParent._isGuildBonus );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_numWins.SetParent( newParent == null ? null : newParent._numWins );
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
		_numWins.Reset();
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
			&& _numWins.IsDerivedFromParent()
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
		else if ( fieldName == "numWins" )
			_numWins.Reset();
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
		if ( fieldName == "numWins" )
			return _numWins.IsDerivedFromParent();
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

[UseTypeName("GUILDBUFFS")]
public class GuildBuffsCollection : DBResource
{
	private UndoRedoDBPtr<GuildBuffsCollection> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBuffsCollection> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<GuildBuf>> _buffs;

	public libdb.IChangeableList<DBPtr<GuildBuf>> buffs { get { return _buffs; } set { _buffs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBuffsCollection>(owner);
		_buffs = new UndoRedoAssignableList<DBPtr<GuildBuf>>( owner );
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

public class FlagGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<FlagGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<FlagGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<CustomFlag> _flag;

	[Description( "Флаг для выдачи" )]
	public DBPtr<CustomFlag> flag { get { return _flag.Get(); } set { _flag.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FlagGuildShopItem>(owner);
		_flag = new UndoRedoDBPtr<CustomFlag>( owner );
		___parent.Changed += FireChangedEvent;
		_flag.Changed += FireChangedEvent;
	}

	public FlagGuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( FlagGuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FlagGuildShopItem" );
		flag = source.flag;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FlagGuildShopItem source = _source as FlagGuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlagGuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FlagGuildShopItem newParent = rawParent == null ? null : rawParent.Get<FlagGuildShopItem>();
		if ( newParent == null && _newParent is FlagGuildShopItem )
			newParent = _newParent as FlagGuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flag.SetParent( newParent == null ? null : newParent._flag );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flag.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flag.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flag" )
			_flag.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flag" )
			return _flag.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class AllHeroEnergyBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<AllHeroEnergyBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<AllHeroEnergyBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AllHeroEnergyBonus>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AllHeroEnergyBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( AllHeroEnergyBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AllHeroEnergyBonus" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AllHeroEnergyBonus source = _source as AllHeroEnergyBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AllHeroEnergyBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AllHeroEnergyBonus newParent = rawParent == null ? null : rawParent.Get<AllHeroEnergyBonus>();
		if ( newParent == null && _newParent is AllHeroEnergyBonus )
			newParent = _newParent as AllHeroEnergyBonus;
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

public class AllGuildMembers : GuildShopItemTarget
{
	private UndoRedoDBPtr<AllGuildMembers> ___parent;
	[HideInOutliner]
	public new DBPtr<AllGuildMembers> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AllGuildMembers>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AllGuildMembers()
	{
		Initialize( this );
	}
	private void AssignSelf( AllGuildMembers source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AllGuildMembers" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AllGuildMembers source = _source as AllGuildMembers;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AllGuildMembers" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AllGuildMembers newParent = rawParent == null ? null : rawParent.Get<AllGuildMembers>();
		if ( newParent == null && _newParent is AllGuildMembers )
			newParent = _newParent as AllGuildMembers;
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

public class HeroEnergyBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<HeroEnergyBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroEnergyBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroEnergyBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
	}

	public HeroEnergyBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroEnergyBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroEnergyBonus" );
		targetHeroes = source.targetHeroes;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetHeroes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class HeroExperienceBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<HeroExperienceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroExperienceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;
	private UndoRedo<EGameType> _mapType;
	private UndoRedo<ESessionType> _sessionType;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Map type" )]
	public EGameType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroExperienceBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		_mapType = new UndoRedo<EGameType>( owner, EGameType.All );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public HeroExperienceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroExperienceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroExperienceBonus" );
		targetHeroes = source.targetHeroes;
		mapType = source.mapType;
		sessionType = source.sessionType;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
		_mapType.Reset();
		_sessionType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetHeroes.IsDerivedFromParent()
			&& _mapType.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class OneTimeGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<OneTimeGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<OneTimeGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<GuildShopItemTarget>> _target;
	private UndoRedoDBPtr<GuildBuf> _guildBuff;

	[Description( "На кого воздействует бонус" )]
	public libdb.IChangeableList<DBPtr<GuildShopItemTarget>> target { get { return _target; } set { _target.Assign( value ); } }

	[Description( "Баф для этого айтема" )]
	public DBPtr<GuildBuf> guildBuff { get { return _guildBuff.Get(); } set { _guildBuff.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OneTimeGuildShopItem>(owner);
		_target = new UndoRedoAssignableList<DBPtr<GuildShopItemTarget>>( owner );
		_guildBuff = new UndoRedoDBPtr<GuildBuf>( owner );
		___parent.Changed += FireChangedEvent;
		_target.Changed += FireChangedEvent;
		_guildBuff.Changed += FireChangedEvent;
	}

	public OneTimeGuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( OneTimeGuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OneTimeGuildShopItem" );
		target = source.target;
		guildBuff = source.guildBuff;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OneTimeGuildShopItem source = _source as OneTimeGuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OneTimeGuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OneTimeGuildShopItem newParent = rawParent == null ? null : rawParent.Get<OneTimeGuildShopItem>();
		if ( newParent == null && _newParent is OneTimeGuildShopItem )
			newParent = _newParent as OneTimeGuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_target.SetParent( newParent == null ? null : newParent._target );
		_guildBuff.SetParent( newParent == null ? null : newParent._guildBuff );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_target.Reset();
		_guildBuff.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_target.IsDerivedFromParent()
			&& _guildBuff.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "target" )
			_target.Reset();
		else if ( fieldName == "guildBuff" )
			_guildBuff.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "target" )
			return _target.IsDerivedFromParent();
		if ( fieldName == "guildBuff" )
			return _guildBuff.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class OnlineGuildMembers : GuildShopItemTarget
{
	private UndoRedoDBPtr<OnlineGuildMembers> ___parent;
	[HideInOutliner]
	public new DBPtr<OnlineGuildMembers> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OnlineGuildMembers>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public OnlineGuildMembers()
	{
		Initialize( this );
	}
	private void AssignSelf( OnlineGuildMembers source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OnlineGuildMembers" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OnlineGuildMembers source = _source as OnlineGuildMembers;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OnlineGuildMembers" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OnlineGuildMembers newParent = rawParent == null ? null : rawParent.Get<OnlineGuildMembers>();
		if ( newParent == null && _newParent is OnlineGuildMembers )
			newParent = _newParent as OnlineGuildMembers;
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

public class RankedGuildMembers : GuildShopItemTarget
{
	private UndoRedoDBPtr<RankedGuildMembers> ___parent;
	[HideInOutliner]
	public new DBPtr<RankedGuildMembers> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minRating;
	private UndoRedo<int> _maxRating;

	[Description( "Рейтинг, с которого начинает действовать баф" )]
	public int minRating { get { return _minRating.Get(); } set { _minRating.Set( value ); } }

	[Description( "Рейтинг, после которого прекращает действовать баф" )]
	public int maxRating { get { return _maxRating.Get(); } set { _maxRating.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RankedGuildMembers>(owner);
		_minRating = new UndoRedo<int>( owner, 0 );
		_maxRating = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_minRating.Changed += FireChangedEvent;
		_maxRating.Changed += FireChangedEvent;
	}

	public RankedGuildMembers()
	{
		Initialize( this );
	}
	private void AssignSelf( RankedGuildMembers source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RankedGuildMembers" );
		minRating = source.minRating;
		maxRating = source.maxRating;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RankedGuildMembers source = _source as RankedGuildMembers;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RankedGuildMembers" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RankedGuildMembers newParent = rawParent == null ? null : rawParent.Get<RankedGuildMembers>();
		if ( newParent == null && _newParent is RankedGuildMembers )
			newParent = _newParent as RankedGuildMembers;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minRating.SetParent( newParent == null ? null : newParent._minRating );
		_maxRating.SetParent( newParent == null ? null : newParent._maxRating );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minRating.Reset();
		_maxRating.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minRating.IsDerivedFromParent()
			&& _maxRating.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minRating" )
			_minRating.Reset();
		else if ( fieldName == "maxRating" )
			_maxRating.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minRating" )
			return _minRating.IsDerivedFromParent();
		if ( fieldName == "maxRating" )
			return _maxRating.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SessionResourceBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<SessionResourceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionResourceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;
	private UndoRedo<EResourceType> _resource;
	private UndoRedo<EGameType> _mapType;
	private UndoRedo<ESessionType> _sessionType;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	public EResourceType resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Map type" )]
	public EGameType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionResourceBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		_resource = new UndoRedo<EResourceType>( owner, EResourceType.Silver );
		_mapType = new UndoRedo<EGameType>( owner, EGameType.All );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public SessionResourceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionResourceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionResourceBonus" );
		targetHeroes = source.targetHeroes;
		resource = source.resource;
		mapType = source.mapType;
		sessionType = source.sessionType;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		_resource.SetParent( newParent == null ? null : newParent._resource );
		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
		_resource.Reset();
		_mapType.Reset();
		_sessionType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetHeroes.IsDerivedFromParent()
			&& _resource.IsDerivedFromParent()
			&& _mapType.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else if ( fieldName == "resource" )
			_resource.Reset();
		else if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SessionTalentsBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<SessionTalentsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionTalentsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;
	private UndoRedoList<ETalentRarity> _talentRarities;
	private UndoRedo<EGameType> _mapType;
	private UndoRedo<ESessionType> _sessionType;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	[Description( "Rarities, affected by buff" )]
	public libdb.IChangeableList<ETalentRarity> talentRarities { get { return _talentRarities; } set { _talentRarities.Assign( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Map type" )]
	public EGameType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Session type" )]
	public ESessionType sessionType { get { return _sessionType.Get(); } set { _sessionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionTalentsBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		_talentRarities = new UndoRedoList<ETalentRarity>( owner );
		_mapType = new UndoRedo<EGameType>( owner, EGameType.All );
		_sessionType = new UndoRedo<ESessionType>( owner, ESessionType.All );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
		_talentRarities.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_sessionType.Changed += FireChangedEvent;
	}

	public SessionTalentsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionTalentsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionTalentsBonus" );
		targetHeroes = source.targetHeroes;
		talentRarities = source.talentRarities;
		mapType = source.mapType;
		sessionType = source.sessionType;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		_talentRarities.SetParent( newParent == null ? null : newParent._talentRarities );
		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_sessionType.SetParent( newParent == null ? null : newParent._sessionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
		_talentRarities.Reset();
		_mapType.Reset();
		_sessionType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetHeroes.IsDerivedFromParent()
			&& _talentRarities.IsDerivedFromParent()
			&& _mapType.IsDerivedFromParent()
			&& _sessionType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else if ( fieldName == "talentRarities" )
			_talentRarities.Reset();
		else if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "sessionType" )
			_sessionType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
		if ( fieldName == "talentRarities" )
			return _talentRarities.IsDerivedFromParent();
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "sessionType" )
			return _sessionType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SkinGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<SkinGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<SkinGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<HeroSkin> _skin;

	[Description( "Скин" )]
	public DBPtr<HeroSkin> skin { get { return _skin.Get(); } set { _skin.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SkinGuildShopItem>(owner);
		_skin = new UndoRedoDBPtr<HeroSkin>( owner );
		___parent.Changed += FireChangedEvent;
		_skin.Changed += FireChangedEvent;
	}

	public SkinGuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( SkinGuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SkinGuildShopItem" );
		skin = source.skin;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SkinGuildShopItem source = _source as SkinGuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkinGuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SkinGuildShopItem newParent = rawParent == null ? null : rawParent.Get<SkinGuildShopItem>();
		if ( newParent == null && _newParent is SkinGuildShopItem )
			newParent = _newParent as SkinGuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_skin.SetParent( newParent == null ? null : newParent._skin );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_skin.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_skin.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "skin" )
			_skin.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "skin" )
			return _skin.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class StatChangeBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<StatChangeBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<StatChangeBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetHeroes> _targetHeroes;
	private UndoRedoAssignableList<StatBonus> _statBonuses;
	private UndoRedoList<EStat> _excludedBufs;
	private UndoRedo<EStatBufToggle> _toggle;

	public DBPtr<TargetHeroes> targetHeroes { get { return _targetHeroes.Get(); } set { _targetHeroes.Set( value ); } }

	[Description( "Список возможных статов для бафа" )]
	public libdb.IChangeableList<StatBonus> statBonuses { get { return _statBonuses; } set { _statBonuses.Assign( value ); } }

	[Description( "Список характеристик, которые не работают друг с другом" )]
	public libdb.IChangeableList<EStat> excludedBufs { get { return _excludedBufs; } set { _excludedBufs.Assign( value ); } }

	[Description( "Тип действия (при старте игры или к 36 уровню)" )]
	public EStatBufToggle toggle { get { return _toggle.Get(); } set { _toggle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatChangeBonus>(owner);
		_targetHeroes = new UndoRedoDBPtr<TargetHeroes>( owner );
		_statBonuses = new UndoRedoAssignableList<StatBonus>( owner );
		_excludedBufs = new UndoRedoList<EStat>( owner );
		_toggle = new UndoRedo<EStatBufToggle>( owner, (EStatBufToggle)0 );
		___parent.Changed += FireChangedEvent;
		_targetHeroes.Changed += FireChangedEvent;
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
		targetHeroes = source.targetHeroes;
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

		_targetHeroes.SetParent( newParent == null ? null : newParent._targetHeroes );
		_statBonuses.SetParent( newParent == null ? null : newParent._statBonuses );
		_excludedBufs.SetParent( newParent == null ? null : newParent._excludedBufs );
		_toggle.SetParent( newParent == null ? null : newParent._toggle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetHeroes.Reset();
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
			_targetHeroes.IsDerivedFromParent()
			&& _statBonuses.IsDerivedFromParent()
			&& _excludedBufs.IsDerivedFromParent()
			&& _toggle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetHeroes" )
			_targetHeroes.Reset();
		else if ( fieldName == "statBonuses" )
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
		if ( fieldName == "targetHeroes" )
			return _targetHeroes.IsDerivedFromParent();
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

public class TalentGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<TalentGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Talent> _talent;

	[Description( "Талант" )]
	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentGuildShopItem>(owner);
		_talent = new UndoRedoDBPtr<Talent>( owner );
		___parent.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
	}

	public TalentGuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentGuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentGuildShopItem" );
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentGuildShopItem source = _source as TalentGuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentGuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentGuildShopItem newParent = rawParent == null ? null : rawParent.Get<TalentGuildShopItem>();
		if ( newParent == null && _newParent is TalentGuildShopItem )
			newParent = _newParent as TalentGuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_talent.SetParent( newParent == null ? null : newParent._talent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_talent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_talent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "talent" )
			_talent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "talent" )
			return _talent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

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

public class WorstGuildInvesters : GuildShopItemTarget
{
	private UndoRedoDBPtr<WorstGuildInvesters> ___parent;
	[HideInOutliner]
	public new DBPtr<WorstGuildInvesters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _daysToCount;

	[Description( "Период за который считаем худшими" )]
	public int daysToCount { get { return _daysToCount.Get(); } set { _daysToCount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WorstGuildInvesters>(owner);
		_daysToCount = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_daysToCount.Changed += FireChangedEvent;
	}

	public WorstGuildInvesters()
	{
		Initialize( this );
	}
	private void AssignSelf( WorstGuildInvesters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WorstGuildInvesters" );
		daysToCount = source.daysToCount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WorstGuildInvesters source = _source as WorstGuildInvesters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WorstGuildInvesters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WorstGuildInvesters newParent = rawParent == null ? null : rawParent.Get<WorstGuildInvesters>();
		if ( newParent == null && _newParent is WorstGuildInvesters )
			newParent = _newParent as WorstGuildInvesters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_daysToCount.SetParent( newParent == null ? null : newParent._daysToCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_daysToCount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_daysToCount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "daysToCount" )
			_daysToCount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "daysToCount" )
			return _daysToCount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class WorstRankedPlayers : GuildShopItemTarget
{
	private UndoRedoDBPtr<WorstRankedPlayers> ___parent;
	[HideInOutliner]
	public new DBPtr<WorstRankedPlayers> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WorstRankedPlayers>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public WorstRankedPlayers()
	{
		Initialize( this );
	}
	private void AssignSelf( WorstRankedPlayers source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WorstRankedPlayers" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WorstRankedPlayers source = _source as WorstRankedPlayers;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WorstRankedPlayers" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WorstRankedPlayers newParent = rawParent == null ? null : rawParent.Get<WorstRankedPlayers>();
		if ( newParent == null && _newParent is WorstRankedPlayers )
			newParent = _newParent as WorstRankedPlayers;
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

}; // namespace DBTypes
