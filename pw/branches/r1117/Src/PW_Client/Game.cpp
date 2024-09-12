#include "stdafx.h"

#pragma warning (disable : 4996)
#include "System/StrProc.h"
#include "System/SyncProcessorState.h"
#include "System/HPTimer.h"
#include "System/MainFrame.h"
#include "System/ProfileManager.h"
#include "Client/MainLoop.h"
#include "Client/MainTimer.h"
#include "Client/VSyncController.h"
#include "Client/ScreenCommands.h"
#include "System/MainFrame.h"
#include "System/FileSystem/FilePath.h"
#include "System/StackWalk.h"
#include "System/FileStreamDumper.h"
#include "System/AssertDumper.h"
#include "System/EventDumper.h"
#include "System/DebugTraceDumper.h"
#include "System/EditBoxDumper.h"
#include "System/CrashRptWrapper.h"
#include "system/BSUtil.h" //TODO: Remove this header (NUM_TASK)
#include "system/expreport.h"
#include "System/meminfo.h"
#include "Render/renderer.h"
#include "System/TextFileDumper.h"
#include "System/ConfigFiles.h"
#include "System/AppInstancesLimit.h"
#include "System/FileSystem/FileExtensionStatisticsMonitor.h"
#include "System/FileSystem/FileActivitySimpleMonitor.h"
#include "System/CmdLineLite.h"
#include "System/InlineProfiler.h"
#include "System/InlineProfiler3/Profiler3UI.h"
#include "System/InlineProfiler3/InlineProfiler3Control.h"
#include "System/PersistEvents.h"
#include "System/FileSystem/TinyFileWriteStream.h"

#include "Core/CoreFSM.h"
#include "Core/Transceiver.h"

#include "System/FileSystem/WinFileSystem.h"
#include "System/FileSystem/PileFileSystem.h"
#include "System/Stream.h"
#include "System/SyncProcessorState.h"
#include "Render/smartrenderer.h"
#include "Render/NullRenderSignal.h"

#include "Render/ParticleFX.h"

#include "PF_GameLogic/PFRenderInterface.h"

#include "UI/Root.h"
#include "UI/DebugVarsRender.h"
#include "UI/FrameTimeRender.h"
#include "UI/Resolution.h"
#include "UI/Scripts.h"

#include "Sound/SoundScene.h"
#include "Sound/EventScene.h"
#include "PF_GameLogic/DBSound.h"

#include "System/LogFileName.h"
#include "ApplicationResources.h"
#include "Version.h"
#include "commctrl.h"

#include "PF_GameLogic/PFGameLogicLog.h"

#include "PF_Core/ForceLink.h"
#include "PF_Minigames/ForceLink.h"

#include "TypesHash.h"
#include "PF_TypesHash.h"

#include "GameContext.h"
#include "LocalGameContext.h"
#include "System/Events.h"
#include "System/EventFileLogger.h"
#include "System/IniFiles.h"
#include "Tools/Censor/CensorDll.h"
#include "NivalInput/Binds.h"
#include "NivalInput/SystemInputEvents.h"

#include "CpuTopology.h"
#include "../System/SimpleSignalST.h"
#include "../System/HPTimer.h"
#include "../Client/MainTimer.h"

#include <Tlhelp32.h>
#include "System/StdOutDumper.h"
#include "LobbyConnection.h"

#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "GameStatistics.h"

#include "PF_GameLogic/SocialConnection.h"
#include "PF_GameLogic/SocialBootstrap.h"
#include "PF_GameLogic/TutorialSplash.h"
#include "PF_GameLogic/GuildEmblem.h"
#include "PF_GameLogic/DBSessionMessages.h"

#include "steam/steam_api.h"
#include "steam/isteamuserstats.h"
#include "steam/isteamremotestorage.h"
#include "steam/isteammatchmaking.h"
#include "steam/steam_gameserver.h"

#include "RegistryToolbox.h"

static int    g_VideoFPS = 10;
static float  g_RecordingTime = 10.0f;
static bool   g_DebugDumpInfo = false;
static bool   g_NullRenderNoLogBox = false;
static bool   g_boostPriority = false;
static int    g_preferredProcessor = 0;
static int    g_inactiveSleep = -1;
static bool   s_localGame = false;
static bool   s_skipFrames = false;
static int    s_skipFramesBarrier = 25;
static int    s_NullRender = false;
static bool   s_bSteamInited = false;
static bool   s_bRegisterReplayExtention = true;


REGISTER_VAR( "debug_dump_info", g_DebugDumpInfo, STORAGE_GLOBAL );
REGISTER_VAR( "boost_main_thread_priority", g_boostPriority, STORAGE_NONE );
REGISTER_VAR( "boost_mtp_processor_number", g_preferredProcessor, STORAGE_NONE );
REGISTER_VAR( "inactive_sleep", g_inactiveSleep, STORAGE_NONE );
REGISTER_DEV_VAR( "video_FPS", g_VideoFPS, STORAGE_NONE);
REGISTER_DEV_VAR( "video_recording_time", g_RecordingTime, STORAGE_NONE);
REGISTER_DEV_VAR( "nullrender", s_NullRender, STORAGE_NONE);
REGISTER_DEV_VAR( "nullrender_no_log_box", g_NullRenderNoLogBox, STORAGE_NONE);
REGISTER_DEV_VAR( "local_game", s_localGame, STORAGE_NONE);
REGISTER_DEV_VAR( "skipFramesEnable", s_skipFrames, STORAGE_NONE);
REGISTER_DEV_VAR( "skipFramesBarrier", s_skipFramesBarrier, STORAGE_NONE);

static int g_deleteLogFilesAfterDays = 30;
REGISTER_VAR( "delete_log_files_after_days", g_deleteLogFilesAfterDays, STORAGE_GLOBAL );

REGISTER_VAR( "register_replay_extention", s_bRegisterReplayExtention, STORAGE_USER );
static string g_CensorFolder = "..\\Censor";
REGISTER_VAR( "censor_folder", g_CensorFolder, STORAGE_GLOBAL );

static string g_language = "ru-RU";
REGISTER_VAR( "language", g_language, STORAGE_PLAYER);

static NDebug::PerformanceDebugVar mainPerf( "01_Total", "MainPerf", 10000, 150.0, false, 80 );
static NDebug::PerformanceDebugVar mainPerf_ContextStep( "03_Context", "MainPerf", 10000, 30.0, true, 80 );
static NDebug::PerformanceDebugVar mainPerf_Step( "04_Step", "MainPerf", 10000, 30.0, true, 80 );
static NDebug::PerformanceDebugVar mainPerf_Present( "05_Present", "MainPerf", 10000, 20.0, false, 80 );
static NDebug::PerformanceDebugVar mainPerf_Render( "06_Render", "MainPerf", 10000, 30.0, true, 80 );

static NDebug::DebugVar<int> heapAllocs( "HeapAllocs", "", true );
static NDebug::DebugVar<int> heapAllocsSize( "HeapAllocsSize", "", true );
static NDebug::DebugVar<int> unfreeHeapAllocs( "UnfreeHeapAllocs", "", true );

static NDebug::DebugVar<int> virtualAllocs( "VirtualAllocs", "", true );
static NDebug::DebugVar<int> virtualAllocsSize( "VirtualAllocsSize", "", true );
static NDebug::DebugVar<int> unfreeVirtualAllocs( "UnfreeVirtualAllocs", "", true );

static NDebug::DebugVar<int> totalAllocsSize( "TotalAllocsSize", "", true );


