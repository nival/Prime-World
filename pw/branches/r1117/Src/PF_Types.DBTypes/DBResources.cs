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
public class CurrencyDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CurrencyDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _Id;
	private TextRef _Description;
	private UndoRedoDBPtr<Texture> _Icon;

	[Custom("Social")]
	[Description( "Currency id" )]
	public string Id { get { return _Id.Get(); } set { _Id.Set( value ); } }

	[Custom("Social")]
	[Description( "Currency description" )]
	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	[Custom("Social")]
	[Description( "Currency icon" )]
	public DBPtr<Texture> Icon { get { return _Icon.Get(); } set { _Icon.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Id = new UndoRedo<string>( owner, string.Empty );
		_Description = new TextRef( owner, new TextRef() );
		_Icon = new UndoRedoDBPtr<Texture>( owner );
		_Id.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_Icon.Changed += FireChangedEvent;
	}

	public CurrencyDescription()
	{
		Initialize( GetOwner() );
	}

	public CurrencyDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CurrencyDescription( DBResource owner, CurrencyDescription source )
		: this(owner, source, true){}

	protected CurrencyDescription( DBResource owner, CurrencyDescription source, bool fireEvent )
	{
		_Id = new UndoRedo<string>( owner, source.Id );
		_Description = new TextRef( owner, source.Description );
		_Icon = new UndoRedoDBPtr<Texture>( owner, source.Icon );
		_Id.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_Icon.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CurrencyDescription source = _source as CurrencyDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CurrencyDescription" );
		Id = source.Id;
		Description = source.Description;
		Icon = source.Icon;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CurrencyDescription newParent = _newParent as CurrencyDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Id.SetParent( newParent == null ? null : newParent._Id );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		_Icon.SetParent( newParent == null ? null : newParent._Icon );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Id.Reset();
		_Description.Reset();
		_Icon.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Id.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			&& _Icon.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Id" )
			_Id.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
		else if ( fieldName == "Icon" )
			_Icon.Reset();
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
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
		if ( fieldName == "Icon" )
			return _Icon.IsDerivedFromParent();
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
[UseTypeName("CRLS")]
public class CurrencyDescriptionList : DBResource
{
	private UndoRedoDBPtr<CurrencyDescriptionList> ___parent;
	[HideInOutliner]
	public new DBPtr<CurrencyDescriptionList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<CurrencyDescription> _CurrencyList;

	[Custom("Social")]
	public libdb.IChangeableList<CurrencyDescription> CurrencyList { get { return _CurrencyList; } set { _CurrencyList.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CurrencyDescriptionList>(owner);
		_CurrencyList = new UndoRedoAssignableList<CurrencyDescription>( owner );
		___parent.Changed += FireChangedEvent;
		_CurrencyList.Changed += FireChangedEvent;
	}

	public CurrencyDescriptionList()
	{
		Initialize( this );
	}
	private void AssignSelf( CurrencyDescriptionList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CurrencyDescriptionList" );
		CurrencyList = source.CurrencyList;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CurrencyDescriptionList source = _source as CurrencyDescriptionList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CurrencyDescriptionList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CurrencyDescriptionList newParent = rawParent == null ? null : rawParent.Get<CurrencyDescriptionList>();
		if ( newParent == null && _newParent is CurrencyDescriptionList )
			newParent = _newParent as CurrencyDescriptionList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_CurrencyList.SetParent( newParent == null ? null : newParent._CurrencyList );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_CurrencyList.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_CurrencyList.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "CurrencyList" )
			_CurrencyList.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "CurrencyList" )
			return _CurrencyList.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
