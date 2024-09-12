#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
enum ControlVarType
{
	CONTROLVARTYPE_CHECKBOX = 0,
	CONTROLVARTYPE_COMBOBOXINTERVAL = 1,
	CONTROLVARTYPE_SLIDER = 2,
	CONTROLVARTYPE_DISPLAYMODECOMBOBOX = 3,
};

const char *EnumToString( const ControlVarType value );
const ControlVarType StringToEnum_ControlVarType( const char* value );

template <>
struct KnownEnum< ControlVarType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const ControlVarType value ) { return EnumToString( value ); }
	static const ControlVarType ToEnum( const char* value ) { return StringToEnum_ControlVarType( value ); }
	static const ControlVarType ToEnum( const string& value ) { return StringToEnum_ControlVarType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

struct ComboBoxDescription
{
public:
	float value;
	CTextRef userName;

	ComboBoxDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct NameValue
{
public:
	string varId;
	int value;

	NameValue();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PreferencesPreset
{
public:
	string presetName;
	vector< NameValue > data;

	PreferencesPreset();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PrefVariable
{
public:
	string varId;
	string commandName;
	ControlVarType controlVarType;
	vector< ComboBoxDescription > comboBoxDescription;
	string applyCommandName;
	string enabledFromOtherVarId;

	PrefVariable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Preferences : public DbResource
{
	DBRESOURCE_METHODS( Preferences );
public:
	vector< PrefVariable > variables;
	vector< PreferencesPreset > presets;

	Preferences();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Preferences& operator = ( const Preferences &_preferences ) { Assign( _preferences ); return *this; }
	Preferences( const Preferences &_preferences ) { Assign( _preferences ); }
	virtual void Assign( const Preferences &_preferences );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Preferences * pOther = dynamic_cast< const Preferences * > ( _pResource );
		if ( pOther ) Preferences::Assign( *pOther );
	}
};

}; // namespace NDb
