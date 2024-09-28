#include "stdafx.h"

#include "Dumper.h"
#include "System/InlineProfiler.h"


namespace NLogg
{

static int s_rotationPeriod = 0;

REGISTER_VAR( "log_rotation_period", s_rotationPeriod, STORAGE_GLOBAL );



const unsigned long GetLevelMask( const NLogg::ELevel eLevel )
{
  return 1 << (unsigned long)eLevel;
}


// mask of ALL logging levels starting with given eMinLevel
const unsigned long GetFromMinLevelMask( const NLogg::ELevel eMinLevel )
{
  unsigned long dwMask = 0xFFFFFFFF;
  for( unsigned long level = 1 << (eMinLevel-1); level; level >>= 1 )
    dwMask &= ~level; // clear all bits from eMinLevel>>1 down
  return dwMask;
}


int CDumper::RotationPeriod()
{
  return s_rotationPeriod;
}


void CDumper::SetRotationPeriod( int _hours )
{
  s_rotationPeriod = _hours;
}



CDumper::CDumper( CLogger *pDefaultLogger, const char *szDumperName_ ) :
dwLevelFilter(0xFFFFFFFF),
szDumperName(szDumperName_)
{
  if ( pDefaultLogger != 0 )
    pDefaultLogger->AddDumper( this );
}



void CDumper::AddLevel( const ELevel eLevel )
{
  if ( dwLevelFilter == 0xFFFFFFFF )
    dwLevelFilter = 0;
  dwLevelFilter |= GetLevelMask( eLevel );
}



void CDumper::AddMinLevel( const ELevel eLevel )
{
  if ( dwLevelFilter == 0xFFFFFFFF )
    dwLevelFilter = 0;
  dwLevelFilter |= GetFromMinLevelMask( eLevel );
}



void CDumper::RemoveLevel( const ELevel eLevel )
{
  dwLevelFilter &= ( 0xFFFFFFFF - GetLevelMask( eLevel ) );
}



void CDumper::Dump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if ( ( dwLevelFilter & GetLevelMask( entryInfo.level ) ) != 0 )
  {
    OnDump( entryInfo, headerAndText, textOnly );
  }
}

} //namespace NLogg
