#include "stdafx.h"

#include "DebugVar.h"
#include "meminfo.h"

#include <stdarg.h>

//#define COLLECT_PERFORMANCE_DEBUG_VAR_INHERIT
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<NDebug::IDebugVar*>& GetVars()
{
  static vector<NDebug::IDebugVar*> debugVars;
  return debugVars;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<NDebug::IDebugVar*>& GetResetOnFrameVars()
{
  static vector<NDebug::IDebugVar*> resetOnFrameVars;
  return resetOnFrameVars;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef COLLECT_PERFORMANCE_DEBUG_VAR_INHERIT
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ThreadIdent
{
  DWORD thread;
  int ident;

  ThreadIdent() : thread( 0 ), ident( 0 ) { }
  ThreadIdent( DWORD _thread ) : thread( _thread ), ident( 0 ) { }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThreadIdent* GetIdents()
{
  static bool ignore = true;
  if ( ignore )
    return 0;
  static ThreadIdent idents[64];
  static bool init = false;
  if ( !init )
  {
    for( int i = 0; i < 64; ++i )
    {
      idents[i].thread = 0;
      idents[i].ident = 0;
    }
    init = true;
  }
  return idents;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StartDebugVar( const wchar_t* name )
{
  if ( !GetIdents() ) 
    return;

  static char* identline = "                                                                                                                                                                                               ";
  const DWORD thread = GetCurrentThreadId();
  int i = 0;
  for( ; i < 64; ++i )
  {
    if ( GetIdents()[i].thread == 0 )
    {
      GetIdents()[i].thread = thread;
      break;
    }
    else if ( GetIdents()[i].thread == thread )
      break;
  }
  if ( i > 64 )
    return;
  string ident( identline, GetIdents()[i].ident );
  string name_str = NStr::ToMBCS( name );
  DebugTrace( ">>>> Thread 0x%08X:  On %s%s", thread, ident.c_str(), name_str.c_str() );
  GetIdents()[i].ident += 2;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StopDebugVar( const wchar_t* name )
{
  if ( !GetIdents() ) 
    return;

  static char* identline = "                                                                                                                                                                                               ";
  const DWORD thread = GetCurrentThreadId();
  int i = 0;
  for( ; i < 64; ++i )
  {
    if ( GetIdents()[i].thread == 0 )
    {
      GetIdents()[i].thread = thread;
      break;
    }
    else if ( GetIdents()[i].thread == thread )
      break;
  }
  if ( i > 64 )
    return;
  GetIdents()[i].ident -= 2;
  if ( GetIdents()[i].ident < 0 )
    GetIdents()[i].ident = 0;
  string ident( identline, GetIdents()[i].ident );
  string name_str = NStr::ToMBCS( name );
  DebugTrace( ">>>> Thread 0x%08X: Off %s%s", thread, ident.c_str(), name_str.c_str() );
}
#endif // #ifdef COLLECT_PERFORMANCE_DEBUG_VAR_INHERIT

} //namespace


namespace NDebug
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterDebugVar( IDebugVar* pDebugVar )
{
  for( vector<NDebug::IDebugVar*>::const_iterator it = GetVars().begin(); it != GetVars().end(); ++it )
  {
    if ( !(*it) )
      continue;
    // some variables from netwrok defined in static library and register many times when loading from different dlls
    //NI_VERIFY( NStr::WCmp( (*it)->GetName(), pDebugVar->GetName() ) != 0, NI_STRFMT( "DebugVar with name %s already registreed", NStr::ToMBCS( pDebugVar->GetName() ).c_str() ), break );
  }

  GetVars().push_back( pDebugVar );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnregisterDebugVar( IDebugVar* pDebugVar )
{
  for( int index = 0 ; index < GetResetOnFrameVars().size(); ++index )
	{
    if ( (IDebugVar*)GetResetOnFrameVars()[index] == pDebugVar )
    {
      GetResetOnFrameVars()[index] = 0;
    }
	}

	for( int index = 0 ; index < GetVars().size(); ++index )
	{
    if ( GetVars()[index] == pDebugVar )
    {
      GetVars()[index] = 0;
      return;
    }
	}

  NI_ALWAYS_ASSERT( "Trying to unregister non-registered debug var" );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Formatters
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void FormatString<char>( char* buffer, const int bufferSize, const char* format, va_list va )
{
	NStr::VPrintf( buffer, bufferSize, format, va);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void FormatString<wchar_t>( wchar_t* buffer, const int bufferSize, const wchar_t* format, va_list va )
{
  NStr::WVPrintf( buffer, bufferSize, format, va);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseDebugVar::BaseDebugVar( const char * _name, bool resetOnFrame  )
{
  NStr::ToWString( _name, name, 64 );

  RegisterDebugVar( this );

  if ( resetOnFrame )
    GetResetOnFrameVars().push_back( this );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseDebugVar::~BaseDebugVar()
{
  UnregisterDebugVar( this );
}



void BaseDebugVar::AddChangeWatcher( IDebugVarWatcher * _watcher )
{
  changeWatchers.push_back( _watcher );
}



void BaseDebugVar::RemoveChangeWatcher( IDebugVarWatcher * _watcher )
{
  for ( TWatchers::iterator it = changeWatchers.begin(); it != changeWatchers.end(); )
    if ( *it == _watcher )
      it = changeWatchers.erase( it );
    else
      ++it;
}



void BaseDebugVar::NotifyAboutChange()
{
  for ( TWatchers::iterator it = changeWatchers.begin(); it != changeWatchers.end(); )
    if ( *it )
    {
      (*it)->OnDebugVarEvent( this );
      ++it;
    }
    else
      it = changeWatchers.erase( it );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StringDebugVar<class TChar, int length>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StringDebugVar::SetValue( const char* format, ... )
{
	char charBuffer[BUFFER_LENGTH];

	va_list va;
	va_start( va, format );
	NStr::VPrintf( charBuffer, BUFFER_LENGTH, format, va);
	va_end( va );

	NStr::ToWString<char const *>( charBuffer, buffer, BUFFER_LENGTH );

  NotifyAboutChange();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StringDebugVar::SetValue( const wchar_t* format, ... )
{
	va_list va;
	va_start( va, format );
	NStr::WVPrintf(buffer, BUFFER_LENGTH, format, va);
	va_end( va ); 

  NotifyAboutChange();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PerformanceDebugVar<maxMallocs, maxMSecs, resetOnFrame>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerformanceDebugVar::Start()
{
  // pass enable-flag into logging system
  mallocsStart = ::GetMallocsTotal();
	NHPTimer::GetTime( msecsStart );

#ifdef COLLECT_PERFORMANCE_DEBUG_VAR_INHERIT
  StartDebugVar( GetName() );
#endif

  if ( trackMallocs )
  {
    NI_VERIFY( !trackMallocsStarted, NI_STRFMT( "Malloc tracking for debug variable \"%s\" started twice", NStr::ToMBCS( GetName() ).c_str() ), return );
    trackMallocsStarted = true;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerformanceDebugVar::Stop()
{
  if ( trackMallocsStarted )
  {
    trackMallocs = false;
    trackMallocsStarted = false;
  }

  double deltaTime = NHPTimer::GetTimePassedAndUpdateTime( msecsStart ) * 1000.0;
  int deltaMallocs = ::GetMallocsTotal() - mallocsStart;

  mallocs += deltaMallocs;
	msecs += deltaTime;

  if ( !isResetOnFrame )
  {
    timeplotter.AddValue( deltaTime );
    mallocplotter.AddValue( deltaMallocs );
  }

#ifdef COLLECT_PERFORMANCE_DEBUG_VAR_INHERIT
  StopDebugVar( GetName() );
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerformanceDebugVar::Reset( float )
{
  Reset();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PerformanceDebugVar::Reset()
{
  mallocsAvg.SetValue( mallocs );
  msecsAvg.SetValue( msecs );

  timeplotter.AddValue( msecs );
  mallocplotter.AddValue( mallocs );

  mallocs = 0;
  msecs = 0;

  mallocsStart = 0;
  msecsStart = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PerformanceDebugVar::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"MS: %.2f (%.2f/%.2f); MEM: %d (%d/%d)", msecs, msecsAvg.GetAvg(), msecsAvg.GetMax(), mallocs, mallocsAvg.GetAvg(), mallocsAvg.GetMax() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PerformanceGuard::PerformanceGuard( const double _limit, const NLogg::ELevel _level, const char* _message ) : limit( _limit ), level( _level ), message( _message )
{
	NHPTimer::GetTime( start );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PerformanceGuard::~PerformanceGuard()
{
  const double time = NHPTimer::GetTimePassedAndUpdateTime( start ) * 1000.0;
  if ( time > limit )
  {
    systemLog( level ) << message << " Exceed timeout (" << time << "ms/" << limit << "ms)" << endl;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AveragePerSecondDebugVar<int>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%d min, %d avg, %d max per second, %d total", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax(), GetTotal() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AveragePerSecondDebugVar<float>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%.2f min, %.2f avg, %.2f max per second, %.2f total", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax(), GetTotal() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AveragePerSecondDebugVar2<int>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%d min, %d avg, %d max per second, %d total", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax(), GetTotal() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AveragePerSecondDebugVar2<float>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%.2f min, %.2f avg, %.2f max per second, %.2f total", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax(), GetTotal() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AverageDebugVar<int>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%d min, %d avg, %d max", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AverageDebugVar<unsigned int>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%u min, %u avg, %u max", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int AverageDebugVar<float>::FormatValue( wchar_t *pBuffer, const int bufferLen ) const
{
  return NStr::SWPrintf( pBuffer, bufferLen, L"%.2f min, %.2f avg, %.2f max", averageCalc.GetMin(), averageCalc.GetAvg(), averageCalc.GetMax() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResetDebugVarsOnFrame( float deltaTime )
{
	for( vector<IDebugVar*>::iterator it = GetResetOnFrameVars().begin(); it != GetResetOnFrameVars().end(); ++it )
		(*it)->Reset( deltaTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProcessAllDebugVars( TProcessEveryDebugVarsFunc func, void* pData )
{
  for( vector<IDebugVar*>::const_iterator it = GetVars().begin(); it != GetVars().end(); ++it )
  {
    if ( (*it) )
			func( 0, (*it)->GetName(), *it, pData );
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void ProcessAllEditorDebugVars( TProcessEveryEditorDebugVarsFunc func )
//{
//  for( vector<IDebugVar*>::const_iterator it = GetVars().begin(); it != GetVars().end(); ++it )
//  {
//    if ( (*it) )
//    {
//      static wchar_t buffer[128];
//      const int length = (*it)->FormatValue( buffer, sizeof( buffer ) / sizeof( wchar_t ) );
//      func( L"", (*it)->GetName(), buffer, length, (*it)->IsWarning() );
//    }
//  }
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IDebugVar* FindDebugVar( const wchar_t* name )
{
  for( vector<IDebugVar*>::const_iterator it = GetVars().begin(); it != GetVars().end(); ++it )
  {
    if ( (*it) )
    {
      if ( NStr::WCmp( name, (*it)->GetName() ) == 0 )
        return *it;
    }
  }

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<IDebugVar*> FindDebugVars( const wchar_t* mask )
{
  vector<IDebugVar*> result;
  int len = wcslen(mask);
  if ( len <= 0 || mask[len-1] != L'*' )
  {
    // not a wildcard
    IDebugVar *var = FindDebugVar( mask );
    if ( var )
      result.push_back( var );
    return result;
  }

  len -= 1;  // cut "*"

  for( vector<IDebugVar*>::const_iterator it = GetVars().begin(); it != GetVars().end(); ++it )
  {
    if ( (*it) )
    {
      if ( NStr::WNCmp( mask, (*it)->GetName(), len ) == 0 )
        result.push_back( *it );
    }
  }

  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GetDebugVarValue( const wchar_t* name, wstring* pResult )
{
	pResult->clear();

  IDebugVar* pVar = FindDebugVar( name );
  if ( !pVar )
    return;

  static wchar_t buffer[128];
  pVar->FormatValue( buffer, sizeof(buffer) / sizeof(wchar_t) );
  *pResult = wstring( buffer );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDebug

