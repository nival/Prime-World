#include "stdafx.h"
#include "LogFileName.h"
#include "FileSystem/FileUtils.h"
#include "FileSystem/FilePath.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_PROFILER

static const char vTuneLibraryName[] = "vtuneapi.dll";  
static bool vtInited = false;
static bool analystInited = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C"
{
  static void ( __cdecl* VTPause ) (void) = 0;
  static void ( __cdecl* VTResume ) (void) = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CodeAnalystStarter
{
  enum ProfileState
  {
    ProfilingUnavailable, /**< The profiler is not available */
    ProfilingStopped,/**< The profiler is not currently profiling */
    Profiling,		/**< The profiler is currently profiling */
    ProfilingPaused,/**< The profiler is currently paused */
    ProfilingAborted /**< The profiler encountered an error and aborted the 
                     profile*/
  };
  struct EventConfiguration
  {
    EventConfiguration ()
    {
      performanceEvent = 0;
      value = 0;
      preferredGroup = -1;
    };
    /** Performance event as created by \ref fnMakeProfileEvent*/
    unsigned __int64 performanceEvent;
    /** Sample period for sampling or starting count for counting */
    unsigned __int64 value; 
    /** Which other events this should be grouped with */
    int preferredGroup;
  }; 


  bool inited;
  bool codeAnalystPresent;
  HRESULT ( *fnEnableProfiling ) (void);
  HRESULT ( *fnReleaseProfiling ) (void);
  HRESULT ( *fnGetLastProfileError ) (uint size, wchar_t *pErrorString);

  HRESULT ( *fnStartProfiling ) (bool startPaused, ProfileState *pProfileState);
  HRESULT ( *fnStopProfiling ) (void);

  HRESULT ( *fnPauseProfiling ) (void);
  HRESULT ( *fnResumeProfiling ) (void);

  HRESULT ( *fnSetProfileOutputFile ) (wchar_t * pFileName);
  HRESULT ( *fnSetFilterProcesses ) (uint * pProcessIds, uint count);
  HRESULT ( *fnSetTimerConfiguration ) (int64 cpuCoreMask, uint *puSPeriod);
  HRESULT ( *fnSetCallStackSampling ) (uint processId, uint unwindLevel, uint samplePeriod);

  HRESULT ( *fnMakeProfileEvent) ( uint eventSelect, uint unitMask, bool edgeDetect, bool usrEvents, bool osEvents, bool guestOnlyEvents, bool hostOnlyEvents
    , bool countingEvent, unsigned __int64 *pPerformanceEvent);
  HRESULT ( *fnSetEventConfiguration) ( EventConfiguration * pPerformanceEvents, uint count, int64 mSMultiplexInterval, int64 cpuCoreMask );

  CodeAnalystStarter() : inited( false ), codeAnalystPresent( false ) {}
  ~CodeAnalystStarter() { Cleanup(); }

  void Init( enum EAMDProfilingType type )
  {
    if ( inited ) 
      return;
    inited = true;
    codeAnalystPresent = false;

    HMODULE module = LoadLibrary( "CaProfileControl.dll" );
    if ( module )
    {
      fnEnableProfiling = (HRESULT (*)(void) )GetProcAddress( module, "?fnEnableProfiling@@YAJXZ" );
      fnReleaseProfiling = (HRESULT (*)(void) )GetProcAddress( module, "?fnReleaseProfiling@@YAJXZ" );
      fnGetLastProfileError = (HRESULT (*)(uint, wchar_t *) )GetProcAddress( module, "?fnGetLastProfileError@@YAJIPAG@Z" );

      fnStartProfiling = (HRESULT (*)(bool , ProfileState *) )GetProcAddress( module, "?fnStartProfiling@@YAJ_NPAW4ProfileState@@@Z" );
      fnStopProfiling = (HRESULT (*)(void) )GetProcAddress( module, "?fnStopProfiling@@YAJXZ" );

      fnPauseProfiling = (HRESULT (*)(void) )GetProcAddress( module, "?fnPauseProfiling@@YAJXZ" );
      fnResumeProfiling = (HRESULT (*)(void) )GetProcAddress( module, "?fnResumeProfiling@@YAJXZ" );

      fnSetProfileOutputFile = (HRESULT (*)(wchar_t *) )GetProcAddress( module, "?fnSetProfileOutputFile@@YAJPAG@Z" );
      fnSetFilterProcesses = (HRESULT (*)(uint *, uint) )GetProcAddress( module, "?fnSetFilterProcesses@@YAJPAII@Z" );
      fnSetTimerConfiguration = (HRESULT (*)(__int64, uint *) )GetProcAddress( module, "?fnSetTimerConfiguration@@YAJ_KPAI@Z" );
      fnSetCallStackSampling = (HRESULT (*)(uint, uint, uint) )GetProcAddress( module, "?fnSetCallStackSampling@@YAJIII@Z" );

      fnMakeProfileEvent = (HRESULT (*)(uint, uint, bool, bool, bool, bool, bool, bool, unsigned __int64 *) )GetProcAddress( module, "?fnMakeProfileEvent@@YAJII_N00000PA_K@Z" );
      fnSetEventConfiguration = (HRESULT (*)(EventConfiguration *, uint, int64, int64) )GetProcAddress( module, "?fnSetEventConfiguration@@YAJPAUEventConfiguration@@I_K1@Z" );

      string fileName = NDebug::GenerateDebugFileName( "prof", "prd" );
      NFile::CFilePath filePath = NFile::GetFilePath( fileName );
      NFile::CreatePath( filePath );
      wstring fileNamew = NStr::ToUnicode( fileName );

      wchar_t buffer[256];

      HRESULT hr = (*fnEnableProfiling)();
      if (S_OK != hr)
      {
        (*fnGetLastProfileError) (256, buffer);
        systemLog( NLogg::LEVEL_MESSAGE ) << "fnEnableProfiling error: " << buffer << endl;
      }

      hr = (*fnSetProfileOutputFile) (&fileNamew[0]);
      if (S_OK != hr)
      {
        (*fnGetLastProfileError) (256, buffer);
        systemLog( NLogg::LEVEL_MESSAGE ) << "fnSetProfileOutputFile error: " << buffer << endl;
      }

      uint procId = ::GetCurrentProcessId();
      hr = (*fnSetFilterProcesses) (&procId, 1);
      if (S_OK != hr)
      {
        (*fnGetLastProfileError) (256, buffer);
        systemLog( NLogg::LEVEL_MESSAGE ) << "fnSetFilterProcesses error: " << buffer << endl;
      }

      // configure{
      switch( type )
      {
      case AMDPT_CALLSTACK:
        hr = SetupTimeBasedProfile( buffer, procId );
        break;
      case AMDPT_EVENTS:
        hr = SetupEventBasedProfile( buffer, procId );
        break;
      }
      // }configure 

      hr = (*fnStartProfiling) (true, NULL);
      if (S_OK != hr)
      {
        (*fnGetLastProfileError) (256, buffer);
        systemLog( NLogg::LEVEL_MESSAGE ) << "fnStartProfiling error: " << buffer << endl;
      }
      if ( SUCCEEDED( hr ) )
        codeAnalystPresent = true; 
    }
  }

  HRESULT SetupTimeBasedProfile( wchar_t * buffer, uint procId )
  {
    uint samplingPerioduS = 10;
    uint unwindLevel = 10;
    uint samplePeriod = 10;

    HRESULT hr = S_OK;
    hr = (*fnSetTimerConfiguration) ( -1, &samplingPerioduS);
    if ( SUCCEEDED( hr ) )
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnSetTimerConfiguration error: " << buffer << endl;
    }

    hr = (*fnSetCallStackSampling) (procId, unwindLevel, samplePeriod);
    if (S_OK != hr)
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnSetCallStackSampling error: " << buffer << endl;
    }
    return hr;
  }
  HRESULT SetupEventBasedProfile( wchar_t * buffer, uint procId )
  {
    vector<EventConfiguration> eventArray;
    HRESULT hr = S_OK;

    eventArray.resize( 3 );
    // Event: Retired near returns
    hr = (*fnMakeProfileEvent) (0x0C8, 0, false, true, true, false,  false, false, &(eventArray[0].performanceEvent));
    //Take a sample every 1,000 returns
    eventArray[0].value = 1000;

    //Define the second event to measure 
    hr = (*fnMakeProfileEvent) (0x076, 0, false, true, true, false,  false, false, &(eventArray[1].performanceEvent));
    //Take a sample every 1,000,000 clock cycles
    eventArray[1].value = 1000000;

    // Event: Retired far control transfers
      hr = (*fnMakeProfileEvent) (0x0C6, 0, false, true, true, false,  false, false, &(eventArray[2].performanceEvent));
      //Take a sample every 1,000 returns
    eventArray[2].value = 1000;

    if (S_OK != hr)
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnMakeProfileEvent error: " << buffer << endl;
    }

    hr = (*fnSetEventConfiguration) (eventArray.begin(), eventArray.size(), 1, -1 );
    if (S_OK != hr)
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnSetEventConfiguration error: " << buffer << endl;
    }
    return hr;
  }

  void Cleanup()
  {
    if (!inited || !codeAnalystPresent )
      return;

    codeAnalystPresent = false;

    wchar_t buffer[256];

    HRESULT hr = (*fnStopProfiling) ();
    if (S_OK != hr)
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnStopProfiling error: " << buffer << endl;
    }

    hr = (*fnReleaseProfiling) ();
    if (S_OK != hr)
    {
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnReleaseProfiling error: " << buffer << endl;
    }
  }

  void Resume()
  {
    if ( !codeAnalystPresent )
      return;
    HRESULT hr = (*fnResumeProfiling) ();
    if (S_OK != hr)
    {
      wchar_t buffer[256];
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnResumeProfiling error: " << buffer << endl;
    }
  }

  void Pause()
  {
    if ( !codeAnalystPresent )
      return;
    HRESULT hr = (*fnPauseProfiling) ();
    if (S_OK != hr)
    {
      wchar_t buffer[256];
      (*fnGetLastProfileError) (256, buffer);
      systemLog( NLogg::LEVEL_MESSAGE ) << "fnPauseProfiling error: " << buffer << endl;
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static CodeAnalystStarter codeAnalystStarter;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitAMDProfiler( EAMDProfilingType type )
{
  codeAnalystStarter.Init( type );
}

void ShutdownAMDProfiler()
{
  codeAnalystStarter.Cleanup();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VTuneResumer::VTuneResumer( /*bool autoStart*/ )
{
  //Resume();
}
VTuneResumer::~VTuneResumer()
{
  //Pause();
}
void VTuneResumer::Pause()
{
  if ( VTPause )
    (*VTPause) ();
  else 
    codeAnalystStarter.Pause();
}
void VTuneResumer::Resume()
{
  if ( !vtInited )
  {
    vtInited = true;

    HMODULE module = LoadLibrary( vTuneLibraryName );
    if ( module )
    {
      VTResume = (void ( __cdecl*)(void) )GetProcAddress( module, "_VTResume@0" );
      VTPause = (void ( __cdecl*)(void) )GetProcAddress( module, "_VTPause@0" );
    }
  }

  if ( VTResume )
    (*VTResume) ();
  else 
    codeAnalystStarter.Resume();

} 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else
void InitAMDProfiler( EAMDProfilingType type ){}
void ShutdownAMDProfiler(){}
#endif
