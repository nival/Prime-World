#include "../stdafx.h"
#include "PerfMonitor.h"

namespace PerfMonitor
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static int CountSetBits( ULONG_PTR bitMask )
  {
    const int LSHIFT = sizeof(ULONG_PTR)*8 - 1;
    int bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;    

    for( int i = 0; i <= LSHIFT; ++i )
    {
      bitSetCount += ((bitMask & bitTest)?1:0);
      bitTest/=2;
    }

    return bitSetCount;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PerfThread : public threading::Thread
  {
  public:
    PerfThread( PerfMonitor* _pMonitor, int _updateInterval ) 
      : threading::Thread( 1024 )
      , pMonitor( _pMonitor )  
      , updateInterval( _updateInterval )
    {}
  protected:
    virtual unsigned Work()
    {
      FILETIME creationTime, exitTime;
      LARGE_INTEGER kernelTime, userTime;

      GetProcessTimes( GetCurrentProcess(), &creationTime, &exitTime, (FILETIME*)&kernelTime, (FILETIME*)&userTime );

      int64 startProcTime = kernelTime.QuadPart + userTime.QuadPart;
      int64 startAbsTime = GetTickCount();

      while( isRunning )
      {
        int64 absTime = startAbsTime;

        do 
        {
          Sleep( 100 );
          absTime = GetTickCount();
          if ( !isRunning )
            return 0;

        } while ( ( absTime - startAbsTime ) < updateInterval );

        GetProcessTimes( GetCurrentProcess(), &creationTime, &exitTime, (FILETIME*)&kernelTime, (FILETIME*)&userTime );
        int64 procTime = kernelTime.QuadPart + userTime.QuadPart;

        double cpuUsage = (procTime - startProcTime) / ( 10000.0 * (absTime - startAbsTime) );

        pMonitor->SetUsage( cpuUsage );

        startProcTime = procTime; startAbsTime = absTime;
      }

      return 0;
    }

    PerfMonitor* pMonitor;
    int updateInterval;
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PerfMonitor::PerfMonitor( int updateIntervalMs, const char* debugVarScreen, const char* debugVarName )
  : pThread( 0 ), pDebugVar( 0 ),coresUsage( 0.f ) 
  {
    coresCount = CountCores();

    if( debugVarScreen && debugVarName )
    {
      pDebugVar = new NDebug::DebugVar<float>( debugVarName, debugVarScreen );
    }

    pThread = new PerfThread( this, updateIntervalMs );
    pThread->Resume();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PerfMonitor::~PerfMonitor()
  {
    if( pThread )
      pThread->Stop( true );
    SAFE_DELETE( pThread );
    SAFE_DELETE( pDebugVar );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  typedef BOOL (WINAPI *LPFN_GLPI)( PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD );

  int PerfMonitor::CountCores()
  {
    LPFN_GLPI getLogicalProcessorInformation;
    getLogicalProcessorInformation = (LPFN_GLPI) GetProcAddress( GetModuleHandle( "kernel32" ), "GetLogicalProcessorInformation" );
    if ( !getLogicalProcessorInformation ) 
    {
      SYSTEM_INFO si;
      GetSystemInfo(&si);
      return si.dwNumberOfProcessors;
    }

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = 0;

    DWORD returnLength = 0;

    DWORD rc = getLogicalProcessorInformation( buffer, &returnLength );

    if ( GetLastError() == ERROR_INSUFFICIENT_BUFFER ) 
    {
      buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)(new char[returnLength]);
      rc = getLogicalProcessorInformation( buffer, &returnLength );
    } 

    NI_VERIFY( rc == TRUE, NStr::StrFmt( "GetLogicalProcessorInformation error: %d", GetLastError() ), return 1 );

    DWORD byteOffset = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* ptr = buffer;
    DWORD logicalProcessorCount = 0;
    DWORD processorCoreCount = 0;

    while ( byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength ) 
    {
      if ( ptr->Relationship == RelationProcessorCore ) 
      {
        processorCoreCount++;
        // A hyperthreaded core supplies more than one logical processor.
        logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
      }
      byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
      ++ptr;
    }
    delete[] buffer;
    return logicalProcessorCount;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PerfMonitor::SetUsage( float _coresUsage )
  {
    coresUsage = _coresUsage;
    if ( pDebugVar )
      pDebugVar->SetValue( GetCPUUsagePercent() );
  }
};
