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
public enum ERerollShopResources
{
	Resource1 = 0,
	Resource2 = 1,
	Resource3 = 2,
	Perl = 3,
	RedPerl = 4,
	Silver = 5,
	Gold = 6,
	Shard = 7,
};

[Custom("DBServer", "Social")]
[Flags]
public enum ERerollShopResourceType
{
	Resource1 = 1,
	Resource2 = 2,
	Resource3 = 4,
	Perl = 8,
	RedPerl = 16,
	Silver = 32,
	Gold = 64,
	Shard = 128,
	All = 255,
};

[Custom("Social")]
public class GroupSlot : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GroupSlot __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<RerollShopSlot> _slot;
	private UndoRedo<ERerollShopResourceType> _currencies;
	private UndoRedo<int> _minPoints;
	private UndoRedo<int> _maxPoints;

	public DBPtr<RerollShopSlot> slot { get { return _slot.Get(); } set { _slot.Set( value ); } }

	[Description( "Ресурсы, за которые можно купить этот слот" )]
	public ERerollShopResourceType currencies { get { return _currencies.Get(); } set { _currencies.Set( value ); } }

	[Description( "Минимальная цена в очках" )]
	public int minPoints { get { return _minPoints.Get(); } set { _minPoints.Set( value ); } }

	[Description( "Максимальная цена в очках" )]
	public int maxPoints { get { return _maxPoints.Get(); } set { _maxPoints.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_slot = new UndoRedoDBPtr<RerollShopSlot>( owner );
		_currencies = new UndoRedo<ERerollShopResourceType>( owner, (ERerollShopResourceType)0 );
		_minPoints = new UndoRedo<int>( owner, 0 );
		_maxPoints = new UndoRedo<int>( owner, 0 );
		_slot.Changed += FireChangedEvent;
		_currencies.Changed += FireChangedEvent;
		_minPoints.Changed += FireChangedEvent;
		_maxPoints.Changed += FireChangedEvent;
	}

	public GroupSlot()
	{
		Initialize( GetOwner() );
	}

	public GroupSlot( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GroupSlot( DBResource owner, GroupSlot source )
		: this(owner, source, true){}

	protected GroupSlot( DBResource owner, GroupSlot source, bool fireEvent )
	{
		_slot = new UndoRedoDBPtr<RerollShopSlot>( owner, source.slot );
		_currencies = new UndoRedo<ERerollShopResourceType>( owner, source.currencies );
		_minPoints = new UndoRedo<int>( owner, source.minPoints );
		_maxPoints = new UndoRedo<int>( owner, source.maxPoints );
		_slot.Changed += FireChangedEvent;
		_currencies.Changed += FireChangedEvent;
		_minPoints.Changed += FireChangedEvent;
		_maxPoints.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GroupSlot source = _source as GroupSlot;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GroupSlot" );
		slot = source.slot;
		currencies = source.currencies;
		minPoints = source.minPoints;
		maxPoints = source.maxPoints;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GroupSlot newParent = _newParent as GroupSlot;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_slot.SetParent( newParent == null ? null : newParent._slot );
		_currencies.SetParent( newParent == null ? null : newParent._currencies );
		_minPoints.SetParent( newParent == null ? null : newParent._minPoints );
		_maxPoints.SetParent( newParent == null ? null : newParent._maxPoints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_slot.Reset();
		_currencies.Reset();
		_minPoints.Reset();
		_maxPoints.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_slot.IsDerivedFromParent()
			&& _currencies.IsDerivedFromParent()
			&& _minPoints.IsDerivedFromParent()
			&& _maxPoints.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "slot" )
			_slot.Reset();
		else if ( fieldName == "currencies" )
			_currencies.Reset();
		else if ( fieldName == "minPoints" )
			_minPoints.Reset();
		else if ( fieldName == "maxPoints" )
			_maxPoints.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "slot" )
			return _slot.IsDerivedFromParent();
		if ( fieldName == "currencies" )
			return _currencies.IsDerivedFromParent();
		if ( fieldName == "minPoints" )
			return _minPoints.IsDerivedFromParent();
		if ( fieldName == "maxPoints" )
			return _maxPoints.IsDerivedFromParent();
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
public class ResourceToPointsConversion : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ResourceToPointsConversion __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ERerollShopResources> _resource;
	private UndoRedo<float> _priceInPoints;
	private UndoRedo<int> _roundToDigits;

	[Description( "Тип ресурса" )]
	public ERerollShopResources resource { get { return _resource.Get(); } set { _resource.Set( value ); } }

	[Description( "Цена в очках" )]
	public float priceInPoints { get { return _priceInPoints.Get(); } set { _priceInPoints.Set( value ); } }

	[Description( "Порядок округления (если стоит 1000, то цена 1541 станет 2000)" )]
	public int roundToDigits { get { return _roundToDigits.Get(); } set { _roundToDigits.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_resource = new UndoRedo<ERerollShopResources>( owner, ERerollShopResources.Resource1 );
		_priceInPoints = new UndoRedo<float>( owner, 0.0f );
		_roundToDigits = new UndoRedo<int>( owner, 0 );
		_resource.Changed += FireChangedEvent;
		_priceInPoints.Changed += FireChangedEvent;
		_roundToDigits.Changed += FireChangedEvent;
	}

	public ResourceToPointsConversion()
	{
		Initialize( GetOwner() );
	}

	public ResourceToPointsConversion( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ResourceToPointsConversion( DBResource owner, ResourceToPointsConversion source )
		: this(owner, source, true){}

	protected ResourceToPointsConversion( DBResource owner, ResourceToPointsConversion source, bool fireEvent )
	{
		_resource = new UndoRedo<ERerollShopResources>( owner, source.resource );
		_priceInPoints = new UndoRedo<float>( owner, source.priceInPoints );
		_roundToDigits = new UndoRedo<int>( owner, source.roundToDigits );
		_resource.Changed += FireChangedEvent;
		_priceInPoints.Changed += FireChangedEvent;
		_roundToDigits.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ResourceToPointsConversion source = _source as ResourceToPointsConversion;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceToPointsConversion" );
		resource = source.resource;
		priceInPoints = source.priceInPoints;
		roundToDigits = source.roundToDigits;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ResourceToPointsConversion newParent = _newParent as ResourceToPointsConversion;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_resource.SetParent( newParent == null ? null : newParent._resource );
		_priceInPoints.SetParent( newParent == null ? null : newParent._priceInPoints );
		_roundToDigits.SetParent( newParent == null ? null : newParent._roundToDigits );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_resource.Reset();
		_priceInPoints.Reset();
		_roundToDigits.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_resource.IsDerivedFromParent()
			&& _priceInPoints.IsDerivedFromParent()
			&& _roundToDigits.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "resource" )
			_resource.Reset();
		else if ( fieldName == "priceInPoints" )
			_priceInPoints.Reset();
		else if ( fieldName == "roundToDigits" )
			_roundToDigits.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		if ( fieldName == "priceInPoints" )
			return _priceInPoints.IsDerivedFromParent();
		if ( fieldName == "roundToDigits" )
			return _roundToDigits.IsDerivedFromParent();
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
public class RerollTimesToDropProbabilty : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RerollTimesToDropProbabilty __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _rerollTime;
	private UndoRedo<float> _newProbability;

	[Description( "Сколько раз нужно сделать реролл" )]
	public int rerollTime { get { return _rerollTime.Get(); } set { _rerollTime.Set( value ); } }

	[Description( "Новая вероятность после rerollTime раз" )]
	public float newProbability { get { return _newProbability.Get(); } set { _newProbability.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rerollTime = new UndoRedo<int>( owner, 0 );
		_newProbability = new UndoRedo<float>( owner, 0.0f );
		_rerollTime.Changed += FireChangedEvent;
		_newProbability.Changed += FireChangedEvent;
	}

	public RerollTimesToDropProbabilty()
	{
		Initialize( GetOwner() );
	}

	public RerollTimesToDropProbabilty( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RerollTimesToDropProbabilty( DBResource owner, RerollTimesToDropProbabilty source )
		: this(owner, source, true){}

	protected RerollTimesToDropProbabilty( DBResource owner, RerollTimesToDropProbabilty source, bool fireEvent )
	{
		_rerollTime = new UndoRedo<int>( owner, source.rerollTime );
		_newProbability = new UndoRedo<float>( owner, source.newProbability );
		_rerollTime.Changed += FireChangedEvent;
		_newProbability.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RerollTimesToDropProbabilty source = _source as RerollTimesToDropProbabilty;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RerollTimesToDropProbabilty" );
		rerollTime = source.rerollTime;
		newProbability = source.newProbability;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RerollTimesToDropProbabilty newParent = _newParent as RerollTimesToDropProbabilty;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rerollTime.SetParent( newParent == null ? null : newParent._rerollTime );
		_newProbability.SetParent( newParent == null ? null : newParent._newProbability );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rerollTime.Reset();
		_newProbability.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rerollTime.IsDerivedFromParent()
			&& _newProbability.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rerollTime" )
			_rerollTime.Reset();
		else if ( fieldName == "newProbability" )
			_newProbability.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rerollTime" )
			return _rerollTime.IsDerivedFromParent();
		if ( fieldName == "newProbability" )
			return _newProbability.IsDerivedFromParent();
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
public class RerollShopSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RerollShopSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<RerollShopGroup>> _groups;
	private UndoRedoAssignableList<ResourceToPointsConversion> _resourcesToPointsTable;
	private UndoRedo<int> _usualSlots;
	private UndoRedo<int> _premiumSlots;
	private UndoRedo<int> _maxInactiveUsualSlots;
	private UndoRedo<int> _maxInactivePremiumSlots;
	private ResourcesTable _rerollPrice;
	private UndoRedo<bool> _premiumNotInactive;
	private UndoRedo<int> _slotBlinkTime;

	[Description( "Группы слотов" )]
	public libdb.IChangeableList<DBPtr<RerollShopGroup>> groups { get { return _groups; } set { _groups.Assign( value ); } }

	[Description( "Таблица стоимости ресурсов в очках" )]
	public libdb.IChangeableList<ResourceToPointsConversion> resourcesToPointsTable { get { return _resourcesToPointsTable; } set { _resourcesToPointsTable.Assign( value ); } }

	[Description( "Кол-во обычных слотов" )]
	public int usualSlots { get { return _usualSlots.Get(); } set { _usualSlots.Set( value ); } }

	[Description( "Дополнительное кол-во слотов для ЗВ" )]
	public int premiumSlots { get { return _premiumSlots.Get(); } set { _premiumSlots.Set( value ); } }

	[Description( "Максимальное кол-во неактивных слотов" )]
	public int maxInactiveUsualSlots { get { return _maxInactiveUsualSlots.Get(); } set { _maxInactiveUsualSlots.Set( value ); } }

	[Description( "Максимальное кол-во неактивных слотов с ЗВ" )]
	public int maxInactivePremiumSlots { get { return _maxInactivePremiumSlots.Get(); } set { _maxInactivePremiumSlots.Set( value ); } }

	[Description( "Цена реролла" )]
	public ResourcesTable rerollPrice { get { return _rerollPrice; } set { _rerollPrice.Assign( value ); } }

	[Description( "Выгорают ли ЗВ слоты" )]
	public bool premiumNotInactive { get { return _premiumNotInactive.Get(); } set { _premiumNotInactive.Set( value ); } }

	[Description( "Раз в сколько секунд подсвечивается произвольный некупленный слот" )]
	public int slotBlinkTime { get { return _slotBlinkTime.Get(); } set { _slotBlinkTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_groups = new UndoRedoAssignableList<DBPtr<RerollShopGroup>>( owner );
		_resourcesToPointsTable = new UndoRedoAssignableList<ResourceToPointsConversion>( owner );
		_usualSlots = new UndoRedo<int>( owner, 0 );
		_premiumSlots = new UndoRedo<int>( owner, 0 );
		_maxInactiveUsualSlots = new UndoRedo<int>( owner, 0 );
		_maxInactivePremiumSlots = new UndoRedo<int>( owner, 0 );
		_rerollPrice = new ResourcesTable( owner );
		_premiumNotInactive = new UndoRedo<bool>( owner, false );
		_slotBlinkTime = new UndoRedo<int>( owner, 0 );
		_groups.Changed += FireChangedEvent;
		_resourcesToPointsTable.Changed += FireChangedEvent;
		_usualSlots.Changed += FireChangedEvent;
		_premiumSlots.Changed += FireChangedEvent;
		_maxInactiveUsualSlots.Changed += FireChangedEvent;
		_maxInactivePremiumSlots.Changed += FireChangedEvent;
		_rerollPrice.Changed += FireChangedEvent;
		_premiumNotInactive.Changed += FireChangedEvent;
		_slotBlinkTime.Changed += FireChangedEvent;
	}

	public RerollShopSettings()
	{
		Initialize( GetOwner() );
	}

	public RerollShopSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RerollShopSettings( DBResource owner, RerollShopSettings source )
		: this(owner, source, true){}

	protected RerollShopSettings( DBResource owner, RerollShopSettings source, bool fireEvent )
	{
		_groups = new UndoRedoAssignableList<DBPtr<RerollShopGroup>>( owner );
		_groups.Assign( source.groups );
		_resourcesToPointsTable = new UndoRedoAssignableList<ResourceToPointsConversion>( owner );
		_resourcesToPointsTable.Assign( source.resourcesToPointsTable );
		_usualSlots = new UndoRedo<int>( owner, source.usualSlots );
		_premiumSlots = new UndoRedo<int>( owner, source.premiumSlots );
		_maxInactiveUsualSlots = new UndoRedo<int>( owner, source.maxInactiveUsualSlots );
		_maxInactivePremiumSlots = new UndoRedo<int>( owner, source.maxInactivePremiumSlots );
		_rerollPrice = new ResourcesTable( owner, source.rerollPrice );
		_premiumNotInactive = new UndoRedo<bool>( owner, source.premiumNotInactive );
		_slotBlinkTime = new UndoRedo<int>( owner, source.slotBlinkTime );
		_groups.Changed += FireChangedEvent;
		_resourcesToPointsTable.Changed += FireChangedEvent;
		_usualSlots.Changed += FireChangedEvent;
		_premiumSlots.Changed += FireChangedEvent;
		_maxInactiveUsualSlots.Changed += FireChangedEvent;
		_maxInactivePremiumSlots.Changed += FireChangedEvent;
		_rerollPrice.Changed += FireChangedEvent;
		_premiumNotInactive.Changed += FireChangedEvent;
		_slotBlinkTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RerollShopSettings source = _source as RerollShopSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RerollShopSettings" );
		groups = source.groups;
		resourcesToPointsTable = source.resourcesToPointsTable;
		usualSlots = source.usualSlots;
		premiumSlots = source.premiumSlots;
		maxInactiveUsualSlots = source.maxInactiveUsualSlots;
		maxInactivePremiumSlots = source.maxInactivePremiumSlots;
		rerollPrice = source.rerollPrice;
		premiumNotInactive = source.premiumNotInactive;
		slotBlinkTime = source.slotBlinkTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RerollShopSettings newParent = _newParent as RerollShopSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_groups.SetParent( newParent == null ? null : newParent._groups );
		_resourcesToPointsTable.SetParent( newParent == null ? null : newParent._resourcesToPointsTable );
		_usualSlots.SetParent( newParent == null ? null : newParent._usualSlots );
		_premiumSlots.SetParent( newParent == null ? null : newParent._premiumSlots );
		_maxInactiveUsualSlots.SetParent( newParent == null ? null : newParent._maxInactiveUsualSlots );
		_maxInactivePremiumSlots.SetParent( newParent == null ? null : newParent._maxInactivePremiumSlots );
		_rerollPrice.SetParent( newParent == null ? null : newParent._rerollPrice );
		_premiumNotInactive.SetParent( newParent == null ? null : newParent._premiumNotInactive );
		_slotBlinkTime.SetParent( newParent == null ? null : newParent._slotBlinkTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_groups.Reset();
		_resourcesToPointsTable.Reset();
		_usualSlots.Reset();
		_premiumSlots.Reset();
		_maxInactiveUsualSlots.Reset();
		_maxInactivePremiumSlots.Reset();
		_rerollPrice.Reset();
		_premiumNotInactive.Reset();
		_slotBlinkTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_groups.IsDerivedFromParent()
			&& _resourcesToPointsTable.IsDerivedFromParent()
			&& _usualSlots.IsDerivedFromParent()
			&& _premiumSlots.IsDerivedFromParent()
			&& _maxInactiveUsualSlots.IsDerivedFromParent()
			&& _maxInactivePremiumSlots.IsDerivedFromParent()
			&& _rerollPrice.IsDerivedFromParent()
			&& _premiumNotInactive.IsDerivedFromParent()
			&& _slotBlinkTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "groups" )
			_groups.Reset();
		else if ( fieldName == "resourcesToPointsTable" )
			_resourcesToPointsTable.Reset();
		else if ( fieldName == "usualSlots" )
			_usualSlots.Reset();
		else if ( fieldName == "premiumSlots" )
			_premiumSlots.Reset();
		else if ( fieldName == "maxInactiveUsualSlots" )
			_maxInactiveUsualSlots.Reset();
		else if ( fieldName == "maxInactivePremiumSlots" )
			_maxInactivePremiumSlots.Reset();
		else if ( fieldName == "rerollPrice" )
			_rerollPrice.Reset();
		else if ( fieldName == "premiumNotInactive" )
			_premiumNotInactive.Reset();
		else if ( fieldName == "slotBlinkTime" )
			_slotBlinkTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "groups" )
			return _groups.IsDerivedFromParent();
		if ( fieldName == "resourcesToPointsTable" )
			return _resourcesToPointsTable.IsDerivedFromParent();
		if ( fieldName == "usualSlots" )
			return _usualSlots.IsDerivedFromParent();
		if ( fieldName == "premiumSlots" )
			return _premiumSlots.IsDerivedFromParent();
		if ( fieldName == "maxInactiveUsualSlots" )
			return _maxInactiveUsualSlots.IsDerivedFromParent();
		if ( fieldName == "maxInactivePremiumSlots" )
			return _maxInactivePremiumSlots.IsDerivedFromParent();
		if ( fieldName == "rerollPrice" )
			return _rerollPrice.IsDerivedFromParent();
		if ( fieldName == "premiumNotInactive" )
			return _premiumNotInactive.IsDerivedFromParent();
		if ( fieldName == "slotBlinkTime" )
			return _slotBlinkTime.IsDerivedFromParent();
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
public class RerollShopSlot : DBResource
{
	private UndoRedoDBPtr<RerollShopSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<RerollShopSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedo<int> _backgroundId;

	[Description( "Id слота" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "Id кадра с подложкой (-1 - стандартная подложка)" )]
	public int backgroundId { get { return _backgroundId.Get(); } set { _backgroundId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RerollShopSlot>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_backgroundId = new UndoRedo<int>( owner, -1 );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_backgroundId.Changed += FireChangedEvent;
	}

	public RerollShopSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( RerollShopSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RerollShopSlot" );
		persistentId = source.persistentId;
		backgroundId = source.backgroundId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RerollShopSlot source = _source as RerollShopSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RerollShopSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RerollShopSlot newParent = rawParent == null ? null : rawParent.Get<RerollShopSlot>();
		if ( newParent == null && _newParent is RerollShopSlot )
			newParent = _newParent as RerollShopSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_backgroundId.SetParent( newParent == null ? null : newParent._backgroundId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_backgroundId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _backgroundId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "backgroundId" )
			_backgroundId.Reset();
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
		if ( fieldName == "backgroundId" )
			return _backgroundId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class LampRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<LampRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<LampRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<GoldLampEvent> _lamp;
	private TextRef _tooltip;
	private UndoRedo<int> _lifeTime;
	private UndoRedo<int> _maxBonus;
	private UndoRedo<int> _transactions;

	[Description( "Акция" )]
	public DBPtr<GoldLampEvent> lamp { get { return _lamp.Get(); } set { _lamp.Set( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Время действия (в секундах)" )]
	public int lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	[Description( "Максимальный бонус" )]
	[NameMapValue]
	public int maxBonus { get { return _maxBonus.Get(); } set { _maxBonus.Set( value ); } }

	[Description( "Количество транзакций" )]
	[NameMapValue]
	public int transactions { get { return _transactions.Get(); } set { _transactions.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LampRerollSlot>(owner);
		_lamp = new UndoRedoDBPtr<GoldLampEvent>( owner );
		_tooltip = new TextRef( owner, new TextRef() );
		_lifeTime = new UndoRedo<int>( owner, 0 );
		_maxBonus = new UndoRedo<int>( owner, 0 );
		_transactions = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_lamp.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_maxBonus.Changed += FireChangedEvent;
		_transactions.Changed += FireChangedEvent;
	}

	public LampRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( LampRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LampRerollSlot" );
		lamp = source.lamp;
		tooltip = source.tooltip;
		lifeTime = source.lifeTime;
		maxBonus = source.maxBonus;
		transactions = source.transactions;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LampRerollSlot source = _source as LampRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LampRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LampRerollSlot newParent = rawParent == null ? null : rawParent.Get<LampRerollSlot>();
		if ( newParent == null && _newParent is LampRerollSlot )
			newParent = _newParent as LampRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lamp.SetParent( newParent == null ? null : newParent._lamp );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_maxBonus.SetParent( newParent == null ? null : newParent._maxBonus );
		_transactions.SetParent( newParent == null ? null : newParent._transactions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lamp.Reset();
		_tooltip.Reset();
		_lifeTime.Reset();
		_maxBonus.Reset();
		_transactions.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lamp.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _maxBonus.IsDerivedFromParent()
			&& _transactions.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lamp" )
			_lamp.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "maxBonus" )
			_maxBonus.Reset();
		else if ( fieldName == "transactions" )
			_transactions.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lamp" )
			return _lamp.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "maxBonus" )
			return _maxBonus.IsDerivedFromParent();
		if ( fieldName == "transactions" )
			return _transactions.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class LootboxRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<LootboxRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<LootboxRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Lootbox> _lootbox;
	private UndoRedo<int> _count;

	[Description( "Add Lootbox to this field" )]
	public DBPtr<Lootbox> lootbox { get { return _lootbox.Get(); } set { _lootbox.Set( value ); } }

	[Description( "Lootboxes count" )]
	[NameMapValue]
	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LootboxRerollSlot>(owner);
		_lootbox = new UndoRedoDBPtr<Lootbox>( owner );
		_count = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_lootbox.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
	}

	public LootboxRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( LootboxRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LootboxRerollSlot" );
		lootbox = source.lootbox;
		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LootboxRerollSlot source = _source as LootboxRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LootboxRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LootboxRerollSlot newParent = rawParent == null ? null : rawParent.Get<LootboxRerollSlot>();
		if ( newParent == null && _newParent is LootboxRerollSlot )
			newParent = _newParent as LootboxRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lootbox.SetParent( newParent == null ? null : newParent._lootbox );
		_count.SetParent( newParent == null ? null : newParent._count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lootbox.Reset();
		_count.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lootbox.IsDerivedFromParent()
			&& _count.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lootbox" )
			_lootbox.Reset();
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
		if ( fieldName == "lootbox" )
			return _lootbox.IsDerivedFromParent();
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

[Custom("Social")]
public class PremiumRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<PremiumRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<PremiumRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _days;
	private TextRef _nameA;
	private TextRef _tooltipA;
	private UndoRedoDBPtr<Texture> _iconA;
	private TextRef _nameB;
	private TextRef _tooltipB;
	private UndoRedoDBPtr<Texture> _iconB;

	[Description( "Количество дней" )]
	[NameMapValue]
	public int days { get { return _days.Get(); } set { _days.Set( value ); } }

	public TextRef nameA { get { return _nameA; } set { _nameA.Assign( value ); } }

	public TextRef tooltipA { get { return _tooltipA; } set { _tooltipA.Assign( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> iconA { get { return _iconA.Get(); } set { _iconA.Set( value ); } }

	public TextRef nameB { get { return _nameB; } set { _nameB.Assign( value ); } }

	public TextRef tooltipB { get { return _tooltipB; } set { _tooltipB.Assign( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> iconB { get { return _iconB.Get(); } set { _iconB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PremiumRerollSlot>(owner);
		_days = new UndoRedo<int>( owner, 0 );
		_nameA = new TextRef( owner, new TextRef() );
		_tooltipA = new TextRef( owner, new TextRef() );
		_iconA = new UndoRedoDBPtr<Texture>( owner );
		_nameB = new TextRef( owner, new TextRef() );
		_tooltipB = new TextRef( owner, new TextRef() );
		_iconB = new UndoRedoDBPtr<Texture>( owner );
		___parent.Changed += FireChangedEvent;
		_days.Changed += FireChangedEvent;
		_nameA.Changed += FireChangedEvent;
		_tooltipA.Changed += FireChangedEvent;
		_iconA.Changed += FireChangedEvent;
		_nameB.Changed += FireChangedEvent;
		_tooltipB.Changed += FireChangedEvent;
		_iconB.Changed += FireChangedEvent;
	}

	public PremiumRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( PremiumRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PremiumRerollSlot" );
		days = source.days;
		nameA = source.nameA;
		tooltipA = source.tooltipA;
		iconA = source.iconA;
		nameB = source.nameB;
		tooltipB = source.tooltipB;
		iconB = source.iconB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PremiumRerollSlot source = _source as PremiumRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PremiumRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PremiumRerollSlot newParent = rawParent == null ? null : rawParent.Get<PremiumRerollSlot>();
		if ( newParent == null && _newParent is PremiumRerollSlot )
			newParent = _newParent as PremiumRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_days.SetParent( newParent == null ? null : newParent._days );
		_nameA.SetParent( newParent == null ? null : newParent._nameA );
		_tooltipA.SetParent( newParent == null ? null : newParent._tooltipA );
		_iconA.SetParent( newParent == null ? null : newParent._iconA );
		_nameB.SetParent( newParent == null ? null : newParent._nameB );
		_tooltipB.SetParent( newParent == null ? null : newParent._tooltipB );
		_iconB.SetParent( newParent == null ? null : newParent._iconB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_days.Reset();
		_nameA.Reset();
		_tooltipA.Reset();
		_iconA.Reset();
		_nameB.Reset();
		_tooltipB.Reset();
		_iconB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_days.IsDerivedFromParent()
			&& _nameA.IsDerivedFromParent()
			&& _tooltipA.IsDerivedFromParent()
			&& _iconA.IsDerivedFromParent()
			&& _nameB.IsDerivedFromParent()
			&& _tooltipB.IsDerivedFromParent()
			&& _iconB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "days" )
			_days.Reset();
		else if ( fieldName == "nameA" )
			_nameA.Reset();
		else if ( fieldName == "tooltipA" )
			_tooltipA.Reset();
		else if ( fieldName == "iconA" )
			_iconA.Reset();
		else if ( fieldName == "nameB" )
			_nameB.Reset();
		else if ( fieldName == "tooltipB" )
			_tooltipB.Reset();
		else if ( fieldName == "iconB" )
			_iconB.Reset();
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
		if ( fieldName == "nameA" )
			return _nameA.IsDerivedFromParent();
		if ( fieldName == "tooltipA" )
			return _tooltipA.IsDerivedFromParent();
		if ( fieldName == "iconA" )
			return _iconA.IsDerivedFromParent();
		if ( fieldName == "nameB" )
			return _nameB.IsDerivedFromParent();
		if ( fieldName == "tooltipB" )
			return _tooltipB.IsDerivedFromParent();
		if ( fieldName == "iconB" )
			return _iconB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("persistentId")]
[Custom("Social")]
public class RerollShopGroup : DBResource
{
	private UndoRedoDBPtr<RerollShopGroup> ___parent;
	[HideInOutliner]
	public new DBPtr<RerollShopGroup> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private UndoRedoAssignableList<GroupSlot> _slots;
	private UndoRedoAssignableList<RerollTimesToDropProbabilty> _rerollTimesToDropProbabilties;
	private UndoRedo<ERerollShopResourceType> _currencies;
	private UndoRedo<int> _minPoints;
	private UndoRedo<int> _maxPoints;
	private UndoRedo<int> _minUpgradeLevel;
	private UndoRedo<int> _maxUpgradeLevel;

	[Description( "ID группы" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "Доступные слоты" )]
	public libdb.IChangeableList<GroupSlot> slots { get { return _slots; } set { _slots.Assign( value ); } }

	[Description( "Вероятности появления группы после n рероллов" )]
	public libdb.IChangeableList<RerollTimesToDropProbabilty> rerollTimesToDropProbabilties { get { return _rerollTimesToDropProbabilties; } set { _rerollTimesToDropProbabilties.Assign( value ); } }

	[Description( "Ресурсы, за которые можно купить товары из группы" )]
	public ERerollShopResourceType currencies { get { return _currencies.Get(); } set { _currencies.Set( value ); } }

	[Description( "Минимальная цена в очках" )]
	public int minPoints { get { return _minPoints.Get(); } set { _minPoints.Set( value ); } }

	[Description( "Максимальная цена в очках" )]
	public int maxPoints { get { return _maxPoints.Get(); } set { _maxPoints.Set( value ); } }

	[Description( "Минимальная заточка талантов в этой группе (1-10), 0 - не используется" )]
	public int minUpgradeLevel { get { return _minUpgradeLevel.Get(); } set { _minUpgradeLevel.Set( value ); } }

	[Description( "Максимальная заточка талантов в этой группе (1-10), 0 - не используется" )]
	public int maxUpgradeLevel { get { return _maxUpgradeLevel.Get(); } set { _maxUpgradeLevel.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RerollShopGroup>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_slots = new UndoRedoAssignableList<GroupSlot>( owner );
		_rerollTimesToDropProbabilties = new UndoRedoAssignableList<RerollTimesToDropProbabilty>( owner );
		_currencies = new UndoRedo<ERerollShopResourceType>( owner, (ERerollShopResourceType)0 );
		_minPoints = new UndoRedo<int>( owner, 0 );
		_maxPoints = new UndoRedo<int>( owner, 0 );
		_minUpgradeLevel = new UndoRedo<int>( owner, 0 );
		_maxUpgradeLevel = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_slots.Changed += FireChangedEvent;
		_rerollTimesToDropProbabilties.Changed += FireChangedEvent;
		_currencies.Changed += FireChangedEvent;
		_minPoints.Changed += FireChangedEvent;
		_maxPoints.Changed += FireChangedEvent;
		_minUpgradeLevel.Changed += FireChangedEvent;
		_maxUpgradeLevel.Changed += FireChangedEvent;
	}

	public RerollShopGroup()
	{
		Initialize( this );
	}
	private void AssignSelf( RerollShopGroup source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RerollShopGroup" );
		persistentId = source.persistentId;
		slots = source.slots;
		rerollTimesToDropProbabilties = source.rerollTimesToDropProbabilties;
		currencies = source.currencies;
		minPoints = source.minPoints;
		maxPoints = source.maxPoints;
		minUpgradeLevel = source.minUpgradeLevel;
		maxUpgradeLevel = source.maxUpgradeLevel;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RerollShopGroup source = _source as RerollShopGroup;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RerollShopGroup" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RerollShopGroup newParent = rawParent == null ? null : rawParent.Get<RerollShopGroup>();
		if ( newParent == null && _newParent is RerollShopGroup )
			newParent = _newParent as RerollShopGroup;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_slots.SetParent( newParent == null ? null : newParent._slots );
		_rerollTimesToDropProbabilties.SetParent( newParent == null ? null : newParent._rerollTimesToDropProbabilties );
		_currencies.SetParent( newParent == null ? null : newParent._currencies );
		_minPoints.SetParent( newParent == null ? null : newParent._minPoints );
		_maxPoints.SetParent( newParent == null ? null : newParent._maxPoints );
		_minUpgradeLevel.SetParent( newParent == null ? null : newParent._minUpgradeLevel );
		_maxUpgradeLevel.SetParent( newParent == null ? null : newParent._maxUpgradeLevel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_slots.Reset();
		_rerollTimesToDropProbabilties.Reset();
		_currencies.Reset();
		_minPoints.Reset();
		_maxPoints.Reset();
		_minUpgradeLevel.Reset();
		_maxUpgradeLevel.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _slots.IsDerivedFromParent()
			&& _rerollTimesToDropProbabilties.IsDerivedFromParent()
			&& _currencies.IsDerivedFromParent()
			&& _minPoints.IsDerivedFromParent()
			&& _maxPoints.IsDerivedFromParent()
			&& _minUpgradeLevel.IsDerivedFromParent()
			&& _maxUpgradeLevel.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "slots" )
			_slots.Reset();
		else if ( fieldName == "rerollTimesToDropProbabilties" )
			_rerollTimesToDropProbabilties.Reset();
		else if ( fieldName == "currencies" )
			_currencies.Reset();
		else if ( fieldName == "minPoints" )
			_minPoints.Reset();
		else if ( fieldName == "maxPoints" )
			_maxPoints.Reset();
		else if ( fieldName == "minUpgradeLevel" )
			_minUpgradeLevel.Reset();
		else if ( fieldName == "maxUpgradeLevel" )
			_maxUpgradeLevel.Reset();
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
		if ( fieldName == "slots" )
			return _slots.IsDerivedFromParent();
		if ( fieldName == "rerollTimesToDropProbabilties" )
			return _rerollTimesToDropProbabilties.IsDerivedFromParent();
		if ( fieldName == "currencies" )
			return _currencies.IsDerivedFromParent();
		if ( fieldName == "minPoints" )
			return _minPoints.IsDerivedFromParent();
		if ( fieldName == "maxPoints" )
			return _maxPoints.IsDerivedFromParent();
		if ( fieldName == "minUpgradeLevel" )
			return _minUpgradeLevel.IsDerivedFromParent();
		if ( fieldName == "maxUpgradeLevel" )
			return _maxUpgradeLevel.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HeroRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<HeroRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;

	[Description( "Герой" )]
	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroRerollSlot>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
	}

	public HeroRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroRerollSlot" );
		hero = source.hero;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroRerollSlot source = _source as HeroRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroRerollSlot newParent = rawParent == null ? null : rawParent.Get<HeroRerollSlot>();
		if ( newParent == null && _newParent is HeroRerollSlot )
			newParent = _newParent as HeroRerollSlot;
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

[Custom("Social")]
public class ResourceRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<ResourceRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<ResourceRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _amount;
	private UndoRedo<ERerollShopResources> _resourceType;
	private ResourcesTable _resource;
	private TextRef _nameA;
	private TextRef _tooltipA;
	private UndoRedoDBPtr<Texture> _iconA;
	private TextRef _nameB;
	private TextRef _tooltipB;
	private UndoRedoDBPtr<Texture> _iconB;

	[Browsable( false )]
	[Description( "Количество ресурса" )]
	[NameMapValue]
	public int amount { get { return _amount.Get(); } set { _amount.Set( value ); } }

	[Browsable( false )]
	[Description( "Тип ресурса" )]
	public ERerollShopResources resourceType { get { return _resourceType.Get(); } set { _resourceType.Set( value ); } }

	[Description( "ресурс" )]
	public ResourcesTable resource { get { return _resource; } set { _resource.Assign( value ); } }

	public TextRef nameA { get { return _nameA; } set { _nameA.Assign( value ); } }

	public TextRef tooltipA { get { return _tooltipA; } set { _tooltipA.Assign( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> iconA { get { return _iconA.Get(); } set { _iconA.Set( value ); } }

	public TextRef nameB { get { return _nameB; } set { _nameB.Assign( value ); } }

	public TextRef tooltipB { get { return _tooltipB; } set { _tooltipB.Assign( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> iconB { get { return _iconB.Get(); } set { _iconB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ResourceRerollSlot>(owner);
		_amount = new UndoRedo<int>( owner, 0 );
		_resourceType = new UndoRedo<ERerollShopResources>( owner, ERerollShopResources.Resource1 );
		_resource = new ResourcesTable( owner );
		_nameA = new TextRef( owner, new TextRef() );
		_tooltipA = new TextRef( owner, new TextRef() );
		_iconA = new UndoRedoDBPtr<Texture>( owner );
		_nameB = new TextRef( owner, new TextRef() );
		_tooltipB = new TextRef( owner, new TextRef() );
		_iconB = new UndoRedoDBPtr<Texture>( owner );
		___parent.Changed += FireChangedEvent;
		_amount.Changed += FireChangedEvent;
		_resourceType.Changed += FireChangedEvent;
		_resource.Changed += FireChangedEvent;
		_nameA.Changed += FireChangedEvent;
		_tooltipA.Changed += FireChangedEvent;
		_iconA.Changed += FireChangedEvent;
		_nameB.Changed += FireChangedEvent;
		_tooltipB.Changed += FireChangedEvent;
		_iconB.Changed += FireChangedEvent;
	}

	public ResourceRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( ResourceRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ResourceRerollSlot" );
		amount = source.amount;
		resourceType = source.resourceType;
		resource = source.resource;
		nameA = source.nameA;
		tooltipA = source.tooltipA;
		iconA = source.iconA;
		nameB = source.nameB;
		tooltipB = source.tooltipB;
		iconB = source.iconB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ResourceRerollSlot source = _source as ResourceRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ResourceRerollSlot newParent = rawParent == null ? null : rawParent.Get<ResourceRerollSlot>();
		if ( newParent == null && _newParent is ResourceRerollSlot )
			newParent = _newParent as ResourceRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_amount.SetParent( newParent == null ? null : newParent._amount );
		_resourceType.SetParent( newParent == null ? null : newParent._resourceType );
		_resource.SetParent( newParent == null ? null : newParent._resource );
		_nameA.SetParent( newParent == null ? null : newParent._nameA );
		_tooltipA.SetParent( newParent == null ? null : newParent._tooltipA );
		_iconA.SetParent( newParent == null ? null : newParent._iconA );
		_nameB.SetParent( newParent == null ? null : newParent._nameB );
		_tooltipB.SetParent( newParent == null ? null : newParent._tooltipB );
		_iconB.SetParent( newParent == null ? null : newParent._iconB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_amount.Reset();
		_resourceType.Reset();
		_resource.Reset();
		_nameA.Reset();
		_tooltipA.Reset();
		_iconA.Reset();
		_nameB.Reset();
		_tooltipB.Reset();
		_iconB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_amount.IsDerivedFromParent()
			&& _resourceType.IsDerivedFromParent()
			&& _resource.IsDerivedFromParent()
			&& _nameA.IsDerivedFromParent()
			&& _tooltipA.IsDerivedFromParent()
			&& _iconA.IsDerivedFromParent()
			&& _nameB.IsDerivedFromParent()
			&& _tooltipB.IsDerivedFromParent()
			&& _iconB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "amount" )
			_amount.Reset();
		else if ( fieldName == "resourceType" )
			_resourceType.Reset();
		else if ( fieldName == "resource" )
			_resource.Reset();
		else if ( fieldName == "nameA" )
			_nameA.Reset();
		else if ( fieldName == "tooltipA" )
			_tooltipA.Reset();
		else if ( fieldName == "iconA" )
			_iconA.Reset();
		else if ( fieldName == "nameB" )
			_nameB.Reset();
		else if ( fieldName == "tooltipB" )
			_tooltipB.Reset();
		else if ( fieldName == "iconB" )
			_iconB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "amount" )
			return _amount.IsDerivedFromParent();
		if ( fieldName == "resourceType" )
			return _resourceType.IsDerivedFromParent();
		if ( fieldName == "resource" )
			return _resource.IsDerivedFromParent();
		if ( fieldName == "nameA" )
			return _nameA.IsDerivedFromParent();
		if ( fieldName == "tooltipA" )
			return _tooltipA.IsDerivedFromParent();
		if ( fieldName == "iconA" )
			return _iconA.IsDerivedFromParent();
		if ( fieldName == "nameB" )
			return _nameB.IsDerivedFromParent();
		if ( fieldName == "tooltipB" )
			return _tooltipB.IsDerivedFromParent();
		if ( fieldName == "iconB" )
			return _iconB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SkinRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<SkinRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<SkinRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<HeroSkin> _skin;

	[Description( "Скин" )]
	public DBPtr<HeroSkin> skin { get { return _skin.Get(); } set { _skin.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SkinRerollSlot>(owner);
		_skin = new UndoRedoDBPtr<HeroSkin>( owner );
		___parent.Changed += FireChangedEvent;
		_skin.Changed += FireChangedEvent;
	}

	public SkinRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( SkinRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SkinRerollSlot" );
		skin = source.skin;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SkinRerollSlot source = _source as SkinRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkinRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SkinRerollSlot newParent = rawParent == null ? null : rawParent.Get<SkinRerollSlot>();
		if ( newParent == null && _newParent is SkinRerollSlot )
			newParent = _newParent as SkinRerollSlot;
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

[Custom("Social")]
public class TalentRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<TalentRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Talent> _talent;

	[Description( "Талант" )]
	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentRerollSlot>(owner);
		_talent = new UndoRedoDBPtr<Talent>( owner );
		___parent.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
	}

	public TalentRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentRerollSlot" );
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentRerollSlot source = _source as TalentRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentRerollSlot newParent = rawParent == null ? null : rawParent.Get<TalentRerollSlot>();
		if ( newParent == null && _newParent is TalentRerollSlot )
			newParent = _newParent as TalentRerollSlot;
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
public class TalentsListRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<TalentsListRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentsListRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Talent>> _talents;

	[Description( "Таланты" )]
	public libdb.IChangeableList<DBPtr<Talent>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentsListRerollSlot>(owner);
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		___parent.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
	}

	public TalentsListRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentsListRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentsListRerollSlot" );
		talents = source.talents;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentsListRerollSlot source = _source as TalentsListRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsListRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentsListRerollSlot newParent = rawParent == null ? null : rawParent.Get<TalentsListRerollSlot>();
		if ( newParent == null && _newParent is TalentsListRerollSlot )
			newParent = _newParent as TalentsListRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_talents.SetParent( newParent == null ? null : newParent._talents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_talents.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_talents.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "talents" )
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
public class UpgradeHeroTalentsRerollSlot : RerollShopSlot
{
	private UndoRedoDBPtr<UpgradeHeroTalentsRerollSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<UpgradeHeroTalentsRerollSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<UpgradeHeroTalentsEvent> _upgradeHeroTalents;
	private TextRef _tooltip;
	private UndoRedo<int> _uses;

	[Description( "Add UpgradeHeroTalentsEvent to this field" )]
	public DBPtr<UpgradeHeroTalentsEvent> upgradeHeroTalents { get { return _upgradeHeroTalents.Get(); } set { _upgradeHeroTalents.Set( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Count adding uses" )]
	[NameMapValue]
	public int uses { get { return _uses.Get(); } set { _uses.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UpgradeHeroTalentsRerollSlot>(owner);
		_upgradeHeroTalents = new UndoRedoDBPtr<UpgradeHeroTalentsEvent>( owner );
		_tooltip = new TextRef( owner, new TextRef() );
		_uses = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_upgradeHeroTalents.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_uses.Changed += FireChangedEvent;
	}

	public UpgradeHeroTalentsRerollSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( UpgradeHeroTalentsRerollSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UpgradeHeroTalentsRerollSlot" );
		upgradeHeroTalents = source.upgradeHeroTalents;
		tooltip = source.tooltip;
		uses = source.uses;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UpgradeHeroTalentsRerollSlot source = _source as UpgradeHeroTalentsRerollSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UpgradeHeroTalentsRerollSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UpgradeHeroTalentsRerollSlot newParent = rawParent == null ? null : rawParent.Get<UpgradeHeroTalentsRerollSlot>();
		if ( newParent == null && _newParent is UpgradeHeroTalentsRerollSlot )
			newParent = _newParent as UpgradeHeroTalentsRerollSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_upgradeHeroTalents.SetParent( newParent == null ? null : newParent._upgradeHeroTalents );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_uses.SetParent( newParent == null ? null : newParent._uses );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_upgradeHeroTalents.Reset();
		_tooltip.Reset();
		_uses.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_upgradeHeroTalents.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _uses.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "upgradeHeroTalents" )
			_upgradeHeroTalents.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "uses" )
			_uses.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "upgradeHeroTalents" )
			return _upgradeHeroTalents.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "uses" )
			return _uses.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