//CRAP
extern "C" INTERMODULE_EXPORT void TooSmartLinker();


namespace
{
void ShowLocalizedErrorMB(LPCWSTR pszName, LPCWSTR pszDefault)
{
  // get the current language from the 'lang.cfg' file
  nstl::wstring lang = L"ru-RU";
  if (!NGlobal::GetVar("language").GetString().empty())
  {
    lang = NGlobal::GetVar("language").GetString() + L"/";
  }
  nstl::string filepath(NFile::Combine(NFile::GetBaseDir(), "Data/Localization/" + NStr::ToMBCS(lang)));
  
  wstring message = NIniFiles::GetINIString( NStr::ToUnicode(filepath).c_str(), L"pw_game_lang.ini", L"ErrMsgs", pszName );
  wstring title = NIniFiles::GetINIString( NStr::ToUnicode(filepath).c_str(), L"pw_game_lang.ini", L"ErrMsgs", L"ErrorTile" );
  if (message.empty()) message = pszDefault ? pszDefault : L"Unexpected error.";
  if (title.empty()) title = L"Error";
  MessageBoxW( 0, message.c_str(), title.c_str(), MB_OK | MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST );
}

} // namespace


static NDebug::PerformanceDebugVar* FindPerfVar( const wchar_t* screen, const wchar_t* name )
{
  NDebug::IDebugVar* pFrameTime = NDebug::FindDebugVar( name );
  if( !pFrameTime )
    return 0;

  return static_cast<NDebug::PerformanceDebugVar*>( pFrameTime );
}



void DumpLoadedModules() 
{ 
  CObj<FileWriteStream> pFile;
  string logFileName = NDebug::GenerateDebugFileName( "modules", "dmp" );
  pFile = new FileWriteStream( logFileName, FILEACCESS_WRITE, FILEOPEN_OPEN_ALWAYS );

  DWORD dwPID = GetCurrentProcessId();
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE; 
  MODULEENTRY32 me32; 

  //  Take a snapshot of all modules in the specified process. 
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID ); 
  if( hModuleSnap == INVALID_HANDLE_VALUE ) 
  { 
    //printError( "CreateToolhelp32Snapshot (of modules)" ); 
    return; 
  } 

  //  Set the size of the structure before using it. 
  me32.dwSize = sizeof( MODULEENTRY32 ); 

  //  Retrieve information about the first module, 
  //  and exit if unsuccessful 
  if( !Module32First( hModuleSnap, &me32 ) ) 
  { 
    //printError( "Module32First" );  // Show cause of failure 
    CloseHandle( hModuleSnap );     // Must clean up the snapshot object! 
    return; 
  } 

  //  Now walk the module list of the process, 
  //  and display information about each module 
  do 
  { 
    /*DebugTrace( NStr::StrFmt( "\n\n     MODULE NAME:     %s",             me32.szModule ) ); 
    DebugTrace( NStr::StrFmt( "\n     executable     = %s",             me32.szExePath ) ); 
    DebugTrace( NStr::StrFmt( "\n     process ID     = 0x%08X",         me32.th32ProcessID ) ); 
    DebugTrace( NStr::StrFmt( "\n     ref count (g)  =     0x%04X",     me32.GlblcntUsage ) ); 
    DebugTrace( NStr::StrFmt( "\n     ref count (p)  =     0x%04X",     me32.ProccntUsage ) ); 
    DebugTrace( NStr::StrFmt( "\n     base address   = 0x%08X", (DWORD) me32.modBaseAddr ) ); 
    DebugTrace( NStr::StrFmt( "\n     base size      = %d",             me32.modBaseSize ) ); */

    const char* line = NStr::StrFmt( "%08X,%08X,%s\x0D\x0A", (DWORD)me32.modBaseAddr, me32.modBaseSize, me32.szExePath );
    pFile->WriteString( line );

  } while( Module32Next( hModuleSnap, &me32 ) ); 

  //  Do not forget to clean up the snapshot object. 
  CloseHandle( hModuleSnap ); 
}



//#define DUMP_ALLOCS_FOR_MEMORY_MONITOR // uncomment this define to dump all allocations for memory monitor application

bool CheckHardwareCompatibility()
{
  bool supportSM30 = Render::GetRenderer()->GetCaps().bSupportSM30;
  bool hasEnoughMemory = true;

  MEMORYSTATUSEX globMemStatus;
  ZeroMemory( &globMemStatus, sizeof( globMemStatus ) );
  globMemStatus.dwLength = sizeof( globMemStatus );

  NDb::Ptr<NDb::SessionMessages> sessionMessages = NDb::SessionRoot::GetRoot()->sessionMessages;
  NI_DATA_ASSERT(sessionMessages, "Session.ROOT.sessionMessages is empty!");

  {
    const NDb::DXErrorMessages* const dxMessages = &sessionMessages->dxErrorMessages;
    Render::SetErrorMessage( 0, dxMessages->title.GetText() );
    Render::SetErrorMessage( D3DERR_INVALIDCALL, dxMessages->errorMessage.GetText() );
    Render::SetErrorMessage( E_OUTOFMEMORY, dxMessages->lowMemoryMessage.GetText() );
    Render::SetErrorMessage( D3DERR_OUTOFVIDEOMEMORY, dxMessages->lowVidMemMessage.GetText() );
  }

  const NDb::ClientHardwareErrorMessages* const heMessages = &sessionMessages->clientHardwareErrorMessages;

  if ( GlobalMemoryStatusEx( &globMemStatus ) )
    hasEnoughMemory = ( ( globMemStatus.ullTotalPhys / 1024ul )  > 900000 ); // да-да смешное число

  if ( !supportSM30 || !hasEnoughMemory )
  {
    nstl::wstring errorMessage = heMessages->errorMessage.GetText();
    if ( !supportSM30 )
    {
      errorMessage += L"\n\n";
      errorMessage += heMessages->shader3compatibilityError.GetText();
    }
    if ( !hasEnoughMemory )
    {
      errorMessage += L"\n\n";
      errorMessage += heMessages->lowMemoryError.GetText();
    }

    MessageBoxW( 0, errorMessage.c_str(), L"Error", MB_OK | MB_ICONWARNING );

    return false;
  }

  return true;
}



struct SPluginSettings
{
  int   width;
  int   height;
  bool  fullscreen;
  const char * sessionLogin;
  const char* serverName;
  const char* uid;
  const char* serverKey;
  const char* serverSecret;

  SPluginSettings() : width( 0 ), height( 0 ), fullscreen( false ), sessionLogin( 0 ), serverName(0), uid(0), serverKey(0), serverSecret(0) {}
};



class AltTabChecker
{
  bool isActive;

public:
  AltTabChecker( bool isActive ) : isActive( isActive ) {}
  void Update()
  {
    const bool appFocused = NMainFrame::IsAppNotMinimized() && NMainFrame::IsAppActive(); //NMainFrame::IsCursorInsideWndClientRect()
    if ( isActive && !appFocused )
    {
      DebugTrace("AltTabChecker: lost focus");
      isActive = appFocused;
    }
    else if ( !isActive && appFocused )
    {
      DebugTrace("AltTabChecker: acquire focus");
      isActive = appFocused;
      NMainFrame::SetActualClipCursorRect();
    }
  }
  bool IsActive() const
  {
    return isActive;
  }
};


class IRenderableScene;

typedef SimpleSignalST<bool, ::IRenderableScene> SceneSkipFrameSignal;

