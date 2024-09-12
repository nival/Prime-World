#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct ClientHardwareErrorMessages
{
public:
	CTextRef errorMessage;
	CTextRef lowMemoryError;
	CTextRef shader3compatibilityError;

	ClientHardwareErrorMessages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DXErrorMessages
{
public:
	CTextRef title;
	CTextRef errorMessage;
	CTextRef lowMemoryMessage;
	CTextRef lowVidMemMessage;

	DXErrorMessages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SessionMessages : public DbResource
{
	DBRESOURCE_METHODS( SessionMessages );
public:
	ClientHardwareErrorMessages clientHardwareErrorMessages;
	DXErrorMessages dxErrorMessages;

	SessionMessages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionMessages& operator = ( const SessionMessages &_sessionMessages ) { Assign( _sessionMessages ); return *this; }
	SessionMessages( const SessionMessages &_sessionMessages ) { Assign( _sessionMessages ); }
	virtual void Assign( const SessionMessages &_sessionMessages );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionMessages * pOther = dynamic_cast< const SessionMessages * > ( _pResource );
		if ( pOther ) SessionMessages::Assign( *pOther );
	}
};

}; // namespace NDb
