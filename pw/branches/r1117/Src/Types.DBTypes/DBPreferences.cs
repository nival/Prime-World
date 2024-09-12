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
public enum ControlVarType
{
	CheckBox = 0,
	ComboBoxInterval = 1,
	Slider = 2,
	DisplayModeComboBox = 3,
};

public class ComboBoxDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ComboBoxDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _value;
	private TextRef _userName;

	public float value { get { return _value.Get(); } set { _value.Set( value ); } }

	public TextRef userName { get { return _userName; } set { _userName.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_value = new UndoRedo<float>( owner, 0.0f );
		_userName = new TextRef( owner, new TextRef() );
		_value.Changed += FireChangedEvent;
		_userName.Changed += FireChangedEvent;
	}

	public ComboBoxDescription()
	{
		Initialize( GetOwner() );
	}

	public ComboBoxDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ComboBoxDescription( DBResource owner, ComboBoxDescription source )
		: this(owner, source, true){}

	protected ComboBoxDescription( DBResource owner, ComboBoxDescription source, bool fireEvent )
	{
		_value = new UndoRedo<float>( owner, source.value );
		_userName = new TextRef( owner, source.userName );
		_value.Changed += FireChangedEvent;
		_userName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ComboBoxDescription source = _source as ComboBoxDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ComboBoxDescription" );
		value = source.value;
		userName = source.userName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ComboBoxDescription newParent = _newParent as ComboBoxDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_value.SetParent( newParent == null ? null : newParent._value );
		_userName.SetParent( newParent == null ? null : newParent._userName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_value.Reset();
		_userName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_value.IsDerivedFromParent()
			&& _userName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "userName" )
			_userName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "userName" )
			return _userName.IsDerivedFromParent();
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

[IndexField("varId")]
public class NameValue : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private NameValue __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _varId;
	private UndoRedo<int> _value;

	public string varId { get { return _varId.Get(); } set { _varId.Set( value ); } }

	public int value { get { return _value.Get(); } set { _value.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_varId = new UndoRedo<string>( owner, string.Empty );
		_value = new UndoRedo<int>( owner, -1000 );
		_varId.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
	}

	public NameValue()
	{
		Initialize( GetOwner() );
	}

	public NameValue( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public NameValue( DBResource owner, NameValue source )
		: this(owner, source, true){}

	protected NameValue( DBResource owner, NameValue source, bool fireEvent )
	{
		_varId = new UndoRedo<string>( owner, source.varId );
		_value = new UndoRedo<int>( owner, source.value );
		_varId.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		NameValue source = _source as NameValue;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NameValue" );
		varId = source.varId;
		value = source.value;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		NameValue newParent = _newParent as NameValue;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_varId.SetParent( newParent == null ? null : newParent._varId );
		_value.SetParent( newParent == null ? null : newParent._value );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_varId.Reset();
		_value.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_varId.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "varId" )
			_varId.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "varId" )
			return _varId.IsDerivedFromParent();
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
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

[IndexField("presetName")]
public class PreferencesPreset : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PreferencesPreset __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _presetName;
	private UndoRedoAssignableList<NameValue> _data;

	public string presetName { get { return _presetName.Get(); } set { _presetName.Set( value ); } }

	public libdb.IChangeableList<NameValue> data { get { return _data; } set { _data.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_presetName = new UndoRedo<string>( owner, string.Empty );
		_data = new UndoRedoAssignableList<NameValue>( owner );
		_presetName.Changed += FireChangedEvent;
		_data.Changed += FireChangedEvent;
	}

	public PreferencesPreset()
	{
		Initialize( GetOwner() );
	}

	public PreferencesPreset( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PreferencesPreset( DBResource owner, PreferencesPreset source )
		: this(owner, source, true){}

	protected PreferencesPreset( DBResource owner, PreferencesPreset source, bool fireEvent )
	{
		_presetName = new UndoRedo<string>( owner, source.presetName );
		_data = new UndoRedoAssignableList<NameValue>( owner );
		_data.Assign( source.data );
		_presetName.Changed += FireChangedEvent;
		_data.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PreferencesPreset source = _source as PreferencesPreset;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PreferencesPreset" );
		presetName = source.presetName;
		data = source.data;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PreferencesPreset newParent = _newParent as PreferencesPreset;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_presetName.SetParent( newParent == null ? null : newParent._presetName );
		_data.SetParent( newParent == null ? null : newParent._data );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_presetName.Reset();
		_data.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_presetName.IsDerivedFromParent()
			&& _data.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "presetName" )
			_presetName.Reset();
		else if ( fieldName == "data" )
			_data.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "presetName" )
			return _presetName.IsDerivedFromParent();
		if ( fieldName == "data" )
			return _data.IsDerivedFromParent();
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

[IndexField("varId")]
public class PrefVariable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PrefVariable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _varId;
	private UndoRedo<string> _commandName;
	private UndoRedo<ControlVarType> _controlVarType;
	private UndoRedoAssignableList<ComboBoxDescription> _comboBoxDescription;
	private UndoRedo<string> _applyCommandName;
	private UndoRedo<string> _enabledFromOtherVarId;

	public string varId { get { return _varId.Get(); } set { _varId.Set( value ); } }

	public string commandName { get { return _commandName.Get(); } set { _commandName.Set( value ); } }

	public ControlVarType controlVarType { get { return _controlVarType.Get(); } set { _controlVarType.Set( value ); } }

	public libdb.IChangeableList<ComboBoxDescription> comboBoxDescription { get { return _comboBoxDescription; } set { _comboBoxDescription.Assign( value ); } }

	public string applyCommandName { get { return _applyCommandName.Get(); } set { _applyCommandName.Set( value ); } }

	public string enabledFromOtherVarId { get { return _enabledFromOtherVarId.Get(); } set { _enabledFromOtherVarId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_varId = new UndoRedo<string>( owner, string.Empty );
		_commandName = new UndoRedo<string>( owner, string.Empty );
		_controlVarType = new UndoRedo<ControlVarType>( owner, ControlVarType.CheckBox );
		_comboBoxDescription = new UndoRedoAssignableList<ComboBoxDescription>( owner );
		_applyCommandName = new UndoRedo<string>( owner, string.Empty );
		_enabledFromOtherVarId = new UndoRedo<string>( owner, string.Empty );
		_varId.Changed += FireChangedEvent;
		_commandName.Changed += FireChangedEvent;
		_controlVarType.Changed += FireChangedEvent;
		_comboBoxDescription.Changed += FireChangedEvent;
		_applyCommandName.Changed += FireChangedEvent;
		_enabledFromOtherVarId.Changed += FireChangedEvent;
	}

	public PrefVariable()
	{
		Initialize( GetOwner() );
	}

	public PrefVariable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PrefVariable( DBResource owner, PrefVariable source )
		: this(owner, source, true){}

	protected PrefVariable( DBResource owner, PrefVariable source, bool fireEvent )
	{
		_varId = new UndoRedo<string>( owner, source.varId );
		_commandName = new UndoRedo<string>( owner, source.commandName );
		_controlVarType = new UndoRedo<ControlVarType>( owner, source.controlVarType );
		_comboBoxDescription = new UndoRedoAssignableList<ComboBoxDescription>( owner );
		_comboBoxDescription.Assign( source.comboBoxDescription );
		_applyCommandName = new UndoRedo<string>( owner, source.applyCommandName );
		_enabledFromOtherVarId = new UndoRedo<string>( owner, source.enabledFromOtherVarId );
		_varId.Changed += FireChangedEvent;
		_commandName.Changed += FireChangedEvent;
		_controlVarType.Changed += FireChangedEvent;
		_comboBoxDescription.Changed += FireChangedEvent;
		_applyCommandName.Changed += FireChangedEvent;
		_enabledFromOtherVarId.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PrefVariable source = _source as PrefVariable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PrefVariable" );
		varId = source.varId;
		commandName = source.commandName;
		controlVarType = source.controlVarType;
		comboBoxDescription = source.comboBoxDescription;
		applyCommandName = source.applyCommandName;
		enabledFromOtherVarId = source.enabledFromOtherVarId;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PrefVariable newParent = _newParent as PrefVariable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_varId.SetParent( newParent == null ? null : newParent._varId );
		_commandName.SetParent( newParent == null ? null : newParent._commandName );
		_controlVarType.SetParent( newParent == null ? null : newParent._controlVarType );
		_comboBoxDescription.SetParent( newParent == null ? null : newParent._comboBoxDescription );
		_applyCommandName.SetParent( newParent == null ? null : newParent._applyCommandName );
		_enabledFromOtherVarId.SetParent( newParent == null ? null : newParent._enabledFromOtherVarId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_varId.Reset();
		_commandName.Reset();
		_controlVarType.Reset();
		_comboBoxDescription.Reset();
		_applyCommandName.Reset();
		_enabledFromOtherVarId.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_varId.IsDerivedFromParent()
			&& _commandName.IsDerivedFromParent()
			&& _controlVarType.IsDerivedFromParent()
			&& _comboBoxDescription.IsDerivedFromParent()
			&& _applyCommandName.IsDerivedFromParent()
			&& _enabledFromOtherVarId.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "varId" )
			_varId.Reset();
		else if ( fieldName == "commandName" )
			_commandName.Reset();
		else if ( fieldName == "controlVarType" )
			_controlVarType.Reset();
		else if ( fieldName == "comboBoxDescription" )
			_comboBoxDescription.Reset();
		else if ( fieldName == "applyCommandName" )
			_applyCommandName.Reset();
		else if ( fieldName == "enabledFromOtherVarId" )
			_enabledFromOtherVarId.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "varId" )
			return _varId.IsDerivedFromParent();
		if ( fieldName == "commandName" )
			return _commandName.IsDerivedFromParent();
		if ( fieldName == "controlVarType" )
			return _controlVarType.IsDerivedFromParent();
		if ( fieldName == "comboBoxDescription" )
			return _comboBoxDescription.IsDerivedFromParent();
		if ( fieldName == "applyCommandName" )
			return _applyCommandName.IsDerivedFromParent();
		if ( fieldName == "enabledFromOtherVarId" )
			return _enabledFromOtherVarId.IsDerivedFromParent();
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

public class Preferences : DBResource
{
	private UndoRedoDBPtr<Preferences> ___parent;
	[HideInOutliner]
	public new DBPtr<Preferences> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<PrefVariable> _variables;
	private UndoRedoAssignableList<PreferencesPreset> _presets;

	public libdb.IChangeableList<PrefVariable> variables { get { return _variables; } set { _variables.Assign( value ); } }

	public libdb.IChangeableList<PreferencesPreset> presets { get { return _presets; } set { _presets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Preferences>(owner);
		_variables = new UndoRedoAssignableList<PrefVariable>( owner );
		_presets = new UndoRedoAssignableList<PreferencesPreset>( owner );
		___parent.Changed += FireChangedEvent;
		_variables.Changed += FireChangedEvent;
		_presets.Changed += FireChangedEvent;
	}

	public Preferences()
	{
		Initialize( this );
	}
	private void AssignSelf( Preferences source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Preferences" );
		variables = source.variables;
		presets = source.presets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Preferences source = _source as Preferences;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Preferences" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Preferences newParent = rawParent == null ? null : rawParent.Get<Preferences>();
		if ( newParent == null && _newParent is Preferences )
			newParent = _newParent as Preferences;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_variables.SetParent( newParent == null ? null : newParent._variables );
		_presets.SetParent( newParent == null ? null : newParent._presets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_variables.Reset();
		_presets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_variables.IsDerivedFromParent()
			&& _presets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "variables" )
			_variables.Reset();
		else if ( fieldName == "presets" )
			_presets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "variables" )
			return _variables.IsDerivedFromParent();
		if ( fieldName == "presets" )
			return _presets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
