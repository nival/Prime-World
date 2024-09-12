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
[NonTerminal]
[Custom("Social")]
public class Cutscene : DBResource
{
	private UndoRedoDBPtr<Cutscene> ___parent;
	[HideInOutliner]
	public new DBPtr<Cutscene> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _CutsceneScriptNameA;
	private UndoRedo<string> _CutsceneScriptNameB;

	[Description( "Строковый идентефикатор кат сцены для фракции A." )]
	public string CutsceneScriptNameA { get { return _CutsceneScriptNameA.Get(); } set { _CutsceneScriptNameA.Set( value ); } }

	[Description( "Строковый идентефикатор кат сцены для фракции B." )]
	public string CutsceneScriptNameB { get { return _CutsceneScriptNameB.Get(); } set { _CutsceneScriptNameB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Cutscene>(owner);
		_CutsceneScriptNameA = new UndoRedo<string>( owner, string.Empty );
		_CutsceneScriptNameB = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_CutsceneScriptNameA.Changed += FireChangedEvent;
		_CutsceneScriptNameB.Changed += FireChangedEvent;
	}

	public Cutscene()
	{
		Initialize( this );
	}
	private void AssignSelf( Cutscene source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Cutscene" );
		CutsceneScriptNameA = source.CutsceneScriptNameA;
		CutsceneScriptNameB = source.CutsceneScriptNameB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Cutscene source = _source as Cutscene;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Cutscene" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Cutscene newParent = rawParent == null ? null : rawParent.Get<Cutscene>();
		if ( newParent == null && _newParent is Cutscene )
			newParent = _newParent as Cutscene;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_CutsceneScriptNameA.SetParent( newParent == null ? null : newParent._CutsceneScriptNameA );
		_CutsceneScriptNameB.SetParent( newParent == null ? null : newParent._CutsceneScriptNameB );
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

}; // namespace DBTypes
