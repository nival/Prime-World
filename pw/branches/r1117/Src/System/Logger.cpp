#include "stdafx.h"

#include "Logger.h"
#include "Dumper.h"
#include "System/InlineProfiler.h"


namespace NLogg
{

CLogger::CLogger( const char *_szName ) :
szName( _szName ),
headerFormat( EHeaderFormat::Default )
{
}




CLogger::~CLogger()
{
  ClearAllDumpers();
}



const bool CLogger::IsDumperPresent( const CDumper *pDumper ) const
{
  for ( TDumpers::const_iterator it = dumpers.begin(); it != dumpers.end(); ++it )
  {
    if ( *it == pDumper )
      return true;
  }

  return false;
}



void CLogger::Log( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  threading::ReadLockGuard guard( mutex );

  Notify( entryInfo, headerAndText, textOnly );

  for ( TDumpers::const_iterator it = dumpers.begin(); it != dumpers.end(); ++it )
    (*it)->Dump( entryInfo, headerAndText, textOnly );
}



const bool CLogger::AddDumper( CDumper *pDumper )
{
  threading::WriteLockGuard guard( mutex );

  if ( IsDumperPresent( pDumper ) )
    return false;

  dumpers.push_back( pDumper );
  return true;
}



const bool CLogger::RemoveDumper( CDumper *pDumper )
{
  threading::WriteLockGuard guard( mutex );

  TDumpers::iterator it = dumpers.begin();
  while ( it != dumpers.end() && *it != pDumper )
    ++it;

  if ( it == dumpers.end() )
    return false;

  dumpers.erase( it );
  return true;		
}



void CLogger::ClearAllDumpers()
{
  TDumpers copy;

  {
    threading::WriteLockGuard guard( mutex );
    copy.swap( dumpers );
  }

  copy.clear();
}



StrongMT<CDumper> CLogger::FindDumperByName( const char* szName ) const
{
  if( szName )
  {
    threading::ReadLockGuard guard( mutex );

    TDumpers::const_iterator it = dumpers.begin();
    while ( it != dumpers.end() )
    {
      if ( strcmp( (*it)->GetName(), szName ) == 0 )
        return *it;

      ++it;
    }
  
  }
  return 0;
}


void CLogger::AddNotifyCallback( INotifyCallback * filter )
{
  threading::WriteLockGuard guard( mutex );

  notifyCallbacks.insert( filter );
}



void CLogger::RemoveNotifyCallback( INotifyCallback * filter )
{
  threading::WriteLockGuard guard( mutex );

  notifyCallbacks.erase( filter );
}



void CLogger::Notify( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly ) const
{
  for ( NotifyCallbacks::const_iterator it = notifyCallbacks.begin(); it != notifyCallbacks.end(); ++it )
  {
    INotifyCallback * filter = *it;
    filter->OnLogEvent( entryInfo, headerAndText, textOnly );
  }
}

} //namespace NLogg
