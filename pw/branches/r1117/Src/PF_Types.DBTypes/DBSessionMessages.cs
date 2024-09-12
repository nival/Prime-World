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
public class ClientHardwareErrorMessages : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ClientHardwareErrorMessages __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _errorMessage;
	private TextRef _lowMemoryError;
	private TextRef _shader3compatibilityError;

	[Description( "Общее сообщение о несовместимости с железом" )]
	public TextRef errorMessage { get { return _errorMessage; } set { _errorMessage.Assign( value ); } }

	[Description( "Причина 1: сообщение о нехватке памяти" )]
	public TextRef lowMemoryError { get { return _lowMemoryError; } set { _lowMemoryError.Assign( value ); } }

	[Description( "Причина 2: неподдерживаются шейдеры 3.0" )]
	public TextRef shader3compatibilityError { get { return _shader3compatibilityError; } set { _shader3compatibilityError.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_errorMessage = new TextRef( owner, new TextRef() );
		_lowMemoryError = new TextRef( owner, new TextRef() );
		_shader3compatibilityError = new TextRef( owner, new TextRef() );
		_errorMessage.Changed += FireChangedEvent;
		_lowMemoryError.Changed += FireChangedEvent;
		_shader3compatibilityError.Changed += FireChangedEvent;
	}

	public ClientHardwareErrorMessages()
	{
		Initialize( GetOwner() );
	}

	public ClientHardwareErrorMessages( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ClientHardwareErrorMessages( DBResource owner, ClientHardwareErrorMessages source )
		: this(owner, source, true){}

	protected ClientHardwareErrorMessages( DBResource owner, ClientHardwareErrorMessages source, bool fireEvent )
	{
		_errorMessage = new TextRef( owner, source.errorMessage );
		_lowMemoryError = new TextRef( owner, source.lowMemoryError );
		_shader3compatibilityError = new TextRef( owner, source.shader3compatibilityError );
		_errorMessage.Changed += FireChangedEvent;
		_lowMemoryError.Changed += FireChangedEvent;
		_shader3compatibilityError.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ClientHardwareErrorMessages source = _source as ClientHardwareErrorMessages;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClientHardwareErrorMessages" );
		errorMessage = source.errorMessage;
		lowMemoryError = source.lowMemoryError;
		shader3compatibilityError = source.shader3compatibilityError;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ClientHardwareErrorMessages newParent = _newParent as ClientHardwareErrorMessages;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_errorMessage.SetParent( newParent == null ? null : newParent._errorMessage );
		_lowMemoryError.SetParent( newParent == null ? null : newParent._lowMemoryError );
		_shader3compatibilityError.SetParent( newParent == null ? null : newParent._shader3compatibilityError );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_errorMessage.Reset();
		_lowMemoryError.Reset();
		_shader3compatibilityError.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_errorMessage.IsDerivedFromParent()
			&& _lowMemoryError.IsDerivedFromParent()
			&& _shader3compatibilityError.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "errorMessage" )
			_errorMessage.Reset();
		else if ( fieldName == "lowMemoryError" )
			_lowMemoryError.Reset();
		else if ( fieldName == "shader3compatibilityError" )
			_shader3compatibilityError.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "errorMessage" )
			return _errorMessage.IsDerivedFromParent();
		if ( fieldName == "lowMemoryError" )
			return _lowMemoryError.IsDerivedFromParent();
		if ( fieldName == "shader3compatibilityError" )
			return _shader3compatibilityError.IsDerivedFromParent();
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

public class DXErrorMessages : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DXErrorMessages __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _title;
	private TextRef _errorMessage;
	private TextRef _lowMemoryMessage;
	private TextRef _lowVidMemMessage;

	[Description( "Dialog title" )]
	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	[Description( "Общее сообщение об ошибке DX (D3DERR_INVALIDCALL)" )]
	public TextRef errorMessage { get { return _errorMessage; } set { _errorMessage.Assign( value ); } }

	[Description( "сообщение о нехватке памяти (E_OUTOFMEMORY)" )]
	public TextRef lowMemoryMessage { get { return _lowMemoryMessage; } set { _lowMemoryMessage.Assign( value ); } }

	[Description( "сообщение о нехватке видеопамяти (D3DERR_OUTOFVIDEOMEMORY)" )]
	public TextRef lowVidMemMessage { get { return _lowVidMemMessage; } set { _lowVidMemMessage.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_title = new TextRef( owner, new TextRef() );
		_errorMessage = new TextRef( owner, new TextRef() );
		_lowMemoryMessage = new TextRef( owner, new TextRef() );
		_lowVidMemMessage = new TextRef( owner, new TextRef() );
		_title.Changed += FireChangedEvent;
		_errorMessage.Changed += FireChangedEvent;
		_lowMemoryMessage.Changed += FireChangedEvent;
		_lowVidMemMessage.Changed += FireChangedEvent;
	}

	public DXErrorMessages()
	{
		Initialize( GetOwner() );
	}

	public DXErrorMessages( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DXErrorMessages( DBResource owner, DXErrorMessages source )
		: this(owner, source, true){}

	protected DXErrorMessages( DBResource owner, DXErrorMessages source, bool fireEvent )
	{
		_title = new TextRef( owner, source.title );
		_errorMessage = new TextRef( owner, source.errorMessage );
		_lowMemoryMessage = new TextRef( owner, source.lowMemoryMessage );
		_lowVidMemMessage = new TextRef( owner, source.lowVidMemMessage );
		_title.Changed += FireChangedEvent;
		_errorMessage.Changed += FireChangedEvent;
		_lowMemoryMessage.Changed += FireChangedEvent;
		_lowVidMemMessage.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DXErrorMessages source = _source as DXErrorMessages;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DXErrorMessages" );
		title = source.title;
		errorMessage = source.errorMessage;
		lowMemoryMessage = source.lowMemoryMessage;
		lowVidMemMessage = source.lowVidMemMessage;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DXErrorMessages newParent = _newParent as DXErrorMessages;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_title.SetParent( newParent == null ? null : newParent._title );
		_errorMessage.SetParent( newParent == null ? null : newParent._errorMessage );
		_lowMemoryMessage.SetParent( newParent == null ? null : newParent._lowMemoryMessage );
		_lowVidMemMessage.SetParent( newParent == null ? null : newParent._lowVidMemMessage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_title.Reset();
		_errorMessage.Reset();
		_lowMemoryMessage.Reset();
		_lowVidMemMessage.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _errorMessage.IsDerivedFromParent()
			&& _lowMemoryMessage.IsDerivedFromParent()
			&& _lowVidMemMessage.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "errorMessage" )
			_errorMessage.Reset();
		else if ( fieldName == "lowMemoryMessage" )
			_lowMemoryMessage.Reset();
		else if ( fieldName == "lowVidMemMessage" )
			_lowVidMemMessage.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "errorMessage" )
			return _errorMessage.IsDerivedFromParent();
		if ( fieldName == "lowMemoryMessage" )
			return _lowMemoryMessage.IsDerivedFromParent();
		if ( fieldName == "lowVidMemMessage" )
			return _lowVidMemMessage.IsDerivedFromParent();
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

public class SessionMessages : DBResource
{
	private UndoRedoDBPtr<SessionMessages> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionMessages> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ClientHardwareErrorMessages _clientHardwareErrorMessages;
	private DXErrorMessages _dxErrorMessages;

	[Description( "Сообщения о несовместимости с железом" )]
	public ClientHardwareErrorMessages clientHardwareErrorMessages { get { return _clientHardwareErrorMessages; } set { _clientHardwareErrorMessages.Assign( value ); } }

	[Description( "Сообщения о проблемах графического движка" )]
	public DXErrorMessages dxErrorMessages { get { return _dxErrorMessages; } set { _dxErrorMessages.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionMessages>(owner);
		_clientHardwareErrorMessages = new ClientHardwareErrorMessages( owner );
		_dxErrorMessages = new DXErrorMessages( owner );
		___parent.Changed += FireChangedEvent;
		_clientHardwareErrorMessages.Changed += FireChangedEvent;
		_dxErrorMessages.Changed += FireChangedEvent;
	}

	public SessionMessages()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionMessages source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionMessages" );
		clientHardwareErrorMessages = source.clientHardwareErrorMessages;
		dxErrorMessages = source.dxErrorMessages;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionMessages source = _source as SessionMessages;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionMessages" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionMessages newParent = rawParent == null ? null : rawParent.Get<SessionMessages>();
		if ( newParent == null && _newParent is SessionMessages )
			newParent = _newParent as SessionMessages;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_clientHardwareErrorMessages.SetParent( newParent == null ? null : newParent._clientHardwareErrorMessages );
		_dxErrorMessages.SetParent( newParent == null ? null : newParent._dxErrorMessages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_clientHardwareErrorMessages.Reset();
		_dxErrorMessages.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_clientHardwareErrorMessages.IsDerivedFromParent()
			&& _dxErrorMessages.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "clientHardwareErrorMessages" )
			_clientHardwareErrorMessages.Reset();
		else if ( fieldName == "dxErrorMessages" )
			_dxErrorMessages.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "clientHardwareErrorMessages" )
			return _clientHardwareErrorMessages.IsDerivedFromParent();
		if ( fieldName == "dxErrorMessages" )
			return _dxErrorMessages.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
