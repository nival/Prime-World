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
public enum ConstructionProductionType
{
	None = 0,
	Resource1 = 1,
	Resource2 = 2,
	Resource3 = 3,
	Silver = 4,
	Perl = 5,
	Talents = 6,
	Duck = 7,
	RedPerl = 8,
	Gold = 9,
	Experience = 10,
	Population = 11,
	Shard = 12,
};

public enum ConstructionTab
{
	Services = 0,
	Pocket = 1,
	Production = 2,
	Houseroom = 3,
	Decor = 4,
	ForHeroes = 5,
};

[Flags]
public enum DiscountType
{
	None = 0,
	Gold = 1,
	Time = 2,
	Price = 4,
};

public enum PlayerFraction
{
	A = 0,
	B = 1,
	N = 2,
	NotSetted = 3,
};

public enum PlayerGender
{
	Unknown = 0,
	Male = 1,
	Female = 2,
	Other = 3,
};

public enum SpecialBathCycles
{
	ToNextSessionInBorderlands = 0,
	ToNextSessionInPvp = 1,
	ToMaxLevel = 2,
	ToMaxLevelForGold = 3,
};

public enum TavernResourceType
{
	None = 0,
	Resource1 = 1,
	Resource2 = 2,
	Resource3 = 3,
	Perl = 4,
	Silver = 5,
	Gold = 6,
	Shard = 7,
};

[Custom("Social")]
public class BathCycleType : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BathCycleType __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _cycleDuration;
	private UndoRedo<int> _restoringEnergy;
	private UndoRedo<SpecialBathCycles> _specialCycle;
	private TextRef _cycleTitle;

	[Description( "Время работы цикла" )]
	public float cycleDuration { get { return _cycleDuration.Get(); } set { _cycleDuration.Set( value ); } }

	[Description( "Количество восстанавливаемой энергии" )]
	public int restoringEnergy { get { return _restoringEnergy.Get(); } set { _restoringEnergy.Set( value ); } }

	[Description( "Специальные циклы восстановления энергии" )]
	public SpecialBathCycles specialCycle { get { return _specialCycle.Get(); } set { _specialCycle.Set( value ); } }

	[Description( "заголовок цикла" )]
	public TextRef cycleTitle { get { return _cycleTitle; } set { _cycleTitle.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_cycleDuration = new UndoRedo<float>( owner, 0.0f );
		_restoringEnergy = new UndoRedo<int>( owner, 0 );
		_specialCycle = new UndoRedo<SpecialBathCycles>( owner, SpecialBathCycles.ToNextSessionInBorderlands );
		_cycleTitle = new TextRef( owner, new TextRef() );
		_cycleDuration.Changed += FireChangedEvent;
		_restoringEnergy.Changed += FireChangedEvent;
		_specialCycle.Changed += FireChangedEvent;
		_cycleTitle.Changed += FireChangedEvent;
	}

	public BathCycleType()
	{
		Initialize( GetOwner() );
	}

	public BathCycleType( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BathCycleType( DBResource owner, BathCycleType source )
		: this(owner, source, true){}

	protected BathCycleType( DBResource owner, BathCycleType source, bool fireEvent )
	{
		_cycleDuration = new UndoRedo<float>( owner, source.cycleDuration );
		_restoringEnergy = new UndoRedo<int>( owner, source.restoringEnergy );
		_specialCycle = new UndoRedo<SpecialBathCycles>( owner, source.specialCycle );
		_cycleTitle = new TextRef( owner, source.cycleTitle );
		_cycleDuration.Changed += FireChangedEvent;
		_restoringEnergy.Changed += FireChangedEvent;
		_specialCycle.Changed += FireChangedEvent;
		_cycleTitle.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BathCycleType source = _source as BathCycleType;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BathCycleType" );
		cycleDuration = source.cycleDuration;
		restoringEnergy = source.restoringEnergy;
		specialCycle = source.specialCycle;
		cycleTitle = source.cycleTitle;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BathCycleType newParent = _newParent as BathCycleType;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cycleDuration.SetParent( newParent == null ? null : newParent._cycleDuration );
		_restoringEnergy.SetParent( newParent == null ? null : newParent._restoringEnergy );
		_specialCycle.SetParent( newParent == null ? null : newParent._specialCycle );
		_cycleTitle.SetParent( newParent == null ? null : newParent._cycleTitle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cycleDuration.Reset();
		_restoringEnergy.Reset();
		_specialCycle.Reset();
		_cycleTitle.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cycleDuration.IsDerivedFromParent()
			&& _restoringEnergy.IsDerivedFromParent()
			&& _specialCycle.IsDerivedFromParent()
			&& _cycleTitle.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cycleDuration" )
			_cycleDuration.Reset();
		else if ( fieldName == "restoringEnergy" )
			_restoringEnergy.Reset();
		else if ( fieldName == "specialCycle" )
			_specialCycle.Reset();
		else if ( fieldName == "cycleTitle" )
			_cycleTitle.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "cycleDuration" )
			return _cycleDuration.IsDerivedFromParent();
		if ( fieldName == "restoringEnergy" )
			return _restoringEnergy.IsDerivedFromParent();
		if ( fieldName == "specialCycle" )
			return _specialCycle.IsDerivedFromParent();
		if ( fieldName == "cycleTitle" )
			return _cycleTitle.IsDerivedFromParent();
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
public class BathLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BathLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _heroesCount;
	private UndoRedo<float> _passiveEnergyRecoveryBoost;
	private UndoRedo<float> _recoveryPriceDiscount;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Сколько героев влезают в баню одновременно" )]
	public int heroesCount { get { return _heroesCount.Get(); } set { _heroesCount.Set( value ); } }

	[Description( "Коэффициент ускорения пассивного восстановления энергии героя" )]
	public float passiveEnergyRecoveryBoost { get { return _passiveEnergyRecoveryBoost.Get(); } set { _passiveEnergyRecoveryBoost.Set( value ); } }

	[Description( "Скидка на цену восстановления героя в бане" )]
	public float recoveryPriceDiscount { get { return _recoveryPriceDiscount.Get(); } set { _recoveryPriceDiscount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_heroesCount = new UndoRedo<int>( owner, 0 );
		_passiveEnergyRecoveryBoost = new UndoRedo<float>( owner, 0.0f );
		_recoveryPriceDiscount = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_heroesCount.Changed += FireChangedEvent;
		_passiveEnergyRecoveryBoost.Changed += FireChangedEvent;
		_recoveryPriceDiscount.Changed += FireChangedEvent;
	}

	public BathLevel()
	{
		Initialize( GetOwner() );
	}

	public BathLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BathLevel( DBResource owner, BathLevel source )
		: this(owner, source, true){}

	protected BathLevel( DBResource owner, BathLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_heroesCount = new UndoRedo<int>( owner, source.heroesCount );
		_passiveEnergyRecoveryBoost = new UndoRedo<float>( owner, source.passiveEnergyRecoveryBoost );
		_recoveryPriceDiscount = new UndoRedo<float>( owner, source.recoveryPriceDiscount );
		_currentLevel.Changed += FireChangedEvent;
		_heroesCount.Changed += FireChangedEvent;
		_passiveEnergyRecoveryBoost.Changed += FireChangedEvent;
		_recoveryPriceDiscount.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BathLevel source = _source as BathLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BathLevel" );
		currentLevel = source.currentLevel;
		heroesCount = source.heroesCount;
		passiveEnergyRecoveryBoost = source.passiveEnergyRecoveryBoost;
		recoveryPriceDiscount = source.recoveryPriceDiscount;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BathLevel newParent = _newParent as BathLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_heroesCount.SetParent( newParent == null ? null : newParent._heroesCount );
		_passiveEnergyRecoveryBoost.SetParent( newParent == null ? null : newParent._passiveEnergyRecoveryBoost );
		_recoveryPriceDiscount.SetParent( newParent == null ? null : newParent._recoveryPriceDiscount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_heroesCount.Reset();
		_passiveEnergyRecoveryBoost.Reset();
		_recoveryPriceDiscount.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _heroesCount.IsDerivedFromParent()
			&& _passiveEnergyRecoveryBoost.IsDerivedFromParent()
			&& _recoveryPriceDiscount.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "heroesCount" )
			_heroesCount.Reset();
		else if ( fieldName == "passiveEnergyRecoveryBoost" )
			_passiveEnergyRecoveryBoost.Reset();
		else if ( fieldName == "recoveryPriceDiscount" )
			_recoveryPriceDiscount.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "heroesCount" )
			return _heroesCount.IsDerivedFromParent();
		if ( fieldName == "passiveEnergyRecoveryBoost" )
			return _passiveEnergyRecoveryBoost.IsDerivedFromParent();
		if ( fieldName == "recoveryPriceDiscount" )
			return _recoveryPriceDiscount.IsDerivedFromParent();
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
public class BathPriceToHeroLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BathPriceToHeroLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<float> _silver;

	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	public float silver { get { return _silver.Get(); } set { _silver.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_silver = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_silver.Changed += FireChangedEvent;
	}

	public BathPriceToHeroLevel()
	{
		Initialize( GetOwner() );
	}

	public BathPriceToHeroLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BathPriceToHeroLevel( DBResource owner, BathPriceToHeroLevel source )
		: this(owner, source, true){}

	protected BathPriceToHeroLevel( DBResource owner, BathPriceToHeroLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_silver = new UndoRedo<float>( owner, source.silver );
		_currentLevel.Changed += FireChangedEvent;
		_silver.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BathPriceToHeroLevel source = _source as BathPriceToHeroLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BathPriceToHeroLevel" );
		currentLevel = source.currentLevel;
		silver = source.silver;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BathPriceToHeroLevel newParent = _newParent as BathPriceToHeroLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_silver.SetParent( newParent == null ? null : newParent._silver );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_silver.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _silver.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "silver" )
			_silver.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "silver" )
			return _silver.IsDerivedFromParent();
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
public class BuildedConstructionPosition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BuildedConstructionPosition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;
	private UndoRedo<int> _pitch;

	[Description( "Позиция x" )]
	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	[Description( "Позиция y" )]
	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	[Description( "Кратный 90 градусам угол(от 0 до 270) поворота здания" )]
	public int pitch { get { return _pitch.Get(); } set { _pitch.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_pitch = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
	}

	public BuildedConstructionPosition()
	{
		Initialize( GetOwner() );
	}

	public BuildedConstructionPosition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BuildedConstructionPosition( DBResource owner, BuildedConstructionPosition source )
		: this(owner, source, true){}

	protected BuildedConstructionPosition( DBResource owner, BuildedConstructionPosition source, bool fireEvent )
	{
		_x = new UndoRedo<int>( owner, source.x );
		_y = new UndoRedo<int>( owner, source.y );
		_pitch = new UndoRedo<int>( owner, source.pitch );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_pitch.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BuildedConstructionPosition source = _source as BuildedConstructionPosition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuildedConstructionPosition" );
		x = source.x;
		y = source.y;
		pitch = source.pitch;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BuildedConstructionPosition newParent = _newParent as BuildedConstructionPosition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		_pitch.SetParent( newParent == null ? null : newParent._pitch );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
		_pitch.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			&& _pitch.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else if ( fieldName == "pitch" )
			_pitch.Reset();
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
		if ( fieldName == "pitch" )
			return _pitch.IsDerivedFromParent();
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
public class BuildedConstruction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BuildedConstruction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _persistentId;
	private BuildedConstructionPosition _position;

	[Description( "ID строения" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	public BuildedConstructionPosition position { get { return _position; } set { _position.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_position = new BuildedConstructionPosition( owner );
		_persistentId.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
	}

	public BuildedConstruction()
	{
		Initialize( GetOwner() );
	}

	public BuildedConstruction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BuildedConstruction( DBResource owner, BuildedConstruction source )
		: this(owner, source, true){}

	protected BuildedConstruction( DBResource owner, BuildedConstruction source, bool fireEvent )
	{
		_persistentId = new UndoRedo<string>( owner, source.persistentId );
		_position = new BuildedConstructionPosition( owner, source.position );
		_persistentId.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BuildedConstruction source = _source as BuildedConstruction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuildedConstruction" );
		persistentId = source.persistentId;
		position = source.position;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BuildedConstruction newParent = _newParent as BuildedConstruction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_position.SetParent( newParent == null ? null : newParent._position );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_persistentId.Reset();
		_position.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
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
public class ConstructionLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ConstructionLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ResourcesTable _price;
	private UndoRedo<int> _fame;

	[Description( "Цена за постройку/апгрейд" )]
	public ResourcesTable price { get { return _price; } set { _price.Assign( value ); } }

	[Description( "Сколько Fame дается за постройку/апгрейд" )]
	public int fame { get { return _fame.Get(); } set { _fame.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_price = new ResourcesTable( owner );
		_fame = new UndoRedo<int>( owner, 0 );
		_price.Changed += FireChangedEvent;
		_fame.Changed += FireChangedEvent;
	}

	public ConstructionLevel()
	{
		Initialize( GetOwner() );
	}

	public ConstructionLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ConstructionLevel( DBResource owner, ConstructionLevel source )
		: this(owner, source, true){}

	protected ConstructionLevel( DBResource owner, ConstructionLevel source, bool fireEvent )
	{
		_price = new ResourcesTable( owner, source.price );
		_fame = new UndoRedo<int>( owner, source.fame );
		_price.Changed += FireChangedEvent;
		_fame.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ConstructionLevel source = _source as ConstructionLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConstructionLevel" );
		price = source.price;
		fame = source.fame;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ConstructionLevel newParent = _newParent as ConstructionLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_price.SetParent( newParent == null ? null : newParent._price );
		_fame.SetParent( newParent == null ? null : newParent._fame );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_price.Reset();
		_fame.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_price.IsDerivedFromParent()
			&& _fame.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "price" )
			_price.Reset();
		else if ( fieldName == "fame" )
			_fame.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "price" )
			return _price.IsDerivedFromParent();
		if ( fieldName == "fame" )
			return _fame.IsDerivedFromParent();
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
public class ConstructionTabDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ConstructionTabDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _Name;
	private UndoRedo<string> _IconPath;
	private TextRef _Tooltip;
	private UndoRedo<int> _Order;

	public TextRef Name { get { return _Name; } set { _Name.Assign( value ); } }

	public string IconPath { get { return _IconPath.Get(); } set { _IconPath.Set( value ); } }

	public TextRef Tooltip { get { return _Tooltip; } set { _Tooltip.Assign( value ); } }

	public int Order { get { return _Order.Get(); } set { _Order.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Name = new TextRef( owner, new TextRef() );
		_IconPath = new UndoRedo<string>( owner, string.Empty );
		_Tooltip = new TextRef( owner, new TextRef() );
		_Order = new UndoRedo<int>( owner, 0 );
		_Name.Changed += FireChangedEvent;
		_IconPath.Changed += FireChangedEvent;
		_Tooltip.Changed += FireChangedEvent;
		_Order.Changed += FireChangedEvent;
	}

	public ConstructionTabDesc()
	{
		Initialize( GetOwner() );
	}

	public ConstructionTabDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ConstructionTabDesc( DBResource owner, ConstructionTabDesc source )
		: this(owner, source, true){}

	protected ConstructionTabDesc( DBResource owner, ConstructionTabDesc source, bool fireEvent )
	{
		_Name = new TextRef( owner, source.Name );
		_IconPath = new UndoRedo<string>( owner, source.IconPath );
		_Tooltip = new TextRef( owner, source.Tooltip );
		_Order = new UndoRedo<int>( owner, source.Order );
		_Name.Changed += FireChangedEvent;
		_IconPath.Changed += FireChangedEvent;
		_Tooltip.Changed += FireChangedEvent;
		_Order.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ConstructionTabDesc source = _source as ConstructionTabDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConstructionTabDesc" );
		Name = source.Name;
		IconPath = source.IconPath;
		Tooltip = source.Tooltip;
		Order = source.Order;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ConstructionTabDesc newParent = _newParent as ConstructionTabDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Name.SetParent( newParent == null ? null : newParent._Name );
		_IconPath.SetParent( newParent == null ? null : newParent._IconPath );
		_Tooltip.SetParent( newParent == null ? null : newParent._Tooltip );
		_Order.SetParent( newParent == null ? null : newParent._Order );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Name.Reset();
		_IconPath.Reset();
		_Tooltip.Reset();
		_Order.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Name.IsDerivedFromParent()
			&& _IconPath.IsDerivedFromParent()
			&& _Tooltip.IsDerivedFromParent()
			&& _Order.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Name" )
			_Name.Reset();
		else if ( fieldName == "IconPath" )
			_IconPath.Reset();
		else if ( fieldName == "Tooltip" )
			_Tooltip.Reset();
		else if ( fieldName == "Order" )
			_Order.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Name" )
			return _Name.IsDerivedFromParent();
		if ( fieldName == "IconPath" )
			return _IconPath.IsDerivedFromParent();
		if ( fieldName == "Tooltip" )
			return _Tooltip.IsDerivedFromParent();
		if ( fieldName == "Order" )
			return _Order.IsDerivedFromParent();
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
public class ContextBuyResource : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ContextBuyResource __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _isPack;
	private UndoRedo<int> _resourceCount;
	private UndoRedo<float> _goldPrice;

	public bool isPack { get { return _isPack.Get(); } set { _isPack.Set( value ); } }

	public int resourceCount { get { return _resourceCount.Get(); } set { _resourceCount.Set( value ); } }

	public float goldPrice { get { return _goldPrice.Get(); } set { _goldPrice.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_isPack = new UndoRedo<bool>( owner, false );
		_resourceCount = new UndoRedo<int>( owner, 0 );
		_goldPrice = new UndoRedo<float>( owner, 0.0f );
		_isPack.Changed += FireChangedEvent;
		_resourceCount.Changed += FireChangedEvent;
		_goldPrice.Changed += FireChangedEvent;
	}

	public ContextBuyResource()
	{
		Initialize( GetOwner() );
	}

	public ContextBuyResource( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ContextBuyResource( DBResource owner, ContextBuyResource source )
		: this(owner, source, true){}

	protected ContextBuyResource( DBResource owner, ContextBuyResource source, bool fireEvent )
	{
		_isPack = new UndoRedo<bool>( owner, source.isPack );
		_resourceCount = new UndoRedo<int>( owner, source.resourceCount );
		_goldPrice = new UndoRedo<float>( owner, source.goldPrice );
		_isPack.Changed += FireChangedEvent;
		_resourceCount.Changed += FireChangedEvent;
		_goldPrice.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ContextBuyResource source = _source as ContextBuyResource;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ContextBuyResource" );
		isPack = source.isPack;
		resourceCount = source.resourceCount;
		goldPrice = source.goldPrice;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ContextBuyResource newParent = _newParent as ContextBuyResource;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_isPack.SetParent( newParent == null ? null : newParent._isPack );
		_resourceCount.SetParent( newParent == null ? null : newParent._resourceCount );
		_goldPrice.SetParent( newParent == null ? null : newParent._goldPrice );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_isPack.Reset();
		_resourceCount.Reset();
		_goldPrice.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_isPack.IsDerivedFromParent()
			&& _resourceCount.IsDerivedFromParent()
			&& _goldPrice.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "isPack" )
			_isPack.Reset();
		else if ( fieldName == "resourceCount" )
			_resourceCount.Reset();
		else if ( fieldName == "goldPrice" )
			_goldPrice.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "isPack" )
			return _isPack.IsDerivedFromParent();
		if ( fieldName == "resourceCount" )
			return _resourceCount.IsDerivedFromParent();
		if ( fieldName == "goldPrice" )
			return _goldPrice.IsDerivedFromParent();
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
public class ContextBuyResourceTabel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ContextBuyResourceTabel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ContextBuyResource _Resource1;
	private ContextBuyResource _Resource2;
	private ContextBuyResource _Resource3;
	private ContextBuyResource _Silver;
	private ContextBuyResource _Perl;

	public ContextBuyResource Resource1 { get { return _Resource1; } set { _Resource1.Assign( value ); } }

	public ContextBuyResource Resource2 { get { return _Resource2; } set { _Resource2.Assign( value ); } }

	public ContextBuyResource Resource3 { get { return _Resource3; } set { _Resource3.Assign( value ); } }

	public ContextBuyResource Silver { get { return _Silver; } set { _Silver.Assign( value ); } }

	public ContextBuyResource Perl { get { return _Perl; } set { _Perl.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Resource1 = new ContextBuyResource( owner );
		_Resource2 = new ContextBuyResource( owner );
		_Resource3 = new ContextBuyResource( owner );
		_Silver = new ContextBuyResource( owner );
		_Perl = new ContextBuyResource( owner );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
	}

	public ContextBuyResourceTabel()
	{
		Initialize( GetOwner() );
	}

	public ContextBuyResourceTabel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ContextBuyResourceTabel( DBResource owner, ContextBuyResourceTabel source )
		: this(owner, source, true){}

	protected ContextBuyResourceTabel( DBResource owner, ContextBuyResourceTabel source, bool fireEvent )
	{
		_Resource1 = new ContextBuyResource( owner, source.Resource1 );
		_Resource2 = new ContextBuyResource( owner, source.Resource2 );
		_Resource3 = new ContextBuyResource( owner, source.Resource3 );
		_Silver = new ContextBuyResource( owner, source.Silver );
		_Perl = new ContextBuyResource( owner, source.Perl );
		_Resource1.Changed += FireChangedEvent;
		_Resource2.Changed += FireChangedEvent;
		_Resource3.Changed += FireChangedEvent;
		_Silver.Changed += FireChangedEvent;
		_Perl.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ContextBuyResourceTabel source = _source as ContextBuyResourceTabel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ContextBuyResourceTabel" );
		Resource1 = source.Resource1;
		Resource2 = source.Resource2;
		Resource3 = source.Resource3;
		Silver = source.Silver;
		Perl = source.Perl;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ContextBuyResourceTabel newParent = _newParent as ContextBuyResourceTabel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Resource1.SetParent( newParent == null ? null : newParent._Resource1 );
		_Resource2.SetParent( newParent == null ? null : newParent._Resource2 );
		_Resource3.SetParent( newParent == null ? null : newParent._Resource3 );
		_Silver.SetParent( newParent == null ? null : newParent._Silver );
		_Perl.SetParent( newParent == null ? null : newParent._Perl );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Resource1.Reset();
		_Resource2.Reset();
		_Resource3.Reset();
		_Silver.Reset();
		_Perl.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Resource1.IsDerivedFromParent()
			&& _Resource2.IsDerivedFromParent()
			&& _Resource3.IsDerivedFromParent()
			&& _Silver.IsDerivedFromParent()
			&& _Perl.IsDerivedFromParent()
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
		else if ( fieldName == "Silver" )
			_Silver.Reset();
		else if ( fieldName == "Perl" )
			_Perl.Reset();
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
		if ( fieldName == "Silver" )
			return _Silver.IsDerivedFromParent();
		if ( fieldName == "Perl" )
			return _Perl.IsDerivedFromParent();
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
public class CycleType : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CycleType __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ResourcesTable _priceToStart;
	private ResourcesTable _resourcesToProduce;
	private UndoRedo<int> _fameToProduce;
	private UndoRedoDBPtr<TimeBlock> _timeblock;
	private UndoRedo<bool> _isCustom;
	private UndoRedo<DiscountType> _discountType;
	private TextRef _customTooltip;

	[Description( "Цена старта добычи ресурсов" )]
	public ResourcesTable priceToStart { get { return _priceToStart; } set { _priceToStart.Assign( value ); } }

	[Description( "Сколько ресурсов добудется. Доступен для namemap'а" )]
	[NameMapValue]
	public ResourcesTable resourcesToProduce { get { return _resourcesToProduce; } set { _resourcesToProduce.Assign( value ); } }

	[Description( "Сколько fame дадут за завершение цикла" )]
	public int fameToProduce { get { return _fameToProduce.Get(); } set { _fameToProduce.Set( value ); } }

	[Description( "Время цикла" )]
	public DBPtr<TimeBlock> timeblock { get { return _timeblock.Get(); } set { _timeblock.Set( value ); } }

	[Description( "При true пользователь может менять количество ресурсов, которые он хочет произвести" )]
	public bool isCustom { get { return _isCustom.Get(); } set { _isCustom.Set( value ); } }

	[Description( "На что распространяется скидка в цикле - ускорение, время, цена запуска" )]
	public DiscountType discountType { get { return _discountType.Get(); } set { _discountType.Set( value ); } }

	[Description( "Кастомный тултип, для циклов" )]
	public TextRef customTooltip { get { return _customTooltip; } set { _customTooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_priceToStart = new ResourcesTable( owner );
		_resourcesToProduce = new ResourcesTable( owner );
		_fameToProduce = new UndoRedo<int>( owner, 0 );
		_timeblock = new UndoRedoDBPtr<TimeBlock>( owner );
		_isCustom = new UndoRedo<bool>( owner, false );
		_discountType = new UndoRedo<DiscountType>( owner, DiscountType.None );
		_customTooltip = new TextRef( owner, new TextRef() );
		_priceToStart.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
		_timeblock.Changed += FireChangedEvent;
		_isCustom.Changed += FireChangedEvent;
		_discountType.Changed += FireChangedEvent;
		_customTooltip.Changed += FireChangedEvent;
	}

	public CycleType()
	{
		Initialize( GetOwner() );
	}

	public CycleType( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CycleType( DBResource owner, CycleType source )
		: this(owner, source, true){}

	protected CycleType( DBResource owner, CycleType source, bool fireEvent )
	{
		_priceToStart = new ResourcesTable( owner, source.priceToStart );
		_resourcesToProduce = new ResourcesTable( owner, source.resourcesToProduce );
		_fameToProduce = new UndoRedo<int>( owner, source.fameToProduce );
		_timeblock = new UndoRedoDBPtr<TimeBlock>( owner, source.timeblock );
		_isCustom = new UndoRedo<bool>( owner, source.isCustom );
		_discountType = new UndoRedo<DiscountType>( owner, source.discountType );
		_customTooltip = new TextRef( owner, source.customTooltip );
		_priceToStart.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
		_timeblock.Changed += FireChangedEvent;
		_isCustom.Changed += FireChangedEvent;
		_discountType.Changed += FireChangedEvent;
		_customTooltip.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CycleType source = _source as CycleType;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CycleType" );
		priceToStart = source.priceToStart;
		resourcesToProduce = source.resourcesToProduce;
		fameToProduce = source.fameToProduce;
		timeblock = source.timeblock;
		isCustom = source.isCustom;
		discountType = source.discountType;
		customTooltip = source.customTooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CycleType newParent = _newParent as CycleType;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_priceToStart.SetParent( newParent == null ? null : newParent._priceToStart );
		_resourcesToProduce.SetParent( newParent == null ? null : newParent._resourcesToProduce );
		_fameToProduce.SetParent( newParent == null ? null : newParent._fameToProduce );
		_timeblock.SetParent( newParent == null ? null : newParent._timeblock );
		_isCustom.SetParent( newParent == null ? null : newParent._isCustom );
		_discountType.SetParent( newParent == null ? null : newParent._discountType );
		_customTooltip.SetParent( newParent == null ? null : newParent._customTooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_priceToStart.Reset();
		_resourcesToProduce.Reset();
		_fameToProduce.Reset();
		_timeblock.Reset();
		_isCustom.Reset();
		_discountType.Reset();
		_customTooltip.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_priceToStart.IsDerivedFromParent()
			&& _resourcesToProduce.IsDerivedFromParent()
			&& _fameToProduce.IsDerivedFromParent()
			&& _timeblock.IsDerivedFromParent()
			&& _isCustom.IsDerivedFromParent()
			&& _discountType.IsDerivedFromParent()
			&& _customTooltip.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "priceToStart" )
			_priceToStart.Reset();
		else if ( fieldName == "resourcesToProduce" )
			_resourcesToProduce.Reset();
		else if ( fieldName == "fameToProduce" )
			_fameToProduce.Reset();
		else if ( fieldName == "timeblock" )
			_timeblock.Reset();
		else if ( fieldName == "isCustom" )
			_isCustom.Reset();
		else if ( fieldName == "discountType" )
			_discountType.Reset();
		else if ( fieldName == "customTooltip" )
			_customTooltip.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "priceToStart" )
			return _priceToStart.IsDerivedFromParent();
		if ( fieldName == "resourcesToProduce" )
			return _resourcesToProduce.IsDerivedFromParent();
		if ( fieldName == "fameToProduce" )
			return _fameToProduce.IsDerivedFromParent();
		if ( fieldName == "timeblock" )
			return _timeblock.IsDerivedFromParent();
		if ( fieldName == "isCustom" )
			return _isCustom.IsDerivedFromParent();
		if ( fieldName == "discountType" )
			return _discountType.IsDerivedFromParent();
		if ( fieldName == "customTooltip" )
			return _customTooltip.IsDerivedFromParent();
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
public class DefaultMap : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DefaultMap __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBAdvMapDescGroup> _group;
	private UndoRedoDBPtr<AdvMapDescription> _map;
	private UndoRedo<bool> _enabled;

	[Description( "Группа карт по умолчанию для режима" )]
	public DBPtr<DBAdvMapDescGroup> group { get { return _group.Get(); } set { _group.Set( value ); } }

	[Description( "Карта по умолчанию для режима" )]
	public DBPtr<AdvMapDescription> map { get { return _map.Get(); } set { _map.Set( value ); } }

	[Description( "Доступна ли она по умолчанию" )]
	public bool enabled { get { return _enabled.Get(); } set { _enabled.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_group = new UndoRedoDBPtr<DBAdvMapDescGroup>( owner );
		_map = new UndoRedoDBPtr<AdvMapDescription>( owner );
		_enabled = new UndoRedo<bool>( owner, false );
		_group.Changed += FireChangedEvent;
		_map.Changed += FireChangedEvent;
		_enabled.Changed += FireChangedEvent;
	}

	public DefaultMap()
	{
		Initialize( GetOwner() );
	}

	public DefaultMap( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DefaultMap( DBResource owner, DefaultMap source )
		: this(owner, source, true){}

	protected DefaultMap( DBResource owner, DefaultMap source, bool fireEvent )
	{
		_group = new UndoRedoDBPtr<DBAdvMapDescGroup>( owner, source.group );
		_map = new UndoRedoDBPtr<AdvMapDescription>( owner, source.map );
		_enabled = new UndoRedo<bool>( owner, source.enabled );
		_group.Changed += FireChangedEvent;
		_map.Changed += FireChangedEvent;
		_enabled.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DefaultMap source = _source as DefaultMap;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DefaultMap" );
		group = source.group;
		map = source.map;
		enabled = source.enabled;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DefaultMap newParent = _newParent as DefaultMap;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_group.SetParent( newParent == null ? null : newParent._group );
		_map.SetParent( newParent == null ? null : newParent._map );
		_enabled.SetParent( newParent == null ? null : newParent._enabled );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_group.Reset();
		_map.Reset();
		_enabled.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_group.IsDerivedFromParent()
			&& _map.IsDerivedFromParent()
			&& _enabled.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "group" )
			_group.Reset();
		else if ( fieldName == "map" )
			_map.Reset();
		else if ( fieldName == "enabled" )
			_enabled.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "group" )
			return _group.IsDerivedFromParent();
		if ( fieldName == "map" )
			return _map.IsDerivedFromParent();
		if ( fieldName == "enabled" )
			return _enabled.IsDerivedFromParent();
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
public class ErrorMessage : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ErrorMessage __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<bool> _CloseApplicationAfterDialog;
	private TextRef _Text;

	public bool CloseApplicationAfterDialog { get { return _CloseApplicationAfterDialog.Get(); } set { _CloseApplicationAfterDialog.Set( value ); } }

	public TextRef Text { get { return _Text; } set { _Text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_CloseApplicationAfterDialog = new UndoRedo<bool>( owner, false );
		_Text = new TextRef( owner, new TextRef() );
		_CloseApplicationAfterDialog.Changed += FireChangedEvent;
		_Text.Changed += FireChangedEvent;
	}

	public ErrorMessage()
	{
		Initialize( GetOwner() );
	}

	public ErrorMessage( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ErrorMessage( DBResource owner, ErrorMessage source )
		: this(owner, source, true){}

	protected ErrorMessage( DBResource owner, ErrorMessage source, bool fireEvent )
	{
		_CloseApplicationAfterDialog = new UndoRedo<bool>( owner, source.CloseApplicationAfterDialog );
		_Text = new TextRef( owner, source.Text );
		_CloseApplicationAfterDialog.Changed += FireChangedEvent;
		_Text.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ErrorMessage source = _source as ErrorMessage;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ErrorMessage" );
		CloseApplicationAfterDialog = source.CloseApplicationAfterDialog;
		Text = source.Text;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ErrorMessage newParent = _newParent as ErrorMessage;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_CloseApplicationAfterDialog.SetParent( newParent == null ? null : newParent._CloseApplicationAfterDialog );
		_Text.SetParent( newParent == null ? null : newParent._Text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_CloseApplicationAfterDialog.Reset();
		_Text.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_CloseApplicationAfterDialog.IsDerivedFromParent()
			&& _Text.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "CloseApplicationAfterDialog" )
			_CloseApplicationAfterDialog.Reset();
		else if ( fieldName == "Text" )
			_Text.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "CloseApplicationAfterDialog" )
			return _CloseApplicationAfterDialog.IsDerivedFromParent();
		if ( fieldName == "Text" )
			return _Text.IsDerivedFromParent();
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

[IndexField("ErrorCode", true)]
[Custom("Social")]
public class ErrorKeyMessagePair : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ErrorKeyMessagePair __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _ErrorCode;
	private ErrorMessage _Message;

	public int ErrorCode { get { return _ErrorCode.Get(); } set { _ErrorCode.Set( value ); } }

	public ErrorMessage Message { get { return _Message; } set { _Message.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_ErrorCode = new UndoRedo<int>( owner, 0 );
		_Message = new ErrorMessage( owner );
		_ErrorCode.Changed += FireChangedEvent;
		_Message.Changed += FireChangedEvent;
	}

	public ErrorKeyMessagePair()
	{
		Initialize( GetOwner() );
	}

	public ErrorKeyMessagePair( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ErrorKeyMessagePair( DBResource owner, ErrorKeyMessagePair source )
		: this(owner, source, true){}

	protected ErrorKeyMessagePair( DBResource owner, ErrorKeyMessagePair source, bool fireEvent )
	{
		_ErrorCode = new UndoRedo<int>( owner, source.ErrorCode );
		_Message = new ErrorMessage( owner, source.Message );
		_ErrorCode.Changed += FireChangedEvent;
		_Message.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ErrorKeyMessagePair source = _source as ErrorKeyMessagePair;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ErrorKeyMessagePair" );
		ErrorCode = source.ErrorCode;
		Message = source.Message;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ErrorKeyMessagePair newParent = _newParent as ErrorKeyMessagePair;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ErrorCode.SetParent( newParent == null ? null : newParent._ErrorCode );
		_Message.SetParent( newParent == null ? null : newParent._Message );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ErrorCode.Reset();
		_Message.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ErrorCode.IsDerivedFromParent()
			&& _Message.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ErrorCode" )
			_ErrorCode.Reset();
		else if ( fieldName == "Message" )
			_Message.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ErrorCode" )
			return _ErrorCode.IsDerivedFromParent();
		if ( fieldName == "Message" )
			return _Message.IsDerivedFromParent();
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
public class FameLevelRes : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FameLevelRes __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private ResourcesTable _resourcesPerLevel;
	private UndoRedo<int> _PremiumAccountHours;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Количество ресурсов, выдаваемых игроку за новый уровень лорда" )]
	public ResourcesTable resourcesPerLevel { get { return _resourcesPerLevel; } set { _resourcesPerLevel.Assign( value ); } }

	[Description( "Количество часов премимум аккаунта, выдаваемых за новый уровень лорда" )]
	public int PremiumAccountHours { get { return _PremiumAccountHours.Get(); } set { _PremiumAccountHours.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_resourcesPerLevel = new ResourcesTable( owner );
		_PremiumAccountHours = new UndoRedo<int>( owner, 0 );
		_currentLevel.Changed += FireChangedEvent;
		_resourcesPerLevel.Changed += FireChangedEvent;
		_PremiumAccountHours.Changed += FireChangedEvent;
	}

	public FameLevelRes()
	{
		Initialize( GetOwner() );
	}

	public FameLevelRes( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FameLevelRes( DBResource owner, FameLevelRes source )
		: this(owner, source, true){}

	protected FameLevelRes( DBResource owner, FameLevelRes source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_resourcesPerLevel = new ResourcesTable( owner, source.resourcesPerLevel );
		_PremiumAccountHours = new UndoRedo<int>( owner, source.PremiumAccountHours );
		_currentLevel.Changed += FireChangedEvent;
		_resourcesPerLevel.Changed += FireChangedEvent;
		_PremiumAccountHours.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FameLevelRes source = _source as FameLevelRes;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FameLevelRes" );
		currentLevel = source.currentLevel;
		resourcesPerLevel = source.resourcesPerLevel;
		PremiumAccountHours = source.PremiumAccountHours;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FameLevelRes newParent = _newParent as FameLevelRes;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_resourcesPerLevel.SetParent( newParent == null ? null : newParent._resourcesPerLevel );
		_PremiumAccountHours.SetParent( newParent == null ? null : newParent._PremiumAccountHours );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_resourcesPerLevel.Reset();
		_PremiumAccountHours.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _resourcesPerLevel.IsDerivedFromParent()
			&& _PremiumAccountHours.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "resourcesPerLevel" )
			_resourcesPerLevel.Reset();
		else if ( fieldName == "PremiumAccountHours" )
			_PremiumAccountHours.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "resourcesPerLevel" )
			return _resourcesPerLevel.IsDerivedFromParent();
		if ( fieldName == "PremiumAccountHours" )
			return _PremiumAccountHours.IsDerivedFromParent();
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
public class FirstBuyCycle : CycleType, libdb.ICompositeDBValue, libdb.IChangeable
{

	private FirstBuyCycle __parent = null;

	private UndoRedoList<int> _percents;

	[Description( "Процент выдачи одного из типа ресурса по окончанию цикла" )]
	[EnumArray(typeof(EResourceType))]
	public libdb.IChangeableList<int> percents { get { return _percents; } set { _percents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_percents = new UndoRedoList<int>( owner, typeof( EResourceType ) );
		_percents.Changed += FireChangedEvent;
	}

	public FirstBuyCycle()
	{
		Initialize( GetOwner() );
	}

	public FirstBuyCycle( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public FirstBuyCycle( DBResource owner, FirstBuyCycle source ): base(owner, source, false)
	{
		_percents = new UndoRedoList<int>( owner, typeof( EResourceType ) );
		_percents.Assign( source.percents );
		_percents.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		FirstBuyCycle source = _source as FirstBuyCycle;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyCycle" );

		base.Assign( source );

		percents = source.percents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		FirstBuyCycle newParent = _newParent as FirstBuyCycle;
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
public class FirstBuyLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FirstBuyLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _additionalTalentSlots;
	private ResourcesTable _additionalStorage;
	private ResourcesTable _resources;
	private FirstBuyCycle _cycle;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "На сколько увеличивается максимальное кол-во талантов в библиотеке" )]
	public int additionalTalentSlots { get { return _additionalTalentSlots.Get(); } set { _additionalTalentSlots.Set( value ); } }

	[Description( "На сколько увеличивается максимальный запас склада" )]
	public ResourcesTable additionalStorage { get { return _additionalStorage; } set { _additionalStorage.Assign( value ); } }

	[Description( "Ресурсы, дающиеся при покупке" )]
	public ResourcesTable resources { get { return _resources; } set { _resources.Assign( value ); } }

	[Description( "Всегда только 1 цикл" )]
	public FirstBuyCycle cycle { get { return _cycle; } set { _cycle.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_additionalTalentSlots = new UndoRedo<int>( owner, 0 );
		_additionalStorage = new ResourcesTable( owner );
		_resources = new ResourcesTable( owner );
		_cycle = new FirstBuyCycle( owner );
		_currentLevel.Changed += FireChangedEvent;
		_additionalTalentSlots.Changed += FireChangedEvent;
		_additionalStorage.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
	}

	public FirstBuyLevel()
	{
		Initialize( GetOwner() );
	}

	public FirstBuyLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FirstBuyLevel( DBResource owner, FirstBuyLevel source )
		: this(owner, source, true){}

	protected FirstBuyLevel( DBResource owner, FirstBuyLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_additionalTalentSlots = new UndoRedo<int>( owner, source.additionalTalentSlots );
		_additionalStorage = new ResourcesTable( owner, source.additionalStorage );
		_resources = new ResourcesTable( owner, source.resources );
		_cycle = new FirstBuyCycle( owner, source.cycle );
		_currentLevel.Changed += FireChangedEvent;
		_additionalTalentSlots.Changed += FireChangedEvent;
		_additionalStorage.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FirstBuyLevel source = _source as FirstBuyLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyLevel" );
		currentLevel = source.currentLevel;
		additionalTalentSlots = source.additionalTalentSlots;
		additionalStorage = source.additionalStorage;
		resources = source.resources;
		cycle = source.cycle;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FirstBuyLevel newParent = _newParent as FirstBuyLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_additionalTalentSlots.SetParent( newParent == null ? null : newParent._additionalTalentSlots );
		_additionalStorage.SetParent( newParent == null ? null : newParent._additionalStorage );
		_resources.SetParent( newParent == null ? null : newParent._resources );
		_cycle.SetParent( newParent == null ? null : newParent._cycle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_additionalTalentSlots.Reset();
		_additionalStorage.Reset();
		_resources.Reset();
		_cycle.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _additionalTalentSlots.IsDerivedFromParent()
			&& _additionalStorage.IsDerivedFromParent()
			&& _resources.IsDerivedFromParent()
			&& _cycle.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "additionalTalentSlots" )
			_additionalTalentSlots.Reset();
		else if ( fieldName == "additionalStorage" )
			_additionalStorage.Reset();
		else if ( fieldName == "resources" )
			_resources.Reset();
		else if ( fieldName == "cycle" )
			_cycle.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "additionalTalentSlots" )
			return _additionalTalentSlots.IsDerivedFromParent();
		if ( fieldName == "additionalStorage" )
			return _additionalStorage.IsDerivedFromParent();
		if ( fieldName == "resources" )
			return _resources.IsDerivedFromParent();
		if ( fieldName == "cycle" )
			return _cycle.IsDerivedFromParent();
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
public class FreeSkipsEventBuildings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FreeSkipsEventBuildings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Constructon> _talentProductionBuilding;
	private UndoRedoDBPtr<Constructon> _crystalProductionBuilding;

	public DBPtr<Constructon> talentProductionBuilding { get { return _talentProductionBuilding.Get(); } set { _talentProductionBuilding.Set( value ); } }

	public DBPtr<Constructon> crystalProductionBuilding { get { return _crystalProductionBuilding.Get(); } set { _crystalProductionBuilding.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_talentProductionBuilding = new UndoRedoDBPtr<Constructon>( owner );
		_crystalProductionBuilding = new UndoRedoDBPtr<Constructon>( owner );
		_talentProductionBuilding.Changed += FireChangedEvent;
		_crystalProductionBuilding.Changed += FireChangedEvent;
	}

	public FreeSkipsEventBuildings()
	{
		Initialize( GetOwner() );
	}

	public FreeSkipsEventBuildings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FreeSkipsEventBuildings( DBResource owner, FreeSkipsEventBuildings source )
		: this(owner, source, true){}

	protected FreeSkipsEventBuildings( DBResource owner, FreeSkipsEventBuildings source, bool fireEvent )
	{
		_talentProductionBuilding = new UndoRedoDBPtr<Constructon>( owner, source.talentProductionBuilding );
		_crystalProductionBuilding = new UndoRedoDBPtr<Constructon>( owner, source.crystalProductionBuilding );
		_talentProductionBuilding.Changed += FireChangedEvent;
		_crystalProductionBuilding.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FreeSkipsEventBuildings source = _source as FreeSkipsEventBuildings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FreeSkipsEventBuildings" );
		talentProductionBuilding = source.talentProductionBuilding;
		crystalProductionBuilding = source.crystalProductionBuilding;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FreeSkipsEventBuildings newParent = _newParent as FreeSkipsEventBuildings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_talentProductionBuilding.SetParent( newParent == null ? null : newParent._talentProductionBuilding );
		_crystalProductionBuilding.SetParent( newParent == null ? null : newParent._crystalProductionBuilding );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_talentProductionBuilding.Reset();
		_crystalProductionBuilding.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_talentProductionBuilding.IsDerivedFromParent()
			&& _crystalProductionBuilding.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "talentProductionBuilding" )
			_talentProductionBuilding.Reset();
		else if ( fieldName == "crystalProductionBuilding" )
			_crystalProductionBuilding.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "talentProductionBuilding" )
			return _talentProductionBuilding.IsDerivedFromParent();
		if ( fieldName == "crystalProductionBuilding" )
			return _crystalProductionBuilding.IsDerivedFromParent();
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
public class GoldLampRollSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GoldLampRollSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _lastPayDate;
	private UndoRedoDBPtr<RollContainer> _container;

	public int lastPayDate { get { return _lastPayDate.Get(); } set { _lastPayDate.Set( value ); } }

	public DBPtr<RollContainer> container { get { return _container.Get(); } set { _container.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lastPayDate = new UndoRedo<int>( owner, 0 );
		_container = new UndoRedoDBPtr<RollContainer>( owner );
		_lastPayDate.Changed += FireChangedEvent;
		_container.Changed += FireChangedEvent;
	}

	public GoldLampRollSettings()
	{
		Initialize( GetOwner() );
	}

	public GoldLampRollSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GoldLampRollSettings( DBResource owner, GoldLampRollSettings source )
		: this(owner, source, true){}

	protected GoldLampRollSettings( DBResource owner, GoldLampRollSettings source, bool fireEvent )
	{
		_lastPayDate = new UndoRedo<int>( owner, source.lastPayDate );
		_container = new UndoRedoDBPtr<RollContainer>( owner, source.container );
		_lastPayDate.Changed += FireChangedEvent;
		_container.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GoldLampRollSettings source = _source as GoldLampRollSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldLampRollSettings" );
		lastPayDate = source.lastPayDate;
		container = source.container;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GoldLampRollSettings newParent = _newParent as GoldLampRollSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lastPayDate.SetParent( newParent == null ? null : newParent._lastPayDate );
		_container.SetParent( newParent == null ? null : newParent._container );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lastPayDate.Reset();
		_container.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lastPayDate.IsDerivedFromParent()
			&& _container.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lastPayDate" )
			_lastPayDate.Reset();
		else if ( fieldName == "container" )
			_container.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lastPayDate" )
			return _lastPayDate.IsDerivedFromParent();
		if ( fieldName == "container" )
			return _container.IsDerivedFromParent();
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
public class GoldTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GoldTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _timePercent;
	private UndoRedo<int> _goldPercent;

	[Description( "Процент вермени, с которого начинается данная цена" )]
	public int timePercent { get { return _timePercent.Get(); } set { _timePercent.Set( value ); } }

	[Description( "Процент от базовой цены, чтобы докупить цикл если он уже отработал [timePercent] процентов времени" )]
	public int goldPercent { get { return _goldPercent.Get(); } set { _goldPercent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_timePercent = new UndoRedo<int>( owner, 0 );
		_goldPercent = new UndoRedo<int>( owner, 0 );
		_timePercent.Changed += FireChangedEvent;
		_goldPercent.Changed += FireChangedEvent;
	}

	public GoldTable()
	{
		Initialize( GetOwner() );
	}

	public GoldTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GoldTable( DBResource owner, GoldTable source )
		: this(owner, source, true){}

	protected GoldTable( DBResource owner, GoldTable source, bool fireEvent )
	{
		_timePercent = new UndoRedo<int>( owner, source.timePercent );
		_goldPercent = new UndoRedo<int>( owner, source.goldPercent );
		_timePercent.Changed += FireChangedEvent;
		_goldPercent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GoldTable source = _source as GoldTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldTable" );
		timePercent = source.timePercent;
		goldPercent = source.goldPercent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GoldTable newParent = _newParent as GoldTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_timePercent.SetParent( newParent == null ? null : newParent._timePercent );
		_goldPercent.SetParent( newParent == null ? null : newParent._goldPercent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_timePercent.Reset();
		_goldPercent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_timePercent.IsDerivedFromParent()
			&& _goldPercent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "timePercent" )
			_timePercent.Reset();
		else if ( fieldName == "goldPercent" )
			_goldPercent.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "timePercent" )
			return _timePercent.IsDerivedFromParent();
		if ( fieldName == "goldPercent" )
			return _goldPercent.IsDerivedFromParent();
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
public class HeroClassInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroClassInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<HeroClassEnum> _Class;
	private TextRef _Name;
	private TextRef _Description;

	public HeroClassEnum Class { get { return _Class.Get(); } set { _Class.Set( value ); } }

	public TextRef Name { get { return _Name; } set { _Name.Assign( value ); } }

	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Class = new UndoRedo<HeroClassEnum>( owner, HeroClassEnum.None );
		_Name = new TextRef( owner, new TextRef() );
		_Description = new TextRef( owner, new TextRef() );
		_Class.Changed += FireChangedEvent;
		_Name.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
	}

	public HeroClassInfo()
	{
		Initialize( GetOwner() );
	}

	public HeroClassInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroClassInfo( DBResource owner, HeroClassInfo source )
		: this(owner, source, true){}

	protected HeroClassInfo( DBResource owner, HeroClassInfo source, bool fireEvent )
	{
		_Class = new UndoRedo<HeroClassEnum>( owner, source.Class );
		_Name = new TextRef( owner, source.Name );
		_Description = new TextRef( owner, source.Description );
		_Class.Changed += FireChangedEvent;
		_Name.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroClassInfo source = _source as HeroClassInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroClassInfo" );
		Class = source.Class;
		Name = source.Name;
		Description = source.Description;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroClassInfo newParent = _newParent as HeroClassInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Class.SetParent( newParent == null ? null : newParent._Class );
		_Name.SetParent( newParent == null ? null : newParent._Name );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Class.Reset();
		_Name.Reset();
		_Description.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Class.IsDerivedFromParent()
			&& _Name.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Class" )
			_Class.Reset();
		else if ( fieldName == "Name" )
			_Name.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
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
		if ( fieldName == "Name" )
			return _Name.IsDerivedFromParent();
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
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
public class HeroesBuildingLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroesBuildingLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<float> _statBufValue;
	private UndoRedo<float> _discount;
	private UndoRedo<int> _fameReqDecr;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Прибавка стата на 36 уровне" )]
	public float statBufValue { get { return _statBufValue.Get(); } set { _statBufValue.Set( value ); } }

	[Description( "Скидка на покупку героев роли в %" )]
	public float discount { get { return _discount.Get(); } set { _discount.Set( value ); } }

	[Description( "Снижение требования к уровню замка для героев роли" )]
	public int fameReqDecr { get { return _fameReqDecr.Get(); } set { _fameReqDecr.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_statBufValue = new UndoRedo<float>( owner, 0.0f );
		_discount = new UndoRedo<float>( owner, 0.0f );
		_fameReqDecr = new UndoRedo<int>( owner, 0 );
		_currentLevel.Changed += FireChangedEvent;
		_statBufValue.Changed += FireChangedEvent;
		_discount.Changed += FireChangedEvent;
		_fameReqDecr.Changed += FireChangedEvent;
	}

	public HeroesBuildingLevel()
	{
		Initialize( GetOwner() );
	}

	public HeroesBuildingLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroesBuildingLevel( DBResource owner, HeroesBuildingLevel source )
		: this(owner, source, true){}

	protected HeroesBuildingLevel( DBResource owner, HeroesBuildingLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_statBufValue = new UndoRedo<float>( owner, source.statBufValue );
		_discount = new UndoRedo<float>( owner, source.discount );
		_fameReqDecr = new UndoRedo<int>( owner, source.fameReqDecr );
		_currentLevel.Changed += FireChangedEvent;
		_statBufValue.Changed += FireChangedEvent;
		_discount.Changed += FireChangedEvent;
		_fameReqDecr.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroesBuildingLevel source = _source as HeroesBuildingLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroesBuildingLevel" );
		currentLevel = source.currentLevel;
		statBufValue = source.statBufValue;
		discount = source.discount;
		fameReqDecr = source.fameReqDecr;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroesBuildingLevel newParent = _newParent as HeroesBuildingLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_statBufValue.SetParent( newParent == null ? null : newParent._statBufValue );
		_discount.SetParent( newParent == null ? null : newParent._discount );
		_fameReqDecr.SetParent( newParent == null ? null : newParent._fameReqDecr );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_statBufValue.Reset();
		_discount.Reset();
		_fameReqDecr.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _statBufValue.IsDerivedFromParent()
			&& _discount.IsDerivedFromParent()
			&& _fameReqDecr.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "statBufValue" )
			_statBufValue.Reset();
		else if ( fieldName == "discount" )
			_discount.Reset();
		else if ( fieldName == "fameReqDecr" )
			_fameReqDecr.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "statBufValue" )
			return _statBufValue.IsDerivedFromParent();
		if ( fieldName == "discount" )
			return _discount.IsDerivedFromParent();
		if ( fieldName == "fameReqDecr" )
			return _fameReqDecr.IsDerivedFromParent();
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
public class HonorLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HonorLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _points;
	private UndoRedoDBPtr<DBRollTalentPercents> _rollTalentsReward;

	[Description( "Кол-во очков чести для перехода на следующий уровень" )]
	public float points { get { return _points.Get(); } set { _points.Set( value ); } }

	[Description( "Табличка процентов на ролл талантов в награду" )]
	public DBPtr<DBRollTalentPercents> rollTalentsReward { get { return _rollTalentsReward.Get(); } set { _rollTalentsReward.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_points = new UndoRedo<float>( owner, 0.0f );
		_rollTalentsReward = new UndoRedoDBPtr<DBRollTalentPercents>( owner );
		_points.Changed += FireChangedEvent;
		_rollTalentsReward.Changed += FireChangedEvent;
	}

	public HonorLevel()
	{
		Initialize( GetOwner() );
	}

	public HonorLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HonorLevel( DBResource owner, HonorLevel source )
		: this(owner, source, true){}

	protected HonorLevel( DBResource owner, HonorLevel source, bool fireEvent )
	{
		_points = new UndoRedo<float>( owner, source.points );
		_rollTalentsReward = new UndoRedoDBPtr<DBRollTalentPercents>( owner, source.rollTalentsReward );
		_points.Changed += FireChangedEvent;
		_rollTalentsReward.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HonorLevel source = _source as HonorLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HonorLevel" );
		points = source.points;
		rollTalentsReward = source.rollTalentsReward;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HonorLevel newParent = _newParent as HonorLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_points.SetParent( newParent == null ? null : newParent._points );
		_rollTalentsReward.SetParent( newParent == null ? null : newParent._rollTalentsReward );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_points.Reset();
		_rollTalentsReward.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_points.IsDerivedFromParent()
			&& _rollTalentsReward.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "points" )
			_points.Reset();
		else if ( fieldName == "rollTalentsReward" )
			_rollTalentsReward.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "points" )
			return _points.IsDerivedFromParent();
		if ( fieldName == "rollTalentsReward" )
			return _rollTalentsReward.IsDerivedFromParent();
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
public class HonorLevelTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HonorLevelTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<HonorLevel> _rewardPerLevel;

	[Description( "Уровни чести" )]
	public libdb.IChangeableList<HonorLevel> rewardPerLevel { get { return _rewardPerLevel; } set { _rewardPerLevel.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_rewardPerLevel = new UndoRedoAssignableList<HonorLevel>( owner );
		_rewardPerLevel.Changed += FireChangedEvent;
	}

	public HonorLevelTable()
	{
		Initialize( GetOwner() );
	}

	public HonorLevelTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HonorLevelTable( DBResource owner, HonorLevelTable source )
		: this(owner, source, true){}

	protected HonorLevelTable( DBResource owner, HonorLevelTable source, bool fireEvent )
	{
		_rewardPerLevel = new UndoRedoAssignableList<HonorLevel>( owner );
		_rewardPerLevel.Assign( source.rewardPerLevel );
		_rewardPerLevel.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HonorLevelTable source = _source as HonorLevelTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HonorLevelTable" );
		rewardPerLevel = source.rewardPerLevel;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HonorLevelTable newParent = _newParent as HonorLevelTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rewardPerLevel.SetParent( newParent == null ? null : newParent._rewardPerLevel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rewardPerLevel.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rewardPerLevel.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rewardPerLevel" )
			_rewardPerLevel.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rewardPerLevel" )
			return _rewardPerLevel.IsDerivedFromParent();
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
public class HouseLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HouseLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _currentMaxPopulation;
	private CycleType _cycle;
	private ResourcesTable _resourcesToProduce;
	private ResourcesTable _totalProduceCapacity;
	private ResourcesTable _boostPrice;
	private UndoRedo<float> _fameToProduce;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "На сколько увеличивается лимит population (НЕ инкриментально, а просто это значение для этого здания)" )]
	public int currentMaxPopulation { get { return _currentMaxPopulation.Get(); } set { _currentMaxPopulation.Set( value ); } }

	[Description( "Всегда только 1 цикл" )]
	public CycleType cycle { get { return _cycle; } set { _cycle.Assign( value ); } }

	[Description( "Ресурсов производится в единицу времени" )]
	public ResourcesTable resourcesToProduce { get { return _resourcesToProduce; } set { _resourcesToProduce.Assign( value ); } }

	[Description( "Вместимость домика" )]
	public ResourcesTable totalProduceCapacity { get { return _totalProduceCapacity; } set { _totalProduceCapacity.Assign( value ); } }

	[Description( "Стоимость ускорения производства" )]
	public ResourcesTable boostPrice { get { return _boostPrice; } set { _boostPrice.Assign( value ); } }

	[Description( "Сколько fame дадут за полный цикл" )]
	public float fameToProduce { get { return _fameToProduce.Get(); } set { _fameToProduce.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_currentMaxPopulation = new UndoRedo<int>( owner, 0 );
		_cycle = new CycleType( owner );
		_resourcesToProduce = new ResourcesTable( owner );
		_totalProduceCapacity = new ResourcesTable( owner );
		_boostPrice = new ResourcesTable( owner );
		_fameToProduce = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_currentMaxPopulation.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_totalProduceCapacity.Changed += FireChangedEvent;
		_boostPrice.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
	}

	public HouseLevel()
	{
		Initialize( GetOwner() );
	}

	public HouseLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HouseLevel( DBResource owner, HouseLevel source )
		: this(owner, source, true){}

	protected HouseLevel( DBResource owner, HouseLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_currentMaxPopulation = new UndoRedo<int>( owner, source.currentMaxPopulation );
		_cycle = new CycleType( owner, source.cycle );
		_resourcesToProduce = new ResourcesTable( owner, source.resourcesToProduce );
		_totalProduceCapacity = new ResourcesTable( owner, source.totalProduceCapacity );
		_boostPrice = new ResourcesTable( owner, source.boostPrice );
		_fameToProduce = new UndoRedo<float>( owner, source.fameToProduce );
		_currentLevel.Changed += FireChangedEvent;
		_currentMaxPopulation.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_totalProduceCapacity.Changed += FireChangedEvent;
		_boostPrice.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HouseLevel source = _source as HouseLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HouseLevel" );
		currentLevel = source.currentLevel;
		currentMaxPopulation = source.currentMaxPopulation;
		cycle = source.cycle;
		resourcesToProduce = source.resourcesToProduce;
		totalProduceCapacity = source.totalProduceCapacity;
		boostPrice = source.boostPrice;
		fameToProduce = source.fameToProduce;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HouseLevel newParent = _newParent as HouseLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_currentMaxPopulation.SetParent( newParent == null ? null : newParent._currentMaxPopulation );
		_cycle.SetParent( newParent == null ? null : newParent._cycle );
		_resourcesToProduce.SetParent( newParent == null ? null : newParent._resourcesToProduce );
		_totalProduceCapacity.SetParent( newParent == null ? null : newParent._totalProduceCapacity );
		_boostPrice.SetParent( newParent == null ? null : newParent._boostPrice );
		_fameToProduce.SetParent( newParent == null ? null : newParent._fameToProduce );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_currentMaxPopulation.Reset();
		_cycle.Reset();
		_resourcesToProduce.Reset();
		_totalProduceCapacity.Reset();
		_boostPrice.Reset();
		_fameToProduce.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _currentMaxPopulation.IsDerivedFromParent()
			&& _cycle.IsDerivedFromParent()
			&& _resourcesToProduce.IsDerivedFromParent()
			&& _totalProduceCapacity.IsDerivedFromParent()
			&& _boostPrice.IsDerivedFromParent()
			&& _fameToProduce.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "currentMaxPopulation" )
			_currentMaxPopulation.Reset();
		else if ( fieldName == "cycle" )
			_cycle.Reset();
		else if ( fieldName == "resourcesToProduce" )
			_resourcesToProduce.Reset();
		else if ( fieldName == "totalProduceCapacity" )
			_totalProduceCapacity.Reset();
		else if ( fieldName == "boostPrice" )
			_boostPrice.Reset();
		else if ( fieldName == "fameToProduce" )
			_fameToProduce.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "currentMaxPopulation" )
			return _currentMaxPopulation.IsDerivedFromParent();
		if ( fieldName == "cycle" )
			return _cycle.IsDerivedFromParent();
		if ( fieldName == "resourcesToProduce" )
			return _resourcesToProduce.IsDerivedFromParent();
		if ( fieldName == "totalProduceCapacity" )
			return _totalProduceCapacity.IsDerivedFromParent();
		if ( fieldName == "boostPrice" )
			return _boostPrice.IsDerivedFromParent();
		if ( fieldName == "fameToProduce" )
			return _fameToProduce.IsDerivedFromParent();
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
public class IntVec2 : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private IntVec2 __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public IntVec2()
	{
		Initialize( GetOwner() );
	}

	public IntVec2( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public IntVec2( DBResource owner, IntVec2 source )
		: this(owner, source, true){}

	protected IntVec2( DBResource owner, IntVec2 source, bool fireEvent )
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
		IntVec2 source = _source as IntVec2;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for IntVec2" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		IntVec2 newParent = _newParent as IntVec2;
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

[IndexField("leagueId")]
[Custom("Social")]
public class LeagueInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LeagueInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _minRating;
	private UndoRedo<int> _minLeaderPlace;
	private UndoRedo<int> _leagueId;

	[Description( "Минимальный рейтинг, начиная с которого начинается лига" )]
	public int minRating { get { return _minRating.Get(); } set { _minRating.Set( value ); } }

	[Description( "Минимальное место в таблице рейтинга для героя пятой лиги, начиная с которого рамка должна отображаться" )]
	public int minLeaderPlace { get { return _minLeaderPlace.Get(); } set { _minLeaderPlace.Set( value ); } }

	[Description( "Индекс лиги из SeasonLeagues" )]
	public int leagueId { get { return _leagueId.Get(); } set { _leagueId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minRating = new UndoRedo<int>( owner, 0 );
		_minLeaderPlace = new UndoRedo<int>( owner, 0 );
		_leagueId = new UndoRedo<int>( owner, 0 );
		_minRating.Changed += FireChangedEvent;
		_minLeaderPlace.Changed += FireChangedEvent;
		_leagueId.Changed += FireChangedEvent;
	}

	public LeagueInfo()
	{
		Initialize( GetOwner() );
	}

	public LeagueInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LeagueInfo( DBResource owner, LeagueInfo source )
		: this(owner, source, true){}

	protected LeagueInfo( DBResource owner, LeagueInfo source, bool fireEvent )
	{
		_minRating = new UndoRedo<int>( owner, source.minRating );
		_minLeaderPlace = new UndoRedo<int>( owner, source.minLeaderPlace );
		_leagueId = new UndoRedo<int>( owner, source.leagueId );
		_minRating.Changed += FireChangedEvent;
		_minLeaderPlace.Changed += FireChangedEvent;
		_leagueId.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LeagueInfo source = _source as LeagueInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LeagueInfo" );
		minRating = source.minRating;
		minLeaderPlace = source.minLeaderPlace;
		leagueId = source.leagueId;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LeagueInfo newParent = _newParent as LeagueInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minRating.SetParent( newParent == null ? null : newParent._minRating );
		_minLeaderPlace.SetParent( newParent == null ? null : newParent._minLeaderPlace );
		_leagueId.SetParent( newParent == null ? null : newParent._leagueId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minRating.Reset();
		_minLeaderPlace.Reset();
		_leagueId.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minRating.IsDerivedFromParent()
			&& _minLeaderPlace.IsDerivedFromParent()
			&& _leagueId.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minRating" )
			_minRating.Reset();
		else if ( fieldName == "minLeaderPlace" )
			_minLeaderPlace.Reset();
		else if ( fieldName == "leagueId" )
			_leagueId.Reset();
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
		if ( fieldName == "minLeaderPlace" )
			return _minLeaderPlace.IsDerivedFromParent();
		if ( fieldName == "leagueId" )
			return _leagueId.IsDerivedFromParent();
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
public class LevelToResources : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LevelToResources __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<FameLevelRes> _resourcesPerLevel;

	[Description( "Таблица ресурсов, выдаваемых игроку за новый уровень лорда" )]
	public libdb.IChangeableList<FameLevelRes> resourcesPerLevel { get { return _resourcesPerLevel; } set { _resourcesPerLevel.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_resourcesPerLevel = new UndoRedoAssignableList<FameLevelRes>( owner );
		_resourcesPerLevel.Changed += FireChangedEvent;
	}

	public LevelToResources()
	{
		Initialize( GetOwner() );
	}

	public LevelToResources( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LevelToResources( DBResource owner, LevelToResources source )
		: this(owner, source, true){}

	protected LevelToResources( DBResource owner, LevelToResources source, bool fireEvent )
	{
		_resourcesPerLevel = new UndoRedoAssignableList<FameLevelRes>( owner );
		_resourcesPerLevel.Assign( source.resourcesPerLevel );
		_resourcesPerLevel.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LevelToResources source = _source as LevelToResources;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LevelToResources" );
		resourcesPerLevel = source.resourcesPerLevel;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LevelToResources newParent = _newParent as LevelToResources;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_resourcesPerLevel.SetParent( newParent == null ? null : newParent._resourcesPerLevel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_resourcesPerLevel.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_resourcesPerLevel.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "resourcesPerLevel" )
			_resourcesPerLevel.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "resourcesPerLevel" )
			return _resourcesPerLevel.IsDerivedFromParent();
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
public class LibraryLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LibraryLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _additionalTalentSlots;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "На сколько увеличивается максимальное кол-во талантов в библиотеке" )]
	public int additionalTalentSlots { get { return _additionalTalentSlots.Get(); } set { _additionalTalentSlots.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_additionalTalentSlots = new UndoRedo<int>( owner, 0 );
		_currentLevel.Changed += FireChangedEvent;
		_additionalTalentSlots.Changed += FireChangedEvent;
	}

	public LibraryLevel()
	{
		Initialize( GetOwner() );
	}

	public LibraryLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LibraryLevel( DBResource owner, LibraryLevel source )
		: this(owner, source, true){}

	protected LibraryLevel( DBResource owner, LibraryLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_additionalTalentSlots = new UndoRedo<int>( owner, source.additionalTalentSlots );
		_currentLevel.Changed += FireChangedEvent;
		_additionalTalentSlots.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LibraryLevel source = _source as LibraryLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LibraryLevel" );
		currentLevel = source.currentLevel;
		additionalTalentSlots = source.additionalTalentSlots;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LibraryLevel newParent = _newParent as LibraryLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_additionalTalentSlots.SetParent( newParent == null ? null : newParent._additionalTalentSlots );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_additionalTalentSlots.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _additionalTalentSlots.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "additionalTalentSlots" )
			_additionalTalentSlots.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "additionalTalentSlots" )
			return _additionalTalentSlots.IsDerivedFromParent();
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
public class MapGrade : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MapGrade __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<SectionsSet> _Sections;
	private ResourcesTable _price;
	private UndoRedoAssignableList<BuildedConstruction> _BuildedConstructions;
	private UndoRedo<int> _sectionsCount;

	[Description( "List of sections for current grade. Default state is open for building and decoration." )]
	public DBPtr<SectionsSet> Sections { get { return _Sections.Get(); } set { _Sections.Set( value ); } }

	public ResourcesTable price { get { return _price; } set { _price.Assign( value ); } }

	public libdb.IChangeableList<BuildedConstruction> BuildedConstructions { get { return _BuildedConstructions; } set { _BuildedConstructions.Assign( value ); } }

	public int sectionsCount { get { return _sectionsCount.Get(); } set { _sectionsCount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Sections = new UndoRedoDBPtr<SectionsSet>( owner );
		_price = new ResourcesTable( owner );
		_BuildedConstructions = new UndoRedoAssignableList<BuildedConstruction>( owner );
		_sectionsCount = new UndoRedo<int>( owner, 0 );
		_Sections.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
		_BuildedConstructions.Changed += FireChangedEvent;
		_sectionsCount.Changed += FireChangedEvent;
	}

	public MapGrade()
	{
		Initialize( GetOwner() );
	}

	public MapGrade( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MapGrade( DBResource owner, MapGrade source )
		: this(owner, source, true){}

	protected MapGrade( DBResource owner, MapGrade source, bool fireEvent )
	{
		_Sections = new UndoRedoDBPtr<SectionsSet>( owner, source.Sections );
		_price = new ResourcesTable( owner, source.price );
		_BuildedConstructions = new UndoRedoAssignableList<BuildedConstruction>( owner );
		_BuildedConstructions.Assign( source.BuildedConstructions );
		_sectionsCount = new UndoRedo<int>( owner, source.sectionsCount );
		_Sections.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
		_BuildedConstructions.Changed += FireChangedEvent;
		_sectionsCount.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MapGrade source = _source as MapGrade;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MapGrade" );
		Sections = source.Sections;
		price = source.price;
		BuildedConstructions = source.BuildedConstructions;
		sectionsCount = source.sectionsCount;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MapGrade newParent = _newParent as MapGrade;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Sections.SetParent( newParent == null ? null : newParent._Sections );
		_price.SetParent( newParent == null ? null : newParent._price );
		_BuildedConstructions.SetParent( newParent == null ? null : newParent._BuildedConstructions );
		_sectionsCount.SetParent( newParent == null ? null : newParent._sectionsCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Sections.Reset();
		_price.Reset();
		_BuildedConstructions.Reset();
		_sectionsCount.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Sections.IsDerivedFromParent()
			&& _price.IsDerivedFromParent()
			&& _BuildedConstructions.IsDerivedFromParent()
			&& _sectionsCount.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Sections" )
			_Sections.Reset();
		else if ( fieldName == "price" )
			_price.Reset();
		else if ( fieldName == "BuildedConstructions" )
			_BuildedConstructions.Reset();
		else if ( fieldName == "sectionsCount" )
			_sectionsCount.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Sections" )
			return _Sections.IsDerivedFromParent();
		if ( fieldName == "price" )
			return _price.IsDerivedFromParent();
		if ( fieldName == "BuildedConstructions" )
			return _BuildedConstructions.IsDerivedFromParent();
		if ( fieldName == "sectionsCount" )
			return _sectionsCount.IsDerivedFromParent();
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
public class MarketingEvents : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MarketingEvents __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<PremiumEvent> _premiumAccEvent;
	private UndoRedoDBPtr<BuyHeroEvent> _buyHero;
	private UndoRedoDBPtr<FirstBuyEvent> _firstBuy;
	private UndoRedoDBPtr<BuySpecialHeroEvent> _buySpecialHero;
	private UndoRedoDBPtr<BuyGoldHeroEvent> _buyGoldHero;
	private UndoRedoDBPtr<BuildGoldenLodgeEvent> _buildGoldenLodge;
	private UndoRedoDBPtr<BuyGoldenLodgeEvent> _buyGoldenLodge;
	private UndoRedoDBPtr<BuySteamGoldEvent> _buySteamGold;
	private UndoRedoDBPtr<BuySteamDLCEvent> _buySteamDLC;
	private UndoRedoDBPtr<BuyAeriaGoldEvent> _buyAeriaGold;
	private UndoRedoDBPtr<BuyArcGamesGoldEvent> _buyArcGamesGold;
	private UndoRedoDBPtr<BuyZZimaGoldEvent> _buyZZimaGold;
	private UndoRedoAssignableList<DBPtr<GoldLampEvent>> _lampEvents;
	private UndoRedoDBPtr<BuyTournamentTicketEvent> _tournamentEvent;
	private UndoRedoDBPtr<TournamentInProgressEvent> _tournamentInProgressEvent;
	private UndoRedoDBPtr<BuyFlagEvent> _buyFlag;
	private UndoRedoDBPtr<BeginnersPack> _beginnersPack;
	private UndoRedoDBPtr<UpgradeHeroTalentsEvent> _upgradeHeroTalentsEvent;
	private UndoRedoDBPtr<PrimeArenaEvent> _primeArenaEvent;

	public DBPtr<PremiumEvent> premiumAccEvent { get { return _premiumAccEvent.Get(); } set { _premiumAccEvent.Set( value ); } }

	public DBPtr<BuyHeroEvent> buyHero { get { return _buyHero.Get(); } set { _buyHero.Set( value ); } }

	public DBPtr<FirstBuyEvent> firstBuy { get { return _firstBuy.Get(); } set { _firstBuy.Set( value ); } }

	public DBPtr<BuySpecialHeroEvent> buySpecialHero { get { return _buySpecialHero.Get(); } set { _buySpecialHero.Set( value ); } }

	public DBPtr<BuyGoldHeroEvent> buyGoldHero { get { return _buyGoldHero.Get(); } set { _buyGoldHero.Set( value ); } }

	public DBPtr<BuildGoldenLodgeEvent> buildGoldenLodge { get { return _buildGoldenLodge.Get(); } set { _buildGoldenLodge.Set( value ); } }

	public DBPtr<BuyGoldenLodgeEvent> buyGoldenLodge { get { return _buyGoldenLodge.Get(); } set { _buyGoldenLodge.Set( value ); } }

	public DBPtr<BuySteamGoldEvent> buySteamGold { get { return _buySteamGold.Get(); } set { _buySteamGold.Set( value ); } }

	public DBPtr<BuySteamDLCEvent> buySteamDLC { get { return _buySteamDLC.Get(); } set { _buySteamDLC.Set( value ); } }

	public DBPtr<BuyAeriaGoldEvent> buyAeriaGold { get { return _buyAeriaGold.Get(); } set { _buyAeriaGold.Set( value ); } }

	public DBPtr<BuyArcGamesGoldEvent> buyArcGamesGold { get { return _buyArcGamesGold.Get(); } set { _buyArcGamesGold.Set( value ); } }

	public DBPtr<BuyZZimaGoldEvent> buyZZimaGold { get { return _buyZZimaGold.Get(); } set { _buyZZimaGold.Set( value ); } }

	public libdb.IChangeableList<DBPtr<GoldLampEvent>> lampEvents { get { return _lampEvents; } set { _lampEvents.Assign( value ); } }

	public DBPtr<BuyTournamentTicketEvent> tournamentEvent { get { return _tournamentEvent.Get(); } set { _tournamentEvent.Set( value ); } }

	public DBPtr<TournamentInProgressEvent> tournamentInProgressEvent { get { return _tournamentInProgressEvent.Get(); } set { _tournamentInProgressEvent.Set( value ); } }

	public DBPtr<BuyFlagEvent> buyFlag { get { return _buyFlag.Get(); } set { _buyFlag.Set( value ); } }

	public DBPtr<BeginnersPack> beginnersPack { get { return _beginnersPack.Get(); } set { _beginnersPack.Set( value ); } }

	public DBPtr<UpgradeHeroTalentsEvent> upgradeHeroTalentsEvent { get { return _upgradeHeroTalentsEvent.Get(); } set { _upgradeHeroTalentsEvent.Set( value ); } }

	public DBPtr<PrimeArenaEvent> primeArenaEvent { get { return _primeArenaEvent.Get(); } set { _primeArenaEvent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_premiumAccEvent = new UndoRedoDBPtr<PremiumEvent>( owner );
		_buyHero = new UndoRedoDBPtr<BuyHeroEvent>( owner );
		_firstBuy = new UndoRedoDBPtr<FirstBuyEvent>( owner );
		_buySpecialHero = new UndoRedoDBPtr<BuySpecialHeroEvent>( owner );
		_buyGoldHero = new UndoRedoDBPtr<BuyGoldHeroEvent>( owner );
		_buildGoldenLodge = new UndoRedoDBPtr<BuildGoldenLodgeEvent>( owner );
		_buyGoldenLodge = new UndoRedoDBPtr<BuyGoldenLodgeEvent>( owner );
		_buySteamGold = new UndoRedoDBPtr<BuySteamGoldEvent>( owner );
		_buySteamDLC = new UndoRedoDBPtr<BuySteamDLCEvent>( owner );
		_buyAeriaGold = new UndoRedoDBPtr<BuyAeriaGoldEvent>( owner );
		_buyArcGamesGold = new UndoRedoDBPtr<BuyArcGamesGoldEvent>( owner );
		_buyZZimaGold = new UndoRedoDBPtr<BuyZZimaGoldEvent>( owner );
		_lampEvents = new UndoRedoAssignableList<DBPtr<GoldLampEvent>>( owner );
		_tournamentEvent = new UndoRedoDBPtr<BuyTournamentTicketEvent>( owner );
		_tournamentInProgressEvent = new UndoRedoDBPtr<TournamentInProgressEvent>( owner );
		_buyFlag = new UndoRedoDBPtr<BuyFlagEvent>( owner );
		_beginnersPack = new UndoRedoDBPtr<BeginnersPack>( owner );
		_upgradeHeroTalentsEvent = new UndoRedoDBPtr<UpgradeHeroTalentsEvent>( owner );
		_primeArenaEvent = new UndoRedoDBPtr<PrimeArenaEvent>( owner );
		_premiumAccEvent.Changed += FireChangedEvent;
		_buyHero.Changed += FireChangedEvent;
		_firstBuy.Changed += FireChangedEvent;
		_buySpecialHero.Changed += FireChangedEvent;
		_buyGoldHero.Changed += FireChangedEvent;
		_buildGoldenLodge.Changed += FireChangedEvent;
		_buyGoldenLodge.Changed += FireChangedEvent;
		_buySteamGold.Changed += FireChangedEvent;
		_buySteamDLC.Changed += FireChangedEvent;
		_buyAeriaGold.Changed += FireChangedEvent;
		_buyArcGamesGold.Changed += FireChangedEvent;
		_buyZZimaGold.Changed += FireChangedEvent;
		_lampEvents.Changed += FireChangedEvent;
		_tournamentEvent.Changed += FireChangedEvent;
		_tournamentInProgressEvent.Changed += FireChangedEvent;
		_buyFlag.Changed += FireChangedEvent;
		_beginnersPack.Changed += FireChangedEvent;
		_upgradeHeroTalentsEvent.Changed += FireChangedEvent;
		_primeArenaEvent.Changed += FireChangedEvent;
	}

	public MarketingEvents()
	{
		Initialize( GetOwner() );
	}

	public MarketingEvents( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MarketingEvents( DBResource owner, MarketingEvents source )
		: this(owner, source, true){}

	protected MarketingEvents( DBResource owner, MarketingEvents source, bool fireEvent )
	{
		_premiumAccEvent = new UndoRedoDBPtr<PremiumEvent>( owner, source.premiumAccEvent );
		_buyHero = new UndoRedoDBPtr<BuyHeroEvent>( owner, source.buyHero );
		_firstBuy = new UndoRedoDBPtr<FirstBuyEvent>( owner, source.firstBuy );
		_buySpecialHero = new UndoRedoDBPtr<BuySpecialHeroEvent>( owner, source.buySpecialHero );
		_buyGoldHero = new UndoRedoDBPtr<BuyGoldHeroEvent>( owner, source.buyGoldHero );
		_buildGoldenLodge = new UndoRedoDBPtr<BuildGoldenLodgeEvent>( owner, source.buildGoldenLodge );
		_buyGoldenLodge = new UndoRedoDBPtr<BuyGoldenLodgeEvent>( owner, source.buyGoldenLodge );
		_buySteamGold = new UndoRedoDBPtr<BuySteamGoldEvent>( owner, source.buySteamGold );
		_buySteamDLC = new UndoRedoDBPtr<BuySteamDLCEvent>( owner, source.buySteamDLC );
		_buyAeriaGold = new UndoRedoDBPtr<BuyAeriaGoldEvent>( owner, source.buyAeriaGold );
		_buyArcGamesGold = new UndoRedoDBPtr<BuyArcGamesGoldEvent>( owner, source.buyArcGamesGold );
		_buyZZimaGold = new UndoRedoDBPtr<BuyZZimaGoldEvent>( owner, source.buyZZimaGold );
		_lampEvents = new UndoRedoAssignableList<DBPtr<GoldLampEvent>>( owner );
		_lampEvents.Assign( source.lampEvents );
		_tournamentEvent = new UndoRedoDBPtr<BuyTournamentTicketEvent>( owner, source.tournamentEvent );
		_tournamentInProgressEvent = new UndoRedoDBPtr<TournamentInProgressEvent>( owner, source.tournamentInProgressEvent );
		_buyFlag = new UndoRedoDBPtr<BuyFlagEvent>( owner, source.buyFlag );
		_beginnersPack = new UndoRedoDBPtr<BeginnersPack>( owner, source.beginnersPack );
		_upgradeHeroTalentsEvent = new UndoRedoDBPtr<UpgradeHeroTalentsEvent>( owner, source.upgradeHeroTalentsEvent );
		_primeArenaEvent = new UndoRedoDBPtr<PrimeArenaEvent>( owner, source.primeArenaEvent );
		_premiumAccEvent.Changed += FireChangedEvent;
		_buyHero.Changed += FireChangedEvent;
		_firstBuy.Changed += FireChangedEvent;
		_buySpecialHero.Changed += FireChangedEvent;
		_buyGoldHero.Changed += FireChangedEvent;
		_buildGoldenLodge.Changed += FireChangedEvent;
		_buyGoldenLodge.Changed += FireChangedEvent;
		_buySteamGold.Changed += FireChangedEvent;
		_buySteamDLC.Changed += FireChangedEvent;
		_buyAeriaGold.Changed += FireChangedEvent;
		_buyArcGamesGold.Changed += FireChangedEvent;
		_buyZZimaGold.Changed += FireChangedEvent;
		_lampEvents.Changed += FireChangedEvent;
		_tournamentEvent.Changed += FireChangedEvent;
		_tournamentInProgressEvent.Changed += FireChangedEvent;
		_buyFlag.Changed += FireChangedEvent;
		_beginnersPack.Changed += FireChangedEvent;
		_upgradeHeroTalentsEvent.Changed += FireChangedEvent;
		_primeArenaEvent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MarketingEvents source = _source as MarketingEvents;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MarketingEvents" );
		premiumAccEvent = source.premiumAccEvent;
		buyHero = source.buyHero;
		firstBuy = source.firstBuy;
		buySpecialHero = source.buySpecialHero;
		buyGoldHero = source.buyGoldHero;
		buildGoldenLodge = source.buildGoldenLodge;
		buyGoldenLodge = source.buyGoldenLodge;
		buySteamGold = source.buySteamGold;
		buySteamDLC = source.buySteamDLC;
		buyAeriaGold = source.buyAeriaGold;
		buyArcGamesGold = source.buyArcGamesGold;
		buyZZimaGold = source.buyZZimaGold;
		lampEvents = source.lampEvents;
		tournamentEvent = source.tournamentEvent;
		tournamentInProgressEvent = source.tournamentInProgressEvent;
		buyFlag = source.buyFlag;
		beginnersPack = source.beginnersPack;
		upgradeHeroTalentsEvent = source.upgradeHeroTalentsEvent;
		primeArenaEvent = source.primeArenaEvent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MarketingEvents newParent = _newParent as MarketingEvents;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_premiumAccEvent.SetParent( newParent == null ? null : newParent._premiumAccEvent );
		_buyHero.SetParent( newParent == null ? null : newParent._buyHero );
		_firstBuy.SetParent( newParent == null ? null : newParent._firstBuy );
		_buySpecialHero.SetParent( newParent == null ? null : newParent._buySpecialHero );
		_buyGoldHero.SetParent( newParent == null ? null : newParent._buyGoldHero );
		_buildGoldenLodge.SetParent( newParent == null ? null : newParent._buildGoldenLodge );
		_buyGoldenLodge.SetParent( newParent == null ? null : newParent._buyGoldenLodge );
		_buySteamGold.SetParent( newParent == null ? null : newParent._buySteamGold );
		_buySteamDLC.SetParent( newParent == null ? null : newParent._buySteamDLC );
		_buyAeriaGold.SetParent( newParent == null ? null : newParent._buyAeriaGold );
		_buyArcGamesGold.SetParent( newParent == null ? null : newParent._buyArcGamesGold );
		_buyZZimaGold.SetParent( newParent == null ? null : newParent._buyZZimaGold );
		_lampEvents.SetParent( newParent == null ? null : newParent._lampEvents );
		_tournamentEvent.SetParent( newParent == null ? null : newParent._tournamentEvent );
		_tournamentInProgressEvent.SetParent( newParent == null ? null : newParent._tournamentInProgressEvent );
		_buyFlag.SetParent( newParent == null ? null : newParent._buyFlag );
		_beginnersPack.SetParent( newParent == null ? null : newParent._beginnersPack );
		_upgradeHeroTalentsEvent.SetParent( newParent == null ? null : newParent._upgradeHeroTalentsEvent );
		_primeArenaEvent.SetParent( newParent == null ? null : newParent._primeArenaEvent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_premiumAccEvent.Reset();
		_buyHero.Reset();
		_firstBuy.Reset();
		_buySpecialHero.Reset();
		_buyGoldHero.Reset();
		_buildGoldenLodge.Reset();
		_buyGoldenLodge.Reset();
		_buySteamGold.Reset();
		_buySteamDLC.Reset();
		_buyAeriaGold.Reset();
		_buyArcGamesGold.Reset();
		_buyZZimaGold.Reset();
		_lampEvents.Reset();
		_tournamentEvent.Reset();
		_tournamentInProgressEvent.Reset();
		_buyFlag.Reset();
		_beginnersPack.Reset();
		_upgradeHeroTalentsEvent.Reset();
		_primeArenaEvent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_premiumAccEvent.IsDerivedFromParent()
			&& _buyHero.IsDerivedFromParent()
			&& _firstBuy.IsDerivedFromParent()
			&& _buySpecialHero.IsDerivedFromParent()
			&& _buyGoldHero.IsDerivedFromParent()
			&& _buildGoldenLodge.IsDerivedFromParent()
			&& _buyGoldenLodge.IsDerivedFromParent()
			&& _buySteamGold.IsDerivedFromParent()
			&& _buySteamDLC.IsDerivedFromParent()
			&& _buyAeriaGold.IsDerivedFromParent()
			&& _buyArcGamesGold.IsDerivedFromParent()
			&& _buyZZimaGold.IsDerivedFromParent()
			&& _lampEvents.IsDerivedFromParent()
			&& _tournamentEvent.IsDerivedFromParent()
			&& _tournamentInProgressEvent.IsDerivedFromParent()
			&& _buyFlag.IsDerivedFromParent()
			&& _beginnersPack.IsDerivedFromParent()
			&& _upgradeHeroTalentsEvent.IsDerivedFromParent()
			&& _primeArenaEvent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "premiumAccEvent" )
			_premiumAccEvent.Reset();
		else if ( fieldName == "buyHero" )
			_buyHero.Reset();
		else if ( fieldName == "firstBuy" )
			_firstBuy.Reset();
		else if ( fieldName == "buySpecialHero" )
			_buySpecialHero.Reset();
		else if ( fieldName == "buyGoldHero" )
			_buyGoldHero.Reset();
		else if ( fieldName == "buildGoldenLodge" )
			_buildGoldenLodge.Reset();
		else if ( fieldName == "buyGoldenLodge" )
			_buyGoldenLodge.Reset();
		else if ( fieldName == "buySteamGold" )
			_buySteamGold.Reset();
		else if ( fieldName == "buySteamDLC" )
			_buySteamDLC.Reset();
		else if ( fieldName == "buyAeriaGold" )
			_buyAeriaGold.Reset();
		else if ( fieldName == "buyArcGamesGold" )
			_buyArcGamesGold.Reset();
		else if ( fieldName == "buyZZimaGold" )
			_buyZZimaGold.Reset();
		else if ( fieldName == "lampEvents" )
			_lampEvents.Reset();
		else if ( fieldName == "tournamentEvent" )
			_tournamentEvent.Reset();
		else if ( fieldName == "tournamentInProgressEvent" )
			_tournamentInProgressEvent.Reset();
		else if ( fieldName == "buyFlag" )
			_buyFlag.Reset();
		else if ( fieldName == "beginnersPack" )
			_beginnersPack.Reset();
		else if ( fieldName == "upgradeHeroTalentsEvent" )
			_upgradeHeroTalentsEvent.Reset();
		else if ( fieldName == "primeArenaEvent" )
			_primeArenaEvent.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "premiumAccEvent" )
			return _premiumAccEvent.IsDerivedFromParent();
		if ( fieldName == "buyHero" )
			return _buyHero.IsDerivedFromParent();
		if ( fieldName == "firstBuy" )
			return _firstBuy.IsDerivedFromParent();
		if ( fieldName == "buySpecialHero" )
			return _buySpecialHero.IsDerivedFromParent();
		if ( fieldName == "buyGoldHero" )
			return _buyGoldHero.IsDerivedFromParent();
		if ( fieldName == "buildGoldenLodge" )
			return _buildGoldenLodge.IsDerivedFromParent();
		if ( fieldName == "buyGoldenLodge" )
			return _buyGoldenLodge.IsDerivedFromParent();
		if ( fieldName == "buySteamGold" )
			return _buySteamGold.IsDerivedFromParent();
		if ( fieldName == "buySteamDLC" )
			return _buySteamDLC.IsDerivedFromParent();
		if ( fieldName == "buyAeriaGold" )
			return _buyAeriaGold.IsDerivedFromParent();
		if ( fieldName == "buyArcGamesGold" )
			return _buyArcGamesGold.IsDerivedFromParent();
		if ( fieldName == "buyZZimaGold" )
			return _buyZZimaGold.IsDerivedFromParent();
		if ( fieldName == "lampEvents" )
			return _lampEvents.IsDerivedFromParent();
		if ( fieldName == "tournamentEvent" )
			return _tournamentEvent.IsDerivedFromParent();
		if ( fieldName == "tournamentInProgressEvent" )
			return _tournamentInProgressEvent.IsDerivedFromParent();
		if ( fieldName == "buyFlag" )
			return _buyFlag.IsDerivedFromParent();
		if ( fieldName == "beginnersPack" )
			return _beginnersPack.IsDerivedFromParent();
		if ( fieldName == "upgradeHeroTalentsEvent" )
			return _upgradeHeroTalentsEvent.IsDerivedFromParent();
		if ( fieldName == "primeArenaEvent" )
			return _primeArenaEvent.IsDerivedFromParent();
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
public class PineTreeLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PineTreeLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private CycleType _cycle;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Всегда только 1 цикл" )]
	public CycleType cycle { get { return _cycle; } set { _cycle.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_cycle = new CycleType( owner );
		_currentLevel.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
	}

	public PineTreeLevel()
	{
		Initialize( GetOwner() );
	}

	public PineTreeLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PineTreeLevel( DBResource owner, PineTreeLevel source )
		: this(owner, source, true){}

	protected PineTreeLevel( DBResource owner, PineTreeLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_cycle = new CycleType( owner, source.cycle );
		_currentLevel.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PineTreeLevel source = _source as PineTreeLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PineTreeLevel" );
		currentLevel = source.currentLevel;
		cycle = source.cycle;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PineTreeLevel newParent = _newParent as PineTreeLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_cycle.SetParent( newParent == null ? null : newParent._cycle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_cycle.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _cycle.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "cycle" )
			_cycle.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "cycle" )
			return _cycle.IsDerivedFromParent();
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
public class ProductionLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ProductionLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedoAssignableList<CycleType> _cycles;
	private ResourcesTable _resourcesToProduce;
	private ResourcesTable _totalProduceCapacity;
	private ResourcesTable _boostPrice;
	private UndoRedo<float> _fameToProduce;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Циклы" )]
	public libdb.IChangeableList<CycleType> cycles { get { return _cycles; } set { _cycles.Assign( value ); } }

	[Description( "Ресурсов производится в единицу времени" )]
	public ResourcesTable resourcesToProduce { get { return _resourcesToProduce; } set { _resourcesToProduce.Assign( value ); } }

	[Description( "Вместимость домика" )]
	public ResourcesTable totalProduceCapacity { get { return _totalProduceCapacity; } set { _totalProduceCapacity.Assign( value ); } }

	[Description( "Стоимость ускорения производства" )]
	public ResourcesTable boostPrice { get { return _boostPrice; } set { _boostPrice.Assign( value ); } }

	[Description( "Сколько fame дадут за полный цикл" )]
	public float fameToProduce { get { return _fameToProduce.Get(); } set { _fameToProduce.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_cycles = new UndoRedoAssignableList<CycleType>( owner );
		_resourcesToProduce = new ResourcesTable( owner );
		_totalProduceCapacity = new ResourcesTable( owner );
		_boostPrice = new ResourcesTable( owner );
		_fameToProduce = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_cycles.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_totalProduceCapacity.Changed += FireChangedEvent;
		_boostPrice.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
	}

	public ProductionLevel()
	{
		Initialize( GetOwner() );
	}

	public ProductionLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ProductionLevel( DBResource owner, ProductionLevel source )
		: this(owner, source, true){}

	protected ProductionLevel( DBResource owner, ProductionLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_cycles = new UndoRedoAssignableList<CycleType>( owner );
		_cycles.Assign( source.cycles );
		_resourcesToProduce = new ResourcesTable( owner, source.resourcesToProduce );
		_totalProduceCapacity = new ResourcesTable( owner, source.totalProduceCapacity );
		_boostPrice = new ResourcesTable( owner, source.boostPrice );
		_fameToProduce = new UndoRedo<float>( owner, source.fameToProduce );
		_currentLevel.Changed += FireChangedEvent;
		_cycles.Changed += FireChangedEvent;
		_resourcesToProduce.Changed += FireChangedEvent;
		_totalProduceCapacity.Changed += FireChangedEvent;
		_boostPrice.Changed += FireChangedEvent;
		_fameToProduce.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ProductionLevel source = _source as ProductionLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ProductionLevel" );
		currentLevel = source.currentLevel;
		cycles = source.cycles;
		resourcesToProduce = source.resourcesToProduce;
		totalProduceCapacity = source.totalProduceCapacity;
		boostPrice = source.boostPrice;
		fameToProduce = source.fameToProduce;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ProductionLevel newParent = _newParent as ProductionLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_cycles.SetParent( newParent == null ? null : newParent._cycles );
		_resourcesToProduce.SetParent( newParent == null ? null : newParent._resourcesToProduce );
		_totalProduceCapacity.SetParent( newParent == null ? null : newParent._totalProduceCapacity );
		_boostPrice.SetParent( newParent == null ? null : newParent._boostPrice );
		_fameToProduce.SetParent( newParent == null ? null : newParent._fameToProduce );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_cycles.Reset();
		_resourcesToProduce.Reset();
		_totalProduceCapacity.Reset();
		_boostPrice.Reset();
		_fameToProduce.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _cycles.IsDerivedFromParent()
			&& _resourcesToProduce.IsDerivedFromParent()
			&& _totalProduceCapacity.IsDerivedFromParent()
			&& _boostPrice.IsDerivedFromParent()
			&& _fameToProduce.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "cycles" )
			_cycles.Reset();
		else if ( fieldName == "resourcesToProduce" )
			_resourcesToProduce.Reset();
		else if ( fieldName == "totalProduceCapacity" )
			_totalProduceCapacity.Reset();
		else if ( fieldName == "boostPrice" )
			_boostPrice.Reset();
		else if ( fieldName == "fameToProduce" )
			_fameToProduce.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "cycles" )
			return _cycles.IsDerivedFromParent();
		if ( fieldName == "resourcesToProduce" )
			return _resourcesToProduce.IsDerivedFromParent();
		if ( fieldName == "totalProduceCapacity" )
			return _totalProduceCapacity.IsDerivedFromParent();
		if ( fieldName == "boostPrice" )
			return _boostPrice.IsDerivedFromParent();
		if ( fieldName == "fameToProduce" )
			return _fameToProduce.IsDerivedFromParent();
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
public class RarityToLevelAndPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RarityToLevelAndPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<int> _levelToPrice;

	public libdb.IChangeableList<int> levelToPrice { get { return _levelToPrice; } set { _levelToPrice.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_levelToPrice = new UndoRedoList<int>( owner );
		_levelToPrice.Changed += FireChangedEvent;
	}

	public RarityToLevelAndPrice()
	{
		Initialize( GetOwner() );
	}

	public RarityToLevelAndPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RarityToLevelAndPrice( DBResource owner, RarityToLevelAndPrice source )
		: this(owner, source, true){}

	protected RarityToLevelAndPrice( DBResource owner, RarityToLevelAndPrice source, bool fireEvent )
	{
		_levelToPrice = new UndoRedoList<int>( owner );
		_levelToPrice.Assign( source.levelToPrice );
		_levelToPrice.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RarityToLevelAndPrice source = _source as RarityToLevelAndPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RarityToLevelAndPrice" );
		levelToPrice = source.levelToPrice;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RarityToLevelAndPrice newParent = _newParent as RarityToLevelAndPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_levelToPrice.SetParent( newParent == null ? null : newParent._levelToPrice );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_levelToPrice.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_levelToPrice.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "levelToPrice" )
			_levelToPrice.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "levelToPrice" )
			return _levelToPrice.IsDerivedFromParent();
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
public class RarityToPointsAndLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RarityToPointsAndLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<int> _levelToPoints;
	private UndoRedo<int> _refinePointsCap;

	[Description( "Соотношение количество очков улучшения с уровнем таланта (в порядке возрастания)" )]
	public libdb.IChangeableList<int> levelToPoints { get { return _levelToPoints; } set { _levelToPoints.Assign( value ); } }

	[Description( "Лимит очков, выше которого нельзя улучшить талант" )]
	public int refinePointsCap { get { return _refinePointsCap.Get(); } set { _refinePointsCap.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_levelToPoints = new UndoRedoList<int>( owner );
		_refinePointsCap = new UndoRedo<int>( owner, 0 );
		_levelToPoints.Changed += FireChangedEvent;
		_refinePointsCap.Changed += FireChangedEvent;
	}

	public RarityToPointsAndLevel()
	{
		Initialize( GetOwner() );
	}

	public RarityToPointsAndLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RarityToPointsAndLevel( DBResource owner, RarityToPointsAndLevel source )
		: this(owner, source, true){}

	protected RarityToPointsAndLevel( DBResource owner, RarityToPointsAndLevel source, bool fireEvent )
	{
		_levelToPoints = new UndoRedoList<int>( owner );
		_levelToPoints.Assign( source.levelToPoints );
		_refinePointsCap = new UndoRedo<int>( owner, source.refinePointsCap );
		_levelToPoints.Changed += FireChangedEvent;
		_refinePointsCap.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RarityToPointsAndLevel source = _source as RarityToPointsAndLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RarityToPointsAndLevel" );
		levelToPoints = source.levelToPoints;
		refinePointsCap = source.refinePointsCap;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RarityToPointsAndLevel newParent = _newParent as RarityToPointsAndLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_levelToPoints.SetParent( newParent == null ? null : newParent._levelToPoints );
		_refinePointsCap.SetParent( newParent == null ? null : newParent._refinePointsCap );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_levelToPoints.Reset();
		_refinePointsCap.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_levelToPoints.IsDerivedFromParent()
			&& _refinePointsCap.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "levelToPoints" )
			_levelToPoints.Reset();
		else if ( fieldName == "refinePointsCap" )
			_refinePointsCap.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "levelToPoints" )
			return _levelToPoints.IsDerivedFromParent();
		if ( fieldName == "refinePointsCap" )
			return _refinePointsCap.IsDerivedFromParent();
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
public class RatingLossToInactivityDays : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RatingLossToInactivityDays __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _ratingToLoose;
	private UndoRedo<int> _minDaysFromLastBattle;

	[Description( "Рейтинг, который потеряет герой, если он не участвовал в боях ratingToLoose дней" )]
	public int ratingToLoose { get { return _ratingToLoose.Get(); } set { _ratingToLoose.Set( value ); } }

	[Description( "Кол-во дней с последней битвы, после которых игрок потеряет ratingToLoose рейтинга" )]
	public int minDaysFromLastBattle { get { return _minDaysFromLastBattle.Get(); } set { _minDaysFromLastBattle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ratingToLoose = new UndoRedo<int>( owner, 0 );
		_minDaysFromLastBattle = new UndoRedo<int>( owner, 0 );
		_ratingToLoose.Changed += FireChangedEvent;
		_minDaysFromLastBattle.Changed += FireChangedEvent;
	}

	public RatingLossToInactivityDays()
	{
		Initialize( GetOwner() );
	}

	public RatingLossToInactivityDays( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RatingLossToInactivityDays( DBResource owner, RatingLossToInactivityDays source )
		: this(owner, source, true){}

	protected RatingLossToInactivityDays( DBResource owner, RatingLossToInactivityDays source, bool fireEvent )
	{
		_ratingToLoose = new UndoRedo<int>( owner, source.ratingToLoose );
		_minDaysFromLastBattle = new UndoRedo<int>( owner, source.minDaysFromLastBattle );
		_ratingToLoose.Changed += FireChangedEvent;
		_minDaysFromLastBattle.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RatingLossToInactivityDays source = _source as RatingLossToInactivityDays;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RatingLossToInactivityDays" );
		ratingToLoose = source.ratingToLoose;
		minDaysFromLastBattle = source.minDaysFromLastBattle;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RatingLossToInactivityDays newParent = _newParent as RatingLossToInactivityDays;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ratingToLoose.SetParent( newParent == null ? null : newParent._ratingToLoose );
		_minDaysFromLastBattle.SetParent( newParent == null ? null : newParent._minDaysFromLastBattle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ratingToLoose.Reset();
		_minDaysFromLastBattle.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ratingToLoose.IsDerivedFromParent()
			&& _minDaysFromLastBattle.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ratingToLoose" )
			_ratingToLoose.Reset();
		else if ( fieldName == "minDaysFromLastBattle" )
			_minDaysFromLastBattle.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ratingToLoose" )
			return _ratingToLoose.IsDerivedFromParent();
		if ( fieldName == "minDaysFromLastBattle" )
			return _minDaysFromLastBattle.IsDerivedFromParent();
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

[IndexField("stars")]
[Custom("Social")]
public class ReforgeRerollPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ReforgeRerollPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _stars;
	private ResourcesTable _priceWithoutSetFilter;
	private ResourcesTable _priceWithSetFilter;

	[Description( "количество звезд (уровень заточки) таланта (начиная с 1)" )]
	public int stars { get { return _stars.Get(); } set { _stars.Set( value ); } }

	[Description( "цена, если роллим из всех сетов" )]
	public ResourcesTable priceWithoutSetFilter { get { return _priceWithoutSetFilter; } set { _priceWithoutSetFilter.Assign( value ); } }

	[Description( "цена, если роллим из конкретного сета" )]
	public ResourcesTable priceWithSetFilter { get { return _priceWithSetFilter; } set { _priceWithSetFilter.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_stars = new UndoRedo<int>( owner, 0 );
		_priceWithoutSetFilter = new ResourcesTable( owner );
		_priceWithSetFilter = new ResourcesTable( owner );
		_stars.Changed += FireChangedEvent;
		_priceWithoutSetFilter.Changed += FireChangedEvent;
		_priceWithSetFilter.Changed += FireChangedEvent;
	}

	public ReforgeRerollPrice()
	{
		Initialize( GetOwner() );
	}

	public ReforgeRerollPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ReforgeRerollPrice( DBResource owner, ReforgeRerollPrice source )
		: this(owner, source, true){}

	protected ReforgeRerollPrice( DBResource owner, ReforgeRerollPrice source, bool fireEvent )
	{
		_stars = new UndoRedo<int>( owner, source.stars );
		_priceWithoutSetFilter = new ResourcesTable( owner, source.priceWithoutSetFilter );
		_priceWithSetFilter = new ResourcesTable( owner, source.priceWithSetFilter );
		_stars.Changed += FireChangedEvent;
		_priceWithoutSetFilter.Changed += FireChangedEvent;
		_priceWithSetFilter.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ReforgeRerollPrice source = _source as ReforgeRerollPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ReforgeRerollPrice" );
		stars = source.stars;
		priceWithoutSetFilter = source.priceWithoutSetFilter;
		priceWithSetFilter = source.priceWithSetFilter;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ReforgeRerollPrice newParent = _newParent as ReforgeRerollPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_stars.SetParent( newParent == null ? null : newParent._stars );
		_priceWithoutSetFilter.SetParent( newParent == null ? null : newParent._priceWithoutSetFilter );
		_priceWithSetFilter.SetParent( newParent == null ? null : newParent._priceWithSetFilter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_stars.Reset();
		_priceWithoutSetFilter.Reset();
		_priceWithSetFilter.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_stars.IsDerivedFromParent()
			&& _priceWithoutSetFilter.IsDerivedFromParent()
			&& _priceWithSetFilter.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "stars" )
			_stars.Reset();
		else if ( fieldName == "priceWithoutSetFilter" )
			_priceWithoutSetFilter.Reset();
		else if ( fieldName == "priceWithSetFilter" )
			_priceWithSetFilter.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "stars" )
			return _stars.IsDerivedFromParent();
		if ( fieldName == "priceWithoutSetFilter" )
			return _priceWithoutSetFilter.IsDerivedFromParent();
		if ( fieldName == "priceWithSetFilter" )
			return _priceWithSetFilter.IsDerivedFromParent();
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

[IndexField("rarity")]
[Custom("Social")]
public class ReforgeTalentPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ReforgeTalentPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ETalentRarity> _rarity;
	private UndoRedoAssignableList<ReforgeRerollPrice> _rerollPrices;
	private ResourcesTable _upgradePrice;
	private UndoRedo<int> _talentsToUpgrade;

	public ETalentRarity rarity { get { return _rarity.Get(); } set { _rarity.Set( value ); } }

	[Description( "цены за реролл (сортировка по stars; как минимум должна быть определена цена для 1 stars; если не смогли найти цену для конкретного stars, будет взята ближайшая с меньшем stars цена)" )]
	public libdb.IChangeableList<ReforgeRerollPrice> rerollPrices { get { return _rerollPrices; } set { _rerollPrices.Assign( value ); } }

	[Description( "цена за апгрейд" )]
	public ResourcesTable upgradePrice { get { return _upgradePrice; } set { _upgradePrice.Assign( value ); } }

	public int talentsToUpgrade { get { return _talentsToUpgrade.Get(); } set { _talentsToUpgrade.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.Class );
		_rerollPrices = new UndoRedoAssignableList<ReforgeRerollPrice>( owner );
		_upgradePrice = new ResourcesTable( owner );
		_talentsToUpgrade = new UndoRedo<int>( owner, 1 );
		_rarity.Changed += FireChangedEvent;
		_rerollPrices.Changed += FireChangedEvent;
		_upgradePrice.Changed += FireChangedEvent;
		_talentsToUpgrade.Changed += FireChangedEvent;
	}

	public ReforgeTalentPrice()
	{
		Initialize( GetOwner() );
	}

	public ReforgeTalentPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ReforgeTalentPrice( DBResource owner, ReforgeTalentPrice source )
		: this(owner, source, true){}

	protected ReforgeTalentPrice( DBResource owner, ReforgeTalentPrice source, bool fireEvent )
	{
		_rarity = new UndoRedo<ETalentRarity>( owner, source.rarity );
		_rerollPrices = new UndoRedoAssignableList<ReforgeRerollPrice>( owner );
		_rerollPrices.Assign( source.rerollPrices );
		_upgradePrice = new ResourcesTable( owner, source.upgradePrice );
		_talentsToUpgrade = new UndoRedo<int>( owner, source.talentsToUpgrade );
		_rarity.Changed += FireChangedEvent;
		_rerollPrices.Changed += FireChangedEvent;
		_upgradePrice.Changed += FireChangedEvent;
		_talentsToUpgrade.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ReforgeTalentPrice source = _source as ReforgeTalentPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ReforgeTalentPrice" );
		rarity = source.rarity;
		rerollPrices = source.rerollPrices;
		upgradePrice = source.upgradePrice;
		talentsToUpgrade = source.talentsToUpgrade;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ReforgeTalentPrice newParent = _newParent as ReforgeTalentPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rarity.SetParent( newParent == null ? null : newParent._rarity );
		_rerollPrices.SetParent( newParent == null ? null : newParent._rerollPrices );
		_upgradePrice.SetParent( newParent == null ? null : newParent._upgradePrice );
		_talentsToUpgrade.SetParent( newParent == null ? null : newParent._talentsToUpgrade );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rarity.Reset();
		_rerollPrices.Reset();
		_upgradePrice.Reset();
		_talentsToUpgrade.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rarity.IsDerivedFromParent()
			&& _rerollPrices.IsDerivedFromParent()
			&& _upgradePrice.IsDerivedFromParent()
			&& _talentsToUpgrade.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rarity" )
			_rarity.Reset();
		else if ( fieldName == "rerollPrices" )
			_rerollPrices.Reset();
		else if ( fieldName == "upgradePrice" )
			_upgradePrice.Reset();
		else if ( fieldName == "talentsToUpgrade" )
			_talentsToUpgrade.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rarity" )
			return _rarity.IsDerivedFromParent();
		if ( fieldName == "rerollPrices" )
			return _rerollPrices.IsDerivedFromParent();
		if ( fieldName == "upgradePrice" )
			return _upgradePrice.IsDerivedFromParent();
		if ( fieldName == "talentsToUpgrade" )
			return _talentsToUpgrade.IsDerivedFromParent();
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

[IndexField("nameLeague")]
[Custom("Social")]
public class SeasonLeagueSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SeasonLeagueSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _leagueId;
	private UndoRedo<int> _flashDataIndex;
	private UndoRedo<int> _crownFlashIndex;
	private UndoRedo<int> _quality;
	private TextRef _nameLeague;

	[Description( "Идентификатор лиги" )]
	public int leagueId { get { return _leagueId.Get(); } set { _leagueId.Set( value ); } }

	[Description( "Индекс для получения данных во флеше ( начинать от 2 )" )]
	public int flashDataIndex { get { return _flashDataIndex.Get(); } set { _flashDataIndex.Set( value ); } }

	[Description( "Индекс индекв фрейма с коронкой во флэше" )]
	public int crownFlashIndex { get { return _crownFlashIndex.Get(); } set { _crownFlashIndex.Set( value ); } }

	[Description( "Важность лиги при её отображении" )]
	public int quality { get { return _quality.Get(); } set { _quality.Set( value ); } }

	[Description( "Имя лиги" )]
	public TextRef nameLeague { get { return _nameLeague; } set { _nameLeague.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_leagueId = new UndoRedo<int>( owner, 0 );
		_flashDataIndex = new UndoRedo<int>( owner, 0 );
		_crownFlashIndex = new UndoRedo<int>( owner, 0 );
		_quality = new UndoRedo<int>( owner, 0 );
		_nameLeague = new TextRef( owner, new TextRef() );
		_leagueId.Changed += FireChangedEvent;
		_flashDataIndex.Changed += FireChangedEvent;
		_crownFlashIndex.Changed += FireChangedEvent;
		_quality.Changed += FireChangedEvent;
		_nameLeague.Changed += FireChangedEvent;
	}

	public SeasonLeagueSettings()
	{
		Initialize( GetOwner() );
	}

	public SeasonLeagueSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SeasonLeagueSettings( DBResource owner, SeasonLeagueSettings source )
		: this(owner, source, true){}

	protected SeasonLeagueSettings( DBResource owner, SeasonLeagueSettings source, bool fireEvent )
	{
		_leagueId = new UndoRedo<int>( owner, source.leagueId );
		_flashDataIndex = new UndoRedo<int>( owner, source.flashDataIndex );
		_crownFlashIndex = new UndoRedo<int>( owner, source.crownFlashIndex );
		_quality = new UndoRedo<int>( owner, source.quality );
		_nameLeague = new TextRef( owner, source.nameLeague );
		_leagueId.Changed += FireChangedEvent;
		_flashDataIndex.Changed += FireChangedEvent;
		_crownFlashIndex.Changed += FireChangedEvent;
		_quality.Changed += FireChangedEvent;
		_nameLeague.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SeasonLeagueSettings source = _source as SeasonLeagueSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SeasonLeagueSettings" );
		leagueId = source.leagueId;
		flashDataIndex = source.flashDataIndex;
		crownFlashIndex = source.crownFlashIndex;
		quality = source.quality;
		nameLeague = source.nameLeague;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SeasonLeagueSettings newParent = _newParent as SeasonLeagueSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_leagueId.SetParent( newParent == null ? null : newParent._leagueId );
		_flashDataIndex.SetParent( newParent == null ? null : newParent._flashDataIndex );
		_crownFlashIndex.SetParent( newParent == null ? null : newParent._crownFlashIndex );
		_quality.SetParent( newParent == null ? null : newParent._quality );
		_nameLeague.SetParent( newParent == null ? null : newParent._nameLeague );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_leagueId.Reset();
		_flashDataIndex.Reset();
		_crownFlashIndex.Reset();
		_quality.Reset();
		_nameLeague.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_leagueId.IsDerivedFromParent()
			&& _flashDataIndex.IsDerivedFromParent()
			&& _crownFlashIndex.IsDerivedFromParent()
			&& _quality.IsDerivedFromParent()
			&& _nameLeague.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "leagueId" )
			_leagueId.Reset();
		else if ( fieldName == "flashDataIndex" )
			_flashDataIndex.Reset();
		else if ( fieldName == "crownFlashIndex" )
			_crownFlashIndex.Reset();
		else if ( fieldName == "quality" )
			_quality.Reset();
		else if ( fieldName == "nameLeague" )
			_nameLeague.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "leagueId" )
			return _leagueId.IsDerivedFromParent();
		if ( fieldName == "flashDataIndex" )
			return _flashDataIndex.IsDerivedFromParent();
		if ( fieldName == "crownFlashIndex" )
			return _crownFlashIndex.IsDerivedFromParent();
		if ( fieldName == "quality" )
			return _quality.IsDerivedFromParent();
		if ( fieldName == "nameLeague" )
			return _nameLeague.IsDerivedFromParent();
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

[IndexField("persistentId")]
[Custom("Social")]
public class SeasonSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SeasonSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _persistentId;
	private TextRef _nameSeason;
	private UndoRedoAssignableList<LeagueInfo> _ParamLeagues;
	private UndoRedo<int> _startTime;
	private UndoRedo<int> _stopTime;

	[Description( "Идентификатор сезона" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "Имя сезона" )]
	public TextRef nameSeason { get { return _nameSeason; } set { _nameSeason.Assign( value ); } }

	[Description( "Настройки лиг в сезонах" )]
	public libdb.IChangeableList<LeagueInfo> ParamLeagues { get { return _ParamLeagues; } set { _ParamLeagues.Assign( value ); } }

	[Description( "Время начала сезона в Unix TimeStamp" )]
	public int startTime { get { return _startTime.Get(); } set { _startTime.Set( value ); } }

	[Description( "Время окончания сезона в Unix TimeStamp" )]
	public int stopTime { get { return _stopTime.Get(); } set { _stopTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_nameSeason = new TextRef( owner, new TextRef() );
		_ParamLeagues = new UndoRedoAssignableList<LeagueInfo>( owner );
		_startTime = new UndoRedo<int>( owner, 0 );
		_stopTime = new UndoRedo<int>( owner, 0 );
		_persistentId.Changed += FireChangedEvent;
		_nameSeason.Changed += FireChangedEvent;
		_ParamLeagues.Changed += FireChangedEvent;
		_startTime.Changed += FireChangedEvent;
		_stopTime.Changed += FireChangedEvent;
	}

	public SeasonSettings()
	{
		Initialize( GetOwner() );
	}

	public SeasonSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SeasonSettings( DBResource owner, SeasonSettings source )
		: this(owner, source, true){}

	protected SeasonSettings( DBResource owner, SeasonSettings source, bool fireEvent )
	{
		_persistentId = new UndoRedo<string>( owner, source.persistentId );
		_nameSeason = new TextRef( owner, source.nameSeason );
		_ParamLeagues = new UndoRedoAssignableList<LeagueInfo>( owner );
		_ParamLeagues.Assign( source.ParamLeagues );
		_startTime = new UndoRedo<int>( owner, source.startTime );
		_stopTime = new UndoRedo<int>( owner, source.stopTime );
		_persistentId.Changed += FireChangedEvent;
		_nameSeason.Changed += FireChangedEvent;
		_ParamLeagues.Changed += FireChangedEvent;
		_startTime.Changed += FireChangedEvent;
		_stopTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SeasonSettings source = _source as SeasonSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SeasonSettings" );
		persistentId = source.persistentId;
		nameSeason = source.nameSeason;
		ParamLeagues = source.ParamLeagues;
		startTime = source.startTime;
		stopTime = source.stopTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SeasonSettings newParent = _newParent as SeasonSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_nameSeason.SetParent( newParent == null ? null : newParent._nameSeason );
		_ParamLeagues.SetParent( newParent == null ? null : newParent._ParamLeagues );
		_startTime.SetParent( newParent == null ? null : newParent._startTime );
		_stopTime.SetParent( newParent == null ? null : newParent._stopTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_persistentId.Reset();
		_nameSeason.Reset();
		_ParamLeagues.Reset();
		_startTime.Reset();
		_stopTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _nameSeason.IsDerivedFromParent()
			&& _ParamLeagues.IsDerivedFromParent()
			&& _startTime.IsDerivedFromParent()
			&& _stopTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "nameSeason" )
			_nameSeason.Reset();
		else if ( fieldName == "ParamLeagues" )
			_ParamLeagues.Reset();
		else if ( fieldName == "startTime" )
			_startTime.Reset();
		else if ( fieldName == "stopTime" )
			_stopTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "nameSeason" )
			return _nameSeason.IsDerivedFromParent();
		if ( fieldName == "ParamLeagues" )
			return _ParamLeagues.IsDerivedFromParent();
		if ( fieldName == "startTime" )
			return _startTime.IsDerivedFromParent();
		if ( fieldName == "stopTime" )
			return _stopTime.IsDerivedFromParent();
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

[Custom("Social")]
public class StorageLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StorageLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private ResourcesTable _additionalStorage;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "На сколько увеличивается максимальный запас" )]
	public ResourcesTable additionalStorage { get { return _additionalStorage; } set { _additionalStorage.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_additionalStorage = new ResourcesTable( owner );
		_currentLevel.Changed += FireChangedEvent;
		_additionalStorage.Changed += FireChangedEvent;
	}

	public StorageLevel()
	{
		Initialize( GetOwner() );
	}

	public StorageLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StorageLevel( DBResource owner, StorageLevel source )
		: this(owner, source, true){}

	protected StorageLevel( DBResource owner, StorageLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_additionalStorage = new ResourcesTable( owner, source.additionalStorage );
		_currentLevel.Changed += FireChangedEvent;
		_additionalStorage.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StorageLevel source = _source as StorageLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StorageLevel" );
		currentLevel = source.currentLevel;
		additionalStorage = source.additionalStorage;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StorageLevel newParent = _newParent as StorageLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_additionalStorage.SetParent( newParent == null ? null : newParent._additionalStorage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_additionalStorage.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _additionalStorage.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "additionalStorage" )
			_additionalStorage.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "additionalStorage" )
			return _additionalStorage.IsDerivedFromParent();
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
public class TalentLevelToUnsoulboundPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentLevelToUnsoulboundPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedo<int> _price;

	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	public int price { get { return _price.Get(); } set { _price.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_price = new UndoRedo<int>( owner, 0 );
		_level.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
	}

	public TalentLevelToUnsoulboundPrice()
	{
		Initialize( GetOwner() );
	}

	public TalentLevelToUnsoulboundPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentLevelToUnsoulboundPrice( DBResource owner, TalentLevelToUnsoulboundPrice source )
		: this(owner, source, true){}

	protected TalentLevelToUnsoulboundPrice( DBResource owner, TalentLevelToUnsoulboundPrice source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_price = new UndoRedo<int>( owner, source.price );
		_level.Changed += FireChangedEvent;
		_price.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentLevelToUnsoulboundPrice source = _source as TalentLevelToUnsoulboundPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentLevelToUnsoulboundPrice" );
		level = source.level;
		price = source.price;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentLevelToUnsoulboundPrice newParent = _newParent as TalentLevelToUnsoulboundPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_price.SetParent( newParent == null ? null : newParent._price );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_price.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _price.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
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
		if ( fieldName == "level" )
			return _level.IsDerivedFromParent();
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

[Custom("Social")]
public class TavernExpCoeffToHeroLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TavernExpCoeffToHeroLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<float> _coefficient;

	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	public float coefficient { get { return _coefficient.Get(); } set { _coefficient.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_coefficient = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_coefficient.Changed += FireChangedEvent;
	}

	public TavernExpCoeffToHeroLevel()
	{
		Initialize( GetOwner() );
	}

	public TavernExpCoeffToHeroLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TavernExpCoeffToHeroLevel( DBResource owner, TavernExpCoeffToHeroLevel source )
		: this(owner, source, true){}

	protected TavernExpCoeffToHeroLevel( DBResource owner, TavernExpCoeffToHeroLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_coefficient = new UndoRedo<float>( owner, source.coefficient );
		_currentLevel.Changed += FireChangedEvent;
		_coefficient.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TavernExpCoeffToHeroLevel source = _source as TavernExpCoeffToHeroLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TavernExpCoeffToHeroLevel" );
		currentLevel = source.currentLevel;
		coefficient = source.coefficient;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TavernExpCoeffToHeroLevel newParent = _newParent as TavernExpCoeffToHeroLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_coefficient.SetParent( newParent == null ? null : newParent._coefficient );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_coefficient.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _coefficient.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "coefficient" )
			_coefficient.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "coefficient" )
			return _coefficient.IsDerivedFromParent();
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
public class TavernLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TavernLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _heroesCount;
	private UndoRedo<float> _rewardCoefficient;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Сколько героев влезают в таверну одновременно" )]
	public int heroesCount { get { return _heroesCount.Get(); } set { _heroesCount.Set( value ); } }

	[Description( "Коэффициент для наград (опыта/ресурса)" )]
	public float rewardCoefficient { get { return _rewardCoefficient.Get(); } set { _rewardCoefficient.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_heroesCount = new UndoRedo<int>( owner, 0 );
		_rewardCoefficient = new UndoRedo<float>( owner, 0.0f );
		_currentLevel.Changed += FireChangedEvent;
		_heroesCount.Changed += FireChangedEvent;
		_rewardCoefficient.Changed += FireChangedEvent;
	}

	public TavernLevel()
	{
		Initialize( GetOwner() );
	}

	public TavernLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TavernLevel( DBResource owner, TavernLevel source )
		: this(owner, source, true){}

	protected TavernLevel( DBResource owner, TavernLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_heroesCount = new UndoRedo<int>( owner, source.heroesCount );
		_rewardCoefficient = new UndoRedo<float>( owner, source.rewardCoefficient );
		_currentLevel.Changed += FireChangedEvent;
		_heroesCount.Changed += FireChangedEvent;
		_rewardCoefficient.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TavernLevel source = _source as TavernLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TavernLevel" );
		currentLevel = source.currentLevel;
		heroesCount = source.heroesCount;
		rewardCoefficient = source.rewardCoefficient;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TavernLevel newParent = _newParent as TavernLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_heroesCount.SetParent( newParent == null ? null : newParent._heroesCount );
		_rewardCoefficient.SetParent( newParent == null ? null : newParent._rewardCoefficient );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_heroesCount.Reset();
		_rewardCoefficient.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _heroesCount.IsDerivedFromParent()
			&& _rewardCoefficient.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "heroesCount" )
			_heroesCount.Reset();
		else if ( fieldName == "rewardCoefficient" )
			_rewardCoefficient.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "heroesCount" )
			return _heroesCount.IsDerivedFromParent();
		if ( fieldName == "rewardCoefficient" )
			return _rewardCoefficient.IsDerivedFromParent();
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
public class TavernLevelQuest : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TavernLevelQuest __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<TavernQuest>> _tavernQuests;

	[Description( "Список квестов доступных на конкретном уровне" )]
	public libdb.IChangeableList<DBPtr<TavernQuest>> tavernQuests { get { return _tavernQuests; } set { _tavernQuests.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_tavernQuests = new UndoRedoAssignableList<DBPtr<TavernQuest>>( owner );
		_tavernQuests.Changed += FireChangedEvent;
	}

	public TavernLevelQuest()
	{
		Initialize( GetOwner() );
	}

	public TavernLevelQuest( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TavernLevelQuest( DBResource owner, TavernLevelQuest source )
		: this(owner, source, true){}

	protected TavernLevelQuest( DBResource owner, TavernLevelQuest source, bool fireEvent )
	{
		_tavernQuests = new UndoRedoAssignableList<DBPtr<TavernQuest>>( owner );
		_tavernQuests.Assign( source.tavernQuests );
		_tavernQuests.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TavernLevelQuest source = _source as TavernLevelQuest;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TavernLevelQuest" );
		tavernQuests = source.tavernQuests;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TavernLevelQuest newParent = _newParent as TavernLevelQuest;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_tavernQuests.SetParent( newParent == null ? null : newParent._tavernQuests );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_tavernQuests.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_tavernQuests.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "tavernQuests" )
			_tavernQuests.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "tavernQuests" )
			return _tavernQuests.IsDerivedFromParent();
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
public class TavernReward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TavernReward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBRollTalentPercents> _rollContainer;
	private UndoRedo<TavernResourceType> _resourceType;
	private UndoRedo<int> _resourceRewardCount;
	private ResourcesTable _resource;
	private UndoRedo<int> _experience;

	[Description( "Ссылка на ролл-таблицу, если награда - талант" )]
	public DBPtr<DBRollTalentPercents> rollContainer { get { return _rollContainer.Get(); } set { _rollContainer.Set( value ); } }

	[Browsable( false )]
	[Description( "Если награда ресурс - тут указать его тип" )]
	public TavernResourceType resourceType { get { return _resourceType.Get(); } set { _resourceType.Set( value ); } }

	[Browsable( false )]
	[Description( "кол-во получаемого ресурса, в зависимости от уровня (УСТАРЕЛО! используй resource)" )]
	public int resourceRewardCount { get { return _resourceRewardCount.Get(); } set { _resourceRewardCount.Set( value ); } }

	[Description( "Ресурс" )]
	public ResourcesTable resource { get { return _resource; } set { _resource.Assign( value ); } }

	[Description( "Экспа получаемая за квест, зависит от уровня таверны" )]
	public int experience { get { return _experience.Get(); } set { _experience.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rollContainer = new UndoRedoDBPtr<DBRollTalentPercents>( owner );
		_resourceType = new UndoRedo<TavernResourceType>( owner, TavernResourceType.None );
		_resourceRewardCount = new UndoRedo<int>( owner, 0 );
		_resource = new ResourcesTable( owner );
		_experience = new UndoRedo<int>( owner, 0 );
		_rollContainer.Changed += FireChangedEvent;
		_resourceType.Changed += FireChangedEvent;
		_resourceRewardCount.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		_experience.Changed += FireChangedEvent;
	}

	public TavernReward()
	{
		Initialize( GetOwner() );
	}

	public TavernReward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TavernReward( DBResource owner, TavernReward source )
		: this(owner, source, true){}

	protected TavernReward( DBResource owner, TavernReward source, bool fireEvent )
	{
		_rollContainer = new UndoRedoDBPtr<DBRollTalentPercents>( owner, source.rollContainer );
		_resourceType = new UndoRedo<TavernResourceType>( owner, source.resourceType );
		_resourceRewardCount = new UndoRedo<int>( owner, source.resourceRewardCount );
		_resource = new ResourcesTable( owner, source.resource );
		_experience = new UndoRedo<int>( owner, source.experience );
		_rollContainer.Changed += FireChangedEvent;
		_resourceType.Changed += FireChangedEvent;
		_resourceRewardCount.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		_experience.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TavernReward source = _source as TavernReward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TavernReward" );
		rollContainer = source.rollContainer;
		resourceType = source.resourceType;
		resourceRewardCount = source.resourceRewardCount;
		resource = source.resource;
		experience = source.experience;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TavernReward newParent = _newParent as TavernReward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rollContainer.SetParent( newParent == null ? null : newParent._rollContainer );
		_resourceType.SetParent( newParent == null ? null : newParent._resourceType );
		_resourceRewardCount.SetParent( newParent == null ? null : newParent._resourceRewardCount );
		_resource.SetParent( newParent == null ? null : newParent._resource );
		_experience.SetParent( newParent == null ? null : newParent._experience );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rollContainer.Reset();
		_resourceType.Reset();
		_resourceRewardCount.Reset();
		_resource.Reset();
		_experience.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rollContainer.IsDerivedFromParent()
			&& _resourceType.IsDerivedFromParent()
			&& _resourceRewardCount.IsDerivedFromParent()
			&& _resource.IsDerivedFromParent()
			&& _experience.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rollContainer" )
			_rollContainer.Reset();
		else if ( fieldName == "resourceType" )
			_resourceType.Reset();
		else if ( fieldName == "resourceRewardCount" )
			_resourceRewardCount.Reset();
		else if ( fieldName == "resource" )
			_resource.Reset();
		else if ( fieldName == "experience" )
			_experience.Reset();
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
		if ( fieldName == "resourceType" )
			return _resourceType.IsDerivedFromParent();
		if ( fieldName == "resourceRewardCount" )
			return _resourceRewardCount.IsDerivedFromParent();
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		if ( fieldName == "experience" )
			return _experience.IsDerivedFromParent();
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
public class TransmutationLevel : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TransmutationLevel __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _currentLevel;
	private UndoRedo<int> _perlForBonuse;
	private ResourcesTable _priceToStart;
	private UndoRedo<int> _fameToProducePerCrystal;

	[Description( "Уровень для которого указаны параметры" )]
	public int currentLevel { get { return _currentLevel.Get(); } set { _currentLevel.Set( value ); } }

	[Description( "Количество талантов, которое крафтится за один цикл кузницы" )]
	public int perlForBonuse { get { return _perlForBonuse.Get(); } set { _perlForBonuse.Set( value ); } }

	[Description( "Цена добычи одного таланта" )]
	public ResourcesTable priceToStart { get { return _priceToStart; } set { _priceToStart.Assign( value ); } }

	[Description( "Сколько fame дадут за завершение цикла" )]
	public int fameToProducePerCrystal { get { return _fameToProducePerCrystal.Get(); } set { _fameToProducePerCrystal.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_currentLevel = new UndoRedo<int>( owner, 0 );
		_perlForBonuse = new UndoRedo<int>( owner, 0 );
		_priceToStart = new ResourcesTable( owner );
		_fameToProducePerCrystal = new UndoRedo<int>( owner, 0 );
		_currentLevel.Changed += FireChangedEvent;
		_perlForBonuse.Changed += FireChangedEvent;
		_priceToStart.Changed += FireChangedEvent;
		_fameToProducePerCrystal.Changed += FireChangedEvent;
	}

	public TransmutationLevel()
	{
		Initialize( GetOwner() );
	}

	public TransmutationLevel( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TransmutationLevel( DBResource owner, TransmutationLevel source )
		: this(owner, source, true){}

	protected TransmutationLevel( DBResource owner, TransmutationLevel source, bool fireEvent )
	{
		_currentLevel = new UndoRedo<int>( owner, source.currentLevel );
		_perlForBonuse = new UndoRedo<int>( owner, source.perlForBonuse );
		_priceToStart = new ResourcesTable( owner, source.priceToStart );
		_fameToProducePerCrystal = new UndoRedo<int>( owner, source.fameToProducePerCrystal );
		_currentLevel.Changed += FireChangedEvent;
		_perlForBonuse.Changed += FireChangedEvent;
		_priceToStart.Changed += FireChangedEvent;
		_fameToProducePerCrystal.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TransmutationLevel source = _source as TransmutationLevel;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TransmutationLevel" );
		currentLevel = source.currentLevel;
		perlForBonuse = source.perlForBonuse;
		priceToStart = source.priceToStart;
		fameToProducePerCrystal = source.fameToProducePerCrystal;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TransmutationLevel newParent = _newParent as TransmutationLevel;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_currentLevel.SetParent( newParent == null ? null : newParent._currentLevel );
		_perlForBonuse.SetParent( newParent == null ? null : newParent._perlForBonuse );
		_priceToStart.SetParent( newParent == null ? null : newParent._priceToStart );
		_fameToProducePerCrystal.SetParent( newParent == null ? null : newParent._fameToProducePerCrystal );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_currentLevel.Reset();
		_perlForBonuse.Reset();
		_priceToStart.Reset();
		_fameToProducePerCrystal.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_currentLevel.IsDerivedFromParent()
			&& _perlForBonuse.IsDerivedFromParent()
			&& _priceToStart.IsDerivedFromParent()
			&& _fameToProducePerCrystal.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "currentLevel" )
			_currentLevel.Reset();
		else if ( fieldName == "perlForBonuse" )
			_perlForBonuse.Reset();
		else if ( fieldName == "priceToStart" )
			_priceToStart.Reset();
		else if ( fieldName == "fameToProducePerCrystal" )
			_fameToProducePerCrystal.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "currentLevel" )
			return _currentLevel.IsDerivedFromParent();
		if ( fieldName == "perlForBonuse" )
			return _perlForBonuse.IsDerivedFromParent();
		if ( fieldName == "priceToStart" )
			return _priceToStart.IsDerivedFromParent();
		if ( fieldName == "fameToProducePerCrystal" )
			return _fameToProducePerCrystal.IsDerivedFromParent();
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

[IndexField("name")]
[Custom("Social")]
public class UIText : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UIText __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private TextRef _text;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_text = new TextRef( owner, new TextRef() );
		_name.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public UIText()
	{
		Initialize( GetOwner() );
	}

	public UIText( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UIText( DBResource owner, UIText source )
		: this(owner, source, true){}

	protected UIText( DBResource owner, UIText source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_text = new TextRef( owner, source.text );
		_name.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UIText source = _source as UIText;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIText" );
		name = source.name;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UIText newParent = _newParent as UIText;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_text.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
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
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
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
[Custom("Social")]
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

[Custom("Social")]
public class Constructon : DBResource
{
	private UndoRedoDBPtr<Constructon> ___parent;
	[HideInOutliner]
	public new DBPtr<Constructon> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedo<bool> _Destroyable;
	private UndoRedo<bool> _Movable;
	private UndoRedo<string> _IconPathA;
	private UndoRedo<string> _IconPathB;
	private Vec3 _OffsetA;
	private Vec3 _OffsetB;
	private UndoRedo<bool> _SupportVisualGradesChanging;
	private UndoRedoList<int> _VisualChangingLevels;
	private UndoRedo<string> _ModelsPathA;
	private UndoRedo<string> _ModelsPathB;
	private UndoRedo<string> _PostBuildingObjectPathA;
	private UndoRedo<string> _PostBuildingObjectPathB;
	private TextRef _CaptionA;
	private TextRef _CaptionB;
	private TextRef _Description;
	private TextRef _Tooltip;
	private TextRef _UpgradeTooltip;
	private UndoRedo<int> _SectionsSize;
	private UndoRedoDBPtr<SectionsSet> _SectionsLockedForBuilding;
	private UndoRedoDBPtr<SectionsSet> _SectionsLockedForDecorations;
	private UndoRedoAssignableList<ConstructionLevel> _Levels;
	private UndoRedo<float> _SellPricePercent;
	private UndoRedoAssignableList<DBPtr<LimitsOfBuilding>> _GroupBuildingLimits;
	private UndoRedo<ConstructionTab> _ConstructionTab;
	private UndoRedo<int> _LevelRequired;
	private UndoRedo<ConstructionProductionType> _ProductionIconType;

	[Description( "ID строения" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	public bool Destroyable { get { return _Destroyable.Get(); } set { _Destroyable.Set( value ); } }

	public bool Movable { get { return _Movable.Get(); } set { _Movable.Set( value ); } }

	[Description( "Путь до иконки относительно UnityClient/Assets/Resources. Как правило начинается с UI/Textures/Constructions/A/" )]
	public string IconPathA { get { return _IconPathA.Get(); } set { _IconPathA.Set( value ); } }

	[Description( "Путь до иконки относительно UnityClient/Assets/Resources. Как правило начинается с UI/Textures/Constructions/B/" )]
	public string IconPathB { get { return _IconPathB.Get(); } set { _IconPathB.Set( value ); } }

	[Description( "Отступ от 0-й клетки до центра 3D модели. В случае '0 0 0' модель будет выровнена по центру." )]
	public Vec3 OffsetA { get { return _OffsetA; } set { _OffsetA.Assign( value ); } }

	[Description( "Отступ от 0-й клетки до центра 3D модели. В случае '0 0 0' модель будет выровнена по центру." )]
	public Vec3 OffsetB { get { return _OffsetB; } set { _OffsetB.Assign( value ); } }

	[Description( "Меняет ли здание внешний вид при повылении грейда. Вне зависимости от значения доступно только при наличии 3D ассетов." )]
	public bool SupportVisualGradesChanging { get { return _SupportVisualGradesChanging.Get(); } set { _SupportVisualGradesChanging.Set( value ); } }

	[Description( "Список уровней на которых здание меняет визуальное отображение(3D модель). Если уровни не заданы, модели будут равномерно распределены по уровням здания. Первую модель(1-й уровень) можно не задавать." )]
	public libdb.IChangeableList<int> VisualChangingLevels { get { return _VisualChangingLevels; } set { _VisualChangingLevels.Assign( value ); } }

	[Description( "Путь до папки с моделями грейдов или до модели здания относительно UnityClient/Assets/Resources для фракции Доктов. Как правило, начинается с Prefabs/Constructions/A/" )]
	public string ModelsPathA { get { return _ModelsPathA.Get(); } set { _ModelsPathA.Set( value ); } }

	[Description( "Путь до папки с моделями грейдов или до модели здания относительно UnityClient/Assets/Resources для фракции Адорнийцев. Как правило, начинается с Prefabs/Constructions/B/" )]
	public string ModelsPathB { get { return _ModelsPathB.Get(); } set { _ModelsPathB.Set( value ); } }

	[Description( "Путь до объекта, который создается после строительства домика(например эффект) относительно UnityClient/Assets/Resources для фракции Доктов. Как правило, начинается с Prefabs/" )]
	public string PostBuildingObjectPathA { get { return _PostBuildingObjectPathA.Get(); } set { _PostBuildingObjectPathA.Set( value ); } }

	[Description( "Путь до объекта, который создается после строительства домика(например эффект) относительно UnityClient/Assets/Resources для фракции Адорнийцев. Как правило, начинается с Prefabs/" )]
	public string PostBuildingObjectPathB { get { return _PostBuildingObjectPathB.Get(); } set { _PostBuildingObjectPathB.Set( value ); } }

	public TextRef CaptionA { get { return _CaptionA; } set { _CaptionA.Assign( value ); } }

	public TextRef CaptionB { get { return _CaptionB; } set { _CaptionB.Assign( value ); } }

	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	public TextRef Tooltip { get { return _Tooltip; } set { _Tooltip.Assign( value ); } }

	public TextRef UpgradeTooltip { get { return _UpgradeTooltip; } set { _UpgradeTooltip.Assign( value ); } }

	public int SectionsSize { get { return _SectionsSize.Get(); } set { _SectionsSize.Set( value ); } }

	public DBPtr<SectionsSet> SectionsLockedForBuilding { get { return _SectionsLockedForBuilding.Get(); } set { _SectionsLockedForBuilding.Set( value ); } }

	public DBPtr<SectionsSet> SectionsLockedForDecorations { get { return _SectionsLockedForDecorations.Get(); } set { _SectionsLockedForDecorations.Set( value ); } }

	[Description( "Уровни апгрейда" )]
	public libdb.IChangeableList<ConstructionLevel> Levels { get { return _Levels; } set { _Levels.Assign( value ); } }

	[Description( "Сколько процентов от цены здания дается при продаже" )]
	public float SellPricePercent { get { return _SellPricePercent.Get(); } set { _SellPricePercent.Set( value ); } }

	[Description( "Лимиты на количество построенных зданий" )]
	public libdb.IChangeableList<DBPtr<LimitsOfBuilding>> GroupBuildingLimits { get { return _GroupBuildingLimits; } set { _GroupBuildingLimits.Assign( value ); } }

	public ConstructionTab ConstructionTab { get { return _ConstructionTab.Get(); } set { _ConstructionTab.Set( value ); } }

	[Description( "Lord's level required for buying buildings" )]
	public int LevelRequired { get { return _LevelRequired.Get(); } set { _LevelRequired.Set( value ); } }

	[Description( "Тип производимого ресурса (None, если иконка не должна отображаться)" )]
	public ConstructionProductionType ProductionIconType { get { return _ProductionIconType.Get(); } set { _ProductionIconType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Constructon>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_Destroyable = new UndoRedo<bool>( owner, false );
		_Movable = new UndoRedo<bool>( owner, false );
		_IconPathA = new UndoRedo<string>( owner, string.Empty );
		_IconPathB = new UndoRedo<string>( owner, string.Empty );
		_OffsetA = new Vec3( owner );
		_OffsetB = new Vec3( owner );
		_SupportVisualGradesChanging = new UndoRedo<bool>( owner, false );
		_VisualChangingLevels = new UndoRedoList<int>( owner );
		_ModelsPathA = new UndoRedo<string>( owner, string.Empty );
		_ModelsPathB = new UndoRedo<string>( owner, string.Empty );
		_PostBuildingObjectPathA = new UndoRedo<string>( owner, string.Empty );
		_PostBuildingObjectPathB = new UndoRedo<string>( owner, string.Empty );
		_CaptionA = new TextRef( owner, new TextRef() );
		_CaptionB = new TextRef( owner, new TextRef() );
		_Description = new TextRef( owner, new TextRef() );
		_Tooltip = new TextRef( owner, new TextRef() );
		_UpgradeTooltip = new TextRef( owner, new TextRef() );
		_SectionsSize = new UndoRedo<int>( owner, 5 );
		_SectionsLockedForBuilding = new UndoRedoDBPtr<SectionsSet>( owner );
		_SectionsLockedForDecorations = new UndoRedoDBPtr<SectionsSet>( owner );
		_Levels = new UndoRedoAssignableList<ConstructionLevel>( owner );
		_SellPricePercent = new UndoRedo<float>( owner, 0.5f );
		_GroupBuildingLimits = new UndoRedoAssignableList<DBPtr<LimitsOfBuilding>>( owner );
		_ConstructionTab = new UndoRedo<ConstructionTab>( owner, ConstructionTab.Services );
		_LevelRequired = new UndoRedo<int>( owner, 0 );
		_ProductionIconType = new UndoRedo<ConstructionProductionType>( owner, ConstructionProductionType.None );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_Destroyable.Changed += FireChangedEvent;
		_Movable.Changed += FireChangedEvent;
		_IconPathA.Changed += FireChangedEvent;
		_IconPathB.Changed += FireChangedEvent;
		_OffsetA.Changed += FireChangedEvent;
		_OffsetB.Changed += FireChangedEvent;
		_SupportVisualGradesChanging.Changed += FireChangedEvent;
		_VisualChangingLevels.Changed += FireChangedEvent;
		_ModelsPathA.Changed += FireChangedEvent;
		_ModelsPathB.Changed += FireChangedEvent;
		_PostBuildingObjectPathA.Changed += FireChangedEvent;
		_PostBuildingObjectPathB.Changed += FireChangedEvent;
		_CaptionA.Changed += FireChangedEvent;
		_CaptionB.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_Tooltip.Changed += FireChangedEvent;
		_UpgradeTooltip.Changed += FireChangedEvent;
		_SectionsSize.Changed += FireChangedEvent;
		_SectionsLockedForBuilding.Changed += FireChangedEvent;
		_SectionsLockedForDecorations.Changed += FireChangedEvent;
		_Levels.Changed += FireChangedEvent;
		_SellPricePercent.Changed += FireChangedEvent;
		_GroupBuildingLimits.Changed += FireChangedEvent;
		_ConstructionTab.Changed += FireChangedEvent;
		_LevelRequired.Changed += FireChangedEvent;
		_ProductionIconType.Changed += FireChangedEvent;
	}

	public Constructon()
	{
		Initialize( this );
	}
	private void AssignSelf( Constructon source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Constructon" );
		persistentId = source.persistentId;
		Destroyable = source.Destroyable;
		Movable = source.Movable;
		IconPathA = source.IconPathA;
		IconPathB = source.IconPathB;
		OffsetA = source.OffsetA;
		OffsetB = source.OffsetB;
		SupportVisualGradesChanging = source.SupportVisualGradesChanging;
		VisualChangingLevels = source.VisualChangingLevels;
		ModelsPathA = source.ModelsPathA;
		ModelsPathB = source.ModelsPathB;
		PostBuildingObjectPathA = source.PostBuildingObjectPathA;
		PostBuildingObjectPathB = source.PostBuildingObjectPathB;
		CaptionA = source.CaptionA;
		CaptionB = source.CaptionB;
		Description = source.Description;
		Tooltip = source.Tooltip;
		UpgradeTooltip = source.UpgradeTooltip;
		SectionsSize = source.SectionsSize;
		SectionsLockedForBuilding = source.SectionsLockedForBuilding;
		SectionsLockedForDecorations = source.SectionsLockedForDecorations;
		Levels = source.Levels;
		SellPricePercent = source.SellPricePercent;
		GroupBuildingLimits = source.GroupBuildingLimits;
		ConstructionTab = source.ConstructionTab;
		LevelRequired = source.LevelRequired;
		ProductionIconType = source.ProductionIconType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Constructon source = _source as Constructon;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Constructon" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Constructon newParent = rawParent == null ? null : rawParent.Get<Constructon>();
		if ( newParent == null && _newParent is Constructon )
			newParent = _newParent as Constructon;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_Destroyable.SetParent( newParent == null ? null : newParent._Destroyable );
		_Movable.SetParent( newParent == null ? null : newParent._Movable );
		_IconPathA.SetParent( newParent == null ? null : newParent._IconPathA );
		_IconPathB.SetParent( newParent == null ? null : newParent._IconPathB );
		_OffsetA.SetParent( newParent == null ? null : newParent._OffsetA );
		_OffsetB.SetParent( newParent == null ? null : newParent._OffsetB );
		_SupportVisualGradesChanging.SetParent( newParent == null ? null : newParent._SupportVisualGradesChanging );
		_VisualChangingLevels.SetParent( newParent == null ? null : newParent._VisualChangingLevels );
		_ModelsPathA.SetParent( newParent == null ? null : newParent._ModelsPathA );
		_ModelsPathB.SetParent( newParent == null ? null : newParent._ModelsPathB );
		_PostBuildingObjectPathA.SetParent( newParent == null ? null : newParent._PostBuildingObjectPathA );
		_PostBuildingObjectPathB.SetParent( newParent == null ? null : newParent._PostBuildingObjectPathB );
		_CaptionA.SetParent( newParent == null ? null : newParent._CaptionA );
		_CaptionB.SetParent( newParent == null ? null : newParent._CaptionB );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		_Tooltip.SetParent( newParent == null ? null : newParent._Tooltip );
		_UpgradeTooltip.SetParent( newParent == null ? null : newParent._UpgradeTooltip );
		_SectionsSize.SetParent( newParent == null ? null : newParent._SectionsSize );
		_SectionsLockedForBuilding.SetParent( newParent == null ? null : newParent._SectionsLockedForBuilding );
		_SectionsLockedForDecorations.SetParent( newParent == null ? null : newParent._SectionsLockedForDecorations );
		_Levels.SetParent( newParent == null ? null : newParent._Levels );
		_SellPricePercent.SetParent( newParent == null ? null : newParent._SellPricePercent );
		_GroupBuildingLimits.SetParent( newParent == null ? null : newParent._GroupBuildingLimits );
		_ConstructionTab.SetParent( newParent == null ? null : newParent._ConstructionTab );
		_LevelRequired.SetParent( newParent == null ? null : newParent._LevelRequired );
		_ProductionIconType.SetParent( newParent == null ? null : newParent._ProductionIconType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_Destroyable.Reset();
		_Movable.Reset();
		_IconPathA.Reset();
		_IconPathB.Reset();
		_OffsetA.Reset();
		_OffsetB.Reset();
		_SupportVisualGradesChanging.Reset();
		_VisualChangingLevels.Reset();
		_ModelsPathA.Reset();
		_ModelsPathB.Reset();
		_PostBuildingObjectPathA.Reset();
		_PostBuildingObjectPathB.Reset();
		_CaptionA.Reset();
		_CaptionB.Reset();
		_Description.Reset();
		_Tooltip.Reset();
		_UpgradeTooltip.Reset();
		_SectionsSize.Reset();
		_SectionsLockedForBuilding.Reset();
		_SectionsLockedForDecorations.Reset();
		_Levels.Reset();
		_SellPricePercent.Reset();
		_GroupBuildingLimits.Reset();
		_ConstructionTab.Reset();
		_LevelRequired.Reset();
		_ProductionIconType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _Destroyable.IsDerivedFromParent()
			&& _Movable.IsDerivedFromParent()
			&& _IconPathA.IsDerivedFromParent()
			&& _IconPathB.IsDerivedFromParent()
			&& _OffsetA.IsDerivedFromParent()
			&& _OffsetB.IsDerivedFromParent()
			&& _SupportVisualGradesChanging.IsDerivedFromParent()
			&& _VisualChangingLevels.IsDerivedFromParent()
			&& _ModelsPathA.IsDerivedFromParent()
			&& _ModelsPathB.IsDerivedFromParent()
			&& _PostBuildingObjectPathA.IsDerivedFromParent()
			&& _PostBuildingObjectPathB.IsDerivedFromParent()
			&& _CaptionA.IsDerivedFromParent()
			&& _CaptionB.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			&& _Tooltip.IsDerivedFromParent()
			&& _UpgradeTooltip.IsDerivedFromParent()
			&& _SectionsSize.IsDerivedFromParent()
			&& _SectionsLockedForBuilding.IsDerivedFromParent()
			&& _SectionsLockedForDecorations.IsDerivedFromParent()
			&& _Levels.IsDerivedFromParent()
			&& _SellPricePercent.IsDerivedFromParent()
			&& _GroupBuildingLimits.IsDerivedFromParent()
			&& _ConstructionTab.IsDerivedFromParent()
			&& _LevelRequired.IsDerivedFromParent()
			&& _ProductionIconType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "Destroyable" )
			_Destroyable.Reset();
		else if ( fieldName == "Movable" )
			_Movable.Reset();
		else if ( fieldName == "IconPathA" )
			_IconPathA.Reset();
		else if ( fieldName == "IconPathB" )
			_IconPathB.Reset();
		else if ( fieldName == "OffsetA" )
			_OffsetA.Reset();
		else if ( fieldName == "OffsetB" )
			_OffsetB.Reset();
		else if ( fieldName == "SupportVisualGradesChanging" )
			_SupportVisualGradesChanging.Reset();
		else if ( fieldName == "VisualChangingLevels" )
			_VisualChangingLevels.Reset();
		else if ( fieldName == "ModelsPathA" )
			_ModelsPathA.Reset();
		else if ( fieldName == "ModelsPathB" )
			_ModelsPathB.Reset();
		else if ( fieldName == "PostBuildingObjectPathA" )
			_PostBuildingObjectPathA.Reset();
		else if ( fieldName == "PostBuildingObjectPathB" )
			_PostBuildingObjectPathB.Reset();
		else if ( fieldName == "CaptionA" )
			_CaptionA.Reset();
		else if ( fieldName == "CaptionB" )
			_CaptionB.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
		else if ( fieldName == "Tooltip" )
			_Tooltip.Reset();
		else if ( fieldName == "UpgradeTooltip" )
			_UpgradeTooltip.Reset();
		else if ( fieldName == "SectionsSize" )
			_SectionsSize.Reset();
		else if ( fieldName == "SectionsLockedForBuilding" )
			_SectionsLockedForBuilding.Reset();
		else if ( fieldName == "SectionsLockedForDecorations" )
			_SectionsLockedForDecorations.Reset();
		else if ( fieldName == "Levels" )
			_Levels.Reset();
		else if ( fieldName == "SellPricePercent" )
			_SellPricePercent.Reset();
		else if ( fieldName == "GroupBuildingLimits" )
			_GroupBuildingLimits.Reset();
		else if ( fieldName == "ConstructionTab" )
			_ConstructionTab.Reset();
		else if ( fieldName == "LevelRequired" )
			_LevelRequired.Reset();
		else if ( fieldName == "ProductionIconType" )
			_ProductionIconType.Reset();
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
		if ( fieldName == "Destroyable" )
			return _Destroyable.IsDerivedFromParent();
		if ( fieldName == "Movable" )
			return _Movable.IsDerivedFromParent();
		if ( fieldName == "IconPathA" )
			return _IconPathA.IsDerivedFromParent();
		if ( fieldName == "IconPathB" )
			return _IconPathB.IsDerivedFromParent();
		if ( fieldName == "OffsetA" )
			return _OffsetA.IsDerivedFromParent();
		if ( fieldName == "OffsetB" )
			return _OffsetB.IsDerivedFromParent();
		if ( fieldName == "SupportVisualGradesChanging" )
			return _SupportVisualGradesChanging.IsDerivedFromParent();
		if ( fieldName == "VisualChangingLevels" )
			return _VisualChangingLevels.IsDerivedFromParent();
		if ( fieldName == "ModelsPathA" )
			return _ModelsPathA.IsDerivedFromParent();
		if ( fieldName == "ModelsPathB" )
			return _ModelsPathB.IsDerivedFromParent();
		if ( fieldName == "PostBuildingObjectPathA" )
			return _PostBuildingObjectPathA.IsDerivedFromParent();
		if ( fieldName == "PostBuildingObjectPathB" )
			return _PostBuildingObjectPathB.IsDerivedFromParent();
		if ( fieldName == "CaptionA" )
			return _CaptionA.IsDerivedFromParent();
		if ( fieldName == "CaptionB" )
			return _CaptionB.IsDerivedFromParent();
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
		if ( fieldName == "Tooltip" )
			return _Tooltip.IsDerivedFromParent();
		if ( fieldName == "UpgradeTooltip" )
			return _UpgradeTooltip.IsDerivedFromParent();
		if ( fieldName == "SectionsSize" )
			return _SectionsSize.IsDerivedFromParent();
		if ( fieldName == "SectionsLockedForBuilding" )
			return _SectionsLockedForBuilding.IsDerivedFromParent();
		if ( fieldName == "SectionsLockedForDecorations" )
			return _SectionsLockedForDecorations.IsDerivedFromParent();
		if ( fieldName == "Levels" )
			return _Levels.IsDerivedFromParent();
		if ( fieldName == "SellPricePercent" )
			return _SellPricePercent.IsDerivedFromParent();
		if ( fieldName == "GroupBuildingLimits" )
			return _GroupBuildingLimits.IsDerivedFromParent();
		if ( fieldName == "ConstructionTab" )
			return _ConstructionTab.IsDerivedFromParent();
		if ( fieldName == "LevelRequired" )
			return _LevelRequired.IsDerivedFromParent();
		if ( fieldName == "ProductionIconType" )
			return _ProductionIconType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class MarketingEvent : BaseMarketingEvent
{
	private UndoRedoDBPtr<MarketingEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<MarketingEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _iconA;
	private UndoRedoDBPtr<Texture> _iconB;
	private UndoRedoDBPtr<Texture> _imageA;
	private UndoRedoDBPtr<Texture> _imageB;
	private TextRef _tooltipA;
	private TextRef _tooltipB;
	private TextRef _nameA;
	private TextRef _nameB;
	private TextRef _sloganA;
	private TextRef _sloganB;
	private TextRef _buttonActionTextA;
	private TextRef _buttonActionTextB;
	private TextRef _cancelButtonActionText;
	private UndoRedo<bool> _isSpecial;
	private UndoRedo<bool> _visible;

	public DBPtr<Texture> iconA { get { return _iconA.Get(); } set { _iconA.Set( value ); } }

	public DBPtr<Texture> iconB { get { return _iconB.Get(); } set { _iconB.Set( value ); } }

	public DBPtr<Texture> imageA { get { return _imageA.Get(); } set { _imageA.Set( value ); } }

	public DBPtr<Texture> imageB { get { return _imageB.Get(); } set { _imageB.Set( value ); } }

	public TextRef tooltipA { get { return _tooltipA; } set { _tooltipA.Assign( value ); } }

	public TextRef tooltipB { get { return _tooltipB; } set { _tooltipB.Assign( value ); } }

	public TextRef nameA { get { return _nameA; } set { _nameA.Assign( value ); } }

	public TextRef nameB { get { return _nameB; } set { _nameB.Assign( value ); } }

	public TextRef sloganA { get { return _sloganA; } set { _sloganA.Assign( value ); } }

	public TextRef sloganB { get { return _sloganB; } set { _sloganB.Assign( value ); } }

	public TextRef buttonActionTextA { get { return _buttonActionTextA; } set { _buttonActionTextA.Assign( value ); } }

	public TextRef buttonActionTextB { get { return _buttonActionTextB; } set { _buttonActionTextB.Assign( value ); } }

	public TextRef cancelButtonActionText { get { return _cancelButtonActionText; } set { _cancelButtonActionText.Assign( value ); } }

	public bool isSpecial { get { return _isSpecial.Get(); } set { _isSpecial.Set( value ); } }

	public bool visible { get { return _visible.Get(); } set { _visible.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MarketingEvent>(owner);
		_iconA = new UndoRedoDBPtr<Texture>( owner );
		_iconB = new UndoRedoDBPtr<Texture>( owner );
		_imageA = new UndoRedoDBPtr<Texture>( owner );
		_imageB = new UndoRedoDBPtr<Texture>( owner );
		_tooltipA = new TextRef( owner, new TextRef() );
		_tooltipB = new TextRef( owner, new TextRef() );
		_nameA = new TextRef( owner, new TextRef() );
		_nameB = new TextRef( owner, new TextRef() );
		_sloganA = new TextRef( owner, new TextRef() );
		_sloganB = new TextRef( owner, new TextRef() );
		_buttonActionTextA = new TextRef( owner, new TextRef() );
		_buttonActionTextB = new TextRef( owner, new TextRef() );
		_cancelButtonActionText = new TextRef( owner, new TextRef() );
		_isSpecial = new UndoRedo<bool>( owner, false );
		_visible = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_iconA.Changed += FireChangedEvent;
		_iconB.Changed += FireChangedEvent;
		_imageA.Changed += FireChangedEvent;
		_imageB.Changed += FireChangedEvent;
		_tooltipA.Changed += FireChangedEvent;
		_tooltipB.Changed += FireChangedEvent;
		_nameA.Changed += FireChangedEvent;
		_nameB.Changed += FireChangedEvent;
		_sloganA.Changed += FireChangedEvent;
		_sloganB.Changed += FireChangedEvent;
		_buttonActionTextA.Changed += FireChangedEvent;
		_buttonActionTextB.Changed += FireChangedEvent;
		_cancelButtonActionText.Changed += FireChangedEvent;
		_isSpecial.Changed += FireChangedEvent;
		_visible.Changed += FireChangedEvent;
	}

	public MarketingEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( MarketingEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MarketingEvent" );
		iconA = source.iconA;
		iconB = source.iconB;
		imageA = source.imageA;
		imageB = source.imageB;
		tooltipA = source.tooltipA;
		tooltipB = source.tooltipB;
		nameA = source.nameA;
		nameB = source.nameB;
		sloganA = source.sloganA;
		sloganB = source.sloganB;
		buttonActionTextA = source.buttonActionTextA;
		buttonActionTextB = source.buttonActionTextB;
		cancelButtonActionText = source.cancelButtonActionText;
		isSpecial = source.isSpecial;
		visible = source.visible;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MarketingEvent source = _source as MarketingEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MarketingEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MarketingEvent newParent = rawParent == null ? null : rawParent.Get<MarketingEvent>();
		if ( newParent == null && _newParent is MarketingEvent )
			newParent = _newParent as MarketingEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_iconA.SetParent( newParent == null ? null : newParent._iconA );
		_iconB.SetParent( newParent == null ? null : newParent._iconB );
		_imageA.SetParent( newParent == null ? null : newParent._imageA );
		_imageB.SetParent( newParent == null ? null : newParent._imageB );
		_tooltipA.SetParent( newParent == null ? null : newParent._tooltipA );
		_tooltipB.SetParent( newParent == null ? null : newParent._tooltipB );
		_nameA.SetParent( newParent == null ? null : newParent._nameA );
		_nameB.SetParent( newParent == null ? null : newParent._nameB );
		_sloganA.SetParent( newParent == null ? null : newParent._sloganA );
		_sloganB.SetParent( newParent == null ? null : newParent._sloganB );
		_buttonActionTextA.SetParent( newParent == null ? null : newParent._buttonActionTextA );
		_buttonActionTextB.SetParent( newParent == null ? null : newParent._buttonActionTextB );
		_cancelButtonActionText.SetParent( newParent == null ? null : newParent._cancelButtonActionText );
		_isSpecial.SetParent( newParent == null ? null : newParent._isSpecial );
		_visible.SetParent( newParent == null ? null : newParent._visible );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_iconA.Reset();
		_iconB.Reset();
		_imageA.Reset();
		_imageB.Reset();
		_tooltipA.Reset();
		_tooltipB.Reset();
		_nameA.Reset();
		_nameB.Reset();
		_sloganA.Reset();
		_sloganB.Reset();
		_buttonActionTextA.Reset();
		_buttonActionTextB.Reset();
		_cancelButtonActionText.Reset();
		_isSpecial.Reset();
		_visible.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_iconA.IsDerivedFromParent()
			&& _iconB.IsDerivedFromParent()
			&& _imageA.IsDerivedFromParent()
			&& _imageB.IsDerivedFromParent()
			&& _tooltipA.IsDerivedFromParent()
			&& _tooltipB.IsDerivedFromParent()
			&& _nameA.IsDerivedFromParent()
			&& _nameB.IsDerivedFromParent()
			&& _sloganA.IsDerivedFromParent()
			&& _sloganB.IsDerivedFromParent()
			&& _buttonActionTextA.IsDerivedFromParent()
			&& _buttonActionTextB.IsDerivedFromParent()
			&& _cancelButtonActionText.IsDerivedFromParent()
			&& _isSpecial.IsDerivedFromParent()
			&& _visible.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "iconA" )
			_iconA.Reset();
		else if ( fieldName == "iconB" )
			_iconB.Reset();
		else if ( fieldName == "imageA" )
			_imageA.Reset();
		else if ( fieldName == "imageB" )
			_imageB.Reset();
		else if ( fieldName == "tooltipA" )
			_tooltipA.Reset();
		else if ( fieldName == "tooltipB" )
			_tooltipB.Reset();
		else if ( fieldName == "nameA" )
			_nameA.Reset();
		else if ( fieldName == "nameB" )
			_nameB.Reset();
		else if ( fieldName == "sloganA" )
			_sloganA.Reset();
		else if ( fieldName == "sloganB" )
			_sloganB.Reset();
		else if ( fieldName == "buttonActionTextA" )
			_buttonActionTextA.Reset();
		else if ( fieldName == "buttonActionTextB" )
			_buttonActionTextB.Reset();
		else if ( fieldName == "cancelButtonActionText" )
			_cancelButtonActionText.Reset();
		else if ( fieldName == "isSpecial" )
			_isSpecial.Reset();
		else if ( fieldName == "visible" )
			_visible.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "iconA" )
			return _iconA.IsDerivedFromParent();
		if ( fieldName == "iconB" )
			return _iconB.IsDerivedFromParent();
		if ( fieldName == "imageA" )
			return _imageA.IsDerivedFromParent();
		if ( fieldName == "imageB" )
			return _imageB.IsDerivedFromParent();
		if ( fieldName == "tooltipA" )
			return _tooltipA.IsDerivedFromParent();
		if ( fieldName == "tooltipB" )
			return _tooltipB.IsDerivedFromParent();
		if ( fieldName == "nameA" )
			return _nameA.IsDerivedFromParent();
		if ( fieldName == "nameB" )
			return _nameB.IsDerivedFromParent();
		if ( fieldName == "sloganA" )
			return _sloganA.IsDerivedFromParent();
		if ( fieldName == "sloganB" )
			return _sloganB.IsDerivedFromParent();
		if ( fieldName == "buttonActionTextA" )
			return _buttonActionTextA.IsDerivedFromParent();
		if ( fieldName == "buttonActionTextB" )
			return _buttonActionTextB.IsDerivedFromParent();
		if ( fieldName == "cancelButtonActionText" )
			return _cancelButtonActionText.IsDerivedFromParent();
		if ( fieldName == "isSpecial" )
			return _isSpecial.IsDerivedFromParent();
		if ( fieldName == "visible" )
			return _visible.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
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

[Custom("Social")]
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

[Custom("Social")]
public class BuildGoldenLodgeEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuildGoldenLodgeEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuildGoldenLodgeEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuildGoldenLodgeEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuildGoldenLodgeEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuildGoldenLodgeEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuildGoldenLodgeEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuildGoldenLodgeEvent source = _source as BuildGoldenLodgeEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuildGoldenLodgeEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuildGoldenLodgeEvent newParent = rawParent == null ? null : rawParent.Get<BuildGoldenLodgeEvent>();
		if ( newParent == null && _newParent is BuildGoldenLodgeEvent )
			newParent = _newParent as BuildGoldenLodgeEvent;
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
public class BuyAeriaGoldEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyAeriaGoldEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyAeriaGoldEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyAeriaGoldEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyAeriaGoldEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyAeriaGoldEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyAeriaGoldEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyAeriaGoldEvent source = _source as BuyAeriaGoldEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyAeriaGoldEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyAeriaGoldEvent newParent = rawParent == null ? null : rawParent.Get<BuyAeriaGoldEvent>();
		if ( newParent == null && _newParent is BuyAeriaGoldEvent )
			newParent = _newParent as BuyAeriaGoldEvent;
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
public class BuyArcGamesGoldEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyArcGamesGoldEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyArcGamesGoldEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyArcGamesGoldEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyArcGamesGoldEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyArcGamesGoldEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyArcGamesGoldEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyArcGamesGoldEvent source = _source as BuyArcGamesGoldEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyArcGamesGoldEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyArcGamesGoldEvent newParent = rawParent == null ? null : rawParent.Get<BuyArcGamesGoldEvent>();
		if ( newParent == null && _newParent is BuyArcGamesGoldEvent )
			newParent = _newParent as BuyArcGamesGoldEvent;
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

[Custom("Social")]
public class BuyFlagEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyFlagEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyFlagEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyFlagEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyFlagEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyFlagEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyFlagEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyFlagEvent source = _source as BuyFlagEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyFlagEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyFlagEvent newParent = rawParent == null ? null : rawParent.Get<BuyFlagEvent>();
		if ( newParent == null && _newParent is BuyFlagEvent )
			newParent = _newParent as BuyFlagEvent;
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
public class BuyGoldenLodgeEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyGoldenLodgeEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyGoldenLodgeEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyGoldenLodgeEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyGoldenLodgeEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyGoldenLodgeEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyGoldenLodgeEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyGoldenLodgeEvent source = _source as BuyGoldenLodgeEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyGoldenLodgeEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyGoldenLodgeEvent newParent = rawParent == null ? null : rawParent.Get<BuyGoldenLodgeEvent>();
		if ( newParent == null && _newParent is BuyGoldenLodgeEvent )
			newParent = _newParent as BuyGoldenLodgeEvent;
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
public class BuyGoldHeroEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyGoldHeroEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyGoldHeroEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _youAlreadyBoughtAllEventHeroes;

	public TextRef youAlreadyBoughtAllEventHeroes { get { return _youAlreadyBoughtAllEventHeroes; } set { _youAlreadyBoughtAllEventHeroes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyGoldHeroEvent>(owner);
		_youAlreadyBoughtAllEventHeroes = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_youAlreadyBoughtAllEventHeroes.Changed += FireChangedEvent;
	}

	public BuyGoldHeroEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyGoldHeroEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyGoldHeroEvent" );
		youAlreadyBoughtAllEventHeroes = source.youAlreadyBoughtAllEventHeroes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyGoldHeroEvent source = _source as BuyGoldHeroEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyGoldHeroEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyGoldHeroEvent newParent = rawParent == null ? null : rawParent.Get<BuyGoldHeroEvent>();
		if ( newParent == null && _newParent is BuyGoldHeroEvent )
			newParent = _newParent as BuyGoldHeroEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_youAlreadyBoughtAllEventHeroes.SetParent( newParent == null ? null : newParent._youAlreadyBoughtAllEventHeroes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_youAlreadyBoughtAllEventHeroes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_youAlreadyBoughtAllEventHeroes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "youAlreadyBoughtAllEventHeroes" )
			_youAlreadyBoughtAllEventHeroes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "youAlreadyBoughtAllEventHeroes" )
			return _youAlreadyBoughtAllEventHeroes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class BuyHeroEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyHeroEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyHeroEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _youAlreadyBoughtAllEventHeroes;
	private TextRef _youAlreadyUsedEvent;

	public TextRef youAlreadyBoughtAllEventHeroes { get { return _youAlreadyBoughtAllEventHeroes; } set { _youAlreadyBoughtAllEventHeroes.Assign( value ); } }

	public TextRef youAlreadyUsedEvent { get { return _youAlreadyUsedEvent; } set { _youAlreadyUsedEvent.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyHeroEvent>(owner);
		_youAlreadyBoughtAllEventHeroes = new TextRef( owner, new TextRef() );
		_youAlreadyUsedEvent = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_youAlreadyBoughtAllEventHeroes.Changed += FireChangedEvent;
		_youAlreadyUsedEvent.Changed += FireChangedEvent;
	}

	public BuyHeroEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyHeroEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyHeroEvent" );
		youAlreadyBoughtAllEventHeroes = source.youAlreadyBoughtAllEventHeroes;
		youAlreadyUsedEvent = source.youAlreadyUsedEvent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyHeroEvent source = _source as BuyHeroEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyHeroEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyHeroEvent newParent = rawParent == null ? null : rawParent.Get<BuyHeroEvent>();
		if ( newParent == null && _newParent is BuyHeroEvent )
			newParent = _newParent as BuyHeroEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_youAlreadyBoughtAllEventHeroes.SetParent( newParent == null ? null : newParent._youAlreadyBoughtAllEventHeroes );
		_youAlreadyUsedEvent.SetParent( newParent == null ? null : newParent._youAlreadyUsedEvent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_youAlreadyBoughtAllEventHeroes.Reset();
		_youAlreadyUsedEvent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_youAlreadyBoughtAllEventHeroes.IsDerivedFromParent()
			&& _youAlreadyUsedEvent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "youAlreadyBoughtAllEventHeroes" )
			_youAlreadyBoughtAllEventHeroes.Reset();
		else if ( fieldName == "youAlreadyUsedEvent" )
			_youAlreadyUsedEvent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "youAlreadyBoughtAllEventHeroes" )
			return _youAlreadyBoughtAllEventHeroes.IsDerivedFromParent();
		if ( fieldName == "youAlreadyUsedEvent" )
			return _youAlreadyUsedEvent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class BuySpecialHeroEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuySpecialHeroEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuySpecialHeroEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuySpecialHeroEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuySpecialHeroEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuySpecialHeroEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuySpecialHeroEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuySpecialHeroEvent source = _source as BuySpecialHeroEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuySpecialHeroEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuySpecialHeroEvent newParent = rawParent == null ? null : rawParent.Get<BuySpecialHeroEvent>();
		if ( newParent == null && _newParent is BuySpecialHeroEvent )
			newParent = _newParent as BuySpecialHeroEvent;
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
public class BuySteamDLCEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuySteamDLCEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuySteamDLCEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuySteamDLCEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuySteamDLCEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuySteamDLCEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuySteamDLCEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuySteamDLCEvent source = _source as BuySteamDLCEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuySteamDLCEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuySteamDLCEvent newParent = rawParent == null ? null : rawParent.Get<BuySteamDLCEvent>();
		if ( newParent == null && _newParent is BuySteamDLCEvent )
			newParent = _newParent as BuySteamDLCEvent;
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
public class BuySteamGoldEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuySteamGoldEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuySteamGoldEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuySteamGoldEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuySteamGoldEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuySteamGoldEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuySteamGoldEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuySteamGoldEvent source = _source as BuySteamGoldEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuySteamGoldEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuySteamGoldEvent newParent = rawParent == null ? null : rawParent.Get<BuySteamGoldEvent>();
		if ( newParent == null && _newParent is BuySteamGoldEvent )
			newParent = _newParent as BuySteamGoldEvent;
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
public class BuyTournamentTicketEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyTournamentTicketEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyTournamentTicketEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyTournamentTicketEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyTournamentTicketEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyTournamentTicketEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyTournamentTicketEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyTournamentTicketEvent source = _source as BuyTournamentTicketEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyTournamentTicketEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyTournamentTicketEvent newParent = rawParent == null ? null : rawParent.Get<BuyTournamentTicketEvent>();
		if ( newParent == null && _newParent is BuyTournamentTicketEvent )
			newParent = _newParent as BuyTournamentTicketEvent;
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
public class BuyZZimaGoldEvent : MarketingEvent
{
	private UndoRedoDBPtr<BuyZZimaGoldEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyZZimaGoldEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyZZimaGoldEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BuyZZimaGoldEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyZZimaGoldEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyZZimaGoldEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyZZimaGoldEvent source = _source as BuyZZimaGoldEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyZZimaGoldEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyZZimaGoldEvent newParent = rawParent == null ? null : rawParent.Get<BuyZZimaGoldEvent>();
		if ( newParent == null && _newParent is BuyZZimaGoldEvent )
			newParent = _newParent as BuyZZimaGoldEvent;
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
public class CastleCutscene : DBResource
{
	private UndoRedoDBPtr<CastleCutscene> ___parent;
	[HideInOutliner]
	public new DBPtr<CastleCutscene> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _CutsceneScriptNameA;
	private UndoRedo<string> _CutsceneScriptNameB;

	[Description( "Строковый идентефикатор кат сцены для фракции A." )]
	public string CutsceneScriptNameA { get { return _CutsceneScriptNameA.Get(); } set { _CutsceneScriptNameA.Set( value ); } }

	[Description( "Строковый идентефикатор кат сцены для фракции B." )]
	public string CutsceneScriptNameB { get { return _CutsceneScriptNameB.Get(); } set { _CutsceneScriptNameB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CastleCutscene>(owner);
		_CutsceneScriptNameA = new UndoRedo<string>( owner, string.Empty );
		_CutsceneScriptNameB = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_CutsceneScriptNameA.Changed += FireChangedEvent;
		_CutsceneScriptNameB.Changed += FireChangedEvent;
	}

	public CastleCutscene()
	{
		Initialize( this );
	}
	private void AssignSelf( CastleCutscene source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CastleCutscene" );
		CutsceneScriptNameA = source.CutsceneScriptNameA;
		CutsceneScriptNameB = source.CutsceneScriptNameB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CastleCutscene source = _source as CastleCutscene;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CastleCutscene" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CastleCutscene newParent = rawParent == null ? null : rawParent.Get<CastleCutscene>();
		if ( newParent == null && _newParent is CastleCutscene )
			newParent = _newParent as CastleCutscene;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_CutsceneScriptNameA.SetParent( newParent == null ? null : newParent._CutsceneScriptNameA );
		_CutsceneScriptNameB.SetParent( newParent == null ? null : newParent._CutsceneScriptNameB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_CutsceneScriptNameA.Reset();
		_CutsceneScriptNameB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_CutsceneScriptNameA.IsDerivedFromParent()
			&& _CutsceneScriptNameB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "CutsceneScriptNameA" )
			_CutsceneScriptNameA.Reset();
		else if ( fieldName == "CutsceneScriptNameB" )
			_CutsceneScriptNameB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "CutsceneScriptNameA" )
			return _CutsceneScriptNameA.IsDerivedFromParent();
		if ( fieldName == "CutsceneScriptNameB" )
			return _CutsceneScriptNameB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class CastleResourceBonus : GuildShopItemBonus
{
	private UndoRedoDBPtr<CastleResourceBonus> ___parent;
	[HideInOutliner]
	public new DBPtr<CastleResourceBonus> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EResourceType> _resource;
	private UndoRedo<EBuildingProductionCycle> _cycle;
	private UndoRedoAssignableList<DBPtr<Constructon>> _buildingsToAffect;
	private ValueProps _modifiers;

	public EResourceType resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	[Description( "Производственный цикл" )]
	public EBuildingProductionCycle cycle { get { return _cycle.Get(); } set { _cycle.Set( value ); } }

	[Description( "Здания, на которые распространяется бонус" )]
	public libdb.IChangeableList<DBPtr<Constructon>> buildingsToAffect { get { return _buildingsToAffect; } set { _buildingsToAffect.Assign( value ); } }

	public ValueProps modifiers { get { return _modifiers; } set { _modifiers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CastleResourceBonus>(owner);
		_resource = new UndoRedo<EResourceType>( owner, EResourceType.Silver );
		_cycle = new UndoRedo<EBuildingProductionCycle>( owner, (EBuildingProductionCycle)0 );
		_buildingsToAffect = new UndoRedoAssignableList<DBPtr<Constructon>>( owner );
		_modifiers = new ValueProps( owner );
		___parent.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		_cycle.Changed += FireChangedEvent;
		_buildingsToAffect.Changed += FireChangedEvent;
		_modifiers.Changed += FireChangedEvent;
	}

	public CastleResourceBonus()
	{
		Initialize( this );
	}
	private void AssignSelf( CastleResourceBonus source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CastleResourceBonus" );
		resource = source.resource;
		cycle = source.cycle;
		buildingsToAffect = source.buildingsToAffect;
		modifiers = source.modifiers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CastleResourceBonus source = _source as CastleResourceBonus;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CastleResourceBonus" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CastleResourceBonus newParent = rawParent == null ? null : rawParent.Get<CastleResourceBonus>();
		if ( newParent == null && _newParent is CastleResourceBonus )
			newParent = _newParent as CastleResourceBonus;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resource.SetParent( newParent == null ? null : newParent._resource );
		_cycle.SetParent( newParent == null ? null : newParent._cycle );
		_buildingsToAffect.SetParent( newParent == null ? null : newParent._buildingsToAffect );
		_modifiers.SetParent( newParent == null ? null : newParent._modifiers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resource.Reset();
		_cycle.Reset();
		_buildingsToAffect.Reset();
		_modifiers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resource.IsDerivedFromParent()
			&& _cycle.IsDerivedFromParent()
			&& _buildingsToAffect.IsDerivedFromParent()
			&& _modifiers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resource" )
			_resource.Reset();
		else if ( fieldName == "cycle" )
			_cycle.Reset();
		else if ( fieldName == "buildingsToAffect" )
			_buildingsToAffect.Reset();
		else if ( fieldName == "modifiers" )
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
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		if ( fieldName == "cycle" )
			return _cycle.IsDerivedFromParent();
		if ( fieldName == "buildingsToAffect" )
			return _buildingsToAffect.IsDerivedFromParent();
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

[Custom("Social")]
public class CommonConstructionsSettings : DBResource
{
	private UndoRedoDBPtr<CommonConstructionsSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<CommonConstructionsSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Vec3 _Offset;

	[Description( "Смещение префаба здания относительно левой верхней клетки знимаемой площади" )]
	public Vec3 Offset { get { return _Offset; } set { _Offset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CommonConstructionsSettings>(owner);
		_Offset = new Vec3( owner );
		___parent.Changed += FireChangedEvent;
		_Offset.Changed += FireChangedEvent;
	}

	public CommonConstructionsSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( CommonConstructionsSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CommonConstructionsSettings" );
		Offset = source.Offset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CommonConstructionsSettings source = _source as CommonConstructionsSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CommonConstructionsSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CommonConstructionsSettings newParent = rawParent == null ? null : rawParent.Get<CommonConstructionsSettings>();
		if ( newParent == null && _newParent is CommonConstructionsSettings )
			newParent = _newParent as CommonConstructionsSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Offset.SetParent( newParent == null ? null : newParent._Offset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Offset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Offset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Offset" )
			_Offset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Offset" )
			return _Offset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Bath : Constructon
{
	private UndoRedoDBPtr<Bath> ___parent;
	[HideInOutliner]
	public new DBPtr<Bath> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<BathLevel> _BathLevels;
	private UndoRedoAssignableList<BathCycleType> _BathCycles;
	private UndoRedo<float> _GoldBoostPrice;

	[Description( "Уровни бани" )]
	public libdb.IChangeableList<BathLevel> BathLevels { get { return _BathLevels; } set { _BathLevels.Assign( value ); } }

	[Description( "Циклы бани" )]
	public libdb.IChangeableList<BathCycleType> BathCycles { get { return _BathCycles; } set { _BathCycles.Assign( value ); } }

	[Description( "Стоимость ускорения восстановления единицы энергии" )]
	public float GoldBoostPrice { get { return _GoldBoostPrice.Get(); } set { _GoldBoostPrice.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Bath>(owner);
		_BathLevels = new UndoRedoAssignableList<BathLevel>( owner );
		_BathCycles = new UndoRedoAssignableList<BathCycleType>( owner );
		_GoldBoostPrice = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_BathLevels.Changed += FireChangedEvent;
		_BathCycles.Changed += FireChangedEvent;
		_GoldBoostPrice.Changed += FireChangedEvent;
	}

	public Bath()
	{
		Initialize( this );
	}
	private void AssignSelf( Bath source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Bath" );
		BathLevels = source.BathLevels;
		BathCycles = source.BathCycles;
		GoldBoostPrice = source.GoldBoostPrice;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Bath source = _source as Bath;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Bath" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Bath newParent = rawParent == null ? null : rawParent.Get<Bath>();
		if ( newParent == null && _newParent is Bath )
			newParent = _newParent as Bath;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_BathLevels.SetParent( newParent == null ? null : newParent._BathLevels );
		_BathCycles.SetParent( newParent == null ? null : newParent._BathCycles );
		_GoldBoostPrice.SetParent( newParent == null ? null : newParent._GoldBoostPrice );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_BathLevels.Reset();
		_BathCycles.Reset();
		_GoldBoostPrice.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_BathLevels.IsDerivedFromParent()
			&& _BathCycles.IsDerivedFromParent()
			&& _GoldBoostPrice.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "BathLevels" )
			_BathLevels.Reset();
		else if ( fieldName == "BathCycles" )
			_BathCycles.Reset();
		else if ( fieldName == "GoldBoostPrice" )
			_GoldBoostPrice.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "BathLevels" )
			return _BathLevels.IsDerivedFromParent();
		if ( fieldName == "BathCycles" )
			return _BathCycles.IsDerivedFromParent();
		if ( fieldName == "GoldBoostPrice" )
			return _GoldBoostPrice.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Credits : DBResource
{
	private UndoRedoDBPtr<Credits> ___parent;
	[HideInOutliner]
	public new DBPtr<Credits> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _text;
	private UndoRedo<string> _backImage;
	private UndoRedo<float> _duration;

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	public string backImage { get { return _backImage.Get(); } set { _backImage.Set( value ); } }

	[Description( "Время за которое должны пролететь титры" )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Credits>(owner);
		_text = new TextRef( owner, new TextRef() );
		_backImage = new UndoRedo<string>( owner, string.Empty );
		_duration = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		_backImage.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
	}

	public Credits()
	{
		Initialize( this );
	}
	private void AssignSelf( Credits source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Credits" );
		text = source.text;
		backImage = source.backImage;
		duration = source.duration;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Credits source = _source as Credits;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Credits" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Credits newParent = rawParent == null ? null : rawParent.Get<Credits>();
		if ( newParent == null && _newParent is Credits )
			newParent = _newParent as Credits;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_text.SetParent( newParent == null ? null : newParent._text );
		_backImage.SetParent( newParent == null ? null : newParent._backImage );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_text.Reset();
		_backImage.Reset();
		_duration.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_text.IsDerivedFromParent()
			&& _backImage.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "text" )
			_text.Reset();
		else if ( fieldName == "backImage" )
			_backImage.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		if ( fieldName == "backImage" )
			return _backImage.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ADMPDSCRGR")]
[Custom("Social")]
public class DBAdvMapDescGroup : DBResource
{
	private UndoRedoDBPtr<DBAdvMapDescGroup> ___parent;
	[HideInOutliner]
	public new DBPtr<DBAdvMapDescGroup> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<AdvMapDescription>> _maps;

	[Description( "Список карт и режимов игры" )]
	public libdb.IChangeableList<DBPtr<AdvMapDescription>> maps { get { return _maps; } set { _maps.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBAdvMapDescGroup>(owner);
		_maps = new UndoRedoAssignableList<DBPtr<AdvMapDescription>>( owner );
		___parent.Changed += FireChangedEvent;
		_maps.Changed += FireChangedEvent;
	}

	public DBAdvMapDescGroup()
	{
		Initialize( this );
	}
	private void AssignSelf( DBAdvMapDescGroup source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBAdvMapDescGroup" );
		maps = source.maps;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBAdvMapDescGroup source = _source as DBAdvMapDescGroup;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBAdvMapDescGroup" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBAdvMapDescGroup newParent = rawParent == null ? null : rawParent.Get<DBAdvMapDescGroup>();
		if ( newParent == null && _newParent is DBAdvMapDescGroup )
			newParent = _newParent as DBAdvMapDescGroup;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_maps.SetParent( newParent == null ? null : newParent._maps );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_maps.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_maps.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "maps" )
			_maps.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "maps" )
			return _maps.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class DBLevelToFame : DBResource
{
	private UndoRedoDBPtr<DBLevelToFame> ___parent;
	[HideInOutliner]
	public new DBPtr<DBLevelToFame> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _Levels;

	public libdb.IChangeableList<int> Levels { get { return _Levels; } set { _Levels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBLevelToFame>(owner);
		_Levels = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		_Levels.Changed += FireChangedEvent;
	}

	public DBLevelToFame()
	{
		Initialize( this );
	}
	private void AssignSelf( DBLevelToFame source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBLevelToFame" );
		Levels = source.Levels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBLevelToFame source = _source as DBLevelToFame;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLevelToFame" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBLevelToFame newParent = rawParent == null ? null : rawParent.Get<DBLevelToFame>();
		if ( newParent == null && _newParent is DBLevelToFame )
			newParent = _newParent as DBLevelToFame;
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
public class DBMap : DBResource
{
	private UndoRedoDBPtr<DBMap> ___parent;
	[HideInOutliner]
	public new DBPtr<DBMap> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Vec2 _MapSize;
	private Vec3 _MapCenter;
	private UndoRedo<float> _SectionSize;
	private UndoRedoAssignableList<MapGrade> _Grades;

	[Description( "Map size in sections." )]
	public Vec2 MapSize { get { return _MapSize; } set { _MapSize.Assign( value ); } }

	[Description( "Map center for Unity 3D coordinates." )]
	public Vec3 MapCenter { get { return _MapCenter; } set { _MapCenter.Assign( value ); } }

	[Description( "Section size for Unity drawing." )]
	public float SectionSize { get { return _SectionSize.Get(); } set { _SectionSize.Set( value ); } }

	[Description( "Castle maps grades. Grade 0 is initial map state." )]
	public libdb.IChangeableList<MapGrade> Grades { get { return _Grades; } set { _Grades.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBMap>(owner);
		_MapSize = new Vec2( owner );
		_MapCenter = new Vec3( owner );
		_SectionSize = new UndoRedo<float>( owner, 0.0f );
		_Grades = new UndoRedoAssignableList<MapGrade>( owner );
		___parent.Changed += FireChangedEvent;
		_MapSize.Changed += FireChangedEvent;
		_MapCenter.Changed += FireChangedEvent;
		_SectionSize.Changed += FireChangedEvent;
		_Grades.Changed += FireChangedEvent;
	}

	public DBMap()
	{
		Initialize( this );
	}
	private void AssignSelf( DBMap source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBMap" );
		MapSize = source.MapSize;
		MapCenter = source.MapCenter;
		SectionSize = source.SectionSize;
		Grades = source.Grades;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBMap source = _source as DBMap;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMap" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBMap newParent = rawParent == null ? null : rawParent.Get<DBMap>();
		if ( newParent == null && _newParent is DBMap )
			newParent = _newParent as DBMap;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_MapSize.SetParent( newParent == null ? null : newParent._MapSize );
		_MapCenter.SetParent( newParent == null ? null : newParent._MapCenter );
		_SectionSize.SetParent( newParent == null ? null : newParent._SectionSize );
		_Grades.SetParent( newParent == null ? null : newParent._Grades );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_MapSize.Reset();
		_MapCenter.Reset();
		_SectionSize.Reset();
		_Grades.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_MapSize.IsDerivedFromParent()
			&& _MapCenter.IsDerivedFromParent()
			&& _SectionSize.IsDerivedFromParent()
			&& _Grades.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "MapSize" )
			_MapSize.Reset();
		else if ( fieldName == "MapCenter" )
			_MapCenter.Reset();
		else if ( fieldName == "SectionSize" )
			_SectionSize.Reset();
		else if ( fieldName == "Grades" )
			_Grades.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "MapSize" )
			return _MapSize.IsDerivedFromParent();
		if ( fieldName == "MapCenter" )
			return _MapCenter.IsDerivedFromParent();
		if ( fieldName == "SectionSize" )
			return _SectionSize.IsDerivedFromParent();
		if ( fieldName == "Grades" )
			return _Grades.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class DBRollTalentPercents : DBResource
{
	private UndoRedoDBPtr<DBRollTalentPercents> ___parent;
	[HideInOutliner]
	public new DBPtr<DBRollTalentPercents> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _percents;

	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<int> percents { get { return _percents; } set { _percents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBRollTalentPercents>(owner);
		_percents = new UndoRedoList<int>( owner, typeof( ETalentRarity ) );
		___parent.Changed += FireChangedEvent;
		_percents.Changed += FireChangedEvent;
	}

	public DBRollTalentPercents()
	{
		Initialize( this );
	}
	private void AssignSelf( DBRollTalentPercents source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBRollTalentPercents" );
		percents = source.percents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBRollTalentPercents source = _source as DBRollTalentPercents;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBRollTalentPercents" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBRollTalentPercents newParent = rawParent == null ? null : rawParent.Get<DBRollTalentPercents>();
		if ( newParent == null && _newParent is DBRollTalentPercents )
			newParent = _newParent as DBRollTalentPercents;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

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
		if ( __parent == null || __parent.Get() == null )
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
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
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
public class DBStatpointsToLevel : DBResource
{
	private UndoRedoDBPtr<DBStatpointsToLevel> ___parent;
	[HideInOutliner]
	public new DBPtr<DBStatpointsToLevel> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _StatPoints;

	public libdb.IChangeableList<int> StatPoints { get { return _StatPoints; } set { _StatPoints.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBStatpointsToLevel>(owner);
		_StatPoints = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		_StatPoints.Changed += FireChangedEvent;
	}

	public DBStatpointsToLevel()
	{
		Initialize( this );
	}
	private void AssignSelf( DBStatpointsToLevel source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBStatpointsToLevel" );
		StatPoints = source.StatPoints;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBStatpointsToLevel source = _source as DBStatpointsToLevel;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBStatpointsToLevel" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBStatpointsToLevel newParent = rawParent == null ? null : rawParent.Get<DBStatpointsToLevel>();
		if ( newParent == null && _newParent is DBStatpointsToLevel )
			newParent = _newParent as DBStatpointsToLevel;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_StatPoints.SetParent( newParent == null ? null : newParent._StatPoints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_StatPoints.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_StatPoints.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "StatPoints" )
			_StatPoints.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "StatPoints" )
			return _StatPoints.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Decoration : Constructon
{
	private UndoRedoDBPtr<Decoration> ___parent;
	[HideInOutliner]
	public new DBPtr<Decoration> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EHeroRaces> _fraction;

	[Description( "Расса, для которой отображается декорация." )]
	public EHeroRaces fraction { get { return _fraction.Get(); } set { _fraction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Decoration>(owner);
		_fraction = new UndoRedo<EHeroRaces>( owner, EHeroRaces.B | EHeroRaces.A );
		___parent.Changed += FireChangedEvent;
		_fraction.Changed += FireChangedEvent;
	}

	public Decoration()
	{
		Initialize( this );
	}
	private void AssignSelf( Decoration source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Decoration" );
		fraction = source.fraction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Decoration source = _source as Decoration;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Decoration" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Decoration newParent = rawParent == null ? null : rawParent.Get<Decoration>();
		if ( newParent == null && _newParent is Decoration )
			newParent = _newParent as Decoration;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fraction.SetParent( newParent == null ? null : newParent._fraction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fraction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fraction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fraction" )
			_fraction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fraction" )
			return _fraction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ErrorMessagesTable : DBResource
{
	private UndoRedoDBPtr<ErrorMessagesTable> ___parent;
	[HideInOutliner]
	public new DBPtr<ErrorMessagesTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ErrorKeyMessagePair> _Errors;

	public libdb.IChangeableList<ErrorKeyMessagePair> Errors { get { return _Errors; } set { _Errors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ErrorMessagesTable>(owner);
		_Errors = new UndoRedoAssignableList<ErrorKeyMessagePair>( owner );
		___parent.Changed += FireChangedEvent;
		_Errors.Changed += FireChangedEvent;
	}

	public ErrorMessagesTable()
	{
		Initialize( this );
	}
	private void AssignSelf( ErrorMessagesTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ErrorMessagesTable" );
		Errors = source.Errors;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ErrorMessagesTable source = _source as ErrorMessagesTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ErrorMessagesTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ErrorMessagesTable newParent = rawParent == null ? null : rawParent.Get<ErrorMessagesTable>();
		if ( newParent == null && _newParent is ErrorMessagesTable )
			newParent = _newParent as ErrorMessagesTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Errors.SetParent( newParent == null ? null : newParent._Errors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Errors.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Errors.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Errors" )
			_Errors.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Errors" )
			return _Errors.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Expansion : Constructon
{
	private UndoRedoDBPtr<Expansion> ___parent;
	[HideInOutliner]
	public new DBPtr<Expansion> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _expansionLevel;

	[Description( "Уровень на котором данное расширение можно построить" )]
	public int expansionLevel { get { return _expansionLevel.Get(); } set { _expansionLevel.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Expansion>(owner);
		_expansionLevel = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_expansionLevel.Changed += FireChangedEvent;
	}

	public Expansion()
	{
		Initialize( this );
	}
	private void AssignSelf( Expansion source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Expansion" );
		expansionLevel = source.expansionLevel;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Expansion source = _source as Expansion;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Expansion" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Expansion newParent = rawParent == null ? null : rawParent.Get<Expansion>();
		if ( newParent == null && _newParent is Expansion )
			newParent = _newParent as Expansion;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_expansionLevel.SetParent( newParent == null ? null : newParent._expansionLevel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_expansionLevel.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_expansionLevel.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "expansionLevel" )
			_expansionLevel.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "expansionLevel" )
			return _expansionLevel.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class FirstBuyBuilding : Constructon
{
	private UndoRedoDBPtr<FirstBuyBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<FirstBuyBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<FirstBuyLevel> _FirstBuyLevels;
	private UndoRedoDBPtr<Consumable> _petItem;

	[Description( "Уровни FirstBuy" )]
	public libdb.IChangeableList<FirstBuyLevel> FirstBuyLevels { get { return _FirstBuyLevels; } set { _FirstBuyLevels.Assign( value ); } }

	[Description( "Пет, вызываемый в бою" )]
	public DBPtr<Consumable> petItem { get { return _petItem.Get(); } set { _petItem.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FirstBuyBuilding>(owner);
		_FirstBuyLevels = new UndoRedoAssignableList<FirstBuyLevel>( owner );
		_petItem = new UndoRedoDBPtr<Consumable>( owner );
		___parent.Changed += FireChangedEvent;
		_FirstBuyLevels.Changed += FireChangedEvent;
		_petItem.Changed += FireChangedEvent;
	}

	public FirstBuyBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( FirstBuyBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyBuilding" );
		FirstBuyLevels = source.FirstBuyLevels;
		petItem = source.petItem;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FirstBuyBuilding source = _source as FirstBuyBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FirstBuyBuilding newParent = rawParent == null ? null : rawParent.Get<FirstBuyBuilding>();
		if ( newParent == null && _newParent is FirstBuyBuilding )
			newParent = _newParent as FirstBuyBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_FirstBuyLevels.SetParent( newParent == null ? null : newParent._FirstBuyLevels );
		_petItem.SetParent( newParent == null ? null : newParent._petItem );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_FirstBuyLevels.Reset();
		_petItem.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_FirstBuyLevels.IsDerivedFromParent()
			&& _petItem.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "FirstBuyLevels" )
			_FirstBuyLevels.Reset();
		else if ( fieldName == "petItem" )
			_petItem.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "FirstBuyLevels" )
			return _FirstBuyLevels.IsDerivedFromParent();
		if ( fieldName == "petItem" )
			return _petItem.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class FirstBuyEvent : MarketingEvent
{
	private UndoRedoDBPtr<FirstBuyEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<FirstBuyEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _youAlreadyBoughtAllFirstBuyHouses;
	private TextRef _youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket;

	public TextRef youAlreadyBoughtAllFirstBuyHouses { get { return _youAlreadyBoughtAllFirstBuyHouses; } set { _youAlreadyBoughtAllFirstBuyHouses.Assign( value ); } }

	public TextRef youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket { get { return _youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket; } set { _youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FirstBuyEvent>(owner);
		_youAlreadyBoughtAllFirstBuyHouses = new TextRef( owner, new TextRef() );
		_youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_youAlreadyBoughtAllFirstBuyHouses.Changed += FireChangedEvent;
		_youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.Changed += FireChangedEvent;
	}

	public FirstBuyEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( FirstBuyEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyEvent" );
		youAlreadyBoughtAllFirstBuyHouses = source.youAlreadyBoughtAllFirstBuyHouses;
		youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket = source.youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FirstBuyEvent source = _source as FirstBuyEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FirstBuyEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FirstBuyEvent newParent = rawParent == null ? null : rawParent.Get<FirstBuyEvent>();
		if ( newParent == null && _newParent is FirstBuyEvent )
			newParent = _newParent as FirstBuyEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_youAlreadyBoughtAllFirstBuyHouses.SetParent( newParent == null ? null : newParent._youAlreadyBoughtAllFirstBuyHouses );
		_youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.SetParent( newParent == null ? null : newParent._youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_youAlreadyBoughtAllFirstBuyHouses.Reset();
		_youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_youAlreadyBoughtAllFirstBuyHouses.IsDerivedFromParent()
			&& _youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "youAlreadyBoughtAllFirstBuyHouses" )
			_youAlreadyBoughtAllFirstBuyHouses.Reset();
		else if ( fieldName == "youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket" )
			_youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "youAlreadyBoughtAllFirstBuyHouses" )
			return _youAlreadyBoughtAllFirstBuyHouses.IsDerivedFromParent();
		if ( fieldName == "youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket" )
			return _youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket.IsDerivedFromParent();
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
[Custom("Social")]
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

[Custom("Social")]
public class GoldLampEvent : MarketingEvent
{
	private UndoRedoDBPtr<GoldLampEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<GoldLampEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _bonusPersent;
	private UndoRedo<ETalentRarity> _unsoulBoundRarity;
	private UndoRedoDBPtr<Texture> _lampIcon;
	private UndoRedoDBPtr<Texture> _banner;

	[Description( "бонусное золотов процентах в целых числах" )]
	public int bonusPersent { get { return _bonusPersent.Get(); } set { _bonusPersent.Set( value ); } }

	[Description( "максимальная рарность таланта, который можно отвязать этой лампой" )]
	public ETalentRarity unsoulBoundRarity { get { return _unsoulBoundRarity.Get(); } set { _unsoulBoundRarity.Set( value ); } }

	[Description( "иконка-нотификатор в замке" )]
	public DBPtr<Texture> lampIcon { get { return _lampIcon.Get(); } set { _lampIcon.Set( value ); } }

	[Description( "баннер в акции пополнения счета" )]
	public DBPtr<Texture> banner { get { return _banner.Get(); } set { _banner.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GoldLampEvent>(owner);
		_bonusPersent = new UndoRedo<int>( owner, 0 );
		_unsoulBoundRarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.ordinary );
		_lampIcon = new UndoRedoDBPtr<Texture>( owner );
		_banner = new UndoRedoDBPtr<Texture>( owner );
		___parent.Changed += FireChangedEvent;
		_bonusPersent.Changed += FireChangedEvent;
		_unsoulBoundRarity.Changed += FireChangedEvent;
		_lampIcon.Changed += FireChangedEvent;
		_banner.Changed += FireChangedEvent;
	}

	public GoldLampEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( GoldLampEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GoldLampEvent" );
		bonusPersent = source.bonusPersent;
		unsoulBoundRarity = source.unsoulBoundRarity;
		lampIcon = source.lampIcon;
		banner = source.banner;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GoldLampEvent source = _source as GoldLampEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldLampEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GoldLampEvent newParent = rawParent == null ? null : rawParent.Get<GoldLampEvent>();
		if ( newParent == null && _newParent is GoldLampEvent )
			newParent = _newParent as GoldLampEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_bonusPersent.SetParent( newParent == null ? null : newParent._bonusPersent );
		_unsoulBoundRarity.SetParent( newParent == null ? null : newParent._unsoulBoundRarity );
		_lampIcon.SetParent( newParent == null ? null : newParent._lampIcon );
		_banner.SetParent( newParent == null ? null : newParent._banner );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_bonusPersent.Reset();
		_unsoulBoundRarity.Reset();
		_lampIcon.Reset();
		_banner.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_bonusPersent.IsDerivedFromParent()
			&& _unsoulBoundRarity.IsDerivedFromParent()
			&& _lampIcon.IsDerivedFromParent()
			&& _banner.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "bonusPersent" )
			_bonusPersent.Reset();
		else if ( fieldName == "unsoulBoundRarity" )
			_unsoulBoundRarity.Reset();
		else if ( fieldName == "lampIcon" )
			_lampIcon.Reset();
		else if ( fieldName == "banner" )
			_banner.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "bonusPersent" )
			return _bonusPersent.IsDerivedFromParent();
		if ( fieldName == "unsoulBoundRarity" )
			return _unsoulBoundRarity.IsDerivedFromParent();
		if ( fieldName == "lampIcon" )
			return _lampIcon.IsDerivedFromParent();
		if ( fieldName == "banner" )
			return _banner.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GoldPriceCycleTable : DBResource
{
	private UndoRedoDBPtr<GoldPriceCycleTable> ___parent;
	[HideInOutliner]
	public new DBPtr<GoldPriceCycleTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<GoldTable> _goldtable;

	public libdb.IChangeableList<GoldTable> goldtable { get { return _goldtable; } set { _goldtable.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GoldPriceCycleTable>(owner);
		_goldtable = new UndoRedoAssignableList<GoldTable>( owner );
		___parent.Changed += FireChangedEvent;
		_goldtable.Changed += FireChangedEvent;
	}

	public GoldPriceCycleTable()
	{
		Initialize( this );
	}
	private void AssignSelf( GoldPriceCycleTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GoldPriceCycleTable" );
		goldtable = source.goldtable;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GoldPriceCycleTable source = _source as GoldPriceCycleTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldPriceCycleTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GoldPriceCycleTable newParent = rawParent == null ? null : rawParent.Get<GoldPriceCycleTable>();
		if ( newParent == null && _newParent is GoldPriceCycleTable )
			newParent = _newParent as GoldPriceCycleTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_goldtable.SetParent( newParent == null ? null : newParent._goldtable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_goldtable.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_goldtable.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "goldtable" )
			_goldtable.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "goldtable" )
			return _goldtable.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GoldProductionBuilding : Constructon
{
	private UndoRedoDBPtr<GoldProductionBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<GoldProductionBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<HouseLevel> _HouseLevels;

	[Description( "Цикл домика (нужен всего 1 уровень, но название сохранено, чтобы с ним можно было работать так же, как с домиком для населения)" )]
	public libdb.IChangeableList<HouseLevel> HouseLevels { get { return _HouseLevels; } set { _HouseLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GoldProductionBuilding>(owner);
		_HouseLevels = new UndoRedoAssignableList<HouseLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_HouseLevels.Changed += FireChangedEvent;
	}

	public GoldProductionBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( GoldProductionBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GoldProductionBuilding" );
		HouseLevels = source.HouseLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GoldProductionBuilding source = _source as GoldProductionBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GoldProductionBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GoldProductionBuilding newParent = rawParent == null ? null : rawParent.Get<GoldProductionBuilding>();
		if ( newParent == null && _newParent is GoldProductionBuilding )
			newParent = _newParent as GoldProductionBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_HouseLevels.SetParent( newParent == null ? null : newParent._HouseLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_HouseLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_HouseLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "HouseLevels" )
			_HouseLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "HouseLevels" )
			return _HouseLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GuildBuilding : Constructon
{
	private UndoRedoDBPtr<GuildBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<GuildBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GuildBuilding>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public GuildBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( GuildBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GuildBuilding" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GuildBuilding source = _source as GuildBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GuildBuilding newParent = rawParent == null ? null : rawParent.Get<GuildBuilding>();
		if ( newParent == null && _newParent is GuildBuilding )
			newParent = _newParent as GuildBuilding;
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

[Custom("Social")]
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

[Custom("Social")]
public class HeroClassInfoTable : DBResource
{
	private UndoRedoDBPtr<HeroClassInfoTable> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroClassInfoTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<HeroClassInfo> _HeroClasses;

	public libdb.IChangeableList<HeroClassInfo> HeroClasses { get { return _HeroClasses; } set { _HeroClasses.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroClassInfoTable>(owner);
		_HeroClasses = new UndoRedoAssignableList<HeroClassInfo>( owner );
		___parent.Changed += FireChangedEvent;
		_HeroClasses.Changed += FireChangedEvent;
	}

	public HeroClassInfoTable()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroClassInfoTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroClassInfoTable" );
		HeroClasses = source.HeroClasses;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroClassInfoTable source = _source as HeroClassInfoTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroClassInfoTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroClassInfoTable newParent = rawParent == null ? null : rawParent.Get<HeroClassInfoTable>();
		if ( newParent == null && _newParent is HeroClassInfoTable )
			newParent = _newParent as HeroClassInfoTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_HeroClasses.SetParent( newParent == null ? null : newParent._HeroClasses );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_HeroClasses.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_HeroClasses.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "HeroClasses" )
			_HeroClasses.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "HeroClasses" )
			return _HeroClasses.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HeroesBuilding : Constructon
{
	private UndoRedoDBPtr<HeroesBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroesBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<HeroClassEnum> _heroClass;
	private UndoRedoList<EStat> _buffStats;
	private UndoRedoAssignableList<HeroesBuildingLevel> _HeroesBuildingLevels;

	[Description( "Роль героя, для которого предназначены бонусы домика" )]
	public HeroClassEnum heroClass { get { return _heroClass.Get(); } set { _heroClass.Set( value ); } }

	[Description( "Статы, на которые распространяются бонусы" )]
	[MinMaxSize(2, 2)]
	public libdb.IChangeableList<EStat> buffStats { get { return _buffStats; } set { _buffStats.Assign( value ); } }

	[Description( "Уровни HeroesBuilding" )]
	public libdb.IChangeableList<HeroesBuildingLevel> HeroesBuildingLevels { get { return _HeroesBuildingLevels; } set { _HeroesBuildingLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroesBuilding>(owner);
		_heroClass = new UndoRedo<HeroClassEnum>( owner, HeroClassEnum.None );
		_buffStats = new UndoRedoList<EStat>( owner, 2, 2 );
		_HeroesBuildingLevels = new UndoRedoAssignableList<HeroesBuildingLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_heroClass.Changed += FireChangedEvent;
		_buffStats.Changed += FireChangedEvent;
		_HeroesBuildingLevels.Changed += FireChangedEvent;
	}

	public HeroesBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroesBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroesBuilding" );
		heroClass = source.heroClass;
		buffStats = source.buffStats;
		HeroesBuildingLevels = source.HeroesBuildingLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroesBuilding source = _source as HeroesBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroesBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroesBuilding newParent = rawParent == null ? null : rawParent.Get<HeroesBuilding>();
		if ( newParent == null && _newParent is HeroesBuilding )
			newParent = _newParent as HeroesBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroClass.SetParent( newParent == null ? null : newParent._heroClass );
		_buffStats.SetParent( newParent == null ? null : newParent._buffStats );
		_HeroesBuildingLevels.SetParent( newParent == null ? null : newParent._HeroesBuildingLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroClass.Reset();
		_buffStats.Reset();
		_HeroesBuildingLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroClass.IsDerivedFromParent()
			&& _buffStats.IsDerivedFromParent()
			&& _HeroesBuildingLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroClass" )
			_heroClass.Reset();
		else if ( fieldName == "buffStats" )
			_buffStats.Reset();
		else if ( fieldName == "HeroesBuildingLevels" )
			_HeroesBuildingLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroClass" )
			return _heroClass.IsDerivedFromParent();
		if ( fieldName == "buffStats" )
			return _buffStats.IsDerivedFromParent();
		if ( fieldName == "HeroesBuildingLevels" )
			return _HeroesBuildingLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HoldGuild : GuildShopItemTarget
{
	private UndoRedoDBPtr<HoldGuild> ___parent;
	[HideInOutliner]
	public new DBPtr<HoldGuild> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HoldGuild>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public HoldGuild()
	{
		Initialize( this );
	}
	private void AssignSelf( HoldGuild source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HoldGuild" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HoldGuild source = _source as HoldGuild;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HoldGuild" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HoldGuild newParent = rawParent == null ? null : rawParent.Get<HoldGuild>();
		if ( newParent == null && _newParent is HoldGuild )
			newParent = _newParent as HoldGuild;
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
public class HouseBuilding : Constructon
{
	private UndoRedoDBPtr<HouseBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<HouseBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<HouseLevel> _HouseLevels;
	private UndoRedo<bool> _hasCustomProductionBoost;
	private UndoRedo<int> _productionTimePeriod;
	private UndoRedo<int> _minimalCollectTime;

	[Description( "Уровни жилого здания" )]
	public libdb.IChangeableList<HouseLevel> HouseLevels { get { return _HouseLevels; } set { _HouseLevels.Assign( value ); } }

	[Description( "Есть ли возможность ускорить производство" )]
	public bool hasCustomProductionBoost { get { return _hasCustomProductionBoost.Get(); } set { _hasCustomProductionBoost.Set( value ); } }

	[Description( "Единица времени, за которое производится единица ресурса из resourcesToProduce" )]
	public int productionTimePeriod { get { return _productionTimePeriod.Get(); } set { _productionTimePeriod.Set( value ); } }

	[Description( "Минимальное время через которое можно собрать ресурс" )]
	public int minimalCollectTime { get { return _minimalCollectTime.Get(); } set { _minimalCollectTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HouseBuilding>(owner);
		_HouseLevels = new UndoRedoAssignableList<HouseLevel>( owner );
		_hasCustomProductionBoost = new UndoRedo<bool>( owner, false );
		_productionTimePeriod = new UndoRedo<int>( owner, 0 );
		_minimalCollectTime = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_HouseLevels.Changed += FireChangedEvent;
		_hasCustomProductionBoost.Changed += FireChangedEvent;
		_productionTimePeriod.Changed += FireChangedEvent;
		_minimalCollectTime.Changed += FireChangedEvent;
	}

	public HouseBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( HouseBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HouseBuilding" );
		HouseLevels = source.HouseLevels;
		hasCustomProductionBoost = source.hasCustomProductionBoost;
		productionTimePeriod = source.productionTimePeriod;
		minimalCollectTime = source.minimalCollectTime;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HouseBuilding source = _source as HouseBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HouseBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HouseBuilding newParent = rawParent == null ? null : rawParent.Get<HouseBuilding>();
		if ( newParent == null && _newParent is HouseBuilding )
			newParent = _newParent as HouseBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_HouseLevels.SetParent( newParent == null ? null : newParent._HouseLevels );
		_hasCustomProductionBoost.SetParent( newParent == null ? null : newParent._hasCustomProductionBoost );
		_productionTimePeriod.SetParent( newParent == null ? null : newParent._productionTimePeriod );
		_minimalCollectTime.SetParent( newParent == null ? null : newParent._minimalCollectTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_HouseLevels.Reset();
		_hasCustomProductionBoost.Reset();
		_productionTimePeriod.Reset();
		_minimalCollectTime.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_HouseLevels.IsDerivedFromParent()
			&& _hasCustomProductionBoost.IsDerivedFromParent()
			&& _productionTimePeriod.IsDerivedFromParent()
			&& _minimalCollectTime.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "HouseLevels" )
			_HouseLevels.Reset();
		else if ( fieldName == "hasCustomProductionBoost" )
			_hasCustomProductionBoost.Reset();
		else if ( fieldName == "productionTimePeriod" )
			_productionTimePeriod.Reset();
		else if ( fieldName == "minimalCollectTime" )
			_minimalCollectTime.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "HouseLevels" )
			return _HouseLevels.IsDerivedFromParent();
		if ( fieldName == "hasCustomProductionBoost" )
			return _hasCustomProductionBoost.IsDerivedFromParent();
		if ( fieldName == "productionTimePeriod" )
			return _productionTimePeriod.IsDerivedFromParent();
		if ( fieldName == "minimalCollectTime" )
			return _minimalCollectTime.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class LibraryBuilding : Constructon
{
	private UndoRedoDBPtr<LibraryBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<LibraryBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<LibraryLevel> _LibraryLevels;

	[Description( "Уровни библиотеки" )]
	public libdb.IChangeableList<LibraryLevel> LibraryLevels { get { return _LibraryLevels; } set { _LibraryLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LibraryBuilding>(owner);
		_LibraryLevels = new UndoRedoAssignableList<LibraryLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_LibraryLevels.Changed += FireChangedEvent;
	}

	public LibraryBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( LibraryBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LibraryBuilding" );
		LibraryLevels = source.LibraryLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LibraryBuilding source = _source as LibraryBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LibraryBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LibraryBuilding newParent = rawParent == null ? null : rawParent.Get<LibraryBuilding>();
		if ( newParent == null && _newParent is LibraryBuilding )
			newParent = _newParent as LibraryBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_LibraryLevels.SetParent( newParent == null ? null : newParent._LibraryLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_LibraryLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_LibraryLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "LibraryLevels" )
			_LibraryLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "LibraryLevels" )
			return _LibraryLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class LimitsOfBuilding : DBResource
{
	private UndoRedoDBPtr<LimitsOfBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<LimitsOfBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _MaxNumberOfBuilding;
	private TextRef _LimitText;
	private UndoRedo<bool> _CountPocket;

	[Description( "Максимальное количество зданий этого типа на территории замка." )]
	public int MaxNumberOfBuilding { get { return _MaxNumberOfBuilding.Get(); } set { _MaxNumberOfBuilding.Set( value ); } }

	[Description( "Текст лимитной группы, например: <br><center>Построено зданий в Замке: {0} из {1}" )]
	public TextRef LimitText { get { return _LimitText; } set { _LimitText.Assign( value ); } }

	[Description( "Учитывать здания в кармане" )]
	public bool CountPocket { get { return _CountPocket.Get(); } set { _CountPocket.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LimitsOfBuilding>(owner);
		_MaxNumberOfBuilding = new UndoRedo<int>( owner, 0 );
		_LimitText = new TextRef( owner, new TextRef() );
		_CountPocket = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_MaxNumberOfBuilding.Changed += FireChangedEvent;
		_LimitText.Changed += FireChangedEvent;
		_CountPocket.Changed += FireChangedEvent;
	}

	public LimitsOfBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( LimitsOfBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LimitsOfBuilding" );
		MaxNumberOfBuilding = source.MaxNumberOfBuilding;
		LimitText = source.LimitText;
		CountPocket = source.CountPocket;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LimitsOfBuilding source = _source as LimitsOfBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LimitsOfBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LimitsOfBuilding newParent = rawParent == null ? null : rawParent.Get<LimitsOfBuilding>();
		if ( newParent == null && _newParent is LimitsOfBuilding )
			newParent = _newParent as LimitsOfBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_MaxNumberOfBuilding.SetParent( newParent == null ? null : newParent._MaxNumberOfBuilding );
		_LimitText.SetParent( newParent == null ? null : newParent._LimitText );
		_CountPocket.SetParent( newParent == null ? null : newParent._CountPocket );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_MaxNumberOfBuilding.Reset();
		_LimitText.Reset();
		_CountPocket.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_MaxNumberOfBuilding.IsDerivedFromParent()
			&& _LimitText.IsDerivedFromParent()
			&& _CountPocket.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "MaxNumberOfBuilding" )
			_MaxNumberOfBuilding.Reset();
		else if ( fieldName == "LimitText" )
			_LimitText.Reset();
		else if ( fieldName == "CountPocket" )
			_CountPocket.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "MaxNumberOfBuilding" )
			return _MaxNumberOfBuilding.IsDerivedFromParent();
		if ( fieldName == "LimitText" )
			return _LimitText.IsDerivedFromParent();
		if ( fieldName == "CountPocket" )
			return _CountPocket.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Lootbox : DBResource
{
	private UndoRedoDBPtr<Lootbox> ___parent;
	[HideInOutliner]
	public new DBPtr<Lootbox> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedoDBPtr<Texture> _image;
	private TextRef _name;
	private TextRef _tooltip;
	private UndoRedoDBPtr<RollContainer> _rollContainer;

	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	public DBPtr<RollContainer> rollContainer { get { return _rollContainer.Get(); } set { _rollContainer.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Lootbox>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_name = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_rollContainer = new UndoRedoDBPtr<RollContainer>( owner );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_rollContainer.Changed += FireChangedEvent;
	}

	public Lootbox()
	{
		Initialize( this );
	}
	private void AssignSelf( Lootbox source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Lootbox" );
		persistentId = source.persistentId;
		image = source.image;
		name = source.name;
		tooltip = source.tooltip;
		rollContainer = source.rollContainer;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Lootbox source = _source as Lootbox;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Lootbox" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Lootbox newParent = rawParent == null ? null : rawParent.Get<Lootbox>();
		if ( newParent == null && _newParent is Lootbox )
			newParent = _newParent as Lootbox;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_image.SetParent( newParent == null ? null : newParent._image );
		_name.SetParent( newParent == null ? null : newParent._name );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_rollContainer.SetParent( newParent == null ? null : newParent._rollContainer );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_image.Reset();
		_name.Reset();
		_tooltip.Reset();
		_rollContainer.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _rollContainer.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "rollContainer" )
			_rollContainer.Reset();
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
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "rollContainer" )
			return _rollContainer.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class LootboxGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<LootboxGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<LootboxGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Lootbox> _lootbox;

	public DBPtr<Lootbox> lootbox { get { return _lootbox.Get(); } set { _lootbox.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LootboxGuildShopItem>(owner);
		_lootbox = new UndoRedoDBPtr<Lootbox>( owner );
		___parent.Changed += FireChangedEvent;
		_lootbox.Changed += FireChangedEvent;
	}

	public LootboxGuildShopItem()
	{
		Initialize( this );
	}
	private void AssignSelf( LootboxGuildShopItem source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LootboxGuildShopItem" );
		lootbox = source.lootbox;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LootboxGuildShopItem source = _source as LootboxGuildShopItem;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LootboxGuildShopItem" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LootboxGuildShopItem newParent = rawParent == null ? null : rawParent.Get<LootboxGuildShopItem>();
		if ( newParent == null && _newParent is LootboxGuildShopItem )
			newParent = _newParent as LootboxGuildShopItem;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lootbox.SetParent( newParent == null ? null : newParent._lootbox );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lootbox.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lootbox.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lootbox" )
			_lootbox.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lootbox" )
			return _lootbox.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class BeginnersPack : MarketingEvent
{
	private UndoRedoDBPtr<BeginnersPack> ___parent;
	[HideInOutliner]
	public new DBPtr<BeginnersPack> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BeginnersPack>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public BeginnersPack()
	{
		Initialize( this );
	}
	private void AssignSelf( BeginnersPack source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BeginnersPack" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BeginnersPack source = _source as BeginnersPack;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BeginnersPack" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BeginnersPack newParent = rawParent == null ? null : rawParent.Get<BeginnersPack>();
		if ( newParent == null && _newParent is BeginnersPack )
			newParent = _newParent as BeginnersPack;
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
public class MDInitParams : DBResource
{
	private UndoRedoDBPtr<MDInitParams> ___parent;
	[HideInOutliner]
	public new DBPtr<MDInitParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ResourcesTable _resourceTable;
	private UndoRedo<int> _fame;

	[Description( "Начальные ресурсы" )]
	public ResourcesTable resourceTable { get { return _resourceTable; } set { _resourceTable.Assign( value ); } }

	[Description( "Начальный fame" )]
	public int fame { get { return _fame.Get(); } set { _fame.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MDInitParams>(owner);
		_resourceTable = new ResourcesTable( owner );
		_fame = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_resourceTable.Changed += FireChangedEvent;
		_fame.Changed += FireChangedEvent;
	}

	public MDInitParams()
	{
		Initialize( this );
	}
	private void AssignSelf( MDInitParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MDInitParams" );
		resourceTable = source.resourceTable;
		fame = source.fame;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MDInitParams source = _source as MDInitParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MDInitParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MDInitParams newParent = rawParent == null ? null : rawParent.Get<MDInitParams>();
		if ( newParent == null && _newParent is MDInitParams )
			newParent = _newParent as MDInitParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resourceTable.SetParent( newParent == null ? null : newParent._resourceTable );
		_fame.SetParent( newParent == null ? null : newParent._fame );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resourceTable.Reset();
		_fame.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resourceTable.IsDerivedFromParent()
			&& _fame.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resourceTable" )
			_resourceTable.Reset();
		else if ( fieldName == "fame" )
			_fame.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "resourceTable" )
			return _resourceTable.IsDerivedFromParent();
		if ( fieldName == "fame" )
			return _fame.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OneTimeGuildShopItem : GuildShopItem
{
	private UndoRedoDBPtr<OneTimeGuildShopItem> ___parent;
	[HideInOutliner]
	public new DBPtr<OneTimeGuildShopItem> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<GuildShopItemTarget>> _target;
	private UndoRedoDBPtr<GuildBuff> _guildBuff;

	[Description( "На кого воздействует бонус" )]
	public libdb.IChangeableList<DBPtr<GuildShopItemTarget>> target { get { return _target; } set { _target.Assign( value ); } }

	[Description( "Баф для этого айтема" )]
	public DBPtr<GuildBuff> guildBuff { get { return _guildBuff.Get(); } set { _guildBuff.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OneTimeGuildShopItem>(owner);
		_target = new UndoRedoAssignableList<DBPtr<GuildShopItemTarget>>( owner );
		_guildBuff = new UndoRedoDBPtr<GuildBuff>( owner );
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

[Custom("Social")]
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

[Custom("Social")]
public class PineTreeBuilding : Constructon
{
	private UndoRedoDBPtr<PineTreeBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<PineTreeBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<PineTreeLevel> _PineTreeLevels;

	[Description( "Уровни ёлки" )]
	public libdb.IChangeableList<PineTreeLevel> PineTreeLevels { get { return _PineTreeLevels; } set { _PineTreeLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PineTreeBuilding>(owner);
		_PineTreeLevels = new UndoRedoAssignableList<PineTreeLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_PineTreeLevels.Changed += FireChangedEvent;
	}

	public PineTreeBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( PineTreeBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PineTreeBuilding" );
		PineTreeLevels = source.PineTreeLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PineTreeBuilding source = _source as PineTreeBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PineTreeBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PineTreeBuilding newParent = rawParent == null ? null : rawParent.Get<PineTreeBuilding>();
		if ( newParent == null && _newParent is PineTreeBuilding )
			newParent = _newParent as PineTreeBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_PineTreeLevels.SetParent( newParent == null ? null : newParent._PineTreeLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_PineTreeLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_PineTreeLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "PineTreeLevels" )
			_PineTreeLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "PineTreeLevels" )
			return _PineTreeLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class PremiumEvent : MarketingEvent
{
	private UndoRedoDBPtr<PremiumEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<PremiumEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _prolongMessageText;
	private TextRef _buyMessageText;
	private TextRef _messageButtonText;

	public TextRef prolongMessageText { get { return _prolongMessageText; } set { _prolongMessageText.Assign( value ); } }

	public TextRef buyMessageText { get { return _buyMessageText; } set { _buyMessageText.Assign( value ); } }

	public TextRef messageButtonText { get { return _messageButtonText; } set { _messageButtonText.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PremiumEvent>(owner);
		_prolongMessageText = new TextRef( owner, new TextRef() );
		_buyMessageText = new TextRef( owner, new TextRef() );
		_messageButtonText = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_prolongMessageText.Changed += FireChangedEvent;
		_buyMessageText.Changed += FireChangedEvent;
		_messageButtonText.Changed += FireChangedEvent;
	}

	public PremiumEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( PremiumEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PremiumEvent" );
		prolongMessageText = source.prolongMessageText;
		buyMessageText = source.buyMessageText;
		messageButtonText = source.messageButtonText;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PremiumEvent source = _source as PremiumEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PremiumEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PremiumEvent newParent = rawParent == null ? null : rawParent.Get<PremiumEvent>();
		if ( newParent == null && _newParent is PremiumEvent )
			newParent = _newParent as PremiumEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_prolongMessageText.SetParent( newParent == null ? null : newParent._prolongMessageText );
		_buyMessageText.SetParent( newParent == null ? null : newParent._buyMessageText );
		_messageButtonText.SetParent( newParent == null ? null : newParent._messageButtonText );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_prolongMessageText.Reset();
		_buyMessageText.Reset();
		_messageButtonText.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_prolongMessageText.IsDerivedFromParent()
			&& _buyMessageText.IsDerivedFromParent()
			&& _messageButtonText.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "prolongMessageText" )
			_prolongMessageText.Reset();
		else if ( fieldName == "buyMessageText" )
			_buyMessageText.Reset();
		else if ( fieldName == "messageButtonText" )
			_messageButtonText.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "prolongMessageText" )
			return _prolongMessageText.IsDerivedFromParent();
		if ( fieldName == "buyMessageText" )
			return _buyMessageText.IsDerivedFromParent();
		if ( fieldName == "messageButtonText" )
			return _messageButtonText.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class PrimeArenaEvent : MarketingEvent
{
	private UndoRedoDBPtr<PrimeArenaEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<PrimeArenaEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PrimeArenaEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public PrimeArenaEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( PrimeArenaEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PrimeArenaEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PrimeArenaEvent source = _source as PrimeArenaEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PrimeArenaEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PrimeArenaEvent newParent = rawParent == null ? null : rawParent.Get<PrimeArenaEvent>();
		if ( newParent == null && _newParent is PrimeArenaEvent )
			newParent = _newParent as PrimeArenaEvent;
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
public class ProductionBuilding : Constructon
{
	private UndoRedoDBPtr<ProductionBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<ProductionBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ProductionLevel> _ProductionLevels;
	private UndoRedo<bool> _hasCustomProductionBoost;
	private UndoRedo<int> _productionTimePeriod;
	private UndoRedo<int> _minimalCollectTime;

	[Description( "Уровни добывающего здания" )]
	public libdb.IChangeableList<ProductionLevel> ProductionLevels { get { return _ProductionLevels; } set { _ProductionLevels.Assign( value ); } }

	[Description( "Есть ли возможность ускорить производство" )]
	public bool hasCustomProductionBoost { get { return _hasCustomProductionBoost.Get(); } set { _hasCustomProductionBoost.Set( value ); } }

	[Description( "Единица времени, за которое производится единица ресурса из resourcesToProduce" )]
	public int productionTimePeriod { get { return _productionTimePeriod.Get(); } set { _productionTimePeriod.Set( value ); } }

	[Description( "Минимальное время через которое можно собрать ресурс" )]
	public int minimalCollectTime { get { return _minimalCollectTime.Get(); } set { _minimalCollectTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ProductionBuilding>(owner);
		_ProductionLevels = new UndoRedoAssignableList<ProductionLevel>( owner );
		_hasCustomProductionBoost = new UndoRedo<bool>( owner, false );
		_productionTimePeriod = new UndoRedo<int>( owner, 0 );
		_minimalCollectTime = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_ProductionLevels.Changed += FireChangedEvent;
		_hasCustomProductionBoost.Changed += FireChangedEvent;
		_productionTimePeriod.Changed += FireChangedEvent;
		_minimalCollectTime.Changed += FireChangedEvent;
	}

	public ProductionBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( ProductionBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ProductionBuilding" );
		ProductionLevels = source.ProductionLevels;
		hasCustomProductionBoost = source.hasCustomProductionBoost;
		productionTimePeriod = source.productionTimePeriod;
		minimalCollectTime = source.minimalCollectTime;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ProductionBuilding source = _source as ProductionBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ProductionBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ProductionBuilding newParent = rawParent == null ? null : rawParent.Get<ProductionBuilding>();
		if ( newParent == null && _newParent is ProductionBuilding )
			newParent = _newParent as ProductionBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ProductionLevels.SetParent( newParent == null ? null : newParent._ProductionLevels );
		_hasCustomProductionBoost.SetParent( newParent == null ? null : newParent._hasCustomProductionBoost );
		_productionTimePeriod.SetParent( newParent == null ? null : newParent._productionTimePeriod );
		_minimalCollectTime.SetParent( newParent == null ? null : newParent._minimalCollectTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ProductionLevels.Reset();
		_hasCustomProductionBoost.Reset();
		_productionTimePeriod.Reset();
		_minimalCollectTime.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ProductionLevels.IsDerivedFromParent()
			&& _hasCustomProductionBoost.IsDerivedFromParent()
			&& _productionTimePeriod.IsDerivedFromParent()
			&& _minimalCollectTime.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ProductionLevels" )
			_ProductionLevels.Reset();
		else if ( fieldName == "hasCustomProductionBoost" )
			_hasCustomProductionBoost.Reset();
		else if ( fieldName == "productionTimePeriod" )
			_productionTimePeriod.Reset();
		else if ( fieldName == "minimalCollectTime" )
			_minimalCollectTime.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ProductionLevels" )
			return _ProductionLevels.IsDerivedFromParent();
		if ( fieldName == "hasCustomProductionBoost" )
			return _hasCustomProductionBoost.IsDerivedFromParent();
		if ( fieldName == "productionTimePeriod" )
			return _productionTimePeriod.IsDerivedFromParent();
		if ( fieldName == "minimalCollectTime" )
			return _minimalCollectTime.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
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

[Custom("Social")]
public class RatingDecreaseByTime : DBResource
{
	private UndoRedoDBPtr<RatingDecreaseByTime> ___parent;
	[HideInOutliner]
	public new DBPtr<RatingDecreaseByTime> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minRatingToLoose;
	private UndoRedoDBPtr<Quest> _ratingUpdateQuest;
	private UndoRedoAssignableList<RatingLossToInactivityDays> _ratings;

	[Description( "Рейтинга с которого начинаем что-то терять при неактивности" )]
	public int minRatingToLoose { get { return _minRatingToLoose.Get(); } set { _minRatingToLoose.Set( value ); } }

	[Description( "Квест, который выдаётся за потерю рейтинга" )]
	public DBPtr<Quest> ratingUpdateQuest { get { return _ratingUpdateQuest.Get(); } set { _ratingUpdateQuest.Set( value ); } }

	[Description( "Список соответствий потеря рейтинга-дни без боёв" )]
	public libdb.IChangeableList<RatingLossToInactivityDays> ratings { get { return _ratings; } set { _ratings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RatingDecreaseByTime>(owner);
		_minRatingToLoose = new UndoRedo<int>( owner, 0 );
		_ratingUpdateQuest = new UndoRedoDBPtr<Quest>( owner );
		_ratings = new UndoRedoAssignableList<RatingLossToInactivityDays>( owner );
		___parent.Changed += FireChangedEvent;
		_minRatingToLoose.Changed += FireChangedEvent;
		_ratingUpdateQuest.Changed += FireChangedEvent;
		_ratings.Changed += FireChangedEvent;
	}

	public RatingDecreaseByTime()
	{
		Initialize( this );
	}
	private void AssignSelf( RatingDecreaseByTime source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RatingDecreaseByTime" );
		minRatingToLoose = source.minRatingToLoose;
		ratingUpdateQuest = source.ratingUpdateQuest;
		ratings = source.ratings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RatingDecreaseByTime source = _source as RatingDecreaseByTime;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RatingDecreaseByTime" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RatingDecreaseByTime newParent = rawParent == null ? null : rawParent.Get<RatingDecreaseByTime>();
		if ( newParent == null && _newParent is RatingDecreaseByTime )
			newParent = _newParent as RatingDecreaseByTime;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minRatingToLoose.SetParent( newParent == null ? null : newParent._minRatingToLoose );
		_ratingUpdateQuest.SetParent( newParent == null ? null : newParent._ratingUpdateQuest );
		_ratings.SetParent( newParent == null ? null : newParent._ratings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minRatingToLoose.Reset();
		_ratingUpdateQuest.Reset();
		_ratings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minRatingToLoose.IsDerivedFromParent()
			&& _ratingUpdateQuest.IsDerivedFromParent()
			&& _ratings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minRatingToLoose" )
			_minRatingToLoose.Reset();
		else if ( fieldName == "ratingUpdateQuest" )
			_ratingUpdateQuest.Reset();
		else if ( fieldName == "ratings" )
			_ratings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minRatingToLoose" )
			return _minRatingToLoose.IsDerivedFromParent();
		if ( fieldName == "ratingUpdateQuest" )
			return _ratingUpdateQuest.IsDerivedFromParent();
		if ( fieldName == "ratings" )
			return _ratings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class RerollShopBuilding : Constructon
{
	private UndoRedoDBPtr<RerollShopBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<RerollShopBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RerollShopBuilding>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public RerollShopBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( RerollShopBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RerollShopBuilding" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RerollShopBuilding source = _source as RerollShopBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RerollShopBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RerollShopBuilding newParent = rawParent == null ? null : rawParent.Get<RerollShopBuilding>();
		if ( newParent == null && _newParent is RerollShopBuilding )
			newParent = _newParent as RerollShopBuilding;
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
public class ResourceAndInventoryLimits : DBResource
{
	private UndoRedoDBPtr<ResourceAndInventoryLimits> ___parent;
	[HideInOutliner]
	public new DBPtr<ResourceAndInventoryLimits> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ResourcesTable _resourceLimits;
	private UndoRedo<int> _inventoryLimits;

	[Description( "Начальные лимиты" )]
	public ResourcesTable resourceLimits { get { return _resourceLimits; } set { _resourceLimits.Assign( value ); } }

	[Description( "Начальные лимит библиотеки" )]
	public int inventoryLimits { get { return _inventoryLimits.Get(); } set { _inventoryLimits.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ResourceAndInventoryLimits>(owner);
		_resourceLimits = new ResourcesTable( owner );
		_inventoryLimits = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_resourceLimits.Changed += FireChangedEvent;
		_inventoryLimits.Changed += FireChangedEvent;
	}

	public ResourceAndInventoryLimits()
	{
		Initialize( this );
	}
	private void AssignSelf( ResourceAndInventoryLimits source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ResourceAndInventoryLimits" );
		resourceLimits = source.resourceLimits;
		inventoryLimits = source.inventoryLimits;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ResourceAndInventoryLimits source = _source as ResourceAndInventoryLimits;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceAndInventoryLimits" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ResourceAndInventoryLimits newParent = rawParent == null ? null : rawParent.Get<ResourceAndInventoryLimits>();
		if ( newParent == null && _newParent is ResourceAndInventoryLimits )
			newParent = _newParent as ResourceAndInventoryLimits;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resourceLimits.SetParent( newParent == null ? null : newParent._resourceLimits );
		_inventoryLimits.SetParent( newParent == null ? null : newParent._inventoryLimits );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resourceLimits.Reset();
		_inventoryLimits.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resourceLimits.IsDerivedFromParent()
			&& _inventoryLimits.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resourceLimits" )
			_resourceLimits.Reset();
		else if ( fieldName == "inventoryLimits" )
			_inventoryLimits.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "resourceLimits" )
			return _resourceLimits.IsDerivedFromParent();
		if ( fieldName == "inventoryLimits" )
			return _inventoryLimits.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SectionsSet : DBResource
{
	private UndoRedoDBPtr<SectionsSet> ___parent;
	[HideInOutliner]
	public new DBPtr<SectionsSet> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<IntVec2> _Sections;

	public libdb.IChangeableList<IntVec2> Sections { get { return _Sections; } set { _Sections.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SectionsSet>(owner);
		_Sections = new UndoRedoAssignableList<IntVec2>( owner );
		___parent.Changed += FireChangedEvent;
		_Sections.Changed += FireChangedEvent;
	}

	public SectionsSet()
	{
		Initialize( this );
	}
	private void AssignSelf( SectionsSet source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SectionsSet" );
		Sections = source.Sections;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SectionsSet source = _source as SectionsSet;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SectionsSet" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SectionsSet newParent = rawParent == null ? null : rawParent.Get<SectionsSet>();
		if ( newParent == null && _newParent is SectionsSet )
			newParent = _newParent as SectionsSet;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Sections.SetParent( newParent == null ? null : newParent._Sections );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Sections.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Sections.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Sections" )
			_Sections.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Sections" )
			return _Sections.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
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

[UseTypeName("ROOT")]
[Custom("Social")]
public class SocialRoot : DBResource
{
	private UndoRedoDBPtr<SocialRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SocialRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<CommonConstructionsSettings> _CommonConstructionsSettings;
	private UndoRedoAssignableList<DBPtr<Constructon>> _Constructions;
	private UndoRedoDBPtr<HeroesDB> _Heroes;
	private UndoRedoAssignableList<DBPtr<Talent>> _Talents;
	private UndoRedoDBPtr<DBLevelToFame> _LevelToFameTable;
	private LevelToResources _LevelToResources;
	private UndoRedoDBPtr<DBStatpointsToLevel> _StatpointsToLevelTable;
	private UndoRedoDBPtr<DBLevelToExperience> _LevelToExperienceTable;
	private UndoRedoDBPtr<DBRatingToFame> _HeroRatingToFameLevel;
	private HonorLevelTable _HonorLevelTable;
	private UndoRedoDBPtr<StatsBudgetContainer> _StatsBudgetContainer;
	private UndoRedoDBPtr<UIRoot> _UIRoot;
	private UndoRedoDBPtr<DBUIData> _DBUIData;
	private UndoRedoDBPtr<RollSettings> _SessionRollSettings;
	private UndoRedoDBPtr<HeroClassInfoTable> _HeroClassesTable;
	private UndoRedoDBPtr<ErrorMessagesTable> _ErrorsTextsTable;
	private UndoRedoDBPtr<AILogicParameters> _AIGameLogic;
	private UndoRedoDBPtr<UnitsLogicParameters> _UnitLogicParameters;
	private UndoRedoDBPtr<DBMap> _Map;
	private UndoRedoAssignableList<ResourcesTable> _TalentsSellPrice;
	private UndoRedoAssignableList<TalentLevelToUnsoulboundPrice> _TalentsUnsoulboundPriceByLevel;
	private UndoRedo<ETalentRarity> _RaritiesWithoutSoulbound;
	private UndoRedoAssignableList<ConstructionTabDesc> _ConstructionTabDescs;
	private UndoRedoAssignableList<ConstructionTabDesc> _HeroesTabDescs;
	private UndoRedoDBPtr<GoldPriceCycleTable> _GoldPriceCycleTable;
	private UndoRedoDBPtr<MDInitParams> _GuestInitParams;
	private UndoRedoDBPtr<MDInitParams> _PlayerInitParams;
	private UndoRedoDBPtr<ResourceAndInventoryLimits> _ResourceAndInventoryLimits;
	private UndoRedoDBPtr<ResourceAndInventoryLimits> _GuestResourceAndInventoryLimits;
	private UndoRedoAssignableList<BuildedConstruction> _BuildedConstructions;
	private UndoRedoDBPtr<DBRollTalentPercents> _RollTalentForTransmutationBuilding;
	private UndoRedoDBPtr<DBRollTalentPercents> _RollTalentPremiumForTransmutationBuilding;
	private UndoRedoAssignableList<DBPtr<QuestLine>> _Quests;
	private UndoRedoAssignableList<DBPtr<Quest>> _SingleQuests;
	private UndoRedoDBPtr<Quest> _StartQuest;
	private UndoRedoDBPtr<Quest> _StartQuestsForFractionChange;
	private ResourcesCoefTable _ResetStatsPriceCoef;
	private UndoRedo<int> _MaxEmptyTalents;
	private UndoRedoDBPtr<CastleCutscene> _SceneObservationCameraFlyCutScene;
	private UndoRedoAssignableList<DefaultMap> _DefaultMaps;
	private UndoRedoAssignableList<DBPtr<DBAdvMapDescGroup>> _GroupMaps;
	private UndoRedoDBPtr<MapList> _AviableMaps;
	private UndoRedo<int> _FirstBuyHeroExpBonus;
	private MarketingEvents _MarketingEvents;
	private UndoRedoAssignableList<RarityToPointsAndLevel> _TalentLevelToPointsAndRarity;
	private UndoRedoAssignableList<RarityToLevelAndPrice> _TalentMergePriceToLevelAndRarity;
	private UndoRedoList<int> _TalentConsumptionPointsToRarity;
	private UndoRedoAssignableList<BathPriceToHeroLevel> _BathPriceToHeroLevel;
	private UndoRedoDBPtr<GuildLevels> _GuildLevels;
	private UndoRedoAssignableList<GoldLampRollSettings> _LampEventsSettings;
	private FreeSkipsEventBuildings _freeSkipsEventBuildings;
	private UndoRedoDBPtr<Texture> _RandomHeroIcon;
	private UndoRedoDBPtr<Credits> _Credits;
	private UndoRedoDBPtr<GuildVisibleBonusesCount> _GuildVisibleBonusesCount;
	private UndoRedoAssignableList<DBPtr<Texture>> _AdditionalTextures;
	private UndoRedoAssignableList<DBPtr<Quest>> _QuestsThatDontHideScreenBlocker;
	private UndoRedoAssignableList<ReforgeTalentPrice> _ReforgeTalentPrices;
	private UndoRedoAssignableList<DBPtr<UITexts>> _UITexts;
	private UndoRedoDBPtr<RatingDecreaseByTime> _RatingDecreaseByTime;
	private UndoRedoAssignableList<GuildSuzerenLevel> _GuildShopLevelToSuzerenExperience;
	private UndoRedoAssignableList<DBPtr<GuildShopItem>> _GuildShopItems;
	private UndoRedoDBPtr<GuildBuffsCollection> _GuildBuffsCollection;
	private UndoRedoList<int> _GuildRatingRanges;
	private ClanWarsData _ClanWarsData;
	private GuildRecruitment _GuildRecruitment;
	private ContextBuyResourceTabel _resourcesToGoldPrice;
	private RerollShopSettings _RerollShop;
	private UndoRedoAssignableList<SeasonSettings> _Seasons;
	private UndoRedoAssignableList<SeasonLeagueSettings> _SeasonLeagues;
	private UndoRedoDBPtr<DynamicQuestForTalents> _DynamicQuestForTalents;
	private UndoRedoDBPtr<TalentsCollectionSettings> _talentsCollectionSettings;
	private UndoRedoDBPtr<CurrencyDescriptionList> _currencies;
	private UndoRedoAssignableList<DBPtr<Lootbox>> _Lootboxes;
	private UndoRedoAssignableList<DBPtr<TalentUpgradeEntity>> _TalentUpgradeEntities;

	public DBPtr<CommonConstructionsSettings> CommonConstructionsSettings { get { return _CommonConstructionsSettings.Get(); } set { _CommonConstructionsSettings.Set( value ); } }

	[Description( "Список зданий замка" )]
	public libdb.IChangeableList<DBPtr<Constructon>> Constructions { get { return _Constructions; } set { _Constructions.Assign( value ); } }

	[Description( "Список героев замка" )]
	public DBPtr<HeroesDB> Heroes { get { return _Heroes.Get(); } set { _Heroes.Set( value ); } }

	[Description( "Список талантов замка" )]
	public libdb.IChangeableList<DBPtr<Talent>> Talents { get { return _Talents; } set { _Talents.Assign( value ); } }

	[Description( "Таблица перевода количества fame в уровень лорда" )]
	public DBPtr<DBLevelToFame> LevelToFameTable { get { return _LevelToFameTable.Get(); } set { _LevelToFameTable.Set( value ); } }

	[Description( "Таблица сколько дают ресурсов за достижение определенного уровня" )]
	public LevelToResources LevelToResources { get { return _LevelToResources; } set { _LevelToResources.Assign( value ); } }

	[Description( "Количество статпоинтов, дающихся за уровень" )]
	public DBPtr<DBStatpointsToLevel> StatpointsToLevelTable { get { return _StatpointsToLevelTable.Get(); } set { _StatpointsToLevelTable.Set( value ); } }

	[Description( "Таблица перевода количества опыта в уровень героя" )]
	public DBPtr<DBLevelToExperience> LevelToExperienceTable { get { return _LevelToExperienceTable.Get(); } set { _LevelToExperienceTable.Set( value ); } }

	[Description( "Таблица зависимости количества очков рейтинга новых героев от уровня фейма" )]
	public DBPtr<DBRatingToFame> HeroRatingToFameLevel { get { return _HeroRatingToFameLevel.Get(); } set { _HeroRatingToFameLevel.Set( value ); } }

	[Description( "Таблица уровней системы чести" )]
	public HonorLevelTable HonorLevelTable { get { return _HonorLevelTable; } set { _HonorLevelTable.Assign( value ); } }

	public DBPtr<StatsBudgetContainer> StatsBudgetContainer { get { return _StatsBudgetContainer.Get(); } set { _StatsBudgetContainer.Set( value ); } }

	public DBPtr<UIRoot> UIRoot { get { return _UIRoot.Get(); } set { _UIRoot.Set( value ); } }

	public DBPtr<DBUIData> DBUIData { get { return _DBUIData.Get(); } set { _DBUIData.Set( value ); } }

	[Description( "Таблица ролла для сессии" )]
	public DBPtr<RollSettings> SessionRollSettings { get { return _SessionRollSettings.Get(); } set { _SessionRollSettings.Set( value ); } }

	[Description( "Класификация героев" )]
	public DBPtr<HeroClassInfoTable> HeroClassesTable { get { return _HeroClassesTable.Get(); } set { _HeroClassesTable.Set( value ); } }

	[Description( "Список сопоставления номера ошибки соцсервера с текстом для пользователя" )]
	public DBPtr<ErrorMessagesTable> ErrorsTextsTable { get { return _ErrorsTextsTable.Get(); } set { _ErrorsTextsTable.Set( value ); } }

	public DBPtr<AILogicParameters> AIGameLogic { get { return _AIGameLogic.Get(); } set { _AIGameLogic.Set( value ); } }

	public DBPtr<UnitsLogicParameters> UnitLogicParameters { get { return _UnitLogicParameters.Get(); } set { _UnitLogicParameters.Set( value ); } }

	[Description( "Карта замка" )]
	public DBPtr<DBMap> Map { get { return _Map.Get(); } set { _Map.Set( value ); } }

	[Description( "Цены на продажу талантов" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<ResourcesTable> TalentsSellPrice { get { return _TalentsSellPrice; } set { _TalentsSellPrice.Assign( value ); } }

	[Description( "Цены на unsoulbound" )]
	public libdb.IChangeableList<TalentLevelToUnsoulboundPrice> TalentsUnsoulboundPriceByLevel { get { return _TalentsUnsoulboundPriceByLevel; } set { _TalentsUnsoulboundPriceByLevel.Assign( value ); } }

	[Description( "Рар до которого таланты не привязываются к герою включительно" )]
	public ETalentRarity RaritiesWithoutSoulbound { get { return _RaritiesWithoutSoulbound.Get(); } set { _RaritiesWithoutSoulbound.Set( value ); } }

	[EnumArray(typeof(ConstructionTab))]
	public libdb.IChangeableList<ConstructionTabDesc> ConstructionTabDescs { get { return _ConstructionTabDescs; } set { _ConstructionTabDescs.Assign( value ); } }

	[EnumArray(typeof(HeroClassEnum))]
	public libdb.IChangeableList<ConstructionTabDesc> HeroesTabDescs { get { return _HeroesTabDescs; } set { _HeroesTabDescs.Assign( value ); } }

	[Description( "Параметры ускорений циклов за деньги" )]
	public DBPtr<GoldPriceCycleTable> GoldPriceCycleTable { get { return _GoldPriceCycleTable.Get(); } set { _GoldPriceCycleTable.Set( value ); } }

	[Description( "Начальные параметры гостя" )]
	public DBPtr<MDInitParams> GuestInitParams { get { return _GuestInitParams.Get(); } set { _GuestInitParams.Set( value ); } }

	[Description( "Начальные параметры игрока" )]
	public DBPtr<MDInitParams> PlayerInitParams { get { return _PlayerInitParams.Get(); } set { _PlayerInitParams.Set( value ); } }

	[Description( "Начальные лимиты игрока" )]
	public DBPtr<ResourceAndInventoryLimits> ResourceAndInventoryLimits { get { return _ResourceAndInventoryLimits.Get(); } set { _ResourceAndInventoryLimits.Set( value ); } }

	[Description( "Начальные лимиты гостя" )]
	public DBPtr<ResourceAndInventoryLimits> GuestResourceAndInventoryLimits { get { return _GuestResourceAndInventoryLimits.Get(); } set { _GuestResourceAndInventoryLimits.Set( value ); } }

	[Description( "Первоначальные, сразу построенные домики" )]
	public libdb.IChangeableList<BuildedConstruction> BuildedConstructions { get { return _BuildedConstructions; } set { _BuildedConstructions.Assign( value ); } }

	[Description( "Табличка процентов на ролл талантов в кузнице" )]
	public DBPtr<DBRollTalentPercents> RollTalentForTransmutationBuilding { get { return _RollTalentForTransmutationBuilding.Get(); } set { _RollTalentForTransmutationBuilding.Set( value ); } }

	[Description( "Табличка процентов на ролл талантов в кузнице с активным премиумом" )]
	public DBPtr<DBRollTalentPercents> RollTalentPremiumForTransmutationBuilding { get { return _RollTalentPremiumForTransmutationBuilding.Get(); } set { _RollTalentPremiumForTransmutationBuilding.Set( value ); } }

	[Description( "Полный список линеек квестов" )]
	public libdb.IChangeableList<DBPtr<QuestLine>> Quests { get { return _Quests; } set { _Quests.Assign( value ); } }

	[Description( "Список одиночных квестов" )]
	public libdb.IChangeableList<DBPtr<Quest>> SingleQuests { get { return _SingleQuests; } set { _SingleQuests.Assign( value ); } }

	[Description( "Стартовый квест" )]
	public DBPtr<Quest> StartQuest { get { return _StartQuest.Get(); } set { _StartQuest.Set( value ); } }

	[Description( "Квесты, которые выдаются при смене фракции" )]
	public DBPtr<Quest> StartQuestsForFractionChange { get { return _StartQuestsForFractionChange.Get(); } set { _StartQuestsForFractionChange.Set( value ); } }

	[Description( "Коэффициент сброса статов героя" )]
	public ResourcesCoefTable ResetStatsPriceCoef { get { return _ResetStatsPriceCoef; } set { _ResetStatsPriceCoef.Assign( value ); } }

	[Description( "Максимально допустимое количество отсутствующих талантов для старта матчмейкинга" )]
	public int MaxEmptyTalents { get { return _MaxEmptyTalents.Get(); } set { _MaxEmptyTalents.Set( value ); } }

	[Description( "Кат сцена пролета камеры. Показывается, например, при первом входе в социальный клиент." )]
	public DBPtr<CastleCutscene> SceneObservationCameraFlyCutScene { get { return _SceneObservationCameraFlyCutScene.Get(); } set { _SceneObservationCameraFlyCutScene.Set( value ); } }

	[Description( "Список дефолтовых карт для каждого режима/слота на экране ворот" )]
	[EnumArray(typeof(MapType))]
	public libdb.IChangeableList<DefaultMap> DefaultMaps { get { return _DefaultMaps; } set { _DefaultMaps.Assign( value ); } }

	[Description( "Список групп карт" )]
	public libdb.IChangeableList<DBPtr<DBAdvMapDescGroup>> GroupMaps { get { return _GroupMaps; } set { _GroupMaps.Assign( value ); } }

	[Description( "Список доступных для замка карт" )]
	public DBPtr<MapList> AviableMaps { get { return _AviableMaps.Get(); } set { _AviableMaps.Set( value ); } }

	[Description( "Количество дополнительного опыта для купленных героев от домиков FirstBuy" )]
	public int FirstBuyHeroExpBonus { get { return _FirstBuyHeroExpBonus.Get(); } set { _FirstBuyHeroExpBonus.Set( value ); } }

	[Description( "Описание акций" )]
	public MarketingEvents MarketingEvents { get { return _MarketingEvents; } set { _MarketingEvents.Assign( value ); } }

	[Description( "Таблица зависимости уровня таланта от его рарности и количества вложенных в него points. Увеличивая максимальный уровень, не забудь увеличить в Tools/Scripts/FillCompiledTooltips.cs в MAX_REFINE_RATE!" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<RarityToPointsAndLevel> TalentLevelToPointsAndRarity { get { return _TalentLevelToPointsAndRarity; } set { _TalentLevelToPointsAndRarity.Assign( value ); } }

	[Description( "Таблица зависимости цены таланта от его рарности и уровня" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<RarityToLevelAndPrice> TalentMergePriceToLevelAndRarity { get { return _TalentMergePriceToLevelAndRarity; } set { _TalentMergePriceToLevelAndRarity.Assign( value ); } }

	[Description( "Зависимость количества points который дает талант при его поглощении от его рарности" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<int> TalentConsumptionPointsToRarity { get { return _TalentConsumptionPointsToRarity; } set { _TalentConsumptionPointsToRarity.Assign( value ); } }

	[Description( "Зависимость стоимости восстановления единцы энергии от уровня героя" )]
	public libdb.IChangeableList<BathPriceToHeroLevel> BathPriceToHeroLevel { get { return _BathPriceToHeroLevel; } set { _BathPriceToHeroLevel.Assign( value ); } }

	[Description( "инфа по левелапам гильдии" )]
	public DBPtr<GuildLevels> GuildLevels { get { return _GuildLevels.Get(); } set { _GuildLevels.Set( value ); } }

	[Description( "Зависимости для вероятностей выпадания лампы от даты последнего платежа" )]
	public libdb.IChangeableList<GoldLampRollSettings> LampEventsSettings { get { return _LampEventsSettings; } set { _LampEventsSettings.Assign( value ); } }

	public FreeSkipsEventBuildings freeSkipsEventBuildings { get { return _freeSkipsEventBuildings; } set { _freeSkipsEventBuildings.Assign( value ); } }

	public DBPtr<Texture> RandomHeroIcon { get { return _RandomHeroIcon.Get(); } set { _RandomHeroIcon.Set( value ); } }

	public DBPtr<Credits> Credits { get { return _Credits.Get(); } set { _Credits.Set( value ); } }

	public DBPtr<GuildVisibleBonusesCount> GuildVisibleBonusesCount { get { return _GuildVisibleBonusesCount.Get(); } set { _GuildVisibleBonusesCount.Set( value ); } }

	[Description( "Иконки, которые должны появиться в замке" )]
	public libdb.IChangeableList<DBPtr<Texture>> AdditionalTextures { get { return _AdditionalTextures; } set { _AdditionalTextures.Assign( value ); } }

	[Description( "Квест, при существовании которого у нас не снимается заставка" )]
	public libdb.IChangeableList<DBPtr<Quest>> QuestsThatDontHideScreenBlocker { get { return _QuestsThatDontHideScreenBlocker; } set { _QuestsThatDontHideScreenBlocker.Assign( value ); } }

	[Description( "Стоимость перековки разных рарностей талантов" )]
	public libdb.IChangeableList<ReforgeTalentPrice> ReforgeTalentPrices { get { return _ReforgeTalentPrices; } set { _ReforgeTalentPrices.Assign( value ); } }

	[Description( "Текстовые ресурсы для соц. клиента. Используются в UI и локализуются." )]
	public libdb.IChangeableList<DBPtr<UITexts>> UITexts { get { return _UITexts; } set { _UITexts.Assign( value ); } }

	[Description( "Изменение рейтинга неактивных игроков" )]
	public DBPtr<RatingDecreaseByTime> RatingDecreaseByTime { get { return _RatingDecreaseByTime.Get(); } set { _RatingDecreaseByTime.Set( value ); } }

	[Description( "Рейтинг сюзерена к уровню магазина" )]
	public libdb.IChangeableList<GuildSuzerenLevel> GuildShopLevelToSuzerenExperience { get { return _GuildShopLevelToSuzerenExperience; } set { _GuildShopLevelToSuzerenExperience.Assign( value ); } }

	[Description( "Ассортимент для кланового магазина" )]
	public libdb.IChangeableList<DBPtr<GuildShopItem>> GuildShopItems { get { return _GuildShopItems; } set { _GuildShopItems.Assign( value ); } }

	[Description( "Гильдийские бафы" )]
	public DBPtr<GuildBuffsCollection> GuildBuffsCollection { get { return _GuildBuffsCollection.Get(); } set { _GuildBuffsCollection.Set( value ); } }

	[Description( "Список интервалов рейтингов" )]
	public libdb.IChangeableList<int> GuildRatingRanges { get { return _GuildRatingRanges; } set { _GuildRatingRanges.Assign( value ); } }

	[Description( "Данные для клановых войн" )]
	public ClanWarsData ClanWarsData { get { return _ClanWarsData; } set { _ClanWarsData.Assign( value ); } }

	[Description( "Данные для поиска подходящих кланов игроками" )]
	public GuildRecruitment GuildRecruitment { get { return _GuildRecruitment; } set { _GuildRecruitment.Assign( value ); } }

	[Description( "Кол-во ресурсов, которое покупается за 1 золотой" )]
	public ContextBuyResourceTabel resourcesToGoldPrice { get { return _resourcesToGoldPrice; } set { _resourcesToGoldPrice.Assign( value ); } }

	[Description( "Настройки магазина с рероллом" )]
	public RerollShopSettings RerollShop { get { return _RerollShop; } set { _RerollShop.Assign( value ); } }

	[Description( "Настройки сезонов" )]
	public libdb.IChangeableList<SeasonSettings> Seasons { get { return _Seasons; } set { _Seasons.Assign( value ); } }

	[Description( "Настройки лиг" )]
	public libdb.IChangeableList<SeasonLeagueSettings> SeasonLeagues { get { return _SeasonLeagues; } set { _SeasonLeagues.Assign( value ); } }

	[Description( "Квесты для талантов" )]
	public DBPtr<DynamicQuestForTalents> DynamicQuestForTalents { get { return _DynamicQuestForTalents.Get(); } set { _DynamicQuestForTalents.Set( value ); } }

	public DBPtr<TalentsCollectionSettings> talentsCollectionSettings { get { return _talentsCollectionSettings.Get(); } set { _talentsCollectionSettings.Set( value ); } }

	[Description( "Валюты событий" )]
	public DBPtr<CurrencyDescriptionList> currencies { get { return _currencies.Get(); } set { _currencies.Set( value ); } }

	[Description( "Список лутбоксов замка" )]
	public libdb.IChangeableList<DBPtr<Lootbox>> Lootboxes { get { return _Lootboxes; } set { _Lootboxes.Assign( value ); } }

	[Description( "Список сущностей апгрейда талантов замка" )]
	public libdb.IChangeableList<DBPtr<TalentUpgradeEntity>> TalentUpgradeEntities { get { return _TalentUpgradeEntities; } set { _TalentUpgradeEntities.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SocialRoot>(owner);
		_CommonConstructionsSettings = new UndoRedoDBPtr<CommonConstructionsSettings>( owner );
		_Constructions = new UndoRedoAssignableList<DBPtr<Constructon>>( owner );
		_Heroes = new UndoRedoDBPtr<HeroesDB>( owner );
		_Talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_LevelToFameTable = new UndoRedoDBPtr<DBLevelToFame>( owner );
		_LevelToResources = new LevelToResources( owner );
		_StatpointsToLevelTable = new UndoRedoDBPtr<DBStatpointsToLevel>( owner );
		_LevelToExperienceTable = new UndoRedoDBPtr<DBLevelToExperience>( owner );
		_HeroRatingToFameLevel = new UndoRedoDBPtr<DBRatingToFame>( owner );
		_HonorLevelTable = new HonorLevelTable( owner );
		_StatsBudgetContainer = new UndoRedoDBPtr<StatsBudgetContainer>( owner );
		_UIRoot = new UndoRedoDBPtr<UIRoot>( owner );
		_DBUIData = new UndoRedoDBPtr<DBUIData>( owner );
		_SessionRollSettings = new UndoRedoDBPtr<RollSettings>( owner );
		_HeroClassesTable = new UndoRedoDBPtr<HeroClassInfoTable>( owner );
		_ErrorsTextsTable = new UndoRedoDBPtr<ErrorMessagesTable>( owner );
		_AIGameLogic = new UndoRedoDBPtr<AILogicParameters>( owner );
		_UnitLogicParameters = new UndoRedoDBPtr<UnitsLogicParameters>( owner );
		_Map = new UndoRedoDBPtr<DBMap>( owner );
		_TalentsSellPrice = new UndoRedoAssignableList<ResourcesTable>( owner, typeof( ETalentRarity ) );
		_TalentsUnsoulboundPriceByLevel = new UndoRedoAssignableList<TalentLevelToUnsoulboundPrice>( owner );
		_RaritiesWithoutSoulbound = new UndoRedo<ETalentRarity>( owner, ETalentRarity.Class );
		_ConstructionTabDescs = new UndoRedoAssignableList<ConstructionTabDesc>( owner, typeof( ConstructionTab ) );
		_HeroesTabDescs = new UndoRedoAssignableList<ConstructionTabDesc>( owner, typeof( HeroClassEnum ) );
		_GoldPriceCycleTable = new UndoRedoDBPtr<GoldPriceCycleTable>( owner );
		_GuestInitParams = new UndoRedoDBPtr<MDInitParams>( owner );
		_PlayerInitParams = new UndoRedoDBPtr<MDInitParams>( owner );
		_ResourceAndInventoryLimits = new UndoRedoDBPtr<ResourceAndInventoryLimits>( owner );
		_GuestResourceAndInventoryLimits = new UndoRedoDBPtr<ResourceAndInventoryLimits>( owner );
		_BuildedConstructions = new UndoRedoAssignableList<BuildedConstruction>( owner );
		_RollTalentForTransmutationBuilding = new UndoRedoDBPtr<DBRollTalentPercents>( owner );
		_RollTalentPremiumForTransmutationBuilding = new UndoRedoDBPtr<DBRollTalentPercents>( owner );
		_Quests = new UndoRedoAssignableList<DBPtr<QuestLine>>( owner );
		_SingleQuests = new UndoRedoAssignableList<DBPtr<Quest>>( owner );
		_StartQuest = new UndoRedoDBPtr<Quest>( owner );
		_StartQuestsForFractionChange = new UndoRedoDBPtr<Quest>( owner );
		_ResetStatsPriceCoef = new ResourcesCoefTable( owner );
		_MaxEmptyTalents = new UndoRedo<int>( owner, 0 );
		_SceneObservationCameraFlyCutScene = new UndoRedoDBPtr<CastleCutscene>( owner );
		_DefaultMaps = new UndoRedoAssignableList<DefaultMap>( owner, typeof( MapType ) );
		_GroupMaps = new UndoRedoAssignableList<DBPtr<DBAdvMapDescGroup>>( owner );
		_AviableMaps = new UndoRedoDBPtr<MapList>( owner );
		_FirstBuyHeroExpBonus = new UndoRedo<int>( owner, 0 );
		_MarketingEvents = new MarketingEvents( owner );
		_TalentLevelToPointsAndRarity = new UndoRedoAssignableList<RarityToPointsAndLevel>( owner, typeof( ETalentRarity ) );
		_TalentMergePriceToLevelAndRarity = new UndoRedoAssignableList<RarityToLevelAndPrice>( owner, typeof( ETalentRarity ) );
		_TalentConsumptionPointsToRarity = new UndoRedoList<int>( owner, typeof( ETalentRarity ) );
		_BathPriceToHeroLevel = new UndoRedoAssignableList<BathPriceToHeroLevel>( owner );
		_GuildLevels = new UndoRedoDBPtr<GuildLevels>( owner );
		_LampEventsSettings = new UndoRedoAssignableList<GoldLampRollSettings>( owner );
		_freeSkipsEventBuildings = new FreeSkipsEventBuildings( owner );
		_RandomHeroIcon = new UndoRedoDBPtr<Texture>( owner );
		_Credits = new UndoRedoDBPtr<Credits>( owner );
		_GuildVisibleBonusesCount = new UndoRedoDBPtr<GuildVisibleBonusesCount>( owner );
		_AdditionalTextures = new UndoRedoAssignableList<DBPtr<Texture>>( owner );
		_QuestsThatDontHideScreenBlocker = new UndoRedoAssignableList<DBPtr<Quest>>( owner );
		_ReforgeTalentPrices = new UndoRedoAssignableList<ReforgeTalentPrice>( owner );
		_UITexts = new UndoRedoAssignableList<DBPtr<UITexts>>( owner );
		_RatingDecreaseByTime = new UndoRedoDBPtr<RatingDecreaseByTime>( owner );
		_GuildShopLevelToSuzerenExperience = new UndoRedoAssignableList<GuildSuzerenLevel>( owner );
		_GuildShopItems = new UndoRedoAssignableList<DBPtr<GuildShopItem>>( owner );
		_GuildBuffsCollection = new UndoRedoDBPtr<GuildBuffsCollection>( owner );
		_GuildRatingRanges = new UndoRedoList<int>( owner );
		_ClanWarsData = new ClanWarsData( owner );
		_GuildRecruitment = new GuildRecruitment( owner );
		_resourcesToGoldPrice = new ContextBuyResourceTabel( owner );
		_RerollShop = new RerollShopSettings( owner );
		_Seasons = new UndoRedoAssignableList<SeasonSettings>( owner );
		_SeasonLeagues = new UndoRedoAssignableList<SeasonLeagueSettings>( owner );
		_DynamicQuestForTalents = new UndoRedoDBPtr<DynamicQuestForTalents>( owner );
		_talentsCollectionSettings = new UndoRedoDBPtr<TalentsCollectionSettings>( owner );
		_currencies = new UndoRedoDBPtr<CurrencyDescriptionList>( owner );
		_Lootboxes = new UndoRedoAssignableList<DBPtr<Lootbox>>( owner );
		_TalentUpgradeEntities = new UndoRedoAssignableList<DBPtr<TalentUpgradeEntity>>( owner );
		___parent.Changed += FireChangedEvent;
		_CommonConstructionsSettings.Changed += FireChangedEvent;
		_Constructions.Changed += FireChangedEvent;
		_Heroes.Changed += FireChangedEvent;
		_Talents.Changed += FireChangedEvent;
		_LevelToFameTable.Changed += FireChangedEvent;
		_LevelToResources.Changed += FireChangedEvent;
		_StatpointsToLevelTable.Changed += FireChangedEvent;
		_LevelToExperienceTable.Changed += FireChangedEvent;
		_HeroRatingToFameLevel.Changed += FireChangedEvent;
		_HonorLevelTable.Changed += FireChangedEvent;
		_StatsBudgetContainer.Changed += FireChangedEvent;
		_UIRoot.Changed += FireChangedEvent;
		_DBUIData.Changed += FireChangedEvent;
		_SessionRollSettings.Changed += FireChangedEvent;
		_HeroClassesTable.Changed += FireChangedEvent;
		_ErrorsTextsTable.Changed += FireChangedEvent;
		_AIGameLogic.Changed += FireChangedEvent;
		_UnitLogicParameters.Changed += FireChangedEvent;
		_Map.Changed += FireChangedEvent;
		_TalentsSellPrice.Changed += FireChangedEvent;
		_TalentsUnsoulboundPriceByLevel.Changed += FireChangedEvent;
		_RaritiesWithoutSoulbound.Changed += FireChangedEvent;
		_ConstructionTabDescs.Changed += FireChangedEvent;
		_HeroesTabDescs.Changed += FireChangedEvent;
		_GoldPriceCycleTable.Changed += FireChangedEvent;
		_GuestInitParams.Changed += FireChangedEvent;
		_PlayerInitParams.Changed += FireChangedEvent;
		_ResourceAndInventoryLimits.Changed += FireChangedEvent;
		_GuestResourceAndInventoryLimits.Changed += FireChangedEvent;
		_BuildedConstructions.Changed += FireChangedEvent;
		_RollTalentForTransmutationBuilding.Changed += FireChangedEvent;
		_RollTalentPremiumForTransmutationBuilding.Changed += FireChangedEvent;
		_Quests.Changed += FireChangedEvent;
		_SingleQuests.Changed += FireChangedEvent;
		_StartQuest.Changed += FireChangedEvent;
		_StartQuestsForFractionChange.Changed += FireChangedEvent;
		_ResetStatsPriceCoef.Changed += FireChangedEvent;
		_MaxEmptyTalents.Changed += FireChangedEvent;
		_SceneObservationCameraFlyCutScene.Changed += FireChangedEvent;
		_DefaultMaps.Changed += FireChangedEvent;
		_GroupMaps.Changed += FireChangedEvent;
		_AviableMaps.Changed += FireChangedEvent;
		_FirstBuyHeroExpBonus.Changed += FireChangedEvent;
		_MarketingEvents.Changed += FireChangedEvent;
		_TalentLevelToPointsAndRarity.Changed += FireChangedEvent;
		_TalentMergePriceToLevelAndRarity.Changed += FireChangedEvent;
		_TalentConsumptionPointsToRarity.Changed += FireChangedEvent;
		_BathPriceToHeroLevel.Changed += FireChangedEvent;
		_GuildLevels.Changed += FireChangedEvent;
		_LampEventsSettings.Changed += FireChangedEvent;
		_freeSkipsEventBuildings.Changed += FireChangedEvent;
		_RandomHeroIcon.Changed += FireChangedEvent;
		_Credits.Changed += FireChangedEvent;
		_GuildVisibleBonusesCount.Changed += FireChangedEvent;
		_AdditionalTextures.Changed += FireChangedEvent;
		_QuestsThatDontHideScreenBlocker.Changed += FireChangedEvent;
		_ReforgeTalentPrices.Changed += FireChangedEvent;
		_UITexts.Changed += FireChangedEvent;
		_RatingDecreaseByTime.Changed += FireChangedEvent;
		_GuildShopLevelToSuzerenExperience.Changed += FireChangedEvent;
		_GuildShopItems.Changed += FireChangedEvent;
		_GuildBuffsCollection.Changed += FireChangedEvent;
		_GuildRatingRanges.Changed += FireChangedEvent;
		_ClanWarsData.Changed += FireChangedEvent;
		_GuildRecruitment.Changed += FireChangedEvent;
		_resourcesToGoldPrice.Changed += FireChangedEvent;
		_RerollShop.Changed += FireChangedEvent;
		_Seasons.Changed += FireChangedEvent;
		_SeasonLeagues.Changed += FireChangedEvent;
		_DynamicQuestForTalents.Changed += FireChangedEvent;
		_talentsCollectionSettings.Changed += FireChangedEvent;
		_currencies.Changed += FireChangedEvent;
		_Lootboxes.Changed += FireChangedEvent;
		_TalentUpgradeEntities.Changed += FireChangedEvent;
	}

	public SocialRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SocialRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SocialRoot" );
		CommonConstructionsSettings = source.CommonConstructionsSettings;
		Constructions = source.Constructions;
		Heroes = source.Heroes;
		Talents = source.Talents;
		LevelToFameTable = source.LevelToFameTable;
		LevelToResources = source.LevelToResources;
		StatpointsToLevelTable = source.StatpointsToLevelTable;
		LevelToExperienceTable = source.LevelToExperienceTable;
		HeroRatingToFameLevel = source.HeroRatingToFameLevel;
		HonorLevelTable = source.HonorLevelTable;
		StatsBudgetContainer = source.StatsBudgetContainer;
		UIRoot = source.UIRoot;
		DBUIData = source.DBUIData;
		SessionRollSettings = source.SessionRollSettings;
		HeroClassesTable = source.HeroClassesTable;
		ErrorsTextsTable = source.ErrorsTextsTable;
		AIGameLogic = source.AIGameLogic;
		UnitLogicParameters = source.UnitLogicParameters;
		Map = source.Map;
		TalentsSellPrice = source.TalentsSellPrice;
		TalentsUnsoulboundPriceByLevel = source.TalentsUnsoulboundPriceByLevel;
		RaritiesWithoutSoulbound = source.RaritiesWithoutSoulbound;
		ConstructionTabDescs = source.ConstructionTabDescs;
		HeroesTabDescs = source.HeroesTabDescs;
		GoldPriceCycleTable = source.GoldPriceCycleTable;
		GuestInitParams = source.GuestInitParams;
		PlayerInitParams = source.PlayerInitParams;
		ResourceAndInventoryLimits = source.ResourceAndInventoryLimits;
		GuestResourceAndInventoryLimits = source.GuestResourceAndInventoryLimits;
		BuildedConstructions = source.BuildedConstructions;
		RollTalentForTransmutationBuilding = source.RollTalentForTransmutationBuilding;
		RollTalentPremiumForTransmutationBuilding = source.RollTalentPremiumForTransmutationBuilding;
		Quests = source.Quests;
		SingleQuests = source.SingleQuests;
		StartQuest = source.StartQuest;
		StartQuestsForFractionChange = source.StartQuestsForFractionChange;
		ResetStatsPriceCoef = source.ResetStatsPriceCoef;
		MaxEmptyTalents = source.MaxEmptyTalents;
		SceneObservationCameraFlyCutScene = source.SceneObservationCameraFlyCutScene;
		DefaultMaps = source.DefaultMaps;
		GroupMaps = source.GroupMaps;
		AviableMaps = source.AviableMaps;
		FirstBuyHeroExpBonus = source.FirstBuyHeroExpBonus;
		MarketingEvents = source.MarketingEvents;
		TalentLevelToPointsAndRarity = source.TalentLevelToPointsAndRarity;
		TalentMergePriceToLevelAndRarity = source.TalentMergePriceToLevelAndRarity;
		TalentConsumptionPointsToRarity = source.TalentConsumptionPointsToRarity;
		BathPriceToHeroLevel = source.BathPriceToHeroLevel;
		GuildLevels = source.GuildLevels;
		LampEventsSettings = source.LampEventsSettings;
		freeSkipsEventBuildings = source.freeSkipsEventBuildings;
		RandomHeroIcon = source.RandomHeroIcon;
		Credits = source.Credits;
		GuildVisibleBonusesCount = source.GuildVisibleBonusesCount;
		AdditionalTextures = source.AdditionalTextures;
		QuestsThatDontHideScreenBlocker = source.QuestsThatDontHideScreenBlocker;
		ReforgeTalentPrices = source.ReforgeTalentPrices;
		UITexts = source.UITexts;
		RatingDecreaseByTime = source.RatingDecreaseByTime;
		GuildShopLevelToSuzerenExperience = source.GuildShopLevelToSuzerenExperience;
		GuildShopItems = source.GuildShopItems;
		GuildBuffsCollection = source.GuildBuffsCollection;
		GuildRatingRanges = source.GuildRatingRanges;
		ClanWarsData = source.ClanWarsData;
		GuildRecruitment = source.GuildRecruitment;
		resourcesToGoldPrice = source.resourcesToGoldPrice;
		RerollShop = source.RerollShop;
		Seasons = source.Seasons;
		SeasonLeagues = source.SeasonLeagues;
		DynamicQuestForTalents = source.DynamicQuestForTalents;
		talentsCollectionSettings = source.talentsCollectionSettings;
		currencies = source.currencies;
		Lootboxes = source.Lootboxes;
		TalentUpgradeEntities = source.TalentUpgradeEntities;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SocialRoot source = _source as SocialRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SocialRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SocialRoot newParent = rawParent == null ? null : rawParent.Get<SocialRoot>();
		if ( newParent == null && _newParent is SocialRoot )
			newParent = _newParent as SocialRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_CommonConstructionsSettings.SetParent( newParent == null ? null : newParent._CommonConstructionsSettings );
		_Constructions.SetParent( newParent == null ? null : newParent._Constructions );
		_Heroes.SetParent( newParent == null ? null : newParent._Heroes );
		_Talents.SetParent( newParent == null ? null : newParent._Talents );
		_LevelToFameTable.SetParent( newParent == null ? null : newParent._LevelToFameTable );
		_LevelToResources.SetParent( newParent == null ? null : newParent._LevelToResources );
		_StatpointsToLevelTable.SetParent( newParent == null ? null : newParent._StatpointsToLevelTable );
		_LevelToExperienceTable.SetParent( newParent == null ? null : newParent._LevelToExperienceTable );
		_HeroRatingToFameLevel.SetParent( newParent == null ? null : newParent._HeroRatingToFameLevel );
		_HonorLevelTable.SetParent( newParent == null ? null : newParent._HonorLevelTable );
		_StatsBudgetContainer.SetParent( newParent == null ? null : newParent._StatsBudgetContainer );
		_UIRoot.SetParent( newParent == null ? null : newParent._UIRoot );
		_DBUIData.SetParent( newParent == null ? null : newParent._DBUIData );
		_SessionRollSettings.SetParent( newParent == null ? null : newParent._SessionRollSettings );
		_HeroClassesTable.SetParent( newParent == null ? null : newParent._HeroClassesTable );
		_ErrorsTextsTable.SetParent( newParent == null ? null : newParent._ErrorsTextsTable );
		_AIGameLogic.SetParent( newParent == null ? null : newParent._AIGameLogic );
		_UnitLogicParameters.SetParent( newParent == null ? null : newParent._UnitLogicParameters );
		_Map.SetParent( newParent == null ? null : newParent._Map );
		_TalentsSellPrice.SetParent( newParent == null ? null : newParent._TalentsSellPrice );
		_TalentsUnsoulboundPriceByLevel.SetParent( newParent == null ? null : newParent._TalentsUnsoulboundPriceByLevel );
		_RaritiesWithoutSoulbound.SetParent( newParent == null ? null : newParent._RaritiesWithoutSoulbound );
		_ConstructionTabDescs.SetParent( newParent == null ? null : newParent._ConstructionTabDescs );
		_HeroesTabDescs.SetParent( newParent == null ? null : newParent._HeroesTabDescs );
		_GoldPriceCycleTable.SetParent( newParent == null ? null : newParent._GoldPriceCycleTable );
		_GuestInitParams.SetParent( newParent == null ? null : newParent._GuestInitParams );
		_PlayerInitParams.SetParent( newParent == null ? null : newParent._PlayerInitParams );
		_ResourceAndInventoryLimits.SetParent( newParent == null ? null : newParent._ResourceAndInventoryLimits );
		_GuestResourceAndInventoryLimits.SetParent( newParent == null ? null : newParent._GuestResourceAndInventoryLimits );
		_BuildedConstructions.SetParent( newParent == null ? null : newParent._BuildedConstructions );
		_RollTalentForTransmutationBuilding.SetParent( newParent == null ? null : newParent._RollTalentForTransmutationBuilding );
		_RollTalentPremiumForTransmutationBuilding.SetParent( newParent == null ? null : newParent._RollTalentPremiumForTransmutationBuilding );
		_Quests.SetParent( newParent == null ? null : newParent._Quests );
		_SingleQuests.SetParent( newParent == null ? null : newParent._SingleQuests );
		_StartQuest.SetParent( newParent == null ? null : newParent._StartQuest );
		_StartQuestsForFractionChange.SetParent( newParent == null ? null : newParent._StartQuestsForFractionChange );
		_ResetStatsPriceCoef.SetParent( newParent == null ? null : newParent._ResetStatsPriceCoef );
		_MaxEmptyTalents.SetParent( newParent == null ? null : newParent._MaxEmptyTalents );
		_SceneObservationCameraFlyCutScene.SetParent( newParent == null ? null : newParent._SceneObservationCameraFlyCutScene );
		_DefaultMaps.SetParent( newParent == null ? null : newParent._DefaultMaps );
		_GroupMaps.SetParent( newParent == null ? null : newParent._GroupMaps );
		_AviableMaps.SetParent( newParent == null ? null : newParent._AviableMaps );
		_FirstBuyHeroExpBonus.SetParent( newParent == null ? null : newParent._FirstBuyHeroExpBonus );
		_MarketingEvents.SetParent( newParent == null ? null : newParent._MarketingEvents );
		_TalentLevelToPointsAndRarity.SetParent( newParent == null ? null : newParent._TalentLevelToPointsAndRarity );
		_TalentMergePriceToLevelAndRarity.SetParent( newParent == null ? null : newParent._TalentMergePriceToLevelAndRarity );
		_TalentConsumptionPointsToRarity.SetParent( newParent == null ? null : newParent._TalentConsumptionPointsToRarity );
		_BathPriceToHeroLevel.SetParent( newParent == null ? null : newParent._BathPriceToHeroLevel );
		_GuildLevels.SetParent( newParent == null ? null : newParent._GuildLevels );
		_LampEventsSettings.SetParent( newParent == null ? null : newParent._LampEventsSettings );
		_freeSkipsEventBuildings.SetParent( newParent == null ? null : newParent._freeSkipsEventBuildings );
		_RandomHeroIcon.SetParent( newParent == null ? null : newParent._RandomHeroIcon );
		_Credits.SetParent( newParent == null ? null : newParent._Credits );
		_GuildVisibleBonusesCount.SetParent( newParent == null ? null : newParent._GuildVisibleBonusesCount );
		_AdditionalTextures.SetParent( newParent == null ? null : newParent._AdditionalTextures );
		_QuestsThatDontHideScreenBlocker.SetParent( newParent == null ? null : newParent._QuestsThatDontHideScreenBlocker );
		_ReforgeTalentPrices.SetParent( newParent == null ? null : newParent._ReforgeTalentPrices );
		_UITexts.SetParent( newParent == null ? null : newParent._UITexts );
		_RatingDecreaseByTime.SetParent( newParent == null ? null : newParent._RatingDecreaseByTime );
		_GuildShopLevelToSuzerenExperience.SetParent( newParent == null ? null : newParent._GuildShopLevelToSuzerenExperience );
		_GuildShopItems.SetParent( newParent == null ? null : newParent._GuildShopItems );
		_GuildBuffsCollection.SetParent( newParent == null ? null : newParent._GuildBuffsCollection );
		_GuildRatingRanges.SetParent( newParent == null ? null : newParent._GuildRatingRanges );
		_ClanWarsData.SetParent( newParent == null ? null : newParent._ClanWarsData );
		_GuildRecruitment.SetParent( newParent == null ? null : newParent._GuildRecruitment );
		_resourcesToGoldPrice.SetParent( newParent == null ? null : newParent._resourcesToGoldPrice );
		_RerollShop.SetParent( newParent == null ? null : newParent._RerollShop );
		_Seasons.SetParent( newParent == null ? null : newParent._Seasons );
		_SeasonLeagues.SetParent( newParent == null ? null : newParent._SeasonLeagues );
		_DynamicQuestForTalents.SetParent( newParent == null ? null : newParent._DynamicQuestForTalents );
		_talentsCollectionSettings.SetParent( newParent == null ? null : newParent._talentsCollectionSettings );
		_currencies.SetParent( newParent == null ? null : newParent._currencies );
		_Lootboxes.SetParent( newParent == null ? null : newParent._Lootboxes );
		_TalentUpgradeEntities.SetParent( newParent == null ? null : newParent._TalentUpgradeEntities );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_CommonConstructionsSettings.Reset();
		_Constructions.Reset();
		_Heroes.Reset();
		_Talents.Reset();
		_LevelToFameTable.Reset();
		_LevelToResources.Reset();
		_StatpointsToLevelTable.Reset();
		_LevelToExperienceTable.Reset();
		_HeroRatingToFameLevel.Reset();
		_HonorLevelTable.Reset();
		_StatsBudgetContainer.Reset();
		_UIRoot.Reset();
		_DBUIData.Reset();
		_SessionRollSettings.Reset();
		_HeroClassesTable.Reset();
		_ErrorsTextsTable.Reset();
		_AIGameLogic.Reset();
		_UnitLogicParameters.Reset();
		_Map.Reset();
		_TalentsSellPrice.Reset();
		_TalentsUnsoulboundPriceByLevel.Reset();
		_RaritiesWithoutSoulbound.Reset();
		_ConstructionTabDescs.Reset();
		_HeroesTabDescs.Reset();
		_GoldPriceCycleTable.Reset();
		_GuestInitParams.Reset();
		_PlayerInitParams.Reset();
		_ResourceAndInventoryLimits.Reset();
		_GuestResourceAndInventoryLimits.Reset();
		_BuildedConstructions.Reset();
		_RollTalentForTransmutationBuilding.Reset();
		_RollTalentPremiumForTransmutationBuilding.Reset();
		_Quests.Reset();
		_SingleQuests.Reset();
		_StartQuest.Reset();
		_StartQuestsForFractionChange.Reset();
		_ResetStatsPriceCoef.Reset();
		_MaxEmptyTalents.Reset();
		_SceneObservationCameraFlyCutScene.Reset();
		_DefaultMaps.Reset();
		_GroupMaps.Reset();
		_AviableMaps.Reset();
		_FirstBuyHeroExpBonus.Reset();
		_MarketingEvents.Reset();
		_TalentLevelToPointsAndRarity.Reset();
		_TalentMergePriceToLevelAndRarity.Reset();
		_TalentConsumptionPointsToRarity.Reset();
		_BathPriceToHeroLevel.Reset();
		_GuildLevels.Reset();
		_LampEventsSettings.Reset();
		_freeSkipsEventBuildings.Reset();
		_RandomHeroIcon.Reset();
		_Credits.Reset();
		_GuildVisibleBonusesCount.Reset();
		_AdditionalTextures.Reset();
		_QuestsThatDontHideScreenBlocker.Reset();
		_ReforgeTalentPrices.Reset();
		_UITexts.Reset();
		_RatingDecreaseByTime.Reset();
		_GuildShopLevelToSuzerenExperience.Reset();
		_GuildShopItems.Reset();
		_GuildBuffsCollection.Reset();
		_GuildRatingRanges.Reset();
		_ClanWarsData.Reset();
		_GuildRecruitment.Reset();
		_resourcesToGoldPrice.Reset();
		_RerollShop.Reset();
		_Seasons.Reset();
		_SeasonLeagues.Reset();
		_DynamicQuestForTalents.Reset();
		_talentsCollectionSettings.Reset();
		_currencies.Reset();
		_Lootboxes.Reset();
		_TalentUpgradeEntities.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_CommonConstructionsSettings.IsDerivedFromParent()
			&& _Constructions.IsDerivedFromParent()
			&& _Heroes.IsDerivedFromParent()
			&& _Talents.IsDerivedFromParent()
			&& _LevelToFameTable.IsDerivedFromParent()
			&& _LevelToResources.IsDerivedFromParent()
			&& _StatpointsToLevelTable.IsDerivedFromParent()
			&& _LevelToExperienceTable.IsDerivedFromParent()
			&& _HeroRatingToFameLevel.IsDerivedFromParent()
			&& _HonorLevelTable.IsDerivedFromParent()
			&& _StatsBudgetContainer.IsDerivedFromParent()
			&& _UIRoot.IsDerivedFromParent()
			&& _DBUIData.IsDerivedFromParent()
			&& _SessionRollSettings.IsDerivedFromParent()
			&& _HeroClassesTable.IsDerivedFromParent()
			&& _ErrorsTextsTable.IsDerivedFromParent()
			&& _AIGameLogic.IsDerivedFromParent()
			&& _UnitLogicParameters.IsDerivedFromParent()
			&& _Map.IsDerivedFromParent()
			&& _TalentsSellPrice.IsDerivedFromParent()
			&& _TalentsUnsoulboundPriceByLevel.IsDerivedFromParent()
			&& _RaritiesWithoutSoulbound.IsDerivedFromParent()
			&& _ConstructionTabDescs.IsDerivedFromParent()
			&& _HeroesTabDescs.IsDerivedFromParent()
			&& _GoldPriceCycleTable.IsDerivedFromParent()
			&& _GuestInitParams.IsDerivedFromParent()
			&& _PlayerInitParams.IsDerivedFromParent()
			&& _ResourceAndInventoryLimits.IsDerivedFromParent()
			&& _GuestResourceAndInventoryLimits.IsDerivedFromParent()
			&& _BuildedConstructions.IsDerivedFromParent()
			&& _RollTalentForTransmutationBuilding.IsDerivedFromParent()
			&& _RollTalentPremiumForTransmutationBuilding.IsDerivedFromParent()
			&& _Quests.IsDerivedFromParent()
			&& _SingleQuests.IsDerivedFromParent()
			&& _StartQuest.IsDerivedFromParent()
			&& _StartQuestsForFractionChange.IsDerivedFromParent()
			&& _ResetStatsPriceCoef.IsDerivedFromParent()
			&& _MaxEmptyTalents.IsDerivedFromParent()
			&& _SceneObservationCameraFlyCutScene.IsDerivedFromParent()
			&& _DefaultMaps.IsDerivedFromParent()
			&& _GroupMaps.IsDerivedFromParent()
			&& _AviableMaps.IsDerivedFromParent()
			&& _FirstBuyHeroExpBonus.IsDerivedFromParent()
			&& _MarketingEvents.IsDerivedFromParent()
			&& _TalentLevelToPointsAndRarity.IsDerivedFromParent()
			&& _TalentMergePriceToLevelAndRarity.IsDerivedFromParent()
			&& _TalentConsumptionPointsToRarity.IsDerivedFromParent()
			&& _BathPriceToHeroLevel.IsDerivedFromParent()
			&& _GuildLevels.IsDerivedFromParent()
			&& _LampEventsSettings.IsDerivedFromParent()
			&& _freeSkipsEventBuildings.IsDerivedFromParent()
			&& _RandomHeroIcon.IsDerivedFromParent()
			&& _Credits.IsDerivedFromParent()
			&& _GuildVisibleBonusesCount.IsDerivedFromParent()
			&& _AdditionalTextures.IsDerivedFromParent()
			&& _QuestsThatDontHideScreenBlocker.IsDerivedFromParent()
			&& _ReforgeTalentPrices.IsDerivedFromParent()
			&& _UITexts.IsDerivedFromParent()
			&& _RatingDecreaseByTime.IsDerivedFromParent()
			&& _GuildShopLevelToSuzerenExperience.IsDerivedFromParent()
			&& _GuildShopItems.IsDerivedFromParent()
			&& _GuildBuffsCollection.IsDerivedFromParent()
			&& _GuildRatingRanges.IsDerivedFromParent()
			&& _ClanWarsData.IsDerivedFromParent()
			&& _GuildRecruitment.IsDerivedFromParent()
			&& _resourcesToGoldPrice.IsDerivedFromParent()
			&& _RerollShop.IsDerivedFromParent()
			&& _Seasons.IsDerivedFromParent()
			&& _SeasonLeagues.IsDerivedFromParent()
			&& _DynamicQuestForTalents.IsDerivedFromParent()
			&& _talentsCollectionSettings.IsDerivedFromParent()
			&& _currencies.IsDerivedFromParent()
			&& _Lootboxes.IsDerivedFromParent()
			&& _TalentUpgradeEntities.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "CommonConstructionsSettings" )
			_CommonConstructionsSettings.Reset();
		else if ( fieldName == "Constructions" )
			_Constructions.Reset();
		else if ( fieldName == "Heroes" )
			_Heroes.Reset();
		else if ( fieldName == "Talents" )
			_Talents.Reset();
		else if ( fieldName == "LevelToFameTable" )
			_LevelToFameTable.Reset();
		else if ( fieldName == "LevelToResources" )
			_LevelToResources.Reset();
		else if ( fieldName == "StatpointsToLevelTable" )
			_StatpointsToLevelTable.Reset();
		else if ( fieldName == "LevelToExperienceTable" )
			_LevelToExperienceTable.Reset();
		else if ( fieldName == "HeroRatingToFameLevel" )
			_HeroRatingToFameLevel.Reset();
		else if ( fieldName == "HonorLevelTable" )
			_HonorLevelTable.Reset();
		else if ( fieldName == "StatsBudgetContainer" )
			_StatsBudgetContainer.Reset();
		else if ( fieldName == "UIRoot" )
			_UIRoot.Reset();
		else if ( fieldName == "DBUIData" )
			_DBUIData.Reset();
		else if ( fieldName == "SessionRollSettings" )
			_SessionRollSettings.Reset();
		else if ( fieldName == "HeroClassesTable" )
			_HeroClassesTable.Reset();
		else if ( fieldName == "ErrorsTextsTable" )
			_ErrorsTextsTable.Reset();
		else if ( fieldName == "AIGameLogic" )
			_AIGameLogic.Reset();
		else if ( fieldName == "UnitLogicParameters" )
			_UnitLogicParameters.Reset();
		else if ( fieldName == "Map" )
			_Map.Reset();
		else if ( fieldName == "TalentsSellPrice" )
			_TalentsSellPrice.Reset();
		else if ( fieldName == "TalentsUnsoulboundPriceByLevel" )
			_TalentsUnsoulboundPriceByLevel.Reset();
		else if ( fieldName == "RaritiesWithoutSoulbound" )
			_RaritiesWithoutSoulbound.Reset();
		else if ( fieldName == "ConstructionTabDescs" )
			_ConstructionTabDescs.Reset();
		else if ( fieldName == "HeroesTabDescs" )
			_HeroesTabDescs.Reset();
		else if ( fieldName == "GoldPriceCycleTable" )
			_GoldPriceCycleTable.Reset();
		else if ( fieldName == "GuestInitParams" )
			_GuestInitParams.Reset();
		else if ( fieldName == "PlayerInitParams" )
			_PlayerInitParams.Reset();
		else if ( fieldName == "ResourceAndInventoryLimits" )
			_ResourceAndInventoryLimits.Reset();
		else if ( fieldName == "GuestResourceAndInventoryLimits" )
			_GuestResourceAndInventoryLimits.Reset();
		else if ( fieldName == "BuildedConstructions" )
			_BuildedConstructions.Reset();
		else if ( fieldName == "RollTalentForTransmutationBuilding" )
			_RollTalentForTransmutationBuilding.Reset();
		else if ( fieldName == "RollTalentPremiumForTransmutationBuilding" )
			_RollTalentPremiumForTransmutationBuilding.Reset();
		else if ( fieldName == "Quests" )
			_Quests.Reset();
		else if ( fieldName == "SingleQuests" )
			_SingleQuests.Reset();
		else if ( fieldName == "StartQuest" )
			_StartQuest.Reset();
		else if ( fieldName == "StartQuestsForFractionChange" )
			_StartQuestsForFractionChange.Reset();
		else if ( fieldName == "ResetStatsPriceCoef" )
			_ResetStatsPriceCoef.Reset();
		else if ( fieldName == "MaxEmptyTalents" )
			_MaxEmptyTalents.Reset();
		else if ( fieldName == "SceneObservationCameraFlyCutScene" )
			_SceneObservationCameraFlyCutScene.Reset();
		else if ( fieldName == "DefaultMaps" )
			_DefaultMaps.Reset();
		else if ( fieldName == "GroupMaps" )
			_GroupMaps.Reset();
		else if ( fieldName == "AviableMaps" )
			_AviableMaps.Reset();
		else if ( fieldName == "FirstBuyHeroExpBonus" )
			_FirstBuyHeroExpBonus.Reset();
		else if ( fieldName == "MarketingEvents" )
			_MarketingEvents.Reset();
		else if ( fieldName == "TalentLevelToPointsAndRarity" )
			_TalentLevelToPointsAndRarity.Reset();
		else if ( fieldName == "TalentMergePriceToLevelAndRarity" )
			_TalentMergePriceToLevelAndRarity.Reset();
		else if ( fieldName == "TalentConsumptionPointsToRarity" )
			_TalentConsumptionPointsToRarity.Reset();
		else if ( fieldName == "BathPriceToHeroLevel" )
			_BathPriceToHeroLevel.Reset();
		else if ( fieldName == "GuildLevels" )
			_GuildLevels.Reset();
		else if ( fieldName == "LampEventsSettings" )
			_LampEventsSettings.Reset();
		else if ( fieldName == "freeSkipsEventBuildings" )
			_freeSkipsEventBuildings.Reset();
		else if ( fieldName == "RandomHeroIcon" )
			_RandomHeroIcon.Reset();
		else if ( fieldName == "Credits" )
			_Credits.Reset();
		else if ( fieldName == "GuildVisibleBonusesCount" )
			_GuildVisibleBonusesCount.Reset();
		else if ( fieldName == "AdditionalTextures" )
			_AdditionalTextures.Reset();
		else if ( fieldName == "QuestsThatDontHideScreenBlocker" )
			_QuestsThatDontHideScreenBlocker.Reset();
		else if ( fieldName == "ReforgeTalentPrices" )
			_ReforgeTalentPrices.Reset();
		else if ( fieldName == "UITexts" )
			_UITexts.Reset();
		else if ( fieldName == "RatingDecreaseByTime" )
			_RatingDecreaseByTime.Reset();
		else if ( fieldName == "GuildShopLevelToSuzerenExperience" )
			_GuildShopLevelToSuzerenExperience.Reset();
		else if ( fieldName == "GuildShopItems" )
			_GuildShopItems.Reset();
		else if ( fieldName == "GuildBuffsCollection" )
			_GuildBuffsCollection.Reset();
		else if ( fieldName == "GuildRatingRanges" )
			_GuildRatingRanges.Reset();
		else if ( fieldName == "ClanWarsData" )
			_ClanWarsData.Reset();
		else if ( fieldName == "GuildRecruitment" )
			_GuildRecruitment.Reset();
		else if ( fieldName == "resourcesToGoldPrice" )
			_resourcesToGoldPrice.Reset();
		else if ( fieldName == "RerollShop" )
			_RerollShop.Reset();
		else if ( fieldName == "Seasons" )
			_Seasons.Reset();
		else if ( fieldName == "SeasonLeagues" )
			_SeasonLeagues.Reset();
		else if ( fieldName == "DynamicQuestForTalents" )
			_DynamicQuestForTalents.Reset();
		else if ( fieldName == "talentsCollectionSettings" )
			_talentsCollectionSettings.Reset();
		else if ( fieldName == "currencies" )
			_currencies.Reset();
		else if ( fieldName == "Lootboxes" )
			_Lootboxes.Reset();
		else if ( fieldName == "TalentUpgradeEntities" )
			_TalentUpgradeEntities.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "CommonConstructionsSettings" )
			return _CommonConstructionsSettings.IsDerivedFromParent();
		if ( fieldName == "Constructions" )
			return _Constructions.IsDerivedFromParent();
		if ( fieldName == "Heroes" )
			return _Heroes.IsDerivedFromParent();
		if ( fieldName == "Talents" )
			return _Talents.IsDerivedFromParent();
		if ( fieldName == "LevelToFameTable" )
			return _LevelToFameTable.IsDerivedFromParent();
		if ( fieldName == "LevelToResources" )
			return _LevelToResources.IsDerivedFromParent();
		if ( fieldName == "StatpointsToLevelTable" )
			return _StatpointsToLevelTable.IsDerivedFromParent();
		if ( fieldName == "LevelToExperienceTable" )
			return _LevelToExperienceTable.IsDerivedFromParent();
		if ( fieldName == "HeroRatingToFameLevel" )
			return _HeroRatingToFameLevel.IsDerivedFromParent();
		if ( fieldName == "HonorLevelTable" )
			return _HonorLevelTable.IsDerivedFromParent();
		if ( fieldName == "StatsBudgetContainer" )
			return _StatsBudgetContainer.IsDerivedFromParent();
		if ( fieldName == "UIRoot" )
			return _UIRoot.IsDerivedFromParent();
		if ( fieldName == "DBUIData" )
			return _DBUIData.IsDerivedFromParent();
		if ( fieldName == "SessionRollSettings" )
			return _SessionRollSettings.IsDerivedFromParent();
		if ( fieldName == "HeroClassesTable" )
			return _HeroClassesTable.IsDerivedFromParent();
		if ( fieldName == "ErrorsTextsTable" )
			return _ErrorsTextsTable.IsDerivedFromParent();
		if ( fieldName == "AIGameLogic" )
			return _AIGameLogic.IsDerivedFromParent();
		if ( fieldName == "UnitLogicParameters" )
			return _UnitLogicParameters.IsDerivedFromParent();
		if ( fieldName == "Map" )
			return _Map.IsDerivedFromParent();
		if ( fieldName == "TalentsSellPrice" )
			return _TalentsSellPrice.IsDerivedFromParent();
		if ( fieldName == "TalentsUnsoulboundPriceByLevel" )
			return _TalentsUnsoulboundPriceByLevel.IsDerivedFromParent();
		if ( fieldName == "RaritiesWithoutSoulbound" )
			return _RaritiesWithoutSoulbound.IsDerivedFromParent();
		if ( fieldName == "ConstructionTabDescs" )
			return _ConstructionTabDescs.IsDerivedFromParent();
		if ( fieldName == "HeroesTabDescs" )
			return _HeroesTabDescs.IsDerivedFromParent();
		if ( fieldName == "GoldPriceCycleTable" )
			return _GoldPriceCycleTable.IsDerivedFromParent();
		if ( fieldName == "GuestInitParams" )
			return _GuestInitParams.IsDerivedFromParent();
		if ( fieldName == "PlayerInitParams" )
			return _PlayerInitParams.IsDerivedFromParent();
		if ( fieldName == "ResourceAndInventoryLimits" )
			return _ResourceAndInventoryLimits.IsDerivedFromParent();
		if ( fieldName == "GuestResourceAndInventoryLimits" )
			return _GuestResourceAndInventoryLimits.IsDerivedFromParent();
		if ( fieldName == "BuildedConstructions" )
			return _BuildedConstructions.IsDerivedFromParent();
		if ( fieldName == "RollTalentForTransmutationBuilding" )
			return _RollTalentForTransmutationBuilding.IsDerivedFromParent();
		if ( fieldName == "RollTalentPremiumForTransmutationBuilding" )
			return _RollTalentPremiumForTransmutationBuilding.IsDerivedFromParent();
		if ( fieldName == "Quests" )
			return _Quests.IsDerivedFromParent();
		if ( fieldName == "SingleQuests" )
			return _SingleQuests.IsDerivedFromParent();
		if ( fieldName == "StartQuest" )
			return _StartQuest.IsDerivedFromParent();
		if ( fieldName == "StartQuestsForFractionChange" )
			return _StartQuestsForFractionChange.IsDerivedFromParent();
		if ( fieldName == "ResetStatsPriceCoef" )
			return _ResetStatsPriceCoef.IsDerivedFromParent();
		if ( fieldName == "MaxEmptyTalents" )
			return _MaxEmptyTalents.IsDerivedFromParent();
		if ( fieldName == "SceneObservationCameraFlyCutScene" )
			return _SceneObservationCameraFlyCutScene.IsDerivedFromParent();
		if ( fieldName == "DefaultMaps" )
			return _DefaultMaps.IsDerivedFromParent();
		if ( fieldName == "GroupMaps" )
			return _GroupMaps.IsDerivedFromParent();
		if ( fieldName == "AviableMaps" )
			return _AviableMaps.IsDerivedFromParent();
		if ( fieldName == "FirstBuyHeroExpBonus" )
			return _FirstBuyHeroExpBonus.IsDerivedFromParent();
		if ( fieldName == "MarketingEvents" )
			return _MarketingEvents.IsDerivedFromParent();
		if ( fieldName == "TalentLevelToPointsAndRarity" )
			return _TalentLevelToPointsAndRarity.IsDerivedFromParent();
		if ( fieldName == "TalentMergePriceToLevelAndRarity" )
			return _TalentMergePriceToLevelAndRarity.IsDerivedFromParent();
		if ( fieldName == "TalentConsumptionPointsToRarity" )
			return _TalentConsumptionPointsToRarity.IsDerivedFromParent();
		if ( fieldName == "BathPriceToHeroLevel" )
			return _BathPriceToHeroLevel.IsDerivedFromParent();
		if ( fieldName == "GuildLevels" )
			return _GuildLevels.IsDerivedFromParent();
		if ( fieldName == "LampEventsSettings" )
			return _LampEventsSettings.IsDerivedFromParent();
		if ( fieldName == "freeSkipsEventBuildings" )
			return _freeSkipsEventBuildings.IsDerivedFromParent();
		if ( fieldName == "RandomHeroIcon" )
			return _RandomHeroIcon.IsDerivedFromParent();
		if ( fieldName == "Credits" )
			return _Credits.IsDerivedFromParent();
		if ( fieldName == "GuildVisibleBonusesCount" )
			return _GuildVisibleBonusesCount.IsDerivedFromParent();
		if ( fieldName == "AdditionalTextures" )
			return _AdditionalTextures.IsDerivedFromParent();
		if ( fieldName == "QuestsThatDontHideScreenBlocker" )
			return _QuestsThatDontHideScreenBlocker.IsDerivedFromParent();
		if ( fieldName == "ReforgeTalentPrices" )
			return _ReforgeTalentPrices.IsDerivedFromParent();
		if ( fieldName == "UITexts" )
			return _UITexts.IsDerivedFromParent();
		if ( fieldName == "RatingDecreaseByTime" )
			return _RatingDecreaseByTime.IsDerivedFromParent();
		if ( fieldName == "GuildShopLevelToSuzerenExperience" )
			return _GuildShopLevelToSuzerenExperience.IsDerivedFromParent();
		if ( fieldName == "GuildShopItems" )
			return _GuildShopItems.IsDerivedFromParent();
		if ( fieldName == "GuildBuffsCollection" )
			return _GuildBuffsCollection.IsDerivedFromParent();
		if ( fieldName == "GuildRatingRanges" )
			return _GuildRatingRanges.IsDerivedFromParent();
		if ( fieldName == "ClanWarsData" )
			return _ClanWarsData.IsDerivedFromParent();
		if ( fieldName == "GuildRecruitment" )
			return _GuildRecruitment.IsDerivedFromParent();
		if ( fieldName == "resourcesToGoldPrice" )
			return _resourcesToGoldPrice.IsDerivedFromParent();
		if ( fieldName == "RerollShop" )
			return _RerollShop.IsDerivedFromParent();
		if ( fieldName == "Seasons" )
			return _Seasons.IsDerivedFromParent();
		if ( fieldName == "SeasonLeagues" )
			return _SeasonLeagues.IsDerivedFromParent();
		if ( fieldName == "DynamicQuestForTalents" )
			return _DynamicQuestForTalents.IsDerivedFromParent();
		if ( fieldName == "talentsCollectionSettings" )
			return _talentsCollectionSettings.IsDerivedFromParent();
		if ( fieldName == "currencies" )
			return _currencies.IsDerivedFromParent();
		if ( fieldName == "Lootboxes" )
			return _Lootboxes.IsDerivedFromParent();
		if ( fieldName == "TalentUpgradeEntities" )
			return _TalentUpgradeEntities.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class StorageBuilding : Constructon
{
	private UndoRedoDBPtr<StorageBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<StorageBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StorageLevel> _StorageLevels;

	[Description( "Уровни склада" )]
	public libdb.IChangeableList<StorageLevel> StorageLevels { get { return _StorageLevels; } set { _StorageLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StorageBuilding>(owner);
		_StorageLevels = new UndoRedoAssignableList<StorageLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_StorageLevels.Changed += FireChangedEvent;
	}

	public StorageBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( StorageBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StorageBuilding" );
		StorageLevels = source.StorageLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StorageBuilding source = _source as StorageBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StorageBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StorageBuilding newParent = rawParent == null ? null : rawParent.Get<StorageBuilding>();
		if ( newParent == null && _newParent is StorageBuilding )
			newParent = _newParent as StorageBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_StorageLevels.SetParent( newParent == null ? null : newParent._StorageLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_StorageLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_StorageLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "StorageLevels" )
			_StorageLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "StorageLevels" )
			return _StorageLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
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

[Custom("Social")]
public class Tavern : Constructon
{
	private UndoRedoDBPtr<Tavern> ___parent;
	[HideInOutliner]
	public new DBPtr<Tavern> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TavernLevel> _tavernLevels;
	private UndoRedoAssignableList<TavernLevelQuest> _tavernLevelQuests;
	private UndoRedoDBPtr<TavernQuest> _patrollQuest;
	private UndoRedo<int> _questRollRange;
	private UndoRedoAssignableList<TavernExpCoeffToHeroLevel> _tavernExpCoeffToHeroLevels;

	public libdb.IChangeableList<TavernLevel> tavernLevels { get { return _tavernLevels; } set { _tavernLevels.Assign( value ); } }

	public libdb.IChangeableList<TavernLevelQuest> tavernLevelQuests { get { return _tavernLevelQuests; } set { _tavernLevelQuests.Assign( value ); } }

	[Description( "Дефолтовый квест партуль" )]
	public DBPtr<TavernQuest> patrollQuest { get { return _patrollQuest.Get(); } set { _patrollQuest.Set( value ); } }

	[Description( "Диапазон выбора квестов для ролла" )]
	public int questRollRange { get { return _questRollRange.Get(); } set { _questRollRange.Set( value ); } }

	[Description( "Таблица для коэффициентов расчета выдачи опыта в зависимости от уровня героя" )]
	public libdb.IChangeableList<TavernExpCoeffToHeroLevel> tavernExpCoeffToHeroLevels { get { return _tavernExpCoeffToHeroLevels; } set { _tavernExpCoeffToHeroLevels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Tavern>(owner);
		_tavernLevels = new UndoRedoAssignableList<TavernLevel>( owner );
		_tavernLevelQuests = new UndoRedoAssignableList<TavernLevelQuest>( owner );
		_patrollQuest = new UndoRedoDBPtr<TavernQuest>( owner );
		_questRollRange = new UndoRedo<int>( owner, 0 );
		_tavernExpCoeffToHeroLevels = new UndoRedoAssignableList<TavernExpCoeffToHeroLevel>( owner );
		___parent.Changed += FireChangedEvent;
		_tavernLevels.Changed += FireChangedEvent;
		_tavernLevelQuests.Changed += FireChangedEvent;
		_patrollQuest.Changed += FireChangedEvent;
		_questRollRange.Changed += FireChangedEvent;
		_tavernExpCoeffToHeroLevels.Changed += FireChangedEvent;
	}

	public Tavern()
	{
		Initialize( this );
	}
	private void AssignSelf( Tavern source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Tavern" );
		tavernLevels = source.tavernLevels;
		tavernLevelQuests = source.tavernLevelQuests;
		patrollQuest = source.patrollQuest;
		questRollRange = source.questRollRange;
		tavernExpCoeffToHeroLevels = source.tavernExpCoeffToHeroLevels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Tavern source = _source as Tavern;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Tavern" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Tavern newParent = rawParent == null ? null : rawParent.Get<Tavern>();
		if ( newParent == null && _newParent is Tavern )
			newParent = _newParent as Tavern;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tavernLevels.SetParent( newParent == null ? null : newParent._tavernLevels );
		_tavernLevelQuests.SetParent( newParent == null ? null : newParent._tavernLevelQuests );
		_patrollQuest.SetParent( newParent == null ? null : newParent._patrollQuest );
		_questRollRange.SetParent( newParent == null ? null : newParent._questRollRange );
		_tavernExpCoeffToHeroLevels.SetParent( newParent == null ? null : newParent._tavernExpCoeffToHeroLevels );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tavernLevels.Reset();
		_tavernLevelQuests.Reset();
		_patrollQuest.Reset();
		_questRollRange.Reset();
		_tavernExpCoeffToHeroLevels.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tavernLevels.IsDerivedFromParent()
			&& _tavernLevelQuests.IsDerivedFromParent()
			&& _patrollQuest.IsDerivedFromParent()
			&& _questRollRange.IsDerivedFromParent()
			&& _tavernExpCoeffToHeroLevels.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tavernLevels" )
			_tavernLevels.Reset();
		else if ( fieldName == "tavernLevelQuests" )
			_tavernLevelQuests.Reset();
		else if ( fieldName == "patrollQuest" )
			_patrollQuest.Reset();
		else if ( fieldName == "questRollRange" )
			_questRollRange.Reset();
		else if ( fieldName == "tavernExpCoeffToHeroLevels" )
			_tavernExpCoeffToHeroLevels.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tavernLevels" )
			return _tavernLevels.IsDerivedFromParent();
		if ( fieldName == "tavernLevelQuests" )
			return _tavernLevelQuests.IsDerivedFromParent();
		if ( fieldName == "patrollQuest" )
			return _patrollQuest.IsDerivedFromParent();
		if ( fieldName == "questRollRange" )
			return _questRollRange.IsDerivedFromParent();
		if ( fieldName == "tavernExpCoeffToHeroLevels" )
			return _tavernExpCoeffToHeroLevels.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("TAVERNQUEST")]
[Custom("Social")]
public class TavernQuest : DBResource
{
	private UndoRedoDBPtr<TavernQuest> ___parent;
	[HideInOutliner]
	public new DBPtr<TavernQuest> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _title;
	private TextRef _description;
	private TavernReward _reward;
	private UndoRedo<int> _energyDecrease;
	private ResourcesTable _priceToStart;
	private UndoRedoDBPtr<TimeBlock> _estimate;
	private UndoRedo<EStat> _statType;
	private UndoRedo<int> _questStatCount;

	[Description( "Заголовок квеста" )]
	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	[Description( "Описание квеста" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Description( "Награды, получаемые за выполнение квеста" )]
	public TavernReward reward { get { return _reward; } set { _reward.Assign( value ); } }

	[Description( "Значение на сколько уменьшится энергии для героев, после выполнения квеста" )]
	public int energyDecrease { get { return _energyDecrease.Get(); } set { _energyDecrease.Set( value ); } }

	[Description( "Цена старта таверны" )]
	public ResourcesTable priceToStart { get { return _priceToStart; } set { _priceToStart.Assign( value ); } }

	[Description( "Время выполнения квеста" )]
	public DBPtr<TimeBlock> estimate { get { return _estimate.Get(); } set { _estimate.Set( value ); } }

	[Description( "Тип необходимого стата" )]
	public EStat statType { get { return _statType.Get(); } set { _statType.Set( value ); } }

	[Description( "Кол-во необходимых статов для выполнения квеста" )]
	public int questStatCount { get { return _questStatCount.Get(); } set { _questStatCount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TavernQuest>(owner);
		_title = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_reward = new TavernReward( owner );
		_energyDecrease = new UndoRedo<int>( owner, 0 );
		_priceToStart = new ResourcesTable( owner );
		_estimate = new UndoRedoDBPtr<TimeBlock>( owner );
		_statType = new UndoRedo<EStat>( owner, EStat.Life );
		_questStatCount = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_reward.Changed += FireChangedEvent;
		_energyDecrease.Changed += FireChangedEvent;
		_priceToStart.Changed += FireChangedEvent;
		_estimate.Changed += FireChangedEvent;
		_statType.Changed += FireChangedEvent;
		_questStatCount.Changed += FireChangedEvent;
	}

	public TavernQuest()
	{
		Initialize( this );
	}
	private void AssignSelf( TavernQuest source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TavernQuest" );
		title = source.title;
		description = source.description;
		reward = source.reward;
		energyDecrease = source.energyDecrease;
		priceToStart = source.priceToStart;
		estimate = source.estimate;
		statType = source.statType;
		questStatCount = source.questStatCount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TavernQuest source = _source as TavernQuest;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TavernQuest" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TavernQuest newParent = rawParent == null ? null : rawParent.Get<TavernQuest>();
		if ( newParent == null && _newParent is TavernQuest )
			newParent = _newParent as TavernQuest;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_title.SetParent( newParent == null ? null : newParent._title );
		_description.SetParent( newParent == null ? null : newParent._description );
		_reward.SetParent( newParent == null ? null : newParent._reward );
		_energyDecrease.SetParent( newParent == null ? null : newParent._energyDecrease );
		_priceToStart.SetParent( newParent == null ? null : newParent._priceToStart );
		_estimate.SetParent( newParent == null ? null : newParent._estimate );
		_statType.SetParent( newParent == null ? null : newParent._statType );
		_questStatCount.SetParent( newParent == null ? null : newParent._questStatCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_title.Reset();
		_description.Reset();
		_reward.Reset();
		_energyDecrease.Reset();
		_priceToStart.Reset();
		_estimate.Reset();
		_statType.Reset();
		_questStatCount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _reward.IsDerivedFromParent()
			&& _energyDecrease.IsDerivedFromParent()
			&& _priceToStart.IsDerivedFromParent()
			&& _estimate.IsDerivedFromParent()
			&& _statType.IsDerivedFromParent()
			&& _questStatCount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "reward" )
			_reward.Reset();
		else if ( fieldName == "energyDecrease" )
			_energyDecrease.Reset();
		else if ( fieldName == "priceToStart" )
			_priceToStart.Reset();
		else if ( fieldName == "estimate" )
			_estimate.Reset();
		else if ( fieldName == "statType" )
			_statType.Reset();
		else if ( fieldName == "questStatCount" )
			_questStatCount.Reset();
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
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "reward" )
			return _reward.IsDerivedFromParent();
		if ( fieldName == "energyDecrease" )
			return _energyDecrease.IsDerivedFromParent();
		if ( fieldName == "priceToStart" )
			return _priceToStart.IsDerivedFromParent();
		if ( fieldName == "estimate" )
			return _estimate.IsDerivedFromParent();
		if ( fieldName == "statType" )
			return _statType.IsDerivedFromParent();
		if ( fieldName == "questStatCount" )
			return _questStatCount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class TimeBlock : DBResource
{
	private UndoRedoDBPtr<TimeBlock> ___parent;
	[HideInOutliner]
	public new DBPtr<TimeBlock> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _time;
	private UndoRedo<int> _gold;

	[Description( "Время цикла в секундах" )]
	public int time { get { return _time.Get(); } set { _time.Set( value ); } }

	[Description( "Базовая цена покупки цикла ( = цена за покупку полного цикла )" )]
	public int gold { get { return _gold.Get(); } set { _gold.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TimeBlock>(owner);
		_time = new UndoRedo<int>( owner, 0 );
		_gold = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_time.Changed += FireChangedEvent;
		_gold.Changed += FireChangedEvent;
	}

	public TimeBlock()
	{
		Initialize( this );
	}
	private void AssignSelf( TimeBlock source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TimeBlock" );
		time = source.time;
		gold = source.gold;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TimeBlock source = _source as TimeBlock;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TimeBlock" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TimeBlock newParent = rawParent == null ? null : rawParent.Get<TimeBlock>();
		if ( newParent == null && _newParent is TimeBlock )
			newParent = _newParent as TimeBlock;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_time.SetParent( newParent == null ? null : newParent._time );
		_gold.SetParent( newParent == null ? null : newParent._gold );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_time.Reset();
		_gold.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_time.IsDerivedFromParent()
			&& _gold.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "time" )
			_time.Reset();
		else if ( fieldName == "gold" )
			_gold.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "time" )
			return _time.IsDerivedFromParent();
		if ( fieldName == "gold" )
			return _gold.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class TournamentInProgressEvent : MarketingEvent
{
	private UndoRedoDBPtr<TournamentInProgressEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<TournamentInProgressEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _tournamentLostImage;
	private UndoRedoDBPtr<Texture> _tournamentLostIcon;
	private TextRef _tournamentLostTooltip;
	private TextRef _inTournamentButtonText;
	private UndoRedo<string> _inTournamentButtonUrl;
	private TextRef _tournamentLostButtonText;
	private UndoRedo<string> _tournamentLostButtonUrl;

	public DBPtr<Texture> tournamentLostImage { get { return _tournamentLostImage.Get(); } set { _tournamentLostImage.Set( value ); } }

	public DBPtr<Texture> tournamentLostIcon { get { return _tournamentLostIcon.Get(); } set { _tournamentLostIcon.Set( value ); } }

	public TextRef tournamentLostTooltip { get { return _tournamentLostTooltip; } set { _tournamentLostTooltip.Assign( value ); } }

	public TextRef inTournamentButtonText { get { return _inTournamentButtonText; } set { _inTournamentButtonText.Assign( value ); } }

	public string inTournamentButtonUrl { get { return _inTournamentButtonUrl.Get(); } set { _inTournamentButtonUrl.Set( value ); } }

	public TextRef tournamentLostButtonText { get { return _tournamentLostButtonText; } set { _tournamentLostButtonText.Assign( value ); } }

	public string tournamentLostButtonUrl { get { return _tournamentLostButtonUrl.Get(); } set { _tournamentLostButtonUrl.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TournamentInProgressEvent>(owner);
		_tournamentLostImage = new UndoRedoDBPtr<Texture>( owner );
		_tournamentLostIcon = new UndoRedoDBPtr<Texture>( owner );
		_tournamentLostTooltip = new TextRef( owner, new TextRef() );
		_inTournamentButtonText = new TextRef( owner, new TextRef() );
		_inTournamentButtonUrl = new UndoRedo<string>( owner, string.Empty );
		_tournamentLostButtonText = new TextRef( owner, new TextRef() );
		_tournamentLostButtonUrl = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_tournamentLostImage.Changed += FireChangedEvent;
		_tournamentLostIcon.Changed += FireChangedEvent;
		_tournamentLostTooltip.Changed += FireChangedEvent;
		_inTournamentButtonText.Changed += FireChangedEvent;
		_inTournamentButtonUrl.Changed += FireChangedEvent;
		_tournamentLostButtonText.Changed += FireChangedEvent;
		_tournamentLostButtonUrl.Changed += FireChangedEvent;
	}

	public TournamentInProgressEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( TournamentInProgressEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TournamentInProgressEvent" );
		tournamentLostImage = source.tournamentLostImage;
		tournamentLostIcon = source.tournamentLostIcon;
		tournamentLostTooltip = source.tournamentLostTooltip;
		inTournamentButtonText = source.inTournamentButtonText;
		inTournamentButtonUrl = source.inTournamentButtonUrl;
		tournamentLostButtonText = source.tournamentLostButtonText;
		tournamentLostButtonUrl = source.tournamentLostButtonUrl;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TournamentInProgressEvent source = _source as TournamentInProgressEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TournamentInProgressEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TournamentInProgressEvent newParent = rawParent == null ? null : rawParent.Get<TournamentInProgressEvent>();
		if ( newParent == null && _newParent is TournamentInProgressEvent )
			newParent = _newParent as TournamentInProgressEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tournamentLostImage.SetParent( newParent == null ? null : newParent._tournamentLostImage );
		_tournamentLostIcon.SetParent( newParent == null ? null : newParent._tournamentLostIcon );
		_tournamentLostTooltip.SetParent( newParent == null ? null : newParent._tournamentLostTooltip );
		_inTournamentButtonText.SetParent( newParent == null ? null : newParent._inTournamentButtonText );
		_inTournamentButtonUrl.SetParent( newParent == null ? null : newParent._inTournamentButtonUrl );
		_tournamentLostButtonText.SetParent( newParent == null ? null : newParent._tournamentLostButtonText );
		_tournamentLostButtonUrl.SetParent( newParent == null ? null : newParent._tournamentLostButtonUrl );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tournamentLostImage.Reset();
		_tournamentLostIcon.Reset();
		_tournamentLostTooltip.Reset();
		_inTournamentButtonText.Reset();
		_inTournamentButtonUrl.Reset();
		_tournamentLostButtonText.Reset();
		_tournamentLostButtonUrl.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tournamentLostImage.IsDerivedFromParent()
			&& _tournamentLostIcon.IsDerivedFromParent()
			&& _tournamentLostTooltip.IsDerivedFromParent()
			&& _inTournamentButtonText.IsDerivedFromParent()
			&& _inTournamentButtonUrl.IsDerivedFromParent()
			&& _tournamentLostButtonText.IsDerivedFromParent()
			&& _tournamentLostButtonUrl.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tournamentLostImage" )
			_tournamentLostImage.Reset();
		else if ( fieldName == "tournamentLostIcon" )
			_tournamentLostIcon.Reset();
		else if ( fieldName == "tournamentLostTooltip" )
			_tournamentLostTooltip.Reset();
		else if ( fieldName == "inTournamentButtonText" )
			_inTournamentButtonText.Reset();
		else if ( fieldName == "inTournamentButtonUrl" )
			_inTournamentButtonUrl.Reset();
		else if ( fieldName == "tournamentLostButtonText" )
			_tournamentLostButtonText.Reset();
		else if ( fieldName == "tournamentLostButtonUrl" )
			_tournamentLostButtonUrl.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tournamentLostImage" )
			return _tournamentLostImage.IsDerivedFromParent();
		if ( fieldName == "tournamentLostIcon" )
			return _tournamentLostIcon.IsDerivedFromParent();
		if ( fieldName == "tournamentLostTooltip" )
			return _tournamentLostTooltip.IsDerivedFromParent();
		if ( fieldName == "inTournamentButtonText" )
			return _inTournamentButtonText.IsDerivedFromParent();
		if ( fieldName == "inTournamentButtonUrl" )
			return _inTournamentButtonUrl.IsDerivedFromParent();
		if ( fieldName == "tournamentLostButtonText" )
			return _tournamentLostButtonText.IsDerivedFromParent();
		if ( fieldName == "tournamentLostButtonUrl" )
			return _tournamentLostButtonUrl.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class TransmutationBuilding : Constructon
{
	private UndoRedoDBPtr<TransmutationBuilding> ___parent;
	[HideInOutliner]
	public new DBPtr<TransmutationBuilding> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _requiredLeveForExclusiveTalents;
	private UndoRedo<int> _requiredLeveForReforging;
	private UndoRedo<int> _requiredLeveForReforgingExclusiveTalents;
	private UndoRedo<ETalentRarity> _requiredRarityForReforging;
	private UndoRedoAssignableList<TransmutationLevel> _TransmutationLevels;
	private UndoRedo<int> _time;

	[Description( "Необходимый уровень кузницы для оранжевых талантов, начинается с 1-чки. Те то что пользователь видит на экране" )]
	public int requiredLeveForExclusiveTalents { get { return _requiredLeveForExclusiveTalents.Get(); } set { _requiredLeveForExclusiveTalents.Set( value ); } }

	[Description( "Уровень кузницы, требуемый для доступа к ЛЮБОЙ перековке талантов" )]
	public int requiredLeveForReforging { get { return _requiredLeveForReforging.Get(); } set { _requiredLeveForReforging.Set( value ); } }

	[Description( "Уровень кузницы, требуемый для перековки ОРАНЖЕВЫХ талантов" )]
	public int requiredLeveForReforgingExclusiveTalents { get { return _requiredLeveForReforgingExclusiveTalents.Get(); } set { _requiredLeveForReforgingExclusiveTalents.Set( value ); } }

	[Description( "Минимальное качество таланта для перековки" )]
	public ETalentRarity requiredRarityForReforging { get { return _requiredRarityForReforging.Get(); } set { _requiredRarityForReforging.Set( value ); } }

	[Description( "Уровни кузницы талантов" )]
	public libdb.IChangeableList<TransmutationLevel> TransmutationLevels { get { return _TransmutationLevels; } set { _TransmutationLevels.Assign( value ); } }

	[Description( "Время цикла в секундах" )]
	public int time { get { return _time.Get(); } set { _time.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TransmutationBuilding>(owner);
		_requiredLeveForExclusiveTalents = new UndoRedo<int>( owner, 20 );
		_requiredLeveForReforging = new UndoRedo<int>( owner, 11 );
		_requiredLeveForReforgingExclusiveTalents = new UndoRedo<int>( owner, 20 );
		_requiredRarityForReforging = new UndoRedo<ETalentRarity>( owner, ETalentRarity.excellent );
		_TransmutationLevels = new UndoRedoAssignableList<TransmutationLevel>( owner );
		_time = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_requiredLeveForExclusiveTalents.Changed += FireChangedEvent;
		_requiredLeveForReforging.Changed += FireChangedEvent;
		_requiredLeveForReforgingExclusiveTalents.Changed += FireChangedEvent;
		_requiredRarityForReforging.Changed += FireChangedEvent;
		_TransmutationLevels.Changed += FireChangedEvent;
		_time.Changed += FireChangedEvent;
	}

	public TransmutationBuilding()
	{
		Initialize( this );
	}
	private void AssignSelf( TransmutationBuilding source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TransmutationBuilding" );
		requiredLeveForExclusiveTalents = source.requiredLeveForExclusiveTalents;
		requiredLeveForReforging = source.requiredLeveForReforging;
		requiredLeveForReforgingExclusiveTalents = source.requiredLeveForReforgingExclusiveTalents;
		requiredRarityForReforging = source.requiredRarityForReforging;
		TransmutationLevels = source.TransmutationLevels;
		time = source.time;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TransmutationBuilding source = _source as TransmutationBuilding;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TransmutationBuilding" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TransmutationBuilding newParent = rawParent == null ? null : rawParent.Get<TransmutationBuilding>();
		if ( newParent == null && _newParent is TransmutationBuilding )
			newParent = _newParent as TransmutationBuilding;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_requiredLeveForExclusiveTalents.SetParent( newParent == null ? null : newParent._requiredLeveForExclusiveTalents );
		_requiredLeveForReforging.SetParent( newParent == null ? null : newParent._requiredLeveForReforging );
		_requiredLeveForReforgingExclusiveTalents.SetParent( newParent == null ? null : newParent._requiredLeveForReforgingExclusiveTalents );
		_requiredRarityForReforging.SetParent( newParent == null ? null : newParent._requiredRarityForReforging );
		_TransmutationLevels.SetParent( newParent == null ? null : newParent._TransmutationLevels );
		_time.SetParent( newParent == null ? null : newParent._time );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_requiredLeveForExclusiveTalents.Reset();
		_requiredLeveForReforging.Reset();
		_requiredLeveForReforgingExclusiveTalents.Reset();
		_requiredRarityForReforging.Reset();
		_TransmutationLevels.Reset();
		_time.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_requiredLeveForExclusiveTalents.IsDerivedFromParent()
			&& _requiredLeveForReforging.IsDerivedFromParent()
			&& _requiredLeveForReforgingExclusiveTalents.IsDerivedFromParent()
			&& _requiredRarityForReforging.IsDerivedFromParent()
			&& _TransmutationLevels.IsDerivedFromParent()
			&& _time.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "requiredLeveForExclusiveTalents" )
			_requiredLeveForExclusiveTalents.Reset();
		else if ( fieldName == "requiredLeveForReforging" )
			_requiredLeveForReforging.Reset();
		else if ( fieldName == "requiredLeveForReforgingExclusiveTalents" )
			_requiredLeveForReforgingExclusiveTalents.Reset();
		else if ( fieldName == "requiredRarityForReforging" )
			_requiredRarityForReforging.Reset();
		else if ( fieldName == "TransmutationLevels" )
			_TransmutationLevels.Reset();
		else if ( fieldName == "time" )
			_time.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "requiredLeveForExclusiveTalents" )
			return _requiredLeveForExclusiveTalents.IsDerivedFromParent();
		if ( fieldName == "requiredLeveForReforging" )
			return _requiredLeveForReforging.IsDerivedFromParent();
		if ( fieldName == "requiredLeveForReforgingExclusiveTalents" )
			return _requiredLeveForReforgingExclusiveTalents.IsDerivedFromParent();
		if ( fieldName == "requiredRarityForReforging" )
			return _requiredRarityForReforging.IsDerivedFromParent();
		if ( fieldName == "TransmutationLevels" )
			return _TransmutationLevels.IsDerivedFromParent();
		if ( fieldName == "time" )
			return _time.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class UITexts : DBResource
{
	private UndoRedoDBPtr<UITexts> ___parent;
	[HideInOutliner]
	public new DBPtr<UITexts> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UIText> _items;

	public libdb.IChangeableList<UIText> items { get { return _items; } set { _items.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UITexts>(owner);
		_items = new UndoRedoAssignableList<UIText>( owner );
		___parent.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
	}

	public UITexts()
	{
		Initialize( this );
	}
	private void AssignSelf( UITexts source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UITexts" );
		items = source.items;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UITexts source = _source as UITexts;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UITexts" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UITexts newParent = rawParent == null ? null : rawParent.Get<UITexts>();
		if ( newParent == null && _newParent is UITexts )
			newParent = _newParent as UITexts;
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

[Custom("Social")]
public class UpgradeHeroTalentsEvent : MarketingEvent
{
	private UndoRedoDBPtr<UpgradeHeroTalentsEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<UpgradeHeroTalentsEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UpgradeHeroTalentsEvent>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UpgradeHeroTalentsEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( UpgradeHeroTalentsEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UpgradeHeroTalentsEvent" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UpgradeHeroTalentsEvent source = _source as UpgradeHeroTalentsEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UpgradeHeroTalentsEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UpgradeHeroTalentsEvent newParent = rawParent == null ? null : rawParent.Get<UpgradeHeroTalentsEvent>();
		if ( newParent == null && _newParent is UpgradeHeroTalentsEvent )
			newParent = _newParent as UpgradeHeroTalentsEvent;
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

[Custom("Social")]
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
