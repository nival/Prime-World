// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBSessionMessages.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SessionMessages );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientHardwareErrorMessages::ClientHardwareErrorMessages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClientHardwareErrorMessages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &errorMessage );
	saver.Add( 3, &lowMemoryError );
	saver.Add( 4, &shader3compatibilityError );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClientHardwareErrorMessages::operator&( IXmlSaver &saver )
{
	saver.Add( "errorMessage", &errorMessage );
	saver.Add( "lowMemoryError", &lowMemoryError );
	saver.Add( "shader3compatibilityError", &shader3compatibilityError );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DXErrorMessages::DXErrorMessages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DXErrorMessages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &title );
	saver.Add( 3, &errorMessage );
	saver.Add( 4, &lowMemoryMessage );
	saver.Add( 5, &lowVidMemMessage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DXErrorMessages::operator&( IXmlSaver &saver )
{
	saver.Add( "title", &title );
	saver.Add( "errorMessage", &errorMessage );
	saver.Add( "lowMemoryMessage", &lowMemoryMessage );
	saver.Add( "lowVidMemMessage", &lowVidMemMessage );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionMessages::SessionMessages()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionMessages::operator&( IBinSaver &saver )
{
	saver.Add( 2, &clientHardwareErrorMessages );
	saver.Add( 3, &dxErrorMessages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionMessages::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionMessages* parentPtr = (SessionMessages*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionMessages::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "clientHardwareErrorMessages", &clientHardwareErrorMessages );
	saver.Add( "dxErrorMessages", &dxErrorMessages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionMessages::Assign( const SessionMessages& _sessionMessages )
{
	clientHardwareErrorMessages.errorMessage = _sessionMessages.clientHardwareErrorMessages.errorMessage;
	clientHardwareErrorMessages.lowMemoryError = _sessionMessages.clientHardwareErrorMessages.lowMemoryError;
	clientHardwareErrorMessages.shader3compatibilityError = _sessionMessages.clientHardwareErrorMessages.shader3compatibilityError;
	dxErrorMessages.title = _sessionMessages.dxErrorMessages.title;
	dxErrorMessages.errorMessage = _sessionMessages.dxErrorMessages.errorMessage;
	dxErrorMessages.lowMemoryMessage = _sessionMessages.dxErrorMessages.lowMemoryMessage;
	dxErrorMessages.lowVidMemMessage = _sessionMessages.dxErrorMessages.lowVidMemMessage;
}
}; // namespace NDb
