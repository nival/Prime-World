// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBPreferences.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( Preferences );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ControlVarType value )
{
	switch( value )
	{
		case CONTROLVARTYPE_CHECKBOX:
			return "CheckBox";
		case CONTROLVARTYPE_COMBOBOXINTERVAL:
			return "ComboBoxInterval";
		case CONTROLVARTYPE_SLIDER:
			return "Slider";
		case CONTROLVARTYPE_DISPLAYMODECOMBOBOX:
			return "DisplayModeComboBox";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ControlVarType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ControlVarType StringToEnum_ControlVarType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ControlVarType)(NStr::ToInt( value ));
	if ( strcmp( value, "CheckBox" ) == 0 || strcmp( value, "CONTROLVARTYPE_CHECKBOX" ) == 0 )
		return CONTROLVARTYPE_CHECKBOX;
	if ( strcmp( value, "ComboBoxInterval" ) == 0 || strcmp( value, "CONTROLVARTYPE_COMBOBOXINTERVAL" ) == 0 )
		return CONTROLVARTYPE_COMBOBOXINTERVAL;
	if ( strcmp( value, "Slider" ) == 0 || strcmp( value, "CONTROLVARTYPE_SLIDER" ) == 0 )
		return CONTROLVARTYPE_SLIDER;
	if ( strcmp( value, "DisplayModeComboBox" ) == 0 || strcmp( value, "CONTROLVARTYPE_DISPLAYMODECOMBOBOX" ) == 0 )
		return CONTROLVARTYPE_DISPLAYMODECOMBOBOX;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ControlVarType", value ) );
	return CONTROLVARTYPE_CHECKBOX;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ComboBoxDescription::ComboBoxDescription() :
		value( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComboBoxDescription::operator&( IBinSaver &saver )
{
	saver.Add( 2, &value );
	saver.Add( 3, &userName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComboBoxDescription::operator&( IXmlSaver &saver )
{
	saver.Add( "value", &value );
	saver.Add( "userName", &userName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NameValue::NameValue() :
		value( -1000 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NameValue::operator&( IBinSaver &saver )
{
	saver.Add( 2, &varId );
	saver.Add( 3, &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NameValue::operator&( IXmlSaver &saver )
{
	saver.Add( "varId", &varId );
	saver.Add( "value", &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PreferencesPreset::PreferencesPreset()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PreferencesPreset::operator&( IBinSaver &saver )
{
	saver.Add( 2, &presetName );
	saver.Add( 3, &data );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PreferencesPreset::operator&( IXmlSaver &saver )
{
	saver.Add( "presetName", &presetName );
	saver.Add( "data", &data );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PrefVariable::PrefVariable() :
		controlVarType( CONTROLVARTYPE_CHECKBOX )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PrefVariable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &varId );
	saver.Add( 3, &commandName );
	saver.Add( 4, &controlVarType );
	saver.Add( 5, &comboBoxDescription );
	saver.Add( 6, &applyCommandName );
	saver.Add( 7, &enabledFromOtherVarId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PrefVariable::operator&( IXmlSaver &saver )
{
	saver.Add( "varId", &varId );
	saver.Add( "commandName", &commandName );
	saver.Add( "controlVarType", &controlVarType );
	saver.Add( "comboBoxDescription", &comboBoxDescription );
	saver.Add( "applyCommandName", &applyCommandName );
	saver.Add( "enabledFromOtherVarId", &enabledFromOtherVarId );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Preferences::Preferences()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Preferences::operator&( IBinSaver &saver )
{
	saver.Add( 2, &variables );
	saver.Add( 3, &presets );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Preferences::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Preferences* parentPtr = (Preferences*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Preferences::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "variables", &variables );
	saver.Add( "presets", &presets );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Preferences::Assign( const Preferences& _preferences )
{
	variables = _preferences.variables;
	presets = _preferences.presets;
}
}; // namespace NDb
