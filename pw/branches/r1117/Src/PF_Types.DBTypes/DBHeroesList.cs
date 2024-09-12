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
[DBVersion(1)]
[UseTypeName("HRDB")]
public class HeroesDB : DBResource
{
	private UndoRedoDBPtr<HeroesDB> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroesDB> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Hero>> _heroes;

	public libdb.IChangeableList<DBPtr<Hero>> heroes { get { return _heroes; } set { _heroes.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroesDB>(owner);
		_heroes = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		___parent.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
	}

	public HeroesDB()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroesDB source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroesDB" );
		heroes = source.heroes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroesDB source = _source as HeroesDB;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroesDB" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroesDB newParent = rawParent == null ? null : rawParent.Get<HeroesDB>();
		if ( newParent == null && _newParent is HeroesDB )
			newParent = _newParent as HeroesDB;
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

}; // namespace DBTypes
