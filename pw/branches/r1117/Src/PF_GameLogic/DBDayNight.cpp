// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBDayNight.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EDayNightState value )
{
	switch( value )
	{
		case DAYNIGHTSTATE_DAY:
			return "Day";
		case DAYNIGHTSTATE_NIGHT:
			return "Night";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EDayNightState", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EDayNightState StringToEnum_EDayNightState( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EDayNightState)(NStr::ToInt( value ));
	if ( strcmp( value, "Day" ) == 0 || strcmp( value, "DAYNIGHTSTATE_DAY" ) == 0 )
		return DAYNIGHTSTATE_DAY;
	if ( strcmp( value, "Night" ) == 0 || strcmp( value, "DAYNIGHTSTATE_NIGHT" ) == 0 )
		return DAYNIGHTSTATE_NIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EDayNightState", value ) );
	return DAYNIGHTSTATE_DAY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DayNightSettings::DayNightSettings() :
		initialState( DAYNIGHTSTATE_DAY )
	, initialStateFraction( 0.0f )
	, transitionDuration( 0.5f )
	, transitionThreshold( 0.75f )
	, dayDuration( 600.0f )
	, nightDuration( 600.0f )
	, twilightDuration( 60.0f )
	, twilightFraction( 0.5f )
	, nightSpecularReduction( 0.4f )
	, hideDayNightWidget( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DayNightSettings::operator&( IBinSaver &saver )
{
	saver.Add( 2, &initialState );
	saver.Add( 3, &initialStateFraction );
	saver.Add( 4, &transitionDuration );
	saver.Add( 5, &transitionThreshold );
	saver.Add( 6, &dayDuration );
	saver.Add( 7, &nightDuration );
	saver.Add( 8, &twilightDuration );
	saver.Add( 9, &twilightFraction );
	saver.Add( 10, &nightSpecularReduction );
	saver.Add( 11, &hideDayNightWidget );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DayNightSettings::operator&( IXmlSaver &saver )
{
	saver.Add( "initialState", &initialState );
	saver.Add( "initialStateFraction", &initialStateFraction );
	saver.Add( "transitionDuration", &transitionDuration );
	saver.Add( "transitionThreshold", &transitionThreshold );
	saver.Add( "dayDuration", &dayDuration );
	saver.Add( "nightDuration", &nightDuration );
	saver.Add( "twilightDuration", &twilightDuration );
	saver.Add( "twilightFraction", &twilightFraction );
	saver.Add( "nightSpecularReduction", &nightSpecularReduction );
	saver.Add( "hideDayNightWidget", &hideDayNightWidget );

	return 0;
}
}; // namespace NDb
