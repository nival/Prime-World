#pragma once

#include "../Scripts/NameMap.h"

namespace NMainLoop
{
_interface IScreenBase;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SInfoMessage
{
	string id;
	string type;
	NScript::NamedValues values;

	SInfoMessage()
	{}

	SInfoMessage( const string & _id, const string & _type )
		: id( _id )
		, type( _type )
	{
		values.Clear();
	}

	SInfoMessage( const string & _id, const string & _type, const NScript::NamedValues & _values )
		: id( _id )
		, type( _type )
		, values( _values )
	{}

	template<typename T>
	void AddParam( const string & name, const T & _value )
	{
		values.SetValue( name, _value );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IInfoMessageCallback : public IObjectBase
{
	virtual bool ShouldDisplayInfoMessage( const SInfoMessage & msg ) = 0;
	virtual void ProcessInfoMessageResult( const SInfoMessage & msg, const string & result ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EInfoMessagePriority
{
	INFOMESSAGEPRIORITY_LOW,
	INFOMESSAGEPRIORITY_NORMAL,
	INFOMESSAGEPRIORITY_HIGH,
	INFOMESSAGEPRIORITY_CRITICAL,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SInfoMessageDesc
{
	SInfoMessage msg;
	EInfoMessagePriority priority;
	IScreenBase *pOnlyForScreen;
	CPtr<IInfoMessageCallback> pCallback;
	bool autoCloseIfNotValid;
	bool modal;

	SInfoMessageDesc()
		: priority( INFOMESSAGEPRIORITY_NORMAL )
		, pOnlyForScreen(0)
		, autoCloseIfNotValid( false )
		, modal( false )
	{}

	SInfoMessageDesc( IInfoMessageCallback *_pCallback, bool _autoCloseIfNotValid, IScreenBase *_pOnlyForScreen, EInfoMessagePriority _priority, const SInfoMessage & _msg, bool _modal )
		: priority( _priority )
		, pOnlyForScreen( _pOnlyForScreen )
		, msg( _msg )
		, pCallback( _pCallback )
		, autoCloseIfNotValid( _autoCloseIfNotValid )
		, modal( _modal )
	{}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddInfoMessage( const SInfoMessageDesc & msgDesc );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
