// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBSmartChat.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SmartChatGroup );
REGISTER_DBRESOURCE( SmartChatConfiguration );
REGISTER_DBRESOURCE( SmartChatCategory );
REGISTER_DBRESOURCE( SmartChatMessage );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartChatGroup::SmartChatGroup()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatGroup::operator&( IBinSaver &saver )
{
	saver.Add( 2, &categories );
	saver.Add( 3, &messages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatGroup::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SmartChatGroup* parentPtr = (SmartChatGroup*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatGroup::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "categories", &categories );
	saver.Add( "messages", &messages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatGroup::Assign( const SmartChatGroup& _smartChatGroup )
{
	categories = _smartChatGroup.categories;
	messages = _smartChatGroup.messages;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartChatConfiguration::SmartChatConfiguration() :
		cancelCommandId( "cmd_smart_chat_cancel" )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatConfiguration::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SmartChatGroup*)this );
	saver.Add( 2, &cancelCommandId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatConfiguration::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SmartChatConfiguration* parentPtr = (SmartChatConfiguration*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatConfiguration::SerializeSelf( IXmlSaver &saver )
{
	SmartChatGroup::SerializeSelf( saver );
	saver.Add( "cancelCommandId", &cancelCommandId );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatConfiguration::Assign( const SmartChatConfiguration& _smartChatConfiguration )
{
	cancelCommandId = _smartChatConfiguration.cancelCommandId;
	categories = _smartChatConfiguration.categories;
	messages = _smartChatConfiguration.messages;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartChatCategory::SmartChatCategory()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatCategory::operator&( IBinSaver &saver )
{
	saver.Add( 1, (SmartChatGroup*)this );
	saver.Add( 2, &commandId );
	saver.Add( 3, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatCategory::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SmartChatCategory* parentPtr = (SmartChatCategory*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatCategory::SerializeSelf( IXmlSaver &saver )
{
	SmartChatGroup::SerializeSelf( saver );
	saver.Add( "commandId", &commandId );
	saver.Add( "name", &name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatCategory::Assign( const SmartChatCategory& _smartChatCategory )
{
	commandId = _smartChatCategory.commandId;
	name = _smartChatCategory.name;
	categories = _smartChatCategory.categories;
	messages = _smartChatCategory.messages;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartChatMessage::SmartChatMessage() :
		showMarker( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatMessage::operator&( IBinSaver &saver )
{
	saver.Add( 2, &commandId );
	saver.Add( 3, &showMarker );
	saver.Add( 4, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SmartChatMessage::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SmartChatMessage* parentPtr = (SmartChatMessage*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatMessage::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "commandId", &commandId );
	saver.Add( "showMarker", &showMarker );
	saver.Add( "text", &text );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SmartChatMessage::Assign( const SmartChatMessage& _smartChatMessage )
{
	commandId = _smartChatMessage.commandId;
	showMarker = _smartChatMessage.showMarker;
	text = _smartChatMessage.text;
}
}; // namespace NDb
