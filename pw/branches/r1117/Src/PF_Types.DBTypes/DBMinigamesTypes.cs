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
public enum ChangesApplyType
{
	DoNotApply = 0,
	ApplyDefault = 1,
	ApplyAbsoluteRotation = 2,
	ApplyAbsoluteAll = 3,
	ApplyRelational = 4,
};

public enum EBidonType
{
	None = 0,
	Speedclock = 1,
	Slowdownglue = 2,
	Magicpointer = 3,
	Palette = 4,
};

public enum MinigameClientType
{
	Local = 0,
	Remote = 1,
	Any = 2,
};

public enum MinigameVisualState
{
	None = 0,
	Session = 1,
	Clinic_Lobby = 2,
	Clinic_InGame = 3,
	Clinic_Shop = 4,
	Easel_Lobby = 5,
	Easel_LeavingLobby = 6,
	Easel_InGame = 7,
};

[TypeId(0xE96B3440)]
public class MinigamePlaceParams : DBResource
{
	private UndoRedoDBPtr<MinigamePlaceParams> ___parent;
	[HideInOutliner]
	public new DBPtr<MinigamePlaceParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<MinigameVisualStateChange>> _stateChanges;

	public libdb.IChangeableList<DBPtr<MinigameVisualStateChange>> stateChanges { get { return _stateChanges; } set { _stateChanges.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinigamePlaceParams>(owner);
		_stateChanges = new UndoRedoAssignableList<DBPtr<MinigameVisualStateChange>>( owner );
		___parent.Changed += FireChangedEvent;
		_stateChanges.Changed += FireChangedEvent;
	}

	public MinigamePlaceParams()
	{
		Initialize( this );
	}
	private void AssignSelf( MinigamePlaceParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinigamePlaceParams" );
		stateChanges = source.stateChanges;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinigamePlaceParams source = _source as MinigamePlaceParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinigamePlaceParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinigamePlaceParams newParent = rawParent == null ? null : rawParent.Get<MinigamePlaceParams>();
		if ( newParent == null && _newParent is MinigamePlaceParams )
			newParent = _newParent as MinigamePlaceParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stateChanges.SetParent( newParent == null ? null : newParent._stateChanges );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stateChanges.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stateChanges.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stateChanges" )
			_stateChanges.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "stateChanges" )
			return _stateChanges.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xE96AD341)]
public class MinigameVisualStateChange : DBResource
{
	private UndoRedoDBPtr<MinigameVisualStateChange> ___parent;
	[HideInOutliner]
	public new DBPtr<MinigameVisualStateChange> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<MinigameVisualState> _fromState;
	private UndoRedo<MinigameVisualState> _toState;
	private UndoRedo<MinigameClientType> _clientType;
	private AnimatedPlacement _newPlacement;
	private UndoRedo<ChangesApplyType> _changePlacement;

	public MinigameVisualState fromState { get { return _fromState.Get(); } set { _fromState.Set( value ); } }

	public MinigameVisualState toState { get { return _toState.Get(); } set { _toState.Set( value ); } }

	public MinigameClientType clientType { get { return _clientType.Get(); } set { _clientType.Set( value ); } }

	[Description( "Rotation and scale are absolute. Position is relative to minigame place position." )]
	public AnimatedPlacement newPlacement { get { return _newPlacement; } set { _newPlacement.Assign( value ); } }

	public ChangesApplyType changePlacement { get { return _changePlacement.Get(); } set { _changePlacement.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinigameVisualStateChange>(owner);
		_fromState = new UndoRedo<MinigameVisualState>( owner, MinigameVisualState.None );
		_toState = new UndoRedo<MinigameVisualState>( owner, MinigameVisualState.None );
		_clientType = new UndoRedo<MinigameClientType>( owner, MinigameClientType.Any );
		_newPlacement = new AnimatedPlacement( owner );
		_changePlacement = new UndoRedo<ChangesApplyType>( owner, ChangesApplyType.DoNotApply );
		___parent.Changed += FireChangedEvent;
		_fromState.Changed += FireChangedEvent;
		_toState.Changed += FireChangedEvent;
		_clientType.Changed += FireChangedEvent;
		_newPlacement.Changed += FireChangedEvent;
		_changePlacement.Changed += FireChangedEvent;
	}

	public MinigameVisualStateChange()
	{
		Initialize( this );
	}
	private void AssignSelf( MinigameVisualStateChange source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinigameVisualStateChange" );
		fromState = source.fromState;
		toState = source.toState;
		clientType = source.clientType;
		newPlacement = source.newPlacement;
		changePlacement = source.changePlacement;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinigameVisualStateChange source = _source as MinigameVisualStateChange;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinigameVisualStateChange" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinigameVisualStateChange newParent = rawParent == null ? null : rawParent.Get<MinigameVisualStateChange>();
		if ( newParent == null && _newParent is MinigameVisualStateChange )
			newParent = _newParent as MinigameVisualStateChange;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fromState.SetParent( newParent == null ? null : newParent._fromState );
		_toState.SetParent( newParent == null ? null : newParent._toState );
		_clientType.SetParent( newParent == null ? null : newParent._clientType );
		_newPlacement.SetParent( newParent == null ? null : newParent._newPlacement );
		_changePlacement.SetParent( newParent == null ? null : newParent._changePlacement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fromState.Reset();
		_toState.Reset();
		_clientType.Reset();
		_newPlacement.Reset();
		_changePlacement.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fromState.IsDerivedFromParent()
			&& _toState.IsDerivedFromParent()
			&& _clientType.IsDerivedFromParent()
			&& _newPlacement.IsDerivedFromParent()
			&& _changePlacement.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fromState" )
			_fromState.Reset();
		else if ( fieldName == "toState" )
			_toState.Reset();
		else if ( fieldName == "clientType" )
			_clientType.Reset();
		else if ( fieldName == "newPlacement" )
			_newPlacement.Reset();
		else if ( fieldName == "changePlacement" )
			_changePlacement.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fromState" )
			return _fromState.IsDerivedFromParent();
		if ( fieldName == "toState" )
			return _toState.IsDerivedFromParent();
		if ( fieldName == "clientType" )
			return _clientType.IsDerivedFromParent();
		if ( fieldName == "newPlacement" )
			return _newPlacement.IsDerivedFromParent();
		if ( fieldName == "changePlacement" )
			return _changePlacement.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
