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
public class GuildCycle : CycleType, libdb.ICompositeDBValue, libdb.IChangeable
{

	private GuildCycle __parent = null;

	private UndoRedoList<int> _percents;

	[Description( "??????? ?????? ?????? ?? ????? ??????? ?? ????????? ?????" )]
	[EnumArray(typeof(EResourceType))]
	public libdb.IChangeableList<int> percents { get { return _percents; } set { _percents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_percents = new UndoRedoList<int>( owner, typeof( EResourceType ) );
		_percents.Changed += FireChangedEvent;
	}

	public GuildCycle()
	{
		Initialize( GetOwner() );
	}

	public GuildCycle( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public GuildCycle( DBResource owner, GuildCycle source ): base(owner, source, false)
	{
		_percents = new UndoRedoList<int>( owner, typeof( EResourceType ) );
		_percents.Assign( source.percents );
		_percents.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		GuildCycle source = _source as GuildCycle;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildCycle" );

		base.Assign( source );

		percents = source.percents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		GuildCycle newParent = _newParent as GuildCycle;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_percents.SetParent( newParent == null ? null : newParent._percents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_percents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_percents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "percents" )
			_percents.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "percents" )
			return _percents.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildSuzerenLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildSuzerenLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<Int64> _requiredExp;

	[Description( "????? ??? ?????????? ??????? ??????" )]
	public Int64 requiredExp { get { return _requiredExp.Get(); } set { _requiredExp.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_requiredExp = new UndoRedo<Int64>( owner, 0 );
		_requiredExp.Changed += FireChangedEvent;
	}

	public GuildSuzerenLevel()
	{
		Initialize( GetOwner() );
	}

	public GuildSuzerenLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildSuzerenLevel( DBResource owner, GuildSuzerenLevel source )
		: this(owner, source, true){}

	protected GuildSuzerenLevel( DBResource owner, GuildSuzerenLevel source, bool fireEvent )
	{
		_requiredExp = new UndoRedo<Int64>( owner, source.requiredExp );
		_requiredExp.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildSuzerenLevel source = _source as GuildSuzerenLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildSuzerenLevel" );
		requiredExp = source.requiredExp;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildSuzerenLevel newParent = _newParent as GuildSuzerenLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_requiredExp.SetParent( newParent == null ? null : newParent._requiredExp );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_requiredExp.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_requiredExp.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "requiredExp" )
			_requiredExp.Reset();
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
public class GuildBankSlotsBonus : GuildBonus
{
	private UndoRedoDBPtr<GuildBankSlotsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBankSlotsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _slots;

	[Description( "?????????? ?????????????? ?????? ????? ??????? (const). ???????? ??? namemap'?" )]
	[NameMapValue]
	public int slots { get { return _slots.Get(); } set { _slots.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBankSlotsBonus>(owner);
		_slots = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_slots.Changed += FireChangedEvent;
	}

	public GuildBankSlotsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBankSlotsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBankSlotsBonus" );
		slots = source.slots;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBankSlotsBonus source = _source as GuildBankSlotsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBankSlotsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBankSlotsBonus newParent = rawParent == null ? null : rawParent.Get<GuildBankSlotsBonus>();
		if ( newParent == null && _newParent is GuildBankSlotsBonus )
			newParent = _newParent as GuildBankSlotsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_slots.SetParent( newParent == null ? null : newParent._slots );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_slots.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_slots.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "slots" )
			_slots.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "slots" )
			return _slots.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildMemberBonus : GuildBonus
{
	private UndoRedoDBPtr<GuildMemberBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildMemberBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _members;

	[Description( "?????????? ?????????????? ??????? ??????? (const). ???????? ??? namemap'?" )]
	[NameMapValue]
	public int members { get { return _members.Get(); } set { _members.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildMemberBonus>(owner);
		_members = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_members.Changed += FireChangedEvent;
	}

	public GuildMemberBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildMemberBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildMemberBonus" );
		members = source.members;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildMemberBonus source = _source as GuildMemberBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildMemberBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildMemberBonus newParent = rawParent == null ? null : rawParent.Get<GuildMemberBonus>();
		if ( newParent == null && _newParent is GuildMemberBonus )
			newParent = _newParent as GuildMemberBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_members.SetParent( newParent == null ? null : newParent._members );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_members.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_members.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "members" )
			_members.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "members" )
			return _members.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildOpenBankBonus : GuildBonus
{
	private UndoRedoDBPtr<GuildOpenBankBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildOpenBankBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildOpenBankBonus>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public GuildOpenBankBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildOpenBankBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildOpenBankBonus" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildOpenBankBonus source = _source as GuildOpenBankBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildOpenBankBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildOpenBankBonus newParent = rawParent == null ? null : rawParent.Get<GuildOpenBankBonus>();
		if ( newParent == null && _newParent is GuildOpenBankBonus )
			newParent = _newParent as GuildOpenBankBonus;
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

[Custom("Social")]
public class GuildProduction : GuildBonus
{
	private UndoRedoDBPtr<GuildProduction> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildProduction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private GuildCycle _cycle;

	[Description( "?????? ?????? 1 ????. ???????? ??? namemap'?" )]
	[NameMapValue]
	public GuildCycle cycle { get { return _cycle; } set { _cycle.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildProduction>(owner);
		_cycle = new GuildCycle( owner );
		___parent.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
	}

	public GuildProduction()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildProduction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildProduction" );
		cycle = source.cycle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildProduction source = _source as GuildProduction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildProduction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildProduction newParent = rawParent == null ? null : rawParent.Get<GuildProduction>();
		if ( newParent == null && _newParent is GuildProduction )
			newParent = _newParent as GuildProduction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cycle.SetParent( newParent == null ? null : newParent._cycle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cycle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cycle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cycle" )
			_cycle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cycle" )
			return _cycle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildStatsBonus : GuildBonus
{
	private UndoRedoDBPtr<GuildStatsBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildStatsBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _MasterPoints;

	[Description( "?????????? ?????? ??????? (inc). ???????? ??? namemap'?" )]
	[NameMapValue]
	public int MasterPoints { get { return _MasterPoints.Get(); } set { _MasterPoints.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildStatsBonus>(owner);
		_MasterPoints = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_MasterPoints.Changed += FireChangedEvent;
	}

	public GuildStatsBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildStatsBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildStatsBonus" );
		MasterPoints = source.MasterPoints;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildStatsBonus source = _source as GuildStatsBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildStatsBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildStatsBonus newParent = rawParent == null ? null : rawParent.Get<GuildStatsBonus>();
		if ( newParent == null && _newParent is GuildStatsBonus )
			newParent = _newParent as GuildStatsBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_MasterPoints.SetParent( newParent == null ? null : newParent._MasterPoints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_MasterPoints.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_MasterPoints.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "MasterPoints" )
			_MasterPoints.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "MasterPoints" )
			return _MasterPoints.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildVisibleBonusesCount : DBResource
{
	private UndoRedoDBPtr<GuildVisibleBonusesCount> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildVisibleBonusesCount> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _defaultBonusCount;
	private UndoRedo<int> _additionalBonusCount;

	[Description( "?????????? ?????? ???????, ???????????? ?? ???????????? ?????? ????? (const)" )]
	public int defaultBonusCount { get { return _defaultBonusCount.Get(); } set { _defaultBonusCount.Set( value ); } }

	public int additionalBonusCount { get { return _additionalBonusCount.Get(); } set { _additionalBonusCount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildVisibleBonusesCount>(owner);
		_defaultBonusCount = new UndoRedo<int>( owner, 0 );
		_additionalBonusCount = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_defaultBonusCount.Changed += FireChangedEvent;
		_additionalBonusCount.Changed += FireChangedEvent;
	}

	public GuildVisibleBonusesCount()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildVisibleBonusesCount source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildVisibleBonusesCount" );
		defaultBonusCount = source.defaultBonusCount;
		additionalBonusCount = source.additionalBonusCount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildVisibleBonusesCount source = _source as GuildVisibleBonusesCount;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildVisibleBonusesCount" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildVisibleBonusesCount newParent = rawParent == null ? null : rawParent.Get<GuildVisibleBonusesCount>();
		if ( newParent == null && _newParent is GuildVisibleBonusesCount )
			newParent = _newParent as GuildVisibleBonusesCount;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_defaultBonusCount.SetParent( newParent == null ? null : newParent._defaultBonusCount );
		_additionalBonusCount.SetParent( newParent == null ? null : newParent._additionalBonusCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultBonusCount.Reset();
		_additionalBonusCount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_defaultBonusCount.IsDerivedFromParent()
			&& _additionalBonusCount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultBonusCount" )
			_defaultBonusCount.Reset();
		else if ( fieldName == "additionalBonusCount" )
			_additionalBonusCount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "defaultBonusCount" )
			return _defaultBonusCount.IsDerivedFromParent();
		if ( fieldName == "additionalBonusCount" )
			return _additionalBonusCount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HeroEnergyRestoreBonus : GuildBonus
{
	private UndoRedoDBPtr<HeroEnergyRestoreBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroEnergyRestoreBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _coef;

	[Description( "?????????? ?????? ?????????? ?????????????? ??????? ????? (const). ???????? ??? namemap'?" )]
	[NameMapValue]
	public float coef { get { return _coef.Get(); } set { _coef.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroEnergyRestoreBonus>(owner);
		_coef = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_coef.Changed += FireChangedEvent;
	}

	public HeroEnergyRestoreBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroEnergyRestoreBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroEnergyRestoreBonus" );
		coef = source.coef;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroEnergyRestoreBonus source = _source as HeroEnergyRestoreBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroEnergyRestoreBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroEnergyRestoreBonus newParent = rawParent == null ? null : rawParent.Get<HeroEnergyRestoreBonus>();
		if ( newParent == null && _newParent is HeroEnergyRestoreBonus )
			newParent = _newParent as HeroEnergyRestoreBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_coef.SetParent( newParent == null ? null : newParent._coef );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_coef.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_coef.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "coef" )
			_coef.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "coef" )
			return _coef.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
