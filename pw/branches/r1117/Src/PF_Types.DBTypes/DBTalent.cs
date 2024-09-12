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
[Custom("Social")]
public enum ETalentLevel
{
	id0 = 0,
	id1 = 1,
	id2 = 2,
	id3 = 3,
	id4 = 4,
	id5 = 5,
};

[Custom("DBServer", "Social")]
public enum ETalentRarity
{
	Class = 0,
	ordinary = 1,
	good = 2,
	excellent = 3,
	magnificent = 4,
	exclusive = 5,
	outstanding = 6,
};

[Custom("DBServer")]
[Flags]
public enum ETalentRollGroup
{
	PvP = 1,
	Training = 2,
	CTE = 4,
	PvE = 8,
	Castle = 16,
	MidOnly = 32,
	All = 63,
};

[Custom("Social")]
public enum ETalents
{
	points_per_level = 4,
};

[Custom("Social")]
public enum ETalentSlot
{
	id0 = 0,
	id1 = 1,
	id2 = 2,
	id3 = 3,
	id4 = 4,
	id5 = 5,
};

[Custom("Social")]
public enum ETalentSlotStatus
{
	normal = 0,
	locked = 1,
	unavailable = 2,
};

[IndexField("caption")]
public class AchievmentCondition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AchievmentCondition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<AchievBase> _achiev;
	private UndoRedo<int> _minRank;

	public DBPtr<AchievBase> achiev { get { return _achiev.Get(); } set { _achiev.Set( value ); } }

	[IntMin(1)]
	public int minRank { get { return _minRank.Get(); } set { _minRank.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_achiev = new UndoRedoDBPtr<AchievBase>( owner );
		_minRank = new UndoRedo<int>( owner, 1 );
		_achiev.Changed += FireChangedEvent;
		_minRank.Changed += FireChangedEvent;
	}

	public AchievmentCondition()
	{
		Initialize( GetOwner() );
	}

	public AchievmentCondition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AchievmentCondition( DBResource owner, AchievmentCondition source )
		: this(owner, source, true){}

	protected AchievmentCondition( DBResource owner, AchievmentCondition source, bool fireEvent )
	{
		_achiev = new UndoRedoDBPtr<AchievBase>( owner, source.achiev );
		_minRank = new UndoRedo<int>( owner, source.minRank );
		_achiev.Changed += FireChangedEvent;
		_minRank.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AchievmentCondition source = _source as AchievmentCondition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievmentCondition" );
		achiev = source.achiev;
		minRank = source.minRank;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AchievmentCondition newParent = _newParent as AchievmentCondition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_achiev.SetParent( newParent == null ? null : newParent._achiev );
		_minRank.SetParent( newParent == null ? null : newParent._minRank );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_achiev.Reset();
		_minRank.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_achiev.IsDerivedFromParent()
			&& _minRank.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "achiev" )
			_achiev.Reset();
		else if ( fieldName == "minRank" )
			_minRank.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "achiev" )
			return _achiev.IsDerivedFromParent();
		if ( fieldName == "minRank" )
			return _minRank.IsDerivedFromParent();
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
public class ConsumptionBonus : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ConsumptionBonus __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _constant;
	private UndoRedo<int> _percent;

	public int constant { get { return _constant.Get(); } set { _constant.Set( value ); } }

	public int percent { get { return _percent.Get(); } set { _percent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_constant = new UndoRedo<int>( owner, 0 );
		_percent = new UndoRedo<int>( owner, 0 );
		_constant.Changed += FireChangedEvent;
		_percent.Changed += FireChangedEvent;
	}

	public ConsumptionBonus()
	{
		Initialize( GetOwner() );
	}

	public ConsumptionBonus( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ConsumptionBonus( DBResource owner, ConsumptionBonus source )
		: this(owner, source, true){}

	protected ConsumptionBonus( DBResource owner, ConsumptionBonus source, bool fireEvent )
	{
		_constant = new UndoRedo<int>( owner, source.constant );
		_percent = new UndoRedo<int>( owner, source.percent );
		_constant.Changed += FireChangedEvent;
		_percent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ConsumptionBonus source = _source as ConsumptionBonus;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConsumptionBonus" );
		constant = source.constant;
		percent = source.percent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ConsumptionBonus newParent = _newParent as ConsumptionBonus;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_constant.SetParent( newParent == null ? null : newParent._constant );
		_percent.SetParent( newParent == null ? null : newParent._percent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_constant.Reset();
		_percent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_constant.IsDerivedFromParent()
			&& _percent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "constant" )
			_constant.Reset();
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
		if ( fieldName == "constant" )
			return _constant.IsDerivedFromParent();
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

[Custom("Social")]
[DBVersion(0)]
public class TalentSlot : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentSlot __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ETalentSlotStatus> _status;
	private UndoRedoDBPtr<Talent> _talent;
	private UndoRedo<int> _refineRate;
	private UndoRedo<int> _aIPriority;

	[Description( "Can't use an talents in this slot, if not 'normal'!" )]
	public ETalentSlotStatus status { get { return _status.Get(); } set { _status.Set( value ); } }

	[Description( "Talent, used in this slot!" )]
	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	[IntMinMax(1, 10)]
	public int refineRate { get { return _refineRate.Get(); } set { _refineRate.Set( value ); } }

	[Description( "Priority for bots" )]
	public int aIPriority { get { return _aIPriority.Get(); } set { _aIPriority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_status = new UndoRedo<ETalentSlotStatus>( owner, ETalentSlotStatus.normal );
		_talent = new UndoRedoDBPtr<Talent>( owner );
		_refineRate = new UndoRedo<int>( owner, 1 );
		_aIPriority = new UndoRedo<int>( owner, 0 );
		_status.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
		_refineRate.Changed += FireChangedEvent;
		_aIPriority.Changed += FireChangedEvent;
	}

	public TalentSlot()
	{
		Initialize( GetOwner() );
	}

	public TalentSlot( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentSlot( DBResource owner, TalentSlot source )
		: this(owner, source, true){}

	protected TalentSlot( DBResource owner, TalentSlot source, bool fireEvent )
	{
		_status = new UndoRedo<ETalentSlotStatus>( owner, source.status );
		_talent = new UndoRedoDBPtr<Talent>( owner, source.talent );
		_refineRate = new UndoRedo<int>( owner, source.refineRate );
		_aIPriority = new UndoRedo<int>( owner, source.aIPriority );
		_status.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
		_refineRate.Changed += FireChangedEvent;
		_aIPriority.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentSlot source = _source as TalentSlot;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentSlot" );
		status = source.status;
		talent = source.talent;
		refineRate = source.refineRate;
		aIPriority = source.aIPriority;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentSlot newParent = _newParent as TalentSlot;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_status.SetParent( newParent == null ? null : newParent._status );
		_talent.SetParent( newParent == null ? null : newParent._talent );
		_refineRate.SetParent( newParent == null ? null : newParent._refineRate );
		_aIPriority.SetParent( newParent == null ? null : newParent._aIPriority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_status.Reset();
		_talent.Reset();
		_refineRate.Reset();
		_aIPriority.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_status.IsDerivedFromParent()
			&& _talent.IsDerivedFromParent()
			&& _refineRate.IsDerivedFromParent()
			&& _aIPriority.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "status" )
			_status.Reset();
		else if ( fieldName == "talent" )
			_talent.Reset();
		else if ( fieldName == "refineRate" )
			_refineRate.Reset();
		else if ( fieldName == "aIPriority" )
			_aIPriority.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "status" )
			return _status.IsDerivedFromParent();
		if ( fieldName == "talent" )
			return _talent.IsDerivedFromParent();
		if ( fieldName == "refineRate" )
			return _refineRate.IsDerivedFromParent();
		if ( fieldName == "aIPriority" )
			return _aIPriority.IsDerivedFromParent();
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
[DBVersion(0)]
public class TalentsLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentsLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<TalentSlot> _talents;

	[EnumArray(typeof(ETalentSlot))]
	public libdb.IChangeableList<TalentSlot> talents { get { return _talents; } set { _talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_talents = new UndoRedoAssignableList<TalentSlot>( owner, typeof( ETalentSlot ) );
		_talents.Changed += FireChangedEvent;
	}

	public TalentsLevel()
	{
		Initialize( GetOwner() );
	}

	public TalentsLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentsLevel( DBResource owner, TalentsLevel source )
		: this(owner, source, true){}

	protected TalentsLevel( DBResource owner, TalentsLevel source, bool fireEvent )
	{
		_talents = new UndoRedoAssignableList<TalentSlot>( owner, typeof( ETalentSlot ) );
		_talents.Assign( source.talents );
		_talents.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentsLevel source = _source as TalentsLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsLevel" );
		talents = source.talents;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentsLevel newParent = _newParent as TalentsLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_talents.SetParent( newParent == null ? null : newParent._talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_talents.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_talents.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "talents" )
			_talents.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
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

[Browsable( false )]
[Custom("Social")]
[IndexField("stat")]
[NoCode]
public class TalentStats : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentStats __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EStat> _stat;
	private UndoRedoList<float> _values;
	private UndoRedo<string> _addValueName;

	public EStat stat { get { return _stat.Get(); } set { _stat.Set( value ); } }

	public libdb.IChangeableList<float> values { get { return _values; } set { _values.Assign( value ); } }

	public string addValueName { get { return _addValueName.Get(); } set { _addValueName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_stat = new UndoRedo<EStat>( owner, EStat.Life );
		_values = new UndoRedoList<float>( owner );
		_addValueName = new UndoRedo<string>( owner, string.Empty );
		_stat.Changed += FireChangedEvent;
		_values.Changed += FireChangedEvent;
		_addValueName.Changed += FireChangedEvent;
	}

	public TalentStats()
	{
		Initialize( GetOwner() );
	}

	public TalentStats( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentStats( DBResource owner, TalentStats source )
		: this(owner, source, true){}

	protected TalentStats( DBResource owner, TalentStats source, bool fireEvent )
	{
		_stat = new UndoRedo<EStat>( owner, source.stat );
		_values = new UndoRedoList<float>( owner );
		_values.Assign( source.values );
		_addValueName = new UndoRedo<string>( owner, source.addValueName );
		_stat.Changed += FireChangedEvent;
		_values.Changed += FireChangedEvent;
		_addValueName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentStats source = _source as TalentStats;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentStats" );
		stat = source.stat;
		values = source.values;
		addValueName = source.addValueName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentStats newParent = _newParent as TalentStats;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_stat.SetParent( newParent == null ? null : newParent._stat );
		_values.SetParent( newParent == null ? null : newParent._values );
		_addValueName.SetParent( newParent == null ? null : newParent._addValueName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_stat.Reset();
		_values.Reset();
		_addValueName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_stat.IsDerivedFromParent()
			&& _values.IsDerivedFromParent()
			&& _addValueName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "stat" )
			_stat.Reset();
		else if ( fieldName == "values" )
			_values.Reset();
		else if ( fieldName == "addValueName" )
			_addValueName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "stat" )
			return _stat.IsDerivedFromParent();
		if ( fieldName == "values" )
			return _values.IsDerivedFromParent();
		if ( fieldName == "addValueName" )
			return _addValueName.IsDerivedFromParent();
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
[TypeId(0x0F690AC0)]
[UseTypeName("TALENT")]
public class Talent : Ability
{
	private UndoRedoDBPtr<Talent> ___parent;
	[HideInOutliner]
	public new DBPtr<Talent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minLevel;
	private UndoRedo<int> _devPoints;
	private UndoRedo<float> _budget;
	private UndoRedoAssignableList<AchievmentCondition> _activationConditions;
	private UndoRedo<int> _naftaCost;
	private UndoRedoAssignableList<DBPtr<Talent>> _prerequisiteTalents;
	private UndoRedoAssignableList<DBPtr<Talent>> _conflictingTalents;
	private UndoRedo<ETalentRarity> _rarity;
	private UndoRedo<string> _persistentId;
	private UndoRedo<int> _vendorCost;
	private UndoRedo<ETalentRollGroup> _talentRollGroups;
	private UndoRedo<int> _askId;
	private UndoRedo<bool> _isGenderTalent;
	private UndoRedo<bool> _isTakenOnStart;
	private UndoRedo<bool> _isUltimateTalent;
	private UndoRedo<int> _upgradeLevel;
	private ConsumptionBonus _consumptionBonus;
	private UndoRedoAssignableList<TalentStats> _talentStats;
	private UndoRedoAssignableList<TalentStats> _variativeMaxTalentStats;
	private UndoRedoAssignableList<TalentStats> _variativeMinTalentStats;
	private UndoRedo<float> _forceBonus;

	[Category( "TURs" )]
	[Custom("Social")]
	[Description( "Level of talent (TUR)" )]
	[IntMin(0)]
	public int minLevel { get { return _minLevel.Get(); } set { _minLevel.Set( value ); } }

	[Category( "TURs" )]
	[Custom("Social")]
	[Description( "Development points to add on talent activate" )]
	[IntMin(1)]
	public int devPoints { get { return _devPoints.Get(); } set { _devPoints.Set( value ); } }

	[Custom("Social")]
	public float budget { get { return _budget.Get(); } set { _budget.Set( value ); } }

	[Category( "TURs" )]
	[Description( "Conditions to determinate then talent can be activated (AND)" )]
	public libdb.IChangeableList<AchievmentCondition> activationConditions { get { return _activationConditions; } set { _activationConditions.Assign( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Cost of activation" )]
	public int naftaCost { get { return _naftaCost.Get(); } set { _naftaCost.Set( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Prerequisite talents." )]
	public libdb.IChangeableList<DBPtr<Talent>> prerequisiteTalents { get { return _prerequisiteTalents; } set { _prerequisiteTalents.Assign( value ); } }

	[Custom("Social")]
	[Description( "Conflicting(alternative) talents." )]
	[NoCode]
	public libdb.IChangeableList<DBPtr<Talent>> conflictingTalents { get { return _conflictingTalents; } set { _conflictingTalents.Assign( value ); } }

	[Category( "UI" )]
	[Custom("DBServer", "Social")]
	[Description( "Rarity of talent" )]
	public ETalentRarity rarity { get { return _rarity.Get(); } set { _rarity.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Talent name to formulas" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Custom("DBServer")]
	[Description( "Talent vendor cost" )]
	public int vendorCost { get { return _vendorCost.Get(); } set { _vendorCost.Set( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Talent roll group" )]
	public ETalentRollGroup talentRollGroups { get { return _talentRollGroups.Get(); } set { _talentRollGroups.Set( value ); } }

	[Description( "Ask index to play. 0 - not set, 1 - A1, etc.." )]
	public int askId { get { return _askId.Get(); } set { _askId.Set( value ); } }

	[Custom("Social")]
	[Description( "Flag for indication of gender talents" )]
	public bool isGenderTalent { get { return _isGenderTalent.Get(); } set { _isGenderTalent.Set( value ); } }

	[Custom("Social")]
	[Description( "We should have this talent already bought on start?" )]
	public bool isTakenOnStart { get { return _isTakenOnStart.Get(); } set { _isTakenOnStart.Set( value ); } }

	[Custom("Social")]
	[Description( "Is super puper talent ? 0_o" )]
	public bool isUltimateTalent { get { return _isUltimateTalent.Get(); } set { _isUltimateTalent.Set( value ); } }

	[Custom("Social")]
	[Description( "Describes talent upgrade. 0 means basic talent, 1- first basic talent upgrade etc" )]
	public int upgradeLevel { get { return _upgradeLevel.Get(); } set { _upgradeLevel.Set( value ); } }

	[Custom("Social")]
	[Description( "Stores information about ConsumptionBonusConstant and ConsumptionBounsPercent needed for Consumption" )]
	public ConsumptionBonus consumptionBonus { get { return _consumptionBonus; } set { _consumptionBonus.Assign( value ); } }

	[Browsable( false )]
	[Custom("Social")]
	[NoCode]
	public libdb.IChangeableList<TalentStats> talentStats { get { return _talentStats; } set { _talentStats.Assign( value ); } }

	[Browsable( false )]
	[Custom("Social")]
	[Description( "Variative stats depending on current hero max base stats NUM_TASK" )]
	[NoCode]
	public libdb.IChangeableList<TalentStats> variativeMaxTalentStats { get { return _variativeMaxTalentStats; } set { _variativeMaxTalentStats.Assign( value ); } }

	[Browsable( false )]
	[Custom("Social")]
	[Description( "Variative stats depending on current hero min base stats NUM_TASK" )]
	[NoCode]
	public libdb.IChangeableList<TalentStats> variativeMinTalentStats { get { return _variativeMinTalentStats; } set { _variativeMinTalentStats.Assign( value ); } }

	[Browsable( false )]
	[Custom("Social")]
	[NoCode]
	public float forceBonus { get { return _forceBonus.Get(); } set { _forceBonus.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Talent>(owner);
		_minLevel = new UndoRedo<int>( owner, 0 );
		_devPoints = new UndoRedo<int>( owner, 1 );
		_budget = new UndoRedo<float>( owner, 0.0f );
		_activationConditions = new UndoRedoAssignableList<AchievmentCondition>( owner );
		_naftaCost = new UndoRedo<int>( owner, 0 );
		_prerequisiteTalents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_conflictingTalents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_rarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.ordinary );
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_vendorCost = new UndoRedo<int>( owner, 0 );
		_talentRollGroups = new UndoRedo<ETalentRollGroup>( owner, ETalentRollGroup.All );
		_askId = new UndoRedo<int>( owner, 0 );
		_isGenderTalent = new UndoRedo<bool>( owner, false );
		_isTakenOnStart = new UndoRedo<bool>( owner, false );
		_isUltimateTalent = new UndoRedo<bool>( owner, false );
		_upgradeLevel = new UndoRedo<int>( owner, 0 );
		_consumptionBonus = new ConsumptionBonus( owner );
		_talentStats = new UndoRedoAssignableList<TalentStats>( owner );
		_variativeMaxTalentStats = new UndoRedoAssignableList<TalentStats>( owner );
		_variativeMinTalentStats = new UndoRedoAssignableList<TalentStats>( owner );
		_forceBonus = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_minLevel.Changed += FireChangedEvent;
		_devPoints.Changed += FireChangedEvent;
		_budget.Changed += FireChangedEvent;
		_activationConditions.Changed += FireChangedEvent;
		_naftaCost.Changed += FireChangedEvent;
		_prerequisiteTalents.Changed += FireChangedEvent;
		_conflictingTalents.Changed += FireChangedEvent;
		_rarity.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_vendorCost.Changed += FireChangedEvent;
		_talentRollGroups.Changed += FireChangedEvent;
		_askId.Changed += FireChangedEvent;
		_isGenderTalent.Changed += FireChangedEvent;
		_isTakenOnStart.Changed += FireChangedEvent;
		_isUltimateTalent.Changed += FireChangedEvent;
		_upgradeLevel.Changed += FireChangedEvent;
		_consumptionBonus.Changed += FireChangedEvent;
		_talentStats.Changed += FireChangedEvent;
		_variativeMaxTalentStats.Changed += FireChangedEvent;
		_variativeMinTalentStats.Changed += FireChangedEvent;
		_forceBonus.Changed += FireChangedEvent;
	}

	public Talent()
	{
		Initialize( this );
	}
	private void AssignSelf( Talent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Talent" );
		minLevel = source.minLevel;
		devPoints = source.devPoints;
		budget = source.budget;
		activationConditions = source.activationConditions;
		naftaCost = source.naftaCost;
		prerequisiteTalents = source.prerequisiteTalents;
		conflictingTalents = source.conflictingTalents;
		rarity = source.rarity;
		persistentId = source.persistentId;
		vendorCost = source.vendorCost;
		talentRollGroups = source.talentRollGroups;
		askId = source.askId;
		isGenderTalent = source.isGenderTalent;
		isTakenOnStart = source.isTakenOnStart;
		isUltimateTalent = source.isUltimateTalent;
		upgradeLevel = source.upgradeLevel;
		consumptionBonus = source.consumptionBonus;
		talentStats = source.talentStats;
		variativeMaxTalentStats = source.variativeMaxTalentStats;
		variativeMinTalentStats = source.variativeMinTalentStats;
		forceBonus = source.forceBonus;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Talent source = _source as Talent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Talent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Talent newParent = rawParent == null ? null : rawParent.Get<Talent>();
		if ( newParent == null && _newParent is Talent )
			newParent = _newParent as Talent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minLevel.SetParent( newParent == null ? null : newParent._minLevel );
		_devPoints.SetParent( newParent == null ? null : newParent._devPoints );
		_budget.SetParent( newParent == null ? null : newParent._budget );
		_activationConditions.SetParent( newParent == null ? null : newParent._activationConditions );
		_naftaCost.SetParent( newParent == null ? null : newParent._naftaCost );
		_prerequisiteTalents.SetParent( newParent == null ? null : newParent._prerequisiteTalents );
		_conflictingTalents.SetParent( newParent == null ? null : newParent._conflictingTalents );
		_rarity.SetParent( newParent == null ? null : newParent._rarity );
		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_vendorCost.SetParent( newParent == null ? null : newParent._vendorCost );
		_talentRollGroups.SetParent( newParent == null ? null : newParent._talentRollGroups );
		_askId.SetParent( newParent == null ? null : newParent._askId );
		_isGenderTalent.SetParent( newParent == null ? null : newParent._isGenderTalent );
		_isTakenOnStart.SetParent( newParent == null ? null : newParent._isTakenOnStart );
		_isUltimateTalent.SetParent( newParent == null ? null : newParent._isUltimateTalent );
		_upgradeLevel.SetParent( newParent == null ? null : newParent._upgradeLevel );
		_consumptionBonus.SetParent( newParent == null ? null : newParent._consumptionBonus );
		_talentStats.SetParent( newParent == null ? null : newParent._talentStats );
		_variativeMaxTalentStats.SetParent( newParent == null ? null : newParent._variativeMaxTalentStats );
		_variativeMinTalentStats.SetParent( newParent == null ? null : newParent._variativeMinTalentStats );
		_forceBonus.SetParent( newParent == null ? null : newParent._forceBonus );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minLevel.Reset();
		_devPoints.Reset();
		_budget.Reset();
		_activationConditions.Reset();
		_naftaCost.Reset();
		_prerequisiteTalents.Reset();
		_conflictingTalents.Reset();
		_rarity.Reset();
		_persistentId.Reset();
		_vendorCost.Reset();
		_talentRollGroups.Reset();
		_askId.Reset();
		_isGenderTalent.Reset();
		_isTakenOnStart.Reset();
		_isUltimateTalent.Reset();
		_upgradeLevel.Reset();
		_consumptionBonus.Reset();
		_talentStats.Reset();
		_variativeMaxTalentStats.Reset();
		_variativeMinTalentStats.Reset();
		_forceBonus.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minLevel.IsDerivedFromParent()
			&& _devPoints.IsDerivedFromParent()
			&& _budget.IsDerivedFromParent()
			&& _activationConditions.IsDerivedFromParent()
			&& _naftaCost.IsDerivedFromParent()
			&& _prerequisiteTalents.IsDerivedFromParent()
			&& _conflictingTalents.IsDerivedFromParent()
			&& _rarity.IsDerivedFromParent()
			&& _persistentId.IsDerivedFromParent()
			&& _vendorCost.IsDerivedFromParent()
			&& _talentRollGroups.IsDerivedFromParent()
			&& _askId.IsDerivedFromParent()
			&& _isGenderTalent.IsDerivedFromParent()
			&& _isTakenOnStart.IsDerivedFromParent()
			&& _isUltimateTalent.IsDerivedFromParent()
			&& _upgradeLevel.IsDerivedFromParent()
			&& _consumptionBonus.IsDerivedFromParent()
			&& _talentStats.IsDerivedFromParent()
			&& _variativeMaxTalentStats.IsDerivedFromParent()
			&& _variativeMinTalentStats.IsDerivedFromParent()
			&& _forceBonus.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minLevel" )
			_minLevel.Reset();
		else if ( fieldName == "devPoints" )
			_devPoints.Reset();
		else if ( fieldName == "budget" )
			_budget.Reset();
		else if ( fieldName == "activationConditions" )
			_activationConditions.Reset();
		else if ( fieldName == "naftaCost" )
			_naftaCost.Reset();
		else if ( fieldName == "prerequisiteTalents" )
			_prerequisiteTalents.Reset();
		else if ( fieldName == "conflictingTalents" )
			_conflictingTalents.Reset();
		else if ( fieldName == "rarity" )
			_rarity.Reset();
		else if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "vendorCost" )
			_vendorCost.Reset();
		else if ( fieldName == "talentRollGroups" )
			_talentRollGroups.Reset();
		else if ( fieldName == "askId" )
			_askId.Reset();
		else if ( fieldName == "isGenderTalent" )
			_isGenderTalent.Reset();
		else if ( fieldName == "isTakenOnStart" )
			_isTakenOnStart.Reset();
		else if ( fieldName == "isUltimateTalent" )
			_isUltimateTalent.Reset();
		else if ( fieldName == "upgradeLevel" )
			_upgradeLevel.Reset();
		else if ( fieldName == "consumptionBonus" )
			_consumptionBonus.Reset();
		else if ( fieldName == "talentStats" )
			_talentStats.Reset();
		else if ( fieldName == "variativeMaxTalentStats" )
			_variativeMaxTalentStats.Reset();
		else if ( fieldName == "variativeMinTalentStats" )
			_variativeMinTalentStats.Reset();
		else if ( fieldName == "forceBonus" )
			_forceBonus.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minLevel" )
			return _minLevel.IsDerivedFromParent();
		if ( fieldName == "devPoints" )
			return _devPoints.IsDerivedFromParent();
		if ( fieldName == "budget" )
			return _budget.IsDerivedFromParent();
		if ( fieldName == "activationConditions" )
			return _activationConditions.IsDerivedFromParent();
		if ( fieldName == "naftaCost" )
			return _naftaCost.IsDerivedFromParent();
		if ( fieldName == "prerequisiteTalents" )
			return _prerequisiteTalents.IsDerivedFromParent();
		if ( fieldName == "conflictingTalents" )
			return _conflictingTalents.IsDerivedFromParent();
		if ( fieldName == "rarity" )
			return _rarity.IsDerivedFromParent();
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "vendorCost" )
			return _vendorCost.IsDerivedFromParent();
		if ( fieldName == "talentRollGroups" )
			return _talentRollGroups.IsDerivedFromParent();
		if ( fieldName == "askId" )
			return _askId.IsDerivedFromParent();
		if ( fieldName == "isGenderTalent" )
			return _isGenderTalent.IsDerivedFromParent();
		if ( fieldName == "isTakenOnStart" )
			return _isTakenOnStart.IsDerivedFromParent();
		if ( fieldName == "isUltimateTalent" )
			return _isUltimateTalent.IsDerivedFromParent();
		if ( fieldName == "upgradeLevel" )
			return _upgradeLevel.IsDerivedFromParent();
		if ( fieldName == "consumptionBonus" )
			return _consumptionBonus.IsDerivedFromParent();
		if ( fieldName == "talentStats" )
			return _talentStats.IsDerivedFromParent();
		if ( fieldName == "variativeMaxTalentStats" )
			return _variativeMaxTalentStats.IsDerivedFromParent();
		if ( fieldName == "variativeMinTalentStats" )
			return _variativeMinTalentStats.IsDerivedFromParent();
		if ( fieldName == "forceBonus" )
			return _forceBonus.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("caption")]
[TypeId(0xE79C6BC0)]
[UseTypeName("TALKIT")]
public class TalentKit : DBResource
{
	private UndoRedoDBPtr<TalentKit> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentKit> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;
	private TextRef _name;
	private UndoRedoDBPtr<Talent> _special;
	private UndoRedo<int> _kitCapacity;
	private UndoRedoAssignableList<DBPtr<Talent>> _talents;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Custom("Social")]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Custom("Social")]
	public DBPtr<Talent> special { get { return _special.Get(); } set { _special.Set( value ); } }

	public int kitCapacity { get { return _kitCapacity.Get(); } set { _kitCapacity.Set( value ); } }

	[Custom("Social")]
	[Description( "Список талантов в этом наборе (сете)" )]
	public libdb.IChangeableList<DBPtr<Talent>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentKit>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		_special = new UndoRedoDBPtr<Talent>( owner );
		_kitCapacity = new UndoRedo<int>( owner, 0 );
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_special.Changed += FireChangedEvent;
		_kitCapacity.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
	}

	public TalentKit()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentKit source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentKit" );
		caption = source.caption;
		name = source.name;
		special = source.special;
		kitCapacity = source.kitCapacity;
		talents = source.talents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentKit source = _source as TalentKit;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentKit" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentKit newParent = rawParent == null ? null : rawParent.Get<TalentKit>();
		if ( newParent == null && _newParent is TalentKit )
			newParent = _newParent as TalentKit;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_name.SetParent( newParent == null ? null : newParent._name );
		_special.SetParent( newParent == null ? null : newParent._special );
		_kitCapacity.SetParent( newParent == null ? null : newParent._kitCapacity );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		_name.Reset();
		_special.Reset();
		_kitCapacity.Reset();
		_talents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _special.IsDerivedFromParent()
			&& _kitCapacity.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "special" )
			_special.Reset();
		else if ( fieldName == "kitCapacity" )
			_kitCapacity.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
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
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "special" )
			return _special.IsDerivedFromParent();
		if ( fieldName == "kitCapacity" )
			return _kitCapacity.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("id")]
[TypeId(0xE79C6BC1)]
[UseTypeName("TALPACK")]
public class TalentPack : DBResource
{
	private UndoRedoDBPtr<TalentPack> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentPack> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _id;
	private TextRef _name;
	private UndoRedo<string> _iconStyle;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedo<bool> _isRedPack;
	private UndoRedoAssignableList<DBPtr<Talent>> _talents;

	[Description( "Имя (строковой айдишник) пака, чтобы можно было спросить через формулы. Паки должны иметь уникальные id." )]
	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	[Custom("Social")]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Custom("Social")]
	public string iconStyle { get { return _iconStyle.Get(); } set { _iconStyle.Set( value ); } }

	[Custom("Social")]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Custom("Social")]
	public bool isRedPack { get { return _isRedPack.Get(); } set { _isRedPack.Set( value ); } }

	[Custom("Social")]
	[Description( "Список талантов в этом паке (edition-е)" )]
	public libdb.IChangeableList<DBPtr<Talent>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentPack>(owner);
		_id = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		_iconStyle = new UndoRedo<string>( owner, string.Empty );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_isRedPack = new UndoRedo<bool>( owner, false );
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		___parent.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_iconStyle.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_isRedPack.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
	}

	public TalentPack()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentPack source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentPack" );
		id = source.id;
		name = source.name;
		iconStyle = source.iconStyle;
		icon = source.icon;
		isRedPack = source.isRedPack;
		talents = source.talents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentPack source = _source as TalentPack;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentPack" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentPack newParent = rawParent == null ? null : rawParent.Get<TalentPack>();
		if ( newParent == null && _newParent is TalentPack )
			newParent = _newParent as TalentPack;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_id.SetParent( newParent == null ? null : newParent._id );
		_name.SetParent( newParent == null ? null : newParent._name );
		_iconStyle.SetParent( newParent == null ? null : newParent._iconStyle );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_isRedPack.SetParent( newParent == null ? null : newParent._isRedPack );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_id.Reset();
		_name.Reset();
		_iconStyle.Reset();
		_icon.Reset();
		_isRedPack.Reset();
		_talents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _iconStyle.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _isRedPack.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "iconStyle" )
			_iconStyle.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "isRedPack" )
			_isRedPack.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
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
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "iconStyle" )
			return _iconStyle.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "isRedPack" )
			return _isRedPack.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[TypeId(0x0F691300)]
[UseTypeName("TALENTSET")]
public class TalentsSet : DBResource
{
	private UndoRedoDBPtr<TalentsSet> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentsSet> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TalentsLevel> _levels;

	[EnumArray(typeof(ETalentLevel))]
	public libdb.IChangeableList<TalentsLevel> levels { get { return _levels; } set { _levels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentsSet>(owner);
		_levels = new UndoRedoAssignableList<TalentsLevel>( owner, typeof( ETalentLevel ) );
		___parent.Changed += FireChangedEvent;
		_levels.Changed += FireChangedEvent;
	}

	public TalentsSet()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentsSet source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentsSet" );
		levels = source.levels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentsSet source = _source as TalentsSet;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsSet" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentsSet newParent = rawParent == null ? null : rawParent.Get<TalentsSet>();
		if ( newParent == null && _newParent is TalentsSet )
			newParent = _newParent as TalentsSet;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_levels.SetParent( newParent == null ? null : newParent._levels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_levels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_levels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "levels" )
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

}; // namespace DBTypes
