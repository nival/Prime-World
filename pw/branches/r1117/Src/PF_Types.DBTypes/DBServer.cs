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
public enum ClanWarsRollItemType
{
	ClanRating = 0,
	PlayerRating = 1,
};

[Custom("DBServer")]
[NoCode]
public enum ESweepStage
{
	LowerLimit = 0,
	UpperLimit = 1,
	WidenedLimits = 2,
};

[Custom("DBServer", "Social")]
public enum ResourceRollConstraint
{
	Silver = 0,
	Resource1 = 1,
	Resource2 = 2,
	Resource3 = 3,
	Pearl = 4,
	RedPearl = 5,
	Shard = 6,
	CustomCurrency = 7,
};

public enum TalentUpgradeEntityType
{
	Rune = 0,
	Catalyst = 1,
};

[Custom("DBServer")]
public class BaseModifierFromQuantity : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BaseModifierFromQuantity __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _quantity;
	private UndoRedo<float> _percent;

	public float quantity { get { return _quantity.Get(); } set { _quantity.Set( value ); } }

	public float percent { get { return _percent.Get(); } set { _percent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_quantity = new UndoRedo<float>( owner, 0.0f );
		_percent = new UndoRedo<float>( owner, 0.0f );
		_quantity.Changed += FireChangedEvent;
		_percent.Changed += FireChangedEvent;
	}

	public BaseModifierFromQuantity()
	{
		Initialize( GetOwner() );
	}

	public BaseModifierFromQuantity( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BaseModifierFromQuantity( DBResource owner, BaseModifierFromQuantity source )
		: this(owner, source, true){}

	protected BaseModifierFromQuantity( DBResource owner, BaseModifierFromQuantity source, bool fireEvent )
	{
		_quantity = new UndoRedo<float>( owner, source.quantity );
		_percent = new UndoRedo<float>( owner, source.percent );
		_quantity.Changed += FireChangedEvent;
		_percent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BaseModifierFromQuantity source = _source as BaseModifierFromQuantity;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseModifierFromQuantity" );
		quantity = source.quantity;
		percent = source.percent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BaseModifierFromQuantity newParent = _newParent as BaseModifierFromQuantity;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_quantity.SetParent( newParent == null ? null : newParent._quantity );
		_percent.SetParent( newParent == null ? null : newParent._percent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_quantity.Reset();
		_percent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_quantity.IsDerivedFromParent()
			&& _percent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "quantity" )
			_quantity.Reset();
		else if ( fieldName == "percent" )
			_percent.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "quantity" )
			return _quantity.IsDerivedFromParent();
		if ( fieldName == "percent" )
			return _percent.IsDerivedFromParent();
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

[Custom("DBServer")]
[DBVersion(1)]
public class EstimFunctionWeights : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EstimFunctionWeights __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _ladiesNumber;
	private UndoRedo<float> _genderPairs;
	private UndoRedo<float> _heroes;
	private UndoRedo<float> _ratingSpan;
	private UndoRedo<float> _ratingPatternDelta;
	private UndoRedo<float> _ratingTeamAvgDelta;
	private UndoRedo<float> _forceSpan;
	private UndoRedo<float> _heroClassesDifference;
	private UndoRedo<float> _heroClassesOptimum;

	[Description( "Вес компоненты про количество девочек в команде" )]
	public float ladiesNumber { get { return _ladiesNumber.Get(); } set { _ladiesNumber.Set( value ); } }

	[Description( "Вес компоненты про соотношение количества гендерных пар между командами" )]
	public float genderPairs { get { return _genderPairs.Get(); } set { _genderPairs.Set( value ); } }

	[Description( "Вес компоненты про количество одинаковых героев" )]
	public float heroes { get { return _heroes.Get(); } set { _heroes.Set( value ); } }

	[Description( "Вес компоненты про разброс рейтинга в команде, только для PVP" )]
	public float ratingSpan { get { return _ratingSpan.Get(); } set { _ratingSpan.Set( value ); } }

	[Description( "Вес компоненты про разброс рейтинга после сортировки игроков по рейтингу" )]
	public float ratingPatternDelta { get { return _ratingPatternDelta.Get(); } set { _ratingPatternDelta.Set( value ); } }

	[Description( "Вес компоненты про разброс среднего рейтинга двух команд" )]
	public float ratingTeamAvgDelta { get { return _ratingTeamAvgDelta.Get(); } set { _ratingTeamAvgDelta.Set( value ); } }

	[Description( "Вес компоненты про разброс форса в команде, только для PVE" )]
	public float forceSpan { get { return _forceSpan.Get(); } set { _forceSpan.Set( value ); } }

	[Description( "Вес компоненты про разницу ролей команд, разница между двумя командами" )]
	public float heroClassesDifference { get { return _heroClassesDifference.Get(); } set { _heroClassesDifference.Set( value ); } }

	[Description( "Вес компоненты про оптимальность классов героев, срднее между двумя командами" )]
	public float heroClassesOptimum { get { return _heroClassesOptimum.Get(); } set { _heroClassesOptimum.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ladiesNumber = new UndoRedo<float>( owner, 1.0f );
		_genderPairs = new UndoRedo<float>( owner, 1.0f );
		_heroes = new UndoRedo<float>( owner, 1.0f );
		_ratingSpan = new UndoRedo<float>( owner, 1.0f );
		_ratingPatternDelta = new UndoRedo<float>( owner, 1.0f );
		_ratingTeamAvgDelta = new UndoRedo<float>( owner, 1.0f );
		_forceSpan = new UndoRedo<float>( owner, 1.0f );
		_heroClassesDifference = new UndoRedo<float>( owner, 1.0f );
		_heroClassesOptimum = new UndoRedo<float>( owner, 1.0f );
		_ladiesNumber.Changed += FireChangedEvent;
		_genderPairs.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
		_ratingSpan.Changed += FireChangedEvent;
		_ratingPatternDelta.Changed += FireChangedEvent;
		_ratingTeamAvgDelta.Changed += FireChangedEvent;
		_forceSpan.Changed += FireChangedEvent;
		_heroClassesDifference.Changed += FireChangedEvent;
		_heroClassesOptimum.Changed += FireChangedEvent;
	}

	public EstimFunctionWeights()
	{
		Initialize( GetOwner() );
	}

	public EstimFunctionWeights( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EstimFunctionWeights( DBResource owner, EstimFunctionWeights source )
		: this(owner, source, true){}

	protected EstimFunctionWeights( DBResource owner, EstimFunctionWeights source, bool fireEvent )
	{
		_ladiesNumber = new UndoRedo<float>( owner, source.ladiesNumber );
		_genderPairs = new UndoRedo<float>( owner, source.genderPairs );
		_heroes = new UndoRedo<float>( owner, source.heroes );
		_ratingSpan = new UndoRedo<float>( owner, source.ratingSpan );
		_ratingPatternDelta = new UndoRedo<float>( owner, source.ratingPatternDelta );
		_ratingTeamAvgDelta = new UndoRedo<float>( owner, source.ratingTeamAvgDelta );
		_forceSpan = new UndoRedo<float>( owner, source.forceSpan );
		_heroClassesDifference = new UndoRedo<float>( owner, source.heroClassesDifference );
		_heroClassesOptimum = new UndoRedo<float>( owner, source.heroClassesOptimum );
		_ladiesNumber.Changed += FireChangedEvent;
		_genderPairs.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
		_ratingSpan.Changed += FireChangedEvent;
		_ratingPatternDelta.Changed += FireChangedEvent;
		_ratingTeamAvgDelta.Changed += FireChangedEvent;
		_forceSpan.Changed += FireChangedEvent;
		_heroClassesDifference.Changed += FireChangedEvent;
		_heroClassesOptimum.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EstimFunctionWeights source = _source as EstimFunctionWeights;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EstimFunctionWeights" );
		ladiesNumber = source.ladiesNumber;
		genderPairs = source.genderPairs;
		heroes = source.heroes;
		ratingSpan = source.ratingSpan;
		ratingPatternDelta = source.ratingPatternDelta;
		ratingTeamAvgDelta = source.ratingTeamAvgDelta;
		forceSpan = source.forceSpan;
		heroClassesDifference = source.heroClassesDifference;
		heroClassesOptimum = source.heroClassesOptimum;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EstimFunctionWeights newParent = _newParent as EstimFunctionWeights;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ladiesNumber.SetParent( newParent == null ? null : newParent._ladiesNumber );
		_genderPairs.SetParent( newParent == null ? null : newParent._genderPairs );
		_heroes.SetParent( newParent == null ? null : newParent._heroes );
		_ratingSpan.SetParent( newParent == null ? null : newParent._ratingSpan );
		_ratingPatternDelta.SetParent( newParent == null ? null : newParent._ratingPatternDelta );
		_ratingTeamAvgDelta.SetParent( newParent == null ? null : newParent._ratingTeamAvgDelta );
		_forceSpan.SetParent( newParent == null ? null : newParent._forceSpan );
		_heroClassesDifference.SetParent( newParent == null ? null : newParent._heroClassesDifference );
		_heroClassesOptimum.SetParent( newParent == null ? null : newParent._heroClassesOptimum );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ladiesNumber.Reset();
		_genderPairs.Reset();
		_heroes.Reset();
		_ratingSpan.Reset();
		_ratingPatternDelta.Reset();
		_ratingTeamAvgDelta.Reset();
		_forceSpan.Reset();
		_heroClassesDifference.Reset();
		_heroClassesOptimum.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ladiesNumber.IsDerivedFromParent()
			&& _genderPairs.IsDerivedFromParent()
			&& _heroes.IsDerivedFromParent()
			&& _ratingSpan.IsDerivedFromParent()
			&& _ratingPatternDelta.IsDerivedFromParent()
			&& _ratingTeamAvgDelta.IsDerivedFromParent()
			&& _forceSpan.IsDerivedFromParent()
			&& _heroClassesDifference.IsDerivedFromParent()
			&& _heroClassesOptimum.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ladiesNumber" )
			_ladiesNumber.Reset();
		else if ( fieldName == "genderPairs" )
			_genderPairs.Reset();
		else if ( fieldName == "heroes" )
			_heroes.Reset();
		else if ( fieldName == "ratingSpan" )
			_ratingSpan.Reset();
		else if ( fieldName == "ratingPatternDelta" )
			_ratingPatternDelta.Reset();
		else if ( fieldName == "ratingTeamAvgDelta" )
			_ratingTeamAvgDelta.Reset();
		else if ( fieldName == "forceSpan" )
			_forceSpan.Reset();
		else if ( fieldName == "heroClassesDifference" )
			_heroClassesDifference.Reset();
		else if ( fieldName == "heroClassesOptimum" )
			_heroClassesOptimum.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ladiesNumber" )
			return _ladiesNumber.IsDerivedFromParent();
		if ( fieldName == "genderPairs" )
			return _genderPairs.IsDerivedFromParent();
		if ( fieldName == "heroes" )
			return _heroes.IsDerivedFromParent();
		if ( fieldName == "ratingSpan" )
			return _ratingSpan.IsDerivedFromParent();
		if ( fieldName == "ratingPatternDelta" )
			return _ratingPatternDelta.IsDerivedFromParent();
		if ( fieldName == "ratingTeamAvgDelta" )
			return _ratingTeamAvgDelta.IsDerivedFromParent();
		if ( fieldName == "forceSpan" )
			return _forceSpan.IsDerivedFromParent();
		if ( fieldName == "heroClassesDifference" )
			return _heroClassesDifference.IsDerivedFromParent();
		if ( fieldName == "heroClassesOptimum" )
			return _heroClassesOptimum.IsDerivedFromParent();
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

[Custom("DBServer")]
public class FullPartyRatingModifier : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FullPartyRatingModifier __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _minRating;
	private UndoRedo<float> _ratingBonus;

	[Description( "Нижнее значение рейтинга героя" )]
	public int minRating { get { return _minRating.Get(); } set { _minRating.Set( value ); } }

	[Description( "Бонусный рейтинг" )]
	public float ratingBonus { get { return _ratingBonus.Get(); } set { _ratingBonus.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minRating = new UndoRedo<int>( owner, 0 );
		_ratingBonus = new UndoRedo<float>( owner, 0.0f );
		_minRating.Changed += FireChangedEvent;
		_ratingBonus.Changed += FireChangedEvent;
	}

	public FullPartyRatingModifier()
	{
		Initialize( GetOwner() );
	}

	public FullPartyRatingModifier( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FullPartyRatingModifier( DBResource owner, FullPartyRatingModifier source )
		: this(owner, source, true){}

	protected FullPartyRatingModifier( DBResource owner, FullPartyRatingModifier source, bool fireEvent )
	{
		_minRating = new UndoRedo<int>( owner, source.minRating );
		_ratingBonus = new UndoRedo<float>( owner, source.ratingBonus );
		_minRating.Changed += FireChangedEvent;
		_ratingBonus.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FullPartyRatingModifier source = _source as FullPartyRatingModifier;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FullPartyRatingModifier" );
		minRating = source.minRating;
		ratingBonus = source.ratingBonus;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FullPartyRatingModifier newParent = _newParent as FullPartyRatingModifier;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minRating.SetParent( newParent == null ? null : newParent._minRating );
		_ratingBonus.SetParent( newParent == null ? null : newParent._ratingBonus );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minRating.Reset();
		_ratingBonus.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minRating.IsDerivedFromParent()
			&& _ratingBonus.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minRating" )
			_minRating.Reset();
		else if ( fieldName == "ratingBonus" )
			_ratingBonus.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minRating" )
			return _minRating.IsDerivedFromParent();
		if ( fieldName == "ratingBonus" )
			return _ratingBonus.IsDerivedFromParent();
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
public class GuildLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<Int64> _requiredExp;
	private TextRef _title;
	private TextRef _tooltip;
	private UndoRedoAssignableList<DBPtr<GuildBonus>> _Bonuses;

	[Description( "requiredExp*GuildLevels.requiredExpMultiplier = суммарное количество ресурсов, необходимое для прокачки клана до уровня. В последний уровень не вписывать больше, чем 9 223 372 036 854 775 807 / Множитель" )]
	public Int64 requiredExp { get { return _requiredExp.Get(); } set { _requiredExp.Set( value ); } }

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<GuildBonus>> Bonuses { get { return _Bonuses; } set { _Bonuses.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_requiredExp = new UndoRedo<Int64>( owner, 0 );
		_title = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_Bonuses = new UndoRedoAssignableList<DBPtr<GuildBonus>>( owner );
		_requiredExp.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_Bonuses.Changed += FireChangedEvent;
	}

	public GuildLevel()
	{
		Initialize( GetOwner() );
	}

	public GuildLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildLevel( DBResource owner, GuildLevel source )
		: this(owner, source, true){}

	protected GuildLevel( DBResource owner, GuildLevel source, bool fireEvent )
	{
		_requiredExp = new UndoRedo<Int64>( owner, source.requiredExp );
		_title = new TextRef( owner, source.title );
		_tooltip = new TextRef( owner, source.tooltip );
		_Bonuses = new UndoRedoAssignableList<DBPtr<GuildBonus>>( owner );
		_Bonuses.Assign( source.Bonuses );
		_requiredExp.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_Bonuses.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildLevel source = _source as GuildLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildLevel" );
		requiredExp = source.requiredExp;
		title = source.title;
		tooltip = source.tooltip;
		Bonuses = source.Bonuses;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildLevel newParent = _newParent as GuildLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_requiredExp.SetParent( newParent == null ? null : newParent._requiredExp );
		_title.SetParent( newParent == null ? null : newParent._title );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_Bonuses.SetParent( newParent == null ? null : newParent._Bonuses );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_requiredExp.Reset();
		_title.Reset();
		_tooltip.Reset();
		_Bonuses.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_requiredExp.IsDerivedFromParent()
			&& _title.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _Bonuses.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "requiredExp" )
			_requiredExp.Reset();
		else if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "Bonuses" )
			_Bonuses.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "requiredExp" )
			return _requiredExp.IsDerivedFromParent();
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "Bonuses" )
			return _Bonuses.IsDerivedFromParent();
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

[Custom("DBServer")]
public class LerpDataItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LerpDataItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x;
	private UndoRedo<float> _y;

	[Description( "Независимая переменная" )]
	public float x { get { return _x.Get(); } set { _x.Set( value ); } }

	[Description( "Зависимая переменная" )]
	public float y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<float>( owner, 0.0f );
		_y = new UndoRedo<float>( owner, 0.0f );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public LerpDataItem()
	{
		Initialize( GetOwner() );
	}

	public LerpDataItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LerpDataItem( DBResource owner, LerpDataItem source )
		: this(owner, source, true){}

	protected LerpDataItem( DBResource owner, LerpDataItem source, bool fireEvent )
	{
		_x = new UndoRedo<float>( owner, source.x );
		_y = new UndoRedo<float>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LerpDataItem source = _source as LerpDataItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LerpDataItem" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LerpDataItem newParent = _newParent as LerpDataItem;
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

[Custom("DBServer")]
[DBVersion(1)]
[IndexField("heroClass")]
public class MMakingHeroClass : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingHeroClass __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minEfficiency;
	private UndoRedo<float> _maxEfficiency;

	public float minEfficiency { get { return _minEfficiency.Get(); } set { _minEfficiency.Set( value ); } }

	public float maxEfficiency { get { return _maxEfficiency.Get(); } set { _maxEfficiency.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minEfficiency = new UndoRedo<float>( owner, 1.0f );
		_maxEfficiency = new UndoRedo<float>( owner, 1.0f );
		_minEfficiency.Changed += FireChangedEvent;
		_maxEfficiency.Changed += FireChangedEvent;
	}

	public MMakingHeroClass()
	{
		Initialize( GetOwner() );
	}

	public MMakingHeroClass( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingHeroClass( DBResource owner, MMakingHeroClass source )
		: this(owner, source, true){}

	protected MMakingHeroClass( DBResource owner, MMakingHeroClass source, bool fireEvent )
	{
		_minEfficiency = new UndoRedo<float>( owner, source.minEfficiency );
		_maxEfficiency = new UndoRedo<float>( owner, source.maxEfficiency );
		_minEfficiency.Changed += FireChangedEvent;
		_maxEfficiency.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingHeroClass source = _source as MMakingHeroClass;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingHeroClass" );
		minEfficiency = source.minEfficiency;
		maxEfficiency = source.maxEfficiency;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingHeroClass newParent = _newParent as MMakingHeroClass;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minEfficiency.SetParent( newParent == null ? null : newParent._minEfficiency );
		_maxEfficiency.SetParent( newParent == null ? null : newParent._maxEfficiency );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minEfficiency.Reset();
		_maxEfficiency.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minEfficiency.IsDerivedFromParent()
			&& _maxEfficiency.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minEfficiency" )
			_minEfficiency.Reset();
		else if ( fieldName == "maxEfficiency" )
			_maxEfficiency.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minEfficiency" )
			return _minEfficiency.IsDerivedFromParent();
		if ( fieldName == "maxEfficiency" )
			return _maxEfficiency.IsDerivedFromParent();
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

[Custom("DBServer")]
public class MMakingLocationPingSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingLocationPingSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _nicePingThreshold;
	private UndoRedo<float> _pingScaleMinFactor;
	private UndoRedo<int> _worstPingWaitTimePenalty;
	private UndoRedo<float> _goodEnoughPingFactor;
	private UndoRedo<int> _ratingThreshold;

	[Description( "Все пинги ниже этого порога будут считаться хорошими" )]
	public int nicePingThreshold { get { return _nicePingThreshold.Get(); } set { _nicePingThreshold.Set( value ); } }

	[Description( "Минимальный масштаб относительной шкалы пингов" )]
	public float pingScaleMinFactor { get { return _pingScaleMinFactor.Get(); } set { _pingScaleMinFactor.Set( value ); } }

	[Description( "Добавка к времени ожидания для худших пингов" )]
	public int worstPingWaitTimePenalty { get { return _worstPingWaitTimePenalty.Get(); } set { _worstPingWaitTimePenalty.Set( value ); } }

	[Description( "Планка для выбора лучшего пинга из доступных" )]
	public float goodEnoughPingFactor { get { return _goodEnoughPingFactor.Get(); } set { _goodEnoughPingFactor.Set( value ); } }

	[Description( "Порог рейтинга, после которого не работают ограничения про пинги и локали" )]
	public int ratingThreshold { get { return _ratingThreshold.Get(); } set { _ratingThreshold.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_nicePingThreshold = new UndoRedo<int>( owner, 40 );
		_pingScaleMinFactor = new UndoRedo<float>( owner, 2.0f );
		_worstPingWaitTimePenalty = new UndoRedo<int>( owner, 180 );
		_goodEnoughPingFactor = new UndoRedo<float>( owner, 0.2f );
		_ratingThreshold = new UndoRedo<int>( owner, 1800 );
		_nicePingThreshold.Changed += FireChangedEvent;
		_pingScaleMinFactor.Changed += FireChangedEvent;
		_worstPingWaitTimePenalty.Changed += FireChangedEvent;
		_goodEnoughPingFactor.Changed += FireChangedEvent;
		_ratingThreshold.Changed += FireChangedEvent;
	}

	public MMakingLocationPingSettings()
	{
		Initialize( GetOwner() );
	}

	public MMakingLocationPingSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingLocationPingSettings( DBResource owner, MMakingLocationPingSettings source )
		: this(owner, source, true){}

	protected MMakingLocationPingSettings( DBResource owner, MMakingLocationPingSettings source, bool fireEvent )
	{
		_nicePingThreshold = new UndoRedo<int>( owner, source.nicePingThreshold );
		_pingScaleMinFactor = new UndoRedo<float>( owner, source.pingScaleMinFactor );
		_worstPingWaitTimePenalty = new UndoRedo<int>( owner, source.worstPingWaitTimePenalty );
		_goodEnoughPingFactor = new UndoRedo<float>( owner, source.goodEnoughPingFactor );
		_ratingThreshold = new UndoRedo<int>( owner, source.ratingThreshold );
		_nicePingThreshold.Changed += FireChangedEvent;
		_pingScaleMinFactor.Changed += FireChangedEvent;
		_worstPingWaitTimePenalty.Changed += FireChangedEvent;
		_goodEnoughPingFactor.Changed += FireChangedEvent;
		_ratingThreshold.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingLocationPingSettings source = _source as MMakingLocationPingSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingLocationPingSettings" );
		nicePingThreshold = source.nicePingThreshold;
		pingScaleMinFactor = source.pingScaleMinFactor;
		worstPingWaitTimePenalty = source.worstPingWaitTimePenalty;
		goodEnoughPingFactor = source.goodEnoughPingFactor;
		ratingThreshold = source.ratingThreshold;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingLocationPingSettings newParent = _newParent as MMakingLocationPingSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_nicePingThreshold.SetParent( newParent == null ? null : newParent._nicePingThreshold );
		_pingScaleMinFactor.SetParent( newParent == null ? null : newParent._pingScaleMinFactor );
		_worstPingWaitTimePenalty.SetParent( newParent == null ? null : newParent._worstPingWaitTimePenalty );
		_goodEnoughPingFactor.SetParent( newParent == null ? null : newParent._goodEnoughPingFactor );
		_ratingThreshold.SetParent( newParent == null ? null : newParent._ratingThreshold );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_nicePingThreshold.Reset();
		_pingScaleMinFactor.Reset();
		_worstPingWaitTimePenalty.Reset();
		_goodEnoughPingFactor.Reset();
		_ratingThreshold.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_nicePingThreshold.IsDerivedFromParent()
			&& _pingScaleMinFactor.IsDerivedFromParent()
			&& _worstPingWaitTimePenalty.IsDerivedFromParent()
			&& _goodEnoughPingFactor.IsDerivedFromParent()
			&& _ratingThreshold.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "nicePingThreshold" )
			_nicePingThreshold.Reset();
		else if ( fieldName == "pingScaleMinFactor" )
			_pingScaleMinFactor.Reset();
		else if ( fieldName == "worstPingWaitTimePenalty" )
			_worstPingWaitTimePenalty.Reset();
		else if ( fieldName == "goodEnoughPingFactor" )
			_goodEnoughPingFactor.Reset();
		else if ( fieldName == "ratingThreshold" )
			_ratingThreshold.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "nicePingThreshold" )
			return _nicePingThreshold.IsDerivedFromParent();
		if ( fieldName == "pingScaleMinFactor" )
			return _pingScaleMinFactor.IsDerivedFromParent();
		if ( fieldName == "worstPingWaitTimePenalty" )
			return _worstPingWaitTimePenalty.IsDerivedFromParent();
		if ( fieldName == "goodEnoughPingFactor" )
			return _goodEnoughPingFactor.IsDerivedFromParent();
		if ( fieldName == "ratingThreshold" )
			return _ratingThreshold.IsDerivedFromParent();
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

[Custom("DBServer")]
public class MMakingLoseStreakCorrection : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingLoseStreakCorrection __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _minStreak;
	private UndoRedo<float> _forcePenalty;
	private UndoRedo<float> _ratingPenalty;
	private UndoRedo<int> _firstCaseThreshold;
	private UndoRedo<float> _firstCasePenalty;
	private UndoRedo<int> _secondCaseThreshold;
	private UndoRedo<float> _secondCasePenalty;
	private UndoRedo<int> _thirdCaseThreshold;
	private UndoRedo<float> _thirdCasePenalty;

	[Description( "Минимальное количество проигрышей подряд, с которого начинает работать механизм коррекции" )]
	public int minStreak { get { return _minStreak.Get(); } set { _minStreak.Set( value ); } }

	[Description( "Штраф форса за каждое последующее поражение" )]
	public float forcePenalty { get { return _forcePenalty.Get(); } set { _forcePenalty.Set( value ); } }

	[Description( "Штраф рейтинга за каждое последующее поражение" )]
	public float ratingPenalty { get { return _ratingPenalty.Get(); } set { _ratingPenalty.Set( value ); } }

	public int firstCaseThreshold { get { return _firstCaseThreshold.Get(); } set { _firstCaseThreshold.Set( value ); } }

	public float firstCasePenalty { get { return _firstCasePenalty.Get(); } set { _firstCasePenalty.Set( value ); } }

	public int secondCaseThreshold { get { return _secondCaseThreshold.Get(); } set { _secondCaseThreshold.Set( value ); } }

	public float secondCasePenalty { get { return _secondCasePenalty.Get(); } set { _secondCasePenalty.Set( value ); } }

	public int thirdCaseThreshold { get { return _thirdCaseThreshold.Get(); } set { _thirdCaseThreshold.Set( value ); } }

	public float thirdCasePenalty { get { return _thirdCasePenalty.Get(); } set { _thirdCasePenalty.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minStreak = new UndoRedo<int>( owner, 2 );
		_forcePenalty = new UndoRedo<float>( owner, 5.0f );
		_ratingPenalty = new UndoRedo<float>( owner, 100.0f );
		_firstCaseThreshold = new UndoRedo<int>( owner, 2 );
		_firstCasePenalty = new UndoRedo<float>( owner, 0.25f );
		_secondCaseThreshold = new UndoRedo<int>( owner, 3 );
		_secondCasePenalty = new UndoRedo<float>( owner, 0.5f );
		_thirdCaseThreshold = new UndoRedo<int>( owner, 5 );
		_thirdCasePenalty = new UndoRedo<float>( owner, 1.0f );
		_minStreak.Changed += FireChangedEvent;
		_forcePenalty.Changed += FireChangedEvent;
		_ratingPenalty.Changed += FireChangedEvent;
		_firstCaseThreshold.Changed += FireChangedEvent;
		_firstCasePenalty.Changed += FireChangedEvent;
		_secondCaseThreshold.Changed += FireChangedEvent;
		_secondCasePenalty.Changed += FireChangedEvent;
		_thirdCaseThreshold.Changed += FireChangedEvent;
		_thirdCasePenalty.Changed += FireChangedEvent;
	}

	public MMakingLoseStreakCorrection()
	{
		Initialize( GetOwner() );
	}

	public MMakingLoseStreakCorrection( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingLoseStreakCorrection( DBResource owner, MMakingLoseStreakCorrection source )
		: this(owner, source, true){}

	protected MMakingLoseStreakCorrection( DBResource owner, MMakingLoseStreakCorrection source, bool fireEvent )
	{
		_minStreak = new UndoRedo<int>( owner, source.minStreak );
		_forcePenalty = new UndoRedo<float>( owner, source.forcePenalty );
		_ratingPenalty = new UndoRedo<float>( owner, source.ratingPenalty );
		_firstCaseThreshold = new UndoRedo<int>( owner, source.firstCaseThreshold );
		_firstCasePenalty = new UndoRedo<float>( owner, source.firstCasePenalty );
		_secondCaseThreshold = new UndoRedo<int>( owner, source.secondCaseThreshold );
		_secondCasePenalty = new UndoRedo<float>( owner, source.secondCasePenalty );
		_thirdCaseThreshold = new UndoRedo<int>( owner, source.thirdCaseThreshold );
		_thirdCasePenalty = new UndoRedo<float>( owner, source.thirdCasePenalty );
		_minStreak.Changed += FireChangedEvent;
		_forcePenalty.Changed += FireChangedEvent;
		_ratingPenalty.Changed += FireChangedEvent;
		_firstCaseThreshold.Changed += FireChangedEvent;
		_firstCasePenalty.Changed += FireChangedEvent;
		_secondCaseThreshold.Changed += FireChangedEvent;
		_secondCasePenalty.Changed += FireChangedEvent;
		_thirdCaseThreshold.Changed += FireChangedEvent;
		_thirdCasePenalty.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingLoseStreakCorrection source = _source as MMakingLoseStreakCorrection;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingLoseStreakCorrection" );
		minStreak = source.minStreak;
		forcePenalty = source.forcePenalty;
		ratingPenalty = source.ratingPenalty;
		firstCaseThreshold = source.firstCaseThreshold;
		firstCasePenalty = source.firstCasePenalty;
		secondCaseThreshold = source.secondCaseThreshold;
		secondCasePenalty = source.secondCasePenalty;
		thirdCaseThreshold = source.thirdCaseThreshold;
		thirdCasePenalty = source.thirdCasePenalty;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingLoseStreakCorrection newParent = _newParent as MMakingLoseStreakCorrection;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minStreak.SetParent( newParent == null ? null : newParent._minStreak );
		_forcePenalty.SetParent( newParent == null ? null : newParent._forcePenalty );
		_ratingPenalty.SetParent( newParent == null ? null : newParent._ratingPenalty );
		_firstCaseThreshold.SetParent( newParent == null ? null : newParent._firstCaseThreshold );
		_firstCasePenalty.SetParent( newParent == null ? null : newParent._firstCasePenalty );
		_secondCaseThreshold.SetParent( newParent == null ? null : newParent._secondCaseThreshold );
		_secondCasePenalty.SetParent( newParent == null ? null : newParent._secondCasePenalty );
		_thirdCaseThreshold.SetParent( newParent == null ? null : newParent._thirdCaseThreshold );
		_thirdCasePenalty.SetParent( newParent == null ? null : newParent._thirdCasePenalty );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minStreak.Reset();
		_forcePenalty.Reset();
		_ratingPenalty.Reset();
		_firstCaseThreshold.Reset();
		_firstCasePenalty.Reset();
		_secondCaseThreshold.Reset();
		_secondCasePenalty.Reset();
		_thirdCaseThreshold.Reset();
		_thirdCasePenalty.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minStreak.IsDerivedFromParent()
			&& _forcePenalty.IsDerivedFromParent()
			&& _ratingPenalty.IsDerivedFromParent()
			&& _firstCaseThreshold.IsDerivedFromParent()
			&& _firstCasePenalty.IsDerivedFromParent()
			&& _secondCaseThreshold.IsDerivedFromParent()
			&& _secondCasePenalty.IsDerivedFromParent()
			&& _thirdCaseThreshold.IsDerivedFromParent()
			&& _thirdCasePenalty.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minStreak" )
			_minStreak.Reset();
		else if ( fieldName == "forcePenalty" )
			_forcePenalty.Reset();
		else if ( fieldName == "ratingPenalty" )
			_ratingPenalty.Reset();
		else if ( fieldName == "firstCaseThreshold" )
			_firstCaseThreshold.Reset();
		else if ( fieldName == "firstCasePenalty" )
			_firstCasePenalty.Reset();
		else if ( fieldName == "secondCaseThreshold" )
			_secondCaseThreshold.Reset();
		else if ( fieldName == "secondCasePenalty" )
			_secondCasePenalty.Reset();
		else if ( fieldName == "thirdCaseThreshold" )
			_thirdCaseThreshold.Reset();
		else if ( fieldName == "thirdCasePenalty" )
			_thirdCasePenalty.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minStreak" )
			return _minStreak.IsDerivedFromParent();
		if ( fieldName == "forcePenalty" )
			return _forcePenalty.IsDerivedFromParent();
		if ( fieldName == "ratingPenalty" )
			return _ratingPenalty.IsDerivedFromParent();
		if ( fieldName == "firstCaseThreshold" )
			return _firstCaseThreshold.IsDerivedFromParent();
		if ( fieldName == "firstCasePenalty" )
			return _firstCasePenalty.IsDerivedFromParent();
		if ( fieldName == "secondCaseThreshold" )
			return _secondCaseThreshold.IsDerivedFromParent();
		if ( fieldName == "secondCasePenalty" )
			return _secondCasePenalty.IsDerivedFromParent();
		if ( fieldName == "thirdCaseThreshold" )
			return _thirdCaseThreshold.IsDerivedFromParent();
		if ( fieldName == "thirdCasePenalty" )
			return _thirdCasePenalty.IsDerivedFromParent();
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

[Custom("DBServer")]
public class MMakingRank : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingRank __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _lowRating;
	private UndoRedo<bool> _mergeWithNextRank;
	private UndoRedo<int> _mergeRanksCount;
	private UndoRedo<string> _debugName;
	private UndoRedo<bool> _useForceMM;
	private UndoRedo<bool> _usePlayerRatingMM;

	[Description( "Минимальный рейтинг" )]
	public float lowRating { get { return _lowRating.Get(); } set { _lowRating.Set( value ); } }

	[Description( "Объединено ли данное звание со следующим" )]
	public bool mergeWithNextRank { get { return _mergeWithNextRank.Get(); } set { _mergeWithNextRank.Set( value ); } }

	[Description( "Дизайнер, будь внимателен, думай головой и смотри на mergeWithNextRank тоже!" )]
	public int mergeRanksCount { get { return _mergeRanksCount.Get(); } set { _mergeRanksCount.Set( value ); } }

	[Description( "Имя для отображения в логах" )]
	public string debugName { get { return _debugName.Get(); } set { _debugName.Set( value ); } }

	[Description( "Надо ли использовать проверку на мощь на данном звании" )]
	public bool useForceMM { get { return _useForceMM.Get(); } set { _useForceMM.Set( value ); } }

	[Description( "Надо ли использовать проверку на пользовательский рейтинг на данном звании" )]
	public bool usePlayerRatingMM { get { return _usePlayerRatingMM.Get(); } set { _usePlayerRatingMM.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lowRating = new UndoRedo<float>( owner, 0.0f );
		_mergeWithNextRank = new UndoRedo<bool>( owner, false );
		_mergeRanksCount = new UndoRedo<int>( owner, 0 );
		_debugName = new UndoRedo<string>( owner, string.Empty );
		_useForceMM = new UndoRedo<bool>( owner, false );
		_usePlayerRatingMM = new UndoRedo<bool>( owner, false );
		_lowRating.Changed += FireChangedEvent;
		_mergeWithNextRank.Changed += FireChangedEvent;
		_mergeRanksCount.Changed += FireChangedEvent;
		_debugName.Changed += FireChangedEvent;
		_useForceMM.Changed += FireChangedEvent;
		_usePlayerRatingMM.Changed += FireChangedEvent;
	}

	public MMakingRank()
	{
		Initialize( GetOwner() );
	}

	public MMakingRank( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingRank( DBResource owner, MMakingRank source )
		: this(owner, source, true){}

	protected MMakingRank( DBResource owner, MMakingRank source, bool fireEvent )
	{
		_lowRating = new UndoRedo<float>( owner, source.lowRating );
		_mergeWithNextRank = new UndoRedo<bool>( owner, source.mergeWithNextRank );
		_mergeRanksCount = new UndoRedo<int>( owner, source.mergeRanksCount );
		_debugName = new UndoRedo<string>( owner, source.debugName );
		_useForceMM = new UndoRedo<bool>( owner, source.useForceMM );
		_usePlayerRatingMM = new UndoRedo<bool>( owner, source.usePlayerRatingMM );
		_lowRating.Changed += FireChangedEvent;
		_mergeWithNextRank.Changed += FireChangedEvent;
		_mergeRanksCount.Changed += FireChangedEvent;
		_debugName.Changed += FireChangedEvent;
		_useForceMM.Changed += FireChangedEvent;
		_usePlayerRatingMM.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingRank source = _source as MMakingRank;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingRank" );
		lowRating = source.lowRating;
		mergeWithNextRank = source.mergeWithNextRank;
		mergeRanksCount = source.mergeRanksCount;
		debugName = source.debugName;
		useForceMM = source.useForceMM;
		usePlayerRatingMM = source.usePlayerRatingMM;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingRank newParent = _newParent as MMakingRank;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lowRating.SetParent( newParent == null ? null : newParent._lowRating );
		_mergeWithNextRank.SetParent( newParent == null ? null : newParent._mergeWithNextRank );
		_mergeRanksCount.SetParent( newParent == null ? null : newParent._mergeRanksCount );
		_debugName.SetParent( newParent == null ? null : newParent._debugName );
		_useForceMM.SetParent( newParent == null ? null : newParent._useForceMM );
		_usePlayerRatingMM.SetParent( newParent == null ? null : newParent._usePlayerRatingMM );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lowRating.Reset();
		_mergeWithNextRank.Reset();
		_mergeRanksCount.Reset();
		_debugName.Reset();
		_useForceMM.Reset();
		_usePlayerRatingMM.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lowRating.IsDerivedFromParent()
			&& _mergeWithNextRank.IsDerivedFromParent()
			&& _mergeRanksCount.IsDerivedFromParent()
			&& _debugName.IsDerivedFromParent()
			&& _useForceMM.IsDerivedFromParent()
			&& _usePlayerRatingMM.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lowRating" )
			_lowRating.Reset();
		else if ( fieldName == "mergeWithNextRank" )
			_mergeWithNextRank.Reset();
		else if ( fieldName == "mergeRanksCount" )
			_mergeRanksCount.Reset();
		else if ( fieldName == "debugName" )
			_debugName.Reset();
		else if ( fieldName == "useForceMM" )
			_useForceMM.Reset();
		else if ( fieldName == "usePlayerRatingMM" )
			_usePlayerRatingMM.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lowRating" )
			return _lowRating.IsDerivedFromParent();
		if ( fieldName == "mergeWithNextRank" )
			return _mergeWithNextRank.IsDerivedFromParent();
		if ( fieldName == "mergeRanksCount" )
			return _mergeRanksCount.IsDerivedFromParent();
		if ( fieldName == "debugName" )
			return _debugName.IsDerivedFromParent();
		if ( fieldName == "useForceMM" )
			return _useForceMM.IsDerivedFromParent();
		if ( fieldName == "usePlayerRatingMM" )
			return _usePlayerRatingMM.IsDerivedFromParent();
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

[Custom("DBServer")]
[DBVersion(1)]
public class MMakingScale : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingScale __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _low;
	private UndoRedo<int> _high;
	private UndoRedo<int> _step;
	private UndoRedoAssignableList<LerpDataItem> _diffLow;
	private UndoRedoAssignableList<LerpDataItem> _diffHigh;

	[Description( "Нижняя граница шкалы" )]
	public int low { get { return _low.Get(); } set { _low.Set( value ); } }

	[Description( "Верхняя граница шкалы" )]
	public int high { get { return _high.Get(); } set { _high.Set( value ); } }

	[Description( "Шаг приращения" )]
	public int step { get { return _step.Get(); } set { _step.Set( value ); } }

	[Description( "Начальная допустимая разница параметра при формировании выборки; Задается кусочно линнейной интерполяцией" )]
	public libdb.IChangeableList<LerpDataItem> diffLow { get { return _diffLow; } set { _diffLow.Assign( value ); } }

	[Description( "Максимальная допустимая разница параметра при формировании выборки; Задается кусочно линнейной интерполяцией" )]
	public libdb.IChangeableList<LerpDataItem> diffHigh { get { return _diffHigh; } set { _diffHigh.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_low = new UndoRedo<int>( owner, 100 );
		_high = new UndoRedo<int>( owner, 1000 );
		_step = new UndoRedo<int>( owner, 20 );
		_diffLow = new UndoRedoAssignableList<LerpDataItem>( owner );
		_diffHigh = new UndoRedoAssignableList<LerpDataItem>( owner );
		_low.Changed += FireChangedEvent;
		_high.Changed += FireChangedEvent;
		_step.Changed += FireChangedEvent;
		_diffLow.Changed += FireChangedEvent;
		_diffHigh.Changed += FireChangedEvent;
	}

	public MMakingScale()
	{
		Initialize( GetOwner() );
	}

	public MMakingScale( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingScale( DBResource owner, MMakingScale source )
		: this(owner, source, true){}

	protected MMakingScale( DBResource owner, MMakingScale source, bool fireEvent )
	{
		_low = new UndoRedo<int>( owner, source.low );
		_high = new UndoRedo<int>( owner, source.high );
		_step = new UndoRedo<int>( owner, source.step );
		_diffLow = new UndoRedoAssignableList<LerpDataItem>( owner );
		_diffLow.Assign( source.diffLow );
		_diffHigh = new UndoRedoAssignableList<LerpDataItem>( owner );
		_diffHigh.Assign( source.diffHigh );
		_low.Changed += FireChangedEvent;
		_high.Changed += FireChangedEvent;
		_step.Changed += FireChangedEvent;
		_diffLow.Changed += FireChangedEvent;
		_diffHigh.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingScale source = _source as MMakingScale;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingScale" );
		low = source.low;
		high = source.high;
		step = source.step;
		diffLow = source.diffLow;
		diffHigh = source.diffHigh;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingScale newParent = _newParent as MMakingScale;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_low.SetParent( newParent == null ? null : newParent._low );
		_high.SetParent( newParent == null ? null : newParent._high );
		_step.SetParent( newParent == null ? null : newParent._step );
		_diffLow.SetParent( newParent == null ? null : newParent._diffLow );
		_diffHigh.SetParent( newParent == null ? null : newParent._diffHigh );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_low.Reset();
		_high.Reset();
		_step.Reset();
		_diffLow.Reset();
		_diffHigh.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_low.IsDerivedFromParent()
			&& _high.IsDerivedFromParent()
			&& _step.IsDerivedFromParent()
			&& _diffLow.IsDerivedFromParent()
			&& _diffHigh.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "low" )
			_low.Reset();
		else if ( fieldName == "high" )
			_high.Reset();
		else if ( fieldName == "step" )
			_step.Reset();
		else if ( fieldName == "diffLow" )
			_diffLow.Reset();
		else if ( fieldName == "diffHigh" )
			_diffHigh.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "low" )
			return _low.IsDerivedFromParent();
		if ( fieldName == "high" )
			return _high.IsDerivedFromParent();
		if ( fieldName == "step" )
			return _step.IsDerivedFromParent();
		if ( fieldName == "diffLow" )
			return _diffLow.IsDerivedFromParent();
		if ( fieldName == "diffHigh" )
			return _diffHigh.IsDerivedFromParent();
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

[Custom("DBServer")]
public class MMakingWaitVsProbability : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MMakingWaitVsProbability __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _startingWaitTime;
	private UndoRedo<float> _endingWaitTime;
	private UndoRedo<int> _startingProbabilityWeight;
	private UndoRedo<int> _endingProbabilityWeight;

	[Description( "Время начала линейного участка, сек" )]
	public float startingWaitTime { get { return _startingWaitTime.Get(); } set { _startingWaitTime.Set( value ); } }

	[Description( "Время окончания линейного участка, сек" )]
	public float endingWaitTime { get { return _endingWaitTime.Get(); } set { _endingWaitTime.Set( value ); } }

	[Description( "Вероятность (вес) в начале линейного участка. Веса нормируются по всем участникам выборки" )]
	public int startingProbabilityWeight { get { return _startingProbabilityWeight.Get(); } set { _startingProbabilityWeight.Set( value ); } }

	[Description( "Вероятность (вес) в конце линейного участка. Веса нормируются по всем участникам выборки" )]
	public int endingProbabilityWeight { get { return _endingProbabilityWeight.Get(); } set { _endingProbabilityWeight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_startingWaitTime = new UndoRedo<float>( owner, 15.0f );
		_endingWaitTime = new UndoRedo<float>( owner, 180.0f );
		_startingProbabilityWeight = new UndoRedo<int>( owner, 100 );
		_endingProbabilityWeight = new UndoRedo<int>( owner, 300 );
		_startingWaitTime.Changed += FireChangedEvent;
		_endingWaitTime.Changed += FireChangedEvent;
		_startingProbabilityWeight.Changed += FireChangedEvent;
		_endingProbabilityWeight.Changed += FireChangedEvent;
	}

	public MMakingWaitVsProbability()
	{
		Initialize( GetOwner() );
	}

	public MMakingWaitVsProbability( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MMakingWaitVsProbability( DBResource owner, MMakingWaitVsProbability source )
		: this(owner, source, true){}

	protected MMakingWaitVsProbability( DBResource owner, MMakingWaitVsProbability source, bool fireEvent )
	{
		_startingWaitTime = new UndoRedo<float>( owner, source.startingWaitTime );
		_endingWaitTime = new UndoRedo<float>( owner, source.endingWaitTime );
		_startingProbabilityWeight = new UndoRedo<int>( owner, source.startingProbabilityWeight );
		_endingProbabilityWeight = new UndoRedo<int>( owner, source.endingProbabilityWeight );
		_startingWaitTime.Changed += FireChangedEvent;
		_endingWaitTime.Changed += FireChangedEvent;
		_startingProbabilityWeight.Changed += FireChangedEvent;
		_endingProbabilityWeight.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MMakingWaitVsProbability source = _source as MMakingWaitVsProbability;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MMakingWaitVsProbability" );
		startingWaitTime = source.startingWaitTime;
		endingWaitTime = source.endingWaitTime;
		startingProbabilityWeight = source.startingProbabilityWeight;
		endingProbabilityWeight = source.endingProbabilityWeight;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MMakingWaitVsProbability newParent = _newParent as MMakingWaitVsProbability;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_startingWaitTime.SetParent( newParent == null ? null : newParent._startingWaitTime );
		_endingWaitTime.SetParent( newParent == null ? null : newParent._endingWaitTime );
		_startingProbabilityWeight.SetParent( newParent == null ? null : newParent._startingProbabilityWeight );
		_endingProbabilityWeight.SetParent( newParent == null ? null : newParent._endingProbabilityWeight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_startingWaitTime.Reset();
		_endingWaitTime.Reset();
		_startingProbabilityWeight.Reset();
		_endingProbabilityWeight.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_startingWaitTime.IsDerivedFromParent()
			&& _endingWaitTime.IsDerivedFromParent()
			&& _startingProbabilityWeight.IsDerivedFromParent()
			&& _endingProbabilityWeight.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "startingWaitTime" )
			_startingWaitTime.Reset();
		else if ( fieldName == "endingWaitTime" )
			_endingWaitTime.Reset();
		else if ( fieldName == "startingProbabilityWeight" )
			_startingProbabilityWeight.Reset();
		else if ( fieldName == "endingProbabilityWeight" )
			_endingProbabilityWeight.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "startingWaitTime" )
			return _startingWaitTime.IsDerivedFromParent();
		if ( fieldName == "endingWaitTime" )
			return _endingWaitTime.IsDerivedFromParent();
		if ( fieldName == "startingProbabilityWeight" )
			return _startingProbabilityWeight.IsDerivedFromParent();
		if ( fieldName == "endingProbabilityWeight" )
			return _endingProbabilityWeight.IsDerivedFromParent();
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

[Custom("DBServer")]
public class PointsToContainers : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PointsToContainers __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _specialPoints;
	private UndoRedo<int> _containers;

	[Description( "Кол-во спец очков" )]
	public int specialPoints { get { return _specialPoints.Get(); } set { _specialPoints.Set( value ); } }

	[Description( "Сколько контейнеров давать за указанные очки" )]
	public int containers { get { return _containers.Get(); } set { _containers.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_specialPoints = new UndoRedo<int>( owner, 0 );
		_containers = new UndoRedo<int>( owner, 0 );
		_specialPoints.Changed += FireChangedEvent;
		_containers.Changed += FireChangedEvent;
	}

	public PointsToContainers()
	{
		Initialize( GetOwner() );
	}

	public PointsToContainers( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PointsToContainers( DBResource owner, PointsToContainers source )
		: this(owner, source, true){}

	protected PointsToContainers( DBResource owner, PointsToContainers source, bool fireEvent )
	{
		_specialPoints = new UndoRedo<int>( owner, source.specialPoints );
		_containers = new UndoRedo<int>( owner, source.containers );
		_specialPoints.Changed += FireChangedEvent;
		_containers.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PointsToContainers source = _source as PointsToContainers;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PointsToContainers" );
		specialPoints = source.specialPoints;
		containers = source.containers;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PointsToContainers newParent = _newParent as PointsToContainers;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_specialPoints.SetParent( newParent == null ? null : newParent._specialPoints );
		_containers.SetParent( newParent == null ? null : newParent._containers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_specialPoints.Reset();
		_containers.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_specialPoints.IsDerivedFromParent()
			&& _containers.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "specialPoints" )
			_specialPoints.Reset();
		else if ( fieldName == "containers" )
			_containers.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "specialPoints" )
			return _specialPoints.IsDerivedFromParent();
		if ( fieldName == "containers" )
			return _containers.IsDerivedFromParent();
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

[Custom("DBServer")]
public class RatingModifier : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RatingModifier __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _minValue;
	private UndoRedo<int> _maxValue;
	private UndoRedo<float> _winModifier;
	private UndoRedo<float> _looseModifier;

	[Description( "Нижнее значение рейтинга героя" )]
	public int minValue { get { return _minValue.Get(); } set { _minValue.Set( value ); } }

	[Description( "Верхнее значение рейтинга героя" )]
	public int maxValue { get { return _maxValue.Get(); } set { _maxValue.Set( value ); } }

	[Description( "Множитель в случае победы" )]
	public float winModifier { get { return _winModifier.Get(); } set { _winModifier.Set( value ); } }

	[Description( "Множитель в случае поражения" )]
	public float looseModifier { get { return _looseModifier.Get(); } set { _looseModifier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minValue = new UndoRedo<int>( owner, 0 );
		_maxValue = new UndoRedo<int>( owner, 0 );
		_winModifier = new UndoRedo<float>( owner, 0.0f );
		_looseModifier = new UndoRedo<float>( owner, 0.0f );
		_minValue.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
		_winModifier.Changed += FireChangedEvent;
		_looseModifier.Changed += FireChangedEvent;
	}

	public RatingModifier()
	{
		Initialize( GetOwner() );
	}

	public RatingModifier( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RatingModifier( DBResource owner, RatingModifier source )
		: this(owner, source, true){}

	protected RatingModifier( DBResource owner, RatingModifier source, bool fireEvent )
	{
		_minValue = new UndoRedo<int>( owner, source.minValue );
		_maxValue = new UndoRedo<int>( owner, source.maxValue );
		_winModifier = new UndoRedo<float>( owner, source.winModifier );
		_looseModifier = new UndoRedo<float>( owner, source.looseModifier );
		_minValue.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
		_winModifier.Changed += FireChangedEvent;
		_looseModifier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RatingModifier source = _source as RatingModifier;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RatingModifier" );
		minValue = source.minValue;
		maxValue = source.maxValue;
		winModifier = source.winModifier;
		looseModifier = source.looseModifier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RatingModifier newParent = _newParent as RatingModifier;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minValue.SetParent( newParent == null ? null : newParent._minValue );
		_maxValue.SetParent( newParent == null ? null : newParent._maxValue );
		_winModifier.SetParent( newParent == null ? null : newParent._winModifier );
		_looseModifier.SetParent( newParent == null ? null : newParent._looseModifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minValue.Reset();
		_maxValue.Reset();
		_winModifier.Reset();
		_looseModifier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minValue.IsDerivedFromParent()
			&& _maxValue.IsDerivedFromParent()
			&& _winModifier.IsDerivedFromParent()
			&& _looseModifier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minValue" )
			_minValue.Reset();
		else if ( fieldName == "maxValue" )
			_maxValue.Reset();
		else if ( fieldName == "winModifier" )
			_winModifier.Reset();
		else if ( fieldName == "looseModifier" )
			_looseModifier.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minValue" )
			return _minValue.IsDerivedFromParent();
		if ( fieldName == "maxValue" )
			return _maxValue.IsDerivedFromParent();
		if ( fieldName == "winModifier" )
			return _winModifier.IsDerivedFromParent();
		if ( fieldName == "looseModifier" )
			return _looseModifier.IsDerivedFromParent();
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

[Custom("DBServer")]
public class RecessionData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RecessionData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<float> _recessionTable;
	private UndoRedo<bool> _isWaitingTimePremium;

	[Description( "Таблица разлетов прохода,нумерацию начинаем с нуля, но считаем что 0 это 1, 1 это 2 и т.д. " )]
	public libdb.IChangeableList<float> recessionTable { get { return _recessionTable; } set { _recessionTable.Assign( value ); } }

	[Description( "Использовать добавку за время ожидания" )]
	public bool isWaitingTimePremium { get { return _isWaitingTimePremium.Get(); } set { _isWaitingTimePremium.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_recessionTable = new UndoRedoList<float>( owner );
		_isWaitingTimePremium = new UndoRedo<bool>( owner, true );
		_recessionTable.Changed += FireChangedEvent;
		_isWaitingTimePremium.Changed += FireChangedEvent;
	}

	public RecessionData()
	{
		Initialize( GetOwner() );
	}

	public RecessionData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RecessionData( DBResource owner, RecessionData source )
		: this(owner, source, true){}

	protected RecessionData( DBResource owner, RecessionData source, bool fireEvent )
	{
		_recessionTable = new UndoRedoList<float>( owner );
		_recessionTable.Assign( source.recessionTable );
		_isWaitingTimePremium = new UndoRedo<bool>( owner, source.isWaitingTimePremium );
		_recessionTable.Changed += FireChangedEvent;
		_isWaitingTimePremium.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RecessionData source = _source as RecessionData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RecessionData" );
		recessionTable = source.recessionTable;
		isWaitingTimePremium = source.isWaitingTimePremium;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RecessionData newParent = _newParent as RecessionData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_recessionTable.SetParent( newParent == null ? null : newParent._recessionTable );
		_isWaitingTimePremium.SetParent( newParent == null ? null : newParent._isWaitingTimePremium );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_recessionTable.Reset();
		_isWaitingTimePremium.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_recessionTable.IsDerivedFromParent()
			&& _isWaitingTimePremium.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "recessionTable" )
			_recessionTable.Reset();
		else if ( fieldName == "isWaitingTimePremium" )
			_isWaitingTimePremium.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "recessionTable" )
			return _recessionTable.IsDerivedFromParent();
		if ( fieldName == "isWaitingTimePremium" )
			return _isWaitingTimePremium.IsDerivedFromParent();
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

[Custom("DBServer")]
public class RecessionFullPartyTableForForceMM : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RecessionFullPartyTableForForceMM __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<float> _recessionTable;
	private UndoRedoList<float> _recessionPremium;

	[Description( "Таблица допустимых разлетов" )]
	public libdb.IChangeableList<float> recessionTable { get { return _recessionTable; } set { _recessionTable.Assign( value ); } }

	[Description( "Таблица добавок к допустимым разлётам за каждые 60 сек ожидания сверх границы" )]
	public libdb.IChangeableList<float> recessionPremium { get { return _recessionPremium; } set { _recessionPremium.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_recessionTable = new UndoRedoList<float>( owner );
		_recessionPremium = new UndoRedoList<float>( owner );
		_recessionTable.Changed += FireChangedEvent;
		_recessionPremium.Changed += FireChangedEvent;
	}

	public RecessionFullPartyTableForForceMM()
	{
		Initialize( GetOwner() );
	}

	public RecessionFullPartyTableForForceMM( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RecessionFullPartyTableForForceMM( DBResource owner, RecessionFullPartyTableForForceMM source )
		: this(owner, source, true){}

	protected RecessionFullPartyTableForForceMM( DBResource owner, RecessionFullPartyTableForForceMM source, bool fireEvent )
	{
		_recessionTable = new UndoRedoList<float>( owner );
		_recessionTable.Assign( source.recessionTable );
		_recessionPremium = new UndoRedoList<float>( owner );
		_recessionPremium.Assign( source.recessionPremium );
		_recessionTable.Changed += FireChangedEvent;
		_recessionPremium.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RecessionFullPartyTableForForceMM source = _source as RecessionFullPartyTableForForceMM;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RecessionFullPartyTableForForceMM" );
		recessionTable = source.recessionTable;
		recessionPremium = source.recessionPremium;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RecessionFullPartyTableForForceMM newParent = _newParent as RecessionFullPartyTableForForceMM;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_recessionTable.SetParent( newParent == null ? null : newParent._recessionTable );
		_recessionPremium.SetParent( newParent == null ? null : newParent._recessionPremium );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_recessionTable.Reset();
		_recessionPremium.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_recessionTable.IsDerivedFromParent()
			&& _recessionPremium.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "recessionTable" )
			_recessionTable.Reset();
		else if ( fieldName == "recessionPremium" )
			_recessionPremium.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "recessionTable" )
			return _recessionTable.IsDerivedFromParent();
		if ( fieldName == "recessionPremium" )
			return _recessionPremium.IsDerivedFromParent();
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

[Custom("DBServer")]
public class RecessionTableForPlayerRatingMM : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RecessionTableForPlayerRatingMM __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<RecessionData> _recessionTable;
	private UndoRedo<float> _recessionSideDiff;
	private UndoRedoList<float> _recessionPremiumTable;
	private UndoRedo<float> _recessionPremiumTimeThreshold;
	private UndoRedo<int> _recessionMaxPlayerRating;
	private UndoRedo<int> _recessionMinPlayerRating;

	[EnumArray(typeof(ESweepStage))]
	public libdb.IChangeableList<RecessionData> recessionTable { get { return _recessionTable; } set { _recessionTable.Assign( value ); } }

	[Description( "Значение отвечающие за максимальную разницу по playerRating между игроками внутри команды" )]
	public float recessionSideDiff { get { return _recessionSideDiff.Get(); } set { _recessionSideDiff.Set( value ); } }

	[Description( "Добавка 50 к допустимым разлётам за каждые 60 сек ожидания сверх границы recessionPremiumTimeThreshold (учитывается линейно, а не кусочно-постоянно)" )]
	public libdb.IChangeableList<float> recessionPremiumTable { get { return _recessionPremiumTable; } set { _recessionPremiumTable.Assign( value ); } }

	[Description( "Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам для подбора команд по пользовательскому рейтингу" )]
	public float recessionPremiumTimeThreshold { get { return _recessionPremiumTimeThreshold.Get(); } set { _recessionPremiumTimeThreshold.Set( value ); } }

	[Description( "В ходе ММ кандидат с playerRating выше этого значения будет приравнен к этому значению. Пример: кандидат с playerRating 2400 в рамках ММ будет расцениваться как кандидат с playerRating 2000." )]
	public int recessionMaxPlayerRating { get { return _recessionMaxPlayerRating.Get(); } set { _recessionMaxPlayerRating.Set( value ); } }

	[Description( "Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам для подбора команд по пользовательскому рейтингу" )]
	public int recessionMinPlayerRating { get { return _recessionMinPlayerRating.Get(); } set { _recessionMinPlayerRating.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_recessionTable = new UndoRedoAssignableList<RecessionData>( owner, typeof( ESweepStage ) );
		_recessionSideDiff = new UndoRedo<float>( owner, 0.0f );
		_recessionPremiumTable = new UndoRedoList<float>( owner );
		_recessionPremiumTimeThreshold = new UndoRedo<float>( owner, 0.0f );
		_recessionMaxPlayerRating = new UndoRedo<int>( owner, 2000 );
		_recessionMinPlayerRating = new UndoRedo<int>( owner, 1200 );
		_recessionTable.Changed += FireChangedEvent;
		_recessionSideDiff.Changed += FireChangedEvent;
		_recessionPremiumTable.Changed += FireChangedEvent;
		_recessionPremiumTimeThreshold.Changed += FireChangedEvent;
		_recessionMaxPlayerRating.Changed += FireChangedEvent;
		_recessionMinPlayerRating.Changed += FireChangedEvent;
	}

	public RecessionTableForPlayerRatingMM()
	{
		Initialize( GetOwner() );
	}

	public RecessionTableForPlayerRatingMM( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RecessionTableForPlayerRatingMM( DBResource owner, RecessionTableForPlayerRatingMM source )
		: this(owner, source, true){}

	protected RecessionTableForPlayerRatingMM( DBResource owner, RecessionTableForPlayerRatingMM source, bool fireEvent )
	{
		_recessionTable = new UndoRedoAssignableList<RecessionData>( owner, typeof( ESweepStage ) );
		_recessionTable.Assign( source.recessionTable );
		_recessionSideDiff = new UndoRedo<float>( owner, source.recessionSideDiff );
		_recessionPremiumTable = new UndoRedoList<float>( owner );
		_recessionPremiumTable.Assign( source.recessionPremiumTable );
		_recessionPremiumTimeThreshold = new UndoRedo<float>( owner, source.recessionPremiumTimeThreshold );
		_recessionMaxPlayerRating = new UndoRedo<int>( owner, source.recessionMaxPlayerRating );
		_recessionMinPlayerRating = new UndoRedo<int>( owner, source.recessionMinPlayerRating );
		_recessionTable.Changed += FireChangedEvent;
		_recessionSideDiff.Changed += FireChangedEvent;
		_recessionPremiumTable.Changed += FireChangedEvent;
		_recessionPremiumTimeThreshold.Changed += FireChangedEvent;
		_recessionMaxPlayerRating.Changed += FireChangedEvent;
		_recessionMinPlayerRating.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RecessionTableForPlayerRatingMM source = _source as RecessionTableForPlayerRatingMM;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RecessionTableForPlayerRatingMM" );
		recessionTable = source.recessionTable;
		recessionSideDiff = source.recessionSideDiff;
		recessionPremiumTable = source.recessionPremiumTable;
		recessionPremiumTimeThreshold = source.recessionPremiumTimeThreshold;
		recessionMaxPlayerRating = source.recessionMaxPlayerRating;
		recessionMinPlayerRating = source.recessionMinPlayerRating;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RecessionTableForPlayerRatingMM newParent = _newParent as RecessionTableForPlayerRatingMM;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_recessionTable.SetParent( newParent == null ? null : newParent._recessionTable );
		_recessionSideDiff.SetParent( newParent == null ? null : newParent._recessionSideDiff );
		_recessionPremiumTable.SetParent( newParent == null ? null : newParent._recessionPremiumTable );
		_recessionPremiumTimeThreshold.SetParent( newParent == null ? null : newParent._recessionPremiumTimeThreshold );
		_recessionMaxPlayerRating.SetParent( newParent == null ? null : newParent._recessionMaxPlayerRating );
		_recessionMinPlayerRating.SetParent( newParent == null ? null : newParent._recessionMinPlayerRating );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_recessionTable.Reset();
		_recessionSideDiff.Reset();
		_recessionPremiumTable.Reset();
		_recessionPremiumTimeThreshold.Reset();
		_recessionMaxPlayerRating.Reset();
		_recessionMinPlayerRating.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_recessionTable.IsDerivedFromParent()
			&& _recessionSideDiff.IsDerivedFromParent()
			&& _recessionPremiumTable.IsDerivedFromParent()
			&& _recessionPremiumTimeThreshold.IsDerivedFromParent()
			&& _recessionMaxPlayerRating.IsDerivedFromParent()
			&& _recessionMinPlayerRating.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "recessionTable" )
			_recessionTable.Reset();
		else if ( fieldName == "recessionSideDiff" )
			_recessionSideDiff.Reset();
		else if ( fieldName == "recessionPremiumTable" )
			_recessionPremiumTable.Reset();
		else if ( fieldName == "recessionPremiumTimeThreshold" )
			_recessionPremiumTimeThreshold.Reset();
		else if ( fieldName == "recessionMaxPlayerRating" )
			_recessionMaxPlayerRating.Reset();
		else if ( fieldName == "recessionMinPlayerRating" )
			_recessionMinPlayerRating.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "recessionTable" )
			return _recessionTable.IsDerivedFromParent();
		if ( fieldName == "recessionSideDiff" )
			return _recessionSideDiff.IsDerivedFromParent();
		if ( fieldName == "recessionPremiumTable" )
			return _recessionPremiumTable.IsDerivedFromParent();
		if ( fieldName == "recessionPremiumTimeThreshold" )
			return _recessionPremiumTimeThreshold.IsDerivedFromParent();
		if ( fieldName == "recessionMaxPlayerRating" )
			return _recessionMaxPlayerRating.IsDerivedFromParent();
		if ( fieldName == "recessionMinPlayerRating" )
			return _recessionMinPlayerRating.IsDerivedFromParent();
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
[DBVersion(0)]
public class RollItemProbability : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RollItemProbability __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _probability;
	private UndoRedoDBPtr<RollItem> _item;

	[Description( "Вес итема для ролла из контейнера - probability всех итемов складываются перед опробыванием вероятности. В лутбоксах -1 гарантирует выдачу итема." )]
	public float probability { get { return _probability.Get(); } set { _probability.Set( value ); } }

	public DBPtr<RollItem> item { get { return _item.Get(); } set { _item.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_probability = new UndoRedo<float>( owner, 0.0f );
		_item = new UndoRedoDBPtr<RollItem>( owner );
		_probability.Changed += FireChangedEvent;
		_item.Changed += FireChangedEvent;
	}

	public RollItemProbability()
	{
		Initialize( GetOwner() );
	}

	public RollItemProbability( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RollItemProbability( DBResource owner, RollItemProbability source )
		: this(owner, source, true){}

	protected RollItemProbability( DBResource owner, RollItemProbability source, bool fireEvent )
	{
		_probability = new UndoRedo<float>( owner, source.probability );
		_item = new UndoRedoDBPtr<RollItem>( owner, source.item );
		_probability.Changed += FireChangedEvent;
		_item.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RollItemProbability source = _source as RollItemProbability;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollItemProbability" );
		probability = source.probability;
		item = source.item;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RollItemProbability newParent = _newParent as RollItemProbability;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_probability.SetParent( newParent == null ? null : newParent._probability );
		_item.SetParent( newParent == null ? null : newParent._item );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_probability.Reset();
		_item.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_probability.IsDerivedFromParent()
			&& _item.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "probability" )
			_probability.Reset();
		else if ( fieldName == "item" )
			_item.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
		if ( fieldName == "item" )
			return _item.IsDerivedFromParent();
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
[DBVersion(0)]
public class RollLevelInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RollLevelInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedo<int> _count;
	private UndoRedo<int> _deviation;

	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	public int deviation { get { return _deviation.Get(); } set { _deviation.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_count = new UndoRedo<int>( owner, 0 );
		_deviation = new UndoRedo<int>( owner, 0 );
		_level.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
		_deviation.Changed += FireChangedEvent;
	}

	public RollLevelInfo()
	{
		Initialize( GetOwner() );
	}

	public RollLevelInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RollLevelInfo( DBResource owner, RollLevelInfo source )
		: this(owner, source, true){}

	protected RollLevelInfo( DBResource owner, RollLevelInfo source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_count = new UndoRedo<int>( owner, source.count );
		_deviation = new UndoRedo<int>( owner, source.deviation );
		_level.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
		_deviation.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RollLevelInfo source = _source as RollLevelInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollLevelInfo" );
		level = source.level;
		count = source.count;
		deviation = source.deviation;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RollLevelInfo newParent = _newParent as RollLevelInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_count.SetParent( newParent == null ? null : newParent._count );
		_deviation.SetParent( newParent == null ? null : newParent._deviation );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_count.Reset();
		_deviation.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _count.IsDerivedFromParent()
			&& _deviation.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
		else if ( fieldName == "count" )
			_count.Reset();
		else if ( fieldName == "deviation" )
			_deviation.Reset();
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
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
		if ( fieldName == "deviation" )
			return _deviation.IsDerivedFromParent();
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

[Custom("DBServer")]
public class SingleRollSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SingleRollSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<RollContainer> _rollContainer;
	private UndoRedo<ETalentRollGroup> _allowedRollGroups;
	private UndoRedo<int> _version;

	[Description( "Контейнер для ролла" )]
	public DBPtr<RollContainer> rollContainer { get { return _rollContainer.Get(); } set { _rollContainer.Set( value ); } }

	[Description( "Allowed talent groups for roll" )]
	public ETalentRollGroup allowedRollGroups { get { return _allowedRollGroups.Get(); } set { _allowedRollGroups.Set( value ); } }

	[Description( "Версия. Увеличить если изменилась ссылка на контейнер." )]
	public int version { get { return _version.Get(); } set { _version.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rollContainer = new UndoRedoDBPtr<RollContainer>( owner );
		_allowedRollGroups = new UndoRedo<ETalentRollGroup>( owner, ETalentRollGroup.All );
		_version = new UndoRedo<int>( owner, 0 );
		_rollContainer.Changed += FireChangedEvent;
		_allowedRollGroups.Changed += FireChangedEvent;
		_version.Changed += FireChangedEvent;
	}

	public SingleRollSettings()
	{
		Initialize( GetOwner() );
	}

	public SingleRollSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SingleRollSettings( DBResource owner, SingleRollSettings source )
		: this(owner, source, true){}

	protected SingleRollSettings( DBResource owner, SingleRollSettings source, bool fireEvent )
	{
		_rollContainer = new UndoRedoDBPtr<RollContainer>( owner, source.rollContainer );
		_allowedRollGroups = new UndoRedo<ETalentRollGroup>( owner, source.allowedRollGroups );
		_version = new UndoRedo<int>( owner, source.version );
		_rollContainer.Changed += FireChangedEvent;
		_allowedRollGroups.Changed += FireChangedEvent;
		_version.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SingleRollSettings source = _source as SingleRollSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SingleRollSettings" );
		rollContainer = source.rollContainer;
		allowedRollGroups = source.allowedRollGroups;
		version = source.version;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SingleRollSettings newParent = _newParent as SingleRollSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rollContainer.SetParent( newParent == null ? null : newParent._rollContainer );
		_allowedRollGroups.SetParent( newParent == null ? null : newParent._allowedRollGroups );
		_version.SetParent( newParent == null ? null : newParent._version );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rollContainer.Reset();
		_allowedRollGroups.Reset();
		_version.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rollContainer.IsDerivedFromParent()
			&& _allowedRollGroups.IsDerivedFromParent()
			&& _version.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rollContainer" )
			_rollContainer.Reset();
		else if ( fieldName == "allowedRollGroups" )
			_allowedRollGroups.Reset();
		else if ( fieldName == "version" )
			_version.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rollContainer" )
			return _rollContainer.IsDerivedFromParent();
		if ( fieldName == "allowedRollGroups" )
			return _allowedRollGroups.IsDerivedFromParent();
		if ( fieldName == "version" )
			return _version.IsDerivedFromParent();
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
public class TalentUpgradeProbability : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentUpgradeProbability __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _probability;
	private UndoRedo<int> _points;

	[Description( "вероятность" )]
	public float probability { get { return _probability.Get(); } set { _probability.Set( value ); } }

	[Description( "очки заточки (опыт) (по ним считается уровень заточки)" )]
	public int points { get { return _points.Get(); } set { _points.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_probability = new UndoRedo<float>( owner, 0.0f );
		_points = new UndoRedo<int>( owner, 0 );
		_probability.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
	}

	public TalentUpgradeProbability()
	{
		Initialize( GetOwner() );
	}

	public TalentUpgradeProbability( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentUpgradeProbability( DBResource owner, TalentUpgradeProbability source )
		: this(owner, source, true){}

	protected TalentUpgradeProbability( DBResource owner, TalentUpgradeProbability source, bool fireEvent )
	{
		_probability = new UndoRedo<float>( owner, source.probability );
		_points = new UndoRedo<int>( owner, source.points );
		_probability.Changed += FireChangedEvent;
		_points.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentUpgradeProbability source = _source as TalentUpgradeProbability;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeProbability" );
		probability = source.probability;
		points = source.points;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentUpgradeProbability newParent = _newParent as TalentUpgradeProbability;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_probability.SetParent( newParent == null ? null : newParent._probability );
		_points.SetParent( newParent == null ? null : newParent._points );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_probability.Reset();
		_points.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_probability.IsDerivedFromParent()
			&& _points.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "probability" )
			_probability.Reset();
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
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
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

[Custom("DBServer", "Social")]
[NameMapValue]
[NonTerminal]
public class GuildBonus : DBResource
{
	private UndoRedoDBPtr<GuildBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _tooltip;

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBonus>(owner);
		_tooltip = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
	}

	public GuildBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBonus" );
		tooltip = source.tooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBonus source = _source as GuildBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBonus newParent = rawParent == null ? null : rawParent.Get<GuildBonus>();
		if ( newParent == null && _newParent is GuildBonus )
			newParent = _newParent as GuildBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tooltip.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tooltip.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
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
public class BaseMarketingEvent : DBResource
{
	private UndoRedoDBPtr<BaseMarketingEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseMarketingEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseMarketingEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BaseMarketingEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseMarketingEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseMarketingEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseMarketingEvent source = _source as BaseMarketingEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseMarketingEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseMarketingEvent newParent = rawParent == null ? null : rawParent.Get<BaseMarketingEvent>();
		if ( newParent == null && _newParent is BaseMarketingEvent )
			newParent = _newParent as BaseMarketingEvent;
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

[Custom("DBServer", "Social")]
[NonTerminal]
public class RollItem : DBResource
{
	private UndoRedoDBPtr<RollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<RollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RollItem>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public RollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( RollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RollItem" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RollItem source = _source as RollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RollItem newParent = rawParent == null ? null : rawParent.Get<RollItem>();
		if ( newParent == null && _newParent is RollItem )
			newParent = _newParent as RollItem;
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

[Custom("DBServer")]
[UseTypeName("CWST")]
public class ClanWarsSettings : DBResource
{
	private UndoRedoDBPtr<ClanWarsSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<ClanWarsSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _basePoints;
	private UndoRedoAssignableList<BaseModifierFromQuantity> _partyClanMembersModifier;
	private UndoRedoAssignableList<BaseModifierFromQuantity> _foeCountsModifier;
	private UndoRedoList<float> _defeatedFoeRankModifier;
	private UndoRedo<float> _clanPoints;
	private UndoRedo<bool> _normalizeBySessionScores;
	private UndoRedo<float> _premiumAccountModifier;

	[Description( "Базовое значение" )]
	public float basePoints { get { return _basePoints.Get(); } set { _basePoints.Set( value ); } }

	[Description( "Модификатор от количества игроков одного клана в команде." )]
	public libdb.IChangeableList<BaseModifierFromQuantity> partyClanMembersModifier { get { return _partyClanMembersModifier; } set { _partyClanMembersModifier.Assign( value ); } }

	[Description( "Модификатор от количества игроков в противоположной команде." )]
	public libdb.IChangeableList<BaseModifierFromQuantity> foeCountsModifier { get { return _foeCountsModifier; } set { _foeCountsModifier.Assign( value ); } }

	[Description( "Значение полученное за рейтинг побежденного врага, в виде: номер ранка( из HeroRanks) - множитель" )]
	public libdb.IChangeableList<float> defeatedFoeRankModifier { get { return _defeatedFoeRankModifier; } set { _defeatedFoeRankModifier.Assign( value ); } }

	[Description( "Очки клана. % сбора очков со своих мемберов." )]
	public float clanPoints { get { return _clanPoints.Get(); } set { _clanPoints.Set( value ); } }

	[Description( "Базовое значение после применения модификаторов умножается на нормализованные по капу очки игрока набранные в сесиии." )]
	public bool normalizeBySessionScores { get { return _normalizeBySessionScores.Get(); } set { _normalizeBySessionScores.Set( value ); } }

	[Description( "Модификатор клановых очков игрока за золотой век." )]
	public float premiumAccountModifier { get { return _premiumAccountModifier.Get(); } set { _premiumAccountModifier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ClanWarsSettings>(owner);
		_basePoints = new UndoRedo<float>( owner, 10.0f );
		_partyClanMembersModifier = new UndoRedoAssignableList<BaseModifierFromQuantity>( owner );
		_foeCountsModifier = new UndoRedoAssignableList<BaseModifierFromQuantity>( owner );
		_defeatedFoeRankModifier = new UndoRedoList<float>( owner );
		_clanPoints = new UndoRedo<float>( owner, 0.3f );
		_normalizeBySessionScores = new UndoRedo<bool>( owner, true );
		_premiumAccountModifier = new UndoRedo<float>( owner, 2.0f );
		___parent.Changed += FireChangedEvent;
		_basePoints.Changed += FireChangedEvent;
		_partyClanMembersModifier.Changed += FireChangedEvent;
		_foeCountsModifier.Changed += FireChangedEvent;
		_defeatedFoeRankModifier.Changed += FireChangedEvent;
		_clanPoints.Changed += FireChangedEvent;
		_normalizeBySessionScores.Changed += FireChangedEvent;
		_premiumAccountModifier.Changed += FireChangedEvent;
	}

	public ClanWarsSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( ClanWarsSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ClanWarsSettings" );
		basePoints = source.basePoints;
		partyClanMembersModifier = source.partyClanMembersModifier;
		foeCountsModifier = source.foeCountsModifier;
		defeatedFoeRankModifier = source.defeatedFoeRankModifier;
		clanPoints = source.clanPoints;
		normalizeBySessionScores = source.normalizeBySessionScores;
		premiumAccountModifier = source.premiumAccountModifier;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ClanWarsSettings source = _source as ClanWarsSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClanWarsSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ClanWarsSettings newParent = rawParent == null ? null : rawParent.Get<ClanWarsSettings>();
		if ( newParent == null && _newParent is ClanWarsSettings )
			newParent = _newParent as ClanWarsSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_basePoints.SetParent( newParent == null ? null : newParent._basePoints );
		_partyClanMembersModifier.SetParent( newParent == null ? null : newParent._partyClanMembersModifier );
		_foeCountsModifier.SetParent( newParent == null ? null : newParent._foeCountsModifier );
		_defeatedFoeRankModifier.SetParent( newParent == null ? null : newParent._defeatedFoeRankModifier );
		_clanPoints.SetParent( newParent == null ? null : newParent._clanPoints );
		_normalizeBySessionScores.SetParent( newParent == null ? null : newParent._normalizeBySessionScores );
		_premiumAccountModifier.SetParent( newParent == null ? null : newParent._premiumAccountModifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_basePoints.Reset();
		_partyClanMembersModifier.Reset();
		_foeCountsModifier.Reset();
		_defeatedFoeRankModifier.Reset();
		_clanPoints.Reset();
		_normalizeBySessionScores.Reset();
		_premiumAccountModifier.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_basePoints.IsDerivedFromParent()
			&& _partyClanMembersModifier.IsDerivedFromParent()
			&& _foeCountsModifier.IsDerivedFromParent()
			&& _defeatedFoeRankModifier.IsDerivedFromParent()
			&& _clanPoints.IsDerivedFromParent()
			&& _normalizeBySessionScores.IsDerivedFromParent()
			&& _premiumAccountModifier.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "basePoints" )
			_basePoints.Reset();
		else if ( fieldName == "partyClanMembersModifier" )
			_partyClanMembersModifier.Reset();
		else if ( fieldName == "foeCountsModifier" )
			_foeCountsModifier.Reset();
		else if ( fieldName == "defeatedFoeRankModifier" )
			_defeatedFoeRankModifier.Reset();
		else if ( fieldName == "clanPoints" )
			_clanPoints.Reset();
		else if ( fieldName == "normalizeBySessionScores" )
			_normalizeBySessionScores.Reset();
		else if ( fieldName == "premiumAccountModifier" )
			_premiumAccountModifier.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "basePoints" )
			return _basePoints.IsDerivedFromParent();
		if ( fieldName == "partyClanMembersModifier" )
			return _partyClanMembersModifier.IsDerivedFromParent();
		if ( fieldName == "foeCountsModifier" )
			return _foeCountsModifier.IsDerivedFromParent();
		if ( fieldName == "defeatedFoeRankModifier" )
			return _defeatedFoeRankModifier.IsDerivedFromParent();
		if ( fieldName == "clanPoints" )
			return _clanPoints.IsDerivedFromParent();
		if ( fieldName == "normalizeBySessionScores" )
			return _normalizeBySessionScores.IsDerivedFromParent();
		if ( fieldName == "premiumAccountModifier" )
			return _premiumAccountModifier.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[UseTypeName("CONTSPEC")]
public class ContainersBySpecialPoints : DBResource
{
	private UndoRedoDBPtr<ContainersBySpecialPoints> ___parent;
	[HideInOutliner]
	public new DBPtr<ContainersBySpecialPoints> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<PointsToContainers> _items;

	public libdb.IChangeableList<PointsToContainers> items { get { return _items; } set { _items.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ContainersBySpecialPoints>(owner);
		_items = new UndoRedoAssignableList<PointsToContainers>( owner );
		___parent.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
	}

	public ContainersBySpecialPoints()
	{
		Initialize( this );
	}
	private void AssignSelf( ContainersBySpecialPoints source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ContainersBySpecialPoints" );
		items = source.items;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ContainersBySpecialPoints source = _source as ContainersBySpecialPoints;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ContainersBySpecialPoints" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ContainersBySpecialPoints newParent = rawParent == null ? null : rawParent.Get<ContainersBySpecialPoints>();
		if ( newParent == null && _newParent is ContainersBySpecialPoints )
			newParent = _newParent as ContainersBySpecialPoints;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_items.SetParent( newParent == null ? null : newParent._items );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_items.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_items.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "items" )
			_items.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "items" )
			return _items.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class FlagRollItem : RollItem
{
	private UndoRedoDBPtr<FlagRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<FlagRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<CustomFlag> _flag;

	public DBPtr<CustomFlag> flag { get { return _flag.Get(); } set { _flag.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FlagRollItem>(owner);
		_flag = new UndoRedoDBPtr<CustomFlag>( owner );
		___parent.Changed += FireChangedEvent;
		_flag.Changed += FireChangedEvent;
	}

	public FlagRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( FlagRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FlagRollItem" );
		flag = source.flag;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FlagRollItem source = _source as FlagRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlagRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FlagRollItem newParent = rawParent == null ? null : rawParent.Get<FlagRollItem>();
		if ( newParent == null && _newParent is FlagRollItem )
			newParent = _newParent as FlagRollItem;
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

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class GoldRollItem : RollItem
{
	private UndoRedoDBPtr<GoldRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<GoldRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _count;

	[Description( "Сколько золота выдать в лутбоксе" )]
	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GoldRollItem>(owner);
		_count = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
	}

	public GoldRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( GoldRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GoldRollItem" );
		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GoldRollItem source = _source as GoldRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GoldRollItem newParent = rawParent == null ? null : rawParent.Get<GoldRollItem>();
		if ( newParent == null && _newParent is GoldRollItem )
			newParent = _newParent as GoldRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_count.SetParent( newParent == null ? null : newParent._count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_count.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_count.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "count" )
			_count.Reset();
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
[UseTypeName("GUILDBONUS")]
public class AdditionHeroExpBonus : GuildBonus
{
	private UndoRedoDBPtr<AdditionHeroExpBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<AdditionHeroExpBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _percent;

	[Description( "Дополнительный процент опыта герою за бой.  Доступен для namemap'а" )]
	[NameMapValue]
	public int percent { get { return _percent.Get(); } set { _percent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdditionHeroExpBonus>(owner);
		_percent = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_percent.Changed += FireChangedEvent;
	}

	public AdditionHeroExpBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( AdditionHeroExpBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdditionHeroExpBonus" );
		percent = source.percent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdditionHeroExpBonus source = _source as AdditionHeroExpBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdditionHeroExpBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdditionHeroExpBonus newParent = rawParent == null ? null : rawParent.Get<AdditionHeroExpBonus>();
		if ( newParent == null && _newParent is AdditionHeroExpBonus )
			newParent = _newParent as AdditionHeroExpBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_percent.SetParent( newParent == null ? null : newParent._percent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_percent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_percent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "percent" )
			_percent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "percent" )
			return _percent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("GUILDLEVELS")]
public class GuildLevels : DBResource
{
	private UndoRedoDBPtr<GuildLevels> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildLevels> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _requiredExpMultiplier;
	private UndoRedoAssignableList<GuildLevel> _levels;

	[Description( "Множитель для представления requiredExp в рассчетах. Если уровень гильдии требует 10 опыта и множитель 10^5, то будет считаться что требуется 10*10^5 = 10^6 опыта" )]
	public int requiredExpMultiplier { get { return _requiredExpMultiplier.Get(); } set { _requiredExpMultiplier.Set( value ); } }

	public libdb.IChangeableList<GuildLevel> levels { get { return _levels; } set { _levels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildLevels>(owner);
		_requiredExpMultiplier = new UndoRedo<int>( owner, 100000 );
		_levels = new UndoRedoAssignableList<GuildLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_requiredExpMultiplier.Changed += FireChangedEvent;
		_levels.Changed += FireChangedEvent;
	}

	public GuildLevels()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildLevels source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildLevels" );
		requiredExpMultiplier = source.requiredExpMultiplier;
		levels = source.levels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildLevels source = _source as GuildLevels;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildLevels" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildLevels newParent = rawParent == null ? null : rawParent.Get<GuildLevels>();
		if ( newParent == null && _newParent is GuildLevels )
			newParent = _newParent as GuildLevels;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_requiredExpMultiplier.SetParent( newParent == null ? null : newParent._requiredExpMultiplier );
		_levels.SetParent( newParent == null ? null : newParent._levels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_requiredExpMultiplier.Reset();
		_levels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_requiredExpMultiplier.IsDerivedFromParent()
			&& _levels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "requiredExpMultiplier" )
			_requiredExpMultiplier.Reset();
		else if ( fieldName == "levels" )
			_levels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "requiredExpMultiplier" )
			return _requiredExpMultiplier.IsDerivedFromParent();
		if ( fieldName == "levels" )
			return _levels.IsDerivedFromParent();
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
[UseTypeName("GUILDBONUS")]
public class GuildResourceBonus : GuildBonus
{
	private UndoRedoDBPtr<GuildResourceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildResourceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _resource;

	[Description( "Кол-во гильдийского ресурса за бой. Доступен для namemap'а" )]
	[NameMapValue]
	public int resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildResourceBonus>(owner);
		_resource = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
	}

	public GuildResourceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildResourceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildResourceBonus" );
		resource = source.resource;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildResourceBonus source = _source as GuildResourceBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildResourceBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildResourceBonus newParent = rawParent == null ? null : rawParent.Get<GuildResourceBonus>();
		if ( newParent == null && _newParent is GuildResourceBonus )
			newParent = _newParent as GuildResourceBonus;
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
[UseTypeName("ROLLITEM")]
public class HeroRollItem : RollItem
{
	private UndoRedoDBPtr<HeroRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;

	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroRollItem>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
	}

	public HeroRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroRollItem" );
		hero = source.hero;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroRollItem source = _source as HeroRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroRollItem newParent = rawParent == null ? null : rawParent.Get<HeroRollItem>();
		if ( newParent == null && _newParent is HeroRollItem )
			newParent = _newParent as HeroRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[DBVersion(6)]
[UseTypeName("MAPMMAKING")]
public class MapMMakingSettings : DBResource
{
	private UndoRedoDBPtr<MapMMakingSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<MapMMakingSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _mock;
	private UndoRedo<bool> _isTournamentMap;
	private EstimFunctionWeights _estimFunctionWeights;
	private UndoRedo<int> _normalBasePointsRepeatFactor;
	private UndoRedo<int> _noobBasePointsRepeatFactor;
	private UndoRedo<float> _ratingDiffGrowTime;
	private UndoRedo<int> _fullSweepSubsetLimit;
	private UndoRedo<int> _fullSweepSubsetLimitPve;
	private UndoRedo<int> _estimFunDecreaseTimeBegin;
	private UndoRedo<int> _estimFunDecreaseTimeEnd;
	private UndoRedo<float> _estimFunDecreaseFactor;
	private UndoRedo<float> _estimFunManoeuvresDecreaseFactor;
	private UndoRedo<int> _identicalHeroesSampleLimit;
	private UndoRedo<int> _identicalGuardHeroesSampleLimit;
	private UndoRedo<int> _identicalNoobHeroesSampleLimit;
	private UndoRedo<int> _lowWaitTimeThreshold;
	private UndoRedo<float> _lowWaitTimeFactor;
	private UndoRedo<int> _manoeuvresMinPopulation;
	private UndoRedo<int> _manoeuvresMaxPopulation;
	private UndoRedo<int> _guardManoeuvresMinPopulation;
	private UndoRedo<int> _guardManoeuvresMaxPopulation;
	private UndoRedo<float> _manoeuvresWaitThreshold;
	private UndoRedo<int> _manoeuvresFullSweepSubset;
	private UndoRedo<int> _trainingFemaleBotsCount;
	private UndoRedo<int> _necessaryLadiesCount;
	private UndoRedoList<float> _partySkillCompensation;
	private MMakingLoseStreakCorrection _loseStreakCorrection;
	private UndoRedo<int> _highRatingThreshold;
	private UndoRedo<int> _proRatingThreshold;
	private UndoRedo<int> _noobGamesMaxNormalRating;
	private UndoRedo<int> _highRatingCooldown;
	private UndoRedo<float> _noobsTimeout;
	private UndoRedo<int> _minimalNoobsPercentage;
	private UndoRedo<int> _fullPartyGameRatingDiffMin;
	private UndoRedo<int> _fullPartyGameRatingDiffMax;
	private UndoRedo<int> _waitTimeSoftLimit;
	private UndoRedo<int> _waitTimeHardLimit;
	private UndoRedo<int> _teamLeaversTimeTrashold;
	private UndoRedo<int> _gameLeaversTimeTrashold;
	private MMakingLocationPingSettings _locationPingSettings;
	private MMakingWaitVsProbability _waitVsProbability;
	private UndoRedoAssignableList<MMakingRank> _ranks;
	private UndoRedoAssignableList<RecessionData> _recessionTableForForceMM;
	private UndoRedoList<float> _recessionPremiumTable;
	private RecessionFullPartyTableForForceMM _recessionFullPartyTableForForceMM;
	private UndoRedo<float> _recessionPremiumTimeThreshold;
	private RecessionTableForPlayerRatingMM _recessionTableForPlayerRatingMM;
	private UndoRedo<int> _playerDiff;
	private UndoRedo<float> _rankDifferenceTimePenalty;
	private UndoRedo<float> _heroClassLimitsAttenuationTime;
	private UndoRedo<bool> _useRanking;
	private UndoRedoAssignableList<MMakingHeroClass> _optimalClasses;
	private UndoRedoList<float> _delayPerDonorLocalePlayer;
	private UndoRedo<int> _fullPartySize;
	private UndoRedo<float> _fullPartyVsRandomTimeThreshold;
	private UndoRedo<int> _localeWaitTimeThreshold;
	private MMakingScale _ratingScale;
	private MMakingScale _forceScale;
	private UndoRedo<float> _TeamSideTimeTreshold;

	[Custom("Social")]
	[Description( "Включает заглушечный ММ" )]
	public bool mock { get { return _mock.Get(); } set { _mock.Set( value ); } }

	[Custom("Social")]
	[Description( "Включает турнирный режим ММ" )]
	public bool isTournamentMap { get { return _isTournamentMap.Get(); } set { _isTournamentMap.Set( value ); } }

	[Description( "Веса компонент оценочной функции" )]
	public EstimFunctionWeights estimFunctionWeights { get { return _estimFunctionWeights; } set { _estimFunctionWeights.Assign( value ); } }

	[Description( "Кратность повторения точек для обычных игроков" )]
	public int normalBasePointsRepeatFactor { get { return _normalBasePointsRepeatFactor.Get(); } set { _normalBasePointsRepeatFactor.Set( value ); } }

	[Description( "Кратность повторения точек в нубятнике" )]
	public int noobBasePointsRepeatFactor { get { return _noobBasePointsRepeatFactor.Get(); } set { _noobBasePointsRepeatFactor.Set( value ); } }

	[Description( "Время ожидания игрока, за которое допустимая разница рейтинга/форса вырастает до макс. значения" )]
	public float ratingDiffGrowTime { get { return _ratingDiffGrowTime.Get(); } set { _ratingDiffGrowTime.Set( value ); } }

	[Description( "Ограничение размера выборки, на которой будет производится полный перебор; Отдельно для каждой фракции" )]
	public int fullSweepSubsetLimit { get { return _fullSweepSubsetLimit.Get(); } set { _fullSweepSubsetLimit.Set( value ); } }

	[Description( "Ограничение размера выборки, на которой будет производится полный перебор; Для PVE режимов" )]
	public int fullSweepSubsetLimitPve { get { return _fullSweepSubsetLimitPve.Get(); } set { _fullSweepSubsetLimitPve.Set( value ); } }

	[Description( "Оценочная функция игры будет снижена, если среднее время ожидания игроков находится в этом интервале" )]
	public int estimFunDecreaseTimeBegin { get { return _estimFunDecreaseTimeBegin.Get(); } set { _estimFunDecreaseTimeBegin.Set( value ); } }

	[Description( "Оценочная функция игры будет снижена, если среднее время ожидания игроков находится в этом интервале" )]
	public int estimFunDecreaseTimeEnd { get { return _estimFunDecreaseTimeEnd.Get(); } set { _estimFunDecreaseTimeEnd.Set( value ); } }

	[Description( "Коэффициент понижения оценочной функции в зависимости от времени ожидания" )]
	public float estimFunDecreaseFactor { get { return _estimFunDecreaseFactor.Get(); } set { _estimFunDecreaseFactor.Set( value ); } }

	[Description( "Коэффициент понижения оценочной функции в зависимости от времени ожидания; В режиме маневров" )]
	public float estimFunManoeuvresDecreaseFactor { get { return _estimFunManoeuvresDecreaseFactor.Get(); } set { _estimFunManoeuvresDecreaseFactor.Set( value ); } }

	[Description( "Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор" )]
	public int identicalHeroesSampleLimit { get { return _identicalHeroesSampleLimit.Get(); } set { _identicalHeroesSampleLimit.Set( value ); } }

	[Description( "Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор; Гвардейский режим" )]
	public int identicalGuardHeroesSampleLimit { get { return _identicalGuardHeroesSampleLimit.Get(); } set { _identicalGuardHeroesSampleLimit.Set( value ); } }

	[Description( "Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор; Нубские игры" )]
	public int identicalNoobHeroesSampleLimit { get { return _identicalNoobHeroesSampleLimit.Get(); } set { _identicalNoobHeroesSampleLimit.Set( value ); } }

	[Description( "Минимальное время ожидания. Если в игре присутствуют люди с меньшим временем, то значение ОФ будет дополнительно увеличено в lowWaitTimeFactor раз" )]
	public int lowWaitTimeThreshold { get { return _lowWaitTimeThreshold.Get(); } set { _lowWaitTimeThreshold.Set( value ); } }

	[Description( "Во сколько раз будет увеличена ОФ, если в игре присутствуют люди с временем, меньшим lowWaitTimeThreshold" )]
	public float lowWaitTimeFactor { get { return _lowWaitTimeFactor.Get(); } set { _lowWaitTimeFactor.Set( value ); } }

	[Description( "Минимальное число людей в очереди ММ для начала маневров, за одну сторону(устарело и не будет использоваться)" )]
	public int manoeuvresMinPopulation { get { return _manoeuvresMinPopulation.Get(); } set { _manoeuvresMinPopulation.Set( value ); } }

	[Description( "Максимальное число людей в очереди ММ для начала маневров, за другую сторону(устарело и не будет использоваться)" )]
	public int manoeuvresMaxPopulation { get { return _manoeuvresMaxPopulation.Get(); } set { _manoeuvresMaxPopulation.Set( value ); } }

	[Description( "Минимальное число людей в очереди ММ для начала гвардейских маневров, за одну сторону (устарело и не будет использоваться)" )]
	public int guardManoeuvresMinPopulation { get { return _guardManoeuvresMinPopulation.Get(); } set { _guardManoeuvresMinPopulation.Set( value ); } }

	[Description( "Максимальное число людей в очереди ММ для начала гвардейских маневров, за другую сторону (устарело и не будет использоваться)" )]
	public int guardManoeuvresMaxPopulation { get { return _guardManoeuvresMaxPopulation.Get(); } set { _guardManoeuvresMaxPopulation.Set( value ); } }

	[Description( "Минимальное время ожидания для участия запроса в маневрах (устарело и не будет использоваться)" )]
	public float manoeuvresWaitThreshold { get { return _manoeuvresWaitThreshold.Get(); } set { _manoeuvresWaitThreshold.Set( value ); } }

	[Description( "Ограничение размера выборки, на которой будет производится полный перебор в режиме маневров (устарело и не будет использоваться)" )]
	public int manoeuvresFullSweepSubset { get { return _manoeuvresFullSweepSubset.Get(); } set { _manoeuvresFullSweepSubset.Set( value ); } }

	[Description( "Идеальное количество девочек-ботов в тренировке" )]
	public int trainingFemaleBotsCount { get { return _trainingFemaleBotsCount.Get(); } set { _trainingFemaleBotsCount.Set( value ); } }

	[Description( "Идеальное количество девочек с точки зрения ММ" )]
	public int necessaryLadiesCount { get { return _necessaryLadiesCount.Get(); } set { _necessaryLadiesCount.Set( value ); } }

	[Description( "Компенсирующая набавка к рейтингу для игроков, участвующих в ММ группой" )]
	public libdb.IChangeableList<float> partySkillCompensation { get { return _partySkillCompensation; } set { _partySkillCompensation.Assign( value ); } }

	[Description( "Настройки механизма коррекции lose streaks" )]
	public MMakingLoseStreakCorrection loseStreakCorrection { get { return _loseStreakCorrection; } set { _loseStreakCorrection.Assign( value ); } }

	[Description( "Порог рейтинга, начиная с которого ММ будет придерживать игроков для 'задротов'" )]
	public int highRatingThreshold { get { return _highRatingThreshold.Get(); } set { _highRatingThreshold.Set( value ); } }

	[Description( "Порог рейтинга, начиная с которого игрок считается 'задротом', и для него начинают придерживать более низкорейтинговых" )]
	public int proRatingThreshold { get { return _proRatingThreshold.Get(); } set { _proRatingThreshold.Set( value ); } }

	[Description( "Максимальный рейтинг обычных игроков для участия в нубской игре" )]
	public int noobGamesMaxNormalRating { get { return _noobGamesMaxNormalRating.Get(); } set { _noobGamesMaxNormalRating.Set( value ); } }

	[Description( "Время, которое будут продолжать придеживать высокорейтинговых игроков, после ухода последнего 'задрота'" )]
	public int highRatingCooldown { get { return _highRatingCooldown.Get(); } set { _highRatingCooldown.Set( value ); } }

	[Description( "Время ожидания игроков-нубов, через которое их могут смешать с normal-игроками" )]
	public float noobsTimeout { get { return _noobsTimeout.Get(); } set { _noobsTimeout.Set( value ); } }

	[Description( "Минимальный процент содержания нубов в нубской игре, за каждую сторону" )]
	public int minimalNoobsPercentage { get { return _minimalNoobsPercentage.Get(); } set { _minimalNoobsPercentage.Set( value ); } }

	[Description( "Разница между рейтингами full-party, при минимальном времени ожидания" )]
	public int fullPartyGameRatingDiffMin { get { return _fullPartyGameRatingDiffMin.Get(); } set { _fullPartyGameRatingDiffMin.Set( value ); } }

	[Description( "Разница между рейтингами full-party, при максимальном времени ожидания" )]
	public int fullPartyGameRatingDiffMax { get { return _fullPartyGameRatingDiffMax.Get(); } set { _fullPartyGameRatingDiffMax.Set( value ); } }

	[Description( "Настройки системы ограничения времени ожидания (tm)" )]
	public int waitTimeSoftLimit { get { return _waitTimeSoftLimit.Get(); } set { _waitTimeSoftLimit.Set( value ); } }

	[Description( "Настройки системы ограничения времени ожидания (tm)" )]
	public int waitTimeHardLimit { get { return _waitTimeHardLimit.Get(); } set { _waitTimeHardLimit.Set( value ); } }

	[Description( "Настройка времени сбора команды, состоящей только из матерых ливеров(tm)" )]
	public int teamLeaversTimeTrashold { get { return _teamLeaversTimeTrashold.Get(); } set { _teamLeaversTimeTrashold.Set( value ); } }

	[Description( "Настройка времени подбора команды противников, состоящей только из матерых ливеров(tm)" )]
	public int gameLeaversTimeTrashold { get { return _gameLeaversTimeTrashold.Get(); } set { _gameLeaversTimeTrashold.Set( value ); } }

	[Description( "Настройки учета качества связи с разными pvx-кластерами" )]
	public MMakingLocationPingSettings locationPingSettings { get { return _locationPingSettings; } set { _locationPingSettings.Assign( value ); } }

	[Description( "Вероятность попадания нуба или гвардейца в соответствующую игру в зависимости от времени ожидания" )]
	public MMakingWaitVsProbability waitVsProbability { get { return _waitVsProbability; } set { _waitVsProbability.Assign( value ); } }

	[Description( "Список званий для использования в ММ" )]
	public libdb.IChangeableList<MMakingRank> ranks { get { return _ranks; } set { _ranks.Assign( value ); } }

	[Description( "Таблица допустимых разлетов" )]
	[EnumArray(typeof(ESweepStage))]
	public libdb.IChangeableList<RecessionData> recessionTableForForceMM { get { return _recessionTableForForceMM; } set { _recessionTableForForceMM.Assign( value ); } }

	[Description( "Таблица добавок к допустимым разлётам за каждые 60 сек ожидания сверх границы" )]
	public libdb.IChangeableList<float> recessionPremiumTable { get { return _recessionPremiumTable; } set { _recessionPremiumTable.Assign( value ); } }

	[Description( "Таблица допустимых разлетов при сборе фулок" )]
	public RecessionFullPartyTableForForceMM recessionFullPartyTableForForceMM { get { return _recessionFullPartyTableForForceMM; } set { _recessionFullPartyTableForForceMM.Assign( value ); } }

	[Description( "Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам" )]
	public float recessionPremiumTimeThreshold { get { return _recessionPremiumTimeThreshold.Get(); } set { _recessionPremiumTimeThreshold.Set( value ); } }

	[Description( "Набор таблиц допустимых разлётов по playerRating для первого/второго/третьего просевов" )]
	public RecessionTableForPlayerRatingMM recessionTableForPlayerRatingMM { get { return _recessionTableForPlayerRatingMM; } set { _recessionTableForPlayerRatingMM.Assign( value ); } }

	[Description( "Максимальная разница количеств игроков в командах на промежуточных шагах алгоритма" )]
	public int playerDiff { get { return _playerDiff.Get(); } set { _playerDiff.Set( value ); } }

	[Description( "Штраф к времени ожидания за разницу в званиях" )]
	public float rankDifferenceTimePenalty { get { return _rankDifferenceTimePenalty.Get(); } set { _rankDifferenceTimePenalty.Set( value ); } }

	[Description( "Время расширения допустимых границ классов героев на еденицу, сек" )]
	public float heroClassLimitsAttenuationTime { get { return _heroClassLimitsAttenuationTime.Get(); } set { _heroClassLimitsAttenuationTime.Set( value ); } }

	[Custom("Social")]
	[Description( "Включает режим ММ по званиям" )]
	public bool useRanking { get { return _useRanking.Get(); } set { _useRanking.Set( value ); } }

	[Description( "Таблица оптимальной эффективности классов в команде (из пяти человек)" )]
	[EnumArray(typeof(MMakingHeroClassEnum))]
	public libdb.IChangeableList<MMakingHeroClass> optimalClasses { get { return _optimalClasses; } set { _optimalClasses.Assign( value ); } }

	[Description( "Таблица барьера времени ожидания в зависимости от количества доноров в команде, от 0 до 4; Только для ММ по званиям" )]
	public libdb.IChangeableList<float> delayPerDonorLocalePlayer { get { return _delayPerDonorLocalePlayer; } set { _delayPerDonorLocalePlayer.Assign( value ); } }

	[Custom("Social")]
	[Description( "Размер команды, при которой она официально считается фуллкой" )]
	public int fullPartySize { get { return _fullPartySize.Get(); } set { _fullPartySize.Set( value ); } }

	[Description( "Порог времени ожидания, начиная с которого full-party может сматчмейкаться с рандомами" )]
	public float fullPartyVsRandomTimeThreshold { get { return _fullPartyVsRandomTimeThreshold.Get(); } set { _fullPartyVsRandomTimeThreshold.Set( value ); } }

	[Description( "Время ожидания, через которое игрок может попасть в игру с разным языком" )]
	public int localeWaitTimeThreshold { get { return _localeWaitTimeThreshold.Get(); } set { _localeWaitTimeThreshold.Set( value ); } }

	[Description( "Параметры расстановки опорных точек рейтинга" )]
	public MMakingScale ratingScale { get { return _ratingScale; } set { _ratingScale.Assign( value ); } }

	[Description( "Параметры расстановки опорных точек форса" )]
	public MMakingScale forceScale { get { return _forceScale; } set { _forceScale.Assign( value ); } }

	[Description( "Время подбора команды только за свою сторону" )]
	public float TeamSideTimeTreshold { get { return _TeamSideTimeTreshold.Get(); } set { _TeamSideTimeTreshold.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MapMMakingSettings>(owner);
		_mock = new UndoRedo<bool>( owner, false );
		_isTournamentMap = new UndoRedo<bool>( owner, false );
		_estimFunctionWeights = new EstimFunctionWeights( owner );
		_normalBasePointsRepeatFactor = new UndoRedo<int>( owner, 5 );
		_noobBasePointsRepeatFactor = new UndoRedo<int>( owner, 40 );
		_ratingDiffGrowTime = new UndoRedo<float>( owner, 180.0f );
		_fullSweepSubsetLimit = new UndoRedo<int>( owner, 15 );
		_fullSweepSubsetLimitPve = new UndoRedo<int>( owner, 15 );
		_estimFunDecreaseTimeBegin = new UndoRedo<int>( owner, 180 );
		_estimFunDecreaseTimeEnd = new UndoRedo<int>( owner, 300 );
		_estimFunDecreaseFactor = new UndoRedo<float>( owner, 0.5f );
		_estimFunManoeuvresDecreaseFactor = new UndoRedo<float>( owner, 0.5f );
		_identicalHeroesSampleLimit = new UndoRedo<int>( owner, 1 );
		_identicalGuardHeroesSampleLimit = new UndoRedo<int>( owner, 1 );
		_identicalNoobHeroesSampleLimit = new UndoRedo<int>( owner, 2 );
		_lowWaitTimeThreshold = new UndoRedo<int>( owner, 30 );
		_lowWaitTimeFactor = new UndoRedo<float>( owner, 2.0f );
		_manoeuvresMinPopulation = new UndoRedo<int>( owner, 25 );
		_manoeuvresMaxPopulation = new UndoRedo<int>( owner, 10 );
		_guardManoeuvresMinPopulation = new UndoRedo<int>( owner, 10 );
		_guardManoeuvresMaxPopulation = new UndoRedo<int>( owner, 10 );
		_manoeuvresWaitThreshold = new UndoRedo<float>( owner, 180.0f );
		_manoeuvresFullSweepSubset = new UndoRedo<int>( owner, 15 );
		_trainingFemaleBotsCount = new UndoRedo<int>( owner, 1 );
		_necessaryLadiesCount = new UndoRedo<int>( owner, 1 );
		_partySkillCompensation = new UndoRedoList<float>( owner );
		_loseStreakCorrection = new MMakingLoseStreakCorrection( owner );
		_highRatingThreshold = new UndoRedo<int>( owner, 1800 );
		_proRatingThreshold = new UndoRedo<int>( owner, 2000 );
		_noobGamesMaxNormalRating = new UndoRedo<int>( owner, 1500 );
		_highRatingCooldown = new UndoRedo<int>( owner, 60 );
		_noobsTimeout = new UndoRedo<float>( owner, 45.0f );
		_minimalNoobsPercentage = new UndoRedo<int>( owner, 60 );
		_fullPartyGameRatingDiffMin = new UndoRedo<int>( owner, 30 );
		_fullPartyGameRatingDiffMax = new UndoRedo<int>( owner, 200 );
		_waitTimeSoftLimit = new UndoRedo<int>( owner, 240 );
		_waitTimeHardLimit = new UndoRedo<int>( owner, 600 );
		_teamLeaversTimeTrashold = new UndoRedo<int>( owner, 600 );
		_gameLeaversTimeTrashold = new UndoRedo<int>( owner, 300 );
		_locationPingSettings = new MMakingLocationPingSettings( owner );
		_waitVsProbability = new MMakingWaitVsProbability( owner );
		_ranks = new UndoRedoAssignableList<MMakingRank>( owner );
		_recessionTableForForceMM = new UndoRedoAssignableList<RecessionData>( owner, typeof( ESweepStage ) );
		_recessionPremiumTable = new UndoRedoList<float>( owner );
		_recessionFullPartyTableForForceMM = new RecessionFullPartyTableForForceMM( owner );
		_recessionPremiumTimeThreshold = new UndoRedo<float>( owner, 0.0f );
		_recessionTableForPlayerRatingMM = new RecessionTableForPlayerRatingMM( owner );
		_playerDiff = new UndoRedo<int>( owner, 5 );
		_rankDifferenceTimePenalty = new UndoRedo<float>( owner, 180.0f );
		_heroClassLimitsAttenuationTime = new UndoRedo<float>( owner, 120.0f );
		_useRanking = new UndoRedo<bool>( owner, false );
		_optimalClasses = new UndoRedoAssignableList<MMakingHeroClass>( owner, typeof( MMakingHeroClassEnum ) );
		_delayPerDonorLocalePlayer = new UndoRedoList<float>( owner );
		_fullPartySize = new UndoRedo<int>( owner, 5 );
		_fullPartyVsRandomTimeThreshold = new UndoRedo<float>( owner, 30.0f );
		_localeWaitTimeThreshold = new UndoRedo<int>( owner, 45 );
		_ratingScale = new MMakingScale( owner );
		_forceScale = new MMakingScale( owner );
		_TeamSideTimeTreshold = new UndoRedo<float>( owner, 120.0f );
		___parent.Changed += FireChangedEvent;
		_mock.Changed += FireChangedEvent;
		_isTournamentMap.Changed += FireChangedEvent;
		_estimFunctionWeights.Changed += FireChangedEvent;
		_normalBasePointsRepeatFactor.Changed += FireChangedEvent;
		_noobBasePointsRepeatFactor.Changed += FireChangedEvent;
		_ratingDiffGrowTime.Changed += FireChangedEvent;
		_fullSweepSubsetLimit.Changed += FireChangedEvent;
		_fullSweepSubsetLimitPve.Changed += FireChangedEvent;
		_estimFunDecreaseTimeBegin.Changed += FireChangedEvent;
		_estimFunDecreaseTimeEnd.Changed += FireChangedEvent;
		_estimFunDecreaseFactor.Changed += FireChangedEvent;
		_estimFunManoeuvresDecreaseFactor.Changed += FireChangedEvent;
		_identicalHeroesSampleLimit.Changed += FireChangedEvent;
		_identicalGuardHeroesSampleLimit.Changed += FireChangedEvent;
		_identicalNoobHeroesSampleLimit.Changed += FireChangedEvent;
		_lowWaitTimeThreshold.Changed += FireChangedEvent;
		_lowWaitTimeFactor.Changed += FireChangedEvent;
		_manoeuvresMinPopulation.Changed += FireChangedEvent;
		_manoeuvresMaxPopulation.Changed += FireChangedEvent;
		_guardManoeuvresMinPopulation.Changed += FireChangedEvent;
		_guardManoeuvresMaxPopulation.Changed += FireChangedEvent;
		_manoeuvresWaitThreshold.Changed += FireChangedEvent;
		_manoeuvresFullSweepSubset.Changed += FireChangedEvent;
		_trainingFemaleBotsCount.Changed += FireChangedEvent;
		_necessaryLadiesCount.Changed += FireChangedEvent;
		_partySkillCompensation.Changed += FireChangedEvent;
		_loseStreakCorrection.Changed += FireChangedEvent;
		_highRatingThreshold.Changed += FireChangedEvent;
		_proRatingThreshold.Changed += FireChangedEvent;
		_noobGamesMaxNormalRating.Changed += FireChangedEvent;
		_highRatingCooldown.Changed += FireChangedEvent;
		_noobsTimeout.Changed += FireChangedEvent;
		_minimalNoobsPercentage.Changed += FireChangedEvent;
		_fullPartyGameRatingDiffMin.Changed += FireChangedEvent;
		_fullPartyGameRatingDiffMax.Changed += FireChangedEvent;
		_waitTimeSoftLimit.Changed += FireChangedEvent;
		_waitTimeHardLimit.Changed += FireChangedEvent;
		_teamLeaversTimeTrashold.Changed += FireChangedEvent;
		_gameLeaversTimeTrashold.Changed += FireChangedEvent;
		_locationPingSettings.Changed += FireChangedEvent;
		_waitVsProbability.Changed += FireChangedEvent;
		_ranks.Changed += FireChangedEvent;
		_recessionTableForForceMM.Changed += FireChangedEvent;
		_recessionPremiumTable.Changed += FireChangedEvent;
		_recessionFullPartyTableForForceMM.Changed += FireChangedEvent;
		_recessionPremiumTimeThreshold.Changed += FireChangedEvent;
		_recessionTableForPlayerRatingMM.Changed += FireChangedEvent;
		_playerDiff.Changed += FireChangedEvent;
		_rankDifferenceTimePenalty.Changed += FireChangedEvent;
		_heroClassLimitsAttenuationTime.Changed += FireChangedEvent;
		_useRanking.Changed += FireChangedEvent;
		_optimalClasses.Changed += FireChangedEvent;
		_delayPerDonorLocalePlayer.Changed += FireChangedEvent;
		_fullPartySize.Changed += FireChangedEvent;
		_fullPartyVsRandomTimeThreshold.Changed += FireChangedEvent;
		_localeWaitTimeThreshold.Changed += FireChangedEvent;
		_ratingScale.Changed += FireChangedEvent;
		_forceScale.Changed += FireChangedEvent;
		_TeamSideTimeTreshold.Changed += FireChangedEvent;
	}

	public MapMMakingSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( MapMMakingSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MapMMakingSettings" );
		mock = source.mock;
		isTournamentMap = source.isTournamentMap;
		estimFunctionWeights = source.estimFunctionWeights;
		normalBasePointsRepeatFactor = source.normalBasePointsRepeatFactor;
		noobBasePointsRepeatFactor = source.noobBasePointsRepeatFactor;
		ratingDiffGrowTime = source.ratingDiffGrowTime;
		fullSweepSubsetLimit = source.fullSweepSubsetLimit;
		fullSweepSubsetLimitPve = source.fullSweepSubsetLimitPve;
		estimFunDecreaseTimeBegin = source.estimFunDecreaseTimeBegin;
		estimFunDecreaseTimeEnd = source.estimFunDecreaseTimeEnd;
		estimFunDecreaseFactor = source.estimFunDecreaseFactor;
		estimFunManoeuvresDecreaseFactor = source.estimFunManoeuvresDecreaseFactor;
		identicalHeroesSampleLimit = source.identicalHeroesSampleLimit;
		identicalGuardHeroesSampleLimit = source.identicalGuardHeroesSampleLimit;
		identicalNoobHeroesSampleLimit = source.identicalNoobHeroesSampleLimit;
		lowWaitTimeThreshold = source.lowWaitTimeThreshold;
		lowWaitTimeFactor = source.lowWaitTimeFactor;
		manoeuvresMinPopulation = source.manoeuvresMinPopulation;
		manoeuvresMaxPopulation = source.manoeuvresMaxPopulation;
		guardManoeuvresMinPopulation = source.guardManoeuvresMinPopulation;
		guardManoeuvresMaxPopulation = source.guardManoeuvresMaxPopulation;
		manoeuvresWaitThreshold = source.manoeuvresWaitThreshold;
		manoeuvresFullSweepSubset = source.manoeuvresFullSweepSubset;
		trainingFemaleBotsCount = source.trainingFemaleBotsCount;
		necessaryLadiesCount = source.necessaryLadiesCount;
		partySkillCompensation = source.partySkillCompensation;
		loseStreakCorrection = source.loseStreakCorrection;
		highRatingThreshold = source.highRatingThreshold;
		proRatingThreshold = source.proRatingThreshold;
		noobGamesMaxNormalRating = source.noobGamesMaxNormalRating;
		highRatingCooldown = source.highRatingCooldown;
		noobsTimeout = source.noobsTimeout;
		minimalNoobsPercentage = source.minimalNoobsPercentage;
		fullPartyGameRatingDiffMin = source.fullPartyGameRatingDiffMin;
		fullPartyGameRatingDiffMax = source.fullPartyGameRatingDiffMax;
		waitTimeSoftLimit = source.waitTimeSoftLimit;
		waitTimeHardLimit = source.waitTimeHardLimit;
		teamLeaversTimeTrashold = source.teamLeaversTimeTrashold;
		gameLeaversTimeTrashold = source.gameLeaversTimeTrashold;
		locationPingSettings = source.locationPingSettings;
		waitVsProbability = source.waitVsProbability;
		ranks = source.ranks;
		recessionTableForForceMM = source.recessionTableForForceMM;
		recessionPremiumTable = source.recessionPremiumTable;
		recessionFullPartyTableForForceMM = source.recessionFullPartyTableForForceMM;
		recessionPremiumTimeThreshold = source.recessionPremiumTimeThreshold;
		recessionTableForPlayerRatingMM = source.recessionTableForPlayerRatingMM;
		playerDiff = source.playerDiff;
		rankDifferenceTimePenalty = source.rankDifferenceTimePenalty;
		heroClassLimitsAttenuationTime = source.heroClassLimitsAttenuationTime;
		useRanking = source.useRanking;
		optimalClasses = source.optimalClasses;
		delayPerDonorLocalePlayer = source.delayPerDonorLocalePlayer;
		fullPartySize = source.fullPartySize;
		fullPartyVsRandomTimeThreshold = source.fullPartyVsRandomTimeThreshold;
		localeWaitTimeThreshold = source.localeWaitTimeThreshold;
		ratingScale = source.ratingScale;
		forceScale = source.forceScale;
		TeamSideTimeTreshold = source.TeamSideTimeTreshold;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MapMMakingSettings source = _source as MapMMakingSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MapMMakingSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MapMMakingSettings newParent = rawParent == null ? null : rawParent.Get<MapMMakingSettings>();
		if ( newParent == null && _newParent is MapMMakingSettings )
			newParent = _newParent as MapMMakingSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mock.SetParent( newParent == null ? null : newParent._mock );
		_isTournamentMap.SetParent( newParent == null ? null : newParent._isTournamentMap );
		_estimFunctionWeights.SetParent( newParent == null ? null : newParent._estimFunctionWeights );
		_normalBasePointsRepeatFactor.SetParent( newParent == null ? null : newParent._normalBasePointsRepeatFactor );
		_noobBasePointsRepeatFactor.SetParent( newParent == null ? null : newParent._noobBasePointsRepeatFactor );
		_ratingDiffGrowTime.SetParent( newParent == null ? null : newParent._ratingDiffGrowTime );
		_fullSweepSubsetLimit.SetParent( newParent == null ? null : newParent._fullSweepSubsetLimit );
		_fullSweepSubsetLimitPve.SetParent( newParent == null ? null : newParent._fullSweepSubsetLimitPve );
		_estimFunDecreaseTimeBegin.SetParent( newParent == null ? null : newParent._estimFunDecreaseTimeBegin );
		_estimFunDecreaseTimeEnd.SetParent( newParent == null ? null : newParent._estimFunDecreaseTimeEnd );
		_estimFunDecreaseFactor.SetParent( newParent == null ? null : newParent._estimFunDecreaseFactor );
		_estimFunManoeuvresDecreaseFactor.SetParent( newParent == null ? null : newParent._estimFunManoeuvresDecreaseFactor );
		_identicalHeroesSampleLimit.SetParent( newParent == null ? null : newParent._identicalHeroesSampleLimit );
		_identicalGuardHeroesSampleLimit.SetParent( newParent == null ? null : newParent._identicalGuardHeroesSampleLimit );
		_identicalNoobHeroesSampleLimit.SetParent( newParent == null ? null : newParent._identicalNoobHeroesSampleLimit );
		_lowWaitTimeThreshold.SetParent( newParent == null ? null : newParent._lowWaitTimeThreshold );
		_lowWaitTimeFactor.SetParent( newParent == null ? null : newParent._lowWaitTimeFactor );
		_manoeuvresMinPopulation.SetParent( newParent == null ? null : newParent._manoeuvresMinPopulation );
		_manoeuvresMaxPopulation.SetParent( newParent == null ? null : newParent._manoeuvresMaxPopulation );
		_guardManoeuvresMinPopulation.SetParent( newParent == null ? null : newParent._guardManoeuvresMinPopulation );
		_guardManoeuvresMaxPopulation.SetParent( newParent == null ? null : newParent._guardManoeuvresMaxPopulation );
		_manoeuvresWaitThreshold.SetParent( newParent == null ? null : newParent._manoeuvresWaitThreshold );
		_manoeuvresFullSweepSubset.SetParent( newParent == null ? null : newParent._manoeuvresFullSweepSubset );
		_trainingFemaleBotsCount.SetParent( newParent == null ? null : newParent._trainingFemaleBotsCount );
		_necessaryLadiesCount.SetParent( newParent == null ? null : newParent._necessaryLadiesCount );
		_partySkillCompensation.SetParent( newParent == null ? null : newParent._partySkillCompensation );
		_loseStreakCorrection.SetParent( newParent == null ? null : newParent._loseStreakCorrection );
		_highRatingThreshold.SetParent( newParent == null ? null : newParent._highRatingThreshold );
		_proRatingThreshold.SetParent( newParent == null ? null : newParent._proRatingThreshold );
		_noobGamesMaxNormalRating.SetParent( newParent == null ? null : newParent._noobGamesMaxNormalRating );
		_highRatingCooldown.SetParent( newParent == null ? null : newParent._highRatingCooldown );
		_noobsTimeout.SetParent( newParent == null ? null : newParent._noobsTimeout );
		_minimalNoobsPercentage.SetParent( newParent == null ? null : newParent._minimalNoobsPercentage );
		_fullPartyGameRatingDiffMin.SetParent( newParent == null ? null : newParent._fullPartyGameRatingDiffMin );
		_fullPartyGameRatingDiffMax.SetParent( newParent == null ? null : newParent._fullPartyGameRatingDiffMax );
		_waitTimeSoftLimit.SetParent( newParent == null ? null : newParent._waitTimeSoftLimit );
		_waitTimeHardLimit.SetParent( newParent == null ? null : newParent._waitTimeHardLimit );
		_teamLeaversTimeTrashold.SetParent( newParent == null ? null : newParent._teamLeaversTimeTrashold );
		_gameLeaversTimeTrashold.SetParent( newParent == null ? null : newParent._gameLeaversTimeTrashold );
		_locationPingSettings.SetParent( newParent == null ? null : newParent._locationPingSettings );
		_waitVsProbability.SetParent( newParent == null ? null : newParent._waitVsProbability );
		_ranks.SetParent( newParent == null ? null : newParent._ranks );
		_recessionTableForForceMM.SetParent( newParent == null ? null : newParent._recessionTableForForceMM );
		_recessionPremiumTable.SetParent( newParent == null ? null : newParent._recessionPremiumTable );
		_recessionFullPartyTableForForceMM.SetParent( newParent == null ? null : newParent._recessionFullPartyTableForForceMM );
		_recessionPremiumTimeThreshold.SetParent( newParent == null ? null : newParent._recessionPremiumTimeThreshold );
		_recessionTableForPlayerRatingMM.SetParent( newParent == null ? null : newParent._recessionTableForPlayerRatingMM );
		_playerDiff.SetParent( newParent == null ? null : newParent._playerDiff );
		_rankDifferenceTimePenalty.SetParent( newParent == null ? null : newParent._rankDifferenceTimePenalty );
		_heroClassLimitsAttenuationTime.SetParent( newParent == null ? null : newParent._heroClassLimitsAttenuationTime );
		_useRanking.SetParent( newParent == null ? null : newParent._useRanking );
		_optimalClasses.SetParent( newParent == null ? null : newParent._optimalClasses );
		_delayPerDonorLocalePlayer.SetParent( newParent == null ? null : newParent._delayPerDonorLocalePlayer );
		_fullPartySize.SetParent( newParent == null ? null : newParent._fullPartySize );
		_fullPartyVsRandomTimeThreshold.SetParent( newParent == null ? null : newParent._fullPartyVsRandomTimeThreshold );
		_localeWaitTimeThreshold.SetParent( newParent == null ? null : newParent._localeWaitTimeThreshold );
		_ratingScale.SetParent( newParent == null ? null : newParent._ratingScale );
		_forceScale.SetParent( newParent == null ? null : newParent._forceScale );
		_TeamSideTimeTreshold.SetParent( newParent == null ? null : newParent._TeamSideTimeTreshold );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mock.Reset();
		_isTournamentMap.Reset();
		_estimFunctionWeights.Reset();
		_normalBasePointsRepeatFactor.Reset();
		_noobBasePointsRepeatFactor.Reset();
		_ratingDiffGrowTime.Reset();
		_fullSweepSubsetLimit.Reset();
		_fullSweepSubsetLimitPve.Reset();
		_estimFunDecreaseTimeBegin.Reset();
		_estimFunDecreaseTimeEnd.Reset();
		_estimFunDecreaseFactor.Reset();
		_estimFunManoeuvresDecreaseFactor.Reset();
		_identicalHeroesSampleLimit.Reset();
		_identicalGuardHeroesSampleLimit.Reset();
		_identicalNoobHeroesSampleLimit.Reset();
		_lowWaitTimeThreshold.Reset();
		_lowWaitTimeFactor.Reset();
		_manoeuvresMinPopulation.Reset();
		_manoeuvresMaxPopulation.Reset();
		_guardManoeuvresMinPopulation.Reset();
		_guardManoeuvresMaxPopulation.Reset();
		_manoeuvresWaitThreshold.Reset();
		_manoeuvresFullSweepSubset.Reset();
		_trainingFemaleBotsCount.Reset();
		_necessaryLadiesCount.Reset();
		_partySkillCompensation.Reset();
		_loseStreakCorrection.Reset();
		_highRatingThreshold.Reset();
		_proRatingThreshold.Reset();
		_noobGamesMaxNormalRating.Reset();
		_highRatingCooldown.Reset();
		_noobsTimeout.Reset();
		_minimalNoobsPercentage.Reset();
		_fullPartyGameRatingDiffMin.Reset();
		_fullPartyGameRatingDiffMax.Reset();
		_waitTimeSoftLimit.Reset();
		_waitTimeHardLimit.Reset();
		_teamLeaversTimeTrashold.Reset();
		_gameLeaversTimeTrashold.Reset();
		_locationPingSettings.Reset();
		_waitVsProbability.Reset();
		_ranks.Reset();
		_recessionTableForForceMM.Reset();
		_recessionPremiumTable.Reset();
		_recessionFullPartyTableForForceMM.Reset();
		_recessionPremiumTimeThreshold.Reset();
		_recessionTableForPlayerRatingMM.Reset();
		_playerDiff.Reset();
		_rankDifferenceTimePenalty.Reset();
		_heroClassLimitsAttenuationTime.Reset();
		_useRanking.Reset();
		_optimalClasses.Reset();
		_delayPerDonorLocalePlayer.Reset();
		_fullPartySize.Reset();
		_fullPartyVsRandomTimeThreshold.Reset();
		_localeWaitTimeThreshold.Reset();
		_ratingScale.Reset();
		_forceScale.Reset();
		_TeamSideTimeTreshold.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mock.IsDerivedFromParent()
			&& _isTournamentMap.IsDerivedFromParent()
			&& _estimFunctionWeights.IsDerivedFromParent()
			&& _normalBasePointsRepeatFactor.IsDerivedFromParent()
			&& _noobBasePointsRepeatFactor.IsDerivedFromParent()
			&& _ratingDiffGrowTime.IsDerivedFromParent()
			&& _fullSweepSubsetLimit.IsDerivedFromParent()
			&& _fullSweepSubsetLimitPve.IsDerivedFromParent()
			&& _estimFunDecreaseTimeBegin.IsDerivedFromParent()
			&& _estimFunDecreaseTimeEnd.IsDerivedFromParent()
			&& _estimFunDecreaseFactor.IsDerivedFromParent()
			&& _estimFunManoeuvresDecreaseFactor.IsDerivedFromParent()
			&& _identicalHeroesSampleLimit.IsDerivedFromParent()
			&& _identicalGuardHeroesSampleLimit.IsDerivedFromParent()
			&& _identicalNoobHeroesSampleLimit.IsDerivedFromParent()
			&& _lowWaitTimeThreshold.IsDerivedFromParent()
			&& _lowWaitTimeFactor.IsDerivedFromParent()
			&& _manoeuvresMinPopulation.IsDerivedFromParent()
			&& _manoeuvresMaxPopulation.IsDerivedFromParent()
			&& _guardManoeuvresMinPopulation.IsDerivedFromParent()
			&& _guardManoeuvresMaxPopulation.IsDerivedFromParent()
			&& _manoeuvresWaitThreshold.IsDerivedFromParent()
			&& _manoeuvresFullSweepSubset.IsDerivedFromParent()
			&& _trainingFemaleBotsCount.IsDerivedFromParent()
			&& _necessaryLadiesCount.IsDerivedFromParent()
			&& _partySkillCompensation.IsDerivedFromParent()
			&& _loseStreakCorrection.IsDerivedFromParent()
			&& _highRatingThreshold.IsDerivedFromParent()
			&& _proRatingThreshold.IsDerivedFromParent()
			&& _noobGamesMaxNormalRating.IsDerivedFromParent()
			&& _highRatingCooldown.IsDerivedFromParent()
			&& _noobsTimeout.IsDerivedFromParent()
			&& _minimalNoobsPercentage.IsDerivedFromParent()
			&& _fullPartyGameRatingDiffMin.IsDerivedFromParent()
			&& _fullPartyGameRatingDiffMax.IsDerivedFromParent()
			&& _waitTimeSoftLimit.IsDerivedFromParent()
			&& _waitTimeHardLimit.IsDerivedFromParent()
			&& _teamLeaversTimeTrashold.IsDerivedFromParent()
			&& _gameLeaversTimeTrashold.IsDerivedFromParent()
			&& _locationPingSettings.IsDerivedFromParent()
			&& _waitVsProbability.IsDerivedFromParent()
			&& _ranks.IsDerivedFromParent()
			&& _recessionTableForForceMM.IsDerivedFromParent()
			&& _recessionPremiumTable.IsDerivedFromParent()
			&& _recessionFullPartyTableForForceMM.IsDerivedFromParent()
			&& _recessionPremiumTimeThreshold.IsDerivedFromParent()
			&& _recessionTableForPlayerRatingMM.IsDerivedFromParent()
			&& _playerDiff.IsDerivedFromParent()
			&& _rankDifferenceTimePenalty.IsDerivedFromParent()
			&& _heroClassLimitsAttenuationTime.IsDerivedFromParent()
			&& _useRanking.IsDerivedFromParent()
			&& _optimalClasses.IsDerivedFromParent()
			&& _delayPerDonorLocalePlayer.IsDerivedFromParent()
			&& _fullPartySize.IsDerivedFromParent()
			&& _fullPartyVsRandomTimeThreshold.IsDerivedFromParent()
			&& _localeWaitTimeThreshold.IsDerivedFromParent()
			&& _ratingScale.IsDerivedFromParent()
			&& _forceScale.IsDerivedFromParent()
			&& _TeamSideTimeTreshold.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mock" )
			_mock.Reset();
		else if ( fieldName == "isTournamentMap" )
			_isTournamentMap.Reset();
		else if ( fieldName == "estimFunctionWeights" )
			_estimFunctionWeights.Reset();
		else if ( fieldName == "normalBasePointsRepeatFactor" )
			_normalBasePointsRepeatFactor.Reset();
		else if ( fieldName == "noobBasePointsRepeatFactor" )
			_noobBasePointsRepeatFactor.Reset();
		else if ( fieldName == "ratingDiffGrowTime" )
			_ratingDiffGrowTime.Reset();
		else if ( fieldName == "fullSweepSubsetLimit" )
			_fullSweepSubsetLimit.Reset();
		else if ( fieldName == "fullSweepSubsetLimitPve" )
			_fullSweepSubsetLimitPve.Reset();
		else if ( fieldName == "estimFunDecreaseTimeBegin" )
			_estimFunDecreaseTimeBegin.Reset();
		else if ( fieldName == "estimFunDecreaseTimeEnd" )
			_estimFunDecreaseTimeEnd.Reset();
		else if ( fieldName == "estimFunDecreaseFactor" )
			_estimFunDecreaseFactor.Reset();
		else if ( fieldName == "estimFunManoeuvresDecreaseFactor" )
			_estimFunManoeuvresDecreaseFactor.Reset();
		else if ( fieldName == "identicalHeroesSampleLimit" )
			_identicalHeroesSampleLimit.Reset();
		else if ( fieldName == "identicalGuardHeroesSampleLimit" )
			_identicalGuardHeroesSampleLimit.Reset();
		else if ( fieldName == "identicalNoobHeroesSampleLimit" )
			_identicalNoobHeroesSampleLimit.Reset();
		else if ( fieldName == "lowWaitTimeThreshold" )
			_lowWaitTimeThreshold.Reset();
		else if ( fieldName == "lowWaitTimeFactor" )
			_lowWaitTimeFactor.Reset();
		else if ( fieldName == "manoeuvresMinPopulation" )
			_manoeuvresMinPopulation.Reset();
		else if ( fieldName == "manoeuvresMaxPopulation" )
			_manoeuvresMaxPopulation.Reset();
		else if ( fieldName == "guardManoeuvresMinPopulation" )
			_guardManoeuvresMinPopulation.Reset();
		else if ( fieldName == "guardManoeuvresMaxPopulation" )
			_guardManoeuvresMaxPopulation.Reset();
		else if ( fieldName == "manoeuvresWaitThreshold" )
			_manoeuvresWaitThreshold.Reset();
		else if ( fieldName == "manoeuvresFullSweepSubset" )
			_manoeuvresFullSweepSubset.Reset();
		else if ( fieldName == "trainingFemaleBotsCount" )
			_trainingFemaleBotsCount.Reset();
		else if ( fieldName == "necessaryLadiesCount" )
			_necessaryLadiesCount.Reset();
		else if ( fieldName == "partySkillCompensation" )
			_partySkillCompensation.Reset();
		else if ( fieldName == "loseStreakCorrection" )
			_loseStreakCorrection.Reset();
		else if ( fieldName == "highRatingThreshold" )
			_highRatingThreshold.Reset();
		else if ( fieldName == "proRatingThreshold" )
			_proRatingThreshold.Reset();
		else if ( fieldName == "noobGamesMaxNormalRating" )
			_noobGamesMaxNormalRating.Reset();
		else if ( fieldName == "highRatingCooldown" )
			_highRatingCooldown.Reset();
		else if ( fieldName == "noobsTimeout" )
			_noobsTimeout.Reset();
		else if ( fieldName == "minimalNoobsPercentage" )
			_minimalNoobsPercentage.Reset();
		else if ( fieldName == "fullPartyGameRatingDiffMin" )
			_fullPartyGameRatingDiffMin.Reset();
		else if ( fieldName == "fullPartyGameRatingDiffMax" )
			_fullPartyGameRatingDiffMax.Reset();
		else if ( fieldName == "waitTimeSoftLimit" )
			_waitTimeSoftLimit.Reset();
		else if ( fieldName == "waitTimeHardLimit" )
			_waitTimeHardLimit.Reset();
		else if ( fieldName == "teamLeaversTimeTrashold" )
			_teamLeaversTimeTrashold.Reset();
		else if ( fieldName == "gameLeaversTimeTrashold" )
			_gameLeaversTimeTrashold.Reset();
		else if ( fieldName == "locationPingSettings" )
			_locationPingSettings.Reset();
		else if ( fieldName == "waitVsProbability" )
			_waitVsProbability.Reset();
		else if ( fieldName == "ranks" )
			_ranks.Reset();
		else if ( fieldName == "recessionTableForForceMM" )
			_recessionTableForForceMM.Reset();
		else if ( fieldName == "recessionPremiumTable" )
			_recessionPremiumTable.Reset();
		else if ( fieldName == "recessionFullPartyTableForForceMM" )
			_recessionFullPartyTableForForceMM.Reset();
		else if ( fieldName == "recessionPremiumTimeThreshold" )
			_recessionPremiumTimeThreshold.Reset();
		else if ( fieldName == "recessionTableForPlayerRatingMM" )
			_recessionTableForPlayerRatingMM.Reset();
		else if ( fieldName == "playerDiff" )
			_playerDiff.Reset();
		else if ( fieldName == "rankDifferenceTimePenalty" )
			_rankDifferenceTimePenalty.Reset();
		else if ( fieldName == "heroClassLimitsAttenuationTime" )
			_heroClassLimitsAttenuationTime.Reset();
		else if ( fieldName == "useRanking" )
			_useRanking.Reset();
		else if ( fieldName == "optimalClasses" )
			_optimalClasses.Reset();
		else if ( fieldName == "delayPerDonorLocalePlayer" )
			_delayPerDonorLocalePlayer.Reset();
		else if ( fieldName == "fullPartySize" )
			_fullPartySize.Reset();
		else if ( fieldName == "fullPartyVsRandomTimeThreshold" )
			_fullPartyVsRandomTimeThreshold.Reset();
		else if ( fieldName == "localeWaitTimeThreshold" )
			_localeWaitTimeThreshold.Reset();
		else if ( fieldName == "ratingScale" )
			_ratingScale.Reset();
		else if ( fieldName == "forceScale" )
			_forceScale.Reset();
		else if ( fieldName == "TeamSideTimeTreshold" )
			_TeamSideTimeTreshold.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mock" )
			return _mock.IsDerivedFromParent();
		if ( fieldName == "isTournamentMap" )
			return _isTournamentMap.IsDerivedFromParent();
		if ( fieldName == "estimFunctionWeights" )
			return _estimFunctionWeights.IsDerivedFromParent();
		if ( fieldName == "normalBasePointsRepeatFactor" )
			return _normalBasePointsRepeatFactor.IsDerivedFromParent();
		if ( fieldName == "noobBasePointsRepeatFactor" )
			return _noobBasePointsRepeatFactor.IsDerivedFromParent();
		if ( fieldName == "ratingDiffGrowTime" )
			return _ratingDiffGrowTime.IsDerivedFromParent();
		if ( fieldName == "fullSweepSubsetLimit" )
			return _fullSweepSubsetLimit.IsDerivedFromParent();
		if ( fieldName == "fullSweepSubsetLimitPve" )
			return _fullSweepSubsetLimitPve.IsDerivedFromParent();
		if ( fieldName == "estimFunDecreaseTimeBegin" )
			return _estimFunDecreaseTimeBegin.IsDerivedFromParent();
		if ( fieldName == "estimFunDecreaseTimeEnd" )
			return _estimFunDecreaseTimeEnd.IsDerivedFromParent();
		if ( fieldName == "estimFunDecreaseFactor" )
			return _estimFunDecreaseFactor.IsDerivedFromParent();
		if ( fieldName == "estimFunManoeuvresDecreaseFactor" )
			return _estimFunManoeuvresDecreaseFactor.IsDerivedFromParent();
		if ( fieldName == "identicalHeroesSampleLimit" )
			return _identicalHeroesSampleLimit.IsDerivedFromParent();
		if ( fieldName == "identicalGuardHeroesSampleLimit" )
			return _identicalGuardHeroesSampleLimit.IsDerivedFromParent();
		if ( fieldName == "identicalNoobHeroesSampleLimit" )
			return _identicalNoobHeroesSampleLimit.IsDerivedFromParent();
		if ( fieldName == "lowWaitTimeThreshold" )
			return _lowWaitTimeThreshold.IsDerivedFromParent();
		if ( fieldName == "lowWaitTimeFactor" )
			return _lowWaitTimeFactor.IsDerivedFromParent();
		if ( fieldName == "manoeuvresMinPopulation" )
			return _manoeuvresMinPopulation.IsDerivedFromParent();
		if ( fieldName == "manoeuvresMaxPopulation" )
			return _manoeuvresMaxPopulation.IsDerivedFromParent();
		if ( fieldName == "guardManoeuvresMinPopulation" )
			return _guardManoeuvresMinPopulation.IsDerivedFromParent();
		if ( fieldName == "guardManoeuvresMaxPopulation" )
			return _guardManoeuvresMaxPopulation.IsDerivedFromParent();
		if ( fieldName == "manoeuvresWaitThreshold" )
			return _manoeuvresWaitThreshold.IsDerivedFromParent();
		if ( fieldName == "manoeuvresFullSweepSubset" )
			return _manoeuvresFullSweepSubset.IsDerivedFromParent();
		if ( fieldName == "trainingFemaleBotsCount" )
			return _trainingFemaleBotsCount.IsDerivedFromParent();
		if ( fieldName == "necessaryLadiesCount" )
			return _necessaryLadiesCount.IsDerivedFromParent();
		if ( fieldName == "partySkillCompensation" )
			return _partySkillCompensation.IsDerivedFromParent();
		if ( fieldName == "loseStreakCorrection" )
			return _loseStreakCorrection.IsDerivedFromParent();
		if ( fieldName == "highRatingThreshold" )
			return _highRatingThreshold.IsDerivedFromParent();
		if ( fieldName == "proRatingThreshold" )
			return _proRatingThreshold.IsDerivedFromParent();
		if ( fieldName == "noobGamesMaxNormalRating" )
			return _noobGamesMaxNormalRating.IsDerivedFromParent();
		if ( fieldName == "highRatingCooldown" )
			return _highRatingCooldown.IsDerivedFromParent();
		if ( fieldName == "noobsTimeout" )
			return _noobsTimeout.IsDerivedFromParent();
		if ( fieldName == "minimalNoobsPercentage" )
			return _minimalNoobsPercentage.IsDerivedFromParent();
		if ( fieldName == "fullPartyGameRatingDiffMin" )
			return _fullPartyGameRatingDiffMin.IsDerivedFromParent();
		if ( fieldName == "fullPartyGameRatingDiffMax" )
			return _fullPartyGameRatingDiffMax.IsDerivedFromParent();
		if ( fieldName == "waitTimeSoftLimit" )
			return _waitTimeSoftLimit.IsDerivedFromParent();
		if ( fieldName == "waitTimeHardLimit" )
			return _waitTimeHardLimit.IsDerivedFromParent();
		if ( fieldName == "teamLeaversTimeTrashold" )
			return _teamLeaversTimeTrashold.IsDerivedFromParent();
		if ( fieldName == "gameLeaversTimeTrashold" )
			return _gameLeaversTimeTrashold.IsDerivedFromParent();
		if ( fieldName == "locationPingSettings" )
			return _locationPingSettings.IsDerivedFromParent();
		if ( fieldName == "waitVsProbability" )
			return _waitVsProbability.IsDerivedFromParent();
		if ( fieldName == "ranks" )
			return _ranks.IsDerivedFromParent();
		if ( fieldName == "recessionTableForForceMM" )
			return _recessionTableForForceMM.IsDerivedFromParent();
		if ( fieldName == "recessionPremiumTable" )
			return _recessionPremiumTable.IsDerivedFromParent();
		if ( fieldName == "recessionFullPartyTableForForceMM" )
			return _recessionFullPartyTableForForceMM.IsDerivedFromParent();
		if ( fieldName == "recessionPremiumTimeThreshold" )
			return _recessionPremiumTimeThreshold.IsDerivedFromParent();
		if ( fieldName == "recessionTableForPlayerRatingMM" )
			return _recessionTableForPlayerRatingMM.IsDerivedFromParent();
		if ( fieldName == "playerDiff" )
			return _playerDiff.IsDerivedFromParent();
		if ( fieldName == "rankDifferenceTimePenalty" )
			return _rankDifferenceTimePenalty.IsDerivedFromParent();
		if ( fieldName == "heroClassLimitsAttenuationTime" )
			return _heroClassLimitsAttenuationTime.IsDerivedFromParent();
		if ( fieldName == "useRanking" )
			return _useRanking.IsDerivedFromParent();
		if ( fieldName == "optimalClasses" )
			return _optimalClasses.IsDerivedFromParent();
		if ( fieldName == "delayPerDonorLocalePlayer" )
			return _delayPerDonorLocalePlayer.IsDerivedFromParent();
		if ( fieldName == "fullPartySize" )
			return _fullPartySize.IsDerivedFromParent();
		if ( fieldName == "fullPartyVsRandomTimeThreshold" )
			return _fullPartyVsRandomTimeThreshold.IsDerivedFromParent();
		if ( fieldName == "localeWaitTimeThreshold" )
			return _localeWaitTimeThreshold.IsDerivedFromParent();
		if ( fieldName == "ratingScale" )
			return _ratingScale.IsDerivedFromParent();
		if ( fieldName == "forceScale" )
			return _forceScale.IsDerivedFromParent();
		if ( fieldName == "TeamSideTimeTreshold" )
			return _TeamSideTimeTreshold.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ROLLITEM")]
public class MarketingEventRollItem : RollItem
{
	private UndoRedoDBPtr<MarketingEventRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<MarketingEventRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedoDBPtr<BaseMarketingEvent> _marketingEvent;
	private UndoRedo<int> _count;
	private UndoRedoDBPtr<Texture> _image;
	private TextRef _tooltip;

	[Custom("DBServer", "Social")]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Custom("Social")]
	[NoCode]
	public DBPtr<BaseMarketingEvent> marketingEvent { get { return _marketingEvent.Get(); } set { _marketingEvent.Set( value ); } }

	[Custom("Social")]
	[NoCode]
	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MarketingEventRollItem>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_marketingEvent = new UndoRedoDBPtr<BaseMarketingEvent>( owner );
		_count = new UndoRedo<int>( owner, 0 );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_tooltip = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_marketingEvent.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
	}

	public MarketingEventRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( MarketingEventRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MarketingEventRollItem" );
		persistentId = source.persistentId;
		marketingEvent = source.marketingEvent;
		count = source.count;
		image = source.image;
		tooltip = source.tooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MarketingEventRollItem source = _source as MarketingEventRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MarketingEventRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MarketingEventRollItem newParent = rawParent == null ? null : rawParent.Get<MarketingEventRollItem>();
		if ( newParent == null && _newParent is MarketingEventRollItem )
			newParent = _newParent as MarketingEventRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_marketingEvent.SetParent( newParent == null ? null : newParent._marketingEvent );
		_count.SetParent( newParent == null ? null : newParent._count );
		_image.SetParent( newParent == null ? null : newParent._image );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_marketingEvent.Reset();
		_count.Reset();
		_image.Reset();
		_tooltip.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _marketingEvent.IsDerivedFromParent()
			&& _count.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "marketingEvent" )
			_marketingEvent.Reset();
		else if ( fieldName == "count" )
			_count.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
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
		if ( fieldName == "marketingEvent" )
			return _marketingEvent.IsDerivedFromParent();
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[DBVersion(0)]
[UseTypeName("MODEROLL")]
public class ModeRollSettings : DBResource
{
	private UndoRedoDBPtr<ModeRollSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<ModeRollSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _scoresCap;
	private UndoRedo<int> _containersOnWin;
	private UndoRedoDBPtr<RollContainerCountByRank> _containersOnFWOD;
	private UndoRedoDBPtr<ContainersBySpecialPoints> _containersBySpecialPoints;
	private UndoRedo<ETalentRollGroup> _allowedRollGroups;
	private UndoRedoAssignableList<DBPtr<RollContainer>> _containers;
	private UndoRedoAssignableList<DBPtr<RollContainer>> _premiumContainers;
	private UndoRedoAssignableList<DBPtr<RollContainer>> _additionalPremiumContainers;
	private UndoRedoDBPtr<RollContainer> _defaultContainer;
	private UndoRedoAssignableList<DBPtr<RollContainer>> _eventContainers;
	private UndoRedoAssignableList<DBPtr<RollContainer>> _premiumEventContainers;
	private UndoRedo<int> _enduranceGain;
	private UndoRedo<float> _enduranceCoeff;
	private UndoRedo<float> _enduranceFameCoeff;
	private UndoRedo<float> _enduranceExperienceCoeff;
	private UndoRedo<float> _enduranceResourcesCoeff;
	private UndoRedo<float> _leaversAwardsCoeff;
	private UndoRedo<int> _reliabilityOnFinishWin;
	private UndoRedo<int> _reliabilityOnFinishLose;
	private UndoRedo<int> _reliabilityOnFinishPeriod;
	private UndoRedo<int> _reliabilityOnFinishPerPeriod;
	private UndoRedo<int> _reliabilityOnLeave;
	private UndoRedo<int> _reliabilityOnLeavePeriod;
	private UndoRedo<int> _reliabilityOnLeavePerPeriod;
	private UndoRedo<int> _talentsMultiplicator;
	private UndoRedo<bool> _enduranceDisableRollBoost;
	private UndoRedoAssignableList<RollLevelInfo> _famePerSession;
	private UndoRedo<float> _fameLoseCoeff;
	private UndoRedo<float> _experienceLoseCoeff;
	private UndoRedo<float> _resourcesLoseCoeff;
	private UndoRedoAssignableList<RollLevelInfo> _experiencePerSession;
	private UndoRedo<int> _dodgePointsOnLeave;
	private UndoRedo<float> _ratingChangeMultiplier;
	private UndoRedo<int> _minSessionDuration;
	private UndoRedo<int> _applyPremiumTalent;
	private UndoRedoDBPtr<RollContainer> _FWODRewardContainer;
	private UndoRedo<string> _modeName;
	private UndoRedo<int> _version;
	private UndoRedo<bool> _teamWinDisconnectedWin;
	private UndoRedoDBPtr<ClanWarsSettings> _clanWarsSettings;
	private UndoRedo<int> _fullPartySize;

	[Description( "Scores cap" )]
	public int scoresCap { get { return _scoresCap.Get(); } set { _scoresCap.Set( value ); } }

	[Description( "Explicitly roll specified number of containers if player wins" )]
	public int containersOnWin { get { return _containersOnWin.Get(); } set { _containersOnWin.Set( value ); } }

	[Description( "Explicitly roll specified number of containers on player's first win of the day by player`s rank" )]
	public DBPtr<RollContainerCountByRank> containersOnFWOD { get { return _containersOnFWOD.Get(); } set { _containersOnFWOD.Set( value ); } }

	[Description( "Дополнительное кол-во контейнеров за спец очки" )]
	public DBPtr<ContainersBySpecialPoints> containersBySpecialPoints { get { return _containersBySpecialPoints.Get(); } set { _containersBySpecialPoints.Set( value ); } }

	[Description( "Allowed talent groups for roll" )]
	public ETalentRollGroup allowedRollGroups { get { return _allowedRollGroups.Get(); } set { _allowedRollGroups.Set( value ); } }

	[Description( "Default roll containers" )]
	public libdb.IChangeableList<DBPtr<RollContainer>> containers { get { return _containers; } set { _containers.Assign( value ); } }

	[Description( "Roll containers for premium roll" )]
	public libdb.IChangeableList<DBPtr<RollContainer>> premiumContainers { get { return _premiumContainers; } set { _premiumContainers.Assign( value ); } }

	[Description( "Roll containers for additional premium roll" )]
	public libdb.IChangeableList<DBPtr<RollContainer>> additionalPremiumContainers { get { return _additionalPremiumContainers; } set { _additionalPremiumContainers.Assign( value ); } }

	[Description( "Default container, rolled always" )]
	public DBPtr<RollContainer> defaultContainer { get { return _defaultContainer.Get(); } set { _defaultContainer.Set( value ); } }

	[Description( "event awards (доп награда, включаемая из конфигов)" )]
	public libdb.IChangeableList<DBPtr<RollContainer>> eventContainers { get { return _eventContainers; } set { _eventContainers.Assign( value ); } }

	[Description( "premium event awards (доп награда для ЗВ, включаемая из конфигов)" )]
	public libdb.IChangeableList<DBPtr<RollContainer>> premiumEventContainers { get { return _premiumEventContainers; } set { _premiumEventContainers.Assign( value ); } }

	[Custom("Social")]
	[Description( "Hero endurance loss for session" )]
	public int enduranceGain { get { return _enduranceGain.Get(); } set { _enduranceGain.Set( value ); } }

	[Description( "Endurance coeff (applied if hero is tired or enduranceDisableRollBoost is TRUE)" )]
	public float enduranceCoeff { get { return _enduranceCoeff.Get(); } set { _enduranceCoeff.Set( value ); } }

	public float enduranceFameCoeff { get { return _enduranceFameCoeff.Get(); } set { _enduranceFameCoeff.Set( value ); } }

	public float enduranceExperienceCoeff { get { return _enduranceExperienceCoeff.Get(); } set { _enduranceExperienceCoeff.Set( value ); } }

	public float enduranceResourcesCoeff { get { return _enduranceResourcesCoeff.Get(); } set { _enduranceResourcesCoeff.Set( value ); } }

	[Description( "Коэффициент награжденения игрока - матерого ливера" )]
	public float leaversAwardsCoeff { get { return _leaversAwardsCoeff.Get(); } set { _leaversAwardsCoeff.Set( value ); } }

	[Description( "Reliability increment if player wins a match" )]
	public int reliabilityOnFinishWin { get { return _reliabilityOnFinishWin.Get(); } set { _reliabilityOnFinishWin.Set( value ); } }

	[Description( "Reliability increment if player loses a match" )]
	public int reliabilityOnFinishLose { get { return _reliabilityOnFinishLose.Get(); } set { _reliabilityOnFinishLose.Set( value ); } }

	[Description( "Reliability match period (duration, in seconds)" )]
	public int reliabilityOnFinishPeriod { get { return _reliabilityOnFinishPeriod.Get(); } set { _reliabilityOnFinishPeriod.Set( value ); } }

	[Description( "Reliability increment for period" )]
	public int reliabilityOnFinishPerPeriod { get { return _reliabilityOnFinishPerPeriod.Get(); } set { _reliabilityOnFinishPerPeriod.Set( value ); } }

	[Description( "Reliability increment if player leaves a match" )]
	public int reliabilityOnLeave { get { return _reliabilityOnLeave.Get(); } set { _reliabilityOnLeave.Set( value ); } }

	[Description( "Reliability leave penalty afk period (duration, in seconds)" )]
	public int reliabilityOnLeavePeriod { get { return _reliabilityOnLeavePeriod.Get(); } set { _reliabilityOnLeavePeriod.Set( value ); } }

	[Description( "Reliability leave penalty" )]
	public int reliabilityOnLeavePerPeriod { get { return _reliabilityOnLeavePerPeriod.Get(); } set { _reliabilityOnLeavePerPeriod.Set( value ); } }

	[Description( "Plain score multiplicator" )]
	public int talentsMultiplicator { get { return _talentsMultiplicator.Get(); } set { _talentsMultiplicator.Set( value ); } }

	[Description( "Flag for disabling roll boost (if TRUE and hero is NOT tired enduranceCoeff if NOT applied for overall items set)" )]
	public bool enduranceDisableRollBoost { get { return _enduranceDisableRollBoost.Get(); } set { _enduranceDisableRollBoost.Set( value ); } }

	[Description( "heroLevel/Fame curve" )]
	public libdb.IChangeableList<RollLevelInfo> famePerSession { get { return _famePerSession; } set { _famePerSession.Assign( value ); } }

	[Description( "Fame coeff, applied if player loses a match" )]
	public float fameLoseCoeff { get { return _fameLoseCoeff.Get(); } set { _fameLoseCoeff.Set( value ); } }

	[Description( "Experience coeff, applied if player loses a match" )]
	public float experienceLoseCoeff { get { return _experienceLoseCoeff.Get(); } set { _experienceLoseCoeff.Set( value ); } }

	[Description( "Resources coeff, applied if player loses a match" )]
	public float resourcesLoseCoeff { get { return _resourcesLoseCoeff.Get(); } set { _resourcesLoseCoeff.Set( value ); } }

	[Description( "heroLevel/Experience curve" )]
	public libdb.IChangeableList<RollLevelInfo> experiencePerSession { get { return _experiencePerSession; } set { _experiencePerSession.Assign( value ); } }

	[Description( "Dodge points penalty if player leaves a guard match" )]
	public int dodgePointsOnLeave { get { return _dodgePointsOnLeave.Get(); } set { _dodgePointsOnLeave.Set( value ); } }

	[Description( "Rating change will be multiplied by this parameter" )]
	public float ratingChangeMultiplier { get { return _ratingChangeMultiplier.Get(); } set { _ratingChangeMultiplier.Set( value ); } }

	[Description( "Минимальная длительность сессии (сек). Если меньше, то награждение пропускается. По умолчанию выкл (0)." )]
	public int minSessionDuration { get { return _minSessionDuration.Get(); } set { _minSessionDuration.Set( value ); } }

	[Description( "Roll additional talent (from additional premium containers) for premium awarding" )]
	public int applyPremiumTalent { get { return _applyPremiumTalent.Get(); } set { _applyPremiumTalent.Set( value ); } }

	[Description( "First win of the day rewards" )]
	public DBPtr<RollContainer> FWODRewardContainer { get { return _FWODRewardContainer.Get(); } set { _FWODRewardContainer.Set( value ); } }

	[Custom("Social")]
	[Description( "Mode name" )]
	public string modeName { get { return _modeName.Get(); } set { _modeName.Set( value ); } }

	[Description( "Version for ModeRollSettings. Change for reset users' context" )]
	public int version { get { return _version.Get(); } set { _version.Set( value ); } }

	[Description( "Если игрок ливнул/дисконнектнулся, а его команда выиграла, то ему засчитывается победа." )]
	public bool teamWinDisconnectedWin { get { return _teamWinDisconnectedWin.Get(); } set { _teamWinDisconnectedWin.Set( value ); } }

	[Description( "Clan Wars Economic settings" )]
	public DBPtr<ClanWarsSettings> clanWarsSettings { get { return _clanWarsSettings.Get(); } set { _clanWarsSettings.Set( value ); } }

	[Description( "Минимальный размер партии, начиная с которой начисляется бонус." )]
	public int fullPartySize { get { return _fullPartySize.Get(); } set { _fullPartySize.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ModeRollSettings>(owner);
		_scoresCap = new UndoRedo<int>( owner, 90 );
		_containersOnWin = new UndoRedo<int>( owner, 0 );
		_containersOnFWOD = new UndoRedoDBPtr<RollContainerCountByRank>( owner );
		_containersBySpecialPoints = new UndoRedoDBPtr<ContainersBySpecialPoints>( owner );
		_allowedRollGroups = new UndoRedo<ETalentRollGroup>( owner, ETalentRollGroup.All );
		_containers = new UndoRedoAssignableList<DBPtr<RollContainer>>( owner );
		_premiumContainers = new UndoRedoAssignableList<DBPtr<RollContainer>>( owner );
		_additionalPremiumContainers = new UndoRedoAssignableList<DBPtr<RollContainer>>( owner );
		_defaultContainer = new UndoRedoDBPtr<RollContainer>( owner );
		_eventContainers = new UndoRedoAssignableList<DBPtr<RollContainer>>( owner );
		_premiumEventContainers = new UndoRedoAssignableList<DBPtr<RollContainer>>( owner );
		_enduranceGain = new UndoRedo<int>( owner, 40 );
		_enduranceCoeff = new UndoRedo<float>( owner, 0.33f );
		_enduranceFameCoeff = new UndoRedo<float>( owner, 0.33f );
		_enduranceExperienceCoeff = new UndoRedo<float>( owner, 0.33f );
		_enduranceResourcesCoeff = new UndoRedo<float>( owner, 0.33f );
		_leaversAwardsCoeff = new UndoRedo<float>( owner, 0.3f );
		_reliabilityOnFinishWin = new UndoRedo<int>( owner, 3 );
		_reliabilityOnFinishLose = new UndoRedo<int>( owner, 5 );
		_reliabilityOnFinishPeriod = new UndoRedo<int>( owner, 1800 );
		_reliabilityOnFinishPerPeriod = new UndoRedo<int>( owner, 1 );
		_reliabilityOnLeave = new UndoRedo<int>( owner, -3 );
		_reliabilityOnLeavePeriod = new UndoRedo<int>( owner, 300 );
		_reliabilityOnLeavePerPeriod = new UndoRedo<int>( owner, -1 );
		_talentsMultiplicator = new UndoRedo<int>( owner, 1 );
		_enduranceDisableRollBoost = new UndoRedo<bool>( owner, true );
		_famePerSession = new UndoRedoAssignableList<RollLevelInfo>( owner );
		_fameLoseCoeff = new UndoRedo<float>( owner, 0.33f );
		_experienceLoseCoeff = new UndoRedo<float>( owner, 0.33f );
		_resourcesLoseCoeff = new UndoRedo<float>( owner, 1.0f );
		_experiencePerSession = new UndoRedoAssignableList<RollLevelInfo>( owner );
		_dodgePointsOnLeave = new UndoRedo<int>( owner, 1 );
		_ratingChangeMultiplier = new UndoRedo<float>( owner, 1.0f );
		_minSessionDuration = new UndoRedo<int>( owner, 0 );
		_applyPremiumTalent = new UndoRedo<int>( owner, 0 );
		_FWODRewardContainer = new UndoRedoDBPtr<RollContainer>( owner );
		_modeName = new UndoRedo<string>( owner, string.Empty );
		_version = new UndoRedo<int>( owner, 0 );
		_teamWinDisconnectedWin = new UndoRedo<bool>( owner, false );
		_clanWarsSettings = new UndoRedoDBPtr<ClanWarsSettings>( owner );
		_fullPartySize = new UndoRedo<int>( owner, 4 );
		___parent.Changed += FireChangedEvent;
		_scoresCap.Changed += FireChangedEvent;
		_containersOnWin.Changed += FireChangedEvent;
		_containersOnFWOD.Changed += FireChangedEvent;
		_containersBySpecialPoints.Changed += FireChangedEvent;
		_allowedRollGroups.Changed += FireChangedEvent;
		_containers.Changed += FireChangedEvent;
		_premiumContainers.Changed += FireChangedEvent;
		_additionalPremiumContainers.Changed += FireChangedEvent;
		_defaultContainer.Changed += FireChangedEvent;
		_eventContainers.Changed += FireChangedEvent;
		_premiumEventContainers.Changed += FireChangedEvent;
		_enduranceGain.Changed += FireChangedEvent;
		_enduranceCoeff.Changed += FireChangedEvent;
		_enduranceFameCoeff.Changed += FireChangedEvent;
		_enduranceExperienceCoeff.Changed += FireChangedEvent;
		_enduranceResourcesCoeff.Changed += FireChangedEvent;
		_leaversAwardsCoeff.Changed += FireChangedEvent;
		_reliabilityOnFinishWin.Changed += FireChangedEvent;
		_reliabilityOnFinishLose.Changed += FireChangedEvent;
		_reliabilityOnFinishPeriod.Changed += FireChangedEvent;
		_reliabilityOnFinishPerPeriod.Changed += FireChangedEvent;
		_reliabilityOnLeave.Changed += FireChangedEvent;
		_reliabilityOnLeavePeriod.Changed += FireChangedEvent;
		_reliabilityOnLeavePerPeriod.Changed += FireChangedEvent;
		_talentsMultiplicator.Changed += FireChangedEvent;
		_enduranceDisableRollBoost.Changed += FireChangedEvent;
		_famePerSession.Changed += FireChangedEvent;
		_fameLoseCoeff.Changed += FireChangedEvent;
		_experienceLoseCoeff.Changed += FireChangedEvent;
		_resourcesLoseCoeff.Changed += FireChangedEvent;
		_experiencePerSession.Changed += FireChangedEvent;
		_dodgePointsOnLeave.Changed += FireChangedEvent;
		_ratingChangeMultiplier.Changed += FireChangedEvent;
		_minSessionDuration.Changed += FireChangedEvent;
		_applyPremiumTalent.Changed += FireChangedEvent;
		_FWODRewardContainer.Changed += FireChangedEvent;
		_modeName.Changed += FireChangedEvent;
		_version.Changed += FireChangedEvent;
		_teamWinDisconnectedWin.Changed += FireChangedEvent;
		_clanWarsSettings.Changed += FireChangedEvent;
		_fullPartySize.Changed += FireChangedEvent;
	}

	public ModeRollSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( ModeRollSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ModeRollSettings" );
		scoresCap = source.scoresCap;
		containersOnWin = source.containersOnWin;
		containersOnFWOD = source.containersOnFWOD;
		containersBySpecialPoints = source.containersBySpecialPoints;
		allowedRollGroups = source.allowedRollGroups;
		containers = source.containers;
		premiumContainers = source.premiumContainers;
		additionalPremiumContainers = source.additionalPremiumContainers;
		defaultContainer = source.defaultContainer;
		eventContainers = source.eventContainers;
		premiumEventContainers = source.premiumEventContainers;
		enduranceGain = source.enduranceGain;
		enduranceCoeff = source.enduranceCoeff;
		enduranceFameCoeff = source.enduranceFameCoeff;
		enduranceExperienceCoeff = source.enduranceExperienceCoeff;
		enduranceResourcesCoeff = source.enduranceResourcesCoeff;
		leaversAwardsCoeff = source.leaversAwardsCoeff;
		reliabilityOnFinishWin = source.reliabilityOnFinishWin;
		reliabilityOnFinishLose = source.reliabilityOnFinishLose;
		reliabilityOnFinishPeriod = source.reliabilityOnFinishPeriod;
		reliabilityOnFinishPerPeriod = source.reliabilityOnFinishPerPeriod;
		reliabilityOnLeave = source.reliabilityOnLeave;
		reliabilityOnLeavePeriod = source.reliabilityOnLeavePeriod;
		reliabilityOnLeavePerPeriod = source.reliabilityOnLeavePerPeriod;
		talentsMultiplicator = source.talentsMultiplicator;
		enduranceDisableRollBoost = source.enduranceDisableRollBoost;
		famePerSession = source.famePerSession;
		fameLoseCoeff = source.fameLoseCoeff;
		experienceLoseCoeff = source.experienceLoseCoeff;
		resourcesLoseCoeff = source.resourcesLoseCoeff;
		experiencePerSession = source.experiencePerSession;
		dodgePointsOnLeave = source.dodgePointsOnLeave;
		ratingChangeMultiplier = source.ratingChangeMultiplier;
		minSessionDuration = source.minSessionDuration;
		applyPremiumTalent = source.applyPremiumTalent;
		FWODRewardContainer = source.FWODRewardContainer;
		modeName = source.modeName;
		version = source.version;
		teamWinDisconnectedWin = source.teamWinDisconnectedWin;
		clanWarsSettings = source.clanWarsSettings;
		fullPartySize = source.fullPartySize;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ModeRollSettings source = _source as ModeRollSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ModeRollSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ModeRollSettings newParent = rawParent == null ? null : rawParent.Get<ModeRollSettings>();
		if ( newParent == null && _newParent is ModeRollSettings )
			newParent = _newParent as ModeRollSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_scoresCap.SetParent( newParent == null ? null : newParent._scoresCap );
		_containersOnWin.SetParent( newParent == null ? null : newParent._containersOnWin );
		_containersOnFWOD.SetParent( newParent == null ? null : newParent._containersOnFWOD );
		_containersBySpecialPoints.SetParent( newParent == null ? null : newParent._containersBySpecialPoints );
		_allowedRollGroups.SetParent( newParent == null ? null : newParent._allowedRollGroups );
		_containers.SetParent( newParent == null ? null : newParent._containers );
		_premiumContainers.SetParent( newParent == null ? null : newParent._premiumContainers );
		_additionalPremiumContainers.SetParent( newParent == null ? null : newParent._additionalPremiumContainers );
		_defaultContainer.SetParent( newParent == null ? null : newParent._defaultContainer );
		_eventContainers.SetParent( newParent == null ? null : newParent._eventContainers );
		_premiumEventContainers.SetParent( newParent == null ? null : newParent._premiumEventContainers );
		_enduranceGain.SetParent( newParent == null ? null : newParent._enduranceGain );
		_enduranceCoeff.SetParent( newParent == null ? null : newParent._enduranceCoeff );
		_enduranceFameCoeff.SetParent( newParent == null ? null : newParent._enduranceFameCoeff );
		_enduranceExperienceCoeff.SetParent( newParent == null ? null : newParent._enduranceExperienceCoeff );
		_enduranceResourcesCoeff.SetParent( newParent == null ? null : newParent._enduranceResourcesCoeff );
		_leaversAwardsCoeff.SetParent( newParent == null ? null : newParent._leaversAwardsCoeff );
		_reliabilityOnFinishWin.SetParent( newParent == null ? null : newParent._reliabilityOnFinishWin );
		_reliabilityOnFinishLose.SetParent( newParent == null ? null : newParent._reliabilityOnFinishLose );
		_reliabilityOnFinishPeriod.SetParent( newParent == null ? null : newParent._reliabilityOnFinishPeriod );
		_reliabilityOnFinishPerPeriod.SetParent( newParent == null ? null : newParent._reliabilityOnFinishPerPeriod );
		_reliabilityOnLeave.SetParent( newParent == null ? null : newParent._reliabilityOnLeave );
		_reliabilityOnLeavePeriod.SetParent( newParent == null ? null : newParent._reliabilityOnLeavePeriod );
		_reliabilityOnLeavePerPeriod.SetParent( newParent == null ? null : newParent._reliabilityOnLeavePerPeriod );
		_talentsMultiplicator.SetParent( newParent == null ? null : newParent._talentsMultiplicator );
		_enduranceDisableRollBoost.SetParent( newParent == null ? null : newParent._enduranceDisableRollBoost );
		_famePerSession.SetParent( newParent == null ? null : newParent._famePerSession );
		_fameLoseCoeff.SetParent( newParent == null ? null : newParent._fameLoseCoeff );
		_experienceLoseCoeff.SetParent( newParent == null ? null : newParent._experienceLoseCoeff );
		_resourcesLoseCoeff.SetParent( newParent == null ? null : newParent._resourcesLoseCoeff );
		_experiencePerSession.SetParent( newParent == null ? null : newParent._experiencePerSession );
		_dodgePointsOnLeave.SetParent( newParent == null ? null : newParent._dodgePointsOnLeave );
		_ratingChangeMultiplier.SetParent( newParent == null ? null : newParent._ratingChangeMultiplier );
		_minSessionDuration.SetParent( newParent == null ? null : newParent._minSessionDuration );
		_applyPremiumTalent.SetParent( newParent == null ? null : newParent._applyPremiumTalent );
		_FWODRewardContainer.SetParent( newParent == null ? null : newParent._FWODRewardContainer );
		_modeName.SetParent( newParent == null ? null : newParent._modeName );
		_version.SetParent( newParent == null ? null : newParent._version );
		_teamWinDisconnectedWin.SetParent( newParent == null ? null : newParent._teamWinDisconnectedWin );
		_clanWarsSettings.SetParent( newParent == null ? null : newParent._clanWarsSettings );
		_fullPartySize.SetParent( newParent == null ? null : newParent._fullPartySize );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_scoresCap.Reset();
		_containersOnWin.Reset();
		_containersOnFWOD.Reset();
		_containersBySpecialPoints.Reset();
		_allowedRollGroups.Reset();
		_containers.Reset();
		_premiumContainers.Reset();
		_additionalPremiumContainers.Reset();
		_defaultContainer.Reset();
		_eventContainers.Reset();
		_premiumEventContainers.Reset();
		_enduranceGain.Reset();
		_enduranceCoeff.Reset();
		_enduranceFameCoeff.Reset();
		_enduranceExperienceCoeff.Reset();
		_enduranceResourcesCoeff.Reset();
		_leaversAwardsCoeff.Reset();
		_reliabilityOnFinishWin.Reset();
		_reliabilityOnFinishLose.Reset();
		_reliabilityOnFinishPeriod.Reset();
		_reliabilityOnFinishPerPeriod.Reset();
		_reliabilityOnLeave.Reset();
		_reliabilityOnLeavePeriod.Reset();
		_reliabilityOnLeavePerPeriod.Reset();
		_talentsMultiplicator.Reset();
		_enduranceDisableRollBoost.Reset();
		_famePerSession.Reset();
		_fameLoseCoeff.Reset();
		_experienceLoseCoeff.Reset();
		_resourcesLoseCoeff.Reset();
		_experiencePerSession.Reset();
		_dodgePointsOnLeave.Reset();
		_ratingChangeMultiplier.Reset();
		_minSessionDuration.Reset();
		_applyPremiumTalent.Reset();
		_FWODRewardContainer.Reset();
		_modeName.Reset();
		_version.Reset();
		_teamWinDisconnectedWin.Reset();
		_clanWarsSettings.Reset();
		_fullPartySize.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_scoresCap.IsDerivedFromParent()
			&& _containersOnWin.IsDerivedFromParent()
			&& _containersOnFWOD.IsDerivedFromParent()
			&& _containersBySpecialPoints.IsDerivedFromParent()
			&& _allowedRollGroups.IsDerivedFromParent()
			&& _containers.IsDerivedFromParent()
			&& _premiumContainers.IsDerivedFromParent()
			&& _additionalPremiumContainers.IsDerivedFromParent()
			&& _defaultContainer.IsDerivedFromParent()
			&& _eventContainers.IsDerivedFromParent()
			&& _premiumEventContainers.IsDerivedFromParent()
			&& _enduranceGain.IsDerivedFromParent()
			&& _enduranceCoeff.IsDerivedFromParent()
			&& _enduranceFameCoeff.IsDerivedFromParent()
			&& _enduranceExperienceCoeff.IsDerivedFromParent()
			&& _enduranceResourcesCoeff.IsDerivedFromParent()
			&& _leaversAwardsCoeff.IsDerivedFromParent()
			&& _reliabilityOnFinishWin.IsDerivedFromParent()
			&& _reliabilityOnFinishLose.IsDerivedFromParent()
			&& _reliabilityOnFinishPeriod.IsDerivedFromParent()
			&& _reliabilityOnFinishPerPeriod.IsDerivedFromParent()
			&& _reliabilityOnLeave.IsDerivedFromParent()
			&& _reliabilityOnLeavePeriod.IsDerivedFromParent()
			&& _reliabilityOnLeavePerPeriod.IsDerivedFromParent()
			&& _talentsMultiplicator.IsDerivedFromParent()
			&& _enduranceDisableRollBoost.IsDerivedFromParent()
			&& _famePerSession.IsDerivedFromParent()
			&& _fameLoseCoeff.IsDerivedFromParent()
			&& _experienceLoseCoeff.IsDerivedFromParent()
			&& _resourcesLoseCoeff.IsDerivedFromParent()
			&& _experiencePerSession.IsDerivedFromParent()
			&& _dodgePointsOnLeave.IsDerivedFromParent()
			&& _ratingChangeMultiplier.IsDerivedFromParent()
			&& _minSessionDuration.IsDerivedFromParent()
			&& _applyPremiumTalent.IsDerivedFromParent()
			&& _FWODRewardContainer.IsDerivedFromParent()
			&& _modeName.IsDerivedFromParent()
			&& _version.IsDerivedFromParent()
			&& _teamWinDisconnectedWin.IsDerivedFromParent()
			&& _clanWarsSettings.IsDerivedFromParent()
			&& _fullPartySize.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "scoresCap" )
			_scoresCap.Reset();
		else if ( fieldName == "containersOnWin" )
			_containersOnWin.Reset();
		else if ( fieldName == "containersOnFWOD" )
			_containersOnFWOD.Reset();
		else if ( fieldName == "containersBySpecialPoints" )
			_containersBySpecialPoints.Reset();
		else if ( fieldName == "allowedRollGroups" )
			_allowedRollGroups.Reset();
		else if ( fieldName == "containers" )
			_containers.Reset();
		else if ( fieldName == "premiumContainers" )
			_premiumContainers.Reset();
		else if ( fieldName == "additionalPremiumContainers" )
			_additionalPremiumContainers.Reset();
		else if ( fieldName == "defaultContainer" )
			_defaultContainer.Reset();
		else if ( fieldName == "eventContainers" )
			_eventContainers.Reset();
		else if ( fieldName == "premiumEventContainers" )
			_premiumEventContainers.Reset();
		else if ( fieldName == "enduranceGain" )
			_enduranceGain.Reset();
		else if ( fieldName == "enduranceCoeff" )
			_enduranceCoeff.Reset();
		else if ( fieldName == "enduranceFameCoeff" )
			_enduranceFameCoeff.Reset();
		else if ( fieldName == "enduranceExperienceCoeff" )
			_enduranceExperienceCoeff.Reset();
		else if ( fieldName == "enduranceResourcesCoeff" )
			_enduranceResourcesCoeff.Reset();
		else if ( fieldName == "leaversAwardsCoeff" )
			_leaversAwardsCoeff.Reset();
		else if ( fieldName == "reliabilityOnFinishWin" )
			_reliabilityOnFinishWin.Reset();
		else if ( fieldName == "reliabilityOnFinishLose" )
			_reliabilityOnFinishLose.Reset();
		else if ( fieldName == "reliabilityOnFinishPeriod" )
			_reliabilityOnFinishPeriod.Reset();
		else if ( fieldName == "reliabilityOnFinishPerPeriod" )
			_reliabilityOnFinishPerPeriod.Reset();
		else if ( fieldName == "reliabilityOnLeave" )
			_reliabilityOnLeave.Reset();
		else if ( fieldName == "reliabilityOnLeavePeriod" )
			_reliabilityOnLeavePeriod.Reset();
		else if ( fieldName == "reliabilityOnLeavePerPeriod" )
			_reliabilityOnLeavePerPeriod.Reset();
		else if ( fieldName == "talentsMultiplicator" )
			_talentsMultiplicator.Reset();
		else if ( fieldName == "enduranceDisableRollBoost" )
			_enduranceDisableRollBoost.Reset();
		else if ( fieldName == "famePerSession" )
			_famePerSession.Reset();
		else if ( fieldName == "fameLoseCoeff" )
			_fameLoseCoeff.Reset();
		else if ( fieldName == "experienceLoseCoeff" )
			_experienceLoseCoeff.Reset();
		else if ( fieldName == "resourcesLoseCoeff" )
			_resourcesLoseCoeff.Reset();
		else if ( fieldName == "experiencePerSession" )
			_experiencePerSession.Reset();
		else if ( fieldName == "dodgePointsOnLeave" )
			_dodgePointsOnLeave.Reset();
		else if ( fieldName == "ratingChangeMultiplier" )
			_ratingChangeMultiplier.Reset();
		else if ( fieldName == "minSessionDuration" )
			_minSessionDuration.Reset();
		else if ( fieldName == "applyPremiumTalent" )
			_applyPremiumTalent.Reset();
		else if ( fieldName == "FWODRewardContainer" )
			_FWODRewardContainer.Reset();
		else if ( fieldName == "modeName" )
			_modeName.Reset();
		else if ( fieldName == "version" )
			_version.Reset();
		else if ( fieldName == "teamWinDisconnectedWin" )
			_teamWinDisconnectedWin.Reset();
		else if ( fieldName == "clanWarsSettings" )
			_clanWarsSettings.Reset();
		else if ( fieldName == "fullPartySize" )
			_fullPartySize.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "scoresCap" )
			return _scoresCap.IsDerivedFromParent();
		if ( fieldName == "containersOnWin" )
			return _containersOnWin.IsDerivedFromParent();
		if ( fieldName == "containersOnFWOD" )
			return _containersOnFWOD.IsDerivedFromParent();
		if ( fieldName == "containersBySpecialPoints" )
			return _containersBySpecialPoints.IsDerivedFromParent();
		if ( fieldName == "allowedRollGroups" )
			return _allowedRollGroups.IsDerivedFromParent();
		if ( fieldName == "containers" )
			return _containers.IsDerivedFromParent();
		if ( fieldName == "premiumContainers" )
			return _premiumContainers.IsDerivedFromParent();
		if ( fieldName == "additionalPremiumContainers" )
			return _additionalPremiumContainers.IsDerivedFromParent();
		if ( fieldName == "defaultContainer" )
			return _defaultContainer.IsDerivedFromParent();
		if ( fieldName == "eventContainers" )
			return _eventContainers.IsDerivedFromParent();
		if ( fieldName == "premiumEventContainers" )
			return _premiumEventContainers.IsDerivedFromParent();
		if ( fieldName == "enduranceGain" )
			return _enduranceGain.IsDerivedFromParent();
		if ( fieldName == "enduranceCoeff" )
			return _enduranceCoeff.IsDerivedFromParent();
		if ( fieldName == "enduranceFameCoeff" )
			return _enduranceFameCoeff.IsDerivedFromParent();
		if ( fieldName == "enduranceExperienceCoeff" )
			return _enduranceExperienceCoeff.IsDerivedFromParent();
		if ( fieldName == "enduranceResourcesCoeff" )
			return _enduranceResourcesCoeff.IsDerivedFromParent();
		if ( fieldName == "leaversAwardsCoeff" )
			return _leaversAwardsCoeff.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnFinishWin" )
			return _reliabilityOnFinishWin.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnFinishLose" )
			return _reliabilityOnFinishLose.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnFinishPeriod" )
			return _reliabilityOnFinishPeriod.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnFinishPerPeriod" )
			return _reliabilityOnFinishPerPeriod.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnLeave" )
			return _reliabilityOnLeave.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnLeavePeriod" )
			return _reliabilityOnLeavePeriod.IsDerivedFromParent();
		if ( fieldName == "reliabilityOnLeavePerPeriod" )
			return _reliabilityOnLeavePerPeriod.IsDerivedFromParent();
		if ( fieldName == "talentsMultiplicator" )
			return _talentsMultiplicator.IsDerivedFromParent();
		if ( fieldName == "enduranceDisableRollBoost" )
			return _enduranceDisableRollBoost.IsDerivedFromParent();
		if ( fieldName == "famePerSession" )
			return _famePerSession.IsDerivedFromParent();
		if ( fieldName == "fameLoseCoeff" )
			return _fameLoseCoeff.IsDerivedFromParent();
		if ( fieldName == "experienceLoseCoeff" )
			return _experienceLoseCoeff.IsDerivedFromParent();
		if ( fieldName == "resourcesLoseCoeff" )
			return _resourcesLoseCoeff.IsDerivedFromParent();
		if ( fieldName == "experiencePerSession" )
			return _experiencePerSession.IsDerivedFromParent();
		if ( fieldName == "dodgePointsOnLeave" )
			return _dodgePointsOnLeave.IsDerivedFromParent();
		if ( fieldName == "ratingChangeMultiplier" )
			return _ratingChangeMultiplier.IsDerivedFromParent();
		if ( fieldName == "minSessionDuration" )
			return _minSessionDuration.IsDerivedFromParent();
		if ( fieldName == "applyPremiumTalent" )
			return _applyPremiumTalent.IsDerivedFromParent();
		if ( fieldName == "FWODRewardContainer" )
			return _FWODRewardContainer.IsDerivedFromParent();
		if ( fieldName == "modeName" )
			return _modeName.IsDerivedFromParent();
		if ( fieldName == "version" )
			return _version.IsDerivedFromParent();
		if ( fieldName == "teamWinDisconnectedWin" )
			return _teamWinDisconnectedWin.IsDerivedFromParent();
		if ( fieldName == "clanWarsSettings" )
			return _clanWarsSettings.IsDerivedFromParent();
		if ( fieldName == "fullPartySize" )
			return _fullPartySize.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class NothingRollItem : RollItem
{
	private UndoRedoDBPtr<NothingRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<NothingRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _dummy;

	public int dummy { get { return _dummy.Get(); } set { _dummy.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NothingRollItem>(owner);
		_dummy = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_dummy.Changed += FireChangedEvent;
	}

	public NothingRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( NothingRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NothingRollItem" );
		dummy = source.dummy;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NothingRollItem source = _source as NothingRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NothingRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NothingRollItem newParent = rawParent == null ? null : rawParent.Get<NothingRollItem>();
		if ( newParent == null && _newParent is NothingRollItem )
			newParent = _newParent as NothingRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_dummy.SetParent( newParent == null ? null : newParent._dummy );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_dummy.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_dummy.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "dummy" )
			_dummy.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "dummy" )
			return _dummy.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class PremiumAccRollItem : RollItem
{
	private UndoRedoDBPtr<PremiumAccRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<PremiumAccRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _days;

	[Description( "Сколько дней золотого века выдать в лутбоксе" )]
	public int days { get { return _days.Get(); } set { _days.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PremiumAccRollItem>(owner);
		_days = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_days.Changed += FireChangedEvent;
	}

	public PremiumAccRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( PremiumAccRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PremiumAccRollItem" );
		days = source.days;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PremiumAccRollItem source = _source as PremiumAccRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PremiumAccRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PremiumAccRollItem newParent = rawParent == null ? null : rawParent.Get<PremiumAccRollItem>();
		if ( newParent == null && _newParent is PremiumAccRollItem )
			newParent = _newParent as PremiumAccRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_days.SetParent( newParent == null ? null : newParent._days );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_days.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_days.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "days" )
			_days.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "days" )
			return _days.IsDerivedFromParent();
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
[UseTypeName("GUILDBONUS")]
public class RandomTalentBonus : GuildBonus
{
	private UndoRedoDBPtr<RandomTalentBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<RandomTalentBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SingleRollSettings _singleRollSettings;

	[Description( "Настройки для одиночного ролла" )]
	public SingleRollSettings singleRollSettings { get { return _singleRollSettings; } set { _singleRollSettings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RandomTalentBonus>(owner);
		_singleRollSettings = new SingleRollSettings( owner );
		___parent.Changed += FireChangedEvent;
		_singleRollSettings.Changed += FireChangedEvent;
	}

	public RandomTalentBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( RandomTalentBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RandomTalentBonus" );
		singleRollSettings = source.singleRollSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RandomTalentBonus source = _source as RandomTalentBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RandomTalentBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RandomTalentBonus newParent = rawParent == null ? null : rawParent.Get<RandomTalentBonus>();
		if ( newParent == null && _newParent is RandomTalentBonus )
			newParent = _newParent as RandomTalentBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_singleRollSettings.SetParent( newParent == null ? null : newParent._singleRollSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_singleRollSettings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_singleRollSettings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "singleRollSettings" )
			_singleRollSettings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "singleRollSettings" )
			return _singleRollSettings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("ROLLITEM")]
public class RarityTalentListRollItem : RollItem
{
	private UndoRedoDBPtr<RarityTalentListRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<RarityTalentListRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETalentRarity> _rarity;

	public ETalentRarity rarity { get { return _rarity.Get(); } set { _rarity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RarityTalentListRollItem>(owner);
		_rarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.Class );
		___parent.Changed += FireChangedEvent;
		_rarity.Changed += FireChangedEvent;
	}

	public RarityTalentListRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( RarityTalentListRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RarityTalentListRollItem" );
		rarity = source.rarity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RarityTalentListRollItem source = _source as RarityTalentListRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RarityTalentListRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RarityTalentListRollItem newParent = rawParent == null ? null : rawParent.Get<RarityTalentListRollItem>();
		if ( newParent == null && _newParent is RarityTalentListRollItem )
			newParent = _newParent as RarityTalentListRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_rarity.SetParent( newParent == null ? null : newParent._rarity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_rarity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_rarity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "rarity" )
			_rarity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "rarity" )
			return _rarity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("ROLLITEM")]
public class ResourceRollItem : RollItem
{
	private UndoRedoDBPtr<ResourceRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<ResourceRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ResourceRollConstraint> _type;
	private UndoRedo<string> _customCurrencyId;
	private UndoRedoAssignableList<RollLevelInfo> _itemsFromLord;
	private UndoRedoAssignableList<RollLevelInfo> _itemsFromHero;
	private UndoRedoAssignableList<RollLevelInfo> _itemsFromRank;

	public ResourceRollConstraint type { get { return _type.Get(); } set { _type.Set( value ); } }

	public string customCurrencyId { get { return _customCurrencyId.Get(); } set { _customCurrencyId.Set( value ); } }

	public libdb.IChangeableList<RollLevelInfo> itemsFromLord { get { return _itemsFromLord; } set { _itemsFromLord.Assign( value ); } }

	public libdb.IChangeableList<RollLevelInfo> itemsFromHero { get { return _itemsFromHero; } set { _itemsFromHero.Assign( value ); } }

	public libdb.IChangeableList<RollLevelInfo> itemsFromRank { get { return _itemsFromRank; } set { _itemsFromRank.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ResourceRollItem>(owner);
		_type = new UndoRedo<ResourceRollConstraint>( owner, ResourceRollConstraint.Silver );
		_customCurrencyId = new UndoRedo<string>( owner, string.Empty );
		_itemsFromLord = new UndoRedoAssignableList<RollLevelInfo>( owner );
		_itemsFromHero = new UndoRedoAssignableList<RollLevelInfo>( owner );
		_itemsFromRank = new UndoRedoAssignableList<RollLevelInfo>( owner );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_customCurrencyId.Changed += FireChangedEvent;
		_itemsFromLord.Changed += FireChangedEvent;
		_itemsFromHero.Changed += FireChangedEvent;
		_itemsFromRank.Changed += FireChangedEvent;
	}

	public ResourceRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( ResourceRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ResourceRollItem" );
		type = source.type;
		customCurrencyId = source.customCurrencyId;
		itemsFromLord = source.itemsFromLord;
		itemsFromHero = source.itemsFromHero;
		itemsFromRank = source.itemsFromRank;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ResourceRollItem source = _source as ResourceRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ResourceRollItem newParent = rawParent == null ? null : rawParent.Get<ResourceRollItem>();
		if ( newParent == null && _newParent is ResourceRollItem )
			newParent = _newParent as ResourceRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		_customCurrencyId.SetParent( newParent == null ? null : newParent._customCurrencyId );
		_itemsFromLord.SetParent( newParent == null ? null : newParent._itemsFromLord );
		_itemsFromHero.SetParent( newParent == null ? null : newParent._itemsFromHero );
		_itemsFromRank.SetParent( newParent == null ? null : newParent._itemsFromRank );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		_customCurrencyId.Reset();
		_itemsFromLord.Reset();
		_itemsFromHero.Reset();
		_itemsFromRank.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _customCurrencyId.IsDerivedFromParent()
			&& _itemsFromLord.IsDerivedFromParent()
			&& _itemsFromHero.IsDerivedFromParent()
			&& _itemsFromRank.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "customCurrencyId" )
			_customCurrencyId.Reset();
		else if ( fieldName == "itemsFromLord" )
			_itemsFromLord.Reset();
		else if ( fieldName == "itemsFromHero" )
			_itemsFromHero.Reset();
		else if ( fieldName == "itemsFromRank" )
			_itemsFromRank.Reset();
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
		if ( fieldName == "customCurrencyId" )
			return _customCurrencyId.IsDerivedFromParent();
		if ( fieldName == "itemsFromLord" )
			return _itemsFromLord.IsDerivedFromParent();
		if ( fieldName == "itemsFromHero" )
			return _itemsFromHero.IsDerivedFromParent();
		if ( fieldName == "itemsFromRank" )
			return _itemsFromRank.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("ROLLCONT")]
public class RollContainer : RollItem
{
	private UndoRedoDBPtr<RollContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<RollContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<RollContainerCostByRank> _costByRank;
	private UndoRedo<string> _name;
	private UndoRedoAssignableList<RollItemProbability> _items;
	private UndoRedo<int> _multiplicator;

	[Description( "Стоимость контейнера в зависимости от звания (по умолчанию берётся из defaultRollContainerCostByRank общих настроек ролла)" )]
	public DBPtr<RollContainerCostByRank> costByRank { get { return _costByRank.Get(); } set { _costByRank.Set( value ); } }

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public libdb.IChangeableList<RollItemProbability> items { get { return _items; } set { _items.Assign( value ); } }

	public int multiplicator { get { return _multiplicator.Get(); } set { _multiplicator.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RollContainer>(owner);
		_costByRank = new UndoRedoDBPtr<RollContainerCostByRank>( owner );
		_name = new UndoRedo<string>( owner, string.Empty );
		_items = new UndoRedoAssignableList<RollItemProbability>( owner );
		_multiplicator = new UndoRedo<int>( owner, 1 );
		___parent.Changed += FireChangedEvent;
		_costByRank.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
		_multiplicator.Changed += FireChangedEvent;
	}

	public RollContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( RollContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RollContainer" );
		costByRank = source.costByRank;
		name = source.name;
		items = source.items;
		multiplicator = source.multiplicator;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RollContainer source = _source as RollContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RollContainer newParent = rawParent == null ? null : rawParent.Get<RollContainer>();
		if ( newParent == null && _newParent is RollContainer )
			newParent = _newParent as RollContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_costByRank.SetParent( newParent == null ? null : newParent._costByRank );
		_name.SetParent( newParent == null ? null : newParent._name );
		_items.SetParent( newParent == null ? null : newParent._items );
		_multiplicator.SetParent( newParent == null ? null : newParent._multiplicator );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_costByRank.Reset();
		_name.Reset();
		_items.Reset();
		_multiplicator.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_costByRank.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _items.IsDerivedFromParent()
			&& _multiplicator.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "costByRank" )
			_costByRank.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "items" )
			_items.Reset();
		else if ( fieldName == "multiplicator" )
			_multiplicator.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "costByRank" )
			return _costByRank.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "items" )
			return _items.IsDerivedFromParent();
		if ( fieldName == "multiplicator" )
			return _multiplicator.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[UseTypeName("RCCS")]
public class RollContainerCostByRank : DBResource
{
	private UndoRedoDBPtr<RollContainerCostByRank> ___parent;
	[HideInOutliner]
	public new DBPtr<RollContainerCostByRank> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<float> _costs;

	public libdb.IChangeableList<float> costs { get { return _costs; } set { _costs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RollContainerCostByRank>(owner);
		_costs = new UndoRedoList<float>( owner );
		___parent.Changed += FireChangedEvent;
		_costs.Changed += FireChangedEvent;
	}

	public RollContainerCostByRank()
	{
		Initialize( this );
	}
	private void AssignSelf( RollContainerCostByRank source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RollContainerCostByRank" );
		costs = source.costs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RollContainerCostByRank source = _source as RollContainerCostByRank;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollContainerCostByRank" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RollContainerCostByRank newParent = rawParent == null ? null : rawParent.Get<RollContainerCostByRank>();
		if ( newParent == null && _newParent is RollContainerCostByRank )
			newParent = _newParent as RollContainerCostByRank;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_costs.SetParent( newParent == null ? null : newParent._costs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_costs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_costs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "costs" )
			_costs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "costs" )
			return _costs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[UseTypeName("RCCT")]
public class RollContainerCountByRank : DBResource
{
	private UndoRedoDBPtr<RollContainerCountByRank> ___parent;
	[HideInOutliner]
	public new DBPtr<RollContainerCountByRank> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _counts;

	public libdb.IChangeableList<int> counts { get { return _counts; } set { _counts.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RollContainerCountByRank>(owner);
		_counts = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		_counts.Changed += FireChangedEvent;
	}

	public RollContainerCountByRank()
	{
		Initialize( this );
	}
	private void AssignSelf( RollContainerCountByRank source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RollContainerCountByRank" );
		counts = source.counts;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RollContainerCountByRank source = _source as RollContainerCountByRank;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollContainerCountByRank" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RollContainerCountByRank newParent = rawParent == null ? null : rawParent.Get<RollContainerCountByRank>();
		if ( newParent == null && _newParent is RollContainerCountByRank )
			newParent = _newParent as RollContainerCountByRank;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_counts.SetParent( newParent == null ? null : newParent._counts );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_counts.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_counts.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "counts" )
			_counts.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "counts" )
			return _counts.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("CWROLLITEM")]
public class ClanWarsRollItem : RollItem
{
	private UndoRedoDBPtr<ClanWarsRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<ClanWarsRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ClanWarsRollItemType> _type;
	private UndoRedo<float> _count;

	public ClanWarsRollItemType type { get { return _type.Get(); } set { _type.Set( value ); } }

	public float count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ClanWarsRollItem>(owner);
		_type = new UndoRedo<ClanWarsRollItemType>( owner, ClanWarsRollItemType.ClanRating );
		_count = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
	}

	public ClanWarsRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( ClanWarsRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ClanWarsRollItem" );
		type = source.type;
		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ClanWarsRollItem source = _source as ClanWarsRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClanWarsRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ClanWarsRollItem newParent = rawParent == null ? null : rawParent.Get<ClanWarsRollItem>();
		if ( newParent == null && _newParent is ClanWarsRollItem )
			newParent = _newParent as ClanWarsRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		_count.SetParent( newParent == null ? null : newParent._count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		_count.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _count.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "count" )
			_count.Reset();
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
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("ROLL")]
public class RollSettings : DBResource
{
	private UndoRedoDBPtr<RollSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<RollSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<ModeRollSettings> _pvp;
	private UndoRedoDBPtr<RollContainerCostByRank> _defaultRollContainerCostByRank;
	private UndoRedoDBPtr<ModeRollSettings> _trainingFWODSettings;
	private UndoRedoAssignableList<RatingModifier> _ratingModifiers;
	private UndoRedoAssignableList<FullPartyRatingModifier> _fullPartyRatingModifiers;
	private SingleRollSettings _forgeRollSettings;
	private UndoRedoDBPtr<GuildLevels> _guildLevels;
	private UndoRedo<int> _requiredLevelForExclusiveTalents;
	private UndoRedo<int> _requiredRatingForExclusiveTalents;
	private UndoRedoDBPtr<ClanWarsSettings> _clanWarsSettings;

	[Description( "Used in social part only!" )]
	public DBPtr<ModeRollSettings> pvp { get { return _pvp.Get(); } set { _pvp.Set( value ); } }

	[Description( "Стоимость ролл-контейнера от звания героя по умолчанию" )]
	public DBPtr<RollContainerCostByRank> defaultRollContainerCostByRank { get { return _defaultRollContainerCostByRank.Get(); } set { _defaultRollContainerCostByRank.Set( value ); } }

	[Description( "Настройки для ролла для первой победы за день в тренировке" )]
	public DBPtr<ModeRollSettings> trainingFWODSettings { get { return _trainingFWODSettings.Get(); } set { _trainingFWODSettings.Set( value ); } }

	[Description( "Модификаторы рейтинговой награды от рейтинга героя" )]
	public libdb.IChangeableList<RatingModifier> ratingModifiers { get { return _ratingModifiers; } set { _ratingModifiers.Assign( value ); } }

	[Description( "Бонусный рейтинг для фуллки от рейтинга героя" )]
	public libdb.IChangeableList<FullPartyRatingModifier> fullPartyRatingModifiers { get { return _fullPartyRatingModifiers; } set { _fullPartyRatingModifiers.Assign( value ); } }

	[Description( "Контейнер для ролла кузницы (!сейчас отключено, настраивать надо в Social.ROOT!)" )]
	public SingleRollSettings forgeRollSettings { get { return _forgeRollSettings; } set { _forgeRollSettings.Assign( value ); } }

	[Description( "Ссылка на гильдийские уровни" )]
	public DBPtr<GuildLevels> guildLevels { get { return _guildLevels.Get(); } set { _guildLevels.Set( value ); } }

	[Description( "Minimum hero's level, required for exclusive (orange) talents roll" )]
	public int requiredLevelForExclusiveTalents { get { return _requiredLevelForExclusiveTalents.Get(); } set { _requiredLevelForExclusiveTalents.Set( value ); } }

	[Description( "Minimum hero's rating, required for exclusive (orange) talents roll" )]
	public int requiredRatingForExclusiveTalents { get { return _requiredRatingForExclusiveTalents.Get(); } set { _requiredRatingForExclusiveTalents.Set( value ); } }

	[Description( "Clan Wars Economic settings" )]
	public DBPtr<ClanWarsSettings> clanWarsSettings { get { return _clanWarsSettings.Get(); } set { _clanWarsSettings.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RollSettings>(owner);
		_pvp = new UndoRedoDBPtr<ModeRollSettings>( owner );
		_defaultRollContainerCostByRank = new UndoRedoDBPtr<RollContainerCostByRank>( owner );
		_trainingFWODSettings = new UndoRedoDBPtr<ModeRollSettings>( owner );
		_ratingModifiers = new UndoRedoAssignableList<RatingModifier>( owner );
		_fullPartyRatingModifiers = new UndoRedoAssignableList<FullPartyRatingModifier>( owner );
		_forgeRollSettings = new SingleRollSettings( owner );
		_guildLevels = new UndoRedoDBPtr<GuildLevels>( owner );
		_requiredLevelForExclusiveTalents = new UndoRedo<int>( owner, 21 );
		_requiredRatingForExclusiveTalents = new UndoRedo<int>( owner, 1600 );
		_clanWarsSettings = new UndoRedoDBPtr<ClanWarsSettings>( owner );
		___parent.Changed += FireChangedEvent;
		_pvp.Changed += FireChangedEvent;
		_defaultRollContainerCostByRank.Changed += FireChangedEvent;
		_trainingFWODSettings.Changed += FireChangedEvent;
		_ratingModifiers.Changed += FireChangedEvent;
		_fullPartyRatingModifiers.Changed += FireChangedEvent;
		_forgeRollSettings.Changed += FireChangedEvent;
		_guildLevels.Changed += FireChangedEvent;
		_requiredLevelForExclusiveTalents.Changed += FireChangedEvent;
		_requiredRatingForExclusiveTalents.Changed += FireChangedEvent;
		_clanWarsSettings.Changed += FireChangedEvent;
	}

	public RollSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( RollSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RollSettings" );
		pvp = source.pvp;
		defaultRollContainerCostByRank = source.defaultRollContainerCostByRank;
		trainingFWODSettings = source.trainingFWODSettings;
		ratingModifiers = source.ratingModifiers;
		fullPartyRatingModifiers = source.fullPartyRatingModifiers;
		forgeRollSettings = source.forgeRollSettings;
		guildLevels = source.guildLevels;
		requiredLevelForExclusiveTalents = source.requiredLevelForExclusiveTalents;
		requiredRatingForExclusiveTalents = source.requiredRatingForExclusiveTalents;
		clanWarsSettings = source.clanWarsSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RollSettings source = _source as RollSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RollSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RollSettings newParent = rawParent == null ? null : rawParent.Get<RollSettings>();
		if ( newParent == null && _newParent is RollSettings )
			newParent = _newParent as RollSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_pvp.SetParent( newParent == null ? null : newParent._pvp );
		_defaultRollContainerCostByRank.SetParent( newParent == null ? null : newParent._defaultRollContainerCostByRank );
		_trainingFWODSettings.SetParent( newParent == null ? null : newParent._trainingFWODSettings );
		_ratingModifiers.SetParent( newParent == null ? null : newParent._ratingModifiers );
		_fullPartyRatingModifiers.SetParent( newParent == null ? null : newParent._fullPartyRatingModifiers );
		_forgeRollSettings.SetParent( newParent == null ? null : newParent._forgeRollSettings );
		_guildLevels.SetParent( newParent == null ? null : newParent._guildLevels );
		_requiredLevelForExclusiveTalents.SetParent( newParent == null ? null : newParent._requiredLevelForExclusiveTalents );
		_requiredRatingForExclusiveTalents.SetParent( newParent == null ? null : newParent._requiredRatingForExclusiveTalents );
		_clanWarsSettings.SetParent( newParent == null ? null : newParent._clanWarsSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_pvp.Reset();
		_defaultRollContainerCostByRank.Reset();
		_trainingFWODSettings.Reset();
		_ratingModifiers.Reset();
		_fullPartyRatingModifiers.Reset();
		_forgeRollSettings.Reset();
		_guildLevels.Reset();
		_requiredLevelForExclusiveTalents.Reset();
		_requiredRatingForExclusiveTalents.Reset();
		_clanWarsSettings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_pvp.IsDerivedFromParent()
			&& _defaultRollContainerCostByRank.IsDerivedFromParent()
			&& _trainingFWODSettings.IsDerivedFromParent()
			&& _ratingModifiers.IsDerivedFromParent()
			&& _fullPartyRatingModifiers.IsDerivedFromParent()
			&& _forgeRollSettings.IsDerivedFromParent()
			&& _guildLevels.IsDerivedFromParent()
			&& _requiredLevelForExclusiveTalents.IsDerivedFromParent()
			&& _requiredRatingForExclusiveTalents.IsDerivedFromParent()
			&& _clanWarsSettings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "pvp" )
			_pvp.Reset();
		else if ( fieldName == "defaultRollContainerCostByRank" )
			_defaultRollContainerCostByRank.Reset();
		else if ( fieldName == "trainingFWODSettings" )
			_trainingFWODSettings.Reset();
		else if ( fieldName == "ratingModifiers" )
			_ratingModifiers.Reset();
		else if ( fieldName == "fullPartyRatingModifiers" )
			_fullPartyRatingModifiers.Reset();
		else if ( fieldName == "forgeRollSettings" )
			_forgeRollSettings.Reset();
		else if ( fieldName == "guildLevels" )
			_guildLevels.Reset();
		else if ( fieldName == "requiredLevelForExclusiveTalents" )
			_requiredLevelForExclusiveTalents.Reset();
		else if ( fieldName == "requiredRatingForExclusiveTalents" )
			_requiredRatingForExclusiveTalents.Reset();
		else if ( fieldName == "clanWarsSettings" )
			_clanWarsSettings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "pvp" )
			return _pvp.IsDerivedFromParent();
		if ( fieldName == "defaultRollContainerCostByRank" )
			return _defaultRollContainerCostByRank.IsDerivedFromParent();
		if ( fieldName == "trainingFWODSettings" )
			return _trainingFWODSettings.IsDerivedFromParent();
		if ( fieldName == "ratingModifiers" )
			return _ratingModifiers.IsDerivedFromParent();
		if ( fieldName == "fullPartyRatingModifiers" )
			return _fullPartyRatingModifiers.IsDerivedFromParent();
		if ( fieldName == "forgeRollSettings" )
			return _forgeRollSettings.IsDerivedFromParent();
		if ( fieldName == "guildLevels" )
			return _guildLevels.IsDerivedFromParent();
		if ( fieldName == "requiredLevelForExclusiveTalents" )
			return _requiredLevelForExclusiveTalents.IsDerivedFromParent();
		if ( fieldName == "requiredRatingForExclusiveTalents" )
			return _requiredRatingForExclusiveTalents.IsDerivedFromParent();
		if ( fieldName == "clanWarsSettings" )
			return _clanWarsSettings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class SkinRollItem : RollItem
{
	private UndoRedoDBPtr<SkinRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<SkinRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<HeroSkin> _skin;

	public DBPtr<HeroSkin> skin { get { return _skin.Get(); } set { _skin.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SkinRollItem>(owner);
		_skin = new UndoRedoDBPtr<HeroSkin>( owner );
		___parent.Changed += FireChangedEvent;
		_skin.Changed += FireChangedEvent;
	}

	public SkinRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( SkinRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SkinRollItem" );
		skin = source.skin;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SkinRollItem source = _source as SkinRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkinRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SkinRollItem newParent = rawParent == null ? null : rawParent.Get<SkinRollItem>();
		if ( newParent == null && _newParent is SkinRollItem )
			newParent = _newParent as SkinRollItem;
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

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("ROLLITEM")]
public class TalentRollItem : RollItem
{
	private UndoRedoDBPtr<TalentRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Talent> _talent;

	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentRollItem>(owner);
		_talent = new UndoRedoDBPtr<Talent>( owner );
		___parent.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
	}

	public TalentRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentRollItem" );
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentRollItem source = _source as TalentRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentRollItem newParent = rawParent == null ? null : rawParent.Get<TalentRollItem>();
		if ( newParent == null && _newParent is TalentRollItem )
			newParent = _newParent as TalentRollItem;
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

[DBVersion(1)]
[IndexField("persistentId")]
[UseTypeName("TALUGRDENT")]
public class TalentUpgradeEntity : DBResource
{
	private UndoRedoDBPtr<TalentUpgradeEntity> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentUpgradeEntity> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private TextRef _description;
	private TextRef _tooltip;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedo<TalentUpgradeEntityType> _type;
	private UndoRedo<int> _talentLevelLimit;
	private UndoRedo<int> _probability;

	[Custom("DBServer", "Social")]
	[Description( "ID" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Custom("Social")]
	[NoCode]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Custom("Social")]
	[NoCode]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Custom("Social")]
	[Description( "Иконка" )]
	[NoCode]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Тип: улучшатель или катализатор" )]
	public TalentUpgradeEntityType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Максимальное кол-во звезд до которого может апнуть" )]
	public int talentLevelLimit { get { return _talentLevelLimit.Get(); } set { _talentLevelLimit.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Шанс срабатывания" )]
	public int probability { get { return _probability.Get(); } set { _probability.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentUpgradeEntity>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_description = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_type = new UndoRedo<TalentUpgradeEntityType>( owner, TalentUpgradeEntityType.Rune );
		_talentLevelLimit = new UndoRedo<int>( owner, 0 );
		_probability = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_talentLevelLimit.Changed += FireChangedEvent;
		_probability.Changed += FireChangedEvent;
	}

	public TalentUpgradeEntity()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentUpgradeEntity source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeEntity" );
		persistentId = source.persistentId;
		description = source.description;
		tooltip = source.tooltip;
		icon = source.icon;
		type = source.type;
		talentLevelLimit = source.talentLevelLimit;
		probability = source.probability;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentUpgradeEntity source = _source as TalentUpgradeEntity;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeEntity" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentUpgradeEntity newParent = rawParent == null ? null : rawParent.Get<TalentUpgradeEntity>();
		if ( newParent == null && _newParent is TalentUpgradeEntity )
			newParent = _newParent as TalentUpgradeEntity;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_description.SetParent( newParent == null ? null : newParent._description );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_type.SetParent( newParent == null ? null : newParent._type );
		_talentLevelLimit.SetParent( newParent == null ? null : newParent._talentLevelLimit );
		_probability.SetParent( newParent == null ? null : newParent._probability );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_description.Reset();
		_tooltip.Reset();
		_icon.Reset();
		_type.Reset();
		_talentLevelLimit.Reset();
		_probability.Reset();
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
			&& _type.IsDerivedFromParent()
			&& _talentLevelLimit.IsDerivedFromParent()
			&& _probability.IsDerivedFromParent()
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
		else if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "talentLevelLimit" )
			_talentLevelLimit.Reset();
		else if ( fieldName == "probability" )
			_probability.Reset();
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
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "talentLevelLimit" )
			return _talentLevelLimit.IsDerivedFromParent();
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class TalentUpgradeEntityRollItem : RollItem
{
	private UndoRedoDBPtr<TalentUpgradeEntityRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentUpgradeEntityRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TalentUpgradeEntity> _entity;

	public DBPtr<TalentUpgradeEntity> entity { get { return _entity.Get(); } set { _entity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentUpgradeEntityRollItem>(owner);
		_entity = new UndoRedoDBPtr<TalentUpgradeEntity>( owner );
		___parent.Changed += FireChangedEvent;
		_entity.Changed += FireChangedEvent;
	}

	public TalentUpgradeEntityRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentUpgradeEntityRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeEntityRollItem" );
		entity = source.entity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentUpgradeEntityRollItem source = _source as TalentUpgradeEntityRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeEntityRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentUpgradeEntityRollItem newParent = rawParent == null ? null : rawParent.Get<TalentUpgradeEntityRollItem>();
		if ( newParent == null && _newParent is TalentUpgradeEntityRollItem )
			newParent = _newParent as TalentUpgradeEntityRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_entity.SetParent( newParent == null ? null : newParent._entity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_entity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_entity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "entity" )
			_entity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "entity" )
			return _entity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
public class TalentUpgradeProbabilityTable : DBResource
{
	private UndoRedoDBPtr<TalentUpgradeProbabilityTable> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentUpgradeProbabilityTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TalentUpgradeProbability> _upgrades;

	[Description( "" )]
	public libdb.IChangeableList<TalentUpgradeProbability> upgrades { get { return _upgrades; } set { _upgrades.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentUpgradeProbabilityTable>(owner);
		_upgrades = new UndoRedoAssignableList<TalentUpgradeProbability>( owner );
		___parent.Changed += FireChangedEvent;
		_upgrades.Changed += FireChangedEvent;
	}

	public TalentUpgradeProbabilityTable()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentUpgradeProbabilityTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeProbabilityTable" );
		upgrades = source.upgrades;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentUpgradeProbabilityTable source = _source as TalentUpgradeProbabilityTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeProbabilityTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentUpgradeProbabilityTable newParent = rawParent == null ? null : rawParent.Get<TalentUpgradeProbabilityTable>();
		if ( newParent == null && _newParent is TalentUpgradeProbabilityTable )
			newParent = _newParent as TalentUpgradeProbabilityTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_upgrades.SetParent( newParent == null ? null : newParent._upgrades );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_upgrades.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_upgrades.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "upgrades" )
			_upgrades.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "upgrades" )
			return _upgrades.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer", "Social")]
[UseTypeName("ROLLITEM")]
public class TalentUpgradeRollItem : RollItem
{
	private UndoRedoDBPtr<TalentUpgradeRollItem> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentUpgradeRollItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TalentUpgradeProbabilityTable> _upgradeTable;
	private UndoRedoDBPtr<RollItem> _talentItem;

	[Description( "вероятности очков заточек" )]
	public DBPtr<TalentUpgradeProbabilityTable> upgradeTable { get { return _upgradeTable.Get(); } set { _upgradeTable.Set( value ); } }

	[Description( "итем, из которого должен наролиться ТАЛАНТ" )]
	public DBPtr<RollItem> talentItem { get { return _talentItem.Get(); } set { _talentItem.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentUpgradeRollItem>(owner);
		_upgradeTable = new UndoRedoDBPtr<TalentUpgradeProbabilityTable>( owner );
		_talentItem = new UndoRedoDBPtr<RollItem>( owner );
		___parent.Changed += FireChangedEvent;
		_upgradeTable.Changed += FireChangedEvent;
		_talentItem.Changed += FireChangedEvent;
	}

	public TalentUpgradeRollItem()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentUpgradeRollItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeRollItem" );
		upgradeTable = source.upgradeTable;
		talentItem = source.talentItem;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentUpgradeRollItem source = _source as TalentUpgradeRollItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentUpgradeRollItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentUpgradeRollItem newParent = rawParent == null ? null : rawParent.Get<TalentUpgradeRollItem>();
		if ( newParent == null && _newParent is TalentUpgradeRollItem )
			newParent = _newParent as TalentUpgradeRollItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_upgradeTable.SetParent( newParent == null ? null : newParent._upgradeTable );
		_talentItem.SetParent( newParent == null ? null : newParent._talentItem );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_upgradeTable.Reset();
		_talentItem.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_upgradeTable.IsDerivedFromParent()
			&& _talentItem.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "upgradeTable" )
			_upgradeTable.Reset();
		else if ( fieldName == "talentItem" )
			_talentItem.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "upgradeTable" )
			return _upgradeTable.IsDerivedFromParent();
		if ( fieldName == "talentItem" )
			return _talentItem.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
