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
public class SmartChatGroup : DBResource
{
	private UndoRedoDBPtr<SmartChatGroup> ___parent;
	[HideInOutliner]
	public new DBPtr<SmartChatGroup> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<SmartChatCategory>> _categories;
	private UndoRedoAssignableList<DBPtr<SmartChatMessage>> _messages;

	public libdb.IChangeableList<DBPtr<SmartChatCategory>> categories { get { return _categories; } set { _categories.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<SmartChatMessage>> messages { get { return _messages; } set { _messages.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SmartChatGroup>(owner);
		_categories = new UndoRedoAssignableList<DBPtr<SmartChatCategory>>( owner );
		_messages = new UndoRedoAssignableList<DBPtr<SmartChatMessage>>( owner );
		___parent.Changed += FireChangedEvent;
		_categories.Changed += FireChangedEvent;
		_messages.Changed += FireChangedEvent;
	}

	public SmartChatGroup()
	{
		Initialize( this );
	}
	private void AssignSelf( SmartChatGroup source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SmartChatGroup" );
		categories = source.categories;
		messages = source.messages;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SmartChatGroup source = _source as SmartChatGroup;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SmartChatGroup" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SmartChatGroup newParent = rawParent == null ? null : rawParent.Get<SmartChatGroup>();
		if ( newParent == null && _newParent is SmartChatGroup )
			newParent = _newParent as SmartChatGroup;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_categories.SetParent( newParent == null ? null : newParent._categories );
		_messages.SetParent( newParent == null ? null : newParent._messages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_categories.Reset();
		_messages.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_categories.IsDerivedFromParent()
			&& _messages.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "categories" )
			_categories.Reset();
		else if ( fieldName == "messages" )
			_messages.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "categories" )
			return _categories.IsDerivedFromParent();
		if ( fieldName == "messages" )
			return _messages.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("SCCFG")]
public class SmartChatConfiguration : SmartChatGroup
{
	private UndoRedoDBPtr<SmartChatConfiguration> ___parent;
	[HideInOutliner]
	public new DBPtr<SmartChatConfiguration> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _cancelCommandId;

	[Description( "Идентификатор команды Cancel/Back для бинда" )]
	public string cancelCommandId { get { return _cancelCommandId.Get(); } set { _cancelCommandId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SmartChatConfiguration>(owner);
		_cancelCommandId = new UndoRedo<string>( owner, "cmd_smart_chat_cancel" );
		___parent.Changed += FireChangedEvent;
		_cancelCommandId.Changed += FireChangedEvent;
	}

	public SmartChatConfiguration()
	{
		Initialize( this );
	}
	private void AssignSelf( SmartChatConfiguration source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SmartChatConfiguration" );
		cancelCommandId = source.cancelCommandId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SmartChatConfiguration source = _source as SmartChatConfiguration;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SmartChatConfiguration" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SmartChatConfiguration newParent = rawParent == null ? null : rawParent.Get<SmartChatConfiguration>();
		if ( newParent == null && _newParent is SmartChatConfiguration )
			newParent = _newParent as SmartChatConfiguration;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cancelCommandId.SetParent( newParent == null ? null : newParent._cancelCommandId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cancelCommandId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cancelCommandId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cancelCommandId" )
			_cancelCommandId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cancelCommandId" )
			return _cancelCommandId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("SCCAT")]
public class SmartChatCategory : SmartChatGroup
{
	private UndoRedoDBPtr<SmartChatCategory> ___parent;
	[HideInOutliner]
	public new DBPtr<SmartChatCategory> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _commandId;
	private TextRef _name;

	[Description( "Идентификатор команды для бинда" )]
	public string commandId { get { return _commandId.Get(); } set { _commandId.Set( value ); } }

	[Description( "Название категории для отображения" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SmartChatCategory>(owner);
		_commandId = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_commandId.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public SmartChatCategory()
	{
		Initialize( this );
	}
	private void AssignSelf( SmartChatCategory source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SmartChatCategory" );
		commandId = source.commandId;
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SmartChatCategory source = _source as SmartChatCategory;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SmartChatCategory" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SmartChatCategory newParent = rawParent == null ? null : rawParent.Get<SmartChatCategory>();
		if ( newParent == null && _newParent is SmartChatCategory )
			newParent = _newParent as SmartChatCategory;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_commandId.SetParent( newParent == null ? null : newParent._commandId );
		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_commandId.Reset();
		_name.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_commandId.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "commandId" )
			_commandId.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "commandId" )
			return _commandId.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class SmartChatMessage : DBResource
{
	private UndoRedoDBPtr<SmartChatMessage> ___parent;
	[HideInOutliner]
	public new DBPtr<SmartChatMessage> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _commandId;
	private UndoRedo<bool> _showMarker;
	private TextRef _text;

	[Description( "Уникальный идентификатор сообщения (передается по сети и интерпретируется клиентом, а также идентификатор команды для бинда" )]
	public string commandId { get { return _commandId.Get(); } set { _commandId.Set( value ); } }

	[Description( "Показывать ли маркер на отправителе" )]
	public bool showMarker { get { return _showMarker.Get(); } set { _showMarker.Set( value ); } }

	[Description( "Текст сообщения" )]
	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SmartChatMessage>(owner);
		_commandId = new UndoRedo<string>( owner, string.Empty );
		_showMarker = new UndoRedo<bool>( owner, false );
		_text = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_commandId.Changed += FireChangedEvent;
		_showMarker.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public SmartChatMessage()
	{
		Initialize( this );
	}
	private void AssignSelf( SmartChatMessage source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SmartChatMessage" );
		commandId = source.commandId;
		showMarker = source.showMarker;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SmartChatMessage source = _source as SmartChatMessage;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SmartChatMessage" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SmartChatMessage newParent = rawParent == null ? null : rawParent.Get<SmartChatMessage>();
		if ( newParent == null && _newParent is SmartChatMessage )
			newParent = _newParent as SmartChatMessage;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_commandId.SetParent( newParent == null ? null : newParent._commandId );
		_showMarker.SetParent( newParent == null ? null : newParent._showMarker );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_commandId.Reset();
		_showMarker.Reset();
		_text.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_commandId.IsDerivedFromParent()
			&& _showMarker.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "commandId" )
			_commandId.Reset();
		else if ( fieldName == "showMarker" )
			_showMarker.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "commandId" )
			return _commandId.IsDerivedFromParent();
		if ( fieldName == "showMarker" )
			return _showMarker.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
