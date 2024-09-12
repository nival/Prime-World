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
[DBVersion(0)]
[UseTypeName("MAPLST")]
public class MapList : DBResource
{
	private UndoRedoDBPtr<MapList> ___parent;
	[HideInOutliner]
	public new DBPtr<MapList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<AdvMapDescription>> _maps;

	[Description( "Список карт и режимов игры" )]
	public libdb.IChangeableList<DBPtr<AdvMapDescription>> maps { get { return _maps; } set { _maps.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MapList>(owner);
		_maps = new UndoRedoAssignableList<DBPtr<AdvMapDescription>>( owner );
		___parent.Changed += FireChangedEvent;
		_maps.Changed += FireChangedEvent;
	}

	public MapList()
	{
		Initialize( this );
	}
	private void AssignSelf( MapList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MapList" );
		maps = source.maps;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MapList source = _source as MapList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MapList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MapList newParent = rawParent == null ? null : rawParent.Get<MapList>();
		if ( newParent == null && _newParent is MapList )
			newParent = _newParent as MapList;
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

}; // namespace DBTypes