static bool SkipFrameIfNeeded(int _numCommands)
{
  static bool lastFrameSkipped = false;

  if(!s_skipFrames)
    return false;

  static NHPTimer::STime lastTime = 0;

  NHPTimer::STime currTime = NMainLoop::GetHPTime();

  bool skipFrame = !lastFrameSkipped &&
    (_numCommands > s_skipFramesBarrier && NHPTimer::Time2Seconds(currTime - lastTime) < 0.2);
  if(!skipFrame)
    lastTime = currTime;

  SceneSkipFrameSignal::Signal(skipFrame);
  lastFrameSkipped = skipFrame;
  return skipFrame;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, size_t N>
class MovingAverage
{
public:
  MovingAverage()
  {
    curIndex = 0; 

    for( size_t i = 0; i < ARRAY_SIZE(arr); ++i )
      arr[i] = T();
  }

  T NextValue( T val, T maxVal )
  {
    arr[curIndex] = val;

    T totalSum = T();     
    size_t itemsProcessed = 0;
    size_t i = curIndex;

    do
    { 
      totalSum += arr[i];   

      if( i != 0 )
        --i;
      else
        i = ARRAY_SIZE(arr) - 1;

      ++itemsProcessed;
    } 
    while( i != curIndex && totalSum < maxVal );


    if( curIndex != ARRAY_SIZE(arr) - 1 )
      ++curIndex;
    else
      curIndex = 0;

    NI_ASSERT( itemsProcessed <= ARRAY_SIZE(arr), "" );
    return totalSum / itemsProcessed;   
  }


private:
  size_t curIndex;
  T arr[N];
};

//В интервале времени 0.2(9) секунды всегда
//помещаются ровно 2 такта логики
static float g_maxMovingAvgTime = 0.2999999f;

REGISTER_DEV_VAR( "max_smooth_time", g_maxMovingAvgTime, STORAGE_NONE);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static _invalid_parameter_handler g_oldInvalidParamHandler;

void DebugTraceInvalidParamsHandler(const wchar_t* expression,
                                    const wchar_t* function, 
                                    const wchar_t* file, 
                                    unsigned int line, 
                                    uintptr_t pReserved)
{
  DebugTrace( "Invalid parameter detected in function %s."
    " File: %s Line: %d\n", NStr::ToMBCS(function).c_str(), NStr::ToMBCS(file).c_str(), line );

  DebugTrace( "Expression: %s\n", NStr::ToMBCS(expression).c_str() );

  //Произошла фатальная ошибка. Продолжать работу нельзя. 
  //Отдаём управления стандартному обработчику, который закроет программу.
  (*g_oldInvalidParamHandler)( expression, function, file, line, pReserved );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool StartRemoteDebugger()
{
  LPTSTR Command = 
    "%SystemDrive%\\Program Files\\Microsoft Visual Studio 9.0\\Common7\\IDE\\Remote Debugger\\x86\\msvsmon.exe"
    " /noauth /nosecuritywarn /nofirewallwarn /nowowwarn /anyuser /timeout 10000000";
  const LPCTSTR CurrentDirectory = NULL;

  TCHAR ExpCommand[MAX_PATH];

  ExpandEnvironmentStrings( Command, ExpCommand, ARRAY_SIZE(ExpCommand) );

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

  // Start the child process. 
  if( !CreateProcess( NULL, // No module name (use command line). 
    ExpCommand,          // Command line. 
    NULL,             // Process handle not inheritable. 
    NULL,             // Thread handle not inheritable. 
    FALSE,            // Set handle inheritance to FALSE. 
    0,                // No creation flags. 
    NULL,             // Use parent's environment block. 
    CurrentDirectory, // Starting directory. 
    &si,              // Pointer to STARTUPINFO structure.
    &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
  {
    systemLog( NLogg::LEVEL_ASSERT ) <<
      "Error on executing command '" << ExpCommand <<
      "' with starting dir '" << (CurrentDirectory == NULL ? "NULL" : CurrentDirectory) << 
      "': " <<  GetLastError(); 

    return false;    
  }

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RaiseMainThreadPriority()
{ // given our process is allowed to run at multiple cores,
  // pin the main thread to preferred one and raise thread priority
  const DWORD numberOfAvailableCores = CpuTopology().NumberOfProcessCores();
  if(g_boostPriority && numberOfAvailableCores > 1)
  {
    const DWORD desiredCore = g_preferredProcessor >= 0 ? g_preferredProcessor
      : numberOfAvailableCores + g_preferredProcessor;
    const DWORD desiredCoreMask = CpuTopology().CoreAffinityMask(desiredCore);
    DWORD idx;
    if( _BitScanForward(&idx, desiredCoreMask) )
    {
      SetThreadIdealProcessor(GetCurrentThread(), idx);
      //SetThreadAffinityMask(GetCurrentThread(), 1 << idx);
      int oldPriority = GetThreadPriority( GetCurrentThread() );
      if(THREAD_PRIORITY_NORMAL == oldPriority)
        SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static StrongMT<Game::IGameContext> context;
static bool timerUpdated = false;

void StepContext()
{
  if(!timerUpdated)
    NMainLoop::UpdateTime();

  if( !NMainFrame::IsExit() )
  {
    NI_PROFILE_BLOCK( "Context" );
    mainPerf_ContextStep.Start();
    context->Poll( NMainLoop::GetTimeDelta() );
    mainPerf_ContextStep.Stop();
  }
  timerUpdated = false;
}

struct GameFileReadContext : public FileReadCallbackContext
{
//  OBJECT_BASIC_METHODS( GameFileReadContext );
public:
  GameFileReadContext( ICastle* castleLink ) : FileReadCallbackContext(), pCastleLink(castleLink) {}
  Weak<ICastle> pCastleLink;
};


void OnPileFileReadError(FileReadResultCode code, FileReadCallbackContext* pContext)
{
  switch (code)
  {
  case FR_READ_ERROR:
  case FR_CRC_FAIL:
    {
      CObj<TinyFileWriteStream> repairFile = new TinyFileWriteStream( NFile::GetBaseDir() + "..\\.force_repair" );
      repairFile->Flush();

      HWND hWnd = (HWND)NMainFrame::GetWnd();
      if( hWnd != 0 )
        ShowWindow(hWnd, SW_MINIMIZE);

      ShowLocalizedErrorMB( L"GameDataCorrupted",
        L"Game Data has been corrupted.\nTo fix the problem please restart the launcher." );

      GameFileReadContext* pGameContext = dynamic_cast<GameFileReadContext*>(pContext);
      if (pGameContext && pGameContext->pCastleLink)
        pGameContext->pCastleLink->QuitGame();

      if ( persistentEvents::GetSingleton() )
        persistentEvents::GetSingleton()->Close();

      NSoundScene::TryTurnOffSound();

      //inputSystemMesages = 0;
      //input = 0;

      context = 0;

      NCore::ReleaseGlobalGameFSM();

      UI::Release();
      UI::ReleaseUIScript();

      //renderingInterface.Stop();

      NDb::SessionRoot::InitRoot( 0 );
      debugDisplay::Cleanup();
      profiler3ui::Shutdown();
#ifndef _SHIPPING
      DumpLoadedModules();
#endif //_SHIPPING

      // Shutdown the SteamAPI
      if (s_bSteamInited)
        SteamAPI_Shutdown();
      // Тк мы можем закараптиться на любой стадии, то у нас будет не правильная инициализация
      // И правильно деинициализироваться мы не сможем
      // Сейчас падает в exit(0) на деинициализации статиков где-то во флэше
      // Поэтому показываем Message Box про закарапченные данные, а потом делаем TerminateProcess
      // NUM_TASK
      TerminateProcess( GetCurrentProcess(), 0 );
      //exit(0);
      break;
    }
    
  }
}

struct MainVars
{
  bool initSound;
  bool initInput;
  bool initContext;
  bool initGameFSM;
  bool initUI;
  bool initRender;
  bool initDB;
  bool initDisplay;
  bool initProfiler;

  bool useCrashRptHandler;

  CObj<Input::Binds> input;
  CObj<Input::SystemEvents> inputSystemMesages;

  Render::DeviceLostWrapper<PF_Render::Interface>* renderingInterface;
  StrongMT<NLogg::EditBoxDumper> logBox;

  MainVars()
  {
    initSound = false; 
    initInput = false; 
    initContext = false; 
    initGameFSM = false; 
    initUI = false; 
    initRender = false; 
    initDB = false; 
    initDisplay = false; 
    initProfiler = false;
    useCrashRptHandler = false;

    input = 0;
    inputSystemMesages = 0;
    renderingInterface = 0;
  }

  void DeInit()
  {
    if ( initSound )
	    NSoundScene::TryTurnOffSound();

    if ( initInput )
    {
      inputSystemMesages = 0;
      input = 0;
    }

    if ( initContext )
      context = 0;

    if ( initGameFSM )
      NCore::ReleaseGlobalGameFSM();

    if ( initUI )
    {
      UI::Release();
      UI::ReleaseUIScript();
    }

    if ( initRender && renderingInterface )
    {
      renderingInterface->Stop();
      delete renderingInterface;
    }

    if ( initDB )
      NDb::SessionRoot::InitRoot( 0 );

    if ( initDisplay )
      debugDisplay::Cleanup();

    if ( initProfiler )
      profiler3ui::Shutdown();

    if ( logBox )
    {
      GetSystemLog().RemoveDumper( logBox );
      logBox = 0;
    }

    GetSystemLog().ClearAllDumpers();

    if ( useCrashRptHandler )
      CrashRptWrapper::UninstallFromProcess();

    // Shutdown the SteamAPI
    if (s_bSteamInited)
      SteamAPI_Shutdown();
  }
};

void LoadCensorDict( string filename, bool isWhiteList = false )
{
  string resPath = NFile::Combine(NFile::GetBaseDir(), g_CensorFolder);
  resPath = NFile::Combine(resPath, "Dicts");
  CensorFilter::LoadDictionary( NStr::ToUnicode(NFile::Combine(resPath, filename)).c_str(), isWhiteList );
}

void InitCensorDicts()
{
  LoadCensorDict("custom.txt");
  LoadCensorDict("custom_whitelist.txt", true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int __stdcall PseudoWinMain( HINSTANCE hInstance, HWND hWnd, LPTSTR lpCmdLine, SPluginSettings * pluginSett )
{
  MainVars mainVars;

  g_oldInvalidParamHandler = _set_invalid_parameter_handler( DebugTraceInvalidParamsHandler );

  Compatibility::Init();

  CmdLineLite::Instance().Init( lpCmdLine );

  bool isSpectator = CmdLineLite::Instance().IsKeyDefined( "spectator" );
  bool isTutorial = CmdLineLite::Instance().IsKeyDefined( "--launchTutorial" );

  if (CmdLineLite::Instance().IsKeyDefined( EXIT_CODE_QUIT_CASTLE ))
    NMainFrame::SetExitCode( EXIT_CODE_QUIT_CASTLE );

  // Check if we deal with a replay
  bool isReplay = false;
  string replayFileName;
  if ( CmdLineLite::Instance().ArgsCount() > 1 )
  {
    replayFileName = CmdLineLite::Instance().Argument(1);
    if(!replayFileName.empty() && replayFileName.find('.') != string::npos && NFile::DoesFileExist(replayFileName))
    {
      isSpectator = true;
      isReplay = true;

      if (!IsDebuggerPresent())
        NFile::SetModuleCurrentDir();
    }
  }

#ifndef _SHIPPING
  if( CmdLineLite::Instance().IsKeyDefined( "RemoteDebugger" ) )
  {
    if( StartRemoteDebugger() )
      MessageBox( 0, "Remote Debugger has been started.\nTry to connect to the computer and press OK", "Waiting for connection", MB_OK | MB_ICONINFORMATION ); 
  }
#endif

  SyncProcessorState();

  threading::SetDebugThreadName( "Main" );
  
  InitCommonControls();
  NFile::InitBaseDir();
  NProfile::Init( PRODUCT_TITLE );
  
  AppInstancesLimit instancesLimit( PRODUCT_TITLE_SHORT );
#ifndef _SHIPPING
  NDebug::SetProductNameAndVersion( NFile::GetBinDir(), PRODUCT_TITLE_SHORT, VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );
#else //_SHIPPING
  NDebug::SetProductNameAndVersion( NProfile::GetFullFolderPath(NProfile::FOLDER_PLAYER), PRODUCT_TITLE_SHORT, VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );
#endif //_SHIPPING

  if ( !instancesLimit.Lock( 3 ) )
  {
    mainVars.DeInit();
    return 0;
  }

  string logsPath = GetFullFolderPath( NProfile::FOLDER_LOGS );
  if (!NFile::DoesFolderExist(logsPath))
    NFile::CreatePath(logsPath);
  NDebug::OverrideDebugLogDir( logsPath.c_str() );

  persistentEvents::CreateSingleton( NDebug::GetDebugLogDir() );
  persistentEvents::GetSingleton()->CheckUnfinishedSessions();
  persistentEvents::AutoClose persistentEventsAutoClose;

  // убираем клиентский заголовок строки до состояния "как было" (только severity)
  GetSystemLog().SetHeaderFormat( NLogg::EHeaderFormat::Default ); 
  GetGameLogicLog().SetHeaderFormat( 0 );

  StrongMT<NLogg::BasicTextFileDumper> textLogDumper( NLogg::BasicTextFileDumper::New( &GetSystemLog(), "output") );

#ifndef _SHIPPING
  StrongMT<NLogg::CFileStreamDumper> gameLogicStreamDumper = new NLogg::CFileStreamDumper( &GetGameLogicLog() );
  StrongMT<NLogg::CAssertDumper> assertDumper = new NLogg::CAssertDumper( &GetSystemLog() );
#endif //_SHIPPING

  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );
  //StrongMT<NLogg::CEventDumper> eventDumper = new NLogg::CEventDumper( &GetSystemLog() ); // it takes 80MB at game loading in deep of StackWalk64

  StrongMT<NLogg::CDumper> pAuxDumper;

  if( Compatibility::IsRunnedUnderWine() )
    pAuxDumper = new NLogg::CStdOutDumper( &GetSystemLog(), stderr, false );

  if ( isSpectator )
  {
    if ( !SteamAPI_Init() )
      DebugTrace( "SteamAPI_Init() failed\n" );
    else
      s_bSteamInited = true;
  }

  mainVars.useCrashRptHandler = !Compatibility::IsRunnedUnderWine() &&
    !CmdLineLite::Instance().IsKeyDefined( "-crashrpt_disable" );

  if ( mainVars.useCrashRptHandler )
  {
    const char * privacyPolicy = "http://updates.playpw.com/eula-ru.rtf";
#ifdef _SHIPPING
    const char * uploadUrl = CmdLineLite::Instance().GetStringKey( "-crashrpt_url", "http://SITE/upload/" );
#else //_SHIPPING
    const char * uploadUrl = CmdLineLite::Instance().GetStringKey( "-crashrpt_url", "http://SITE/upload/" );
#endif //_SHIPPING
    CrashRptWrapper::InstallForProcess( uploadUrl, !CmdLineLite::Instance().IsKeyDefined( "-crashrpt_nomultipart" ), false, 0, privacyPolicy );
  }
  else
    NBSU::InitUnhandledExceptionHandler();

  SetMallocThreadMask( GetCurrentThreadId() );

#ifdef DUMP_ALLOCS_FOR_MEMORY_MONITOR
  //NDebug::EnableAllocFreeEvents( true );
#endif

  if ( mainVars.useCrashRptHandler )
    CrashRptWrapper::AddFileToReport( textLogDumper->FileName().c_str(), "Application Log" );

  if ( mainVars.useCrashRptHandler )
    CrashRptWrapper::AddFileToReport( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ).c_str(), "Game Settings File" );

  profiler3::GetControl()->Setup( profiler3::SSettings() );

  NI_PROFILE_THREAD;

  profiler3ui::Init();
  mainVars.initProfiler = true;

  if( Compatibility::IsRunnedUnderWine() )
    DebugTrace( "System runned under Wine emulator" );
  else
    DebugTrace( "System runned under native Windows" );  

#ifndef _SHIPPING
  DebugTrace( "Development version" );
#endif // _SHIPPING

  if ( isTutorial )
  {
    MessageTrace("Starting in tutorial mode");
  }
  else if ( isReplay )
  {
    MessageTrace("Starting in replay mode");
  }
  else if ( isSpectator )
  {
    MessageTrace("Starting in spectator mode");
  }
  else
  {
    MessageTrace("Starting in normal mode");
  }

  NGlobal::ExecuteConfig( "default.cfg", NProfile::FOLDER_GLOBAL );
  NGlobal::ExecuteConfig( "user.cfg", NProfile::FOLDER_USER );
  NGlobal::ExecuteConfig( "lang.cfg", NProfile::FOLDER_PLAYER );

  if (!NGlobal::ExecuteConfig("social.cfg", NProfile::FOLDER_GLOBAL))
  {
    mainVars.DeInit();
    return 0xDEAD;
  }

#ifndef _SHIPPING
  if (CmdLineLite::Instance().IsKeyDefined("--splash"))
  {
    const NGameX::TutorialSplash splash;

    ::Sleep(5000);

    return 0xBEEF;
  }
#endif // _SHIPPING

  hWnd = (HWND)CmdLineLite::Instance().GetIntKey( "parentWindow" );
  SPluginSettings parentSettings;
  Strong<NGameX::ISocialConnection> socialServer;
  Strong<NGameX::GuildEmblem> guildEmblem = new NGameX::GuildEmblem;

  bool startFromCastle = false;

  NGameX::SocialBootstrap::LoginParams socialLoginParams;
  NGameX::SocialBootstrap::LaunchData socialLaunchData;

  typedef AutoPtr<NGameX::SocialBootstrap::Session> SocialBootstrapSessionPtr;
  typedef AutoPtr<NGameX::SocialBootstrap::MatchMaking> SocialBootstrapMatchMakingPtr;

  SocialBootstrapSessionPtr socialSession;

  if (isTutorial)
  {
    //--snid pw
    //--snuid 3602865
    //--server login0
    //--sntoken 10b9c1b6fd2bab21de2aa1daaf3d189c
    //--secret 085fa17457d1fba12e4eb596b83ba99a
    //--needqueue
    //ver 0.12.357.33707
    //--pwdserver http://ru.pwcastle.SITE.com:88/
    socialLoginParams.queueLogin = CmdLineLite::Instance().IsKeyDefined("--needqueue");
    socialLoginParams.serverName = CmdLineLite::Instance().GetStringKey("--server");
    socialLoginParams.serverSecret = CmdLineLite::Instance().GetStringKey("--secret");
    socialLoginParams.snid = CmdLineLite::Instance().GetStringKey("--snid");
    socialLoginParams.snuid = CmdLineLite::Instance().GetStringKey("--snuid");
    socialLoginParams.sntoken = CmdLineLite::Instance().GetStringKey("--sntoken");
    socialLoginParams.sntoken2 = CmdLineLite::Instance().GetStringKey("--sntoken2");
    socialLoginParams.version = CmdLineLite::Instance().GetStringKey("ver");

    const NGameX::TutorialSplash splash;

    socialSession = SocialBootstrapSessionPtr(new NGameX::SocialBootstrap::Session(socialLoginParams, false));

    if (!socialSession->Login())
    {
      ErrorTrace("Social login failed");

      ShowLocalizedErrorMB(L"SocialConnectionFailed", L"Failed to connect to server.");
      return 0xDEAD;
    }

    NGameX::SocialBootstrap::MatchMaking smm(*socialSession);

    if (!smm.Make())
    {
      ErrorTrace("Social matchmaking failed");

      ShowLocalizedErrorMB(L"SocialMatchMakingFailed", L"Failed to start game session.");
      return 0xDEAD;
    }

    socialLaunchData.Update(*socialSession);
    socialLaunchData.Update(smm);

    pluginSett = &parentSettings;

    pluginSett->width = (CmdLineLite::Instance().GetIntKey("parentWidth"));
    pluginSett->height = (CmdLineLite::Instance().GetIntKey("parentHeight"));
    pluginSett->fullscreen = (CmdLineLite::Instance().GetIntKey("parentFullscreen") != 0);
    pluginSett->sessionLogin = socialLaunchData.sessionId.c_str();

    pluginSett->uid = socialLaunchData.uid.c_str();
    pluginSett->serverKey = socialLaunchData.serverKey.c_str();
    pluginSett->serverName = socialLaunchData.serverLocation.c_str();
    pluginSett->serverSecret = socialLaunchData.serverSecret.c_str();

    socialServer = new NGameX::SocialConnection(*socialSession);
  }
  else if ( CmdLineLite::Instance().IsKeyDefined( "parentWidth" ) )
  {
    pluginSett = &parentSettings;

    pluginSett->width = CmdLineLite::Instance().GetIntKey( "parentWidth" );
    pluginSett->height = CmdLineLite::Instance().GetIntKey( "parentHeight" );
    pluginSett->fullscreen = ( CmdLineLite::Instance().GetIntKey( "parentFullscreen" ) != 0 );
    pluginSett->sessionLogin = CmdLineLite::Instance().GetStringKey( "parentSessionLogin" );

    pluginSett->uid = CmdLineLite::Instance().GetStringKey("uid");
    pluginSett->serverKey = CmdLineLite::Instance().GetStringKey("serverKey");
    pluginSett->serverName = CmdLineLite::Instance().GetStringKey("serverName");
    pluginSett->serverSecret = CmdLineLite::Instance().GetStringKey("serverSecret");

    socialServer = new NGameX::SocialConnection( pluginSett->serverName, pluginSett->uid, pluginSett->serverKey, pluginSett->serverSecret );

    startFromCastle = true;
  }
  else
  {
    socialServer = new NGameX::DummySocialConnection();
  }

  const char * sessLogin = pluginSett ? pluginSett->sessionLogin : 0;
  if ( !sessLogin )
    sessLogin = CmdLineLite::Instance().GetStringKey( "-session_login", 0 );

#ifdef _SHIPPING
  const bool launch = isReplay || ((isTutorial || startFromCastle) && !!sessLogin);

  if (!launch)
  {
    ShowLocalizedErrorMB( L"StartViaLauncher", L"Please start the game via the launcher." );

    mainVars.DeInit();
    return 0xDEAD;
  }
#endif

  if ( pluginSett )
	{
//    NGlobal::SetVar( "gfx_resolution", NStr::StrFmt( "%dx%d", pluginSett->width, pluginSett->height ), STORAGE_DONT_CARE );
//		NGlobal::SetVar( "gfx_fullscreen", NStr::StrFmt( "%d", pluginSett->fullscreen ? 1 : 0 ), STORAGE_DONT_CARE );
	}

  //TODO: add SHIPPING ifdef
  bool fullscreen = NGlobal::GetVar( "gfx_fullscreen" ).GetInt64();

  const string szAppName( NStr::StrFmt( "%s - %s - %d.%d.%02d.%04d", PRODUCT_TITLE, VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION ) );
  string windowTitle( NStr::StrFmt( "%s - %s - %d.%d.%02d.%04d", PRODUCT_TITLE, VERSION_BRANCH, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION ) );
  if ( instancesLimit.Index() > 1 )
    windowTitle += NStr::StrFmt( " (%i)", instancesLimit.Index() );

  //if ( pluginSett )
  //{
  //  if ( !NMainFrame::InitApplication( hInstance, szAppName.c_str(), windowTitle.c_str(), MAKEINTRESOURCE( IDI_MAIN ), fullscreen, pluginSett->width, pluginSett->height, hWnd ) )
  //    return 0xDEAD;
  //}
  //else
  {
    if ( !NMainFrame::InitApplication( hInstance, szAppName.c_str(), windowTitle.c_str(), MAKEINTRESOURCEW( IDI_MAIN ), fullscreen, 800, 600, hWnd ) )
    {
      mainVars.DeInit();
      return 0xDEAD;
    }
  }

  Strong<ICastle> pCastleLink;

  if ( startFromCastle )
  {
    pCastleLink = CreateCastleLink( CmdLineLite::Instance().GetIntKey("connectionPort"),
                                    CmdLineLite::Instance().GetStringKey("castleCmdLn"),
                                    hInstance,
                                    NMainFrame::GetWnd());
  }
  else if (isTutorial)
  {
    nstl::string castleCmdLine(CmdLineLite::Instance().GetStringKey("--castleCmdLn", "Castle.exe"));

    {
      castleCmdLine = NStr::StrFmt("<%s> --snid %s --snuid %s --sntoken %s ver %s --server %s --secret %s --loginKey %s --uid %s",
        castleCmdLine.c_str(),
        socialLoginParams.snid,
        socialLoginParams.snuid,
        socialLaunchData.serverLoginToken.c_str(),
        socialLoginParams.version,
        socialLaunchData.serverName.c_str(),
        socialLaunchData.serverSecret.c_str(),
        socialLaunchData.serverKey.c_str(),
        socialLaunchData.uid.c_str());
    }

    pCastleLink = CreateCastleLink(0, castleCmdLine.c_str(), hInstance, NMainFrame::GetWnd());
  }
  else
  {
    pCastleLink = CreateDummyCastleLink();
  }

  mainVars.input = new Input::Binds( Input::CreateHwInput( NMainFrame::GetWnd(), hInstance, false, true ) );
  mainVars.inputSystemMesages = new Input::SystemEvents( mainVars.input );
  Input::BindsManager::Instance()->SetBinds( mainVars.input );
  mainVars.initInput = true;

  RootFileSystem::AddDebugMonitor( new FileExtensionStatisticsMonitor );
  IFileReadCallback* callback = CreateFileReadCallback( OnPileFileReadError, new GameFileReadContext( pCastleLink ) );

  RootFileSystem::RegisterFileSystem( new fileSystem::PileFileSystem(callback), callback );
  RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );

  if (g_language.empty())
  {
    g_language = "ru-RU";
  }
  if (!TryLoadTextsCache( NFile::Combine( NFile::GetBaseDir(), "Data/Localization/" + g_language + "/text.text" ).c_str() ))
  {
    // fall back to the root text.text file
    TryLoadTextsCache( NFile::Combine( NFile::GetBaseDir(), "Packs/text.text" ).c_str() );
  }

  if ( const char * fsActLog = CmdLineLite::Instance().GetStringKey( "-log_fs_activity" ) )
    RootFileSystem::AddDebugMonitor( new FileActivitySimpleMonitor( fsActLog ) );

  Types::HashCheck::Check();
  PF_Types::HashCheck::Check();
  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );
  mainVars.initDB = true;

  if ( !NGlobal::ExecuteConfig( "game.cfg",	NProfile::FOLDER_GLOBAL ) )
  {
    mainVars.DeInit();
    return false;
  }

#ifdef _SHIPPING
  NGlobal::ExecuteConfig( "input.cfg", NProfile::FOLDER_USER, L"input" );
  NGlobal::ExecuteConfig( "smart_chat.cfg", NProfile::FOLDER_GLOBAL );
#endif

  if ( isSpectator )
  {
    NGlobal::ExecuteConfig( "spectator.cfg",	NProfile::FOLDER_GLOBAL );
  }

  NFile::DeleteOldFiles( NProfile::GetRootLogsFolder().c_str(), double(g_deleteLogFilesAfterDays) * 60 * 60 * 24 );
  NFile::DeleteOldFiles( NProfile::GetFullFolderPath(NProfile::FOLDER_REPLAYS).c_str(), double(g_deleteLogFilesAfterDays) * 60 * 60 * 24 );

  if ( s_localGame || isReplay )
  {
    context = new Game::LocalGameContext( isSpectator );
  }
  else if (isTutorial)
  {
    context = new Game::GameContext(socialLaunchData.sessionId.c_str(), NULL, socialLaunchData.mapId.c_str(), socialServer, guildEmblem, false, true);
  }
  else
  {
    const char * devLogin = CmdLineLite::Instance().GetStringKey( "-dev_login", "" );
    const char * mapId = CmdLineLite::Instance().GetStringKey( "mapId", "" );
    context = new Game::GameContext( sessLogin, devLogin, mapId, socialServer, guildEmblem, isSpectator, false );
  }

  context->Start();
  mainVars.initContext = true;

  //This config is mainly needed to enable custom lobby console commands
  NGlobal::ExecuteConfig( "autoexec.cfg",	NProfile::FOLDER_GLOBAL );

  if(s_bRegisterReplayExtention)
   RegisterReplayFileExtentionAssociation();

  CoInitialize(NULL);

  if ( s_NullRender && !g_NullRenderNoLogBox )
  {
    mainVars.logBox = new NLogg::EditBoxDumper( &GetSystemLog(), NMainFrame::GetWnd() );
  }

  if ( g_DebugDumpInfo )
  {
    NBSU::SystemReport sysRep;
    sysRep.dumpSystemInfo(true);
  }

  Render::RenderMode renderMode;
  
  mainVars.renderingInterface = new Render::DeviceLostWrapper<PF_Render::Interface>;
  Render::GetRenderModeFromConfig(renderMode);
  Render::GetRenderer()->CorrectRenderMode(renderMode);
  PF_Render::Interface::CorrectRendermode( renderMode );
    
  NullRenderSignal::Signal(s_NullRender);
  if(!mainVars.renderingInterface->Start( renderMode ) && s_NullRender != RENDER_DISABLE_FLAG)
  {
    mainVars.DeInit();
    return 0xDEAD;
  }

  mainVars.initRender = true;
  mainVars.initDisplay = true;

  if(s_NullRender != RENDER_DISABLE_FLAG)
    if ( !CheckHardwareCompatibility() )
    {
      mainVars.DeInit();
      return 0xDEAD;
    }

  UI::Initialize( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot" ) ) );
  mainVars.initUI = true;

  if(s_NullRender != RENDER_DISABLE_FLAG) {
    const Render::RenderMode& currentRenderMode = Render::GetRenderer()->GetCurrentRenderMode();
    UI::UpdateScreenResolution( currentRenderMode.width, currentRenderMode.height, false );
    NMainFrame::ResizeWindow( currentRenderMode.width, currentRenderMode.height, currentRenderMode.isFullScreen );
  }

  if ( mainVars.logBox )
    mainVars.logBox->ResizeLogWindow();

  /*if(s_NullRender != RENDER_DISABLE_FLAG)*/ 
  {
    NSoundScene::TryTurnOnSound();

    NDb::SoundRoot::InitRoot( NDb::DBID( "Audio/SoundRoot" ) );
    for ( int i = 0; i < NDb::SoundRoot::GetRoot()->sceneScenes.size(); i++ )
      NSoundScene::InitSoundScene( i, NDb::SoundRoot::GetRoot()->sceneScenes[i] );
    NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_LOADING, false );
    mainVars.initSound = true;
  }

  if (s_bSteamInited)
    SteamUtils()->SetOverlayNotificationPosition( k_EPositionBottomLeft );

  // force linking with PF_Core
  PF_Core::ForceLink();
  PF_Minigames::ForceLink();
  TooSmartLinker();

  RaiseMainThreadPriority();

  NMainLoop::CreateSystemScreens();

  AltTabChecker altTabChecker( NMainFrame::IsAppNotMinimized() && NMainFrame::IsAppActive() );
  bool isActive = true; // This ensures, that first priority change will always raise priority

  MovingAverage<float, 60> avgDeltaTime;
  bool isFirstLoopStep = true;

  static HANDLE hFileMapping = INVALID_HANDLE_VALUE;

  bool wasActive = true;
  bool wasInLostDevice = false;

  SetStepCallback(StepContext);

  if(isReplay)
  {
    nstl::wstring path;
    NStr::ToUnicode(&path, replayFileName);
    NGlobal::RunCommand(NStr::StrFmtW(L"replay \"%s\"", path.c_str()));
  }

  InitCensorDicts();
  
  mainVars.initGameFSM = true;
  while ( true )
  {
    NI_PROFILE_BLOCK_MEM( "Main Loop" );

#if defined( NI_PROFILER_USE_VERSION ) && ( NI_PROFILER_USE_VERSION == 3 )
    NI_PROFILE_BLOCK_MEM( "Frame" );
#endif
    //compulsory update
    //-----------------------------------------------------------------------
    NMainLoop::UpdateTime();
    timerUpdated = true;
    
    { //Check for alt+tab
      altTabChecker.Update();
      if(altTabChecker.IsActive() != isActive) {
        isActive = altTabChecker.IsActive();
        context->OnAltTab(isActive);
      }
    }

    if( fullscreen && altTabChecker.IsActive() )
    {
      if(INVALID_HANDLE_VALUE == hFileMapping) {
        // Turn off Outlook notifications. See http://support.microsoft.com/kb/913045
        const TCHAR strFileMapName[] = TEXT("Local\\FullScreenPresentationModeInfo");
        hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(RECT), strFileMapName);
        if(hFileMapping) {          
          // Writing the application's rect into the shared memory
          RECT *pRect = static_cast<RECT *>(MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0));
          if(pRect) {
            GetWindowRect(NMainFrame::GetWnd(), pRect);
            UnmapViewOfFile(pRect);
          }    
        }
      }
    }
    else if(INVALID_HANDLE_VALUE != hFileMapping)
    {
      CloseHandle(hFileMapping);
      hFileMapping = INVALID_HANDLE_VALUE;
    }

    // Update socialConnection
    {
      socialServer->Step();
    }

    // Update sound
    {
      if ( altTabChecker.IsActive() )
	      NSoundScene::SystemResume();
	    else
	      NSoundScene::SystemStop();
	    NSoundScene::EventSystemUpdate( NMainLoop::GetTimeDelta() * 1000.0f );
	    NSoundScene::Update();
    }

    StrongMT<StatisticService::GameStatistics> gameStatistics = context->GameStatLogic();
    // Pump messages
    {
      NHPTimer::STime startTime, endTime;
      NHPTimer::GetTime( startTime );

      NMainFrame::PumpMessages();

      NHPTimer::GetTime( endTime );

      if ( NHPTimer::Time2Milliseconds( endTime - startTime ) > 10 )
      {
        if ( gameStatistics )
        {
          gameStatistics->AddStepTimeFlags( StatisticService::RPC::DragFlag );
          gameStatistics->RemoveStepTimeFlags( StatisticService::RPC::DragFlag );
        }

        DebugTrace("Pump messages lag");
      }

      if ( NMainFrame::IsExit() )
        context->Shutdown();
    }

    if ( gameStatistics )
    {
      if ( wasActive ^ NMainFrame::IsAppActive() )
      {
        if ( NMainFrame::IsAppActive() )
            gameStatistics->RemoveStepTimeFlags( StatisticService::RPC::InactiveFlag );
        else
            gameStatistics->AddStepTimeFlags( StatisticService::RPC::InactiveFlag );

        wasActive = NMainFrame::IsAppActive();
      }

      if ( wasInLostDevice ^ Render::GetRenderer()->DeviceIsLost() )
      {
        if ( Render::GetRenderer()->DeviceIsLost() )
          gameStatistics->AddStepTimeFlags( StatisticService::RPC::InactiveFlag );
        else
          gameStatistics->RemoveStepTimeFlags( StatisticService::RPC::InactiveFlag );

        wasInLostDevice = Render::GetRenderer()->DeviceIsLost();
      }
    }

    RootFileSystem::ProcessFileWatchers();
    // Step context
    int numCommands = -1;
    if( !NMainFrame::IsExit() )
    {
      NI_PROFILE_BLOCK( "Context" );
      mainPerf_ContextStep.Start();
      numCommands = context->Poll( NMainLoop::GetTimeDelta() );
      mainPerf_ContextStep.Stop();
    }
    timerUpdated = false;

    SkipFrameIfNeeded(numCommands);

    const float commonTimeDelta = NMainLoop::GetTimeDelta();
    
    //Усредняем длительность кадра, что даёт значительно более плавную картинку, при FPS < 60
    const float smoothTimeDelta = avgDeltaTime.NextValue( NMainLoop::GetTimeDelta(), g_maxMovingAvgTime );    
    NMainLoop::SetTemporaryTimeDelta( smoothTimeDelta );
    
    { // Mainloop
      mainPerf_Step.Start();

      //Poll input
      mainVars.input->Update( NMainLoop::GetTimeDelta(), altTabChecker.IsActive() );
      mainVars.inputSystemMesages->Pump( mainVars.input->GetEvents() );

      //Step game screens and stuff #here call adv screen
      const bool canContinue = NMainLoop::Step( NMainFrame::IsAppActive(), mainVars.input->GetEvents() );
      mainPerf_Step.Stop();
      if ( !canContinue ) 
        break;
    }

    if ( !NMainFrame::IsAppActive() && 0 <= g_inactiveSleep && g_inactiveSleep < 1000 )
    {
      NI_PROFILE_BLOCK( "Sleep" );
      Sleep( g_inactiveSleep );
    }

    // Do present, unless skip everything
    if ( !s_NullRender )
    {
      Render::SharedVB::UnlockAll(); // Don't hold VB's locked for too long

      NI_PROFILE_BLOCK( "RenderPresent" );
      mainPerf_Present.Start(true);
      //NMainLoop::VSyncController::WaitBeforePresent();
      int presentCount = NMainLoop::VSyncController::CalculatePresentCount();
      for (int i = 0; i < presentCount; i++)
        mainVars.renderingInterface->Present();
      NMainLoop::VSyncController::MarkPresentFinished();
      mainPerf_Present.Stop();
    }
    
    NMainLoop::SetTemporaryTimeDelta( commonTimeDelta );

    // Process counters
    mainPerf.Stop();

    {
      NI_PROFILE_BLOCK( "NDebug" );

      // debug ui renderers can be processed only if we call some Render
      NDebug::DrawDebugVars();

      debugDisplay::Render();

      debugDisplay::AddText( "__pos0", debugDisplay::Align( 0, -1 ), NStr::StrFmt( "version: %s-%d.%d.%02d.%04d", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, VERSION_REVISION ), debugDisplay::Color::White );

      NDebug::ShowFPS();

      NDebug::ShowTime();
      NDebug::DumpSystemStatistics();

      NDebug::CheckWatchedVars();
      NDebug::ResetDebugVarsOnFrame( NMainLoop::GetTimeDelta() );

      // get information about mallocs from newdelete.cpp
		  heapAllocs.SetValue( GetMallocsTotal() );
		  heapAllocsSize.SetValue( GetMallocsSize() );
		  unfreeHeapAllocs.SetValue( GetMallocsUnfree() );

      // get information about mallocs fron detour
		  //heapAllocs.SetValue( NDebug::GetHeapAllocCount() );
		  //heapAllocsSize.SetValue( NDebug::GetTotalHeapAllocSize() );
		  //unfreeHeapAllocs.SetValue( NDebug::GetUnfreeHeapAllocCount() );

#ifndef _SHIPPING
		  virtualAllocs.SetValue( NDebug::GetVirtualAllocCount() );
		  virtualAllocsSize.SetValue( NDebug::GetTotalVirtualAllocSize() );
		  unfreeVirtualAllocs.SetValue( NDebug::GetUnfreeVirtualAllocCount() );

		  totalAllocsSize.SetValue( ( NDebug::GetTotalVirtualAllocSize() + NDebug::GetTotalHeapAllocSize() ) / 1024 / 1024 );
#endif //_SHIPPING
    }
		
    mainPerf.Start( true );

    // Render. RenderUI at least
    if( !s_NullRender )
    {
      NI_PROFILE_BLOCK( "Render" );
      mainPerf_Render.Start();
      mainVars.renderingInterface->Render( false );
      mainPerf_Render.Stop();
    }
    else
      mainVars.renderingInterface->FlushUI();

    if ( isFirstLoopStep )
      pCastleLink->StartRender();
      
    pCastleLink->Update( NMainLoop::GetTimeDelta() );
    
    isFirstLoopStep = false;
  } //Main loop ends

  if (socialSession )
    socialSession->Logout();

  if ( NMainFrame::GetExitCode() == EXIT_CODE_QUIT_CASTLE )
  {
    //if (socialSession)
    //  socialSession->Logout();
    pCastleLink->QuitGame();
    

  }
  else
    pCastleLink->ReturnToCastle();

  if ( persistentEvents::GetSingleton() )
    persistentEvents::GetSingleton()->Close();

	if(!isReplay)
  {
#ifdef _SHIPPING
		Input::SaveInputConfig( NProfile::GetFullFilePath( "input.cfg", NProfile::FOLDER_USER ), L"input" );
#endif
    NGlobal::SaveConfig( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ), STORAGE_USER );
  }

#ifndef _SHIPPING
  DumpLoadedModules();
#endif //_SHIPPING

  mainVars.DeInit();
  return 0;
}


//Entry point
extern "C"
{

INTERMODULE_EXPORT void WINAPIV StartPWApplication( HWND hWnd )
{
  PseudoWinMain( GetModuleHandle( NULL ), hWnd, GetCommandLine(), 0 );
}

INTERMODULE_EXPORT void WINAPIV StartPWPlugin( HWND hWnd, int width, int height, bool fullscreen, const char * sessionLogin )
{
  SPluginSettings sett;
  sett.width = width;
  sett.height = height;
  sett.fullscreen = fullscreen;
  sett.sessionLogin = sessionLogin;
  PseudoWinMain( GetModuleHandle( NULL ), hWnd, GetCommandLine(), &sett );

  TerminateProcess( GetCurrentProcess(), 0 );
}

} //extern "C"


#ifndef DO_NOT_USE_DLLMAIN
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
  switch ( fdwReason )
  {
    case DLL_PROCESS_ATTACH:
      return TRUE;
    case DLL_THREAD_ATTACH:
      return TRUE;
    case DLL_THREAD_DETACH:
      return TRUE;
    case DLL_PROCESS_DETACH:
      return TRUE;
  }
  return TRUE;
}
#endif



//Debug console command, used to debug exception handling
static int DoTheStackOverflow( int depth, char * ptr, int size )
{
  if ( !depth )
    return 0;

  int sum = 0;
  for( int i = 0; i < size; ++i )
    sum += ptr[i];
  char buf[256];
  memset( buf, 0, 256 );
  sum += DoTheStackOverflow( depth - 1, buf, 256 );
  return sum;
}



static bool DebugCrashNow( const char *name, const vector<wstring> &params )
{
  if ( params.size() == 1 )
  {
    if ( !_wcsicmp( params[0].c_str(),  L"gpf") )
    {
      int * nullPtr = 0;
      DebugTrace( "Writing address 0x%08x...", (int)nullPtr ); //Block compiler optimizations
      *nullPtr = 0;
      return true;
    }
    else if ( !_wcsicmp( params[0].c_str(),  L"zero") )
    {
      int zero = strtol( "0", 0, 10 ); //FIXME: Maharaja code!
      DebugTrace( "Dividing by %d...", zero ); //Block compiler optimizations
      DebugTrace( "Result: %d", (int)params.size() / zero );
      return true;
    }
    else if ( !_wcsicmp( params[0].c_str(),  L"stack") )
    {
      DebugTrace( "Flooding stack..." );
      DebugTrace( "Result: %d", DoTheStackOverflow( 1024 * 1024 * 1024, 0, 0 ) );
      return true;
    }
    else if ( !_wcsicmp( params[0].c_str(),  L"assert") )
    {
      NI_ALWAYS_ASSERT( "Test assert" );
      return true;
    }
    else if ( !_wcsicmp( params[0].c_str(),  L"heap") )
    {
      DebugTrace( "Allocating memory..." );
      for ( int i = 0; i < 1024 * 1024; ++i )
      {
        const int size = 64 * 1024;
        char * ptr = new char[size];
        if ( ptr )
        {
          //Fill just first kb to avoid extensive swap
          for ( int j = 0; ( j < size ) && ( j < 1024 ); ++j )
            ptr[j] = j & 0xff;
        }
      }
      return true;
    }
  }

  DebugTrace( "Usage: %s gpf | zero | stack | assert | heap", name );
  return true;
}

static bool SetMallocThreadMask( const char * name, const vector<wstring> & _paramsSet )
{
  if ( _paramsSet.size() > 0 )
    SetMallocThreadMask( NStr::ToULong( NStr::ToMBCS( _paramsSet[0] ) ) );

  return true;
}

REGISTER_CMD( debug_crash_now, DebugCrashNow );
REGISTER_CMD( malloc_mask, SetMallocThreadMask )
