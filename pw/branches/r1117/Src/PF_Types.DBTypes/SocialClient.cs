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
[NoCode]
public enum EBarColor
{
	None = 0,
	Red = 1,
	Green = 2,
	Yellow = 3,
	Blue = 4,
};

[Custom("Social", "DBServer")]
[Flags]
[NoCode]
public enum HeroClassEnum
{
	None = 0,
	Protector = 1,
	Vanguard = 2,
	Executioner = 4,
	Fighter = 8,
	Support = 16,
};

[Custom("Social")]
[NoCode]
public class BonusTalents : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BonusTalents __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<Talent>> _Talents;

	[Description( "Таланты за этот уровень героя" )]
	public libdb.IChangeableList<DBPtr<Talent>> Talents { get { return _Talents; } set { _Talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_Talents.Changed += FireChangedEvent;
	}

	public BonusTalents()
	{
		Initialize( GetOwner() );
	}

	public BonusTalents( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BonusTalents( DBResource owner, BonusTalents source )
		: this(owner, source, true){}

	protected BonusTalents( DBResource owner, BonusTalents source, bool fireEvent )
	{
		_Talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_Talents.Assign( source.Talents );
		_Talents.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BonusTalents source = _source as BonusTalents;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BonusTalents" );
		Talents = source.Talents;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BonusTalents newParent = _newParent as BonusTalents;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Talents.SetParent( newParent == null ? null : newParent._Talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Talents.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Talents.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Talents" )
			_Talents.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Talents" )
			return _Talents.IsDerivedFromParent();
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
[NoCode]
public class CharacterBar : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CharacterBar __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EBarColor> _BarColor;
	private UndoRedo<int> _Count;

	[Description( "Цвет" )]
	public EBarColor BarColor { get { return _BarColor.Get(); } set { _BarColor.Set( value ); } }

	[Description( "Количество кадров" )]
	public int Count { get { return _Count.Get(); } set { _Count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_BarColor = new UndoRedo<EBarColor>( owner, EBarColor.None );
		_Count = new UndoRedo<int>( owner, 0 );
		_BarColor.Changed += FireChangedEvent;
		_Count.Changed += FireChangedEvent;
	}

	public CharacterBar()
	{
		Initialize( GetOwner() );
	}

	public CharacterBar( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CharacterBar( DBResource owner, CharacterBar source )
		: this(owner, source, true){}

	protected CharacterBar( DBResource owner, CharacterBar source, bool fireEvent )
	{
		_BarColor = new UndoRedo<EBarColor>( owner, source.BarColor );
		_Count = new UndoRedo<int>( owner, source.Count );
		_BarColor.Changed += FireChangedEvent;
		_Count.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CharacterBar source = _source as CharacterBar;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CharacterBar" );
		BarColor = source.BarColor;
		Count = source.Count;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CharacterBar newParent = _newParent as CharacterBar;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_BarColor.SetParent( newParent == null ? null : newParent._BarColor );
		_Count.SetParent( newParent == null ? null : newParent._Count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_BarColor.Reset();
		_Count.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_BarColor.IsDerivedFromParent()
			&& _Count.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "BarColor" )
			_BarColor.Reset();
		else if ( fieldName == "Count" )
			_Count.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "BarColor" )
			return _BarColor.IsDerivedFromParent();
		if ( fieldName == "Count" )
			return _Count.IsDerivedFromParent();
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
[NoCode]
public class CharacterBarSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CharacterBarSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private CharacterBar _Attak;
	private CharacterBar _Defence;
	private CharacterBar _Talents;
	private CharacterBar _Complexity;

	[Description( "Атака" )]
	public CharacterBar Attak { get { return _Attak; } set { _Attak.Assign( value ); } }

	[Description( "Защита" )]
	public CharacterBar Defence { get { return _Defence; } set { _Defence.Assign( value ); } }

	[Description( "Таланты" )]
	public CharacterBar Talents { get { return _Talents; } set { _Talents.Assign( value ); } }

	[Description( "Сложность" )]
	public CharacterBar Complexity { get { return _Complexity; } set { _Complexity.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Attak = new CharacterBar( owner );
		_Defence = new CharacterBar( owner );
		_Talents = new CharacterBar( owner );
		_Complexity = new CharacterBar( owner );
		_Attak.Changed += FireChangedEvent;
		_Defence.Changed += FireChangedEvent;
		_Talents.Changed += FireChangedEvent;
		_Complexity.Changed += FireChangedEvent;
	}

	public CharacterBarSettings()
	{
		Initialize( GetOwner() );
	}

	public CharacterBarSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CharacterBarSettings( DBResource owner, CharacterBarSettings source )
		: this(owner, source, true){}

	protected CharacterBarSettings( DBResource owner, CharacterBarSettings source, bool fireEvent )
	{
		_Attak = new CharacterBar( owner, source.Attak );
		_Defence = new CharacterBar( owner, source.Defence );
		_Talents = new CharacterBar( owner, source.Talents );
		_Complexity = new CharacterBar( owner, source.Complexity );
		_Attak.Changed += FireChangedEvent;
		_Defence.Changed += FireChangedEvent;
		_Talents.Changed += FireChangedEvent;
		_Complexity.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CharacterBarSettings source = _source as CharacterBarSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CharacterBarSettings" );
		Attak = source.Attak;
		Defence = source.Defence;
		Talents = source.Talents;
		Complexity = source.Complexity;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CharacterBarSettings newParent = _newParent as CharacterBarSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Attak.SetParent( newParent == null ? null : newParent._Attak );
		_Defence.SetParent( newParent == null ? null : newParent._Defence );
		_Talents.SetParent( newParent == null ? null : newParent._Talents );
		_Complexity.SetParent( newParent == null ? null : newParent._Complexity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Attak.Reset();
		_Defence.Reset();
		_Talents.Reset();
		_Complexity.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Attak.IsDerivedFromParent()
			&& _Defence.IsDerivedFromParent()
			&& _Talents.IsDerivedFromParent()
			&& _Complexity.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Attak" )
			_Attak.Reset();
		else if ( fieldName == "Defence" )
			_Defence.Reset();
		else if ( fieldName == "Talents" )
			_Talents.Reset();
		else if ( fieldName == "Complexity" )
			_Complexity.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Attak" )
			return _Attak.IsDerivedFromParent();
		if ( fieldName == "Defence" )
			return _Defence.IsDerivedFromParent();
		if ( fieldName == "Talents" )
			return _Talents.IsDerivedFromParent();
		if ( fieldName == "Complexity" )
			return _Complexity.IsDerivedFromParent();
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
[NoCode]
public class CurrencyItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CurrencyItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _Id;
	private UndoRedo<int> _Value;

	[NameMapValue]
	public string Id { get { return _Id.Get(); } set { _Id.Set( value ); } }

	[NameMapValue]
	public int Value { get { return _Value.Get(); } set { _Value.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Id = new UndoRedo<string>( owner, string.Empty );
		_Value = new UndoRedo<int>( owner, 0 );
		_Id.Changed += FireChangedEvent;
		_Value.Changed += FireChangedEvent;
	}

	public CurrencyItem()
	{
		Initialize( GetOwner() );
	}

	public CurrencyItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CurrencyItem( DBResource owner, CurrencyItem source )
		: this(owner, source, true){}

	protected CurrencyItem( DBResource owner, CurrencyItem source, bool fireEvent )
	{
		_Id = new UndoRedo<string>( owner, source.Id );
		_Value = new UndoRedo<int>( owner, source.Value );
		_Id.Changed += FireChangedEvent;
		_Value.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CurrencyItem source = _source as CurrencyItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CurrencyItem" );
		Id = source.Id;
		Value = source.Value;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CurrencyItem newParent = _newParent as CurrencyItem;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Id.SetParent( newParent == null ? null : newParent._Id );
		_Value.SetParent( newParent == null ? null : newParent._Value );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Id.Reset();
		_Value.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Id.IsDerivedFromParent()
			&& _Value.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Id" )
			_Id.Reset();
		else if ( fieldName == "Value" )
			_Value.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Id" )
			return _Id.IsDerivedFromParent();
		if ( fieldName == "Value" )
			return _Value.IsDerivedFromParent();
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
[NoCode]
public class EnduranceRegenTime : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EnduranceRegenTime __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedo<int> _enduranceRegenTime;

	[Description( "Уровень героя ( начинается с 0 )" )]
	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	[Description( "Скорость в секундах восстановления до MaxEndurance" )]
	public int enduranceRegenTime { get { return _enduranceRegenTime.Get(); } set { _enduranceRegenTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_enduranceRegenTime = new UndoRedo<int>( owner, 86400 );
		_level.Changed += FireChangedEvent;
		_enduranceRegenTime.Changed += FireChangedEvent;
	}

	public EnduranceRegenTime()
	{
		Initialize( GetOwner() );
	}

	public EnduranceRegenTime( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EnduranceRegenTime( DBResource owner, EnduranceRegenTime source )
		: this(owner, source, true){}

	protected EnduranceRegenTime( DBResource owner, EnduranceRegenTime source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_enduranceRegenTime = new UndoRedo<int>( owner, source.enduranceRegenTime );
		_level.Changed += FireChangedEvent;
		_enduranceRegenTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EnduranceRegenTime source = _source as EnduranceRegenTime;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EnduranceRegenTime" );
		level = source.level;
		enduranceRegenTime = source.enduranceRegenTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EnduranceRegenTime newParent = _newParent as EnduranceRegenTime;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_enduranceRegenTime.SetParent( newParent == null ? null : newParent._enduranceRegenTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_enduranceRegenTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _enduranceRegenTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
		else if ( fieldName == "enduranceRegenTime" )
			_enduranceRegenTime.Reset();
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
		if ( fieldName == "enduranceRegenTime" )
			return _enduranceRegenTime.IsDerivedFromParent();
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
[NoCode]
public class HeroClassStatPair : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroClassStatPair __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<HeroClassEnum> _Class;
	private UndoRedo<int> _Bonus;

	public HeroClassEnum Class { get { return _Class.Get(); } set { _Class.Set( value ); } }

	public int Bonus { get { return _Bonus.Get(); } set { _Bonus.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Class = new UndoRedo<HeroClassEnum>( owner, HeroClassEnum.None );
		_Bonus = new UndoRedo<int>( owner, 0 );
		_Class.Changed += FireChangedEvent;
		_Bonus.Changed += FireChangedEvent;
	}

	public HeroClassStatPair()
	{
		Initialize( GetOwner() );
	}

	public HeroClassStatPair( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroClassStatPair( DBResource owner, HeroClassStatPair source )
		: this(owner, source, true){}

	protected HeroClassStatPair( DBResource owner, HeroClassStatPair source, bool fireEvent )
	{
		_Class = new UndoRedo<HeroClassEnum>( owner, source.Class );
		_Bonus = new UndoRedo<int>( owner, source.Bonus );
		_Class.Changed += FireChangedEvent;
		_Bonus.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroClassStatPair source = _source as HeroClassStatPair;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroClassStatPair" );
		Class = source.Class;
		Bonus = source.Bonus;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroClassStatPair newParent = _newParent as HeroClassStatPair;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Class.SetParent( newParent == null ? null : newParent._Class );
		_Bonus.SetParent( newParent == null ? null : newParent._Bonus );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Class.Reset();
		_Bonus.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Class.IsDerivedFromParent()
			&& _Bonus.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Class" )
			_Class.Reset();
		else if ( fieldName == "Bonus" )
			_Bonus.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Class" )
			return _Class.IsDerivedFromParent();
		if ( fieldName == "Bonus" )
			return _Bonus.IsDerivedFromParent();
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
[NoCode]
public class HeroClassStatBonus : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroClassStatBonus __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<HeroClassStatPair> _Bonuses;

	public libdb.IChangeableList<HeroClassStatPair> Bonuses { get { return _Bonuses; } set { _Bonuses.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Bonuses = new UndoRedoAssignableList<HeroClassStatPair>( owner );
		_Bonuses.Changed += FireChangedEvent;
	}

	public HeroClassStatBonus()
	{
		Initialize( GetOwner() );
	}

	public HeroClassStatBonus( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroClassStatBonus( DBResource owner, HeroClassStatBonus source )
		: this(owner, source, true){}

	protected HeroClassStatBonus( DBResource owner, HeroClassStatBonus source, bool fireEvent )
	{
		_Bonuses = new UndoRedoAssignableList<HeroClassStatPair>( owner );
		_Bonuses.Assign( source.Bonuses );
		_Bonuses.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroClassStatBonus source = _source as HeroClassStatBonus;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroClassStatBonus" );
		Bonuses = source.Bonuses;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroClassStatBonus newParent = _newParent as HeroClassStatBonus;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Bonuses.SetParent( newParent == null ? null : newParent._Bonuses );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Bonuses.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Bonuses.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Bonuses" )
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

[Custom("Social")]
[NoCode]
public class ResourcesTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ResourcesTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _Resource1;
	private UndoRedo<int> _Resource2;
	private UndoRedo<int> _Resource3;
	private UndoRedo<int> _Resource1_Rare;
	private UndoRedo<int> _Resource2_Rare;
	private UndoRedo<int> _Resource3_Rare;
	private UndoRedo<int> _Perl;
	private UndoRedo<int> _RedPerl;
	private UndoRedo<int> _Silver;
	private UndoRedo<int> _Gold;
	private UndoRedo<int> _Population;
	private UndoRedo<int> _CWPoints_Clan;
	private UndoRedo<int> _CWPoints_Player;
	private UndoRedo<int> _Shard;
	private UndoRedoAssignableList<CurrencyItem> _Currencies;

	[NameMapValue]
	public int Resource1 { get { return _Resource1.Get(); } set { _Resource1.Set( value ); } }

	[NameMapValue]
	public int Resource2 { get { return _Resource2.Get(); } set { _Resource2.Set( value ); } }

	[NameMapValue]
	public int Resource3 { get { return _Resource3.Get(); } set { _Resource3.Set( value ); } }

	public int Resource1_Rare { get { return _Resource1_Rare.Get(); } set { _Resource1_Rare.Set( value ); } }

	public int Resource2_Rare { get { return _Resource2_Rare.Get(); } set { _Resource2_Rare.Set( value ); } }

	public int Resource3_Rare { get { return _Resource3_Rare.Get(); } set { _Resource3_Rare.Set( value ); } }

	[NameMapValue]
	public int Perl { get { return _Perl.Get(); } set { _Perl.Set( value ); } }

	[NameMapValue]
	public int RedPerl { get { return _RedPerl.Get(); } set { _RedPerl.Set( value ); } }

	[NameMapValue]
	public int Silver { get { return _Silver.Get(); } set { _Silver.Set( value ); } }

	[NameMapValue]
	public int Gold { get { return _Gold.Get(); } set { _Gold.Set( value ); } }

	[NameMapValue]
	public int Population { get { return _Population.Get(); } set { _Population.Set( value ); } }

	[NameMapValue]
	public int CWPoints_Clan { get { return _CWPoints_Clan.Get(); } set { _CWPoints_Clan.Set( value ); } }

	[NameMapValue]
	public int CWPoints_Player { get { return _CWPoints_Player.Get(); } set { _CWPoints_Player.Set( value ); } }

	[NameMapValue]
	public int Shard { get { return _Shard.Get(); } set { _Shard.Set( value ); } }

	[NameMapValue]
	public libdb.IChangeableList<CurrencyItem> Currencies { get { return _Currencies; } set { _Currencies.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Resource1 = new UndoRedo<int>( owner, 0 );
		_Resource2 = new UndoRedo<int>( owner, 0 );
		_Resource3 = new UndoRedo<int>( owner, 0 );
		_Resource1_Rare = new UndoRedo<int>( owner, 0 );
		_Resource2_Rare = new UndoRedo<int>( owner, 0 );
		_Resource3_Rare = new UndoRedo<int>( owner, 0 );
		_Perl = new UndoRedo<int>( owner, 0 );
		_RedPerl = new UndoRedo<int>( owner, 0 );
		_Silver = new UndoRedo<int>( owner, 0 );
		_Gold = new UndoRedo<int>( owner, 0 );
		_Population = new UndoRedo<int>( owner, 0 );
		_CWPoints_Clan = new UndoRedo<int>( owner, 0 );
		_CWPoints_Player = new UndoRedo<int>( owner, 0 );
		_Shard = new UndoRedo<int>( owner, 0 );
		_Currencies = new UndoRedoAssignableList<CurrencyItem>( owner );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Resource1_Rare.Changed += FireChangedEvent;
		_Resource2_Rare.Changed += FireChangedEvent;
		_Resource3_Rare.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
		_RedPerl.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Gold.Changed += FireChangedEvent;
		_Population.Changed += FireChangedEvent;
		_CWPoints_Clan.Changed += FireChangedEvent;
		_CWPoints_Player.Changed += FireChangedEvent;
		_Shard.Changed += FireChangedEvent;
		_Currencies.Changed += FireChangedEvent;
	}

	public ResourcesTable()
	{
		Initialize( GetOwner() );
	}

	public ResourcesTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ResourcesTable( DBResource owner, ResourcesTable source )
		: this(owner, source, true){}

	protected ResourcesTable( DBResource owner, ResourcesTable source, bool fireEvent )
	{
		_Resource1 = new UndoRedo<int>( owner, source.Resource1 );
		_Resource2 = new UndoRedo<int>( owner, source.Resource2 );
		_Resource3 = new UndoRedo<int>( owner, source.Resource3 );
		_Resource1_Rare = new UndoRedo<int>( owner, source.Resource1_Rare );
		_Resource2_Rare = new UndoRedo<int>( owner, source.Resource2_Rare );
		_Resource3_Rare = new UndoRedo<int>( owner, source.Resource3_Rare );
		_Perl = new UndoRedo<int>( owner, source.Perl );
		_RedPerl = new UndoRedo<int>( owner, source.RedPerl );
		_Silver = new UndoRedo<int>( owner, source.Silver );
		_Gold = new UndoRedo<int>( owner, source.Gold );
		_Population = new UndoRedo<int>( owner, source.Population );
		_CWPoints_Clan = new UndoRedo<int>( owner, source.CWPoints_Clan );
		_CWPoints_Player = new UndoRedo<int>( owner, source.CWPoints_Player );
		_Shard = new UndoRedo<int>( owner, source.Shard );
		_Currencies = new UndoRedoAssignableList<CurrencyItem>( owner );
		_Currencies.Assign( source.Currencies );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Resource1_Rare.Changed += FireChangedEvent;
		_Resource2_Rare.Changed += FireChangedEvent;
		_Resource3_Rare.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
		_RedPerl.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Gold.Changed += FireChangedEvent;
		_Population.Changed += FireChangedEvent;
		_CWPoints_Clan.Changed += FireChangedEvent;
		_CWPoints_Player.Changed += FireChangedEvent;
		_Shard.Changed += FireChangedEvent;
		_Currencies.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ResourcesTable source = _source as ResourcesTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourcesTable" );
		Resource1 = source.Resource1;
		Resource2 = source.Resource2;
		Resource3 = source.Resource3;
		Resource1_Rare = source.Resource1_Rare;
		Resource2_Rare = source.Resource2_Rare;
		Resource3_Rare = source.Resource3_Rare;
		Perl = source.Perl;
		RedPerl = source.RedPerl;
		Silver = source.Silver;
		Gold = source.Gold;
		Population = source.Population;
		CWPoints_Clan = source.CWPoints_Clan;
		CWPoints_Player = source.CWPoints_Player;
		Shard = source.Shard;
		Currencies = source.Currencies;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ResourcesTable newParent = _newParent as ResourcesTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Resource1.SetParent( newParent == null ? null : newParent._Resource1 );
		_Resource2.SetParent( newParent == null ? null : newParent._Resource2 );
		_Resource3.SetParent( newParent == null ? null : newParent._Resource3 );
		_Resource1_Rare.SetParent( newParent == null ? null : newParent._Resource1_Rare );
		_Resource2_Rare.SetParent( newParent == null ? null : newParent._Resource2_Rare );
		_Resource3_Rare.SetParent( newParent == null ? null : newParent._Resource3_Rare );
		_Perl.SetParent( newParent == null ? null : newParent._Perl );
		_RedPerl.SetParent( newParent == null ? null : newParent._RedPerl );
		_Silver.SetParent( newParent == null ? null : newParent._Silver );
		_Gold.SetParent( newParent == null ? null : newParent._Gold );
		_Population.SetParent( newParent == null ? null : newParent._Population );
		_CWPoints_Clan.SetParent( newParent == null ? null : newParent._CWPoints_Clan );
		_CWPoints_Player.SetParent( newParent == null ? null : newParent._CWPoints_Player );
		_Shard.SetParent( newParent == null ? null : newParent._Shard );
		_Currencies.SetParent( newParent == null ? null : newParent._Currencies );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Resource1.Reset();
		_Resource2.Reset();
		_Resource3.Reset();
		_Resource1_Rare.Reset();
		_Resource2_Rare.Reset();
		_Resource3_Rare.Reset();
		_Perl.Reset();
		_RedPerl.Reset();
		_Silver.Reset();
		_Gold.Reset();
		_Population.Reset();
		_CWPoints_Clan.Reset();
		_CWPoints_Player.Reset();
		_Shard.Reset();
		_Currencies.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Resource1.IsDerivedFromParent()
			&& _Resource2.IsDerivedFromParent()
			&& _Resource3.IsDerivedFromParent()
			&& _Resource1_Rare.IsDerivedFromParent()
			&& _Resource2_Rare.IsDerivedFromParent()
			&& _Resource3_Rare.IsDerivedFromParent()
			&& _Perl.IsDerivedFromParent()
			&& _RedPerl.IsDerivedFromParent()
			&& _Silver.IsDerivedFromParent()
			&& _Gold.IsDerivedFromParent()
			&& _Population.IsDerivedFromParent()
			&& _CWPoints_Clan.IsDerivedFromParent()
			&& _CWPoints_Player.IsDerivedFromParent()
			&& _Shard.IsDerivedFromParent()
			&& _Currencies.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Resource1" )
			_Resource1.Reset();
		else if ( fieldName == "Resource2" )
			_Resource2.Reset();
		else if ( fieldName == "Resource3" )
			_Resource3.Reset();
		else if ( fieldName == "Resource1_Rare" )
			_Resource1_Rare.Reset();
		else if ( fieldName == "Resource2_Rare" )
			_Resource2_Rare.Reset();
		else if ( fieldName == "Resource3_Rare" )
			_Resource3_Rare.Reset();
		else if ( fieldName == "Perl" )
			_Perl.Reset();
		else if ( fieldName == "RedPerl" )
			_RedPerl.Reset();
		else if ( fieldName == "Silver" )
			_Silver.Reset();
		else if ( fieldName == "Gold" )
			_Gold.Reset();
		else if ( fieldName == "Population" )
			_Population.Reset();
		else if ( fieldName == "CWPoints_Clan" )
			_CWPoints_Clan.Reset();
		else if ( fieldName == "CWPoints_Player" )
			_CWPoints_Player.Reset();
		else if ( fieldName == "Shard" )
			_Shard.Reset();
		else if ( fieldName == "Currencies" )
			_Currencies.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Resource1" )
			return _Resource1.IsDerivedFromParent();
		if ( fieldName == "Resource2" )
			return _Resource2.IsDerivedFromParent();
		if ( fieldName == "Resource3" )
			return _Resource3.IsDerivedFromParent();
		if ( fieldName == "Resource1_Rare" )
			return _Resource1_Rare.IsDerivedFromParent();
		if ( fieldName == "Resource2_Rare" )
			return _Resource2_Rare.IsDerivedFromParent();
		if ( fieldName == "Resource3_Rare" )
			return _Resource3_Rare.IsDerivedFromParent();
		if ( fieldName == "Perl" )
			return _Perl.IsDerivedFromParent();
		if ( fieldName == "RedPerl" )
			return _RedPerl.IsDerivedFromParent();
		if ( fieldName == "Silver" )
			return _Silver.IsDerivedFromParent();
		if ( fieldName == "Gold" )
			return _Gold.IsDerivedFromParent();
		if ( fieldName == "Population" )
			return _Population.IsDerivedFromParent();
		if ( fieldName == "CWPoints_Clan" )
			return _CWPoints_Clan.IsDerivedFromParent();
		if ( fieldName == "CWPoints_Player" )
			return _CWPoints_Player.IsDerivedFromParent();
		if ( fieldName == "Shard" )
			return _Shard.IsDerivedFromParent();
		if ( fieldName == "Currencies" )
			return _Currencies.IsDerivedFromParent();
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
[NoCode]
public class ResourcesCoefTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ResourcesCoefTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _Resource1;
	private UndoRedo<float> _Resource2;
	private UndoRedo<float> _Resource3;
	private UndoRedo<float> _Resource1_Rare;
	private UndoRedo<float> _Resource2_Rare;
	private UndoRedo<float> _Resource3_Rare;
	private UndoRedo<float> _Perl;
	private UndoRedo<float> _RedPerl;
	private UndoRedo<float> _Silver;
	private UndoRedo<float> _Gold;
	private UndoRedo<float> _Population;
	private UndoRedo<float> _CWPoints_Clan;
	private UndoRedo<float> _CWPoints_Player;
	private UndoRedo<float> _Shard;
	private UndoRedo<float> _Currencies;

	public float Resource1 { get { return _Resource1.Get(); } set { _Resource1.Set( value ); } }

	public float Resource2 { get { return _Resource2.Get(); } set { _Resource2.Set( value ); } }

	public float Resource3 { get { return _Resource3.Get(); } set { _Resource3.Set( value ); } }

	public float Resource1_Rare { get { return _Resource1_Rare.Get(); } set { _Resource1_Rare.Set( value ); } }

	public float Resource2_Rare { get { return _Resource2_Rare.Get(); } set { _Resource2_Rare.Set( value ); } }

	public float Resource3_Rare { get { return _Resource3_Rare.Get(); } set { _Resource3_Rare.Set( value ); } }

	public float Perl { get { return _Perl.Get(); } set { _Perl.Set( value ); } }

	public float RedPerl { get { return _RedPerl.Get(); } set { _RedPerl.Set( value ); } }

	public float Silver { get { return _Silver.Get(); } set { _Silver.Set( value ); } }

	public float Gold { get { return _Gold.Get(); } set { _Gold.Set( value ); } }

	public float Population { get { return _Population.Get(); } set { _Population.Set( value ); } }

	public float CWPoints_Clan { get { return _CWPoints_Clan.Get(); } set { _CWPoints_Clan.Set( value ); } }

	public float CWPoints_Player { get { return _CWPoints_Player.Get(); } set { _CWPoints_Player.Set( value ); } }

	public float Shard { get { return _Shard.Get(); } set { _Shard.Set( value ); } }

	public float Currencies { get { return _Currencies.Get(); } set { _Currencies.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Resource1 = new UndoRedo<float>( owner, 0.0f );
		_Resource2 = new UndoRedo<float>( owner, 0.0f );
		_Resource3 = new UndoRedo<float>( owner, 0.0f );
		_Resource1_Rare = new UndoRedo<float>( owner, 0.0f );
		_Resource2_Rare = new UndoRedo<float>( owner, 0.0f );
		_Resource3_Rare = new UndoRedo<float>( owner, 0.0f );
		_Perl = new UndoRedo<float>( owner, 0.0f );
		_RedPerl = new UndoRedo<float>( owner, 0.0f );
		_Silver = new UndoRedo<float>( owner, 0.0f );
		_Gold = new UndoRedo<float>( owner, 0.0f );
		_Population = new UndoRedo<float>( owner, 0.0f );
		_CWPoints_Clan = new UndoRedo<float>( owner, 0.0f );
		_CWPoints_Player = new UndoRedo<float>( owner, 0.0f );
		_Shard = new UndoRedo<float>( owner, 0.0f );
		_Currencies = new UndoRedo<float>( owner, 0.0f );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Resource1_Rare.Changed += FireChangedEvent;
		_Resource2_Rare.Changed += FireChangedEvent;
		_Resource3_Rare.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
		_RedPerl.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Gold.Changed += FireChangedEvent;
		_Population.Changed += FireChangedEvent;
		_CWPoints_Clan.Changed += FireChangedEvent;
		_CWPoints_Player.Changed += FireChangedEvent;
		_Shard.Changed += FireChangedEvent;
		_Currencies.Changed += FireChangedEvent;
	}

	public ResourcesCoefTable()
	{
		Initialize( GetOwner() );
	}

	public ResourcesCoefTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ResourcesCoefTable( DBResource owner, ResourcesCoefTable source )
		: this(owner, source, true){}

	protected ResourcesCoefTable( DBResource owner, ResourcesCoefTable source, bool fireEvent )
	{
		_Resource1 = new UndoRedo<float>( owner, source.Resource1 );
		_Resource2 = new UndoRedo<float>( owner, source.Resource2 );
		_Resource3 = new UndoRedo<float>( owner, source.Resource3 );
		_Resource1_Rare = new UndoRedo<float>( owner, source.Resource1_Rare );
		_Resource2_Rare = new UndoRedo<float>( owner, source.Resource2_Rare );
		_Resource3_Rare = new UndoRedo<float>( owner, source.Resource3_Rare );
		_Perl = new UndoRedo<float>( owner, source.Perl );
		_RedPerl = new UndoRedo<float>( owner, source.RedPerl );
		_Silver = new UndoRedo<float>( owner, source.Silver );
		_Gold = new UndoRedo<float>( owner, source.Gold );
		_Population = new UndoRedo<float>( owner, source.Population );
		_CWPoints_Clan = new UndoRedo<float>( owner, source.CWPoints_Clan );
		_CWPoints_Player = new UndoRedo<float>( owner, source.CWPoints_Player );
		_Shard = new UndoRedo<float>( owner, source.Shard );
		_Currencies = new UndoRedo<float>( owner, source.Currencies );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Resource1_Rare.Changed += FireChangedEvent;
		_Resource2_Rare.Changed += FireChangedEvent;
		_Resource3_Rare.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
		_RedPerl.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Gold.Changed += FireChangedEvent;
		_Population.Changed += FireChangedEvent;
		_CWPoints_Clan.Changed += FireChangedEvent;
		_CWPoints_Player.Changed += FireChangedEvent;
		_Shard.Changed += FireChangedEvent;
		_Currencies.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ResourcesCoefTable source = _source as ResourcesCoefTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourcesCoefTable" );
		Resource1 = source.Resource1;
		Resource2 = source.Resource2;
		Resource3 = source.Resource3;
		Resource1_Rare = source.Resource1_Rare;
		Resource2_Rare = source.Resource2_Rare;
		Resource3_Rare = source.Resource3_Rare;
		Perl = source.Perl;
		RedPerl = source.RedPerl;
		Silver = source.Silver;
		Gold = source.Gold;
		Population = source.Population;
		CWPoints_Clan = source.CWPoints_Clan;
		CWPoints_Player = source.CWPoints_Player;
		Shard = source.Shard;
		Currencies = source.Currencies;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ResourcesCoefTable newParent = _newParent as ResourcesCoefTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Resource1.SetParent( newParent == null ? null : newParent._Resource1 );
		_Resource2.SetParent( newParent == null ? null : newParent._Resource2 );
		_Resource3.SetParent( newParent == null ? null : newParent._Resource3 );
		_Resource1_Rare.SetParent( newParent == null ? null : newParent._Resource1_Rare );
		_Resource2_Rare.SetParent( newParent == null ? null : newParent._Resource2_Rare );
		_Resource3_Rare.SetParent( newParent == null ? null : newParent._Resource3_Rare );
		_Perl.SetParent( newParent == null ? null : newParent._Perl );
		_RedPerl.SetParent( newParent == null ? null : newParent._RedPerl );
		_Silver.SetParent( newParent == null ? null : newParent._Silver );
		_Gold.SetParent( newParent == null ? null : newParent._Gold );
		_Population.SetParent( newParent == null ? null : newParent._Population );
		_CWPoints_Clan.SetParent( newParent == null ? null : newParent._CWPoints_Clan );
		_CWPoints_Player.SetParent( newParent == null ? null : newParent._CWPoints_Player );
		_Shard.SetParent( newParent == null ? null : newParent._Shard );
		_Currencies.SetParent( newParent == null ? null : newParent._Currencies );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Resource1.Reset();
		_Resource2.Reset();
		_Resource3.Reset();
		_Resource1_Rare.Reset();
		_Resource2_Rare.Reset();
		_Resource3_Rare.Reset();
		_Perl.Reset();
		_RedPerl.Reset();
		_Silver.Reset();
		_Gold.Reset();
		_Population.Reset();
		_CWPoints_Clan.Reset();
		_CWPoints_Player.Reset();
		_Shard.Reset();
		_Currencies.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Resource1.IsDerivedFromParent()
			&& _Resource2.IsDerivedFromParent()
			&& _Resource3.IsDerivedFromParent()
			&& _Resource1_Rare.IsDerivedFromParent()
			&& _Resource2_Rare.IsDerivedFromParent()
			&& _Resource3_Rare.IsDerivedFromParent()
			&& _Perl.IsDerivedFromParent()
			&& _RedPerl.IsDerivedFromParent()
			&& _Silver.IsDerivedFromParent()
			&& _Gold.IsDerivedFromParent()
			&& _Population.IsDerivedFromParent()
			&& _CWPoints_Clan.IsDerivedFromParent()
			&& _CWPoints_Player.IsDerivedFromParent()
			&& _Shard.IsDerivedFromParent()
			&& _Currencies.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Resource1" )
			_Resource1.Reset();
		else if ( fieldName == "Resource2" )
			_Resource2.Reset();
		else if ( fieldName == "Resource3" )
			_Resource3.Reset();
		else if ( fieldName == "Resource1_Rare" )
			_Resource1_Rare.Reset();
		else if ( fieldName == "Resource2_Rare" )
			_Resource2_Rare.Reset();
		else if ( fieldName == "Resource3_Rare" )
			_Resource3_Rare.Reset();
		else if ( fieldName == "Perl" )
			_Perl.Reset();
		else if ( fieldName == "RedPerl" )
			_RedPerl.Reset();
		else if ( fieldName == "Silver" )
			_Silver.Reset();
		else if ( fieldName == "Gold" )
			_Gold.Reset();
		else if ( fieldName == "Population" )
			_Population.Reset();
		else if ( fieldName == "CWPoints_Clan" )
			_CWPoints_Clan.Reset();
		else if ( fieldName == "CWPoints_Player" )
			_CWPoints_Player.Reset();
		else if ( fieldName == "Shard" )
			_Shard.Reset();
		else if ( fieldName == "Currencies" )
			_Currencies.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Resource1" )
			return _Resource1.IsDerivedFromParent();
		if ( fieldName == "Resource2" )
			return _Resource2.IsDerivedFromParent();
		if ( fieldName == "Resource3" )
			return _Resource3.IsDerivedFromParent();
		if ( fieldName == "Resource1_Rare" )
			return _Resource1_Rare.IsDerivedFromParent();
		if ( fieldName == "Resource2_Rare" )
			return _Resource2_Rare.IsDerivedFromParent();
		if ( fieldName == "Resource3_Rare" )
			return _Resource3_Rare.IsDerivedFromParent();
		if ( fieldName == "Perl" )
			return _Perl.IsDerivedFromParent();
		if ( fieldName == "RedPerl" )
			return _RedPerl.IsDerivedFromParent();
		if ( fieldName == "Silver" )
			return _Silver.IsDerivedFromParent();
		if ( fieldName == "Gold" )
			return _Gold.IsDerivedFromParent();
		if ( fieldName == "Population" )
			return _Population.IsDerivedFromParent();
		if ( fieldName == "CWPoints_Clan" )
			return _CWPoints_Clan.IsDerivedFromParent();
		if ( fieldName == "CWPoints_Player" )
			return _CWPoints_Player.IsDerivedFromParent();
		if ( fieldName == "Shard" )
			return _Shard.IsDerivedFromParent();
		if ( fieldName == "Currencies" )
			return _Currencies.IsDerivedFromParent();
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
[NoCode]
public class LobbyHeroData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LobbyHeroData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _heroAskSoundA;
	private UndoRedo<string> _heroAskSoundB;
	private UndoRedoDBPtr<Texture> _heroRenderA;
	private TextRef _heroDescriptionA;
	private TextRef _heroBiographyA;
	private UndoRedoDBPtr<Texture> _heroRenderB;
	private TextRef _heroDescriptionB;
	private TextRef _heroBiographyB;
	private UndoRedo<bool> _IsHeroHiredByDefaultMale;
	private UndoRedo<bool> _IsHeroHiredByDefaultFemale;
	private UndoRedoDBPtr<HeroStatsTable> _Stats;
	private UndoRedo<HeroClassEnum> _Classes;
	private ResourcesTable _CostMale;
	private ResourcesTable _CostFemale;
	private ResourcesTable _ProductionResultIncrement;
	private UndoRedo<int> _LevelRequireFemale;
	private UndoRedo<int> _LevelRequireMale;
	private UndoRedo<int> _Version;
	private UndoRedoDBPtr<HeroFameIncrement> _FameIncrement;
	private UndoRedoList<string> _RequiredHeroes;
	private UndoRedoDBPtr<BonusTalentsForLevel> _BonusTalentsForLevel;
	private CharacterBarSettings _CharacterBarSettings;

	[Description( "Path to sound, played on hero click in Doct castle. Relative path from Resources/Sound/, without file extension." )]
	public string heroAskSoundA { get { return _heroAskSoundA.Get(); } set { _heroAskSoundA.Set( value ); } }

	[Description( "Path to sound, played on hero click in Adornian castle. Relative path from Resources/Sound/, without file extension." )]
	public string heroAskSoundB { get { return _heroAskSoundB.Get(); } set { _heroAskSoundB.Set( value ); } }

	[Description( "Hero UI render for first faction" )]
	public DBPtr<Texture> heroRenderA { get { return _heroRenderA.Get(); } set { _heroRenderA.Set( value ); } }

	[Description( "Hero UI description for first faction" )]
	public TextRef heroDescriptionA { get { return _heroDescriptionA; } set { _heroDescriptionA.Assign( value ); } }

	[Description( "Hero UI biography for first faction" )]
	public TextRef heroBiographyA { get { return _heroBiographyA; } set { _heroBiographyA.Assign( value ); } }

	[Description( "Hero UI render for second faction" )]
	public DBPtr<Texture> heroRenderB { get { return _heroRenderB.Get(); } set { _heroRenderB.Set( value ); } }

	[Description( "Hero UI description for second faction" )]
	public TextRef heroDescriptionB { get { return _heroDescriptionB; } set { _heroDescriptionB.Assign( value ); } }

	[Description( "Hero UI biography for second faction" )]
	public TextRef heroBiographyB { get { return _heroBiographyB; } set { _heroBiographyB.Assign( value ); } }

	[Description( "Is hero availabe by default. Using for male players." )]
	public bool IsHeroHiredByDefaultMale { get { return _IsHeroHiredByDefaultMale.Get(); } set { _IsHeroHiredByDefaultMale.Set( value ); } }

	[Description( "Is hero availabe by default. Using for female players." )]
	public bool IsHeroHiredByDefaultFemale { get { return _IsHeroHiredByDefaultFemale.Get(); } set { _IsHeroHiredByDefaultFemale.Set( value ); } }

	[Description( "Hero stats for Social client." )]
	public DBPtr<HeroStatsTable> Stats { get { return _Stats.Get(); } set { _Stats.Set( value ); } }

	[Description( "Hero classes" )]
	public HeroClassEnum Classes { get { return _Classes.Get(); } set { _Classes.Set( value ); } }

	[Description( "Hero employment cost. Using for male players." )]
	public ResourcesTable CostMale { get { return _CostMale; } set { _CostMale.Assign( value ); } }

	[Description( "Hero employment cost. Using for female players." )]
	public ResourcesTable CostFemale { get { return _CostFemale; } set { _CostFemale.Assign( value ); } }

	[Description( "Production cycle resources delta" )]
	public ResourcesTable ProductionResultIncrement { get { return _ProductionResultIncrement; } set { _ProductionResultIncrement.Assign( value ); } }

	[Description( "Lord's level required for hero employment. Using for female players." )]
	public int LevelRequireFemale { get { return _LevelRequireFemale.Get(); } set { _LevelRequireFemale.Set( value ); } }

	[Description( "Lord's level required for hero employment. Using for male players." )]
	public int LevelRequireMale { get { return _LevelRequireMale.Get(); } set { _LevelRequireMale.Set( value ); } }

	[Browsable( false )]
	[Description( "Used for TalentSet versioning" )]
	public int Version { get { return _Version.Get(); } set { _Version.Set( value ); } }

	[Description( "Fame increment for hero levels. First level using for employment case." )]
	public DBPtr<HeroFameIncrement> FameIncrement { get { return _FameIncrement.Get(); } set { _FameIncrement.Set( value ); } }

	[Description( "heroId's required for current hero employment." )]
	public libdb.IChangeableList<string> RequiredHeroes { get { return _RequiredHeroes; } set { _RequiredHeroes.Assign( value ); } }

	[Description( "Список талантов, которые даются за достижение нового уровня героя" )]
	public DBPtr<BonusTalentsForLevel> BonusTalentsForLevel { get { return _BonusTalentsForLevel.Get(); } set { _BonusTalentsForLevel.Set( value ); } }

	[Description( "Настройки характеристик героя (атака, защита, таланты, сложность) " )]
	public CharacterBarSettings CharacterBarSettings { get { return _CharacterBarSettings; } set { _CharacterBarSettings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_heroAskSoundA = new UndoRedo<string>( owner, string.Empty );
		_heroAskSoundB = new UndoRedo<string>( owner, string.Empty );
		_heroRenderA = new UndoRedoDBPtr<Texture>( owner );
		_heroDescriptionA = new TextRef( owner, new TextRef() );
		_heroBiographyA = new TextRef( owner, new TextRef() );
		_heroRenderB = new UndoRedoDBPtr<Texture>( owner );
		_heroDescriptionB = new TextRef( owner, new TextRef() );
		_heroBiographyB = new TextRef( owner, new TextRef() );
		_IsHeroHiredByDefaultMale = new UndoRedo<bool>( owner, false );
		_IsHeroHiredByDefaultFemale = new UndoRedo<bool>( owner, false );
		_Stats = new UndoRedoDBPtr<HeroStatsTable>( owner );
		_Classes = new UndoRedo<HeroClassEnum>( owner, HeroClassEnum.None );
		_CostMale = new ResourcesTable( owner );
		_CostFemale = new ResourcesTable( owner );
		_ProductionResultIncrement = new ResourcesTable( owner );
		_LevelRequireFemale = new UndoRedo<int>( owner, 0 );
		_LevelRequireMale = new UndoRedo<int>( owner, 0 );
		_Version = new UndoRedo<int>( owner, 0 );
		_FameIncrement = new UndoRedoDBPtr<HeroFameIncrement>( owner );
		_RequiredHeroes = new UndoRedoList<string>( owner );
		_BonusTalentsForLevel = new UndoRedoDBPtr<BonusTalentsForLevel>( owner );
		_CharacterBarSettings = new CharacterBarSettings( owner );
		_heroAskSoundA.Changed += FireChangedEvent;
		_heroAskSoundB.Changed += FireChangedEvent;
		_heroRenderA.Changed += FireChangedEvent;
		_heroDescriptionA.Changed += FireChangedEvent;
		_heroBiographyA.Changed += FireChangedEvent;
		_heroRenderB.Changed += FireChangedEvent;
		_heroDescriptionB.Changed += FireChangedEvent;
		_heroBiographyB.Changed += FireChangedEvent;
		_IsHeroHiredByDefaultMale.Changed += FireChangedEvent;
		_IsHeroHiredByDefaultFemale.Changed += FireChangedEvent;
		_Stats.Changed += FireChangedEvent;
		_Classes.Changed += FireChangedEvent;
		_CostMale.Changed += FireChangedEvent;
		_CostFemale.Changed += FireChangedEvent;
		_ProductionResultIncrement.Changed += FireChangedEvent;
		_LevelRequireFemale.Changed += FireChangedEvent;
		_LevelRequireMale.Changed += FireChangedEvent;
		_Version.Changed += FireChangedEvent;
		_FameIncrement.Changed += FireChangedEvent;
		_RequiredHeroes.Changed += FireChangedEvent;
		_BonusTalentsForLevel.Changed += FireChangedEvent;
		_CharacterBarSettings.Changed += FireChangedEvent;
	}

	public LobbyHeroData()
	{
		Initialize( GetOwner() );
	}

	public LobbyHeroData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LobbyHeroData( DBResource owner, LobbyHeroData source )
		: this(owner, source, true){}

	protected LobbyHeroData( DBResource owner, LobbyHeroData source, bool fireEvent )
	{
		_heroAskSoundA = new UndoRedo<string>( owner, source.heroAskSoundA );
		_heroAskSoundB = new UndoRedo<string>( owner, source.heroAskSoundB );
		_heroRenderA = new UndoRedoDBPtr<Texture>( owner, source.heroRenderA );
		_heroDescriptionA = new TextRef( owner, source.heroDescriptionA );
		_heroBiographyA = new TextRef( owner, source.heroBiographyA );
		_heroRenderB = new UndoRedoDBPtr<Texture>( owner, source.heroRenderB );
		_heroDescriptionB = new TextRef( owner, source.heroDescriptionB );
		_heroBiographyB = new TextRef( owner, source.heroBiographyB );
		_IsHeroHiredByDefaultMale = new UndoRedo<bool>( owner, source.IsHeroHiredByDefaultMale );
		_IsHeroHiredByDefaultFemale = new UndoRedo<bool>( owner, source.IsHeroHiredByDefaultFemale );
		_Stats = new UndoRedoDBPtr<HeroStatsTable>( owner, source.Stats );
		_Classes = new UndoRedo<HeroClassEnum>( owner, source.Classes );
		_CostMale = new ResourcesTable( owner, source.CostMale );
		_CostFemale = new ResourcesTable( owner, source.CostFemale );
		_ProductionResultIncrement = new ResourcesTable( owner, source.ProductionResultIncrement );
		_LevelRequireFemale = new UndoRedo<int>( owner, source.LevelRequireFemale );
		_LevelRequireMale = new UndoRedo<int>( owner, source.LevelRequireMale );
		_Version = new UndoRedo<int>( owner, source.Version );
		_FameIncrement = new UndoRedoDBPtr<HeroFameIncrement>( owner, source.FameIncrement );
		_RequiredHeroes = new UndoRedoList<string>( owner );
		_RequiredHeroes.Assign( source.RequiredHeroes );
		_BonusTalentsForLevel = new UndoRedoDBPtr<BonusTalentsForLevel>( owner, source.BonusTalentsForLevel );
		_CharacterBarSettings = new CharacterBarSettings( owner, source.CharacterBarSettings );
		_heroAskSoundA.Changed += FireChangedEvent;
		_heroAskSoundB.Changed += FireChangedEvent;
		_heroRenderA.Changed += FireChangedEvent;
		_heroDescriptionA.Changed += FireChangedEvent;
		_heroBiographyA.Changed += FireChangedEvent;
		_heroRenderB.Changed += FireChangedEvent;
		_heroDescriptionB.Changed += FireChangedEvent;
		_heroBiographyB.Changed += FireChangedEvent;
		_IsHeroHiredByDefaultMale.Changed += FireChangedEvent;
		_IsHeroHiredByDefaultFemale.Changed += FireChangedEvent;
		_Stats.Changed += FireChangedEvent;
		_Classes.Changed += FireChangedEvent;
		_CostMale.Changed += FireChangedEvent;
		_CostFemale.Changed += FireChangedEvent;
		_ProductionResultIncrement.Changed += FireChangedEvent;
		_LevelRequireFemale.Changed += FireChangedEvent;
		_LevelRequireMale.Changed += FireChangedEvent;
		_Version.Changed += FireChangedEvent;
		_FameIncrement.Changed += FireChangedEvent;
		_RequiredHeroes.Changed += FireChangedEvent;
		_BonusTalentsForLevel.Changed += FireChangedEvent;
		_CharacterBarSettings.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LobbyHeroData source = _source as LobbyHeroData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LobbyHeroData" );
		heroAskSoundA = source.heroAskSoundA;
		heroAskSoundB = source.heroAskSoundB;
		heroRenderA = source.heroRenderA;
		heroDescriptionA = source.heroDescriptionA;
		heroBiographyA = source.heroBiographyA;
		heroRenderB = source.heroRenderB;
		heroDescriptionB = source.heroDescriptionB;
		heroBiographyB = source.heroBiographyB;
		IsHeroHiredByDefaultMale = source.IsHeroHiredByDefaultMale;
		IsHeroHiredByDefaultFemale = source.IsHeroHiredByDefaultFemale;
		Stats = source.Stats;
		Classes = source.Classes;
		CostMale = source.CostMale;
		CostFemale = source.CostFemale;
		ProductionResultIncrement = source.ProductionResultIncrement;
		LevelRequireFemale = source.LevelRequireFemale;
		LevelRequireMale = source.LevelRequireMale;
		Version = source.Version;
		FameIncrement = source.FameIncrement;
		RequiredHeroes = source.RequiredHeroes;
		BonusTalentsForLevel = source.BonusTalentsForLevel;
		CharacterBarSettings = source.CharacterBarSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LobbyHeroData newParent = _newParent as LobbyHeroData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_heroAskSoundA.SetParent( newParent == null ? null : newParent._heroAskSoundA );
		_heroAskSoundB.SetParent( newParent == null ? null : newParent._heroAskSoundB );
		_heroRenderA.SetParent( newParent == null ? null : newParent._heroRenderA );
		_heroDescriptionA.SetParent( newParent == null ? null : newParent._heroDescriptionA );
		_heroBiographyA.SetParent( newParent == null ? null : newParent._heroBiographyA );
		_heroRenderB.SetParent( newParent == null ? null : newParent._heroRenderB );
		_heroDescriptionB.SetParent( newParent == null ? null : newParent._heroDescriptionB );
		_heroBiographyB.SetParent( newParent == null ? null : newParent._heroBiographyB );
		_IsHeroHiredByDefaultMale.SetParent( newParent == null ? null : newParent._IsHeroHiredByDefaultMale );
		_IsHeroHiredByDefaultFemale.SetParent( newParent == null ? null : newParent._IsHeroHiredByDefaultFemale );
		_Stats.SetParent( newParent == null ? null : newParent._Stats );
		_Classes.SetParent( newParent == null ? null : newParent._Classes );
		_CostMale.SetParent( newParent == null ? null : newParent._CostMale );
		_CostFemale.SetParent( newParent == null ? null : newParent._CostFemale );
		_ProductionResultIncrement.SetParent( newParent == null ? null : newParent._ProductionResultIncrement );
		_LevelRequireFemale.SetParent( newParent == null ? null : newParent._LevelRequireFemale );
		_LevelRequireMale.SetParent( newParent == null ? null : newParent._LevelRequireMale );
		_Version.SetParent( newParent == null ? null : newParent._Version );
		_FameIncrement.SetParent( newParent == null ? null : newParent._FameIncrement );
		_RequiredHeroes.SetParent( newParent == null ? null : newParent._RequiredHeroes );
		_BonusTalentsForLevel.SetParent( newParent == null ? null : newParent._BonusTalentsForLevel );
		_CharacterBarSettings.SetParent( newParent == null ? null : newParent._CharacterBarSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_heroAskSoundA.Reset();
		_heroAskSoundB.Reset();
		_heroRenderA.Reset();
		_heroDescriptionA.Reset();
		_heroBiographyA.Reset();
		_heroRenderB.Reset();
		_heroDescriptionB.Reset();
		_heroBiographyB.Reset();
		_IsHeroHiredByDefaultMale.Reset();
		_IsHeroHiredByDefaultFemale.Reset();
		_Stats.Reset();
		_Classes.Reset();
		_CostMale.Reset();
		_CostFemale.Reset();
		_ProductionResultIncrement.Reset();
		_LevelRequireFemale.Reset();
		_LevelRequireMale.Reset();
		_Version.Reset();
		_FameIncrement.Reset();
		_RequiredHeroes.Reset();
		_BonusTalentsForLevel.Reset();
		_CharacterBarSettings.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_heroAskSoundA.IsDerivedFromParent()
			&& _heroAskSoundB.IsDerivedFromParent()
			&& _heroRenderA.IsDerivedFromParent()
			&& _heroDescriptionA.IsDerivedFromParent()
			&& _heroBiographyA.IsDerivedFromParent()
			&& _heroRenderB.IsDerivedFromParent()
			&& _heroDescriptionB.IsDerivedFromParent()
			&& _heroBiographyB.IsDerivedFromParent()
			&& _IsHeroHiredByDefaultMale.IsDerivedFromParent()
			&& _IsHeroHiredByDefaultFemale.IsDerivedFromParent()
			&& _Stats.IsDerivedFromParent()
			&& _Classes.IsDerivedFromParent()
			&& _CostMale.IsDerivedFromParent()
			&& _CostFemale.IsDerivedFromParent()
			&& _ProductionResultIncrement.IsDerivedFromParent()
			&& _LevelRequireFemale.IsDerivedFromParent()
			&& _LevelRequireMale.IsDerivedFromParent()
			&& _Version.IsDerivedFromParent()
			&& _FameIncrement.IsDerivedFromParent()
			&& _RequiredHeroes.IsDerivedFromParent()
			&& _BonusTalentsForLevel.IsDerivedFromParent()
			&& _CharacterBarSettings.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "heroAskSoundA" )
			_heroAskSoundA.Reset();
		else if ( fieldName == "heroAskSoundB" )
			_heroAskSoundB.Reset();
		else if ( fieldName == "heroRenderA" )
			_heroRenderA.Reset();
		else if ( fieldName == "heroDescriptionA" )
			_heroDescriptionA.Reset();
		else if ( fieldName == "heroBiographyA" )
			_heroBiographyA.Reset();
		else if ( fieldName == "heroRenderB" )
			_heroRenderB.Reset();
		else if ( fieldName == "heroDescriptionB" )
			_heroDescriptionB.Reset();
		else if ( fieldName == "heroBiographyB" )
			_heroBiographyB.Reset();
		else if ( fieldName == "IsHeroHiredByDefaultMale" )
			_IsHeroHiredByDefaultMale.Reset();
		else if ( fieldName == "IsHeroHiredByDefaultFemale" )
			_IsHeroHiredByDefaultFemale.Reset();
		else if ( fieldName == "Stats" )
			_Stats.Reset();
		else if ( fieldName == "Classes" )
			_Classes.Reset();
		else if ( fieldName == "CostMale" )
			_CostMale.Reset();
		else if ( fieldName == "CostFemale" )
			_CostFemale.Reset();
		else if ( fieldName == "ProductionResultIncrement" )
			_ProductionResultIncrement.Reset();
		else if ( fieldName == "LevelRequireFemale" )
			_LevelRequireFemale.Reset();
		else if ( fieldName == "LevelRequireMale" )
			_LevelRequireMale.Reset();
		else if ( fieldName == "Version" )
			_Version.Reset();
		else if ( fieldName == "FameIncrement" )
			_FameIncrement.Reset();
		else if ( fieldName == "RequiredHeroes" )
			_RequiredHeroes.Reset();
		else if ( fieldName == "BonusTalentsForLevel" )
			_BonusTalentsForLevel.Reset();
		else if ( fieldName == "CharacterBarSettings" )
			_CharacterBarSettings.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "heroAskSoundA" )
			return _heroAskSoundA.IsDerivedFromParent();
		if ( fieldName == "heroAskSoundB" )
			return _heroAskSoundB.IsDerivedFromParent();
		if ( fieldName == "heroRenderA" )
			return _heroRenderA.IsDerivedFromParent();
		if ( fieldName == "heroDescriptionA" )
			return _heroDescriptionA.IsDerivedFromParent();
		if ( fieldName == "heroBiographyA" )
			return _heroBiographyA.IsDerivedFromParent();
		if ( fieldName == "heroRenderB" )
			return _heroRenderB.IsDerivedFromParent();
		if ( fieldName == "heroDescriptionB" )
			return _heroDescriptionB.IsDerivedFromParent();
		if ( fieldName == "heroBiographyB" )
			return _heroBiographyB.IsDerivedFromParent();
		if ( fieldName == "IsHeroHiredByDefaultMale" )
			return _IsHeroHiredByDefaultMale.IsDerivedFromParent();
		if ( fieldName == "IsHeroHiredByDefaultFemale" )
			return _IsHeroHiredByDefaultFemale.IsDerivedFromParent();
		if ( fieldName == "Stats" )
			return _Stats.IsDerivedFromParent();
		if ( fieldName == "Classes" )
			return _Classes.IsDerivedFromParent();
		if ( fieldName == "CostMale" )
			return _CostMale.IsDerivedFromParent();
		if ( fieldName == "CostFemale" )
			return _CostFemale.IsDerivedFromParent();
		if ( fieldName == "ProductionResultIncrement" )
			return _ProductionResultIncrement.IsDerivedFromParent();
		if ( fieldName == "LevelRequireFemale" )
			return _LevelRequireFemale.IsDerivedFromParent();
		if ( fieldName == "LevelRequireMale" )
			return _LevelRequireMale.IsDerivedFromParent();
		if ( fieldName == "Version" )
			return _Version.IsDerivedFromParent();
		if ( fieldName == "FameIncrement" )
			return _FameIncrement.IsDerivedFromParent();
		if ( fieldName == "RequiredHeroes" )
			return _RequiredHeroes.IsDerivedFromParent();
		if ( fieldName == "BonusTalentsForLevel" )
			return _BonusTalentsForLevel.IsDerivedFromParent();
		if ( fieldName == "CharacterBarSettings" )
			return _CharacterBarSettings.IsDerivedFromParent();
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
[NoCode]
public class BonusTalentsForLevel : DBResource
{
	private UndoRedoDBPtr<BonusTalentsForLevel> ___parent;
	[HideInOutliner]
	public new DBPtr<BonusTalentsForLevel> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<BonusTalents> _Levels;

	[Description( "Уровни героя" )]
	public libdb.IChangeableList<BonusTalents> Levels { get { return _Levels; } set { _Levels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BonusTalentsForLevel>(owner);
		_Levels = new UndoRedoAssignableList<BonusTalents>( owner );
		___parent.Changed += FireChangedEvent;
		_Levels.Changed += FireChangedEvent;
	}

	public BonusTalentsForLevel()
	{
		Initialize( this );
	}
	private void AssignSelf( BonusTalentsForLevel source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BonusTalentsForLevel" );
		Levels = source.Levels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BonusTalentsForLevel source = _source as BonusTalentsForLevel;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BonusTalentsForLevel" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BonusTalentsForLevel newParent = rawParent == null ? null : rawParent.Get<BonusTalentsForLevel>();
		if ( newParent == null && _newParent is BonusTalentsForLevel )
			newParent = _newParent as BonusTalentsForLevel;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Levels.SetParent( newParent == null ? null : newParent._Levels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Levels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Levels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Levels" )
			_Levels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Levels" )
			return _Levels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[NoCode]
public class HeroFameIncrement : DBResource
{
	private UndoRedoDBPtr<HeroFameIncrement> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroFameIncrement> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _FameIncrement;

	public libdb.IChangeableList<int> FameIncrement { get { return _FameIncrement; } set { _FameIncrement.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroFameIncrement>(owner);
		_FameIncrement = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		_FameIncrement.Changed += FireChangedEvent;
	}

	public HeroFameIncrement()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroFameIncrement source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroFameIncrement" );
		FameIncrement = source.FameIncrement;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroFameIncrement source = _source as HeroFameIncrement;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroFameIncrement" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroFameIncrement newParent = rawParent == null ? null : rawParent.Get<HeroFameIncrement>();
		if ( newParent == null && _newParent is HeroFameIncrement )
			newParent = _newParent as HeroFameIncrement;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_FameIncrement.SetParent( newParent == null ? null : newParent._FameIncrement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_FameIncrement.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_FameIncrement.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "FameIncrement" )
			_FameIncrement.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "FameIncrement" )
			return _FameIncrement.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[NoCode]
public class HeroStatsTable : DBResource
{
	private UndoRedoDBPtr<HeroStatsTable> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroStatsTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _MaxEndurance;
	private UndoRedoAssignableList<EnduranceRegenTime> _EnduranceRegen;

	[Description( "Максимальное кол-во бодрости" )]
	public int MaxEndurance { get { return _MaxEndurance.Get(); } set { _MaxEndurance.Set( value ); } }

	[Description( "Табличка соответствия скорости восстановления бодрости и левела героя" )]
	public libdb.IChangeableList<EnduranceRegenTime> EnduranceRegen { get { return _EnduranceRegen; } set { _EnduranceRegen.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroStatsTable>(owner);
		_MaxEndurance = new UndoRedo<int>( owner, 100 );
		_EnduranceRegen = new UndoRedoAssignableList<EnduranceRegenTime>( owner );
		___parent.Changed += FireChangedEvent;
		_MaxEndurance.Changed += FireChangedEvent;
		_EnduranceRegen.Changed += FireChangedEvent;
	}

	public HeroStatsTable()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroStatsTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroStatsTable" );
		MaxEndurance = source.MaxEndurance;
		EnduranceRegen = source.EnduranceRegen;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroStatsTable source = _source as HeroStatsTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroStatsTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroStatsTable newParent = rawParent == null ? null : rawParent.Get<HeroStatsTable>();
		if ( newParent == null && _newParent is HeroStatsTable )
			newParent = _newParent as HeroStatsTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_MaxEndurance.SetParent( newParent == null ? null : newParent._MaxEndurance );
		_EnduranceRegen.SetParent( newParent == null ? null : newParent._EnduranceRegen );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_MaxEndurance.Reset();
		_EnduranceRegen.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_MaxEndurance.IsDerivedFromParent()
			&& _EnduranceRegen.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "MaxEndurance" )
			_MaxEndurance.Reset();
		else if ( fieldName == "EnduranceRegen" )
			_EnduranceRegen.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "MaxEndurance" )
			return _MaxEndurance.IsDerivedFromParent();
		if ( fieldName == "EnduranceRegen" )
			return _EnduranceRegen.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
