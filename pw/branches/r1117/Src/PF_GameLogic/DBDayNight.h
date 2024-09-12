#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
enum EDayNightState
{
	DAYNIGHTSTATE_DAY = 0,
	DAYNIGHTSTATE_NIGHT = 1,
};

const char *EnumToString( const EDayNightState value );
const EDayNightState StringToEnum_EDayNightState( const char* value );

template <>
struct KnownEnum< EDayNightState >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EDayNightState value ) { return EnumToString( value ); }
	static const EDayNightState ToEnum( const char* value ) { return StringToEnum_EDayNightState( value ); }
	static const EDayNightState ToEnum( const string& value ) { return StringToEnum_EDayNightState( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct DayNightSettings
{
public:
	EDayNightState initialState;
	float initialStateFraction;
	float transitionDuration;
	float transitionThreshold;
	float dayDuration;
	float nightDuration;
	float twilightDuration;
	float twilightFraction;
	float nightSpecularReduction;
	bool hideDayNightWidget;

	DayNightSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

}; // namespace NDb
