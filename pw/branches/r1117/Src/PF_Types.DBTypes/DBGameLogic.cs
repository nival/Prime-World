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
public enum BillingServicesStart
{
	Impulses = 100,
	Generic = 1000,
	Rewards = 2000,
};

[Custom("Social")]
public enum EGender
{
	Male = 0,
	Female = 1,
};

public enum EGlyphSpawnMode
{
	RandomWeight = 0,
	Ordered = 1,
};

public enum EMenuItemAction
{
	GoBack = 0,
	ContactWithGameMaster = 1,
	OpenSubmenu = 2,
	GameSettings = 3,
	GraphicSettings = 4,
	SoundSettings = 5,
	ControlSettings = 6,
	GoToTown = 7,
	LeaveTheGame = 8,
	LeaveMinigame = 9,
	AbortMinigameLevel = 10,
};

public enum EMenuItemType
{
	ButtonType = 0,
	TextType = 1,
	IconType = 2,
};

public enum ETeamColorID
{
	Team = 0,
	Hero1 = 1,
	Hero2 = 2,
	Hero3 = 3,
	Hero4 = 4,
	Hero5 = 5,
};

public enum GeneralServices
{
	ZZBoost = 0,
};

public enum ImpulseBuffs
{
	Buff_Healing = 0,
	Buff_GetMana = 1,
	Buff_Cleanising = 2,
	Buff_Rising = 3,
	Buff_Invulnerability = 4,
	Buff_Blast = 5,
	Buff_Speed = 6,
	Buff_Help = 7,
	Buff_Gratitude1 = 8,
	Buff_Gratitude2 = 9,
	Buff_Resurrection = 10,
};

public enum TeamForceCalcMethod
{
	Minimum = 0,
	Average = 1,
};

[Custom("DBServer")]
public enum ZZRewards
{
	Victory = 0,
};

public class AbilityAndDamageScalingParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AbilityAndDamageScalingParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _abilityScaleStatLeft;
	private UndoRedo<float> _abilityScaleStatRight;
	private UndoRedo<float> _abilityScaleLifeLeft;
	private UndoRedo<float> _abilityScaleLifeRight;
	private UndoRedo<float> _abilityScaleEnergyLeft;
	private UndoRedo<float> _abilityScaleEnergyRight;
	private UndoRedo<float> _damageScaleStatLeft;
	private UndoRedo<float> _damageScaleStatRight;
	private UndoRedo<float> _damageScaleLifeLeft;
	private UndoRedo<float> _damageScaleLifeRight;
	private UndoRedo<float> _damageScaleEnergyLeft;
	private UndoRedo<float> _damageScaleEnergyRight;

	public float abilityScaleStatLeft { get { return _abilityScaleStatLeft.Get(); } set { _abilityScaleStatLeft.Set( value ); } }

	public float abilityScaleStatRight { get { return _abilityScaleStatRight.Get(); } set { _abilityScaleStatRight.Set( value ); } }

	public float abilityScaleLifeLeft { get { return _abilityScaleLifeLeft.Get(); } set { _abilityScaleLifeLeft.Set( value ); } }

	public float abilityScaleLifeRight { get { return _abilityScaleLifeRight.Get(); } set { _abilityScaleLifeRight.Set( value ); } }

	public float abilityScaleEnergyLeft { get { return _abilityScaleEnergyLeft.Get(); } set { _abilityScaleEnergyLeft.Set( value ); } }

	public float abilityScaleEnergyRight { get { return _abilityScaleEnergyRight.Get(); } set { _abilityScaleEnergyRight.Set( value ); } }

	public float damageScaleStatLeft { get { return _damageScaleStatLeft.Get(); } set { _damageScaleStatLeft.Set( value ); } }

	public float damageScaleStatRight { get { return _damageScaleStatRight.Get(); } set { _damageScaleStatRight.Set( value ); } }

	public float damageScaleLifeLeft { get { return _damageScaleLifeLeft.Get(); } set { _damageScaleLifeLeft.Set( value ); } }

	public float damageScaleLifeRight { get { return _damageScaleLifeRight.Get(); } set { _damageScaleLifeRight.Set( value ); } }

	public float damageScaleEnergyLeft { get { return _damageScaleEnergyLeft.Get(); } set { _damageScaleEnergyLeft.Set( value ); } }

	public float damageScaleEnergyRight { get { return _damageScaleEnergyRight.Get(); } set { _damageScaleEnergyRight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_abilityScaleStatLeft = new UndoRedo<float>( owner, 50.0f );
		_abilityScaleStatRight = new UndoRedo<float>( owner, 160.0f );
		_abilityScaleLifeLeft = new UndoRedo<float>( owner, 600.0f );
		_abilityScaleLifeRight = new UndoRedo<float>( owner, 3350.0f );
		_abilityScaleEnergyLeft = new UndoRedo<float>( owner, 600.0f );
		_abilityScaleEnergyRight = new UndoRedo<float>( owner, 3350.0f );
		_damageScaleStatLeft = new UndoRedo<float>( owner, 50.0f );
		_damageScaleStatRight = new UndoRedo<float>( owner, 223.0f );
		_damageScaleLifeLeft = new UndoRedo<float>( owner, 600.0f );
		_damageScaleLifeRight = new UndoRedo<float>( owner, 4683.0f );
		_damageScaleEnergyLeft = new UndoRedo<float>( owner, 600.0f );
		_damageScaleEnergyRight = new UndoRedo<float>( owner, 4683.0f );
		_abilityScaleStatLeft.Changed += FireChangedEvent;
		_abilityScaleStatRight.Changed += FireChangedEvent;
		_abilityScaleLifeLeft.Changed += FireChangedEvent;
		_abilityScaleLifeRight.Changed += FireChangedEvent;
		_abilityScaleEnergyLeft.Changed += FireChangedEvent;
		_abilityScaleEnergyRight.Changed += FireChangedEvent;
		_damageScaleStatLeft.Changed += FireChangedEvent;
		_damageScaleStatRight.Changed += FireChangedEvent;
		_damageScaleLifeLeft.Changed += FireChangedEvent;
		_damageScaleLifeRight.Changed += FireChangedEvent;
		_damageScaleEnergyLeft.Changed += FireChangedEvent;
		_damageScaleEnergyRight.Changed += FireChangedEvent;
	}

	public AbilityAndDamageScalingParams()
	{
		Initialize( GetOwner() );
	}

	public AbilityAndDamageScalingParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AbilityAndDamageScalingParams( DBResource owner, AbilityAndDamageScalingParams source )
		: this(owner, source, true){}

	protected AbilityAndDamageScalingParams( DBResource owner, AbilityAndDamageScalingParams source, bool fireEvent )
	{
		_abilityScaleStatLeft = new UndoRedo<float>( owner, source.abilityScaleStatLeft );
		_abilityScaleStatRight = new UndoRedo<float>( owner, source.abilityScaleStatRight );
		_abilityScaleLifeLeft = new UndoRedo<float>( owner, source.abilityScaleLifeLeft );
		_abilityScaleLifeRight = new UndoRedo<float>( owner, source.abilityScaleLifeRight );
		_abilityScaleEnergyLeft = new UndoRedo<float>( owner, source.abilityScaleEnergyLeft );
		_abilityScaleEnergyRight = new UndoRedo<float>( owner, source.abilityScaleEnergyRight );
		_damageScaleStatLeft = new UndoRedo<float>( owner, source.damageScaleStatLeft );
		_damageScaleStatRight = new UndoRedo<float>( owner, source.damageScaleStatRight );
		_damageScaleLifeLeft = new UndoRedo<float>( owner, source.damageScaleLifeLeft );
		_damageScaleLifeRight = new UndoRedo<float>( owner, source.damageScaleLifeRight );
		_damageScaleEnergyLeft = new UndoRedo<float>( owner, source.damageScaleEnergyLeft );
		_damageScaleEnergyRight = new UndoRedo<float>( owner, source.damageScaleEnergyRight );
		_abilityScaleStatLeft.Changed += FireChangedEvent;
		_abilityScaleStatRight.Changed += FireChangedEvent;
		_abilityScaleLifeLeft.Changed += FireChangedEvent;
		_abilityScaleLifeRight.Changed += FireChangedEvent;
		_abilityScaleEnergyLeft.Changed += FireChangedEvent;
		_abilityScaleEnergyRight.Changed += FireChangedEvent;
		_damageScaleStatLeft.Changed += FireChangedEvent;
		_damageScaleStatRight.Changed += FireChangedEvent;
		_damageScaleLifeLeft.Changed += FireChangedEvent;
		_damageScaleLifeRight.Changed += FireChangedEvent;
		_damageScaleEnergyLeft.Changed += FireChangedEvent;
		_damageScaleEnergyRight.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AbilityAndDamageScalingParams source = _source as AbilityAndDamageScalingParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbilityAndDamageScalingParams" );
		abilityScaleStatLeft = source.abilityScaleStatLeft;
		abilityScaleStatRight = source.abilityScaleStatRight;
		abilityScaleLifeLeft = source.abilityScaleLifeLeft;
		abilityScaleLifeRight = source.abilityScaleLifeRight;
		abilityScaleEnergyLeft = source.abilityScaleEnergyLeft;
		abilityScaleEnergyRight = source.abilityScaleEnergyRight;
		damageScaleStatLeft = source.damageScaleStatLeft;
		damageScaleStatRight = source.damageScaleStatRight;
		damageScaleLifeLeft = source.damageScaleLifeLeft;
		damageScaleLifeRight = source.damageScaleLifeRight;
		damageScaleEnergyLeft = source.damageScaleEnergyLeft;
		damageScaleEnergyRight = source.damageScaleEnergyRight;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AbilityAndDamageScalingParams newParent = _newParent as AbilityAndDamageScalingParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_abilityScaleStatLeft.SetParent( newParent == null ? null : newParent._abilityScaleStatLeft );
		_abilityScaleStatRight.SetParent( newParent == null ? null : newParent._abilityScaleStatRight );
		_abilityScaleLifeLeft.SetParent( newParent == null ? null : newParent._abilityScaleLifeLeft );
		_abilityScaleLifeRight.SetParent( newParent == null ? null : newParent._abilityScaleLifeRight );
		_abilityScaleEnergyLeft.SetParent( newParent == null ? null : newParent._abilityScaleEnergyLeft );
		_abilityScaleEnergyRight.SetParent( newParent == null ? null : newParent._abilityScaleEnergyRight );
		_damageScaleStatLeft.SetParent( newParent == null ? null : newParent._damageScaleStatLeft );
		_damageScaleStatRight.SetParent( newParent == null ? null : newParent._damageScaleStatRight );
		_damageScaleLifeLeft.SetParent( newParent == null ? null : newParent._damageScaleLifeLeft );
		_damageScaleLifeRight.SetParent( newParent == null ? null : newParent._damageScaleLifeRight );
		_damageScaleEnergyLeft.SetParent( newParent == null ? null : newParent._damageScaleEnergyLeft );
		_damageScaleEnergyRight.SetParent( newParent == null ? null : newParent._damageScaleEnergyRight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_abilityScaleStatLeft.Reset();
		_abilityScaleStatRight.Reset();
		_abilityScaleLifeLeft.Reset();
		_abilityScaleLifeRight.Reset();
		_abilityScaleEnergyLeft.Reset();
		_abilityScaleEnergyRight.Reset();
		_damageScaleStatLeft.Reset();
		_damageScaleStatRight.Reset();
		_damageScaleLifeLeft.Reset();
		_damageScaleLifeRight.Reset();
		_damageScaleEnergyLeft.Reset();
		_damageScaleEnergyRight.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_abilityScaleStatLeft.IsDerivedFromParent()
			&& _abilityScaleStatRight.IsDerivedFromParent()
			&& _abilityScaleLifeLeft.IsDerivedFromParent()
			&& _abilityScaleLifeRight.IsDerivedFromParent()
			&& _abilityScaleEnergyLeft.IsDerivedFromParent()
			&& _abilityScaleEnergyRight.IsDerivedFromParent()
			&& _damageScaleStatLeft.IsDerivedFromParent()
			&& _damageScaleStatRight.IsDerivedFromParent()
			&& _damageScaleLifeLeft.IsDerivedFromParent()
			&& _damageScaleLifeRight.IsDerivedFromParent()
			&& _damageScaleEnergyLeft.IsDerivedFromParent()
			&& _damageScaleEnergyRight.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "abilityScaleStatLeft" )
			_abilityScaleStatLeft.Reset();
		else if ( fieldName == "abilityScaleStatRight" )
			_abilityScaleStatRight.Reset();
		else if ( fieldName == "abilityScaleLifeLeft" )
			_abilityScaleLifeLeft.Reset();
		else if ( fieldName == "abilityScaleLifeRight" )
			_abilityScaleLifeRight.Reset();
		else if ( fieldName == "abilityScaleEnergyLeft" )
			_abilityScaleEnergyLeft.Reset();
		else if ( fieldName == "abilityScaleEnergyRight" )
			_abilityScaleEnergyRight.Reset();
		else if ( fieldName == "damageScaleStatLeft" )
			_damageScaleStatLeft.Reset();
		else if ( fieldName == "damageScaleStatRight" )
			_damageScaleStatRight.Reset();
		else if ( fieldName == "damageScaleLifeLeft" )
			_damageScaleLifeLeft.Reset();
		else if ( fieldName == "damageScaleLifeRight" )
			_damageScaleLifeRight.Reset();
		else if ( fieldName == "damageScaleEnergyLeft" )
			_damageScaleEnergyLeft.Reset();
		else if ( fieldName == "damageScaleEnergyRight" )
			_damageScaleEnergyRight.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "abilityScaleStatLeft" )
			return _abilityScaleStatLeft.IsDerivedFromParent();
		if ( fieldName == "abilityScaleStatRight" )
			return _abilityScaleStatRight.IsDerivedFromParent();
		if ( fieldName == "abilityScaleLifeLeft" )
			return _abilityScaleLifeLeft.IsDerivedFromParent();
		if ( fieldName == "abilityScaleLifeRight" )
			return _abilityScaleLifeRight.IsDerivedFromParent();
		if ( fieldName == "abilityScaleEnergyLeft" )
			return _abilityScaleEnergyLeft.IsDerivedFromParent();
		if ( fieldName == "abilityScaleEnergyRight" )
			return _abilityScaleEnergyRight.IsDerivedFromParent();
		if ( fieldName == "damageScaleStatLeft" )
			return _damageScaleStatLeft.IsDerivedFromParent();
		if ( fieldName == "damageScaleStatRight" )
			return _damageScaleStatRight.IsDerivedFromParent();
		if ( fieldName == "damageScaleLifeLeft" )
			return _damageScaleLifeLeft.IsDerivedFromParent();
		if ( fieldName == "damageScaleLifeRight" )
			return _damageScaleLifeRight.IsDerivedFromParent();
		if ( fieldName == "damageScaleEnergyLeft" )
			return _damageScaleEnergyLeft.IsDerivedFromParent();
		if ( fieldName == "damageScaleEnergyRight" )
			return _damageScaleEnergyRight.IsDerivedFromParent();
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
public class BuyServiceCost : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BuyServiceCost __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _goldCost;

	[Description( "Cost of service in zzgold." )]
	public int goldCost { get { return _goldCost.Get(); } set { _goldCost.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_goldCost = new UndoRedo<int>( owner, 1 );
		_goldCost.Changed += FireChangedEvent;
	}

	public BuyServiceCost()
	{
		Initialize( GetOwner() );
	}

	public BuyServiceCost( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BuyServiceCost( DBResource owner, BuyServiceCost source )
		: this(owner, source, true){}

	protected BuyServiceCost( DBResource owner, BuyServiceCost source, bool fireEvent )
	{
		_goldCost = new UndoRedo<int>( owner, source.goldCost );
		_goldCost.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BuyServiceCost source = _source as BuyServiceCost;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyServiceCost" );
		goldCost = source.goldCost;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BuyServiceCost newParent = _newParent as BuyServiceCost;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_goldCost.SetParent( newParent == null ? null : newParent._goldCost );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_goldCost.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_goldCost.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "goldCost" )
			_goldCost.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "goldCost" )
			return _goldCost.IsDerivedFromParent();
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

public class CommonSummonParameters : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CommonSummonParameters __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _primarySummonEscortDistance;
	private UndoRedo<float> _secondarySummonEscortDistance;
	private UndoRedo<float> _petEscortDistance;

	public float primarySummonEscortDistance { get { return _primarySummonEscortDistance.Get(); } set { _primarySummonEscortDistance.Set( value ); } }

	public float secondarySummonEscortDistance { get { return _secondarySummonEscortDistance.Get(); } set { _secondarySummonEscortDistance.Set( value ); } }

	public float petEscortDistance { get { return _petEscortDistance.Get(); } set { _petEscortDistance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_primarySummonEscortDistance = new UndoRedo<float>( owner, 4.5f );
		_secondarySummonEscortDistance = new UndoRedo<float>( owner, 7.0f );
		_petEscortDistance = new UndoRedo<float>( owner, 2.5f );
		_primarySummonEscortDistance.Changed += FireChangedEvent;
		_secondarySummonEscortDistance.Changed += FireChangedEvent;
		_petEscortDistance.Changed += FireChangedEvent;
	}

	public CommonSummonParameters()
	{
		Initialize( GetOwner() );
	}

	public CommonSummonParameters( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CommonSummonParameters( DBResource owner, CommonSummonParameters source )
		: this(owner, source, true){}

	protected CommonSummonParameters( DBResource owner, CommonSummonParameters source, bool fireEvent )
	{
		_primarySummonEscortDistance = new UndoRedo<float>( owner, source.primarySummonEscortDistance );
		_secondarySummonEscortDistance = new UndoRedo<float>( owner, source.secondarySummonEscortDistance );
		_petEscortDistance = new UndoRedo<float>( owner, source.petEscortDistance );
		_primarySummonEscortDistance.Changed += FireChangedEvent;
		_secondarySummonEscortDistance.Changed += FireChangedEvent;
		_petEscortDistance.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CommonSummonParameters source = _source as CommonSummonParameters;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CommonSummonParameters" );
		primarySummonEscortDistance = source.primarySummonEscortDistance;
		secondarySummonEscortDistance = source.secondarySummonEscortDistance;
		petEscortDistance = source.petEscortDistance;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CommonSummonParameters newParent = _newParent as CommonSummonParameters;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_primarySummonEscortDistance.SetParent( newParent == null ? null : newParent._primarySummonEscortDistance );
		_secondarySummonEscortDistance.SetParent( newParent == null ? null : newParent._secondarySummonEscortDistance );
		_petEscortDistance.SetParent( newParent == null ? null : newParent._petEscortDistance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_primarySummonEscortDistance.Reset();
		_secondarySummonEscortDistance.Reset();
		_petEscortDistance.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_primarySummonEscortDistance.IsDerivedFromParent()
			&& _secondarySummonEscortDistance.IsDerivedFromParent()
			&& _petEscortDistance.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "primarySummonEscortDistance" )
			_primarySummonEscortDistance.Reset();
		else if ( fieldName == "secondarySummonEscortDistance" )
			_secondarySummonEscortDistance.Reset();
		else if ( fieldName == "petEscortDistance" )
			_petEscortDistance.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "primarySummonEscortDistance" )
			return _primarySummonEscortDistance.IsDerivedFromParent();
		if ( fieldName == "secondarySummonEscortDistance" )
			return _secondarySummonEscortDistance.IsDerivedFromParent();
		if ( fieldName == "petEscortDistance" )
			return _petEscortDistance.IsDerivedFromParent();
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

[IndexField("caption")]
public class ConsumableGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ConsumableGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _caption;
	private TextRef _name;
	private TextRef _description;
	private UndoRedo<float> _cooldown;
	private UndoRedoAssignableList<DBPtr<Consumable>> _consumables;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public float cooldown { get { return _cooldown.Get(); } set { _cooldown.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Consumable>> consumables { get { return _consumables; } set { _consumables.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_caption = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_cooldown = new UndoRedo<float>( owner, 1.0f );
		_consumables = new UndoRedoAssignableList<DBPtr<Consumable>>( owner );
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_consumables.Changed += FireChangedEvent;
	}

	public ConsumableGroup()
	{
		Initialize( GetOwner() );
	}

	public ConsumableGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ConsumableGroup( DBResource owner, ConsumableGroup source )
		: this(owner, source, true){}

	protected ConsumableGroup( DBResource owner, ConsumableGroup source, bool fireEvent )
	{
		_caption = new UndoRedo<string>( owner, source.caption );
		_name = new TextRef( owner, source.name );
		_description = new TextRef( owner, source.description );
		_cooldown = new UndoRedo<float>( owner, source.cooldown );
		_consumables = new UndoRedoAssignableList<DBPtr<Consumable>>( owner );
		_consumables.Assign( source.consumables );
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_consumables.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ConsumableGroup source = _source as ConsumableGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConsumableGroup" );
		caption = source.caption;
		name = source.name;
		description = source.description;
		cooldown = source.cooldown;
		consumables = source.consumables;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ConsumableGroup newParent = _newParent as ConsumableGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_cooldown.SetParent( newParent == null ? null : newParent._cooldown );
		_consumables.SetParent( newParent == null ? null : newParent._consumables );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_caption.Reset();
		_name.Reset();
		_description.Reset();
		_cooldown.Reset();
		_consumables.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _cooldown.IsDerivedFromParent()
			&& _consumables.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "cooldown" )
			_cooldown.Reset();
		else if ( fieldName == "consumables" )
			_consumables.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "cooldown" )
			return _cooldown.IsDerivedFromParent();
		if ( fieldName == "consumables" )
			return _consumables.IsDerivedFromParent();
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

public class CreatureHappyStateParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreatureHappyStateParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _happyCreaturesPercent;
	private UndoRedo<float> _minRestTime;
	private UndoRedo<float> _happyCheckTick;

	[Description( "Процент ''счастливых'' крипов: [0..1]" )]
	public float happyCreaturesPercent { get { return _happyCreaturesPercent.Get(); } set { _happyCreaturesPercent.Set( value ); } }

	[Description( "Сколько секунд крип должен отдыхать от ''счастья''" )]
	public float minRestTime { get { return _minRestTime.Get(); } set { _minRestTime.Set( value ); } }

	[Description( "Раз в сколько секунд проверяем процент ''счастливых'' крипов" )]
	public float happyCheckTick { get { return _happyCheckTick.Get(); } set { _happyCheckTick.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_happyCreaturesPercent = new UndoRedo<float>( owner, 0.5f );
		_minRestTime = new UndoRedo<float>( owner, 0.5f );
		_happyCheckTick = new UndoRedo<float>( owner, 1.0f );
		_happyCreaturesPercent.Changed += FireChangedEvent;
		_minRestTime.Changed += FireChangedEvent;
		_happyCheckTick.Changed += FireChangedEvent;
	}

	public CreatureHappyStateParams()
	{
		Initialize( GetOwner() );
	}

	public CreatureHappyStateParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreatureHappyStateParams( DBResource owner, CreatureHappyStateParams source )
		: this(owner, source, true){}

	protected CreatureHappyStateParams( DBResource owner, CreatureHappyStateParams source, bool fireEvent )
	{
		_happyCreaturesPercent = new UndoRedo<float>( owner, source.happyCreaturesPercent );
		_minRestTime = new UndoRedo<float>( owner, source.minRestTime );
		_happyCheckTick = new UndoRedo<float>( owner, source.happyCheckTick );
		_happyCreaturesPercent.Changed += FireChangedEvent;
		_minRestTime.Changed += FireChangedEvent;
		_happyCheckTick.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreatureHappyStateParams source = _source as CreatureHappyStateParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreatureHappyStateParams" );
		happyCreaturesPercent = source.happyCreaturesPercent;
		minRestTime = source.minRestTime;
		happyCheckTick = source.happyCheckTick;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreatureHappyStateParams newParent = _newParent as CreatureHappyStateParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_happyCreaturesPercent.SetParent( newParent == null ? null : newParent._happyCreaturesPercent );
		_minRestTime.SetParent( newParent == null ? null : newParent._minRestTime );
		_happyCheckTick.SetParent( newParent == null ? null : newParent._happyCheckTick );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_happyCreaturesPercent.Reset();
		_minRestTime.Reset();
		_happyCheckTick.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_happyCreaturesPercent.IsDerivedFromParent()
			&& _minRestTime.IsDerivedFromParent()
			&& _happyCheckTick.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "happyCreaturesPercent" )
			_happyCreaturesPercent.Reset();
		else if ( fieldName == "minRestTime" )
			_minRestTime.Reset();
		else if ( fieldName == "happyCheckTick" )
			_happyCheckTick.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "happyCreaturesPercent" )
			return _happyCreaturesPercent.IsDerivedFromParent();
		if ( fieldName == "minRestTime" )
			return _minRestTime.IsDerivedFromParent();
		if ( fieldName == "happyCheckTick" )
			return _happyCheckTick.IsDerivedFromParent();
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

public class CreepsLevelUpInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreepsLevelUpInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _interval;
	private UndoRedo<int> _increment;

	public float interval { get { return _interval.Get(); } set { _interval.Set( value ); } }

	public int increment { get { return _increment.Get(); } set { _increment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_interval = new UndoRedo<float>( owner, 300.0f );
		_increment = new UndoRedo<int>( owner, 1 );
		_interval.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
	}

	public CreepsLevelUpInfo()
	{
		Initialize( GetOwner() );
	}

	public CreepsLevelUpInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreepsLevelUpInfo( DBResource owner, CreepsLevelUpInfo source )
		: this(owner, source, true){}

	protected CreepsLevelUpInfo( DBResource owner, CreepsLevelUpInfo source, bool fireEvent )
	{
		_interval = new UndoRedo<float>( owner, source.interval );
		_increment = new UndoRedo<int>( owner, source.increment );
		_interval.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreepsLevelUpInfo source = _source as CreepsLevelUpInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepsLevelUpInfo" );
		interval = source.interval;
		increment = source.increment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreepsLevelUpInfo newParent = _newParent as CreepsLevelUpInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_interval.SetParent( newParent == null ? null : newParent._interval );
		_increment.SetParent( newParent == null ? null : newParent._increment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_interval.Reset();
		_increment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_interval.IsDerivedFromParent()
			&& _increment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "interval" )
			_interval.Reset();
		else if ( fieldName == "increment" )
			_increment.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "interval" )
			return _interval.IsDerivedFromParent();
		if ( fieldName == "increment" )
			return _increment.IsDerivedFromParent();
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
public class DBFameRatingPair : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBFameRatingPair __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _fameLevel;
	private UndoRedo<int> _rating;

	public int fameLevel { get { return _fameLevel.Get(); } set { _fameLevel.Set( value ); } }

	public int rating { get { return _rating.Get(); } set { _rating.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_fameLevel = new UndoRedo<int>( owner, 0 );
		_rating = new UndoRedo<int>( owner, 0 );
		_fameLevel.Changed += FireChangedEvent;
		_rating.Changed += FireChangedEvent;
	}

	public DBFameRatingPair()
	{
		Initialize( GetOwner() );
	}

	public DBFameRatingPair( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBFameRatingPair( DBResource owner, DBFameRatingPair source )
		: this(owner, source, true){}

	protected DBFameRatingPair( DBResource owner, DBFameRatingPair source, bool fireEvent )
	{
		_fameLevel = new UndoRedo<int>( owner, source.fameLevel );
		_rating = new UndoRedo<int>( owner, source.rating );
		_fameLevel.Changed += FireChangedEvent;
		_rating.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBFameRatingPair source = _source as DBFameRatingPair;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBFameRatingPair" );
		fameLevel = source.fameLevel;
		rating = source.rating;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBFameRatingPair newParent = _newParent as DBFameRatingPair;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_fameLevel.SetParent( newParent == null ? null : newParent._fameLevel );
		_rating.SetParent( newParent == null ? null : newParent._rating );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_fameLevel.Reset();
		_rating.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_fameLevel.IsDerivedFromParent()
			&& _rating.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "fameLevel" )
			_fameLevel.Reset();
		else if ( fieldName == "rating" )
			_rating.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "fameLevel" )
			return _fameLevel.IsDerivedFromParent();
		if ( fieldName == "rating" )
			return _rating.IsDerivedFromParent();
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

public class ExpoModeParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ExpoModeParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<StatsEnhancersContainer> _statsEnhancers;
	private UndoRedo<float> _minHeroLife;
	private ExecutableFloatString _damageModifier;

	public DBPtr<StatsEnhancersContainer> statsEnhancers { get { return _statsEnhancers.Get(); } set { _statsEnhancers.Set( value ); } }

	public float minHeroLife { get { return _minHeroLife.Get(); } set { _minHeroLife.Set( value ); } }

	public ExecutableFloatString damageModifier { get { return _damageModifier; } set { _damageModifier.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_statsEnhancers = new UndoRedoDBPtr<StatsEnhancersContainer>( owner );
		_minHeroLife = new UndoRedo<float>( owner, 0.0f );
		ExecutableFloatString __damageModifier = new ExecutableFloatString(); // Construct default object for damageModifier
		__damageModifier.sString = "1.0f";
		_damageModifier = new ExecutableFloatString( owner, __damageModifier );
		_statsEnhancers.Changed += FireChangedEvent;
		_minHeroLife.Changed += FireChangedEvent;
		_damageModifier.Changed += FireChangedEvent;
	}

	public ExpoModeParams()
	{
		Initialize( GetOwner() );
	}

	public ExpoModeParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ExpoModeParams( DBResource owner, ExpoModeParams source )
		: this(owner, source, true){}

	protected ExpoModeParams( DBResource owner, ExpoModeParams source, bool fireEvent )
	{
		_statsEnhancers = new UndoRedoDBPtr<StatsEnhancersContainer>( owner, source.statsEnhancers );
		_minHeroLife = new UndoRedo<float>( owner, source.minHeroLife );
		_damageModifier = new ExecutableFloatString( owner, source.damageModifier );
		_statsEnhancers.Changed += FireChangedEvent;
		_minHeroLife.Changed += FireChangedEvent;
		_damageModifier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ExpoModeParams source = _source as ExpoModeParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExpoModeParams" );
		statsEnhancers = source.statsEnhancers;
		minHeroLife = source.minHeroLife;
		damageModifier = source.damageModifier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ExpoModeParams newParent = _newParent as ExpoModeParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_statsEnhancers.SetParent( newParent == null ? null : newParent._statsEnhancers );
		_minHeroLife.SetParent( newParent == null ? null : newParent._minHeroLife );
		_damageModifier.SetParent( newParent == null ? null : newParent._damageModifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statsEnhancers.Reset();
		_minHeroLife.Reset();
		_damageModifier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statsEnhancers.IsDerivedFromParent()
			&& _minHeroLife.IsDerivedFromParent()
			&& _damageModifier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statsEnhancers" )
			_statsEnhancers.Reset();
		else if ( fieldName == "minHeroLife" )
			_minHeroLife.Reset();
		else if ( fieldName == "damageModifier" )
			_damageModifier.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "statsEnhancers" )
			return _statsEnhancers.IsDerivedFromParent();
		if ( fieldName == "minHeroLife" )
			return _minHeroLife.IsDerivedFromParent();
		if ( fieldName == "damageModifier" )
			return _damageModifier.IsDerivedFromParent();
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

public class GameMenuItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GameMenuItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _itemText;
	private UndoRedo<EMenuItemType> _itemType;
	private UndoRedo<EMenuItemAction> _itemAction;
	private UndoRedo<bool> _minigamesOnly;
	private UndoRedoDBPtr<DBGameMenu> _subMenu;

	[Description( "An item text." )]
	public TextRef itemText { get { return _itemText; } set { _itemText.Assign( value ); } }

	[Description( "An item type. For example it might be button, text or icon." )]
	public EMenuItemType itemType { get { return _itemType.Get(); } set { _itemType.Set( value ); } }

	[Description( "An item action after click. Open the sub menu for example, or continue the game, etc." )]
	public EMenuItemAction itemAction { get { return _itemAction.Get(); } set { _itemAction.Set( value ); } }

	[Description( "This menu item will only be shown in minigames" )]
	public bool minigamesOnly { get { return _minigamesOnly.Get(); } set { _minigamesOnly.Set( value ); } }

	public DBPtr<DBGameMenu> subMenu { get { return _subMenu.Get(); } set { _subMenu.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_itemText = new TextRef( owner, new TextRef() );
		_itemType = new UndoRedo<EMenuItemType>( owner, EMenuItemType.ButtonType );
		_itemAction = new UndoRedo<EMenuItemAction>( owner, EMenuItemAction.GoBack );
		_minigamesOnly = new UndoRedo<bool>( owner, false );
		_subMenu = new UndoRedoDBPtr<DBGameMenu>( owner );
		_itemText.Changed += FireChangedEvent;
		_itemType.Changed += FireChangedEvent;
		_itemAction.Changed += FireChangedEvent;
		_minigamesOnly.Changed += FireChangedEvent;
		_subMenu.Changed += FireChangedEvent;
	}

	public GameMenuItem()
	{
		Initialize( GetOwner() );
	}

	public GameMenuItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GameMenuItem( DBResource owner, GameMenuItem source )
		: this(owner, source, true){}

	protected GameMenuItem( DBResource owner, GameMenuItem source, bool fireEvent )
	{
		_itemText = new TextRef( owner, source.itemText );
		_itemType = new UndoRedo<EMenuItemType>( owner, source.itemType );
		_itemAction = new UndoRedo<EMenuItemAction>( owner, source.itemAction );
		_minigamesOnly = new UndoRedo<bool>( owner, source.minigamesOnly );
		_subMenu = new UndoRedoDBPtr<DBGameMenu>( owner, source.subMenu );
		_itemText.Changed += FireChangedEvent;
		_itemType.Changed += FireChangedEvent;
		_itemAction.Changed += FireChangedEvent;
		_minigamesOnly.Changed += FireChangedEvent;
		_subMenu.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GameMenuItem source = _source as GameMenuItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GameMenuItem" );
		itemText = source.itemText;
		itemType = source.itemType;
		itemAction = source.itemAction;
		minigamesOnly = source.minigamesOnly;
		subMenu = source.subMenu;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GameMenuItem newParent = _newParent as GameMenuItem;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_itemText.SetParent( newParent == null ? null : newParent._itemText );
		_itemType.SetParent( newParent == null ? null : newParent._itemType );
		_itemAction.SetParent( newParent == null ? null : newParent._itemAction );
		_minigamesOnly.SetParent( newParent == null ? null : newParent._minigamesOnly );
		_subMenu.SetParent( newParent == null ? null : newParent._subMenu );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_itemText.Reset();
		_itemType.Reset();
		_itemAction.Reset();
		_minigamesOnly.Reset();
		_subMenu.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_itemText.IsDerivedFromParent()
			&& _itemType.IsDerivedFromParent()
			&& _itemAction.IsDerivedFromParent()
			&& _minigamesOnly.IsDerivedFromParent()
			&& _subMenu.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "itemText" )
			_itemText.Reset();
		else if ( fieldName == "itemType" )
			_itemType.Reset();
		else if ( fieldName == "itemAction" )
			_itemAction.Reset();
		else if ( fieldName == "minigamesOnly" )
			_minigamesOnly.Reset();
		else if ( fieldName == "subMenu" )
			_subMenu.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "itemText" )
			return _itemText.IsDerivedFromParent();
		if ( fieldName == "itemType" )
			return _itemType.IsDerivedFromParent();
		if ( fieldName == "itemAction" )
			return _itemAction.IsDerivedFromParent();
		if ( fieldName == "minigamesOnly" )
			return _minigamesOnly.IsDerivedFromParent();
		if ( fieldName == "subMenu" )
			return _subMenu.IsDerivedFromParent();
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

[DBVersion(0)]
public class GlyphSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GlyphSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minNormalSpawnDelay;
	private UndoRedo<float> _maxNormalSpawnDelay;
	private UndoRedo<float> _minAfterPickupSpawnDelay;
	private UndoRedo<float> _maxAfterPickupSpawnDelay;
	private UndoRedo<float> _spawnAttemptDelayDecrease;
	private UndoRedo<int> _maxInstances;
	private UndoRedo<EGlyphSpawnMode> _spawnMode;

	public float minNormalSpawnDelay { get { return _minNormalSpawnDelay.Get(); } set { _minNormalSpawnDelay.Set( value ); } }

	public float maxNormalSpawnDelay { get { return _maxNormalSpawnDelay.Get(); } set { _maxNormalSpawnDelay.Set( value ); } }

	public float minAfterPickupSpawnDelay { get { return _minAfterPickupSpawnDelay.Get(); } set { _minAfterPickupSpawnDelay.Set( value ); } }

	public float maxAfterPickupSpawnDelay { get { return _maxAfterPickupSpawnDelay.Get(); } set { _maxAfterPickupSpawnDelay.Set( value ); } }

	public float spawnAttemptDelayDecrease { get { return _spawnAttemptDelayDecrease.Get(); } set { _spawnAttemptDelayDecrease.Set( value ); } }

	[Description( "Максимальное количество глифов на карте (во всех спавнерах)" )]
	public int maxInstances { get { return _maxInstances.Get(); } set { _maxInstances.Set( value ); } }

	public EGlyphSpawnMode spawnMode { get { return _spawnMode.Get(); } set { _spawnMode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minNormalSpawnDelay = new UndoRedo<float>( owner, 50.0f );
		_maxNormalSpawnDelay = new UndoRedo<float>( owner, 150.0f );
		_minAfterPickupSpawnDelay = new UndoRedo<float>( owner, 50.0f );
		_maxAfterPickupSpawnDelay = new UndoRedo<float>( owner, 240.0f );
		_spawnAttemptDelayDecrease = new UndoRedo<float>( owner, 50.0f );
		_maxInstances = new UndoRedo<int>( owner, 2 );
		_spawnMode = new UndoRedo<EGlyphSpawnMode>( owner, EGlyphSpawnMode.RandomWeight );
		_minNormalSpawnDelay.Changed += FireChangedEvent;
		_maxNormalSpawnDelay.Changed += FireChangedEvent;
		_minAfterPickupSpawnDelay.Changed += FireChangedEvent;
		_maxAfterPickupSpawnDelay.Changed += FireChangedEvent;
		_spawnAttemptDelayDecrease.Changed += FireChangedEvent;
		_maxInstances.Changed += FireChangedEvent;
		_spawnMode.Changed += FireChangedEvent;
	}

	public GlyphSettings()
	{
		Initialize( GetOwner() );
	}

	public GlyphSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GlyphSettings( DBResource owner, GlyphSettings source )
		: this(owner, source, true){}

	protected GlyphSettings( DBResource owner, GlyphSettings source, bool fireEvent )
	{
		_minNormalSpawnDelay = new UndoRedo<float>( owner, source.minNormalSpawnDelay );
		_maxNormalSpawnDelay = new UndoRedo<float>( owner, source.maxNormalSpawnDelay );
		_minAfterPickupSpawnDelay = new UndoRedo<float>( owner, source.minAfterPickupSpawnDelay );
		_maxAfterPickupSpawnDelay = new UndoRedo<float>( owner, source.maxAfterPickupSpawnDelay );
		_spawnAttemptDelayDecrease = new UndoRedo<float>( owner, source.spawnAttemptDelayDecrease );
		_maxInstances = new UndoRedo<int>( owner, source.maxInstances );
		_spawnMode = new UndoRedo<EGlyphSpawnMode>( owner, source.spawnMode );
		_minNormalSpawnDelay.Changed += FireChangedEvent;
		_maxNormalSpawnDelay.Changed += FireChangedEvent;
		_minAfterPickupSpawnDelay.Changed += FireChangedEvent;
		_maxAfterPickupSpawnDelay.Changed += FireChangedEvent;
		_spawnAttemptDelayDecrease.Changed += FireChangedEvent;
		_maxInstances.Changed += FireChangedEvent;
		_spawnMode.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GlyphSettings source = _source as GlyphSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GlyphSettings" );
		minNormalSpawnDelay = source.minNormalSpawnDelay;
		maxNormalSpawnDelay = source.maxNormalSpawnDelay;
		minAfterPickupSpawnDelay = source.minAfterPickupSpawnDelay;
		maxAfterPickupSpawnDelay = source.maxAfterPickupSpawnDelay;
		spawnAttemptDelayDecrease = source.spawnAttemptDelayDecrease;
		maxInstances = source.maxInstances;
		spawnMode = source.spawnMode;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GlyphSettings newParent = _newParent as GlyphSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minNormalSpawnDelay.SetParent( newParent == null ? null : newParent._minNormalSpawnDelay );
		_maxNormalSpawnDelay.SetParent( newParent == null ? null : newParent._maxNormalSpawnDelay );
		_minAfterPickupSpawnDelay.SetParent( newParent == null ? null : newParent._minAfterPickupSpawnDelay );
		_maxAfterPickupSpawnDelay.SetParent( newParent == null ? null : newParent._maxAfterPickupSpawnDelay );
		_spawnAttemptDelayDecrease.SetParent( newParent == null ? null : newParent._spawnAttemptDelayDecrease );
		_maxInstances.SetParent( newParent == null ? null : newParent._maxInstances );
		_spawnMode.SetParent( newParent == null ? null : newParent._spawnMode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minNormalSpawnDelay.Reset();
		_maxNormalSpawnDelay.Reset();
		_minAfterPickupSpawnDelay.Reset();
		_maxAfterPickupSpawnDelay.Reset();
		_spawnAttemptDelayDecrease.Reset();
		_maxInstances.Reset();
		_spawnMode.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minNormalSpawnDelay.IsDerivedFromParent()
			&& _maxNormalSpawnDelay.IsDerivedFromParent()
			&& _minAfterPickupSpawnDelay.IsDerivedFromParent()
			&& _maxAfterPickupSpawnDelay.IsDerivedFromParent()
			&& _spawnAttemptDelayDecrease.IsDerivedFromParent()
			&& _maxInstances.IsDerivedFromParent()
			&& _spawnMode.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minNormalSpawnDelay" )
			_minNormalSpawnDelay.Reset();
		else if ( fieldName == "maxNormalSpawnDelay" )
			_maxNormalSpawnDelay.Reset();
		else if ( fieldName == "minAfterPickupSpawnDelay" )
			_minAfterPickupSpawnDelay.Reset();
		else if ( fieldName == "maxAfterPickupSpawnDelay" )
			_maxAfterPickupSpawnDelay.Reset();
		else if ( fieldName == "spawnAttemptDelayDecrease" )
			_spawnAttemptDelayDecrease.Reset();
		else if ( fieldName == "maxInstances" )
			_maxInstances.Reset();
		else if ( fieldName == "spawnMode" )
			_spawnMode.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minNormalSpawnDelay" )
			return _minNormalSpawnDelay.IsDerivedFromParent();
		if ( fieldName == "maxNormalSpawnDelay" )
			return _maxNormalSpawnDelay.IsDerivedFromParent();
		if ( fieldName == "minAfterPickupSpawnDelay" )
			return _minAfterPickupSpawnDelay.IsDerivedFromParent();
		if ( fieldName == "maxAfterPickupSpawnDelay" )
			return _maxAfterPickupSpawnDelay.IsDerivedFromParent();
		if ( fieldName == "spawnAttemptDelayDecrease" )
			return _spawnAttemptDelayDecrease.IsDerivedFromParent();
		if ( fieldName == "maxInstances" )
			return _maxInstances.IsDerivedFromParent();
		if ( fieldName == "spawnMode" )
			return _spawnMode.IsDerivedFromParent();
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

public class HeroStatisticsParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroStatisticsParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _timeSlicePeriod;

	public float timeSlicePeriod { get { return _timeSlicePeriod.Get(); } set { _timeSlicePeriod.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_timeSlicePeriod = new UndoRedo<float>( owner, 60.0f );
		_timeSlicePeriod.Changed += FireChangedEvent;
	}

	public HeroStatisticsParams()
	{
		Initialize( GetOwner() );
	}

	public HeroStatisticsParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroStatisticsParams( DBResource owner, HeroStatisticsParams source )
		: this(owner, source, true){}

	protected HeroStatisticsParams( DBResource owner, HeroStatisticsParams source, bool fireEvent )
	{
		_timeSlicePeriod = new UndoRedo<float>( owner, source.timeSlicePeriod );
		_timeSlicePeriod.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroStatisticsParams source = _source as HeroStatisticsParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroStatisticsParams" );
		timeSlicePeriod = source.timeSlicePeriod;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroStatisticsParams newParent = _newParent as HeroStatisticsParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_timeSlicePeriod.SetParent( newParent == null ? null : newParent._timeSlicePeriod );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_timeSlicePeriod.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_timeSlicePeriod.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "timeSlicePeriod" )
			_timeSlicePeriod.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "timeSlicePeriod" )
			return _timeSlicePeriod.IsDerivedFromParent();
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

public class KillTimeIntervals : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private KillTimeIntervals __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _creepKillInterval;
	private UndoRedo<float> _buildingKillInterval;
	private UndoRedo<float> _heroKillerDeadInterval;
	private UndoRedo<float> _heroKillDamageInterval;

	public float creepKillInterval { get { return _creepKillInterval.Get(); } set { _creepKillInterval.Set( value ); } }

	public float buildingKillInterval { get { return _buildingKillInterval.Get(); } set { _buildingKillInterval.Set( value ); } }

	public float heroKillerDeadInterval { get { return _heroKillerDeadInterval.Get(); } set { _heroKillerDeadInterval.Set( value ); } }

	public float heroKillDamageInterval { get { return _heroKillDamageInterval.Get(); } set { _heroKillDamageInterval.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_creepKillInterval = new UndoRedo<float>( owner, 0.5f );
		_buildingKillInterval = new UndoRedo<float>( owner, 2.0f );
		_heroKillerDeadInterval = new UndoRedo<float>( owner, 5.0f );
		_heroKillDamageInterval = new UndoRedo<float>( owner, 10.0f );
		_creepKillInterval.Changed += FireChangedEvent;
		_buildingKillInterval.Changed += FireChangedEvent;
		_heroKillerDeadInterval.Changed += FireChangedEvent;
		_heroKillDamageInterval.Changed += FireChangedEvent;
	}

	public KillTimeIntervals()
	{
		Initialize( GetOwner() );
	}

	public KillTimeIntervals( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public KillTimeIntervals( DBResource owner, KillTimeIntervals source )
		: this(owner, source, true){}

	protected KillTimeIntervals( DBResource owner, KillTimeIntervals source, bool fireEvent )
	{
		_creepKillInterval = new UndoRedo<float>( owner, source.creepKillInterval );
		_buildingKillInterval = new UndoRedo<float>( owner, source.buildingKillInterval );
		_heroKillerDeadInterval = new UndoRedo<float>( owner, source.heroKillerDeadInterval );
		_heroKillDamageInterval = new UndoRedo<float>( owner, source.heroKillDamageInterval );
		_creepKillInterval.Changed += FireChangedEvent;
		_buildingKillInterval.Changed += FireChangedEvent;
		_heroKillerDeadInterval.Changed += FireChangedEvent;
		_heroKillDamageInterval.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		KillTimeIntervals source = _source as KillTimeIntervals;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for KillTimeIntervals" );
		creepKillInterval = source.creepKillInterval;
		buildingKillInterval = source.buildingKillInterval;
		heroKillerDeadInterval = source.heroKillerDeadInterval;
		heroKillDamageInterval = source.heroKillDamageInterval;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		KillTimeIntervals newParent = _newParent as KillTimeIntervals;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_creepKillInterval.SetParent( newParent == null ? null : newParent._creepKillInterval );
		_buildingKillInterval.SetParent( newParent == null ? null : newParent._buildingKillInterval );
		_heroKillerDeadInterval.SetParent( newParent == null ? null : newParent._heroKillerDeadInterval );
		_heroKillDamageInterval.SetParent( newParent == null ? null : newParent._heroKillDamageInterval );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_creepKillInterval.Reset();
		_buildingKillInterval.Reset();
		_heroKillerDeadInterval.Reset();
		_heroKillDamageInterval.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_creepKillInterval.IsDerivedFromParent()
			&& _buildingKillInterval.IsDerivedFromParent()
			&& _heroKillerDeadInterval.IsDerivedFromParent()
			&& _heroKillDamageInterval.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "creepKillInterval" )
			_creepKillInterval.Reset();
		else if ( fieldName == "buildingKillInterval" )
			_buildingKillInterval.Reset();
		else if ( fieldName == "heroKillerDeadInterval" )
			_heroKillerDeadInterval.Reset();
		else if ( fieldName == "heroKillDamageInterval" )
			_heroKillDamageInterval.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "creepKillInterval" )
			return _creepKillInterval.IsDerivedFromParent();
		if ( fieldName == "buildingKillInterval" )
			return _buildingKillInterval.IsDerivedFromParent();
		if ( fieldName == "heroKillerDeadInterval" )
			return _heroKillerDeadInterval.IsDerivedFromParent();
		if ( fieldName == "heroKillDamageInterval" )
			return _heroKillDamageInterval.IsDerivedFromParent();
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

public class OvertimeRespawnParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private OvertimeRespawnParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _overtime;
	private UndoRedo<float> _respawnDelayForOvertime;

	[Description( "Session overtime (in minutes), after which hero respawn time will increase" )]
	public float overtime { get { return _overtime.Get(); } set { _overtime.Set( value ); } }

	[Description( "Hero respawn delay for each minute of overtime (in seconds)" )]
	public float respawnDelayForOvertime { get { return _respawnDelayForOvertime.Get(); } set { _respawnDelayForOvertime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_overtime = new UndoRedo<float>( owner, 25.0f );
		_respawnDelayForOvertime = new UndoRedo<float>( owner, 1.5f );
		_overtime.Changed += FireChangedEvent;
		_respawnDelayForOvertime.Changed += FireChangedEvent;
	}

	public OvertimeRespawnParams()
	{
		Initialize( GetOwner() );
	}

	public OvertimeRespawnParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public OvertimeRespawnParams( DBResource owner, OvertimeRespawnParams source )
		: this(owner, source, true){}

	protected OvertimeRespawnParams( DBResource owner, OvertimeRespawnParams source, bool fireEvent )
	{
		_overtime = new UndoRedo<float>( owner, source.overtime );
		_respawnDelayForOvertime = new UndoRedo<float>( owner, source.respawnDelayForOvertime );
		_overtime.Changed += FireChangedEvent;
		_respawnDelayForOvertime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		OvertimeRespawnParams source = _source as OvertimeRespawnParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OvertimeRespawnParams" );
		overtime = source.overtime;
		respawnDelayForOvertime = source.respawnDelayForOvertime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		OvertimeRespawnParams newParent = _newParent as OvertimeRespawnParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_overtime.SetParent( newParent == null ? null : newParent._overtime );
		_respawnDelayForOvertime.SetParent( newParent == null ? null : newParent._respawnDelayForOvertime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_overtime.Reset();
		_respawnDelayForOvertime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_overtime.IsDerivedFromParent()
			&& _respawnDelayForOvertime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "overtime" )
			_overtime.Reset();
		else if ( fieldName == "respawnDelayForOvertime" )
			_respawnDelayForOvertime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "overtime" )
			return _overtime.IsDerivedFromParent();
		if ( fieldName == "respawnDelayForOvertime" )
			return _respawnDelayForOvertime.IsDerivedFromParent();
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

[IndexField("caption")]
public class TalentGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _caption;
	private TextRef _name;
	private TextRef _description;
	private UndoRedo<float> _cooldown;
	private UndoRedoAssignableList<DBPtr<Talent>> _talents;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public float cooldown { get { return _cooldown.Get(); } set { _cooldown.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Talent>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_caption = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_cooldown = new UndoRedo<float>( owner, 15.0f );
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
	}

	public TalentGroup()
	{
		Initialize( GetOwner() );
	}

	public TalentGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentGroup( DBResource owner, TalentGroup source )
		: this(owner, source, true){}

	protected TalentGroup( DBResource owner, TalentGroup source, bool fireEvent )
	{
		_caption = new UndoRedo<string>( owner, source.caption );
		_name = new TextRef( owner, source.name );
		_description = new TextRef( owner, source.description );
		_cooldown = new UndoRedo<float>( owner, source.cooldown );
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_talents.Assign( source.talents );
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentGroup source = _source as TalentGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentGroup" );
		caption = source.caption;
		name = source.name;
		description = source.description;
		cooldown = source.cooldown;
		talents = source.talents;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentGroup newParent = _newParent as TalentGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_cooldown.SetParent( newParent == null ? null : newParent._cooldown );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_caption.Reset();
		_name.Reset();
		_description.Reset();
		_cooldown.Reset();
		_talents.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _cooldown.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "cooldown" )
			_cooldown.Reset();
		else if ( fieldName == "talents" )
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
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "cooldown" )
			return _cooldown.IsDerivedFromParent();
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

[DBVersion(1)]
public class TeamColors : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TeamColors __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<HDRColor> _teamColors;

	[EnumArray(typeof(ETeamColorID))]
	public libdb.IChangeableList<HDRColor> teamColors { get { return _teamColors; } set { _teamColors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_teamColors = new UndoRedoAssignableList<HDRColor>( owner, typeof( ETeamColorID ) );
		_teamColors.Changed += FireChangedEvent;
	}

	public TeamColors()
	{
		Initialize( GetOwner() );
	}

	public TeamColors( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TeamColors( DBResource owner, TeamColors source )
		: this(owner, source, true){}

	protected TeamColors( DBResource owner, TeamColors source, bool fireEvent )
	{
		_teamColors = new UndoRedoAssignableList<HDRColor>( owner, typeof( ETeamColorID ) );
		_teamColors.Assign( source.teamColors );
		_teamColors.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TeamColors source = _source as TeamColors;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TeamColors" );
		teamColors = source.teamColors;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TeamColors newParent = _newParent as TeamColors;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_teamColors.SetParent( newParent == null ? null : newParent._teamColors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_teamColors.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_teamColors.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "teamColors" )
			_teamColors.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "teamColors" )
			return _teamColors.IsDerivedFromParent();
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

public class TurretParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TurretParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _turretAngleSpeed;
	private UndoRedo<float> _turretAngleAcceleration;
	private UndoRedo<float> _turretRotaionTolerance;
	private UndoRedo<float> _turretLastAngleResetDelay;

	[Description( "Turret turn speed (angles per second)" )]
	public float turretAngleSpeed { get { return _turretAngleSpeed.Get(); } set { _turretAngleSpeed.Set( value ); } }

	[Description( "Turret acceleration (angles per squared second)" )]
	public float turretAngleAcceleration { get { return _turretAngleAcceleration.Get(); } set { _turretAngleAcceleration.Set( value ); } }

	[Description( "Turret rotation tolerance (angles)" )]
	[FloatMinMax(0, 360)]
	public float turretRotaionTolerance { get { return _turretRotaionTolerance.Get(); } set { _turretRotaionTolerance.Set( value ); } }

	public float turretLastAngleResetDelay { get { return _turretLastAngleResetDelay.Get(); } set { _turretLastAngleResetDelay.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_turretAngleSpeed = new UndoRedo<float>( owner, 100.0f );
		_turretAngleAcceleration = new UndoRedo<float>( owner, 25.0f );
		_turretRotaionTolerance = new UndoRedo<float>( owner, 5.0f );
		_turretLastAngleResetDelay = new UndoRedo<float>( owner, 2.0f );
		_turretAngleSpeed.Changed += FireChangedEvent;
		_turretAngleAcceleration.Changed += FireChangedEvent;
		_turretRotaionTolerance.Changed += FireChangedEvent;
		_turretLastAngleResetDelay.Changed += FireChangedEvent;
	}

	public TurretParams()
	{
		Initialize( GetOwner() );
	}

	public TurretParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TurretParams( DBResource owner, TurretParams source )
		: this(owner, source, true){}

	protected TurretParams( DBResource owner, TurretParams source, bool fireEvent )
	{
		_turretAngleSpeed = new UndoRedo<float>( owner, source.turretAngleSpeed );
		_turretAngleAcceleration = new UndoRedo<float>( owner, source.turretAngleAcceleration );
		_turretRotaionTolerance = new UndoRedo<float>( owner, source.turretRotaionTolerance );
		_turretLastAngleResetDelay = new UndoRedo<float>( owner, source.turretLastAngleResetDelay );
		_turretAngleSpeed.Changed += FireChangedEvent;
		_turretAngleAcceleration.Changed += FireChangedEvent;
		_turretRotaionTolerance.Changed += FireChangedEvent;
		_turretLastAngleResetDelay.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TurretParams source = _source as TurretParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TurretParams" );
		turretAngleSpeed = source.turretAngleSpeed;
		turretAngleAcceleration = source.turretAngleAcceleration;
		turretRotaionTolerance = source.turretRotaionTolerance;
		turretLastAngleResetDelay = source.turretLastAngleResetDelay;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TurretParams newParent = _newParent as TurretParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_turretAngleSpeed.SetParent( newParent == null ? null : newParent._turretAngleSpeed );
		_turretAngleAcceleration.SetParent( newParent == null ? null : newParent._turretAngleAcceleration );
		_turretRotaionTolerance.SetParent( newParent == null ? null : newParent._turretRotaionTolerance );
		_turretLastAngleResetDelay.SetParent( newParent == null ? null : newParent._turretLastAngleResetDelay );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_turretAngleSpeed.Reset();
		_turretAngleAcceleration.Reset();
		_turretRotaionTolerance.Reset();
		_turretLastAngleResetDelay.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_turretAngleSpeed.IsDerivedFromParent()
			&& _turretAngleAcceleration.IsDerivedFromParent()
			&& _turretRotaionTolerance.IsDerivedFromParent()
			&& _turretLastAngleResetDelay.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "turretAngleSpeed" )
			_turretAngleSpeed.Reset();
		else if ( fieldName == "turretAngleAcceleration" )
			_turretAngleAcceleration.Reset();
		else if ( fieldName == "turretRotaionTolerance" )
			_turretRotaionTolerance.Reset();
		else if ( fieldName == "turretLastAngleResetDelay" )
			_turretLastAngleResetDelay.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "turretAngleSpeed" )
			return _turretAngleSpeed.IsDerivedFromParent();
		if ( fieldName == "turretAngleAcceleration" )
			return _turretAngleAcceleration.IsDerivedFromParent();
		if ( fieldName == "turretRotaionTolerance" )
			return _turretRotaionTolerance.IsDerivedFromParent();
		if ( fieldName == "turretLastAngleResetDelay" )
			return _turretLastAngleResetDelay.IsDerivedFromParent();
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

[DBVersion(9)]
[UseTypeName("AILP")]
public class AILogicParameters : DBResource
{
	private UndoRedoDBPtr<AILogicParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<AILogicParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TextRef> _teamsNames;
	private UndoRedoDBPtr<SingleStateObject> _chestGameObject;
	private UndoRedoAssignableList<DBPtr<ConditionFormula>> _conditionFormulas;
	private UndoRedoDBPtr<UnitConstantsContainer> _globalConstants;
	private UndoRedoDBPtr<HeroRespawnParams> _heroRespawnParams;
	private UndoRedo<float> _heroAdvanceRespawnTime;
	private UndoRedo<float> _baseRedeemCost;
	private UndoRedo<float> _redeemCostPerLevel;
	private UndoRedo<float> _redeemCostrecalculateTime;
	private UndoRedo<float> _followRange;
	private UndoRedo<float> _pickupItemRange;
	private UndoRedo<float> _killAwardPartyMultiplier;
	private UndoRedo<float> _maxTrueSightRange;
	private UndoRedo<float> _channelingAbilityRangeMultiplier;
	private UndoRedo<float> _heroScreamDelay;
	private UndoRedo<float> _globalCooldownTime;
	private UndoRedo<float> _skeletonLifeTime;
	private GlyphSettings _glyphSettings;
	private UndoRedo<float> _assistAccountTime;
	private KillTimeIntervals _killTimeIntervals;
	private UndoRedo<int> _creepsWavesDelay;
	private UndoRedo<int> _creepLevelCap;
	private CreepsLevelUpInfo _creepsLevelUpInfo;
	private UndoRedoList<float> _quarterDestroyStatsMultipliers;
	private UndoRedo<float> _movingTimerBlock;
	private CreatureHappyStateParams _creatureHappyStateParams;
	private CommonSummonParameters _commonSummonParameters;
	private UndoRedo<float> _rotationSpeed;
	private UndoRedo<float> _rotationSpeedZ;
	private TurretParams _towerTurretParams;
	private UndoRedoAssignableList<TurretParams> _mainBuildingTurretParams;
	private UndoRedo<int> _expandNatureSegmentRation;
	private UndoRedo<float> _expandNatureGlyphsLifeTime;
	private UndoRedo<float> _expandNatureGlyphsVisibilityRadius;
	private UndoRedoDBPtr<GameObject> _expandNatureGlyphGameObject;
	private UndoRedoDBPtr<Ability> _buildingsDenyAbility;
	private UndoRedo<float> _buildingsDenyMinHealth;
	private UndoRedo<float> _buildingsDenyExperiencePenalty;
	private UndoRedo<float> _buildingsDenyNaftaPenalty;
	private UndoRedo<float> _buildingsDenyNaftaSpecPenalty;
	private UndoRedo<float> _buildingsDenyTeamNaftaPenalty;
	private UndoRedoDBPtr<Ability> _buildingsAbilityA;
	private UndoRedoDBPtr<Ability> _buildingsAbilityB;
	private UndoRedo<float> _buildingsMinHealthExplosionPercent;
	private UndoRedo<float> _buildingsFragEffectProbability;
	private UndoRedoDBPtr<Ability> _raiseFlagAbility;
	private UndoRedo<float> _talentsBuyRange;
	private UndoRedoDBPtr<TalentsSet> _defaultTalentsSet;
	private UndoRedo<float> _talentBaseStatBudget;
	private UndoRedoList<int> _talentNaftaCostByLevel;
	private UndoRedoList<int> _talentVendorCostByRarity;
	private UndoRedo<float> _pauseSeconds;
	private UndoRedoDBPtr<DerivativeStatsContainer> _derivativeStats;
	private UndoRedoDBPtr<StatsBudgetContainer> _statsBudget;
	private UndoRedoDBPtr<ForceParameters> _forceParameters;
	private UndoRedoDBPtr<TalentGroupList> _talentGroups;
	private UndoRedoDBPtr<ConsumableGroupList> _consumableGroups;
	private UndoRedoDBPtr<TalentKitList> _talentKits;
	private UndoRedoDBPtr<TalentPackList> _talentPacks;
	private ExecutableFloatString _energyDamageReduction;
	private ExecutableFloatString _physicalDamageReduction;
	private HeroStatisticsParams _heroStatisticsParams;
	private ExpoModeParams _expoModeParams;
	private AbilityAndDamageScalingParams _abilityAndDamageScalingParams;
	private UndoRedoDBPtr<DBLevelToExperience> _levelToExperienceTable;
	private UndoRedoDBPtr<BotsSettings> _botsSettings;
	private UndoRedo<float> _warFogRemoveTime;
	private UndoRedo<float> _warFogRemoveRadius;
	private UndoRedo<int> _maxCreepsCount;
	private UndoRedoDBPtr<Talent> _portal;
	private UndoRedoDBPtr<HeroRanks> _heroRanks;
	private UndoRedo<int> _baseEmblemHeroNeeds;
	private UndoRedoDBPtr<BehaviourTrackerParams> _behaviourTrackerParams;

	[Category( "Misc" )]
	[EnumArray(typeof(EFaction))]
	public libdb.IChangeableList<TextRef> teamsNames { get { return _teamsNames; } set { _teamsNames.Assign( value ); } }

	[Category( "Misc" )]
	[Description( "Game object, used for chests with artifact" )]
	public DBPtr<SingleStateObject> chestGameObject { get { return _chestGameObject.Get(); } set { _chestGameObject.Set( value ); } }

	[Category( "Misc" )]
	[Custom("Social")]
	public libdb.IChangeableList<DBPtr<ConditionFormula>> conditionFormulas { get { return _conditionFormulas; } set { _conditionFormulas.Assign( value ); } }

	[Category( "Misc" )]
	[Custom("Social")]
	public DBPtr<UnitConstantsContainer> globalConstants { get { return _globalConstants.Get(); } set { _globalConstants.Set( value ); } }

	[Category( "Heroes" )]
	public DBPtr<HeroRespawnParams> heroRespawnParams { get { return _heroRespawnParams.Get(); } set { _heroRespawnParams.Set( value ); } }

	[Description( "Время на проигрывание анимации воскрешения. Используется в формуле вычисления задержки respawnDelay = level * heroRespawnDelayMultiplier * reviveTimeScale - heroAdvanceRespawnTime" )]
	public float heroAdvanceRespawnTime { get { return _heroAdvanceRespawnTime.Get(); } set { _heroAdvanceRespawnTime.Set( value ); } }

	[Category( "Heroes" )]
	public float baseRedeemCost { get { return _baseRedeemCost.Get(); } set { _baseRedeemCost.Set( value ); } }

	[Category( "Heroes" )]
	public float redeemCostPerLevel { get { return _redeemCostPerLevel.Get(); } set { _redeemCostPerLevel.Set( value ); } }

	[Category( "Heroes" )]
	public float redeemCostrecalculateTime { get { return _redeemCostrecalculateTime.Get(); } set { _redeemCostrecalculateTime.Set( value ); } }

	[Category( "Heroes" )]
	public float followRange { get { return _followRange.Get(); } set { _followRange.Set( value ); } }

	[Category( "Heroes" )]
	public float pickupItemRange { get { return _pickupItemRange.Get(); } set { _pickupItemRange.Set( value ); } }

	[Category( "Heroes" )]
	public float killAwardPartyMultiplier { get { return _killAwardPartyMultiplier.Get(); } set { _killAwardPartyMultiplier.Set( value ); } }

	[Category( "Heroes" )]
	public float maxTrueSightRange { get { return _maxTrueSightRange.Get(); } set { _maxTrueSightRange.Set( value ); } }

	[Description( "Range to target check for channeling applicator uses this multiplier" )]
	public float channelingAbilityRangeMultiplier { get { return _channelingAbilityRangeMultiplier.Get(); } set { _channelingAbilityRangeMultiplier.Set( value ); } }

	[Category( "Logic" )]
	public float heroScreamDelay { get { return _heroScreamDelay.Get(); } set { _heroScreamDelay.Set( value ); } }

	[Category( "Logic" )]
	[Description( "Global cooldown time for all abilities" )]
	public float globalCooldownTime { get { return _globalCooldownTime.Get(); } set { _globalCooldownTime.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Life time in seconds of skeleton (for moving unit only)" )]
	public float skeletonLifeTime { get { return _skeletonLifeTime.Get(); } set { _skeletonLifeTime.Set( value ); } }

	[Category( "Logic" )]
	public GlyphSettings glyphSettings { get { return _glyphSettings; } set { _glyphSettings.Assign( value ); } }

	[Category( "Statistics" )]
	[Description( "Within this time assist actions will be accounted while evaluating assistants" )]
	public float assistAccountTime { get { return _assistAccountTime.Get(); } set { _assistAccountTime.Set( value ); } }

	[Description( "Time intervals settings for kills counting" )]
	public KillTimeIntervals killTimeIntervals { get { return _killTimeIntervals; } set { _killTimeIntervals.Assign( value ); } }

	[Category( "Creeps" )]
	public int creepsWavesDelay { get { return _creepsWavesDelay.Get(); } set { _creepsWavesDelay.Set( value ); } }

	[Category( "Creeps" )]
	public int creepLevelCap { get { return _creepLevelCap.Get(); } set { _creepLevelCap.Set( value ); } }

	[Category( "Creeps" )]
	public CreepsLevelUpInfo creepsLevelUpInfo { get { return _creepsLevelUpInfo; } set { _creepsLevelUpInfo.Assign( value ); } }

	[Category( "Creeps" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> quarterDestroyStatsMultipliers { get { return _quarterDestroyStatsMultipliers; } set { _quarterDestroyStatsMultipliers.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Время, по исченеии которого крип телепортируется на спавнер, если он застрял где-то" )]
	public float movingTimerBlock { get { return _movingTimerBlock.Get(); } set { _movingTimerBlock.Set( value ); } }

	[Category( "Units" )]
	public CreatureHappyStateParams creatureHappyStateParams { get { return _creatureHappyStateParams; } set { _creatureHappyStateParams.Assign( value ); } }

	public CommonSummonParameters commonSummonParameters { get { return _commonSummonParameters; } set { _commonSummonParameters.Assign( value ); } }

	[Category( "Units" )]
	[Description( "Unit rotation speed (degrees per second) " )]
	public float rotationSpeed { get { return _rotationSpeed.Get(); } set { _rotationSpeed.Set( value ); } }

	[Category( "Units" )]
	[Description( "Unit vertical rotation speed (degrees per second) " )]
	public float rotationSpeedZ { get { return _rotationSpeedZ.Get(); } set { _rotationSpeedZ.Set( value ); } }

	public TurretParams towerTurretParams { get { return _towerTurretParams; } set { _towerTurretParams.Assign( value ); } }

	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<TurretParams> mainBuildingTurretParams { get { return _mainBuildingTurretParams; } set { _mainBuildingTurretParams.Assign( value ); } }

	[Category( "Expand Nature" )]
	public int expandNatureSegmentRation { get { return _expandNatureSegmentRation.Get(); } set { _expandNatureSegmentRation.Set( value ); } }

	[Category( "Expand Nature" )]
	public float expandNatureGlyphsLifeTime { get { return _expandNatureGlyphsLifeTime.Get(); } set { _expandNatureGlyphsLifeTime.Set( value ); } }

	[Category( "Expand Nature" )]
	public float expandNatureGlyphsVisibilityRadius { get { return _expandNatureGlyphsVisibilityRadius.Get(); } set { _expandNatureGlyphsVisibilityRadius.Set( value ); } }

	[Category( "Expand Nature" )]
	public DBPtr<GameObject> expandNatureGlyphGameObject { get { return _expandNatureGlyphGameObject.Get(); } set { _expandNatureGlyphGameObject.Set( value ); } }

	[Category( "Buildings deny" )]
	public DBPtr<Ability> buildingsDenyAbility { get { return _buildingsDenyAbility.Get(); } set { _buildingsDenyAbility.Set( value ); } }

	[Category( "Buildings deny" )]
	public float buildingsDenyMinHealth { get { return _buildingsDenyMinHealth.Get(); } set { _buildingsDenyMinHealth.Set( value ); } }

	[Category( "Buildings deny" )]
	[Description( "Penalty of experience, given from tower if denied (in percents)" )]
	public float buildingsDenyExperiencePenalty { get { return _buildingsDenyExperiencePenalty.Get(); } set { _buildingsDenyExperiencePenalty.Set( value ); } }

	[Category( "Buildings deny" )]
	[Description( "Penalty of nafta, given from tower if denied (in percents)" )]
	public float buildingsDenyNaftaPenalty { get { return _buildingsDenyNaftaPenalty.Get(); } set { _buildingsDenyNaftaPenalty.Set( value ); } }

	[Category( "Buildings deny" )]
	[Description( "Penalty of nafta, given from tower if denied (in percents)" )]
	public float buildingsDenyNaftaSpecPenalty { get { return _buildingsDenyNaftaSpecPenalty.Get(); } set { _buildingsDenyNaftaSpecPenalty.Set( value ); } }

	[Category( "Buildings deny" )]
	[Description( "Penalty of team nafta, given from tower if denied (in percents)" )]
	public float buildingsDenyTeamNaftaPenalty { get { return _buildingsDenyTeamNaftaPenalty.Get(); } set { _buildingsDenyTeamNaftaPenalty.Set( value ); } }

	[Category( "Buildings" )]
	public DBPtr<Ability> buildingsAbilityA { get { return _buildingsAbilityA.Get(); } set { _buildingsAbilityA.Set( value ); } }

	[Category( "Buildings" )]
	public DBPtr<Ability> buildingsAbilityB { get { return _buildingsAbilityB.Get(); } set { _buildingsAbilityB.Set( value ); } }

	[Category( "Buildings" )]
	public float buildingsMinHealthExplosionPercent { get { return _buildingsMinHealthExplosionPercent.Get(); } set { _buildingsMinHealthExplosionPercent.Set( value ); } }

	[Category( "Buildings" )]
	public float buildingsFragEffectProbability { get { return _buildingsFragEffectProbability.Get(); } set { _buildingsFragEffectProbability.Set( value ); } }

	[Category( "Buildings" )]
	[Description( "Raise a flag ability" )]
	public DBPtr<Ability> raiseFlagAbility { get { return _raiseFlagAbility.Get(); } set { _raiseFlagAbility.Set( value ); } }

	[Category( "Talents" )]
	[Description( "Max range from shop, then male hero can to activate talents" )]
	public float talentsBuyRange { get { return _talentsBuyRange.Get(); } set { _talentsBuyRange.Set( value ); } }

	[Category( "Talents" )]
	public DBPtr<TalentsSet> defaultTalentsSet { get { return _defaultTalentsSet.Get(); } set { _defaultTalentsSet.Set( value ); } }

	[Category( "Talents" )]
	[Custom("Social")]
	public float talentBaseStatBudget { get { return _talentBaseStatBudget.Get(); } set { _talentBaseStatBudget.Set( value ); } }

	[Category( "Talents" )]
	[Custom("Social")]
	[Description( "Базовая стоимость от уровня" )]
	[EnumArray(typeof(ETalentLevel))]
	public libdb.IChangeableList<int> talentNaftaCostByLevel { get { return _talentNaftaCostByLevel; } set { _talentNaftaCostByLevel.Assign( value ); } }

	[Category( "Talents" )]
	[Custom("DBServer")]
	[Description( "Ценность таланта при выдаче" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<int> talentVendorCostByRarity { get { return _talentVendorCostByRarity; } set { _talentVendorCostByRarity.Assign( value ); } }

	[Category( "Interface" )]
	[Description( "Time for pause in seconds" )]
	public float pauseSeconds { get { return _pauseSeconds.Get(); } set { _pauseSeconds.Set( value ); } }

	[Category( "Derivate Stats" )]
	[Custom("Social")]
	public DBPtr<DerivativeStatsContainer> derivativeStats { get { return _derivativeStats.Get(); } set { _derivativeStats.Set( value ); } }

	public DBPtr<StatsBudgetContainer> statsBudget { get { return _statsBudget.Get(); } set { _statsBudget.Set( value ); } }

	[Custom("Social")]
	public DBPtr<ForceParameters> forceParameters { get { return _forceParameters.Get(); } set { _forceParameters.Set( value ); } }

	public DBPtr<TalentGroupList> talentGroups { get { return _talentGroups.Get(); } set { _talentGroups.Set( value ); } }

	public DBPtr<ConsumableGroupList> consumableGroups { get { return _consumableGroups.Get(); } set { _consumableGroups.Set( value ); } }

	[Custom("Social")]
	public DBPtr<TalentKitList> talentKits { get { return _talentKits.Get(); } set { _talentKits.Set( value ); } }

	[Custom("Social")]
	public DBPtr<TalentPackList> talentPacks { get { return _talentPacks.Get(); } set { _talentPacks.Set( value ); } }

	[Description( "Energy damage reduction formula" )]
	public ExecutableFloatString energyDamageReduction { get { return _energyDamageReduction; } set { _energyDamageReduction.Assign( value ); } }

	[Description( "Physical damage reduction formula" )]
	public ExecutableFloatString physicalDamageReduction { get { return _physicalDamageReduction; } set { _physicalDamageReduction.Assign( value ); } }

	public HeroStatisticsParams heroStatisticsParams { get { return _heroStatisticsParams; } set { _heroStatisticsParams.Assign( value ); } }

	public ExpoModeParams expoModeParams { get { return _expoModeParams; } set { _expoModeParams.Assign( value ); } }

	public AbilityAndDamageScalingParams abilityAndDamageScalingParams { get { return _abilityAndDamageScalingParams; } set { _abilityAndDamageScalingParams.Assign( value ); } }

	[Description( "таблица показывающая скольо нужно экспы герою чтобы достичь левела в замке" )]
	public DBPtr<DBLevelToExperience> levelToExperienceTable { get { return _levelToExperienceTable.Get(); } set { _levelToExperienceTable.Set( value ); } }

	public DBPtr<BotsSettings> botsSettings { get { return _botsSettings.Get(); } set { _botsSettings.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines default time for removing WarFog around attacker after dispatch delivery to target (seconds)." )]
	public float warFogRemoveTime { get { return _warFogRemoveTime.Get(); } set { _warFogRemoveTime.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines default radius for removing WarFog around attacker after dispatch delivery to target (meters)." )]
	public float warFogRemoveRadius { get { return _warFogRemoveRadius.Get(); } set { _warFogRemoveRadius.Set( value ); } }

	[Category( "MaxCreepsCount" )]
	[Description( "Defines a maximum number of creeps that can be on map at the same time." )]
	public int maxCreepsCount { get { return _maxCreepsCount.Get(); } set { _maxCreepsCount.Set( value ); } }

	public DBPtr<Talent> portal { get { return _portal.Get(); } set { _portal.Set( value ); } }

	[Custom("DBServer", "Social")]
	public DBPtr<HeroRanks> heroRanks { get { return _heroRanks.Get(); } set { _heroRanks.Set( value ); } }

	[Description( "При скольки героях одного клана на поднятых флагах рисуется эмблема клана" )]
	public int baseEmblemHeroNeeds { get { return _baseEmblemHeroNeeds.Get(); } set { _baseEmblemHeroNeeds.Set( value ); } }

	public DBPtr<BehaviourTrackerParams> behaviourTrackerParams { get { return _behaviourTrackerParams.Get(); } set { _behaviourTrackerParams.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AILogicParameters>(owner);
		_teamsNames = new UndoRedoAssignableList<TextRef>( owner, typeof( EFaction ) );
		_chestGameObject = new UndoRedoDBPtr<SingleStateObject>( owner );
		_conditionFormulas = new UndoRedoAssignableList<DBPtr<ConditionFormula>>( owner );
		_globalConstants = new UndoRedoDBPtr<UnitConstantsContainer>( owner );
		_heroRespawnParams = new UndoRedoDBPtr<HeroRespawnParams>( owner );
		_heroAdvanceRespawnTime = new UndoRedo<float>( owner, 1.0f );
		_baseRedeemCost = new UndoRedo<float>( owner, 100.0f );
		_redeemCostPerLevel = new UndoRedo<float>( owner, 10.0f );
		_redeemCostrecalculateTime = new UndoRedo<float>( owner, 3.0f );
		_followRange = new UndoRedo<float>( owner, 4.0f );
		_pickupItemRange = new UndoRedo<float>( owner, 2.0f );
		_killAwardPartyMultiplier = new UndoRedo<float>( owner, 1.0f );
		_maxTrueSightRange = new UndoRedo<float>( owner, 15.0f );
		_channelingAbilityRangeMultiplier = new UndoRedo<float>( owner, 1.2f );
		_heroScreamDelay = new UndoRedo<float>( owner, 3.0f );
		_globalCooldownTime = new UndoRedo<float>( owner, 1.0f );
		_skeletonLifeTime = new UndoRedo<float>( owner, 10.0f );
		_glyphSettings = new GlyphSettings( owner );
		_assistAccountTime = new UndoRedo<float>( owner, 30.0f );
		_killTimeIntervals = new KillTimeIntervals( owner );
		_creepsWavesDelay = new UndoRedo<int>( owner, 30 );
		_creepLevelCap = new UndoRedo<int>( owner, 30 );
		_creepsLevelUpInfo = new CreepsLevelUpInfo( owner );
		_quarterDestroyStatsMultipliers = new UndoRedoList<float>( owner, typeof( EStat ) );
		_movingTimerBlock = new UndoRedo<float>( owner, 3.0f );
		_creatureHappyStateParams = new CreatureHappyStateParams( owner );
		_commonSummonParameters = new CommonSummonParameters( owner );
		_rotationSpeed = new UndoRedo<float>( owner, 1000.0f );
		_rotationSpeedZ = new UndoRedo<float>( owner, 100.0f );
		_towerTurretParams = new TurretParams( owner );
		_mainBuildingTurretParams = new UndoRedoAssignableList<TurretParams>( owner, typeof( ETeamID ) );
		_expandNatureSegmentRation = new UndoRedo<int>( owner, 1 );
		_expandNatureGlyphsLifeTime = new UndoRedo<float>( owner, 30.0f );
		_expandNatureGlyphsVisibilityRadius = new UndoRedo<float>( owner, 10.0f );
		_expandNatureGlyphGameObject = new UndoRedoDBPtr<GameObject>( owner );
		_buildingsDenyAbility = new UndoRedoDBPtr<Ability>( owner );
		_buildingsDenyMinHealth = new UndoRedo<float>( owner, 0.0f );
		_buildingsDenyExperiencePenalty = new UndoRedo<float>( owner, 0.5f );
		_buildingsDenyNaftaPenalty = new UndoRedo<float>( owner, 0.0f );
		_buildingsDenyNaftaSpecPenalty = new UndoRedo<float>( owner, 0.0f );
		_buildingsDenyTeamNaftaPenalty = new UndoRedo<float>( owner, 0.5f );
		_buildingsAbilityA = new UndoRedoDBPtr<Ability>( owner );
		_buildingsAbilityB = new UndoRedoDBPtr<Ability>( owner );
		_buildingsMinHealthExplosionPercent = new UndoRedo<float>( owner, 80.0f );
		_buildingsFragEffectProbability = new UndoRedo<float>( owner, 0.2f );
		_raiseFlagAbility = new UndoRedoDBPtr<Ability>( owner );
		_talentsBuyRange = new UndoRedo<float>( owner, 15.0f );
		_defaultTalentsSet = new UndoRedoDBPtr<TalentsSet>( owner );
		_talentBaseStatBudget = new UndoRedo<float>( owner, 480.0f );
		_talentNaftaCostByLevel = new UndoRedoList<int>( owner, typeof( ETalentLevel ) );
		_talentVendorCostByRarity = new UndoRedoList<int>( owner, typeof( ETalentRarity ) );
		_pauseSeconds = new UndoRedo<float>( owner, 300.0f );
		_derivativeStats = new UndoRedoDBPtr<DerivativeStatsContainer>( owner );
		_statsBudget = new UndoRedoDBPtr<StatsBudgetContainer>( owner );
		_forceParameters = new UndoRedoDBPtr<ForceParameters>( owner );
		_talentGroups = new UndoRedoDBPtr<TalentGroupList>( owner );
		_consumableGroups = new UndoRedoDBPtr<ConsumableGroupList>( owner );
		_talentKits = new UndoRedoDBPtr<TalentKitList>( owner );
		_talentPacks = new UndoRedoDBPtr<TalentPackList>( owner );
		ExecutableFloatString __energyDamageReduction = new ExecutableFloatString(); // Construct default object for energyDamageReduction
		__energyDamageReduction.sString = "0.0";
		_energyDamageReduction = new ExecutableFloatString( owner, __energyDamageReduction );
		ExecutableFloatString __physicalDamageReduction = new ExecutableFloatString(); // Construct default object for physicalDamageReduction
		__physicalDamageReduction.sString = "0.0";
		_physicalDamageReduction = new ExecutableFloatString( owner, __physicalDamageReduction );
		_heroStatisticsParams = new HeroStatisticsParams( owner );
		ExpoModeParams __expoModeParams = new ExpoModeParams(); // Construct default object for expoModeParams
		__expoModeParams.damageModifier.sString = "1.0f";
		_expoModeParams = new ExpoModeParams( owner, __expoModeParams );
		_abilityAndDamageScalingParams = new AbilityAndDamageScalingParams( owner );
		_levelToExperienceTable = new UndoRedoDBPtr<DBLevelToExperience>( owner );
		_botsSettings = new UndoRedoDBPtr<BotsSettings>( owner );
		_warFogRemoveTime = new UndoRedo<float>( owner, 0.4f );
		_warFogRemoveRadius = new UndoRedo<float>( owner, 4.0f );
		_maxCreepsCount = new UndoRedo<int>( owner, 256 );
		_portal = new UndoRedoDBPtr<Talent>( owner );
		_heroRanks = new UndoRedoDBPtr<HeroRanks>( owner );
		_baseEmblemHeroNeeds = new UndoRedo<int>( owner, 3 );
		_behaviourTrackerParams = new UndoRedoDBPtr<BehaviourTrackerParams>( owner );
		___parent.Changed += FireChangedEvent;
		_teamsNames.Changed += FireChangedEvent;
		_chestGameObject.Changed += FireChangedEvent;
		_conditionFormulas.Changed += FireChangedEvent;
		_globalConstants.Changed += FireChangedEvent;
		_heroRespawnParams.Changed += FireChangedEvent;
		_heroAdvanceRespawnTime.Changed += FireChangedEvent;
		_baseRedeemCost.Changed += FireChangedEvent;
		_redeemCostPerLevel.Changed += FireChangedEvent;
		_redeemCostrecalculateTime.Changed += FireChangedEvent;
		_followRange.Changed += FireChangedEvent;
		_pickupItemRange.Changed += FireChangedEvent;
		_killAwardPartyMultiplier.Changed += FireChangedEvent;
		_maxTrueSightRange.Changed += FireChangedEvent;
		_channelingAbilityRangeMultiplier.Changed += FireChangedEvent;
		_heroScreamDelay.Changed += FireChangedEvent;
		_globalCooldownTime.Changed += FireChangedEvent;
		_skeletonLifeTime.Changed += FireChangedEvent;
		_glyphSettings.Changed += FireChangedEvent;
		_assistAccountTime.Changed += FireChangedEvent;
		_killTimeIntervals.Changed += FireChangedEvent;
		_creepsWavesDelay.Changed += FireChangedEvent;
		_creepLevelCap.Changed += FireChangedEvent;
		_creepsLevelUpInfo.Changed += FireChangedEvent;
		_quarterDestroyStatsMultipliers.Changed += FireChangedEvent;
		_movingTimerBlock.Changed += FireChangedEvent;
		_creatureHappyStateParams.Changed += FireChangedEvent;
		_commonSummonParameters.Changed += FireChangedEvent;
		_rotationSpeed.Changed += FireChangedEvent;
		_rotationSpeedZ.Changed += FireChangedEvent;
		_towerTurretParams.Changed += FireChangedEvent;
		_mainBuildingTurretParams.Changed += FireChangedEvent;
		_expandNatureSegmentRation.Changed += FireChangedEvent;
		_expandNatureGlyphsLifeTime.Changed += FireChangedEvent;
		_expandNatureGlyphsVisibilityRadius.Changed += FireChangedEvent;
		_expandNatureGlyphGameObject.Changed += FireChangedEvent;
		_buildingsDenyAbility.Changed += FireChangedEvent;
		_buildingsDenyMinHealth.Changed += FireChangedEvent;
		_buildingsDenyExperiencePenalty.Changed += FireChangedEvent;
		_buildingsDenyNaftaPenalty.Changed += FireChangedEvent;
		_buildingsDenyNaftaSpecPenalty.Changed += FireChangedEvent;
		_buildingsDenyTeamNaftaPenalty.Changed += FireChangedEvent;
		_buildingsAbilityA.Changed += FireChangedEvent;
		_buildingsAbilityB.Changed += FireChangedEvent;
		_buildingsMinHealthExplosionPercent.Changed += FireChangedEvent;
		_buildingsFragEffectProbability.Changed += FireChangedEvent;
		_raiseFlagAbility.Changed += FireChangedEvent;
		_talentsBuyRange.Changed += FireChangedEvent;
		_defaultTalentsSet.Changed += FireChangedEvent;
		_talentBaseStatBudget.Changed += FireChangedEvent;
		_talentNaftaCostByLevel.Changed += FireChangedEvent;
		_talentVendorCostByRarity.Changed += FireChangedEvent;
		_pauseSeconds.Changed += FireChangedEvent;
		_derivativeStats.Changed += FireChangedEvent;
		_statsBudget.Changed += FireChangedEvent;
		_forceParameters.Changed += FireChangedEvent;
		_talentGroups.Changed += FireChangedEvent;
		_consumableGroups.Changed += FireChangedEvent;
		_talentKits.Changed += FireChangedEvent;
		_talentPacks.Changed += FireChangedEvent;
		_energyDamageReduction.Changed += FireChangedEvent;
		_physicalDamageReduction.Changed += FireChangedEvent;
		_heroStatisticsParams.Changed += FireChangedEvent;
		_expoModeParams.Changed += FireChangedEvent;
		_abilityAndDamageScalingParams.Changed += FireChangedEvent;
		_levelToExperienceTable.Changed += FireChangedEvent;
		_botsSettings.Changed += FireChangedEvent;
		_warFogRemoveTime.Changed += FireChangedEvent;
		_warFogRemoveRadius.Changed += FireChangedEvent;
		_maxCreepsCount.Changed += FireChangedEvent;
		_portal.Changed += FireChangedEvent;
		_heroRanks.Changed += FireChangedEvent;
		_baseEmblemHeroNeeds.Changed += FireChangedEvent;
		_behaviourTrackerParams.Changed += FireChangedEvent;
	}

	public AILogicParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( AILogicParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AILogicParameters" );
		teamsNames = source.teamsNames;
		chestGameObject = source.chestGameObject;
		conditionFormulas = source.conditionFormulas;
		globalConstants = source.globalConstants;
		heroRespawnParams = source.heroRespawnParams;
		heroAdvanceRespawnTime = source.heroAdvanceRespawnTime;
		baseRedeemCost = source.baseRedeemCost;
		redeemCostPerLevel = source.redeemCostPerLevel;
		redeemCostrecalculateTime = source.redeemCostrecalculateTime;
		followRange = source.followRange;
		pickupItemRange = source.pickupItemRange;
		killAwardPartyMultiplier = source.killAwardPartyMultiplier;
		maxTrueSightRange = source.maxTrueSightRange;
		channelingAbilityRangeMultiplier = source.channelingAbilityRangeMultiplier;
		heroScreamDelay = source.heroScreamDelay;
		globalCooldownTime = source.globalCooldownTime;
		skeletonLifeTime = source.skeletonLifeTime;
		glyphSettings = source.glyphSettings;
		assistAccountTime = source.assistAccountTime;
		killTimeIntervals = source.killTimeIntervals;
		creepsWavesDelay = source.creepsWavesDelay;
		creepLevelCap = source.creepLevelCap;
		creepsLevelUpInfo = source.creepsLevelUpInfo;
		quarterDestroyStatsMultipliers = source.quarterDestroyStatsMultipliers;
		movingTimerBlock = source.movingTimerBlock;
		creatureHappyStateParams = source.creatureHappyStateParams;
		commonSummonParameters = source.commonSummonParameters;
		rotationSpeed = source.rotationSpeed;
		rotationSpeedZ = source.rotationSpeedZ;
		towerTurretParams = source.towerTurretParams;
		mainBuildingTurretParams = source.mainBuildingTurretParams;
		expandNatureSegmentRation = source.expandNatureSegmentRation;
		expandNatureGlyphsLifeTime = source.expandNatureGlyphsLifeTime;
		expandNatureGlyphsVisibilityRadius = source.expandNatureGlyphsVisibilityRadius;
		expandNatureGlyphGameObject = source.expandNatureGlyphGameObject;
		buildingsDenyAbility = source.buildingsDenyAbility;
		buildingsDenyMinHealth = source.buildingsDenyMinHealth;
		buildingsDenyExperiencePenalty = source.buildingsDenyExperiencePenalty;
		buildingsDenyNaftaPenalty = source.buildingsDenyNaftaPenalty;
		buildingsDenyNaftaSpecPenalty = source.buildingsDenyNaftaSpecPenalty;
		buildingsDenyTeamNaftaPenalty = source.buildingsDenyTeamNaftaPenalty;
		buildingsAbilityA = source.buildingsAbilityA;
		buildingsAbilityB = source.buildingsAbilityB;
		buildingsMinHealthExplosionPercent = source.buildingsMinHealthExplosionPercent;
		buildingsFragEffectProbability = source.buildingsFragEffectProbability;
		raiseFlagAbility = source.raiseFlagAbility;
		talentsBuyRange = source.talentsBuyRange;
		defaultTalentsSet = source.defaultTalentsSet;
		talentBaseStatBudget = source.talentBaseStatBudget;
		talentNaftaCostByLevel = source.talentNaftaCostByLevel;
		talentVendorCostByRarity = source.talentVendorCostByRarity;
		pauseSeconds = source.pauseSeconds;
		derivativeStats = source.derivativeStats;
		statsBudget = source.statsBudget;
		forceParameters = source.forceParameters;
		talentGroups = source.talentGroups;
		consumableGroups = source.consumableGroups;
		talentKits = source.talentKits;
		talentPacks = source.talentPacks;
		energyDamageReduction = source.energyDamageReduction;
		physicalDamageReduction = source.physicalDamageReduction;
		heroStatisticsParams = source.heroStatisticsParams;
		expoModeParams = source.expoModeParams;
		abilityAndDamageScalingParams = source.abilityAndDamageScalingParams;
		levelToExperienceTable = source.levelToExperienceTable;
		botsSettings = source.botsSettings;
		warFogRemoveTime = source.warFogRemoveTime;
		warFogRemoveRadius = source.warFogRemoveRadius;
		maxCreepsCount = source.maxCreepsCount;
		portal = source.portal;
		heroRanks = source.heroRanks;
		baseEmblemHeroNeeds = source.baseEmblemHeroNeeds;
		behaviourTrackerParams = source.behaviourTrackerParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AILogicParameters source = _source as AILogicParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AILogicParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AILogicParameters newParent = rawParent == null ? null : rawParent.Get<AILogicParameters>();
		if ( newParent == null && _newParent is AILogicParameters )
			newParent = _newParent as AILogicParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_teamsNames.SetParent( newParent == null ? null : newParent._teamsNames );
		_chestGameObject.SetParent( newParent == null ? null : newParent._chestGameObject );
		_conditionFormulas.SetParent( newParent == null ? null : newParent._conditionFormulas );
		_globalConstants.SetParent( newParent == null ? null : newParent._globalConstants );
		_heroRespawnParams.SetParent( newParent == null ? null : newParent._heroRespawnParams );
		_heroAdvanceRespawnTime.SetParent( newParent == null ? null : newParent._heroAdvanceRespawnTime );
		_baseRedeemCost.SetParent( newParent == null ? null : newParent._baseRedeemCost );
		_redeemCostPerLevel.SetParent( newParent == null ? null : newParent._redeemCostPerLevel );
		_redeemCostrecalculateTime.SetParent( newParent == null ? null : newParent._redeemCostrecalculateTime );
		_followRange.SetParent( newParent == null ? null : newParent._followRange );
		_pickupItemRange.SetParent( newParent == null ? null : newParent._pickupItemRange );
		_killAwardPartyMultiplier.SetParent( newParent == null ? null : newParent._killAwardPartyMultiplier );
		_maxTrueSightRange.SetParent( newParent == null ? null : newParent._maxTrueSightRange );
		_channelingAbilityRangeMultiplier.SetParent( newParent == null ? null : newParent._channelingAbilityRangeMultiplier );
		_heroScreamDelay.SetParent( newParent == null ? null : newParent._heroScreamDelay );
		_globalCooldownTime.SetParent( newParent == null ? null : newParent._globalCooldownTime );
		_skeletonLifeTime.SetParent( newParent == null ? null : newParent._skeletonLifeTime );
		_glyphSettings.SetParent( newParent == null ? null : newParent._glyphSettings );
		_assistAccountTime.SetParent( newParent == null ? null : newParent._assistAccountTime );
		_killTimeIntervals.SetParent( newParent == null ? null : newParent._killTimeIntervals );
		_creepsWavesDelay.SetParent( newParent == null ? null : newParent._creepsWavesDelay );
		_creepLevelCap.SetParent( newParent == null ? null : newParent._creepLevelCap );
		_creepsLevelUpInfo.SetParent( newParent == null ? null : newParent._creepsLevelUpInfo );
		_quarterDestroyStatsMultipliers.SetParent( newParent == null ? null : newParent._quarterDestroyStatsMultipliers );
		_movingTimerBlock.SetParent( newParent == null ? null : newParent._movingTimerBlock );
		_creatureHappyStateParams.SetParent( newParent == null ? null : newParent._creatureHappyStateParams );
		_commonSummonParameters.SetParent( newParent == null ? null : newParent._commonSummonParameters );
		_rotationSpeed.SetParent( newParent == null ? null : newParent._rotationSpeed );
		_rotationSpeedZ.SetParent( newParent == null ? null : newParent._rotationSpeedZ );
		_towerTurretParams.SetParent( newParent == null ? null : newParent._towerTurretParams );
		_mainBuildingTurretParams.SetParent( newParent == null ? null : newParent._mainBuildingTurretParams );
		_expandNatureSegmentRation.SetParent( newParent == null ? null : newParent._expandNatureSegmentRation );
		_expandNatureGlyphsLifeTime.SetParent( newParent == null ? null : newParent._expandNatureGlyphsLifeTime );
		_expandNatureGlyphsVisibilityRadius.SetParent( newParent == null ? null : newParent._expandNatureGlyphsVisibilityRadius );
		_expandNatureGlyphGameObject.SetParent( newParent == null ? null : newParent._expandNatureGlyphGameObject );
		_buildingsDenyAbility.SetParent( newParent == null ? null : newParent._buildingsDenyAbility );
		_buildingsDenyMinHealth.SetParent( newParent == null ? null : newParent._buildingsDenyMinHealth );
		_buildingsDenyExperiencePenalty.SetParent( newParent == null ? null : newParent._buildingsDenyExperiencePenalty );
		_buildingsDenyNaftaPenalty.SetParent( newParent == null ? null : newParent._buildingsDenyNaftaPenalty );
		_buildingsDenyNaftaSpecPenalty.SetParent( newParent == null ? null : newParent._buildingsDenyNaftaSpecPenalty );
		_buildingsDenyTeamNaftaPenalty.SetParent( newParent == null ? null : newParent._buildingsDenyTeamNaftaPenalty );
		_buildingsAbilityA.SetParent( newParent == null ? null : newParent._buildingsAbilityA );
		_buildingsAbilityB.SetParent( newParent == null ? null : newParent._buildingsAbilityB );
		_buildingsMinHealthExplosionPercent.SetParent( newParent == null ? null : newParent._buildingsMinHealthExplosionPercent );
		_buildingsFragEffectProbability.SetParent( newParent == null ? null : newParent._buildingsFragEffectProbability );
		_raiseFlagAbility.SetParent( newParent == null ? null : newParent._raiseFlagAbility );
		_talentsBuyRange.SetParent( newParent == null ? null : newParent._talentsBuyRange );
		_defaultTalentsSet.SetParent( newParent == null ? null : newParent._defaultTalentsSet );
		_talentBaseStatBudget.SetParent( newParent == null ? null : newParent._talentBaseStatBudget );
		_talentNaftaCostByLevel.SetParent( newParent == null ? null : newParent._talentNaftaCostByLevel );
		_talentVendorCostByRarity.SetParent( newParent == null ? null : newParent._talentVendorCostByRarity );
		_pauseSeconds.SetParent( newParent == null ? null : newParent._pauseSeconds );
		_derivativeStats.SetParent( newParent == null ? null : newParent._derivativeStats );
		_statsBudget.SetParent( newParent == null ? null : newParent._statsBudget );
		_forceParameters.SetParent( newParent == null ? null : newParent._forceParameters );
		_talentGroups.SetParent( newParent == null ? null : newParent._talentGroups );
		_consumableGroups.SetParent( newParent == null ? null : newParent._consumableGroups );
		_talentKits.SetParent( newParent == null ? null : newParent._talentKits );
		_talentPacks.SetParent( newParent == null ? null : newParent._talentPacks );
		_energyDamageReduction.SetParent( newParent == null ? null : newParent._energyDamageReduction );
		_physicalDamageReduction.SetParent( newParent == null ? null : newParent._physicalDamageReduction );
		_heroStatisticsParams.SetParent( newParent == null ? null : newParent._heroStatisticsParams );
		_expoModeParams.SetParent( newParent == null ? null : newParent._expoModeParams );
		_abilityAndDamageScalingParams.SetParent( newParent == null ? null : newParent._abilityAndDamageScalingParams );
		_levelToExperienceTable.SetParent( newParent == null ? null : newParent._levelToExperienceTable );
		_botsSettings.SetParent( newParent == null ? null : newParent._botsSettings );
		_warFogRemoveTime.SetParent( newParent == null ? null : newParent._warFogRemoveTime );
		_warFogRemoveRadius.SetParent( newParent == null ? null : newParent._warFogRemoveRadius );
		_maxCreepsCount.SetParent( newParent == null ? null : newParent._maxCreepsCount );
		_portal.SetParent( newParent == null ? null : newParent._portal );
		_heroRanks.SetParent( newParent == null ? null : newParent._heroRanks );
		_baseEmblemHeroNeeds.SetParent( newParent == null ? null : newParent._baseEmblemHeroNeeds );
		_behaviourTrackerParams.SetParent( newParent == null ? null : newParent._behaviourTrackerParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_teamsNames.Reset();
		_chestGameObject.Reset();
		_conditionFormulas.Reset();
		_globalConstants.Reset();
		_heroRespawnParams.Reset();
		_heroAdvanceRespawnTime.Reset();
		_baseRedeemCost.Reset();
		_redeemCostPerLevel.Reset();
		_redeemCostrecalculateTime.Reset();
		_followRange.Reset();
		_pickupItemRange.Reset();
		_killAwardPartyMultiplier.Reset();
		_maxTrueSightRange.Reset();
		_channelingAbilityRangeMultiplier.Reset();
		_heroScreamDelay.Reset();
		_globalCooldownTime.Reset();
		_skeletonLifeTime.Reset();
		_glyphSettings.Reset();
		_assistAccountTime.Reset();
		_killTimeIntervals.Reset();
		_creepsWavesDelay.Reset();
		_creepLevelCap.Reset();
		_creepsLevelUpInfo.Reset();
		_quarterDestroyStatsMultipliers.Reset();
		_movingTimerBlock.Reset();
		_creatureHappyStateParams.Reset();
		_commonSummonParameters.Reset();
		_rotationSpeed.Reset();
		_rotationSpeedZ.Reset();
		_towerTurretParams.Reset();
		_mainBuildingTurretParams.Reset();
		_expandNatureSegmentRation.Reset();
		_expandNatureGlyphsLifeTime.Reset();
		_expandNatureGlyphsVisibilityRadius.Reset();
		_expandNatureGlyphGameObject.Reset();
		_buildingsDenyAbility.Reset();
		_buildingsDenyMinHealth.Reset();
		_buildingsDenyExperiencePenalty.Reset();
		_buildingsDenyNaftaPenalty.Reset();
		_buildingsDenyNaftaSpecPenalty.Reset();
		_buildingsDenyTeamNaftaPenalty.Reset();
		_buildingsAbilityA.Reset();
		_buildingsAbilityB.Reset();
		_buildingsMinHealthExplosionPercent.Reset();
		_buildingsFragEffectProbability.Reset();
		_raiseFlagAbility.Reset();
		_talentsBuyRange.Reset();
		_defaultTalentsSet.Reset();
		_talentBaseStatBudget.Reset();
		_talentNaftaCostByLevel.Reset();
		_talentVendorCostByRarity.Reset();
		_pauseSeconds.Reset();
		_derivativeStats.Reset();
		_statsBudget.Reset();
		_forceParameters.Reset();
		_talentGroups.Reset();
		_consumableGroups.Reset();
		_talentKits.Reset();
		_talentPacks.Reset();
		_energyDamageReduction.Reset();
		_physicalDamageReduction.Reset();
		_heroStatisticsParams.Reset();
		_expoModeParams.Reset();
		_abilityAndDamageScalingParams.Reset();
		_levelToExperienceTable.Reset();
		_botsSettings.Reset();
		_warFogRemoveTime.Reset();
		_warFogRemoveRadius.Reset();
		_maxCreepsCount.Reset();
		_portal.Reset();
		_heroRanks.Reset();
		_baseEmblemHeroNeeds.Reset();
		_behaviourTrackerParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_teamsNames.IsDerivedFromParent()
			&& _chestGameObject.IsDerivedFromParent()
			&& _conditionFormulas.IsDerivedFromParent()
			&& _globalConstants.IsDerivedFromParent()
			&& _heroRespawnParams.IsDerivedFromParent()
			&& _heroAdvanceRespawnTime.IsDerivedFromParent()
			&& _baseRedeemCost.IsDerivedFromParent()
			&& _redeemCostPerLevel.IsDerivedFromParent()
			&& _redeemCostrecalculateTime.IsDerivedFromParent()
			&& _followRange.IsDerivedFromParent()
			&& _pickupItemRange.IsDerivedFromParent()
			&& _killAwardPartyMultiplier.IsDerivedFromParent()
			&& _maxTrueSightRange.IsDerivedFromParent()
			&& _channelingAbilityRangeMultiplier.IsDerivedFromParent()
			&& _heroScreamDelay.IsDerivedFromParent()
			&& _globalCooldownTime.IsDerivedFromParent()
			&& _skeletonLifeTime.IsDerivedFromParent()
			&& _glyphSettings.IsDerivedFromParent()
			&& _assistAccountTime.IsDerivedFromParent()
			&& _killTimeIntervals.IsDerivedFromParent()
			&& _creepsWavesDelay.IsDerivedFromParent()
			&& _creepLevelCap.IsDerivedFromParent()
			&& _creepsLevelUpInfo.IsDerivedFromParent()
			&& _quarterDestroyStatsMultipliers.IsDerivedFromParent()
			&& _movingTimerBlock.IsDerivedFromParent()
			&& _creatureHappyStateParams.IsDerivedFromParent()
			&& _commonSummonParameters.IsDerivedFromParent()
			&& _rotationSpeed.IsDerivedFromParent()
			&& _rotationSpeedZ.IsDerivedFromParent()
			&& _towerTurretParams.IsDerivedFromParent()
			&& _mainBuildingTurretParams.IsDerivedFromParent()
			&& _expandNatureSegmentRation.IsDerivedFromParent()
			&& _expandNatureGlyphsLifeTime.IsDerivedFromParent()
			&& _expandNatureGlyphsVisibilityRadius.IsDerivedFromParent()
			&& _expandNatureGlyphGameObject.IsDerivedFromParent()
			&& _buildingsDenyAbility.IsDerivedFromParent()
			&& _buildingsDenyMinHealth.IsDerivedFromParent()
			&& _buildingsDenyExperiencePenalty.IsDerivedFromParent()
			&& _buildingsDenyNaftaPenalty.IsDerivedFromParent()
			&& _buildingsDenyNaftaSpecPenalty.IsDerivedFromParent()
			&& _buildingsDenyTeamNaftaPenalty.IsDerivedFromParent()
			&& _buildingsAbilityA.IsDerivedFromParent()
			&& _buildingsAbilityB.IsDerivedFromParent()
			&& _buildingsMinHealthExplosionPercent.IsDerivedFromParent()
			&& _buildingsFragEffectProbability.IsDerivedFromParent()
			&& _raiseFlagAbility.IsDerivedFromParent()
			&& _talentsBuyRange.IsDerivedFromParent()
			&& _defaultTalentsSet.IsDerivedFromParent()
			&& _talentBaseStatBudget.IsDerivedFromParent()
			&& _talentNaftaCostByLevel.IsDerivedFromParent()
			&& _talentVendorCostByRarity.IsDerivedFromParent()
			&& _pauseSeconds.IsDerivedFromParent()
			&& _derivativeStats.IsDerivedFromParent()
			&& _statsBudget.IsDerivedFromParent()
			&& _forceParameters.IsDerivedFromParent()
			&& _talentGroups.IsDerivedFromParent()
			&& _consumableGroups.IsDerivedFromParent()
			&& _talentKits.IsDerivedFromParent()
			&& _talentPacks.IsDerivedFromParent()
			&& _energyDamageReduction.IsDerivedFromParent()
			&& _physicalDamageReduction.IsDerivedFromParent()
			&& _heroStatisticsParams.IsDerivedFromParent()
			&& _expoModeParams.IsDerivedFromParent()
			&& _abilityAndDamageScalingParams.IsDerivedFromParent()
			&& _levelToExperienceTable.IsDerivedFromParent()
			&& _botsSettings.IsDerivedFromParent()
			&& _warFogRemoveTime.IsDerivedFromParent()
			&& _warFogRemoveRadius.IsDerivedFromParent()
			&& _maxCreepsCount.IsDerivedFromParent()
			&& _portal.IsDerivedFromParent()
			&& _heroRanks.IsDerivedFromParent()
			&& _baseEmblemHeroNeeds.IsDerivedFromParent()
			&& _behaviourTrackerParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "teamsNames" )
			_teamsNames.Reset();
		else if ( fieldName == "chestGameObject" )
			_chestGameObject.Reset();
		else if ( fieldName == "conditionFormulas" )
			_conditionFormulas.Reset();
		else if ( fieldName == "globalConstants" )
			_globalConstants.Reset();
		else if ( fieldName == "heroRespawnParams" )
			_heroRespawnParams.Reset();
		else if ( fieldName == "heroAdvanceRespawnTime" )
			_heroAdvanceRespawnTime.Reset();
		else if ( fieldName == "baseRedeemCost" )
			_baseRedeemCost.Reset();
		else if ( fieldName == "redeemCostPerLevel" )
			_redeemCostPerLevel.Reset();
		else if ( fieldName == "redeemCostrecalculateTime" )
			_redeemCostrecalculateTime.Reset();
		else if ( fieldName == "followRange" )
			_followRange.Reset();
		else if ( fieldName == "pickupItemRange" )
			_pickupItemRange.Reset();
		else if ( fieldName == "killAwardPartyMultiplier" )
			_killAwardPartyMultiplier.Reset();
		else if ( fieldName == "maxTrueSightRange" )
			_maxTrueSightRange.Reset();
		else if ( fieldName == "channelingAbilityRangeMultiplier" )
			_channelingAbilityRangeMultiplier.Reset();
		else if ( fieldName == "heroScreamDelay" )
			_heroScreamDelay.Reset();
		else if ( fieldName == "globalCooldownTime" )
			_globalCooldownTime.Reset();
		else if ( fieldName == "skeletonLifeTime" )
			_skeletonLifeTime.Reset();
		else if ( fieldName == "glyphSettings" )
			_glyphSettings.Reset();
		else if ( fieldName == "assistAccountTime" )
			_assistAccountTime.Reset();
		else if ( fieldName == "killTimeIntervals" )
			_killTimeIntervals.Reset();
		else if ( fieldName == "creepsWavesDelay" )
			_creepsWavesDelay.Reset();
		else if ( fieldName == "creepLevelCap" )
			_creepLevelCap.Reset();
		else if ( fieldName == "creepsLevelUpInfo" )
			_creepsLevelUpInfo.Reset();
		else if ( fieldName == "quarterDestroyStatsMultipliers" )
			_quarterDestroyStatsMultipliers.Reset();
		else if ( fieldName == "movingTimerBlock" )
			_movingTimerBlock.Reset();
		else if ( fieldName == "creatureHappyStateParams" )
			_creatureHappyStateParams.Reset();
		else if ( fieldName == "commonSummonParameters" )
			_commonSummonParameters.Reset();
		else if ( fieldName == "rotationSpeed" )
			_rotationSpeed.Reset();
		else if ( fieldName == "rotationSpeedZ" )
			_rotationSpeedZ.Reset();
		else if ( fieldName == "towerTurretParams" )
			_towerTurretParams.Reset();
		else if ( fieldName == "mainBuildingTurretParams" )
			_mainBuildingTurretParams.Reset();
		else if ( fieldName == "expandNatureSegmentRation" )
			_expandNatureSegmentRation.Reset();
		else if ( fieldName == "expandNatureGlyphsLifeTime" )
			_expandNatureGlyphsLifeTime.Reset();
		else if ( fieldName == "expandNatureGlyphsVisibilityRadius" )
			_expandNatureGlyphsVisibilityRadius.Reset();
		else if ( fieldName == "expandNatureGlyphGameObject" )
			_expandNatureGlyphGameObject.Reset();
		else if ( fieldName == "buildingsDenyAbility" )
			_buildingsDenyAbility.Reset();
		else if ( fieldName == "buildingsDenyMinHealth" )
			_buildingsDenyMinHealth.Reset();
		else if ( fieldName == "buildingsDenyExperiencePenalty" )
			_buildingsDenyExperiencePenalty.Reset();
		else if ( fieldName == "buildingsDenyNaftaPenalty" )
			_buildingsDenyNaftaPenalty.Reset();
		else if ( fieldName == "buildingsDenyNaftaSpecPenalty" )
			_buildingsDenyNaftaSpecPenalty.Reset();
		else if ( fieldName == "buildingsDenyTeamNaftaPenalty" )
			_buildingsDenyTeamNaftaPenalty.Reset();
		else if ( fieldName == "buildingsAbilityA" )
			_buildingsAbilityA.Reset();
		else if ( fieldName == "buildingsAbilityB" )
			_buildingsAbilityB.Reset();
		else if ( fieldName == "buildingsMinHealthExplosionPercent" )
			_buildingsMinHealthExplosionPercent.Reset();
		else if ( fieldName == "buildingsFragEffectProbability" )
			_buildingsFragEffectProbability.Reset();
		else if ( fieldName == "raiseFlagAbility" )
			_raiseFlagAbility.Reset();
		else if ( fieldName == "talentsBuyRange" )
			_talentsBuyRange.Reset();
		else if ( fieldName == "defaultTalentsSet" )
			_defaultTalentsSet.Reset();
		else if ( fieldName == "talentBaseStatBudget" )
			_talentBaseStatBudget.Reset();
		else if ( fieldName == "talentNaftaCostByLevel" )
			_talentNaftaCostByLevel.Reset();
		else if ( fieldName == "talentVendorCostByRarity" )
			_talentVendorCostByRarity.Reset();
		else if ( fieldName == "pauseSeconds" )
			_pauseSeconds.Reset();
		else if ( fieldName == "derivativeStats" )
			_derivativeStats.Reset();
		else if ( fieldName == "statsBudget" )
			_statsBudget.Reset();
		else if ( fieldName == "forceParameters" )
			_forceParameters.Reset();
		else if ( fieldName == "talentGroups" )
			_talentGroups.Reset();
		else if ( fieldName == "consumableGroups" )
			_consumableGroups.Reset();
		else if ( fieldName == "talentKits" )
			_talentKits.Reset();
		else if ( fieldName == "talentPacks" )
			_talentPacks.Reset();
		else if ( fieldName == "energyDamageReduction" )
			_energyDamageReduction.Reset();
		else if ( fieldName == "physicalDamageReduction" )
			_physicalDamageReduction.Reset();
		else if ( fieldName == "heroStatisticsParams" )
			_heroStatisticsParams.Reset();
		else if ( fieldName == "expoModeParams" )
			_expoModeParams.Reset();
		else if ( fieldName == "abilityAndDamageScalingParams" )
			_abilityAndDamageScalingParams.Reset();
		else if ( fieldName == "levelToExperienceTable" )
			_levelToExperienceTable.Reset();
		else if ( fieldName == "botsSettings" )
			_botsSettings.Reset();
		else if ( fieldName == "warFogRemoveTime" )
			_warFogRemoveTime.Reset();
		else if ( fieldName == "warFogRemoveRadius" )
			_warFogRemoveRadius.Reset();
		else if ( fieldName == "maxCreepsCount" )
			_maxCreepsCount.Reset();
		else if ( fieldName == "portal" )
			_portal.Reset();
		else if ( fieldName == "heroRanks" )
			_heroRanks.Reset();
		else if ( fieldName == "baseEmblemHeroNeeds" )
			_baseEmblemHeroNeeds.Reset();
		else if ( fieldName == "behaviourTrackerParams" )
			_behaviourTrackerParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "teamsNames" )
			return _teamsNames.IsDerivedFromParent();
		if ( fieldName == "chestGameObject" )
			return _chestGameObject.IsDerivedFromParent();
		if ( fieldName == "conditionFormulas" )
			return _conditionFormulas.IsDerivedFromParent();
		if ( fieldName == "globalConstants" )
			return _globalConstants.IsDerivedFromParent();
		if ( fieldName == "heroRespawnParams" )
			return _heroRespawnParams.IsDerivedFromParent();
		if ( fieldName == "heroAdvanceRespawnTime" )
			return _heroAdvanceRespawnTime.IsDerivedFromParent();
		if ( fieldName == "baseRedeemCost" )
			return _baseRedeemCost.IsDerivedFromParent();
		if ( fieldName == "redeemCostPerLevel" )
			return _redeemCostPerLevel.IsDerivedFromParent();
		if ( fieldName == "redeemCostrecalculateTime" )
			return _redeemCostrecalculateTime.IsDerivedFromParent();
		if ( fieldName == "followRange" )
			return _followRange.IsDerivedFromParent();
		if ( fieldName == "pickupItemRange" )
			return _pickupItemRange.IsDerivedFromParent();
		if ( fieldName == "killAwardPartyMultiplier" )
			return _killAwardPartyMultiplier.IsDerivedFromParent();
		if ( fieldName == "maxTrueSightRange" )
			return _maxTrueSightRange.IsDerivedFromParent();
		if ( fieldName == "channelingAbilityRangeMultiplier" )
			return _channelingAbilityRangeMultiplier.IsDerivedFromParent();
		if ( fieldName == "heroScreamDelay" )
			return _heroScreamDelay.IsDerivedFromParent();
		if ( fieldName == "globalCooldownTime" )
			return _globalCooldownTime.IsDerivedFromParent();
		if ( fieldName == "skeletonLifeTime" )
			return _skeletonLifeTime.IsDerivedFromParent();
		if ( fieldName == "glyphSettings" )
			return _glyphSettings.IsDerivedFromParent();
		if ( fieldName == "assistAccountTime" )
			return _assistAccountTime.IsDerivedFromParent();
		if ( fieldName == "killTimeIntervals" )
			return _killTimeIntervals.IsDerivedFromParent();
		if ( fieldName == "creepsWavesDelay" )
			return _creepsWavesDelay.IsDerivedFromParent();
		if ( fieldName == "creepLevelCap" )
			return _creepLevelCap.IsDerivedFromParent();
		if ( fieldName == "creepsLevelUpInfo" )
			return _creepsLevelUpInfo.IsDerivedFromParent();
		if ( fieldName == "quarterDestroyStatsMultipliers" )
			return _quarterDestroyStatsMultipliers.IsDerivedFromParent();
		if ( fieldName == "movingTimerBlock" )
			return _movingTimerBlock.IsDerivedFromParent();
		if ( fieldName == "creatureHappyStateParams" )
			return _creatureHappyStateParams.IsDerivedFromParent();
		if ( fieldName == "commonSummonParameters" )
			return _commonSummonParameters.IsDerivedFromParent();
		if ( fieldName == "rotationSpeed" )
			return _rotationSpeed.IsDerivedFromParent();
		if ( fieldName == "rotationSpeedZ" )
			return _rotationSpeedZ.IsDerivedFromParent();
		if ( fieldName == "towerTurretParams" )
			return _towerTurretParams.IsDerivedFromParent();
		if ( fieldName == "mainBuildingTurretParams" )
			return _mainBuildingTurretParams.IsDerivedFromParent();
		if ( fieldName == "expandNatureSegmentRation" )
			return _expandNatureSegmentRation.IsDerivedFromParent();
		if ( fieldName == "expandNatureGlyphsLifeTime" )
			return _expandNatureGlyphsLifeTime.IsDerivedFromParent();
		if ( fieldName == "expandNatureGlyphsVisibilityRadius" )
			return _expandNatureGlyphsVisibilityRadius.IsDerivedFromParent();
		if ( fieldName == "expandNatureGlyphGameObject" )
			return _expandNatureGlyphGameObject.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyAbility" )
			return _buildingsDenyAbility.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyMinHealth" )
			return _buildingsDenyMinHealth.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyExperiencePenalty" )
			return _buildingsDenyExperiencePenalty.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyNaftaPenalty" )
			return _buildingsDenyNaftaPenalty.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyNaftaSpecPenalty" )
			return _buildingsDenyNaftaSpecPenalty.IsDerivedFromParent();
		if ( fieldName == "buildingsDenyTeamNaftaPenalty" )
			return _buildingsDenyTeamNaftaPenalty.IsDerivedFromParent();
		if ( fieldName == "buildingsAbilityA" )
			return _buildingsAbilityA.IsDerivedFromParent();
		if ( fieldName == "buildingsAbilityB" )
			return _buildingsAbilityB.IsDerivedFromParent();
		if ( fieldName == "buildingsMinHealthExplosionPercent" )
			return _buildingsMinHealthExplosionPercent.IsDerivedFromParent();
		if ( fieldName == "buildingsFragEffectProbability" )
			return _buildingsFragEffectProbability.IsDerivedFromParent();
		if ( fieldName == "raiseFlagAbility" )
			return _raiseFlagAbility.IsDerivedFromParent();
		if ( fieldName == "talentsBuyRange" )
			return _talentsBuyRange.IsDerivedFromParent();
		if ( fieldName == "defaultTalentsSet" )
			return _defaultTalentsSet.IsDerivedFromParent();
		if ( fieldName == "talentBaseStatBudget" )
			return _talentBaseStatBudget.IsDerivedFromParent();
		if ( fieldName == "talentNaftaCostByLevel" )
			return _talentNaftaCostByLevel.IsDerivedFromParent();
		if ( fieldName == "talentVendorCostByRarity" )
			return _talentVendorCostByRarity.IsDerivedFromParent();
		if ( fieldName == "pauseSeconds" )
			return _pauseSeconds.IsDerivedFromParent();
		if ( fieldName == "derivativeStats" )
			return _derivativeStats.IsDerivedFromParent();
		if ( fieldName == "statsBudget" )
			return _statsBudget.IsDerivedFromParent();
		if ( fieldName == "forceParameters" )
			return _forceParameters.IsDerivedFromParent();
		if ( fieldName == "talentGroups" )
			return _talentGroups.IsDerivedFromParent();
		if ( fieldName == "consumableGroups" )
			return _consumableGroups.IsDerivedFromParent();
		if ( fieldName == "talentKits" )
			return _talentKits.IsDerivedFromParent();
		if ( fieldName == "talentPacks" )
			return _talentPacks.IsDerivedFromParent();
		if ( fieldName == "energyDamageReduction" )
			return _energyDamageReduction.IsDerivedFromParent();
		if ( fieldName == "physicalDamageReduction" )
			return _physicalDamageReduction.IsDerivedFromParent();
		if ( fieldName == "heroStatisticsParams" )
			return _heroStatisticsParams.IsDerivedFromParent();
		if ( fieldName == "expoModeParams" )
			return _expoModeParams.IsDerivedFromParent();
		if ( fieldName == "abilityAndDamageScalingParams" )
			return _abilityAndDamageScalingParams.IsDerivedFromParent();
		if ( fieldName == "levelToExperienceTable" )
			return _levelToExperienceTable.IsDerivedFromParent();
		if ( fieldName == "botsSettings" )
			return _botsSettings.IsDerivedFromParent();
		if ( fieldName == "warFogRemoveTime" )
			return _warFogRemoveTime.IsDerivedFromParent();
		if ( fieldName == "warFogRemoveRadius" )
			return _warFogRemoveRadius.IsDerivedFromParent();
		if ( fieldName == "maxCreepsCount" )
			return _maxCreepsCount.IsDerivedFromParent();
		if ( fieldName == "portal" )
			return _portal.IsDerivedFromParent();
		if ( fieldName == "heroRanks" )
			return _heroRanks.IsDerivedFromParent();
		if ( fieldName == "baseEmblemHeroNeeds" )
			return _baseEmblemHeroNeeds.IsDerivedFromParent();
		if ( fieldName == "behaviourTrackerParams" )
			return _behaviourTrackerParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[UseTypeName("BTP")]
public class BehaviourTrackerParams : DBResource
{
	private UndoRedoDBPtr<BehaviourTrackerParams> ___parent;
	[HideInOutliner]
	public new DBPtr<BehaviourTrackerParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _idleTime;
	private UndoRedo<int> _goodActionTimeout;
	private UndoRedo<int> _goodZumaActionTimeout;
	private UndoRedo<int> _feederDeathCount;
	private UndoRedo<int> _feederDeathTime;
	private UndoRedo<int> _badBehaviourComplaintsThreshold;
	private UndoRedo<int> _insultComplaintsThreshold;
	private UndoRedo<int> _autoMuteMinMessage;
	private UndoRedo<int> _autoMuteMessagePerTime;
	private UndoRedo<int> _autoMuteTimeLimit;
	private UndoRedo<int> _autoMuteMessageLength;

	[Description( "Время (сек) ожидания после начала игры" )]
	public int idleTime { get { return _idleTime.Get(); } set { _idleTime.Set( value ); } }

	[Description( "Игрок получает 'зону риска', если в течение этого времени (сек) он не принимал участия в игре" )]
	public int goodActionTimeout { get { return _goodActionTimeout.Get(); } set { _goodActionTimeout.Set( value ); } }

	[Description( "Игрок получает 'зону риска', если в течение этого времени (сек) он, находясь в зуме, не передал ни одного свитка союзнику" )]
	public int goodZumaActionTimeout { get { return _goodZumaActionTimeout.Get(); } set { _goodZumaActionTimeout.Set( value ); } }

	[Description( "Игрок получает 'зону риска' и считается фидером, если его герой умер указанное количество раз в течение @feederDeathTime" )]
	public int feederDeathCount { get { return _feederDeathCount.Get(); } set { _feederDeathCount.Set( value ); } }

	[Description( "Игрок получает 'зону риска' и считается фидером, если его герой умер @feederDeathCount раз в течение указанного времени (сек)" )]
	public int feederDeathTime { get { return _feederDeathTime.Get(); } set { _feederDeathTime.Set( value ); } }

	[Description( "Поведение игрока считается действительно неспортивным, если он собрал столько (или больше) жалоб о неспортивном поведении от союзников" )]
	public int badBehaviourComplaintsThreshold { get { return _badBehaviourComplaintsThreshold.Get(); } set { _badBehaviourComplaintsThreshold.Set( value ); } }

	[Description( "Количество репорта по причине оскорбления, после которых по окончанию сессии будем наказываеть мьютом" )]
	public int insultComplaintsThreshold { get { return _insultComplaintsThreshold.Get(); } set { _insultComplaintsThreshold.Set( value ); } }

	[Description( "Общее количество сообщений в чате от игрока мы планируем наказывать игрока мьютом, которых по окончанию сессии будем наказываеть мьютом" )]
	public int autoMuteMinMessage { get { return _autoMuteMinMessage.Get(); } set { _autoMuteMinMessage.Set( value ); } }

	[Description( "Общее количество сообщений в чате за время AutoMuteTimeLimit, после которых мы считаем сообщения спамом" )]
	public int autoMuteMessagePerTime { get { return _autoMuteMessagePerTime.Get(); } set { _autoMuteMessagePerTime.Set( value ); } }

	[Description( "Время, за которое мы проверяем количество сообщений AutoMuteMessagePerTime" )]
	public int autoMuteTimeLimit { get { return _autoMuteTimeLimit.Get(); } set { _autoMuteTimeLimit.Set( value ); } }

	[Description( "Длина сообщения, выше которой сообщение считается плохим и учитывается системой автомьюта" )]
	public int autoMuteMessageLength { get { return _autoMuteMessageLength.Get(); } set { _autoMuteMessageLength.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BehaviourTrackerParams>(owner);
		_idleTime = new UndoRedo<int>( owner, 120 );
		_goodActionTimeout = new UndoRedo<int>( owner, 180 );
		_goodZumaActionTimeout = new UndoRedo<int>( owner, 300 );
		_feederDeathCount = new UndoRedo<int>( owner, 3 );
		_feederDeathTime = new UndoRedo<int>( owner, 240 );
		_badBehaviourComplaintsThreshold = new UndoRedo<int>( owner, 2 );
		_insultComplaintsThreshold = new UndoRedo<int>( owner, 2 );
		_autoMuteMinMessage = new UndoRedo<int>( owner, 0 );
		_autoMuteMessagePerTime = new UndoRedo<int>( owner, 3 );
		_autoMuteTimeLimit = new UndoRedo<int>( owner, 10 );
		_autoMuteMessageLength = new UndoRedo<int>( owner, 50 );
		___parent.Changed += FireChangedEvent;
		_idleTime.Changed += FireChangedEvent;
		_goodActionTimeout.Changed += FireChangedEvent;
		_goodZumaActionTimeout.Changed += FireChangedEvent;
		_feederDeathCount.Changed += FireChangedEvent;
		_feederDeathTime.Changed += FireChangedEvent;
		_badBehaviourComplaintsThreshold.Changed += FireChangedEvent;
		_insultComplaintsThreshold.Changed += FireChangedEvent;
		_autoMuteMinMessage.Changed += FireChangedEvent;
		_autoMuteMessagePerTime.Changed += FireChangedEvent;
		_autoMuteTimeLimit.Changed += FireChangedEvent;
		_autoMuteMessageLength.Changed += FireChangedEvent;
	}

	public BehaviourTrackerParams()
	{
		Initialize( this );
	}
	private void AssignSelf( BehaviourTrackerParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BehaviourTrackerParams" );
		idleTime = source.idleTime;
		goodActionTimeout = source.goodActionTimeout;
		goodZumaActionTimeout = source.goodZumaActionTimeout;
		feederDeathCount = source.feederDeathCount;
		feederDeathTime = source.feederDeathTime;
		badBehaviourComplaintsThreshold = source.badBehaviourComplaintsThreshold;
		insultComplaintsThreshold = source.insultComplaintsThreshold;
		autoMuteMinMessage = source.autoMuteMinMessage;
		autoMuteMessagePerTime = source.autoMuteMessagePerTime;
		autoMuteTimeLimit = source.autoMuteTimeLimit;
		autoMuteMessageLength = source.autoMuteMessageLength;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BehaviourTrackerParams source = _source as BehaviourTrackerParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BehaviourTrackerParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BehaviourTrackerParams newParent = rawParent == null ? null : rawParent.Get<BehaviourTrackerParams>();
		if ( newParent == null && _newParent is BehaviourTrackerParams )
			newParent = _newParent as BehaviourTrackerParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_idleTime.SetParent( newParent == null ? null : newParent._idleTime );
		_goodActionTimeout.SetParent( newParent == null ? null : newParent._goodActionTimeout );
		_goodZumaActionTimeout.SetParent( newParent == null ? null : newParent._goodZumaActionTimeout );
		_feederDeathCount.SetParent( newParent == null ? null : newParent._feederDeathCount );
		_feederDeathTime.SetParent( newParent == null ? null : newParent._feederDeathTime );
		_badBehaviourComplaintsThreshold.SetParent( newParent == null ? null : newParent._badBehaviourComplaintsThreshold );
		_insultComplaintsThreshold.SetParent( newParent == null ? null : newParent._insultComplaintsThreshold );
		_autoMuteMinMessage.SetParent( newParent == null ? null : newParent._autoMuteMinMessage );
		_autoMuteMessagePerTime.SetParent( newParent == null ? null : newParent._autoMuteMessagePerTime );
		_autoMuteTimeLimit.SetParent( newParent == null ? null : newParent._autoMuteTimeLimit );
		_autoMuteMessageLength.SetParent( newParent == null ? null : newParent._autoMuteMessageLength );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_idleTime.Reset();
		_goodActionTimeout.Reset();
		_goodZumaActionTimeout.Reset();
		_feederDeathCount.Reset();
		_feederDeathTime.Reset();
		_badBehaviourComplaintsThreshold.Reset();
		_insultComplaintsThreshold.Reset();
		_autoMuteMinMessage.Reset();
		_autoMuteMessagePerTime.Reset();
		_autoMuteTimeLimit.Reset();
		_autoMuteMessageLength.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_idleTime.IsDerivedFromParent()
			&& _goodActionTimeout.IsDerivedFromParent()
			&& _goodZumaActionTimeout.IsDerivedFromParent()
			&& _feederDeathCount.IsDerivedFromParent()
			&& _feederDeathTime.IsDerivedFromParent()
			&& _badBehaviourComplaintsThreshold.IsDerivedFromParent()
			&& _insultComplaintsThreshold.IsDerivedFromParent()
			&& _autoMuteMinMessage.IsDerivedFromParent()
			&& _autoMuteMessagePerTime.IsDerivedFromParent()
			&& _autoMuteTimeLimit.IsDerivedFromParent()
			&& _autoMuteMessageLength.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "idleTime" )
			_idleTime.Reset();
		else if ( fieldName == "goodActionTimeout" )
			_goodActionTimeout.Reset();
		else if ( fieldName == "goodZumaActionTimeout" )
			_goodZumaActionTimeout.Reset();
		else if ( fieldName == "feederDeathCount" )
			_feederDeathCount.Reset();
		else if ( fieldName == "feederDeathTime" )
			_feederDeathTime.Reset();
		else if ( fieldName == "badBehaviourComplaintsThreshold" )
			_badBehaviourComplaintsThreshold.Reset();
		else if ( fieldName == "insultComplaintsThreshold" )
			_insultComplaintsThreshold.Reset();
		else if ( fieldName == "autoMuteMinMessage" )
			_autoMuteMinMessage.Reset();
		else if ( fieldName == "autoMuteMessagePerTime" )
			_autoMuteMessagePerTime.Reset();
		else if ( fieldName == "autoMuteTimeLimit" )
			_autoMuteTimeLimit.Reset();
		else if ( fieldName == "autoMuteMessageLength" )
			_autoMuteMessageLength.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "idleTime" )
			return _idleTime.IsDerivedFromParent();
		if ( fieldName == "goodActionTimeout" )
			return _goodActionTimeout.IsDerivedFromParent();
		if ( fieldName == "goodZumaActionTimeout" )
			return _goodZumaActionTimeout.IsDerivedFromParent();
		if ( fieldName == "feederDeathCount" )
			return _feederDeathCount.IsDerivedFromParent();
		if ( fieldName == "feederDeathTime" )
			return _feederDeathTime.IsDerivedFromParent();
		if ( fieldName == "badBehaviourComplaintsThreshold" )
			return _badBehaviourComplaintsThreshold.IsDerivedFromParent();
		if ( fieldName == "insultComplaintsThreshold" )
			return _insultComplaintsThreshold.IsDerivedFromParent();
		if ( fieldName == "autoMuteMinMessage" )
			return _autoMuteMinMessage.IsDerivedFromParent();
		if ( fieldName == "autoMuteMessagePerTime" )
			return _autoMuteMessagePerTime.IsDerivedFromParent();
		if ( fieldName == "autoMuteTimeLimit" )
			return _autoMuteTimeLimit.IsDerivedFromParent();
		if ( fieldName == "autoMuteMessageLength" )
			return _autoMuteMessageLength.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("BOTS")]
public class BotsSettings : DBResource
{
	private UndoRedoDBPtr<BotsSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<BotsSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _manaUsePotionThreshold;
	private UndoRedo<float> _healthUsePotionThreshold;
	private UndoRedo<int> _minShoppingMoney;
	private UndoRedo<int> _maxHealthPotion;
	private UndoRedo<int> _maxManaPotion;
	private UndoRedoAssignableList<DBPtr<Hero>> _doNotBuyMana;
	private UndoRedo<int> _timeToGo;
	private UndoRedo<bool> _midOnly;
	private UndoRedo<bool> _enableBotsAI;
	private UndoRedo<int> _timeToTeleport;
	private UndoRedo<float> _healthFractionToRetreatToBase;
	private UndoRedo<float> _healthToRetreatToBase;
	private UndoRedo<float> _escapeTowerDistance;
	private UndoRedo<float> _healthFractionToMoveToFront;
	private UndoRedo<float> _forcedFollowRange;

	[Description( "Если % маны опуститься ниже, то используем поушен" )]
	public float manaUsePotionThreshold { get { return _manaUsePotionThreshold.Get(); } set { _manaUsePotionThreshold.Set( value ); } }

	[Description( "Если % жизни опуститься ниже, то используем поушен" )]
	public float healthUsePotionThreshold { get { return _healthUsePotionThreshold.Get(); } set { _healthUsePotionThreshold.Set( value ); } }

	[Description( "Наименьшее количество денег с которым бот пойдет в магазин" )]
	public int minShoppingMoney { get { return _minShoppingMoney.Get(); } set { _minShoppingMoney.Set( value ); } }

	[Description( "Максимальное кол-во бутылочек жизни, которое может купить бот" )]
	public int maxHealthPotion { get { return _maxHealthPotion.Get(); } set { _maxHealthPotion.Set( value ); } }

	[Description( "Максимальное кол-во бутылочек маны, которое может купить бот" )]
	public int maxManaPotion { get { return _maxManaPotion.Get(); } set { _maxManaPotion.Set( value ); } }

	[Description( "Список героев, которым не покупать бутылки маны" )]
	public libdb.IChangeableList<DBPtr<Hero>> doNotBuyMana { get { return _doNotBuyMana; } set { _doNotBuyMana.Assign( value ); } }

	[Description( "Время в секундах после которого боты расходятся по лайнам" )]
	public int timeToGo { get { return _timeToGo.Get(); } set { _timeToGo.Set( value ); } }

	[Description( "Боты ходят только по миду" )]
	public bool midOnly { get { return _midOnly.Get(); } set { _midOnly.Set( value ); } }

	[Description( "Enable/disable AI for bots" )]
	public bool enableBotsAI { get { return _enableBotsAI.Get(); } set { _enableBotsAI.Set( value ); } }

	[Description( "Время в секундах после которого боты будут телепортиться" )]
	public int timeToTeleport { get { return _timeToTeleport.Get(); } set { _timeToTeleport.Set( value ); } }

	[Description( "Life fraction value to retreat to base" )]
	public float healthFractionToRetreatToBase { get { return _healthFractionToRetreatToBase.Get(); } set { _healthFractionToRetreatToBase.Set( value ); } }

	[Description( "Life absolute value to retreat to base" )]
	public float healthToRetreatToBase { get { return _healthToRetreatToBase.Get(); } set { _healthToRetreatToBase.Set( value ); } }

	[Description( "Distance along road to run away from attacking tower" )]
	public float escapeTowerDistance { get { return _escapeTowerDistance.Get(); } set { _escapeTowerDistance.Set( value ); } }

	[Description( "Life fraction value to move back to front" )]
	public float healthFractionToMoveToFront { get { return _healthFractionToMoveToFront.Get(); } set { _healthFractionToMoveToFront.Set( value ); } }

	[Description( "Distance to follow unit regardless to attacking units" )]
	public float forcedFollowRange { get { return _forcedFollowRange.Get(); } set { _forcedFollowRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BotsSettings>(owner);
		_manaUsePotionThreshold = new UndoRedo<float>( owner, 0.5f );
		_healthUsePotionThreshold = new UndoRedo<float>( owner, 0.5f );
		_minShoppingMoney = new UndoRedo<int>( owner, 100 );
		_maxHealthPotion = new UndoRedo<int>( owner, 2 );
		_maxManaPotion = new UndoRedo<int>( owner, 1 );
		_doNotBuyMana = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		_timeToGo = new UndoRedo<int>( owner, 45 );
		_midOnly = new UndoRedo<bool>( owner, false );
		_enableBotsAI = new UndoRedo<bool>( owner, true );
		_timeToTeleport = new UndoRedo<int>( owner, 180 );
		_healthFractionToRetreatToBase = new UndoRedo<float>( owner, 0.1f );
		_healthToRetreatToBase = new UndoRedo<float>( owner, 60.0f );
		_escapeTowerDistance = new UndoRedo<float>( owner, 20.0f );
		_healthFractionToMoveToFront = new UndoRedo<float>( owner, 0.8f );
		_forcedFollowRange = new UndoRedo<float>( owner, 20.0f );
		___parent.Changed += FireChangedEvent;
		_manaUsePotionThreshold.Changed += FireChangedEvent;
		_healthUsePotionThreshold.Changed += FireChangedEvent;
		_minShoppingMoney.Changed += FireChangedEvent;
		_maxHealthPotion.Changed += FireChangedEvent;
		_maxManaPotion.Changed += FireChangedEvent;
		_doNotBuyMana.Changed += FireChangedEvent;
		_timeToGo.Changed += FireChangedEvent;
		_midOnly.Changed += FireChangedEvent;
		_enableBotsAI.Changed += FireChangedEvent;
		_timeToTeleport.Changed += FireChangedEvent;
		_healthFractionToRetreatToBase.Changed += FireChangedEvent;
		_healthToRetreatToBase.Changed += FireChangedEvent;
		_escapeTowerDistance.Changed += FireChangedEvent;
		_healthFractionToMoveToFront.Changed += FireChangedEvent;
		_forcedFollowRange.Changed += FireChangedEvent;
	}

	public BotsSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( BotsSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BotsSettings" );
		manaUsePotionThreshold = source.manaUsePotionThreshold;
		healthUsePotionThreshold = source.healthUsePotionThreshold;
		minShoppingMoney = source.minShoppingMoney;
		maxHealthPotion = source.maxHealthPotion;
		maxManaPotion = source.maxManaPotion;
		doNotBuyMana = source.doNotBuyMana;
		timeToGo = source.timeToGo;
		midOnly = source.midOnly;
		enableBotsAI = source.enableBotsAI;
		timeToTeleport = source.timeToTeleport;
		healthFractionToRetreatToBase = source.healthFractionToRetreatToBase;
		healthToRetreatToBase = source.healthToRetreatToBase;
		escapeTowerDistance = source.escapeTowerDistance;
		healthFractionToMoveToFront = source.healthFractionToMoveToFront;
		forcedFollowRange = source.forcedFollowRange;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BotsSettings source = _source as BotsSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BotsSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BotsSettings newParent = rawParent == null ? null : rawParent.Get<BotsSettings>();
		if ( newParent == null && _newParent is BotsSettings )
			newParent = _newParent as BotsSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_manaUsePotionThreshold.SetParent( newParent == null ? null : newParent._manaUsePotionThreshold );
		_healthUsePotionThreshold.SetParent( newParent == null ? null : newParent._healthUsePotionThreshold );
		_minShoppingMoney.SetParent( newParent == null ? null : newParent._minShoppingMoney );
		_maxHealthPotion.SetParent( newParent == null ? null : newParent._maxHealthPotion );
		_maxManaPotion.SetParent( newParent == null ? null : newParent._maxManaPotion );
		_doNotBuyMana.SetParent( newParent == null ? null : newParent._doNotBuyMana );
		_timeToGo.SetParent( newParent == null ? null : newParent._timeToGo );
		_midOnly.SetParent( newParent == null ? null : newParent._midOnly );
		_enableBotsAI.SetParent( newParent == null ? null : newParent._enableBotsAI );
		_timeToTeleport.SetParent( newParent == null ? null : newParent._timeToTeleport );
		_healthFractionToRetreatToBase.SetParent( newParent == null ? null : newParent._healthFractionToRetreatToBase );
		_healthToRetreatToBase.SetParent( newParent == null ? null : newParent._healthToRetreatToBase );
		_escapeTowerDistance.SetParent( newParent == null ? null : newParent._escapeTowerDistance );
		_healthFractionToMoveToFront.SetParent( newParent == null ? null : newParent._healthFractionToMoveToFront );
		_forcedFollowRange.SetParent( newParent == null ? null : newParent._forcedFollowRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_manaUsePotionThreshold.Reset();
		_healthUsePotionThreshold.Reset();
		_minShoppingMoney.Reset();
		_maxHealthPotion.Reset();
		_maxManaPotion.Reset();
		_doNotBuyMana.Reset();
		_timeToGo.Reset();
		_midOnly.Reset();
		_enableBotsAI.Reset();
		_timeToTeleport.Reset();
		_healthFractionToRetreatToBase.Reset();
		_healthToRetreatToBase.Reset();
		_escapeTowerDistance.Reset();
		_healthFractionToMoveToFront.Reset();
		_forcedFollowRange.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_manaUsePotionThreshold.IsDerivedFromParent()
			&& _healthUsePotionThreshold.IsDerivedFromParent()
			&& _minShoppingMoney.IsDerivedFromParent()
			&& _maxHealthPotion.IsDerivedFromParent()
			&& _maxManaPotion.IsDerivedFromParent()
			&& _doNotBuyMana.IsDerivedFromParent()
			&& _timeToGo.IsDerivedFromParent()
			&& _midOnly.IsDerivedFromParent()
			&& _enableBotsAI.IsDerivedFromParent()
			&& _timeToTeleport.IsDerivedFromParent()
			&& _healthFractionToRetreatToBase.IsDerivedFromParent()
			&& _healthToRetreatToBase.IsDerivedFromParent()
			&& _escapeTowerDistance.IsDerivedFromParent()
			&& _healthFractionToMoveToFront.IsDerivedFromParent()
			&& _forcedFollowRange.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "manaUsePotionThreshold" )
			_manaUsePotionThreshold.Reset();
		else if ( fieldName == "healthUsePotionThreshold" )
			_healthUsePotionThreshold.Reset();
		else if ( fieldName == "minShoppingMoney" )
			_minShoppingMoney.Reset();
		else if ( fieldName == "maxHealthPotion" )
			_maxHealthPotion.Reset();
		else if ( fieldName == "maxManaPotion" )
			_maxManaPotion.Reset();
		else if ( fieldName == "doNotBuyMana" )
			_doNotBuyMana.Reset();
		else if ( fieldName == "timeToGo" )
			_timeToGo.Reset();
		else if ( fieldName == "midOnly" )
			_midOnly.Reset();
		else if ( fieldName == "enableBotsAI" )
			_enableBotsAI.Reset();
		else if ( fieldName == "timeToTeleport" )
			_timeToTeleport.Reset();
		else if ( fieldName == "healthFractionToRetreatToBase" )
			_healthFractionToRetreatToBase.Reset();
		else if ( fieldName == "healthToRetreatToBase" )
			_healthToRetreatToBase.Reset();
		else if ( fieldName == "escapeTowerDistance" )
			_escapeTowerDistance.Reset();
		else if ( fieldName == "healthFractionToMoveToFront" )
			_healthFractionToMoveToFront.Reset();
		else if ( fieldName == "forcedFollowRange" )
			_forcedFollowRange.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "manaUsePotionThreshold" )
			return _manaUsePotionThreshold.IsDerivedFromParent();
		if ( fieldName == "healthUsePotionThreshold" )
			return _healthUsePotionThreshold.IsDerivedFromParent();
		if ( fieldName == "minShoppingMoney" )
			return _minShoppingMoney.IsDerivedFromParent();
		if ( fieldName == "maxHealthPotion" )
			return _maxHealthPotion.IsDerivedFromParent();
		if ( fieldName == "maxManaPotion" )
			return _maxManaPotion.IsDerivedFromParent();
		if ( fieldName == "doNotBuyMana" )
			return _doNotBuyMana.IsDerivedFromParent();
		if ( fieldName == "timeToGo" )
			return _timeToGo.IsDerivedFromParent();
		if ( fieldName == "midOnly" )
			return _midOnly.IsDerivedFromParent();
		if ( fieldName == "enableBotsAI" )
			return _enableBotsAI.IsDerivedFromParent();
		if ( fieldName == "timeToTeleport" )
			return _timeToTeleport.IsDerivedFromParent();
		if ( fieldName == "healthFractionToRetreatToBase" )
			return _healthFractionToRetreatToBase.IsDerivedFromParent();
		if ( fieldName == "healthToRetreatToBase" )
			return _healthToRetreatToBase.IsDerivedFromParent();
		if ( fieldName == "escapeTowerDistance" )
			return _escapeTowerDistance.IsDerivedFromParent();
		if ( fieldName == "healthFractionToMoveToFront" )
			return _healthFractionToMoveToFront.IsDerivedFromParent();
		if ( fieldName == "forcedFollowRange" )
			return _forcedFollowRange.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[DBVersion(2)]
[TypeId(0x0F994BC9)]
[UseTypeName("CIBC")]
public class BuyServicesContainer : DBResource
{
	private UndoRedoDBPtr<BuyServicesContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<BuyServicesContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<BuyServiceCost> _services;
	private UndoRedoAssignableList<BuyServiceCost> _buffs;
	private UndoRedoAssignableList<BuyServiceCost> _rewards;

	[EnumArray(typeof(GeneralServices))]
	public libdb.IChangeableList<BuyServiceCost> services { get { return _services; } set { _services.Assign( value ); } }

	[EnumArray(typeof(ImpulseBuffs))]
	public libdb.IChangeableList<BuyServiceCost> buffs { get { return _buffs; } set { _buffs.Assign( value ); } }

	[EnumArray(typeof(ZZRewards))]
	public libdb.IChangeableList<BuyServiceCost> rewards { get { return _rewards; } set { _rewards.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuyServicesContainer>(owner);
		_services = new UndoRedoAssignableList<BuyServiceCost>( owner, typeof( GeneralServices ) );
		_buffs = new UndoRedoAssignableList<BuyServiceCost>( owner, typeof( ImpulseBuffs ) );
		_rewards = new UndoRedoAssignableList<BuyServiceCost>( owner, typeof( ZZRewards ) );
		___parent.Changed += FireChangedEvent;
		_services.Changed += FireChangedEvent;
		_buffs.Changed += FireChangedEvent;
		_rewards.Changed += FireChangedEvent;
	}

	public BuyServicesContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( BuyServicesContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuyServicesContainer" );
		services = source.services;
		buffs = source.buffs;
		rewards = source.rewards;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuyServicesContainer source = _source as BuyServicesContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuyServicesContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuyServicesContainer newParent = rawParent == null ? null : rawParent.Get<BuyServicesContainer>();
		if ( newParent == null && _newParent is BuyServicesContainer )
			newParent = _newParent as BuyServicesContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_services.SetParent( newParent == null ? null : newParent._services );
		_buffs.SetParent( newParent == null ? null : newParent._buffs );
		_rewards.SetParent( newParent == null ? null : newParent._rewards );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_services.Reset();
		_buffs.Reset();
		_rewards.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_services.IsDerivedFromParent()
			&& _buffs.IsDerivedFromParent()
			&& _rewards.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "services" )
			_services.Reset();
		else if ( fieldName == "buffs" )
			_buffs.Reset();
		else if ( fieldName == "rewards" )
			_rewards.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "services" )
			return _services.IsDerivedFromParent();
		if ( fieldName == "buffs" )
			return _buffs.IsDerivedFromParent();
		if ( fieldName == "rewards" )
			return _rewards.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CHLP")]
public class ChatLogicParameters : DBResource
{
	private UndoRedoDBPtr<ChatLogicParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<ChatLogicParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeBeforeDisappearing;
	private UndoRedo<int> _disappearingTime;
	private UndoRedo<float> _backgroundOpacityPermanent;
	private UndoRedo<float> _backgroundOpacityMotion;
	private UndoRedo<string> _channelStyle;
	private UndoRedo<string> _nicknameStyle;
	private UndoRedo<string> _messageStyle;

	[Description( "Time after that the chat message will begin to disappear." )]
	public int timeBeforeDisappearing { get { return _timeBeforeDisappearing.Get(); } set { _timeBeforeDisappearing.Set( value ); } }

	[Description( "The duration of chat message disappearing time." )]
	public int disappearingTime { get { return _disappearingTime.Get(); } set { _disappearingTime.Set( value ); } }

	[Description( "Chat background opacity WITHOUT mouse over. Minimal opacity = 0.0, maximal opacity = 1.0" )]
	public float backgroundOpacityPermanent { get { return _backgroundOpacityPermanent.Get(); } set { _backgroundOpacityPermanent.Set( value ); } }

	[Description( "Chat background opacity WITH mouse over. Minimal opacity = 0.0, maximal opacity = 1.0" )]
	public float backgroundOpacityMotion { get { return _backgroundOpacityMotion.Get(); } set { _backgroundOpacityMotion.Set( value ); } }

	[Description( "UI channel text style" )]
	public string channelStyle { get { return _channelStyle.Get(); } set { _channelStyle.Set( value ); } }

	[Description( "UI nickname text style" )]
	public string nicknameStyle { get { return _nicknameStyle.Get(); } set { _nicknameStyle.Set( value ); } }

	[Description( "UI message text style" )]
	public string messageStyle { get { return _messageStyle.Get(); } set { _messageStyle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChatLogicParameters>(owner);
		_timeBeforeDisappearing = new UndoRedo<int>( owner, 0 );
		_disappearingTime = new UndoRedo<int>( owner, 0 );
		_backgroundOpacityPermanent = new UndoRedo<float>( owner, 0.0f );
		_backgroundOpacityMotion = new UndoRedo<float>( owner, 0.0f );
		_channelStyle = new UndoRedo<string>( owner, string.Empty );
		_nicknameStyle = new UndoRedo<string>( owner, string.Empty );
		_messageStyle = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_timeBeforeDisappearing.Changed += FireChangedEvent;
		_disappearingTime.Changed += FireChangedEvent;
		_backgroundOpacityPermanent.Changed += FireChangedEvent;
		_backgroundOpacityMotion.Changed += FireChangedEvent;
		_channelStyle.Changed += FireChangedEvent;
		_nicknameStyle.Changed += FireChangedEvent;
		_messageStyle.Changed += FireChangedEvent;
	}

	public ChatLogicParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( ChatLogicParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChatLogicParameters" );
		timeBeforeDisappearing = source.timeBeforeDisappearing;
		disappearingTime = source.disappearingTime;
		backgroundOpacityPermanent = source.backgroundOpacityPermanent;
		backgroundOpacityMotion = source.backgroundOpacityMotion;
		channelStyle = source.channelStyle;
		nicknameStyle = source.nicknameStyle;
		messageStyle = source.messageStyle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChatLogicParameters source = _source as ChatLogicParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChatLogicParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChatLogicParameters newParent = rawParent == null ? null : rawParent.Get<ChatLogicParameters>();
		if ( newParent == null && _newParent is ChatLogicParameters )
			newParent = _newParent as ChatLogicParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeBeforeDisappearing.SetParent( newParent == null ? null : newParent._timeBeforeDisappearing );
		_disappearingTime.SetParent( newParent == null ? null : newParent._disappearingTime );
		_backgroundOpacityPermanent.SetParent( newParent == null ? null : newParent._backgroundOpacityPermanent );
		_backgroundOpacityMotion.SetParent( newParent == null ? null : newParent._backgroundOpacityMotion );
		_channelStyle.SetParent( newParent == null ? null : newParent._channelStyle );
		_nicknameStyle.SetParent( newParent == null ? null : newParent._nicknameStyle );
		_messageStyle.SetParent( newParent == null ? null : newParent._messageStyle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeBeforeDisappearing.Reset();
		_disappearingTime.Reset();
		_backgroundOpacityPermanent.Reset();
		_backgroundOpacityMotion.Reset();
		_channelStyle.Reset();
		_nicknameStyle.Reset();
		_messageStyle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeBeforeDisappearing.IsDerivedFromParent()
			&& _disappearingTime.IsDerivedFromParent()
			&& _backgroundOpacityPermanent.IsDerivedFromParent()
			&& _backgroundOpacityMotion.IsDerivedFromParent()
			&& _channelStyle.IsDerivedFromParent()
			&& _nicknameStyle.IsDerivedFromParent()
			&& _messageStyle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeBeforeDisappearing" )
			_timeBeforeDisappearing.Reset();
		else if ( fieldName == "disappearingTime" )
			_disappearingTime.Reset();
		else if ( fieldName == "backgroundOpacityPermanent" )
			_backgroundOpacityPermanent.Reset();
		else if ( fieldName == "backgroundOpacityMotion" )
			_backgroundOpacityMotion.Reset();
		else if ( fieldName == "channelStyle" )
			_channelStyle.Reset();
		else if ( fieldName == "nicknameStyle" )
			_nicknameStyle.Reset();
		else if ( fieldName == "messageStyle" )
			_messageStyle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeBeforeDisappearing" )
			return _timeBeforeDisappearing.IsDerivedFromParent();
		if ( fieldName == "disappearingTime" )
			return _disappearingTime.IsDerivedFromParent();
		if ( fieldName == "backgroundOpacityPermanent" )
			return _backgroundOpacityPermanent.IsDerivedFromParent();
		if ( fieldName == "backgroundOpacityMotion" )
			return _backgroundOpacityMotion.IsDerivedFromParent();
		if ( fieldName == "channelStyle" )
			return _channelStyle.IsDerivedFromParent();
		if ( fieldName == "nicknameStyle" )
			return _nicknameStyle.IsDerivedFromParent();
		if ( fieldName == "messageStyle" )
			return _messageStyle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CGRP")]
public class ConsumableGroupList : DBResource
{
	private UndoRedoDBPtr<ConsumableGroupList> ___parent;
	[HideInOutliner]
	public new DBPtr<ConsumableGroupList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ConsumableGroup> _groups;

	public libdb.IChangeableList<ConsumableGroup> groups { get { return _groups; } set { _groups.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConsumableGroupList>(owner);
		_groups = new UndoRedoAssignableList<ConsumableGroup>( owner );
		___parent.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
	}

	public ConsumableGroupList()
	{
		Initialize( this );
	}
	private void AssignSelf( ConsumableGroupList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConsumableGroupList" );
		groups = source.groups;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConsumableGroupList source = _source as ConsumableGroupList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConsumableGroupList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConsumableGroupList newParent = rawParent == null ? null : rawParent.Get<ConsumableGroupList>();
		if ( newParent == null && _newParent is ConsumableGroupList )
			newParent = _newParent as ConsumableGroupList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_groups.SetParent( newParent == null ? null : newParent._groups );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_groups.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_groups.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "groups" )
			_groups.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("GM")]
public class DBGameMenu : DBResource
{
	private UndoRedoDBPtr<DBGameMenu> ___parent;
	[HideInOutliner]
	public new DBPtr<DBGameMenu> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<GameMenuItem> _menuItems;

	[Description( "List of menu items." )]
	public libdb.IChangeableList<GameMenuItem> menuItems { get { return _menuItems; } set { _menuItems.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBGameMenu>(owner);
		_menuItems = new UndoRedoAssignableList<GameMenuItem>( owner );
		___parent.Changed += FireChangedEvent;
		_menuItems.Changed += FireChangedEvent;
	}

	public DBGameMenu()
	{
		Initialize( this );
	}
	private void AssignSelf( DBGameMenu source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBGameMenu" );
		menuItems = source.menuItems;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBGameMenu source = _source as DBGameMenu;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBGameMenu" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBGameMenu newParent = rawParent == null ? null : rawParent.Get<DBGameMenu>();
		if ( newParent == null && _newParent is DBGameMenu )
			newParent = _newParent as DBGameMenu;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_menuItems.SetParent( newParent == null ? null : newParent._menuItems );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_menuItems.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_menuItems.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "menuItems" )
			_menuItems.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "menuItems" )
			return _menuItems.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class DBLevelToExperience : DBResource
{
	private UndoRedoDBPtr<DBLevelToExperience> ___parent;
	[HideInOutliner]
	public new DBPtr<DBLevelToExperience> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<int> _Levels;

	public libdb.IChangeableList<int> Levels { get { return _Levels; } set { _Levels.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBLevelToExperience>(owner);
		_Levels = new UndoRedoList<int>( owner );
		___parent.Changed += FireChangedEvent;
		_Levels.Changed += FireChangedEvent;
	}

	public DBLevelToExperience()
	{
		Initialize( this );
	}
	private void AssignSelf( DBLevelToExperience source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBLevelToExperience" );
		Levels = source.Levels;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBLevelToExperience source = _source as DBLevelToExperience;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBLevelToExperience" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBLevelToExperience newParent = rawParent == null ? null : rawParent.Get<DBLevelToExperience>();
		if ( newParent == null && _newParent is DBLevelToExperience )
			newParent = _newParent as DBLevelToExperience;
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
public class DBRatingToFame : DBResource
{
	private UndoRedoDBPtr<DBRatingToFame> ___parent;
	[HideInOutliner]
	public new DBPtr<DBRatingToFame> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBFameRatingPair> _Ratings;

	public libdb.IChangeableList<DBFameRatingPair> Ratings { get { return _Ratings; } set { _Ratings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBRatingToFame>(owner);
		_Ratings = new UndoRedoAssignableList<DBFameRatingPair>( owner );
		___parent.Changed += FireChangedEvent;
		_Ratings.Changed += FireChangedEvent;
	}

	public DBRatingToFame()
	{
		Initialize( this );
	}
	private void AssignSelf( DBRatingToFame source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBRatingToFame" );
		Ratings = source.Ratings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBRatingToFame source = _source as DBRatingToFame;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBRatingToFame" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBRatingToFame newParent = rawParent == null ? null : rawParent.Get<DBRatingToFame>();
		if ( newParent == null && _newParent is DBRatingToFame )
			newParent = _newParent as DBRatingToFame;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Ratings.SetParent( newParent == null ? null : newParent._Ratings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Ratings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Ratings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Ratings" )
			_Ratings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Ratings" )
			return _Ratings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(2)]
public class ForceParameters : DBResource
{
	private UndoRedoDBPtr<ForceParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<ForceParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<float> _talentLevelForceModifiers;
	private UndoRedoList<float> _talentRarityForceModifiers;
	private UndoRedoList<float> _talentRarityForceSummand;
	private UndoRedoList<float> _classTalentLevelForceModifiers;
	private UndoRedo<float> _talentForceBonusPerStar;
	private UndoRedo<float> _classTalentForceBonusPerStar;
	private UndoRedoList<float> _talentLevelBonusPercent;
	private UndoRedo<float> _baseHeroForce;
	private UndoRedo<float> _defaultBaseForce;
	private UndoRedo<float> _masteryPointForce;
	private UndoRedo<float> _statBonusByForce;
	private UndoRedo<float> _defaultStatBonus;
	private UndoRedo<TeamForceCalcMethod> _teamForceCalcMethod;
	private UndoRedo<float> _mapHabitantsStatsMultiplier;
	private UndoRedo<float> _trainingBotsStatsMultiplier;
	private UndoRedo<float> _talentForceModifier;
	private UndoRedo<float> _seriesMapHabitantsStatsMultiplier;
	private UndoRedo<float> _maxHeroForce;

	[Description( "Таблица модификаторов ТУРа неклассовых талантов для вычисления Мощи" )]
	[EnumArray(typeof(ETalentLevel))]
	public libdb.IChangeableList<float> talentLevelForceModifiers { get { return _talentLevelForceModifiers; } set { _talentLevelForceModifiers.Assign( value ); } }

	[Description( "Таблица модификаторов РАРов для вычисления Мощи" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<float> talentRarityForceModifiers { get { return _talentRarityForceModifiers; } set { _talentRarityForceModifiers.Assign( value ); } }

	[Description( "Таблица добавляемых значений РАРов для вычисления Мощи" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<float> talentRarityForceSummand { get { return _talentRarityForceSummand; } set { _talentRarityForceSummand.Assign( value ); } }

	[Description( "Таблица модификаторов ТУРа классовых талантов для вычисления Мощи" )]
	[EnumArray(typeof(ETalentLevel))]
	public libdb.IChangeableList<float> classTalentLevelForceModifiers { get { return _classTalentLevelForceModifiers; } set { _classTalentLevelForceModifiers.Assign( value ); } }

	[Description( "% увеличения бюджета за звезду" )]
	public float talentForceBonusPerStar { get { return _talentForceBonusPerStar.Get(); } set { _talentForceBonusPerStar.Set( value ); } }

	[Description( "% увеличения бюджета за звезду для классовых талантов" )]
	public float classTalentForceBonusPerStar { get { return _classTalentForceBonusPerStar.Get(); } set { _classTalentForceBonusPerStar.Set( value ); } }

	[Description( "% от общего Суммарного бонуса" )]
	[EnumArray(typeof(ETalentLevel))]
	public libdb.IChangeableList<float> talentLevelBonusPercent { get { return _talentLevelBonusPercent; } set { _talentLevelBonusPercent.Assign( value ); } }

	[Description( "Базовая мощь героя" )]
	public float baseHeroForce { get { return _baseHeroForce.Get(); } set { _baseHeroForce.Set( value ); } }

	[Description( "Стандартная мощь для обобщённого героя" )]
	public float defaultBaseForce { get { return _defaultBaseForce.Get(); } set { _defaultBaseForce.Set( value ); } }

	[Description( "Мощь от единицы мастерства" )]
	public float masteryPointForce { get { return _masteryPointForce.Get(); } set { _masteryPointForce.Set( value ); } }

	[Description( "Бонус от мощи к статам" )]
	public float statBonusByForce { get { return _statBonusByForce.Get(); } set { _statBonusByForce.Set( value ); } }

	[Description( "Дефолтовый бонус к статам" )]
	public float defaultStatBonus { get { return _defaultStatBonus.Get(); } set { _defaultStatBonus.Set( value ); } }

	[Description( "Способ вычисления мощи команды героев" )]
	public TeamForceCalcMethod teamForceCalcMethod { get { return _teamForceCalcMethod.Get(); } set { _teamForceCalcMethod.Set( value ); } }

	[Description( "Множитель на отношение мощи команды героев к мощи карты" )]
	public float mapHabitantsStatsMultiplier { get { return _mapHabitantsStatsMultiplier.Get(); } set { _mapHabitantsStatsMultiplier.Set( value ); } }

	[Description( "Множитель на отношение мощи ботов к мощи карты" )]
	public float trainingBotsStatsMultiplier { get { return _trainingBotsStatsMultiplier.Get(); } set { _trainingBotsStatsMultiplier.Set( value ); } }

	[Description( "Коэфицент для регулировки влияния бюджета на мощь" )]
	public float talentForceModifier { get { return _talentForceModifier.Get(); } set { _talentForceModifier.Set( value ); } }

	[Description( "Для Series карт. Множитель на отношение мощи героя к мощи карты" )]
	public float seriesMapHabitantsStatsMultiplier { get { return _seriesMapHabitantsStatsMultiplier.Get(); } set { _seriesMapHabitantsStatsMultiplier.Set( value ); } }

	[Description( "Ограничение на мощь команды" )]
	public float maxHeroForce { get { return _maxHeroForce.Get(); } set { _maxHeroForce.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ForceParameters>(owner);
		_talentLevelForceModifiers = new UndoRedoList<float>( owner, typeof( ETalentLevel ) );
		_talentRarityForceModifiers = new UndoRedoList<float>( owner, typeof( ETalentRarity ) );
		_talentRarityForceSummand = new UndoRedoList<float>( owner, typeof( ETalentRarity ) );
		_classTalentLevelForceModifiers = new UndoRedoList<float>( owner, typeof( ETalentLevel ) );
		_talentForceBonusPerStar = new UndoRedo<float>( owner, 5.0f );
		_classTalentForceBonusPerStar = new UndoRedo<float>( owner, 5.0f );
		_talentLevelBonusPercent = new UndoRedoList<float>( owner, typeof( ETalentLevel ) );
		_baseHeroForce = new UndoRedo<float>( owner, 0.0f );
		_defaultBaseForce = new UndoRedo<float>( owner, 100.0f );
		_masteryPointForce = new UndoRedo<float>( owner, 1.0f );
		_statBonusByForce = new UndoRedo<float>( owner, 1.27f );
		_defaultStatBonus = new UndoRedo<float>( owner, 252.0f );
		_teamForceCalcMethod = new UndoRedo<TeamForceCalcMethod>( owner, TeamForceCalcMethod.Minimum );
		_mapHabitantsStatsMultiplier = new UndoRedo<float>( owner, 0.55f );
		_trainingBotsStatsMultiplier = new UndoRedo<float>( owner, 0.6f );
		_talentForceModifier = new UndoRedo<float>( owner, 1.1f );
		_seriesMapHabitantsStatsMultiplier = new UndoRedo<float>( owner, 0.7f );
		_maxHeroForce = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_talentLevelForceModifiers.Changed += FireChangedEvent;
		_talentRarityForceModifiers.Changed += FireChangedEvent;
		_talentRarityForceSummand.Changed += FireChangedEvent;
		_classTalentLevelForceModifiers.Changed += FireChangedEvent;
		_talentForceBonusPerStar.Changed += FireChangedEvent;
		_classTalentForceBonusPerStar.Changed += FireChangedEvent;
		_talentLevelBonusPercent.Changed += FireChangedEvent;
		_baseHeroForce.Changed += FireChangedEvent;
		_defaultBaseForce.Changed += FireChangedEvent;
		_masteryPointForce.Changed += FireChangedEvent;
		_statBonusByForce.Changed += FireChangedEvent;
		_defaultStatBonus.Changed += FireChangedEvent;
		_teamForceCalcMethod.Changed += FireChangedEvent;
		_mapHabitantsStatsMultiplier.Changed += FireChangedEvent;
		_trainingBotsStatsMultiplier.Changed += FireChangedEvent;
		_talentForceModifier.Changed += FireChangedEvent;
		_seriesMapHabitantsStatsMultiplier.Changed += FireChangedEvent;
		_maxHeroForce.Changed += FireChangedEvent;
	}

	public ForceParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( ForceParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ForceParameters" );
		talentLevelForceModifiers = source.talentLevelForceModifiers;
		talentRarityForceModifiers = source.talentRarityForceModifiers;
		talentRarityForceSummand = source.talentRarityForceSummand;
		classTalentLevelForceModifiers = source.classTalentLevelForceModifiers;
		talentForceBonusPerStar = source.talentForceBonusPerStar;
		classTalentForceBonusPerStar = source.classTalentForceBonusPerStar;
		talentLevelBonusPercent = source.talentLevelBonusPercent;
		baseHeroForce = source.baseHeroForce;
		defaultBaseForce = source.defaultBaseForce;
		masteryPointForce = source.masteryPointForce;
		statBonusByForce = source.statBonusByForce;
		defaultStatBonus = source.defaultStatBonus;
		teamForceCalcMethod = source.teamForceCalcMethod;
		mapHabitantsStatsMultiplier = source.mapHabitantsStatsMultiplier;
		trainingBotsStatsMultiplier = source.trainingBotsStatsMultiplier;
		talentForceModifier = source.talentForceModifier;
		seriesMapHabitantsStatsMultiplier = source.seriesMapHabitantsStatsMultiplier;
		maxHeroForce = source.maxHeroForce;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ForceParameters source = _source as ForceParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ForceParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ForceParameters newParent = rawParent == null ? null : rawParent.Get<ForceParameters>();
		if ( newParent == null && _newParent is ForceParameters )
			newParent = _newParent as ForceParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_talentLevelForceModifiers.SetParent( newParent == null ? null : newParent._talentLevelForceModifiers );
		_talentRarityForceModifiers.SetParent( newParent == null ? null : newParent._talentRarityForceModifiers );
		_talentRarityForceSummand.SetParent( newParent == null ? null : newParent._talentRarityForceSummand );
		_classTalentLevelForceModifiers.SetParent( newParent == null ? null : newParent._classTalentLevelForceModifiers );
		_talentForceBonusPerStar.SetParent( newParent == null ? null : newParent._talentForceBonusPerStar );
		_classTalentForceBonusPerStar.SetParent( newParent == null ? null : newParent._classTalentForceBonusPerStar );
		_talentLevelBonusPercent.SetParent( newParent == null ? null : newParent._talentLevelBonusPercent );
		_baseHeroForce.SetParent( newParent == null ? null : newParent._baseHeroForce );
		_defaultBaseForce.SetParent( newParent == null ? null : newParent._defaultBaseForce );
		_masteryPointForce.SetParent( newParent == null ? null : newParent._masteryPointForce );
		_statBonusByForce.SetParent( newParent == null ? null : newParent._statBonusByForce );
		_defaultStatBonus.SetParent( newParent == null ? null : newParent._defaultStatBonus );
		_teamForceCalcMethod.SetParent( newParent == null ? null : newParent._teamForceCalcMethod );
		_mapHabitantsStatsMultiplier.SetParent( newParent == null ? null : newParent._mapHabitantsStatsMultiplier );
		_trainingBotsStatsMultiplier.SetParent( newParent == null ? null : newParent._trainingBotsStatsMultiplier );
		_talentForceModifier.SetParent( newParent == null ? null : newParent._talentForceModifier );
		_seriesMapHabitantsStatsMultiplier.SetParent( newParent == null ? null : newParent._seriesMapHabitantsStatsMultiplier );
		_maxHeroForce.SetParent( newParent == null ? null : newParent._maxHeroForce );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_talentLevelForceModifiers.Reset();
		_talentRarityForceModifiers.Reset();
		_talentRarityForceSummand.Reset();
		_classTalentLevelForceModifiers.Reset();
		_talentForceBonusPerStar.Reset();
		_classTalentForceBonusPerStar.Reset();
		_talentLevelBonusPercent.Reset();
		_baseHeroForce.Reset();
		_defaultBaseForce.Reset();
		_masteryPointForce.Reset();
		_statBonusByForce.Reset();
		_defaultStatBonus.Reset();
		_teamForceCalcMethod.Reset();
		_mapHabitantsStatsMultiplier.Reset();
		_trainingBotsStatsMultiplier.Reset();
		_talentForceModifier.Reset();
		_seriesMapHabitantsStatsMultiplier.Reset();
		_maxHeroForce.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_talentLevelForceModifiers.IsDerivedFromParent()
			&& _talentRarityForceModifiers.IsDerivedFromParent()
			&& _talentRarityForceSummand.IsDerivedFromParent()
			&& _classTalentLevelForceModifiers.IsDerivedFromParent()
			&& _talentForceBonusPerStar.IsDerivedFromParent()
			&& _classTalentForceBonusPerStar.IsDerivedFromParent()
			&& _talentLevelBonusPercent.IsDerivedFromParent()
			&& _baseHeroForce.IsDerivedFromParent()
			&& _defaultBaseForce.IsDerivedFromParent()
			&& _masteryPointForce.IsDerivedFromParent()
			&& _statBonusByForce.IsDerivedFromParent()
			&& _defaultStatBonus.IsDerivedFromParent()
			&& _teamForceCalcMethod.IsDerivedFromParent()
			&& _mapHabitantsStatsMultiplier.IsDerivedFromParent()
			&& _trainingBotsStatsMultiplier.IsDerivedFromParent()
			&& _talentForceModifier.IsDerivedFromParent()
			&& _seriesMapHabitantsStatsMultiplier.IsDerivedFromParent()
			&& _maxHeroForce.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "talentLevelForceModifiers" )
			_talentLevelForceModifiers.Reset();
		else if ( fieldName == "talentRarityForceModifiers" )
			_talentRarityForceModifiers.Reset();
		else if ( fieldName == "talentRarityForceSummand" )
			_talentRarityForceSummand.Reset();
		else if ( fieldName == "classTalentLevelForceModifiers" )
			_classTalentLevelForceModifiers.Reset();
		else if ( fieldName == "talentForceBonusPerStar" )
			_talentForceBonusPerStar.Reset();
		else if ( fieldName == "classTalentForceBonusPerStar" )
			_classTalentForceBonusPerStar.Reset();
		else if ( fieldName == "talentLevelBonusPercent" )
			_talentLevelBonusPercent.Reset();
		else if ( fieldName == "baseHeroForce" )
			_baseHeroForce.Reset();
		else if ( fieldName == "defaultBaseForce" )
			_defaultBaseForce.Reset();
		else if ( fieldName == "masteryPointForce" )
			_masteryPointForce.Reset();
		else if ( fieldName == "statBonusByForce" )
			_statBonusByForce.Reset();
		else if ( fieldName == "defaultStatBonus" )
			_defaultStatBonus.Reset();
		else if ( fieldName == "teamForceCalcMethod" )
			_teamForceCalcMethod.Reset();
		else if ( fieldName == "mapHabitantsStatsMultiplier" )
			_mapHabitantsStatsMultiplier.Reset();
		else if ( fieldName == "trainingBotsStatsMultiplier" )
			_trainingBotsStatsMultiplier.Reset();
		else if ( fieldName == "talentForceModifier" )
			_talentForceModifier.Reset();
		else if ( fieldName == "seriesMapHabitantsStatsMultiplier" )
			_seriesMapHabitantsStatsMultiplier.Reset();
		else if ( fieldName == "maxHeroForce" )
			_maxHeroForce.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "talentLevelForceModifiers" )
			return _talentLevelForceModifiers.IsDerivedFromParent();
		if ( fieldName == "talentRarityForceModifiers" )
			return _talentRarityForceModifiers.IsDerivedFromParent();
		if ( fieldName == "talentRarityForceSummand" )
			return _talentRarityForceSummand.IsDerivedFromParent();
		if ( fieldName == "classTalentLevelForceModifiers" )
			return _classTalentLevelForceModifiers.IsDerivedFromParent();
		if ( fieldName == "talentForceBonusPerStar" )
			return _talentForceBonusPerStar.IsDerivedFromParent();
		if ( fieldName == "classTalentForceBonusPerStar" )
			return _classTalentForceBonusPerStar.IsDerivedFromParent();
		if ( fieldName == "talentLevelBonusPercent" )
			return _talentLevelBonusPercent.IsDerivedFromParent();
		if ( fieldName == "baseHeroForce" )
			return _baseHeroForce.IsDerivedFromParent();
		if ( fieldName == "defaultBaseForce" )
			return _defaultBaseForce.IsDerivedFromParent();
		if ( fieldName == "masteryPointForce" )
			return _masteryPointForce.IsDerivedFromParent();
		if ( fieldName == "statBonusByForce" )
			return _statBonusByForce.IsDerivedFromParent();
		if ( fieldName == "defaultStatBonus" )
			return _defaultStatBonus.IsDerivedFromParent();
		if ( fieldName == "teamForceCalcMethod" )
			return _teamForceCalcMethod.IsDerivedFromParent();
		if ( fieldName == "mapHabitantsStatsMultiplier" )
			return _mapHabitantsStatsMultiplier.IsDerivedFromParent();
		if ( fieldName == "trainingBotsStatsMultiplier" )
			return _trainingBotsStatsMultiplier.IsDerivedFromParent();
		if ( fieldName == "talentForceModifier" )
			return _talentForceModifier.IsDerivedFromParent();
		if ( fieldName == "seriesMapHabitantsStatsMultiplier" )
			return _seriesMapHabitantsStatsMultiplier.IsDerivedFromParent();
		if ( fieldName == "maxHeroForce" )
			return _maxHeroForce.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("HRESP")]
public class HeroRespawnParams : DBResource
{
	private UndoRedoDBPtr<HeroRespawnParams> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroRespawnParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _heroRespawnDelayMultiplier;
	private UndoRedo<float> _heroMinRespawnTime;
	private UndoRedo<float> _heroBaseRespawnTime;
	private OvertimeRespawnParams _overtimeRespawnParams;

	[Description( "Множитель для формулы задержки времени воскрешения (умножается на уровень героя)" )]
	public float heroRespawnDelayMultiplier { get { return _heroRespawnDelayMultiplier.Get(); } set { _heroRespawnDelayMultiplier.Set( value ); } }

	[Description( "Минимальное время возрождения героя. Значение level * heroRespawnDelayMultiplier * reviveTimeScale  не может быть меньше указанного в heroMinRespawnTime" )]
	public float heroMinRespawnTime { get { return _heroMinRespawnTime.Get(); } set { _heroMinRespawnTime.Set( value ); } }

	[Description( "Базовое время возрождение к которому будут добавлятся все остальные модификаторы" )]
	public float heroBaseRespawnTime { get { return _heroBaseRespawnTime.Get(); } set { _heroBaseRespawnTime.Set( value ); } }

	public OvertimeRespawnParams overtimeRespawnParams { get { return _overtimeRespawnParams; } set { _overtimeRespawnParams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroRespawnParams>(owner);
		_heroRespawnDelayMultiplier = new UndoRedo<float>( owner, 5.0f );
		_heroMinRespawnTime = new UndoRedo<float>( owner, 6.0f );
		_heroBaseRespawnTime = new UndoRedo<float>( owner, 5.0f );
		_overtimeRespawnParams = new OvertimeRespawnParams( owner );
		___parent.Changed += FireChangedEvent;
		_heroRespawnDelayMultiplier.Changed += FireChangedEvent;
		_heroMinRespawnTime.Changed += FireChangedEvent;
		_heroBaseRespawnTime.Changed += FireChangedEvent;
		_overtimeRespawnParams.Changed += FireChangedEvent;
	}

	public HeroRespawnParams()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroRespawnParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroRespawnParams" );
		heroRespawnDelayMultiplier = source.heroRespawnDelayMultiplier;
		heroMinRespawnTime = source.heroMinRespawnTime;
		heroBaseRespawnTime = source.heroBaseRespawnTime;
		overtimeRespawnParams = source.overtimeRespawnParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroRespawnParams source = _source as HeroRespawnParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroRespawnParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroRespawnParams newParent = rawParent == null ? null : rawParent.Get<HeroRespawnParams>();
		if ( newParent == null && _newParent is HeroRespawnParams )
			newParent = _newParent as HeroRespawnParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroRespawnDelayMultiplier.SetParent( newParent == null ? null : newParent._heroRespawnDelayMultiplier );
		_heroMinRespawnTime.SetParent( newParent == null ? null : newParent._heroMinRespawnTime );
		_heroBaseRespawnTime.SetParent( newParent == null ? null : newParent._heroBaseRespawnTime );
		_overtimeRespawnParams.SetParent( newParent == null ? null : newParent._overtimeRespawnParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroRespawnDelayMultiplier.Reset();
		_heroMinRespawnTime.Reset();
		_heroBaseRespawnTime.Reset();
		_overtimeRespawnParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroRespawnDelayMultiplier.IsDerivedFromParent()
			&& _heroMinRespawnTime.IsDerivedFromParent()
			&& _heroBaseRespawnTime.IsDerivedFromParent()
			&& _overtimeRespawnParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroRespawnDelayMultiplier" )
			_heroRespawnDelayMultiplier.Reset();
		else if ( fieldName == "heroMinRespawnTime" )
			_heroMinRespawnTime.Reset();
		else if ( fieldName == "heroBaseRespawnTime" )
			_heroBaseRespawnTime.Reset();
		else if ( fieldName == "overtimeRespawnParams" )
			_overtimeRespawnParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroRespawnDelayMultiplier" )
			return _heroRespawnDelayMultiplier.IsDerivedFromParent();
		if ( fieldName == "heroMinRespawnTime" )
			return _heroMinRespawnTime.IsDerivedFromParent();
		if ( fieldName == "heroBaseRespawnTime" )
			return _heroBaseRespawnTime.IsDerivedFromParent();
		if ( fieldName == "overtimeRespawnParams" )
			return _overtimeRespawnParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Construct", "PF_Minigames::IMinigamesMain")]
public class MinigamesBasic : DBResource
{
	private UndoRedoDBPtr<MinigamesBasic> ___parent;
	[HideInOutliner]
	public new DBPtr<MinigamesBasic> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinigamesBasic>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public MinigamesBasic()
	{
		Initialize( this );
	}
	private void AssignSelf( MinigamesBasic source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinigamesBasic" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinigamesBasic source = _source as MinigamesBasic;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinigamesBasic" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinigamesBasic newParent = rawParent == null ? null : rawParent.Get<MinigamesBasic>();
		if ( newParent == null && _newParent is MinigamesBasic )
			newParent = _newParent as MinigamesBasic;
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

[UseTypeName("TGRP")]
public class TalentGroupList : DBResource
{
	private UndoRedoDBPtr<TalentGroupList> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentGroupList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TalentGroup> _groups;

	public libdb.IChangeableList<TalentGroup> groups { get { return _groups; } set { _groups.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentGroupList>(owner);
		_groups = new UndoRedoAssignableList<TalentGroup>( owner );
		___parent.Changed += FireChangedEvent;
		_groups.Changed += FireChangedEvent;
	}

	public TalentGroupList()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentGroupList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentGroupList" );
		groups = source.groups;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentGroupList source = _source as TalentGroupList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentGroupList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentGroupList newParent = rawParent == null ? null : rawParent.Get<TalentGroupList>();
		if ( newParent == null && _newParent is TalentGroupList )
			newParent = _newParent as TalentGroupList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_groups.SetParent( newParent == null ? null : newParent._groups );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_groups.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_groups.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "groups" )
			_groups.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("TKLIST")]
public class TalentKitList : DBResource
{
	private UndoRedoDBPtr<TalentKitList> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentKitList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<TalentKit>> _kits;

	public libdb.IChangeableList<DBPtr<TalentKit>> kits { get { return _kits; } set { _kits.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentKitList>(owner);
		_kits = new UndoRedoAssignableList<DBPtr<TalentKit>>( owner );
		___parent.Changed += FireChangedEvent;
		_kits.Changed += FireChangedEvent;
	}

	public TalentKitList()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentKitList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentKitList" );
		kits = source.kits;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentKitList source = _source as TalentKitList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentKitList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentKitList newParent = rawParent == null ? null : rawParent.Get<TalentKitList>();
		if ( newParent == null && _newParent is TalentKitList )
			newParent = _newParent as TalentKitList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_kits.SetParent( newParent == null ? null : newParent._kits );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_kits.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_kits.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "kits" )
			_kits.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "kits" )
			return _kits.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("TPKLIST")]
public class TalentPackList : DBResource
{
	private UndoRedoDBPtr<TalentPackList> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentPackList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<TalentPack>> _packs;

	public libdb.IChangeableList<DBPtr<TalentPack>> packs { get { return _packs; } set { _packs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentPackList>(owner);
		_packs = new UndoRedoAssignableList<DBPtr<TalentPack>>( owner );
		___parent.Changed += FireChangedEvent;
		_packs.Changed += FireChangedEvent;
	}

	public TalentPackList()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentPackList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentPackList" );
		packs = source.packs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentPackList source = _source as TalentPackList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentPackList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentPackList newParent = rawParent == null ? null : rawParent.Get<TalentPackList>();
		if ( newParent == null && _newParent is TalentPackList )
			newParent = _newParent as TalentPackList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_packs.SetParent( newParent == null ? null : newParent._packs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_packs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_packs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "packs" )
			_packs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "packs" )
			return _packs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[UseTypeName("TCS")]
public class TeamsColoringScheme : DBResource
{
	private UndoRedoDBPtr<TeamsColoringScheme> ___parent;
	[HideInOutliner]
	public new DBPtr<TeamsColoringScheme> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TeamColors _teamA;
	private TeamColors _teamB;

	public TeamColors teamA { get { return _teamA; } set { _teamA.Assign( value ); } }

	public TeamColors teamB { get { return _teamB; } set { _teamB.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TeamsColoringScheme>(owner);
		_teamA = new TeamColors( owner );
		_teamB = new TeamColors( owner );
		___parent.Changed += FireChangedEvent;
		_teamA.Changed += FireChangedEvent;
		_teamB.Changed += FireChangedEvent;
	}

	public TeamsColoringScheme()
	{
		Initialize( this );
	}
	private void AssignSelf( TeamsColoringScheme source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TeamsColoringScheme" );
		teamA = source.teamA;
		teamB = source.teamB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TeamsColoringScheme source = _source as TeamsColoringScheme;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TeamsColoringScheme" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TeamsColoringScheme newParent = rawParent == null ? null : rawParent.Get<TeamsColoringScheme>();
		if ( newParent == null && _newParent is TeamsColoringScheme )
			newParent = _newParent as TeamsColoringScheme;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_teamA.SetParent( newParent == null ? null : newParent._teamA );
		_teamB.SetParent( newParent == null ? null : newParent._teamB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_teamA.Reset();
		_teamB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_teamA.IsDerivedFromParent()
			&& _teamB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "teamA" )
			_teamA.Reset();
		else if ( fieldName == "teamB" )
			_teamB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "teamA" )
			return _teamA.IsDerivedFromParent();
		if ( fieldName == "teamB" )
			return _teamB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[UseTypeName("UNDP")]
public class UnitDeathParameters : DBResource
{
	private UndoRedoDBPtr<UnitDeathParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitDeathParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _fallOffset;
	private UndoRedo<float> _fallSpeed;
	private UndoRedo<float> _deathTime;
	private UndoRedo<float> _unsummonTime;
	private UndoRedo<float> _observeOffset;
	private UndoRedo<float> _effectOffset;
	private UndoRedoDBPtr<EffectBase> _effect;

	[Category( "Corpses" )]
	[Description( "Time offset in seconds then need to start put fall throught terrain after unit death" )]
	public float fallOffset { get { return _fallOffset.Get(); } set { _fallOffset.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Speed of dead unit fall throught terrain (m/s)" )]
	public float fallSpeed { get { return _fallSpeed.Get(); } set { _fallSpeed.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Time offset in seconds then need to remove unit from world after death" )]
	public float deathTime { get { return _deathTime.Get(); } set { _deathTime.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Time offset in seconds then need to remove unit from world after unsummon" )]
	public float unsummonTime { get { return _unsummonTime.Get(); } set { _unsummonTime.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Time offset in seconds after logical death of the unit before visibility will be removed" )]
	public float observeOffset { get { return _observeOffset.Get(); } set { _observeOffset.Set( value ); } }

	[Category( "Corpses" )]
	[Description( "Time offset in seconds then need play unit die effect after diying animation ends" )]
	public float effectOffset { get { return _effectOffset.Get(); } set { _effectOffset.Set( value ); } }

	[Category( "Dead Effect" )]
	public DBPtr<EffectBase> effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitDeathParameters>(owner);
		_fallOffset = new UndoRedo<float>( owner, 4.5f );
		_fallSpeed = new UndoRedo<float>( owner, 0.5f );
		_deathTime = new UndoRedo<float>( owner, 5.0f );
		_unsummonTime = new UndoRedo<float>( owner, 0.5f );
		_observeOffset = new UndoRedo<float>( owner, 5.0f );
		_effectOffset = new UndoRedo<float>( owner, 0.5f );
		_effect = new UndoRedoDBPtr<EffectBase>( owner );
		___parent.Changed += FireChangedEvent;
		_fallOffset.Changed += FireChangedEvent;
		_fallSpeed.Changed += FireChangedEvent;
		_deathTime.Changed += FireChangedEvent;
		_unsummonTime.Changed += FireChangedEvent;
		_observeOffset.Changed += FireChangedEvent;
		_effectOffset.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
	}

	public UnitDeathParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitDeathParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitDeathParameters" );
		fallOffset = source.fallOffset;
		fallSpeed = source.fallSpeed;
		deathTime = source.deathTime;
		unsummonTime = source.unsummonTime;
		observeOffset = source.observeOffset;
		effectOffset = source.effectOffset;
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitDeathParameters source = _source as UnitDeathParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitDeathParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitDeathParameters newParent = rawParent == null ? null : rawParent.Get<UnitDeathParameters>();
		if ( newParent == null && _newParent is UnitDeathParameters )
			newParent = _newParent as UnitDeathParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fallOffset.SetParent( newParent == null ? null : newParent._fallOffset );
		_fallSpeed.SetParent( newParent == null ? null : newParent._fallSpeed );
		_deathTime.SetParent( newParent == null ? null : newParent._deathTime );
		_unsummonTime.SetParent( newParent == null ? null : newParent._unsummonTime );
		_observeOffset.SetParent( newParent == null ? null : newParent._observeOffset );
		_effectOffset.SetParent( newParent == null ? null : newParent._effectOffset );
		_effect.SetParent( newParent == null ? null : newParent._effect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fallOffset.Reset();
		_fallSpeed.Reset();
		_deathTime.Reset();
		_unsummonTime.Reset();
		_observeOffset.Reset();
		_effectOffset.Reset();
		_effect.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fallOffset.IsDerivedFromParent()
			&& _fallSpeed.IsDerivedFromParent()
			&& _deathTime.IsDerivedFromParent()
			&& _unsummonTime.IsDerivedFromParent()
			&& _observeOffset.IsDerivedFromParent()
			&& _effectOffset.IsDerivedFromParent()
			&& _effect.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fallOffset" )
			_fallOffset.Reset();
		else if ( fieldName == "fallSpeed" )
			_fallSpeed.Reset();
		else if ( fieldName == "deathTime" )
			_deathTime.Reset();
		else if ( fieldName == "unsummonTime" )
			_unsummonTime.Reset();
		else if ( fieldName == "observeOffset" )
			_observeOffset.Reset();
		else if ( fieldName == "effectOffset" )
			_effectOffset.Reset();
		else if ( fieldName == "effect" )
			_effect.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fallOffset" )
			return _fallOffset.IsDerivedFromParent();
		if ( fieldName == "fallSpeed" )
			return _fallSpeed.IsDerivedFromParent();
		if ( fieldName == "deathTime" )
			return _deathTime.IsDerivedFromParent();
		if ( fieldName == "unsummonTime" )
			return _unsummonTime.IsDerivedFromParent();
		if ( fieldName == "observeOffset" )
			return _observeOffset.IsDerivedFromParent();
		if ( fieldName == "effectOffset" )
			return _effectOffset.IsDerivedFromParent();
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[UseTypeName("UNLP")]
public class UnitLogicParameters : DBResource
{
	private UndoRedoDBPtr<UnitLogicParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitLogicParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<StatsContainer> _defaultStats;
	private UndoRedoDBPtr<UnitTargetingParameters> _targetingPars;
	private UndoRedo<float> _screamRange;

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Default stats values" )]
	public DBPtr<StatsContainer> defaultStats { get { return _defaultStats.Get(); } set { _defaultStats.Set( value ); } }

	[Category( "Logic" )]
	[Description( "Targeting parameters" )]
	public DBPtr<UnitTargetingParameters> targetingPars { get { return _targetingPars.Get(); } set { _targetingPars.Set( value ); } }

	[Category( "Ranges" )]
	public float screamRange { get { return _screamRange.Get(); } set { _screamRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitLogicParameters>(owner);
		_defaultStats = new UndoRedoDBPtr<StatsContainer>( owner );
		_targetingPars = new UndoRedoDBPtr<UnitTargetingParameters>( owner );
		_screamRange = new UndoRedo<float>( owner, 20.0f );
		___parent.Changed += FireChangedEvent;
		_defaultStats.Changed += FireChangedEvent;
		_targetingPars.Changed += FireChangedEvent;
		_screamRange.Changed += FireChangedEvent;
	}

	public UnitLogicParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitLogicParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitLogicParameters" );
		defaultStats = source.defaultStats;
		targetingPars = source.targetingPars;
		screamRange = source.screamRange;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitLogicParameters source = _source as UnitLogicParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitLogicParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitLogicParameters newParent = rawParent == null ? null : rawParent.Get<UnitLogicParameters>();
		if ( newParent == null && _newParent is UnitLogicParameters )
			newParent = _newParent as UnitLogicParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_defaultStats.SetParent( newParent == null ? null : newParent._defaultStats );
		_targetingPars.SetParent( newParent == null ? null : newParent._targetingPars );
		_screamRange.SetParent( newParent == null ? null : newParent._screamRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultStats.Reset();
		_targetingPars.Reset();
		_screamRange.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_defaultStats.IsDerivedFromParent()
			&& _targetingPars.IsDerivedFromParent()
			&& _screamRange.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultStats" )
			_defaultStats.Reset();
		else if ( fieldName == "targetingPars" )
			_targetingPars.Reset();
		else if ( fieldName == "screamRange" )
			_screamRange.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "defaultStats" )
			return _defaultStats.IsDerivedFromParent();
		if ( fieldName == "targetingPars" )
			return _targetingPars.IsDerivedFromParent();
		if ( fieldName == "screamRange" )
			return _screamRange.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("UNTL")]
public class UnitsLogicParameters : DBResource
{
	private UndoRedoDBPtr<UnitsLogicParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitsLogicParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<UnitLogicParameters>> _unitParameters;

	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<DBPtr<UnitLogicParameters>> unitParameters { get { return _unitParameters; } set { _unitParameters.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitsLogicParameters>(owner);
		_unitParameters = new UndoRedoAssignableList<DBPtr<UnitLogicParameters>>( owner, typeof( EUnitType ) );
		___parent.Changed += FireChangedEvent;
		_unitParameters.Changed += FireChangedEvent;
	}

	public UnitsLogicParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitsLogicParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitsLogicParameters" );
		unitParameters = source.unitParameters;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitsLogicParameters source = _source as UnitsLogicParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitsLogicParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitsLogicParameters newParent = rawParent == null ? null : rawParent.Get<UnitsLogicParameters>();
		if ( newParent == null && _newParent is UnitsLogicParameters )
			newParent = _newParent as UnitsLogicParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_unitParameters.SetParent( newParent == null ? null : newParent._unitParameters );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_unitParameters.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_unitParameters.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "unitParameters" )
			_unitParameters.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "unitParameters" )
			return _unitParameters.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[UseTypeName("UNTP")]
public class UnitTargetingParameters : DBResource
{
	private UndoRedoDBPtr<UnitTargetingParameters> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitTargetingParameters> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoList<float> _unitTargetWeight;
	private UndoRedo<float> _unitTypeTableWeight;
	private UndoRedo<float> _weightMaximumRangePersent;
	private UndoRedo<float> _rangeWeight;
	private UndoRedo<float> _attackerMeWeight;
	private UndoRedoList<float> _attackerHeroWeight;
	private UndoRedo<float> _attackerHeroTableWeight;
	private UndoRedo<float> _attackerHeroSummonWeight;
	private UndoRedo<float> _attackerTowerWeight;
	private UndoRedo<float> _attackerMasterWeight;
	private UndoRedo<float> _attackerAllyWeight;
	private UndoRedoList<float> _currentTargetWeight;
	private UndoRedo<float> _currentTargetTableWeight;
	private UndoRedo<float> _targetRevisionTime;
	private UndoRedo<float> _healthWeight;
	private UndoRedo<float> _masterTargetWeight;
	private UndoRedo<float> _talentAttackWeight;
	private UndoRedo<float> _autoAttackWeight;
	private UndoRedo<float> _OutOfAggroWeight;
	private UndoRedo<float> _allyTargetWeight;
	private UndoRedo<float> _aggressiveNeutralWeight;
	private UndoRedo<float> _aggressiveNeutralAttackingHeroWeight;
	private ExecutableFloatString _customWeight;
	private UndoRedo<float> _maxTimeFromAttack;
	private UndoRedo<float> _targetingRange;
	private UndoRedo<float> _chaseRange;
	private UndoRedo<float> _aggroRange;
	private UndoRedo<bool> _ignoreSiblingTarget;
	private UndoRedo<bool> _isStationarySummon;
	private UndoRedo<bool> _onlyAutoTargeting;
	private UndoRedo<float> _attackerNearbyHeroWeight;
	private UndoRedo<float> _nearbyRange;
	private UndoRedo<float> _longSuspendTimeout;
	private UndoRedo<float> _sortSuspendTimeout;

	[Category( "Targeting by type" )]
	[Description( "Table of target types weights" )]
	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<float> unitTargetWeight { get { return _unitTargetWeight; } set { _unitTargetWeight.Assign( value ); } }

	[Category( "Targeting by type" )]
	[Description( "Multiplier for the common weights table" )]
	public float unitTypeTableWeight { get { return _unitTypeTableWeight.Get(); } set { _unitTypeTableWeight.Set( value ); } }

	[Category( "Targeting by range" )]
	[FloatMinMax(0, 1)]
	public float weightMaximumRangePersent { get { return _weightMaximumRangePersent.Get(); } set { _weightMaximumRangePersent.Set( value ); } }

	[Category( "Targeting by range" )]
	public float rangeWeight { get { return _rangeWeight.Get(); } set { _rangeWeight.Set( value ); } }

	[Category( "Targeting attackers" )]
	public float attackerMeWeight { get { return _attackerMeWeight.Get(); } set { _attackerMeWeight.Set( value ); } }

	[Category( "Targeting attackers" )]
	[Description( "Table of weights of allied hero attackers" )]
	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<float> attackerHeroWeight { get { return _attackerHeroWeight; } set { _attackerHeroWeight.Assign( value ); } }

	[Category( "Targeting attackers" )]
	[Description( "Multiplier for allied hero attackers weights table" )]
	public float attackerHeroTableWeight { get { return _attackerHeroTableWeight.Get(); } set { _attackerHeroTableWeight.Set( value ); } }

	[Description( "Weight of summon whose master attacks allied hero. This weight applies instead of unitTargetWeight and attackerHeroWeight. Leave 0 in a case where such logics is not required." )]
	public float attackerHeroSummonWeight { get { return _attackerHeroSummonWeight.Get(); } set { _attackerHeroSummonWeight.Set( value ); } }

	[Category( "Targeting towers" )]
	public float attackerTowerWeight { get { return _attackerTowerWeight.Get(); } set { _attackerTowerWeight.Set( value ); } }

	[Category( "Targeting attackers" )]
	public float attackerMasterWeight { get { return _attackerMasterWeight.Get(); } set { _attackerMasterWeight.Set( value ); } }

	[Category( "Targeting attackers" )]
	public float attackerAllyWeight { get { return _attackerAllyWeight.Get(); } set { _attackerAllyWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Current target weights table" )]
	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<float> currentTargetWeight { get { return _currentTargetWeight; } set { _currentTargetWeight.Assign( value ); } }

	[Description( "Multiplier for current target weights table" )]
	public float currentTargetTableWeight { get { return _currentTargetTableWeight.Get(); } set { _currentTargetTableWeight.Set( value ); } }

	[Category( "Targeting common" )]
	public float targetRevisionTime { get { return _targetRevisionTime.Get(); } set { _targetRevisionTime.Set( value ); } }

	[Category( "Targeting common" )]
	public float healthWeight { get { return _healthWeight.Get(); } set { _healthWeight.Set( value ); } }

	[Category( "Targeting master" )]
	public float masterTargetWeight { get { return _masterTargetWeight.Get(); } set { _masterTargetWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Weight of target, attacked by talent. Added to total weight." )]
	public float talentAttackWeight { get { return _talentAttackWeight.Get(); } set { _talentAttackWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Weight of target, attacked by autoattack. Added to total weight." )]
	public float autoAttackWeight { get { return _autoAttackWeight.Get(); } set { _autoAttackWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Weight of target, attacked out of aggroRange" )]
	public float OutOfAggroWeight { get { return _OutOfAggroWeight.Get(); } set { _OutOfAggroWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Weight of target if at least one ally within screamRange has the same target" )]
	public float allyTargetWeight { get { return _allyTargetWeight.Get(); } set { _allyTargetWeight.Set( value ); } }

	[Description( "Вес агрессивного нейтрала" )]
	public float aggressiveNeutralWeight { get { return _aggressiveNeutralWeight.Get(); } set { _aggressiveNeutralWeight.Set( value ); } }

	[Description( "Вес агрессивного нейтрала который бьёт союзного героя. Предыдущий вес в этом случае не применяется" )]
	public float aggressiveNeutralAttackingHeroWeight { get { return _aggressiveNeutralAttackingHeroWeight.Get(); } set { _aggressiveNeutralAttackingHeroWeight.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Custom weight (formula)" )]
	public ExecutableFloatString customWeight { get { return _customWeight; } set { _customWeight.Assign( value ); } }

	[Category( "Targeting common" )]
	[Description( "Max time in seconds from attack, which may pass and it will be still considered in target weight calculation. -1 means no time check." )]
	public float maxTimeFromAttack { get { return _maxTimeFromAttack.Get(); } set { _maxTimeFromAttack.Set( value ); } }

	[Category( "Ranges" )]
	public float targetingRange { get { return _targetingRange.Get(); } set { _targetingRange.Set( value ); } }

	[Category( "Ranges" )]
	public float chaseRange { get { return _chaseRange.Get(); } set { _chaseRange.Set( value ); } }

	[Category( "Ranges" )]
	public float aggroRange { get { return _aggroRange.Get(); } set { _aggroRange.Set( value ); } }

	[Description( "Unit ignores targets attacked by friendly units same as this one" )]
	public bool ignoreSiblingTarget { get { return _ignoreSiblingTarget.Get(); } set { _ignoreSiblingTarget.Set( value ); } }

	[Description( "Is the unit is a stationary summon. Don't check ranges to master." )]
	public bool isStationarySummon { get { return _isStationarySummon.Get(); } set { _isStationarySummon.Set( value ); } }

	[Description( "Don't select target that damages the unit and ignore force assigning of targets. Select targets only by weights." )]
	public bool onlyAutoTargeting { get { return _onlyAutoTargeting.Get(); } set { _onlyAutoTargeting.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Weight of target hero that attacks allied hero." )]
	public float attackerNearbyHeroWeight { get { return _attackerNearbyHeroWeight.Get(); } set { _attackerNearbyHeroWeight.Set( value ); } }

	[Category( "Ranges" )]
	public float nearbyRange { get { return _nearbyRange.Get(); } set { _nearbyRange.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Long Suspend Timeout(in seconds)" )]
	public float longSuspendTimeout { get { return _longSuspendTimeout.Get(); } set { _longSuspendTimeout.Set( value ); } }

	[Category( "Targeting common" )]
	[Description( "Sort Suspend Timeout(in seconds)" )]
	public float sortSuspendTimeout { get { return _sortSuspendTimeout.Get(); } set { _sortSuspendTimeout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitTargetingParameters>(owner);
		_unitTargetWeight = new UndoRedoList<float>( owner, typeof( EUnitType ) );
		_unitTypeTableWeight = new UndoRedo<float>( owner, 0.0f );
		_weightMaximumRangePersent = new UndoRedo<float>( owner, 0.0f );
		_rangeWeight = new UndoRedo<float>( owner, 0.0f );
		_attackerMeWeight = new UndoRedo<float>( owner, 0.5f );
		_attackerHeroWeight = new UndoRedoList<float>( owner, typeof( EUnitType ) );
		_attackerHeroTableWeight = new UndoRedo<float>( owner, 1.0f );
		_attackerHeroSummonWeight = new UndoRedo<float>( owner, 0.0f );
		_attackerTowerWeight = new UndoRedo<float>( owner, 8.0f );
		_attackerMasterWeight = new UndoRedo<float>( owner, 2.0f );
		_attackerAllyWeight = new UndoRedo<float>( owner, 0.2f );
		_currentTargetWeight = new UndoRedoList<float>( owner, typeof( EUnitType ) );
		_currentTargetTableWeight = new UndoRedo<float>( owner, 1.0f );
		_targetRevisionTime = new UndoRedo<float>( owner, 7.0f );
		_healthWeight = new UndoRedo<float>( owner, 0.3f );
		_masterTargetWeight = new UndoRedo<float>( owner, 0.0f );
		_talentAttackWeight = new UndoRedo<float>( owner, 0.0f );
		_autoAttackWeight = new UndoRedo<float>( owner, 0.0f );
		_OutOfAggroWeight = new UndoRedo<float>( owner, 0.0f );
		_allyTargetWeight = new UndoRedo<float>( owner, 0.0f );
		_aggressiveNeutralWeight = new UndoRedo<float>( owner, 0.0f );
		_aggressiveNeutralAttackingHeroWeight = new UndoRedo<float>( owner, 0.0f );
		ExecutableFloatString __customWeight = new ExecutableFloatString(); // Construct default object for customWeight
		__customWeight.sString = "0.0f";
		_customWeight = new ExecutableFloatString( owner, __customWeight );
		_maxTimeFromAttack = new UndoRedo<float>( owner, -1.0f );
		_targetingRange = new UndoRedo<float>( owner, 15.0f );
		_chaseRange = new UndoRedo<float>( owner, 30.0f );
		_aggroRange = new UndoRedo<float>( owner, -1.0f );
		_ignoreSiblingTarget = new UndoRedo<bool>( owner, false );
		_isStationarySummon = new UndoRedo<bool>( owner, false );
		_onlyAutoTargeting = new UndoRedo<bool>( owner, false );
		_attackerNearbyHeroWeight = new UndoRedo<float>( owner, 0.0f );
		_nearbyRange = new UndoRedo<float>( owner, 0.0f );
		_longSuspendTimeout = new UndoRedo<float>( owner, 0.3f );
		_sortSuspendTimeout = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_unitTargetWeight.Changed += FireChangedEvent;
		_unitTypeTableWeight.Changed += FireChangedEvent;
		_weightMaximumRangePersent.Changed += FireChangedEvent;
		_rangeWeight.Changed += FireChangedEvent;
		_attackerMeWeight.Changed += FireChangedEvent;
		_attackerHeroWeight.Changed += FireChangedEvent;
		_attackerHeroTableWeight.Changed += FireChangedEvent;
		_attackerHeroSummonWeight.Changed += FireChangedEvent;
		_attackerTowerWeight.Changed += FireChangedEvent;
		_attackerMasterWeight.Changed += FireChangedEvent;
		_attackerAllyWeight.Changed += FireChangedEvent;
		_currentTargetWeight.Changed += FireChangedEvent;
		_currentTargetTableWeight.Changed += FireChangedEvent;
		_targetRevisionTime.Changed += FireChangedEvent;
		_healthWeight.Changed += FireChangedEvent;
		_masterTargetWeight.Changed += FireChangedEvent;
		_talentAttackWeight.Changed += FireChangedEvent;
		_autoAttackWeight.Changed += FireChangedEvent;
		_OutOfAggroWeight.Changed += FireChangedEvent;
		_allyTargetWeight.Changed += FireChangedEvent;
		_aggressiveNeutralWeight.Changed += FireChangedEvent;
		_aggressiveNeutralAttackingHeroWeight.Changed += FireChangedEvent;
		_customWeight.Changed += FireChangedEvent;
		_maxTimeFromAttack.Changed += FireChangedEvent;
		_targetingRange.Changed += FireChangedEvent;
		_chaseRange.Changed += FireChangedEvent;
		_aggroRange.Changed += FireChangedEvent;
		_ignoreSiblingTarget.Changed += FireChangedEvent;
		_isStationarySummon.Changed += FireChangedEvent;
		_onlyAutoTargeting.Changed += FireChangedEvent;
		_attackerNearbyHeroWeight.Changed += FireChangedEvent;
		_nearbyRange.Changed += FireChangedEvent;
		_longSuspendTimeout.Changed += FireChangedEvent;
		_sortSuspendTimeout.Changed += FireChangedEvent;
	}

	public UnitTargetingParameters()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitTargetingParameters source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitTargetingParameters" );
		unitTargetWeight = source.unitTargetWeight;
		unitTypeTableWeight = source.unitTypeTableWeight;
		weightMaximumRangePersent = source.weightMaximumRangePersent;
		rangeWeight = source.rangeWeight;
		attackerMeWeight = source.attackerMeWeight;
		attackerHeroWeight = source.attackerHeroWeight;
		attackerHeroTableWeight = source.attackerHeroTableWeight;
		attackerHeroSummonWeight = source.attackerHeroSummonWeight;
		attackerTowerWeight = source.attackerTowerWeight;
		attackerMasterWeight = source.attackerMasterWeight;
		attackerAllyWeight = source.attackerAllyWeight;
		currentTargetWeight = source.currentTargetWeight;
		currentTargetTableWeight = source.currentTargetTableWeight;
		targetRevisionTime = source.targetRevisionTime;
		healthWeight = source.healthWeight;
		masterTargetWeight = source.masterTargetWeight;
		talentAttackWeight = source.talentAttackWeight;
		autoAttackWeight = source.autoAttackWeight;
		OutOfAggroWeight = source.OutOfAggroWeight;
		allyTargetWeight = source.allyTargetWeight;
		aggressiveNeutralWeight = source.aggressiveNeutralWeight;
		aggressiveNeutralAttackingHeroWeight = source.aggressiveNeutralAttackingHeroWeight;
		customWeight = source.customWeight;
		maxTimeFromAttack = source.maxTimeFromAttack;
		targetingRange = source.targetingRange;
		chaseRange = source.chaseRange;
		aggroRange = source.aggroRange;
		ignoreSiblingTarget = source.ignoreSiblingTarget;
		isStationarySummon = source.isStationarySummon;
		onlyAutoTargeting = source.onlyAutoTargeting;
		attackerNearbyHeroWeight = source.attackerNearbyHeroWeight;
		nearbyRange = source.nearbyRange;
		longSuspendTimeout = source.longSuspendTimeout;
		sortSuspendTimeout = source.sortSuspendTimeout;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitTargetingParameters source = _source as UnitTargetingParameters;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitTargetingParameters" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitTargetingParameters newParent = rawParent == null ? null : rawParent.Get<UnitTargetingParameters>();
		if ( newParent == null && _newParent is UnitTargetingParameters )
			newParent = _newParent as UnitTargetingParameters;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_unitTargetWeight.SetParent( newParent == null ? null : newParent._unitTargetWeight );
		_unitTypeTableWeight.SetParent( newParent == null ? null : newParent._unitTypeTableWeight );
		_weightMaximumRangePersent.SetParent( newParent == null ? null : newParent._weightMaximumRangePersent );
		_rangeWeight.SetParent( newParent == null ? null : newParent._rangeWeight );
		_attackerMeWeight.SetParent( newParent == null ? null : newParent._attackerMeWeight );
		_attackerHeroWeight.SetParent( newParent == null ? null : newParent._attackerHeroWeight );
		_attackerHeroTableWeight.SetParent( newParent == null ? null : newParent._attackerHeroTableWeight );
		_attackerHeroSummonWeight.SetParent( newParent == null ? null : newParent._attackerHeroSummonWeight );
		_attackerTowerWeight.SetParent( newParent == null ? null : newParent._attackerTowerWeight );
		_attackerMasterWeight.SetParent( newParent == null ? null : newParent._attackerMasterWeight );
		_attackerAllyWeight.SetParent( newParent == null ? null : newParent._attackerAllyWeight );
		_currentTargetWeight.SetParent( newParent == null ? null : newParent._currentTargetWeight );
		_currentTargetTableWeight.SetParent( newParent == null ? null : newParent._currentTargetTableWeight );
		_targetRevisionTime.SetParent( newParent == null ? null : newParent._targetRevisionTime );
		_healthWeight.SetParent( newParent == null ? null : newParent._healthWeight );
		_masterTargetWeight.SetParent( newParent == null ? null : newParent._masterTargetWeight );
		_talentAttackWeight.SetParent( newParent == null ? null : newParent._talentAttackWeight );
		_autoAttackWeight.SetParent( newParent == null ? null : newParent._autoAttackWeight );
		_OutOfAggroWeight.SetParent( newParent == null ? null : newParent._OutOfAggroWeight );
		_allyTargetWeight.SetParent( newParent == null ? null : newParent._allyTargetWeight );
		_aggressiveNeutralWeight.SetParent( newParent == null ? null : newParent._aggressiveNeutralWeight );
		_aggressiveNeutralAttackingHeroWeight.SetParent( newParent == null ? null : newParent._aggressiveNeutralAttackingHeroWeight );
		_customWeight.SetParent( newParent == null ? null : newParent._customWeight );
		_maxTimeFromAttack.SetParent( newParent == null ? null : newParent._maxTimeFromAttack );
		_targetingRange.SetParent( newParent == null ? null : newParent._targetingRange );
		_chaseRange.SetParent( newParent == null ? null : newParent._chaseRange );
		_aggroRange.SetParent( newParent == null ? null : newParent._aggroRange );
		_ignoreSiblingTarget.SetParent( newParent == null ? null : newParent._ignoreSiblingTarget );
		_isStationarySummon.SetParent( newParent == null ? null : newParent._isStationarySummon );
		_onlyAutoTargeting.SetParent( newParent == null ? null : newParent._onlyAutoTargeting );
		_attackerNearbyHeroWeight.SetParent( newParent == null ? null : newParent._attackerNearbyHeroWeight );
		_nearbyRange.SetParent( newParent == null ? null : newParent._nearbyRange );
		_longSuspendTimeout.SetParent( newParent == null ? null : newParent._longSuspendTimeout );
		_sortSuspendTimeout.SetParent( newParent == null ? null : newParent._sortSuspendTimeout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_unitTargetWeight.Reset();
		_unitTypeTableWeight.Reset();
		_weightMaximumRangePersent.Reset();
		_rangeWeight.Reset();
		_attackerMeWeight.Reset();
		_attackerHeroWeight.Reset();
		_attackerHeroTableWeight.Reset();
		_attackerHeroSummonWeight.Reset();
		_attackerTowerWeight.Reset();
		_attackerMasterWeight.Reset();
		_attackerAllyWeight.Reset();
		_currentTargetWeight.Reset();
		_currentTargetTableWeight.Reset();
		_targetRevisionTime.Reset();
		_healthWeight.Reset();
		_masterTargetWeight.Reset();
		_talentAttackWeight.Reset();
		_autoAttackWeight.Reset();
		_OutOfAggroWeight.Reset();
		_allyTargetWeight.Reset();
		_aggressiveNeutralWeight.Reset();
		_aggressiveNeutralAttackingHeroWeight.Reset();
		_customWeight.Reset();
		_maxTimeFromAttack.Reset();
		_targetingRange.Reset();
		_chaseRange.Reset();
		_aggroRange.Reset();
		_ignoreSiblingTarget.Reset();
		_isStationarySummon.Reset();
		_onlyAutoTargeting.Reset();
		_attackerNearbyHeroWeight.Reset();
		_nearbyRange.Reset();
		_longSuspendTimeout.Reset();
		_sortSuspendTimeout.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_unitTargetWeight.IsDerivedFromParent()
			&& _unitTypeTableWeight.IsDerivedFromParent()
			&& _weightMaximumRangePersent.IsDerivedFromParent()
			&& _rangeWeight.IsDerivedFromParent()
			&& _attackerMeWeight.IsDerivedFromParent()
			&& _attackerHeroWeight.IsDerivedFromParent()
			&& _attackerHeroTableWeight.IsDerivedFromParent()
			&& _attackerHeroSummonWeight.IsDerivedFromParent()
			&& _attackerTowerWeight.IsDerivedFromParent()
			&& _attackerMasterWeight.IsDerivedFromParent()
			&& _attackerAllyWeight.IsDerivedFromParent()
			&& _currentTargetWeight.IsDerivedFromParent()
			&& _currentTargetTableWeight.IsDerivedFromParent()
			&& _targetRevisionTime.IsDerivedFromParent()
			&& _healthWeight.IsDerivedFromParent()
			&& _masterTargetWeight.IsDerivedFromParent()
			&& _talentAttackWeight.IsDerivedFromParent()
			&& _autoAttackWeight.IsDerivedFromParent()
			&& _OutOfAggroWeight.IsDerivedFromParent()
			&& _allyTargetWeight.IsDerivedFromParent()
			&& _aggressiveNeutralWeight.IsDerivedFromParent()
			&& _aggressiveNeutralAttackingHeroWeight.IsDerivedFromParent()
			&& _customWeight.IsDerivedFromParent()
			&& _maxTimeFromAttack.IsDerivedFromParent()
			&& _targetingRange.IsDerivedFromParent()
			&& _chaseRange.IsDerivedFromParent()
			&& _aggroRange.IsDerivedFromParent()
			&& _ignoreSiblingTarget.IsDerivedFromParent()
			&& _isStationarySummon.IsDerivedFromParent()
			&& _onlyAutoTargeting.IsDerivedFromParent()
			&& _attackerNearbyHeroWeight.IsDerivedFromParent()
			&& _nearbyRange.IsDerivedFromParent()
			&& _longSuspendTimeout.IsDerivedFromParent()
			&& _sortSuspendTimeout.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "unitTargetWeight" )
			_unitTargetWeight.Reset();
		else if ( fieldName == "unitTypeTableWeight" )
			_unitTypeTableWeight.Reset();
		else if ( fieldName == "weightMaximumRangePersent" )
			_weightMaximumRangePersent.Reset();
		else if ( fieldName == "rangeWeight" )
			_rangeWeight.Reset();
		else if ( fieldName == "attackerMeWeight" )
			_attackerMeWeight.Reset();
		else if ( fieldName == "attackerHeroWeight" )
			_attackerHeroWeight.Reset();
		else if ( fieldName == "attackerHeroTableWeight" )
			_attackerHeroTableWeight.Reset();
		else if ( fieldName == "attackerHeroSummonWeight" )
			_attackerHeroSummonWeight.Reset();
		else if ( fieldName == "attackerTowerWeight" )
			_attackerTowerWeight.Reset();
		else if ( fieldName == "attackerMasterWeight" )
			_attackerMasterWeight.Reset();
		else if ( fieldName == "attackerAllyWeight" )
			_attackerAllyWeight.Reset();
		else if ( fieldName == "currentTargetWeight" )
			_currentTargetWeight.Reset();
		else if ( fieldName == "currentTargetTableWeight" )
			_currentTargetTableWeight.Reset();
		else if ( fieldName == "targetRevisionTime" )
			_targetRevisionTime.Reset();
		else if ( fieldName == "healthWeight" )
			_healthWeight.Reset();
		else if ( fieldName == "masterTargetWeight" )
			_masterTargetWeight.Reset();
		else if ( fieldName == "talentAttackWeight" )
			_talentAttackWeight.Reset();
		else if ( fieldName == "autoAttackWeight" )
			_autoAttackWeight.Reset();
		else if ( fieldName == "OutOfAggroWeight" )
			_OutOfAggroWeight.Reset();
		else if ( fieldName == "allyTargetWeight" )
			_allyTargetWeight.Reset();
		else if ( fieldName == "aggressiveNeutralWeight" )
			_aggressiveNeutralWeight.Reset();
		else if ( fieldName == "aggressiveNeutralAttackingHeroWeight" )
			_aggressiveNeutralAttackingHeroWeight.Reset();
		else if ( fieldName == "customWeight" )
			_customWeight.Reset();
		else if ( fieldName == "maxTimeFromAttack" )
			_maxTimeFromAttack.Reset();
		else if ( fieldName == "targetingRange" )
			_targetingRange.Reset();
		else if ( fieldName == "chaseRange" )
			_chaseRange.Reset();
		else if ( fieldName == "aggroRange" )
			_aggroRange.Reset();
		else if ( fieldName == "ignoreSiblingTarget" )
			_ignoreSiblingTarget.Reset();
		else if ( fieldName == "isStationarySummon" )
			_isStationarySummon.Reset();
		else if ( fieldName == "onlyAutoTargeting" )
			_onlyAutoTargeting.Reset();
		else if ( fieldName == "attackerNearbyHeroWeight" )
			_attackerNearbyHeroWeight.Reset();
		else if ( fieldName == "nearbyRange" )
			_nearbyRange.Reset();
		else if ( fieldName == "longSuspendTimeout" )
			_longSuspendTimeout.Reset();
		else if ( fieldName == "sortSuspendTimeout" )
			_sortSuspendTimeout.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "unitTargetWeight" )
			return _unitTargetWeight.IsDerivedFromParent();
		if ( fieldName == "unitTypeTableWeight" )
			return _unitTypeTableWeight.IsDerivedFromParent();
		if ( fieldName == "weightMaximumRangePersent" )
			return _weightMaximumRangePersent.IsDerivedFromParent();
		if ( fieldName == "rangeWeight" )
			return _rangeWeight.IsDerivedFromParent();
		if ( fieldName == "attackerMeWeight" )
			return _attackerMeWeight.IsDerivedFromParent();
		if ( fieldName == "attackerHeroWeight" )
			return _attackerHeroWeight.IsDerivedFromParent();
		if ( fieldName == "attackerHeroTableWeight" )
			return _attackerHeroTableWeight.IsDerivedFromParent();
		if ( fieldName == "attackerHeroSummonWeight" )
			return _attackerHeroSummonWeight.IsDerivedFromParent();
		if ( fieldName == "attackerTowerWeight" )
			return _attackerTowerWeight.IsDerivedFromParent();
		if ( fieldName == "attackerMasterWeight" )
			return _attackerMasterWeight.IsDerivedFromParent();
		if ( fieldName == "attackerAllyWeight" )
			return _attackerAllyWeight.IsDerivedFromParent();
		if ( fieldName == "currentTargetWeight" )
			return _currentTargetWeight.IsDerivedFromParent();
		if ( fieldName == "currentTargetTableWeight" )
			return _currentTargetTableWeight.IsDerivedFromParent();
		if ( fieldName == "targetRevisionTime" )
			return _targetRevisionTime.IsDerivedFromParent();
		if ( fieldName == "healthWeight" )
			return _healthWeight.IsDerivedFromParent();
		if ( fieldName == "masterTargetWeight" )
			return _masterTargetWeight.IsDerivedFromParent();
		if ( fieldName == "talentAttackWeight" )
			return _talentAttackWeight.IsDerivedFromParent();
		if ( fieldName == "autoAttackWeight" )
			return _autoAttackWeight.IsDerivedFromParent();
		if ( fieldName == "OutOfAggroWeight" )
			return _OutOfAggroWeight.IsDerivedFromParent();
		if ( fieldName == "allyTargetWeight" )
			return _allyTargetWeight.IsDerivedFromParent();
		if ( fieldName == "aggressiveNeutralWeight" )
			return _aggressiveNeutralWeight.IsDerivedFromParent();
		if ( fieldName == "aggressiveNeutralAttackingHeroWeight" )
			return _aggressiveNeutralAttackingHeroWeight.IsDerivedFromParent();
		if ( fieldName == "customWeight" )
			return _customWeight.IsDerivedFromParent();
		if ( fieldName == "maxTimeFromAttack" )
			return _maxTimeFromAttack.IsDerivedFromParent();
		if ( fieldName == "targetingRange" )
			return _targetingRange.IsDerivedFromParent();
		if ( fieldName == "chaseRange" )
			return _chaseRange.IsDerivedFromParent();
		if ( fieldName == "aggroRange" )
			return _aggroRange.IsDerivedFromParent();
		if ( fieldName == "ignoreSiblingTarget" )
			return _ignoreSiblingTarget.IsDerivedFromParent();
		if ( fieldName == "isStationarySummon" )
			return _isStationarySummon.IsDerivedFromParent();
		if ( fieldName == "onlyAutoTargeting" )
			return _onlyAutoTargeting.IsDerivedFromParent();
		if ( fieldName == "attackerNearbyHeroWeight" )
			return _attackerNearbyHeroWeight.IsDerivedFromParent();
		if ( fieldName == "nearbyRange" )
			return _nearbyRange.IsDerivedFromParent();
		if ( fieldName == "longSuspendTimeout" )
			return _longSuspendTimeout.IsDerivedFromParent();
		if ( fieldName == "sortSuspendTimeout" )
			return _sortSuspendTimeout.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
