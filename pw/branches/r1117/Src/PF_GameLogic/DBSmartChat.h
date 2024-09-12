#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct SmartChatCategory;
struct SmartChatMessage;

struct SmartChatGroup : public DbResource
{
	DBRESOURCE_METHODS( SmartChatGroup );
public:
	vector< Ptr< SmartChatCategory > > categories;
	vector< Ptr< SmartChatMessage > > messages;

	SmartChatGroup();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SmartChatGroup& operator = ( const SmartChatGroup &_smartChatGroup ) { Assign( _smartChatGroup ); return *this; }
	SmartChatGroup( const SmartChatGroup &_smartChatGroup ) { Assign( _smartChatGroup ); }
	virtual void Assign( const SmartChatGroup &_smartChatGroup );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SmartChatGroup * pOther = dynamic_cast< const SmartChatGroup * > ( _pResource );
		if ( pOther ) SmartChatGroup::Assign( *pOther );
	}
};

struct SmartChatConfiguration : public SmartChatGroup
{
	DBRESOURCE_METHODS( SmartChatConfiguration );
public:
	string cancelCommandId;

	SmartChatConfiguration();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SmartChatConfiguration& operator = ( const SmartChatConfiguration &_smartChatConfiguration ) { Assign( _smartChatConfiguration ); return *this; }
	SmartChatConfiguration( const SmartChatConfiguration &_smartChatConfiguration ) { Assign( _smartChatConfiguration ); }
	virtual void Assign( const SmartChatConfiguration &_smartChatConfiguration );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SmartChatConfiguration * pOther = dynamic_cast< const SmartChatConfiguration * > ( _pResource );
		if ( pOther ) SmartChatConfiguration::Assign( *pOther );
	}
};

struct SmartChatCategory : public SmartChatGroup
{
	DBRESOURCE_METHODS( SmartChatCategory );
public:
	string commandId;
	CTextRef name;

	SmartChatCategory();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SmartChatCategory& operator = ( const SmartChatCategory &_smartChatCategory ) { Assign( _smartChatCategory ); return *this; }
	SmartChatCategory( const SmartChatCategory &_smartChatCategory ) { Assign( _smartChatCategory ); }
	virtual void Assign( const SmartChatCategory &_smartChatCategory );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SmartChatCategory * pOther = dynamic_cast< const SmartChatCategory * > ( _pResource );
		if ( pOther ) SmartChatCategory::Assign( *pOther );
	}
};

struct SmartChatMessage : public DbResource
{
	DBRESOURCE_METHODS( SmartChatMessage );
public:
	string commandId;
	bool showMarker;
	CTextRef text;

	SmartChatMessage();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SmartChatMessage& operator = ( const SmartChatMessage &_smartChatMessage ) { Assign( _smartChatMessage ); return *this; }
	SmartChatMessage( const SmartChatMessage &_smartChatMessage ) { Assign( _smartChatMessage ); }
	virtual void Assign( const SmartChatMessage &_smartChatMessage );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SmartChatMessage * pOther = dynamic_cast< const SmartChatMessage * > ( _pResource );
		if ( pOther ) SmartChatMessage::Assign( *pOther );
	}
};

}; // namespace NDb
