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
public enum EConsumableOrigin
{
	Default = 0,
	Shop = 1,
	Minigame = 2,
	Pickupable = 3,
	Applicator = 4,
	Script = 5,
};

[Custom("Social")]
[DBVersion(1)]
[TypeId(0x0F68CB80)]
[UseTypeName("ARCT")]
public class Consumable : Ability
{
	private UndoRedoDBPtr<Consumable> ___parent;
	[HideInOutliner]
	public new DBPtr<Consumable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _naftaCost;
	private UndoRedo<int> _maxQuantity;
	private UndoRedoDBPtr<GameObject> _gameObject;
	private UndoRedo<bool> _isPotion;
	private UndoRedo<string> _persistentId;

	[Category( "Logic" )]
	[Description( "Cost of artifact" )]
	public int naftaCost { get { return _naftaCost.Get(); } set { _naftaCost.Set( value ); } }

	[Category( "Logic" )]
	[Description( "Maximum quantity in one slot (stacking). Set 0 if item doesn't spend on use" )]
	[IntMin(0)]
	public int maxQuantity { get { return _maxQuantity.Get(); } set { _maxQuantity.Set( value ); } }

	[Category( "Visual" )]
	[Description( "Visual object for lying consumable( chest, etc..)" )]
	public DBPtr<GameObject> gameObject { get { return _gameObject.Get(); } set { _gameObject.Set( value ); } }

	[Category( "Logic" )]
	[Description( "Flag for determining potions" )]
	public bool isPotion { get { return _isPotion.Get(); } set { _isPotion.Set( value ); } }

	[Description( "Global consumable ID" )]
	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Consumable>(owner);
		_naftaCost = new UndoRedo<int>( owner, 0 );
		_maxQuantity = new UndoRedo<int>( owner, 1 );
		_gameObject = new UndoRedoDBPtr<GameObject>( owner );
		_isPotion = new UndoRedo<bool>( owner, false );
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_naftaCost.Changed += FireChangedEvent;
		_maxQuantity.Changed += FireChangedEvent;
		_gameObject.Changed += FireChangedEvent;
		_isPotion.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
	}

	public Consumable()
	{
		Initialize( this );
	}
	private void AssignSelf( Consumable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Consumable" );
		naftaCost = source.naftaCost;
		maxQuantity = source.maxQuantity;
		gameObject = source.gameObject;
		isPotion = source.isPotion;
		persistentId = source.persistentId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Consumable source = _source as Consumable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Consumable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Consumable newParent = rawParent == null ? null : rawParent.Get<Consumable>();
		if ( newParent == null && _newParent is Consumable )
			newParent = _newParent as Consumable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_naftaCost.SetParent( newParent == null ? null : newParent._naftaCost );
		_maxQuantity.SetParent( newParent == null ? null : newParent._maxQuantity );
		_gameObject.SetParent( newParent == null ? null : newParent._gameObject );
		_isPotion.SetParent( newParent == null ? null : newParent._isPotion );
		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_naftaCost.Reset();
		_maxQuantity.Reset();
		_gameObject.Reset();
		_isPotion.Reset();
		_persistentId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_naftaCost.IsDerivedFromParent()
			&& _maxQuantity.IsDerivedFromParent()
			&& _gameObject.IsDerivedFromParent()
			&& _isPotion.IsDerivedFromParent()
			&& _persistentId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "naftaCost" )
			_naftaCost.Reset();
		else if ( fieldName == "maxQuantity" )
			_maxQuantity.Reset();
		else if ( fieldName == "gameObject" )
			_gameObject.Reset();
		else if ( fieldName == "isPotion" )
			_isPotion.Reset();
		else if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "naftaCost" )
			return _naftaCost.IsDerivedFromParent();
		if ( fieldName == "maxQuantity" )
			return _maxQuantity.IsDerivedFromParent();
		if ( fieldName == "gameObject" )
			return _gameObject.IsDerivedFromParent();
		if ( fieldName == "isPotion" )
			return _isPotion.IsDerivedFromParent();
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0F68CB81)]
[UseTypeName("CNSH")]
public class ConsumablesShop : DBResource
{
	private UndoRedoDBPtr<ConsumablesShop> ___parent;
	[HideInOutliner]
	public new DBPtr<ConsumablesShop> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Consumable>> _items;
	private UndoRedo<float> _interactionRadius;
	private UndoRedo<bool> _secretShop;

	[Description( "List of consumables" )]
	public libdb.IChangeableList<DBPtr<Consumable>> items { get { return _items; } set { _items.Assign( value ); } }

	[Description( "Interaction radius" )]
	[FloatMin(0)]
	public float interactionRadius { get { return _interactionRadius.Get(); } set { _interactionRadius.Set( value ); } }

	[Description( "True if shop is secret" )]
	public bool secretShop { get { return _secretShop.Get(); } set { _secretShop.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConsumablesShop>(owner);
		_items = new UndoRedoAssignableList<DBPtr<Consumable>>( owner );
		_interactionRadius = new UndoRedo<float>( owner, 10.0f );
		_secretShop = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
		_interactionRadius.Changed += FireChangedEvent;
		_secretShop.Changed += FireChangedEvent;
	}

	public ConsumablesShop()
	{
		Initialize( this );
	}
	private void AssignSelf( ConsumablesShop source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConsumablesShop" );
		items = source.items;
		interactionRadius = source.interactionRadius;
		secretShop = source.secretShop;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConsumablesShop source = _source as ConsumablesShop;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConsumablesShop" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConsumablesShop newParent = rawParent == null ? null : rawParent.Get<ConsumablesShop>();
		if ( newParent == null && _newParent is ConsumablesShop )
			newParent = _newParent as ConsumablesShop;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_items.SetParent( newParent == null ? null : newParent._items );
		_interactionRadius.SetParent( newParent == null ? null : newParent._interactionRadius );
		_secretShop.SetParent( newParent == null ? null : newParent._secretShop );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_items.Reset();
		_interactionRadius.Reset();
		_secretShop.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_items.IsDerivedFromParent()
			&& _interactionRadius.IsDerivedFromParent()
			&& _secretShop.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "items" )
			_items.Reset();
		else if ( fieldName == "interactionRadius" )
			_interactionRadius.Reset();
		else if ( fieldName == "secretShop" )
			_secretShop.Reset();
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
		if ( fieldName == "interactionRadius" )
			return _interactionRadius.IsDerivedFromParent();
		if ( fieldName == "secretShop" )
			return _secretShop.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
