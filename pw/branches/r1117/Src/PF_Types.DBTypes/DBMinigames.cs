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
public class Bidon : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Bidon __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Ability> _ability;
	private UndoRedo<string> _commonNode;
	private UndoRedo<string> _upperNode;
	private UndoRedo<string> _commonMarker;
	private UndoRedo<string> _upperMarker;

	public DBPtr<Ability> ability { get { return _ability.Get(); } set { _ability.Set( value ); } }

	public string commonNode { get { return _commonNode.Get(); } set { _commonNode.Set( value ); } }

	public string upperNode { get { return _upperNode.Get(); } set { _upperNode.Set( value ); } }

	public string commonMarker { get { return _commonMarker.Get(); } set { _commonMarker.Set( value ); } }

	public string upperMarker { get { return _upperMarker.Get(); } set { _upperMarker.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ability = new UndoRedoDBPtr<Ability>( owner );
		_commonNode = new UndoRedo<string>( owner, string.Empty );
		_upperNode = new UndoRedo<string>( owner, string.Empty );
		_commonMarker = new UndoRedo<string>( owner, string.Empty );
		_upperMarker = new UndoRedo<string>( owner, string.Empty );
		_ability.Changed += FireChangedEvent;
		_commonNode.Changed += FireChangedEvent;
		_upperNode.Changed += FireChangedEvent;
		_commonMarker.Changed += FireChangedEvent;
		_upperMarker.Changed += FireChangedEvent;
	}

	public Bidon()
	{
		Initialize( GetOwner() );
	}

	public Bidon( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Bidon( DBResource owner, Bidon source )
		: this(owner, source, true){}

	protected Bidon( DBResource owner, Bidon source, bool fireEvent )
	{
		_ability = new UndoRedoDBPtr<Ability>( owner, source.ability );
		_commonNode = new UndoRedo<string>( owner, source.commonNode );
		_upperNode = new UndoRedo<string>( owner, source.upperNode );
		_commonMarker = new UndoRedo<string>( owner, source.commonMarker );
		_upperMarker = new UndoRedo<string>( owner, source.upperMarker );
		_ability.Changed += FireChangedEvent;
		_commonNode.Changed += FireChangedEvent;
		_upperNode.Changed += FireChangedEvent;
		_commonMarker.Changed += FireChangedEvent;
		_upperMarker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Bidon source = _source as Bidon;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Bidon" );
		ability = source.ability;
		commonNode = source.commonNode;
		upperNode = source.upperNode;
		commonMarker = source.commonMarker;
		upperMarker = source.upperMarker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Bidon newParent = _newParent as Bidon;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ability.SetParent( newParent == null ? null : newParent._ability );
		_commonNode.SetParent( newParent == null ? null : newParent._commonNode );
		_upperNode.SetParent( newParent == null ? null : newParent._upperNode );
		_commonMarker.SetParent( newParent == null ? null : newParent._commonMarker );
		_upperMarker.SetParent( newParent == null ? null : newParent._upperMarker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ability.Reset();
		_commonNode.Reset();
		_upperNode.Reset();
		_commonMarker.Reset();
		_upperMarker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ability.IsDerivedFromParent()
			&& _commonNode.IsDerivedFromParent()
			&& _upperNode.IsDerivedFromParent()
			&& _commonMarker.IsDerivedFromParent()
			&& _upperMarker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ability" )
			_ability.Reset();
		else if ( fieldName == "commonNode" )
			_commonNode.Reset();
		else if ( fieldName == "upperNode" )
			_upperNode.Reset();
		else if ( fieldName == "commonMarker" )
			_commonMarker.Reset();
		else if ( fieldName == "upperMarker" )
			_upperMarker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ability" )
			return _ability.IsDerivedFromParent();
		if ( fieldName == "commonNode" )
			return _commonNode.IsDerivedFromParent();
		if ( fieldName == "upperNode" )
			return _upperNode.IsDerivedFromParent();
		if ( fieldName == "commonMarker" )
			return _commonMarker.IsDerivedFromParent();
		if ( fieldName == "upperMarker" )
			return _upperMarker.IsDerivedFromParent();
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

[FactoryImpl("Construct", "PF_Minigames::MinigamesMain", "MinigamesMain.h")]
public class DBMinigamesCommon : MinigamesBasic
{
	private UndoRedoDBPtr<DBMinigamesCommon> ___parent;
	[HideInOutliner]
	public new DBPtr<DBMinigamesCommon> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ViewCamera _cameraOptions;
	private UndoRedo<bool> _smoothCamera;
	private TextRef _namePoolMelee;
	private TextRef _namePoolRange;
	private TextRef _namePoolSiege;
	private UndoRedoAssignableList<Bidon> _sessionBidonAbilities;

	[Description( "Camera position at minigame lobby screen" )]
	public ViewCamera cameraOptions { get { return _cameraOptions; } set { _cameraOptions.Assign( value ); } }

	public bool smoothCamera { get { return _smoothCamera.Get(); } set { _smoothCamera.Set( value ); } }

	[Category( "Creeps Pool" )]
	[Description( "Name pool for melee creeps" )]
	public TextRef namePoolMelee { get { return _namePoolMelee; } set { _namePoolMelee.Assign( value ); } }

	[Category( "Creeps Pool" )]
	[Description( "Name pool for range creeps" )]
	public TextRef namePoolRange { get { return _namePoolRange; } set { _namePoolRange.Assign( value ); } }

	[Category( "Creeps Pool" )]
	[Description( "Name pool for siege creeps" )]
	public TextRef namePoolSiege { get { return _namePoolSiege; } set { _namePoolSiege.Assign( value ); } }

	[Description( "Abilities in session for bidons" )]
	[EnumArray(typeof(EBidonType))]
	public libdb.IChangeableList<Bidon> sessionBidonAbilities { get { return _sessionBidonAbilities; } set { _sessionBidonAbilities.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBMinigamesCommon>(owner);
		_cameraOptions = new ViewCamera( owner );
		_smoothCamera = new UndoRedo<bool>( owner, false );
		_namePoolMelee = new TextRef( owner, new TextRef() );
		_namePoolRange = new TextRef( owner, new TextRef() );
		_namePoolSiege = new TextRef( owner, new TextRef() );
		_sessionBidonAbilities = new UndoRedoAssignableList<Bidon>( owner, typeof( EBidonType ) );
		___parent.Changed += FireChangedEvent;
		_cameraOptions.Changed += FireChangedEvent;
		_smoothCamera.Changed += FireChangedEvent;
		_namePoolMelee.Changed += FireChangedEvent;
		_namePoolRange.Changed += FireChangedEvent;
		_namePoolSiege.Changed += FireChangedEvent;
		_sessionBidonAbilities.Changed += FireChangedEvent;
	}

	public DBMinigamesCommon()
	{
		Initialize( this );
	}
	private void AssignSelf( DBMinigamesCommon source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBMinigamesCommon" );
		cameraOptions = source.cameraOptions;
		smoothCamera = source.smoothCamera;
		namePoolMelee = source.namePoolMelee;
		namePoolRange = source.namePoolRange;
		namePoolSiege = source.namePoolSiege;
		sessionBidonAbilities = source.sessionBidonAbilities;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBMinigamesCommon source = _source as DBMinigamesCommon;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMinigamesCommon" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBMinigamesCommon newParent = rawParent == null ? null : rawParent.Get<DBMinigamesCommon>();
		if ( newParent == null && _newParent is DBMinigamesCommon )
			newParent = _newParent as DBMinigamesCommon;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cameraOptions.SetParent( newParent == null ? null : newParent._cameraOptions );
		_smoothCamera.SetParent( newParent == null ? null : newParent._smoothCamera );
		_namePoolMelee.SetParent( newParent == null ? null : newParent._namePoolMelee );
		_namePoolRange.SetParent( newParent == null ? null : newParent._namePoolRange );
		_namePoolSiege.SetParent( newParent == null ? null : newParent._namePoolSiege );
		_sessionBidonAbilities.SetParent( newParent == null ? null : newParent._sessionBidonAbilities );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cameraOptions.Reset();
		_smoothCamera.Reset();
		_namePoolMelee.Reset();
		_namePoolRange.Reset();
		_namePoolSiege.Reset();
		_sessionBidonAbilities.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cameraOptions.IsDerivedFromParent()
			&& _smoothCamera.IsDerivedFromParent()
			&& _namePoolMelee.IsDerivedFromParent()
			&& _namePoolRange.IsDerivedFromParent()
			&& _namePoolSiege.IsDerivedFromParent()
			&& _sessionBidonAbilities.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cameraOptions" )
			_cameraOptions.Reset();
		else if ( fieldName == "smoothCamera" )
			_smoothCamera.Reset();
		else if ( fieldName == "namePoolMelee" )
			_namePoolMelee.Reset();
		else if ( fieldName == "namePoolRange" )
			_namePoolRange.Reset();
		else if ( fieldName == "namePoolSiege" )
			_namePoolSiege.Reset();
		else if ( fieldName == "sessionBidonAbilities" )
			_sessionBidonAbilities.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cameraOptions" )
			return _cameraOptions.IsDerivedFromParent();
		if ( fieldName == "smoothCamera" )
			return _smoothCamera.IsDerivedFromParent();
		if ( fieldName == "namePoolMelee" )
			return _namePoolMelee.IsDerivedFromParent();
		if ( fieldName == "namePoolRange" )
			return _namePoolRange.IsDerivedFromParent();
		if ( fieldName == "namePoolSiege" )
			return _namePoolSiege.IsDerivedFromParent();
		if ( fieldName == "sessionBidonAbilities" )
			return _sessionBidonAbilities.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
