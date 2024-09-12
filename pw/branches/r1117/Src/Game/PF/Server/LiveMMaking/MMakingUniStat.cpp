#include "stdafx.h"
#include "MMakingUniStat.h"
#include "MMakingLog.h"
#include "System/InlineProfiler.h"

namespace mmaking
{

struct UniStatLoger::Stat : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Stat, BaseObjectMT );

  double    minuteSum, hourSum;
  unsigned  minuteSamples, hourSamples;

  Stat() :
  minuteSum( 0 ), hourSum( 0 ),
  minuteSamples( 0 ), hourSamples( 0 )
  {}
};


UniStatLoger::UniStatLoger( const char * _logSuffix ) :
headerChangedMinute( false ), headerChangedHour( false ),
minuteEnds( -1 ), hourEnds( -1 ),
minuteIndex( 0 ), hourIndex( 0 )
{
  if ( _logSuffix )
  {
    minuteLoger = new Loger( ( string( _logSuffix ) + "_m.csv" ).c_str(), "" );
    hourLoger = new Loger( ( string( _logSuffix ) + "_h.csv" ).c_str(), "" );

    minuteLoger->EnableTimestampLogging( false );
    hourLoger->EnableTimestampLogging( false );
  }
}



void UniStatLoger::Poll( timer::Time _now )
{
  NI_PROFILE_FUNCTION;

  if ( minuteLoger )
    minuteLoger->Poll( _now );
  if( hourLoger )
    hourLoger->Poll( _now );

  if ( ( minuteEnds < 0 ) || ( _now >= minuteEnds ) )
  {
    if ( minuteEnds >= 0 )
    {
      MinuteDump( _now );
      ++minuteIndex;
    }
    minuteEnds = _now + 60.0;
  }

  if ( ( hourEnds < 0 ) || ( _now >= hourEnds ) )
  {
    if ( hourEnds >= 0 )
    {
      HourDump( _now );
      ++hourIndex;
    }
    hourEnds = _now + 3600.0;
  }
}



void UniStatLoger::AddStat( const char * _id, double _value )
{
  NI_PROFILE_FUNCTION;

  StrongMT<Stat> & slot = stats[_id];
  if ( !slot )
  {
    slot = new Stat;
    headerChangedMinute = headerChangedHour = true;
  }

  slot->minuteSum += _value;
  slot->hourSum += _value;
  slot->minuteSamples += 1;
  slot->hourSamples += 1;
}



void UniStatLoger::WriteHeader( timer::Time _now, const char * _idxFldName, Loger * _loger )
{
  if ( !_loger )
    return;

  std::string str;
  str.reserve( 512 );
  str = "SimulationTime;";
  str += _idxFldName;
  for ( TStats::const_iterator it = stats.begin(); it != stats.end(); ++it )
  {
    str += ";";
    str += it->first;
  }

  for ( TStats::const_iterator it = stats.begin(); it != stats.end(); ++it )
  {
    str += ";";
    str += it->first;
    str += "Count";
  }

  _loger->Log( ELogLevel::Normal, "%s", str.c_str() );
}



void UniStatLoger::WriteStats( timer::Time _now, unsigned _idxFld, double Stat::*sumFld, unsigned Stat::*samplesFld, Loger * _loger )
{
  if ( !_loger )
    return;

  std::string str;
  str.reserve( 512 );
  str = NI_STRFMT( "%.1f;%u", _now, _idxFld );

  for ( TStats::const_iterator it = stats.begin(); it != stats.end(); ++it )
  {
    Stat * stat = it->second;

    unsigned & samples = stat->*samplesFld;
    double & sum = stat->*sumFld;
    double avg = samples ? ( sum / samples ) : 0;

    str += NI_STRFMT( ";%d", (int)avg );
  }


  for ( TStats::const_iterator it = stats.begin(); it != stats.end(); ++it )
  {
    Stat * stat = it->second;

    unsigned & samples = stat->*samplesFld;
    double & sum = stat->*sumFld;

    str += NI_STRFMT( ";%u", samples );

    sum = 0;
    samples = 0;
  }

  _loger->Log( ELogLevel::Normal, "%s", str.c_str() );
}



void UniStatLoger::MinuteDump( timer::Time _now )
{
  if ( headerChangedMinute )
  {
    headerChangedMinute = false;
    WriteHeader( _now, "MinuteIndex", minuteLoger );
  }

  WriteStats( _now, minuteIndex, &Stat::minuteSum, &Stat::minuteSamples, minuteLoger );
}



void UniStatLoger::HourDump( timer::Time _now )
{
  if ( headerChangedHour )
  {
    headerChangedHour = false;
    WriteHeader( _now, "HourIndex", hourLoger );
  }

  WriteStats( _now, hourIndex, &Stat::hourSum, &Stat::hourSamples, hourLoger );
}

} //namespace mmaking
